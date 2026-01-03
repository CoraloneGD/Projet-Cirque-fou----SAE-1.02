#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "animal.h"

#pragma warning(disable:4996)

void empiler(Maillon** sommet, const char* animal) {
    Maillon* nouveau = (Maillon*)malloc(sizeof(Maillon));
    if (nouveau != NULL) {
        strcpy(nouveau->nomAnimal, animal);
        nouveau->suivant = *sommet;
        *sommet = nouveau;
    }
}

void depiler(Maillon** sommet) {
    if (*sommet != NULL) {
        Maillon* temp = *sommet;
        *sommet = (*sommet)->suivant;
        free(temp);
    }
}

Maillon* extrMaillon(Maillon** sommet) {
    if (*sommet == NULL) return NULL;
    Maillon* extrait = *sommet;
    *sommet = (*sommet)->suivant;
    extrait->suivant = NULL;
    return extrait;
}

void poserMaillon(Maillon** sommet, Maillon* m) {
    if (m == NULL) return;
    m->suivant = *sommet;
    *sommet = m;
}

void KI_LO(Maillon** source, Maillon** destination) {
    Maillon* animal = extrMaillon(source);
    if (animal != NULL) {
        poserMaillon(&destination, animal);
    }
}

void SO(Maillon** bleu, Maillon** rouge) {
    if (*bleu == NULL || *rouge == NULL) return;

    Maillon* animalBleu = extrMaillon(bleu);
    Maillon* animalRouge = extrMaillon(rouge);

    poserMaillon(bleu, animalRouge);
    poserMaillon(rouge, animalBleu);
}

void NI_MA(Maillon** sommet) {
    if (*sommet == NULL || (*sommet)->suivant == NULL) {
        return;
    }

    Maillon* courant = *sommet;
    Maillon* precedent = NULL;

    while (courant->suivant != NULL) {
        precedent = courant;
        courant = courant->suivant;
    }

    precedent->suivant = NULL;
    poserMaillon(sommet, courant);
}