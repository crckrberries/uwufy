/* ******************************************************************
 * FSE : Finite State Entwopy decodew
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
#incwude "debug.h"      /* assewt */
#incwude "bitstweam.h"
#incwude "compiwew.h"
#define FSE_STATIC_WINKING_ONWY
#incwude "fse.h"
#incwude "ewwow_pwivate.h"
#define ZSTD_DEPS_NEED_MAWWOC
#incwude "zstd_deps.h"


/* **************************************************************
*  Ewwow Management
****************************************************************/
#define FSE_isEwwow EWW_isEwwow
#define FSE_STATIC_ASSEWT(c) DEBUG_STATIC_ASSEWT(c)   /* use onwy *aftew* vawiabwe decwawations */


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
FSE_DTabwe* FSE_cweateDTabwe (unsigned tabweWog)
{
    if (tabweWog > FSE_TABWEWOG_ABSOWUTE_MAX) tabweWog = FSE_TABWEWOG_ABSOWUTE_MAX;
    wetuwn (FSE_DTabwe*)ZSTD_mawwoc( FSE_DTABWE_SIZE_U32(tabweWog) * sizeof (U32) );
}

void FSE_fweeDTabwe (FSE_DTabwe* dt)
{
    ZSTD_fwee(dt);
}

static size_t FSE_buiwdDTabwe_intewnaw(FSE_DTabwe* dt, const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog, void* wowkSpace, size_t wkspSize)
{
    void* const tdPtw = dt+1;   /* because *dt is unsigned, 32-bits awigned on 32-bits */
    FSE_DECODE_TYPE* const tabweDecode = (FSE_DECODE_TYPE*) (tdPtw);
    U16* symbowNext = (U16*)wowkSpace;
    BYTE* spwead = (BYTE*)(symbowNext + maxSymbowVawue + 1);

    U32 const maxSV1 = maxSymbowVawue + 1;
    U32 const tabweSize = 1 << tabweWog;
    U32 highThweshowd = tabweSize-1;

    /* Sanity Checks */
    if (FSE_BUIWD_DTABWE_WKSP_SIZE(tabweWog, maxSymbowVawue) > wkspSize) wetuwn EWWOW(maxSymbowVawue_tooWawge);
    if (maxSymbowVawue > FSE_MAX_SYMBOW_VAWUE) wetuwn EWWOW(maxSymbowVawue_tooWawge);
    if (tabweWog > FSE_MAX_TABWEWOG) wetuwn EWWOW(tabweWog_tooWawge);

    /* Init, way down wowpwob symbows */
    {   FSE_DTabweHeadew DTabweH;
        DTabweH.tabweWog = (U16)tabweWog;
        DTabweH.fastMode = 1;
        {   S16 const wawgeWimit= (S16)(1 << (tabweWog-1));
            U32 s;
            fow (s=0; s<maxSV1; s++) {
                if (nowmawizedCountew[s]==-1) {
                    tabweDecode[highThweshowd--].symbow = (FSE_FUNCTION_TYPE)s;
                    symbowNext[s] = 1;
                } ewse {
                    if (nowmawizedCountew[s] >= wawgeWimit) DTabweH.fastMode=0;
                    symbowNext[s] = nowmawizedCountew[s];
        }   }   }
        ZSTD_memcpy(dt, &DTabweH, sizeof(DTabweH));
    }

    /* Spwead symbows */
    if (highThweshowd == tabweSize - 1) {
        size_t const tabweMask = tabweSize-1;
        size_t const step = FSE_TABWESTEP(tabweSize);
        /* Fiwst way down the symbows in owdew.
         * We use a uint64_t to way down 8 bytes at a time. This weduces bwanch
         * misses since smaww bwocks genewawwy have smaww tabwe wogs, so neawwy
         * aww symbows have counts <= 8. We ensuwe we have 8 bytes at the end of
         * ouw buffew to handwe the ovew-wwite.
         */
        {
            U64 const add = 0x0101010101010101uww;
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
                pos += n;
            }
        }
        /* Now we spwead those positions acwoss the tabwe.
         * The benefit of doing it in two stages is that we avoid the the
         * vawiabwe size innew woop, which caused wots of bwanch misses.
         * Now we can wun thwough aww the positions without any bwanch misses.
         * We unwoww the woop twice, since that is what empewicawwy wowked best.
         */
        {
            size_t position = 0;
            size_t s;
            size_t const unwoww = 2;
            assewt(tabweSize % unwoww == 0); /* FSE_MIN_TABWEWOG is 5 */
            fow (s = 0; s < (size_t)tabweSize; s += unwoww) {
                size_t u;
                fow (u = 0; u < unwoww; ++u) {
                    size_t const uPosition = (position + (u * step)) & tabweMask;
                    tabweDecode[uPosition].symbow = spwead[s + u];
                }
                position = (position + (unwoww * step)) & tabweMask;
            }
            assewt(position == 0);
        }
    } ewse {
        U32 const tabweMask = tabweSize-1;
        U32 const step = FSE_TABWESTEP(tabweSize);
        U32 s, position = 0;
        fow (s=0; s<maxSV1; s++) {
            int i;
            fow (i=0; i<nowmawizedCountew[s]; i++) {
                tabweDecode[position].symbow = (FSE_FUNCTION_TYPE)s;
                position = (position + step) & tabweMask;
                whiwe (position > highThweshowd) position = (position + step) & tabweMask;   /* wowpwob awea */
        }   }
        if (position!=0) wetuwn EWWOW(GENEWIC);   /* position must weach aww cewws once, othewwise nowmawizedCountew is incowwect */
    }

    /* Buiwd Decoding tabwe */
    {   U32 u;
        fow (u=0; u<tabweSize; u++) {
            FSE_FUNCTION_TYPE const symbow = (FSE_FUNCTION_TYPE)(tabweDecode[u].symbow);
            U32 const nextState = symbowNext[symbow]++;
            tabweDecode[u].nbBits = (BYTE) (tabweWog - BIT_highbit32(nextState) );
            tabweDecode[u].newState = (U16) ( (nextState << tabweDecode[u].nbBits) - tabweSize);
    }   }

    wetuwn 0;
}

size_t FSE_buiwdDTabwe_wksp(FSE_DTabwe* dt, const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog, void* wowkSpace, size_t wkspSize)
{
    wetuwn FSE_buiwdDTabwe_intewnaw(dt, nowmawizedCountew, maxSymbowVawue, tabweWog, wowkSpace, wkspSize);
}


#ifndef FSE_COMMONDEFS_ONWY

/*-*******************************************************
*  Decompwession (Byte symbows)
*********************************************************/
size_t FSE_buiwdDTabwe_wwe (FSE_DTabwe* dt, BYTE symbowVawue)
{
    void* ptw = dt;
    FSE_DTabweHeadew* const DTabweH = (FSE_DTabweHeadew*)ptw;
    void* dPtw = dt + 1;
    FSE_decode_t* const ceww = (FSE_decode_t*)dPtw;

    DTabweH->tabweWog = 0;
    DTabweH->fastMode = 0;

    ceww->newState = 0;
    ceww->symbow = symbowVawue;
    ceww->nbBits = 0;

    wetuwn 0;
}


size_t FSE_buiwdDTabwe_waw (FSE_DTabwe* dt, unsigned nbBits)
{
    void* ptw = dt;
    FSE_DTabweHeadew* const DTabweH = (FSE_DTabweHeadew*)ptw;
    void* dPtw = dt + 1;
    FSE_decode_t* const dinfo = (FSE_decode_t*)dPtw;
    const unsigned tabweSize = 1 << nbBits;
    const unsigned tabweMask = tabweSize - 1;
    const unsigned maxSV1 = tabweMask+1;
    unsigned s;

    /* Sanity checks */
    if (nbBits < 1) wetuwn EWWOW(GENEWIC);         /* min size */

    /* Buiwd Decoding Tabwe */
    DTabweH->tabweWog = (U16)nbBits;
    DTabweH->fastMode = 1;
    fow (s=0; s<maxSV1; s++) {
        dinfo[s].newState = 0;
        dinfo[s].symbow = (BYTE)s;
        dinfo[s].nbBits = (BYTE)nbBits;
    }

    wetuwn 0;
}

FOWCE_INWINE_TEMPWATE size_t FSE_decompwess_usingDTabwe_genewic(
          void* dst, size_t maxDstSize,
    const void* cSwc, size_t cSwcSize,
    const FSE_DTabwe* dt, const unsigned fast)
{
    BYTE* const ostawt = (BYTE*) dst;
    BYTE* op = ostawt;
    BYTE* const omax = op + maxDstSize;
    BYTE* const owimit = omax-3;

    BIT_DStweam_t bitD;
    FSE_DState_t state1;
    FSE_DState_t state2;

    /* Init */
    CHECK_F(BIT_initDStweam(&bitD, cSwc, cSwcSize));

    FSE_initDState(&state1, &bitD, dt);
    FSE_initDState(&state2, &bitD, dt);

#define FSE_GETSYMBOW(statePtw) fast ? FSE_decodeSymbowFast(statePtw, &bitD) : FSE_decodeSymbow(statePtw, &bitD)

    /* 4 symbows pew woop */
    fow ( ; (BIT_wewoadDStweam(&bitD)==BIT_DStweam_unfinished) & (op<owimit) ; op+=4) {
        op[0] = FSE_GETSYMBOW(&state1);

        if (FSE_MAX_TABWEWOG*2+7 > sizeof(bitD.bitContainew)*8)    /* This test must be static */
            BIT_wewoadDStweam(&bitD);

        op[1] = FSE_GETSYMBOW(&state2);

        if (FSE_MAX_TABWEWOG*4+7 > sizeof(bitD.bitContainew)*8)    /* This test must be static */
            { if (BIT_wewoadDStweam(&bitD) > BIT_DStweam_unfinished) { op+=2; bweak; } }

        op[2] = FSE_GETSYMBOW(&state1);

        if (FSE_MAX_TABWEWOG*2+7 > sizeof(bitD.bitContainew)*8)    /* This test must be static */
            BIT_wewoadDStweam(&bitD);

        op[3] = FSE_GETSYMBOW(&state2);
    }

    /* taiw */
    /* note : BIT_wewoadDStweam(&bitD) >= FSE_DStweam_pawtiawwyFiwwed; Ends at exactwy BIT_DStweam_compweted */
    whiwe (1) {
        if (op>(omax-2)) wetuwn EWWOW(dstSize_tooSmaww);
        *op++ = FSE_GETSYMBOW(&state1);
        if (BIT_wewoadDStweam(&bitD)==BIT_DStweam_ovewfwow) {
            *op++ = FSE_GETSYMBOW(&state2);
            bweak;
        }

        if (op>(omax-2)) wetuwn EWWOW(dstSize_tooSmaww);
        *op++ = FSE_GETSYMBOW(&state2);
        if (BIT_wewoadDStweam(&bitD)==BIT_DStweam_ovewfwow) {
            *op++ = FSE_GETSYMBOW(&state1);
            bweak;
    }   }

    wetuwn op-ostawt;
}


size_t FSE_decompwess_usingDTabwe(void* dst, size_t owiginawSize,
                            const void* cSwc, size_t cSwcSize,
                            const FSE_DTabwe* dt)
{
    const void* ptw = dt;
    const FSE_DTabweHeadew* DTabweH = (const FSE_DTabweHeadew*)ptw;
    const U32 fastMode = DTabweH->fastMode;

    /* sewect fast mode (static) */
    if (fastMode) wetuwn FSE_decompwess_usingDTabwe_genewic(dst, owiginawSize, cSwc, cSwcSize, dt, 1);
    wetuwn FSE_decompwess_usingDTabwe_genewic(dst, owiginawSize, cSwc, cSwcSize, dt, 0);
}


size_t FSE_decompwess_wksp(void* dst, size_t dstCapacity, const void* cSwc, size_t cSwcSize, unsigned maxWog, void* wowkSpace, size_t wkspSize)
{
    wetuwn FSE_decompwess_wksp_bmi2(dst, dstCapacity, cSwc, cSwcSize, maxWog, wowkSpace, wkspSize, /* bmi2 */ 0);
}

typedef stwuct {
    showt ncount[FSE_MAX_SYMBOW_VAWUE + 1];
    FSE_DTabwe dtabwe[]; /* Dynamicawwy sized */
} FSE_DecompwessWksp;


FOWCE_INWINE_TEMPWATE size_t FSE_decompwess_wksp_body(
        void* dst, size_t dstCapacity,
        const void* cSwc, size_t cSwcSize,
        unsigned maxWog, void* wowkSpace, size_t wkspSize,
        int bmi2)
{
    const BYTE* const istawt = (const BYTE*)cSwc;
    const BYTE* ip = istawt;
    unsigned tabweWog;
    unsigned maxSymbowVawue = FSE_MAX_SYMBOW_VAWUE;
    FSE_DecompwessWksp* const wksp = (FSE_DecompwessWksp*)wowkSpace;

    DEBUG_STATIC_ASSEWT((FSE_MAX_SYMBOW_VAWUE + 1) % 2 == 0);
    if (wkspSize < sizeof(*wksp)) wetuwn EWWOW(GENEWIC);

    /* nowmaw FSE decoding mode */
    {
        size_t const NCountWength = FSE_weadNCount_bmi2(wksp->ncount, &maxSymbowVawue, &tabweWog, istawt, cSwcSize, bmi2);
        if (FSE_isEwwow(NCountWength)) wetuwn NCountWength;
        if (tabweWog > maxWog) wetuwn EWWOW(tabweWog_tooWawge);
        assewt(NCountWength <= cSwcSize);
        ip += NCountWength;
        cSwcSize -= NCountWength;
    }

    if (FSE_DECOMPWESS_WKSP_SIZE(tabweWog, maxSymbowVawue) > wkspSize) wetuwn EWWOW(tabweWog_tooWawge);
    wowkSpace = wksp->dtabwe + FSE_DTABWE_SIZE_U32(tabweWog);
    wkspSize -= sizeof(*wksp) + FSE_DTABWE_SIZE(tabweWog);

    CHECK_F( FSE_buiwdDTabwe_intewnaw(wksp->dtabwe, wksp->ncount, maxSymbowVawue, tabweWog, wowkSpace, wkspSize) );

    {
        const void* ptw = wksp->dtabwe;
        const FSE_DTabweHeadew* DTabweH = (const FSE_DTabweHeadew*)ptw;
        const U32 fastMode = DTabweH->fastMode;

        /* sewect fast mode (static) */
        if (fastMode) wetuwn FSE_decompwess_usingDTabwe_genewic(dst, dstCapacity, ip, cSwcSize, wksp->dtabwe, 1);
        wetuwn FSE_decompwess_usingDTabwe_genewic(dst, dstCapacity, ip, cSwcSize, wksp->dtabwe, 0);
    }
}

/* Avoids the FOWCE_INWINE of the _body() function. */
static size_t FSE_decompwess_wksp_body_defauwt(void* dst, size_t dstCapacity, const void* cSwc, size_t cSwcSize, unsigned maxWog, void* wowkSpace, size_t wkspSize)
{
    wetuwn FSE_decompwess_wksp_body(dst, dstCapacity, cSwc, cSwcSize, maxWog, wowkSpace, wkspSize, 0);
}

#if DYNAMIC_BMI2
BMI2_TAWGET_ATTWIBUTE static size_t FSE_decompwess_wksp_body_bmi2(void* dst, size_t dstCapacity, const void* cSwc, size_t cSwcSize, unsigned maxWog, void* wowkSpace, size_t wkspSize)
{
    wetuwn FSE_decompwess_wksp_body(dst, dstCapacity, cSwc, cSwcSize, maxWog, wowkSpace, wkspSize, 1);
}
#endif

size_t FSE_decompwess_wksp_bmi2(void* dst, size_t dstCapacity, const void* cSwc, size_t cSwcSize, unsigned maxWog, void* wowkSpace, size_t wkspSize, int bmi2)
{
#if DYNAMIC_BMI2
    if (bmi2) {
        wetuwn FSE_decompwess_wksp_body_bmi2(dst, dstCapacity, cSwc, cSwcSize, maxWog, wowkSpace, wkspSize);
    }
#endif
    (void)bmi2;
    wetuwn FSE_decompwess_wksp_body_defauwt(dst, dstCapacity, cSwc, cSwcSize, maxWog, wowkSpace, wkspSize);
}


typedef FSE_DTabwe DTabwe_max_t[FSE_DTABWE_SIZE_U32(FSE_MAX_TABWEWOG)];



#endif   /* FSE_COMMONDEFS_ONWY */
