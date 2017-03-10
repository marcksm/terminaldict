#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trieR.h"



Node *root;

char *get (char *key) {
  Node *x = get1 (root, key, 0);
  if (x == NULL) return NULL;
  return (x->value);
}

Node *get1 (Node *x, char *key, int d) {
  if (x == NULL) return NULL;
  if (d == strlen(key)) return x;
  char c = key[d];
  return get1 (x->next[c], key, d + 1);
}

/*int length (char *string) {
  int size;
  for (int i = 0; string[i] != "\0"; i++) size++;
  return size;
}*/

void put (char *key, char *val) {

  root = &(*put1 (root, key, val, 0));

}

Node *put1 (Node *x, char *key, char *val, int d) {
  if (x == NULL) {
    Node *y = malloc (sizeof (Node));
    x = y;
  }

  if (d == strlen(key)) {x->value = val; return x; }
  char c = key[d];
  x->next[c] = put1 (x->next[c], key, val, d+1);
  return x;
}
