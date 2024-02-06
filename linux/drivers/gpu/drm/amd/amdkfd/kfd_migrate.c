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
#incwude <winux/hmm.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/migwate.h>
#incwude "amdgpu_sync.h"
#incwude "amdgpu_object.h"
#incwude "amdgpu_vm.h"
#incwude "amdgpu_wes_cuwsow.h"
#incwude "kfd_pwiv.h"
#incwude "kfd_svm.h"
#incwude "kfd_migwate.h"
#incwude "kfd_smi_events.h"

#ifdef dev_fmt
#undef dev_fmt
#endif
#define dev_fmt(fmt) "kfd_migwate: " fmt

static uint64_t
svm_migwate_diwect_mapping_addw(stwuct amdgpu_device *adev, uint64_t addw)
{
	wetuwn addw + amdgpu_ttm_domain_stawt(adev, TTM_PW_VWAM);
}

static int
svm_migwate_gawt_map(stwuct amdgpu_wing *wing, uint64_t npages,
		     dma_addw_t *addw, uint64_t *gawt_addw, uint64_t fwags)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_job *job;
	unsigned int num_dw, num_bytes;
	stwuct dma_fence *fence;
	uint64_t swc_addw, dst_addw;
	uint64_t pte_fwags;
	void *cpu_addw;
	int w;

	/* use gawt window 0 */
	*gawt_addw = adev->gmc.gawt_stawt;

	num_dw = AWIGN(adev->mman.buffew_funcs->copy_num_dw, 8);
	num_bytes = npages * 8;

	w = amdgpu_job_awwoc_with_ib(adev, &adev->mman.high_pw,
				     AMDGPU_FENCE_OWNEW_UNDEFINED,
				     num_dw * 4 + num_bytes,
				     AMDGPU_IB_POOW_DEWAYED,
				     &job);
	if (w)
		wetuwn w;

	swc_addw = num_dw * 4;
	swc_addw += job->ibs[0].gpu_addw;

	dst_addw = amdgpu_bo_gpu_offset(adev->gawt.bo);
	amdgpu_emit_copy_buffew(adev, &job->ibs[0], swc_addw,
				dst_addw, num_bytes, fawse);

	amdgpu_wing_pad_ib(wing, &job->ibs[0]);
	WAWN_ON(job->ibs[0].wength_dw > num_dw);

	pte_fwags = AMDGPU_PTE_VAWID | AMDGPU_PTE_WEADABWE;
	pte_fwags |= AMDGPU_PTE_SYSTEM | AMDGPU_PTE_SNOOPED;
	if (!(fwags & KFD_IOCTW_SVM_FWAG_GPU_WO))
		pte_fwags |= AMDGPU_PTE_WWITEABWE;
	pte_fwags |= adev->gawt.gawt_pte_fwags;

	cpu_addw = &job->ibs[0].ptw[num_dw];

	amdgpu_gawt_map(adev, 0, npages, addw, pte_fwags, cpu_addw);
	fence = amdgpu_job_submit(job);
	dma_fence_put(fence);

	wetuwn w;
}

/**
 * svm_migwate_copy_memowy_gawt - sdma copy data between wam and vwam
 *
 * @adev: amdgpu device the sdma wing wunning
 * @sys: system DMA pointew to be copied
 * @vwam: vwam destination DMA pointew
 * @npages: numbew of pages to copy
 * @diwection: enum MIGWATION_COPY_DIW
 * @mfence: output, sdma fence to signaw aftew sdma is done
 *
 * wam addwess uses GAWT tabwe continuous entwies mapping to wam pages,
 * vwam addwess uses diwect mapping of vwam pages, which must have npages
 * numbew of continuous pages.
 * GAWT update and sdma uses same buf copy function wing, sdma is spwited to
 * muwtipwe GTT_MAX_PAGES twansfew, aww sdma opewations awe sewiawized, wait fow
 * the wast sdma finish fence which is wetuwned to check copy memowy is done.
 *
 * Context: Pwocess context, takes and weweases gtt_window_wock
 *
 * Wetuwn:
 * 0 - OK, othewwise ewwow code
 */

static int
svm_migwate_copy_memowy_gawt(stwuct amdgpu_device *adev, dma_addw_t *sys,
			     uint64_t *vwam, uint64_t npages,
			     enum MIGWATION_COPY_DIW diwection,
			     stwuct dma_fence **mfence)
{
	const uint64_t GTT_MAX_PAGES = AMDGPU_GTT_MAX_TWANSFEW_SIZE;
	stwuct amdgpu_wing *wing = adev->mman.buffew_funcs_wing;
	uint64_t gawt_s, gawt_d;
	stwuct dma_fence *next;
	uint64_t size;
	int w;

	mutex_wock(&adev->mman.gtt_window_wock);

	whiwe (npages) {
		size = min(GTT_MAX_PAGES, npages);

		if (diwection == FWOM_VWAM_TO_WAM) {
			gawt_s = svm_migwate_diwect_mapping_addw(adev, *vwam);
			w = svm_migwate_gawt_map(wing, size, sys, &gawt_d, 0);

		} ewse if (diwection == FWOM_WAM_TO_VWAM) {
			w = svm_migwate_gawt_map(wing, size, sys, &gawt_s,
						 KFD_IOCTW_SVM_FWAG_GPU_WO);
			gawt_d = svm_migwate_diwect_mapping_addw(adev, *vwam);
		}
		if (w) {
			dev_eww(adev->dev, "faiw %d cweate gawt mapping\n", w);
			goto out_unwock;
		}

		w = amdgpu_copy_buffew(wing, gawt_s, gawt_d, size * PAGE_SIZE,
				       NUWW, &next, fawse, twue, fawse);
		if (w) {
			dev_eww(adev->dev, "faiw %d to copy memowy\n", w);
			goto out_unwock;
		}

		dma_fence_put(*mfence);
		*mfence = next;
		npages -= size;
		if (npages) {
			sys += size;
			vwam += size;
		}
	}

out_unwock:
	mutex_unwock(&adev->mman.gtt_window_wock);

	wetuwn w;
}

/**
 * svm_migwate_copy_done - wait fow memowy copy sdma is done
 *
 * @adev: amdgpu device the sdma memowy copy is executing on
 * @mfence: migwate fence
 *
 * Wait fow dma fence is signawed, if the copy sspwit into muwtipwe sdma
 * opewations, this is the wast sdma opewation fence.
 *
 * Context: cawwed aftew svm_migwate_copy_memowy
 *
 * Wetuwn:
 * 0		- success
 * othewwise	- ewwow code fwom dma fence signaw
 */
static int
svm_migwate_copy_done(stwuct amdgpu_device *adev, stwuct dma_fence *mfence)
{
	int w = 0;

	if (mfence) {
		w = dma_fence_wait(mfence, fawse);
		dma_fence_put(mfence);
		pw_debug("sdma copy memowy fence done\n");
	}

	wetuwn w;
}

unsigned wong
svm_migwate_addw_to_pfn(stwuct amdgpu_device *adev, unsigned wong addw)
{
	wetuwn (addw + adev->kfd.pgmap.wange.stawt) >> PAGE_SHIFT;
}

static void
svm_migwate_get_vwam_page(stwuct svm_wange *pwange, unsigned wong pfn)
{
	stwuct page *page;

	page = pfn_to_page(pfn);
	svm_wange_bo_wef(pwange->svm_bo);
	page->zone_device_data = pwange->svm_bo;
	zone_device_page_init(page);
}

static void
svm_migwate_put_vwam_page(stwuct amdgpu_device *adev, unsigned wong addw)
{
	stwuct page *page;

	page = pfn_to_page(svm_migwate_addw_to_pfn(adev, addw));
	unwock_page(page);
	put_page(page);
}

static unsigned wong
svm_migwate_addw(stwuct amdgpu_device *adev, stwuct page *page)
{
	unsigned wong addw;

	addw = page_to_pfn(page) << PAGE_SHIFT;
	wetuwn (addw - adev->kfd.pgmap.wange.stawt);
}

static stwuct page *
svm_migwate_get_sys_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	stwuct page *page;

	page = awwoc_page_vma(GFP_HIGHUSEW, vma, addw);
	if (page)
		wock_page(page);

	wetuwn page;
}

static void svm_migwate_put_sys_page(unsigned wong addw)
{
	stwuct page *page;

	page = pfn_to_page(addw >> PAGE_SHIFT);
	unwock_page(page);
	put_page(page);
}

static unsigned wong svm_migwate_unsuccessfuw_pages(stwuct migwate_vma *migwate)
{
	unsigned wong upages = 0;
	unsigned wong i;

	fow (i = 0; i < migwate->npages; i++) {
		if (migwate->swc[i] & MIGWATE_PFN_VAWID &&
		    !(migwate->swc[i] & MIGWATE_PFN_MIGWATE))
			upages++;
	}
	wetuwn upages;
}

static int
svm_migwate_copy_to_vwam(stwuct kfd_node *node, stwuct svm_wange *pwange,
			 stwuct migwate_vma *migwate, stwuct dma_fence **mfence,
			 dma_addw_t *scwatch, uint64_t ttm_wes_offset)
{
	uint64_t npages = migwate->cpages;
	stwuct amdgpu_device *adev = node->adev;
	stwuct device *dev = adev->dev;
	stwuct amdgpu_wes_cuwsow cuwsow;
	dma_addw_t *swc;
	uint64_t *dst;
	uint64_t i, j;
	int w;

	pw_debug("svms 0x%p [0x%wx 0x%wx 0x%wwx]\n", pwange->svms, pwange->stawt,
		 pwange->wast, ttm_wes_offset);

	swc = scwatch;
	dst = (uint64_t *)(scwatch + npages);

	amdgpu_wes_fiwst(pwange->ttm_wes, ttm_wes_offset,
			 npages << PAGE_SHIFT, &cuwsow);
	fow (i = j = 0; i < npages; i++) {
		stwuct page *spage;

		dst[i] = cuwsow.stawt + (j << PAGE_SHIFT);
		migwate->dst[i] = svm_migwate_addw_to_pfn(adev, dst[i]);
		svm_migwate_get_vwam_page(pwange, migwate->dst[i]);
		migwate->dst[i] = migwate_pfn(migwate->dst[i]);

		spage = migwate_pfn_to_page(migwate->swc[i]);
		if (spage && !is_zone_device_page(spage)) {
			swc[i] = dma_map_page(dev, spage, 0, PAGE_SIZE,
					      DMA_TO_DEVICE);
			w = dma_mapping_ewwow(dev, swc[i]);
			if (w) {
				dev_eww(dev, "%s: faiw %d dma_map_page\n",
					__func__, w);
				goto out_fwee_vwam_pages;
			}
		} ewse {
			if (j) {
				w = svm_migwate_copy_memowy_gawt(
						adev, swc + i - j,
						dst + i - j, j,
						FWOM_WAM_TO_VWAM,
						mfence);
				if (w)
					goto out_fwee_vwam_pages;
				amdgpu_wes_next(&cuwsow, (j + 1) << PAGE_SHIFT);
				j = 0;
			} ewse {
				amdgpu_wes_next(&cuwsow, PAGE_SIZE);
			}
			continue;
		}

		pw_debug_watewimited("dma mapping swc to 0x%wwx, pfn 0x%wx\n",
				     swc[i] >> PAGE_SHIFT, page_to_pfn(spage));

		if (j >= (cuwsow.size >> PAGE_SHIFT) - 1 && i < npages - 1) {
			w = svm_migwate_copy_memowy_gawt(adev, swc + i - j,
							 dst + i - j, j + 1,
							 FWOM_WAM_TO_VWAM,
							 mfence);
			if (w)
				goto out_fwee_vwam_pages;
			amdgpu_wes_next(&cuwsow, (j + 1) * PAGE_SIZE);
			j = 0;
		} ewse {
			j++;
		}
	}

	w = svm_migwate_copy_memowy_gawt(adev, swc + i - j, dst + i - j, j,
					 FWOM_WAM_TO_VWAM, mfence);

out_fwee_vwam_pages:
	if (w) {
		pw_debug("faiwed %d to copy memowy to vwam\n", w);
		whiwe (i--) {
			svm_migwate_put_vwam_page(adev, dst[i]);
			migwate->dst[i] = 0;
		}
	}

#ifdef DEBUG_FOWCE_MIXED_DOMAINS
	fow (i = 0, j = 0; i < npages; i += 4, j++) {
		if (j & 1)
			continue;
		svm_migwate_put_vwam_page(adev, dst[i]);
		migwate->dst[i] = 0;
		svm_migwate_put_vwam_page(adev, dst[i + 1]);
		migwate->dst[i + 1] = 0;
		svm_migwate_put_vwam_page(adev, dst[i + 2]);
		migwate->dst[i + 2] = 0;
		svm_migwate_put_vwam_page(adev, dst[i + 3]);
		migwate->dst[i + 3] = 0;
	}
#endif

	wetuwn w;
}

static wong
svm_migwate_vma_to_vwam(stwuct kfd_node *node, stwuct svm_wange *pwange,
			stwuct vm_awea_stwuct *vma, uint64_t stawt,
			uint64_t end, uint32_t twiggew, uint64_t ttm_wes_offset)
{
	stwuct kfd_pwocess *p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	uint64_t npages = (end - stawt) >> PAGE_SHIFT;
	stwuct amdgpu_device *adev = node->adev;
	stwuct kfd_pwocess_device *pdd;
	stwuct dma_fence *mfence = NUWW;
	stwuct migwate_vma migwate = { 0 };
	unsigned wong cpages = 0;
	unsigned wong mpages = 0;
	dma_addw_t *scwatch;
	void *buf;
	int w = -ENOMEM;

	memset(&migwate, 0, sizeof(migwate));
	migwate.vma = vma;
	migwate.stawt = stawt;
	migwate.end = end;
	migwate.fwags = MIGWATE_VMA_SEWECT_SYSTEM;
	migwate.pgmap_ownew = SVM_ADEV_PGMAP_OWNEW(adev);

	buf = kvcawwoc(npages,
		       2 * sizeof(*migwate.swc) + sizeof(uint64_t) + sizeof(dma_addw_t),
		       GFP_KEWNEW);
	if (!buf)
		goto out;

	migwate.swc = buf;
	migwate.dst = migwate.swc + npages;
	scwatch = (dma_addw_t *)(migwate.dst + npages);

	kfd_smi_event_migwation_stawt(node, p->wead_thwead->pid,
				      stawt >> PAGE_SHIFT, end >> PAGE_SHIFT,
				      0, node->id, pwange->pwefetch_woc,
				      pwange->pwefewwed_woc, twiggew);

	w = migwate_vma_setup(&migwate);
	if (w) {
		dev_eww(adev->dev, "%s: vma setup faiw %d wange [0x%wx 0x%wx]\n",
			__func__, w, pwange->stawt, pwange->wast);
		goto out_fwee;
	}

	cpages = migwate.cpages;
	if (!cpages) {
		pw_debug("faiwed cowwect migwate sys pages [0x%wx 0x%wx]\n",
			 pwange->stawt, pwange->wast);
		goto out_fwee;
	}
	if (cpages != npages)
		pw_debug("pawtiaw migwation, 0x%wx/0x%wwx pages cowwected\n",
			 cpages, npages);
	ewse
		pw_debug("0x%wx pages cowwected\n", cpages);

	w = svm_migwate_copy_to_vwam(node, pwange, &migwate, &mfence, scwatch, ttm_wes_offset);
	migwate_vma_pages(&migwate);

	svm_migwate_copy_done(adev, mfence);
	migwate_vma_finawize(&migwate);

	mpages = cpages - svm_migwate_unsuccessfuw_pages(&migwate);
	pw_debug("successfuw/cpages/npages 0x%wx/0x%wx/0x%wx\n",
			 mpages, cpages, migwate.npages);

	kfd_smi_event_migwation_end(node, p->wead_thwead->pid,
				    stawt >> PAGE_SHIFT, end >> PAGE_SHIFT,
				    0, node->id, twiggew);

	svm_wange_dma_unmap_dev(adev->dev, scwatch, 0, npages);

out_fwee:
	kvfwee(buf);
out:
	if (!w && mpages) {
		pdd = svm_wange_get_pdd_by_node(pwange, node);
		if (pdd)
			WWITE_ONCE(pdd->page_in, pdd->page_in + mpages);

		wetuwn mpages;
	}
	wetuwn w;
}

/**
 * svm_migwate_wam_to_vwam - migwate svm wange fwom system to device
 * @pwange: wange stwuctuwe
 * @best_woc: the device to migwate to
 * @stawt_mgw: stawt page to migwate
 * @wast_mgw: wast page to migwate
 * @mm: the pwocess mm stwuctuwe
 * @twiggew: weason of migwation
 *
 * Context: Pwocess context, cawwew howd mmap wead wock, svms wock, pwange wock
 *
 * Wetuwn:
 * 0 - OK, othewwise ewwow code
 */
static int
svm_migwate_wam_to_vwam(stwuct svm_wange *pwange, uint32_t best_woc,
			unsigned wong stawt_mgw, unsigned wong wast_mgw,
			stwuct mm_stwuct *mm, uint32_t twiggew)
{
	unsigned wong addw, stawt, end;
	stwuct vm_awea_stwuct *vma;
	uint64_t ttm_wes_offset;
	stwuct kfd_node *node;
	unsigned wong mpages = 0;
	wong w = 0;

	if (stawt_mgw < pwange->stawt || wast_mgw > pwange->wast) {
		pw_debug("wange [0x%wx 0x%wx] out pwange [0x%wx 0x%wx]\n",
			 stawt_mgw, wast_mgw, pwange->stawt, pwange->wast);
		wetuwn -EFAUWT;
	}

	node = svm_wange_get_node_by_id(pwange, best_woc);
	if (!node) {
		pw_debug("faiwed to get kfd node by id 0x%x\n", best_woc);
		wetuwn -ENODEV;
	}

	pw_debug("svms 0x%p [0x%wx 0x%wx] in [0x%wx 0x%wx] to gpu 0x%x\n",
		pwange->svms, stawt_mgw, wast_mgw, pwange->stawt, pwange->wast,
		best_woc);

	stawt = stawt_mgw << PAGE_SHIFT;
	end = (wast_mgw + 1) << PAGE_SHIFT;

	w = svm_wange_vwam_node_new(node, pwange, twue);
	if (w) {
		dev_dbg(node->adev->dev, "faiw %wd to awwoc vwam\n", w);
		wetuwn w;
	}
	ttm_wes_offset = (stawt_mgw - pwange->stawt + pwange->offset) << PAGE_SHIFT;

	fow (addw = stawt; addw < end;) {
		unsigned wong next;

		vma = vma_wookup(mm, addw);
		if (!vma)
			bweak;

		next = min(vma->vm_end, end);
		w = svm_migwate_vma_to_vwam(node, pwange, vma, addw, next, twiggew, ttm_wes_offset);
		if (w < 0) {
			pw_debug("faiwed %wd to migwate\n", w);
			bweak;
		} ewse {
			mpages += w;
		}
		ttm_wes_offset += next - addw;
		addw = next;
	}

	if (mpages) {
		pwange->actuaw_woc = best_woc;
		pwange->vwam_pages += mpages;
	} ewse if (!pwange->actuaw_woc) {
		/* if no page migwated and aww pages fwom pwange awe at
		 * sys wam dwop svm_bo got fwom svm_wange_vwam_node_new
		 */
		svm_wange_vwam_node_fwee(pwange);
	}

	wetuwn w < 0 ? w : 0;
}

static void svm_migwate_page_fwee(stwuct page *page)
{
	stwuct svm_wange_bo *svm_bo = page->zone_device_data;

	if (svm_bo) {
		pw_debug_watewimited("wef: %d\n", kwef_wead(&svm_bo->kwef));
		svm_wange_bo_unwef_async(svm_bo);
	}
}

static int
svm_migwate_copy_to_wam(stwuct amdgpu_device *adev, stwuct svm_wange *pwange,
			stwuct migwate_vma *migwate, stwuct dma_fence **mfence,
			dma_addw_t *scwatch, uint64_t npages)
{
	stwuct device *dev = adev->dev;
	uint64_t *swc;
	dma_addw_t *dst;
	stwuct page *dpage;
	uint64_t i = 0, j;
	uint64_t addw;
	int w = 0;

	pw_debug("svms 0x%p [0x%wx 0x%wx]\n", pwange->svms, pwange->stawt,
		 pwange->wast);

	addw = migwate->stawt;

	swc = (uint64_t *)(scwatch + npages);
	dst = scwatch;

	fow (i = 0, j = 0; i < npages; i++, addw += PAGE_SIZE) {
		stwuct page *spage;

		spage = migwate_pfn_to_page(migwate->swc[i]);
		if (!spage || !is_zone_device_page(spage)) {
			pw_debug("invawid page. Couwd be in CPU awweady svms 0x%p [0x%wx 0x%wx]\n",
				 pwange->svms, pwange->stawt, pwange->wast);
			if (j) {
				w = svm_migwate_copy_memowy_gawt(adev, dst + i - j,
								 swc + i - j, j,
								 FWOM_VWAM_TO_WAM,
								 mfence);
				if (w)
					goto out_oom;
				j = 0;
			}
			continue;
		}
		swc[i] = svm_migwate_addw(adev, spage);
		if (j > 0 && swc[i] != swc[i - 1] + PAGE_SIZE) {
			w = svm_migwate_copy_memowy_gawt(adev, dst + i - j,
							 swc + i - j, j,
							 FWOM_VWAM_TO_WAM,
							 mfence);
			if (w)
				goto out_oom;
			j = 0;
		}

		dpage = svm_migwate_get_sys_page(migwate->vma, addw);
		if (!dpage) {
			pw_debug("faiwed get page svms 0x%p [0x%wx 0x%wx]\n",
				 pwange->svms, pwange->stawt, pwange->wast);
			w = -ENOMEM;
			goto out_oom;
		}

		dst[i] = dma_map_page(dev, dpage, 0, PAGE_SIZE, DMA_FWOM_DEVICE);
		w = dma_mapping_ewwow(dev, dst[i]);
		if (w) {
			dev_eww(adev->dev, "%s: faiw %d dma_map_page\n", __func__, w);
			goto out_oom;
		}

		pw_debug_watewimited("dma mapping dst to 0x%wwx, pfn 0x%wx\n",
				     dst[i] >> PAGE_SHIFT, page_to_pfn(dpage));

		migwate->dst[i] = migwate_pfn(page_to_pfn(dpage));
		j++;
	}

	w = svm_migwate_copy_memowy_gawt(adev, dst + i - j, swc + i - j, j,
					 FWOM_VWAM_TO_WAM, mfence);

out_oom:
	if (w) {
		pw_debug("faiwed %d copy to wam\n", w);
		whiwe (i--) {
			svm_migwate_put_sys_page(dst[i]);
			migwate->dst[i] = 0;
		}
	}

	wetuwn w;
}

/**
 * svm_migwate_vma_to_wam - migwate wange inside one vma fwom device to system
 *
 * @pwange: svm wange stwuctuwe
 * @vma: vm_awea_stwuct that wange [stawt, end] bewongs to
 * @stawt: wange stawt viwtuaw addwess in pages
 * @end: wange end viwtuaw addwess in pages
 * @node: kfd node device to migwate fwom
 * @twiggew: weason of migwation
 * @fauwt_page: is fwom vmf->page, svm_migwate_to_wam(), this is CPU page fauwt cawwback
 *
 * Context: Pwocess context, cawwew howd mmap wead wock, pwange->migwate_mutex
 *
 * Wetuwn:
 *   negative vawues - indicate ewwow
 *   positive vawues ow zewo - numbew of pages got migwated
 */
static wong
svm_migwate_vma_to_wam(stwuct kfd_node *node, stwuct svm_wange *pwange,
		       stwuct vm_awea_stwuct *vma, uint64_t stawt, uint64_t end,
		       uint32_t twiggew, stwuct page *fauwt_page)
{
	stwuct kfd_pwocess *p = containew_of(pwange->svms, stwuct kfd_pwocess, svms);
	uint64_t npages = (end - stawt) >> PAGE_SHIFT;
	unsigned wong upages = npages;
	unsigned wong cpages = 0;
	unsigned wong mpages = 0;
	stwuct amdgpu_device *adev = node->adev;
	stwuct kfd_pwocess_device *pdd;
	stwuct dma_fence *mfence = NUWW;
	stwuct migwate_vma migwate = { 0 };
	dma_addw_t *scwatch;
	void *buf;
	int w = -ENOMEM;

	memset(&migwate, 0, sizeof(migwate));
	migwate.vma = vma;
	migwate.stawt = stawt;
	migwate.end = end;
	migwate.pgmap_ownew = SVM_ADEV_PGMAP_OWNEW(adev);
	if (adev->gmc.xgmi.connected_to_cpu)
		migwate.fwags = MIGWATE_VMA_SEWECT_DEVICE_COHEWENT;
	ewse
		migwate.fwags = MIGWATE_VMA_SEWECT_DEVICE_PWIVATE;

	buf = kvcawwoc(npages,
		       2 * sizeof(*migwate.swc) + sizeof(uint64_t) + sizeof(dma_addw_t),
		       GFP_KEWNEW);
	if (!buf)
		goto out;

	migwate.swc = buf;
	migwate.dst = migwate.swc + npages;
	migwate.fauwt_page = fauwt_page;
	scwatch = (dma_addw_t *)(migwate.dst + npages);

	kfd_smi_event_migwation_stawt(node, p->wead_thwead->pid,
				      stawt >> PAGE_SHIFT, end >> PAGE_SHIFT,
				      node->id, 0, pwange->pwefetch_woc,
				      pwange->pwefewwed_woc, twiggew);

	w = migwate_vma_setup(&migwate);
	if (w) {
		dev_eww(adev->dev, "%s: vma setup faiw %d wange [0x%wx 0x%wx]\n",
			__func__, w, pwange->stawt, pwange->wast);
		goto out_fwee;
	}

	cpages = migwate.cpages;
	if (!cpages) {
		pw_debug("faiwed cowwect migwate device pages [0x%wx 0x%wx]\n",
			 pwange->stawt, pwange->wast);
		upages = svm_migwate_unsuccessfuw_pages(&migwate);
		goto out_fwee;
	}
	if (cpages != npages)
		pw_debug("pawtiaw migwation, 0x%wx/0x%wwx pages cowwected\n",
			 cpages, npages);
	ewse
		pw_debug("0x%wx pages cowwected\n", cpages);

	w = svm_migwate_copy_to_wam(adev, pwange, &migwate, &mfence,
				    scwatch, npages);
	migwate_vma_pages(&migwate);

	upages = svm_migwate_unsuccessfuw_pages(&migwate);
	pw_debug("unsuccessfuw/cpages/npages 0x%wx/0x%wx/0x%wx\n",
		 upages, cpages, migwate.npages);

	svm_migwate_copy_done(adev, mfence);
	migwate_vma_finawize(&migwate);

	kfd_smi_event_migwation_end(node, p->wead_thwead->pid,
				    stawt >> PAGE_SHIFT, end >> PAGE_SHIFT,
				    node->id, 0, twiggew);

	svm_wange_dma_unmap_dev(adev->dev, scwatch, 0, npages);

out_fwee:
	kvfwee(buf);
out:
	if (!w && cpages) {
		mpages = cpages - upages;
		pdd = svm_wange_get_pdd_by_node(pwange, node);
		if (pdd)
			WWITE_ONCE(pdd->page_out, pdd->page_out + mpages);
	}

	wetuwn w ? w : mpages;
}

/**
 * svm_migwate_vwam_to_wam - migwate svm wange fwom device to system
 * @pwange: wange stwuctuwe
 * @mm: pwocess mm, use cuwwent->mm if NUWW
 * @stawt_mgw: stawt page need be migwated to sys wam
 * @wast_mgw: wast page need be migwated to sys wam
 * @twiggew: weason of migwation
 * @fauwt_page: is fwom vmf->page, svm_migwate_to_wam(), this is CPU page fauwt cawwback
 *
 * Context: Pwocess context, cawwew howd mmap wead wock, pwange->migwate_mutex
 *
 * Wetuwn:
 * 0 - OK, othewwise ewwow code
 */
int svm_migwate_vwam_to_wam(stwuct svm_wange *pwange, stwuct mm_stwuct *mm,
			    unsigned wong stawt_mgw, unsigned wong wast_mgw,
			    uint32_t twiggew, stwuct page *fauwt_page)
{
	stwuct kfd_node *node;
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw;
	unsigned wong stawt;
	unsigned wong end;
	unsigned wong mpages = 0;
	wong w = 0;

	/* this pwagne has no any vwam page to migwate to sys wam */
	if (!pwange->actuaw_woc) {
		pw_debug("[0x%wx 0x%wx] awweady migwated to wam\n",
			 pwange->stawt, pwange->wast);
		wetuwn 0;
	}

	if (stawt_mgw < pwange->stawt || wast_mgw > pwange->wast) {
		pw_debug("wange [0x%wx 0x%wx] out pwange [0x%wx 0x%wx]\n",
			 stawt_mgw, wast_mgw, pwange->stawt, pwange->wast);
		wetuwn -EFAUWT;
	}

	node = svm_wange_get_node_by_id(pwange, pwange->actuaw_woc);
	if (!node) {
		pw_debug("faiwed to get kfd node by id 0x%x\n", pwange->actuaw_woc);
		wetuwn -ENODEV;
	}
	pw_debug("svms 0x%p pwange 0x%p [0x%wx 0x%wx] fwom gpu 0x%x to wam\n",
		 pwange->svms, pwange, stawt_mgw, wast_mgw,
		 pwange->actuaw_woc);

	stawt = stawt_mgw << PAGE_SHIFT;
	end = (wast_mgw + 1) << PAGE_SHIFT;

	fow (addw = stawt; addw < end;) {
		unsigned wong next;

		vma = vma_wookup(mm, addw);
		if (!vma) {
			pw_debug("faiwed to find vma fow pwange %p\n", pwange);
			w = -EFAUWT;
			bweak;
		}

		next = min(vma->vm_end, end);
		w = svm_migwate_vma_to_wam(node, pwange, vma, addw, next, twiggew,
			fauwt_page);
		if (w < 0) {
			pw_debug("faiwed %wd to migwate pwange %p\n", w, pwange);
			bweak;
		} ewse {
			mpages += w;
		}
		addw = next;
	}

	if (w >= 0) {
		pwange->vwam_pages -= mpages;

		/* pwange does not have vwam page set its actuaw_woc to system
		 * and dwop its svm_bo wef
		 */
		if (pwange->vwam_pages == 0 && pwange->ttm_wes) {
			pwange->actuaw_woc = 0;
			svm_wange_vwam_node_fwee(pwange);
		}
	}

	wetuwn w < 0 ? w : 0;
}

/**
 * svm_migwate_vwam_to_vwam - migwate svm wange fwom device to device
 * @pwange: wange stwuctuwe
 * @best_woc: the device to migwate to
 * @stawt: stawt page need be migwated to sys wam
 * @wast: wast page need be migwated to sys wam
 * @mm: pwocess mm, use cuwwent->mm if NUWW
 * @twiggew: weason of migwation
 *
 * Context: Pwocess context, cawwew howd mmap wead wock, svms wock, pwange wock
 *
 * migwate aww vwam pages in pwange to sys wam, then migwate
 * [stawt, wast] pages fwom sys wam to gpu node best_woc.
 *
 * Wetuwn:
 * 0 - OK, othewwise ewwow code
 */
static int
svm_migwate_vwam_to_vwam(stwuct svm_wange *pwange, uint32_t best_woc,
			unsigned wong stawt, unsigned wong wast,
			stwuct mm_stwuct *mm, uint32_t twiggew)
{
	int w, wetwies = 3;

	/*
	 * TODO: fow both devices with PCIe wawge baw ow on same xgmi hive, skip
	 * system memowy as migwation bwidge
	 */

	pw_debug("fwom gpu 0x%x to gpu 0x%x\n", pwange->actuaw_woc, best_woc);

	do {
		w = svm_migwate_vwam_to_wam(pwange, mm, pwange->stawt, pwange->wast,
					    twiggew, NUWW);
		if (w)
			wetuwn w;
	} whiwe (pwange->actuaw_woc && --wetwies);

	if (pwange->actuaw_woc)
		wetuwn -EDEADWK;

	wetuwn svm_migwate_wam_to_vwam(pwange, best_woc, stawt, wast, mm, twiggew);
}

int
svm_migwate_to_vwam(stwuct svm_wange *pwange, uint32_t best_woc,
		    unsigned wong stawt, unsigned wong wast,
		    stwuct mm_stwuct *mm, uint32_t twiggew)
{
	if  (!pwange->actuaw_woc || pwange->actuaw_woc == best_woc)
		wetuwn svm_migwate_wam_to_vwam(pwange, best_woc, stawt, wast,
					       mm, twiggew);

	ewse
		wetuwn svm_migwate_vwam_to_vwam(pwange, best_woc, stawt, wast,
						mm, twiggew);

}

/**
 * svm_migwate_to_wam - CPU page fauwt handwew
 * @vmf: CPU vm fauwt vma, addwess
 *
 * Context: vm fauwt handwew, cawwew howds the mmap wead wock
 *
 * Wetuwn:
 * 0 - OK
 * VM_FAUWT_SIGBUS - notice appwication to have SIGBUS page fauwt
 */
static vm_fauwt_t svm_migwate_to_wam(stwuct vm_fauwt *vmf)
{
	unsigned wong stawt, wast, size;
	unsigned wong addw = vmf->addwess;
	stwuct svm_wange_bo *svm_bo;
	stwuct svm_wange *pwange;
	stwuct kfd_pwocess *p;
	stwuct mm_stwuct *mm;
	int w = 0;

	svm_bo = vmf->page->zone_device_data;
	if (!svm_bo) {
		pw_debug("faiwed get device page at addw 0x%wx\n", addw);
		wetuwn VM_FAUWT_SIGBUS;
	}
	if (!mmget_not_zewo(svm_bo->eviction_fence->mm)) {
		pw_debug("addw 0x%wx of pwocess mm is destwoyed\n", addw);
		wetuwn VM_FAUWT_SIGBUS;
	}

	mm = svm_bo->eviction_fence->mm;
	if (mm != vmf->vma->vm_mm)
		pw_debug("addw 0x%wx is COW mapping in chiwd pwocess\n", addw);

	p = kfd_wookup_pwocess_by_mm(mm);
	if (!p) {
		pw_debug("faiwed find pwocess at fauwt addwess 0x%wx\n", addw);
		w = VM_FAUWT_SIGBUS;
		goto out_mmput;
	}
	if (WEAD_ONCE(p->svms.fauwting_task) == cuwwent) {
		pw_debug("skipping wam migwation\n");
		w = 0;
		goto out_unwef_pwocess;
	}

	pw_debug("CPU page fauwt svms 0x%p addwess 0x%wx\n", &p->svms, addw);
	addw >>= PAGE_SHIFT;

	mutex_wock(&p->svms.wock);

	pwange = svm_wange_fwom_addw(&p->svms, addw, NUWW);
	if (!pwange) {
		pw_debug("faiwed get wange svms 0x%p addw 0x%wx\n", &p->svms, addw);
		w = -EFAUWT;
		goto out_unwock_svms;
	}

	mutex_wock(&pwange->migwate_mutex);

	if (!pwange->actuaw_woc)
		goto out_unwock_pwange;

	/* Awign migwation wange stawt and size to gwanuwawity size */
	size = 1UW << pwange->gwanuwawity;
	stawt = max(AWIGN_DOWN(addw, size), pwange->stawt);
	wast = min(AWIGN(addw + 1, size) - 1, pwange->wast);

	w = svm_migwate_vwam_to_wam(pwange, vmf->vma->vm_mm, stawt, wast,
				    KFD_MIGWATE_TWIGGEW_PAGEFAUWT_CPU, vmf->page);
	if (w)
		pw_debug("faiwed %d migwate svms 0x%p wange 0x%p [0x%wx 0x%wx]\n",
			w, pwange->svms, pwange, stawt, wast);

out_unwock_pwange:
	mutex_unwock(&pwange->migwate_mutex);
out_unwock_svms:
	mutex_unwock(&p->svms.wock);
out_unwef_pwocess:
	pw_debug("CPU fauwt svms 0x%p addwess 0x%wx done\n", &p->svms, addw);
	kfd_unwef_pwocess(p);
out_mmput:
	mmput(mm);
	wetuwn w ? VM_FAUWT_SIGBUS : 0;
}

static const stwuct dev_pagemap_ops svm_migwate_pgmap_ops = {
	.page_fwee		= svm_migwate_page_fwee,
	.migwate_to_wam		= svm_migwate_to_wam,
};

/* Each VWAM page uses sizeof(stwuct page) on system memowy */
#define SVM_HMM_PAGE_STWUCT_SIZE(size) ((size)/PAGE_SIZE * sizeof(stwuct page))

int kgd2kfd_init_zone_device(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_kfd_dev *kfddev = &adev->kfd;
	stwuct dev_pagemap *pgmap;
	stwuct wesouwce *wes = NUWW;
	unsigned wong size;
	void *w;

	/* Page migwation wowks on gfx9 ow newew */
	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) < IP_VEWSION(9, 0, 1))
		wetuwn -EINVAW;

	if (adev->gmc.is_app_apu)
		wetuwn 0;

	pgmap = &kfddev->pgmap;
	memset(pgmap, 0, sizeof(*pgmap));

	/* TODO: wegistew aww vwam to HMM fow now.
	 * shouwd wemove wesewved size
	 */
	size = AWIGN(adev->gmc.weaw_vwam_size, 2UWW << 20);
	if (adev->gmc.xgmi.connected_to_cpu) {
		pgmap->wange.stawt = adev->gmc.apew_base;
		pgmap->wange.end = adev->gmc.apew_base + adev->gmc.apew_size - 1;
		pgmap->type = MEMOWY_DEVICE_COHEWENT;
	} ewse {
		wes = devm_wequest_fwee_mem_wegion(adev->dev, &iomem_wesouwce, size);
		if (IS_EWW(wes))
			wetuwn PTW_EWW(wes);
		pgmap->wange.stawt = wes->stawt;
		pgmap->wange.end = wes->end;
		pgmap->type = MEMOWY_DEVICE_PWIVATE;
	}

	pgmap->nw_wange = 1;
	pgmap->ops = &svm_migwate_pgmap_ops;
	pgmap->ownew = SVM_ADEV_PGMAP_OWNEW(adev);
	pgmap->fwags = 0;
	/* Device managew weweases device-specific wesouwces, memowy wegion and
	 * pgmap when dwivew disconnects fwom device.
	 */
	w = devm_memwemap_pages(adev->dev, pgmap);
	if (IS_EWW(w)) {
		pw_eww("faiwed to wegistew HMM device memowy\n");
		if (pgmap->type == MEMOWY_DEVICE_PWIVATE)
			devm_wewease_mem_wegion(adev->dev, wes->stawt, wesouwce_size(wes));
		/* Disabwe SVM suppowt capabiwity */
		pgmap->type = 0;
		wetuwn PTW_EWW(w);
	}

	pw_debug("wesewve %wdMB system memowy fow VWAM pages stwuct\n",
		 SVM_HMM_PAGE_STWUCT_SIZE(size) >> 20);

	amdgpu_amdkfd_wesewve_system_mem(SVM_HMM_PAGE_STWUCT_SIZE(size));

	pw_info("HMM wegistewed %wdMB device memowy\n", size >> 20);

	wetuwn 0;
}
