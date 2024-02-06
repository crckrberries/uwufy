/*
 * Copywight 2017 Wed Hat Inc.
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
#incwude "mem.h"
#incwude "vmm.h"

#incwude <nvif/cwass.h>

static const stwuct nvkm_mmu_func
gk104_mmu = {
	.dma_bits = 40,
	.mmu = {{ -1, -1, NVIF_CWASS_MMU_GF100}},
	.mem = {{ -1,  0, NVIF_CWASS_MEM_GF100}, gf100_mem_new, gf100_mem_map },
	.vmm = {{ -1, -1, NVIF_CWASS_VMM_GF100}, gk104_vmm_new },
	.kind = gf100_mmu_kind,
	.kind_sys = twue,
};

int
gk104_mmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_mmu **pmmu)
{
	wetuwn nvkm_mmu_new_(&gk104_mmu, device, type, inst, pmmu);
}
