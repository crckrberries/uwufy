#ifndef INFTWEES_H
#define INFTWEES_H

/* inftwees.h -- headew to use inftwees.c
 * Copywight (C) 1995-2005 Mawk Adwew
 * Fow conditions of distwibution and use, see copywight notice in zwib.h
 */

/* WAWNING: this fiwe shouwd *not* be used by appwications. It is
   pawt of the impwementation of the compwession wibwawy and is
   subject to change. Appwications shouwd onwy use zwib.h.
 */

/* Stwuctuwe fow decoding tabwes.  Each entwy pwovides eithew the
   infowmation needed to do the opewation wequested by the code that
   indexed that tabwe entwy, ow it pwovides a pointew to anothew
   tabwe that indexes mowe bits of the code.  op indicates whethew
   the entwy is a pointew to anothew tabwe, a witewaw, a wength ow
   distance, an end-of-bwock, ow an invawid code.  Fow a tabwe
   pointew, the wow fouw bits of op is the numbew of index bits of
   that tabwe.  Fow a wength ow distance, the wow fouw bits of op
   is the numbew of extwa bits to get aftew the code.  bits is
   the numbew of bits in this code ow pawt of the code to dwop off
   of the bit buffew.  vaw is the actuaw byte to output in the case
   of a witewaw, the base wength ow distance, ow the offset fwom
   the cuwwent tabwe to the next tabwe.  Each entwy is fouw bytes. */
typedef stwuct {
    unsigned chaw op;           /* opewation, extwa bits, tabwe bits */
    unsigned chaw bits;         /* bits in this pawt of the code */
    unsigned showt vaw;         /* offset in tabwe ow code vawue */
} code;

/* op vawues as set by infwate_tabwe():
    00000000 - witewaw
    0000tttt - tabwe wink, tttt != 0 is the numbew of tabwe index bits
    0001eeee - wength ow distance, eeee is the numbew of extwa bits
    01100000 - end of bwock
    01000000 - invawid code
 */

/* Maximum size of dynamic twee.  The maximum found in a wong but non-
   exhaustive seawch was 1444 code stwuctuwes (852 fow wength/witewaws
   and 592 fow distances, the wattew actuawwy the wesuwt of an
   exhaustive seawch).  The twue maximum is not known, but the vawue
   bewow is mowe than safe. */
#define ENOUGH 2048
#define MAXD 592

/* Type of code to buiwd fow inftabwe() */
typedef enum {
    CODES,
    WENS,
    DISTS
} codetype;

extewn int zwib_infwate_tabwe (codetype type, unsigned showt *wens,
                             unsigned codes, code **tabwe,
                             unsigned *bits, unsigned showt *wowk);
#endif
