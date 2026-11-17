#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_LEN 199933

typedef struct node_s {
  int64_t start;
  int64_t end;
  struct node_s * next;
  struct node_s * prev;
} node_t;

typedef struct hash_s {
  int64_t n;
  struct hash_s * next;
} hash_t;

static inline int64_t max(int64_t a, int64_t b) { return a > b ? a : b; }

static char buf[10240];
int main() {
  FILE * f = fopen("day2.input", "rb");
  fgets(buf, sizeof(buf), f);
  fclose(f);

  node_t * head = NULL;

  int maxlen = 0;
  int64_t maxval = 0;
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
    maxval = max(maxval, r);

    node_t * n = malloc(sizeof(node_t));
    *n = (node_t) {
      .start = l,
      .end   = r,
      .next  = head,
    };
    if (head && head->next) head->next->prev = n;
    head = n;
  }

  int64_t limit = 1;
  for (int i = 0; i < (maxlen >> 2); i++) limit *= 10;

  hash_t * hash[HASH_LEN] = {0};

  int64_t sum = 0;
  char buf[10240];
  for (int64_t i = 1; i < limit; i++) {
    char num[128];
    snprintf(num, sizeof(num) - 1, "%lld", i);
    strcpy(buf, num);

    for (int j = 0; j < 100; j++) {
      strcat(buf, num);

      int64_t id = atoll(buf);
      if (id > maxval) break;

      int64_t key = id % HASH_LEN;
      hash_t * h = hash[key];
      while (h && h->n != id) h = h->next;
      if (h) break;

      h = malloc(sizeof(hash_t));
      h->n    = id;
      h->next = hash[key];
      hash[key] = h;

      for (node_t * n = head; n; n = n->next) {
        if (n->start <= id && id <= n->end) {
          printf("%lld\n", id);
          sum += id;
        }
      }
    }
  }
  printf("=== %lld\n", sum);
}
