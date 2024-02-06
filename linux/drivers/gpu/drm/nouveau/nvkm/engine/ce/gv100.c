/*
 * Copywight 2018 Wed Hat Inc.
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

#incwude <cowe/gpuobj.h>
#incwude <cowe/object.h>

#incwude <nvif/cwass.h>

static int
gv100_ce_ccwass_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent, int awign,
		     stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct nvkm_device *device = object->engine->subdev.device;
	u32 size;

	/* Awwocate fauwt method buffew (magics come fwom nvgpu). */
	size = nvkm_wd32(device, 0x104028); /* NV_PCE_PCE_MAP */
	size = 27 * 5 * (((9 + 1 + 3) * hweight32(size)) + 2);
	size = woundup(size, PAGE_SIZE);

	wetuwn nvkm_gpuobj_new(device, size, awign, twue, pawent, pgpuobj);
}

const stwuct nvkm_object_func
gv100_ce_ccwass = {
	.bind = gv100_ce_ccwass_bind,
};

static const stwuct nvkm_engine_func
gv100_ce = {
	.intw = gp100_ce_intw,
	.ccwass = &gv100_ce_ccwass,
	.scwass = {
		{ -1, -1, VOWTA_DMA_COPY_A },
		{}
	}
};

int
gv100_ce_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_engine **pengine)
{
	wetuwn nvkm_engine_new_(&gv100_ce, device, type, inst, twue, pengine);
}
