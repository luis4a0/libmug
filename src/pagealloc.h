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

#ifndef PAGEALLOC_H
#define PAGEALLOC_H

#include <stddef.h> /* for size_t */

#define LIBMUG_PAGESIZE        4194304
#define LIBMUG_TABLESIZE       2048
#define LIBMUG_PAGES           8
#define LIBMUG_VOIDSCAST       unsigned long

struct pinfo{
    void *start;
    size_t size;
};

LIBMUG_THREAD_ATTR void**  pages_startptr;
LIBMUG_THREAD_ATTR size_t  pages_max;/*=LIBMUG_PAGES;*/
LIBMUG_THREAD_ATTR size_t  pages_allocated;
LIBMUG_THREAD_ATTR size_t  pages_current;

LIBMUG_THREAD_ATTR size_t  page_remainingbytes;
LIBMUG_THREAD_ATTR void*   page_currentptr;

LIBMUG_THREAD_ATTR struct pinfo    *nodes_allocated;
LIBMUG_THREAD_ATTR size_t          nodes_total;
LIBMUG_THREAD_ATTR size_t          nodes_assigned;

void* meminit();

void* newpage();

/* if they ask us to allocate a memory size bigger than the page,
   we are lost (we could in that case make a bigger page) */
void* palloc(size_t);

void* prealloc(void*,size_t);

#define LIBMUG_PFREE(X)        {}
/*void LIBMUG_PFREE(void*);*/

void* memclear();

void memrelease();

#endif /* PAGEALLOC_H */
