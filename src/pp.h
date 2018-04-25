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

/* Interface for polynomials over Zn */

#ifndef PP_H
#define PP_H

#include "p.h"
#include <stdio.h>
#include <gmp.h>

/* Given a polynomial over Z, compute its image over Zn. */
int pp_from_poly(LIBMUG_PN*,mpz_t*,int);

/* Print a polynomial over Zn to the given file descriptor. */
void pp_out_str(FILE*,LIBMUG_PN*,int);

/* Compute a division with remainder over Zn. The first degree must be
 * greater or equal to the second. */
int pp_pdivrem(LIBMUG_PN*,LIBMUG_PN*,int,LIBMUG_PN*,int);

/* Computes the primitive part of a polynomial over Zn. Maybe at this point
 * http://www.risc.jku.at/education/courses/ws2011/ca/3-gcd.pdf is a good
 * reading. */
LIBMUG_PN pp_pp(LIBMUG_PN*,LIBMUG_PN*,int);

/* Compute the GCD of two polynomials over Zn. The first degree must be
 * greater or equal to the second. */
int pp_gcd(LIBMUG_PN*,LIBMUG_PN*,int,LIBMUG_PN*,int);

/* Computes the derivative of a polynomial over Zn. */
void pp_deriv(LIBMUG_PN*,LIBMUG_PN*,int);

#endif /* PP_H */
