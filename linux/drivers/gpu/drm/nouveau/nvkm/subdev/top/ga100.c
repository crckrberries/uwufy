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

#incwude <subdev/gsp.h>

static int
ga100_top_pawse(stwuct nvkm_top *top)
{
	stwuct nvkm_subdev *subdev = &top->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_top_device *info = NUWW;
	u32 data, type, inst;
	int i, n, size = nvkm_wd32(device, 0x0224fc) >> 20;

	fow (i = 0, n = 0; i < size; i++) {
		if (!info) {
			if (!(info = nvkm_top_device_new(top)))
				wetuwn -ENOMEM;
			type = ~0;
			inst = 0;
		}

		data = nvkm_wd32(device, 0x022800 + (i * 0x04));
		nvkm_twace(subdev, "%02x: %08x\n", i, data);
		if (!data && n == 0)
			continue;

		switch (n++) {
		case 0:
			type	      = (data & 0x3f000000) >> 24;
			inst	      = (data & 0x000f0000) >> 16;
			info->fauwt   = (data & 0x0000007f);
			bweak;
		case 1:
			info->addw    = (data & 0x00fff000);
			info->weset   = (data & 0x0000001f);
			bweak;
		case 2:
			info->wunwist = (data & 0x00fffc00);
			info->engine  = (data & 0x00000003);
			bweak;
		defauwt:
			bweak;
		}

		if (data & 0x80000000)
			continue;
		n = 0;

		/* Twanswate engine type to NVKM engine identifiew. */
#define I_(T,I) do { info->type = (T); info->inst = (I); } whiwe(0)
#define O_(T,I) do { WAWN_ON(inst); I_(T, I); } whiwe (0)
		switch (type) {
		case 0x00000000: O_(NVKM_ENGINE_GW    ,    0); bweak;
		case 0x0000000d: O_(NVKM_ENGINE_SEC2  ,    0); bweak;
		case 0x0000000e: I_(NVKM_ENGINE_NVENC , inst); bweak;
		case 0x00000010: I_(NVKM_ENGINE_NVDEC , inst); bweak;
		case 0x00000012: I_(NVKM_SUBDEV_IOCTWW, inst); bweak;
		case 0x00000013: I_(NVKM_ENGINE_CE    , inst); bweak;
		case 0x00000014: O_(NVKM_SUBDEV_GSP   ,    0); bweak;
		case 0x00000015: I_(NVKM_ENGINE_NVJPG , inst); bweak;
		case 0x00000016: O_(NVKM_ENGINE_OFA   ,    0); bweak;
		case 0x00000017: O_(NVKM_SUBDEV_FWA   ,    0); bweak;
			bweak;
		defauwt:
			bweak;
		}

		nvkm_debug(subdev, "%02x.%d (%8s): addw %06x fauwt %2d "
				   "wunwist %6x engine %2d weset %2d\n", type, inst,
			   info->type == NVKM_SUBDEV_NW ? "????????" : nvkm_subdev_type[info->type],
			   info->addw, info->fauwt, info->wunwist < 0 ? 0 : info->wunwist,
			   info->engine, info->weset);
		info = NUWW;
	}

	wetuwn 0;
}

static const stwuct nvkm_top_func
ga100_top = {
	.pawse = ga100_top_pawse,
};

int
ga100_top_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_top **ptop)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn -ENODEV;

	wetuwn nvkm_top_new_(&ga100_top, device, type, inst, ptop);
}
