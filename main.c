#include "lib.h"

#include <
int main() {
    FILE * file = fopen("test.txt", "r+");
    make_ids(file);
    float my_grades[5] = {10, 10, 10, 10, 10};
    radd(file, "Hrach", my_grades);
    radd(file, "Davo", my_grades);
    radd(file, "Maria", my_grades);
    radd(file, "Suren", my_grades);
    radd(file, "Narine", my_grades);
    rprintf(file);
    rdelete(file, 1);
    printf("------\n");
    rprintf(file);
    fclose(file);
    file = NULL;
    return 0;
}