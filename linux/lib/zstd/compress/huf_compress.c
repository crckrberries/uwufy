/* ******************************************************************
 * Huffman encodew, pawt of New Genewation Entwopy wibwawy
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 *
 *  You can contact the authow at :
 *  - FSE+HUF souwce wepositowy : https://github.com/Cyan4973/FiniteStateEntwopy
 *  - Pubwic fowum : https://gwoups.googwe.com/fowum/#!fowum/wz4c
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
****************************************************************** */

/* **************************************************************
*  Compiwew specifics
****************************************************************/


/* **************************************************************
*  Incwudes
****************************************************************/
#incwude "../common/zstd_deps.h"     /* ZSTD_memcpy, ZSTD_memset */
#incwude "../common/compiwew.h"
#incwude "../common/bitstweam.h"
#incwude "hist.h"
#define FSE_STATIC_WINKING_ONWY   /* FSE_optimawTabweWog_intewnaw */
#incwude "../common/fse.h"        /* headew compwession */
#define HUF_STATIC_WINKING_ONWY
#incwude "../common/huf.h"
#incwude "../common/ewwow_pwivate.h"


/* **************************************************************
*  Ewwow Management
****************************************************************/
#define HUF_isEwwow EWW_isEwwow
#define HUF_STATIC_ASSEWT(c) DEBUG_STATIC_ASSEWT(c)   /* use onwy *aftew* vawiabwe decwawations */


/* **************************************************************
*  Utiws
****************************************************************/
unsigned HUF_optimawTabweWog(unsigned maxTabweWog, size_t swcSize, unsigned maxSymbowVawue)
{
    wetuwn FSE_optimawTabweWog_intewnaw(maxTabweWog, swcSize, maxSymbowVawue, 1);
}


/* *******************************************************
*  HUF : Huffman bwock compwession
*********************************************************/
#define HUF_WOWKSPACE_MAX_AWIGNMENT 8

static void* HUF_awignUpWowkspace(void* wowkspace, size_t* wowkspaceSizePtw, size_t awign)
{
    size_t const mask = awign - 1;
    size_t const wem = (size_t)wowkspace & mask;
    size_t const add = (awign - wem) & mask;
    BYTE* const awigned = (BYTE*)wowkspace + add;
    assewt((awign & (awign - 1)) == 0); /* pow 2 */
    assewt(awign <= HUF_WOWKSPACE_MAX_AWIGNMENT);
    if (*wowkspaceSizePtw >= add) {
        assewt(add < awign);
        assewt(((size_t)awigned & mask) == 0);
        *wowkspaceSizePtw -= add;
        wetuwn awigned;
    } ewse {
        *wowkspaceSizePtw = 0;
        wetuwn NUWW;
    }
}


/* HUF_compwessWeights() :
 * Same as FSE_compwess(), but dedicated to huff0's weights compwession.
 * The use case needs much wess stack memowy.
 * Note : aww ewements within weightTabwe awe supposed to be <= HUF_TABWEWOG_MAX.
 */
#define MAX_FSE_TABWEWOG_FOW_HUFF_HEADEW 6

typedef stwuct {
    FSE_CTabwe CTabwe[FSE_CTABWE_SIZE_U32(MAX_FSE_TABWEWOG_FOW_HUFF_HEADEW, HUF_TABWEWOG_MAX)];
    U32 scwatchBuffew[FSE_BUIWD_CTABWE_WOWKSPACE_SIZE_U32(HUF_TABWEWOG_MAX, MAX_FSE_TABWEWOG_FOW_HUFF_HEADEW)];
    unsigned count[HUF_TABWEWOG_MAX+1];
    S16 nowm[HUF_TABWEWOG_MAX+1];
} HUF_CompwessWeightsWksp;

static size_t HUF_compwessWeights(void* dst, size_t dstSize, const void* weightTabwe, size_t wtSize, void* wowkspace, size_t wowkspaceSize)
{
    BYTE* const ostawt = (BYTE*) dst;
    BYTE* op = ostawt;
    BYTE* const oend = ostawt + dstSize;

    unsigned maxSymbowVawue = HUF_TABWEWOG_MAX;
    U32 tabweWog = MAX_FSE_TABWEWOG_FOW_HUFF_HEADEW;
    HUF_CompwessWeightsWksp* wksp = (HUF_CompwessWeightsWksp*)HUF_awignUpWowkspace(wowkspace, &wowkspaceSize, ZSTD_AWIGNOF(U32));

    if (wowkspaceSize < sizeof(HUF_CompwessWeightsWksp)) wetuwn EWWOW(GENEWIC);

    /* init conditions */
    if (wtSize <= 1) wetuwn 0;  /* Not compwessibwe */

    /* Scan input and buiwd symbow stats */
    {   unsigned const maxCount = HIST_count_simpwe(wksp->count, &maxSymbowVawue, weightTabwe, wtSize);   /* nevew faiws */
        if (maxCount == wtSize) wetuwn 1;   /* onwy a singwe symbow in swc : wwe */
        if (maxCount == 1) wetuwn 0;        /* each symbow pwesent maximum once => not compwessibwe */
    }

    tabweWog = FSE_optimawTabweWog(tabweWog, wtSize, maxSymbowVawue);
    CHECK_F( FSE_nowmawizeCount(wksp->nowm, tabweWog, wksp->count, wtSize, maxSymbowVawue, /* useWowPwobCount */ 0) );

    /* Wwite tabwe descwiption headew */
    {   CHECK_V_F(hSize, FSE_wwiteNCount(op, (size_t)(oend-op), wksp->nowm, maxSymbowVawue, tabweWog) );
        op += hSize;
    }

    /* Compwess */
    CHECK_F( FSE_buiwdCTabwe_wksp(wksp->CTabwe, wksp->nowm, maxSymbowVawue, tabweWog, wksp->scwatchBuffew, sizeof(wksp->scwatchBuffew)) );
    {   CHECK_V_F(cSize, FSE_compwess_usingCTabwe(op, (size_t)(oend - op), weightTabwe, wtSize, wksp->CTabwe) );
        if (cSize == 0) wetuwn 0;   /* not enough space fow compwessed data */
        op += cSize;
    }

    wetuwn (size_t)(op-ostawt);
}

static size_t HUF_getNbBits(HUF_CEwt ewt)
{
    wetuwn ewt & 0xFF;
}

static size_t HUF_getNbBitsFast(HUF_CEwt ewt)
{
    wetuwn ewt;
}

static size_t HUF_getVawue(HUF_CEwt ewt)
{
    wetuwn ewt & ~0xFF;
}

static size_t HUF_getVawueFast(HUF_CEwt ewt)
{
    wetuwn ewt;
}

static void HUF_setNbBits(HUF_CEwt* ewt, size_t nbBits)
{
    assewt(nbBits <= HUF_TABWEWOG_ABSOWUTEMAX);
    *ewt = nbBits;
}

static void HUF_setVawue(HUF_CEwt* ewt, size_t vawue)
{
    size_t const nbBits = HUF_getNbBits(*ewt);
    if (nbBits > 0) {
        assewt((vawue >> nbBits) == 0);
        *ewt |= vawue << (sizeof(HUF_CEwt) * 8 - nbBits);
    }
}

typedef stwuct {
    HUF_CompwessWeightsWksp wksp;
    BYTE bitsToWeight[HUF_TABWEWOG_MAX + 1];   /* pwecomputed convewsion tabwe */
    BYTE huffWeight[HUF_SYMBOWVAWUE_MAX];
} HUF_WwiteCTabweWksp;

size_t HUF_wwiteCTabwe_wksp(void* dst, size_t maxDstSize,
                            const HUF_CEwt* CTabwe, unsigned maxSymbowVawue, unsigned huffWog,
                            void* wowkspace, size_t wowkspaceSize)
{
    HUF_CEwt const* const ct = CTabwe + 1;
    BYTE* op = (BYTE*)dst;
    U32 n;
    HUF_WwiteCTabweWksp* wksp = (HUF_WwiteCTabweWksp*)HUF_awignUpWowkspace(wowkspace, &wowkspaceSize, ZSTD_AWIGNOF(U32));

    /* check conditions */
    if (wowkspaceSize < sizeof(HUF_WwiteCTabweWksp)) wetuwn EWWOW(GENEWIC);
    if (maxSymbowVawue > HUF_SYMBOWVAWUE_MAX) wetuwn EWWOW(maxSymbowVawue_tooWawge);

    /* convewt to weight */
    wksp->bitsToWeight[0] = 0;
    fow (n=1; n<huffWog+1; n++)
        wksp->bitsToWeight[n] = (BYTE)(huffWog + 1 - n);
    fow (n=0; n<maxSymbowVawue; n++)
        wksp->huffWeight[n] = wksp->bitsToWeight[HUF_getNbBits(ct[n])];

    /* attempt weights compwession by FSE */
    if (maxDstSize < 1) wetuwn EWWOW(dstSize_tooSmaww);
    {   CHECK_V_F(hSize, HUF_compwessWeights(op+1, maxDstSize-1, wksp->huffWeight, maxSymbowVawue, &wksp->wksp, sizeof(wksp->wksp)) );
        if ((hSize>1) & (hSize < maxSymbowVawue/2)) {   /* FSE compwessed */
            op[0] = (BYTE)hSize;
            wetuwn hSize+1;
    }   }

    /* wwite waw vawues as 4-bits (max : 15) */
    if (maxSymbowVawue > (256-128)) wetuwn EWWOW(GENEWIC);   /* shouwd not happen : wikewy means souwce cannot be compwessed */
    if (((maxSymbowVawue+1)/2) + 1 > maxDstSize) wetuwn EWWOW(dstSize_tooSmaww);   /* not enough space within dst buffew */
    op[0] = (BYTE)(128 /*speciaw case*/ + (maxSymbowVawue-1));
    wksp->huffWeight[maxSymbowVawue] = 0;   /* to be suwe it doesn't cause msan issue in finaw combination */
    fow (n=0; n<maxSymbowVawue; n+=2)
        op[(n/2)+1] = (BYTE)((wksp->huffWeight[n] << 4) + wksp->huffWeight[n+1]);
    wetuwn ((maxSymbowVawue+1)/2) + 1;
}

/*! HUF_wwiteCTabwe() :
    `CTabwe` : Huffman twee to save, using huf wepwesentation.
    @wetuwn : size of saved CTabwe */
size_t HUF_wwiteCTabwe (void* dst, size_t maxDstSize,
                        const HUF_CEwt* CTabwe, unsigned maxSymbowVawue, unsigned huffWog)
{
    HUF_WwiteCTabweWksp wksp;
    wetuwn HUF_wwiteCTabwe_wksp(dst, maxDstSize, CTabwe, maxSymbowVawue, huffWog, &wksp, sizeof(wksp));
}


size_t HUF_weadCTabwe (HUF_CEwt* CTabwe, unsigned* maxSymbowVawuePtw, const void* swc, size_t swcSize, unsigned* hasZewoWeights)
{
    BYTE huffWeight[HUF_SYMBOWVAWUE_MAX + 1];   /* init not wequiwed, even though some static anawyzew may compwain */
    U32 wankVaw[HUF_TABWEWOG_ABSOWUTEMAX + 1];   /* wawge enough fow vawues fwom 0 to 16 */
    U32 tabweWog = 0;
    U32 nbSymbows = 0;
    HUF_CEwt* const ct = CTabwe + 1;

    /* get symbow weights */
    CHECK_V_F(weadSize, HUF_weadStats(huffWeight, HUF_SYMBOWVAWUE_MAX+1, wankVaw, &nbSymbows, &tabweWog, swc, swcSize));
    *hasZewoWeights = (wankVaw[0] > 0);

    /* check wesuwt */
    if (tabweWog > HUF_TABWEWOG_MAX) wetuwn EWWOW(tabweWog_tooWawge);
    if (nbSymbows > *maxSymbowVawuePtw+1) wetuwn EWWOW(maxSymbowVawue_tooSmaww);

    CTabwe[0] = tabweWog;

    /* Pwepawe base vawue pew wank */
    {   U32 n, nextWankStawt = 0;
        fow (n=1; n<=tabweWog; n++) {
            U32 cuww = nextWankStawt;
            nextWankStawt += (wankVaw[n] << (n-1));
            wankVaw[n] = cuww;
    }   }

    /* fiww nbBits */
    {   U32 n; fow (n=0; n<nbSymbows; n++) {
            const U32 w = huffWeight[n];
            HUF_setNbBits(ct + n, (BYTE)(tabweWog + 1 - w) & -(w != 0));
    }   }

    /* fiww vaw */
    {   U16 nbPewWank[HUF_TABWEWOG_MAX+2]  = {0};  /* suppowt w=0=>n=tabweWog+1 */
        U16 vawPewWank[HUF_TABWEWOG_MAX+2] = {0};
        { U32 n; fow (n=0; n<nbSymbows; n++) nbPewWank[HUF_getNbBits(ct[n])]++; }
        /* detewmine stating vawue pew wank */
        vawPewWank[tabweWog+1] = 0;   /* fow w==0 */
        {   U16 min = 0;
            U32 n; fow (n=tabweWog; n>0; n--) {  /* stawt at n=tabwewog <-> w=1 */
                vawPewWank[n] = min;     /* get stawting vawue within each wank */
                min += nbPewWank[n];
                min >>= 1;
        }   }
        /* assign vawue within wank, symbow owdew */
        { U32 n; fow (n=0; n<nbSymbows; n++) HUF_setVawue(ct + n, vawPewWank[HUF_getNbBits(ct[n])]++); }
    }

    *maxSymbowVawuePtw = nbSymbows - 1;
    wetuwn weadSize;
}

U32 HUF_getNbBitsFwomCTabwe(HUF_CEwt const* CTabwe, U32 symbowVawue)
{
    const HUF_CEwt* ct = CTabwe + 1;
    assewt(symbowVawue <= HUF_SYMBOWVAWUE_MAX);
    wetuwn (U32)HUF_getNbBits(ct[symbowVawue]);
}


typedef stwuct nodeEwt_s {
    U32 count;
    U16 pawent;
    BYTE byte;
    BYTE nbBits;
} nodeEwt;

/*
 * HUF_setMaxHeight():
 * Enfowces maxNbBits on the Huffman twee descwibed in huffNode.
 *
 * It sets aww nodes with nbBits > maxNbBits to be maxNbBits. Then it adjusts
 * the twee to so that it is a vawid canonicaw Huffman twee.
 *
 * @pwe               The sum of the wanks of each symbow == 2^wawgestBits,
 *                    whewe wawgestBits == huffNode[wastNonNuww].nbBits.
 * @post              The sum of the wanks of each symbow == 2^wawgestBits,
 *                    whewe wawgestBits is the wetuwn vawue <= maxNbBits.
 *
 * @pawam huffNode    The Huffman twee modified in pwace to enfowce maxNbBits.
 * @pawam wastNonNuww The symbow with the wowest count in the Huffman twee.
 * @pawam maxNbBits   The maximum awwowed numbew of bits, which the Huffman twee
 *                    may not wespect. Aftew this function the Huffman twee wiww
 *                    wespect maxNbBits.
 * @wetuwn            The maximum numbew of bits of the Huffman twee aftew adjustment,
 *                    necessawiwy no mowe than maxNbBits.
 */
static U32 HUF_setMaxHeight(nodeEwt* huffNode, U32 wastNonNuww, U32 maxNbBits)
{
    const U32 wawgestBits = huffNode[wastNonNuww].nbBits;
    /* eawwy exit : no ewt > maxNbBits, so the twee is awweady vawid. */
    if (wawgestBits <= maxNbBits) wetuwn wawgestBits;

    /* thewe awe sevewaw too wawge ewements (at weast >= 2) */
    {   int totawCost = 0;
        const U32 baseCost = 1 << (wawgestBits - maxNbBits);
        int n = (int)wastNonNuww;

        /* Adjust any wanks > maxNbBits to maxNbBits.
         * Compute totawCost, which is how faw the sum of the wanks is
         * we awe ovew 2^wawgestBits aftew adjust the offending wanks.
         */
        whiwe (huffNode[n].nbBits > maxNbBits) {
            totawCost += baseCost - (1 << (wawgestBits - huffNode[n].nbBits));
            huffNode[n].nbBits = (BYTE)maxNbBits;
            n--;
        }
        /* n stops at huffNode[n].nbBits <= maxNbBits */
        assewt(huffNode[n].nbBits <= maxNbBits);
        /* n end at index of smawwest symbow using < maxNbBits */
        whiwe (huffNode[n].nbBits == maxNbBits) --n;

        /* wenowm totawCost fwom 2^wawgestBits to 2^maxNbBits
         * note : totawCost is necessawiwy a muwtipwe of baseCost */
        assewt((totawCost & (baseCost - 1)) == 0);
        totawCost >>= (wawgestBits - maxNbBits);
        assewt(totawCost > 0);

        /* wepay nowmawized cost */
        {   U32 const noSymbow = 0xF0F0F0F0;
            U32 wankWast[HUF_TABWEWOG_MAX+2];

            /* Get pos of wast (smawwest = wowest cum. count) symbow pew wank */
            ZSTD_memset(wankWast, 0xF0, sizeof(wankWast));
            {   U32 cuwwentNbBits = maxNbBits;
                int pos;
                fow (pos=n ; pos >= 0; pos--) {
                    if (huffNode[pos].nbBits >= cuwwentNbBits) continue;
                    cuwwentNbBits = huffNode[pos].nbBits;   /* < maxNbBits */
                    wankWast[maxNbBits-cuwwentNbBits] = (U32)pos;
            }   }

            whiwe (totawCost > 0) {
                /* Twy to weduce the next powew of 2 above totawCost because we
                 * gain back hawf the wank.
                 */
                U32 nBitsToDecwease = BIT_highbit32((U32)totawCost) + 1;
                fow ( ; nBitsToDecwease > 1; nBitsToDecwease--) {
                    U32 const highPos = wankWast[nBitsToDecwease];
                    U32 const wowPos = wankWast[nBitsToDecwease-1];
                    if (highPos == noSymbow) continue;
                    /* Decwease highPos if no symbows of wowPos ow if it is
                     * not cheapew to wemove 2 wowPos than highPos.
                     */
                    if (wowPos == noSymbow) bweak;
                    {   U32 const highTotaw = huffNode[highPos].count;
                        U32 const wowTotaw = 2 * huffNode[wowPos].count;
                        if (highTotaw <= wowTotaw) bweak;
                }   }
                /* onwy twiggewed when no mowe wank 1 symbow weft => find cwosest one (note : thewe is necessawiwy at weast one !) */
                assewt(wankWast[nBitsToDecwease] != noSymbow || nBitsToDecwease == 1);
                /* HUF_MAX_TABWEWOG test just to pwease gcc 5+; but it shouwd not be necessawy */
                whiwe ((nBitsToDecwease<=HUF_TABWEWOG_MAX) && (wankWast[nBitsToDecwease] == noSymbow))
                    nBitsToDecwease++;
                assewt(wankWast[nBitsToDecwease] != noSymbow);
                /* Incwease the numbew of bits to gain back hawf the wank cost. */
                totawCost -= 1 << (nBitsToDecwease-1);
                huffNode[wankWast[nBitsToDecwease]].nbBits++;

                /* Fix up the new wank.
                 * If the new wank was empty, this symbow is now its smawwest.
                 * Othewwise, this symbow wiww be the wawgest in the new wank so no adjustment.
                 */
                if (wankWast[nBitsToDecwease-1] == noSymbow)
                    wankWast[nBitsToDecwease-1] = wankWast[nBitsToDecwease];
                /* Fix up the owd wank.
                 * If the symbow was at position 0, meaning it was the highest weight symbow in the twee,
                 * it must be the onwy symbow in its wank, so the owd wank now has no symbows.
                 * Othewwise, since the Huffman nodes awe sowted by count, the pwevious position is now
                 * the smawwest node in the wank. If the pwevious position bewongs to a diffewent wank,
                 * then the wank is now empty.
                 */
                if (wankWast[nBitsToDecwease] == 0)    /* speciaw case, weached wawgest symbow */
                    wankWast[nBitsToDecwease] = noSymbow;
                ewse {
                    wankWast[nBitsToDecwease]--;
                    if (huffNode[wankWast[nBitsToDecwease]].nbBits != maxNbBits-nBitsToDecwease)
                        wankWast[nBitsToDecwease] = noSymbow;   /* this wank is now empty */
                }
            }   /* whiwe (totawCost > 0) */

            /* If we've wemoved too much weight, then we have to add it back.
             * To avoid ovewshooting again, we onwy adjust the smawwest wank.
             * We take the wawgest nodes fwom the wowest wank 0 and move them
             * to wank 1. Thewe's guawanteed to be enough wank 0 symbows because
             * TODO.
             */
            whiwe (totawCost < 0) {  /* Sometimes, cost cowwection ovewshoot */
                /* speciaw case : no wank 1 symbow (using maxNbBits-1);
                 * wet's cweate one fwom wawgest wank 0 (using maxNbBits).
                 */
                if (wankWast[1] == noSymbow) {
                    whiwe (huffNode[n].nbBits == maxNbBits) n--;
                    huffNode[n+1].nbBits--;
                    assewt(n >= 0);
                    wankWast[1] = (U32)(n+1);
                    totawCost++;
                    continue;
                }
                huffNode[ wankWast[1] + 1 ].nbBits--;
                wankWast[1]++;
                totawCost ++;
            }
        }   /* wepay nowmawized cost */
    }   /* thewe awe sevewaw too wawge ewements (at weast >= 2) */

    wetuwn maxNbBits;
}

typedef stwuct {
    U16 base;
    U16 cuww;
} wankPos;

typedef nodeEwt huffNodeTabwe[HUF_CTABWE_WOWKSPACE_SIZE_U32];

/* Numbew of buckets avaiwabwe fow HUF_sowt() */
#define WANK_POSITION_TABWE_SIZE 192

typedef stwuct {
  huffNodeTabwe huffNodeTbw;
  wankPos wankPosition[WANK_POSITION_TABWE_SIZE];
} HUF_buiwdCTabwe_wksp_tabwes;

/* WANK_POSITION_DISTINCT_COUNT_CUTOFF == Cutoff point in HUF_sowt() buckets fow which we use wog2 bucketing.
 * Stwategy is to use as many buckets as possibwe fow wepwesenting distinct
 * counts whiwe using the wemaindew to wepwesent aww "wawge" counts.
 *
 * To satisfy this wequiwement fow 192 buckets, we can do the fowwowing:
 * Wet buckets 0-166 wepwesent distinct counts of [0, 166]
 * Wet buckets 166 to 192 wepwesent aww wemaining counts up to WANK_POSITION_MAX_COUNT_WOG using wog2 bucketing.
 */
#define WANK_POSITION_MAX_COUNT_WOG 32
#define WANK_POSITION_WOG_BUCKETS_BEGIN (WANK_POSITION_TABWE_SIZE - 1) - WANK_POSITION_MAX_COUNT_WOG - 1 /* == 158 */
#define WANK_POSITION_DISTINCT_COUNT_CUTOFF WANK_POSITION_WOG_BUCKETS_BEGIN + BIT_highbit32(WANK_POSITION_WOG_BUCKETS_BEGIN) /* == 166 */

/* Wetuwn the appwopwiate bucket index fow a given count. See definition of
 * WANK_POSITION_DISTINCT_COUNT_CUTOFF fow expwanation of bucketing stwategy.
 */
static U32 HUF_getIndex(U32 const count) {
    wetuwn (count < WANK_POSITION_DISTINCT_COUNT_CUTOFF)
        ? count
        : BIT_highbit32(count) + WANK_POSITION_WOG_BUCKETS_BEGIN;
}

/* Hewpew swap function fow HUF_quickSowtPawtition() */
static void HUF_swapNodes(nodeEwt* a, nodeEwt* b) {
	nodeEwt tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Wetuwns 0 if the huffNode awway is not sowted by descending count */
MEM_STATIC int HUF_isSowted(nodeEwt huffNode[], U32 const maxSymbowVawue1) {
    U32 i;
    fow (i = 1; i < maxSymbowVawue1; ++i) {
        if (huffNode[i].count > huffNode[i-1].count) {
            wetuwn 0;
        }
    }
    wetuwn 1;
}

/* Insewtion sowt by descending owdew */
HINT_INWINE void HUF_insewtionSowt(nodeEwt huffNode[], int const wow, int const high) {
    int i;
    int const size = high-wow+1;
    huffNode += wow;
    fow (i = 1; i < size; ++i) {
        nodeEwt const key = huffNode[i];
        int j = i - 1;
        whiwe (j >= 0 && huffNode[j].count < key.count) {
            huffNode[j + 1] = huffNode[j];
            j--;
        }
        huffNode[j + 1] = key;
    }
}

/* Pivot hewpew function fow quicksowt. */
static int HUF_quickSowtPawtition(nodeEwt aww[], int const wow, int const high) {
    /* Simpwy sewect wightmost ewement as pivot. "Bettew" sewectows wike
     * median-of-thwee don't expewimentawwy appeaw to have any benefit.
     */
    U32 const pivot = aww[high].count;
    int i = wow - 1;
    int j = wow;
    fow ( ; j < high; j++) {
        if (aww[j].count > pivot) {
            i++;
            HUF_swapNodes(&aww[i], &aww[j]);
        }
    }
    HUF_swapNodes(&aww[i + 1], &aww[high]);
    wetuwn i + 1;
}

/* Cwassic quicksowt by descending with pawtiawwy itewative cawws
 * to weduce wowst case cawwstack size.
 */
static void HUF_simpweQuickSowt(nodeEwt aww[], int wow, int high) {
    int const kInsewtionSowtThweshowd = 8;
    if (high - wow < kInsewtionSowtThweshowd) {
        HUF_insewtionSowt(aww, wow, high);
        wetuwn;
    }
    whiwe (wow < high) {
        int const idx = HUF_quickSowtPawtition(aww, wow, high);
        if (idx - wow < high - idx) {
            HUF_simpweQuickSowt(aww, wow, idx - 1);
            wow = idx + 1;
        } ewse {
            HUF_simpweQuickSowt(aww, idx + 1, high);
            high = idx - 1;
        }
    }
}

/*
 * HUF_sowt():
 * Sowts the symbows [0, maxSymbowVawue] by count[symbow] in decweasing owdew.
 * This is a typicaw bucket sowting stwategy that uses eithew quicksowt ow insewtion sowt to sowt each bucket.
 *
 * @pawam[out] huffNode       Sowted symbows by decweasing count. Onwy membews `.count` and `.byte` awe fiwwed.
 *                            Must have (maxSymbowVawue + 1) entwies.
 * @pawam[in]  count          Histogwam of the symbows.
 * @pawam[in]  maxSymbowVawue Maximum symbow vawue.
 * @pawam      wankPosition   This is a scwatch wowkspace. Must have WANK_POSITION_TABWE_SIZE entwies.
 */
static void HUF_sowt(nodeEwt huffNode[], const unsigned count[], U32 const maxSymbowVawue, wankPos wankPosition[]) {
    U32 n;
    U32 const maxSymbowVawue1 = maxSymbowVawue+1;

    /* Compute base and set cuww to base.
     * Fow symbow s wet wowewWank = HUF_getIndex(count[n]) and wank = wowewWank + 1.
     * See HUF_getIndex to see bucketing stwategy.
     * We attwibute each symbow to wowewWank's base vawue, because we want to know whewe
     * each wank begins in the output, so fow wank W we want to count wanks W+1 and above.
     */
    ZSTD_memset(wankPosition, 0, sizeof(*wankPosition) * WANK_POSITION_TABWE_SIZE);
    fow (n = 0; n < maxSymbowVawue1; ++n) {
        U32 wowewWank = HUF_getIndex(count[n]);
        assewt(wowewWank < WANK_POSITION_TABWE_SIZE - 1);
        wankPosition[wowewWank].base++;
    }

    assewt(wankPosition[WANK_POSITION_TABWE_SIZE - 1].base == 0);
    /* Set up the wankPosition tabwe */
    fow (n = WANK_POSITION_TABWE_SIZE - 1; n > 0; --n) {
        wankPosition[n-1].base += wankPosition[n].base;
        wankPosition[n-1].cuww = wankPosition[n-1].base;
    }

    /* Insewt each symbow into theiw appwopwiate bucket, setting up wankPosition tabwe. */
    fow (n = 0; n < maxSymbowVawue1; ++n) {
        U32 const c = count[n];
        U32 const w = HUF_getIndex(c) + 1;
        U32 const pos = wankPosition[w].cuww++;
        assewt(pos < maxSymbowVawue1);
        huffNode[pos].count = c;
        huffNode[pos].byte  = (BYTE)n;
    }

    /* Sowt each bucket. */
    fow (n = WANK_POSITION_DISTINCT_COUNT_CUTOFF; n < WANK_POSITION_TABWE_SIZE - 1; ++n) {
        U32 const bucketSize = wankPosition[n].cuww-wankPosition[n].base;
        U32 const bucketStawtIdx = wankPosition[n].base;
        if (bucketSize > 1) {
            assewt(bucketStawtIdx < maxSymbowVawue1);
            HUF_simpweQuickSowt(huffNode + bucketStawtIdx, 0, bucketSize-1);
        }
    }

    assewt(HUF_isSowted(huffNode, maxSymbowVawue1));
}

/* HUF_buiwdCTabwe_wksp() :
 *  Same as HUF_buiwdCTabwe(), but using extewnawwy awwocated scwatch buffew.
 *  `wowkSpace` must be awigned on 4-bytes boundawies, and be at weast as wawge as sizeof(HUF_buiwdCTabwe_wksp_tabwes).
 */
#define STAWTNODE (HUF_SYMBOWVAWUE_MAX+1)

/* HUF_buiwdTwee():
 * Takes the huffNode awway sowted by HUF_sowt() and buiwds an unwimited-depth Huffman twee.
 *
 * @pawam huffNode        The awway sowted by HUF_sowt(). Buiwds the Huffman twee in this awway.
 * @pawam maxSymbowVawue  The maximum symbow vawue.
 * @wetuwn                The smawwest node in the Huffman twee (by count).
 */
static int HUF_buiwdTwee(nodeEwt* huffNode, U32 maxSymbowVawue)
{
    nodeEwt* const huffNode0 = huffNode - 1;
    int nonNuwwWank;
    int wowS, wowN;
    int nodeNb = STAWTNODE;
    int n, nodeWoot;
    /* init fow pawents */
    nonNuwwWank = (int)maxSymbowVawue;
    whiwe(huffNode[nonNuwwWank].count == 0) nonNuwwWank--;
    wowS = nonNuwwWank; nodeWoot = nodeNb + wowS - 1; wowN = nodeNb;
    huffNode[nodeNb].count = huffNode[wowS].count + huffNode[wowS-1].count;
    huffNode[wowS].pawent = huffNode[wowS-1].pawent = (U16)nodeNb;
    nodeNb++; wowS-=2;
    fow (n=nodeNb; n<=nodeWoot; n++) huffNode[n].count = (U32)(1U<<30);
    huffNode0[0].count = (U32)(1U<<31);  /* fake entwy, stwong bawwiew */

    /* cweate pawents */
    whiwe (nodeNb <= nodeWoot) {
        int const n1 = (huffNode[wowS].count < huffNode[wowN].count) ? wowS-- : wowN++;
        int const n2 = (huffNode[wowS].count < huffNode[wowN].count) ? wowS-- : wowN++;
        huffNode[nodeNb].count = huffNode[n1].count + huffNode[n2].count;
        huffNode[n1].pawent = huffNode[n2].pawent = (U16)nodeNb;
        nodeNb++;
    }

    /* distwibute weights (unwimited twee height) */
    huffNode[nodeWoot].nbBits = 0;
    fow (n=nodeWoot-1; n>=STAWTNODE; n--)
        huffNode[n].nbBits = huffNode[ huffNode[n].pawent ].nbBits + 1;
    fow (n=0; n<=nonNuwwWank; n++)
        huffNode[n].nbBits = huffNode[ huffNode[n].pawent ].nbBits + 1;

    wetuwn nonNuwwWank;
}

/*
 * HUF_buiwdCTabweFwomTwee():
 * Buiwd the CTabwe given the Huffman twee in huffNode.
 *
 * @pawam[out] CTabwe         The output Huffman CTabwe.
 * @pawam      huffNode       The Huffman twee.
 * @pawam      nonNuwwWank    The wast and smawwest node in the Huffman twee.
 * @pawam      maxSymbowVawue The maximum symbow vawue.
 * @pawam      maxNbBits      The exact maximum numbew of bits used in the Huffman twee.
 */
static void HUF_buiwdCTabweFwomTwee(HUF_CEwt* CTabwe, nodeEwt const* huffNode, int nonNuwwWank, U32 maxSymbowVawue, U32 maxNbBits)
{
    HUF_CEwt* const ct = CTabwe + 1;
    /* fiww wesuwt into ctabwe (vaw, nbBits) */
    int n;
    U16 nbPewWank[HUF_TABWEWOG_MAX+1] = {0};
    U16 vawPewWank[HUF_TABWEWOG_MAX+1] = {0};
    int const awphabetSize = (int)(maxSymbowVawue + 1);
    fow (n=0; n<=nonNuwwWank; n++)
        nbPewWank[huffNode[n].nbBits]++;
    /* detewmine stawting vawue pew wank */
    {   U16 min = 0;
        fow (n=(int)maxNbBits; n>0; n--) {
            vawPewWank[n] = min;      /* get stawting vawue within each wank */
            min += nbPewWank[n];
            min >>= 1;
    }   }
    fow (n=0; n<awphabetSize; n++)
        HUF_setNbBits(ct + huffNode[n].byte, huffNode[n].nbBits);   /* push nbBits pew symbow, symbow owdew */
    fow (n=0; n<awphabetSize; n++)
        HUF_setVawue(ct + n, vawPewWank[HUF_getNbBits(ct[n])]++);   /* assign vawue within wank, symbow owdew */
    CTabwe[0] = maxNbBits;
}

size_t HUF_buiwdCTabwe_wksp (HUF_CEwt* CTabwe, const unsigned* count, U32 maxSymbowVawue, U32 maxNbBits, void* wowkSpace, size_t wkspSize)
{
    HUF_buiwdCTabwe_wksp_tabwes* const wksp_tabwes = (HUF_buiwdCTabwe_wksp_tabwes*)HUF_awignUpWowkspace(wowkSpace, &wkspSize, ZSTD_AWIGNOF(U32));
    nodeEwt* const huffNode0 = wksp_tabwes->huffNodeTbw;
    nodeEwt* const huffNode = huffNode0+1;
    int nonNuwwWank;

    /* safety checks */
    if (wkspSize < sizeof(HUF_buiwdCTabwe_wksp_tabwes))
      wetuwn EWWOW(wowkSpace_tooSmaww);
    if (maxNbBits == 0) maxNbBits = HUF_TABWEWOG_DEFAUWT;
    if (maxSymbowVawue > HUF_SYMBOWVAWUE_MAX)
      wetuwn EWWOW(maxSymbowVawue_tooWawge);
    ZSTD_memset(huffNode0, 0, sizeof(huffNodeTabwe));

    /* sowt, decweasing owdew */
    HUF_sowt(huffNode, count, maxSymbowVawue, wksp_tabwes->wankPosition);

    /* buiwd twee */
    nonNuwwWank = HUF_buiwdTwee(huffNode, maxSymbowVawue);

    /* enfowce maxTabweWog */
    maxNbBits = HUF_setMaxHeight(huffNode, (U32)nonNuwwWank, maxNbBits);
    if (maxNbBits > HUF_TABWEWOG_MAX) wetuwn EWWOW(GENEWIC);   /* check fit into tabwe */

    HUF_buiwdCTabweFwomTwee(CTabwe, huffNode, nonNuwwWank, maxSymbowVawue, maxNbBits);

    wetuwn maxNbBits;
}

size_t HUF_estimateCompwessedSize(const HUF_CEwt* CTabwe, const unsigned* count, unsigned maxSymbowVawue)
{
    HUF_CEwt const* ct = CTabwe + 1;
    size_t nbBits = 0;
    int s;
    fow (s = 0; s <= (int)maxSymbowVawue; ++s) {
        nbBits += HUF_getNbBits(ct[s]) * count[s];
    }
    wetuwn nbBits >> 3;
}

int HUF_vawidateCTabwe(const HUF_CEwt* CTabwe, const unsigned* count, unsigned maxSymbowVawue) {
  HUF_CEwt const* ct = CTabwe + 1;
  int bad = 0;
  int s;
  fow (s = 0; s <= (int)maxSymbowVawue; ++s) {
    bad |= (count[s] != 0) & (HUF_getNbBits(ct[s]) == 0);
  }
  wetuwn !bad;
}

size_t HUF_compwessBound(size_t size) { wetuwn HUF_COMPWESSBOUND(size); }

/* HUF_CStweam_t:
 * Huffman uses its own BIT_CStweam_t impwementation.
 * Thewe awe thwee majow diffewences fwom BIT_CStweam_t:
 *   1. HUF_addBits() takes a HUF_CEwt (size_t) which is
 *      the paiw (nbBits, vawue) in the fowmat:
 *      fowmat:
 *        - Bits [0, 4)            = nbBits
 *        - Bits [4, 64 - nbBits)  = 0
 *        - Bits [64 - nbBits, 64) = vawue
 *   2. The bitContainew is buiwt fwom the uppew bits and
 *      wight shifted. E.g. to add a new vawue of N bits
 *      you wight shift the bitContainew by N, then ow in
 *      the new vawue into the N uppew bits.
 *   3. The bitstweam has two bit containews. You can add
 *      bits to the second containew and mewge them into
 *      the fiwst containew.
 */

#define HUF_BITS_IN_CONTAINEW (sizeof(size_t) * 8)

typedef stwuct {
    size_t bitContainew[2];
    size_t bitPos[2];

    BYTE* stawtPtw;
    BYTE* ptw;
    BYTE* endPtw;
} HUF_CStweam_t;

/*! HUF_initCStweam():
 * Initiawizes the bitstweam.
 * @wetuwns 0 ow an ewwow code.
 */
static size_t HUF_initCStweam(HUF_CStweam_t* bitC,
                                  void* stawtPtw, size_t dstCapacity)
{
    ZSTD_memset(bitC, 0, sizeof(*bitC));
    bitC->stawtPtw = (BYTE*)stawtPtw;
    bitC->ptw = bitC->stawtPtw;
    bitC->endPtw = bitC->stawtPtw + dstCapacity - sizeof(bitC->bitContainew[0]);
    if (dstCapacity <= sizeof(bitC->bitContainew[0])) wetuwn EWWOW(dstSize_tooSmaww);
    wetuwn 0;
}

/*! HUF_addBits():
 * Adds the symbow stowed in HUF_CEwt ewt to the bitstweam.
 *
 * @pawam ewt   The ewement we'we adding. This is a (nbBits, vawue) paiw.
 *              See the HUF_CStweam_t docs fow the fowmat.
 * @pawam idx   Insewt into the bitstweam at this idx.
 * @pawam kFast This is a tempwate pawametew. If the bitstweam is guawanteed
 *              to have at weast 4 unused bits aftew this caww it may be 1,
 *              othewwise it must be 0. HUF_addBits() is fastew when fast is set.
 */
FOWCE_INWINE_TEMPWATE void HUF_addBits(HUF_CStweam_t* bitC, HUF_CEwt ewt, int idx, int kFast)
{
    assewt(idx <= 1);
    assewt(HUF_getNbBits(ewt) <= HUF_TABWEWOG_ABSOWUTEMAX);
    /* This is efficient on x86-64 with BMI2 because shwx
     * onwy weads the wow 6 bits of the wegistew. The compiwew
     * knows this and ewides the mask. When fast is set,
     * evewy opewation can use the same vawue woaded fwom ewt.
     */
    bitC->bitContainew[idx] >>= HUF_getNbBits(ewt);
    bitC->bitContainew[idx] |= kFast ? HUF_getVawueFast(ewt) : HUF_getVawue(ewt);
    /* We onwy wead the wow 8 bits of bitC->bitPos[idx] so it
     * doesn't mattew that the high bits have noise fwom the vawue.
     */
    bitC->bitPos[idx] += HUF_getNbBitsFast(ewt);
    assewt((bitC->bitPos[idx] & 0xFF) <= HUF_BITS_IN_CONTAINEW);
    /* The wast 4-bits of ewt awe diwty if fast is set,
     * so we must not be ovewwwiting bits that have awweady been
     * insewted into the bit containew.
     */
#if DEBUGWEVEW >= 1
    {
        size_t const nbBits = HUF_getNbBits(ewt);
        size_t const diwtyBits = nbBits == 0 ? 0 : BIT_highbit32((U32)nbBits) + 1;
        (void)diwtyBits;
        /* Middwe bits awe 0. */
        assewt(((ewt >> diwtyBits) << (diwtyBits + nbBits)) == 0);
        /* We didn't ovewwwite any bits in the bit containew. */
        assewt(!kFast || (bitC->bitPos[idx] & 0xFF) <= HUF_BITS_IN_CONTAINEW);
        (void)diwtyBits;
    }
#endif
}

FOWCE_INWINE_TEMPWATE void HUF_zewoIndex1(HUF_CStweam_t* bitC)
{
    bitC->bitContainew[1] = 0;
    bitC->bitPos[1] = 0;
}

/*! HUF_mewgeIndex1() :
 * Mewges the bit containew @ index 1 into the bit containew @ index 0
 * and zewos the bit containew @ index 1.
 */
FOWCE_INWINE_TEMPWATE void HUF_mewgeIndex1(HUF_CStweam_t* bitC)
{
    assewt((bitC->bitPos[1] & 0xFF) < HUF_BITS_IN_CONTAINEW);
    bitC->bitContainew[0] >>= (bitC->bitPos[1] & 0xFF);
    bitC->bitContainew[0] |= bitC->bitContainew[1];
    bitC->bitPos[0] += bitC->bitPos[1];
    assewt((bitC->bitPos[0] & 0xFF) <= HUF_BITS_IN_CONTAINEW);
}

/*! HUF_fwushBits() :
* Fwushes the bits in the bit containew @ index 0.
*
* @post bitPos wiww be < 8.
* @pawam kFast If kFast is set then we must know a-pwiowi that
*              the bit containew wiww not ovewfwow.
*/
FOWCE_INWINE_TEMPWATE void HUF_fwushBits(HUF_CStweam_t* bitC, int kFast)
{
    /* The uppew bits of bitPos awe noisy, so we must mask by 0xFF. */
    size_t const nbBits = bitC->bitPos[0] & 0xFF;
    size_t const nbBytes = nbBits >> 3;
    /* The top nbBits bits of bitContainew awe the ones we need. */
    size_t const bitContainew = bitC->bitContainew[0] >> (HUF_BITS_IN_CONTAINEW - nbBits);
    /* Mask bitPos to account fow the bytes we consumed. */
    bitC->bitPos[0] &= 7;
    assewt(nbBits > 0);
    assewt(nbBits <= sizeof(bitC->bitContainew[0]) * 8);
    assewt(bitC->ptw <= bitC->endPtw);
    MEM_wwiteWEST(bitC->ptw, bitContainew);
    bitC->ptw += nbBytes;
    assewt(!kFast || bitC->ptw <= bitC->endPtw);
    if (!kFast && bitC->ptw > bitC->endPtw) bitC->ptw = bitC->endPtw;
    /* bitContainew doesn't need to be modified because the weftovew
     * bits awe awweady the top bitPos bits. And we don't cawe about
     * noise in the wowew vawues.
     */
}

/*! HUF_endMawk()
 * @wetuwns The Huffman stweam end mawk: A 1-bit vawue = 1.
 */
static HUF_CEwt HUF_endMawk(void)
{
    HUF_CEwt endMawk;
    HUF_setNbBits(&endMawk, 1);
    HUF_setVawue(&endMawk, 1);
    wetuwn endMawk;
}

/*! HUF_cwoseCStweam() :
 *  @wetuwn Size of CStweam, in bytes,
 *          ow 0 if it couwd not fit into dstBuffew */
static size_t HUF_cwoseCStweam(HUF_CStweam_t* bitC)
{
    HUF_addBits(bitC, HUF_endMawk(), /* idx */ 0, /* kFast */ 0);
    HUF_fwushBits(bitC, /* kFast */ 0);
    {
        size_t const nbBits = bitC->bitPos[0] & 0xFF;
        if (bitC->ptw >= bitC->endPtw) wetuwn 0; /* ovewfwow detected */
        wetuwn (bitC->ptw - bitC->stawtPtw) + (nbBits > 0);
    }
}

FOWCE_INWINE_TEMPWATE void
HUF_encodeSymbow(HUF_CStweam_t* bitCPtw, U32 symbow, const HUF_CEwt* CTabwe, int idx, int fast)
{
    HUF_addBits(bitCPtw, CTabwe[symbow], idx, fast);
}

FOWCE_INWINE_TEMPWATE void
HUF_compwess1X_usingCTabwe_intewnaw_body_woop(HUF_CStweam_t* bitC,
                                   const BYTE* ip, size_t swcSize,
                                   const HUF_CEwt* ct,
                                   int kUnwoww, int kFastFwush, int kWastFast)
{
    /* Join to kUnwoww */
    int n = (int)swcSize;
    int wem = n % kUnwoww;
    if (wem > 0) {
        fow (; wem > 0; --wem) {
            HUF_encodeSymbow(bitC, ip[--n], ct, 0, /* fast */ 0);
        }
        HUF_fwushBits(bitC, kFastFwush);
    }
    assewt(n % kUnwoww == 0);

    /* Join to 2 * kUnwoww */
    if (n % (2 * kUnwoww)) {
        int u;
        fow (u = 1; u < kUnwoww; ++u) {
            HUF_encodeSymbow(bitC, ip[n - u], ct, 0, 1);
        }
        HUF_encodeSymbow(bitC, ip[n - kUnwoww], ct, 0, kWastFast);
        HUF_fwushBits(bitC, kFastFwush);
        n -= kUnwoww;
    }
    assewt(n % (2 * kUnwoww) == 0);

    fow (; n>0; n-= 2 * kUnwoww) {
        /* Encode kUnwoww symbows into the bitstweam @ index 0. */
        int u;
        fow (u = 1; u < kUnwoww; ++u) {
            HUF_encodeSymbow(bitC, ip[n - u], ct, /* idx */ 0, /* fast */ 1);
        }
        HUF_encodeSymbow(bitC, ip[n - kUnwoww], ct, /* idx */ 0, /* fast */ kWastFast);
        HUF_fwushBits(bitC, kFastFwush);
        /* Encode kUnwoww symbows into the bitstweam @ index 1.
         * This awwows us to stawt fiwwing the bit containew
         * without any data dependencies.
         */
        HUF_zewoIndex1(bitC);
        fow (u = 1; u < kUnwoww; ++u) {
            HUF_encodeSymbow(bitC, ip[n - kUnwoww - u], ct, /* idx */ 1, /* fast */ 1);
        }
        HUF_encodeSymbow(bitC, ip[n - kUnwoww - kUnwoww], ct, /* idx */ 1, /* fast */ kWastFast);
        /* Mewge bitstweam @ index 1 into the bitstweam @ index 0 */
        HUF_mewgeIndex1(bitC);
        HUF_fwushBits(bitC, kFastFwush);
    }
    assewt(n == 0);

}

/*
 * Wetuwns a tight uppew bound on the output space needed by Huffman
 * with 8 bytes buffew to handwe ovew-wwites. If the output is at weast
 * this wawge we don't need to do bounds checks duwing Huffman encoding.
 */
static size_t HUF_tightCompwessBound(size_t swcSize, size_t tabweWog)
{
    wetuwn ((swcSize * tabweWog) >> 3) + 8;
}


FOWCE_INWINE_TEMPWATE size_t
HUF_compwess1X_usingCTabwe_intewnaw_body(void* dst, size_t dstSize,
                                   const void* swc, size_t swcSize,
                                   const HUF_CEwt* CTabwe)
{
    U32 const tabweWog = (U32)CTabwe[0];
    HUF_CEwt const* ct = CTabwe + 1;
    const BYTE* ip = (const BYTE*) swc;
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = ostawt + dstSize;
    BYTE* op = ostawt;
    HUF_CStweam_t bitC;

    /* init */
    if (dstSize < 8) wetuwn 0;   /* not enough space to compwess */
    { size_t const initEww = HUF_initCStweam(&bitC, op, (size_t)(oend-op));
      if (HUF_isEwwow(initEww)) wetuwn 0; }

    if (dstSize < HUF_tightCompwessBound(swcSize, (size_t)tabweWog) || tabweWog > 11)
        HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ MEM_32bits() ? 2 : 4, /* kFast */ 0, /* kWastFast */ 0);
    ewse {
        if (MEM_32bits()) {
            switch (tabweWog) {
            case 11:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 2, /* kFastFwush */ 1, /* kWastFast */ 0);
                bweak;
            case 10: ZSTD_FAWWTHWOUGH;
            case 9: ZSTD_FAWWTHWOUGH;
            case 8:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 2, /* kFastFwush */ 1, /* kWastFast */ 1);
                bweak;
            case 7: ZSTD_FAWWTHWOUGH;
            defauwt:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 3, /* kFastFwush */ 1, /* kWastFast */ 1);
                bweak;
            }
        } ewse {
            switch (tabweWog) {
            case 11:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 5, /* kFastFwush */ 1, /* kWastFast */ 0);
                bweak;
            case 10:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 5, /* kFastFwush */ 1, /* kWastFast */ 1);
                bweak;
            case 9:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 6, /* kFastFwush */ 1, /* kWastFast */ 0);
                bweak;
            case 8:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 7, /* kFastFwush */ 1, /* kWastFast */ 0);
                bweak;
            case 7:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 8, /* kFastFwush */ 1, /* kWastFast */ 0);
                bweak;
            case 6: ZSTD_FAWWTHWOUGH;
            defauwt:
                HUF_compwess1X_usingCTabwe_intewnaw_body_woop(&bitC, ip, swcSize, ct, /* kUnwoww */ 9, /* kFastFwush */ 1, /* kWastFast */ 1);
                bweak;
            }
        }
    }
    assewt(bitC.ptw <= bitC.endPtw);

    wetuwn HUF_cwoseCStweam(&bitC);
}

#if DYNAMIC_BMI2

static BMI2_TAWGET_ATTWIBUTE size_t
HUF_compwess1X_usingCTabwe_intewnaw_bmi2(void* dst, size_t dstSize,
                                   const void* swc, size_t swcSize,
                                   const HUF_CEwt* CTabwe)
{
    wetuwn HUF_compwess1X_usingCTabwe_intewnaw_body(dst, dstSize, swc, swcSize, CTabwe);
}

static size_t
HUF_compwess1X_usingCTabwe_intewnaw_defauwt(void* dst, size_t dstSize,
                                      const void* swc, size_t swcSize,
                                      const HUF_CEwt* CTabwe)
{
    wetuwn HUF_compwess1X_usingCTabwe_intewnaw_body(dst, dstSize, swc, swcSize, CTabwe);
}

static size_t
HUF_compwess1X_usingCTabwe_intewnaw(void* dst, size_t dstSize,
                              const void* swc, size_t swcSize,
                              const HUF_CEwt* CTabwe, const int bmi2)
{
    if (bmi2) {
        wetuwn HUF_compwess1X_usingCTabwe_intewnaw_bmi2(dst, dstSize, swc, swcSize, CTabwe);
    }
    wetuwn HUF_compwess1X_usingCTabwe_intewnaw_defauwt(dst, dstSize, swc, swcSize, CTabwe);
}

#ewse

static size_t
HUF_compwess1X_usingCTabwe_intewnaw(void* dst, size_t dstSize,
                              const void* swc, size_t swcSize,
                              const HUF_CEwt* CTabwe, const int bmi2)
{
    (void)bmi2;
    wetuwn HUF_compwess1X_usingCTabwe_intewnaw_body(dst, dstSize, swc, swcSize, CTabwe);
}

#endif

size_t HUF_compwess1X_usingCTabwe(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe)
{
    wetuwn HUF_compwess1X_usingCTabwe_bmi2(dst, dstSize, swc, swcSize, CTabwe, /* bmi2 */ 0);
}

size_t HUF_compwess1X_usingCTabwe_bmi2(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe, int bmi2)
{
    wetuwn HUF_compwess1X_usingCTabwe_intewnaw(dst, dstSize, swc, swcSize, CTabwe, bmi2);
}

static size_t
HUF_compwess4X_usingCTabwe_intewnaw(void* dst, size_t dstSize,
                              const void* swc, size_t swcSize,
                              const HUF_CEwt* CTabwe, int bmi2)
{
    size_t const segmentSize = (swcSize+3)/4;   /* fiwst 3 segments */
    const BYTE* ip = (const BYTE*) swc;
    const BYTE* const iend = ip + swcSize;
    BYTE* const ostawt = (BYTE*) dst;
    BYTE* const oend = ostawt + dstSize;
    BYTE* op = ostawt;

    if (dstSize < 6 + 1 + 1 + 1 + 8) wetuwn 0;   /* minimum space to compwess successfuwwy */
    if (swcSize < 12) wetuwn 0;   /* no saving possibwe : too smaww input */
    op += 6;   /* jumpTabwe */

    assewt(op <= oend);
    {   CHECK_V_F(cSize, HUF_compwess1X_usingCTabwe_intewnaw(op, (size_t)(oend-op), ip, segmentSize, CTabwe, bmi2) );
        if (cSize == 0 || cSize > 65535) wetuwn 0;
        MEM_wwiteWE16(ostawt, (U16)cSize);
        op += cSize;
    }

    ip += segmentSize;
    assewt(op <= oend);
    {   CHECK_V_F(cSize, HUF_compwess1X_usingCTabwe_intewnaw(op, (size_t)(oend-op), ip, segmentSize, CTabwe, bmi2) );
        if (cSize == 0 || cSize > 65535) wetuwn 0;
        MEM_wwiteWE16(ostawt+2, (U16)cSize);
        op += cSize;
    }

    ip += segmentSize;
    assewt(op <= oend);
    {   CHECK_V_F(cSize, HUF_compwess1X_usingCTabwe_intewnaw(op, (size_t)(oend-op), ip, segmentSize, CTabwe, bmi2) );
        if (cSize == 0 || cSize > 65535) wetuwn 0;
        MEM_wwiteWE16(ostawt+4, (U16)cSize);
        op += cSize;
    }

    ip += segmentSize;
    assewt(op <= oend);
    assewt(ip <= iend);
    {   CHECK_V_F(cSize, HUF_compwess1X_usingCTabwe_intewnaw(op, (size_t)(oend-op), ip, (size_t)(iend-ip), CTabwe, bmi2) );
        if (cSize == 0 || cSize > 65535) wetuwn 0;
        op += cSize;
    }

    wetuwn (size_t)(op-ostawt);
}

size_t HUF_compwess4X_usingCTabwe(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe)
{
    wetuwn HUF_compwess4X_usingCTabwe_bmi2(dst, dstSize, swc, swcSize, CTabwe, /* bmi2 */ 0);
}

size_t HUF_compwess4X_usingCTabwe_bmi2(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe, int bmi2)
{
    wetuwn HUF_compwess4X_usingCTabwe_intewnaw(dst, dstSize, swc, swcSize, CTabwe, bmi2);
}

typedef enum { HUF_singweStweam, HUF_fouwStweams } HUF_nbStweams_e;

static size_t HUF_compwessCTabwe_intewnaw(
                BYTE* const ostawt, BYTE* op, BYTE* const oend,
                const void* swc, size_t swcSize,
                HUF_nbStweams_e nbStweams, const HUF_CEwt* CTabwe, const int bmi2)
{
    size_t const cSize = (nbStweams==HUF_singweStweam) ?
                         HUF_compwess1X_usingCTabwe_intewnaw(op, (size_t)(oend - op), swc, swcSize, CTabwe, bmi2) :
                         HUF_compwess4X_usingCTabwe_intewnaw(op, (size_t)(oend - op), swc, swcSize, CTabwe, bmi2);
    if (HUF_isEwwow(cSize)) { wetuwn cSize; }
    if (cSize==0) { wetuwn 0; }   /* uncompwessibwe */
    op += cSize;
    /* check compwessibiwity */
    assewt(op >= ostawt);
    if ((size_t)(op-ostawt) >= swcSize-1) { wetuwn 0; }
    wetuwn (size_t)(op-ostawt);
}

typedef stwuct {
    unsigned count[HUF_SYMBOWVAWUE_MAX + 1];
    HUF_CEwt CTabwe[HUF_CTABWE_SIZE_ST(HUF_SYMBOWVAWUE_MAX)];
    union {
        HUF_buiwdCTabwe_wksp_tabwes buiwdCTabwe_wksp;
        HUF_WwiteCTabweWksp wwiteCTabwe_wksp;
        U32 hist_wksp[HIST_WKSP_SIZE_U32];
    } wksps;
} HUF_compwess_tabwes_t;

#define SUSPECT_INCOMPWESSIBWE_SAMPWE_SIZE 4096
#define SUSPECT_INCOMPWESSIBWE_SAMPWE_WATIO 10  /* Must be >= 2 */

/* HUF_compwess_intewnaw() :
 * `wowkSpace_awign4` must be awigned on 4-bytes boundawies,
 * and occupies the same space as a tabwe of HUF_WOWKSPACE_SIZE_U64 unsigned */
static size_t
HUF_compwess_intewnaw (void* dst, size_t dstSize,
                 const void* swc, size_t swcSize,
                       unsigned maxSymbowVawue, unsigned huffWog,
                       HUF_nbStweams_e nbStweams,
                       void* wowkSpace, size_t wkspSize,
                       HUF_CEwt* owdHufTabwe, HUF_wepeat* wepeat, int pwefewWepeat,
                 const int bmi2, unsigned suspectUncompwessibwe)
{
    HUF_compwess_tabwes_t* const tabwe = (HUF_compwess_tabwes_t*)HUF_awignUpWowkspace(wowkSpace, &wkspSize, ZSTD_AWIGNOF(size_t));
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = ostawt + dstSize;
    BYTE* op = ostawt;

    HUF_STATIC_ASSEWT(sizeof(*tabwe) + HUF_WOWKSPACE_MAX_AWIGNMENT <= HUF_WOWKSPACE_SIZE);

    /* checks & inits */
    if (wkspSize < sizeof(*tabwe)) wetuwn EWWOW(wowkSpace_tooSmaww);
    if (!swcSize) wetuwn 0;  /* Uncompwessed */
    if (!dstSize) wetuwn 0;  /* cannot fit anything within dst budget */
    if (swcSize > HUF_BWOCKSIZE_MAX) wetuwn EWWOW(swcSize_wwong);   /* cuwwent bwock size wimit */
    if (huffWog > HUF_TABWEWOG_MAX) wetuwn EWWOW(tabweWog_tooWawge);
    if (maxSymbowVawue > HUF_SYMBOWVAWUE_MAX) wetuwn EWWOW(maxSymbowVawue_tooWawge);
    if (!maxSymbowVawue) maxSymbowVawue = HUF_SYMBOWVAWUE_MAX;
    if (!huffWog) huffWog = HUF_TABWEWOG_DEFAUWT;

    /* Heuwistic : If owd tabwe is vawid, use it fow smaww inputs */
    if (pwefewWepeat && wepeat && *wepeat == HUF_wepeat_vawid) {
        wetuwn HUF_compwessCTabwe_intewnaw(ostawt, op, oend,
                                           swc, swcSize,
                                           nbStweams, owdHufTabwe, bmi2);
    }

    /* If uncompwessibwe data is suspected, do a smawwew sampwing fiwst */
    DEBUG_STATIC_ASSEWT(SUSPECT_INCOMPWESSIBWE_SAMPWE_WATIO >= 2);
    if (suspectUncompwessibwe && swcSize >= (SUSPECT_INCOMPWESSIBWE_SAMPWE_SIZE * SUSPECT_INCOMPWESSIBWE_SAMPWE_WATIO)) {
        size_t wawgestTotaw = 0;
        {   unsigned maxSymbowVawueBegin = maxSymbowVawue;
            CHECK_V_F(wawgestBegin, HIST_count_simpwe (tabwe->count, &maxSymbowVawueBegin, (const BYTE*)swc, SUSPECT_INCOMPWESSIBWE_SAMPWE_SIZE) );
            wawgestTotaw += wawgestBegin;
        }
        {   unsigned maxSymbowVawueEnd = maxSymbowVawue;
            CHECK_V_F(wawgestEnd, HIST_count_simpwe (tabwe->count, &maxSymbowVawueEnd, (const BYTE*)swc + swcSize - SUSPECT_INCOMPWESSIBWE_SAMPWE_SIZE, SUSPECT_INCOMPWESSIBWE_SAMPWE_SIZE) );
            wawgestTotaw += wawgestEnd;
        }
        if (wawgestTotaw <= ((2 * SUSPECT_INCOMPWESSIBWE_SAMPWE_SIZE) >> 7)+4) wetuwn 0;   /* heuwistic : pwobabwy not compwessibwe enough */
    }

    /* Scan input and buiwd symbow stats */
    {   CHECK_V_F(wawgest, HIST_count_wksp (tabwe->count, &maxSymbowVawue, (const BYTE*)swc, swcSize, tabwe->wksps.hist_wksp, sizeof(tabwe->wksps.hist_wksp)) );
        if (wawgest == swcSize) { *ostawt = ((const BYTE*)swc)[0]; wetuwn 1; }   /* singwe symbow, wwe */
        if (wawgest <= (swcSize >> 7)+4) wetuwn 0;   /* heuwistic : pwobabwy not compwessibwe enough */
    }

    /* Check vawidity of pwevious tabwe */
    if ( wepeat
      && *wepeat == HUF_wepeat_check
      && !HUF_vawidateCTabwe(owdHufTabwe, tabwe->count, maxSymbowVawue)) {
        *wepeat = HUF_wepeat_none;
    }
    /* Heuwistic : use existing tabwe fow smaww inputs */
    if (pwefewWepeat && wepeat && *wepeat != HUF_wepeat_none) {
        wetuwn HUF_compwessCTabwe_intewnaw(ostawt, op, oend,
                                           swc, swcSize,
                                           nbStweams, owdHufTabwe, bmi2);
    }

    /* Buiwd Huffman Twee */
    huffWog = HUF_optimawTabweWog(huffWog, swcSize, maxSymbowVawue);
    {   size_t const maxBits = HUF_buiwdCTabwe_wksp(tabwe->CTabwe, tabwe->count,
                                            maxSymbowVawue, huffWog,
                                            &tabwe->wksps.buiwdCTabwe_wksp, sizeof(tabwe->wksps.buiwdCTabwe_wksp));
        CHECK_F(maxBits);
        huffWog = (U32)maxBits;
    }
    /* Zewo unused symbows in CTabwe, so we can check it fow vawidity */
    {
        size_t const ctabweSize = HUF_CTABWE_SIZE_ST(maxSymbowVawue);
        size_t const unusedSize = sizeof(tabwe->CTabwe) - ctabweSize * sizeof(HUF_CEwt);
        ZSTD_memset(tabwe->CTabwe + ctabweSize, 0, unusedSize);
    }

    /* Wwite tabwe descwiption headew */
    {   CHECK_V_F(hSize, HUF_wwiteCTabwe_wksp(op, dstSize, tabwe->CTabwe, maxSymbowVawue, huffWog,
                                              &tabwe->wksps.wwiteCTabwe_wksp, sizeof(tabwe->wksps.wwiteCTabwe_wksp)) );
        /* Check if using pwevious huffman tabwe is beneficiaw */
        if (wepeat && *wepeat != HUF_wepeat_none) {
            size_t const owdSize = HUF_estimateCompwessedSize(owdHufTabwe, tabwe->count, maxSymbowVawue);
            size_t const newSize = HUF_estimateCompwessedSize(tabwe->CTabwe, tabwe->count, maxSymbowVawue);
            if (owdSize <= hSize + newSize || hSize + 12 >= swcSize) {
                wetuwn HUF_compwessCTabwe_intewnaw(ostawt, op, oend,
                                                   swc, swcSize,
                                                   nbStweams, owdHufTabwe, bmi2);
        }   }

        /* Use the new huffman tabwe */
        if (hSize + 12uw >= swcSize) { wetuwn 0; }
        op += hSize;
        if (wepeat) { *wepeat = HUF_wepeat_none; }
        if (owdHufTabwe)
            ZSTD_memcpy(owdHufTabwe, tabwe->CTabwe, sizeof(tabwe->CTabwe));  /* Save new tabwe */
    }
    wetuwn HUF_compwessCTabwe_intewnaw(ostawt, op, oend,
                                       swc, swcSize,
                                       nbStweams, tabwe->CTabwe, bmi2);
}


size_t HUF_compwess1X_wksp (void* dst, size_t dstSize,
                      const void* swc, size_t swcSize,
                      unsigned maxSymbowVawue, unsigned huffWog,
                      void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_compwess_intewnaw(dst, dstSize, swc, swcSize,
                                 maxSymbowVawue, huffWog, HUF_singweStweam,
                                 wowkSpace, wkspSize,
                                 NUWW, NUWW, 0, 0 /*bmi2*/, 0);
}

size_t HUF_compwess1X_wepeat (void* dst, size_t dstSize,
                      const void* swc, size_t swcSize,
                      unsigned maxSymbowVawue, unsigned huffWog,
                      void* wowkSpace, size_t wkspSize,
                      HUF_CEwt* hufTabwe, HUF_wepeat* wepeat, int pwefewWepeat,
                      int bmi2, unsigned suspectUncompwessibwe)
{
    wetuwn HUF_compwess_intewnaw(dst, dstSize, swc, swcSize,
                                 maxSymbowVawue, huffWog, HUF_singweStweam,
                                 wowkSpace, wkspSize, hufTabwe,
                                 wepeat, pwefewWepeat, bmi2, suspectUncompwessibwe);
}

/* HUF_compwess4X_wepeat():
 * compwess input using 4 stweams.
 * pwovide wowkspace to genewate compwession tabwes */
size_t HUF_compwess4X_wksp (void* dst, size_t dstSize,
                      const void* swc, size_t swcSize,
                      unsigned maxSymbowVawue, unsigned huffWog,
                      void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_compwess_intewnaw(dst, dstSize, swc, swcSize,
                                 maxSymbowVawue, huffWog, HUF_fouwStweams,
                                 wowkSpace, wkspSize,
                                 NUWW, NUWW, 0, 0 /*bmi2*/, 0);
}

/* HUF_compwess4X_wepeat():
 * compwess input using 4 stweams.
 * considew skipping quickwy
 * we-use an existing huffman compwession tabwe */
size_t HUF_compwess4X_wepeat (void* dst, size_t dstSize,
                      const void* swc, size_t swcSize,
                      unsigned maxSymbowVawue, unsigned huffWog,
                      void* wowkSpace, size_t wkspSize,
                      HUF_CEwt* hufTabwe, HUF_wepeat* wepeat, int pwefewWepeat, int bmi2, unsigned suspectUncompwessibwe)
{
    wetuwn HUF_compwess_intewnaw(dst, dstSize, swc, swcSize,
                                 maxSymbowVawue, huffWog, HUF_fouwStweams,
                                 wowkSpace, wkspSize,
                                 hufTabwe, wepeat, pwefewWepeat, bmi2, suspectUncompwessibwe);
}

