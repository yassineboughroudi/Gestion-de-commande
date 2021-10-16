#include "commande.h"
#include<stdio.h>
#include<stdlib.h>

/*****************************************************/
LigCmd* creerLigCmd(void)
{
    LigCmd* ligCmd = malloc(sizeof(LigCmd));
    if(ligCmd == NULL) exit(EXIT_FAILURE);
    printf("Num Commande : ");
    scanf("%d", &ligCmd->numCmd);
    printf("Ref Article : ");
    scanf("%s", ligCmd->refArt);
    printf("Qte Article : ");
    scanf("%d", &ligCmd->qteArt);
    printf("Prix Article : ");
    scanf("%f", &ligCmd->prixArt);
    return ligCmd;
}
/*****************************************************/
void afficherLigCmd(LigCmd* ligCmd)
{
    printf("%s\t\t%d\t\t%.2f\n", ligCmd->refArt, ligCmd->qteArt, ligCmd->prixArt);
}
/*****************************************************/
void creerListeCmdVide(ListeCmd* list)
{
    list->tete = list->queue = NULL;
    list->taille = 0;
}
/*****************************************************/
Noeud* creerNoeud(Noeud* next, LigCmd* ligCmd)
{
    Noeud* nouveau = malloc(sizeof(Noeud));
    if(nouveau == NULL) exit(EXIT_FAILURE);
    nouveau->ligCmd = ligCmd;
    nouveau->suivant = next;
    return nouveau;
}
/*****************************************************/
void ajouterLigCmd(ListeCmd* list, LigCmd* ligCmd)
{
    Noeud *courant=list->tete, *precedent=NULL, *nouveau;
    while(courant!=NULL && courant->ligCmd->numCmd != ligCmd->numCmd)
    {
        precedent=courant;
        courant=courant->suivant;
    }
    nouveau=creerNoeud(courant, ligCmd);
    if(precedent==NULL)
        list->tete=nouveau;
    else
        precedent->suivant=nouveau;
    if(courant==NULL)
        list->queue=nouveau;
    list->taille++;
}
/*****************************************************/
void afficherCmd(ListeCmd* list, int numCmd)
{
    Noeud* courant=list->tete;
    float totalCmd=0;

    while(courant && courant->ligCmd->numCmd!=numCmd)
        courant = courant->suivant;

    printf("Reference\tQuantite\tPrix Unit.\n");
    while(courant && courant->ligCmd->numCmd==numCmd)
    {
        afficherLigCmd(courant->ligCmd);
        totalCmd += courant->ligCmd->qteArt * courant->ligCmd->prixArt;
        courant = courant->suivant;
    }
    printf("Total : %.2f\n", totalCmd);
}
/******************************************************/
int supprimerCmd(ListeCmd* list, int numCmd)
{
    Noeud *courant=list->tete, *precedent=NULL;
    while(courant && courant->ligCmd->numCmd!=numCmd)
    {
        precedent=courant;
        courant=courant->suivant;
    }
    if(courant==NULL) return 0;

    if(precedent==NULL)
    {
        while(courant && courant->ligCmd->numCmd==numCmd)
        {
            list->tete=courant->suivant;
            free(courant->ligCmd);
            free(courant);
            courant=list->tete;
            list->taille--;
        }
        if(courant==NULL) list->queue = NULL;
    }
    else
    {
        while(courant && courant->ligCmd->numCmd == numCmd)
        {
            precedent->suivant = courant->suivant;
            free(courant->ligCmd);
            free(courant);
            courant=precedent->suivant;
            list->taille--;
        }
        if(courant==NULL) list->queue = precedent;
    }
    return 1;
}
/*********************************************************/
void supprimerListeCmd(ListeCmd* list)
{
    Noeud *courant=list->tete;
    while(courant!=NULL)
    {
        list->tete = courant->suivant;
        free(courant->ligCmd);
        free(courant);
        courant = list->tete;
    }
    creerListeCmdVide(list);
}
/*********************************************************/
void inverserListeCmd(ListeCmd* list)
{
    Noeud *courant=list->tete, *precedent=NULL, *suivant;
    while(courant!=NULL)
    {
        suivant = courant->suivant;
        courant->suivant = precedent;
        precedent = courant;
        courant = suivant;
    }
    list->queue = list->tete;
    list->tete = precedent;
}
/********************************************************/
void afficherListeCmd(ListeCmd* list)
{
    Noeud *courant=list->tete;
    printf("Reference\tQuantite\tPrix Unit.\n");
    while(courant!=NULL)
    {
        afficherLigCmd(courant->ligCmd);
        courant = courant->suivant;
    }
}
/********************************************************/
LigCmd** listeCmdToTabCmd(ListeCmd* list, int* n)
{
    Noeud *courant=list->tete;
    LigCmd** tabCmd=malloc(list->taille * sizeof(LigCmd*));
    int i=0;

    while(courant != NULL)
    {
        tabCmd[i] = malloc(sizeof(LigCmd));
        *tabCmd[i++] = *courant->ligCmd;
        courant = courant->suivant;
    }
    *n = i;

    return tabCmd;
}
/********************************************************/
void afficherTabCmd(LigCmd**tabCmd, int n)
{
    int i;
    printf("Reference\tQuantite\tPrix Unit.\n");
    for(i=0; i<n; i++)
        afficherLigCmd(tabCmd[i]);
}
/********************************************************/
void supprimerTabCmd(LigCmd** tabCmd, int n)
{
    int i;
    for(i=0; i<n; i++)
        free(tabCmd[i]);
    free(tabCmd);
}
