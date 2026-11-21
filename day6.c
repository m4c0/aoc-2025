#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int colen(const char * str) {
  int res = 0;
  while (*str == ' ') {
    res++;
    str++;
  }
  while (*str >= '0' && *str <= '9') {
    res++;
    str++;
  }
  return res;
}

int main() {
  FILE * f = fopen("day6.sample", "rb");

  char buf[102400];
  fread(buf, 1, sizeof(buf), f);

  int lcount = 0;
  for (char * p = strchr(buf, '\n'); p; p = strchr(p + 1, '\n')) {
    *p = 0;
    lcount++;
  }

  int linelen = strlen(buf);

  char ** lines = malloc(sizeof(void *) * lcount);
  char * p = buf;
  for (int i = 0; i < lcount; i++) {
    lines[i] = p;
    p += strlen(p) + 1;
  }

  int64_t res = 0;
  while (linelen > 0) {
    int64_t nums[8] = {0};
    int clen = 0;
    for (int i = 0; i < lcount; i++) {
      int l = colen(lines[i]);
      if (l > clen) clen = l;
    }
    for (int i = 0; i < lcount; i++) {
      lines[i][clen] = 0;
      printf("[%s]", lines[i]);

      if (lines[i][0] == '*') {
        int64_t acc = 1;
        for (int j = 0; j < lcount - 1; j++) {
          acc *= nums[j];
        }
        res += acc;
      } else if (lines[i][0] == '+') {
        for (int j = 0; j < lcount - 1; j++) {
          res += nums[j];
        }
      } else {
        for (int j = 0; j < clen; j++) {
          if (lines[i][j] == ' ') continue;
          nums[j] = nums[j] * 10 + lines[i][j] - '0';
        }
      }

      lines[i] += clen + 1;
    }
    printf("\n");
    linelen -= clen + 1;
  }

  printf("= %lld\n", res);
}
