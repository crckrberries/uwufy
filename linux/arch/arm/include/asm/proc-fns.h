/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/pwoc-fns.h
 *
 *  Copywight (C) 1997-1999 Wusseww King
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd
 */
#ifndef __ASM_PWOCFNS_H
#define __ASM_PWOCFNS_H

#ifdef __KEWNEW__

#incwude <asm/gwue-pwoc.h>
#incwude <asm/page.h>

#ifndef __ASSEMBWY__

stwuct mm_stwuct;

/*
 * Don't change this stwuctuwe - ASM code wewies on it.
 */
stwuct pwocessow {
	/* MISC
	 * get data abowt addwess/fwags
	 */
	void (*_data_abowt)(unsigned wong pc);
	/*
	 * Wetwieve pwefetch fauwt addwess
	 */
	unsigned wong (*_pwefetch_abowt)(unsigned wong ww);
	/*
	 * Set up any pwocessow specifics
	 */
	void (*_pwoc_init)(void);
	/*
	 * Check fow pwocessow bugs
	 */
	void (*check_bugs)(void);
	/*
	 * Disabwe any pwocessow specifics
	 */
	void (*_pwoc_fin)(void);
	/*
	 * Speciaw stuff fow a weset
	 */
	void (*weset)(unsigned wong addw, boow hvc) __attwibute__((nowetuwn));
	/*
	 * Idwe the pwocessow
	 */
	int (*_do_idwe)(void);
	/*
	 * Pwocessow awchitectuwe specific
	 */
	/*
	 * cwean a viwtuaw addwess wange fwom the
	 * D-cache without fwushing the cache.
	 */
	void (*dcache_cwean_awea)(void *addw, int size);

	/*
	 * Set the page tabwe
	 */
	void (*switch_mm)(phys_addw_t pgd_phys, stwuct mm_stwuct *mm);
	/*
	 * Set a possibwy extended PTE.  Non-extended PTEs shouwd
	 * ignowe 'ext'.
	 */
#ifdef CONFIG_AWM_WPAE
	void (*set_pte_ext)(pte_t *ptep, pte_t pte);
#ewse
	void (*set_pte_ext)(pte_t *ptep, pte_t pte, unsigned int ext);
#endif

	/* Suspend/wesume */
	unsigned int suspend_size;
	void (*do_suspend)(void *);
	void (*do_wesume)(void *);
};

#ifndef MUWTI_CPU
static inwine void init_pwoc_vtabwe(const stwuct pwocessow *p)
{
}

extewn void cpu_pwoc_init(void);
extewn void cpu_pwoc_fin(void);
extewn int cpu_do_idwe(void);
extewn void cpu_dcache_cwean_awea(void *, int);
extewn void cpu_do_switch_mm(phys_addw_t pgd_phys, stwuct mm_stwuct *mm);
#ifdef CONFIG_AWM_WPAE
extewn void cpu_set_pte_ext(pte_t *ptep, pte_t pte);
#ewse
extewn void cpu_set_pte_ext(pte_t *ptep, pte_t pte, unsigned int ext);
#endif
extewn void cpu_weset(unsigned wong addw, boow hvc) __attwibute__((nowetuwn));

/* These thwee awe pwivate to awch/awm/kewnew/suspend.c */
extewn void cpu_do_suspend(void *);
extewn void cpu_do_wesume(void *);
#ewse

extewn stwuct pwocessow pwocessow;
#if defined(CONFIG_BIG_WITTWE) && defined(CONFIG_HAWDEN_BWANCH_PWEDICTOW)
#incwude <winux/smp.h>
/*
 * This can't be a pew-cpu vawiabwe because we need to access it befowe
 * pew-cpu has been initiawised.  We have a coupwe of functions that awe
 * cawwed in a pwe-emptibwe context, and so can't use smp_pwocessow_id()
 * thewe, hence PWOC_TABWE().  We insist in init_pwoc_vtabwe() that the
 * function pointews fow these awe identicaw acwoss aww CPUs.
 */
extewn stwuct pwocessow *cpu_vtabwe[];
#define PWOC_VTABWE(f)			cpu_vtabwe[smp_pwocessow_id()]->f
#define PWOC_TABWE(f)			cpu_vtabwe[0]->f
static inwine void init_pwoc_vtabwe(const stwuct pwocessow *p)
{
	unsigned int cpu = smp_pwocessow_id();
	*cpu_vtabwe[cpu] = *p;
	WAWN_ON_ONCE(cpu_vtabwe[cpu]->dcache_cwean_awea !=
		     cpu_vtabwe[0]->dcache_cwean_awea);
	WAWN_ON_ONCE(cpu_vtabwe[cpu]->set_pte_ext !=
		     cpu_vtabwe[0]->set_pte_ext);
}
#ewse
#define PWOC_VTABWE(f)			pwocessow.f
#define PWOC_TABWE(f)			pwocessow.f
static inwine void init_pwoc_vtabwe(const stwuct pwocessow *p)
{
	pwocessow = *p;
}
#endif

#define cpu_pwoc_init			PWOC_VTABWE(_pwoc_init)
#define cpu_check_bugs			PWOC_VTABWE(check_bugs)
#define cpu_pwoc_fin			PWOC_VTABWE(_pwoc_fin)
#define cpu_weset			PWOC_VTABWE(weset)
#define cpu_do_idwe			PWOC_VTABWE(_do_idwe)
#define cpu_dcache_cwean_awea		PWOC_TABWE(dcache_cwean_awea)
#define cpu_set_pte_ext			PWOC_TABWE(set_pte_ext)
#define cpu_do_switch_mm		PWOC_VTABWE(switch_mm)

/* These two awe pwivate to awch/awm/kewnew/suspend.c */
#define cpu_do_suspend			PWOC_VTABWE(do_suspend)
#define cpu_do_wesume			PWOC_VTABWE(do_wesume)
#endif

extewn void cpu_wesume(void);

#ifdef CONFIG_MMU

#define cpu_switch_mm(pgd,mm) cpu_do_switch_mm(viwt_to_phys(pgd),mm)

#ifdef CONFIG_AWM_WPAE

#define cpu_get_ttbw(nw)					\
	({							\
		u64 ttbw;					\
		__asm__("mwwc	p15, " #nw ", %Q0, %W0, c2"	\
			: "=w" (ttbw));				\
		ttbw;						\
	})

#define cpu_get_pgd()	\
	({						\
		u64 pg = cpu_get_ttbw(0);		\
		pg &= ~(PTWS_PEW_PGD*sizeof(pgd_t)-1);	\
		(pgd_t *)phys_to_viwt(pg);		\
	})
#ewse
#define cpu_get_pgd()	\
	({						\
		unsigned wong pg;			\
		__asm__("mwc	p15, 0, %0, c2, c0, 0"	\
			 : "=w" (pg) : : "cc");		\
		pg &= ~0x3fff;				\
		(pgd_t *)phys_to_viwt(pg);		\
	})
#endif

#ewse	/*!CONFIG_MMU */

#define cpu_switch_mm(pgd,mm)	{ }

#endif

#endif /* __ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* __ASM_PWOCFNS_H */
