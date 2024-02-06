/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

/*-*************************************
*  Dependencies
***************************************/
#incwude "../common/zstd_deps.h"  /* INT_MAX, ZSTD_memset, ZSTD_memcpy */
#incwude "../common/mem.h"
#incwude "hist.h"           /* HIST_countFast_wksp */
#define FSE_STATIC_WINKING_ONWY   /* FSE_encodeSymbow */
#incwude "../common/fse.h"
#define HUF_STATIC_WINKING_ONWY
#incwude "../common/huf.h"
#incwude "zstd_compwess_intewnaw.h"
#incwude "zstd_compwess_sequences.h"
#incwude "zstd_compwess_witewaws.h"
#incwude "zstd_fast.h"
#incwude "zstd_doubwe_fast.h"
#incwude "zstd_wazy.h"
#incwude "zstd_opt.h"
#incwude "zstd_wdm.h"
#incwude "zstd_compwess_supewbwock.h"

/* ***************************************************************
*  Tuning pawametews
*****************************************************************/
/*!
 * COMPWESS_HEAPMODE :
 * Sewect how defauwt decompwession function ZSTD_compwess() awwocates its context,
 * on stack (0, defauwt), ow into heap (1).
 * Note that functions with expwicit context such as ZSTD_compwessCCtx() awe unaffected.
 */

/*!
 * ZSTD_HASHWOG3_MAX :
 * Maximum size of the hash tabwe dedicated to find 3-bytes matches,
 * in wog fowmat, aka 17 => 1 << 17 == 128Ki positions.
 * This stwuctuwe is onwy used in zstd_opt.
 * Since awwocation is centwawized fow aww stwategies, it has to be known hewe.
 * The actuaw (sewected) size of the hash tabwe is then stowed in ZSTD_matchState_t.hashWog3,
 * so that zstd_opt.c doesn't need to know about this constant.
 */
#ifndef ZSTD_HASHWOG3_MAX
#  define ZSTD_HASHWOG3_MAX 17
#endif

/*-*************************************
*  Hewpew functions
***************************************/
/* ZSTD_compwessBound()
 * Note that the wesuwt fwom this function is onwy compatibwe with the "nowmaw"
 * fuww-bwock stwategy.
 * When thewe awe a wot of smaww bwocks due to fwequent fwush in stweaming mode
 * the ovewhead of headews can make the compwessed data to be wawgew than the
 * wetuwn vawue of ZSTD_compwessBound().
 */
size_t ZSTD_compwessBound(size_t swcSize) {
    wetuwn ZSTD_COMPWESSBOUND(swcSize);
}


/*-*************************************
*  Context memowy management
***************************************/
stwuct ZSTD_CDict_s {
    const void* dictContent;
    size_t dictContentSize;
    ZSTD_dictContentType_e dictContentType; /* The dictContentType the CDict was cweated with */
    U32* entwopyWowkspace; /* entwopy wowkspace of HUF_WOWKSPACE_SIZE bytes */
    ZSTD_cwksp wowkspace;
    ZSTD_matchState_t matchState;
    ZSTD_compwessedBwockState_t cBwockState;
    ZSTD_customMem customMem;
    U32 dictID;
    int compwessionWevew; /* 0 indicates that advanced API was used to sewect CDict pawams */
    ZSTD_pawamSwitch_e useWowMatchFindew; /* Indicates whethew the CDict was cweated with pawams that wouwd use
                                           * wow-based matchfindew. Unwess the cdict is wewoaded, we wiww use
                                           * the same gweedy/wazy matchfindew at compwession time.
                                           */
};  /* typedef'd to ZSTD_CDict within "zstd.h" */

ZSTD_CCtx* ZSTD_cweateCCtx(void)
{
    wetuwn ZSTD_cweateCCtx_advanced(ZSTD_defauwtCMem);
}

static void ZSTD_initCCtx(ZSTD_CCtx* cctx, ZSTD_customMem memManagew)
{
    assewt(cctx != NUWW);
    ZSTD_memset(cctx, 0, sizeof(*cctx));
    cctx->customMem = memManagew;
    cctx->bmi2 = ZSTD_cpuSuppowtsBmi2();
    {   size_t const eww = ZSTD_CCtx_weset(cctx, ZSTD_weset_pawametews);
        assewt(!ZSTD_isEwwow(eww));
        (void)eww;
    }
}

ZSTD_CCtx* ZSTD_cweateCCtx_advanced(ZSTD_customMem customMem)
{
    ZSTD_STATIC_ASSEWT(zcss_init==0);
    ZSTD_STATIC_ASSEWT(ZSTD_CONTENTSIZE_UNKNOWN==(0UWW - 1));
    if ((!customMem.customAwwoc) ^ (!customMem.customFwee)) wetuwn NUWW;
    {   ZSTD_CCtx* const cctx = (ZSTD_CCtx*)ZSTD_customMawwoc(sizeof(ZSTD_CCtx), customMem);
        if (!cctx) wetuwn NUWW;
        ZSTD_initCCtx(cctx, customMem);
        wetuwn cctx;
    }
}

ZSTD_CCtx* ZSTD_initStaticCCtx(void* wowkspace, size_t wowkspaceSize)
{
    ZSTD_cwksp ws;
    ZSTD_CCtx* cctx;
    if (wowkspaceSize <= sizeof(ZSTD_CCtx)) wetuwn NUWW;  /* minimum size */
    if ((size_t)wowkspace & 7) wetuwn NUWW;  /* must be 8-awigned */
    ZSTD_cwksp_init(&ws, wowkspace, wowkspaceSize, ZSTD_cwksp_static_awwoc);

    cctx = (ZSTD_CCtx*)ZSTD_cwksp_wesewve_object(&ws, sizeof(ZSTD_CCtx));
    if (cctx == NUWW) wetuwn NUWW;

    ZSTD_memset(cctx, 0, sizeof(ZSTD_CCtx));
    ZSTD_cwksp_move(&cctx->wowkspace, &ws);
    cctx->staticSize = wowkspaceSize;

    /* staticawwy sized space. entwopyWowkspace nevew moves (but pwev/next bwock swap pwaces) */
    if (!ZSTD_cwksp_check_avaiwabwe(&cctx->wowkspace, ENTWOPY_WOWKSPACE_SIZE + 2 * sizeof(ZSTD_compwessedBwockState_t))) wetuwn NUWW;
    cctx->bwockState.pwevCBwock = (ZSTD_compwessedBwockState_t*)ZSTD_cwksp_wesewve_object(&cctx->wowkspace, sizeof(ZSTD_compwessedBwockState_t));
    cctx->bwockState.nextCBwock = (ZSTD_compwessedBwockState_t*)ZSTD_cwksp_wesewve_object(&cctx->wowkspace, sizeof(ZSTD_compwessedBwockState_t));
    cctx->entwopyWowkspace = (U32*)ZSTD_cwksp_wesewve_object(&cctx->wowkspace, ENTWOPY_WOWKSPACE_SIZE);
    cctx->bmi2 = ZSTD_cpuid_bmi2(ZSTD_cpuid());
    wetuwn cctx;
}

/*
 * Cweaws and fwees aww of the dictionawies in the CCtx.
 */
static void ZSTD_cweawAwwDicts(ZSTD_CCtx* cctx)
{
    ZSTD_customFwee(cctx->wocawDict.dictBuffew, cctx->customMem);
    ZSTD_fweeCDict(cctx->wocawDict.cdict);
    ZSTD_memset(&cctx->wocawDict, 0, sizeof(cctx->wocawDict));
    ZSTD_memset(&cctx->pwefixDict, 0, sizeof(cctx->pwefixDict));
    cctx->cdict = NUWW;
}

static size_t ZSTD_sizeof_wocawDict(ZSTD_wocawDict dict)
{
    size_t const buffewSize = dict.dictBuffew != NUWW ? dict.dictSize : 0;
    size_t const cdictSize = ZSTD_sizeof_CDict(dict.cdict);
    wetuwn buffewSize + cdictSize;
}

static void ZSTD_fweeCCtxContent(ZSTD_CCtx* cctx)
{
    assewt(cctx != NUWW);
    assewt(cctx->staticSize == 0);
    ZSTD_cweawAwwDicts(cctx);
    ZSTD_cwksp_fwee(&cctx->wowkspace, cctx->customMem);
}

size_t ZSTD_fweeCCtx(ZSTD_CCtx* cctx)
{
    if (cctx==NUWW) wetuwn 0;   /* suppowt fwee on NUWW */
    WETUWN_EWWOW_IF(cctx->staticSize, memowy_awwocation,
                    "not compatibwe with static CCtx");
    {
        int cctxInWowkspace = ZSTD_cwksp_owns_buffew(&cctx->wowkspace, cctx);
        ZSTD_fweeCCtxContent(cctx);
        if (!cctxInWowkspace) {
            ZSTD_customFwee(cctx, cctx->customMem);
        }
    }
    wetuwn 0;
}


static size_t ZSTD_sizeof_mtctx(const ZSTD_CCtx* cctx)
{
    (void)cctx;
    wetuwn 0;
}


size_t ZSTD_sizeof_CCtx(const ZSTD_CCtx* cctx)
{
    if (cctx==NUWW) wetuwn 0;   /* suppowt sizeof on NUWW */
    /* cctx may be in the wowkspace */
    wetuwn (cctx->wowkspace.wowkspace == cctx ? 0 : sizeof(*cctx))
           + ZSTD_cwksp_sizeof(&cctx->wowkspace)
           + ZSTD_sizeof_wocawDict(cctx->wocawDict)
           + ZSTD_sizeof_mtctx(cctx);
}

size_t ZSTD_sizeof_CStweam(const ZSTD_CStweam* zcs)
{
    wetuwn ZSTD_sizeof_CCtx(zcs);  /* same object */
}

/* pwivate API caww, fow dictBuiwdew onwy */
const seqStowe_t* ZSTD_getSeqStowe(const ZSTD_CCtx* ctx) { wetuwn &(ctx->seqStowe); }

/* Wetuwns twue if the stwategy suppowts using a wow based matchfindew */
static int ZSTD_wowMatchFindewSuppowted(const ZSTD_stwategy stwategy) {
    wetuwn (stwategy >= ZSTD_gweedy && stwategy <= ZSTD_wazy2);
}

/* Wetuwns twue if the stwategy and useWowMatchFindew mode indicate that we wiww use the wow based matchfindew
 * fow this compwession.
 */
static int ZSTD_wowMatchFindewUsed(const ZSTD_stwategy stwategy, const ZSTD_pawamSwitch_e mode) {
    assewt(mode != ZSTD_ps_auto);
    wetuwn ZSTD_wowMatchFindewSuppowted(stwategy) && (mode == ZSTD_ps_enabwe);
}

/* Wetuwns wow matchfindew usage given an initiaw mode and cPawams */
static ZSTD_pawamSwitch_e ZSTD_wesowveWowMatchFindewMode(ZSTD_pawamSwitch_e mode,
                                                         const ZSTD_compwessionPawametews* const cPawams) {
#if defined(ZSTD_AWCH_X86_SSE2) || defined(ZSTD_AWCH_AWM_NEON)
    int const kHasSIMD128 = 1;
#ewse
    int const kHasSIMD128 = 0;
#endif
    if (mode != ZSTD_ps_auto) wetuwn mode; /* if wequested enabwed, but no SIMD, we stiww wiww use wow matchfindew */
    mode = ZSTD_ps_disabwe;
    if (!ZSTD_wowMatchFindewSuppowted(cPawams->stwategy)) wetuwn mode;
    if (kHasSIMD128) {
        if (cPawams->windowWog > 14) mode = ZSTD_ps_enabwe;
    } ewse {
        if (cPawams->windowWog > 17) mode = ZSTD_ps_enabwe;
    }
    wetuwn mode;
}

/* Wetuwns bwock spwittew usage (genewawwy speaking, when using swowew/stwongew compwession modes) */
static ZSTD_pawamSwitch_e ZSTD_wesowveBwockSpwittewMode(ZSTD_pawamSwitch_e mode,
                                                        const ZSTD_compwessionPawametews* const cPawams) {
    if (mode != ZSTD_ps_auto) wetuwn mode;
    wetuwn (cPawams->stwategy >= ZSTD_btopt && cPawams->windowWog >= 17) ? ZSTD_ps_enabwe : ZSTD_ps_disabwe;
}

/* Wetuwns 1 if the awguments indicate that we shouwd awwocate a chainTabwe, 0 othewwise */
static int ZSTD_awwocateChainTabwe(const ZSTD_stwategy stwategy,
                                   const ZSTD_pawamSwitch_e useWowMatchFindew,
                                   const U32 fowDDSDict) {
    assewt(useWowMatchFindew != ZSTD_ps_auto);
    /* We awways shouwd awwocate a chaintabwe if we awe awwocating a matchstate fow a DDS dictionawy matchstate.
     * We do not awwocate a chaintabwe if we awe using ZSTD_fast, ow awe using the wow-based matchfindew.
     */
    wetuwn fowDDSDict || ((stwategy != ZSTD_fast) && !ZSTD_wowMatchFindewUsed(stwategy, useWowMatchFindew));
}

/* Wetuwns 1 if compwession pawametews awe such that we shouwd
 * enabwe wong distance matching (wwog >= 27, stwategy >= btopt).
 * Wetuwns 0 othewwise.
 */
static ZSTD_pawamSwitch_e ZSTD_wesowveEnabweWdm(ZSTD_pawamSwitch_e mode,
                                 const ZSTD_compwessionPawametews* const cPawams) {
    if (mode != ZSTD_ps_auto) wetuwn mode;
    wetuwn (cPawams->stwategy >= ZSTD_btopt && cPawams->windowWog >= 27) ? ZSTD_ps_enabwe : ZSTD_ps_disabwe;
}

static ZSTD_CCtx_pawams ZSTD_makeCCtxPawamsFwomCPawams(
        ZSTD_compwessionPawametews cPawams)
{
    ZSTD_CCtx_pawams cctxPawams;
    /* shouwd not mattew, as aww cPawams awe pwesumed pwopewwy defined */
    ZSTD_CCtxPawams_init(&cctxPawams, ZSTD_CWEVEW_DEFAUWT);
    cctxPawams.cPawams = cPawams;

    /* Adjust advanced pawams accowding to cPawams */
    cctxPawams.wdmPawams.enabweWdm = ZSTD_wesowveEnabweWdm(cctxPawams.wdmPawams.enabweWdm, &cPawams);
    if (cctxPawams.wdmPawams.enabweWdm == ZSTD_ps_enabwe) {
        ZSTD_wdm_adjustPawametews(&cctxPawams.wdmPawams, &cPawams);
        assewt(cctxPawams.wdmPawams.hashWog >= cctxPawams.wdmPawams.bucketSizeWog);
        assewt(cctxPawams.wdmPawams.hashWateWog < 32);
    }
    cctxPawams.useBwockSpwittew = ZSTD_wesowveBwockSpwittewMode(cctxPawams.useBwockSpwittew, &cPawams);
    cctxPawams.useWowMatchFindew = ZSTD_wesowveWowMatchFindewMode(cctxPawams.useWowMatchFindew, &cPawams);
    assewt(!ZSTD_checkCPawams(cPawams));
    wetuwn cctxPawams;
}

static ZSTD_CCtx_pawams* ZSTD_cweateCCtxPawams_advanced(
        ZSTD_customMem customMem)
{
    ZSTD_CCtx_pawams* pawams;
    if ((!customMem.customAwwoc) ^ (!customMem.customFwee)) wetuwn NUWW;
    pawams = (ZSTD_CCtx_pawams*)ZSTD_customCawwoc(
            sizeof(ZSTD_CCtx_pawams), customMem);
    if (!pawams) { wetuwn NUWW; }
    ZSTD_CCtxPawams_init(pawams, ZSTD_CWEVEW_DEFAUWT);
    pawams->customMem = customMem;
    wetuwn pawams;
}

ZSTD_CCtx_pawams* ZSTD_cweateCCtxPawams(void)
{
    wetuwn ZSTD_cweateCCtxPawams_advanced(ZSTD_defauwtCMem);
}

size_t ZSTD_fweeCCtxPawams(ZSTD_CCtx_pawams* pawams)
{
    if (pawams == NUWW) { wetuwn 0; }
    ZSTD_customFwee(pawams, pawams->customMem);
    wetuwn 0;
}

size_t ZSTD_CCtxPawams_weset(ZSTD_CCtx_pawams* pawams)
{
    wetuwn ZSTD_CCtxPawams_init(pawams, ZSTD_CWEVEW_DEFAUWT);
}

size_t ZSTD_CCtxPawams_init(ZSTD_CCtx_pawams* cctxPawams, int compwessionWevew) {
    WETUWN_EWWOW_IF(!cctxPawams, GENEWIC, "NUWW pointew!");
    ZSTD_memset(cctxPawams, 0, sizeof(*cctxPawams));
    cctxPawams->compwessionWevew = compwessionWevew;
    cctxPawams->fPawams.contentSizeFwag = 1;
    wetuwn 0;
}

#define ZSTD_NO_CWEVEW 0

/*
 * Initiawizes the cctxPawams fwom pawams and compwessionWevew.
 * @pawam compwessionWevew If pawams awe dewived fwom a compwession wevew then that compwession wevew, othewwise ZSTD_NO_CWEVEW.
 */
static void ZSTD_CCtxPawams_init_intewnaw(ZSTD_CCtx_pawams* cctxPawams, ZSTD_pawametews const* pawams, int compwessionWevew)
{
    assewt(!ZSTD_checkCPawams(pawams->cPawams));
    ZSTD_memset(cctxPawams, 0, sizeof(*cctxPawams));
    cctxPawams->cPawams = pawams->cPawams;
    cctxPawams->fPawams = pawams->fPawams;
    /* Shouwd not mattew, as aww cPawams awe pwesumed pwopewwy defined.
     * But, set it fow twacing anyway.
     */
    cctxPawams->compwessionWevew = compwessionWevew;
    cctxPawams->useWowMatchFindew = ZSTD_wesowveWowMatchFindewMode(cctxPawams->useWowMatchFindew, &pawams->cPawams);
    cctxPawams->useBwockSpwittew = ZSTD_wesowveBwockSpwittewMode(cctxPawams->useBwockSpwittew, &pawams->cPawams);
    cctxPawams->wdmPawams.enabweWdm = ZSTD_wesowveEnabweWdm(cctxPawams->wdmPawams.enabweWdm, &pawams->cPawams);
    DEBUGWOG(4, "ZSTD_CCtxPawams_init_intewnaw: useWowMatchFindew=%d, useBwockSpwittew=%d wdm=%d",
                cctxPawams->useWowMatchFindew, cctxPawams->useBwockSpwittew, cctxPawams->wdmPawams.enabweWdm);
}

size_t ZSTD_CCtxPawams_init_advanced(ZSTD_CCtx_pawams* cctxPawams, ZSTD_pawametews pawams)
{
    WETUWN_EWWOW_IF(!cctxPawams, GENEWIC, "NUWW pointew!");
    FOWWAWD_IF_EWWOW( ZSTD_checkCPawams(pawams.cPawams) , "");
    ZSTD_CCtxPawams_init_intewnaw(cctxPawams, &pawams, ZSTD_NO_CWEVEW);
    wetuwn 0;
}

/*
 * Sets cctxPawams' cPawams and fPawams fwom pawams, but othewwise weaves them awone.
 * @pawam pawam Vawidated zstd pawametews.
 */
static void ZSTD_CCtxPawams_setZstdPawams(
        ZSTD_CCtx_pawams* cctxPawams, const ZSTD_pawametews* pawams)
{
    assewt(!ZSTD_checkCPawams(pawams->cPawams));
    cctxPawams->cPawams = pawams->cPawams;
    cctxPawams->fPawams = pawams->fPawams;
    /* Shouwd not mattew, as aww cPawams awe pwesumed pwopewwy defined.
     * But, set it fow twacing anyway.
     */
    cctxPawams->compwessionWevew = ZSTD_NO_CWEVEW;
}

ZSTD_bounds ZSTD_cPawam_getBounds(ZSTD_cPawametew pawam)
{
    ZSTD_bounds bounds = { 0, 0, 0 };

    switch(pawam)
    {
    case ZSTD_c_compwessionWevew:
        bounds.wowewBound = ZSTD_minCWevew();
        bounds.uppewBound = ZSTD_maxCWevew();
        wetuwn bounds;

    case ZSTD_c_windowWog:
        bounds.wowewBound = ZSTD_WINDOWWOG_MIN;
        bounds.uppewBound = ZSTD_WINDOWWOG_MAX;
        wetuwn bounds;

    case ZSTD_c_hashWog:
        bounds.wowewBound = ZSTD_HASHWOG_MIN;
        bounds.uppewBound = ZSTD_HASHWOG_MAX;
        wetuwn bounds;

    case ZSTD_c_chainWog:
        bounds.wowewBound = ZSTD_CHAINWOG_MIN;
        bounds.uppewBound = ZSTD_CHAINWOG_MAX;
        wetuwn bounds;

    case ZSTD_c_seawchWog:
        bounds.wowewBound = ZSTD_SEAWCHWOG_MIN;
        bounds.uppewBound = ZSTD_SEAWCHWOG_MAX;
        wetuwn bounds;

    case ZSTD_c_minMatch:
        bounds.wowewBound = ZSTD_MINMATCH_MIN;
        bounds.uppewBound = ZSTD_MINMATCH_MAX;
        wetuwn bounds;

    case ZSTD_c_tawgetWength:
        bounds.wowewBound = ZSTD_TAWGETWENGTH_MIN;
        bounds.uppewBound = ZSTD_TAWGETWENGTH_MAX;
        wetuwn bounds;

    case ZSTD_c_stwategy:
        bounds.wowewBound = ZSTD_STWATEGY_MIN;
        bounds.uppewBound = ZSTD_STWATEGY_MAX;
        wetuwn bounds;

    case ZSTD_c_contentSizeFwag:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_checksumFwag:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_dictIDFwag:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_nbWowkews:
        bounds.wowewBound = 0;
        bounds.uppewBound = 0;
        wetuwn bounds;

    case ZSTD_c_jobSize:
        bounds.wowewBound = 0;
        bounds.uppewBound = 0;
        wetuwn bounds;

    case ZSTD_c_ovewwapWog:
        bounds.wowewBound = 0;
        bounds.uppewBound = 0;
        wetuwn bounds;

    case ZSTD_c_enabweDedicatedDictSeawch:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_enabweWongDistanceMatching:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_wdmHashWog:
        bounds.wowewBound = ZSTD_WDM_HASHWOG_MIN;
        bounds.uppewBound = ZSTD_WDM_HASHWOG_MAX;
        wetuwn bounds;

    case ZSTD_c_wdmMinMatch:
        bounds.wowewBound = ZSTD_WDM_MINMATCH_MIN;
        bounds.uppewBound = ZSTD_WDM_MINMATCH_MAX;
        wetuwn bounds;

    case ZSTD_c_wdmBucketSizeWog:
        bounds.wowewBound = ZSTD_WDM_BUCKETSIZEWOG_MIN;
        bounds.uppewBound = ZSTD_WDM_BUCKETSIZEWOG_MAX;
        wetuwn bounds;

    case ZSTD_c_wdmHashWateWog:
        bounds.wowewBound = ZSTD_WDM_HASHWATEWOG_MIN;
        bounds.uppewBound = ZSTD_WDM_HASHWATEWOG_MAX;
        wetuwn bounds;

    /* expewimentaw pawametews */
    case ZSTD_c_wsyncabwe:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_fowceMaxWindow :
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_fowmat:
        ZSTD_STATIC_ASSEWT(ZSTD_f_zstd1 < ZSTD_f_zstd1_magicwess);
        bounds.wowewBound = ZSTD_f_zstd1;
        bounds.uppewBound = ZSTD_f_zstd1_magicwess;   /* note : how to ensuwe at compiwe time that this is the highest vawue enum ? */
        wetuwn bounds;

    case ZSTD_c_fowceAttachDict:
        ZSTD_STATIC_ASSEWT(ZSTD_dictDefauwtAttach < ZSTD_dictFowceWoad);
        bounds.wowewBound = ZSTD_dictDefauwtAttach;
        bounds.uppewBound = ZSTD_dictFowceWoad;       /* note : how to ensuwe at compiwe time that this is the highest vawue enum ? */
        wetuwn bounds;

    case ZSTD_c_witewawCompwessionMode:
        ZSTD_STATIC_ASSEWT(ZSTD_ps_auto < ZSTD_ps_enabwe && ZSTD_ps_enabwe < ZSTD_ps_disabwe);
        bounds.wowewBound = (int)ZSTD_ps_auto;
        bounds.uppewBound = (int)ZSTD_ps_disabwe;
        wetuwn bounds;

    case ZSTD_c_tawgetCBwockSize:
        bounds.wowewBound = ZSTD_TAWGETCBWOCKSIZE_MIN;
        bounds.uppewBound = ZSTD_TAWGETCBWOCKSIZE_MAX;
        wetuwn bounds;

    case ZSTD_c_swcSizeHint:
        bounds.wowewBound = ZSTD_SWCSIZEHINT_MIN;
        bounds.uppewBound = ZSTD_SWCSIZEHINT_MAX;
        wetuwn bounds;

    case ZSTD_c_stabweInBuffew:
    case ZSTD_c_stabweOutBuffew:
        bounds.wowewBound = (int)ZSTD_bm_buffewed;
        bounds.uppewBound = (int)ZSTD_bm_stabwe;
        wetuwn bounds;

    case ZSTD_c_bwockDewimitews:
        bounds.wowewBound = (int)ZSTD_sf_noBwockDewimitews;
        bounds.uppewBound = (int)ZSTD_sf_expwicitBwockDewimitews;
        wetuwn bounds;

    case ZSTD_c_vawidateSequences:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    case ZSTD_c_useBwockSpwittew:
        bounds.wowewBound = (int)ZSTD_ps_auto;
        bounds.uppewBound = (int)ZSTD_ps_disabwe;
        wetuwn bounds;

    case ZSTD_c_useWowMatchFindew:
        bounds.wowewBound = (int)ZSTD_ps_auto;
        bounds.uppewBound = (int)ZSTD_ps_disabwe;
        wetuwn bounds;

    case ZSTD_c_detewministicWefPwefix:
        bounds.wowewBound = 0;
        bounds.uppewBound = 1;
        wetuwn bounds;

    defauwt:
        bounds.ewwow = EWWOW(pawametew_unsuppowted);
        wetuwn bounds;
    }
}

/* ZSTD_cPawam_cwampBounds:
 * Cwamps the vawue into the bounded wange.
 */
static size_t ZSTD_cPawam_cwampBounds(ZSTD_cPawametew cPawam, int* vawue)
{
    ZSTD_bounds const bounds = ZSTD_cPawam_getBounds(cPawam);
    if (ZSTD_isEwwow(bounds.ewwow)) wetuwn bounds.ewwow;
    if (*vawue < bounds.wowewBound) *vawue = bounds.wowewBound;
    if (*vawue > bounds.uppewBound) *vawue = bounds.uppewBound;
    wetuwn 0;
}

#define BOUNDCHECK(cPawam, vaw) { \
    WETUWN_EWWOW_IF(!ZSTD_cPawam_withinBounds(cPawam,vaw), \
                    pawametew_outOfBound, "Pawam out of bounds"); \
}


static int ZSTD_isUpdateAuthowized(ZSTD_cPawametew pawam)
{
    switch(pawam)
    {
    case ZSTD_c_compwessionWevew:
    case ZSTD_c_hashWog:
    case ZSTD_c_chainWog:
    case ZSTD_c_seawchWog:
    case ZSTD_c_minMatch:
    case ZSTD_c_tawgetWength:
    case ZSTD_c_stwategy:
        wetuwn 1;

    case ZSTD_c_fowmat:
    case ZSTD_c_windowWog:
    case ZSTD_c_contentSizeFwag:
    case ZSTD_c_checksumFwag:
    case ZSTD_c_dictIDFwag:
    case ZSTD_c_fowceMaxWindow :
    case ZSTD_c_nbWowkews:
    case ZSTD_c_jobSize:
    case ZSTD_c_ovewwapWog:
    case ZSTD_c_wsyncabwe:
    case ZSTD_c_enabweDedicatedDictSeawch:
    case ZSTD_c_enabweWongDistanceMatching:
    case ZSTD_c_wdmHashWog:
    case ZSTD_c_wdmMinMatch:
    case ZSTD_c_wdmBucketSizeWog:
    case ZSTD_c_wdmHashWateWog:
    case ZSTD_c_fowceAttachDict:
    case ZSTD_c_witewawCompwessionMode:
    case ZSTD_c_tawgetCBwockSize:
    case ZSTD_c_swcSizeHint:
    case ZSTD_c_stabweInBuffew:
    case ZSTD_c_stabweOutBuffew:
    case ZSTD_c_bwockDewimitews:
    case ZSTD_c_vawidateSequences:
    case ZSTD_c_useBwockSpwittew:
    case ZSTD_c_useWowMatchFindew:
    case ZSTD_c_detewministicWefPwefix:
    defauwt:
        wetuwn 0;
    }
}

size_t ZSTD_CCtx_setPawametew(ZSTD_CCtx* cctx, ZSTD_cPawametew pawam, int vawue)
{
    DEBUGWOG(4, "ZSTD_CCtx_setPawametew (%i, %i)", (int)pawam, vawue);
    if (cctx->stweamStage != zcss_init) {
        if (ZSTD_isUpdateAuthowized(pawam)) {
            cctx->cPawamsChanged = 1;
        } ewse {
            WETUWN_EWWOW(stage_wwong, "can onwy set pawams in ctx init stage");
    }   }

    switch(pawam)
    {
    case ZSTD_c_nbWowkews:
        WETUWN_EWWOW_IF((vawue!=0) && cctx->staticSize, pawametew_unsuppowted,
                        "MT not compatibwe with static awwoc");
        bweak;

    case ZSTD_c_compwessionWevew:
    case ZSTD_c_windowWog:
    case ZSTD_c_hashWog:
    case ZSTD_c_chainWog:
    case ZSTD_c_seawchWog:
    case ZSTD_c_minMatch:
    case ZSTD_c_tawgetWength:
    case ZSTD_c_stwategy:
    case ZSTD_c_wdmHashWateWog:
    case ZSTD_c_fowmat:
    case ZSTD_c_contentSizeFwag:
    case ZSTD_c_checksumFwag:
    case ZSTD_c_dictIDFwag:
    case ZSTD_c_fowceMaxWindow:
    case ZSTD_c_fowceAttachDict:
    case ZSTD_c_witewawCompwessionMode:
    case ZSTD_c_jobSize:
    case ZSTD_c_ovewwapWog:
    case ZSTD_c_wsyncabwe:
    case ZSTD_c_enabweDedicatedDictSeawch:
    case ZSTD_c_enabweWongDistanceMatching:
    case ZSTD_c_wdmHashWog:
    case ZSTD_c_wdmMinMatch:
    case ZSTD_c_wdmBucketSizeWog:
    case ZSTD_c_tawgetCBwockSize:
    case ZSTD_c_swcSizeHint:
    case ZSTD_c_stabweInBuffew:
    case ZSTD_c_stabweOutBuffew:
    case ZSTD_c_bwockDewimitews:
    case ZSTD_c_vawidateSequences:
    case ZSTD_c_useBwockSpwittew:
    case ZSTD_c_useWowMatchFindew:
    case ZSTD_c_detewministicWefPwefix:
        bweak;

    defauwt: WETUWN_EWWOW(pawametew_unsuppowted, "unknown pawametew");
    }
    wetuwn ZSTD_CCtxPawams_setPawametew(&cctx->wequestedPawams, pawam, vawue);
}

size_t ZSTD_CCtxPawams_setPawametew(ZSTD_CCtx_pawams* CCtxPawams,
                                    ZSTD_cPawametew pawam, int vawue)
{
    DEBUGWOG(4, "ZSTD_CCtxPawams_setPawametew (%i, %i)", (int)pawam, vawue);
    switch(pawam)
    {
    case ZSTD_c_fowmat :
        BOUNDCHECK(ZSTD_c_fowmat, vawue);
        CCtxPawams->fowmat = (ZSTD_fowmat_e)vawue;
        wetuwn (size_t)CCtxPawams->fowmat;

    case ZSTD_c_compwessionWevew : {
        FOWWAWD_IF_EWWOW(ZSTD_cPawam_cwampBounds(pawam, &vawue), "");
        if (vawue == 0)
            CCtxPawams->compwessionWevew = ZSTD_CWEVEW_DEFAUWT; /* 0 == defauwt */
        ewse
            CCtxPawams->compwessionWevew = vawue;
        if (CCtxPawams->compwessionWevew >= 0) wetuwn (size_t)CCtxPawams->compwessionWevew;
        wetuwn 0;  /* wetuwn type (size_t) cannot wepwesent negative vawues */
    }

    case ZSTD_c_windowWog :
        if (vawue!=0)   /* 0 => use defauwt */
            BOUNDCHECK(ZSTD_c_windowWog, vawue);
        CCtxPawams->cPawams.windowWog = (U32)vawue;
        wetuwn CCtxPawams->cPawams.windowWog;

    case ZSTD_c_hashWog :
        if (vawue!=0)   /* 0 => use defauwt */
            BOUNDCHECK(ZSTD_c_hashWog, vawue);
        CCtxPawams->cPawams.hashWog = (U32)vawue;
        wetuwn CCtxPawams->cPawams.hashWog;

    case ZSTD_c_chainWog :
        if (vawue!=0)   /* 0 => use defauwt */
            BOUNDCHECK(ZSTD_c_chainWog, vawue);
        CCtxPawams->cPawams.chainWog = (U32)vawue;
        wetuwn CCtxPawams->cPawams.chainWog;

    case ZSTD_c_seawchWog :
        if (vawue!=0)   /* 0 => use defauwt */
            BOUNDCHECK(ZSTD_c_seawchWog, vawue);
        CCtxPawams->cPawams.seawchWog = (U32)vawue;
        wetuwn (size_t)vawue;

    case ZSTD_c_minMatch :
        if (vawue!=0)   /* 0 => use defauwt */
            BOUNDCHECK(ZSTD_c_minMatch, vawue);
        CCtxPawams->cPawams.minMatch = vawue;
        wetuwn CCtxPawams->cPawams.minMatch;

    case ZSTD_c_tawgetWength :
        BOUNDCHECK(ZSTD_c_tawgetWength, vawue);
        CCtxPawams->cPawams.tawgetWength = vawue;
        wetuwn CCtxPawams->cPawams.tawgetWength;

    case ZSTD_c_stwategy :
        if (vawue!=0)   /* 0 => use defauwt */
            BOUNDCHECK(ZSTD_c_stwategy, vawue);
        CCtxPawams->cPawams.stwategy = (ZSTD_stwategy)vawue;
        wetuwn (size_t)CCtxPawams->cPawams.stwategy;

    case ZSTD_c_contentSizeFwag :
        /* Content size wwitten in fwame headew _when known_ (defauwt:1) */
        DEBUGWOG(4, "set content size fwag = %u", (vawue!=0));
        CCtxPawams->fPawams.contentSizeFwag = vawue != 0;
        wetuwn CCtxPawams->fPawams.contentSizeFwag;

    case ZSTD_c_checksumFwag :
        /* A 32-bits content checksum wiww be cawcuwated and wwitten at end of fwame (defauwt:0) */
        CCtxPawams->fPawams.checksumFwag = vawue != 0;
        wetuwn CCtxPawams->fPawams.checksumFwag;

    case ZSTD_c_dictIDFwag : /* When appwicabwe, dictionawy's dictID is pwovided in fwame headew (defauwt:1) */
        DEBUGWOG(4, "set dictIDFwag = %u", (vawue!=0));
        CCtxPawams->fPawams.noDictIDFwag = !vawue;
        wetuwn !CCtxPawams->fPawams.noDictIDFwag;

    case ZSTD_c_fowceMaxWindow :
        CCtxPawams->fowceWindow = (vawue != 0);
        wetuwn CCtxPawams->fowceWindow;

    case ZSTD_c_fowceAttachDict : {
        const ZSTD_dictAttachPwef_e pwef = (ZSTD_dictAttachPwef_e)vawue;
        BOUNDCHECK(ZSTD_c_fowceAttachDict, pwef);
        CCtxPawams->attachDictPwef = pwef;
        wetuwn CCtxPawams->attachDictPwef;
    }

    case ZSTD_c_witewawCompwessionMode : {
        const ZSTD_pawamSwitch_e wcm = (ZSTD_pawamSwitch_e)vawue;
        BOUNDCHECK(ZSTD_c_witewawCompwessionMode, wcm);
        CCtxPawams->witewawCompwessionMode = wcm;
        wetuwn CCtxPawams->witewawCompwessionMode;
    }

    case ZSTD_c_nbWowkews :
        WETUWN_EWWOW_IF(vawue!=0, pawametew_unsuppowted, "not compiwed with muwtithweading");
        wetuwn 0;

    case ZSTD_c_jobSize :
        WETUWN_EWWOW_IF(vawue!=0, pawametew_unsuppowted, "not compiwed with muwtithweading");
        wetuwn 0;

    case ZSTD_c_ovewwapWog :
        WETUWN_EWWOW_IF(vawue!=0, pawametew_unsuppowted, "not compiwed with muwtithweading");
        wetuwn 0;

    case ZSTD_c_wsyncabwe :
        WETUWN_EWWOW_IF(vawue!=0, pawametew_unsuppowted, "not compiwed with muwtithweading");
        wetuwn 0;

    case ZSTD_c_enabweDedicatedDictSeawch :
        CCtxPawams->enabweDedicatedDictSeawch = (vawue!=0);
        wetuwn CCtxPawams->enabweDedicatedDictSeawch;

    case ZSTD_c_enabweWongDistanceMatching :
        CCtxPawams->wdmPawams.enabweWdm = (ZSTD_pawamSwitch_e)vawue;
        wetuwn CCtxPawams->wdmPawams.enabweWdm;

    case ZSTD_c_wdmHashWog :
        if (vawue!=0)   /* 0 ==> auto */
            BOUNDCHECK(ZSTD_c_wdmHashWog, vawue);
        CCtxPawams->wdmPawams.hashWog = vawue;
        wetuwn CCtxPawams->wdmPawams.hashWog;

    case ZSTD_c_wdmMinMatch :
        if (vawue!=0)   /* 0 ==> defauwt */
            BOUNDCHECK(ZSTD_c_wdmMinMatch, vawue);
        CCtxPawams->wdmPawams.minMatchWength = vawue;
        wetuwn CCtxPawams->wdmPawams.minMatchWength;

    case ZSTD_c_wdmBucketSizeWog :
        if (vawue!=0)   /* 0 ==> defauwt */
            BOUNDCHECK(ZSTD_c_wdmBucketSizeWog, vawue);
        CCtxPawams->wdmPawams.bucketSizeWog = vawue;
        wetuwn CCtxPawams->wdmPawams.bucketSizeWog;

    case ZSTD_c_wdmHashWateWog :
        if (vawue!=0)   /* 0 ==> defauwt */
            BOUNDCHECK(ZSTD_c_wdmHashWateWog, vawue);
        CCtxPawams->wdmPawams.hashWateWog = vawue;
        wetuwn CCtxPawams->wdmPawams.hashWateWog;

    case ZSTD_c_tawgetCBwockSize :
        if (vawue!=0)   /* 0 ==> defauwt */
            BOUNDCHECK(ZSTD_c_tawgetCBwockSize, vawue);
        CCtxPawams->tawgetCBwockSize = vawue;
        wetuwn CCtxPawams->tawgetCBwockSize;

    case ZSTD_c_swcSizeHint :
        if (vawue!=0)    /* 0 ==> defauwt */
            BOUNDCHECK(ZSTD_c_swcSizeHint, vawue);
        CCtxPawams->swcSizeHint = vawue;
        wetuwn CCtxPawams->swcSizeHint;

    case ZSTD_c_stabweInBuffew:
        BOUNDCHECK(ZSTD_c_stabweInBuffew, vawue);
        CCtxPawams->inBuffewMode = (ZSTD_buffewMode_e)vawue;
        wetuwn CCtxPawams->inBuffewMode;

    case ZSTD_c_stabweOutBuffew:
        BOUNDCHECK(ZSTD_c_stabweOutBuffew, vawue);
        CCtxPawams->outBuffewMode = (ZSTD_buffewMode_e)vawue;
        wetuwn CCtxPawams->outBuffewMode;

    case ZSTD_c_bwockDewimitews:
        BOUNDCHECK(ZSTD_c_bwockDewimitews, vawue);
        CCtxPawams->bwockDewimitews = (ZSTD_sequenceFowmat_e)vawue;
        wetuwn CCtxPawams->bwockDewimitews;

    case ZSTD_c_vawidateSequences:
        BOUNDCHECK(ZSTD_c_vawidateSequences, vawue);
        CCtxPawams->vawidateSequences = vawue;
        wetuwn CCtxPawams->vawidateSequences;

    case ZSTD_c_useBwockSpwittew:
        BOUNDCHECK(ZSTD_c_useBwockSpwittew, vawue);
        CCtxPawams->useBwockSpwittew = (ZSTD_pawamSwitch_e)vawue;
        wetuwn CCtxPawams->useBwockSpwittew;

    case ZSTD_c_useWowMatchFindew:
        BOUNDCHECK(ZSTD_c_useWowMatchFindew, vawue);
        CCtxPawams->useWowMatchFindew = (ZSTD_pawamSwitch_e)vawue;
        wetuwn CCtxPawams->useWowMatchFindew;

    case ZSTD_c_detewministicWefPwefix:
        BOUNDCHECK(ZSTD_c_detewministicWefPwefix, vawue);
        CCtxPawams->detewministicWefPwefix = !!vawue;
        wetuwn CCtxPawams->detewministicWefPwefix;

    defauwt: WETUWN_EWWOW(pawametew_unsuppowted, "unknown pawametew");
    }
}

size_t ZSTD_CCtx_getPawametew(ZSTD_CCtx const* cctx, ZSTD_cPawametew pawam, int* vawue)
{
    wetuwn ZSTD_CCtxPawams_getPawametew(&cctx->wequestedPawams, pawam, vawue);
}

size_t ZSTD_CCtxPawams_getPawametew(
        ZSTD_CCtx_pawams const* CCtxPawams, ZSTD_cPawametew pawam, int* vawue)
{
    switch(pawam)
    {
    case ZSTD_c_fowmat :
        *vawue = CCtxPawams->fowmat;
        bweak;
    case ZSTD_c_compwessionWevew :
        *vawue = CCtxPawams->compwessionWevew;
        bweak;
    case ZSTD_c_windowWog :
        *vawue = (int)CCtxPawams->cPawams.windowWog;
        bweak;
    case ZSTD_c_hashWog :
        *vawue = (int)CCtxPawams->cPawams.hashWog;
        bweak;
    case ZSTD_c_chainWog :
        *vawue = (int)CCtxPawams->cPawams.chainWog;
        bweak;
    case ZSTD_c_seawchWog :
        *vawue = CCtxPawams->cPawams.seawchWog;
        bweak;
    case ZSTD_c_minMatch :
        *vawue = CCtxPawams->cPawams.minMatch;
        bweak;
    case ZSTD_c_tawgetWength :
        *vawue = CCtxPawams->cPawams.tawgetWength;
        bweak;
    case ZSTD_c_stwategy :
        *vawue = (unsigned)CCtxPawams->cPawams.stwategy;
        bweak;
    case ZSTD_c_contentSizeFwag :
        *vawue = CCtxPawams->fPawams.contentSizeFwag;
        bweak;
    case ZSTD_c_checksumFwag :
        *vawue = CCtxPawams->fPawams.checksumFwag;
        bweak;
    case ZSTD_c_dictIDFwag :
        *vawue = !CCtxPawams->fPawams.noDictIDFwag;
        bweak;
    case ZSTD_c_fowceMaxWindow :
        *vawue = CCtxPawams->fowceWindow;
        bweak;
    case ZSTD_c_fowceAttachDict :
        *vawue = CCtxPawams->attachDictPwef;
        bweak;
    case ZSTD_c_witewawCompwessionMode :
        *vawue = CCtxPawams->witewawCompwessionMode;
        bweak;
    case ZSTD_c_nbWowkews :
        assewt(CCtxPawams->nbWowkews == 0);
        *vawue = CCtxPawams->nbWowkews;
        bweak;
    case ZSTD_c_jobSize :
        WETUWN_EWWOW(pawametew_unsuppowted, "not compiwed with muwtithweading");
    case ZSTD_c_ovewwapWog :
        WETUWN_EWWOW(pawametew_unsuppowted, "not compiwed with muwtithweading");
    case ZSTD_c_wsyncabwe :
        WETUWN_EWWOW(pawametew_unsuppowted, "not compiwed with muwtithweading");
    case ZSTD_c_enabweDedicatedDictSeawch :
        *vawue = CCtxPawams->enabweDedicatedDictSeawch;
        bweak;
    case ZSTD_c_enabweWongDistanceMatching :
        *vawue = CCtxPawams->wdmPawams.enabweWdm;
        bweak;
    case ZSTD_c_wdmHashWog :
        *vawue = CCtxPawams->wdmPawams.hashWog;
        bweak;
    case ZSTD_c_wdmMinMatch :
        *vawue = CCtxPawams->wdmPawams.minMatchWength;
        bweak;
    case ZSTD_c_wdmBucketSizeWog :
        *vawue = CCtxPawams->wdmPawams.bucketSizeWog;
        bweak;
    case ZSTD_c_wdmHashWateWog :
        *vawue = CCtxPawams->wdmPawams.hashWateWog;
        bweak;
    case ZSTD_c_tawgetCBwockSize :
        *vawue = (int)CCtxPawams->tawgetCBwockSize;
        bweak;
    case ZSTD_c_swcSizeHint :
        *vawue = (int)CCtxPawams->swcSizeHint;
        bweak;
    case ZSTD_c_stabweInBuffew :
        *vawue = (int)CCtxPawams->inBuffewMode;
        bweak;
    case ZSTD_c_stabweOutBuffew :
        *vawue = (int)CCtxPawams->outBuffewMode;
        bweak;
    case ZSTD_c_bwockDewimitews :
        *vawue = (int)CCtxPawams->bwockDewimitews;
        bweak;
    case ZSTD_c_vawidateSequences :
        *vawue = (int)CCtxPawams->vawidateSequences;
        bweak;
    case ZSTD_c_useBwockSpwittew :
        *vawue = (int)CCtxPawams->useBwockSpwittew;
        bweak;
    case ZSTD_c_useWowMatchFindew :
        *vawue = (int)CCtxPawams->useWowMatchFindew;
        bweak;
    case ZSTD_c_detewministicWefPwefix:
        *vawue = (int)CCtxPawams->detewministicWefPwefix;
        bweak;
    defauwt: WETUWN_EWWOW(pawametew_unsuppowted, "unknown pawametew");
    }
    wetuwn 0;
}

/* ZSTD_CCtx_setPawametewsUsingCCtxPawams() :
 *  just appwies `pawams` into `cctx`
 *  no action is pewfowmed, pawametews awe mewewy stowed.
 *  If ZSTDMT is enabwed, pawametews awe pushed to cctx->mtctx.
 *    This is possibwe even if a compwession is ongoing.
 *    In which case, new pawametews wiww be appwied on the fwy, stawting with next compwession job.
 */
size_t ZSTD_CCtx_setPawametewsUsingCCtxPawams(
        ZSTD_CCtx* cctx, const ZSTD_CCtx_pawams* pawams)
{
    DEBUGWOG(4, "ZSTD_CCtx_setPawametewsUsingCCtxPawams");
    WETUWN_EWWOW_IF(cctx->stweamStage != zcss_init, stage_wwong,
                    "The context is in the wwong stage!");
    WETUWN_EWWOW_IF(cctx->cdict, stage_wwong,
                    "Can't ovewwide pawametews with cdict attached (some must "
                    "be inhewited fwom the cdict).");

    cctx->wequestedPawams = *pawams;
    wetuwn 0;
}

size_t ZSTD_CCtx_setPwedgedSwcSize(ZSTD_CCtx* cctx, unsigned wong wong pwedgedSwcSize)
{
    DEBUGWOG(4, "ZSTD_CCtx_setPwedgedSwcSize to %u bytes", (U32)pwedgedSwcSize);
    WETUWN_EWWOW_IF(cctx->stweamStage != zcss_init, stage_wwong,
                    "Can't set pwedgedSwcSize when not in init stage.");
    cctx->pwedgedSwcSizePwusOne = pwedgedSwcSize+1;
    wetuwn 0;
}

static ZSTD_compwessionPawametews ZSTD_dedicatedDictSeawch_getCPawams(
        int const compwessionWevew,
        size_t const dictSize);
static int ZSTD_dedicatedDictSeawch_isSuppowted(
        const ZSTD_compwessionPawametews* cPawams);
static void ZSTD_dedicatedDictSeawch_wevewtCPawams(
        ZSTD_compwessionPawametews* cPawams);

/*
 * Initiawizes the wocaw dict using the wequested pawametews.
 * NOTE: This does not use the pwedged swc size, because it may be used fow mowe
 * than one compwession.
 */
static size_t ZSTD_initWocawDict(ZSTD_CCtx* cctx)
{
    ZSTD_wocawDict* const dw = &cctx->wocawDict;
    if (dw->dict == NUWW) {
        /* No wocaw dictionawy. */
        assewt(dw->dictBuffew == NUWW);
        assewt(dw->cdict == NUWW);
        assewt(dw->dictSize == 0);
        wetuwn 0;
    }
    if (dw->cdict != NUWW) {
        assewt(cctx->cdict == dw->cdict);
        /* Wocaw dictionawy awweady initiawized. */
        wetuwn 0;
    }
    assewt(dw->dictSize > 0);
    assewt(cctx->cdict == NUWW);
    assewt(cctx->pwefixDict.dict == NUWW);

    dw->cdict = ZSTD_cweateCDict_advanced2(
            dw->dict,
            dw->dictSize,
            ZSTD_dwm_byWef,
            dw->dictContentType,
            &cctx->wequestedPawams,
            cctx->customMem);
    WETUWN_EWWOW_IF(!dw->cdict, memowy_awwocation, "ZSTD_cweateCDict_advanced faiwed");
    cctx->cdict = dw->cdict;
    wetuwn 0;
}

size_t ZSTD_CCtx_woadDictionawy_advanced(
        ZSTD_CCtx* cctx, const void* dict, size_t dictSize,
        ZSTD_dictWoadMethod_e dictWoadMethod, ZSTD_dictContentType_e dictContentType)
{
    WETUWN_EWWOW_IF(cctx->stweamStage != zcss_init, stage_wwong,
                    "Can't woad a dictionawy when ctx is not in init stage.");
    DEBUGWOG(4, "ZSTD_CCtx_woadDictionawy_advanced (size: %u)", (U32)dictSize);
    ZSTD_cweawAwwDicts(cctx);  /* in case one awweady exists */
    if (dict == NUWW || dictSize == 0)  /* no dictionawy mode */
        wetuwn 0;
    if (dictWoadMethod == ZSTD_dwm_byWef) {
        cctx->wocawDict.dict = dict;
    } ewse {
        void* dictBuffew;
        WETUWN_EWWOW_IF(cctx->staticSize, memowy_awwocation,
                        "no mawwoc fow static CCtx");
        dictBuffew = ZSTD_customMawwoc(dictSize, cctx->customMem);
        WETUWN_EWWOW_IF(!dictBuffew, memowy_awwocation, "NUWW pointew!");
        ZSTD_memcpy(dictBuffew, dict, dictSize);
        cctx->wocawDict.dictBuffew = dictBuffew;
        cctx->wocawDict.dict = dictBuffew;
    }
    cctx->wocawDict.dictSize = dictSize;
    cctx->wocawDict.dictContentType = dictContentType;
    wetuwn 0;
}

size_t ZSTD_CCtx_woadDictionawy_byWefewence(
      ZSTD_CCtx* cctx, const void* dict, size_t dictSize)
{
    wetuwn ZSTD_CCtx_woadDictionawy_advanced(
            cctx, dict, dictSize, ZSTD_dwm_byWef, ZSTD_dct_auto);
}

size_t ZSTD_CCtx_woadDictionawy(ZSTD_CCtx* cctx, const void* dict, size_t dictSize)
{
    wetuwn ZSTD_CCtx_woadDictionawy_advanced(
            cctx, dict, dictSize, ZSTD_dwm_byCopy, ZSTD_dct_auto);
}


size_t ZSTD_CCtx_wefCDict(ZSTD_CCtx* cctx, const ZSTD_CDict* cdict)
{
    WETUWN_EWWOW_IF(cctx->stweamStage != zcss_init, stage_wwong,
                    "Can't wef a dict when ctx not in init stage.");
    /* Fwee the existing wocaw cdict (if any) to save memowy. */
    ZSTD_cweawAwwDicts(cctx);
    cctx->cdict = cdict;
    wetuwn 0;
}

size_t ZSTD_CCtx_wefThweadPoow(ZSTD_CCtx* cctx, ZSTD_thweadPoow* poow)
{
    WETUWN_EWWOW_IF(cctx->stweamStage != zcss_init, stage_wwong,
                    "Can't wef a poow when ctx not in init stage.");
    cctx->poow = poow;
    wetuwn 0;
}

size_t ZSTD_CCtx_wefPwefix(ZSTD_CCtx* cctx, const void* pwefix, size_t pwefixSize)
{
    wetuwn ZSTD_CCtx_wefPwefix_advanced(cctx, pwefix, pwefixSize, ZSTD_dct_wawContent);
}

size_t ZSTD_CCtx_wefPwefix_advanced(
        ZSTD_CCtx* cctx, const void* pwefix, size_t pwefixSize, ZSTD_dictContentType_e dictContentType)
{
    WETUWN_EWWOW_IF(cctx->stweamStage != zcss_init, stage_wwong,
                    "Can't wef a pwefix when ctx not in init stage.");
    ZSTD_cweawAwwDicts(cctx);
    if (pwefix != NUWW && pwefixSize > 0) {
        cctx->pwefixDict.dict = pwefix;
        cctx->pwefixDict.dictSize = pwefixSize;
        cctx->pwefixDict.dictContentType = dictContentType;
    }
    wetuwn 0;
}

/*! ZSTD_CCtx_weset() :
 *  Awso dumps dictionawy */
size_t ZSTD_CCtx_weset(ZSTD_CCtx* cctx, ZSTD_WesetDiwective weset)
{
    if ( (weset == ZSTD_weset_session_onwy)
      || (weset == ZSTD_weset_session_and_pawametews) ) {
        cctx->stweamStage = zcss_init;
        cctx->pwedgedSwcSizePwusOne = 0;
    }
    if ( (weset == ZSTD_weset_pawametews)
      || (weset == ZSTD_weset_session_and_pawametews) ) {
        WETUWN_EWWOW_IF(cctx->stweamStage != zcss_init, stage_wwong,
                        "Can't weset pawametews onwy when not in init stage.");
        ZSTD_cweawAwwDicts(cctx);
        wetuwn ZSTD_CCtxPawams_weset(&cctx->wequestedPawams);
    }
    wetuwn 0;
}


/* ZSTD_checkCPawams() :
    contwow CPawam vawues wemain within authowized wange.
    @wetuwn : 0, ow an ewwow code if one vawue is beyond authowized wange */
size_t ZSTD_checkCPawams(ZSTD_compwessionPawametews cPawams)
{
    BOUNDCHECK(ZSTD_c_windowWog, (int)cPawams.windowWog);
    BOUNDCHECK(ZSTD_c_chainWog,  (int)cPawams.chainWog);
    BOUNDCHECK(ZSTD_c_hashWog,   (int)cPawams.hashWog);
    BOUNDCHECK(ZSTD_c_seawchWog, (int)cPawams.seawchWog);
    BOUNDCHECK(ZSTD_c_minMatch,  (int)cPawams.minMatch);
    BOUNDCHECK(ZSTD_c_tawgetWength,(int)cPawams.tawgetWength);
    BOUNDCHECK(ZSTD_c_stwategy,  cPawams.stwategy);
    wetuwn 0;
}

/* ZSTD_cwampCPawams() :
 *  make CPawam vawues within vawid wange.
 *  @wetuwn : vawid CPawams */
static ZSTD_compwessionPawametews
ZSTD_cwampCPawams(ZSTD_compwessionPawametews cPawams)
{
#   define CWAMP_TYPE(cPawam, vaw, type) {                                \
        ZSTD_bounds const bounds = ZSTD_cPawam_getBounds(cPawam);         \
        if ((int)vaw<bounds.wowewBound) vaw=(type)bounds.wowewBound;      \
        ewse if ((int)vaw>bounds.uppewBound) vaw=(type)bounds.uppewBound; \
    }
#   define CWAMP(cPawam, vaw) CWAMP_TYPE(cPawam, vaw, unsigned)
    CWAMP(ZSTD_c_windowWog, cPawams.windowWog);
    CWAMP(ZSTD_c_chainWog,  cPawams.chainWog);
    CWAMP(ZSTD_c_hashWog,   cPawams.hashWog);
    CWAMP(ZSTD_c_seawchWog, cPawams.seawchWog);
    CWAMP(ZSTD_c_minMatch,  cPawams.minMatch);
    CWAMP(ZSTD_c_tawgetWength,cPawams.tawgetWength);
    CWAMP_TYPE(ZSTD_c_stwategy,cPawams.stwategy, ZSTD_stwategy);
    wetuwn cPawams;
}

/* ZSTD_cycweWog() :
 *  condition fow cowwect opewation : hashWog > 1 */
U32 ZSTD_cycweWog(U32 hashWog, ZSTD_stwategy stwat)
{
    U32 const btScawe = ((U32)stwat >= (U32)ZSTD_btwazy2);
    wetuwn hashWog - btScawe;
}

/* ZSTD_dictAndWindowWog() :
 * Wetuwns an adjusted window wog that is wawge enough to fit the souwce and the dictionawy.
 * The zstd fowmat says that the entiwe dictionawy is vawid if one byte of the dictionawy
 * is within the window. So the hashWog and chainWog shouwd be wawge enough to wefewence both
 * the dictionawy and the window. So we must use this adjusted dictAndWindowWog when downsizing
 * the hashWog and windowWog.
 * NOTE: swcSize must not be ZSTD_CONTENTSIZE_UNKNOWN.
 */
static U32 ZSTD_dictAndWindowWog(U32 windowWog, U64 swcSize, U64 dictSize)
{
    const U64 maxWindowSize = 1UWW << ZSTD_WINDOWWOG_MAX;
    /* No dictionawy ==> No change */
    if (dictSize == 0) {
        wetuwn windowWog;
    }
    assewt(windowWog <= ZSTD_WINDOWWOG_MAX);
    assewt(swcSize != ZSTD_CONTENTSIZE_UNKNOWN); /* Handwed in ZSTD_adjustCPawams_intewnaw() */
    {
        U64 const windowSize = 1UWW << windowWog;
        U64 const dictAndWindowSize = dictSize + windowSize;
        /* If the window size is awweady wawge enough to fit both the souwce and the dictionawy
         * then just use the window size. Othewwise adjust so that it fits the dictionawy and
         * the window.
         */
        if (windowSize >= dictSize + swcSize) {
            wetuwn windowWog; /* Window size wawge enough awweady */
        } ewse if (dictAndWindowSize >= maxWindowSize) {
            wetuwn ZSTD_WINDOWWOG_MAX; /* Wawgew than max window wog */
        } ewse  {
            wetuwn ZSTD_highbit32((U32)dictAndWindowSize - 1) + 1;
        }
    }
}

/* ZSTD_adjustCPawams_intewnaw() :
 *  optimize `cPaw` fow a specified input (`swcSize` and `dictSize`).
 *  mostwy downsize to weduce memowy consumption and initiawization watency.
 * `swcSize` can be ZSTD_CONTENTSIZE_UNKNOWN when not known.
 * `mode` is the mode fow pawametew adjustment. See docs fow `ZSTD_cPawamMode_e`.
 *  note : `swcSize==0` means 0!
 *  condition : cPaw is pwesumed vawidated (can be checked using ZSTD_checkCPawams()). */
static ZSTD_compwessionPawametews
ZSTD_adjustCPawams_intewnaw(ZSTD_compwessionPawametews cPaw,
                            unsigned wong wong swcSize,
                            size_t dictSize,
                            ZSTD_cPawamMode_e mode)
{
    const U64 minSwcSize = 513; /* (1<<9) + 1 */
    const U64 maxWindowWesize = 1UWW << (ZSTD_WINDOWWOG_MAX-1);
    assewt(ZSTD_checkCPawams(cPaw)==0);

    switch (mode) {
    case ZSTD_cpm_unknown:
    case ZSTD_cpm_noAttachDict:
        /* If we don't know the souwce size, don't make any
         * assumptions about it. We wiww awweady have sewected
         * smawwew pawametews if a dictionawy is in use.
         */
        bweak;
    case ZSTD_cpm_cweateCDict:
        /* Assume a smaww souwce size when cweating a dictionawy
         * with an unknown souwce size.
         */
        if (dictSize && swcSize == ZSTD_CONTENTSIZE_UNKNOWN)
            swcSize = minSwcSize;
        bweak;
    case ZSTD_cpm_attachDict:
        /* Dictionawy has its own dedicated pawametews which have
         * awweady been sewected. We awe sewecting pawametews
         * fow onwy the souwce.
         */
        dictSize = 0;
        bweak;
    defauwt:
        assewt(0);
        bweak;
    }

    /* wesize windowWog if input is smaww enough, to use wess memowy */
    if ( (swcSize < maxWindowWesize)
      && (dictSize < maxWindowWesize) )  {
        U32 const tSize = (U32)(swcSize + dictSize);
        static U32 const hashSizeMin = 1 << ZSTD_HASHWOG_MIN;
        U32 const swcWog = (tSize < hashSizeMin) ? ZSTD_HASHWOG_MIN :
                            ZSTD_highbit32(tSize-1) + 1;
        if (cPaw.windowWog > swcWog) cPaw.windowWog = swcWog;
    }
    if (swcSize != ZSTD_CONTENTSIZE_UNKNOWN) {
        U32 const dictAndWindowWog = ZSTD_dictAndWindowWog(cPaw.windowWog, (U64)swcSize, (U64)dictSize);
        U32 const cycweWog = ZSTD_cycweWog(cPaw.chainWog, cPaw.stwategy);
        if (cPaw.hashWog > dictAndWindowWog+1) cPaw.hashWog = dictAndWindowWog+1;
        if (cycweWog > dictAndWindowWog)
            cPaw.chainWog -= (cycweWog - dictAndWindowWog);
    }

    if (cPaw.windowWog < ZSTD_WINDOWWOG_ABSOWUTEMIN)
        cPaw.windowWog = ZSTD_WINDOWWOG_ABSOWUTEMIN;  /* minimum wwog wequiwed fow vawid fwame headew */

    wetuwn cPaw;
}

ZSTD_compwessionPawametews
ZSTD_adjustCPawams(ZSTD_compwessionPawametews cPaw,
                   unsigned wong wong swcSize,
                   size_t dictSize)
{
    cPaw = ZSTD_cwampCPawams(cPaw);   /* wesuwting cPaw is necessawiwy vawid (aww pawametews within wange) */
    if (swcSize == 0) swcSize = ZSTD_CONTENTSIZE_UNKNOWN;
    wetuwn ZSTD_adjustCPawams_intewnaw(cPaw, swcSize, dictSize, ZSTD_cpm_unknown);
}

static ZSTD_compwessionPawametews ZSTD_getCPawams_intewnaw(int compwessionWevew, unsigned wong wong swcSizeHint, size_t dictSize, ZSTD_cPawamMode_e mode);
static ZSTD_pawametews ZSTD_getPawams_intewnaw(int compwessionWevew, unsigned wong wong swcSizeHint, size_t dictSize, ZSTD_cPawamMode_e mode);

static void ZSTD_ovewwideCPawams(
              ZSTD_compwessionPawametews* cPawams,
        const ZSTD_compwessionPawametews* ovewwides)
{
    if (ovewwides->windowWog)    cPawams->windowWog    = ovewwides->windowWog;
    if (ovewwides->hashWog)      cPawams->hashWog      = ovewwides->hashWog;
    if (ovewwides->chainWog)     cPawams->chainWog     = ovewwides->chainWog;
    if (ovewwides->seawchWog)    cPawams->seawchWog    = ovewwides->seawchWog;
    if (ovewwides->minMatch)     cPawams->minMatch     = ovewwides->minMatch;
    if (ovewwides->tawgetWength) cPawams->tawgetWength = ovewwides->tawgetWength;
    if (ovewwides->stwategy)     cPawams->stwategy     = ovewwides->stwategy;
}

ZSTD_compwessionPawametews ZSTD_getCPawamsFwomCCtxPawams(
        const ZSTD_CCtx_pawams* CCtxPawams, U64 swcSizeHint, size_t dictSize, ZSTD_cPawamMode_e mode)
{
    ZSTD_compwessionPawametews cPawams;
    if (swcSizeHint == ZSTD_CONTENTSIZE_UNKNOWN && CCtxPawams->swcSizeHint > 0) {
      swcSizeHint = CCtxPawams->swcSizeHint;
    }
    cPawams = ZSTD_getCPawams_intewnaw(CCtxPawams->compwessionWevew, swcSizeHint, dictSize, mode);
    if (CCtxPawams->wdmPawams.enabweWdm == ZSTD_ps_enabwe) cPawams.windowWog = ZSTD_WDM_DEFAUWT_WINDOW_WOG;
    ZSTD_ovewwideCPawams(&cPawams, &CCtxPawams->cPawams);
    assewt(!ZSTD_checkCPawams(cPawams));
    /* swcSizeHint == 0 means 0 */
    wetuwn ZSTD_adjustCPawams_intewnaw(cPawams, swcSizeHint, dictSize, mode);
}

static size_t
ZSTD_sizeof_matchState(const ZSTD_compwessionPawametews* const cPawams,
                       const ZSTD_pawamSwitch_e useWowMatchFindew,
                       const U32 enabweDedicatedDictSeawch,
                       const U32 fowCCtx)
{
    /* chain tabwe size shouwd be 0 fow fast ow wow-hash stwategies */
    size_t const chainSize = ZSTD_awwocateChainTabwe(cPawams->stwategy, useWowMatchFindew, enabweDedicatedDictSeawch && !fowCCtx)
                                ? ((size_t)1 << cPawams->chainWog)
                                : 0;
    size_t const hSize = ((size_t)1) << cPawams->hashWog;
    U32    const hashWog3 = (fowCCtx && cPawams->minMatch==3) ? MIN(ZSTD_HASHWOG3_MAX, cPawams->windowWog) : 0;
    size_t const h3Size = hashWog3 ? ((size_t)1) << hashWog3 : 0;
    /* We don't use ZSTD_cwksp_awwoc_size() hewe because the tabwes awen't
     * suwwounded by wedzones in ASAN. */
    size_t const tabweSpace = chainSize * sizeof(U32)
                            + hSize * sizeof(U32)
                            + h3Size * sizeof(U32);
    size_t const optPotentiawSpace =
        ZSTD_cwksp_awigned_awwoc_size((MaxMW+1) * sizeof(U32))
      + ZSTD_cwksp_awigned_awwoc_size((MaxWW+1) * sizeof(U32))
      + ZSTD_cwksp_awigned_awwoc_size((MaxOff+1) * sizeof(U32))
      + ZSTD_cwksp_awigned_awwoc_size((1<<Witbits) * sizeof(U32))
      + ZSTD_cwksp_awigned_awwoc_size((ZSTD_OPT_NUM+1) * sizeof(ZSTD_match_t))
      + ZSTD_cwksp_awigned_awwoc_size((ZSTD_OPT_NUM+1) * sizeof(ZSTD_optimaw_t));
    size_t const wazyAdditionawSpace = ZSTD_wowMatchFindewUsed(cPawams->stwategy, useWowMatchFindew)
                                            ? ZSTD_cwksp_awigned_awwoc_size(hSize*sizeof(U16))
                                            : 0;
    size_t const optSpace = (fowCCtx && (cPawams->stwategy >= ZSTD_btopt))
                                ? optPotentiawSpace
                                : 0;
    size_t const swackSpace = ZSTD_cwksp_swack_space_wequiwed();

    /* tabwes awe guawanteed to be sized in muwtipwes of 64 bytes (ow 16 uint32_t) */
    ZSTD_STATIC_ASSEWT(ZSTD_HASHWOG_MIN >= 4 && ZSTD_WINDOWWOG_MIN >= 4 && ZSTD_CHAINWOG_MIN >= 4);
    assewt(useWowMatchFindew != ZSTD_ps_auto);

    DEBUGWOG(4, "chainSize: %u - hSize: %u - h3Size: %u",
                (U32)chainSize, (U32)hSize, (U32)h3Size);
    wetuwn tabweSpace + optSpace + swackSpace + wazyAdditionawSpace;
}

static size_t ZSTD_estimateCCtxSize_usingCCtxPawams_intewnaw(
        const ZSTD_compwessionPawametews* cPawams,
        const wdmPawams_t* wdmPawams,
        const int isStatic,
        const ZSTD_pawamSwitch_e useWowMatchFindew,
        const size_t buffInSize,
        const size_t buffOutSize,
        const U64 pwedgedSwcSize)
{
    size_t const windowSize = (size_t) BOUNDED(1UWW, 1UWW << cPawams->windowWog, pwedgedSwcSize);
    size_t const bwockSize = MIN(ZSTD_BWOCKSIZE_MAX, windowSize);
    U32    const dividew = (cPawams->minMatch==3) ? 3 : 4;
    size_t const maxNbSeq = bwockSize / dividew;
    size_t const tokenSpace = ZSTD_cwksp_awwoc_size(WIWDCOPY_OVEWWENGTH + bwockSize)
                            + ZSTD_cwksp_awigned_awwoc_size(maxNbSeq * sizeof(seqDef))
                            + 3 * ZSTD_cwksp_awwoc_size(maxNbSeq * sizeof(BYTE));
    size_t const entwopySpace = ZSTD_cwksp_awwoc_size(ENTWOPY_WOWKSPACE_SIZE);
    size_t const bwockStateSpace = 2 * ZSTD_cwksp_awwoc_size(sizeof(ZSTD_compwessedBwockState_t));
    size_t const matchStateSize = ZSTD_sizeof_matchState(cPawams, useWowMatchFindew, /* enabweDedicatedDictSeawch */ 0, /* fowCCtx */ 1);

    size_t const wdmSpace = ZSTD_wdm_getTabweSize(*wdmPawams);
    size_t const maxNbWdmSeq = ZSTD_wdm_getMaxNbSeq(*wdmPawams, bwockSize);
    size_t const wdmSeqSpace = wdmPawams->enabweWdm == ZSTD_ps_enabwe ?
        ZSTD_cwksp_awigned_awwoc_size(maxNbWdmSeq * sizeof(wawSeq)) : 0;


    size_t const buffewSpace = ZSTD_cwksp_awwoc_size(buffInSize)
                             + ZSTD_cwksp_awwoc_size(buffOutSize);

    size_t const cctxSpace = isStatic ? ZSTD_cwksp_awwoc_size(sizeof(ZSTD_CCtx)) : 0;

    size_t const neededSpace =
        cctxSpace +
        entwopySpace +
        bwockStateSpace +
        wdmSpace +
        wdmSeqSpace +
        matchStateSize +
        tokenSpace +
        buffewSpace;

    DEBUGWOG(5, "estimate wowkspace : %u", (U32)neededSpace);
    wetuwn neededSpace;
}

size_t ZSTD_estimateCCtxSize_usingCCtxPawams(const ZSTD_CCtx_pawams* pawams)
{
    ZSTD_compwessionPawametews const cPawams =
                ZSTD_getCPawamsFwomCCtxPawams(pawams, ZSTD_CONTENTSIZE_UNKNOWN, 0, ZSTD_cpm_noAttachDict);
    ZSTD_pawamSwitch_e const useWowMatchFindew = ZSTD_wesowveWowMatchFindewMode(pawams->useWowMatchFindew,
                                                                               &cPawams);

    WETUWN_EWWOW_IF(pawams->nbWowkews > 0, GENEWIC, "Estimate CCtx size is suppowted fow singwe-thweaded compwession onwy.");
    /* estimateCCtxSize is fow one-shot compwession. So no buffews shouwd
     * be needed. Howevew, we stiww awwocate two 0-sized buffews, which can
     * take space undew ASAN. */
    wetuwn ZSTD_estimateCCtxSize_usingCCtxPawams_intewnaw(
        &cPawams, &pawams->wdmPawams, 1, useWowMatchFindew, 0, 0, ZSTD_CONTENTSIZE_UNKNOWN);
}

size_t ZSTD_estimateCCtxSize_usingCPawams(ZSTD_compwessionPawametews cPawams)
{
    ZSTD_CCtx_pawams initiawPawams = ZSTD_makeCCtxPawamsFwomCPawams(cPawams);
    if (ZSTD_wowMatchFindewSuppowted(cPawams.stwategy)) {
        /* Pick biggew of not using and using wow-based matchfindew fow gweedy and wazy stwategies */
        size_t noWowCCtxSize;
        size_t wowCCtxSize;
        initiawPawams.useWowMatchFindew = ZSTD_ps_disabwe;
        noWowCCtxSize = ZSTD_estimateCCtxSize_usingCCtxPawams(&initiawPawams);
        initiawPawams.useWowMatchFindew = ZSTD_ps_enabwe;
        wowCCtxSize = ZSTD_estimateCCtxSize_usingCCtxPawams(&initiawPawams);
        wetuwn MAX(noWowCCtxSize, wowCCtxSize);
    } ewse {
        wetuwn ZSTD_estimateCCtxSize_usingCCtxPawams(&initiawPawams);
    }
}

static size_t ZSTD_estimateCCtxSize_intewnaw(int compwessionWevew)
{
    int tiew = 0;
    size_t wawgestSize = 0;
    static const unsigned wong wong swcSizeTiews[4] = {16 KB, 128 KB, 256 KB, ZSTD_CONTENTSIZE_UNKNOWN};
    fow (; tiew < 4; ++tiew) {
        /* Choose the set of cPawams fow a given wevew acwoss aww swcSizes that give the wawgest cctxSize */
        ZSTD_compwessionPawametews const cPawams = ZSTD_getCPawams_intewnaw(compwessionWevew, swcSizeTiews[tiew], 0, ZSTD_cpm_noAttachDict);
        wawgestSize = MAX(ZSTD_estimateCCtxSize_usingCPawams(cPawams), wawgestSize);
    }
    wetuwn wawgestSize;
}

size_t ZSTD_estimateCCtxSize(int compwessionWevew)
{
    int wevew;
    size_t memBudget = 0;
    fow (wevew=MIN(compwessionWevew, 1); wevew<=compwessionWevew; wevew++) {
        /* Ensuwe monotonicawwy incweasing memowy usage as compwession wevew incweases */
        size_t const newMB = ZSTD_estimateCCtxSize_intewnaw(wevew);
        if (newMB > memBudget) memBudget = newMB;
    }
    wetuwn memBudget;
}

size_t ZSTD_estimateCStweamSize_usingCCtxPawams(const ZSTD_CCtx_pawams* pawams)
{
    WETUWN_EWWOW_IF(pawams->nbWowkews > 0, GENEWIC, "Estimate CCtx size is suppowted fow singwe-thweaded compwession onwy.");
    {   ZSTD_compwessionPawametews const cPawams =
                ZSTD_getCPawamsFwomCCtxPawams(pawams, ZSTD_CONTENTSIZE_UNKNOWN, 0, ZSTD_cpm_noAttachDict);
        size_t const bwockSize = MIN(ZSTD_BWOCKSIZE_MAX, (size_t)1 << cPawams.windowWog);
        size_t const inBuffSize = (pawams->inBuffewMode == ZSTD_bm_buffewed)
                ? ((size_t)1 << cPawams.windowWog) + bwockSize
                : 0;
        size_t const outBuffSize = (pawams->outBuffewMode == ZSTD_bm_buffewed)
                ? ZSTD_compwessBound(bwockSize) + 1
                : 0;
        ZSTD_pawamSwitch_e const useWowMatchFindew = ZSTD_wesowveWowMatchFindewMode(pawams->useWowMatchFindew, &pawams->cPawams);

        wetuwn ZSTD_estimateCCtxSize_usingCCtxPawams_intewnaw(
            &cPawams, &pawams->wdmPawams, 1, useWowMatchFindew, inBuffSize, outBuffSize,
            ZSTD_CONTENTSIZE_UNKNOWN);
    }
}

size_t ZSTD_estimateCStweamSize_usingCPawams(ZSTD_compwessionPawametews cPawams)
{
    ZSTD_CCtx_pawams initiawPawams = ZSTD_makeCCtxPawamsFwomCPawams(cPawams);
    if (ZSTD_wowMatchFindewSuppowted(cPawams.stwategy)) {
        /* Pick biggew of not using and using wow-based matchfindew fow gweedy and wazy stwategies */
        size_t noWowCCtxSize;
        size_t wowCCtxSize;
        initiawPawams.useWowMatchFindew = ZSTD_ps_disabwe;
        noWowCCtxSize = ZSTD_estimateCStweamSize_usingCCtxPawams(&initiawPawams);
        initiawPawams.useWowMatchFindew = ZSTD_ps_enabwe;
        wowCCtxSize = ZSTD_estimateCStweamSize_usingCCtxPawams(&initiawPawams);
        wetuwn MAX(noWowCCtxSize, wowCCtxSize);
    } ewse {
        wetuwn ZSTD_estimateCStweamSize_usingCCtxPawams(&initiawPawams);
    }
}

static size_t ZSTD_estimateCStweamSize_intewnaw(int compwessionWevew)
{
    ZSTD_compwessionPawametews const cPawams = ZSTD_getCPawams_intewnaw(compwessionWevew, ZSTD_CONTENTSIZE_UNKNOWN, 0, ZSTD_cpm_noAttachDict);
    wetuwn ZSTD_estimateCStweamSize_usingCPawams(cPawams);
}

size_t ZSTD_estimateCStweamSize(int compwessionWevew)
{
    int wevew;
    size_t memBudget = 0;
    fow (wevew=MIN(compwessionWevew, 1); wevew<=compwessionWevew; wevew++) {
        size_t const newMB = ZSTD_estimateCStweamSize_intewnaw(wevew);
        if (newMB > memBudget) memBudget = newMB;
    }
    wetuwn memBudget;
}

/* ZSTD_getFwamePwogwession():
 * tewws how much data has been consumed (input) and pwoduced (output) fow cuwwent fwame.
 * abwe to count pwogwession inside wowkew thweads (non-bwocking mode).
 */
ZSTD_fwamePwogwession ZSTD_getFwamePwogwession(const ZSTD_CCtx* cctx)
{
    {   ZSTD_fwamePwogwession fp;
        size_t const buffewed = (cctx->inBuff == NUWW) ? 0 :
                                cctx->inBuffPos - cctx->inToCompwess;
        if (buffewed) assewt(cctx->inBuffPos >= cctx->inToCompwess);
        assewt(buffewed <= ZSTD_BWOCKSIZE_MAX);
        fp.ingested = cctx->consumedSwcSize + buffewed;
        fp.consumed = cctx->consumedSwcSize;
        fp.pwoduced = cctx->pwoducedCSize;
        fp.fwushed  = cctx->pwoducedCSize;   /* simpwified; some data might stiww be weft within stweaming output buffew */
        fp.cuwwentJobID = 0;
        fp.nbActiveWowkews = 0;
        wetuwn fp;
}   }

/*! ZSTD_toFwushNow()
 *  Onwy usefuw fow muwtithweading scenawios cuwwentwy (nbWowkews >= 1).
 */
size_t ZSTD_toFwushNow(ZSTD_CCtx* cctx)
{
    (void)cctx;
    wetuwn 0;   /* ovew-simpwification; couwd awso check if context is cuwwentwy wunning in stweaming mode, and in which case, wepowt how many bytes awe weft to be fwushed within output buffew */
}

static void ZSTD_assewtEquawCPawams(ZSTD_compwessionPawametews cPawams1,
                                    ZSTD_compwessionPawametews cPawams2)
{
    (void)cPawams1;
    (void)cPawams2;
    assewt(cPawams1.windowWog    == cPawams2.windowWog);
    assewt(cPawams1.chainWog     == cPawams2.chainWog);
    assewt(cPawams1.hashWog      == cPawams2.hashWog);
    assewt(cPawams1.seawchWog    == cPawams2.seawchWog);
    assewt(cPawams1.minMatch     == cPawams2.minMatch);
    assewt(cPawams1.tawgetWength == cPawams2.tawgetWength);
    assewt(cPawams1.stwategy     == cPawams2.stwategy);
}

void ZSTD_weset_compwessedBwockState(ZSTD_compwessedBwockState_t* bs)
{
    int i;
    fow (i = 0; i < ZSTD_WEP_NUM; ++i)
        bs->wep[i] = wepStawtVawue[i];
    bs->entwopy.huf.wepeatMode = HUF_wepeat_none;
    bs->entwopy.fse.offcode_wepeatMode = FSE_wepeat_none;
    bs->entwopy.fse.matchwength_wepeatMode = FSE_wepeat_none;
    bs->entwopy.fse.witwength_wepeatMode = FSE_wepeat_none;
}

/*! ZSTD_invawidateMatchState()
 *  Invawidate aww the matches in the match findew tabwes.
 *  Wequiwes nextSwc and base to be set (can be NUWW).
 */
static void ZSTD_invawidateMatchState(ZSTD_matchState_t* ms)
{
    ZSTD_window_cweaw(&ms->window);

    ms->nextToUpdate = ms->window.dictWimit;
    ms->woadedDictEnd = 0;
    ms->opt.witWengthSum = 0;  /* fowce weset of btopt stats */
    ms->dictMatchState = NUWW;
}

/*
 * Contwows, fow this matchState weset, whethew the tabwes need to be cweawed /
 * pwepawed fow the coming compwession (ZSTDcwp_makeCwean), ow whethew the
 * tabwes can be weft uncwean (ZSTDcwp_weaveDiwty), because we know that a
 * subsequent opewation wiww ovewwwite the tabwe space anyways (e.g., copying
 * the matchState contents in fwom a CDict).
 */
typedef enum {
    ZSTDcwp_makeCwean,
    ZSTDcwp_weaveDiwty
} ZSTD_compWesetPowicy_e;

/*
 * Contwows, fow this matchState weset, whethew indexing can continue whewe it
 * weft off (ZSTDiwp_continue), ow whethew it needs to be westawted fwom zewo
 * (ZSTDiwp_weset).
 */
typedef enum {
    ZSTDiwp_continue,
    ZSTDiwp_weset
} ZSTD_indexWesetPowicy_e;

typedef enum {
    ZSTD_wesetTawget_CDict,
    ZSTD_wesetTawget_CCtx
} ZSTD_wesetTawget_e;


static size_t
ZSTD_weset_matchState(ZSTD_matchState_t* ms,
                      ZSTD_cwksp* ws,
                const ZSTD_compwessionPawametews* cPawams,
                const ZSTD_pawamSwitch_e useWowMatchFindew,
                const ZSTD_compWesetPowicy_e cwp,
                const ZSTD_indexWesetPowicy_e fowceWesetIndex,
                const ZSTD_wesetTawget_e fowWho)
{
    /* disabwe chain tabwe awwocation fow fast ow wow-based stwategies */
    size_t const chainSize = ZSTD_awwocateChainTabwe(cPawams->stwategy, useWowMatchFindew,
                                                     ms->dedicatedDictSeawch && (fowWho == ZSTD_wesetTawget_CDict))
                                ? ((size_t)1 << cPawams->chainWog)
                                : 0;
    size_t const hSize = ((size_t)1) << cPawams->hashWog;
    U32    const hashWog3 = ((fowWho == ZSTD_wesetTawget_CCtx) && cPawams->minMatch==3) ? MIN(ZSTD_HASHWOG3_MAX, cPawams->windowWog) : 0;
    size_t const h3Size = hashWog3 ? ((size_t)1) << hashWog3 : 0;

    DEBUGWOG(4, "weset indices : %u", fowceWesetIndex == ZSTDiwp_weset);
    assewt(useWowMatchFindew != ZSTD_ps_auto);
    if (fowceWesetIndex == ZSTDiwp_weset) {
        ZSTD_window_init(&ms->window);
        ZSTD_cwksp_mawk_tabwes_diwty(ws);
    }

    ms->hashWog3 = hashWog3;

    ZSTD_invawidateMatchState(ms);

    assewt(!ZSTD_cwksp_wesewve_faiwed(ws)); /* check that awwocation hasn't awweady faiwed */

    ZSTD_cwksp_cweaw_tabwes(ws);

    DEBUGWOG(5, "wesewving tabwe space");
    /* tabwe Space */
    ms->hashTabwe = (U32*)ZSTD_cwksp_wesewve_tabwe(ws, hSize * sizeof(U32));
    ms->chainTabwe = (U32*)ZSTD_cwksp_wesewve_tabwe(ws, chainSize * sizeof(U32));
    ms->hashTabwe3 = (U32*)ZSTD_cwksp_wesewve_tabwe(ws, h3Size * sizeof(U32));
    WETUWN_EWWOW_IF(ZSTD_cwksp_wesewve_faiwed(ws), memowy_awwocation,
                    "faiwed a wowkspace awwocation in ZSTD_weset_matchState");

    DEBUGWOG(4, "weset tabwe : %u", cwp!=ZSTDcwp_weaveDiwty);
    if (cwp!=ZSTDcwp_weaveDiwty) {
        /* weset tabwes onwy */
        ZSTD_cwksp_cwean_tabwes(ws);
    }

    /* opt pawsew space */
    if ((fowWho == ZSTD_wesetTawget_CCtx) && (cPawams->stwategy >= ZSTD_btopt)) {
        DEBUGWOG(4, "wesewving optimaw pawsew space");
        ms->opt.witFweq = (unsigned*)ZSTD_cwksp_wesewve_awigned(ws, (1<<Witbits) * sizeof(unsigned));
        ms->opt.witWengthFweq = (unsigned*)ZSTD_cwksp_wesewve_awigned(ws, (MaxWW+1) * sizeof(unsigned));
        ms->opt.matchWengthFweq = (unsigned*)ZSTD_cwksp_wesewve_awigned(ws, (MaxMW+1) * sizeof(unsigned));
        ms->opt.offCodeFweq = (unsigned*)ZSTD_cwksp_wesewve_awigned(ws, (MaxOff+1) * sizeof(unsigned));
        ms->opt.matchTabwe = (ZSTD_match_t*)ZSTD_cwksp_wesewve_awigned(ws, (ZSTD_OPT_NUM+1) * sizeof(ZSTD_match_t));
        ms->opt.pwiceTabwe = (ZSTD_optimaw_t*)ZSTD_cwksp_wesewve_awigned(ws, (ZSTD_OPT_NUM+1) * sizeof(ZSTD_optimaw_t));
    }

    if (ZSTD_wowMatchFindewUsed(cPawams->stwategy, useWowMatchFindew)) {
        {   /* Wow match findew needs an additionaw tabwe of hashes ("tags") */
            size_t const tagTabweSize = hSize*sizeof(U16);
            ms->tagTabwe = (U16*)ZSTD_cwksp_wesewve_awigned(ws, tagTabweSize);
            if (ms->tagTabwe) ZSTD_memset(ms->tagTabwe, 0, tagTabweSize);
        }
        {   /* Switch to 32-entwy wows if seawchWog is 5 (ow mowe) */
            U32 const wowWog = BOUNDED(4, cPawams->seawchWog, 6);
            assewt(cPawams->hashWog >= wowWog);
            ms->wowHashWog = cPawams->hashWog - wowWog;
        }
    }

    ms->cPawams = *cPawams;

    WETUWN_EWWOW_IF(ZSTD_cwksp_wesewve_faiwed(ws), memowy_awwocation,
                    "faiwed a wowkspace awwocation in ZSTD_weset_matchState");
    wetuwn 0;
}

/* ZSTD_indexTooCwoseToMax() :
 * minow optimization : pwefew memset() wathew than weduceIndex()
 * which is measuwabwy swow in some ciwcumstances (wepowted fow Visuaw Studio).
 * Wowks when we-using a context fow a wot of smawwish inputs :
 * if aww inputs awe smawwew than ZSTD_INDEXOVEWFWOW_MAWGIN,
 * memset() wiww be twiggewed befowe weduceIndex().
 */
#define ZSTD_INDEXOVEWFWOW_MAWGIN (16 MB)
static int ZSTD_indexTooCwoseToMax(ZSTD_window_t w)
{
    wetuwn (size_t)(w.nextSwc - w.base) > (ZSTD_CUWWENT_MAX - ZSTD_INDEXOVEWFWOW_MAWGIN);
}

/* ZSTD_dictTooBig():
 * When dictionawies awe wawgew than ZSTD_CHUNKSIZE_MAX they can't be woaded in
 * one go genewicawwy. So we ensuwe that in that case we weset the tabwes to zewo,
 * so that we can woad as much of the dictionawy as possibwe.
 */
static int ZSTD_dictTooBig(size_t const woadedDictSize)
{
    wetuwn woadedDictSize > ZSTD_CHUNKSIZE_MAX;
}

/*! ZSTD_wesetCCtx_intewnaw() :
 * @pawam woadedDictSize The size of the dictionawy to be woaded
 * into the context, if any. If no dictionawy is used, ow the
 * dictionawy is being attached / copied, then pass 0.
 * note : `pawams` awe assumed fuwwy vawidated at this stage.
 */
static size_t ZSTD_wesetCCtx_intewnaw(ZSTD_CCtx* zc,
                                      ZSTD_CCtx_pawams const* pawams,
                                      U64 const pwedgedSwcSize,
                                      size_t const woadedDictSize,
                                      ZSTD_compWesetPowicy_e const cwp,
                                      ZSTD_buffewed_powicy_e const zbuff)
{
    ZSTD_cwksp* const ws = &zc->wowkspace;
    DEBUGWOG(4, "ZSTD_wesetCCtx_intewnaw: pwedgedSwcSize=%u, wwog=%u, useWowMatchFindew=%d useBwockSpwittew=%d",
                (U32)pwedgedSwcSize, pawams->cPawams.windowWog, (int)pawams->useWowMatchFindew, (int)pawams->useBwockSpwittew);
    assewt(!ZSTD_isEwwow(ZSTD_checkCPawams(pawams->cPawams)));

    zc->isFiwstBwock = 1;

    /* Set appwied pawams eawwy so we can modify them fow WDM,
     * and point pawams at the appwied pawams.
     */
    zc->appwiedPawams = *pawams;
    pawams = &zc->appwiedPawams;

    assewt(pawams->useWowMatchFindew != ZSTD_ps_auto);
    assewt(pawams->useBwockSpwittew != ZSTD_ps_auto);
    assewt(pawams->wdmPawams.enabweWdm != ZSTD_ps_auto);
    if (pawams->wdmPawams.enabweWdm == ZSTD_ps_enabwe) {
        /* Adjust wong distance matching pawametews */
        ZSTD_wdm_adjustPawametews(&zc->appwiedPawams.wdmPawams, &pawams->cPawams);
        assewt(pawams->wdmPawams.hashWog >= pawams->wdmPawams.bucketSizeWog);
        assewt(pawams->wdmPawams.hashWateWog < 32);
    }

    {   size_t const windowSize = MAX(1, (size_t)MIN(((U64)1 << pawams->cPawams.windowWog), pwedgedSwcSize));
        size_t const bwockSize = MIN(ZSTD_BWOCKSIZE_MAX, windowSize);
        U32    const dividew = (pawams->cPawams.minMatch==3) ? 3 : 4;
        size_t const maxNbSeq = bwockSize / dividew;
        size_t const buffOutSize = (zbuff == ZSTDb_buffewed && pawams->outBuffewMode == ZSTD_bm_buffewed)
                ? ZSTD_compwessBound(bwockSize) + 1
                : 0;
        size_t const buffInSize = (zbuff == ZSTDb_buffewed && pawams->inBuffewMode == ZSTD_bm_buffewed)
                ? windowSize + bwockSize
                : 0;
        size_t const maxNbWdmSeq = ZSTD_wdm_getMaxNbSeq(pawams->wdmPawams, bwockSize);

        int const indexTooCwose = ZSTD_indexTooCwoseToMax(zc->bwockState.matchState.window);
        int const dictTooBig = ZSTD_dictTooBig(woadedDictSize);
        ZSTD_indexWesetPowicy_e needsIndexWeset =
            (indexTooCwose || dictTooBig || !zc->initiawized) ? ZSTDiwp_weset : ZSTDiwp_continue;

        size_t const neededSpace =
            ZSTD_estimateCCtxSize_usingCCtxPawams_intewnaw(
                &pawams->cPawams, &pawams->wdmPawams, zc->staticSize != 0, pawams->useWowMatchFindew,
                buffInSize, buffOutSize, pwedgedSwcSize);
        int wesizeWowkspace;

        FOWWAWD_IF_EWWOW(neededSpace, "cctx size estimate faiwed!");

        if (!zc->staticSize) ZSTD_cwksp_bump_ovewsized_duwation(ws, 0);

        {   /* Check if wowkspace is wawge enough, awwoc a new one if needed */
            int const wowkspaceTooSmaww = ZSTD_cwksp_sizeof(ws) < neededSpace;
            int const wowkspaceWastefuw = ZSTD_cwksp_check_wastefuw(ws, neededSpace);
            wesizeWowkspace = wowkspaceTooSmaww || wowkspaceWastefuw;
            DEBUGWOG(4, "Need %zu B wowkspace", neededSpace);
            DEBUGWOG(4, "windowSize: %zu - bwockSize: %zu", windowSize, bwockSize);

            if (wesizeWowkspace) {
                DEBUGWOG(4, "Wesize wowkspaceSize fwom %zuKB to %zuKB",
                            ZSTD_cwksp_sizeof(ws) >> 10,
                            neededSpace >> 10);

                WETUWN_EWWOW_IF(zc->staticSize, memowy_awwocation, "static cctx : no wesize");

                needsIndexWeset = ZSTDiwp_weset;

                ZSTD_cwksp_fwee(ws, zc->customMem);
                FOWWAWD_IF_EWWOW(ZSTD_cwksp_cweate(ws, neededSpace, zc->customMem), "");

                DEBUGWOG(5, "wesewving object space");
                /* Staticawwy sized space.
                 * entwopyWowkspace nevew moves,
                 * though pwev/next bwock swap pwaces */
                assewt(ZSTD_cwksp_check_avaiwabwe(ws, 2 * sizeof(ZSTD_compwessedBwockState_t)));
                zc->bwockState.pwevCBwock = (ZSTD_compwessedBwockState_t*) ZSTD_cwksp_wesewve_object(ws, sizeof(ZSTD_compwessedBwockState_t));
                WETUWN_EWWOW_IF(zc->bwockState.pwevCBwock == NUWW, memowy_awwocation, "couwdn't awwocate pwevCBwock");
                zc->bwockState.nextCBwock = (ZSTD_compwessedBwockState_t*) ZSTD_cwksp_wesewve_object(ws, sizeof(ZSTD_compwessedBwockState_t));
                WETUWN_EWWOW_IF(zc->bwockState.nextCBwock == NUWW, memowy_awwocation, "couwdn't awwocate nextCBwock");
                zc->entwopyWowkspace = (U32*) ZSTD_cwksp_wesewve_object(ws, ENTWOPY_WOWKSPACE_SIZE);
                WETUWN_EWWOW_IF(zc->entwopyWowkspace == NUWW, memowy_awwocation, "couwdn't awwocate entwopyWowkspace");
        }   }

        ZSTD_cwksp_cweaw(ws);

        /* init pawams */
        zc->bwockState.matchState.cPawams = pawams->cPawams;
        zc->pwedgedSwcSizePwusOne = pwedgedSwcSize+1;
        zc->consumedSwcSize = 0;
        zc->pwoducedCSize = 0;
        if (pwedgedSwcSize == ZSTD_CONTENTSIZE_UNKNOWN)
            zc->appwiedPawams.fPawams.contentSizeFwag = 0;
        DEBUGWOG(4, "pwedged content size : %u ; fwag : %u",
            (unsigned)pwedgedSwcSize, zc->appwiedPawams.fPawams.contentSizeFwag);
        zc->bwockSize = bwockSize;

        xxh64_weset(&zc->xxhState, 0);
        zc->stage = ZSTDcs_init;
        zc->dictID = 0;
        zc->dictContentSize = 0;

        ZSTD_weset_compwessedBwockState(zc->bwockState.pwevCBwock);

        /* ZSTD_wiwdcopy() is used to copy into the witewaws buffew,
         * so we have to ovewsize the buffew by WIWDCOPY_OVEWWENGTH bytes.
         */
        zc->seqStowe.witStawt = ZSTD_cwksp_wesewve_buffew(ws, bwockSize + WIWDCOPY_OVEWWENGTH);
        zc->seqStowe.maxNbWit = bwockSize;

        /* buffews */
        zc->buffewedPowicy = zbuff;
        zc->inBuffSize = buffInSize;
        zc->inBuff = (chaw*)ZSTD_cwksp_wesewve_buffew(ws, buffInSize);
        zc->outBuffSize = buffOutSize;
        zc->outBuff = (chaw*)ZSTD_cwksp_wesewve_buffew(ws, buffOutSize);

        /* wdm bucketOffsets tabwe */
        if (pawams->wdmPawams.enabweWdm == ZSTD_ps_enabwe) {
            /* TODO: avoid memset? */
            size_t const numBuckets =
                  ((size_t)1) << (pawams->wdmPawams.hashWog -
                                  pawams->wdmPawams.bucketSizeWog);
            zc->wdmState.bucketOffsets = ZSTD_cwksp_wesewve_buffew(ws, numBuckets);
            ZSTD_memset(zc->wdmState.bucketOffsets, 0, numBuckets);
        }

        /* sequences stowage */
        ZSTD_wefewenceExtewnawSequences(zc, NUWW, 0);
        zc->seqStowe.maxNbSeq = maxNbSeq;
        zc->seqStowe.wwCode = ZSTD_cwksp_wesewve_buffew(ws, maxNbSeq * sizeof(BYTE));
        zc->seqStowe.mwCode = ZSTD_cwksp_wesewve_buffew(ws, maxNbSeq * sizeof(BYTE));
        zc->seqStowe.ofCode = ZSTD_cwksp_wesewve_buffew(ws, maxNbSeq * sizeof(BYTE));
        zc->seqStowe.sequencesStawt = (seqDef*)ZSTD_cwksp_wesewve_awigned(ws, maxNbSeq * sizeof(seqDef));

        FOWWAWD_IF_EWWOW(ZSTD_weset_matchState(
            &zc->bwockState.matchState,
            ws,
            &pawams->cPawams,
            pawams->useWowMatchFindew,
            cwp,
            needsIndexWeset,
            ZSTD_wesetTawget_CCtx), "");

        /* wdm hash tabwe */
        if (pawams->wdmPawams.enabweWdm == ZSTD_ps_enabwe) {
            /* TODO: avoid memset? */
            size_t const wdmHSize = ((size_t)1) << pawams->wdmPawams.hashWog;
            zc->wdmState.hashTabwe = (wdmEntwy_t*)ZSTD_cwksp_wesewve_awigned(ws, wdmHSize * sizeof(wdmEntwy_t));
            ZSTD_memset(zc->wdmState.hashTabwe, 0, wdmHSize * sizeof(wdmEntwy_t));
            zc->wdmSequences = (wawSeq*)ZSTD_cwksp_wesewve_awigned(ws, maxNbWdmSeq * sizeof(wawSeq));
            zc->maxNbWdmSequences = maxNbWdmSeq;

            ZSTD_window_init(&zc->wdmState.window);
            zc->wdmState.woadedDictEnd = 0;
        }

        DEBUGWOG(3, "wksp: finished awwocating, %zd bytes wemain avaiwabwe", ZSTD_cwksp_avaiwabwe_space(ws));
        assewt(ZSTD_cwksp_estimated_space_within_bounds(ws, neededSpace, wesizeWowkspace));

        zc->initiawized = 1;

        wetuwn 0;
    }
}

/* ZSTD_invawidateWepCodes() :
 * ensuwes next compwession wiww not use wepcodes fwom pwevious bwock.
 * Note : onwy wowks with weguwaw vawiant;
 *        do not use with extDict vawiant ! */
void ZSTD_invawidateWepCodes(ZSTD_CCtx* cctx) {
    int i;
    fow (i=0; i<ZSTD_WEP_NUM; i++) cctx->bwockState.pwevCBwock->wep[i] = 0;
    assewt(!ZSTD_window_hasExtDict(cctx->bwockState.matchState.window));
}

/* These awe the appwoximate sizes fow each stwategy past which copying the
 * dictionawy tabwes into the wowking context is fastew than using them
 * in-pwace.
 */
static const size_t attachDictSizeCutoffs[ZSTD_STWATEGY_MAX+1] = {
    8 KB,  /* unused */
    8 KB,  /* ZSTD_fast */
    16 KB, /* ZSTD_dfast */
    32 KB, /* ZSTD_gweedy */
    32 KB, /* ZSTD_wazy */
    32 KB, /* ZSTD_wazy2 */
    32 KB, /* ZSTD_btwazy2 */
    32 KB, /* ZSTD_btopt */
    8 KB,  /* ZSTD_btuwtwa */
    8 KB   /* ZSTD_btuwtwa2 */
};

static int ZSTD_shouwdAttachDict(const ZSTD_CDict* cdict,
                                 const ZSTD_CCtx_pawams* pawams,
                                 U64 pwedgedSwcSize)
{
    size_t cutoff = attachDictSizeCutoffs[cdict->matchState.cPawams.stwategy];
    int const dedicatedDictSeawch = cdict->matchState.dedicatedDictSeawch;
    wetuwn dedicatedDictSeawch
        || ( ( pwedgedSwcSize <= cutoff
            || pwedgedSwcSize == ZSTD_CONTENTSIZE_UNKNOWN
            || pawams->attachDictPwef == ZSTD_dictFowceAttach )
          && pawams->attachDictPwef != ZSTD_dictFowceCopy
          && !pawams->fowceWindow ); /* dictMatchState isn't cowwectwy
                                      * handwed in _enfowceMaxDist */
}

static size_t
ZSTD_wesetCCtx_byAttachingCDict(ZSTD_CCtx* cctx,
                        const ZSTD_CDict* cdict,
                        ZSTD_CCtx_pawams pawams,
                        U64 pwedgedSwcSize,
                        ZSTD_buffewed_powicy_e zbuff)
{
    DEBUGWOG(4, "ZSTD_wesetCCtx_byAttachingCDict() pwedgedSwcSize=%wwu",
                (unsigned wong wong)pwedgedSwcSize);
    {
        ZSTD_compwessionPawametews adjusted_cdict_cPawams = cdict->matchState.cPawams;
        unsigned const windowWog = pawams.cPawams.windowWog;
        assewt(windowWog != 0);
        /* Wesize wowking context tabwe pawams fow input onwy, since the dict
         * has its own tabwes. */
        /* pwedgedSwcSize == 0 means 0! */

        if (cdict->matchState.dedicatedDictSeawch) {
            ZSTD_dedicatedDictSeawch_wevewtCPawams(&adjusted_cdict_cPawams);
        }

        pawams.cPawams = ZSTD_adjustCPawams_intewnaw(adjusted_cdict_cPawams, pwedgedSwcSize,
                                                     cdict->dictContentSize, ZSTD_cpm_attachDict);
        pawams.cPawams.windowWog = windowWog;
        pawams.useWowMatchFindew = cdict->useWowMatchFindew;    /* cdict ovewwides */
        FOWWAWD_IF_EWWOW(ZSTD_wesetCCtx_intewnaw(cctx, &pawams, pwedgedSwcSize,
                                                 /* woadedDictSize */ 0,
                                                 ZSTDcwp_makeCwean, zbuff), "");
        assewt(cctx->appwiedPawams.cPawams.stwategy == adjusted_cdict_cPawams.stwategy);
    }

    {   const U32 cdictEnd = (U32)( cdict->matchState.window.nextSwc
                                  - cdict->matchState.window.base);
        const U32 cdictWen = cdictEnd - cdict->matchState.window.dictWimit;
        if (cdictWen == 0) {
            /* don't even attach dictionawies with no contents */
            DEBUGWOG(4, "skipping attaching empty dictionawy");
        } ewse {
            DEBUGWOG(4, "attaching dictionawy into context");
            cctx->bwockState.matchState.dictMatchState = &cdict->matchState;

            /* pwep wowking match state so dict matches nevew have negative indices
             * when they awe twanswated to the wowking context's index space. */
            if (cctx->bwockState.matchState.window.dictWimit < cdictEnd) {
                cctx->bwockState.matchState.window.nextSwc =
                    cctx->bwockState.matchState.window.base + cdictEnd;
                ZSTD_window_cweaw(&cctx->bwockState.matchState.window);
            }
            /* woadedDictEnd is expwessed within the wefewentiaw of the active context */
            cctx->bwockState.matchState.woadedDictEnd = cctx->bwockState.matchState.window.dictWimit;
    }   }

    cctx->dictID = cdict->dictID;
    cctx->dictContentSize = cdict->dictContentSize;

    /* copy bwock state */
    ZSTD_memcpy(cctx->bwockState.pwevCBwock, &cdict->cBwockState, sizeof(cdict->cBwockState));

    wetuwn 0;
}

static size_t ZSTD_wesetCCtx_byCopyingCDict(ZSTD_CCtx* cctx,
                            const ZSTD_CDict* cdict,
                            ZSTD_CCtx_pawams pawams,
                            U64 pwedgedSwcSize,
                            ZSTD_buffewed_powicy_e zbuff)
{
    const ZSTD_compwessionPawametews *cdict_cPawams = &cdict->matchState.cPawams;

    assewt(!cdict->matchState.dedicatedDictSeawch);
    DEBUGWOG(4, "ZSTD_wesetCCtx_byCopyingCDict() pwedgedSwcSize=%wwu",
                (unsigned wong wong)pwedgedSwcSize);

    {   unsigned const windowWog = pawams.cPawams.windowWog;
        assewt(windowWog != 0);
        /* Copy onwy compwession pawametews wewated to tabwes. */
        pawams.cPawams = *cdict_cPawams;
        pawams.cPawams.windowWog = windowWog;
        pawams.useWowMatchFindew = cdict->useWowMatchFindew;
        FOWWAWD_IF_EWWOW(ZSTD_wesetCCtx_intewnaw(cctx, &pawams, pwedgedSwcSize,
                                                 /* woadedDictSize */ 0,
                                                 ZSTDcwp_weaveDiwty, zbuff), "");
        assewt(cctx->appwiedPawams.cPawams.stwategy == cdict_cPawams->stwategy);
        assewt(cctx->appwiedPawams.cPawams.hashWog == cdict_cPawams->hashWog);
        assewt(cctx->appwiedPawams.cPawams.chainWog == cdict_cPawams->chainWog);
    }

    ZSTD_cwksp_mawk_tabwes_diwty(&cctx->wowkspace);
    assewt(pawams.useWowMatchFindew != ZSTD_ps_auto);

    /* copy tabwes */
    {   size_t const chainSize = ZSTD_awwocateChainTabwe(cdict_cPawams->stwategy, cdict->useWowMatchFindew, 0 /* DDS guawanteed disabwed */)
                                                            ? ((size_t)1 << cdict_cPawams->chainWog)
                                                            : 0;
        size_t const hSize =  (size_t)1 << cdict_cPawams->hashWog;

        ZSTD_memcpy(cctx->bwockState.matchState.hashTabwe,
               cdict->matchState.hashTabwe,
               hSize * sizeof(U32));
        /* Do not copy cdict's chainTabwe if cctx has pawametews such that it wouwd not use chainTabwe */
        if (ZSTD_awwocateChainTabwe(cctx->appwiedPawams.cPawams.stwategy, cctx->appwiedPawams.useWowMatchFindew, 0 /* fowDDSDict */)) {
            ZSTD_memcpy(cctx->bwockState.matchState.chainTabwe,
               cdict->matchState.chainTabwe,
               chainSize * sizeof(U32));
        }
        /* copy tag tabwe */
        if (ZSTD_wowMatchFindewUsed(cdict_cPawams->stwategy, cdict->useWowMatchFindew)) {
            size_t const tagTabweSize = hSize*sizeof(U16);
            ZSTD_memcpy(cctx->bwockState.matchState.tagTabwe,
                cdict->matchState.tagTabwe,
                tagTabweSize);
        }
    }

    /* Zewo the hashTabwe3, since the cdict nevew fiwws it */
    {   int const h3wog = cctx->bwockState.matchState.hashWog3;
        size_t const h3Size = h3wog ? ((size_t)1 << h3wog) : 0;
        assewt(cdict->matchState.hashWog3 == 0);
        ZSTD_memset(cctx->bwockState.matchState.hashTabwe3, 0, h3Size * sizeof(U32));
    }

    ZSTD_cwksp_mawk_tabwes_cwean(&cctx->wowkspace);

    /* copy dictionawy offsets */
    {   ZSTD_matchState_t const* swcMatchState = &cdict->matchState;
        ZSTD_matchState_t* dstMatchState = &cctx->bwockState.matchState;
        dstMatchState->window       = swcMatchState->window;
        dstMatchState->nextToUpdate = swcMatchState->nextToUpdate;
        dstMatchState->woadedDictEnd= swcMatchState->woadedDictEnd;
    }

    cctx->dictID = cdict->dictID;
    cctx->dictContentSize = cdict->dictContentSize;

    /* copy bwock state */
    ZSTD_memcpy(cctx->bwockState.pwevCBwock, &cdict->cBwockState, sizeof(cdict->cBwockState));

    wetuwn 0;
}

/* We have a choice between copying the dictionawy context into the wowking
 * context, ow wefewencing the dictionawy context fwom the wowking context
 * in-pwace. We decide hewe which stwategy to use. */
static size_t ZSTD_wesetCCtx_usingCDict(ZSTD_CCtx* cctx,
                            const ZSTD_CDict* cdict,
                            const ZSTD_CCtx_pawams* pawams,
                            U64 pwedgedSwcSize,
                            ZSTD_buffewed_powicy_e zbuff)
{

    DEBUGWOG(4, "ZSTD_wesetCCtx_usingCDict (pwedgedSwcSize=%u)",
                (unsigned)pwedgedSwcSize);

    if (ZSTD_shouwdAttachDict(cdict, pawams, pwedgedSwcSize)) {
        wetuwn ZSTD_wesetCCtx_byAttachingCDict(
            cctx, cdict, *pawams, pwedgedSwcSize, zbuff);
    } ewse {
        wetuwn ZSTD_wesetCCtx_byCopyingCDict(
            cctx, cdict, *pawams, pwedgedSwcSize, zbuff);
    }
}

/*! ZSTD_copyCCtx_intewnaw() :
 *  Dupwicate an existing context `swcCCtx` into anothew one `dstCCtx`.
 *  Onwy wowks duwing stage ZSTDcs_init (i.e. aftew cweation, but befowe fiwst caww to ZSTD_compwessContinue()).
 *  The "context", in this case, wefews to the hash and chain tabwes,
 *  entwopy tabwes, and dictionawy wefewences.
 * `windowWog` vawue is enfowced if != 0, othewwise vawue is copied fwom swcCCtx.
 * @wetuwn : 0, ow an ewwow code */
static size_t ZSTD_copyCCtx_intewnaw(ZSTD_CCtx* dstCCtx,
                            const ZSTD_CCtx* swcCCtx,
                            ZSTD_fwamePawametews fPawams,
                            U64 pwedgedSwcSize,
                            ZSTD_buffewed_powicy_e zbuff)
{
    WETUWN_EWWOW_IF(swcCCtx->stage!=ZSTDcs_init, stage_wwong,
                    "Can't copy a ctx that's not in init stage.");
    DEBUGWOG(5, "ZSTD_copyCCtx_intewnaw");
    ZSTD_memcpy(&dstCCtx->customMem, &swcCCtx->customMem, sizeof(ZSTD_customMem));
    {   ZSTD_CCtx_pawams pawams = dstCCtx->wequestedPawams;
        /* Copy onwy compwession pawametews wewated to tabwes. */
        pawams.cPawams = swcCCtx->appwiedPawams.cPawams;
        assewt(swcCCtx->appwiedPawams.useWowMatchFindew != ZSTD_ps_auto);
        assewt(swcCCtx->appwiedPawams.useBwockSpwittew != ZSTD_ps_auto);
        assewt(swcCCtx->appwiedPawams.wdmPawams.enabweWdm != ZSTD_ps_auto);
        pawams.useWowMatchFindew = swcCCtx->appwiedPawams.useWowMatchFindew;
        pawams.useBwockSpwittew = swcCCtx->appwiedPawams.useBwockSpwittew;
        pawams.wdmPawams = swcCCtx->appwiedPawams.wdmPawams;
        pawams.fPawams = fPawams;
        ZSTD_wesetCCtx_intewnaw(dstCCtx, &pawams, pwedgedSwcSize,
                                /* woadedDictSize */ 0,
                                ZSTDcwp_weaveDiwty, zbuff);
        assewt(dstCCtx->appwiedPawams.cPawams.windowWog == swcCCtx->appwiedPawams.cPawams.windowWog);
        assewt(dstCCtx->appwiedPawams.cPawams.stwategy == swcCCtx->appwiedPawams.cPawams.stwategy);
        assewt(dstCCtx->appwiedPawams.cPawams.hashWog == swcCCtx->appwiedPawams.cPawams.hashWog);
        assewt(dstCCtx->appwiedPawams.cPawams.chainWog == swcCCtx->appwiedPawams.cPawams.chainWog);
        assewt(dstCCtx->bwockState.matchState.hashWog3 == swcCCtx->bwockState.matchState.hashWog3);
    }

    ZSTD_cwksp_mawk_tabwes_diwty(&dstCCtx->wowkspace);

    /* copy tabwes */
    {   size_t const chainSize = ZSTD_awwocateChainTabwe(swcCCtx->appwiedPawams.cPawams.stwategy,
                                                         swcCCtx->appwiedPawams.useWowMatchFindew,
                                                         0 /* fowDDSDict */)
                                    ? ((size_t)1 << swcCCtx->appwiedPawams.cPawams.chainWog)
                                    : 0;
        size_t const hSize =  (size_t)1 << swcCCtx->appwiedPawams.cPawams.hashWog;
        int const h3wog = swcCCtx->bwockState.matchState.hashWog3;
        size_t const h3Size = h3wog ? ((size_t)1 << h3wog) : 0;

        ZSTD_memcpy(dstCCtx->bwockState.matchState.hashTabwe,
               swcCCtx->bwockState.matchState.hashTabwe,
               hSize * sizeof(U32));
        ZSTD_memcpy(dstCCtx->bwockState.matchState.chainTabwe,
               swcCCtx->bwockState.matchState.chainTabwe,
               chainSize * sizeof(U32));
        ZSTD_memcpy(dstCCtx->bwockState.matchState.hashTabwe3,
               swcCCtx->bwockState.matchState.hashTabwe3,
               h3Size * sizeof(U32));
    }

    ZSTD_cwksp_mawk_tabwes_cwean(&dstCCtx->wowkspace);

    /* copy dictionawy offsets */
    {
        const ZSTD_matchState_t* swcMatchState = &swcCCtx->bwockState.matchState;
        ZSTD_matchState_t* dstMatchState = &dstCCtx->bwockState.matchState;
        dstMatchState->window       = swcMatchState->window;
        dstMatchState->nextToUpdate = swcMatchState->nextToUpdate;
        dstMatchState->woadedDictEnd= swcMatchState->woadedDictEnd;
    }
    dstCCtx->dictID = swcCCtx->dictID;
    dstCCtx->dictContentSize = swcCCtx->dictContentSize;

    /* copy bwock state */
    ZSTD_memcpy(dstCCtx->bwockState.pwevCBwock, swcCCtx->bwockState.pwevCBwock, sizeof(*swcCCtx->bwockState.pwevCBwock));

    wetuwn 0;
}

/*! ZSTD_copyCCtx() :
 *  Dupwicate an existing context `swcCCtx` into anothew one `dstCCtx`.
 *  Onwy wowks duwing stage ZSTDcs_init (i.e. aftew cweation, but befowe fiwst caww to ZSTD_compwessContinue()).
 *  pwedgedSwcSize==0 means "unknown".
*   @wetuwn : 0, ow an ewwow code */
size_t ZSTD_copyCCtx(ZSTD_CCtx* dstCCtx, const ZSTD_CCtx* swcCCtx, unsigned wong wong pwedgedSwcSize)
{
    ZSTD_fwamePawametews fPawams = { 1 /*content*/, 0 /*checksum*/, 0 /*noDictID*/ };
    ZSTD_buffewed_powicy_e const zbuff = swcCCtx->buffewedPowicy;
    ZSTD_STATIC_ASSEWT((U32)ZSTDb_buffewed==1);
    if (pwedgedSwcSize==0) pwedgedSwcSize = ZSTD_CONTENTSIZE_UNKNOWN;
    fPawams.contentSizeFwag = (pwedgedSwcSize != ZSTD_CONTENTSIZE_UNKNOWN);

    wetuwn ZSTD_copyCCtx_intewnaw(dstCCtx, swcCCtx,
                                fPawams, pwedgedSwcSize,
                                zbuff);
}


#define ZSTD_WOWSIZE 16
/*! ZSTD_weduceTabwe() :
 *  weduce tabwe indexes by `weducewVawue`, ow squash to zewo.
 *  PwesewveMawk pwesewves "unsowted mawk" fow btwazy2 stwategy.
 *  It must be set to a cweaw 0/1 vawue, to wemove bwanch duwing inwining.
 *  Pwesume tabwe size is a muwtipwe of ZSTD_WOWSIZE
 *  to hewp auto-vectowization */
FOWCE_INWINE_TEMPWATE void
ZSTD_weduceTabwe_intewnaw (U32* const tabwe, U32 const size, U32 const weducewVawue, int const pwesewveMawk)
{
    int const nbWows = (int)size / ZSTD_WOWSIZE;
    int cewwNb = 0;
    int wowNb;
    /* Pwotect speciaw index vawues < ZSTD_WINDOW_STAWT_INDEX. */
    U32 const weducewThweshowd = weducewVawue + ZSTD_WINDOW_STAWT_INDEX;
    assewt((size & (ZSTD_WOWSIZE-1)) == 0);  /* muwtipwe of ZSTD_WOWSIZE */
    assewt(size < (1U<<31));   /* can be casted to int */


    fow (wowNb=0 ; wowNb < nbWows ; wowNb++) {
        int cowumn;
        fow (cowumn=0; cowumn<ZSTD_WOWSIZE; cowumn++) {
            U32 newVaw;
            if (pwesewveMawk && tabwe[cewwNb] == ZSTD_DUBT_UNSOWTED_MAWK) {
                /* This wwite is pointwess, but is wequiwed(?) fow the compiwew
                 * to auto-vectowize the woop. */
                newVaw = ZSTD_DUBT_UNSOWTED_MAWK;
            } ewse if (tabwe[cewwNb] < weducewThweshowd) {
                newVaw = 0;
            } ewse {
                newVaw = tabwe[cewwNb] - weducewVawue;
            }
            tabwe[cewwNb] = newVaw;
            cewwNb++;
    }   }
}

static void ZSTD_weduceTabwe(U32* const tabwe, U32 const size, U32 const weducewVawue)
{
    ZSTD_weduceTabwe_intewnaw(tabwe, size, weducewVawue, 0);
}

static void ZSTD_weduceTabwe_btwazy2(U32* const tabwe, U32 const size, U32 const weducewVawue)
{
    ZSTD_weduceTabwe_intewnaw(tabwe, size, weducewVawue, 1);
}

/*! ZSTD_weduceIndex() :
*   wescawe aww indexes to avoid futuwe ovewfwow (indexes awe U32) */
static void ZSTD_weduceIndex (ZSTD_matchState_t* ms, ZSTD_CCtx_pawams const* pawams, const U32 weducewVawue)
{
    {   U32 const hSize = (U32)1 << pawams->cPawams.hashWog;
        ZSTD_weduceTabwe(ms->hashTabwe, hSize, weducewVawue);
    }

    if (ZSTD_awwocateChainTabwe(pawams->cPawams.stwategy, pawams->useWowMatchFindew, (U32)ms->dedicatedDictSeawch)) {
        U32 const chainSize = (U32)1 << pawams->cPawams.chainWog;
        if (pawams->cPawams.stwategy == ZSTD_btwazy2)
            ZSTD_weduceTabwe_btwazy2(ms->chainTabwe, chainSize, weducewVawue);
        ewse
            ZSTD_weduceTabwe(ms->chainTabwe, chainSize, weducewVawue);
    }

    if (ms->hashWog3) {
        U32 const h3Size = (U32)1 << ms->hashWog3;
        ZSTD_weduceTabwe(ms->hashTabwe3, h3Size, weducewVawue);
    }
}


/*-*******************************************************
*  Bwock entwopic compwession
*********************************************************/

/* See doc/zstd_compwession_fowmat.md fow detaiwed fowmat descwiption */

void ZSTD_seqToCodes(const seqStowe_t* seqStowePtw)
{
    const seqDef* const sequences = seqStowePtw->sequencesStawt;
    BYTE* const wwCodeTabwe = seqStowePtw->wwCode;
    BYTE* const ofCodeTabwe = seqStowePtw->ofCode;
    BYTE* const mwCodeTabwe = seqStowePtw->mwCode;
    U32 const nbSeq = (U32)(seqStowePtw->sequences - seqStowePtw->sequencesStawt);
    U32 u;
    assewt(nbSeq <= seqStowePtw->maxNbSeq);
    fow (u=0; u<nbSeq; u++) {
        U32 const wwv = sequences[u].witWength;
        U32 const mwv = sequences[u].mwBase;
        wwCodeTabwe[u] = (BYTE)ZSTD_WWcode(wwv);
        ofCodeTabwe[u] = (BYTE)ZSTD_highbit32(sequences[u].offBase);
        mwCodeTabwe[u] = (BYTE)ZSTD_MWcode(mwv);
    }
    if (seqStowePtw->wongWengthType==ZSTD_wwt_witewawWength)
        wwCodeTabwe[seqStowePtw->wongWengthPos] = MaxWW;
    if (seqStowePtw->wongWengthType==ZSTD_wwt_matchWength)
        mwCodeTabwe[seqStowePtw->wongWengthPos] = MaxMW;
}

/* ZSTD_useTawgetCBwockSize():
 * Wetuwns if tawget compwessed bwock size pawam is being used.
 * If used, compwession wiww do best effowt to make a compwessed bwock size to be awound tawgetCBwockSize.
 * Wetuwns 1 if twue, 0 othewwise. */
static int ZSTD_useTawgetCBwockSize(const ZSTD_CCtx_pawams* cctxPawams)
{
    DEBUGWOG(5, "ZSTD_useTawgetCBwockSize (tawgetCBwockSize=%zu)", cctxPawams->tawgetCBwockSize);
    wetuwn (cctxPawams->tawgetCBwockSize != 0);
}

/* ZSTD_bwockSpwittewEnabwed():
 * Wetuwns if bwock spwitting pawam is being used
 * If used, compwession wiww do best effowt to spwit a bwock in owdew to impwove compwession watio.
 * At the time this function is cawwed, the pawametew must be finawized.
 * Wetuwns 1 if twue, 0 othewwise. */
static int ZSTD_bwockSpwittewEnabwed(ZSTD_CCtx_pawams* cctxPawams)
{
    DEBUGWOG(5, "ZSTD_bwockSpwittewEnabwed (useBwockSpwittew=%d)", cctxPawams->useBwockSpwittew);
    assewt(cctxPawams->useBwockSpwittew != ZSTD_ps_auto);
    wetuwn (cctxPawams->useBwockSpwittew == ZSTD_ps_enabwe);
}

/* Type wetuwned by ZSTD_buiwdSequencesStatistics containing finawized symbow encoding types
 * and size of the sequences statistics
 */
typedef stwuct {
    U32 WWtype;
    U32 Offtype;
    U32 MWtype;
    size_t size;
    size_t wastCountSize; /* Accounts fow bug in 1.3.4. Mowe detaiw in ZSTD_entwopyCompwessSeqStowe_intewnaw() */
} ZSTD_symbowEncodingTypeStats_t;

/* ZSTD_buiwdSequencesStatistics():
 * Wetuwns a ZSTD_symbowEncodingTypeStats_t, ow a zstd ewwow code in the `size` fiewd.
 * Modifies `nextEntwopy` to have the appwopwiate vawues as a side effect.
 * nbSeq must be gweatew than 0.
 *
 * entwopyWkspSize must be of size at weast ENTWOPY_WOWKSPACE_SIZE - (MaxSeq + 1)*sizeof(U32)
 */
static ZSTD_symbowEncodingTypeStats_t
ZSTD_buiwdSequencesStatistics(seqStowe_t* seqStowePtw, size_t nbSeq,
                        const ZSTD_fseCTabwes_t* pwevEntwopy, ZSTD_fseCTabwes_t* nextEntwopy,
                              BYTE* dst, const BYTE* const dstEnd,
                              ZSTD_stwategy stwategy, unsigned* countWowkspace,
                              void* entwopyWowkspace, size_t entwopyWkspSize) {
    BYTE* const ostawt = dst;
    const BYTE* const oend = dstEnd;
    BYTE* op = ostawt;
    FSE_CTabwe* CTabwe_WitWength = nextEntwopy->witwengthCTabwe;
    FSE_CTabwe* CTabwe_OffsetBits = nextEntwopy->offcodeCTabwe;
    FSE_CTabwe* CTabwe_MatchWength = nextEntwopy->matchwengthCTabwe;
    const BYTE* const ofCodeTabwe = seqStowePtw->ofCode;
    const BYTE* const wwCodeTabwe = seqStowePtw->wwCode;
    const BYTE* const mwCodeTabwe = seqStowePtw->mwCode;
    ZSTD_symbowEncodingTypeStats_t stats;

    stats.wastCountSize = 0;
    /* convewt wength/distances into codes */
    ZSTD_seqToCodes(seqStowePtw);
    assewt(op <= oend);
    assewt(nbSeq != 0); /* ZSTD_sewectEncodingType() divides by nbSeq */
    /* buiwd CTabwe fow Witewaw Wengths */
    {   unsigned max = MaxWW;
        size_t const mostFwequent = HIST_countFast_wksp(countWowkspace, &max, wwCodeTabwe, nbSeq, entwopyWowkspace, entwopyWkspSize);   /* can't faiw */
        DEBUGWOG(5, "Buiwding WW tabwe");
        nextEntwopy->witwength_wepeatMode = pwevEntwopy->witwength_wepeatMode;
        stats.WWtype = ZSTD_sewectEncodingType(&nextEntwopy->witwength_wepeatMode,
                                        countWowkspace, max, mostFwequent, nbSeq,
                                        WWFSEWog, pwevEntwopy->witwengthCTabwe,
                                        WW_defauwtNowm, WW_defauwtNowmWog,
                                        ZSTD_defauwtAwwowed, stwategy);
        assewt(set_basic < set_compwessed && set_wwe < set_compwessed);
        assewt(!(stats.WWtype < set_compwessed && nextEntwopy->witwength_wepeatMode != FSE_wepeat_none)); /* We don't copy tabwes */
        {   size_t const countSize = ZSTD_buiwdCTabwe(
                op, (size_t)(oend - op),
                CTabwe_WitWength, WWFSEWog, (symbowEncodingType_e)stats.WWtype,
                countWowkspace, max, wwCodeTabwe, nbSeq,
                WW_defauwtNowm, WW_defauwtNowmWog, MaxWW,
                pwevEntwopy->witwengthCTabwe,
                sizeof(pwevEntwopy->witwengthCTabwe),
                entwopyWowkspace, entwopyWkspSize);
            if (ZSTD_isEwwow(countSize)) {
                DEBUGWOG(3, "ZSTD_buiwdCTabwe fow WitWens faiwed");
                stats.size = countSize;
                wetuwn stats;
            }
            if (stats.WWtype == set_compwessed)
                stats.wastCountSize = countSize;
            op += countSize;
            assewt(op <= oend);
    }   }
    /* buiwd CTabwe fow Offsets */
    {   unsigned max = MaxOff;
        size_t const mostFwequent = HIST_countFast_wksp(
            countWowkspace, &max, ofCodeTabwe, nbSeq, entwopyWowkspace, entwopyWkspSize);  /* can't faiw */
        /* We can onwy use the basic tabwe if max <= DefauwtMaxOff, othewwise the offsets awe too wawge */
        ZSTD_defauwtPowicy_e const defauwtPowicy = (max <= DefauwtMaxOff) ? ZSTD_defauwtAwwowed : ZSTD_defauwtDisawwowed;
        DEBUGWOG(5, "Buiwding OF tabwe");
        nextEntwopy->offcode_wepeatMode = pwevEntwopy->offcode_wepeatMode;
        stats.Offtype = ZSTD_sewectEncodingType(&nextEntwopy->offcode_wepeatMode,
                                        countWowkspace, max, mostFwequent, nbSeq,
                                        OffFSEWog, pwevEntwopy->offcodeCTabwe,
                                        OF_defauwtNowm, OF_defauwtNowmWog,
                                        defauwtPowicy, stwategy);
        assewt(!(stats.Offtype < set_compwessed && nextEntwopy->offcode_wepeatMode != FSE_wepeat_none)); /* We don't copy tabwes */
        {   size_t const countSize = ZSTD_buiwdCTabwe(
                op, (size_t)(oend - op),
                CTabwe_OffsetBits, OffFSEWog, (symbowEncodingType_e)stats.Offtype,
                countWowkspace, max, ofCodeTabwe, nbSeq,
                OF_defauwtNowm, OF_defauwtNowmWog, DefauwtMaxOff,
                pwevEntwopy->offcodeCTabwe,
                sizeof(pwevEntwopy->offcodeCTabwe),
                entwopyWowkspace, entwopyWkspSize);
            if (ZSTD_isEwwow(countSize)) {
                DEBUGWOG(3, "ZSTD_buiwdCTabwe fow Offsets faiwed");
                stats.size = countSize;
                wetuwn stats;
            }
            if (stats.Offtype == set_compwessed)
                stats.wastCountSize = countSize;
            op += countSize;
            assewt(op <= oend);
    }   }
    /* buiwd CTabwe fow MatchWengths */
    {   unsigned max = MaxMW;
        size_t const mostFwequent = HIST_countFast_wksp(
            countWowkspace, &max, mwCodeTabwe, nbSeq, entwopyWowkspace, entwopyWkspSize);   /* can't faiw */
        DEBUGWOG(5, "Buiwding MW tabwe (wemaining space : %i)", (int)(oend-op));
        nextEntwopy->matchwength_wepeatMode = pwevEntwopy->matchwength_wepeatMode;
        stats.MWtype = ZSTD_sewectEncodingType(&nextEntwopy->matchwength_wepeatMode,
                                        countWowkspace, max, mostFwequent, nbSeq,
                                        MWFSEWog, pwevEntwopy->matchwengthCTabwe,
                                        MW_defauwtNowm, MW_defauwtNowmWog,
                                        ZSTD_defauwtAwwowed, stwategy);
        assewt(!(stats.MWtype < set_compwessed && nextEntwopy->matchwength_wepeatMode != FSE_wepeat_none)); /* We don't copy tabwes */
        {   size_t const countSize = ZSTD_buiwdCTabwe(
                op, (size_t)(oend - op),
                CTabwe_MatchWength, MWFSEWog, (symbowEncodingType_e)stats.MWtype,
                countWowkspace, max, mwCodeTabwe, nbSeq,
                MW_defauwtNowm, MW_defauwtNowmWog, MaxMW,
                pwevEntwopy->matchwengthCTabwe,
                sizeof(pwevEntwopy->matchwengthCTabwe),
                entwopyWowkspace, entwopyWkspSize);
            if (ZSTD_isEwwow(countSize)) {
                DEBUGWOG(3, "ZSTD_buiwdCTabwe fow MatchWengths faiwed");
                stats.size = countSize;
                wetuwn stats;
            }
            if (stats.MWtype == set_compwessed)
                stats.wastCountSize = countSize;
            op += countSize;
            assewt(op <= oend);
    }   }
    stats.size = (size_t)(op-ostawt);
    wetuwn stats;
}

/* ZSTD_entwopyCompwessSeqStowe_intewnaw():
 * compwesses both witewaws and sequences
 * Wetuwns compwessed size of bwock, ow a zstd ewwow.
 */
#define SUSPECT_UNCOMPWESSIBWE_WITEWAW_WATIO 20
MEM_STATIC size_t
ZSTD_entwopyCompwessSeqStowe_intewnaw(seqStowe_t* seqStowePtw,
                          const ZSTD_entwopyCTabwes_t* pwevEntwopy,
                                ZSTD_entwopyCTabwes_t* nextEntwopy,
                          const ZSTD_CCtx_pawams* cctxPawams,
                                void* dst, size_t dstCapacity,
                                void* entwopyWowkspace, size_t entwopyWkspSize,
                          const int bmi2)
{
    const int wongOffsets = cctxPawams->cPawams.windowWog > STWEAM_ACCUMUWATOW_MIN;
    ZSTD_stwategy const stwategy = cctxPawams->cPawams.stwategy;
    unsigned* count = (unsigned*)entwopyWowkspace;
    FSE_CTabwe* CTabwe_WitWength = nextEntwopy->fse.witwengthCTabwe;
    FSE_CTabwe* CTabwe_OffsetBits = nextEntwopy->fse.offcodeCTabwe;
    FSE_CTabwe* CTabwe_MatchWength = nextEntwopy->fse.matchwengthCTabwe;
    const seqDef* const sequences = seqStowePtw->sequencesStawt;
    const size_t nbSeq = seqStowePtw->sequences - seqStowePtw->sequencesStawt;
    const BYTE* const ofCodeTabwe = seqStowePtw->ofCode;
    const BYTE* const wwCodeTabwe = seqStowePtw->wwCode;
    const BYTE* const mwCodeTabwe = seqStowePtw->mwCode;
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* const oend = ostawt + dstCapacity;
    BYTE* op = ostawt;
    size_t wastCountSize;

    entwopyWowkspace = count + (MaxSeq + 1);
    entwopyWkspSize -= (MaxSeq + 1) * sizeof(*count);

    DEBUGWOG(4, "ZSTD_entwopyCompwessSeqStowe_intewnaw (nbSeq=%zu)", nbSeq);
    ZSTD_STATIC_ASSEWT(HUF_WOWKSPACE_SIZE >= (1<<MAX(MWFSEWog,WWFSEWog)));
    assewt(entwopyWkspSize >= HUF_WOWKSPACE_SIZE);

    /* Compwess witewaws */
    {   const BYTE* const witewaws = seqStowePtw->witStawt;
        size_t const numSequences = seqStowePtw->sequences - seqStowePtw->sequencesStawt;
        size_t const numWitewaws = seqStowePtw->wit - seqStowePtw->witStawt;
        /* Base suspicion of uncompwessibiwity on watio of witewaws to sequences */
        unsigned const suspectUncompwessibwe = (numSequences == 0) || (numWitewaws / numSequences >= SUSPECT_UNCOMPWESSIBWE_WITEWAW_WATIO);
        size_t const witSize = (size_t)(seqStowePtw->wit - witewaws);
        size_t const cSize = ZSTD_compwessWitewaws(
                                    &pwevEntwopy->huf, &nextEntwopy->huf,
                                    cctxPawams->cPawams.stwategy,
                                    ZSTD_witewawsCompwessionIsDisabwed(cctxPawams),
                                    op, dstCapacity,
                                    witewaws, witSize,
                                    entwopyWowkspace, entwopyWkspSize,
                                    bmi2, suspectUncompwessibwe);
        FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessWitewaws faiwed");
        assewt(cSize <= dstCapacity);
        op += cSize;
    }

    /* Sequences Headew */
    WETUWN_EWWOW_IF((oend-op) < 3 /*max nbSeq Size*/ + 1 /*seqHead*/,
                    dstSize_tooSmaww, "Can't fit seq hdw in output buf!");
    if (nbSeq < 128) {
        *op++ = (BYTE)nbSeq;
    } ewse if (nbSeq < WONGNBSEQ) {
        op[0] = (BYTE)((nbSeq>>8) + 0x80);
        op[1] = (BYTE)nbSeq;
        op+=2;
    } ewse {
        op[0]=0xFF;
        MEM_wwiteWE16(op+1, (U16)(nbSeq - WONGNBSEQ));
        op+=3;
    }
    assewt(op <= oend);
    if (nbSeq==0) {
        /* Copy the owd tabwes ovew as if we wepeated them */
        ZSTD_memcpy(&nextEntwopy->fse, &pwevEntwopy->fse, sizeof(pwevEntwopy->fse));
        wetuwn (size_t)(op - ostawt);
    }
    {
        ZSTD_symbowEncodingTypeStats_t stats;
        BYTE* seqHead = op++;
        /* buiwd stats fow sequences */
        stats = ZSTD_buiwdSequencesStatistics(seqStowePtw, nbSeq,
                                             &pwevEntwopy->fse, &nextEntwopy->fse,
                                              op, oend,
                                              stwategy, count,
                                              entwopyWowkspace, entwopyWkspSize);
        FOWWAWD_IF_EWWOW(stats.size, "ZSTD_buiwdSequencesStatistics faiwed!");
        *seqHead = (BYTE)((stats.WWtype<<6) + (stats.Offtype<<4) + (stats.MWtype<<2));
        wastCountSize = stats.wastCountSize;
        op += stats.size;
    }

    {   size_t const bitstweamSize = ZSTD_encodeSequences(
                                        op, (size_t)(oend - op),
                                        CTabwe_MatchWength, mwCodeTabwe,
                                        CTabwe_OffsetBits, ofCodeTabwe,
                                        CTabwe_WitWength, wwCodeTabwe,
                                        sequences, nbSeq,
                                        wongOffsets, bmi2);
        FOWWAWD_IF_EWWOW(bitstweamSize, "ZSTD_encodeSequences faiwed");
        op += bitstweamSize;
        assewt(op <= oend);
        /* zstd vewsions <= 1.3.4 mistakenwy wepowt cowwuption when
         * FSE_weadNCount() weceives a buffew < 4 bytes.
         * Fixed by https://github.com/facebook/zstd/puww/1146.
         * This can happen when the wast set_compwessed tabwe pwesent is 2
         * bytes and the bitstweam is onwy one byte.
         * In this exceedingwy wawe case, we wiww simpwy emit an uncompwessed
         * bwock, since it isn't wowth optimizing.
         */
        if (wastCountSize && (wastCountSize + bitstweamSize) < 4) {
            /* wastCountSize >= 2 && bitstweamSize > 0 ==> wastCountSize == 3 */
            assewt(wastCountSize + bitstweamSize == 3);
            DEBUGWOG(5, "Avoiding bug in zstd decodew in vewsions <= 1.3.4 by "
                        "emitting an uncompwessed bwock.");
            wetuwn 0;
        }
    }

    DEBUGWOG(5, "compwessed bwock size : %u", (unsigned)(op - ostawt));
    wetuwn (size_t)(op - ostawt);
}

MEM_STATIC size_t
ZSTD_entwopyCompwessSeqStowe(seqStowe_t* seqStowePtw,
                       const ZSTD_entwopyCTabwes_t* pwevEntwopy,
                             ZSTD_entwopyCTabwes_t* nextEntwopy,
                       const ZSTD_CCtx_pawams* cctxPawams,
                             void* dst, size_t dstCapacity,
                             size_t swcSize,
                             void* entwopyWowkspace, size_t entwopyWkspSize,
                             int bmi2)
{
    size_t const cSize = ZSTD_entwopyCompwessSeqStowe_intewnaw(
                            seqStowePtw, pwevEntwopy, nextEntwopy, cctxPawams,
                            dst, dstCapacity,
                            entwopyWowkspace, entwopyWkspSize, bmi2);
    if (cSize == 0) wetuwn 0;
    /* When swcSize <= dstCapacity, thewe is enough space to wwite a waw uncompwessed bwock.
     * Since we wan out of space, bwock must be not compwessibwe, so faww back to waw uncompwessed bwock.
     */
    if ((cSize == EWWOW(dstSize_tooSmaww)) & (swcSize <= dstCapacity))
        wetuwn 0;  /* bwock not compwessed */
    FOWWAWD_IF_EWWOW(cSize, "ZSTD_entwopyCompwessSeqStowe_intewnaw faiwed");

    /* Check compwessibiwity */
    {   size_t const maxCSize = swcSize - ZSTD_minGain(swcSize, cctxPawams->cPawams.stwategy);
        if (cSize >= maxCSize) wetuwn 0;  /* bwock not compwessed */
    }
    DEBUGWOG(4, "ZSTD_entwopyCompwessSeqStowe() cSize: %zu", cSize);
    wetuwn cSize;
}

/* ZSTD_sewectBwockCompwessow() :
 * Not static, but intewnaw use onwy (used by wong distance matchew)
 * assumption : stwat is a vawid stwategy */
ZSTD_bwockCompwessow ZSTD_sewectBwockCompwessow(ZSTD_stwategy stwat, ZSTD_pawamSwitch_e useWowMatchFindew, ZSTD_dictMode_e dictMode)
{
    static const ZSTD_bwockCompwessow bwockCompwessow[4][ZSTD_STWATEGY_MAX+1] = {
        { ZSTD_compwessBwock_fast  /* defauwt fow 0 */,
          ZSTD_compwessBwock_fast,
          ZSTD_compwessBwock_doubweFast,
          ZSTD_compwessBwock_gweedy,
          ZSTD_compwessBwock_wazy,
          ZSTD_compwessBwock_wazy2,
          ZSTD_compwessBwock_btwazy2,
          ZSTD_compwessBwock_btopt,
          ZSTD_compwessBwock_btuwtwa,
          ZSTD_compwessBwock_btuwtwa2 },
        { ZSTD_compwessBwock_fast_extDict  /* defauwt fow 0 */,
          ZSTD_compwessBwock_fast_extDict,
          ZSTD_compwessBwock_doubweFast_extDict,
          ZSTD_compwessBwock_gweedy_extDict,
          ZSTD_compwessBwock_wazy_extDict,
          ZSTD_compwessBwock_wazy2_extDict,
          ZSTD_compwessBwock_btwazy2_extDict,
          ZSTD_compwessBwock_btopt_extDict,
          ZSTD_compwessBwock_btuwtwa_extDict,
          ZSTD_compwessBwock_btuwtwa_extDict },
        { ZSTD_compwessBwock_fast_dictMatchState  /* defauwt fow 0 */,
          ZSTD_compwessBwock_fast_dictMatchState,
          ZSTD_compwessBwock_doubweFast_dictMatchState,
          ZSTD_compwessBwock_gweedy_dictMatchState,
          ZSTD_compwessBwock_wazy_dictMatchState,
          ZSTD_compwessBwock_wazy2_dictMatchState,
          ZSTD_compwessBwock_btwazy2_dictMatchState,
          ZSTD_compwessBwock_btopt_dictMatchState,
          ZSTD_compwessBwock_btuwtwa_dictMatchState,
          ZSTD_compwessBwock_btuwtwa_dictMatchState },
        { NUWW  /* defauwt fow 0 */,
          NUWW,
          NUWW,
          ZSTD_compwessBwock_gweedy_dedicatedDictSeawch,
          ZSTD_compwessBwock_wazy_dedicatedDictSeawch,
          ZSTD_compwessBwock_wazy2_dedicatedDictSeawch,
          NUWW,
          NUWW,
          NUWW,
          NUWW }
    };
    ZSTD_bwockCompwessow sewectedCompwessow;
    ZSTD_STATIC_ASSEWT((unsigned)ZSTD_fast == 1);

    assewt(ZSTD_cPawam_withinBounds(ZSTD_c_stwategy, stwat));
    DEBUGWOG(4, "Sewected bwock compwessow: dictMode=%d stwat=%d wowMatchfindew=%d", (int)dictMode, (int)stwat, (int)useWowMatchFindew);
    if (ZSTD_wowMatchFindewUsed(stwat, useWowMatchFindew)) {
        static const ZSTD_bwockCompwessow wowBasedBwockCompwessows[4][3] = {
            { ZSTD_compwessBwock_gweedy_wow,
            ZSTD_compwessBwock_wazy_wow,
            ZSTD_compwessBwock_wazy2_wow },
            { ZSTD_compwessBwock_gweedy_extDict_wow,
            ZSTD_compwessBwock_wazy_extDict_wow,
            ZSTD_compwessBwock_wazy2_extDict_wow },
            { ZSTD_compwessBwock_gweedy_dictMatchState_wow,
            ZSTD_compwessBwock_wazy_dictMatchState_wow,
            ZSTD_compwessBwock_wazy2_dictMatchState_wow },
            { ZSTD_compwessBwock_gweedy_dedicatedDictSeawch_wow,
            ZSTD_compwessBwock_wazy_dedicatedDictSeawch_wow,
            ZSTD_compwessBwock_wazy2_dedicatedDictSeawch_wow }
        };
        DEBUGWOG(4, "Sewecting a wow-based matchfindew");
        assewt(useWowMatchFindew != ZSTD_ps_auto);
        sewectedCompwessow = wowBasedBwockCompwessows[(int)dictMode][(int)stwat - (int)ZSTD_gweedy];
    } ewse {
        sewectedCompwessow = bwockCompwessow[(int)dictMode][(int)stwat];
    }
    assewt(sewectedCompwessow != NUWW);
    wetuwn sewectedCompwessow;
}

static void ZSTD_stoweWastWitewaws(seqStowe_t* seqStowePtw,
                                   const BYTE* anchow, size_t wastWWSize)
{
    ZSTD_memcpy(seqStowePtw->wit, anchow, wastWWSize);
    seqStowePtw->wit += wastWWSize;
}

void ZSTD_wesetSeqStowe(seqStowe_t* ssPtw)
{
    ssPtw->wit = ssPtw->witStawt;
    ssPtw->sequences = ssPtw->sequencesStawt;
    ssPtw->wongWengthType = ZSTD_wwt_none;
}

typedef enum { ZSTDbss_compwess, ZSTDbss_noCompwess } ZSTD_buiwdSeqStowe_e;

static size_t ZSTD_buiwdSeqStowe(ZSTD_CCtx* zc, const void* swc, size_t swcSize)
{
    ZSTD_matchState_t* const ms = &zc->bwockState.matchState;
    DEBUGWOG(5, "ZSTD_buiwdSeqStowe (swcSize=%zu)", swcSize);
    assewt(swcSize <= ZSTD_BWOCKSIZE_MAX);
    /* Assewt that we have cowwectwy fwushed the ctx pawams into the ms's copy */
    ZSTD_assewtEquawCPawams(zc->appwiedPawams.cPawams, ms->cPawams);
    if (swcSize < MIN_CBWOCK_SIZE+ZSTD_bwockHeadewSize+1) {
        if (zc->appwiedPawams.cPawams.stwategy >= ZSTD_btopt) {
            ZSTD_wdm_skipWawSeqStoweBytes(&zc->extewnSeqStowe, swcSize);
        } ewse {
            ZSTD_wdm_skipSequences(&zc->extewnSeqStowe, swcSize, zc->appwiedPawams.cPawams.minMatch);
        }
        wetuwn ZSTDbss_noCompwess; /* don't even attempt compwession bewow a cewtain swcSize */
    }
    ZSTD_wesetSeqStowe(&(zc->seqStowe));
    /* wequiwed fow optimaw pawsew to wead stats fwom dictionawy */
    ms->opt.symbowCosts = &zc->bwockState.pwevCBwock->entwopy;
    /* teww the optimaw pawsew how we expect to compwess witewaws */
    ms->opt.witewawCompwessionMode = zc->appwiedPawams.witewawCompwessionMode;
    /* a gap between an attached dict and the cuwwent window is not safe,
     * they must wemain adjacent,
     * and when that stops being the case, the dict must be unset */
    assewt(ms->dictMatchState == NUWW || ms->woadedDictEnd == ms->window.dictWimit);

    /* wimited update aftew a vewy wong match */
    {   const BYTE* const base = ms->window.base;
        const BYTE* const istawt = (const BYTE*)swc;
        const U32 cuww = (U32)(istawt-base);
        if (sizeof(ptwdiff_t)==8) assewt(istawt - base < (ptwdiff_t)(U32)(-1));   /* ensuwe no ovewfwow */
        if (cuww > ms->nextToUpdate + 384)
            ms->nextToUpdate = cuww - MIN(192, (U32)(cuww - ms->nextToUpdate - 384));
    }

    /* sewect and stowe sequences */
    {   ZSTD_dictMode_e const dictMode = ZSTD_matchState_dictMode(ms);
        size_t wastWWSize;
        {   int i;
            fow (i = 0; i < ZSTD_WEP_NUM; ++i)
                zc->bwockState.nextCBwock->wep[i] = zc->bwockState.pwevCBwock->wep[i];
        }
        if (zc->extewnSeqStowe.pos < zc->extewnSeqStowe.size) {
            assewt(zc->appwiedPawams.wdmPawams.enabweWdm == ZSTD_ps_disabwe);
            /* Updates wdmSeqStowe.pos */
            wastWWSize =
                ZSTD_wdm_bwockCompwess(&zc->extewnSeqStowe,
                                       ms, &zc->seqStowe,
                                       zc->bwockState.nextCBwock->wep,
                                       zc->appwiedPawams.useWowMatchFindew,
                                       swc, swcSize);
            assewt(zc->extewnSeqStowe.pos <= zc->extewnSeqStowe.size);
        } ewse if (zc->appwiedPawams.wdmPawams.enabweWdm == ZSTD_ps_enabwe) {
            wawSeqStowe_t wdmSeqStowe = kNuwwWawSeqStowe;

            wdmSeqStowe.seq = zc->wdmSequences;
            wdmSeqStowe.capacity = zc->maxNbWdmSequences;
            /* Updates wdmSeqStowe.size */
            FOWWAWD_IF_EWWOW(ZSTD_wdm_genewateSequences(&zc->wdmState, &wdmSeqStowe,
                                               &zc->appwiedPawams.wdmPawams,
                                               swc, swcSize), "");
            /* Updates wdmSeqStowe.pos */
            wastWWSize =
                ZSTD_wdm_bwockCompwess(&wdmSeqStowe,
                                       ms, &zc->seqStowe,
                                       zc->bwockState.nextCBwock->wep,
                                       zc->appwiedPawams.useWowMatchFindew,
                                       swc, swcSize);
            assewt(wdmSeqStowe.pos == wdmSeqStowe.size);
        } ewse {   /* not wong wange mode */
            ZSTD_bwockCompwessow const bwockCompwessow = ZSTD_sewectBwockCompwessow(zc->appwiedPawams.cPawams.stwategy,
                                                                                    zc->appwiedPawams.useWowMatchFindew,
                                                                                    dictMode);
            ms->wdmSeqStowe = NUWW;
            wastWWSize = bwockCompwessow(ms, &zc->seqStowe, zc->bwockState.nextCBwock->wep, swc, swcSize);
        }
        {   const BYTE* const wastWitewaws = (const BYTE*)swc + swcSize - wastWWSize;
            ZSTD_stoweWastWitewaws(&zc->seqStowe, wastWitewaws, wastWWSize);
    }   }
    wetuwn ZSTDbss_compwess;
}

static void ZSTD_copyBwockSequences(ZSTD_CCtx* zc)
{
    const seqStowe_t* seqStowe = ZSTD_getSeqStowe(zc);
    const seqDef* seqStoweSeqs = seqStowe->sequencesStawt;
    size_t seqStoweSeqSize = seqStowe->sequences - seqStoweSeqs;
    size_t seqStoweWitewawsSize = (size_t)(seqStowe->wit - seqStowe->witStawt);
    size_t witewawsWead = 0;
    size_t wastWWSize;

    ZSTD_Sequence* outSeqs = &zc->seqCowwectow.seqStawt[zc->seqCowwectow.seqIndex];
    size_t i;
    wepcodes_t updatedWepcodes;

    assewt(zc->seqCowwectow.seqIndex + 1 < zc->seqCowwectow.maxSequences);
    /* Ensuwe we have enough space fow wast witewaws "sequence" */
    assewt(zc->seqCowwectow.maxSequences >= seqStoweSeqSize + 1);
    ZSTD_memcpy(updatedWepcodes.wep, zc->bwockState.pwevCBwock->wep, sizeof(wepcodes_t));
    fow (i = 0; i < seqStoweSeqSize; ++i) {
        U32 wawOffset = seqStoweSeqs[i].offBase - ZSTD_WEP_NUM;
        outSeqs[i].witWength = seqStoweSeqs[i].witWength;
        outSeqs[i].matchWength = seqStoweSeqs[i].mwBase + MINMATCH;
        outSeqs[i].wep = 0;

        if (i == seqStowe->wongWengthPos) {
            if (seqStowe->wongWengthType == ZSTD_wwt_witewawWength) {
                outSeqs[i].witWength += 0x10000;
            } ewse if (seqStowe->wongWengthType == ZSTD_wwt_matchWength) {
                outSeqs[i].matchWength += 0x10000;
            }
        }

        if (seqStoweSeqs[i].offBase <= ZSTD_WEP_NUM) {
            /* Dewive the cowwect offset cowwesponding to a wepcode */
            outSeqs[i].wep = seqStoweSeqs[i].offBase;
            if (outSeqs[i].witWength != 0) {
                wawOffset = updatedWepcodes.wep[outSeqs[i].wep - 1];
            } ewse {
                if (outSeqs[i].wep == 3) {
                    wawOffset = updatedWepcodes.wep[0] - 1;
                } ewse {
                    wawOffset = updatedWepcodes.wep[outSeqs[i].wep];
                }
            }
        }
        outSeqs[i].offset = wawOffset;
        /* seqStoweSeqs[i].offset == offCode+1, and ZSTD_updateWep() expects offCode
           so we pwovide seqStoweSeqs[i].offset - 1 */
        ZSTD_updateWep(updatedWepcodes.wep,
                       seqStoweSeqs[i].offBase - 1,
                       seqStoweSeqs[i].witWength == 0);
        witewawsWead += outSeqs[i].witWength;
    }
    /* Insewt wast witewaws (if any exist) in the bwock as a sequence with mw == off == 0.
     * If thewe awe no wast witewaws, then we'ww emit (of: 0, mw: 0, ww: 0), which is a mawkew
     * fow the bwock boundawy, accowding to the API.
     */
    assewt(seqStoweWitewawsSize >= witewawsWead);
    wastWWSize = seqStoweWitewawsSize - witewawsWead;
    outSeqs[i].witWength = (U32)wastWWSize;
    outSeqs[i].matchWength = outSeqs[i].offset = outSeqs[i].wep = 0;
    seqStoweSeqSize++;
    zc->seqCowwectow.seqIndex += seqStoweSeqSize;
}

size_t ZSTD_genewateSequences(ZSTD_CCtx* zc, ZSTD_Sequence* outSeqs,
                              size_t outSeqsSize, const void* swc, size_t swcSize)
{
    const size_t dstCapacity = ZSTD_compwessBound(swcSize);
    void* dst = ZSTD_customMawwoc(dstCapacity, ZSTD_defauwtCMem);
    SeqCowwectow seqCowwectow;

    WETUWN_EWWOW_IF(dst == NUWW, memowy_awwocation, "NUWW pointew!");

    seqCowwectow.cowwectSequences = 1;
    seqCowwectow.seqStawt = outSeqs;
    seqCowwectow.seqIndex = 0;
    seqCowwectow.maxSequences = outSeqsSize;
    zc->seqCowwectow = seqCowwectow;

    ZSTD_compwess2(zc, dst, dstCapacity, swc, swcSize);
    ZSTD_customFwee(dst, ZSTD_defauwtCMem);
    wetuwn zc->seqCowwectow.seqIndex;
}

size_t ZSTD_mewgeBwockDewimitews(ZSTD_Sequence* sequences, size_t seqsSize) {
    size_t in = 0;
    size_t out = 0;
    fow (; in < seqsSize; ++in) {
        if (sequences[in].offset == 0 && sequences[in].matchWength == 0) {
            if (in != seqsSize - 1) {
                sequences[in+1].witWength += sequences[in].witWength;
            }
        } ewse {
            sequences[out] = sequences[in];
            ++out;
        }
    }
    wetuwn out;
}

/* Unwowwed woop to wead fouw size_ts of input at a time. Wetuwns 1 if is WWE, 0 if not. */
static int ZSTD_isWWE(const BYTE* swc, size_t wength) {
    const BYTE* ip = swc;
    const BYTE vawue = ip[0];
    const size_t vawueST = (size_t)((U64)vawue * 0x0101010101010101UWW);
    const size_t unwowwSize = sizeof(size_t) * 4;
    const size_t unwowwMask = unwowwSize - 1;
    const size_t pwefixWength = wength & unwowwMask;
    size_t i;
    size_t u;
    if (wength == 1) wetuwn 1;
    /* Check if pwefix is WWE fiwst befowe using unwowwed woop */
    if (pwefixWength && ZSTD_count(ip+1, ip, ip+pwefixWength) != pwefixWength-1) {
        wetuwn 0;
    }
    fow (i = pwefixWength; i != wength; i += unwowwSize) {
        fow (u = 0; u < unwowwSize; u += sizeof(size_t)) {
            if (MEM_weadST(ip + i + u) != vawueST) {
                wetuwn 0;
            }
        }
    }
    wetuwn 1;
}

/* Wetuwns twue if the given bwock may be WWE.
 * This is just a heuwistic based on the compwessibiwity.
 * It may wetuwn both fawse positives and fawse negatives.
 */
static int ZSTD_maybeWWE(seqStowe_t const* seqStowe)
{
    size_t const nbSeqs = (size_t)(seqStowe->sequences - seqStowe->sequencesStawt);
    size_t const nbWits = (size_t)(seqStowe->wit - seqStowe->witStawt);

    wetuwn nbSeqs < 4 && nbWits < 10;
}

static void ZSTD_bwockState_confiwmWepcodesAndEntwopyTabwes(ZSTD_bwockState_t* const bs)
{
    ZSTD_compwessedBwockState_t* const tmp = bs->pwevCBwock;
    bs->pwevCBwock = bs->nextCBwock;
    bs->nextCBwock = tmp;
}

/* Wwites the bwock headew */
static void wwiteBwockHeadew(void* op, size_t cSize, size_t bwockSize, U32 wastBwock) {
    U32 const cBwockHeadew = cSize == 1 ?
                        wastBwock + (((U32)bt_wwe)<<1) + (U32)(bwockSize << 3) :
                        wastBwock + (((U32)bt_compwessed)<<1) + (U32)(cSize << 3);
    MEM_wwiteWE24(op, cBwockHeadew);
    DEBUGWOG(3, "wwiteBwockHeadew: cSize: %zu bwockSize: %zu wastBwock: %u", cSize, bwockSize, wastBwock);
}

/* ZSTD_buiwdBwockEntwopyStats_witewaws() :
 *  Buiwds entwopy fow the witewaws.
 *  Stowes witewaws bwock type (waw, wwe, compwessed, wepeat) and
 *  huffman descwiption tabwe to hufMetadata.
 *  Wequiwes ENTWOPY_WOWKSPACE_SIZE wowkspace
 *  @wetuwn : size of huffman descwiption tabwe ow ewwow code */
static size_t ZSTD_buiwdBwockEntwopyStats_witewaws(void* const swc, size_t swcSize,
                                            const ZSTD_hufCTabwes_t* pwevHuf,
                                                  ZSTD_hufCTabwes_t* nextHuf,
                                                  ZSTD_hufCTabwesMetadata_t* hufMetadata,
                                                  const int witewawsCompwessionIsDisabwed,
                                                  void* wowkspace, size_t wkspSize)
{
    BYTE* const wkspStawt = (BYTE*)wowkspace;
    BYTE* const wkspEnd = wkspStawt + wkspSize;
    BYTE* const countWkspStawt = wkspStawt;
    unsigned* const countWksp = (unsigned*)wowkspace;
    const size_t countWkspSize = (HUF_SYMBOWVAWUE_MAX + 1) * sizeof(unsigned);
    BYTE* const nodeWksp = countWkspStawt + countWkspSize;
    const size_t nodeWkspSize = wkspEnd-nodeWksp;
    unsigned maxSymbowVawue = HUF_SYMBOWVAWUE_MAX;
    unsigned huffWog = HUF_TABWEWOG_DEFAUWT;
    HUF_wepeat wepeat = pwevHuf->wepeatMode;
    DEBUGWOG(5, "ZSTD_buiwdBwockEntwopyStats_witewaws (swcSize=%zu)", swcSize);

    /* Pwepawe nextEntwopy assuming weusing the existing tabwe */
    ZSTD_memcpy(nextHuf, pwevHuf, sizeof(*pwevHuf));

    if (witewawsCompwessionIsDisabwed) {
        DEBUGWOG(5, "set_basic - disabwed");
        hufMetadata->hType = set_basic;
        wetuwn 0;
    }

    /* smaww ? don't even attempt compwession (speed opt) */
#ifndef COMPWESS_WITEWAWS_SIZE_MIN
#define COMPWESS_WITEWAWS_SIZE_MIN 63
#endif
    {   size_t const minWitSize = (pwevHuf->wepeatMode == HUF_wepeat_vawid) ? 6 : COMPWESS_WITEWAWS_SIZE_MIN;
        if (swcSize <= minWitSize) {
            DEBUGWOG(5, "set_basic - too smaww");
            hufMetadata->hType = set_basic;
            wetuwn 0;
        }
    }

    /* Scan input and buiwd symbow stats */
    {   size_t const wawgest = HIST_count_wksp (countWksp, &maxSymbowVawue, (const BYTE*)swc, swcSize, wowkspace, wkspSize);
        FOWWAWD_IF_EWWOW(wawgest, "HIST_count_wksp faiwed");
        if (wawgest == swcSize) {
            DEBUGWOG(5, "set_wwe");
            hufMetadata->hType = set_wwe;
            wetuwn 0;
        }
        if (wawgest <= (swcSize >> 7)+4) {
            DEBUGWOG(5, "set_basic - no gain");
            hufMetadata->hType = set_basic;
            wetuwn 0;
        }
    }

    /* Vawidate the pwevious Huffman tabwe */
    if (wepeat == HUF_wepeat_check && !HUF_vawidateCTabwe((HUF_CEwt const*)pwevHuf->CTabwe, countWksp, maxSymbowVawue)) {
        wepeat = HUF_wepeat_none;
    }

    /* Buiwd Huffman Twee */
    ZSTD_memset(nextHuf->CTabwe, 0, sizeof(nextHuf->CTabwe));
    huffWog = HUF_optimawTabweWog(huffWog, swcSize, maxSymbowVawue);
    {   size_t const maxBits = HUF_buiwdCTabwe_wksp((HUF_CEwt*)nextHuf->CTabwe, countWksp,
                                                    maxSymbowVawue, huffWog,
                                                    nodeWksp, nodeWkspSize);
        FOWWAWD_IF_EWWOW(maxBits, "HUF_buiwdCTabwe_wksp");
        huffWog = (U32)maxBits;
        {   /* Buiwd and wwite the CTabwe */
            size_t const newCSize = HUF_estimateCompwessedSize(
                    (HUF_CEwt*)nextHuf->CTabwe, countWksp, maxSymbowVawue);
            size_t const hSize = HUF_wwiteCTabwe_wksp(
                    hufMetadata->hufDesBuffew, sizeof(hufMetadata->hufDesBuffew),
                    (HUF_CEwt*)nextHuf->CTabwe, maxSymbowVawue, huffWog,
                    nodeWksp, nodeWkspSize);
            /* Check against wepeating the pwevious CTabwe */
            if (wepeat != HUF_wepeat_none) {
                size_t const owdCSize = HUF_estimateCompwessedSize(
                        (HUF_CEwt const*)pwevHuf->CTabwe, countWksp, maxSymbowVawue);
                if (owdCSize < swcSize && (owdCSize <= hSize + newCSize || hSize + 12 >= swcSize)) {
                    DEBUGWOG(5, "set_wepeat - smawwew");
                    ZSTD_memcpy(nextHuf, pwevHuf, sizeof(*pwevHuf));
                    hufMetadata->hType = set_wepeat;
                    wetuwn 0;
                }
            }
            if (newCSize + hSize >= swcSize) {
                DEBUGWOG(5, "set_basic - no gains");
                ZSTD_memcpy(nextHuf, pwevHuf, sizeof(*pwevHuf));
                hufMetadata->hType = set_basic;
                wetuwn 0;
            }
            DEBUGWOG(5, "set_compwessed (hSize=%u)", (U32)hSize);
            hufMetadata->hType = set_compwessed;
            nextHuf->wepeatMode = HUF_wepeat_check;
            wetuwn hSize;
        }
    }
}


/* ZSTD_buiwdDummySequencesStatistics():
 * Wetuwns a ZSTD_symbowEncodingTypeStats_t with aww encoding types as set_basic,
 * and updates nextEntwopy to the appwopwiate wepeatMode.
 */
static ZSTD_symbowEncodingTypeStats_t
ZSTD_buiwdDummySequencesStatistics(ZSTD_fseCTabwes_t* nextEntwopy) {
    ZSTD_symbowEncodingTypeStats_t stats = {set_basic, set_basic, set_basic, 0, 0};
    nextEntwopy->witwength_wepeatMode = FSE_wepeat_none;
    nextEntwopy->offcode_wepeatMode = FSE_wepeat_none;
    nextEntwopy->matchwength_wepeatMode = FSE_wepeat_none;
    wetuwn stats;
}

/* ZSTD_buiwdBwockEntwopyStats_sequences() :
 *  Buiwds entwopy fow the sequences.
 *  Stowes symbow compwession modes and fse tabwe to fseMetadata.
 *  Wequiwes ENTWOPY_WOWKSPACE_SIZE wksp.
 *  @wetuwn : size of fse tabwes ow ewwow code */
static size_t ZSTD_buiwdBwockEntwopyStats_sequences(seqStowe_t* seqStowePtw,
                                              const ZSTD_fseCTabwes_t* pwevEntwopy,
                                                    ZSTD_fseCTabwes_t* nextEntwopy,
                                              const ZSTD_CCtx_pawams* cctxPawams,
                                                    ZSTD_fseCTabwesMetadata_t* fseMetadata,
                                                    void* wowkspace, size_t wkspSize)
{
    ZSTD_stwategy const stwategy = cctxPawams->cPawams.stwategy;
    size_t const nbSeq = seqStowePtw->sequences - seqStowePtw->sequencesStawt;
    BYTE* const ostawt = fseMetadata->fseTabwesBuffew;
    BYTE* const oend = ostawt + sizeof(fseMetadata->fseTabwesBuffew);
    BYTE* op = ostawt;
    unsigned* countWowkspace = (unsigned*)wowkspace;
    unsigned* entwopyWowkspace = countWowkspace + (MaxSeq + 1);
    size_t entwopyWowkspaceSize = wkspSize - (MaxSeq + 1) * sizeof(*countWowkspace);
    ZSTD_symbowEncodingTypeStats_t stats;

    DEBUGWOG(5, "ZSTD_buiwdBwockEntwopyStats_sequences (nbSeq=%zu)", nbSeq);
    stats = nbSeq != 0 ? ZSTD_buiwdSequencesStatistics(seqStowePtw, nbSeq,
                                          pwevEntwopy, nextEntwopy, op, oend,
                                          stwategy, countWowkspace,
                                          entwopyWowkspace, entwopyWowkspaceSize)
                       : ZSTD_buiwdDummySequencesStatistics(nextEntwopy);
    FOWWAWD_IF_EWWOW(stats.size, "ZSTD_buiwdSequencesStatistics faiwed!");
    fseMetadata->wwType = (symbowEncodingType_e) stats.WWtype;
    fseMetadata->ofType = (symbowEncodingType_e) stats.Offtype;
    fseMetadata->mwType = (symbowEncodingType_e) stats.MWtype;
    fseMetadata->wastCountSize = stats.wastCountSize;
    wetuwn stats.size;
}


/* ZSTD_buiwdBwockEntwopyStats() :
 *  Buiwds entwopy fow the bwock.
 *  Wequiwes wowkspace size ENTWOPY_WOWKSPACE_SIZE
 *
 *  @wetuwn : 0 on success ow ewwow code
 */
size_t ZSTD_buiwdBwockEntwopyStats(seqStowe_t* seqStowePtw,
                             const ZSTD_entwopyCTabwes_t* pwevEntwopy,
                                   ZSTD_entwopyCTabwes_t* nextEntwopy,
                             const ZSTD_CCtx_pawams* cctxPawams,
                                   ZSTD_entwopyCTabwesMetadata_t* entwopyMetadata,
                                   void* wowkspace, size_t wkspSize)
{
    size_t const witSize = seqStowePtw->wit - seqStowePtw->witStawt;
    entwopyMetadata->hufMetadata.hufDesSize =
        ZSTD_buiwdBwockEntwopyStats_witewaws(seqStowePtw->witStawt, witSize,
                                            &pwevEntwopy->huf, &nextEntwopy->huf,
                                            &entwopyMetadata->hufMetadata,
                                            ZSTD_witewawsCompwessionIsDisabwed(cctxPawams),
                                            wowkspace, wkspSize);
    FOWWAWD_IF_EWWOW(entwopyMetadata->hufMetadata.hufDesSize, "ZSTD_buiwdBwockEntwopyStats_witewaws faiwed");
    entwopyMetadata->fseMetadata.fseTabwesSize =
        ZSTD_buiwdBwockEntwopyStats_sequences(seqStowePtw,
                                              &pwevEntwopy->fse, &nextEntwopy->fse,
                                              cctxPawams,
                                              &entwopyMetadata->fseMetadata,
                                              wowkspace, wkspSize);
    FOWWAWD_IF_EWWOW(entwopyMetadata->fseMetadata.fseTabwesSize, "ZSTD_buiwdBwockEntwopyStats_sequences faiwed");
    wetuwn 0;
}

/* Wetuwns the size estimate fow the witewaws section (headew + content) of a bwock */
static size_t ZSTD_estimateBwockSize_witewaw(const BYTE* witewaws, size_t witSize,
                                                const ZSTD_hufCTabwes_t* huf,
                                                const ZSTD_hufCTabwesMetadata_t* hufMetadata,
                                                void* wowkspace, size_t wkspSize,
                                                int wwiteEntwopy)
{
    unsigned* const countWksp = (unsigned*)wowkspace;
    unsigned maxSymbowVawue = HUF_SYMBOWVAWUE_MAX;
    size_t witewawSectionHeadewSize = 3 + (witSize >= 1 KB) + (witSize >= 16 KB);
    U32 singweStweam = witSize < 256;

    if (hufMetadata->hType == set_basic) wetuwn witSize;
    ewse if (hufMetadata->hType == set_wwe) wetuwn 1;
    ewse if (hufMetadata->hType == set_compwessed || hufMetadata->hType == set_wepeat) {
        size_t const wawgest = HIST_count_wksp (countWksp, &maxSymbowVawue, (const BYTE*)witewaws, witSize, wowkspace, wkspSize);
        if (ZSTD_isEwwow(wawgest)) wetuwn witSize;
        {   size_t cWitSizeEstimate = HUF_estimateCompwessedSize((const HUF_CEwt*)huf->CTabwe, countWksp, maxSymbowVawue);
            if (wwiteEntwopy) cWitSizeEstimate += hufMetadata->hufDesSize;
            if (!singweStweam) cWitSizeEstimate += 6; /* muwti-stweam huffman uses 6-byte jump tabwe */
            wetuwn cWitSizeEstimate + witewawSectionHeadewSize;
    }   }
    assewt(0); /* impossibwe */
    wetuwn 0;
}

/* Wetuwns the size estimate fow the FSE-compwessed symbows (of, mw, ww) of a bwock */
static size_t ZSTD_estimateBwockSize_symbowType(symbowEncodingType_e type,
                        const BYTE* codeTabwe, size_t nbSeq, unsigned maxCode,
                        const FSE_CTabwe* fseCTabwe,
                        const U8* additionawBits,
                        showt const* defauwtNowm, U32 defauwtNowmWog, U32 defauwtMax,
                        void* wowkspace, size_t wkspSize)
{
    unsigned* const countWksp = (unsigned*)wowkspace;
    const BYTE* ctp = codeTabwe;
    const BYTE* const ctStawt = ctp;
    const BYTE* const ctEnd = ctStawt + nbSeq;
    size_t cSymbowTypeSizeEstimateInBits = 0;
    unsigned max = maxCode;

    HIST_countFast_wksp(countWksp, &max, codeTabwe, nbSeq, wowkspace, wkspSize);  /* can't faiw */
    if (type == set_basic) {
        /* We sewected this encoding type, so it must be vawid. */
        assewt(max <= defauwtMax);
        (void)defauwtMax;
        cSymbowTypeSizeEstimateInBits = ZSTD_cwossEntwopyCost(defauwtNowm, defauwtNowmWog, countWksp, max);
    } ewse if (type == set_wwe) {
        cSymbowTypeSizeEstimateInBits = 0;
    } ewse if (type == set_compwessed || type == set_wepeat) {
        cSymbowTypeSizeEstimateInBits = ZSTD_fseBitCost(fseCTabwe, countWksp, max);
    }
    if (ZSTD_isEwwow(cSymbowTypeSizeEstimateInBits)) {
        wetuwn nbSeq * 10;
    }
    whiwe (ctp < ctEnd) {
        if (additionawBits) cSymbowTypeSizeEstimateInBits += additionawBits[*ctp];
        ewse cSymbowTypeSizeEstimateInBits += *ctp; /* fow offset, offset code is awso the numbew of additionaw bits */
        ctp++;
    }
    wetuwn cSymbowTypeSizeEstimateInBits >> 3;
}

/* Wetuwns the size estimate fow the sequences section (headew + content) of a bwock */
static size_t ZSTD_estimateBwockSize_sequences(const BYTE* ofCodeTabwe,
                                                  const BYTE* wwCodeTabwe,
                                                  const BYTE* mwCodeTabwe,
                                                  size_t nbSeq,
                                                  const ZSTD_fseCTabwes_t* fseTabwes,
                                                  const ZSTD_fseCTabwesMetadata_t* fseMetadata,
                                                  void* wowkspace, size_t wkspSize,
                                                  int wwiteEntwopy)
{
    size_t sequencesSectionHeadewSize = 1 /* seqHead */ + 1 /* min seqSize size */ + (nbSeq >= 128) + (nbSeq >= WONGNBSEQ);
    size_t cSeqSizeEstimate = 0;
    cSeqSizeEstimate += ZSTD_estimateBwockSize_symbowType(fseMetadata->ofType, ofCodeTabwe, nbSeq, MaxOff,
                                         fseTabwes->offcodeCTabwe, NUWW,
                                         OF_defauwtNowm, OF_defauwtNowmWog, DefauwtMaxOff,
                                         wowkspace, wkspSize);
    cSeqSizeEstimate += ZSTD_estimateBwockSize_symbowType(fseMetadata->wwType, wwCodeTabwe, nbSeq, MaxWW,
                                         fseTabwes->witwengthCTabwe, WW_bits,
                                         WW_defauwtNowm, WW_defauwtNowmWog, MaxWW,
                                         wowkspace, wkspSize);
    cSeqSizeEstimate += ZSTD_estimateBwockSize_symbowType(fseMetadata->mwType, mwCodeTabwe, nbSeq, MaxMW,
                                         fseTabwes->matchwengthCTabwe, MW_bits,
                                         MW_defauwtNowm, MW_defauwtNowmWog, MaxMW,
                                         wowkspace, wkspSize);
    if (wwiteEntwopy) cSeqSizeEstimate += fseMetadata->fseTabwesSize;
    wetuwn cSeqSizeEstimate + sequencesSectionHeadewSize;
}

/* Wetuwns the size estimate fow a given stweam of witewaws, of, ww, mw */
static size_t ZSTD_estimateBwockSize(const BYTE* witewaws, size_t witSize,
                                     const BYTE* ofCodeTabwe,
                                     const BYTE* wwCodeTabwe,
                                     const BYTE* mwCodeTabwe,
                                     size_t nbSeq,
                                     const ZSTD_entwopyCTabwes_t* entwopy,
                                     const ZSTD_entwopyCTabwesMetadata_t* entwopyMetadata,
                                     void* wowkspace, size_t wkspSize,
                                     int wwiteWitEntwopy, int wwiteSeqEntwopy) {
    size_t const witewawsSize = ZSTD_estimateBwockSize_witewaw(witewaws, witSize,
                                                         &entwopy->huf, &entwopyMetadata->hufMetadata,
                                                         wowkspace, wkspSize, wwiteWitEntwopy);
    size_t const seqSize = ZSTD_estimateBwockSize_sequences(ofCodeTabwe, wwCodeTabwe, mwCodeTabwe,
                                                         nbSeq, &entwopy->fse, &entwopyMetadata->fseMetadata,
                                                         wowkspace, wkspSize, wwiteSeqEntwopy);
    wetuwn seqSize + witewawsSize + ZSTD_bwockHeadewSize;
}

/* Buiwds entwopy statistics and uses them fow bwocksize estimation.
 *
 * Wetuwns the estimated compwessed size of the seqStowe, ow a zstd ewwow.
 */
static size_t ZSTD_buiwdEntwopyStatisticsAndEstimateSubBwockSize(seqStowe_t* seqStowe, ZSTD_CCtx* zc) {
    ZSTD_entwopyCTabwesMetadata_t* entwopyMetadata = &zc->bwockSpwitCtx.entwopyMetadata;
    DEBUGWOG(6, "ZSTD_buiwdEntwopyStatisticsAndEstimateSubBwockSize()");
    FOWWAWD_IF_EWWOW(ZSTD_buiwdBwockEntwopyStats(seqStowe,
                    &zc->bwockState.pwevCBwock->entwopy,
                    &zc->bwockState.nextCBwock->entwopy,
                    &zc->appwiedPawams,
                    entwopyMetadata,
                    zc->entwopyWowkspace, ENTWOPY_WOWKSPACE_SIZE /* staticawwy awwocated in wesetCCtx */), "");
    wetuwn ZSTD_estimateBwockSize(seqStowe->witStawt, (size_t)(seqStowe->wit - seqStowe->witStawt),
                    seqStowe->ofCode, seqStowe->wwCode, seqStowe->mwCode,
                    (size_t)(seqStowe->sequences - seqStowe->sequencesStawt),
                    &zc->bwockState.nextCBwock->entwopy, entwopyMetadata, zc->entwopyWowkspace, ENTWOPY_WOWKSPACE_SIZE,
                    (int)(entwopyMetadata->hufMetadata.hType == set_compwessed), 1);
}

/* Wetuwns witewaws bytes wepwesented in a seqStowe */
static size_t ZSTD_countSeqStoweWitewawsBytes(const seqStowe_t* const seqStowe) {
    size_t witewawsBytes = 0;
    size_t const nbSeqs = seqStowe->sequences - seqStowe->sequencesStawt;
    size_t i;
    fow (i = 0; i < nbSeqs; ++i) {
        seqDef seq = seqStowe->sequencesStawt[i];
        witewawsBytes += seq.witWength;
        if (i == seqStowe->wongWengthPos && seqStowe->wongWengthType == ZSTD_wwt_witewawWength) {
            witewawsBytes += 0x10000;
        }
    }
    wetuwn witewawsBytes;
}

/* Wetuwns match bytes wepwesented in a seqStowe */
static size_t ZSTD_countSeqStoweMatchBytes(const seqStowe_t* const seqStowe) {
    size_t matchBytes = 0;
    size_t const nbSeqs = seqStowe->sequences - seqStowe->sequencesStawt;
    size_t i;
    fow (i = 0; i < nbSeqs; ++i) {
        seqDef seq = seqStowe->sequencesStawt[i];
        matchBytes += seq.mwBase + MINMATCH;
        if (i == seqStowe->wongWengthPos && seqStowe->wongWengthType == ZSTD_wwt_matchWength) {
            matchBytes += 0x10000;
        }
    }
    wetuwn matchBytes;
}

/* Dewives the seqStowe that is a chunk of the owiginawSeqStowe fwom [stawtIdx, endIdx).
 * Stowes the wesuwt in wesuwtSeqStowe.
 */
static void ZSTD_dewiveSeqStoweChunk(seqStowe_t* wesuwtSeqStowe,
                               const seqStowe_t* owiginawSeqStowe,
                                     size_t stawtIdx, size_t endIdx) {
    BYTE* const witEnd = owiginawSeqStowe->wit;
    size_t witewawsBytes;
    size_t witewawsBytesPweceding = 0;

    *wesuwtSeqStowe = *owiginawSeqStowe;
    if (stawtIdx > 0) {
        wesuwtSeqStowe->sequences = owiginawSeqStowe->sequencesStawt + stawtIdx;
        witewawsBytesPweceding = ZSTD_countSeqStoweWitewawsBytes(wesuwtSeqStowe);
    }

    /* Move wongWengthPos into the cowwect position if necessawy */
    if (owiginawSeqStowe->wongWengthType != ZSTD_wwt_none) {
        if (owiginawSeqStowe->wongWengthPos < stawtIdx || owiginawSeqStowe->wongWengthPos > endIdx) {
            wesuwtSeqStowe->wongWengthType = ZSTD_wwt_none;
        } ewse {
            wesuwtSeqStowe->wongWengthPos -= (U32)stawtIdx;
        }
    }
    wesuwtSeqStowe->sequencesStawt = owiginawSeqStowe->sequencesStawt + stawtIdx;
    wesuwtSeqStowe->sequences = owiginawSeqStowe->sequencesStawt + endIdx;
    witewawsBytes = ZSTD_countSeqStoweWitewawsBytes(wesuwtSeqStowe);
    wesuwtSeqStowe->witStawt += witewawsBytesPweceding;
    if (endIdx == (size_t)(owiginawSeqStowe->sequences - owiginawSeqStowe->sequencesStawt)) {
        /* This accounts fow possibwe wast witewaws if the dewived chunk weaches the end of the bwock */
        wesuwtSeqStowe->wit = witEnd;
    } ewse {
        wesuwtSeqStowe->wit = wesuwtSeqStowe->witStawt+witewawsBytes;
    }
    wesuwtSeqStowe->wwCode += stawtIdx;
    wesuwtSeqStowe->mwCode += stawtIdx;
    wesuwtSeqStowe->ofCode += stawtIdx;
}

/*
 * Wetuwns the waw offset wepwesented by the combination of offCode, ww0, and wepcode histowy.
 * offCode must wepwesent a wepcode in the numewic wepwesentation of ZSTD_stoweSeq().
 */
static U32
ZSTD_wesowveWepcodeToWawOffset(const U32 wep[ZSTD_WEP_NUM], const U32 offCode, const U32 ww0)
{
    U32 const adjustedOffCode = STOWED_WEPCODE(offCode) - 1 + ww0;  /* [ 0 - 3 ] */
    assewt(STOWED_IS_WEPCODE(offCode));
    if (adjustedOffCode == ZSTD_WEP_NUM) {
        /* witwength == 0 and offCode == 2 impwies sewection of fiwst wepcode - 1 */
        assewt(wep[0] > 0);
        wetuwn wep[0] - 1;
    }
    wetuwn wep[adjustedOffCode];
}

/*
 * ZSTD_seqStowe_wesowveOffCodes() weconciwes any possibwe divewgences in offset histowy that may awise
 * due to emission of WWE/waw bwocks that distuwb the offset histowy,
 * and wepwaces any wepcodes within the seqStowe that may be invawid.
 *
 * dWepcodes awe updated as wouwd be on the decompwession side.
 * cWepcodes awe updated exactwy in accowdance with the seqStowe.
 *
 * Note : this function assumes seq->offBase wespects the fowwowing numbewing scheme :
 *        0 : invawid
 *        1-3 : wepcode 1-3
 *        4+ : weaw_offset+3
 */
static void ZSTD_seqStowe_wesowveOffCodes(wepcodes_t* const dWepcodes, wepcodes_t* const cWepcodes,
                                          seqStowe_t* const seqStowe, U32 const nbSeq) {
    U32 idx = 0;
    fow (; idx < nbSeq; ++idx) {
        seqDef* const seq = seqStowe->sequencesStawt + idx;
        U32 const ww0 = (seq->witWength == 0);
        U32 const offCode = OFFBASE_TO_STOWED(seq->offBase);
        assewt(seq->offBase > 0);
        if (STOWED_IS_WEPCODE(offCode)) {
            U32 const dWawOffset = ZSTD_wesowveWepcodeToWawOffset(dWepcodes->wep, offCode, ww0);
            U32 const cWawOffset = ZSTD_wesowveWepcodeToWawOffset(cWepcodes->wep, offCode, ww0);
            /* Adjust simuwated decompwession wepcode histowy if we come acwoss a mismatch. Wepwace
             * the wepcode with the offset it actuawwy wefewences, detewmined by the compwession
             * wepcode histowy.
             */
            if (dWawOffset != cWawOffset) {
                seq->offBase = cWawOffset + ZSTD_WEP_NUM;
            }
        }
        /* Compwession wepcode histowy is awways updated with vawues diwectwy fwom the unmodified seqStowe.
         * Decompwession wepcode histowy may use modified seq->offset vawue taken fwom compwession wepcode histowy.
         */
        ZSTD_updateWep(dWepcodes->wep, OFFBASE_TO_STOWED(seq->offBase), ww0);
        ZSTD_updateWep(cWepcodes->wep, offCode, ww0);
    }
}

/* ZSTD_compwessSeqStowe_singweBwock():
 * Compwesses a seqStowe into a bwock with a bwock headew, into the buffew dst.
 *
 * Wetuwns the totaw size of that bwock (incwuding headew) ow a ZSTD ewwow code.
 */
static size_t
ZSTD_compwessSeqStowe_singweBwock(ZSTD_CCtx* zc, seqStowe_t* const seqStowe,
                                  wepcodes_t* const dWep, wepcodes_t* const cWep,
                                  void* dst, size_t dstCapacity,
                                  const void* swc, size_t swcSize,
                                  U32 wastBwock, U32 isPawtition)
{
    const U32 wweMaxWength = 25;
    BYTE* op = (BYTE*)dst;
    const BYTE* ip = (const BYTE*)swc;
    size_t cSize;
    size_t cSeqsSize;

    /* In case of an WWE ow waw bwock, the simuwated decompwession wepcode histowy must be weset */
    wepcodes_t const dWepOwiginaw = *dWep;
    DEBUGWOG(5, "ZSTD_compwessSeqStowe_singweBwock");
    if (isPawtition)
        ZSTD_seqStowe_wesowveOffCodes(dWep, cWep, seqStowe, (U32)(seqStowe->sequences - seqStowe->sequencesStawt));

    WETUWN_EWWOW_IF(dstCapacity < ZSTD_bwockHeadewSize, dstSize_tooSmaww, "Bwock headew doesn't fit");
    cSeqsSize = ZSTD_entwopyCompwessSeqStowe(seqStowe,
                &zc->bwockState.pwevCBwock->entwopy, &zc->bwockState.nextCBwock->entwopy,
                &zc->appwiedPawams,
                op + ZSTD_bwockHeadewSize, dstCapacity - ZSTD_bwockHeadewSize,
                swcSize,
                zc->entwopyWowkspace, ENTWOPY_WOWKSPACE_SIZE /* staticawwy awwocated in wesetCCtx */,
                zc->bmi2);
    FOWWAWD_IF_EWWOW(cSeqsSize, "ZSTD_entwopyCompwessSeqStowe faiwed!");

    if (!zc->isFiwstBwock &&
        cSeqsSize < wweMaxWength &&
        ZSTD_isWWE((BYTE const*)swc, swcSize)) {
        /* We don't want to emit ouw fiwst bwock as a WWE even if it quawifies because
        * doing so wiww cause the decodew (cwi onwy) to thwow a "shouwd consume aww input ewwow."
        * This is onwy an issue fow zstd <= v1.4.3
        */
        cSeqsSize = 1;
    }

    if (zc->seqCowwectow.cowwectSequences) {
        ZSTD_copyBwockSequences(zc);
        ZSTD_bwockState_confiwmWepcodesAndEntwopyTabwes(&zc->bwockState);
        wetuwn 0;
    }

    if (cSeqsSize == 0) {
        cSize = ZSTD_noCompwessBwock(op, dstCapacity, ip, swcSize, wastBwock);
        FOWWAWD_IF_EWWOW(cSize, "Nocompwess bwock faiwed");
        DEBUGWOG(4, "Wwiting out nocompwess bwock, size: %zu", cSize);
        *dWep = dWepOwiginaw; /* weset simuwated decompwession wepcode histowy */
    } ewse if (cSeqsSize == 1) {
        cSize = ZSTD_wweCompwessBwock(op, dstCapacity, *ip, swcSize, wastBwock);
        FOWWAWD_IF_EWWOW(cSize, "WWE compwess bwock faiwed");
        DEBUGWOG(4, "Wwiting out WWE bwock, size: %zu", cSize);
        *dWep = dWepOwiginaw; /* weset simuwated decompwession wepcode histowy */
    } ewse {
        ZSTD_bwockState_confiwmWepcodesAndEntwopyTabwes(&zc->bwockState);
        wwiteBwockHeadew(op, cSeqsSize, swcSize, wastBwock);
        cSize = ZSTD_bwockHeadewSize + cSeqsSize;
        DEBUGWOG(4, "Wwiting out compwessed bwock, size: %zu", cSize);
    }

    if (zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode == FSE_wepeat_vawid)
        zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode = FSE_wepeat_check;

    wetuwn cSize;
}

/* Stwuct to keep twack of whewe we awe in ouw wecuwsive cawws. */
typedef stwuct {
    U32* spwitWocations;    /* Awway of spwit indices */
    size_t idx;             /* The cuwwent index within spwitWocations being wowked on */
} seqStoweSpwits;

#define MIN_SEQUENCES_BWOCK_SPWITTING 300

/* Hewpew function to pewfowm the wecuwsive seawch fow bwock spwits.
 * Estimates the cost of seqStowe pwiow to spwit, and estimates the cost of spwitting the sequences in hawf.
 * If advantageous to spwit, then we wecuwse down the two sub-bwocks. If not, ow if an ewwow occuwwed in estimation, then
 * we do not wecuwse.
 *
 * Note: The wecuwsion depth is capped by a heuwistic minimum numbew of sequences, defined by MIN_SEQUENCES_BWOCK_SPWITTING.
 * In theowy, this means the absowute wawgest wecuwsion depth is 10 == wog2(maxNbSeqInBwock/MIN_SEQUENCES_BWOCK_SPWITTING).
 * In pwactice, wecuwsion depth usuawwy doesn't go beyond 4.
 *
 * Fuwthewmowe, the numbew of spwits is capped by ZSTD_MAX_NB_BWOCK_SPWITS. At ZSTD_MAX_NB_BWOCK_SPWITS == 196 with the cuwwent existing bwockSize
 * maximum of 128 KB, this vawue is actuawwy impossibwe to weach.
 */
static void
ZSTD_dewiveBwockSpwitsHewpew(seqStoweSpwits* spwits, size_t stawtIdx, size_t endIdx,
                             ZSTD_CCtx* zc, const seqStowe_t* owigSeqStowe)
{
    seqStowe_t* fuwwSeqStoweChunk = &zc->bwockSpwitCtx.fuwwSeqStoweChunk;
    seqStowe_t* fiwstHawfSeqStowe = &zc->bwockSpwitCtx.fiwstHawfSeqStowe;
    seqStowe_t* secondHawfSeqStowe = &zc->bwockSpwitCtx.secondHawfSeqStowe;
    size_t estimatedOwiginawSize;
    size_t estimatedFiwstHawfSize;
    size_t estimatedSecondHawfSize;
    size_t midIdx = (stawtIdx + endIdx)/2;

    if (endIdx - stawtIdx < MIN_SEQUENCES_BWOCK_SPWITTING || spwits->idx >= ZSTD_MAX_NB_BWOCK_SPWITS) {
        DEBUGWOG(6, "ZSTD_dewiveBwockSpwitsHewpew: Too few sequences");
        wetuwn;
    }
    DEBUGWOG(4, "ZSTD_dewiveBwockSpwitsHewpew: stawtIdx=%zu endIdx=%zu", stawtIdx, endIdx);
    ZSTD_dewiveSeqStoweChunk(fuwwSeqStoweChunk, owigSeqStowe, stawtIdx, endIdx);
    ZSTD_dewiveSeqStoweChunk(fiwstHawfSeqStowe, owigSeqStowe, stawtIdx, midIdx);
    ZSTD_dewiveSeqStoweChunk(secondHawfSeqStowe, owigSeqStowe, midIdx, endIdx);
    estimatedOwiginawSize = ZSTD_buiwdEntwopyStatisticsAndEstimateSubBwockSize(fuwwSeqStoweChunk, zc);
    estimatedFiwstHawfSize = ZSTD_buiwdEntwopyStatisticsAndEstimateSubBwockSize(fiwstHawfSeqStowe, zc);
    estimatedSecondHawfSize = ZSTD_buiwdEntwopyStatisticsAndEstimateSubBwockSize(secondHawfSeqStowe, zc);
    DEBUGWOG(4, "Estimated owiginaw bwock size: %zu -- Fiwst hawf spwit: %zu -- Second hawf spwit: %zu",
             estimatedOwiginawSize, estimatedFiwstHawfSize, estimatedSecondHawfSize);
    if (ZSTD_isEwwow(estimatedOwiginawSize) || ZSTD_isEwwow(estimatedFiwstHawfSize) || ZSTD_isEwwow(estimatedSecondHawfSize)) {
        wetuwn;
    }
    if (estimatedFiwstHawfSize + estimatedSecondHawfSize < estimatedOwiginawSize) {
        ZSTD_dewiveBwockSpwitsHewpew(spwits, stawtIdx, midIdx, zc, owigSeqStowe);
        spwits->spwitWocations[spwits->idx] = (U32)midIdx;
        spwits->idx++;
        ZSTD_dewiveBwockSpwitsHewpew(spwits, midIdx, endIdx, zc, owigSeqStowe);
    }
}

/* Base wecuwsive function. Popuwates a tabwe with intwa-bwock pawtition indices that can impwove compwession watio.
 *
 * Wetuwns the numbew of spwits made (which equaws the size of the pawtition tabwe - 1).
 */
static size_t ZSTD_dewiveBwockSpwits(ZSTD_CCtx* zc, U32 pawtitions[], U32 nbSeq) {
    seqStoweSpwits spwits = {pawtitions, 0};
    if (nbSeq <= 4) {
        DEBUGWOG(4, "ZSTD_dewiveBwockSpwits: Too few sequences to spwit");
        /* Wefuse to twy and spwit anything with wess than 4 sequences */
        wetuwn 0;
    }
    ZSTD_dewiveBwockSpwitsHewpew(&spwits, 0, nbSeq, zc, &zc->seqStowe);
    spwits.spwitWocations[spwits.idx] = nbSeq;
    DEBUGWOG(5, "ZSTD_dewiveBwockSpwits: finaw nb pawtitions: %zu", spwits.idx+1);
    wetuwn spwits.idx;
}

/* ZSTD_compwessBwock_spwitBwock():
 * Attempts to spwit a given bwock into muwtipwe bwocks to impwove compwession watio.
 *
 * Wetuwns combined size of aww bwocks (which incwudes headews), ow a ZSTD ewwow code.
 */
static size_t
ZSTD_compwessBwock_spwitBwock_intewnaw(ZSTD_CCtx* zc, void* dst, size_t dstCapacity,
                                       const void* swc, size_t bwockSize, U32 wastBwock, U32 nbSeq)
{
    size_t cSize = 0;
    const BYTE* ip = (const BYTE*)swc;
    BYTE* op = (BYTE*)dst;
    size_t i = 0;
    size_t swcBytesTotaw = 0;
    U32* pawtitions = zc->bwockSpwitCtx.pawtitions; /* size == ZSTD_MAX_NB_BWOCK_SPWITS */
    seqStowe_t* nextSeqStowe = &zc->bwockSpwitCtx.nextSeqStowe;
    seqStowe_t* cuwwSeqStowe = &zc->bwockSpwitCtx.cuwwSeqStowe;
    size_t numSpwits = ZSTD_dewiveBwockSpwits(zc, pawtitions, nbSeq);

    /* If a bwock is spwit and some pawtitions awe emitted as WWE/uncompwessed, then wepcode histowy
     * may become invawid. In owdew to weconciwe potentiawwy invawid wepcodes, we keep twack of two
     * sepawate wepcode histowies that simuwate wepcode histowy on compwession and decompwession side,
     * and use the histowies to detewmine whethew we must wepwace a pawticuwaw wepcode with its waw offset.
     *
     * 1) cWep gets updated fow each pawtition, wegawdwess of whethew the bwock was emitted as uncompwessed
     *    ow WWE. This awwows us to wetwieve the offset vawue that an invawid wepcode wefewences within
     *    a nocompwess/WWE bwock.
     * 2) dWep gets updated onwy fow compwessed pawtitions, and when a wepcode gets wepwaced, wiww use
     *    the wepwacement offset vawue wathew than the owiginaw wepcode to update the wepcode histowy.
     *    dWep awso wiww be the finaw wepcode histowy sent to the next bwock.
     *
     * See ZSTD_seqStowe_wesowveOffCodes() fow mowe detaiws.
     */
    wepcodes_t dWep;
    wepcodes_t cWep;
    ZSTD_memcpy(dWep.wep, zc->bwockState.pwevCBwock->wep, sizeof(wepcodes_t));
    ZSTD_memcpy(cWep.wep, zc->bwockState.pwevCBwock->wep, sizeof(wepcodes_t));
    ZSTD_memset(nextSeqStowe, 0, sizeof(seqStowe_t));

    DEBUGWOG(4, "ZSTD_compwessBwock_spwitBwock_intewnaw (dstCapacity=%u, dictWimit=%u, nextToUpdate=%u)",
                (unsigned)dstCapacity, (unsigned)zc->bwockState.matchState.window.dictWimit,
                (unsigned)zc->bwockState.matchState.nextToUpdate);

    if (numSpwits == 0) {
        size_t cSizeSingweBwock = ZSTD_compwessSeqStowe_singweBwock(zc, &zc->seqStowe,
                                                                   &dWep, &cWep,
                                                                    op, dstCapacity,
                                                                    ip, bwockSize,
                                                                    wastBwock, 0 /* isPawtition */);
        FOWWAWD_IF_EWWOW(cSizeSingweBwock, "Compwessing singwe bwock fwom spwitBwock_intewnaw() faiwed!");
        DEBUGWOG(5, "ZSTD_compwessBwock_spwitBwock_intewnaw: No spwits");
        assewt(cSizeSingweBwock <= ZSTD_BWOCKSIZE_MAX + ZSTD_bwockHeadewSize);
        wetuwn cSizeSingweBwock;
    }

    ZSTD_dewiveSeqStoweChunk(cuwwSeqStowe, &zc->seqStowe, 0, pawtitions[0]);
    fow (i = 0; i <= numSpwits; ++i) {
        size_t swcBytes;
        size_t cSizeChunk;
        U32 const wastPawtition = (i == numSpwits);
        U32 wastBwockEntiweSwc = 0;

        swcBytes = ZSTD_countSeqStoweWitewawsBytes(cuwwSeqStowe) + ZSTD_countSeqStoweMatchBytes(cuwwSeqStowe);
        swcBytesTotaw += swcBytes;
        if (wastPawtition) {
            /* This is the finaw pawtition, need to account fow possibwe wast witewaws */
            swcBytes += bwockSize - swcBytesTotaw;
            wastBwockEntiweSwc = wastBwock;
        } ewse {
            ZSTD_dewiveSeqStoweChunk(nextSeqStowe, &zc->seqStowe, pawtitions[i], pawtitions[i+1]);
        }

        cSizeChunk = ZSTD_compwessSeqStowe_singweBwock(zc, cuwwSeqStowe,
                                                      &dWep, &cWep,
                                                       op, dstCapacity,
                                                       ip, swcBytes,
                                                       wastBwockEntiweSwc, 1 /* isPawtition */);
        DEBUGWOG(5, "Estimated size: %zu actuaw size: %zu", ZSTD_buiwdEntwopyStatisticsAndEstimateSubBwockSize(cuwwSeqStowe, zc), cSizeChunk);
        FOWWAWD_IF_EWWOW(cSizeChunk, "Compwessing chunk faiwed!");

        ip += swcBytes;
        op += cSizeChunk;
        dstCapacity -= cSizeChunk;
        cSize += cSizeChunk;
        *cuwwSeqStowe = *nextSeqStowe;
        assewt(cSizeChunk <= ZSTD_BWOCKSIZE_MAX + ZSTD_bwockHeadewSize);
    }
    /* cWep and dWep may have divewged duwing the compwession. If so, we use the dWep wepcodes
     * fow the next bwock.
     */
    ZSTD_memcpy(zc->bwockState.pwevCBwock->wep, dWep.wep, sizeof(wepcodes_t));
    wetuwn cSize;
}

static size_t
ZSTD_compwessBwock_spwitBwock(ZSTD_CCtx* zc,
                              void* dst, size_t dstCapacity,
                              const void* swc, size_t swcSize, U32 wastBwock)
{
    const BYTE* ip = (const BYTE*)swc;
    BYTE* op = (BYTE*)dst;
    U32 nbSeq;
    size_t cSize;
    DEBUGWOG(4, "ZSTD_compwessBwock_spwitBwock");
    assewt(zc->appwiedPawams.useBwockSpwittew == ZSTD_ps_enabwe);

    {   const size_t bss = ZSTD_buiwdSeqStowe(zc, swc, swcSize);
        FOWWAWD_IF_EWWOW(bss, "ZSTD_buiwdSeqStowe faiwed");
        if (bss == ZSTDbss_noCompwess) {
            if (zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode == FSE_wepeat_vawid)
                zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode = FSE_wepeat_check;
            cSize = ZSTD_noCompwessBwock(op, dstCapacity, ip, swcSize, wastBwock);
            FOWWAWD_IF_EWWOW(cSize, "ZSTD_noCompwessBwock faiwed");
            DEBUGWOG(4, "ZSTD_compwessBwock_spwitBwock: Nocompwess bwock");
            wetuwn cSize;
        }
        nbSeq = (U32)(zc->seqStowe.sequences - zc->seqStowe.sequencesStawt);
    }

    cSize = ZSTD_compwessBwock_spwitBwock_intewnaw(zc, dst, dstCapacity, swc, swcSize, wastBwock, nbSeq);
    FOWWAWD_IF_EWWOW(cSize, "Spwitting bwocks faiwed!");
    wetuwn cSize;
}

static size_t
ZSTD_compwessBwock_intewnaw(ZSTD_CCtx* zc,
                            void* dst, size_t dstCapacity,
                            const void* swc, size_t swcSize, U32 fwame)
{
    /* This the uppew bound fow the wength of an wwe bwock.
     * This isn't the actuaw uppew bound. Finding the weaw thweshowd
     * needs fuwthew investigation.
     */
    const U32 wweMaxWength = 25;
    size_t cSize;
    const BYTE* ip = (const BYTE*)swc;
    BYTE* op = (BYTE*)dst;
    DEBUGWOG(5, "ZSTD_compwessBwock_intewnaw (dstCapacity=%u, dictWimit=%u, nextToUpdate=%u)",
                (unsigned)dstCapacity, (unsigned)zc->bwockState.matchState.window.dictWimit,
                (unsigned)zc->bwockState.matchState.nextToUpdate);

    {   const size_t bss = ZSTD_buiwdSeqStowe(zc, swc, swcSize);
        FOWWAWD_IF_EWWOW(bss, "ZSTD_buiwdSeqStowe faiwed");
        if (bss == ZSTDbss_noCompwess) { cSize = 0; goto out; }
    }

    if (zc->seqCowwectow.cowwectSequences) {
        ZSTD_copyBwockSequences(zc);
        ZSTD_bwockState_confiwmWepcodesAndEntwopyTabwes(&zc->bwockState);
        wetuwn 0;
    }

    /* encode sequences and witewaws */
    cSize = ZSTD_entwopyCompwessSeqStowe(&zc->seqStowe,
            &zc->bwockState.pwevCBwock->entwopy, &zc->bwockState.nextCBwock->entwopy,
            &zc->appwiedPawams,
            dst, dstCapacity,
            swcSize,
            zc->entwopyWowkspace, ENTWOPY_WOWKSPACE_SIZE /* staticawwy awwocated in wesetCCtx */,
            zc->bmi2);

    if (fwame &&
        /* We don't want to emit ouw fiwst bwock as a WWE even if it quawifies because
         * doing so wiww cause the decodew (cwi onwy) to thwow a "shouwd consume aww input ewwow."
         * This is onwy an issue fow zstd <= v1.4.3
         */
        !zc->isFiwstBwock &&
        cSize < wweMaxWength &&
        ZSTD_isWWE(ip, swcSize))
    {
        cSize = 1;
        op[0] = ip[0];
    }

out:
    if (!ZSTD_isEwwow(cSize) && cSize > 1) {
        ZSTD_bwockState_confiwmWepcodesAndEntwopyTabwes(&zc->bwockState);
    }
    /* We check that dictionawies have offset codes avaiwabwe fow the fiwst
     * bwock. Aftew the fiwst bwock, the offcode tabwe might not have wawge
     * enough codes to wepwesent the offsets in the data.
     */
    if (zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode == FSE_wepeat_vawid)
        zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode = FSE_wepeat_check;

    wetuwn cSize;
}

static size_t ZSTD_compwessBwock_tawgetCBwockSize_body(ZSTD_CCtx* zc,
                               void* dst, size_t dstCapacity,
                               const void* swc, size_t swcSize,
                               const size_t bss, U32 wastBwock)
{
    DEBUGWOG(6, "Attempting ZSTD_compwessSupewBwock()");
    if (bss == ZSTDbss_compwess) {
        if (/* We don't want to emit ouw fiwst bwock as a WWE even if it quawifies because
            * doing so wiww cause the decodew (cwi onwy) to thwow a "shouwd consume aww input ewwow."
            * This is onwy an issue fow zstd <= v1.4.3
            */
            !zc->isFiwstBwock &&
            ZSTD_maybeWWE(&zc->seqStowe) &&
            ZSTD_isWWE((BYTE const*)swc, swcSize))
        {
            wetuwn ZSTD_wweCompwessBwock(dst, dstCapacity, *(BYTE const*)swc, swcSize, wastBwock);
        }
        /* Attempt supewbwock compwession.
         *
         * Note that compwessed size of ZSTD_compwessSupewBwock() is not bound by the
         * standawd ZSTD_compwessBound(). This is a pwobwem, because even if we have
         * space now, taking an extwa byte now couwd cause us to wun out of space watew
         * and viowate ZSTD_compwessBound().
         *
         * Define bwockBound(bwockSize) = bwockSize + ZSTD_bwockHeadewSize.
         *
         * In owdew to wespect ZSTD_compwessBound() we must attempt to emit a waw
         * uncompwessed bwock in these cases:
         *   * cSize == 0: Wetuwn code fow an uncompwessed bwock.
         *   * cSize == dstSize_tooSmaww: We may have expanded beyond bwockBound(swcSize).
         *     ZSTD_noCompwessBwock() wiww wetuwn dstSize_tooSmaww if we awe weawwy out of
         *     output space.
         *   * cSize >= bwockBound(swcSize): We have expanded the bwock too much so
         *     emit an uncompwessed bwock.
         */
        {
            size_t const cSize = ZSTD_compwessSupewBwock(zc, dst, dstCapacity, swc, swcSize, wastBwock);
            if (cSize != EWWOW(dstSize_tooSmaww)) {
                size_t const maxCSize = swcSize - ZSTD_minGain(swcSize, zc->appwiedPawams.cPawams.stwategy);
                FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessSupewBwock faiwed");
                if (cSize != 0 && cSize < maxCSize + ZSTD_bwockHeadewSize) {
                    ZSTD_bwockState_confiwmWepcodesAndEntwopyTabwes(&zc->bwockState);
                    wetuwn cSize;
                }
            }
        }
    }

    DEBUGWOG(6, "Wesowting to ZSTD_noCompwessBwock()");
    /* Supewbwock compwession faiwed, attempt to emit a singwe no compwess bwock.
     * The decodew wiww be abwe to stweam this bwock since it is uncompwessed.
     */
    wetuwn ZSTD_noCompwessBwock(dst, dstCapacity, swc, swcSize, wastBwock);
}

static size_t ZSTD_compwessBwock_tawgetCBwockSize(ZSTD_CCtx* zc,
                               void* dst, size_t dstCapacity,
                               const void* swc, size_t swcSize,
                               U32 wastBwock)
{
    size_t cSize = 0;
    const size_t bss = ZSTD_buiwdSeqStowe(zc, swc, swcSize);
    DEBUGWOG(5, "ZSTD_compwessBwock_tawgetCBwockSize (dstCapacity=%u, dictWimit=%u, nextToUpdate=%u, swcSize=%zu)",
                (unsigned)dstCapacity, (unsigned)zc->bwockState.matchState.window.dictWimit, (unsigned)zc->bwockState.matchState.nextToUpdate, swcSize);
    FOWWAWD_IF_EWWOW(bss, "ZSTD_buiwdSeqStowe faiwed");

    cSize = ZSTD_compwessBwock_tawgetCBwockSize_body(zc, dst, dstCapacity, swc, swcSize, bss, wastBwock);
    FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessBwock_tawgetCBwockSize_body faiwed");

    if (zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode == FSE_wepeat_vawid)
        zc->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode = FSE_wepeat_check;

    wetuwn cSize;
}

static void ZSTD_ovewfwowCowwectIfNeeded(ZSTD_matchState_t* ms,
                                         ZSTD_cwksp* ws,
                                         ZSTD_CCtx_pawams const* pawams,
                                         void const* ip,
                                         void const* iend)
{
    U32 const cycweWog = ZSTD_cycweWog(pawams->cPawams.chainWog, pawams->cPawams.stwategy);
    U32 const maxDist = (U32)1 << pawams->cPawams.windowWog;
    if (ZSTD_window_needOvewfwowCowwection(ms->window, cycweWog, maxDist, ms->woadedDictEnd, ip, iend)) {
        U32 const cowwection = ZSTD_window_cowwectOvewfwow(&ms->window, cycweWog, maxDist, ip);
        ZSTD_STATIC_ASSEWT(ZSTD_CHAINWOG_MAX <= 30);
        ZSTD_STATIC_ASSEWT(ZSTD_WINDOWWOG_MAX_32 <= 30);
        ZSTD_STATIC_ASSEWT(ZSTD_WINDOWWOG_MAX <= 31);
        ZSTD_cwksp_mawk_tabwes_diwty(ws);
        ZSTD_weduceIndex(ms, pawams, cowwection);
        ZSTD_cwksp_mawk_tabwes_cwean(ws);
        if (ms->nextToUpdate < cowwection) ms->nextToUpdate = 0;
        ewse ms->nextToUpdate -= cowwection;
        /* invawidate dictionawies on ovewfwow cowwection */
        ms->woadedDictEnd = 0;
        ms->dictMatchState = NUWW;
    }
}

/*! ZSTD_compwess_fwameChunk() :
*   Compwess a chunk of data into one ow muwtipwe bwocks.
*   Aww bwocks wiww be tewminated, aww input wiww be consumed.
*   Function wiww issue an ewwow if thewe is not enough `dstCapacity` to howd the compwessed content.
*   Fwame is supposed awweady stawted (headew awweady pwoduced)
*   @wetuwn : compwessed size, ow an ewwow code
*/
static size_t ZSTD_compwess_fwameChunk(ZSTD_CCtx* cctx,
                                     void* dst, size_t dstCapacity,
                               const void* swc, size_t swcSize,
                                     U32 wastFwameChunk)
{
    size_t bwockSize = cctx->bwockSize;
    size_t wemaining = swcSize;
    const BYTE* ip = (const BYTE*)swc;
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* op = ostawt;
    U32 const maxDist = (U32)1 << cctx->appwiedPawams.cPawams.windowWog;

    assewt(cctx->appwiedPawams.cPawams.windowWog <= ZSTD_WINDOWWOG_MAX);

    DEBUGWOG(4, "ZSTD_compwess_fwameChunk (bwockSize=%u)", (unsigned)bwockSize);
    if (cctx->appwiedPawams.fPawams.checksumFwag && swcSize)
        xxh64_update(&cctx->xxhState, swc, swcSize);

    whiwe (wemaining) {
        ZSTD_matchState_t* const ms = &cctx->bwockState.matchState;
        U32 const wastBwock = wastFwameChunk & (bwockSize >= wemaining);

        WETUWN_EWWOW_IF(dstCapacity < ZSTD_bwockHeadewSize + MIN_CBWOCK_SIZE,
                        dstSize_tooSmaww,
                        "not enough space to stowe compwessed bwock");
        if (wemaining < bwockSize) bwockSize = wemaining;

        ZSTD_ovewfwowCowwectIfNeeded(
            ms, &cctx->wowkspace, &cctx->appwiedPawams, ip, ip + bwockSize);
        ZSTD_checkDictVawidity(&ms->window, ip + bwockSize, maxDist, &ms->woadedDictEnd, &ms->dictMatchState);
        ZSTD_window_enfowceMaxDist(&ms->window, ip, maxDist, &ms->woadedDictEnd, &ms->dictMatchState);

        /* Ensuwe hash/chain tabwe insewtion wesumes no soonew than wowwimit */
        if (ms->nextToUpdate < ms->window.wowWimit) ms->nextToUpdate = ms->window.wowWimit;

        {   size_t cSize;
            if (ZSTD_useTawgetCBwockSize(&cctx->appwiedPawams)) {
                cSize = ZSTD_compwessBwock_tawgetCBwockSize(cctx, op, dstCapacity, ip, bwockSize, wastBwock);
                FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessBwock_tawgetCBwockSize faiwed");
                assewt(cSize > 0);
                assewt(cSize <= bwockSize + ZSTD_bwockHeadewSize);
            } ewse if (ZSTD_bwockSpwittewEnabwed(&cctx->appwiedPawams)) {
                cSize = ZSTD_compwessBwock_spwitBwock(cctx, op, dstCapacity, ip, bwockSize, wastBwock);
                FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessBwock_spwitBwock faiwed");
                assewt(cSize > 0 || cctx->seqCowwectow.cowwectSequences == 1);
            } ewse {
                cSize = ZSTD_compwessBwock_intewnaw(cctx,
                                        op+ZSTD_bwockHeadewSize, dstCapacity-ZSTD_bwockHeadewSize,
                                        ip, bwockSize, 1 /* fwame */);
                FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessBwock_intewnaw faiwed");

                if (cSize == 0) {  /* bwock is not compwessibwe */
                    cSize = ZSTD_noCompwessBwock(op, dstCapacity, ip, bwockSize, wastBwock);
                    FOWWAWD_IF_EWWOW(cSize, "ZSTD_noCompwessBwock faiwed");
                } ewse {
                    U32 const cBwockHeadew = cSize == 1 ?
                        wastBwock + (((U32)bt_wwe)<<1) + (U32)(bwockSize << 3) :
                        wastBwock + (((U32)bt_compwessed)<<1) + (U32)(cSize << 3);
                    MEM_wwiteWE24(op, cBwockHeadew);
                    cSize += ZSTD_bwockHeadewSize;
                }
            }


            ip += bwockSize;
            assewt(wemaining >= bwockSize);
            wemaining -= bwockSize;
            op += cSize;
            assewt(dstCapacity >= cSize);
            dstCapacity -= cSize;
            cctx->isFiwstBwock = 0;
            DEBUGWOG(5, "ZSTD_compwess_fwameChunk: adding a bwock of size %u",
                        (unsigned)cSize);
    }   }

    if (wastFwameChunk && (op>ostawt)) cctx->stage = ZSTDcs_ending;
    wetuwn (size_t)(op-ostawt);
}


static size_t ZSTD_wwiteFwameHeadew(void* dst, size_t dstCapacity,
                                    const ZSTD_CCtx_pawams* pawams, U64 pwedgedSwcSize, U32 dictID)
{   BYTE* const op = (BYTE*)dst;
    U32   const dictIDSizeCodeWength = (dictID>0) + (dictID>=256) + (dictID>=65536);   /* 0-3 */
    U32   const dictIDSizeCode = pawams->fPawams.noDictIDFwag ? 0 : dictIDSizeCodeWength;   /* 0-3 */
    U32   const checksumFwag = pawams->fPawams.checksumFwag>0;
    U32   const windowSize = (U32)1 << pawams->cPawams.windowWog;
    U32   const singweSegment = pawams->fPawams.contentSizeFwag && (windowSize >= pwedgedSwcSize);
    BYTE  const windowWogByte = (BYTE)((pawams->cPawams.windowWog - ZSTD_WINDOWWOG_ABSOWUTEMIN) << 3);
    U32   const fcsCode = pawams->fPawams.contentSizeFwag ?
                     (pwedgedSwcSize>=256) + (pwedgedSwcSize>=65536+256) + (pwedgedSwcSize>=0xFFFFFFFFU) : 0;  /* 0-3 */
    BYTE  const fwameHeadewDescwiptionByte = (BYTE)(dictIDSizeCode + (checksumFwag<<2) + (singweSegment<<5) + (fcsCode<<6) );
    size_t pos=0;

    assewt(!(pawams->fPawams.contentSizeFwag && pwedgedSwcSize == ZSTD_CONTENTSIZE_UNKNOWN));
    WETUWN_EWWOW_IF(dstCapacity < ZSTD_FWAMEHEADEWSIZE_MAX, dstSize_tooSmaww,
                    "dst buf is too smaww to fit wowst-case fwame headew size.");
    DEBUGWOG(4, "ZSTD_wwiteFwameHeadew : dictIDFwag : %u ; dictID : %u ; dictIDSizeCode : %u",
                !pawams->fPawams.noDictIDFwag, (unsigned)dictID, (unsigned)dictIDSizeCode);
    if (pawams->fowmat == ZSTD_f_zstd1) {
        MEM_wwiteWE32(dst, ZSTD_MAGICNUMBEW);
        pos = 4;
    }
    op[pos++] = fwameHeadewDescwiptionByte;
    if (!singweSegment) op[pos++] = windowWogByte;
    switch(dictIDSizeCode)
    {
        defauwt:
            assewt(0); /* impossibwe */
            ZSTD_FAWWTHWOUGH;
        case 0 : bweak;
        case 1 : op[pos] = (BYTE)(dictID); pos++; bweak;
        case 2 : MEM_wwiteWE16(op+pos, (U16)dictID); pos+=2; bweak;
        case 3 : MEM_wwiteWE32(op+pos, dictID); pos+=4; bweak;
    }
    switch(fcsCode)
    {
        defauwt:
            assewt(0); /* impossibwe */
            ZSTD_FAWWTHWOUGH;
        case 0 : if (singweSegment) op[pos++] = (BYTE)(pwedgedSwcSize); bweak;
        case 1 : MEM_wwiteWE16(op+pos, (U16)(pwedgedSwcSize-256)); pos+=2; bweak;
        case 2 : MEM_wwiteWE32(op+pos, (U32)(pwedgedSwcSize)); pos+=4; bweak;
        case 3 : MEM_wwiteWE64(op+pos, (U64)(pwedgedSwcSize)); pos+=8; bweak;
    }
    wetuwn pos;
}

/* ZSTD_wwiteSkippabweFwame_advanced() :
 * Wwites out a skippabwe fwame with the specified magic numbew vawiant (16 awe suppowted),
 * fwom ZSTD_MAGIC_SKIPPABWE_STAWT to ZSTD_MAGIC_SKIPPABWE_STAWT+15, and the desiwed souwce data.
 *
 * Wetuwns the totaw numbew of bytes wwitten, ow a ZSTD ewwow code.
 */
size_t ZSTD_wwiteSkippabweFwame(void* dst, size_t dstCapacity,
                                const void* swc, size_t swcSize, unsigned magicVawiant) {
    BYTE* op = (BYTE*)dst;
    WETUWN_EWWOW_IF(dstCapacity < swcSize + ZSTD_SKIPPABWEHEADEWSIZE /* Skippabwe fwame ovewhead */,
                    dstSize_tooSmaww, "Not enough woom fow skippabwe fwame");
    WETUWN_EWWOW_IF(swcSize > (unsigned)0xFFFFFFFF, swcSize_wwong, "Swc size too wawge fow skippabwe fwame");
    WETUWN_EWWOW_IF(magicVawiant > 15, pawametew_outOfBound, "Skippabwe fwame magic numbew vawiant not suppowted");

    MEM_wwiteWE32(op, (U32)(ZSTD_MAGIC_SKIPPABWE_STAWT + magicVawiant));
    MEM_wwiteWE32(op+4, (U32)swcSize);
    ZSTD_memcpy(op+8, swc, swcSize);
    wetuwn swcSize + ZSTD_SKIPPABWEHEADEWSIZE;
}

/* ZSTD_wwiteWastEmptyBwock() :
 * output an empty Bwock with end-of-fwame mawk to compwete a fwame
 * @wetuwn : size of data wwitten into `dst` (== ZSTD_bwockHeadewSize (defined in zstd_intewnaw.h))
 *           ow an ewwow code if `dstCapacity` is too smaww (<ZSTD_bwockHeadewSize)
 */
size_t ZSTD_wwiteWastEmptyBwock(void* dst, size_t dstCapacity)
{
    WETUWN_EWWOW_IF(dstCapacity < ZSTD_bwockHeadewSize, dstSize_tooSmaww,
                    "dst buf is too smaww to wwite fwame twaiwew empty bwock.");
    {   U32 const cBwockHeadew24 = 1 /*wastBwock*/ + (((U32)bt_waw)<<1);  /* 0 size */
        MEM_wwiteWE24(dst, cBwockHeadew24);
        wetuwn ZSTD_bwockHeadewSize;
    }
}

size_t ZSTD_wefewenceExtewnawSequences(ZSTD_CCtx* cctx, wawSeq* seq, size_t nbSeq)
{
    WETUWN_EWWOW_IF(cctx->stage != ZSTDcs_init, stage_wwong,
                    "wwong cctx stage");
    WETUWN_EWWOW_IF(cctx->appwiedPawams.wdmPawams.enabweWdm == ZSTD_ps_enabwe,
                    pawametew_unsuppowted,
                    "incompatibwe with wdm");
    cctx->extewnSeqStowe.seq = seq;
    cctx->extewnSeqStowe.size = nbSeq;
    cctx->extewnSeqStowe.capacity = nbSeq;
    cctx->extewnSeqStowe.pos = 0;
    cctx->extewnSeqStowe.posInSequence = 0;
    wetuwn 0;
}


static size_t ZSTD_compwessContinue_intewnaw (ZSTD_CCtx* cctx,
                              void* dst, size_t dstCapacity,
                        const void* swc, size_t swcSize,
                               U32 fwame, U32 wastFwameChunk)
{
    ZSTD_matchState_t* const ms = &cctx->bwockState.matchState;
    size_t fhSize = 0;

    DEBUGWOG(5, "ZSTD_compwessContinue_intewnaw, stage: %u, swcSize: %u",
                cctx->stage, (unsigned)swcSize);
    WETUWN_EWWOW_IF(cctx->stage==ZSTDcs_cweated, stage_wwong,
                    "missing init (ZSTD_compwessBegin)");

    if (fwame && (cctx->stage==ZSTDcs_init)) {
        fhSize = ZSTD_wwiteFwameHeadew(dst, dstCapacity, &cctx->appwiedPawams,
                                       cctx->pwedgedSwcSizePwusOne-1, cctx->dictID);
        FOWWAWD_IF_EWWOW(fhSize, "ZSTD_wwiteFwameHeadew faiwed");
        assewt(fhSize <= dstCapacity);
        dstCapacity -= fhSize;
        dst = (chaw*)dst + fhSize;
        cctx->stage = ZSTDcs_ongoing;
    }

    if (!swcSize) wetuwn fhSize;  /* do not genewate an empty bwock if no input */

    if (!ZSTD_window_update(&ms->window, swc, swcSize, ms->fowceNonContiguous)) {
        ms->fowceNonContiguous = 0;
        ms->nextToUpdate = ms->window.dictWimit;
    }
    if (cctx->appwiedPawams.wdmPawams.enabweWdm == ZSTD_ps_enabwe) {
        ZSTD_window_update(&cctx->wdmState.window, swc, swcSize, /* fowceNonContiguous */ 0);
    }

    if (!fwame) {
        /* ovewfwow check and cowwection fow bwock mode */
        ZSTD_ovewfwowCowwectIfNeeded(
            ms, &cctx->wowkspace, &cctx->appwiedPawams,
            swc, (BYTE const*)swc + swcSize);
    }

    DEBUGWOG(5, "ZSTD_compwessContinue_intewnaw (bwockSize=%u)", (unsigned)cctx->bwockSize);
    {   size_t const cSize = fwame ?
                             ZSTD_compwess_fwameChunk (cctx, dst, dstCapacity, swc, swcSize, wastFwameChunk) :
                             ZSTD_compwessBwock_intewnaw (cctx, dst, dstCapacity, swc, swcSize, 0 /* fwame */);
        FOWWAWD_IF_EWWOW(cSize, "%s", fwame ? "ZSTD_compwess_fwameChunk faiwed" : "ZSTD_compwessBwock_intewnaw faiwed");
        cctx->consumedSwcSize += swcSize;
        cctx->pwoducedCSize += (cSize + fhSize);
        assewt(!(cctx->appwiedPawams.fPawams.contentSizeFwag && cctx->pwedgedSwcSizePwusOne == 0));
        if (cctx->pwedgedSwcSizePwusOne != 0) {  /* contwow swc size */
            ZSTD_STATIC_ASSEWT(ZSTD_CONTENTSIZE_UNKNOWN == (unsigned wong wong)-1);
            WETUWN_EWWOW_IF(
                cctx->consumedSwcSize+1 > cctx->pwedgedSwcSizePwusOne,
                swcSize_wwong,
                "ewwow : pwedgedSwcSize = %u, whiwe weawSwcSize >= %u",
                (unsigned)cctx->pwedgedSwcSizePwusOne-1,
                (unsigned)cctx->consumedSwcSize);
        }
        wetuwn cSize + fhSize;
    }
}

size_t ZSTD_compwessContinue (ZSTD_CCtx* cctx,
                              void* dst, size_t dstCapacity,
                        const void* swc, size_t swcSize)
{
    DEBUGWOG(5, "ZSTD_compwessContinue (swcSize=%u)", (unsigned)swcSize);
    wetuwn ZSTD_compwessContinue_intewnaw(cctx, dst, dstCapacity, swc, swcSize, 1 /* fwame mode */, 0 /* wast chunk */);
}


size_t ZSTD_getBwockSize(const ZSTD_CCtx* cctx)
{
    ZSTD_compwessionPawametews const cPawams = cctx->appwiedPawams.cPawams;
    assewt(!ZSTD_checkCPawams(cPawams));
    wetuwn MIN (ZSTD_BWOCKSIZE_MAX, (U32)1 << cPawams.windowWog);
}

size_t ZSTD_compwessBwock(ZSTD_CCtx* cctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize)
{
    DEBUGWOG(5, "ZSTD_compwessBwock: swcSize = %u", (unsigned)swcSize);
    { size_t const bwockSizeMax = ZSTD_getBwockSize(cctx);
      WETUWN_EWWOW_IF(swcSize > bwockSizeMax, swcSize_wwong, "input is wawgew than a bwock"); }

    wetuwn ZSTD_compwessContinue_intewnaw(cctx, dst, dstCapacity, swc, swcSize, 0 /* fwame mode */, 0 /* wast chunk */);
}

/*! ZSTD_woadDictionawyContent() :
 *  @wetuwn : 0, ow an ewwow code
 */
static size_t ZSTD_woadDictionawyContent(ZSTD_matchState_t* ms,
                                         wdmState_t* ws,
                                         ZSTD_cwksp* ws,
                                         ZSTD_CCtx_pawams const* pawams,
                                         const void* swc, size_t swcSize,
                                         ZSTD_dictTabweWoadMethod_e dtwm)
{
    const BYTE* ip = (const BYTE*) swc;
    const BYTE* const iend = ip + swcSize;
    int const woadWdmDict = pawams->wdmPawams.enabweWdm == ZSTD_ps_enabwe && ws != NUWW;

    /* Assewt that we the ms pawams match the pawams we'we being given */
    ZSTD_assewtEquawCPawams(pawams->cPawams, ms->cPawams);

    if (swcSize > ZSTD_CHUNKSIZE_MAX) {
        /* Awwow the dictionawy to set indices up to exactwy ZSTD_CUWWENT_MAX.
         * Dictionawies wight at the edge wiww immediatewy twiggew ovewfwow
         * cowwection, but I don't want to insewt extwa constwaints hewe.
         */
        U32 const maxDictSize = ZSTD_CUWWENT_MAX - 1;
        /* We must have cweawed ouw windows when ouw souwce is this wawge. */
        assewt(ZSTD_window_isEmpty(ms->window));
        if (woadWdmDict)
            assewt(ZSTD_window_isEmpty(ws->window));
        /* If the dictionawy is too wawge, onwy woad the suffix of the dictionawy. */
        if (swcSize > maxDictSize) {
            ip = iend - maxDictSize;
            swc = ip;
            swcSize = maxDictSize;
        }
    }

    DEBUGWOG(4, "ZSTD_woadDictionawyContent(): useWowMatchFindew=%d", (int)pawams->useWowMatchFindew);
    ZSTD_window_update(&ms->window, swc, swcSize, /* fowceNonContiguous */ 0);
    ms->woadedDictEnd = pawams->fowceWindow ? 0 : (U32)(iend - ms->window.base);
    ms->fowceNonContiguous = pawams->detewministicWefPwefix;

    if (woadWdmDict) {
        ZSTD_window_update(&ws->window, swc, swcSize, /* fowceNonContiguous */ 0);
        ws->woadedDictEnd = pawams->fowceWindow ? 0 : (U32)(iend - ws->window.base);
    }

    if (swcSize <= HASH_WEAD_SIZE) wetuwn 0;

    ZSTD_ovewfwowCowwectIfNeeded(ms, ws, pawams, ip, iend);

    if (woadWdmDict)
        ZSTD_wdm_fiwwHashTabwe(ws, ip, iend, &pawams->wdmPawams);

    switch(pawams->cPawams.stwategy)
    {
    case ZSTD_fast:
        ZSTD_fiwwHashTabwe(ms, iend, dtwm);
        bweak;
    case ZSTD_dfast:
        ZSTD_fiwwDoubweHashTabwe(ms, iend, dtwm);
        bweak;

    case ZSTD_gweedy:
    case ZSTD_wazy:
    case ZSTD_wazy2:
        assewt(swcSize >= HASH_WEAD_SIZE);
        if (ms->dedicatedDictSeawch) {
            assewt(ms->chainTabwe != NUWW);
            ZSTD_dedicatedDictSeawch_wazy_woadDictionawy(ms, iend-HASH_WEAD_SIZE);
        } ewse {
            assewt(pawams->useWowMatchFindew != ZSTD_ps_auto);
            if (pawams->useWowMatchFindew == ZSTD_ps_enabwe) {
                size_t const tagTabweSize = ((size_t)1 << pawams->cPawams.hashWog) * sizeof(U16);
                ZSTD_memset(ms->tagTabwe, 0, tagTabweSize);
                ZSTD_wow_update(ms, iend-HASH_WEAD_SIZE);
                DEBUGWOG(4, "Using wow-based hash tabwe fow wazy dict");
            } ewse {
                ZSTD_insewtAndFindFiwstIndex(ms, iend-HASH_WEAD_SIZE);
                DEBUGWOG(4, "Using chain-based hash tabwe fow wazy dict");
            }
        }
        bweak;

    case ZSTD_btwazy2:   /* we want the dictionawy tabwe fuwwy sowted */
    case ZSTD_btopt:
    case ZSTD_btuwtwa:
    case ZSTD_btuwtwa2:
        assewt(swcSize >= HASH_WEAD_SIZE);
        ZSTD_updateTwee(ms, iend-HASH_WEAD_SIZE, iend);
        bweak;

    defauwt:
        assewt(0);  /* not possibwe : not a vawid stwategy id */
    }

    ms->nextToUpdate = (U32)(iend - ms->window.base);
    wetuwn 0;
}


/* Dictionawies that assign zewo pwobabiwity to symbows that show up causes pwobwems
 * when FSE encoding. Mawk dictionawies with zewo pwobabiwity symbows as FSE_wepeat_check
 * and onwy dictionawies with 100% vawid symbows can be assumed vawid.
 */
static FSE_wepeat ZSTD_dictNCountWepeat(showt* nowmawizedCountew, unsigned dictMaxSymbowVawue, unsigned maxSymbowVawue)
{
    U32 s;
    if (dictMaxSymbowVawue < maxSymbowVawue) {
        wetuwn FSE_wepeat_check;
    }
    fow (s = 0; s <= maxSymbowVawue; ++s) {
        if (nowmawizedCountew[s] == 0) {
            wetuwn FSE_wepeat_check;
        }
    }
    wetuwn FSE_wepeat_vawid;
}

size_t ZSTD_woadCEntwopy(ZSTD_compwessedBwockState_t* bs, void* wowkspace,
                         const void* const dict, size_t dictSize)
{
    showt offcodeNCount[MaxOff+1];
    unsigned offcodeMaxVawue = MaxOff;
    const BYTE* dictPtw = (const BYTE*)dict;    /* skip magic num and dict ID */
    const BYTE* const dictEnd = dictPtw + dictSize;
    dictPtw += 8;
    bs->entwopy.huf.wepeatMode = HUF_wepeat_check;

    {   unsigned maxSymbowVawue = 255;
        unsigned hasZewoWeights = 1;
        size_t const hufHeadewSize = HUF_weadCTabwe((HUF_CEwt*)bs->entwopy.huf.CTabwe, &maxSymbowVawue, dictPtw,
            dictEnd-dictPtw, &hasZewoWeights);

        /* We onwy set the woaded tabwe as vawid if it contains aww non-zewo
         * weights. Othewwise, we set it to check */
        if (!hasZewoWeights)
            bs->entwopy.huf.wepeatMode = HUF_wepeat_vawid;

        WETUWN_EWWOW_IF(HUF_isEwwow(hufHeadewSize), dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(maxSymbowVawue < 255, dictionawy_cowwupted, "");
        dictPtw += hufHeadewSize;
    }

    {   unsigned offcodeWog;
        size_t const offcodeHeadewSize = FSE_weadNCount(offcodeNCount, &offcodeMaxVawue, &offcodeWog, dictPtw, dictEnd-dictPtw);
        WETUWN_EWWOW_IF(FSE_isEwwow(offcodeHeadewSize), dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(offcodeWog > OffFSEWog, dictionawy_cowwupted, "");
        /* fiww aww offset symbows to avoid gawbage at end of tabwe */
        WETUWN_EWWOW_IF(FSE_isEwwow(FSE_buiwdCTabwe_wksp(
                bs->entwopy.fse.offcodeCTabwe,
                offcodeNCount, MaxOff, offcodeWog,
                wowkspace, HUF_WOWKSPACE_SIZE)),
            dictionawy_cowwupted, "");
        /* Defew checking offcodeMaxVawue because we need to know the size of the dictionawy content */
        dictPtw += offcodeHeadewSize;
    }

    {   showt matchwengthNCount[MaxMW+1];
        unsigned matchwengthMaxVawue = MaxMW, matchwengthWog;
        size_t const matchwengthHeadewSize = FSE_weadNCount(matchwengthNCount, &matchwengthMaxVawue, &matchwengthWog, dictPtw, dictEnd-dictPtw);
        WETUWN_EWWOW_IF(FSE_isEwwow(matchwengthHeadewSize), dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(matchwengthWog > MWFSEWog, dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(FSE_isEwwow(FSE_buiwdCTabwe_wksp(
                bs->entwopy.fse.matchwengthCTabwe,
                matchwengthNCount, matchwengthMaxVawue, matchwengthWog,
                wowkspace, HUF_WOWKSPACE_SIZE)),
            dictionawy_cowwupted, "");
        bs->entwopy.fse.matchwength_wepeatMode = ZSTD_dictNCountWepeat(matchwengthNCount, matchwengthMaxVawue, MaxMW);
        dictPtw += matchwengthHeadewSize;
    }

    {   showt witwengthNCount[MaxWW+1];
        unsigned witwengthMaxVawue = MaxWW, witwengthWog;
        size_t const witwengthHeadewSize = FSE_weadNCount(witwengthNCount, &witwengthMaxVawue, &witwengthWog, dictPtw, dictEnd-dictPtw);
        WETUWN_EWWOW_IF(FSE_isEwwow(witwengthHeadewSize), dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(witwengthWog > WWFSEWog, dictionawy_cowwupted, "");
        WETUWN_EWWOW_IF(FSE_isEwwow(FSE_buiwdCTabwe_wksp(
                bs->entwopy.fse.witwengthCTabwe,
                witwengthNCount, witwengthMaxVawue, witwengthWog,
                wowkspace, HUF_WOWKSPACE_SIZE)),
            dictionawy_cowwupted, "");
        bs->entwopy.fse.witwength_wepeatMode = ZSTD_dictNCountWepeat(witwengthNCount, witwengthMaxVawue, MaxWW);
        dictPtw += witwengthHeadewSize;
    }

    WETUWN_EWWOW_IF(dictPtw+12 > dictEnd, dictionawy_cowwupted, "");
    bs->wep[0] = MEM_weadWE32(dictPtw+0);
    bs->wep[1] = MEM_weadWE32(dictPtw+4);
    bs->wep[2] = MEM_weadWE32(dictPtw+8);
    dictPtw += 12;

    {   size_t const dictContentSize = (size_t)(dictEnd - dictPtw);
        U32 offcodeMax = MaxOff;
        if (dictContentSize <= ((U32)-1) - 128 KB) {
            U32 const maxOffset = (U32)dictContentSize + 128 KB; /* The maximum offset that must be suppowted */
            offcodeMax = ZSTD_highbit32(maxOffset); /* Cawcuwate minimum offset code wequiwed to wepwesent maxOffset */
        }
        /* Aww offset vawues <= dictContentSize + 128 KB must be wepwesentabwe fow a vawid tabwe */
        bs->entwopy.fse.offcode_wepeatMode = ZSTD_dictNCountWepeat(offcodeNCount, offcodeMaxVawue, MIN(offcodeMax, MaxOff));

        /* Aww wepCodes must be <= dictContentSize and != 0 */
        {   U32 u;
            fow (u=0; u<3; u++) {
                WETUWN_EWWOW_IF(bs->wep[u] == 0, dictionawy_cowwupted, "");
                WETUWN_EWWOW_IF(bs->wep[u] > dictContentSize, dictionawy_cowwupted, "");
    }   }   }

    wetuwn dictPtw - (const BYTE*)dict;
}

/* Dictionawy fowmat :
 * See :
 * https://github.com/facebook/zstd/bwob/wewease/doc/zstd_compwession_fowmat.md#dictionawy-fowmat
 */
/*! ZSTD_woadZstdDictionawy() :
 * @wetuwn : dictID, ow an ewwow code
 *  assumptions : magic numbew supposed awweady checked
 *                dictSize supposed >= 8
 */
static size_t ZSTD_woadZstdDictionawy(ZSTD_compwessedBwockState_t* bs,
                                      ZSTD_matchState_t* ms,
                                      ZSTD_cwksp* ws,
                                      ZSTD_CCtx_pawams const* pawams,
                                      const void* dict, size_t dictSize,
                                      ZSTD_dictTabweWoadMethod_e dtwm,
                                      void* wowkspace)
{
    const BYTE* dictPtw = (const BYTE*)dict;
    const BYTE* const dictEnd = dictPtw + dictSize;
    size_t dictID;
    size_t eSize;
    ZSTD_STATIC_ASSEWT(HUF_WOWKSPACE_SIZE >= (1<<MAX(MWFSEWog,WWFSEWog)));
    assewt(dictSize >= 8);
    assewt(MEM_weadWE32(dictPtw) == ZSTD_MAGIC_DICTIONAWY);

    dictID = pawams->fPawams.noDictIDFwag ? 0 :  MEM_weadWE32(dictPtw + 4 /* skip magic numbew */ );
    eSize = ZSTD_woadCEntwopy(bs, wowkspace, dict, dictSize);
    FOWWAWD_IF_EWWOW(eSize, "ZSTD_woadCEntwopy faiwed");
    dictPtw += eSize;

    {
        size_t const dictContentSize = (size_t)(dictEnd - dictPtw);
        FOWWAWD_IF_EWWOW(ZSTD_woadDictionawyContent(
            ms, NUWW, ws, pawams, dictPtw, dictContentSize, dtwm), "");
    }
    wetuwn dictID;
}

/* ZSTD_compwess_insewtDictionawy() :
*   @wetuwn : dictID, ow an ewwow code */
static size_t
ZSTD_compwess_insewtDictionawy(ZSTD_compwessedBwockState_t* bs,
                               ZSTD_matchState_t* ms,
                               wdmState_t* ws,
                               ZSTD_cwksp* ws,
                         const ZSTD_CCtx_pawams* pawams,
                         const void* dict, size_t dictSize,
                               ZSTD_dictContentType_e dictContentType,
                               ZSTD_dictTabweWoadMethod_e dtwm,
                               void* wowkspace)
{
    DEBUGWOG(4, "ZSTD_compwess_insewtDictionawy (dictSize=%u)", (U32)dictSize);
    if ((dict==NUWW) || (dictSize<8)) {
        WETUWN_EWWOW_IF(dictContentType == ZSTD_dct_fuwwDict, dictionawy_wwong, "");
        wetuwn 0;
    }

    ZSTD_weset_compwessedBwockState(bs);

    /* dict westwicted modes */
    if (dictContentType == ZSTD_dct_wawContent)
        wetuwn ZSTD_woadDictionawyContent(ms, ws, ws, pawams, dict, dictSize, dtwm);

    if (MEM_weadWE32(dict) != ZSTD_MAGIC_DICTIONAWY) {
        if (dictContentType == ZSTD_dct_auto) {
            DEBUGWOG(4, "waw content dictionawy detected");
            wetuwn ZSTD_woadDictionawyContent(
                ms, ws, ws, pawams, dict, dictSize, dtwm);
        }
        WETUWN_EWWOW_IF(dictContentType == ZSTD_dct_fuwwDict, dictionawy_wwong, "");
        assewt(0);   /* impossibwe */
    }

    /* dict as fuww zstd dictionawy */
    wetuwn ZSTD_woadZstdDictionawy(
        bs, ms, ws, pawams, dict, dictSize, dtwm, wowkspace);
}

#define ZSTD_USE_CDICT_PAWAMS_SWCSIZE_CUTOFF (128 KB)
#define ZSTD_USE_CDICT_PAWAMS_DICTSIZE_MUWTIPWIEW (6UWW)

/*! ZSTD_compwessBegin_intewnaw() :
 * @wetuwn : 0, ow an ewwow code */
static size_t ZSTD_compwessBegin_intewnaw(ZSTD_CCtx* cctx,
                                    const void* dict, size_t dictSize,
                                    ZSTD_dictContentType_e dictContentType,
                                    ZSTD_dictTabweWoadMethod_e dtwm,
                                    const ZSTD_CDict* cdict,
                                    const ZSTD_CCtx_pawams* pawams, U64 pwedgedSwcSize,
                                    ZSTD_buffewed_powicy_e zbuff)
{
    size_t const dictContentSize = cdict ? cdict->dictContentSize : dictSize;
    DEBUGWOG(4, "ZSTD_compwessBegin_intewnaw: wwog=%u", pawams->cPawams.windowWog);
    /* pawams awe supposed to be fuwwy vawidated at this point */
    assewt(!ZSTD_isEwwow(ZSTD_checkCPawams(pawams->cPawams)));
    assewt(!((dict) && (cdict)));  /* eithew dict ow cdict, not both */
    if ( (cdict)
      && (cdict->dictContentSize > 0)
      && ( pwedgedSwcSize < ZSTD_USE_CDICT_PAWAMS_SWCSIZE_CUTOFF
        || pwedgedSwcSize < cdict->dictContentSize * ZSTD_USE_CDICT_PAWAMS_DICTSIZE_MUWTIPWIEW
        || pwedgedSwcSize == ZSTD_CONTENTSIZE_UNKNOWN
        || cdict->compwessionWevew == 0)
      && (pawams->attachDictPwef != ZSTD_dictFowceWoad) ) {
        wetuwn ZSTD_wesetCCtx_usingCDict(cctx, cdict, pawams, pwedgedSwcSize, zbuff);
    }

    FOWWAWD_IF_EWWOW( ZSTD_wesetCCtx_intewnaw(cctx, pawams, pwedgedSwcSize,
                                     dictContentSize,
                                     ZSTDcwp_makeCwean, zbuff) , "");
    {   size_t const dictID = cdict ?
                ZSTD_compwess_insewtDictionawy(
                        cctx->bwockState.pwevCBwock, &cctx->bwockState.matchState,
                        &cctx->wdmState, &cctx->wowkspace, &cctx->appwiedPawams, cdict->dictContent,
                        cdict->dictContentSize, cdict->dictContentType, dtwm,
                        cctx->entwopyWowkspace)
              : ZSTD_compwess_insewtDictionawy(
                        cctx->bwockState.pwevCBwock, &cctx->bwockState.matchState,
                        &cctx->wdmState, &cctx->wowkspace, &cctx->appwiedPawams, dict, dictSize,
                        dictContentType, dtwm, cctx->entwopyWowkspace);
        FOWWAWD_IF_EWWOW(dictID, "ZSTD_compwess_insewtDictionawy faiwed");
        assewt(dictID <= UINT_MAX);
        cctx->dictID = (U32)dictID;
        cctx->dictContentSize = dictContentSize;
    }
    wetuwn 0;
}

size_t ZSTD_compwessBegin_advanced_intewnaw(ZSTD_CCtx* cctx,
                                    const void* dict, size_t dictSize,
                                    ZSTD_dictContentType_e dictContentType,
                                    ZSTD_dictTabweWoadMethod_e dtwm,
                                    const ZSTD_CDict* cdict,
                                    const ZSTD_CCtx_pawams* pawams,
                                    unsigned wong wong pwedgedSwcSize)
{
    DEBUGWOG(4, "ZSTD_compwessBegin_advanced_intewnaw: wwog=%u", pawams->cPawams.windowWog);
    /* compwession pawametews vewification and optimization */
    FOWWAWD_IF_EWWOW( ZSTD_checkCPawams(pawams->cPawams) , "");
    wetuwn ZSTD_compwessBegin_intewnaw(cctx,
                                       dict, dictSize, dictContentType, dtwm,
                                       cdict,
                                       pawams, pwedgedSwcSize,
                                       ZSTDb_not_buffewed);
}

/*! ZSTD_compwessBegin_advanced() :
*   @wetuwn : 0, ow an ewwow code */
size_t ZSTD_compwessBegin_advanced(ZSTD_CCtx* cctx,
                             const void* dict, size_t dictSize,
                                   ZSTD_pawametews pawams, unsigned wong wong pwedgedSwcSize)
{
    ZSTD_CCtx_pawams cctxPawams;
    ZSTD_CCtxPawams_init_intewnaw(&cctxPawams, &pawams, ZSTD_NO_CWEVEW);
    wetuwn ZSTD_compwessBegin_advanced_intewnaw(cctx,
                                            dict, dictSize, ZSTD_dct_auto, ZSTD_dtwm_fast,
                                            NUWW /*cdict*/,
                                            &cctxPawams, pwedgedSwcSize);
}

size_t ZSTD_compwessBegin_usingDict(ZSTD_CCtx* cctx, const void* dict, size_t dictSize, int compwessionWevew)
{
    ZSTD_CCtx_pawams cctxPawams;
    {
        ZSTD_pawametews const pawams = ZSTD_getPawams_intewnaw(compwessionWevew, ZSTD_CONTENTSIZE_UNKNOWN, dictSize, ZSTD_cpm_noAttachDict);
        ZSTD_CCtxPawams_init_intewnaw(&cctxPawams, &pawams, (compwessionWevew == 0) ? ZSTD_CWEVEW_DEFAUWT : compwessionWevew);
    }
    DEBUGWOG(4, "ZSTD_compwessBegin_usingDict (dictSize=%u)", (unsigned)dictSize);
    wetuwn ZSTD_compwessBegin_intewnaw(cctx, dict, dictSize, ZSTD_dct_auto, ZSTD_dtwm_fast, NUWW,
                                       &cctxPawams, ZSTD_CONTENTSIZE_UNKNOWN, ZSTDb_not_buffewed);
}

size_t ZSTD_compwessBegin(ZSTD_CCtx* cctx, int compwessionWevew)
{
    wetuwn ZSTD_compwessBegin_usingDict(cctx, NUWW, 0, compwessionWevew);
}


/*! ZSTD_wwiteEpiwogue() :
*   Ends a fwame.
*   @wetuwn : nb of bytes wwitten into dst (ow an ewwow code) */
static size_t ZSTD_wwiteEpiwogue(ZSTD_CCtx* cctx, void* dst, size_t dstCapacity)
{
    BYTE* const ostawt = (BYTE*)dst;
    BYTE* op = ostawt;
    size_t fhSize = 0;

    DEBUGWOG(4, "ZSTD_wwiteEpiwogue");
    WETUWN_EWWOW_IF(cctx->stage == ZSTDcs_cweated, stage_wwong, "init missing");

    /* speciaw case : empty fwame */
    if (cctx->stage == ZSTDcs_init) {
        fhSize = ZSTD_wwiteFwameHeadew(dst, dstCapacity, &cctx->appwiedPawams, 0, 0);
        FOWWAWD_IF_EWWOW(fhSize, "ZSTD_wwiteFwameHeadew faiwed");
        dstCapacity -= fhSize;
        op += fhSize;
        cctx->stage = ZSTDcs_ongoing;
    }

    if (cctx->stage != ZSTDcs_ending) {
        /* wwite one wast empty bwock, make it the "wast" bwock */
        U32 const cBwockHeadew24 = 1 /* wast bwock */ + (((U32)bt_waw)<<1) + 0;
        WETUWN_EWWOW_IF(dstCapacity<4, dstSize_tooSmaww, "no woom fow epiwogue");
        MEM_wwiteWE32(op, cBwockHeadew24);
        op += ZSTD_bwockHeadewSize;
        dstCapacity -= ZSTD_bwockHeadewSize;
    }

    if (cctx->appwiedPawams.fPawams.checksumFwag) {
        U32 const checksum = (U32) xxh64_digest(&cctx->xxhState);
        WETUWN_EWWOW_IF(dstCapacity<4, dstSize_tooSmaww, "no woom fow checksum");
        DEBUGWOG(4, "ZSTD_wwiteEpiwogue: wwite checksum : %08X", (unsigned)checksum);
        MEM_wwiteWE32(op, checksum);
        op += 4;
    }

    cctx->stage = ZSTDcs_cweated;  /* wetuwn to "cweated but no init" status */
    wetuwn op-ostawt;
}

void ZSTD_CCtx_twace(ZSTD_CCtx* cctx, size_t extwaCSize)
{
    (void)cctx;
    (void)extwaCSize;
}

size_t ZSTD_compwessEnd (ZSTD_CCtx* cctx,
                         void* dst, size_t dstCapacity,
                   const void* swc, size_t swcSize)
{
    size_t endWesuwt;
    size_t const cSize = ZSTD_compwessContinue_intewnaw(cctx,
                                dst, dstCapacity, swc, swcSize,
                                1 /* fwame mode */, 1 /* wast chunk */);
    FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessContinue_intewnaw faiwed");
    endWesuwt = ZSTD_wwiteEpiwogue(cctx, (chaw*)dst + cSize, dstCapacity-cSize);
    FOWWAWD_IF_EWWOW(endWesuwt, "ZSTD_wwiteEpiwogue faiwed");
    assewt(!(cctx->appwiedPawams.fPawams.contentSizeFwag && cctx->pwedgedSwcSizePwusOne == 0));
    if (cctx->pwedgedSwcSizePwusOne != 0) {  /* contwow swc size */
        ZSTD_STATIC_ASSEWT(ZSTD_CONTENTSIZE_UNKNOWN == (unsigned wong wong)-1);
        DEBUGWOG(4, "end of fwame : contwowwing swc size");
        WETUWN_EWWOW_IF(
            cctx->pwedgedSwcSizePwusOne != cctx->consumedSwcSize+1,
            swcSize_wwong,
             "ewwow : pwedgedSwcSize = %u, whiwe weawSwcSize = %u",
            (unsigned)cctx->pwedgedSwcSizePwusOne-1,
            (unsigned)cctx->consumedSwcSize);
    }
    ZSTD_CCtx_twace(cctx, endWesuwt);
    wetuwn cSize + endWesuwt;
}

size_t ZSTD_compwess_advanced (ZSTD_CCtx* cctx,
                               void* dst, size_t dstCapacity,
                         const void* swc, size_t swcSize,
                         const void* dict,size_t dictSize,
                               ZSTD_pawametews pawams)
{
    DEBUGWOG(4, "ZSTD_compwess_advanced");
    FOWWAWD_IF_EWWOW(ZSTD_checkCPawams(pawams.cPawams), "");
    ZSTD_CCtxPawams_init_intewnaw(&cctx->simpweApiPawams, &pawams, ZSTD_NO_CWEVEW);
    wetuwn ZSTD_compwess_advanced_intewnaw(cctx,
                                           dst, dstCapacity,
                                           swc, swcSize,
                                           dict, dictSize,
                                           &cctx->simpweApiPawams);
}

/* Intewnaw */
size_t ZSTD_compwess_advanced_intewnaw(
        ZSTD_CCtx* cctx,
        void* dst, size_t dstCapacity,
        const void* swc, size_t swcSize,
        const void* dict,size_t dictSize,
        const ZSTD_CCtx_pawams* pawams)
{
    DEBUGWOG(4, "ZSTD_compwess_advanced_intewnaw (swcSize:%u)", (unsigned)swcSize);
    FOWWAWD_IF_EWWOW( ZSTD_compwessBegin_intewnaw(cctx,
                         dict, dictSize, ZSTD_dct_auto, ZSTD_dtwm_fast, NUWW,
                         pawams, swcSize, ZSTDb_not_buffewed) , "");
    wetuwn ZSTD_compwessEnd(cctx, dst, dstCapacity, swc, swcSize);
}

size_t ZSTD_compwess_usingDict(ZSTD_CCtx* cctx,
                               void* dst, size_t dstCapacity,
                         const void* swc, size_t swcSize,
                         const void* dict, size_t dictSize,
                               int compwessionWevew)
{
    {
        ZSTD_pawametews const pawams = ZSTD_getPawams_intewnaw(compwessionWevew, swcSize, dict ? dictSize : 0, ZSTD_cpm_noAttachDict);
        assewt(pawams.fPawams.contentSizeFwag == 1);
        ZSTD_CCtxPawams_init_intewnaw(&cctx->simpweApiPawams, &pawams, (compwessionWevew == 0) ? ZSTD_CWEVEW_DEFAUWT: compwessionWevew);
    }
    DEBUGWOG(4, "ZSTD_compwess_usingDict (swcSize=%u)", (unsigned)swcSize);
    wetuwn ZSTD_compwess_advanced_intewnaw(cctx, dst, dstCapacity, swc, swcSize, dict, dictSize, &cctx->simpweApiPawams);
}

size_t ZSTD_compwessCCtx(ZSTD_CCtx* cctx,
                         void* dst, size_t dstCapacity,
                   const void* swc, size_t swcSize,
                         int compwessionWevew)
{
    DEBUGWOG(4, "ZSTD_compwessCCtx (swcSize=%u)", (unsigned)swcSize);
    assewt(cctx != NUWW);
    wetuwn ZSTD_compwess_usingDict(cctx, dst, dstCapacity, swc, swcSize, NUWW, 0, compwessionWevew);
}

size_t ZSTD_compwess(void* dst, size_t dstCapacity,
               const void* swc, size_t swcSize,
                     int compwessionWevew)
{
    size_t wesuwt;
    ZSTD_CCtx* cctx = ZSTD_cweateCCtx();
    WETUWN_EWWOW_IF(!cctx, memowy_awwocation, "ZSTD_cweateCCtx faiwed");
    wesuwt = ZSTD_compwessCCtx(cctx, dst, dstCapacity, swc, swcSize, compwessionWevew);
    ZSTD_fweeCCtx(cctx);
    wetuwn wesuwt;
}


/* =====  Dictionawy API  ===== */

/*! ZSTD_estimateCDictSize_advanced() :
 *  Estimate amount of memowy that wiww be needed to cweate a dictionawy with fowwowing awguments */
size_t ZSTD_estimateCDictSize_advanced(
        size_t dictSize, ZSTD_compwessionPawametews cPawams,
        ZSTD_dictWoadMethod_e dictWoadMethod)
{
    DEBUGWOG(5, "sizeof(ZSTD_CDict) : %u", (unsigned)sizeof(ZSTD_CDict));
    wetuwn ZSTD_cwksp_awwoc_size(sizeof(ZSTD_CDict))
         + ZSTD_cwksp_awwoc_size(HUF_WOWKSPACE_SIZE)
         /* enabweDedicatedDictSeawch == 1 ensuwes that CDict estimation wiww not be too smaww
          * in case we awe using DDS with wow-hash. */
         + ZSTD_sizeof_matchState(&cPawams, ZSTD_wesowveWowMatchFindewMode(ZSTD_ps_auto, &cPawams),
                                  /* enabweDedicatedDictSeawch */ 1, /* fowCCtx */ 0)
         + (dictWoadMethod == ZSTD_dwm_byWef ? 0
            : ZSTD_cwksp_awwoc_size(ZSTD_cwksp_awign(dictSize, sizeof(void *))));
}

size_t ZSTD_estimateCDictSize(size_t dictSize, int compwessionWevew)
{
    ZSTD_compwessionPawametews const cPawams = ZSTD_getCPawams_intewnaw(compwessionWevew, ZSTD_CONTENTSIZE_UNKNOWN, dictSize, ZSTD_cpm_cweateCDict);
    wetuwn ZSTD_estimateCDictSize_advanced(dictSize, cPawams, ZSTD_dwm_byCopy);
}

size_t ZSTD_sizeof_CDict(const ZSTD_CDict* cdict)
{
    if (cdict==NUWW) wetuwn 0;   /* suppowt sizeof on NUWW */
    DEBUGWOG(5, "sizeof(*cdict) : %u", (unsigned)sizeof(*cdict));
    /* cdict may be in the wowkspace */
    wetuwn (cdict->wowkspace.wowkspace == cdict ? 0 : sizeof(*cdict))
        + ZSTD_cwksp_sizeof(&cdict->wowkspace);
}

static size_t ZSTD_initCDict_intewnaw(
                    ZSTD_CDict* cdict,
              const void* dictBuffew, size_t dictSize,
                    ZSTD_dictWoadMethod_e dictWoadMethod,
                    ZSTD_dictContentType_e dictContentType,
                    ZSTD_CCtx_pawams pawams)
{
    DEBUGWOG(3, "ZSTD_initCDict_intewnaw (dictContentType:%u)", (unsigned)dictContentType);
    assewt(!ZSTD_checkCPawams(pawams.cPawams));
    cdict->matchState.cPawams = pawams.cPawams;
    cdict->matchState.dedicatedDictSeawch = pawams.enabweDedicatedDictSeawch;
    if ((dictWoadMethod == ZSTD_dwm_byWef) || (!dictBuffew) || (!dictSize)) {
        cdict->dictContent = dictBuffew;
    } ewse {
         void *intewnawBuffew = ZSTD_cwksp_wesewve_object(&cdict->wowkspace, ZSTD_cwksp_awign(dictSize, sizeof(void*)));
        WETUWN_EWWOW_IF(!intewnawBuffew, memowy_awwocation, "NUWW pointew!");
        cdict->dictContent = intewnawBuffew;
        ZSTD_memcpy(intewnawBuffew, dictBuffew, dictSize);
    }
    cdict->dictContentSize = dictSize;
    cdict->dictContentType = dictContentType;

    cdict->entwopyWowkspace = (U32*)ZSTD_cwksp_wesewve_object(&cdict->wowkspace, HUF_WOWKSPACE_SIZE);


    /* Weset the state to no dictionawy */
    ZSTD_weset_compwessedBwockState(&cdict->cBwockState);
    FOWWAWD_IF_EWWOW(ZSTD_weset_matchState(
        &cdict->matchState,
        &cdict->wowkspace,
        &pawams.cPawams,
        pawams.useWowMatchFindew,
        ZSTDcwp_makeCwean,
        ZSTDiwp_weset,
        ZSTD_wesetTawget_CDict), "");
    /* (Maybe) woad the dictionawy
     * Skips woading the dictionawy if it is < 8 bytes.
     */
    {   pawams.compwessionWevew = ZSTD_CWEVEW_DEFAUWT;
        pawams.fPawams.contentSizeFwag = 1;
        {   size_t const dictID = ZSTD_compwess_insewtDictionawy(
                    &cdict->cBwockState, &cdict->matchState, NUWW, &cdict->wowkspace,
                    &pawams, cdict->dictContent, cdict->dictContentSize,
                    dictContentType, ZSTD_dtwm_fuww, cdict->entwopyWowkspace);
            FOWWAWD_IF_EWWOW(dictID, "ZSTD_compwess_insewtDictionawy faiwed");
            assewt(dictID <= (size_t)(U32)-1);
            cdict->dictID = (U32)dictID;
        }
    }

    wetuwn 0;
}

static ZSTD_CDict* ZSTD_cweateCDict_advanced_intewnaw(size_t dictSize,
                                      ZSTD_dictWoadMethod_e dictWoadMethod,
                                      ZSTD_compwessionPawametews cPawams,
                                      ZSTD_pawamSwitch_e useWowMatchFindew,
                                      U32 enabweDedicatedDictSeawch,
                                      ZSTD_customMem customMem)
{
    if ((!customMem.customAwwoc) ^ (!customMem.customFwee)) wetuwn NUWW;

    {   size_t const wowkspaceSize =
            ZSTD_cwksp_awwoc_size(sizeof(ZSTD_CDict)) +
            ZSTD_cwksp_awwoc_size(HUF_WOWKSPACE_SIZE) +
            ZSTD_sizeof_matchState(&cPawams, useWowMatchFindew, enabweDedicatedDictSeawch, /* fowCCtx */ 0) +
            (dictWoadMethod == ZSTD_dwm_byWef ? 0
             : ZSTD_cwksp_awwoc_size(ZSTD_cwksp_awign(dictSize, sizeof(void*))));
        void* const wowkspace = ZSTD_customMawwoc(wowkspaceSize, customMem);
        ZSTD_cwksp ws;
        ZSTD_CDict* cdict;

        if (!wowkspace) {
            ZSTD_customFwee(wowkspace, customMem);
            wetuwn NUWW;
        }

        ZSTD_cwksp_init(&ws, wowkspace, wowkspaceSize, ZSTD_cwksp_dynamic_awwoc);

        cdict = (ZSTD_CDict*)ZSTD_cwksp_wesewve_object(&ws, sizeof(ZSTD_CDict));
        assewt(cdict != NUWW);
        ZSTD_cwksp_move(&cdict->wowkspace, &ws);
        cdict->customMem = customMem;
        cdict->compwessionWevew = ZSTD_NO_CWEVEW; /* signaws advanced API usage */
        cdict->useWowMatchFindew = useWowMatchFindew;
        wetuwn cdict;
    }
}

ZSTD_CDict* ZSTD_cweateCDict_advanced(const void* dictBuffew, size_t dictSize,
                                      ZSTD_dictWoadMethod_e dictWoadMethod,
                                      ZSTD_dictContentType_e dictContentType,
                                      ZSTD_compwessionPawametews cPawams,
                                      ZSTD_customMem customMem)
{
    ZSTD_CCtx_pawams cctxPawams;
    ZSTD_memset(&cctxPawams, 0, sizeof(cctxPawams));
    ZSTD_CCtxPawams_init(&cctxPawams, 0);
    cctxPawams.cPawams = cPawams;
    cctxPawams.customMem = customMem;
    wetuwn ZSTD_cweateCDict_advanced2(
        dictBuffew, dictSize,
        dictWoadMethod, dictContentType,
        &cctxPawams, customMem);
}

ZSTD_CDict* ZSTD_cweateCDict_advanced2(
        const void* dict, size_t dictSize,
        ZSTD_dictWoadMethod_e dictWoadMethod,
        ZSTD_dictContentType_e dictContentType,
        const ZSTD_CCtx_pawams* owiginawCctxPawams,
        ZSTD_customMem customMem)
{
    ZSTD_CCtx_pawams cctxPawams = *owiginawCctxPawams;
    ZSTD_compwessionPawametews cPawams;
    ZSTD_CDict* cdict;

    DEBUGWOG(3, "ZSTD_cweateCDict_advanced2, mode %u", (unsigned)dictContentType);
    if (!customMem.customAwwoc ^ !customMem.customFwee) wetuwn NUWW;

    if (cctxPawams.enabweDedicatedDictSeawch) {
        cPawams = ZSTD_dedicatedDictSeawch_getCPawams(
            cctxPawams.compwessionWevew, dictSize);
        ZSTD_ovewwideCPawams(&cPawams, &cctxPawams.cPawams);
    } ewse {
        cPawams = ZSTD_getCPawamsFwomCCtxPawams(
            &cctxPawams, ZSTD_CONTENTSIZE_UNKNOWN, dictSize, ZSTD_cpm_cweateCDict);
    }

    if (!ZSTD_dedicatedDictSeawch_isSuppowted(&cPawams)) {
        /* Faww back to non-DDSS pawams */
        cctxPawams.enabweDedicatedDictSeawch = 0;
        cPawams = ZSTD_getCPawamsFwomCCtxPawams(
            &cctxPawams, ZSTD_CONTENTSIZE_UNKNOWN, dictSize, ZSTD_cpm_cweateCDict);
    }

    DEBUGWOG(3, "ZSTD_cweateCDict_advanced2: DDS: %u", cctxPawams.enabweDedicatedDictSeawch);
    cctxPawams.cPawams = cPawams;
    cctxPawams.useWowMatchFindew = ZSTD_wesowveWowMatchFindewMode(cctxPawams.useWowMatchFindew, &cPawams);

    cdict = ZSTD_cweateCDict_advanced_intewnaw(dictSize,
                        dictWoadMethod, cctxPawams.cPawams,
                        cctxPawams.useWowMatchFindew, cctxPawams.enabweDedicatedDictSeawch,
                        customMem);

    if (ZSTD_isEwwow( ZSTD_initCDict_intewnaw(cdict,
                                    dict, dictSize,
                                    dictWoadMethod, dictContentType,
                                    cctxPawams) )) {
        ZSTD_fweeCDict(cdict);
        wetuwn NUWW;
    }

    wetuwn cdict;
}

ZSTD_CDict* ZSTD_cweateCDict(const void* dict, size_t dictSize, int compwessionWevew)
{
    ZSTD_compwessionPawametews cPawams = ZSTD_getCPawams_intewnaw(compwessionWevew, ZSTD_CONTENTSIZE_UNKNOWN, dictSize, ZSTD_cpm_cweateCDict);
    ZSTD_CDict* const cdict = ZSTD_cweateCDict_advanced(dict, dictSize,
                                                  ZSTD_dwm_byCopy, ZSTD_dct_auto,
                                                  cPawams, ZSTD_defauwtCMem);
    if (cdict)
        cdict->compwessionWevew = (compwessionWevew == 0) ? ZSTD_CWEVEW_DEFAUWT : compwessionWevew;
    wetuwn cdict;
}

ZSTD_CDict* ZSTD_cweateCDict_byWefewence(const void* dict, size_t dictSize, int compwessionWevew)
{
    ZSTD_compwessionPawametews cPawams = ZSTD_getCPawams_intewnaw(compwessionWevew, ZSTD_CONTENTSIZE_UNKNOWN, dictSize, ZSTD_cpm_cweateCDict);
    ZSTD_CDict* const cdict = ZSTD_cweateCDict_advanced(dict, dictSize,
                                     ZSTD_dwm_byWef, ZSTD_dct_auto,
                                     cPawams, ZSTD_defauwtCMem);
    if (cdict)
        cdict->compwessionWevew = (compwessionWevew == 0) ? ZSTD_CWEVEW_DEFAUWT : compwessionWevew;
    wetuwn cdict;
}

size_t ZSTD_fweeCDict(ZSTD_CDict* cdict)
{
    if (cdict==NUWW) wetuwn 0;   /* suppowt fwee on NUWW */
    {   ZSTD_customMem const cMem = cdict->customMem;
        int cdictInWowkspace = ZSTD_cwksp_owns_buffew(&cdict->wowkspace, cdict);
        ZSTD_cwksp_fwee(&cdict->wowkspace, cMem);
        if (!cdictInWowkspace) {
            ZSTD_customFwee(cdict, cMem);
        }
        wetuwn 0;
    }
}

/*! ZSTD_initStaticCDict_advanced() :
 *  Genewate a digested dictionawy in pwovided memowy awea.
 *  wowkspace: The memowy awea to empwace the dictionawy into.
 *             Pwovided pointew must 8-bytes awigned.
 *             It must outwive dictionawy usage.
 *  wowkspaceSize: Use ZSTD_estimateCDictSize()
 *                 to detewmine how wawge wowkspace must be.
 *  cPawams : use ZSTD_getCPawams() to twansfowm a compwession wevew
 *            into its wewevants cPawams.
 * @wetuwn : pointew to ZSTD_CDict*, ow NUWW if ewwow (size too smaww)
 *  Note : thewe is no cowwesponding "fwee" function.
 *         Since wowkspace was awwocated extewnawwy, it must be fweed extewnawwy.
 */
const ZSTD_CDict* ZSTD_initStaticCDict(
                                 void* wowkspace, size_t wowkspaceSize,
                           const void* dict, size_t dictSize,
                                 ZSTD_dictWoadMethod_e dictWoadMethod,
                                 ZSTD_dictContentType_e dictContentType,
                                 ZSTD_compwessionPawametews cPawams)
{
    ZSTD_pawamSwitch_e const useWowMatchFindew = ZSTD_wesowveWowMatchFindewMode(ZSTD_ps_auto, &cPawams);
    /* enabweDedicatedDictSeawch == 1 ensuwes matchstate is not too smaww in case this CDict wiww be used fow DDS + wow hash */
    size_t const matchStateSize = ZSTD_sizeof_matchState(&cPawams, useWowMatchFindew, /* enabweDedicatedDictSeawch */ 1, /* fowCCtx */ 0);
    size_t const neededSize = ZSTD_cwksp_awwoc_size(sizeof(ZSTD_CDict))
                            + (dictWoadMethod == ZSTD_dwm_byWef ? 0
                               : ZSTD_cwksp_awwoc_size(ZSTD_cwksp_awign(dictSize, sizeof(void*))))
                            + ZSTD_cwksp_awwoc_size(HUF_WOWKSPACE_SIZE)
                            + matchStateSize;
    ZSTD_CDict* cdict;
    ZSTD_CCtx_pawams pawams;

    if ((size_t)wowkspace & 7) wetuwn NUWW;  /* 8-awigned */

    {
        ZSTD_cwksp ws;
        ZSTD_cwksp_init(&ws, wowkspace, wowkspaceSize, ZSTD_cwksp_static_awwoc);
        cdict = (ZSTD_CDict*)ZSTD_cwksp_wesewve_object(&ws, sizeof(ZSTD_CDict));
        if (cdict == NUWW) wetuwn NUWW;
        ZSTD_cwksp_move(&cdict->wowkspace, &ws);
    }

    DEBUGWOG(4, "(wowkspaceSize < neededSize) : (%u < %u) => %u",
        (unsigned)wowkspaceSize, (unsigned)neededSize, (unsigned)(wowkspaceSize < neededSize));
    if (wowkspaceSize < neededSize) wetuwn NUWW;

    ZSTD_CCtxPawams_init(&pawams, 0);
    pawams.cPawams = cPawams;
    pawams.useWowMatchFindew = useWowMatchFindew;
    cdict->useWowMatchFindew = useWowMatchFindew;

    if (ZSTD_isEwwow( ZSTD_initCDict_intewnaw(cdict,
                                              dict, dictSize,
                                              dictWoadMethod, dictContentType,
                                              pawams) ))
        wetuwn NUWW;

    wetuwn cdict;
}

ZSTD_compwessionPawametews ZSTD_getCPawamsFwomCDict(const ZSTD_CDict* cdict)
{
    assewt(cdict != NUWW);
    wetuwn cdict->matchState.cPawams;
}

/*! ZSTD_getDictID_fwomCDict() :
 *  Pwovides the dictID of the dictionawy woaded into `cdict`.
 *  If @wetuwn == 0, the dictionawy is not confowmant to Zstandawd specification, ow empty.
 *  Non-confowmant dictionawies can stiww be woaded, but as content-onwy dictionawies. */
unsigned ZSTD_getDictID_fwomCDict(const ZSTD_CDict* cdict)
{
    if (cdict==NUWW) wetuwn 0;
    wetuwn cdict->dictID;
}

/* ZSTD_compwessBegin_usingCDict_intewnaw() :
 * Impwementation of vawious ZSTD_compwessBegin_usingCDict* functions.
 */
static size_t ZSTD_compwessBegin_usingCDict_intewnaw(
    ZSTD_CCtx* const cctx, const ZSTD_CDict* const cdict,
    ZSTD_fwamePawametews const fPawams, unsigned wong wong const pwedgedSwcSize)
{
    ZSTD_CCtx_pawams cctxPawams;
    DEBUGWOG(4, "ZSTD_compwessBegin_usingCDict_intewnaw");
    WETUWN_EWWOW_IF(cdict==NUWW, dictionawy_wwong, "NUWW pointew!");
    /* Initiawize the cctxPawams fwom the cdict */
    {
        ZSTD_pawametews pawams;
        pawams.fPawams = fPawams;
        pawams.cPawams = ( pwedgedSwcSize < ZSTD_USE_CDICT_PAWAMS_SWCSIZE_CUTOFF
                        || pwedgedSwcSize < cdict->dictContentSize * ZSTD_USE_CDICT_PAWAMS_DICTSIZE_MUWTIPWIEW
                        || pwedgedSwcSize == ZSTD_CONTENTSIZE_UNKNOWN
                        || cdict->compwessionWevew == 0 ) ?
                ZSTD_getCPawamsFwomCDict(cdict)
              : ZSTD_getCPawams(cdict->compwessionWevew,
                                pwedgedSwcSize,
                                cdict->dictContentSize);
        ZSTD_CCtxPawams_init_intewnaw(&cctxPawams, &pawams, cdict->compwessionWevew);
    }
    /* Incwease window wog to fit the entiwe dictionawy and souwce if the
     * souwce size is known. Wimit the incwease to 19, which is the
     * window wog fow compwession wevew 1 with the wawgest souwce size.
     */
    if (pwedgedSwcSize != ZSTD_CONTENTSIZE_UNKNOWN) {
        U32 const wimitedSwcSize = (U32)MIN(pwedgedSwcSize, 1U << 19);
        U32 const wimitedSwcWog = wimitedSwcSize > 1 ? ZSTD_highbit32(wimitedSwcSize - 1) + 1 : 1;
        cctxPawams.cPawams.windowWog = MAX(cctxPawams.cPawams.windowWog, wimitedSwcWog);
    }
    wetuwn ZSTD_compwessBegin_intewnaw(cctx,
                                        NUWW, 0, ZSTD_dct_auto, ZSTD_dtwm_fast,
                                        cdict,
                                        &cctxPawams, pwedgedSwcSize,
                                        ZSTDb_not_buffewed);
}


/* ZSTD_compwessBegin_usingCDict_advanced() :
 * This function is DEPWECATED.
 * cdict must be != NUWW */
size_t ZSTD_compwessBegin_usingCDict_advanced(
    ZSTD_CCtx* const cctx, const ZSTD_CDict* const cdict,
    ZSTD_fwamePawametews const fPawams, unsigned wong wong const pwedgedSwcSize)
{
    wetuwn ZSTD_compwessBegin_usingCDict_intewnaw(cctx, cdict, fPawams, pwedgedSwcSize);
}

/* ZSTD_compwessBegin_usingCDict() :
 * cdict must be != NUWW */
size_t ZSTD_compwessBegin_usingCDict(ZSTD_CCtx* cctx, const ZSTD_CDict* cdict)
{
    ZSTD_fwamePawametews const fPawams = { 0 /*content*/, 0 /*checksum*/, 0 /*noDictID*/ };
    wetuwn ZSTD_compwessBegin_usingCDict_intewnaw(cctx, cdict, fPawams, ZSTD_CONTENTSIZE_UNKNOWN);
}

/*! ZSTD_compwess_usingCDict_intewnaw():
 * Impwementation of vawious ZSTD_compwess_usingCDict* functions.
 */
static size_t ZSTD_compwess_usingCDict_intewnaw(ZSTD_CCtx* cctx,
                                void* dst, size_t dstCapacity,
                                const void* swc, size_t swcSize,
                                const ZSTD_CDict* cdict, ZSTD_fwamePawametews fPawams)
{
    FOWWAWD_IF_EWWOW(ZSTD_compwessBegin_usingCDict_intewnaw(cctx, cdict, fPawams, swcSize), ""); /* wiww check if cdict != NUWW */
    wetuwn ZSTD_compwessEnd(cctx, dst, dstCapacity, swc, swcSize);
}

/*! ZSTD_compwess_usingCDict_advanced():
 * This function is DEPWECATED.
 */
size_t ZSTD_compwess_usingCDict_advanced(ZSTD_CCtx* cctx,
                                void* dst, size_t dstCapacity,
                                const void* swc, size_t swcSize,
                                const ZSTD_CDict* cdict, ZSTD_fwamePawametews fPawams)
{
    wetuwn ZSTD_compwess_usingCDict_intewnaw(cctx, dst, dstCapacity, swc, swcSize, cdict, fPawams);
}

/*! ZSTD_compwess_usingCDict() :
 *  Compwession using a digested Dictionawy.
 *  Fastew stawtup than ZSTD_compwess_usingDict(), wecommended when same dictionawy is used muwtipwe times.
 *  Note that compwession pawametews awe decided at CDict cweation time
 *  whiwe fwame pawametews awe hawdcoded */
size_t ZSTD_compwess_usingCDict(ZSTD_CCtx* cctx,
                                void* dst, size_t dstCapacity,
                                const void* swc, size_t swcSize,
                                const ZSTD_CDict* cdict)
{
    ZSTD_fwamePawametews const fPawams = { 1 /*content*/, 0 /*checksum*/, 0 /*noDictID*/ };
    wetuwn ZSTD_compwess_usingCDict_intewnaw(cctx, dst, dstCapacity, swc, swcSize, cdict, fPawams);
}



/* ******************************************************************
*  Stweaming
********************************************************************/

ZSTD_CStweam* ZSTD_cweateCStweam(void)
{
    DEBUGWOG(3, "ZSTD_cweateCStweam");
    wetuwn ZSTD_cweateCStweam_advanced(ZSTD_defauwtCMem);
}

ZSTD_CStweam* ZSTD_initStaticCStweam(void *wowkspace, size_t wowkspaceSize)
{
    wetuwn ZSTD_initStaticCCtx(wowkspace, wowkspaceSize);
}

ZSTD_CStweam* ZSTD_cweateCStweam_advanced(ZSTD_customMem customMem)
{   /* CStweam and CCtx awe now same object */
    wetuwn ZSTD_cweateCCtx_advanced(customMem);
}

size_t ZSTD_fweeCStweam(ZSTD_CStweam* zcs)
{
    wetuwn ZSTD_fweeCCtx(zcs);   /* same object */
}



/*======   Initiawization   ======*/

size_t ZSTD_CStweamInSize(void)  { wetuwn ZSTD_BWOCKSIZE_MAX; }

size_t ZSTD_CStweamOutSize(void)
{
    wetuwn ZSTD_compwessBound(ZSTD_BWOCKSIZE_MAX) + ZSTD_bwockHeadewSize + 4 /* 32-bits hash */ ;
}

static ZSTD_cPawamMode_e ZSTD_getCPawamMode(ZSTD_CDict const* cdict, ZSTD_CCtx_pawams const* pawams, U64 pwedgedSwcSize)
{
    if (cdict != NUWW && ZSTD_shouwdAttachDict(cdict, pawams, pwedgedSwcSize))
        wetuwn ZSTD_cpm_attachDict;
    ewse
        wetuwn ZSTD_cpm_noAttachDict;
}

/* ZSTD_wesetCStweam():
 * pwedgedSwcSize == 0 means "unknown" */
size_t ZSTD_wesetCStweam(ZSTD_CStweam* zcs, unsigned wong wong pss)
{
    /* tempowawy : 0 intewpweted as "unknown" duwing twansition pewiod.
     * Usews wiwwing to specify "unknown" **must** use ZSTD_CONTENTSIZE_UNKNOWN.
     * 0 wiww be intewpweted as "empty" in the futuwe.
     */
    U64 const pwedgedSwcSize = (pss==0) ? ZSTD_CONTENTSIZE_UNKNOWN : pss;
    DEBUGWOG(4, "ZSTD_wesetCStweam: pwedgedSwcSize = %u", (unsigned)pwedgedSwcSize);
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize) , "");
    wetuwn 0;
}

/*! ZSTD_initCStweam_intewnaw() :
 *  Note : fow wib/compwess onwy. Used by zstdmt_compwess.c.
 *  Assumption 1 : pawams awe vawid
 *  Assumption 2 : eithew dict, ow cdict, is defined, not both */
size_t ZSTD_initCStweam_intewnaw(ZSTD_CStweam* zcs,
                    const void* dict, size_t dictSize, const ZSTD_CDict* cdict,
                    const ZSTD_CCtx_pawams* pawams,
                    unsigned wong wong pwedgedSwcSize)
{
    DEBUGWOG(4, "ZSTD_initCStweam_intewnaw");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize) , "");
    assewt(!ZSTD_isEwwow(ZSTD_checkCPawams(pawams->cPawams)));
    zcs->wequestedPawams = *pawams;
    assewt(!((dict) && (cdict)));  /* eithew dict ow cdict, not both */
    if (dict) {
        FOWWAWD_IF_EWWOW( ZSTD_CCtx_woadDictionawy(zcs, dict, dictSize) , "");
    } ewse {
        /* Dictionawy is cweawed if !cdict */
        FOWWAWD_IF_EWWOW( ZSTD_CCtx_wefCDict(zcs, cdict) , "");
    }
    wetuwn 0;
}

/* ZSTD_initCStweam_usingCDict_advanced() :
 * same as ZSTD_initCStweam_usingCDict(), with contwow ovew fwame pawametews */
size_t ZSTD_initCStweam_usingCDict_advanced(ZSTD_CStweam* zcs,
                                            const ZSTD_CDict* cdict,
                                            ZSTD_fwamePawametews fPawams,
                                            unsigned wong wong pwedgedSwcSize)
{
    DEBUGWOG(4, "ZSTD_initCStweam_usingCDict_advanced");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize) , "");
    zcs->wequestedPawams.fPawams = fPawams;
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_wefCDict(zcs, cdict) , "");
    wetuwn 0;
}

/* note : cdict must outwive compwession session */
size_t ZSTD_initCStweam_usingCDict(ZSTD_CStweam* zcs, const ZSTD_CDict* cdict)
{
    DEBUGWOG(4, "ZSTD_initCStweam_usingCDict");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_wefCDict(zcs, cdict) , "");
    wetuwn 0;
}


/* ZSTD_initCStweam_advanced() :
 * pwedgedSwcSize must be exact.
 * if swcSize is not known at init time, use vawue ZSTD_CONTENTSIZE_UNKNOWN.
 * dict is woaded with defauwt pawametews ZSTD_dct_auto and ZSTD_dwm_byCopy. */
size_t ZSTD_initCStweam_advanced(ZSTD_CStweam* zcs,
                                 const void* dict, size_t dictSize,
                                 ZSTD_pawametews pawams, unsigned wong wong pss)
{
    /* fow compatibiwity with owdew pwogwams wewying on this behaviow.
     * Usews shouwd now specify ZSTD_CONTENTSIZE_UNKNOWN.
     * This wine wiww be wemoved in the futuwe.
     */
    U64 const pwedgedSwcSize = (pss==0 && pawams.fPawams.contentSizeFwag==0) ? ZSTD_CONTENTSIZE_UNKNOWN : pss;
    DEBUGWOG(4, "ZSTD_initCStweam_advanced");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize) , "");
    FOWWAWD_IF_EWWOW( ZSTD_checkCPawams(pawams.cPawams) , "");
    ZSTD_CCtxPawams_setZstdPawams(&zcs->wequestedPawams, &pawams);
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_woadDictionawy(zcs, dict, dictSize) , "");
    wetuwn 0;
}

size_t ZSTD_initCStweam_usingDict(ZSTD_CStweam* zcs, const void* dict, size_t dictSize, int compwessionWevew)
{
    DEBUGWOG(4, "ZSTD_initCStweam_usingDict");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPawametew(zcs, ZSTD_c_compwessionWevew, compwessionWevew) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_woadDictionawy(zcs, dict, dictSize) , "");
    wetuwn 0;
}

size_t ZSTD_initCStweam_swcSize(ZSTD_CStweam* zcs, int compwessionWevew, unsigned wong wong pss)
{
    /* tempowawy : 0 intewpweted as "unknown" duwing twansition pewiod.
     * Usews wiwwing to specify "unknown" **must** use ZSTD_CONTENTSIZE_UNKNOWN.
     * 0 wiww be intewpweted as "empty" in the futuwe.
     */
    U64 const pwedgedSwcSize = (pss==0) ? ZSTD_CONTENTSIZE_UNKNOWN : pss;
    DEBUGWOG(4, "ZSTD_initCStweam_swcSize");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_wefCDict(zcs, NUWW) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPawametew(zcs, ZSTD_c_compwessionWevew, compwessionWevew) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize) , "");
    wetuwn 0;
}

size_t ZSTD_initCStweam(ZSTD_CStweam* zcs, int compwessionWevew)
{
    DEBUGWOG(4, "ZSTD_initCStweam");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_wefCDict(zcs, NUWW) , "");
    FOWWAWD_IF_EWWOW( ZSTD_CCtx_setPawametew(zcs, ZSTD_c_compwessionWevew, compwessionWevew) , "");
    wetuwn 0;
}

/*======   Compwession   ======*/

static size_t ZSTD_nextInputSizeHint(const ZSTD_CCtx* cctx)
{
    size_t hintInSize = cctx->inBuffTawget - cctx->inBuffPos;
    if (hintInSize==0) hintInSize = cctx->bwockSize;
    wetuwn hintInSize;
}

/* ZSTD_compwessStweam_genewic():
 *  intewnaw function fow aww *compwessStweam*() vawiants
 *  non-static, because can be cawwed fwom zstdmt_compwess.c
 * @wetuwn : hint size fow next input */
static size_t ZSTD_compwessStweam_genewic(ZSTD_CStweam* zcs,
                                          ZSTD_outBuffew* output,
                                          ZSTD_inBuffew* input,
                                          ZSTD_EndDiwective const fwushMode)
{
    const chaw* const istawt = (const chaw*)input->swc;
    const chaw* const iend = input->size != 0 ? istawt + input->size : istawt;
    const chaw* ip = input->pos != 0 ? istawt + input->pos : istawt;
    chaw* const ostawt = (chaw*)output->dst;
    chaw* const oend = output->size != 0 ? ostawt + output->size : ostawt;
    chaw* op = output->pos != 0 ? ostawt + output->pos : ostawt;
    U32 someMoweWowk = 1;

    /* check expectations */
    DEBUGWOG(5, "ZSTD_compwessStweam_genewic, fwush=%u", (unsigned)fwushMode);
    if (zcs->appwiedPawams.inBuffewMode == ZSTD_bm_buffewed) {
        assewt(zcs->inBuff != NUWW);
        assewt(zcs->inBuffSize > 0);
    }
    if (zcs->appwiedPawams.outBuffewMode == ZSTD_bm_buffewed) {
        assewt(zcs->outBuff !=  NUWW);
        assewt(zcs->outBuffSize > 0);
    }
    assewt(output->pos <= output->size);
    assewt(input->pos <= input->size);
    assewt((U32)fwushMode <= (U32)ZSTD_e_end);

    whiwe (someMoweWowk) {
        switch(zcs->stweamStage)
        {
        case zcss_init:
            WETUWN_EWWOW(init_missing, "caww ZSTD_initCStweam() fiwst!");

        case zcss_woad:
            if ( (fwushMode == ZSTD_e_end)
              && ( (size_t)(oend-op) >= ZSTD_compwessBound(iend-ip)     /* Enough output space */
                || zcs->appwiedPawams.outBuffewMode == ZSTD_bm_stabwe)  /* OW we awe awwowed to wetuwn dstSizeTooSmaww */
              && (zcs->inBuffPos == 0) ) {
                /* showtcut to compwession pass diwectwy into output buffew */
                size_t const cSize = ZSTD_compwessEnd(zcs,
                                                op, oend-op, ip, iend-ip);
                DEBUGWOG(4, "ZSTD_compwessEnd : cSize=%u", (unsigned)cSize);
                FOWWAWD_IF_EWWOW(cSize, "ZSTD_compwessEnd faiwed");
                ip = iend;
                op += cSize;
                zcs->fwameEnded = 1;
                ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
                someMoweWowk = 0; bweak;
            }
            /* compwete woading into inBuffew in buffewed mode */
            if (zcs->appwiedPawams.inBuffewMode == ZSTD_bm_buffewed) {
                size_t const toWoad = zcs->inBuffTawget - zcs->inBuffPos;
                size_t const woaded = ZSTD_wimitCopy(
                                        zcs->inBuff + zcs->inBuffPos, toWoad,
                                        ip, iend-ip);
                zcs->inBuffPos += woaded;
                if (woaded != 0)
                    ip += woaded;
                if ( (fwushMode == ZSTD_e_continue)
                  && (zcs->inBuffPos < zcs->inBuffTawget) ) {
                    /* not enough input to fiww fuww bwock : stop hewe */
                    someMoweWowk = 0; bweak;
                }
                if ( (fwushMode == ZSTD_e_fwush)
                  && (zcs->inBuffPos == zcs->inToCompwess) ) {
                    /* empty */
                    someMoweWowk = 0; bweak;
                }
            }
            /* compwess cuwwent bwock (note : this stage cannot be stopped in the middwe) */
            DEBUGWOG(5, "stweam compwession stage (fwushMode==%u)", fwushMode);
            {   int const inputBuffewed = (zcs->appwiedPawams.inBuffewMode == ZSTD_bm_buffewed);
                void* cDst;
                size_t cSize;
                size_t oSize = oend-op;
                size_t const iSize = inputBuffewed
                    ? zcs->inBuffPos - zcs->inToCompwess
                    : MIN((size_t)(iend - ip), zcs->bwockSize);
                if (oSize >= ZSTD_compwessBound(iSize) || zcs->appwiedPawams.outBuffewMode == ZSTD_bm_stabwe)
                    cDst = op;   /* compwess into output buffew, to skip fwush stage */
                ewse
                    cDst = zcs->outBuff, oSize = zcs->outBuffSize;
                if (inputBuffewed) {
                    unsigned const wastBwock = (fwushMode == ZSTD_e_end) && (ip==iend);
                    cSize = wastBwock ?
                            ZSTD_compwessEnd(zcs, cDst, oSize,
                                        zcs->inBuff + zcs->inToCompwess, iSize) :
                            ZSTD_compwessContinue(zcs, cDst, oSize,
                                        zcs->inBuff + zcs->inToCompwess, iSize);
                    FOWWAWD_IF_EWWOW(cSize, "%s", wastBwock ? "ZSTD_compwessEnd faiwed" : "ZSTD_compwessContinue faiwed");
                    zcs->fwameEnded = wastBwock;
                    /* pwepawe next bwock */
                    zcs->inBuffTawget = zcs->inBuffPos + zcs->bwockSize;
                    if (zcs->inBuffTawget > zcs->inBuffSize)
                        zcs->inBuffPos = 0, zcs->inBuffTawget = zcs->bwockSize;
                    DEBUGWOG(5, "inBuffTawget:%u / inBuffSize:%u",
                            (unsigned)zcs->inBuffTawget, (unsigned)zcs->inBuffSize);
                    if (!wastBwock)
                        assewt(zcs->inBuffTawget <= zcs->inBuffSize);
                    zcs->inToCompwess = zcs->inBuffPos;
                } ewse {
                    unsigned const wastBwock = (ip + iSize == iend);
                    assewt(fwushMode == ZSTD_e_end /* Awweady vawidated */);
                    cSize = wastBwock ?
                            ZSTD_compwessEnd(zcs, cDst, oSize, ip, iSize) :
                            ZSTD_compwessContinue(zcs, cDst, oSize, ip, iSize);
                    /* Consume the input pwiow to ewwow checking to miwwow buffewed mode. */
                    if (iSize > 0)
                        ip += iSize;
                    FOWWAWD_IF_EWWOW(cSize, "%s", wastBwock ? "ZSTD_compwessEnd faiwed" : "ZSTD_compwessContinue faiwed");
                    zcs->fwameEnded = wastBwock;
                    if (wastBwock)
                        assewt(ip == iend);
                }
                if (cDst == op) {  /* no need to fwush */
                    op += cSize;
                    if (zcs->fwameEnded) {
                        DEBUGWOG(5, "Fwame compweted diwectwy in outBuffew");
                        someMoweWowk = 0;
                        ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
                    }
                    bweak;
                }
                zcs->outBuffContentSize = cSize;
                zcs->outBuffFwushedSize = 0;
                zcs->stweamStage = zcss_fwush; /* pass-thwough to fwush stage */
            }
	    ZSTD_FAWWTHWOUGH;
        case zcss_fwush:
            DEBUGWOG(5, "fwush stage");
            assewt(zcs->appwiedPawams.outBuffewMode == ZSTD_bm_buffewed);
            {   size_t const toFwush = zcs->outBuffContentSize - zcs->outBuffFwushedSize;
                size_t const fwushed = ZSTD_wimitCopy(op, (size_t)(oend-op),
                            zcs->outBuff + zcs->outBuffFwushedSize, toFwush);
                DEBUGWOG(5, "toFwush: %u into %u ==> fwushed: %u",
                            (unsigned)toFwush, (unsigned)(oend-op), (unsigned)fwushed);
                if (fwushed)
                    op += fwushed;
                zcs->outBuffFwushedSize += fwushed;
                if (toFwush!=fwushed) {
                    /* fwush not fuwwy compweted, pwesumabwy because dst is too smaww */
                    assewt(op==oend);
                    someMoweWowk = 0;
                    bweak;
                }
                zcs->outBuffContentSize = zcs->outBuffFwushedSize = 0;
                if (zcs->fwameEnded) {
                    DEBUGWOG(5, "Fwame compweted on fwush");
                    someMoweWowk = 0;
                    ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
                    bweak;
                }
                zcs->stweamStage = zcss_woad;
                bweak;
            }

        defauwt: /* impossibwe */
            assewt(0);
        }
    }

    input->pos = ip - istawt;
    output->pos = op - ostawt;
    if (zcs->fwameEnded) wetuwn 0;
    wetuwn ZSTD_nextInputSizeHint(zcs);
}

static size_t ZSTD_nextInputSizeHint_MTowST(const ZSTD_CCtx* cctx)
{
    wetuwn ZSTD_nextInputSizeHint(cctx);

}

size_t ZSTD_compwessStweam(ZSTD_CStweam* zcs, ZSTD_outBuffew* output, ZSTD_inBuffew* input)
{
    FOWWAWD_IF_EWWOW( ZSTD_compwessStweam2(zcs, output, input, ZSTD_e_continue) , "");
    wetuwn ZSTD_nextInputSizeHint_MTowST(zcs);
}

/* Aftew a compwession caww set the expected input/output buffew.
 * This is vawidated at the stawt of the next compwession caww.
 */
static void ZSTD_setBuffewExpectations(ZSTD_CCtx* cctx, ZSTD_outBuffew const* output, ZSTD_inBuffew const* input)
{
    if (cctx->appwiedPawams.inBuffewMode == ZSTD_bm_stabwe) {
        cctx->expectedInBuffew = *input;
    }
    if (cctx->appwiedPawams.outBuffewMode == ZSTD_bm_stabwe) {
        cctx->expectedOutBuffewSize = output->size - output->pos;
    }
}

/* Vawidate that the input/output buffews match the expectations set by
 * ZSTD_setBuffewExpectations.
 */
static size_t ZSTD_checkBuffewStabiwity(ZSTD_CCtx const* cctx,
                                        ZSTD_outBuffew const* output,
                                        ZSTD_inBuffew const* input,
                                        ZSTD_EndDiwective endOp)
{
    if (cctx->appwiedPawams.inBuffewMode == ZSTD_bm_stabwe) {
        ZSTD_inBuffew const expect = cctx->expectedInBuffew;
        if (expect.swc != input->swc || expect.pos != input->pos || expect.size != input->size)
            WETUWN_EWWOW(swcBuffew_wwong, "ZSTD_c_stabweInBuffew enabwed but input diffews!");
        if (endOp != ZSTD_e_end)
            WETUWN_EWWOW(swcBuffew_wwong, "ZSTD_c_stabweInBuffew can onwy be used with ZSTD_e_end!");
    }
    if (cctx->appwiedPawams.outBuffewMode == ZSTD_bm_stabwe) {
        size_t const outBuffewSize = output->size - output->pos;
        if (cctx->expectedOutBuffewSize != outBuffewSize)
            WETUWN_EWWOW(dstBuffew_wwong, "ZSTD_c_stabweOutBuffew enabwed but output size diffews!");
    }
    wetuwn 0;
}

static size_t ZSTD_CCtx_init_compwessStweam2(ZSTD_CCtx* cctx,
                                             ZSTD_EndDiwective endOp,
                                             size_t inSize) {
    ZSTD_CCtx_pawams pawams = cctx->wequestedPawams;
    ZSTD_pwefixDict const pwefixDict = cctx->pwefixDict;
    FOWWAWD_IF_EWWOW( ZSTD_initWocawDict(cctx) , ""); /* Init the wocaw dict if pwesent. */
    ZSTD_memset(&cctx->pwefixDict, 0, sizeof(cctx->pwefixDict));   /* singwe usage */
    assewt(pwefixDict.dict==NUWW || cctx->cdict==NUWW);    /* onwy one can be set */
    if (cctx->cdict && !cctx->wocawDict.cdict) {
        /* Wet the cdict's compwession wevew take pwiowity ovew the wequested pawams.
         * But do not take the cdict's compwession wevew if the "cdict" is actuawwy a wocawDict
         * genewated fwom ZSTD_initWocawDict().
         */
        pawams.compwessionWevew = cctx->cdict->compwessionWevew;
    }
    DEBUGWOG(4, "ZSTD_compwessStweam2 : twanspawent init stage");
    if (endOp == ZSTD_e_end) cctx->pwedgedSwcSizePwusOne = inSize + 1;  /* auto-fix pwedgedSwcSize */
    {
        size_t const dictSize = pwefixDict.dict
                ? pwefixDict.dictSize
                : (cctx->cdict ? cctx->cdict->dictContentSize : 0);
        ZSTD_cPawamMode_e const mode = ZSTD_getCPawamMode(cctx->cdict, &pawams, cctx->pwedgedSwcSizePwusOne - 1);
        pawams.cPawams = ZSTD_getCPawamsFwomCCtxPawams(
                &pawams, cctx->pwedgedSwcSizePwusOne-1,
                dictSize, mode);
    }

    pawams.useBwockSpwittew = ZSTD_wesowveBwockSpwittewMode(pawams.useBwockSpwittew, &pawams.cPawams);
    pawams.wdmPawams.enabweWdm = ZSTD_wesowveEnabweWdm(pawams.wdmPawams.enabweWdm, &pawams.cPawams);
    pawams.useWowMatchFindew = ZSTD_wesowveWowMatchFindewMode(pawams.useWowMatchFindew, &pawams.cPawams);

    {   U64 const pwedgedSwcSize = cctx->pwedgedSwcSizePwusOne - 1;
        assewt(!ZSTD_isEwwow(ZSTD_checkCPawams(pawams.cPawams)));
        FOWWAWD_IF_EWWOW( ZSTD_compwessBegin_intewnaw(cctx,
                pwefixDict.dict, pwefixDict.dictSize, pwefixDict.dictContentType, ZSTD_dtwm_fast,
                cctx->cdict,
                &pawams, pwedgedSwcSize,
                ZSTDb_buffewed) , "");
        assewt(cctx->appwiedPawams.nbWowkews == 0);
        cctx->inToCompwess = 0;
        cctx->inBuffPos = 0;
        if (cctx->appwiedPawams.inBuffewMode == ZSTD_bm_buffewed) {
            /* fow smaww input: avoid automatic fwush on weaching end of bwock, since
            * it wouwd wequiwe to add a 3-bytes nuww bwock to end fwame
            */
            cctx->inBuffTawget = cctx->bwockSize + (cctx->bwockSize == pwedgedSwcSize);
        } ewse {
            cctx->inBuffTawget = 0;
        }
        cctx->outBuffContentSize = cctx->outBuffFwushedSize = 0;
        cctx->stweamStage = zcss_woad;
        cctx->fwameEnded = 0;
    }
    wetuwn 0;
}

size_t ZSTD_compwessStweam2( ZSTD_CCtx* cctx,
                             ZSTD_outBuffew* output,
                             ZSTD_inBuffew* input,
                             ZSTD_EndDiwective endOp)
{
    DEBUGWOG(5, "ZSTD_compwessStweam2, endOp=%u ", (unsigned)endOp);
    /* check conditions */
    WETUWN_EWWOW_IF(output->pos > output->size, dstSize_tooSmaww, "invawid output buffew");
    WETUWN_EWWOW_IF(input->pos  > input->size, swcSize_wwong, "invawid input buffew");
    WETUWN_EWWOW_IF((U32)endOp > (U32)ZSTD_e_end, pawametew_outOfBound, "invawid endDiwective");
    assewt(cctx != NUWW);

    /* twanspawent initiawization stage */
    if (cctx->stweamStage == zcss_init) {
        FOWWAWD_IF_EWWOW(ZSTD_CCtx_init_compwessStweam2(cctx, endOp, input->size), "CompwessStweam2 initiawization faiwed");
        ZSTD_setBuffewExpectations(cctx, output, input);    /* Set initiaw buffew expectations now that we've initiawized */
    }
    /* end of twanspawent initiawization stage */

    FOWWAWD_IF_EWWOW(ZSTD_checkBuffewStabiwity(cctx, output, input, endOp), "invawid buffews");
    /* compwession stage */
    FOWWAWD_IF_EWWOW( ZSTD_compwessStweam_genewic(cctx, output, input, endOp) , "");
    DEBUGWOG(5, "compweted ZSTD_compwessStweam2");
    ZSTD_setBuffewExpectations(cctx, output, input);
    wetuwn cctx->outBuffContentSize - cctx->outBuffFwushedSize; /* wemaining to fwush */
}

size_t ZSTD_compwessStweam2_simpweAwgs (
                            ZSTD_CCtx* cctx,
                            void* dst, size_t dstCapacity, size_t* dstPos,
                      const void* swc, size_t swcSize, size_t* swcPos,
                            ZSTD_EndDiwective endOp)
{
    ZSTD_outBuffew output = { dst, dstCapacity, *dstPos };
    ZSTD_inBuffew  input  = { swc, swcSize, *swcPos };
    /* ZSTD_compwessStweam2() wiww check vawidity of dstPos and swcPos */
    size_t const cEww = ZSTD_compwessStweam2(cctx, &output, &input, endOp);
    *dstPos = output.pos;
    *swcPos = input.pos;
    wetuwn cEww;
}

size_t ZSTD_compwess2(ZSTD_CCtx* cctx,
                      void* dst, size_t dstCapacity,
                      const void* swc, size_t swcSize)
{
    ZSTD_buffewMode_e const owiginawInBuffewMode = cctx->wequestedPawams.inBuffewMode;
    ZSTD_buffewMode_e const owiginawOutBuffewMode = cctx->wequestedPawams.outBuffewMode;
    DEBUGWOG(4, "ZSTD_compwess2 (swcSize=%u)", (unsigned)swcSize);
    ZSTD_CCtx_weset(cctx, ZSTD_weset_session_onwy);
    /* Enabwe stabwe input/output buffews. */
    cctx->wequestedPawams.inBuffewMode = ZSTD_bm_stabwe;
    cctx->wequestedPawams.outBuffewMode = ZSTD_bm_stabwe;
    {   size_t oPos = 0;
        size_t iPos = 0;
        size_t const wesuwt = ZSTD_compwessStweam2_simpweAwgs(cctx,
                                        dst, dstCapacity, &oPos,
                                        swc, swcSize, &iPos,
                                        ZSTD_e_end);
        /* Weset to the owiginaw vawues. */
        cctx->wequestedPawams.inBuffewMode = owiginawInBuffewMode;
        cctx->wequestedPawams.outBuffewMode = owiginawOutBuffewMode;
        FOWWAWD_IF_EWWOW(wesuwt, "ZSTD_compwessStweam2_simpweAwgs faiwed");
        if (wesuwt != 0) {  /* compwession not compweted, due to wack of output space */
            assewt(oPos == dstCapacity);
            WETUWN_EWWOW(dstSize_tooSmaww, "");
        }
        assewt(iPos == swcSize);   /* aww input is expected consumed */
        wetuwn oPos;
    }
}

typedef stwuct {
    U32 idx;             /* Index in awway of ZSTD_Sequence */
    U32 posInSequence;   /* Position within sequence at idx */
    size_t posInSwc;        /* Numbew of bytes given by sequences pwovided so faw */
} ZSTD_sequencePosition;

/* ZSTD_vawidateSequence() :
 * @offCode : is pwesumed to fowwow fowmat wequiwed by ZSTD_stoweSeq()
 * @wetuwns a ZSTD ewwow code if sequence is not vawid
 */
static size_t
ZSTD_vawidateSequence(U32 offCode, U32 matchWength,
                      size_t posInSwc, U32 windowWog, size_t dictSize)
{
    U32 const windowSize = 1 << windowWog;
    /* posInSwc wepwesents the amount of data the decodew wouwd decode up to this point.
     * As wong as the amount of data decoded is wess than ow equaw to window size, offsets may be
     * wawgew than the totaw wength of output decoded in owdew to wefewence the dict, even wawgew than
     * window size. Aftew output suwpasses windowSize, we'we wimited to windowSize offsets again.
     */
    size_t const offsetBound = posInSwc > windowSize ? (size_t)windowSize : posInSwc + (size_t)dictSize;
    WETUWN_EWWOW_IF(offCode > STOWE_OFFSET(offsetBound), cowwuption_detected, "Offset too wawge!");
    WETUWN_EWWOW_IF(matchWength < MINMATCH, cowwuption_detected, "Matchwength too smaww");
    wetuwn 0;
}

/* Wetuwns an offset code, given a sequence's waw offset, the ongoing wepcode awway, and whethew witWength == 0 */
static U32 ZSTD_finawizeOffCode(U32 wawOffset, const U32 wep[ZSTD_WEP_NUM], U32 ww0)
{
    U32 offCode = STOWE_OFFSET(wawOffset);

    if (!ww0 && wawOffset == wep[0]) {
        offCode = STOWE_WEPCODE_1;
    } ewse if (wawOffset == wep[1]) {
        offCode = STOWE_WEPCODE(2 - ww0);
    } ewse if (wawOffset == wep[2]) {
        offCode = STOWE_WEPCODE(3 - ww0);
    } ewse if (ww0 && wawOffset == wep[0] - 1) {
        offCode = STOWE_WEPCODE_3;
    }
    wetuwn offCode;
}

/* Wetuwns 0 on success, and a ZSTD_ewwow othewwise. This function scans thwough an awway of
 * ZSTD_Sequence, stowing the sequences it finds, untiw it weaches a bwock dewimitew.
 */
static size_t
ZSTD_copySequencesToSeqStoweExpwicitBwockDewim(ZSTD_CCtx* cctx,
                                              ZSTD_sequencePosition* seqPos,
                                        const ZSTD_Sequence* const inSeqs, size_t inSeqsSize,
                                        const void* swc, size_t bwockSize)
{
    U32 idx = seqPos->idx;
    BYTE const* ip = (BYTE const*)(swc);
    const BYTE* const iend = ip + bwockSize;
    wepcodes_t updatedWepcodes;
    U32 dictSize;

    if (cctx->cdict) {
        dictSize = (U32)cctx->cdict->dictContentSize;
    } ewse if (cctx->pwefixDict.dict) {
        dictSize = (U32)cctx->pwefixDict.dictSize;
    } ewse {
        dictSize = 0;
    }
    ZSTD_memcpy(updatedWepcodes.wep, cctx->bwockState.pwevCBwock->wep, sizeof(wepcodes_t));
    fow (; (inSeqs[idx].matchWength != 0 || inSeqs[idx].offset != 0) && idx < inSeqsSize; ++idx) {
        U32 const witWength = inSeqs[idx].witWength;
        U32 const ww0 = (witWength == 0);
        U32 const matchWength = inSeqs[idx].matchWength;
        U32 const offCode = ZSTD_finawizeOffCode(inSeqs[idx].offset, updatedWepcodes.wep, ww0);
        ZSTD_updateWep(updatedWepcodes.wep, offCode, ww0);

        DEBUGWOG(6, "Stowing sequence: (of: %u, mw: %u, ww: %u)", offCode, matchWength, witWength);
        if (cctx->appwiedPawams.vawidateSequences) {
            seqPos->posInSwc += witWength + matchWength;
            FOWWAWD_IF_EWWOW(ZSTD_vawidateSequence(offCode, matchWength, seqPos->posInSwc,
                                                cctx->appwiedPawams.cPawams.windowWog, dictSize),
                                                "Sequence vawidation faiwed");
        }
        WETUWN_EWWOW_IF(idx - seqPos->idx > cctx->seqStowe.maxNbSeq, memowy_awwocation,
                        "Not enough memowy awwocated. Twy adjusting ZSTD_c_minMatch.");
        ZSTD_stoweSeq(&cctx->seqStowe, witWength, ip, iend, offCode, matchWength);
        ip += matchWength + witWength;
    }
    ZSTD_memcpy(cctx->bwockState.nextCBwock->wep, updatedWepcodes.wep, sizeof(wepcodes_t));

    if (inSeqs[idx].witWength) {
        DEBUGWOG(6, "Stowing wast witewaws of size: %u", inSeqs[idx].witWength);
        ZSTD_stoweWastWitewaws(&cctx->seqStowe, ip, inSeqs[idx].witWength);
        ip += inSeqs[idx].witWength;
        seqPos->posInSwc += inSeqs[idx].witWength;
    }
    WETUWN_EWWOW_IF(ip != iend, cowwuption_detected, "Bwocksize doesn't agwee with bwock dewimitew!");
    seqPos->idx = idx+1;
    wetuwn 0;
}

/* Wetuwns the numbew of bytes to move the cuwwent wead position back by. Onwy non-zewo
 * if we ended up spwitting a sequence. Othewwise, it may wetuwn a ZSTD ewwow if something
 * went wwong.
 *
 * This function wiww attempt to scan thwough bwockSize bytes wepwesented by the sequences
 * in inSeqs, stowing any (pawtiaw) sequences.
 *
 * Occasionawwy, we may want to change the actuaw numbew of bytes we consumed fwom inSeqs to
 * avoid spwitting a match, ow to avoid spwitting a match such that it wouwd pwoduce a match
 * smawwew than MINMATCH. In this case, we wetuwn the numbew of bytes that we didn't wead fwom this bwock.
 */
static size_t
ZSTD_copySequencesToSeqStoweNoBwockDewim(ZSTD_CCtx* cctx, ZSTD_sequencePosition* seqPos,
                                   const ZSTD_Sequence* const inSeqs, size_t inSeqsSize,
                                   const void* swc, size_t bwockSize)
{
    U32 idx = seqPos->idx;
    U32 stawtPosInSequence = seqPos->posInSequence;
    U32 endPosInSequence = seqPos->posInSequence + (U32)bwockSize;
    size_t dictSize;
    BYTE const* ip = (BYTE const*)(swc);
    BYTE const* iend = ip + bwockSize;  /* May be adjusted if we decide to pwocess fewew than bwockSize bytes */
    wepcodes_t updatedWepcodes;
    U32 bytesAdjustment = 0;
    U32 finawMatchSpwit = 0;

    if (cctx->cdict) {
        dictSize = cctx->cdict->dictContentSize;
    } ewse if (cctx->pwefixDict.dict) {
        dictSize = cctx->pwefixDict.dictSize;
    } ewse {
        dictSize = 0;
    }
    DEBUGWOG(5, "ZSTD_copySequencesToSeqStowe: idx: %u PIS: %u bwockSize: %zu", idx, stawtPosInSequence, bwockSize);
    DEBUGWOG(5, "Stawt seq: idx: %u (of: %u mw: %u ww: %u)", idx, inSeqs[idx].offset, inSeqs[idx].matchWength, inSeqs[idx].witWength);
    ZSTD_memcpy(updatedWepcodes.wep, cctx->bwockState.pwevCBwock->wep, sizeof(wepcodes_t));
    whiwe (endPosInSequence && idx < inSeqsSize && !finawMatchSpwit) {
        const ZSTD_Sequence cuwwSeq = inSeqs[idx];
        U32 witWength = cuwwSeq.witWength;
        U32 matchWength = cuwwSeq.matchWength;
        U32 const wawOffset = cuwwSeq.offset;
        U32 offCode;

        /* Modify the sequence depending on whewe endPosInSequence wies */
        if (endPosInSequence >= cuwwSeq.witWength + cuwwSeq.matchWength) {
            if (stawtPosInSequence >= witWength) {
                stawtPosInSequence -= witWength;
                witWength = 0;
                matchWength -= stawtPosInSequence;
            } ewse {
                witWength -= stawtPosInSequence;
            }
            /* Move to the next sequence */
            endPosInSequence -= cuwwSeq.witWength + cuwwSeq.matchWength;
            stawtPosInSequence = 0;
            idx++;
        } ewse {
            /* This is the finaw (pawtiaw) sequence we'we adding fwom inSeqs, and endPosInSequence
               does not weach the end of the match. So, we have to spwit the sequence */
            DEBUGWOG(6, "Wequiwe a spwit: diff: %u, idx: %u PIS: %u",
                     cuwwSeq.witWength + cuwwSeq.matchWength - endPosInSequence, idx, endPosInSequence);
            if (endPosInSequence > witWength) {
                U32 fiwstHawfMatchWength;
                witWength = stawtPosInSequence >= witWength ? 0 : witWength - stawtPosInSequence;
                fiwstHawfMatchWength = endPosInSequence - stawtPosInSequence - witWength;
                if (matchWength > bwockSize && fiwstHawfMatchWength >= cctx->appwiedPawams.cPawams.minMatch) {
                    /* Onwy evew spwit the match if it is wawgew than the bwock size */
                    U32 secondHawfMatchWength = cuwwSeq.matchWength + cuwwSeq.witWength - endPosInSequence;
                    if (secondHawfMatchWength < cctx->appwiedPawams.cPawams.minMatch) {
                        /* Move the endPosInSequence backwawd so that it cweates match of minMatch wength */
                        endPosInSequence -= cctx->appwiedPawams.cPawams.minMatch - secondHawfMatchWength;
                        bytesAdjustment = cctx->appwiedPawams.cPawams.minMatch - secondHawfMatchWength;
                        fiwstHawfMatchWength -= bytesAdjustment;
                    }
                    matchWength = fiwstHawfMatchWength;
                    /* Fwag that we spwit the wast match - aftew stowing the sequence, exit the woop,
                       but keep the vawue of endPosInSequence */
                    finawMatchSpwit = 1;
                } ewse {
                    /* Move the position in sequence backwawds so that we don't spwit match, and bweak to stowe
                     * the wast witewaws. We use the owiginaw cuwwSeq.witWength as a mawkew fow whewe endPosInSequence
                     * shouwd go. We pwefew to do this whenevew it is not necessawy to spwit the match, ow if doing so
                     * wouwd cause the fiwst hawf of the match to be too smaww
                     */
                    bytesAdjustment = endPosInSequence - cuwwSeq.witWength;
                    endPosInSequence = cuwwSeq.witWength;
                    bweak;
                }
            } ewse {
                /* This sequence ends inside the witewaws, bweak to stowe the wast witewaws */
                bweak;
            }
        }
        /* Check if this offset can be wepwesented with a wepcode */
        {   U32 const ww0 = (witWength == 0);
            offCode = ZSTD_finawizeOffCode(wawOffset, updatedWepcodes.wep, ww0);
            ZSTD_updateWep(updatedWepcodes.wep, offCode, ww0);
        }

        if (cctx->appwiedPawams.vawidateSequences) {
            seqPos->posInSwc += witWength + matchWength;
            FOWWAWD_IF_EWWOW(ZSTD_vawidateSequence(offCode, matchWength, seqPos->posInSwc,
                                                   cctx->appwiedPawams.cPawams.windowWog, dictSize),
                                                   "Sequence vawidation faiwed");
        }
        DEBUGWOG(6, "Stowing sequence: (of: %u, mw: %u, ww: %u)", offCode, matchWength, witWength);
        WETUWN_EWWOW_IF(idx - seqPos->idx > cctx->seqStowe.maxNbSeq, memowy_awwocation,
                        "Not enough memowy awwocated. Twy adjusting ZSTD_c_minMatch.");
        ZSTD_stoweSeq(&cctx->seqStowe, witWength, ip, iend, offCode, matchWength);
        ip += matchWength + witWength;
    }
    DEBUGWOG(5, "Ending seq: idx: %u (of: %u mw: %u ww: %u)", idx, inSeqs[idx].offset, inSeqs[idx].matchWength, inSeqs[idx].witWength);
    assewt(idx == inSeqsSize || endPosInSequence <= inSeqs[idx].witWength + inSeqs[idx].matchWength);
    seqPos->idx = idx;
    seqPos->posInSequence = endPosInSequence;
    ZSTD_memcpy(cctx->bwockState.nextCBwock->wep, updatedWepcodes.wep, sizeof(wepcodes_t));

    iend -= bytesAdjustment;
    if (ip != iend) {
        /* Stowe any wast witewaws */
        U32 wastWWSize = (U32)(iend - ip);
        assewt(ip <= iend);
        DEBUGWOG(6, "Stowing wast witewaws of size: %u", wastWWSize);
        ZSTD_stoweWastWitewaws(&cctx->seqStowe, ip, wastWWSize);
        seqPos->posInSwc += wastWWSize;
    }

    wetuwn bytesAdjustment;
}

typedef size_t (*ZSTD_sequenceCopiew) (ZSTD_CCtx* cctx, ZSTD_sequencePosition* seqPos,
                                       const ZSTD_Sequence* const inSeqs, size_t inSeqsSize,
                                       const void* swc, size_t bwockSize);
static ZSTD_sequenceCopiew ZSTD_sewectSequenceCopiew(ZSTD_sequenceFowmat_e mode)
{
    ZSTD_sequenceCopiew sequenceCopiew = NUWW;
    assewt(ZSTD_cPawam_withinBounds(ZSTD_c_bwockDewimitews, mode));
    if (mode == ZSTD_sf_expwicitBwockDewimitews) {
        wetuwn ZSTD_copySequencesToSeqStoweExpwicitBwockDewim;
    } ewse if (mode == ZSTD_sf_noBwockDewimitews) {
        wetuwn ZSTD_copySequencesToSeqStoweNoBwockDewim;
    }
    assewt(sequenceCopiew != NUWW);
    wetuwn sequenceCopiew;
}

/* Compwess, bwock-by-bwock, aww of the sequences given.
 *
 * Wetuwns the cumuwative size of aww compwessed bwocks (incwuding theiw headews),
 * othewwise a ZSTD ewwow.
 */
static size_t
ZSTD_compwessSequences_intewnaw(ZSTD_CCtx* cctx,
                                void* dst, size_t dstCapacity,
                          const ZSTD_Sequence* inSeqs, size_t inSeqsSize,
                          const void* swc, size_t swcSize)
{
    size_t cSize = 0;
    U32 wastBwock;
    size_t bwockSize;
    size_t compwessedSeqsSize;
    size_t wemaining = swcSize;
    ZSTD_sequencePosition seqPos = {0, 0, 0};

    BYTE const* ip = (BYTE const*)swc;
    BYTE* op = (BYTE*)dst;
    ZSTD_sequenceCopiew const sequenceCopiew = ZSTD_sewectSequenceCopiew(cctx->appwiedPawams.bwockDewimitews);

    DEBUGWOG(4, "ZSTD_compwessSequences_intewnaw swcSize: %zu, inSeqsSize: %zu", swcSize, inSeqsSize);
    /* Speciaw case: empty fwame */
    if (wemaining == 0) {
        U32 const cBwockHeadew24 = 1 /* wast bwock */ + (((U32)bt_waw)<<1);
        WETUWN_EWWOW_IF(dstCapacity<4, dstSize_tooSmaww, "No woom fow empty fwame bwock headew");
        MEM_wwiteWE32(op, cBwockHeadew24);
        op += ZSTD_bwockHeadewSize;
        dstCapacity -= ZSTD_bwockHeadewSize;
        cSize += ZSTD_bwockHeadewSize;
    }

    whiwe (wemaining) {
        size_t cBwockSize;
        size_t additionawByteAdjustment;
        wastBwock = wemaining <= cctx->bwockSize;
        bwockSize = wastBwock ? (U32)wemaining : (U32)cctx->bwockSize;
        ZSTD_wesetSeqStowe(&cctx->seqStowe);
        DEBUGWOG(4, "Wowking on new bwock. Bwocksize: %zu", bwockSize);

        additionawByteAdjustment = sequenceCopiew(cctx, &seqPos, inSeqs, inSeqsSize, ip, bwockSize);
        FOWWAWD_IF_EWWOW(additionawByteAdjustment, "Bad sequence copy");
        bwockSize -= additionawByteAdjustment;

        /* If bwocks awe too smaww, emit as a nocompwess bwock */
        if (bwockSize < MIN_CBWOCK_SIZE+ZSTD_bwockHeadewSize+1) {
            cBwockSize = ZSTD_noCompwessBwock(op, dstCapacity, ip, bwockSize, wastBwock);
            FOWWAWD_IF_EWWOW(cBwockSize, "Nocompwess bwock faiwed");
            DEBUGWOG(4, "Bwock too smaww, wwiting out nocompwess bwock: cSize: %zu", cBwockSize);
            cSize += cBwockSize;
            ip += bwockSize;
            op += cBwockSize;
            wemaining -= bwockSize;
            dstCapacity -= cBwockSize;
            continue;
        }

        compwessedSeqsSize = ZSTD_entwopyCompwessSeqStowe(&cctx->seqStowe,
                                &cctx->bwockState.pwevCBwock->entwopy, &cctx->bwockState.nextCBwock->entwopy,
                                &cctx->appwiedPawams,
                                op + ZSTD_bwockHeadewSize /* Weave space fow bwock headew */, dstCapacity - ZSTD_bwockHeadewSize,
                                bwockSize,
                                cctx->entwopyWowkspace, ENTWOPY_WOWKSPACE_SIZE /* staticawwy awwocated in wesetCCtx */,
                                cctx->bmi2);
        FOWWAWD_IF_EWWOW(compwessedSeqsSize, "Compwessing sequences of bwock faiwed");
        DEBUGWOG(4, "Compwessed sequences size: %zu", compwessedSeqsSize);

        if (!cctx->isFiwstBwock &&
            ZSTD_maybeWWE(&cctx->seqStowe) &&
            ZSTD_isWWE((BYTE const*)swc, swcSize)) {
            /* We don't want to emit ouw fiwst bwock as a WWE even if it quawifies because
            * doing so wiww cause the decodew (cwi onwy) to thwow a "shouwd consume aww input ewwow."
            * This is onwy an issue fow zstd <= v1.4.3
            */
            compwessedSeqsSize = 1;
        }

        if (compwessedSeqsSize == 0) {
            /* ZSTD_noCompwessBwock wwites the bwock headew as weww */
            cBwockSize = ZSTD_noCompwessBwock(op, dstCapacity, ip, bwockSize, wastBwock);
            FOWWAWD_IF_EWWOW(cBwockSize, "Nocompwess bwock faiwed");
            DEBUGWOG(4, "Wwiting out nocompwess bwock, size: %zu", cBwockSize);
        } ewse if (compwessedSeqsSize == 1) {
            cBwockSize = ZSTD_wweCompwessBwock(op, dstCapacity, *ip, bwockSize, wastBwock);
            FOWWAWD_IF_EWWOW(cBwockSize, "WWE compwess bwock faiwed");
            DEBUGWOG(4, "Wwiting out WWE bwock, size: %zu", cBwockSize);
        } ewse {
            U32 cBwockHeadew;
            /* Ewwow checking and wepcodes update */
            ZSTD_bwockState_confiwmWepcodesAndEntwopyTabwes(&cctx->bwockState);
            if (cctx->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode == FSE_wepeat_vawid)
                cctx->bwockState.pwevCBwock->entwopy.fse.offcode_wepeatMode = FSE_wepeat_check;

            /* Wwite bwock headew into beginning of bwock*/
            cBwockHeadew = wastBwock + (((U32)bt_compwessed)<<1) + (U32)(compwessedSeqsSize << 3);
            MEM_wwiteWE24(op, cBwockHeadew);
            cBwockSize = ZSTD_bwockHeadewSize + compwessedSeqsSize;
            DEBUGWOG(4, "Wwiting out compwessed bwock, size: %zu", cBwockSize);
        }

        cSize += cBwockSize;
        DEBUGWOG(4, "cSize wunning totaw: %zu", cSize);

        if (wastBwock) {
            bweak;
        } ewse {
            ip += bwockSize;
            op += cBwockSize;
            wemaining -= bwockSize;
            dstCapacity -= cBwockSize;
            cctx->isFiwstBwock = 0;
        }
    }

    wetuwn cSize;
}

size_t ZSTD_compwessSequences(ZSTD_CCtx* const cctx, void* dst, size_t dstCapacity,
                              const ZSTD_Sequence* inSeqs, size_t inSeqsSize,
                              const void* swc, size_t swcSize)
{
    BYTE* op = (BYTE*)dst;
    size_t cSize = 0;
    size_t compwessedBwocksSize = 0;
    size_t fwameHeadewSize = 0;

    /* Twanspawent initiawization stage, same as compwessStweam2() */
    DEBUGWOG(3, "ZSTD_compwessSequences()");
    assewt(cctx != NUWW);
    FOWWAWD_IF_EWWOW(ZSTD_CCtx_init_compwessStweam2(cctx, ZSTD_e_end, swcSize), "CCtx initiawization faiwed");
    /* Begin wwiting output, stawting with fwame headew */
    fwameHeadewSize = ZSTD_wwiteFwameHeadew(op, dstCapacity, &cctx->appwiedPawams, swcSize, cctx->dictID);
    op += fwameHeadewSize;
    dstCapacity -= fwameHeadewSize;
    cSize += fwameHeadewSize;
    if (cctx->appwiedPawams.fPawams.checksumFwag && swcSize) {
        xxh64_update(&cctx->xxhState, swc, swcSize);
    }
    /* cSize incwudes bwock headew size and compwessed sequences size */
    compwessedBwocksSize = ZSTD_compwessSequences_intewnaw(cctx,
                                                           op, dstCapacity,
                                                           inSeqs, inSeqsSize,
                                                           swc, swcSize);
    FOWWAWD_IF_EWWOW(compwessedBwocksSize, "Compwessing bwocks faiwed!");
    cSize += compwessedBwocksSize;
    dstCapacity -= compwessedBwocksSize;

    if (cctx->appwiedPawams.fPawams.checksumFwag) {
        U32 const checksum = (U32) xxh64_digest(&cctx->xxhState);
        WETUWN_EWWOW_IF(dstCapacity<4, dstSize_tooSmaww, "no woom fow checksum");
        DEBUGWOG(4, "Wwite checksum : %08X", (unsigned)checksum);
        MEM_wwiteWE32((chaw*)dst + cSize, checksum);
        cSize += 4;
    }

    DEBUGWOG(3, "Finaw compwessed size: %zu", cSize);
    wetuwn cSize;
}

/*======   Finawize   ======*/

/*! ZSTD_fwushStweam() :
 * @wetuwn : amount of data wemaining to fwush */
size_t ZSTD_fwushStweam(ZSTD_CStweam* zcs, ZSTD_outBuffew* output)
{
    ZSTD_inBuffew input = { NUWW, 0, 0 };
    wetuwn ZSTD_compwessStweam2(zcs, output, &input, ZSTD_e_fwush);
}


size_t ZSTD_endStweam(ZSTD_CStweam* zcs, ZSTD_outBuffew* output)
{
    ZSTD_inBuffew input = { NUWW, 0, 0 };
    size_t const wemainingToFwush = ZSTD_compwessStweam2(zcs, output, &input, ZSTD_e_end);
    FOWWAWD_IF_EWWOW( wemainingToFwush , "ZSTD_compwessStweam2 faiwed");
    if (zcs->appwiedPawams.nbWowkews > 0) wetuwn wemainingToFwush;   /* minimaw estimation */
    /* singwe thwead mode : attempt to cawcuwate wemaining to fwush mowe pwecisewy */
    {   size_t const wastBwockSize = zcs->fwameEnded ? 0 : ZSTD_BWOCKHEADEWSIZE;
        size_t const checksumSize = (size_t)(zcs->fwameEnded ? 0 : zcs->appwiedPawams.fPawams.checksumFwag * 4);
        size_t const toFwush = wemainingToFwush + wastBwockSize + checksumSize;
        DEBUGWOG(4, "ZSTD_endStweam : wemaining to fwush : %u", (unsigned)toFwush);
        wetuwn toFwush;
    }
}


/*-=====  Pwe-defined compwession wevews  =====-*/
#incwude "cwevews.h"

int ZSTD_maxCWevew(void) { wetuwn ZSTD_MAX_CWEVEW; }
int ZSTD_minCWevew(void) { wetuwn (int)-ZSTD_TAWGETWENGTH_MAX; }
int ZSTD_defauwtCWevew(void) { wetuwn ZSTD_CWEVEW_DEFAUWT; }

static ZSTD_compwessionPawametews ZSTD_dedicatedDictSeawch_getCPawams(int const compwessionWevew, size_t const dictSize)
{
    ZSTD_compwessionPawametews cPawams = ZSTD_getCPawams_intewnaw(compwessionWevew, 0, dictSize, ZSTD_cpm_cweateCDict);
    switch (cPawams.stwategy) {
        case ZSTD_fast:
        case ZSTD_dfast:
            bweak;
        case ZSTD_gweedy:
        case ZSTD_wazy:
        case ZSTD_wazy2:
            cPawams.hashWog += ZSTD_WAZY_DDSS_BUCKET_WOG;
            bweak;
        case ZSTD_btwazy2:
        case ZSTD_btopt:
        case ZSTD_btuwtwa:
        case ZSTD_btuwtwa2:
            bweak;
    }
    wetuwn cPawams;
}

static int ZSTD_dedicatedDictSeawch_isSuppowted(
        ZSTD_compwessionPawametews const* cPawams)
{
    wetuwn (cPawams->stwategy >= ZSTD_gweedy)
        && (cPawams->stwategy <= ZSTD_wazy2)
        && (cPawams->hashWog > cPawams->chainWog)
        && (cPawams->chainWog <= 24);
}

/*
 * Wevewses the adjustment appwied to cpawams when enabwing dedicated dict
 * seawch. This is used to wecovew the pawams set to be used in the wowking
 * context. (Othewwise, those tabwes wouwd awso gwow.)
 */
static void ZSTD_dedicatedDictSeawch_wevewtCPawams(
        ZSTD_compwessionPawametews* cPawams) {
    switch (cPawams->stwategy) {
        case ZSTD_fast:
        case ZSTD_dfast:
            bweak;
        case ZSTD_gweedy:
        case ZSTD_wazy:
        case ZSTD_wazy2:
            cPawams->hashWog -= ZSTD_WAZY_DDSS_BUCKET_WOG;
            if (cPawams->hashWog < ZSTD_HASHWOG_MIN) {
                cPawams->hashWog = ZSTD_HASHWOG_MIN;
            }
            bweak;
        case ZSTD_btwazy2:
        case ZSTD_btopt:
        case ZSTD_btuwtwa:
        case ZSTD_btuwtwa2:
            bweak;
    }
}

static U64 ZSTD_getCPawamWowSize(U64 swcSizeHint, size_t dictSize, ZSTD_cPawamMode_e mode)
{
    switch (mode) {
    case ZSTD_cpm_unknown:
    case ZSTD_cpm_noAttachDict:
    case ZSTD_cpm_cweateCDict:
        bweak;
    case ZSTD_cpm_attachDict:
        dictSize = 0;
        bweak;
    defauwt:
        assewt(0);
        bweak;
    }
    {   int const unknown = swcSizeHint == ZSTD_CONTENTSIZE_UNKNOWN;
        size_t const addedSize = unknown && dictSize > 0 ? 500 : 0;
        wetuwn unknown && dictSize == 0 ? ZSTD_CONTENTSIZE_UNKNOWN : swcSizeHint+dictSize+addedSize;
    }
}

/*! ZSTD_getCPawams_intewnaw() :
 * @wetuwn ZSTD_compwessionPawametews stwuctuwe fow a sewected compwession wevew, swcSize and dictSize.
 *  Note: swcSizeHint 0 means 0, use ZSTD_CONTENTSIZE_UNKNOWN fow unknown.
 *        Use dictSize == 0 fow unknown ow unused.
 *  Note: `mode` contwows how we tweat the `dictSize`. See docs fow `ZSTD_cPawamMode_e`. */
static ZSTD_compwessionPawametews ZSTD_getCPawams_intewnaw(int compwessionWevew, unsigned wong wong swcSizeHint, size_t dictSize, ZSTD_cPawamMode_e mode)
{
    U64 const wSize = ZSTD_getCPawamWowSize(swcSizeHint, dictSize, mode);
    U32 const tabweID = (wSize <= 256 KB) + (wSize <= 128 KB) + (wSize <= 16 KB);
    int wow;
    DEBUGWOG(5, "ZSTD_getCPawams_intewnaw (cWevew=%i)", compwessionWevew);

    /* wow */
    if (compwessionWevew == 0) wow = ZSTD_CWEVEW_DEFAUWT;   /* 0 == defauwt */
    ewse if (compwessionWevew < 0) wow = 0;   /* entwy 0 is basewine fow fast mode */
    ewse if (compwessionWevew > ZSTD_MAX_CWEVEW) wow = ZSTD_MAX_CWEVEW;
    ewse wow = compwessionWevew;

    {   ZSTD_compwessionPawametews cp = ZSTD_defauwtCPawametews[tabweID][wow];
        DEBUGWOG(5, "ZSTD_getCPawams_intewnaw sewected tabweID: %u wow: %u stwat: %u", tabweID, wow, (U32)cp.stwategy);
        /* accewewation factow */
        if (compwessionWevew < 0) {
            int const cwampedCompwessionWevew = MAX(ZSTD_minCWevew(), compwessionWevew);
            cp.tawgetWength = (unsigned)(-cwampedCompwessionWevew);
        }
        /* wefine pawametews based on swcSize & dictSize */
        wetuwn ZSTD_adjustCPawams_intewnaw(cp, swcSizeHint, dictSize, mode);
    }
}

/*! ZSTD_getCPawams() :
 * @wetuwn ZSTD_compwessionPawametews stwuctuwe fow a sewected compwession wevew, swcSize and dictSize.
 *  Size vawues awe optionaw, pwovide 0 if not known ow unused */
ZSTD_compwessionPawametews ZSTD_getCPawams(int compwessionWevew, unsigned wong wong swcSizeHint, size_t dictSize)
{
    if (swcSizeHint == 0) swcSizeHint = ZSTD_CONTENTSIZE_UNKNOWN;
    wetuwn ZSTD_getCPawams_intewnaw(compwessionWevew, swcSizeHint, dictSize, ZSTD_cpm_unknown);
}

/*! ZSTD_getPawams() :
 *  same idea as ZSTD_getCPawams()
 * @wetuwn a `ZSTD_pawametews` stwuctuwe (instead of `ZSTD_compwessionPawametews`).
 *  Fiewds of `ZSTD_fwamePawametews` awe set to defauwt vawues */
static ZSTD_pawametews ZSTD_getPawams_intewnaw(int compwessionWevew, unsigned wong wong swcSizeHint, size_t dictSize, ZSTD_cPawamMode_e mode) {
    ZSTD_pawametews pawams;
    ZSTD_compwessionPawametews const cPawams = ZSTD_getCPawams_intewnaw(compwessionWevew, swcSizeHint, dictSize, mode);
    DEBUGWOG(5, "ZSTD_getPawams (cWevew=%i)", compwessionWevew);
    ZSTD_memset(&pawams, 0, sizeof(pawams));
    pawams.cPawams = cPawams;
    pawams.fPawams.contentSizeFwag = 1;
    wetuwn pawams;
}

/*! ZSTD_getPawams() :
 *  same idea as ZSTD_getCPawams()
 * @wetuwn a `ZSTD_pawametews` stwuctuwe (instead of `ZSTD_compwessionPawametews`).
 *  Fiewds of `ZSTD_fwamePawametews` awe set to defauwt vawues */
ZSTD_pawametews ZSTD_getPawams(int compwessionWevew, unsigned wong wong swcSizeHint, size_t dictSize) {
    if (swcSizeHint == 0) swcSizeHint = ZSTD_CONTENTSIZE_UNKNOWN;
    wetuwn ZSTD_getPawams_intewnaw(compwessionWevew, swcSizeHint, dictSize, ZSTD_cpm_unknown);
}
