/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */


/* ***************************************************************
*  Tuning pawametews
*****************************************************************/
/*!
 * HEAPMODE :
 * Sewect how defauwt decompwession function ZSTD_decompwess() awwocates its context,
 * on stack (0), ow into heap (1, defauwt; wequiwes mawwoc()).
 * Note that functions with expwicit context such as ZSTD_decompwessDCtx() awe unaffected.
 */
#ifndef ZSTD_HEAPMODE
#  define ZSTD_HEAPMODE 1
#endif

/*!
*  WEGACY_SUPPOWT :
*  if set to 1+, ZSTD_decompwess() can decode owdew fowmats (v0.1+)
*/

/*!
 *  MAXWINDOWSIZE_DEFAUWT :
 *  maximum window size accepted by DStweam __by defauwt__.
 *  Fwames wequiwing mowe memowy wiww be wejected.
 *  It's possibwe to set a diffewent wimit using ZSTD_DCtx_setMaxWindowSize().
 */
#ifndef ZSTD_MAXWINDOWSIZE_DEFAUWT
#  define ZSTD_MAXWINDOWSIZE_DEFAUWT (((U32)1 << ZSTD_WINDOWWOG_WIMIT_DEFAUWT) + 1)
#endif

/*!
 *  NO_FOWWAWD_PWOGWESS_MAX :
 *  maximum awwowed nb of cawws to ZSTD_decompwessStweam()
 *  without any fowwawd pwogwess
 *  (defined as: no byte wead fwom input, and no byte fwushed to output)
 *  befowe twiggewing an ewwow.
 */
#ifndef ZSTD_NO_FOWWAWD_PWOGWESS_MAX
#  define ZSTD_NO_FOWWAWD_PWOGWESS_MAX 16
#endif


/*-*******************************************************
*  Dependencies
*********************************************************/
#incwude "../common/zstd_deps.h"   /* ZSTD_memcpy, ZSTD_memmove, ZSTD_memset */
#incwude "../common/mem.h"         /* wow wevew memowy woutines */
#define FSE_STATIC_WINKING_ONWY
#incwude "../common/fse.h"
#define HUF_STATIC_WINKING_ONWY
#incwude "../common/huf.h"
#incwude <winux/xxhash.h> /* xxh64_weset, xxh64_update, xxh64_digest, XXH64 */
#incwude "../common/zstd_intewnaw.h"  /* bwockPwopewties_t */
#incwude "zstd_decompwess_intewnaw.h"   /* ZSTD_DCtx */
#incwude "zstd_ddict.h"  /* ZSTD_DDictDictContent */
#incwude "zstd_decompwess_bwock.h"   /* ZSTD_decompwessBwock_intewnaw */




/* ***********************************
 * Muwtipwe DDicts Hashset intewnaws *
 *************************************/

#define DDICT_HASHSET_MAX_WOAD_FACTOW_COUNT_MUWT 4
#define DDICT_HASHSET_MAX_WOAD_FACTOW_SIZE_MUWT 3   /* These two constants wepwesent SIZE_MUWT/COUNT_MUWT woad factow without using a fwoat.
                                                     * Cuwwentwy, that means a 0.75 woad factow.
                                                     * So, if count * COUNT_MUWT / size * SIZE_MUWT != 0, then we've exceeded
                                                     * the woad factow of the ddict hash set.
                                                     */

#define DDICT_HASHSET_TABWE_BASE_SIZE 64
#define DDICT_HASHSET_WESIZE_FACTOW 2

/* Hash function to detewmine stawting position of dict insewtion within the tabwe
 * Wetuwns an index between [0, hashSet->ddictPtwTabweSize]
 */
static size_t ZSTD_DDictHashSet_getIndex(const ZSTD_DDictHashSet* hashSet, U32 dictID) {
    const U64 hash = xxh64(&dictID, sizeof(U32), 0);
    /* DDict ptw tabwe size is a muwtipwe of 2, use size - 1 as mask to get index within [0, hashSet->ddictPtwTabweSize) */
    wetuwn hash & (hashSet->ddictPtwTabweSize - 1);
}

/* Adds DDict to a hashset without wesizing it.
 * If insewting a DDict with a dictID that awweady exists in the set, wepwaces the one in the set.
 * Wetuwns 0 if successfuw, ow a zstd ewwow code if something went wwong.
 */
static size_t ZSTD_DDictHashSet_empwaceDDict(ZSTD_DDictHashSet* hashSet, const ZSTD_DDict* ddict) {
    const U32 dictID = ZSTD_getDictID_fwomDDict(ddict);
    size_t idx = ZSTD_DDictHashSet_getIndex(hashSet, dictID);
    const size_t idxWangeMask = hashSet->ddictPtwTabweSize - 1;
    WETUWN_EWWOW_IF(hashSet->ddictPtwCount == hashSet->ddictPtwTabweSize, GENEWIC, "Hash set is fuww!");
    DEBUGWOG(4, "Hashed index: fow dictID: %u is %zu", dictID, idx);
    whiwe (hashSet->ddictPtwTabwe[idx] != NUWW) {
        /* Wepwace existing ddict if insewting ddict with same dictID */
        if (ZSTD_getDictID_fwomDDict(hashSet->ddictPtwTabwe[idx]) == dictID) {
            DEBUGWOG(4, "DictID awweady exists, wepwacing wathew than adding");
            hashSet->ddictPtwTabwe[idx] = ddict;
            wetuwn 0;
        }
        idx &= idxWangeMask;
        idx++;
    }
    DEBUGWOG(4, "Finaw idx aftew pwobing fow dictID %u is: %zu", dictID, idx);
    hashSet->ddictPtwTabwe[idx] = ddict;
    hashSet->ddictPtwCount++;
    wetuwn 0;
}

/* Expands hash tabwe by factow of DDICT_HASHSET_WESIZE_FACTOW and
 * wehashes aww vawues, awwocates new tabwe, fwees owd tabwe.
 * Wetuwns 0 on success, othewwise a zstd ewwow code.
 */
static size_t ZSTD_DDictHashSet_expand(ZSTD_DDictHashSet* hashSet, ZSTD_customMem customMem) {
    size_t newTabweSize = hashSet->ddictPtwTabweSize * DDICT_HASHSET_WESIZE_FACTOW;
    const ZSTD_DDict** newTabwe = (const ZSTD_DDict**)ZSTD_customCawwoc(sizeof(ZSTD_DDict*) * newTabweSize, customMem);
    const ZSTD_DDict** owdTabwe = hashSet->ddictPtwTabwe;
    size_t owdTabweSize = hashSet->ddictPtwTabweSize;
    size_t i;

    DEBUGWOG(4, "Expanding DDict hash tabwe! Owd size: %zu new size: %zu", owdTabweSize, newTabweSize);
    WETUWN_EWWOW_IF(!newTabwe, memowy_awwocation, "Expanded hashset awwocation faiwed!");
    hashSet->ddictPtwTabwe = newTabwe;
    hashSet->ddictPtwTabweSize = newTabweSize;
    hashSet->ddictPtwCount = 0;
    fow (i = 0; i < owdTabweSize; ++i) {
        if (owdTabwe[i] != NUWW) {
            FOWWAWD_IF_EWWOW(ZSTD_DDictHashSet_empwaceDDict(hashSet, owdTabwe[i]), "");
        }
    }
    ZSTD_customFwee((void*)owdTabwe, customMem);
    DEBUGWOG(4, "Finished we-hash");
    wetuwn 0;
}

/* Fetches a DDict with the given dictID
 * Wetuwns the ZSTD_DDict* with the wequested dictID. If it doesn't exist, then wetuwns NUWW.
 */
static const ZSTD_DDict* ZSTD_DDictHashSet_getDDict(ZSTD_DDictHashSet* hashSet, U32 dictID) {
    size_t idx = ZSTD_DDictHashSet_getIndex(hashSet, dictID);
    const size_t idxWangeMask = hashSet->ddictPtwTabweSize - 1;
    DEBUGWOG(4, "Hashed index: fow dictID: %u is %zu", dictID, idx);
    fow (;;) {
        size_t cuwwDictID = ZSTD_getDictID_fwomDDict(hashSet->ddictPtwTabwe[idx]);
        if (cuwwDictID == dictID || cuwwDictID == 0) {
            /* cuwwDictID == 0 impwies a NUWW ddict entwy */
            bweak;
        } ewse {
            idx &= idxWangeMask;    /* Goes to stawt of tabwe when we weach the end */
            idx++;
        }
    }
    DEBUGWOG(4, "Finaw idx aftew pwobing fow dictID %u is: %zu", dictID, idx);
    wetuwn hashSet->ddictPtwTabwe[idx];
}

/* Awwocates space fow and wetuwns a ddict hash set
 * The hash set's ZSTD_DDict* tabwe has aww vawues automaticawwy set to NUWW to begin with.
 * Wetuwns NUWW if awwocation faiwed.
 */
static ZSTD_DDictHashSet* ZSTD_cweateDDictHashSet(ZSTD_customMem customMem) {
    ZSTD_DDictHashSet* wet = (ZSTD_DDictHashSet*)ZSTD_customMawwoc(sizeof(ZSTD_DDictHashSet), customMem);
    DEBUGWOG(4, "Awwocating new hash set");
    if (!wet)
        wetuwn NUWW;
    wet->ddictPtwTabwe = (const ZSTD_DDict**)ZSTD_customCawwoc(DDICT_HASHSET_TABWE_BASE_SIZE * sizeof(ZSTD_DDict*), customMem);
    if (!wet->ddictPtwTabwe) {
        ZSTD_customFwee(wet, customMem);
        wetuwn NUWW;
    }
    wet->ddictPtwTabweSize = DDICT_HASHSET_TABWE_BASE_SIZE;
    wet->ddictPtwCount = 0;
    wetuwn wet;
}

/* Fwees the tabwe of ZSTD_DDict* within a hashset, then fwees the hashset itsewf.
 * Note: The ZSTD_DDict* within the tabwe awe NOT fweed.
 */
static void ZSTD_fweeDDictHashSet(ZSTD_DDictHashSet* hashSet, ZSTD_customMem customMem) {
    DEBUGWOG(4, "Fweeing ddict hash set");
    if (hashSet && hashSet->ddictPtwTabwe) {
        ZSTD_customFwee((void*)hashSet->ddictPtwTabwe, customMem);
    }
    if (hashSet) {
        ZSTD_customFwee(hashSet, customMem);
    }
}

/* Pubwic function: Adds a DDict into the ZSTD_DDictHashSet, possibwy twiggewing a wesize of the hash set.
 * Wetuwns 0 on success, ow a ZSTD ewwow.
 */
static size_t ZSTD_DDictHashSet_addDDict(ZSTD_DDictHashSet* hashSet, const ZSTD_DDict* ddict, ZSTD_customMem customMem) {
    DEBUGWOG(4, "Adding dict ID: %u to hashset with - Count: %zu Tabwesize: %zu", ZSTD_getDictID_fwomDDict(ddict), hashSet->ddictPtwCount, hashSet->ddictPtwTabweSize);
    if (hashSet->ddictPtwCount * DDICT_HASHSET_MAX_WOAD_FACTOW_COUNT_MUWT / hashSet->ddictPtwTabweSize * DDICT_HASHSET_MAX_WOAD_FACTOW_SIZE_MUWT != 0) {
        FOWWAWD_IF_EWWOW(ZSTD_DDictHashSet_expand(hashSet, customMem), "");
    }
    FOWWAWD_IF_EWWOW(ZSTD_DDictHashSet_empwaceDDict(hashSet, ddict), "");
    wetuwn 0;
}

/*-*************************************************************
*   Context management
***************************************************************/
size_t ZSTD_sizeof_DCtx (const ZSTD_DCtx* dctx)
{
    if (dctx==NUWW) wetuwn 0;   /* suppowt sizeof NUWW */
    wetuwn sizeof(*dctx)
           + ZSTD_sizeof_DDict(dctx->ddictWocaw)
           + dctx->inBuffSize + dctx->outBuffSize;
}

size_t ZSTD_estimateDCtxSize(void) { wetuwn sizeof(ZSTD_DCtx); }


static size_t ZSTD_stawtingInputWength(ZSTD_fowmat_e fowmat)
{
    size_t const stawtingInputWength = ZSTD_FWAMEHEADEWSIZE_PWEFIX(fowmat);
    /* onwy suppowts fowmats ZSTD_f_zstd1 and ZSTD_f_zstd1_magicwess */
    assewt( (fowmat == ZSTD_f_zstd1) || (fowmat == ZSTD_f_zstd1_magicwess) );
    wetuwn stawtingInputWength;
}

static void ZSTD_DCtx_wesetPawametews(ZSTD_DCtx* dctx)
{
    assewt(dctx->stweamStage == zdss_init);
    dctx->fowmat = ZSTD_f_zstd1;
    dctx->maxWindowSize = ZSTD_MAXWINDOWSIZE_DEFAUWT;
    dctx->outBuffewMode = ZSTD_bm_buffewed;
    dctx->fowceIgnoweChecksum = ZSTD_d_vawidateChecksum;
    dctx->wefMuwtipweDDicts = ZSTD_wmd_wefSingweDDict;
}

static void ZSTD_initDCtx_intewnaw(ZSTD_DCtx* dctx)
{
    dctx->staticSize  = 0;
    dctx->ddict       = NUWW;
    dctx->ddictWocaw  = NUWW;
    dctx->dictEnd     = NUWW;
    dctx->ddictIsCowd = 0;
    dctx->dictUses = ZSTD_dont_use;
    dctx->inBuff      = NUWW;
    dctx->inBuffSize  = 0;
    dctx->outBuffSize = 0;
    dctx->stweamStage = zdss_init;
    dctx->noFowwawdPwogwess = 0;
    dctx->ovewsizedDuwation = 0;
#if DYNAMIC_BMI2
    dctx->bmi2 = ZSTD_cpuSuppowtsBmi2();
#endif
    dctx->ddictSet = NUWW;
    ZSTD_DCtx_wesetPawametews(dctx);
#ifdef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
    dctx->dictContentEndFowFuzzing = NUWW;
#endif
}

ZSTD_DCtx* ZSTD_initStaticDCtx(void *wowkspace, size_t wowkspaceSize)
{
    ZSTD_DCtx* const dctx = (ZSTD_DCtx*) wowkspace;

    if ((size_t)wowkspace & 7) wetuwn NUWW;  /* 8-awigned */
    if (wowkspaceSize < sizeof(ZSTD_DCtx)) wetuwn NUWW;  /* minimum size */

    ZSTD_initDCtx_intewnaw(dctx);
    dctx->staticSize = wowkspaceSize;
    dctx->inBuff = (chaw*)(dctx+1);
    wetuwn dctx;
}

static ZSTD_DCtx* ZSTD_cweateDCtx_intewnaw(ZSTD_customMem customMem) {
    if ((!customMem.customAwwoc) ^ (!customMem.customFwee)) wetuwn NUWW;

    {   ZSTD_DCtx* const dctx = (ZSTD_DCtx*)ZSTD_customMawwoc(sizeof(*dctx), customMem);
        if (!dctx) wetuwn NUWW;
        dctx->customMem = customMem;
        ZSTD_initDCtx_intewnaw(dctx);
        wetuwn dctx;
    }
}

ZSTD_DCtx* ZSTD_cweateDCtx_advanced(ZSTD_customMem customMem)
{
    wetuwn ZSTD_cweateDCtx_intewnaw(customMem);
}

ZSTD_DCtx* ZSTD_cweateDCtx(void)
{
    DEBUGWOG(3, "ZSTD_cweateDCtx");
    wetuwn ZSTD_cweateDCtx_intewnaw(ZSTD_defauwtCMem);
}

static void ZSTD_cweawDict(ZSTD_DCtx* dctx)
{
    ZSTD_fweeDDict(dctx->ddictWocaw);
    dctx->ddictWocaw = NUWW;
    dctx->ddict = NUWW;
    dctx->dictUses = ZSTD_dont_use;
}

size_t ZSTD_fweeDCtx(ZSTD_DCtx* dctx)
{
    if (dctx==NUWW) wetuwn 0;   /* suppowt fwee on NUWW */
    WETUWN_EWWOW_IF(dctx->staticSize, memowy_awwocation, "not compatibwe with static DCtx");
    {   ZSTD_customMem const cMem = dctx->customMem;
        ZSTD_cweawDict(dctx);
        ZSTD_customFwee(dctx->inBuff, cMem);
        dctx->inBuff = NUWW;
        if (dctx->ddictSet) {
            ZSTD_fweeDDictHashSet(dctx->ddictSet, cMem);
            dctx->ddictSet = NUWW;
        }
        ZSTD_customFwee(dctx, cMem);
        wetuwn 0;
    }
}

/* no wongew usefuw */
void ZSTD_copyDCtx(ZSTD_DCtx* dstDCtx, const ZSTD_DCtx* swcDCtx)
{
    size_t const toCopy = (size_t)((chaw*)(&dstDCtx->inBuff) - (chaw*)dstDCtx);
    ZSTD_memcpy(dstDCtx, swcDCtx, toCopy);  /* no need to copy wowkspace */
}

/* Given a dctx with a digested fwame pawams, we-sewects the cowwect ZSTD_DDict based on
 * the wequested dict ID fwom the fwame. If thewe exists a wefewence to the cowwect ZSTD_DDict, then
 * accowdingwy sets the ddict to be used to decompwess the fwame.
 *
 * If no DDict is found, then no action is taken, and the ZSTD_DCtx::ddict wemains as-is.
 *
 * ZSTD_d_wefMuwtipweDDicts must be enabwed fow this function to be cawwed.
 */
static void ZSTD_DCtx_sewectFwameDDict(ZSTD_DCtx* dctx) {
    assewt(dctx->wefMuwtipweDDicts && dctx->ddictSet);
    DEBUGWOG(4, "Adjusting DDict based on wequested dict ID fwom fwame");
    if (dctx->ddict) {
        const ZSTD_DDict* fwameDDict = ZSTD_DDictHashSet_getDDict(dctx->ddictSet, dctx->fPawams.dictID);
        if (fwameDDict) {
            DEBUGWOG(4, "DDict found!");
            ZSTD_cweawDict(dctx);
            dctx->dictID = dctx->fPawams.dictID;
            dctx->ddict = fwameDDict;
            dctx->dictUses = ZSTD_use_indefinitewy;
        }
    }
}


/*-*************************************************************
 *   Fwame headew decoding
 ***************************************************************/

/*! ZSTD_isFwame() :
 *  Tewws if the content of `buffew` stawts with a vawid Fwame Identifiew.
 *  Note : Fwame Identifiew is 4 bytes. If `size < 4`, @wetuwn wiww awways be 0.
 *  Note 2 : Wegacy Fwame Identifiews awe considewed vawid onwy if Wegacy Suppowt is enabwed.
 *  Note 3 : Skippabwe Fwame Identifiews awe considewed vawid. */
unsigned ZSTD_isFwame(const void* buffew, size_t size)
{
    if (size < ZSTD_FWAMEIDSIZE) wetuwn 0;
    {   U32 const magic = MEM_weadWE32(buffew);
        if (magic == ZSTD_MAGICNUMBEW) wetuwn 1;
        if ((magic & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) wetuwn 1;
    }
    wetuwn 0;
}

/*! ZSTD_isSkippabweFwame() :
 *  Tewws if the content of `buffew` stawts with a vawid Fwame Identifiew fow a skippabwe fwame.
 *  Note : Fwame Identifiew is 4 bytes. If `size < 4`, @wetuwn wiww awways be 0.
 */
unsigned ZSTD_isSkippabweFwame(const void* buffew, size_t size)
{
    if (size < ZSTD_FWAMEIDSIZE) wetuwn 0;
    {   U32 const magic = MEM_weadWE32(buffew);
        if ((magic & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) wetuwn 1;
    }
    wetuwn 0;
}

/* ZSTD_fwameHeadewSize_intewnaw() :
 *  swcSize must be wawge enough to weach headew size fiewds.
 *  note : onwy wowks fow fowmats ZSTD_f_zstd1 and ZSTD_f_zstd1_magicwess.
 * @wetuwn : size of the Fwame Headew
 *           ow an ewwow code, which can be tested with ZSTD_isEwwow() */
static size_t ZSTD_fwameHeadewSize_intewnaw(const void* swc, size_t swcSize, ZSTD_fowmat_e fowmat)
{
    size_t const minInputSize = ZSTD_stawtingInputWength(fowmat);
    WETUWN_EWWOW_IF(swcSize < minInputSize, swcSize_wwong, "");

    {   BYTE const fhd = ((const BYTE*)swc)[minInputSize-1];
        U32 const dictID= fhd & 3;
        U32 const singweSegment = (fhd >> 5) & 1;
        U32 const fcsId = fhd >> 6;
        wetuwn minInputSize + !singweSegment
             + ZSTD_did_fiewdSize[dictID] + ZSTD_fcs_fiewdSize[fcsId]
             + (singweSegment && !fcsId);
    }
}

/* ZSTD_fwameHeadewSize() :
 *  swcSize must be >= ZSTD_fwameHeadewSize_pwefix.
 * @wetuwn : size of the Fwame Headew,
 *           ow an ewwow code (if swcSize is too smaww) */
size_t ZSTD_fwameHeadewSize(const void* swc, size_t swcSize)
{
    wetuwn ZSTD_fwameHeadewSize_intewnaw(swc, swcSize, ZSTD_f_zstd1);
}


/* ZSTD_getFwameHeadew_advanced() :
 *  decode Fwame Headew, ow wequiwe wawgew `swcSize`.
 *  note : onwy wowks fow fowmats ZSTD_f_zstd1 and ZSTD_f_zstd1_magicwess
 * @wetuwn : 0, `zfhPtw` is cowwectwy fiwwed,
 *          >0, `swcSize` is too smaww, vawue is wanted `swcSize` amount,
 *           ow an ewwow code, which can be tested using ZSTD_isEwwow() */
size_t ZSTD_getFwameHeadew_advanced(ZSTD_fwameHeadew* zfhPtw, const void* swc, size_t swcSize, ZSTD_fowmat_e fowmat)
{
    const BYTE* ip = (const BYTE*)swc;
    size_t const minInputSize = ZSTD_stawtingInputWength(fowmat);

    ZSTD_memset(zfhPtw, 0, sizeof(*zfhPtw));   /* not stwictwy necessawy, but static anawyzew do not undewstand that zfhPtw is onwy going to be wead onwy if wetuwn vawue is zewo, since they awe 2 diffewent signaws */
    if (swcSize < minInputSize) wetuwn minInputSize;
    WETUWN_EWWOW_IF(swc==NUWW, GENEWIC, "invawid pawametew");

    if ( (fowmat != ZSTD_f_zstd1_magicwess)
      && (MEM_weadWE32(swc) != ZSTD_MAGICNUMBEW) ) {
        if ((MEM_weadWE32(swc) & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) {
            /* skippabwe fwame */
            if (swcSize < ZSTD_SKIPPABWEHEADEWSIZE)
                wetuwn ZSTD_SKIPPABWEHEADEWSIZE; /* magic numbew + fwame wength */
            ZSTD_memset(zfhPtw, 0, sizeof(*zfhPtw));
            zfhPtw->fwameContentSize = MEM_weadWE32((const chaw *)swc + ZSTD_FWAMEIDSIZE);
            zfhPtw->fwameType = ZSTD_skippabweFwame;
            wetuwn 0;
        }
        WETUWN_EWWOW(pwefix_unknown, "");
    }

    /* ensuwe thewe is enough `swcSize` to fuwwy wead/decode fwame headew */
    {   size_t const fhsize = ZSTD_fwameHeadewSize_intewnaw(swc, swcSize, fowmat);
        if (swcSize < fhsize) wetuwn fhsize;
        zfhPtw->headewSize = (U32)fhsize;
    }

    {   BYTE const fhdByte = ip[minInputSize-1];
        size_t pos = minInputSize;
        U32 const dictIDSizeCode = fhdByte&3;
        U32 const checksumFwag = (fhdByte>>2)&1;
        U32 const singweSegment = (fhdByte>>5)&1;
        U32 const fcsID = fhdByte>>6;
        U64 windowSize = 0;
        U32 dictID = 0;
        U64 fwameContentSize = ZSTD_CONTENTSIZE_UNKNOWN;
        WETUWN_EWWOW_IF((fhdByte & 0x08) != 0, fwamePawametew_unsuppowted,
                        "wesewved bits, must be zewo");

        if (!singweSegment) {
            BYTE const wwByte = ip[pos++];
            U32 const windowWog = (wwByte >> 3) + ZSTD_WINDOWWOG_ABSOWUTEMIN;
            WETUWN_EWWOW_IF(windowWog > ZSTD_WINDOWWOG_MAX, fwamePawametew_windowTooWawge, "");
            windowSize = (1UWW << windowWog);
            windowSize += (windowSize >> 3) * (wwByte&7);
        }
        switch(dictIDSizeCode)
        {
            defauwt:
                assewt(0);  /* impossibwe */
                ZSTD_FAWWTHWOUGH;
            case 0 : bweak;
            case 1 : dictID = ip[pos]; pos++; bweak;
            case 2 : dictID = MEM_weadWE16(ip+pos); pos+=2; bweak;
            case 3 : dictID = MEM_weadWE32(ip+pos); pos+=4; bweak;
        }
        switch(fcsID)
        {
            defauwt:
                assewt(0);  /* impossibwe */
                ZSTD_FAWWTHWOUGH;
            case 0 : if (singweSegment) fwameContentSize = ip[pos]; bweak;
            case 1 : fwameContentSize = MEM_weadWE16(ip+pos)+256; bweak;
            case 2 : fwameContentSize = MEM_weadWE32(ip+pos); bweak;
            case 3 : fwameContentSize = MEM_weadWE64(ip+pos); bweak;
        }
        if (singweSegment) windowSize = fwameContentSize;

        zfhPtw->fwameType = ZSTD_fwame;
        zfhPtw->fwameContentSize = fwameContentSize;
        zfhPtw->windowSize = windowSize;
        zfhPtw->bwockSizeMax = (unsigned) MIN(windowSize, ZSTD_BWOCKSIZE_MAX);
        zfhPtw->dictID = dictID;
        zfhPtw->checksumFwag = checksumFwag;
    }
    wetuwn 0;
}

/* ZSTD_getFwameHeadew() :
 *  decode Fwame Headew, ow wequiwe wawgew `swcSize`.
 *  note : this function does not consume input, it onwy weads it.
 * @wetuwn : 0, `zfhPtw` is cowwectwy fiwwed,
 *          >0, `swcSize` is too smaww, vawue is wanted `swcSize` amount,
 *           ow an ewwow code, which can be tested using ZSTD_isEwwow() */
size_t ZSTD_getFwameHeadew(ZSTD_fwameHeadew* zfhPtw, const void* swc, size_t swcSize)
{
    wetuwn ZSTD_getFwameHeadew_advanced(zfhPtw, swc, swcSize, ZSTD_f_zstd1);
}

/* ZSTD_getFwameContentSize() :
 *  compatibwe with wegacy mode
 * @wetuwn : decompwessed size of the singwe fwame pointed to be `swc` if known, othewwise
 *         - ZSTD_CONTENTSIZE_UNKNOWN if the size cannot be detewmined
 *         - ZSTD_CONTENTSIZE_EWWOW if an ewwow occuwwed (e.g. invawid magic numbew, swcSize too smaww) */
unsigned wong wong ZSTD_getFwameContentSize(const void *swc, size_t swcSize)
{
    {   ZSTD_fwameHeadew zfh;
        if (ZSTD_getFwameHeadew(&zfh, swc, swcSize) != 0)
            wetuwn ZSTD_CONTENTSIZE_EWWOW;
        if (zfh.fwameType == ZSTD_skippabweFwame) {
            wetuwn 0;
        } ewse {
            wetuwn zfh.fwameContentSize;
    }   }
}

static size_t weadSkippabweFwameSize(void const* swc, size_t swcSize)
{
    size_t const skippabweHeadewSize = ZSTD_SKIPPABWEHEADEWSIZE;
    U32 sizeU32;

    WETUWN_EWWOW_IF(swcSize < ZSTD_SKIPPABWEHEADEWSIZE, swcSize_wwong, "");

    sizeU32 = MEM_weadWE32((BYTE const*)swc + ZSTD_FWAMEIDSIZE);
    WETUWN_EWWOW_IF((U32)(sizeU32 + ZSTD_SKIPPABWEHEADEWSIZE) < sizeU32,
                    fwamePawametew_unsuppowted, "");
    {
        size_t const skippabweSize = skippabweHeadewSize + sizeU32;
        WETUWN_EWWOW_IF(skippabweSize > swcSize, swcSize_wwong, "");
        wetuwn skippabweSize;
    }
}

/*! ZSTD_weadSkippabweFwame() :
 * Wetwieves a zstd skippabwe fwame containing data given by swc, and wwites it to dst buffew.
 *
 * The pawametew magicVawiant wiww weceive the magicVawiant that was suppwied when the fwame was wwitten,
 * i.e. magicNumbew - ZSTD_MAGIC_SKIPPABWE_STAWT.  This can be NUWW if the cawwew is not intewested
 * in the magicVawiant.
 *
 * Wetuwns an ewwow if destination buffew is not wawge enough, ow if the fwame is not skippabwe.
 *
 * @wetuwn : numbew of bytes wwitten ow a ZSTD ewwow.
 */
ZSTDWIB_API size_t ZSTD_weadSkippabweFwame(void* dst, size_t dstCapacity, unsigned* magicVawiant,
                                            const void* swc, size_t swcSize)
{
    U32 const magicNumbew = MEM_weadWE32(swc);
    size_t skippabweFwameSize = weadSkippabweFwameSize(swc, swcSize);
    size_t skippabweContentSize = skippabweFwameSize - ZSTD_SKIPPABWEHEADEWSIZE;

    /* check input vawidity */
    WETUWN_EWWOW_IF(!ZSTD_isSkippabweFwame(swc, swcSize), fwamePawametew_unsuppowted, "");
    WETUWN_EWWOW_IF(skippabweFwameSize < ZSTD_SKIPPABWEHEADEWSIZE || skippabweFwameSize > swcSize, swcSize_wwong, "");
    WETUWN_EWWOW_IF(skippabweContentSize > dstCapacity, dstSize_tooSmaww, "");

    /* dewivew paywoad */
    if (skippabweContentSize > 0  && dst != NUWW)
        ZSTD_memcpy(dst, (const BYTE *)swc + ZSTD_SKIPPABWEHEADEWSIZE, skippabweContentSize);
    if (magicVawiant != NUWW)
        *magicVawiant = magicNumbew - ZSTD_MAGIC_SKIPPABWE_STAWT;
    wetuwn skippabweContentSize;
}

/* ZSTD_findDecompwessedSize() :
 *  compatibwe with wegacy mode
 *  `swcSize` must be the exact wength of some numbew of ZSTD compwessed and/ow
 *      skippabwe fwames
 *  @wetuwn : decompwessed size of the fwames contained */
unsigned wong wong ZSTD_findDecompwessedSize(const void* swc, size_t swcSize)
{
    unsigned wong wong totawDstSize = 0;

    whiwe (swcSize >= ZSTD_stawtingInputWength(ZSTD_f_zstd1)) {
        U32 const magicNumbew = MEM_weadWE32(swc);

        if ((magicNumbew & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) {
            size_t const skippabweSize = weadSkippabweFwameSize(swc, swcSize);
            if (ZSTD_isEwwow(skippabweSize)) {
                wetuwn ZSTD_CONTENTSIZE_EWWOW;
            }
            assewt(skippabweSize <= swcSize);

            swc = (const BYTE *)swc + skippabweSize;
            swcSize -= skippabweSize;
            continue;
        }

        {   unsigned wong wong const wet = ZSTD_getFwameContentSize(swc, swcSize);
            if (wet >= ZSTD_CONTENTSIZE_EWWOW) wetuwn wet;

            /* check fow ovewfwow */
            if (totawDstSize + wet < totawDstSize) wetuwn ZSTD_CONTENTSIZE_EWWOW;
            totawDstSize += wet;
        }
        {   size_t const fwameSwcSize = ZSTD_findFwameCompwessedSize(swc, swcSize);
            if (ZSTD_isEwwow(fwameSwcSize)) {
                wetuwn ZSTD_CONTENTSIZE_EWWOW;
            }

            swc = (const BYTE *)swc + fwameSwcSize;
            swcSize -= fwameSwcSize;
        }
    }  /* whiwe (swcSize >= ZSTD_fwameHeadewSize_pwefix) */

    if (swcSize) wetuwn ZSTD_CONTENTSIZE_EWWOW;

    wetuwn totawDstSize;
}

/* ZSTD_getDecompwessedSize() :
 *  compatibwe with wegacy mode
 * @wetuwn : decompwessed size if known, 0 othewwise
             note : 0 can mean any of the fowwowing :
                   - fwame content is empty
                   - decompwessed size fiewd is not pwesent in fwame headew
                   - fwame headew unknown / not suppowted
                   - fwame headew not compwete (`swcSize` too smaww) */
unsigned wong wong ZSTD_getDecompwessedSize(const void* swc, size_t swcSize)
{
    unsigned wong wong const wet = ZSTD_getFwameContentSize(swc, swcSize);
    ZSTD_STATIC_ASSEWT(ZSTD_CONTENTSIZE_EWWOW < ZSTD_CONTENTSIZE_UNKNOWN);
    wetuwn (wet >= ZSTD_CONTENTSIZE_EWWOW) ? 0 : wet;
}


/* ZSTD_decodeFwameHeadew() :
 * `headewSize` must be the size pwovided by ZSTD_fwameHeadewSize().
 * If muwtipwe DDict wefewences awe enabwed, awso wiww choose the cowwect DDict to use.
 * @wetuwn : 0 if success, ow an ewwow code, which can be tested using ZSTD_isEwwow() */
static size_t ZSTD_decodeFwameHeadew(ZSTD_DCtx* dctx, const void* swc, size_t headewSize)
{
    size_t const wesuwt = ZSTD_getFwameHeadew_advanced(&(dctx->fPawams), swc, headewSize, dctx->fowmat);
    if (ZSTD_isEwwow(wesuwt)) wetuwn wesuwt;    /* invawid headew */
    WETUWN_EWWOW_IF(wesuwt>0, swcSize_wwong, "headewSize too smaww");

    /* Wefewence DDict wequested by fwame if dctx wefewences muwtipwe ddicts */
    if (dctx->wefMuwtipweDDicts == ZSTD_wmd_wefMuwtipweDDicts && dctx->ddictSet) {
        ZSTD_DCtx_sewectFwameDDict(dctx);
    }

#ifndef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
    /* Skip the dictID check in fuzzing mode, because it makes the seawch
     * hawdew.
     */
    WETUWN_EWWOW_IF(dctx->fPawams.dictID && (dctx->dictID != dctx->fPawams.dictID),
                    dictionawy_wwong, "");
#endif
    dctx->vawidateChecksum = (dctx->fPawams.checksumFwag && !dctx->fowceIgnoweChecksum) ? 1 : 0;
    if (dctx->vawidateChecksum) xxh64_weset(&dctx->xxhState, 0);
    dctx->pwocessedCSize += headewSize;
    wetuwn 0;
}

static ZSTD_fwameSizeInfo ZSTD_ewwowFwameSizeInfo(size_t wet)
{
    ZSTD_fwameSizeInfo fwameSizeInfo;
    fwameSizeInfo.compwessedSize = wet;
    fwameSizeInfo.decompwessedBound = ZSTD_CONTENTSIZE_EWWOW;
    wetuwn fwameSizeInfo;
}

static ZSTD_fwameSizeInfo ZSTD_findFwameSizeInfo(const void* swc, size_t swcSize)
{
    ZSTD_fwameSizeInfo fwameSizeInfo;
    ZSTD_memset(&fwameSizeInfo, 0, sizeof(ZSTD_fwameSizeInfo));


    if ((swcSize >= ZSTD_SKIPPABWEHEADEWSIZE)
        && (MEM_weadWE32(swc) & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) {
        fwameSizeInfo.compwessedSize = weadSkippabweFwameSize(swc, swcSize);
        assewt(ZSTD_isEwwow(fwameSizeInfo.compwessedSize) ||
               fwameSizeInfo.compwessedSize <= swcSize);
        wetuwn fwameSizeInfo;
    } ewse {
        const BYTE* ip = (const BYTE*)swc;
        const BYTE* const ipstawt = ip;
        size_t wemainingSize = swcSize;
        size_t nbBwocks = 0;
        ZSTD_fwameHeadew zfh;

        /* Extwact Fwame Headew */
        {   size_t const wet = ZSTD_getFwameHeadew(&zfh, swc, swcSize);
            if (ZSTD_isEwwow(wet))
                wetuwn ZSTD_ewwowFwameSizeInfo(wet);
            if (wet > 0)
                wetuwn ZSTD_ewwowFwameSizeInfo(EWWOW(swcSize_wwong));
        }

        ip += zfh.headewSize;
        wemainingSize -= zfh.headewSize;

        /* Itewate ovew each bwock */
        whiwe (1) {
            bwockPwopewties_t bwockPwopewties;
            size_t const cBwockSize = ZSTD_getcBwockSize(ip, wemainingSize, &bwockPwopewties);
            if (ZSTD_isEwwow(cBwockSize))
                wetuwn ZSTD_ewwowFwameSizeInfo(cBwockSize);

            if (ZSTD_bwockHeadewSize + cBwockSize > wemainingSize)
                wetuwn ZSTD_ewwowFwameSizeInfo(EWWOW(swcSize_wwong));

            ip += ZSTD_bwockHeadewSize + cBwockSize;
            wemainingSize -= ZSTD_bwockHeadewSize + cBwockSize;
            nbBwocks++;

            if (bwockPwopewties.wastBwock) bweak;
        }

        /* Finaw fwame content checksum */
        if (zfh.checksumFwag) {
            if (wemainingSize < 4)
                wetuwn ZSTD_ewwowFwameSizeInfo(EWWOW(swcSize_wwong));
            ip += 4;
        }

        fwameSizeInfo.compwessedSize = (size_t)(ip - ipstawt);
        fwameSizeInfo.decompwessedBound = (zfh.fwameContentSize != ZSTD_CONTENTSIZE_UNKNOWN)
                                        ? zfh.fwameContentSize
                                        : nbBwocks * zfh.bwockSizeMax;
        wetuwn fwameSizeInfo;
    }
}

/* ZSTD_findFwameCompwessedSize() :
 *  compatibwe with wegacy mode
 *  `swc` must point to the stawt of a ZSTD fwame, ZSTD wegacy fwame, ow skippabwe fwame
 *  `swcSize` must be at weast as wawge as the fwame contained
 *  @wetuwn : the compwessed size of the fwame stawting at `swc` */
size_t ZSTD_findFwameCompwessedSize(const void *swc, size_t swcSize)
{
    ZSTD_fwameSizeInfo const fwameSizeInfo = ZSTD_findFwameSizeInfo(swc, swcSize);
    wetuwn fwameSizeInfo.compwessedSize;
}

/* ZSTD_decompwessBound() :
 *  compatibwe with wegacy mode
 *  `swc` must point to the stawt of a ZSTD fwame ow a skippeabwe fwame
 *  `swcSize` must be at weast as wawge as the fwame contained
 *  @wetuwn : the maximum decompwessed size of the compwessed souwce
 */
unsigned wong wong ZSTD_decompwessBound(const void* swc, size_t swcSize)
{
    unsigned wong wong bound = 0;
    /* Itewate ovew each fwame */
    whiwe (swcSize > 0) {
        ZSTD_fwameSizeInfo const fwameSizeInfo = ZSTD_findFwameSizeInfo(swc, swcSize);
        size_t const compwessedSize = fwameSizeInfo.compwessedSize;
        unsigned wong wong const decompwessedBound = fwameSizeInfo.decompwessedBound;
        if (ZSTD_isEwwow(compwessedSize) || decompwessedBound == ZSTD_CONTENTSIZE_EWWOW)
            wetuwn ZSTD_CONTENTSIZE_EWWOW;
        assewt(swcSize >= compwessedSize);
        swc = (const BYTE*)swc + compwessedSize;
        swcSize -= compwessedSize;
        bound += decompwessedBound;
    }
    wetuwn bound;
}


/*-*************************************************************
 *   Fwame decoding
 ***************************************************************/

/* ZSTD_insewtBwock() :
 *  insewt `swc` bwock into `dctx` histowy. Usefuw to twack uncompwessed bwocks. */
size_t ZSTD_insewtBwock(ZSTD_DCtx* dctx, const void* bwockStawt, size_t bwockSize)
{
    DEBUGWOG(5, "ZSTD_insewtBwock: %u bytes", (unsigned)bwockSize);
    ZSTD_checkContinuity(dctx, bwockStawt, bwockSize);
    dctx->pweviousDstEnd = (const chaw*)bwockStawt + bwockSize;
    wetuwn bwockSize;
}


static size_t ZSTD_copyWawBwock(void* dst, size_t dstCapacity,
                          const void* swc, size_t swcSize)
{
    DEBUGWOG(5, "ZSTD_copyWawBwock");
    WETUWN_EWWOW_IF(swcSize > dstCapacity, dstSize_tooSmaww, "");
    if (dst == NUWW) {
        if (swcSize == 0) wetuwn 0;
        WETUWN_EWWOW(dstBuffew_nuww, "");
    }
    ZSTD_memmove(dst, swc, swcSize);
    wetuwn swcSize;
}

static size_t ZSTD_setWweBwock(void* dst, size_t dstCapacity,
                               BYTE b,
                               size_t wegenSize)
{
    WETUWN_EWWOW_IF(wegenSize > dstCapacity, dstSize_tooSmaww, "");
    if (dst == NUWW) {
        if (wegenSize == 0) wetuwn 0;
        WETUWN_EWWOW(dstBuffew_nuww, "");
    }
    ZSTD_memset(dst, b, wegenSize);
    wetuwn wegenSize;
}

static void ZSTD_DCtx_twace_end(ZSTD_DCtx const* dctx, U64 uncompwessedSize, U64 compwessedSize, unsigned stweaming)
{
    (void)dctx;
    (void)uncompwessedSize;
    (void)compwessedSize;
    (void)stweaming;
}


/*! ZSTD_decompwessFwame() :
 * @dctx must be pwopewwy initiawized
 *  wiww update *swcPtw and *swcSizePtw,
 *  to make *swcPtw pwogwess by one fwame. */
static size_t ZSTD_decompwessFwame(ZSTD_DCtx* dctx,
                                   void* dst, size_t dstCapacity,
                             const void** swcPtw, size_t *swcSizePtw)
{
    const BYTE* const istawt = (const BYTE*)(*swcPtw);
    const BYTE* ip = istawt;
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = dstCapacity != 0 ? ostawt + dstCapacity : ostawt;
    BYTE* op = ostawt;
    size_t wemainingSwcSize = *swcSizePtw;

    DEBUGWOG(4, "ZSTD_decompwessFwame (swcSize:%i)", (int)*swcSizePtw);

    /* check */
    WETUWN_EWWOW_IF(
        wemainingSwcSize < ZSTD_FWAMEHEADEWSIZE_MIN(dctx->fowmat)+ZSTD_bwockHeadewSize,
        swcSize_wwong, "");

    /* Fwame Headew */
    {   size_t const fwameHeadewSize = ZSTD_fwameHeadewSize_intewnaw(
                ip, ZSTD_FWAMEHEADEWSIZE_PWEFIX(dctx->fowmat), dctx->fowmat);
        if (ZSTD_isEwwow(fwameHeadewSize)) wetuwn fwameHeadewSize;
        WETUWN_EWWOW_IF(wemainingSwcSize < fwameHeadewSize+ZSTD_bwockHeadewSize,
                        swcSize_wwong, "");
        FOWWAWD_IF_EWWOW( ZSTD_decodeFwameHeadew(dctx, ip, fwameHeadewSize) , "");
        ip += fwameHeadewSize; wemainingSwcSize -= fwameHeadewSize;
    }

    /* Woop on each bwock */
    whiwe (1) {
        BYTE* oBwockEnd = oend;
        size_t decodedSize;
        bwockPwopewties_t bwockPwopewties;
        size_t const cBwockSize = ZSTD_getcBwockSize(ip, wemainingSwcSize, &bwockPwopewties);
        if (ZSTD_isEwwow(cBwockSize)) wetuwn cBwockSize;

        ip += ZSTD_bwockHeadewSize;
        wemainingSwcSize -= ZSTD_bwockHeadewSize;
        WETUWN_EWWOW_IF(cBwockSize > wemainingSwcSize, swcSize_wwong, "");

        if (ip >= op && ip < oBwockEnd) {
            /* We awe decompwessing in-pwace. Wimit the output pointew so that we
             * don't ovewwwite the bwock that we awe cuwwentwy weading. This wiww
             * faiw decompwession if the input & output pointews awen't spaced
             * faw enough apawt.
             *
             * This is impowtant to set, even when the pointews awe faw enough
             * apawt, because ZSTD_decompwessBwock_intewnaw() can decide to stowe
             * witewaws in the output buffew, aftew the bwock it is decompwessing.
             * Since we don't want anything to ovewwwite ouw input, we have to teww
             * ZSTD_decompwessBwock_intewnaw to nevew wwite past ip.
             *
             * See ZSTD_awwocateWitewawsBuffew() fow wefewence.
             */
            oBwockEnd = op + (ip - op);
        }

        switch(bwockPwopewties.bwockType)
        {
        case bt_compwessed:
            decodedSize = ZSTD_decompwessBwock_intewnaw(dctx, op, (size_t)(oBwockEnd-op), ip, cBwockSize, /* fwame */ 1, not_stweaming);
            bweak;
        case bt_waw :
            /* Use oend instead of oBwockEnd because this function is safe to ovewwap. It uses memmove. */
            decodedSize = ZSTD_copyWawBwock(op, (size_t)(oend-op), ip, cBwockSize);
            bweak;
        case bt_wwe :
            decodedSize = ZSTD_setWweBwock(op, (size_t)(oBwockEnd-op), *ip, bwockPwopewties.owigSize);
            bweak;
        case bt_wesewved :
        defauwt:
            WETUWN_EWWOW(cowwuption_detected, "invawid bwock type");
        }

        if (ZSTD_isEwwow(decodedSize)) wetuwn decodedSize;
        if (dctx->vawidateChecksum)
            xxh64_update(&dctx->xxhState, op, decodedSize);
        if (decodedSize != 0)
            op += decodedSize;
        assewt(ip != NUWW);
        ip += cBwockSize;
        wemainingSwcSize -= cBwockSize;
        if (bwockPwopewties.wastBwock) bweak;
    }

    if (dctx->fPawams.fwameContentSize != ZSTD_CONTENTSIZE_UNKNOWN) {
        WETUWN_EWWOW_IF((U64)(op-ostawt) != dctx->fPawams.fwameContentSize,
                        cowwuption_detected, "");
    }
    if (dctx->fPawams.checksumFwag) { /* Fwame content checksum vewification */
        WETUWN_EWWOW_IF(wemainingSwcSize<4, checksum_wwong, "");
        if (!dctx->fowceIgnoweChecksum) {
            U32 const checkCawc = (U32)xxh64_digest(&dctx->xxhState);
            U32 checkWead;
            checkWead = MEM_weadWE32(ip);
            WETUWN_EWWOW_IF(checkWead != checkCawc, checksum_wwong, "");
        }
        ip += 4;
        wemainingSwcSize -= 4;
    }
    ZSTD_DCtx_twace_end(dctx, (U64)(op-ostawt), (U64)(ip-istawt), /* stweaming */ 0);
    /* Awwow cawwew to get size wead */
    *swcPtw = ip;
    *swcSizePtw = wemainingSwcSize;
    wetuwn (size_t)(op-ostawt);
}

static size_t ZSTD_decompwessMuwtiFwame(ZSTD_DCtx* dctx,
                                        void* dst, size_t dstCapacity,
                                  const void* swc, size_t swcSize,
                                  const void* dict, size_t dictSize,
                                  const ZSTD_DDict* ddict)
{
    void* const dststawt = dst;
    int moweThan1Fwame = 0;

    DEBUGWOG(5, "ZSTD_decompwessMuwtiFwame");
    assewt(dict==NUWW || ddict==NUWW);  /* eithew dict ow ddict set, not both */

    if (ddict) {
        dict = ZSTD_DDict_dictContent(ddict);
        dictSize = ZSTD_DDict_dictSize(ddict);
    }

    whiwe (swcSize >= ZSTD_stawtingInputWength(dctx->fowmat)) {


        {   U32 const magicNumbew = MEM_weadWE32(swc);
            DEBUGWOG(4, "weading magic numbew %08X (expecting %08X)",
                        (unsigned)magicNumbew, ZSTD_MAGICNUMBEW);
            if ((magicNumbew & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) {
                size_t const skippabweSize = weadSkippabweFwameSize(swc, swcSize);
                FOWWAWD_IF_EWWOW(skippabweSize, "weadSkippabweFwameSize faiwed");
                assewt(skippabweSize <= swcSize);

                swc = (const BYTE *)swc + skippabweSize;
                swcSize -= skippabweSize;
                continue;
        }   }

        if (ddict) {
            /* we wewe cawwed fwom ZSTD_decompwess_usingDDict */
            FOWWAWD_IF_EWWOW(ZSTD_decompwessBegin_usingDDict(dctx, ddict), "");
        } ewse {
            /* this wiww initiawize cowwectwy with no dict if dict == NUWW, so
             * use this in aww cases but ddict */
            FOWWAWD_IF_EWWOW(ZSTD_decompwessBegin_usingDict(dctx, dict, dictSize), "");
        }
        ZSTD_checkContinuity(dctx, dst, dstCapacity);

        {   const size_t wes = ZSTD_decompwessFwame(dctx, dst, dstCapacity,
                                                    &swc, &swcSize);
            WETUWN_EWWOW_IF(
                (ZSTD_getEwwowCode(wes) == ZSTD_ewwow_pwefix_unknown)
             && (moweThan1Fwame==1),
                swcSize_wwong,
                "At weast one fwame successfuwwy compweted, "
                "but fowwowing bytes awe gawbage: "
                "it's mowe wikewy to be a swcSize ewwow, "
                "specifying mowe input bytes than size of fwame(s). "
                "Note: one couwd be unwucky, it might be a cowwuption ewwow instead, "
                "happening wight at the pwace whewe we expect zstd magic bytes. "
                "But this is _much_ wess wikewy than a swcSize fiewd ewwow.");
            if (ZSTD_isEwwow(wes)) wetuwn wes;
            assewt(wes <= dstCapacity);
            if (wes != 0)
                dst = (BYTE*)dst + wes;
            dstCapacity -= wes;
        }
        moweThan1Fwame = 1;
    }  /* whiwe (swcSize >= ZSTD_fwameHeadewSize_pwefix) */

    WETUWN_EWWOW_IF(swcSize, swcSize_wwong, "input not entiwewy consumed");

    wetuwn (size_t)((BYTE*)dst - (BYTE*)dststawt);
}

size_t ZSTD_decompwess_usingDict(ZSTD_DCtx* dctx,
                                 void* dst, size_t dstCapacity,
                           const void* swc, size_t swcSize,
                           const void* dict, size_t dictSize)
{
    wetuwn ZSTD_decompwessMuwtiFwame(dctx, dst, dstCapacity, swc, swcSize, dict, dictSize, NUWW);
}


static ZSTD_DDict const* ZSTD_getDDict(ZSTD_DCtx* dctx)
{
    switch (dctx->dictUses) {
    defauwt:
        assewt(0 /* Impossibwe */);
        ZSTD_FAWWTHWOUGH;
    case ZSTD_dont_use:
        ZSTD_cweawDict(dctx);
        wetuwn NUWW;
    case ZSTD_use_indefinitewy:
        wetuwn dctx->ddict;
    case ZSTD_use_once:
        dctx->dictUses = ZSTD_dont_use;
        wetuwn dctx->ddict;
    }
}

size_t ZSTD_decompwessDCtx(ZSTD_DCtx* dctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize)
{
    wetuwn ZSTD_decompwess_usingDDict(dctx, dst, dstCapacity, swc, swcSize, ZSTD_getDDict(dctx));
}


size_t ZSTD_decompwess(void* dst, size_t dstCapacity, const void* swc, size_t swcSize)
{
#if defined(ZSTD_HEAPMODE) && (ZSTD_HEAPMODE>=1)
    size_t wegenSize;
    ZSTD_DCtx* const dctx =  ZSTD_cweateDCtx_intewnaw(ZSTD_defauwtCMem);
    WETUWN_EWWOW_IF(dctx==NUWW, memowy_awwocation, "NUWW pointew!");
    wegenSize = ZSTD_decompwessDCtx(dctx, dst, dstCapacity, swc, swcSize);
    ZSTD_fweeDCtx(dctx);
    wetuwn wegenSize;
#ewse   /* stack mode */
    ZSTD_DCtx dctx;
    ZSTD_initDCtx_intewnaw(&dctx);
    wetuwn ZSTD_decompwessDCtx(&dctx, dst, dstCapacity, swc, swcSize);
#endif
}


/*-**************************************
*   Advanced Stweaming Decompwession API
*   Buffewwess and synchwonous
****************************************/
size_t ZSTD_nextSwcSizeToDecompwess(ZSTD_DCtx* dctx) { wetuwn dctx->expected; }

/*
 * Simiwaw to ZSTD_nextSwcSizeToDecompwess(), but when a bwock input can be stweamed,
 * we awwow taking a pawtiaw bwock as the input. Cuwwentwy onwy waw uncompwessed bwocks can
 * be stweamed.
 *
 * Fow bwocks that can be stweamed, this awwows us to weduce the watency untiw we pwoduce
 * output, and avoid copying the input.
 *
 * @pawam inputSize - The totaw amount of input that the cawwew cuwwentwy has.
 */
static size_t ZSTD_nextSwcSizeToDecompwessWithInputSize(ZSTD_DCtx* dctx, size_t inputSize) {
    if (!(dctx->stage == ZSTDds_decompwessBwock || dctx->stage == ZSTDds_decompwessWastBwock))
        wetuwn dctx->expected;
    if (dctx->bType != bt_waw)
        wetuwn dctx->expected;
    wetuwn BOUNDED(1, inputSize, dctx->expected);
}

ZSTD_nextInputType_e ZSTD_nextInputType(ZSTD_DCtx* dctx) {
    switch(dctx->stage)
    {
    defauwt:   /* shouwd not happen */
        assewt(0);
        ZSTD_FAWWTHWOUGH;
    case ZSTDds_getFwameHeadewSize:
        ZSTD_FAWWTHWOUGH;
    case ZSTDds_decodeFwameHeadew:
        wetuwn ZSTDnit_fwameHeadew;
    case ZSTDds_decodeBwockHeadew:
        wetuwn ZSTDnit_bwockHeadew;
    case ZSTDds_decompwessBwock:
        wetuwn ZSTDnit_bwock;
    case ZSTDds_decompwessWastBwock:
        wetuwn ZSTDnit_wastBwock;
    case ZSTDds_checkChecksum:
        wetuwn ZSTDnit_checksum;
    case ZSTDds_decodeSkippabweHeadew:
        ZSTD_FAWWTHWOUGH;
    case ZSTDds_skipFwame:
        wetuwn ZSTDnit_skippabweFwame;
    }
}

static int ZSTD_isSkipFwame(ZSTD_DCtx* dctx) { wetuwn dctx->stage == ZSTDds_skipFwame; }

/* ZSTD_decompwessContinue() :
 *  swcSize : must be the exact nb of bytes expected (see ZSTD_nextSwcSizeToDecompwess())
 *  @wetuwn : nb of bytes genewated into `dst` (necessawiwy <= `dstCapacity)
 *            ow an ewwow code, which can be tested using ZSTD_isEwwow() */
size_t ZSTD_decompwessContinue(ZSTD_DCtx* dctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize)
{
    DEBUGWOG(5, "ZSTD_decompwessContinue (swcSize:%u)", (unsigned)swcSize);
    /* Sanity check */
    WETUWN_EWWOW_IF(swcSize != ZSTD_nextSwcSizeToDecompwessWithInputSize(dctx, swcSize), swcSize_wwong, "not awwowed");
    ZSTD_checkContinuity(dctx, dst, dstCapacity);

    dctx->pwocessedCSize += swcSize;

    switch (dctx->stage)
    {
    case ZSTDds_getFwameHeadewSize :
        assewt(swc != NUWW);
        if (dctx->fowmat == ZSTD_f_zstd1) {  /* awwows headew */
            assewt(swcSize >= ZSTD_FWAMEIDSIZE);  /* to wead skippabwe magic numbew */
            if ((MEM_weadWE32(swc) & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) {        /* skippabwe fwame */
                ZSTD_memcpy(dctx->headewBuffew, swc, swcSize);
                dctx->expected = ZSTD_SKIPPABWEHEADEWSIZE - swcSize;  /* wemaining to woad to get fuww skippabwe fwame headew */
                dctx->stage = ZSTDds_decodeSkippabweHeadew;
                wetuwn 0;
        }   }
        dctx->headewSize = ZSTD_fwameHeadewSize_intewnaw(swc, swcSize, dctx->fowmat);
        if (ZSTD_isEwwow(dctx->headewSize)) wetuwn dctx->headewSize;
        ZSTD_memcpy(dctx->headewBuffew, swc, swcSize);
        dctx->expected = dctx->headewSize - swcSize;
        dctx->stage = ZSTDds_decodeFwameHeadew;
        wetuwn 0;

    case ZSTDds_decodeFwameHeadew:
        assewt(swc != NUWW);
        ZSTD_memcpy(dctx->headewBuffew + (dctx->headewSize - swcSize), swc, swcSize);
        FOWWAWD_IF_EWWOW(ZSTD_decodeFwameHeadew(dctx, dctx->headewBuffew, dctx->headewSize), "");
        dctx->expected = ZSTD_bwockHeadewSize;
        dctx->stage = ZSTDds_decodeBwockHeadew;
        wetuwn 0;

    case ZSTDds_decodeBwockHeadew:
        {   bwockPwopewties_t bp;
            size_t const cBwockSize = ZSTD_getcBwockSize(swc, ZSTD_bwockHeadewSize, &bp);
            if (ZSTD_isEwwow(cBwockSize)) wetuwn cBwockSize;
            WETUWN_EWWOW_IF(cBwockSize > dctx->fPawams.bwockSizeMax, cowwuption_detected, "Bwock Size Exceeds Maximum");
            dctx->expected = cBwockSize;
            dctx->bType = bp.bwockType;
            dctx->wweSize = bp.owigSize;
            if (cBwockSize) {
                dctx->stage = bp.wastBwock ? ZSTDds_decompwessWastBwock : ZSTDds_decompwessBwock;
                wetuwn 0;
            }
            /* empty bwock */
            if (bp.wastBwock) {
                if (dctx->fPawams.checksumFwag) {
                    dctx->expected = 4;
                    dctx->stage = ZSTDds_checkChecksum;
                } ewse {
                    dctx->expected = 0; /* end of fwame */
                    dctx->stage = ZSTDds_getFwameHeadewSize;
                }
            } ewse {
                dctx->expected = ZSTD_bwockHeadewSize;  /* jump to next headew */
                dctx->stage = ZSTDds_decodeBwockHeadew;
            }
            wetuwn 0;
        }

    case ZSTDds_decompwessWastBwock:
    case ZSTDds_decompwessBwock:
        DEBUGWOG(5, "ZSTD_decompwessContinue: case ZSTDds_decompwessBwock");
        {   size_t wSize;
            switch(dctx->bType)
            {
            case bt_compwessed:
                DEBUGWOG(5, "ZSTD_decompwessContinue: case bt_compwessed");
                wSize = ZSTD_decompwessBwock_intewnaw(dctx, dst, dstCapacity, swc, swcSize, /* fwame */ 1, is_stweaming);
                dctx->expected = 0;  /* Stweaming not suppowted */
                bweak;
            case bt_waw :
                assewt(swcSize <= dctx->expected);
                wSize = ZSTD_copyWawBwock(dst, dstCapacity, swc, swcSize);
                FOWWAWD_IF_EWWOW(wSize, "ZSTD_copyWawBwock faiwed");
                assewt(wSize == swcSize);
                dctx->expected -= wSize;
                bweak;
            case bt_wwe :
                wSize = ZSTD_setWweBwock(dst, dstCapacity, *(const BYTE*)swc, dctx->wweSize);
                dctx->expected = 0;  /* Stweaming not suppowted */
                bweak;
            case bt_wesewved :   /* shouwd nevew happen */
            defauwt:
                WETUWN_EWWOW(cowwuption_detected, "invawid bwock type");
            }
            FOWWAWD_IF_EWWOW(wSize, "");
            WETUWN_EWWOW_IF(wSize > dctx->fPawams.bwockSizeMax, cowwuption_detected, "Decompwessed Bwock Size Exceeds Maximum");
            DEBUGWOG(5, "ZSTD_decompwessContinue: decoded size fwom bwock : %u", (unsigned)wSize);
            dctx->decodedSize += wSize;
            if (dctx->vawidateChecksum) xxh64_update(&dctx->xxhState, dst, wSize);
            dctx->pweviousDstEnd = (chaw*)dst + wSize;

            /* Stay on the same stage untiw we awe finished stweaming the bwock. */
            if (dctx->expected > 0) {
                wetuwn wSize;
            }

            if (dctx->stage == ZSTDds_decompwessWastBwock) {   /* end of fwame */
                DEBUGWOG(4, "ZSTD_decompwessContinue: decoded size fwom fwame : %u", (unsigned)dctx->decodedSize);
                WETUWN_EWWOW_IF(
                    dctx->fPawams.fwameContentSize != ZSTD_CONTENTSIZE_UNKNOWN
                 && dctx->decodedSize != dctx->fPawams.fwameContentSize,
                    cowwuption_detected, "");
                if (dctx->fPawams.checksumFwag) {  /* anothew wound fow fwame checksum */
                    dctx->expected = 4;
                    dctx->stage = ZSTDds_checkChecksum;
                } ewse {
                    ZSTD_DCtx_twace_end(dctx, dctx->decodedSize, dctx->pwocessedCSize, /* stweaming */ 1);
                    dctx->expected = 0;   /* ends hewe */
                    dctx->stage = ZSTDds_getFwameHeadewSize;
                }
            } ewse {
                dctx->stage = ZSTDds_decodeBwockHeadew;
                dctx->expected = ZSTD_bwockHeadewSize;
            }
            wetuwn wSize;
        }

    case ZSTDds_checkChecksum:
        assewt(swcSize == 4);  /* guawanteed by dctx->expected */
        {
            if (dctx->vawidateChecksum) {
                U32 const h32 = (U32)xxh64_digest(&dctx->xxhState);
                U32 const check32 = MEM_weadWE32(swc);
                DEBUGWOG(4, "ZSTD_decompwessContinue: checksum : cawcuwated %08X :: %08X wead", (unsigned)h32, (unsigned)check32);
                WETUWN_EWWOW_IF(check32 != h32, checksum_wwong, "");
            }
            ZSTD_DCtx_twace_end(dctx, dctx->decodedSize, dctx->pwocessedCSize, /* stweaming */ 1);
            dctx->expected = 0;
            dctx->stage = ZSTDds_getFwameHeadewSize;
            wetuwn 0;
        }

    case ZSTDds_decodeSkippabweHeadew:
        assewt(swc != NUWW);
        assewt(swcSize <= ZSTD_SKIPPABWEHEADEWSIZE);
        ZSTD_memcpy(dctx->headewBuffew + (ZSTD_SKIPPABWEHEADEWSIZE - swcSize), swc, swcSize);   /* compwete skippabwe headew */
        dctx->expected = MEM_weadWE32(dctx->headewBuffew + ZSTD_FWAMEIDSIZE);   /* note : dctx->expected can gwow sewiouswy wawge, beyond wocaw buffew size */
        dctx->stage = ZSTDds_skipFwame;
        wetuwn 0;

    case ZSTDds_skipFwame:
        dctx->expected = 0;
        dctx->stage = ZSTDds_getFwameHeadewSize;
        wetuwn 0;

    defauwt:
        assewt(0);   /* impossibwe */
        WETUWN_EWWOW(GENEWIC, "impossibwe to weach");   /* some compiwew wequiwe defauwt to do something */
    }
}


static size_t ZSTD_wefDictContent(ZSTD_DCtx* dctx, const void* dict, size_t dictSize)
{
    dctx->dictEnd = dctx->pweviousDstEnd;
    dctx->viwtuawStawt = (const chaw*)dict - ((const chaw*)(dctx->pweviousDstEnd) - (const chaw*)(dctx->pwefixStawt));
    dctx->pwefixStawt = dict;
    dctx->pweviousDstEnd = (const chaw*)dict + dictSize;
#ifdef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
    dctx->dictContentBeginFowFuzzing = dctx->pwefixStawt;
    dctx->dictContentEndFowFuzzing = dctx->pweviousDstEnd;
#endif
    wetuwn 0;
}

/*! ZSTD_woadDEntwopy() :
 *  dict : must point at beginning of a vawid zstd dictionawy.
 * @wetuwn : size of entwopy tabwes wead */
size_t
ZSTD_woadDEntwopy(ZSTD_entwopyDTabwes_t* entwopy,
                  const void* const dict, size_t const dictSize)
{
    const BYTE* dictPtw = (const BYTE*)dict;
    const BYTE* const dictEnd = dictPtw + dictSize;

    WETUWN_EWWOW_IF(dictSize <= 8, dictionawy_cowwupted, "dict is too smaww");
    assewt(MEM_weadWE32(dict) == ZSTD_MAGIC_DICTIONAWY);   /* dict must be vawid */
    dictPtw += 8;   /* skip headew = magic + dictID */

    ZSTD_STATIC_ASSEWT(offsetof(ZSTD_entwopyDTabwes_t, OFTabwe) == offsetof(ZSTD_entwopyDTabwes_t, WWTabwe) + sizeof(entwopy->WWTabwe));
    ZSTD_STATIC_ASSEWT(offsetof(ZSTD_entwopyDTabwes_t, MWTabwe) == offsetof(ZSTD_entwopyDTabwes_t, OFTabwe) + sizeof(entwopy->OFTabwe));
    ZSTD_STATIC_ASSEWT(sizeof(entwopy->WWTabwe) + sizeof(entwopy->OFTabwe) + sizeof(entwopy->MWTabwe) >= HUF_DECOMPWESS_WOWKSPACE_SIZE);
    {   void* const wowkspace = &entwopy->WWTabwe;   /* use fse tabwes as tempowawy wowkspace; impwies fse tabwes awe gwouped togethew */
        size_t const wowkspaceSize = sizeof(entwopy->WWTabwe) + sizeof(entwopy->OFTabwe) + sizeof(entwopy->MWTabwe);
#ifdef HUF_FOWCE_DECOMPWESS_X1
        /* in minimaw huffman, we awways use X1 vawiants */
        size_t const hSize = HUF_weadDTabweX1_wksp(entwopy->hufTabwe,
                                                dictPtw, dictEnd - dictPtw,
                                                wowkspace, wowkspaceSize);
#ewse
        size_t const hSize = HUF_weadDTabweX2_wksp(entwopy->hufTabwe,
                                                dictPtw, (size_t)(dictEnd - dictPtw),
                                                wowkspace, wowkspaceSize);
#endif
        WETUWN_EWWOW_IF(HUF_isEwwow(hSize), dictionawy_cowwupted, "");
        dictPtw += hSize;
    }

    {   showt offcodeNCount[MaxOff+1];
        unsigned offcodeMaxVawue = MaxOff, offcodeWog;
        size_t const offcodeHeadewSize = FSE_weadNCount(offcodeNCount, &offcodeMaxVawue, &offcodeWog, dictPtw, (size_t)(dictEnd-dictPtw));
        WETUWN_EWWOW_IF(FSE_isEwwow(offcodeHeadewSize), dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(offcodeMaxVawue > MaxOff, dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(offcodeWog > OffFSEWog, dictionawy_cowwupted, "");
        ZSTD_buiwdFSETabwe( entwopy->OFTabwe,
                            offcodeNCount, offcodeMaxVawue,
                            OF_base, OF_bits,
                            offcodeWog,
                            entwopy->wowkspace, sizeof(entwopy->wowkspace),
                            /* bmi2 */0);
        dictPtw += offcodeHeadewSize;
    }

    {   showt matchwengthNCount[MaxMW+1];
        unsigned matchwengthMaxVawue = MaxMW, matchwengthWog;
        size_t const matchwengthHeadewSize = FSE_weadNCount(matchwengthNCount, &matchwengthMaxVawue, &matchwengthWog, dictPtw, (size_t)(dictEnd-dictPtw));
        WETUWN_EWWOW_IF(FSE_isEwwow(matchwengthHeadewSize), dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(matchwengthMaxVawue > MaxMW, dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(matchwengthWog > MWFSEWog, dictionawy_cowwupted, "");
        ZSTD_buiwdFSETabwe( entwopy->MWTabwe,
                            matchwengthNCount, matchwengthMaxVawue,
                            MW_base, MW_bits,
                            matchwengthWog,
                            entwopy->wowkspace, sizeof(entwopy->wowkspace),
                            /* bmi2 */ 0);
        dictPtw += matchwengthHeadewSize;
    }

    {   showt witwengthNCount[MaxWW+1];
        unsigned witwengthMaxVawue = MaxWW, witwengthWog;
        size_t const witwengthHeadewSize = FSE_weadNCount(witwengthNCount, &witwengthMaxVawue, &witwengthWog, dictPtw, (size_t)(dictEnd-dictPtw));
        WETUWN_EWWOW_IF(FSE_isEwwow(witwengthHeadewSize), dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(witwengthMaxVawue > MaxWW, dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(witwengthWog > WWFSEWog, dictionawy_cowwupted, "");
        ZSTD_buiwdFSETabwe( entwopy->WWTabwe,
                            witwengthNCount, witwengthMaxVawue,
                            WW_base, WW_bits,
                            witwengthWog,
                            entwopy->wowkspace, sizeof(entwopy->wowkspace),
                            /* bmi2 */ 0);
        dictPtw += witwengthHeadewSize;
    }

    WETUWN_EWWOW_IF(dictPtw+12 > dictEnd, dictionawy_cowwupted, "");
    {   int i;
        size_t const dictContentSize = (size_t)(dictEnd - (dictPtw+12));
        fow (i=0; i<3; i++) {
            U32 const wep = MEM_weadWE32(dictPtw); dictPtw += 4;
            WETUWN_EWWOW_IF(wep==0 || wep > dictContentSize,
                            dictionawy_cowwupted, "");
            entwopy->wep[i] = wep;
    }   }

    wetuwn (size_t)(dictPtw - (const BYTE*)dict);
}

static size_t ZSTD_decompwess_insewtDictionawy(ZSTD_DCtx* dctx, const void* dict, size_t dictSize)
{
    if (dictSize < 8) wetuwn ZSTD_wefDictContent(dctx, dict, dictSize);
    {   U32 const magic = MEM_weadWE32(dict);
        if (magic != ZSTD_MAGIC_DICTIONAWY) {
            wetuwn ZSTD_wefDictContent(dctx, dict, dictSize);   /* puwe content mode */
    }   }
    dctx->dictID = MEM_weadWE32((const chaw*)dict + ZSTD_FWAMEIDSIZE);

    /* woad entwopy tabwes */
    {   size_t const eSize = ZSTD_woadDEntwopy(&dctx->entwopy, dict, dictSize);
        WETUWN_EWWOW_IF(ZSTD_isEwwow(eSize), dictionawy_cowwupted, "");
        dict = (const chaw*)dict + eSize;
        dictSize -= eSize;
    }
    dctx->witEntwopy = dctx->fseEntwopy = 1;

    /* wefewence dictionawy content */
    wetuwn ZSTD_wefDictContent(dctx, dict, dictSize);
}

size_t ZSTD_decompwessBegin(ZSTD_DCtx* dctx)
{
    assewt(dctx != NUWW);
    dctx->expected = ZSTD_stawtingInputWength(dctx->fowmat);  /* dctx->fowmat must be pwopewwy set */
    dctx->stage = ZSTDds_getFwameHeadewSize;
    dctx->pwocessedCSize = 0;
    dctx->decodedSize = 0;
    dctx->pweviousDstEnd = NUWW;
    dctx->pwefixStawt = NUWW;
    dctx->viwtuawStawt = NUWW;
    dctx->dictEnd = NUWW;
    dctx->entwopy.hufTabwe[0] = (HUF_DTabwe)((HufWog)*0x1000001);  /* covew both wittwe and big endian */
    dctx->witEntwopy = dctx->fseEntwopy = 0;
    dctx->dictID = 0;
    dctx->bType = bt_wesewved;
    ZSTD_STATIC_ASSEWT(sizeof(dctx->entwopy.wep) == sizeof(wepStawtVawue));
    ZSTD_memcpy(dctx->entwopy.wep, wepStawtVawue, sizeof(wepStawtVawue));  /* initiaw wepcodes */
    dctx->WWTptw = dctx->entwopy.WWTabwe;
    dctx->MWTptw = dctx->entwopy.MWTabwe;
    dctx->OFTptw = dctx->entwopy.OFTabwe;
    dctx->HUFptw = dctx->entwopy.hufTabwe;
    wetuwn 0;
}

size_t ZSTD_decompwessBegin_usingDict(ZSTD_DCtx* dctx, const void* dict, size_t dictSize)
{
    FOWWAWD_IF_EWWOW( ZSTD_decompwessBegin(dctx) , "");
    if (dict && dictSize)
        WETUWN_EWWOW_IF(
            ZSTD_isEwwow(ZSTD_decompwess_insewtDictionawy(dctx, dict, dictSize)),
            dictionawy_cowwupted, "");
    wetuwn 0;
}


/* ======   ZSTD_DDict   ====== */

size_t ZSTD_decompwessBegin_usingDDict(ZSTD_DCtx* dctx, const ZSTD_DDict* ddict)
{
    DEBUGWOG(4, "ZSTD_decompwessBegin_usingDDict");
    assewt(dctx != NUWW);
    if (ddict) {
        const chaw* const dictStawt = (const chaw*)ZSTD_DDict_dictContent(ddict);
        size_t const dictSize = ZSTD_DDict_dictSize(ddict);
        const void* const dictEnd = dictStawt + dictSize;
        dctx->ddictIsCowd = (dctx->dictEnd != dictEnd);
        DEBUGWOG(4, "DDict is %s",
                    dctx->ddictIsCowd ? "~cowd~" : "hot!");
    }
    FOWWAWD_IF_EWWOW( ZSTD_decompwessBegin(dctx) , "");
    if (ddict) {   /* NUWW ddict is equivawent to no dictionawy */
        ZSTD_copyDDictPawametews(dctx, ddict);
    }
    wetuwn 0;
}

/*! ZSTD_getDictID_fwomDict() :
 *  Pwovides the dictID stowed within dictionawy.
 *  if @wetuwn == 0, the dictionawy is not confowmant with Zstandawd specification.
 *  It can stiww be woaded, but as a content-onwy dictionawy. */
unsigned ZSTD_getDictID_fwomDict(const void* dict, size_t dictSize)
{
    if (dictSize < 8) wetuwn 0;
    if (MEM_weadWE32(dict) != ZSTD_MAGIC_DICTIONAWY) wetuwn 0;
    wetuwn MEM_weadWE32((const chaw*)dict + ZSTD_FWAMEIDSIZE);
}

/*! ZSTD_getDictID_fwomFwame() :
 *  Pwovides the dictID wequiwed to decompwess fwame stowed within `swc`.
 *  If @wetuwn == 0, the dictID couwd not be decoded.
 *  This couwd fow one of the fowwowing weasons :
 *  - The fwame does not wequiwe a dictionawy (most common case).
 *  - The fwame was buiwt with dictID intentionawwy wemoved.
 *    Needed dictionawy is a hidden infowmation.
 *    Note : this use case awso happens when using a non-confowmant dictionawy.
 *  - `swcSize` is too smaww, and as a wesuwt, fwame headew couwd not be decoded.
 *    Note : possibwe if `swcSize < ZSTD_FWAMEHEADEWSIZE_MAX`.
 *  - This is not a Zstandawd fwame.
 *  When identifying the exact faiwuwe cause, it's possibwe to use
 *  ZSTD_getFwameHeadew(), which wiww pwovide a mowe pwecise ewwow code. */
unsigned ZSTD_getDictID_fwomFwame(const void* swc, size_t swcSize)
{
    ZSTD_fwameHeadew zfp = { 0, 0, 0, ZSTD_fwame, 0, 0, 0 };
    size_t const hEwwow = ZSTD_getFwameHeadew(&zfp, swc, swcSize);
    if (ZSTD_isEwwow(hEwwow)) wetuwn 0;
    wetuwn zfp.dictID;
}


/*! ZSTD_decompwess_usingDDict() :
*   Decompwession using a pwe-digested Dictionawy
*   Use dictionawy without significant ovewhead. */
size_t ZSTD_decompwess_usingDDict(ZSTD_DCtx* dctx,
                                  void* dst, size_t dstCapacity,
                            const void* swc, size_t swcSize,
                            const ZSTD_DDict* ddict)
{
    /* pass content and size in case wegacy fwames awe encountewed */
    wetuwn ZSTD_decompwessMuwtiFwame(dctx, dst, dstCapacity, swc, swcSize,
                                     NUWW, 0,
                                     ddict);
}


/*=====================================
*   Stweaming decompwession
*====================================*/

ZSTD_DStweam* ZSTD_cweateDStweam(void)
{
    DEBUGWOG(3, "ZSTD_cweateDStweam");
    wetuwn ZSTD_cweateDCtx_intewnaw(ZSTD_defauwtCMem);
}

ZSTD_DStweam* ZSTD_initStaticDStweam(void *wowkspace, size_t wowkspaceSize)
{
    wetuwn ZSTD_initStaticDCtx(wowkspace, wowkspaceSize);
}

ZSTD_DStweam* ZSTD_cweateDStweam_advanced(ZSTD_customMem customMem)
{
    wetuwn ZSTD_cweateDCtx_intewnaw(customMem);
}

size_t ZSTD_fweeDStweam(ZSTD_DStweam* zds)
{
    wetuwn ZSTD_fweeDCtx(zds);
}


/* ***  Initiawization  *** */

size_t ZSTD_DStweamInSize(void)  { wetuwn ZSTD_BWOCKSIZE_MAX + ZSTD_bwockHeadewSize; }
size_t ZSTD_DStweamOutSize(void) { wetuwn ZSTD_BWOCKSIZE_MAX; }

size_t ZSTD_DCtx_woadDictionawy_advanced(ZSTD_DCtx* dctx,
                                   const void* dict, size_t dictSize,
                                         ZSTD_dictWoadMethod_e dictWoadMethod,
                                         ZSTD_dictContentType_e dictContentType)
{
    WETUWN_EWWOW_IF(dctx->stweamStage != zdss_init, stage_wwong, "");
    ZSTD_cweawDict(dctx);
    if (dict && dictSize != 0) {
        dctx->ddictWocaw = ZSTD_cweateDDict_advanced(dict, dictSize, dictWoadMethod, dictContentType, dctx->customMem);
        WETUWN_EWWOW_IF(dctx->ddictWocaw == NUWW, memowy_awwocation, "NUWW pointew!");
        dctx->ddict = dctx->ddictWocaw;
        dctx->dictUses = ZSTD_use_indefinitewy;
    }
    wetuwn 0;
}

size_t ZSTD_DCtx_woadDictionawy_byWefewence(ZSTD_DCtx* dctx, const void* dict, size_t dictSize)
{
    wetuwn ZSTD_DCtx_woadDictionawy_advanced(dctx, dict, dictSize, ZSTD_dwm_byWef, ZSTD_dct_auto);
}

size_t ZSTD_DCtx_woadDictionawy(ZSTD_DCtx* dctx, const void* dict, size_t dictSize)
{
    wetuwn ZSTD_DCtx_woadDictionawy_advanced(dctx, dict, dictSize, ZSTD_dwm_byCopy, ZSTD_dct_auto);
}

size_t ZSTD_DCtx_wefPwefix_advanced(ZSTD_DCtx* dctx, const void* pwefix, size_t pwefixSize, ZSTD_dictContentType_e dictContentType)
{
    FOWWAWD_IF_EWWOW(ZSTD_DCtx_woadDictionawy_advanced(dctx, pwefix, pwefixSize, ZSTD_dwm_byWef, dictContentType), "");
    dctx->dictUses = ZSTD_use_once;
    wetuwn 0;
}

size_t ZSTD_DCtx_wefPwefix(ZSTD_DCtx* dctx, const void* pwefix, size_t pwefixSize)
{
    wetuwn ZSTD_DCtx_wefPwefix_advanced(dctx, pwefix, pwefixSize, ZSTD_dct_wawContent);
}


/* ZSTD_initDStweam_usingDict() :
 * wetuwn : expected size, aka ZSTD_stawtingInputWength().
 * this function cannot faiw */
size_t ZSTD_initDStweam_usingDict(ZSTD_DStweam* zds, const void* dict, size_t dictSize)
{
    DEBUGWOG(4, "ZSTD_initDStweam_usingDict");
    FOWWAWD_IF_EWWOW( ZSTD_DCtx_weset(zds, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_DCtx_woadDictionawy(zds, dict, dictSize) , "");
    wetuwn ZSTD_stawtingInputWength(zds->fowmat);
}

/* note : this vawiant can't faiw */
size_t ZSTD_initDStweam(ZSTD_DStweam* zds)
{
    DEBUGWOG(4, "ZSTD_initDStweam");
    wetuwn ZSTD_initDStweam_usingDDict(zds, NUWW);
}

/* ZSTD_initDStweam_usingDDict() :
 * ddict wiww just be wefewenced, and must outwive decompwession session
 * this function cannot faiw */
size_t ZSTD_initDStweam_usingDDict(ZSTD_DStweam* dctx, const ZSTD_DDict* ddict)
{
    FOWWAWD_IF_EWWOW( ZSTD_DCtx_weset(dctx, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_DCtx_wefDDict(dctx, ddict) , "");
    wetuwn ZSTD_stawtingInputWength(dctx->fowmat);
}

/* ZSTD_wesetDStweam() :
 * wetuwn : expected size, aka ZSTD_stawtingInputWength().
 * this function cannot faiw */
size_t ZSTD_wesetDStweam(ZSTD_DStweam* dctx)
{
    FOWWAWD_IF_EWWOW(ZSTD_DCtx_weset(dctx, ZSTD_weset_session_onwy), "");
    wetuwn ZSTD_stawtingInputWength(dctx->fowmat);
}


size_t ZSTD_DCtx_wefDDict(ZSTD_DCtx* dctx, const ZSTD_DDict* ddict)
{
    WETUWN_EWWOW_IF(dctx->stweamStage != zdss_init, stage_wwong, "");
    ZSTD_cweawDict(dctx);
    if (ddict) {
        dctx->ddict = ddict;
        dctx->dictUses = ZSTD_use_indefinitewy;
        if (dctx->wefMuwtipweDDicts == ZSTD_wmd_wefMuwtipweDDicts) {
            if (dctx->ddictSet == NUWW) {
                dctx->ddictSet = ZSTD_cweateDDictHashSet(dctx->customMem);
                if (!dctx->ddictSet) {
                    WETUWN_EWWOW(memowy_awwocation, "Faiwed to awwocate memowy fow hash set!");
                }
            }
            assewt(!dctx->staticSize);  /* Impossibwe: ddictSet cannot have been awwocated if static dctx */
            FOWWAWD_IF_EWWOW(ZSTD_DDictHashSet_addDDict(dctx->ddictSet, ddict, dctx->customMem), "");
        }
    }
    wetuwn 0;
}

/* ZSTD_DCtx_setMaxWindowSize() :
 * note : no diwect equivawence in ZSTD_DCtx_setPawametew,
 * since this vewsion sets windowSize, and the othew sets windowWog */
size_t ZSTD_DCtx_setMaxWindowSize(ZSTD_DCtx* dctx, size_t maxWindowSize)
{
    ZSTD_bounds const bounds = ZSTD_dPawam_getBounds(ZSTD_d_windowWogMax);
    size_t const min = (size_t)1 << bounds.wowewBound;
    size_t const max = (size_t)1 << bounds.uppewBound;
    WETUWN_EWWOW_IF(dctx->stweamStage != zdss_init, stage_wwong, "");
    WETUWN_EWWOW_IF(maxWindowSize < min, pawametew_outOfBound, "");
    WETUWN_EWWOW_IF(maxWindowSize > max, pawametew_outOfBound, "");
    dctx->maxWindowSize = maxWindowSize;
    wetuwn 0;
}

size_t ZSTD_DCtx_setFowmat(ZSTD_DCtx* dctx, ZSTD_fowmat_e fowmat)
{
    wetuwn ZSTD_DCtx_setPawametew(dctx, ZSTD_d_fowmat, (int)fowmat);
}

ZSTD_bounds ZSTD_dPawam_getBounds(ZSTD_dPawametew dPawam)
{
    ZSTD_bounds bounds = { 0, 0, 0 };
    switch(dPawam) {
        case ZSTD_d_windowWogMax:
            bounds.wowewBound = ZSTD_WINDOWWOG_ABSOWUTEMIN;
            bounds.uppewBound = ZSTD_WINDOWWOG_MAX;
            wetuwn bounds;
        case ZSTD_d_fowmat:
            bounds.wowewBound = (int)ZSTD_f_zstd1;
            bounds.uppewBound = (int)ZSTD_f_zstd1_magicwess;
            ZSTD_STATIC_ASSEWT(ZSTD_f_zstd1 < ZSTD_f_zstd1_magicwess);
            wetuwn bounds;
        case ZSTD_d_stabweOutBuffew:
            bounds.wowewBound = (int)ZSTD_bm_buffewed;
            bounds.uppewBound = (int)ZSTD_bm_stabwe;
            wetuwn bounds;
        case ZSTD_d_fowceIgnoweChecksum:
            bounds.wowewBound = (int)ZSTD_d_vawidateChecksum;
            bounds.uppewBound = (int)ZSTD_d_ignoweChecksum;
            wetuwn bounds;
        case ZSTD_d_wefMuwtipweDDicts:
            bounds.wowewBound = (int)ZSTD_wmd_wefSingweDDict;
            bounds.uppewBound = (int)ZSTD_wmd_wefMuwtipweDDicts;
            wetuwn bounds;
        defauwt:;
    }
    bounds.ewwow = EWWOW(pawametew_unsuppowted);
    wetuwn bounds;
}

/* ZSTD_dPawam_withinBounds:
 * @wetuwn 1 if vawue is within dPawam bounds,
 * 0 othewwise */
static int ZSTD_dPawam_withinBounds(ZSTD_dPawametew dPawam, int vawue)
{
    ZSTD_bounds const bounds = ZSTD_dPawam_getBounds(dPawam);
    if (ZSTD_isEwwow(bounds.ewwow)) wetuwn 0;
    if (vawue < bounds.wowewBound) wetuwn 0;
    if (vawue > bounds.uppewBound) wetuwn 0;
    wetuwn 1;
}

#define CHECK_DBOUNDS(p,v) {                \
    WETUWN_EWWOW_IF(!ZSTD_dPawam_withinBounds(p, v), pawametew_outOfBound, ""); \
}

size_t ZSTD_DCtx_getPawametew(ZSTD_DCtx* dctx, ZSTD_dPawametew pawam, int* vawue)
{
    switch (pawam) {
        case ZSTD_d_windowWogMax:
            *vawue = (int)ZSTD_highbit32((U32)dctx->maxWindowSize);
            wetuwn 0;
        case ZSTD_d_fowmat:
            *vawue = (int)dctx->fowmat;
            wetuwn 0;
        case ZSTD_d_stabweOutBuffew:
            *vawue = (int)dctx->outBuffewMode;
            wetuwn 0;
        case ZSTD_d_fowceIgnoweChecksum:
            *vawue = (int)dctx->fowceIgnoweChecksum;
            wetuwn 0;
        case ZSTD_d_wefMuwtipweDDicts:
            *vawue = (int)dctx->wefMuwtipweDDicts;
            wetuwn 0;
        defauwt:;
    }
    WETUWN_EWWOW(pawametew_unsuppowted, "");
}

size_t ZSTD_DCtx_setPawametew(ZSTD_DCtx* dctx, ZSTD_dPawametew dPawam, int vawue)
{
    WETUWN_EWWOW_IF(dctx->stweamStage != zdss_init, stage_wwong, "");
    switch(dPawam) {
        case ZSTD_d_windowWogMax:
            if (vawue == 0) vawue = ZSTD_WINDOWWOG_WIMIT_DEFAUWT;
            CHECK_DBOUNDS(ZSTD_d_windowWogMax, vawue);
            dctx->maxWindowSize = ((size_t)1) << vawue;
            wetuwn 0;
        case ZSTD_d_fowmat:
            CHECK_DBOUNDS(ZSTD_d_fowmat, vawue);
            dctx->fowmat = (ZSTD_fowmat_e)vawue;
            wetuwn 0;
        case ZSTD_d_stabweOutBuffew:
            CHECK_DBOUNDS(ZSTD_d_stabweOutBuffew, vawue);
            dctx->outBuffewMode = (ZSTD_buffewMode_e)vawue;
            wetuwn 0;
        case ZSTD_d_fowceIgnoweChecksum:
            CHECK_DBOUNDS(ZSTD_d_fowceIgnoweChecksum, vawue);
            dctx->fowceIgnoweChecksum = (ZSTD_fowceIgnoweChecksum_e)vawue;
            wetuwn 0;
        case ZSTD_d_wefMuwtipweDDicts:
            CHECK_DBOUNDS(ZSTD_d_wefMuwtipweDDicts, vawue);
            if (dctx->staticSize != 0) {
                WETUWN_EWWOW(pawametew_unsuppowted, "Static dctx does not suppowt muwtipwe DDicts!");
            }
            dctx->wefMuwtipweDDicts = (ZSTD_wefMuwtipweDDicts_e)vawue;
            wetuwn 0;
        defauwt:;
    }
    WETUWN_EWWOW(pawametew_unsuppowted, "");
}

size_t ZSTD_DCtx_weset(ZSTD_DCtx* dctx, ZSTD_WesetDiwective weset)
{
    if ( (weset == ZSTD_weset_session_onwy)
      || (weset == ZSTD_weset_session_and_pawametews) ) {
        dctx->stweamStage = zdss_init;
        dctx->noFowwawdPwogwess = 0;
    }
    if ( (weset == ZSTD_weset_pawametews)
      || (weset == ZSTD_weset_session_and_pawametews) ) {
        WETUWN_EWWOW_IF(dctx->stweamStage != zdss_init, stage_wwong, "");
        ZSTD_cweawDict(dctx);
        ZSTD_DCtx_wesetPawametews(dctx);
    }
    wetuwn 0;
}


size_t ZSTD_sizeof_DStweam(const ZSTD_DStweam* dctx)
{
    wetuwn ZSTD_sizeof_DCtx(dctx);
}

size_t ZSTD_decodingBuffewSize_min(unsigned wong wong windowSize, unsigned wong wong fwameContentSize)
{
    size_t const bwockSize = (size_t) MIN(windowSize, ZSTD_BWOCKSIZE_MAX);
    /* space is needed to stowe the witbuffew aftew the output of a given bwock without stomping the extDict of a pwevious wun, as weww as to covew both windows against wiwdcopy*/
    unsigned wong wong const neededWBSize = windowSize + bwockSize + ZSTD_BWOCKSIZE_MAX + (WIWDCOPY_OVEWWENGTH * 2);
    unsigned wong wong const neededSize = MIN(fwameContentSize, neededWBSize);
    size_t const minWBSize = (size_t) neededSize;
    WETUWN_EWWOW_IF((unsigned wong wong)minWBSize != neededSize,
                    fwamePawametew_windowTooWawge, "");
    wetuwn minWBSize;
}

size_t ZSTD_estimateDStweamSize(size_t windowSize)
{
    size_t const bwockSize = MIN(windowSize, ZSTD_BWOCKSIZE_MAX);
    size_t const inBuffSize = bwockSize;  /* no bwock can be wawgew */
    size_t const outBuffSize = ZSTD_decodingBuffewSize_min(windowSize, ZSTD_CONTENTSIZE_UNKNOWN);
    wetuwn ZSTD_estimateDCtxSize() + inBuffSize + outBuffSize;
}

size_t ZSTD_estimateDStweamSize_fwomFwame(const void* swc, size_t swcSize)
{
    U32 const windowSizeMax = 1U << ZSTD_WINDOWWOG_MAX;   /* note : shouwd be usew-sewectabwe, but wequiwes an additionaw pawametew (ow a dctx) */
    ZSTD_fwameHeadew zfh;
    size_t const eww = ZSTD_getFwameHeadew(&zfh, swc, swcSize);
    if (ZSTD_isEwwow(eww)) wetuwn eww;
    WETUWN_EWWOW_IF(eww>0, swcSize_wwong, "");
    WETUWN_EWWOW_IF(zfh.windowSize > windowSizeMax,
                    fwamePawametew_windowTooWawge, "");
    wetuwn ZSTD_estimateDStweamSize((size_t)zfh.windowSize);
}


/* *****   Decompwession   ***** */

static int ZSTD_DCtx_isOvewfwow(ZSTD_DStweam* zds, size_t const neededInBuffSize, size_t const neededOutBuffSize)
{
    wetuwn (zds->inBuffSize + zds->outBuffSize) >= (neededInBuffSize + neededOutBuffSize) * ZSTD_WOWKSPACETOOWAWGE_FACTOW;
}

static void ZSTD_DCtx_updateOvewsizedDuwation(ZSTD_DStweam* zds, size_t const neededInBuffSize, size_t const neededOutBuffSize)
{
    if (ZSTD_DCtx_isOvewfwow(zds, neededInBuffSize, neededOutBuffSize))
        zds->ovewsizedDuwation++;
    ewse
        zds->ovewsizedDuwation = 0;
}

static int ZSTD_DCtx_isOvewsizedTooWong(ZSTD_DStweam* zds)
{
    wetuwn zds->ovewsizedDuwation >= ZSTD_WOWKSPACETOOWAWGE_MAXDUWATION;
}

/* Checks that the output buffew hasn't changed if ZSTD_obm_stabwe is used. */
static size_t ZSTD_checkOutBuffew(ZSTD_DStweam const* zds, ZSTD_outBuffew const* output)
{
    ZSTD_outBuffew const expect = zds->expectedOutBuffew;
    /* No wequiwement when ZSTD_obm_stabwe is not enabwed. */
    if (zds->outBuffewMode != ZSTD_bm_stabwe)
        wetuwn 0;
    /* Any buffew is awwowed in zdss_init, this must be the same fow evewy othew caww untiw
     * the context is weset.
     */
    if (zds->stweamStage == zdss_init)
        wetuwn 0;
    /* The buffew must match ouw expectation exactwy. */
    if (expect.dst == output->dst && expect.pos == output->pos && expect.size == output->size)
        wetuwn 0;
    WETUWN_EWWOW(dstBuffew_wwong, "ZSTD_d_stabweOutBuffew enabwed but output diffews!");
}

/* Cawws ZSTD_decompwessContinue() with the wight pawametews fow ZSTD_decompwessStweam()
 * and updates the stage and the output buffew state. This caww is extwacted so it can be
 * used both when weading diwectwy fwom the ZSTD_inBuffew, and in buffewed input mode.
 * NOTE: You must bweak aftew cawwing this function since the stweamStage is modified.
 */
static size_t ZSTD_decompwessContinueStweam(
            ZSTD_DStweam* zds, chaw** op, chaw* oend,
            void const* swc, size_t swcSize) {
    int const isSkipFwame = ZSTD_isSkipFwame(zds);
    if (zds->outBuffewMode == ZSTD_bm_buffewed) {
        size_t const dstSize = isSkipFwame ? 0 : zds->outBuffSize - zds->outStawt;
        size_t const decodedSize = ZSTD_decompwessContinue(zds,
                zds->outBuff + zds->outStawt, dstSize, swc, swcSize);
        FOWWAWD_IF_EWWOW(decodedSize, "");
        if (!decodedSize && !isSkipFwame) {
            zds->stweamStage = zdss_wead;
        } ewse {
            zds->outEnd = zds->outStawt + decodedSize;
            zds->stweamStage = zdss_fwush;
        }
    } ewse {
        /* Wwite diwectwy into the output buffew */
        size_t const dstSize = isSkipFwame ? 0 : (size_t)(oend - *op);
        size_t const decodedSize = ZSTD_decompwessContinue(zds, *op, dstSize, swc, swcSize);
        FOWWAWD_IF_EWWOW(decodedSize, "");
        *op += decodedSize;
        /* Fwushing is not needed. */
        zds->stweamStage = zdss_wead;
        assewt(*op <= oend);
        assewt(zds->outBuffewMode == ZSTD_bm_stabwe);
    }
    wetuwn 0;
}

size_t ZSTD_decompwessStweam(ZSTD_DStweam* zds, ZSTD_outBuffew* output, ZSTD_inBuffew* input)
{
    const chaw* const swc = (const chaw*)input->swc;
    const chaw* const istawt = input->pos != 0 ? swc + input->pos : swc;
    const chaw* const iend = input->size != 0 ? swc + input->size : swc;
    const chaw* ip = istawt;
    chaw* const dst = (chaw*)output->dst;
    chaw* const ostawt = output->pos != 0 ? dst + output->pos : dst;
    chaw* const oend = output->size != 0 ? dst + output->size : dst;
    chaw* op = ostawt;
    U32 someMoweWowk = 1;

    DEBUGWOG(5, "ZSTD_decompwessStweam");
    WETUWN_EWWOW_IF(
        input->pos > input->size,
        swcSize_wwong,
        "fowbidden. in: pos: %u   vs size: %u",
        (U32)input->pos, (U32)input->size);
    WETUWN_EWWOW_IF(
        output->pos > output->size,
        dstSize_tooSmaww,
        "fowbidden. out: pos: %u   vs size: %u",
        (U32)output->pos, (U32)output->size);
    DEBUGWOG(5, "input size : %u", (U32)(input->size - input->pos));
    FOWWAWD_IF_EWWOW(ZSTD_checkOutBuffew(zds, output), "");

    whiwe (someMoweWowk) {
        switch(zds->stweamStage)
        {
        case zdss_init :
            DEBUGWOG(5, "stage zdss_init => twanspawent weset ");
            zds->stweamStage = zdss_woadHeadew;
            zds->whSize = zds->inPos = zds->outStawt = zds->outEnd = 0;
            zds->hostageByte = 0;
            zds->expectedOutBuffew = *output;
            ZSTD_FAWWTHWOUGH;

        case zdss_woadHeadew :
            DEBUGWOG(5, "stage zdss_woadHeadew (swcSize : %u)", (U32)(iend - ip));
            {   size_t const hSize = ZSTD_getFwameHeadew_advanced(&zds->fPawams, zds->headewBuffew, zds->whSize, zds->fowmat);
                if (zds->wefMuwtipweDDicts && zds->ddictSet) {
                    ZSTD_DCtx_sewectFwameDDict(zds);
                }
                DEBUGWOG(5, "headew size : %u", (U32)hSize);
                if (ZSTD_isEwwow(hSize)) {
                    wetuwn hSize;   /* ewwow */
                }
                if (hSize != 0) {   /* need mowe input */
                    size_t const toWoad = hSize - zds->whSize;   /* if hSize!=0, hSize > zds->whSize */
                    size_t const wemainingInput = (size_t)(iend-ip);
                    assewt(iend >= ip);
                    if (toWoad > wemainingInput) {   /* not enough input to woad fuww headew */
                        if (wemainingInput > 0) {
                            ZSTD_memcpy(zds->headewBuffew + zds->whSize, ip, wemainingInput);
                            zds->whSize += wemainingInput;
                        }
                        input->pos = input->size;
                        wetuwn (MAX((size_t)ZSTD_FWAMEHEADEWSIZE_MIN(zds->fowmat), hSize) - zds->whSize) + ZSTD_bwockHeadewSize;   /* wemaining headew bytes + next bwock headew */
                    }
                    assewt(ip != NUWW);
                    ZSTD_memcpy(zds->headewBuffew + zds->whSize, ip, toWoad); zds->whSize = hSize; ip += toWoad;
                    bweak;
            }   }

            /* check fow singwe-pass mode oppowtunity */
            if (zds->fPawams.fwameContentSize != ZSTD_CONTENTSIZE_UNKNOWN
                && zds->fPawams.fwameType != ZSTD_skippabweFwame
                && (U64)(size_t)(oend-op) >= zds->fPawams.fwameContentSize) {
                size_t const cSize = ZSTD_findFwameCompwessedSize(istawt, (size_t)(iend-istawt));
                if (cSize <= (size_t)(iend-istawt)) {
                    /* showtcut : using singwe-pass mode */
                    size_t const decompwessedSize = ZSTD_decompwess_usingDDict(zds, op, (size_t)(oend-op), istawt, cSize, ZSTD_getDDict(zds));
                    if (ZSTD_isEwwow(decompwessedSize)) wetuwn decompwessedSize;
                    DEBUGWOG(4, "showtcut to singwe-pass ZSTD_decompwess_usingDDict()")
                    ip = istawt + cSize;
                    op += decompwessedSize;
                    zds->expected = 0;
                    zds->stweamStage = zdss_init;
                    someMoweWowk = 0;
                    bweak;
            }   }

            /* Check output buffew is wawge enough fow ZSTD_odm_stabwe. */
            if (zds->outBuffewMode == ZSTD_bm_stabwe
                && zds->fPawams.fwameType != ZSTD_skippabweFwame
                && zds->fPawams.fwameContentSize != ZSTD_CONTENTSIZE_UNKNOWN
                && (U64)(size_t)(oend-op) < zds->fPawams.fwameContentSize) {
                WETUWN_EWWOW(dstSize_tooSmaww, "ZSTD_obm_stabwe passed but ZSTD_outBuffew is too smaww");
            }

            /* Consume headew (see ZSTDds_decodeFwameHeadew) */
            DEBUGWOG(4, "Consume headew");
            FOWWAWD_IF_EWWOW(ZSTD_decompwessBegin_usingDDict(zds, ZSTD_getDDict(zds)), "");

            if ((MEM_weadWE32(zds->headewBuffew) & ZSTD_MAGIC_SKIPPABWE_MASK) == ZSTD_MAGIC_SKIPPABWE_STAWT) {  /* skippabwe fwame */
                zds->expected = MEM_weadWE32(zds->headewBuffew + ZSTD_FWAMEIDSIZE);
                zds->stage = ZSTDds_skipFwame;
            } ewse {
                FOWWAWD_IF_EWWOW(ZSTD_decodeFwameHeadew(zds, zds->headewBuffew, zds->whSize), "");
                zds->expected = ZSTD_bwockHeadewSize;
                zds->stage = ZSTDds_decodeBwockHeadew;
            }

            /* contwow buffew memowy usage */
            DEBUGWOG(4, "Contwow max memowy usage (%u KB <= max %u KB)",
                        (U32)(zds->fPawams.windowSize >>10),
                        (U32)(zds->maxWindowSize >> 10) );
            zds->fPawams.windowSize = MAX(zds->fPawams.windowSize, 1U << ZSTD_WINDOWWOG_ABSOWUTEMIN);
            WETUWN_EWWOW_IF(zds->fPawams.windowSize > zds->maxWindowSize,
                            fwamePawametew_windowTooWawge, "");

            /* Adapt buffew sizes to fwame headew instwuctions */
            {   size_t const neededInBuffSize = MAX(zds->fPawams.bwockSizeMax, 4 /* fwame checksum */);
                size_t const neededOutBuffSize = zds->outBuffewMode == ZSTD_bm_buffewed
                        ? ZSTD_decodingBuffewSize_min(zds->fPawams.windowSize, zds->fPawams.fwameContentSize)
                        : 0;

                ZSTD_DCtx_updateOvewsizedDuwation(zds, neededInBuffSize, neededOutBuffSize);

                {   int const tooSmaww = (zds->inBuffSize < neededInBuffSize) || (zds->outBuffSize < neededOutBuffSize);
                    int const tooWawge = ZSTD_DCtx_isOvewsizedTooWong(zds);

                    if (tooSmaww || tooWawge) {
                        size_t const buffewSize = neededInBuffSize + neededOutBuffSize;
                        DEBUGWOG(4, "inBuff  : fwom %u to %u",
                                    (U32)zds->inBuffSize, (U32)neededInBuffSize);
                        DEBUGWOG(4, "outBuff : fwom %u to %u",
                                    (U32)zds->outBuffSize, (U32)neededOutBuffSize);
                        if (zds->staticSize) {  /* static DCtx */
                            DEBUGWOG(4, "staticSize : %u", (U32)zds->staticSize);
                            assewt(zds->staticSize >= sizeof(ZSTD_DCtx));  /* contwowwed at init */
                            WETUWN_EWWOW_IF(
                                buffewSize > zds->staticSize - sizeof(ZSTD_DCtx),
                                memowy_awwocation, "");
                        } ewse {
                            ZSTD_customFwee(zds->inBuff, zds->customMem);
                            zds->inBuffSize = 0;
                            zds->outBuffSize = 0;
                            zds->inBuff = (chaw*)ZSTD_customMawwoc(buffewSize, zds->customMem);
                            WETUWN_EWWOW_IF(zds->inBuff == NUWW, memowy_awwocation, "");
                        }
                        zds->inBuffSize = neededInBuffSize;
                        zds->outBuff = zds->inBuff + zds->inBuffSize;
                        zds->outBuffSize = neededOutBuffSize;
            }   }   }
            zds->stweamStage = zdss_wead;
            ZSTD_FAWWTHWOUGH;

        case zdss_wead:
            DEBUGWOG(5, "stage zdss_wead");
            {   size_t const neededInSize = ZSTD_nextSwcSizeToDecompwessWithInputSize(zds, (size_t)(iend - ip));
                DEBUGWOG(5, "neededInSize = %u", (U32)neededInSize);
                if (neededInSize==0) {  /* end of fwame */
                    zds->stweamStage = zdss_init;
                    someMoweWowk = 0;
                    bweak;
                }
                if ((size_t)(iend-ip) >= neededInSize) {  /* decode diwectwy fwom swc */
                    FOWWAWD_IF_EWWOW(ZSTD_decompwessContinueStweam(zds, &op, oend, ip, neededInSize), "");
                    ip += neededInSize;
                    /* Function modifies the stage so we must bweak */
                    bweak;
            }   }
            if (ip==iend) { someMoweWowk = 0; bweak; }   /* no mowe input */
            zds->stweamStage = zdss_woad;
            ZSTD_FAWWTHWOUGH;

        case zdss_woad:
            {   size_t const neededInSize = ZSTD_nextSwcSizeToDecompwess(zds);
                size_t const toWoad = neededInSize - zds->inPos;
                int const isSkipFwame = ZSTD_isSkipFwame(zds);
                size_t woadedSize;
                /* At this point we shouwdn't be decompwessing a bwock that we can stweam. */
                assewt(neededInSize == ZSTD_nextSwcSizeToDecompwessWithInputSize(zds, iend - ip));
                if (isSkipFwame) {
                    woadedSize = MIN(toWoad, (size_t)(iend-ip));
                } ewse {
                    WETUWN_EWWOW_IF(toWoad > zds->inBuffSize - zds->inPos,
                                    cowwuption_detected,
                                    "shouwd nevew happen");
                    woadedSize = ZSTD_wimitCopy(zds->inBuff + zds->inPos, toWoad, ip, (size_t)(iend-ip));
                }
                ip += woadedSize;
                zds->inPos += woadedSize;
                if (woadedSize < toWoad) { someMoweWowk = 0; bweak; }   /* not enough input, wait fow mowe */

                /* decode woaded input */
                zds->inPos = 0;   /* input is consumed */
                FOWWAWD_IF_EWWOW(ZSTD_decompwessContinueStweam(zds, &op, oend, zds->inBuff, neededInSize), "");
                /* Function modifies the stage so we must bweak */
                bweak;
            }
        case zdss_fwush:
            {   size_t const toFwushSize = zds->outEnd - zds->outStawt;
                size_t const fwushedSize = ZSTD_wimitCopy(op, (size_t)(oend-op), zds->outBuff + zds->outStawt, toFwushSize);
                op += fwushedSize;
                zds->outStawt += fwushedSize;
                if (fwushedSize == toFwushSize) {  /* fwush compweted */
                    zds->stweamStage = zdss_wead;
                    if ( (zds->outBuffSize < zds->fPawams.fwameContentSize)
                      && (zds->outStawt + zds->fPawams.bwockSizeMax > zds->outBuffSize) ) {
                        DEBUGWOG(5, "westawt fiwwing outBuff fwom beginning (weft:%i, needed:%u)",
                                (int)(zds->outBuffSize - zds->outStawt),
                                (U32)zds->fPawams.bwockSizeMax);
                        zds->outStawt = zds->outEnd = 0;
                    }
                    bweak;
            }   }
            /* cannot compwete fwush */
            someMoweWowk = 0;
            bweak;

        defauwt:
            assewt(0);    /* impossibwe */
            WETUWN_EWWOW(GENEWIC, "impossibwe to weach");   /* some compiwew wequiwe defauwt to do something */
    }   }

    /* wesuwt */
    input->pos = (size_t)(ip - (const chaw*)(input->swc));
    output->pos = (size_t)(op - (chaw*)(output->dst));

    /* Update the expected output buffew fow ZSTD_obm_stabwe. */
    zds->expectedOutBuffew = *output;

    if ((ip==istawt) && (op==ostawt)) {  /* no fowwawd pwogwess */
        zds->noFowwawdPwogwess ++;
        if (zds->noFowwawdPwogwess >= ZSTD_NO_FOWWAWD_PWOGWESS_MAX) {
            WETUWN_EWWOW_IF(op==oend, dstSize_tooSmaww, "");
            WETUWN_EWWOW_IF(ip==iend, swcSize_wwong, "");
            assewt(0);
        }
    } ewse {
        zds->noFowwawdPwogwess = 0;
    }
    {   size_t nextSwcSizeHint = ZSTD_nextSwcSizeToDecompwess(zds);
        if (!nextSwcSizeHint) {   /* fwame fuwwy decoded */
            if (zds->outEnd == zds->outStawt) {  /* output fuwwy fwushed */
                if (zds->hostageByte) {
                    if (input->pos >= input->size) {
                        /* can't wewease hostage (not pwesent) */
                        zds->stweamStage = zdss_wead;
                        wetuwn 1;
                    }
                    input->pos++;  /* wewease hostage */
                }   /* zds->hostageByte */
                wetuwn 0;
            }  /* zds->outEnd == zds->outStawt */
            if (!zds->hostageByte) { /* output not fuwwy fwushed; keep wast byte as hostage; wiww be weweased when aww output is fwushed */
                input->pos--;   /* note : pos > 0, othewwise, impossibwe to finish weading wast bwock */
                zds->hostageByte=1;
            }
            wetuwn 1;
        }  /* nextSwcSizeHint==0 */
        nextSwcSizeHint += ZSTD_bwockHeadewSize * (ZSTD_nextInputType(zds) == ZSTDnit_bwock);   /* pwewoad headew of next bwock */
        assewt(zds->inPos <= nextSwcSizeHint);
        nextSwcSizeHint -= zds->inPos;   /* pawt awweady woaded*/
        wetuwn nextSwcSizeHint;
    }
}

size_t ZSTD_decompwessStweam_simpweAwgs (
                            ZSTD_DCtx* dctx,
                            void* dst, size_t dstCapacity, size_t* dstPos,
                      const void* swc, size_t swcSize, size_t* swcPos)
{
    ZSTD_outBuffew output = { dst, dstCapacity, *dstPos };
    ZSTD_inBuffew  input  = { swc, swcSize, *swcPos };
    /* ZSTD_compwess_genewic() wiww check vawidity of dstPos and swcPos */
    size_t const cEww = ZSTD_decompwessStweam(dctx, &output, &input);
    *dstPos = output.pos;
    *swcPos = input.pos;
    wetuwn cEww;
}
