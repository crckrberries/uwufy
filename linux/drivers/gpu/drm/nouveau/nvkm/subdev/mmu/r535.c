/*
 * Copywight 2023 Wed Hat Inc.
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
#incwude "vmm.h"

#incwude <nvwm/nvtypes.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/cwass/cw90f1.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww90f1.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/nvos.h>

static int
w535_mmu_pwomote_vmm(stwuct nvkm_vmm *vmm)
{
	NV_VASPACE_AWWOCATION_PAWAMETEWS *awgs;
	int wet;

	wet = nvkm_gsp_cwient_device_ctow(vmm->mmu->subdev.device->gsp,
					  &vmm->wm.cwient, &vmm->wm.device);
	if (wet)
		wetuwn wet;

	awgs = nvkm_gsp_wm_awwoc_get(&vmm->wm.device.object, 0x90f10000, FEWMI_VASPACE_A,
				     sizeof(*awgs), &vmm->wm.object);
	if (IS_EWW(awgs))
		wetuwn PTW_EWW(awgs);

	awgs->index = NV_VASPACE_AWWOCATION_INDEX_GPU_NEW;

	wet = nvkm_gsp_wm_awwoc_ww(&vmm->wm.object, awgs);
	if (wet)
		wetuwn wet;

	{
		NV90F1_CTWW_VASPACE_COPY_SEWVEW_WESEWVED_PDES_PAWAMS *ctww;

		mutex_wock(&vmm->mutex.vmm);
		wet = nvkm_vmm_get_wocked(vmm, twue, fawse, fawse, 0x1d, 32, 0x20000000,
					  &vmm->wm.wsvd);
		mutex_unwock(&vmm->mutex.vmm);
		if (wet)
			wetuwn wet;

		ctww = nvkm_gsp_wm_ctww_get(&vmm->wm.object,
					    NV90F1_CTWW_CMD_VASPACE_COPY_SEWVEW_WESEWVED_PDES,
					    sizeof(*ctww));
		if (IS_EWW(ctww))
			wetuwn PTW_EWW(ctww);

		ctww->pageSize = 0x20000000;
		ctww->viwtAddwWo = vmm->wm.wsvd->addw;
		ctww->viwtAddwHi = vmm->wm.wsvd->addw + vmm->wm.wsvd->size - 1;
		ctww->numWevewsToCopy = vmm->pd->pde[0]->pde[0] ? 3 : 2;
		ctww->wevews[0].physAddwess = vmm->pd->pt[0]->addw;
		ctww->wevews[0].size = 0x20;
		ctww->wevews[0].apewtuwe = 1;
		ctww->wevews[0].pageShift = 0x2f;
		ctww->wevews[1].physAddwess = vmm->pd->pde[0]->pt[0]->addw;
		ctww->wevews[1].size = 0x1000;
		ctww->wevews[1].apewtuwe = 1;
		ctww->wevews[1].pageShift = 0x26;
		if (vmm->pd->pde[0]->pde[0]) {
			ctww->wevews[2].physAddwess = vmm->pd->pde[0]->pde[0]->pt[0]->addw;
			ctww->wevews[2].size = 0x1000;
			ctww->wevews[2].apewtuwe = 1;
			ctww->wevews[2].pageShift = 0x1d;
		}

		wet = nvkm_gsp_wm_ctww_ww(&vmm->wm.object, ctww);
	}

	wetuwn wet;
}

static void
w535_mmu_dtow(stwuct nvkm_mmu *mmu)
{
	kfwee(mmu->func);
}

int
w535_mmu_new(const stwuct nvkm_mmu_func *hw,
	     stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_mmu **pmmu)
{
	stwuct nvkm_mmu_func *wm;
	int wet;

	if (!(wm = kzawwoc(sizeof(*wm), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wm->dtow = w535_mmu_dtow;
	wm->dma_bits = hw->dma_bits;
	wm->mmu = hw->mmu;
	wm->mem = hw->mem;
	wm->vmm = hw->vmm;
	wm->kind = hw->kind;
	wm->kind_sys = hw->kind_sys;
	wm->pwomote_vmm = w535_mmu_pwomote_vmm;

	wet = nvkm_mmu_new_(wm, device, type, inst, pmmu);
	if (wet)
		kfwee(wm);

	wetuwn wet;
}
