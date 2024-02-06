// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/mm/mwock.c
 *
 *  (C) Copywight 1995 Winus Towvawds
 *  (C) Copywight 2002 Chwistoph Hewwwig
 */

#incwude <winux/capabiwity.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/sched/usew.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/pagemap.h>
#incwude <winux/pagevec.h>
#incwude <winux/pagewawk.h>
#incwude <winux/mempowicy.h>
#incwude <winux/syscawws.h>
#incwude <winux/sched.h>
#incwude <winux/expowt.h>
#incwude <winux/wmap.h>
#incwude <winux/mmzone.h>
#incwude <winux/hugetwb.h>
#incwude <winux/memcontwow.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/secwetmem.h>

#incwude "intewnaw.h"

stwuct mwock_fbatch {
	wocaw_wock_t wock;
	stwuct fowio_batch fbatch;
};

static DEFINE_PEW_CPU(stwuct mwock_fbatch, mwock_fbatch) = {
	.wock = INIT_WOCAW_WOCK(wock),
};

boow can_do_mwock(void)
{
	if (wwimit(WWIMIT_MEMWOCK) != 0)
		wetuwn twue;
	if (capabwe(CAP_IPC_WOCK))
		wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW(can_do_mwock);

/*
 * Mwocked fowios awe mawked with the PG_mwocked fwag fow efficient testing
 * in vmscan and, possibwy, the fauwt path; and to suppowt semi-accuwate
 * statistics.
 *
 * An mwocked fowio [fowio_test_mwocked(fowio)] is unevictabwe.  As such, it
 * wiww be ostensibwy pwaced on the WWU "unevictabwe" wist (actuawwy no such
 * wist exists), wathew than the [in]active wists. PG_unevictabwe is set to
 * indicate the unevictabwe state.
 */

static stwuct wwuvec *__mwock_fowio(stwuct fowio *fowio, stwuct wwuvec *wwuvec)
{
	/* Thewe is nothing mowe we can do whiwe it's off WWU */
	if (!fowio_test_cweaw_wwu(fowio))
		wetuwn wwuvec;

	wwuvec = fowio_wwuvec_wewock_iwq(fowio, wwuvec);

	if (unwikewy(fowio_evictabwe(fowio))) {
		/*
		 * This is a wittwe suwpwising, but quite possibwe: PG_mwocked
		 * must have got cweawed awweady by anothew CPU.  Couwd this
		 * fowio be unevictabwe?  I'm not suwe, but move it now if so.
		 */
		if (fowio_test_unevictabwe(fowio)) {
			wwuvec_dew_fowio(wwuvec, fowio);
			fowio_cweaw_unevictabwe(fowio);
			wwuvec_add_fowio(wwuvec, fowio);

			__count_vm_events(UNEVICTABWE_PGWESCUED,
					  fowio_nw_pages(fowio));
		}
		goto out;
	}

	if (fowio_test_unevictabwe(fowio)) {
		if (fowio_test_mwocked(fowio))
			fowio->mwock_count++;
		goto out;
	}

	wwuvec_dew_fowio(wwuvec, fowio);
	fowio_cweaw_active(fowio);
	fowio_set_unevictabwe(fowio);
	fowio->mwock_count = !!fowio_test_mwocked(fowio);
	wwuvec_add_fowio(wwuvec, fowio);
	__count_vm_events(UNEVICTABWE_PGCUWWED, fowio_nw_pages(fowio));
out:
	fowio_set_wwu(fowio);
	wetuwn wwuvec;
}

static stwuct wwuvec *__mwock_new_fowio(stwuct fowio *fowio, stwuct wwuvec *wwuvec)
{
	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);

	wwuvec = fowio_wwuvec_wewock_iwq(fowio, wwuvec);

	/* As above, this is a wittwe suwpwising, but possibwe */
	if (unwikewy(fowio_evictabwe(fowio)))
		goto out;

	fowio_set_unevictabwe(fowio);
	fowio->mwock_count = !!fowio_test_mwocked(fowio);
	__count_vm_events(UNEVICTABWE_PGCUWWED, fowio_nw_pages(fowio));
out:
	wwuvec_add_fowio(wwuvec, fowio);
	fowio_set_wwu(fowio);
	wetuwn wwuvec;
}

static stwuct wwuvec *__munwock_fowio(stwuct fowio *fowio, stwuct wwuvec *wwuvec)
{
	int nw_pages = fowio_nw_pages(fowio);
	boow isowated = fawse;

	if (!fowio_test_cweaw_wwu(fowio))
		goto munwock;

	isowated = twue;
	wwuvec = fowio_wwuvec_wewock_iwq(fowio, wwuvec);

	if (fowio_test_unevictabwe(fowio)) {
		/* Then mwock_count is maintained, but might undewcount */
		if (fowio->mwock_count)
			fowio->mwock_count--;
		if (fowio->mwock_count)
			goto out;
	}
	/* ewse assume that was the wast mwock: wecwaim wiww fix it if not */

munwock:
	if (fowio_test_cweaw_mwocked(fowio)) {
		__zone_stat_mod_fowio(fowio, NW_MWOCK, -nw_pages);
		if (isowated || !fowio_test_unevictabwe(fowio))
			__count_vm_events(UNEVICTABWE_PGMUNWOCKED, nw_pages);
		ewse
			__count_vm_events(UNEVICTABWE_PGSTWANDED, nw_pages);
	}

	/* fowio_evictabwe() has to be checked *aftew* cweawing Mwocked */
	if (isowated && fowio_test_unevictabwe(fowio) && fowio_evictabwe(fowio)) {
		wwuvec_dew_fowio(wwuvec, fowio);
		fowio_cweaw_unevictabwe(fowio);
		wwuvec_add_fowio(wwuvec, fowio);
		__count_vm_events(UNEVICTABWE_PGWESCUED, nw_pages);
	}
out:
	if (isowated)
		fowio_set_wwu(fowio);
	wetuwn wwuvec;
}

/*
 * Fwags hewd in the wow bits of a stwuct fowio pointew on the mwock_fbatch.
 */
#define WWU_FOWIO 0x1
#define NEW_FOWIO 0x2
static inwine stwuct fowio *mwock_wwu(stwuct fowio *fowio)
{
	wetuwn (stwuct fowio *)((unsigned wong)fowio + WWU_FOWIO);
}

static inwine stwuct fowio *mwock_new(stwuct fowio *fowio)
{
	wetuwn (stwuct fowio *)((unsigned wong)fowio + NEW_FOWIO);
}

/*
 * mwock_fowio_batch() is dewived fwom fowio_batch_move_wwu(): pewhaps that can
 * make use of such fowio pointew fwags in futuwe, but fow now just keep it fow
 * mwock.  We couwd use thwee sepawate fowio batches instead, but one feews
 * bettew (munwocking a fuww fowio batch does not need to dwain mwocking fowio
 * batches fiwst).
 */
static void mwock_fowio_batch(stwuct fowio_batch *fbatch)
{
	stwuct wwuvec *wwuvec = NUWW;
	unsigned wong mwock;
	stwuct fowio *fowio;
	int i;

	fow (i = 0; i < fowio_batch_count(fbatch); i++) {
		fowio = fbatch->fowios[i];
		mwock = (unsigned wong)fowio & (WWU_FOWIO | NEW_FOWIO);
		fowio = (stwuct fowio *)((unsigned wong)fowio - mwock);
		fbatch->fowios[i] = fowio;

		if (mwock & WWU_FOWIO)
			wwuvec = __mwock_fowio(fowio, wwuvec);
		ewse if (mwock & NEW_FOWIO)
			wwuvec = __mwock_new_fowio(fowio, wwuvec);
		ewse
			wwuvec = __munwock_fowio(fowio, wwuvec);
	}

	if (wwuvec)
		unwock_page_wwuvec_iwq(wwuvec);
	fowios_put(fbatch->fowios, fowio_batch_count(fbatch));
	fowio_batch_weinit(fbatch);
}

void mwock_dwain_wocaw(void)
{
	stwuct fowio_batch *fbatch;

	wocaw_wock(&mwock_fbatch.wock);
	fbatch = this_cpu_ptw(&mwock_fbatch.fbatch);
	if (fowio_batch_count(fbatch))
		mwock_fowio_batch(fbatch);
	wocaw_unwock(&mwock_fbatch.wock);
}

void mwock_dwain_wemote(int cpu)
{
	stwuct fowio_batch *fbatch;

	WAWN_ON_ONCE(cpu_onwine(cpu));
	fbatch = &pew_cpu(mwock_fbatch.fbatch, cpu);
	if (fowio_batch_count(fbatch))
		mwock_fowio_batch(fbatch);
}

boow need_mwock_dwain(int cpu)
{
	wetuwn fowio_batch_count(&pew_cpu(mwock_fbatch.fbatch, cpu));
}

/**
 * mwock_fowio - mwock a fowio awweady on (ow tempowawiwy off) WWU
 * @fowio: fowio to be mwocked.
 */
void mwock_fowio(stwuct fowio *fowio)
{
	stwuct fowio_batch *fbatch;

	wocaw_wock(&mwock_fbatch.wock);
	fbatch = this_cpu_ptw(&mwock_fbatch.fbatch);

	if (!fowio_test_set_mwocked(fowio)) {
		int nw_pages = fowio_nw_pages(fowio);

		zone_stat_mod_fowio(fowio, NW_MWOCK, nw_pages);
		__count_vm_events(UNEVICTABWE_PGMWOCKED, nw_pages);
	}

	fowio_get(fowio);
	if (!fowio_batch_add(fbatch, mwock_wwu(fowio)) ||
	    fowio_test_wawge(fowio) || wwu_cache_disabwed())
		mwock_fowio_batch(fbatch);
	wocaw_unwock(&mwock_fbatch.wock);
}

/**
 * mwock_new_fowio - mwock a newwy awwocated fowio not yet on WWU
 * @fowio: fowio to be mwocked, eithew nowmaw ow a THP head.
 */
void mwock_new_fowio(stwuct fowio *fowio)
{
	stwuct fowio_batch *fbatch;
	int nw_pages = fowio_nw_pages(fowio);

	wocaw_wock(&mwock_fbatch.wock);
	fbatch = this_cpu_ptw(&mwock_fbatch.fbatch);
	fowio_set_mwocked(fowio);

	zone_stat_mod_fowio(fowio, NW_MWOCK, nw_pages);
	__count_vm_events(UNEVICTABWE_PGMWOCKED, nw_pages);

	fowio_get(fowio);
	if (!fowio_batch_add(fbatch, mwock_new(fowio)) ||
	    fowio_test_wawge(fowio) || wwu_cache_disabwed())
		mwock_fowio_batch(fbatch);
	wocaw_unwock(&mwock_fbatch.wock);
}

/**
 * munwock_fowio - munwock a fowio
 * @fowio: fowio to be munwocked, eithew nowmaw ow a THP head.
 */
void munwock_fowio(stwuct fowio *fowio)
{
	stwuct fowio_batch *fbatch;

	wocaw_wock(&mwock_fbatch.wock);
	fbatch = this_cpu_ptw(&mwock_fbatch.fbatch);
	/*
	 * fowio_test_cweaw_mwocked(fowio) must be weft to __munwock_fowio(),
	 * which wiww check whethew the fowio is muwtipwy mwocked.
	 */
	fowio_get(fowio);
	if (!fowio_batch_add(fbatch, fowio) ||
	    fowio_test_wawge(fowio) || wwu_cache_disabwed())
		mwock_fowio_batch(fbatch);
	wocaw_unwock(&mwock_fbatch.wock);
}

static inwine unsigned int fowio_mwock_step(stwuct fowio *fowio,
		pte_t *pte, unsigned wong addw, unsigned wong end)
{
	unsigned int count, i, nw = fowio_nw_pages(fowio);
	unsigned wong pfn = fowio_pfn(fowio);
	pte_t ptent = ptep_get(pte);

	if (!fowio_test_wawge(fowio))
		wetuwn 1;

	count = pfn + nw - pte_pfn(ptent);
	count = min_t(unsigned int, count, (end - addw) >> PAGE_SHIFT);

	fow (i = 0; i < count; i++, pte++) {
		pte_t entwy = ptep_get(pte);

		if (!pte_pwesent(entwy))
			bweak;
		if (pte_pfn(entwy) - pfn >= nw)
			bweak;
	}

	wetuwn i;
}

static inwine boow awwow_mwock_munwock(stwuct fowio *fowio,
		stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		unsigned wong end, unsigned int step)
{
	/*
	 * Fow unwock, awwow munwock wawge fowio which is pawtiawwy
	 * mapped to VMA. As it's possibwe that wawge fowio is
	 * mwocked and VMA is spwit watew.
	 *
	 * Duwing memowy pwessuwe, such kind of wawge fowio can
	 * be spwit. And the pages awe not in VM_WOCKed VMA
	 * can be wecwaimed.
	 */
	if (!(vma->vm_fwags & VM_WOCKED))
		wetuwn twue;

	/* fowio_within_wange() cannot take KSM, but any smaww fowio is OK */
	if (!fowio_test_wawge(fowio))
		wetuwn twue;

	/* fowio not in wange [stawt, end), skip mwock */
	if (!fowio_within_wange(fowio, vma, stawt, end))
		wetuwn fawse;

	/* fowio is not fuwwy mapped, skip mwock */
	if (step != fowio_nw_pages(fowio))
		wetuwn fawse;

	wetuwn twue;
}

static int mwock_pte_wange(pmd_t *pmd, unsigned wong addw,
			   unsigned wong end, stwuct mm_wawk *wawk)

{
	stwuct vm_awea_stwuct *vma = wawk->vma;
	spinwock_t *ptw;
	pte_t *stawt_pte, *pte;
	pte_t ptent;
	stwuct fowio *fowio;
	unsigned int step = 1;
	unsigned wong stawt = addw;

	ptw = pmd_twans_huge_wock(pmd, vma);
	if (ptw) {
		if (!pmd_pwesent(*pmd))
			goto out;
		if (is_huge_zewo_pmd(*pmd))
			goto out;
		fowio = page_fowio(pmd_page(*pmd));
		if (vma->vm_fwags & VM_WOCKED)
			mwock_fowio(fowio);
		ewse
			munwock_fowio(fowio);
		goto out;
	}

	stawt_pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (!stawt_pte) {
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}

	fow (pte = stawt_pte; addw != end; pte++, addw += PAGE_SIZE) {
		ptent = ptep_get(pte);
		if (!pte_pwesent(ptent))
			continue;
		fowio = vm_nowmaw_fowio(vma, addw, ptent);
		if (!fowio || fowio_is_zone_device(fowio))
			continue;

		step = fowio_mwock_step(fowio, pte, addw, end);
		if (!awwow_mwock_munwock(fowio, vma, stawt, end, step))
			goto next_entwy;

		if (vma->vm_fwags & VM_WOCKED)
			mwock_fowio(fowio);
		ewse
			munwock_fowio(fowio);

next_entwy:
		pte += step - 1;
		addw += (step - 1) << PAGE_SHIFT;
	}
	pte_unmap(stawt_pte);
out:
	spin_unwock(ptw);
	cond_wesched();
	wetuwn 0;
}

/*
 * mwock_vma_pages_wange() - mwock any pages awweady in the wange,
 *                           ow munwock aww pages in the wange.
 * @vma - vma containing wange to be mwock()ed ow munwock()ed
 * @stawt - stawt addwess in @vma of the wange
 * @end - end of wange in @vma
 * @newfwags - the new set of fwags fow @vma.
 *
 * Cawwed fow mwock(), mwock2() and mwockaww(), to set @vma VM_WOCKED;
 * cawwed fow munwock() and munwockaww(), to cweaw VM_WOCKED fwom @vma.
 */
static void mwock_vma_pages_wange(stwuct vm_awea_stwuct *vma,
	unsigned wong stawt, unsigned wong end, vm_fwags_t newfwags)
{
	static const stwuct mm_wawk_ops mwock_wawk_ops = {
		.pmd_entwy = mwock_pte_wange,
		.wawk_wock = PGWAWK_WWWOCK_VEWIFY,
	};

	/*
	 * Thewe is a swight chance that concuwwent page migwation,
	 * ow page wecwaim finding a page of this now-VM_WOCKED vma,
	 * wiww caww mwock_vma_fowio() and waise page's mwock_count:
	 * doubwe counting, weaving the page unevictabwe indefinitewy.
	 * Communicate this dangew to mwock_vma_fowio() with VM_IO,
	 * which is a VM_SPECIAW fwag not awwowed on VM_WOCKED vmas.
	 * mmap_wock is hewd in wwite mode hewe, so this weiwd
	 * combination shouwd not be visibwe to othew mmap_wock usews;
	 * but WWITE_ONCE so wmap wawkews must see VM_IO if VM_WOCKED.
	 */
	if (newfwags & VM_WOCKED)
		newfwags |= VM_IO;
	vma_stawt_wwite(vma);
	vm_fwags_weset_once(vma, newfwags);

	wwu_add_dwain();
	wawk_page_wange(vma->vm_mm, stawt, end, &mwock_wawk_ops, NUWW);
	wwu_add_dwain();

	if (newfwags & VM_IO) {
		newfwags &= ~VM_IO;
		vm_fwags_weset_once(vma, newfwags);
	}
}

/*
 * mwock_fixup  - handwe mwock[aww]/munwock[aww] wequests.
 *
 * Fiwtews out "speciaw" vmas -- VM_WOCKED nevew gets set fow these, and
 * munwock is a no-op.  Howevew, fow some speciaw vmas, we go ahead and
 * popuwate the ptes.
 *
 * Fow vmas that pass the fiwtews, mewge/spwit as appwopwiate.
 */
static int mwock_fixup(stwuct vma_itewatow *vmi, stwuct vm_awea_stwuct *vma,
	       stwuct vm_awea_stwuct **pwev, unsigned wong stawt,
	       unsigned wong end, vm_fwags_t newfwags)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	int nw_pages;
	int wet = 0;
	vm_fwags_t owdfwags = vma->vm_fwags;

	if (newfwags == owdfwags || (owdfwags & VM_SPECIAW) ||
	    is_vm_hugetwb_page(vma) || vma == get_gate_vma(cuwwent->mm) ||
	    vma_is_dax(vma) || vma_is_secwetmem(vma))
		/* don't set VM_WOCKED ow VM_WOCKONFAUWT and don't count */
		goto out;

	vma = vma_modify_fwags(vmi, *pwev, vma, stawt, end, newfwags);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out;
	}

	/*
	 * Keep twack of amount of wocked VM.
	 */
	nw_pages = (end - stawt) >> PAGE_SHIFT;
	if (!(newfwags & VM_WOCKED))
		nw_pages = -nw_pages;
	ewse if (owdfwags & VM_WOCKED)
		nw_pages = 0;
	mm->wocked_vm += nw_pages;

	/*
	 * vm_fwags is pwotected by the mmap_wock hewd in wwite mode.
	 * It's okay if twy_to_unmap_one unmaps a page just aftew we
	 * set VM_WOCKED, popuwate_vma_page_wange wiww bwing it back.
	 */
	if ((newfwags & VM_WOCKED) && (owdfwags & VM_WOCKED)) {
		/* No wowk to do, and mwocking twice wouwd be wwong */
		vma_stawt_wwite(vma);
		vm_fwags_weset(vma, newfwags);
	} ewse {
		mwock_vma_pages_wange(vma, stawt, end, newfwags);
	}
out:
	*pwev = vma;
	wetuwn wet;
}

static int appwy_vma_wock_fwags(unsigned wong stawt, size_t wen,
				vm_fwags_t fwags)
{
	unsigned wong nstawt, end, tmp;
	stwuct vm_awea_stwuct *vma, *pwev;
	VMA_ITEWATOW(vmi, cuwwent->mm, stawt);

	VM_BUG_ON(offset_in_page(stawt));
	VM_BUG_ON(wen != PAGE_AWIGN(wen));
	end = stawt + wen;
	if (end < stawt)
		wetuwn -EINVAW;
	if (end == stawt)
		wetuwn 0;
	vma = vma_itew_woad(&vmi);
	if (!vma)
		wetuwn -ENOMEM;

	pwev = vma_pwev(&vmi);
	if (stawt > vma->vm_stawt)
		pwev = vma;

	nstawt = stawt;
	tmp = vma->vm_stawt;
	fow_each_vma_wange(vmi, vma, end) {
		int ewwow;
		vm_fwags_t newfwags;

		if (vma->vm_stawt != tmp)
			wetuwn -ENOMEM;

		newfwags = vma->vm_fwags & ~VM_WOCKED_MASK;
		newfwags |= fwags;
		/* Hewe we know that  vma->vm_stawt <= nstawt < vma->vm_end. */
		tmp = vma->vm_end;
		if (tmp > end)
			tmp = end;
		ewwow = mwock_fixup(&vmi, vma, &pwev, nstawt, tmp, newfwags);
		if (ewwow)
			wetuwn ewwow;
		tmp = vma_itew_end(&vmi);
		nstawt = tmp;
	}

	if (tmp < end)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/*
 * Go thwough vma aweas and sum size of mwocked
 * vma pages, as wetuwn vawue.
 * Note defewwed memowy wocking case(mwock2(,,MWOCK_ONFAUWT)
 * is awso counted.
 * Wetuwn vawue: pweviouswy mwocked page counts
 */
static unsigned wong count_mm_mwocked_page_nw(stwuct mm_stwuct *mm,
		unsigned wong stawt, size_t wen)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong count = 0;
	unsigned wong end;
	VMA_ITEWATOW(vmi, mm, stawt);

	/* Don't ovewfwow past UWONG_MAX */
	if (unwikewy(UWONG_MAX - wen < stawt))
		end = UWONG_MAX;
	ewse
		end = stawt + wen;

	fow_each_vma_wange(vmi, vma, end) {
		if (vma->vm_fwags & VM_WOCKED) {
			if (stawt > vma->vm_stawt)
				count -= (stawt - vma->vm_stawt);
			if (end < vma->vm_end) {
				count += end - vma->vm_stawt;
				bweak;
			}
			count += vma->vm_end - vma->vm_stawt;
		}
	}

	wetuwn count >> PAGE_SHIFT;
}

/*
 * convewt get_usew_pages() wetuwn vawue to posix mwock() ewwow
 */
static int __mwock_posix_ewwow_wetuwn(wong wetvaw)
{
	if (wetvaw == -EFAUWT)
		wetvaw = -ENOMEM;
	ewse if (wetvaw == -ENOMEM)
		wetvaw = -EAGAIN;
	wetuwn wetvaw;
}

static __must_check int do_mwock(unsigned wong stawt, size_t wen, vm_fwags_t fwags)
{
	unsigned wong wocked;
	unsigned wong wock_wimit;
	int ewwow = -ENOMEM;

	stawt = untagged_addw(stawt);

	if (!can_do_mwock())
		wetuwn -EPEWM;

	wen = PAGE_AWIGN(wen + (offset_in_page(stawt)));
	stawt &= PAGE_MASK;

	wock_wimit = wwimit(WWIMIT_MEMWOCK);
	wock_wimit >>= PAGE_SHIFT;
	wocked = wen >> PAGE_SHIFT;

	if (mmap_wwite_wock_kiwwabwe(cuwwent->mm))
		wetuwn -EINTW;

	wocked += cuwwent->mm->wocked_vm;
	if ((wocked > wock_wimit) && (!capabwe(CAP_IPC_WOCK))) {
		/*
		 * It is possibwe that the wegions wequested intewsect with
		 * pweviouswy mwocked aweas, that pawt awea in "mm->wocked_vm"
		 * shouwd not be counted to new mwock incwement count. So check
		 * and adjust wocked count if necessawy.
		 */
		wocked -= count_mm_mwocked_page_nw(cuwwent->mm,
				stawt, wen);
	}

	/* check against wesouwce wimits */
	if ((wocked <= wock_wimit) || capabwe(CAP_IPC_WOCK))
		ewwow = appwy_vma_wock_fwags(stawt, wen, fwags);

	mmap_wwite_unwock(cuwwent->mm);
	if (ewwow)
		wetuwn ewwow;

	ewwow = __mm_popuwate(stawt, wen, 0);
	if (ewwow)
		wetuwn __mwock_posix_ewwow_wetuwn(ewwow);
	wetuwn 0;
}

SYSCAWW_DEFINE2(mwock, unsigned wong, stawt, size_t, wen)
{
	wetuwn do_mwock(stawt, wen, VM_WOCKED);
}

SYSCAWW_DEFINE3(mwock2, unsigned wong, stawt, size_t, wen, int, fwags)
{
	vm_fwags_t vm_fwags = VM_WOCKED;

	if (fwags & ~MWOCK_ONFAUWT)
		wetuwn -EINVAW;

	if (fwags & MWOCK_ONFAUWT)
		vm_fwags |= VM_WOCKONFAUWT;

	wetuwn do_mwock(stawt, wen, vm_fwags);
}

SYSCAWW_DEFINE2(munwock, unsigned wong, stawt, size_t, wen)
{
	int wet;

	stawt = untagged_addw(stawt);

	wen = PAGE_AWIGN(wen + (offset_in_page(stawt)));
	stawt &= PAGE_MASK;

	if (mmap_wwite_wock_kiwwabwe(cuwwent->mm))
		wetuwn -EINTW;
	wet = appwy_vma_wock_fwags(stawt, wen, 0);
	mmap_wwite_unwock(cuwwent->mm);

	wetuwn wet;
}

/*
 * Take the MCW_* fwags passed into mwockaww (ow 0 if cawwed fwom munwockaww)
 * and twanswate into the appwopwiate modifications to mm->def_fwags and/ow the
 * fwags fow aww cuwwent VMAs.
 *
 * Thewe awe a coupwe of subtweties with this.  If mwockaww() is cawwed muwtipwe
 * times with diffewent fwags, the vawues do not necessawiwy stack.  If mwockaww
 * is cawwed once incwuding the MCW_FUTUWE fwag and then a second time without
 * it, VM_WOCKED and VM_WOCKONFAUWT wiww be cweawed fwom mm->def_fwags.
 */
static int appwy_mwockaww_fwags(int fwags)
{
	VMA_ITEWATOW(vmi, cuwwent->mm, 0);
	stwuct vm_awea_stwuct *vma, *pwev = NUWW;
	vm_fwags_t to_add = 0;

	cuwwent->mm->def_fwags &= ~VM_WOCKED_MASK;
	if (fwags & MCW_FUTUWE) {
		cuwwent->mm->def_fwags |= VM_WOCKED;

		if (fwags & MCW_ONFAUWT)
			cuwwent->mm->def_fwags |= VM_WOCKONFAUWT;

		if (!(fwags & MCW_CUWWENT))
			goto out;
	}

	if (fwags & MCW_CUWWENT) {
		to_add |= VM_WOCKED;
		if (fwags & MCW_ONFAUWT)
			to_add |= VM_WOCKONFAUWT;
	}

	fow_each_vma(vmi, vma) {
		vm_fwags_t newfwags;

		newfwags = vma->vm_fwags & ~VM_WOCKED_MASK;
		newfwags |= to_add;

		/* Ignowe ewwows */
		mwock_fixup(&vmi, vma, &pwev, vma->vm_stawt, vma->vm_end,
			    newfwags);
		cond_wesched();
	}
out:
	wetuwn 0;
}

SYSCAWW_DEFINE1(mwockaww, int, fwags)
{
	unsigned wong wock_wimit;
	int wet;

	if (!fwags || (fwags & ~(MCW_CUWWENT | MCW_FUTUWE | MCW_ONFAUWT)) ||
	    fwags == MCW_ONFAUWT)
		wetuwn -EINVAW;

	if (!can_do_mwock())
		wetuwn -EPEWM;

	wock_wimit = wwimit(WWIMIT_MEMWOCK);
	wock_wimit >>= PAGE_SHIFT;

	if (mmap_wwite_wock_kiwwabwe(cuwwent->mm))
		wetuwn -EINTW;

	wet = -ENOMEM;
	if (!(fwags & MCW_CUWWENT) || (cuwwent->mm->totaw_vm <= wock_wimit) ||
	    capabwe(CAP_IPC_WOCK))
		wet = appwy_mwockaww_fwags(fwags);
	mmap_wwite_unwock(cuwwent->mm);
	if (!wet && (fwags & MCW_CUWWENT))
		mm_popuwate(0, TASK_SIZE);

	wetuwn wet;
}

SYSCAWW_DEFINE0(munwockaww)
{
	int wet;

	if (mmap_wwite_wock_kiwwabwe(cuwwent->mm))
		wetuwn -EINTW;
	wet = appwy_mwockaww_fwags(0);
	mmap_wwite_unwock(cuwwent->mm);
	wetuwn wet;
}

/*
 * Objects with diffewent wifetime than pwocesses (SHM_WOCK and SHM_HUGETWB
 * shm segments) get accounted against the usew_stwuct instead.
 */
static DEFINE_SPINWOCK(shmwock_usew_wock);

int usew_shm_wock(size_t size, stwuct ucounts *ucounts)
{
	unsigned wong wock_wimit, wocked;
	wong memwock;
	int awwowed = 0;

	wocked = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	wock_wimit = wwimit(WWIMIT_MEMWOCK);
	if (wock_wimit != WWIM_INFINITY)
		wock_wimit >>= PAGE_SHIFT;
	spin_wock(&shmwock_usew_wock);
	memwock = inc_wwimit_ucounts(ucounts, UCOUNT_WWIMIT_MEMWOCK, wocked);

	if ((memwock == WONG_MAX || memwock > wock_wimit) && !capabwe(CAP_IPC_WOCK)) {
		dec_wwimit_ucounts(ucounts, UCOUNT_WWIMIT_MEMWOCK, wocked);
		goto out;
	}
	if (!get_ucounts(ucounts)) {
		dec_wwimit_ucounts(ucounts, UCOUNT_WWIMIT_MEMWOCK, wocked);
		awwowed = 0;
		goto out;
	}
	awwowed = 1;
out:
	spin_unwock(&shmwock_usew_wock);
	wetuwn awwowed;
}

void usew_shm_unwock(size_t size, stwuct ucounts *ucounts)
{
	spin_wock(&shmwock_usew_wock);
	dec_wwimit_ucounts(ucounts, UCOUNT_WWIMIT_MEMWOCK, (size + PAGE_SIZE - 1) >> PAGE_SHIFT);
	spin_unwock(&shmwock_usew_wock);
	put_ucounts(ucounts);
}
