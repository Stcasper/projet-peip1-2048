#include "jeu.h"

/* NE PAS MODIFIER LES FONCTIONS DEFINIES DANS CE FICHIER ! */

/* initialise le generateur de nombres pseudo-aleatoire.
 * Cette fonction ne doit etre appelee qu'une seule fois, au lancement
 * du programme
 */
void resetRand (int mode) { srand(mode ? time(0) : 1); }


/* Tirage aleatoire de la valeur de la nouvelle tuile.
 * Respecte la proportion (moyenne) demandee de tuiles 2
 */
size_t nouvelle(const Grille &g) {
  return (rand() % 10) < (int) proportion(g) ? 2 : 4;
}

/* retourne l'indice de la prochaine case vide a remplir par la nouvelle tuile.
 * dans un vecteur qui serait implicitement obtenu en collectant les
 * coordonnees des cases vides dans un parcours de haut en bas et de gauche à
 * droite de la grille.
 * Une fois que vous avez obtenu l'indice grace a un appel a cette fonction,
 * en parcourant le graphe de la meme maniere, l'indice vous indique quelle case
 * doit etre remplie.
 */

size_t place(const Grille &g) {
  size_t cible, n;
  n = vides(g);
  if (n == 0) {
    cerr << ">Erreur: appel a place() sur une grille pleine" << endl;
    exit(1);
  }
  cible = rand() % n;
  // Mettre l'instruction suivante en commentaire si vous ne voulez
  // plus avoir le message.
  cerr << "Indice de la prochaine tuile: " << cible << endl;
  return cible;
}
