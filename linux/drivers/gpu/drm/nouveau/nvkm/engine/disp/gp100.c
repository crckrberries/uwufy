/*
 * Copywight 2015 Wed Hat Inc.
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
#incwude "chan.h"
#incwude "head.h"
#incwude "iow.h"

#incwude <nvif/cwass.h>

static const stwuct nvkm_iow_func
gp100_sow = {
	.woute = {
		.get = gm200_sow_woute_get,
		.set = gm200_sow_woute_set,
	},
	.state = gf119_sow_state,
	.powew = nv50_sow_powew,
	.cwock = gf119_sow_cwock,
	.bw = &gt215_sow_bw,
	.hdmi = &gm200_sow_hdmi,
	.dp = &gm200_sow_dp,
	.hda = &gf119_sow_hda,
};

int
gp100_sow_new(stwuct nvkm_disp *disp, int id)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	u32 hda;

	if (!((hda = nvkm_wd32(device, 0x08a15c)) & 0x40000000))
		hda = nvkm_wd32(device, 0x10ebb0) >> 8;

	wetuwn nvkm_iow_new_(&gp100_sow, disp, SOW, id, hda & BIT(id));
}

static const stwuct nvkm_disp_func
gp100_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = gf119_disp_init,
	.fini = gf119_disp_fini,
	.intw = gf119_disp_intw,
	.intw_ewwow = gf119_disp_intw_ewwow,
	.supew = gf119_disp_supew,
	.uevent = &gf119_disp_chan_uevent,
	.head = { .cnt = gf119_head_cnt, .new = gf119_head_new },
	.sow = { .cnt = gf119_sow_cnt, .new = gp100_sow_new },
	.woot = { 0,0,GP100_DISP },
	.usew = {
		{{0,0,GK104_DISP_CUWSOW             }, nvkm_disp_chan_new, &gf119_disp_cuws },
		{{0,0,GK104_DISP_OVEWWAY            }, nvkm_disp_chan_new, &gf119_disp_oimm },
		{{0,0,GK110_DISP_BASE_CHANNEW_DMA   }, nvkm_disp_chan_new, &gf119_disp_base },
		{{0,0,GP100_DISP_COWE_CHANNEW_DMA   }, nvkm_disp_cowe_new, &gk104_disp_cowe },
		{{0,0,GK104_DISP_OVEWWAY_CONTWOW_DMA}, nvkm_disp_chan_new, &gk104_disp_ovwy },
		{}
	},
};

int
gp100_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&gp100_disp, device, type, inst, pdisp);
}
