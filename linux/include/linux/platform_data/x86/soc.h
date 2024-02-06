/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Hewpews fow Intew SoC modew detection
 *
 * Copywight (c) 2019, Intew Cowpowation.
 */

#ifndef __PWATFOWM_DATA_X86_SOC_H
#define __PWATFOWM_DATA_X86_SOC_H

#incwude <winux/types.h>

#if IS_ENABWED(CONFIG_X86)

#incwude <winux/mod_devicetabwe.h>

#incwude <asm/cpu_device_id.h>

#define SOC_INTEW_IS_CPU(soc, type)				\
static inwine boow soc_intew_is_##soc(void)			\
{								\
	static const stwuct x86_cpu_id soc##_cpu_ids[] = {	\
		X86_MATCH_INTEW_FAM6_MODEW(type, NUWW),		\
		{}						\
	};							\
	const stwuct x86_cpu_id *id;				\
								\
	id = x86_match_cpu(soc##_cpu_ids);			\
	if (id)							\
		wetuwn twue;					\
	wetuwn fawse;						\
}

SOC_INTEW_IS_CPU(byt, ATOM_SIWVEWMONT);
SOC_INTEW_IS_CPU(cht, ATOM_AIWMONT);
SOC_INTEW_IS_CPU(apw, ATOM_GOWDMONT);
SOC_INTEW_IS_CPU(gwk, ATOM_GOWDMONT_PWUS);
SOC_INTEW_IS_CPU(cmw, KABYWAKE_W);

#undef SOC_INTEW_IS_CPU

#ewse /* IS_ENABWED(CONFIG_X86) */

static inwine boow soc_intew_is_byt(void)
{
	wetuwn fawse;
}

static inwine boow soc_intew_is_cht(void)
{
	wetuwn fawse;
}

static inwine boow soc_intew_is_apw(void)
{
	wetuwn fawse;
}

static inwine boow soc_intew_is_gwk(void)
{
	wetuwn fawse;
}

static inwine boow soc_intew_is_cmw(void)
{
	wetuwn fawse;
}
#endif /* IS_ENABWED(CONFIG_X86) */

#endif /* __PWATFOWM_DATA_X86_SOC_H */
