#include "lib.h"

int all_ids[MAX_ID_COUNT];
int awailable_ids[MAX_ID_COUNT];

void make_ids(FILE * file) {
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < MAX_ID_COUNT; ++i) {
        all_ids[i] = i;
        awailable_ids[i] = 1;
    }
    int count_of_students = 0;
    Student test_student;
    while(fread(&test_student, sizeof(Student), 1, file)) {
        ++count_of_students;
    }
    for (int i = 0; i < count_of_students; ++i) {
        awailable_ids[i] = 0;
    }
    return;
}

int get_available_id() {
    for (int i = 0; i < MAX_ID_COUNT; ++i) {
        if (awailable_ids[i]) { 
            awailable_ids[i] = 0;
            return all_ids[i];
        }
    }
    return -1;
}

void radd(FILE * file, const char * name, float * grades) {
    if (!file || !name || !grades) {
        printf("Invalid arguments!\n");
        exit(EXIT_FAILURE);
    }
    Student new_student;

    strcpy(new_student.name, name);
    new_student.id = get_available_id();
    for (int i = 0; i < GRADES_COUNT; ++i) {
        new_student.grades[i] = grades[i];
    }
    fseek(file, 0, SEEK_END);
    fwrite(&new_student, sizeof(new_student), 1, file);
    fflush(file);
    return;
}

Student * rnsearch(FILE * file, const char * name) {
    fseek(file, 0, SEEK_SET);
    Student * test_student = (Student *) malloc(sizeof(Student));

    while(fread(test_student, sizeof(Student), 1, file)) {
        if (!strcmp(name, test_student->name)) {
            printf("Name: %s\n", test_student->name);
            printf("ID: %d\n", test_student->id);
            printf("Grades: ");
            for (int i = 0; i < GRADES_COUNT; ++i) {
                printf("%.2f ", test_student->grades[i]);
            } printf("\n");
            goto END_LABEL;
        }
    }
    printf("No matches found!\n");

END_LABEL:
    return test_student;
}

Student * risearch(FILE * file, const int id) {
    fseek(file, 0, SEEK_SET);
    Student * test_student = (Student *) malloc(sizeof(Student));

    while(fread(test_student, sizeof(Student), 1, file)) {
        if (test_student->id == id) {
            printf("Name: %s\n", test_student->name);
            printf("ID: %d\n", test_student->id);
            printf("Grades: ");
            for (int i = 0; i < GRADES_COUNT; ++i) {
                printf("%.2f ", test_student->grades[i]);
            } printf("\n");
            goto END_LABEL;
        }
    }
    printf("No matches found!\n");

END_LABEL:
    return test_student;
}

void rupdate(FILE * file, const int old_id, const char * new_name, float * new_grades) {
    fseek(file, 0, SEEK_SET);
    Student test_student;
    while (fread(&test_student, sizeof(Student), 1, file)) {
        if (test_student.id == old_id) {
            strcpy(test_student.name, new_name);
            for (int i = 0; i < GRADES_COUNT; ++i) {
                test_student.grades[i] = new_grades[i];
            }
            goto END_LABEL;
        }
    }
    printf("No matches found!\n");
    return;
END_LABEL:
    fseek(file, -(sizeof(Student)), SEEK_CUR);
    fwrite(&test_student, sizeof(Student), 1, file);
    return;
}

void rprintf(FILE * file) {
    fseek(file, 0, SEEK_SET);
    Student test_student;
    while (fread(&test_student, sizeof(Student), 1, file)) {
        printf("Name: %s, ID: %d\n", test_student.name, test_student.id);
    }
    return;
}

void rdelete(FILE * file, int id) {
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    Student test_student;
    while (fread(&test_student, sizeof(Student), 1, file)) {
        if (test_student.id == id) {
            fseek(file, -1 * (sizeof(Student)), SEEK_CUR);
            int position = ftell(file); 
            fseek(file, sizeof(Student), SEEK_CUR);
            int needed_size = file_size - ftell(file);
            char * buf = (char *) malloc(sizeof(char) * needed_size);
            fread(buf, needed_size, 1, file);
            fseek(file, position, SEEK_SET);
            fwrite(buf, needed_size, 1, file);
            ftruncate(fileno(file), position + needed_size);
            fseek(file, position, SEEK_SET);
            while(fread(&test_student, sizeof(Student), 1, file)) {
                test_student.id = id;
                ++id;
                fseek(file, -(sizeof(Student)), SEEK_CUR);
                fwrite(&test_student, sizeof(Student), 1, file);
            }
            printf("Done!\n");
            goto END_LABEL;
        }
    }
    printf("No matches found!\n");
END_LABEL:
    return;
}