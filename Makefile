include config

ABS_PREFIX=$(abspath ${PREFIX})

.PHONY: all static dynamic test

all: static

static:
	cd src && \
	make BUILD_TYPE=static ABS_PREFIX=${ABS_PREFIX} ${FULLNAME}.a && \
	cd ..

dynamic:
	cd src && \
	make BUILD_TYPE=dynamic ABS_PREFIX=${ABS_PREFIX} ${FULLNAME}.so && \
	cd ..

test:
	cd test && \
	make BUILD_TYPE=static ABS_PREFIX=${ABS_PREFIX} && \
	cd ..

clean:
	cd src && make clean && cd ..
	cd test && make clean && cd ..

distclean:
	cd src && make clean && cd ..
	cd test && make clean && cd ..
	rm -rf include/ lib/
