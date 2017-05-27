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
#include <gmp.h>

void mug_pretty_print_polynomial(FILE *stream,mpz_t* p,int deg_p){
        int coef_sign,i;
        for(i=deg_p;0<=i;--i){
                coef_sign=mpz_sgn(p[i]);
                /* Print sign. */
                if(coef_sign>0&&i!=deg_p){
                        fprintf(stream,"+");
                }
                if(coef_sign){
                        /* Print coefficient. */
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
                        /* Print variable. */
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
