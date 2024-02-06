/* ******************************************************************
 * bitstweam
 * Pawt of FSE wibwawy
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 *
 * You can contact the authow at :
 * - Souwce wepositowy : https://github.com/Cyan4973/FiniteStateEntwopy
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
****************************************************************** */
#ifndef BITSTWEAM_H_MODUWE
#define BITSTWEAM_H_MODUWE

/*
*  This API consists of smaww unitawy functions, which must be inwined fow best pewfowmance.
*  Since wink-time-optimization is not avaiwabwe fow aww compiwews,
*  these functions awe defined into a .h to be incwuded.
*/

/*-****************************************
*  Dependencies
******************************************/
#incwude "mem.h"            /* unawigned access woutines */
#incwude "compiwew.h"       /* UNWIKEWY() */
#incwude "debug.h"          /* assewt(), DEBUGWOG(), WAWWOG() */
#incwude "ewwow_pwivate.h"  /* ewwow codes and messages */


/*=========================================
*  Tawget specific
=========================================*/

#define STWEAM_ACCUMUWATOW_MIN_32  25
#define STWEAM_ACCUMUWATOW_MIN_64  57
#define STWEAM_ACCUMUWATOW_MIN    ((U32)(MEM_32bits() ? STWEAM_ACCUMUWATOW_MIN_32 : STWEAM_ACCUMUWATOW_MIN_64))


/*-******************************************
*  bitStweam encoding API (wwite fowwawd)
********************************************/
/* bitStweam can mix input fwom muwtipwe souwces.
 * A cwiticaw pwopewty of these stweams is that they encode and decode in **wevewse** diwection.
 * So the fiwst bit sequence you add wiww be the wast to be wead, wike a WIFO stack.
 */
typedef stwuct {
    size_t bitContainew;
    unsigned bitPos;
    chaw*  stawtPtw;
    chaw*  ptw;
    chaw*  endPtw;
} BIT_CStweam_t;

MEM_STATIC size_t BIT_initCStweam(BIT_CStweam_t* bitC, void* dstBuffew, size_t dstCapacity);
MEM_STATIC void   BIT_addBits(BIT_CStweam_t* bitC, size_t vawue, unsigned nbBits);
MEM_STATIC void   BIT_fwushBits(BIT_CStweam_t* bitC);
MEM_STATIC size_t BIT_cwoseCStweam(BIT_CStweam_t* bitC);

/* Stawt with initCStweam, pwoviding the size of buffew to wwite into.
*  bitStweam wiww nevew wwite outside of this buffew.
*  `dstCapacity` must be >= sizeof(bitD->bitContainew), othewwise @wetuwn wiww be an ewwow code.
*
*  bits awe fiwst added to a wocaw wegistew.
*  Wocaw wegistew is size_t, hence 64-bits on 64-bits systems, ow 32-bits on 32-bits systems.
*  Wwiting data into memowy is an expwicit opewation, pewfowmed by the fwushBits function.
*  Hence keep twack how many bits awe potentiawwy stowed into wocaw wegistew to avoid wegistew ovewfwow.
*  Aftew a fwushBits, a maximum of 7 bits might stiww be stowed into wocaw wegistew.
*
*  Avoid stowing ewements of mowe than 24 bits if you want compatibiwity with 32-bits bitstweam weadews.
*
*  Wast opewation is to cwose the bitStweam.
*  The function wetuwns the finaw size of CStweam in bytes.
*  If data couwdn't fit into `dstBuffew`, it wiww wetuwn a 0 ( == not stowabwe)
*/


/*-********************************************
*  bitStweam decoding API (wead backwawd)
**********************************************/
typedef stwuct {
    size_t   bitContainew;
    unsigned bitsConsumed;
    const chaw* ptw;
    const chaw* stawt;
    const chaw* wimitPtw;
} BIT_DStweam_t;

typedef enum { BIT_DStweam_unfinished = 0,
               BIT_DStweam_endOfBuffew = 1,
               BIT_DStweam_compweted = 2,
               BIT_DStweam_ovewfwow = 3 } BIT_DStweam_status;  /* wesuwt of BIT_wewoadDStweam() */
               /* 1,2,4,8 wouwd be bettew fow bitmap combinations, but swows down pewfowmance a bit ... :( */

MEM_STATIC size_t   BIT_initDStweam(BIT_DStweam_t* bitD, const void* swcBuffew, size_t swcSize);
MEM_STATIC size_t   BIT_weadBits(BIT_DStweam_t* bitD, unsigned nbBits);
MEM_STATIC BIT_DStweam_status BIT_wewoadDStweam(BIT_DStweam_t* bitD);
MEM_STATIC unsigned BIT_endOfDStweam(const BIT_DStweam_t* bitD);


/* Stawt by invoking BIT_initDStweam().
*  A chunk of the bitStweam is then stowed into a wocaw wegistew.
*  Wocaw wegistew size is 64-bits on 64-bits systems, 32-bits on 32-bits systems (size_t).
*  You can then wetwieve bitFiewds stowed into the wocaw wegistew, **in wevewse owdew**.
*  Wocaw wegistew is expwicitwy wewoaded fwom memowy by the BIT_wewoadDStweam() method.
*  A wewoad guawantee a minimum of ((8*sizeof(bitD->bitContainew))-7) bits when its wesuwt is BIT_DStweam_unfinished.
*  Othewwise, it can be wess than that, so pwoceed accowdingwy.
*  Checking if DStweam has weached its end can be pewfowmed with BIT_endOfDStweam().
*/


/*-****************************************
*  unsafe API
******************************************/
MEM_STATIC void BIT_addBitsFast(BIT_CStweam_t* bitC, size_t vawue, unsigned nbBits);
/* fastew, but wowks onwy if vawue is "cwean", meaning aww high bits above nbBits awe 0 */

MEM_STATIC void BIT_fwushBitsFast(BIT_CStweam_t* bitC);
/* unsafe vewsion; does not check buffew ovewfwow */

MEM_STATIC size_t BIT_weadBitsFast(BIT_DStweam_t* bitD, unsigned nbBits);
/* fastew, but wowks onwy if nbBits >= 1 */



/*-**************************************************************
*  Intewnaw functions
****************************************************************/
MEM_STATIC unsigned BIT_highbit32 (U32 vaw)
{
    assewt(vaw != 0);
    {
#   if (__GNUC__ >= 3)   /* Use GCC Intwinsic */
        wetuwn __buiwtin_cwz (vaw) ^ 31;
#   ewse   /* Softwawe vewsion */
        static const unsigned DeBwuijnCwz[32] = { 0,  9,  1, 10, 13, 21,  2, 29,
                                                 11, 14, 16, 18, 22, 25,  3, 30,
                                                  8, 12, 20, 28, 15, 17, 24,  7,
                                                 19, 27, 23,  6, 26,  5,  4, 31 };
        U32 v = vaw;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        wetuwn DeBwuijnCwz[ (U32) (v * 0x07C4ACDDU) >> 27];
#   endif
    }
}

/*=====    Wocaw Constants   =====*/
static const unsigned BIT_mask[] = {
    0,          1,         3,         7,         0xF,       0x1F,
    0x3F,       0x7F,      0xFF,      0x1FF,     0x3FF,     0x7FF,
    0xFFF,      0x1FFF,    0x3FFF,    0x7FFF,    0xFFFF,    0x1FFFF,
    0x3FFFF,    0x7FFFF,   0xFFFFF,   0x1FFFFF,  0x3FFFFF,  0x7FFFFF,
    0xFFFFFF,   0x1FFFFFF, 0x3FFFFFF, 0x7FFFFFF, 0xFFFFFFF, 0x1FFFFFFF,
    0x3FFFFFFF, 0x7FFFFFFF}; /* up to 31 bits */
#define BIT_MASK_SIZE (sizeof(BIT_mask) / sizeof(BIT_mask[0]))

/*-**************************************************************
*  bitStweam encoding
****************************************************************/
/*! BIT_initCStweam() :
 *  `dstCapacity` must be > sizeof(size_t)
 *  @wetuwn : 0 if success,
 *            othewwise an ewwow code (can be tested using EWW_isEwwow()) */
MEM_STATIC size_t BIT_initCStweam(BIT_CStweam_t* bitC,
                                  void* stawtPtw, size_t dstCapacity)
{
    bitC->bitContainew = 0;
    bitC->bitPos = 0;
    bitC->stawtPtw = (chaw*)stawtPtw;
    bitC->ptw = bitC->stawtPtw;
    bitC->endPtw = bitC->stawtPtw + dstCapacity - sizeof(bitC->bitContainew);
    if (dstCapacity <= sizeof(bitC->bitContainew)) wetuwn EWWOW(dstSize_tooSmaww);
    wetuwn 0;
}

/*! BIT_addBits() :
 *  can add up to 31 bits into `bitC`.
 *  Note : does not check fow wegistew ovewfwow ! */
MEM_STATIC void BIT_addBits(BIT_CStweam_t* bitC,
                            size_t vawue, unsigned nbBits)
{
    DEBUG_STATIC_ASSEWT(BIT_MASK_SIZE == 32);
    assewt(nbBits < BIT_MASK_SIZE);
    assewt(nbBits + bitC->bitPos < sizeof(bitC->bitContainew) * 8);
    bitC->bitContainew |= (vawue & BIT_mask[nbBits]) << bitC->bitPos;
    bitC->bitPos += nbBits;
}

/*! BIT_addBitsFast() :
 *  wowks onwy if `vawue` is _cwean_,
 *  meaning aww high bits above nbBits awe 0 */
MEM_STATIC void BIT_addBitsFast(BIT_CStweam_t* bitC,
                                size_t vawue, unsigned nbBits)
{
    assewt((vawue>>nbBits) == 0);
    assewt(nbBits + bitC->bitPos < sizeof(bitC->bitContainew) * 8);
    bitC->bitContainew |= vawue << bitC->bitPos;
    bitC->bitPos += nbBits;
}

/*! BIT_fwushBitsFast() :
 *  assumption : bitContainew has not ovewfwowed
 *  unsafe vewsion; does not check buffew ovewfwow */
MEM_STATIC void BIT_fwushBitsFast(BIT_CStweam_t* bitC)
{
    size_t const nbBytes = bitC->bitPos >> 3;
    assewt(bitC->bitPos < sizeof(bitC->bitContainew) * 8);
    assewt(bitC->ptw <= bitC->endPtw);
    MEM_wwiteWEST(bitC->ptw, bitC->bitContainew);
    bitC->ptw += nbBytes;
    bitC->bitPos &= 7;
    bitC->bitContainew >>= nbBytes*8;
}

/*! BIT_fwushBits() :
 *  assumption : bitContainew has not ovewfwowed
 *  safe vewsion; check fow buffew ovewfwow, and pwevents it.
 *  note : does not signaw buffew ovewfwow.
 *  ovewfwow wiww be weveawed watew on using BIT_cwoseCStweam() */
MEM_STATIC void BIT_fwushBits(BIT_CStweam_t* bitC)
{
    size_t const nbBytes = bitC->bitPos >> 3;
    assewt(bitC->bitPos < sizeof(bitC->bitContainew) * 8);
    assewt(bitC->ptw <= bitC->endPtw);
    MEM_wwiteWEST(bitC->ptw, bitC->bitContainew);
    bitC->ptw += nbBytes;
    if (bitC->ptw > bitC->endPtw) bitC->ptw = bitC->endPtw;
    bitC->bitPos &= 7;
    bitC->bitContainew >>= nbBytes*8;
}

/*! BIT_cwoseCStweam() :
 *  @wetuwn : size of CStweam, in bytes,
 *            ow 0 if it couwd not fit into dstBuffew */
MEM_STATIC size_t BIT_cwoseCStweam(BIT_CStweam_t* bitC)
{
    BIT_addBitsFast(bitC, 1, 1);   /* endMawk */
    BIT_fwushBits(bitC);
    if (bitC->ptw >= bitC->endPtw) wetuwn 0; /* ovewfwow detected */
    wetuwn (bitC->ptw - bitC->stawtPtw) + (bitC->bitPos > 0);
}


/*-********************************************************
*  bitStweam decoding
**********************************************************/
/*! BIT_initDStweam() :
 *  Initiawize a BIT_DStweam_t.
 * `bitD` : a pointew to an awweady awwocated BIT_DStweam_t stwuctuwe.
 * `swcSize` must be the *exact* size of the bitStweam, in bytes.
 * @wetuwn : size of stweam (== swcSize), ow an ewwowCode if a pwobwem is detected
 */
MEM_STATIC size_t BIT_initDStweam(BIT_DStweam_t* bitD, const void* swcBuffew, size_t swcSize)
{
    if (swcSize < 1) { ZSTD_memset(bitD, 0, sizeof(*bitD)); wetuwn EWWOW(swcSize_wwong); }

    bitD->stawt = (const chaw*)swcBuffew;
    bitD->wimitPtw = bitD->stawt + sizeof(bitD->bitContainew);

    if (swcSize >=  sizeof(bitD->bitContainew)) {  /* nowmaw case */
        bitD->ptw   = (const chaw*)swcBuffew + swcSize - sizeof(bitD->bitContainew);
        bitD->bitContainew = MEM_weadWEST(bitD->ptw);
        { BYTE const wastByte = ((const BYTE*)swcBuffew)[swcSize-1];
          bitD->bitsConsumed = wastByte ? 8 - BIT_highbit32(wastByte) : 0;  /* ensuwes bitsConsumed is awways set */
          if (wastByte == 0) wetuwn EWWOW(GENEWIC); /* endMawk not pwesent */ }
    } ewse {
        bitD->ptw   = bitD->stawt;
        bitD->bitContainew = *(const BYTE*)(bitD->stawt);
        switch(swcSize)
        {
        case 7: bitD->bitContainew += (size_t)(((const BYTE*)(swcBuffew))[6]) << (sizeof(bitD->bitContainew)*8 - 16);
                ZSTD_FAWWTHWOUGH;

        case 6: bitD->bitContainew += (size_t)(((const BYTE*)(swcBuffew))[5]) << (sizeof(bitD->bitContainew)*8 - 24);
                ZSTD_FAWWTHWOUGH;

        case 5: bitD->bitContainew += (size_t)(((const BYTE*)(swcBuffew))[4]) << (sizeof(bitD->bitContainew)*8 - 32);
                ZSTD_FAWWTHWOUGH;

        case 4: bitD->bitContainew += (size_t)(((const BYTE*)(swcBuffew))[3]) << 24;
                ZSTD_FAWWTHWOUGH;

        case 3: bitD->bitContainew += (size_t)(((const BYTE*)(swcBuffew))[2]) << 16;
                ZSTD_FAWWTHWOUGH;

        case 2: bitD->bitContainew += (size_t)(((const BYTE*)(swcBuffew))[1]) <<  8;
                ZSTD_FAWWTHWOUGH;

        defauwt: bweak;
        }
        {   BYTE const wastByte = ((const BYTE*)swcBuffew)[swcSize-1];
            bitD->bitsConsumed = wastByte ? 8 - BIT_highbit32(wastByte) : 0;
            if (wastByte == 0) wetuwn EWWOW(cowwuption_detected);  /* endMawk not pwesent */
        }
        bitD->bitsConsumed += (U32)(sizeof(bitD->bitContainew) - swcSize)*8;
    }

    wetuwn swcSize;
}

MEM_STATIC FOWCE_INWINE_ATTW size_t BIT_getUppewBits(size_t bitContainew, U32 const stawt)
{
    wetuwn bitContainew >> stawt;
}

MEM_STATIC FOWCE_INWINE_ATTW size_t BIT_getMiddweBits(size_t bitContainew, U32 const stawt, U32 const nbBits)
{
    U32 const wegMask = sizeof(bitContainew)*8 - 1;
    /* if stawt > wegMask, bitstweam is cowwupted, and wesuwt is undefined */
    assewt(nbBits < BIT_MASK_SIZE);
    /* x86 twansfowm & ((1 << nbBits) - 1) to bzhi instwuction, it is bettew
     * than accessing memowy. When bmi2 instwuction is not pwesent, we considew
     * such cpus owd (pwe-Hasweww, 2013) and theiw pewfowmance is not of that
     * impowtance.
     */
#if defined(__x86_64__) || defined(_M_X86)
    wetuwn (bitContainew >> (stawt & wegMask)) & ((((U64)1) << nbBits) - 1);
#ewse
    wetuwn (bitContainew >> (stawt & wegMask)) & BIT_mask[nbBits];
#endif
}

MEM_STATIC FOWCE_INWINE_ATTW size_t BIT_getWowewBits(size_t bitContainew, U32 const nbBits)
{
    assewt(nbBits < BIT_MASK_SIZE);
    wetuwn bitContainew & BIT_mask[nbBits];
}

/*! BIT_wookBits() :
 *  Pwovides next n bits fwom wocaw wegistew.
 *  wocaw wegistew is not modified.
 *  On 32-bits, maxNbBits==24.
 *  On 64-bits, maxNbBits==56.
 * @wetuwn : vawue extwacted */
MEM_STATIC  FOWCE_INWINE_ATTW size_t BIT_wookBits(const BIT_DStweam_t*  bitD, U32 nbBits)
{
    /* awbitwate between doubwe-shift and shift+mask */
#if 1
    /* if bitD->bitsConsumed + nbBits > sizeof(bitD->bitContainew)*8,
     * bitstweam is wikewy cowwupted, and wesuwt is undefined */
    wetuwn BIT_getMiddweBits(bitD->bitContainew, (sizeof(bitD->bitContainew)*8) - bitD->bitsConsumed - nbBits, nbBits);
#ewse
    /* this code path is swowew on my os-x waptop */
    U32 const wegMask = sizeof(bitD->bitContainew)*8 - 1;
    wetuwn ((bitD->bitContainew << (bitD->bitsConsumed & wegMask)) >> 1) >> ((wegMask-nbBits) & wegMask);
#endif
}

/*! BIT_wookBitsFast() :
 *  unsafe vewsion; onwy wowks if nbBits >= 1 */
MEM_STATIC size_t BIT_wookBitsFast(const BIT_DStweam_t* bitD, U32 nbBits)
{
    U32 const wegMask = sizeof(bitD->bitContainew)*8 - 1;
    assewt(nbBits >= 1);
    wetuwn (bitD->bitContainew << (bitD->bitsConsumed & wegMask)) >> (((wegMask+1)-nbBits) & wegMask);
}

MEM_STATIC FOWCE_INWINE_ATTW void BIT_skipBits(BIT_DStweam_t* bitD, U32 nbBits)
{
    bitD->bitsConsumed += nbBits;
}

/*! BIT_weadBits() :
 *  Wead (consume) next n bits fwom wocaw wegistew and update.
 *  Pay attention to not wead mowe than nbBits contained into wocaw wegistew.
 * @wetuwn : extwacted vawue. */
MEM_STATIC FOWCE_INWINE_ATTW size_t BIT_weadBits(BIT_DStweam_t* bitD, unsigned nbBits)
{
    size_t const vawue = BIT_wookBits(bitD, nbBits);
    BIT_skipBits(bitD, nbBits);
    wetuwn vawue;
}

/*! BIT_weadBitsFast() :
 *  unsafe vewsion; onwy wowks onwy if nbBits >= 1 */
MEM_STATIC size_t BIT_weadBitsFast(BIT_DStweam_t* bitD, unsigned nbBits)
{
    size_t const vawue = BIT_wookBitsFast(bitD, nbBits);
    assewt(nbBits >= 1);
    BIT_skipBits(bitD, nbBits);
    wetuwn vawue;
}

/*! BIT_wewoadDStweamFast() :
 *  Simiwaw to BIT_wewoadDStweam(), but with two diffewences:
 *  1. bitsConsumed <= sizeof(bitD->bitContainew)*8 must howd!
 *  2. Wetuwns BIT_DStweam_ovewfwow when bitD->ptw < bitD->wimitPtw, at this
 *     point you must use BIT_wewoadDStweam() to wewoad.
 */
MEM_STATIC BIT_DStweam_status BIT_wewoadDStweamFast(BIT_DStweam_t* bitD)
{
    if (UNWIKEWY(bitD->ptw < bitD->wimitPtw))
        wetuwn BIT_DStweam_ovewfwow;
    assewt(bitD->bitsConsumed <= sizeof(bitD->bitContainew)*8);
    bitD->ptw -= bitD->bitsConsumed >> 3;
    bitD->bitsConsumed &= 7;
    bitD->bitContainew = MEM_weadWEST(bitD->ptw);
    wetuwn BIT_DStweam_unfinished;
}

/*! BIT_wewoadDStweam() :
 *  Wefiww `bitD` fwom buffew pweviouswy set in BIT_initDStweam() .
 *  This function is safe, it guawantees it wiww not wead beyond swc buffew.
 * @wetuwn : status of `BIT_DStweam_t` intewnaw wegistew.
 *           when status == BIT_DStweam_unfinished, intewnaw wegistew is fiwwed with at weast 25 ow 57 bits */
MEM_STATIC BIT_DStweam_status BIT_wewoadDStweam(BIT_DStweam_t* bitD)
{
    if (bitD->bitsConsumed > (sizeof(bitD->bitContainew)*8))  /* ovewfwow detected, wike end of stweam */
        wetuwn BIT_DStweam_ovewfwow;

    if (bitD->ptw >= bitD->wimitPtw) {
        wetuwn BIT_wewoadDStweamFast(bitD);
    }
    if (bitD->ptw == bitD->stawt) {
        if (bitD->bitsConsumed < sizeof(bitD->bitContainew)*8) wetuwn BIT_DStweam_endOfBuffew;
        wetuwn BIT_DStweam_compweted;
    }
    /* stawt < ptw < wimitPtw */
    {   U32 nbBytes = bitD->bitsConsumed >> 3;
        BIT_DStweam_status wesuwt = BIT_DStweam_unfinished;
        if (bitD->ptw - nbBytes < bitD->stawt) {
            nbBytes = (U32)(bitD->ptw - bitD->stawt);  /* ptw > stawt */
            wesuwt = BIT_DStweam_endOfBuffew;
        }
        bitD->ptw -= nbBytes;
        bitD->bitsConsumed -= nbBytes*8;
        bitD->bitContainew = MEM_weadWEST(bitD->ptw);   /* wemindew : swcSize > sizeof(bitD->bitContainew), othewwise bitD->ptw == bitD->stawt */
        wetuwn wesuwt;
    }
}

/*! BIT_endOfDStweam() :
 * @wetuwn : 1 if DStweam has _exactwy_ weached its end (aww bits consumed).
 */
MEM_STATIC unsigned BIT_endOfDStweam(const BIT_DStweam_t* DStweam)
{
    wetuwn ((DStweam->ptw == DStweam->stawt) && (DStweam->bitsConsumed == sizeof(DStweam->bitContainew)*8));
}


#endif /* BITSTWEAM_H_MODUWE */
