# C Ordered Dictionary Example Implementation
**Author:** Andrew Quach

## Resources Used
- Chapter 18 of Beautiful Code By Andy Oram, Greg Wilson.
- James Routley's [Write a Hash Table](https://github.com/jamesroutley/write-a-hash-table) tutorial.

## Hash Table Implementation
This repo is an attempt at building Python's ordered dictionary in C. The hash table uses the Python 2.7 hash function.
```c
static long ht_hash(const unsigned char* s) {
    long x = *s << 7;
    int len = strlen(s);
    while (*s) {
        x = (1000003 * x) ^ *s++;
    }
    return x ^ len;
}
```
It also uses Python's special open addressing approach.
```c
int i = e->hash;
int perturb = e->hash;
...
// Temp is the bucket being checked
// ht_DEL_SENTINEL is a dummy value
while (temp != NULL) {
    if (temp != &ht_DEL_SENTINEL &&
    strcmp(temp->key, e->key) == 0) {
        ...
    }
    i = (5 * i) + 1 + perturb;
    // ht_PERTURB_SHIFT = 5
    perturb >>= ht_PERTURB_SHIFT;
    ...
}
```
Hash table resizes when >66% filled. Hash table quadruples if the amount of entries is under 50000. It doubles if greater or equal to 50000.
```c
if (ht->fill * 100) / (ht->mask + 1) > 66) {
    if (ht->used < 50000) {
        ht_resize(ht, ht->used*4);
    } else {
        ht_resize(ht, ht->used*2);
    }
}
```
The size of the table will always be in powers of 2 for fast modulus operations.

### Not Implemented:
Small dictionary optimizations and other special case optimizations are not implemented as of now.

## Ordered Dictionary Implementation

The ordered dictionary uses two hash tables and a doubly-linked list to maintain constant time insertion, searching, and deletion.

Hash table 1 (dict_kv) holds the standard key-value pairs. The linked list holds the keys in order of insertion. Hash table 2 (dict_kh) holds key-node address pairs. 

Insertion appends the key to the linked list [O(1)], adds the key-value pair to hash table 1 [O(1)], then adds the key-node address pair to hash table 2 [O(1)].

Searching functions exactly like a standard hash table [O(1)].

Deletion finds the node address from hash table 2 [O(1)], deletes the key from the linked list in constant time (knowing the node address) [O(1)], then deletes the entries from the two hash tables [O(1)].

## Usage

A main function is given to test out the source files.  To run the test binary, make sure you are in the root directory of the repository, then run:

    $ make
    $ bin/binary.out

To clean up:

    $ make clean
