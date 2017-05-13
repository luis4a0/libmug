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

#ifndef P_H
#define P_H

#include "inverse.h"

namespace LIBMUG{

// LIBMUG_PN size is 32 bits, the sizes of LIBMUG_LPN and LIBMUG_SPN must be,
// at least, as twice as the size of LIBMUG_PN
#define LIBMUG_PN_BITS  32
#define LIBMUG_PN       LIBMUG_U32  // unsigned
#define LIBMUG_LPN      LIBMUG_U64  // unsigned long long
#define LIBMUG_SPN      LIBMUG_S64  // long long

#define LIBMUG_mpz_set_pn(A,PN)     mpz_set_ui(A,(unsigned long)(PN))
#define LIBMUG_mpz_mul_pn(A,B,PN)   mpz_mul_ui(A,B,(unsigned long)(PN))
#define LIBMUG_mpz_add_pn(A,B,PN)   mpz_add_ui(A,B,(unsigned long)(PN))
#define LIBMUG_mpz_sub_pn(A,B,PN)   mpz_sub_ui(A,B,(unsigned long)(PN))
#define LIBMUG_mpz_set_spn(A,SPN)   mpz_set_si(A,(long)(SPN))
#define LIBMUG_mpz_add_spn(A,B,SPN) \
        (SPN<0?LIBMUG_mpz_sub_pn(A,B,-(SPN)):LIBMUG_mpz_add_pn(A,B,(SPN)))
#define LIBMUG_mpz_mul_spn(A,B,SPN) mpz_mul_si(A,B,SPN)

LIBMUG_THREAD_ATTR LIBMUG_PN prime; class Prime:public Inverse{
    protected:
        static LIBMUG_SPN p_pntospn(LIBMUG_PN p){
            if(p>(prime-1)/2)
                return (LIBMUG_SPN)p-prime;
            return (LIBMUG_SPN)p;
        };

        static void p_set_prime(LIBMUG_PN p){prime=p;};

        static LIBMUG_PN p_prime(){return prime;};

        static LIBMUG_PN p_add(LIBMUG_PN a,LIBMUG_PN b){
            LIBMUG_LPN c=(LIBMUG_LPN)a+b;
            return (c<prime?(LIBMUG_PN)c:(LIBMUG_PN)(c-prime));
        };

        static LIBMUG_PN p_sub(LIBMUG_PN a,LIBMUG_PN b){
            return (a<b?prime-(b-a):a-b);
        };

        // returns a*b-c*d
        static LIBMUG_PN p_submuls(LIBMUG_PN a,LIBMUG_PN b,LIBMUG_PN c,LIBMUG_PN d){
            LIBMUG_LPN mul;
            LIBMUG_PN pnm1,pnm2;
            mul=(LIBMUG_LPN)a*b;
            pnm1=(mul<prime?(LIBMUG_PN)mul:(LIBMUG_PN)(mul%prime));
            mul=(LIBMUG_LPN)c*d;
            pnm2=(mul<prime?(LIBMUG_PN)mul:(LIBMUG_PN)(mul%prime));
            return (pnm1<pnm2?prime-(pnm2-pnm1):pnm1-pnm2);
        };

        static LIBMUG_PN p_inv(LIBMUG_PN a){
            LIBMUG_SPN c=eea_s(a,prime);
            return(c<0?(LIBMUG_PN)(c+prime):(LIBMUG_PN)c);
        };

        static LIBMUG_PN p_convert(LIBMUG_PN a){
            return (a<prime?a:a%prime);
        };

        // define p_mul(A,B)    ((LIBMUG_PN)(((LIBMUG_LPN)A*B)%p_prime()))
        static LIBMUG_PN p_mul(LIBMUG_PN a,LIBMUG_PN b){
            LIBMUG_LPN c=(LIBMUG_LPN)a*b;
            return (LIBMUG_PN)(c<prime?c:c%prime);
        };

        static LIBMUG_PN p_mul3(LIBMUG_PN a,LIBMUG_PN b,LIBMUG_PN c){
            LIBMUG_LPN d;
            if((d=(LIBMUG_LPN)a*b)<prime)
                d*=c;
            else
                d=(d%prime)*c;
            return (LIBMUG_PN)(d<prime?d:d%prime);
        };

        // returns a*conv(b)
        static LIBMUG_PN p_mulc(LIBMUG_PN a,LIBMUG_PN b){
            LIBMUG_LPN temp=(LIBMUG_LPN)a*(b<prime?b:b%prime);
            return (temp<prime?(LIBMUG_PN)temp:(LIBMUG_PN)(temp%prime));
        };

        // returns a*conv(b)+conv(c)
        static LIBMUG_PN p_mulcaddc(LIBMUG_PN a,LIBMUG_PN b,LIBMUG_PN c){
            LIBMUG_LPN temp=(LIBMUG_LPN)a*(b<prime?b:b%prime);
            temp=(temp<prime?temp:temp%prime)+(c<prime?c:c%prime);
            return (temp<prime?(LIBMUG_PN)temp:(LIBMUG_PN)(temp-prime));
        };

        // returns (conv(a)-b)*inv(c)
        static LIBMUG_PN p_convsubdiv(LIBMUG_PN a,LIBMUG_PN b,LIBMUG_PN c){
            LIBMUG_SPN inv_c=eea_s(c,prime);
            LIBMUG_PN pninv_c=(inv_c<0?(LIBMUG_PN)(inv_c+prime):(LIBMUG_PN)inv_c);
            LIBMUG_PN conv_a=(a<prime?a:a%prime);
            LIBMUG_LPN mult=
                (LIBMUG_LPN)(conv_a<b?prime-(b-conv_a):conv_a-b)*pninv_c;
            return (LIBMUG_PN)(mult<prime?mult:mult%prime);
        };

        // vzGG, p. 73
        static LIBMUG_PN p_pow(LIBMUG_PN a,LIBMUG_PN n){
            LIBMUG_PN b,i;
            i=1<<(LIBMUG_PN_BITS-1);
            while(!(i&n))
                i>>=1;
            b=a;
            while(i>>=1)
                b=(i&n?p_mul3(b,b,a):p_mul(b,b));
            return b;
        };

        #define LIBMUG_P_DIV(A,B)      (p_mul(A,p_inv(B)))

        static LIBMUG_PN p_gcd(LIBMUG_PN a,LIBMUG_PN b){
            if(!b)
                return a;
            return p_gcd(b,a%b);
        };

}; // class Prime

} // namespace LIBMUG

#endif  // P_H
