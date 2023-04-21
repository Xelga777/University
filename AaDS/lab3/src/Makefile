CC = gcc
STD = -std=c11
WFLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -lcheck

S21_LIB = libtable.a
LIB_FILES = $(wildcard lib/*.c)
C_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c, %.o, $(C_FILES))

## здесь прописывать файлы с тестами
TEST_C_FILES = $(wildcard tests.c)

## здесь не надо
TEST_OBJ_FILES = $(patsubst %.c, %.o, $(TEST_C_FILES))

## флаги для тестирования на WSL/linux
WSL_LINK_FLAGS = -lsubunit -lm

## очистка мусора
TRASH = $(wildcard *.o *.a *.gc* tests test.info report)

all: clean table.a main

table.a: table.o
	ar -rc $(S21_LIB) $(wildcard tbl_*.o)
	ranlib $(S21_LIB)

table.o:
	$(CC) $(STD) -c $(WFLAGS) $(LIB_FILES)

main.o:
	$(CC) $(STD) -c $(WFLAGS) $(C_FILES)

main: main.o table.a
	$(CC) $(STD) $(WFLAGS) $(OBJ_FILES) -L. -ltable -o lab3.out

test: clean table.a
ifeq ($(shell uname -s), Linux)
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS)
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(S21_LIB) -o tests $(TEST_FLAGS) $(WSL_LINK_FLAGS)
	./tests
else
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS)
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(S21_LIB) -o tests  $(TEST_FLAGS) 
	./tests
endif

gcov_report: clean table.a
ifeq ($(shell uname -s), Linux)
	$(CC) $(STD) --coverage $(LIB_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS) -o tests
else
	$(CC) $(STD) --coverage $(LIB_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) -o tests
endif
	./tests
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	clang-format -n -style=google *.c *.h lib/*.*

correct_style:
	clang-format -i -style=google *.c *.h

check_leaks: clean test
	valgrind --leak-check=full --show-leak-kinds=all -s ./lab3.out

clean:
	rm -rf $(TRASH)

rebuild: clean all
