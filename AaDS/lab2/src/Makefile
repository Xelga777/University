CC = gcc
STD = -std=c11
FLAGS = -Wall -Werror -Wextra
BUILD_PATH = ../build/

all:

lstack_list: stack.h
	$(CC) $(STD) $(FLAGS) -c -D __LIST_IMPLEMENTATION__ -o $(BUILD_PATH)lstack_list.o
	ar -rc $(BUILD_PATH)lstack_list.a $(BUILD_PATH)lstack_list.o

clean:
	rm -rf BUILD_PATH
	mkdir ../build

rebuild: clean all
