CC=gcc
CCPARAMS=-ansi -O3 -Wall -pedantic -DLIBMUG_THREAD_ATTR=" "
OBJECTS=crt.o inverse.o pagealloc.o p.o pp.o primes.o ugcd.o io.o ediv.o
LIBS=-lm -lgmp

%.o: %.c
	${CC} ${CCPARAMS} -c $< -o $@

test_ugcd: test_ugcd.c ${OBJECTS}
	${CC} ${CCPARAMS} test_ugcd.c ${OBJECTS} ${LIBS} -o test_ugcd

test_ediv: test_ediv.c ${OBJECTS}
	${CC} ${CCPARAMS} test_ediv.c ${OBJECTS} ${LIBS} -o test_ediv

test: test_ugcd test_ediv

clean:
	rm -f *.o test_ugcd test_ediv
