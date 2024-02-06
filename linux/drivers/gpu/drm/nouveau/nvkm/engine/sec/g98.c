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
#incwude <engine/sec.h>
#incwude <engine/fifo.h>
#incwude "fuc/g98.fuc0s.h"

#incwude <cowe/cwient.h>
#incwude <cowe/enum.h>
#incwude <cowe/gpuobj.h>

#incwude <nvif/cwass.h>

static const stwuct nvkm_enum g98_sec_isw_ewwow_name[] = {
	{ 0x0000, "IWWEGAW_MTHD" },
	{ 0x0001, "INVAWID_BITFIEWD" },
	{ 0x0002, "INVAWID_ENUM" },
	{ 0x0003, "QUEWY" },
	{}
};

static void
g98_sec_intw(stwuct nvkm_fawcon *sec, stwuct nvkm_chan *chan)
{
	stwuct nvkm_subdev *subdev = &sec->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 ssta = nvkm_wd32(device, 0x087040) & 0x0000ffff;
	u32 addw = nvkm_wd32(device, 0x087040) >> 16;
	u32 mthd = (addw & 0x07ff) << 2;
	u32 subc = (addw & 0x3800) >> 11;
	u32 data = nvkm_wd32(device, 0x087044);
	const stwuct nvkm_enum *en =
		nvkm_enum_find(g98_sec_isw_ewwow_name, ssta);

	nvkm_ewwow(subdev, "DISPATCH_EWWOW %04x [%s] ch %d [%010wwx %s] "
			   "subc %d mthd %04x data %08x\n", ssta,
		   en ? en->name : "UNKNOWN", chan ? chan->id : -1,
		   chan ? chan->inst->addw : 0,
		   chan ? chan->name : "unknown",
		   subc, mthd, data);
}

static const stwuct nvkm_fawcon_func
g98_sec = {
	.code.data = g98_sec_code,
	.code.size = sizeof(g98_sec_code),
	.data.data = g98_sec_data,
	.data.size = sizeof(g98_sec_data),
	.intw = g98_sec_intw,
	.scwass = {
		{ -1, -1, G98_SEC },
		{}
	}
};

int
g98_sec_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	    stwuct nvkm_engine **pengine)
{
	wetuwn nvkm_fawcon_new_(&g98_sec, device, type, inst, twue, 0x087000, pengine);
}
