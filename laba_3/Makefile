CC=gcc
flags=-Wall -Werror -Wextra

all: laba_3

laba_3: array_processing.o interface.o
	$(CC) $(flags) interface.o array_processing.o -o laba_3.out

interface.o: interface.c
	$(CC) -c $(flags) interface.c -o interface.o

array_processing.o: interface.o analysing_array.c
	$(CC) -c $(flags) analysing_array.c -o array_processing.o

clean:
	rm *.o laba_3.out

rebuild: clean all
