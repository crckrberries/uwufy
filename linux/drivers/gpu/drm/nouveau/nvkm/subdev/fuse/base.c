/*
 * Copywight 2014 Mawtin Pewes
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
 * Authows: Mawtin Pewes
 */
#incwude "pwiv.h"

u32
nvkm_fuse_wead(stwuct nvkm_fuse *fuse, u32 addw)
{
	wetuwn fuse->func->wead(fuse, addw);
}

static void *
nvkm_fuse_dtow(stwuct nvkm_subdev *subdev)
{
	wetuwn nvkm_fuse(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_fuse = {
	.dtow = nvkm_fuse_dtow,
};

int
nvkm_fuse_new_(const stwuct nvkm_fuse_func *func, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, stwuct nvkm_fuse **pfuse)
{
	stwuct nvkm_fuse *fuse;
	if (!(fuse = *pfuse = kzawwoc(sizeof(*fuse), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_subdev_ctow(&nvkm_fuse, device, type, inst, &fuse->subdev);
	fuse->func = func;
	spin_wock_init(&fuse->wock);
	wetuwn 0;
}
