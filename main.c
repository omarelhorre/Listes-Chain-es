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
    li->debut = 0;
    li->fin = 0;
    li->ref = 0;
    return(li);
}
noeud* creer_produit(void)
{
    noeud* E1;
    E1 = malloc(sizeof(noeud));
    verifyNoeudAllocation(E1);
    E1->qte = 0;
    E1->prix = 0;
    E1->nom[0] = '\0'; //on initialise comme ca?
    E1->suivant = NULL;
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

}
void ajouter_produit_liste_milieu(liste* li)
{
    noeud* E;
    E = saisirProduit();
    int mileu = (li->ref)/2;
    noeud* courant ;
    //cas d'une liste vide
    if(li->debut == NULL){
        printf("la liste est vide, insertion au debut"); //on refait la verification est ce que c normal?
        ajouter_produit_liste_debut(li);
    }
    else{
        courant = li->debut; //ici courant stock l'adresse de debut
        for(int i = 0; i<mileu-1 ; i++) {
            courant = courant->suivant;
        }
        E->suivant = courant->suivant;
        courant->suivant = E;
    }
    if(E->suivant == NULL){
        printf("l'element est insere a la fin!\n");
        li->fin = E;
    }
    //augmenter le nombre d'elements
    (li->ref)++;
}
void affiherListeProduit(liste* li)
{
    if(li->debut==NULL){
        printf("liste vide\n");
    }
    noeud* ptr;
    ptr = li->debut;
    while(ptr !=NULL){
        printf("Le nom du produit est : %s\nPrix : %f\nQuantite: %d\n",ptr->nom,ptr->prix,ptr->qte);
        ptr = ptr->suivant;
    }

}

void enregistrer_liste_produits(FILE* myFile,liste* li)
{
    myFile = fopen("produits.txt","w"); // ca ecrase tout fichier existant et cree si il n'existe pas
    if(myFile == NULL){
        perror("Erreur");
    }
    noeud* ptr;
    ptr = li->debut;
    if(ptr==NULL){
        printf("liste vide\n");
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
}

noeud* trouver_produit_cher(liste*li)
{
if(li->debut==NULL){
        printf("liste vide\n");
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
printf("l'element ayant le plus grand prix est \nNom : %s\nPrix : %f\nQuantite : %d\n",cou->nom,cou->prix,cou->qte);
return cou;
}

void lireDepuisFichier(liste* li,FILE *file)
{
    file = fopen("produits.txt","r");
    noeud* buffer = (noeud*) malloc(sizeof(noeud));
    noeud* ptr;
    ptr=li->debut;
    buffer->suivant = NULL;
    if(li->fin == NULL ){
        printf("liste vide\n");
        printf("Ajout à la tete...\n");
        while(fscanf(file,"%s %f %d",buffer->nom, &buffer->prix,&buffer->qte) == 3)
    {
                strcpy(ptr->nom,buffer->nom);
                ptr->prix = buffer->prix;
                ptr->qte = buffer->qte;
                ptr = ptr->suivant;
    }   
        
    }
    else if(li->fin != NULL)
    ptr = ptr->suivant;
    {
    while(fscanf(file,"%s %f %d",buffer->nom, &buffer->prix,&buffer->qte) == 3)
    {
        strcpy(ptr->nom,buffer->nom);
        ptr->prix = buffer->prix;
        ptr->qte = buffer->qte;
        ptr = ptr->suivant;    
    }
}
    fclose(file);
    free(buffer);
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
trouver_produit_cher(list);
break;
case 6:
enregistrer_liste_produits(myFile,list);
break;
case 7:
lireDepuisFichier(list,myFile);
break;
default:
free(list);
exit(1);
    break;
}
goto label;
}
