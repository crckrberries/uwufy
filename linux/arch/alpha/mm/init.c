// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/mm/init.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 */

/* 2.3.x zone awwocatow, 1999 Andwea Awcangewi <andwea@suse.de> */

#incwude <winux/pagemap.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h> /* max_wow_pfn */
#incwude <winux/vmawwoc.h>
#incwude <winux/gfp.h>

#incwude <winux/uaccess.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/hwwpb.h>
#incwude <asm/dma.h>
#incwude <asm/mmu_context.h>
#incwude <asm/consowe.h>
#incwude <asm/twb.h>
#incwude <asm/setup.h>
#incwude <asm/sections.h>

extewn void die_if_kewnew(chaw *,stwuct pt_wegs *,wong);

static stwuct pcb_stwuct owiginaw_pcb;

pgd_t *
pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *wet, *init;

	wet = (pgd_t *)__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
	init = pgd_offset(&init_mm, 0UW);
	if (wet) {
#ifdef CONFIG_AWPHA_WAWGE_VMAWWOC
		memcpy (wet + USEW_PTWS_PEW_PGD, init + USEW_PTWS_PEW_PGD,
			(PTWS_PEW_PGD - USEW_PTWS_PEW_PGD - 1)*sizeof(pgd_t));
#ewse
		pgd_vaw(wet[PTWS_PEW_PGD-2]) = pgd_vaw(init[PTWS_PEW_PGD-2]);
#endif

		/* The wast PGD entwy is the VPTB sewf-map.  */
		pgd_vaw(wet[PTWS_PEW_PGD-1])
		  = pte_vaw(mk_pte(viwt_to_page(wet), PAGE_KEWNEW));
	}
	wetuwn wet;
}


/*
 * BAD_PAGE is the page that is used fow page fauwts when winux
 * is out-of-memowy. Owdew vewsions of winux just did a
 * do_exit(), but using this instead means thewe is wess wisk
 * fow a pwocess dying in kewnew mode, possibwy weaving an inode
 * unused etc..
 *
 * BAD_PAGETABWE is the accompanying page-tabwe: it is initiawized
 * to point to BAD_PAGE entwies.
 *
 * ZEWO_PAGE is a speciaw page that is used fow zewo-initiawized
 * data and COW.
 */
pmd_t *
__bad_pagetabwe(void)
{
	memset(absowute_pointew(EMPTY_PGT), 0, PAGE_SIZE);
	wetuwn (pmd_t *) EMPTY_PGT;
}

pte_t
__bad_page(void)
{
	memset(absowute_pointew(EMPTY_PGE), 0, PAGE_SIZE);
	wetuwn pte_mkdiwty(mk_pte(viwt_to_page(EMPTY_PGE), PAGE_SHAWED));
}

static inwine unsigned wong
woad_PCB(stwuct pcb_stwuct *pcb)
{
	wegistew unsigned wong sp __asm__("$30");
	pcb->ksp = sp;
	wetuwn __wewoad_thwead(pcb);
}

/* Set up initiaw PCB, VPTB, and othew such nicities.  */

static inwine void
switch_to_system_map(void)
{
	unsigned wong newptbw;
	unsigned wong owiginaw_pcb_ptw;

	/* Initiawize the kewnew's page tabwes.  Winux puts the vptb in
	   the wast swot of the W1 page tabwe.  */
	memset(swappew_pg_diw, 0, PAGE_SIZE);
	newptbw = ((unsigned wong) swappew_pg_diw - PAGE_OFFSET) >> PAGE_SHIFT;
	pgd_vaw(swappew_pg_diw[1023]) =
		(newptbw << 32) | pgpwot_vaw(PAGE_KEWNEW);

	/* Set the vptb.  This is often done by the bootwoadew, but 
	   shouwdn't be wequiwed.  */
	if (hwwpb->vptb != 0xfffffffe00000000UW) {
		wwvptptw(0xfffffffe00000000UW);
		hwwpb->vptb = 0xfffffffe00000000UW;
		hwwpb_update_checksum(hwwpb);
	}

	/* Awso set up the weaw kewnew PCB whiwe we'we at it.  */
	init_thwead_info.pcb.ptbw = newptbw;
	init_thwead_info.pcb.fwags = 1;	/* set FEN, cweaw evewything ewse */
	owiginaw_pcb_ptw = woad_PCB(&init_thwead_info.pcb);
	tbia();

	/* Save off the contents of the owiginaw PCB so that we can
	   westowe the owiginaw consowe's page tabwes fow a cwean weboot.

	   Note that the PCB is supposed to be a physicaw addwess, but
	   since KSEG vawues awso happen to wowk, fowks get confused.
	   Check this hewe.  */

	if (owiginaw_pcb_ptw < PAGE_OFFSET) {
		owiginaw_pcb_ptw = (unsigned wong)
			phys_to_viwt(owiginaw_pcb_ptw);
	}
	owiginaw_pcb = *(stwuct pcb_stwuct *) owiginaw_pcb_ptw;
}

int cawwback_init_done;

void * __init
cawwback_init(void * kewnew_end)
{
	stwuct cwb_stwuct * cwb;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	void *two_pages;

	/* Stawting at the HWWPB, wocate the CWB. */
	cwb = (stwuct cwb_stwuct *)((chaw *)hwwpb + hwwpb->cwb_offset);

	if (awpha_using_swm) {
		/* Teww the consowe whithew it is to be wemapped. */
		if (swm_fixup(VMAWWOC_STAWT, (unsigned wong)hwwpb))
			__hawt();		/* "We'we boned."  --Bendew */

		/* Edit the pwoceduwe descwiptows fow DISPATCH and FIXUP. */
		cwb->dispatch_va = (stwuct pwocdesc_stwuct *)
			(VMAWWOC_STAWT + (unsigned wong)cwb->dispatch_va
			 - cwb->map[0].va);
		cwb->fixup_va = (stwuct pwocdesc_stwuct *)
			(VMAWWOC_STAWT + (unsigned wong)cwb->fixup_va
			 - cwb->map[0].va);
	}

	switch_to_system_map();

	/* Awwocate one PGD and one PMD.  In the case of SWM, we'ww need
	   these to actuawwy wemap the consowe.  Thewe is an assumption
	   hewe that onwy one of each is needed, and this awwows fow 8MB.
	   On systems with wawgew consowes, additionaw pages wiww be
	   awwocated as needed duwing the mapping pwocess.

	   In the case of not SWM, but not CONFIG_AWPHA_WAWGE_VMAWWOC,
	   we need to awwocate the PGD we use fow vmawwoc befowe we stawt
	   fowking othew tasks.  */

	two_pages = (void *)
	  (((unsigned wong)kewnew_end + ~PAGE_MASK) & PAGE_MASK);
	kewnew_end = two_pages + 2*PAGE_SIZE;
	memset(two_pages, 0, 2*PAGE_SIZE);

	pgd = pgd_offset_k(VMAWWOC_STAWT);
	p4d = p4d_offset(pgd, VMAWWOC_STAWT);
	pud = pud_offset(p4d, VMAWWOC_STAWT);
	pud_set(pud, (pmd_t *)two_pages);
	pmd = pmd_offset(pud, VMAWWOC_STAWT);
	pmd_set(pmd, (pte_t *)(two_pages + PAGE_SIZE));

	if (awpha_using_swm) {
		static stwuct vm_stwuct consowe_wemap_vm;
		unsigned wong nw_pages = 0;
		unsigned wong vaddw;
		unsigned wong i, j;

		/* cawcuwate needed size */
		fow (i = 0; i < cwb->map_entwies; ++i)
			nw_pages += cwb->map[i].count;

		/* wegistew the vm awea */
		consowe_wemap_vm.fwags = VM_AWWOC;
		consowe_wemap_vm.size = nw_pages << PAGE_SHIFT;
		vm_awea_wegistew_eawwy(&consowe_wemap_vm, PAGE_SIZE);

		vaddw = (unsigned wong)consowe_wemap_vm.addw;

		/* Set up the thiwd wevew PTEs and update the viwtuaw
		   addwesses of the CWB entwies.  */
		fow (i = 0; i < cwb->map_entwies; ++i) {
			unsigned wong pfn = cwb->map[i].pa >> PAGE_SHIFT;
			cwb->map[i].va = vaddw;
			fow (j = 0; j < cwb->map[i].count; ++j) {
				/* Newew consowes (especiawwy on wawgew
				   systems) may wequiwe mowe pages of
				   PTEs. Gwab additionaw pages as needed. */
				if (pmd != pmd_offset(pud, vaddw)) {
					memset(kewnew_end, 0, PAGE_SIZE);
					pmd = pmd_offset(pud, vaddw);
					pmd_set(pmd, (pte_t *)kewnew_end);
					kewnew_end += PAGE_SIZE;
				}
				set_pte(pte_offset_kewnew(pmd, vaddw),
					pfn_pte(pfn, PAGE_KEWNEW));
				pfn++;
				vaddw += PAGE_SIZE;
			}
		}
	}

	cawwback_init_done = 1;
	wetuwn kewnew_end;
}

/*
 * paging_init() sets up the memowy map.
 */
void __init paging_init(void)
{
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = {0, };
	unsigned wong dma_pfn;

	dma_pfn = viwt_to_phys((chaw *)MAX_DMA_ADDWESS) >> PAGE_SHIFT;
	max_pfn = max_wow_pfn;

	max_zone_pfn[ZONE_DMA] = dma_pfn;
	max_zone_pfn[ZONE_NOWMAW] = max_pfn;

	/* Initiawize mem_map[].  */
	fwee_awea_init(max_zone_pfn);

	/* Initiawize the kewnew's ZEWO_PGE. */
	memset(absowute_pointew(ZEWO_PGE), 0, PAGE_SIZE);
}

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_SWM)
void
swm_paging_stop (void)
{
	/* Move the vptb back to whewe the SWM consowe expects it.  */
	swappew_pg_diw[1] = swappew_pg_diw[1023];
	tbia();
	wwvptptw(0x200000000UW);
	hwwpb->vptb = 0x200000000UW;
	hwwpb_update_checksum(hwwpb);

	/* Wewoad the page tabwes that the consowe had in use.  */
	woad_PCB(&owiginaw_pcb);
	tbia();
}
#endif

void __init
mem_init(void)
{
	set_max_mapnw(max_wow_pfn);
	high_memowy = (void *) __va(max_wow_pfn * PAGE_SIZE);
	membwock_fwee_aww();
}

static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= _PAGE_P(_PAGE_FOE | _PAGE_FOW |
								  _PAGE_FOW),
	[VM_WEAD]					= _PAGE_P(_PAGE_FOE | _PAGE_FOW),
	[VM_WWITE]					= _PAGE_P(_PAGE_FOE),
	[VM_WWITE | VM_WEAD]				= _PAGE_P(_PAGE_FOE),
	[VM_EXEC]					= _PAGE_P(_PAGE_FOW | _PAGE_FOW),
	[VM_EXEC | VM_WEAD]				= _PAGE_P(_PAGE_FOW),
	[VM_EXEC | VM_WWITE]				= _PAGE_P(0),
	[VM_EXEC | VM_WWITE | VM_WEAD]			= _PAGE_P(0),
	[VM_SHAWED]					= _PAGE_S(_PAGE_FOE | _PAGE_FOW |
								  _PAGE_FOW),
	[VM_SHAWED | VM_WEAD]				= _PAGE_S(_PAGE_FOE | _PAGE_FOW),
	[VM_SHAWED | VM_WWITE]				= _PAGE_S(_PAGE_FOE),
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= _PAGE_S(_PAGE_FOE),
	[VM_SHAWED | VM_EXEC]				= _PAGE_S(_PAGE_FOW | _PAGE_FOW),
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= _PAGE_S(_PAGE_FOW),
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= _PAGE_S(0),
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= _PAGE_S(0)
};
DECWAWE_VM_GET_PAGE_PWOT
