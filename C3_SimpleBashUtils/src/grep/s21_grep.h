#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 4096

typedef struct Options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} Options;

void funcPatternFromFile(char *pattern, char *optarg);

void addNewPattern(char *pattern, char *optarg);

void printFunc(FILE *fileForSearch, char *currentFile, Options option,
               regex_t regEx, int singleFile);
#endif  //  SRC_GREP_S21_GREP_H_
