CC = gcc
STD = -std=c11
FLAGS = -Wall -Wextra
BUILD_PATH = ../build/
FILES = io.c polish_not.c token.c

all: main

libstack_list: stack.h
	$(CC) $(STD) $(FLAGS) -c stack.c -D __LIST_IMPLEMENTATION__ -o $(BUILD_PATH)stack_list.o
	ar -rc $(BUILD_PATH)libstack.a $(BUILD_PATH)stack_list.o

libstack_vector: stack.h
	$(CC) $(STD) $(FLAGS) -c -D __VECTOR_IMPLEMENTATION__ -o $(BUILD_PATH)stack_vector.o
	ar -rc $(BUILD_PATH)libstack.a $(BUILD_PATH)stack_vector.o

main: 
	$(CC) $(STD) $(FLAGS) $(FILES) $(BUILD_PATH)libstack.a -o $(BUILD_PATH)lab2.out

clean:
	rm -rf BUILD_PATH
	mkdir ../build

rebuild: clean all
