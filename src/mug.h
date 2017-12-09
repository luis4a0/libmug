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

#ifndef MUG_H
#define MUG_H

#include <stdio.h>
#include <gmp.h>

int mug_ugcd(mpz_t*,mpz_t*,int,mpz_t*,int);

void mug_pretty_print_polynomial(FILE*,mpz_t*,int);

int mug_ediv(mpz_t*,mpz_t*,int,mpz_t*,int);

#endif /* MUG_H */
