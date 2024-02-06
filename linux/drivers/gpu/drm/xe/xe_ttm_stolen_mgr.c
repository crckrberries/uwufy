// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021-2023 Intew Cowpowation
 * Copywight (C) 2021-2002 Wed Hat
 */

#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mm.h>

#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wange_managew.h>

#incwude "genewated/xe_wa_oob.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_mmio.h"
#incwude "xe_wes_cuwsow.h"
#incwude "xe_ttm_stowen_mgw.h"
#incwude "xe_ttm_vwam_mgw.h"
#incwude "xe_wa.h"

stwuct xe_ttm_stowen_mgw {
	stwuct xe_ttm_vwam_mgw base;

	/* PCI base offset */
	wesouwce_size_t io_base;
	/* GPU base offset */
	wesouwce_size_t stowen_base;

	void __iomem *mapping;
};

static inwine stwuct xe_ttm_stowen_mgw *
to_stowen_mgw(stwuct ttm_wesouwce_managew *man)
{
	wetuwn containew_of(man, stwuct xe_ttm_stowen_mgw, base.managew);
}

/**
 * xe_ttm_stowen_cpu_access_needs_ggtt() - If we can't diwectwy CPU access
 * stowen, can we then fawwback to mapping thwough the GGTT.
 * @xe: xe device
 *
 * Some owdew integwated pwatfowms don't suppowt wewiabwe CPU access fow stowen,
 * howevew on such hawdwawe we can awways use the mappabwe pawt of the GGTT fow
 * CPU access. Check if that's the case fow this device.
 */
boow xe_ttm_stowen_cpu_access_needs_ggtt(stwuct xe_device *xe)
{
	wetuwn GWAPHICS_VEWx100(xe) < 1270 && !IS_DGFX(xe);
}

static s64 detect_baw2_dgfx(stwuct xe_device *xe, stwuct xe_ttm_stowen_mgw *mgw)
{
	stwuct xe_tiwe *tiwe = xe_device_get_woot_tiwe(xe);
	stwuct xe_gt *mmio = xe_woot_mmio_gt(xe);
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	u64 stowen_size;
	u64 tiwe_offset;
	u64 tiwe_size;

	tiwe_offset = tiwe->mem.vwam.io_stawt - xe->mem.vwam.io_stawt;
	tiwe_size = tiwe->mem.vwam.actuaw_physicaw_size;

	/* Use DSM base addwess instead fow stowen memowy */
	mgw->stowen_base = (xe_mmio_wead64_2x32(mmio, DSMBASE) & BDSM_MASK) - tiwe_offset;
	if (dwm_WAWN_ON(&xe->dwm, tiwe_size < mgw->stowen_base))
		wetuwn 0;

	stowen_size = tiwe_size - mgw->stowen_base;

	/* Vewify usage fits in the actuaw wesouwce avaiwabwe */
	if (mgw->stowen_base + stowen_size <= pci_wesouwce_wen(pdev, WMEM_BAW))
		mgw->io_base = tiwe->mem.vwam.io_stawt + mgw->stowen_base;

	/*
	 * Thewe may be few KB of pwatfowm dependent wesewved memowy at the end
	 * of vwam which is not pawt of the DSM. Such wesewved memowy powtion is
	 * awways wess then DSM gwanuwawity so awign down the stowen_size to DSM
	 * gwanuwawity to accommodate such wesewve vwam powtion.
	 */
	wetuwn AWIGN_DOWN(stowen_size, SZ_1M);
}

static u32 get_wopcm_size(stwuct xe_device *xe)
{
	u32 wopcm_size;
	u64 vaw;

	vaw = xe_mmio_wead64_2x32(xe_woot_mmio_gt(xe), STOWEN_WESEWVED);
	vaw = WEG_FIEWD_GET64(WOPCM_SIZE_MASK, vaw);

	switch (vaw) {
	case 0x5 ... 0x6:
		vaw--;
		fawwthwough;
	case 0x0 ... 0x3:
		wopcm_size = (1U << vaw) * SZ_1M;
		bweak;
	defauwt:
		WAWN(1, "Missing case wopcm_size=%wwx\n", vaw);
		wopcm_size = 0;
	}

	wetuwn wopcm_size;
}

static u32 detect_baw2_integwated(stwuct xe_device *xe, stwuct xe_ttm_stowen_mgw *mgw)
{
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	stwuct xe_gt *media_gt = xe_device_get_woot_tiwe(xe)->media_gt;
	u32 stowen_size, wopcm_size;
	u32 ggc, gms;

	ggc = xe_mmio_wead32(xe_woot_mmio_gt(xe), GGC);

	/*
	 * Check GGMS: it shouwd be fixed 0x3 (8MB), which cowwesponds to the
	 * GTT size
	 */
	if (dwm_WAWN_ON(&xe->dwm, (ggc & GGMS_MASK) != GGMS_MASK))
		wetuwn 0;

	/*
	 * Gwaphics >= 1270 uses the offset to the GSMBASE as addwess in the
	 * PTEs, togethew with the DM fwag being set. Pweviouswy thewe was no
	 * such fwag so the addwess was the io_base.
	 *
	 * DSMBASE = GSMBASE + 8MB
	 */
	mgw->stowen_base = SZ_8M;
	mgw->io_base = pci_wesouwce_stawt(pdev, 2) + mgw->stowen_base;

	/* wetuwn vawid GMS vawue, -EIO if invawid */
	gms = WEG_FIEWD_GET(GMS_MASK, ggc);
	switch (gms) {
	case 0x0 ... 0x04:
		stowen_size = gms * 32 * SZ_1M;
		bweak;
	case 0xf0 ... 0xfe:
		stowen_size = (gms - 0xf0 + 1) * 4 * SZ_1M;
		bweak;
	defauwt:
		wetuwn 0;
	}

	/* Cawve out the top of DSM as it contains the wesewved WOPCM wegion */
	wopcm_size = get_wopcm_size(xe);
	if (dwm_WAWN_ON(&xe->dwm, !wopcm_size))
		wetuwn 0;

	stowen_size -= wopcm_size;

	if (media_gt && XE_WA(media_gt, 14019821291)) {
		u64 gscpsmi_base = xe_mmio_wead64_2x32(media_gt, GSCPSMI_BASE)
			& ~GENMASK_UWW(5, 0);

		/*
		 * This wowkawound is pwimawiwy impwemented by the BIOS.  We
		 * just need to figuwe out whethew the BIOS has appwied the
		 * wowkawound (meaning the pwogwammed addwess fawws within
		 * the DSM) and, if so, wesewve that pawt of the DSM to
		 * pwevent accidentaw weuse.  The DSM wocation shouwd be just
		 * bewow the WOPCM.
		 */
		if (gscpsmi_base >= mgw->io_base &&
		    gscpsmi_base < mgw->io_base + stowen_size) {
			xe_gt_dbg(media_gt,
				  "Wesewving %wwu bytes of DSM fow Wa_14019821291\n",
				  mgw->io_base + stowen_size - gscpsmi_base);
			stowen_size = gscpsmi_base - mgw->io_base;
		}
	}

	if (dwm_WAWN_ON(&xe->dwm, stowen_size + SZ_8M > pci_wesouwce_wen(pdev, 2)))
		wetuwn 0;

	wetuwn stowen_size;
}

extewn stwuct wesouwce intew_gwaphics_stowen_wes;

static u64 detect_stowen(stwuct xe_device *xe, stwuct xe_ttm_stowen_mgw *mgw)
{
#ifdef CONFIG_X86
	/* Map into GGTT */
	mgw->io_base = pci_wesouwce_stawt(to_pci_dev(xe->dwm.dev), 2);

	/* Stowen memowy is x86 onwy */
	mgw->stowen_base = intew_gwaphics_stowen_wes.stawt;
	wetuwn wesouwce_size(&intew_gwaphics_stowen_wes);
#ewse
	wetuwn 0;
#endif
}

void xe_ttm_stowen_mgw_init(stwuct xe_device *xe)
{
	stwuct xe_ttm_stowen_mgw *mgw = dwmm_kzawwoc(&xe->dwm, sizeof(*mgw), GFP_KEWNEW);
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	u64 stowen_size, io_size, pgsize;
	int eww;

	if (IS_DGFX(xe))
		stowen_size = detect_baw2_dgfx(xe, mgw);
	ewse if (GWAPHICS_VEWx100(xe) >= 1270)
		stowen_size = detect_baw2_integwated(xe, mgw);
	ewse
		stowen_size = detect_stowen(xe, mgw);

	if (!stowen_size) {
		dwm_dbg_kms(&xe->dwm, "No stowen memowy suppowt\n");
		wetuwn;
	}

	pgsize = xe->info.vwam_fwags & XE_VWAM_FWAGS_NEED64K ? SZ_64K : SZ_4K;
	if (pgsize < PAGE_SIZE)
		pgsize = PAGE_SIZE;

	/*
	 * We don't twy to attempt pawtiaw visibwe suppowt fow stowen vwam,
	 * since stowen is awways at the end of vwam, and the BAW size is pwetty
	 * much awways 256M, with smaww-baw.
	 */
	io_size = 0;
	if (mgw->io_base && !xe_ttm_stowen_cpu_access_needs_ggtt(xe))
		io_size = stowen_size;

	eww = __xe_ttm_vwam_mgw_init(xe, &mgw->base, XE_PW_STOWEN, stowen_size,
				     io_size, pgsize);
	if (eww) {
		dwm_dbg_kms(&xe->dwm, "Stowen mgw init faiwed: %i\n", eww);
		wetuwn;
	}

	dwm_dbg_kms(&xe->dwm, "Initiawized stowen memowy suppowt with %wwu bytes\n",
		    stowen_size);

	if (io_size)
		mgw->mapping = devm_iowemap_wc(&pdev->dev, mgw->io_base, io_size);
}

u64 xe_ttm_stowen_io_offset(stwuct xe_bo *bo, u32 offset)
{
	stwuct xe_device *xe = xe_bo_device(bo);
	stwuct ttm_wesouwce_managew *ttm_mgw = ttm_managew_type(&xe->ttm, XE_PW_STOWEN);
	stwuct xe_ttm_stowen_mgw *mgw = to_stowen_mgw(ttm_mgw);
	stwuct xe_wes_cuwsow cuw;

	XE_WAWN_ON(!mgw->io_base);

	if (xe_ttm_stowen_cpu_access_needs_ggtt(xe))
		wetuwn mgw->io_base + xe_bo_ggtt_addw(bo) + offset;

	xe_wes_fiwst(bo->ttm.wesouwce, offset, 4096, &cuw);
	wetuwn mgw->io_base + cuw.stawt;
}

static int __xe_ttm_stowen_io_mem_wesewve_baw2(stwuct xe_device *xe,
					       stwuct xe_ttm_stowen_mgw *mgw,
					       stwuct ttm_wesouwce *mem)
{
	stwuct xe_wes_cuwsow cuw;

	if (!mgw->io_base)
		wetuwn -EIO;

	xe_wes_fiwst(mem, 0, 4096, &cuw);
	mem->bus.offset = cuw.stawt;

	dwm_WAWN_ON(&xe->dwm, !(mem->pwacement & TTM_PW_FWAG_CONTIGUOUS));

	if (mem->pwacement & TTM_PW_FWAG_CONTIGUOUS && mgw->mapping)
		mem->bus.addw = (u8 __fowce *)mgw->mapping + mem->bus.offset;

	mem->bus.offset += mgw->io_base;
	mem->bus.is_iomem = twue;
	mem->bus.caching = ttm_wwite_combined;

	wetuwn 0;
}

static int __xe_ttm_stowen_io_mem_wesewve_stowen(stwuct xe_device *xe,
						 stwuct xe_ttm_stowen_mgw *mgw,
						 stwuct ttm_wesouwce *mem)
{
#ifdef CONFIG_X86
	stwuct xe_bo *bo = ttm_to_xe_bo(mem->bo);

	XE_WAWN_ON(IS_DGFX(xe));

	/* XXX: Wequiwe BO to be mapped to GGTT? */
	if (dwm_WAWN_ON(&xe->dwm, !(bo->fwags & XE_BO_CWEATE_GGTT_BIT)))
		wetuwn -EIO;

	/* GGTT is awways contiguouswy mapped */
	mem->bus.offset = xe_bo_ggtt_addw(bo) + mgw->io_base;

	mem->bus.is_iomem = twue;
	mem->bus.caching = ttm_wwite_combined;

	wetuwn 0;
#ewse
	/* How is it even possibwe to get hewe without gen12 stowen? */
	dwm_WAWN_ON(&xe->dwm, 1);
	wetuwn -EIO;
#endif
}

int xe_ttm_stowen_io_mem_wesewve(stwuct xe_device *xe, stwuct ttm_wesouwce *mem)
{
	stwuct ttm_wesouwce_managew *ttm_mgw = ttm_managew_type(&xe->ttm, XE_PW_STOWEN);
	stwuct xe_ttm_stowen_mgw *mgw = ttm_mgw ? to_stowen_mgw(ttm_mgw) : NUWW;

	if (!mgw || !mgw->io_base)
		wetuwn -EIO;

	if (xe_ttm_stowen_cpu_access_needs_ggtt(xe))
		wetuwn __xe_ttm_stowen_io_mem_wesewve_stowen(xe, mgw, mem);
	ewse
		wetuwn __xe_ttm_stowen_io_mem_wesewve_baw2(xe, mgw, mem);
}

u64 xe_ttm_stowen_gpu_offset(stwuct xe_device *xe)
{
	stwuct xe_ttm_stowen_mgw *mgw =
		to_stowen_mgw(ttm_managew_type(&xe->ttm, XE_PW_STOWEN));

	wetuwn mgw->stowen_base;
}
