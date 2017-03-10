#ifndef TRIER_H_
#define TRIER_H_

typedef struct node {
  char *value;
  int length;
  struct node *next[256];
} Node;

char *get (char *key);

Node *get1 (Node *x, char *key, int d);

int length (char *string);

void put (char *key, char *val);

Node *put1 (Node *x, char *key, char *val, int d);

#endif
