#include <stdlib.h>
#include <gmp.h>
#include "mug.h"

/* Compute the exact division quotient=p1/p2.
   p1=10x^5-14x^4-7x^3-26x^2-26x+11,
   p2=2x^3+3x-1,
   quotient=5x^2-7x-11. */
int main(){
        size_t i;
        int deg_quotient;
        size_t alloc_quotient=3;
        mpz_t p1[6],p2[4];
        mpz_t* quotient=(mpz_t*)malloc(alloc_quotient*sizeof(mpz_t));
        /* Initialize p1. */
        for(i=0;i<6;++i)
                mpz_init(p1[i]);
        /* Initialize p2. */
        for(i=0;i<4;++i){
                mpz_init(p2[i]);
        }
        /* Don't initialize quotient. */
        /* Set coefficients of p1 (if not set, they are zero). */
        mpz_set_si(p1[0],11);
        mpz_set_si(p1[1],-26);
        mpz_set_si(p1[2],-26);
        mpz_set_si(p1[3],-7);
        mpz_set_si(p1[4],-14);
        mpz_set_si(p1[5],10);
        /* Set coefficients of p2. */
        mpz_set_si(p2[0],-1);
        mpz_set_si(p2[1],3);
        mpz_set_si(p2[3],2);
        /* Compute the exact division. */
        deg_quotient=mug_ediv(quotient,p1,5,p2,3);
        /* Print p1, p2 and the result. */
        fprintf(stdout,"p1=");
        mug_pretty_print_polynomial(stdout,p1,5);
        fprintf(stdout,"\np2=");
        mug_pretty_print_polynomial(stdout,p2,3);
        fprintf(stdout,"\nquotient=");
        mug_pretty_print_polynomial(stdout,quotient,deg_quotient);
        fprintf(stdout,"\n");
        for(i=0;i<6;++i)
                mpz_clear(p1[i]);
        for(i=0;i<4;++i)
                mpz_clear(p2[i]);
        for(i=0;i<alloc_quotient;++i)
                mpz_clear(quotient[i]);
        free(quotient);
        return 0;
}
