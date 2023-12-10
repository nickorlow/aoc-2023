#include <stdio.h>

int main() {
  FILE* file;
  file = fopen("input.txt", "r");
  char buffer[2];
  int output = 0;

  while (fgets(buffer, sizeof(buffer), file)) {
    char c = buffer[0]; 
  }

  printf("Output is: %d\n", output);
  return 0;
}
