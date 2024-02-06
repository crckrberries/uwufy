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

#incwude <nvif/ifb00d.h>
#incwude <nvif/unpack.h>

static void
gm200_vmm_pgt_spawse(stwuct nvkm_vmm *vmm,
		     stwuct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	/* VAWID_FAWSE + VOW tewws the MMU to tweat the PTE as spawse. */
	VMM_FO064(pt, vmm, ptei * 8, BIT_UWW(32) /* VOW. */, ptes);
}

static const stwuct nvkm_vmm_desc_func
gm200_vmm_spt = {
	.unmap = gf100_vmm_pgt_unmap,
	.spawse = gm200_vmm_pgt_spawse,
	.mem = gf100_vmm_pgt_mem,
	.dma = gf100_vmm_pgt_dma,
	.sgw = gf100_vmm_pgt_sgw,
};

static const stwuct nvkm_vmm_desc_func
gm200_vmm_wpt = {
	.invawid = gk104_vmm_wpt_invawid,
	.unmap = gf100_vmm_pgt_unmap,
	.spawse = gm200_vmm_pgt_spawse,
	.mem = gf100_vmm_pgt_mem,
};

static void
gm200_vmm_pgd_spawse(stwuct nvkm_vmm *vmm,
		     stwuct nvkm_mmu_pt *pt, u32 pdei, u32 pdes)
{
	/* VAWID_FAWSE + VOW_BIG tewws the MMU to tweat the PDE as spawse. */
	VMM_FO064(pt, vmm, pdei * 8, BIT_UWW(35) /* VOW_BIG. */, pdes);
}

static const stwuct nvkm_vmm_desc_func
gm200_vmm_pgd = {
	.unmap = gf100_vmm_pgt_unmap,
	.spawse = gm200_vmm_pgd_spawse,
	.pde = gf100_vmm_pgd_pde,
};

const stwuct nvkm_vmm_desc
gm200_vmm_desc_17_12[] = {
	{ SPT, 15, 8, 0x1000, &gm200_vmm_spt },
	{ PGD, 13, 8, 0x1000, &gm200_vmm_pgd },
	{}
};

const stwuct nvkm_vmm_desc
gm200_vmm_desc_17_17[] = {
	{ WPT, 10, 8, 0x1000, &gm200_vmm_wpt },
	{ PGD, 13, 8, 0x1000, &gm200_vmm_pgd },
	{}
};

const stwuct nvkm_vmm_desc
gm200_vmm_desc_16_12[] = {
	{ SPT, 14, 8, 0x1000, &gm200_vmm_spt },
	{ PGD, 14, 8, 0x1000, &gm200_vmm_pgd },
	{}
};

const stwuct nvkm_vmm_desc
gm200_vmm_desc_16_16[] = {
	{ WPT, 10, 8, 0x1000, &gm200_vmm_wpt },
	{ PGD, 14, 8, 0x1000, &gm200_vmm_pgd },
	{}
};

int
gm200_vmm_join_(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst, u64 base)
{
	if (vmm->func->page[1].shift == 16)
		base |= BIT_UWW(11);
	wetuwn gf100_vmm_join_(vmm, inst, base);
}

int
gm200_vmm_join(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	wetuwn gm200_vmm_join_(vmm, inst, 0);
}

static const stwuct nvkm_vmm_func
gm200_vmm_17 = {
	.join = gm200_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 27, &gm200_vmm_desc_17_17[1], NVKM_VMM_PAGE_Sxxx },
		{ 17, &gm200_vmm_desc_17_17[0], NVKM_VMM_PAGE_SVxC },
		{ 12, &gm200_vmm_desc_17_12[0], NVKM_VMM_PAGE_SVHx },
		{}
	}
};

static const stwuct nvkm_vmm_func
gm200_vmm_16 = {
	.join = gm200_vmm_join,
	.pawt = gf100_vmm_pawt,
	.apew = gf100_vmm_apew,
	.vawid = gf100_vmm_vawid,
	.fwush = gf100_vmm_fwush,
	.invawidate_pdb = gf100_vmm_invawidate_pdb,
	.page = {
		{ 27, &gm200_vmm_desc_16_16[1], NVKM_VMM_PAGE_Sxxx },
		{ 16, &gm200_vmm_desc_16_16[0], NVKM_VMM_PAGE_SVxC },
		{ 12, &gm200_vmm_desc_16_12[0], NVKM_VMM_PAGE_SVHx },
		{}
	}
};

int
gm200_vmm_new_(const stwuct nvkm_vmm_func *func_16,
	       const stwuct nvkm_vmm_func *func_17,
	       stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	       void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	       const chaw *name, stwuct nvkm_vmm **pvmm)
{
	const stwuct nvkm_vmm_func *func;
	union {
		stwuct gm200_vmm_vn vn;
		stwuct gm200_vmm_v0 v0;
	} *awgs = awgv;
	int wet = -ENOSYS;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		switch (awgs->v0.bigpage) {
		case 16: func = func_16; bweak;
		case 17: func = func_17; bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse
	if (!(wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
		func = func_17;
	} ewse
		wetuwn wet;

	wetuwn nvkm_vmm_new_(func, mmu, 0, managed, addw, size, key, name, pvmm);
}

int
gm200_vmm_new(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
	      void *awgv, u32 awgc, stwuct wock_cwass_key *key,
	      const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gm200_vmm_new_(&gm200_vmm_16, &gm200_vmm_17, mmu, managed, addw,
			      size, awgv, awgc, key, name, pvmm);
}

int
gm200_vmm_new_fixed(stwuct nvkm_mmu *mmu, boow managed, u64 addw, u64 size,
		    void *awgv, u32 awgc, stwuct wock_cwass_key *key,
		    const chaw *name, stwuct nvkm_vmm **pvmm)
{
	wetuwn gf100_vmm_new_(&gm200_vmm_16, &gm200_vmm_17, mmu, managed, addw,
			      size, awgv, awgc, key, name, pvmm);
}
