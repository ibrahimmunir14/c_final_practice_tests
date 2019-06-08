#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
} Person;

Person *getPerson(void) {
    Person *person = (Person *) malloc(sizeof(Person));
    printf("Enter person's name: ");
    fflush(stdout);
    char buffer[50];
    fgets(buffer, 50, stdin);
    strncpy(person->name, strtok(buffer, "\n"), 50);
    printf("Enter person's age: ");
    fflush(stdout);
    scanf("%i", &person->age);
    fflush(stdin);
    return person;
}

Person *printPeople(Person **people, int numPeople) {
    for (int i = 0; i < numPeople; i++) {
        printf("Person %i: %s (%i)\n", i+1, people[i]->name, people[i]->age);
    }
}

void freePeople(Person **people, int numPeople) {
    for (int i = 0; i < numPeople; i++) {
        free(people[i]);
    }
    free(people);
}

int main(int argc, char **argv) {
    if (argc != 2) { return EXIT_FAILURE; }

    int numPeople = atoi(argv[1]);
    Person **people = calloc(numPeople, sizeof(Person *));
    
    for (int i = 0; i < numPeople; i++) {
        printf("Enter details for person #%i:\n", i+1);
        people[i] = getPerson();
        printf("\n");
    }

    printPeople(people, numPeople);
    freePeople(people, numPeople);
}