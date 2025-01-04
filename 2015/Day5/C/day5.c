#include <stdio.h>

int check_vowel(char c) {
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
    return 1;
  }
  return 0;
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
  char buffer[255];
  int sum = 0;
  while (fgets(buffer, 255, source)) {
    int i = 0;
    int vowels = 0;
    char current_char = '\0';
    int repeat = 0;
    int forbidden = 0;
    while (buffer[i] != '\0') {
      if (buffer[i] == current_char) {
        repeat++;
      }
      if ((current_char == 'a' && buffer[i] == 'b') ||
          (current_char == 'c' && buffer[i] == 'd') ||
          (current_char == 'p' && buffer[i] == 'q') ||
          (current_char == 'x' && buffer[i] == 'y')) {
        forbidden = 1;
      }
      current_char = buffer[i];

      vowels += check_vowel(buffer[i]);
      i++;
    }
    if (vowels >= 3 && repeat > 0 && forbidden <= 0) {
      sum++;
    }
  }
  rewind(source);
  while (fgets(buffer, 255, source)) {
    int i = 0;
    while (buffer[i] != '\0') {
    }
  }
  printf("%d\n", sum);
  return 0;
}
