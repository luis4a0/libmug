#include <gmp.h>
#include "mug.h"

/* Compute the GCD of x^2+2*x and -2*x-4 (must be x+2). */
int main(){
        size_t i;
        int deg_gcd;
        mpz_t p1[3],p2[2],gcd[2];
        /* Initialize p1. */
        for(i=0;i<3;++i)
                mpz_init(p1[i]);
        /* Initialize p2 and gcd (the destination polynomial must have its
           coefficients allocated). */
        for(i=0;i<2;++i){
                mpz_init(p2[i]);
                mpz_init(gcd[i]);
        }
        /* Set coefficients of p1 (if not set, they are zero). */
        mpz_set_ui(p1[1],2);
        mpz_set_ui(p1[2],1);
        /* Set coefficients of p2. */
        mpz_set_si(p2[0],-4);
        mpz_set_si(p2[1],-2);
        /* Compute GCD. */
        deg_gcd=mug_ugcd(gcd,p1,2,p2,1);
        /* Print p1, p2 and the result. */
        mug_pretty_print_polynomial(stderr,p1,2);
        fprintf(stderr,"\n");
        mug_pretty_print_polynomial(stderr,p2,1);
        fprintf(stderr,"\n");
        mug_pretty_print_polynomial(stderr,gcd,deg_gcd);
        fprintf(stderr,"\n");

        for(i=0;i<3;++i)
                mpz_clear(p1[i]);
        for(i=0;i<2;++i){
                mpz_clear(p2[i]);
                mpz_clear(gcd[i]);
        }

        return 0;
}
