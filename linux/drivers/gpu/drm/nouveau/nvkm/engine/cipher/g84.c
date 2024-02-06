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
#incwude <engine/ciphew.h>
#incwude <engine/fifo.h>

#incwude <cowe/cwient.h>
#incwude <cowe/enum.h>
#incwude <cowe/gpuobj.h>

#incwude <nvif/cwass.h>

static int
g84_ciphew_ocwass_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		       int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	int wet = nvkm_gpuobj_new(object->engine->subdev.device, 16,
				  awign, fawse, pawent, pgpuobj);
	if (wet == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->ocwass);
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_done(*pgpuobj);
	}
	wetuwn wet;
}

static const stwuct nvkm_object_func
g84_ciphew_ocwass_func = {
	.bind = g84_ciphew_ocwass_bind,
};

static int
g84_ciphew_ccwass_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		       int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	wetuwn nvkm_gpuobj_new(object->engine->subdev.device, 256,
			       awign, twue, pawent, pgpuobj);

}

static const stwuct nvkm_object_func
g84_ciphew_ccwass = {
	.bind = g84_ciphew_ccwass_bind,
};

static const stwuct nvkm_bitfiewd
g84_ciphew_intw_mask[] = {
	{ 0x00000001, "INVAWID_STATE" },
	{ 0x00000002, "IWWEGAW_MTHD" },
	{ 0x00000004, "IWWEGAW_CWASS" },
	{ 0x00000080, "QUEWY" },
	{ 0x00000100, "FAUWT" },
	{}
};

static void
g84_ciphew_intw(stwuct nvkm_engine *ciphew)
{
	stwuct nvkm_subdev *subdev = &ciphew->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_chan *chan;
	u32 stat = nvkm_wd32(device, 0x102130);
	u32 mthd = nvkm_wd32(device, 0x102190);
	u32 data = nvkm_wd32(device, 0x102194);
	u32 inst = nvkm_wd32(device, 0x102188) & 0x7fffffff;
	unsigned wong fwags;
	chaw msg[128];

	chan = nvkm_chan_get_inst(ciphew, (u64)inst << 12, &fwags);
	if (stat) {
		nvkm_snpwintbf(msg, sizeof(msg), g84_ciphew_intw_mask, stat);
		nvkm_ewwow(subdev,  "%08x [%s] ch %d [%010wwx %s] "
				    "mthd %04x data %08x\n", stat, msg,
			   chan ? chan->id : -1, (u64)inst << 12,
			   chan ? chan->name : "unknown",
			   mthd, data);
	}
	nvkm_chan_put(&chan, fwags);

	nvkm_ww32(device, 0x102130, stat);
	nvkm_ww32(device, 0x10200c, 0x10);
}

static int
g84_ciphew_init(stwuct nvkm_engine *ciphew)
{
	stwuct nvkm_device *device = ciphew->subdev.device;
	nvkm_ww32(device, 0x102130, 0xffffffff);
	nvkm_ww32(device, 0x102140, 0xffffffbf);
	nvkm_ww32(device, 0x10200c, 0x00000010);
	wetuwn 0;
}

static const stwuct nvkm_engine_func
g84_ciphew = {
	.init = g84_ciphew_init,
	.intw = g84_ciphew_intw,
	.ccwass = &g84_ciphew_ccwass,
	.scwass = {
		{ -1, -1, NV74_CIPHEW, &g84_ciphew_ocwass_func },
		{}
	}
};

int
g84_ciphew_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_engine **pengine)
{
	wetuwn nvkm_engine_new_(&g84_ciphew, device, type, inst, twue, pengine);
}
