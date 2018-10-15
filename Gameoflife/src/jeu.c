/**
 * \file jeu.c
 */

#include "../include/jeu.h"

/**
 * Fonction de comptage des voisins vivants
 * @param g une grille de cellules et ses dimensions
 * @param i coordonnée sur l’axe des abscisses
 * @param j coordonnée sur l’axe des ordonnées
 *
 * Cette fonction n'est utilisée en pratique que lorsque 
 * le voisinage cyclique est activé
 */
int compte_voisins_vivants (int i, int j, grille g)
{
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	
	return v; 
}

/**
 * 2e fonction de comptage des voisins vivants
 * 
 * @see compte_voisins_vivants
 *
 * Cette fonction est utilisée en pratique lorsque le 
 * voisinage cyclique est desactivé
 */

int compte_voisins_vivants2 (int i, int j, grille g)
{
	int v = 0, it = 0, l = g.nbl, c = g.nbc;
	int im = i < l - 1, in = i > 0, jm = j < c - 1, jn = j > 0;

	int tab[8][3] =
	{
		{ in && jn, i-1, j-1},
		{ in, i-1, j},
		{ in && jm, i-1, j+1},
		{ jn, i, j-1},
		{ jm, i, j+1},
		{ im && jn, i+1, j-1},
		{ im, i+1, j},
		{ im && jm, i+1, j+1}
	};

	for (it = 0 ; it < 8 ; it++)
	{
		if (tab[it][0]) 
		{
			v+= est_vivante(tab[it][1], tab[it][2], g);
		}
	}
	return v;
}

/**
 * Fonction de mise à jour d'une grille
 *
 * @param g grille source
 * @param gc grille copie
 * @param *f, pointeur sur une fonction de type compte_voisins_vivants
 * @parma vi, entier représentant l'activation ou non de l'option vieillissement
 */
void evolue (grille *g, grille *gc, int (*f) (int, int, grille), int vi)
{
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (est_nonViable( i, j, *g))
			{
				continue;
			}

			v = f(i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if (( v!=2 && v!= 3 ) || (vi && ++g->cellules[i][j] > 8))
				{
					set_morte(i,j,*g);
				}
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}

/**
 * Fonction vérifiant si une grille est oscillante
 * @param g grille source
 * @param f fonction compte_voisins
 * @param vi viellissement des cellules
 */
int est_oscillante(grille* g, int (*f) (int, int, grille), int vi)
{
	grille gc, gc2;
	alloue_grille (g -> nbl, g -> nbc, &gc);
	alloue_grille (g -> nbl, g -> nbc, &gc2);

	copie_grille(*g, gc);

	int temps = 0;

	do 
	{
		evolue (&gc, &gc2, f, vi);
		temps+=1;

		if (temps > 100)
		{
			temps = -1;
			break;
		}
	}
	while ( !est_identique(g, &gc));

	libere_grille (&gc);
	libere_grille (&gc2);

	return temps;
}

/**
 * Fonction de vérification de grilles
 * Parcourt chaque grille et renvoie 0 si les grilles ne sont pas similaires
 * @param g grille source
 * @param gc 2e grille à comparer à la première
 */
int est_identique (grille* g, grille* gc)
{
	int i, j, lignes, col;
	lignes = g -> nbl;
	col = g -> nbc;

	if ( lignes != gc -> nbl || col != gc -> nbc)
	{
		return 0;
	}

	for ( i = 0 ; i < lignes ; i++)
	{
		for ( j = 0 ; j < col ; j++)
		{
			if ( g -> cellules[i][j] != gc ->cellules[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}
