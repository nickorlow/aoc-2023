#include <stdio.h>
#include <stdlib.h>

#define IS_NUM(a) (a >= '0' && a <= '9')
#define ATOI(a) (a - '0')
#define WIN_NUMS 10 
#define NUM_CARDS 202 
#define FILE_NAME "input.txt"


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
  file = fopen(FILE_NAME, "r");
  char buffer[2];
  int output = 0;

  int* wc_hist = malloc(sizeof(int) * NUM_CARDS);
  int card_idx;

  int scratch = 0;
  int wc = 0;
  int index = 0;
  int* winning_nums = malloc(sizeof(int) * WIN_NUMS);
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
      wc_hist[card_idx] = wc;
      card_idx++;
      scratch = 0;
      wc = 0;
      index = 0;
      cur_state = newline;
    } else if (c == '|') {
      cur_state = our_numbers;
    }
  }

  int* won_cards = malloc(sizeof(int) * NUM_CARDS);

  for(int i = 0; i < NUM_CARDS; i++) {
    won_cards[i] = 1;
  }

  for(int i = 0; i < NUM_CARDS; i++) {
    for(int j = 1; (i+j) < NUM_CARDS && j <= wc_hist[i]; j++) {
      won_cards[i+j] += won_cards[i];
    }
  }

  int sum = 0;
  for(int i = 0; i < NUM_CARDS; i++) {
    printf("%d: %d \n", i+1, won_cards[i]);
    sum += won_cards[i];
  }
  printf("sum: %d \n", sum);

  return 0;
}
