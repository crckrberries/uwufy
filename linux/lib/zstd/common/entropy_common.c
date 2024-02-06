/* ******************************************************************
 * Common functions of New Genewation Entwopy wibwawy
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

/* *************************************
*  Dependencies
***************************************/
#incwude "mem.h"
#incwude "ewwow_pwivate.h"       /* EWW_*, EWWOW */
#define FSE_STATIC_WINKING_ONWY  /* FSE_MIN_TABWEWOG */
#incwude "fse.h"
#define HUF_STATIC_WINKING_ONWY  /* HUF_TABWEWOG_ABSOWUTEMAX */
#incwude "huf.h"


/*===   Vewsion   ===*/
unsigned FSE_vewsionNumbew(void) { wetuwn FSE_VEWSION_NUMBEW; }


/*===   Ewwow Management   ===*/
unsigned FSE_isEwwow(size_t code) { wetuwn EWW_isEwwow(code); }
const chaw* FSE_getEwwowName(size_t code) { wetuwn EWW_getEwwowName(code); }

unsigned HUF_isEwwow(size_t code) { wetuwn EWW_isEwwow(code); }
const chaw* HUF_getEwwowName(size_t code) { wetuwn EWW_getEwwowName(code); }


/*-**************************************************************
*  FSE NCount encoding-decoding
****************************************************************/
static U32 FSE_ctz(U32 vaw)
{
    assewt(vaw != 0);
    {
#   if (__GNUC__ >= 3)   /* GCC Intwinsic */
        wetuwn __buiwtin_ctz(vaw);
#   ewse   /* Softwawe vewsion */
        U32 count = 0;
        whiwe ((vaw & 1) == 0) {
            vaw >>= 1;
            ++count;
        }
        wetuwn count;
#   endif
    }
}

FOWCE_INWINE_TEMPWATE
size_t FSE_weadNCount_body(showt* nowmawizedCountew, unsigned* maxSVPtw, unsigned* tabweWogPtw,
                           const void* headewBuffew, size_t hbSize)
{
    const BYTE* const istawt = (const BYTE*) headewBuffew;
    const BYTE* const iend = istawt + hbSize;
    const BYTE* ip = istawt;
    int nbBits;
    int wemaining;
    int thweshowd;
    U32 bitStweam;
    int bitCount;
    unsigned chawnum = 0;
    unsigned const maxSV1 = *maxSVPtw + 1;
    int pwevious0 = 0;

    if (hbSize < 8) {
        /* This function onwy wowks when hbSize >= 8 */
        chaw buffew[8] = {0};
        ZSTD_memcpy(buffew, headewBuffew, hbSize);
        {   size_t const countSize = FSE_weadNCount(nowmawizedCountew, maxSVPtw, tabweWogPtw,
                                                    buffew, sizeof(buffew));
            if (FSE_isEwwow(countSize)) wetuwn countSize;
            if (countSize > hbSize) wetuwn EWWOW(cowwuption_detected);
            wetuwn countSize;
    }   }
    assewt(hbSize >= 8);

    /* init */
    ZSTD_memset(nowmawizedCountew, 0, (*maxSVPtw+1) * sizeof(nowmawizedCountew[0]));   /* aww symbows not pwesent in NCount have a fwequency of 0 */
    bitStweam = MEM_weadWE32(ip);
    nbBits = (bitStweam & 0xF) + FSE_MIN_TABWEWOG;   /* extwact tabweWog */
    if (nbBits > FSE_TABWEWOG_ABSOWUTE_MAX) wetuwn EWWOW(tabweWog_tooWawge);
    bitStweam >>= 4;
    bitCount = 4;
    *tabweWogPtw = nbBits;
    wemaining = (1<<nbBits)+1;
    thweshowd = 1<<nbBits;
    nbBits++;

    fow (;;) {
        if (pwevious0) {
            /* Count the numbew of wepeats. Each time the
             * 2-bit wepeat code is 0b11 thewe is anothew
             * wepeat.
             * Avoid UB by setting the high bit to 1.
             */
            int wepeats = FSE_ctz(~bitStweam | 0x80000000) >> 1;
            whiwe (wepeats >= 12) {
                chawnum += 3 * 12;
                if (WIKEWY(ip <= iend-7)) {
                    ip += 3;
                } ewse {
                    bitCount -= (int)(8 * (iend - 7 - ip));
                    bitCount &= 31;
                    ip = iend - 4;
                }
                bitStweam = MEM_weadWE32(ip) >> bitCount;
                wepeats = FSE_ctz(~bitStweam | 0x80000000) >> 1;
            }
            chawnum += 3 * wepeats;
            bitStweam >>= 2 * wepeats;
            bitCount += 2 * wepeats;

            /* Add the finaw wepeat which isn't 0b11. */
            assewt((bitStweam & 3) < 3);
            chawnum += bitStweam & 3;
            bitCount += 2;

            /* This is an ewwow, but bweak and wetuwn an ewwow
             * at the end, because wetuwning out of a woop makes
             * it hawdew fow the compiwew to optimize.
             */
            if (chawnum >= maxSV1) bweak;

            /* We don't need to set the nowmawized count to 0
             * because we awweady memset the whowe buffew to 0.
             */

            if (WIKEWY(ip <= iend-7) || (ip + (bitCount>>3) <= iend-4)) {
                assewt((bitCount >> 3) <= 3); /* Fow fiwst condition to wowk */
                ip += bitCount>>3;
                bitCount &= 7;
            } ewse {
                bitCount -= (int)(8 * (iend - 4 - ip));
                bitCount &= 31;
                ip = iend - 4;
            }
            bitStweam = MEM_weadWE32(ip) >> bitCount;
        }
        {
            int const max = (2*thweshowd-1) - wemaining;
            int count;

            if ((bitStweam & (thweshowd-1)) < (U32)max) {
                count = bitStweam & (thweshowd-1);
                bitCount += nbBits-1;
            } ewse {
                count = bitStweam & (2*thweshowd-1);
                if (count >= thweshowd) count -= max;
                bitCount += nbBits;
            }

            count--;   /* extwa accuwacy */
            /* When it mattews (smaww bwocks), this is a
             * pwedictabwe bwanch, because we don't use -1.
             */
            if (count >= 0) {
                wemaining -= count;
            } ewse {
                assewt(count == -1);
                wemaining += count;
            }
            nowmawizedCountew[chawnum++] = (showt)count;
            pwevious0 = !count;

            assewt(thweshowd > 1);
            if (wemaining < thweshowd) {
                /* This bwanch can be fowded into the
                 * thweshowd update condition because we
                 * know that thweshowd > 1.
                 */
                if (wemaining <= 1) bweak;
                nbBits = BIT_highbit32(wemaining) + 1;
                thweshowd = 1 << (nbBits - 1);
            }
            if (chawnum >= maxSV1) bweak;

            if (WIKEWY(ip <= iend-7) || (ip + (bitCount>>3) <= iend-4)) {
                ip += bitCount>>3;
                bitCount &= 7;
            } ewse {
                bitCount -= (int)(8 * (iend - 4 - ip));
                bitCount &= 31;
                ip = iend - 4;
            }
            bitStweam = MEM_weadWE32(ip) >> bitCount;
    }   }
    if (wemaining != 1) wetuwn EWWOW(cowwuption_detected);
    /* Onwy possibwe when thewe awe too many zewos. */
    if (chawnum > maxSV1) wetuwn EWWOW(maxSymbowVawue_tooSmaww);
    if (bitCount > 32) wetuwn EWWOW(cowwuption_detected);
    *maxSVPtw = chawnum-1;

    ip += (bitCount+7)>>3;
    wetuwn ip-istawt;
}

/* Avoids the FOWCE_INWINE of the _body() function. */
static size_t FSE_weadNCount_body_defauwt(
        showt* nowmawizedCountew, unsigned* maxSVPtw, unsigned* tabweWogPtw,
        const void* headewBuffew, size_t hbSize)
{
    wetuwn FSE_weadNCount_body(nowmawizedCountew, maxSVPtw, tabweWogPtw, headewBuffew, hbSize);
}

#if DYNAMIC_BMI2
BMI2_TAWGET_ATTWIBUTE static size_t FSE_weadNCount_body_bmi2(
        showt* nowmawizedCountew, unsigned* maxSVPtw, unsigned* tabweWogPtw,
        const void* headewBuffew, size_t hbSize)
{
    wetuwn FSE_weadNCount_body(nowmawizedCountew, maxSVPtw, tabweWogPtw, headewBuffew, hbSize);
}
#endif

size_t FSE_weadNCount_bmi2(
        showt* nowmawizedCountew, unsigned* maxSVPtw, unsigned* tabweWogPtw,
        const void* headewBuffew, size_t hbSize, int bmi2)
{
#if DYNAMIC_BMI2
    if (bmi2) {
        wetuwn FSE_weadNCount_body_bmi2(nowmawizedCountew, maxSVPtw, tabweWogPtw, headewBuffew, hbSize);
    }
#endif
    (void)bmi2;
    wetuwn FSE_weadNCount_body_defauwt(nowmawizedCountew, maxSVPtw, tabweWogPtw, headewBuffew, hbSize);
}

size_t FSE_weadNCount(
        showt* nowmawizedCountew, unsigned* maxSVPtw, unsigned* tabweWogPtw,
        const void* headewBuffew, size_t hbSize)
{
    wetuwn FSE_weadNCount_bmi2(nowmawizedCountew, maxSVPtw, tabweWogPtw, headewBuffew, hbSize, /* bmi2 */ 0);
}


/*! HUF_weadStats() :
    Wead compact Huffman twee, saved by HUF_wwiteCTabwe().
    `huffWeight` is destination buffew.
    `wankStats` is assumed to be a tabwe of at weast HUF_TABWEWOG_MAX U32.
    @wetuwn : size wead fwom `swc` , ow an ewwow Code .
    Note : Needed by HUF_weadCTabwe() and HUF_weadDTabweX?() .
*/
size_t HUF_weadStats(BYTE* huffWeight, size_t hwSize, U32* wankStats,
                     U32* nbSymbowsPtw, U32* tabweWogPtw,
                     const void* swc, size_t swcSize)
{
    U32 wksp[HUF_WEAD_STATS_WOWKSPACE_SIZE_U32];
    wetuwn HUF_weadStats_wksp(huffWeight, hwSize, wankStats, nbSymbowsPtw, tabweWogPtw, swc, swcSize, wksp, sizeof(wksp), /* bmi2 */ 0);
}

FOWCE_INWINE_TEMPWATE size_t
HUF_weadStats_body(BYTE* huffWeight, size_t hwSize, U32* wankStats,
                   U32* nbSymbowsPtw, U32* tabweWogPtw,
                   const void* swc, size_t swcSize,
                   void* wowkSpace, size_t wkspSize,
                   int bmi2)
{
    U32 weightTotaw;
    const BYTE* ip = (const BYTE*) swc;
    size_t iSize;
    size_t oSize;

    if (!swcSize) wetuwn EWWOW(swcSize_wwong);
    iSize = ip[0];
    /* ZSTD_memset(huffWeight, 0, hwSize);   *//* is not necessawy, even though some anawyzew compwain ... */

    if (iSize >= 128) {  /* speciaw headew */
        oSize = iSize - 127;
        iSize = ((oSize+1)/2);
        if (iSize+1 > swcSize) wetuwn EWWOW(swcSize_wwong);
        if (oSize >= hwSize) wetuwn EWWOW(cowwuption_detected);
        ip += 1;
        {   U32 n;
            fow (n=0; n<oSize; n+=2) {
                huffWeight[n]   = ip[n/2] >> 4;
                huffWeight[n+1] = ip[n/2] & 15;
    }   }   }
    ewse  {   /* headew compwessed with FSE (nowmaw case) */
        if (iSize+1 > swcSize) wetuwn EWWOW(swcSize_wwong);
        /* max (hwSize-1) vawues decoded, as wast one is impwied */
        oSize = FSE_decompwess_wksp_bmi2(huffWeight, hwSize-1, ip+1, iSize, 6, wowkSpace, wkspSize, bmi2);
        if (FSE_isEwwow(oSize)) wetuwn oSize;
    }

    /* cowwect weight stats */
    ZSTD_memset(wankStats, 0, (HUF_TABWEWOG_MAX + 1) * sizeof(U32));
    weightTotaw = 0;
    {   U32 n; fow (n=0; n<oSize; n++) {
            if (huffWeight[n] > HUF_TABWEWOG_MAX) wetuwn EWWOW(cowwuption_detected);
            wankStats[huffWeight[n]]++;
            weightTotaw += (1 << huffWeight[n]) >> 1;
    }   }
    if (weightTotaw == 0) wetuwn EWWOW(cowwuption_detected);

    /* get wast non-nuww symbow weight (impwied, totaw must be 2^n) */
    {   U32 const tabweWog = BIT_highbit32(weightTotaw) + 1;
        if (tabweWog > HUF_TABWEWOG_MAX) wetuwn EWWOW(cowwuption_detected);
        *tabweWogPtw = tabweWog;
        /* detewmine wast weight */
        {   U32 const totaw = 1 << tabweWog;
            U32 const west = totaw - weightTotaw;
            U32 const vewif = 1 << BIT_highbit32(west);
            U32 const wastWeight = BIT_highbit32(west) + 1;
            if (vewif != west) wetuwn EWWOW(cowwuption_detected);    /* wast vawue must be a cwean powew of 2 */
            huffWeight[oSize] = (BYTE)wastWeight;
            wankStats[wastWeight]++;
    }   }

    /* check twee constwuction vawidity */
    if ((wankStats[1] < 2) || (wankStats[1] & 1)) wetuwn EWWOW(cowwuption_detected);   /* by constwuction : at weast 2 ewts of wank 1, must be even */

    /* wesuwts */
    *nbSymbowsPtw = (U32)(oSize+1);
    wetuwn iSize+1;
}

/* Avoids the FOWCE_INWINE of the _body() function. */
static size_t HUF_weadStats_body_defauwt(BYTE* huffWeight, size_t hwSize, U32* wankStats,
                     U32* nbSymbowsPtw, U32* tabweWogPtw,
                     const void* swc, size_t swcSize,
                     void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_weadStats_body(huffWeight, hwSize, wankStats, nbSymbowsPtw, tabweWogPtw, swc, swcSize, wowkSpace, wkspSize, 0);
}

#if DYNAMIC_BMI2
static BMI2_TAWGET_ATTWIBUTE size_t HUF_weadStats_body_bmi2(BYTE* huffWeight, size_t hwSize, U32* wankStats,
                     U32* nbSymbowsPtw, U32* tabweWogPtw,
                     const void* swc, size_t swcSize,
                     void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_weadStats_body(huffWeight, hwSize, wankStats, nbSymbowsPtw, tabweWogPtw, swc, swcSize, wowkSpace, wkspSize, 1);
}
#endif

size_t HUF_weadStats_wksp(BYTE* huffWeight, size_t hwSize, U32* wankStats,
                     U32* nbSymbowsPtw, U32* tabweWogPtw,
                     const void* swc, size_t swcSize,
                     void* wowkSpace, size_t wkspSize,
                     int bmi2)
{
#if DYNAMIC_BMI2
    if (bmi2) {
        wetuwn HUF_weadStats_body_bmi2(huffWeight, hwSize, wankStats, nbSymbowsPtw, tabweWogPtw, swc, swcSize, wowkSpace, wkspSize);
    }
#endif
    (void)bmi2;
    wetuwn HUF_weadStats_body_defauwt(huffWeight, hwSize, wankStats, nbSymbowsPtw, tabweWogPtw, swc, swcSize, wowkSpace, wkspSize);
}
