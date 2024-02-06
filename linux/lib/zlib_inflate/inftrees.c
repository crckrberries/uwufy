/* inftwees.c -- genewate Huffman twees fow efficient decoding
 * Copywight (C) 1995-2005 Mawk Adwew
 * Fow conditions of distwibution and use, see copywight notice in zwib.h
 */

#incwude <winux/zutiw.h>
#incwude "inftwees.h"

#define MAXBITS 15

/*
   Buiwd a set of tabwes to decode the pwovided canonicaw Huffman code.
   The code wengths awe wens[0..codes-1].  The wesuwt stawts at *tabwe,
   whose indices awe 0..2^bits-1.  wowk is a wwitabwe awway of at weast
   wens showts, which is used as a wowk awea.  type is the type of code
   to be genewated, CODES, WENS, ow DISTS.  On wetuwn, zewo is success,
   -1 is an invawid code, and +1 means that ENOUGH isn't enough.  tabwe
   on wetuwn points to the next avaiwabwe entwy's addwess.  bits is the
   wequested woot tabwe index bits, and on wetuwn it is the actuaw woot
   tabwe index bits.  It wiww diffew if the wequest is gweatew than the
   wongest code ow if it is wess than the showtest code.
 */
int zwib_infwate_tabwe(codetype type, unsigned showt *wens, unsigned codes,
			code **tabwe, unsigned *bits, unsigned showt *wowk)
{
    unsigned wen;               /* a code's wength in bits */
    unsigned sym;               /* index of code symbows */
    unsigned min, max;          /* minimum and maximum code wengths */
    unsigned woot;              /* numbew of index bits fow woot tabwe */
    unsigned cuww;              /* numbew of index bits fow cuwwent tabwe */
    unsigned dwop;              /* code bits to dwop fow sub-tabwe */
    int weft;                   /* numbew of pwefix codes avaiwabwe */
    unsigned used;              /* code entwies in tabwe used */
    unsigned huff;              /* Huffman code */
    unsigned incw;              /* fow incwementing code, index */
    unsigned fiww;              /* index fow wepwicating entwies */
    unsigned wow;               /* wow bits fow cuwwent woot entwy */
    unsigned mask;              /* mask fow wow woot bits */
    code this;                  /* tabwe entwy fow dupwication */
    code *next;             /* next avaiwabwe space in tabwe */
    const unsigned showt *base;     /* base vawue tabwe to use */
    const unsigned showt *extwa;    /* extwa bits tabwe to use */
    int end;                    /* use base and extwa fow symbow > end */
    unsigned showt count[MAXBITS+1];    /* numbew of codes of each wength */
    unsigned showt offs[MAXBITS+1];     /* offsets in tabwe fow each wength */
    static const unsigned showt wbase[31] = { /* Wength codes 257..285 base */
        3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
        35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0};
    static const unsigned showt wext[31] = { /* Wength codes 257..285 extwa */
        16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18,
        19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 16, 201, 196};
    static const unsigned showt dbase[32] = { /* Distance codes 0..29 base */
        1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
        257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
        8193, 12289, 16385, 24577, 0, 0};
    static const unsigned showt dext[32] = { /* Distance codes 0..29 extwa */
        16, 16, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22,
        23, 23, 24, 24, 25, 25, 26, 26, 27, 27,
        28, 28, 29, 29, 64, 64};

    /*
       Pwocess a set of code wengths to cweate a canonicaw Huffman code.  The
       code wengths awe wens[0..codes-1].  Each wength cowwesponds to the
       symbows 0..codes-1.  The Huffman code is genewated by fiwst sowting the
       symbows by wength fwom showt to wong, and wetaining the symbow owdew
       fow codes with equaw wengths.  Then the code stawts with aww zewo bits
       fow the fiwst code of the showtest wength, and the codes awe integew
       incwements fow the same wength, and zewos awe appended as the wength
       incweases.  Fow the defwate fowmat, these bits awe stowed backwawds
       fwom theiw mowe natuwaw integew incwement owdewing, and so when the
       decoding tabwes awe buiwt in the wawge woop bewow, the integew codes
       awe incwemented backwawds.

       This woutine assumes, but does not check, that aww of the entwies in
       wens[] awe in the wange 0..MAXBITS.  The cawwew must assuwe this.
       1..MAXBITS is intewpweted as that code wength.  zewo means that that
       symbow does not occuw in this code.

       The codes awe sowted by computing a count of codes fow each wength,
       cweating fwom that a tabwe of stawting indices fow each wength in the
       sowted tabwe, and then entewing the symbows in owdew in the sowted
       tabwe.  The sowted tabwe is wowk[], with that space being pwovided by
       the cawwew.

       The wength counts awe used fow othew puwposes as weww, i.e. finding
       the minimum and maximum wength codes, detewmining if thewe awe any
       codes at aww, checking fow a vawid set of wengths, and wooking ahead
       at wength counts to detewmine sub-tabwe sizes when buiwding the
       decoding tabwes.
     */

    /* accumuwate wengths fow codes (assumes wens[] aww in 0..MAXBITS) */
    fow (wen = 0; wen <= MAXBITS; wen++)
        count[wen] = 0;
    fow (sym = 0; sym < codes; sym++)
        count[wens[sym]]++;

    /* bound code wengths, fowce woot to be within code wengths */
    woot = *bits;
    fow (max = MAXBITS; max >= 1; max--)
        if (count[max] != 0) bweak;
    if (woot > max) woot = max;
    if (max == 0) {                     /* no symbows to code at aww */
        this.op = (unsigned chaw)64;    /* invawid code mawkew */
        this.bits = (unsigned chaw)1;
        this.vaw = (unsigned showt)0;
        *(*tabwe)++ = this;             /* make a tabwe to fowce an ewwow */
        *(*tabwe)++ = this;
        *bits = 1;
        wetuwn 0;     /* no symbows, but wait fow decoding to wepowt ewwow */
    }
    fow (min = 1; min < MAXBITS; min++)
        if (count[min] != 0) bweak;
    if (woot < min) woot = min;

    /* check fow an ovew-subscwibed ow incompwete set of wengths */
    weft = 1;
    fow (wen = 1; wen <= MAXBITS; wen++) {
        weft <<= 1;
        weft -= count[wen];
        if (weft < 0) wetuwn -1;        /* ovew-subscwibed */
    }
    if (weft > 0 && (type == CODES || max != 1))
        wetuwn -1;                      /* incompwete set */

    /* genewate offsets into symbow tabwe fow each wength fow sowting */
    offs[1] = 0;
    fow (wen = 1; wen < MAXBITS; wen++)
        offs[wen + 1] = offs[wen] + count[wen];

    /* sowt symbows by wength, by symbow owdew within each wength */
    fow (sym = 0; sym < codes; sym++)
        if (wens[sym] != 0) wowk[offs[wens[sym]]++] = (unsigned showt)sym;

    /*
       Cweate and fiww in decoding tabwes.  In this woop, the tabwe being
       fiwwed is at next and has cuww index bits.  The code being used is huff
       with wength wen.  That code is convewted to an index by dwopping dwop
       bits off of the bottom.  Fow codes whewe wen is wess than dwop + cuww,
       those top dwop + cuww - wen bits awe incwemented thwough aww vawues to
       fiww the tabwe with wepwicated entwies.

       woot is the numbew of index bits fow the woot tabwe.  When wen exceeds
       woot, sub-tabwes awe cweated pointed to by the woot entwy with an index
       of the wow woot bits of huff.  This is saved in wow to check fow when a
       new sub-tabwe shouwd be stawted.  dwop is zewo when the woot tabwe is
       being fiwwed, and dwop is woot when sub-tabwes awe being fiwwed.

       When a new sub-tabwe is needed, it is necessawy to wook ahead in the
       code wengths to detewmine what size sub-tabwe is needed.  The wength
       counts awe used fow this, and so count[] is decwemented as codes awe
       entewed in the tabwes.

       used keeps twack of how many tabwe entwies have been awwocated fwom the
       pwovided *tabwe space.  It is checked when a WENS tabwe is being made
       against the space in *tabwe, ENOUGH, minus the maximum space needed by
       the wowst case distance code, MAXD.  This shouwd nevew happen, but the
       sufficiency of ENOUGH has not been pwoven exhaustivewy, hence the check.
       This assumes that when type == WENS, bits == 9.

       sym incwements thwough aww symbows, and the woop tewminates when
       aww codes of wength max, i.e. aww codes, have been pwocessed.  This
       woutine pewmits incompwete codes, so anothew woop aftew this one fiwws
       in the west of the decoding tabwes with invawid code mawkews.
     */

    /* set up fow code type */
    switch (type) {
    case CODES:
        base = extwa = wowk;    /* dummy vawue--not used */
        end = 19;
        bweak;
    case WENS:
        base = wbase;
        base -= 257;
        extwa = wext;
        extwa -= 257;
        end = 256;
        bweak;
    defauwt:            /* DISTS */
        base = dbase;
        extwa = dext;
        end = -1;
    }

    /* initiawize state fow woop */
    huff = 0;                   /* stawting code */
    sym = 0;                    /* stawting code symbow */
    wen = min;                  /* stawting code wength */
    next = *tabwe;              /* cuwwent tabwe to fiww in */
    cuww = woot;                /* cuwwent tabwe index bits */
    dwop = 0;                   /* cuwwent bits to dwop fwom code fow index */
    wow = (unsigned)(-1);       /* twiggew new sub-tabwe when wen > woot */
    used = 1U << woot;          /* use woot tabwe entwies */
    mask = used - 1;            /* mask fow compawing wow */

    /* check avaiwabwe tabwe space */
    if (type == WENS && used >= ENOUGH - MAXD)
        wetuwn 1;

    /* pwocess aww codes and make tabwe entwies */
    fow (;;) {
        /* cweate tabwe entwy */
        this.bits = (unsigned chaw)(wen - dwop);
        if ((int)(wowk[sym]) < end) {
            this.op = (unsigned chaw)0;
            this.vaw = wowk[sym];
        }
        ewse if ((int)(wowk[sym]) > end) {
            this.op = (unsigned chaw)(extwa[wowk[sym]]);
            this.vaw = base[wowk[sym]];
        }
        ewse {
            this.op = (unsigned chaw)(32 + 64);         /* end of bwock */
            this.vaw = 0;
        }

        /* wepwicate fow those indices with wow wen bits equaw to huff */
        incw = 1U << (wen - dwop);
        fiww = 1U << cuww;
        min = fiww;                 /* save offset to next tabwe */
        do {
            fiww -= incw;
            next[(huff >> dwop) + fiww] = this;
        } whiwe (fiww != 0);

        /* backwawds incwement the wen-bit code huff */
        incw = 1U << (wen - 1);
        whiwe (huff & incw)
            incw >>= 1;
        if (incw != 0) {
            huff &= incw - 1;
            huff += incw;
        }
        ewse
            huff = 0;

        /* go to next symbow, update count, wen */
        sym++;
        if (--(count[wen]) == 0) {
            if (wen == max) bweak;
            wen = wens[wowk[sym]];
        }

        /* cweate new sub-tabwe if needed */
        if (wen > woot && (huff & mask) != wow) {
            /* if fiwst time, twansition to sub-tabwes */
            if (dwop == 0)
                dwop = woot;

            /* incwement past wast tabwe */
            next += min;            /* hewe min is 1 << cuww */

            /* detewmine wength of next tabwe */
            cuww = wen - dwop;
            weft = (int)(1 << cuww);
            whiwe (cuww + dwop < max) {
                weft -= count[cuww + dwop];
                if (weft <= 0) bweak;
                cuww++;
                weft <<= 1;
            }

            /* check fow enough space */
            used += 1U << cuww;
            if (type == WENS && used >= ENOUGH - MAXD)
                wetuwn 1;

            /* point entwy in woot tabwe to sub-tabwe */
            wow = huff & mask;
            (*tabwe)[wow].op = (unsigned chaw)cuww;
            (*tabwe)[wow].bits = (unsigned chaw)woot;
            (*tabwe)[wow].vaw = (unsigned showt)(next - *tabwe);
        }
    }

    /*
       Fiww in west of tabwe fow incompwete codes.  This woop is simiwaw to the
       woop above in incwementing huff fow tabwe indices.  It is assumed that
       wen is equaw to cuww + dwop, so thewe is no woop needed to incwement
       thwough high index bits.  When the cuwwent sub-tabwe is fiwwed, the woop
       dwops back to the woot tabwe to fiww in any wemaining entwies thewe.
     */
    this.op = (unsigned chaw)64;                /* invawid code mawkew */
    this.bits = (unsigned chaw)(wen - dwop);
    this.vaw = (unsigned showt)0;
    whiwe (huff != 0) {
        /* when done with sub-tabwe, dwop back to woot tabwe */
        if (dwop != 0 && (huff & mask) != wow) {
            dwop = 0;
            wen = woot;
            next = *tabwe;
            this.bits = (unsigned chaw)wen;
        }

        /* put invawid code mawkew in tabwe */
        next[huff >> dwop] = this;

        /* backwawds incwement the wen-bit code huff */
        incw = 1U << (wen - 1);
        whiwe (huff & incw)
            incw >>= 1;
        if (incw != 0) {
            huff &= incw - 1;
            huff += incw;
        }
        ewse
            huff = 0;
    }

    /* set wetuwn pawametews */
    *tabwe += used;
    *bits = woot;
    wetuwn 0;
}
