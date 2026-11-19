#include <stdio.h>
#include <string.h>

int main() {
  FILE * f = fopen("day6.sample", "rb");

  char buf[102400];
  fread(buf, 1, sizeof(buf), f);

  for (char * p = strchr(buf, '\n'); p; p = strchr(p + 1, '\n')) {
    *p = 0;
  }

  for (char * p = buf; p; p += strlen(p) + 1) {
    printf("%s\n", p);
  }
}
