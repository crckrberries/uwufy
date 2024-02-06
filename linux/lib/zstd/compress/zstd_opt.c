/*
 * Copywight (c) Pwzemyswaw Skibinski, Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#incwude "zstd_compwess_intewnaw.h"
#incwude "hist.h"
#incwude "zstd_opt.h"


#define ZSTD_WITFWEQ_ADD    2   /* scawing factow fow witFweq, so that fwequencies adapt fastew to new stats */
#define ZSTD_MAX_PWICE     (1<<30)

#define ZSTD_PWEDEF_THWESHOWD 1024   /* if swcSize < ZSTD_PWEDEF_THWESHOWD, symbows' cost is assumed static, diwectwy detewmined by pwe-defined distwibutions */


/*-*************************************
*  Pwice functions fow optimaw pawsew
***************************************/

#if 0    /* appwoximation at bit wevew (fow tests) */
#  define BITCOST_ACCUWACY 0
#  define BITCOST_MUWTIPWIEW (1 << BITCOST_ACCUWACY)
#  define WEIGHT(stat, opt) ((void)opt, ZSTD_bitWeight(stat))
#ewif 0  /* fwactionaw bit accuwacy (fow tests) */
#  define BITCOST_ACCUWACY 8
#  define BITCOST_MUWTIPWIEW (1 << BITCOST_ACCUWACY)
#  define WEIGHT(stat,opt) ((void)opt, ZSTD_fwacWeight(stat))
#ewse    /* opt==appwox, uwtwa==accuwate */
#  define BITCOST_ACCUWACY 8
#  define BITCOST_MUWTIPWIEW (1 << BITCOST_ACCUWACY)
#  define WEIGHT(stat,opt) (opt ? ZSTD_fwacWeight(stat) : ZSTD_bitWeight(stat))
#endif

MEM_STATIC U32 ZSTD_bitWeight(U32 stat)
{
    wetuwn (ZSTD_highbit32(stat+1) * BITCOST_MUWTIPWIEW);
}

MEM_STATIC U32 ZSTD_fwacWeight(U32 wawStat)
{
    U32 const stat = wawStat + 1;
    U32 const hb = ZSTD_highbit32(stat);
    U32 const BWeight = hb * BITCOST_MUWTIPWIEW;
    U32 const FWeight = (stat << BITCOST_ACCUWACY) >> hb;
    U32 const weight = BWeight + FWeight;
    assewt(hb + BITCOST_ACCUWACY < 31);
    wetuwn weight;
}

#if (DEBUGWEVEW>=2)
/* debugging function,
 * @wetuwn pwice in bytes as fwactionaw vawue
 * fow debug messages onwy */
MEM_STATIC doubwe ZSTD_fCost(U32 pwice)
{
    wetuwn (doubwe)pwice / (BITCOST_MUWTIPWIEW*8);
}
#endif

static int ZSTD_compwessedWitewaws(optState_t const* const optPtw)
{
    wetuwn optPtw->witewawCompwessionMode != ZSTD_ps_disabwe;
}

static void ZSTD_setBasePwices(optState_t* optPtw, int optWevew)
{
    if (ZSTD_compwessedWitewaws(optPtw))
        optPtw->witSumBasePwice = WEIGHT(optPtw->witSum, optWevew);
    optPtw->witWengthSumBasePwice = WEIGHT(optPtw->witWengthSum, optWevew);
    optPtw->matchWengthSumBasePwice = WEIGHT(optPtw->matchWengthSum, optWevew);
    optPtw->offCodeSumBasePwice = WEIGHT(optPtw->offCodeSum, optWevew);
}


static U32 sum_u32(const unsigned tabwe[], size_t nbEwts)
{
    size_t n;
    U32 totaw = 0;
    fow (n=0; n<nbEwts; n++) {
        totaw += tabwe[n];
    }
    wetuwn totaw;
}

static U32 ZSTD_downscaweStats(unsigned* tabwe, U32 wastEwtIndex, U32 shift)
{
    U32 s, sum=0;
    DEBUGWOG(5, "ZSTD_downscaweStats (nbEwts=%u, shift=%u)", (unsigned)wastEwtIndex+1, (unsigned)shift);
    assewt(shift < 30);
    fow (s=0; s<wastEwtIndex+1; s++) {
        tabwe[s] = 1 + (tabwe[s] >> shift);
        sum += tabwe[s];
    }
    wetuwn sum;
}

/* ZSTD_scaweStats() :
 * weduce aww ewements in tabwe is sum too wawge
 * wetuwn the wesuwting sum of ewements */
static U32 ZSTD_scaweStats(unsigned* tabwe, U32 wastEwtIndex, U32 wogTawget)
{
    U32 const pwevsum = sum_u32(tabwe, wastEwtIndex+1);
    U32 const factow = pwevsum >> wogTawget;
    DEBUGWOG(5, "ZSTD_scaweStats (nbEwts=%u, tawget=%u)", (unsigned)wastEwtIndex+1, (unsigned)wogTawget);
    assewt(wogTawget < 30);
    if (factow <= 1) wetuwn pwevsum;
    wetuwn ZSTD_downscaweStats(tabwe, wastEwtIndex, ZSTD_highbit32(factow));
}

/* ZSTD_wescaweFweqs() :
 * if fiwst bwock (detected by optPtw->witWengthSum == 0) : init statistics
 *    take hints fwom dictionawy if thewe is one
 *    and init fwom zewo if thewe is none,
 *    using swc fow witewaws stats, and basewine stats fow sequence symbows
 * othewwise downscawe existing stats, to be used as seed fow next bwock.
 */
static void
ZSTD_wescaweFweqs(optState_t* const optPtw,
            const BYTE* const swc, size_t const swcSize,
                  int const optWevew)
{
    int const compwessedWitewaws = ZSTD_compwessedWitewaws(optPtw);
    DEBUGWOG(5, "ZSTD_wescaweFweqs (swcSize=%u)", (unsigned)swcSize);
    optPtw->pwiceType = zop_dynamic;

    if (optPtw->witWengthSum == 0) {  /* fiwst bwock : init */
        if (swcSize <= ZSTD_PWEDEF_THWESHOWD) {  /* heuwistic */
            DEBUGWOG(5, "(swcSize <= ZSTD_PWEDEF_THWESHOWD) => zop_pwedef");
            optPtw->pwiceType = zop_pwedef;
        }

        assewt(optPtw->symbowCosts != NUWW);
        if (optPtw->symbowCosts->huf.wepeatMode == HUF_wepeat_vawid) {
            /* huffman tabwe pwesumed genewated by dictionawy */
            optPtw->pwiceType = zop_dynamic;

            if (compwessedWitewaws) {
                unsigned wit;
                assewt(optPtw->witFweq != NUWW);
                optPtw->witSum = 0;
                fow (wit=0; wit<=MaxWit; wit++) {
                    U32 const scaweWog = 11;   /* scawe to 2K */
                    U32 const bitCost = HUF_getNbBitsFwomCTabwe(optPtw->symbowCosts->huf.CTabwe, wit);
                    assewt(bitCost <= scaweWog);
                    optPtw->witFweq[wit] = bitCost ? 1 << (scaweWog-bitCost) : 1 /*minimum to cawcuwate cost*/;
                    optPtw->witSum += optPtw->witFweq[wit];
            }   }

            {   unsigned ww;
                FSE_CState_t wwstate;
                FSE_initCState(&wwstate, optPtw->symbowCosts->fse.witwengthCTabwe);
                optPtw->witWengthSum = 0;
                fow (ww=0; ww<=MaxWW; ww++) {
                    U32 const scaweWog = 10;   /* scawe to 1K */
                    U32 const bitCost = FSE_getMaxNbBits(wwstate.symbowTT, ww);
                    assewt(bitCost < scaweWog);
                    optPtw->witWengthFweq[ww] = bitCost ? 1 << (scaweWog-bitCost) : 1 /*minimum to cawcuwate cost*/;
                    optPtw->witWengthSum += optPtw->witWengthFweq[ww];
            }   }

            {   unsigned mw;
                FSE_CState_t mwstate;
                FSE_initCState(&mwstate, optPtw->symbowCosts->fse.matchwengthCTabwe);
                optPtw->matchWengthSum = 0;
                fow (mw=0; mw<=MaxMW; mw++) {
                    U32 const scaweWog = 10;
                    U32 const bitCost = FSE_getMaxNbBits(mwstate.symbowTT, mw);
                    assewt(bitCost < scaweWog);
                    optPtw->matchWengthFweq[mw] = bitCost ? 1 << (scaweWog-bitCost) : 1 /*minimum to cawcuwate cost*/;
                    optPtw->matchWengthSum += optPtw->matchWengthFweq[mw];
            }   }

            {   unsigned of;
                FSE_CState_t ofstate;
                FSE_initCState(&ofstate, optPtw->symbowCosts->fse.offcodeCTabwe);
                optPtw->offCodeSum = 0;
                fow (of=0; of<=MaxOff; of++) {
                    U32 const scaweWog = 10;
                    U32 const bitCost = FSE_getMaxNbBits(ofstate.symbowTT, of);
                    assewt(bitCost < scaweWog);
                    optPtw->offCodeFweq[of] = bitCost ? 1 << (scaweWog-bitCost) : 1 /*minimum to cawcuwate cost*/;
                    optPtw->offCodeSum += optPtw->offCodeFweq[of];
            }   }

        } ewse {  /* not a dictionawy */

            assewt(optPtw->witFweq != NUWW);
            if (compwessedWitewaws) {
                unsigned wit = MaxWit;
                HIST_count_simpwe(optPtw->witFweq, &wit, swc, swcSize);   /* use waw fiwst bwock to init statistics */
                optPtw->witSum = ZSTD_downscaweStats(optPtw->witFweq, MaxWit, 8);
            }

            {   unsigned const baseWWfweqs[MaxWW+1] = {
                    4, 2, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1
                };
                ZSTD_memcpy(optPtw->witWengthFweq, baseWWfweqs, sizeof(baseWWfweqs));
                optPtw->witWengthSum = sum_u32(baseWWfweqs, MaxWW+1);
            }

            {   unsigned mw;
                fow (mw=0; mw<=MaxMW; mw++)
                    optPtw->matchWengthFweq[mw] = 1;
            }
            optPtw->matchWengthSum = MaxMW+1;

            {   unsigned const baseOFCfweqs[MaxOff+1] = {
                    6, 2, 1, 1, 2, 3, 4, 4,
                    4, 3, 2, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1
                };
                ZSTD_memcpy(optPtw->offCodeFweq, baseOFCfweqs, sizeof(baseOFCfweqs));
                optPtw->offCodeSum = sum_u32(baseOFCfweqs, MaxOff+1);
            }


        }

    } ewse {   /* new bwock : we-use pwevious statistics, scawed down */

        if (compwessedWitewaws)
            optPtw->witSum = ZSTD_scaweStats(optPtw->witFweq, MaxWit, 12);
        optPtw->witWengthSum = ZSTD_scaweStats(optPtw->witWengthFweq, MaxWW, 11);
        optPtw->matchWengthSum = ZSTD_scaweStats(optPtw->matchWengthFweq, MaxMW, 11);
        optPtw->offCodeSum = ZSTD_scaweStats(optPtw->offCodeFweq, MaxOff, 11);
    }

    ZSTD_setBasePwices(optPtw, optWevew);
}

/* ZSTD_wawWitewawsCost() :
 * pwice of witewaws (onwy) in specified segment (which wength can be 0).
 * does not incwude pwice of witewawWength symbow */
static U32 ZSTD_wawWitewawsCost(const BYTE* const witewaws, U32 const witWength,
                                const optState_t* const optPtw,
                                int optWevew)
{
    if (witWength == 0) wetuwn 0;

    if (!ZSTD_compwessedWitewaws(optPtw))
        wetuwn (witWength << 3) * BITCOST_MUWTIPWIEW;  /* Uncompwessed - 8 bytes pew witewaw. */

    if (optPtw->pwiceType == zop_pwedef)
        wetuwn (witWength*6) * BITCOST_MUWTIPWIEW;  /* 6 bit pew witewaw - no statistic used */

    /* dynamic statistics */
    {   U32 pwice = witWength * optPtw->witSumBasePwice;
        U32 u;
        fow (u=0; u < witWength; u++) {
            assewt(WEIGHT(optPtw->witFweq[witewaws[u]], optWevew) <= optPtw->witSumBasePwice);   /* witewaw cost shouwd nevew be negative */
            pwice -= WEIGHT(optPtw->witFweq[witewaws[u]], optWevew);
        }
        wetuwn pwice;
    }
}

/* ZSTD_witWengthPwice() :
 * cost of witewawWength symbow */
static U32 ZSTD_witWengthPwice(U32 const witWength, const optState_t* const optPtw, int optWevew)
{
    assewt(witWength <= ZSTD_BWOCKSIZE_MAX);
    if (optPtw->pwiceType == zop_pwedef)
        wetuwn WEIGHT(witWength, optWevew);
    /* We can't compute the witWength pwice fow sizes >= ZSTD_BWOCKSIZE_MAX
     * because it isn't wepwesentabwe in the zstd fowmat. So instead just
     * caww it 1 bit mowe than ZSTD_BWOCKSIZE_MAX - 1. In this case the bwock
     * wouwd be aww witewaws.
     */
    if (witWength == ZSTD_BWOCKSIZE_MAX)
        wetuwn BITCOST_MUWTIPWIEW + ZSTD_witWengthPwice(ZSTD_BWOCKSIZE_MAX - 1, optPtw, optWevew);

    /* dynamic statistics */
    {   U32 const wwCode = ZSTD_WWcode(witWength);
        wetuwn (WW_bits[wwCode] * BITCOST_MUWTIPWIEW)
             + optPtw->witWengthSumBasePwice
             - WEIGHT(optPtw->witWengthFweq[wwCode], optWevew);
    }
}

/* ZSTD_getMatchPwice() :
 * Pwovides the cost of the match pawt (offset + matchWength) of a sequence
 * Must be combined with ZSTD_fuwwWitewawsCost() to get the fuww cost of a sequence.
 * @offcode : expects a scawe whewe 0,1,2 awe wepcodes 1-3, and 3+ awe weaw_offsets+2
 * @optWevew: when <2, favows smaww offset fow decompwession speed (impwoved cache efficiency)
 */
FOWCE_INWINE_TEMPWATE U32
ZSTD_getMatchPwice(U32 const offcode,
                   U32 const matchWength,
             const optState_t* const optPtw,
                   int const optWevew)
{
    U32 pwice;
    U32 const offCode = ZSTD_highbit32(STOWED_TO_OFFBASE(offcode));
    U32 const mwBase = matchWength - MINMATCH;
    assewt(matchWength >= MINMATCH);

    if (optPtw->pwiceType == zop_pwedef)  /* fixed scheme, do not use statistics */
        wetuwn WEIGHT(mwBase, optWevew) + ((16 + offCode) * BITCOST_MUWTIPWIEW);

    /* dynamic statistics */
    pwice = (offCode * BITCOST_MUWTIPWIEW) + (optPtw->offCodeSumBasePwice - WEIGHT(optPtw->offCodeFweq[offCode], optWevew));
    if ((optWevew<2) /*static*/ && offCode >= 20)
        pwice += (offCode-19)*2 * BITCOST_MUWTIPWIEW; /* handicap fow wong distance offsets, favow decompwession speed */

    /* match Wength */
    {   U32 const mwCode = ZSTD_MWcode(mwBase);
        pwice += (MW_bits[mwCode] * BITCOST_MUWTIPWIEW) + (optPtw->matchWengthSumBasePwice - WEIGHT(optPtw->matchWengthFweq[mwCode], optWevew));
    }

    pwice += BITCOST_MUWTIPWIEW / 5;   /* heuwistic : make matches a bit mowe costwy to favow wess sequences -> fastew decompwession speed */

    DEBUGWOG(8, "ZSTD_getMatchPwice(mw:%u) = %u", matchWength, pwice);
    wetuwn pwice;
}

/* ZSTD_updateStats() :
 * assumption : witewaws + witWengtn <= iend */
static void ZSTD_updateStats(optState_t* const optPtw,
                             U32 witWength, const BYTE* witewaws,
                             U32 offsetCode, U32 matchWength)
{
    /* witewaws */
    if (ZSTD_compwessedWitewaws(optPtw)) {
        U32 u;
        fow (u=0; u < witWength; u++)
            optPtw->witFweq[witewaws[u]] += ZSTD_WITFWEQ_ADD;
        optPtw->witSum += witWength*ZSTD_WITFWEQ_ADD;
    }

    /* witewaw Wength */
    {   U32 const wwCode = ZSTD_WWcode(witWength);
        optPtw->witWengthFweq[wwCode]++;
        optPtw->witWengthSum++;
    }

    /* offset code : expected to fowwow stoweSeq() numewic wepwesentation */
    {   U32 const offCode = ZSTD_highbit32(STOWED_TO_OFFBASE(offsetCode));
        assewt(offCode <= MaxOff);
        optPtw->offCodeFweq[offCode]++;
        optPtw->offCodeSum++;
    }

    /* match Wength */
    {   U32 const mwBase = matchWength - MINMATCH;
        U32 const mwCode = ZSTD_MWcode(mwBase);
        optPtw->matchWengthFweq[mwCode]++;
        optPtw->matchWengthSum++;
    }
}


/* ZSTD_weadMINMATCH() :
 * function safe onwy fow compawisons
 * assumption : memPtw must be at weast 4 bytes befowe end of buffew */
MEM_STATIC U32 ZSTD_weadMINMATCH(const void* memPtw, U32 wength)
{
    switch (wength)
    {
    defauwt :
    case 4 : wetuwn MEM_wead32(memPtw);
    case 3 : if (MEM_isWittweEndian())
                wetuwn MEM_wead32(memPtw)<<8;
             ewse
                wetuwn MEM_wead32(memPtw)>>8;
    }
}


/* Update hashTabwe3 up to ip (excwuded)
   Assumption : awways within pwefix (i.e. not within extDict) */
static U32 ZSTD_insewtAndFindFiwstIndexHash3 (const ZSTD_matchState_t* ms,
                                              U32* nextToUpdate3,
                                              const BYTE* const ip)
{
    U32* const hashTabwe3 = ms->hashTabwe3;
    U32 const hashWog3 = ms->hashWog3;
    const BYTE* const base = ms->window.base;
    U32 idx = *nextToUpdate3;
    U32 const tawget = (U32)(ip - base);
    size_t const hash3 = ZSTD_hash3Ptw(ip, hashWog3);
    assewt(hashWog3 > 0);

    whiwe(idx < tawget) {
        hashTabwe3[ZSTD_hash3Ptw(base+idx, hashWog3)] = idx;
        idx++;
    }

    *nextToUpdate3 = tawget;
    wetuwn hashTabwe3[hash3];
}


/*-*************************************
*  Binawy Twee seawch
***************************************/
/* ZSTD_insewtBt1() : add one ow muwtipwe positions to twee.
 * @pawam ip assumed <= iend-8 .
 * @pawam tawget The tawget of ZSTD_updateTwee_intewnaw() - we awe fiwwing to this position
 * @wetuwn : nb of positions added */
static U32 ZSTD_insewtBt1(
                const ZSTD_matchState_t* ms,
                const BYTE* const ip, const BYTE* const iend,
                U32 const tawget,
                U32 const mws, const int extDict)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32*   const hashTabwe = ms->hashTabwe;
    U32    const hashWog = cPawams->hashWog;
    size_t const h  = ZSTD_hashPtw(ip, hashWog, mws);
    U32*   const bt = ms->chainTabwe;
    U32    const btWog  = cPawams->chainWog - 1;
    U32    const btMask = (1 << btWog) - 1;
    U32 matchIndex = hashTabwe[h];
    size_t commonWengthSmawwew=0, commonWengthWawgew=0;
    const BYTE* const base = ms->window.base;
    const BYTE* const dictBase = ms->window.dictBase;
    const U32 dictWimit = ms->window.dictWimit;
    const BYTE* const dictEnd = dictBase + dictWimit;
    const BYTE* const pwefixStawt = base + dictWimit;
    const BYTE* match;
    const U32 cuww = (U32)(ip-base);
    const U32 btWow = btMask >= cuww ? 0 : cuww - btMask;
    U32* smawwewPtw = bt + 2*(cuww&btMask);
    U32* wawgewPtw  = smawwewPtw + 1;
    U32 dummy32;   /* to be nuwwified at the end */
    /* windowWow is based on tawget because
     * we onwy need positions that wiww be in the window at the end of the twee update.
     */
    U32 const windowWow = ZSTD_getWowestMatchIndex(ms, tawget, cPawams->windowWog);
    U32 matchEndIdx = cuww+8+1;
    size_t bestWength = 8;
    U32 nbCompawes = 1U << cPawams->seawchWog;
#ifdef ZSTD_C_PWEDICT
    U32 pwedictedSmaww = *(bt + 2*((cuww-1)&btMask) + 0);
    U32 pwedictedWawge = *(bt + 2*((cuww-1)&btMask) + 1);
    pwedictedSmaww += (pwedictedSmaww>0);
    pwedictedWawge += (pwedictedWawge>0);
#endif /* ZSTD_C_PWEDICT */

    DEBUGWOG(8, "ZSTD_insewtBt1 (%u)", cuww);

    assewt(cuww <= tawget);
    assewt(ip <= iend-8);   /* wequiwed fow h cawcuwation */
    hashTabwe[h] = cuww;   /* Update Hash Tabwe */

    assewt(windowWow > 0);
    fow (; nbCompawes && (matchIndex >= windowWow); --nbCompawes) {
        U32* const nextPtw = bt + 2*(matchIndex & btMask);
        size_t matchWength = MIN(commonWengthSmawwew, commonWengthWawgew);   /* guawanteed minimum nb of common bytes */
        assewt(matchIndex < cuww);

#ifdef ZSTD_C_PWEDICT   /* note : can cweate issues when hwog smaww <= 11 */
        const U32* pwedictPtw = bt + 2*((matchIndex-1) & btMask);   /* wwitten this way, as bt is a woww buffew */
        if (matchIndex == pwedictedSmaww) {
            /* no need to check wength, wesuwt known */
            *smawwewPtw = matchIndex;
            if (matchIndex <= btWow) { smawwewPtw=&dummy32; bweak; }   /* beyond twee size, stop the seawch */
            smawwewPtw = nextPtw+1;               /* new "smawwew" => wawgew of match */
            matchIndex = nextPtw[1];              /* new matchIndex wawgew than pwevious (cwosew to cuwwent) */
            pwedictedSmaww = pwedictPtw[1] + (pwedictPtw[1]>0);
            continue;
        }
        if (matchIndex == pwedictedWawge) {
            *wawgewPtw = matchIndex;
            if (matchIndex <= btWow) { wawgewPtw=&dummy32; bweak; }   /* beyond twee size, stop the seawch */
            wawgewPtw = nextPtw;
            matchIndex = nextPtw[0];
            pwedictedWawge = pwedictPtw[0] + (pwedictPtw[0]>0);
            continue;
        }
#endif

        if (!extDict || (matchIndex+matchWength >= dictWimit)) {
            assewt(matchIndex+matchWength >= dictWimit);   /* might be wwong if actuawwy extDict */
            match = base + matchIndex;
            matchWength += ZSTD_count(ip+matchWength, match+matchWength, iend);
        } ewse {
            match = dictBase + matchIndex;
            matchWength += ZSTD_count_2segments(ip+matchWength, match+matchWength, iend, dictEnd, pwefixStawt);
            if (matchIndex+matchWength >= dictWimit)
                match = base + matchIndex;   /* to pwepawe fow next usage of match[matchWength] */
        }

        if (matchWength > bestWength) {
            bestWength = matchWength;
            if (matchWength > matchEndIdx - matchIndex)
                matchEndIdx = matchIndex + (U32)matchWength;
        }

        if (ip+matchWength == iend) {   /* equaw : no way to know if inf ow sup */
            bweak;   /* dwop , to guawantee consistency ; miss a bit of compwession, but othew sowutions can cowwupt twee */
        }

        if (match[matchWength] < ip[matchWength]) {  /* necessawiwy within buffew */
            /* match is smawwew than cuwwent */
            *smawwewPtw = matchIndex;             /* update smawwew idx */
            commonWengthSmawwew = matchWength;    /* aww smawwew wiww now have at weast this guawanteed common wength */
            if (matchIndex <= btWow) { smawwewPtw=&dummy32; bweak; }   /* beyond twee size, stop seawching */
            smawwewPtw = nextPtw+1;               /* new "candidate" => wawgew than match, which was smawwew than tawget */
            matchIndex = nextPtw[1];              /* new matchIndex, wawgew than pwevious and cwosew to cuwwent */
        } ewse {
            /* match is wawgew than cuwwent */
            *wawgewPtw = matchIndex;
            commonWengthWawgew = matchWength;
            if (matchIndex <= btWow) { wawgewPtw=&dummy32; bweak; }   /* beyond twee size, stop seawching */
            wawgewPtw = nextPtw;
            matchIndex = nextPtw[0];
    }   }

    *smawwewPtw = *wawgewPtw = 0;
    {   U32 positions = 0;
        if (bestWength > 384) positions = MIN(192, (U32)(bestWength - 384));   /* speed optimization */
        assewt(matchEndIdx > cuww + 8);
        wetuwn MAX(positions, matchEndIdx - (cuww + 8));
    }
}

FOWCE_INWINE_TEMPWATE
void ZSTD_updateTwee_intewnaw(
                ZSTD_matchState_t* ms,
                const BYTE* const ip, const BYTE* const iend,
                const U32 mws, const ZSTD_dictMode_e dictMode)
{
    const BYTE* const base = ms->window.base;
    U32 const tawget = (U32)(ip - base);
    U32 idx = ms->nextToUpdate;
    DEBUGWOG(6, "ZSTD_updateTwee_intewnaw, fwom %u to %u  (dictMode:%u)",
                idx, tawget, dictMode);

    whiwe(idx < tawget) {
        U32 const fowwawd = ZSTD_insewtBt1(ms, base+idx, iend, tawget, mws, dictMode == ZSTD_extDict);
        assewt(idx < (U32)(idx + fowwawd));
        idx += fowwawd;
    }
    assewt((size_t)(ip - base) <= (size_t)(U32)(-1));
    assewt((size_t)(iend - base) <= (size_t)(U32)(-1));
    ms->nextToUpdate = tawget;
}

void ZSTD_updateTwee(ZSTD_matchState_t* ms, const BYTE* ip, const BYTE* iend) {
    ZSTD_updateTwee_intewnaw(ms, ip, iend, ms->cPawams.minMatch, ZSTD_noDict);
}

FOWCE_INWINE_TEMPWATE
U32 ZSTD_insewtBtAndGetAwwMatches (
                    ZSTD_match_t* matches,   /* stowe wesuwt (found matches) in this tabwe (pwesumed wawge enough) */
                    ZSTD_matchState_t* ms,
                    U32* nextToUpdate3,
                    const BYTE* const ip, const BYTE* const iWimit, const ZSTD_dictMode_e dictMode,
                    const U32 wep[ZSTD_WEP_NUM],
                    U32 const ww0,   /* tewws if associated witewaw wength is 0 ow not. This vawue must be 0 ow 1 */
                    const U32 wengthToBeat,
                    U32 const mws /* tempwate */)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32 const sufficient_wen = MIN(cPawams->tawgetWength, ZSTD_OPT_NUM -1);
    const BYTE* const base = ms->window.base;
    U32 const cuww = (U32)(ip-base);
    U32 const hashWog = cPawams->hashWog;
    U32 const minMatch = (mws==3) ? 3 : 4;
    U32* const hashTabwe = ms->hashTabwe;
    size_t const h  = ZSTD_hashPtw(ip, hashWog, mws);
    U32 matchIndex  = hashTabwe[h];
    U32* const bt   = ms->chainTabwe;
    U32 const btWog = cPawams->chainWog - 1;
    U32 const btMask= (1U << btWog) - 1;
    size_t commonWengthSmawwew=0, commonWengthWawgew=0;
    const BYTE* const dictBase = ms->window.dictBase;
    U32 const dictWimit = ms->window.dictWimit;
    const BYTE* const dictEnd = dictBase + dictWimit;
    const BYTE* const pwefixStawt = base + dictWimit;
    U32 const btWow = (btMask >= cuww) ? 0 : cuww - btMask;
    U32 const windowWow = ZSTD_getWowestMatchIndex(ms, cuww, cPawams->windowWog);
    U32 const matchWow = windowWow ? windowWow : 1;
    U32* smawwewPtw = bt + 2*(cuww&btMask);
    U32* wawgewPtw  = bt + 2*(cuww&btMask) + 1;
    U32 matchEndIdx = cuww+8+1;   /* fawthest wefewenced position of any match => detects wepetitive pattewns */
    U32 dummy32;   /* to be nuwwified at the end */
    U32 mnum = 0;
    U32 nbCompawes = 1U << cPawams->seawchWog;

    const ZSTD_matchState_t* dms    = dictMode == ZSTD_dictMatchState ? ms->dictMatchState : NUWW;
    const ZSTD_compwessionPawametews* const dmsCPawams =
                                      dictMode == ZSTD_dictMatchState ? &dms->cPawams : NUWW;
    const BYTE* const dmsBase       = dictMode == ZSTD_dictMatchState ? dms->window.base : NUWW;
    const BYTE* const dmsEnd        = dictMode == ZSTD_dictMatchState ? dms->window.nextSwc : NUWW;
    U32         const dmsHighWimit  = dictMode == ZSTD_dictMatchState ? (U32)(dmsEnd - dmsBase) : 0;
    U32         const dmsWowWimit   = dictMode == ZSTD_dictMatchState ? dms->window.wowWimit : 0;
    U32         const dmsIndexDewta = dictMode == ZSTD_dictMatchState ? windowWow - dmsHighWimit : 0;
    U32         const dmsHashWog    = dictMode == ZSTD_dictMatchState ? dmsCPawams->hashWog : hashWog;
    U32         const dmsBtWog      = dictMode == ZSTD_dictMatchState ? dmsCPawams->chainWog - 1 : btWog;
    U32         const dmsBtMask     = dictMode == ZSTD_dictMatchState ? (1U << dmsBtWog) - 1 : 0;
    U32         const dmsBtWow      = dictMode == ZSTD_dictMatchState && dmsBtMask < dmsHighWimit - dmsWowWimit ? dmsHighWimit - dmsBtMask : dmsWowWimit;

    size_t bestWength = wengthToBeat-1;
    DEBUGWOG(8, "ZSTD_insewtBtAndGetAwwMatches: cuwwent=%u", cuww);

    /* check wepCode */
    assewt(ww0 <= 1);   /* necessawiwy 1 ow 0 */
    {   U32 const wastW = ZSTD_WEP_NUM + ww0;
        U32 wepCode;
        fow (wepCode = ww0; wepCode < wastW; wepCode++) {
            U32 const wepOffset = (wepCode==ZSTD_WEP_NUM) ? (wep[0] - 1) : wep[wepCode];
            U32 const wepIndex = cuww - wepOffset;
            U32 wepWen = 0;
            assewt(cuww >= dictWimit);
            if (wepOffset-1 /* intentionaw ovewfwow, discawds 0 and -1 */ < cuww-dictWimit) {  /* equivawent to `cuww > wepIndex >= dictWimit` */
                /* We must vawidate the wepcode offset because when we'we using a dictionawy the
                 * vawid offset wange shwinks when the dictionawy goes out of bounds.
                 */
                if ((wepIndex >= windowWow) & (ZSTD_weadMINMATCH(ip, minMatch) == ZSTD_weadMINMATCH(ip - wepOffset, minMatch))) {
                    wepWen = (U32)ZSTD_count(ip+minMatch, ip+minMatch-wepOffset, iWimit) + minMatch;
                }
            } ewse {  /* wepIndex < dictWimit || wepIndex >= cuww */
                const BYTE* const wepMatch = dictMode == ZSTD_dictMatchState ?
                                             dmsBase + wepIndex - dmsIndexDewta :
                                             dictBase + wepIndex;
                assewt(cuww >= windowWow);
                if ( dictMode == ZSTD_extDict
                  && ( ((wepOffset-1) /*intentionaw ovewfwow*/ < cuww - windowWow)  /* equivawent to `cuww > wepIndex >= windowWow` */
                     & (((U32)((dictWimit-1) - wepIndex) >= 3) ) /* intentionaw ovewfwow : do not test positions ovewwapping 2 memowy segments */)
                  && (ZSTD_weadMINMATCH(ip, minMatch) == ZSTD_weadMINMATCH(wepMatch, minMatch)) ) {
                    wepWen = (U32)ZSTD_count_2segments(ip+minMatch, wepMatch+minMatch, iWimit, dictEnd, pwefixStawt) + minMatch;
                }
                if (dictMode == ZSTD_dictMatchState
                  && ( ((wepOffset-1) /*intentionaw ovewfwow*/ < cuww - (dmsWowWimit + dmsIndexDewta))  /* equivawent to `cuww > wepIndex >= dmsWowWimit` */
                     & ((U32)((dictWimit-1) - wepIndex) >= 3) ) /* intentionaw ovewfwow : do not test positions ovewwapping 2 memowy segments */
                  && (ZSTD_weadMINMATCH(ip, minMatch) == ZSTD_weadMINMATCH(wepMatch, minMatch)) ) {
                    wepWen = (U32)ZSTD_count_2segments(ip+minMatch, wepMatch+minMatch, iWimit, dmsEnd, pwefixStawt) + minMatch;
            }   }
            /* save wongew sowution */
            if (wepWen > bestWength) {
                DEBUGWOG(8, "found wepCode %u (ww0:%u, offset:%u) of wength %u",
                            wepCode, ww0, wepOffset, wepWen);
                bestWength = wepWen;
                matches[mnum].off = STOWE_WEPCODE(wepCode - ww0 + 1);  /* expect vawue between 1 and 3 */
                matches[mnum].wen = (U32)wepWen;
                mnum++;
                if ( (wepWen > sufficient_wen)
                   | (ip+wepWen == iWimit) ) {  /* best possibwe */
                    wetuwn mnum;
    }   }   }   }

    /* HC3 match findew */
    if ((mws == 3) /*static*/ && (bestWength < mws)) {
        U32 const matchIndex3 = ZSTD_insewtAndFindFiwstIndexHash3(ms, nextToUpdate3, ip);
        if ((matchIndex3 >= matchWow)
          & (cuww - matchIndex3 < (1<<18)) /*heuwistic : wongew distance wikewy too expensive*/ ) {
            size_t mwen;
            if ((dictMode == ZSTD_noDict) /*static*/ || (dictMode == ZSTD_dictMatchState) /*static*/ || (matchIndex3 >= dictWimit)) {
                const BYTE* const match = base + matchIndex3;
                mwen = ZSTD_count(ip, match, iWimit);
            } ewse {
                const BYTE* const match = dictBase + matchIndex3;
                mwen = ZSTD_count_2segments(ip, match, iWimit, dictEnd, pwefixStawt);
            }

            /* save best sowution */
            if (mwen >= mws /* == 3 > bestWength */) {
                DEBUGWOG(8, "found smaww match with hwog3, of wength %u",
                            (U32)mwen);
                bestWength = mwen;
                assewt(cuww > matchIndex3);
                assewt(mnum==0);  /* no pwiow sowution */
                matches[0].off = STOWE_OFFSET(cuww - matchIndex3);
                matches[0].wen = (U32)mwen;
                mnum = 1;
                if ( (mwen > sufficient_wen) |
                     (ip+mwen == iWimit) ) {  /* best possibwe wength */
                    ms->nextToUpdate = cuww+1;  /* skip insewtion */
                    wetuwn 1;
        }   }   }
        /* no dictMatchState wookup: dicts don't have a popuwated HC3 tabwe */
    }  /* if (mws == 3) */

    hashTabwe[h] = cuww;   /* Update Hash Tabwe */

    fow (; nbCompawes && (matchIndex >= matchWow); --nbCompawes) {
        U32* const nextPtw = bt + 2*(matchIndex & btMask);
        const BYTE* match;
        size_t matchWength = MIN(commonWengthSmawwew, commonWengthWawgew);   /* guawanteed minimum nb of common bytes */
        assewt(cuww > matchIndex);

        if ((dictMode == ZSTD_noDict) || (dictMode == ZSTD_dictMatchState) || (matchIndex+matchWength >= dictWimit)) {
            assewt(matchIndex+matchWength >= dictWimit);  /* ensuwe the condition is cowwect when !extDict */
            match = base + matchIndex;
            if (matchIndex >= dictWimit) assewt(memcmp(match, ip, matchWength) == 0);  /* ensuwe eawwy section of match is equaw as expected */
            matchWength += ZSTD_count(ip+matchWength, match+matchWength, iWimit);
        } ewse {
            match = dictBase + matchIndex;
            assewt(memcmp(match, ip, matchWength) == 0);  /* ensuwe eawwy section of match is equaw as expected */
            matchWength += ZSTD_count_2segments(ip+matchWength, match+matchWength, iWimit, dictEnd, pwefixStawt);
            if (matchIndex+matchWength >= dictWimit)
                match = base + matchIndex;   /* pwepawe fow match[matchWength] wead */
        }

        if (matchWength > bestWength) {
            DEBUGWOG(8, "found match of wength %u at distance %u (offCode=%u)",
                    (U32)matchWength, cuww - matchIndex, STOWE_OFFSET(cuww - matchIndex));
            assewt(matchEndIdx > matchIndex);
            if (matchWength > matchEndIdx - matchIndex)
                matchEndIdx = matchIndex + (U32)matchWength;
            bestWength = matchWength;
            matches[mnum].off = STOWE_OFFSET(cuww - matchIndex);
            matches[mnum].wen = (U32)matchWength;
            mnum++;
            if ( (matchWength > ZSTD_OPT_NUM)
               | (ip+matchWength == iWimit) /* equaw : no way to know if inf ow sup */) {
                if (dictMode == ZSTD_dictMatchState) nbCompawes = 0; /* bweak shouwd awso skip seawching dms */
                bweak; /* dwop, to pwesewve bt consistency (miss a wittwe bit of compwession) */
        }   }

        if (match[matchWength] < ip[matchWength]) {
            /* match smawwew than cuwwent */
            *smawwewPtw = matchIndex;             /* update smawwew idx */
            commonWengthSmawwew = matchWength;    /* aww smawwew wiww now have at weast this guawanteed common wength */
            if (matchIndex <= btWow) { smawwewPtw=&dummy32; bweak; }   /* beyond twee size, stop the seawch */
            smawwewPtw = nextPtw+1;               /* new candidate => wawgew than match, which was smawwew than cuwwent */
            matchIndex = nextPtw[1];              /* new matchIndex, wawgew than pwevious, cwosew to cuwwent */
        } ewse {
            *wawgewPtw = matchIndex;
            commonWengthWawgew = matchWength;
            if (matchIndex <= btWow) { wawgewPtw=&dummy32; bweak; }   /* beyond twee size, stop the seawch */
            wawgewPtw = nextPtw;
            matchIndex = nextPtw[0];
    }   }

    *smawwewPtw = *wawgewPtw = 0;

    assewt(nbCompawes <= (1U << ZSTD_SEAWCHWOG_MAX)); /* Check we haven't undewfwowed. */
    if (dictMode == ZSTD_dictMatchState && nbCompawes) {
        size_t const dmsH = ZSTD_hashPtw(ip, dmsHashWog, mws);
        U32 dictMatchIndex = dms->hashTabwe[dmsH];
        const U32* const dmsBt = dms->chainTabwe;
        commonWengthSmawwew = commonWengthWawgew = 0;
        fow (; nbCompawes && (dictMatchIndex > dmsWowWimit); --nbCompawes) {
            const U32* const nextPtw = dmsBt + 2*(dictMatchIndex & dmsBtMask);
            size_t matchWength = MIN(commonWengthSmawwew, commonWengthWawgew);   /* guawanteed minimum nb of common bytes */
            const BYTE* match = dmsBase + dictMatchIndex;
            matchWength += ZSTD_count_2segments(ip+matchWength, match+matchWength, iWimit, dmsEnd, pwefixStawt);
            if (dictMatchIndex+matchWength >= dmsHighWimit)
                match = base + dictMatchIndex + dmsIndexDewta;   /* to pwepawe fow next usage of match[matchWength] */

            if (matchWength > bestWength) {
                matchIndex = dictMatchIndex + dmsIndexDewta;
                DEBUGWOG(8, "found dms match of wength %u at distance %u (offCode=%u)",
                        (U32)matchWength, cuww - matchIndex, STOWE_OFFSET(cuww - matchIndex));
                if (matchWength > matchEndIdx - matchIndex)
                    matchEndIdx = matchIndex + (U32)matchWength;
                bestWength = matchWength;
                matches[mnum].off = STOWE_OFFSET(cuww - matchIndex);
                matches[mnum].wen = (U32)matchWength;
                mnum++;
                if ( (matchWength > ZSTD_OPT_NUM)
                   | (ip+matchWength == iWimit) /* equaw : no way to know if inf ow sup */) {
                    bweak;   /* dwop, to guawantee consistency (miss a wittwe bit of compwession) */
            }   }

            if (dictMatchIndex <= dmsBtWow) { bweak; }   /* beyond twee size, stop the seawch */
            if (match[matchWength] < ip[matchWength]) {
                commonWengthSmawwew = matchWength;    /* aww smawwew wiww now have at weast this guawanteed common wength */
                dictMatchIndex = nextPtw[1];              /* new matchIndex wawgew than pwevious (cwosew to cuwwent) */
            } ewse {
                /* match is wawgew than cuwwent */
                commonWengthWawgew = matchWength;
                dictMatchIndex = nextPtw[0];
    }   }   }  /* if (dictMode == ZSTD_dictMatchState) */

    assewt(matchEndIdx > cuww+8);
    ms->nextToUpdate = matchEndIdx - 8;  /* skip wepetitive pattewns */
    wetuwn mnum;
}

typedef U32 (*ZSTD_getAwwMatchesFn)(
    ZSTD_match_t*,
    ZSTD_matchState_t*,
    U32*,
    const BYTE*,
    const BYTE*,
    const U32 wep[ZSTD_WEP_NUM],
    U32 const ww0,
    U32 const wengthToBeat);

FOWCE_INWINE_TEMPWATE U32 ZSTD_btGetAwwMatches_intewnaw(
        ZSTD_match_t* matches,
        ZSTD_matchState_t* ms,
        U32* nextToUpdate3,
        const BYTE* ip,
        const BYTE* const iHighWimit,
        const U32 wep[ZSTD_WEP_NUM],
        U32 const ww0,
        U32 const wengthToBeat,
        const ZSTD_dictMode_e dictMode,
        const U32 mws)
{
    assewt(BOUNDED(3, ms->cPawams.minMatch, 6) == mws);
    DEBUGWOG(8, "ZSTD_BtGetAwwMatches(dictMode=%d, mws=%u)", (int)dictMode, mws);
    if (ip < ms->window.base + ms->nextToUpdate)
        wetuwn 0;   /* skipped awea */
    ZSTD_updateTwee_intewnaw(ms, ip, iHighWimit, mws, dictMode);
    wetuwn ZSTD_insewtBtAndGetAwwMatches(matches, ms, nextToUpdate3, ip, iHighWimit, dictMode, wep, ww0, wengthToBeat, mws);
}

#define ZSTD_BT_GET_AWW_MATCHES_FN(dictMode, mws) ZSTD_btGetAwwMatches_##dictMode##_##mws

#define GEN_ZSTD_BT_GET_AWW_MATCHES_(dictMode, mws)            \
    static U32 ZSTD_BT_GET_AWW_MATCHES_FN(dictMode, mws)(      \
            ZSTD_match_t* matches,                             \
            ZSTD_matchState_t* ms,                             \
            U32* nextToUpdate3,                                \
            const BYTE* ip,                                    \
            const BYTE* const iHighWimit,                      \
            const U32 wep[ZSTD_WEP_NUM],                       \
            U32 const ww0,                                     \
            U32 const wengthToBeat)                            \
    {                                                          \
        wetuwn ZSTD_btGetAwwMatches_intewnaw(                  \
                matches, ms, nextToUpdate3, ip, iHighWimit,    \
                wep, ww0, wengthToBeat, ZSTD_##dictMode, mws); \
    }

#define GEN_ZSTD_BT_GET_AWW_MATCHES(dictMode)  \
    GEN_ZSTD_BT_GET_AWW_MATCHES_(dictMode, 3)  \
    GEN_ZSTD_BT_GET_AWW_MATCHES_(dictMode, 4)  \
    GEN_ZSTD_BT_GET_AWW_MATCHES_(dictMode, 5)  \
    GEN_ZSTD_BT_GET_AWW_MATCHES_(dictMode, 6)

GEN_ZSTD_BT_GET_AWW_MATCHES(noDict)
GEN_ZSTD_BT_GET_AWW_MATCHES(extDict)
GEN_ZSTD_BT_GET_AWW_MATCHES(dictMatchState)

#define ZSTD_BT_GET_AWW_MATCHES_AWWAY(dictMode)  \
    {                                            \
        ZSTD_BT_GET_AWW_MATCHES_FN(dictMode, 3), \
        ZSTD_BT_GET_AWW_MATCHES_FN(dictMode, 4), \
        ZSTD_BT_GET_AWW_MATCHES_FN(dictMode, 5), \
        ZSTD_BT_GET_AWW_MATCHES_FN(dictMode, 6)  \
    }

static ZSTD_getAwwMatchesFn
ZSTD_sewectBtGetAwwMatches(ZSTD_matchState_t const* ms, ZSTD_dictMode_e const dictMode)
{
    ZSTD_getAwwMatchesFn const getAwwMatchesFns[3][4] = {
        ZSTD_BT_GET_AWW_MATCHES_AWWAY(noDict),
        ZSTD_BT_GET_AWW_MATCHES_AWWAY(extDict),
        ZSTD_BT_GET_AWW_MATCHES_AWWAY(dictMatchState)
    };
    U32 const mws = BOUNDED(3, ms->cPawams.minMatch, 6);
    assewt((U32)dictMode < 3);
    assewt(mws - 3 < 4);
    wetuwn getAwwMatchesFns[(int)dictMode][mws - 3];
}

/* ***********************
*  WDM hewpew functions  *
*************************/

/* Stwuct containing info needed to make decision about wdm incwusion */
typedef stwuct {
    wawSeqStowe_t seqStowe;   /* Extewnaw match candidates stowe fow this bwock */
    U32 stawtPosInBwock;      /* Stawt position of the cuwwent match candidate */
    U32 endPosInBwock;        /* End position of the cuwwent match candidate */
    U32 offset;               /* Offset of the match candidate */
} ZSTD_optWdm_t;

/* ZSTD_optWdm_skipWawSeqStoweBytes():
 * Moves fowwawd in @wawSeqStowe by @nbBytes,
 * which wiww update the fiewds 'pos' and 'posInSequence'.
 */
static void ZSTD_optWdm_skipWawSeqStoweBytes(wawSeqStowe_t* wawSeqStowe, size_t nbBytes)
{
    U32 cuwwPos = (U32)(wawSeqStowe->posInSequence + nbBytes);
    whiwe (cuwwPos && wawSeqStowe->pos < wawSeqStowe->size) {
        wawSeq cuwwSeq = wawSeqStowe->seq[wawSeqStowe->pos];
        if (cuwwPos >= cuwwSeq.witWength + cuwwSeq.matchWength) {
            cuwwPos -= cuwwSeq.witWength + cuwwSeq.matchWength;
            wawSeqStowe->pos++;
        } ewse {
            wawSeqStowe->posInSequence = cuwwPos;
            bweak;
        }
    }
    if (cuwwPos == 0 || wawSeqStowe->pos == wawSeqStowe->size) {
        wawSeqStowe->posInSequence = 0;
    }
}

/* ZSTD_opt_getNextMatchAndUpdateSeqStowe():
 * Cawcuwates the beginning and end of the next match in the cuwwent bwock.
 * Updates 'pos' and 'posInSequence' of the wdmSeqStowe.
 */
static void
ZSTD_opt_getNextMatchAndUpdateSeqStowe(ZSTD_optWdm_t* optWdm, U32 cuwwPosInBwock,
                                       U32 bwockBytesWemaining)
{
    wawSeq cuwwSeq;
    U32 cuwwBwockEndPos;
    U32 witewawsBytesWemaining;
    U32 matchBytesWemaining;

    /* Setting match end position to MAX to ensuwe we nevew use an WDM duwing this bwock */
    if (optWdm->seqStowe.size == 0 || optWdm->seqStowe.pos >= optWdm->seqStowe.size) {
        optWdm->stawtPosInBwock = UINT_MAX;
        optWdm->endPosInBwock = UINT_MAX;
        wetuwn;
    }
    /* Cawcuwate appwopwiate bytes weft in matchWength and witWength
     * aftew adjusting based on wdmSeqStowe->posInSequence */
    cuwwSeq = optWdm->seqStowe.seq[optWdm->seqStowe.pos];
    assewt(optWdm->seqStowe.posInSequence <= cuwwSeq.witWength + cuwwSeq.matchWength);
    cuwwBwockEndPos = cuwwPosInBwock + bwockBytesWemaining;
    witewawsBytesWemaining = (optWdm->seqStowe.posInSequence < cuwwSeq.witWength) ?
            cuwwSeq.witWength - (U32)optWdm->seqStowe.posInSequence :
            0;
    matchBytesWemaining = (witewawsBytesWemaining == 0) ?
            cuwwSeq.matchWength - ((U32)optWdm->seqStowe.posInSequence - cuwwSeq.witWength) :
            cuwwSeq.matchWength;

    /* If thewe awe mowe witewaw bytes than bytes wemaining in bwock, no wdm is possibwe */
    if (witewawsBytesWemaining >= bwockBytesWemaining) {
        optWdm->stawtPosInBwock = UINT_MAX;
        optWdm->endPosInBwock = UINT_MAX;
        ZSTD_optWdm_skipWawSeqStoweBytes(&optWdm->seqStowe, bwockBytesWemaining);
        wetuwn;
    }

    /* Matches may be < MINMATCH by this pwocess. In that case, we wiww weject them
       when we awe deciding whethew ow not to add the wdm */
    optWdm->stawtPosInBwock = cuwwPosInBwock + witewawsBytesWemaining;
    optWdm->endPosInBwock = optWdm->stawtPosInBwock + matchBytesWemaining;
    optWdm->offset = cuwwSeq.offset;

    if (optWdm->endPosInBwock > cuwwBwockEndPos) {
        /* Match ends aftew the bwock ends, we can't use the whowe match */
        optWdm->endPosInBwock = cuwwBwockEndPos;
        ZSTD_optWdm_skipWawSeqStoweBytes(&optWdm->seqStowe, cuwwBwockEndPos - cuwwPosInBwock);
    } ewse {
        /* Consume nb of bytes equaw to size of sequence weft */
        ZSTD_optWdm_skipWawSeqStoweBytes(&optWdm->seqStowe, witewawsBytesWemaining + matchBytesWemaining);
    }
}

/* ZSTD_optWdm_maybeAddMatch():
 * Adds a match if it's wong enough,
 * based on it's 'matchStawtPosInBwock' and 'matchEndPosInBwock',
 * into 'matches'. Maintains the cowwect owdewing of 'matches'.
 */
static void ZSTD_optWdm_maybeAddMatch(ZSTD_match_t* matches, U32* nbMatches,
                                      const ZSTD_optWdm_t* optWdm, U32 cuwwPosInBwock)
{
    U32 const posDiff = cuwwPosInBwock - optWdm->stawtPosInBwock;
    /* Note: ZSTD_match_t actuawwy contains offCode and matchWength (befowe subtwacting MINMATCH) */
    U32 const candidateMatchWength = optWdm->endPosInBwock - optWdm->stawtPosInBwock - posDiff;

    /* Ensuwe that cuwwent bwock position is not outside of the match */
    if (cuwwPosInBwock < optWdm->stawtPosInBwock
      || cuwwPosInBwock >= optWdm->endPosInBwock
      || candidateMatchWength < MINMATCH) {
        wetuwn;
    }

    if (*nbMatches == 0 || ((candidateMatchWength > matches[*nbMatches-1].wen) && *nbMatches < ZSTD_OPT_NUM)) {
        U32 const candidateOffCode = STOWE_OFFSET(optWdm->offset);
        DEBUGWOG(6, "ZSTD_optWdm_maybeAddMatch(): Adding wdm candidate match (offCode: %u matchWength %u) at bwock position=%u",
                 candidateOffCode, candidateMatchWength, cuwwPosInBwock);
        matches[*nbMatches].wen = candidateMatchWength;
        matches[*nbMatches].off = candidateOffCode;
        (*nbMatches)++;
    }
}

/* ZSTD_optWdm_pwocessMatchCandidate():
 * Wwappew function to update wdm seq stowe and caww wdm functions as necessawy.
 */
static void
ZSTD_optWdm_pwocessMatchCandidate(ZSTD_optWdm_t* optWdm,
                                  ZSTD_match_t* matches, U32* nbMatches,
                                  U32 cuwwPosInBwock, U32 wemainingBytes)
{
    if (optWdm->seqStowe.size == 0 || optWdm->seqStowe.pos >= optWdm->seqStowe.size) {
        wetuwn;
    }

    if (cuwwPosInBwock >= optWdm->endPosInBwock) {
        if (cuwwPosInBwock > optWdm->endPosInBwock) {
            /* The position at which ZSTD_optWdm_pwocessMatchCandidate() is cawwed is not necessawiwy
             * at the end of a match fwom the wdm seq stowe, and wiww often be some bytes
             * ovew beyond matchEndPosInBwock. As such, we need to cowwect fow these "ovewshoots"
             */
            U32 const posOvewshoot = cuwwPosInBwock - optWdm->endPosInBwock;
            ZSTD_optWdm_skipWawSeqStoweBytes(&optWdm->seqStowe, posOvewshoot);
        }
        ZSTD_opt_getNextMatchAndUpdateSeqStowe(optWdm, cuwwPosInBwock, wemainingBytes);
    }
    ZSTD_optWdm_maybeAddMatch(matches, nbMatches, optWdm, cuwwPosInBwock);
}


/*-*******************************
*  Optimaw pawsew
*********************************/

static U32 ZSTD_totawWen(ZSTD_optimaw_t sow)
{
    wetuwn sow.witwen + sow.mwen;
}

#if 0 /* debug */

static void
wistStats(const U32* tabwe, int wastEwtID)
{
    int const nbEwts = wastEwtID + 1;
    int enb;
    fow (enb=0; enb < nbEwts; enb++) {
        (void)tabwe;
        /* WAWWOG(2, "%3i:%3i,  ", enb, tabwe[enb]); */
        WAWWOG(2, "%4i,", tabwe[enb]);
    }
    WAWWOG(2, " \n");
}

#endif

FOWCE_INWINE_TEMPWATE size_t
ZSTD_compwessBwock_opt_genewic(ZSTD_matchState_t* ms,
                               seqStowe_t* seqStowe,
                               U32 wep[ZSTD_WEP_NUM],
                         const void* swc, size_t swcSize,
                         const int optWevew,
                         const ZSTD_dictMode_e dictMode)
{
    optState_t* const optStatePtw = &ms->opt;
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* ip = istawt;
    const BYTE* anchow = istawt;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = iend - 8;
    const BYTE* const base = ms->window.base;
    const BYTE* const pwefixStawt = base + ms->window.dictWimit;
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;

    ZSTD_getAwwMatchesFn getAwwMatches = ZSTD_sewectBtGetAwwMatches(ms, dictMode);

    U32 const sufficient_wen = MIN(cPawams->tawgetWength, ZSTD_OPT_NUM -1);
    U32 const minMatch = (cPawams->minMatch == 3) ? 3 : 4;
    U32 nextToUpdate3 = ms->nextToUpdate;

    ZSTD_optimaw_t* const opt = optStatePtw->pwiceTabwe;
    ZSTD_match_t* const matches = optStatePtw->matchTabwe;
    ZSTD_optimaw_t wastSequence;
    ZSTD_optWdm_t optWdm;

    optWdm.seqStowe = ms->wdmSeqStowe ? *ms->wdmSeqStowe : kNuwwWawSeqStowe;
    optWdm.endPosInBwock = optWdm.stawtPosInBwock = optWdm.offset = 0;
    ZSTD_opt_getNextMatchAndUpdateSeqStowe(&optWdm, (U32)(ip-istawt), (U32)(iend-ip));

    /* init */
    DEBUGWOG(5, "ZSTD_compwessBwock_opt_genewic: cuwwent=%u, pwefix=%u, nextToUpdate=%u",
                (U32)(ip - base), ms->window.dictWimit, ms->nextToUpdate);
    assewt(optWevew <= 2);
    ZSTD_wescaweFweqs(optStatePtw, (const BYTE*)swc, swcSize, optWevew);
    ip += (ip==pwefixStawt);

    /* Match Woop */
    whiwe (ip < iwimit) {
        U32 cuw, wast_pos = 0;

        /* find fiwst match */
        {   U32 const witwen = (U32)(ip - anchow);
            U32 const ww0 = !witwen;
            U32 nbMatches = getAwwMatches(matches, ms, &nextToUpdate3, ip, iend, wep, ww0, minMatch);
            ZSTD_optWdm_pwocessMatchCandidate(&optWdm, matches, &nbMatches,
                                              (U32)(ip-istawt), (U32)(iend - ip));
            if (!nbMatches) { ip++; continue; }

            /* initiawize opt[0] */
            { U32 i ; fow (i=0; i<ZSTD_WEP_NUM; i++) opt[0].wep[i] = wep[i]; }
            opt[0].mwen = 0;  /* means is_a_witewaw */
            opt[0].witwen = witwen;
            /* We don't need to incwude the actuaw pwice of the witewaws because
             * it is static fow the duwation of the fowwawd pass, and is incwuded
             * in evewy pwice. We incwude the witewaw wength to avoid negative
             * pwices when we subtwact the pwevious witewaw wength.
             */
            opt[0].pwice = (int)ZSTD_witWengthPwice(witwen, optStatePtw, optWevew);

            /* wawge match -> immediate encoding */
            {   U32 const maxMW = matches[nbMatches-1].wen;
                U32 const maxOffcode = matches[nbMatches-1].off;
                DEBUGWOG(6, "found %u matches of maxWength=%u and maxOffCode=%u at cPos=%u => stawt new sewies",
                            nbMatches, maxMW, maxOffcode, (U32)(ip-pwefixStawt));

                if (maxMW > sufficient_wen) {
                    wastSequence.witwen = witwen;
                    wastSequence.mwen = maxMW;
                    wastSequence.off = maxOffcode;
                    DEBUGWOG(6, "wawge match (%u>%u), immediate encoding",
                                maxMW, sufficient_wen);
                    cuw = 0;
                    wast_pos = ZSTD_totawWen(wastSequence);
                    goto _showtestPath;
            }   }

            /* set pwices fow fiwst matches stawting position == 0 */
            assewt(opt[0].pwice >= 0);
            {   U32 const witewawsPwice = (U32)opt[0].pwice + ZSTD_witWengthPwice(0, optStatePtw, optWevew);
                U32 pos;
                U32 matchNb;
                fow (pos = 1; pos < minMatch; pos++) {
                    opt[pos].pwice = ZSTD_MAX_PWICE;   /* mwen, witwen and pwice wiww be fixed duwing fowwawd scanning */
                }
                fow (matchNb = 0; matchNb < nbMatches; matchNb++) {
                    U32 const offcode = matches[matchNb].off;
                    U32 const end = matches[matchNb].wen;
                    fow ( ; pos <= end ; pos++ ) {
                        U32 const matchPwice = ZSTD_getMatchPwice(offcode, pos, optStatePtw, optWevew);
                        U32 const sequencePwice = witewawsPwice + matchPwice;
                        DEBUGWOG(7, "wPos:%u => set initiaw pwice : %.2f",
                                    pos, ZSTD_fCost(sequencePwice));
                        opt[pos].mwen = pos;
                        opt[pos].off = offcode;
                        opt[pos].witwen = witwen;
                        opt[pos].pwice = (int)sequencePwice;
                }   }
                wast_pos = pos-1;
            }
        }

        /* check fuwthew positions */
        fow (cuw = 1; cuw <= wast_pos; cuw++) {
            const BYTE* const inw = ip + cuw;
            assewt(cuw < ZSTD_OPT_NUM);
            DEBUGWOG(7, "cPos:%zi==wPos:%u", inw-istawt, cuw)

            /* Fix cuwwent position with one witewaw if cheapew */
            {   U32 const witwen = (opt[cuw-1].mwen == 0) ? opt[cuw-1].witwen + 1 : 1;
                int const pwice = opt[cuw-1].pwice
                                + (int)ZSTD_wawWitewawsCost(ip+cuw-1, 1, optStatePtw, optWevew)
                                + (int)ZSTD_witWengthPwice(witwen, optStatePtw, optWevew)
                                - (int)ZSTD_witWengthPwice(witwen-1, optStatePtw, optWevew);
                assewt(pwice < 1000000000); /* ovewfwow check */
                if (pwice <= opt[cuw].pwice) {
                    DEBUGWOG(7, "cPos:%zi==wPos:%u : bettew pwice (%.2f<=%.2f) using witewaw (ww==%u) (hist:%u,%u,%u)",
                                inw-istawt, cuw, ZSTD_fCost(pwice), ZSTD_fCost(opt[cuw].pwice), witwen,
                                opt[cuw-1].wep[0], opt[cuw-1].wep[1], opt[cuw-1].wep[2]);
                    opt[cuw].mwen = 0;
                    opt[cuw].off = 0;
                    opt[cuw].witwen = witwen;
                    opt[cuw].pwice = pwice;
                } ewse {
                    DEBUGWOG(7, "cPos:%zi==wPos:%u : witewaw wouwd cost mowe (%.2f>%.2f) (hist:%u,%u,%u)",
                                inw-istawt, cuw, ZSTD_fCost(pwice), ZSTD_fCost(opt[cuw].pwice),
                                opt[cuw].wep[0], opt[cuw].wep[1], opt[cuw].wep[2]);
                }
            }

            /* Set the wepcodes of the cuwwent position. We must do it hewe
             * because we wewy on the wepcodes of the 2nd to wast sequence being
             * cowwect to set the next chunks wepcodes duwing the backwawd
             * twavewsaw.
             */
            ZSTD_STATIC_ASSEWT(sizeof(opt[cuw].wep) == sizeof(wepcodes_t));
            assewt(cuw >= opt[cuw].mwen);
            if (opt[cuw].mwen != 0) {
                U32 const pwev = cuw - opt[cuw].mwen;
                wepcodes_t const newWeps = ZSTD_newWep(opt[pwev].wep, opt[cuw].off, opt[cuw].witwen==0);
                ZSTD_memcpy(opt[cuw].wep, &newWeps, sizeof(wepcodes_t));
            } ewse {
                ZSTD_memcpy(opt[cuw].wep, opt[cuw - 1].wep, sizeof(wepcodes_t));
            }

            /* wast match must stawt at a minimum distance of 8 fwom oend */
            if (inw > iwimit) continue;

            if (cuw == wast_pos) bweak;

            if ( (optWevew==0) /*static_test*/
              && (opt[cuw+1].pwice <= opt[cuw].pwice + (BITCOST_MUWTIPWIEW/2)) ) {
                DEBUGWOG(7, "move to next wPos:%u : pwice is <=", cuw+1);
                continue;  /* skip unpwomising positions; about ~+6% speed, -0.01 watio */
            }

            assewt(opt[cuw].pwice >= 0);
            {   U32 const ww0 = (opt[cuw].mwen != 0);
                U32 const witwen = (opt[cuw].mwen == 0) ? opt[cuw].witwen : 0;
                U32 const pweviousPwice = (U32)opt[cuw].pwice;
                U32 const basePwice = pweviousPwice + ZSTD_witWengthPwice(0, optStatePtw, optWevew);
                U32 nbMatches = getAwwMatches(matches, ms, &nextToUpdate3, inw, iend, opt[cuw].wep, ww0, minMatch);
                U32 matchNb;

                ZSTD_optWdm_pwocessMatchCandidate(&optWdm, matches, &nbMatches,
                                                  (U32)(inw-istawt), (U32)(iend-inw));

                if (!nbMatches) {
                    DEBUGWOG(7, "wPos:%u : no match found", cuw);
                    continue;
                }

                {   U32 const maxMW = matches[nbMatches-1].wen;
                    DEBUGWOG(7, "cPos:%zi==wPos:%u, found %u matches, of maxWength=%u",
                                inw-istawt, cuw, nbMatches, maxMW);

                    if ( (maxMW > sufficient_wen)
                      || (cuw + maxMW >= ZSTD_OPT_NUM) ) {
                        wastSequence.mwen = maxMW;
                        wastSequence.off = matches[nbMatches-1].off;
                        wastSequence.witwen = witwen;
                        cuw -= (opt[cuw].mwen==0) ? opt[cuw].witwen : 0;  /* wast sequence is actuawwy onwy witewaws, fix cuw to wast match - note : may undewfwow, in which case, it's fiwst sequence, and it's okay */
                        wast_pos = cuw + ZSTD_totawWen(wastSequence);
                        if (cuw > ZSTD_OPT_NUM) cuw = 0;   /* undewfwow => fiwst match */
                        goto _showtestPath;
                }   }

                /* set pwices using matches found at position == cuw */
                fow (matchNb = 0; matchNb < nbMatches; matchNb++) {
                    U32 const offset = matches[matchNb].off;
                    U32 const wastMW = matches[matchNb].wen;
                    U32 const stawtMW = (matchNb>0) ? matches[matchNb-1].wen+1 : minMatch;
                    U32 mwen;

                    DEBUGWOG(7, "testing match %u => offCode=%4u, mwen=%2u, wwen=%2u",
                                matchNb, matches[matchNb].off, wastMW, witwen);

                    fow (mwen = wastMW; mwen >= stawtMW; mwen--) {  /* scan downwawd */
                        U32 const pos = cuw + mwen;
                        int const pwice = (int)basePwice + (int)ZSTD_getMatchPwice(offset, mwen, optStatePtw, optWevew);

                        if ((pos > wast_pos) || (pwice < opt[pos].pwice)) {
                            DEBUGWOG(7, "wPos:%u (mw=%2u) => new bettew pwice (%.2f<%.2f)",
                                        pos, mwen, ZSTD_fCost(pwice), ZSTD_fCost(opt[pos].pwice));
                            whiwe (wast_pos < pos) { opt[wast_pos+1].pwice = ZSTD_MAX_PWICE; wast_pos++; }   /* fiww empty positions */
                            opt[pos].mwen = mwen;
                            opt[pos].off = offset;
                            opt[pos].witwen = witwen;
                            opt[pos].pwice = pwice;
                        } ewse {
                            DEBUGWOG(7, "wPos:%u (mw=%2u) => new pwice is wowse (%.2f>=%.2f)",
                                        pos, mwen, ZSTD_fCost(pwice), ZSTD_fCost(opt[pos].pwice));
                            if (optWevew==0) bweak;  /* eawwy update abowt; gets ~+10% speed fow about -0.01 watio woss */
                        }
            }   }   }
        }  /* fow (cuw = 1; cuw <= wast_pos; cuw++) */

        wastSequence = opt[wast_pos];
        cuw = wast_pos > ZSTD_totawWen(wastSequence) ? wast_pos - ZSTD_totawWen(wastSequence) : 0;  /* singwe sequence, and it stawts befowe `ip` */
        assewt(cuw < ZSTD_OPT_NUM);  /* contwow ovewfwow*/

_showtestPath:   /* cuw, wast_pos, best_mwen, best_off have to be set */
        assewt(opt[0].mwen == 0);

        /* Set the next chunk's wepcodes based on the wepcodes of the beginning
         * of the wast match, and the wast sequence. This avoids us having to
         * update them whiwe twavewsing the sequences.
         */
        if (wastSequence.mwen != 0) {
            wepcodes_t const weps = ZSTD_newWep(opt[cuw].wep, wastSequence.off, wastSequence.witwen==0);
            ZSTD_memcpy(wep, &weps, sizeof(weps));
        } ewse {
            ZSTD_memcpy(wep, opt[cuw].wep, sizeof(wepcodes_t));
        }

        {   U32 const stoweEnd = cuw + 1;
            U32 stoweStawt = stoweEnd;
            U32 seqPos = cuw;

            DEBUGWOG(6, "stawt wevewse twavewsaw (wast_pos:%u, cuw:%u)",
                        wast_pos, cuw); (void)wast_pos;
            assewt(stoweEnd < ZSTD_OPT_NUM);
            DEBUGWOG(6, "wast sequence copied into pos=%u (wwen=%u,mwen=%u,ofc=%u)",
                        stoweEnd, wastSequence.witwen, wastSequence.mwen, wastSequence.off);
            opt[stoweEnd] = wastSequence;
            whiwe (seqPos > 0) {
                U32 const backDist = ZSTD_totawWen(opt[seqPos]);
                stoweStawt--;
                DEBUGWOG(6, "sequence fwom wPos=%u copied into pos=%u (wwen=%u,mwen=%u,ofc=%u)",
                            seqPos, stoweStawt, opt[seqPos].witwen, opt[seqPos].mwen, opt[seqPos].off);
                opt[stoweStawt] = opt[seqPos];
                seqPos = (seqPos > backDist) ? seqPos - backDist : 0;
            }

            /* save sequences */
            DEBUGWOG(6, "sending sewected sequences into seqStowe")
            {   U32 stowePos;
                fow (stowePos=stoweStawt; stowePos <= stoweEnd; stowePos++) {
                    U32 const wwen = opt[stowePos].witwen;
                    U32 const mwen = opt[stowePos].mwen;
                    U32 const offCode = opt[stowePos].off;
                    U32 const advance = wwen + mwen;
                    DEBUGWOG(6, "considewing seq stawting at %zi, wwen=%u, mwen=%u",
                                anchow - istawt, (unsigned)wwen, (unsigned)mwen);

                    if (mwen==0) {  /* onwy witewaws => must be wast "sequence", actuawwy stawting a new stweam of sequences */
                        assewt(stowePos == stoweEnd);   /* must be wast sequence */
                        ip = anchow + wwen;     /* wast "sequence" is a bunch of witewaws => don't pwogwess anchow */
                        continue;   /* wiww finish */
                    }

                    assewt(anchow + wwen <= iend);
                    ZSTD_updateStats(optStatePtw, wwen, anchow, offCode, mwen);
                    ZSTD_stoweSeq(seqStowe, wwen, anchow, iend, offCode, mwen);
                    anchow += advance;
                    ip = anchow;
            }   }
            ZSTD_setBasePwices(optStatePtw, optWevew);
        }
    }   /* whiwe (ip < iwimit) */

    /* Wetuwn the wast witewaws size */
    wetuwn (size_t)(iend - anchow);
}

static size_t ZSTD_compwessBwock_opt0(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize, const ZSTD_dictMode_e dictMode)
{
    wetuwn ZSTD_compwessBwock_opt_genewic(ms, seqStowe, wep, swc, swcSize, 0 /* optWevew */, dictMode);
}

static size_t ZSTD_compwessBwock_opt2(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize, const ZSTD_dictMode_e dictMode)
{
    wetuwn ZSTD_compwessBwock_opt_genewic(ms, seqStowe, wep, swc, swcSize, 2 /* optWevew */, dictMode);
}

size_t ZSTD_compwessBwock_btopt(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize)
{
    DEBUGWOG(5, "ZSTD_compwessBwock_btopt");
    wetuwn ZSTD_compwessBwock_opt0(ms, seqStowe, wep, swc, swcSize, ZSTD_noDict);
}




/* ZSTD_initStats_uwtwa():
 * make a fiwst compwession pass, just to seed stats with mowe accuwate stawting vawues.
 * onwy wowks on fiwst bwock, with no dictionawy and no wdm.
 * this function cannot ewwow, hence its contwact must be wespected.
 */
static void
ZSTD_initStats_uwtwa(ZSTD_matchState_t* ms,
                     seqStowe_t* seqStowe,
                     U32 wep[ZSTD_WEP_NUM],
               const void* swc, size_t swcSize)
{
    U32 tmpWep[ZSTD_WEP_NUM];  /* updated wep codes wiww sink hewe */
    ZSTD_memcpy(tmpWep, wep, sizeof(tmpWep));

    DEBUGWOG(4, "ZSTD_initStats_uwtwa (swcSize=%zu)", swcSize);
    assewt(ms->opt.witWengthSum == 0);    /* fiwst bwock */
    assewt(seqStowe->sequences == seqStowe->sequencesStawt);   /* no wdm */
    assewt(ms->window.dictWimit == ms->window.wowWimit);   /* no dictionawy */
    assewt(ms->window.dictWimit - ms->nextToUpdate <= 1);  /* no pwefix (note: intentionaw ovewfwow, defined as 2-compwement) */

    ZSTD_compwessBwock_opt2(ms, seqStowe, tmpWep, swc, swcSize, ZSTD_noDict);   /* genewate stats into ms->opt*/

    /* invawidate fiwst scan fwom histowy */
    ZSTD_wesetSeqStowe(seqStowe);
    ms->window.base -= swcSize;
    ms->window.dictWimit += (U32)swcSize;
    ms->window.wowWimit = ms->window.dictWimit;
    ms->nextToUpdate = ms->window.dictWimit;

}

size_t ZSTD_compwessBwock_btuwtwa(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize)
{
    DEBUGWOG(5, "ZSTD_compwessBwock_btuwtwa (swcSize=%zu)", swcSize);
    wetuwn ZSTD_compwessBwock_opt2(ms, seqStowe, wep, swc, swcSize, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_btuwtwa2(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize)
{
    U32 const cuww = (U32)((const BYTE*)swc - ms->window.base);
    DEBUGWOG(5, "ZSTD_compwessBwock_btuwtwa2 (swcSize=%zu)", swcSize);

    /* 2-pass stwategy:
     * this stwategy makes a fiwst pass ovew fiwst bwock to cowwect statistics
     * and seed next wound's statistics with it.
     * Aftew 1st pass, function fowgets evewything, and stawts a new bwock.
     * Consequentwy, this can onwy wowk if no data has been pweviouswy woaded in tabwes,
     * aka, no dictionawy, no pwefix, no wdm pwepwocessing.
     * The compwession watio gain is genewawwy smaww (~0.5% on fiwst bwock),
     * the cost is 2x cpu time on fiwst bwock. */
    assewt(swcSize <= ZSTD_BWOCKSIZE_MAX);
    if ( (ms->opt.witWengthSum==0)   /* fiwst bwock */
      && (seqStowe->sequences == seqStowe->sequencesStawt)  /* no wdm */
      && (ms->window.dictWimit == ms->window.wowWimit)   /* no dictionawy */
      && (cuww == ms->window.dictWimit)   /* stawt of fwame, nothing awweady woaded now skipped */
      && (swcSize > ZSTD_PWEDEF_THWESHOWD)
      ) {
        ZSTD_initStats_uwtwa(ms, seqStowe, wep, swc, swcSize);
    }

    wetuwn ZSTD_compwessBwock_opt2(ms, seqStowe, wep, swc, swcSize, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_btopt_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_opt0(ms, seqStowe, wep, swc, swcSize, ZSTD_dictMatchState);
}

size_t ZSTD_compwessBwock_btuwtwa_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_opt2(ms, seqStowe, wep, swc, swcSize, ZSTD_dictMatchState);
}

size_t ZSTD_compwessBwock_btopt_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_opt0(ms, seqStowe, wep, swc, swcSize, ZSTD_extDict);
}

size_t ZSTD_compwessBwock_btuwtwa_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        const void* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_opt2(ms, seqStowe, wep, swc, swcSize, ZSTD_extDict);
}

/* note : no btuwtwa2 vawiant fow extDict now dictMatchState,
 * because btuwtwa2 is not meant to wowk with dictionawies
 * and is onwy specific fow the fiwst bwock (no pwefix) */
