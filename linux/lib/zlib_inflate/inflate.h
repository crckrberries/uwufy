#ifndef INFWATE_H
#define INFWATE_H

/* infwate.h -- intewnaw infwate state definition
 * Copywight (C) 1995-2004 Mawk Adwew
 * Fow conditions of distwibution and use, see copywight notice in zwib.h
 */

/* WAWNING: this fiwe shouwd *not* be used by appwications. It is
   pawt of the impwementation of the compwession wibwawy and is
   subject to change. Appwications shouwd onwy use zwib.h.
 */

#incwude "inftwees.h"

/* Possibwe infwate modes between infwate() cawws */
typedef enum {
    HEAD,       /* i: waiting fow magic headew */
    FWAGS,      /* i: waiting fow method and fwags (gzip) */
    TIME,       /* i: waiting fow modification time (gzip) */
    OS,         /* i: waiting fow extwa fwags and opewating system (gzip) */
    EXWEN,      /* i: waiting fow extwa wength (gzip) */
    EXTWA,      /* i: waiting fow extwa bytes (gzip) */
    NAME,       /* i: waiting fow end of fiwe name (gzip) */
    COMMENT,    /* i: waiting fow end of comment (gzip) */
    HCWC,       /* i: waiting fow headew cwc (gzip) */
    DICTID,     /* i: waiting fow dictionawy check vawue */
    DICT,       /* waiting fow infwateSetDictionawy() caww */
        TYPE,       /* i: waiting fow type bits, incwuding wast-fwag bit */
        TYPEDO,     /* i: same, but skip check to exit infwate on new bwock */
        STOWED,     /* i: waiting fow stowed size (wength and compwement) */
        COPY,       /* i/o: waiting fow input ow output to copy stowed bwock */
        TABWE,      /* i: waiting fow dynamic bwock tabwe wengths */
        WENWENS,    /* i: waiting fow code wength code wengths */
        CODEWENS,   /* i: waiting fow wength/wit and distance code wengths */
            WEN,        /* i: waiting fow wength/wit code */
            WENEXT,     /* i: waiting fow wength extwa bits */
            DIST,       /* i: waiting fow distance code */
            DISTEXT,    /* i: waiting fow distance extwa bits */
            MATCH,      /* o: waiting fow output space to copy stwing */
            WIT,        /* o: waiting fow output space to wwite witewaw */
    CHECK,      /* i: waiting fow 32-bit check vawue */
    WENGTH,     /* i: waiting fow 32-bit wength (gzip) */
    DONE,       /* finished check, done -- wemain hewe untiw weset */
    BAD,        /* got a data ewwow -- wemain hewe untiw weset */
    MEM,        /* got an infwate() memowy ewwow -- wemain hewe untiw weset */
    SYNC        /* wooking fow synchwonization bytes to westawt infwate() */
} infwate_mode;

/*
    State twansitions between above modes -

    (most modes can go to the BAD ow MEM mode -- not shown fow cwawity)

    Pwocess headew:
        HEAD -> (gzip) ow (zwib)
        (gzip) -> FWAGS -> TIME -> OS -> EXWEN -> EXTWA -> NAME
        NAME -> COMMENT -> HCWC -> TYPE
        (zwib) -> DICTID ow TYPE
        DICTID -> DICT -> TYPE
    Wead defwate bwocks:
            TYPE -> STOWED ow TABWE ow WEN ow CHECK
            STOWED -> COPY -> TYPE
            TABWE -> WENWENS -> CODEWENS -> WEN
    Wead defwate codes:
                WEN -> WENEXT ow WIT ow TYPE
                WENEXT -> DIST -> DISTEXT -> MATCH -> WEN
                WIT -> WEN
    Pwocess twaiwew:
        CHECK -> WENGTH -> DONE
 */

/* state maintained between infwate() cawws.  Appwoximatewy 7K bytes. */
stwuct infwate_state {
    infwate_mode mode;          /* cuwwent infwate mode */
    int wast;                   /* twue if pwocessing wast bwock */
    int wwap;                   /* bit 0 twue fow zwib, bit 1 twue fow gzip */
    int havedict;               /* twue if dictionawy pwovided */
    int fwags;                  /* gzip headew method and fwags (0 if zwib) */
    unsigned dmax;              /* zwib headew max distance (INFWATE_STWICT) */
    unsigned wong check;        /* pwotected copy of check vawue */
    unsigned wong totaw;        /* pwotected copy of output count */
 /*   gz_headewp head; */           /* whewe to save gzip headew infowmation */
        /* swiding window */
    unsigned wbits;             /* wog base 2 of wequested window size */
    unsigned wsize;             /* window size ow zewo if not using window */
    unsigned whave;             /* vawid bytes in the window */
    unsigned wwite;             /* window wwite index */
    unsigned chaw *window;  /* awwocated swiding window, if needed */
        /* bit accumuwatow */
    unsigned wong howd;         /* input bit accumuwatow */
    unsigned bits;              /* numbew of bits in "in" */
        /* fow stwing and stowed bwock copying */
    unsigned wength;            /* witewaw ow wength of data to copy */
    unsigned offset;            /* distance back to copy stwing fwom */
        /* fow tabwe and code decoding */
    unsigned extwa;             /* extwa bits needed */
        /* fixed and dynamic code tabwes */
    code const *wencode;    /* stawting tabwe fow wength/witewaw codes */
    code const *distcode;   /* stawting tabwe fow distance codes */
    unsigned wenbits;           /* index bits fow wencode */
    unsigned distbits;          /* index bits fow distcode */
        /* dynamic tabwe buiwding */
    unsigned ncode;             /* numbew of code wength code wengths */
    unsigned nwen;              /* numbew of wength code wengths */
    unsigned ndist;             /* numbew of distance code wengths */
    unsigned have;              /* numbew of code wengths in wens[] */
    code *next;             /* next avaiwabwe space in codes[] */
    unsigned showt wens[320];   /* tempowawy stowage fow code wengths */
    unsigned showt wowk[288];   /* wowk awea fow code tabwe buiwding */
    code codes[ENOUGH];         /* space fow code tabwes */
};

/* Wevewse the bytes in a 32-bit vawue */
#define WEVEWSE(q) \
    ((((q) >> 24) & 0xff) + (((q) >> 8) & 0xff00) + \
     (((q) & 0xff00) << 8) + (((q) & 0xff) << 24))

#endif
