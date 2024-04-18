# all, clean, test, s21_matrix_oop.a
GCC=g++
CFALGS= -Wall -Werror -Wextra -std=c++17
SOURCES=*.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TESTS_SOURCES=tests/*.cpp
TESTSFLAGS= -lgtest -lgmock -pthread
GCOVFLAGS=-fprofile-arcs -ftest-coverage -lgcov

ifeq ($(shell uname), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif


all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	$(GCC) $(CFALGS) $(SOURCES) -c
	ar rcs s21_matrix_oop.a $(OBJECTS)

clean:
	rm -rf s21_matrix_oop test *.a $(OBJECTS) a.out *.gcno *.gcda report report.info *.dSYM

test: clean s21_matrix_oop.a
	$(GCC) $(CFALGS) $(TESTS_SOURCES) s21_matrix_oop.a $(TESTSFLAGS) -o test
	./test

clang:
	clang-format -n -style=google $(SOURCES) *.h $(TESTS_SOURCES)

gcov_report: clean s21_matrix_oop.a
	$(GCC) $(CFALGS) $(TESTS_SOURCES) $(SOURCES) s21_matrix_oop.a $(TESTSFLAGS) $(GCOVFLAGS) -o s21_matrix_oop
	./s21_matrix_oop
	lcov -t "./s21_matrix_oop" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

valgrind: clean test
	valgrind --tool=memcheck --leak-check=yes  ./test
