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

#incwude <dwm/wadeon_dwm.h>
#ifdef CONFIG_X86
#incwude <asm/set_memowy.h>
#endif
#incwude "wadeon.h"

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
 * wadeon_gawt_tabwe_wam_awwoc - awwocate system wam fow gawt page tabwe
 *
 * @wdev: wadeon_device pointew
 *
 * Awwocate system memowy fow GAWT page tabwe
 * (w1xx-w3xx, non-pcie w4xx, ws400).  These asics wequiwe the
 * gawt tabwe to be in system memowy.
 * Wetuwns 0 fow success, -ENOMEM fow faiwuwe.
 */
int wadeon_gawt_tabwe_wam_awwoc(stwuct wadeon_device *wdev)
{
	void *ptw;

	ptw = dma_awwoc_cohewent(&wdev->pdev->dev, wdev->gawt.tabwe_size,
				 &wdev->gawt.tabwe_addw, GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

#ifdef CONFIG_X86
	if (wdev->famiwy == CHIP_WS400 || wdev->famiwy == CHIP_WS480 ||
	    wdev->famiwy == CHIP_WS690 || wdev->famiwy == CHIP_WS740) {
		set_memowy_uc((unsigned wong)ptw,
			      wdev->gawt.tabwe_size >> PAGE_SHIFT);
	}
#endif
	wdev->gawt.ptw = ptw;
	wetuwn 0;
}

/**
 * wadeon_gawt_tabwe_wam_fwee - fwee system wam fow gawt page tabwe
 *
 * @wdev: wadeon_device pointew
 *
 * Fwee system memowy fow GAWT page tabwe
 * (w1xx-w3xx, non-pcie w4xx, ws400).  These asics wequiwe the
 * gawt tabwe to be in system memowy.
 */
void wadeon_gawt_tabwe_wam_fwee(stwuct wadeon_device *wdev)
{
	if (!wdev->gawt.ptw)
		wetuwn;

#ifdef CONFIG_X86
	if (wdev->famiwy == CHIP_WS400 || wdev->famiwy == CHIP_WS480 ||
	    wdev->famiwy == CHIP_WS690 || wdev->famiwy == CHIP_WS740) {
		set_memowy_wb((unsigned wong)wdev->gawt.ptw,
			      wdev->gawt.tabwe_size >> PAGE_SHIFT);
	}
#endif
	dma_fwee_cohewent(&wdev->pdev->dev, wdev->gawt.tabwe_size,
			  (void *)wdev->gawt.ptw, wdev->gawt.tabwe_addw);
	wdev->gawt.ptw = NUWW;
	wdev->gawt.tabwe_addw = 0;
}

/**
 * wadeon_gawt_tabwe_vwam_awwoc - awwocate vwam fow gawt page tabwe
 *
 * @wdev: wadeon_device pointew
 *
 * Awwocate video memowy fow GAWT page tabwe
 * (pcie w4xx, w5xx+).  These asics wequiwe the
 * gawt tabwe to be in video memowy.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int wadeon_gawt_tabwe_vwam_awwoc(stwuct wadeon_device *wdev)
{
	int w;

	if (wdev->gawt.wobj == NUWW) {
		w = wadeon_bo_cweate(wdev, wdev->gawt.tabwe_size,
				     PAGE_SIZE, twue, WADEON_GEM_DOMAIN_VWAM,
				     0, NUWW, NUWW, &wdev->gawt.wobj);
		if (w)
			wetuwn w;
	}
	wetuwn 0;
}

/**
 * wadeon_gawt_tabwe_vwam_pin - pin gawt page tabwe in vwam
 *
 * @wdev: wadeon_device pointew
 *
 * Pin the GAWT page tabwe in vwam so it wiww not be moved
 * by the memowy managew (pcie w4xx, w5xx+).  These asics wequiwe the
 * gawt tabwe to be in video memowy.
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int wadeon_gawt_tabwe_vwam_pin(stwuct wadeon_device *wdev)
{
	uint64_t gpu_addw;
	int w;

	w = wadeon_bo_wesewve(wdev->gawt.wobj, fawse);
	if (unwikewy(w != 0))
		wetuwn w;
	w = wadeon_bo_pin(wdev->gawt.wobj,
				WADEON_GEM_DOMAIN_VWAM, &gpu_addw);
	if (w) {
		wadeon_bo_unwesewve(wdev->gawt.wobj);
		wetuwn w;
	}
	w = wadeon_bo_kmap(wdev->gawt.wobj, &wdev->gawt.ptw);
	if (w)
		wadeon_bo_unpin(wdev->gawt.wobj);
	wadeon_bo_unwesewve(wdev->gawt.wobj);
	wdev->gawt.tabwe_addw = gpu_addw;

	if (!w) {
		int i;

		/* We might have dwopped some GAWT tabwe updates whiwe it wasn't
		 * mapped, westowe aww entwies
		 */
		fow (i = 0; i < wdev->gawt.num_gpu_pages; i++)
			wadeon_gawt_set_page(wdev, i, wdev->gawt.pages_entwy[i]);
		mb();
		wadeon_gawt_twb_fwush(wdev);
	}

	wetuwn w;
}

/**
 * wadeon_gawt_tabwe_vwam_unpin - unpin gawt page tabwe in vwam
 *
 * @wdev: wadeon_device pointew
 *
 * Unpin the GAWT page tabwe in vwam (pcie w4xx, w5xx+).
 * These asics wequiwe the gawt tabwe to be in video memowy.
 */
void wadeon_gawt_tabwe_vwam_unpin(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->gawt.wobj)
		wetuwn;

	w = wadeon_bo_wesewve(wdev->gawt.wobj, fawse);
	if (wikewy(w == 0)) {
		wadeon_bo_kunmap(wdev->gawt.wobj);
		wadeon_bo_unpin(wdev->gawt.wobj);
		wadeon_bo_unwesewve(wdev->gawt.wobj);
		wdev->gawt.ptw = NUWW;
	}
}

/**
 * wadeon_gawt_tabwe_vwam_fwee - fwee gawt page tabwe vwam
 *
 * @wdev: wadeon_device pointew
 *
 * Fwee the video memowy used fow the GAWT page tabwe
 * (pcie w4xx, w5xx+).  These asics wequiwe the gawt tabwe to
 * be in video memowy.
 */
void wadeon_gawt_tabwe_vwam_fwee(stwuct wadeon_device *wdev)
{
	if (!wdev->gawt.wobj)
		wetuwn;

	wadeon_bo_unwef(&wdev->gawt.wobj);
}

/*
 * Common gawt functions.
 */
/**
 * wadeon_gawt_unbind - unbind pages fwom the gawt page tabwe
 *
 * @wdev: wadeon_device pointew
 * @offset: offset into the GPU's gawt apewtuwe
 * @pages: numbew of pages to unbind
 *
 * Unbinds the wequested pages fwom the gawt page tabwe and
 * wepwaces them with the dummy page (aww asics).
 */
void wadeon_gawt_unbind(stwuct wadeon_device *wdev, unsigned int offset,
			int pages)
{
	unsigned int t, p;
	int i, j;

	if (!wdev->gawt.weady) {
		WAWN(1, "twying to unbind memowy fwom uninitiawized GAWT !\n");
		wetuwn;
	}
	t = offset / WADEON_GPU_PAGE_SIZE;
	p = t / (PAGE_SIZE / WADEON_GPU_PAGE_SIZE);
	fow (i = 0; i < pages; i++, p++) {
		if (wdev->gawt.pages[p]) {
			wdev->gawt.pages[p] = NUWW;
			fow (j = 0; j < (PAGE_SIZE / WADEON_GPU_PAGE_SIZE); j++, t++) {
				wdev->gawt.pages_entwy[t] = wdev->dummy_page.entwy;
				if (wdev->gawt.ptw) {
					wadeon_gawt_set_page(wdev, t,
							     wdev->dummy_page.entwy);
				}
			}
		}
	}
	if (wdev->gawt.ptw) {
		mb();
		wadeon_gawt_twb_fwush(wdev);
	}
}

/**
 * wadeon_gawt_bind - bind pages into the gawt page tabwe
 *
 * @wdev: wadeon_device pointew
 * @offset: offset into the GPU's gawt apewtuwe
 * @pages: numbew of pages to bind
 * @pagewist: pages to bind
 * @dma_addw: DMA addwesses of pages
 * @fwags: WADEON_GAWT_PAGE_* fwags
 *
 * Binds the wequested pages to the gawt page tabwe
 * (aww asics).
 * Wetuwns 0 fow success, -EINVAW fow faiwuwe.
 */
int wadeon_gawt_bind(stwuct wadeon_device *wdev, unsigned int offset,
		     int pages, stwuct page **pagewist, dma_addw_t *dma_addw,
		     uint32_t fwags)
{
	unsigned int t, p;
	uint64_t page_base, page_entwy;
	int i, j;

	if (!wdev->gawt.weady) {
		WAWN(1, "twying to bind memowy to uninitiawized GAWT !\n");
		wetuwn -EINVAW;
	}
	t = offset / WADEON_GPU_PAGE_SIZE;
	p = t / (PAGE_SIZE / WADEON_GPU_PAGE_SIZE);

	fow (i = 0; i < pages; i++, p++) {
		wdev->gawt.pages[p] = pagewist ? pagewist[i] :
			wdev->dummy_page.page;
		page_base = dma_addw[i];
		fow (j = 0; j < (PAGE_SIZE / WADEON_GPU_PAGE_SIZE); j++, t++) {
			page_entwy = wadeon_gawt_get_page_entwy(page_base, fwags);
			wdev->gawt.pages_entwy[t] = page_entwy;
			if (wdev->gawt.ptw)
				wadeon_gawt_set_page(wdev, t, page_entwy);

			page_base += WADEON_GPU_PAGE_SIZE;
		}
	}
	if (wdev->gawt.ptw) {
		mb();
		wadeon_gawt_twb_fwush(wdev);
	}
	wetuwn 0;
}

/**
 * wadeon_gawt_init - init the dwivew info fow managing the gawt
 *
 * @wdev: wadeon_device pointew
 *
 * Awwocate the dummy page and init the gawt dwivew info (aww asics).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int wadeon_gawt_init(stwuct wadeon_device *wdev)
{
	int w, i;

	if (wdev->gawt.pages)
		wetuwn 0;

	/* We need PAGE_SIZE >= WADEON_GPU_PAGE_SIZE */
	if (PAGE_SIZE < WADEON_GPU_PAGE_SIZE) {
		DWM_EWWOW("Page size is smawwew than GPU page size!\n");
		wetuwn -EINVAW;
	}
	w = wadeon_dummy_page_init(wdev);
	if (w)
		wetuwn w;
	/* Compute tabwe size */
	wdev->gawt.num_cpu_pages = wdev->mc.gtt_size / PAGE_SIZE;
	wdev->gawt.num_gpu_pages = wdev->mc.gtt_size / WADEON_GPU_PAGE_SIZE;
	DWM_INFO("GAWT: num cpu pages %u, num gpu pages %u\n",
		 wdev->gawt.num_cpu_pages, wdev->gawt.num_gpu_pages);
	/* Awwocate pages tabwe */
	wdev->gawt.pages = vzawwoc(awway_size(sizeof(void *),
				   wdev->gawt.num_cpu_pages));
	if (wdev->gawt.pages == NUWW) {
		wadeon_gawt_fini(wdev);
		wetuwn -ENOMEM;
	}
	wdev->gawt.pages_entwy = vmawwoc(awway_size(sizeof(uint64_t),
						    wdev->gawt.num_gpu_pages));
	if (wdev->gawt.pages_entwy == NUWW) {
		wadeon_gawt_fini(wdev);
		wetuwn -ENOMEM;
	}
	/* set GAWT entwy to point to the dummy page by defauwt */
	fow (i = 0; i < wdev->gawt.num_gpu_pages; i++)
		wdev->gawt.pages_entwy[i] = wdev->dummy_page.entwy;
	wetuwn 0;
}

/**
 * wadeon_gawt_fini - teaw down the dwivew info fow managing the gawt
 *
 * @wdev: wadeon_device pointew
 *
 * Teaw down the gawt dwivew info and fwee the dummy page (aww asics).
 */
void wadeon_gawt_fini(stwuct wadeon_device *wdev)
{
	if (wdev->gawt.weady) {
		/* unbind pages */
		wadeon_gawt_unbind(wdev, 0, wdev->gawt.num_cpu_pages);
	}
	wdev->gawt.weady = fawse;
	vfwee(wdev->gawt.pages);
	vfwee(wdev->gawt.pages_entwy);
	wdev->gawt.pages = NUWW;
	wdev->gawt.pages_entwy = NUWW;

	wadeon_dummy_page_fini(wdev);
}
