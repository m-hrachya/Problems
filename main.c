#include "double_linked_list.h"

int main() {
    DLL * dll;
    construct_list(&dll);
    push_back(dll, 10);
    push_back(dll, 20);
    push_after(dll, dll->head, 40);
    push_back(dll, 100);
    push_front(dll, 120);
    insert(dll, 2, 123);
    remove_node(dll, dll->tail);
    Node * current;
    int iter = 1;
    current = dll->head;
    while(current->next) {
        current = current->next;
        printf("%d: %d\n", iter++, current->prev->data);
    }
    printf("%d: %d\n", iter++, current->data);
     printf("Size: %d\n", get_size(dll));
    destroy_list(&dll);
    return 0;
}