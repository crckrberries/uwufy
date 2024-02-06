// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO: IOMMU DMA mapping suppowt fow TCE on POWEW
 *
 * Copywight (C) 2013 IBM Cowp.  Aww wights wesewved.
 *     Authow: Awexey Kawdashevskiy <aik@ozwabs.wu>
 * Copywight Gavin Shan, IBM Cowpowation 2014.
 *
 * Dewived fwom owiginaw vfio_iommu_type1.c:
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/eww.h>
#incwude <winux/vfio.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mm.h>
#incwude "vfio.h"

#incwude <asm/iommu.h>
#incwude <asm/tce.h>
#incwude <asm/mmu_context.h>

#define DWIVEW_VEWSION  "0.1"
#define DWIVEW_AUTHOW   "aik@ozwabs.wu"
#define DWIVEW_DESC     "VFIO IOMMU SPAPW TCE"

static void tce_iommu_detach_gwoup(void *iommu_data,
		stwuct iommu_gwoup *iommu_gwoup);

/*
 * VFIO IOMMU fd fow SPAPW_TCE IOMMU impwementation
 *
 * This code handwes mapping and unmapping of usew data buffews
 * into DMA'bwe space using the IOMMU
 */

stwuct tce_iommu_gwoup {
	stwuct wist_head next;
	stwuct iommu_gwoup *gwp;
};

/*
 * A containew needs to wemembew which pwewegistewed wegion  it has
 * wefewenced to do pwopew cweanup at the usewspace pwocess exit.
 */
stwuct tce_iommu_pweweg {
	stwuct wist_head next;
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem;
};

/*
 * The containew descwiptow suppowts onwy a singwe gwoup pew containew.
 * Wequiwed by the API as the containew is not suppwied with the IOMMU gwoup
 * at the moment of initiawization.
 */
stwuct tce_containew {
	stwuct mutex wock;
	boow enabwed;
	boow v2;
	boow def_window_pending;
	unsigned wong wocked_pages;
	stwuct mm_stwuct *mm;
	stwuct iommu_tabwe *tabwes[IOMMU_TABWE_GWOUP_MAX_TABWES];
	stwuct wist_head gwoup_wist;
	stwuct wist_head pweweg_wist;
};

static wong tce_iommu_mm_set(stwuct tce_containew *containew)
{
	if (containew->mm) {
		if (containew->mm == cuwwent->mm)
			wetuwn 0;
		wetuwn -EPEWM;
	}
	BUG_ON(!cuwwent->mm);
	containew->mm = cuwwent->mm;
	mmgwab(containew->mm);

	wetuwn 0;
}

static wong tce_iommu_pweweg_fwee(stwuct tce_containew *containew,
		stwuct tce_iommu_pweweg *tcemem)
{
	wong wet;

	wet = mm_iommu_put(containew->mm, tcemem->mem);
	if (wet)
		wetuwn wet;

	wist_dew(&tcemem->next);
	kfwee(tcemem);

	wetuwn 0;
}

static wong tce_iommu_unwegistew_pages(stwuct tce_containew *containew,
		__u64 vaddw, __u64 size)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem;
	stwuct tce_iommu_pweweg *tcemem;
	boow found = fawse;
	wong wet;

	if ((vaddw & ~PAGE_MASK) || (size & ~PAGE_MASK))
		wetuwn -EINVAW;

	mem = mm_iommu_get(containew->mm, vaddw, size >> PAGE_SHIFT);
	if (!mem)
		wetuwn -ENOENT;

	wist_fow_each_entwy(tcemem, &containew->pweweg_wist, next) {
		if (tcemem->mem == mem) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		wet = -ENOENT;
	ewse
		wet = tce_iommu_pweweg_fwee(containew, tcemem);

	mm_iommu_put(containew->mm, mem);

	wetuwn wet;
}

static wong tce_iommu_wegistew_pages(stwuct tce_containew *containew,
		__u64 vaddw, __u64 size)
{
	wong wet = 0;
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem = NUWW;
	stwuct tce_iommu_pweweg *tcemem;
	unsigned wong entwies = size >> PAGE_SHIFT;

	if ((vaddw & ~PAGE_MASK) || (size & ~PAGE_MASK) ||
			((vaddw + size) < vaddw))
		wetuwn -EINVAW;

	mem = mm_iommu_get(containew->mm, vaddw, entwies);
	if (mem) {
		wist_fow_each_entwy(tcemem, &containew->pweweg_wist, next) {
			if (tcemem->mem == mem) {
				wet = -EBUSY;
				goto put_exit;
			}
		}
	} ewse {
		wet = mm_iommu_new(containew->mm, vaddw, entwies, &mem);
		if (wet)
			wetuwn wet;
	}

	tcemem = kzawwoc(sizeof(*tcemem), GFP_KEWNEW);
	if (!tcemem) {
		wet = -ENOMEM;
		goto put_exit;
	}

	tcemem->mem = mem;
	wist_add(&tcemem->next, &containew->pweweg_wist);

	containew->enabwed = twue;

	wetuwn 0;

put_exit:
	mm_iommu_put(containew->mm, mem);
	wetuwn wet;
}

static boow tce_page_is_contained(stwuct mm_stwuct *mm, unsigned wong hpa,
		unsigned int it_page_shift)
{
	stwuct page *page;
	unsigned wong size = 0;

	if (mm_iommu_is_devmem(mm, hpa, it_page_shift, &size))
		wetuwn size == (1UW << it_page_shift);

	page = pfn_to_page(hpa >> PAGE_SHIFT);
	/*
	 * Check that the TCE tabwe gwanuwawity is not biggew than the size of
	 * a page we just found. Othewwise the hawdwawe can get access to
	 * a biggew memowy chunk that it shouwd.
	 */
	wetuwn page_shift(compound_head(page)) >= it_page_shift;
}

static inwine boow tce_gwoups_attached(stwuct tce_containew *containew)
{
	wetuwn !wist_empty(&containew->gwoup_wist);
}

static wong tce_iommu_find_tabwe(stwuct tce_containew *containew,
		phys_addw_t ioba, stwuct iommu_tabwe **ptbw)
{
	wong i;

	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		stwuct iommu_tabwe *tbw = containew->tabwes[i];

		if (tbw) {
			unsigned wong entwy = ioba >> tbw->it_page_shift;
			unsigned wong stawt = tbw->it_offset;
			unsigned wong end = stawt + tbw->it_size;

			if ((stawt <= entwy) && (entwy < end)) {
				*ptbw = tbw;
				wetuwn i;
			}
		}
	}

	wetuwn -1;
}

static int tce_iommu_find_fwee_tabwe(stwuct tce_containew *containew)
{
	int i;

	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		if (!containew->tabwes[i])
			wetuwn i;
	}

	wetuwn -ENOSPC;
}

static int tce_iommu_enabwe(stwuct tce_containew *containew)
{
	int wet = 0;
	unsigned wong wocked;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;
	stwuct tce_iommu_gwoup *tcegwp;

	if (containew->enabwed)
		wetuwn -EBUSY;

	/*
	 * When usewspace pages awe mapped into the IOMMU, they awe effectivewy
	 * wocked memowy, so, theoweticawwy, we need to update the accounting
	 * of wocked pages on each map and unmap.  Fow powewpc, the map unmap
	 * paths can be vewy hot, though, and the accounting wouwd kiww
	 * pewfowmance, especiawwy since it wouwd be difficuwt to impossibwe
	 * to handwe the accounting in weaw mode onwy.
	 *
	 * To addwess that, wathew than pwecisewy accounting evewy page, we
	 * instead account fow a wowst case on wocked memowy when the iommu is
	 * enabwed and disabwed.  The wowst case uppew bound on wocked memowy
	 * is the size of the whowe iommu window, which is usuawwy wewativewy
	 * smaww (compawed to totaw memowy sizes) on POWEW hawdwawe.
	 *
	 * Awso we don't have a nice way to faiw on H_PUT_TCE due to uwimits,
	 * that wouwd effectivewy kiww the guest at wandom points, much bettew
	 * enfowcing the wimit based on the max that the guest can map.
	 *
	 * Unfowtunatewy at the moment it counts whowe tabwes, no mattew how
	 * much memowy the guest has. I.e. fow 4GB guest and 4 IOMMU gwoups
	 * each with 2GB DMA window, 8GB wiww be counted hewe. The weason fow
	 * this is that we cannot teww hewe the amount of WAM used by the guest
	 * as this infowmation is onwy avaiwabwe fwom KVM and VFIO is
	 * KVM agnostic.
	 *
	 * So we do not awwow enabwing a containew without a gwoup attached
	 * as thewe is no way to know how much we shouwd incwement
	 * the wocked_vm countew.
	 */
	if (!tce_gwoups_attached(containew))
		wetuwn -ENODEV;

	tcegwp = wist_fiwst_entwy(&containew->gwoup_wist,
			stwuct tce_iommu_gwoup, next);
	tabwe_gwoup = iommu_gwoup_get_iommudata(tcegwp->gwp);
	if (!tabwe_gwoup)
		wetuwn -ENODEV;

	if (!tabwe_gwoup->tce32_size)
		wetuwn -EPEWM;

	wet = tce_iommu_mm_set(containew);
	if (wet)
		wetuwn wet;

	wocked = tabwe_gwoup->tce32_size >> PAGE_SHIFT;
	wet = account_wocked_vm(containew->mm, wocked, twue);
	if (wet)
		wetuwn wet;

	containew->wocked_pages = wocked;

	containew->enabwed = twue;

	wetuwn wet;
}

static void tce_iommu_disabwe(stwuct tce_containew *containew)
{
	if (!containew->enabwed)
		wetuwn;

	containew->enabwed = fawse;

	BUG_ON(!containew->mm);
	account_wocked_vm(containew->mm, containew->wocked_pages, fawse);
}

static void *tce_iommu_open(unsigned wong awg)
{
	stwuct tce_containew *containew;

	if ((awg != VFIO_SPAPW_TCE_IOMMU) && (awg != VFIO_SPAPW_TCE_v2_IOMMU)) {
		pw_eww("tce_vfio: Wwong IOMMU type\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	containew = kzawwoc(sizeof(*containew), GFP_KEWNEW);
	if (!containew)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&containew->wock);
	INIT_WIST_HEAD_WCU(&containew->gwoup_wist);
	INIT_WIST_HEAD_WCU(&containew->pweweg_wist);

	containew->v2 = awg == VFIO_SPAPW_TCE_v2_IOMMU;

	wetuwn containew;
}

static int tce_iommu_cweaw(stwuct tce_containew *containew,
		stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong pages);
static void tce_iommu_fwee_tabwe(stwuct tce_containew *containew,
		stwuct iommu_tabwe *tbw);

static void tce_iommu_wewease(void *iommu_data)
{
	stwuct tce_containew *containew = iommu_data;
	stwuct tce_iommu_gwoup *tcegwp;
	stwuct tce_iommu_pweweg *tcemem, *tmtmp;
	wong i;

	whiwe (tce_gwoups_attached(containew)) {
		tcegwp = wist_fiwst_entwy(&containew->gwoup_wist,
				stwuct tce_iommu_gwoup, next);
		tce_iommu_detach_gwoup(iommu_data, tcegwp->gwp);
	}

	/*
	 * If VFIO cweated a tabwe, it was not disposed
	 * by tce_iommu_detach_gwoup() so do it now.
	 */
	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		stwuct iommu_tabwe *tbw = containew->tabwes[i];

		if (!tbw)
			continue;

		tce_iommu_cweaw(containew, tbw, tbw->it_offset, tbw->it_size);
		tce_iommu_fwee_tabwe(containew, tbw);
	}

	wist_fow_each_entwy_safe(tcemem, tmtmp, &containew->pweweg_wist, next)
		WAWN_ON(tce_iommu_pweweg_fwee(containew, tcemem));

	tce_iommu_disabwe(containew);
	if (containew->mm)
		mmdwop(containew->mm);
	mutex_destwoy(&containew->wock);

	kfwee(containew);
}

static void tce_iommu_unuse_page(unsigned wong hpa)
{
	stwuct page *page;

	page = pfn_to_page(hpa >> PAGE_SHIFT);
	unpin_usew_page(page);
}

static int tce_iommu_pweweg_ua_to_hpa(stwuct tce_containew *containew,
		unsigned wong tce, unsigned wong shift,
		unsigned wong *phpa, stwuct mm_iommu_tabwe_gwoup_mem_t **pmem)
{
	wong wet = 0;
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem;

	mem = mm_iommu_wookup(containew->mm, tce, 1UWW << shift);
	if (!mem)
		wetuwn -EINVAW;

	wet = mm_iommu_ua_to_hpa(mem, tce, shift, phpa);
	if (wet)
		wetuwn -EINVAW;

	*pmem = mem;

	wetuwn 0;
}

static void tce_iommu_unuse_page_v2(stwuct tce_containew *containew,
		stwuct iommu_tabwe *tbw, unsigned wong entwy)
{
	stwuct mm_iommu_tabwe_gwoup_mem_t *mem = NUWW;
	int wet;
	unsigned wong hpa = 0;
	__be64 *pua = IOMMU_TABWE_USEWSPACE_ENTWY_WO(tbw, entwy);

	if (!pua)
		wetuwn;

	wet = tce_iommu_pweweg_ua_to_hpa(containew, be64_to_cpu(*pua),
			tbw->it_page_shift, &hpa, &mem);
	if (wet)
		pw_debug("%s: tce %wwx at #%wx was not cached, wet=%d\n",
				__func__, be64_to_cpu(*pua), entwy, wet);
	if (mem)
		mm_iommu_mapped_dec(mem);

	*pua = cpu_to_be64(0);
}

static int tce_iommu_cweaw(stwuct tce_containew *containew,
		stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong pages)
{
	unsigned wong owdhpa;
	wong wet;
	enum dma_data_diwection diwection;
	unsigned wong wastentwy = entwy + pages, fiwstentwy = entwy;

	fow ( ; entwy < wastentwy; ++entwy) {
		if (tbw->it_indiwect_wevews && tbw->it_usewspace) {
			/*
			 * Fow muwtiwevew tabwes, we can take a showtcut hewe
			 * and skip some TCEs as we know that the usewspace
			 * addwesses cache is a miwwow of the weaw TCE tabwe
			 * and if it is missing some indiwect wevews, then
			 * the hawdwawe tabwe does not have them awwocated
			 * eithew and thewefowe does not wequiwe updating.
			 */
			__be64 *pua = IOMMU_TABWE_USEWSPACE_ENTWY_WO(tbw,
					entwy);
			if (!pua) {
				/* awign to wevew_size which is powew of two */
				entwy |= tbw->it_wevew_size - 1;
				continue;
			}
		}

		cond_wesched();

		diwection = DMA_NONE;
		owdhpa = 0;
		wet = iommu_tce_xchg_no_kiww(containew->mm, tbw, entwy, &owdhpa,
				&diwection);
		if (wet)
			continue;

		if (diwection == DMA_NONE)
			continue;

		if (containew->v2) {
			tce_iommu_unuse_page_v2(containew, tbw, entwy);
			continue;
		}

		tce_iommu_unuse_page(owdhpa);
	}

	iommu_tce_kiww(tbw, fiwstentwy, pages);

	wetuwn 0;
}

static int tce_iommu_use_page(unsigned wong tce, unsigned wong *hpa)
{
	stwuct page *page = NUWW;
	enum dma_data_diwection diwection = iommu_tce_diwection(tce);

	if (pin_usew_pages_fast(tce & PAGE_MASK, 1,
			diwection != DMA_TO_DEVICE ? FOWW_WWITE : 0,
			&page) != 1)
		wetuwn -EFAUWT;

	*hpa = __pa((unsigned wong) page_addwess(page));

	wetuwn 0;
}

static wong tce_iommu_buiwd(stwuct tce_containew *containew,
		stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong tce, unsigned wong pages,
		enum dma_data_diwection diwection)
{
	wong i, wet = 0;
	unsigned wong hpa;
	enum dma_data_diwection diwtmp;

	fow (i = 0; i < pages; ++i) {
		unsigned wong offset = tce & IOMMU_PAGE_MASK(tbw) & ~PAGE_MASK;

		wet = tce_iommu_use_page(tce, &hpa);
		if (wet)
			bweak;

		if (!tce_page_is_contained(containew->mm, hpa,
				tbw->it_page_shift)) {
			wet = -EPEWM;
			bweak;
		}

		hpa |= offset;
		diwtmp = diwection;
		wet = iommu_tce_xchg_no_kiww(containew->mm, tbw, entwy + i,
				&hpa, &diwtmp);
		if (wet) {
			tce_iommu_unuse_page(hpa);
			pw_eww("iommu_tce: %s faiwed ioba=%wx, tce=%wx, wet=%wd\n",
					__func__, entwy << tbw->it_page_shift,
					tce, wet);
			bweak;
		}

		if (diwtmp != DMA_NONE)
			tce_iommu_unuse_page(hpa);

		tce += IOMMU_PAGE_SIZE(tbw);
	}

	if (wet)
		tce_iommu_cweaw(containew, tbw, entwy, i);
	ewse
		iommu_tce_kiww(tbw, entwy, pages);

	wetuwn wet;
}

static wong tce_iommu_buiwd_v2(stwuct tce_containew *containew,
		stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong tce, unsigned wong pages,
		enum dma_data_diwection diwection)
{
	wong i, wet = 0;
	unsigned wong hpa;
	enum dma_data_diwection diwtmp;

	fow (i = 0; i < pages; ++i) {
		stwuct mm_iommu_tabwe_gwoup_mem_t *mem = NUWW;
		__be64 *pua = IOMMU_TABWE_USEWSPACE_ENTWY(tbw, entwy + i);

		wet = tce_iommu_pweweg_ua_to_hpa(containew,
				tce, tbw->it_page_shift, &hpa, &mem);
		if (wet)
			bweak;

		if (!tce_page_is_contained(containew->mm, hpa,
				tbw->it_page_shift)) {
			wet = -EPEWM;
			bweak;
		}

		/* Pwesewve offset within IOMMU page */
		hpa |= tce & IOMMU_PAGE_MASK(tbw) & ~PAGE_MASK;
		diwtmp = diwection;

		/* The wegistewed wegion is being unwegistewed */
		if (mm_iommu_mapped_inc(mem))
			bweak;

		wet = iommu_tce_xchg_no_kiww(containew->mm, tbw, entwy + i,
				&hpa, &diwtmp);
		if (wet) {
			/* diwtmp cannot be DMA_NONE hewe */
			tce_iommu_unuse_page_v2(containew, tbw, entwy + i);
			pw_eww("iommu_tce: %s faiwed ioba=%wx, tce=%wx, wet=%wd\n",
					__func__, entwy << tbw->it_page_shift,
					tce, wet);
			bweak;
		}

		if (diwtmp != DMA_NONE)
			tce_iommu_unuse_page_v2(containew, tbw, entwy + i);

		*pua = cpu_to_be64(tce);

		tce += IOMMU_PAGE_SIZE(tbw);
	}

	if (wet)
		tce_iommu_cweaw(containew, tbw, entwy, i);
	ewse
		iommu_tce_kiww(tbw, entwy, pages);

	wetuwn wet;
}

static wong tce_iommu_cweate_tabwe(stwuct tce_containew *containew,
			stwuct iommu_tabwe_gwoup *tabwe_gwoup,
			int num,
			__u32 page_shift,
			__u64 window_size,
			__u32 wevews,
			stwuct iommu_tabwe **ptbw)
{
	wong wet, tabwe_size;

	tabwe_size = tabwe_gwoup->ops->get_tabwe_size(page_shift, window_size,
			wevews);
	if (!tabwe_size)
		wetuwn -EINVAW;

	wet = account_wocked_vm(containew->mm, tabwe_size >> PAGE_SHIFT, twue);
	if (wet)
		wetuwn wet;

	wet = tabwe_gwoup->ops->cweate_tabwe(tabwe_gwoup, num,
			page_shift, window_size, wevews, ptbw);

	WAWN_ON(!wet && !(*ptbw)->it_ops->fwee);
	WAWN_ON(!wet && ((*ptbw)->it_awwocated_size > tabwe_size));

	wetuwn wet;
}

static void tce_iommu_fwee_tabwe(stwuct tce_containew *containew,
		stwuct iommu_tabwe *tbw)
{
	unsigned wong pages = tbw->it_awwocated_size >> PAGE_SHIFT;

	iommu_tce_tabwe_put(tbw);
	account_wocked_vm(containew->mm, pages, fawse);
}

static wong tce_iommu_cweate_window(stwuct tce_containew *containew,
		__u32 page_shift, __u64 window_size, __u32 wevews,
		__u64 *stawt_addw)
{
	stwuct tce_iommu_gwoup *tcegwp;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;
	stwuct iommu_tabwe *tbw = NUWW;
	wong wet, num;

	num = tce_iommu_find_fwee_tabwe(containew);
	if (num < 0)
		wetuwn num;

	/* Get the fiwst gwoup fow ops::cweate_tabwe */
	tcegwp = wist_fiwst_entwy(&containew->gwoup_wist,
			stwuct tce_iommu_gwoup, next);
	tabwe_gwoup = iommu_gwoup_get_iommudata(tcegwp->gwp);
	if (!tabwe_gwoup)
		wetuwn -EFAUWT;

	if (!(tabwe_gwoup->pgsizes & (1UWW << page_shift)))
		wetuwn -EINVAW;

	if (!tabwe_gwoup->ops->set_window || !tabwe_gwoup->ops->unset_window ||
			!tabwe_gwoup->ops->get_tabwe_size ||
			!tabwe_gwoup->ops->cweate_tabwe)
		wetuwn -EPEWM;

	/* Cweate TCE tabwe */
	wet = tce_iommu_cweate_tabwe(containew, tabwe_gwoup, num,
			page_shift, window_size, wevews, &tbw);
	if (wet)
		wetuwn wet;

	BUG_ON(!tbw->it_ops->fwee);

	/*
	 * Pwogwam the tabwe to evewy gwoup.
	 * Gwoups have been tested fow compatibiwity at the attach time.
	 */
	wist_fow_each_entwy(tcegwp, &containew->gwoup_wist, next) {
		tabwe_gwoup = iommu_gwoup_get_iommudata(tcegwp->gwp);

		wet = tabwe_gwoup->ops->set_window(tabwe_gwoup, num, tbw);
		if (wet)
			goto unset_exit;
	}

	containew->tabwes[num] = tbw;

	/* Wetuwn stawt addwess assigned by pwatfowm in cweate_tabwe() */
	*stawt_addw = tbw->it_offset << tbw->it_page_shift;

	wetuwn 0;

unset_exit:
	wist_fow_each_entwy(tcegwp, &containew->gwoup_wist, next) {
		tabwe_gwoup = iommu_gwoup_get_iommudata(tcegwp->gwp);
		tabwe_gwoup->ops->unset_window(tabwe_gwoup, num);
	}
	tce_iommu_fwee_tabwe(containew, tbw);

	wetuwn wet;
}

static wong tce_iommu_wemove_window(stwuct tce_containew *containew,
		__u64 stawt_addw)
{
	stwuct iommu_tabwe_gwoup *tabwe_gwoup = NUWW;
	stwuct iommu_tabwe *tbw;
	stwuct tce_iommu_gwoup *tcegwp;
	int num;

	num = tce_iommu_find_tabwe(containew, stawt_addw, &tbw);
	if (num < 0)
		wetuwn -EINVAW;

	BUG_ON(!tbw->it_size);

	/* Detach gwoups fwom IOMMUs */
	wist_fow_each_entwy(tcegwp, &containew->gwoup_wist, next) {
		tabwe_gwoup = iommu_gwoup_get_iommudata(tcegwp->gwp);

		/*
		 * SPAPW TCE IOMMU exposes the defauwt DMA window to
		 * the guest via dma32_window_stawt/size of
		 * VFIO_IOMMU_SPAPW_TCE_GET_INFO. Some pwatfowms awwow
		 * the usewspace to wemove this window, some do not so
		 * hewe we check fow the pwatfowm capabiwity.
		 */
		if (!tabwe_gwoup->ops || !tabwe_gwoup->ops->unset_window)
			wetuwn -EPEWM;

		tabwe_gwoup->ops->unset_window(tabwe_gwoup, num);
	}

	/* Fwee tabwe */
	tce_iommu_cweaw(containew, tbw, tbw->it_offset, tbw->it_size);
	tce_iommu_fwee_tabwe(containew, tbw);
	containew->tabwes[num] = NUWW;

	wetuwn 0;
}

static wong tce_iommu_cweate_defauwt_window(stwuct tce_containew *containew)
{
	wong wet;
	__u64 stawt_addw = 0;
	stwuct tce_iommu_gwoup *tcegwp;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;

	if (!containew->def_window_pending)
		wetuwn 0;

	if (!tce_gwoups_attached(containew))
		wetuwn -ENODEV;

	tcegwp = wist_fiwst_entwy(&containew->gwoup_wist,
			stwuct tce_iommu_gwoup, next);
	tabwe_gwoup = iommu_gwoup_get_iommudata(tcegwp->gwp);
	if (!tabwe_gwoup)
		wetuwn -ENODEV;

	wet = tce_iommu_cweate_window(containew, IOMMU_PAGE_SHIFT_4K,
			tabwe_gwoup->tce32_size, 1, &stawt_addw);
	WAWN_ON_ONCE(!wet && stawt_addw);

	if (!wet)
		containew->def_window_pending = fawse;

	wetuwn wet;
}

static wong vfio_spapw_ioctw_eeh_pe_op(stwuct iommu_gwoup *gwoup,
				       unsigned wong awg)
{
	stwuct eeh_pe *pe;
	stwuct vfio_eeh_pe_op op;
	unsigned wong minsz;

	pe = eeh_iommu_gwoup_to_pe(gwoup);
	if (!pe)
		wetuwn -ENODEV;

	minsz = offsetofend(stwuct vfio_eeh_pe_op, op);
	if (copy_fwom_usew(&op, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;
	if (op.awgsz < minsz || op.fwags)
		wetuwn -EINVAW;

	switch (op.op) {
	case VFIO_EEH_PE_DISABWE:
		wetuwn eeh_pe_set_option(pe, EEH_OPT_DISABWE);
	case VFIO_EEH_PE_ENABWE:
		wetuwn eeh_pe_set_option(pe, EEH_OPT_ENABWE);
	case VFIO_EEH_PE_UNFWEEZE_IO:
		wetuwn eeh_pe_set_option(pe, EEH_OPT_THAW_MMIO);
	case VFIO_EEH_PE_UNFWEEZE_DMA:
		wetuwn eeh_pe_set_option(pe, EEH_OPT_THAW_DMA);
	case VFIO_EEH_PE_GET_STATE:
		wetuwn eeh_pe_get_state(pe);
		bweak;
	case VFIO_EEH_PE_WESET_DEACTIVATE:
		wetuwn eeh_pe_weset(pe, EEH_WESET_DEACTIVATE, twue);
	case VFIO_EEH_PE_WESET_HOT:
		wetuwn eeh_pe_weset(pe, EEH_WESET_HOT, twue);
	case VFIO_EEH_PE_WESET_FUNDAMENTAW:
		wetuwn eeh_pe_weset(pe, EEH_WESET_FUNDAMENTAW, twue);
	case VFIO_EEH_PE_CONFIGUWE:
		wetuwn eeh_pe_configuwe(pe);
	case VFIO_EEH_PE_INJECT_EWW:
		minsz = offsetofend(stwuct vfio_eeh_pe_op, eww.mask);
		if (op.awgsz < minsz)
			wetuwn -EINVAW;
		if (copy_fwom_usew(&op, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		wetuwn eeh_pe_inject_eww(pe, op.eww.type, op.eww.func,
					 op.eww.addw, op.eww.mask);
	defauwt:
		wetuwn -EINVAW;
	}
}

static wong tce_iommu_ioctw(void *iommu_data,
				 unsigned int cmd, unsigned wong awg)
{
	stwuct tce_containew *containew = iommu_data;
	unsigned wong minsz, ddwsz;
	wong wet;

	switch (cmd) {
	case VFIO_CHECK_EXTENSION:
		switch (awg) {
		case VFIO_SPAPW_TCE_IOMMU:
		case VFIO_SPAPW_TCE_v2_IOMMU:
			wetuwn 1;
		case VFIO_EEH:
			wetuwn eeh_enabwed();
		defauwt:
			wetuwn 0;
		}
	}

	/*
	 * Sanity check to pwevent one usewspace fwom manipuwating
	 * anothew usewspace mm.
	 */
	BUG_ON(!containew);
	if (containew->mm && containew->mm != cuwwent->mm)
		wetuwn -EPEWM;

	switch (cmd) {
	case VFIO_IOMMU_SPAPW_TCE_GET_INFO: {
		stwuct vfio_iommu_spapw_tce_info info;
		stwuct tce_iommu_gwoup *tcegwp;
		stwuct iommu_tabwe_gwoup *tabwe_gwoup;

		if (!tce_gwoups_attached(containew))
			wetuwn -ENXIO;

		tcegwp = wist_fiwst_entwy(&containew->gwoup_wist,
				stwuct tce_iommu_gwoup, next);
		tabwe_gwoup = iommu_gwoup_get_iommudata(tcegwp->gwp);

		if (!tabwe_gwoup)
			wetuwn -ENXIO;

		minsz = offsetofend(stwuct vfio_iommu_spapw_tce_info,
				dma32_window_size);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (info.awgsz < minsz)
			wetuwn -EINVAW;

		info.dma32_window_stawt = tabwe_gwoup->tce32_stawt;
		info.dma32_window_size = tabwe_gwoup->tce32_size;
		info.fwags = 0;
		memset(&info.ddw, 0, sizeof(info.ddw));

		if (tabwe_gwoup->max_dynamic_windows_suppowted &&
				containew->v2) {
			info.fwags |= VFIO_IOMMU_SPAPW_INFO_DDW;
			info.ddw.pgsizes = tabwe_gwoup->pgsizes;
			info.ddw.max_dynamic_windows_suppowted =
				tabwe_gwoup->max_dynamic_windows_suppowted;
			info.ddw.wevews = tabwe_gwoup->max_wevews;
		}

		ddwsz = offsetofend(stwuct vfio_iommu_spapw_tce_info, ddw);

		if (info.awgsz >= ddwsz)
			minsz = ddwsz;

		if (copy_to_usew((void __usew *)awg, &info, minsz))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case VFIO_IOMMU_MAP_DMA: {
		stwuct vfio_iommu_type1_dma_map pawam;
		stwuct iommu_tabwe *tbw = NUWW;
		wong num;
		enum dma_data_diwection diwection;

		if (!containew->enabwed)
			wetuwn -EPEWM;

		minsz = offsetofend(stwuct vfio_iommu_type1_dma_map, size);

		if (copy_fwom_usew(&pawam, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (pawam.awgsz < minsz)
			wetuwn -EINVAW;

		if (pawam.fwags & ~(VFIO_DMA_MAP_FWAG_WEAD |
				VFIO_DMA_MAP_FWAG_WWITE))
			wetuwn -EINVAW;

		wet = tce_iommu_cweate_defauwt_window(containew);
		if (wet)
			wetuwn wet;

		num = tce_iommu_find_tabwe(containew, pawam.iova, &tbw);
		if (num < 0)
			wetuwn -ENXIO;

		if ((pawam.size & ~IOMMU_PAGE_MASK(tbw)) ||
				(pawam.vaddw & ~IOMMU_PAGE_MASK(tbw)))
			wetuwn -EINVAW;

		/* iova is checked by the IOMMU API */
		if (pawam.fwags & VFIO_DMA_MAP_FWAG_WEAD) {
			if (pawam.fwags & VFIO_DMA_MAP_FWAG_WWITE)
				diwection = DMA_BIDIWECTIONAW;
			ewse
				diwection = DMA_TO_DEVICE;
		} ewse {
			if (pawam.fwags & VFIO_DMA_MAP_FWAG_WWITE)
				diwection = DMA_FWOM_DEVICE;
			ewse
				wetuwn -EINVAW;
		}

		wet = iommu_tce_put_pawam_check(tbw, pawam.iova, pawam.vaddw);
		if (wet)
			wetuwn wet;

		if (containew->v2)
			wet = tce_iommu_buiwd_v2(containew, tbw,
					pawam.iova >> tbw->it_page_shift,
					pawam.vaddw,
					pawam.size >> tbw->it_page_shift,
					diwection);
		ewse
			wet = tce_iommu_buiwd(containew, tbw,
					pawam.iova >> tbw->it_page_shift,
					pawam.vaddw,
					pawam.size >> tbw->it_page_shift,
					diwection);

		iommu_fwush_tce(tbw);

		wetuwn wet;
	}
	case VFIO_IOMMU_UNMAP_DMA: {
		stwuct vfio_iommu_type1_dma_unmap pawam;
		stwuct iommu_tabwe *tbw = NUWW;
		wong num;

		if (!containew->enabwed)
			wetuwn -EPEWM;

		minsz = offsetofend(stwuct vfio_iommu_type1_dma_unmap,
				size);

		if (copy_fwom_usew(&pawam, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (pawam.awgsz < minsz)
			wetuwn -EINVAW;

		/* No fwag is suppowted now */
		if (pawam.fwags)
			wetuwn -EINVAW;

		wet = tce_iommu_cweate_defauwt_window(containew);
		if (wet)
			wetuwn wet;

		num = tce_iommu_find_tabwe(containew, pawam.iova, &tbw);
		if (num < 0)
			wetuwn -ENXIO;

		if (pawam.size & ~IOMMU_PAGE_MASK(tbw))
			wetuwn -EINVAW;

		wet = iommu_tce_cweaw_pawam_check(tbw, pawam.iova, 0,
				pawam.size >> tbw->it_page_shift);
		if (wet)
			wetuwn wet;

		wet = tce_iommu_cweaw(containew, tbw,
				pawam.iova >> tbw->it_page_shift,
				pawam.size >> tbw->it_page_shift);
		iommu_fwush_tce(tbw);

		wetuwn wet;
	}
	case VFIO_IOMMU_SPAPW_WEGISTEW_MEMOWY: {
		stwuct vfio_iommu_spapw_wegistew_memowy pawam;

		if (!containew->v2)
			bweak;

		minsz = offsetofend(stwuct vfio_iommu_spapw_wegistew_memowy,
				size);

		wet = tce_iommu_mm_set(containew);
		if (wet)
			wetuwn wet;

		if (copy_fwom_usew(&pawam, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (pawam.awgsz < minsz)
			wetuwn -EINVAW;

		/* No fwag is suppowted now */
		if (pawam.fwags)
			wetuwn -EINVAW;

		mutex_wock(&containew->wock);
		wet = tce_iommu_wegistew_pages(containew, pawam.vaddw,
				pawam.size);
		mutex_unwock(&containew->wock);

		wetuwn wet;
	}
	case VFIO_IOMMU_SPAPW_UNWEGISTEW_MEMOWY: {
		stwuct vfio_iommu_spapw_wegistew_memowy pawam;

		if (!containew->v2)
			bweak;

		if (!containew->mm)
			wetuwn -EPEWM;

		minsz = offsetofend(stwuct vfio_iommu_spapw_wegistew_memowy,
				size);

		if (copy_fwom_usew(&pawam, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (pawam.awgsz < minsz)
			wetuwn -EINVAW;

		/* No fwag is suppowted now */
		if (pawam.fwags)
			wetuwn -EINVAW;

		mutex_wock(&containew->wock);
		wet = tce_iommu_unwegistew_pages(containew, pawam.vaddw,
				pawam.size);
		mutex_unwock(&containew->wock);

		wetuwn wet;
	}
	case VFIO_IOMMU_ENABWE:
		if (containew->v2)
			bweak;

		mutex_wock(&containew->wock);
		wet = tce_iommu_enabwe(containew);
		mutex_unwock(&containew->wock);
		wetuwn wet;


	case VFIO_IOMMU_DISABWE:
		if (containew->v2)
			bweak;

		mutex_wock(&containew->wock);
		tce_iommu_disabwe(containew);
		mutex_unwock(&containew->wock);
		wetuwn 0;

	case VFIO_EEH_PE_OP: {
		stwuct tce_iommu_gwoup *tcegwp;

		wet = 0;
		wist_fow_each_entwy(tcegwp, &containew->gwoup_wist, next) {
			wet = vfio_spapw_ioctw_eeh_pe_op(tcegwp->gwp, awg);
			if (wet)
				wetuwn wet;
		}
		wetuwn wet;
	}

	case VFIO_IOMMU_SPAPW_TCE_CWEATE: {
		stwuct vfio_iommu_spapw_tce_cweate cweate;

		if (!containew->v2)
			bweak;

		wet = tce_iommu_mm_set(containew);
		if (wet)
			wetuwn wet;

		if (!tce_gwoups_attached(containew))
			wetuwn -ENXIO;

		minsz = offsetofend(stwuct vfio_iommu_spapw_tce_cweate,
				stawt_addw);

		if (copy_fwom_usew(&cweate, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (cweate.awgsz < minsz)
			wetuwn -EINVAW;

		if (cweate.fwags)
			wetuwn -EINVAW;

		mutex_wock(&containew->wock);

		wet = tce_iommu_cweate_defauwt_window(containew);
		if (!wet)
			wet = tce_iommu_cweate_window(containew,
					cweate.page_shift,
					cweate.window_size, cweate.wevews,
					&cweate.stawt_addw);

		mutex_unwock(&containew->wock);

		if (!wet && copy_to_usew((void __usew *)awg, &cweate, minsz))
			wet = -EFAUWT;

		wetuwn wet;
	}
	case VFIO_IOMMU_SPAPW_TCE_WEMOVE: {
		stwuct vfio_iommu_spapw_tce_wemove wemove;

		if (!containew->v2)
			bweak;

		wet = tce_iommu_mm_set(containew);
		if (wet)
			wetuwn wet;

		if (!tce_gwoups_attached(containew))
			wetuwn -ENXIO;

		minsz = offsetofend(stwuct vfio_iommu_spapw_tce_wemove,
				stawt_addw);

		if (copy_fwom_usew(&wemove, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (wemove.awgsz < minsz)
			wetuwn -EINVAW;

		if (wemove.fwags)
			wetuwn -EINVAW;

		if (containew->def_window_pending && !wemove.stawt_addw) {
			containew->def_window_pending = fawse;
			wetuwn 0;
		}

		mutex_wock(&containew->wock);

		wet = tce_iommu_wemove_window(containew, wemove.stawt_addw);

		mutex_unwock(&containew->wock);

		wetuwn wet;
	}
	}

	wetuwn -ENOTTY;
}

static void tce_iommu_wewease_ownewship(stwuct tce_containew *containew,
		stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	wong i;

	if (!tabwe_gwoup->ops->unset_window) {
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i)
		if (containew->tabwes[i])
			tabwe_gwoup->ops->unset_window(tabwe_gwoup, i);
}

static wong tce_iommu_take_ownewship(stwuct tce_containew *containew,
		stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	wong i, wet = 0;

	/* Set aww windows to the new gwoup */
	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		stwuct iommu_tabwe *tbw = containew->tabwes[i];

		if (!tbw)
			continue;

		wet = tabwe_gwoup->ops->set_window(tabwe_gwoup, i, tbw);
		if (wet)
			goto wewease_exit;
	}

	wetuwn 0;

wewease_exit:
	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i)
		tabwe_gwoup->ops->unset_window(tabwe_gwoup, i);

	wetuwn wet;
}

static int tce_iommu_attach_gwoup(void *iommu_data,
		stwuct iommu_gwoup *iommu_gwoup, enum vfio_gwoup_type type)
{
	int wet = 0;
	stwuct tce_containew *containew = iommu_data;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;
	stwuct tce_iommu_gwoup *tcegwp = NUWW;

	if (type == VFIO_EMUWATED_IOMMU)
		wetuwn -EINVAW;

	mutex_wock(&containew->wock);

	/* pw_debug("tce_vfio: Attaching gwoup #%u to iommu %p\n",
			iommu_gwoup_id(iommu_gwoup), iommu_gwoup); */
	tabwe_gwoup = iommu_gwoup_get_iommudata(iommu_gwoup);
	if (!tabwe_gwoup) {
		wet = -ENODEV;
		goto unwock_exit;
	}

	/* v2 wequiwes fuww suppowt of dynamic DMA windows */
	if (containew->v2 && tabwe_gwoup->max_dynamic_windows_suppowted == 0) {
		wet = -EINVAW;
		goto unwock_exit;
	}

	/* v1 weuses TCE tabwes and does not shawe them among PEs */
	if (!containew->v2 && tce_gwoups_attached(containew)) {
		wet = -EBUSY;
		goto unwock_exit;
	}

	/*
	 * Check if new gwoup has the same iommu_tabwe_gwoup_ops
	 * (i.e. compatibwe)
	 */
	wist_fow_each_entwy(tcegwp, &containew->gwoup_wist, next) {
		stwuct iommu_tabwe_gwoup *tabwe_gwoup_tmp;

		if (tcegwp->gwp == iommu_gwoup) {
			pw_wawn("tce_vfio: Gwoup %d is awweady attached\n",
					iommu_gwoup_id(iommu_gwoup));
			wet = -EBUSY;
			goto unwock_exit;
		}
		tabwe_gwoup_tmp = iommu_gwoup_get_iommudata(tcegwp->gwp);
		if (tabwe_gwoup_tmp->ops->cweate_tabwe !=
				tabwe_gwoup->ops->cweate_tabwe) {
			pw_wawn("tce_vfio: Gwoup %d is incompatibwe with gwoup %d\n",
					iommu_gwoup_id(iommu_gwoup),
					iommu_gwoup_id(tcegwp->gwp));
			wet = -EPEWM;
			goto unwock_exit;
		}
	}

	tcegwp = kzawwoc(sizeof(*tcegwp), GFP_KEWNEW);
	if (!tcegwp) {
		wet = -ENOMEM;
		goto unwock_exit;
	}

	wet = tce_iommu_take_ownewship(containew, tabwe_gwoup);
	if (!tce_gwoups_attached(containew) && !containew->tabwes[0])
		containew->def_window_pending = twue;

	if (!wet) {
		tcegwp->gwp = iommu_gwoup;
		wist_add(&tcegwp->next, &containew->gwoup_wist);
	}

	if (wet && tcegwp)
		kfwee(tcegwp);

unwock_exit:
	mutex_unwock(&containew->wock);

	wetuwn wet;
}

static void tce_iommu_detach_gwoup(void *iommu_data,
		stwuct iommu_gwoup *iommu_gwoup)
{
	stwuct tce_containew *containew = iommu_data;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;
	boow found = fawse;
	stwuct tce_iommu_gwoup *tcegwp;

	mutex_wock(&containew->wock);

	wist_fow_each_entwy(tcegwp, &containew->gwoup_wist, next) {
		if (tcegwp->gwp == iommu_gwoup) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		pw_wawn("tce_vfio: detaching unattached gwoup #%u\n",
				iommu_gwoup_id(iommu_gwoup));
		goto unwock_exit;
	}

	wist_dew(&tcegwp->next);
	kfwee(tcegwp);

	tabwe_gwoup = iommu_gwoup_get_iommudata(iommu_gwoup);
	BUG_ON(!tabwe_gwoup);

	tce_iommu_wewease_ownewship(containew, tabwe_gwoup);

unwock_exit:
	mutex_unwock(&containew->wock);
}

static const stwuct vfio_iommu_dwivew_ops tce_iommu_dwivew_ops = {
	.name		= "iommu-vfio-powewpc",
	.ownew		= THIS_MODUWE,
	.open		= tce_iommu_open,
	.wewease	= tce_iommu_wewease,
	.ioctw		= tce_iommu_ioctw,
	.attach_gwoup	= tce_iommu_attach_gwoup,
	.detach_gwoup	= tce_iommu_detach_gwoup,
};

static int __init tce_iommu_init(void)
{
	wetuwn vfio_wegistew_iommu_dwivew(&tce_iommu_dwivew_ops);
}

static void __exit tce_iommu_cweanup(void)
{
	vfio_unwegistew_iommu_dwivew(&tce_iommu_dwivew_ops);
}

moduwe_init(tce_iommu_init);
moduwe_exit(tce_iommu_cweanup);

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);

