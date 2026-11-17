#include <stdio.h>
#include <string.h>

int main() {
  FILE * f = fopen("day3.input", "rb");
  char buf[10240];

  int64_t sum = 0;
  while (fgets(buf, sizeof(buf) - 1, f)) {
    buf[strlen(buf) - 1] = 0;

    int len = strlen(buf);

    int64_t num = 0;
    int max_i = -1;
    for (int j = 0; j < 12; j++) {
      int64_t max_d = buf[++max_i] - '0';
      for (int i = max_i; i < len - (12 - j - 1); i++) {
        int64_t v = buf[i] - '0';
        if (v <= max_d) continue;
        max_i = i;
        max_d = v;
      }
      num = num * 10 + max_d;
    }
    printf("%s -- %lld\n", buf, num);
    sum += num;
  }
  printf("= %lld\n", sum);
}
