#define ht_MINSIZE 8
#define ht_PERTURB_SHIFT 5

typedef struct {
    char* key;
    char* value;
    long hash;
} ht_entry;

typedef struct {
    int fill;
    int used;
    int mask;
    ht_entry** table;
} hashtable;

ht_entry ht_DEL_SENTINEL = {NULL, NULL, 0};

static long ht_hash(const unsigned char* s);
static ht_entry* ht_create_entry(const char* k, const char* v);
static void ht_delete_entry(ht_entry* e);
static hashtable* ht_create_table(int size);
static void ht_resize(hashtable* ht, const int size);
static void ht_insert_entry(hashtable* ht, ht_entry* e);

hashtable* ht_init_table();
void ht_delete_table(hashtable* ht);
void ht_insert(hashtable* ht, const char* k, const char* v);
char* ht_search(hashtable* ht, const char* k);
void ht_delete(hashtable* ht, const char* k);
