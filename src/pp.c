/*
   Copyright (c) 2017,2018 Luis Peñaranda. All rights reserved.

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
#include "p.h"
#include "pagealloc.h"

int pp_from_poly(LIBMUG_PN *pp,mpz_t *poly,int n){
    int i;
    if(!(pp[n]=mpz_fdiv_ui(poly[n],p_prime())))
        return -1;
    for(i=0;i<n;++i)
        pp[i]=mpz_fdiv_ui(poly[i],p_prime());
    return n;
}

void pp_out_str(FILE *stream,LIBMUG_PN* pp,int n){
    int i;
    for(i=n;i;--i)
        fprintf(stream,"%d*x^%d+",pp[i],i);
    fprintf(stream,"%d",pp[0]);
    return;
}

/* Knuth 2; m>=n */
int pp_pdivrem(LIBMUG_PN *r,LIBMUG_PN *u,int m,LIBMUG_PN *v,int n){
    int k,j;
    for(k=0;k<=m;++k)
        r[k]=u[k];
    /* division p. 402 */
    /*for(k=m-n;k>=0;--k)
      for(j=n+k-1;j>=k;--j)
          r[j]=p_sub(r[j],p_mul(qk,v[j-k]));*/
    /* pseudo-division, p. 407 */
    for(k=m-n;k>=0;--k)
        for(j=n+k-1;j>=0;--j)
            /*r[j]=p_sub(
                          p_mul(v[n],r[j]),
                          p_mul(r[n+k],(j<k?0:v[j-k])));*/
            r[j]=p_submuls(v[n],r[j],r[n+k],(j<k?0:v[j-k]));
    --n;
    while(!r[n]&&n)
        --n;
    return n;
}

LIBMUG_PN pp_pp(LIBMUG_PN *pp,LIBMUG_PN *p,int dp){
    int i;
    LIBMUG_PN inv,cont=p[dp];
    /* cont is the content of the polynomial. */
    for(i=0;i<dp;++i)
        cont=p_gcd(cont,p[i]);
    inv=p_inv(cont);
    for(i=0;i<=dp;++i)
        pp[i]=p_mul(p[i],inv);
    return cont;
}

/* GCL, page 280; da>=db */
int pp_gcd(LIBMUG_PN *g,LIBMUG_PN *a,int da,LIBMUG_PN *b,int db){
    LIBMUG_PN *r0,*r1,*r2;
    int i,d0,d1,d2;
    d0=da;
    r0=(LIBMUG_PN*)palloc((1+da)*sizeof(LIBMUG_PN));
    /*for(i=0;i<=da;++i)
      r0[i]=a[i];*/
    pp_pp(r0,a,da);
    d1=db;
    r1=(LIBMUG_PN*)palloc((1+da)*sizeof(LIBMUG_PN));
    /*for(i=0;i<=db;++i)
      r1[i]=b[i];*/
    pp_pp(r1,b,db);
    r2=(LIBMUG_PN*)palloc((1+da)*sizeof(LIBMUG_PN));
    d2=pp_pdivrem(r2,r0,d0,r1,d1);
    while(d2){
        for(i=0;i<=d1;++i)
            r0[i]=r1[i];
        d0=d1;
        /*for(i=0;i<=d2;++i)
          r1[i]=r2[i];*/
    pp_pp(r1,r2,d2);
    d1=d2;
    d2=pp_pdivrem(r2,r0,d0,r1,d1);
    }
    if(!r2[0]){
        /*LIBMUG_PN inv=p_inv(r1[d1]);
        g[d1]=1;
        for(i=0;i<d1;++i)
            g[i]=p_mul(inv,r1[i]);*/
        for(i=0;i<=d1;++i)
            g[i]=r1[i];
    }else{
        d1=0;
        g[0]=1;
    }
    LIBMUG_PFREE(r0);
    LIBMUG_PFREE(r1);
    LIBMUG_PFREE(r2);
    return d1;
}

void pp_deriv(LIBMUG_PN *deriv,LIBMUG_PN *p,int deg){
    int i;
    deriv=(LIBMUG_PN*)palloc(deg*sizeof(LIBMUG_PN));
    for(i=deg;i;--i)
        deriv[i-1]=p_mul(i,p[i]);
    return;
}

/* vim: ts=4 sw=4 expandtab
*/
