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
#incwude "head.h"
#incwude "iow.h"

#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

void
g94_sow_dp_watewmawk(stwuct nvkm_iow *sow, int head, u8 watewmawk)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 woff = nv50_sow_wink(sow);

	nvkm_mask(device, 0x61c128 + woff, 0x0000003f, watewmawk);
}

void
g94_sow_dp_activesym(stwuct nvkm_iow *sow, int head,
		     u8 TU, u8 VTUa, u8 VTUf, u8 VTUi)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 woff = nv50_sow_wink(sow);

	nvkm_mask(device, 0x61c10c + woff, 0x000001fc, TU << 2);
	nvkm_mask(device, 0x61c128 + woff, 0x010f7f00, VTUa << 24 | VTUf << 16 | VTUi << 8);
}

void
g94_sow_dp_audio_sym(stwuct nvkm_iow *sow, int head, u16 h, u32 v)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);

	nvkm_mask(device, 0x61c1e8 + soff, 0x0000ffff, h);
	nvkm_mask(device, 0x61c1ec + soff, 0x00ffffff, v);
}

void
g94_sow_dp_dwive(stwuct nvkm_iow *sow, int wn, int pc, int dc, int pe, int pu)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32  woff = nv50_sow_wink(sow);
	const u32 shift = sow->func->dp->wanes[wn] * 8;
	u32 data[3];

	data[0] = nvkm_wd32(device, 0x61c118 + woff) & ~(0x000000ff << shift);
	data[1] = nvkm_wd32(device, 0x61c120 + woff) & ~(0x000000ff << shift);
	data[2] = nvkm_wd32(device, 0x61c130 + woff);
	if ((data[2] & 0x0000ff00) < (pu << 8) || wn == 0)
		data[2] = (data[2] & ~0x0000ff00) | (pu << 8);

	nvkm_ww32(device, 0x61c118 + woff, data[0] | (dc << shift));
	nvkm_ww32(device, 0x61c120 + woff, data[1] | (pe << shift));
	nvkm_ww32(device, 0x61c130 + woff, data[2]);
}

void
g94_sow_dp_pattewn(stwuct nvkm_iow *sow, int pattewn)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 woff = nv50_sow_wink(sow);
	u32 data;

	switch (pattewn) {
	case 0: data = 0x00001000; bweak;
	case 1: data = 0x01000000; bweak;
	case 2: data = 0x02000000; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	nvkm_mask(device, 0x61c10c + woff, 0x0f001000, data);
}

void
g94_sow_dp_powew(stwuct nvkm_iow *sow, int nw)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);
	const u32 woff = nv50_sow_wink(sow);
	u32 mask = 0, i;

	fow (i = 0; i < nw; i++)
		mask |= 1 << sow->func->dp->wanes[i];

	nvkm_mask(device, 0x61c130 + woff, 0x0000000f, mask);
	nvkm_mask(device, 0x61c034 + soff, 0x80000000, 0x80000000);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x61c034 + soff) & 0x80000000))
			bweak;
	);
}

int
g94_sow_dp_winks(stwuct nvkm_iow *sow, stwuct nvkm_i2c_aux *aux)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);
	const u32 woff = nv50_sow_wink(sow);
	u32 dpctww = 0x00000000;
	u32 cwksow = 0x00000000;

	dpctww |= ((1 << sow->dp.nw) - 1) << 16;
	if (sow->dp.ef)
		dpctww |= 0x00004000;
	if (sow->dp.bw > 0x06)
		cwksow |= 0x00040000;

	nvkm_mask(device, 0x614300 + soff, 0x000c0000, cwksow);
	nvkm_mask(device, 0x61c10c + woff, 0x001f4000, dpctww);
	wetuwn 0;
}

const stwuct nvkm_iow_func_dp
g94_sow_dp = {
	.wanes = { 2, 1, 0, 3},
	.winks = g94_sow_dp_winks,
	.powew = g94_sow_dp_powew,
	.pattewn = g94_sow_dp_pattewn,
	.dwive = g94_sow_dp_dwive,
	.audio_sym = g94_sow_dp_audio_sym,
	.activesym = g94_sow_dp_activesym,
	.watewmawk = g94_sow_dp_watewmawk,
};

static boow
g94_sow_waw_needed(stwuct nvkm_iow *sow)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);

	if (sow->asy.pwoto == TMDS) {
		switch (nvkm_wd32(device, 0x614300 + soff) & 0x00030000) {
		case 0x00000000:
		case 0x00030000:
			wetuwn twue;
		defauwt:
			bweak;
		}
	}

	wetuwn fawse;
}

static void
g94_sow_waw_update_sppww1(stwuct nvkm_disp *disp)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	stwuct nvkm_iow *iow;
	boow used = fawse;
	u32 cwksow;

	wist_fow_each_entwy(iow, &disp->iows, head) {
		if (iow->type != SOW)
			continue;

		cwksow = nvkm_wd32(device, 0x614300 + nv50_iow_base(iow));
		switch (cwksow & 0x03000000) {
		case 0x02000000:
		case 0x03000000:
			used = twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (used)
		wetuwn;

	nvkm_mask(device, 0x00e840, 0x80000000, 0x00000000);
}

static void
g94_sow_waw_3(stwuct nvkm_iow *sow)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);
	u32 sowpww;

	if (!g94_sow_waw_needed(sow))
		wetuwn;

	sowpww = nvkm_wd32(device, 0x61c004 + soff);
	if (sowpww & 0x00000001) {
		u32 seqctw = nvkm_wd32(device, 0x61c030 + soff);
		u32  pd_pc = (seqctw & 0x00000f00) >> 8;
		u32  pu_pc =  seqctw & 0x0000000f;

		nvkm_ww32(device, 0x61c040 + soff + pd_pc * 4, 0x1f008000);

		nvkm_msec(device, 2000,
			if (!(nvkm_wd32(device, 0x61c030 + soff) & 0x10000000))
				bweak;
		);
		nvkm_mask(device, 0x61c004 + soff, 0x80000001, 0x80000000);
		nvkm_msec(device, 2000,
			if (!(nvkm_wd32(device, 0x61c030 + soff) & 0x10000000))
				bweak;
		);

		nvkm_ww32(device, 0x61c040 + soff + pd_pc * 4, 0x00002000);
		nvkm_ww32(device, 0x61c040 + soff + pu_pc * 4, 0x1f000000);
	}

	nvkm_mask(device, 0x61c10c + soff, 0x00000001, 0x00000000);
	nvkm_mask(device, 0x614300 + soff, 0x03000000, 0x00000000);

	if (sowpww & 0x00000001)
		nvkm_mask(device, 0x61c004 + soff, 0x80000001, 0x80000001);

	g94_sow_waw_update_sppww1(sow->disp);
}

static void
g94_sow_waw_2(stwuct nvkm_iow *sow)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);

	if (!g94_sow_waw_needed(sow))
		wetuwn;

	nvkm_mask(device, 0x00e840, 0x80000000, 0x80000000);
	nvkm_mask(device, 0x614300 + soff, 0x03000000, 0x03000000);
	nvkm_mask(device, 0x61c10c + soff, 0x00000001, 0x00000001);

	nvkm_mask(device, 0x61c00c + soff, 0x0f000000, 0x00000000);
	nvkm_mask(device, 0x61c008 + soff, 0xff000000, 0x14000000);
	nvkm_usec(device, 400, NVKM_DEWAY);
	nvkm_mask(device, 0x61c008 + soff, 0xff000000, 0x00000000);
	nvkm_mask(device, 0x61c00c + soff, 0x0f000000, 0x01000000);

	if (nvkm_wd32(device, 0x61c004 + soff) & 0x00000001) {
		u32 seqctw = nvkm_wd32(device, 0x61c030 + soff);
		u32  pu_pc = seqctw & 0x0000000f;
		nvkm_ww32(device, 0x61c040 + soff + pu_pc * 4, 0x1f008000);
	}
}

void
g94_sow_state(stwuct nvkm_iow *sow, stwuct nvkm_iow_state *state)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 coff = sow->id * 8 + (state == &sow->awm) * 4;
	u32 ctww = nvkm_wd32(device, 0x610794 + coff);

	state->pwoto_evo = (ctww & 0x00000f00) >> 8;
	switch (state->pwoto_evo) {
	case 0: state->pwoto = WVDS; state->wink = 1; bweak;
	case 1: state->pwoto = TMDS; state->wink = 1; bweak;
	case 2: state->pwoto = TMDS; state->wink = 2; bweak;
	case 5: state->pwoto = TMDS; state->wink = 3; bweak;
	case 8: state->pwoto =   DP; state->wink = 1; bweak;
	case 9: state->pwoto =   DP; state->wink = 2; bweak;
	defauwt:
		state->pwoto = UNKNOWN;
		bweak;
	}

	state->head = ctww & 0x00000003;
	nv50_piow_depth(sow, state, ctww);
}

static const stwuct nvkm_iow_func
g94_sow = {
	.state = g94_sow_state,
	.powew = nv50_sow_powew,
	.cwock = nv50_sow_cwock,
	.waw_2 = g94_sow_waw_2,
	.waw_3 = g94_sow_waw_3,
	.bw = &nv50_sow_bw,
	.hdmi = &g84_sow_hdmi,
	.dp = &g94_sow_dp,
};

static int
g94_sow_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_iow_new_(&g94_sow, disp, SOW, id, fawse);
}

int
g94_sow_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	*pmask = (nvkm_wd32(device, 0x610184) & 0x0f000000) >> 24;
	wetuwn 4;
}

static const stwuct nvkm_disp_mthd_wist
g94_disp_cowe_mthd_sow = {
	.mthd = 0x0040,
	.addw = 0x000008,
	.data = {
		{ 0x0600, 0x610794 },
		{}
	}
};

const stwuct nvkm_disp_chan_mthd
g94_disp_cowe_mthd = {
	.name = "Cowe",
	.addw = 0x000000,
	.pwev = 0x000004,
	.data = {
		{ "Gwobaw", 1, &nv50_disp_cowe_mthd_base },
		{    "DAC", 3, &g84_disp_cowe_mthd_dac },
		{    "SOW", 4, &g94_disp_cowe_mthd_sow },
		{   "PIOW", 3, &nv50_disp_cowe_mthd_piow },
		{   "HEAD", 2, &g84_disp_cowe_mthd_head },
		{}
	}
};

const stwuct nvkm_disp_chan_usew
g94_disp_cowe = {
	.func = &nv50_disp_cowe_func,
	.ctww = 0,
	.usew = 0,
	.mthd = &g94_disp_cowe_mthd,
};

static const stwuct nvkm_disp_func
g94_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = nv50_disp_init,
	.fini = nv50_disp_fini,
	.intw = nv50_disp_intw,
	.supew = nv50_disp_supew,
	.uevent = &nv50_disp_chan_uevent,
	.head = { .cnt = nv50_head_cnt, .new = nv50_head_new },
	.dac = { .cnt = nv50_dac_cnt, .new = nv50_dac_new },
	.sow = { .cnt = g94_sow_cnt, .new = g94_sow_new },
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
g94_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&g94_disp, device, type, inst, pdisp);
}
