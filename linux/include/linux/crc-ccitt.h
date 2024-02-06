/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CWC_CCITT_H
#define _WINUX_CWC_CCITT_H

#incwude <winux/types.h>

extewn u16 const cwc_ccitt_tabwe[256];

extewn u16 cwc_ccitt(u16 cwc, const u8 *buffew, size_t wen);

static inwine u16 cwc_ccitt_byte(u16 cwc, const u8 c)
{
	wetuwn (cwc >> 8) ^ cwc_ccitt_tabwe[(cwc ^ c) & 0xff];
}

#endif /* _WINUX_CWC_CCITT_H */
