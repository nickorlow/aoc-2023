#include <stdio.h>

#define IS_NUM(a) (a >= '0' && a <= '9')
#define ATOI(a) (a - '0')
#define WIN_NUMS 10 


enum state {
  newline,
  spacer,
  winning_numbers,
  our_numbers
};


int ipow(int a, int b) {
  if (b == 0) return 1;
  return a * ipow(a, b-1);
}

int main() {
  FILE* file;
  file = fopen("input.txt", "r");
  char buffer[2];
  int output = 0;

  int scratch = 0;
  int wc = 0;
  int index = 0;
  int winning_nums[WIN_NUMS];
  enum state cur_state = newline;

  while (fgets(buffer, sizeof(buffer), file)) {
    char c = buffer[0]; 

    if(cur_state == spacer) {
      cur_state = winning_numbers;
      continue;
    }

    if(cur_state == newline) {
      if(c == ':') cur_state = spacer;
      continue;
    }

    if(IS_NUM(c)) {
      scratch = (scratch * 10) + ATOI(c);
    } else if ((c == ' ' || c == '\n') && scratch != 0) {

      if(cur_state == winning_numbers) {
        winning_nums[index] = scratch;
        index++;
      } else {
        for(int i = 0; i < WIN_NUMS; i++) {
          if(winning_nums[i] == scratch) {
            wc++;
          }
        }
      }

      scratch = 0;
    } 

    if (c == '\n') {
      int s = wc == 0 ? 0 : ipow(2, wc-1);
      printf("wc %d / score: %d\n", wc, s);
      output += s;
      scratch = 0;
      wc = 0;
      index = 0;
      cur_state = newline;
    } else if (c == '|') {
      cur_state = our_numbers;
    }
  }

  printf("Output is: %d\n", output);
  return 0;
}
