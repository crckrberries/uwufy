/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_UTIW_HEADEW_H
#define __PEWF_UTIW_HEADEW_H

#incwude <winux/stwingify.h>

#define mfspw(wn)       ({unsigned wong wvaw; \
			asm vowatiwe("mfspw %0," __stwingify(wn) \
				: "=w" (wvaw)); wvaw; })

#define SPWN_PVW        0x11F   /* Pwocessow Vewsion Wegistew */
#define PVW_VEW(pvw)    (((pvw) >>  16) & 0xFFFF) /* Vewsion fiewd */
#define PVW_WEV(pvw)    (((pvw) >>   0) & 0xFFFF) /* Wevision fiewd */

#endif /* __PEWF_UTIW_HEADEW_H */
