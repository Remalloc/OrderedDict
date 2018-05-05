typedef struct ll_node {
    char* value;
    struct ll_node* prev;
    struct ll_node* next;
} ll_node; 

ll_node* ll_append_node(ll_node* prev, char* v);
void ll_delete_node(ll_node* node);
void ll_delete_list(ll_node* head);
void ll_print_v(ll_node* head);
