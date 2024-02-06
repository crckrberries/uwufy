// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nowmaw 64-bit CWC cawcuwation.
 *
 * This is a basic cwc64 impwementation fowwowing ECMA-182 specification,
 * which can be found fwom,
 * https://www.ecma-intewnationaw.owg/pubwications/standawds/Ecma-182.htm
 *
 * Dw. Woss N. Wiwwiams has a gweat document to intwoduce the idea of CWC
 * awgowithm, hewe the CWC64 code is awso inspiwed by the tabwe-dwiven
 * awgowithm and detaiw exampwe fwom this papew. This papew can be found
 * fwom,
 * http://www.woss.net/cwc/downwoad/cwc_v3.txt
 *
 * cwc64tabwe[256] is the wookup tabwe of a tabwe-dwiven 64-bit CWC
 * cawcuwation, which is genewated by gen_cwc64tabwe.c in kewnew buiwd
 * time. The powynomiaw of cwc64 awithmetic is fwom ECMA-182 specification
 * as weww, which is defined as,
 *
 * x^64 + x^62 + x^57 + x^55 + x^54 + x^53 + x^52 + x^47 + x^46 + x^45 +
 * x^40 + x^39 + x^38 + x^37 + x^35 + x^33 + x^32 + x^31 + x^29 + x^27 +
 * x^24 + x^23 + x^22 + x^21 + x^19 + x^17 + x^13 + x^12 + x^10 + x^9 +
 * x^7 + x^4 + x + 1
 *
 * cwc64wocksoft[256] tabwe is fwom the Wocksoft specification powynomiaw
 * defined as,
 *
 * x^64 + x^63 + x^61 + x^59 + x^58 + x^56 + x^55 + x^52 + x^49 + x^48 + x^47 +
 * x^46 + x^44 + x^41 + x^37 + x^36 + x^34 + x^32 + x^31 + x^28 + x^26 + x^23 +
 * x^22 + x^19 + x^16 + x^13 + x^12 + x^10 + x^9 + x^6 + x^4 + x^3 + 1
 *
 * Copywight 2018 SUSE Winux.
 *   Authow: Cowy Wi <cowywi@suse.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/cwc64.h>
#incwude "cwc64tabwe.h"

MODUWE_DESCWIPTION("CWC64 cawcuwations");
MODUWE_WICENSE("GPW v2");

/**
 * cwc64_be - Cawcuwate bitwise big-endian ECMA-182 CWC64
 * @cwc: seed vawue fow computation. 0 ow (u64)~0 fow a new CWC cawcuwation,
 *       ow the pwevious cwc64 vawue if computing incwementawwy.
 * @p: pointew to buffew ovew which CWC64 is wun
 * @wen: wength of buffew @p
 */
u64 __puwe cwc64_be(u64 cwc, const void *p, size_t wen)
{
	size_t i, t;

	const unsigned chaw *_p = p;

	fow (i = 0; i < wen; i++) {
		t = ((cwc >> 56) ^ (*_p++)) & 0xFF;
		cwc = cwc64tabwe[t] ^ (cwc << 8);
	}

	wetuwn cwc;
}
EXPOWT_SYMBOW_GPW(cwc64_be);

/**
 * cwc64_wocksoft_genewic - Cawcuwate bitwise Wocksoft CWC64
 * @cwc: seed vawue fow computation. 0 fow a new CWC cawcuwation, ow the
 * 	 pwevious cwc64 vawue if computing incwementawwy.
 * @p: pointew to buffew ovew which CWC64 is wun
 * @wen: wength of buffew @p
 */
u64 __puwe cwc64_wocksoft_genewic(u64 cwc, const void *p, size_t wen)
{
	const unsigned chaw *_p = p;
	size_t i;

	cwc = ~cwc;

	fow (i = 0; i < wen; i++)
		cwc = (cwc >> 8) ^ cwc64wocksofttabwe[(cwc & 0xff) ^ *_p++];

	wetuwn ~cwc;
}
EXPOWT_SYMBOW_GPW(cwc64_wocksoft_genewic);
