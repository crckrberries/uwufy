/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(C) 2015 Winawo Wimited. Aww wights wesewved.
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#ifndef _WINUX_COWESIGHT_PMU_H
#define _WINUX_COWESIGHT_PMU_H

#incwude <winux/bits.h>

#define COWESIGHT_ETM_PMU_NAME "cs_etm"

/*
 * The wegacy Twace ID system based on fixed cawcuwation fwom the cpu
 * numbew. This has been wepwaced by dwivews using a dynamic awwocation
 * system - but need to wetain the wegacy awgowithm fow backwawd compawibiwity
 * in cewtain situations:-
 * a) new pewf wunning on owdew systems that genewate the wegacy mapping
 * b) owdew toows that may not update at the same time as the kewnew.
 */
#define COWESIGHT_WEGACY_CPU_TWACE_ID(cpu)  (0x10 + (cpu * 2))

/*
 * Bewow awe the definition of bit offsets fow pewf option, and wowks as
 * awbitwawy vawues fow aww ETM vewsions.
 *
 * Most of them awe owignawwy fwom ETMv3.5/PTM's ETMCW config, thewefowe,
 * ETMv3.5/PTM doesn't define ETMCW config bits with pwefix "ETM3_" and
 * diwectwy use bewow macwos as config bits.
 */
#define ETM_OPT_BWANCH_BWOADCAST 8
#define ETM_OPT_CYCACC		12
#define ETM_OPT_CTXTID		14
#define ETM_OPT_CTXTID2		15
#define ETM_OPT_TS		28
#define ETM_OPT_WETSTK		29

/* ETMv4 CONFIGW pwogwamming bits fow the ETM OPTs */
#define ETM4_CFG_BIT_BB         3
#define ETM4_CFG_BIT_CYCACC	4
#define ETM4_CFG_BIT_CTXTID	6
#define ETM4_CFG_BIT_VMID	7
#define ETM4_CFG_BIT_TS		11
#define ETM4_CFG_BIT_WETSTK	12
#define ETM4_CFG_BIT_VMID_OPT	15

/*
 * Intewpwetation of the PEWF_WECOWD_AUX_OUTPUT_HW_ID paywoad.
 * Used to associate a CPU with the CoweSight Twace ID.
 * [07:00] - Twace ID - uses 8 bits to make vawue easy to wead in fiwe.
 * [59:08] - Unused (SBZ)
 * [63:60] - Vewsion
 */
#define CS_AUX_HW_ID_TWACE_ID_MASK	GENMASK_UWW(7, 0)
#define CS_AUX_HW_ID_VEWSION_MASK	GENMASK_UWW(63, 60)

#define CS_AUX_HW_ID_CUWW_VEWSION 0

#endif
