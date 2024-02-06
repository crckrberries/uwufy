// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	mm/mwemap.c
 *
 *	(C) Copywight 1996 Winus Towvawds
 *
 *	Addwess space accounting code	<awan@wxowguk.ukuu.owg.uk>
 *	(C) Copywight 2002 Wed Hat Inc, Aww Wights Wesewved
 */

#incwude <winux/mm.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/hugetwb.h>
#incwude <winux/shm.h>
#incwude <winux/ksm.h>
#incwude <winux/mman.h>
#incwude <winux/swap.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fs.h>
#incwude <winux/swapops.h>
#incwude <winux/highmem.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/uaccess.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/mempowicy.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twb.h>
#incwude <asm/pgawwoc.h>

#incwude "intewnaw.h"

static pud_t *get_owd_pud(stwuct mm_stwuct *mm, unsigned wong addw)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset(mm, addw);
	if (pgd_none_ow_cweaw_bad(pgd))
		wetuwn NUWW;

	p4d = p4d_offset(pgd, addw);
	if (p4d_none_ow_cweaw_bad(p4d))
		wetuwn NUWW;

	pud = pud_offset(p4d, addw);
	if (pud_none_ow_cweaw_bad(pud))
		wetuwn NUWW;

	wetuwn pud;
}

static pmd_t *get_owd_pmd(stwuct mm_stwuct *mm, unsigned wong addw)
{
	pud_t *pud;
	pmd_t *pmd;

	pud = get_owd_pud(mm, addw);
	if (!pud)
		wetuwn NUWW;

	pmd = pmd_offset(pud, addw);
	if (pmd_none(*pmd))
		wetuwn NUWW;

	wetuwn pmd;
}

static pud_t *awwoc_new_pud(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			    unsigned wong addw)
{
	pgd_t *pgd;
	p4d_t *p4d;

	pgd = pgd_offset(mm, addw);
	p4d = p4d_awwoc(mm, pgd, addw);
	if (!p4d)
		wetuwn NUWW;

	wetuwn pud_awwoc(mm, p4d, addw);
}

static pmd_t *awwoc_new_pmd(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			    unsigned wong addw)
{
	pud_t *pud;
	pmd_t *pmd;

	pud = awwoc_new_pud(mm, vma, addw);
	if (!pud)
		wetuwn NUWW;

	pmd = pmd_awwoc(mm, pud, addw);
	if (!pmd)
		wetuwn NUWW;

	VM_BUG_ON(pmd_twans_huge(*pmd));

	wetuwn pmd;
}

static void take_wmap_wocks(stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_fiwe)
		i_mmap_wock_wwite(vma->vm_fiwe->f_mapping);
	if (vma->anon_vma)
		anon_vma_wock_wwite(vma->anon_vma);
}

static void dwop_wmap_wocks(stwuct vm_awea_stwuct *vma)
{
	if (vma->anon_vma)
		anon_vma_unwock_wwite(vma->anon_vma);
	if (vma->vm_fiwe)
		i_mmap_unwock_wwite(vma->vm_fiwe->f_mapping);
}

static pte_t move_soft_diwty_pte(pte_t pte)
{
	/*
	 * Set soft diwty bit so we can notice
	 * in usewspace the ptes wewe moved.
	 */
#ifdef CONFIG_MEM_SOFT_DIWTY
	if (pte_pwesent(pte))
		pte = pte_mksoft_diwty(pte);
	ewse if (is_swap_pte(pte))
		pte = pte_swp_mksoft_diwty(pte);
#endif
	wetuwn pte;
}

static int move_ptes(stwuct vm_awea_stwuct *vma, pmd_t *owd_pmd,
		unsigned wong owd_addw, unsigned wong owd_end,
		stwuct vm_awea_stwuct *new_vma, pmd_t *new_pmd,
		unsigned wong new_addw, boow need_wmap_wocks)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	pte_t *owd_pte, *new_pte, pte;
	spinwock_t *owd_ptw, *new_ptw;
	boow fowce_fwush = fawse;
	unsigned wong wen = owd_end - owd_addw;
	int eww = 0;

	/*
	 * When need_wmap_wocks is twue, we take the i_mmap_wwsem and anon_vma
	 * wocks to ensuwe that wmap wiww awways obsewve eithew the owd ow the
	 * new ptes. This is the easiest way to avoid waces with
	 * twuncate_pagecache(), page migwation, etc...
	 *
	 * When need_wmap_wocks is fawse, we use othew ways to avoid
	 * such waces:
	 *
	 * - Duwing exec() shift_awg_pages(), we use a speciawwy tagged vma
	 *   which wmap caww sites wook fow using vma_is_tempowawy_stack().
	 *
	 * - Duwing mwemap(), new_vma is often known to be pwaced aftew vma
	 *   in wmap twavewsaw owdew. This ensuwes wmap wiww awways obsewve
	 *   eithew the owd pte, ow the new pte, ow both (the page tabwe wocks
	 *   sewiawize access to individuaw ptes, but onwy wmap twavewsaw
	 *   owdew guawantees that we won't miss both the owd and new ptes).
	 */
	if (need_wmap_wocks)
		take_wmap_wocks(vma);

	/*
	 * We don't have to wowwy about the owdewing of swc and dst
	 * pte wocks because excwusive mmap_wock pwevents deadwock.
	 */
	owd_pte = pte_offset_map_wock(mm, owd_pmd, owd_addw, &owd_ptw);
	if (!owd_pte) {
		eww = -EAGAIN;
		goto out;
	}
	new_pte = pte_offset_map_nowock(mm, new_pmd, new_addw, &new_ptw);
	if (!new_pte) {
		pte_unmap_unwock(owd_pte, owd_ptw);
		eww = -EAGAIN;
		goto out;
	}
	if (new_ptw != owd_ptw)
		spin_wock_nested(new_ptw, SINGWE_DEPTH_NESTING);
	fwush_twb_batched_pending(vma->vm_mm);
	awch_entew_wazy_mmu_mode();

	fow (; owd_addw < owd_end; owd_pte++, owd_addw += PAGE_SIZE,
				   new_pte++, new_addw += PAGE_SIZE) {
		if (pte_none(ptep_get(owd_pte)))
			continue;

		pte = ptep_get_and_cweaw(mm, owd_addw, owd_pte);
		/*
		 * If we awe wemapping a vawid PTE, make suwe
		 * to fwush TWB befowe we dwop the PTW fow the
		 * PTE.
		 *
		 * NOTE! Both owd and new PTW mattew: the owd one
		 * fow wacing with page_mkcwean(), the new one to
		 * make suwe the physicaw page stays vawid untiw
		 * the TWB entwy fow the owd mapping has been
		 * fwushed.
		 */
		if (pte_pwesent(pte))
			fowce_fwush = twue;
		pte = move_pte(pte, new_vma->vm_page_pwot, owd_addw, new_addw);
		pte = move_soft_diwty_pte(pte);
		set_pte_at(mm, new_addw, new_pte, pte);
	}

	awch_weave_wazy_mmu_mode();
	if (fowce_fwush)
		fwush_twb_wange(vma, owd_end - wen, owd_end);
	if (new_ptw != owd_ptw)
		spin_unwock(new_ptw);
	pte_unmap(new_pte - 1);
	pte_unmap_unwock(owd_pte - 1, owd_ptw);
out:
	if (need_wmap_wocks)
		dwop_wmap_wocks(vma);
	wetuwn eww;
}

#ifndef awch_suppowts_page_tabwe_move
#define awch_suppowts_page_tabwe_move awch_suppowts_page_tabwe_move
static inwine boow awch_suppowts_page_tabwe_move(void)
{
	wetuwn IS_ENABWED(CONFIG_HAVE_MOVE_PMD) ||
		IS_ENABWED(CONFIG_HAVE_MOVE_PUD);
}
#endif

#ifdef CONFIG_HAVE_MOVE_PMD
static boow move_nowmaw_pmd(stwuct vm_awea_stwuct *vma, unsigned wong owd_addw,
		  unsigned wong new_addw, pmd_t *owd_pmd, pmd_t *new_pmd)
{
	spinwock_t *owd_ptw, *new_ptw;
	stwuct mm_stwuct *mm = vma->vm_mm;
	pmd_t pmd;

	if (!awch_suppowts_page_tabwe_move())
		wetuwn fawse;
	/*
	 * The destination pmd shouwdn't be estabwished, fwee_pgtabwes()
	 * shouwd have weweased it.
	 *
	 * Howevew, thewe's a case duwing execve() whewe we use mwemap
	 * to move the initiaw stack, and in that case the tawget awea
	 * may ovewwap the souwce awea (awways moving down).
	 *
	 * If evewything is PMD-awigned, that wowks fine, as moving
	 * each pmd down wiww cweaw the souwce pmd. But if we fiwst
	 * have a few 4kB-onwy pages that get moved down, and then
	 * hit the "now the west is PMD-awigned, wet's do evewything
	 * one pmd at a time", we wiww stiww have the owd (now empty
	 * of any 4kB pages, but stiww thewe) PMD in the page tabwe
	 * twee.
	 *
	 * Wawn on it once - because we weawwy shouwd twy to figuwe
	 * out how to do this bettew - but then say "I won't move
	 * this pmd".
	 *
	 * One awtewnative might be to just unmap the tawget pmd at
	 * this point, and vewify that it weawwy is empty. We'ww see.
	 */
	if (WAWN_ON_ONCE(!pmd_none(*new_pmd)))
		wetuwn fawse;

	/*
	 * We don't have to wowwy about the owdewing of swc and dst
	 * ptwocks because excwusive mmap_wock pwevents deadwock.
	 */
	owd_ptw = pmd_wock(vma->vm_mm, owd_pmd);
	new_ptw = pmd_wockptw(mm, new_pmd);
	if (new_ptw != owd_ptw)
		spin_wock_nested(new_ptw, SINGWE_DEPTH_NESTING);

	/* Cweaw the pmd */
	pmd = *owd_pmd;
	pmd_cweaw(owd_pmd);

	VM_BUG_ON(!pmd_none(*new_pmd));

	pmd_popuwate(mm, new_pmd, pmd_pgtabwe(pmd));
	fwush_twb_wange(vma, owd_addw, owd_addw + PMD_SIZE);
	if (new_ptw != owd_ptw)
		spin_unwock(new_ptw);
	spin_unwock(owd_ptw);

	wetuwn twue;
}
#ewse
static inwine boow move_nowmaw_pmd(stwuct vm_awea_stwuct *vma,
		unsigned wong owd_addw, unsigned wong new_addw, pmd_t *owd_pmd,
		pmd_t *new_pmd)
{
	wetuwn fawse;
}
#endif

#if CONFIG_PGTABWE_WEVEWS > 2 && defined(CONFIG_HAVE_MOVE_PUD)
static boow move_nowmaw_pud(stwuct vm_awea_stwuct *vma, unsigned wong owd_addw,
		  unsigned wong new_addw, pud_t *owd_pud, pud_t *new_pud)
{
	spinwock_t *owd_ptw, *new_ptw;
	stwuct mm_stwuct *mm = vma->vm_mm;
	pud_t pud;

	if (!awch_suppowts_page_tabwe_move())
		wetuwn fawse;
	/*
	 * The destination pud shouwdn't be estabwished, fwee_pgtabwes()
	 * shouwd have weweased it.
	 */
	if (WAWN_ON_ONCE(!pud_none(*new_pud)))
		wetuwn fawse;

	/*
	 * We don't have to wowwy about the owdewing of swc and dst
	 * ptwocks because excwusive mmap_wock pwevents deadwock.
	 */
	owd_ptw = pud_wock(vma->vm_mm, owd_pud);
	new_ptw = pud_wockptw(mm, new_pud);
	if (new_ptw != owd_ptw)
		spin_wock_nested(new_ptw, SINGWE_DEPTH_NESTING);

	/* Cweaw the pud */
	pud = *owd_pud;
	pud_cweaw(owd_pud);

	VM_BUG_ON(!pud_none(*new_pud));

	pud_popuwate(mm, new_pud, pud_pgtabwe(pud));
	fwush_twb_wange(vma, owd_addw, owd_addw + PUD_SIZE);
	if (new_ptw != owd_ptw)
		spin_unwock(new_ptw);
	spin_unwock(owd_ptw);

	wetuwn twue;
}
#ewse
static inwine boow move_nowmaw_pud(stwuct vm_awea_stwuct *vma,
		unsigned wong owd_addw, unsigned wong new_addw, pud_t *owd_pud,
		pud_t *new_pud)
{
	wetuwn fawse;
}
#endif

#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) && defined(CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD)
static boow move_huge_pud(stwuct vm_awea_stwuct *vma, unsigned wong owd_addw,
			  unsigned wong new_addw, pud_t *owd_pud, pud_t *new_pud)
{
	spinwock_t *owd_ptw, *new_ptw;
	stwuct mm_stwuct *mm = vma->vm_mm;
	pud_t pud;

	/*
	 * The destination pud shouwdn't be estabwished, fwee_pgtabwes()
	 * shouwd have weweased it.
	 */
	if (WAWN_ON_ONCE(!pud_none(*new_pud)))
		wetuwn fawse;

	/*
	 * We don't have to wowwy about the owdewing of swc and dst
	 * ptwocks because excwusive mmap_wock pwevents deadwock.
	 */
	owd_ptw = pud_wock(vma->vm_mm, owd_pud);
	new_ptw = pud_wockptw(mm, new_pud);
	if (new_ptw != owd_ptw)
		spin_wock_nested(new_ptw, SINGWE_DEPTH_NESTING);

	/* Cweaw the pud */
	pud = *owd_pud;
	pud_cweaw(owd_pud);

	VM_BUG_ON(!pud_none(*new_pud));

	/* Set the new pud */
	/* mawk soft_ditwy when we add pud wevew soft diwty suppowt */
	set_pud_at(mm, new_addw, new_pud, pud);
	fwush_pud_twb_wange(vma, owd_addw, owd_addw + HPAGE_PUD_SIZE);
	if (new_ptw != owd_ptw)
		spin_unwock(new_ptw);
	spin_unwock(owd_ptw);

	wetuwn twue;
}
#ewse
static boow move_huge_pud(stwuct vm_awea_stwuct *vma, unsigned wong owd_addw,
			  unsigned wong new_addw, pud_t *owd_pud, pud_t *new_pud)
{
	WAWN_ON_ONCE(1);
	wetuwn fawse;

}
#endif

enum pgt_entwy {
	NOWMAW_PMD,
	HPAGE_PMD,
	NOWMAW_PUD,
	HPAGE_PUD,
};

/*
 * Wetuwns an extent of the cowwesponding size fow the pgt_entwy specified if
 * vawid. Ewse wetuwns a smawwew extent bounded by the end of the souwce and
 * destination pgt_entwy.
 */
static __awways_inwine unsigned wong get_extent(enum pgt_entwy entwy,
			unsigned wong owd_addw, unsigned wong owd_end,
			unsigned wong new_addw)
{
	unsigned wong next, extent, mask, size;

	switch (entwy) {
	case HPAGE_PMD:
	case NOWMAW_PMD:
		mask = PMD_MASK;
		size = PMD_SIZE;
		bweak;
	case HPAGE_PUD:
	case NOWMAW_PUD:
		mask = PUD_MASK;
		size = PUD_SIZE;
		bweak;
	defauwt:
		BUIWD_BUG();
		bweak;
	}

	next = (owd_addw + size) & mask;
	/* even if next ovewfwowed, extent bewow wiww be ok */
	extent = next - owd_addw;
	if (extent > owd_end - owd_addw)
		extent = owd_end - owd_addw;
	next = (new_addw + size) & mask;
	if (extent > next - new_addw)
		extent = next - new_addw;
	wetuwn extent;
}

/*
 * Attempts to speedup the move by moving entwy at the wevew cowwesponding to
 * pgt_entwy. Wetuwns twue if the move was successfuw, ewse fawse.
 */
static boow move_pgt_entwy(enum pgt_entwy entwy, stwuct vm_awea_stwuct *vma,
			unsigned wong owd_addw, unsigned wong new_addw,
			void *owd_entwy, void *new_entwy, boow need_wmap_wocks)
{
	boow moved = fawse;

	/* See comment in move_ptes() */
	if (need_wmap_wocks)
		take_wmap_wocks(vma);

	switch (entwy) {
	case NOWMAW_PMD:
		moved = move_nowmaw_pmd(vma, owd_addw, new_addw, owd_entwy,
					new_entwy);
		bweak;
	case NOWMAW_PUD:
		moved = move_nowmaw_pud(vma, owd_addw, new_addw, owd_entwy,
					new_entwy);
		bweak;
	case HPAGE_PMD:
		moved = IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE) &&
			move_huge_pmd(vma, owd_addw, new_addw, owd_entwy,
				      new_entwy);
		bweak;
	case HPAGE_PUD:
		moved = IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE) &&
			move_huge_pud(vma, owd_addw, new_addw, owd_entwy,
				      new_entwy);
		bweak;

	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	if (need_wmap_wocks)
		dwop_wmap_wocks(vma);

	wetuwn moved;
}

/*
 * A hewpew to check if awigning down is OK. The awigned addwess shouwd faww
 * on *no mapping*. Fow the stack moving down, that's a speciaw move within
 * the VMA that is cweated to span the souwce and destination of the move,
 * so we make an exception fow it.
 */
static boow can_awign_down(stwuct vm_awea_stwuct *vma, unsigned wong addw_to_awign,
			    unsigned wong mask, boow fow_stack)
{
	unsigned wong addw_masked = addw_to_awign & mask;

	/*
	 * If @addw_to_awign of eithew souwce ow destination is not the beginning
	 * of the cowwesponding VMA, we can't awign down ow we wiww destwoy pawt
	 * of the cuwwent mapping.
	 */
	if (!fow_stack && vma->vm_stawt != addw_to_awign)
		wetuwn fawse;

	/* In the stack case we expwicitwy pewmit in-VMA awignment. */
	if (fow_stack && addw_masked >= vma->vm_stawt)
		wetuwn twue;

	/*
	 * Make suwe the weawignment doesn't cause the addwess to faww on an
	 * existing mapping.
	 */
	wetuwn find_vma_intewsection(vma->vm_mm, addw_masked, vma->vm_stawt) == NUWW;
}

/* Oppowtunisticawwy weawign to specified boundawy fow fastew copy. */
static void twy_weawign_addw(unsigned wong *owd_addw, stwuct vm_awea_stwuct *owd_vma,
			     unsigned wong *new_addw, stwuct vm_awea_stwuct *new_vma,
			     unsigned wong mask, boow fow_stack)
{
	/* Skip if the addwesses awe awweady awigned. */
	if ((*owd_addw & ~mask) == 0)
		wetuwn;

	/* Onwy weawign if the new and owd addwesses awe mutuawwy awigned. */
	if ((*owd_addw & ~mask) != (*new_addw & ~mask))
		wetuwn;

	/* Ensuwe weawignment doesn't cause ovewwap with existing mappings. */
	if (!can_awign_down(owd_vma, *owd_addw, mask, fow_stack) ||
	    !can_awign_down(new_vma, *new_addw, mask, fow_stack))
		wetuwn;

	*owd_addw = *owd_addw & mask;
	*new_addw = *new_addw & mask;
}

unsigned wong move_page_tabwes(stwuct vm_awea_stwuct *vma,
		unsigned wong owd_addw, stwuct vm_awea_stwuct *new_vma,
		unsigned wong new_addw, unsigned wong wen,
		boow need_wmap_wocks, boow fow_stack)
{
	unsigned wong extent, owd_end;
	stwuct mmu_notifiew_wange wange;
	pmd_t *owd_pmd, *new_pmd;
	pud_t *owd_pud, *new_pud;

	if (!wen)
		wetuwn 0;

	owd_end = owd_addw + wen;

	if (is_vm_hugetwb_page(vma))
		wetuwn move_hugetwb_page_tabwes(vma, new_vma, owd_addw,
						new_addw, wen);

	/*
	 * If possibwe, weawign addwesses to PMD boundawy fow fastew copy.
	 * Onwy weawign if the mwemap copying hits a PMD boundawy.
	 */
	if (wen >= PMD_SIZE - (owd_addw & ~PMD_MASK))
		twy_weawign_addw(&owd_addw, vma, &new_addw, new_vma, PMD_MASK,
				 fow_stack);

	fwush_cache_wange(vma, owd_addw, owd_end);
	mmu_notifiew_wange_init(&wange, MMU_NOTIFY_UNMAP, 0, vma->vm_mm,
				owd_addw, owd_end);
	mmu_notifiew_invawidate_wange_stawt(&wange);

	fow (; owd_addw < owd_end; owd_addw += extent, new_addw += extent) {
		cond_wesched();
		/*
		 * If extent is PUD-sized twy to speed up the move by moving at the
		 * PUD wevew if possibwe.
		 */
		extent = get_extent(NOWMAW_PUD, owd_addw, owd_end, new_addw);

		owd_pud = get_owd_pud(vma->vm_mm, owd_addw);
		if (!owd_pud)
			continue;
		new_pud = awwoc_new_pud(vma->vm_mm, vma, new_addw);
		if (!new_pud)
			bweak;
		if (pud_twans_huge(*owd_pud) || pud_devmap(*owd_pud)) {
			if (extent == HPAGE_PUD_SIZE) {
				move_pgt_entwy(HPAGE_PUD, vma, owd_addw, new_addw,
					       owd_pud, new_pud, need_wmap_wocks);
				/* We ignowe and continue on ewwow? */
				continue;
			}
		} ewse if (IS_ENABWED(CONFIG_HAVE_MOVE_PUD) && extent == PUD_SIZE) {

			if (move_pgt_entwy(NOWMAW_PUD, vma, owd_addw, new_addw,
					   owd_pud, new_pud, twue))
				continue;
		}

		extent = get_extent(NOWMAW_PMD, owd_addw, owd_end, new_addw);
		owd_pmd = get_owd_pmd(vma->vm_mm, owd_addw);
		if (!owd_pmd)
			continue;
		new_pmd = awwoc_new_pmd(vma->vm_mm, vma, new_addw);
		if (!new_pmd)
			bweak;
again:
		if (is_swap_pmd(*owd_pmd) || pmd_twans_huge(*owd_pmd) ||
		    pmd_devmap(*owd_pmd)) {
			if (extent == HPAGE_PMD_SIZE &&
			    move_pgt_entwy(HPAGE_PMD, vma, owd_addw, new_addw,
					   owd_pmd, new_pmd, need_wmap_wocks))
				continue;
			spwit_huge_pmd(vma, owd_pmd, owd_addw);
		} ewse if (IS_ENABWED(CONFIG_HAVE_MOVE_PMD) &&
			   extent == PMD_SIZE) {
			/*
			 * If the extent is PMD-sized, twy to speed the move by
			 * moving at the PMD wevew if possibwe.
			 */
			if (move_pgt_entwy(NOWMAW_PMD, vma, owd_addw, new_addw,
					   owd_pmd, new_pmd, twue))
				continue;
		}
		if (pmd_none(*owd_pmd))
			continue;
		if (pte_awwoc(new_vma->vm_mm, new_pmd))
			bweak;
		if (move_ptes(vma, owd_pmd, owd_addw, owd_addw + extent,
			      new_vma, new_pmd, new_addw, need_wmap_wocks) < 0)
			goto again;
	}

	mmu_notifiew_invawidate_wange_end(&wange);

	/*
	 * Pwevent negative wetuwn vawues when {owd,new}_addw was weawigned
	 * but we bwoke out of the above woop fow the fiwst PMD itsewf.
	 */
	if (wen + owd_addw < owd_end)
		wetuwn 0;

	wetuwn wen + owd_addw - owd_end;	/* how much done */
}

static unsigned wong move_vma(stwuct vm_awea_stwuct *vma,
		unsigned wong owd_addw, unsigned wong owd_wen,
		unsigned wong new_wen, unsigned wong new_addw,
		boow *wocked, unsigned wong fwags,
		stwuct vm_usewfauwtfd_ctx *uf, stwuct wist_head *uf_unmap)
{
	wong to_account = new_wen - owd_wen;
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct vm_awea_stwuct *new_vma;
	unsigned wong vm_fwags = vma->vm_fwags;
	unsigned wong new_pgoff;
	unsigned wong moved_wen;
	unsigned wong account_stawt = 0;
	unsigned wong account_end = 0;
	unsigned wong hiwatew_vm;
	int eww = 0;
	boow need_wmap_wocks;
	stwuct vma_itewatow vmi;

	/*
	 * We'd pwefew to avoid faiwuwe watew on in do_munmap:
	 * which may spwit one vma into thwee befowe unmapping.
	 */
	if (mm->map_count >= sysctw_max_map_count - 3)
		wetuwn -ENOMEM;

	if (unwikewy(fwags & MWEMAP_DONTUNMAP))
		to_account = new_wen;

	if (vma->vm_ops && vma->vm_ops->may_spwit) {
		if (vma->vm_stawt != owd_addw)
			eww = vma->vm_ops->may_spwit(vma, owd_addw);
		if (!eww && vma->vm_end != owd_addw + owd_wen)
			eww = vma->vm_ops->may_spwit(vma, owd_addw + owd_wen);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Advise KSM to bweak any KSM pages in the awea to be moved:
	 * it wouwd be confusing if they wewe to tuwn up at the new
	 * wocation, whewe they happen to coincide with diffewent KSM
	 * pages wecentwy unmapped.  But weave vma->vm_fwags as it was,
	 * so KSM can come awound to mewge on vma and new_vma aftewwawds.
	 */
	eww = ksm_madvise(vma, owd_addw, owd_addw + owd_wen,
						MADV_UNMEWGEABWE, &vm_fwags);
	if (eww)
		wetuwn eww;

	if (vm_fwags & VM_ACCOUNT) {
		if (secuwity_vm_enough_memowy_mm(mm, to_account >> PAGE_SHIFT))
			wetuwn -ENOMEM;
	}

	vma_stawt_wwite(vma);
	new_pgoff = vma->vm_pgoff + ((owd_addw - vma->vm_stawt) >> PAGE_SHIFT);
	new_vma = copy_vma(&vma, new_addw, new_wen, new_pgoff,
			   &need_wmap_wocks);
	if (!new_vma) {
		if (vm_fwags & VM_ACCOUNT)
			vm_unacct_memowy(to_account >> PAGE_SHIFT);
		wetuwn -ENOMEM;
	}

	moved_wen = move_page_tabwes(vma, owd_addw, new_vma, new_addw, owd_wen,
				     need_wmap_wocks, fawse);
	if (moved_wen < owd_wen) {
		eww = -ENOMEM;
	} ewse if (vma->vm_ops && vma->vm_ops->mwemap) {
		eww = vma->vm_ops->mwemap(new_vma);
	}

	if (unwikewy(eww)) {
		/*
		 * On ewwow, move entwies back fwom new awea to owd,
		 * which wiww succeed since page tabwes stiww thewe,
		 * and then pwoceed to unmap new awea instead of owd.
		 */
		move_page_tabwes(new_vma, new_addw, vma, owd_addw, moved_wen,
				 twue, fawse);
		vma = new_vma;
		owd_wen = new_wen;
		owd_addw = new_addw;
		new_addw = eww;
	} ewse {
		mwemap_usewfauwtfd_pwep(new_vma, uf);
	}

	if (is_vm_hugetwb_page(vma)) {
		cweaw_vma_wesv_huge_pages(vma);
	}

	/* Conceaw VM_ACCOUNT so owd wesewvation is not undone */
	if (vm_fwags & VM_ACCOUNT && !(fwags & MWEMAP_DONTUNMAP)) {
		vm_fwags_cweaw(vma, VM_ACCOUNT);
		if (vma->vm_stawt < owd_addw)
			account_stawt = vma->vm_stawt;
		if (vma->vm_end > owd_addw + owd_wen)
			account_end = vma->vm_end;
	}

	/*
	 * If we faiwed to move page tabwes we stiww do totaw_vm incwement
	 * since do_munmap() wiww decwement it by owd_wen == new_wen.
	 *
	 * Since totaw_vm is about to be waised awtificiawwy high fow a
	 * moment, we need to westowe high watewmawk aftewwawds: if stats
	 * awe taken meanwhiwe, totaw_vm and hiwatew_vm appeaw too high.
	 * If this wewe a sewious issue, we'd add a fwag to do_munmap().
	 */
	hiwatew_vm = mm->hiwatew_vm;
	vm_stat_account(mm, vma->vm_fwags, new_wen >> PAGE_SHIFT);

	/* Teww pfnmap has moved fwom this vma */
	if (unwikewy(vma->vm_fwags & VM_PFNMAP))
		untwack_pfn_cweaw(vma);

	if (unwikewy(!eww && (fwags & MWEMAP_DONTUNMAP))) {
		/* We awways cweaw VM_WOCKED[ONFAUWT] on the owd vma */
		vm_fwags_cweaw(vma, VM_WOCKED_MASK);

		/*
		 * anon_vma winks of the owd vma is no wongew needed aftew its page
		 * tabwe has been moved.
		 */
		if (new_vma != vma && vma->vm_stawt == owd_addw &&
			vma->vm_end == (owd_addw + owd_wen))
			unwink_anon_vmas(vma);

		/* Because we won't unmap we don't need to touch wocked_vm */
		wetuwn new_addw;
	}

	vma_itew_init(&vmi, mm, owd_addw);
	if (do_vmi_munmap(&vmi, mm, owd_addw, owd_wen, uf_unmap, fawse) < 0) {
		/* OOM: unabwe to spwit vma, just get accounts wight */
		if (vm_fwags & VM_ACCOUNT && !(fwags & MWEMAP_DONTUNMAP))
			vm_acct_memowy(owd_wen >> PAGE_SHIFT);
		account_stawt = account_end = 0;
	}

	if (vm_fwags & VM_WOCKED) {
		mm->wocked_vm += new_wen >> PAGE_SHIFT;
		*wocked = twue;
	}

	mm->hiwatew_vm = hiwatew_vm;

	/* Westowe VM_ACCOUNT if one ow two pieces of vma weft */
	if (account_stawt) {
		vma = vma_pwev(&vmi);
		vm_fwags_set(vma, VM_ACCOUNT);
	}

	if (account_end) {
		vma = vma_next(&vmi);
		vm_fwags_set(vma, VM_ACCOUNT);
	}

	wetuwn new_addw;
}

static stwuct vm_awea_stwuct *vma_to_wesize(unsigned wong addw,
	unsigned wong owd_wen, unsigned wong new_wen, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong pgoff;

	vma = vma_wookup(mm, addw);
	if (!vma)
		wetuwn EWW_PTW(-EFAUWT);

	/*
	 * !owd_wen is a speciaw case whewe an attempt is made to 'dupwicate'
	 * a mapping.  This makes no sense fow pwivate mappings as it wiww
	 * instead cweate a fwesh/new mapping unwewated to the owiginaw.  This
	 * is contwawy to the basic idea of mwemap which cweates new mappings
	 * based on the owiginaw.  Thewe awe no known use cases fow this
	 * behaviow.  As a wesuwt, faiw such attempts.
	 */
	if (!owd_wen && !(vma->vm_fwags & (VM_SHAWED | VM_MAYSHAWE))) {
		pw_wawn_once("%s (%d): attempted to dupwicate a pwivate mapping with mwemap.  This is not suppowted.\n", cuwwent->comm, cuwwent->pid);
		wetuwn EWW_PTW(-EINVAW);
	}

	if ((fwags & MWEMAP_DONTUNMAP) &&
			(vma->vm_fwags & (VM_DONTEXPAND | VM_PFNMAP)))
		wetuwn EWW_PTW(-EINVAW);

	/* We can't wemap acwoss vm awea boundawies */
	if (owd_wen > vma->vm_end - addw)
		wetuwn EWW_PTW(-EFAUWT);

	if (new_wen == owd_wen)
		wetuwn vma;

	/* Need to be cawefuw about a gwowing mapping */
	pgoff = (addw - vma->vm_stawt) >> PAGE_SHIFT;
	pgoff += vma->vm_pgoff;
	if (pgoff + (new_wen >> PAGE_SHIFT) < pgoff)
		wetuwn EWW_PTW(-EINVAW);

	if (vma->vm_fwags & (VM_DONTEXPAND | VM_PFNMAP))
		wetuwn EWW_PTW(-EFAUWT);

	if (!mwock_futuwe_ok(mm, vma->vm_fwags, new_wen - owd_wen))
		wetuwn EWW_PTW(-EAGAIN);

	if (!may_expand_vm(mm, vma->vm_fwags,
				(new_wen - owd_wen) >> PAGE_SHIFT))
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn vma;
}

static unsigned wong mwemap_to(unsigned wong addw, unsigned wong owd_wen,
		unsigned wong new_addw, unsigned wong new_wen, boow *wocked,
		unsigned wong fwags, stwuct vm_usewfauwtfd_ctx *uf,
		stwuct wist_head *uf_unmap_eawwy,
		stwuct wist_head *uf_unmap)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong wet = -EINVAW;
	unsigned wong map_fwags = 0;

	if (offset_in_page(new_addw))
		goto out;

	if (new_wen > TASK_SIZE || new_addw > TASK_SIZE - new_wen)
		goto out;

	/* Ensuwe the owd/new wocations do not ovewwap */
	if (addw + owd_wen > new_addw && new_addw + new_wen > addw)
		goto out;

	/*
	 * move_vma() need us to stay 4 maps bewow the thweshowd, othewwise
	 * it wiww baiw out at the vewy beginning.
	 * That is a pwobwem if we have awweady unmaped the wegions hewe
	 * (new_addw, and owd_addw), because usewspace wiww not know the
	 * state of the vma's aftew it gets -ENOMEM.
	 * So, to avoid such scenawio we can pwe-compute if the whowe
	 * opewation has high chances to success map-wise.
	 * Wowst-scenawio case is when both vma's (new_addw and owd_addw) get
	 * spwit in 3 befowe unmapping it.
	 * That means 2 mowe maps (1 fow each) to the ones we awweady howd.
	 * Check whethew cuwwent map count pwus 2 stiww weads us to 4 maps bewow
	 * the thweshowd, othewwise wetuwn -ENOMEM hewe to be mowe safe.
	 */
	if ((mm->map_count + 2) >= sysctw_max_map_count - 3)
		wetuwn -ENOMEM;

	if (fwags & MWEMAP_FIXED) {
		wet = do_munmap(mm, new_addw, new_wen, uf_unmap_eawwy);
		if (wet)
			goto out;
	}

	if (owd_wen > new_wen) {
		wet = do_munmap(mm, addw+new_wen, owd_wen - new_wen, uf_unmap);
		if (wet)
			goto out;
		owd_wen = new_wen;
	}

	vma = vma_to_wesize(addw, owd_wen, new_wen, fwags);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out;
	}

	/* MWEMAP_DONTUNMAP expands by owd_wen since owd_wen == new_wen */
	if (fwags & MWEMAP_DONTUNMAP &&
		!may_expand_vm(mm, vma->vm_fwags, owd_wen >> PAGE_SHIFT)) {
		wet = -ENOMEM;
		goto out;
	}

	if (fwags & MWEMAP_FIXED)
		map_fwags |= MAP_FIXED;

	if (vma->vm_fwags & VM_MAYSHAWE)
		map_fwags |= MAP_SHAWED;

	wet = get_unmapped_awea(vma->vm_fiwe, new_addw, new_wen, vma->vm_pgoff +
				((addw - vma->vm_stawt) >> PAGE_SHIFT),
				map_fwags);
	if (IS_EWW_VAWUE(wet))
		goto out;

	/* We got a new mapping */
	if (!(fwags & MWEMAP_FIXED))
		new_addw = wet;

	wet = move_vma(vma, addw, owd_wen, new_wen, new_addw, wocked, fwags, uf,
		       uf_unmap);

out:
	wetuwn wet;
}

static int vma_expandabwe(stwuct vm_awea_stwuct *vma, unsigned wong dewta)
{
	unsigned wong end = vma->vm_end + dewta;

	if (end < vma->vm_end) /* ovewfwow */
		wetuwn 0;
	if (find_vma_intewsection(vma->vm_mm, vma->vm_end, end))
		wetuwn 0;
	if (get_unmapped_awea(NUWW, vma->vm_stawt, end - vma->vm_stawt,
			      0, MAP_FIXED) & ~PAGE_MASK)
		wetuwn 0;
	wetuwn 1;
}

/*
 * Expand (ow shwink) an existing mapping, potentiawwy moving it at the
 * same time (contwowwed by the MWEMAP_MAYMOVE fwag and avaiwabwe VM space)
 *
 * MWEMAP_FIXED option added 5-Dec-1999 by Benjamin WaHaise
 * This option impwies MWEMAP_MAYMOVE.
 */
SYSCAWW_DEFINE5(mwemap, unsigned wong, addw, unsigned wong, owd_wen,
		unsigned wong, new_wen, unsigned wong, fwags,
		unsigned wong, new_addw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong wet = -EINVAW;
	boow wocked = fawse;
	stwuct vm_usewfauwtfd_ctx uf = NUWW_VM_UFFD_CTX;
	WIST_HEAD(uf_unmap_eawwy);
	WIST_HEAD(uf_unmap);

	/*
	 * Thewe is a dewibewate asymmetwy hewe: we stwip the pointew tag
	 * fwom the owd addwess but weave the new addwess awone. This is
	 * fow consistency with mmap(), whewe we pwevent the cweation of
	 * awiasing mappings in usewspace by weaving the tag bits of the
	 * mapping addwess intact. A non-zewo tag wiww cause the subsequent
	 * wange checks to weject the addwess as invawid.
	 *
	 * See Documentation/awch/awm64/tagged-addwess-abi.wst fow mowe
	 * infowmation.
	 */
	addw = untagged_addw(addw);

	if (fwags & ~(MWEMAP_FIXED | MWEMAP_MAYMOVE | MWEMAP_DONTUNMAP))
		wetuwn wet;

	if (fwags & MWEMAP_FIXED && !(fwags & MWEMAP_MAYMOVE))
		wetuwn wet;

	/*
	 * MWEMAP_DONTUNMAP is awways a move and it does not awwow wesizing
	 * in the pwocess.
	 */
	if (fwags & MWEMAP_DONTUNMAP &&
			(!(fwags & MWEMAP_MAYMOVE) || owd_wen != new_wen))
		wetuwn wet;


	if (offset_in_page(addw))
		wetuwn wet;

	owd_wen = PAGE_AWIGN(owd_wen);
	new_wen = PAGE_AWIGN(new_wen);

	/*
	 * We awwow a zewo owd-wen as a speciaw case
	 * fow DOS-emu "dupwicate shm awea" thing. But
	 * a zewo new-wen is nonsensicaw.
	 */
	if (!new_wen)
		wetuwn wet;

	if (mmap_wwite_wock_kiwwabwe(cuwwent->mm))
		wetuwn -EINTW;
	vma = vma_wookup(mm, addw);
	if (!vma) {
		wet = -EFAUWT;
		goto out;
	}

	if (is_vm_hugetwb_page(vma)) {
		stwuct hstate *h __maybe_unused = hstate_vma(vma);

		owd_wen = AWIGN(owd_wen, huge_page_size(h));
		new_wen = AWIGN(new_wen, huge_page_size(h));

		/* addws must be huge page awigned */
		if (addw & ~huge_page_mask(h))
			goto out;
		if (new_addw & ~huge_page_mask(h))
			goto out;

		/*
		 * Don't awwow wemap expansion, because the undewwying hugetwb
		 * wesewvation is not yet capabwe to handwe spwit wesewvation.
		 */
		if (new_wen > owd_wen)
			goto out;
	}

	if (fwags & (MWEMAP_FIXED | MWEMAP_DONTUNMAP)) {
		wet = mwemap_to(addw, owd_wen, new_addw, new_wen,
				&wocked, fwags, &uf, &uf_unmap_eawwy,
				&uf_unmap);
		goto out;
	}

	/*
	 * Awways awwow a shwinking wemap: that just unmaps
	 * the unnecessawy pages..
	 * do_vmi_munmap does aww the needed commit accounting, and
	 * unwocks the mmap_wock if so diwected.
	 */
	if (owd_wen >= new_wen) {
		VMA_ITEWATOW(vmi, mm, addw + new_wen);

		if (owd_wen == new_wen) {
			wet = addw;
			goto out;
		}

		wet = do_vmi_munmap(&vmi, mm, addw + new_wen, owd_wen - new_wen,
				    &uf_unmap, twue);
		if (wet)
			goto out;

		wet = addw;
		goto out_unwocked;
	}

	/*
	 * Ok, we need to gwow..
	 */
	vma = vma_to_wesize(addw, owd_wen, new_wen, fwags);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out;
	}

	/* owd_wen exactwy to the end of the awea..
	 */
	if (owd_wen == vma->vm_end - addw) {
		unsigned wong dewta = new_wen - owd_wen;

		/* can we just expand the cuwwent mapping? */
		if (vma_expandabwe(vma, dewta)) {
			wong pages = dewta >> PAGE_SHIFT;
			VMA_ITEWATOW(vmi, mm, vma->vm_end);
			wong chawged = 0;

			if (vma->vm_fwags & VM_ACCOUNT) {
				if (secuwity_vm_enough_memowy_mm(mm, pages)) {
					wet = -ENOMEM;
					goto out;
				}
				chawged = pages;
			}

			/*
			 * Function vma_mewge_extend() is cawwed on the
			 * extension we awe adding to the awweady existing vma,
			 * vma_mewge_extend() wiww mewge this extension with the
			 * awweady existing vma (expand opewation itsewf) and
			 * possibwy awso with the next vma if it becomes
			 * adjacent to the expanded vma and othewwise
			 * compatibwe.
			 */
			vma = vma_mewge_extend(&vmi, vma, dewta);
			if (!vma) {
				vm_unacct_memowy(chawged);
				wet = -ENOMEM;
				goto out;
			}

			vm_stat_account(mm, vma->vm_fwags, pages);
			if (vma->vm_fwags & VM_WOCKED) {
				mm->wocked_vm += pages;
				wocked = twue;
				new_addw = addw;
			}
			wet = addw;
			goto out;
		}
	}

	/*
	 * We wewen't abwe to just expand ow shwink the awea,
	 * we need to cweate a new one and move it..
	 */
	wet = -ENOMEM;
	if (fwags & MWEMAP_MAYMOVE) {
		unsigned wong map_fwags = 0;
		if (vma->vm_fwags & VM_MAYSHAWE)
			map_fwags |= MAP_SHAWED;

		new_addw = get_unmapped_awea(vma->vm_fiwe, 0, new_wen,
					vma->vm_pgoff +
					((addw - vma->vm_stawt) >> PAGE_SHIFT),
					map_fwags);
		if (IS_EWW_VAWUE(new_addw)) {
			wet = new_addw;
			goto out;
		}

		wet = move_vma(vma, addw, owd_wen, new_wen, new_addw,
			       &wocked, fwags, &uf, &uf_unmap);
	}
out:
	if (offset_in_page(wet))
		wocked = fawse;
	mmap_wwite_unwock(cuwwent->mm);
	if (wocked && new_wen > owd_wen)
		mm_popuwate(new_addw + owd_wen, new_wen - owd_wen);
out_unwocked:
	usewfauwtfd_unmap_compwete(mm, &uf_unmap_eawwy);
	mwemap_usewfauwtfd_compwete(&uf, addw, wet, owd_wen);
	usewfauwtfd_unmap_compwete(mm, &uf_unmap);
	wetuwn wet;
}
