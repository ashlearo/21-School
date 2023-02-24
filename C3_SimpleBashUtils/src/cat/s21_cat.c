#include "s21_cat.h"

int main(int argc, char *argv[]) {
  all_flags flags = {0, 0, 0, 0, 0, 0, 0, 0};
  int opt = 0, error_opt = 0;
  int last_enter = 0;
  const char *short_options = "beEstTnv?";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        flags.b = 1;
        break;
      case 'e':
        flags.e = 1;
        flags.v = 1;
        break;
      case 'E':
        flags.e = 1;
        break;
      case 'n':
        flags.n = 1;
        break;
      case 's':
        flags.s = 1;
        break;
      case 't':
        flags.t = 1;
        flags.v = 1;
        break;
      case 'T':
        flags.t = 1;
        break;
      case 'v':
        flags.v = 1;
        break;
      case '?':
        printf("usage: cat [-benstuv] [file ...]\n");
        error_opt = 1;
        exit(1);
    }
  }
  if (!error_opt) {
    while (optind < argc) {
      open_file(argv, flags, &last_enter);
      optind++;
    }
  }
  return 0;
}

void open_file(char *argv[], all_flags flags, int *last_enter) {
  FILE *fp = NULL;
  if (flags.b && flags.n) flags.n = 0;
  fp = fopen(argv[optind], "r+");
  if (!fp) {
    fprintf(stderr, "cat: %s: : No such file or directory\n", argv[optind]);
  } else {
    s21_cat(flags, fp, last_enter);
    fclose(fp);
  }
}

void s21_cat(all_flags flags, FILE *fp, int *last_enter) {
  int ch, prev = -2, temp = 0, count = 1;
  while ((ch = fgetc(fp)) != EOF) {
    if (flags.s) {
      if (ch == '\n') {
        if (*last_enter) {
          temp += 2;
          *last_enter = 0;
        } else {
          temp++;
        }
      } else {
        temp = 0;
      }
    }
    if ((ch == '\n') && (!flags.s || temp < 3)) {
      if (flags.n && start_of_line(prev)) {
        printf("%6d\t", count++);
      }
      if (flags.e) printf("%c", '$');
      printf("%c", ch);
    }
    if (!(ch == '\n')) {
      int printed = 0;
      if (start_of_line(prev) && (flags.n || flags.b)) printf("%6d\t", count++);
      if (flags.t && ch == '\t') {
        printf("^I");
        printed = 1;
      } else if (flags.v)
        printed = opt_v(&ch);
      if (!printed) printf("%c", ch);
    }
    prev = ch;
  }

  if (prev == '\n') *last_enter = 1;
}

int start_of_line(char prev_ch) { return prev_ch == '\n' || prev_ch == -2; }

int opt_v(int *ch) {
  int printed = 1;
  if (*ch == '\0')
    printf("^@");
  else if ((*ch > 0 && *ch <= 8) || ((*ch >= 11 && *ch <= 26)))
    printf("^%c", *ch + 'A' - 1);
  else if (*ch == 27)
    printf("^[");
  else if (*ch == 28)
    printf("^\\");
  else if (*ch == 29)
    printf("^]");
  else if (*ch == 30)
    printf("^^");
  else if (*ch == 31)
    printf("^_");
  else if (*ch == 127)
    printf("^?");
  else
    printed = 0;
  return printed;
}