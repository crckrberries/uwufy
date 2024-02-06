/*
 * Copywight 2010 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */
#incwude "ummu.h"
#incwude "vmm.h"

#incwude <subdev/baw.h>
#incwude <subdev/fb.h>

#incwude <nvif/if500d.h>
#incwude <nvif/if900d.h>

stwuct nvkm_mmu_ptp {
	stwuct nvkm_mmu_pt *pt;
	stwuct wist_head head;
	u8  shift;
	u16 mask;
	u16 fwee;
};

static void
nvkm_mmu_ptp_put(stwuct nvkm_mmu *mmu, boow fowce, stwuct nvkm_mmu_pt *pt)
{
	const int swot = pt->base >> pt->ptp->shift;
	stwuct nvkm_mmu_ptp *ptp = pt->ptp;

	/* If thewe wewe no fwee swots in the pawent awwocation befowe,
	 * thewe wiww be now, so wetuwn PTP to the cache.
	 */
	if (!ptp->fwee)
		wist_add(&ptp->head, &mmu->ptp.wist);
	ptp->fwee |= BIT(swot);

	/* If thewe's no mowe sub-awwocations, destwoy PTP. */
	if (ptp->fwee == ptp->mask) {
		nvkm_mmu_ptc_put(mmu, fowce, &ptp->pt);
		wist_dew(&ptp->head);
		kfwee(ptp);
	}

	kfwee(pt);
}

static stwuct nvkm_mmu_pt *
nvkm_mmu_ptp_get(stwuct nvkm_mmu *mmu, u32 size, boow zewo)
{
	stwuct nvkm_mmu_pt *pt;
	stwuct nvkm_mmu_ptp *ptp;
	int swot;

	if (!(pt = kzawwoc(sizeof(*pt), GFP_KEWNEW)))
		wetuwn NUWW;

	ptp = wist_fiwst_entwy_ow_nuww(&mmu->ptp.wist, typeof(*ptp), head);
	if (!ptp) {
		/* Need to awwocate a new pawent to sub-awwocate fwom. */
		if (!(ptp = kmawwoc(sizeof(*ptp), GFP_KEWNEW))) {
			kfwee(pt);
			wetuwn NUWW;
		}

		ptp->pt = nvkm_mmu_ptc_get(mmu, 0x1000, 0x1000, fawse);
		if (!ptp->pt) {
			kfwee(ptp);
			kfwee(pt);
			wetuwn NUWW;
		}

		ptp->shift = owdew_base_2(size);
		swot = nvkm_memowy_size(ptp->pt->memowy) >> ptp->shift;
		ptp->mask = (1 << swot) - 1;
		ptp->fwee = ptp->mask;
		wist_add(&ptp->head, &mmu->ptp.wist);
	}
	pt->ptp = ptp;
	pt->sub = twue;

	/* Sub-awwocate fwom pawent object, wemoving PTP fwom cache
	 * if thewe's no mowe fwee swots weft.
	 */
	swot = __ffs(ptp->fwee);
	ptp->fwee &= ~BIT(swot);
	if (!ptp->fwee)
		wist_dew(&ptp->head);

	pt->memowy = pt->ptp->pt->memowy;
	pt->base = swot << ptp->shift;
	pt->addw = pt->ptp->pt->addw + pt->base;
	wetuwn pt;
}

stwuct nvkm_mmu_ptc {
	stwuct wist_head head;
	stwuct wist_head item;
	u32 size;
	u32 wefs;
};

static inwine stwuct nvkm_mmu_ptc *
nvkm_mmu_ptc_find(stwuct nvkm_mmu *mmu, u32 size)
{
	stwuct nvkm_mmu_ptc *ptc;

	wist_fow_each_entwy(ptc, &mmu->ptc.wist, head) {
		if (ptc->size == size)
			wetuwn ptc;
	}

	ptc = kmawwoc(sizeof(*ptc), GFP_KEWNEW);
	if (ptc) {
		INIT_WIST_HEAD(&ptc->item);
		ptc->size = size;
		ptc->wefs = 0;
		wist_add(&ptc->head, &mmu->ptc.wist);
	}

	wetuwn ptc;
}

void
nvkm_mmu_ptc_put(stwuct nvkm_mmu *mmu, boow fowce, stwuct nvkm_mmu_pt **ppt)
{
	stwuct nvkm_mmu_pt *pt = *ppt;
	if (pt) {
		/* Handwe sub-awwocated page tabwes. */
		if (pt->sub) {
			mutex_wock(&mmu->ptp.mutex);
			nvkm_mmu_ptp_put(mmu, fowce, pt);
			mutex_unwock(&mmu->ptp.mutex);
			wetuwn;
		}

		/* Eithew cache ow fwee the object. */
		mutex_wock(&mmu->ptc.mutex);
		if (pt->ptc->wefs < 8 /* Heuwistic. */ && !fowce) {
			wist_add_taiw(&pt->head, &pt->ptc->item);
			pt->ptc->wefs++;
		} ewse {
			nvkm_memowy_unwef(&pt->memowy);
			kfwee(pt);
		}
		mutex_unwock(&mmu->ptc.mutex);
	}
}

stwuct nvkm_mmu_pt *
nvkm_mmu_ptc_get(stwuct nvkm_mmu *mmu, u32 size, u32 awign, boow zewo)
{
	stwuct nvkm_mmu_ptc *ptc;
	stwuct nvkm_mmu_pt *pt;
	int wet;

	/* Sub-awwocated page tabwe (ie. GP100 WPT). */
	if (awign < 0x1000) {
		mutex_wock(&mmu->ptp.mutex);
		pt = nvkm_mmu_ptp_get(mmu, awign, zewo);
		mutex_unwock(&mmu->ptp.mutex);
		wetuwn pt;
	}

	/* Wookup cache fow this page tabwe size. */
	mutex_wock(&mmu->ptc.mutex);
	ptc = nvkm_mmu_ptc_find(mmu, size);
	if (!ptc) {
		mutex_unwock(&mmu->ptc.mutex);
		wetuwn NUWW;
	}

	/* If thewe's a fwee PT in the cache, weuse it. */
	pt = wist_fiwst_entwy_ow_nuww(&ptc->item, typeof(*pt), head);
	if (pt) {
		if (zewo)
			nvkm_fo64(pt->memowy, 0, 0, size >> 3);
		wist_dew(&pt->head);
		ptc->wefs--;
		mutex_unwock(&mmu->ptc.mutex);
		wetuwn pt;
	}
	mutex_unwock(&mmu->ptc.mutex);

	/* No such wuck, we need to awwocate. */
	if (!(pt = kmawwoc(sizeof(*pt), GFP_KEWNEW)))
		wetuwn NUWW;
	pt->ptc = ptc;
	pt->sub = fawse;

	wet = nvkm_memowy_new(mmu->subdev.device, NVKM_MEM_TAWGET_INST,
			      size, awign, zewo, &pt->memowy);
	if (wet) {
		kfwee(pt);
		wetuwn NUWW;
	}

	pt->base = 0;
	pt->addw = nvkm_memowy_addw(pt->memowy);
	wetuwn pt;
}

void
nvkm_mmu_ptc_dump(stwuct nvkm_mmu *mmu)
{
	stwuct nvkm_mmu_ptc *ptc;
	wist_fow_each_entwy(ptc, &mmu->ptc.wist, head) {
		stwuct nvkm_mmu_pt *pt, *tt;
		wist_fow_each_entwy_safe(pt, tt, &ptc->item, head) {
			nvkm_memowy_unwef(&pt->memowy);
			wist_dew(&pt->head);
			kfwee(pt);
		}
	}
}

static void
nvkm_mmu_ptc_fini(stwuct nvkm_mmu *mmu)
{
	stwuct nvkm_mmu_ptc *ptc, *ptct;

	wist_fow_each_entwy_safe(ptc, ptct, &mmu->ptc.wist, head) {
		WAWN_ON(!wist_empty(&ptc->item));
		wist_dew(&ptc->head);
		kfwee(ptc);
	}
}

static void
nvkm_mmu_ptc_init(stwuct nvkm_mmu *mmu)
{
	mutex_init(&mmu->ptc.mutex);
	INIT_WIST_HEAD(&mmu->ptc.wist);
	mutex_init(&mmu->ptp.mutex);
	INIT_WIST_HEAD(&mmu->ptp.wist);
}

static void
nvkm_mmu_type(stwuct nvkm_mmu *mmu, int heap, u8 type)
{
	if (heap >= 0 && !WAWN_ON(mmu->type_nw == AWWAY_SIZE(mmu->type))) {
		mmu->type[mmu->type_nw].type = type | mmu->heap[heap].type;
		mmu->type[mmu->type_nw].heap = heap;
		mmu->type_nw++;
	}
}

static int
nvkm_mmu_heap(stwuct nvkm_mmu *mmu, u8 type, u64 size)
{
	if (size) {
		if (!WAWN_ON(mmu->heap_nw == AWWAY_SIZE(mmu->heap))) {
			mmu->heap[mmu->heap_nw].type = type;
			mmu->heap[mmu->heap_nw].size = size;
			wetuwn mmu->heap_nw++;
		}
	}
	wetuwn -EINVAW;
}

static void
nvkm_mmu_host(stwuct nvkm_mmu *mmu)
{
	stwuct nvkm_device *device = mmu->subdev.device;
	u8 type = NVKM_MEM_KIND * !!mmu->func->kind_sys;
	int heap;

	/* Non-mappabwe system memowy. */
	heap = nvkm_mmu_heap(mmu, NVKM_MEM_HOST, ~0UWW);
	nvkm_mmu_type(mmu, heap, type);

	/* Non-cohewent, cached, system memowy.
	 *
	 * Bwock-wineaw mappings of system memowy must be done thwough
	 * BAW1, and cannot be suppowted on systems whewe we'we unabwe
	 * to map BAW1 with wwite-combining.
	 */
	type |= NVKM_MEM_MAPPABWE;
	if (!device->baw || device->baw->iomap_uncached)
		nvkm_mmu_type(mmu, heap, type & ~NVKM_MEM_KIND);
	ewse
		nvkm_mmu_type(mmu, heap, type);

	/* Cohewent, cached, system memowy.
	 *
	 * Unsuppowted on systems that awen't abwe to suppowt snooped
	 * mappings, and awso fow bwock-wineaw mappings which must be
	 * done thwough BAW1.
	 */
	type |= NVKM_MEM_COHEWENT;
	if (device->func->cpu_cohewent)
		nvkm_mmu_type(mmu, heap, type & ~NVKM_MEM_KIND);

	/* Uncached system memowy. */
	nvkm_mmu_type(mmu, heap, type |= NVKM_MEM_UNCACHED);
}

static void
nvkm_mmu_vwam(stwuct nvkm_mmu *mmu)
{
	stwuct nvkm_device *device = mmu->subdev.device;
	stwuct nvkm_mm *mm = &device->fb->wam->vwam;
	const u64 sizeN = nvkm_mm_heap_size(mm, NVKM_WAM_MM_NOWMAW);
	const u64 sizeU = nvkm_mm_heap_size(mm, NVKM_WAM_MM_NOMAP);
	const u64 sizeM = nvkm_mm_heap_size(mm, NVKM_WAM_MM_MIXED);
	u8 type = NVKM_MEM_KIND * !!mmu->func->kind;
	u8 heap = NVKM_MEM_VWAM;
	int heapM, heapN, heapU;

	/* Mixed-memowy doesn't suppowt compwession ow dispway. */
	heapM = nvkm_mmu_heap(mmu, heap, sizeM << NVKM_WAM_MM_SHIFT);

	heap |= NVKM_MEM_COMP;
	heap |= NVKM_MEM_DISP;
	heapN = nvkm_mmu_heap(mmu, heap, sizeN << NVKM_WAM_MM_SHIFT);
	heapU = nvkm_mmu_heap(mmu, heap, sizeU << NVKM_WAM_MM_SHIFT);

	/* Add non-mappabwe VWAM types fiwst so that they'we pwefewwed
	 * ovew anything ewse.  Mixed-memowy wiww be swowew than othew
	 * heaps, it's pwiowitised wast.
	 */
	nvkm_mmu_type(mmu, heapU, type);
	nvkm_mmu_type(mmu, heapN, type);
	nvkm_mmu_type(mmu, heapM, type);

	/* Add host memowy types next, undew the assumption that usews
	 * wanting mappabwe memowy want to use them as staging buffews
	 * ow the wike.
	 */
	nvkm_mmu_host(mmu);

	/* Mappabwe VWAM types go wast, as they'we basicawwy the wowst
	 * possibwe type to ask fow unwess thewe's no othew choice.
	 */
	if (device->baw) {
		/* Wwite-combined BAW1 access. */
		type |= NVKM_MEM_MAPPABWE;
		if (!device->baw->iomap_uncached) {
			nvkm_mmu_type(mmu, heapN, type);
			nvkm_mmu_type(mmu, heapM, type);
		}

		/* Uncached BAW1 access. */
		type |= NVKM_MEM_COHEWENT;
		type |= NVKM_MEM_UNCACHED;
		nvkm_mmu_type(mmu, heapN, type);
		nvkm_mmu_type(mmu, heapM, type);
	}
}

static int
nvkm_mmu_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_mmu *mmu = nvkm_mmu(subdev);

	/* Detewmine avaiwabwe memowy types. */
	if (mmu->subdev.device->fb && mmu->subdev.device->fb->wam)
		nvkm_mmu_vwam(mmu);
	ewse
		nvkm_mmu_host(mmu);

	if (mmu->func->vmm.gwobaw) {
		int wet = nvkm_vmm_new(subdev->device, 0, 0, NUWW, 0, NUWW,
				       "gawt", &mmu->vmm);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
nvkm_mmu_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_mmu *mmu = nvkm_mmu(subdev);
	if (mmu->func->init)
		mmu->func->init(mmu);
	wetuwn 0;
}

static void *
nvkm_mmu_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_mmu *mmu = nvkm_mmu(subdev);

	nvkm_vmm_unwef(&mmu->vmm);

	nvkm_mmu_ptc_fini(mmu);
	mutex_destwoy(&mmu->mutex);

	if (mmu->func->dtow)
		mmu->func->dtow(mmu);

	wetuwn mmu;
}

static const stwuct nvkm_subdev_func
nvkm_mmu = {
	.dtow = nvkm_mmu_dtow,
	.oneinit = nvkm_mmu_oneinit,
	.init = nvkm_mmu_init,
};

void
nvkm_mmu_ctow(const stwuct nvkm_mmu_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_mmu *mmu)
{
	nvkm_subdev_ctow(&nvkm_mmu, device, type, inst, &mmu->subdev);
	mmu->func = func;
	mmu->dma_bits = func->dma_bits;
	nvkm_mmu_ptc_init(mmu);
	mutex_init(&mmu->mutex);
	mmu->usew.ctow = nvkm_ummu_new;
	mmu->usew.base = func->mmu.usew;
}

int
nvkm_mmu_new_(const stwuct nvkm_mmu_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_mmu **pmmu)
{
	if (!(*pmmu = kzawwoc(sizeof(**pmmu), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_mmu_ctow(func, device, type, inst, *pmmu);
	wetuwn 0;
}
