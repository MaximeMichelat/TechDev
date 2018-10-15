#ifndef DEF_ALEA
#define DEF_ALEA
#include <stdlib.h>
#include <time.h>
#include "tableau.h"

extern tableau t ;

// tire un entier aléatoire entre 0 et m
int alea (int m);

// remplit t avec des valeurs aléatoires
void remplir (int m);

#endif
