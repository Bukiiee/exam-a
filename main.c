#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int TAILLE=9;
int remplissage =0;
const int HORIZ=0;
const int VERT=1;
int grille[9][9];


/*
Pour l'exercice vous aurez besoin de generer des entiers aléatoire : rand() renvoit un entier aléatoire.
il s'utilise : rand() % NOMBREMAX + 1 
Pour un entier aléatoire entre 0 et 1 il faut donc faire rand() %2
voir dans la methode main.
*/


// Ecrire la fonction generer(), elle prend en paramètre la grille et renvoie le nombre d'éléments non nuls
int generer(int arr[TAILLE][TAILLE]){
    int i,j,total = 0;
    for (i = 0; i < TAILLE; i++){
        for (j = 0; j < TAILLE; j++){
            if (arr[i][j] != 0){
            total++;}          
        }
    }
    return total;
}

// Ce lien vous sera utile : https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

/*Écrire une fonction saisir() qui demande à l’utilisateur de saisir au clavier les indices i et j et la valeur v à placer à l’emplacement (i,j).
La fonction doit vérifier la validité des indices et de la valeur.
Si la case n’est pas occupée, la valeur doit être placée dans la grille. remplissage est alors incrémentée*/
void saisir(){
    int i, j, v;
    printf("Choisissez les coordonnees, format ligne colonne : ");
    scanf("%d %d", &i, &j);
    //si la case est hors grille, ou déjà remplie, on rejoue
    while (i<0 | i>8 | j<0 | j>8 | grille[i][j]!=0){
        printf("Case invalide, rejouez (meme format): ");
        scanf("%d %d", &i, &j);
    }
    printf("Choisissez la valeur : ");
    scanf("%d", &v);
    // si la valeur n'est pas entre 1 et 9, on rejoue
    while (v<1 | v>9){
        printf("Choix invalide, rejouez : ");
        scanf("%d", &v);
    }
    //on place la valeur dans la grille
    grille[i][j]=v;

}

/*
Écrire la fonction verifierLigneColonne() qui prend en paramètre un numéro et un sens (HORIZ ou VERT)
qui vérifie que la ligne ou la colonne (suivant les cas) numéro est bien remplie.
On pourra utiliser un tableau intermédiaire pour vérifier cela. La fonction retournera 1 si tout s’est bien passé, 0 sinon.
Les constantes HORIZ de valeur 0 et VERT de valeur 1 sont à définir.
*/

int verifierLigneColonne(int num, int sens){
    int i, val, tableau[TAILLE];
    //on parcourt la ligne
    if (sens == 0){ 
        for (i = 0; i < TAILLE; i++){
            // on crée un tableau trié avec les valeurs récupérées
            val = grille[i][num];
            if (tableau[val]==0){
                tableau[val] = val;
            }
            //si on a une valeur en double, on renvoie 0
            else{
                return 0;
            }
        } 
    }
    //idem pour la colonne
    if (sens ==1){
        for (i = 0; i < TAILLE; i++){
            val = grille[num][i];
            if (tableau[val]==0){
                tableau[val] = val;
            }
            else{
                return 0;
            }
        }
    }

    //on vérifie qu'il n'y ait aucune valeur manquante dans le tableau
    for (i = 0; i < TAILLE; i++){
        if (tableau[i]==0){
            return 0;
        }
    }
    return 1;
} 

/*
Écrire la fonction verifierRegion() qui prend en paramètre deux indices k et l qui correspondent à la région (k,l)
et qui renvoie 1 si la région est correctement remplie, 0 sinon.
*/

int verifierRegion(int k, int l){
    int i,j, val, tableau[TAILLE];
    //ici, on a sépare la grille en 9 régions 0,0 ; 0,1 ; 0,2 ; 1,0 ; 1,1 ...
    //chaque région va des cases k*3 à k*3+3 horizontalement et verticalement
    for(i=k*3;i<k*3+3; ++i){
        for(j=k*3; j<k*3+3; ++j){
            val = grille[i][j];
            if (tableau[val]==0){
                tableau[val] = val;
            }
            else{
                return 0;
            } 
        }
    }
    for (i = 0; i < TAILLE; i++){
        if (tableau[i]==0){
            return 0;
        }
    }
    return 1;
    
}

//Écrire la fonction verifierGrille() qui renvoie 1 si la grille est correctement remplie et 0 sinon

int verifierGrille(){
    int i,j;
    for (i = 0; i < TAILLE; i++){
        if (verifierLigneColonne(i, HORIZ) == 0 | verifierLigneColonne(i, VERT) == 0){
            return 0;
        }
    }
    for(i=0;i<3; ++i){
        for(j=0; j<3; ++j){
            if (verifierRegion(i,j)==0){
            return 0;
            }
        }
    }
    return 1;
}

//Écrire le programme principal, en supposant que la seule condition d’arrêt est la réussite du sudoku (ce test ne devra être fait que si nécessaire)
void afficher(){
    int i,j;
    for(i=0;i<TAILLE; ++i){
        for(j=0; j<TAILLE; ++j){
            printf("%d ", grille[i][j]);     
        }
    printf("\n");
    }
}

int main(){
    // Ne pas toucher le code entre les commentaires
    srand( time( NULL ) );

    int i, j, k;
    int solution[9][9];
    printf("SOLUTION");  
    printf("\n");  
    printf("---------------------------------");  
    printf("\n");  
    for(j=0;j<9; ++j) 
    {
    for(i=0; i<9; ++i)
        solution[j][i] = (i + j*3 +j /3) %9 +1 ; 
    }
    
    for(i=0;i<9; ++i) 
    {
    for(j=0; j<9; ++j)
        printf("%d ", solution[i][j]);
    printf("\n");  
    }
    printf("---------------------------------");  
    printf("\n");  
    
    //toucher le code entre les commentaires
    // creer une fonction qui prend la variable solution, et la variable tableauJoueur (par exemple) : un tableau rempli de 0, cette fonction doit copier certaines valeurs 
    //(grace au rand() % N) de solution dans tableauJoueur afin d'initialiser une grille jouable ( car solution est bel est bien la solution, donc pas jouable par définition. ).
    //    printf("%d",rand() % 2);

    
    for(i=0;i<TAILLE; ++i){
        for(j=0; j<TAILLE; ++j){
            k= (rand() %3);
            if (k!=1){
                grille[i][j] = 0;
            }
            else{
                grille[i][j] = solution[i][j];
            } 
        }
    }

    afficher();
    while (generer(grille)<(TAILLE*TAILLE)){
        saisir(grille);
        remplissage++;
        afficher();
    } 
    if (verifierGrille()==1){
        printf("T'es trop chaud mec franchement bravo \n");
    }
    else{
        printf("J'veux pas dire mais t'as l'air d'avoir été bercé trop près du mur \n");
    }
    //Ne pas toucher au code ci dessous
    system("pause");
    return 0;
}