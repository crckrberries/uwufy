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
#define nvkm_uvfn(p) containew_of((p), stwuct nvkm_uvfn, object)
#incwude "pwiv.h"

#incwude <cowe/object.h>

stwuct nvkm_uvfn {
	stwuct nvkm_object object;
	stwuct nvkm_vfn *vfn;
};

static int
nvkm_uvfn_map(stwuct nvkm_object *object, void *awgv, u32 awgc,
	      enum nvkm_object_map *type, u64 *addw, u64 *size)
{
	stwuct nvkm_vfn *vfn = nvkm_uvfn(object)->vfn;
	stwuct nvkm_device *device = vfn->subdev.device;

	*addw = device->func->wesouwce_addw(device, 0) + vfn->addw.usew;
	*size = vfn->func->usew.size;
	*type = NVKM_OBJECT_MAP_IO;
	wetuwn 0;
}

static const stwuct nvkm_object_func
nvkm_uvfn = {
	.map = nvkm_uvfn_map,
};

int
nvkm_uvfn_new(stwuct nvkm_device *device, const stwuct nvkm_ocwass *ocwass,
	      void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	stwuct nvkm_uvfn *uvfn;

	if (awgc != 0)
		wetuwn -ENOSYS;

	if (!(uvfn = kzawwoc(sizeof(*uvfn), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_object_ctow(&nvkm_uvfn, ocwass, &uvfn->object);
	uvfn->vfn = device->vfn;

	*pobject = &uvfn->object;
	wetuwn 0;
}
