CC = gcc
STD = -std=c11
FLAGS = -Wall -Werror -Wextra
BUILD_PATH = ../build/

all: create_objs
	$(CC) $(STD) $(BUILD_PATH)io.o main.c -o $(BUILD_PATH)lab1.out

create_objs: IO.h
	$(CC) $(STD) -c $(FLAGS) IO.c -o $(BUILD_PATH)io.o

clean:
	rm -rf $(BUILD_PATH)*.o $(BUILD_PATH)*.out

rebuild: clean all
