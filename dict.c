#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tst.h"

int main () {
  FILE *dict = NULL;
  dict = fopen("de-en.txt", "r");
  int c = 0, count = 0;
  char *buff1 = NULL, *buff2= NULL, *buff3 = NULL, *newbuffer = NULL;
  char *word, *word1, *word2;
  c = fgetc (dict);
  int length = 0, length1 = 0, length2 = 0, length3 = 0;

  word1 = malloc (sizeof (int));
  word2 = malloc (sizeof (int));
  do {
    count++;
    //if (count > 1200000) break;
    //printf ("%d\n",c);
    buff1 = malloc (45 * sizeof (int));
    buff2 = malloc (45 * sizeof (int));
    buff3 = malloc (5 * sizeof (int));
    while ('\t' != c) {
      if (c == EOF) break;
      buff1[length1] = c;
      buff1[length1 + 1] = '\0';
      c = fgetc (dict);
      length1++;
    }
    while (c == '\t') { c = fgetc (dict); }
    length1 = 0;
    while ('\n' != (c)) {
      if (c == EOF) break;
      buff2[length2] = c;
      buff2[length2 + 1] = '\0';
      c = fgetc (dict);
      if (c == '\t') break;
      length2++;
    }
    length2 = 0;
    while (c == '\t') { c = fgetc (dict); }
    while ('\n' != (c)) {
      if (c == EOF) break;
      if (c == '\t') break;
      buff3[length3] = c;
      buff3[length3 + 1] = '\0';
      c = fgetc (dict);
      if (c == '\t') break;
      length3++;
    }
    length3 = 0;
    while (c == '\n') { c = fgetc (dict); }
    put(buff1, buff2);
    //printf ("%s\n", get(buff1));
    //printf ("[%s]\n", buff2);
    if (c == EOF) break;
    //free (buff1);
    //free (buff2);
    //free (buff3);
  } while (1);
  while (1) {
    word = malloc (300 * sizeof (int));
    c = getc (stdin);
    while (c != '\n') {
      word[length] = c;
      word[length + 1] = '\0';
      length++;
      c = getc (stdin);
    }
    printf ("APALAVRA EH:%s\n",word);
    printword (word);
    length = 0;
    free (word);
  }

  return 0;
}
