#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ordereddict.h"

int main() {
    char* values[10];
    int i;
    char str_i[3];
    for (i = 0; i < 10; i++) {
        sprintf(str_i, "%d", i);
        strcat(str_i, "value");
        values[i] = strdup(str_i);
    }

    hashtable* ht = ht_init_table();
    for (i = 0; i < 10; i++) {
        sprintf(str_i, "%d", i);
        strcat(str_i, "k");
        ht_insert(ht, str_i, values[i]);
    }
    puts("Hash Table: 10 Elements");
    ht_print_kv(ht);
    ht_delete(ht, "4k");
    puts("Hash Table: 9 Elements");
    ht_print_kv(ht);
    ht_delete_table(ht);
    
    ordereddict* od = od_init_table();
    for (i = 0; i < 10; i++) {
        sprintf(str_i, "%d", i);
        strcat(str_i, "k");
        od_insert(od, str_i, values[i]);
    }
    puts("Ordered Dict: 10 Elements");
    od_print_kv(od);
    od_delete(od, "4k");
    puts("Ordered Dict: 9 Elements");
    od_print_kv(od);
    od_delete_table(od);

    for (i = 0; i < 10; i++) {
        free(values[i]);
    }
}
