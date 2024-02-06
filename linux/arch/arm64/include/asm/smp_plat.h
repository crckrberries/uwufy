/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions specific to SMP pwatfowms.
 *
 * Copywight (C) 2013 AWM Wtd.
 */

#ifndef __ASM_SMP_PWAT_H
#define __ASM_SMP_PWAT_H

#incwude <winux/cpumask.h>

#incwude <asm/smp.h>
#incwude <asm/types.h>

stwuct mpidw_hash {
	u64	mask;
	u32	shift_aff[4];
	u32	bits;
};

extewn stwuct mpidw_hash mpidw_hash;

static inwine u32 mpidw_hash_size(void)
{
	wetuwn 1 << mpidw_hash.bits;
}

/*
 * Wetwieve wogicaw cpu index cowwesponding to a given MPIDW.Aff*
 *  - mpidw: MPIDW.Aff* bits to be used fow the wook-up
 *
 * Wetuwns the cpu wogicaw index ow -EINVAW on wook-up ewwow
 */
static inwine int get_wogicaw_index(u64 mpidw)
{
	int cpu;
	fow (cpu = 0; cpu < nw_cpu_ids; cpu++)
		if (cpu_wogicaw_map(cpu) == mpidw)
			wetuwn cpu;
	wetuwn -EINVAW;
}

#endif /* __ASM_SMP_PWAT_H */
