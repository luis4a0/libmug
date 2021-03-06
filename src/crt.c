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

#include "pp.h"
#include "pagealloc.h"

/* Chinese remainder algorithm (GCL, page 180). */
void cra(mpz_ptr r,LIBMUG_PN * m,LIBMUG_PN *u,int n){
    int k,i;
    LIBMUG_PN product,temp;
    LIBMUG_PN *v=(LIBMUG_PN*)palloc(n*sizeof(LIBMUG_PN));
    /* TODO: is it necessary to set all members of v to zero? */
    /* I don't think so. */
    for(i=0;i<n;++i)
        v[i]=0;

    v[0]=u[0];
    for(k=1;k<n;++k){
        p_set_prime(m[k]);
        /* step 1, gamma_k is p_inv(product) */
        product=p_convert(m[0]);
        for(i=1;i<k;++i)
            /*product=p_mul(product,p_convert(m[i]));*/
            product=p_mulc(product,m[i]);
        /* step 2 */
        temp=p_convert(v[k-1]);
        for(i=k-2;i>=0;--i)
            /*temp=p_add(p_convert(v[i]),p_mul(temp,p_convert(m[i])));*/
            temp=p_mulcaddc(temp,m[i],v[i]);
        /*v[k]=p_mul(p_sub(p_convert(u[k]),temp),p_inv(product));*/
        v[k]=p_convsubdiv(u[k],temp,product);
    }
    /* step 3: operations are done in Zm, not in Z */
    LIBMUG_mpz_set_spn(r,p_pntospn(v[n-1]));
    for(k=n-2;k>=0;--k){
        LIBMUG_mpz_mul_pn(r,r,m[k]);
        LIBMUG_mpz_add_pn(r,r,v[k]);
    }
    return;
}

/* Polynomial chinese remainder algorithm, it is the same:
   m are the modules, and m has size size_y, p is the residue
   vector and also has size size_y, but every one of its elements
   has size size_x (which will be de degree of the output
   polynomial); size_y is what is called n in the book. */
void pcra(mpz_t *r,
          LIBMUG_PN *m,
          LIBMUG_PN **p,
          int size_x,
          int size_y){
    LIBMUG_PN **v;
    int i,j,k;
    LIBMUG_PN product,temp;

    /* Construct v. */
    v=(LIBMUG_PN**)palloc((size_x+1)*sizeof(LIBMUG_PN*));
    for(i=0;i<=size_x;++i)
        v[i]=(LIBMUG_PN*)palloc(size_y*sizeof(LIBMUG_PN));

    for(j=0;j<=size_x;++j){
        v[j][0]=p[0][j];
        for(k=1;k<size_y;++k){
            p_set_prime(m[k]);
            /* step 1, gamma_k is p_inv(product) */
            product=p_convert(m[0]);
            for(i=1;i<k;++i)
                product=p_mulc(product,m[i]);
            /* step 2 */
            temp=p_convert(v[j][k-1]);
            for(i=k-2;i>=0;--i)
                temp=p_mulcaddc(temp,m[i],v[j][i]);
            v[j][k]=p_convsubdiv(p[k][j],temp,product);
        }
    }
    /* step 3 */
    /* be careful: operations are done in Zm, not in Z */
    for(j=0;j<=size_x;++j){
        LIBMUG_mpz_set_spn(r[j],p_pntospn(v[j][size_y-1]));
        for(k=size_y-2;k>=0;--k){
            LIBMUG_mpz_mul_pn(r[j],r[j],m[k]);
            LIBMUG_mpz_add_pn(r[j],r[j],v[j][k]);
        }
    }
}
