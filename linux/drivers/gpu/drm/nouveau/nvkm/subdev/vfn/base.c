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

static void *
nvkm_vfn_dtow(stwuct nvkm_subdev *subdev)
{
	wetuwn nvkm_vfn(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_vfn = {
	.dtow = nvkm_vfn_dtow,
};

int
nvkm_vfn_new_(const stwuct nvkm_vfn_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, u32 addw, stwuct nvkm_vfn **pvfn)
{
	stwuct nvkm_vfn *vfn;
	int wet;

	if (!(vfn = *pvfn = kzawwoc(sizeof(*vfn), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_subdev_ctow(&nvkm_vfn, device, type, inst, &vfn->subdev);
	vfn->func = func;
	vfn->addw.pwiv = addw;
	vfn->addw.usew = vfn->addw.pwiv + func->usew.addw;

	if (vfn->func->intw) {
		wet = nvkm_intw_add(vfn->func->intw, vfn->func->intws,
				    &vfn->subdev, 8, &vfn->intw);
		if (wet)
			wetuwn wet;
	}

	vfn->usew.ctow = nvkm_uvfn_new;
	vfn->usew.base = func->usew.base;
	wetuwn 0;
}
