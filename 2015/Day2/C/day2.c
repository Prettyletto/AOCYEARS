#include <stdio.h>
#include <string.h>

int return_smallest_number(int n1, int n2, int n3) {

  if (n1 <= n2 && n1 <= n3) {
    return n1;
  } else if (n2 <= n3 && n2 <= n1) {
    return n2;
  } else if (n3 <= n1 && n3 <= n2) {
    return n3;
  }
  return n1;
}

long calculate_area(int length, int width, int height) {
  long result = 0;
  int lw = (length * width);
  int wh = (width * height);
  int hl = (height * length);
  int smallest_side = return_smallest_number(lw, wh, hl);

  result = (2 * lw + 2 * wh + 2 * hl) + smallest_side;

  return result;
}

long calculate_volume(int length, int width, int height) {
  long result = 0;
  int perimeter1 = 2 * (length + width);
  int perimeter2 = 2 * (width + height);
  int perimeter3 = 2 * (length + height);
  int smallest_perimeter =
      return_smallest_number(perimeter1, perimeter2, perimeter3);
  result = (length * width * height) + smallest_perimeter;

  return result;
}

long problem_one(char *line) {

  int length = 0;
  int width = 0;
  int height = 0;
  long sum = 0;

  sscanf(line, "%dx%dx%d", &length, &width, &height);
  sum = calculate_area(length, width, height);
  return sum;
}

long problem_two(char *line) {

  int length = 0;
  int width = 0;
  int height = 0;
  long sum = 0;

  sscanf(line, "%dx%dx%d", &length, &width, &height);
  sum = calculate_volume(length, width, height);
  return sum;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("%s Usage: [file directory] \n", argv[0]);
    return 1;
  }

  FILE *source = fopen(argv[1], "r");
  if (source == NULL) {
    printf("Could not open %s \n", argv[1]);
    return 2;
  }
  long sum = 0;
  char line[255];
  while (fgets(line, 255, source)) {
    sum += problem_two(line);
  }
  printf("%ld\n", sum);

  return 0;
}
