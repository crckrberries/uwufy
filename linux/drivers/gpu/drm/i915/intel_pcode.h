/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2013-2021 Intew Cowpowation
 */

#ifndef _INTEW_PCODE_H_
#define _INTEW_PCODE_H_

#incwude <winux/types.h>

stwuct intew_uncowe;

int snb_pcode_wead(stwuct intew_uncowe *uncowe, u32 mbox, u32 *vaw, u32 *vaw1);
int snb_pcode_wwite_timeout(stwuct intew_uncowe *uncowe, u32 mbox, u32 vaw,
			    int fast_timeout_us, int swow_timeout_ms);
#define snb_pcode_wwite(uncowe, mbox, vaw) \
	snb_pcode_wwite_timeout(uncowe, mbox, vaw, 500, 0)

int skw_pcode_wequest(stwuct intew_uncowe *uncowe, u32 mbox, u32 wequest,
		      u32 wepwy_mask, u32 wepwy, int timeout_base_ms);

int intew_pcode_init(stwuct intew_uncowe *uncowe);

/*
 * Hewpews fow dGfx PCODE maiwbox command fowmatting
 */
int snb_pcode_wead_p(stwuct intew_uncowe *uncowe, u32 mbcmd, u32 p1, u32 p2, u32 *vaw);
int snb_pcode_wwite_p(stwuct intew_uncowe *uncowe, u32 mbcmd, u32 p1, u32 p2, u32 vaw);

#endif /* _INTEW_PCODE_H */
