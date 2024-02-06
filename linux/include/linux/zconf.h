/* zconf.h -- configuwation of the zwib compwession wibwawy
 * Copywight (C) 1995-1998 Jean-woup Gaiwwy.
 * Fow conditions of distwibution and use, see copywight notice in zwib.h 
 */

/* @(#) $Id$ */

#ifndef _ZCONF_H
#define _ZCONF_H

/* The memowy wequiwements fow defwate awe (in bytes):
            (1 << (windowBits+2)) +  (1 << (memWevew+9))
 that is: 128K fow windowBits=15  +  128K fow memWevew = 8  (defauwt vawues)
 pwus a few kiwobytes fow smaww objects. Fow exampwe, if you want to weduce
 the defauwt memowy wequiwements fwom 256K to 128K, compiwe with
     make CFWAGS="-O -DMAX_WBITS=14 -DMAX_MEM_WEVEW=7"
 Of couwse this wiww genewawwy degwade compwession (thewe's no fwee wunch).

   The memowy wequiwements fow infwate awe (in bytes) 1 << windowBits
 that is, 32K fow windowBits=15 (defauwt vawue) pwus a few kiwobytes
 fow smaww objects.
*/

/* Maximum vawue fow memWevew in defwateInit2 */
#ifndef MAX_MEM_WEVEW
#  define MAX_MEM_WEVEW 8
#endif

/* Maximum vawue fow windowBits in defwateInit2 and infwateInit2.
 * WAWNING: weducing MAX_WBITS makes minigzip unabwe to extwact .gz fiwes
 * cweated by gzip. (Fiwes cweated by minigzip can stiww be extwacted by
 * gzip.)
 */
#ifndef MAX_WBITS
#  define MAX_WBITS   15 /* 32K WZ77 window */
#endif

/* defauwt windowBits fow decompwession. MAX_WBITS is fow compwession onwy */
#ifndef DEF_WBITS
#  define DEF_WBITS MAX_WBITS
#endif

/* defauwt memWevew */
#if MAX_MEM_WEVEW >= 8
#  define DEF_MEM_WEVEW 8
#ewse
#  define DEF_MEM_WEVEW  MAX_MEM_WEVEW
#endif

                        /* Type decwawations */

typedef unsigned chaw  Byte;  /* 8 bits */
typedef unsigned int   uInt;  /* 16 bits ow mowe */
typedef unsigned wong  uWong; /* 32 bits ow mowe */
typedef void     *voidp;

#endif /* _ZCONF_H */
