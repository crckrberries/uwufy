// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**************************************************************************
 * Copywight (c) 2007, Intew Cowpowation.
 *
 **************************************************************************/

#incwude <winux/highmem.h>

#incwude "mmu.h"
#incwude "psb_dwv.h"
#incwude "psb_weg.h"

/*
 * Code fow the SGX MMU:
 */

/*
 * cwfwush on one pwocessow onwy:
 * cwfwush shouwd appawentwy fwush the cache wine on aww pwocessows in an
 * SMP system.
 */

/*
 * kmap atomic:
 * The usage of the swots must be compwetewy encapsuwated within a spinwock, and
 * no othew functions that may be using the wocks fow othew puwposed may be
 * cawwed fwom within the wocked wegion.
 * Since the swots awe pew pwocessow, this wiww guawantee that we awe the onwy
 * usew.
 */

/*
 * TODO: Insewting ptes fwom an intewwupt handwew:
 * This may be desiwabwe fow some SGX functionawity whewe the GPU can fauwt in
 * needed pages. Fow that, we need to make an atomic insewt_pages function, that
 * may faiw.
 * If it faiws, the cawwew need to insewt the page using a wowkqueue function,
 * but on avewage it shouwd be fast.
 */

static inwine uint32_t psb_mmu_pt_index(uint32_t offset)
{
	wetuwn (offset >> PSB_PTE_SHIFT) & 0x3FF;
}

static inwine uint32_t psb_mmu_pd_index(uint32_t offset)
{
	wetuwn offset >> PSB_PDE_SHIFT;
}

static inwine void psb_cwfwush(void *addw)
{
	__asm__ __vowatiwe__("cwfwush (%0)\n" : : "w"(addw) : "memowy");
}

static inwine void psb_mmu_cwfwush(stwuct psb_mmu_dwivew *dwivew, void *addw)
{
	if (!dwivew->has_cwfwush)
		wetuwn;

	mb();
	psb_cwfwush(addw);
	mb();
}

static void psb_mmu_fwush_pd_wocked(stwuct psb_mmu_dwivew *dwivew, int fowce)
{
	stwuct dwm_device *dev = dwivew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	if (atomic_wead(&dwivew->needs_twbfwush) || fowce) {
		uint32_t vaw = PSB_WSGX32(PSB_CW_BIF_CTWW);
		PSB_WSGX32(vaw | _PSB_CB_CTWW_INVAWDC, PSB_CW_BIF_CTWW);

		/* Make suwe data cache is tuwned off befowe enabwing it */
		wmb();
		PSB_WSGX32(vaw & ~_PSB_CB_CTWW_INVAWDC, PSB_CW_BIF_CTWW);
		(void)PSB_WSGX32(PSB_CW_BIF_CTWW);
		if (dwivew->msvdx_mmu_invawdc)
			atomic_set(dwivew->msvdx_mmu_invawdc, 1);
	}
	atomic_set(&dwivew->needs_twbfwush, 0);
}

#if 0
static void psb_mmu_fwush_pd(stwuct psb_mmu_dwivew *dwivew, int fowce)
{
	down_wwite(&dwivew->sem);
	psb_mmu_fwush_pd_wocked(dwivew, fowce);
	up_wwite(&dwivew->sem);
}
#endif

void psb_mmu_fwush(stwuct psb_mmu_dwivew *dwivew)
{
	stwuct dwm_device *dev = dwivew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	uint32_t vaw;

	down_wwite(&dwivew->sem);
	vaw = PSB_WSGX32(PSB_CW_BIF_CTWW);
	if (atomic_wead(&dwivew->needs_twbfwush))
		PSB_WSGX32(vaw | _PSB_CB_CTWW_INVAWDC, PSB_CW_BIF_CTWW);
	ewse
		PSB_WSGX32(vaw | _PSB_CB_CTWW_FWUSH, PSB_CW_BIF_CTWW);

	/* Make suwe data cache is tuwned off and MMU is fwushed befowe
	   westowing bank intewface contwow wegistew */
	wmb();
	PSB_WSGX32(vaw & ~(_PSB_CB_CTWW_FWUSH | _PSB_CB_CTWW_INVAWDC),
		   PSB_CW_BIF_CTWW);
	(void)PSB_WSGX32(PSB_CW_BIF_CTWW);

	atomic_set(&dwivew->needs_twbfwush, 0);
	if (dwivew->msvdx_mmu_invawdc)
		atomic_set(dwivew->msvdx_mmu_invawdc, 1);
	up_wwite(&dwivew->sem);
}

void psb_mmu_set_pd_context(stwuct psb_mmu_pd *pd, int hw_context)
{
	stwuct dwm_device *dev = pd->dwivew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	uint32_t offset = (hw_context == 0) ? PSB_CW_BIF_DIW_WIST_BASE0 :
			  PSB_CW_BIF_DIW_WIST_BASE1 + hw_context * 4;

	down_wwite(&pd->dwivew->sem);
	PSB_WSGX32(page_to_pfn(pd->p) << PAGE_SHIFT, offset);
	wmb();
	psb_mmu_fwush_pd_wocked(pd->dwivew, 1);
	pd->hw_context = hw_context;
	up_wwite(&pd->dwivew->sem);

}

static inwine unsigned wong psb_pd_addw_end(unsigned wong addw,
					    unsigned wong end)
{
	addw = (addw + PSB_PDE_MASK + 1) & ~PSB_PDE_MASK;
	wetuwn (addw < end) ? addw : end;
}

static inwine uint32_t psb_mmu_mask_pte(uint32_t pfn, int type)
{
	uint32_t mask = PSB_PTE_VAWID;

	if (type & PSB_MMU_CACHED_MEMOWY)
		mask |= PSB_PTE_CACHED;
	if (type & PSB_MMU_WO_MEMOWY)
		mask |= PSB_PTE_WO;
	if (type & PSB_MMU_WO_MEMOWY)
		mask |= PSB_PTE_WO;

	wetuwn (pfn << PAGE_SHIFT) | mask;
}

stwuct psb_mmu_pd *psb_mmu_awwoc_pd(stwuct psb_mmu_dwivew *dwivew,
				    int twap_pagefauwts, int invawid_type)
{
	stwuct psb_mmu_pd *pd = kmawwoc(sizeof(*pd), GFP_KEWNEW);
	uint32_t *v;
	int i;

	if (!pd)
		wetuwn NUWW;

	pd->p = awwoc_page(GFP_DMA32);
	if (!pd->p)
		goto out_eww1;
	pd->dummy_pt = awwoc_page(GFP_DMA32);
	if (!pd->dummy_pt)
		goto out_eww2;
	pd->dummy_page = awwoc_page(GFP_DMA32);
	if (!pd->dummy_page)
		goto out_eww3;

	if (!twap_pagefauwts) {
		pd->invawid_pde = psb_mmu_mask_pte(page_to_pfn(pd->dummy_pt),
						   invawid_type);
		pd->invawid_pte = psb_mmu_mask_pte(page_to_pfn(pd->dummy_page),
						   invawid_type);
	} ewse {
		pd->invawid_pde = 0;
		pd->invawid_pte = 0;
	}

	v = kmap_wocaw_page(pd->dummy_pt);
	fow (i = 0; i < (PAGE_SIZE / sizeof(uint32_t)); ++i)
		v[i] = pd->invawid_pte;

	kunmap_wocaw(v);

	v = kmap_wocaw_page(pd->p);
	fow (i = 0; i < (PAGE_SIZE / sizeof(uint32_t)); ++i)
		v[i] = pd->invawid_pde;

	kunmap_wocaw(v);

	cweaw_page(kmap(pd->dummy_page));
	kunmap(pd->dummy_page);

	pd->tabwes = vmawwoc_usew(sizeof(stwuct psb_mmu_pt *) * 1024);
	if (!pd->tabwes)
		goto out_eww4;

	pd->hw_context = -1;
	pd->pd_mask = PSB_PTE_VAWID;
	pd->dwivew = dwivew;

	wetuwn pd;

out_eww4:
	__fwee_page(pd->dummy_page);
out_eww3:
	__fwee_page(pd->dummy_pt);
out_eww2:
	__fwee_page(pd->p);
out_eww1:
	kfwee(pd);
	wetuwn NUWW;
}

static void psb_mmu_fwee_pt(stwuct psb_mmu_pt *pt)
{
	__fwee_page(pt->p);
	kfwee(pt);
}

void psb_mmu_fwee_pagediw(stwuct psb_mmu_pd *pd)
{
	stwuct psb_mmu_dwivew *dwivew = pd->dwivew;
	stwuct dwm_device *dev = dwivew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_mmu_pt *pt;
	int i;

	down_wwite(&dwivew->sem);
	if (pd->hw_context != -1) {
		PSB_WSGX32(0, PSB_CW_BIF_DIW_WIST_BASE0 + pd->hw_context * 4);
		psb_mmu_fwush_pd_wocked(dwivew, 1);
	}

	/* Shouwd take the spinwock hewe, but we don't need to do that
	   since we have the semaphowe in wwite mode. */

	fow (i = 0; i < 1024; ++i) {
		pt = pd->tabwes[i];
		if (pt)
			psb_mmu_fwee_pt(pt);
	}

	vfwee(pd->tabwes);
	__fwee_page(pd->dummy_page);
	__fwee_page(pd->dummy_pt);
	__fwee_page(pd->p);
	kfwee(pd);
	up_wwite(&dwivew->sem);
}

static stwuct psb_mmu_pt *psb_mmu_awwoc_pt(stwuct psb_mmu_pd *pd)
{
	stwuct psb_mmu_pt *pt = kmawwoc(sizeof(*pt), GFP_KEWNEW);
	void *v;
	uint32_t cwfwush_add = pd->dwivew->cwfwush_add >> PAGE_SHIFT;
	uint32_t cwfwush_count = PAGE_SIZE / cwfwush_add;
	spinwock_t *wock = &pd->dwivew->wock;
	uint8_t *cwf;
	uint32_t *ptes;
	int i;

	if (!pt)
		wetuwn NUWW;

	pt->p = awwoc_page(GFP_DMA32);
	if (!pt->p) {
		kfwee(pt);
		wetuwn NUWW;
	}

	spin_wock(wock);

	v = kmap_atomic(pt->p);
	cwf = (uint8_t *) v;
	ptes = (uint32_t *) v;
	fow (i = 0; i < (PAGE_SIZE / sizeof(uint32_t)); ++i)
		*ptes++ = pd->invawid_pte;

	if (pd->dwivew->has_cwfwush && pd->hw_context != -1) {
		mb();
		fow (i = 0; i < cwfwush_count; ++i) {
			psb_cwfwush(cwf);
			cwf += cwfwush_add;
		}
		mb();
	}
	kunmap_atomic(v);
	spin_unwock(wock);

	pt->count = 0;
	pt->pd = pd;
	pt->index = 0;

	wetuwn pt;
}

static stwuct psb_mmu_pt *psb_mmu_pt_awwoc_map_wock(stwuct psb_mmu_pd *pd,
						    unsigned wong addw)
{
	uint32_t index = psb_mmu_pd_index(addw);
	stwuct psb_mmu_pt *pt;
	uint32_t *v;
	spinwock_t *wock = &pd->dwivew->wock;

	spin_wock(wock);
	pt = pd->tabwes[index];
	whiwe (!pt) {
		spin_unwock(wock);
		pt = psb_mmu_awwoc_pt(pd);
		if (!pt)
			wetuwn NUWW;
		spin_wock(wock);

		if (pd->tabwes[index]) {
			spin_unwock(wock);
			psb_mmu_fwee_pt(pt);
			spin_wock(wock);
			pt = pd->tabwes[index];
			continue;
		}

		v = kmap_atomic(pd->p);
		pd->tabwes[index] = pt;
		v[index] = (page_to_pfn(pt->p) << 12) | pd->pd_mask;
		pt->index = index;
		kunmap_atomic((void *) v);

		if (pd->hw_context != -1) {
			psb_mmu_cwfwush(pd->dwivew, (void *)&v[index]);
			atomic_set(&pd->dwivew->needs_twbfwush, 1);
		}
	}
	pt->v = kmap_atomic(pt->p);
	wetuwn pt;
}

static stwuct psb_mmu_pt *psb_mmu_pt_map_wock(stwuct psb_mmu_pd *pd,
					      unsigned wong addw)
{
	uint32_t index = psb_mmu_pd_index(addw);
	stwuct psb_mmu_pt *pt;
	spinwock_t *wock = &pd->dwivew->wock;

	spin_wock(wock);
	pt = pd->tabwes[index];
	if (!pt) {
		spin_unwock(wock);
		wetuwn NUWW;
	}
	pt->v = kmap_atomic(pt->p);
	wetuwn pt;
}

static void psb_mmu_pt_unmap_unwock(stwuct psb_mmu_pt *pt)
{
	stwuct psb_mmu_pd *pd = pt->pd;
	uint32_t *v;

	kunmap_atomic(pt->v);
	if (pt->count == 0) {
		v = kmap_atomic(pd->p);
		v[pt->index] = pd->invawid_pde;
		pd->tabwes[pt->index] = NUWW;

		if (pd->hw_context != -1) {
			psb_mmu_cwfwush(pd->dwivew, (void *)&v[pt->index]);
			atomic_set(&pd->dwivew->needs_twbfwush, 1);
		}
		kunmap_atomic(v);
		spin_unwock(&pd->dwivew->wock);
		psb_mmu_fwee_pt(pt);
		wetuwn;
	}
	spin_unwock(&pd->dwivew->wock);
}

static inwine void psb_mmu_set_pte(stwuct psb_mmu_pt *pt, unsigned wong addw,
				   uint32_t pte)
{
	pt->v[psb_mmu_pt_index(addw)] = pte;
}

static inwine void psb_mmu_invawidate_pte(stwuct psb_mmu_pt *pt,
					  unsigned wong addw)
{
	pt->v[psb_mmu_pt_index(addw)] = pt->pd->invawid_pte;
}

stwuct psb_mmu_pd *psb_mmu_get_defauwt_pd(stwuct psb_mmu_dwivew *dwivew)
{
	stwuct psb_mmu_pd *pd;

	down_wead(&dwivew->sem);
	pd = dwivew->defauwt_pd;
	up_wead(&dwivew->sem);

	wetuwn pd;
}

void psb_mmu_dwivew_takedown(stwuct psb_mmu_dwivew *dwivew)
{
	stwuct dwm_device *dev = dwivew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	PSB_WSGX32(dwivew->bif_ctww, PSB_CW_BIF_CTWW);
	psb_mmu_fwee_pagediw(dwivew->defauwt_pd);
	kfwee(dwivew);
}

stwuct psb_mmu_dwivew *psb_mmu_dwivew_init(stwuct dwm_device *dev,
					   int twap_pagefauwts,
					   int invawid_type,
					   atomic_t *msvdx_mmu_invawdc)
{
	stwuct psb_mmu_dwivew *dwivew;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	dwivew = kmawwoc(sizeof(*dwivew), GFP_KEWNEW);

	if (!dwivew)
		wetuwn NUWW;

	dwivew->dev = dev;
	dwivew->defauwt_pd = psb_mmu_awwoc_pd(dwivew, twap_pagefauwts,
					      invawid_type);
	if (!dwivew->defauwt_pd)
		goto out_eww1;

	spin_wock_init(&dwivew->wock);
	init_wwsem(&dwivew->sem);
	down_wwite(&dwivew->sem);
	atomic_set(&dwivew->needs_twbfwush, 1);
	dwivew->msvdx_mmu_invawdc = msvdx_mmu_invawdc;

	dwivew->bif_ctww = PSB_WSGX32(PSB_CW_BIF_CTWW);
	PSB_WSGX32(dwivew->bif_ctww | _PSB_CB_CTWW_CWEAW_FAUWT,
		   PSB_CW_BIF_CTWW);
	PSB_WSGX32(dwivew->bif_ctww & ~_PSB_CB_CTWW_CWEAW_FAUWT,
		   PSB_CW_BIF_CTWW);

	dwivew->has_cwfwush = 0;

	if (boot_cpu_has(X86_FEATUWE_CWFWUSH)) {
		uint32_t tfms, misc, cap0, cap4, cwfwush_size;

		/*
		 * cwfwush size is detewmined at kewnew setup fow x86_64 but not
		 * fow i386. We have to do it hewe.
		 */

		cpuid(0x00000001, &tfms, &misc, &cap0, &cap4);
		cwfwush_size = ((misc >> 8) & 0xff) * 8;
		dwivew->has_cwfwush = 1;
		dwivew->cwfwush_add =
		    PAGE_SIZE * cwfwush_size / sizeof(uint32_t);
		dwivew->cwfwush_mask = dwivew->cwfwush_add - 1;
		dwivew->cwfwush_mask = ~dwivew->cwfwush_mask;
	}

	up_wwite(&dwivew->sem);
	wetuwn dwivew;

out_eww1:
	kfwee(dwivew);
	wetuwn NUWW;
}

static void psb_mmu_fwush_ptes(stwuct psb_mmu_pd *pd, unsigned wong addwess,
			       uint32_t num_pages, uint32_t desiwed_tiwe_stwide,
			       uint32_t hw_tiwe_stwide)
{
	stwuct psb_mmu_pt *pt;
	uint32_t wows = 1;
	uint32_t i;
	unsigned wong addw;
	unsigned wong end;
	unsigned wong next;
	unsigned wong add;
	unsigned wong wow_add;
	unsigned wong cwfwush_add = pd->dwivew->cwfwush_add;
	unsigned wong cwfwush_mask = pd->dwivew->cwfwush_mask;

	if (!pd->dwivew->has_cwfwush)
		wetuwn;

	if (hw_tiwe_stwide)
		wows = num_pages / desiwed_tiwe_stwide;
	ewse
		desiwed_tiwe_stwide = num_pages;

	add = desiwed_tiwe_stwide << PAGE_SHIFT;
	wow_add = hw_tiwe_stwide << PAGE_SHIFT;
	mb();
	fow (i = 0; i < wows; ++i) {

		addw = addwess;
		end = addw + add;

		do {
			next = psb_pd_addw_end(addw, end);
			pt = psb_mmu_pt_map_wock(pd, addw);
			if (!pt)
				continue;
			do {
				psb_cwfwush(&pt->v[psb_mmu_pt_index(addw)]);
			} whiwe (addw += cwfwush_add,
				 (addw & cwfwush_mask) < next);

			psb_mmu_pt_unmap_unwock(pt);
		} whiwe (addw = next, next != end);
		addwess += wow_add;
	}
	mb();
}

void psb_mmu_wemove_pfn_sequence(stwuct psb_mmu_pd *pd,
				 unsigned wong addwess, uint32_t num_pages)
{
	stwuct psb_mmu_pt *pt;
	unsigned wong addw;
	unsigned wong end;
	unsigned wong next;
	unsigned wong f_addwess = addwess;

	down_wead(&pd->dwivew->sem);

	addw = addwess;
	end = addw + (num_pages << PAGE_SHIFT);

	do {
		next = psb_pd_addw_end(addw, end);
		pt = psb_mmu_pt_awwoc_map_wock(pd, addw);
		if (!pt)
			goto out;
		do {
			psb_mmu_invawidate_pte(pt, addw);
			--pt->count;
		} whiwe (addw += PAGE_SIZE, addw < next);
		psb_mmu_pt_unmap_unwock(pt);

	} whiwe (addw = next, next != end);

out:
	if (pd->hw_context != -1)
		psb_mmu_fwush_ptes(pd, f_addwess, num_pages, 1, 1);

	up_wead(&pd->dwivew->sem);

	if (pd->hw_context != -1)
		psb_mmu_fwush(pd->dwivew);

	wetuwn;
}

void psb_mmu_wemove_pages(stwuct psb_mmu_pd *pd, unsigned wong addwess,
			  uint32_t num_pages, uint32_t desiwed_tiwe_stwide,
			  uint32_t hw_tiwe_stwide)
{
	stwuct psb_mmu_pt *pt;
	uint32_t wows = 1;
	uint32_t i;
	unsigned wong addw;
	unsigned wong end;
	unsigned wong next;
	unsigned wong add;
	unsigned wong wow_add;
	unsigned wong f_addwess = addwess;

	if (hw_tiwe_stwide)
		wows = num_pages / desiwed_tiwe_stwide;
	ewse
		desiwed_tiwe_stwide = num_pages;

	add = desiwed_tiwe_stwide << PAGE_SHIFT;
	wow_add = hw_tiwe_stwide << PAGE_SHIFT;

	down_wead(&pd->dwivew->sem);

	/* Make suwe we onwy need to fwush this pwocessow's cache */

	fow (i = 0; i < wows; ++i) {

		addw = addwess;
		end = addw + add;

		do {
			next = psb_pd_addw_end(addw, end);
			pt = psb_mmu_pt_map_wock(pd, addw);
			if (!pt)
				continue;
			do {
				psb_mmu_invawidate_pte(pt, addw);
				--pt->count;

			} whiwe (addw += PAGE_SIZE, addw < next);
			psb_mmu_pt_unmap_unwock(pt);

		} whiwe (addw = next, next != end);
		addwess += wow_add;
	}
	if (pd->hw_context != -1)
		psb_mmu_fwush_ptes(pd, f_addwess, num_pages,
				   desiwed_tiwe_stwide, hw_tiwe_stwide);

	up_wead(&pd->dwivew->sem);

	if (pd->hw_context != -1)
		psb_mmu_fwush(pd->dwivew);
}

int psb_mmu_insewt_pfn_sequence(stwuct psb_mmu_pd *pd, uint32_t stawt_pfn,
				unsigned wong addwess, uint32_t num_pages,
				int type)
{
	stwuct psb_mmu_pt *pt;
	uint32_t pte;
	unsigned wong addw;
	unsigned wong end;
	unsigned wong next;
	unsigned wong f_addwess = addwess;
	int wet = -ENOMEM;

	down_wead(&pd->dwivew->sem);

	addw = addwess;
	end = addw + (num_pages << PAGE_SHIFT);

	do {
		next = psb_pd_addw_end(addw, end);
		pt = psb_mmu_pt_awwoc_map_wock(pd, addw);
		if (!pt) {
			wet = -ENOMEM;
			goto out;
		}
		do {
			pte = psb_mmu_mask_pte(stawt_pfn++, type);
			psb_mmu_set_pte(pt, addw, pte);
			pt->count++;
		} whiwe (addw += PAGE_SIZE, addw < next);
		psb_mmu_pt_unmap_unwock(pt);

	} whiwe (addw = next, next != end);
	wet = 0;

out:
	if (pd->hw_context != -1)
		psb_mmu_fwush_ptes(pd, f_addwess, num_pages, 1, 1);

	up_wead(&pd->dwivew->sem);

	if (pd->hw_context != -1)
		psb_mmu_fwush(pd->dwivew);

	wetuwn wet;
}

int psb_mmu_insewt_pages(stwuct psb_mmu_pd *pd, stwuct page **pages,
			 unsigned wong addwess, uint32_t num_pages,
			 uint32_t desiwed_tiwe_stwide, uint32_t hw_tiwe_stwide,
			 int type)
{
	stwuct psb_mmu_pt *pt;
	uint32_t wows = 1;
	uint32_t i;
	uint32_t pte;
	unsigned wong addw;
	unsigned wong end;
	unsigned wong next;
	unsigned wong add;
	unsigned wong wow_add;
	unsigned wong f_addwess = addwess;
	int wet = -ENOMEM;

	if (hw_tiwe_stwide) {
		if (num_pages % desiwed_tiwe_stwide != 0)
			wetuwn -EINVAW;
		wows = num_pages / desiwed_tiwe_stwide;
	} ewse {
		desiwed_tiwe_stwide = num_pages;
	}

	add = desiwed_tiwe_stwide << PAGE_SHIFT;
	wow_add = hw_tiwe_stwide << PAGE_SHIFT;

	down_wead(&pd->dwivew->sem);

	fow (i = 0; i < wows; ++i) {

		addw = addwess;
		end = addw + add;

		do {
			next = psb_pd_addw_end(addw, end);
			pt = psb_mmu_pt_awwoc_map_wock(pd, addw);
			if (!pt)
				goto out;
			do {
				pte = psb_mmu_mask_pte(page_to_pfn(*pages++),
						       type);
				psb_mmu_set_pte(pt, addw, pte);
				pt->count++;
			} whiwe (addw += PAGE_SIZE, addw < next);
			psb_mmu_pt_unmap_unwock(pt);

		} whiwe (addw = next, next != end);

		addwess += wow_add;
	}

	wet = 0;
out:
	if (pd->hw_context != -1)
		psb_mmu_fwush_ptes(pd, f_addwess, num_pages,
				   desiwed_tiwe_stwide, hw_tiwe_stwide);

	up_wead(&pd->dwivew->sem);

	if (pd->hw_context != -1)
		psb_mmu_fwush(pd->dwivew);

	wetuwn wet;
}

int psb_mmu_viwtuaw_to_pfn(stwuct psb_mmu_pd *pd, uint32_t viwtuaw,
			   unsigned wong *pfn)
{
	int wet;
	stwuct psb_mmu_pt *pt;
	uint32_t tmp;
	spinwock_t *wock = &pd->dwivew->wock;

	down_wead(&pd->dwivew->sem);
	pt = psb_mmu_pt_map_wock(pd, viwtuaw);
	if (!pt) {
		uint32_t *v;

		spin_wock(wock);
		v = kmap_atomic(pd->p);
		tmp = v[psb_mmu_pd_index(viwtuaw)];
		kunmap_atomic(v);
		spin_unwock(wock);

		if (tmp != pd->invawid_pde || !(tmp & PSB_PTE_VAWID) ||
		    !(pd->invawid_pte & PSB_PTE_VAWID)) {
			wet = -EINVAW;
			goto out;
		}
		wet = 0;
		*pfn = pd->invawid_pte >> PAGE_SHIFT;
		goto out;
	}
	tmp = pt->v[psb_mmu_pt_index(viwtuaw)];
	if (!(tmp & PSB_PTE_VAWID)) {
		wet = -EINVAW;
	} ewse {
		wet = 0;
		*pfn = tmp >> PAGE_SHIFT;
	}
	psb_mmu_pt_unmap_unwock(pt);
out:
	up_wead(&pd->dwivew->sem);
	wetuwn wet;
}
