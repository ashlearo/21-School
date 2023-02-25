#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct all_flags {
  int b;
  int e;
  int n;
  int E;
  int s;
  int t;
  int T;
  int v;
} all_flags;
void open_file(char* argv[], all_flags flags, int* last_enter);
void s21_cat(all_flags flags, FILE* fp, int* last_enter);
int start_of_line(char prev_ch);
int opt_v(int* ch);

#endif  //  SRC_CAT_S21_CAT_H_
