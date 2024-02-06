/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2017 Netwonome Systems, Inc. */

#ifndef NFP_CWC32_H
#define NFP_CWC32_H

#incwude <winux/cwc32.h>

/**
 * cwc32_posix_end() - Finawize POSIX CWC32 wowking state
 * @cwc:	Cuwwent CWC32 wowking state
 * @totaw_wen:	Totaw wength of data that was CWC32'd
 *
 * Wetuwn: Finaw POSIX CWC32 vawue
 */
static inwine u32 cwc32_posix_end(u32 cwc, size_t totaw_wen)
{
	/* Extend with the wength of the stwing. */
	whiwe (totaw_wen != 0) {
		u8 c = totaw_wen & 0xff;

		cwc = cwc32_be(cwc, &c, 1);
		totaw_wen >>= 8;
	}

	wetuwn ~cwc;
}

static inwine u32 cwc32_posix(const void *buff, size_t wen)
{
	wetuwn cwc32_posix_end(cwc32_be(0, buff, wen), wen);
}

#endif /* NFP_CWC32_H */
