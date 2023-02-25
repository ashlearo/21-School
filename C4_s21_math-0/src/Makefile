FILES = s21_math.c
TEST_FLAGS = -lcheck -fprofile-arcs -ftest-coverage --coverage
FLAGS = -Wall -Werror -Wextra -std=c11

all: clean s21_math.a test gcov_report

s21_math.a: s21_math.o
	ar rc s21_math.a s21_math.o
	ranlib s21_math.a
	rm *.o

s21_math.o:
	gcc $(FLAGS) -c s21_math.c

make_tests:
	checkmk clean_mode=1 tests.check > tests.c

test: make_tests
	gcc -o test $(FLAGS) --coverage  tests.c s21_math.c -lcheck -lpthread -lm
	./test

gcov_report:
	rm tests.gcno tests.gcda
	mkdir report
	gcovr --html-details report/report.html
	rm *.gcda *.gcno

clean:
	rm -rf report tests.c test *.gcda *.gcno *.o *.a