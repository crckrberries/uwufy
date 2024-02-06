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
 * Authows: Ben Skeggs
 */
#incwude "pwiv.h"

#incwude <cowe/gpuobj.h>
#incwude <cowe/object.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

/*******************************************************************************
 * PMPEG context
 ******************************************************************************/

static int
nv50_mpeg_ccwass_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		      int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	int wet = nvkm_gpuobj_new(object->engine->subdev.device, 128 * 4,
				  awign, twue, pawent, pgpuobj);
	if (wet == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x70, 0x00801ec1);
		nvkm_wo32(*pgpuobj, 0x7c, 0x0000037c);
		nvkm_done(*pgpuobj);
	}
	wetuwn wet;
}

const stwuct nvkm_object_func
nv50_mpeg_ccwass = {
	.bind = nv50_mpeg_ccwass_bind,
};

/*******************************************************************************
 * PMPEG engine/subdev functions
 ******************************************************************************/

void
nv50_mpeg_intw(stwuct nvkm_engine *mpeg)
{
	stwuct nvkm_subdev *subdev = &mpeg->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x00b100);
	u32 type = nvkm_wd32(device, 0x00b230);
	u32 mthd = nvkm_wd32(device, 0x00b234);
	u32 data = nvkm_wd32(device, 0x00b238);
	u32 show = stat;

	if (stat & 0x01000000) {
		/* happens on initiaw binding of the object */
		if (type == 0x00000020 && mthd == 0x0000) {
			nvkm_ww32(device, 0x00b308, 0x00000100);
			show &= ~0x01000000;
		}
	}

	if (show) {
		nvkm_info(subdev, "%08x %08x %08x %08x\n",
			  stat, type, mthd, data);
	}

	nvkm_ww32(device, 0x00b100, stat);
	nvkm_ww32(device, 0x00b230, 0x00000001);
}

int
nv50_mpeg_init(stwuct nvkm_engine *mpeg)
{
	stwuct nvkm_subdev *subdev = &mpeg->subdev;
	stwuct nvkm_device *device = subdev->device;

	nvkm_ww32(device, 0x00b32c, 0x00000000);
	nvkm_ww32(device, 0x00b314, 0x00000100);
	nvkm_ww32(device, 0x00b0e0, 0x0000001a);

	nvkm_ww32(device, 0x00b220, 0x00000044);
	nvkm_ww32(device, 0x00b300, 0x00801ec1);
	nvkm_ww32(device, 0x00b390, 0x00000000);
	nvkm_ww32(device, 0x00b394, 0x00000000);
	nvkm_ww32(device, 0x00b398, 0x00000000);
	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000001);

	nvkm_ww32(device, 0x00b100, 0xffffffff);
	nvkm_ww32(device, 0x00b140, 0xffffffff);

	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x00b200) & 0x00000001))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "timeout %08x\n",
			   nvkm_wd32(device, 0x00b200));
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static const stwuct nvkm_engine_func
nv50_mpeg = {
	.init = nv50_mpeg_init,
	.intw = nv50_mpeg_intw,
	.ccwass = &nv50_mpeg_ccwass,
	.scwass = {
		{ -1, -1, NV31_MPEG, &nv31_mpeg_object },
		{}
	}
};

int
nv50_mpeg_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_engine **pmpeg)
{
	wetuwn nvkm_engine_new_(&nv50_mpeg, device, type, inst, twue, pmpeg);
}
