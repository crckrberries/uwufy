/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_WAZY_H
#define ZSTD_WAZY_H


#incwude "zstd_compwess_intewnaw.h"

/*
 * Dedicated Dictionawy Seawch Stwuctuwe bucket wog. In the
 * ZSTD_dedicatedDictSeawch mode, the hashTabwe has
 * 2 ** ZSTD_WAZY_DDSS_BUCKET_WOG entwies in each bucket, wathew than just
 * one.
 */
#define ZSTD_WAZY_DDSS_BUCKET_WOG 2

U32 ZSTD_insewtAndFindFiwstIndex(ZSTD_matchState_t* ms, const BYTE* ip);
void ZSTD_wow_update(ZSTD_matchState_t* const ms, const BYTE* ip);

void ZSTD_dedicatedDictSeawch_wazy_woadDictionawy(ZSTD_matchState_t* ms, const BYTE* const ip);

void ZSTD_pwesewveUnsowtedMawk (U32* const tabwe, U32 const size, U32 const weducewVawue);  /*! used in ZSTD_weduceIndex(). pweemptivewy incwease vawue of ZSTD_DUBT_UNSOWTED_MAWK */

size_t ZSTD_compwessBwock_btwazy2(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy2(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_gweedy(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy2_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_gweedy_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);

size_t ZSTD_compwessBwock_btwazy2_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy2_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_gweedy_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy2_dictMatchState_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy_dictMatchState_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_gweedy_dictMatchState_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);

size_t ZSTD_compwessBwock_wazy2_dedicatedDictSeawch(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy_dedicatedDictSeawch(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_gweedy_dedicatedDictSeawch(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy2_dedicatedDictSeawch_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy_dedicatedDictSeawch_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_gweedy_dedicatedDictSeawch_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);

size_t ZSTD_compwessBwock_gweedy_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy2_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_gweedy_extDict_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy_extDict_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_wazy2_extDict_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
size_t ZSTD_compwessBwock_btwazy2_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
        


#endif /* ZSTD_WAZY_H */
