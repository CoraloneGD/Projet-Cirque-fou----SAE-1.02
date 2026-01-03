#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "animal.h"
#include "config.h"
#include "plateau.h"
#include "joueur.h"

#pragma warning(disable: 4996 6011)

#define NB_ANIMAUX 3
#define TOTAL_CARTES 24

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));

    // 1. On vérifie s'il y a assez de joueurs en paramètres
    if (argc < 3) {
        printf("Usage : %s Nom1 Nom2 [Nom3...]\n", argv[0]);
        return 1;
    }

    // 2. On remplit la liste des joueurs avec les arguments argv
    ListeJoueurs liste = { NULL, 0 };
    for (int i = 1; i < argc; i++) {
        ajouterJoueur(&liste, argv[i]);
    }

    // 3. Lecture du fichier de config
    Config maConfig;
    if (lectureFichier(&maConfig) != 0) return 1;

    // Affichage de la légende comme sur l'image
    printf("KI (B -> R) | LO (B <- R) | SO (B <-> R) | NI (B ^) | MA (R ^)\n");
    Config config;

    // Appel de la fonction
    if (lectureFichier(&config) != 0) {
        return 1; // Arrêt si fichier absent
    }

    // 3. Génération des 24 cartes (Heap + Shuffle)
    int total_cartes = TOTAL_CARTES;
    Plateau* pioche = (Plateau*)malloc(total_cartes * sizeof(Plateau));
    int index_heap = 0;
    permHeap(config.nb_animaux, config.noms_animaux, config.nb_animaux, pioche, &index_heap);
    melangeFisherYates(pioche, total_cartes);

    // 4. Initialisation du plateau actuel (Position de départ)
    Plateau actuel;
    copiePlateau(pioche[rand(0, TOTAL_CARTES)], &actuel);

    // 5. Boucle de jeu
    int carte_index = 1; // La carte 0 est le départ, la carte 1 est le premier objectif
    while (carte_index < total_cartes) {
        Plateau objectif = pioche[carte_index];

        printf("--- TOUR %d ---\n", carte_index);
        afficher_jeu(actuel, objectif);

        // Ici viendra la logique de saisie "NOM SEQUENCE"
        // et l'utilisation de copier_plateau pour tester la solution.

        carte_index++;
        // Si un joueur gagne : actuel = brouillon; (après avoir libéré l'ancien actuel)
    }

    // 6. Fin de partie
    // trierJoueurs(&liste);
    // afficherScores(liste);

    return 0;
}