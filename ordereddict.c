#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ordereddict.h"

ordereddict* od_init_table() {
   ordereddict* od = malloc(sizeof(ordereddict)); 
   od->dict_kv = ht_init_table();
   od->dict_kh = ht_init_table();
   od->ll_head = NULL;
   od->ll_curr = NULL;
}

void od_delete_table(ordereddict* od) {
    ll_delete_list(od->ll_head);
    ht_delete_table(od->dict_kv);
    ht_delete_table(od->dict_kh);
    free(od);
}

void od_insert(ordereddict* od, const char* k, void* v) {
    ht_insert(od->dict_kv, k, v);    
    ll_node* node = ll_append_node(od->ll_curr, k);
    if (od->ll_head == NULL) {
        od->ll_head = node;
    }
    od->ll_curr = node;
    ht_insert(od->dict_kh, k, (void*)node);
}

void* od_search(ordereddict* od, const char* k) {
    return ht_search(od->dict_kv, k);
}

void od_delete(ordereddict* od, const char* k) {
    ll_node* node = (ll_node*)ht_search(od->dict_kh, k);
    ll_delete_node(node);
    ht_delete(od->dict_kv, k);
    ht_delete(od->dict_kh, k);
}

void od_print_kv(ordereddict* od) {
    ll_node* node = od->ll_head;
    puts("{");
    while (node != NULL) {
        printf("%s : %s,\n",
               node->value,
               (char*)ht_search(od->dict_kv, node->value));
        node = node->next;
    }
    puts("}");
}
