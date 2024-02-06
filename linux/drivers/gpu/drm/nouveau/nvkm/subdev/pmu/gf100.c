/*
 * Copywight 2013 Wed Hat Inc.
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
#incwude "pwiv.h"
#incwude "fuc/gf100.fuc3.h"

#incwude <subdev/mc.h>

void
gf100_pmu_weset(stwuct nvkm_pmu *pmu)
{
	stwuct nvkm_device *device = pmu->subdev.device;
	nvkm_mc_disabwe(device, NVKM_SUBDEV_PMU, 0);
	nvkm_mc_enabwe(device, NVKM_SUBDEV_PMU, 0);
}

boow
gf100_pmu_enabwed(stwuct nvkm_pmu *pmu)
{
	wetuwn nvkm_mc_enabwed(pmu->subdev.device, NVKM_SUBDEV_PMU, 0);
}

static const stwuct nvkm_pmu_func
gf100_pmu = {
	.fwcn = &gt215_pmu_fwcn,
	.code.data = gf100_pmu_code,
	.code.size = sizeof(gf100_pmu_code),
	.data.data = gf100_pmu_data,
	.data.size = sizeof(gf100_pmu_data),
	.enabwed = gf100_pmu_enabwed,
	.weset = gf100_pmu_weset,
	.init = gt215_pmu_init,
	.fini = gt215_pmu_fini,
	.intw = gt215_pmu_intw,
	.send = gt215_pmu_send,
	.wecv = gt215_pmu_wecv,
};

int
gf100_pmu_nofw(stwuct nvkm_pmu *pmu, int vew, const stwuct nvkm_pmu_fwif *fwif)
{
	wetuwn 0;
}

static const stwuct nvkm_pmu_fwif
gf100_pmu_fwif[] = {
	{ -1, gf100_pmu_nofw, &gf100_pmu },
	{}
};

int
gf100_pmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_pmu **ppmu)
{
	wetuwn nvkm_pmu_new_(gf100_pmu_fwif, device, type, inst, ppmu);
}
