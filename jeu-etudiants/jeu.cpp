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

        if (g.cases.at(k).at(i)==0){  // on test si la case est vide// modifi�
            j=j+1;
            if (j==position){ // si on est a la bonne position on copie la nouvelle case dans la grille
                g.cases.at(k).at(i)=nouvelle_case;//modifi�
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
    if((res==2) or (res==4)){   // si la case qui a la valeur la plus haute est 2 ou 4 alors on consid�re que le score est 0
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

int droite(Grille &g) {
bool fusionPossible = false;
bool pasZero = false;
bool mvmtPos = false;

//d�calage droite
    for (size_t i=0; i<g.dim;i=i+1){ //Pour chaque ligne
        pasZero = false;
        for (size_t j =0; j<g.dim; j=j+1){// Pour chaque colonne
            if (g.cases.at(j).at(i)!=0) {
                pasZero = true;
            }
         if ((pasZero) and (g.cases.at(j).at(i)==0)) {
            mvmtPos=true;
         }
         if (g.cases.at(j).at(i)==0){ // Si la valeur de la case est �gale � z�ro

          // Cr�ation d'une ligne tampon
          vector<size_t> tampon;
          tampon=vector<size_t>(g.dim);

          // Copie de la ligne a d�caler dans le vector tampon
          for(size_t w=0; w<g.dim;w=w+1){
            tampon.at(w)=g.cases.at(w).at(i);
          }

          g.cases.at(0).at(i)=0; //on d�cale le 0 tout a gauche

          for(size_t c=0; c<j;c=c+1){ // on s'arrete a la case j car il n'y a rien a d�caler apr�s
                g.cases.at(c+1).at(i)=tampon.at(c);
            }
         }
        }
    }

    // Fusion droite
    for (size_t i=0; i<g.dim;i=i+1){ //Pour chaque ligne
        for (size_t j=g.dim-1; j>0; j=j-1){// Pour chaque colonne (On lit deouis la droite vu qu'on d�cale � gauche) (On s'arr�te un cran avant la fin pour ne pas d�border du tableau)
            if (g.cases.at(j).at(i)==g.cases.at(j-1).at(i)&&g.cases.at(j).at(i)!=0){ // Si la valeur de la case est �gale � la valeur de la case suivante et est non nulle
                g.cases.at(j).at(i)=g.cases.at(j).at(i)*2; // On fusionne les deux cases dans la premi�re
                fusionPossible=true;
                g.cases.at(j-1).at(i)=0; // On met un z�ro dans la seconde
                //j=j-1; // On d�cale d'un indice pour �viter de traiter � nouveau la colonne d'apr�s
            }
        }
    }

    // deuxuieme d�&calage � droite
     for (size_t i=0; i<g.dim;i=i+1){
        for (size_t j =0; j<g.dim; j=j+1){// on parcourt la grille
         if (g.cases.at(j).at(i)==0){ //on parcourt en lignes

          vector<size_t> tampon;
          tampon=vector<size_t>(g.dim);//on d�finit la taille de la ligne
          for(size_t w=0; w<g.dim;w=w+1){
            tampon.at(w)=g.cases.at(w).at(i);// on copie la ligne a d�caler dans le vector tampon
          }
            g.cases.at(0).at(i)=0; //on d�cale le 0 tout a gauche
            for(size_t c=0; c<j;c=c+1){ // on s'arrete a la case j car il n'y a rien a d�caler apr�s
                g.cases.at(c+1).at(i)=tampon.at(c);
            }
         }
        }
    }


  if ((fusionPossible==false) and (mvmtPos==false)) {
        return -1; // a completer
  }
  else {
    ajout(g);
    return vides(g);
  }
}

int gauche(Grille &g) {
    bool fusionPossible = false;
    bool pasZero = true;
    bool mvmtPos = false;


    //d�calage gauche
    for (size_t i=0; i<g.dim;i=i+1){ //Pour chaque ligne
        pasZero = false;
        for (size_t j =g.dim; j>0; j=j-1){// Pour chaque colonne
            if (g.cases.at(j-1).at(i)!=0) {
                pasZero = true;
            }
            if ((pasZero) and (g.cases.at(j-1).at(i)==0)) {
                mvmtPos=true;
            }
            if (g.cases.at(j-1).at(i)==0){ // Si la valeur de la case est �gale � z�ro

                // Cr�ation d'une ligne tampon
                vector<size_t> tampon;
                tampon=vector<size_t>(g.dim);

                // Copie de la ligne a d�caler dans le vector tampon
                for(size_t w=0; w<g.dim;w=w+1){
                    tampon.at(w)=g.cases.at(w).at(i);
                }

                g.cases.at(g.dim-1).at(i)=0; //on d�cale le 0 tout a droite

                for(size_t c=g.dim; c>j;c=c-1){ // on s'arrete a la case j car il n'y a rien a d�caler apr�s
                    g.cases.at(c-2).at(i)=tampon.at(c-1);
                }
            }
        }
    }


    // Fusion gauche
    for (size_t i=0; i<g.dim;i=i+1){ //Pour chaque ligne
        for (size_t j =0; j<g.dim-1; j=j+1){// Pour chaque colonne (On lit deouis la gauche vu qu'on d�cale � gauche) (On s'arr�te un cran avant la fin pour ne pas d�border du tableau)
            if (g.cases.at(j).at(i)==g.cases.at(j+1).at(i)&&g.cases.at(j).at(i)!=0){ // Si la valeur de la case est �gale � la valeur de la case suivante et est non nulle
                g.cases.at(j).at(i)=g.cases.at(j).at(i)*2; // On fusionne les deux cases dans la premi�re
                fusionPossible=true;
                g.cases.at(j+1).at(i)=0; // On met un z�ro dans la seconde
                j=j+1; // On d�cale d'un indice pour �viter de traiter � nouveau la colonne d'apr�s
            }
        }
    }

    //d�calage gauche pour �liminer les z�ros cr��s par la fusion
    for (size_t i=0; i<g.dim;i=i+1){ //Pour chaque ligne
        for (size_t j =g.dim; j>0; j=j-1){// Pour chaque colonne
            if (g.cases.at(j-1).at(i)==0){ // Si la valeur de la case est �gale � z�ro

                // Cr�ation d'une ligne tampon
                vector<size_t> tampon;
                tampon=vector<size_t>(g.dim);

                // Copie de la ligne a d�caler dans le vector tampon
                for(size_t w=0; w<g.dim;w=w+1){
                    tampon.at(w)=g.cases.at(w).at(i);
                }

                g.cases.at(g.dim-1).at(i)=0; //on d�cale le 0 tout a droite

                for(size_t c=g.dim; c>j;c=c-1){ // on s'arrete a la case j car il n'y a rien a d�caler apr�s
                    g.cases.at(c-2).at(i)=tampon.at(c-1);
                }
            }
        }
    }

  if ((fusionPossible==false) and (mvmtPos==false)) {
        return -1; // a completer
  }
  else {
    ajout(g);
    return vides(g);
  }
}

int haut(Grille &g) {
    bool fusionPossible = false;
    bool pasZero = false;
    bool mvmtPos = false;


    //d�calage haut
    for (size_t j=0; j<g.dim;j=j+1){ //Pour chaque colonne
        pasZero = false;
        for (size_t i =g.dim; i>0; i=i-1){// Pour chaque ligne
            if (g.cases.at(j).at(i-1)!=0) {
                pasZero = true;
            }
            if ((pasZero) and (g.cases.at(j).at(i-1)==0)) {
                mvmtPos=true;
            }
            if (g.cases.at(j).at(i-1)==0){ // Si la valeur de la case est �gale � z�ro

                // Cr�ation d'une ligne tampon
                vector<size_t> tampon;
                tampon=vector<size_t>(g.dim);

                // Copie de la ligne a d�caler dans le vector tampon
                for(size_t w=0; w<g.dim;w=w+1){
                    tampon.at(w)=g.cases.at(j).at(w);
                }

                g.cases.at(j).at(g.dim-1)=0; //on d�cale le 0 tout en bas

                for(size_t c=g.dim; c>i;c=c-1){ // on s'arrete a la case i car il n'y a rien a d�caler apr�s
                    g.cases.at(j).at(c-2)=tampon.at(c-1);
                }
            }
        }
    }

    // Fusion haut
    for (size_t j=0; j<g.dim;j=j+1){ //Pour chaque colonne
        for (size_t i =0; i<g.dim-1; i=i+1){// Pour chaque ligne (On lit deouis le haut vu qu'on d�cale en haut) (On s'arr�te un cran avant la fin pour ne pas d�border du tableau)
            if (g.cases.at(j).at(i)==g.cases.at(j).at(i+1)&&g.cases.at(j).at(i)!=0){ // Si la valeur de la case est �gale � la valeur de la case suivante et est non nulle
                g.cases.at(j).at(i)=g.cases.at(j).at(i)*2; // On fusionne les deux cases dans la premi�re
                fusionPossible=true;
                g.cases.at(j).at(i+1)=0; // On met un z�ro dans la seconde
                i=i+1; // On d�cale d'un indice pour �viter de traiter � nouveau la ligne d'apr�s
            }
        }
    }

    //d�calage haut pour �liminer les z�ros cr��s par la fusion
    for (size_t j=0; j<g.dim;j=j+1){ //Pour chaque colonne
        for (size_t i =g.dim; i>0; i=i-1){// Pour chaque ligne
            if (g.cases.at(j).at(i-1)==0){ // Si la valeur de la case est �gale � z�ro

                // Cr�ation d'une ligne tampon
                vector<size_t> tampon;
                tampon=vector<size_t>(g.dim);

                // Copie de la ligne a d�caler dans le vector tampon
                for(size_t w=0; w<g.dim;w=w+1){
                    tampon.at(w)=g.cases.at(j).at(w);
                }

                g.cases.at(j).at(g.dim-1)=0; //on d�cale le 0 tout en bas

                for(size_t c=g.dim; c>i;c=c-1){ // on s'arrete a la case i car il n'y a rien a d�caler apr�s
                    g.cases.at(j).at(c-2)=tampon.at(c-1);
                }
            }
        }
    }

   if ((fusionPossible==false) and (mvmtPos==false)) {
        return -1; // a completer
  }
  else {
    ajout(g);
    return vides(g);
  }
}

int bas(Grille &g) {
    bool fusionPossible = false;
    bool pasZero = false;
    bool mvmtPos = false;


    //d�calage bas
    for (size_t j=0; j<g.dim;j=j+1){ //Pour chaque colonne
        pasZero = false;
        for (size_t i =0; i<g.dim; i=i+1){// Pour chaque ligne
            if (g.cases.at(j).at(i)!=0) {
                pasZero = true;
            }
         if ((pasZero) and (g.cases.at(j).at(i)==0)) {
            mvmtPos=true;
         }
         if (g.cases.at(j).at(i)==0){ // Si la valeur de la case est �gale � z�ro

          // Cr�ation d'une ligne tampon
          vector<size_t> tampon;
          tampon=vector<size_t>(g.dim);

          // Copie de la ligne a d�caler dans le vector tampon
          for(size_t w=0; w<g.dim;w=w+1){
            tampon.at(w)=g.cases.at(j).at(w);
          }

          g.cases.at(j).at(0)=0; //on d�cale le 0 tout en haut

          for(size_t c=0; c<i;c=c+1){ // on s'arrete a la case j car il n'y a rien a d�caler apr�s
                g.cases.at(j).at(c+1)=tampon.at(c);
            }
         }
        }
    }


    // Fusion bas
    for (size_t j=0; j<g.dim;j=j+1){ //Pour chaque colonne
        for (size_t i = g.dim-1; i>0; i=i-1){// Pour chaque ligne (On lit deouis le bas vu qu'on d�cale en bas) (On s'arr�te un cran avant la fin pour ne pas d�border du tableau)
            if (g.cases.at(j).at(i)==g.cases.at(j).at(i-1)&&g.cases.at(j).at(i)!=0){ // Si la valeur de la case est �gale � la valeur de la case suivante et est non nulle
                g.cases.at(j).at(i)=g.cases.at(j).at(i)*2; // On fusionne les deux cases dans la premi�re
                fusionPossible=true;
                g.cases.at(j).at(i-1)=0; // On met un z�ro dans la seconde
                //i=i+1; // On d�cale d'un indice pour �viter de traiter � nouveau la ligne d'apr�s
            }
        }
    }

    //d�calage bas pour �liminer les z�ros cr��s par la fusion
    for (size_t j=0; j<g.dim;j=j+1){ //Pour chaque colonne
        pasZero = false;
        for (size_t i =0; i<g.dim; i=i+1){// Pour chaque ligne
         if (g.cases.at(j).at(i)==0){ // Si la valeur de la case est �gale � z�ro

          // Cr�ation d'une ligne tampon
          vector<size_t> tampon;
          tampon=vector<size_t>(g.dim);

          // Copie de la ligne a d�caler dans le vector tampon
          for(size_t w=0; w<g.dim;w=w+1){
            tampon.at(w)=g.cases.at(j).at(w);
          }

          g.cases.at(j).at(0)=0; //on d�cale le 0 tout en haut

          for(size_t c=0; c<i;c=c+1){ // on s'arrete a la case j car il n'y a rien a d�caler apr�s
                g.cases.at(j).at(c+1)=tampon.at(c);
            }
         }
        }
    }

   if ((fusionPossible==false) and (mvmtPos==false)) {
        return -1; // a completer
  }
  else {
    ajout(g);
    return vides(g);
  }
}

void affiche (const Grille &g) { //ok
    for (size_t i=0;i<dimension(g);i=i+1){
        for(size_t j=0;j<=6*dimension(g);j=j+1){ // on affiche une ligne d'�toiles
            cout << '*';
        }
        cout<<endl;
    for( size_t j=0; j<g.dim;j=j+1){
            cout<<'*'<< setw(5) << g.cases.at(j).at(i); //modifi�
    }
    cout << '*';
    cout<<endl;
    }

    for(size_t j=0;j<=6*dimension(g);j=j+1){
    cout << '*';
    }
    cout<<endl;
}

void ajout (Grille &g) {
  size_t nouvelle_case , i, j, position ,k;
  position=place(g);
  nouvelle_case=nouvelle(g);
  j=0;

  for (i=0 ; i<g.dim;i=i+1){
    for(k=0; k<g.dim;k=k+1){  // on parcour la grille.

        if (g.cases.at(k).at(i)==0){  // on test si la case est vide// modifi�
            j=j+1;
            if (j==position){ // si on est a la bonne position on copie la nouvelle case dans la grille
                g.cases.at(k).at(i)=nouvelle_case;//modifi�
            }
        }
    }
  }
}
