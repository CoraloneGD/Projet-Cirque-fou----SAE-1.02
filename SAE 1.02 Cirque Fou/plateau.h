#pragma once
#include "animal.h"

typedef struct {
	Podium bleu; ///< Podium bleu
	Podium rouge; ///< Podium rouge
} Plateau;

/*
* @brief applique un ordre sur le plateau
* @param p Pointeur vers le plateau
* @param ordre Ordre à appliquer
*/
void appliquerOrdre(Plateau* p, const char* ordre);

/*
* @brief vérifie si deux plateaux sont égaux
* @param p1 Pointeur vers le premier plateau
* @param p2 Pointeur vers le second plateau
* @return 1 (vrai) si les plateaux sont égaux, 0 (faux) sinon
*/
int estEgal(Plateau* p1, Plateau* p2);

/*
* @brief génère toutes les permutations des animaux et crée les répartitions possibles
* @param n Nombre d'animaux à permuter
* @param noms Tableau des noms des animaux
* @param nb_total_animaux Nombre total d'animaux
* @param cartes Tableau des plateaux pour stocker les répartitions
* @param index Pointeur vers l'index actuel dans le tableau des cartes
*/
void permHeap(int n, char** noms, int nb_total_animaux, Plateau* cartes, int* index);

/*
* @brief mélange les cartes du plateau en utilisant l'algorithme de Fisher-Yates
* @param tableau_cartes Pointeur vers le tableau des cartes
* @param nombre_de_cartes Nombre de cartes dans le tableau
*/
void melangeFisherYates(Plateau* tableau_cartes, int nbCartes);

/*
* @brief copie un podium d'une source à une destination
* @param source Podium source
* @param destination Pointeur vers le podium destination
*/
void copiePodium(Podium source, Podium* destination);

/*
* @brief copie un plateau d'une source à une destination
* @param source Plateau source
* @param destination Pointeur vers le plateau destination
*/
void copiePlateau(Plateau source, Plateau* destination);

/*
* @brief affiche l'état actuel et l'objectif du jeu
* @param actuel Plateau actuel
* @param objectif Plateau objectif
*/
void afficher_jeu(Plateau actuel, Plateau objectif);
