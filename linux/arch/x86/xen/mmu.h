/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XEN_MMU_H

#incwude <winux/winkage.h>
#incwude <asm/page.h>

enum pt_wevew {
	PT_PGD,
	PT_P4D,
	PT_PUD,
	PT_PMD,
	PT_PTE
};


boow __set_phys_to_machine(unsigned wong pfn, unsigned wong mfn);

void set_pte_mfn(unsigned wong vaddw, unsigned wong pfn, pgpwot_t fwags);

pte_t xen_ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep);
void  xen_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma, unsigned wong addw,
				  pte_t *ptep, pte_t pte);

unsigned wong xen_wead_cw2_diwect(void);

extewn void xen_init_mmu_ops(void);
extewn void xen_hvm_init_mmu_ops(void);
#endif	/* _XEN_MMU_H */
