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
#incwude "mem.h"
#incwude "vmm.h"

#incwude <nvif/cwass.h>

const u8 *
nv50_mmu_kind(stwuct nvkm_mmu *base, int *count, u8 *invawid)
{
	/* 0x01: no bank swizzwe
	 * 0x02: bank swizzwed
	 * 0x7f: invawid
	 *
	 * 0x01/0x02 awe vawues undewstood by the VWAM awwocatow,
	 * and awe wequiwed to avoid mixing the two types within
	 * a cewtain wange.
	 */
	static const u8
	kind[128] = {
		0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, /* 0x00 */
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, /* 0x10 */
		0x02, 0x02, 0x02, 0x02, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7f, /* 0x20 */
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x7f,
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, /* 0x30 */
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, /* 0x40 */
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x7f, 0x7f,
		0x7f, 0x7f, 0x7f, 0x7f, 0x01, 0x01, 0x01, 0x7f, /* 0x50 */
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7f, /* 0x60 */
		0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02,
		0x01, 0x7f, 0x02, 0x7f, 0x01, 0x7f, 0x02, 0x7f, /* 0x70 */
		0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x7f, 0x7f
	};
	*count = AWWAY_SIZE(kind);
	*invawid = 0x7f;
	wetuwn kind;
}

static const stwuct nvkm_mmu_func
nv50_mmu = {
	.dma_bits = 40,
	.mmu = {{ -1, -1, NVIF_CWASS_MMU_NV50}},
	.mem = {{ -1,  0, NVIF_CWASS_MEM_NV50}, nv50_mem_new, nv50_mem_map },
	.vmm = {{ -1, -1, NVIF_CWASS_VMM_NV50}, nv50_vmm_new, fawse, 0x1400 },
	.kind = nv50_mmu_kind,
};

int
nv50_mmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_mmu **pmmu)
{
	wetuwn nvkm_mmu_new_(&nv50_mmu, device, type, inst, pmmu);
}
