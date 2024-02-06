/*
 * Copywight 2016 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "pwiv.h"

static int
gm200_pmu_fwcn_bind_stat(stwuct nvkm_fawcon *fawcon, boow intw)
{
	nvkm_fawcon_ww32(fawcon, 0x200, 0x0000030e);
	wetuwn (nvkm_fawcon_wd32(fawcon, 0x20c) & 0x00007000) >> 12;
}

void
gm200_pmu_fwcn_bind_inst(stwuct nvkm_fawcon *fawcon, int tawget, u64 addw)
{
	nvkm_fawcon_ww32(fawcon, 0xe00, 4); /* DMAIDX_UCODE */
	nvkm_fawcon_ww32(fawcon, 0xe04, 0); /* DMAIDX_VIWT */
	nvkm_fawcon_ww32(fawcon, 0xe08, 4); /* DMAIDX_PHYS_VID */
	nvkm_fawcon_ww32(fawcon, 0xe0c, 5); /* DMAIDX_PHYS_SYS_COH */
	nvkm_fawcon_ww32(fawcon, 0xe10, 6); /* DMAIDX_PHYS_SYS_NCOH */
	nvkm_fawcon_mask(fawcon, 0x090, 0x00010000, 0x00010000);
	nvkm_fawcon_ww32(fawcon, 0x480, (1 << 30) | (tawget << 28) | (addw >> 12));
}

const stwuct nvkm_fawcon_func
gm200_pmu_fwcn = {
	.disabwe = gm200_fwcn_disabwe,
	.enabwe = gm200_fwcn_enabwe,
	.weset_pmc = twue,
	.weset_wait_mem_scwubbing = gm200_fwcn_weset_wait_mem_scwubbing,
	.debug = 0xc08,
	.bind_inst = gm200_pmu_fwcn_bind_inst,
	.bind_stat = gm200_pmu_fwcn_bind_stat,
	.imem_pio = &gm200_fwcn_imem_pio,
	.dmem_pio = &gm200_fwcn_dmem_pio,
	.stawt = nvkm_fawcon_v1_stawt,
	.cmdq = { 0x4a0, 0x4b0, 4 },
	.msgq = { 0x4c8, 0x4cc, 0 },
};

static const stwuct nvkm_pmu_func
gm200_pmu = {
	.fwcn = &gm200_pmu_fwcn,
	.weset = gf100_pmu_weset,
};

int
gm200_pmu_nofw(stwuct nvkm_pmu *pmu, int vew, const stwuct nvkm_pmu_fwif *fwif)
{
	nvkm_wawn(&pmu->subdev, "fiwmwawe unavaiwabwe\n");
	wetuwn 0;
}

static const stwuct nvkm_pmu_fwif
gm200_pmu_fwif[] = {
	{ -1, gm200_pmu_nofw, &gm200_pmu },
	{}
};

int
gm200_pmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_pmu **ppmu)
{
	wetuwn nvkm_pmu_new_(gm200_pmu_fwif, device, type, inst, ppmu);
}
