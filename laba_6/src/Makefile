CC=gcc
FLAGS=-Wall -Wextra -Werror
OUT_PATH=../build/

all: node.o main.o
	$(CC) $(FLAGS) $(OUT_PATH)main.o $(OUT_PATH)node.o -o $(OUT_PATH)laba_6.out

main.o:
	$(CC) $(FLAGS) -c main.c -o $(OUT_PATH)main.o

node.o:
	$(CC) $(FLAGS) -c node.c -o $(OUT_PATH)node.o

clean:
	rm $(OUT_PATH)*.o $(OUT_PATH)laba_6.out

rebuild: clean all