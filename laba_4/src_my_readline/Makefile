CC=gcc
FLAGS=-Wall -Werror -Wextra

all: io.o main.o
	$(CC) $(FLAGS) ../build/my_io.o ../build/my_main.o -o ../lab_4_mylib.out

my_string.o: my_string.h
	$(CC) $(FLAGS) -c my_string.c -o ../mylib_funcs/my_string.o

io.o: io.h
	$(CC) $(FLAGS) -c  io.c -o ../build/my_io.o

main.o: main.h io.h
	$(CC) $(FLAGS) -c main.c -o ../build/my_main.o

clean:
	rm ../build/*.o

rebuild: clean all