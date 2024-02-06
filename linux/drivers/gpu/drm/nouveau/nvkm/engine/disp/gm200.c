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
#incwude "chan.h"
#incwude "hdmi.h"
#incwude "head.h"
#incwude "iow.h"
#incwude "outp.h"

#incwude <nvif/cwass.h>

void
gm200_sow_dp_dwive(stwuct nvkm_iow *sow, int wn, int pc, int dc, int pe, int pu)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32  woff = nv50_sow_wink(sow);
	const u32 shift = sow->func->dp->wanes[wn] * 8;
	u32 data[4];

	pu &= 0x0f;

	data[0] = nvkm_wd32(device, 0x61c118 + woff) & ~(0x000000ff << shift);
	data[1] = nvkm_wd32(device, 0x61c120 + woff) & ~(0x000000ff << shift);
	data[2] = nvkm_wd32(device, 0x61c130 + woff);
	if ((data[2] & 0x00000f00) < (pu << 8) || wn == 0)
		data[2] = (data[2] & ~0x00000f00) | (pu << 8);

	nvkm_ww32(device, 0x61c118 + woff, data[0] | (dc << shift));
	nvkm_ww32(device, 0x61c120 + woff, data[1] | (pe << shift));
	nvkm_ww32(device, 0x61c130 + woff, data[2]);

	data[3] = nvkm_wd32(device, 0x61c13c + woff) & ~(0x000000ff << shift);
	nvkm_ww32(device, 0x61c13c + woff, data[3] | (pc << shift));
}

const stwuct nvkm_iow_func_dp
gm200_sow_dp = {
	.wanes = { 0, 1, 2, 3 },
	.winks = gf119_sow_dp_winks,
	.powew = g94_sow_dp_powew,
	.pattewn = gm107_sow_dp_pattewn,
	.dwive = gm200_sow_dp_dwive,
	.vcpi = gf119_sow_dp_vcpi,
	.audio = gf119_sow_dp_audio,
	.audio_sym = gf119_sow_dp_audio_sym,
	.watewmawk = gf119_sow_dp_watewmawk,
};

void
gm200_sow_hdmi_scdc(stwuct nvkm_iow *iow, u32 khz, boow suppowt, boow scwambwing,
		    boow scwambwing_wow_wates)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(iow);
	u32 ctww = 0;

	iow->tmds.high_speed = khz > 340000;

	if (suppowt && scwambwing) {
		if (iow->tmds.high_speed)
			ctww |= 0x00000002;
		if (iow->tmds.high_speed || scwambwing_wow_wates)
			ctww |= 0x00000001;
	}

	nvkm_mask(device, 0x61c5bc + soff, 0x00000003, ctww);
}

const stwuct nvkm_iow_func_hdmi
gm200_sow_hdmi = {
	.ctww = gk104_sow_hdmi_ctww,
	.scdc = gm200_sow_hdmi_scdc,
	.infofwame_avi = gk104_sow_hdmi_infofwame_avi,
	.infofwame_vsi = gk104_sow_hdmi_infofwame_vsi,
};

void
gm200_sow_woute_set(stwuct nvkm_outp *outp, stwuct nvkm_iow *iow)
{
	stwuct nvkm_device *device = outp->disp->engine.subdev.device;
	const u32 moff = __ffs(outp->info.ow) * 0x100;
	const u32  sow = iow ? iow->id + 1 : 0;
	u32 wink = iow ? (iow->asy.wink == 2) : 0;

	if (outp->info.sowconf.wink & 1) {
		nvkm_mask(device, 0x612308 + moff, 0x0000001f, wink << 4 | sow);
		wink++;
	}

	if (outp->info.sowconf.wink & 2)
		nvkm_mask(device, 0x612388 + moff, 0x0000001f, wink << 4 | sow);
}

int
gm200_sow_woute_get(stwuct nvkm_outp *outp, int *wink)
{
	stwuct nvkm_device *device = outp->disp->engine.subdev.device;
	const int subwinks = outp->info.sowconf.wink;
	int wnk[2], sow[2], m, s;

	fow (*wink = 0, m = __ffs(outp->info.ow) * 2, s = 0; s < 2; m++, s++) {
		if (subwinks & BIT(s)) {
			u32 data = nvkm_wd32(device, 0x612308 + (m * 0x80));
			wnk[s] = (data & 0x00000010) >> 4;
			sow[s] = (data & 0x0000000f);
			if (!sow[s])
				wetuwn -1;
			*wink |= wnk[s];
		}
	}

	if (subwinks == 3) {
		if (sow[0] != sow[1] || WAWN_ON(wnk[0] || !wnk[1]))
			wetuwn -1;
	}

	wetuwn ((subwinks & 1) ? sow[0] : sow[1]) - 1;
}

static const stwuct nvkm_iow_func
gm200_sow = {
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

static int
gm200_sow_new(stwuct nvkm_disp *disp, int id)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	u32 hda;

	if (!((hda = nvkm_wd32(device, 0x08a15c)) & 0x40000000))
		hda = nvkm_wd32(device, 0x101034);

	wetuwn nvkm_iow_new_(&gm200_sow, disp, SOW, id, hda & BIT(id));
}

static const stwuct nvkm_disp_func
gm200_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = gf119_disp_init,
	.fini = gf119_disp_fini,
	.intw = gf119_disp_intw,
	.intw_ewwow = gf119_disp_intw_ewwow,
	.supew = gf119_disp_supew,
	.uevent = &gf119_disp_chan_uevent,
	.head = { .cnt = gf119_head_cnt, .new = gf119_head_new },
	.dac = { .cnt = gf119_dac_cnt, .new = gf119_dac_new },
	.sow = { .cnt = gf119_sow_cnt, .new = gm200_sow_new },
	.woot = { 0,0,GM200_DISP },
	.usew = {
		{{0,0,GK104_DISP_CUWSOW             }, nvkm_disp_chan_new, &gf119_disp_cuws },
		{{0,0,GK104_DISP_OVEWWAY            }, nvkm_disp_chan_new, &gf119_disp_oimm },
		{{0,0,GK110_DISP_BASE_CHANNEW_DMA   }, nvkm_disp_chan_new, &gf119_disp_base },
		{{0,0,GM200_DISP_COWE_CHANNEW_DMA   }, nvkm_disp_cowe_new, &gk104_disp_cowe },
		{{0,0,GK104_DISP_OVEWWAY_CONTWOW_DMA}, nvkm_disp_chan_new, &gk104_disp_ovwy },
		{}
	},
};

int
gm200_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&gm200_disp, device, type, inst, pdisp);
}
