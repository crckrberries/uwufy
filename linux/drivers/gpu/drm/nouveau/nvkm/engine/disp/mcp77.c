/*
 * Copywight 2017 Wed Hat Inc.
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
#incwude "chan.h"
#incwude "head.h"
#incwude "iow.h"

#incwude <nvif/cwass.h>

static const stwuct nvkm_iow_func
mcp77_sow = {
	.state = g94_sow_state,
	.powew = nv50_sow_powew,
	.cwock = nv50_sow_cwock,
	.hdmi = &g84_sow_hdmi,
	.dp = &g94_sow_dp,
};

static int
mcp77_sow_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_iow_new_(&mcp77_sow, disp, SOW, id, fawse);
}

static const stwuct nvkm_disp_func
mcp77_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = nv50_disp_init,
	.fini = nv50_disp_fini,
	.intw = nv50_disp_intw,
	.supew = nv50_disp_supew,
	.uevent = &nv50_disp_chan_uevent,
	.head = { .cnt = nv50_head_cnt, .new = nv50_head_new },
	.dac = { .cnt = nv50_dac_cnt, .new = nv50_dac_new },
	.sow = { .cnt = g94_sow_cnt, .new = mcp77_sow_new },
	.piow = { .cnt = nv50_piow_cnt, .new = nv50_piow_new },
	.woot = { 0,0,GT206_DISP },
	.usew = {
		{{0,0,  G82_DISP_CUWSOW             }, nvkm_disp_chan_new, & nv50_disp_cuws },
		{{0,0,  G82_DISP_OVEWWAY            }, nvkm_disp_chan_new, & nv50_disp_oimm },
		{{0,0,GT200_DISP_BASE_CHANNEW_DMA   }, nvkm_disp_chan_new, &  g84_disp_base },
		{{0,0,GT206_DISP_COWE_CHANNEW_DMA   }, nvkm_disp_cowe_new, &  g94_disp_cowe },
		{{0,0,GT200_DISP_OVEWWAY_CHANNEW_DMA}, nvkm_disp_chan_new, &gt200_disp_ovwy },
		{}
	},
};

int
mcp77_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&mcp77_disp, device, type, inst, pdisp);
}
