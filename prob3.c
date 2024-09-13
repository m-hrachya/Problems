#include <stdio.h>
#include <string.h>
#define MARK_NAME_SIZE 50
#define MODEL_NAME_SIZE 50

typedef struct Car {
    char mark[MARK_NAME_SIZE];
    char model[MODEL_NAME_SIZE];
    int year;
} Car;

void initializeCar(Car * car_obj) {
    printf("Enter car mark: ");
    scanf(" %[^\n]", car_obj -> mark);
    printf("Enter car model: ");
    scanf(" %[^\n]", car_obj -> model);
    printf("Enter release year: ");
    scanf("%d", &(car_obj -> year));
    return;
}

int getMercedesYear(const Car * car_objs, int count) {
    for (int i = 0; i < count; ++i) {
        if (!strcmp(car_objs[i].mark, "Mercedes")) {
            return car_objs[i].year;
        }
    }
    return -1;
}

int main() {
    Car my_cars[3];
    for (int i = 0; i < 3; ++i) {
        printf("Enter car N%d:-----------\n", i);
        initializeCar(&my_cars[i]);
    }
    printf("Mercedes: %d\n", getMercedesYear(my_cars, 3));
    return 0;
}