#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
    int * vec;
    int size;
    int capacity;
} Vector;

int at(const Vector * vector, int pos) {
    return (vector->vec)[pos];
}
int empty(const Vector * vector) {
    for (int i = 0; i < vector->size; ++i) {
        if ((vector->vec)[i] != 0) {
            return 0;
        }
    }
    return 1;
}

void push_back(Vector * vector, int value) {
    if (vector -> capacity > vector -> size) {
        (vector -> vec)[vector->size] = value;
        vector -> size += 1;
    } else {
        vector -> vec = (int *) realloc(vector -> vec, sizeof(int) * vector -> capacity * 2);
        vector -> capacity *= 2;
        (vector -> vec)[vector->size] = value;
        vector -> size += 1;
    }
    return;
}

void pop_back(Vector * vector) {
    vector -> vec[vector -> size - 1] = 0;
    --(vector -> size);
    if (vector -> size <= (vector -> capacity) / 2) {
        vector -> vec = (int *) realloc(vector -> vec, sizeof(int) * (vector -> capacity / 2));
        vector -> capacity /= 2;
    }
    return;
}

int front(const Vector * vector) {
    return vector->vec[0];
}
int back(const Vector * vector) {
    return vector->vec[vector->size - 1];
}
int size(const Vector * vector) {
    return vector->size;
}
int capacity(const Vector * vector) {
    return vector->capacity;
}

void insert(Vector * vector, int pos, int value) {
    if (pos > vector->size) {
        printf("Invalid position!\n");
        return;
    }
    if (vector->size == vector->capacity) {
        vector -> vec = (int *) realloc(vector -> vec, sizeof(int) * vector -> capacity * 2);
        vector -> capacity *= 2;
    }
    for (int i = vector->size; i > pos; --i) {
        vector->vec[i] = vector->vec[i - 1];
    }
    vector->vec[pos] = value;
    ++(vector->size);
    return;
}

void erase(Vector * vector, int pos) {
    if (pos > vector->size) {
        printf("Invalid position!\n");
        return;
    }
    for (int i = pos; i < vector->size - 1; ++i) {
        vector->vec[i] = vector->vec[i + 1];
    }
    --vector->size;
    if (vector -> size <= (vector -> capacity) / 2) {
        vector -> vec = (int *) realloc(vector -> vec, sizeof(int) * (vector -> capacity / 2));
        vector -> capacity /= 2;
    }
    return;
}

void clear(Vector * vector) {
    vector->size = 0;
    return;
}

void shrink_to_fit(Vector * vector) {
    vector->vec = (int *) realloc(vector -> vec, sizeof(int) * vector->size);
    vector->capacity = vector->size;
    return;
}

void reserve(Vector * vector, size_t new_cap) {
    vector->vec = (int *) realloc(vector -> vec, sizeof(int) * (vector->capacity + new_cap));
    vector->capacity += new_cap;
    return;
}

void copy(const Vector * vector1, Vector * vector2) {
    int size = vector1->size < vector2->size ? vector1->size : vector2->size;
    for (int i = 0; i < size; ++i) {
        vector2->vec[i] = vector2->vec[i];
    }
    return;
}

int main() {
    Vector my_vec;
    my_vec.vec = (int *) malloc(sizeof(int) * 10);
    my_vec.size = 5;
    my_vec.capacity = 10;
    printf("%d\n", empty(&my_vec));
    for (int i = 0; i < my_vec.size; ++i) {
        scanf("%d", &my_vec.vec[i]);
    }
    printf("%d\n", at(&my_vec, 4));
    insert(&my_vec, 3, 12);
    for (int i = 0; i < my_vec.size; ++i) {
        printf("%d ", my_vec.vec[i]);
    }
    printf("\n");
    erase(&my_vec, 2);
    for (int i = 0; i < my_vec.size; ++i) {
        printf("%d ", my_vec.vec[i]);
    }
    printf("\n%d\n", empty(&my_vec));
    printf("%d\n", capacity(&my_vec));
    
    push_back(&my_vec, 10);
    reserve(&my_vec, 23);
    shrink_to_fit(&my_vec);
   printf("%d\n", capacity(&my_vec));
    return 0;
}