#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

int lectureFichier(Config* config) {
    FILE* fichier = fopen("crazy.cfg", "r");
    if (!fichier) {
        printf("Erreur : Impossible d'ouvrir crazy.cfg\n");
        return 1;
    }

    char ligne[100];
    config->nb_animaux = 0;

    // 1. Lire la première ligne (Nombre d'ordres)
    if (fgets(ligne, sizeof(ligne), fichier)) {
        config->nb_ordres = atoi(ligne);
    }

    // 2. Lire les lignes suivantes (Les noms des animaux)
    while (fgets(ligne, sizeof(ligne), fichier) && config->nb_animaux < 10) {
        ligne[strcspn(ligne, "\r\n")] = '\0'; // Nettoyer le saut de ligne

        if (strlen(ligne) > 0) {
            // On alloue de la mémoire pour chaque nom
            config->noms_animaux[config->nb_animaux] = _strdup(ligne);
            config->nb_animaux++;
        }
    }

    fclose(fichier);
    return 0;
}
