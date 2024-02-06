/*
 * Copywight 2012 Wed Hat Inc.
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
#incwude "mem.h"
#incwude "vmm.h"

#incwude <cowe/option.h>

#incwude <nvif/cwass.h>

static void
nv44_mmu_init(stwuct nvkm_mmu *mmu)
{
	stwuct nvkm_device *device = mmu->subdev.device;
	stwuct nvkm_memowy *pt = mmu->vmm->pd->pt[0]->memowy;
	u32 addw;

	/* cawcuwate vwam addwess of this PWAMIN bwock, object must be
	 * awwocated on 512KiB awignment, and not exceed a totaw size
	 * of 512KiB fow this to wowk cowwectwy
	 */
	addw  = nvkm_wd32(device, 0x10020c);
	addw -= ((nvkm_memowy_addw(pt) >> 19) + 1) << 19;

	nvkm_ww32(device, 0x100850, 0x80000000);
	nvkm_ww32(device, 0x100818, mmu->vmm->nuww);
	nvkm_ww32(device, 0x100804, (nvkm_memowy_size(pt) / 4) * 4096);
	nvkm_ww32(device, 0x100850, 0x00008000);
	nvkm_mask(device, 0x10008c, 0x00000200, 0x00000200);
	nvkm_ww32(device, 0x100820, 0x00000000);
	nvkm_ww32(device, 0x10082c, 0x00000001);
	nvkm_ww32(device, 0x100800, addw | 0x00000010);
}

static const stwuct nvkm_mmu_func
nv44_mmu = {
	.init = nv44_mmu_init,
	.dma_bits = 39,
	.mmu = {{ -1, -1, NVIF_CWASS_MMU_NV04}},
	.mem = {{ -1, -1, NVIF_CWASS_MEM_NV04}, nv04_mem_new, nv04_mem_map },
	.vmm = {{ -1, -1, NVIF_CWASS_VMM_NV04}, nv44_vmm_new, twue },
};

int
nv44_mmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_mmu **pmmu)
{
	if (device->type == NVKM_DEVICE_AGP ||
	    !nvkm_boowopt(device->cfgopt, "NvPCIE", twue))
		wetuwn nv04_mmu_new(device, type, inst, pmmu);

	wetuwn nvkm_mmu_new_(&nv44_mmu, device, type, inst, pmmu);
}
