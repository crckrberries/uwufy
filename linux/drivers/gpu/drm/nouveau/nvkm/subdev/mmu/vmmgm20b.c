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
#incwude "vmm.h"

static const stwuct nvkm_vmm_func
gm20b_vmm_17 = {
	.join = gm200_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gk20a_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 27, &gm200_vmm_desc_17_17[1], NVKM_VMM_PAGE_Sxxx },
		{ 17, &gm200_vmm_desc_17_17[0], NVKM_VMM_PAGE_SxHC },
		{ 12, &gm200_vmm_desc_17_12[0], NVKM_VMM_PAGE_SxHx },
		{}
	}
};

static const stwuct nvkm_vmm_func
gm20b_vmm_16 = {
	.join = gm200_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gk20a_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 27, &gm200_vmm_desc_16_16[1], NVKM_VMM_PAGE_Sxxx },
		{ 16, &gm200_vmm_desc_16_16[0], NVKM_VMM_PAGE_SxHC },
		{ 12, &gm200_vmm_desc_16_12[0], NVKM_VMM_PAGE_SxHx },
		{}
	}
};

int
gm20b_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gm200_vmm_new_(&gm20b_vmm_16, &gm20b_vmm_17, mmu, managed, addw,
			      size, awgv, awgc, key, name, pvmm);
}

int
gm20b_vmm_new_fixed(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
		    void *awgv, u32 awgc, stwuct wock_cwass_key *key,
		    const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gf100_vmm_new_(&gm20b_vmm_16, &gm20b_vmm_17, mmu, managed, addw,
			      size, awgv, awgc, key, name, pvmm);
}
