#ifndef HASHSET_H
#define HASHSET_H

#include <stddef.h>
#include <stdint.h>

typedef struct node {
  int8_t *data;
  struct node *next;
} node;

typedef struct HashSet {
  node **buckets;
  size_t size;
  size_t capacity;
  size_t type_size;
  size_t (*hash_func)(int8_t *key, size_t type_size);
} HashSet;

void init(HashSet *set, size_t type_size,
          size_t (*hash_func)(int8_t *key, size_t type_size));
void resize(HashSet *set);
void shrink(HashSet *set);
int contains(HashSet *set, int8_t *element);
int insert(HashSet *set, int8_t *element);
int set_remove(HashSet *set, int8_t *element);
void clear(HashSet *set);
void destroy(HashSet *set);

#endif
