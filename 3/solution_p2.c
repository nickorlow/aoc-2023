#include <stdio.h>
#include <stdlib.h>

#define IS_NUM(a) (a >= '0' && a <= '9')
#define IS_SYM(a) (a == '*')
#define ATOI(a) (a - '0')

struct grid_item {
  int x;
  int sx;
  int y;
  int val;
  int is_symbol;
  struct grid_item* next;
};

int intlen(int x) {
  if (x < 10) return 1;
  return 1 + intlen(x/10);
}

int main() {
  FILE* file;
  file = fopen("input2.txt", "r");
  char buffer[2];
  int cur_num = 0;
  int y = 0;
  int x = 0;

  struct grid_item first = {0, 0, 0, 0, NULL};
  struct grid_item* cur = &first;

  while (fgets(buffer, sizeof(buffer), file)) {
    char c = buffer[0]; 

    if (IS_NUM(c)) {
      cur_num = (cur_num * 10) + ATOI(c);
    } else {
      if(cur_num > 0) {
        struct grid_item* new_item = malloc(sizeof(struct grid_item));
        new_item->sx = x - intlen(cur_num);
        new_item->x = x-1;
        new_item->y = y;
        new_item->val = cur_num;
        new_item->is_symbol = 0;
        cur->next = new_item;
        cur = cur->next;
        cur_num = 0;
      }


      if (IS_SYM(c)) {
        struct grid_item* new_item = malloc(sizeof(struct grid_item));
        new_item->x = x;
        new_item->sx = 0;
        new_item->y = y;
        new_item->val = 0;
        new_item->is_symbol = 1;
        cur->next = new_item;
        cur = cur->next;
      } else if (c == '\n') {
        x = -1;
        y++;
      }
    }

    x++;
  }

  cur = &first;
  int sum = 0;

  while(cur != NULL) {
    if(cur->is_symbol) {
      struct grid_item* inner_cur = &first;
      int c = 0;
      int gr = 0;
      while (inner_cur != NULL) {
        if(!inner_cur->is_symbol) {
          int is_next_to = 0;

          int dy = abs(inner_cur->y - cur->y);

          is_next_to = dy <= 1 && cur->x >= inner_cur->sx - 1 && cur->x <= inner_cur->x + 1;

          if(is_next_to) {
            c++;
            gr = gr == 0 ? inner_cur->val : gr * inner_cur->val;
          }
        }
        inner_cur = inner_cur->next;
      }
      if (c == 2) sum += gr;
    }
    cur = cur->next;
  }

  printf("SUM: %d\n", sum);
  return 0;
}
