#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void * readline(char * ptr, int len, FILE * f) {
  void * p = fgets(ptr, len, f);
  ptr[strlen(ptr) - 1] = 0;
  return p;
}

int main() {
  FILE * f = fopen("day7.input", "rb");
  
  int res = 0;

  char buf[1024];

  int rays[1024] = {0};

  readline(buf, sizeof(buf), f);
  for (int i = 0; buf[i]; i++) {
    if (buf[i] == 'S') rays[i] = 1;
  }

  while (readline(buf, sizeof(buf), f)) {
    for (int i = 0; buf[i]; i++) {
      if (buf[i] != '^') continue;
      if (rays[i] == 0) continue;

      res++;
      if (i > 0) rays[i - 1] = 1;
      rays[i] = 0;
      rays[i + 1] = 1;
    }
  }

  printf("%d\n", res);
}
