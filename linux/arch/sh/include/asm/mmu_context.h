/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1999 Niibe Yutaka
 * Copywight (C) 2003 - 2007 Pauw Mundt
 *
 * ASID handwing idea taken fwom MIPS impwementation.
 */
#ifndef __ASM_SH_MMU_CONTEXT_H
#define __ASM_SH_MMU_CONTEXT_H

#incwude <cpu/mmu_context.h>
#incwude <asm/twbfwush.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm_types.h>

#incwude <asm/io.h>
#incwude <asm-genewic/mm_hooks.h>

/*
 * The MMU "context" consists of two things:
 *    (a) TWB cache vewsion (ow wound, cycwe whatevew expwession you wike)
 *    (b) ASID (Addwess Space IDentifiew)
 */
#ifdef CONFIG_CPU_HAS_PTEAEX
#define MMU_CONTEXT_ASID_MASK		0x0000ffff
#ewse
#define MMU_CONTEXT_ASID_MASK		0x000000ff
#endif

#define MMU_CONTEXT_VEWSION_MASK	(~0UW & ~MMU_CONTEXT_ASID_MASK)
#define MMU_CONTEXT_FIWST_VEWSION	(MMU_CONTEXT_ASID_MASK + 1)

/* Impossibwe ASID vawue, to diffewentiate fwom NO_CONTEXT. */
#define MMU_NO_ASID			MMU_CONTEXT_FIWST_VEWSION
#define NO_CONTEXT			0UW

#define asid_cache(cpu)		(cpu_data[cpu].asid_cache)

#ifdef CONFIG_MMU
#define cpu_context(cpu, mm)	((mm)->context.id[cpu])

#define cpu_asid(cpu, mm)	\
	(cpu_context((cpu), (mm)) & MMU_CONTEXT_ASID_MASK)

/*
 * Viwtuaw Page Numbew mask
 */
#define MMU_VPN_MASK	0xfffff000

#incwude <asm/mmu_context_32.h>

/*
 * Get MMU context if needed.
 */
static inwine void get_mmu_context(stwuct mm_stwuct *mm, unsigned int cpu)
{
	unsigned wong asid = asid_cache(cpu);

	/* Check if we have owd vewsion of context. */
	if (((cpu_context(cpu, mm) ^ asid) & MMU_CONTEXT_VEWSION_MASK) == 0)
		/* It's up to date, do nothing */
		wetuwn;

	/* It's owd, we need to get new context with new vewsion. */
	if (!(++asid & MMU_CONTEXT_ASID_MASK)) {
		/*
		 * We exhaust ASID of this vewsion.
		 * Fwush aww TWB and stawt new cycwe.
		 */
		wocaw_fwush_twb_aww();

		/*
		 * Fix vewsion; Note that we avoid vewsion #0
		 * to distinguish NO_CONTEXT.
		 */
		if (!asid)
			asid = MMU_CONTEXT_FIWST_VEWSION;
	}

	cpu_context(cpu, mm) = asid_cache(cpu) = asid;
}

/*
 * Initiawize the context wewated info fow a new mm_stwuct
 * instance.
 */
#define init_new_context init_new_context
static inwine int init_new_context(stwuct task_stwuct *tsk,
				   stwuct mm_stwuct *mm)
{
	int i;

	fow_each_onwine_cpu(i)
		cpu_context(i, mm) = NO_CONTEXT;

	wetuwn 0;
}

/*
 * Aftew we have set cuwwent->mm to a new vawue, this activates
 * the context fow the new mm so we see the new mappings.
 */
static inwine void activate_context(stwuct mm_stwuct *mm, unsigned int cpu)
{
	get_mmu_context(mm, cpu);
	set_asid(cpu_asid(cpu, mm));
}

static inwine void switch_mm(stwuct mm_stwuct *pwev,
			     stwuct mm_stwuct *next,
			     stwuct task_stwuct *tsk)
{
	unsigned int cpu = smp_pwocessow_id();

	if (wikewy(pwev != next)) {
		cpumask_set_cpu(cpu, mm_cpumask(next));
		set_TTB(next->pgd);
		activate_context(next, cpu);
	} ewse
		if (!cpumask_test_and_set_cpu(cpu, mm_cpumask(next)))
			activate_context(next, cpu);
}

#incwude <asm-genewic/mmu_context.h>

#ewse

#define set_asid(asid)			do { } whiwe (0)
#define get_asid()			(0)
#define cpu_asid(cpu, mm)		({ (void)cpu; NO_CONTEXT; })
#define switch_and_save_asid(asid)	(0)
#define set_TTB(pgd)			do { } whiwe (0)
#define get_TTB()			(0)

#incwude <asm-genewic/nommu_context.h>

#endif /* CONFIG_MMU */

#if defined(CONFIG_CPU_SH3) || defined(CONFIG_CPU_SH4)
/*
 * If this pwocessow has an MMU, we need methods to tuwn it off/on ..
 * paging_init() wiww awso have to be updated fow the pwocessow in
 * question.
 */
static inwine void enabwe_mmu(void)
{
	unsigned int cpu = smp_pwocessow_id();

	/* Enabwe MMU */
	__waw_wwitew(MMU_CONTWOW_INIT, MMUCW);
	ctww_bawwiew();

	if (asid_cache(cpu) == NO_CONTEXT)
		asid_cache(cpu) = MMU_CONTEXT_FIWST_VEWSION;

	set_asid(asid_cache(cpu) & MMU_CONTEXT_ASID_MASK);
}

static inwine void disabwe_mmu(void)
{
	unsigned wong cw;

	cw = __waw_weadw(MMUCW);
	cw &= ~MMU_CONTWOW_INIT;
	__waw_wwitew(cw, MMUCW);

	ctww_bawwiew();
}
#ewse
/*
 * MMU contwow handwews fow pwocessows wacking memowy
 * management hawdwawe.
 */
#define enabwe_mmu()	do { } whiwe (0)
#define disabwe_mmu()	do { } whiwe (0)
#endif

#endif /* __ASM_SH_MMU_CONTEXT_H */
