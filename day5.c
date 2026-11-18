#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  int64_t l, r;
  struct node_s * next;
  struct node_s * prev;
} node_t;

static void * readline(char * ptr, int len, FILE * f) {
  void * p = fgets(ptr, len, f);
  ptr[strlen(ptr) - 1] = 0;
  return p;
}

int main() {
  FILE * f = fopen("day5.input", "rb");

  node_t * list = NULL;
  
  int count = 0;
  int intervals = 1;
  char buf[1024];
  while (readline(buf, sizeof(buf), f)) {
    if (!buf[0]) {
      intervals = 0;
      continue;
    }

    if (intervals) {
      char * l = buf;
      char * r = strchr(buf, '-');
      *r++ = 0;

      assert(strlen(l) <= 18);
      assert(strlen(r) <= 18);

      node_t * n = malloc(sizeof(node_t));
      n->l = atoll(l);
      n->r = atoll(r);
      n->next = list;
      n->prev = NULL;
      if (list) list->prev = n;
      list = n;

      assert(n->l <= n->r);
    } else {
      int64_t val = atoll(buf);
      for (node_t * n = list; n; n = n->next) {
        if (n->l <= val && val <= n->r) {
          printf("%lld\n", val);
          count++;
          break;
        }
      }
    }
  }
  printf("= %d\n", count);

  for (node_t * a = list; a; a = a->next) {
    for (node_t * b = a->next; b; b = b->next) {
      if (a->r >= b->l && a->l <= b->r) {
        printf("merge %lld,%lld + %lld,%lld", a->l, a->r, b->l, b->r);
        if (b->l < a->l) a->l = b->l;
        if (b->r > a->r) a->r = b->r;
        printf(" = %lld,%lld\n", a->l, a->r);

        if (b->next) b->next->prev = b->prev;
        if (b->prev) b->prev->next = b->next;
        b = a;
      }
    }
  }

  int64_t part2 = 0;
  for (node_t * a = list; a; a = a->next) {
    part2 += a->r - a->l + 1;
  }
  printf("+ %lld\n", part2);
}
