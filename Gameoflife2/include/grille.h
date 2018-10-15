/**
 * \file grille.h
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * Structure d’une grille de Game of Life.
 */
typedef struct 
{
	int nbl; /**< Nombre de lignes dans la grille. */
	int nbc; /**< Nombre de colonnes dans la grille. */
	int** cellules; /**< Pointeurs vers les segments de mémoire contenant les cellules. */
} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

/**
 * Rend une cellule d’une grille vivante.
 *
 * @param i Coordonnée sur l’axe des abscisses.
 * @param j Coordonnée sur l’axe des ordonnées.
 * @param g Une grille (pas un pointeur vers une grille)
 */
static inline void set_vivante(int i, int j, grille g)
{
	g.cellules[i][j] = 1;
}


/**
 * Rend une cellule d’une grille morte.
 *
 * @see set_vivante
 */
static inline void set_morte(int i, int j, grille g)
{
	g.cellules[i][j] = 0;
}

static inline void set_nonViable (int i, int j, grille g)
{
	g.cellules[i][j] = -1;
}

/**
 * Retourne un booléan représentant l’état d’une cellule sur une grille.
 *
 * La valeur retournée est non-nulle si la cellule est vivante, et nulle si 
 *  morte
 *
 * @see set_vivante
 */
static inline int est_vivante(int i, int j, grille g)
{
	return g.cellules[i][j] >= 1;
}

static inline int est_nonViable (int i, int j, grille g)
{
	return g.cellules[i][j] < 0;
}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
