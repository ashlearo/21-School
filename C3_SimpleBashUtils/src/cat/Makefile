FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

all: clean s21_cat

s21_cat:
	gcc $(FLAGS) s21_cat.c -o s21_cat

clean:
	rm -rf s21_cat

rebuild: clean s21_cat

check:
	clang-format -style=Google -n *.c *.h

clang-format:
	clang-format -style=Google -i *.c *.h

test_func: s21_cat
	sh test_func_cat.sh

test_leak: s21_cat
	sh test_leak_cat.sh