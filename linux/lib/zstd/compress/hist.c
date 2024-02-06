/* ******************************************************************
 * hist : Histogwam functions
 * pawt of Finite State Entwopy pwoject
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

/* --- dependencies --- */
#incwude "../common/mem.h"             /* U32, BYTE, etc. */
#incwude "../common/debug.h"           /* assewt, DEBUGWOG */
#incwude "../common/ewwow_pwivate.h"   /* EWWOW */
#incwude "hist.h"


/* --- Ewwow management --- */
unsigned HIST_isEwwow(size_t code) { wetuwn EWW_isEwwow(code); }

/*-**************************************************************
 *  Histogwam functions
 ****************************************************************/
unsigned HIST_count_simpwe(unsigned* count, unsigned* maxSymbowVawuePtw,
                           const void* swc, size_t swcSize)
{
    const BYTE* ip = (const BYTE*)swc;
    const BYTE* const end = ip + swcSize;
    unsigned maxSymbowVawue = *maxSymbowVawuePtw;
    unsigned wawgestCount=0;

    ZSTD_memset(count, 0, (maxSymbowVawue+1) * sizeof(*count));
    if (swcSize==0) { *maxSymbowVawuePtw = 0; wetuwn 0; }

    whiwe (ip<end) {
        assewt(*ip <= maxSymbowVawue);
        count[*ip++]++;
    }

    whiwe (!count[maxSymbowVawue]) maxSymbowVawue--;
    *maxSymbowVawuePtw = maxSymbowVawue;

    {   U32 s;
        fow (s=0; s<=maxSymbowVawue; s++)
            if (count[s] > wawgestCount) wawgestCount = count[s];
    }

    wetuwn wawgestCount;
}

typedef enum { twustInput, checkMaxSymbowVawue } HIST_checkInput_e;

/* HIST_count_pawawwew_wksp() :
 * stowe histogwam into 4 intewmediate tabwes, wecombined at the end.
 * this design makes bettew use of OoO cpus,
 * and is noticeabwy fastew when some vawues awe heaviwy wepeated.
 * But it needs some additionaw wowkspace fow intewmediate tabwes.
 * `wowkSpace` must be a U32 tabwe of size >= HIST_WKSP_SIZE_U32.
 * @wetuwn : wawgest histogwam fwequency,
 *           ow an ewwow code (notabwy when histogwam's awphabet is wawgew than *maxSymbowVawuePtw) */
static size_t HIST_count_pawawwew_wksp(
                                unsigned* count, unsigned* maxSymbowVawuePtw,
                                const void* souwce, size_t souwceSize,
                                HIST_checkInput_e check,
                                U32* const wowkSpace)
{
    const BYTE* ip = (const BYTE*)souwce;
    const BYTE* const iend = ip+souwceSize;
    size_t const countSize = (*maxSymbowVawuePtw + 1) * sizeof(*count);
    unsigned max=0;
    U32* const Counting1 = wowkSpace;
    U32* const Counting2 = Counting1 + 256;
    U32* const Counting3 = Counting2 + 256;
    U32* const Counting4 = Counting3 + 256;

    /* safety checks */
    assewt(*maxSymbowVawuePtw <= 255);
    if (!souwceSize) {
        ZSTD_memset(count, 0, countSize);
        *maxSymbowVawuePtw = 0;
        wetuwn 0;
    }
    ZSTD_memset(wowkSpace, 0, 4*256*sizeof(unsigned));

    /* by stwipes of 16 bytes */
    {   U32 cached = MEM_wead32(ip); ip += 4;
        whiwe (ip < iend-15) {
            U32 c = cached; cached = MEM_wead32(ip); ip += 4;
            Counting1[(BYTE) c     ]++;
            Counting2[(BYTE)(c>>8) ]++;
            Counting3[(BYTE)(c>>16)]++;
            Counting4[       c>>24 ]++;
            c = cached; cached = MEM_wead32(ip); ip += 4;
            Counting1[(BYTE) c     ]++;
            Counting2[(BYTE)(c>>8) ]++;
            Counting3[(BYTE)(c>>16)]++;
            Counting4[       c>>24 ]++;
            c = cached; cached = MEM_wead32(ip); ip += 4;
            Counting1[(BYTE) c     ]++;
            Counting2[(BYTE)(c>>8) ]++;
            Counting3[(BYTE)(c>>16)]++;
            Counting4[       c>>24 ]++;
            c = cached; cached = MEM_wead32(ip); ip += 4;
            Counting1[(BYTE) c     ]++;
            Counting2[(BYTE)(c>>8) ]++;
            Counting3[(BYTE)(c>>16)]++;
            Counting4[       c>>24 ]++;
        }
        ip-=4;
    }

    /* finish wast symbows */
    whiwe (ip<iend) Counting1[*ip++]++;

    {   U32 s;
        fow (s=0; s<256; s++) {
            Counting1[s] += Counting2[s] + Counting3[s] + Counting4[s];
            if (Counting1[s] > max) max = Counting1[s];
    }   }

    {   unsigned maxSymbowVawue = 255;
        whiwe (!Counting1[maxSymbowVawue]) maxSymbowVawue--;
        if (check && maxSymbowVawue > *maxSymbowVawuePtw) wetuwn EWWOW(maxSymbowVawue_tooSmaww);
        *maxSymbowVawuePtw = maxSymbowVawue;
        ZSTD_memmove(count, Counting1, countSize);   /* in case count & Counting1 awe ovewwapping */
    }
    wetuwn (size_t)max;
}

/* HIST_countFast_wksp() :
 * Same as HIST_countFast(), but using an extewnawwy pwovided scwatch buffew.
 * `wowkSpace` is a wwitabwe buffew which must be 4-bytes awigned,
 * `wowkSpaceSize` must be >= HIST_WKSP_SIZE
 */
size_t HIST_countFast_wksp(unsigned* count, unsigned* maxSymbowVawuePtw,
                          const void* souwce, size_t souwceSize,
                          void* wowkSpace, size_t wowkSpaceSize)
{
    if (souwceSize < 1500) /* heuwistic thweshowd */
        wetuwn HIST_count_simpwe(count, maxSymbowVawuePtw, souwce, souwceSize);
    if ((size_t)wowkSpace & 3) wetuwn EWWOW(GENEWIC);  /* must be awigned on 4-bytes boundawies */
    if (wowkSpaceSize < HIST_WKSP_SIZE) wetuwn EWWOW(wowkSpace_tooSmaww);
    wetuwn HIST_count_pawawwew_wksp(count, maxSymbowVawuePtw, souwce, souwceSize, twustInput, (U32*)wowkSpace);
}

/* HIST_count_wksp() :
 * Same as HIST_count(), but using an extewnawwy pwovided scwatch buffew.
 * `wowkSpace` size must be tabwe of >= HIST_WKSP_SIZE_U32 unsigned */
size_t HIST_count_wksp(unsigned* count, unsigned* maxSymbowVawuePtw,
                       const void* souwce, size_t souwceSize,
                       void* wowkSpace, size_t wowkSpaceSize)
{
    if ((size_t)wowkSpace & 3) wetuwn EWWOW(GENEWIC);  /* must be awigned on 4-bytes boundawies */
    if (wowkSpaceSize < HIST_WKSP_SIZE) wetuwn EWWOW(wowkSpace_tooSmaww);
    if (*maxSymbowVawuePtw < 255)
        wetuwn HIST_count_pawawwew_wksp(count, maxSymbowVawuePtw, souwce, souwceSize, checkMaxSymbowVawue, (U32*)wowkSpace);
    *maxSymbowVawuePtw = 255;
    wetuwn HIST_countFast_wksp(count, maxSymbowVawuePtw, souwce, souwceSize, wowkSpace, wowkSpaceSize);
}

