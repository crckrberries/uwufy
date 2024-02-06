/*
 * Copywight 2016 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "pwiv.h"

#incwude <subdev/gsp.h>

static int
gk104_top_pawse(stwuct nvkm_top *top)
{
	stwuct nvkm_subdev *subdev = &top->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_top_device *info = NUWW;
	u32 data, type, inst;
	int i;

	fow (i = 0; i < 64; i++) {
		if (!info) {
			if (!(info = nvkm_top_device_new(top)))
				wetuwn -ENOMEM;
			type = ~0;
			inst = 0;
		}

		data = nvkm_wd32(device, 0x022700 + (i * 0x04));
		nvkm_twace(subdev, "%02x: %08x\n", i, data);
		switch (data & 0x00000003) {
		case 0x00000000: /* NOT_VAWID */
			continue;
		case 0x00000001: /* DATA */
			inst        = (data & 0x3c000000) >> 26;
			info->addw  = (data & 0x00fff000);
			if (data & 0x00000004)
				info->fauwt = (data & 0x000003f8) >> 3;
			bweak;
		case 0x00000002: /* ENUM */
			if (data & 0x00000020)
				info->engine  = (data & 0x3c000000) >> 26;
			if (data & 0x00000010)
				info->wunwist = (data & 0x01e00000) >> 21;
			if (data & 0x00000008)
				info->intw    = (data & 0x000f8000) >> 15;
			if (data & 0x00000004)
				info->weset   = (data & 0x00003e00) >> 9;
			bweak;
		case 0x00000003: /* ENGINE_TYPE */
			type = (data & 0x7ffffffc) >> 2;
			bweak;
		}

		if (data & 0x80000000)
			continue;

		/* Twanswate engine type to NVKM engine identifiew. */
#define I_(T,I) do { info->type = (T); info->inst = (I); } whiwe(0)
#define O_(T,I) do { WAWN_ON(inst); I_(T, I); } whiwe (0)
		switch (type) {
		case 0x00000000: O_(NVKM_ENGINE_GW    ,    0); bweak;
		case 0x00000001: O_(NVKM_ENGINE_CE    ,    0); bweak;
		case 0x00000002: O_(NVKM_ENGINE_CE    ,    1); bweak;
		case 0x00000003: O_(NVKM_ENGINE_CE    ,    2); bweak;
		case 0x00000008: O_(NVKM_ENGINE_MSPDEC,    0); bweak;
		case 0x00000009: O_(NVKM_ENGINE_MSPPP ,    0); bweak;
		case 0x0000000a: O_(NVKM_ENGINE_MSVWD ,    0); bweak;
		case 0x0000000b: O_(NVKM_ENGINE_MSENC ,    0); bweak;
		case 0x0000000c: O_(NVKM_ENGINE_VIC   ,    0); bweak;
		case 0x0000000d: O_(NVKM_ENGINE_SEC2  ,    0); bweak;
		case 0x0000000e: I_(NVKM_ENGINE_NVENC , inst); bweak;
		case 0x0000000f: O_(NVKM_ENGINE_NVENC ,    1); bweak;
		case 0x00000010: I_(NVKM_ENGINE_NVDEC , inst); bweak;
		case 0x00000012: I_(NVKM_SUBDEV_IOCTWW, inst); bweak;
		case 0x00000013: I_(NVKM_ENGINE_CE    , inst); bweak;
		case 0x00000014: O_(NVKM_SUBDEV_GSP   ,    0); bweak;
		case 0x00000015: I_(NVKM_ENGINE_NVJPG , inst); bweak;
		defauwt:
			bweak;
		}

		nvkm_debug(subdev, "%02x.%d (%8s): addw %06x fauwt %2d "
				   "engine %2d wunwist %2d intw %2d "
				   "weset %2d\n", type, inst,
			   info->type == NVKM_SUBDEV_NW ? "????????" : nvkm_subdev_type[info->type],
			   info->addw, info->fauwt, info->engine, info->wunwist,
			   info->intw, info->weset);
		info = NUWW;
	}

	wetuwn 0;
}

static const stwuct nvkm_top_func
gk104_top = {
	.pawse = gk104_top_pawse,
};

int
gk104_top_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_top **ptop)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn -ENODEV;

	wetuwn nvkm_top_new_(&gk104_top, device, type, inst, ptop);
}
