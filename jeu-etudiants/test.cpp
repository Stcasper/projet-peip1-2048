#include "jeu.h"
#include <cctype>	// pour isspace
#include <vector>
#include <string>
#include <iostream>




/* remet une grille dans l'etat de depart */
void reset(Grille &g) {
  init(g, dimension(g), cible(g), proportion(g));
}

/* exemple d'utilisation d'une grille a partir du contenu d'un vecteur.
 * La fonction charge() permet de mettre directement une grille dans
 * un etat donne pour pouvoir lui appliquer certaines commandes.
 * Suppose que les dimensions de la grille et des vecteurs sont cohérentes
 * Vous pouvez constituer vos propres tests et les lancer a partir de
 * la fonction main.
 */
bool teste1(Grille &g) {
  //vector<vector<size_t>> v ={ { 128, 4, 0, 0 }, { 2, 16, 4, 2 }, { 0, 0, 0, 0 }, { 2, 0, 0, 0} };
  //vector<vector<size_t>> v ={ { 16, 8, 4, 4 }, { 4, 4, 8, 8 }, { 2, 0, 0, 2 }, { 2, 0, 2, 4} };
  vector<vector<size_t>> v ={ { 2, 4, 2, 2 }, { 2, 4, 0, 0 }, { 4, 8, 0, 2 }, { 0, 8, 2, 4} };
  bool res;
  reset(g);	// reinitialiser la grille avant chargement.
  res = charge(g, v);
  if (not res) {
    cerr << "probleme de chargement !" << endl;
    return false;
  }
  //gauche(g);
  affiche(g);
  return true;
}

bool teste21(Grille &g) {
  vector<vector<size_t>> v =
    { { 128, 8, 2, 0 }, { 4, 16, 0, 0 }, { 0, 0, 4, 0 }, { 2, 0, 0, 0} };
  bool res;
  reset(g);
  res = charge(g, v);
  if (not res) {
    cerr << "probleme de chargement !" << endl;
    return false;
  }
  gauche(g); haut(g);
  affiche(g);
  return true;
}

// a completer
int main() {
  Grille g; char lu;
  cout << "Bienvenue dans notre 2048" << endl;
  // cree une grille de taille 4*4 avec une cible a atteindre de 64
  // avec proba 0.7 d'avoir une tuile de valeur 2 et proba 0.3 d'avoir
  // une tuile de valeur 4 a chaque fois qu'on fait apparaitre une
  // nouvelle tuile
  init(g, 4, 64, 7);
  teste1(g);
  affiche(g);
  while (true) {
    cout << "Entrez la prochaine commande: ";
    do { cin >> lu; } while (isspace(lu));
    if (lu == 'q' or lu == 'Q') break;
    if(lu=='d'){
        droite(g);
    }
    if (lu=='g'){
        gauche(g);
    }
    // faire ce qu'il faut en fonction de ce que vaut la variable 'lu'
    affiche(g);
    cout<<"votre score est de "<<score(g)<< endl;
  }
  cout << "Bye Bye" << endl;
  return 0;
}
