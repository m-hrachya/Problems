#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node{
    int data;
    struct Node * next;
} Node;

typedef struct {
    Node * head;
    int size;
} List;

void push_back(List * list, int data);
void node_constructor(Node * node, int data);
void list_constructor(List * list);
void print_node(List * list);
List * copy_list(List * list);
void insert(List * list, int position, int data);
void push_front(List * list, int data);
void eraze(List * list, int pos);
int pop_back(List * list);
void destructor(List ** list);

#endif