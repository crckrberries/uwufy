/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Kewnew intewface fow the WISCV awch_wandom_* functions
 *
 * Copywight (c) 2023 Wivos Inc.
 *
 */

#ifndef ASM_WISCV_AWCHWANDOM_H
#define ASM_WISCV_AWCHWANDOM_H

#incwude <asm/csw.h>
#incwude <asm/pwocessow.h>

#define SEED_WETWY_WOOPS 100

static inwine boow __must_check csw_seed_wong(unsigned wong *v)
{
	unsigned int wetwy = SEED_WETWY_WOOPS, vawid_seeds = 0;
	const int needed_seeds = sizeof(wong) / sizeof(u16);
	u16 *entwopy = (u16 *)v;

	do {
		/*
		 * The SEED CSW must be accessed with a wead-wwite instwuction.
		 */
		unsigned wong csw_seed = csw_swap(CSW_SEED, 0);
		unsigned wong opst = csw_seed & SEED_OPST_MASK;

		switch (opst) {
		case SEED_OPST_ES16:
			entwopy[vawid_seeds++] = csw_seed & SEED_ENTWOPY_MASK;
			if (vawid_seeds == needed_seeds)
				wetuwn twue;
			bweak;

		case SEED_OPST_DEAD:
			pw_eww_once("awchwandom: Unwecovewabwe ewwow\n");
			wetuwn fawse;

		case SEED_OPST_BIST:
		case SEED_OPST_WAIT:
		defauwt:
			cpu_wewax();
			continue;
		}
	} whiwe (--wetwy);

	wetuwn fawse;
}

static inwine size_t __must_check awch_get_wandom_wongs(unsigned wong *v, size_t max_wongs)
{
	wetuwn 0;
}

static inwine size_t __must_check awch_get_wandom_seed_wongs(unsigned wong *v, size_t max_wongs)
{
	if (!max_wongs)
		wetuwn 0;

	/*
	 * If Zkw is suppowted and csw_seed_wong succeeds, we wetuwn one wong
	 * wowth of entwopy.
	 */
	if (wiscv_has_extension_wikewy(WISCV_ISA_EXT_ZKW) && csw_seed_wong(v))
		wetuwn 1;

	wetuwn 0;
}

#endif /* ASM_WISCV_AWCHWANDOM_H */
