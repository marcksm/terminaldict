#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tst.h"
#include "dict.h"
#define LINE_MAX_SIZE 250

int nextChar(FILE *dict) {
  int c;
  c = fgetc (dict);
  return c;
}

int nextCharLine(char *line, int *current) {
  return line[(*current)++];
}
void errorLog(char *error, int line, const char *func_name) {
  printf ("%s", error);
  printf (" - function name: %s", func_name);
  printf (" - At line %d", line);
  exit(1);
}

FILE *openDictionaryData(FILE *dict) {
  dict = fopen("de-to-en.txt", "r");
  if (dict == NULL) { errorLog("Error dictionary not found", __LINE__, __func__); }
  return dict;
}
FILE *ignoreHeader(FILE *dict) {
  if (dict == NULL) { errorLog("Error dict is null", __LINE__, __func__); }
  int current_character;
  current_character = nextChar(dict);
  while (current_character == '#') {
    do {
      current_character = nextChar(dict);
    } while(current_character != '\n');
    current_character = nextChar(dict);
  }
  return dict;
}

char *extractOneLine(FILE *dict) {
  char *line, *buffer;
  int current_character, index = 0;
  buffer = malloc(LINE_MAX_SIZE * sizeof (int));
  current_character = nextChar(dict);
  do {
    buffer[index++] = current_character;
    current_character = nextChar(dict);
  } while(current_character != '\n');
  line = buffer;
  return line;
}
Word *extractOneWord(char *line) {
  Word *w;
  char *deutsch, *english, *gen;
  int current_character = 0, index = 0;
  int current = 0;
  deutsch = malloc(LINE_MAX_SIZE * sizeof(int));
  english = malloc(LINE_MAX_SIZE * sizeof(int));
  gen = malloc(LINE_MAX_SIZE * sizeof(int));
  printf("\n");
  do {
    current_character = nextCharLine(line, &current);
    if (current_character == '{') break;
    deutsch[index++] = current_character;
  } while(current_character != '{');
  printf ("%s\n", deutsch);
  index = 0;
  gen[index++] = '{';
  do {
    current_character = nextCharLine(line, &current);
    gen[index++] = current_character;
  } while(current_character != '}');
  printf ("%s\n", gen);
  index = 0;
  do {
    current_character = nextCharLine(line, &current);
    if (current_character == '\t') current_character = nextCharLine(line, &current);
    english[index++] = current_character;
  } while(current_character != '\n');
  printf ("%s\n", english);
  // w->deutsch = deutsch;
  // w->english = english;
  // w->gen = gen;
  //
  // free(line);
  return w;
}
FILE *mountDictionary(FILE *dict) {
  if (dict == NULL) { errorLog("Error dict is null", __LINE__, __func__); }

  Word *w;
  char *line;

  line = extractOneLine(dict);
  printf ("%s", line);

  w    = extractOneWord(line);
  // printf ("\n%s", w->english);
  return dict;
}

int main () {
  char *word1, *word2;
  FILE *dict = NULL;
  dict = openDictionaryData(dict);
  dict = ignoreHeader(dict);
  dict = mountDictionary(dict);
  fclose (dict);
  return 0;
}
