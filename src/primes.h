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

#ifndef PRIMES_H
#define PRIMES_H

#include "p.h"

/* I borrowed these numbers from RS, this leaves us around 250000 primes */
#define LIBMUG_PR_MIN 2145338339
#define LIBMUG_PR_MAX 2147483647

/*#define LIBMUG_PR_IS_PRIME(N)        (pr_fermat(N)?pr_is_prime_bruteforce(N):0)*/
#define LIBMUG_PR_IS_PRIME(N)  pr_mrj(N)

LIBMUG_THREAD_ATTR LIBMUG_PN currentprime;

int pr_is_prime_bruteforce(LIBMUG_PN);

/* Returns 0 if n is composite. */
int pr_fermat(LIBMUG_PN);

/* Solovay-Strassen */
int pr_ss(LIBMUG_PN);

/* Miller-Rabin */
int pr_mr(LIBMUG_PN);

/* Miller-Rabin-Jaeschke */
int pr_mrj(LIBMUG_PN);

LIBMUG_PN pr_actual();

int pr_init();

LIBMUG_PN pr_next();

#endif /* PRIMES_H */
