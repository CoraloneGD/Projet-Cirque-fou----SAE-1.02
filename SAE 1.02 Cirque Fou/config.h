#pragma once

typedef struct {
    int nb_ordres;          // Pour stocker le nombre d'ordres requis (ex: 4)
    char* noms_animaux[10]; // Tableau de pointeurs pour les noms (ex: "LION", "OURS")
    int nb_animaux;         // Compteur d'animaux trouvés
} Config;

/*
* @brief lit le fichier crazy.cfg et remplit la structure Config
* @param config Pointeur vers la structure Config à remplir
* @return 0 en cas de succès, 1 en cas d'erreur
*/
int lectureFichier(Config* config);