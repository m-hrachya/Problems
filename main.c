#include "linked_list.h"

int main() {
    List * my_list;
    list_constructor(my_list);
    for (int i = 0; i < 5; ++i) {
        push_back(my_list, i);
    }
    print_node(my_list);
    printf("Size: %d\n", my_list->size);
    insert(my_list, 5, 14);
    
    List * my_copy = copy_list(my_list);
    eraze(my_list, 0);
    print_node(my_list);
    print_node(my_copy);
    destructor(&my_copy);
    destructor(&my_list);
    print_node(my_list);
    return 0;
}