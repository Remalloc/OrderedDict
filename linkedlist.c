#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

ll_node* ll_append_node(ll_node* prev, const char* v) {
    ll_node* node = malloc(sizeof(ll_node));
    node->value = strdup(v);
    node->next = NULL;
    if (prev == NULL) {
        node->prev = NULL;
        return node;
    }
    prev->next = node;
    node->prev = prev;
    return node;
}

void ll_delete_node(ll_node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node->value);
    free(node);
}

void ll_delete_list(ll_node* head) {
    ll_node* node = head;
    ll_node* temp;
    while (node != NULL) {
        temp = node->next;
        free(node->value);
        free(node);
        node = temp;
    }
}

void ll_print_v(ll_node* head) {
    ll_node* node = head;
    puts("[");
    while (node != NULL) {
        printf("%s,\n", node->value);
        node = node->next;
    }
    puts("]");
}
