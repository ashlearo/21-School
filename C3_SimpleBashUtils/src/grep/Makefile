FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

all: s21_grep

s21_grep: Makefile s21_grep.c
	gcc $(FLAGS) s21_grep.c s21_grep.h -o s21_grep

test_func: s21_grep
	sh test_func_grep.sh

test_leak: s21_grep
	sh test_leak_grep.sh

check:
	clang-format -style=Google -n *.c *.h

clang-format:
	clang-format -style=Google -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -f s21_grep