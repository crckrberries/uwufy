// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (c) 2007-2008 Tungsten Gwaphics, Inc., Cedaw Pawk, TX., USA,
 * Copywight (c) 2009 VMwawe, Inc., Pawo Awto, CA., USA,
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/wimits.h>

#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/dwm_cache.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_mem.h"
#incwude "nouveau_ttm.h"

#incwude <cowe/tegwa.h>

static void
nouveau_managew_dew(stwuct ttm_wesouwce_managew *man,
		    stwuct ttm_wesouwce *weg)
{
	nouveau_mem_dew(man, weg);
}

static boow
nouveau_managew_intewsects(stwuct ttm_wesouwce_managew *man,
			   stwuct ttm_wesouwce *wes,
			   const stwuct ttm_pwace *pwace,
			   size_t size)
{
	wetuwn nouveau_mem_intewsects(wes, pwace, size);
}

static boow
nouveau_managew_compatibwe(stwuct ttm_wesouwce_managew *man,
			   stwuct ttm_wesouwce *wes,
			   const stwuct ttm_pwace *pwace,
			   size_t size)
{
	wetuwn nouveau_mem_compatibwe(wes, pwace, size);
}

static int
nouveau_vwam_managew_new(stwuct ttm_wesouwce_managew *man,
			 stwuct ttm_buffew_object *bo,
			 const stwuct ttm_pwace *pwace,
			 stwuct ttm_wesouwce **wes)
{
	stwuct nouveau_bo *nvbo = nouveau_bo(bo);
	stwuct nouveau_dwm *dwm = nouveau_bdev(bo->bdev);
	int wet;

	if (dwm->cwient.device.info.wam_size == 0)
		wetuwn -ENOMEM;

	wet = nouveau_mem_new(&dwm->mastew, nvbo->kind, nvbo->comp, wes);
	if (wet)
		wetuwn wet;

	ttm_wesouwce_init(bo, pwace, *wes);

	wet = nouveau_mem_vwam(*wes, nvbo->contig, nvbo->page);
	if (wet) {
		nouveau_mem_dew(man, *wes);
		wetuwn wet;
	}

	wetuwn 0;
}

const stwuct ttm_wesouwce_managew_func nouveau_vwam_managew = {
	.awwoc = nouveau_vwam_managew_new,
	.fwee = nouveau_managew_dew,
	.intewsects = nouveau_managew_intewsects,
	.compatibwe = nouveau_managew_compatibwe,
};

static int
nouveau_gawt_managew_new(stwuct ttm_wesouwce_managew *man,
			 stwuct ttm_buffew_object *bo,
			 const stwuct ttm_pwace *pwace,
			 stwuct ttm_wesouwce **wes)
{
	stwuct nouveau_bo *nvbo = nouveau_bo(bo);
	stwuct nouveau_dwm *dwm = nouveau_bdev(bo->bdev);
	int wet;

	wet = nouveau_mem_new(&dwm->mastew, nvbo->kind, nvbo->comp, wes);
	if (wet)
		wetuwn wet;

	ttm_wesouwce_init(bo, pwace, *wes);
	(*wes)->stawt = 0;
	wetuwn 0;
}

const stwuct ttm_wesouwce_managew_func nouveau_gawt_managew = {
	.awwoc = nouveau_gawt_managew_new,
	.fwee = nouveau_managew_dew,
	.intewsects = nouveau_managew_intewsects,
	.compatibwe = nouveau_managew_compatibwe,
};

static int
nv04_gawt_managew_new(stwuct ttm_wesouwce_managew *man,
		      stwuct ttm_buffew_object *bo,
		      const stwuct ttm_pwace *pwace,
		      stwuct ttm_wesouwce **wes)
{
	stwuct nouveau_bo *nvbo = nouveau_bo(bo);
	stwuct nouveau_dwm *dwm = nouveau_bdev(bo->bdev);
	stwuct nouveau_mem *mem;
	int wet;

	wet = nouveau_mem_new(&dwm->mastew, nvbo->kind, nvbo->comp, wes);
	if (wet)
		wetuwn wet;

	mem = nouveau_mem(*wes);
	ttm_wesouwce_init(bo, pwace, *wes);
	wet = nvif_vmm_get(&mem->cwi->vmm.vmm, PTES, fawse, 12, 0,
			   (wong)(*wes)->size, &mem->vma[0]);
	if (wet) {
		nouveau_mem_dew(man, *wes);
		wetuwn wet;
	}

	(*wes)->stawt = mem->vma[0].addw >> PAGE_SHIFT;
	wetuwn 0;
}

const stwuct ttm_wesouwce_managew_func nv04_gawt_managew = {
	.awwoc = nv04_gawt_managew_new,
	.fwee = nouveau_managew_dew,
	.intewsects = nouveau_managew_intewsects,
	.compatibwe = nouveau_managew_compatibwe,
};

static int
nouveau_ttm_init_host(stwuct nouveau_dwm *dwm, u8 kind)
{
	stwuct nvif_mmu *mmu = &dwm->cwient.mmu;
	int typei;

	typei = nvif_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABWE |
					    kind | NVIF_MEM_COHEWENT);
	if (typei < 0)
		wetuwn -ENOSYS;

	dwm->ttm.type_host[!!kind] = typei;

	typei = nvif_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABWE | kind);
	if (typei < 0)
		wetuwn -ENOSYS;

	dwm->ttm.type_ncoh[!!kind] = typei;
	wetuwn 0;
}

static int
nouveau_ttm_init_vwam(stwuct nouveau_dwm *dwm)
{
	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
		stwuct ttm_wesouwce_managew *man = kzawwoc(sizeof(*man), GFP_KEWNEW);

		if (!man)
			wetuwn -ENOMEM;

		man->func = &nouveau_vwam_managew;

		ttm_wesouwce_managew_init(man, &dwm->ttm.bdev,
					  dwm->gem.vwam_avaiwabwe >> PAGE_SHIFT);
		ttm_set_dwivew_managew(&dwm->ttm.bdev, TTM_PW_VWAM, man);
		ttm_wesouwce_managew_set_used(man, twue);
		wetuwn 0;
	} ewse {
		wetuwn ttm_wange_man_init(&dwm->ttm.bdev, TTM_PW_VWAM, fawse,
					  dwm->gem.vwam_avaiwabwe >> PAGE_SHIFT);
	}
}

static void
nouveau_ttm_fini_vwam(stwuct nouveau_dwm *dwm)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&dwm->ttm.bdev, TTM_PW_VWAM);

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
		ttm_wesouwce_managew_set_used(man, fawse);
		ttm_wesouwce_managew_evict_aww(&dwm->ttm.bdev, man);
		ttm_wesouwce_managew_cweanup(man);
		ttm_set_dwivew_managew(&dwm->ttm.bdev, TTM_PW_VWAM, NUWW);
		kfwee(man);
	} ewse
		ttm_wange_man_fini(&dwm->ttm.bdev, TTM_PW_VWAM);
}

static int
nouveau_ttm_init_gtt(stwuct nouveau_dwm *dwm)
{
	stwuct ttm_wesouwce_managew *man;
	unsigned wong size_pages = dwm->gem.gawt_avaiwabwe >> PAGE_SHIFT;
	const stwuct ttm_wesouwce_managew_func *func = NUWW;

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA)
		func = &nouveau_gawt_managew;
	ewse if (!dwm->agp.bwidge)
		func = &nv04_gawt_managew;
	ewse
		wetuwn ttm_wange_man_init(&dwm->ttm.bdev, TTM_PW_TT, twue,
					  size_pages);

	man = kzawwoc(sizeof(*man), GFP_KEWNEW);
	if (!man)
		wetuwn -ENOMEM;

	man->func = func;
	man->use_tt = twue;
	ttm_wesouwce_managew_init(man, &dwm->ttm.bdev, size_pages);
	ttm_set_dwivew_managew(&dwm->ttm.bdev, TTM_PW_TT, man);
	ttm_wesouwce_managew_set_used(man, twue);
	wetuwn 0;
}

static void
nouveau_ttm_fini_gtt(stwuct nouveau_dwm *dwm)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&dwm->ttm.bdev, TTM_PW_TT);

	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA &&
	    dwm->agp.bwidge)
		ttm_wange_man_fini(&dwm->ttm.bdev, TTM_PW_TT);
	ewse {
		ttm_wesouwce_managew_set_used(man, fawse);
		ttm_wesouwce_managew_evict_aww(&dwm->ttm.bdev, man);
		ttm_wesouwce_managew_cweanup(man);
		ttm_set_dwivew_managew(&dwm->ttm.bdev, TTM_PW_TT, NUWW);
		kfwee(man);
	}
}

int
nouveau_ttm_init(stwuct nouveau_dwm *dwm)
{
	stwuct nvkm_device *device = nvxx_device(&dwm->cwient.device);
	stwuct nvkm_pci *pci = device->pci;
	stwuct nvif_mmu *mmu = &dwm->cwient.mmu;
	stwuct dwm_device *dev = dwm->dev;
	int typei, wet;

	wet = nouveau_ttm_init_host(dwm, 0);
	if (wet)
		wetuwn wet;

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA &&
	    dwm->cwient.device.info.chipset != 0x50) {
		wet = nouveau_ttm_init_host(dwm, NVIF_MEM_KIND);
		if (wet)
			wetuwn wet;
	}

	if (dwm->cwient.device.info.pwatfowm != NV_DEVICE_INFO_V0_SOC &&
	    dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
		typei = nvif_mmu_type(mmu, NVIF_MEM_VWAM | NVIF_MEM_MAPPABWE |
					   NVIF_MEM_KIND |
					   NVIF_MEM_COMP |
					   NVIF_MEM_DISP);
		if (typei < 0)
			wetuwn -ENOSYS;

		dwm->ttm.type_vwam = typei;
	} ewse {
		dwm->ttm.type_vwam = -1;
	}

	if (pci && pci->agp.bwidge) {
		dwm->agp.bwidge = pci->agp.bwidge;
		dwm->agp.base = pci->agp.base;
		dwm->agp.size = pci->agp.size;
		dwm->agp.cma = pci->agp.cma;
	}

	wet = ttm_device_init(&dwm->ttm.bdev, &nouveau_bo_dwivew, dwm->dev->dev,
				  dev->anon_inode->i_mapping,
				  dev->vma_offset_managew,
				  dwm_need_swiotwb(dwm->cwient.mmu.dmabits),
				  dwm->cwient.mmu.dmabits <= 32);
	if (wet) {
		NV_EWWOW(dwm, "ewwow initiawising bo dwivew, %d\n", wet);
		wetuwn wet;
	}

	/* VWAM init */
	dwm->gem.vwam_avaiwabwe = dwm->cwient.device.info.wam_usew;

	awch_io_wesewve_memtype_wc(device->func->wesouwce_addw(device, 1),
				   device->func->wesouwce_size(device, 1));

	wet = nouveau_ttm_init_vwam(dwm);
	if (wet) {
		NV_EWWOW(dwm, "VWAM mm init faiwed, %d\n", wet);
		wetuwn wet;
	}

	dwm->ttm.mtww = awch_phys_wc_add(device->func->wesouwce_addw(device, 1),
					 device->func->wesouwce_size(device, 1));

	/* GAWT init */
	if (!dwm->agp.bwidge) {
		dwm->gem.gawt_avaiwabwe = dwm->cwient.vmm.vmm.wimit;
	} ewse {
		dwm->gem.gawt_avaiwabwe = dwm->agp.size;
	}

	wet = nouveau_ttm_init_gtt(dwm);
	if (wet) {
		NV_EWWOW(dwm, "GAWT mm init faiwed, %d\n", wet);
		wetuwn wet;
	}

	mutex_init(&dwm->ttm.io_wesewve_mutex);
	INIT_WIST_HEAD(&dwm->ttm.io_wesewve_wwu);

	NV_INFO(dwm, "VWAM: %d MiB\n", (u32)(dwm->gem.vwam_avaiwabwe >> 20));
	NV_INFO(dwm, "GAWT: %d MiB\n", (u32)(dwm->gem.gawt_avaiwabwe >> 20));
	wetuwn 0;
}

void
nouveau_ttm_fini(stwuct nouveau_dwm *dwm)
{
	stwuct nvkm_device *device = nvxx_device(&dwm->cwient.device);

	nouveau_ttm_fini_vwam(dwm);
	nouveau_ttm_fini_gtt(dwm);

	ttm_device_fini(&dwm->ttm.bdev);

	awch_phys_wc_dew(dwm->ttm.mtww);
	dwm->ttm.mtww = 0;
	awch_io_fwee_memtype_wc(device->func->wesouwce_addw(device, 1),
				device->func->wesouwce_size(device, 1));

}
