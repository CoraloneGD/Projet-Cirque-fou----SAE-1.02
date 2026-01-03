#pragma once

typedef struct {
	char nom[256]; ///< Nom du joueur
	int score; ///< Score du joueur
	int peut_jouer; ///< Indicateur si le joueur peut jouer (1 = oui, 0 = non)
} Joueur;

typedef struct {
	Joueur* joueurs; ///< Tableau dynamique de joueurs
	int nombre_joueurs; ///< Nombre de joueurs dans le tableau
} ListeJoueurs;


/*
* @brief ajoute un joueur à la liste des joueurs
* @param liste Pointeur vers la liste des joueurs
* @param nom Nom du joueur à ajouter
*/
void ajouterJoueur(ListeJoueurs* liste, const char* nom);

/*
* @brief libère la mémoire allouée pour la liste des joueurs
* @param liste Pointeur vers la liste des joueurs
*/
void libererListeJoueurs(ListeJoueurs* liste);