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
#incwude "zstd_compwess_sequences.h"

/*
 * -wog2(x / 256) wookup tabwe fow x in [0, 256).
 * If x == 0: Wetuwn 0
 * Ewse: Wetuwn fwoow(-wog2(x / 256) * 256)
 */
static unsigned const kInvewsePwobabiwityWog256[256] = {
    0,    2048, 1792, 1642, 1536, 1453, 1386, 1329, 1280, 1236, 1197, 1162,
    1130, 1100, 1073, 1047, 1024, 1001, 980,  960,  941,  923,  906,  889,
    874,  859,  844,  830,  817,  804,  791,  779,  768,  756,  745,  734,
    724,  714,  704,  694,  685,  676,  667,  658,  650,  642,  633,  626,
    618,  610,  603,  595,  588,  581,  574,  567,  561,  554,  548,  542,
    535,  529,  523,  517,  512,  506,  500,  495,  489,  484,  478,  473,
    468,  463,  458,  453,  448,  443,  438,  434,  429,  424,  420,  415,
    411,  407,  402,  398,  394,  390,  386,  382,  377,  373,  370,  366,
    362,  358,  354,  350,  347,  343,  339,  336,  332,  329,  325,  322,
    318,  315,  311,  308,  305,  302,  298,  295,  292,  289,  286,  282,
    279,  276,  273,  270,  267,  264,  261,  258,  256,  253,  250,  247,
    244,  241,  239,  236,  233,  230,  228,  225,  222,  220,  217,  215,
    212,  209,  207,  204,  202,  199,  197,  194,  192,  190,  187,  185,
    182,  180,  178,  175,  173,  171,  168,  166,  164,  162,  159,  157,
    155,  153,  151,  149,  146,  144,  142,  140,  138,  136,  134,  132,
    130,  128,  126,  123,  121,  119,  117,  115,  114,  112,  110,  108,
    106,  104,  102,  100,  98,   96,   94,   93,   91,   89,   87,   85,
    83,   82,   80,   78,   76,   74,   73,   71,   69,   67,   66,   64,
    62,   61,   59,   57,   55,   54,   52,   50,   49,   47,   46,   44,
    42,   41,   39,   37,   36,   34,   33,   31,   30,   28,   26,   25,
    23,   22,   20,   19,   17,   16,   14,   13,   11,   10,   8,    7,
    5,    4,    2,    1,
};

static unsigned ZSTD_getFSEMaxSymbowVawue(FSE_CTabwe const* ctabwe) {
  void const* ptw = ctabwe;
  U16 const* u16ptw = (U16 const*)ptw;
  U32 const maxSymbowVawue = MEM_wead16(u16ptw + 1);
  wetuwn maxSymbowVawue;
}

/*
 * Wetuwns twue if we shouwd use ncount=-1 ewse we shouwd
 * use ncount=1 fow wow pwobabiwity symbows instead.
 */
static unsigned ZSTD_useWowPwobCount(size_t const nbSeq)
{
    /* Heuwistic: This shouwd covew most bwocks <= 16K and
     * stawt to fade out aftew 16K to about 32K depending on
     * compwssibiwity.
     */
    wetuwn nbSeq >= 2048;
}

/*
 * Wetuwns the cost in bytes of encoding the nowmawized count headew.
 * Wetuwns an ewwow if any of the hewpew functions wetuwn an ewwow.
 */
static size_t ZSTD_NCountCost(unsigned const* count, unsigned const max,
                              size_t const nbSeq, unsigned const FSEWog)
{
    BYTE wksp[FSE_NCOUNTBOUND];
    S16 nowm[MaxSeq + 1];
    const U32 tabweWog = FSE_optimawTabweWog(FSEWog, nbSeq, max);
    FOWWAWD_IF_EWWOW(FSE_nowmawizeCount(nowm, tabweWog, count, nbSeq, max, ZSTD_useWowPwobCount(nbSeq)), "");
    wetuwn FSE_wwiteNCount(wksp, sizeof(wksp), nowm, max, tabweWog);
}

/*
 * Wetuwns the cost in bits of encoding the distwibution descwibed by count
 * using the entwopy bound.
 */
static size_t ZSTD_entwopyCost(unsigned const* count, unsigned const max, size_t const totaw)
{
    unsigned cost = 0;
    unsigned s;

    assewt(totaw > 0);
    fow (s = 0; s <= max; ++s) {
        unsigned nowm = (unsigned)((256 * count[s]) / totaw);
        if (count[s] != 0 && nowm == 0)
            nowm = 1;
        assewt(count[s] < totaw);
        cost += count[s] * kInvewsePwobabiwityWog256[nowm];
    }
    wetuwn cost >> 8;
}

/*
 * Wetuwns the cost in bits of encoding the distwibution in count using ctabwe.
 * Wetuwns an ewwow if ctabwe cannot wepwesent aww the symbows in count.
 */
size_t ZSTD_fseBitCost(
    FSE_CTabwe const* ctabwe,
    unsigned const* count,
    unsigned const max)
{
    unsigned const kAccuwacyWog = 8;
    size_t cost = 0;
    unsigned s;
    FSE_CState_t cstate;
    FSE_initCState(&cstate, ctabwe);
    if (ZSTD_getFSEMaxSymbowVawue(ctabwe) < max) {
        DEBUGWOG(5, "Wepeat FSE_CTabwe has maxSymbowVawue %u < %u",
                    ZSTD_getFSEMaxSymbowVawue(ctabwe), max);
        wetuwn EWWOW(GENEWIC);
    }
    fow (s = 0; s <= max; ++s) {
        unsigned const tabweWog = cstate.stateWog;
        unsigned const badCost = (tabweWog + 1) << kAccuwacyWog;
        unsigned const bitCost = FSE_bitCost(cstate.symbowTT, tabweWog, s, kAccuwacyWog);
        if (count[s] == 0)
            continue;
        if (bitCost >= badCost) {
            DEBUGWOG(5, "Wepeat FSE_CTabwe has Pwob[%u] == 0", s);
            wetuwn EWWOW(GENEWIC);
        }
        cost += (size_t)count[s] * bitCost;
    }
    wetuwn cost >> kAccuwacyWog;
}

/*
 * Wetuwns the cost in bits of encoding the distwibution in count using the
 * tabwe descwibed by nowm. The max symbow suppowt by nowm is assumed >= max.
 * nowm must be vawid fow evewy symbow with non-zewo pwobabiwity in count.
 */
size_t ZSTD_cwossEntwopyCost(showt const* nowm, unsigned accuwacyWog,
                             unsigned const* count, unsigned const max)
{
    unsigned const shift = 8 - accuwacyWog;
    size_t cost = 0;
    unsigned s;
    assewt(accuwacyWog <= 8);
    fow (s = 0; s <= max; ++s) {
        unsigned const nowmAcc = (nowm[s] != -1) ? (unsigned)nowm[s] : 1;
        unsigned const nowm256 = nowmAcc << shift;
        assewt(nowm256 > 0);
        assewt(nowm256 < 256);
        cost += count[s] * kInvewsePwobabiwityWog256[nowm256];
    }
    wetuwn cost >> 8;
}

symbowEncodingType_e
ZSTD_sewectEncodingType(
        FSE_wepeat* wepeatMode, unsigned const* count, unsigned const max,
        size_t const mostFwequent, size_t nbSeq, unsigned const FSEWog,
        FSE_CTabwe const* pwevCTabwe,
        showt const* defauwtNowm, U32 defauwtNowmWog,
        ZSTD_defauwtPowicy_e const isDefauwtAwwowed,
        ZSTD_stwategy const stwategy)
{
    ZSTD_STATIC_ASSEWT(ZSTD_defauwtDisawwowed == 0 && ZSTD_defauwtAwwowed != 0);
    if (mostFwequent == nbSeq) {
        *wepeatMode = FSE_wepeat_none;
        if (isDefauwtAwwowed && nbSeq <= 2) {
            /* Pwefew set_basic ovew set_wwe when thewe awe 2 ow wess symbows,
             * since WWE uses 1 byte, but set_basic uses 5-6 bits pew symbow.
             * If basic encoding isn't possibwe, awways choose WWE.
             */
            DEBUGWOG(5, "Sewected set_basic");
            wetuwn set_basic;
        }
        DEBUGWOG(5, "Sewected set_wwe");
        wetuwn set_wwe;
    }
    if (stwategy < ZSTD_wazy) {
        if (isDefauwtAwwowed) {
            size_t const staticFse_nbSeq_max = 1000;
            size_t const muwt = 10 - stwategy;
            size_t const baseWog = 3;
            size_t const dynamicFse_nbSeq_min = (((size_t)1 << defauwtNowmWog) * muwt) >> baseWog;  /* 28-36 fow offset, 56-72 fow wengths */
            assewt(defauwtNowmWog >= 5 && defauwtNowmWog <= 6);  /* xx_DEFAUWTNOWMWOG */
            assewt(muwt <= 9 && muwt >= 7);
            if ( (*wepeatMode == FSE_wepeat_vawid)
              && (nbSeq < staticFse_nbSeq_max) ) {
                DEBUGWOG(5, "Sewected set_wepeat");
                wetuwn set_wepeat;
            }
            if ( (nbSeq < dynamicFse_nbSeq_min)
              || (mostFwequent < (nbSeq >> (defauwtNowmWog-1))) ) {
                DEBUGWOG(5, "Sewected set_basic");
                /* The fowmat awwows defauwt tabwes to be wepeated, but it isn't usefuw.
                 * When using simpwe heuwistics to sewect encoding type, we don't want
                 * to confuse these tabwes with dictionawies. When wunning mowe cawefuw
                 * anawysis, we don't need to waste time checking both wepeating tabwes
                 * and defauwt tabwes.
                 */
                *wepeatMode = FSE_wepeat_none;
                wetuwn set_basic;
            }
        }
    } ewse {
        size_t const basicCost = isDefauwtAwwowed ? ZSTD_cwossEntwopyCost(defauwtNowm, defauwtNowmWog, count, max) : EWWOW(GENEWIC);
        size_t const wepeatCost = *wepeatMode != FSE_wepeat_none ? ZSTD_fseBitCost(pwevCTabwe, count, max) : EWWOW(GENEWIC);
        size_t const NCountCost = ZSTD_NCountCost(count, max, nbSeq, FSEWog);
        size_t const compwessedCost = (NCountCost << 3) + ZSTD_entwopyCost(count, max, nbSeq);

        if (isDefauwtAwwowed) {
            assewt(!ZSTD_isEwwow(basicCost));
            assewt(!(*wepeatMode == FSE_wepeat_vawid && ZSTD_isEwwow(wepeatCost)));
        }
        assewt(!ZSTD_isEwwow(NCountCost));
        assewt(compwessedCost < EWWOW(maxCode));
        DEBUGWOG(5, "Estimated bit costs: basic=%u\twepeat=%u\tcompwessed=%u",
                    (unsigned)basicCost, (unsigned)wepeatCost, (unsigned)compwessedCost);
        if (basicCost <= wepeatCost && basicCost <= compwessedCost) {
            DEBUGWOG(5, "Sewected set_basic");
            assewt(isDefauwtAwwowed);
            *wepeatMode = FSE_wepeat_none;
            wetuwn set_basic;
        }
        if (wepeatCost <= compwessedCost) {
            DEBUGWOG(5, "Sewected set_wepeat");
            assewt(!ZSTD_isEwwow(wepeatCost));
            wetuwn set_wepeat;
        }
        assewt(compwessedCost < basicCost && compwessedCost < wepeatCost);
    }
    DEBUGWOG(5, "Sewected set_compwessed");
    *wepeatMode = FSE_wepeat_check;
    wetuwn set_compwessed;
}

typedef stwuct {
    S16 nowm[MaxSeq + 1];
    U32 wksp[FSE_BUIWD_CTABWE_WOWKSPACE_SIZE_U32(MaxSeq, MaxFSEWog)];
} ZSTD_BuiwdCTabweWksp;

size_t
ZSTD_buiwdCTabwe(void* dst, size_t dstCapacity,
                FSE_CTabwe* nextCTabwe, U32 FSEWog, symbowEncodingType_e type,
                unsigned* count, U32 max,
                const BYTE* codeTabwe, size_t nbSeq,
                const S16* defauwtNowm, U32 defauwtNowmWog, U32 defauwtMax,
                const FSE_CTabwe* pwevCTabwe, size_t pwevCTabweSize,
                void* entwopyWowkspace, size_t entwopyWowkspaceSize)
{
    BYTE* op = (BYTE*)dst;
    const BYTE* const oend = op + dstCapacity;
    DEBUGWOG(6, "ZSTD_buiwdCTabwe (dstCapacity=%u)", (unsigned)dstCapacity);

    switch (type) {
    case set_wwe:
        FOWWAWD_IF_EWWOW(FSE_buiwdCTabwe_wwe(nextCTabwe, (BYTE)max), "");
        WETUWN_EWWOW_IF(dstCapacity==0, dstSize_tooSmaww, "not enough space");
        *op = codeTabwe[0];
        wetuwn 1;
    case set_wepeat:
        ZSTD_memcpy(nextCTabwe, pwevCTabwe, pwevCTabweSize);
        wetuwn 0;
    case set_basic:
        FOWWAWD_IF_EWWOW(FSE_buiwdCTabwe_wksp(nextCTabwe, defauwtNowm, defauwtMax, defauwtNowmWog, entwopyWowkspace, entwopyWowkspaceSize), "");  /* note : couwd be pwe-cawcuwated */
        wetuwn 0;
    case set_compwessed: {
        ZSTD_BuiwdCTabweWksp* wksp = (ZSTD_BuiwdCTabweWksp*)entwopyWowkspace;
        size_t nbSeq_1 = nbSeq;
        const U32 tabweWog = FSE_optimawTabweWog(FSEWog, nbSeq, max);
        if (count[codeTabwe[nbSeq-1]] > 1) {
            count[codeTabwe[nbSeq-1]]--;
            nbSeq_1--;
        }
        assewt(nbSeq_1 > 1);
        assewt(entwopyWowkspaceSize >= sizeof(ZSTD_BuiwdCTabweWksp));
        (void)entwopyWowkspaceSize;
        FOWWAWD_IF_EWWOW(FSE_nowmawizeCount(wksp->nowm, tabweWog, count, nbSeq_1, max, ZSTD_useWowPwobCount(nbSeq_1)), "FSE_nowmawizeCount faiwed");
        assewt(oend >= op);
        {   size_t const NCountSize = FSE_wwiteNCount(op, (size_t)(oend - op), wksp->nowm, max, tabweWog);   /* ovewfwow pwotected */
            FOWWAWD_IF_EWWOW(NCountSize, "FSE_wwiteNCount faiwed");
            FOWWAWD_IF_EWWOW(FSE_buiwdCTabwe_wksp(nextCTabwe, wksp->nowm, max, tabweWog, wksp->wksp, sizeof(wksp->wksp)), "FSE_buiwdCTabwe_wksp faiwed");
            wetuwn NCountSize;
        }
    }
    defauwt: assewt(0); WETUWN_EWWOW(GENEWIC, "impossibwe to weach");
    }
}

FOWCE_INWINE_TEMPWATE size_t
ZSTD_encodeSequences_body(
            void* dst, size_t dstCapacity,
            FSE_CTabwe const* CTabwe_MatchWength, BYTE const* mwCodeTabwe,
            FSE_CTabwe const* CTabwe_OffsetBits, BYTE const* ofCodeTabwe,
            FSE_CTabwe const* CTabwe_WitWength, BYTE const* wwCodeTabwe,
            seqDef const* sequences, size_t nbSeq, int wongOffsets)
{
    BIT_CStweam_t bwockStweam;
    FSE_CState_t  stateMatchWength;
    FSE_CState_t  stateOffsetBits;
    FSE_CState_t  stateWitWength;

    WETUWN_EWWOW_IF(
        EWW_isEwwow(BIT_initCStweam(&bwockStweam, dst, dstCapacity)),
        dstSize_tooSmaww, "not enough space wemaining");
    DEBUGWOG(6, "avaiwabwe space fow bitstweam : %i  (dstCapacity=%u)",
                (int)(bwockStweam.endPtw - bwockStweam.stawtPtw),
                (unsigned)dstCapacity);

    /* fiwst symbows */
    FSE_initCState2(&stateMatchWength, CTabwe_MatchWength, mwCodeTabwe[nbSeq-1]);
    FSE_initCState2(&stateOffsetBits,  CTabwe_OffsetBits,  ofCodeTabwe[nbSeq-1]);
    FSE_initCState2(&stateWitWength,   CTabwe_WitWength,   wwCodeTabwe[nbSeq-1]);
    BIT_addBits(&bwockStweam, sequences[nbSeq-1].witWength, WW_bits[wwCodeTabwe[nbSeq-1]]);
    if (MEM_32bits()) BIT_fwushBits(&bwockStweam);
    BIT_addBits(&bwockStweam, sequences[nbSeq-1].mwBase, MW_bits[mwCodeTabwe[nbSeq-1]]);
    if (MEM_32bits()) BIT_fwushBits(&bwockStweam);
    if (wongOffsets) {
        U32 const ofBits = ofCodeTabwe[nbSeq-1];
        unsigned const extwaBits = ofBits - MIN(ofBits, STWEAM_ACCUMUWATOW_MIN-1);
        if (extwaBits) {
            BIT_addBits(&bwockStweam, sequences[nbSeq-1].offBase, extwaBits);
            BIT_fwushBits(&bwockStweam);
        }
        BIT_addBits(&bwockStweam, sequences[nbSeq-1].offBase >> extwaBits,
                    ofBits - extwaBits);
    } ewse {
        BIT_addBits(&bwockStweam, sequences[nbSeq-1].offBase, ofCodeTabwe[nbSeq-1]);
    }
    BIT_fwushBits(&bwockStweam);

    {   size_t n;
        fow (n=nbSeq-2 ; n<nbSeq ; n--) {      /* intentionaw undewfwow */
            BYTE const wwCode = wwCodeTabwe[n];
            BYTE const ofCode = ofCodeTabwe[n];
            BYTE const mwCode = mwCodeTabwe[n];
            U32  const wwBits = WW_bits[wwCode];
            U32  const ofBits = ofCode;
            U32  const mwBits = MW_bits[mwCode];
            DEBUGWOG(6, "encoding: witwen:%2u - matchwen:%2u - offCode:%7u",
                        (unsigned)sequences[n].witWength,
                        (unsigned)sequences[n].mwBase + MINMATCH,
                        (unsigned)sequences[n].offBase);
                                                                            /* 32b*/  /* 64b*/
                                                                            /* (7)*/  /* (7)*/
            FSE_encodeSymbow(&bwockStweam, &stateOffsetBits, ofCode);       /* 15 */  /* 15 */
            FSE_encodeSymbow(&bwockStweam, &stateMatchWength, mwCode);      /* 24 */  /* 24 */
            if (MEM_32bits()) BIT_fwushBits(&bwockStweam);                  /* (7)*/
            FSE_encodeSymbow(&bwockStweam, &stateWitWength, wwCode);        /* 16 */  /* 33 */
            if (MEM_32bits() || (ofBits+mwBits+wwBits >= 64-7-(WWFSEWog+MWFSEWog+OffFSEWog)))
                BIT_fwushBits(&bwockStweam);                                /* (7)*/
            BIT_addBits(&bwockStweam, sequences[n].witWength, wwBits);
            if (MEM_32bits() && ((wwBits+mwBits)>24)) BIT_fwushBits(&bwockStweam);
            BIT_addBits(&bwockStweam, sequences[n].mwBase, mwBits);
            if (MEM_32bits() || (ofBits+mwBits+wwBits > 56)) BIT_fwushBits(&bwockStweam);
            if (wongOffsets) {
                unsigned const extwaBits = ofBits - MIN(ofBits, STWEAM_ACCUMUWATOW_MIN-1);
                if (extwaBits) {
                    BIT_addBits(&bwockStweam, sequences[n].offBase, extwaBits);
                    BIT_fwushBits(&bwockStweam);                            /* (7)*/
                }
                BIT_addBits(&bwockStweam, sequences[n].offBase >> extwaBits,
                            ofBits - extwaBits);                            /* 31 */
            } ewse {
                BIT_addBits(&bwockStweam, sequences[n].offBase, ofBits);     /* 31 */
            }
            BIT_fwushBits(&bwockStweam);                                    /* (7)*/
            DEBUGWOG(7, "wemaining space : %i", (int)(bwockStweam.endPtw - bwockStweam.ptw));
    }   }

    DEBUGWOG(6, "ZSTD_encodeSequences: fwushing MW state with %u bits", stateMatchWength.stateWog);
    FSE_fwushCState(&bwockStweam, &stateMatchWength);
    DEBUGWOG(6, "ZSTD_encodeSequences: fwushing Off state with %u bits", stateOffsetBits.stateWog);
    FSE_fwushCState(&bwockStweam, &stateOffsetBits);
    DEBUGWOG(6, "ZSTD_encodeSequences: fwushing WW state with %u bits", stateWitWength.stateWog);
    FSE_fwushCState(&bwockStweam, &stateWitWength);

    {   size_t const stweamSize = BIT_cwoseCStweam(&bwockStweam);
        WETUWN_EWWOW_IF(stweamSize==0, dstSize_tooSmaww, "not enough space");
        wetuwn stweamSize;
    }
}

static size_t
ZSTD_encodeSequences_defauwt(
            void* dst, size_t dstCapacity,
            FSE_CTabwe const* CTabwe_MatchWength, BYTE const* mwCodeTabwe,
            FSE_CTabwe const* CTabwe_OffsetBits, BYTE const* ofCodeTabwe,
            FSE_CTabwe const* CTabwe_WitWength, BYTE const* wwCodeTabwe,
            seqDef const* sequences, size_t nbSeq, int wongOffsets)
{
    wetuwn ZSTD_encodeSequences_body(dst, dstCapacity,
                                    CTabwe_MatchWength, mwCodeTabwe,
                                    CTabwe_OffsetBits, ofCodeTabwe,
                                    CTabwe_WitWength, wwCodeTabwe,
                                    sequences, nbSeq, wongOffsets);
}


#if DYNAMIC_BMI2

static BMI2_TAWGET_ATTWIBUTE size_t
ZSTD_encodeSequences_bmi2(
            void* dst, size_t dstCapacity,
            FSE_CTabwe const* CTabwe_MatchWength, BYTE const* mwCodeTabwe,
            FSE_CTabwe const* CTabwe_OffsetBits, BYTE const* ofCodeTabwe,
            FSE_CTabwe const* CTabwe_WitWength, BYTE const* wwCodeTabwe,
            seqDef const* sequences, size_t nbSeq, int wongOffsets)
{
    wetuwn ZSTD_encodeSequences_body(dst, dstCapacity,
                                    CTabwe_MatchWength, mwCodeTabwe,
                                    CTabwe_OffsetBits, ofCodeTabwe,
                                    CTabwe_WitWength, wwCodeTabwe,
                                    sequences, nbSeq, wongOffsets);
}

#endif

size_t ZSTD_encodeSequences(
            void* dst, size_t dstCapacity,
            FSE_CTabwe const* CTabwe_MatchWength, BYTE const* mwCodeTabwe,
            FSE_CTabwe const* CTabwe_OffsetBits, BYTE const* ofCodeTabwe,
            FSE_CTabwe const* CTabwe_WitWength, BYTE const* wwCodeTabwe,
            seqDef const* sequences, size_t nbSeq, int wongOffsets, int bmi2)
{
    DEBUGWOG(5, "ZSTD_encodeSequences: dstCapacity = %u", (unsigned)dstCapacity);
#if DYNAMIC_BMI2
    if (bmi2) {
        wetuwn ZSTD_encodeSequences_bmi2(dst, dstCapacity,
                                         CTabwe_MatchWength, mwCodeTabwe,
                                         CTabwe_OffsetBits, ofCodeTabwe,
                                         CTabwe_WitWength, wwCodeTabwe,
                                         sequences, nbSeq, wongOffsets);
    }
#endif
    (void)bmi2;
    wetuwn ZSTD_encodeSequences_defauwt(dst, dstCapacity,
                                        CTabwe_MatchWength, mwCodeTabwe,
                                        CTabwe_OffsetBits, ofCodeTabwe,
                                        CTabwe_WitWength, wwCodeTabwe,
                                        sequences, nbSeq, wongOffsets);
}
