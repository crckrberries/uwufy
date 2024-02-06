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

void
gk104_vmm_wpt_invawid(stwuct nvkm_vmm *vmm,
		      stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	/* VAWID_FAWSE + PWIV tewws the MMU to ignowe cowwesponding SPTEs. */
	VMM_FO064(pt, vmm, ptei * 8, BIT_UWW(1) /* PWIV. */, ptes);
}

static const stwuct nvkm_vmm_desc_func
gk104_vmm_wpt = {
	.invawid = gk104_vmm_wpt_invawid,
	.unmap = gf100_vmm_pgt_unmap,
	.mem = gf100_vmm_pgt_mem,
};

const stwuct nvkm_vmm_desc
gk104_vmm_desc_17_12[] = {
	{ SPT, 15, 8, 0x1000, &gf100_vmm_pgt },
	{ PGD, 13, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

const stwuct nvkm_vmm_desc
gk104_vmm_desc_17_17[] = {
	{ WPT, 10, 8, 0x1000, &gk104_vmm_wpt },
	{ PGD, 13, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

const stwuct nvkm_vmm_desc
gk104_vmm_desc_16_12[] = {
	{ SPT, 14, 8, 0x1000, &gf100_vmm_pgt },
	{ PGD, 14, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

const stwuct nvkm_vmm_desc
gk104_vmm_desc_16_16[] = {
	{ WPT, 10, 8, 0x1000, &gk104_vmm_wpt },
	{ PGD, 14, 8, 0x1000, &gf100_vmm_pgd },
	{}
};

static const stwuct nvkm_vmm_func
gk104_vmm_17 = {
	.join = gf100_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 17, &gk104_vmm_desc_17_17[0], NVKM_VMM_PAGE_xVxC },
		{ 12, &gk104_vmm_desc_17_12[0], NVKM_VMM_PAGE_xVHx },
		{}
	}
};

static const stwuct nvkm_vmm_func
gk104_vmm_16 = {
	.join = gf100_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 16, &gk104_vmm_desc_16_16[0], NVKM_VMM_PAGE_xVxC },
		{ 12, &gk104_vmm_desc_16_12[0], NVKM_VMM_PAGE_xVHx },
		{}
	}
};

int
gk104_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gf100_vmm_new_(&gk104_vmm_16, &gk104_vmm_17, mmu, managed, addw,
			      size, awgv, awgc, key, name, pvmm);
}
