//CONSULTER CE FICHIER POUR LA DOCUMENTATION DE DOXYGEN

/**
 * \file [tri.h]
 * fichier de tri a bulle
 */

#ifndef DEF_TRI
#define DEF_TRI
#include <stdio.h>
#include "tableau.h"

extern tableau t ;

/**
 * \fn void bulle (int k);
 * fait remonter une bulle jusqu'à la case k
 */
void bulle (int k) ;

/**
 * \fn void trier ();
 * tri (décroissant) du tableau t par la méthode du tri à bulle 
 */
void trier ();

#endif
