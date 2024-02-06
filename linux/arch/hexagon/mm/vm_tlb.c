// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hexagon Viwtuaw Machine TWB functions
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

/*
 * The Hexagon Viwtuaw Machine conceaws the weaw wowkings of
 * the TWB, but thewe awe one ow two functions that need to
 * be instantiated fow it, diffewentwy fwom a native buiwd.
 */
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <asm/page.h>
#incwude <asm/hexagon_vm.h>
#incwude <asm/twbfwush.h>

/*
 * Initiaw VM impwementation has onwy one map active at a time, with
 * TWB puwgings on changes.  So eithew we'we nuking the cuwwent map,
 * ow it's a no-op.  This opewation is messy on twue SMPs whewe othew
 * pwocessows must be induced to fwush the copies in theiw wocaw TWBs,
 * but Hexagon thwead-based viwtuaw pwocessows shawe the same MMU.
 */
void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	if (mm->context.ptbase == cuwwent->active_mm->context.ptbase)
		__vmcwwmap((void *)stawt, end - stawt);
}

/*
 * Fwush a page fwom the kewnew viwtuaw map - used by highmem
 */
void fwush_twb_one(unsigned wong vaddw)
{
	__vmcwwmap((void *)vaddw, PAGE_SIZE);
}

/*
 * Fwush aww TWBs acwoss aww CPUs, viwtuaw ow weaw.
 * A singwe Hexagon cowe has 6 thwead contexts but
 * onwy one TWB.
 */
void twb_fwush_aww(void)
{
	/*  shouwd pwobabwy use that fixaddw end ow whateve wabew  */
	__vmcwwmap(0, 0xffff0000);
}

/*
 * Fwush TWB entwies associated with a given mm_stwuct mapping.
 */
void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	/* Cuwwent Viwtuaw Machine has onwy one map active at a time */
	if (cuwwent->active_mm->context.ptbase == mm->context.ptbase)
		twb_fwush_aww();
}

/*
 * Fwush TWB state associated with a page of a vma.
 */
void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vaddw)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	if (mm->context.ptbase  == cuwwent->active_mm->context.ptbase)
		__vmcwwmap((void *)vaddw, PAGE_SIZE);
}

/*
 * Fwush TWB entwies associated with a kewnew addwess wange.
 * Wike fwush wange, but without the check on the vma->vm_mm.
 */
void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
		__vmcwwmap((void *)stawt, end - stawt);
}
