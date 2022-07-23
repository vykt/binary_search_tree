CC=gcc
CFLAGS= -Wall -ggdb -O2
CLEAN_TARGETS=bstree bstree.o bstree.h.gch

bstree: bstree.o
	${CC} ${CFLAGS} -o bstree bstree.o bstree.h

bstree.o: bstree.c bstree.h
	${CC} ${CFLAGS} -c bstree.c bstree.h

clean:
	rm ${CLEAN_TARGETS}
