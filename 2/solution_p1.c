#include <stdio.h>
#include <stdlib.h>

#define RED_LIMIT 12
#define GREEN_LIMIT 13
#define BLUE_LIMIT 14
#define IS_NUM(a) (a >= '0' && a <= '9')
#define ATOI(a) (a - '0')

struct revealed_set {
  int red;
  int blue;
  int green;
};

struct game {
  int id;
  int len;
  struct revealed_set* sets;
};

enum parse_state {
  game_num,
  block_num,
  block_color,
};

int is_good(struct game* cg) {
  for(int i = 0; i < cg->len; i++) {
    struct revealed_set* rs = &cg->sets[i];
    if(rs->blue > BLUE_LIMIT || rs->green > GREEN_LIMIT || rs->red > RED_LIMIT) {
      return 0;
    }
  }
  return 1;
}

int main() {
  FILE* file;
  file = fopen("input.txt", "r");
  char buffer[2];
  int sum = 0;

  int scratch = 0;
  struct game cur_game;
  cur_game.id = 0;
  cur_game.sets = 0;
  enum parse_state state = game_num; 
  

  while(fgets(buffer,sizeof(buffer),file)) {
    char c = buffer[0];

    switch(state) {
      case game_num: {
        if(c == ':') {
          printf("Game ID: %d\n", cur_game.id);
          cur_game.sets = malloc(10 * sizeof(struct revealed_set));
          cur_game.len = 1; 
          state = block_num;
        } else if (IS_NUM(c)) {
          cur_game.id = (cur_game.id * 10) + ATOI(c); 
        }
        break;
      }

      case block_num: {
        if(IS_NUM(c)) {
          scratch = (scratch * 10) + ATOI(c);
        } else if (scratch != 0) {
          state = block_color;
        }
      }

      case block_color: {
        switch(c) {
          case 'r': {
            if(scratch == 0) break;
            cur_game.sets[cur_game.len - 1].red = scratch;
            scratch = 0;
            break;
          } 

          case 'g': {
            if(scratch == 0) break;
            cur_game.sets[cur_game.len - 1].green = scratch;
            scratch = 0;
            break;
          }

          case 'b': {
            if(scratch == 0) break;
            cur_game.sets[cur_game.len - 1].blue = scratch;
            scratch = 0;
            break;
          };

          case ',': {
            state = block_num;
            scratch = 0;
            break;
          } 

          case ';': {
            struct revealed_set* rs = &cur_game.sets[cur_game.len-1];
            printf("Show %d: %d r, %d g, %d b\n", cur_game.len, rs->red, rs->green, rs->blue);
            cur_game.len++;
            scratch = 0;
            state = block_num;
            break;
          }

          case '\n': {
            struct revealed_set* rs = &cur_game.sets[cur_game.len-1];
            printf("Show %d: %d r, %d g, %d b\n", cur_game.len, rs->red, rs->green, rs->blue);
            if(is_good(&cur_game)) {
              sum += cur_game.id;
              printf("GOOD - %d\n", sum);
            }
            printf("\n");
            cur_game.id = 0;
            free(cur_game.sets);
            cur_game.sets = NULL;
            cur_game.len = 0;
            state = game_num;
            break;
          }
        }
      }

    } 
  }

  printf("Total Sum : %d\n", sum);
  return 0;
}
