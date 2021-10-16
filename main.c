#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "commande.h"

/*************************************************************** */
int menu(void)
{
    int choix;
    system("cls");
    printf("\t\tGestion des commandes\n\n");
    printf("0) Fin\n");
    printf("1) Ajouter une ligne de commande\n");
    printf("2) Afficher une commande\n");
    printf("3) Supprimer une commande\n");
    printf("4) Supprimer la liste de commandes\n");
    printf("5) Inverser la liste de commandes\n");
    printf("6) Transformer la liste de commandes en tableau de commandes\n");
    printf("7) Supprimer le tableau de commandes\n\n");
    printf("\t\tVotre choix : ");scanf("%d", &choix);
    system("cls");
    return choix;
}
int main()
{
    ListeCmd listeCmd;
    LigCmd* ligCmd;
    LigCmd** tabCmd=NULL;
    int choix, numCmd, n;
    creerListeCmdVide(&listeCmd);
    do
    {
        choix = menu();
        switch(choix)
        {
            case 1 : ligCmd = creerLigCmd();
                     ajouterLigCmd(&listeCmd, ligCmd);
                     break;
            case 2 : printf("Commande Num : ");
                     scanf("%d", &numCmd);
                     afficherCmd(&listeCmd, numCmd);
                     _getch();
                     break;
            case 3 : printf("Num Commande : ");
                     scanf("%d", &numCmd);
                     if(supprimerCmd(&listeCmd, numCmd)==1)
                        printf("La commande est supprimee!");
                     else
                        printf("La commande est inexistante!");
                     _getch();
                     break;
            case 4 : supprimerListeCmd(&listeCmd);
                     printf("La liste des commandes est supprimee!");
                     _getch();
                     break;
            case 5 : inverserListeCmd(&listeCmd);
                     printf("La liste des commandes est inversee!\n");
                     afficherListeCmd(&listeCmd); /* test */
                     _getch();
                     break;
            case 6 : if(listeCmd.taille==0)
                        printf("La liste des commandes est vide!");
                     else
                     {
                        if(tabCmd!=NULL) supprimerTabCmd(tabCmd, n);
                        tabCmd = listeCmdToTabCmd(&listeCmd, &n);
                        afficherTabCmd(tabCmd, n); /* test */
                     }
                     _getch();
                     break;
            case 7 : if(tabCmd==NULL)
                        printf("Le tableau des commandes est vide!");
                     else
                     {
                        supprimerTabCmd(tabCmd, n);
                        tabCmd = NULL;
                        printf("Le tableau des commandes est supprime!");
                     }
                     _getch();
                     break;
        }
    }while(choix!=0);
    return 0;
}
