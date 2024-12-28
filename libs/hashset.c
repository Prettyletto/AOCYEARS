#include "hashset.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void init(HashSet *set, size_t type_size,
          size_t (*hash_func)(int8_t *key, size_t type_size)) {
  set->buckets = calloc(8, sizeof(node *));
  if (set->buckets == NULL) {
    printf("couldn't initialize the set, aborting\n");
    abort();
  }
  set->capacity = 8;
  set->size = 0;
  set->type_size = type_size;
  set->hash_func = hash_func;
}

void resize(HashSet *set) {
  node **new_buckets = calloc(set->capacity * 2, sizeof(node *));
  if (new_buckets == NULL) {
    printf("problem in resizing the set aborting\n");
    abort();
  }
  for (int i = 0; i < set->capacity; i++) {
    node *tmp = set->buckets[i];
    while (tmp != NULL) {
      int index =
          set->hash_func(tmp->data, set->type_size) % (set->capacity * 2);
      node *next = tmp->next;
      tmp->next = new_buckets[index];
      new_buckets[index] = tmp;
      tmp = next;
    }
  }

  free(set->buckets);
  set->buckets = new_buckets;
  set->capacity *= 2;
}

void shrink(HashSet *set) {
  node **new_buckets = calloc(set->capacity / 2, sizeof(node *));
  if (new_buckets == NULL) {
    printf("problem in shrinking the set aborting\n");
    abort();
  }
  for (int i = 0; i < set->capacity; i++) {
    node *tmp = set->buckets[i];
    while (tmp != NULL) {
      int index =
          set->hash_func(tmp->data, set->type_size) % (set->capacity / 2);
      node *next = tmp->next;
      tmp->next = new_buckets[index];
      new_buckets[index] = tmp;
      tmp = next;
    }
  }

  free(set->buckets);
  set->buckets = new_buckets;
  set->capacity /= 2;
}

int contains(HashSet *set, int8_t *element) {
  int index = set->hash_func(element, set->type_size) % set->capacity;
  node *tmp = set->buckets[index];
  while (tmp != NULL) {
    if (memcmp(tmp->data, element, set->type_size) == 0) {
      return index;
    }
    tmp = tmp->next;
  }

  return -1;
}

int insert(HashSet *set, int8_t *element) {
  if (set->size >= set->capacity) {
    resize(set);
  }
  if (contains(set, element) != -1) {
    printf("Already on the set\n");
    return -1;
  }
  int index = set->hash_func(element, set->type_size) % set->capacity;
  node *insert_tmp = malloc(sizeof(node));
  insert_tmp->data = malloc(set->type_size);
  memcpy(insert_tmp->data, element, set->type_size);
  insert_tmp->next = set->buckets[index];
  set->buckets[index] = insert_tmp;
  set->size++;

  return 0;
}

int set_remove(HashSet *set, int8_t *element) {
  int index = contains(set, element);
  if (index == -1) {
    printf("Element is not on the set\n");
    return -1;
  }
  node *tmp = set->buckets[index];
  node *prev = NULL;
  while (tmp != NULL) {
    if (memcmp(tmp->data, element, set->type_size) == 0) {
      if (prev == NULL) {
        set->buckets[index] = tmp->next;
      } else {
        prev->next = tmp->next;
      }
      free(tmp->data);
      free(tmp);
      set->size--;
      break;
    }
    prev = tmp;
    tmp = tmp->next;
  }
  if (set->size > 0 && set->size < set->capacity / 4) {
    shrink(set);
  }

  return 0;
}

void clear(HashSet *set) {
  for (int i = 0; i < set->capacity; i++) {
    node *tmp = set->buckets[i];
    while (tmp != NULL) {
      node *next = tmp->next;
      free(tmp->data);
      free(tmp);
      tmp = next;
    }
    set->buckets[i] = NULL;
  }
  set->size = 0;
}

void destroy(HashSet *set) {

  clear(set);
  free(set->buckets);
}
