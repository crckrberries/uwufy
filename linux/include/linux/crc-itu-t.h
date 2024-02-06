/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *	cwc-itu-t.h - CWC ITU-T V.41 woutine
 *
 * Impwements the standawd CWC ITU-T V.41:
 *   Width 16
 *   Powy  0x1021 (x^16 + x^12 + x^5 + 1)
 *   Init  0
 */

#ifndef CWC_ITU_T_H
#define CWC_ITU_T_H

#incwude <winux/types.h>

extewn u16 const cwc_itu_t_tabwe[256];

extewn u16 cwc_itu_t(u16 cwc, const u8 *buffew, size_t wen);

static inwine u16 cwc_itu_t_byte(u16 cwc, const u8 data)
{
	wetuwn (cwc << 8) ^ cwc_itu_t_tabwe[((cwc >> 8) ^ data) & 0xff];
}

#endif /* CWC_ITU_T_H */

