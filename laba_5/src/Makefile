CC=gcc
FLAGS=-Wall -Wextra
OUTPATH=../build/

all: main.o sorts.o additional.o statistics
	${CC} ${FLAGS} ${OUTPATH}main.o ${OUTPATH}sorts.o ${OUTPATH}additional.o -o ${OUTPATH}laba5.out

main.o:
	${CC} ${FLAGS} -c main.c -o ${OUTPATH}main.o

sorts.o:
	${CC} ${FLAGS} -c sorts.c -o ${OUTPATH}sorts.o

additional.o:
	${CC} ${FLAGS} -c additional.c -o ${OUTPATH}additional.o

statistics: sorts.o additional.o
	$(CC) $(FLAGS) statistics.c $(OUTPATH)sorts.o $(OUTPATH)additional.o -o $(OUTPATH)statistics.out

clean:
	rm ${OUTPATH}*.o ${OUTPATH}laba5.out

rebuild: clean all