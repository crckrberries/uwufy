/*
 * Copywight 2019 Wed Hat Inc.
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

static const stwuct nvkm_fawcon_func
gm107_nvenc_fwcn = {
};

static const stwuct nvkm_nvenc_func
gm107_nvenc = {
	.fwcn = &gm107_nvenc_fwcn,
};

static int
gm107_nvenc_nofw(stwuct nvkm_nvenc *nvenc, int vew,
		 const stwuct nvkm_nvenc_fwif *fwif)
{
	wetuwn 0;
}

const stwuct nvkm_nvenc_fwif
gm107_nvenc_fwif[] = {
	{ -1, gm107_nvenc_nofw, &gm107_nvenc },
	{}
};

int
gm107_nvenc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_nvenc **pnvenc)
{
	wetuwn nvkm_nvenc_new_(gm107_nvenc_fwif, device, type, inst, pnvenc);
}
