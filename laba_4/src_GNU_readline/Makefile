CC=gcc
FLAGS=-Wall -Werror -Wextra

all: io.o main.o
	$(CC) $(FLAGS) ../build/GNU_io.o ../build/GNU_main.o -lreadline -o ../lab_4_GNUlib.out

io.o: io.h
	$(CC) $(FLAGS) -c  io.c -o ../build/GNU_io.o -lreadline

main.o: main.h io.h
	$(CC) $(FLAGS) -c main.c -o ../build/GNU_main.o

clean:
	rm ../build/*.o
	rm computed source

rebuild: clean all