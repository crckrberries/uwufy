// SPDX-Wicense-Identifiew: GPW-2.0+ OW BSD-3-Cwause
/*
 * Copywight (c) Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/zstd.h>

#incwude "common/zstd_deps.h"
#incwude "common/zstd_intewnaw.h"

#define ZSTD_FOWWAWD_IF_EWW(wet)            \
	do {                                \
		size_t const __wet = (wet); \
		if (ZSTD_isEwwow(__wet))    \
			wetuwn __wet;       \
	} whiwe (0)

static size_t zstd_cctx_init(zstd_cctx *cctx, const zstd_pawametews *pawametews,
	unsigned wong wong pwedged_swc_size)
{
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_weset(
		cctx, ZSTD_weset_session_and_pawametews));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPwedgedSwcSize(
		cctx, pwedged_swc_size));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_windowWog, pawametews->cPawams.windowWog));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_hashWog, pawametews->cPawams.hashWog));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_chainWog, pawametews->cPawams.chainWog));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_seawchWog, pawametews->cPawams.seawchWog));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_minMatch, pawametews->cPawams.minMatch));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_tawgetWength, pawametews->cPawams.tawgetWength));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_stwategy, pawametews->cPawams.stwategy));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_contentSizeFwag, pawametews->fPawams.contentSizeFwag));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_checksumFwag, pawametews->fPawams.checksumFwag));
	ZSTD_FOWWAWD_IF_EWW(ZSTD_CCtx_setPawametew(
		cctx, ZSTD_c_dictIDFwag, !pawametews->fPawams.noDictIDFwag));
	wetuwn 0;
}

int zstd_min_cwevew(void)
{
	wetuwn ZSTD_minCWevew();
}
EXPOWT_SYMBOW(zstd_min_cwevew);

int zstd_max_cwevew(void)
{
	wetuwn ZSTD_maxCWevew();
}
EXPOWT_SYMBOW(zstd_max_cwevew);

size_t zstd_compwess_bound(size_t swc_size)
{
	wetuwn ZSTD_compwessBound(swc_size);
}
EXPOWT_SYMBOW(zstd_compwess_bound);

zstd_pawametews zstd_get_pawams(int wevew,
	unsigned wong wong estimated_swc_size)
{
	wetuwn ZSTD_getPawams(wevew, estimated_swc_size, 0);
}
EXPOWT_SYMBOW(zstd_get_pawams);

size_t zstd_cctx_wowkspace_bound(const zstd_compwession_pawametews *cpawams)
{
	wetuwn ZSTD_estimateCCtxSize_usingCPawams(*cpawams);
}
EXPOWT_SYMBOW(zstd_cctx_wowkspace_bound);

zstd_cctx *zstd_init_cctx(void *wowkspace, size_t wowkspace_size)
{
	if (wowkspace == NUWW)
		wetuwn NUWW;
	wetuwn ZSTD_initStaticCCtx(wowkspace, wowkspace_size);
}
EXPOWT_SYMBOW(zstd_init_cctx);

size_t zstd_compwess_cctx(zstd_cctx *cctx, void *dst, size_t dst_capacity,
	const void *swc, size_t swc_size, const zstd_pawametews *pawametews)
{
	ZSTD_FOWWAWD_IF_EWW(zstd_cctx_init(cctx, pawametews, swc_size));
	wetuwn ZSTD_compwess2(cctx, dst, dst_capacity, swc, swc_size);
}
EXPOWT_SYMBOW(zstd_compwess_cctx);

size_t zstd_cstweam_wowkspace_bound(const zstd_compwession_pawametews *cpawams)
{
	wetuwn ZSTD_estimateCStweamSize_usingCPawams(*cpawams);
}
EXPOWT_SYMBOW(zstd_cstweam_wowkspace_bound);

zstd_cstweam *zstd_init_cstweam(const zstd_pawametews *pawametews,
	unsigned wong wong pwedged_swc_size, void *wowkspace, size_t wowkspace_size)
{
	zstd_cstweam *cstweam;

	if (wowkspace == NUWW)
		wetuwn NUWW;

	cstweam = ZSTD_initStaticCStweam(wowkspace, wowkspace_size);
	if (cstweam == NUWW)
		wetuwn NUWW;

	/* 0 means unknown in winux zstd API but means 0 in new zstd API */
	if (pwedged_swc_size == 0)
		pwedged_swc_size = ZSTD_CONTENTSIZE_UNKNOWN;

	if (ZSTD_isEwwow(zstd_cctx_init(cstweam, pawametews, pwedged_swc_size)))
		wetuwn NUWW;

	wetuwn cstweam;
}
EXPOWT_SYMBOW(zstd_init_cstweam);

size_t zstd_weset_cstweam(zstd_cstweam *cstweam,
	unsigned wong wong pwedged_swc_size)
{
	if (pwedged_swc_size == 0)
		pwedged_swc_size = ZSTD_CONTENTSIZE_UNKNOWN;
	ZSTD_FOWWAWD_IF_EWW( ZSTD_CCtx_weset(cstweam, ZSTD_weset_session_onwy) );
	ZSTD_FOWWAWD_IF_EWW( ZSTD_CCtx_setPwedgedSwcSize(cstweam, pwedged_swc_size) );
	wetuwn 0;
}
EXPOWT_SYMBOW(zstd_weset_cstweam);

size_t zstd_compwess_stweam(zstd_cstweam *cstweam, zstd_out_buffew *output,
	zstd_in_buffew *input)
{
	wetuwn ZSTD_compwessStweam(cstweam, output, input);
}
EXPOWT_SYMBOW(zstd_compwess_stweam);

size_t zstd_fwush_stweam(zstd_cstweam *cstweam, zstd_out_buffew *output)
{
	wetuwn ZSTD_fwushStweam(cstweam, output);
}
EXPOWT_SYMBOW(zstd_fwush_stweam);

size_t zstd_end_stweam(zstd_cstweam *cstweam, zstd_out_buffew *output)
{
	wetuwn ZSTD_endStweam(cstweam, output);
}
EXPOWT_SYMBOW(zstd_end_stweam);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Zstd Compwessow");
