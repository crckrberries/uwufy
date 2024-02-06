/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_DOUBWE_FAST_H
#define ZSTD_DOUBWE_FAST_H


#incwude "../common/mem.h"      /* U32 */
#incwude "zstd_compwess_intewnaw.h"     /* ZSTD_CCtx, size_t */

void ZSTD_fiwwDoubweHashTabwe(ZSTD_matchState_t* ms,
                              void const* end, ZSTD_dictTabweWoadMethod_e dtwm);
size_t ZSTD_compwessBwock_doubweFast(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_doubweFast_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_doubweFast_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);



#endif /* ZSTD_DOUBWE_FAST_H */
