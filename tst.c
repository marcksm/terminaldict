#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tst.h"



Node *root;

List *get (char *key) {
  Node *x = get1 (root, key, 0);
  if (x == NULL) return NULL;
  readall(x);
  return (x->val);
}

Node *get1 (Node *x, char *key, int d) {
  if (x == NULL) return NULL;
  int c = key[d];
  if (c < x->c) { return get1 (x->left, key, d);}
  else if (c > x->c) { return get1 (x->right, key, d);}
  else if (d < strlen(key)-1) { return get1 (x->mid, key, d+1);}
  else { return x; }
}

void put (char *key, char *val) {
  root = &(*put1 (root, key, val, 0));
}

Node *put1 (Node *x, char *key, char *val, int d) {
  // printf("%d - %c, ", d, key[d]);
  int c = key[d];
  if (x == NULL) {
    Node *y = malloc (sizeof (Node));
    x = y;
    x->c = c;
  }
  // printf("%c", c);
  if (c < x->c) { x->left = put1(x->left,key,val,d); }
  else if (c > x->c) { x->right = put1(x->right,key,val,d);}
  else if (d < strlen(key) - 1) { x->mid = put1(x->mid, key, val, d+1);}
  else {
    List *novo = malloc (sizeof (List));
    List *p;
    p = (x->val);
    if (x->val == NULL) {
      novo->value = val;
      x->val = novo;
      x->key = key;
      return x;
    }
    while (p->next != NULL) {p = p->next; }
    p->next = novo;
    novo->value = val;

  }
  return x;
}

int contains (char *key) {
  return get(key) != NULL;
}

void printword (char *key) {

  List *lista = get(key);
  printf ("%s:\n", key);
  if (lista == NULL) return;
  printf ("\t\t%s\n",lista->value);
  while (lista->next != NULL) {
      lista = lista->next;
      printf ("\t\t%s\n",lista->value);
  }
}

void readall (Node *x) {
  if (x == NULL) return;
printNode (x);
  readall (x->left);
  //printf ("%c", *(&(x->key)[0]));

  readall (x->mid);
  readall (x->right);

}
 void printNode (Node *x) {
   List *lista = x->val;
   if (lista == NULL) return;
   printf ("%s:", x->key);
   printf ("\t\t%s\n",lista->value);
   while (lista->next != NULL) {
       lista = lista->next;
       printf ("\t\t%s\n",lista->value);
   }
 }
