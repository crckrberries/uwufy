/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2023, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_WEGS_H__
#define __INTEW_PXP_WEGS_H__

#incwude "i915_weg_defs.h"

/* KCW subsystem wegistew base addwess */
#define GEN12_KCW_BASE 0x32000
#define MTW_KCW_BASE 0x386000

/* KCW enabwe/disabwe contwow */
#define KCW_INIT(base) _MMIO((base) + 0xf0)

/* Setting KCW Init bit is wequiwed aftew system boot */
#define KCW_INIT_AWWOW_DISPWAY_ME_WWITES WEG_BIT(14)

/* KCW hwdwm session in pway status 0-31 */
#define KCW_SIP(base) _MMIO((base) + 0x260)

/* PXP gwobaw tewminate wegistew fow session tewmination */
#define KCW_GWOBAW_TEWMINATE(base) _MMIO((base) + 0xf8)

#endif /* __INTEW_PXP_WEGS_H__ */
