#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tst.h"
#include "dict.h"
#define LINE_MAX_SIZE 350

int nextChar(FILE *dict) {
  int c;
  c = fgetc (dict);
  return c;
}

int nextCharLine(char *line, int *current) {
  if (line[(*current)] == '\0') return '\n';
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
  char *line;
  int current_character, index = 0;
  line = malloc(LINE_MAX_SIZE * sizeof (int));
  current_character = nextChar(dict);
  do {
    line[index++] = current_character;
    current_character = nextChar(dict);
  } while(current_character != '\n');
  line[index] = '\0';
  return line;
}

Word *extractOneWord(char *line) {
  Word *w;
  w = malloc(sizeof(Word));
  int current_character = 0, index = 0;
  int current = 0;
  w->deutsch = malloc(LINE_MAX_SIZE * sizeof(int));
  w->english = malloc(LINE_MAX_SIZE * sizeof(int));
  w->gen     = malloc(LINE_MAX_SIZE * sizeof(int));
  do {
    current_character = nextCharLine(line, &current);
    // if (current_character == '{') break;
    if (current_character == '\t') break;
    w->deutsch[index++] = current_character;
  } while(current_character != '\t');
  w->deutsch[index] = '\0';
  index = 0;
  // w->gen[index++] = '{';
  // do {
  //   current_character = nextCharLine(line, &current);
  //   if (current_character == '\n') break;
  //   w->gen[index++] = current_character;
  // } while(current_character != '}');
  // w->gen[index] = '\0';
  index = 0;
  do {
    current_character = nextCharLine(line, &current);
    if (current_character == '\t') current_character = nextCharLine(line, &current);
    if (current_character == '\n') break;
    w->english[index++] = current_character;
  } while(current_character != '\n');
  w->english[index] = '\0';

  free(line);
  return w;
}
FILE *mountDictionary(FILE *dict) {
  if (dict == NULL) { errorLog("Error dict is null", __LINE__, __func__); }

  Word *w;
  int i = 50;
  char *line;
  do {
  line = extractOneLine(dict);
  w = extractOneWord(line);

  printf("\n\n\n%s\n", w->deutsch);
  printf("%s\n", w->english);
  printf("%s\n\n\n", w->gen);
}while(i-- > 0);
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
