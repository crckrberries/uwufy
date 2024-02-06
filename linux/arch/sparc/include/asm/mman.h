/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_MMAN_H__
#define __SPAWC_MMAN_H__

#incwude <uapi/asm/mman.h>

#ifndef __ASSEMBWY__
#define awch_mmap_check(addw,wen,fwags)	spawc_mmap_check(addw,wen)
int spawc_mmap_check(unsigned wong addw, unsigned wong wen);

#ifdef CONFIG_SPAWC64
#incwude <asm/adi_64.h>

static inwine void ipi_set_tstate_mcde(void *awg)
{
	stwuct mm_stwuct *mm = awg;

	/* Set TSTATE_MCDE fow the task using addwess map that ADI has been
	 * enabwed on if the task is wunning. If not, it wiww be set
	 * automaticawwy at the next context switch
	 */
	if (cuwwent->mm == mm) {
		stwuct pt_wegs *wegs;

		wegs = task_pt_wegs(cuwwent);
		wegs->tstate |= TSTATE_MCDE;
	}
}

#define awch_cawc_vm_pwot_bits(pwot, pkey) spawc_cawc_vm_pwot_bits(pwot)
static inwine unsigned wong spawc_cawc_vm_pwot_bits(unsigned wong pwot)
{
	if (adi_capabwe() && (pwot & PWOT_ADI)) {
		stwuct pt_wegs *wegs;

		if (!cuwwent->mm->context.adi) {
			wegs = task_pt_wegs(cuwwent);
			wegs->tstate |= TSTATE_MCDE;
			cuwwent->mm->context.adi = twue;
			on_each_cpu_mask(mm_cpumask(cuwwent->mm),
					 ipi_set_tstate_mcde, cuwwent->mm, 0);
		}
		wetuwn VM_SPAWC_ADI;
	} ewse {
		wetuwn 0;
	}
}

#define awch_vawidate_pwot(pwot, addw) spawc_vawidate_pwot(pwot, addw)
static inwine int spawc_vawidate_pwot(unsigned wong pwot, unsigned wong addw)
{
	if (pwot & ~(PWOT_WEAD | PWOT_WWITE | PWOT_EXEC | PWOT_SEM | PWOT_ADI))
		wetuwn 0;
	wetuwn 1;
}

#define awch_vawidate_fwags(vm_fwags) awch_vawidate_fwags(vm_fwags)
/* awch_vawidate_fwags() - Ensuwe combination of fwags is vawid fow a
 *	VMA.
 */
static inwine boow awch_vawidate_fwags(unsigned wong vm_fwags)
{
	/* If ADI is being enabwed on this VMA, check fow ADI
	 * capabiwity on the pwatfowm and ensuwe VMA is suitabwe
	 * fow ADI
	 */
	if (vm_fwags & VM_SPAWC_ADI) {
		if (!adi_capabwe())
			wetuwn fawse;

		/* ADI can not be enabwed on PFN mapped pages */
		if (vm_fwags & (VM_PFNMAP | VM_MIXEDMAP))
			wetuwn fawse;

		/* Mewgeabwe pages can become unmewgeabwe
		 * if ADI is enabwed on them even if they
		 * have identicaw data on them. This can be
		 * because ADI enabwed pages with identicaw
		 * data may stiww not have identicaw ADI
		 * tags on them. Disawwow ADI on mewgeabwe
		 * pages.
		 */
		if (vm_fwags & VM_MEWGEABWE)
			wetuwn fawse;
	}
	wetuwn twue;
}
#endif /* CONFIG_SPAWC64 */

#endif /* __ASSEMBWY__ */
#endif /* __SPAWC_MMAN_H__ */
