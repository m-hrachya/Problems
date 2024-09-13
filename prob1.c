#include <stdio.h>
#define NAMESIZE 50
#define AUTHORNAME 50

typedef struct Book {
        char name[NAMESIZE];
        char author[AUTHORNAME];
        int year;
    } Book;

void initialize(struct Book * book) {
    printf("Enter book name: ");
    scanf(" %[^\n]", book -> name);
    printf("Enter author name: ");
    scanf(" %[^\n]", book -> author);
    printf("Enter year: ");
    scanf("%d", &(book -> year));
    fflush(stdin);
    return;
}

void getNames(struct Book * book, int count) {
    for (int i = 0; i < count; ++i) {
        if((book[i]).name[0] == 'A' || (book[i]).name[0] == 'a') {
            puts((book[i]).name);
        }
    }
    return;
}

int main() {
    Book myBooks[3];
    for(int i = 0; i < 3; ++i) {
        printf("Book %d:   ----------------\n", i+1);
        initialize(&myBooks[i]);
    }
    getNames(&myBooks[0], 3);
    return 0;
}