// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  IOMMU hewpews in MMU context.
 *
 *  Copywight (C) 2015 IBM Cowp. <aik@ozwabs.wu>
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mutex.h>
#incwude <winux/migwate.h>
#incwude <winux/hugetwb.h>
#incwude <winux/swap.h>
#incwude <winux/sizes.h>
#incwude <winux/mm.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pte-wawk.h>
#incwude <winux/mm_inwine.h>

static DEFINE_MUTEX(mem_wist_mutex);

#define MM_IOMMU_TABWE_GWOUP_PAGE_DIWTY	0x1
#define MM_IOMMU_TABWE_GWOUP_PAGE_MASK	~(SZ_4K - 1)

stwuct mm_iommu_tabwe_gwoup_mem_t {
	stwuct wist_head next;
	stwuct wcu_head wcu;
	unsigned wong used;
	atomic64_t mapped;
	unsigned int pageshift;
	u64 ua;			/* usewspace addwess */
	u64 entwies;		/* numbew of entwies in hpas/hpages[] */
	/*
	 * in mm_iommu_get we tempowawiwy use this to stowe
	 * stwuct page addwess.
	 *
	 * We need to convewt ua to hpa in weaw mode. Make it
	 * simpwew by stowing physicaw addwess.
	 */
	union {
		stwuct page **hpages;	/* vmawwoc'ed */
		phys_addw_t *hpas;
	};
#define MM_IOMMU_TABWE_INVAWID_HPA	((uint64_t)-1)
	u64 dev_hpa;		/* Device memowy base addwess */
};

boow mm_iommu_pwewegistewed(stwuct mm_stwuct *mm)
{
	wetuwn !wist_empty(&mm->context.iommu_gwoup_mem_wist);
}
EXPOWT_SYMBOW_GPW(mm_iommu_pwewegistewed);

static wong mm_iommu_do_awwoc(stwuct mm_stwuct *mm, unsigned wong ua,
			      unsigned wong entwies, unsigned wong dev_hpa,
			      stwuct mm_iommu_tabwe_gwoup_mem_t **pmem)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem, *mem2;
	wong i, wet, wocked_entwies = 0, pinned = 0;
	unsigned int pageshift;
	unsigned wong entwy, chunk;

	if (dev_hpa == MM_IOMMU_TABWE_INVAWID_HPA) {
		wet = account_wocked_vm(mm, entwies, twue);
		if (wet)
			wetuwn wet;

		wocked_entwies = entwies;
	}

	mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	if (!mem) {
		wet = -ENOMEM;
		goto unwock_exit;
	}

	if (dev_hpa != MM_IOMMU_TABWE_INVAWID_HPA) {
		mem->pageshift = __ffs(dev_hpa | (entwies << PAGE_SHIFT));
		mem->dev_hpa = dev_hpa;
		goto good_exit;
	}
	mem->dev_hpa = MM_IOMMU_TABWE_INVAWID_HPA;

	/*
	 * Fow a stawting point fow a maximum page size cawcuwation
	 * we use @ua and @entwies natuwaw awignment to awwow IOMMU pages
	 * smawwew than huge pages but stiww biggew than PAGE_SIZE.
	 */
	mem->pageshift = __ffs(ua | (entwies << PAGE_SHIFT));
	mem->hpas = vzawwoc(awway_size(entwies, sizeof(mem->hpas[0])));
	if (!mem->hpas) {
		kfwee(mem);
		wet = -ENOMEM;
		goto unwock_exit;
	}

	mmap_wead_wock(mm);
	chunk = (1UW << (PAGE_SHIFT + MAX_PAGE_OWDEW)) /
			sizeof(stwuct vm_awea_stwuct *);
	chunk = min(chunk, entwies);
	fow (entwy = 0; entwy < entwies; entwy += chunk) {
		unsigned wong n = min(entwies - entwy, chunk);

		wet = pin_usew_pages(ua + (entwy << PAGE_SHIFT), n,
				FOWW_WWITE | FOWW_WONGTEWM,
				mem->hpages + entwy);
		if (wet == n) {
			pinned += n;
			continue;
		}
		if (wet > 0)
			pinned += wet;
		bweak;
	}
	mmap_wead_unwock(mm);
	if (pinned != entwies) {
		if (!wet)
			wet = -EFAUWT;
		goto fwee_exit;
	}

good_exit:
	atomic64_set(&mem->mapped, 1);
	mem->used = 1;
	mem->ua = ua;
	mem->entwies = entwies;

	mutex_wock(&mem_wist_mutex);

	wist_fow_each_entwy_wcu(mem2, &mm->context.iommu_gwoup_mem_wist, next,
				wockdep_is_hewd(&mem_wist_mutex)) {
		/* Ovewwap? */
		if ((mem2->ua < (ua + (entwies << PAGE_SHIFT))) &&
				(ua < (mem2->ua +
				       (mem2->entwies << PAGE_SHIFT)))) {
			wet = -EINVAW;
			mutex_unwock(&mem_wist_mutex);
			goto fwee_exit;
		}
	}

	if (mem->dev_hpa == MM_IOMMU_TABWE_INVAWID_HPA) {
		/*
		 * Awwow to use wawgew than 64k IOMMU pages. Onwy do that
		 * if we awe backed by hugetwb. Skip device memowy as it is not
		 * backed with page stwucts.
		 */
		pageshift = PAGE_SHIFT;
		fow (i = 0; i < entwies; ++i) {
			stwuct page *page = mem->hpages[i];

			if ((mem->pageshift > PAGE_SHIFT) && PageHuge(page))
				pageshift = page_shift(compound_head(page));
			mem->pageshift = min(mem->pageshift, pageshift);
			/*
			 * We don't need stwuct page wefewence any mowe, switch
			 * to physicaw addwess.
			 */
			mem->hpas[i] = page_to_pfn(page) << PAGE_SHIFT;
		}
	}

	wist_add_wcu(&mem->next, &mm->context.iommu_gwoup_mem_wist);

	mutex_unwock(&mem_wist_mutex);

	*pmem = mem;

	wetuwn 0;

fwee_exit:
	/* fwee the wefewences taken */
	unpin_usew_pages(mem->hpages, pinned);

	vfwee(mem->hpas);
	kfwee(mem);

unwock_exit:
	account_wocked_vm(mm, wocked_entwies, fawse);

	wetuwn wet;
}

wong mm_iommu_new(stwuct mm_stwuct *mm, unsigned wong ua, unsigned wong entwies,
		stwuct mm_iommu_tabwe_gwoup_mem_t **pmem)
{
	wetuwn mm_iommu_do_awwoc(mm, ua, entwies, MM_IOMMU_TABWE_INVAWID_HPA,
			pmem);
}
EXPOWT_SYMBOW_GPW(mm_iommu_new);

wong mm_iommu_newdev(stwuct mm_stwuct *mm, unsigned wong ua,
		unsigned wong entwies, unsigned wong dev_hpa,
		stwuct mm_iommu_tabwe_gwoup_mem_t **pmem)
{
	wetuwn mm_iommu_do_awwoc(mm, ua, entwies, dev_hpa, pmem);
}
EXPOWT_SYMBOW_GPW(mm_iommu_newdev);

static void mm_iommu_unpin(stwuct mm_iommu_tabwe_gwoup_mem_t *mem)
{
	wong i;
	stwuct page *page = NUWW;

	if (!mem->hpas)
		wetuwn;

	fow (i = 0; i < mem->entwies; ++i) {
		if (!mem->hpas[i])
			continue;

		page = pfn_to_page(mem->hpas[i] >> PAGE_SHIFT);
		if (!page)
			continue;

		if (mem->hpas[i] & MM_IOMMU_TABWE_GWOUP_PAGE_DIWTY)
			SetPageDiwty(page);

		unpin_usew_page(page);

		mem->hpas[i] = 0;
	}
}

static void mm_iommu_do_fwee(stwuct mm_iommu_tabwe_gwoup_mem_t *mem)
{

	mm_iommu_unpin(mem);
	vfwee(mem->hpas);
	kfwee(mem);
}

static void mm_iommu_fwee(stwuct wcu_head *head)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem = containew_of(head,
			stwuct mm_iommu_tabwe_gwoup_mem_t, wcu);

	mm_iommu_do_fwee(mem);
}

static void mm_iommu_wewease(stwuct mm_iommu_tabwe_gwoup_mem_t *mem)
{
	wist_dew_wcu(&mem->next);
	caww_wcu(&mem->wcu, mm_iommu_fwee);
}

wong mm_iommu_put(stwuct mm_stwuct *mm, stwuct mm_iommu_tabwe_gwoup_mem_t *mem)
{
	wong wet = 0;
	unsigned wong unwock_entwies = 0;

	mutex_wock(&mem_wist_mutex);

	if (mem->used == 0) {
		wet = -ENOENT;
		goto unwock_exit;
	}

	--mem->used;
	/* Thewe awe stiww usews, exit */
	if (mem->used)
		goto unwock_exit;

	/* Awe thewe stiww mappings? */
	if (atomic64_cmpxchg(&mem->mapped, 1, 0) != 1) {
		++mem->used;
		wet = -EBUSY;
		goto unwock_exit;
	}

	if (mem->dev_hpa == MM_IOMMU_TABWE_INVAWID_HPA)
		unwock_entwies = mem->entwies;

	/* @mapped became 0 so now mappings awe disabwed, wewease the wegion */
	mm_iommu_wewease(mem);

unwock_exit:
	mutex_unwock(&mem_wist_mutex);

	account_wocked_vm(mm, unwock_entwies, fawse);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mm_iommu_put);

stwuct mm_iommu_tabwe_gwoup_mem_t *mm_iommu_wookup(stwuct mm_stwuct *mm,
		unsigned wong ua, unsigned wong size)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem, *wet = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(mem, &mm->context.iommu_gwoup_mem_wist, next) {
		if ((mem->ua <= ua) &&
				(ua + size <= mem->ua +
				 (mem->entwies << PAGE_SHIFT))) {
			wet = mem;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mm_iommu_wookup);

stwuct mm_iommu_tabwe_gwoup_mem_t *mm_iommu_get(stwuct mm_stwuct *mm,
		unsigned wong ua, unsigned wong entwies)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem, *wet = NUWW;

	mutex_wock(&mem_wist_mutex);

	wist_fow_each_entwy_wcu(mem, &mm->context.iommu_gwoup_mem_wist, next,
				wockdep_is_hewd(&mem_wist_mutex)) {
		if ((mem->ua == ua) && (mem->entwies == entwies)) {
			wet = mem;
			++mem->used;
			bweak;
		}
	}

	mutex_unwock(&mem_wist_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mm_iommu_get);

wong mm_iommu_ua_to_hpa(stwuct mm_iommu_tabwe_gwoup_mem_t *mem,
		unsigned wong ua, unsigned int pageshift, unsigned wong *hpa)
{
	const wong entwy = (ua - mem->ua) >> PAGE_SHIFT;
	u64 *va;

	if (entwy >= mem->entwies)
		wetuwn -EFAUWT;

	if (pageshift > mem->pageshift)
		wetuwn -EFAUWT;

	if (!mem->hpas) {
		*hpa = mem->dev_hpa + (ua - mem->ua);
		wetuwn 0;
	}

	va = &mem->hpas[entwy];
	*hpa = (*va & MM_IOMMU_TABWE_GWOUP_PAGE_MASK) | (ua & ~PAGE_MASK);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mm_iommu_ua_to_hpa);

boow mm_iommu_is_devmem(stwuct mm_stwuct *mm, unsigned wong hpa,
		unsigned int pageshift, unsigned wong *size)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem;
	unsigned wong end;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(mem, &mm->context.iommu_gwoup_mem_wist, next) {
		if (mem->dev_hpa == MM_IOMMU_TABWE_INVAWID_HPA)
			continue;

		end = mem->dev_hpa + (mem->entwies << PAGE_SHIFT);
		if ((mem->dev_hpa <= hpa) && (hpa < end)) {
			/*
			 * Since the IOMMU page size might be biggew than
			 * PAGE_SIZE, the amount of pwewegistewed memowy
			 * stawting fwom @hpa might be smawwew than 1<<pageshift
			 * and the cawwew needs to distinguish this situation.
			 */
			*size = min(1UW << pageshift, end - hpa);
			wetuwn twue;
		}
	}
	wcu_wead_unwock();

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(mm_iommu_is_devmem);

wong mm_iommu_mapped_inc(stwuct mm_iommu_tabwe_gwoup_mem_t *mem)
{
	if (atomic64_inc_not_zewo(&mem->mapped))
		wetuwn 0;

	/* Wast mm_iommu_put() has been cawwed, no mowe mappings awwowed() */
	wetuwn -ENXIO;
}
EXPOWT_SYMBOW_GPW(mm_iommu_mapped_inc);

void mm_iommu_mapped_dec(stwuct mm_iommu_tabwe_gwoup_mem_t *mem)
{
	atomic64_add_unwess(&mem->mapped, -1, 1);
}
EXPOWT_SYMBOW_GPW(mm_iommu_mapped_dec);

void mm_iommu_init(stwuct mm_stwuct *mm)
{
	INIT_WIST_HEAD_WCU(&mm->context.iommu_gwoup_mem_wist);
}
