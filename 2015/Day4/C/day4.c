
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  unsigned char result[MD5_DIGEST_LENGTH];

  const char *str = "ckczppom";
  char buffer[255];
  int n = 0;
  char hex[255];
  while (1) {
    sprintf(buffer, "%d", n);
    char *new_str;
    new_str = malloc(strlen(str) + strlen(buffer) + 1);
    if (new_str == NULL) {
      printf("Error allocating memory to string\n");
      abort();
    }
    new_str[0] = '\0';
    strcat(new_str, str);
    strcat(new_str, buffer);
    MD5((unsigned char *)new_str, strlen(new_str), result);
    // for problem one is only 5 '%02x' here as we checking only 5 zeroes.
    sprintf(hex, "%02x%02x%02x%02x%02x%02x", result[0], result[1], result[2],
            result[3], result[4], result[5]);
    // for problem one is "00000" here.
    if (strncmp(hex, "0000000", 6) == 0) {
      printf("Found: %s\n", new_str);
      free(new_str);
      break;
    }
    free(new_str);
    n++;
  }

  return 0;
}
