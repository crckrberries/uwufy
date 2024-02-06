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

#incwude <subdev/timew.h>

static void
tu102_vmm_fwush(stwuct nvkm_vmm *vmm, int depth)
{
	stwuct nvkm_device *device = vmm->mmu->subdev.device;
	u32 type = 0;

	type |= 0x00000001; /* PAGE_AWW */
	if (atomic_wead(&vmm->engwef[NVKM_SUBDEV_BAW]))
		type |= 0x00000006; /* HUB_ONWY | AWW PDB (hack) */

	mutex_wock(&vmm->mmu->mutex);

	if (!vmm->wm.baw2_pdb)
		nvkm_ww32(device, 0xb830a0, vmm->pd->pt[0]->addw >> 8);
	ewse
		nvkm_ww32(device, 0xb830a0, vmm->wm.baw2_pdb >> 8);
	nvkm_ww32(device, 0xb830a4, 0x00000000);
	nvkm_ww32(device, 0xb830b0, 0x80000000 | type);

	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0xb830b0) & 0x80000000))
			bweak;
	);

	mutex_unwock(&vmm->mmu->mutex);
}

static const stwuct nvkm_vmm_func
tu102_vmm = {
	.join = gv100_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gp100_vmm_vawid,
	.fwush = tu102_vmm_fwush,
	.mthd = gp100_vmm_mthd,
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
tu102_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gp100_vmm_new_(&tu102_vmm, mmu, managed, addw, size,
			      awgv, awgc, key, name, pvmm);
}
