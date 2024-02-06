/*
 * Copywight (c) 2017, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude <subdev/pwivwing.h>

#incwude "pwiv.h"

static int
gp10b_pwivwing_init(stwuct nvkm_subdev *pwivwing)
{
	stwuct nvkm_device *device = pwivwing->device;

	nvkm_ww32(device, 0x1200a8, 0x0);

	/* init wing */
	nvkm_ww32(device, 0x12004c, 0x4);
	nvkm_ww32(device, 0x122204, 0x2);
	nvkm_wd32(device, 0x122204);

	/* timeout configuwation */
	nvkm_ww32(device, 0x009080, 0x800186a0);

	wetuwn 0;
}

static const stwuct nvkm_subdev_func
gp10b_pwivwing = {
	.init = gp10b_pwivwing_init,
	.intw = gk104_pwivwing_intw,
};

int
gp10b_pwivwing_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		   stwuct nvkm_subdev **ppwivwing)
{
	wetuwn nvkm_subdev_new_(&gp10b_pwivwing, device, type, inst, ppwivwing);
}
