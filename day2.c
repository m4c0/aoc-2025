#include <assert.h>
#include <stdio.h>
#include <string.h>

static char buf[10240];
int main() {
  FILE * f = fopen("day2.sample", "rb");
  fgets(buf, sizeof(buf), f);
  fclose(f);

  for (char * ptr = buf; *ptr; ptr += strlen(ptr) + 1) {
    char * pp = strchr(ptr, ',');
    if (pp) *pp = 0;
    pp = strchr(ptr, '\n');
    if (pp) *pp = 0;

    char * l = ptr;
    
    ptr = strchr(l, '-');
    assert(ptr);
    *ptr++ = 0;

    char * r = ptr;

    printf("-- [%s][%s]\n", l, r);
  }
}
