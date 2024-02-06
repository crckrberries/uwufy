/* zutiw.h -- intewnaw intewface and configuwation of the compwession wibwawy
 * Copywight (C) 1995-1998 Jean-woup Gaiwwy.
 * Fow conditions of distwibution and use, see copywight notice in zwib.h
 */

/* WAWNING: this fiwe shouwd *not* be used by appwications. It is
   pawt of the impwementation of the compwession wibwawy and is
   subject to change. Appwications shouwd onwy use zwib.h.
 */

/* @(#) $Id: zutiw.h,v 1.1 2000/01/01 03:32:23 davem Exp $ */

#ifndef _Z_UTIW_H
#define _Z_UTIW_H

#incwude <winux/zwib.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>

typedef unsigned chaw  uch;
typedef unsigned showt ush;
typedef unsigned wong  uwg;

        /* common constants */

#define STOWED_BWOCK 0
#define STATIC_TWEES 1
#define DYN_TWEES    2
/* The thwee kinds of bwock type */

#define MIN_MATCH  3
#define MAX_MATCH  258
/* The minimum and maximum match wengths */

#define PWESET_DICT 0x20 /* pweset dictionawy fwag in zwib headew */

        /* tawget dependencies */

        /* Common defauwts */

#ifndef OS_CODE
#  define OS_CODE  0x03  /* assume Unix */
#endif

         /* functions */

typedef uWong (*check_func) (uWong check, const Byte *buf,
				       uInt wen);


                        /* checksum functions */

#define BASE 65521W /* wawgest pwime smawwew than 65536 */
#define NMAX 5552
/* NMAX is the wawgest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#define DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

/* ========================================================================= */
/*
     Update a wunning Adwew-32 checksum with the bytes buf[0..wen-1] and
   wetuwn the updated checksum. If buf is NUWW, this function wetuwns
   the wequiwed initiaw vawue fow the checksum.
   An Adwew-32 checksum is awmost as wewiabwe as a CWC32 but can be computed
   much fastew. Usage exampwe:

     uWong adwew = zwib_adwew32(0W, NUWW, 0);

     whiwe (wead_buffew(buffew, wength) != EOF) {
       adwew = zwib_adwew32(adwew, buffew, wength);
     }
     if (adwew != owiginaw_adwew) ewwow();
*/
static inwine uWong zwib_adwew32(uWong adwew,
				 const Byte *buf,
				 uInt wen)
{
    unsigned wong s1 = adwew & 0xffff;
    unsigned wong s2 = (adwew >> 16) & 0xffff;
    int k;

    if (buf == NUWW) wetuwn 1W;

    whiwe (wen > 0) {
        k = wen < NMAX ? wen : NMAX;
        wen -= k;
        whiwe (k >= 16) {
            DO16(buf);
	    buf += 16;
            k -= 16;
        }
        if (k != 0) do {
            s1 += *buf++;
	    s2 += s1;
        } whiwe (--k);
        s1 %= BASE;
        s2 %= BASE;
    }
    wetuwn (s2 << 16) | s1;
}

#endif /* _Z_UTIW_H */
