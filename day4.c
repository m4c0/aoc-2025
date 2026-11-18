#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enough to take an input line
#define LEN 200

static int ding(char ** l, int i, int j) {
  int n = 0;
  for (int di = -1; di <= 1; di++) {
    for (int dj = -1; dj <= 1; dj++) {
      if (!di && !dj) continue;
      if (l[i + di][j + dj] == '.') continue;
      n++;
      if (n >= 4) return 0;
    }
  }
  return 1;
}

static int count(char ** l, char ** r, int size) {
  int res = 0;
  for (int i = 1; i <= size; i++) {
    for (int j = 1; j <= size; j++) {
      int valid = 0;
      if (l[i][j] == '@') valid = ding(l, i, j);
      r[i][j] = valid ? '.' : l[i][j];
      printf("%c", valid ? 'x' : l[i][j]);
      if (valid) res++;
    }
    printf("\n");
  }
  return res;
}

static void * readline(char * ptr, int len, FILE * f) {
  void * p = fgets(ptr + 1, len, f);
  ptr[strlen(ptr) - 1] = 0;
  return p;
}

int main() {
  FILE * f = fopen("day4.input", "rb");

  char ** l = malloc(LEN * sizeof(void *));
  char ** r = malloc(LEN * sizeof(void *));
  for (int i = 0; i < LEN; i++) {
    l[i] = malloc(LEN + 1);
    r[i] = malloc(LEN + 1);
  }

  int size = 0;
  while (readline(l[size + 1], LEN, f)) size++;

  for (int j = 0; j < size + 2; j++) {
    l[0][j] = r[0][j] = '.';
    l[size + 1][j] = r[size + 1][j] = '.';
    l[j + 1][0] = r[j + 1][0] = '.';
    l[j + 1][size + 1] = r[j + 1][size + 1] = '.';
    l[j + 1][size + 2] = r[j + 1][size + 2] = 0;
  }

  int sum = 0;
  int n;
  while ((n = count(l, r, size))) {
    sum += n;
    char ** tmp = r;
    r = l;
    l = tmp;

    printf("%d (%d)\n\n", n, sum);
  }
}
