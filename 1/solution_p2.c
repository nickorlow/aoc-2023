#include <stdio.h>
#include <stdlib.h>

struct trie {
  char c;
  int r;
  int len;
  struct trie** next;
};

struct trie* get_next(struct trie* cur, struct trie* root, char n) {
  for(int i = 0; i < cur->len; i++) {
    if(cur->next[i]->c == n) {
      return cur->next[i];
    }
  }
  if(root == NULL) {
    return cur;
  } else {
    return get_next(root, NULL, n);
  }
}

void add_to_trie(struct trie* node, int i, char* word, int v) {
  if(word[i] == '\0') {
    node->r = v;
    return;
  } else {
    struct trie* next = get_next(node, NULL, word[i]);
    if(node == next) {
    struct trie* new_node = malloc(sizeof(struct trie));
    new_node->c = word[i];
    new_node->r = -1;
    new_node->next = malloc(10* sizeof(struct trie*));
    new_node->len = 0;
    add_to_trie(new_node, i + 1, word, v);
    node->next[node->len] = new_node;
    node->len++;
    } else {
      add_to_trie(next, i + 1, word, v);
    }
  }
}

struct trie* create_trie(char* words[], int vals[]) {
  struct trie* root = malloc(sizeof(struct trie));
  root->c = '\0';
  root->r = -1;
  root->len = 0;
  root->next = malloc(10 * sizeof(struct trie*));
  for(int i = 0; i < 9; i++) {
    add_to_trie(root, 0, words[i], vals[i]);
  }
  return root;
}

int main() {
  int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  char* words[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  struct trie* root = create_trie(words, vals);
  struct trie* cur = root;
  int line = 1;

  FILE* file;
  file = fopen("input.txt", "r");
  char buffer[2];
  int sum = 0;
  int first = -1;
  int second = -1;

  while (fgets(buffer, sizeof(buffer), file)) {
    char c = buffer[0]; 
    int num = -1;

    if (c >= '0' && c <= '9') {
      num = c - '0';
      cur = root;
    } else {
      cur = get_next(cur, root, c);

      if (cur->r != -1) {
        num = cur->r;
        cur = get_next(root, root, c);
      }
    }

    if(num != -1) {
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
      printf("%d: num is: %d\n", line, sum - os);
      line++;
    }
  }

  printf("Total is: %d\n", sum);
  return 0;
}
