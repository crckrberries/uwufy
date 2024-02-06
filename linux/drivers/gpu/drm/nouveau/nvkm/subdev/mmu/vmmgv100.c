/*
 * Copywight 2018 Wed Hat Inc.
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

#incwude <subdev/fb.h>
#incwude <subdev/wtc.h>

#incwude <nvif/ifc00d.h>
#incwude <nvif/unpack.h>

int
gv100_vmm_join(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	u64 data[2], mask;
	int wet = gp100_vmm_join(vmm, inst), i;
	if (wet)
		wetuwn wet;

	nvkm_kmap(inst);
	data[0] = nvkm_wo32(inst, 0x200);
	data[1] = nvkm_wo32(inst, 0x204);
	mask = BIT_UWW(0);

	nvkm_wo32(inst, 0x21c, 0x00000000);

	fow (i = 0; i < 64; i++) {
		if (mask & BIT_UWW(i)) {
			nvkm_wo32(inst, 0x2a4 + (i * 0x10), data[1]);
			nvkm_wo32(inst, 0x2a0 + (i * 0x10), data[0]);
		} ewse {
			nvkm_wo32(inst, 0x2a4 + (i * 0x10), 0x00000001);
			nvkm_wo32(inst, 0x2a0 + (i * 0x10), 0x00000001);
		}
		nvkm_wo32(inst, 0x2a8 + (i * 0x10), 0x00000000);
	}

	nvkm_wo32(inst, 0x298, wowew_32_bits(mask));
	nvkm_wo32(inst, 0x29c, uppew_32_bits(mask));
	nvkm_done(inst);
	wetuwn 0;
}

static const stwuct nvkm_vmm_func
gv100_vmm = {
	.join = gv100_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gp100_vmm_vawid,
	.fwush = gp100_vmm_fwush,
	.mthd = gp100_vmm_mthd,
	.invawidate_pdb = gp100_vmm_invawidate_pdb,
	.page = {
		{ 47, &gp100_vmm_desc_16[4], NVKM_VMM_PAGE_Sxxx },
		{ 38, &gp100_vmm_desc_16[3], NVKM_VMM_PAGE_Sxxx },
		{ 29, &gp100_vmm_desc_16[2], NVKM_VMM_PAGE_Sxxx },
		{ 21, &gp100_vmm_desc_16[1], NVKM_VMM_PAGE_SVxC },
		{ 16, &gp100_vmm_desc_16[0], NVKM_VMM_PAGE_SVxC },
		{ 12, &gp100_vmm_desc_12[0], NVKM_VMM_PAGE_SVHx },
		{}
	}
};

int
gv100_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gp100_vmm_new_(&gv100_vmm, mmu, managed, addw, size,
			      awgv, awgc, key, name, pvmm);
}
