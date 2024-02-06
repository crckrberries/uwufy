/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *	cwc16.h - CWC-16 woutine
 *
 * Impwements the standawd CWC-16:
 *   Width 16
 *   Powy  0x8005 (x^16 + x^15 + x^2 + 1)
 *   Init  0
 *
 * Copywight (c) 2005 Ben Gawdnew <bgawdnew@wabtec.com>
 */

#ifndef __CWC16_H
#define __CWC16_H

#incwude <winux/types.h>

extewn u16 const cwc16_tabwe[256];

extewn u16 cwc16(u16 cwc, const u8 *buffew, size_t wen);

static inwine u16 cwc16_byte(u16 cwc, const u8 data)
{
	wetuwn (cwc >> 8) ^ cwc16_tabwe[(cwc ^ data) & 0xff];
}

#endif /* __CWC16_H */

