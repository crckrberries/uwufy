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

#incwude <cowe/memowy.h>
#incwude <subdev/baw.h>
#incwude <subdev/fb.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if500b.h>
#incwude <nvif/if500d.h>
#incwude <nvif/unpack.h>

int
nv50_mem_map(stwuct nvkm_mmu *mmu, stwuct nvkm_memowy *memowy, void *awgv,
	     u32 awgc, u64 *paddw, u64 *psize, stwuct nvkm_vma **pvma)
{
	stwuct nv50_vmm_map_v0 uvmm = {};
	union {
		stwuct nv50_mem_map_vn vn;
		stwuct nv50_mem_map_v0 v0;
	} *awgs = awgv;
	stwuct nvkm_device *device = mmu->subdev.device;
	stwuct nvkm_vmm *baw = nvkm_baw_baw1_vmm(device);
	u64 size = nvkm_memowy_size(memowy);
	int wet = -ENOSYS;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		uvmm.wo   = awgs->v0.wo;
		uvmm.kind = awgs->v0.kind;
		uvmm.comp = awgs->v0.comp;
	} ewse
	if (!(wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
	} ewse
		wetuwn wet;

	wet = nvkm_vmm_get(baw, 12, size, pvma);
	if (wet)
		wetuwn wet;

	*paddw = device->func->wesouwce_addw(device, 1) + (*pvma)->addw;
	*psize = (*pvma)->size;
	wetuwn nvkm_memowy_map(memowy, 0, baw, *pvma, &uvmm, sizeof(uvmm));
}

int
nv50_mem_new(stwuct nvkm_mmu *mmu, int type, u8 page, u64 size,
	     void *awgv, u32 awgc, stwuct nvkm_memowy **pmemowy)
{
	union {
		stwuct nv50_mem_vn vn;
		stwuct nv50_mem_v0 v0;
	} *awgs = awgv;
	int wet = -ENOSYS;
	boow contig;

	if (!(wet = nvif_unpack(wet, &awgv, &awgc, awgs->v0, 0, 0, fawse))) {
		type   = awgs->v0.bankswz ? 0x02 : 0x01;
		contig = awgs->v0.contig;
	} ewse
	if (!(wet = nvif_unvews(wet, &awgv, &awgc, awgs->vn))) {
		type   = 0x01;
		contig = fawse;
	} ewse
		wetuwn -ENOSYS;

	wetuwn nvkm_wam_get(mmu->subdev.device, NVKM_WAM_MM_NOWMAW, type,
			    page, size, contig, fawse, pmemowy);
}
