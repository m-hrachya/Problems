#include "linked_list.h"

void list_constructor(List * list) {
    if (list == NULL) {
        printf("List is empty!\n");
        return;
    }
    list->head = NULL;
    list->size = 0;
    return;
}

void destructor(List ** list) {
    if (*list == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node * current = (*list)->head;
    while(current->next) {
        Node * tmp = current;
        current = current->next;
        free(tmp);
        tmp = NULL;
    }
    free(current);
    current = NULL;
    (*list)->size = 0;
    *list = NULL;
}

void node_constructor(Node * node, int data) {
    if (node == NULL) {
        printf("Node is empty!\n");
        return;
    }
    node->data = data;
    node->next = NULL;
    return;
}

void push_back(List * list, int data) {
    if (list == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node * new_node = (Node *) malloc(sizeof(Node));
    node_constructor(new_node, data);
    if(list->head == NULL) {
        list->head = new_node;
    } else {
        Node * current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    ++list->size;
    return;
}
List * copy_list(List * list) {
    assert(list != NULL);
    List * copy_list = (List *) malloc(sizeof(List));
    assert(copy_list != NULL);
    list_constructor(copy_list);
    if(!list->head){
        return copy_list;
    } 
    Node * current = list->head;
    while (current){
        Node * temp = (Node *) malloc(sizeof(Node));
        assert(temp != NULL);
        push_back(copy_list,current->data);
        current = current->next;
    }
    return copy_list;
}
void insert(List * list, int position, int data){
        if (list == NULL) {
            printf("List is empty!\n");
            return;
        }
        if(position < 0 || position  > list->size){
                printf("wrong index for insert function\n");
                exit(EXIT_FAILURE);
        }
        Node * new_node = (Node *) malloc(sizeof(Node));
        node_constructor(new_node,data);
        Node * current = list->head;
        if(!position){
                list->head = new_node;
                new_node->next = current;
                ++(list->size);
                return;
        }
        for(int i = 0; i < position - 1; ++i){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        ++(list->size);
        return;
}
void push_front(List * list, int data){
        if (list == NULL) {
            printf("List is empty!\n");
            return;
        }
        Node  * new_node = (Node *) malloc(sizeof(Node));
        node_constructor(new_node, data);
        Node * current = list->head;
        list->head = new_node;
        list->head->next = current;
        ++list->size;
        return;
}

void eraze(List * list, int pos) {
    if (list == NULL) {
        printf("List is empty!\n");
        return;
    }
    if (pos == 0) {
        Node * tmp = list->head;
        list->head = list->head->next;
        free(tmp);
        tmp = NULL;
End:    --list->size;
        return;
    }
    if (pos < 0 || pos >= list->size) {
        printf("Invalid position!\n");
        return;
    }
    if (pos == list->size - 1) {
        Node * current = list->head;
        while (current -> next -> next) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
        goto End;
    }
    Node * current = list->head;
    for(int i = 0; i < pos - 1; ++i) {
        current = current->next;
    }
    Node * tmp = current->next;
    current->next = current->next->next;
    free(tmp);
    tmp = NULL;
    goto End;
}

void print_node(List * list) {
    if (list == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node * current = list->head;
    int incr = 1;
    while(current->next) {
        printf("%d: %d\n", incr++, current->data);
        current = current->next;
    }
    printf("%d: %d\n", incr, current->data);
    return;
}

int pop_back(List * list) {
    assert(list != NULL);
    Node * current = list->head;
     while(current->next) {
        current = current->next;
    }
    int res = current->data;
    eraze(list, list->size - 1);
    return res;
}