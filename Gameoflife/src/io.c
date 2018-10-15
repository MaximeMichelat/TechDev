/**
 * \file
 */

#include "../include/io.h"

void afficheTexte (cairo_surface_t* cs, int x, int y, char* str)
{
	cairo_t *cr;
	cr = cairo_create(cs);

	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_select_font_face (cr, "Times New Roman", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 12);

	cairo_move_to(cr, x, y);
	cairo_show_text(cr, str);
	cairo_destroy(cr);
}

void affiche_grille (grille g, cairo_surface_t* cs)
{
	//Espace correspond à l'espace entre les cellules
	int i, j, l = g.nbl, c = g.nbc;
	int x = ESPACE+30, y = ESPACE+30;

	cairo_t* cr;
	cr = cairo_create(cs);

	cairo_set_source_rgb (cr, 0,0,0);
	cairo_paint(cr);

	for (i = 0 ; i < l ; i++)
	{
		for (j = 0 ; j < c ; j++)
		{
			cairo_rectangle (cr, x, y, TAILLECEL, TAILLECEL);
			if (g.cellules[i][j] == 0)
			{
				cairo_set_source_rgb (cr, 1.0,0,0);
			}
			else if (g.cellules[i][j] < 0)
			{
				cairo_set_source_rgb (cr, 0.5,0,1.0);
			}
			else
			{
				cairo_set_source_rgb (cr, 0, 1-((g.cellules[i][j]) * 0.1), 1);
			}
			cairo_fill(cr);
			x+=TAILLECEL+ESPACE;
		}
		x=ESPACE+30;
		y+=TAILLECEL+ESPACE;
	}
	cairo_destroy(cr);
}

void debut_jeu (grille* g, grille* gc)
{
	int temps = 0, cycle = 1, vi = 0, tmposc, o = 0;
	int (*f)(int, int, grille) = compte_voisins_vivants;

	char str[100];

	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	if ( !(dpy = XOpenDisplay(NULL)))
	{
		fprintf(stderr, "ERROR : Could not open display\n");
		exit(1);
	}

	scr = DefaultScreen(dpy);
	rootwin = RootWindow(dpy, scr);

	win = XCreateSimpleWindow (dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, BlackPixel( dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput (dpy, win, ExposureMask | ButtonPressMask | KeyPressMask);
	XMapWindow(dpy, win);

	cairo_surface_t* cs;
	cs = cairo_xlib_surface_create(dpy, win, DefaultVisual (dpy, 0), SIZEX, SIZEY);

	while (1)
	{
		XNextEvent (dpy, &e);

		if (e.type == ButtonPress)
		{
			if (e.xbutton.button == Button1)
			{
				temps += 1;
				evolue (g, gc, f, vi);
			}
			else
			{
				break;
			}
		}
		else if (e.type == KeyPress)
		{
			switch (e.xkey.keycode)
			{
				case 54 : 
				{
					cycle = (cycle + 1) % 2;
					if (cycle)
					{
						f = compte_voisins_vivants;
					}
					else
					{
						f = compte_voisins_vivants2;
					}
					break;
				}

				case 55 :
				{
					vi = (vi + 1) % 2;
					break;
				}

				case 32 :
				{
					o = (o + 1) % 2;
					tmposc = est_oscillante(g, f, vi);
					break;
				}
			}
		}
		affiche_grille (*g, cs);
		sprintf(str, "Temps : %d", temps);
		afficheTexte(cs, 50, 20, str);

		if (cycle)
		{
			sprintf(str, "Cyclique");
		}
		else
		{
			sprintf(str, "Non-cyclique");
		}
		afficheTexte(cs, 150, 20, str);

		if (o)
		{
			if (tmposc < 0)
			{
				sprintf(str, "Oscillation : Colonie non oscillante");
			}
			else
			{
				sprintf(str, "Oscillation : Colonie oscillante de période %d", tmposc);
			}
		}
		else
		{
			sprintf(str, "Oscillation : désactivée");
		}
		afficheTexte(cs, 250, 20, str);


		if (vi)
		{
			sprintf(str, "Viellissement des cellules activé");
		}
		else
		{
			sprintf(str, "Viellissement des cellules desactivé");
		}
		afficheTexte(cs, 500, 20, str);
	}
}
