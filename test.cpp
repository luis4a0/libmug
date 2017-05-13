/* define it here to avoid latter complaints */
#define LIBMUG_THREAD_ATTR

#include <stdio.h>
#include <gmp.h>
#include "ugcd.h"

void pretty_print_polynomial(FILE *stream,mpz_t* p,int deg_p){
        int coef_sign;
        for(int i=deg_p;0<=i;--i){
                coef_sign=mpz_sgn(p[i]);
                // Print sign.
                if(coef_sign>0&&i!=deg_p){
                        fprintf(stream,"+");
                }
                if(coef_sign){
                        // Print coefficient.
                        if(!mpz_cmp_ui(p[i],1)){
                                if(i!=deg_p)
                                        fprintf(stream,"+");
                        }else{
                                if(!mpz_cmp_si(p[i],-1)){
                                        fprintf(stream,"-");
                                }else{
                                        mpz_out_str(stream,10,p[i]);
                                        if(i)
                                                fprintf(stream,"*");
                                }
                        }
                        // Print variable.
                        switch(i){
                                case 0:
                                        break;
                                case 1:
                                        fprintf(stream,"x");
                                        break;
                                default:
                                        fprintf(stream,"x^%d",i);
                                        break;
                        }
                }
        }
        return;
}

/* Compute the GCD of x^2+2*x and -2*x-4 (must be x+2). */
int main(){
        mpz_t p1[3],p2[2],gcd[2];
        /* Initialize p1. */
        for(size_t i=0;i<3;++i)
                mpz_init(p1[i]);
        /* Initialize p2 and gcd (the destination polynomial must have its
           coefficients allocated). */
        for(size_t i=0;i<2;++i){
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
        int deg_gcd=Ugcd::ugcd(gcd,p1,2,p2,1);
        /* Print p1, p2 and the result. */
        pretty_print_polynomial(stderr,p1,2);
        fprintf(stderr,"\n");
        pretty_print_polynomial(stderr,p2,1);
        fprintf(stderr,"\n");
        pretty_print_polynomial(stderr,gcd,deg_gcd);
        fprintf(stderr,"\n");
        return 0;
}
