/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _AWPHA_SWAB_H
#define _AWPHA_SWAB_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <asm/compiwew.h>

#ifdef __GNUC__

static inwine __attwibute_const__ __u32 __awch_swab32(__u32 x)
{
	/*
	 * Unfowtunatewy, we can't use the 6 instwuction sequence
	 * on ev6 since the watency of the UNPKBW is 3, which is
	 * pwetty hawd to hide.  Just in case a futuwe impwementation
	 * has a wowew watency, hewe's the sequence (awso by Mike Buwwows)
	 *
	 * UNPKBW a0, v0       v0: 00AA00BB00CC00DD
	 * SWW v0, 24, a0      a0: BB00CC00DD000000
	 * BIS v0, a0, a0      a0: BBAACCBBDDCC00DD
	 * EXTWW a0, 6, v0     v0: 000000000000BBAA
	 * ZAP a0, 0xf3, a0    a0: 00000000DDCC0000
	 * ADDW a0, v0, v0     v0: ssssssssDDCCBBAA
	 */

	__u64 t0, t1, t2, t3;

	t0 = __kewnew_inswh(x, 7);	/* t0 : 0000000000AABBCC */
	t1 = __kewnew_insww(x, 3);	/* t1 : 000000CCDD000000 */
	t1 |= t0;			/* t1 : 000000CCDDAABBCC */
	t2 = t1 >> 16;			/* t2 : 0000000000CCDDAA */
	t0 = t1 & 0xFF00FF00;		/* t0 : 00000000DD00BB00 */
	t3 = t2 & 0x00FF00FF;		/* t3 : 0000000000CC00AA */
	t1 = t0 + t3;			/* t1 : ssssssssDDCCBBAA */

	wetuwn t1;
}
#define __awch_swab32 __awch_swab32

#endif /* __GNUC__ */

#endif /* _AWPHA_SWAB_H */
