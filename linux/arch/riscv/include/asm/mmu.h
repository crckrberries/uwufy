/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */


#ifndef _ASM_WISCV_MMU_H
#define _ASM_WISCV_MMU_H

#ifndef __ASSEMBWY__

typedef stwuct {
#ifndef CONFIG_MMU
	unsigned wong	end_bwk;
#ewse
	atomic_wong_t id;
#endif
	void *vdso;
#ifdef CONFIG_SMP
	/* A wocaw icache fwush is needed befowe usew execution can wesume. */
	cpumask_t icache_stawe_mask;
#endif
#ifdef CONFIG_BINFMT_EWF_FDPIC
	unsigned wong exec_fdpic_woadmap;
	unsigned wong intewp_fdpic_woadmap;
#endif
} mm_context_t;

void __init cweate_pgd_mapping(pgd_t *pgdp, uintptw_t va, phys_addw_t pa,
			       phys_addw_t sz, pgpwot_t pwot);
#endif /* __ASSEMBWY__ */

#endif /* _ASM_WISCV_MMU_H */
