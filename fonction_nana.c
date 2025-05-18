#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <time.h>
#include <stdbool.h>
#include"fonction_nana.h"
//#define  LARGEUR_PLATEAU 80
//#define HAUTEUR_PLATEAU 40
#define HAUTEUR_MIN_na 42  // Réduit de 45 à 42
#define LARGEUR_MIN_na 60
Jetons_na jetons_na[4][4]; 
Jetons_na des[4];
Jetons_na jetons_na_temp[4][4]; 
bool drapeau_na = false; bool son_na = true; 
char noms_na[4][25] ={"Joueur1","Joueur2","Joueur3","Joueur4"}; 
char caracteres[4] = {254, 232, 234, 224}; 
char valeurs_jetons_na[4] = {254, 232, 234, 224};
int nb_joueurs_na; int valeur_de_na; 
int tour_joueur_na = 0; 
int temp_de_na; 
int jetons_na_a_deplacer_na; 
int frequence_na = 200; 
int fin_j1_y_na = 26; int fin_j2_x_na = 25; int fin_j3_x_na = 25; int fin_j4_y_na = 22; 
int gagnants_na[4] = {0};



void obtenir_taille_terminal_na(int *lignes_na, int *colonne_nas_na) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *lignes_na = w.ws_row;
    *colonne_nas_na = w.ws_col;
}



void deplacer_curseur_na(int x, int y) {
    int lignes_na, colonne_nas_na;
    obtenir_taille_terminal_na(&lignes_na, &colonne_nas_na);
    int offset_x_na = (colonne_nas_na - LARGEUR_MIN_na) / 2;
    int offset_y_na = (lignes_na - HAUTEUR_MIN_na) / 2;
    x = (x + offset_x_na < colonne_nas_na) ? x + offset_x_na : colonne_nas_na - 1;
    y = (y + offset_y_na < lignes_na) ? y + offset_y_na : lignes_na - 1;
    printf("\033[%d;%dH", y + 1, x + 1);
}
float calculer_echelle_na(void) {
    int lignes_na, colonne_nas_na;
    obtenir_taille_terminal_na(&lignes_na, &colonne_nas_na);
    const int MIN_LIGNES_na = 45;
    const int MIN_COLONNE_naS_na = 80;
    float echelle_lignes_na = (float)lignes_na / MIN_LIGNES_na;
    float echelle_colonne_nas_na = (float)colonne_nas_na / MIN_COLONNE_naS_na;
    return (echelle_lignes_na < echelle_colonne_nas_na) ? echelle_lignes_na : echelle_colonne_nas_na;
}
void definir_caracteres_na(void) {
    const char* ROUGE_na = "\033[31m";
    const char* VERT_na = "\033[32m";
    const char* JAUNE_na = "\033[33m";
    const char* BLEU_na = "\033[34m";
    const char* RESET_na = "\033[0m";
    const char* couleurs_joueurs_na[4] = {ROUGE_na, VERT_na, BLEU_na, JAUNE_na};
    int caracteres_ascii_na[3][4] ;
    caracteres_ascii_na[0][0] = 254;
    caracteres_ascii_na[0][1] = 232;
    caracteres_ascii_na[0][2] = 234;
    caracteres_ascii_na[0][3] = 224;
    caracteres_ascii_na[1][0] = 248;
    caracteres_ascii_na[1][1] = 235;
    caracteres_ascii_na[1][2] = 237;
    caracteres_ascii_na[1][3] = 225;
    caracteres_ascii_na[2][0] = 236;
    caracteres_ascii_na[2][1] = 231;
    caracteres_ascii_na[2][2] = 227;
    caracteres_ascii_na[2][3] = 233;

    int position_x_na = 10;
    int position_y_na = 14;
    char touche_na;
    int compteur_na = 1;

    do {
        do {
            deplacer_curseur_na(10, 13);
            printf("%sAppuyez sur [v] %s%s",couleurs_joueurs_na[compteur_na-1], noms_na[compteur_na-1], RESET_na);
    
            printf("\n\n");
            
            for(int x = 10; x <= 26; x++) {
                deplacer_curseur_na(x, 15);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
                deplacer_curseur_na(x, 16);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
                deplacer_curseur_na(x, 18);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
            }
            for(int y = 14; y <= 18; y++) {
                deplacer_curseur_na(10, y);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
                deplacer_curseur_na(14, y);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
                deplacer_curseur_na(18, y);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
                deplacer_curseur_na(22, y);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
                deplacer_curseur_na(26, y);
                printf("%s%c%s", couleurs_joueurs_na[compteur_na-1], 178, RESET_na);
            }

            int decalage_y_na = 15;
            for(int y = 0; y < 2; y++) {
                int decalage_x_na = 12;
                for(int x = 0; x < 4; x++) 
                {     
                    deplacer_curseur_na(x+decalage_x_na,y+decalage_y_na);
                    printf("%s%c%s", couleurs_joueurs_na[compteur_na-1],caracteres_ascii_na[y][x], RESET_na);
                    decalage_x_na += 3;
                }
                decalage_y_na += 1;
            }
            deplacer_curseur_na(position_x_na, position_y_na + 1);
            printf("%s|%s", couleurs_joueurs_na[compteur_na-1], RESET_na);
            deplacer_curseur_na(position_x_na + 4, position_y_na + 1);
            printf("%s|%s", couleurs_joueurs_na[compteur_na-1], RESET_na);
            deplacer_curseur_na(position_x_na + 1, position_y_na);
            printf("%s___%s", couleurs_joueurs_na[compteur_na-1], RESET_na);
            touche_na = getchar();
            system("clear");

            if(touche_na == 'h' || touche_na == 'H') {  
                if(position_y_na - 2 > 13)
                    position_y_na -= 2;
            }
            else if(touche_na == 'g' || touche_na == 'G') {  
                if(position_x_na - 4 >= 10)
                    position_x_na -= 4;
            }
            else if(touche_na == 'd' || touche_na == 'D') {  
                if(position_x_na + 4 < 26)
                    position_x_na += 4;
            }
            else if(touche_na == 'b' || touche_na == 'B') {  
                if(position_y_na + 2 < 18)
                    position_y_na += 2;
            }
            else if(touche_na == 'v' || touche_na == 'V') {  
                int y;
                if(position_y_na == 14) {
                    valeurs_jetons_na[compteur_na-1] = caracteres_ascii_na[0][(position_x_na - 10)/4];
                    for(int x = 0; x < 3; x++) {
                        for(y = (position_x_na - 10)/4; y < 4; y++) {
                            caracteres_ascii_na[x][y] = caracteres_ascii_na[x][y+1];
                        }
                        caracteres_ascii_na[x][y-1] = caracteres_ascii_na[x+1][0];
                    }
                }
                else {
                    valeurs_jetons_na[compteur_na-1] = caracteres_ascii_na[1][(position_x_na - 10)/4];
                    for(int x = 1; x < 3; x++) {
                        for(y = (position_x_na - 10)/4; y < 4; y++) {
                            caracteres_ascii_na[x][y] = caracteres_ascii_na[x][y+1];
                        }
                        caracteres_ascii_na[x][y-1] = caracteres_ascii_na[x+1][0];
                    }
                }
                compteur_na++;
            }
        } while(touche_na != 'v' && touche_na != 'V');
    } while(compteur_na <= nb_joueurs_na);
}


//bool verification_rotation = false;

void dessiner_forme_na(){
    const int DECALAGE_Y_na = -7;
    int lignes_na, colonne_nas_na;
    obtenir_taille_terminal_na(&lignes_na, &colonne_nas_na);
    
    if (lignes_na < 24 || colonne_nas_na < 80) {
        printf("Terminal trop petit ! Minimum requis : 80x24\n");
        return;
    }

for(int i = 6; i <= 43; i++) {
    deplacer_curseur_na(5, (4+i)+DECALAGE_Y_na);
    printf("%c", 178);
}

for(int i = 2; i <= 43; i++) {
    deplacer_curseur_na(23,(4+i)+DECALAGE_Y_na);
    printf("%c", 178);
}

for(int i = 6; i <= 43; i++) {
    deplacer_curseur_na(32, (4+i)+DECALAGE_Y_na);
    printf("%c", 178);
}

for(int i = 6; i <= 43; i++) {
    deplacer_curseur_na(50, (4+i)+DECALAGE_Y_na);
    printf("%c", 178);
}

deplacer_curseur_na(5, 10+DECALAGE_Y_na);
for(int i = 0; i <= 45; i++)
    printf("%c", 178);

deplacer_curseur_na(5, 23+DECALAGE_Y_na);
for(int i = 0; i <= 45; i++)
    printf("%c", 178);

deplacer_curseur_na(5, 32+DECALAGE_Y_na); 
for(int i = 0; i <= 45; i++)
    printf("%c", 178);


for(int i = 10; i <= 23; i++) {
    deplacer_curseur_na(26, i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(29, i+DECALAGE_Y_na);
    printf("%c", 178);
}

for(int i = 32; i <= 43; i++) {
    deplacer_curseur_na(26, i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(29, i+DECALAGE_Y_na);
    printf("%c", 178);
}

for(int i = 10; i <= 23; i += 2) {
    for(int j = 23; j <= 32; j++) {
        deplacer_curseur_na(j, i+DECALAGE_Y_na);
        printf("%c", 178);
    }
}

for(int i = 32; i <= 43; i += 2) {
    for(int j = 23; j <= 32; j++) {
        deplacer_curseur_na(j, i+DECALAGE_Y_na);
        printf("%c", 178);
    }
}


deplacer_curseur_na(5, 44+DECALAGE_Y_na);
for(int i = 1; i <= 46; i++)
    printf("%c", 178);

for(int i = 1; i <= 45; i++) {
    deplacer_curseur_na(4+i, 26+DECALAGE_Y_na);
    if(i <= 19 || i >= 29)
        printf("%c", 178);
    deplacer_curseur_na(4+i, 29+DECALAGE_Y_na);
    if(i <= 19 || i >= 29)
        printf("%c", 178);
}
for(int i = 23; i <= 32; i++)       
{
    deplacer_curseur_na(8,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(11,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(14,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(17,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(20,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(23,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(32,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(35,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(38,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(41,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(44,i+DECALAGE_Y_na);
    printf("%c", 178);
    deplacer_curseur_na(47,i+DECALAGE_Y_na);
    printf("%c", 178);
}


deplacer_curseur_na(9,24+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(9,25+DECALAGE_Y_na);
printf("%c%c", 43, 43+DECALAGE_Y_na);
deplacer_curseur_na(30,13+DECALAGE_Y_na);
printf("%c%c", 43, 43+DECALAGE_Y_na);
deplacer_curseur_na(24,15+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(42,24+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(42,25+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(45,30+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(45,31+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(12,30+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(12,31+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(24,41+DECALAGE_Y_na);
printf("%c%c", 43, 43);
deplacer_curseur_na(30,39+DECALAGE_Y_na);
printf("%c%c", 43, 43);

for(int i = 13; i <= 22; i += 2)
{
    deplacer_curseur_na(27,i+DECALAGE_Y_na);
    printf("%c%c", 43, 43);
}


for(int i = 33; i <= 42; i += 2)
{
    deplacer_curseur_na(27,i+DECALAGE_Y_na);
    printf("%c%c", 43, 43);
}

for(int i = 9; i <= 22; i += 3)
{
    deplacer_curseur_na(i,27+DECALAGE_Y_na);
    printf("%c%c", 43, 43);
    deplacer_curseur_na(i,28+DECALAGE_Y_na);
    printf("%c%c", 43, 43);
}

for(int i = 33; i <= 47; i += 3)
{
    deplacer_curseur_na(i,27+DECALAGE_Y_na);
    printf("%c%c", 43, 43);
    deplacer_curseur_na(i,28+DECALAGE_Y_na);
    printf("%c%c", 43, 43);
}

if(gagnants_na[0] == 3)
{
    deplacer_curseur_na(10,15);
    printf("Gagnant");
}
if(gagnants_na[1] == 3)
{
    deplacer_curseur_na(35,15);
    printf("Gagnant");
}
if(gagnants_na[2] == 3)
{
    deplacer_curseur_na(10,39);
    printf("Gagnant");
}
if(gagnants_na[3] == 3)
{
    deplacer_curseur_na(35,39);
    printf("Gagnant");
}

deplacer_curseur_na(6,6);
printf("%c%c%c", 178, 178, 178);
deplacer_curseur_na(8,5);
printf("%c", 178);
deplacer_curseur_na(47,6);
printf("%c%c%c", 178, 178, 178);
deplacer_curseur_na(47,5);
printf("%c", 178);
deplacer_curseur_na(6,42+DECALAGE_Y_na);
printf("%c%c%c", 178, 178, 178);
deplacer_curseur_na(8,43+DECALAGE_Y_na);
printf("%c", 178);
deplacer_curseur_na(47,42+DECALAGE_Y_na);
printf("%c%c%c", 178, 178, 178);
deplacer_curseur_na(47,43+DECALAGE_Y_na);
printf("%c", 178+DECALAGE_Y_na);


{
    for(int y = 0; y < nb_joueurs_na; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            deplacer_curseur_na(jetons_na[y][x].x, jetons_na[y][x].y+DECALAGE_Y_na);
            printf("\033[1;3%dm%c\033[0m", y+1, valeurs_jetons_na[y]);
        }
    }
}

{
    int temp = 0;
    deplacer_curseur_na(des[tour_joueur_na].x, des[tour_joueur_na].y+DECALAGE_Y_na);
    printf("%d", valeur_de_na);
}


{   
    deplacer_curseur_na(55,11+DECALAGE_Y_na);
    printf("Informations:");
    deplacer_curseur_na(55,12+DECALAGE_Y_na);
    printf("-------------");
    deplacer_curseur_na(55,13+DECALAGE_Y_na);
    printf("1)Nous créons un petit bloc_na  ");
    deplacer_curseur_na(55,14+DECALAGE_Y_na);
    printf("dans toutes les sections,"); 
    deplacer_curseur_na(55,15+DECALAGE_Y_na);
    printf("qui permet de faire tourner le dé.");
    deplacer_curseur_na(55,16+DECALAGE_Y_na);
    printf("2)Nous utilisons le signe '+'");
    deplacer_curseur_na(55,17+DECALAGE_Y_na);
    printf(" dans le jeu qui protège le joueur");
    deplacer_curseur_na(55,18+DECALAGE_Y_na);
    printf("des autres joueurs.");
    deplacer_curseur_na(55,19+DECALAGE_Y_na);
    printf("3)Nous créons le bloc_na autour du pion,");
    deplacer_curseur_na(55,20+DECALAGE_Y_na);
    printf("quand vous appuyez sur 'O',");
    deplacer_curseur_na(55,21+DECALAGE_Y_na);
    printf("le joueur se déplacera.");
    deplacer_curseur_na(55,22+DECALAGE_Y_na);
    printf("vous pouvez déplacer le bloc_na vers le ");
    deplacer_curseur_na(55,23+DECALAGE_Y_na);
    printf("joueur que vous souhaitez déplacer.");
    deplacer_curseur_na(55,24+DECALAGE_Y_na);
    printf("4)Vous pouvez choisir le caractère,");
    deplacer_curseur_na(58,25+DECALAGE_Y_na);
    printf("que vous voulez utiliser comme joueur");
    deplacer_curseur_na(55,26+DECALAGE_Y_na);
    printf("5)Vous pouvez changer le nom du joueur,");
    deplacer_curseur_na(58,27+DECALAGE_Y_na);
    printf(" comme changer 'Michel' en'Louis'etc");
    deplacer_curseur_na(55,28+DECALAGE_Y_na);
    printf("6)Nous donnons 50 points au gagnant");
    deplacer_curseur_na(55,29+DECALAGE_Y_na);
    printf("Contrôles:");
    deplacer_curseur_na(55,30+DECALAGE_Y_na);
    printf("----------");
    deplacer_curseur_na(55,31+DECALAGE_Y_na);
    printf("Utilisez les touche_nas suivantes:");
    deplacer_curseur_na(55,32+DECALAGE_Y_na);
    printf("Z - haut\tS - bas");
    deplacer_curseur_na(55,33+DECALAGE_Y_na);
    printf("Q - gauche\tD - droite");
    deplacer_curseur_na(55,34+DECALAGE_Y_na);
    printf("O - valider\tX - quitter");
    deplacer_curseur_na(55,35+DECALAGE_Y_na);
    printf("il est important de savoir que ");
    deplacer_curseur_na(55, 36+DECALAGE_Y_na);
    printf("la touche_na O est utilisée pour ");
    deplacer_curseur_na(55,37+DECALAGE_Y_na);
    printf("1)sélectionner le pion");
    deplacer_curseur_na(55,38+DECALAGE_Y_na);
    printf("2)faire tourner le dé");
    deplacer_curseur_na(55,39+DECALAGE_Y_na);
    printf("3)sélectionner le pion à déplacer");
}

{  
    if(nb_joueurs_na <= 2)
    {
        deplacer_curseur_na(6,9+DECALAGE_Y_na);
        printf("%s", noms_na[0]);     
        deplacer_curseur_na(41,9+DECALAGE_Y_na);
        printf("%s", noms_na[1]);     
    }
    if(nb_joueurs_na == 3)
    {
        deplacer_curseur_na(6,9+DECALAGE_Y_na);
        printf("%s", noms_na[0]);     
        deplacer_curseur_na(41,9+DECALAGE_Y_na);
        printf("%s", noms_na[1]);     
        deplacer_curseur_na(6,45+DECALAGE_Y_na);
        printf("%s", noms_na[2]);     
    }
    if(nb_joueurs_na == 4)
    {
        deplacer_curseur_na(6,9+DECALAGE_Y_na);
        printf("%s", noms_na[0]);     
        deplacer_curseur_na(41,9+DECALAGE_Y_na);
        printf("%s", noms_na[1]);     
        deplacer_curseur_na(6,45+DECALAGE_Y_na);
        printf("%s", noms_na[2]);     
        deplacer_curseur_na(41,45+DECALAGE_Y_na);
        printf("%s", noms_na[3]);     
    }
}
}
void emettre_son_na(int frequence_na, int duree) {
    printf("\a");  // Beep système
    fflush(stdout);
    usleep(duree * 1000);
}


void adapter_affichage_na() {
    int lignes_na, colonne_nas_na;
    obtenir_taille_terminal_na(&lignes_na, &colonne_nas_na);
    float scale_x_na = (float)colonne_nas_na / LARGEUR_MIN_na;  
    float scale_y_na = (float)lignes_na / HAUTEUR_MIN_na;    
    float scale = (scale_x_na < scale_y_na) ? scale_x_na : scale_y_na;
    
    if (scale < 1.0) {
        
        printf("\033[3J\033[H\033[2J"); 
        printf("Terminal trop petit! Taille minimum recommandée:%dx%d\n", LARGEUR_MIN_na, HAUTEUR_MIN_na);
        printf("Taille actuelle: %dx%d\n", colonne_nas_na, lignes_na);
        printf("\nRedimensionnement automatique...\n\n");
        
        printf("\033[?25l"); 
        printf("\033[%d;%df", (lignes_na-45)/2, (colonne_nas_na-60)/2);
    }
    dessiner_forme_na();    
    printf("\033[?25h"); 
}
void tuer_jetons_na(void) 
{   
    
    for(int ligne_na = 0; ligne_na < nb_joueurs_na; ligne_na++) 
    {
        if(ligne_na != tour_joueur_na) 
        {
            for(int colonne_na = 0; colonne_na < 4; colonne_na++) 
            {
                if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == jetons_na[ligne_na][colonne_na].y) && 
                    (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == jetons_na[ligne_na][colonne_na].x))
                {   
                    if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 10 && 
                        jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 24))
                    {
                        if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 24 && 
                            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 15))
                        {
                            if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 30 && 
                                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 13))
                            {
                                if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 42 && 
                                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 24))
                                {
                                    if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 45 && 
                                        jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 30))
                                    {
                                        if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 30 && 
                                            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 39))
                                        {
                                            if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 24 && 
                                                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 41))
                                            {
                                                if(!(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 12 && 
                                                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 30))
                                                {
                                                    /* Retourne le jetons_na capturé à sa position initiale */
                                                    jetons_na[ligne_na][colonne_na].x = jetons_na_temp[ligne_na][colonne_na].x;
                                                    jetons_na[ligne_na][colonne_na].y = jetons_na_temp[ligne_na][colonne_na].y;
                                                    emettre_son_na(frequence_na, 500);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void lancer_de_4_na(void)
{   
    //int de_resultat;
    //bool peut_sortir = false;
    
    /*for (int i = 0; i < 3; i++) {
        de_resultat = rand() % 6 + 1;
        printf("Tentative %d : résultat du dé = %d\n", i + 1, de_resultat);
        if (de_resultat == 4) {
            peut_sortir = true;
            break;
        }
    }*/
    /*if (peut_sortir) {
        printf("Le joueur %d peut sortir un pion !\n", tour_joueur_na);
*/
        if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 8 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 16) || 
            (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 14 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 16)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 10;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 24;
        } 
        else if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 8 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 18) || 
                 (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 14 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 18)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 10;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 24;
        } 
        else if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 41 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 16) || 
                 (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 47 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 16)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 30;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 13;
        } 
        else if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 41 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 18) || 
                 (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 47 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 18)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 30;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 13;
        } 
        else if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 8 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 35) || 
                 (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 14 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 35)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 24;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 41;
        } 
        else if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 8 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 39) || 
                 (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 14 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 39)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 24;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 41;
        } 
        else if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 41 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 35) || 
                 (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 47 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 35)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 45;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 30;
        } 
        else if ((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 41 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 39) || 
                 (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 47 && jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 39)) {
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 45;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 30;
        } 
        else {
            drapeau_na = true;
        }
    /*} /*else {
        printf("Le joueur %d n'a pas obtenu un 4 en 3 tentatives.\n", tour_joueur_na);
        drapeau_na = true;
    }*/
}

void deplacer_jetons_na(void) {
    if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 27 && 
        jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 21) {   
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 24;
        }

        if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 24 && 
        jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 22)    
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 24;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 21;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 21 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 30)    
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 33;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 24;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 30 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 33) 
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 30;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 33;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 33 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 24)    
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = 21;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 30;
        }

        else if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 24) && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x < 22)    
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x += 3;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 27 && 
            (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x >= 6 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x <= 21) && 
                tour_joueur_na == 0)   
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x += 3;
            temp_de_na--;
        }
        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 27 && 
        (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 10 && 
         jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 19) && 
         tour_joueur_na == 1)    
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y += 2;
                temp_de_na--;
            }

            else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 27 && 
                    (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 43 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 31) && 
                    tour_joueur_na == 2)    
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y -= 2;
                temp_de_na--;
            }

            else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 27 && 
                    (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x <= 48 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x >= 30) && 
                    tour_joueur_na == 3)   
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x -= 3;
                temp_de_na--;
            }

            else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 27 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 21)
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 24;
            }

            else if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 24 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 12) && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 24)
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y -= 2;
            }

            else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 12 && 
                    (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x >= 24 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x < 30))
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x += 3;
            }

            else if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 10 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 21) && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 30)
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y += 2;
            }

            else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 24 && 
                    (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x >= 33 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x < 47))
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x += 3;
            }

            else if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 24 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 28) && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 48)
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y += 3;
            }

            else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 30 && 
                    (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x <= 48 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x > 33))
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x -= 3;
            }
            else if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 41 && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 33) && 
                    jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 30)
            {
                if(son_na)
                    emettre_son_na(frequence_na, 250);
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y += 2;
            }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 43 && 
                (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x >= 26 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x <= 30))
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x -= 3;
        }

        else if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y <= 43 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 35) && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 24)
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y -= 2;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 30 && 
                (jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x >= 9 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x <= 21))
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x -= 3;
        }

        else if((jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x <= 30 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y >= 22) && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 6)
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y -= 3;
        }

      
        if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 24 && 
        jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 6)    
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = 24;
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x += 1;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 24 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 27)
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = fin_j1_y_na;
            fin_j1_y_na++;
            gagnants_na[0]++;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 27 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 24)
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = fin_j2_x_na;
            fin_j2_x_na++;
            gagnants_na[1]++;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 27 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 31)
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x = fin_j3_x_na;
            fin_j3_x_na++;
            gagnants_na[2]++;
        }

        else if(jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].x == 30 && 
                jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y == 27)
        {
            if(son_na)
                emettre_son_na(frequence_na, 250);
            jetons_na[tour_joueur_na][jetons_na_a_deplacer_na].y = fin_j4_y_na;
            fin_j4_y_na++;
            gagnants_na[3]++;
        }
} 

/*void jouer_na()
{
    char touche_na;
    int a = 0;

    do {
        system("clear"); 
        dessiner_forme_na();
        touche_na = getchar();
        
        if(touche_na == 'o' || touche_na == 'O') {
            valeur_de_na = rand() % 6 + 1; 
            
            do {
                system("clear");
                dessiner_forme_na();
                deplacer_curseur_na(jetons_na[tour_joueur_na][a].x - 1, jetons_na[tour_joueur_na][a].y);
                printf("|");
                deplacer_curseur_na(jetons_na[tour_joueur_na][a].x + 1, jetons_na[tour_joueur_na][a].y);
                printf("|");
                deplacer_curseur_na(jetons_na[tour_joueur_na][a].x, jetons_na[tour_joueur_na][a].y - 1);
                printf("_");
                
                touche_na = getchar();
                
                switch(touche_na) {
                    case 'w': 
                    case 'W':
                    case 'A':
                    case 'a':
                    case 'd':
                    case 'D':
                    case 's':
                    case 'S':
                        a++;
                        if(a > 3)
                            a = 0;
                        break;
                        
                    case 'O':
                    case 'o': 
                        jetons_na_a_deplacer_na = a;
                        if(valeur_de_na == 4) {
                            lancer_de_4_na();
                        }
                        system("clear");
                        dessiner_forme_na();
                        temp_de_na = valeur_de_na;
                        
                        if(drapeau_na || (valeur_de_na < 6)) {
                
                            for(int i = 1; i <= valeur_de_na; i++) {
                                deplacer_jetons_na();
                                system("clear");
                                dessiner_forme_na();

                                for(int j = 1; j <= 99999999; j++);
                            }
                            drapeau_na = 0;
                        }
                        tuer_jetons_na();
                    
                        
                        if(valeur_de_na != 4) 
                            tour_joueur_na++;
                            
                        if(tour_joueur_na > nb_joueurs_na - 1) 
                            tour_joueur_na = 0;
                        break;
                }
                
                jetons_na_a_deplacer_na = 0;
                
            } while((touche_na != 'o' && touche_na != 'O') && (touche_na != 'q' && touche_na != 'Q'));
        }
                
        
        system("clear");
        
    } while(touche_na != 'q' || touche_na != 'Q');
    if(touche_na == 'q' || touche_na == 'Q') {
        deplacer_curseur_na(10, 15);
        printf("Merci d'avoir joué ! J'espère que vous avez apprécié le jeu.");
    }
}: 
*/
void jouer_na()
{
    char touche_na;
    int a = 0;

    do {
        system("clear"); 
        dessiner_forme_na();
        touche_na = getchar();
        
        if(touche_na == 'o' || touche_na == 'O') {
        
            valeur_de_na = rand() % 6 + 1; 
            //touche_na = getchar();
            do {
                system("clear");
                dessiner_forme_na();
                deplacer_curseur_na(jetons_na[tour_joueur_na][a].x - 1, jetons_na[tour_joueur_na][a].y);
                printf("|");
                deplacer_curseur_na(jetons_na[tour_joueur_na][a].x + 1, jetons_na[tour_joueur_na][a].y);
                printf("|");
                deplacer_curseur_na(jetons_na[tour_joueur_na][a].x, jetons_na[tour_joueur_na][a].y - 1);
                printf("_");
                
                touche_na = getchar();
                
               
                
                switch(touche_na) {
                    case 'w': 
                    case 'W':
                    case 'A':
                    case 'a':
                    case 'd':
                    case 'D':
                    case 's':
                    case 'S':
                        a++;
                        if(a > 3)
                            a = 0;
                        break;
                        
                    case 'O':
                    case 'o': 
                        jetons_na_a_deplacer_na = a;
                        if(valeur_de_na == 4) {
                            lancer_de_4_na();
                        }
                        system("clear");
                        dessiner_forme_na();
                        temp_de_na = valeur_de_na;
                        
                        if(drapeau_na || (valeur_de_na < 6)) {
                
                            for(int i = 1; i <= valeur_de_na; i++) {
                                deplacer_jetons_na();
                                system("clear");
                                dessiner_forme_na();

                                for(int j = 1; j <= 99999999; j++);
                            }
                            drapeau_na = 0;
                        }
                        tuer_jetons_na();
                    
                        
                        if(valeur_de_na != 4) 
                            tour_joueur_na++;
                            
                        if(tour_joueur_na > nb_joueurs_na - 1) 
                            tour_joueur_na = 0;
                        break;
                }
                
                jetons_na_a_deplacer_na = 0;
                
            } while((touche_na != 'o' && touche_na != 'O') && (touche_na != 'q' && touche_na != 'Q'));
        }
                
        
        system("clear");
        
    } while(touche_na != 'q' || touche_na != 'Q');
    if(touche_na == 'q' || touche_na == 'Q') {
        deplacer_curseur_na(10, 15);
        printf("Merci d'avoir joué ! J'espère que vous avez apprécié le jeu.");
    }
}

void sous_menu_na()
{
    system("clear"); /* Pour Ubuntu */
    
    /* Assigner les positions des jetons_na pour joueur 1 */
    {
        jetons_na[0][0].x = 8;
        jetons_na[0][0].y = 16;
        jetons_na[0][1].x = 14;
        jetons_na[0][1].y = 16;
        jetons_na[0][2].x = 8;
        jetons_na[0][2].y = 18;
        jetons_na[0][3].x = 14;
        jetons_na[0][3].y = 18;
    }
    
    /* Assigner les positions des jetons_na pour joueur 2 */
    {
        jetons_na[1][0].x = 41;
        jetons_na[1][0].y = 16;
        jetons_na[1][1].x = 47;
        jetons_na[1][1].y = 16;
        jetons_na[1][2].x = 41;
        jetons_na[1][2].y = 18;
        jetons_na[1][3].x = 47;
        jetons_na[1][3].y = 18;
    }
    
    /* Assigner les positions des jetons_na pour joueur 3 */
    {
        jetons_na[2][0].x = 8;
        jetons_na[2][0].y = 35;
        jetons_na[2][1].x = 14;
        jetons_na[2][1].y = 35;
        jetons_na[2][2].x = 8;
        jetons_na[2][2].y = 39;
        jetons_na[2][3].x = 14;
        jetons_na[2][3].y = 39;
    }
    
    /* Assigner les positions des jetons_na pour joueur 4 */
    {
        jetons_na[3][0].x = 41;
        jetons_na[3][0].y = 35;
        jetons_na[3][1].x = 47;
        jetons_na[3][1].y = 35;
        jetons_na[3][2].x = 41;
        jetons_na[3][2].y = 39;
        jetons_na[3][3].x = 47;
        jetons_na[3][3].y = 39;
    }
    
    /* Copier les positions dans jetons_na_temp */
    for(int ligne = 0; ligne < 4; ligne++) {
        for(int col = 0; col < 4; col++) {
            jetons_na_temp[ligne][col].x = jetons_na[ligne][col].x;
            jetons_na_temp[ligne][col].y = jetons_na[ligne][col].y;
        }
    }
    
    /* Assigner les positions du dé */
    {
        des[0].x = 7;
        des[0].y = 11;
        des[1].x = 48;
        des[1].y = 11;
        des[2].x = 7;
        des[2].y = 43;
        des[3].x = 48;
        des[3].y = 43;
    }
    
    char bloc_na;
    Jetons_na p1;
    p1.x = 51;
    p1.y = 11;
    
    do {
        deplacer_curseur_na(10, 10);
        printf("Combien de joueurs veulent jouer? (entrer 2-4)[d-droite/a-gauche/o-valider] ");
        deplacer_curseur_na(51, 11);
        
        
        for(int i = 51; i <= 63; i++)
            printf("%c", 178);
        for(int i = 51; i <= 63; i += 4) {
            deplacer_curseur_na(i, 12);
            printf("%c", 178);
        }
        deplacer_curseur_na(51, 13);
        for(int i = 51; i <= 63; i++)
            printf("%c", 178);
            
        deplacer_curseur_na(53, 12);
        printf("2");
        deplacer_curseur_na(57, 12);
        printf("3");
        deplacer_curseur_na(61, 12);
        printf("4");
        
    
        deplacer_curseur_na(p1.x, p1.y);
        printf("_____");
        deplacer_curseur_na(p1.x, p1.y + 1);
        printf("|");
        deplacer_curseur_na(p1.x + 4, p1.y + 1);
        printf("|");
        
        bloc_na = getchar();
        
        switch(bloc_na) {
            case 'd':
            case 'D':
                if(p1.x < 59)
                    p1.x += 4;
                break;
            case 'a':
            case 'A':
                if(p1.x > 51)
                    p1.x -= 4;
                break;
            case 'o':
            case 'O':
                if(p1.x == 51)
                    nb_joueurs_na = 2;
                else if(p1.x == 55)
                    nb_joueurs_na = 3;
                else
                    nb_joueurs_na = 4;
                break;
        }
    } while(bloc_na != 'o' && bloc_na != 'O');
     // Switch pour le menu_na des paramètres
    if(nb_joueurs_na >= 2 && nb_joueurs_na <= 4) {
        system("clear");
        deplacer_curseur_na(10, 11);
        printf("Voulez-vous entrer les noms_na des joueurs ? (y-oui n-non) ");
        char choix_na = getchar();
        scanf("%s",&choix_na);
        if(choix_na == 'y' || choix_na == 'Y') {
            for(int i = 0; i < nb_joueurs_na; i++) {
                system("clear");
                deplacer_curseur_na(10, 12);
                printf("Entrer le nom du joueur %d ", i+1);
                deplacer_curseur_na(33, 12);
                printf("|");
                deplacer_curseur_na(33, 11);
                
                for(int i = 1; i < 15; i++)
                    printf("_");
                    
                deplacer_curseur_na(47, 12);
                printf("|");
                deplacer_curseur_na(34, 12);
                
                for(int i = 1; i < 14; i++)
                    printf("_");
                    
                deplacer_curseur_na(34, 12);
                int y = 0;
                
                do {
                    y++;
                    noms_na[i][y - 1] = getchar();
                } while(noms_na[i][y - 1] != '\n');
            }
            
            system("clear");
            definir_caracteres_na();
            jouer_na();
        }
        else if(choix_na == 'q' || choix_na == 'Q') {
            deplacer_curseur_na(10, 15);
            printf("Merci d'avoir joué ! J'espère que vous avez apprécié le jeu.");
        }
        else {
            system("clear");
            definir_caracteres_na();
            system("clear");
            jouer_na();
        }
    }
}


void chargement_na()    
{
    system("clear");
    deplacer_curseur_na(15, 10);
    printf("\nChargement veuillez patienter...\n");
    for(int i = 1; i <= 10; i++)
    {
       
        for(int t = 1; t <= 1000000; t++);
        printf("%c", 177);
    }
}

void menu_na(){
    char touche_na = 's';
    Jetons_na curseur_menu_na;
    curseur_menu_na.x = 9;    
    curseur_menu_na.y = 14;   
    
    do
    {
        system("clear");  


        deplacer_curseur_na(45, 15);
        printf("Touches ");
        deplacer_curseur_na(45, 17);
        printf("----------- ");
        deplacer_curseur_na(45, 18);
        printf("Utilisez les touche_nas suivantes");
        deplacer_curseur_na(40, 20);
        printf("w : Haut, s : Bas, o : valider");
        deplacer_curseur_na(40, 22);
        deplacer_curseur_na(10, 9);
        printf("Bienvenue joueurs");
        deplacer_curseur_na(10, 11);
        printf("Menu_na principal");
        deplacer_curseur_na(8, 12);
        printf("____________________________");
        deplacer_curseur_na(10, 15);
        printf("Démarrer");
        deplacer_curseur_na(10, 17);
        printf("Paramètres");
        deplacer_curseur_na(10, 19);
        printf("À propos");
        
        deplacer_curseur_na(curseur_menu_na.x, curseur_menu_na.y);
        for(int i = 0; i <= 11; i++)
            printf("_");
        deplacer_curseur_na(curseur_menu_na.x, curseur_menu_na.y + 1);
        printf("|");
        deplacer_curseur_na(curseur_menu_na.x + 11, curseur_menu_na.y + 1);
        printf("|");
        
        
        
        touche_na = getchar();   
        switch(touche_na)
        {
            case 's':
            case 'S':
                if(curseur_menu_na.y < 18)
                    curseur_menu_na.y += 2;
                break;
            case 'W':
            case 'w':
                if(curseur_menu_na.y > 14)
                    curseur_menu_na.y -= 2;
                break;
            case 'o':
            case 'O':
                if(curseur_menu_na.y == 14)   
                    sous_menu_na();
                else if(curseur_menu_na.y == 16)   
                {
                    char touche_na_param;
                    Jetons_na curseur_param;
                    curseur_param.x = 19;
                    curseur_param.y = 13;
                    do
                    {
                        system("\nclear\n");
                        deplacer_curseur_na(10, 11);
                        printf("\nParamètres\n");
                        deplacer_curseur_na(20, 12);
                        printf("Son");
                        deplacer_curseur_na(20, 15);
                        printf("Volume");
                        deplacer_curseur_na(20, 18);
                        printf("Retour");
                        deplacer_curseur_na(curseur_param.x, curseur_param.y + 1);
                        printf("|");
                        deplacer_curseur_na(curseur_param.x, curseur_param.y);
                        
                        for(int i = 1; i <= 8; i++)
                            printf("_");
                        
                        deplacer_curseur_na(curseur_param.x + 7, curseur_param.y + 1);
                        printf("|");
                        
                        if(curseur_param.y == 13 || curseur_param.y == 16)
                        {
                            deplacer_curseur_na(curseur_param.x + 1, curseur_param.y + 1);
                            printf("<");
                            deplacer_curseur_na(curseur_param.x + 6, curseur_param.y + 1);
                            printf(">");
                        }
                        
                        if(curseur_param.y == 16)
                        {
                            deplacer_curseur_na(curseur_param.x + 3, curseur_param.y + 1);
                            printf("%d", frequence_na / 100);
                        }
                        else if(curseur_param.y == 13)
                        {
                            deplacer_curseur_na(curseur_param.x + 3, curseur_param.y + 1);
                            if(son_na)
                                printf("on");
                            else
                                printf("off");
                        }
                        
                        touche_na_param = getchar();
                        
                switch(touche_na_param)   
                {
                    case 's':
                    case 'S':
                        if(curseur_param.y < 16)
                            curseur_param.y += 3;
                        else if(curseur_param.y == 16)
                            curseur_param.y += 1;
                        break;
                        
                    case 'w':
                    case 'W':
                        if(curseur_param.y == 17)
                            curseur_param.y -= 1;
                        else if(curseur_param.y > 13)
                            curseur_param.y -= 3;
                        break;
                        
                    case 'd':
                    case 'D':
                        if(curseur_param.y == 16 && frequence_na <= 400)
                            frequence_na += 100;
                        else if(curseur_param.y == 13)
                            son_na = !son_na;
                        break;
                        
                    case 'A':
                    case 'a':
                        if(curseur_param.y == 16 && frequence_na > 100)
                            frequence_na -= 100;
                        else if(curseur_param.y == 13)
                            son_na = !son_na;
                        break;
                        
                    case 'o':
                    case 'O':
                        if(curseur_param.y == 17)
                            menu_na();
                        break;
                    }
                } while(touche_na_param != 'O' || touche_na_param != 'o');
            }
            else if(curseur_menu_na.y == 18)
				{
					char bloc_na;
					do
					{
						system("clear");
						deplacer_curseur_na(10,15);
						printf("credit:");
						deplacer_curseur_na(10,16);
						printf("Programmeur:");
						deplacer_curseur_na(20,17);
						printf("NANA KAMDOU");
						deplacer_curseur_na(20,18);
						printf("Jires Jospin");
						deplacer_curseur_na(20,19);
						printf("UY1-Cameroun");
						deplacer_curseur_na(20,20);
						printf("Licence");
						deplacer_curseur_na(20,21);
						printf("Niveau 2");
						deplacer_curseur_na(10,22);
						printf("Fac-science");
						deplacer_curseur_na(20,23);
						printf("Entreprise ");
						deplacer_curseur_na(30,24);
						printf("-------------------");
						deplacer_curseur_na(30,25);
						printf("NKJ Corporation");
						deplacer_curseur_na(50,27);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						deplacer_curseur_na(50,28);
						printf("%c",178);
						deplacer_curseur_na(55,28);
						printf("%c",178);
						deplacer_curseur_na(51,28);
						printf("Back");
						deplacer_curseur_na(50,29);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						printf("%c",178);
						bloc_na = getchar();
						if(bloc_na == 'o' || bloc_na == 'O')
							menu_na();
					}while(bloc_na != 'o' && bloc_na != 'O');
				}
				
		}
	}while(touche_na != 'o' && touche_na != 'O');
}
