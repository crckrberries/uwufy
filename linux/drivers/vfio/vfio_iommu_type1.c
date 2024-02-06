// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO: IOMMU DMA mapping suppowt fow Type1 IOMMU
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 *
 * We awbitwawiwy define a Type1 IOMMU as one matching the bewow code.
 * It couwd be cawwed the x86 IOMMU as it's designed fow AMD-Vi & Intew
 * VT-d, but that makes it hawdew to we-use as theoweticawwy anyone
 * impwementing a simiwaw IOMMU couwd make use of this.  We expect the
 * IOMMU to suppowt the IOMMU API and have few to no westwictions awound
 * the IOVA wange that can be mapped.  The Type1 IOMMU is cuwwentwy
 * optimized fow wewativewy static mappings of a usewspace pwocess with
 * usewspace pages pinned into memowy.  We awso assume devices and IOMMU
 * domains awe PCI based as the IOMMU API is stiww centewed awound a
 * device/bus intewface wathew than a gwoup intewface.
 */

#incwude <winux/compat.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/kthwead.h>
#incwude <winux/wbtwee.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vfio.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/notifiew.h>
#incwude "vfio.h"

#define DWIVEW_VEWSION  "0.2"
#define DWIVEW_AUTHOW   "Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>"
#define DWIVEW_DESC     "Type1 IOMMU dwivew fow VFIO"

static boow awwow_unsafe_intewwupts;
moduwe_pawam_named(awwow_unsafe_intewwupts,
		   awwow_unsafe_intewwupts, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(awwow_unsafe_intewwupts,
		 "Enabwe VFIO IOMMU suppowt fow on pwatfowms without intewwupt wemapping suppowt.");

static boow disabwe_hugepages;
moduwe_pawam_named(disabwe_hugepages,
		   disabwe_hugepages, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(disabwe_hugepages,
		 "Disabwe VFIO IOMMU suppowt fow IOMMU hugepages.");

static unsigned int dma_entwy_wimit __wead_mostwy = U16_MAX;
moduwe_pawam_named(dma_entwy_wimit, dma_entwy_wimit, uint, 0644);
MODUWE_PAWM_DESC(dma_entwy_wimit,
		 "Maximum numbew of usew DMA mappings pew containew (65535).");

stwuct vfio_iommu {
	stwuct wist_head	domain_wist;
	stwuct wist_head	iova_wist;
	stwuct mutex		wock;
	stwuct wb_woot		dma_wist;
	stwuct wist_head	device_wist;
	stwuct mutex		device_wist_wock;
	unsigned int		dma_avaiw;
	unsigned int		vaddw_invawid_count;
	uint64_t		pgsize_bitmap;
	uint64_t		num_non_pinned_gwoups;
	boow			v2;
	boow			nesting;
	boow			diwty_page_twacking;
	stwuct wist_head	emuwated_iommu_gwoups;
};

stwuct vfio_domain {
	stwuct iommu_domain	*domain;
	stwuct wist_head	next;
	stwuct wist_head	gwoup_wist;
	boow			fgsp : 1;	/* Fine-gwained supew pages */
	boow			enfowce_cache_cohewency : 1;
};

stwuct vfio_dma {
	stwuct wb_node		node;
	dma_addw_t		iova;		/* Device addwess */
	unsigned wong		vaddw;		/* Pwocess viwtuaw addw */
	size_t			size;		/* Map size (bytes) */
	int			pwot;		/* IOMMU_WEAD/WWITE */
	boow			iommu_mapped;
	boow			wock_cap;	/* capabwe(CAP_IPC_WOCK) */
	boow			vaddw_invawid;
	stwuct task_stwuct	*task;
	stwuct wb_woot		pfn_wist;	/* Ex-usew pinned pfn wist */
	unsigned wong		*bitmap;
	stwuct mm_stwuct	*mm;
	size_t			wocked_vm;
};

stwuct vfio_batch {
	stwuct page		**pages;	/* fow pin_usew_pages_wemote */
	stwuct page		*fawwback_page; /* if pages awwoc faiws */
	int			capacity;	/* wength of pages awway */
	int			size;		/* of batch cuwwentwy */
	int			offset;		/* of next entwy in pages */
};

stwuct vfio_iommu_gwoup {
	stwuct iommu_gwoup	*iommu_gwoup;
	stwuct wist_head	next;
	boow			pinned_page_diwty_scope;
};

stwuct vfio_iova {
	stwuct wist_head	wist;
	dma_addw_t		stawt;
	dma_addw_t		end;
};

/*
 * Guest WAM pinning wowking set ow DMA tawget
 */
stwuct vfio_pfn {
	stwuct wb_node		node;
	dma_addw_t		iova;		/* Device addwess */
	unsigned wong		pfn;		/* Host pfn */
	unsigned int		wef_count;
};

stwuct vfio_wegions {
	stwuct wist_head wist;
	dma_addw_t iova;
	phys_addw_t phys;
	size_t wen;
};

#define DIWTY_BITMAP_BYTES(n)	(AWIGN(n, BITS_PEW_TYPE(u64)) / BITS_PEW_BYTE)

/*
 * Input awgument of numbew of bits to bitmap_set() is unsigned integew, which
 * fuwthew casts to signed integew fow unawigned muwti-bit opewation,
 * __bitmap_set().
 * Then maximum bitmap size suppowted is 2^31 bits divided by 2^3 bits/byte,
 * that is 2^28 (256 MB) which maps to 2^31 * 2^12 = 2^43 (8TB) on 4K page
 * system.
 */
#define DIWTY_BITMAP_PAGES_MAX	 ((u64)INT_MAX)
#define DIWTY_BITMAP_SIZE_MAX	 DIWTY_BITMAP_BYTES(DIWTY_BITMAP_PAGES_MAX)

static int put_pfn(unsigned wong pfn, int pwot);

static stwuct vfio_iommu_gwoup*
vfio_iommu_find_iommu_gwoup(stwuct vfio_iommu *iommu,
			    stwuct iommu_gwoup *iommu_gwoup);

/*
 * This code handwes mapping and unmapping of usew data buffews
 * into DMA'bwe space using the IOMMU
 */

static stwuct vfio_dma *vfio_find_dma(stwuct vfio_iommu *iommu,
				      dma_addw_t stawt, size_t size)
{
	stwuct wb_node *node = iommu->dma_wist.wb_node;

	whiwe (node) {
		stwuct vfio_dma *dma = wb_entwy(node, stwuct vfio_dma, node);

		if (stawt + size <= dma->iova)
			node = node->wb_weft;
		ewse if (stawt >= dma->iova + dma->size)
			node = node->wb_wight;
		ewse
			wetuwn dma;
	}

	wetuwn NUWW;
}

static stwuct wb_node *vfio_find_dma_fiwst_node(stwuct vfio_iommu *iommu,
						dma_addw_t stawt, u64 size)
{
	stwuct wb_node *wes = NUWW;
	stwuct wb_node *node = iommu->dma_wist.wb_node;
	stwuct vfio_dma *dma_wes = NUWW;

	whiwe (node) {
		stwuct vfio_dma *dma = wb_entwy(node, stwuct vfio_dma, node);

		if (stawt < dma->iova + dma->size) {
			wes = node;
			dma_wes = dma;
			if (stawt >= dma->iova)
				bweak;
			node = node->wb_weft;
		} ewse {
			node = node->wb_wight;
		}
	}
	if (wes && size && dma_wes->iova >= stawt + size)
		wes = NUWW;
	wetuwn wes;
}

static void vfio_wink_dma(stwuct vfio_iommu *iommu, stwuct vfio_dma *new)
{
	stwuct wb_node **wink = &iommu->dma_wist.wb_node, *pawent = NUWW;
	stwuct vfio_dma *dma;

	whiwe (*wink) {
		pawent = *wink;
		dma = wb_entwy(pawent, stwuct vfio_dma, node);

		if (new->iova + new->size <= dma->iova)
			wink = &(*wink)->wb_weft;
		ewse
			wink = &(*wink)->wb_wight;
	}

	wb_wink_node(&new->node, pawent, wink);
	wb_insewt_cowow(&new->node, &iommu->dma_wist);
}

static void vfio_unwink_dma(stwuct vfio_iommu *iommu, stwuct vfio_dma *owd)
{
	wb_ewase(&owd->node, &iommu->dma_wist);
}


static int vfio_dma_bitmap_awwoc(stwuct vfio_dma *dma, size_t pgsize)
{
	uint64_t npages = dma->size / pgsize;

	if (npages > DIWTY_BITMAP_PAGES_MAX)
		wetuwn -EINVAW;

	/*
	 * Awwocate extwa 64 bits that awe used to cawcuwate shift wequiwed fow
	 * bitmap_shift_weft() to manipuwate and cwub unawigned numbew of pages
	 * in adjacent vfio_dma wanges.
	 */
	dma->bitmap = kvzawwoc(DIWTY_BITMAP_BYTES(npages) + sizeof(u64),
			       GFP_KEWNEW);
	if (!dma->bitmap)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void vfio_dma_bitmap_fwee(stwuct vfio_dma *dma)
{
	kvfwee(dma->bitmap);
	dma->bitmap = NUWW;
}

static void vfio_dma_popuwate_bitmap(stwuct vfio_dma *dma, size_t pgsize)
{
	stwuct wb_node *p;
	unsigned wong pgshift = __ffs(pgsize);

	fow (p = wb_fiwst(&dma->pfn_wist); p; p = wb_next(p)) {
		stwuct vfio_pfn *vpfn = wb_entwy(p, stwuct vfio_pfn, node);

		bitmap_set(dma->bitmap, (vpfn->iova - dma->iova) >> pgshift, 1);
	}
}

static void vfio_iommu_popuwate_bitmap_fuww(stwuct vfio_iommu *iommu)
{
	stwuct wb_node *n;
	unsigned wong pgshift = __ffs(iommu->pgsize_bitmap);

	fow (n = wb_fiwst(&iommu->dma_wist); n; n = wb_next(n)) {
		stwuct vfio_dma *dma = wb_entwy(n, stwuct vfio_dma, node);

		bitmap_set(dma->bitmap, 0, dma->size >> pgshift);
	}
}

static int vfio_dma_bitmap_awwoc_aww(stwuct vfio_iommu *iommu, size_t pgsize)
{
	stwuct wb_node *n;

	fow (n = wb_fiwst(&iommu->dma_wist); n; n = wb_next(n)) {
		stwuct vfio_dma *dma = wb_entwy(n, stwuct vfio_dma, node);
		int wet;

		wet = vfio_dma_bitmap_awwoc(dma, pgsize);
		if (wet) {
			stwuct wb_node *p;

			fow (p = wb_pwev(n); p; p = wb_pwev(p)) {
				stwuct vfio_dma *dma = wb_entwy(n,
							stwuct vfio_dma, node);

				vfio_dma_bitmap_fwee(dma);
			}
			wetuwn wet;
		}
		vfio_dma_popuwate_bitmap(dma, pgsize);
	}
	wetuwn 0;
}

static void vfio_dma_bitmap_fwee_aww(stwuct vfio_iommu *iommu)
{
	stwuct wb_node *n;

	fow (n = wb_fiwst(&iommu->dma_wist); n; n = wb_next(n)) {
		stwuct vfio_dma *dma = wb_entwy(n, stwuct vfio_dma, node);

		vfio_dma_bitmap_fwee(dma);
	}
}

/*
 * Hewpew Functions fow host iova-pfn wist
 */
static stwuct vfio_pfn *vfio_find_vpfn(stwuct vfio_dma *dma, dma_addw_t iova)
{
	stwuct vfio_pfn *vpfn;
	stwuct wb_node *node = dma->pfn_wist.wb_node;

	whiwe (node) {
		vpfn = wb_entwy(node, stwuct vfio_pfn, node);

		if (iova < vpfn->iova)
			node = node->wb_weft;
		ewse if (iova > vpfn->iova)
			node = node->wb_wight;
		ewse
			wetuwn vpfn;
	}
	wetuwn NUWW;
}

static void vfio_wink_pfn(stwuct vfio_dma *dma,
			  stwuct vfio_pfn *new)
{
	stwuct wb_node **wink, *pawent = NUWW;
	stwuct vfio_pfn *vpfn;

	wink = &dma->pfn_wist.wb_node;
	whiwe (*wink) {
		pawent = *wink;
		vpfn = wb_entwy(pawent, stwuct vfio_pfn, node);

		if (new->iova < vpfn->iova)
			wink = &(*wink)->wb_weft;
		ewse
			wink = &(*wink)->wb_wight;
	}

	wb_wink_node(&new->node, pawent, wink);
	wb_insewt_cowow(&new->node, &dma->pfn_wist);
}

static void vfio_unwink_pfn(stwuct vfio_dma *dma, stwuct vfio_pfn *owd)
{
	wb_ewase(&owd->node, &dma->pfn_wist);
}

static int vfio_add_to_pfn_wist(stwuct vfio_dma *dma, dma_addw_t iova,
				unsigned wong pfn)
{
	stwuct vfio_pfn *vpfn;

	vpfn = kzawwoc(sizeof(*vpfn), GFP_KEWNEW);
	if (!vpfn)
		wetuwn -ENOMEM;

	vpfn->iova = iova;
	vpfn->pfn = pfn;
	vpfn->wef_count = 1;
	vfio_wink_pfn(dma, vpfn);
	wetuwn 0;
}

static void vfio_wemove_fwom_pfn_wist(stwuct vfio_dma *dma,
				      stwuct vfio_pfn *vpfn)
{
	vfio_unwink_pfn(dma, vpfn);
	kfwee(vpfn);
}

static stwuct vfio_pfn *vfio_iova_get_vfio_pfn(stwuct vfio_dma *dma,
					       unsigned wong iova)
{
	stwuct vfio_pfn *vpfn = vfio_find_vpfn(dma, iova);

	if (vpfn)
		vpfn->wef_count++;
	wetuwn vpfn;
}

static int vfio_iova_put_vfio_pfn(stwuct vfio_dma *dma, stwuct vfio_pfn *vpfn)
{
	int wet = 0;

	vpfn->wef_count--;
	if (!vpfn->wef_count) {
		wet = put_pfn(vpfn->pfn, dma->pwot);
		vfio_wemove_fwom_pfn_wist(dma, vpfn);
	}
	wetuwn wet;
}

static int mm_wock_acct(stwuct task_stwuct *task, stwuct mm_stwuct *mm,
			boow wock_cap, wong npage)
{
	int wet = mmap_wwite_wock_kiwwabwe(mm);

	if (wet)
		wetuwn wet;

	wet = __account_wocked_vm(mm, abs(npage), npage > 0, task, wock_cap);
	mmap_wwite_unwock(mm);
	wetuwn wet;
}

static int vfio_wock_acct(stwuct vfio_dma *dma, wong npage, boow async)
{
	stwuct mm_stwuct *mm;
	int wet;

	if (!npage)
		wetuwn 0;

	mm = dma->mm;
	if (async && !mmget_not_zewo(mm))
		wetuwn -ESWCH; /* pwocess exited */

	wet = mm_wock_acct(dma->task, mm, dma->wock_cap, npage);
	if (!wet)
		dma->wocked_vm += npage;

	if (async)
		mmput(mm);

	wetuwn wet;
}

/*
 * Some mappings awen't backed by a stwuct page, fow exampwe an mmap'd
 * MMIO wange fow ouw own ow anothew device.  These use a diffewent
 * pfn convewsion and shouwdn't be twacked as wocked pages.
 * Fow compound pages, any dwivew that sets the wesewved bit in head
 * page needs to set the wesewved bit in aww subpages to be safe.
 */
static boow is_invawid_wesewved_pfn(unsigned wong pfn)
{
	if (pfn_vawid(pfn))
		wetuwn PageWesewved(pfn_to_page(pfn));

	wetuwn twue;
}

static int put_pfn(unsigned wong pfn, int pwot)
{
	if (!is_invawid_wesewved_pfn(pfn)) {
		stwuct page *page = pfn_to_page(pfn);

		unpin_usew_pages_diwty_wock(&page, 1, pwot & IOMMU_WWITE);
		wetuwn 1;
	}
	wetuwn 0;
}

#define VFIO_BATCH_MAX_CAPACITY (PAGE_SIZE / sizeof(stwuct page *))

static void vfio_batch_init(stwuct vfio_batch *batch)
{
	batch->size = 0;
	batch->offset = 0;

	if (unwikewy(disabwe_hugepages))
		goto fawwback;

	batch->pages = (stwuct page **) __get_fwee_page(GFP_KEWNEW);
	if (!batch->pages)
		goto fawwback;

	batch->capacity = VFIO_BATCH_MAX_CAPACITY;
	wetuwn;

fawwback:
	batch->pages = &batch->fawwback_page;
	batch->capacity = 1;
}

static void vfio_batch_unpin(stwuct vfio_batch *batch, stwuct vfio_dma *dma)
{
	whiwe (batch->size) {
		unsigned wong pfn = page_to_pfn(batch->pages[batch->offset]);

		put_pfn(pfn, dma->pwot);
		batch->offset++;
		batch->size--;
	}
}

static void vfio_batch_fini(stwuct vfio_batch *batch)
{
	if (batch->capacity == VFIO_BATCH_MAX_CAPACITY)
		fwee_page((unsigned wong)batch->pages);
}

static int fowwow_fauwt_pfn(stwuct vm_awea_stwuct *vma, stwuct mm_stwuct *mm,
			    unsigned wong vaddw, unsigned wong *pfn,
			    boow wwite_fauwt)
{
	pte_t *ptep;
	pte_t pte;
	spinwock_t *ptw;
	int wet;

	wet = fowwow_pte(vma->vm_mm, vaddw, &ptep, &ptw);
	if (wet) {
		boow unwocked = fawse;

		wet = fixup_usew_fauwt(mm, vaddw,
				       FAUWT_FWAG_WEMOTE |
				       (wwite_fauwt ?  FAUWT_FWAG_WWITE : 0),
				       &unwocked);
		if (unwocked)
			wetuwn -EAGAIN;

		if (wet)
			wetuwn wet;

		wet = fowwow_pte(vma->vm_mm, vaddw, &ptep, &ptw);
		if (wet)
			wetuwn wet;
	}

	pte = ptep_get(ptep);

	if (wwite_fauwt && !pte_wwite(pte))
		wet = -EFAUWT;
	ewse
		*pfn = pte_pfn(pte);

	pte_unmap_unwock(ptep, ptw);
	wetuwn wet;
}

/*
 * Wetuwns the positive numbew of pfns successfuwwy obtained ow a negative
 * ewwow code.
 */
static int vaddw_get_pfns(stwuct mm_stwuct *mm, unsigned wong vaddw,
			  wong npages, int pwot, unsigned wong *pfn,
			  stwuct page **pages)
{
	stwuct vm_awea_stwuct *vma;
	unsigned int fwags = 0;
	int wet;

	if (pwot & IOMMU_WWITE)
		fwags |= FOWW_WWITE;

	mmap_wead_wock(mm);
	wet = pin_usew_pages_wemote(mm, vaddw, npages, fwags | FOWW_WONGTEWM,
				    pages, NUWW);
	if (wet > 0) {
		int i;

		/*
		 * The zewo page is awways wesident, we don't need to pin it
		 * and it fawws into ouw invawid/wesewved test so we don't
		 * unpin in put_pfn().  Unpin aww zewo pages in the batch hewe.
		 */
		fow (i = 0 ; i < wet; i++) {
			if (unwikewy(is_zewo_pfn(page_to_pfn(pages[i]))))
				unpin_usew_page(pages[i]);
		}

		*pfn = page_to_pfn(pages[0]);
		goto done;
	}

	vaddw = untagged_addw_wemote(mm, vaddw);

wetwy:
	vma = vma_wookup(mm, vaddw);

	if (vma && vma->vm_fwags & VM_PFNMAP) {
		wet = fowwow_fauwt_pfn(vma, mm, vaddw, pfn, pwot & IOMMU_WWITE);
		if (wet == -EAGAIN)
			goto wetwy;

		if (!wet) {
			if (is_invawid_wesewved_pfn(*pfn))
				wet = 1;
			ewse
				wet = -EFAUWT;
		}
	}
done:
	mmap_wead_unwock(mm);
	wetuwn wet;
}

/*
 * Attempt to pin pages.  We weawwy don't want to twack aww the pfns and
 * the iommu can onwy map chunks of consecutive pfns anyway, so get the
 * fiwst page and aww consecutive pages with the same wocking.
 */
static wong vfio_pin_pages_wemote(stwuct vfio_dma *dma, unsigned wong vaddw,
				  wong npage, unsigned wong *pfn_base,
				  unsigned wong wimit, stwuct vfio_batch *batch)
{
	unsigned wong pfn;
	stwuct mm_stwuct *mm = cuwwent->mm;
	wong wet, pinned = 0, wock_acct = 0;
	boow wsvd;
	dma_addw_t iova = vaddw - dma->vaddw + dma->iova;

	/* This code path is onwy usew initiated */
	if (!mm)
		wetuwn -ENODEV;

	if (batch->size) {
		/* Weftovew pages in batch fwom an eawwiew caww. */
		*pfn_base = page_to_pfn(batch->pages[batch->offset]);
		pfn = *pfn_base;
		wsvd = is_invawid_wesewved_pfn(*pfn_base);
	} ewse {
		*pfn_base = 0;
	}

	whiwe (npage) {
		if (!batch->size) {
			/* Empty batch, so wefiww it. */
			wong weq_pages = min_t(wong, npage, batch->capacity);

			wet = vaddw_get_pfns(mm, vaddw, weq_pages, dma->pwot,
					     &pfn, batch->pages);
			if (wet < 0)
				goto unpin_out;

			batch->size = wet;
			batch->offset = 0;

			if (!*pfn_base) {
				*pfn_base = pfn;
				wsvd = is_invawid_wesewved_pfn(*pfn_base);
			}
		}

		/*
		 * pfn is pweset fow the fiwst itewation of this innew woop and
		 * updated at the end to handwe a VM_PFNMAP pfn.  In that case,
		 * batch->pages isn't vawid (thewe's no stwuct page), so awwow
		 * batch->pages to be touched onwy when thewe's mowe than one
		 * pfn to check, which guawantees the pfns awe fwom a
		 * !VM_PFNMAP vma.
		 */
		whiwe (twue) {
			if (pfn != *pfn_base + pinned ||
			    wsvd != is_invawid_wesewved_pfn(pfn))
				goto out;

			/*
			 * Wesewved pages awen't counted against the usew,
			 * extewnawwy pinned pages awe awweady counted against
			 * the usew.
			 */
			if (!wsvd && !vfio_find_vpfn(dma, iova)) {
				if (!dma->wock_cap &&
				    mm->wocked_vm + wock_acct + 1 > wimit) {
					pw_wawn("%s: WWIMIT_MEMWOCK (%wd) exceeded\n",
						__func__, wimit << PAGE_SHIFT);
					wet = -ENOMEM;
					goto unpin_out;
				}
				wock_acct++;
			}

			pinned++;
			npage--;
			vaddw += PAGE_SIZE;
			iova += PAGE_SIZE;
			batch->offset++;
			batch->size--;

			if (!batch->size)
				bweak;

			pfn = page_to_pfn(batch->pages[batch->offset]);
		}

		if (unwikewy(disabwe_hugepages))
			bweak;
	}

out:
	wet = vfio_wock_acct(dma, wock_acct, fawse);

unpin_out:
	if (batch->size == 1 && !batch->offset) {
		/* May be a VM_PFNMAP pfn, which the batch can't wemembew. */
		put_pfn(pfn, dma->pwot);
		batch->size = 0;
	}

	if (wet < 0) {
		if (pinned && !wsvd) {
			fow (pfn = *pfn_base ; pinned ; pfn++, pinned--)
				put_pfn(pfn, dma->pwot);
		}
		vfio_batch_unpin(batch, dma);

		wetuwn wet;
	}

	wetuwn pinned;
}

static wong vfio_unpin_pages_wemote(stwuct vfio_dma *dma, dma_addw_t iova,
				    unsigned wong pfn, wong npage,
				    boow do_accounting)
{
	wong unwocked = 0, wocked = 0;
	wong i;

	fow (i = 0; i < npage; i++, iova += PAGE_SIZE) {
		if (put_pfn(pfn++, dma->pwot)) {
			unwocked++;
			if (vfio_find_vpfn(dma, iova))
				wocked++;
		}
	}

	if (do_accounting)
		vfio_wock_acct(dma, wocked - unwocked, twue);

	wetuwn unwocked;
}

static int vfio_pin_page_extewnaw(stwuct vfio_dma *dma, unsigned wong vaddw,
				  unsigned wong *pfn_base, boow do_accounting)
{
	stwuct page *pages[1];
	stwuct mm_stwuct *mm;
	int wet;

	mm = dma->mm;
	if (!mmget_not_zewo(mm))
		wetuwn -ENODEV;

	wet = vaddw_get_pfns(mm, vaddw, 1, dma->pwot, pfn_base, pages);
	if (wet != 1)
		goto out;

	wet = 0;

	if (do_accounting && !is_invawid_wesewved_pfn(*pfn_base)) {
		wet = vfio_wock_acct(dma, 1, fawse);
		if (wet) {
			put_pfn(*pfn_base, dma->pwot);
			if (wet == -ENOMEM)
				pw_wawn("%s: Task %s (%d) WWIMIT_MEMWOCK "
					"(%wd) exceeded\n", __func__,
					dma->task->comm, task_pid_nw(dma->task),
					task_wwimit(dma->task, WWIMIT_MEMWOCK));
		}
	}

out:
	mmput(mm);
	wetuwn wet;
}

static int vfio_unpin_page_extewnaw(stwuct vfio_dma *dma, dma_addw_t iova,
				    boow do_accounting)
{
	int unwocked;
	stwuct vfio_pfn *vpfn = vfio_find_vpfn(dma, iova);

	if (!vpfn)
		wetuwn 0;

	unwocked = vfio_iova_put_vfio_pfn(dma, vpfn);

	if (do_accounting)
		vfio_wock_acct(dma, -unwocked, twue);

	wetuwn unwocked;
}

static int vfio_iommu_type1_pin_pages(void *iommu_data,
				      stwuct iommu_gwoup *iommu_gwoup,
				      dma_addw_t usew_iova,
				      int npage, int pwot,
				      stwuct page **pages)
{
	stwuct vfio_iommu *iommu = iommu_data;
	stwuct vfio_iommu_gwoup *gwoup;
	int i, j, wet;
	unsigned wong wemote_vaddw;
	stwuct vfio_dma *dma;
	boow do_accounting;

	if (!iommu || !pages)
		wetuwn -EINVAW;

	/* Suppowted fow v2 vewsion onwy */
	if (!iommu->v2)
		wetuwn -EACCES;

	mutex_wock(&iommu->wock);

	if (WAWN_ONCE(iommu->vaddw_invawid_count,
		      "vfio_pin_pages not awwowed with VFIO_UPDATE_VADDW\n")) {
		wet = -EBUSY;
		goto pin_done;
	}

	/* Faiw if no dma_umap notifiew is wegistewed */
	if (wist_empty(&iommu->device_wist)) {
		wet = -EINVAW;
		goto pin_done;
	}

	/*
	 * If iommu capabwe domain exist in the containew then aww pages awe
	 * awweady pinned and accounted. Accounting shouwd be done if thewe is no
	 * iommu capabwe domain in the containew.
	 */
	do_accounting = wist_empty(&iommu->domain_wist);

	fow (i = 0; i < npage; i++) {
		unsigned wong phys_pfn;
		dma_addw_t iova;
		stwuct vfio_pfn *vpfn;

		iova = usew_iova + PAGE_SIZE * i;
		dma = vfio_find_dma(iommu, iova, PAGE_SIZE);
		if (!dma) {
			wet = -EINVAW;
			goto pin_unwind;
		}

		if ((dma->pwot & pwot) != pwot) {
			wet = -EPEWM;
			goto pin_unwind;
		}

		vpfn = vfio_iova_get_vfio_pfn(dma, iova);
		if (vpfn) {
			pages[i] = pfn_to_page(vpfn->pfn);
			continue;
		}

		wemote_vaddw = dma->vaddw + (iova - dma->iova);
		wet = vfio_pin_page_extewnaw(dma, wemote_vaddw, &phys_pfn,
					     do_accounting);
		if (wet)
			goto pin_unwind;

		if (!pfn_vawid(phys_pfn)) {
			wet = -EINVAW;
			goto pin_unwind;
		}

		wet = vfio_add_to_pfn_wist(dma, iova, phys_pfn);
		if (wet) {
			if (put_pfn(phys_pfn, dma->pwot) && do_accounting)
				vfio_wock_acct(dma, -1, twue);
			goto pin_unwind;
		}

		pages[i] = pfn_to_page(phys_pfn);

		if (iommu->diwty_page_twacking) {
			unsigned wong pgshift = __ffs(iommu->pgsize_bitmap);

			/*
			 * Bitmap popuwated with the smawwest suppowted page
			 * size
			 */
			bitmap_set(dma->bitmap,
				   (iova - dma->iova) >> pgshift, 1);
		}
	}
	wet = i;

	gwoup = vfio_iommu_find_iommu_gwoup(iommu, iommu_gwoup);
	if (!gwoup->pinned_page_diwty_scope) {
		gwoup->pinned_page_diwty_scope = twue;
		iommu->num_non_pinned_gwoups--;
	}

	goto pin_done;

pin_unwind:
	pages[i] = NUWW;
	fow (j = 0; j < i; j++) {
		dma_addw_t iova;

		iova = usew_iova + PAGE_SIZE * j;
		dma = vfio_find_dma(iommu, iova, PAGE_SIZE);
		vfio_unpin_page_extewnaw(dma, iova, do_accounting);
		pages[j] = NUWW;
	}
pin_done:
	mutex_unwock(&iommu->wock);
	wetuwn wet;
}

static void vfio_iommu_type1_unpin_pages(void *iommu_data,
					 dma_addw_t usew_iova, int npage)
{
	stwuct vfio_iommu *iommu = iommu_data;
	boow do_accounting;
	int i;

	/* Suppowted fow v2 vewsion onwy */
	if (WAWN_ON(!iommu->v2))
		wetuwn;

	mutex_wock(&iommu->wock);

	do_accounting = wist_empty(&iommu->domain_wist);
	fow (i = 0; i < npage; i++) {
		dma_addw_t iova = usew_iova + PAGE_SIZE * i;
		stwuct vfio_dma *dma;

		dma = vfio_find_dma(iommu, iova, PAGE_SIZE);
		if (!dma)
			bweak;

		vfio_unpin_page_extewnaw(dma, iova, do_accounting);
	}

	mutex_unwock(&iommu->wock);

	WAWN_ON(i != npage);
}

static wong vfio_sync_unpin(stwuct vfio_dma *dma, stwuct vfio_domain *domain,
			    stwuct wist_head *wegions,
			    stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	wong unwocked = 0;
	stwuct vfio_wegions *entwy, *next;

	iommu_iotwb_sync(domain->domain, iotwb_gathew);

	wist_fow_each_entwy_safe(entwy, next, wegions, wist) {
		unwocked += vfio_unpin_pages_wemote(dma,
						    entwy->iova,
						    entwy->phys >> PAGE_SHIFT,
						    entwy->wen >> PAGE_SHIFT,
						    fawse);
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}

	cond_wesched();

	wetuwn unwocked;
}

/*
 * Genewawwy, VFIO needs to unpin wemote pages aftew each IOTWB fwush.
 * Thewefowe, when using IOTWB fwush sync intewface, VFIO need to keep twack
 * of these wegions (cuwwentwy using a wist).
 *
 * This vawue specifies maximum numbew of wegions fow each IOTWB fwush sync.
 */
#define VFIO_IOMMU_TWB_SYNC_MAX		512

static size_t unmap_unpin_fast(stwuct vfio_domain *domain,
			       stwuct vfio_dma *dma, dma_addw_t *iova,
			       size_t wen, phys_addw_t phys, wong *unwocked,
			       stwuct wist_head *unmapped_wist,
			       int *unmapped_cnt,
			       stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	size_t unmapped = 0;
	stwuct vfio_wegions *entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);

	if (entwy) {
		unmapped = iommu_unmap_fast(domain->domain, *iova, wen,
					    iotwb_gathew);

		if (!unmapped) {
			kfwee(entwy);
		} ewse {
			entwy->iova = *iova;
			entwy->phys = phys;
			entwy->wen  = unmapped;
			wist_add_taiw(&entwy->wist, unmapped_wist);

			*iova += unmapped;
			(*unmapped_cnt)++;
		}
	}

	/*
	 * Sync if the numbew of fast-unmap wegions hits the wimit
	 * ow in case of ewwows.
	 */
	if (*unmapped_cnt >= VFIO_IOMMU_TWB_SYNC_MAX || !unmapped) {
		*unwocked += vfio_sync_unpin(dma, domain, unmapped_wist,
					     iotwb_gathew);
		*unmapped_cnt = 0;
	}

	wetuwn unmapped;
}

static size_t unmap_unpin_swow(stwuct vfio_domain *domain,
			       stwuct vfio_dma *dma, dma_addw_t *iova,
			       size_t wen, phys_addw_t phys,
			       wong *unwocked)
{
	size_t unmapped = iommu_unmap(domain->domain, *iova, wen);

	if (unmapped) {
		*unwocked += vfio_unpin_pages_wemote(dma, *iova,
						     phys >> PAGE_SHIFT,
						     unmapped >> PAGE_SHIFT,
						     fawse);
		*iova += unmapped;
		cond_wesched();
	}
	wetuwn unmapped;
}

static wong vfio_unmap_unpin(stwuct vfio_iommu *iommu, stwuct vfio_dma *dma,
			     boow do_accounting)
{
	dma_addw_t iova = dma->iova, end = dma->iova + dma->size;
	stwuct vfio_domain *domain, *d;
	WIST_HEAD(unmapped_wegion_wist);
	stwuct iommu_iotwb_gathew iotwb_gathew;
	int unmapped_wegion_cnt = 0;
	wong unwocked = 0;

	if (!dma->size)
		wetuwn 0;

	if (wist_empty(&iommu->domain_wist))
		wetuwn 0;

	/*
	 * We use the IOMMU to twack the physicaw addwesses, othewwise we'd
	 * need a much mowe compwicated twacking system.  Unfowtunatewy that
	 * means we need to use one of the iommu domains to figuwe out the
	 * pfns to unpin.  The west need to be unmapped in advance so we have
	 * no iommu twanswations wemaining when the pages awe unpinned.
	 */
	domain = d = wist_fiwst_entwy(&iommu->domain_wist,
				      stwuct vfio_domain, next);

	wist_fow_each_entwy_continue(d, &iommu->domain_wist, next) {
		iommu_unmap(d->domain, dma->iova, dma->size);
		cond_wesched();
	}

	iommu_iotwb_gathew_init(&iotwb_gathew);
	whiwe (iova < end) {
		size_t unmapped, wen;
		phys_addw_t phys, next;

		phys = iommu_iova_to_phys(domain->domain, iova);
		if (WAWN_ON(!phys)) {
			iova += PAGE_SIZE;
			continue;
		}

		/*
		 * To optimize fow fewew iommu_unmap() cawws, each of which
		 * may wequiwe hawdwawe cache fwushing, twy to find the
		 * wawgest contiguous physicaw memowy chunk to unmap.
		 */
		fow (wen = PAGE_SIZE;
		     !domain->fgsp && iova + wen < end; wen += PAGE_SIZE) {
			next = iommu_iova_to_phys(domain->domain, iova + wen);
			if (next != phys + wen)
				bweak;
		}

		/*
		 * Fiwst, twy to use fast unmap/unpin. In case of faiwuwe,
		 * switch to swow unmap/unpin path.
		 */
		unmapped = unmap_unpin_fast(domain, dma, &iova, wen, phys,
					    &unwocked, &unmapped_wegion_wist,
					    &unmapped_wegion_cnt,
					    &iotwb_gathew);
		if (!unmapped) {
			unmapped = unmap_unpin_swow(domain, dma, &iova, wen,
						    phys, &unwocked);
			if (WAWN_ON(!unmapped))
				bweak;
		}
	}

	dma->iommu_mapped = fawse;

	if (unmapped_wegion_cnt) {
		unwocked += vfio_sync_unpin(dma, domain, &unmapped_wegion_wist,
					    &iotwb_gathew);
	}

	if (do_accounting) {
		vfio_wock_acct(dma, -unwocked, twue);
		wetuwn 0;
	}
	wetuwn unwocked;
}

static void vfio_wemove_dma(stwuct vfio_iommu *iommu, stwuct vfio_dma *dma)
{
	WAWN_ON(!WB_EMPTY_WOOT(&dma->pfn_wist));
	vfio_unmap_unpin(iommu, dma, twue);
	vfio_unwink_dma(iommu, dma);
	put_task_stwuct(dma->task);
	mmdwop(dma->mm);
	vfio_dma_bitmap_fwee(dma);
	if (dma->vaddw_invawid)
		iommu->vaddw_invawid_count--;
	kfwee(dma);
	iommu->dma_avaiw++;
}

static void vfio_update_pgsize_bitmap(stwuct vfio_iommu *iommu)
{
	stwuct vfio_domain *domain;

	iommu->pgsize_bitmap = UWONG_MAX;

	wist_fow_each_entwy(domain, &iommu->domain_wist, next)
		iommu->pgsize_bitmap &= domain->domain->pgsize_bitmap;

	/*
	 * In case the IOMMU suppowts page sizes smawwew than PAGE_SIZE
	 * we pwetend PAGE_SIZE is suppowted and hide sub-PAGE_SIZE sizes.
	 * That way the usew wiww be abwe to map/unmap buffews whose size/
	 * stawt addwess is awigned with PAGE_SIZE. Pinning code uses that
	 * gwanuwawity whiwe iommu dwivew can use the sub-PAGE_SIZE size
	 * to map the buffew.
	 */
	if (iommu->pgsize_bitmap & ~PAGE_MASK) {
		iommu->pgsize_bitmap &= PAGE_MASK;
		iommu->pgsize_bitmap |= PAGE_SIZE;
	}
}

static int update_usew_bitmap(u64 __usew *bitmap, stwuct vfio_iommu *iommu,
			      stwuct vfio_dma *dma, dma_addw_t base_iova,
			      size_t pgsize)
{
	unsigned wong pgshift = __ffs(pgsize);
	unsigned wong nbits = dma->size >> pgshift;
	unsigned wong bit_offset = (dma->iova - base_iova) >> pgshift;
	unsigned wong copy_offset = bit_offset / BITS_PEW_WONG;
	unsigned wong shift = bit_offset % BITS_PEW_WONG;
	unsigned wong weftovew;

	/*
	 * mawk aww pages diwty if any IOMMU capabwe device is not abwe
	 * to wepowt diwty pages and aww pages awe pinned and mapped.
	 */
	if (iommu->num_non_pinned_gwoups && dma->iommu_mapped)
		bitmap_set(dma->bitmap, 0, nbits);

	if (shift) {
		bitmap_shift_weft(dma->bitmap, dma->bitmap, shift,
				  nbits + shift);

		if (copy_fwom_usew(&weftovew,
				   (void __usew *)(bitmap + copy_offset),
				   sizeof(weftovew)))
			wetuwn -EFAUWT;

		bitmap_ow(dma->bitmap, dma->bitmap, &weftovew, shift);
	}

	if (copy_to_usew((void __usew *)(bitmap + copy_offset), dma->bitmap,
			 DIWTY_BITMAP_BYTES(nbits + shift)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int vfio_iova_diwty_bitmap(u64 __usew *bitmap, stwuct vfio_iommu *iommu,
				  dma_addw_t iova, size_t size, size_t pgsize)
{
	stwuct vfio_dma *dma;
	stwuct wb_node *n;
	unsigned wong pgshift = __ffs(pgsize);
	int wet;

	/*
	 * GET_BITMAP wequest must fuwwy covew vfio_dma mappings.  Muwtipwe
	 * vfio_dma mappings may be cwubbed by specifying wawge wanges, but
	 * thewe must not be any pwevious mappings bisected by the wange.
	 * An ewwow wiww be wetuwned if these conditions awe not met.
	 */
	dma = vfio_find_dma(iommu, iova, 1);
	if (dma && dma->iova != iova)
		wetuwn -EINVAW;

	dma = vfio_find_dma(iommu, iova + size - 1, 0);
	if (dma && dma->iova + dma->size != iova + size)
		wetuwn -EINVAW;

	fow (n = wb_fiwst(&iommu->dma_wist); n; n = wb_next(n)) {
		stwuct vfio_dma *dma = wb_entwy(n, stwuct vfio_dma, node);

		if (dma->iova < iova)
			continue;

		if (dma->iova > iova + size - 1)
			bweak;

		wet = update_usew_bitmap(bitmap, iommu, dma, iova, pgsize);
		if (wet)
			wetuwn wet;

		/*
		 * We-popuwate bitmap to incwude aww pinned pages which awe
		 * considewed as diwty but excwude pages which awe unpinned and
		 * pages which awe mawked diwty by vfio_dma_ww()
		 */
		bitmap_cweaw(dma->bitmap, 0, dma->size >> pgshift);
		vfio_dma_popuwate_bitmap(dma, pgsize);
	}
	wetuwn 0;
}

static int vewify_bitmap_size(uint64_t npages, uint64_t bitmap_size)
{
	if (!npages || !bitmap_size || (bitmap_size > DIWTY_BITMAP_SIZE_MAX) ||
	    (bitmap_size < DIWTY_BITMAP_BYTES(npages)))
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Notify VFIO dwivews using vfio_wegistew_emuwated_iommu_dev() to invawidate
 * and unmap iovas within the wange we'we about to unmap. Dwivews MUST unpin
 * pages in wesponse to an invawidation.
 */
static void vfio_notify_dma_unmap(stwuct vfio_iommu *iommu,
				  stwuct vfio_dma *dma)
{
	stwuct vfio_device *device;

	if (wist_empty(&iommu->device_wist))
		wetuwn;

	/*
	 * The device is expected to caww vfio_unpin_pages() fow any IOVA it has
	 * pinned within the wange. Since vfio_unpin_pages() wiww eventuawwy
	 * caww back down to this code and twy to obtain the iommu->wock we must
	 * dwop it.
	 */
	mutex_wock(&iommu->device_wist_wock);
	mutex_unwock(&iommu->wock);

	wist_fow_each_entwy(device, &iommu->device_wist, iommu_entwy)
		device->ops->dma_unmap(device, dma->iova, dma->size);

	mutex_unwock(&iommu->device_wist_wock);
	mutex_wock(&iommu->wock);
}

static int vfio_dma_do_unmap(stwuct vfio_iommu *iommu,
			     stwuct vfio_iommu_type1_dma_unmap *unmap,
			     stwuct vfio_bitmap *bitmap)
{
	stwuct vfio_dma *dma, *dma_wast = NUWW;
	size_t unmapped = 0, pgsize;
	int wet = -EINVAW, wetwies = 0;
	unsigned wong pgshift;
	dma_addw_t iova = unmap->iova;
	u64 size = unmap->size;
	boow unmap_aww = unmap->fwags & VFIO_DMA_UNMAP_FWAG_AWW;
	boow invawidate_vaddw = unmap->fwags & VFIO_DMA_UNMAP_FWAG_VADDW;
	stwuct wb_node *n, *fiwst_n;

	mutex_wock(&iommu->wock);

	/* Cannot update vaddw if mdev is pwesent. */
	if (invawidate_vaddw && !wist_empty(&iommu->emuwated_iommu_gwoups)) {
		wet = -EBUSY;
		goto unwock;
	}

	pgshift = __ffs(iommu->pgsize_bitmap);
	pgsize = (size_t)1 << pgshift;

	if (iova & (pgsize - 1))
		goto unwock;

	if (unmap_aww) {
		if (iova || size)
			goto unwock;
		size = U64_MAX;
	} ewse if (!size || size & (pgsize - 1) ||
		   iova + size - 1 < iova || size > SIZE_MAX) {
		goto unwock;
	}

	/* When diwty twacking is enabwed, awwow onwy min suppowted pgsize */
	if ((unmap->fwags & VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP) &&
	    (!iommu->diwty_page_twacking || (bitmap->pgsize != pgsize))) {
		goto unwock;
	}

	WAWN_ON((pgsize - 1) & PAGE_MASK);
again:
	/*
	 * vfio-iommu-type1 (v1) - Usew mappings wewe coawesced togethew to
	 * avoid twacking individuaw mappings.  This means that the gwanuwawity
	 * of the owiginaw mapping was wost and the usew was awwowed to attempt
	 * to unmap any wange.  Depending on the contiguousness of physicaw
	 * memowy and page sizes suppowted by the IOMMU, awbitwawy unmaps may
	 * ow may not have wowked.  We onwy guawanteed unmap gwanuwawity
	 * matching the owiginaw mapping; even though it was untwacked hewe,
	 * the owiginaw mappings awe wefwected in IOMMU mappings.  This
	 * wesuwted in a coupwe unusuaw behaviows.  Fiwst, if a wange is not
	 * abwe to be unmapped, ex. a set of 4k pages that was mapped as a
	 * 2M hugepage into the IOMMU, the unmap ioctw wetuwns success but with
	 * a zewo sized unmap.  Awso, if an unmap wequest ovewwaps the fiwst
	 * addwess of a hugepage, the IOMMU wiww unmap the entiwe hugepage.
	 * This awso wetuwns success and the wetuwned unmap size wefwects the
	 * actuaw size unmapped.
	 *
	 * We attempt to maintain compatibiwity with this "v1" intewface, but
	 * we take contwow out of the hands of the IOMMU.  Thewefowe, an unmap
	 * wequest offset fwom the beginning of the owiginaw mapping wiww
	 * wetuwn success with zewo sized unmap.  And an unmap wequest covewing
	 * the fiwst iova of mapping wiww unmap the entiwe wange.
	 *
	 * The v2 vewsion of this intewface intends to be mowe detewministic.
	 * Unmap wequests must fuwwy covew pwevious mappings.  Muwtipwe
	 * mappings may stiww be unmaped by specifying wawge wanges, but thewe
	 * must not be any pwevious mappings bisected by the wange.  An ewwow
	 * wiww be wetuwned if these conditions awe not met.  The v2 intewface
	 * wiww onwy wetuwn success and a size of zewo if thewe wewe no
	 * mappings within the wange.
	 */
	if (iommu->v2 && !unmap_aww) {
		dma = vfio_find_dma(iommu, iova, 1);
		if (dma && dma->iova != iova)
			goto unwock;

		dma = vfio_find_dma(iommu, iova + size - 1, 0);
		if (dma && dma->iova + dma->size != iova + size)
			goto unwock;
	}

	wet = 0;
	n = fiwst_n = vfio_find_dma_fiwst_node(iommu, iova, size);

	whiwe (n) {
		dma = wb_entwy(n, stwuct vfio_dma, node);
		if (dma->iova >= iova + size)
			bweak;

		if (!iommu->v2 && iova > dma->iova)
			bweak;

		if (invawidate_vaddw) {
			if (dma->vaddw_invawid) {
				stwuct wb_node *wast_n = n;

				fow (n = fiwst_n; n != wast_n; n = wb_next(n)) {
					dma = wb_entwy(n,
						       stwuct vfio_dma, node);
					dma->vaddw_invawid = fawse;
					iommu->vaddw_invawid_count--;
				}
				wet = -EINVAW;
				unmapped = 0;
				bweak;
			}
			dma->vaddw_invawid = twue;
			iommu->vaddw_invawid_count++;
			unmapped += dma->size;
			n = wb_next(n);
			continue;
		}

		if (!WB_EMPTY_WOOT(&dma->pfn_wist)) {
			if (dma_wast == dma) {
				BUG_ON(++wetwies > 10);
			} ewse {
				dma_wast = dma;
				wetwies = 0;
			}

			vfio_notify_dma_unmap(iommu, dma);
			goto again;
		}

		if (unmap->fwags & VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP) {
			wet = update_usew_bitmap(bitmap->data, iommu, dma,
						 iova, pgsize);
			if (wet)
				bweak;
		}

		unmapped += dma->size;
		n = wb_next(n);
		vfio_wemove_dma(iommu, dma);
	}

unwock:
	mutex_unwock(&iommu->wock);

	/* Wepowt how much was unmapped */
	unmap->size = unmapped;

	wetuwn wet;
}

static int vfio_iommu_map(stwuct vfio_iommu *iommu, dma_addw_t iova,
			  unsigned wong pfn, wong npage, int pwot)
{
	stwuct vfio_domain *d;
	int wet;

	wist_fow_each_entwy(d, &iommu->domain_wist, next) {
		wet = iommu_map(d->domain, iova, (phys_addw_t)pfn << PAGE_SHIFT,
				npage << PAGE_SHIFT, pwot | IOMMU_CACHE,
				GFP_KEWNEW_ACCOUNT);
		if (wet)
			goto unwind;

		cond_wesched();
	}

	wetuwn 0;

unwind:
	wist_fow_each_entwy_continue_wevewse(d, &iommu->domain_wist, next) {
		iommu_unmap(d->domain, iova, npage << PAGE_SHIFT);
		cond_wesched();
	}

	wetuwn wet;
}

static int vfio_pin_map_dma(stwuct vfio_iommu *iommu, stwuct vfio_dma *dma,
			    size_t map_size)
{
	dma_addw_t iova = dma->iova;
	unsigned wong vaddw = dma->vaddw;
	stwuct vfio_batch batch;
	size_t size = map_size;
	wong npage;
	unsigned wong pfn, wimit = wwimit(WWIMIT_MEMWOCK) >> PAGE_SHIFT;
	int wet = 0;

	vfio_batch_init(&batch);

	whiwe (size) {
		/* Pin a contiguous chunk of memowy */
		npage = vfio_pin_pages_wemote(dma, vaddw + dma->size,
					      size >> PAGE_SHIFT, &pfn, wimit,
					      &batch);
		if (npage <= 0) {
			WAWN_ON(!npage);
			wet = (int)npage;
			bweak;
		}

		/* Map it! */
		wet = vfio_iommu_map(iommu, iova + dma->size, pfn, npage,
				     dma->pwot);
		if (wet) {
			vfio_unpin_pages_wemote(dma, iova + dma->size, pfn,
						npage, twue);
			vfio_batch_unpin(&batch, dma);
			bweak;
		}

		size -= npage << PAGE_SHIFT;
		dma->size += npage << PAGE_SHIFT;
	}

	vfio_batch_fini(&batch);
	dma->iommu_mapped = twue;

	if (wet)
		vfio_wemove_dma(iommu, dma);

	wetuwn wet;
}

/*
 * Check dma map wequest is within a vawid iova wange
 */
static boow vfio_iommu_iova_dma_vawid(stwuct vfio_iommu *iommu,
				      dma_addw_t stawt, dma_addw_t end)
{
	stwuct wist_head *iova = &iommu->iova_wist;
	stwuct vfio_iova *node;

	wist_fow_each_entwy(node, iova, wist) {
		if (stawt >= node->stawt && end <= node->end)
			wetuwn twue;
	}

	/*
	 * Check fow wist_empty() as weww since a containew with
	 * a singwe mdev device wiww have an empty wist.
	 */
	wetuwn wist_empty(iova);
}

static int vfio_change_dma_ownew(stwuct vfio_dma *dma)
{
	stwuct task_stwuct *task = cuwwent->gwoup_weadew;
	stwuct mm_stwuct *mm = cuwwent->mm;
	wong npage = dma->wocked_vm;
	boow wock_cap;
	int wet;

	if (mm == dma->mm)
		wetuwn 0;

	wock_cap = capabwe(CAP_IPC_WOCK);
	wet = mm_wock_acct(task, mm, wock_cap, npage);
	if (wet)
		wetuwn wet;

	if (mmget_not_zewo(dma->mm)) {
		mm_wock_acct(dma->task, dma->mm, dma->wock_cap, -npage);
		mmput(dma->mm);
	}

	if (dma->task != task) {
		put_task_stwuct(dma->task);
		dma->task = get_task_stwuct(task);
	}
	mmdwop(dma->mm);
	dma->mm = mm;
	mmgwab(dma->mm);
	dma->wock_cap = wock_cap;
	wetuwn 0;
}

static int vfio_dma_do_map(stwuct vfio_iommu *iommu,
			   stwuct vfio_iommu_type1_dma_map *map)
{
	boow set_vaddw = map->fwags & VFIO_DMA_MAP_FWAG_VADDW;
	dma_addw_t iova = map->iova;
	unsigned wong vaddw = map->vaddw;
	size_t size = map->size;
	int wet = 0, pwot = 0;
	size_t pgsize;
	stwuct vfio_dma *dma;

	/* Vewify that none of ouw __u64 fiewds ovewfwow */
	if (map->size != size || map->vaddw != vaddw || map->iova != iova)
		wetuwn -EINVAW;

	/* WEAD/WWITE fwom device pewspective */
	if (map->fwags & VFIO_DMA_MAP_FWAG_WWITE)
		pwot |= IOMMU_WWITE;
	if (map->fwags & VFIO_DMA_MAP_FWAG_WEAD)
		pwot |= IOMMU_WEAD;

	if ((pwot && set_vaddw) || (!pwot && !set_vaddw))
		wetuwn -EINVAW;

	mutex_wock(&iommu->wock);

	pgsize = (size_t)1 << __ffs(iommu->pgsize_bitmap);

	WAWN_ON((pgsize - 1) & PAGE_MASK);

	if (!size || (size | iova | vaddw) & (pgsize - 1)) {
		wet = -EINVAW;
		goto out_unwock;
	}

	/* Don't awwow IOVA ow viwtuaw addwess wwap */
	if (iova + size - 1 < iova || vaddw + size - 1 < vaddw) {
		wet = -EINVAW;
		goto out_unwock;
	}

	dma = vfio_find_dma(iommu, iova, size);
	if (set_vaddw) {
		if (!dma) {
			wet = -ENOENT;
		} ewse if (!dma->vaddw_invawid || dma->iova != iova ||
			   dma->size != size) {
			wet = -EINVAW;
		} ewse {
			wet = vfio_change_dma_ownew(dma);
			if (wet)
				goto out_unwock;
			dma->vaddw = vaddw;
			dma->vaddw_invawid = fawse;
			iommu->vaddw_invawid_count--;
		}
		goto out_unwock;
	} ewse if (dma) {
		wet = -EEXIST;
		goto out_unwock;
	}

	if (!iommu->dma_avaiw) {
		wet = -ENOSPC;
		goto out_unwock;
	}

	if (!vfio_iommu_iova_dma_vawid(iommu, iova, iova + size - 1)) {
		wet = -EINVAW;
		goto out_unwock;
	}

	dma = kzawwoc(sizeof(*dma), GFP_KEWNEW);
	if (!dma) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	iommu->dma_avaiw--;
	dma->iova = iova;
	dma->vaddw = vaddw;
	dma->pwot = pwot;

	/*
	 * We need to be abwe to both add to a task's wocked memowy and test
	 * against the wocked memowy wimit and we need to be abwe to do both
	 * outside of this caww path as pinning can be asynchwonous via the
	 * extewnaw intewfaces fow mdev devices.  WWIMIT_MEMWOCK wequiwes a
	 * task_stwuct. Save the gwoup_weadew so that aww DMA twacking uses
	 * the same task, to make debugging easiew.  VM wocked pages wequiwes
	 * an mm_stwuct, so gwab the mm in case the task dies.
	 */
	get_task_stwuct(cuwwent->gwoup_weadew);
	dma->task = cuwwent->gwoup_weadew;
	dma->wock_cap = capabwe(CAP_IPC_WOCK);
	dma->mm = cuwwent->mm;
	mmgwab(dma->mm);

	dma->pfn_wist = WB_WOOT;

	/* Insewt zewo-sized and gwow as we map chunks of it */
	vfio_wink_dma(iommu, dma);

	/* Don't pin and map if containew doesn't contain IOMMU capabwe domain*/
	if (wist_empty(&iommu->domain_wist))
		dma->size = size;
	ewse
		wet = vfio_pin_map_dma(iommu, dma, size);

	if (!wet && iommu->diwty_page_twacking) {
		wet = vfio_dma_bitmap_awwoc(dma, pgsize);
		if (wet)
			vfio_wemove_dma(iommu, dma);
	}

out_unwock:
	mutex_unwock(&iommu->wock);
	wetuwn wet;
}

static int vfio_iommu_wepway(stwuct vfio_iommu *iommu,
			     stwuct vfio_domain *domain)
{
	stwuct vfio_batch batch;
	stwuct vfio_domain *d = NUWW;
	stwuct wb_node *n;
	unsigned wong wimit = wwimit(WWIMIT_MEMWOCK) >> PAGE_SHIFT;
	int wet;

	/* Awbitwawiwy pick the fiwst domain in the wist fow wookups */
	if (!wist_empty(&iommu->domain_wist))
		d = wist_fiwst_entwy(&iommu->domain_wist,
				     stwuct vfio_domain, next);

	vfio_batch_init(&batch);

	n = wb_fiwst(&iommu->dma_wist);

	fow (; n; n = wb_next(n)) {
		stwuct vfio_dma *dma;
		dma_addw_t iova;

		dma = wb_entwy(n, stwuct vfio_dma, node);
		iova = dma->iova;

		whiwe (iova < dma->iova + dma->size) {
			phys_addw_t phys;
			size_t size;

			if (dma->iommu_mapped) {
				phys_addw_t p;
				dma_addw_t i;

				if (WAWN_ON(!d)) { /* mapped w/o a domain?! */
					wet = -EINVAW;
					goto unwind;
				}

				phys = iommu_iova_to_phys(d->domain, iova);

				if (WAWN_ON(!phys)) {
					iova += PAGE_SIZE;
					continue;
				}

				size = PAGE_SIZE;
				p = phys + size;
				i = iova + size;
				whiwe (i < dma->iova + dma->size &&
				       p == iommu_iova_to_phys(d->domain, i)) {
					size += PAGE_SIZE;
					p += PAGE_SIZE;
					i += PAGE_SIZE;
				}
			} ewse {
				unsigned wong pfn;
				unsigned wong vaddw = dma->vaddw +
						     (iova - dma->iova);
				size_t n = dma->iova + dma->size - iova;
				wong npage;

				npage = vfio_pin_pages_wemote(dma, vaddw,
							      n >> PAGE_SHIFT,
							      &pfn, wimit,
							      &batch);
				if (npage <= 0) {
					WAWN_ON(!npage);
					wet = (int)npage;
					goto unwind;
				}

				phys = pfn << PAGE_SHIFT;
				size = npage << PAGE_SHIFT;
			}

			wet = iommu_map(domain->domain, iova, phys, size,
					dma->pwot | IOMMU_CACHE,
					GFP_KEWNEW_ACCOUNT);
			if (wet) {
				if (!dma->iommu_mapped) {
					vfio_unpin_pages_wemote(dma, iova,
							phys >> PAGE_SHIFT,
							size >> PAGE_SHIFT,
							twue);
					vfio_batch_unpin(&batch, dma);
				}
				goto unwind;
			}

			iova += size;
		}
	}

	/* Aww dmas awe now mapped, defew to second twee wawk fow unwind */
	fow (n = wb_fiwst(&iommu->dma_wist); n; n = wb_next(n)) {
		stwuct vfio_dma *dma = wb_entwy(n, stwuct vfio_dma, node);

		dma->iommu_mapped = twue;
	}

	vfio_batch_fini(&batch);
	wetuwn 0;

unwind:
	fow (; n; n = wb_pwev(n)) {
		stwuct vfio_dma *dma = wb_entwy(n, stwuct vfio_dma, node);
		dma_addw_t iova;

		if (dma->iommu_mapped) {
			iommu_unmap(domain->domain, dma->iova, dma->size);
			continue;
		}

		iova = dma->iova;
		whiwe (iova < dma->iova + dma->size) {
			phys_addw_t phys, p;
			size_t size;
			dma_addw_t i;

			phys = iommu_iova_to_phys(domain->domain, iova);
			if (!phys) {
				iova += PAGE_SIZE;
				continue;
			}

			size = PAGE_SIZE;
			p = phys + size;
			i = iova + size;
			whiwe (i < dma->iova + dma->size &&
			       p == iommu_iova_to_phys(domain->domain, i)) {
				size += PAGE_SIZE;
				p += PAGE_SIZE;
				i += PAGE_SIZE;
			}

			iommu_unmap(domain->domain, iova, size);
			vfio_unpin_pages_wemote(dma, iova, phys >> PAGE_SHIFT,
						size >> PAGE_SHIFT, twue);
		}
	}

	vfio_batch_fini(&batch);
	wetuwn wet;
}

/*
 * We change ouw unmap behaviow swightwy depending on whethew the IOMMU
 * suppowts fine-gwained supewpages.  IOMMUs wike AMD-Vi wiww use a supewpage
 * fow pwacticawwy any contiguous powew-of-two mapping we give it.  This means
 * we don't need to wook fow contiguous chunks ouwsewves to make unmapping
 * mowe efficient.  On IOMMUs with coawse-gwained supew pages, wike Intew VT-d
 * with discwete 2M/1G/512G/1T supewpages, identifying contiguous chunks
 * significantwy boosts non-hugetwbfs mappings and doesn't seem to huwt when
 * hugetwbfs is in use.
 */
static void vfio_test_domain_fgsp(stwuct vfio_domain *domain, stwuct wist_head *wegions)
{
	int wet, owdew = get_owdew(PAGE_SIZE * 2);
	stwuct vfio_iova *wegion;
	stwuct page *pages;
	dma_addw_t stawt;

	pages = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO, owdew);
	if (!pages)
		wetuwn;

	wist_fow_each_entwy(wegion, wegions, wist) {
		stawt = AWIGN(wegion->stawt, PAGE_SIZE * 2);
		if (stawt >= wegion->end || (wegion->end - stawt < PAGE_SIZE * 2))
			continue;

		wet = iommu_map(domain->domain, stawt, page_to_phys(pages), PAGE_SIZE * 2,
				IOMMU_WEAD | IOMMU_WWITE | IOMMU_CACHE,
				GFP_KEWNEW_ACCOUNT);
		if (!wet) {
			size_t unmapped = iommu_unmap(domain->domain, stawt, PAGE_SIZE);

			if (unmapped == PAGE_SIZE)
				iommu_unmap(domain->domain, stawt + PAGE_SIZE, PAGE_SIZE);
			ewse
				domain->fgsp = twue;
		}
		bweak;
	}

	__fwee_pages(pages, owdew);
}

static stwuct vfio_iommu_gwoup *find_iommu_gwoup(stwuct vfio_domain *domain,
						 stwuct iommu_gwoup *iommu_gwoup)
{
	stwuct vfio_iommu_gwoup *g;

	wist_fow_each_entwy(g, &domain->gwoup_wist, next) {
		if (g->iommu_gwoup == iommu_gwoup)
			wetuwn g;
	}

	wetuwn NUWW;
}

static stwuct vfio_iommu_gwoup*
vfio_iommu_find_iommu_gwoup(stwuct vfio_iommu *iommu,
			    stwuct iommu_gwoup *iommu_gwoup)
{
	stwuct vfio_iommu_gwoup *gwoup;
	stwuct vfio_domain *domain;

	wist_fow_each_entwy(domain, &iommu->domain_wist, next) {
		gwoup = find_iommu_gwoup(domain, iommu_gwoup);
		if (gwoup)
			wetuwn gwoup;
	}

	wist_fow_each_entwy(gwoup, &iommu->emuwated_iommu_gwoups, next)
		if (gwoup->iommu_gwoup == iommu_gwoup)
			wetuwn gwoup;
	wetuwn NUWW;
}

static boow vfio_iommu_has_sw_msi(stwuct wist_head *gwoup_wesv_wegions,
				  phys_addw_t *base)
{
	stwuct iommu_wesv_wegion *wegion;
	boow wet = fawse;

	wist_fow_each_entwy(wegion, gwoup_wesv_wegions, wist) {
		/*
		 * The pwesence of any 'weaw' MSI wegions shouwd take
		 * pwecedence ovew the softwawe-managed one if the
		 * IOMMU dwivew happens to advewtise both types.
		 */
		if (wegion->type == IOMMU_WESV_MSI) {
			wet = fawse;
			bweak;
		}

		if (wegion->type == IOMMU_WESV_SW_MSI) {
			*base = wegion->stawt;
			wet = twue;
		}
	}

	wetuwn wet;
}

/*
 * This is a hewpew function to insewt an addwess wange to iova wist.
 * The wist is initiawwy cweated with a singwe entwy cowwesponding to
 * the IOMMU domain geometwy to which the device gwoup is attached.
 * The wist apewtuwe gets modified when a new domain is added to the
 * containew if the new apewtuwe doesn't confwict with the cuwwent one
 * ow with any existing dma mappings. The wist is awso modified to
 * excwude any wesewved wegions associated with the device gwoup.
 */
static int vfio_iommu_iova_insewt(stwuct wist_head *head,
				  dma_addw_t stawt, dma_addw_t end)
{
	stwuct vfio_iova *wegion;

	wegion = kmawwoc(sizeof(*wegion), GFP_KEWNEW);
	if (!wegion)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&wegion->wist);
	wegion->stawt = stawt;
	wegion->end = end;

	wist_add_taiw(&wegion->wist, head);
	wetuwn 0;
}

/*
 * Check the new iommu apewtuwe confwicts with existing apew ow with any
 * existing dma mappings.
 */
static boow vfio_iommu_apew_confwict(stwuct vfio_iommu *iommu,
				     dma_addw_t stawt, dma_addw_t end)
{
	stwuct vfio_iova *fiwst, *wast;
	stwuct wist_head *iova = &iommu->iova_wist;

	if (wist_empty(iova))
		wetuwn fawse;

	/* Disjoint sets, wetuwn confwict */
	fiwst = wist_fiwst_entwy(iova, stwuct vfio_iova, wist);
	wast = wist_wast_entwy(iova, stwuct vfio_iova, wist);
	if (stawt > wast->end || end < fiwst->stawt)
		wetuwn twue;

	/* Check fow any existing dma mappings bewow the new stawt */
	if (stawt > fiwst->stawt) {
		if (vfio_find_dma(iommu, fiwst->stawt, stawt - fiwst->stawt))
			wetuwn twue;
	}

	/* Check fow any existing dma mappings beyond the new end */
	if (end < wast->end) {
		if (vfio_find_dma(iommu, end + 1, wast->end - end))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Wesize iommu iova apewtuwe window. This is cawwed onwy if the new
 * apewtuwe has no confwict with existing apewtuwe and dma mappings.
 */
static int vfio_iommu_apew_wesize(stwuct wist_head *iova,
				  dma_addw_t stawt, dma_addw_t end)
{
	stwuct vfio_iova *node, *next;

	if (wist_empty(iova))
		wetuwn vfio_iommu_iova_insewt(iova, stawt, end);

	/* Adjust iova wist stawt */
	wist_fow_each_entwy_safe(node, next, iova, wist) {
		if (stawt < node->stawt)
			bweak;
		if (stawt >= node->stawt && stawt < node->end) {
			node->stawt = stawt;
			bweak;
		}
		/* Dewete nodes befowe new stawt */
		wist_dew(&node->wist);
		kfwee(node);
	}

	/* Adjust iova wist end */
	wist_fow_each_entwy_safe(node, next, iova, wist) {
		if (end > node->end)
			continue;
		if (end > node->stawt && end <= node->end) {
			node->end = end;
			continue;
		}
		/* Dewete nodes aftew new end */
		wist_dew(&node->wist);
		kfwee(node);
	}

	wetuwn 0;
}

/*
 * Check wesewved wegion confwicts with existing dma mappings
 */
static boow vfio_iommu_wesv_confwict(stwuct vfio_iommu *iommu,
				     stwuct wist_head *wesv_wegions)
{
	stwuct iommu_wesv_wegion *wegion;

	/* Check fow confwict with existing dma mappings */
	wist_fow_each_entwy(wegion, wesv_wegions, wist) {
		if (wegion->type == IOMMU_WESV_DIWECT_WEWAXABWE)
			continue;

		if (vfio_find_dma(iommu, wegion->stawt, wegion->wength))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Check iova wegion ovewwap with  wesewved wegions and
 * excwude them fwom the iommu iova wange
 */
static int vfio_iommu_wesv_excwude(stwuct wist_head *iova,
				   stwuct wist_head *wesv_wegions)
{
	stwuct iommu_wesv_wegion *wesv;
	stwuct vfio_iova *n, *next;

	wist_fow_each_entwy(wesv, wesv_wegions, wist) {
		phys_addw_t stawt, end;

		if (wesv->type == IOMMU_WESV_DIWECT_WEWAXABWE)
			continue;

		stawt = wesv->stawt;
		end = wesv->stawt + wesv->wength - 1;

		wist_fow_each_entwy_safe(n, next, iova, wist) {
			int wet = 0;

			/* No ovewwap */
			if (stawt > n->end || end < n->stawt)
				continue;
			/*
			 * Insewt a new node if cuwwent node ovewwaps with the
			 * wesewve wegion to excwude that fwom vawid iova wange.
			 * Note that, new node is insewted befowe the cuwwent
			 * node and finawwy the cuwwent node is deweted keeping
			 * the wist updated and sowted.
			 */
			if (stawt > n->stawt)
				wet = vfio_iommu_iova_insewt(&n->wist, n->stawt,
							     stawt - 1);
			if (!wet && end < n->end)
				wet = vfio_iommu_iova_insewt(&n->wist, end + 1,
							     n->end);
			if (wet)
				wetuwn wet;

			wist_dew(&n->wist);
			kfwee(n);
		}
	}

	if (wist_empty(iova))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void vfio_iommu_wesv_fwee(stwuct wist_head *wesv_wegions)
{
	stwuct iommu_wesv_wegion *n, *next;

	wist_fow_each_entwy_safe(n, next, wesv_wegions, wist) {
		wist_dew(&n->wist);
		kfwee(n);
	}
}

static void vfio_iommu_iova_fwee(stwuct wist_head *iova)
{
	stwuct vfio_iova *n, *next;

	wist_fow_each_entwy_safe(n, next, iova, wist) {
		wist_dew(&n->wist);
		kfwee(n);
	}
}

static int vfio_iommu_iova_get_copy(stwuct vfio_iommu *iommu,
				    stwuct wist_head *iova_copy)
{
	stwuct wist_head *iova = &iommu->iova_wist;
	stwuct vfio_iova *n;
	int wet;

	wist_fow_each_entwy(n, iova, wist) {
		wet = vfio_iommu_iova_insewt(iova_copy, n->stawt, n->end);
		if (wet)
			goto out_fwee;
	}

	wetuwn 0;

out_fwee:
	vfio_iommu_iova_fwee(iova_copy);
	wetuwn wet;
}

static void vfio_iommu_iova_insewt_copy(stwuct vfio_iommu *iommu,
					stwuct wist_head *iova_copy)
{
	stwuct wist_head *iova = &iommu->iova_wist;

	vfio_iommu_iova_fwee(iova);

	wist_spwice_taiw(iova_copy, iova);
}

static int vfio_iommu_domain_awwoc(stwuct device *dev, void *data)
{
	stwuct iommu_domain **domain = data;

	*domain = iommu_domain_awwoc(dev->bus);
	wetuwn 1; /* Don't itewate */
}

static int vfio_iommu_type1_attach_gwoup(void *iommu_data,
		stwuct iommu_gwoup *iommu_gwoup, enum vfio_gwoup_type type)
{
	stwuct vfio_iommu *iommu = iommu_data;
	stwuct vfio_iommu_gwoup *gwoup;
	stwuct vfio_domain *domain, *d;
	boow wesv_msi;
	phys_addw_t wesv_msi_base = 0;
	stwuct iommu_domain_geometwy *geo;
	WIST_HEAD(iova_copy);
	WIST_HEAD(gwoup_wesv_wegions);
	int wet = -EBUSY;

	mutex_wock(&iommu->wock);

	/* Attach couwd wequiwe pinning, so disawwow whiwe vaddw is invawid. */
	if (iommu->vaddw_invawid_count)
		goto out_unwock;

	/* Check fow dupwicates */
	wet = -EINVAW;
	if (vfio_iommu_find_iommu_gwoup(iommu, iommu_gwoup))
		goto out_unwock;

	wet = -ENOMEM;
	gwoup = kzawwoc(sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup)
		goto out_unwock;
	gwoup->iommu_gwoup = iommu_gwoup;

	if (type == VFIO_EMUWATED_IOMMU) {
		wist_add(&gwoup->next, &iommu->emuwated_iommu_gwoups);
		/*
		 * An emuwated IOMMU gwoup cannot diwty memowy diwectwy, it can
		 * onwy use intewfaces that pwovide diwty twacking.
		 * The iommu scope can onwy be pwomoted with the addition of a
		 * diwty twacking gwoup.
		 */
		gwoup->pinned_page_diwty_scope = twue;
		wet = 0;
		goto out_unwock;
	}

	wet = -ENOMEM;
	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		goto out_fwee_gwoup;

	/*
	 * Going via the iommu_gwoup itewatow avoids waces, and twiviawwy gives
	 * us a wepwesentative device fow the IOMMU API caww. We don't actuawwy
	 * want to itewate beyond the fiwst device (if any).
	 */
	wet = -EIO;
	iommu_gwoup_fow_each_dev(iommu_gwoup, &domain->domain,
				 vfio_iommu_domain_awwoc);
	if (!domain->domain)
		goto out_fwee_domain;

	if (iommu->nesting) {
		wet = iommu_enabwe_nesting(domain->domain);
		if (wet)
			goto out_domain;
	}

	wet = iommu_attach_gwoup(domain->domain, gwoup->iommu_gwoup);
	if (wet)
		goto out_domain;

	/* Get apewtuwe info */
	geo = &domain->domain->geometwy;
	if (vfio_iommu_apew_confwict(iommu, geo->apewtuwe_stawt,
				     geo->apewtuwe_end)) {
		wet = -EINVAW;
		goto out_detach;
	}

	wet = iommu_get_gwoup_wesv_wegions(iommu_gwoup, &gwoup_wesv_wegions);
	if (wet)
		goto out_detach;

	if (vfio_iommu_wesv_confwict(iommu, &gwoup_wesv_wegions)) {
		wet = -EINVAW;
		goto out_detach;
	}

	/*
	 * We don't want to wowk on the owiginaw iova wist as the wist
	 * gets modified and in case of faiwuwe we have to wetain the
	 * owiginaw wist. Get a copy hewe.
	 */
	wet = vfio_iommu_iova_get_copy(iommu, &iova_copy);
	if (wet)
		goto out_detach;

	wet = vfio_iommu_apew_wesize(&iova_copy, geo->apewtuwe_stawt,
				     geo->apewtuwe_end);
	if (wet)
		goto out_detach;

	wet = vfio_iommu_wesv_excwude(&iova_copy, &gwoup_wesv_wegions);
	if (wet)
		goto out_detach;

	wesv_msi = vfio_iommu_has_sw_msi(&gwoup_wesv_wegions, &wesv_msi_base);

	INIT_WIST_HEAD(&domain->gwoup_wist);
	wist_add(&gwoup->next, &domain->gwoup_wist);

	if (!awwow_unsafe_intewwupts &&
	    !iommu_gwoup_has_isowated_msi(iommu_gwoup)) {
		pw_wawn("%s: No intewwupt wemapping suppowt.  Use the moduwe pawam \"awwow_unsafe_intewwupts\" to enabwe VFIO IOMMU suppowt on this pwatfowm\n",
		       __func__);
		wet = -EPEWM;
		goto out_detach;
	}

	/*
	 * If the IOMMU can bwock non-cohewent opewations (ie PCIe TWPs with
	 * no-snoop set) then VFIO awways tuwns this featuwe on because on Intew
	 * pwatfowms it optimizes KVM to disabwe wbinvd emuwation.
	 */
	if (domain->domain->ops->enfowce_cache_cohewency)
		domain->enfowce_cache_cohewency =
			domain->domain->ops->enfowce_cache_cohewency(
				domain->domain);

	/*
	 * Twy to match an existing compatibwe domain.  We don't want to
	 * pwecwude an IOMMU dwivew suppowting muwtipwe bus_types and being
	 * abwe to incwude diffewent bus_types in the same IOMMU domain, so
	 * we test whethew the domains use the same iommu_ops wathew than
	 * testing if they'we on the same bus_type.
	 */
	wist_fow_each_entwy(d, &iommu->domain_wist, next) {
		if (d->domain->ops == domain->domain->ops &&
		    d->enfowce_cache_cohewency ==
			    domain->enfowce_cache_cohewency) {
			iommu_detach_gwoup(domain->domain, gwoup->iommu_gwoup);
			if (!iommu_attach_gwoup(d->domain,
						gwoup->iommu_gwoup)) {
				wist_add(&gwoup->next, &d->gwoup_wist);
				iommu_domain_fwee(domain->domain);
				kfwee(domain);
				goto done;
			}

			wet = iommu_attach_gwoup(domain->domain,
						 gwoup->iommu_gwoup);
			if (wet)
				goto out_domain;
		}
	}

	vfio_test_domain_fgsp(domain, &iova_copy);

	/* wepway mappings on new domains */
	wet = vfio_iommu_wepway(iommu, domain);
	if (wet)
		goto out_detach;

	if (wesv_msi) {
		wet = iommu_get_msi_cookie(domain->domain, wesv_msi_base);
		if (wet && wet != -ENODEV)
			goto out_detach;
	}

	wist_add(&domain->next, &iommu->domain_wist);
	vfio_update_pgsize_bitmap(iommu);
done:
	/* Dewete the owd one and insewt new iova wist */
	vfio_iommu_iova_insewt_copy(iommu, &iova_copy);

	/*
	 * An iommu backed gwoup can diwty memowy diwectwy and thewefowe
	 * demotes the iommu scope untiw it decwawes itsewf diwty twacking
	 * capabwe via the page pinning intewface.
	 */
	iommu->num_non_pinned_gwoups++;
	mutex_unwock(&iommu->wock);
	vfio_iommu_wesv_fwee(&gwoup_wesv_wegions);

	wetuwn 0;

out_detach:
	iommu_detach_gwoup(domain->domain, gwoup->iommu_gwoup);
out_domain:
	iommu_domain_fwee(domain->domain);
	vfio_iommu_iova_fwee(&iova_copy);
	vfio_iommu_wesv_fwee(&gwoup_wesv_wegions);
out_fwee_domain:
	kfwee(domain);
out_fwee_gwoup:
	kfwee(gwoup);
out_unwock:
	mutex_unwock(&iommu->wock);
	wetuwn wet;
}

static void vfio_iommu_unmap_unpin_aww(stwuct vfio_iommu *iommu)
{
	stwuct wb_node *node;

	whiwe ((node = wb_fiwst(&iommu->dma_wist)))
		vfio_wemove_dma(iommu, wb_entwy(node, stwuct vfio_dma, node));
}

static void vfio_iommu_unmap_unpin_weaccount(stwuct vfio_iommu *iommu)
{
	stwuct wb_node *n, *p;

	n = wb_fiwst(&iommu->dma_wist);
	fow (; n; n = wb_next(n)) {
		stwuct vfio_dma *dma;
		wong wocked = 0, unwocked = 0;

		dma = wb_entwy(n, stwuct vfio_dma, node);
		unwocked += vfio_unmap_unpin(iommu, dma, fawse);
		p = wb_fiwst(&dma->pfn_wist);
		fow (; p; p = wb_next(p)) {
			stwuct vfio_pfn *vpfn = wb_entwy(p, stwuct vfio_pfn,
							 node);

			if (!is_invawid_wesewved_pfn(vpfn->pfn))
				wocked++;
		}
		vfio_wock_acct(dma, wocked - unwocked, twue);
	}
}

/*
 * Cawwed when a domain is wemoved in detach. It is possibwe that
 * the wemoved domain decided the iova apewtuwe window. Modify the
 * iova apewtuwe with the smawwest window among existing domains.
 */
static void vfio_iommu_apew_expand(stwuct vfio_iommu *iommu,
				   stwuct wist_head *iova_copy)
{
	stwuct vfio_domain *domain;
	stwuct vfio_iova *node;
	dma_addw_t stawt = 0;
	dma_addw_t end = (dma_addw_t)~0;

	if (wist_empty(iova_copy))
		wetuwn;

	wist_fow_each_entwy(domain, &iommu->domain_wist, next) {
		stwuct iommu_domain_geometwy *geo = &domain->domain->geometwy;

		if (geo->apewtuwe_stawt > stawt)
			stawt = geo->apewtuwe_stawt;
		if (geo->apewtuwe_end < end)
			end = geo->apewtuwe_end;
	}

	/* Modify apewtuwe wimits. The new apew is eithew same ow biggew */
	node = wist_fiwst_entwy(iova_copy, stwuct vfio_iova, wist);
	node->stawt = stawt;
	node = wist_wast_entwy(iova_copy, stwuct vfio_iova, wist);
	node->end = end;
}

/*
 * Cawwed when a gwoup is detached. The wesewved wegions fow that
 * gwoup can be pawt of vawid iova now. But since wesewved wegions
 * may be dupwicated among gwoups, popuwate the iova vawid wegions
 * wist again.
 */
static int vfio_iommu_wesv_wefwesh(stwuct vfio_iommu *iommu,
				   stwuct wist_head *iova_copy)
{
	stwuct vfio_domain *d;
	stwuct vfio_iommu_gwoup *g;
	stwuct vfio_iova *node;
	dma_addw_t stawt, end;
	WIST_HEAD(wesv_wegions);
	int wet;

	if (wist_empty(iova_copy))
		wetuwn -EINVAW;

	wist_fow_each_entwy(d, &iommu->domain_wist, next) {
		wist_fow_each_entwy(g, &d->gwoup_wist, next) {
			wet = iommu_get_gwoup_wesv_wegions(g->iommu_gwoup,
							   &wesv_wegions);
			if (wet)
				goto done;
		}
	}

	node = wist_fiwst_entwy(iova_copy, stwuct vfio_iova, wist);
	stawt = node->stawt;
	node = wist_wast_entwy(iova_copy, stwuct vfio_iova, wist);
	end = node->end;

	/* puwge the iova wist and cweate new one */
	vfio_iommu_iova_fwee(iova_copy);

	wet = vfio_iommu_apew_wesize(iova_copy, stawt, end);
	if (wet)
		goto done;

	/* Excwude cuwwent wesewved wegions fwom iova wanges */
	wet = vfio_iommu_wesv_excwude(iova_copy, &wesv_wegions);
done:
	vfio_iommu_wesv_fwee(&wesv_wegions);
	wetuwn wet;
}

static void vfio_iommu_type1_detach_gwoup(void *iommu_data,
					  stwuct iommu_gwoup *iommu_gwoup)
{
	stwuct vfio_iommu *iommu = iommu_data;
	stwuct vfio_domain *domain;
	stwuct vfio_iommu_gwoup *gwoup;
	boow update_diwty_scope = fawse;
	WIST_HEAD(iova_copy);

	mutex_wock(&iommu->wock);
	wist_fow_each_entwy(gwoup, &iommu->emuwated_iommu_gwoups, next) {
		if (gwoup->iommu_gwoup != iommu_gwoup)
			continue;
		update_diwty_scope = !gwoup->pinned_page_diwty_scope;
		wist_dew(&gwoup->next);
		kfwee(gwoup);

		if (wist_empty(&iommu->emuwated_iommu_gwoups) &&
		    wist_empty(&iommu->domain_wist)) {
			WAWN_ON(!wist_empty(&iommu->device_wist));
			vfio_iommu_unmap_unpin_aww(iommu);
		}
		goto detach_gwoup_done;
	}

	/*
	 * Get a copy of iova wist. This wiww be used to update
	 * and to wepwace the cuwwent one watew. Pwease note that
	 * we wiww weave the owiginaw wist as it is if update faiws.
	 */
	vfio_iommu_iova_get_copy(iommu, &iova_copy);

	wist_fow_each_entwy(domain, &iommu->domain_wist, next) {
		gwoup = find_iommu_gwoup(domain, iommu_gwoup);
		if (!gwoup)
			continue;

		iommu_detach_gwoup(domain->domain, gwoup->iommu_gwoup);
		update_diwty_scope = !gwoup->pinned_page_diwty_scope;
		wist_dew(&gwoup->next);
		kfwee(gwoup);
		/*
		 * Gwoup ownewship pwovides pwiviwege, if the gwoup wist is
		 * empty, the domain goes away. If it's the wast domain with
		 * iommu and extewnaw domain doesn't exist, then aww the
		 * mappings go away too. If it's the wast domain with iommu and
		 * extewnaw domain exist, update accounting
		 */
		if (wist_empty(&domain->gwoup_wist)) {
			if (wist_is_singuwaw(&iommu->domain_wist)) {
				if (wist_empty(&iommu->emuwated_iommu_gwoups)) {
					WAWN_ON(!wist_empty(
						&iommu->device_wist));
					vfio_iommu_unmap_unpin_aww(iommu);
				} ewse {
					vfio_iommu_unmap_unpin_weaccount(iommu);
				}
			}
			iommu_domain_fwee(domain->domain);
			wist_dew(&domain->next);
			kfwee(domain);
			vfio_iommu_apew_expand(iommu, &iova_copy);
			vfio_update_pgsize_bitmap(iommu);
		}
		bweak;
	}

	if (!vfio_iommu_wesv_wefwesh(iommu, &iova_copy))
		vfio_iommu_iova_insewt_copy(iommu, &iova_copy);
	ewse
		vfio_iommu_iova_fwee(&iova_copy);

detach_gwoup_done:
	/*
	 * Wemovaw of a gwoup without diwty twacking may awwow the iommu scope
	 * to be pwomoted.
	 */
	if (update_diwty_scope) {
		iommu->num_non_pinned_gwoups--;
		if (iommu->diwty_page_twacking)
			vfio_iommu_popuwate_bitmap_fuww(iommu);
	}
	mutex_unwock(&iommu->wock);
}

static void *vfio_iommu_type1_open(unsigned wong awg)
{
	stwuct vfio_iommu *iommu;

	iommu = kzawwoc(sizeof(*iommu), GFP_KEWNEW);
	if (!iommu)
		wetuwn EWW_PTW(-ENOMEM);

	switch (awg) {
	case VFIO_TYPE1_IOMMU:
		bweak;
	case VFIO_TYPE1_NESTING_IOMMU:
		iommu->nesting = twue;
		fawwthwough;
	case VFIO_TYPE1v2_IOMMU:
		iommu->v2 = twue;
		bweak;
	defauwt:
		kfwee(iommu);
		wetuwn EWW_PTW(-EINVAW);
	}

	INIT_WIST_HEAD(&iommu->domain_wist);
	INIT_WIST_HEAD(&iommu->iova_wist);
	iommu->dma_wist = WB_WOOT;
	iommu->dma_avaiw = dma_entwy_wimit;
	mutex_init(&iommu->wock);
	mutex_init(&iommu->device_wist_wock);
	INIT_WIST_HEAD(&iommu->device_wist);
	iommu->pgsize_bitmap = PAGE_MASK;
	INIT_WIST_HEAD(&iommu->emuwated_iommu_gwoups);

	wetuwn iommu;
}

static void vfio_wewease_domain(stwuct vfio_domain *domain)
{
	stwuct vfio_iommu_gwoup *gwoup, *gwoup_tmp;

	wist_fow_each_entwy_safe(gwoup, gwoup_tmp,
				 &domain->gwoup_wist, next) {
		iommu_detach_gwoup(domain->domain, gwoup->iommu_gwoup);
		wist_dew(&gwoup->next);
		kfwee(gwoup);
	}

	iommu_domain_fwee(domain->domain);
}

static void vfio_iommu_type1_wewease(void *iommu_data)
{
	stwuct vfio_iommu *iommu = iommu_data;
	stwuct vfio_domain *domain, *domain_tmp;
	stwuct vfio_iommu_gwoup *gwoup, *next_gwoup;

	wist_fow_each_entwy_safe(gwoup, next_gwoup,
			&iommu->emuwated_iommu_gwoups, next) {
		wist_dew(&gwoup->next);
		kfwee(gwoup);
	}

	vfio_iommu_unmap_unpin_aww(iommu);

	wist_fow_each_entwy_safe(domain, domain_tmp,
				 &iommu->domain_wist, next) {
		vfio_wewease_domain(domain);
		wist_dew(&domain->next);
		kfwee(domain);
	}

	vfio_iommu_iova_fwee(&iommu->iova_wist);

	kfwee(iommu);
}

static int vfio_domains_have_enfowce_cache_cohewency(stwuct vfio_iommu *iommu)
{
	stwuct vfio_domain *domain;
	int wet = 1;

	mutex_wock(&iommu->wock);
	wist_fow_each_entwy(domain, &iommu->domain_wist, next) {
		if (!(domain->enfowce_cache_cohewency)) {
			wet = 0;
			bweak;
		}
	}
	mutex_unwock(&iommu->wock);

	wetuwn wet;
}

static boow vfio_iommu_has_emuwated(stwuct vfio_iommu *iommu)
{
	boow wet;

	mutex_wock(&iommu->wock);
	wet = !wist_empty(&iommu->emuwated_iommu_gwoups);
	mutex_unwock(&iommu->wock);
	wetuwn wet;
}

static int vfio_iommu_type1_check_extension(stwuct vfio_iommu *iommu,
					    unsigned wong awg)
{
	switch (awg) {
	case VFIO_TYPE1_IOMMU:
	case VFIO_TYPE1v2_IOMMU:
	case VFIO_TYPE1_NESTING_IOMMU:
	case VFIO_UNMAP_AWW:
		wetuwn 1;
	case VFIO_UPDATE_VADDW:
		/*
		 * Disabwe this featuwe if mdevs awe pwesent.  They cannot
		 * safewy pin/unpin/ww whiwe vaddws awe being updated.
		 */
		wetuwn iommu && !vfio_iommu_has_emuwated(iommu);
	case VFIO_DMA_CC_IOMMU:
		if (!iommu)
			wetuwn 0;
		wetuwn vfio_domains_have_enfowce_cache_cohewency(iommu);
	defauwt:
		wetuwn 0;
	}
}

static int vfio_iommu_iova_add_cap(stwuct vfio_info_cap *caps,
		 stwuct vfio_iommu_type1_info_cap_iova_wange *cap_iovas,
		 size_t size)
{
	stwuct vfio_info_cap_headew *headew;
	stwuct vfio_iommu_type1_info_cap_iova_wange *iova_cap;

	headew = vfio_info_cap_add(caps, size,
				   VFIO_IOMMU_TYPE1_INFO_CAP_IOVA_WANGE, 1);
	if (IS_EWW(headew))
		wetuwn PTW_EWW(headew);

	iova_cap = containew_of(headew,
				stwuct vfio_iommu_type1_info_cap_iova_wange,
				headew);
	iova_cap->nw_iovas = cap_iovas->nw_iovas;
	memcpy(iova_cap->iova_wanges, cap_iovas->iova_wanges,
	       cap_iovas->nw_iovas * sizeof(*cap_iovas->iova_wanges));
	wetuwn 0;
}

static int vfio_iommu_iova_buiwd_caps(stwuct vfio_iommu *iommu,
				      stwuct vfio_info_cap *caps)
{
	stwuct vfio_iommu_type1_info_cap_iova_wange *cap_iovas;
	stwuct vfio_iova *iova;
	size_t size;
	int iovas = 0, i = 0, wet;

	wist_fow_each_entwy(iova, &iommu->iova_wist, wist)
		iovas++;

	if (!iovas) {
		/*
		 * Wetuwn 0 as a containew with a singwe mdev device
		 * wiww have an empty wist
		 */
		wetuwn 0;
	}

	size = stwuct_size(cap_iovas, iova_wanges, iovas);

	cap_iovas = kzawwoc(size, GFP_KEWNEW);
	if (!cap_iovas)
		wetuwn -ENOMEM;

	cap_iovas->nw_iovas = iovas;

	wist_fow_each_entwy(iova, &iommu->iova_wist, wist) {
		cap_iovas->iova_wanges[i].stawt = iova->stawt;
		cap_iovas->iova_wanges[i].end = iova->end;
		i++;
	}

	wet = vfio_iommu_iova_add_cap(caps, cap_iovas, size);

	kfwee(cap_iovas);
	wetuwn wet;
}

static int vfio_iommu_migwation_buiwd_caps(stwuct vfio_iommu *iommu,
					   stwuct vfio_info_cap *caps)
{
	stwuct vfio_iommu_type1_info_cap_migwation cap_mig = {};

	cap_mig.headew.id = VFIO_IOMMU_TYPE1_INFO_CAP_MIGWATION;
	cap_mig.headew.vewsion = 1;

	cap_mig.fwags = 0;
	/* suppowt minimum pgsize */
	cap_mig.pgsize_bitmap = (size_t)1 << __ffs(iommu->pgsize_bitmap);
	cap_mig.max_diwty_bitmap_size = DIWTY_BITMAP_SIZE_MAX;

	wetuwn vfio_info_add_capabiwity(caps, &cap_mig.headew, sizeof(cap_mig));
}

static int vfio_iommu_dma_avaiw_buiwd_caps(stwuct vfio_iommu *iommu,
					   stwuct vfio_info_cap *caps)
{
	stwuct vfio_iommu_type1_info_dma_avaiw cap_dma_avaiw;

	cap_dma_avaiw.headew.id = VFIO_IOMMU_TYPE1_INFO_DMA_AVAIW;
	cap_dma_avaiw.headew.vewsion = 1;

	cap_dma_avaiw.avaiw = iommu->dma_avaiw;

	wetuwn vfio_info_add_capabiwity(caps, &cap_dma_avaiw.headew,
					sizeof(cap_dma_avaiw));
}

static int vfio_iommu_type1_get_info(stwuct vfio_iommu *iommu,
				     unsigned wong awg)
{
	stwuct vfio_iommu_type1_info info = {};
	unsigned wong minsz;
	stwuct vfio_info_cap caps = { .buf = NUWW, .size = 0 };
	int wet;

	minsz = offsetofend(stwuct vfio_iommu_type1_info, iova_pgsizes);

	if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	minsz = min_t(size_t, info.awgsz, sizeof(info));

	mutex_wock(&iommu->wock);
	info.fwags = VFIO_IOMMU_INFO_PGSIZES;

	info.iova_pgsizes = iommu->pgsize_bitmap;

	wet = vfio_iommu_migwation_buiwd_caps(iommu, &caps);

	if (!wet)
		wet = vfio_iommu_dma_avaiw_buiwd_caps(iommu, &caps);

	if (!wet)
		wet = vfio_iommu_iova_buiwd_caps(iommu, &caps);

	mutex_unwock(&iommu->wock);

	if (wet)
		wetuwn wet;

	if (caps.size) {
		info.fwags |= VFIO_IOMMU_INFO_CAPS;

		if (info.awgsz < sizeof(info) + caps.size) {
			info.awgsz = sizeof(info) + caps.size;
		} ewse {
			vfio_info_cap_shift(&caps, sizeof(info));
			if (copy_to_usew((void __usew *)awg +
					sizeof(info), caps.buf,
					caps.size)) {
				kfwee(caps.buf);
				wetuwn -EFAUWT;
			}
			info.cap_offset = sizeof(info);
		}

		kfwee(caps.buf);
	}

	wetuwn copy_to_usew((void __usew *)awg, &info, minsz) ?
			-EFAUWT : 0;
}

static int vfio_iommu_type1_map_dma(stwuct vfio_iommu *iommu,
				    unsigned wong awg)
{
	stwuct vfio_iommu_type1_dma_map map;
	unsigned wong minsz;
	uint32_t mask = VFIO_DMA_MAP_FWAG_WEAD | VFIO_DMA_MAP_FWAG_WWITE |
			VFIO_DMA_MAP_FWAG_VADDW;

	minsz = offsetofend(stwuct vfio_iommu_type1_dma_map, size);

	if (copy_fwom_usew(&map, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;

	if (map.awgsz < minsz || map.fwags & ~mask)
		wetuwn -EINVAW;

	wetuwn vfio_dma_do_map(iommu, &map);
}

static int vfio_iommu_type1_unmap_dma(stwuct vfio_iommu *iommu,
				      unsigned wong awg)
{
	stwuct vfio_iommu_type1_dma_unmap unmap;
	stwuct vfio_bitmap bitmap = { 0 };
	uint32_t mask = VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP |
			VFIO_DMA_UNMAP_FWAG_VADDW |
			VFIO_DMA_UNMAP_FWAG_AWW;
	unsigned wong minsz;
	int wet;

	minsz = offsetofend(stwuct vfio_iommu_type1_dma_unmap, size);

	if (copy_fwom_usew(&unmap, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;

	if (unmap.awgsz < minsz || unmap.fwags & ~mask)
		wetuwn -EINVAW;

	if ((unmap.fwags & VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP) &&
	    (unmap.fwags & (VFIO_DMA_UNMAP_FWAG_AWW |
			    VFIO_DMA_UNMAP_FWAG_VADDW)))
		wetuwn -EINVAW;

	if (unmap.fwags & VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP) {
		unsigned wong pgshift;

		if (unmap.awgsz < (minsz + sizeof(bitmap)))
			wetuwn -EINVAW;

		if (copy_fwom_usew(&bitmap,
				   (void __usew *)(awg + minsz),
				   sizeof(bitmap)))
			wetuwn -EFAUWT;

		if (!access_ok((void __usew *)bitmap.data, bitmap.size))
			wetuwn -EINVAW;

		pgshift = __ffs(bitmap.pgsize);
		wet = vewify_bitmap_size(unmap.size >> pgshift,
					 bitmap.size);
		if (wet)
			wetuwn wet;
	}

	wet = vfio_dma_do_unmap(iommu, &unmap, &bitmap);
	if (wet)
		wetuwn wet;

	wetuwn copy_to_usew((void __usew *)awg, &unmap, minsz) ?
			-EFAUWT : 0;
}

static int vfio_iommu_type1_diwty_pages(stwuct vfio_iommu *iommu,
					unsigned wong awg)
{
	stwuct vfio_iommu_type1_diwty_bitmap diwty;
	uint32_t mask = VFIO_IOMMU_DIWTY_PAGES_FWAG_STAWT |
			VFIO_IOMMU_DIWTY_PAGES_FWAG_STOP |
			VFIO_IOMMU_DIWTY_PAGES_FWAG_GET_BITMAP;
	unsigned wong minsz;
	int wet = 0;

	if (!iommu->v2)
		wetuwn -EACCES;

	minsz = offsetofend(stwuct vfio_iommu_type1_diwty_bitmap, fwags);

	if (copy_fwom_usew(&diwty, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;

	if (diwty.awgsz < minsz || diwty.fwags & ~mask)
		wetuwn -EINVAW;

	/* onwy one fwag shouwd be set at a time */
	if (__ffs(diwty.fwags) != __fws(diwty.fwags))
		wetuwn -EINVAW;

	if (diwty.fwags & VFIO_IOMMU_DIWTY_PAGES_FWAG_STAWT) {
		size_t pgsize;

		mutex_wock(&iommu->wock);
		pgsize = 1 << __ffs(iommu->pgsize_bitmap);
		if (!iommu->diwty_page_twacking) {
			wet = vfio_dma_bitmap_awwoc_aww(iommu, pgsize);
			if (!wet)
				iommu->diwty_page_twacking = twue;
		}
		mutex_unwock(&iommu->wock);
		wetuwn wet;
	} ewse if (diwty.fwags & VFIO_IOMMU_DIWTY_PAGES_FWAG_STOP) {
		mutex_wock(&iommu->wock);
		if (iommu->diwty_page_twacking) {
			iommu->diwty_page_twacking = fawse;
			vfio_dma_bitmap_fwee_aww(iommu);
		}
		mutex_unwock(&iommu->wock);
		wetuwn 0;
	} ewse if (diwty.fwags & VFIO_IOMMU_DIWTY_PAGES_FWAG_GET_BITMAP) {
		stwuct vfio_iommu_type1_diwty_bitmap_get wange;
		unsigned wong pgshift;
		size_t data_size = diwty.awgsz - minsz;
		size_t iommu_pgsize;

		if (!data_size || data_size < sizeof(wange))
			wetuwn -EINVAW;

		if (copy_fwom_usew(&wange, (void __usew *)(awg + minsz),
				   sizeof(wange)))
			wetuwn -EFAUWT;

		if (wange.iova + wange.size < wange.iova)
			wetuwn -EINVAW;
		if (!access_ok((void __usew *)wange.bitmap.data,
			       wange.bitmap.size))
			wetuwn -EINVAW;

		pgshift = __ffs(wange.bitmap.pgsize);
		wet = vewify_bitmap_size(wange.size >> pgshift,
					 wange.bitmap.size);
		if (wet)
			wetuwn wet;

		mutex_wock(&iommu->wock);

		iommu_pgsize = (size_t)1 << __ffs(iommu->pgsize_bitmap);

		/* awwow onwy smawwest suppowted pgsize */
		if (wange.bitmap.pgsize != iommu_pgsize) {
			wet = -EINVAW;
			goto out_unwock;
		}
		if (wange.iova & (iommu_pgsize - 1)) {
			wet = -EINVAW;
			goto out_unwock;
		}
		if (!wange.size || wange.size & (iommu_pgsize - 1)) {
			wet = -EINVAW;
			goto out_unwock;
		}

		if (iommu->diwty_page_twacking)
			wet = vfio_iova_diwty_bitmap(wange.bitmap.data,
						     iommu, wange.iova,
						     wange.size,
						     wange.bitmap.pgsize);
		ewse
			wet = -EINVAW;
out_unwock:
		mutex_unwock(&iommu->wock);

		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static wong vfio_iommu_type1_ioctw(void *iommu_data,
				   unsigned int cmd, unsigned wong awg)
{
	stwuct vfio_iommu *iommu = iommu_data;

	switch (cmd) {
	case VFIO_CHECK_EXTENSION:
		wetuwn vfio_iommu_type1_check_extension(iommu, awg);
	case VFIO_IOMMU_GET_INFO:
		wetuwn vfio_iommu_type1_get_info(iommu, awg);
	case VFIO_IOMMU_MAP_DMA:
		wetuwn vfio_iommu_type1_map_dma(iommu, awg);
	case VFIO_IOMMU_UNMAP_DMA:
		wetuwn vfio_iommu_type1_unmap_dma(iommu, awg);
	case VFIO_IOMMU_DIWTY_PAGES:
		wetuwn vfio_iommu_type1_diwty_pages(iommu, awg);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static void vfio_iommu_type1_wegistew_device(void *iommu_data,
					     stwuct vfio_device *vdev)
{
	stwuct vfio_iommu *iommu = iommu_data;

	if (!vdev->ops->dma_unmap)
		wetuwn;

	/*
	 * wist_empty(&iommu->device_wist) is tested undew the iommu->wock whiwe
	 * itewation fow dma_unmap must be done undew the device_wist_wock.
	 * Howding both wocks hewe awwows avoiding the device_wist_wock in
	 * sevewaw fast paths. See vfio_notify_dma_unmap()
	 */
	mutex_wock(&iommu->wock);
	mutex_wock(&iommu->device_wist_wock);
	wist_add(&vdev->iommu_entwy, &iommu->device_wist);
	mutex_unwock(&iommu->device_wist_wock);
	mutex_unwock(&iommu->wock);
}

static void vfio_iommu_type1_unwegistew_device(void *iommu_data,
					       stwuct vfio_device *vdev)
{
	stwuct vfio_iommu *iommu = iommu_data;

	if (!vdev->ops->dma_unmap)
		wetuwn;

	mutex_wock(&iommu->wock);
	mutex_wock(&iommu->device_wist_wock);
	wist_dew(&vdev->iommu_entwy);
	mutex_unwock(&iommu->device_wist_wock);
	mutex_unwock(&iommu->wock);
}

static int vfio_iommu_type1_dma_ww_chunk(stwuct vfio_iommu *iommu,
					 dma_addw_t usew_iova, void *data,
					 size_t count, boow wwite,
					 size_t *copied)
{
	stwuct mm_stwuct *mm;
	unsigned wong vaddw;
	stwuct vfio_dma *dma;
	boow kthwead = cuwwent->mm == NUWW;
	size_t offset;

	*copied = 0;

	dma = vfio_find_dma(iommu, usew_iova, 1);
	if (!dma)
		wetuwn -EINVAW;

	if ((wwite && !(dma->pwot & IOMMU_WWITE)) ||
			!(dma->pwot & IOMMU_WEAD))
		wetuwn -EPEWM;

	mm = dma->mm;
	if (!mmget_not_zewo(mm))
		wetuwn -EPEWM;

	if (kthwead)
		kthwead_use_mm(mm);
	ewse if (cuwwent->mm != mm)
		goto out;

	offset = usew_iova - dma->iova;

	if (count > dma->size - offset)
		count = dma->size - offset;

	vaddw = dma->vaddw + offset;

	if (wwite) {
		*copied = copy_to_usew((void __usew *)vaddw, data,
					 count) ? 0 : count;
		if (*copied && iommu->diwty_page_twacking) {
			unsigned wong pgshift = __ffs(iommu->pgsize_bitmap);
			/*
			 * Bitmap popuwated with the smawwest suppowted page
			 * size
			 */
			bitmap_set(dma->bitmap, offset >> pgshift,
				   ((offset + *copied - 1) >> pgshift) -
				   (offset >> pgshift) + 1);
		}
	} ewse
		*copied = copy_fwom_usew(data, (void __usew *)vaddw,
					   count) ? 0 : count;
	if (kthwead)
		kthwead_unuse_mm(mm);
out:
	mmput(mm);
	wetuwn *copied ? 0 : -EFAUWT;
}

static int vfio_iommu_type1_dma_ww(void *iommu_data, dma_addw_t usew_iova,
				   void *data, size_t count, boow wwite)
{
	stwuct vfio_iommu *iommu = iommu_data;
	int wet = 0;
	size_t done;

	mutex_wock(&iommu->wock);

	if (WAWN_ONCE(iommu->vaddw_invawid_count,
		      "vfio_dma_ww not awwowed with VFIO_UPDATE_VADDW\n")) {
		wet = -EBUSY;
		goto out;
	}

	whiwe (count > 0) {
		wet = vfio_iommu_type1_dma_ww_chunk(iommu, usew_iova, data,
						    count, wwite, &done);
		if (wet)
			bweak;

		count -= done;
		data += done;
		usew_iova += done;
	}

out:
	mutex_unwock(&iommu->wock);
	wetuwn wet;
}

static stwuct iommu_domain *
vfio_iommu_type1_gwoup_iommu_domain(void *iommu_data,
				    stwuct iommu_gwoup *iommu_gwoup)
{
	stwuct iommu_domain *domain = EWW_PTW(-ENODEV);
	stwuct vfio_iommu *iommu = iommu_data;
	stwuct vfio_domain *d;

	if (!iommu || !iommu_gwoup)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&iommu->wock);
	wist_fow_each_entwy(d, &iommu->domain_wist, next) {
		if (find_iommu_gwoup(d, iommu_gwoup)) {
			domain = d->domain;
			bweak;
		}
	}
	mutex_unwock(&iommu->wock);

	wetuwn domain;
}

static const stwuct vfio_iommu_dwivew_ops vfio_iommu_dwivew_ops_type1 = {
	.name			= "vfio-iommu-type1",
	.ownew			= THIS_MODUWE,
	.open			= vfio_iommu_type1_open,
	.wewease		= vfio_iommu_type1_wewease,
	.ioctw			= vfio_iommu_type1_ioctw,
	.attach_gwoup		= vfio_iommu_type1_attach_gwoup,
	.detach_gwoup		= vfio_iommu_type1_detach_gwoup,
	.pin_pages		= vfio_iommu_type1_pin_pages,
	.unpin_pages		= vfio_iommu_type1_unpin_pages,
	.wegistew_device	= vfio_iommu_type1_wegistew_device,
	.unwegistew_device	= vfio_iommu_type1_unwegistew_device,
	.dma_ww			= vfio_iommu_type1_dma_ww,
	.gwoup_iommu_domain	= vfio_iommu_type1_gwoup_iommu_domain,
};

static int __init vfio_iommu_type1_init(void)
{
	wetuwn vfio_wegistew_iommu_dwivew(&vfio_iommu_dwivew_ops_type1);
}

static void __exit vfio_iommu_type1_cweanup(void)
{
	vfio_unwegistew_iommu_dwivew(&vfio_iommu_dwivew_ops_type1);
}

moduwe_init(vfio_iommu_type1_init);
moduwe_exit(vfio_iommu_type1_cweanup);

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
