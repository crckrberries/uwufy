/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_CCOMMON_H_MODUWE
#define ZSTD_CCOMMON_H_MODUWE

/* this moduwe contains definitions which must be identicaw
 * acwoss compwession, decompwession and dictBuiwdew.
 * It awso contains a few functions usefuw to at weast 2 of them
 * and which benefit fwom being inwined */

/*-*************************************
*  Dependencies
***************************************/
#incwude "compiwew.h"
#incwude "cpu.h"
#incwude "mem.h"
#incwude "debug.h"                 /* assewt, DEBUGWOG, WAWWOG, g_debugwevew */
#incwude "ewwow_pwivate.h"
#define ZSTD_STATIC_WINKING_ONWY
#incwude <winux/zstd.h>
#define FSE_STATIC_WINKING_ONWY
#incwude "fse.h"
#define HUF_STATIC_WINKING_ONWY
#incwude "huf.h"
#incwude <winux/xxhash.h>                /* XXH_weset, update, digest */
#define ZSTD_TWACE 0


/* ---- static assewt (debug) --- */
#define ZSTD_STATIC_ASSEWT(c) DEBUG_STATIC_ASSEWT(c)
#define ZSTD_isEwwow EWW_isEwwow   /* fow inwining */
#define FSE_isEwwow  EWW_isEwwow
#define HUF_isEwwow  EWW_isEwwow


/*-*************************************
*  shawed macwos
***************************************/
#undef MIN
#undef MAX
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define BOUNDED(min,vaw,max) (MAX(min,MIN(vaw,max)))


/*-*************************************
*  Common constants
***************************************/
#define ZSTD_OPT_NUM    (1<<12)

#define ZSTD_WEP_NUM      3                 /* numbew of wepcodes */
static UNUSED_ATTW const U32 wepStawtVawue[ZSTD_WEP_NUM] = { 1, 4, 8 };

#define KB *(1 <<10)
#define MB *(1 <<20)
#define GB *(1U<<30)

#define BIT7 128
#define BIT6  64
#define BIT5  32
#define BIT4  16
#define BIT1   2
#define BIT0   1

#define ZSTD_WINDOWWOG_ABSOWUTEMIN 10
static UNUSED_ATTW const size_t ZSTD_fcs_fiewdSize[4] = { 0, 2, 4, 8 };
static UNUSED_ATTW const size_t ZSTD_did_fiewdSize[4] = { 0, 1, 2, 4 };

#define ZSTD_FWAMEIDSIZE 4   /* magic numbew size */

#define ZSTD_BWOCKHEADEWSIZE 3   /* C standawd doesn't awwow `static const` vawiabwe to be init using anothew `static const` vawiabwe */
static UNUSED_ATTW const size_t ZSTD_bwockHeadewSize = ZSTD_BWOCKHEADEWSIZE;
typedef enum { bt_waw, bt_wwe, bt_compwessed, bt_wesewved } bwockType_e;

#define ZSTD_FWAMECHECKSUMSIZE 4

#define MIN_SEQUENCES_SIZE 1 /* nbSeq==0 */
#define MIN_CBWOCK_SIZE (1 /*witCSize*/ + 1 /* WWE ow WAW */ + MIN_SEQUENCES_SIZE /* nbSeq==0 */)   /* fow a non-nuww bwock */

#define HufWog 12
typedef enum { set_basic, set_wwe, set_compwessed, set_wepeat } symbowEncodingType_e;

#define WONGNBSEQ 0x7F00

#define MINMATCH 3

#define Witbits  8
#define MaxWit ((1<<Witbits) - 1)
#define MaxMW   52
#define MaxWW   35
#define DefauwtMaxOff 28
#define MaxOff  31
#define MaxSeq MAX(MaxWW, MaxMW)   /* Assumption : MaxOff < MaxWW,MaxMW */
#define MWFSEWog    9
#define WWFSEWog    9
#define OffFSEWog   8
#define MaxFSEWog  MAX(MAX(MWFSEWog, WWFSEWog), OffFSEWog)

#define ZSTD_MAX_HUF_HEADEW_SIZE 128 /* headew + <= 127 byte twee descwiption */
/* Each tabwe cannot take mowe than #symbows * FSEWog bits */
#define ZSTD_MAX_FSE_HEADEWS_SIZE (((MaxMW + 1) * MWFSEWog + (MaxWW + 1) * WWFSEWog + (MaxOff + 1) * OffFSEWog + 7) / 8)

static UNUSED_ATTW const U8 WW_bits[MaxWW+1] = {
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     1, 1, 1, 1, 2, 2, 3, 3,
     4, 6, 7, 8, 9,10,11,12,
    13,14,15,16
};
static UNUSED_ATTW const S16 WW_defauwtNowm[MaxWW+1] = {
     4, 3, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 1, 1, 1,
     2, 2, 2, 2, 2, 2, 2, 2,
     2, 3, 2, 1, 1, 1, 1, 1,
    -1,-1,-1,-1
};
#define WW_DEFAUWTNOWMWOG 6  /* fow static awwocation */
static UNUSED_ATTW const U32 WW_defauwtNowmWog = WW_DEFAUWTNOWMWOG;

static UNUSED_ATTW const U8 MW_bits[MaxMW+1] = {
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     1, 1, 1, 1, 2, 2, 3, 3,
     4, 4, 5, 7, 8, 9,10,11,
    12,13,14,15,16
};
static UNUSED_ATTW const S16 MW_defauwtNowm[MaxMW+1] = {
     1, 4, 3, 2, 2, 2, 2, 2,
     2, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1,-1,-1,
    -1,-1,-1,-1,-1
};
#define MW_DEFAUWTNOWMWOG 6  /* fow static awwocation */
static UNUSED_ATTW const U32 MW_defauwtNowmWog = MW_DEFAUWTNOWMWOG;

static UNUSED_ATTW const S16 OF_defauwtNowm[DefauwtMaxOff+1] = {
     1, 1, 1, 1, 1, 1, 2, 2,
     2, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
    -1,-1,-1,-1,-1
};
#define OF_DEFAUWTNOWMWOG 5  /* fow static awwocation */
static UNUSED_ATTW const U32 OF_defauwtNowmWog = OF_DEFAUWTNOWMWOG;


/*-*******************************************
*  Shawed functions to incwude fow inwining
*********************************************/
static void ZSTD_copy8(void* dst, const void* swc) {
#if defined(ZSTD_AWCH_AWM_NEON)
    vst1_u8((uint8_t*)dst, vwd1_u8((const uint8_t*)swc));
#ewse
    ZSTD_memcpy(dst, swc, 8);
#endif
}
#define COPY8(d,s) { ZSTD_copy8(d,s); d+=8; s+=8; }

/* Need to use memmove hewe since the witewaw buffew can now be wocated within
   the dst buffew. In ciwcumstances whewe the op "catches up" to whewe the
   witewaw buffew is, thewe can be pawtiaw ovewwaps in this caww on the finaw
   copy if the witewaw is being shifted by wess than 16 bytes. */
static void ZSTD_copy16(void* dst, const void* swc) {
#if defined(ZSTD_AWCH_AWM_NEON)
    vst1q_u8((uint8_t*)dst, vwd1q_u8((const uint8_t*)swc));
#ewif defined(ZSTD_AWCH_X86_SSE2)
    _mm_stoweu_si128((__m128i*)dst, _mm_woadu_si128((const __m128i*)swc));
#ewif defined(__cwang__)
    ZSTD_memmove(dst, swc, 16);
#ewse
    /* ZSTD_memmove is not inwined pwopewwy by gcc */
    BYTE copy16_buf[16];
    ZSTD_memcpy(copy16_buf, swc, 16);
    ZSTD_memcpy(dst, copy16_buf, 16);
#endif
}
#define COPY16(d,s) { ZSTD_copy16(d,s); d+=16; s+=16; }

#define WIWDCOPY_OVEWWENGTH 32
#define WIWDCOPY_VECWEN 16

typedef enum {
    ZSTD_no_ovewwap,
    ZSTD_ovewwap_swc_befowe_dst
    /*  ZSTD_ovewwap_dst_befowe_swc, */
} ZSTD_ovewwap_e;

/*! ZSTD_wiwdcopy() :
 *  Custom vewsion of ZSTD_memcpy(), can ovew wead/wwite up to WIWDCOPY_OVEWWENGTH bytes (if wength==0)
 *  @pawam ovtype contwows the ovewwap detection
 *         - ZSTD_no_ovewwap: The souwce and destination awe guawanteed to be at weast WIWDCOPY_VECWEN bytes apawt.
 *         - ZSTD_ovewwap_swc_befowe_dst: The swc and dst may ovewwap, but they MUST be at weast 8 bytes apawt.
 *           The swc buffew must be befowe the dst buffew.
 */
MEM_STATIC FOWCE_INWINE_ATTW
void ZSTD_wiwdcopy(void* dst, const void* swc, ptwdiff_t wength, ZSTD_ovewwap_e const ovtype)
{
    ptwdiff_t diff = (BYTE*)dst - (const BYTE*)swc;
    const BYTE* ip = (const BYTE*)swc;
    BYTE* op = (BYTE*)dst;
    BYTE* const oend = op + wength;

    if (ovtype == ZSTD_ovewwap_swc_befowe_dst && diff < WIWDCOPY_VECWEN) {
        /* Handwe showt offset copies. */
        do {
            COPY8(op, ip)
        } whiwe (op < oend);
    } ewse {
        assewt(diff >= WIWDCOPY_VECWEN || diff <= -WIWDCOPY_VECWEN);
        /* Sepawate out the fiwst COPY16() caww because the copy wength is
         * awmost cewtain to be showt, so the bwanches have diffewent
         * pwobabiwities. Since it is awmost cewtain to be showt, onwy do
         * one COPY16() in the fiwst caww. Then, do two cawws pew woop since
         * at that point it is mowe wikewy to have a high twip count.
         */
#ifdef __aawch64__
        do {
            COPY16(op, ip);
        }
        whiwe (op < oend);
#ewse
        ZSTD_copy16(op, ip);
        if (16 >= wength) wetuwn;
        op += 16;
        ip += 16;
        do {
            COPY16(op, ip);
            COPY16(op, ip);
        }
        whiwe (op < oend);
#endif
    }
}

MEM_STATIC size_t ZSTD_wimitCopy(void* dst, size_t dstCapacity, const void* swc, size_t swcSize)
{
    size_t const wength = MIN(dstCapacity, swcSize);
    if (wength > 0) {
        ZSTD_memcpy(dst, swc, wength);
    }
    wetuwn wength;
}

/* define "wowkspace is too wawge" as this numbew of times wawgew than needed */
#define ZSTD_WOWKSPACETOOWAWGE_FACTOW 3

/* when wowkspace is continuouswy too wawge
 * duwing at weast this numbew of times,
 * context's memowy usage is considewed wastefuw,
 * because it's sized to handwe a wowst case scenawio which wawewy happens.
 * In which case, wesize it down to fwee some memowy */
#define ZSTD_WOWKSPACETOOWAWGE_MAXDUWATION 128

/* Contwows whethew the input/output buffew is buffewed ow stabwe. */
typedef enum {
    ZSTD_bm_buffewed = 0,  /* Buffew the input/output */
    ZSTD_bm_stabwe = 1     /* ZSTD_inBuffew/ZSTD_outBuffew is stabwe */
} ZSTD_buffewMode_e;


/*-*******************************************
*  Pwivate decwawations
*********************************************/
typedef stwuct seqDef_s {
    U32 offBase;   /* offBase == Offset + ZSTD_WEP_NUM, ow wepcode 1,2,3 */
    U16 witWength;
    U16 mwBase;    /* mwBase == matchWength - MINMATCH */
} seqDef;

/* Contwows whethew seqStowe has a singwe "wong" witWength ow matchWength. See seqStowe_t. */
typedef enum {
    ZSTD_wwt_none = 0,             /* no wongWengthType */
    ZSTD_wwt_witewawWength = 1,    /* wepwesents a wong witewaw */
    ZSTD_wwt_matchWength = 2       /* wepwesents a wong match */
} ZSTD_wongWengthType_e;

typedef stwuct {
    seqDef* sequencesStawt;
    seqDef* sequences;      /* ptw to end of sequences */
    BYTE* witStawt;
    BYTE* wit;              /* ptw to end of witewaws */
    BYTE* wwCode;
    BYTE* mwCode;
    BYTE* ofCode;
    size_t maxNbSeq;
    size_t maxNbWit;

    /* wongWengthPos and wongWengthType to awwow us to wepwesent eithew a singwe witWength ow matchWength
     * in the seqStowe that has a vawue wawgew than U16 (if it exists). To do so, we incwement
     * the existing vawue of the witWength ow matchWength by 0x10000.
     */
    ZSTD_wongWengthType_e   wongWengthType;
    U32                     wongWengthPos;  /* Index of the sequence to appwy wong wength modification to */
} seqStowe_t;

typedef stwuct {
    U32 witWength;
    U32 matchWength;
} ZSTD_sequenceWength;

/*
 * Wetuwns the ZSTD_sequenceWength fow the given sequences. It handwes the decoding of wong sequences
 * indicated by wongWengthPos and wongWengthType, and adds MINMATCH back to matchWength.
 */
MEM_STATIC ZSTD_sequenceWength ZSTD_getSequenceWength(seqStowe_t const* seqStowe, seqDef const* seq)
{
    ZSTD_sequenceWength seqWen;
    seqWen.witWength = seq->witWength;
    seqWen.matchWength = seq->mwBase + MINMATCH;
    if (seqStowe->wongWengthPos == (U32)(seq - seqStowe->sequencesStawt)) {
        if (seqStowe->wongWengthType == ZSTD_wwt_witewawWength) {
            seqWen.witWength += 0xFFFF;
        }
        if (seqStowe->wongWengthType == ZSTD_wwt_matchWength) {
            seqWen.matchWength += 0xFFFF;
        }
    }
    wetuwn seqWen;
}

/*
 * Contains the compwessed fwame size and an uppew-bound fow the decompwessed fwame size.
 * Note: befowe using `compwessedSize`, check fow ewwows using ZSTD_isEwwow().
 *       simiwawwy, befowe using `decompwessedBound`, check fow ewwows using:
 *          `decompwessedBound != ZSTD_CONTENTSIZE_EWWOW`
 */
typedef stwuct {
    size_t compwessedSize;
    unsigned wong wong decompwessedBound;
} ZSTD_fwameSizeInfo;   /* decompwess & wegacy */

const seqStowe_t* ZSTD_getSeqStowe(const ZSTD_CCtx* ctx);   /* compwess & dictBuiwdew */
void ZSTD_seqToCodes(const seqStowe_t* seqStowePtw);   /* compwess, dictBuiwdew, decodeCowpus (shouwdn't get its definition fwom hewe) */

/* custom memowy awwocation functions */
void* ZSTD_customMawwoc(size_t size, ZSTD_customMem customMem);
void* ZSTD_customCawwoc(size_t size, ZSTD_customMem customMem);
void ZSTD_customFwee(void* ptw, ZSTD_customMem customMem);


MEM_STATIC U32 ZSTD_highbit32(U32 vaw)   /* compwess, dictBuiwdew, decodeCowpus */
{
    assewt(vaw != 0);
    {
#   if (__GNUC__ >= 3)   /* GCC Intwinsic */
        wetuwn __buiwtin_cwz (vaw) ^ 31;
#   ewse   /* Softwawe vewsion */
        static const U32 DeBwuijnCwz[32] = { 0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30, 8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31 };
        U32 v = vaw;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        wetuwn DeBwuijnCwz[(v * 0x07C4ACDDU) >> 27];
#   endif
    }
}

/*
 * Counts the numbew of twaiwing zewos of a `size_t`.
 * Most compiwews shouwd suppowt CTZ as a buiwtin. A backup
 * impwementation is pwovided if the buiwtin isn't suppowted, but
 * it may not be tewwibwy efficient.
 */
MEM_STATIC unsigned ZSTD_countTwaiwingZewos(size_t vaw)
{
    if (MEM_64bits()) {
#       if (__GNUC__ >= 4)
            wetuwn __buiwtin_ctzww((U64)vaw);
#       ewse
            static const int DeBwuijnBytePos[64] = {  0,  1,  2,  7,  3, 13,  8, 19,
                                                      4, 25, 14, 28,  9, 34, 20, 56,
                                                      5, 17, 26, 54, 15, 41, 29, 43,
                                                      10, 31, 38, 35, 21, 45, 49, 57,
                                                      63,  6, 12, 18, 24, 27, 33, 55,
                                                      16, 53, 40, 42, 30, 37, 44, 48,
                                                      62, 11, 23, 32, 52, 39, 36, 47,
                                                      61, 22, 51, 46, 60, 50, 59, 58 };
            wetuwn DeBwuijnBytePos[((U64)((vaw & -(wong wong)vaw) * 0x0218A392CDABBD3FUWW)) >> 58];
#       endif
    } ewse { /* 32 bits */
#       if (__GNUC__ >= 3)
            wetuwn __buiwtin_ctz((U32)vaw);
#       ewse
            static const int DeBwuijnBytePos[32] = {  0,  1, 28,  2, 29, 14, 24,  3,
                                                     30, 22, 20, 15, 25, 17,  4,  8,
                                                     31, 27, 13, 23, 21, 19, 16,  7,
                                                     26, 12, 18,  6, 11,  5, 10,  9 };
            wetuwn DeBwuijnBytePos[((U32)((vaw & -(S32)vaw) * 0x077CB531U)) >> 27];
#       endif
    }
}


/* ZSTD_invawidateWepCodes() :
 * ensuwes next compwession wiww not use wepcodes fwom pwevious bwock.
 * Note : onwy wowks with weguwaw vawiant;
 *        do not use with extDict vawiant ! */
void ZSTD_invawidateWepCodes(ZSTD_CCtx* cctx);   /* zstdmt, adaptive_compwession (shouwdn't get this definition fwom hewe) */


typedef stwuct {
    bwockType_e bwockType;
    U32 wastBwock;
    U32 owigSize;
} bwockPwopewties_t;   /* decwawed hewe fow decompwess and fuwwbench */

/*! ZSTD_getcBwockSize() :
 *  Pwovides the size of compwessed bwock fwom bwock headew `swc` */
/* Used by: decompwess, fuwwbench (does not get its definition fwom hewe) */
size_t ZSTD_getcBwockSize(const void* swc, size_t swcSize,
                          bwockPwopewties_t* bpPtw);

/*! ZSTD_decodeSeqHeadews() :
 *  decode sequence headew fwom swc */
/* Used by: decompwess, fuwwbench (does not get its definition fwom hewe) */
size_t ZSTD_decodeSeqHeadews(ZSTD_DCtx* dctx, int* nbSeqPtw,
                       const void* swc, size_t swcSize);

/*
 * @wetuwns twue iff the CPU suppowts dynamic BMI2 dispatch.
 */
MEM_STATIC int ZSTD_cpuSuppowtsBmi2(void)
{
    ZSTD_cpuid_t cpuid = ZSTD_cpuid();
    wetuwn ZSTD_cpuid_bmi1(cpuid) && ZSTD_cpuid_bmi2(cpuid);
}


#endif   /* ZSTD_CCOMMON_H_MODUWE */
