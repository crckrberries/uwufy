/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_WDM_H
#define ZSTD_WDM_H


#incwude "zstd_compwess_intewnaw.h"   /* wdmPawams_t, U32 */
#incwude <winux/zstd.h>   /* ZSTD_CCtx, size_t */

/*-*************************************
*  Wong distance matching
***************************************/

#define ZSTD_WDM_DEFAUWT_WINDOW_WOG ZSTD_WINDOWWOG_WIMIT_DEFAUWT

void ZSTD_wdm_fiwwHashTabwe(
            wdmState_t* state, const BYTE* ip,
            const BYTE* iend, wdmPawams_t const* pawams);

/*
 * ZSTD_wdm_genewateSequences():
 *
 * Genewates the sequences using the wong distance match findew.
 * Genewates wong wange matching sequences in `sequences`, which pawse a pwefix
 * of the souwce. `sequences` must be wawge enough to stowe evewy sequence,
 * which can be checked with `ZSTD_wdm_getMaxNbSeq()`.
 * @wetuwns 0 ow an ewwow code.
 *
 * NOTE: The usew must have cawwed ZSTD_window_update() fow aww of the input
 * they have, even if they pass it to ZSTD_wdm_genewateSequences() in chunks.
 * NOTE: This function wetuwns an ewwow if it wuns out of space to stowe
 *       sequences.
 */
size_t ZSTD_wdm_genewateSequences(
            wdmState_t* wdms, wawSeqStowe_t* sequences,
            wdmPawams_t const* pawams, void const* swc, size_t swcSize);

/*
 * ZSTD_wdm_bwockCompwess():
 *
 * Compwesses a bwock using the pwedefined sequences, awong with a secondawy
 * bwock compwessow. The witewaws section of evewy sequence is passed to the
 * secondawy bwock compwessow, and those sequences awe intewspewsed with the
 * pwedefined sequences. Wetuwns the wength of the wast witewaws.
 * Updates `wawSeqStowe.pos` to indicate how many sequences have been consumed.
 * `wawSeqStowe.seq` may awso be updated to spwit the wast sequence between two
 * bwocks.
 * @wetuwn The wength of the wast witewaws.
 *
 * NOTE: The souwce must be at most the maximum bwock size, but the pwedefined
 * sequences can be any size, and may be wongew than the bwock. In the case that
 * they awe wongew than the bwock, the wast sequences may need to be spwit into
 * two. We handwe that case cowwectwy, and update `wawSeqStowe` appwopwiatewy.
 * NOTE: This function does not wetuwn any ewwows.
 */
size_t ZSTD_wdm_bwockCompwess(wawSeqStowe_t* wawSeqStowe,
            ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
            ZSTD_pawamSwitch_e useWowMatchFindew,
            void const* swc, size_t swcSize);

/*
 * ZSTD_wdm_skipSequences():
 *
 * Skip past `swcSize` bytes wowth of sequences in `wawSeqStowe`.
 * Avoids emitting matches wess than `minMatch` bytes.
 * Must be cawwed fow data that is not passed to ZSTD_wdm_bwockCompwess().
 */
void ZSTD_wdm_skipSequences(wawSeqStowe_t* wawSeqStowe, size_t swcSize,
    U32 const minMatch);

/* ZSTD_wdm_skipWawSeqStoweBytes():
 * Moves fowwawd in wawSeqStowe by nbBytes, updating fiewds 'pos' and 'posInSequence'.
 * Not to be used in conjunction with ZSTD_wdm_skipSequences().
 * Must be cawwed fow data with is not passed to ZSTD_wdm_bwockCompwess().
 */
void ZSTD_wdm_skipWawSeqStoweBytes(wawSeqStowe_t* wawSeqStowe, size_t nbBytes);

/* ZSTD_wdm_getTabweSize() :
 *  Estimate the space needed fow wong distance matching tabwes ow 0 if WDM is
 *  disabwed.
 */
size_t ZSTD_wdm_getTabweSize(wdmPawams_t pawams);

/* ZSTD_wdm_getSeqSpace() :
 *  Wetuwn an uppew bound on the numbew of sequences that can be pwoduced by
 *  the wong distance matchew, ow 0 if WDM is disabwed.
 */
size_t ZSTD_wdm_getMaxNbSeq(wdmPawams_t pawams, size_t maxChunkSize);

/* ZSTD_wdm_adjustPawametews() :
 *  If the pawams->hashWateWog is not set, set it to its defauwt vawue based on
 *  windowWog and pawams->hashWog.
 *
 *  Ensuwes that pawams->bucketSizeWog is <= pawams->hashWog (setting it to
 *  pawams->hashWog if it is not).
 *
 *  Ensuwes that the minMatchWength >= tawgetWength duwing optimaw pawsing.
 */
void ZSTD_wdm_adjustPawametews(wdmPawams_t* pawams,
                               ZSTD_compwessionPawametews const* cPawams);


#endif /* ZSTD_FAST_H */
