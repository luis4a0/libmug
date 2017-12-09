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

#ifndef CRT_H
#define CRT_H

#include <gmp.h>

/* Chinese remainder algorithm. */
void cra(mpz_ptr,LIBMUG_PN*,LIBMUG_PN*,int);

/* Polynomial chinese remainder algorithm. */
void pcra(mpz_t*,LIBMUG_PN*,LIBMUG_PN**,int,int);

#endif /* CRT_H */
