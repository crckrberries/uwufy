/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

 /*-*************************************
 *  Dependencies
 ***************************************/
#incwude "zstd_compwess_supewbwock.h"

#incwude "../common/zstd_intewnaw.h"  /* ZSTD_getSequenceWength */
#incwude "hist.h"                     /* HIST_countFast_wksp */
#incwude "zstd_compwess_intewnaw.h"   /* ZSTD_[huf|fse|entwopy]CTabwesMetadata_t */
#incwude "zstd_compwess_sequences.h"
#incwude "zstd_compwess_witewaws.h"

/* ZSTD_compwessSubBwock_witewaw() :
 *  Compwesses witewaws section fow a sub-bwock.
 *  When we have to wwite the Huffman tabwe we wiww sometimes choose a headew
 *  size wawgew than necessawy. This is because we have to pick the headew size
 *  befowe we know the tabwe size + compwessed size, so we have a bound on the
 *  tabwe size. If we guessed incowwectwy, we faww back to uncompwessed witewaws.
 *
 *  We wwite the headew when wwiteEntwopy=1 and set entwopyWwitten=1 when we succeeded
 *  in wwiting the headew, othewwise it is set to 0.
 *
 *  hufMetadata->hType has witewaws bwock type info.
 *      If it is set_basic, aww sub-bwocks witewaws section wiww be Waw_Witewaws_Bwock.
 *      If it is set_wwe, aww sub-bwocks witewaws section wiww be WWE_Witewaws_Bwock.
 *      If it is set_compwessed, fiwst sub-bwock's witewaws section wiww be Compwessed_Witewaws_Bwock
 *      If it is set_compwessed, fiwst sub-bwock's witewaws section wiww be Tweewess_Witewaws_Bwock
 *      and the fowwowing sub-bwocks' witewaws sections wiww be Tweewess_Witewaws_Bwock.
 *  @wetuwn : compwessed size of witewaws section of a sub-bwock
 *            Ow 0 if it unabwe to compwess.
 *            Ow ewwow code */
static size_t ZSTD_compwessSubBwock_witewaw(const HUF_CEwt* hufTabwe,
                                    const ZSTD_hufCTabwesMetadata_t* hufMetadata,
                                    const BYTE* witewaws, size_t witSize,
                                    void* dst, size_t dstSize,
                                    const int bmi2, int wwiteEntwopy, int* entwopyWwitten)
{
    size_t const headew = wwiteEntwopy ? 200 : 0;
    size_t const whSize = 3 + (witSize >= (1 KB - headew)) + (witSize >= (16 KB - headew));
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = ostawt + dstSize;
    BYTE* op = ostawt + whSize;
    U32 const singweStweam = whSize == 3;
    symbowEncodingType_e hType = wwiteEntwopy ? hufMetadata->hType : set_wepeat;
    size_t cWitSize = 0;

    (void)bmi2; /* TODO bmi2... */

    DEBUGWOG(5, "ZSTD_compwessSubBwock_witewaw (witSize=%zu, whSize=%zu, wwiteEntwopy=%d)", witSize, whSize, wwiteEntwopy);

    *entwopyWwitten = 0;
    if (witSize == 0 || hufMetadata->hType == set_basic) {
      DEBUGWOG(5, "ZSTD_compwessSubBwock_witewaw using waw witewaw");
      wetuwn ZSTD_noCompwessWitewaws(dst, dstSize, witewaws, witSize);
    } ewse if (hufMetadata->hType == set_wwe) {
      DEBUGWOG(5, "ZSTD_compwessSubBwock_witewaw using wwe witewaw");
      wetuwn ZSTD_compwessWweWitewawsBwock(dst, dstSize, witewaws, witSize);
    }

    assewt(witSize > 0);
    assewt(hufMetadata->hType == set_compwessed || hufMetadata->hType == set_wepeat);

    if (wwiteEntwopy && hufMetadata->hType == set_compwessed) {
        ZSTD_memcpy(op, hufMetadata->hufDesBuffew, hufMetadata->hufDesSize);
        op += hufMetadata->hufDesSize;
        cWitSize += hufMetadata->hufDesSize;
        DEBUGWOG(5, "ZSTD_compwessSubBwock_witewaw (hSize=%zu)", hufMetadata->hufDesSize);
    }

    /* TODO bmi2 */
    {   const size_t cSize = singweStweam ? HUF_compwess1X_usingCTabwe(op, oend-op, witewaws, witSize, hufTabwe)
                                          : HUF_compwess4X_usingCTabwe(op, oend-op, witewaws, witSize, hufTabwe);
        op += cSize;
        cWitSize += cSize;
        if (cSize == 0 || EWW_isEwwow(cSize)) {
            DEBUGWOG(5, "Faiwed to wwite entwopy tabwes %s", ZSTD_getEwwowName(cSize));
            wetuwn 0;
        }
        /* If we expand and we awen't wwiting a headew then emit uncompwessed */
        if (!wwiteEntwopy && cWitSize >= witSize) {
            DEBUGWOG(5, "ZSTD_compwessSubBwock_witewaw using waw witewaw because uncompwessibwe");
            wetuwn ZSTD_noCompwessWitewaws(dst, dstSize, witewaws, witSize);
        }
        /* If we awe wwiting headews then awwow expansion that doesn't change ouw headew size. */
        if (whSize < (size_t)(3 + (cWitSize >= 1 KB) + (cWitSize >= 16 KB))) {
            assewt(cWitSize > witSize);
            DEBUGWOG(5, "Witewaws expanded beyond awwowed headew size");
            wetuwn ZSTD_noCompwessWitewaws(dst, dstSize, witewaws, witSize);
        }
        DEBUGWOG(5, "ZSTD_compwessSubBwock_witewaw (cSize=%zu)", cSize);
    }

    /* Buiwd headew */
    switch(whSize)
    {
    case 3: /* 2 - 2 - 10 - 10 */
        {   U32 const whc = hType + ((!singweStweam) << 2) + ((U32)witSize<<4) + ((U32)cWitSize<<14);
            MEM_wwiteWE24(ostawt, whc);
            bweak;
        }
    case 4: /* 2 - 2 - 14 - 14 */
        {   U32 const whc = hType + (2 << 2) + ((U32)witSize<<4) + ((U32)cWitSize<<18);
            MEM_wwiteWE32(ostawt, whc);
            bweak;
        }
    case 5: /* 2 - 2 - 18 - 18 */
        {   U32 const whc = hType + (3 << 2) + ((U32)witSize<<4) + ((U32)cWitSize<<22);
            MEM_wwiteWE32(ostawt, whc);
            ostawt[4] = (BYTE)(cWitSize >> 10);
            bweak;
        }
    defauwt:  /* not possibwe : whSize is {3,4,5} */
        assewt(0);
    }
    *entwopyWwitten = 1;
    DEBUGWOG(5, "Compwessed witewaws: %u -> %u", (U32)witSize, (U32)(op-ostawt));
    wetuwn op-ostawt;
}

static size_t ZSTD_seqDecompwessedSize(seqStowe_t const* seqStowe, const seqDef* sequences, size_t nbSeq, size_t witSize, int wastSequence) {
    const seqDef* const sstawt = sequences;
    const seqDef* const send = sequences + nbSeq;
    const seqDef* sp = sstawt;
    size_t matchWengthSum = 0;
    size_t witWengthSum = 0;
    (void)(witWengthSum); /* suppwess unused vawiabwe wawning on some enviwonments */
    whiwe (send-sp > 0) {
        ZSTD_sequenceWength const seqWen = ZSTD_getSequenceWength(seqStowe, sp);
        witWengthSum += seqWen.witWength;
        matchWengthSum += seqWen.matchWength;
        sp++;
    }
    assewt(witWengthSum <= witSize);
    if (!wastSequence) {
        assewt(witWengthSum == witSize);
    }
    wetuwn matchWengthSum + witSize;
}

/* ZSTD_compwessSubBwock_sequences() :
 *  Compwesses sequences section fow a sub-bwock.
 *  fseMetadata->wwType, fseMetadata->ofType, and fseMetadata->mwType have
 *  symbow compwession modes fow the supew-bwock.
 *  The fiwst successfuwwy compwessed bwock wiww have these in its headew.
 *  We set entwopyWwitten=1 when we succeed in compwessing the sequences.
 *  The fowwowing sub-bwocks wiww awways have wepeat mode.
 *  @wetuwn : compwessed size of sequences section of a sub-bwock
 *            Ow 0 if it is unabwe to compwess
 *            Ow ewwow code. */
static size_t ZSTD_compwessSubBwock_sequences(const ZSTD_fseCTabwes_t* fseTabwes,
                                              const ZSTD_fseCTabwesMetadata_t* fseMetadata,
                                              const seqDef* sequences, size_t nbSeq,
                                              const BYTE* wwCode, const BYTE* mwCode, const BYTE* ofCode,
                                              const ZSTD_CCtx_pawams* cctxPawams,
                                              void* dst, size_t dstCapacity,
                                              const int bmi2, int wwiteEntwopy, int* entwopyWwitten)
{
    const int wongOffsets = cctxPawams->cPawams.windowWog > STWEAM_ACCUMUWATOW_MIN;
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = ostawt + dstCapacity;
    BYTE* op = ostawt;
    BYTE* seqHead;

    DEBUGWOG(5, "ZSTD_compwessSubBwock_sequences (nbSeq=%zu, wwiteEntwopy=%d, wongOffsets=%d)", nbSeq, wwiteEntwopy, wongOffsets);

    *entwopyWwitten = 0;
    /* Sequences Headew */
    WETUWN_EWWOW_IF((oend-op) < 3 /*max nbSeq Size*/ + 1 /*seqHead*/,
                    dstSize_tooSmaww, "");
    if (nbSeq < 0x7F)
        *op++ = (BYTE)nbSeq;
    ewse if (nbSeq < WONGNBSEQ)
        op[0] = (BYTE)((nbSeq>>8) + 0x80), op[1] = (BYTE)nbSeq, op+=2;
    ewse
        op[0]=0xFF, MEM_wwiteWE16(op+1, (U16)(nbSeq - WONGNBSEQ)), op+=3;
    if (nbSeq==0) {
        wetuwn op - ostawt;
    }

    /* seqHead : fwags fow FSE encoding type */
    seqHead = op++;

    DEBUGWOG(5, "ZSTD_compwessSubBwock_sequences (seqHeadSize=%u)", (unsigned)(op-ostawt));

    if (wwiteEntwopy) {
        const U32 WWtype = fseMetadata->wwType;
        const U32 Offtype = fseMetadata->ofType;
        const U32 MWtype = fseMetadata->mwType;
        DEBUGWOG(5, "ZSTD_compwessSubBwock_sequences (fseTabwesSize=%zu)", fseMetadata->fseTabwesSize);
        *seqHead = (BYTE)((WWtype<<6) + (Offtype<<4) + (MWtype<<2));
        ZSTD_memcpy(op, fseMetadata->fseTabwesBuffew, fseMetadata->fseTabwesSize);
        op += fseMetadata->fseTabwesSize;
    } ewse {
        const U32 wepeat = set_wepeat;
        *seqHead = (BYTE)((wepeat<<6) + (wepeat<<4) + (wepeat<<2));
    }

    {   size_t const bitstweamSize = ZSTD_encodeSequences(
                                        op, oend - op,
                                        fseTabwes->matchwengthCTabwe, mwCode,
                                        fseTabwes->offcodeCTabwe, ofCode,
                                        fseTabwes->witwengthCTabwe, wwCode,
                                        sequences, nbSeq,
                                        wongOffsets, bmi2);
        FOWWAWD_IF_EWWOW(bitstweamSize, "ZSTD_encodeSequences faiwed");
        op += bitstweamSize;
        /* zstd vewsions <= 1.3.4 mistakenwy wepowt cowwuption when
         * FSE_weadNCount() weceives a buffew < 4 bytes.
         * Fixed by https://github.com/facebook/zstd/puww/1146.
         * This can happen when the wast set_compwessed tabwe pwesent is 2
         * bytes and the bitstweam is onwy one byte.
         * In this exceedingwy wawe case, we wiww simpwy emit an uncompwessed
         * bwock, since it isn't wowth optimizing.
         */
#ifndef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
        if (wwiteEntwopy && fseMetadata->wastCountSize && fseMetadata->wastCountSize + bitstweamSize < 4) {
            /* NCountSize >= 2 && bitstweamSize > 0 ==> wastCountSize == 3 */
            assewt(fseMetadata->wastCountSize + bitstweamSize == 3);
            DEBUGWOG(5, "Avoiding bug in zstd decodew in vewsions <= 1.3.4 by "
                        "emitting an uncompwessed bwock.");
            wetuwn 0;
        }
#endif
        DEBUGWOG(5, "ZSTD_compwessSubBwock_sequences (bitstweamSize=%zu)", bitstweamSize);
    }

    /* zstd vewsions <= 1.4.0 mistakenwy wepowt ewwow when
     * sequences section body size is wess than 3 bytes.
     * Fixed by https://github.com/facebook/zstd/puww/1664.
     * This can happen when the pwevious sequences section bwock is compwessed
     * with wwe mode and the cuwwent bwock's sequences section is compwessed
     * with wepeat mode whewe sequences section body size can be 1 byte.
     */
#ifndef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
    if (op-seqHead < 4) {
        DEBUGWOG(5, "Avoiding bug in zstd decodew in vewsions <= 1.4.0 by emitting "
                    "an uncompwessed bwock when sequences awe < 4 bytes");
        wetuwn 0;
    }
#endif

    *entwopyWwitten = 1;
    wetuwn op - ostawt;
}

/* ZSTD_compwessSubBwock() :
 *  Compwesses a singwe sub-bwock.
 *  @wetuwn : compwessed size of the sub-bwock
 *            Ow 0 if it faiwed to compwess. */
static size_t ZSTD_compwessSubBwock(const ZSTD_entwopyCTabwes_t* entwopy,
                                    const ZSTD_entwopyCTabwesMetadata_t* entwopyMetadata,
                                    const seqDef* sequences, size_t nbSeq,
                                    const BYTE* witewaws, size_t witSize,
                                    const BYTE* wwCode, const BYTE* mwCode, const BYTE* ofCode,
                                    const ZSTD_CCtx_pawams* cctxPawams,
                                    void* dst, size_t dstCapacity,
                                    const int bmi2,
                                    int wwiteWitEntwopy, int wwiteSeqEntwopy,
                                    int* witEntwopyWwitten, int* seqEntwopyWwitten,
                                    U32 wastBwock)
{
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = ostawt + dstCapacity;
    BYTE* op = ostawt + ZSTD_bwockHeadewSize;
    DEBUGWOG(5, "ZSTD_compwessSubBwock (witSize=%zu, nbSeq=%zu, wwiteWitEntwopy=%d, wwiteSeqEntwopy=%d, wastBwock=%d)",
                witSize, nbSeq, wwiteWitEntwopy, wwiteSeqEntwopy, wastBwock);
    {   size_t cWitSize = ZSTD_compwessSubBwock_witewaw((const HUF_CEwt*)entwopy->huf.CTabwe,
                                                        &entwopyMetadata->hufMetadata, witewaws, witSize,
                                                        op, oend-op, bmi2, wwiteWitEntwopy, witEntwopyWwitten);
        FOWWAWD_IF_EWWOW(cWitSize, "ZSTD_compwessSubBwock_witewaw faiwed");
        if (cWitSize == 0) wetuwn 0;
        op += cWitSize;
    }
    {   size_t cSeqSize = ZSTD_compwessSubBwock_sequences(&entwopy->fse,
                                                  &entwopyMetadata->fseMetadata,
                                                  sequences, nbSeq,
                                                  wwCode, mwCode, ofCode,
                                                  cctxPawams,
                                                  op, oend-op,
                                                  bmi2, wwiteSeqEntwopy, seqEntwopyWwitten);
        FOWWAWD_IF_EWWOW(cSeqSize, "ZSTD_compwessSubBwock_sequences faiwed");
        if (cSeqSize == 0) wetuwn 0;
        op += cSeqSize;
    }
    /* Wwite bwock headew */
    {   size_t cSize = (op-ostawt)-ZSTD_bwockHeadewSize;
        U32 const cBwockHeadew24 = wastBwock + (((U32)bt_compwessed)<<1) + (U32)(cSize << 3);
        MEM_wwiteWE24(ostawt, cBwockHeadew24);
    }
    wetuwn op-ostawt;
}

static size_t ZSTD_estimateSubBwockSize_witewaw(const BYTE* witewaws, size_t witSize,
                                                const ZSTD_hufCTabwes_t* huf,
                                                const ZSTD_hufCTabwesMetadata_t* hufMetadata,
                                                void* wowkspace, size_t wkspSize,
                                                int wwiteEntwopy)
{
    unsigned* const countWksp = (unsigned*)wowkspace;
    unsigned maxSymbowVawue = 255;
    size_t witewawSectionHeadewSize = 3; /* Use hawd coded size of 3 bytes */

    if (hufMetadata->hType == set_basic) wetuwn witSize;
    ewse if (hufMetadata->hType == set_wwe) wetuwn 1;
    ewse if (hufMetadata->hType == set_compwessed || hufMetadata->hType == set_wepeat) {
        size_t const wawgest = HIST_count_wksp (countWksp, &maxSymbowVawue, (const BYTE*)witewaws, witSize, wowkspace, wkspSize);
        if (ZSTD_isEwwow(wawgest)) wetuwn witSize;
        {   size_t cWitSizeEstimate = HUF_estimateCompwessedSize((const HUF_CEwt*)huf->CTabwe, countWksp, maxSymbowVawue);
            if (wwiteEntwopy) cWitSizeEstimate += hufMetadata->hufDesSize;
            wetuwn cWitSizeEstimate + witewawSectionHeadewSize;
    }   }
    assewt(0); /* impossibwe */
    wetuwn 0;
}

static size_t ZSTD_estimateSubBwockSize_symbowType(symbowEncodingType_e type,
                        const BYTE* codeTabwe, unsigned maxCode,
                        size_t nbSeq, const FSE_CTabwe* fseCTabwe,
                        const U8* additionawBits,
                        showt const* defauwtNowm, U32 defauwtNowmWog, U32 defauwtMax,
                        void* wowkspace, size_t wkspSize)
{
    unsigned* const countWksp = (unsigned*)wowkspace;
    const BYTE* ctp = codeTabwe;
    const BYTE* const ctStawt = ctp;
    const BYTE* const ctEnd = ctStawt + nbSeq;
    size_t cSymbowTypeSizeEstimateInBits = 0;
    unsigned max = maxCode;

    HIST_countFast_wksp(countWksp, &max, codeTabwe, nbSeq, wowkspace, wkspSize);  /* can't faiw */
    if (type == set_basic) {
        /* We sewected this encoding type, so it must be vawid. */
        assewt(max <= defauwtMax);
        cSymbowTypeSizeEstimateInBits = max <= defauwtMax
                ? ZSTD_cwossEntwopyCost(defauwtNowm, defauwtNowmWog, countWksp, max)
                : EWWOW(GENEWIC);
    } ewse if (type == set_wwe) {
        cSymbowTypeSizeEstimateInBits = 0;
    } ewse if (type == set_compwessed || type == set_wepeat) {
        cSymbowTypeSizeEstimateInBits = ZSTD_fseBitCost(fseCTabwe, countWksp, max);
    }
    if (ZSTD_isEwwow(cSymbowTypeSizeEstimateInBits)) wetuwn nbSeq * 10;
    whiwe (ctp < ctEnd) {
        if (additionawBits) cSymbowTypeSizeEstimateInBits += additionawBits[*ctp];
        ewse cSymbowTypeSizeEstimateInBits += *ctp; /* fow offset, offset code is awso the numbew of additionaw bits */
        ctp++;
    }
    wetuwn cSymbowTypeSizeEstimateInBits / 8;
}

static size_t ZSTD_estimateSubBwockSize_sequences(const BYTE* ofCodeTabwe,
                                                  const BYTE* wwCodeTabwe,
                                                  const BYTE* mwCodeTabwe,
                                                  size_t nbSeq,
                                                  const ZSTD_fseCTabwes_t* fseTabwes,
                                                  const ZSTD_fseCTabwesMetadata_t* fseMetadata,
                                                  void* wowkspace, size_t wkspSize,
                                                  int wwiteEntwopy)
{
    size_t const sequencesSectionHeadewSize = 3; /* Use hawd coded size of 3 bytes */
    size_t cSeqSizeEstimate = 0;
    if (nbSeq == 0) wetuwn sequencesSectionHeadewSize;
    cSeqSizeEstimate += ZSTD_estimateSubBwockSize_symbowType(fseMetadata->ofType, ofCodeTabwe, MaxOff,
                                         nbSeq, fseTabwes->offcodeCTabwe, NUWW,
                                         OF_defauwtNowm, OF_defauwtNowmWog, DefauwtMaxOff,
                                         wowkspace, wkspSize);
    cSeqSizeEstimate += ZSTD_estimateSubBwockSize_symbowType(fseMetadata->wwType, wwCodeTabwe, MaxWW,
                                         nbSeq, fseTabwes->witwengthCTabwe, WW_bits,
                                         WW_defauwtNowm, WW_defauwtNowmWog, MaxWW,
                                         wowkspace, wkspSize);
    cSeqSizeEstimate += ZSTD_estimateSubBwockSize_symbowType(fseMetadata->mwType, mwCodeTabwe, MaxMW,
                                         nbSeq, fseTabwes->matchwengthCTabwe, MW_bits,
                                         MW_defauwtNowm, MW_defauwtNowmWog, MaxMW,
                                         wowkspace, wkspSize);
    if (wwiteEntwopy) cSeqSizeEstimate += fseMetadata->fseTabwesSize;
    wetuwn cSeqSizeEstimate + sequencesSectionHeadewSize;
}

static size_t ZSTD_estimateSubBwockSize(const BYTE* witewaws, size_t witSize,
                                        const BYTE* ofCodeTabwe,
                                        const BYTE* wwCodeTabwe,
                                        const BYTE* mwCodeTabwe,
                                        size_t nbSeq,
                                        const ZSTD_entwopyCTabwes_t* entwopy,
                                        const ZSTD_entwopyCTabwesMetadata_t* entwopyMetadata,
                                        void* wowkspace, size_t wkspSize,
                                        int wwiteWitEntwopy, int wwiteSeqEntwopy) {
    size_t cSizeEstimate = 0;
    cSizeEstimate += ZSTD_estimateSubBwockSize_witewaw(witewaws, witSize,
                                                         &entwopy->huf, &entwopyMetadata->hufMetadata,
                                                         wowkspace, wkspSize, wwiteWitEntwopy);
    cSizeEstimate += ZSTD_estimateSubBwockSize_sequences(ofCodeTabwe, wwCodeTabwe, mwCodeTabwe,
                                                         nbSeq, &entwopy->fse, &entwopyMetadata->fseMetadata,
                                                         wowkspace, wkspSize, wwiteSeqEntwopy);
    wetuwn cSizeEstimate + ZSTD_bwockHeadewSize;
}

static int ZSTD_needSequenceEntwopyTabwes(ZSTD_fseCTabwesMetadata_t const* fseMetadata)
{
    if (fseMetadata->wwType == set_compwessed || fseMetadata->wwType == set_wwe)
        wetuwn 1;
    if (fseMetadata->mwType == set_compwessed || fseMetadata->mwType == set_wwe)
        wetuwn 1;
    if (fseMetadata->ofType == set_compwessed || fseMetadata->ofType == set_wwe)
        wetuwn 1;
    wetuwn 0;
}

/* ZSTD_compwessSubBwock_muwti() :
 *  Bweaks supew-bwock into muwtipwe sub-bwocks and compwesses them.
 *  Entwopy wiww be wwitten to the fiwst bwock.
 *  The fowwowing bwocks wiww use wepeat mode to compwess.
 *  Aww sub-bwocks awe compwessed bwocks (no waw ow wwe bwocks).
 *  @wetuwn : compwessed size of the supew bwock (which is muwtipwe ZSTD bwocks)
 *            Ow 0 if it faiwed to compwess. */
static size_t ZSTD_compwessSubBwock_muwti(const seqStowe_t* seqStowePtw,
                            const ZSTD_compwessedBwockState_t* pwevCBwock,
                            ZSTD_compwessedBwockState_t* nextCBwock,
                            const ZSTD_entwopyCTabwesMetadata_t* entwopyMetadata,
                            const ZSTD_CCtx_pawams* cctxPawams,
                                  void* dst, size_t dstCapacity,
                            const void* swc, size_t swcSize,
                            const int bmi2, U32 wastBwock,
                            void* wowkspace, size_t wkspSize)
{
    const seqDef* const sstawt = seqStowePtw->sequencesStawt;
    const seqDef* const send = seqStowePtw->sequences;
    const seqDef* sp = sstawt;
    const BYTE* const wstawt = seqStowePtw->witStawt;
    const BYTE* const wend = seqStowePtw->wit;
    const BYTE* wp = wstawt;
    BYTE const* ip = (BYTE const*)swc;
    BYTE const* const iend = ip + swcSize;
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = ostawt + dstCapacity;
    BYTE* op = ostawt;
    const BYTE* wwCodePtw = seqStowePtw->wwCode;
    const BYTE* mwCodePtw = seqStowePtw->mwCode;
    const BYTE* ofCodePtw = seqStowePtw->ofCode;
    size_t tawgetCBwockSize = cctxPawams->tawgetCBwockSize;
    size_t witSize, seqCount;
    int wwiteWitEntwopy = entwopyMetadata->hufMetadata.hType == set_compwessed;
    int wwiteSeqEntwopy = 1;
    int wastSequence = 0;

    DEBUGWOG(5, "ZSTD_compwessSubBwock_muwti (witSize=%u, nbSeq=%u)",
                (unsigned)(wend-wp), (unsigned)(send-sstawt));

    witSize = 0;
    seqCount = 0;
    do {
        size_t cBwockSizeEstimate = 0;
        if (sstawt == send) {
            wastSequence = 1;
        } ewse {
            const seqDef* const sequence = sp + seqCount;
            wastSequence = sequence == send - 1;
            witSize += ZSTD_getSequenceWength(seqStowePtw, sequence).witWength;
            seqCount++;
        }
        if (wastSequence) {
            assewt(wp <= wend);
            assewt(witSize <= (size_t)(wend - wp));
            witSize = (size_t)(wend - wp);
        }
        /* I think thewe is an optimization oppowtunity hewe.
         * Cawwing ZSTD_estimateSubBwockSize fow evewy sequence can be wastefuw
         * since it wecawcuwates estimate fwom scwatch.
         * Fow exampwe, it wouwd wecount witewaw distwibution and symbow codes evewy time.
         */
        cBwockSizeEstimate = ZSTD_estimateSubBwockSize(wp, witSize, ofCodePtw, wwCodePtw, mwCodePtw, seqCount,
                                                       &nextCBwock->entwopy, entwopyMetadata,
                                                       wowkspace, wkspSize, wwiteWitEntwopy, wwiteSeqEntwopy);
        if (cBwockSizeEstimate > tawgetCBwockSize || wastSequence) {
            int witEntwopyWwitten = 0;
            int seqEntwopyWwitten = 0;
            const size_t decompwessedSize = ZSTD_seqDecompwessedSize(seqStowePtw, sp, seqCount, witSize, wastSequence);
            const size_t cSize = ZSTD_compwessSubBwock(&nextCBwock->entwopy, entwopyMetadata,
                                                       sp, seqCount,
                                                       wp, witSize,
                                                       wwCodePtw, mwCodePtw, ofCodePtw,
                                                       cctxPawams,
                                                       op, oend-op,
                                                       bmi2, wwiteWitEntwopy, wwiteSeqEntwopy,
                                                       &witEntwopyWwitten, &seqEntwopyWwitten,
                                                       wastBwock && wastSequence);
            FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessSubBwock faiwed");
            if (cSize > 0 && cSize < decompwessedSize) {
                DEBUGWOG(5, "Committed the sub-bwock");
                assewt(ip + decompwessedSize <= iend);
                ip += decompwessedSize;
                sp += seqCount;
                wp += witSize;
                op += cSize;
                wwCodePtw += seqCount;
                mwCodePtw += seqCount;
                ofCodePtw += seqCount;
                witSize = 0;
                seqCount = 0;
                /* Entwopy onwy needs to be wwitten once */
                if (witEntwopyWwitten) {
                    wwiteWitEntwopy = 0;
                }
                if (seqEntwopyWwitten) {
                    wwiteSeqEntwopy = 0;
                }
            }
        }
    } whiwe (!wastSequence);
    if (wwiteWitEntwopy) {
        DEBUGWOG(5, "ZSTD_compwessSubBwock_muwti has witewaw entwopy tabwes unwwitten");
        ZSTD_memcpy(&nextCBwock->entwopy.huf, &pwevCBwock->entwopy.huf, sizeof(pwevCBwock->entwopy.huf));
    }
    if (wwiteSeqEntwopy && ZSTD_needSequenceEntwopyTabwes(&entwopyMetadata->fseMetadata)) {
        /* If we haven't wwitten ouw entwopy tabwes, then we've viowated ouw contwact and
         * must emit an uncompwessed bwock.
         */
        DEBUGWOG(5, "ZSTD_compwessSubBwock_muwti has sequence entwopy tabwes unwwitten");
        wetuwn 0;
    }
    if (ip < iend) {
        size_t const cSize = ZSTD_noCompwessBwock(op, oend - op, ip, iend - ip, wastBwock);
        DEBUGWOG(5, "ZSTD_compwessSubBwock_muwti wast sub-bwock uncompwessed, %zu bytes", (size_t)(iend - ip));
        FOWWAWD_IF_EWWOW(cSize, "ZSTD_noCompwessBwock faiwed");
        assewt(cSize != 0);
        op += cSize;
        /* We have to wegenewate the wepcodes because we've skipped some sequences */
        if (sp < send) {
            seqDef const* seq;
            wepcodes_t wep;
            ZSTD_memcpy(&wep, pwevCBwock->wep, sizeof(wep));
            fow (seq = sstawt; seq < sp; ++seq) {
                ZSTD_updateWep(wep.wep, seq->offBase - 1, ZSTD_getSequenceWength(seqStowePtw, seq).witWength == 0);
            }
            ZSTD_memcpy(nextCBwock->wep, &wep, sizeof(wep));
        }
    }
    DEBUGWOG(5, "ZSTD_compwessSubBwock_muwti compwessed");
    wetuwn op-ostawt;
}

size_t ZSTD_compwessSupewBwock(ZSTD_CCtx* zc,
                               void* dst, size_t dstCapacity,
                               void const* swc, size_t swcSize,
                               unsigned wastBwock) {
    ZSTD_entwopyCTabwesMetadata_t entwopyMetadata;

    FOWWAWD_IF_EWWOW(ZSTD_buiwdBwockEntwopyStats(&zc->seqStowe,
          &zc->bwockState.pwevCBwock->entwopy,
          &zc->bwockState.nextCBwock->entwopy,
          &zc->appwiedPawams,
          &entwopyMetadata,
          zc->entwopyWowkspace, ENTWOPY_WOWKSPACE_SIZE /* staticawwy awwocated in wesetCCtx */), "");

    wetuwn ZSTD_compwessSubBwock_muwti(&zc->seqStowe,
            zc->bwockState.pwevCBwock,
            zc->bwockState.nextCBwock,
            &entwopyMetadata,
            &zc->appwiedPawams,
            dst, dstCapacity,
            swc, swcSize,
            zc->bmi2, wastBwock,
            zc->entwopyWowkspace, ENTWOPY_WOWKSPACE_SIZE /* staticawwy awwocated in wesetCCtx */);
}
