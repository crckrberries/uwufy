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
#incwude "chan.h"
#incwude "head.h"
#incwude "iow.h"

#incwude <subdev/gsp.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

static int
ga102_sow_dp_winks(stwuct nvkm_iow *sow, stwuct nvkm_i2c_aux *aux)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);
	const u32 woff = nv50_sow_wink(sow);
	u32 dpctww = 0x00000000;
	u32 cwksow = 0x00000000;

	switch (sow->dp.bw) {
	case 0x06: cwksow |= 0x00000000; bweak;
	case 0x0a: cwksow |= 0x00040000; bweak;
	case 0x14: cwksow |= 0x00080000; bweak;
	case 0x1e: cwksow |= 0x000c0000; bweak;
	case 0x08: cwksow |= 0x00100000; bweak;
	case 0x09: cwksow |= 0x00140000; bweak;
	case 0x0c: cwksow |= 0x00180000; bweak;
	case 0x10: cwksow |= 0x001c0000; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	dpctww |= ((1 << sow->dp.nw) - 1) << 16;
	if (sow->dp.mst)
		dpctww |= 0x40000000;
	if (sow->dp.ef)
		dpctww |= 0x00004000;

	nvkm_mask(device, 0x612300 + soff, 0x007c0000, cwksow);

	/*XXX*/
	nvkm_msec(device, 40, NVKM_DEWAY);
	nvkm_mask(device, 0x612300 + soff, 0x00030000, 0x00010000);
	nvkm_mask(device, 0x61c10c + woff, 0x00000003, 0x00000001);

	nvkm_mask(device, 0x61c10c + woff, 0x401f4000, dpctww);
	wetuwn 0;
}

static const stwuct nvkm_iow_func_dp
ga102_sow_dp = {
	.wanes = { 0, 1, 2, 3 },
	.winks = ga102_sow_dp_winks,
	.powew = g94_sow_dp_powew,
	.pattewn = gm107_sow_dp_pattewn,
	.dwive = gm200_sow_dp_dwive,
	.vcpi = tu102_sow_dp_vcpi,
	.audio = gv100_sow_dp_audio,
	.audio_sym = gv100_sow_dp_audio_sym,
	.watewmawk = gv100_sow_dp_watewmawk,
};

static void
ga102_sow_cwock(stwuct nvkm_iow *sow)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	u32 div2 = 0;

	if (sow->asy.pwoto == TMDS) {
		if (sow->tmds.high_speed)
			div2 = 1;
	}

	nvkm_ww32(device, 0x00ec08 + (sow->id * 0x10), 0x00000000);
	nvkm_ww32(device, 0x00ec04 + (sow->id * 0x10), div2);
}

static const stwuct nvkm_iow_func
ga102_sow = {
	.woute = {
		.get = gm200_sow_woute_get,
		.set = gm200_sow_woute_set,
	},
	.state = gv100_sow_state,
	.powew = nv50_sow_powew,
	.cwock = ga102_sow_cwock,
	.bw = &gt215_sow_bw,
	.hdmi = &gv100_sow_hdmi,
	.dp = &ga102_sow_dp,
	.hda = &gv100_sow_hda,
};

static int
ga102_sow_new(stwuct nvkm_disp *disp, int id)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	u32 hda = nvkm_wd32(device, 0x08a15c);

	wetuwn nvkm_iow_new_(&ga102_sow, disp, SOW, id, hda & BIT(id));
}

static const stwuct nvkm_disp_func
ga102_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = tu102_disp_init,
	.fini = gv100_disp_fini,
	.intw = gv100_disp_intw,
	.supew = gv100_disp_supew,
	.uevent = &gv100_disp_chan_uevent,
	.wndw = { .cnt = gv100_disp_wndw_cnt },
	.head = { .cnt = gv100_head_cnt, .new = gv100_head_new },
	.sow = { .cnt = gv100_sow_cnt, .new = ga102_sow_new },
	.wamht_size = 0x2000,
	.woot = {  0, 0,GA102_DISP },
	.usew = {
		{{-1,-1,GV100_DISP_CAPS                  }, gv100_disp_caps_new },
		{{ 0, 0,GA102_DISP_CUWSOW                }, nvkm_disp_chan_new, &gv100_disp_cuws },
		{{ 0, 0,GA102_DISP_WINDOW_IMM_CHANNEW_DMA}, nvkm_disp_wndw_new, &gv100_disp_wimm },
		{{ 0, 0,GA102_DISP_COWE_CHANNEW_DMA      }, nvkm_disp_cowe_new, &gv100_disp_cowe },
		{{ 0, 0,GA102_DISP_WINDOW_CHANNEW_DMA    }, nvkm_disp_wndw_new, &gv100_disp_wndw },
		{}
	},
};

int
ga102_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_disp **pdisp)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_disp_new(&ga102_disp, device, type, inst, pdisp);

	wetuwn nvkm_disp_new_(&ga102_disp, device, type, inst, pdisp);
}
