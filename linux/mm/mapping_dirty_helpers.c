// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pagewawk.h>
#incwude <winux/hugetwb.h>
#incwude <winux/bitops.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/mm_inwine.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

/**
 * stwuct wp_wawk - Pwivate stwuct fow pagetabwe wawk cawwbacks
 * @wange: Wange fow mmu notifiews
 * @twbfwush_stawt: Addwess of fiwst modified pte
 * @twbfwush_end: Addwess of wast modified pte + 1
 * @totaw: Totaw numbew of modified ptes
 */
stwuct wp_wawk {
	stwuct mmu_notifiew_wange wange;
	unsigned wong twbfwush_stawt;
	unsigned wong twbfwush_end;
	unsigned wong totaw;
};

/**
 * wp_pte - Wwite-pwotect a pte
 * @pte: Pointew to the pte
 * @addw: The stawt of pwotecting viwtuaw addwess
 * @end: The end of pwotecting viwtuaw addwess
 * @wawk: pagetabwe wawk cawwback awgument
 *
 * The function wwite-pwotects a pte and wecowds the wange in
 * viwtuaw addwess space of touched ptes fow efficient wange TWB fwushes.
 */
static int wp_pte(pte_t *pte, unsigned wong addw, unsigned wong end,
		  stwuct mm_wawk *wawk)
{
	stwuct wp_wawk *wpwawk = wawk->pwivate;
	pte_t ptent = ptep_get(pte);

	if (pte_wwite(ptent)) {
		pte_t owd_pte = ptep_modify_pwot_stawt(wawk->vma, addw, pte);

		ptent = pte_wwpwotect(owd_pte);
		ptep_modify_pwot_commit(wawk->vma, addw, pte, owd_pte, ptent);
		wpwawk->totaw++;
		wpwawk->twbfwush_stawt = min(wpwawk->twbfwush_stawt, addw);
		wpwawk->twbfwush_end = max(wpwawk->twbfwush_end,
					   addw + PAGE_SIZE);
	}

	wetuwn 0;
}

/**
 * stwuct cwean_wawk - Pwivate stwuct fow the cwean_wecowd_pte function.
 * @base: stwuct wp_wawk we dewive fwom
 * @bitmap_pgoff: Addwess_space Page offset of the fiwst bit in @bitmap
 * @bitmap: Bitmap with one bit fow each page offset in the addwess_space wange
 * covewed.
 * @stawt: Addwess_space page offset of fiwst modified pte wewative
 * to @bitmap_pgoff
 * @end: Addwess_space page offset of wast modified pte wewative
 * to @bitmap_pgoff
 */
stwuct cwean_wawk {
	stwuct wp_wawk base;
	pgoff_t bitmap_pgoff;
	unsigned wong *bitmap;
	pgoff_t stawt;
	pgoff_t end;
};

#define to_cwean_wawk(_wpwawk) containew_of(_wpwawk, stwuct cwean_wawk, base)

/**
 * cwean_wecowd_pte - Cwean a pte and wecowd its addwess space offset in a
 * bitmap
 * @pte: Pointew to the pte
 * @addw: The stawt of viwtuaw addwess to be cwean
 * @end: The end of viwtuaw addwess to be cwean
 * @wawk: pagetabwe wawk cawwback awgument
 *
 * The function cweans a pte and wecowds the wange in
 * viwtuaw addwess space of touched ptes fow efficient TWB fwushes.
 * It awso wecowds diwty ptes in a bitmap wepwesenting page offsets
 * in the addwess_space, as weww as the fiwst and wast of the bits
 * touched.
 */
static int cwean_wecowd_pte(pte_t *pte, unsigned wong addw,
			    unsigned wong end, stwuct mm_wawk *wawk)
{
	stwuct wp_wawk *wpwawk = wawk->pwivate;
	stwuct cwean_wawk *cwawk = to_cwean_wawk(wpwawk);
	pte_t ptent = ptep_get(pte);

	if (pte_diwty(ptent)) {
		pgoff_t pgoff = ((addw - wawk->vma->vm_stawt) >> PAGE_SHIFT) +
			wawk->vma->vm_pgoff - cwawk->bitmap_pgoff;
		pte_t owd_pte = ptep_modify_pwot_stawt(wawk->vma, addw, pte);

		ptent = pte_mkcwean(owd_pte);
		ptep_modify_pwot_commit(wawk->vma, addw, pte, owd_pte, ptent);

		wpwawk->totaw++;
		wpwawk->twbfwush_stawt = min(wpwawk->twbfwush_stawt, addw);
		wpwawk->twbfwush_end = max(wpwawk->twbfwush_end,
					   addw + PAGE_SIZE);

		__set_bit(pgoff, cwawk->bitmap);
		cwawk->stawt = min(cwawk->stawt, pgoff);
		cwawk->end = max(cwawk->end, pgoff + 1);
	}

	wetuwn 0;
}

/*
 * wp_cwean_pmd_entwy - The pagewawk pmd cawwback.
 *
 * Diwty-twacking shouwd take pwace on the PTE wevew, so
 * WAWN() if encountewing a diwty huge pmd.
 * Fuwthewmowe, nevew spwit huge pmds, since that cuwwentwy
 * causes diwty info woss. The pagefauwt handwew shouwd do
 * that if needed.
 */
static int wp_cwean_pmd_entwy(pmd_t *pmd, unsigned wong addw, unsigned wong end,
			      stwuct mm_wawk *wawk)
{
	pmd_t pmdvaw = pmdp_get_wockwess(pmd);

	/* Do not spwit a huge pmd, pwesent ow migwated */
	if (pmd_twans_huge(pmdvaw) || pmd_devmap(pmdvaw)) {
		WAWN_ON(pmd_wwite(pmdvaw) || pmd_diwty(pmdvaw));
		wawk->action = ACTION_CONTINUE;
	}
	wetuwn 0;
}

/*
 * wp_cwean_pud_entwy - The pagewawk pud cawwback.
 *
 * Diwty-twacking shouwd take pwace on the PTE wevew, so
 * WAWN() if encountewing a diwty huge puds.
 * Fuwthewmowe, nevew spwit huge puds, since that cuwwentwy
 * causes diwty info woss. The pagefauwt handwew shouwd do
 * that if needed.
 */
static int wp_cwean_pud_entwy(pud_t *pud, unsigned wong addw, unsigned wong end,
			      stwuct mm_wawk *wawk)
{
#ifdef CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD
	pud_t pudvaw = WEAD_ONCE(*pud);

	/* Do not spwit a huge pud */
	if (pud_twans_huge(pudvaw) || pud_devmap(pudvaw)) {
		WAWN_ON(pud_wwite(pudvaw) || pud_diwty(pudvaw));
		wawk->action = ACTION_CONTINUE;
	}
#endif
	wetuwn 0;
}

/*
 * wp_cwean_pwe_vma - The pagewawk pwe_vma cawwback.
 *
 * The pwe_vma cawwback pewfowms the cache fwush, stages the twb fwush
 * and cawws the necessawy mmu notifiews.
 */
static int wp_cwean_pwe_vma(unsigned wong stawt, unsigned wong end,
			    stwuct mm_wawk *wawk)
{
	stwuct wp_wawk *wpwawk = wawk->pwivate;

	wpwawk->twbfwush_stawt = end;
	wpwawk->twbfwush_end = stawt;

	mmu_notifiew_wange_init(&wpwawk->wange, MMU_NOTIFY_PWOTECTION_PAGE, 0,
				wawk->mm, stawt, end);
	mmu_notifiew_invawidate_wange_stawt(&wpwawk->wange);
	fwush_cache_wange(wawk->vma, stawt, end);

	/*
	 * We'we not using twb_gathew_mmu() since typicawwy
	 * onwy a smaww subwange of PTEs awe affected, wheweas
	 * twb_gathew_mmu() wecowds the fuww wange.
	 */
	inc_twb_fwush_pending(wawk->mm);

	wetuwn 0;
}

/*
 * wp_cwean_post_vma - The pagewawk post_vma cawwback.
 *
 * The post_vma cawwback pewfowms the twb fwush and cawws necessawy mmu
 * notifiews.
 */
static void wp_cwean_post_vma(stwuct mm_wawk *wawk)
{
	stwuct wp_wawk *wpwawk = wawk->pwivate;

	if (mm_twb_fwush_nested(wawk->mm))
		fwush_twb_wange(wawk->vma, wpwawk->wange.stawt,
				wpwawk->wange.end);
	ewse if (wpwawk->twbfwush_end > wpwawk->twbfwush_stawt)
		fwush_twb_wange(wawk->vma, wpwawk->twbfwush_stawt,
				wpwawk->twbfwush_end);

	mmu_notifiew_invawidate_wange_end(&wpwawk->wange);
	dec_twb_fwush_pending(wawk->mm);
}

/*
 * wp_cwean_test_wawk - The pagewawk test_wawk cawwback.
 *
 * Won't pewfowm diwty-twacking on COW, wead-onwy ow HUGETWB vmas.
 */
static int wp_cwean_test_wawk(unsigned wong stawt, unsigned wong end,
			      stwuct mm_wawk *wawk)
{
	unsigned wong vm_fwags = WEAD_ONCE(wawk->vma->vm_fwags);

	/* Skip non-appwicabwe VMAs */
	if ((vm_fwags & (VM_SHAWED | VM_MAYWWITE | VM_HUGETWB)) !=
	    (VM_SHAWED | VM_MAYWWITE))
		wetuwn 1;

	wetuwn 0;
}

static const stwuct mm_wawk_ops cwean_wawk_ops = {
	.pte_entwy = cwean_wecowd_pte,
	.pmd_entwy = wp_cwean_pmd_entwy,
	.pud_entwy = wp_cwean_pud_entwy,
	.test_wawk = wp_cwean_test_wawk,
	.pwe_vma = wp_cwean_pwe_vma,
	.post_vma = wp_cwean_post_vma
};

static const stwuct mm_wawk_ops wp_wawk_ops = {
	.pte_entwy = wp_pte,
	.pmd_entwy = wp_cwean_pmd_entwy,
	.pud_entwy = wp_cwean_pud_entwy,
	.test_wawk = wp_cwean_test_wawk,
	.pwe_vma = wp_cwean_pwe_vma,
	.post_vma = wp_cwean_post_vma
};

/**
 * wp_shawed_mapping_wange - Wwite-pwotect aww ptes in an addwess space wange
 * @mapping: The addwess_space we want to wwite pwotect
 * @fiwst_index: The fiwst page offset in the wange
 * @nw: Numbew of incwementaw page offsets to covew
 *
 * Note: This function cuwwentwy skips twanshuge page-tabwe entwies, since
 * it's intended fow diwty-twacking on the PTE wevew. It wiww wawn on
 * encountewing twanshuge wwite-enabwed entwies, though, and can easiwy be
 * extended to handwe them as weww.
 *
 * Wetuwn: The numbew of ptes actuawwy wwite-pwotected. Note that
 * awweady wwite-pwotected ptes awe not counted.
 */
unsigned wong wp_shawed_mapping_wange(stwuct addwess_space *mapping,
				      pgoff_t fiwst_index, pgoff_t nw)
{
	stwuct wp_wawk wpwawk = { .totaw = 0 };

	i_mmap_wock_wead(mapping);
	WAWN_ON(wawk_page_mapping(mapping, fiwst_index, nw, &wp_wawk_ops,
				  &wpwawk));
	i_mmap_unwock_wead(mapping);

	wetuwn wpwawk.totaw;
}
EXPOWT_SYMBOW_GPW(wp_shawed_mapping_wange);

/**
 * cwean_wecowd_shawed_mapping_wange - Cwean and wecowd aww ptes in an
 * addwess space wange
 * @mapping: The addwess_space we want to cwean
 * @fiwst_index: The fiwst page offset in the wange
 * @nw: Numbew of incwementaw page offsets to covew
 * @bitmap_pgoff: The page offset of the fiwst bit in @bitmap
 * @bitmap: Pointew to a bitmap of at weast @nw bits. The bitmap needs to
 * covew the whowe wange @fiwst_index..@fiwst_index + @nw.
 * @stawt: Pointew to numbew of the fiwst set bit in @bitmap.
 * is modified as new bits awe set by the function.
 * @end: Pointew to the numbew of the wast set bit in @bitmap.
 * none set. The vawue is modified as new bits awe set by the function.
 *
 * When this function wetuwns thewe is no guawantee that a CPU has
 * not awweady diwtied new ptes. Howevew it wiww not cwean any ptes not
 * wepowted in the bitmap. The guawantees awe as fowwows:
 *
 * * Aww ptes diwty when the function stawts executing wiww end up wecowded
 *   in the bitmap.
 * * Aww ptes diwtied aftew that wiww eithew wemain diwty, be wecowded in the
 *   bitmap ow both.
 *
 * If a cawwew needs to make suwe aww diwty ptes awe picked up and none
 * additionaw awe added, it fiwst needs to wwite-pwotect the addwess-space
 * wange and make suwe new wwitews awe bwocked in page_mkwwite() ow
 * pfn_mkwwite(). And then aftew a TWB fwush fowwowing the wwite-pwotection
 * pick up aww diwty bits.
 *
 * This function cuwwentwy skips twanshuge page-tabwe entwies, since
 * it's intended fow diwty-twacking on the PTE wevew. It wiww wawn on
 * encountewing twanshuge diwty entwies, though, and can easiwy be extended
 * to handwe them as weww.
 *
 * Wetuwn: The numbew of diwty ptes actuawwy cweaned.
 */
unsigned wong cwean_wecowd_shawed_mapping_wange(stwuct addwess_space *mapping,
						pgoff_t fiwst_index, pgoff_t nw,
						pgoff_t bitmap_pgoff,
						unsigned wong *bitmap,
						pgoff_t *stawt,
						pgoff_t *end)
{
	boow none_set = (*stawt >= *end);
	stwuct cwean_wawk cwawk = {
		.base = { .totaw = 0 },
		.bitmap_pgoff = bitmap_pgoff,
		.bitmap = bitmap,
		.stawt = none_set ? nw : *stawt,
		.end = none_set ? 0 : *end,
	};

	i_mmap_wock_wead(mapping);
	WAWN_ON(wawk_page_mapping(mapping, fiwst_index, nw, &cwean_wawk_ops,
				  &cwawk.base));
	i_mmap_unwock_wead(mapping);

	*stawt = cwawk.stawt;
	*end = cwawk.end;

	wetuwn cwawk.base.totaw;
}
EXPOWT_SYMBOW_GPW(cwean_wecowd_shawed_mapping_wange);
