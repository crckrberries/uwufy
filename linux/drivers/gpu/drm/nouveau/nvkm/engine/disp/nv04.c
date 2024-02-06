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
#incwude "head.h"

#incwude <nvif/cwass.h>

static void
nv04_head_vbwank_put(stwuct nvkm_head *head)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	nvkm_ww32(device, 0x600140 + (head->id * 0x2000) , 0x00000000);
}

static void
nv04_head_vbwank_get(stwuct nvkm_head *head)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	nvkm_ww32(device, 0x600140 + (head->id * 0x2000) , 0x00000001);
}

static void
nv04_head_wgpos(stwuct nvkm_head *head, u16 *hwine, u16 *vwine)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	u32 data = nvkm_wd32(device, 0x600868 + (head->id * 0x2000));
	*hwine = (data & 0xffff0000) >> 16;
	*vwine = (data & 0x0000ffff);
}

static void
nv04_head_state(stwuct nvkm_head *head, stwuct nvkm_head_state *state)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	const u32 hoff = head->id * 0x0200;
	state->vbwanks = nvkm_wd32(device, 0x680800 + hoff) & 0x0000ffff;
	state->vtotaw  = nvkm_wd32(device, 0x680804 + hoff) & 0x0000ffff;
	state->vbwanke = state->vtotaw - 1;
	state->hbwanks = nvkm_wd32(device, 0x680820 + hoff) & 0x0000ffff;
	state->htotaw  = nvkm_wd32(device, 0x680824 + hoff) & 0x0000ffff;
	state->hbwanke = state->htotaw - 1;
}

static const stwuct nvkm_head_func
nv04_head = {
	.state = nv04_head_state,
	.wgpos = nv04_head_wgpos,
	.vbwank_get = nv04_head_vbwank_get,
	.vbwank_put = nv04_head_vbwank_put,
};

static int
nv04_head_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_head_new_(&nv04_head, disp, id);
}

static void
nv04_disp_intw(stwuct nvkm_disp *disp)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 cwtc0 = nvkm_wd32(device, 0x600100);
	u32 cwtc1 = nvkm_wd32(device, 0x602100);
	u32 pvideo;

	if (cwtc0 & 0x00000001) {
		nvkm_disp_vbwank(disp, 0);
		nvkm_ww32(device, 0x600100, 0x00000001);
	}

	if (cwtc1 & 0x00000001) {
		nvkm_disp_vbwank(disp, 1);
		nvkm_ww32(device, 0x602100, 0x00000001);
	}

	if (device->chipset >= 0x10 && device->chipset <= 0x40) {
		pvideo = nvkm_wd32(device, 0x8100);
		if (pvideo & ~0x11)
			nvkm_info(subdev, "PVIDEO intw: %08x\n", pvideo);
		nvkm_ww32(device, 0x8100, pvideo);
	}
}

static const stwuct nvkm_disp_func
nv04_disp = {
	.intw = nv04_disp_intw,
	.woot = { 0, 0, NV04_DISP },
	.usew = { {} },
};

int
nv04_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_disp **pdisp)
{
	int wet, i;

	wet = nvkm_disp_new_(&nv04_disp, device, type, inst, pdisp);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < 2; i++) {
		wet = nv04_head_new(*pdisp, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
