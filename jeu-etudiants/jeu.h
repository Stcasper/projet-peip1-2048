#include <cstdlib> // pour srand, exit
#include <time.h>  // pour time
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/* Ne pas toucher aux deux lignes
 * #ifndef  _JEU_2024
 * #define  _JEU_2024 1
 * ...
 * ni a la ligne en fin de fichier
 * #endif
 * qui encadrent nos definitions. Elles servent à eviter que le compilateur
 * definisse deux fois les memes identificateurs (ce qui provoquerait une
 * erreur) au cas ou vous feriez deux fois #include "jeu.h"
 * Le compilateur ne traite les lignes que si la macro _JEU_2048 n'est
 * pas definie, ce qu'il s'empresse de faire quand il voit ce code pour la
 * premiere fois.
 */
#ifndef _JEU_2048
#define _JEU_2048 1


/* Dans la structure grille on définit la dimension de notre grille (ex: 4*4)
On définit la probabilité de voir apparaitre sur une tuile 2
On définit la cible qui est le moment où le jeu est fini et que l'utilisateur a gagné.
Pour finir on a un vector de vector de size_t pour stoquer les nombres presents dans la grille.*/
typedef struct {
  size_t dim , objectif , proba;
  vector <vector <size_t>> cases;
} Grille;


void init(Grille &g, size_t dimension, size_t cible, size_t proportion);
bool charge(Grille &g, vector<vector<size_t>> &v);
void affiche(const Grille &g);
int gauche(Grille &g), droite(Grille &g), haut(Grille &g), bas(Grille &g);
bool succes(const Grille &g);
size_t proportion(const Grille &g), dimension(const Grille &g);
size_t score(const Grille &g), vides(const Grille &g), cible(const Grille &g);
size_t nouvelle(const Grille &g), place(const Grille &g);
void resetRand(bool mode);

/* ajouter ici les en-tetes des fonctions qui sont definies dans un fichier
 * et utilisees dans un autre
 */

#endif 	// Ne pas toucher !
