#pragma once

typedef struct {
	char nomAnimal[20]; // Nom de l'animal
	struct Maillon* suivant; // Pointeur vers le maillon suivant
} Maillon;

typedef struct {
	Maillon* sommet; // Pointeur vers le sommet de la pile
	int taille;      // Nombre d'animaux sur le podium
} Podium;

/*
* @brief empile un animal sur le podium
* @param sommet Pointeur vers le sommet de la pile
* @param animal Nom de l'animal à empiler
*/
void empiler(Maillon** sommet, const char* animal);

/*
* @brief dépile l'animal au sommet du podium
* @param sommet Pointeur vers le sommet de la pile
*/
void depiler(Maillon** sommet);

/*
* @brief extrait le maillon au sommet du podium sans le supprimer
* @param sommet Pointeur vers le sommet de la pile
*/
Maillon* extrMaillon(Maillon** sommet);

/*
* @brief repose un maillon extrait au sommet du podium
* @param sommet Pointeur vers le sommet de la pile
* @param m Pointeur vers le maillon à reposer
*/
void poserMaillon(Maillon** sommet, Maillon* m);

/*
* @brief déplace un animal d'un sommet d'un podium à un autre (UTILE POUR KI-LO)
* @param source Pointeur vers le podium source
* @param destination Pointeur vers le podium destination
*/
void KI_LO(Maillon** source, Maillon** destination);

/*
* @brief échange les animaux au sommet de deux podiums (UTILE POUR SO)
* @param bleu Pointeur vers le podium bleu
* @param rouge Pointeur vers le podium rouge
*/
void SO(Maillon** bleu, Maillon** rouge);

/*
* @brief déplace l'animal au bas du podium vers le sommet (UTILE POUR NI-MA)
* @param sommet Pointeur vers le sommet de la pile
*/
void NI_MA(Maillon** sommet);

