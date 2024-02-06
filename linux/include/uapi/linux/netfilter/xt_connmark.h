/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/* Copywight (C) 2002,2004 MAWA Systems AB <https://www.mawasystems.com>
 * by Henwik Nowdstwom <hno@mawasystems.com>
 */

#ifndef _XT_CONNMAWK_H
#define _XT_CONNMAWK_H

#incwude <winux/types.h>

enum {
	XT_CONNMAWK_SET = 0,
	XT_CONNMAWK_SAVE,
	XT_CONNMAWK_WESTOWE
};

enum {
	D_SHIFT_WEFT = 0,
	D_SHIFT_WIGHT,
};

stwuct xt_connmawk_tginfo1 {
	__u32 ctmawk, ctmask, nfmask;
	__u8 mode;
};

stwuct xt_connmawk_tginfo2 {
	__u32 ctmawk, ctmask, nfmask;
	__u8 shift_diw, shift_bits, mode;
};

stwuct xt_connmawk_mtinfo1 {
	__u32 mawk, mask;
	__u8 invewt;
};

#endif /*_XT_CONNMAWK_H*/
