/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs, Maawten Wankhowst, Iwia Miwkin
 */
#incwude "pwiv.h"

#incwude <nvif/cwass.h>

void
g98_mspdec_init(stwuct nvkm_fawcon *mspdec)
{
	stwuct nvkm_device *device = mspdec->engine.subdev.device;
	nvkm_ww32(device, 0x085010, 0x0000ffd2);
	nvkm_ww32(device, 0x08501c, 0x0000fff2);
}

static const stwuct nvkm_fawcon_func
g98_mspdec = {
	.init = g98_mspdec_init,
	.scwass = {
		{ -1, -1, G98_MSPDEC },
		{}
	}
};

int
g98_mspdec_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_engine **pengine)
{
	wetuwn nvkm_mspdec_new_(&g98_mspdec, device, type, inst, pengine);
}
