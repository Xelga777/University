CC=gcc
flags=-Wall -Werror -Wextra

all: laba_3

laba_3: array_processing.o interface.o computating.o
	$(CC) $(flags) ../build/interface.o ../build/array_processing.o ../build/computating.o -o ../build/laba_3.out

interface.o: interface.c
	$(CC) -c $(flags) interface.c -o ../build/interface.o

array_processing.o: interface.o analysing_array.c
	$(CC) -c $(flags) analysing_array.c -o ../build/array_processing.o

computating.o: computating.c
	$(CC) -c $(flags) computating.c -o ../build/computating.o

clean:
	rm ../build/*.o ../build/laba_3.out

rebuild: clean all
