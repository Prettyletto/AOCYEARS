#include <stdint.h>
#include <stdio.h>

int64_t problem_one(FILE *source) {
  rewind(source);
  int64_t sum = 0;
  int buffer;
  while ((buffer = fgetc(source)) != EOF) {
    if (buffer == '(') {
      sum++;
    } else if (buffer == ')') {
      sum--;
    }
  }

  return sum;
}

int64_t problem_two(FILE *source) {
  rewind(source);
  int64_t sum = 0;
  int64_t index = 0;
  int buffer;
  while ((buffer = fgetc(source)) != EOF) {
    if (sum == -1) {
      return index;
    }
    if (buffer == '(') {
      sum++;
      index++;
    } else if (buffer == ')') {
      sum--;
      index++;
    }
  }

  return index;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("%s Usage: [file.txt]\n", argv[0]);
    return 1;
  }
  FILE *source = fopen(argv[1], "r");
  if (source == NULL) {
    printf("Failed to open the files %s\n", argv[1]);
    return 2;
  }

  printf("%ld\n", problem_one(source));
  printf("%ld\n", problem_two(source));
  return 0;
}
