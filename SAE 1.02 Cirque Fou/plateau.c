#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plateau.h"
#include "config.h"

void appliquerOrdre(Plateau* p, const char* ordre) {
    if (strcmp(ordre, "KI") == 0) {
        KI_LO(&p->bleu.sommet, &p->rouge.sommet);
        p->bleu.taille--;
        p->rouge.taille++;
    }
    else if (strcmp(ordre, "LO") == 0) {
        KI_LO(&p->rouge.sommet, &p->bleu.sommet);
        p->rouge.taille--;
        p->bleu.taille++;
    }
    else if (strcmp(ordre, "SO") == 0) {
        SO(&p->bleu.sommet, &p->rouge.sommet);
    }
    else if (strcmp(ordre, "NI") == 0) {
        NI_MA(&p->bleu.sommet);
    }
    else if (strcmp(ordre, "MA") == 0) {
        NI_MA(&p->rouge.sommet);
    }
}

int estEgal(Plateau* p1, Plateau* p2) {
    if (p1->bleu.taille != p2->bleu.taille || p1->rouge.taille != p2->rouge.taille) {
        return 0;
    }
    Maillon* m1 = p1->bleu.sommet;
    Maillon* m2 = p2->bleu.sommet;
    while (m1 != NULL && m2 != NULL) {
        if (strcmp(m1->nomAnimal, m2->nomAnimal) != 0) {
            return 0;
        }
        m1 = m1->suivant;
        m2 = m2->suivant;
    }
    m1 = p1->rouge.sommet;
    m2 = p2->rouge.sommet;
    while (m1 != NULL && m2 != NULL) {
        if (strcmp(m1->nomAnimal, m2->nomAnimal) != 0) {
            return 0;
        }
        m1 = m1->suivant;
        m2 = m2->suivant;
    }
    return 1;
}

void permHeap(int n, char** noms, int nb_total_animaux, Plateau* cartes, int* index) {
    if (n == 1) {
        // Pour chaque permutation, on génère (nb_total_animaux + 1) répartitions
        for (int nb_bleu = 0; nb_bleu <= nb_total_animaux; nb_bleu++) {
            int nb_rouge = nb_total_animaux - nb_bleu;

            // Initialisation de la carte
            cartes[*index].bleu.sommet = NULL;
            cartes[*index].bleu.taille = 0; // Sera mis à jour par empiler
            cartes[*index].rouge.sommet = NULL;
            cartes[*index].rouge.taille = 0;

            // Remplissage dynamique des podiums
            for (int i = 0; i < nb_bleu; i++) {
                empiler(&(cartes[*index].bleu.sommet), noms[i]);
                cartes[*index].bleu.taille++;
            }
            for (int i = 0; i < nb_rouge; i++) {
                empiler(&(cartes[*index].rouge.sommet), noms[nb_bleu + i]);
                cartes[*index].rouge.taille++;
            }
            (*index)++;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        permHeap(n - 1, noms, nb_total_animaux, cartes, index);

        // Échange standard de Heap
        char* temp = noms[n - 1];
        if (n % 2 == 0) {
            noms[n - 1] = noms[i];
            noms[i] = temp;
        }
        else {
            noms[n - 1] = noms[0];
            noms[0] = temp;
        }
    }
}

void melangeFisherYates(Plateau* tableau_cartes, int nbCartes) {
    // On parcourt le tableau de l'indice n-1 jusqu'à 1
    for (int i = nbCartes - 1; i > 0; i--) {
        // On choisit un indice j au hasard entre 0 et i
        int j = rand() % (i + 1);

        // On échange les structures Plateau complètes à l'indice i et j
        // Cela échange les sommets et les tailles des deux podiums d'un coup
        Plateau temp = tableau_cartes[i];
        tableau_cartes[i] = tableau_cartes[j];
        tableau_cartes[j] = temp;
    }
}

void copiePodium(Podium source, Podium* destination) {
    destination->sommet = NULL;
    destination->taille = 0;

    if (source.sommet == NULL) 
        return;

    char* noms_temp[10];
    int i = 0;
    Maillon* courant = source.sommet;

    while (courant != NULL) {
        noms_temp[i++] = courant->nomAnimal;
        courant = courant->suivant;
    }

    for (int j = i - 1; j >= 0; j--) {
        empiler(&(destination->sommet), noms_temp[j]);
        destination->taille++;
    }
}

void copiePlateau(Plateau source, Plateau* destination) {
    copiePodium(source.bleu, &(destination->bleu));
    copiePodium(source.rouge, &(destination->rouge));
}

void afficher_jeu(Plateau actuel, Plateau objectif) {
    int h_max = 3; // Le sujet limite à 3 animaux
    char* noms_actuel_B[3] = { "", "", "" };
    char* noms_actuel_R[3] = { "", "", "" };
    char* noms_obj_B[3] = { "", "", "" };
    char* noms_obj_R[3] = { "", "", "" };

    // Remplissage des tableaux temporaires pour un accès direct par étage
    Maillon* c = actuel.bleu.sommet;
    for (int i = actuel.bleu.taille - 1; i >= 0; i--) { noms_actuel_B[i] = c->nomAnimal; c = c->suivant; }
    c = actuel.rouge.sommet;
    for (int i = actuel.rouge.taille - 1; i >= 0; i--) { noms_actuel_R[i] = c->nomAnimal; c = c->suivant; }
    c = objectif.bleu.sommet;
    for (int i = objectif.bleu.taille - 1; i >= 0; i--) { noms_obj_B[i] = c->nomAnimal; c = c->suivant; }
    c = objectif.rouge.sommet;
    for (int i = objectif.rouge.taille - 1; i >= 0; i--) { noms_obj_R[i] = c->nomAnimal; c = c->suivant; }

    // Affichage ligne par ligne (du haut vers le bas)
    for (int i = h_max - 1; i >= 0; i--) {
        printf("%-10s %-10s", noms_actuel_B[i], noms_actuel_R[i]);
        if (i == 1) printf("  ==>   "); else printf("        ");
        printf("%-10s %-10s\n", noms_obj_B[i], noms_obj_R[i]);
    }

    // Affichage des socles
    printf("---------- ----------        ---------- ----------\n");
    printf("   BLEU      ROUGE              BLEU      ROUGE   \n\n");
}