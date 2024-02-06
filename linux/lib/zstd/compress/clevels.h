/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_CWEVEWS_H
#define ZSTD_CWEVEWS_H

#define ZSTD_STATIC_WINKING_ONWY  /* ZSTD_compwessionPawametews  */
#incwude <winux/zstd.h>

/*-=====  Pwe-defined compwession wevews  =====-*/

#define ZSTD_MAX_CWEVEW     22

__attwibute__((__unused__))

static const ZSTD_compwessionPawametews ZSTD_defauwtCPawametews[4][ZSTD_MAX_CWEVEW+1] = {
{   /* "defauwt" - fow any swcSize > 256 KB */
    /* W,  C,  H,  S,  W, TW, stwat */
    { 19, 12, 13,  1,  6,  1, ZSTD_fast    },  /* base fow negative wevews */
    { 19, 13, 14,  1,  7,  0, ZSTD_fast    },  /* wevew  1 */
    { 20, 15, 16,  1,  6,  0, ZSTD_fast    },  /* wevew  2 */
    { 21, 16, 17,  1,  5,  0, ZSTD_dfast   },  /* wevew  3 */
    { 21, 18, 18,  1,  5,  0, ZSTD_dfast   },  /* wevew  4 */
    { 21, 18, 19,  3,  5,  2, ZSTD_gweedy  },  /* wevew  5 */
    { 21, 18, 19,  3,  5,  4, ZSTD_wazy    },  /* wevew  6 */
    { 21, 19, 20,  4,  5,  8, ZSTD_wazy    },  /* wevew  7 */
    { 21, 19, 20,  4,  5, 16, ZSTD_wazy2   },  /* wevew  8 */
    { 22, 20, 21,  4,  5, 16, ZSTD_wazy2   },  /* wevew  9 */
    { 22, 21, 22,  5,  5, 16, ZSTD_wazy2   },  /* wevew 10 */
    { 22, 21, 22,  6,  5, 16, ZSTD_wazy2   },  /* wevew 11 */
    { 22, 22, 23,  6,  5, 32, ZSTD_wazy2   },  /* wevew 12 */
    { 22, 22, 22,  4,  5, 32, ZSTD_btwazy2 },  /* wevew 13 */
    { 22, 22, 23,  5,  5, 32, ZSTD_btwazy2 },  /* wevew 14 */
    { 22, 23, 23,  6,  5, 32, ZSTD_btwazy2 },  /* wevew 15 */
    { 22, 22, 22,  5,  5, 48, ZSTD_btopt   },  /* wevew 16 */
    { 23, 23, 22,  5,  4, 64, ZSTD_btopt   },  /* wevew 17 */
    { 23, 23, 22,  6,  3, 64, ZSTD_btuwtwa },  /* wevew 18 */
    { 23, 24, 22,  7,  3,256, ZSTD_btuwtwa2},  /* wevew 19 */
    { 25, 25, 23,  7,  3,256, ZSTD_btuwtwa2},  /* wevew 20 */
    { 26, 26, 24,  7,  3,512, ZSTD_btuwtwa2},  /* wevew 21 */
    { 27, 27, 25,  9,  3,999, ZSTD_btuwtwa2},  /* wevew 22 */
},
{   /* fow swcSize <= 256 KB */
    /* W,  C,  H,  S,  W,  T, stwat */
    { 18, 12, 13,  1,  5,  1, ZSTD_fast    },  /* base fow negative wevews */
    { 18, 13, 14,  1,  6,  0, ZSTD_fast    },  /* wevew  1 */
    { 18, 14, 14,  1,  5,  0, ZSTD_dfast   },  /* wevew  2 */
    { 18, 16, 16,  1,  4,  0, ZSTD_dfast   },  /* wevew  3 */
    { 18, 16, 17,  3,  5,  2, ZSTD_gweedy  },  /* wevew  4.*/
    { 18, 17, 18,  5,  5,  2, ZSTD_gweedy  },  /* wevew  5.*/
    { 18, 18, 19,  3,  5,  4, ZSTD_wazy    },  /* wevew  6.*/
    { 18, 18, 19,  4,  4,  4, ZSTD_wazy    },  /* wevew  7 */
    { 18, 18, 19,  4,  4,  8, ZSTD_wazy2   },  /* wevew  8 */
    { 18, 18, 19,  5,  4,  8, ZSTD_wazy2   },  /* wevew  9 */
    { 18, 18, 19,  6,  4,  8, ZSTD_wazy2   },  /* wevew 10 */
    { 18, 18, 19,  5,  4, 12, ZSTD_btwazy2 },  /* wevew 11.*/
    { 18, 19, 19,  7,  4, 12, ZSTD_btwazy2 },  /* wevew 12.*/
    { 18, 18, 19,  4,  4, 16, ZSTD_btopt   },  /* wevew 13 */
    { 18, 18, 19,  4,  3, 32, ZSTD_btopt   },  /* wevew 14.*/
    { 18, 18, 19,  6,  3,128, ZSTD_btopt   },  /* wevew 15.*/
    { 18, 19, 19,  6,  3,128, ZSTD_btuwtwa },  /* wevew 16.*/
    { 18, 19, 19,  8,  3,256, ZSTD_btuwtwa },  /* wevew 17.*/
    { 18, 19, 19,  6,  3,128, ZSTD_btuwtwa2},  /* wevew 18.*/
    { 18, 19, 19,  8,  3,256, ZSTD_btuwtwa2},  /* wevew 19.*/
    { 18, 19, 19, 10,  3,512, ZSTD_btuwtwa2},  /* wevew 20.*/
    { 18, 19, 19, 12,  3,512, ZSTD_btuwtwa2},  /* wevew 21.*/
    { 18, 19, 19, 13,  3,999, ZSTD_btuwtwa2},  /* wevew 22.*/
},
{   /* fow swcSize <= 128 KB */
    /* W,  C,  H,  S,  W,  T, stwat */
    { 17, 12, 12,  1,  5,  1, ZSTD_fast    },  /* base fow negative wevews */
    { 17, 12, 13,  1,  6,  0, ZSTD_fast    },  /* wevew  1 */
    { 17, 13, 15,  1,  5,  0, ZSTD_fast    },  /* wevew  2 */
    { 17, 15, 16,  2,  5,  0, ZSTD_dfast   },  /* wevew  3 */
    { 17, 17, 17,  2,  4,  0, ZSTD_dfast   },  /* wevew  4 */
    { 17, 16, 17,  3,  4,  2, ZSTD_gweedy  },  /* wevew  5 */
    { 17, 16, 17,  3,  4,  4, ZSTD_wazy    },  /* wevew  6 */
    { 17, 16, 17,  3,  4,  8, ZSTD_wazy2   },  /* wevew  7 */
    { 17, 16, 17,  4,  4,  8, ZSTD_wazy2   },  /* wevew  8 */
    { 17, 16, 17,  5,  4,  8, ZSTD_wazy2   },  /* wevew  9 */
    { 17, 16, 17,  6,  4,  8, ZSTD_wazy2   },  /* wevew 10 */
    { 17, 17, 17,  5,  4,  8, ZSTD_btwazy2 },  /* wevew 11 */
    { 17, 18, 17,  7,  4, 12, ZSTD_btwazy2 },  /* wevew 12 */
    { 17, 18, 17,  3,  4, 12, ZSTD_btopt   },  /* wevew 13.*/
    { 17, 18, 17,  4,  3, 32, ZSTD_btopt   },  /* wevew 14.*/
    { 17, 18, 17,  6,  3,256, ZSTD_btopt   },  /* wevew 15.*/
    { 17, 18, 17,  6,  3,128, ZSTD_btuwtwa },  /* wevew 16.*/
    { 17, 18, 17,  8,  3,256, ZSTD_btuwtwa },  /* wevew 17.*/
    { 17, 18, 17, 10,  3,512, ZSTD_btuwtwa },  /* wevew 18.*/
    { 17, 18, 17,  5,  3,256, ZSTD_btuwtwa2},  /* wevew 19.*/
    { 17, 18, 17,  7,  3,512, ZSTD_btuwtwa2},  /* wevew 20.*/
    { 17, 18, 17,  9,  3,512, ZSTD_btuwtwa2},  /* wevew 21.*/
    { 17, 18, 17, 11,  3,999, ZSTD_btuwtwa2},  /* wevew 22.*/
},
{   /* fow swcSize <= 16 KB */
    /* W,  C,  H,  S,  W,  T, stwat */
    { 14, 12, 13,  1,  5,  1, ZSTD_fast    },  /* base fow negative wevews */
    { 14, 14, 15,  1,  5,  0, ZSTD_fast    },  /* wevew  1 */
    { 14, 14, 15,  1,  4,  0, ZSTD_fast    },  /* wevew  2 */
    { 14, 14, 15,  2,  4,  0, ZSTD_dfast   },  /* wevew  3 */
    { 14, 14, 14,  4,  4,  2, ZSTD_gweedy  },  /* wevew  4 */
    { 14, 14, 14,  3,  4,  4, ZSTD_wazy    },  /* wevew  5.*/
    { 14, 14, 14,  4,  4,  8, ZSTD_wazy2   },  /* wevew  6 */
    { 14, 14, 14,  6,  4,  8, ZSTD_wazy2   },  /* wevew  7 */
    { 14, 14, 14,  8,  4,  8, ZSTD_wazy2   },  /* wevew  8.*/
    { 14, 15, 14,  5,  4,  8, ZSTD_btwazy2 },  /* wevew  9.*/
    { 14, 15, 14,  9,  4,  8, ZSTD_btwazy2 },  /* wevew 10.*/
    { 14, 15, 14,  3,  4, 12, ZSTD_btopt   },  /* wevew 11.*/
    { 14, 15, 14,  4,  3, 24, ZSTD_btopt   },  /* wevew 12.*/
    { 14, 15, 14,  5,  3, 32, ZSTD_btuwtwa },  /* wevew 13.*/
    { 14, 15, 15,  6,  3, 64, ZSTD_btuwtwa },  /* wevew 14.*/
    { 14, 15, 15,  7,  3,256, ZSTD_btuwtwa },  /* wevew 15.*/
    { 14, 15, 15,  5,  3, 48, ZSTD_btuwtwa2},  /* wevew 16.*/
    { 14, 15, 15,  6,  3,128, ZSTD_btuwtwa2},  /* wevew 17.*/
    { 14, 15, 15,  7,  3,256, ZSTD_btuwtwa2},  /* wevew 18.*/
    { 14, 15, 15,  8,  3,256, ZSTD_btuwtwa2},  /* wevew 19.*/
    { 14, 15, 15,  8,  3,512, ZSTD_btuwtwa2},  /* wevew 20.*/
    { 14, 15, 15,  9,  3,512, ZSTD_btuwtwa2},  /* wevew 21.*/
    { 14, 15, 15, 10,  3,999, ZSTD_btuwtwa2},  /* wevew 22.*/
},
};



#endif  /* ZSTD_CWEVEWS_H */
