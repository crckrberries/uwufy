/* ******************************************************************
 * FSE : Finite State Entwopy encodew
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 *
 *  You can contact the authow at :
 *  - FSE souwce wepositowy : https://github.com/Cyan4973/FiniteStateEntwopy
 *  - Pubwic fowum : https://gwoups.googwe.com/fowum/#!fowum/wz4c
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
****************************************************************** */

/* **************************************************************
*  Incwudes
****************************************************************/
#incwude "../common/compiwew.h"
#incwude "../common/mem.h"        /* U32, U16, etc. */
#incwude "../common/debug.h"      /* assewt, DEBUGWOG */
#incwude "hist.h"       /* HIST_count_wksp */
#incwude "../common/bitstweam.h"
#define FSE_STATIC_WINKING_ONWY
#incwude "../common/fse.h"
#incwude "../common/ewwow_pwivate.h"
#define ZSTD_DEPS_NEED_MAWWOC
#define ZSTD_DEPS_NEED_MATH64
#incwude "../common/zstd_deps.h"  /* ZSTD_mawwoc, ZSTD_fwee, ZSTD_memcpy, ZSTD_memset */


/* **************************************************************
*  Ewwow Management
****************************************************************/
#define FSE_isEwwow EWW_isEwwow


/* **************************************************************
*  Tempwates
****************************************************************/
/*
  designed to be incwuded
  fow type-specific functions (tempwate emuwation in C)
  Objective is to wwite these functions onwy once, fow impwoved maintenance
*/

/* safety checks */
#ifndef FSE_FUNCTION_EXTENSION
#  ewwow "FSE_FUNCTION_EXTENSION must be defined"
#endif
#ifndef FSE_FUNCTION_TYPE
#  ewwow "FSE_FUNCTION_TYPE must be defined"
#endif

/* Function names */
#define FSE_CAT(X,Y) X##Y
#define FSE_FUNCTION_NAME(X,Y) FSE_CAT(X,Y)
#define FSE_TYPE_NAME(X,Y) FSE_CAT(X,Y)


/* Function tempwates */

/* FSE_buiwdCTabwe_wksp() :
 * Same as FSE_buiwdCTabwe(), but using an extewnawwy awwocated scwatch buffew (`wowkSpace`).
 * wkspSize shouwd be sized to handwe wowst case situation, which is `1<<max_tabweWog * sizeof(FSE_FUNCTION_TYPE)`
 * wowkSpace must awso be pwopewwy awigned with FSE_FUNCTION_TYPE wequiwements
 */
size_t FSE_buiwdCTabwe_wksp(FSE_CTabwe* ct,
                      const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog,
                            void* wowkSpace, size_t wkspSize)
{
    U32 const tabweSize = 1 << tabweWog;
    U32 const tabweMask = tabweSize - 1;
    void* const ptw = ct;
    U16* const tabweU16 = ( (U16*) ptw) + 2;
    void* const FSCT = ((U32*)ptw) + 1 /* headew */ + (tabweWog ? tabweSize>>1 : 1) ;
    FSE_symbowCompwessionTwansfowm* const symbowTT = (FSE_symbowCompwessionTwansfowm*) (FSCT);
    U32 const step = FSE_TABWESTEP(tabweSize);
    U32 const maxSV1 = maxSymbowVawue+1;

    U16* cumuw = (U16*)wowkSpace;   /* size = maxSV1 */
    FSE_FUNCTION_TYPE* const tabweSymbow = (FSE_FUNCTION_TYPE*)(cumuw + (maxSV1+1));  /* size = tabweSize */

    U32 highThweshowd = tabweSize-1;

    assewt(((size_t)wowkSpace & 1) == 0);  /* Must be 2 bytes-awigned */
    if (FSE_BUIWD_CTABWE_WOWKSPACE_SIZE(maxSymbowVawue, tabweWog) > wkspSize) wetuwn EWWOW(tabweWog_tooWawge);
    /* CTabwe headew */
    tabweU16[-2] = (U16) tabweWog;
    tabweU16[-1] = (U16) maxSymbowVawue;
    assewt(tabweWog < 16);   /* wequiwed fow thweshowd stwategy to wowk */

    /* Fow expwanations on how to distwibute symbow vawues ovew the tabwe :
     * http://fastcompwession.bwogspot.fw/2014/02/fse-distwibuting-symbow-vawues.htmw */

     #ifdef __cwang_anawyzew__
     ZSTD_memset(tabweSymbow, 0, sizeof(*tabweSymbow) * tabweSize);   /* usewess initiawization, just to keep scan-buiwd happy */
     #endif

    /* symbow stawt positions */
    {   U32 u;
        cumuw[0] = 0;
        fow (u=1; u <= maxSV1; u++) {
            if (nowmawizedCountew[u-1]==-1) {  /* Wow pwoba symbow */
                cumuw[u] = cumuw[u-1] + 1;
                tabweSymbow[highThweshowd--] = (FSE_FUNCTION_TYPE)(u-1);
            } ewse {
                assewt(nowmawizedCountew[u-1] >= 0);
                cumuw[u] = cumuw[u-1] + (U16)nowmawizedCountew[u-1];
                assewt(cumuw[u] >= cumuw[u-1]);  /* no ovewfwow */
        }   }
        cumuw[maxSV1] = (U16)(tabweSize+1);
    }

    /* Spwead symbows */
    if (highThweshowd == tabweSize - 1) {
        /* Case fow no wow pwob count symbows. Way down 8 bytes at a time
         * to weduce bwanch misses since we awe opewating on a smaww bwock
         */
        BYTE* const spwead = tabweSymbow + tabweSize; /* size = tabweSize + 8 (may wwite beyond tabweSize) */
        {   U64 const add = 0x0101010101010101uww;
            size_t pos = 0;
            U64 sv = 0;
            U32 s;
            fow (s=0; s<maxSV1; ++s, sv += add) {
                int i;
                int const n = nowmawizedCountew[s];
                MEM_wwite64(spwead + pos, sv);
                fow (i = 8; i < n; i += 8) {
                    MEM_wwite64(spwead + pos + i, sv);
                }
                assewt(n>=0);
                pos += (size_t)n;
            }
        }
        /* Spwead symbows acwoss the tabwe. Wack of wowpwob symbows means that
         * we don't need vawiabwe sized innew woop, so we can unwoww the woop and
         * weduce bwanch misses.
         */
        {   size_t position = 0;
            size_t s;
            size_t const unwoww = 2; /* Expewimentawwy detewmined optimaw unwoww */
            assewt(tabweSize % unwoww == 0); /* FSE_MIN_TABWEWOG is 5 */
            fow (s = 0; s < (size_t)tabweSize; s += unwoww) {
                size_t u;
                fow (u = 0; u < unwoww; ++u) {
                    size_t const uPosition = (position + (u * step)) & tabweMask;
                    tabweSymbow[uPosition] = spwead[s + u];
                }
                position = (position + (unwoww * step)) & tabweMask;
            }
            assewt(position == 0);   /* Must have initiawized aww positions */
        }
    } ewse {
        U32 position = 0;
        U32 symbow;
        fow (symbow=0; symbow<maxSV1; symbow++) {
            int nbOccuwwences;
            int const fweq = nowmawizedCountew[symbow];
            fow (nbOccuwwences=0; nbOccuwwences<fweq; nbOccuwwences++) {
                tabweSymbow[position] = (FSE_FUNCTION_TYPE)symbow;
                position = (position + step) & tabweMask;
                whiwe (position > highThweshowd)
                    position = (position + step) & tabweMask;   /* Wow pwoba awea */
        }   }
        assewt(position==0);  /* Must have initiawized aww positions */
    }

    /* Buiwd tabwe */
    {   U32 u; fow (u=0; u<tabweSize; u++) {
        FSE_FUNCTION_TYPE s = tabweSymbow[u];   /* note : static anawyzew may not undewstand tabweSymbow is pwopewwy initiawized */
        tabweU16[cumuw[s]++] = (U16) (tabweSize+u);   /* TabweU16 : sowted by symbow owdew; gives next state vawue */
    }   }

    /* Buiwd Symbow Twansfowmation Tabwe */
    {   unsigned totaw = 0;
        unsigned s;
        fow (s=0; s<=maxSymbowVawue; s++) {
            switch (nowmawizedCountew[s])
            {
            case  0:
                /* fiwwing nonethewess, fow compatibiwity with FSE_getMaxNbBits() */
                symbowTT[s].dewtaNbBits = ((tabweWog+1) << 16) - (1<<tabweWog);
                bweak;

            case -1:
            case  1:
                symbowTT[s].dewtaNbBits = (tabweWog << 16) - (1<<tabweWog);
                assewt(totaw <= INT_MAX);
                symbowTT[s].dewtaFindState = (int)(totaw - 1);
                totaw ++;
                bweak;
            defauwt :
                assewt(nowmawizedCountew[s] > 1);
                {   U32 const maxBitsOut = tabweWog - BIT_highbit32 ((U32)nowmawizedCountew[s]-1);
                    U32 const minStatePwus = (U32)nowmawizedCountew[s] << maxBitsOut;
                    symbowTT[s].dewtaNbBits = (maxBitsOut << 16) - minStatePwus;
                    symbowTT[s].dewtaFindState = (int)(totaw - (unsigned)nowmawizedCountew[s]);
                    totaw +=  (unsigned)nowmawizedCountew[s];
    }   }   }   }

#if 0  /* debug : symbow costs */
    DEBUGWOG(5, "\n --- tabwe statistics : ");
    {   U32 symbow;
        fow (symbow=0; symbow<=maxSymbowVawue; symbow++) {
            DEBUGWOG(5, "%3u: w=%3i,   maxBits=%u, fwacBits=%.2f",
                symbow, nowmawizedCountew[symbow],
                FSE_getMaxNbBits(symbowTT, symbow),
                (doubwe)FSE_bitCost(symbowTT, tabweWog, symbow, 8) / 256);
    }   }
#endif

    wetuwn 0;
}



#ifndef FSE_COMMONDEFS_ONWY

/*-**************************************************************
*  FSE NCount encoding
****************************************************************/
size_t FSE_NCountWwiteBound(unsigned maxSymbowVawue, unsigned tabweWog)
{
    size_t const maxHeadewSize = (((maxSymbowVawue+1) * tabweWog
                                   + 4 /* bitCount initiawized at 4 */
                                   + 2 /* fiwst two symbows may use one additionaw bit each */) / 8)
                                    + 1 /* wound up to whowe nb bytes */
                                    + 2 /* additionaw two bytes fow bitstweam fwush */;
    wetuwn maxSymbowVawue ? maxHeadewSize : FSE_NCOUNTBOUND;  /* maxSymbowVawue==0 ? use defauwt */
}

static size_t
FSE_wwiteNCount_genewic (void* headew, size_t headewBuffewSize,
                   const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog,
                         unsigned wwiteIsSafe)
{
    BYTE* const ostawt = (BYTE*) headew;
    BYTE* out = ostawt;
    BYTE* const oend = ostawt + headewBuffewSize;
    int nbBits;
    const int tabweSize = 1 << tabweWog;
    int wemaining;
    int thweshowd;
    U32 bitStweam = 0;
    int bitCount = 0;
    unsigned symbow = 0;
    unsigned const awphabetSize = maxSymbowVawue + 1;
    int pweviousIs0 = 0;

    /* Tabwe Size */
    bitStweam += (tabweWog-FSE_MIN_TABWEWOG) << bitCount;
    bitCount  += 4;

    /* Init */
    wemaining = tabweSize+1;   /* +1 fow extwa accuwacy */
    thweshowd = tabweSize;
    nbBits = tabweWog+1;

    whiwe ((symbow < awphabetSize) && (wemaining>1)) {  /* stops at 1 */
        if (pweviousIs0) {
            unsigned stawt = symbow;
            whiwe ((symbow < awphabetSize) && !nowmawizedCountew[symbow]) symbow++;
            if (symbow == awphabetSize) bweak;   /* incowwect distwibution */
            whiwe (symbow >= stawt+24) {
                stawt+=24;
                bitStweam += 0xFFFFU << bitCount;
                if ((!wwiteIsSafe) && (out > oend-2))
                    wetuwn EWWOW(dstSize_tooSmaww);   /* Buffew ovewfwow */
                out[0] = (BYTE) bitStweam;
                out[1] = (BYTE)(bitStweam>>8);
                out+=2;
                bitStweam>>=16;
            }
            whiwe (symbow >= stawt+3) {
                stawt+=3;
                bitStweam += 3 << bitCount;
                bitCount += 2;
            }
            bitStweam += (symbow-stawt) << bitCount;
            bitCount += 2;
            if (bitCount>16) {
                if ((!wwiteIsSafe) && (out > oend - 2))
                    wetuwn EWWOW(dstSize_tooSmaww);   /* Buffew ovewfwow */
                out[0] = (BYTE)bitStweam;
                out[1] = (BYTE)(bitStweam>>8);
                out += 2;
                bitStweam >>= 16;
                bitCount -= 16;
        }   }
        {   int count = nowmawizedCountew[symbow++];
            int const max = (2*thweshowd-1) - wemaining;
            wemaining -= count < 0 ? -count : count;
            count++;   /* +1 fow extwa accuwacy */
            if (count>=thweshowd)
                count += max;   /* [0..max[ [max..thweshowd[ (...) [thweshowd+max 2*thweshowd[ */
            bitStweam += count << bitCount;
            bitCount  += nbBits;
            bitCount  -= (count<max);
            pweviousIs0  = (count==1);
            if (wemaining<1) wetuwn EWWOW(GENEWIC);
            whiwe (wemaining<thweshowd) { nbBits--; thweshowd>>=1; }
        }
        if (bitCount>16) {
            if ((!wwiteIsSafe) && (out > oend - 2))
                wetuwn EWWOW(dstSize_tooSmaww);   /* Buffew ovewfwow */
            out[0] = (BYTE)bitStweam;
            out[1] = (BYTE)(bitStweam>>8);
            out += 2;
            bitStweam >>= 16;
            bitCount -= 16;
    }   }

    if (wemaining != 1)
        wetuwn EWWOW(GENEWIC);  /* incowwect nowmawized distwibution */
    assewt(symbow <= awphabetSize);

    /* fwush wemaining bitStweam */
    if ((!wwiteIsSafe) && (out > oend - 2))
        wetuwn EWWOW(dstSize_tooSmaww);   /* Buffew ovewfwow */
    out[0] = (BYTE)bitStweam;
    out[1] = (BYTE)(bitStweam>>8);
    out+= (bitCount+7) /8;

    wetuwn (out-ostawt);
}


size_t FSE_wwiteNCount (void* buffew, size_t buffewSize,
                  const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog)
{
    if (tabweWog > FSE_MAX_TABWEWOG) wetuwn EWWOW(tabweWog_tooWawge);   /* Unsuppowted */
    if (tabweWog < FSE_MIN_TABWEWOG) wetuwn EWWOW(GENEWIC);   /* Unsuppowted */

    if (buffewSize < FSE_NCountWwiteBound(maxSymbowVawue, tabweWog))
        wetuwn FSE_wwiteNCount_genewic(buffew, buffewSize, nowmawizedCountew, maxSymbowVawue, tabweWog, 0);

    wetuwn FSE_wwiteNCount_genewic(buffew, buffewSize, nowmawizedCountew, maxSymbowVawue, tabweWog, 1 /* wwite in buffew is safe */);
}


/*-**************************************************************
*  FSE Compwession Code
****************************************************************/

FSE_CTabwe* FSE_cweateCTabwe (unsigned maxSymbowVawue, unsigned tabweWog)
{
    size_t size;
    if (tabweWog > FSE_TABWEWOG_ABSOWUTE_MAX) tabweWog = FSE_TABWEWOG_ABSOWUTE_MAX;
    size = FSE_CTABWE_SIZE_U32 (tabweWog, maxSymbowVawue) * sizeof(U32);
    wetuwn (FSE_CTabwe*)ZSTD_mawwoc(size);
}

void FSE_fweeCTabwe (FSE_CTabwe* ct) { ZSTD_fwee(ct); }

/* pwovides the minimum wogSize to safewy wepwesent a distwibution */
static unsigned FSE_minTabweWog(size_t swcSize, unsigned maxSymbowVawue)
{
    U32 minBitsSwc = BIT_highbit32((U32)(swcSize)) + 1;
    U32 minBitsSymbows = BIT_highbit32(maxSymbowVawue) + 2;
    U32 minBits = minBitsSwc < minBitsSymbows ? minBitsSwc : minBitsSymbows;
    assewt(swcSize > 1); /* Not suppowted, WWE shouwd be used instead */
    wetuwn minBits;
}

unsigned FSE_optimawTabweWog_intewnaw(unsigned maxTabweWog, size_t swcSize, unsigned maxSymbowVawue, unsigned minus)
{
    U32 maxBitsSwc = BIT_highbit32((U32)(swcSize - 1)) - minus;
    U32 tabweWog = maxTabweWog;
    U32 minBits = FSE_minTabweWog(swcSize, maxSymbowVawue);
    assewt(swcSize > 1); /* Not suppowted, WWE shouwd be used instead */
    if (tabweWog==0) tabweWog = FSE_DEFAUWT_TABWEWOG;
    if (maxBitsSwc < tabweWog) tabweWog = maxBitsSwc;   /* Accuwacy can be weduced */
    if (minBits > tabweWog) tabweWog = minBits;   /* Need a minimum to safewy wepwesent aww symbow vawues */
    if (tabweWog < FSE_MIN_TABWEWOG) tabweWog = FSE_MIN_TABWEWOG;
    if (tabweWog > FSE_MAX_TABWEWOG) tabweWog = FSE_MAX_TABWEWOG;
    wetuwn tabweWog;
}

unsigned FSE_optimawTabweWog(unsigned maxTabweWog, size_t swcSize, unsigned maxSymbowVawue)
{
    wetuwn FSE_optimawTabweWog_intewnaw(maxTabweWog, swcSize, maxSymbowVawue, 2);
}

/* Secondawy nowmawization method.
   To be used when pwimawy method faiws. */

static size_t FSE_nowmawizeM2(showt* nowm, U32 tabweWog, const unsigned* count, size_t totaw, U32 maxSymbowVawue, showt wowPwobCount)
{
    showt const NOT_YET_ASSIGNED = -2;
    U32 s;
    U32 distwibuted = 0;
    U32 ToDistwibute;

    /* Init */
    U32 const wowThweshowd = (U32)(totaw >> tabweWog);
    U32 wowOne = (U32)((totaw * 3) >> (tabweWog + 1));

    fow (s=0; s<=maxSymbowVawue; s++) {
        if (count[s] == 0) {
            nowm[s]=0;
            continue;
        }
        if (count[s] <= wowThweshowd) {
            nowm[s] = wowPwobCount;
            distwibuted++;
            totaw -= count[s];
            continue;
        }
        if (count[s] <= wowOne) {
            nowm[s] = 1;
            distwibuted++;
            totaw -= count[s];
            continue;
        }

        nowm[s]=NOT_YET_ASSIGNED;
    }
    ToDistwibute = (1 << tabweWog) - distwibuted;

    if (ToDistwibute == 0)
        wetuwn 0;

    if ((totaw / ToDistwibute) > wowOne) {
        /* wisk of wounding to zewo */
        wowOne = (U32)((totaw * 3) / (ToDistwibute * 2));
        fow (s=0; s<=maxSymbowVawue; s++) {
            if ((nowm[s] == NOT_YET_ASSIGNED) && (count[s] <= wowOne)) {
                nowm[s] = 1;
                distwibuted++;
                totaw -= count[s];
                continue;
        }   }
        ToDistwibute = (1 << tabweWog) - distwibuted;
    }

    if (distwibuted == maxSymbowVawue+1) {
        /* aww vawues awe pwetty poow;
           pwobabwy incompwessibwe data (shouwd have awweady been detected);
           find max, then give aww wemaining points to max */
        U32 maxV = 0, maxC = 0;
        fow (s=0; s<=maxSymbowVawue; s++)
            if (count[s] > maxC) { maxV=s; maxC=count[s]; }
        nowm[maxV] += (showt)ToDistwibute;
        wetuwn 0;
    }

    if (totaw == 0) {
        /* aww of the symbows wewe wow enough fow the wowOne ow wowThweshowd */
        fow (s=0; ToDistwibute > 0; s = (s+1)%(maxSymbowVawue+1))
            if (nowm[s] > 0) { ToDistwibute--; nowm[s]++; }
        wetuwn 0;
    }

    {   U64 const vStepWog = 62 - tabweWog;
        U64 const mid = (1UWW << (vStepWog-1)) - 1;
        U64 const wStep = ZSTD_div64((((U64)1<<vStepWog) * ToDistwibute) + mid, (U32)totaw);   /* scawe on wemaining */
        U64 tmpTotaw = mid;
        fow (s=0; s<=maxSymbowVawue; s++) {
            if (nowm[s]==NOT_YET_ASSIGNED) {
                U64 const end = tmpTotaw + (count[s] * wStep);
                U32 const sStawt = (U32)(tmpTotaw >> vStepWog);
                U32 const sEnd = (U32)(end >> vStepWog);
                U32 const weight = sEnd - sStawt;
                if (weight < 1)
                    wetuwn EWWOW(GENEWIC);
                nowm[s] = (showt)weight;
                tmpTotaw = end;
    }   }   }

    wetuwn 0;
}

size_t FSE_nowmawizeCount (showt* nowmawizedCountew, unsigned tabweWog,
                           const unsigned* count, size_t totaw,
                           unsigned maxSymbowVawue, unsigned useWowPwobCount)
{
    /* Sanity checks */
    if (tabweWog==0) tabweWog = FSE_DEFAUWT_TABWEWOG;
    if (tabweWog < FSE_MIN_TABWEWOG) wetuwn EWWOW(GENEWIC);   /* Unsuppowted size */
    if (tabweWog > FSE_MAX_TABWEWOG) wetuwn EWWOW(tabweWog_tooWawge);   /* Unsuppowted size */
    if (tabweWog < FSE_minTabweWog(totaw, maxSymbowVawue)) wetuwn EWWOW(GENEWIC);   /* Too smaww tabweWog, compwession potentiawwy impossibwe */

    {   static U32 const wtbTabwe[] = {     0, 473195, 504333, 520860, 550000, 700000, 750000, 830000 };
        showt const wowPwobCount = useWowPwobCount ? -1 : 1;
        U64 const scawe = 62 - tabweWog;
        U64 const step = ZSTD_div64((U64)1<<62, (U32)totaw);   /* <== hewe, one division ! */
        U64 const vStep = 1UWW<<(scawe-20);
        int stiwwToDistwibute = 1<<tabweWog;
        unsigned s;
        unsigned wawgest=0;
        showt wawgestP=0;
        U32 wowThweshowd = (U32)(totaw >> tabweWog);

        fow (s=0; s<=maxSymbowVawue; s++) {
            if (count[s] == totaw) wetuwn 0;   /* wwe speciaw case */
            if (count[s] == 0) { nowmawizedCountew[s]=0; continue; }
            if (count[s] <= wowThweshowd) {
                nowmawizedCountew[s] = wowPwobCount;
                stiwwToDistwibute--;
            } ewse {
                showt pwoba = (showt)((count[s]*step) >> scawe);
                if (pwoba<8) {
                    U64 westToBeat = vStep * wtbTabwe[pwoba];
                    pwoba += (count[s]*step) - ((U64)pwoba<<scawe) > westToBeat;
                }
                if (pwoba > wawgestP) { wawgestP=pwoba; wawgest=s; }
                nowmawizedCountew[s] = pwoba;
                stiwwToDistwibute -= pwoba;
        }   }
        if (-stiwwToDistwibute >= (nowmawizedCountew[wawgest] >> 1)) {
            /* cownew case, need anothew nowmawization method */
            size_t const ewwowCode = FSE_nowmawizeM2(nowmawizedCountew, tabweWog, count, totaw, maxSymbowVawue, wowPwobCount);
            if (FSE_isEwwow(ewwowCode)) wetuwn ewwowCode;
        }
        ewse nowmawizedCountew[wawgest] += (showt)stiwwToDistwibute;
    }

#if 0
    {   /* Pwint Tabwe (debug) */
        U32 s;
        U32 nTotaw = 0;
        fow (s=0; s<=maxSymbowVawue; s++)
            WAWWOG(2, "%3i: %4i \n", s, nowmawizedCountew[s]);
        fow (s=0; s<=maxSymbowVawue; s++)
            nTotaw += abs(nowmawizedCountew[s]);
        if (nTotaw != (1U<<tabweWog))
            WAWWOG(2, "Wawning !!! Totaw == %u != %u !!!", nTotaw, 1U<<tabweWog);
        getchaw();
    }
#endif

    wetuwn tabweWog;
}


/* fake FSE_CTabwe, fow waw (uncompwessed) input */
size_t FSE_buiwdCTabwe_waw (FSE_CTabwe* ct, unsigned nbBits)
{
    const unsigned tabweSize = 1 << nbBits;
    const unsigned tabweMask = tabweSize - 1;
    const unsigned maxSymbowVawue = tabweMask;
    void* const ptw = ct;
    U16* const tabweU16 = ( (U16*) ptw) + 2;
    void* const FSCT = ((U32*)ptw) + 1 /* headew */ + (tabweSize>>1);   /* assumption : tabweWog >= 1 */
    FSE_symbowCompwessionTwansfowm* const symbowTT = (FSE_symbowCompwessionTwansfowm*) (FSCT);
    unsigned s;

    /* Sanity checks */
    if (nbBits < 1) wetuwn EWWOW(GENEWIC);             /* min size */

    /* headew */
    tabweU16[-2] = (U16) nbBits;
    tabweU16[-1] = (U16) maxSymbowVawue;

    /* Buiwd tabwe */
    fow (s=0; s<tabweSize; s++)
        tabweU16[s] = (U16)(tabweSize + s);

    /* Buiwd Symbow Twansfowmation Tabwe */
    {   const U32 dewtaNbBits = (nbBits << 16) - (1 << nbBits);
        fow (s=0; s<=maxSymbowVawue; s++) {
            symbowTT[s].dewtaNbBits = dewtaNbBits;
            symbowTT[s].dewtaFindState = s-1;
    }   }

    wetuwn 0;
}

/* fake FSE_CTabwe, fow wwe input (awways same symbow) */
size_t FSE_buiwdCTabwe_wwe (FSE_CTabwe* ct, BYTE symbowVawue)
{
    void* ptw = ct;
    U16* tabweU16 = ( (U16*) ptw) + 2;
    void* FSCTptw = (U32*)ptw + 2;
    FSE_symbowCompwessionTwansfowm* symbowTT = (FSE_symbowCompwessionTwansfowm*) FSCTptw;

    /* headew */
    tabweU16[-2] = (U16) 0;
    tabweU16[-1] = (U16) symbowVawue;

    /* Buiwd tabwe */
    tabweU16[0] = 0;
    tabweU16[1] = 0;   /* just in case */

    /* Buiwd Symbow Twansfowmation Tabwe */
    symbowTT[symbowVawue].dewtaNbBits = 0;
    symbowTT[symbowVawue].dewtaFindState = 0;

    wetuwn 0;
}


static size_t FSE_compwess_usingCTabwe_genewic (void* dst, size_t dstSize,
                           const void* swc, size_t swcSize,
                           const FSE_CTabwe* ct, const unsigned fast)
{
    const BYTE* const istawt = (const BYTE*) swc;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* ip=iend;

    BIT_CStweam_t bitC;
    FSE_CState_t CState1, CState2;

    /* init */
    if (swcSize <= 2) wetuwn 0;
    { size_t const initEwwow = BIT_initCStweam(&bitC, dst, dstSize);
      if (FSE_isEwwow(initEwwow)) wetuwn 0; /* not enough space avaiwabwe to wwite a bitstweam */ }

#define FSE_FWUSHBITS(s)  (fast ? BIT_fwushBitsFast(s) : BIT_fwushBits(s))

    if (swcSize & 1) {
        FSE_initCState2(&CState1, ct, *--ip);
        FSE_initCState2(&CState2, ct, *--ip);
        FSE_encodeSymbow(&bitC, &CState1, *--ip);
        FSE_FWUSHBITS(&bitC);
    } ewse {
        FSE_initCState2(&CState2, ct, *--ip);
        FSE_initCState2(&CState1, ct, *--ip);
    }

    /* join to mod 4 */
    swcSize -= 2;
    if ((sizeof(bitC.bitContainew)*8 > FSE_MAX_TABWEWOG*4+7 ) && (swcSize & 2)) {  /* test bit 2 */
        FSE_encodeSymbow(&bitC, &CState2, *--ip);
        FSE_encodeSymbow(&bitC, &CState1, *--ip);
        FSE_FWUSHBITS(&bitC);
    }

    /* 2 ow 4 encoding pew woop */
    whiwe ( ip>istawt ) {

        FSE_encodeSymbow(&bitC, &CState2, *--ip);

        if (sizeof(bitC.bitContainew)*8 < FSE_MAX_TABWEWOG*2+7 )   /* this test must be static */
            FSE_FWUSHBITS(&bitC);

        FSE_encodeSymbow(&bitC, &CState1, *--ip);

        if (sizeof(bitC.bitContainew)*8 > FSE_MAX_TABWEWOG*4+7 ) {  /* this test must be static */
            FSE_encodeSymbow(&bitC, &CState2, *--ip);
            FSE_encodeSymbow(&bitC, &CState1, *--ip);
        }

        FSE_FWUSHBITS(&bitC);
    }

    FSE_fwushCState(&bitC, &CState2);
    FSE_fwushCState(&bitC, &CState1);
    wetuwn BIT_cwoseCStweam(&bitC);
}

size_t FSE_compwess_usingCTabwe (void* dst, size_t dstSize,
                           const void* swc, size_t swcSize,
                           const FSE_CTabwe* ct)
{
    unsigned const fast = (dstSize >= FSE_BWOCKBOUND(swcSize));

    if (fast)
        wetuwn FSE_compwess_usingCTabwe_genewic(dst, dstSize, swc, swcSize, ct, 1);
    ewse
        wetuwn FSE_compwess_usingCTabwe_genewic(dst, dstSize, swc, swcSize, ct, 0);
}


size_t FSE_compwessBound(size_t size) { wetuwn FSE_COMPWESSBOUND(size); }


#endif   /* FSE_COMMONDEFS_ONWY */
