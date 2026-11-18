#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enough to take an input line
#define LEN 200

static int count(char ** l) {
  int res = 0;
  for (int i = 1; l[1][i + 1]; i++) {
    int valid = 0;
    if (l[1][i] == '@') {
      int n = 0;
      for (int dx = -1; dx <= 1; dx++) {
        for (int y = 0; y <= 2; y++) {
          if (dx == 0 && y == 1) continue;
          if (l[y][i + dx] == '@') n++;
        }
      }
      valid = n < 4;
    }
    if (valid) res++;
    printf("%c", valid ? 'x' : l[1][i]);
  }
  printf("\n");
  return res;
}

static void * readline(char * ptr, int len, FILE * f) {
  void * p = fgets(ptr + 1, len, f);
  ptr[strlen(ptr)] = 0;
  ptr[strlen(ptr) - 1] = '.';
  return p;
}

int main() {
  FILE * f = fopen("day4.input", "rb");

  char * l[3];
  for (int i = 0; i < 3; i++) {
    l[i] = malloc(LEN + 1);
    for (int j = 0; j < LEN; j++) l[i][j] = '.';
    l[i][LEN] = 0;
  }

  int first = 1;
  int n = 0;
  while (readline(l[2], LEN, f)) {
    if (!first) n += count(l);

    first = 0;

    char * tmp = l[0];
    l[0] = l[1];
    l[1] = l[2];
    l[2] = tmp;
  }

  for (int j = 0; j < LEN; j++) l[2][j] = '.';
  n += count(l);

  printf("%d\n", n);
}
