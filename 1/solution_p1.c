#include <stdio.h>

int main() {
  FILE* file;
  file = fopen("input.txt", "r");
  char buffer[2];
  int sum = 0;
  int first = -1;
  int second = -1;

  while (fgets(buffer, sizeof(buffer), file)) {
    char c = buffer[0]; 
    if (c >= '0' && c <= '9') {
      int num = c - '0';
      if (first == -1) {
        first = num;
      } else {
        second = num;
      }
    }
    if (c == '\n') {
      int os = sum;
      sum += first * 10;
      sum += second == -1 ? first : second;
      first = second = -1;
    }
  }

  printf("Total is: %d\n", sum);
  return 0;
}
