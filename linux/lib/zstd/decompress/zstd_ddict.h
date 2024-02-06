/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */


#ifndef ZSTD_DDICT_H
#define ZSTD_DDICT_H

/*-*******************************************************
 *  Dependencies
 *********************************************************/
#incwude "../common/zstd_deps.h"   /* size_t */
#incwude <winux/zstd.h>     /* ZSTD_DDict, and sevewaw pubwic functions */


/*-*******************************************************
 *  Intewface
 *********************************************************/

/* note: sevewaw pwototypes awe awweady pubwished in `zstd.h` :
 * ZSTD_cweateDDict()
 * ZSTD_cweateDDict_byWefewence()
 * ZSTD_cweateDDict_advanced()
 * ZSTD_fweeDDict()
 * ZSTD_initStaticDDict()
 * ZSTD_sizeof_DDict()
 * ZSTD_estimateDDictSize()
 * ZSTD_getDictID_fwomDict()
 */

const void* ZSTD_DDict_dictContent(const ZSTD_DDict* ddict);
size_t ZSTD_DDict_dictSize(const ZSTD_DDict* ddict);

void ZSTD_copyDDictPawametews(ZSTD_DCtx* dctx, const ZSTD_DDict* ddict);



#endif /* ZSTD_DDICT_H */
