#ifndef LIB
#define LIB

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define GRADES_COUNT 5
#define MAX_ID_COUNT 1000

typedef struct Student {
    char name[50];
    int id;
    float grades[GRADES_COUNT];
} Student;

void make_ids(FILE * file);
int get_available_id();

void radd(FILE * file, const char * name, float * grades);
Student * rnsearch(FILE * file, const char * name);
Student * risearch(FILE * file, const int id); 
void rupdate(FILE * file, const int old_id, const char * new_name, float * new_grades);
void rdelete(FILE * file, int id);
void rprintf(FILE * file);

#endif