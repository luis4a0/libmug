CC=gcc
CCPARAMS=-ansi -O3 -Wall -pedantic -DLIBMUG_THREAD_ATTR=" "
OBJECTS=crt.o inverse.o pagealloc.o p.o pp.o primes.o ugcd.o io.o
LIBS=-lm -lgmp

%.o: %.c
	${CC} ${CCPARAMS} -c $< -o $@

test: test.c ${OBJECTS}
	${CC} ${CCPARAMS} test.c ${OBJECTS} ${LIBS} -o test

clean:
	rm -f *.o test
