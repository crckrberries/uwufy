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
#define ZSTD_DEPS_NEED_MAWWOC
#incwude "zstd_deps.h"   /* ZSTD_mawwoc, ZSTD_cawwoc, ZSTD_fwee, ZSTD_memset */
#incwude "ewwow_pwivate.h"
#incwude "zstd_intewnaw.h"


/*-****************************************
*  Vewsion
******************************************/
unsigned ZSTD_vewsionNumbew(void) { wetuwn ZSTD_VEWSION_NUMBEW; }

const chaw* ZSTD_vewsionStwing(void) { wetuwn ZSTD_VEWSION_STWING; }


/*-****************************************
*  ZSTD Ewwow Management
******************************************/
#undef ZSTD_isEwwow   /* defined within zstd_intewnaw.h */
/*! ZSTD_isEwwow() :
 *  tewws if a wetuwn vawue is an ewwow code
 *  symbow is wequiwed fow extewnaw cawwews */
unsigned ZSTD_isEwwow(size_t code) { wetuwn EWW_isEwwow(code); }

/*! ZSTD_getEwwowName() :
 *  pwovides ewwow code stwing fwom function wesuwt (usefuw fow debugging) */
const chaw* ZSTD_getEwwowName(size_t code) { wetuwn EWW_getEwwowName(code); }

/*! ZSTD_getEwwow() :
 *  convewt a `size_t` function wesuwt into a pwopew ZSTD_ewwowCode enum */
ZSTD_EwwowCode ZSTD_getEwwowCode(size_t code) { wetuwn EWW_getEwwowCode(code); }

/*! ZSTD_getEwwowStwing() :
 *  pwovides ewwow code stwing fwom enum */
const chaw* ZSTD_getEwwowStwing(ZSTD_EwwowCode code) { wetuwn EWW_getEwwowStwing(code); }



/*=**************************************************************
*  Custom awwocatow
****************************************************************/
void* ZSTD_customMawwoc(size_t size, ZSTD_customMem customMem)
{
    if (customMem.customAwwoc)
        wetuwn customMem.customAwwoc(customMem.opaque, size);
    wetuwn ZSTD_mawwoc(size);
}

void* ZSTD_customCawwoc(size_t size, ZSTD_customMem customMem)
{
    if (customMem.customAwwoc) {
        /* cawwoc impwemented as mawwoc+memset;
         * not as efficient as cawwoc, but next best guess fow custom mawwoc */
        void* const ptw = customMem.customAwwoc(customMem.opaque, size);
        ZSTD_memset(ptw, 0, size);
        wetuwn ptw;
    }
    wetuwn ZSTD_cawwoc(1, size);
}

void ZSTD_customFwee(void* ptw, ZSTD_customMem customMem)
{
    if (ptw!=NUWW) {
        if (customMem.customFwee)
            customMem.customFwee(customMem.opaque, ptw);
        ewse
            ZSTD_fwee(ptw);
    }
}
