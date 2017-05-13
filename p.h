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

#ifdef _MSC_VER
#  define LIBMUG_S64 __int64
#  define LIBMUG_U64 unsigned __int64
#  define LIBMUG_U32 unsigned __int32
#else
#  include <stdint.h>
#  define LIBMUG_S64 int64_t
#  define LIBMUG_U64 uint64_t
#  define LIBMUG_U32 uint32_t
#endif

/* LIBMUG_PN size is 32 bits, the sizes of LIBMUG_LPN and LIBMUG_SPN must be,
   at least, as twice as the size of LIBMUG_PN */
#define LIBMUG_PN_BITS  32
#define LIBMUG_PN       LIBMUG_U32  /* unsigned */
#define LIBMUG_LPN      LIBMUG_U64  /* unsigned long long */
#define LIBMUG_SPN      LIBMUG_S64  /* long long */

#define LIBMUG_mpz_set_pn(A,PN)     mpz_set_ui(A,(unsigned long)(PN))
#define LIBMUG_mpz_mul_pn(A,B,PN)   mpz_mul_ui(A,B,(unsigned long)(PN))
#define LIBMUG_mpz_add_pn(A,B,PN)   mpz_add_ui(A,B,(unsigned long)(PN))
#define LIBMUG_mpz_sub_pn(A,B,PN)   mpz_sub_ui(A,B,(unsigned long)(PN))
#define LIBMUG_mpz_set_spn(A,SPN)   mpz_set_si(A,(long)(SPN))
#define LIBMUG_mpz_add_spn(A,B,SPN) \
        (SPN<0?LIBMUG_mpz_sub_pn(A,B,-(SPN)):LIBMUG_mpz_add_pn(A,B,(SPN)))
#define LIBMUG_mpz_mul_spn(A,B,SPN) mpz_mul_si(A,B,SPN)

LIBMUG_THREAD_ATTR LIBMUG_PN prime;

LIBMUG_SPN p_pntospn(LIBMUG_PN);

void p_set_prime(LIBMUG_PN);

LIBMUG_PN p_prime();

LIBMUG_PN p_add(LIBMUG_PN,LIBMUG_PN);

LIBMUG_PN p_sub(LIBMUG_PN,LIBMUG_PN);

/* returns a*b-c*d */
LIBMUG_PN p_submuls(LIBMUG_PN,LIBMUG_PN,LIBMUG_PN,LIBMUG_PN);

LIBMUG_PN p_inv(LIBMUG_PN);

LIBMUG_PN p_convert(LIBMUG_PN);

/*#define p_mul(A,B)    ((LIBMUG_PN)(((LIBMUG_LPN)A*B)%p_prime()))*/
LIBMUG_PN p_mul(LIBMUG_PN,LIBMUG_PN);

LIBMUG_PN p_mul3(LIBMUG_PN,LIBMUG_PN,LIBMUG_PN);

/* returns a*conv(b) */
LIBMUG_PN p_mulc(LIBMUG_PN,LIBMUG_PN);

/* returns a*conv(b)+conv(c) */
LIBMUG_PN p_mulcaddc(LIBMUG_PN,LIBMUG_PN,LIBMUG_PN);

/* returns (conv(a)-b)*inv(c) */
LIBMUG_PN p_convsubdiv(LIBMUG_PN,LIBMUG_PN,LIBMUG_PN);

LIBMUG_PN p_pow(LIBMUG_PN,LIBMUG_PN);

#define LIBMUG_P_DIV(A,B)      (p_mul(A,p_inv(B)))

LIBMUG_PN p_gcd(LIBMUG_PN,LIBMUG_PN);

#endif /* P_H */
