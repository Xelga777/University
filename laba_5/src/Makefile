CC=gcc
FLAGS=-Wall -Werror -Wextra
OUTPATH=../build/

all: main.o sorts.o additional.o
	${CC} ${FLAGS} ${OUTPATH}main.o ${OUTPATH}sorts.o ${OUTPATH}additional.o -o ${OUTPATH}laba5.out

main.o:
	${CC} ${FLAGS} -c main.c -o ${OUTPATH}main.o

sorts.o:
	${CC} ${FLAGS} -c sorts.c -o ${OUTPATH}sorts.o

additional.o:
	${CC} ${FLAGS} -c additional.c -o ${OUTPATH}additional.o

clean:
	rm ${OUTPATH}*.o ${OUTPATH}laba5.out

rebuild: clean all