CC=gcc
FLAGS=-Wall -Werror -Wextra
MYPATH=../build/

all: GNU_main MY_main
	$(CC) $(FLAGS) main.c $(MYPATH)io.o $(MYPATH)my_string.o -lreadline -o $(MYPATH)test.out

io.o:
	$(CC) $(FLAGS) -c io.c -o $(MYPATH)io.o

MY_main: my_string.o io.o
	$(CC) $(FLAGS) -D __MY_VER__ main.c $(MYPATH)io.o $(MYPATH)my_string.o -o $(MYPATH)MY_main.out

GNU_main: io.o
	$(CC) $(FLAGS) -D __GNU_VER__ main.c $(MYPATH)io.o -lreadline -o $(MYPATH)GNU_main.out

my_string.o:
	$(CC) $(FLAGS) -c ../mylib_funcs/my_string.c -o $(MYPATH)my_string.o

clean:
	rm ../build/*.o
	rm ../build/*.out

rebuild: clean all