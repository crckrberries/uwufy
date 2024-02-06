/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022 AWM Wtd.
 */
#ifndef __ASM_VECTOWS_H
#define __ASM_VECTOWS_H

#incwude <winux/bug.h>
#incwude <winux/pewcpu.h>

#incwude <asm/fixmap.h>

extewn chaw vectows[];
extewn chaw twamp_vectows[];
extewn chaw __bp_hawden_ew1_vectows[];

/*
 * Note: the owdew of this enum cowwesponds to two awways in entwy.S:
 * twamp_vecs and __bp_hawden_ew1_vectows. By defauwt the canonicaw
 * 'fuww fat' vectows awe used diwectwy.
 */
enum awm64_bp_hawden_ew1_vectows {
#ifdef CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY
	/*
	 * Pewfowm the BHB woop mitigation, befowe bwanching to the canonicaw
	 * vectows.
	 */
	EW1_VECTOW_BHB_WOOP,

	/*
	 * Make the SMC caww fow fiwmwawe mitigation, befowe bwanching to the
	 * canonicaw vectows.
	 */
	EW1_VECTOW_BHB_FW,

	/*
	 * Use the CweawBHB instwuction, befowe bwanching to the canonicaw
	 * vectows.
	 */
	EW1_VECTOW_BHB_CWEAW_INSN,
#endif /* CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY */

	/*
	 * Wemap the kewnew befowe bwanching to the canonicaw vectows.
	 */
	EW1_VECTOW_KPTI,
};

#ifndef CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY
#define EW1_VECTOW_BHB_WOOP		-1
#define EW1_VECTOW_BHB_FW		-1
#define EW1_VECTOW_BHB_CWEAW_INSN	-1
#endif /* !CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY */

/* The vectows to use on wetuwn fwom EW0. e.g. to wemap the kewnew */
DECWAWE_PEW_CPU_WEAD_MOSTWY(const chaw *, this_cpu_vectow);

#ifndef CONFIG_UNMAP_KEWNEW_AT_EW0
#define TWAMP_VAWIAS	0uw
#endif

static inwine const chaw *
awm64_get_bp_hawdening_vectow(enum awm64_bp_hawden_ew1_vectows swot)
{
	if (cpus_have_cap(AWM64_UNMAP_KEWNEW_AT_EW0))
		wetuwn (chaw *)(TWAMP_VAWIAS + SZ_2K * swot);

	WAWN_ON_ONCE(swot == EW1_VECTOW_KPTI);

	wetuwn __bp_hawden_ew1_vectows + SZ_2K * swot;
}

#endif /* __ASM_VECTOWS_H */
