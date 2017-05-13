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

#ifndef INVERSE_H
#define INVERSE_H

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

namespace LIBMUG{

#define LIBMUG_N(A)   (A<0?-A:A)
//#define LIBMUG_U(A) (A<0?-1:1)
#define LIBMUG_U(A,C) (A<0?(C<0?1:-1):(C<0?-1:1))

class Inverse{

    protected:
        // given a and b, returns s such that gcd(a,b)=s*a+t*b (GCL, page 36)
        // s*a+t*q=1 => s is the inverse of a, mod q (pafe 173)
        static LIBMUG_S64 eea_s(LIBMUG_U32 a,LIBMUG_U32 b){
            LIBMUG_S64 c1,d1,r1;//,c2,d2,r2,t,s;
            LIBMUG_U32 r,c,d;//,q;
            // a and b are positive, so a=LIBMUG_N(a) and b=LIBMUG_N(b)
            //c=LIBMUG_N(a);      d=LIBMUG_N(b);
            c=a;    d=b;
            c1=1;   d1=0;
            //c2=0; d2=1;
            while(d){
                    //q=c/d;
                    r=c%d;
                    r1=c1-d1*(c/d); //r2=c2-d2*q;
                    c=d;    c1=d1;  //c2=d2;
                    d=r;    d1=r1;  //d2=r2;
            }
            // gcd(a,b) is LIBMUG_N(c)
            //t=c2/(LIBMUG_U(b)*LIBMUG_U(c));
            // a and c are always positive, so s=c1/LIBMUG_U(a,c) equals c1
            //s=c1/LIBMUG_U(a,c);
            //return s;
            return c1;
        };
}; // class Inverse

#undef LIBMUG_N
#undef LIBMUG_U

} // namespace LIBMUG

#endif  // INVERSE_H
