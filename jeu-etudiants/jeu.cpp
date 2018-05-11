#include "jeu.h"



void init(Grille &g, size_t dimension, size_t cible, size_t proportion) { //ok
  g.dim=dimension;
  g.objectif=cible;
  g.proba=proportion;

  vector<vector<size_t>> v;
  v=vector<vector<size_t>>(g.dim);

  size_t p , l,m;

  for(m=0; m<g.dim; m=m+1){
    for(l=0; l<g.dim;l=l+1){ // on parcourt le vecteur v.
    v.at(m).push_back(0);
      // on remplit v de 0.
    }
  }
    g.cases=v;


  for(p=0; p<2; p=p+1){ // on tourne deux fois pour ajouter deux valeurs dans la grille

  size_t nouvelle_case , i, j, position ,k;
  position=place(g);
  nouvelle_case=nouvelle(g);
  j=0;

  for (i=0 ; i<g.dim;i=i+1){
    for(k=0; k<g.dim;k=k+1){  // on parcour la grille.

        if (g.cases.at(k).at(i)==0){  // on test si la case est vide// modifié
            j=j+1;
            if (j==position){ // si on est a la bonne position on copie la nouvelle case dans la grille
                g.cases.at(k).at(i)=nouvelle_case;//modifié
            }
        }
    }
  }
  }


  // on initialise g en attrubuant une dimension une cible et un proba
}

size_t vides(const Grille &g) {  //ok
  size_t i, j;
  size_t res=0;
  for (i=0;i<g.dim;i=i+1){
    for(j=0; j<g.dim;j=j+1){
        if(g.cases.at(i).at(j)==0){
            res=res+1;
        }
    }
  }

  return res;
}

size_t score(const Grille &g) {  //ok
  size_t i, j;
  size_t res=0;
  for (i=0;i<g.dim;i=i+1){
    for(j=0; j<g.dim;j=j+1){  //on parcour la grille
        if(g.cases.at(i).at(j)>res){  // on recherche la case de la grille qui a la plus haute valeur
            res=g.cases.at(i).at(j);
        }
    }
  }
    if((res==2) or (res==4)){   // si la case qui a la valeur la plus haute est 2 ou 4 alors on considère que le score est 0
        res=0;
    }
  return res;
 }

size_t proportion(const Grille &g) { //ok
  size_t res=0;
    res=g.proba;
    return res;
}

size_t cible(const Grille &g) {  //ok
  size_t res=0;
    res=g.objectif;
  return res;
}

size_t dimension(const Grille &g) {  //ok
  size_t res=0;
    res=g.dim;
    return res;
}

bool succes(const Grille &g) {  //ok
 if (score(g)==cible(g)){
        return true;
    }
    else {
return false;
    }
}

bool charge(Grille &g, vector<vector<size_t>> &v) { //ok
// On suppose ici que les tuiles de v ne comportent bien que des puissances de 2
size_t i,j;

  if ((score(g)!=0) or (g.dim!=v.size())){   // on test que le score est a 0 et que la dimension de v est corecte.
    return false;
  }
    for(j=0; j<v.size();j=j+1){  //on parcour le vector v
        if (v.at(j).size()!=g.dim){ // on test si chaque vector de v a la bonne dimension.
    return false;
        }
    }
  for(i=0; i<v.size(); i=i+1){  // on copie le contenu de v dans le vector de la grille.
    g.cases.at(i)=v.at(i);
  }

   return true;
}

int droite(Grille &g) { //fausse
    bool fusionpos;
    bool mvmtpos;
    fusionpos=false;
    mvmtpos=false;


 //décalage droite
    for (size_t i=0; i<g.dim;i=i+1){
        for (size_t j =0; j<g.dim; j=j+1){// on parcourt la grille
         if (g.cases.at(j).at(i)==0){ //on parcourt en lignes

          vector<size_t> tampon;
          tampon=vector<size_t>(g.dim);//on définit la taille de la ligne
          for(size_t w=0; w<g.dim;w=w+1){
            tampon.at(w)=g.cases.at(w).at(i);// on copie la ligne a décaler dans le vector tampon
          }
            g.cases.at(0).at(i)=0; //on décale le 0 tout a gauche
            for(size_t c=0; c<j;c=c+1){ // on s'arrete a la case j car il n'y a rien a décaler après
                g.cases.at(c+1).at(i)=tampon.at(c);
            }
         }
        }
    }

    //fusion droite
    for (size_t k=0;k<g.dim;k=k+1){//on parcourt les lignes de haut en bas
    for (size_t i=g.dim-1;i>1;i=i-1){  // on parcourt les colonnes de droite à gauche
     if(i!=0){//condition pour éviter les sorties de tableaux
//tester si non nul



       for(size_t n=i-1;n<1;n=n-1){
       if((g.cases.at(i).at(k)!=0) and (g.cases.at(n).at(k)!=0)){//si on a pas de cases vides on rentre dans le if
            if(g.cases.at(i).at(k)==g.cases.at(n).at(k)){
                fusionpos=true;
                g.cases.at(i).at(k)=g.cases.at(n).at(k)*2;
                g.cases.at(n).at(k)=0;
            }
       }
       }
       }
    }
    }


  return -1;
}

int gauche(Grille &g) {
  return -1; // a completer
}

int haut(Grille &g) {
  return -1; // a completer
}

int bas(Grille &g) {
  return -1; // a completer
}

void affiche (const Grille &g) { //ok
    for (size_t i=0;i<dimension(g);i=i+1){
        for(size_t j=0;j<=6*dimension(g);j=j+1){ // on affiche une ligne d'étoiles
            cout << '*';
        }
        cout<<endl;
    for( size_t j=0; j<g.dim;j=j+1){
            cout<<'*'<< setw(5) << g.cases.at(j).at(i); //modifié
    }
    cout << '*';
    cout<<endl;
    }

    for(size_t j=0;j<=6*dimension(g);j=j+1){
    cout << '*';
    }
    cout<<endl;
}


