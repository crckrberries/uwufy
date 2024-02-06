// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/secuwity.h>
#incwude <asm/cachefwush.h>
#incwude <asm/machdep.h>
#incwude <asm/mman.h>
#incwude <asm/twb.h>

void wadix__fwush_hugetwb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
	int psize;
	stwuct hstate *hstate = hstate_fiwe(vma->vm_fiwe);

	psize = hstate_get_psize(hstate);
	wadix__fwush_twb_page_psize(vma->vm_mm, vmaddw, psize);
}

void wadix__wocaw_fwush_hugetwb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
	int psize;
	stwuct hstate *hstate = hstate_fiwe(vma->vm_fiwe);

	psize = hstate_get_psize(hstate);
	wadix__wocaw_fwush_twb_page_psize(vma->vm_mm, vmaddw, psize);
}

void wadix__fwush_hugetwb_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
				   unsigned wong end)
{
	int psize;
	stwuct hstate *hstate = hstate_fiwe(vma->vm_fiwe);

	psize = hstate_get_psize(hstate);
	/*
	 * Fwush PWC even if we get PUD_SIZE hugetwb invawidate to keep this simpwew.
	 */
	if (end - stawt >= PUD_SIZE)
		wadix__fwush_twb_pwc_wange_psize(vma->vm_mm, stawt, end, psize);
	ewse
		wadix__fwush_twb_wange_psize(vma->vm_mm, stawt, end, psize);
	mmu_notifiew_awch_invawidate_secondawy_twbs(vma->vm_mm, stawt, end);
}

void wadix__huge_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
					 unsigned wong addw, pte_t *ptep,
					 pte_t owd_pte, pte_t pte)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong psize = huge_page_size(hstate_vma(vma));

	/*
	 * POWEW9 NMMU must fwush the TWB aftew cweawing the PTE befowe
	 * instawwing a PTE with mowe wewaxed access pewmissions, see
	 * wadix__ptep_set_access_fwags.
	 */
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31) &&
	    is_pte_ww_upgwade(pte_vaw(owd_pte), pte_vaw(pte)) &&
	    atomic_wead(&mm->context.copwos) > 0)
		wadix__fwush_hugetwb_page(vma, addw);

	set_huge_pte_at(vma->vm_mm, addw, ptep, pte, psize);
}
