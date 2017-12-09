include ../config

INSTALL_LIB=${ABS_PREFIX}/lib
INSTALL_INCLUDE=${ABS_PREFIX}/include

TESTS=test_ugcd test_ediv

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ -I${INSTALL_INCLUDE}

${TESTS}: %: %.o ${TESTS}
	${CC} ${CFLAGS} $< ${INSTALL_LIB}/${FULLNAME}.a -o $@ ${LIBS}

all: ${TESTS}

clean:
	rm -rf *.o ${TESTS}
