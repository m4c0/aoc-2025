#include <stdio.h>
#include <string.h>

int main() {
  FILE * f = fopen("day3.input", "rb");
  char buf[10240];

  int sum = 0;
  while (fgets(buf, sizeof(buf) - 1, f)) {
    buf[strlen(buf) - 1] = 0;

    int max_d = buf[0] - '0';
    int max_i = 0;
    for (int i = 1; buf[i + 1]; i++) {
      int v = buf[i] - '0';
      if (v <= max_d) continue;
      max_i = i;
      max_d = v;
    }

    int max_u = buf[++max_i] - '0';
    for (int i = max_i; buf[i]; i++) {
      int v = buf[i] - '0';
      if (v <= max_u) continue;
      max_i = i;
      max_u = v;
    }

    printf("%s -- %d%d\n", buf, max_d, max_u);
    sum += max_d * 10 + max_u;
  }
  printf("= %d\n", sum);
}
