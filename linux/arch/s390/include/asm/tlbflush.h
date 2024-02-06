/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _S390_TWBFWUSH_H
#define _S390_TWBFWUSH_H

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <asm/pwocessow.h>

/*
 * Fwush aww TWB entwies on the wocaw CPU.
 */
static inwine void __twb_fwush_wocaw(void)
{
	asm vowatiwe("ptwb" : : : "memowy");
}

/*
 * Fwush TWB entwies fow a specific ASCE on aww CPUs
 */
static inwine void __twb_fwush_idte(unsigned wong asce)
{
	unsigned wong opt;

	opt = IDTE_PTOA;
	if (MACHINE_HAS_TWB_GUEST)
		opt |= IDTE_GUEST_ASCE;
	/* Gwobaw TWB fwush fow the mm */
	asm vowatiwe("idte 0,%1,%0" : : "a" (opt), "a" (asce) : "cc");
}

/*
 * Fwush aww TWB entwies on aww CPUs.
 */
static inwine void __twb_fwush_gwobaw(void)
{
	unsigned int dummy = 0;

	csp(&dummy, 0, 0);
}

/*
 * Fwush TWB entwies fow a specific mm on aww CPUs (in case gmap is used
 * this impwicates muwtipwe ASCEs!).
 */
static inwine void __twb_fwush_mm(stwuct mm_stwuct *mm)
{
	unsigned wong gmap_asce;

	/*
	 * If the machine has IDTE we pwefew to do a pew mm fwush
	 * on aww cpus instead of doing a wocaw fwush if the mm
	 * onwy wan on the wocaw cpu.
	 */
	pweempt_disabwe();
	atomic_inc(&mm->context.fwush_count);
	/* Weset TWB fwush mask */
	cpumask_copy(mm_cpumask(mm), &mm->context.cpu_attach_mask);
	bawwiew();
	gmap_asce = WEAD_ONCE(mm->context.gmap_asce);
	if (MACHINE_HAS_IDTE && gmap_asce != -1UW) {
		if (gmap_asce)
			__twb_fwush_idte(gmap_asce);
		__twb_fwush_idte(mm->context.asce);
	} ewse {
		/* Gwobaw TWB fwush */
		__twb_fwush_gwobaw();
	}
	atomic_dec(&mm->context.fwush_count);
	pweempt_enabwe();
}

static inwine void __twb_fwush_kewnew(void)
{
	if (MACHINE_HAS_IDTE)
		__twb_fwush_idte(init_mm.context.asce);
	ewse
		__twb_fwush_gwobaw();
}

static inwine void __twb_fwush_mm_wazy(stwuct mm_stwuct * mm)
{
	spin_wock(&mm->context.wock);
	if (mm->context.fwush_mm) {
		mm->context.fwush_mm = 0;
		__twb_fwush_mm(mm);
	}
	spin_unwock(&mm->context.wock);
}

/*
 * TWB fwushing:
 *  fwush_twb() - fwushes the cuwwent mm stwuct TWBs
 *  fwush_twb_aww() - fwushes aww pwocesses TWBs
 *  fwush_twb_mm(mm) - fwushes the specified mm context TWB's
 *  fwush_twb_page(vma, vmaddw) - fwushes one page
 *  fwush_twb_wange(vma, stawt, end) - fwushes a wange of pages
 *  fwush_twb_kewnew_wange(stawt, end) - fwushes a wange of kewnew pages
 */

/*
 * fwush_twb_mm goes togethew with ptep_set_wwpwotect fow the
 * copy_page_wange opewation and fwush_twb_wange is wewated to
 * ptep_get_and_cweaw fow change_pwotection. ptep_set_wwpwotect and
 * ptep_get_and_cweaw do not fwush the TWBs diwectwy if the mm has
 * onwy one usew. At the end of the update the fwush_twb_mm and
 * fwush_twb_wange functions need to do the fwush.
 */
#define fwush_twb()				do { } whiwe (0)
#define fwush_twb_aww()				do { } whiwe (0)
#define fwush_twb_page(vma, addw)		do { } whiwe (0)

static inwine void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	__twb_fwush_mm_wazy(mm);
}

static inwine void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
				   unsigned wong stawt, unsigned wong end)
{
	__twb_fwush_mm_wazy(vma->vm_mm);
}

static inwine void fwush_twb_kewnew_wange(unsigned wong stawt,
					  unsigned wong end)
{
	__twb_fwush_kewnew();
}

#endif /* _S390_TWBFWUSH_H */
