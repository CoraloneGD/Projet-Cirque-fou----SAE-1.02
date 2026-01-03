#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joueur.h"

#pragma warning(disable:4996)

void ajouterJoueur(ListeJoueurs* liste, const char* nom) {
    Joueur* temp = (Joueur*)realloc(liste->joueurs, (liste->nombre_joueurs + 1) * sizeof(Joueur));

    if (temp != NULL) {
        liste->joueurs = temp;
        strcpy(liste->joueurs[liste->nombre_joueurs].nom, nom);
        liste->joueurs[liste->nombre_joueurs].score = 0;
        liste->joueurs[liste->nombre_joueurs].peut_jouer = 1;
        liste->nombre_joueurs++;
    }
}

void libererListeJoueurs(ListeJoueurs* liste) {
	free(liste->joueurs);
	liste->joueurs = NULL;
	liste->nombre_joueurs = 0;
}