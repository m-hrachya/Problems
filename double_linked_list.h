#ifndef DLL_
#define DLL_
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node * next;
    struct Node * prev;
} Node;

typedef struct DLL {
    Node * head;
    Node * tail;
} DLL;

void construct_node(Node**, int);
void construct_list(DLL**);
void destroy_list(DLL**);
DLL* copy_list(DLL *);
void push_back(DLL*, int);
void push_front(DLL*, int);
void push_after(DLL*, Node*, int);
void insert(DLL*, int, int);
int get_size(const DLL*);
void insert_before(DLL*, Node*, int);
void remove_front(DLL*);
void remove_back(DLL*);
void remove_node(DLL*, Node*);

#endif