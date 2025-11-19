//Friday Nov 24 2:16AM
//Creation lib.h
//Listes Chainee
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct noeud
{
    char nom[50];
    float prix;
    int qte;
    struct noeud* suivant;
}noeud;

typedef struct
{
    noeud* debut;
    noeud* fin;
    int ref;
}liste;
void verifyListeAllocation(liste* li)
{
    if(li==NULL){
        perror("erreur");
        exit(EXIT_FAILURE);
    }
}
void verifyNoeudAllocation(noeud* E)
{
    if(E==NULL){
        perror("erreur");
        exit(EXIT_FAILURE);
    }
}

liste* creer_liste_produits(void)
{
    liste* li = (liste *)malloc(sizeof(liste));
    verifyListeAllocation(li);
    li->debut = NULL;
    li->fin = NULL;
    li->ref = 0;
    return(li);
    printf("Creation liste...\n");
    printf("Liste cree avec succes \n\n");
}
noeud* creer_produit(void)
{
    noeud* E1;
    E1 = malloc(sizeof(noeud));
    verifyNoeudAllocation(E1);
    printf("Creation produit\n");
    E1->qte = 0;
    E1->prix = 0;
    E1->nom[0] = '\0'; //on initialise comme ca?
    E1->suivant = NULL;
    printf("Produit cree \n\n");
    return (E1);
}
noeud* saisirProduit(void)
{
    noeud* E1;
    E1= creer_produit();
    printf("entrer la designation de votre produit : ");
    scanf("%s",E1->nom);
    printf("entrer le prix de votre produit : ");
    scanf("%f",&E1->prix);
    printf("entrer la quantite disponible : ");
    scanf("%d",&E1->qte);
    E1->suivant = NULL;
    printf("Element saisi avec succes \n\n");
    return(E1);
    

}
void ajouter_produit_liste_fin(liste* li)
{
    noeud* E;
    E = saisirProduit();
    //cas d'une liste vide
    if(li->debut == NULL){
        li->debut = E;
        li->fin = E;
    }
    else{
        li->fin->suivant = E;
        li->fin = E;
    }
    //ajouter le nombre d'elements
    (li->ref)++;
    printf("Element saisi a la fin avec succes \n\n");

}
void ajouter_produit_liste_debut(liste* li)
{
    noeud* E;
    E = saisirProduit();
    //cas d'une liste vide
    if(li->debut == NULL){
        li->debut = E;
        li->fin = E;
    }
    else{
        E->suivant = li->debut;
        li->debut = E;
    }
    //ajouter le nombre d'elements
    (li->ref)++;
    printf("Element ajoute au debut avec succes \n\n");

}
void ajouter_produit_liste_milieu(liste* li)
{
    int milieu = (li->ref)/2;
    noeud* courant ;
    //cas d'une liste vide
    if(li->debut == NULL){
        printf("la liste est vide, insertion au debut"); //on refait la verification est ce que c normal?
        ajouter_produit_liste_debut(li);
        return;
    }
    noeud* E;
    E = saisirProduit();
    
        courant = li->debut; //ici courant stock l'adresse de debut
        for(int i = 0; i<milieu-1 ; i++) {
            courant = courant->suivant;
        }
        E->suivant = courant->suivant;
        courant->suivant = E;
    
    if(E->suivant == NULL){
        printf("l'element est insere a la fin!\n");
        li->fin = E;
    }
    //augmenter le nombre d'elements
    (li->ref)++;
    printf("Element insere au milieu avec succes\n\n");
    return;
}
void affiherListeProduit(liste* li)
{
    if(li->debut==NULL){
        printf("liste vide\n");
        return;
    }
    noeud* ptr;
    ptr = li->debut;
    while(ptr !=NULL){
        printf("Nom : %s | Prix : %f | Quantite : %d\n\n",ptr->nom,ptr->prix,ptr->qte);
        ptr = ptr->suivant;
    }

}

void enregistrer_liste_produits(FILE* myFile,liste* li)
{
    myFile = fopen("produits.txt","w"); // ca ecrase tout fichier existant et cree si il n'existe pas
    if(myFile == NULL){
        perror("Erreur");
        exit(EXIT_FAILURE);
    }
    noeud* ptr;
    ptr = li->debut;
    if(ptr==NULL){
        printf("liste vide\n"
        "Retour Au Menu Principale...");
        return;
    }
    while(ptr != NULL){
        fprintf(myFile,"%s %f %d\n",ptr->nom,ptr->prix,ptr->qte);
        ptr = ptr->suivant;
    }
    fclose(myFile);
}

void trier_liste_produits(liste* li)

{
    if(li->debut==NULL){
        printf("liste vide\n");
        printf("Retour au Menu Principale \n\n");
        return;
    }
    noeud* i;
    noeud* j;
    noeud* tmp = malloc(sizeof(noeud));

    for( i=(li->debut) ; i!=NULL; i= (i->suivant) )
    {
    
        for(j= (i->suivant) ; j!=NULL; j= (j->suivant) )
        {
            if( (j->prix) < (i->prix) )
        {
            //echange mots
            strcpy((tmp->nom),(j->nom)); 
            strcpy((j->nom),(i->nom));
            strcpy((i->nom),(tmp->nom));

            //echange prix
            (tmp->prix) = (j->prix);
            (j->prix) = (i->prix);
            (i->prix) = (tmp->prix);

            //echange Qte
            (tmp->qte) = (j->qte);
            (j->qte) = (i->qte);
            (i->qte) = (tmp->qte);
        }
        }
        
    }
    printf("tri effectue\n");
    free(tmp);
}

noeud* trouver_produit_cher(liste*li)
{
if(li->debut==NULL){
        printf("liste vide\n");
        return NULL;
    }
float max;
noeud* i;
noeud* cou;
max = li->debut->prix;
cou = li->debut;
for(i = li->debut; i!=NULL; i = i->suivant )
{
    if(i->prix > max)
    {
        max = i->prix;
        cou = i;
    }
}
return cou;
}

void lireDepuisFichier(liste* li,FILE *file)
{

    file = fopen("produits.txt","r");
    if(file == NULL){
        perror("erreur");
        exit(EXIT_FAILURE);
    }
    noeud buffer;
        while(fscanf(file,"%s %f %d",buffer.nom, &buffer.prix,&buffer.qte) == 3)
    {
                noeud* ptr = creer_produit();
                strcpy(ptr->nom,buffer.nom);
                ptr->prix = buffer.prix;
                ptr->qte = buffer.qte;
                // deja faite dans la fct ptr->suivant = NULL;
                if(li->fin == NULL){
                    li->fin = li->debut = ptr;
                }
                else{
                    li->fin->suivant = ptr;
                    li->fin = ptr;
                }
    li->ref ++;       
    }   
        

    fclose(file);
    printf("fichier lis avec succes\n"); 
}

void libererListe(liste* li){
    noeud* prec;
    noeud* ptr;
    prec = NULL;
    ptr = li->debut;
    while(ptr!=NULL)
    {
        prec = ptr;
        ptr = ptr->suivant;
        free(prec);
    }
    li->debut = NULL;
    li->fin = NULL; 
    li->ref  = 0;
}
void main(void)
{
    liste* list;
    list = creer_liste_produits();
    FILE* myFile;
    label:
    printf(
    "-----------------------------------------------------\n"
    "Bienvenue dans programme de gestion de produits\n"
    "-----------------------------------------------------\n"
    "0. AFficher la liste de produits a partir de la liste\n"
    "-----------------------------------------------------\n"
    "1. Ajouter produit au debut \n"
    "-----------------------------------------------------\n"
    "2. Ajouter produit au milieu \n"
    "-----------------------------------------------------\n"
    "3. Ajouter produit a la fin \n"
    "-----------------------------------------------------\n"
    "4.Trier liste produits \n"
    "-----------------------------------------------------\n"
    "5. Afficher produit plus cher \n"
    "-----------------------------------------------------\n"
    "6. Enregistrer liste produits \n"
    "-----------------------------------------------------\n"
    "7. Charger depuis fichier \n"
    "-----------------------------------------------------\n"
    "Entrer n'importe quelle valeur pour quitter le programme \n"
    "-----------------------------------------------------\n"
);
int n;
int ans;
//choix de l'utilisateur

do
{ 
printf("Effectuer un choix : ");
scanf("%d",&ans); 
}while (ans<0 || ans> 9);

printf(
    "-----------------------------------------------------\n"
    "Choix effectue\n"
    "-----------------------------------------------------\n");
switch (ans)
{
case 0:
    affiherListeProduit(list);
    break;
case 1:
    ajouter_produit_liste_debut(list);
    break;
case 2:
    ajouter_produit_liste_milieu(list);
    break;
case 3:
    ajouter_produit_liste_fin(list);
    break;
case 4:
    trier_liste_produits(list);
    break;
case 5:
noeud* prod;
prod = trouver_produit_cher(list);
if(prod == NULL){
    break;
}
printf("l'adress du produit plus cher est : nom : %s | prix : %f | stock %d", prod->nom,prod->prix,prod->qte );
break;
case 6:
enregistrer_liste_produits(myFile,list);
break;
case 7:
lireDepuisFichier(list,myFile);
break;
default:
libererListe(list);
exit(1);
    break;
}
goto label;
}
