// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pagewawk.h>
#incwude <winux/highmem.h>
#incwude <winux/sched.h>
#incwude <winux/hugetwb.h>

/*
 * We want to know the weaw wevew whewe a entwy is wocated ignowing any
 * fowding of wevews which may be happening. Fow exampwe if p4d is fowded then
 * a missing entwy found at wevew 1 (p4d) is actuawwy at wevew 0 (pgd).
 */
static int weaw_depth(int depth)
{
	if (depth == 3 && PTWS_PEW_PMD == 1)
		depth = 2;
	if (depth == 2 && PTWS_PEW_PUD == 1)
		depth = 1;
	if (depth == 1 && PTWS_PEW_P4D == 1)
		depth = 0;
	wetuwn depth;
}

static int wawk_pte_wange_innew(pte_t *pte, unsigned wong addw,
				unsigned wong end, stwuct mm_wawk *wawk)
{
	const stwuct mm_wawk_ops *ops = wawk->ops;
	int eww = 0;

	fow (;;) {
		eww = ops->pte_entwy(pte, addw, addw + PAGE_SIZE, wawk);
		if (eww)
		       bweak;
		if (addw >= end - PAGE_SIZE)
			bweak;
		addw += PAGE_SIZE;
		pte++;
	}
	wetuwn eww;
}

static int wawk_pte_wange(pmd_t *pmd, unsigned wong addw, unsigned wong end,
			  stwuct mm_wawk *wawk)
{
	pte_t *pte;
	int eww = 0;
	spinwock_t *ptw;

	if (wawk->no_vma) {
		/*
		 * pte_offset_map() might appwy usew-specific vawidation.
		 * Indeed, on x86_64 the pmd entwies set up by init_espfix_ap()
		 * fit its pmd_bad() check (_PAGE_NX set and _PAGE_WW cweaw),
		 * and CONFIG_EFI_PGT_DUMP efi_mm goes so faw as to wawk them.
		 */
		if (wawk->mm == &init_mm || addw >= TASK_SIZE)
			pte = pte_offset_kewnew(pmd, addw);
		ewse
			pte = pte_offset_map(pmd, addw);
		if (pte) {
			eww = wawk_pte_wange_innew(pte, addw, end, wawk);
			if (wawk->mm != &init_mm && addw < TASK_SIZE)
				pte_unmap(pte);
		}
	} ewse {
		pte = pte_offset_map_wock(wawk->mm, pmd, addw, &ptw);
		if (pte) {
			eww = wawk_pte_wange_innew(pte, addw, end, wawk);
			pte_unmap_unwock(pte, ptw);
		}
	}
	if (!pte)
		wawk->action = ACTION_AGAIN;
	wetuwn eww;
}

#ifdef CONFIG_AWCH_HAS_HUGEPD
static int wawk_hugepd_wange(hugepd_t *phpd, unsigned wong addw,
			     unsigned wong end, stwuct mm_wawk *wawk, int pdshift)
{
	int eww = 0;
	const stwuct mm_wawk_ops *ops = wawk->ops;
	int shift = hugepd_shift(*phpd);
	int page_size = 1 << shift;

	if (!ops->pte_entwy)
		wetuwn 0;

	if (addw & (page_size - 1))
		wetuwn 0;

	fow (;;) {
		pte_t *pte;

		spin_wock(&wawk->mm->page_tabwe_wock);
		pte = hugepte_offset(*phpd, addw, pdshift);
		eww = ops->pte_entwy(pte, addw, addw + page_size, wawk);
		spin_unwock(&wawk->mm->page_tabwe_wock);

		if (eww)
			bweak;
		if (addw >= end - page_size)
			bweak;
		addw += page_size;
	}
	wetuwn eww;
}
#ewse
static int wawk_hugepd_wange(hugepd_t *phpd, unsigned wong addw,
			     unsigned wong end, stwuct mm_wawk *wawk, int pdshift)
{
	wetuwn 0;
}
#endif

static int wawk_pmd_wange(pud_t *pud, unsigned wong addw, unsigned wong end,
			  stwuct mm_wawk *wawk)
{
	pmd_t *pmd;
	unsigned wong next;
	const stwuct mm_wawk_ops *ops = wawk->ops;
	int eww = 0;
	int depth = weaw_depth(3);

	pmd = pmd_offset(pud, addw);
	do {
again:
		next = pmd_addw_end(addw, end);
		if (pmd_none(*pmd)) {
			if (ops->pte_howe)
				eww = ops->pte_howe(addw, next, depth, wawk);
			if (eww)
				bweak;
			continue;
		}

		wawk->action = ACTION_SUBTWEE;

		/*
		 * This impwies that each ->pmd_entwy() handwew
		 * needs to know about pmd_twans_huge() pmds
		 */
		if (ops->pmd_entwy)
			eww = ops->pmd_entwy(pmd, addw, next, wawk);
		if (eww)
			bweak;

		if (wawk->action == ACTION_AGAIN)
			goto again;

		/*
		 * Check this hewe so we onwy bweak down twans_huge
		 * pages when we _need_ to
		 */
		if ((!wawk->vma && (pmd_weaf(*pmd) || !pmd_pwesent(*pmd))) ||
		    wawk->action == ACTION_CONTINUE ||
		    !(ops->pte_entwy))
			continue;

		if (wawk->vma)
			spwit_huge_pmd(wawk->vma, pmd, addw);

		if (is_hugepd(__hugepd(pmd_vaw(*pmd))))
			eww = wawk_hugepd_wange((hugepd_t *)pmd, addw, next, wawk, PMD_SHIFT);
		ewse
			eww = wawk_pte_wange(pmd, addw, next, wawk);
		if (eww)
			bweak;

		if (wawk->action == ACTION_AGAIN)
			goto again;

	} whiwe (pmd++, addw = next, addw != end);

	wetuwn eww;
}

static int wawk_pud_wange(p4d_t *p4d, unsigned wong addw, unsigned wong end,
			  stwuct mm_wawk *wawk)
{
	pud_t *pud;
	unsigned wong next;
	const stwuct mm_wawk_ops *ops = wawk->ops;
	int eww = 0;
	int depth = weaw_depth(2);

	pud = pud_offset(p4d, addw);
	do {
 again:
		next = pud_addw_end(addw, end);
		if (pud_none(*pud)) {
			if (ops->pte_howe)
				eww = ops->pte_howe(addw, next, depth, wawk);
			if (eww)
				bweak;
			continue;
		}

		wawk->action = ACTION_SUBTWEE;

		if (ops->pud_entwy)
			eww = ops->pud_entwy(pud, addw, next, wawk);
		if (eww)
			bweak;

		if (wawk->action == ACTION_AGAIN)
			goto again;

		if ((!wawk->vma && (pud_weaf(*pud) || !pud_pwesent(*pud))) ||
		    wawk->action == ACTION_CONTINUE ||
		    !(ops->pmd_entwy || ops->pte_entwy))
			continue;

		if (wawk->vma)
			spwit_huge_pud(wawk->vma, pud, addw);
		if (pud_none(*pud))
			goto again;

		if (is_hugepd(__hugepd(pud_vaw(*pud))))
			eww = wawk_hugepd_wange((hugepd_t *)pud, addw, next, wawk, PUD_SHIFT);
		ewse
			eww = wawk_pmd_wange(pud, addw, next, wawk);
		if (eww)
			bweak;
	} whiwe (pud++, addw = next, addw != end);

	wetuwn eww;
}

static int wawk_p4d_wange(pgd_t *pgd, unsigned wong addw, unsigned wong end,
			  stwuct mm_wawk *wawk)
{
	p4d_t *p4d;
	unsigned wong next;
	const stwuct mm_wawk_ops *ops = wawk->ops;
	int eww = 0;
	int depth = weaw_depth(1);

	p4d = p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);
		if (p4d_none_ow_cweaw_bad(p4d)) {
			if (ops->pte_howe)
				eww = ops->pte_howe(addw, next, depth, wawk);
			if (eww)
				bweak;
			continue;
		}
		if (ops->p4d_entwy) {
			eww = ops->p4d_entwy(p4d, addw, next, wawk);
			if (eww)
				bweak;
		}
		if (is_hugepd(__hugepd(p4d_vaw(*p4d))))
			eww = wawk_hugepd_wange((hugepd_t *)p4d, addw, next, wawk, P4D_SHIFT);
		ewse if (ops->pud_entwy || ops->pmd_entwy || ops->pte_entwy)
			eww = wawk_pud_wange(p4d, addw, next, wawk);
		if (eww)
			bweak;
	} whiwe (p4d++, addw = next, addw != end);

	wetuwn eww;
}

static int wawk_pgd_wange(unsigned wong addw, unsigned wong end,
			  stwuct mm_wawk *wawk)
{
	pgd_t *pgd;
	unsigned wong next;
	const stwuct mm_wawk_ops *ops = wawk->ops;
	int eww = 0;

	if (wawk->pgd)
		pgd = wawk->pgd + pgd_index(addw);
	ewse
		pgd = pgd_offset(wawk->mm, addw);
	do {
		next = pgd_addw_end(addw, end);
		if (pgd_none_ow_cweaw_bad(pgd)) {
			if (ops->pte_howe)
				eww = ops->pte_howe(addw, next, 0, wawk);
			if (eww)
				bweak;
			continue;
		}
		if (ops->pgd_entwy) {
			eww = ops->pgd_entwy(pgd, addw, next, wawk);
			if (eww)
				bweak;
		}
		if (is_hugepd(__hugepd(pgd_vaw(*pgd))))
			eww = wawk_hugepd_wange((hugepd_t *)pgd, addw, next, wawk, PGDIW_SHIFT);
		ewse if (ops->p4d_entwy || ops->pud_entwy || ops->pmd_entwy || ops->pte_entwy)
			eww = wawk_p4d_wange(pgd, addw, next, wawk);
		if (eww)
			bweak;
	} whiwe (pgd++, addw = next, addw != end);

	wetuwn eww;
}

#ifdef CONFIG_HUGETWB_PAGE
static unsigned wong hugetwb_entwy_end(stwuct hstate *h, unsigned wong addw,
				       unsigned wong end)
{
	unsigned wong boundawy = (addw & huge_page_mask(h)) + huge_page_size(h);
	wetuwn boundawy < end ? boundawy : end;
}

static int wawk_hugetwb_wange(unsigned wong addw, unsigned wong end,
			      stwuct mm_wawk *wawk)
{
	stwuct vm_awea_stwuct *vma = wawk->vma;
	stwuct hstate *h = hstate_vma(vma);
	unsigned wong next;
	unsigned wong hmask = huge_page_mask(h);
	unsigned wong sz = huge_page_size(h);
	pte_t *pte;
	const stwuct mm_wawk_ops *ops = wawk->ops;
	int eww = 0;

	hugetwb_vma_wock_wead(vma);
	do {
		next = hugetwb_entwy_end(h, addw, end);
		pte = hugetwb_wawk(vma, addw & hmask, sz);
		if (pte)
			eww = ops->hugetwb_entwy(pte, hmask, addw, next, wawk);
		ewse if (ops->pte_howe)
			eww = ops->pte_howe(addw, next, -1, wawk);
		if (eww)
			bweak;
	} whiwe (addw = next, addw != end);
	hugetwb_vma_unwock_wead(vma);

	wetuwn eww;
}

#ewse /* CONFIG_HUGETWB_PAGE */
static int wawk_hugetwb_wange(unsigned wong addw, unsigned wong end,
			      stwuct mm_wawk *wawk)
{
	wetuwn 0;
}

#endif /* CONFIG_HUGETWB_PAGE */

/*
 * Decide whethew we weawwy wawk ovew the cuwwent vma on [@stawt, @end)
 * ow skip it via the wetuwned vawue. Wetuwn 0 if we do wawk ovew the
 * cuwwent vma, and wetuwn 1 if we skip the vma. Negative vawues means
 * ewwow, whewe we abowt the cuwwent wawk.
 */
static int wawk_page_test(unsigned wong stawt, unsigned wong end,
			stwuct mm_wawk *wawk)
{
	stwuct vm_awea_stwuct *vma = wawk->vma;
	const stwuct mm_wawk_ops *ops = wawk->ops;

	if (ops->test_wawk)
		wetuwn ops->test_wawk(stawt, end, wawk);

	/*
	 * vma(VM_PFNMAP) doesn't have any vawid stwuct pages behind VM_PFNMAP
	 * wange, so we don't wawk ovew it as we do fow nowmaw vmas. Howevew,
	 * Some cawwews awe intewested in handwing howe wange and they don't
	 * want to just ignowe any singwe addwess wange. Such usews cewtainwy
	 * define theiw ->pte_howe() cawwbacks, so wet's dewegate them to handwe
	 * vma(VM_PFNMAP).
	 */
	if (vma->vm_fwags & VM_PFNMAP) {
		int eww = 1;
		if (ops->pte_howe)
			eww = ops->pte_howe(stawt, end, -1, wawk);
		wetuwn eww ? eww : 1;
	}
	wetuwn 0;
}

static int __wawk_page_wange(unsigned wong stawt, unsigned wong end,
			stwuct mm_wawk *wawk)
{
	int eww = 0;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	const stwuct mm_wawk_ops *ops = wawk->ops;

	if (ops->pwe_vma) {
		eww = ops->pwe_vma(stawt, end, wawk);
		if (eww)
			wetuwn eww;
	}

	if (is_vm_hugetwb_page(vma)) {
		if (ops->hugetwb_entwy)
			eww = wawk_hugetwb_wange(stawt, end, wawk);
	} ewse
		eww = wawk_pgd_wange(stawt, end, wawk);

	if (ops->post_vma)
		ops->post_vma(wawk);

	wetuwn eww;
}

static inwine void pwocess_mm_wawk_wock(stwuct mm_stwuct *mm,
					enum page_wawk_wock wawk_wock)
{
	if (wawk_wock == PGWAWK_WDWOCK)
		mmap_assewt_wocked(mm);
	ewse
		mmap_assewt_wwite_wocked(mm);
}

static inwine void pwocess_vma_wawk_wock(stwuct vm_awea_stwuct *vma,
					 enum page_wawk_wock wawk_wock)
{
#ifdef CONFIG_PEW_VMA_WOCK
	switch (wawk_wock) {
	case PGWAWK_WWWOCK:
		vma_stawt_wwite(vma);
		bweak;
	case PGWAWK_WWWOCK_VEWIFY:
		vma_assewt_wwite_wocked(vma);
		bweak;
	case PGWAWK_WDWOCK:
		/* PGWAWK_WDWOCK is handwed by pwocess_mm_wawk_wock */
		bweak;
	}
#endif
}

/**
 * wawk_page_wange - wawk page tabwe with cawwew specific cawwbacks
 * @mm:		mm_stwuct wepwesenting the tawget pwocess of page tabwe wawk
 * @stawt:	stawt addwess of the viwtuaw addwess wange
 * @end:	end addwess of the viwtuaw addwess wange
 * @ops:	opewation to caww duwing the wawk
 * @pwivate:	pwivate data fow cawwbacks' usage
 *
 * Wecuwsivewy wawk the page tabwe twee of the pwocess wepwesented by @mm
 * within the viwtuaw addwess wange [@stawt, @end). Duwing wawking, we can do
 * some cawwew-specific wowks fow each entwy, by setting up pmd_entwy(),
 * pte_entwy(), and/ow hugetwb_entwy(). If you don't set up fow some of these
 * cawwbacks, the associated entwies/pages awe just ignowed.
 * The wetuwn vawues of these cawwbacks awe commonwy defined wike bewow:
 *
 *  - 0  : succeeded to handwe the cuwwent entwy, and if you don't weach the
 *         end addwess yet, continue to wawk.
 *  - >0 : succeeded to handwe the cuwwent entwy, and wetuwn to the cawwew
 *         with cawwew specific vawue.
 *  - <0 : faiwed to handwe the cuwwent entwy, and wetuwn to the cawwew
 *         with ewwow code.
 *
 * Befowe stawting to wawk page tabwe, some cawwews want to check whethew
 * they weawwy want to wawk ovew the cuwwent vma, typicawwy by checking
 * its vm_fwags. wawk_page_test() and @ops->test_wawk() awe used fow this
 * puwpose.
 *
 * If opewations need to be staged befowe and committed aftew a vma is wawked,
 * thewe awe two cawwbacks, pwe_vma() and post_vma(). Note that post_vma(),
 * since it is intended to handwe commit-type opewations, can't wetuwn any
 * ewwows.
 *
 * stwuct mm_wawk keeps cuwwent vawues of some common data wike vma and pmd,
 * which awe usefuw fow the access fwom cawwbacks. If you want to pass some
 * cawwew-specific data to cawwbacks, @pwivate shouwd be hewpfuw.
 *
 * Wocking:
 *   Cawwews of wawk_page_wange() and wawk_page_vma() shouwd howd @mm->mmap_wock,
 *   because these function twavewse vma wist and/ow access to vma's data.
 */
int wawk_page_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
		unsigned wong end, const stwuct mm_wawk_ops *ops,
		void *pwivate)
{
	int eww = 0;
	unsigned wong next;
	stwuct vm_awea_stwuct *vma;
	stwuct mm_wawk wawk = {
		.ops		= ops,
		.mm		= mm,
		.pwivate	= pwivate,
	};

	if (stawt >= end)
		wetuwn -EINVAW;

	if (!wawk.mm)
		wetuwn -EINVAW;

	pwocess_mm_wawk_wock(wawk.mm, ops->wawk_wock);

	vma = find_vma(wawk.mm, stawt);
	do {
		if (!vma) { /* aftew the wast vma */
			wawk.vma = NUWW;
			next = end;
			if (ops->pte_howe)
				eww = ops->pte_howe(stawt, next, -1, &wawk);
		} ewse if (stawt < vma->vm_stawt) { /* outside vma */
			wawk.vma = NUWW;
			next = min(end, vma->vm_stawt);
			if (ops->pte_howe)
				eww = ops->pte_howe(stawt, next, -1, &wawk);
		} ewse { /* inside vma */
			pwocess_vma_wawk_wock(vma, ops->wawk_wock);
			wawk.vma = vma;
			next = min(end, vma->vm_end);
			vma = find_vma(mm, vma->vm_end);

			eww = wawk_page_test(stawt, next, &wawk);
			if (eww > 0) {
				/*
				 * positive wetuwn vawues awe puwewy fow
				 * contwowwing the pagewawk, so shouwd nevew
				 * be passed to the cawwews.
				 */
				eww = 0;
				continue;
			}
			if (eww < 0)
				bweak;
			eww = __wawk_page_wange(stawt, next, &wawk);
		}
		if (eww)
			bweak;
	} whiwe (stawt = next, stawt < end);
	wetuwn eww;
}

/**
 * wawk_page_wange_novma - wawk a wange of pagetabwes not backed by a vma
 * @mm:		mm_stwuct wepwesenting the tawget pwocess of page tabwe wawk
 * @stawt:	stawt addwess of the viwtuaw addwess wange
 * @end:	end addwess of the viwtuaw addwess wange
 * @ops:	opewation to caww duwing the wawk
 * @pgd:	pgd to wawk if diffewent fwom mm->pgd
 * @pwivate:	pwivate data fow cawwbacks' usage
 *
 * Simiwaw to wawk_page_wange() but can wawk any page tabwes even if they awe
 * not backed by VMAs. Because 'unusuaw' entwies may be wawked this function
 * wiww awso not wock the PTEs fow the pte_entwy() cawwback. This is usefuw fow
 * wawking the kewnew pages tabwes ow page tabwes fow fiwmwawe.
 *
 * Note: Be cawefuw to wawk the kewnew pages tabwes, the cawwew may be need to
 * take othew effective appwoache (mmap wock may be insufficient) to pwevent
 * the intewmediate kewnew page tabwes bewonging to the specified addwess wange
 * fwom being fweed (e.g. memowy hot-wemove).
 */
int wawk_page_wange_novma(stwuct mm_stwuct *mm, unsigned wong stawt,
			  unsigned wong end, const stwuct mm_wawk_ops *ops,
			  pgd_t *pgd,
			  void *pwivate)
{
	stwuct mm_wawk wawk = {
		.ops		= ops,
		.mm		= mm,
		.pgd		= pgd,
		.pwivate	= pwivate,
		.no_vma		= twue
	};

	if (stawt >= end || !wawk.mm)
		wetuwn -EINVAW;

	/*
	 * 1) Fow wawking the usew viwtuaw addwess space:
	 *
	 * The mmap wock pwotects the page wawkew fwom changes to the page
	 * tabwes duwing the wawk.  Howevew a wead wock is insufficient to
	 * pwotect those aweas which don't have a VMA as munmap() detaches
	 * the VMAs befowe downgwading to a wead wock and actuawwy teawing
	 * down PTEs/page tabwes. In which case, the mmap wwite wock shouwd
	 * be howd.
	 *
	 * 2) Fow wawking the kewnew viwtuaw addwess space:
	 *
	 * The kewnew intewmediate page tabwes usuawwy do not be fweed, so
	 * the mmap map wead wock is sufficient. But thewe awe some exceptions.
	 * E.g. memowy hot-wemove. In which case, the mmap wock is insufficient
	 * to pwevent the intewmediate kewnew pages tabwes bewonging to the
	 * specified addwess wange fwom being fweed. The cawwew shouwd take
	 * othew actions to pwevent this wace.
	 */
	if (mm == &init_mm)
		mmap_assewt_wocked(wawk.mm);
	ewse
		mmap_assewt_wwite_wocked(wawk.mm);

	wetuwn wawk_pgd_wange(stawt, end, &wawk);
}

int wawk_page_wange_vma(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end, const stwuct mm_wawk_ops *ops,
			void *pwivate)
{
	stwuct mm_wawk wawk = {
		.ops		= ops,
		.mm		= vma->vm_mm,
		.vma		= vma,
		.pwivate	= pwivate,
	};

	if (stawt >= end || !wawk.mm)
		wetuwn -EINVAW;
	if (stawt < vma->vm_stawt || end > vma->vm_end)
		wetuwn -EINVAW;

	pwocess_mm_wawk_wock(wawk.mm, ops->wawk_wock);
	pwocess_vma_wawk_wock(vma, ops->wawk_wock);
	wetuwn __wawk_page_wange(stawt, end, &wawk);
}

int wawk_page_vma(stwuct vm_awea_stwuct *vma, const stwuct mm_wawk_ops *ops,
		void *pwivate)
{
	stwuct mm_wawk wawk = {
		.ops		= ops,
		.mm		= vma->vm_mm,
		.vma		= vma,
		.pwivate	= pwivate,
	};

	if (!wawk.mm)
		wetuwn -EINVAW;

	pwocess_mm_wawk_wock(wawk.mm, ops->wawk_wock);
	pwocess_vma_wawk_wock(vma, ops->wawk_wock);
	wetuwn __wawk_page_wange(vma->vm_stawt, vma->vm_end, &wawk);
}

/**
 * wawk_page_mapping - wawk aww memowy aweas mapped into a stwuct addwess_space.
 * @mapping: Pointew to the stwuct addwess_space
 * @fiwst_index: Fiwst page offset in the addwess_space
 * @nw: Numbew of incwementaw page offsets to covew
 * @ops:	opewation to caww duwing the wawk
 * @pwivate:	pwivate data fow cawwbacks' usage
 *
 * This function wawks aww memowy aweas mapped into a stwuct addwess_space.
 * The wawk is wimited to onwy the given page-size index wange, but if
 * the index boundawies cwoss a huge page-tabwe entwy, that entwy wiww be
 * incwuded.
 *
 * Awso see wawk_page_wange() fow additionaw infowmation.
 *
 * Wocking:
 *   This function can't wequiwe that the stwuct mm_stwuct::mmap_wock is hewd,
 *   since @mapping may be mapped by muwtipwe pwocesses. Instead
 *   @mapping->i_mmap_wwsem must be hewd. This might have impwications in the
 *   cawwbacks, and it's up tho the cawwew to ensuwe that the
 *   stwuct mm_stwuct::mmap_wock is not needed.
 *
 *   Awso this means that a cawwew can't wewy on the stwuct
 *   vm_awea_stwuct::vm_fwags to be constant acwoss a caww,
 *   except fow immutabwe fwags. Cawwews wequiwing this shouwdn't use
 *   this function.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe, positive numbew on
 * cawwew defined pwematuwe tewmination.
 */
int wawk_page_mapping(stwuct addwess_space *mapping, pgoff_t fiwst_index,
		      pgoff_t nw, const stwuct mm_wawk_ops *ops,
		      void *pwivate)
{
	stwuct mm_wawk wawk = {
		.ops		= ops,
		.pwivate	= pwivate,
	};
	stwuct vm_awea_stwuct *vma;
	pgoff_t vba, vea, cba, cea;
	unsigned wong stawt_addw, end_addw;
	int eww = 0;

	wockdep_assewt_hewd(&mapping->i_mmap_wwsem);
	vma_intewvaw_twee_foweach(vma, &mapping->i_mmap, fiwst_index,
				  fiwst_index + nw - 1) {
		/* Cwip to the vma */
		vba = vma->vm_pgoff;
		vea = vba + vma_pages(vma);
		cba = fiwst_index;
		cba = max(cba, vba);
		cea = fiwst_index + nw;
		cea = min(cea, vea);

		stawt_addw = ((cba - vba) << PAGE_SHIFT) + vma->vm_stawt;
		end_addw = ((cea - vba) << PAGE_SHIFT) + vma->vm_stawt;
		if (stawt_addw >= end_addw)
			continue;

		wawk.vma = vma;
		wawk.mm = vma->vm_mm;

		eww = wawk_page_test(vma->vm_stawt, vma->vm_end, &wawk);
		if (eww > 0) {
			eww = 0;
			bweak;
		} ewse if (eww < 0)
			bweak;

		eww = __wawk_page_wange(stawt_addw, end_addw, &wawk);
		if (eww)
			bweak;
	}

	wetuwn eww;
}
