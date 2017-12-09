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

#include "mug.h"
#include "pp.h"
#include "primes.h"
#include "pagealloc.h"
#include "crt.h"
#include <stdlib.h>

/* To initialize the random number generator. */
#ifndef _MSC_VER
#  include <time.h>
#endif

/* let's assume that 300 is enough for degree 500 gcds */
#define LIBMUG_MOD_QTY 300

int mug_ugcd(mpz_t *gcd,mpz_t *Anp,int degA,mpz_t *Bnp,int degB){
    mpz_t *A,*B;
    mpz_t lcgcd,cA,cB;
    mpz_ptr m,bound;
    /* dG is initialized to zero only to avoid compiler complaints */
    int dA,dB,dG=0,maxd,i,maxA,maxB;
    size_t modsize,modalloc;
    LIBMUG_PN **p;
    size_t p_next=0;
    LIBMUG_PN *mA,*mB,*mG,*mod;
    LIBMUG_PN lc=0,scaleG;

    /* Initialize the random number generator. */
#ifndef _MSC_VER
    srand(time(NULL));
#endif

    if(degB>degA){
        if(!degA){
            mpz_set_ui(gcd[0],1);
            return 0;
        }else
            return mug_ugcd(gcd,Bnp,degB,Anp,degA);
    }
    if(!degB){
        mpz_set_ui(gcd[0],1);
        return 0;
    }

    /* initialize the memory */
    meminit();

    A=(mpz_t*)malloc((1+degA)*sizeof(mpz_t));
    B=(mpz_t*)malloc((1+degB)*sizeof(mpz_t));
    mpz_init_set(cA,Anp[degA]);
    for(i=0;i<degA;++i)
        mpz_gcd(cA,cA,Anp[i]);
    mpz_init_set(cB,Bnp[degB]);
    for(i=0;i<degB;++i)
        mpz_gcd(cB,cB,Bnp[i]);

    for(i=0;i<=degA;++i){
        mpz_init(A[i]);
        mpz_divexact(A[i],Anp[i],cA);
    }
    for(i=0;i<=degB;++i){
        mpz_init(B[i]);
        mpz_divexact(B[i],Bnp[i],cB);
    }

    /* calculate the gcd of the principal coefficients */
    mpz_init(lcgcd);
    mpz_gcd(lcgcd,A[degA],B[degB]);

    /* find the limit of modular image computation */
    maxA=degA;
    for(i=0;i<degA;++i)
        if(mpz_cmpabs(A[i],A[maxA])>0)
            maxA=i;
    maxB=degB;
    for(i=0;i<degB;++i)
        if(mpz_cmpabs(B[i],B[maxB])>0)
            maxB=i;
    mpz_pow_ui(cA,A[maxA],2);
    mpz_mul_ui(cA,cA,degA+1);
    mpz_mul_2exp(cA,cA,2*degA);
    mpz_sqrt(cA,cA);
    mpz_pow_ui(cB,B[maxB],2);
    mpz_mul_ui(cB,cB,degB+1);
    mpz_mul_2exp(cB,cB,2*degB);
    mpz_sqrt(cB,cB);
    if(mpz_cmp(cA,cB)<0){
        bound=(mpz_ptr)cA;
        m=(mpz_ptr)cB;
    }else{
        bound=(mpz_ptr)cB;
        m=(mpz_ptr)cA;
    }
    mpz_mul(bound,bound,lcgcd);
    mpz_mul_2exp(bound,bound,1);
    mpz_setbit(bound,0);

    mA=(LIBMUG_PN*)palloc((1+degA)*sizeof(LIBMUG_PN));
    mB=(LIBMUG_PN*)palloc((1+degB)*sizeof(LIBMUG_PN));
    maxd=degA;      /* we know that degA>=degB */
    mG=(LIBMUG_PN*)palloc((1+maxd)*sizeof(LIBMUG_PN));
    pr_init();
    mpz_set_ui(m,1);
    mod=(LIBMUG_PN*)palloc(LIBMUG_MOD_QTY*sizeof(LIBMUG_PN));
    modalloc=LIBMUG_MOD_QTY;
    modsize=0;
    p=(LIBMUG_PN**)palloc((1+(degA<degB?degB:degA))*sizeof(LIBMUG_PN));

    while(mpz_cmp(m,bound)<=0){
        do{
            p_set_prime(pr_next());
            dA=pp_from_poly(mA,A,degA);
            if(dA!=-1){
                dB=pp_from_poly(mB,B,degB);
                if(dB!=-1)
                    lc=mpz_fdiv_ui(lcgcd,p_prime());
                /* lc is the image of the principal coefficient */
            }
        }while(dA==-1||dB==-1||!lc
                ||mpz_divisible_ui_p(A[degA],p_prime())
                ||mpz_divisible_ui_p(B[degB],p_prime()));
        /* now we calculate the gcd mod p_prime */
        dG=pp_gcd(mG,mA,degA,mB,degB);
        scaleG=LIBMUG_P_DIV(lc,mG[dG]);
        mG[dG]=lc;
        for(i=0;i<dG;++i)
            mG[i]=p_mul(mG[i],scaleG);
        if(!dG){        /* done, we know that the gcd is constant */
            mpz_set_ui(gcd[0],1);
            dG=0;
            goto cleanandexit;
        }
        if(dG<maxd){
            LIBMUG_mpz_set_pn(m,p_prime());
            maxd=dG;
            p_next=1;
            p[0]=mG;
            mod[0]=p_prime();
            modsize=1;
            mG=(LIBMUG_PN*)palloc((1+maxd)*sizeof(LIBMUG_PN));
            /* TODO: clean the  LIBMUG_PN* that are in p */
        }else{
            if(dG==maxd){
                LIBMUG_mpz_mul_pn(m,m,p_prime());
                if(modsize==modalloc){
                    modalloc*=2;
                    mod=(LIBMUG_PN*)
                        prealloc(mod,modalloc*sizeof(LIBMUG_PN));
                }
                mod[modsize]=p_prime();
                ++modsize;
                p[p_next++]=mG;
                mG=(LIBMUG_PN*)palloc((1+maxd)*sizeof(LIBMUG_PN));
            }
        }
    }

    pcra(gcd,mod,p,maxd,modsize);

    cleanandexit:

    LIBMUG_PFREE(mA);
    LIBMUG_PFREE(mB);
    LIBMUG_PFREE(mG);
    LIBMUG_PFREE(mod);
    /* TODO: clean the LIBMUG_PN* that are in p */
    for(i=0;i<=degA;++i)
        mpz_clear(A[i]);
    for(i=0;i<=degB;++i)
        mpz_clear(B[i]);
    mpz_clear(m);
    mpz_clear(bound);
    mpz_clear(lcgcd);
    free(A);
    free(B);

    memrelease();

    return dG;
}
