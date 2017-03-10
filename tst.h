#ifndef TST_H_
#define TST_H_

typedef struct list {
  char *value;
  struct list *next;
} List;

typedef struct node {
  //char *value;
  List *val;
  char *key;
  int c;
  struct node *left, *right, *mid;
} Node;

List *get (char *key);

Node *get1 (Node *x, char *key, int d);

int length (char *string);

void put (char *key, char *val);

Node *put1 (Node *x, char *key, char *val, int d);

int contains (char *key);

void printword (char *key);

void readall (Node *x);

void printNode (Node *x);

#endif
