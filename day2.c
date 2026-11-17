#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  int64_t start;
  int64_t end;
  struct node_s * next;
  struct node_s * prev;
} node_t;

static inline int max(int a, int b) { return a > b ? a : b; }

static char buf[10240];
int main() {
  FILE * f = fopen("day2.input", "rb");
  fgets(buf, sizeof(buf), f);
  fclose(f);

  node_t * head = NULL;

  int maxlen = 0;
  for (char * ptr = buf; *ptr; ptr += strlen(ptr) + 1) {
    char * pp = strchr(ptr, ',');
    if (pp) *pp = 0;
    pp = strchr(ptr, '\n');
    if (pp) *pp = 0;

    maxlen = max(maxlen, strlen(ptr));
    int64_t l = atoll(ptr);
    
    ptr = strchr(ptr, '-');
    assert(ptr);
    *ptr++ = 0;

    maxlen = max(maxlen, strlen(ptr));
    int64_t r = atoll(ptr);

    node_t * n = malloc(sizeof(node_t));
    *n = (node_t) {
      .start = l,
      .end   = r,
      .next  = head,
    };
    if (head && head->next) head->next->prev = n;
    head = n;
  }

  int limit = 1;
  for (int i = 0; i < (maxlen >> 2); i++) limit *= 10;

  int64_t sum = 0;
  for (int i = 1; i < limit; i++) {
    char buf[1024];
    snprintf(buf, sizeof(buf) - 1, "%d%d", i, i);
    int64_t id = atoll(buf);

    for (node_t * n = head; n; n = n->next) {
      if (n->start <= id && id <= n->end) {
        printf("%lld\n", id);
        sum += id;
      }
    }
  }
  printf("=== %lld\n", sum);
}
