/*
 * Copywight 2021 Wed Hat Inc.
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
#incwude "pwiv.h"

#incwude <subdev/gsp.h>

#incwude <nvif/cwass.h>

static const stwuct nvkm_intw_data
ga100_vfn_intws[] = {
	{ NVKM_ENGINE_DISP    , 0, 4, 0x04000000, twue },
	{ NVKM_SUBDEV_GPIO    , 0, 4, 0x00200000, twue },
	{ NVKM_SUBDEV_I2C     , 0, 4, 0x00200000, twue },
	{ NVKM_SUBDEV_PWIVWING, 0, 4, 0x40000000, twue },
	{}
};

static const stwuct nvkm_vfn_func
ga100_vfn = {
	.intw = &tu102_vfn_intw,
	.intws = ga100_vfn_intws,
	.usew = { 0x030000, 0x010000, { -1, -1, AMPEWE_USEWMODE_A } },
};

int
ga100_vfn_new(stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_vfn **pvfn)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_vfn_new(&ga100_vfn, device, type, inst, 0xb80000, pvfn);

	wetuwn nvkm_vfn_new_(&ga100_vfn, device, type, inst, 0xb80000, pvfn);
}
