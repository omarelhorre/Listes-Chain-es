//sunday 7:52 AM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//definition des structures
typedef struct noeud{
    struct noeud* precedent;
    char nom[50];
    float prix;
    int quantite;
    struct noeud* suivant;
}noeud;

typedef struct list{
    noeud* debut;
    noeud* fin;
    int nef;
}list;

noeud* creer_produit(void){
    noeud* E = malloc(sizeof(noeud));
    if(E==NULL) exit(EXIT_FAILURE);
    E->nom[0] = '\0';
    E->prix = 0;
    E->suivant = NULL;
    E->quantite = 0;
    E->precedent= NULL;
    return(E);
}

list* creer_liste_produits(void){
    list *li = malloc(sizeof(list));
    if(li==NULL) exit(EXIT_FAILURE);
    li->debut = NULL;
    li->fin = NULL;
    li->nef = 0;
    printf("liste cree avec succes\n\n");
    return li;
}
noeud* saisir_produit(void)
{
    noeud* E1 = creer_produit();
    printf("entrer le nom du produit : ");
    scanf("%s",E1->nom);
    printf("entrer le prix : ");
    scanf("%f",&E1->prix);
    printf("entrer le stock : ");
    scanf("%d",&E1->quantite);
    printf("element lit avec succes\n\n");
    return E1;

}
void ajouter_produit_liste_debut(list* li){
    noeud* ptr = saisir_produit();
    if(li->fin == NULL)
    {
        printf("liste vide");
        li->debut = li->fin = ptr;
    }
    else
    {
         ptr->suivant = li->debut;
         li->debut->precedent = ptr;
         li->debut = ptr;
        }
    li->nef++;
    printf("element ajoute avec succes\n\n");
}

void ajouter_produit_liste_fin(list* li){
    noeud* ptr = saisir_produit();
    if(li->fin == NULL)
    {
        printf("liste vide, Insertion au debut");
        li->debut = li->fin = ptr;
    }
    else
    {
         ptr->precedent = li->fin;
         li->fin->suivant = ptr;
         li->fin = ptr;
        }
    li->nef++;
    printf("element ajoute avec succes\n\n");
}

int ajouter_produit_liste_milieu(list* li){
    int milieu;
    /* if(li->fin == NULL)
    {
        printf("Insertion au milieu impossible, veuillez remplir la liste d'abord : \n ");
        ajouter_produit_liste_debut(li);

    }
    else{ */
    milieu = (li->nef / 2);
    noeud* courant;
    courant = li->debut;
    if(li->nef < 2){
        printf("aucun element ou un seul existe dans la liste\n\n");
        ajouter_produit_liste_fin(li); 
        return 0;
    }
    noeud* ptr = saisir_produit();
    for (int i=0; i<milieu-1; i++){
        courant = courant->suivant;
    }
    ptr->suivant = courant->suivant;
    ptr->precedent = courant;
    courant->suivant->precedent = ptr;
    courant->suivant = ptr;
   // }
    li->nef ++;
    printf("element ajoute avec succes\n\n");
    return 1;
}
void afficher_liste_produits(list* li){
    noeud* ptr;
    ptr = li->debut;
    if(ptr==NULL){
        printf("liste vide retour au menu princiapale\n\n");
        return;
    }
    printf("NULL\n");
    while(ptr != NULL){
    printf("Nom : %s | prix : %f | stock : %d\n",ptr->nom,ptr->prix,ptr->quantite);
    ptr = ptr->suivant;
}
    printf("NULL\n");
    printf("liste afficher avec succes\n\n");

}

void afficher_liste_produits_inv(list* li){
    noeud* ptr;
    ptr = li->fin;
    if(ptr==NULL){
        printf("liste vide retour au menu princiapal\n\n");
        return;
    }
    printf("NULL\n");
    while(ptr != NULL){
    printf("Nom : %s | prix : %f | stock : %d\n",ptr->nom,ptr->prix,ptr->quantite);
    ptr = ptr->precedent;}
    printf("NULL\n\n");
    
}

void enregistrer_liste_produits(list *li,FILE* file){
    if(li->debut == NULL){
        printf("liste vide\n\n");
        return;
    }
    file = fopen("produits.txt","w");
    if(file == NULL){
        perror("Erreur");
        exit(EXIT_FAILURE);
    }
    noeud* ptr;
    ptr = li->debut;
    while(ptr !=NULL){
        fprintf(file,"%s %f %d",ptr->nom,ptr->prix,ptr->quantite);
        ptr=ptr->suivant;
    }
    fclose(file);
    printf("liste enregistre\n\n");
}
void lire_liste_produits(list *li,FILE* file){
    file = fopen("produits.txt","r");
    if(file == NULL){
        perror("Erreur");
        exit(EXIT_FAILURE);
    }
    //j'evite a alouer une autre case
    noeud buffer;
    noeud* precedent;

    //pas le meme traitement que le TP;
    while( fscanf(file,"%s %f %d",buffer.nom,&buffer.prix,&buffer.quantite) == 3){
        noeud* ptr = creer_produit();
        strcpy(ptr->nom, buffer.nom);
        ptr->prix = buffer.prix;
        ptr->quantite = buffer.quantite;
        if(li->fin == NULL){
            li->debut = li->fin = ptr;
        }
        else{
            li->fin->suivant = ptr;
            ptr->precedent = li->fin;
            li->fin = ptr;
        }
        li->nef ++;
    }
    fclose(file);
    printf("Liste charge avec succes\n\n");
}

//trier liste des produits par leurs prix

void trier_liste_produits(list* li){
    if(li->fin == NULL)
    {
        printf("Liste vide\n"
        "Retour au Menu principale\n\n");
        return;
    }
    noeud tmp;
    noeud* i;
    noeud* j;
    
    for(i = li->debut ; i!= NULL; i=i->suivant){
        for(j=i->suivant; j!=NULL; j=j->suivant){
            if(i->prix > j->prix){
                strcpy(tmp.nom,j->nom);
                tmp.prix = j->prix;
                tmp.quantite = j->quantite;

                strcpy(j->nom,i->nom);
                j->prix = i->prix;
                j->quantite = i->quantite;

                strcpy(i->nom,tmp.nom);
                i->prix = tmp.prix;
                i->quantite = tmp.quantite;

            }
        }
    }
}

noeud*  trouver_produit_cher(list* li){
    if (li->debut == NULL)
    {
        printf("list vide\n"
        "Retour au menu principale...\n\n");
        return NULL;
    }
    
    noeud* plus_cher;
    noeud* ptr;
    ptr = li->debut;
    plus_cher = ptr;
    while(ptr != NULL)
    {
        if(ptr->prix > plus_cher->prix)
         {
            plus_cher = ptr;
        }
        ptr = ptr->suivant;
        
    }
    return plus_cher;
}

void libererListe(list* li){
    noeud* ptr;
    noeud* prec;
    prec = NULL;
    ptr= li->debut;
    while(ptr!=NULL){
        prec = ptr;
        ptr = ptr->suivant;
        free(prec);
    }
    li->debut = NULL;
    li->fin = NULL;
    li->nef = 0;
}

void main(void)
{
    list* list;
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
    "4. Trier liste produits \n"
    "-----------------------------------------------------\n"
    "5. Afficher produit plus cher \n"
    "-----------------------------------------------------\n"
    "6. Enregistrer liste produits \n"
    "-----------------------------------------------------\n"
    "7. Charger depuis fichier \n"
    "-----------------------------------------------------\n"
    "8. Nouvelle option : Afficher la liste en inverse \n"
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
    afficher_liste_produits(list);
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
printf("l'adress du produit plus cher est : nom : %s | prix : %f | stock %d", prod->nom,prod->prix,prod->quantite );
break;
case 6:
enregistrer_liste_produits(list,myFile);
break;
case 7:
lire_liste_produits(list,myFile);
break;
case 8:
afficher_liste_produits_inv(list);
break;
default:
libererListe(list);
free(list);
exit(1);
    break;
}
goto label;
}
