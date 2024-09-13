#include "double_linked_list.h"

void construct_node(Node ** node, int data) {
    *node = (Node *) malloc(sizeof(Node));
    (*node)->data = data;
    (*node)->next = NULL;
    (*node)->prev = NULL;
}
void construct_list(DLL** list) {
    (*list) = (DLL*) malloc(sizeof(DLL));
    (*list)->head = NULL;
    (*list)->tail = NULL;
}

void destroy_list(DLL** list) {
    if(!*list || !list || !(*list)->head) {
        printf("Nothing to destroy!\n");
        return;
    }
    Node * current;
    current = (*list)->head;
    while(current->next) {
        current = current->next;
        free(current->prev);
    }
    free(current);
    current = NULL;
    (*list)->head = NULL;
    (*list)->tail = NULL;
    free(*list);
    *list = NULL;
    return;
}

DLL* copy_list(DLL * src) {
    if(!src || !src->head || !src->tail) {
        printf("List is empty!\n");
        return (DLL*) NULL;
    }
    DLL * dest;
    construct_list(&dest);
    Node * current = src->head;
    while(current->next) {
        current = current->next;
        push_back(dest, current->prev->data);
    }
    push_back(dest, current->data);
    return dest;
}

void push_back(DLL* list, int data) {
    if(!list) {
        printf("List is empty!\n");
        return;
    }
    Node * node;
    construct_node(&node, data);
    if(!list->head) {
        list->head = node;
        list->tail = node;
        return;
    }
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    return;
}

void push_front(DLL* list, int data) {
    if(!list) {
        printf("List is empty!\n");
        return;
    }
    Node * node;
    construct_node(&node, data);
    if(!list->head) {
        list->head = node;
        list->tail = node;
        return;
    }
    list->head->prev = node;
    node->next = list->head;
    list->head = node;
    return;                   
}
void push_after(DLL* list, Node* node, int data) {
    if(!list) {
        printf("List is empty!\n");
        return;
    }
    Node * new_node;
    construct_node(&new_node, data);
    if(!node->next) {
        node->next = new_node;
        new_node->prev = node;
        list->tail = new_node;
        return;
    }
    new_node->next = node->next;
    new_node->prev = node->next->prev;
    node->next->prev = new_node;
    node->next = new_node;
    return;
}

int get_size(const DLL* list) {
    if(!list || !list->head || !list->tail) {
        return 0;
    }
    Node * current = list->head;
    int count = 0;
    while(current->next) {
        current = current->next;
        ++count;
    }
    return ++count;
}

void insert(DLL* list, int position, int data) {
    if(!list) {
        printf("List is empty!\n");
        return;
    }
    int size = get_size(list);
    if (position > size) {
        printf("Invalid position!\n");
        return;
    }
    if (position == 0) {
        push_front(list, data);
        return;
    }
    if (position == size) {
        push_back(list, data);
        return;
    }
    Node * current = list->head;
    for (int i = 1; i < position; ++i) {
        current = current->next;
    }
    push_after(list, current, data);
    return;
} 

void insert_before(DLL* list, Node* node, int data) {
    if(!list) {
        printf("List is empty!\n");
        return;
    }
    Node * new_node;
    construct_node(&new_node, data);
    if (!node->prev) {
        node->prev = new_node;
        new_node->next = node;
        list->head = new_node; 
        return;
    }
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;
    return;
} 

void remove_front(DLL* list) {
    if(!list || !list->head || !list->tail) {
        printf("List is empty!\n");
        return;
    }
    Node * tmp = list->head;
    list->head = tmp->next;
    list->head->prev = NULL;
    free(tmp);
    tmp = NULL;
    return;
}

void remove_back(DLL* list) {
    if(!list || !list->head || !list->tail) {
        printf("List is empty!\n");
        return;
    }
    Node * tmp = list->tail;
    list->tail = tmp->prev;
    list->tail->next = NULL;
    free(tmp);
    tmp = NULL;
    return;
}

void remove_node(DLL* list, Node * node) {
    if(!list || !list->head || !list->tail) {
        printf("List is empty!\n");
        return;
    }
    if(!node->next) {
        remove_back(list);
        return;
    }
    if(!node->prev) {
        remove_front(list);
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return;
}
