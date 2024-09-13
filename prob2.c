#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NMSIZE 25
#define LNMSIZE 25


typedef struct Person {
    char name[NMSIZE];
    char lastName[LNMSIZE];
    int age;
    struct Date {
        int day;
        int month;
        int year;
    } Date;
} Person;

void getAge(struct Person * person) {
    person -> age = 2024 - (person -> Date).year;
    return;
}

Person getOldest(const struct Person * person, int count) {
    int maxAge = person[0].age;
    for (int i = 1; i < count; ++i) {
        maxAge = maxAge > person[i].age ? maxAge : person[i].age;
    }
    for (int i = 0; i < count; ++i) {
        if (person[i].age == maxAge) return person[i];
    }
    return person[0];
}

void initializePerson(struct Person * person) {
    printf("Enter name: ");
    scanf("%s", person -> name);
    printf("Enter last name: ");
    scanf("%s", person -> lastName);
    printf("Enter birthday in format day/month/year: ");
    scanf("%d/%d/%d", &(person -> Date).day, &(person -> Date).month, &(person -> Date).year);
    getAge(person);
    return;
}

void sortPeople(struct Person * people, int count) {
    int start = 0;
    int end = count - 1;
    while (start != end) {  // 124, 15, 46
        while ((people[start].age >= 18)) {
            if (start == end) goto EndLabel;
            Person temp = people[start];
            people[start] = people[end];
            people[end] = temp;
            --end;
            printf("Done, %d - start, %d i end\n", start, end);
        }
        if (start == end) goto EndLabel;
        ++start;
    }
EndLabel: return;
}

void removeOldPeople(struct Person * people, int * count) {
    for (int i = 0; i < (* count); ++i) {
        if (people[i].age >= 63) {
            printf("Sorry %s, you are too old! Bye...\n", people[i].name);
            for (int j = i; j < (* count) - 1; ++j) {
                people[j] = people[j + 1];
            }
            --i;
            --(*count);
        }
    }
    return;
}

int main() {
    int count = 0;
    printf("Enter people's count: ");
    scanf("%d", &count);
    Person * people = (Person *)malloc(sizeof(Person) * count);
    assert(people != NULL);
    for (int i = 0; i < count; ++i) {
        initializePerson(&people[i]);
    }
    for (int i = 0; i < count; ++i) {
        printf("%d) You are %s %s, you are %d year old!\n", i + 1, people[i].name, people[i].lastName, people[i].age);
    }
    Person OldestPerson = getOldest(&people[0], count);
    printf("Oldest person is %s %s, %d year's old!\n", OldestPerson.name, OldestPerson.lastName, OldestPerson.age);
    sortPeople(&people[0], count);
    for (int i = 0; i < count; ++i) {
        printf("%d) You are %s %s, you are %d year old!\n", i + 1, people[i].name, people[i].lastName, people[i].age);
    }
    removeOldPeople(&people[0], &count);

    for (int i = 0; i < count; ++i) {
        printf("%d) You are %s %s, you are %d year old!\n", i + 1, people[i].name, people[i].lastName, people[i].age);
    }

    free(people);
    people = NULL;
    return 0;
}