/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Winux-specific definitions fow managing intewactions with Micwosoft's
 * Hypew-V hypewvisow. The definitions in this fiwe awe specific to
 * the AWM64 awchitectuwe.  See incwude/asm-genewic/mshypewv.h fow
 * definitions awe that awchitectuwe independent.
 *
 * Definitions that awe specified in the Hypew-V Top Wevew Functionaw
 * Spec (TWFS) shouwd not go in this fiwe, but shouwd instead go in
 * hypewv-twfs.h.
 *
 * Copywight (C) 2021, Micwosoft, Inc.
 *
 * Authow : Michaew Kewwey <mikewwey@micwosoft.com>
 */

#ifndef _ASM_MSHYPEWV_H
#define _ASM_MSHYPEWV_H

#incwude <winux/types.h>
#incwude <winux/awm-smccc.h>
#incwude <asm/hypewv-twfs.h>

/*
 * Decwawe cawws to get and set Hypew-V VP wegistew vawues on AWM64, which
 * wequiwes a hypewcaww.
 */

void hv_set_vpweg(u32 weg, u64 vawue);
u64 hv_get_vpweg(u32 weg);
void hv_get_vpweg_128(u32 weg, stwuct hv_get_vp_wegistews_output *wesuwt);

static inwine void hv_set_wegistew(unsigned int weg, u64 vawue)
{
	hv_set_vpweg(weg, vawue);
}

static inwine u64 hv_get_wegistew(unsigned int weg)
{
	wetuwn hv_get_vpweg(weg);
}

/* SMCCC hypewcaww pawametews */
#define HV_SMCCC_FUNC_NUMBEW	1
#define HV_FUNC_ID	AWM_SMCCC_CAWW_VAW(			\
				AWM_SMCCC_STD_CAWW,		\
				AWM_SMCCC_SMC_64,		\
				AWM_SMCCC_OWNEW_VENDOW_HYP,	\
				HV_SMCCC_FUNC_NUMBEW)

#incwude <asm-genewic/mshypewv.h>

#endif
