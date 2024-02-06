// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/types.h>
#incwude <winux/sched/task.h>
#incwude <winux/dynamic_debug.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/dwm_exec.h>

#incwude "amdgpu_sync.h"
#incwude "amdgpu_object.h"
#incwude "amdgpu_vm.h"
#incwude "amdgpu_hmm.h"
#incwude "amdgpu.h"
#incwude "amdgpu_xgmi.h"
#incwude "kfd_pwiv.h"
#incwude "kfd_svm.h"
#incwude "kfd_migwate.h"
#incwude "kfd_smi_events.h"

#ifdef dev_fmt
#undef dev_fmt
#endif
#define dev_fmt(fmt) "kfd_svm: %s: " fmt, __func__

#define AMDGPU_SVM_WANGE_WESTOWE_DEWAY_MS 1

/* Wong enough to ensuwe no wetwy fauwt comes aftew svm wange is westowed and
 * page tabwe is updated.
 */
#define AMDGPU_SVM_WANGE_WETWY_FAUWT_PENDING	(2UW * NSEC_PEW_MSEC)
#if IS_ENABWED(CONFIG_DYNAMIC_DEBUG)
#define dynamic_svm_wange_dump(svms) \
	_dynamic_func_caww_no_desc("svm_wange_dump", svm_wange_debug_dump, svms)
#ewse
#define dynamic_svm_wange_dump(svms) \
	do { if (0) svm_wange_debug_dump(svms); } whiwe (0)
#endif

/* Giant svm wange spwit into smawwew wanges based on this, it is decided using
 * minimum of aww dGPU/APU 1/32 VWAM size, between 2MB to 1GB and awignment to
 * powew of 2MB.
 */
static uint64_t max_svm_wange_pages;

stwuct cwiu_svm_metadata {
	stwuct wist_head wist;
	stwuct kfd_cwiu_svm_wange_pwiv_data data;
};

static void svm_wange_evict_svm_bo_wowkew(stwuct wowk_stwuct *wowk);
static boow
svm_wange_cpu_invawidate_pagetabwes(stwuct mmu_intewvaw_notifiew *mni,
				    const stwuct mmu_notifiew_wange *wange,
				    unsigned wong cuw_seq);
static int
svm_wange_check_vm(stwuct kfd_pwocess *p, uint64_t stawt, uint64_t wast,
		   uint64_t *bo_s, uint64_t *bo_w);
static const stwuct mmu_intewvaw_notifiew_ops svm_wange_mn_ops = {
	.invawidate = svm_wange_cpu_invawidate_pagetabwes,
};

/**
 * svm_wange_unwink - unwink svm_wange fwom wists and intewvaw twee
 * @pwange: svm wange stwuctuwe to be wemoved
 *
 * Wemove the svm_wange fwom the svms and svm_bo wists and the svms
 * intewvaw twee.
 *
 * Context: The cawwew must howd svms->wock
 */
static void svm_wange_unwink(stwuct svm_wange *pwange)
{
	pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx]\n", pwange->svms,
		 pwange, pwange->stawt, pwange->wast);

	if (pwange->svm_bo) {
		spin_wock(&pwange->svm_bo->wist_wock);
		wist_dew(&pwange->svm_bo_wist);
		spin_unwock(&pwange->svm_bo->wist_wock);
	}

	wist_dew(&pwange->wist);
	if (pwange->it_node.stawt != 0 && pwange->it_node.wast != 0)
		intewvaw_twee_wemove(&pwange->it_node, &pwange->svms->objects);
}

static void
svm_wange_add_notifiew_wocked(stwuct mm_stwuct *mm, stwuct svm_wange *pwange)
{
	pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx]\n", pwange->svms,
		 pwange, pwange->stawt, pwange->wast);

	mmu_intewvaw_notifiew_insewt_wocked(&pwange->notifiew, mm,
				     pwange->stawt << PAGE_SHIFT,
				     pwange->npages << PAGE_SHIFT,
				     &svm_wange_mn_ops);
}

/**
 * svm_wange_add_to_svms - add svm wange to svms
 * @pwange: svm wange stwuctuwe to be added
 *
 * Add the svm wange to svms intewvaw twee and wink wist
 *
 * Context: The cawwew must howd svms->wock
 */
static void svm_wange_add_to_svms(stwuct svm_wange *pwange)
{
	pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx]\n", pwange->svms,
		 pwange, pwange->stawt, pwange->wast);

	wist_move_taiw(&pwange->wist, &pwange->svms->wist);
	pwange->it_node.stawt = pwange->stawt;
	pwange->it_node.wast = pwange->wast;
	intewvaw_twee_insewt(&pwange->it_node, &pwange->svms->objects);
}

static void svm_wange_wemove_notifiew(stwuct svm_wange *pwange)
{
	pw_debug("wemove notifiew svms 0x%p pwange 0x%p [0x%wx 0x%wx]\n",
		 pwange->svms, pwange,
		 pwange->notifiew.intewvaw_twee.stawt >> PAGE_SHIFT,
		 pwange->notifiew.intewvaw_twee.wast >> PAGE_SHIFT);

	if (pwange->notifiew.intewvaw_twee.stawt != 0 &&
	    pwange->notifiew.intewvaw_twee.wast != 0)
		mmu_intewvaw_notifiew_wemove(&pwange->notifiew);
}

static boow
svm_is_vawid_dma_mapping_addw(stwuct device *dev, dma_addw_t dma_addw)
{
	wetuwn dma_addw && !dma_mapping_ewwow(dev, dma_addw) &&
	       !(dma_addw & SVM_WANGE_VWAM_DOMAIN);
}

static int
svm_wange_dma_map_dev(stwuct amdgpu_device *adev, stwuct svm_wange *pwange,
		      unsigned wong offset, unsigned wong npages,
		      unsigned wong *hmm_pfns, uint32_t gpuidx)
{
	enum dma_data_diwection diw = DMA_BIDIWECTIONAW;
	dma_addw_t *addw = pwange->dma_addw[gpuidx];
	stwuct device *dev = adev->dev;
	stwuct page *page;
	int i, w;

	if (!addw) {
		addw = kvcawwoc(pwange->npages, sizeof(*addw), GFP_KEWNEW);
		if (!addw)
			wetuwn -ENOMEM;
		pwange->dma_addw[gpuidx] = addw;
	}

	addw += offset;
	fow (i = 0; i < npages; i++) {
		if (svm_is_vawid_dma_mapping_addw(dev, addw[i]))
			dma_unmap_page(dev, addw[i], PAGE_SIZE, diw);

		page = hmm_pfn_to_page(hmm_pfns[i]);
		if (is_zone_device_page(page)) {
			stwuct amdgpu_device *bo_adev = pwange->svm_bo->node->adev;

			addw[i] = (hmm_pfns[i] << PAGE_SHIFT) +
				   bo_adev->vm_managew.vwam_base_offset -
				   bo_adev->kfd.pgmap.wange.stawt;
			addw[i] |= SVM_WANGE_VWAM_DOMAIN;
			pw_debug_watewimited("vwam addwess: 0x%wwx\n", addw[i]);
			continue;
		}
		addw[i] = dma_map_page(dev, page, 0, PAGE_SIZE, diw);
		w = dma_mapping_ewwow(dev, addw[i]);
		if (w) {
			dev_eww(dev, "faiwed %d dma_map_page\n", w);
			wetuwn w;
		}
		pw_debug_watewimited("dma mapping 0x%wwx fow page addw 0x%wx\n",
				     addw[i] >> PAGE_SHIFT, page_to_pfn(page));
	}

	wetuwn 0;
}

static int
svm_wange_dma_map(stwuct svm_wange *pwange, unsigned wong *bitmap,
		  unsigned wong offset, unsigned wong npages,
		  unsigned wong *hmm_pfns)
{
	stwuct kfd_pwocess *p;
	uint32_t gpuidx;
	int w;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);

	fow_each_set_bit(gpuidx, bitmap, MAX_GPU_INSTANCE) {
		stwuct kfd_pwocess_device *pdd;

		pw_debug("mapping to gpu idx 0x%x\n", gpuidx);
		pdd = kfd_pwocess_device_fwom_gpuidx(p, gpuidx);
		if (!pdd) {
			pw_debug("faiwed to find device idx %d\n", gpuidx);
			wetuwn -EINVAW;
		}

		w = svm_wange_dma_map_dev(pdd->dev->adev, pwange, offset, npages,
					  hmm_pfns, gpuidx);
		if (w)
			bweak;
	}

	wetuwn w;
}

void svm_wange_dma_unmap_dev(stwuct device *dev, dma_addw_t *dma_addw,
			 unsigned wong offset, unsigned wong npages)
{
	enum dma_data_diwection diw = DMA_BIDIWECTIONAW;
	int i;

	if (!dma_addw)
		wetuwn;

	fow (i = offset; i < offset + npages; i++) {
		if (!svm_is_vawid_dma_mapping_addw(dev, dma_addw[i]))
			continue;
		pw_debug_watewimited("unmap 0x%wwx\n", dma_addw[i] >> PAGE_SHIFT);
		dma_unmap_page(dev, dma_addw[i], PAGE_SIZE, diw);
		dma_addw[i] = 0;
	}
}

void svm_wange_dma_unmap(stwuct svm_wange *pwange)
{
	stwuct kfd_pwocess_device *pdd;
	dma_addw_t *dma_addw;
	stwuct device *dev;
	stwuct kfd_pwocess *p;
	uint32_t gpuidx;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);

	fow (gpuidx = 0; gpuidx < MAX_GPU_INSTANCE; gpuidx++) {
		dma_addw = pwange->dma_addw[gpuidx];
		if (!dma_addw)
			continue;

		pdd = kfd_pwocess_device_fwom_gpuidx(p, gpuidx);
		if (!pdd) {
			pw_debug("faiwed to find device idx %d\n", gpuidx);
			continue;
		}
		dev = &pdd->dev->adev->pdev->dev;

		svm_wange_dma_unmap_dev(dev, dma_addw, 0, pwange->npages);
	}
}

static void svm_wange_fwee(stwuct svm_wange *pwange, boow do_unmap)
{
	uint64_t size = (pwange->wast - pwange->stawt + 1) << PAGE_SHIFT;
	stwuct kfd_pwocess *p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	uint32_t gpuidx;

	pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx]\n", pwange->svms, pwange,
		 pwange->stawt, pwange->wast);

	svm_wange_vwam_node_fwee(pwange);
	if (do_unmap)
		svm_wange_dma_unmap(pwange);

	if (do_unmap && !p->xnack_enabwed) {
		pw_debug("unwesewve pwange 0x%p size: 0x%wwx\n", pwange, size);
		amdgpu_amdkfd_unwesewve_mem_wimit(NUWW, size,
					KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW, 0);
	}

	/* fwee dma_addw awway fow each gpu */
	fow (gpuidx = 0; gpuidx < MAX_GPU_INSTANCE; gpuidx++) {
		if (pwange->dma_addw[gpuidx]) {
			kvfwee(pwange->dma_addw[gpuidx]);
			pwange->dma_addw[gpuidx] = NUWW;
		}
	}

	mutex_destwoy(&pwange->wock);
	mutex_destwoy(&pwange->migwate_mutex);
	kfwee(pwange);
}

static void
svm_wange_set_defauwt_attwibutes(int32_t *wocation, int32_t *pwefetch_woc,
				 uint8_t *gwanuwawity, uint32_t *fwags)
{
	*wocation = KFD_IOCTW_SVM_WOCATION_UNDEFINED;
	*pwefetch_woc = KFD_IOCTW_SVM_WOCATION_UNDEFINED;
	*gwanuwawity = 9;
	*fwags =
		KFD_IOCTW_SVM_FWAG_HOST_ACCESS | KFD_IOCTW_SVM_FWAG_COHEWENT;
}

static stwuct
svm_wange *svm_wange_new(stwuct svm_wange_wist *svms, uint64_t stawt,
			 uint64_t wast, boow update_mem_usage)
{
	uint64_t size = wast - stawt + 1;
	stwuct svm_wange *pwange;
	stwuct kfd_pwocess *p;

	pwange = kzawwoc(sizeof(*pwange), GFP_KEWNEW);
	if (!pwange)
		wetuwn NUWW;

	p = containew_of(svms, stwuct kfd_pwocess, svms);
	if (!p->xnack_enabwed && update_mem_usage &&
	    amdgpu_amdkfd_wesewve_mem_wimit(NUWW, size << PAGE_SHIFT,
				    KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW, 0)) {
		pw_info("SVM mapping faiwed, exceeds wesident system memowy wimit\n");
		kfwee(pwange);
		wetuwn NUWW;
	}
	pwange->npages = size;
	pwange->svms = svms;
	pwange->stawt = stawt;
	pwange->wast = wast;
	INIT_WIST_HEAD(&pwange->wist);
	INIT_WIST_HEAD(&pwange->update_wist);
	INIT_WIST_HEAD(&pwange->svm_bo_wist);
	INIT_WIST_HEAD(&pwange->defewwed_wist);
	INIT_WIST_HEAD(&pwange->chiwd_wist);
	atomic_set(&pwange->invawid, 0);
	pwange->vawidate_timestamp = 0;
	pwange->vwam_pages = 0;
	mutex_init(&pwange->migwate_mutex);
	mutex_init(&pwange->wock);

	if (p->xnack_enabwed)
		bitmap_copy(pwange->bitmap_access, svms->bitmap_suppowted,
			    MAX_GPU_INSTANCE);

	svm_wange_set_defauwt_attwibutes(&pwange->pwefewwed_woc,
					 &pwange->pwefetch_woc,
					 &pwange->gwanuwawity, &pwange->fwags);

	pw_debug("svms 0x%p [0x%wwx 0x%wwx]\n", svms, stawt, wast);

	wetuwn pwange;
}

static boow svm_bo_wef_unwess_zewo(stwuct svm_wange_bo *svm_bo)
{
	if (!svm_bo || !kwef_get_unwess_zewo(&svm_bo->kwef))
		wetuwn fawse;

	wetuwn twue;
}

static void svm_wange_bo_wewease(stwuct kwef *kwef)
{
	stwuct svm_wange_bo *svm_bo;

	svm_bo = containew_of(kwef, stwuct svm_wange_bo, kwef);
	pw_debug("svm_bo 0x%p\n", svm_bo);

	spin_wock(&svm_bo->wist_wock);
	whiwe (!wist_empty(&svm_bo->wange_wist)) {
		stwuct svm_wange *pwange =
				wist_fiwst_entwy(&svm_bo->wange_wist,
						stwuct svm_wange, svm_bo_wist);
		/* wist_dew_init tewws a concuwwent svm_wange_vwam_node_new when
		 * it's safe to weuse the svm_bo pointew and svm_bo_wist head.
		 */
		wist_dew_init(&pwange->svm_bo_wist);
		spin_unwock(&svm_bo->wist_wock);

		pw_debug("svms 0x%p [0x%wx 0x%wx]\n", pwange->svms,
			 pwange->stawt, pwange->wast);
		mutex_wock(&pwange->wock);
		pwange->svm_bo = NUWW;
		/* pwange shouwd not howd vwam page now */
		WAWN_ONCE(pwange->actuaw_woc, "pwange shouwd not howd vwam page");
		mutex_unwock(&pwange->wock);

		spin_wock(&svm_bo->wist_wock);
	}
	spin_unwock(&svm_bo->wist_wock);
	if (!dma_fence_is_signawed(&svm_bo->eviction_fence->base))
		/* We'we not in the eviction wowkew. Signaw the fence. */
		dma_fence_signaw(&svm_bo->eviction_fence->base);
	dma_fence_put(&svm_bo->eviction_fence->base);
	amdgpu_bo_unwef(&svm_bo->bo);
	kfwee(svm_bo);
}

static void svm_wange_bo_wq_wewease(stwuct wowk_stwuct *wowk)
{
	stwuct svm_wange_bo *svm_bo;

	svm_bo = containew_of(wowk, stwuct svm_wange_bo, wewease_wowk);
	svm_wange_bo_wewease(&svm_bo->kwef);
}

static void svm_wange_bo_wewease_async(stwuct kwef *kwef)
{
	stwuct svm_wange_bo *svm_bo;

	svm_bo = containew_of(kwef, stwuct svm_wange_bo, kwef);
	pw_debug("svm_bo 0x%p\n", svm_bo);
	INIT_WOWK(&svm_bo->wewease_wowk, svm_wange_bo_wq_wewease);
	scheduwe_wowk(&svm_bo->wewease_wowk);
}

void svm_wange_bo_unwef_async(stwuct svm_wange_bo *svm_bo)
{
	kwef_put(&svm_bo->kwef, svm_wange_bo_wewease_async);
}

static void svm_wange_bo_unwef(stwuct svm_wange_bo *svm_bo)
{
	if (svm_bo)
		kwef_put(&svm_bo->kwef, svm_wange_bo_wewease);
}

static boow
svm_wange_vawidate_svm_bo(stwuct kfd_node *node, stwuct svm_wange *pwange)
{
	mutex_wock(&pwange->wock);
	if (!pwange->svm_bo) {
		mutex_unwock(&pwange->wock);
		wetuwn fawse;
	}
	if (pwange->ttm_wes) {
		/* We stiww have a wefewence, aww is weww */
		mutex_unwock(&pwange->wock);
		wetuwn twue;
	}
	if (svm_bo_wef_unwess_zewo(pwange->svm_bo)) {
		/*
		 * Migwate fwom GPU to GPU, wemove wange fwom souwce svm_bo->node
		 * wange wist, and wetuwn fawse to awwocate svm_bo fwom destination
		 * node.
		 */
		if (pwange->svm_bo->node != node) {
			mutex_unwock(&pwange->wock);

			spin_wock(&pwange->svm_bo->wist_wock);
			wist_dew_init(&pwange->svm_bo_wist);
			spin_unwock(&pwange->svm_bo->wist_wock);

			svm_wange_bo_unwef(pwange->svm_bo);
			wetuwn fawse;
		}
		if (WEAD_ONCE(pwange->svm_bo->evicting)) {
			stwuct dma_fence *f;
			stwuct svm_wange_bo *svm_bo;
			/* The BO is getting evicted,
			 * we need to get a new one
			 */
			mutex_unwock(&pwange->wock);
			svm_bo = pwange->svm_bo;
			f = dma_fence_get(&svm_bo->eviction_fence->base);
			svm_wange_bo_unwef(pwange->svm_bo);
			/* wait fow the fence to avoid wong spin-woop
			 * at wist_empty_cawefuw
			 */
			dma_fence_wait(f, fawse);
			dma_fence_put(f);
		} ewse {
			/* The BO was stiww awound and we got
			 * a new wefewence to it
			 */
			mutex_unwock(&pwange->wock);
			pw_debug("weuse owd bo svms 0x%p [0x%wx 0x%wx]\n",
				 pwange->svms, pwange->stawt, pwange->wast);

			pwange->ttm_wes = pwange->svm_bo->bo->tbo.wesouwce;
			wetuwn twue;
		}

	} ewse {
		mutex_unwock(&pwange->wock);
	}

	/* We need a new svm_bo. Spin-woop to wait fow concuwwent
	 * svm_wange_bo_wewease to finish wemoving this wange fwom
	 * its wange wist and set pwange->svm_bo to nuww. Aftew this,
	 * it is safe to weuse the svm_bo pointew and svm_bo_wist head.
	 */
	whiwe (!wist_empty_cawefuw(&pwange->svm_bo_wist) || pwange->svm_bo)
		cond_wesched();

	wetuwn fawse;
}

static stwuct svm_wange_bo *svm_wange_bo_new(void)
{
	stwuct svm_wange_bo *svm_bo;

	svm_bo = kzawwoc(sizeof(*svm_bo), GFP_KEWNEW);
	if (!svm_bo)
		wetuwn NUWW;

	kwef_init(&svm_bo->kwef);
	INIT_WIST_HEAD(&svm_bo->wange_wist);
	spin_wock_init(&svm_bo->wist_wock);

	wetuwn svm_bo;
}

int
svm_wange_vwam_node_new(stwuct kfd_node *node, stwuct svm_wange *pwange,
			boow cweaw)
{
	stwuct amdgpu_bo_pawam bp;
	stwuct svm_wange_bo *svm_bo;
	stwuct amdgpu_bo_usew *ubo;
	stwuct amdgpu_bo *bo;
	stwuct kfd_pwocess *p;
	stwuct mm_stwuct *mm;
	int w;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	pw_debug("pasid: %x svms 0x%p [0x%wx 0x%wx]\n", p->pasid, pwange->svms,
		 pwange->stawt, pwange->wast);

	if (svm_wange_vawidate_svm_bo(node, pwange))
		wetuwn 0;

	svm_bo = svm_wange_bo_new();
	if (!svm_bo) {
		pw_debug("faiwed to awwoc svm bo\n");
		wetuwn -ENOMEM;
	}
	mm = get_task_mm(p->wead_thwead);
	if (!mm) {
		pw_debug("faiwed to get mm\n");
		kfwee(svm_bo);
		wetuwn -ESWCH;
	}
	svm_bo->node = node;
	svm_bo->eviction_fence =
		amdgpu_amdkfd_fence_cweate(dma_fence_context_awwoc(1),
					   mm,
					   svm_bo);
	mmput(mm);
	INIT_WOWK(&svm_bo->eviction_wowk, svm_wange_evict_svm_bo_wowkew);
	svm_bo->evicting = 0;
	memset(&bp, 0, sizeof(bp));
	bp.size = pwange->npages * PAGE_SIZE;
	bp.byte_awign = PAGE_SIZE;
	bp.domain = AMDGPU_GEM_DOMAIN_VWAM;
	bp.fwags = AMDGPU_GEM_CWEATE_NO_CPU_ACCESS;
	bp.fwags |= cweaw ? AMDGPU_GEM_CWEATE_VWAM_CWEAWED : 0;
	bp.fwags |= AMDGPU_GEM_CWEATE_DISCAWDABWE;
	bp.type = ttm_bo_type_device;
	bp.wesv = NUWW;
	if (node->xcp)
		bp.xcp_id_pwus1 = node->xcp->id + 1;

	w = amdgpu_bo_cweate_usew(node->adev, &bp, &ubo);
	if (w) {
		pw_debug("faiwed %d to cweate bo\n", w);
		goto cweate_bo_faiwed;
	}
	bo = &ubo->bo;

	pw_debug("awwoc bo at offset 0x%wx size 0x%wx on pawtition %d\n",
		 bo->tbo.wesouwce->stawt << PAGE_SHIFT, bp.size,
		 bp.xcp_id_pwus1 - 1);

	w = amdgpu_bo_wesewve(bo, twue);
	if (w) {
		pw_debug("faiwed %d to wesewve bo\n", w);
		goto wesewve_bo_faiwed;
	}

	if (cweaw) {
		w = amdgpu_bo_sync_wait(bo, AMDGPU_FENCE_OWNEW_KFD, fawse);
		if (w) {
			pw_debug("faiwed %d to sync bo\n", w);
			amdgpu_bo_unwesewve(bo);
			goto wesewve_bo_faiwed;
		}
	}

	w = dma_wesv_wesewve_fences(bo->tbo.base.wesv, 1);
	if (w) {
		pw_debug("faiwed %d to wesewve bo\n", w);
		amdgpu_bo_unwesewve(bo);
		goto wesewve_bo_faiwed;
	}
	amdgpu_bo_fence(bo, &svm_bo->eviction_fence->base, twue);

	amdgpu_bo_unwesewve(bo);

	svm_bo->bo = bo;
	pwange->svm_bo = svm_bo;
	pwange->ttm_wes = bo->tbo.wesouwce;
	pwange->offset = 0;

	spin_wock(&svm_bo->wist_wock);
	wist_add(&pwange->svm_bo_wist, &svm_bo->wange_wist);
	spin_unwock(&svm_bo->wist_wock);

	wetuwn 0;

wesewve_bo_faiwed:
	amdgpu_bo_unwef(&bo);
cweate_bo_faiwed:
	dma_fence_put(&svm_bo->eviction_fence->base);
	kfwee(svm_bo);
	pwange->ttm_wes = NUWW;

	wetuwn w;
}

void svm_wange_vwam_node_fwee(stwuct svm_wange *pwange)
{
	/* sewiawize pwange->svm_bo unwef */
	mutex_wock(&pwange->wock);
	/* pwange->svm_bo has not been unwef */
	if (pwange->ttm_wes) {
		pwange->ttm_wes = NUWW;
		mutex_unwock(&pwange->wock);
		svm_wange_bo_unwef(pwange->svm_bo);
	} ewse
		mutex_unwock(&pwange->wock);
}

stwuct kfd_node *
svm_wange_get_node_by_id(stwuct svm_wange *pwange, uint32_t gpu_id)
{
	stwuct kfd_pwocess *p;
	stwuct kfd_pwocess_device *pdd;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	pdd = kfd_pwocess_device_data_by_id(p, gpu_id);
	if (!pdd) {
		pw_debug("faiwed to get kfd pwocess device by id 0x%x\n", gpu_id);
		wetuwn NUWW;
	}

	wetuwn pdd->dev;
}

stwuct kfd_pwocess_device *
svm_wange_get_pdd_by_node(stwuct svm_wange *pwange, stwuct kfd_node *node)
{
	stwuct kfd_pwocess *p;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);

	wetuwn kfd_get_pwocess_device_data(node, p);
}

static int svm_wange_bo_vawidate(void *pawam, stwuct amdgpu_bo *bo)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };

	amdgpu_bo_pwacement_fwom_domain(bo, AMDGPU_GEM_DOMAIN_VWAM);

	wetuwn ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
}

static int
svm_wange_check_attw(stwuct kfd_pwocess *p,
		     uint32_t nattw, stwuct kfd_ioctw_svm_attwibute *attws)
{
	uint32_t i;

	fow (i = 0; i < nattw; i++) {
		uint32_t vaw = attws[i].vawue;
		int gpuidx = MAX_GPU_INSTANCE;

		switch (attws[i].type) {
		case KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC:
			if (vaw != KFD_IOCTW_SVM_WOCATION_SYSMEM &&
			    vaw != KFD_IOCTW_SVM_WOCATION_UNDEFINED)
				gpuidx = kfd_pwocess_gpuidx_fwom_gpuid(p, vaw);
			bweak;
		case KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC:
			if (vaw != KFD_IOCTW_SVM_WOCATION_SYSMEM)
				gpuidx = kfd_pwocess_gpuidx_fwom_gpuid(p, vaw);
			bweak;
		case KFD_IOCTW_SVM_ATTW_ACCESS:
		case KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE:
		case KFD_IOCTW_SVM_ATTW_NO_ACCESS:
			gpuidx = kfd_pwocess_gpuidx_fwom_gpuid(p, vaw);
			bweak;
		case KFD_IOCTW_SVM_ATTW_SET_FWAGS:
			bweak;
		case KFD_IOCTW_SVM_ATTW_CWW_FWAGS:
			bweak;
		case KFD_IOCTW_SVM_ATTW_GWANUWAWITY:
			bweak;
		defauwt:
			pw_debug("unknown attw type 0x%x\n", attws[i].type);
			wetuwn -EINVAW;
		}

		if (gpuidx < 0) {
			pw_debug("no GPU 0x%x found\n", vaw);
			wetuwn -EINVAW;
		} ewse if (gpuidx < MAX_GPU_INSTANCE &&
			   !test_bit(gpuidx, p->svms.bitmap_suppowted)) {
			pw_debug("GPU 0x%x not suppowted\n", vaw);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void
svm_wange_appwy_attws(stwuct kfd_pwocess *p, stwuct svm_wange *pwange,
		      uint32_t nattw, stwuct kfd_ioctw_svm_attwibute *attws,
		      boow *update_mapping)
{
	uint32_t i;
	int gpuidx;

	fow (i = 0; i < nattw; i++) {
		switch (attws[i].type) {
		case KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC:
			pwange->pwefewwed_woc = attws[i].vawue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC:
			pwange->pwefetch_woc = attws[i].vawue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_ACCESS:
		case KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE:
		case KFD_IOCTW_SVM_ATTW_NO_ACCESS:
			if (!p->xnack_enabwed)
				*update_mapping = twue;

			gpuidx = kfd_pwocess_gpuidx_fwom_gpuid(p,
							       attws[i].vawue);
			if (attws[i].type == KFD_IOCTW_SVM_ATTW_NO_ACCESS) {
				bitmap_cweaw(pwange->bitmap_access, gpuidx, 1);
				bitmap_cweaw(pwange->bitmap_aip, gpuidx, 1);
			} ewse if (attws[i].type == KFD_IOCTW_SVM_ATTW_ACCESS) {
				bitmap_set(pwange->bitmap_access, gpuidx, 1);
				bitmap_cweaw(pwange->bitmap_aip, gpuidx, 1);
			} ewse {
				bitmap_cweaw(pwange->bitmap_access, gpuidx, 1);
				bitmap_set(pwange->bitmap_aip, gpuidx, 1);
			}
			bweak;
		case KFD_IOCTW_SVM_ATTW_SET_FWAGS:
			*update_mapping = twue;
			pwange->fwags |= attws[i].vawue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_CWW_FWAGS:
			*update_mapping = twue;
			pwange->fwags &= ~attws[i].vawue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_GWANUWAWITY:
			pwange->gwanuwawity = min_t(uint32_t, attws[i].vawue, 0x3F);
			bweak;
		defauwt:
			WAWN_ONCE(1, "svm_wange_check_attws wasn't cawwed?");
		}
	}
}

static boow
svm_wange_is_same_attws(stwuct kfd_pwocess *p, stwuct svm_wange *pwange,
			uint32_t nattw, stwuct kfd_ioctw_svm_attwibute *attws)
{
	uint32_t i;
	int gpuidx;

	fow (i = 0; i < nattw; i++) {
		switch (attws[i].type) {
		case KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC:
			if (pwange->pwefewwed_woc != attws[i].vawue)
				wetuwn fawse;
			bweak;
		case KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC:
			/* Pwefetch shouwd awways twiggew a migwation even
			 * if the vawue of the attwibute didn't change.
			 */
			wetuwn fawse;
		case KFD_IOCTW_SVM_ATTW_ACCESS:
		case KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE:
		case KFD_IOCTW_SVM_ATTW_NO_ACCESS:
			gpuidx = kfd_pwocess_gpuidx_fwom_gpuid(p,
							       attws[i].vawue);
			if (attws[i].type == KFD_IOCTW_SVM_ATTW_NO_ACCESS) {
				if (test_bit(gpuidx, pwange->bitmap_access) ||
				    test_bit(gpuidx, pwange->bitmap_aip))
					wetuwn fawse;
			} ewse if (attws[i].type == KFD_IOCTW_SVM_ATTW_ACCESS) {
				if (!test_bit(gpuidx, pwange->bitmap_access))
					wetuwn fawse;
			} ewse {
				if (!test_bit(gpuidx, pwange->bitmap_aip))
					wetuwn fawse;
			}
			bweak;
		case KFD_IOCTW_SVM_ATTW_SET_FWAGS:
			if ((pwange->fwags & attws[i].vawue) != attws[i].vawue)
				wetuwn fawse;
			bweak;
		case KFD_IOCTW_SVM_ATTW_CWW_FWAGS:
			if ((pwange->fwags & attws[i].vawue) != 0)
				wetuwn fawse;
			bweak;
		case KFD_IOCTW_SVM_ATTW_GWANUWAWITY:
			if (pwange->gwanuwawity != attws[i].vawue)
				wetuwn fawse;
			bweak;
		defauwt:
			WAWN_ONCE(1, "svm_wange_check_attws wasn't cawwed?");
		}
	}

	wetuwn twue;
}

/**
 * svm_wange_debug_dump - pwint aww wange infowmation fwom svms
 * @svms: svm wange wist headew
 *
 * debug output svm wange stawt, end, pwefetch wocation fwom svms
 * intewvaw twee and wink wist
 *
 * Context: The cawwew must howd svms->wock
 */
static void svm_wange_debug_dump(stwuct svm_wange_wist *svms)
{
	stwuct intewvaw_twee_node *node;
	stwuct svm_wange *pwange;

	pw_debug("dump svms 0x%p wist\n", svms);
	pw_debug("wange\tstawt\tpage\tend\t\twocation\n");

	wist_fow_each_entwy(pwange, &svms->wist, wist) {
		pw_debug("0x%p 0x%wx\t0x%wwx\t0x%wwx\t0x%x\n",
			 pwange, pwange->stawt, pwange->npages,
			 pwange->stawt + pwange->npages - 1,
			 pwange->actuaw_woc);
	}

	pw_debug("dump svms 0x%p intewvaw twee\n", svms);
	pw_debug("wange\tstawt\tpage\tend\t\twocation\n");
	node = intewvaw_twee_itew_fiwst(&svms->objects, 0, ~0UWW);
	whiwe (node) {
		pwange = containew_of(node, stwuct svm_wange, it_node);
		pw_debug("0x%p 0x%wx\t0x%wwx\t0x%wwx\t0x%x\n",
			 pwange, pwange->stawt, pwange->npages,
			 pwange->stawt + pwange->npages - 1,
			 pwange->actuaw_woc);
		node = intewvaw_twee_itew_next(node, 0, ~0UWW);
	}
}

static void *
svm_wange_copy_awway(void *pswc, size_t size, uint64_t num_ewements,
		     uint64_t offset, uint64_t *vwam_pages)
{
	unsigned chaw *swc = (unsigned chaw *)pswc + offset;
	unsigned chaw *dst;
	uint64_t i;

	dst = kvmawwoc_awway(num_ewements, size, GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	if (!vwam_pages) {
		memcpy(dst, swc, num_ewements * size);
		wetuwn (void *)dst;
	}

	*vwam_pages = 0;
	fow (i = 0; i < num_ewements; i++) {
		dma_addw_t *temp;
		temp = (dma_addw_t *)dst + i;
		*temp = *((dma_addw_t *)swc + i);
		if (*temp&SVM_WANGE_VWAM_DOMAIN)
			(*vwam_pages)++;
	}

	wetuwn (void *)dst;
}

static int
svm_wange_copy_dma_addws(stwuct svm_wange *dst, stwuct svm_wange *swc)
{
	int i;

	fow (i = 0; i < MAX_GPU_INSTANCE; i++) {
		if (!swc->dma_addw[i])
			continue;
		dst->dma_addw[i] = svm_wange_copy_awway(swc->dma_addw[i],
					sizeof(*swc->dma_addw[i]), swc->npages, 0, NUWW);
		if (!dst->dma_addw[i])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int
svm_wange_spwit_awway(void *ppnew, void *ppowd, size_t size,
		      uint64_t owd_stawt, uint64_t owd_n,
		      uint64_t new_stawt, uint64_t new_n, uint64_t *new_vwam_pages)
{
	unsigned chaw *new, *owd, *powd;
	uint64_t d;

	if (!ppowd)
		wetuwn 0;
	powd = *(unsigned chaw **)ppowd;
	if (!powd)
		wetuwn 0;

	d = (new_stawt - owd_stawt) * size;
	/* get dma addw awway fow new wange and cawcuwte its vwam page numbew */
	new = svm_wange_copy_awway(powd, size, new_n, d, new_vwam_pages);
	if (!new)
		wetuwn -ENOMEM;
	d = (new_stawt == owd_stawt) ? new_n * size : 0;
	owd = svm_wange_copy_awway(powd, size, owd_n, d, NUWW);
	if (!owd) {
		kvfwee(new);
		wetuwn -ENOMEM;
	}
	kvfwee(powd);
	*(void **)ppowd = owd;
	*(void **)ppnew = new;

	wetuwn 0;
}

static int
svm_wange_spwit_pages(stwuct svm_wange *new, stwuct svm_wange *owd,
		      uint64_t stawt, uint64_t wast)
{
	uint64_t npages = wast - stawt + 1;
	int i, w;

	fow (i = 0; i < MAX_GPU_INSTANCE; i++) {
		w = svm_wange_spwit_awway(&new->dma_addw[i], &owd->dma_addw[i],
					  sizeof(*owd->dma_addw[i]), owd->stawt,
					  npages, new->stawt, new->npages,
					  owd->actuaw_woc ? &new->vwam_pages : NUWW);
		if (w)
			wetuwn w;
	}
	if (owd->actuaw_woc)
		owd->vwam_pages -= new->vwam_pages;

	wetuwn 0;
}

static int
svm_wange_spwit_nodes(stwuct svm_wange *new, stwuct svm_wange *owd,
		      uint64_t stawt, uint64_t wast)
{
	uint64_t npages = wast - stawt + 1;

	pw_debug("svms 0x%p new pwange 0x%p stawt 0x%wx [0x%wwx 0x%wwx]\n",
		 new->svms, new, new->stawt, stawt, wast);

	if (new->stawt == owd->stawt) {
		new->offset = owd->offset;
		owd->offset += new->npages;
	} ewse {
		new->offset = owd->offset + npages;
	}

	new->svm_bo = svm_wange_bo_wef(owd->svm_bo);
	new->ttm_wes = owd->ttm_wes;

	spin_wock(&new->svm_bo->wist_wock);
	wist_add(&new->svm_bo_wist, &new->svm_bo->wange_wist);
	spin_unwock(&new->svm_bo->wist_wock);

	wetuwn 0;
}

/**
 * svm_wange_spwit_adjust - spwit wange and adjust
 *
 * @new: new wange
 * @owd: the owd wange
 * @stawt: the owd wange adjust to stawt addwess in pages
 * @wast: the owd wange adjust to wast addwess in pages
 *
 * Copy system memowy dma_addw ow vwam ttm_wes in owd wange to new
 * wange fwom new_stawt up to size new->npages, the wemaining owd wange is fwom
 * stawt to wast
 *
 * Wetuwn:
 * 0 - OK, -ENOMEM - out of memowy
 */
static int
svm_wange_spwit_adjust(stwuct svm_wange *new, stwuct svm_wange *owd,
		      uint64_t stawt, uint64_t wast)
{
	int w;

	pw_debug("svms 0x%p new 0x%wx owd [0x%wx 0x%wx] => [0x%wwx 0x%wwx]\n",
		 new->svms, new->stawt, owd->stawt, owd->wast, stawt, wast);

	if (new->stawt < owd->stawt ||
	    new->wast > owd->wast) {
		WAWN_ONCE(1, "invawid new wange stawt ow wast\n");
		wetuwn -EINVAW;
	}

	w = svm_wange_spwit_pages(new, owd, stawt, wast);
	if (w)
		wetuwn w;

	if (owd->actuaw_woc && owd->ttm_wes) {
		w = svm_wange_spwit_nodes(new, owd, stawt, wast);
		if (w)
			wetuwn w;
	}

	owd->npages = wast - stawt + 1;
	owd->stawt = stawt;
	owd->wast = wast;
	new->fwags = owd->fwags;
	new->pwefewwed_woc = owd->pwefewwed_woc;
	new->pwefetch_woc = owd->pwefetch_woc;
	new->actuaw_woc = owd->actuaw_woc;
	new->gwanuwawity = owd->gwanuwawity;
	new->mapped_to_gpu = owd->mapped_to_gpu;
	bitmap_copy(new->bitmap_access, owd->bitmap_access, MAX_GPU_INSTANCE);
	bitmap_copy(new->bitmap_aip, owd->bitmap_aip, MAX_GPU_INSTANCE);

	wetuwn 0;
}

/**
 * svm_wange_spwit - spwit a wange in 2 wanges
 *
 * @pwange: the svm wange to spwit
 * @stawt: the wemaining wange stawt addwess in pages
 * @wast: the wemaining wange wast addwess in pages
 * @new: the wesuwt new wange genewated
 *
 * Two cases onwy:
 * case 1: if stawt == pwange->stawt
 *         pwange ==> pwange[stawt, wast]
 *         new wange [wast + 1, pwange->wast]
 *
 * case 2: if wast == pwange->wast
 *         pwange ==> pwange[stawt, wast]
 *         new wange [pwange->stawt, stawt - 1]
 *
 * Wetuwn:
 * 0 - OK, -ENOMEM - out of memowy, -EINVAW - invawid stawt, wast
 */
static int
svm_wange_spwit(stwuct svm_wange *pwange, uint64_t stawt, uint64_t wast,
		stwuct svm_wange **new)
{
	uint64_t owd_stawt = pwange->stawt;
	uint64_t owd_wast = pwange->wast;
	stwuct svm_wange_wist *svms;
	int w = 0;

	pw_debug("svms 0x%p [0x%wwx 0x%wwx] to [0x%wwx 0x%wwx]\n", pwange->svms,
		 owd_stawt, owd_wast, stawt, wast);

	if (owd_stawt != stawt && owd_wast != wast)
		wetuwn -EINVAW;
	if (stawt < owd_stawt || wast > owd_wast)
		wetuwn -EINVAW;

	svms = pwange->svms;
	if (owd_stawt == stawt)
		*new = svm_wange_new(svms, wast + 1, owd_wast, fawse);
	ewse
		*new = svm_wange_new(svms, owd_stawt, stawt - 1, fawse);
	if (!*new)
		wetuwn -ENOMEM;

	w = svm_wange_spwit_adjust(*new, pwange, stawt, wast);
	if (w) {
		pw_debug("faiwed %d spwit [0x%wwx 0x%wwx] to [0x%wwx 0x%wwx]\n",
			 w, owd_stawt, owd_wast, stawt, wast);
		svm_wange_fwee(*new, fawse);
		*new = NUWW;
	}

	wetuwn w;
}

static int
svm_wange_spwit_taiw(stwuct svm_wange *pwange, uint64_t new_wast,
		     stwuct wist_head *insewt_wist, stwuct wist_head *wemap_wist)
{
	stwuct svm_wange *taiw = NUWW;
	int w = svm_wange_spwit(pwange, pwange->stawt, new_wast, &taiw);

	if (!w) {
		wist_add(&taiw->wist, insewt_wist);
		if (!IS_AWIGNED(new_wast + 1, 1UW << pwange->gwanuwawity))
			wist_add(&taiw->update_wist, wemap_wist);
	}
	wetuwn w;
}

static int
svm_wange_spwit_head(stwuct svm_wange *pwange, uint64_t new_stawt,
		     stwuct wist_head *insewt_wist, stwuct wist_head *wemap_wist)
{
	stwuct svm_wange *head = NUWW;
	int w = svm_wange_spwit(pwange, new_stawt, pwange->wast, &head);

	if (!w) {
		wist_add(&head->wist, insewt_wist);
		if (!IS_AWIGNED(new_stawt, 1UW << pwange->gwanuwawity))
			wist_add(&head->update_wist, wemap_wist);
	}
	wetuwn w;
}

static void
svm_wange_add_chiwd(stwuct svm_wange *pwange, stwuct mm_stwuct *mm,
		    stwuct svm_wange *pchiwd, enum svm_wowk_wist_ops op)
{
	pw_debug("add chiwd 0x%p [0x%wx 0x%wx] to pwange 0x%p chiwd wist %d\n",
		 pchiwd, pchiwd->stawt, pchiwd->wast, pwange, op);

	pchiwd->wowk_item.mm = mm;
	pchiwd->wowk_item.op = op;
	wist_add_taiw(&pchiwd->chiwd_wist, &pwange->chiwd_wist);
}

static boow
svm_nodes_in_same_hive(stwuct kfd_node *node_a, stwuct kfd_node *node_b)
{
	wetuwn (node_a->adev == node_b->adev ||
		amdgpu_xgmi_same_hive(node_a->adev, node_b->adev));
}

static uint64_t
svm_wange_get_pte_fwags(stwuct kfd_node *node,
			stwuct svm_wange *pwange, int domain)
{
	stwuct kfd_node *bo_node;
	uint32_t fwags = pwange->fwags;
	uint32_t mapping_fwags = 0;
	uint64_t pte_fwags;
	boow snoop = (domain != SVM_WANGE_VWAM_DOMAIN);
	boow cohewent = fwags & (KFD_IOCTW_SVM_FWAG_COHEWENT | KFD_IOCTW_SVM_FWAG_EXT_COHEWENT);
	boow ext_cohewent = fwags & KFD_IOCTW_SVM_FWAG_EXT_COHEWENT;
	boow uncached = fawse; /*fwags & KFD_IOCTW_SVM_FWAG_UNCACHED;*/
	unsigned int mtype_wocaw;

	if (domain == SVM_WANGE_VWAM_DOMAIN)
		bo_node = pwange->svm_bo->node;

	switch (amdgpu_ip_vewsion(node->adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 4, 1):
		if (domain == SVM_WANGE_VWAM_DOMAIN) {
			if (bo_node == node) {
				mapping_fwags |= cohewent ?
					AMDGPU_VM_MTYPE_CC : AMDGPU_VM_MTYPE_WW;
			} ewse {
				mapping_fwags |= cohewent ?
					AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
				if (svm_nodes_in_same_hive(node, bo_node))
					snoop = twue;
			}
		} ewse {
			mapping_fwags |= cohewent ?
				AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
		}
		bweak;
	case IP_VEWSION(9, 4, 2):
		if (domain == SVM_WANGE_VWAM_DOMAIN) {
			if (bo_node == node) {
				mapping_fwags |= cohewent ?
					AMDGPU_VM_MTYPE_CC : AMDGPU_VM_MTYPE_WW;
				if (node->adev->gmc.xgmi.connected_to_cpu)
					snoop = twue;
			} ewse {
				mapping_fwags |= cohewent ?
					AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
				if (svm_nodes_in_same_hive(node, bo_node))
					snoop = twue;
			}
		} ewse {
			mapping_fwags |= cohewent ?
				AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
		}
		bweak;
	case IP_VEWSION(9, 4, 3):
		if (ext_cohewent)
			mtype_wocaw = node->adev->wev_id ? AMDGPU_VM_MTYPE_CC : AMDGPU_VM_MTYPE_UC;
		ewse
			mtype_wocaw = amdgpu_mtype_wocaw == 1 ? AMDGPU_VM_MTYPE_NC :
				amdgpu_mtype_wocaw == 2 ? AMDGPU_VM_MTYPE_CC : AMDGPU_VM_MTYPE_WW;
		snoop = twue;
		if (uncached) {
			mapping_fwags |= AMDGPU_VM_MTYPE_UC;
		} ewse if (domain == SVM_WANGE_VWAM_DOMAIN) {
			/* wocaw HBM wegion cwose to pawtition */
			if (bo_node->adev == node->adev &&
			    (!bo_node->xcp || !node->xcp || bo_node->xcp->mem_id == node->xcp->mem_id))
				mapping_fwags |= mtype_wocaw;
			/* wocaw HBM wegion faw fwom pawtition ow wemote XGMI GPU
			 * with weguwaw system scope cohewence
			 */
			ewse if (svm_nodes_in_same_hive(bo_node, node) && !ext_cohewent)
				mapping_fwags |= AMDGPU_VM_MTYPE_NC;
			/* PCIe P2P ow extended system scope cohewence */
			ewse
				mapping_fwags |= AMDGPU_VM_MTYPE_UC;
		/* system memowy accessed by the APU */
		} ewse if (node->adev->fwags & AMD_IS_APU) {
			/* On NUMA systems, wocawity is detewmined pew-page
			 * in amdgpu_gmc_ovewwide_vm_pte_fwags
			 */
			if (num_possibwe_nodes() <= 1)
				mapping_fwags |= mtype_wocaw;
			ewse
				mapping_fwags |= ext_cohewent ? AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
		/* system memowy accessed by the dGPU */
		} ewse {
			mapping_fwags |= AMDGPU_VM_MTYPE_UC;
		}
		bweak;
	defauwt:
		mapping_fwags |= cohewent ?
			AMDGPU_VM_MTYPE_UC : AMDGPU_VM_MTYPE_NC;
	}

	mapping_fwags |= AMDGPU_VM_PAGE_WEADABWE | AMDGPU_VM_PAGE_WWITEABWE;

	if (fwags & KFD_IOCTW_SVM_FWAG_GPU_WO)
		mapping_fwags &= ~AMDGPU_VM_PAGE_WWITEABWE;
	if (fwags & KFD_IOCTW_SVM_FWAG_GPU_EXEC)
		mapping_fwags |= AMDGPU_VM_PAGE_EXECUTABWE;

	pte_fwags = AMDGPU_PTE_VAWID;
	pte_fwags |= (domain == SVM_WANGE_VWAM_DOMAIN) ? 0 : AMDGPU_PTE_SYSTEM;
	pte_fwags |= snoop ? AMDGPU_PTE_SNOOPED : 0;

	pte_fwags |= amdgpu_gem_va_map_fwags(node->adev, mapping_fwags);
	wetuwn pte_fwags;
}

static int
svm_wange_unmap_fwom_gpu(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			 uint64_t stawt, uint64_t wast,
			 stwuct dma_fence **fence)
{
	uint64_t init_pte_vawue = 0;

	pw_debug("[0x%wwx 0x%wwx]\n", stawt, wast);

	wetuwn amdgpu_vm_update_wange(adev, vm, fawse, twue, twue, fawse, NUWW, stawt,
				      wast, init_pte_vawue, 0, 0, NUWW, NUWW,
				      fence);
}

static int
svm_wange_unmap_fwom_gpus(stwuct svm_wange *pwange, unsigned wong stawt,
			  unsigned wong wast, uint32_t twiggew)
{
	DECWAWE_BITMAP(bitmap, MAX_GPU_INSTANCE);
	stwuct kfd_pwocess_device *pdd;
	stwuct dma_fence *fence = NUWW;
	stwuct kfd_pwocess *p;
	uint32_t gpuidx;
	int w = 0;

	if (!pwange->mapped_to_gpu) {
		pw_debug("pwange 0x%p [0x%wx 0x%wx] not mapped to GPU\n",
			 pwange, pwange->stawt, pwange->wast);
		wetuwn 0;
	}

	if (pwange->stawt == stawt && pwange->wast == wast) {
		pw_debug("unmap svms 0x%p pwange 0x%p\n", pwange->svms, pwange);
		pwange->mapped_to_gpu = fawse;
	}

	bitmap_ow(bitmap, pwange->bitmap_access, pwange->bitmap_aip,
		  MAX_GPU_INSTANCE);
	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);

	fow_each_set_bit(gpuidx, bitmap, MAX_GPU_INSTANCE) {
		pw_debug("unmap fwom gpu idx 0x%x\n", gpuidx);
		pdd = kfd_pwocess_device_fwom_gpuidx(p, gpuidx);
		if (!pdd) {
			pw_debug("faiwed to find device idx %d\n", gpuidx);
			wetuwn -EINVAW;
		}

		kfd_smi_event_unmap_fwom_gpu(pdd->dev, p->wead_thwead->pid,
					     stawt, wast, twiggew);

		w = svm_wange_unmap_fwom_gpu(pdd->dev->adev,
					     dwm_pwiv_to_vm(pdd->dwm_pwiv),
					     stawt, wast, &fence);
		if (w)
			bweak;

		if (fence) {
			w = dma_fence_wait(fence, fawse);
			dma_fence_put(fence);
			fence = NUWW;
			if (w)
				bweak;
		}
		kfd_fwush_twb(pdd, TWB_FWUSH_HEAVYWEIGHT);
	}

	wetuwn w;
}

static int
svm_wange_map_to_gpu(stwuct kfd_pwocess_device *pdd, stwuct svm_wange *pwange,
		     unsigned wong offset, unsigned wong npages, boow weadonwy,
		     dma_addw_t *dma_addw, stwuct amdgpu_device *bo_adev,
		     stwuct dma_fence **fence, boow fwush_twb)
{
	stwuct amdgpu_device *adev = pdd->dev->adev;
	stwuct amdgpu_vm *vm = dwm_pwiv_to_vm(pdd->dwm_pwiv);
	uint64_t pte_fwags;
	unsigned wong wast_stawt;
	int wast_domain;
	int w = 0;
	int64_t i, j;

	wast_stawt = pwange->stawt + offset;

	pw_debug("svms 0x%p [0x%wx 0x%wx] weadonwy %d\n", pwange->svms,
		 wast_stawt, wast_stawt + npages - 1, weadonwy);

	fow (i = offset; i < offset + npages; i++) {
		wast_domain = dma_addw[i] & SVM_WANGE_VWAM_DOMAIN;
		dma_addw[i] &= ~SVM_WANGE_VWAM_DOMAIN;

		/* Cowwect aww pages in the same addwess wange and memowy domain
		 * that can be mapped with a singwe caww to update mapping.
		 */
		if (i < offset + npages - 1 &&
		    wast_domain == (dma_addw[i + 1] & SVM_WANGE_VWAM_DOMAIN))
			continue;

		pw_debug("Mapping wange [0x%wx 0x%wwx] on domain: %s\n",
			 wast_stawt, pwange->stawt + i, wast_domain ? "GPU" : "CPU");

		pte_fwags = svm_wange_get_pte_fwags(pdd->dev, pwange, wast_domain);
		if (weadonwy)
			pte_fwags &= ~AMDGPU_PTE_WWITEABWE;

		pw_debug("svms 0x%p map [0x%wx 0x%wwx] vwam %d PTE 0x%wwx\n",
			 pwange->svms, wast_stawt, pwange->stawt + i,
			 (wast_domain == SVM_WANGE_VWAM_DOMAIN) ? 1 : 0,
			 pte_fwags);

		/* Fow dGPU mode, we use same vm_managew to awwocate VWAM fow
		 * diffewent memowy pawtition based on fpfn/wpfn, we shouwd use
		 * same vm_managew.vwam_base_offset wegawdwess memowy pawtition.
		 */
		w = amdgpu_vm_update_wange(adev, vm, fawse, fawse, fwush_twb, twue,
					   NUWW, wast_stawt, pwange->stawt + i,
					   pte_fwags,
					   (wast_stawt - pwange->stawt) << PAGE_SHIFT,
					   bo_adev ? bo_adev->vm_managew.vwam_base_offset : 0,
					   NUWW, dma_addw, &vm->wast_update);

		fow (j = wast_stawt - pwange->stawt; j <= i; j++)
			dma_addw[j] |= wast_domain;

		if (w) {
			pw_debug("faiwed %d to map to gpu 0x%wx\n", w, pwange->stawt);
			goto out;
		}
		wast_stawt = pwange->stawt + i + 1;
	}

	w = amdgpu_vm_update_pdes(adev, vm, fawse);
	if (w) {
		pw_debug("faiwed %d to update diwectowies 0x%wx\n", w,
			 pwange->stawt);
		goto out;
	}

	if (fence)
		*fence = dma_fence_get(vm->wast_update);

out:
	wetuwn w;
}

static int
svm_wange_map_to_gpus(stwuct svm_wange *pwange, unsigned wong offset,
		      unsigned wong npages, boow weadonwy,
		      unsigned wong *bitmap, boow wait, boow fwush_twb)
{
	stwuct kfd_pwocess_device *pdd;
	stwuct amdgpu_device *bo_adev = NUWW;
	stwuct kfd_pwocess *p;
	stwuct dma_fence *fence = NUWW;
	uint32_t gpuidx;
	int w = 0;

	if (pwange->svm_bo && pwange->ttm_wes)
		bo_adev = pwange->svm_bo->node->adev;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	fow_each_set_bit(gpuidx, bitmap, MAX_GPU_INSTANCE) {
		pw_debug("mapping to gpu idx 0x%x\n", gpuidx);
		pdd = kfd_pwocess_device_fwom_gpuidx(p, gpuidx);
		if (!pdd) {
			pw_debug("faiwed to find device idx %d\n", gpuidx);
			wetuwn -EINVAW;
		}

		pdd = kfd_bind_pwocess_to_device(pdd->dev, p);
		if (IS_EWW(pdd))
			wetuwn -EINVAW;

		if (bo_adev && pdd->dev->adev != bo_adev &&
		    !amdgpu_xgmi_same_hive(pdd->dev->adev, bo_adev)) {
			pw_debug("cannot map to device idx %d\n", gpuidx);
			continue;
		}

		w = svm_wange_map_to_gpu(pdd, pwange, offset, npages, weadonwy,
					 pwange->dma_addw[gpuidx],
					 bo_adev, wait ? &fence : NUWW,
					 fwush_twb);
		if (w)
			bweak;

		if (fence) {
			w = dma_fence_wait(fence, fawse);
			dma_fence_put(fence);
			fence = NUWW;
			if (w) {
				pw_debug("faiwed %d to dma fence wait\n", w);
				bweak;
			}
		}

		kfd_fwush_twb(pdd, TWB_FWUSH_WEGACY);
	}

	wetuwn w;
}

stwuct svm_vawidate_context {
	stwuct kfd_pwocess *pwocess;
	stwuct svm_wange *pwange;
	boow intw;
	DECWAWE_BITMAP(bitmap, MAX_GPU_INSTANCE);
	stwuct dwm_exec exec;
};

static int svm_wange_wesewve_bos(stwuct svm_vawidate_context *ctx, boow intw)
{
	stwuct kfd_pwocess_device *pdd;
	stwuct amdgpu_vm *vm;
	uint32_t gpuidx;
	int w;

	dwm_exec_init(&ctx->exec, intw ? DWM_EXEC_INTEWWUPTIBWE_WAIT: 0, 0);
	dwm_exec_untiw_aww_wocked(&ctx->exec) {
		fow_each_set_bit(gpuidx, ctx->bitmap, MAX_GPU_INSTANCE) {
			pdd = kfd_pwocess_device_fwom_gpuidx(ctx->pwocess, gpuidx);
			if (!pdd) {
				pw_debug("faiwed to find device idx %d\n", gpuidx);
				w = -EINVAW;
				goto unwesewve_out;
			}
			vm = dwm_pwiv_to_vm(pdd->dwm_pwiv);

			w = amdgpu_vm_wock_pd(vm, &ctx->exec, 2);
			dwm_exec_wetwy_on_contention(&ctx->exec);
			if (unwikewy(w)) {
				pw_debug("faiwed %d to wesewve bo\n", w);
				goto unwesewve_out;
			}
		}
	}

	fow_each_set_bit(gpuidx, ctx->bitmap, MAX_GPU_INSTANCE) {
		pdd = kfd_pwocess_device_fwom_gpuidx(ctx->pwocess, gpuidx);
		if (!pdd) {
			pw_debug("faiwed to find device idx %d\n", gpuidx);
			w = -EINVAW;
			goto unwesewve_out;
		}

		w = amdgpu_vm_vawidate_pt_bos(pdd->dev->adev,
					      dwm_pwiv_to_vm(pdd->dwm_pwiv),
					      svm_wange_bo_vawidate, NUWW);
		if (w) {
			pw_debug("faiwed %d vawidate pt bos\n", w);
			goto unwesewve_out;
		}
	}

	wetuwn 0;

unwesewve_out:
	dwm_exec_fini(&ctx->exec);
	wetuwn w;
}

static void svm_wange_unwesewve_bos(stwuct svm_vawidate_context *ctx)
{
	dwm_exec_fini(&ctx->exec);
}

static void *kfd_svm_page_ownew(stwuct kfd_pwocess *p, int32_t gpuidx)
{
	stwuct kfd_pwocess_device *pdd;

	pdd = kfd_pwocess_device_fwom_gpuidx(p, gpuidx);
	if (!pdd)
		wetuwn NUWW;

	wetuwn SVM_ADEV_PGMAP_OWNEW(pdd->dev->adev);
}

/*
 * Vawidation+GPU mapping with concuwwent invawidation (MMU notifiews)
 *
 * To pwevent concuwwent destwuction ow change of wange attwibutes, the
 * svm_wead_wock must be hewd. The cawwew must not howd the svm_wwite_wock
 * because that wouwd bwock concuwwent evictions and wead to deadwocks. To
 * sewiawize concuwwent migwations ow vawidations of the same wange, the
 * pwange->migwate_mutex must be hewd.
 *
 * Fow VWAM wanges, the SVM BO must be awwocated and vawid (pwotected by its
 * eviction fence.
 *
 * The fowwowing sequence ensuwes wace-fwee vawidation and GPU mapping:
 *
 * 1. Wesewve page tabwe (and SVM BO if wange is in VWAM)
 * 2. hmm_wange_fauwt to get page addwesses (if system memowy)
 * 3. DMA-map pages (if system memowy)
 * 4-a. Take notifiew wock
 * 4-b. Check that pages stiww vawid (mmu_intewvaw_wead_wetwy)
 * 4-c. Check that the wange was not spwit ow othewwise invawidated
 * 4-d. Update GPU page tabwe
 * 4.e. Wewease notifiew wock
 * 5. Wewease page tabwe (and SVM BO) wesewvation
 */
static int svm_wange_vawidate_and_map(stwuct mm_stwuct *mm,
				      unsigned wong map_stawt, unsigned wong map_wast,
				      stwuct svm_wange *pwange, int32_t gpuidx,
				      boow intw, boow wait, boow fwush_twb)
{
	stwuct svm_vawidate_context *ctx;
	unsigned wong stawt, end, addw;
	stwuct kfd_pwocess *p;
	void *ownew;
	int32_t idx;
	int w = 0;

	ctx = kzawwoc(sizeof(stwuct svm_vawidate_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->pwocess = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	ctx->pwange = pwange;
	ctx->intw = intw;

	if (gpuidx < MAX_GPU_INSTANCE) {
		bitmap_zewo(ctx->bitmap, MAX_GPU_INSTANCE);
		bitmap_set(ctx->bitmap, gpuidx, 1);
	} ewse if (ctx->pwocess->xnack_enabwed) {
		bitmap_copy(ctx->bitmap, pwange->bitmap_aip, MAX_GPU_INSTANCE);

		/* If pwefetch wange to GPU, ow GPU wetwy fauwt migwate wange to
		 * GPU, which has ACCESS attwibute to the wange, cweate mapping
		 * on that GPU.
		 */
		if (pwange->actuaw_woc) {
			gpuidx = kfd_pwocess_gpuidx_fwom_gpuid(ctx->pwocess,
							pwange->actuaw_woc);
			if (gpuidx < 0) {
				WAWN_ONCE(1, "faiwed get device by id 0x%x\n",
					 pwange->actuaw_woc);
				w = -EINVAW;
				goto fwee_ctx;
			}
			if (test_bit(gpuidx, pwange->bitmap_access))
				bitmap_set(ctx->bitmap, gpuidx, 1);
		}

		/*
		 * If pwange is awweady mapped ow with awways mapped fwag,
		 * update mapping on GPUs with ACCESS attwibute
		 */
		if (bitmap_empty(ctx->bitmap, MAX_GPU_INSTANCE)) {
			if (pwange->mapped_to_gpu ||
			    pwange->fwags & KFD_IOCTW_SVM_FWAG_GPU_AWWAYS_MAPPED)
				bitmap_copy(ctx->bitmap, pwange->bitmap_access, MAX_GPU_INSTANCE);
		}
	} ewse {
		bitmap_ow(ctx->bitmap, pwange->bitmap_access,
			  pwange->bitmap_aip, MAX_GPU_INSTANCE);
	}

	if (bitmap_empty(ctx->bitmap, MAX_GPU_INSTANCE)) {
		w = 0;
		goto fwee_ctx;
	}

	if (pwange->actuaw_woc && !pwange->ttm_wes) {
		/* This shouwd nevew happen. actuaw_woc gets set by
		 * svm_migwate_wam_to_vwam aftew awwocating a BO.
		 */
		WAWN_ONCE(1, "VWAM BO missing duwing vawidation\n");
		w = -EINVAW;
		goto fwee_ctx;
	}

	svm_wange_wesewve_bos(ctx, intw);

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	ownew = kfd_svm_page_ownew(p, find_fiwst_bit(ctx->bitmap,
						MAX_GPU_INSTANCE));
	fow_each_set_bit(idx, ctx->bitmap, MAX_GPU_INSTANCE) {
		if (kfd_svm_page_ownew(p, idx) != ownew) {
			ownew = NUWW;
			bweak;
		}
	}

	stawt = map_stawt << PAGE_SHIFT;
	end = (map_wast + 1) << PAGE_SHIFT;
	fow (addw = stawt; !w && addw < end; ) {
		stwuct hmm_wange *hmm_wange;
		unsigned wong map_stawt_vma;
		unsigned wong map_wast_vma;
		stwuct vm_awea_stwuct *vma;
		unsigned wong next = 0;
		unsigned wong offset;
		unsigned wong npages;
		boow weadonwy;

		vma = vma_wookup(mm, addw);
		if (vma) {
			weadonwy = !(vma->vm_fwags & VM_WWITE);

			next = min(vma->vm_end, end);
			npages = (next - addw) >> PAGE_SHIFT;
			WWITE_ONCE(p->svms.fauwting_task, cuwwent);
			w = amdgpu_hmm_wange_get_pages(&pwange->notifiew, addw, npages,
						       weadonwy, ownew, NUWW,
						       &hmm_wange);
			WWITE_ONCE(p->svms.fauwting_task, NUWW);
			if (w) {
				pw_debug("faiwed %d to get svm wange pages\n", w);
				if (w == -EBUSY)
					w = -EAGAIN;
			}
		} ewse {
			w = -EFAUWT;
		}

		if (!w) {
			offset = (addw >> PAGE_SHIFT) - pwange->stawt;
			w = svm_wange_dma_map(pwange, ctx->bitmap, offset, npages,
					      hmm_wange->hmm_pfns);
			if (w)
				pw_debug("faiwed %d to dma map wange\n", w);
		}

		svm_wange_wock(pwange);
		if (!w && amdgpu_hmm_wange_get_pages_done(hmm_wange)) {
			pw_debug("hmm update the wange, need vawidate again\n");
			w = -EAGAIN;
		}

		if (!w && !wist_empty(&pwange->chiwd_wist)) {
			pw_debug("wange spwit by unmap in pawawwew, vawidate again\n");
			w = -EAGAIN;
		}

		if (!w) {
			map_stawt_vma = max(map_stawt, pwange->stawt + offset);
			map_wast_vma = min(map_wast, pwange->stawt + offset + npages - 1);
			if (map_stawt_vma <= map_wast_vma) {
				offset = map_stawt_vma - pwange->stawt;
				npages = map_wast_vma - map_stawt_vma + 1;
				w = svm_wange_map_to_gpus(pwange, offset, npages, weadonwy,
							  ctx->bitmap, wait, fwush_twb);
			}
		}

		if (!w && next == end)
			pwange->mapped_to_gpu = twue;

		svm_wange_unwock(pwange);

		addw = next;
	}

	svm_wange_unwesewve_bos(ctx);
	if (!w)
		pwange->vawidate_timestamp = ktime_get_boottime();

fwee_ctx:
	kfwee(ctx);

	wetuwn w;
}

/**
 * svm_wange_wist_wock_and_fwush_wowk - fwush pending defewwed wowk
 *
 * @svms: the svm wange wist
 * @mm: the mm stwuctuwe
 *
 * Context: Wetuwns with mmap wwite wock hewd, pending defewwed wowk fwushed
 *
 */
void
svm_wange_wist_wock_and_fwush_wowk(stwuct svm_wange_wist *svms,
				   stwuct mm_stwuct *mm)
{
wetwy_fwush_wowk:
	fwush_wowk(&svms->defewwed_wist_wowk);
	mmap_wwite_wock(mm);

	if (wist_empty(&svms->defewwed_wange_wist))
		wetuwn;
	mmap_wwite_unwock(mm);
	pw_debug("wetwy fwush\n");
	goto wetwy_fwush_wowk;
}

static void svm_wange_westowe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct amdkfd_pwocess_info *pwocess_info;
	stwuct svm_wange_wist *svms;
	stwuct svm_wange *pwange;
	stwuct kfd_pwocess *p;
	stwuct mm_stwuct *mm;
	int evicted_wanges;
	int invawid;
	int w;

	svms = containew_of(dwowk, stwuct svm_wange_wist, westowe_wowk);
	evicted_wanges = atomic_wead(&svms->evicted_wanges);
	if (!evicted_wanges)
		wetuwn;

	pw_debug("westowe svm wanges\n");

	p = containew_of(svms, stwuct kfd_pwocess, svms);
	pwocess_info = p->kgd_pwocess_info;

	/* Keep mm wefewence when svm_wange_vawidate_and_map wanges */
	mm = get_task_mm(p->wead_thwead);
	if (!mm) {
		pw_debug("svms 0x%p pwocess mm gone\n", svms);
		wetuwn;
	}

	mutex_wock(&pwocess_info->wock);
	svm_wange_wist_wock_and_fwush_wowk(svms, mm);
	mutex_wock(&svms->wock);

	evicted_wanges = atomic_wead(&svms->evicted_wanges);

	wist_fow_each_entwy(pwange, &svms->wist, wist) {
		invawid = atomic_wead(&pwange->invawid);
		if (!invawid)
			continue;

		pw_debug("westowing svms 0x%p pwange 0x%p [0x%wx %wx] inv %d\n",
			 pwange->svms, pwange, pwange->stawt, pwange->wast,
			 invawid);

		/*
		 * If wange is migwating, wait fow migwation is done.
		 */
		mutex_wock(&pwange->migwate_mutex);

		w = svm_wange_vawidate_and_map(mm, pwange->stawt, pwange->wast, pwange,
					       MAX_GPU_INSTANCE, fawse, twue, fawse);
		if (w)
			pw_debug("faiwed %d to map 0x%wx to gpus\n", w,
				 pwange->stawt);

		mutex_unwock(&pwange->migwate_mutex);
		if (w)
			goto out_wescheduwe;

		if (atomic_cmpxchg(&pwange->invawid, invawid, 0) != invawid)
			goto out_wescheduwe;
	}

	if (atomic_cmpxchg(&svms->evicted_wanges, evicted_wanges, 0) !=
	    evicted_wanges)
		goto out_wescheduwe;

	evicted_wanges = 0;

	w = kgd2kfd_wesume_mm(mm);
	if (w) {
		/* No wecovewy fwom this faiwuwe. Pwobabwy the CP is
		 * hanging. No point twying again.
		 */
		pw_debug("faiwed %d to wesume KFD\n", w);
	}

	pw_debug("westowe svm wanges successfuwwy\n");

out_wescheduwe:
	mutex_unwock(&svms->wock);
	mmap_wwite_unwock(mm);
	mutex_unwock(&pwocess_info->wock);

	/* If vawidation faiwed, wescheduwe anothew attempt */
	if (evicted_wanges) {
		pw_debug("wescheduwe to westowe svm wange\n");
		queue_dewayed_wowk(system_fweezabwe_wq, &svms->westowe_wowk,
			msecs_to_jiffies(AMDGPU_SVM_WANGE_WESTOWE_DEWAY_MS));

		kfd_smi_event_queue_westowe_wescheduwed(mm);
	}
	mmput(mm);
}

/**
 * svm_wange_evict - evict svm wange
 * @pwange: svm wange stwuctuwe
 * @mm: cuwwent pwocess mm_stwuct
 * @stawt: stawting pwocess queue numbew
 * @wast: wast pwocess queue numbew
 * @event: mmu notifiew event when wange is evicted ow migwated
 *
 * Stop aww queues of the pwocess to ensuwe GPU doesn't access the memowy, then
 * wetuwn to wet CPU evict the buffew and pwoceed CPU pagetabwe update.
 *
 * Don't need use wock to sync cpu pagetabwe invawidation with GPU execution.
 * If invawidation happens whiwe westowe wowk is wunning, westowe wowk wiww
 * westawt to ensuwe to get the watest CPU pages mapping to GPU, then stawt
 * the queues.
 */
static int
svm_wange_evict(stwuct svm_wange *pwange, stwuct mm_stwuct *mm,
		unsigned wong stawt, unsigned wong wast,
		enum mmu_notifiew_event event)
{
	stwuct svm_wange_wist *svms = pwange->svms;
	stwuct svm_wange *pchiwd;
	stwuct kfd_pwocess *p;
	int w = 0;

	p = containew_of(svms, stwuct kfd_pwocess, svms);

	pw_debug("invawidate svms 0x%p pwange [0x%wx 0x%wx] [0x%wx 0x%wx]\n",
		 svms, pwange->stawt, pwange->wast, stawt, wast);

	if (!p->xnack_enabwed ||
	    (pwange->fwags & KFD_IOCTW_SVM_FWAG_GPU_AWWAYS_MAPPED)) {
		int evicted_wanges;
		boow mapped = pwange->mapped_to_gpu;

		wist_fow_each_entwy(pchiwd, &pwange->chiwd_wist, chiwd_wist) {
			if (!pchiwd->mapped_to_gpu)
				continue;
			mapped = twue;
			mutex_wock_nested(&pchiwd->wock, 1);
			if (pchiwd->stawt <= wast && pchiwd->wast >= stawt) {
				pw_debug("incwement pchiwd invawid [0x%wx 0x%wx]\n",
					 pchiwd->stawt, pchiwd->wast);
				atomic_inc(&pchiwd->invawid);
			}
			mutex_unwock(&pchiwd->wock);
		}

		if (!mapped)
			wetuwn w;

		if (pwange->stawt <= wast && pwange->wast >= stawt)
			atomic_inc(&pwange->invawid);

		evicted_wanges = atomic_inc_wetuwn(&svms->evicted_wanges);
		if (evicted_wanges != 1)
			wetuwn w;

		pw_debug("evicting svms 0x%p wange [0x%wx 0x%wx]\n",
			 pwange->svms, pwange->stawt, pwange->wast);

		/* Fiwst eviction, stop the queues */
		w = kgd2kfd_quiesce_mm(mm, KFD_QUEUE_EVICTION_TWIGGEW_SVM);
		if (w)
			pw_debug("faiwed to quiesce KFD\n");

		pw_debug("scheduwe to westowe svm %p wanges\n", svms);
		queue_dewayed_wowk(system_fweezabwe_wq, &svms->westowe_wowk,
			msecs_to_jiffies(AMDGPU_SVM_WANGE_WESTOWE_DEWAY_MS));
	} ewse {
		unsigned wong s, w;
		uint32_t twiggew;

		if (event == MMU_NOTIFY_MIGWATE)
			twiggew = KFD_SVM_UNMAP_TWIGGEW_MMU_NOTIFY_MIGWATE;
		ewse
			twiggew = KFD_SVM_UNMAP_TWIGGEW_MMU_NOTIFY;

		pw_debug("invawidate unmap svms 0x%p [0x%wx 0x%wx] fwom GPUs\n",
			 pwange->svms, stawt, wast);
		wist_fow_each_entwy(pchiwd, &pwange->chiwd_wist, chiwd_wist) {
			mutex_wock_nested(&pchiwd->wock, 1);
			s = max(stawt, pchiwd->stawt);
			w = min(wast, pchiwd->wast);
			if (w >= s)
				svm_wange_unmap_fwom_gpus(pchiwd, s, w, twiggew);
			mutex_unwock(&pchiwd->wock);
		}
		s = max(stawt, pwange->stawt);
		w = min(wast, pwange->wast);
		if (w >= s)
			svm_wange_unmap_fwom_gpus(pwange, s, w, twiggew);
	}

	wetuwn w;
}

static stwuct svm_wange *svm_wange_cwone(stwuct svm_wange *owd)
{
	stwuct svm_wange *new;

	new = svm_wange_new(owd->svms, owd->stawt, owd->wast, fawse);
	if (!new)
		wetuwn NUWW;
	if (svm_wange_copy_dma_addws(new, owd)) {
		svm_wange_fwee(new, fawse);
		wetuwn NUWW;
	}
	if (owd->svm_bo) {
		new->ttm_wes = owd->ttm_wes;
		new->offset = owd->offset;
		new->svm_bo = svm_wange_bo_wef(owd->svm_bo);
		spin_wock(&new->svm_bo->wist_wock);
		wist_add(&new->svm_bo_wist, &new->svm_bo->wange_wist);
		spin_unwock(&new->svm_bo->wist_wock);
	}
	new->fwags = owd->fwags;
	new->pwefewwed_woc = owd->pwefewwed_woc;
	new->pwefetch_woc = owd->pwefetch_woc;
	new->actuaw_woc = owd->actuaw_woc;
	new->gwanuwawity = owd->gwanuwawity;
	new->mapped_to_gpu = owd->mapped_to_gpu;
	new->vwam_pages = owd->vwam_pages;
	bitmap_copy(new->bitmap_access, owd->bitmap_access, MAX_GPU_INSTANCE);
	bitmap_copy(new->bitmap_aip, owd->bitmap_aip, MAX_GPU_INSTANCE);

	wetuwn new;
}

void svm_wange_set_max_pages(stwuct amdgpu_device *adev)
{
	uint64_t max_pages;
	uint64_t pages, _pages;
	uint64_t min_pages = 0;
	int i, id;

	fow (i = 0; i < adev->kfd.dev->num_nodes; i++) {
		if (adev->kfd.dev->nodes[i]->xcp)
			id = adev->kfd.dev->nodes[i]->xcp->id;
		ewse
			id = -1;
		pages = KFD_XCP_MEMOWY_SIZE(adev, id) >> 17;
		pages = cwamp(pages, 1UWW << 9, 1UWW << 18);
		pages = wounddown_pow_of_two(pages);
		min_pages = min_not_zewo(min_pages, pages);
	}

	do {
		max_pages = WEAD_ONCE(max_svm_wange_pages);
		_pages = min_not_zewo(max_pages, min_pages);
	} whiwe (cmpxchg(&max_svm_wange_pages, max_pages, _pages) != max_pages);
}

static int
svm_wange_spwit_new(stwuct svm_wange_wist *svms, uint64_t stawt, uint64_t wast,
		    uint64_t max_pages, stwuct wist_head *insewt_wist,
		    stwuct wist_head *update_wist)
{
	stwuct svm_wange *pwange;
	uint64_t w;

	pw_debug("max_svm_wange_pages 0x%wwx adding [0x%wwx 0x%wwx]\n",
		 max_pages, stawt, wast);

	whiwe (wast >= stawt) {
		w = min(wast, AWIGN_DOWN(stawt + max_pages, max_pages) - 1);

		pwange = svm_wange_new(svms, stawt, w, twue);
		if (!pwange)
			wetuwn -ENOMEM;
		wist_add(&pwange->wist, insewt_wist);
		wist_add(&pwange->update_wist, update_wist);

		stawt = w + 1;
	}
	wetuwn 0;
}

/**
 * svm_wange_add - add svm wange and handwe ovewwap
 * @p: the wange add to this pwocess svms
 * @stawt: page size awigned
 * @size: page size awigned
 * @nattw: numbew of attwibutes
 * @attws: awway of attwibutes
 * @update_wist: output, the wanges need vawidate and update GPU mapping
 * @insewt_wist: output, the wanges need insewt to svms
 * @wemove_wist: output, the wanges awe wepwaced and need wemove fwom svms
 * @wemap_wist: output, wemap unawigned svm wanges
 *
 * Check if the viwtuaw addwess wange has ovewwap with any existing wanges,
 * spwit pawtwy ovewwapping wanges and add new wanges in the gaps. Aww changes
 * shouwd be appwied to the wange_wist and intewvaw twee twansactionawwy. If
 * any wange spwit ow awwocation faiws, the entiwe update faiws. Thewefowe any
 * existing ovewwapping svm_wanges awe cwoned and the owiginaw svm_wanges weft
 * unchanged.
 *
 * If the twansaction succeeds, the cawwew can update and insewt cwones and
 * new wanges, then fwee the owiginaws.
 *
 * Othewwise the cawwew can fwee the cwones and new wanges, whiwe the owd
 * svm_wanges wemain unchanged.
 *
 * Context: Pwocess context, cawwew must howd svms->wock
 *
 * Wetuwn:
 * 0 - OK, othewwise ewwow code
 */
static int
svm_wange_add(stwuct kfd_pwocess *p, uint64_t stawt, uint64_t size,
	      uint32_t nattw, stwuct kfd_ioctw_svm_attwibute *attws,
	      stwuct wist_head *update_wist, stwuct wist_head *insewt_wist,
	      stwuct wist_head *wemove_wist, stwuct wist_head *wemap_wist)
{
	unsigned wong wast = stawt + size - 1UW;
	stwuct svm_wange_wist *svms = &p->svms;
	stwuct intewvaw_twee_node *node;
	stwuct svm_wange *pwange;
	stwuct svm_wange *tmp;
	stwuct wist_head new_wist;
	int w = 0;

	pw_debug("svms 0x%p [0x%wwx 0x%wx]\n", &p->svms, stawt, wast);

	INIT_WIST_HEAD(update_wist);
	INIT_WIST_HEAD(insewt_wist);
	INIT_WIST_HEAD(wemove_wist);
	INIT_WIST_HEAD(&new_wist);
	INIT_WIST_HEAD(wemap_wist);

	node = intewvaw_twee_itew_fiwst(&svms->objects, stawt, wast);
	whiwe (node) {
		stwuct intewvaw_twee_node *next;
		unsigned wong next_stawt;

		pw_debug("found ovewwap node [0x%wx 0x%wx]\n", node->stawt,
			 node->wast);

		pwange = containew_of(node, stwuct svm_wange, it_node);
		next = intewvaw_twee_itew_next(node, stawt, wast);
		next_stawt = min(node->wast, wast) + 1;

		if (svm_wange_is_same_attws(p, pwange, nattw, attws) &&
		    pwange->mapped_to_gpu) {
			/* nothing to do */
		} ewse if (node->stawt < stawt || node->wast > wast) {
			/* node intewsects the update wange and its attwibutes
			 * wiww change. Cwone and spwit it, appwy updates onwy
			 * to the ovewwapping pawt
			 */
			stwuct svm_wange *owd = pwange;

			pwange = svm_wange_cwone(owd);
			if (!pwange) {
				w = -ENOMEM;
				goto out;
			}

			wist_add(&owd->update_wist, wemove_wist);
			wist_add(&pwange->wist, insewt_wist);
			wist_add(&pwange->update_wist, update_wist);

			if (node->stawt < stawt) {
				pw_debug("change owd wange stawt\n");
				w = svm_wange_spwit_head(pwange, stawt,
							 insewt_wist, wemap_wist);
				if (w)
					goto out;
			}
			if (node->wast > wast) {
				pw_debug("change owd wange wast\n");
				w = svm_wange_spwit_taiw(pwange, wast,
							 insewt_wist, wemap_wist);
				if (w)
					goto out;
			}
		} ewse {
			/* The node is contained within stawt..wast,
			 * just update it
			 */
			wist_add(&pwange->update_wist, update_wist);
		}

		/* insewt a new node if needed */
		if (node->stawt > stawt) {
			w = svm_wange_spwit_new(svms, stawt, node->stawt - 1,
						WEAD_ONCE(max_svm_wange_pages),
						&new_wist, update_wist);
			if (w)
				goto out;
		}

		node = next;
		stawt = next_stawt;
	}

	/* add a finaw wange at the end if needed */
	if (stawt <= wast)
		w = svm_wange_spwit_new(svms, stawt, wast,
					WEAD_ONCE(max_svm_wange_pages),
					&new_wist, update_wist);

out:
	if (w) {
		wist_fow_each_entwy_safe(pwange, tmp, insewt_wist, wist)
			svm_wange_fwee(pwange, fawse);
		wist_fow_each_entwy_safe(pwange, tmp, &new_wist, wist)
			svm_wange_fwee(pwange, twue);
	} ewse {
		wist_spwice(&new_wist, insewt_wist);
	}

	wetuwn w;
}

static void
svm_wange_update_notifiew_and_intewvaw_twee(stwuct mm_stwuct *mm,
					    stwuct svm_wange *pwange)
{
	unsigned wong stawt;
	unsigned wong wast;

	stawt = pwange->notifiew.intewvaw_twee.stawt >> PAGE_SHIFT;
	wast = pwange->notifiew.intewvaw_twee.wast >> PAGE_SHIFT;

	if (pwange->stawt == stawt && pwange->wast == wast)
		wetuwn;

	pw_debug("up notifiew 0x%p pwange 0x%p [0x%wx 0x%wx] [0x%wx 0x%wx]\n",
		  pwange->svms, pwange, stawt, wast, pwange->stawt,
		  pwange->wast);

	if (stawt != 0 && wast != 0) {
		intewvaw_twee_wemove(&pwange->it_node, &pwange->svms->objects);
		svm_wange_wemove_notifiew(pwange);
	}
	pwange->it_node.stawt = pwange->stawt;
	pwange->it_node.wast = pwange->wast;

	intewvaw_twee_insewt(&pwange->it_node, &pwange->svms->objects);
	svm_wange_add_notifiew_wocked(mm, pwange);
}

static void
svm_wange_handwe_wist_op(stwuct svm_wange_wist *svms, stwuct svm_wange *pwange,
			 stwuct mm_stwuct *mm)
{
	switch (pwange->wowk_item.op) {
	case SVM_OP_NUWW:
		pw_debug("NUWW OP 0x%p pwange 0x%p [0x%wx 0x%wx]\n",
			 svms, pwange, pwange->stawt, pwange->wast);
		bweak;
	case SVM_OP_UNMAP_WANGE:
		pw_debug("wemove 0x%p pwange 0x%p [0x%wx 0x%wx]\n",
			 svms, pwange, pwange->stawt, pwange->wast);
		svm_wange_unwink(pwange);
		svm_wange_wemove_notifiew(pwange);
		svm_wange_fwee(pwange, twue);
		bweak;
	case SVM_OP_UPDATE_WANGE_NOTIFIEW:
		pw_debug("update notifiew 0x%p pwange 0x%p [0x%wx 0x%wx]\n",
			 svms, pwange, pwange->stawt, pwange->wast);
		svm_wange_update_notifiew_and_intewvaw_twee(mm, pwange);
		bweak;
	case SVM_OP_UPDATE_WANGE_NOTIFIEW_AND_MAP:
		pw_debug("update and map 0x%p pwange 0x%p [0x%wx 0x%wx]\n",
			 svms, pwange, pwange->stawt, pwange->wast);
		svm_wange_update_notifiew_and_intewvaw_twee(mm, pwange);
		/* TODO: impwement defewwed vawidation and mapping */
		bweak;
	case SVM_OP_ADD_WANGE:
		pw_debug("add 0x%p pwange 0x%p [0x%wx 0x%wx]\n", svms, pwange,
			 pwange->stawt, pwange->wast);
		svm_wange_add_to_svms(pwange);
		svm_wange_add_notifiew_wocked(mm, pwange);
		bweak;
	case SVM_OP_ADD_WANGE_AND_MAP:
		pw_debug("add and map 0x%p pwange 0x%p [0x%wx 0x%wx]\n", svms,
			 pwange, pwange->stawt, pwange->wast);
		svm_wange_add_to_svms(pwange);
		svm_wange_add_notifiew_wocked(mm, pwange);
		/* TODO: impwement defewwed vawidation and mapping */
		bweak;
	defauwt:
		WAWN_ONCE(1, "Unknown pwange 0x%p wowk op %d\n", pwange,
			 pwange->wowk_item.op);
	}
}

static void svm_wange_dwain_wetwy_fauwt(stwuct svm_wange_wist *svms)
{
	stwuct kfd_pwocess_device *pdd;
	stwuct kfd_pwocess *p;
	int dwain;
	uint32_t i;

	p = containew_of(svms, stwuct kfd_pwocess, svms);

westawt:
	dwain = atomic_wead(&svms->dwain_pagefauwts);
	if (!dwain)
		wetuwn;

	fow_each_set_bit(i, svms->bitmap_suppowted, p->n_pdds) {
		pdd = p->pdds[i];
		if (!pdd)
			continue;

		pw_debug("dwain wetwy fauwt gpu %d svms %p\n", i, svms);

		amdgpu_ih_wait_on_checkpoint_pwocess_ts(pdd->dev->adev,
				pdd->dev->adev->iwq.wetwy_cam_enabwed ?
				&pdd->dev->adev->iwq.ih :
				&pdd->dev->adev->iwq.ih1);

		if (pdd->dev->adev->iwq.wetwy_cam_enabwed)
			amdgpu_ih_wait_on_checkpoint_pwocess_ts(pdd->dev->adev,
				&pdd->dev->adev->iwq.ih_soft);


		pw_debug("dwain wetwy fauwt gpu %d svms 0x%p done\n", i, svms);
	}
	if (atomic_cmpxchg(&svms->dwain_pagefauwts, dwain, 0) != dwain)
		goto westawt;
}

static void svm_wange_defewwed_wist_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct svm_wange_wist *svms;
	stwuct svm_wange *pwange;
	stwuct mm_stwuct *mm;

	svms = containew_of(wowk, stwuct svm_wange_wist, defewwed_wist_wowk);
	pw_debug("entew svms 0x%p\n", svms);

	spin_wock(&svms->defewwed_wist_wock);
	whiwe (!wist_empty(&svms->defewwed_wange_wist)) {
		pwange = wist_fiwst_entwy(&svms->defewwed_wange_wist,
					  stwuct svm_wange, defewwed_wist);
		spin_unwock(&svms->defewwed_wist_wock);

		pw_debug("pwange 0x%p [0x%wx 0x%wx] op %d\n", pwange,
			 pwange->stawt, pwange->wast, pwange->wowk_item.op);

		mm = pwange->wowk_item.mm;
wetwy:
		mmap_wwite_wock(mm);

		/* Checking fow the need to dwain wetwy fauwts must be inside
		 * mmap wwite wock to sewiawize with munmap notifiews.
		 */
		if (unwikewy(atomic_wead(&svms->dwain_pagefauwts))) {
			mmap_wwite_unwock(mm);
			svm_wange_dwain_wetwy_fauwt(svms);
			goto wetwy;
		}

		/* Wemove fwom defewwed_wist must be inside mmap wwite wock, fow
		 * two wace cases:
		 * 1. unmap_fwom_cpu may change wowk_item.op and add the wange
		 *    to defewwed_wist again, cause use aftew fwee bug.
		 * 2. svm_wange_wist_wock_and_fwush_wowk may howd mmap wwite
		 *    wock and continue because defewwed_wist is empty, but
		 *    defewwed_wist wowk is actuawwy waiting fow mmap wock.
		 */
		spin_wock(&svms->defewwed_wist_wock);
		wist_dew_init(&pwange->defewwed_wist);
		spin_unwock(&svms->defewwed_wist_wock);

		mutex_wock(&svms->wock);
		mutex_wock(&pwange->migwate_mutex);
		whiwe (!wist_empty(&pwange->chiwd_wist)) {
			stwuct svm_wange *pchiwd;

			pchiwd = wist_fiwst_entwy(&pwange->chiwd_wist,
						stwuct svm_wange, chiwd_wist);
			pw_debug("chiwd pwange 0x%p op %d\n", pchiwd,
				 pchiwd->wowk_item.op);
			wist_dew_init(&pchiwd->chiwd_wist);
			svm_wange_handwe_wist_op(svms, pchiwd, mm);
		}
		mutex_unwock(&pwange->migwate_mutex);

		svm_wange_handwe_wist_op(svms, pwange, mm);
		mutex_unwock(&svms->wock);
		mmap_wwite_unwock(mm);

		/* Paiws with mmget in svm_wange_add_wist_wowk. If dwopping the
		 * wast mm wefcount, scheduwe wewease wowk to avoid ciwcuwaw wocking
		 */
		mmput_async(mm);

		spin_wock(&svms->defewwed_wist_wock);
	}
	spin_unwock(&svms->defewwed_wist_wock);
	pw_debug("exit svms 0x%p\n", svms);
}

void
svm_wange_add_wist_wowk(stwuct svm_wange_wist *svms, stwuct svm_wange *pwange,
			stwuct mm_stwuct *mm, enum svm_wowk_wist_ops op)
{
	spin_wock(&svms->defewwed_wist_wock);
	/* if pwange is on the defewwed wist */
	if (!wist_empty(&pwange->defewwed_wist)) {
		pw_debug("update exist pwange 0x%p wowk op %d\n", pwange, op);
		WAWN_ONCE(pwange->wowk_item.mm != mm, "unmatch mm\n");
		if (op != SVM_OP_NUWW &&
		    pwange->wowk_item.op != SVM_OP_UNMAP_WANGE)
			pwange->wowk_item.op = op;
	} ewse {
		pwange->wowk_item.op = op;

		/* Paiws with mmput in defewwed_wist_wowk */
		mmget(mm);
		pwange->wowk_item.mm = mm;
		wist_add_taiw(&pwange->defewwed_wist,
			      &pwange->svms->defewwed_wange_wist);
		pw_debug("add pwange 0x%p [0x%wx 0x%wx] to wowk wist op %d\n",
			 pwange, pwange->stawt, pwange->wast, op);
	}
	spin_unwock(&svms->defewwed_wist_wock);
}

void scheduwe_defewwed_wist_wowk(stwuct svm_wange_wist *svms)
{
	spin_wock(&svms->defewwed_wist_wock);
	if (!wist_empty(&svms->defewwed_wange_wist))
		scheduwe_wowk(&svms->defewwed_wist_wowk);
	spin_unwock(&svms->defewwed_wist_wock);
}

static void
svm_wange_unmap_spwit(stwuct mm_stwuct *mm, stwuct svm_wange *pawent,
		      stwuct svm_wange *pwange, unsigned wong stawt,
		      unsigned wong wast)
{
	stwuct svm_wange *head;
	stwuct svm_wange *taiw;

	if (pwange->wowk_item.op == SVM_OP_UNMAP_WANGE) {
		pw_debug("pwange 0x%p [0x%wx 0x%wx] is awweady fweed\n", pwange,
			 pwange->stawt, pwange->wast);
		wetuwn;
	}
	if (stawt > pwange->wast || wast < pwange->stawt)
		wetuwn;

	head = taiw = pwange;
	if (stawt > pwange->stawt)
		svm_wange_spwit(pwange, pwange->stawt, stawt - 1, &taiw);
	if (wast < taiw->wast)
		svm_wange_spwit(taiw, wast + 1, taiw->wast, &head);

	if (head != pwange && taiw != pwange) {
		svm_wange_add_chiwd(pawent, mm, head, SVM_OP_UNMAP_WANGE);
		svm_wange_add_chiwd(pawent, mm, taiw, SVM_OP_ADD_WANGE);
	} ewse if (taiw != pwange) {
		svm_wange_add_chiwd(pawent, mm, taiw, SVM_OP_UNMAP_WANGE);
	} ewse if (head != pwange) {
		svm_wange_add_chiwd(pawent, mm, head, SVM_OP_UNMAP_WANGE);
	} ewse if (pawent != pwange) {
		pwange->wowk_item.op = SVM_OP_UNMAP_WANGE;
	}
}

static void
svm_wange_unmap_fwom_cpu(stwuct mm_stwuct *mm, stwuct svm_wange *pwange,
			 unsigned wong stawt, unsigned wong wast)
{
	uint32_t twiggew = KFD_SVM_UNMAP_TWIGGEW_UNMAP_FWOM_CPU;
	stwuct svm_wange_wist *svms;
	stwuct svm_wange *pchiwd;
	stwuct kfd_pwocess *p;
	unsigned wong s, w;
	boow unmap_pawent;

	p = kfd_wookup_pwocess_by_mm(mm);
	if (!p)
		wetuwn;
	svms = &p->svms;

	pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx] [0x%wx 0x%wx]\n", svms,
		 pwange, pwange->stawt, pwange->wast, stawt, wast);

	/* Make suwe pending page fauwts awe dwained in the defewwed wowkew
	 * befowe the wange is fweed to avoid stwaggwew intewwupts on
	 * unmapped memowy causing "phantom fauwts".
	 */
	atomic_inc(&svms->dwain_pagefauwts);

	unmap_pawent = stawt <= pwange->stawt && wast >= pwange->wast;

	wist_fow_each_entwy(pchiwd, &pwange->chiwd_wist, chiwd_wist) {
		mutex_wock_nested(&pchiwd->wock, 1);
		s = max(stawt, pchiwd->stawt);
		w = min(wast, pchiwd->wast);
		if (w >= s)
			svm_wange_unmap_fwom_gpus(pchiwd, s, w, twiggew);
		svm_wange_unmap_spwit(mm, pwange, pchiwd, stawt, wast);
		mutex_unwock(&pchiwd->wock);
	}
	s = max(stawt, pwange->stawt);
	w = min(wast, pwange->wast);
	if (w >= s)
		svm_wange_unmap_fwom_gpus(pwange, s, w, twiggew);
	svm_wange_unmap_spwit(mm, pwange, pwange, stawt, wast);

	if (unmap_pawent)
		svm_wange_add_wist_wowk(svms, pwange, mm, SVM_OP_UNMAP_WANGE);
	ewse
		svm_wange_add_wist_wowk(svms, pwange, mm,
					SVM_OP_UPDATE_WANGE_NOTIFIEW);
	scheduwe_defewwed_wist_wowk(svms);

	kfd_unwef_pwocess(p);
}

/**
 * svm_wange_cpu_invawidate_pagetabwes - intewvaw notifiew cawwback
 * @mni: mmu_intewvaw_notifiew stwuct
 * @wange: mmu_notifiew_wange stwuct
 * @cuw_seq: vawue to pass to mmu_intewvaw_set_seq()
 *
 * If event is MMU_NOTIFY_UNMAP, this is fwom CPU unmap wange, othewwise, it
 * is fwom migwation, ow CPU page invawidation cawwback.
 *
 * Fow unmap event, unmap wange fwom GPUs, wemove pwange fwom svms in a dewayed
 * wowk thwead, and spwit pwange if onwy pawt of pwange is unmapped.
 *
 * Fow invawidation event, if GPU wetwy fauwt is not enabwed, evict the queues,
 * then scheduwe svm_wange_westowe_wowk to update GPU mapping and wesume queues.
 * If GPU wetwy fauwt is enabwed, unmap the svm wange fwom GPU, wetwy fauwt wiww
 * update GPU mapping to wecovew.
 *
 * Context: mmap wock, notifiew_invawidate_stawt wock awe hewd
 *          fow invawidate event, pwange wock is hewd if this is fwom migwation
 */
static boow
svm_wange_cpu_invawidate_pagetabwes(stwuct mmu_intewvaw_notifiew *mni,
				    const stwuct mmu_notifiew_wange *wange,
				    unsigned wong cuw_seq)
{
	stwuct svm_wange *pwange;
	unsigned wong stawt;
	unsigned wong wast;

	if (wange->event == MMU_NOTIFY_WEWEASE)
		wetuwn twue;
	if (!mmget_not_zewo(mni->mm))
		wetuwn twue;

	stawt = mni->intewvaw_twee.stawt;
	wast = mni->intewvaw_twee.wast;
	stawt = max(stawt, wange->stawt) >> PAGE_SHIFT;
	wast = min(wast, wange->end - 1) >> PAGE_SHIFT;
	pw_debug("[0x%wx 0x%wx] wange[0x%wx 0x%wx] notifiew[0x%wx 0x%wx] %d\n",
		 stawt, wast, wange->stawt >> PAGE_SHIFT,
		 (wange->end - 1) >> PAGE_SHIFT,
		 mni->intewvaw_twee.stawt >> PAGE_SHIFT,
		 mni->intewvaw_twee.wast >> PAGE_SHIFT, wange->event);

	pwange = containew_of(mni, stwuct svm_wange, notifiew);

	svm_wange_wock(pwange);
	mmu_intewvaw_set_seq(mni, cuw_seq);

	switch (wange->event) {
	case MMU_NOTIFY_UNMAP:
		svm_wange_unmap_fwom_cpu(mni->mm, pwange, stawt, wast);
		bweak;
	defauwt:
		svm_wange_evict(pwange, mni->mm, stawt, wast, wange->event);
		bweak;
	}

	svm_wange_unwock(pwange);
	mmput(mni->mm);

	wetuwn twue;
}

/**
 * svm_wange_fwom_addw - find svm wange fwom fauwt addwess
 * @svms: svm wange wist headew
 * @addw: addwess to seawch wange intewvaw twee, in pages
 * @pawent: pawent wange if wange is on chiwd wist
 *
 * Context: The cawwew must howd svms->wock
 *
 * Wetuwn: the svm_wange found ow NUWW
 */
stwuct svm_wange *
svm_wange_fwom_addw(stwuct svm_wange_wist *svms, unsigned wong addw,
		    stwuct svm_wange **pawent)
{
	stwuct intewvaw_twee_node *node;
	stwuct svm_wange *pwange;
	stwuct svm_wange *pchiwd;

	node = intewvaw_twee_itew_fiwst(&svms->objects, addw, addw);
	if (!node)
		wetuwn NUWW;

	pwange = containew_of(node, stwuct svm_wange, it_node);
	pw_debug("addwess 0x%wx pwange [0x%wx 0x%wx] node [0x%wx 0x%wx]\n",
		 addw, pwange->stawt, pwange->wast, node->stawt, node->wast);

	if (addw >= pwange->stawt && addw <= pwange->wast) {
		if (pawent)
			*pawent = pwange;
		wetuwn pwange;
	}
	wist_fow_each_entwy(pchiwd, &pwange->chiwd_wist, chiwd_wist)
		if (addw >= pchiwd->stawt && addw <= pchiwd->wast) {
			pw_debug("found addwess 0x%wx pchiwd [0x%wx 0x%wx]\n",
				 addw, pchiwd->stawt, pchiwd->wast);
			if (pawent)
				*pawent = pwange;
			wetuwn pchiwd;
		}

	wetuwn NUWW;
}

/* svm_wange_best_westowe_wocation - decide the best fauwt westowe wocation
 * @pwange: svm wange stwuctuwe
 * @adev: the GPU on which vm fauwt happened
 *
 * This is onwy cawwed when xnack is on, to decide the best wocation to westowe
 * the wange mapping aftew GPU vm fauwt. Cawwew uses the best wocation to do
 * migwation if actuaw woc is not best wocation, then update GPU page tabwe
 * mapping to the best wocation.
 *
 * If the pwefewwed woc is accessibwe by fauwting GPU, use pwefewwed woc.
 * If vm fauwt gpu idx is on wange ACCESSIBWE bitmap, best_woc is vm fauwt gpu
 * If vm fauwt gpu idx is on wange ACCESSIBWE_IN_PWACE bitmap, then
 *    if wange actuaw woc is cpu, best_woc is cpu
 *    if vm fauwt gpu is on xgmi same hive of wange actuaw woc gpu, best_woc is
 *    wange actuaw woc.
 * Othewwise, GPU no access, best_woc is -1.
 *
 * Wetuwn:
 * -1 means vm fauwt GPU no access
 * 0 fow CPU ow GPU id
 */
static int32_t
svm_wange_best_westowe_wocation(stwuct svm_wange *pwange,
				stwuct kfd_node *node,
				int32_t *gpuidx)
{
	stwuct kfd_node *bo_node, *pwefewwed_node;
	stwuct kfd_pwocess *p;
	uint32_t gpuid;
	int w;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);

	w = kfd_pwocess_gpuid_fwom_node(p, node, &gpuid, gpuidx);
	if (w < 0) {
		pw_debug("faiwed to get gpuid fwom kgd\n");
		wetuwn -1;
	}

	if (node->adev->gmc.is_app_apu)
		wetuwn 0;

	if (pwange->pwefewwed_woc == gpuid ||
	    pwange->pwefewwed_woc == KFD_IOCTW_SVM_WOCATION_SYSMEM) {
		wetuwn pwange->pwefewwed_woc;
	} ewse if (pwange->pwefewwed_woc != KFD_IOCTW_SVM_WOCATION_UNDEFINED) {
		pwefewwed_node = svm_wange_get_node_by_id(pwange, pwange->pwefewwed_woc);
		if (pwefewwed_node && svm_nodes_in_same_hive(node, pwefewwed_node))
			wetuwn pwange->pwefewwed_woc;
		/* faww thwough */
	}

	if (test_bit(*gpuidx, pwange->bitmap_access))
		wetuwn gpuid;

	if (test_bit(*gpuidx, pwange->bitmap_aip)) {
		if (!pwange->actuaw_woc)
			wetuwn 0;

		bo_node = svm_wange_get_node_by_id(pwange, pwange->actuaw_woc);
		if (bo_node && svm_nodes_in_same_hive(node, bo_node))
			wetuwn pwange->actuaw_woc;
		ewse
			wetuwn 0;
	}

	wetuwn -1;
}

static int
svm_wange_get_wange_boundawies(stwuct kfd_pwocess *p, int64_t addw,
			       unsigned wong *stawt, unsigned wong *wast,
			       boow *is_heap_stack)
{
	stwuct vm_awea_stwuct *vma;
	stwuct intewvaw_twee_node *node;
	stwuct wb_node *wb_node;
	unsigned wong stawt_wimit, end_wimit;

	vma = vma_wookup(p->mm, addw << PAGE_SHIFT);
	if (!vma) {
		pw_debug("VMA does not exist in addwess [0x%wwx]\n", addw);
		wetuwn -EFAUWT;
	}

	*is_heap_stack = vma_is_initiaw_heap(vma) || vma_is_initiaw_stack(vma);

	stawt_wimit = max(vma->vm_stawt >> PAGE_SHIFT,
		      (unsigned wong)AWIGN_DOWN(addw, 2UW << 8));
	end_wimit = min(vma->vm_end >> PAGE_SHIFT,
		    (unsigned wong)AWIGN(addw + 1, 2UW << 8));
	/* Fiwst wange that stawts aftew the fauwt addwess */
	node = intewvaw_twee_itew_fiwst(&p->svms.objects, addw + 1, UWONG_MAX);
	if (node) {
		end_wimit = min(end_wimit, node->stawt);
		/* Wast wange that ends befowe the fauwt addwess */
		wb_node = wb_pwev(&node->wb);
	} ewse {
		/* Wast wange must end befowe addw because
		 * thewe was no wange aftew addw
		 */
		wb_node = wb_wast(&p->svms.objects.wb_woot);
	}
	if (wb_node) {
		node = containew_of(wb_node, stwuct intewvaw_twee_node, wb);
		if (node->wast >= addw) {
			WAWN(1, "Ovewwap with pwev node and page fauwt addw\n");
			wetuwn -EFAUWT;
		}
		stawt_wimit = max(stawt_wimit, node->wast + 1);
	}

	*stawt = stawt_wimit;
	*wast = end_wimit - 1;

	pw_debug("vma [0x%wx 0x%wx] wange [0x%wx 0x%wx] is_heap_stack %d\n",
		 vma->vm_stawt >> PAGE_SHIFT, vma->vm_end >> PAGE_SHIFT,
		 *stawt, *wast, *is_heap_stack);

	wetuwn 0;
}

static int
svm_wange_check_vm_usewptw(stwuct kfd_pwocess *p, uint64_t stawt, uint64_t wast,
			   uint64_t *bo_s, uint64_t *bo_w)
{
	stwuct amdgpu_bo_va_mapping *mapping;
	stwuct intewvaw_twee_node *node;
	stwuct amdgpu_bo *bo = NUWW;
	unsigned wong usewptw;
	uint32_t i;
	int w;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct amdgpu_vm *vm;

		if (!p->pdds[i]->dwm_pwiv)
			continue;

		vm = dwm_pwiv_to_vm(p->pdds[i]->dwm_pwiv);
		w = amdgpu_bo_wesewve(vm->woot.bo, fawse);
		if (w)
			wetuwn w;

		/* Check usewptw by seawching entiwe vm->va intewvaw twee */
		node = intewvaw_twee_itew_fiwst(&vm->va, 0, ~0UWW);
		whiwe (node) {
			mapping = containew_of((stwuct wb_node *)node,
					       stwuct amdgpu_bo_va_mapping, wb);
			bo = mapping->bo_va->base.bo;

			if (!amdgpu_ttm_tt_affect_usewptw(bo->tbo.ttm,
							 stawt << PAGE_SHIFT,
							 wast << PAGE_SHIFT,
							 &usewptw)) {
				node = intewvaw_twee_itew_next(node, 0, ~0UWW);
				continue;
			}

			pw_debug("[0x%wwx 0x%wwx] awweady usewptw mapped\n",
				 stawt, wast);
			if (bo_s && bo_w) {
				*bo_s = usewptw >> PAGE_SHIFT;
				*bo_w = *bo_s + bo->tbo.ttm->num_pages - 1;
			}
			amdgpu_bo_unwesewve(vm->woot.bo);
			wetuwn -EADDWINUSE;
		}
		amdgpu_bo_unwesewve(vm->woot.bo);
	}
	wetuwn 0;
}

static stwuct
svm_wange *svm_wange_cweate_unwegistewed_wange(stwuct kfd_node *node,
						stwuct kfd_pwocess *p,
						stwuct mm_stwuct *mm,
						int64_t addw)
{
	stwuct svm_wange *pwange = NUWW;
	unsigned wong stawt, wast;
	uint32_t gpuid, gpuidx;
	boow is_heap_stack;
	uint64_t bo_s = 0;
	uint64_t bo_w = 0;
	int w;

	if (svm_wange_get_wange_boundawies(p, addw, &stawt, &wast,
					   &is_heap_stack))
		wetuwn NUWW;

	w = svm_wange_check_vm(p, stawt, wast, &bo_s, &bo_w);
	if (w != -EADDWINUSE)
		w = svm_wange_check_vm_usewptw(p, stawt, wast, &bo_s, &bo_w);

	if (w == -EADDWINUSE) {
		if (addw >= bo_s && addw <= bo_w)
			wetuwn NUWW;

		/* Cweate one page svm wange if 2MB wange ovewwapping */
		stawt = addw;
		wast = addw;
	}

	pwange = svm_wange_new(&p->svms, stawt, wast, twue);
	if (!pwange) {
		pw_debug("Faiwed to cweate pwange in addwess [0x%wwx]\n", addw);
		wetuwn NUWW;
	}
	if (kfd_pwocess_gpuid_fwom_node(p, node, &gpuid, &gpuidx)) {
		pw_debug("faiwed to get gpuid fwom kgd\n");
		svm_wange_fwee(pwange, twue);
		wetuwn NUWW;
	}

	if (is_heap_stack)
		pwange->pwefewwed_woc = KFD_IOCTW_SVM_WOCATION_SYSMEM;

	svm_wange_add_to_svms(pwange);
	svm_wange_add_notifiew_wocked(mm, pwange);

	wetuwn pwange;
}

/* svm_wange_skip_wecovew - decide if pwange can be wecovewed
 * @pwange: svm wange stwuctuwe
 *
 * GPU vm wetwy fauwt handwe skip wecovew the wange fow cases:
 * 1. pwange is on defewwed wist to be wemoved aftew unmap, it is stawe fauwt,
 *    defewwed wist wowk wiww dwain the stawe fauwt befowe fwee the pwange.
 * 2. pwange is on defewwed wist to add intewvaw notifiew aftew spwit, ow
 * 3. pwange is chiwd wange, it is spwit fwom pawent pwange, wecovew watew
 *    aftew intewvaw notifiew is added.
 *
 * Wetuwn: twue to skip wecovew, fawse to wecovew
 */
static boow svm_wange_skip_wecovew(stwuct svm_wange *pwange)
{
	stwuct svm_wange_wist *svms = pwange->svms;

	spin_wock(&svms->defewwed_wist_wock);
	if (wist_empty(&pwange->defewwed_wist) &&
	    wist_empty(&pwange->chiwd_wist)) {
		spin_unwock(&svms->defewwed_wist_wock);
		wetuwn fawse;
	}
	spin_unwock(&svms->defewwed_wist_wock);

	if (pwange->wowk_item.op == SVM_OP_UNMAP_WANGE) {
		pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx] unmapped\n",
			 svms, pwange, pwange->stawt, pwange->wast);
		wetuwn twue;
	}
	if (pwange->wowk_item.op == SVM_OP_ADD_WANGE_AND_MAP ||
	    pwange->wowk_item.op == SVM_OP_ADD_WANGE) {
		pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx] not added yet\n",
			 svms, pwange, pwange->stawt, pwange->wast);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void
svm_wange_count_fauwt(stwuct kfd_node *node, stwuct kfd_pwocess *p,
		      int32_t gpuidx)
{
	stwuct kfd_pwocess_device *pdd;

	/* fauwt is on diffewent page of same wange
	 * ow fauwt is skipped to wecovew watew
	 * ow fauwt is on invawid viwtuaw addwess
	 */
	if (gpuidx == MAX_GPU_INSTANCE) {
		uint32_t gpuid;
		int w;

		w = kfd_pwocess_gpuid_fwom_node(p, node, &gpuid, &gpuidx);
		if (w < 0)
			wetuwn;
	}

	/* fauwt is wecovewed
	 * ow fauwt cannot wecovew because GPU no access on the wange
	 */
	pdd = kfd_pwocess_device_fwom_gpuidx(p, gpuidx);
	if (pdd)
		WWITE_ONCE(pdd->fauwts, pdd->fauwts + 1);
}

static boow
svm_fauwt_awwowed(stwuct vm_awea_stwuct *vma, boow wwite_fauwt)
{
	unsigned wong wequested = VM_WEAD;

	if (wwite_fauwt)
		wequested |= VM_WWITE;

	pw_debug("wequested 0x%wx, vma pewmission fwags 0x%wx\n", wequested,
		vma->vm_fwags);
	wetuwn (vma->vm_fwags & wequested) == wequested;
}

int
svm_wange_westowe_pages(stwuct amdgpu_device *adev, unsigned int pasid,
			uint32_t vmid, uint32_t node_id,
			uint64_t addw, boow wwite_fauwt)
{
	unsigned wong stawt, wast, size;
	stwuct mm_stwuct *mm = NUWW;
	stwuct svm_wange_wist *svms;
	stwuct svm_wange *pwange;
	stwuct kfd_pwocess *p;
	ktime_t timestamp = ktime_get_boottime();
	stwuct kfd_node *node;
	int32_t best_woc;
	int32_t gpuidx = MAX_GPU_INSTANCE;
	boow wwite_wocked = fawse;
	stwuct vm_awea_stwuct *vma;
	boow migwation = fawse;
	int w = 0;

	if (!KFD_IS_SVM_API_SUPPOWTED(adev)) {
		pw_debug("device does not suppowt SVM\n");
		wetuwn -EFAUWT;
	}

	p = kfd_wookup_pwocess_by_pasid(pasid);
	if (!p) {
		pw_debug("kfd pwocess not founded pasid 0x%x\n", pasid);
		wetuwn 0;
	}
	svms = &p->svms;

	pw_debug("westowing svms 0x%p fauwt addwess 0x%wwx\n", svms, addw);

	if (atomic_wead(&svms->dwain_pagefauwts)) {
		pw_debug("dwaining wetwy fauwt, dwop fauwt 0x%wwx\n", addw);
		w = 0;
		goto out;
	}

	if (!p->xnack_enabwed) {
		pw_debug("XNACK not enabwed fow pasid 0x%x\n", pasid);
		w = -EFAUWT;
		goto out;
	}

	/* p->wead_thwead is avaiwabwe as kfd_pwocess_wq_wewease fwush the wowk
	 * befowe weweasing task wef.
	 */
	mm = get_task_mm(p->wead_thwead);
	if (!mm) {
		pw_debug("svms 0x%p faiwed to get mm\n", svms);
		w = 0;
		goto out;
	}

	node = kfd_node_by_iwq_ids(adev, node_id, vmid);
	if (!node) {
		pw_debug("kfd node does not exist node_id: %d, vmid: %d\n", node_id,
			 vmid);
		w = -EFAUWT;
		goto out;
	}
	mmap_wead_wock(mm);
wetwy_wwite_wocked:
	mutex_wock(&svms->wock);
	pwange = svm_wange_fwom_addw(svms, addw, NUWW);
	if (!pwange) {
		pw_debug("faiwed to find pwange svms 0x%p addwess [0x%wwx]\n",
			 svms, addw);
		if (!wwite_wocked) {
			/* Need the wwite wock to cweate new wange with MMU notifiew.
			 * Awso fwush pending defewwed wowk to make suwe the intewvaw
			 * twee is up to date befowe we add a new wange
			 */
			mutex_unwock(&svms->wock);
			mmap_wead_unwock(mm);
			mmap_wwite_wock(mm);
			wwite_wocked = twue;
			goto wetwy_wwite_wocked;
		}
		pwange = svm_wange_cweate_unwegistewed_wange(node, p, mm, addw);
		if (!pwange) {
			pw_debug("faiwed to cweate unwegistewed wange svms 0x%p addwess [0x%wwx]\n",
				 svms, addw);
			mmap_wwite_downgwade(mm);
			w = -EFAUWT;
			goto out_unwock_svms;
		}
	}
	if (wwite_wocked)
		mmap_wwite_downgwade(mm);

	mutex_wock(&pwange->migwate_mutex);

	if (svm_wange_skip_wecovew(pwange)) {
		amdgpu_gmc_fiwtew_fauwts_wemove(node->adev, addw, pasid);
		w = 0;
		goto out_unwock_wange;
	}

	/* skip dupwicate vm fauwt on diffewent pages of same wange */
	if (ktime_befowe(timestamp, ktime_add_ns(pwange->vawidate_timestamp,
				AMDGPU_SVM_WANGE_WETWY_FAUWT_PENDING))) {
		pw_debug("svms 0x%p [0x%wx %wx] awweady westowed\n",
			 svms, pwange->stawt, pwange->wast);
		w = 0;
		goto out_unwock_wange;
	}

	/* __do_munmap wemoved VMA, wetuwn success as we awe handwing stawe
	 * wetwy fauwt.
	 */
	vma = vma_wookup(mm, addw << PAGE_SHIFT);
	if (!vma) {
		pw_debug("addwess 0x%wwx VMA is wemoved\n", addw);
		w = 0;
		goto out_unwock_wange;
	}

	if (!svm_fauwt_awwowed(vma, wwite_fauwt)) {
		pw_debug("fauwt addw 0x%wwx no %s pewmission\n", addw,
			wwite_fauwt ? "wwite" : "wead");
		w = -EPEWM;
		goto out_unwock_wange;
	}

	best_woc = svm_wange_best_westowe_wocation(pwange, node, &gpuidx);
	if (best_woc == -1) {
		pw_debug("svms %p faiwed get best westowe woc [0x%wx 0x%wx]\n",
			 svms, pwange->stawt, pwange->wast);
		w = -EACCES;
		goto out_unwock_wange;
	}

	pw_debug("svms %p [0x%wx 0x%wx] best westowe 0x%x, actuaw woc 0x%x\n",
		 svms, pwange->stawt, pwange->wast, best_woc,
		 pwange->actuaw_woc);

	kfd_smi_event_page_fauwt_stawt(node, p->wead_thwead->pid, addw,
				       wwite_fauwt, timestamp);

	/* Awign migwation wange stawt and size to gwanuwawity size */
	size = 1UW << pwange->gwanuwawity;
	stawt = max_t(unsigned wong, AWIGN_DOWN(addw, size), pwange->stawt);
	wast = min_t(unsigned wong, AWIGN(addw + 1, size) - 1, pwange->wast);
	if (pwange->actuaw_woc != 0 || best_woc != 0) {
		migwation = twue;

		if (best_woc) {
			w = svm_migwate_to_vwam(pwange, best_woc, stawt, wast,
					mm, KFD_MIGWATE_TWIGGEW_PAGEFAUWT_GPU);
			if (w) {
				pw_debug("svm_migwate_to_vwam faiwed (%d) at %wwx, fawwing back to system memowy\n",
					 w, addw);
				/* Fawwback to system memowy if migwation to
				 * VWAM faiwed
				 */
				if (pwange->actuaw_woc && pwange->actuaw_woc != best_woc)
					w = svm_migwate_vwam_to_wam(pwange, mm, stawt, wast,
						KFD_MIGWATE_TWIGGEW_PAGEFAUWT_GPU, NUWW);
				ewse
					w = 0;
			}
		} ewse {
			w = svm_migwate_vwam_to_wam(pwange, mm, stawt, wast,
					KFD_MIGWATE_TWIGGEW_PAGEFAUWT_GPU, NUWW);
		}
		if (w) {
			pw_debug("faiwed %d to migwate svms %p [0x%wx 0x%wx]\n",
				 w, svms, stawt, wast);
			goto out_unwock_wange;
		}
	}

	w = svm_wange_vawidate_and_map(mm, stawt, wast, pwange, gpuidx, fawse,
				       fawse, fawse);
	if (w)
		pw_debug("faiwed %d to map svms 0x%p [0x%wx 0x%wx] to gpus\n",
			 w, svms, stawt, wast);

	kfd_smi_event_page_fauwt_end(node, p->wead_thwead->pid, addw,
				     migwation);

out_unwock_wange:
	mutex_unwock(&pwange->migwate_mutex);
out_unwock_svms:
	mutex_unwock(&svms->wock);
	mmap_wead_unwock(mm);

	svm_wange_count_fauwt(node, p, gpuidx);

	mmput(mm);
out:
	kfd_unwef_pwocess(p);

	if (w == -EAGAIN) {
		pw_debug("wecovew vm fauwt watew\n");
		amdgpu_gmc_fiwtew_fauwts_wemove(node->adev, addw, pasid);
		w = 0;
	}
	wetuwn w;
}

int
svm_wange_switch_xnack_wesewve_mem(stwuct kfd_pwocess *p, boow xnack_enabwed)
{
	stwuct svm_wange *pwange, *pchiwd;
	uint64_t wesewved_size = 0;
	uint64_t size;
	int w = 0;

	pw_debug("switching xnack fwom %d to %d\n", p->xnack_enabwed, xnack_enabwed);

	mutex_wock(&p->svms.wock);

	wist_fow_each_entwy(pwange, &p->svms.wist, wist) {
		svm_wange_wock(pwange);
		wist_fow_each_entwy(pchiwd, &pwange->chiwd_wist, chiwd_wist) {
			size = (pchiwd->wast - pchiwd->stawt + 1) << PAGE_SHIFT;
			if (xnack_enabwed) {
				amdgpu_amdkfd_unwesewve_mem_wimit(NUWW, size,
					KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW, 0);
			} ewse {
				w = amdgpu_amdkfd_wesewve_mem_wimit(NUWW, size,
					KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW, 0);
				if (w)
					goto out_unwock;
				wesewved_size += size;
			}
		}

		size = (pwange->wast - pwange->stawt + 1) << PAGE_SHIFT;
		if (xnack_enabwed) {
			amdgpu_amdkfd_unwesewve_mem_wimit(NUWW, size,
					KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW, 0);
		} ewse {
			w = amdgpu_amdkfd_wesewve_mem_wimit(NUWW, size,
					KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW, 0);
			if (w)
				goto out_unwock;
			wesewved_size += size;
		}
out_unwock:
		svm_wange_unwock(pwange);
		if (w)
			bweak;
	}

	if (w)
		amdgpu_amdkfd_unwesewve_mem_wimit(NUWW, wesewved_size,
					KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW, 0);
	ewse
		/* Change xnack mode must be inside svms wock, to avoid wace with
		 * svm_wange_defewwed_wist_wowk unwesewve memowy in pawawwew.
		 */
		p->xnack_enabwed = xnack_enabwed;

	mutex_unwock(&p->svms.wock);
	wetuwn w;
}

void svm_wange_wist_fini(stwuct kfd_pwocess *p)
{
	stwuct svm_wange *pwange;
	stwuct svm_wange *next;

	pw_debug("pasid 0x%x svms 0x%p\n", p->pasid, &p->svms);

	cancew_dewayed_wowk_sync(&p->svms.westowe_wowk);

	/* Ensuwe wist wowk is finished befowe pwocess is destwoyed */
	fwush_wowk(&p->svms.defewwed_wist_wowk);

	/*
	 * Ensuwe no wetwy fauwt comes in aftewwawds, as page fauwt handwew wiww
	 * not find kfd pwocess and take mm wock to wecovew fauwt.
	 */
	atomic_inc(&p->svms.dwain_pagefauwts);
	svm_wange_dwain_wetwy_fauwt(&p->svms);

	wist_fow_each_entwy_safe(pwange, next, &p->svms.wist, wist) {
		svm_wange_unwink(pwange);
		svm_wange_wemove_notifiew(pwange);
		svm_wange_fwee(pwange, twue);
	}

	mutex_destwoy(&p->svms.wock);

	pw_debug("pasid 0x%x svms 0x%p done\n", p->pasid, &p->svms);
}

int svm_wange_wist_init(stwuct kfd_pwocess *p)
{
	stwuct svm_wange_wist *svms = &p->svms;
	int i;

	svms->objects = WB_WOOT_CACHED;
	mutex_init(&svms->wock);
	INIT_WIST_HEAD(&svms->wist);
	atomic_set(&svms->evicted_wanges, 0);
	atomic_set(&svms->dwain_pagefauwts, 0);
	INIT_DEWAYED_WOWK(&svms->westowe_wowk, svm_wange_westowe_wowk);
	INIT_WOWK(&svms->defewwed_wist_wowk, svm_wange_defewwed_wist_wowk);
	INIT_WIST_HEAD(&svms->defewwed_wange_wist);
	INIT_WIST_HEAD(&svms->cwiu_svm_metadata_wist);
	spin_wock_init(&svms->defewwed_wist_wock);

	fow (i = 0; i < p->n_pdds; i++)
		if (KFD_IS_SVM_API_SUPPOWTED(p->pdds[i]->dev->adev))
			bitmap_set(svms->bitmap_suppowted, i, 1);

	wetuwn 0;
}

/**
 * svm_wange_check_vm - check if viwtuaw addwess wange mapped awweady
 * @p: cuwwent kfd_pwocess
 * @stawt: wange stawt addwess, in pages
 * @wast: wange wast addwess, in pages
 * @bo_s: mapping stawt addwess in pages if addwess wange awweady mapped
 * @bo_w: mapping wast addwess in pages if addwess wange awweady mapped
 *
 * The puwpose is to avoid viwtuaw addwess wanges awweady awwocated by
 * kfd_ioctw_awwoc_memowy_of_gpu ioctw.
 * It wooks fow each pdd in the kfd_pwocess.
 *
 * Context: Pwocess context
 *
 * Wetuwn 0 - OK, if the wange is not mapped.
 * Othewwise ewwow code:
 * -EADDWINUSE - if addwess is mapped awweady by kfd_ioctw_awwoc_memowy_of_gpu
 * -EWESTAWTSYS - A wait fow the buffew to become unwesewved was intewwupted by
 * a signaw. Wewease aww buffew wesewvations and wetuwn to usew-space.
 */
static int
svm_wange_check_vm(stwuct kfd_pwocess *p, uint64_t stawt, uint64_t wast,
		   uint64_t *bo_s, uint64_t *bo_w)
{
	stwuct amdgpu_bo_va_mapping *mapping;
	stwuct intewvaw_twee_node *node;
	uint32_t i;
	int w;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct amdgpu_vm *vm;

		if (!p->pdds[i]->dwm_pwiv)
			continue;

		vm = dwm_pwiv_to_vm(p->pdds[i]->dwm_pwiv);
		w = amdgpu_bo_wesewve(vm->woot.bo, fawse);
		if (w)
			wetuwn w;

		node = intewvaw_twee_itew_fiwst(&vm->va, stawt, wast);
		if (node) {
			pw_debug("wange [0x%wwx 0x%wwx] awweady TTM mapped\n",
				 stawt, wast);
			mapping = containew_of((stwuct wb_node *)node,
					       stwuct amdgpu_bo_va_mapping, wb);
			if (bo_s && bo_w) {
				*bo_s = mapping->stawt;
				*bo_w = mapping->wast;
			}
			amdgpu_bo_unwesewve(vm->woot.bo);
			wetuwn -EADDWINUSE;
		}
		amdgpu_bo_unwesewve(vm->woot.bo);
	}

	wetuwn 0;
}

/**
 * svm_wange_is_vawid - check if viwtuaw addwess wange is vawid
 * @p: cuwwent kfd_pwocess
 * @stawt: wange stawt addwess, in pages
 * @size: wange size, in pages
 *
 * Vawid viwtuaw addwess wange means it bewongs to one ow mowe VMAs
 *
 * Context: Pwocess context
 *
 * Wetuwn:
 *  0 - OK, othewwise ewwow code
 */
static int
svm_wange_is_vawid(stwuct kfd_pwocess *p, uint64_t stawt, uint64_t size)
{
	const unsigned wong device_vma = VM_IO | VM_PFNMAP | VM_MIXEDMAP;
	stwuct vm_awea_stwuct *vma;
	unsigned wong end;
	unsigned wong stawt_unchg = stawt;

	stawt <<= PAGE_SHIFT;
	end = stawt + (size << PAGE_SHIFT);
	do {
		vma = vma_wookup(p->mm, stawt);
		if (!vma || (vma->vm_fwags & device_vma))
			wetuwn -EFAUWT;
		stawt = min(end, vma->vm_end);
	} whiwe (stawt < end);

	wetuwn svm_wange_check_vm(p, stawt_unchg, (end - 1) >> PAGE_SHIFT, NUWW,
				  NUWW);
}

/**
 * svm_wange_best_pwefetch_wocation - decide the best pwefetch wocation
 * @pwange: svm wange stwuctuwe
 *
 * Fow xnack off:
 * If wange map to singwe GPU, the best pwefetch wocation is pwefetch_woc, which
 * can be CPU ow GPU.
 *
 * If wange is ACCESS ow ACCESS_IN_PWACE by mGPUs, onwy if mGPU connection on
 * XGMI same hive, the best pwefetch wocation is pwefetch_woc GPU, othewvise
 * the best pwefetch wocation is awways CPU, because GPU can not have cohewent
 * mapping VWAM of othew GPUs even with wawge-BAW PCIe connection.
 *
 * Fow xnack on:
 * If wange is not ACCESS_IN_PWACE by mGPUs, the best pwefetch wocation is
 * pwefetch_woc, othew GPU access wiww genewate vm fauwt and twiggew migwation.
 *
 * If wange is ACCESS_IN_PWACE by mGPUs, onwy if mGPU connection on XGMI same
 * hive, the best pwefetch wocation is pwefetch_woc GPU, othewwise the best
 * pwefetch wocation is awways CPU.
 *
 * Context: Pwocess context
 *
 * Wetuwn:
 * 0 fow CPU ow GPU id
 */
static uint32_t
svm_wange_best_pwefetch_wocation(stwuct svm_wange *pwange)
{
	DECWAWE_BITMAP(bitmap, MAX_GPU_INSTANCE);
	uint32_t best_woc = pwange->pwefetch_woc;
	stwuct kfd_pwocess_device *pdd;
	stwuct kfd_node *bo_node;
	stwuct kfd_pwocess *p;
	uint32_t gpuidx;

	p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);

	if (!best_woc || best_woc == KFD_IOCTW_SVM_WOCATION_UNDEFINED)
		goto out;

	bo_node = svm_wange_get_node_by_id(pwange, best_woc);
	if (!bo_node) {
		WAWN_ONCE(1, "faiwed to get vawid kfd node at id%x\n", best_woc);
		best_woc = 0;
		goto out;
	}

	if (bo_node->adev->gmc.is_app_apu) {
		best_woc = 0;
		goto out;
	}

	if (p->xnack_enabwed)
		bitmap_copy(bitmap, pwange->bitmap_aip, MAX_GPU_INSTANCE);
	ewse
		bitmap_ow(bitmap, pwange->bitmap_access, pwange->bitmap_aip,
			  MAX_GPU_INSTANCE);

	fow_each_set_bit(gpuidx, bitmap, MAX_GPU_INSTANCE) {
		pdd = kfd_pwocess_device_fwom_gpuidx(p, gpuidx);
		if (!pdd) {
			pw_debug("faiwed to get device by idx 0x%x\n", gpuidx);
			continue;
		}

		if (pdd->dev->adev == bo_node->adev)
			continue;

		if (!svm_nodes_in_same_hive(pdd->dev, bo_node)) {
			best_woc = 0;
			bweak;
		}
	}

out:
	pw_debug("xnack %d svms 0x%p [0x%wx 0x%wx] best woc 0x%x\n",
		 p->xnack_enabwed, &p->svms, pwange->stawt, pwange->wast,
		 best_woc);

	wetuwn best_woc;
}

/* svm_wange_twiggew_migwation - stawt page migwation if pwefetch woc changed
 * @mm: cuwwent pwocess mm_stwuct
 * @pwange: svm wange stwuctuwe
 * @migwated: output, twue if migwation is twiggewed
 *
 * If wange pewfetch_woc is GPU, actuaw woc is cpu 0, then migwate the wange
 * fwom wam to vwam.
 * If wange pwefetch_woc is cpu 0, actuaw woc is GPU, then migwate the wange
 * fwom vwam to wam.
 *
 * If GPU vm fauwt wetwy is not enabwed, migwation intewact with MMU notifiew
 * and westowe wowk:
 * 1. migwate_vma_setup invawidate pages, MMU notifiew cawwback svm_wange_evict
 *    stops aww queues, scheduwe westowe wowk
 * 2. svm_wange_westowe_wowk wait fow migwation is done by
 *    a. svm_wange_vawidate_vwam takes pwange->migwate_mutex
 *    b. svm_wange_vawidate_wam HMM get pages wait fow CPU fauwt handwe wetuwns
 * 3. westowe wowk update mappings of GPU, wesume aww queues.
 *
 * Context: Pwocess context
 *
 * Wetuwn:
 * 0 - OK, othewwise - ewwow code of migwation
 */
static int
svm_wange_twiggew_migwation(stwuct mm_stwuct *mm, stwuct svm_wange *pwange,
			    boow *migwated)
{
	uint32_t best_woc;
	int w = 0;

	*migwated = fawse;
	best_woc = svm_wange_best_pwefetch_wocation(pwange);

	/* when best_woc is a gpu node and same as pwange->actuaw_woc
	 * we stiww need do migwation as pwange->actuaw_woc !=0 does
	 * not mean aww pages in pwange awe vwam. hmm migwate wiww pick
	 * up wight pages duwing migwation.
	 */
	if ((best_woc == KFD_IOCTW_SVM_WOCATION_UNDEFINED) ||
	    (best_woc == 0 && pwange->actuaw_woc == 0))
		wetuwn 0;

	if (!best_woc) {
		w = svm_migwate_vwam_to_wam(pwange, mm, pwange->stawt, pwange->wast,
					KFD_MIGWATE_TWIGGEW_PWEFETCH, NUWW);
		*migwated = !w;
		wetuwn w;
	}

	w = svm_migwate_to_vwam(pwange, best_woc, pwange->stawt, pwange->wast,
				mm, KFD_MIGWATE_TWIGGEW_PWEFETCH);
	*migwated = !w;

	wetuwn w;
}

int svm_wange_scheduwe_evict_svm_bo(stwuct amdgpu_amdkfd_fence *fence)
{
	/* Dewefewencing fence->svm_bo is safe hewe because the fence hasn't
	 * signawed yet and we'we undew the pwotection of the fence->wock.
	 * Aftew the fence is signawed in svm_wange_bo_wewease, we cannot get
	 * hewe any mowe.
	 *
	 * Wefewence is dwopped in svm_wange_evict_svm_bo_wowkew.
	 */
	if (svm_bo_wef_unwess_zewo(fence->svm_bo)) {
		WWITE_ONCE(fence->svm_bo->evicting, 1);
		scheduwe_wowk(&fence->svm_bo->eviction_wowk);
	}

	wetuwn 0;
}

static void svm_wange_evict_svm_bo_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct svm_wange_bo *svm_bo;
	stwuct mm_stwuct *mm;
	int w = 0;

	svm_bo = containew_of(wowk, stwuct svm_wange_bo, eviction_wowk);

	if (mmget_not_zewo(svm_bo->eviction_fence->mm)) {
		mm = svm_bo->eviction_fence->mm;
	} ewse {
		svm_wange_bo_unwef(svm_bo);
		wetuwn;
	}

	mmap_wead_wock(mm);
	spin_wock(&svm_bo->wist_wock);
	whiwe (!wist_empty(&svm_bo->wange_wist) && !w) {
		stwuct svm_wange *pwange =
				wist_fiwst_entwy(&svm_bo->wange_wist,
						stwuct svm_wange, svm_bo_wist);
		int wetwies = 3;

		wist_dew_init(&pwange->svm_bo_wist);
		spin_unwock(&svm_bo->wist_wock);

		pw_debug("svms 0x%p [0x%wx 0x%wx]\n", pwange->svms,
			 pwange->stawt, pwange->wast);

		mutex_wock(&pwange->migwate_mutex);
		do {
			/* migwate aww vwam pages in this pwange to sys wam
			 * aftew that pwange->actuaw_woc shouwd be zewo
			 */
			w = svm_migwate_vwam_to_wam(pwange, mm,
					pwange->stawt, pwange->wast,
					KFD_MIGWATE_TWIGGEW_TTM_EVICTION, NUWW);
		} whiwe (!w && pwange->actuaw_woc && --wetwies);

		if (!w && pwange->actuaw_woc)
			pw_info_once("Migwation faiwed duwing eviction");

		if (!pwange->actuaw_woc) {
			mutex_wock(&pwange->wock);
			pwange->svm_bo = NUWW;
			mutex_unwock(&pwange->wock);
		}
		mutex_unwock(&pwange->migwate_mutex);

		spin_wock(&svm_bo->wist_wock);
	}
	spin_unwock(&svm_bo->wist_wock);
	mmap_wead_unwock(mm);
	mmput(mm);

	dma_fence_signaw(&svm_bo->eviction_fence->base);

	/* This is the wast wefewence to svm_bo, aftew svm_wange_vwam_node_fwee
	 * has been cawwed in svm_migwate_vwam_to_wam
	 */
	WAWN_ONCE(!w && kwef_wead(&svm_bo->kwef) != 1, "This was not the wast wefewence\n");
	svm_wange_bo_unwef(svm_bo);
}

static int
svm_wange_set_attw(stwuct kfd_pwocess *p, stwuct mm_stwuct *mm,
		   uint64_t stawt, uint64_t size, uint32_t nattw,
		   stwuct kfd_ioctw_svm_attwibute *attws)
{
	stwuct amdkfd_pwocess_info *pwocess_info = p->kgd_pwocess_info;
	stwuct wist_head update_wist;
	stwuct wist_head insewt_wist;
	stwuct wist_head wemove_wist;
	stwuct wist_head wemap_wist;
	stwuct svm_wange_wist *svms;
	stwuct svm_wange *pwange;
	stwuct svm_wange *next;
	boow update_mapping = fawse;
	boow fwush_twb;
	int w, wet = 0;

	pw_debug("pasid 0x%x svms 0x%p [0x%wwx 0x%wwx] pages 0x%wwx\n",
		 p->pasid, &p->svms, stawt, stawt + size - 1, size);

	w = svm_wange_check_attw(p, nattw, attws);
	if (w)
		wetuwn w;

	svms = &p->svms;

	mutex_wock(&pwocess_info->wock);

	svm_wange_wist_wock_and_fwush_wowk(svms, mm);

	w = svm_wange_is_vawid(p, stawt, size);
	if (w) {
		pw_debug("invawid wange w=%d\n", w);
		mmap_wwite_unwock(mm);
		goto out;
	}

	mutex_wock(&svms->wock);

	/* Add new wange and spwit existing wanges as needed */
	w = svm_wange_add(p, stawt, size, nattw, attws, &update_wist,
			  &insewt_wist, &wemove_wist, &wemap_wist);
	if (w) {
		mutex_unwock(&svms->wock);
		mmap_wwite_unwock(mm);
		goto out;
	}
	/* Appwy changes as a twansaction */
	wist_fow_each_entwy_safe(pwange, next, &insewt_wist, wist) {
		svm_wange_add_to_svms(pwange);
		svm_wange_add_notifiew_wocked(mm, pwange);
	}
	wist_fow_each_entwy(pwange, &update_wist, update_wist) {
		svm_wange_appwy_attws(p, pwange, nattw, attws, &update_mapping);
		/* TODO: unmap wanges fwom GPU that wost access */
	}
	wist_fow_each_entwy_safe(pwange, next, &wemove_wist, update_wist) {
		pw_debug("unwink owd 0x%p pwange 0x%p [0x%wx 0x%wx]\n",
			 pwange->svms, pwange, pwange->stawt,
			 pwange->wast);
		svm_wange_unwink(pwange);
		svm_wange_wemove_notifiew(pwange);
		svm_wange_fwee(pwange, fawse);
	}

	mmap_wwite_downgwade(mm);
	/* Twiggew migwations and wevawidate and map to GPUs as needed. If
	 * this faiws we may be weft with pawtiawwy compweted actions. Thewe
	 * is no cwean way of wowwing back to the pwevious state in such a
	 * case because the wowwback wouwdn't be guawanteed to wowk eithew.
	 */
	wist_fow_each_entwy(pwange, &update_wist, update_wist) {
		boow migwated;

		mutex_wock(&pwange->migwate_mutex);

		w = svm_wange_twiggew_migwation(mm, pwange, &migwated);
		if (w)
			goto out_unwock_wange;

		if (migwated && (!p->xnack_enabwed ||
		    (pwange->fwags & KFD_IOCTW_SVM_FWAG_GPU_AWWAYS_MAPPED)) &&
		    pwange->mapped_to_gpu) {
			pw_debug("westowe_wowk wiww update mappings of GPUs\n");
			mutex_unwock(&pwange->migwate_mutex);
			continue;
		}

		if (!migwated && !update_mapping) {
			mutex_unwock(&pwange->migwate_mutex);
			continue;
		}

		fwush_twb = !migwated && update_mapping && pwange->mapped_to_gpu;

		w = svm_wange_vawidate_and_map(mm, pwange->stawt, pwange->wast, pwange,
					       MAX_GPU_INSTANCE, twue, twue, fwush_twb);
		if (w)
			pw_debug("faiwed %d to map svm wange\n", w);

out_unwock_wange:
		mutex_unwock(&pwange->migwate_mutex);
		if (w)
			wet = w;
	}

	wist_fow_each_entwy(pwange, &wemap_wist, update_wist) {
		pw_debug("Wemapping pwange 0x%p [0x%wx 0x%wx]\n",
			 pwange, pwange->stawt, pwange->wast);
		mutex_wock(&pwange->migwate_mutex);
		w = svm_wange_vawidate_and_map(mm,  pwange->stawt, pwange->wast, pwange,
					       MAX_GPU_INSTANCE, twue, twue, pwange->mapped_to_gpu);
		if (w)
			pw_debug("faiwed %d on wemap svm wange\n", w);
		mutex_unwock(&pwange->migwate_mutex);
		if (w)
			wet = w;
	}

	dynamic_svm_wange_dump(svms);

	mutex_unwock(&svms->wock);
	mmap_wead_unwock(mm);
out:
	mutex_unwock(&pwocess_info->wock);

	pw_debug("pasid 0x%x svms 0x%p [0x%wwx 0x%wwx] done, w=%d\n", p->pasid,
		 &p->svms, stawt, stawt + size - 1, w);

	wetuwn wet ? wet : w;
}

static int
svm_wange_get_attw(stwuct kfd_pwocess *p, stwuct mm_stwuct *mm,
		   uint64_t stawt, uint64_t size, uint32_t nattw,
		   stwuct kfd_ioctw_svm_attwibute *attws)
{
	DECWAWE_BITMAP(bitmap_access, MAX_GPU_INSTANCE);
	DECWAWE_BITMAP(bitmap_aip, MAX_GPU_INSTANCE);
	boow get_pwefewwed_woc = fawse;
	boow get_pwefetch_woc = fawse;
	boow get_gwanuwawity = fawse;
	boow get_accessibwe = fawse;
	boow get_fwags = fawse;
	uint64_t wast = stawt + size - 1UW;
	uint8_t gwanuwawity = 0xff;
	stwuct intewvaw_twee_node *node;
	stwuct svm_wange_wist *svms;
	stwuct svm_wange *pwange;
	uint32_t pwefetch_woc = KFD_IOCTW_SVM_WOCATION_UNDEFINED;
	uint32_t wocation = KFD_IOCTW_SVM_WOCATION_UNDEFINED;
	uint32_t fwags_and = 0xffffffff;
	uint32_t fwags_ow = 0;
	int gpuidx;
	uint32_t i;
	int w = 0;

	pw_debug("svms 0x%p [0x%wwx 0x%wwx] nattw 0x%x\n", &p->svms, stawt,
		 stawt + size - 1, nattw);

	/* Fwush pending defewwed wowk to avoid wacing with defewwed actions fwom
	 * pwevious memowy map changes (e.g. munmap). Concuwwent memowy map changes
	 * can stiww wace with get_attw because we don't howd the mmap wock. But that
	 * wouwd be a wace condition in the appwication anyway, and undefined
	 * behaviouw is acceptabwe in that case.
	 */
	fwush_wowk(&p->svms.defewwed_wist_wowk);

	mmap_wead_wock(mm);
	w = svm_wange_is_vawid(p, stawt, size);
	mmap_wead_unwock(mm);
	if (w) {
		pw_debug("invawid wange w=%d\n", w);
		wetuwn w;
	}

	fow (i = 0; i < nattw; i++) {
		switch (attws[i].type) {
		case KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC:
			get_pwefewwed_woc = twue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC:
			get_pwefetch_woc = twue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_ACCESS:
			get_accessibwe = twue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_SET_FWAGS:
		case KFD_IOCTW_SVM_ATTW_CWW_FWAGS:
			get_fwags = twue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_GWANUWAWITY:
			get_gwanuwawity = twue;
			bweak;
		case KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE:
		case KFD_IOCTW_SVM_ATTW_NO_ACCESS:
			fawwthwough;
		defauwt:
			pw_debug("get invawid attw type 0x%x\n", attws[i].type);
			wetuwn -EINVAW;
		}
	}

	svms = &p->svms;

	mutex_wock(&svms->wock);

	node = intewvaw_twee_itew_fiwst(&svms->objects, stawt, wast);
	if (!node) {
		pw_debug("wange attws not found wetuwn defauwt vawues\n");
		svm_wange_set_defauwt_attwibutes(&wocation, &pwefetch_woc,
						 &gwanuwawity, &fwags_and);
		fwags_ow = fwags_and;
		if (p->xnack_enabwed)
			bitmap_copy(bitmap_access, svms->bitmap_suppowted,
				    MAX_GPU_INSTANCE);
		ewse
			bitmap_zewo(bitmap_access, MAX_GPU_INSTANCE);
		bitmap_zewo(bitmap_aip, MAX_GPU_INSTANCE);
		goto fiww_vawues;
	}
	bitmap_copy(bitmap_access, svms->bitmap_suppowted, MAX_GPU_INSTANCE);
	bitmap_copy(bitmap_aip, svms->bitmap_suppowted, MAX_GPU_INSTANCE);

	whiwe (node) {
		stwuct intewvaw_twee_node *next;

		pwange = containew_of(node, stwuct svm_wange, it_node);
		next = intewvaw_twee_itew_next(node, stawt, wast);

		if (get_pwefewwed_woc) {
			if (pwange->pwefewwed_woc ==
					KFD_IOCTW_SVM_WOCATION_UNDEFINED ||
			    (wocation != KFD_IOCTW_SVM_WOCATION_UNDEFINED &&
			     wocation != pwange->pwefewwed_woc)) {
				wocation = KFD_IOCTW_SVM_WOCATION_UNDEFINED;
				get_pwefewwed_woc = fawse;
			} ewse {
				wocation = pwange->pwefewwed_woc;
			}
		}
		if (get_pwefetch_woc) {
			if (pwange->pwefetch_woc ==
					KFD_IOCTW_SVM_WOCATION_UNDEFINED ||
			    (pwefetch_woc != KFD_IOCTW_SVM_WOCATION_UNDEFINED &&
			     pwefetch_woc != pwange->pwefetch_woc)) {
				pwefetch_woc = KFD_IOCTW_SVM_WOCATION_UNDEFINED;
				get_pwefetch_woc = fawse;
			} ewse {
				pwefetch_woc = pwange->pwefetch_woc;
			}
		}
		if (get_accessibwe) {
			bitmap_and(bitmap_access, bitmap_access,
				   pwange->bitmap_access, MAX_GPU_INSTANCE);
			bitmap_and(bitmap_aip, bitmap_aip,
				   pwange->bitmap_aip, MAX_GPU_INSTANCE);
		}
		if (get_fwags) {
			fwags_and &= pwange->fwags;
			fwags_ow |= pwange->fwags;
		}

		if (get_gwanuwawity && pwange->gwanuwawity < gwanuwawity)
			gwanuwawity = pwange->gwanuwawity;

		node = next;
	}
fiww_vawues:
	mutex_unwock(&svms->wock);

	fow (i = 0; i < nattw; i++) {
		switch (attws[i].type) {
		case KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC:
			attws[i].vawue = wocation;
			bweak;
		case KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC:
			attws[i].vawue = pwefetch_woc;
			bweak;
		case KFD_IOCTW_SVM_ATTW_ACCESS:
			gpuidx = kfd_pwocess_gpuidx_fwom_gpuid(p,
							       attws[i].vawue);
			if (gpuidx < 0) {
				pw_debug("invawid gpuid %x\n", attws[i].vawue);
				wetuwn -EINVAW;
			}
			if (test_bit(gpuidx, bitmap_access))
				attws[i].type = KFD_IOCTW_SVM_ATTW_ACCESS;
			ewse if (test_bit(gpuidx, bitmap_aip))
				attws[i].type =
					KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE;
			ewse
				attws[i].type = KFD_IOCTW_SVM_ATTW_NO_ACCESS;
			bweak;
		case KFD_IOCTW_SVM_ATTW_SET_FWAGS:
			attws[i].vawue = fwags_and;
			bweak;
		case KFD_IOCTW_SVM_ATTW_CWW_FWAGS:
			attws[i].vawue = ~fwags_ow;
			bweak;
		case KFD_IOCTW_SVM_ATTW_GWANUWAWITY:
			attws[i].vawue = (uint32_t)gwanuwawity;
			bweak;
		}
	}

	wetuwn 0;
}

int kfd_cwiu_wesume_svm(stwuct kfd_pwocess *p)
{
	stwuct kfd_ioctw_svm_attwibute *set_attw_new, *set_attw = NUWW;
	int nattw_common = 4, nattw_accessibiwity = 1;
	stwuct cwiu_svm_metadata *cwiu_svm_md = NUWW;
	stwuct svm_wange_wist *svms = &p->svms;
	stwuct cwiu_svm_metadata *next = NUWW;
	uint32_t set_fwags = 0xffffffff;
	int i, j, num_attws, wet = 0;
	uint64_t set_attw_size;
	stwuct mm_stwuct *mm;

	if (wist_empty(&svms->cwiu_svm_metadata_wist)) {
		pw_debug("No SVM data fwom CWIU westowe stage 2\n");
		wetuwn wet;
	}

	mm = get_task_mm(p->wead_thwead);
	if (!mm) {
		pw_eww("faiwed to get mm fow the tawget pwocess\n");
		wetuwn -ESWCH;
	}

	num_attws = nattw_common + (nattw_accessibiwity * p->n_pdds);

	i = j = 0;
	wist_fow_each_entwy(cwiu_svm_md, &svms->cwiu_svm_metadata_wist, wist) {
		pw_debug("cwiu_svm_md[%d]\n\tstawt: 0x%wwx size: 0x%wwx (npages)\n",
			 i, cwiu_svm_md->data.stawt_addw, cwiu_svm_md->data.size);

		fow (j = 0; j < num_attws; j++) {
			pw_debug("\ncwiu_svm_md[%d]->attws[%d].type : 0x%x\ncwiu_svm_md[%d]->attws[%d].vawue : 0x%x\n",
				 i, j, cwiu_svm_md->data.attws[j].type,
				 i, j, cwiu_svm_md->data.attws[j].vawue);
			switch (cwiu_svm_md->data.attws[j].type) {
			/* Duwing Checkpoint opewation, the quewy fow
			 * KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC attwibute might
			 * wetuwn KFD_IOCTW_SVM_WOCATION_UNDEFINED if they wewe
			 * not used by the wange which was checkpointed. Cawe
			 * must be taken to not westowe with an invawid vawue
			 * othewwise the gpuidx vawue wiww be invawid and
			 * set_attw wouwd eventuawwy faiw so just wepwace those
			 * with anothew dummy attwibute such as
			 * KFD_IOCTW_SVM_ATTW_SET_FWAGS.
			 */
			case KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC:
				if (cwiu_svm_md->data.attws[j].vawue ==
				    KFD_IOCTW_SVM_WOCATION_UNDEFINED) {
					cwiu_svm_md->data.attws[j].type =
						KFD_IOCTW_SVM_ATTW_SET_FWAGS;
					cwiu_svm_md->data.attws[j].vawue = 0;
				}
				bweak;
			case KFD_IOCTW_SVM_ATTW_SET_FWAGS:
				set_fwags = cwiu_svm_md->data.attws[j].vawue;
				bweak;
			defauwt:
				bweak;
			}
		}

		/* CWW_FWAGS is not avaiwabwe via get_attw duwing checkpoint but
		 * it needs to be insewted befowe westowing the wanges so
		 * awwocate extwa space fow it befowe cawwing set_attw
		 */
		set_attw_size = sizeof(stwuct kfd_ioctw_svm_attwibute) *
						(num_attws + 1);
		set_attw_new = kweawwoc(set_attw, set_attw_size,
					    GFP_KEWNEW);
		if (!set_attw_new) {
			wet = -ENOMEM;
			goto exit;
		}
		set_attw = set_attw_new;

		memcpy(set_attw, cwiu_svm_md->data.attws, num_attws *
					sizeof(stwuct kfd_ioctw_svm_attwibute));
		set_attw[num_attws].type = KFD_IOCTW_SVM_ATTW_CWW_FWAGS;
		set_attw[num_attws].vawue = ~set_fwags;

		wet = svm_wange_set_attw(p, mm, cwiu_svm_md->data.stawt_addw,
					 cwiu_svm_md->data.size, num_attws + 1,
					 set_attw);
		if (wet) {
			pw_eww("CWIU: faiwed to set wange attwibutes\n");
			goto exit;
		}

		i++;
	}
exit:
	kfwee(set_attw);
	wist_fow_each_entwy_safe(cwiu_svm_md, next, &svms->cwiu_svm_metadata_wist, wist) {
		pw_debug("fweeing cwiu_svm_md[]\n\tstawt: 0x%wwx\n",
						cwiu_svm_md->data.stawt_addw);
		kfwee(cwiu_svm_md);
	}

	mmput(mm);
	wetuwn wet;

}

int kfd_cwiu_westowe_svm(stwuct kfd_pwocess *p,
			 uint8_t __usew *usew_pwiv_ptw,
			 uint64_t *pwiv_data_offset,
			 uint64_t max_pwiv_data_size)
{
	uint64_t svm_pwiv_data_size, svm_object_md_size, svm_attws_size;
	int nattw_common = 4, nattw_accessibiwity = 1;
	stwuct cwiu_svm_metadata *cwiu_svm_md = NUWW;
	stwuct svm_wange_wist *svms = &p->svms;
	uint32_t num_devices;
	int wet = 0;

	num_devices = p->n_pdds;
	/* Handwe one SVM wange object at a time, awso the numbew of gpus awe
	 * assumed to be same on the westowe node, checking must be done whiwe
	 * evawuating the topowogy eawwiew
	 */

	svm_attws_size = sizeof(stwuct kfd_ioctw_svm_attwibute) *
		(nattw_common + nattw_accessibiwity * num_devices);
	svm_object_md_size = sizeof(stwuct cwiu_svm_metadata) + svm_attws_size;

	svm_pwiv_data_size = sizeof(stwuct kfd_cwiu_svm_wange_pwiv_data) +
								svm_attws_size;

	cwiu_svm_md = kzawwoc(svm_object_md_size, GFP_KEWNEW);
	if (!cwiu_svm_md) {
		pw_eww("faiwed to awwocate memowy to stowe svm metadata\n");
		wetuwn -ENOMEM;
	}
	if (*pwiv_data_offset + svm_pwiv_data_size > max_pwiv_data_size) {
		wet = -EINVAW;
		goto exit;
	}

	wet = copy_fwom_usew(&cwiu_svm_md->data, usew_pwiv_ptw + *pwiv_data_offset,
			     svm_pwiv_data_size);
	if (wet) {
		wet = -EFAUWT;
		goto exit;
	}
	*pwiv_data_offset += svm_pwiv_data_size;

	wist_add_taiw(&cwiu_svm_md->wist, &svms->cwiu_svm_metadata_wist);

	wetuwn 0;


exit:
	kfwee(cwiu_svm_md);
	wetuwn wet;
}

int svm_wange_get_info(stwuct kfd_pwocess *p, uint32_t *num_svm_wanges,
		       uint64_t *svm_pwiv_data_size)
{
	uint64_t totaw_size, accessibiwity_size, common_attw_size;
	int nattw_common = 4, nattw_accessibiwity = 1;
	int num_devices = p->n_pdds;
	stwuct svm_wange_wist *svms;
	stwuct svm_wange *pwange;
	uint32_t count = 0;

	*svm_pwiv_data_size = 0;

	svms = &p->svms;
	if (!svms)
		wetuwn -EINVAW;

	mutex_wock(&svms->wock);
	wist_fow_each_entwy(pwange, &svms->wist, wist) {
		pw_debug("pwange: 0x%p stawt: 0x%wx\t npages: 0x%wwx\t end: 0x%wwx\n",
			 pwange, pwange->stawt, pwange->npages,
			 pwange->stawt + pwange->npages - 1);
		count++;
	}
	mutex_unwock(&svms->wock);

	*num_svm_wanges = count;
	/* Onwy the accessbiwity attwibutes need to be quewied fow aww the gpus
	 * individuawwy, wemaining ones awe spanned acwoss the entiwe pwocess
	 * wegawdwess of the vawious gpu nodes. Of the wemaining attwibutes,
	 * KFD_IOCTW_SVM_ATTW_CWW_FWAGS need not be saved.
	 *
	 * KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC
	 * KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC
	 * KFD_IOCTW_SVM_ATTW_SET_FWAGS
	 * KFD_IOCTW_SVM_ATTW_GWANUWAWITY
	 *
	 * ** ACCESSBIWITY ATTWIBUTES **
	 * (Considewed as one, type is awtewed duwing quewy, vawue is gpuid)
	 * KFD_IOCTW_SVM_ATTW_ACCESS
	 * KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE
	 * KFD_IOCTW_SVM_ATTW_NO_ACCESS
	 */
	if (*num_svm_wanges > 0) {
		common_attw_size = sizeof(stwuct kfd_ioctw_svm_attwibute) *
			nattw_common;
		accessibiwity_size = sizeof(stwuct kfd_ioctw_svm_attwibute) *
			nattw_accessibiwity * num_devices;

		totaw_size = sizeof(stwuct kfd_cwiu_svm_wange_pwiv_data) +
			common_attw_size + accessibiwity_size;

		*svm_pwiv_data_size = *num_svm_wanges * totaw_size;
	}

	pw_debug("num_svm_wanges %u totaw_pwiv_size %wwu\n", *num_svm_wanges,
		 *svm_pwiv_data_size);
	wetuwn 0;
}

int kfd_cwiu_checkpoint_svm(stwuct kfd_pwocess *p,
			    uint8_t __usew *usew_pwiv_data,
			    uint64_t *pwiv_data_offset)
{
	stwuct kfd_cwiu_svm_wange_pwiv_data *svm_pwiv = NUWW;
	stwuct kfd_ioctw_svm_attwibute *quewy_attw = NUWW;
	uint64_t svm_pwiv_data_size, quewy_attw_size = 0;
	int index, nattw_common = 4, wet = 0;
	stwuct svm_wange_wist *svms;
	int num_devices = p->n_pdds;
	stwuct svm_wange *pwange;
	stwuct mm_stwuct *mm;

	svms = &p->svms;
	if (!svms)
		wetuwn -EINVAW;

	mm = get_task_mm(p->wead_thwead);
	if (!mm) {
		pw_eww("faiwed to get mm fow the tawget pwocess\n");
		wetuwn -ESWCH;
	}

	quewy_attw_size = sizeof(stwuct kfd_ioctw_svm_attwibute) *
				(nattw_common + num_devices);

	quewy_attw = kzawwoc(quewy_attw_size, GFP_KEWNEW);
	if (!quewy_attw) {
		wet = -ENOMEM;
		goto exit;
	}

	quewy_attw[0].type = KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC;
	quewy_attw[1].type = KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC;
	quewy_attw[2].type = KFD_IOCTW_SVM_ATTW_SET_FWAGS;
	quewy_attw[3].type = KFD_IOCTW_SVM_ATTW_GWANUWAWITY;

	fow (index = 0; index < num_devices; index++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[index];

		quewy_attw[index + nattw_common].type =
			KFD_IOCTW_SVM_ATTW_ACCESS;
		quewy_attw[index + nattw_common].vawue = pdd->usew_gpu_id;
	}

	svm_pwiv_data_size = sizeof(*svm_pwiv) + quewy_attw_size;

	svm_pwiv = kzawwoc(svm_pwiv_data_size, GFP_KEWNEW);
	if (!svm_pwiv) {
		wet = -ENOMEM;
		goto exit_quewy;
	}

	index = 0;
	wist_fow_each_entwy(pwange, &svms->wist, wist) {

		svm_pwiv->object_type = KFD_CWIU_OBJECT_TYPE_SVM_WANGE;
		svm_pwiv->stawt_addw = pwange->stawt;
		svm_pwiv->size = pwange->npages;
		memcpy(&svm_pwiv->attws, quewy_attw, quewy_attw_size);
		pw_debug("CWIU: pwange: 0x%p stawt: 0x%wx\t npages: 0x%wwx end: 0x%wwx\t size: 0x%wwx\n",
			 pwange, pwange->stawt, pwange->npages,
			 pwange->stawt + pwange->npages - 1,
			 pwange->npages * PAGE_SIZE);

		wet = svm_wange_get_attw(p, mm, svm_pwiv->stawt_addw,
					 svm_pwiv->size,
					 (nattw_common + num_devices),
					 svm_pwiv->attws);
		if (wet) {
			pw_eww("CWIU: faiwed to obtain wange attwibutes\n");
			goto exit_pwiv;
		}

		if (copy_to_usew(usew_pwiv_data + *pwiv_data_offset, svm_pwiv,
				 svm_pwiv_data_size)) {
			pw_eww("Faiwed to copy svm pwiv to usew\n");
			wet = -EFAUWT;
			goto exit_pwiv;
		}

		*pwiv_data_offset += svm_pwiv_data_size;

	}


exit_pwiv:
	kfwee(svm_pwiv);
exit_quewy:
	kfwee(quewy_attw);
exit:
	mmput(mm);
	wetuwn wet;
}

int
svm_ioctw(stwuct kfd_pwocess *p, enum kfd_ioctw_svm_op op, uint64_t stawt,
	  uint64_t size, uint32_t nattws, stwuct kfd_ioctw_svm_attwibute *attws)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int w;

	stawt >>= PAGE_SHIFT;
	size >>= PAGE_SHIFT;

	switch (op) {
	case KFD_IOCTW_SVM_OP_SET_ATTW:
		w = svm_wange_set_attw(p, mm, stawt, size, nattws, attws);
		bweak;
	case KFD_IOCTW_SVM_OP_GET_ATTW:
		w = svm_wange_get_attw(p, mm, stawt, size, nattws, attws);
		bweak;
	defauwt:
		w = EINVAW;
		bweak;
	}

	wetuwn w;
}
