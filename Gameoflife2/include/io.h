/**
 * \file io.h
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"

#define SIZEX 1000
#define SIZEY 1000
#define ESPACE 10
#define TAILLECEL 50

// affichage d'une grille
void affiche_grille (grille g, cairo_surface_t* cs);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
