#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

typedef struct
{
    int numCmd;
    char refArt[25];
    int qteArt;
    float prixArt;
}LigCmd;

typedef struct Noeud
 {
    LigCmd* ligCmd;
    struct Noeud* suivant;
 }Noeud;

typedef struct
{
    Noeud* tete;
    Noeud* queue;
    int taille;
 }ListeCmd;

LigCmd* creerLigCmd(void);
void afficherLigCmd(LigCmd*);

void creerListeCmdVide(ListeCmd*);
Noeud* creerNoeud(Noeud* next, LigCmd*);
void ajouterLigCmd(ListeCmd*, LigCmd*);
void afficherCmd(ListeCmd*, int);
int supprimerCmd(ListeCmd*, int);
void supprimerListeCmd(ListeCmd*);
void inverserListeCmd(ListeCmd*);
LigCmd** listeCmdToTabCmd(ListeCmd*, int*);
void supprimerTabCmd(LigCmd**, int);

void afficherListeCmd(ListeCmd*);
void afficherTabCmd(LigCmd**, int n);

#endif
