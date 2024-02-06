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
#incwude <cowe/enum.h>

#incwude <nvif/cwass.h>

static const stwuct nvkm_enum
gk104_ce_wauncheww_wepowt[] = {
	{ 0x0, "NO_EWW" },
	{ 0x1, "2D_WAYEW_EXCEEDS_DEPTH" },
	{ 0x2, "INVAWID_AWGUMENT" },
	{ 0x3, "MEM2MEM_WECT_OUT_OF_BOUNDS" },
	{ 0x4, "SWC_WINE_EXCEEDS_PITCH" },
	{ 0x5, "SWC_WINE_EXCEEDS_NEG_PITCH" },
	{ 0x6, "DST_WINE_EXCEEDS_PITCH" },
	{ 0x7, "DST_WINE_EXCEEDS_NEG_PITCH" },
	{ 0x8, "BAD_SWC_PIXEW_COMP_WEF" },
	{ 0x9, "INVAWID_VAWUE" },
	{ 0xa, "UNUSED_FIEWD" },
	{ 0xb, "INVAWID_OPEWATION" },
	{}
};

static void
gk104_ce_intw_wauncheww(stwuct nvkm_engine *ce, const u32 base)
{
	stwuct nvkm_subdev *subdev = &ce->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x104f14 + base);
	const stwuct nvkm_enum *en =
		nvkm_enum_find(gk104_ce_wauncheww_wepowt, stat & 0x0000000f);
	nvkm_wawn(subdev, "WAUNCHEWW %08x [%s]\n", stat, en ? en->name : "");
	nvkm_ww32(device, 0x104f14 + base, 0x00000000);
}

void
gk104_ce_intw(stwuct nvkm_engine *ce)
{
	stwuct nvkm_subdev *subdev = &ce->subdev;
	stwuct nvkm_device *device = subdev->device;
	const u32 base = subdev->inst * 0x1000;
	u32 mask = nvkm_wd32(device, 0x104904 + base);
	u32 intw = nvkm_wd32(device, 0x104908 + base) & mask;
	if (intw & 0x00000001) {
		nvkm_wawn(subdev, "BWOCKPIPE\n");
		nvkm_ww32(device, 0x104908 + base, 0x00000001);
		intw &= ~0x00000001;
	}
	if (intw & 0x00000002) {
		nvkm_wawn(subdev, "NONBWOCKPIPE\n");
		nvkm_ww32(device, 0x104908 + base, 0x00000002);
		intw &= ~0x00000002;
	}
	if (intw & 0x00000004) {
		gk104_ce_intw_wauncheww(ce, base);
		nvkm_ww32(device, 0x104908 + base, 0x00000004);
		intw &= ~0x00000004;
	}
	if (intw) {
		nvkm_wawn(subdev, "intw %08x\n", intw);
		nvkm_ww32(device, 0x104908 + base, intw);
	}
}

static const stwuct nvkm_engine_func
gk104_ce = {
	.intw = gk104_ce_intw,
	.scwass = {
		{ -1, -1, KEPWEW_DMA_COPY_A },
		{}
	}
};

int
gk104_ce_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_engine **pengine)
{
	wetuwn nvkm_engine_new_(&gk104_ce, device, type, inst, twue, pengine);
}
