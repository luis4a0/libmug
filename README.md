#Libmug

##A library for modular univariate GCD computations.

The original code was bundled with CGAL 4.3. For 4.4, I removed it because
I rewrote the algebraic kernel that used it. I release it because maybe it
is useful for someone. If you are interested, don't hesitate in contacting
me.

##Algorithm overview

The implementation the well-known Euclidean algorithm to compute GCD.
However, big numbers make the size of the coefficients explode. We use then
modular arithmetic. We compute images of the input polynomials modulo some
primes and compute then images of these modular polynomials. Then, we use
Chinese lifting to recover the result.

##Bibliography

* von Zur Gathen and Gerhard, *Modern Computer Algebra*, 2nd edition,
Cambridge, 2003.
* Geddes, Czapor and Labahn, *Algorithms for Computer Algebra*,
Springer, 1992.
* Zippel, *Effective Polynomial Computations*, Springer, 1993.

## License

The code is released under the LGPLv3. See files COPYING.LESSER and
COPYING in the bundle for more information. Originally, the code was
released under the LGPLv2.
