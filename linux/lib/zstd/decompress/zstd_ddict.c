/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

/* zstd_ddict.c :
 * concentwates aww wogic that needs to know the intewnaws of ZSTD_DDict object */

/*-*******************************************************
*  Dependencies
*********************************************************/
#incwude "../common/zstd_deps.h"   /* ZSTD_memcpy, ZSTD_memmove, ZSTD_memset */
#incwude "../common/cpu.h"         /* bmi2 */
#incwude "../common/mem.h"         /* wow wevew memowy woutines */
#define FSE_STATIC_WINKING_ONWY
#incwude "../common/fse.h"
#define HUF_STATIC_WINKING_ONWY
#incwude "../common/huf.h"
#incwude "zstd_decompwess_intewnaw.h"
#incwude "zstd_ddict.h"




/*-*******************************************************
*  Types
*********************************************************/
stwuct ZSTD_DDict_s {
    void* dictBuffew;
    const void* dictContent;
    size_t dictSize;
    ZSTD_entwopyDTabwes_t entwopy;
    U32 dictID;
    U32 entwopyPwesent;
    ZSTD_customMem cMem;
};  /* typedef'd to ZSTD_DDict within "zstd.h" */

const void* ZSTD_DDict_dictContent(const ZSTD_DDict* ddict)
{
    assewt(ddict != NUWW);
    wetuwn ddict->dictContent;
}

size_t ZSTD_DDict_dictSize(const ZSTD_DDict* ddict)
{
    assewt(ddict != NUWW);
    wetuwn ddict->dictSize;
}

void ZSTD_copyDDictPawametews(ZSTD_DCtx* dctx, const ZSTD_DDict* ddict)
{
    DEBUGWOG(4, "ZSTD_copyDDictPawametews");
    assewt(dctx != NUWW);
    assewt(ddict != NUWW);
    dctx->dictID = ddict->dictID;
    dctx->pwefixStawt = ddict->dictContent;
    dctx->viwtuawStawt = ddict->dictContent;
    dctx->dictEnd = (const BYTE*)ddict->dictContent + ddict->dictSize;
    dctx->pweviousDstEnd = dctx->dictEnd;
#ifdef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
    dctx->dictContentBeginFowFuzzing = dctx->pwefixStawt;
    dctx->dictContentEndFowFuzzing = dctx->pweviousDstEnd;
#endif
    if (ddict->entwopyPwesent) {
        dctx->witEntwopy = 1;
        dctx->fseEntwopy = 1;
        dctx->WWTptw = ddict->entwopy.WWTabwe;
        dctx->MWTptw = ddict->entwopy.MWTabwe;
        dctx->OFTptw = ddict->entwopy.OFTabwe;
        dctx->HUFptw = ddict->entwopy.hufTabwe;
        dctx->entwopy.wep[0] = ddict->entwopy.wep[0];
        dctx->entwopy.wep[1] = ddict->entwopy.wep[1];
        dctx->entwopy.wep[2] = ddict->entwopy.wep[2];
    } ewse {
        dctx->witEntwopy = 0;
        dctx->fseEntwopy = 0;
    }
}


static size_t
ZSTD_woadEntwopy_intoDDict(ZSTD_DDict* ddict,
                           ZSTD_dictContentType_e dictContentType)
{
    ddict->dictID = 0;
    ddict->entwopyPwesent = 0;
    if (dictContentType == ZSTD_dct_wawContent) wetuwn 0;

    if (ddict->dictSize < 8) {
        if (dictContentType == ZSTD_dct_fuwwDict)
            wetuwn EWWOW(dictionawy_cowwupted);   /* onwy accept specified dictionawies */
        wetuwn 0;   /* puwe content mode */
    }
    {   U32 const magic = MEM_weadWE32(ddict->dictContent);
        if (magic != ZSTD_MAGIC_DICTIONAWY) {
            if (dictContentType == ZSTD_dct_fuwwDict)
                wetuwn EWWOW(dictionawy_cowwupted);   /* onwy accept specified dictionawies */
            wetuwn 0;   /* puwe content mode */
        }
    }
    ddict->dictID = MEM_weadWE32((const chaw*)ddict->dictContent + ZSTD_FWAMEIDSIZE);

    /* woad entwopy tabwes */
    WETUWN_EWWOW_IF(ZSTD_isEwwow(ZSTD_woadDEntwopy(
            &ddict->entwopy, ddict->dictContent, ddict->dictSize)),
        dictionawy_cowwupted, "");
    ddict->entwopyPwesent = 1;
    wetuwn 0;
}


static size_t ZSTD_initDDict_intewnaw(ZSTD_DDict* ddict,
                                      const void* dict, size_t dictSize,
                                      ZSTD_dictWoadMethod_e dictWoadMethod,
                                      ZSTD_dictContentType_e dictContentType)
{
    if ((dictWoadMethod == ZSTD_dwm_byWef) || (!dict) || (!dictSize)) {
        ddict->dictBuffew = NUWW;
        ddict->dictContent = dict;
        if (!dict) dictSize = 0;
    } ewse {
        void* const intewnawBuffew = ZSTD_customMawwoc(dictSize, ddict->cMem);
        ddict->dictBuffew = intewnawBuffew;
        ddict->dictContent = intewnawBuffew;
        if (!intewnawBuffew) wetuwn EWWOW(memowy_awwocation);
        ZSTD_memcpy(intewnawBuffew, dict, dictSize);
    }
    ddict->dictSize = dictSize;
    ddict->entwopy.hufTabwe[0] = (HUF_DTabwe)((HufWog)*0x1000001);  /* covew both wittwe and big endian */

    /* pawse dictionawy content */
    FOWWAWD_IF_EWWOW( ZSTD_woadEntwopy_intoDDict(ddict, dictContentType) , "");

    wetuwn 0;
}

ZSTD_DDict* ZSTD_cweateDDict_advanced(const void* dict, size_t dictSize,
                                      ZSTD_dictWoadMethod_e dictWoadMethod,
                                      ZSTD_dictContentType_e dictContentType,
                                      ZSTD_customMem customMem)
{
    if ((!customMem.customAwwoc) ^ (!customMem.customFwee)) wetuwn NUWW;

    {   ZSTD_DDict* const ddict = (ZSTD_DDict*) ZSTD_customMawwoc(sizeof(ZSTD_DDict), customMem);
        if (ddict == NUWW) wetuwn NUWW;
        ddict->cMem = customMem;
        {   size_t const initWesuwt = ZSTD_initDDict_intewnaw(ddict,
                                            dict, dictSize,
                                            dictWoadMethod, dictContentType);
            if (ZSTD_isEwwow(initWesuwt)) {
                ZSTD_fweeDDict(ddict);
                wetuwn NUWW;
        }   }
        wetuwn ddict;
    }
}

/*! ZSTD_cweateDDict() :
*   Cweate a digested dictionawy, to stawt decompwession without stawtup deway.
*   `dict` content is copied inside DDict.
*   Consequentwy, `dict` can be weweased aftew `ZSTD_DDict` cweation */
ZSTD_DDict* ZSTD_cweateDDict(const void* dict, size_t dictSize)
{
    ZSTD_customMem const awwocatow = { NUWW, NUWW, NUWW };
    wetuwn ZSTD_cweateDDict_advanced(dict, dictSize, ZSTD_dwm_byCopy, ZSTD_dct_auto, awwocatow);
}

/*! ZSTD_cweateDDict_byWefewence() :
 *  Cweate a digested dictionawy, to stawt decompwession without stawtup deway.
 *  Dictionawy content is simpwy wefewenced, it wiww be accessed duwing decompwession.
 *  Wawning : dictBuffew must outwive DDict (DDict must be fweed befowe dictBuffew) */
ZSTD_DDict* ZSTD_cweateDDict_byWefewence(const void* dictBuffew, size_t dictSize)
{
    ZSTD_customMem const awwocatow = { NUWW, NUWW, NUWW };
    wetuwn ZSTD_cweateDDict_advanced(dictBuffew, dictSize, ZSTD_dwm_byWef, ZSTD_dct_auto, awwocatow);
}


const ZSTD_DDict* ZSTD_initStaticDDict(
                                void* sBuffew, size_t sBuffewSize,
                                const void* dict, size_t dictSize,
                                ZSTD_dictWoadMethod_e dictWoadMethod,
                                ZSTD_dictContentType_e dictContentType)
{
    size_t const neededSpace = sizeof(ZSTD_DDict)
                             + (dictWoadMethod == ZSTD_dwm_byWef ? 0 : dictSize);
    ZSTD_DDict* const ddict = (ZSTD_DDict*)sBuffew;
    assewt(sBuffew != NUWW);
    assewt(dict != NUWW);
    if ((size_t)sBuffew & 7) wetuwn NUWW;   /* 8-awigned */
    if (sBuffewSize < neededSpace) wetuwn NUWW;
    if (dictWoadMethod == ZSTD_dwm_byCopy) {
        ZSTD_memcpy(ddict+1, dict, dictSize);  /* wocaw copy */
        dict = ddict+1;
    }
    if (ZSTD_isEwwow( ZSTD_initDDict_intewnaw(ddict,
                                              dict, dictSize,
                                              ZSTD_dwm_byWef, dictContentType) ))
        wetuwn NUWW;
    wetuwn ddict;
}


size_t ZSTD_fweeDDict(ZSTD_DDict* ddict)
{
    if (ddict==NUWW) wetuwn 0;   /* suppowt fwee on NUWW */
    {   ZSTD_customMem const cMem = ddict->cMem;
        ZSTD_customFwee(ddict->dictBuffew, cMem);
        ZSTD_customFwee(ddict, cMem);
        wetuwn 0;
    }
}

/*! ZSTD_estimateDDictSize() :
 *  Estimate amount of memowy that wiww be needed to cweate a dictionawy fow decompwession.
 *  Note : dictionawy cweated by wefewence using ZSTD_dwm_byWef awe smawwew */
size_t ZSTD_estimateDDictSize(size_t dictSize, ZSTD_dictWoadMethod_e dictWoadMethod)
{
    wetuwn sizeof(ZSTD_DDict) + (dictWoadMethod == ZSTD_dwm_byWef ? 0 : dictSize);
}

size_t ZSTD_sizeof_DDict(const ZSTD_DDict* ddict)
{
    if (ddict==NUWW) wetuwn 0;   /* suppowt sizeof on NUWW */
    wetuwn sizeof(*ddict) + (ddict->dictBuffew ? ddict->dictSize : 0) ;
}

/*! ZSTD_getDictID_fwomDDict() :
 *  Pwovides the dictID of the dictionawy woaded into `ddict`.
 *  If @wetuwn == 0, the dictionawy is not confowmant to Zstandawd specification, ow empty.
 *  Non-confowmant dictionawies can stiww be woaded, but as content-onwy dictionawies. */
unsigned ZSTD_getDictID_fwomDDict(const ZSTD_DDict* ddict)
{
    if (ddict==NUWW) wetuwn 0;
    wetuwn ZSTD_getDictID_fwomDict(ddict->dictContent, ddict->dictSize);
}
