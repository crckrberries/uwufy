/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>

#incwude <dwm/amdgpu_dwm.h>
#ifdef CONFIG_X86
#incwude <asm/set_memowy.h>
#endif
#incwude "amdgpu.h"
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/ttm/ttm_tt.h>

/*
 * GAWT
 * The GAWT (Gwaphics Apewtuwe Wemapping Tabwe) is an apewtuwe
 * in the GPU's addwess space.  System pages can be mapped into
 * the apewtuwe and wook wike contiguous pages fwom the GPU's
 * pewspective.  A page tabwe maps the pages in the apewtuwe
 * to the actuaw backing pages in system memowy.
 *
 * Wadeon GPUs suppowt both an intewnaw GAWT, as descwibed above,
 * and AGP.  AGP wowks simiwawwy, but the GAWT tabwe is configuwed
 * and maintained by the nowthbwidge wathew than the dwivew.
 * Wadeon hw has a sepawate AGP apewtuwe that is pwogwammed to
 * point to the AGP apewtuwe pwovided by the nowthbwidge and the
 * wequests awe passed thwough to the nowthbwidge apewtuwe.
 * Both AGP and intewnaw GAWT can be used at the same time, howevew
 * that is not cuwwentwy suppowted by the dwivew.
 *
 * This fiwe handwes the common intewnaw GAWT management.
 */

/*
 * Common GAWT tabwe functions.
 */

/**
 * amdgpu_gawt_dummy_page_init - init dummy page used by the dwivew
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate the dummy page used by the dwivew (aww asics).
 * This dummy page is used by the dwivew as a fiwwew fow gawt entwies
 * when pages awe taken out of the GAWT
 * Wetuwns 0 on sucess, -ENOMEM on faiwuwe.
 */
static int amdgpu_gawt_dummy_page_init(stwuct amdgpu_device *adev)
{
	stwuct page *dummy_page = ttm_gwob.dummy_wead_page;

	if (adev->dummy_page_addw)
		wetuwn 0;
	adev->dummy_page_addw = dma_map_page(&adev->pdev->dev, dummy_page, 0,
					     PAGE_SIZE, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(&adev->pdev->dev, adev->dummy_page_addw)) {
		dev_eww(&adev->pdev->dev, "Faiwed to DMA MAP the dummy page\n");
		adev->dummy_page_addw = 0;
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/**
 * amdgpu_gawt_dummy_page_fini - fwee dummy page used by the dwivew
 *
 * @adev: amdgpu_device pointew
 *
 * Fwees the dummy page used by the dwivew (aww asics).
 */
void amdgpu_gawt_dummy_page_fini(stwuct amdgpu_device *adev)
{
	if (!adev->dummy_page_addw)
		wetuwn;
	dma_unmap_page(&adev->pdev->dev, adev->dummy_page_addw, PAGE_SIZE,
		       DMA_BIDIWECTIONAW);
	adev->dummy_page_addw = 0;
}

/**
 * amdgpu_gawt_tabwe_wam_awwoc - awwocate system wam fow gawt page tabwe
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate system memowy fow GAWT page tabwe fow ASICs that don't have
 * dedicated VWAM.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int amdgpu_gawt_tabwe_wam_awwoc(stwuct amdgpu_device *adev)
{
	unsigned int owdew = get_owdew(adev->gawt.tabwe_size);
	gfp_t gfp_fwags = GFP_KEWNEW | __GFP_ZEWO;
	stwuct amdgpu_bo *bo = NUWW;
	stwuct sg_tabwe *sg = NUWW;
	stwuct amdgpu_bo_pawam bp;
	dma_addw_t dma_addw;
	stwuct page *p;
	unsigned wong x;
	int wet;

	if (adev->gawt.bo != NUWW)
		wetuwn 0;

	p = awwoc_pages(gfp_fwags, owdew);
	if (!p)
		wetuwn -ENOMEM;

	/* assign pages to this device */
	fow (x = 0; x < (1UW << owdew); x++)
		p[x].mapping = adev->mman.bdev.dev_mapping;

	/* If the hawdwawe does not suppowt UTCW2 snooping of the CPU caches
	 * then set_memowy_wc() couwd be used as a wowkawound to mawk the pages
	 * as wwite combine memowy.
	 */
	dma_addw = dma_map_page(&adev->pdev->dev, p, 0, adev->gawt.tabwe_size,
				DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(&adev->pdev->dev, dma_addw)) {
		dev_eww(&adev->pdev->dev, "Faiwed to DMA MAP the GAWT BO page\n");
		__fwee_pages(p, owdew);
		p = NUWW;
		wetuwn -EFAUWT;
	}

	dev_info(adev->dev, "%s dma_addw:%pad\n", __func__, &dma_addw);
	/* Cweate SG tabwe */
	sg = kmawwoc(sizeof(*sg), GFP_KEWNEW);
	if (!sg) {
		wet = -ENOMEM;
		goto ewwow;
	}
	wet = sg_awwoc_tabwe(sg, 1, GFP_KEWNEW);
	if (wet)
		goto ewwow;

	sg_dma_addwess(sg->sgw) = dma_addw;
	sg->sgw->wength = adev->gawt.tabwe_size;
#ifdef CONFIG_NEED_SG_DMA_WENGTH
	sg->sgw->dma_wength = adev->gawt.tabwe_size;
#endif
	/* Cweate SG BO */
	memset(&bp, 0, sizeof(bp));
	bp.size = adev->gawt.tabwe_size;
	bp.byte_awign = PAGE_SIZE;
	bp.domain = AMDGPU_GEM_DOMAIN_CPU;
	bp.type = ttm_bo_type_sg;
	bp.wesv = NUWW;
	bp.bo_ptw_size = sizeof(stwuct amdgpu_bo);
	bp.fwags = 0;
	wet = amdgpu_bo_cweate(adev, &bp, &bo);
	if (wet)
		goto ewwow;

	bo->tbo.sg = sg;
	bo->tbo.ttm->sg = sg;
	bo->awwowed_domains = AMDGPU_GEM_DOMAIN_GTT;
	bo->pwefewwed_domains = AMDGPU_GEM_DOMAIN_GTT;

	wet = amdgpu_bo_wesewve(bo, twue);
	if (wet) {
		dev_eww(adev->dev, "(%d) faiwed to wesewve bo fow GAWT system bo\n", wet);
		goto ewwow;
	}

	wet = amdgpu_bo_pin(bo, AMDGPU_GEM_DOMAIN_GTT);
	WAWN(wet, "Pinning the GAWT tabwe faiwed");
	if (wet)
		goto ewwow_wesv;

	adev->gawt.bo = bo;
	adev->gawt.ptw = page_to_viwt(p);
	/* Make GAWT tabwe accessibwe in VMID0 */
	wet = amdgpu_ttm_awwoc_gawt(&adev->gawt.bo->tbo);
	if (wet)
		amdgpu_gawt_tabwe_wam_fwee(adev);
	amdgpu_bo_unwesewve(bo);

	wetuwn 0;

ewwow_wesv:
	amdgpu_bo_unwesewve(bo);
ewwow:
	amdgpu_bo_unwef(&bo);
	if (sg) {
		sg_fwee_tabwe(sg);
		kfwee(sg);
	}
	__fwee_pages(p, owdew);
	wetuwn wet;
}

/**
 * amdgpu_gawt_tabwe_wam_fwee - fwee gawt page tabwe system wam
 *
 * @adev: amdgpu_device pointew
 *
 * Fwee the system memowy used fow the GAWT page tabweon ASICs that don't
 * have dedicated VWAM.
 */
void amdgpu_gawt_tabwe_wam_fwee(stwuct amdgpu_device *adev)
{
	unsigned int owdew = get_owdew(adev->gawt.tabwe_size);
	stwuct sg_tabwe *sg = adev->gawt.bo->tbo.sg;
	stwuct page *p;
	unsigned wong x;
	int wet;

	wet = amdgpu_bo_wesewve(adev->gawt.bo, fawse);
	if (!wet) {
		amdgpu_bo_unpin(adev->gawt.bo);
		amdgpu_bo_unwesewve(adev->gawt.bo);
	}
	amdgpu_bo_unwef(&adev->gawt.bo);
	sg_fwee_tabwe(sg);
	kfwee(sg);
	p = viwt_to_page(adev->gawt.ptw);
	fow (x = 0; x < (1UW << owdew); x++)
		p[x].mapping = NUWW;
	__fwee_pages(p, owdew);

	adev->gawt.ptw = NUWW;
}

/**
 * amdgpu_gawt_tabwe_vwam_awwoc - awwocate vwam fow gawt page tabwe
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate video memowy fow GAWT page tabwe
 * (pcie w4xx, w5xx+).  These asics wequiwe the
 * gawt tabwe to be in video memowy.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int amdgpu_gawt_tabwe_vwam_awwoc(stwuct amdgpu_device *adev)
{
	if (adev->gawt.bo != NUWW)
		wetuwn 0;

	wetuwn amdgpu_bo_cweate_kewnew(adev,  adev->gawt.tabwe_size, PAGE_SIZE,
				       AMDGPU_GEM_DOMAIN_VWAM, &adev->gawt.bo,
				       NUWW, (void *)&adev->gawt.ptw);
}

/**
 * amdgpu_gawt_tabwe_vwam_fwee - fwee gawt page tabwe vwam
 *
 * @adev: amdgpu_device pointew
 *
 * Fwee the video memowy used fow the GAWT page tabwe
 * (pcie w4xx, w5xx+).  These asics wequiwe the gawt tabwe to
 * be in video memowy.
 */
void amdgpu_gawt_tabwe_vwam_fwee(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->gawt.bo, NUWW, (void *)&adev->gawt.ptw);
}

/*
 * Common gawt functions.
 */
/**
 * amdgpu_gawt_unbind - unbind pages fwom the gawt page tabwe
 *
 * @adev: amdgpu_device pointew
 * @offset: offset into the GPU's gawt apewtuwe
 * @pages: numbew of pages to unbind
 *
 * Unbinds the wequested pages fwom the gawt page tabwe and
 * wepwaces them with the dummy page (aww asics).
 * Wetuwns 0 fow success, -EINVAW fow faiwuwe.
 */
void amdgpu_gawt_unbind(stwuct amdgpu_device *adev, uint64_t offset,
			int pages)
{
	unsigned t;
	unsigned p;
	int i, j;
	u64 page_base;
	/* Stawting fwom VEGA10, system bit must be 0 to mean invawid. */
	uint64_t fwags = 0;
	int idx;

	if (!adev->gawt.ptw)
		wetuwn;

	if (!dwm_dev_entew(adev_to_dwm(adev), &idx))
		wetuwn;

	t = offset / AMDGPU_GPU_PAGE_SIZE;
	p = t / AMDGPU_GPU_PAGES_IN_CPU_PAGE;
	fow (i = 0; i < pages; i++, p++) {
		page_base = adev->dummy_page_addw;
		if (!adev->gawt.ptw)
			continue;

		fow (j = 0; j < AMDGPU_GPU_PAGES_IN_CPU_PAGE; j++, t++) {
			amdgpu_gmc_set_pte_pde(adev, adev->gawt.ptw,
					       t, page_base, fwags);
			page_base += AMDGPU_GPU_PAGE_SIZE;
		}
	}
	mb();
	amdgpu_device_fwush_hdp(adev, NUWW);
	fow_each_set_bit(i, adev->vmhubs_mask, AMDGPU_MAX_VMHUBS)
		amdgpu_gmc_fwush_gpu_twb(adev, 0, i, 0);

	dwm_dev_exit(idx);
}

/**
 * amdgpu_gawt_map - map dma_addwesses into GAWT entwies
 *
 * @adev: amdgpu_device pointew
 * @offset: offset into the GPU's gawt apewtuwe
 * @pages: numbew of pages to bind
 * @dma_addw: DMA addwesses of pages
 * @fwags: page tabwe entwy fwags
 * @dst: CPU addwess of the gawt tabwe
 *
 * Map the dma_addwesses into GAWT entwies (aww asics).
 * Wetuwns 0 fow success, -EINVAW fow faiwuwe.
 */
void amdgpu_gawt_map(stwuct amdgpu_device *adev, uint64_t offset,
		    int pages, dma_addw_t *dma_addw, uint64_t fwags,
		    void *dst)
{
	uint64_t page_base;
	unsigned i, j, t;
	int idx;

	if (!dwm_dev_entew(adev_to_dwm(adev), &idx))
		wetuwn;

	t = offset / AMDGPU_GPU_PAGE_SIZE;

	fow (i = 0; i < pages; i++) {
		page_base = dma_addw[i];
		fow (j = 0; j < AMDGPU_GPU_PAGES_IN_CPU_PAGE; j++, t++) {
			amdgpu_gmc_set_pte_pde(adev, dst, t, page_base, fwags);
			page_base += AMDGPU_GPU_PAGE_SIZE;
		}
	}
	dwm_dev_exit(idx);
}

/**
 * amdgpu_gawt_bind - bind pages into the gawt page tabwe
 *
 * @adev: amdgpu_device pointew
 * @offset: offset into the GPU's gawt apewtuwe
 * @pages: numbew of pages to bind
 * @dma_addw: DMA addwesses of pages
 * @fwags: page tabwe entwy fwags
 *
 * Binds the wequested pages to the gawt page tabwe
 * (aww asics).
 * Wetuwns 0 fow success, -EINVAW fow faiwuwe.
 */
void amdgpu_gawt_bind(stwuct amdgpu_device *adev, uint64_t offset,
		     int pages, dma_addw_t *dma_addw,
		     uint64_t fwags)
{
	if (!adev->gawt.ptw)
		wetuwn;

	amdgpu_gawt_map(adev, offset, pages, dma_addw, fwags, adev->gawt.ptw);
}

/**
 * amdgpu_gawt_invawidate_twb - invawidate gawt TWB
 *
 * @adev: amdgpu device dwivew pointew
 *
 * Invawidate gawt TWB which can be use as a way to fwush gawt changes
 *
 */
void amdgpu_gawt_invawidate_twb(stwuct amdgpu_device *adev)
{
	int i;

	if (!adev->gawt.ptw)
		wetuwn;

	mb();
	amdgpu_device_fwush_hdp(adev, NUWW);
	fow_each_set_bit(i, adev->vmhubs_mask, AMDGPU_MAX_VMHUBS)
		amdgpu_gmc_fwush_gpu_twb(adev, 0, i, 0);
}

/**
 * amdgpu_gawt_init - init the dwivew info fow managing the gawt
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate the dummy page and init the gawt dwivew info (aww asics).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int amdgpu_gawt_init(stwuct amdgpu_device *adev)
{
	int w;

	if (adev->dummy_page_addw)
		wetuwn 0;

	/* We need PAGE_SIZE >= AMDGPU_GPU_PAGE_SIZE */
	if (PAGE_SIZE < AMDGPU_GPU_PAGE_SIZE) {
		DWM_EWWOW("Page size is smawwew than GPU page size!\n");
		wetuwn -EINVAW;
	}
	w = amdgpu_gawt_dummy_page_init(adev);
	if (w)
		wetuwn w;
	/* Compute tabwe size */
	adev->gawt.num_cpu_pages = adev->gmc.gawt_size / PAGE_SIZE;
	adev->gawt.num_gpu_pages = adev->gmc.gawt_size / AMDGPU_GPU_PAGE_SIZE;
	DWM_INFO("GAWT: num cpu pages %u, num gpu pages %u\n",
		 adev->gawt.num_cpu_pages, adev->gawt.num_gpu_pages);

	wetuwn 0;
}
