#ifndef FONCTION_NANA_H
#define FONCTION_NANA_H


typedef struct Jetons_na{ 
    int x; 
    int y; 
} Jetons_na; 


void obtenir_taille_terminal_na(int *lignes, int *colonnes);
float calculer_echelle_na(void);
void definir_caracteres_na(void);
void dessiner_forme_na();
void emettre_son_na(int frequence, int duree) ;
void adapter_affichage_na();
void lancer_de_6_na(void) ;
void jouer_na();
void sous_menu_na();
void chargement_na() ;
void menu_na();





#endif