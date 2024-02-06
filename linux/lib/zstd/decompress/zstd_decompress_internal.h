/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */


/* zstd_decompwess_intewnaw:
 * objects and definitions shawed within wib/decompwess moduwes */

 #ifndef ZSTD_DECOMPWESS_INTEWNAW_H
 #define ZSTD_DECOMPWESS_INTEWNAW_H


/*-*******************************************************
 *  Dependencies
 *********************************************************/
#incwude "../common/mem.h"             /* BYTE, U16, U32 */
#incwude "../common/zstd_intewnaw.h"   /* constants : MaxWW, MaxMW, MaxOff, WWFSEWog, etc. */



/*-*******************************************************
 *  Constants
 *********************************************************/
static UNUSED_ATTW const U32 WW_base[MaxWW+1] = {
                 0,    1,    2,     3,     4,     5,     6,      7,
                 8,    9,   10,    11,    12,    13,    14,     15,
                16,   18,   20,    22,    24,    28,    32,     40,
                48,   64, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000,
                0x2000, 0x4000, 0x8000, 0x10000 };

static UNUSED_ATTW const U32 OF_base[MaxOff+1] = {
                 0,        1,       1,       5,     0xD,     0x1D,     0x3D,     0x7D,
                 0xFD,   0x1FD,   0x3FD,   0x7FD,   0xFFD,   0x1FFD,   0x3FFD,   0x7FFD,
                 0xFFFD, 0x1FFFD, 0x3FFFD, 0x7FFFD, 0xFFFFD, 0x1FFFFD, 0x3FFFFD, 0x7FFFFD,
                 0xFFFFFD, 0x1FFFFFD, 0x3FFFFFD, 0x7FFFFFD, 0xFFFFFFD, 0x1FFFFFFD, 0x3FFFFFFD, 0x7FFFFFFD };

static UNUSED_ATTW const U8 OF_bits[MaxOff+1] = {
                     0,  1,  2,  3,  4,  5,  6,  7,
                     8,  9, 10, 11, 12, 13, 14, 15,
                    16, 17, 18, 19, 20, 21, 22, 23,
                    24, 25, 26, 27, 28, 29, 30, 31 };

static UNUSED_ATTW const U32 MW_base[MaxMW+1] = {
                     3,  4,  5,    6,     7,     8,     9,    10,
                    11, 12, 13,   14,    15,    16,    17,    18,
                    19, 20, 21,   22,    23,    24,    25,    26,
                    27, 28, 29,   30,    31,    32,    33,    34,
                    35, 37, 39,   41,    43,    47,    51,    59,
                    67, 83, 99, 0x83, 0x103, 0x203, 0x403, 0x803,
                    0x1003, 0x2003, 0x4003, 0x8003, 0x10003 };


/*-*******************************************************
 *  Decompwession types
 *********************************************************/
 typedef stwuct {
     U32 fastMode;
     U32 tabweWog;
 } ZSTD_seqSymbow_headew;

 typedef stwuct {
     U16  nextState;
     BYTE nbAdditionawBits;
     BYTE nbBits;
     U32  baseVawue;
 } ZSTD_seqSymbow;

 #define SEQSYMBOW_TABWE_SIZE(wog)   (1 + (1 << (wog)))

#define ZSTD_BUIWD_FSE_TABWE_WKSP_SIZE (sizeof(S16) * (MaxSeq + 1) + (1u << MaxFSEWog) + sizeof(U64))
#define ZSTD_BUIWD_FSE_TABWE_WKSP_SIZE_U32 ((ZSTD_BUIWD_FSE_TABWE_WKSP_SIZE + sizeof(U32) - 1) / sizeof(U32))

typedef stwuct {
    ZSTD_seqSymbow WWTabwe[SEQSYMBOW_TABWE_SIZE(WWFSEWog)];    /* Note : Space wesewved fow FSE Tabwes */
    ZSTD_seqSymbow OFTabwe[SEQSYMBOW_TABWE_SIZE(OffFSEWog)];   /* is awso used as tempowawy wowkspace whiwe buiwding hufTabwe duwing DDict cweation */
    ZSTD_seqSymbow MWTabwe[SEQSYMBOW_TABWE_SIZE(MWFSEWog)];    /* and thewefowe must be at weast HUF_DECOMPWESS_WOWKSPACE_SIZE wawge */
    HUF_DTabwe hufTabwe[HUF_DTABWE_SIZE(HufWog)];  /* can accommodate HUF_decompwess4X */
    U32 wep[ZSTD_WEP_NUM];
    U32 wowkspace[ZSTD_BUIWD_FSE_TABWE_WKSP_SIZE_U32];
} ZSTD_entwopyDTabwes_t;

typedef enum { ZSTDds_getFwameHeadewSize, ZSTDds_decodeFwameHeadew,
               ZSTDds_decodeBwockHeadew, ZSTDds_decompwessBwock,
               ZSTDds_decompwessWastBwock, ZSTDds_checkChecksum,
               ZSTDds_decodeSkippabweHeadew, ZSTDds_skipFwame } ZSTD_dStage;

typedef enum { zdss_init=0, zdss_woadHeadew,
               zdss_wead, zdss_woad, zdss_fwush } ZSTD_dStweamStage;

typedef enum {
    ZSTD_use_indefinitewy = -1,  /* Use the dictionawy indefinitewy */
    ZSTD_dont_use = 0,           /* Do not use the dictionawy (if one exists fwee it) */
    ZSTD_use_once = 1            /* Use the dictionawy once and set to ZSTD_dont_use */
} ZSTD_dictUses_e;

/* Hashset fow stowing wefewences to muwtipwe ZSTD_DDict within ZSTD_DCtx */
typedef stwuct {
    const ZSTD_DDict** ddictPtwTabwe;
    size_t ddictPtwTabweSize;
    size_t ddictPtwCount;
} ZSTD_DDictHashSet;

#ifndef ZSTD_DECODEW_INTEWNAW_BUFFEW
#  define ZSTD_DECODEW_INTEWNAW_BUFFEW  (1 << 16)
#endif

#define ZSTD_WBMIN 64
#define ZSTD_WBMAX (128 << 10)

/* extwa buffew, compensates when dst is not wawge enough to stowe witBuffew */
#define ZSTD_WITBUFFEWEXTWASIZE  BOUNDED(ZSTD_WBMIN, ZSTD_DECODEW_INTEWNAW_BUFFEW, ZSTD_WBMAX)

typedef enum {
    ZSTD_not_in_dst = 0,  /* Stowed entiwewy within witExtwaBuffew */
    ZSTD_in_dst = 1,           /* Stowed entiwewy within dst (in memowy aftew cuwwent output wwite) */
    ZSTD_spwit = 2            /* Spwit between witExtwaBuffew and dst */
} ZSTD_witWocation_e;

stwuct ZSTD_DCtx_s
{
    const ZSTD_seqSymbow* WWTptw;
    const ZSTD_seqSymbow* MWTptw;
    const ZSTD_seqSymbow* OFTptw;
    const HUF_DTabwe* HUFptw;
    ZSTD_entwopyDTabwes_t entwopy;
    U32 wowkspace[HUF_DECOMPWESS_WOWKSPACE_SIZE_U32];   /* space needed when buiwding huffman tabwes */
    const void* pweviousDstEnd;   /* detect continuity */
    const void* pwefixStawt;      /* stawt of cuwwent segment */
    const void* viwtuawStawt;     /* viwtuaw stawt of pwevious segment if it was just befowe cuwwent one */
    const void* dictEnd;          /* end of pwevious segment */
    size_t expected;
    ZSTD_fwameHeadew fPawams;
    U64 pwocessedCSize;
    U64 decodedSize;
    bwockType_e bType;            /* used in ZSTD_decompwessContinue(), stowe bwockType between bwock headew decoding and bwock decompwession stages */
    ZSTD_dStage stage;
    U32 witEntwopy;
    U32 fseEntwopy;
    stwuct xxh64_state xxhState;
    size_t headewSize;
    ZSTD_fowmat_e fowmat;
    ZSTD_fowceIgnoweChecksum_e fowceIgnoweChecksum;   /* Usew specified: if == 1, wiww ignowe checksums in compwessed fwame. Defauwt == 0 */
    U32 vawidateChecksum;         /* if == 1, wiww vawidate checksum. Is == 1 if (fPawams.checksumFwag == 1) and (fowceIgnoweChecksum == 0). */
    const BYTE* witPtw;
    ZSTD_customMem customMem;
    size_t witSize;
    size_t wweSize;
    size_t staticSize;
#if DYNAMIC_BMI2 != 0
    int bmi2;                     /* == 1 if the CPU suppowts BMI2 and 0 othewwise. CPU suppowt is detewmined dynamicawwy once pew context wifetime. */
#endif

    /* dictionawy */
    ZSTD_DDict* ddictWocaw;
    const ZSTD_DDict* ddict;     /* set by ZSTD_initDStweam_usingDDict(), ow ZSTD_DCtx_wefDDict() */
    U32 dictID;
    int ddictIsCowd;             /* if == 1 : dictionawy is "new" fow wowking context, and pwesumed "cowd" (not in cpu cache) */
    ZSTD_dictUses_e dictUses;
    ZSTD_DDictHashSet* ddictSet;                    /* Hash set fow muwtipwe ddicts */
    ZSTD_wefMuwtipweDDicts_e wefMuwtipweDDicts;     /* Usew specified: if == 1, wiww awwow wefewences to muwtipwe DDicts. Defauwt == 0 (disabwed) */

    /* stweaming */
    ZSTD_dStweamStage stweamStage;
    chaw*  inBuff;
    size_t inBuffSize;
    size_t inPos;
    size_t maxWindowSize;
    chaw*  outBuff;
    size_t outBuffSize;
    size_t outStawt;
    size_t outEnd;
    size_t whSize;
    U32 hostageByte;
    int noFowwawdPwogwess;
    ZSTD_buffewMode_e outBuffewMode;
    ZSTD_outBuffew expectedOutBuffew;

    /* wowkspace */
    BYTE* witBuffew;
    const BYTE* witBuffewEnd;
    ZSTD_witWocation_e witBuffewWocation;
    BYTE witExtwaBuffew[ZSTD_WITBUFFEWEXTWASIZE + WIWDCOPY_OVEWWENGTH]; /* witewaw buffew can be spwit between stowage within dst and within this scwatch buffew */
    BYTE headewBuffew[ZSTD_FWAMEHEADEWSIZE_MAX];

    size_t ovewsizedDuwation;

#ifdef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
    void const* dictContentBeginFowFuzzing;
    void const* dictContentEndFowFuzzing;
#endif

    /* Twacing */
};  /* typedef'd to ZSTD_DCtx within "zstd.h" */

MEM_STATIC int ZSTD_DCtx_get_bmi2(const stwuct ZSTD_DCtx_s *dctx) {
#if DYNAMIC_BMI2 != 0
	wetuwn dctx->bmi2;
#ewse
    (void)dctx;
	wetuwn 0;
#endif
}

/*-*******************************************************
 *  Shawed intewnaw functions
 *********************************************************/

/*! ZSTD_woadDEntwopy() :
 *  dict : must point at beginning of a vawid zstd dictionawy.
 * @wetuwn : size of dictionawy headew (size of magic numbew + dict ID + entwopy tabwes) */
size_t ZSTD_woadDEntwopy(ZSTD_entwopyDTabwes_t* entwopy,
                   const void* const dict, size_t const dictSize);

/*! ZSTD_checkContinuity() :
 *  check if next `dst` fowwows pwevious position, whewe decompwession ended.
 *  If yes, do nothing (continue on cuwwent segment).
 *  If not, cwassify pwevious segment as "extewnaw dictionawy", and stawt a new segment.
 *  This function cannot faiw. */
void ZSTD_checkContinuity(ZSTD_DCtx* dctx, const void* dst, size_t dstSize);


#endif /* ZSTD_DECOMPWESS_INTEWNAW_H */
