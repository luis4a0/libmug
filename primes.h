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

#ifndef PRIMES_H
#define PRIMES_H

#include "crt.h"

// I borrowed these numbers from Fabrice, this leaves us around 250000 primes
#define LIBMUG_PR_MIN 2145338339
#define LIBMUG_PR_MAX 2147483647

//#define LIBMUG_PR_IS_PRIME(N)        (pr_fermat(N)?pr_is_prime_bruteforce(N):0)
#define LIBMUG_PR_IS_PRIME(N)  pr_mrj(N)

#ifdef _MSC_VER
#  define LIBMUG_RANDOM  rand
#else
#  define LIBMUG_RANDOM  random
#endif

namespace LIBMUG{

LIBMUG_THREAD_ATTR LIBMUG_PN currentprime;

class Primes:public Crt{
    private:
        static int pr_is_prime_bruteforce(LIBMUG_PN n){
            int i,sqrtn;
            sqrtn=(LIBMUG_PN)(sqrt((double)n));
            for(i=3;i<=sqrtn;++i)
                if(!(n%i))
                    return 0;
            return 1;
        }

        // vzGG, p. 507; returns 0 if n is composite
        static int pr_fermat(LIBMUG_PN n){
            p_set_prime(n);
            return(p_pow(2+((LIBMUG_PN)LIBMUG_RANDOM())%(n-4),n-1)==1);
        }

        // Solovay-Strassen
        static int pr_ss(LIBMUG_PN n){
            LIBMUG_PN a,x;
            p_set_prime(n);
            a=1+(LIBMUG_PN)LIBMUG_RANDOM()%(n-2);
            x=LIBMUG_P_DIV(a,n);
            return(!x||p_pow(a,n>>1)!=x);
        }

        // Miller-Rabin
        static int pr_mr(LIBMUG_PN n){
            LIBMUG_PN s,d,a,x,r;
            s=1;
            d=(n-1)>>1;
            while(!(d&1)){
                ++s;
                d=d>>1;
            }
            p_set_prime(n);
            a=2+(LIBMUG_PN)LIBMUG_RANDOM()%(n-4);
            x=p_pow(a,d);
            if(x==1||x==n-1)
                return 1; // pobably prime
            for(r=1;r<s;++r){
                x=p_mul(x,x);
                if(x==1)
                    return 0; // composite
                if(x==n-1)
                    return 1; // probably
            }
            return 0; // composite
        }

        // Miller-Rabin-Jaeschke
        static int pr_mrj(LIBMUG_PN n){
            LIBMUG_PN s,d,a[3],r;//,x;
            int index;
            a[0]=2;
            a[1]=7;
            a[2]=61;
            s=1;
            d=(n-1)>>1;
            while(!(d&1)){
                ++s;
                d=d>>1;
            }
            p_set_prime(n);
            index=-1;
        start_test:
            ++index;
            //if(index=3)
            if(index==3)
                return 1; // prime
            if(p_pow(a[index],d)==1)
                goto start_test;
            for(r=0;r<s;++r)
                if(p_pow(a[index],(d<<r))==n-1)
                    goto start_test;
            return 0; // composite
        }

        static LIBMUG_PN pr_actual(){
            return currentprime;
        }

    protected:
        static int pr_init(){
            currentprime=LIBMUG_PR_MIN;
            return 0;
        }

        static LIBMUG_PN pr_next(){
            do{
                currentprime+=2;
            }while(!LIBMUG_PR_IS_PRIME(currentprime));
            return currentprime;
        }

}; // class Primes

} // namespace LIBMUG

#endif  // PRIMES_H
