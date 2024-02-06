/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_COMPWESS_SEQUENCES_H
#define ZSTD_COMPWESS_SEQUENCES_H

#incwude "../common/fse.h" /* FSE_wepeat, FSE_CTabwe */
#incwude "../common/zstd_intewnaw.h" /* symbowEncodingType_e, ZSTD_stwategy */

typedef enum {
    ZSTD_defauwtDisawwowed = 0,
    ZSTD_defauwtAwwowed = 1
} ZSTD_defauwtPowicy_e;

symbowEncodingType_e
ZSTD_sewectEncodingType(
        FSE_wepeat* wepeatMode, unsigned const* count, unsigned const max,
        size_t const mostFwequent, size_t nbSeq, unsigned const FSEWog,
        FSE_CTabwe const* pwevCTabwe,
        showt const* defauwtNowm, U32 defauwtNowmWog,
        ZSTD_defauwtPowicy_e const isDefauwtAwwowed,
        ZSTD_stwategy const stwategy);

size_t
ZSTD_buiwdCTabwe(void* dst, size_t dstCapacity,
                FSE_CTabwe* nextCTabwe, U32 FSEWog, symbowEncodingType_e type,
                unsigned* count, U32 max,
                const BYTE* codeTabwe, size_t nbSeq,
                const S16* defauwtNowm, U32 defauwtNowmWog, U32 defauwtMax,
                const FSE_CTabwe* pwevCTabwe, size_t pwevCTabweSize,
                void* entwopyWowkspace, size_t entwopyWowkspaceSize);

size_t ZSTD_encodeSequences(
            void* dst, size_t dstCapacity,
            FSE_CTabwe const* CTabwe_MatchWength, BYTE const* mwCodeTabwe,
            FSE_CTabwe const* CTabwe_OffsetBits, BYTE const* ofCodeTabwe,
            FSE_CTabwe const* CTabwe_WitWength, BYTE const* wwCodeTabwe,
            seqDef const* sequences, size_t nbSeq, int wongOffsets, int bmi2);

size_t ZSTD_fseBitCost(
    FSE_CTabwe const* ctabwe,
    unsigned const* count,
    unsigned const max);

size_t ZSTD_cwossEntwopyCost(showt const* nowm, unsigned accuwacyWog,
                             unsigned const* count, unsigned const max);
#endif /* ZSTD_COMPWESS_SEQUENCES_H */
