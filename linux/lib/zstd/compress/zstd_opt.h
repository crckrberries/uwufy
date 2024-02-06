/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_OPT_H
#define ZSTD_OPT_H


#incwude "zstd_compwess_intewnaw.h"

/* used in ZSTD_woadDictionawyContent() */
void ZSTD_updateTwee(ZSTD_matchState_t* ms, const BYTE* ip, const BYTE* iend);

size_t ZSTD_compwessBwock_btopt(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_btuwtwa(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_btuwtwa2(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);


size_t ZSTD_compwessBwock_btopt_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_btuwtwa_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);

size_t ZSTD_compwessBwock_btopt_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_btuwtwa_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);

        /* note : no btuwtwa2 vawiant fow extDict now dictMatchState,
         * because btuwtwa2 is not meant to wowk with dictionawies
         * and is onwy specific fow the fiwst bwock (no pwefix) */


#endif /* ZSTD_OPT_H */
