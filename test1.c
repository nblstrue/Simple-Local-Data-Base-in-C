#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "saveInfos.txt" // within the same folder as the executable
#define STRUCT_ARGUMENTS 6
#define MAX_PERSON 99

typedef char CHAR50[50];
typedef enum {false, true} bool; // false = 0 and true = 1
typedef struct {
    int    age;
    float  income;
    float  weight;
    float  height;
    CHAR50 address;
    CHAR50 firstname;
    CHAR50 lastname;
    CHAR50 job;
    CHAR50 number;
    CHAR50 email;
    CHAR50 address;
} Person;
Person TABLE_PERSONS[MAX_PERSON];
int position_table = 0;

void line_break(char *str)
{
    str[strcspn(str, "\n")] = '\0'; // Removes the line break character from the string
}

void show_infos()
{
    /*
       -> Take all the data from the struct array and display it in the console
     */
}

void send_infos()
{
    /*
       -> Take all the data from the struct array and write it to the file
     */
}

void create_person()
{
    /*
       -> Ask the user for all the information about a person
       -> Store the information in the struct array
     */
}

void find_info(FILE *f, Person *p)
{
    CHAR50 text;
    bool found = false;
    /*
       -> Ask the user for a search term (name, firstname, job, number, email)
       -> Search through the struct array for matching entries
       -> Display the found entries
     */
}

void delete_file(FILE *f)
{
    char c;

    printf("\n\nAre you sure to erase ALL the content of the database ? (o/y) You wont be able to retrieve the data after this)\n");
    scanf(" %c", &c); while(getchar() != '\n');
    while(c != 'o' && c != 'n')
    {
        printf("\n\nERROR: invalid input value for choice (choice = %c)", c);
        printf("\n\nAre you sure to erase ALL the content of the database ? (o/y) You wont be able to retrieve the data after this\n");
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
            printf("\n\n---> Data successfully erased <---");
        }
    }
    else
    {
        printf("\n\n---> Data erasure cancelled <---");
    }
}

Person recup_infos()
{
    /*
       -> Take the infomations from the file and store them in the struct array
     */
}

void menu(FILE* fichier, Person *p)
{
   /*
    * The user should be able to choose between:
      -> Adding a person
      -> Displaying all persons
      -> Searching for a person
      -> Deleting all data
      -> Modifying a person's information
      -> Quitting the program
    */
}

int main()
{
    /*
       -> Create the file if it doesnt exist, or upload the content existing from the file to the struct array
       -> then do a loop of the menu until the user wants to quit
     */
    return 0;
}
