CC = gcc
STD = -std=c11
FLAGS = -Wall -Wextra
BUILD_PATH = ../build/
FILES = io.c polish_not.c token.c

all: libstack_list libstack_vector

libstack_list: stack.h
	$(CC) $(STD) $(FLAGS) -c -D __LIST_IMPLEMENTATION__ stack.c -o $(BUILD_PATH)stack_list.o
	ar -rc $(BUILD_PATH)libstack.a $(BUILD_PATH)stack_list.o
	$(CC) $(STD) $(FLAGS) $(FILES) -D __LIST_IMPLEMENTATION__ -L$(BUILD_PATH) -lstack -o $(BUILD_PATH)lab2_list.out

libstack_vector: stack.h
	$(CC) $(STD) $(FLAGS) -c -D __VECTOR_IMPLEMENTATION__ stack.c -o $(BUILD_PATH)stack_vector.o
	ar -rc $(BUILD_PATH)libstack.a $(BUILD_PATH)stack_vector.o
	$(CC) $(STD) $(FLAGS) $(FILES) -D __VECTOR_IMPLEMENTATION__ -L$(BUILD_PATH) -lstack -o $(BUILD_PATH)lab2_vector.out	

clean:
	rm $(BUILD_PATH)*.o* $(BUILD_PATH)*.a

rebuild: clean all
