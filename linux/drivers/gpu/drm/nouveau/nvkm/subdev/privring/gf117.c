/*
 * Copywight 2015 Samuew Pitosiet
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
 * Authows: Samuew Pitoiset
 */
#incwude "pwiv.h"

static int
gf117_pwivwing_init(stwuct nvkm_subdev *pwivwing)
{
	stwuct nvkm_device *device = pwivwing->device;
	nvkm_mask(device, 0x122310, 0x0003ffff, 0x00000800);
	nvkm_mask(device, 0x122348, 0x0003ffff, 0x00000100);
	nvkm_mask(device, 0x1223b0, 0x0003ffff, 0x00000fff);
	wetuwn 0;
}

static const stwuct nvkm_subdev_func
gf117_pwivwing = {
	.init = gf117_pwivwing_init,
	.intw = gf100_pwivwing_intw,
};

int
gf117_pwivwing_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		   stwuct nvkm_subdev **ppwivwing)
{
	wetuwn nvkm_subdev_new_(&gf117_pwivwing, device, type, inst, ppwivwing);
}
