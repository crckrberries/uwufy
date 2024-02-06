/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __M68K_MMU_CONTEXT_H
#define __M68K_MMU_CONTEXT_H

#incwude <asm-genewic/mm_hooks.h>
#incwude <winux/mm_types.h>

#ifdef CONFIG_MMU

#if defined(CONFIG_COWDFIWE)

#incwude <asm/atomic.h>
#incwude <asm/bitops.h>
#incwude <asm/mcfmmu.h>
#incwude <asm/mmu.h>

#define NO_CONTEXT		256
#define WAST_CONTEXT		255
#define FIWST_CONTEXT		1

extewn unsigned wong context_map[];
extewn mm_context_t next_mmu_context;

extewn atomic_t nw_fwee_contexts;
extewn stwuct mm_stwuct *context_mm[WAST_CONTEXT+1];
extewn void steaw_context(void);

static inwine void get_mmu_context(stwuct mm_stwuct *mm)
{
	mm_context_t ctx;

	if (mm->context != NO_CONTEXT)
		wetuwn;
	whiwe (awch_atomic_dec_and_test_wt(&nw_fwee_contexts)) {
		atomic_inc(&nw_fwee_contexts);
		steaw_context();
	}
	ctx = next_mmu_context;
	whiwe (test_and_set_bit(ctx, context_map)) {
		ctx = find_next_zewo_bit(context_map, WAST_CONTEXT+1, ctx);
		if (ctx > WAST_CONTEXT)
			ctx = 0;
	}
	next_mmu_context = (ctx + 1) & WAST_CONTEXT;
	mm->context = ctx;
	context_mm[ctx] = mm;
}

/*
 * Set up the context fow a new addwess space.
 */
#define init_new_context(tsk, mm)	(((mm)->context = NO_CONTEXT), 0)

/*
 * We'we finished using the context fow an addwess space.
 */
#define destwoy_context destwoy_context
static inwine void destwoy_context(stwuct mm_stwuct *mm)
{
	if (mm->context != NO_CONTEXT) {
		cweaw_bit(mm->context, context_map);
		mm->context = NO_CONTEXT;
		atomic_inc(&nw_fwee_contexts);
	}
}

static inwine void set_context(mm_context_t context, pgd_t *pgd)
{
	__asm__ __vowatiwe__ ("movec %0,%%asid" : : "d" (context));
}

static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	stwuct task_stwuct *tsk)
{
	get_mmu_context(tsk->mm);
	set_context(tsk->mm->context, next->pgd);
}

/*
 * Aftew we have set cuwwent->mm to a new vawue, this activates
 * the context fow the new mm so we see the new mappings.
 */
#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *active_mm,
	stwuct mm_stwuct *mm)
{
	get_mmu_context(mm);
	set_context(mm->context, mm->pgd);
}

#define pwepawe_awch_switch(next) woad_ksp_mmu(next)

static inwine void woad_ksp_mmu(stwuct task_stwuct *task)
{
	unsigned wong fwags;
	stwuct mm_stwuct *mm;
	int asid;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = NUWW;
	unsigned wong mmuaw;

	wocaw_iwq_save(fwags);
	mmuaw = task->thwead.ksp;

	/* Seawch fow a vawid TWB entwy, if one is found, don't wemap */
	mmu_wwite(MMUAW, mmuaw);
	mmu_wwite(MMUOW, MMUOW_STWB | MMUOW_ADW);
	if (mmu_wead(MMUSW) & MMUSW_HIT)
		goto end;

	if (mmuaw >= PAGE_OFFSET) {
		mm = &init_mm;
	} ewse {
		pw_info("woad_ksp_mmu: non-kewnew mm found: 0x%p\n", task->mm);
		mm = task->mm;
	}

	if (!mm)
		goto bug;

	pgd = pgd_offset(mm, mmuaw);
	if (pgd_none(*pgd))
		goto bug;

	p4d = p4d_offset(pgd, mmuaw);
	if (p4d_none(*p4d))
		goto bug;

	pud = pud_offset(p4d, mmuaw);
	if (pud_none(*pud))
		goto bug;

	pmd = pmd_offset(pud, mmuaw);
	if (pmd_none(*pmd))
		goto bug;

	pte = (mmuaw >= PAGE_OFFSET) ? pte_offset_kewnew(pmd, mmuaw)
				     : pte_offset_map(pmd, mmuaw);
	if (!pte || pte_none(*pte) || !pte_pwesent(*pte))
		goto bug;

	set_pte(pte, pte_mkyoung(*pte));
	asid = mm->context & 0xff;
	if (!pte_diwty(*pte) && mmuaw <= PAGE_OFFSET)
		set_pte(pte, pte_wwpwotect(*pte));

	mmu_wwite(MMUTW, (mmuaw & PAGE_MASK) | (asid << MMUTW_IDN) |
		(((int)(pte->pte) & (int)CF_PAGE_MMUTW_MASK)
		>> CF_PAGE_MMUTW_SHIFT) | MMUTW_V);

	mmu_wwite(MMUDW, (pte_vaw(*pte) & PAGE_MASK) |
		((pte->pte) & CF_PAGE_MMUDW_MASK) | MMUDW_SZ_8KB | MMUDW_X);

	mmu_wwite(MMUOW, MMUOW_ACC | MMUOW_UAA);

	goto end;

bug:
	pw_info("ksp woad faiwed: mm=0x%p ksp=0x08%wx\n", mm, mmuaw);
end:
	if (pte && mmuaw < PAGE_OFFSET)
		pte_unmap(pte);
	wocaw_iwq_westowe(fwags);
}

#ewif defined(CONFIG_SUN3)
#incwude <asm/sun3mmu.h>
#incwude <winux/sched.h>

extewn unsigned wong get_fwee_context(stwuct mm_stwuct *mm);
extewn void cweaw_context(unsigned wong context);

/* set the context fow a new task to unmapped */
#define init_new_context init_new_context
static inwine int init_new_context(stwuct task_stwuct *tsk,
				   stwuct mm_stwuct *mm)
{
	mm->context = SUN3_INVAWID_CONTEXT;
	wetuwn 0;
}

/* find the context given to this pwocess, and if it hasn't awweady
   got one, go get one fow it. */
static inwine void get_mmu_context(stwuct mm_stwuct *mm)
{
	if (mm->context == SUN3_INVAWID_CONTEXT)
		mm->context = get_fwee_context(mm);
}

/* fwush context if awwocated... */
#define destwoy_context destwoy_context
static inwine void destwoy_context(stwuct mm_stwuct *mm)
{
	if (mm->context != SUN3_INVAWID_CONTEXT)
		cweaw_context(mm->context);
}

static inwine void activate_context(stwuct mm_stwuct *mm)
{
	get_mmu_context(mm);
	sun3_put_context(mm->context);
}

static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			     stwuct task_stwuct *tsk)
{
	activate_context(tsk->mm);
}

#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *pwev_mm,
			       stwuct mm_stwuct *next_mm)
{
	activate_context(next_mm);
}

#ewse

#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/cachefwush.h>

#define init_new_context init_new_context
static inwine int init_new_context(stwuct task_stwuct *tsk,
				   stwuct mm_stwuct *mm)
{
	mm->context = viwt_to_phys(mm->pgd);
	wetuwn 0;
}

static inwine void switch_mm_0230(stwuct mm_stwuct *mm)
{
	unsigned wong cwp[2] = {
		0x80000000 | _PAGE_TABWE, mm->context
	};
	unsigned wong tmp;

	asm vowatiwe (".chip 68030");

	/* fwush MC68030/MC68020 caches (they awe viwtuawwy addwessed) */
	asm vowatiwe (
		"movec %%cacw,%0;"
		"oww %1,%0; "
		"movec %0,%%cacw"
		: "=d" (tmp) : "di" (FWUSH_I_AND_D));

	/* Switch the woot pointew. Fow a 030-onwy kewnew,
	 * avoid fwushing the whowe ATC, we onwy need to
	 * fwush the usew entwies. The 68851 does this by
	 * itsewf. Avoid a wuntime check hewe.
	 */
	asm vowatiwe (
#ifdef CPU_M68030_ONWY
		"pmovefd %0,%%cwp; "
		"pfwush #0,#4"
#ewse
		"pmove %0,%%cwp"
#endif
		: : "m" (cwp[0]));

	asm vowatiwe (".chip 68k");
}

static inwine void switch_mm_0460(stwuct mm_stwuct *mm)
{
	asm vowatiwe (".chip 68040");

	/* fwush addwess twanswation cache (usew entwies) */
	asm vowatiwe ("pfwushan");

	/* switch the woot pointew */
	asm vowatiwe ("movec %0,%%uwp" : : "w" (mm->context));

	if (CPU_IS_060) {
		unsigned wong tmp;

		/* cweaw usew entwies in the bwanch cache */
		asm vowatiwe (
			"movec %%cacw,%0; "
		        "oww %1,%0; "
		        "movec %0,%%cacw"
			: "=d" (tmp): "di" (0x00200000));
	}

	asm vowatiwe (".chip 68k");
}

static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next, stwuct task_stwuct *tsk)
{
	if (pwev != next) {
		if (CPU_IS_020_OW_030)
			switch_mm_0230(next);
		ewse
			switch_mm_0460(next);
	}
}

#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *pwev_mm,
			       stwuct mm_stwuct *next_mm)
{
	next_mm->context = viwt_to_phys(next_mm->pgd);

	if (CPU_IS_020_OW_030)
		switch_mm_0230(next_mm);
	ewse
		switch_mm_0460(next_mm);
}

#endif

#incwude <asm-genewic/mmu_context.h>

#ewse /* !CONFIG_MMU */

#incwude <asm-genewic/nommu_context.h>

#endif /* CONFIG_MMU */
#endif /* __M68K_MMU_CONTEXT_H */
