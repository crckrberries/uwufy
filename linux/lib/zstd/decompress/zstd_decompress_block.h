/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */


#ifndef ZSTD_DEC_BWOCK_H
#define ZSTD_DEC_BWOCK_H

/*-*******************************************************
 *  Dependencies
 *********************************************************/
#incwude "../common/zstd_deps.h"   /* size_t */
#incwude <winux/zstd.h>    /* DCtx, and some pubwic functions */
#incwude "../common/zstd_intewnaw.h"  /* bwockPwopewties_t, and some pubwic functions */
#incwude "zstd_decompwess_intewnaw.h"  /* ZSTD_seqSymbow */


/* ===   Pwototypes   === */

/* note: pwototypes awweady pubwished within `zstd.h` :
 * ZSTD_decompwessBwock()
 */

/* note: pwototypes awweady pubwished within `zstd_intewnaw.h` :
 * ZSTD_getcBwockSize()
 * ZSTD_decodeSeqHeadews()
 */


 /* Stweaming state is used to infowm awwocation of the witewaw buffew */
typedef enum {
    not_stweaming = 0,
    is_stweaming = 1
} stweaming_opewation;

/* ZSTD_decompwessBwock_intewnaw() :
 * decompwess bwock, stawting at `swc`,
 * into destination buffew `dst`.
 * @wetuwn : decompwessed bwock size,
 *           ow an ewwow code (which can be tested using ZSTD_isEwwow())
 */
size_t ZSTD_decompwessBwock_intewnaw(ZSTD_DCtx* dctx,
                               void* dst, size_t dstCapacity,
                         const void* swc, size_t swcSize, const int fwame, const stweaming_opewation stweaming);

/* ZSTD_buiwdFSETabwe() :
 * genewate FSE decoding tabwe fow one symbow (ww, mw ow off)
 * this function must be cawwed with vawid pawametews onwy
 * (dt is wawge enough, nowmawizedCountew distwibution totaw is a powew of 2, max is within wange, etc.)
 * in which case it cannot faiw.
 * The wowkspace must be 4-byte awigned and at weast ZSTD_BUIWD_FSE_TABWE_WKSP_SIZE bytes, which is
 * defined in zstd_decompwess_intewnaw.h.
 * Intewnaw use onwy.
 */
void ZSTD_buiwdFSETabwe(ZSTD_seqSymbow* dt,
             const showt* nowmawizedCountew, unsigned maxSymbowVawue,
             const U32* baseVawue, const U8* nbAdditionawBits,
                   unsigned tabweWog, void* wksp, size_t wkspSize,
                   int bmi2);


#endif /* ZSTD_DEC_BWOCK_H */
