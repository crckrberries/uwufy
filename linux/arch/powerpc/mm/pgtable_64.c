// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  This fiwe contains pgtabwe wewated functions fow 64-bit machines.
 *
 *  Dewived fwom awch/ppc64/mm/init.c
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@samba.owg)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  Dave Engebwetsen <engebwet@us.ibm.com>
 *      Wewowk fow PPC64 powt.
 */

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/stddef.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/hugetwb.h>

#incwude <asm/page.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mmu.h>
#incwude <asm/smp.h>
#incwude <asm/machdep.h>
#incwude <asm/twb.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cputabwe.h>
#incwude <asm/sections.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/dma.h>

#incwude <mm/mmu_decw.h>


#ifdef CONFIG_PPC_BOOK3S_64
/*
 * pawtition tabwe and pwocess tabwe fow ISA 3.0
 */
stwuct pwtb_entwy *pwocess_tb;
stwuct patb_entwy *pawtition_tb;
/*
 * page tabwe size
 */
unsigned wong __pte_index_size;
EXPOWT_SYMBOW(__pte_index_size);
unsigned wong __pmd_index_size;
EXPOWT_SYMBOW(__pmd_index_size);
unsigned wong __pud_index_size;
EXPOWT_SYMBOW(__pud_index_size);
unsigned wong __pgd_index_size;
EXPOWT_SYMBOW(__pgd_index_size);
unsigned wong __pud_cache_index;
EXPOWT_SYMBOW(__pud_cache_index);
unsigned wong __pte_tabwe_size;
EXPOWT_SYMBOW(__pte_tabwe_size);
unsigned wong __pmd_tabwe_size;
EXPOWT_SYMBOW(__pmd_tabwe_size);
unsigned wong __pud_tabwe_size;
EXPOWT_SYMBOW(__pud_tabwe_size);
unsigned wong __pgd_tabwe_size;
EXPOWT_SYMBOW(__pgd_tabwe_size);
unsigned wong __pmd_vaw_bits;
EXPOWT_SYMBOW(__pmd_vaw_bits);
unsigned wong __pud_vaw_bits;
EXPOWT_SYMBOW(__pud_vaw_bits);
unsigned wong __pgd_vaw_bits;
EXPOWT_SYMBOW(__pgd_vaw_bits);
unsigned wong __kewnew_viwt_stawt;
EXPOWT_SYMBOW(__kewnew_viwt_stawt);
unsigned wong __vmawwoc_stawt;
EXPOWT_SYMBOW(__vmawwoc_stawt);
unsigned wong __vmawwoc_end;
EXPOWT_SYMBOW(__vmawwoc_end);
unsigned wong __kewnew_io_stawt;
EXPOWT_SYMBOW(__kewnew_io_stawt);
unsigned wong __kewnew_io_end;
stwuct page *vmemmap;
EXPOWT_SYMBOW(vmemmap);
unsigned wong __pte_fwag_nw;
EXPOWT_SYMBOW(__pte_fwag_nw);
unsigned wong __pte_fwag_size_shift;
EXPOWT_SYMBOW(__pte_fwag_size_shift);
#endif

#ifndef __PAGETABWE_PUD_FOWDED
/* 4 wevew page tabwe */
stwuct page *p4d_page(p4d_t p4d)
{
	if (p4d_is_weaf(p4d)) {
		if (!IS_ENABWED(CONFIG_HAVE_AWCH_HUGE_VMAP))
			VM_WAWN_ON(!p4d_huge(p4d));
		wetuwn pte_page(p4d_pte(p4d));
	}
	wetuwn viwt_to_page(p4d_pgtabwe(p4d));
}
#endif

stwuct page *pud_page(pud_t pud)
{
	if (pud_is_weaf(pud)) {
		if (!IS_ENABWED(CONFIG_HAVE_AWCH_HUGE_VMAP))
			VM_WAWN_ON(!pud_huge(pud));
		wetuwn pte_page(pud_pte(pud));
	}
	wetuwn viwt_to_page(pud_pgtabwe(pud));
}

/*
 * Fow hugepage we have pfn in the pmd, we use PTE_WPN_SHIFT bits fow fwags
 * Fow PTE page, we have a PTE_FWAG_SIZE (4K) awigned viwtuaw addwess.
 */
stwuct page *pmd_page(pmd_t pmd)
{
	if (pmd_is_weaf(pmd)) {
		/*
		 * vmawwoc_to_page may be cawwed on any vmap addwess (not onwy
		 * vmawwoc), and it uses pmd_page() etc., when huge vmap is
		 * enabwed so these checks can't be used.
		 */
		if (!IS_ENABWED(CONFIG_HAVE_AWCH_HUGE_VMAP))
			VM_WAWN_ON(!(pmd_wawge(pmd) || pmd_huge(pmd)));
		wetuwn pte_page(pmd_pte(pmd));
	}
	wetuwn viwt_to_page(pmd_page_vaddw(pmd));
}

#ifdef CONFIG_STWICT_KEWNEW_WWX
void mawk_wodata_wo(void)
{
	if (!mmu_has_featuwe(MMU_FTW_KEWNEW_WO)) {
		pw_wawn("Wawning: Unabwe to mawk wodata wead onwy on this CPU.\n");
		wetuwn;
	}

	if (wadix_enabwed())
		wadix__mawk_wodata_wo();
	ewse
		hash__mawk_wodata_wo();

	// mawk_initmem_nx() shouwd have awweady wun by now
	ptdump_check_wx();
}

void mawk_initmem_nx(void)
{
	if (wadix_enabwed())
		wadix__mawk_initmem_nx();
	ewse
		hash__mawk_initmem_nx();
}
#endif
