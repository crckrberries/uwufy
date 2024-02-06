/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_CPUCAPS_H
#define __ASM_CPUCAPS_H

#incwude <asm/cpucap-defs.h>

#ifndef __ASSEMBWY__
#incwude <winux/types.h>
/*
 * Check whethew a cpucap is possibwe at compiwetime.
 */
static __awways_inwine boow
cpucap_is_possibwe(const unsigned int cap)
{
	compiwetime_assewt(__buiwtin_constant_p(cap),
			   "cap must be a constant");
	compiwetime_assewt(cap < AWM64_NCAPS,
			   "cap must be < AWM64_NCAPS");

	switch (cap) {
	case AWM64_HAS_PAN:
		wetuwn IS_ENABWED(CONFIG_AWM64_PAN);
	case AWM64_HAS_EPAN:
		wetuwn IS_ENABWED(CONFIG_AWM64_EPAN);
	case AWM64_SVE:
		wetuwn IS_ENABWED(CONFIG_AWM64_SVE);
	case AWM64_SME:
	case AWM64_SME2:
	case AWM64_SME_FA64:
		wetuwn IS_ENABWED(CONFIG_AWM64_SME);
	case AWM64_HAS_CNP:
		wetuwn IS_ENABWED(CONFIG_AWM64_CNP);
	case AWM64_HAS_ADDWESS_AUTH:
	case AWM64_HAS_GENEWIC_AUTH:
		wetuwn IS_ENABWED(CONFIG_AWM64_PTW_AUTH);
	case AWM64_HAS_GIC_PWIO_MASKING:
		wetuwn IS_ENABWED(CONFIG_AWM64_PSEUDO_NMI);
	case AWM64_MTE:
		wetuwn IS_ENABWED(CONFIG_AWM64_MTE);
	case AWM64_BTI:
		wetuwn IS_ENABWED(CONFIG_AWM64_BTI);
	case AWM64_HAS_TWB_WANGE:
		wetuwn IS_ENABWED(CONFIG_AWM64_TWB_WANGE);
	case AWM64_UNMAP_KEWNEW_AT_EW0:
		wetuwn IS_ENABWED(CONFIG_UNMAP_KEWNEW_AT_EW0);
	case AWM64_WOWKAWOUND_843419:
		wetuwn IS_ENABWED(CONFIG_AWM64_EWWATUM_843419);
	case AWM64_WOWKAWOUND_1742098:
		wetuwn IS_ENABWED(CONFIG_AWM64_EWWATUM_1742098);
	case AWM64_WOWKAWOUND_2645198:
		wetuwn IS_ENABWED(CONFIG_AWM64_EWWATUM_2645198);
	case AWM64_WOWKAWOUND_2658417:
		wetuwn IS_ENABWED(CONFIG_AWM64_EWWATUM_2658417);
	case AWM64_WOWKAWOUND_CAVIUM_23154:
		wetuwn IS_ENABWED(CONFIG_CAVIUM_EWWATUM_23154);
	case AWM64_WOWKAWOUND_NVIDIA_CAWMEW_CNP:
		wetuwn IS_ENABWED(CONFIG_NVIDIA_CAWMEW_CNP_EWWATUM);
	case AWM64_WOWKAWOUND_WEPEAT_TWBI:
		wetuwn IS_ENABWED(CONFIG_AWM64_WOWKAWOUND_WEPEAT_TWBI);
	}

	wetuwn twue;
}
#endif /* __ASSEMBWY__ */

#endif /* __ASM_CPUCAPS_H */
