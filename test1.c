/*---------------------------------------------------------VERSION FRANCAISE---------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "saveInfos.txt" // a trouver dans le dossier où se trouve 'test1.c'
#define STRUCT_ARGUMENTS 6
typedef char CHAR50[50];
typedef struct {
    int age;
    CHAR50 firstname;
    CHAR50 lastname;
    CHAR50 job;
    CHAR50 number;
    CHAR50 email;
} Person;

void line_break(char *str)
{
    str[strcspn(str, "\n")] = '\0'; // supprime le '\n' final si présent
}

/*void find_info(FILE* f, Person *p)
{
    char c;
    CHAR50 text;
    printf("Que cherchez vous: un Nom/Prenom (p), un Email (e), un Metier (m), un Numero (n) ou un Age (a)\n");
    scanf(" %c", c); line_break(c);

    while(c != 'p' && c != 'e' && c != 'm' && c != 'n' && c != 'a')
    {
        printf("\n\nERROR: invalid input value for choice (choice = %c)", c);
        printf("Que cherchez vous: un Nom/Prenom (p), un Email (e), un Metier (m), un Numero (n) ou un Age (a)\n");
        scanf(" %c", c); line_break(c);
    }

    printf("\nSi vous acces à une information qui est lie a ce que vous chercher, veillez l'ecrire ci-dessous\n-> ");
    fgets(text, sizeof(CHAR50), stdin); line_break(text);

    if(text[0] != '\0')
    {
        rewind(f); // remet le curseur au début du fichier

        while (fscanf(f, "%s %s %d %s %s %s\n",
                    p->firstname, p->lastname, &p->age, p->job, p->number, p->email) == 6)
        {
            for(int i = 0; i < STRUCT_ARGUMENTS; i++)

        }
    }
}*/

void delete_file(FILE *f)
{
    char c;

    printf("\n\nEtes vous sur de votre choix ? (o/n)(Les donnees seront TOUTES ecrasees mais le fichier restera existant)\n");
    scanf(" %c", &c); while(getchar() != '\n');
    while(c != 'o' && c != 'n')
    {
        printf("\n\nERROR: invalid input value for choice (choice = %c)", c);
        printf("\n\nEtes vous sur de votre choix ? (o/n)(Les donnees seront TOUTES ecrasees mais le fichier restera existant)\n");
        scanf(" %c", &c); while(getchar() != '\n');
    }

    f = freopen("saveInfos.txt", "w", f); // remplace l’ancien FILE* par un nouveau vide
    if (!f) {
        perror("Erreur lors de la réouverture du fichier");
    }
    else{ printf("\n\n---> Donnees ecrasees avec success <---"); }
}

void show_infos(FILE* f)
{
    Person p;
    rewind(f); // remet le curseur au début du fichier

    while (fscanf(f, "%s %s %d %s %s %s\n",
                  p.firstname, p.lastname, &p.age, p.job, p.number, p.email) == 6)
    {
        printf("\nPrenom et Nom: %s %s\nÂge: %d\nMétier: %s\nNuméro: %s\nEmail: %s\n",
               p.firstname, p.lastname, p.age, p.job, p.number, p.email);
    }
}

void send_infos(Person *p, FILE* f)
{
     fprintf(f, "%s %s %d %s %s %s\n",
            p->firstname,
            p->lastname,
            p->age,
            p->job,
            p->number,
            p->email);

    fflush(f);
}

Person recup_infos()
{
    Person p;
    int result;
    printf("Nous allons recuperer vos informations personnelles (50 caractères max par champ).\n");

    printf("Entrez votre prénom : ");
    fgets(p.firstname, sizeof(p.firstname), stdin);
    line_break(p.firstname); //enpèche 'fgets' de copier les sauts de lignes

    printf("Entrez votre nom de famille : ");
    fgets(p.lastname, sizeof(p.lastname), stdin);
    line_break(p.lastname);

    printf("Entrez votre métier : ");
    fgets(p.job, sizeof(p.job), stdin);
    line_break(p.job);

    printf("Entrez votre numéro de téléphone : ");
    fgets(p.number, sizeof(p.number), stdin);
    line_break(p.number);

    printf("Entrez votre email : ");
    fgets(p.email, sizeof(p.email), stdin);
    line_break(p.email);

    printf("Entrez votre âge : ");
    result = scanf("%d", &p.age);
    while (getchar() != '\n'); // vide le buffer

    while(result != 1)
    {
        printf("ERROR: invalid input type given to an variable (age = %d)\n\n", p.age);
        printf("Entrez votre âge : ");
        result = scanf("%d", &p.age);
        while (getchar() != '\n'); // vide le buffer
    }

    return p;
}

char menu(FILE* fichier, Person *p)
{
    char c;
    printf("\n\n ---> Que voulez-vous faire ? (a/l/q) <---");
    printf("\na. Ajouter une personne");
    printf("\nl. Lire le fichier");
    printf("\ns. Supprimer les données");
    //printf("\nc. Chercher quelqu'un avec une information");
    printf("\nq. Quitter");
    printf("\nVotre choix:"); scanf(" %c", &c); while (getchar() != '\n');

    while(c != 'a' && c != 'l' && c != 'q' && c != 's' && c != 'c')
    {
        printf("\n\nERROR: invalid input for choice ( variable: %c )", c);
        printf("\n\n ---> Que voulez-vous faire ? (a/l/s/q) <---");
        printf("\na. Ajouter une personne");
        printf("\nl. Lire le fichier");
        printf("\ns. Supprimer les données");
        //printf("\nc. Chercher quelqu'un avec une information");
        printf("\nq. Quitter");
        printf("\nVotre choix: "); scanf(" %c", &c); while (getchar() != '\n');
    }
    switch (c)
    {
        case 'a': *p = recup_infos();
                  send_infos(p, fichier);
                  break;

        case 'l': show_infos(fichier);
                  break;

        case 's': delete_file(fichier);
                  break;

        //case 'c': find_info(fichier, p);

        default:  printf("\n\nNous vous remercions d'avoir utilise notre programme ! A bientot !");
                  break;
    }

    return c;
}

int main()
{
    char choice;
    FILE* f = fopen(FILENAME, "a+");
    Person client;

    while(choice != 'q')
        choice = menu(f, &client);
    
    fclose(f);
    return 0;
}

/*---------------------------------------------------------ENGLISH VERSION---------------------------------------------------------------*/
