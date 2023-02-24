#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    char pattern[BUFFERSIZE] = {0};

    Options option = {0};
    int opt;
    while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
      switch (opt) {
        case 'e':
          option.e = 1;
          addNewPattern(pattern, optarg);
          break;
        case 'i':
          option.i = 1;
          break;
        case 'v':
          option.v = 1;
          break;
        case 'c':
          option.c = 1;
          break;
        case 'l':
          option.l = 1;
          break;
        case 'n':
          option.n = 1;
          break;
        case 'h':
          option.h = 1;
          break;
        case 's':
          option.s = 1;
          break;
        case 'o':
          option.o = 1;
          break;
        case 'f':
          option.f = 1;
          funcPatternFromFile(pattern, optarg);
          break;
        case '?':
          fprintf(stderr,
                  "usage: s21_grep: [-e:ivclnhsf:o] [pattern] [file]\n");
          break;
      }
    }

    argc -= optind;
    argv += optind;
    if (option.e == 0 && option.f == 0) {
      addNewPattern(pattern, argv[0]);
      argc--;
      argv++;
    }

    int singleFile = (argc == 1) ? 1 : 0;
    regex_t regEx;
    regcomp(&regEx, pattern,
            option.i ? REG_EXTENDED | REG_ICASE : REG_EXTENDED);
    FILE *fileForSearch = NULL;
    while (*argv) {
      fileForSearch = fopen(*argv, "r");
      if (fileForSearch) {
        printFunc(fileForSearch, *argv, option, regEx, singleFile);
      } else {
        if (!option.s) {
          fprintf(stderr, "s21_grep: %s: No such file or directory\n", *argv);
        }
      }
      argv++;
    }

    fclose(fileForSearch);
    regfree(&regEx);
  }
  return 0;
}

void addNewPattern(char *pattern, char *newPattern) {
  if (*pattern == '\0') {
    strcat(pattern, newPattern);
  } else {
    strcat(pattern, "|");
    strcat(pattern, newPattern);
  }
}

void printFunc(FILE *fileForSearch, char *currentFile, Options option,
               regex_t regEx, int singleFile) {
  char buffer[BUFFERSIZE] = {0};

  int countString = 0;
  int countMatch = 0;
  int matchString = 0;

  while (fgets(buffer, BUFFERSIZE - 1, fileForSearch) != NULL) {
    int length = strlen(buffer);
    if (buffer[length - 1] == '\n') buffer[length - 1] = '\0';

    countString++;
    matchString = !(regexec(&regEx, buffer, 0, NULL, 0));
    if (matchString && (!option.c) && (!option.n) && (!option.h) &&
        (!option.l) && (!option.v) && (!option.i) && (!option.h) &&
        (!option.s) && (!option.o)) {
      if (singleFile)
        fprintf(stdout, "%s\n", buffer);
      else
        fprintf(stdout, "%s:%s\n", currentFile, buffer);
    }
    if (matchString && option.l) {
      if (option.c) {
        if (singleFile) {
          fprintf(stdout, "1\n%s\n", currentFile);
          return;
        } else {
          fprintf(stdout, "%s:1\n%s\n", currentFile, currentFile);
          return;
        }
      } else {
        fprintf(stdout, "%s\n", currentFile);
        return;
      }
    }
    if (option.v) matchString = !matchString;

    if ((option.v) && (!option.c) && (!option.n) && (!option.h) &&
        (!option.l) && (!option.o) && matchString) {
      fprintf(stdout, "%s\n", buffer);
    } else if (((option.c) || (option.n) || (option.h) || (option.l) ||
                (option.o))) {
      if (matchString) {
        countMatch++;
        if (!option.c) {
          if (option.o && (!option.l)) {
            regmatch_t findPattern[1];
            char *tmpBuffer = buffer;
            if (!singleFile) fprintf(stdout, "%s:", currentFile);
            while (regexec(&regEx, tmpBuffer, 1, findPattern, 0) == 0) {
              char stringForPrint[BUFFERSIZE] = {0};

              fprintf(stdout, "%s\n",
                      strncpy(stringForPrint, tmpBuffer + findPattern[0].rm_so,
                              findPattern[0].rm_eo - findPattern[0].rm_so));
              tmpBuffer += findPattern[0].rm_eo;
            }
          }

          if ((option.n) && (!option.o)) {
            if (option.h)
              fprintf(stdout, "%d:%s\n", countString, buffer);
            else if (!singleFile)
              fprintf(stdout, "%s:%d:%s\n", currentFile, countString, buffer);
            else
              fprintf(stdout, "%d:%s\n", countString, buffer);
          }
          if ((!option.n) && (option.h)) fprintf(stdout, "%s\n", buffer);
        }
      }
    }
  }
  if (option.c) {
    if (singleFile)
      fprintf(stdout, "%d\n", countMatch);
    else {
      if (option.h)
        fprintf(stdout, "%d\n", countMatch);
      else
        fprintf(stdout, "%s:%d\n", currentFile, countMatch);
    }
  }
}

void funcPatternFromFile(char *pattern, char *optarg) {
  FILE *patternFile = fopen(optarg, "r");
  if (patternFile) {
    char patternFromFile[BUFFERSIZE] = {0};
    while (fgets(patternFromFile, BUFFERSIZE - 1, patternFile) != NULL) {
      int length = strlen(patternFromFile);
      if (patternFromFile[length - 1] == '\n')
        patternFromFile[length - 1] = '\0';
      addNewPattern(pattern, patternFromFile);
    }
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", optarg);
    exit(1);
  }
  fclose(patternFile);
}