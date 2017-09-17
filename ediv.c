/*
   Copyright (c) 2017 Luis Peñaranda. All rights reserved.

   This file is part of libmug.

   Libmug is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Libmug is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with libmug.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/* Sets s(x)=s(x)-g(x)*k*x^shift. Return the degree of s after subtraction.
   The result is computed starting in coefficient start, the other
   coefficients of s are left untouched.
   Preconditions, degs>=degg+shift, shift>=0 and s[degs]!=0. */
int mug_fms(mpz_t *s,int degs,mpz_t *g,int degg,mpz_ptr k,int shift,int start){
        size_t i;
        for(i=start;i<=degg+shift;++i)
                mpz_submul(s[i],g[i-shift],k);
        if(degg+shift==degs)
                /* Compute the output degree of s. Note that no leading
                   zero coefficient of s is cleared, all of them need to
                   be cleared on exit. */
                while((degs>0)&&(!mpz_sgn(s[degs])))
                        --degs;
        return degs;
}

/* Exact division: sets q(x)=f(x)/g(x). Precondition: the remainder of
   the division is zero. */
int mug_ediv(mpz_t *q,mpz_t *f,int degf,mpz_t *g,int degg){
        int i,degr,start;
        mpz_t *r;
        /* Init the coefficients of the quotient q. */
        int allocq=1+degf-degg; /* allocq is one more than the degree of q. */
        for(i=0;i<allocq;++i)
                mpz_init(q[i]);
        if(!degg){
                for(i=0;i<=degf;++i)
                        mpz_divexact(q[i],f[i],g[0]);
                return allocq-1;
        }

        /* r(x) is the rest of the division on each step, that is, r(x) is
           initialized as f(x) and at each iteration, r(x)=r(x)-q[i]*g(x).
           Note that not all the coefficients of r will be computed, we
           will compute only the coefficients which will be useful in latter
           iterations. start is the starting useful coefficient of r. */
        start=degf-degg;
        /* TODO: allocate less coefficients for r. In practice, we never
           use coefficients between 0 and start-1. */
        r=(mpz_t*)malloc((degf+1)*sizeof(mpz_t));
        for(i=start;i<=degf;++i)
                mpz_init_set(r[i],f[i]);
        degr=degf;

        for(i=degf-degg;i>0;--i){
                mpz_divexact(q[i],r[degr],g[degg]);
                degr=mug_fms(r,degr,g,degg,q[i],i,start);
        }
        mpz_divexact(q[0],r[degr],g[degg]);
        /* Free the space allocated for r and its coefficients. */
        for(i=start;i<=degf;++i)
                mpz_clear(r[i]);
        free(r);

        return allocq-1;
}
