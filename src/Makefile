include ../config

INSTALL_LIB=${ABS_PREFIX}/lib
INSTALL_INCLUDE=${ABS_PREFIX}/include

CCPARAMS=${CFLAGS} -DLIBMUG_THREAD_ATTR=" "
OBJECTS=crt.o inverse.o pagealloc.o p.o pp.o primes.o ugcd.o io.o ediv.o

# The includes to be copied to the install directory.
INCLUDES=mug.h

ifeq (${BUILD_TYPE},dynamic)
	CCPARAMS:=${CCPARAMS} -fPIC
	LINK_LIB:=${CC} -shared -Wl,-soname,${FULLNAME}.so.${SOMAJOR} -o ${FULLNAME}.so.${SOMAJOR}.${SOMINOR} ${OBJECTS}
else
	LINK_LIB:=${CC} ${CCPARAMS} test_ugcd.c ${FULLNAME}.a ${LIBS} -o test_ugcd
endif

all: ${BUILD_TYPE}

%.o: %.c
	${CC} ${CCPARAMS} -c $< -o $@

${FULLNAME}.a: ${OBJECTS}
	${AR} -cvq ${FULLNAME}.a ${OBJECTS}
	if [ ! -d ${INSTALL_LIB} ]; then mkdir ${INSTALL_LIB}; fi
	cp ${FULLNAME}.a ${INSTALL_LIB}
	if [ ! -d ${INSTALL_INCLUDE} ]; then mkdir ${INSTALL_INCLUDE}; fi
	cp ${INCLUDES} ${INSTALL_INCLUDE}

${FULLNAME}.so: ${OBJECTS}
	${LINK_LIB}
	if [ ! -d ${INSTALL_LIB} ]; then mkdir ${INSTALL_LIB}; fi
	cp ${FULLNAME}.so.${SOMAJOR}.${SOMINOR} ${INSTALL_LIB}
	cd ${INSTALL_LIB} && \
	ln -f -s ${FULLNAME}.so.${SOMAJOR}.${SOMINOR} ${FULLNAME}.so.${SOMAJOR} && \
	ln -f -s ${FULLNAME}.so.${SOMAJOR}.${SOMINOR} ${FULLNAME}.so && \
	cd -
	if [ ! -d ${INSTALL_INCLUDE} ]; then mkdir ${INSTALL_INCLUDE}; fi
	cp ${INCLUDES} ${INSTALL_INCLUDE}

clean:
	rm -f *.o ${FULLNAME}.a ${FULLNAME}.so* test_ugcd test_ediv
