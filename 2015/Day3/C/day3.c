#include <hashset.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
  int x;
  int y;
} Point;

size_t hash_point(int8_t *point, size_t size) {
  Point *p = (Point *)point;
  size_t hash = 17;
  hash = hash * 31 + p->x;
  hash = hash * 31 + p->y;
  return hash;
}

void problem_one(HashSet *set, int buffer, int *x, int *y) {
  switch (buffer) {
  case '>':
    (*x)++;
    break;
  case '<':
    (*x)--;
    break;
  case '^':
    (*y)++;
    break;
  case 'v':
    (*y)--;
    break;
  default:
    break;
  }
  Point *point = malloc(sizeof(Point));
  point->x = *x;
  point->y = *y;
  insert(set, (int8_t *)point);
  free(point);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("%s Usage: [file path]\n", argv[0]);
    return 1;
  }
  FILE *source = fopen(argv[1], "r");
  if (source == NULL) {
    printf("Failed openning file %s\n", argv[1]);
    return 2;
  }
  HashSet set;
  init(&set, sizeof(Point), hash_point);
  int buffer;
  int x = 0;
  int y = 0;
  int x1 = 0;
  int y1 = 0;
  int i = 0;
  while ((buffer = fgetc(source)) != EOF) {
    if (buffer == '\0') {
      break;
    }
    if (i == 0) {
      problem_one(&set, buffer, &x, &y);
      i = 1;
    } else if (i == 1) {
      problem_one(&set, buffer, &x1, &y1);
      i = 0;
    }
  }

  printf("%ld", set.size);
  destroy(&set);
  fclose(source);
  printf("\n");
  return 0;
}
