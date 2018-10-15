/**
 * \file io.c
 */

#include "../include_console/io.h"


char lireChar()
{
	char c = 0;
	c = getchar();
	if (c != '\n')
	{
		printf("\n\e[2A");
		while (getchar() != '\n')
		{
			printf(" ");
		}
		printf(" \n\n");
		printf("\n\e[2A");
	}

	return c;
}


/**
 * Fonction d'affichage des traits sur la sortie standard.
 *
 * @param c nombre de traits a afficher
 */
void affiche_trait (int c)
{
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * Fonction d'affichage de lignes sur la sortie standard.
 *
 * @param c nombre de lignes
 * @param *ligne un pointeur représentant la présence ou non d'une cellule
 */
void affiche_ligne (int c, int* ligne)
{
	int i;
	for (i=0; i<c; ++i)
	{
		if (ligne[i] == 0 ) 
		{
			printf ("|   "); 
		}
		else if (ligne[i] < 0)
		{
			printf("| X ");
		}
		else 
		{
			printf ("| %d ", ligne[i] - 1);
		}
	}
	printf("|\n");
	return;
}


/**
 * Fonction d'affichage d'une grille.
 *
 * Affiche la grille sur la sortie standard.
 *
 * @param g une grille
 */
void affiche_grille (grille g)
{
	int i, l = g.nbl, c = g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i = 0 ; i < l ; ++i) 
	{
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/**
 * Fonction d'effacage d'une grille
 *
 * Nettoie la zone du terminal dans laquelle la grille est affichée.

 * @param g une grille
 */
void efface_grille (grille g)
{
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 * Fonction de jeu
 *
 * @param g Grille de l’état actuel du jeu.
 * @param gc Grille dans laquelle stocker le nouvel état du jeu.
 *
 * Permet l'évolution du jeu, gère les options d'affichage
 * de vieillissement, de voisinage cyclique, d'évolution de la 
 * grille ou de l'arrêt du jeu.
 *
 * Elle teste pour cela la valeur d'une variable de type char :
 * c active ou désactive le voisinage cyclique
 * v active ou désactive l'affichage du vieillissement
 * q quitte le jeu
 * Enter passe au tour suivant
 */
void debut_jeu(grille *g, grille *gc)
{
	int temps = 0, cycle = 1, v = 0, tmposc;
	int (*f)(int, int, grille) = compte_voisins_vivants;
	char c = 0;
	while (c != 'q') // touche 'q' pour quitter
	{
		
		printf("Temps : %d, Cycle : %d Viellissement : %d", temps, cycle, v);
		affiche_grille(*g);
		c = lireChar();
		switch (c) 
		{
			case '\n' :
			{ // touche "entree" pour évoluer
				temps+=1;
				evolue(g,gc,f,v);
				break;
			}

			case 'c' :
			{
				cycle = (cycle+1) % 2;
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

			case 'v' :
			{
				v = (v+1) % 2;
				break;
			}

			case 'o' :
			{
				tmposc = est_oscillante(g, f, v);
				if (tmposc < 0)
				{
					printf("Colonie non oscillante");
				}
				else
				{
					printf("Colonie oscillante de période %d ",tmposc);
				}
				break;
			}

			case 'q' :
			{
				return;
			}
		}
		efface_grille(*g);
	}
	return;	
}
