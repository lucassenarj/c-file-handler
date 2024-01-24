#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Person {
    char name[50];
    int age;
    char gender;
} Person;

const int size = 10;
Person people[size];

int amount = 0;

bool createPerson();
void printPeople();
bool saveFile();
bool readFile();
bool saveBinFile();
bool readBinFile();

int main(void)
{
    int op;
    do {
        printf("\n1 - Create Person \n2 - Print People List \n3 - Store in text file\n4 - Read from text file\n");
        printf("5 - Store in bin file\n6 - Read from bin file\n0 - Exit\n");
        scanf("%d", &op);

        switch (op)
        {
        case 0:
            printf("\n\nExiting...\n\n");
            break;
        case 1:
            createPerson();
            break;
        case 2:
            printPeople();
            break;
        case 3: 
            saveFile();
            break;
        case 4: 
            readFile();
            break;
        case 5: 
            saveBinFile();
            break;
        case 6: 
            readBinFile();
            break;
        default:
            printf("\n\nInvalid option!\n\n");
            break;
        }
    } while (op != 0);

    return 0;
}

bool createPerson()
{
    if (amount >= size) {
        printf("ERROR: Max amount of people in file");
        return false;
    }

    //clean up keyboard buffer
    scanf("%*c");
    
    Person p;
    printf("Type name: ");

    /*
        use fgets instead of scanf because scanf only read until the first space
        and if user type more chars thant the data type is expecting
        the required memory overlaps the defined amount to fit all the characteres
        typed by the user. with fgets, if user type more then the characteres expected
        all the characters that overlaps the expected number it will be lost
    */
    fgets(p.name, 50, stdin);

    printf("Type age: ");
    scanf("%d", &p.age);

    //clean up keyboard buffer
    scanf("%*c");

    printf("Type gender: ");
    scanf("%c", &p.gender);

    // store person on people array
    people[amount] = p;

    // increase amount
    amount++;

    return true;
}

void printPeople()
{
    int i;
    for (i = 0; i < amount; i++)
    {
        printf("Name: %s", people[i].name);
        printf("Age: %d\t", people[i].age);
        printf("Gender: %c\n\n", people[i].gender);
    }
}

bool saveFile()
{
    int i;
    FILE *file = fopen("./files/people.txt", "w");
    if (file == NULL) {
        printf("ERROR: Unable to open the file\n");
        return false;
    }

    // first, store the amount of person store in file
    fprintf(file, "%d\n", amount);

    for (i = 0; i < amount; i++)
    {
        fprintf(file, "%s", people[i].name);
        fprintf(file, "%d\n", people[i].age);
        fprintf(file, "%c\n", people[i].gender);
    }

    // close file
    fclose(file);
    return true;
}

bool readFile()
{
    int i;
    FILE *file = fopen("./files/people.txt", "r");
    if (file == NULL) {
        printf("ERROR: Unable to open the file\n");
        return false;
    }

    /*
        read amount of person stored in file to global variable
        obs: we stored the variable with \n
        so we need to inform this when fetch from file
    */
    fscanf(file, "%d\n", &amount);

    for (i = 0; i < amount; i++)
    {
        Person p;
        /*
            use fgets instead of scanf to read string
            because scanf has issue with space when reading string
            so to avoid this, use fgets
        */
        fgets(p.name, 50, file);

        fscanf(file, "%d\n", &p.age);
        fscanf(file, "%c\n", &p.gender);

        // store person inside people array
        people[i] = p;
    }

    // close file
    fclose(file);
    return true;
}

bool saveBinFile()
{
    FILE *file = fopen("./files/people.bin", "wb");
    if (file == NULL) {
        printf("ERROR: Unable to open file");
        return false;
    }
    // amount of person that will be stored
    fprintf(file, "%d\n", amount);

    // 
    fwrite(people, sizeof(Person), amount, file);

    // close file
    fclose(file);

    return true;
}

bool readBinFile()
{
    FILE *file = fopen("./files/people.bin", "rb");
    if (file == NULL) {
        printf("ERROR: Unable to open file");
        return false;
    }

    // read amount of person stored on file
    fscanf(file, "%d\n", &amount);

    // read person from file
    fread(people, sizeof(Person), amount, file);

    // close file
    fclose(file);

    return true;
}
