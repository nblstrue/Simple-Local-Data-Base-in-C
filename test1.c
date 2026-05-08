/*
 * ## Update V1.2 - Overhaul of the Project (December 2025)
 *
 * Will be using a struct array to store people in memory before writing them to the file
 * Overhaul of all the functions
 *  * recup_infos (adding Income, weight, height, job title, address)
 *  * send_infos (last function sending the full content of TABLE_PERSONS to the file)
 *  * show_infos (displaying all the content of TABLE_PERSONS in the console)
 *  * find_info (searching for a person in TABLE_PERSONS by any of their information)
 *  * delete_data (erasing all the content of the struct array and the file content)
 * Quality of life updates (updating ways of coding, small errors)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for usleep()
#define FILENAME "saveInfos.txt" // within the same folder as the executable
#define STRUCT_ARGUMENTS 6
#define MAX_PERSON 99

typedef char CHAR50[50];
typedef enum {false, true} bool; // false = 0 and true = 1
typedef struct {
    int      age;
    float    income;
    float    weight;
    float    height;
    long int number;
    bool     content;
    CHAR50   address;
    CHAR50   firstname;
    CHAR50   lastname;
    CHAR50   job;
    CHAR50   email;
} Person;
Person TABLE_PERSONS[MAX_PERSON];
int position_table = 0;
const char *begin_msg =
        "\033[1;36m╔══════════════════════════════════════════╗\n"
        "║        ★ Local DataBase System ★         ║\n"       
        "╚══════════════════════════════════════════╝\033[0m\n\n"
        "\033[1;32mWelcome! This program lets you manage and store personal records locally.\n"
        "You can add, view, find, or delete entries easily — perfect for small-scale data handling.\033[0m\n\n"
        "\033[1;36m╔═════════════════════════════╗\n"
        "║        ★ The Menu ★         ║\n"
        "╚═════════════════════════════╝\033[0m\n\n"
        "\033[1;32m-> Add a person to the database by enterung their name, age, contact info, eand much more\n"
        "-> Show all of the stored data currently saved in the database\n"
        "-> Find a specific person by an information or another detail\n"
        "-> Delete all stored data (⚠ irreversible!)\n"
        "-> Quit the program safely\033[0m\n\n";

void line_break(char *str)
{
    str[strcspn(str, "\n")] = '\0'; // Removes the line break character from the string
}

void find_person()
{
    CHAR50 search_term;

    printf("\n\nTo find someone, you will need to write an information related to that person : ");
    fgets(search_term, sizeof(search_term), stdin);
    line_break(search_term);

    for(int i = 0; i < position_table; i++)
    {
        if(strcmp(TABLE_PERSONS[i].firstname, search_term) == 0 || strcmp(TABLE_PERSONS[i].lastname, search_term) == 0 || atoi(search_term) == TABLE_PERSONS[i].number ||
           strcmp(TABLE_PERSONS[i].email, search_term) == 0 || strcmp(TABLE_PERSONS[i].job, search_term) == 0 || strcmp(TABLE_PERSONS[i].address, search_term) == 0)
        {
            printf("\nPerson found:\n");
            printf("Firstname: %s\n", TABLE_PERSONS[i].firstname);
            printf("Lastname: %s\n", TABLE_PERSONS[i].lastname);
            printf("Age: %d\n", TABLE_PERSONS[i].age);
            printf("Phone Number: %ld\n", TABLE_PERSONS[i].number);
            printf("Email: %s\n", TABLE_PERSONS[i].email);
            printf("Job Title: %s\n", TABLE_PERSONS[i].job);
            printf("Income: %.2f USD\n", TABLE_PERSONS[i].income);
            printf("Weight: %.2f kg\n", TABLE_PERSONS[i].weight);
            printf("Height: %.2f cm\n", TABLE_PERSONS[i].height);
            printf("Address: %s\n\n", TABLE_PERSONS[i].address);
            return;
        }
    }
}

void delete_file(FILE *f)
{
    char c;

    printf("\n\nAre you sure to erase ALL the content of the database ? (y/n) You wont be able to retrieve the data after this)\n");
    scanf(" %c", &c); while(getchar() != '\n'); // Clear input buffer
    while(c != 'y' && c != 'n')
    {
        printf("\n\nERROR: invalid input value for choice (choice = %c)", c);
        printf("\n\nAre you sure to erase ALL the content of the database ? (y/n) You wont be able to retrieve the data after this\n");
        scanf(" %c", &c); while(getchar() != '\n');
    }

    if(c == 'o')
    {
        f = freopen(FILENAME, "w", f);
        if (!f) {
            perror("ERROR: Could not open the new file after erasing the old data");
        }
        else
        {
            for(int i = 0; i < STRUCT_ARGUMENTS; i++)
            {
                TABLE_PERSONS[i] = (Person){0};
            }
            printf("\n\n---> Data successfully erased <---\n\n\n");
        }
    }
    else
    {
        printf("\n\n---> Data erasure cancelled <---");
    }
}

void exit_program(char *c, FILE* fichier)
{
    fflush(stdin);
    char end;
    printf("/n/nAre you sure you want to exit the program ? (y/n)\n");
    scanf("%c", &end); while(getchar() != '\n');
    while(end != 'y' && end != 'n')
    {
        printf("\n\nERROR: invalid input value for choice (choice = %c)", end);
        printf("\n\nAre you sure you want to exit the program ? (y/n)\n");
        scanf(" %c", &end); while(getchar() != '\n');
    }

    if(end == 'n')
        *c = '\0';
    else
    {
        printf("\nExiting the program...\n");
        for(int i = 0; i < position_table; i++)
        {
            fprintf(fichier, "%s %s %d %ld %s %s %.2f %.2f %.2f %s\n",
                    TABLE_PERSONS[i].firstname,
                    TABLE_PERSONS[i].lastname,
                    TABLE_PERSONS[i].age,
                    TABLE_PERSONS[i].number,
                    TABLE_PERSONS[i].email,
                    TABLE_PERSONS[i].job,
                    TABLE_PERSONS[i].income,
                    TABLE_PERSONS[i].weight,
                    TABLE_PERSONS[i].height,
                    TABLE_PERSONS[i].address);
        }
        *c = 'q';
    }
}

void add_person()
{
    int verif_num = 0;
    TABLE_PERSONS[position_table].content = true;

    printf("\n\nWrite your firstname : ");
    fgets(TABLE_PERSONS[position_table].firstname, sizeof(TABLE_PERSONS[position_table].firstname), stdin);
    line_break(TABLE_PERSONS[position_table].firstname);

    printf("\nWrite your lastname : ");
    fgets(TABLE_PERSONS[position_table].lastname, sizeof(TABLE_PERSONS[position_table].lastname), stdin);
    line_break(TABLE_PERSONS[position_table].lastname);

    printf("\nWrite your age : ");
    verif_num = scanf("%d", &TABLE_PERSONS[position_table].age); while(getchar() != '\n');
    while(verif_num != 1)
    {
        printf("ERROR: invalid input type given to an variable (age = %d)", TABLE_PERSONS[position_table].age);
        printf("/n/nWrite your age : ");
        verif_num = scanf("%d", &TABLE_PERSONS[position_table].age);
        while (getchar() != '\n');
    }

    verif_num = 0;
    fflush(stdin);

    printf("\nWrite your phone number (if your number has space, just write it without space): ");
    verif_num = scanf("%ld", &TABLE_PERSONS[position_table].number);
    while(verif_num != 1)
    {
        printf("ERROR: invalid input type given to an variable (age = %ld)", TABLE_PERSONS[position_table].number);
        printf("\nnWrite your phone number (if your number has space, just write it without space): ");
        verif_num = scanf("%ld", &TABLE_PERSONS[position_table].number);
        while (getchar() != '\n');
    }

    printf("\nWrite your email address : ");
    fgets(TABLE_PERSONS[position_table].email, sizeof(TABLE_PERSONS[position_table].email), stdin);
    line_break(TABLE_PERSONS[position_table].email);

    printf("\nWrite your job title : ");
    fgets(TABLE_PERSONS[position_table].job, sizeof(TABLE_PERSONS[position_table].job), stdin);
    line_break(TABLE_PERSONS[position_table].job);

    printf("\nWrite your income (in USD) : ");
    verif_num = scanf("%f", &TABLE_PERSONS[position_table].income); while(getchar() != '\n');
    while(verif_num != 1)
    {
        printf("\nERROR: invalid input type given to an variable (income = %f)", TABLE_PERSONS[position_table].income);
        printf("\nWrite your income (in USD) : ");
        verif_num = scanf("%f", &TABLE_PERSONS[position_table].income);
        while (getchar() != '\n');
    }

    printf("\nWrite your weight (in kg) : ");
    verif_num = scanf("%f", &TABLE_PERSONS[position_table].weight); while(getchar() != '\n');
    while(verif_num != 1)
    {
        printf("\nERROR: invalid input type given to an variable (weight = %f)", TABLE_PERSONS[position_table].weight);
        printf("\nWrite your weight (in kg) : ");
        verif_num = scanf("%f", &TABLE_PERSONS[position_table].weight);
        while (getchar() != '\n');
    }

    printf("\nWrite your height (in cm) : ");
    verif_num = scanf("%f", &TABLE_PERSONS[position_table].height); while(getchar() != '\n');
    while(verif_num != 1)
    {
        printf("\nERROR: invalid input type given to an variable (height = %f)", TABLE_PERSONS[position_table].height);
        printf("\nWrite your height (in cm) : ");
        verif_num = scanf("%f", &TABLE_PERSONS[position_table].height);
        while (getchar() != '\n');
    }

    printf("\nWrite your address : ");
    fgets(TABLE_PERSONS[position_table].address, sizeof(TABLE_PERSONS[position_table].address), stdin);
    line_break(TABLE_PERSONS[position_table].address);

    printf("\n---> Person %s %s added successfully to the database <---\n",
           TABLE_PERSONS[position_table].firstname,
           TABLE_PERSONS[position_table].lastname);

    position_table++;
}

void show_db()
{
    if(TABLE_PERSONS[0].content == false)
    {
        printf("\n\nThe database is empty.\n\n");
    }
    else
    {
        for(int i = 0; i < position_table; i++)
        {
            printf("\nPerson %d:\n", i + 1);
            printf("Firstname: %s\n", TABLE_PERSONS[i].firstname);
            printf("Lastname: %s\n", TABLE_PERSONS[i].lastname);
            printf("Age: %d\n", TABLE_PERSONS[i].age);
            printf("Phone Number: %ld\n", TABLE_PERSONS[i].number);
            printf("Email: %s\n", TABLE_PERSONS[i].email);
            printf("Job Title: %s\n", TABLE_PERSONS[i].job);
            printf("Income: %.2f USD\n", TABLE_PERSONS[i].income);
            printf("Weight: %.2f kg\n", TABLE_PERSONS[i].weight);
            printf("Height: %.2f cm\n", TABLE_PERSONS[i].height);
            printf("Address: %s\n\nn", TABLE_PERSONS[i].address);
        }
    }
}

char menu(FILE* f)
{
    char c_per = '\0';

    printf("\033[1;36m╔══════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;33m║              📋  MAIN MENU               ║\033[0m\n");
    printf("\033[1;36m╠══════════════════════════════════════════╣\033[0m\n");
    printf("║  \033[1;32m[a]\033[0m Add a new person                    ║\n");
    printf("║  \033[1;32m[s]\033[0m Show all persons                    ║\n");
    printf("║  \033[1;32m[f]\033[0m Find a person                       ║\n");
    printf("║  \033[1;32m[d]\033[0m Delete all data                     ║\n");
    printf("║  \033[1;32m[q]\033[0m Quit the program                    ║\n");
    printf("\033[1;36m╚══════════════════════════════════════════╝\033[0m\n");
    printf("\033[1;32mEnter choice :\033[0m");
    scanf(" %c", &c_per); while(getchar() != '\n');

    switch(c_per)
    {
        case 'a':
            add_person();
            break;
        case 's':
            show_db();
            break;
        case 'f':
            find_person();
            break;
        case 'd':
            delete_file(f);
            break;
        case 'q':
            exit_program(&c_per, f);
            break;
        default:
            printf("\nERROR: Invalid choice '%c'. Please try again.\n", c_per);
            break;
    }

    return c_per;
}

int main()
{
    char choice = '\0';
    FILE* fichier = fopen(FILENAME, "a+");
    if(fichier == NULL)
    {
        printf("ERROR: Could not open or create the file %s\n", FILENAME);
        exit(1);
    }
    else
    {
        for(int i = 0; i < MAX_PERSON; i++)
        {
            if(fscanf(fichier, "%s %s %d %ld %s %s %f %f %f %s/n",
                      TABLE_PERSONS[i].firstname,
                      TABLE_PERSONS[i].lastname,
                      &TABLE_PERSONS[i].age,
                      &TABLE_PERSONS[i].number,
                      TABLE_PERSONS[i].email,
                      TABLE_PERSONS[i].job,
                      &TABLE_PERSONS[i].income,
                      &TABLE_PERSONS[i].weight,
                      &TABLE_PERSONS[i].height,
                      TABLE_PERSONS[i].address) == 10)
            {
                position_table++;
            }
            else
            {
                break;
            }
        }
    }

    for (int i = 0; i < strlen(begin_msg); i++) {
        printf("%c", begin_msg[i]);
        fflush(stdout);
        usleep(10000); // 15ms delay per character
    }

    while(choice != 'q')
    {
        choice = menu(fichier);
    }

    fclose(fichier);

    return 0;
}
