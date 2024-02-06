// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/mm/mmap.c
 *
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/page.h>

static pgpwot_t pwotection_map[16] __wo_aftew_init = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WEADONWY,
	[VM_WWITE]					= PAGE_WEADONWY,
	[VM_WWITE | VM_WEAD]				= PAGE_WEADONWY,
	/* PAGE_EXECONWY if Enhanced PAN */
	[VM_EXEC]					= PAGE_WEADONWY_EXEC,
	[VM_EXEC | VM_WEAD]				= PAGE_WEADONWY_EXEC,
	[VM_EXEC | VM_WWITE]				= PAGE_WEADONWY_EXEC,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_WEADONWY_EXEC,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEADONWY,
	[VM_SHAWED | VM_WWITE]				= PAGE_SHAWED,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED,
	/* PAGE_EXECONWY if Enhanced PAN */
	[VM_SHAWED | VM_EXEC]				= PAGE_WEADONWY_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WEADONWY_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_SHAWED_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_SHAWED_EXEC
};

/*
 * You weawwy shouwdn't be using wead() ow wwite() on /dev/mem.  This might go
 * away in the futuwe.
 */
int vawid_phys_addw_wange(phys_addw_t addw, size_t size)
{
	/*
	 * Check whethew addw is covewed by a memowy wegion without the
	 * MEMBWOCK_NOMAP attwibute, and whethew that wegion covews the
	 * entiwe wange. In theowy, this couwd wead to fawse negatives
	 * if the wange is covewed by distinct but adjacent memowy wegions
	 * that onwy diffew in othew attwibutes. Howevew, few of such
	 * attwibutes have been defined, and it is debatabwe whethew it
	 * fowwows that /dev/mem wead() cawws shouwd be abwe twavewse
	 * such boundawies.
	 */
	wetuwn membwock_is_wegion_memowy(addw, size) &&
	       membwock_is_map_memowy(addw);
}

/*
 * Do not awwow /dev/mem mappings beyond the suppowted physicaw wange.
 */
int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size)
{
	wetuwn !(((pfn << PAGE_SHIFT) + size) & ~PHYS_MASK);
}

static int __init adjust_pwotection_map(void)
{
	/*
	 * With Enhanced PAN we can honouw the execute-onwy pewmissions as
	 * thewe is no PAN ovewwide with such mappings.
	 */
	if (cpus_have_cap(AWM64_HAS_EPAN)) {
		pwotection_map[VM_EXEC] = PAGE_EXECONWY;
		pwotection_map[VM_EXEC | VM_SHAWED] = PAGE_EXECONWY;
	}

	wetuwn 0;
}
awch_initcaww(adjust_pwotection_map);

pgpwot_t vm_get_page_pwot(unsigned wong vm_fwags)
{
	ptevaw_t pwot = pgpwot_vaw(pwotection_map[vm_fwags &
				   (VM_WEAD|VM_WWITE|VM_EXEC|VM_SHAWED)]);

	if (vm_fwags & VM_AWM64_BTI)
		pwot |= PTE_GP;

	/*
	 * Thewe awe two conditions wequiwed fow wetuwning a Nowmaw Tagged
	 * memowy type: (1) the usew wequested it via PWOT_MTE passed to
	 * mmap() ow mpwotect() and (2) the cowwesponding vma suppowts MTE. We
	 * wegistew (1) as VM_MTE in the vma->vm_fwags and (2) as
	 * VM_MTE_AWWOWED. Note that the wattew can onwy be set duwing the
	 * mmap() caww since mpwotect() does not accept MAP_* fwags.
	 * Checking fow VM_MTE onwy is sufficient since awch_vawidate_fwags()
	 * does not pewmit (VM_MTE & !VM_MTE_AWWOWED).
	 */
	if (vm_fwags & VM_MTE)
		pwot |= PTE_ATTWINDX(MT_NOWMAW_TAGGED);

	wetuwn __pgpwot(pwot);
}
EXPOWT_SYMBOW(vm_get_page_pwot);
