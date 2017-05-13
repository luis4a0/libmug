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

#include "pagealloc.h"
#include <stdlib.h>
#include <string.h>

#define LIBMUG_PAGESIZE        4194304
#define LIBMUG_TABLESIZE       2048
#define LIBMUG_PAGES           8
#define LIBMUG_VOIDSCAST       unsigned long

void* meminit(){
    pages_startptr=(void**)malloc(LIBMUG_PAGES*sizeof(void*));
    pages_startptr[0]=malloc(LIBMUG_PAGESIZE);
    pages_allocated=1;
    pages_current=0;
    page_remainingbytes=LIBMUG_PAGESIZE;
    page_currentptr=pages_startptr[0];
    nodes_total=LIBMUG_TABLESIZE;
    nodes_allocated=
        (struct pinfo*)malloc(LIBMUG_TABLESIZE*sizeof(struct pinfo));
    nodes_assigned=0;
    return page_currentptr;
}

void* newpage(){
    void *r;
    if(pages_allocated>pages_current+1){
        ++pages_current;
        r=pages_startptr[pages_current];
        page_currentptr=r;
        page_remainingbytes=LIBMUG_PAGESIZE;
        return r;
    }
    /* iso c++ forbids to initialize a static member (pages_max),
       so we have to start using pages_max when the amount of
       allocated pages reaches the value LIBMUG_PAGES (this is not of
       course the cleanest way to do it) */
    if(pages_allocated==LIBMUG_PAGES)
        pages_max=2*LIBMUG_PAGES;
    else
        pages_max=0;
    if(pages_allocated==pages_max){
        pages_max*=2;
        pages_startptr=
            (void**)realloc(pages_startptr,pages_max*sizeof(void*));
    }
    r=malloc(LIBMUG_PAGESIZE);
    pages_startptr[pages_allocated]=r;
    page_currentptr=r;
    ++pages_allocated;
    page_remainingbytes=LIBMUG_PAGESIZE;
    return r;
}

/* if they ask us to allocate a memory size bigger than the page,
   we are lost (we could in that case make a bigger page) */
void* palloc(size_t size){
    void* r;
    if(size>page_remainingbytes){
        newpage();
        return palloc(size);
    }
    if(nodes_assigned==nodes_total){
        nodes_total*=2;
        nodes_allocated=(struct pinfo*)realloc
            (nodes_allocated,nodes_total*sizeof(struct pinfo));
    }
    page_remainingbytes-=size;
    r=page_currentptr;
    page_currentptr=(void*)((LIBMUG_VOIDSCAST)page_currentptr+size);
    /* c++ does not support nodes_allocated[nodes_assigned]={r,s} */
    nodes_allocated[nodes_assigned].start=r;
    nodes_allocated[nodes_assigned].size=size;
    ++nodes_assigned;
    return r;
}

void* prealloc(void *ptr,size_t size){
    void *dest;
    size_t i=0;
    while(nodes_allocated[i].start!=ptr)
        ++i;
    if(nodes_allocated[i].size<size){
        dest=palloc(size);
        nodes_allocated[i].start=dest;
        nodes_allocated[i].size=size;
        return memcpy(dest,ptr,nodes_allocated[i].size);
    }
    return ptr;
}

/*void LIBMUG_PFREE(void* ptr){
  size_t i=0;
  while(nodes_allocated[i].start!=ptr)
      ++i;
  nodes_allocated[i].start=0;
  return;
};*/

void* memclear(){
    pages_current=0;
    page_remainingbytes=LIBMUG_PAGESIZE;
    page_currentptr=pages_startptr[0];
    nodes_assigned=0;
    return page_currentptr;
}

void memrelease(){
    size_t i;
    for(i=0;i<pages_allocated;++i)
        free(pages_startptr[i]);
    return;
}
