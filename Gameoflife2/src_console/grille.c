/**
 * \file grille.c
 */

#include "../include/grille.h"


/** 
 * Fonction d'initialisation d'un grille
 *
 * Initialise un grille à partir d'un fichier
 *
 * @param filename nom de fichier contenant les dimensions de la grille
 * @param g un pointeur sur la grille 
 */
void init_grille_from_file (char * filename, grille* g)
{
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n = 0; n < vivantes; ++n)
	{
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fscanf(pfile, "%d", & vivantes);
	for (n = 0; n < vivantes; ++n)
	{
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_nonViable(i,j,*g);
	}
	fclose (pfile);
	return;
}

/**
 * Fonction de copie de grille
 *
 * Copie la grille source vers la grille de destination
 *
 * @param gs grille source
 * @param gd grille de destination
 */
void copie_grille (grille gs, grille gd)
{
	int i, j;
	for (i=0; i<gs.nbl; ++i) 
	{
		for (j=0; j<gs.nbc; ++j)
		{	
			gd.cellules[i][j] = gs.cellules[i][j];
		}
	}
	return;	
}


/**
 * Initialization de la grille.
 *
 * Alloue un segment de mémoire pour stocker les cellules et stocke dans
 * la structure les dimensions de la grille.
 *
 * @param l Nombre de lignes de la grille.
 * @param c Nombre de colonnes de la grille.
 * @param *g Pointeur vers une grille non initialisée.
*/
void alloue_grille (int l, int c, grille* g)
{
	int i,j;

	g->nbl = l;
	g->nbc = c;
	g->cellules = malloc(sizeof(int *) * l);

	for (i = 0 ; i < l ; i++)
	{
		g-> cellules[i] = malloc (sizeof(int) * c);
		for (j = 0 ; j < c ; j++)
		{
			g->cellules[i][j] = 0;
		}
	}
	return ;
}

/**
 * Libère une grille.
 *
 * @param *g Un pointeur vers une grille initialisée.
 *
 * @warn Si la grille n’est pas initialisée, des libérations invalides seront
 *   provoquées.
 */
void libere_grille (grille *g)
{
	int i;
	for (i = 0 ; i < g->nbl ; i++)
	{
		free(g->cellules[i]);
	}

	free (g->cellules);
	return ;
}
