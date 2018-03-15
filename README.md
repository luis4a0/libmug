# Libmug

## A library for modular univariate GCD computations.

The original code was bundled with CGAL, between versions 3.6 (March, 2010)
and 4.3 (October, 2013). For CGAL 4.4, I removed it because I rewrote the
algebraic kernel that used it. I release it because I hope the code is useful
for someone. If you are interested, don't hesitate in contacting me.

## Algorithm overview

The implementation the well-known Euclidean algorithm to compute GCD.
However, big numbers make the size of the coefficients explode. We use then
modular arithmetic. We compute images of the input polynomials modulo some
primes and compute then images of these modular polynomials. Then, we use
Chinese lifting to recover the result.

## Compiling and testing

[![Build Status](https://travis-ci.org/luis4a0/libmug.svg?branch=master)
](https://travis-ci.org/luis4a0/libmug)

You can compile using GNU make. Edit makefile and config to suit your needs.

The code is tested automatically via [Travis CI](https://travis-ci.org) using
GCC and Clang, both under GNU/Linux and Mac OS. Tests are triggered when a new
commit is pushed. The code should also compile on MSVC, although I did not
test it.

## Bibliography

* von Zur Gathen and Gerhard, *Modern Computer Algebra*, 2nd edition,
Cambridge, 2003.
* Geddes, Czapor and Labahn, *Algorithms for Computer Algebra*,
Springer, 1992.
* Zippel, *Effective Polynomial Computations*, Springer, 1993.

## License

The code is released under the LGPLv3. See files COPYING.LESSER and
COPYING in the bundle for more information. Originally, the code was
released under the LGPLv2.
