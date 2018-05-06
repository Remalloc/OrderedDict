#ifndef ORDEREDDICT_H
#define ORDEREDDICT_H

#include "hashtable.h"
#include "linkedlist.h"

typedef struct {
    hashtable* dict_kv;
    hashtable* dict_kh;
    ll_node* ll_head;
    ll_node* ll_curr;
} ordereddict;

ordereddict* od_init_table();
void od_delete_table(ordereddict* od);
void od_insert(ordereddict* od, const char* k, void* v);
void* od_search(ordereddict* od, const char* k);
void od_delete(ordereddict* od, const char* k);
void od_print_kv(ordereddict* od);

#endif
