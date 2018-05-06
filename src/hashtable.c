#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

#define ht_MINSIZE 8
#define ht_PERTURB_SHIFT 5

ht_entry ht_DEL_SENTINEL = {NULL, NULL, 0};

// Python 2.7 hash function
static long ht_hash(const unsigned char* s) {
    long x = *s << 7;
    int len = strlen(s); 
    while (*s) {
        x = (1000003 * x) ^ *s++;
    }
    return x ^ len; 
}

static ht_entry* ht_create_entry(const char* k, void* v) {
    ht_entry* e = malloc(sizeof(ht_entry)); 
    e->key = strdup(k);
    e->value = v;
    e->hash = ht_hash(k);
    return e;
}

static void ht_delete_entry(ht_entry* e) {
    free(e->key);
    free(e);
}

static hashtable* ht_create_table(int size) {
    hashtable* ht = malloc(sizeof(hashtable));
    ht->fill = 0;
    ht->used = 0;

    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;

    ht->mask = size;
    ht->table = (ht_entry**)calloc(ht->mask+1, sizeof(ht_entry*));
    return ht;
}

static void ht_resize(hashtable* ht, const int size) {
    hashtable* temp = ht_create_table(size);
    int prev_size = ht->mask + 1;
    ht_entry** entries = ht->table;
    while(--prev_size >= 0) {
        if (*entries != NULL && *entries != &ht_DEL_SENTINEL) {
            ht_insert_entry(temp, *entries);
        }
        *entries++;
    }
    ht->fill = ht->used;

    ht->mask = temp->mask;    
    free(ht->table);
    ht->table = temp->table;
    free(temp);
}

static void ht_insert_entry(hashtable* ht, ht_entry* e) {
    if ((ht->fill * 100) / (ht->mask + 1) > 66) {
        if (ht->used < 50000) {
            ht_resize(ht, ht->used*4);
        } else {
            ht_resize(ht, ht->used*2);
        }
    } 

    int i = e->hash;
    int perturb = e->hash;
    ht_entry* temp = ht->table[i & ht->mask];
    while (temp != NULL) {
        if (temp != &ht_DEL_SENTINEL &&
            strcmp(temp->key, e->key) == 0) {
            ht_delete_entry(temp);
            ht->table[i & ht->mask] = e;
            return;
        }
        i = (5 * i) + 1 + perturb;
        perturb >>= ht_PERTURB_SHIFT;
        temp = ht->table[i & ht->mask];
    }
    ht->table[i & ht->mask] = e;
    ht->fill++;
    ht->used++;
}

hashtable* ht_init_table() {
    return ht_create_table(ht_MINSIZE);
}

void ht_delete_table(hashtable* ht) {
    int size = ht->mask + 1;
    ht_entry** entries = ht->table;
    while (--size >= 0) {
        if (*entries != NULL && *entries != &ht_DEL_SENTINEL) { 
            ht_delete_entry(*entries);
        }
        *entries++;
    }
    free(ht->table);
    free(ht);
}

void ht_insert(hashtable* ht, const char* k, void* v) {
    ht_entry* e = ht_create_entry(k, v);
    ht_insert_entry(ht, e);
}

void* ht_search(hashtable* ht, const char* k) {
    int i = ht_hash(k);
    int perturb = i;
    ht_entry* temp = ht->table[i & ht->mask];
    while (temp != NULL) {
        if (temp != &ht_DEL_SENTINEL &&
            strcmp(temp->key, k) == 0) {
            return temp->value;
        }
        i = (5 * i) + 1 + perturb;
        perturb >>= ht_PERTURB_SHIFT;
        temp = ht->table[i & ht->mask];
    }
    return NULL;
}

void ht_delete(hashtable* ht, const char* k) {
    int i = ht_hash(k);
    int perturb = i;
    ht_entry* temp = ht->table[i & ht->mask];
    while (temp != NULL) {
        if (temp != &ht_DEL_SENTINEL &&
            strcmp(temp->key, k) == 0) {
            ht_delete_entry(temp);
            ht->table[i & ht->mask] = &ht_DEL_SENTINEL;
            return;
        }
        i = (5 * i) + 1 + perturb;
        perturb >>= ht_PERTURB_SHIFT;
        temp = ht->table[i & ht->mask];
    }
    ht->used--;
}

void ht_print_kv(hashtable* ht) {
    int size = ht->mask + 1;
    ht_entry** entries = ht->table;
    puts("{");
    while (--size >= 0) {
        if (*entries != NULL && *entries != &ht_DEL_SENTINEL) {
            printf("%s : %s,\n", (*entries)->key, (char *)((*entries)->value));
        }
        *entries++;
    }
    puts("}");
}

//int main() {
//    hashtable* ht = ht_init_table();
//    char* s1 = strdup("asdf");
//    char* s2 = strdup("fdsa");
//    ht_insert(ht, "test", s1);
//    ht_insert(ht, "post", s2);
//    ht_print_kv(ht);
//    ht_delete_table(ht);
//    free(s1);
//    free(s2);
//}
