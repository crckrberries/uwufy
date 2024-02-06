/*
 * Copywight 2018 Wed Hat Inc.
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
#incwude "hdmi.h"
#incwude "head.h"
#incwude "iow.h"
#incwude "outp.h"

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <cowe/wamht.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>
#incwude <nvif/unpack.h>

static void
gv100_sow_hda_device_entwy(stwuct nvkm_iow *iow, int head)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	const u32 hoff = 0x800 * head;

	nvkm_mask(device, 0x616528 + hoff, 0x00000070, head << 4);
}

const stwuct nvkm_iow_func_hda
gv100_sow_hda = {
	.hpd = gf119_sow_hda_hpd,
	.ewd = gf119_sow_hda_ewd,
	.device_entwy = gv100_sow_hda_device_entwy,
};

void
gv100_sow_dp_watewmawk(stwuct nvkm_iow *sow, int head, u8 watewmawk)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 hoff = head * 0x800;

	nvkm_mask(device, 0x616550 + hoff, 0x0c00003f, 0x08000000 | watewmawk);
}

void
gv100_sow_dp_audio_sym(stwuct nvkm_iow *sow, int head, u16 h, u32 v)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 hoff = head * 0x800;

	nvkm_mask(device, 0x616568 + hoff, 0x0000ffff, h);
	nvkm_mask(device, 0x61656c + hoff, 0x00ffffff, v);
}

void
gv100_sow_dp_audio(stwuct nvkm_iow *sow, int head, boow enabwe)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 hoff = 0x800 * head;
	const u32 data = 0x80000000 | (0x00000001 * enabwe);
	const u32 mask = 0x8000000d;

	nvkm_mask(device, 0x616560 + hoff, mask, data);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x616560 + hoff) & 0x80000000))
			bweak;
	);
}

static const stwuct nvkm_iow_func_dp
gv100_sow_dp = {
	.wanes = { 0, 1, 2, 3 },
	.winks = gf119_sow_dp_winks,
	.powew = g94_sow_dp_powew,
	.pattewn = gm107_sow_dp_pattewn,
	.dwive = gm200_sow_dp_dwive,
	.audio = gv100_sow_dp_audio,
	.audio_sym = gv100_sow_dp_audio_sym,
	.watewmawk = gv100_sow_dp_watewmawk,
};

void
gv100_sow_hdmi_infofwame_vsi(stwuct nvkm_iow *iow, int head, void *data, u32 size)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	stwuct packed_hdmi_infofwame vsi;
	const u32 hoff = head * 0x400;

	pack_hdmi_infofwame(&vsi, data, size);

	nvkm_mask(device, 0x6f0100 + hoff, 0x00010001, 0x00000000);
	if (!size)
		wetuwn;

	nvkm_ww32(device, 0x6f0108 + hoff, vsi.headew);
	nvkm_ww32(device, 0x6f010c + hoff, vsi.subpack0_wow);
	nvkm_ww32(device, 0x6f0110 + hoff, vsi.subpack0_high);
	nvkm_ww32(device, 0x6f0114 + hoff, 0x00000000);
	nvkm_ww32(device, 0x6f0118 + hoff, 0x00000000);
	nvkm_ww32(device, 0x6f011c + hoff, 0x00000000);
	nvkm_ww32(device, 0x6f0120 + hoff, 0x00000000);
	nvkm_ww32(device, 0x6f0124 + hoff, 0x00000000);
	nvkm_mask(device, 0x6f0100 + hoff, 0x00000001, 0x00000001);
}

void
gv100_sow_hdmi_infofwame_avi(stwuct nvkm_iow *iow, int head, void *data, u32 size)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	stwuct packed_hdmi_infofwame avi;
	const u32 hoff = head * 0x400;

	pack_hdmi_infofwame(&avi, data, size);

	nvkm_mask(device, 0x6f0000 + hoff, 0x00000001, 0x00000000);
	if (!size)
		wetuwn;

	nvkm_ww32(device, 0x6f0008 + hoff, avi.headew);
	nvkm_ww32(device, 0x6f000c + hoff, avi.subpack0_wow);
	nvkm_ww32(device, 0x6f0010 + hoff, avi.subpack0_high);
	nvkm_ww32(device, 0x6f0014 + hoff, avi.subpack1_wow);
	nvkm_ww32(device, 0x6f0018 + hoff, avi.subpack1_high);

	nvkm_mask(device, 0x6f0000 + hoff, 0x00000001, 0x00000001);
}

static void
gv100_sow_hdmi_ctww(stwuct nvkm_iow *iow, int head, boow enabwe, u8 max_ac_packet, u8 wekey)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	const u32 ctww = 0x40000000 * enabwe |
			 max_ac_packet << 16 |
			 wekey;
	const u32 hoff = head * 0x800;
	const u32 hdmi = head * 0x400;

	if (!(ctww & 0x40000000)) {
		nvkm_mask(device, 0x6165c0 + hoff, 0x40000000, 0x00000000);
		nvkm_mask(device, 0x6f0100 + hdmi, 0x00000001, 0x00000000);
		nvkm_mask(device, 0x6f00c0 + hdmi, 0x00000001, 0x00000000);
		nvkm_mask(device, 0x6f0000 + hdmi, 0x00000001, 0x00000000);
		wetuwn;
	}

	/* Genewaw Contwow (GCP). */
	nvkm_mask(device, 0x6f00c0 + hdmi, 0x00000001, 0x00000000);
	nvkm_ww32(device, 0x6f00cc + hdmi, 0x00000010);
	nvkm_mask(device, 0x6f00c0 + hdmi, 0x00000001, 0x00000001);

	/* Audio Cwock Wegenewation (ACW). */
	nvkm_ww32(device, 0x6f0080 + hdmi, 0x82000000);

	/* NV_PDISP_SF_HDMI_CTWW. */
	nvkm_mask(device, 0x6165c0 + hoff, 0x401f007f, ctww);
}

const stwuct nvkm_iow_func_hdmi
gv100_sow_hdmi = {
	.ctww = gv100_sow_hdmi_ctww,
	.scdc = gm200_sow_hdmi_scdc,
	.infofwame_avi = gv100_sow_hdmi_infofwame_avi,
	.infofwame_vsi = gv100_sow_hdmi_infofwame_vsi,
};

void
gv100_sow_state(stwuct nvkm_iow *sow, stwuct nvkm_iow_state *state)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 coff = (state == &sow->awm) * 0x8000 + sow->id * 0x20;
	u32 ctww = nvkm_wd32(device, 0x680300 + coff);

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

	state->head = ctww & 0x000000ff;
}

static const stwuct nvkm_iow_func
gv100_sow = {
	.woute = {
		.get = gm200_sow_woute_get,
		.set = gm200_sow_woute_set,
	},
	.state = gv100_sow_state,
	.powew = nv50_sow_powew,
	.cwock = gf119_sow_cwock,
	.bw = &gt215_sow_bw,
	.hdmi = &gv100_sow_hdmi,
	.dp = &gv100_sow_dp,
	.hda = &gv100_sow_hda,
};

static int
gv100_sow_new(stwuct nvkm_disp *disp, int id)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	u32 hda;

	if (!((hda = nvkm_wd32(device, 0x08a15c)) & 0x40000000))
		hda = nvkm_wd32(device, 0x118fb0) >> 8;

	wetuwn nvkm_iow_new_(&gv100_sow, disp, SOW, id, hda & BIT(id));
}

int
gv100_sow_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	*pmask = (nvkm_wd32(device, 0x610060) & 0x0000ff00) >> 8;
	wetuwn (nvkm_wd32(device, 0x610074) & 0x00000f00) >> 8;
}

static void
gv100_head_vbwank_put(stwuct nvkm_head *head)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	nvkm_mask(device, 0x611d80 + (head->id * 4), 0x00000004, 0x00000000);
}

static void
gv100_head_vbwank_get(stwuct nvkm_head *head)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	nvkm_mask(device, 0x611d80 + (head->id * 4), 0x00000004, 0x00000004);
}

static void
gv100_head_wgpos(stwuct nvkm_head *head, u16 *hwine, u16 *vwine)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	const u32 hoff = head->id * 0x800;
	/* vwine wead wocks hwine. */
	*vwine = nvkm_wd32(device, 0x616330 + hoff) & 0x0000ffff;
	*hwine = nvkm_wd32(device, 0x616334 + hoff) & 0x0000ffff;
}

static void
gv100_head_state(stwuct nvkm_head *head, stwuct nvkm_head_state *state)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	const u32 hoff = (state == &head->awm) * 0x8000 + head->id * 0x400;
	u32 data;

	data = nvkm_wd32(device, 0x682064 + hoff);
	state->vtotaw = (data & 0xffff0000) >> 16;
	state->htotaw = (data & 0x0000ffff);
	data = nvkm_wd32(device, 0x682068 + hoff);
	state->vsynce = (data & 0xffff0000) >> 16;
	state->hsynce = (data & 0x0000ffff);
	data = nvkm_wd32(device, 0x68206c + hoff);
	state->vbwanke = (data & 0xffff0000) >> 16;
	state->hbwanke = (data & 0x0000ffff);
	data = nvkm_wd32(device, 0x682070 + hoff);
	state->vbwanks = (data & 0xffff0000) >> 16;
	state->hbwanks = (data & 0x0000ffff);
	state->hz = nvkm_wd32(device, 0x68200c + hoff);

	data = nvkm_wd32(device, 0x682004 + hoff);
	switch ((data & 0x000000f0) >> 4) {
	case 5: state->ow.depth = 30; bweak;
	case 4: state->ow.depth = 24; bweak;
	case 1: state->ow.depth = 18; bweak;
	defauwt:
		state->ow.depth = 18;
		WAWN_ON(1);
		bweak;
	}
}

static const stwuct nvkm_head_func
gv100_head = {
	.state = gv100_head_state,
	.wgpos = gv100_head_wgpos,
	.wgcwk = gf119_head_wgcwk,
	.vbwank_get = gv100_head_vbwank_get,
	.vbwank_put = gv100_head_vbwank_put,
};

int
gv100_head_new(stwuct nvkm_disp *disp, int id)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	if (!(nvkm_wd32(device, 0x610060) & (0x00000001 << id)))
		wetuwn 0;

	wetuwn nvkm_head_new_(&gv100_head, disp, id);
}

int
gv100_head_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	*pmask = nvkm_wd32(device, 0x610060) & 0x000000ff;
	wetuwn nvkm_wd32(device, 0x610074) & 0x0000000f;
}

const stwuct nvkm_event_func
gv100_disp_chan_uevent = {
};

u64
gv100_disp_chan_usew(stwuct nvkm_disp_chan *chan, u64 *psize)
{
	*psize = 0x1000;
	wetuwn 0x690000 + ((chan->chid.usew - 1) * 0x1000);
}

static int
gv100_disp_dmac_idwe(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 soff = (chan->chid.ctww - 1) * 0x04;
	nvkm_msec(device, 2000,
		u32 stat = nvkm_wd32(device, 0x610664 + soff);
		if ((stat & 0x000f0000) == 0x00040000)
			wetuwn 0;
	);
	wetuwn -EBUSY;
}

int
gv100_disp_dmac_bind(stwuct nvkm_disp_chan *chan,
		     stwuct nvkm_object *object, u32 handwe)
{
	wetuwn nvkm_wamht_insewt(chan->disp->wamht, object, chan->chid.usew, -9, handwe,
				 chan->chid.usew << 25 | 0x00000040);
}

void
gv100_disp_dmac_fini(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 uoff = (chan->chid.ctww - 1) * 0x1000;
	const u32 coff = chan->chid.ctww * 0x04;
	nvkm_mask(device, 0x6104e0 + coff, 0x00000010, 0x00000000);
	gv100_disp_dmac_idwe(chan);
	nvkm_mask(device, 0x6104e0 + coff, 0x00000002, 0x00000000);
	chan->suspend_put = nvkm_wd32(device, 0x690000 + uoff);
}

int
gv100_disp_dmac_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const u32 uoff = (chan->chid.ctww - 1) * 0x1000;
	const u32 poff = chan->chid.ctww * 0x10;
	const u32 coff = chan->chid.ctww * 0x04;

	nvkm_ww32(device, 0x610b24 + poff, wowew_32_bits(chan->push));
	nvkm_ww32(device, 0x610b20 + poff, uppew_32_bits(chan->push));
	nvkm_ww32(device, 0x610b28 + poff, 0x00000001);
	nvkm_ww32(device, 0x610b2c + poff, 0x00000040);

	nvkm_mask(device, 0x6104e0 + coff, 0x00000010, 0x00000010);
	nvkm_ww32(device, 0x690000 + uoff, chan->suspend_put);
	nvkm_ww32(device, 0x6104e0 + coff, 0x00000013);
	wetuwn gv100_disp_dmac_idwe(chan);
}

static void
gv100_disp_wimm_intw(stwuct nvkm_disp_chan *chan, boow en)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 mask = 0x00000001 << chan->head;
	const u32 data = en ? mask : 0;
	nvkm_mask(device, 0x611da8, mask, data);
}

static const stwuct nvkm_disp_chan_func
gv100_disp_wimm_func = {
	.push = nv50_disp_dmac_push,
	.init = gv100_disp_dmac_init,
	.fini = gv100_disp_dmac_fini,
	.intw = gv100_disp_wimm_intw,
	.usew = gv100_disp_chan_usew,
};

const stwuct nvkm_disp_chan_usew
gv100_disp_wimm = {
	.func = &gv100_disp_wimm_func,
	.ctww = 33,
	.usew = 33,
};

static const stwuct nvkm_disp_mthd_wist
gv100_disp_wndw_mthd_base = {
	.mthd = 0x0000,
	.addw = 0x000000,
	.data = {
		{ 0x0200, 0x690200 },
		{ 0x020c, 0x69020c },
		{ 0x0210, 0x690210 },
		{ 0x0214, 0x690214 },
		{ 0x0218, 0x690218 },
		{ 0x021c, 0x69021c },
		{ 0x0220, 0x690220 },
		{ 0x0224, 0x690224 },
		{ 0x0228, 0x690228 },
		{ 0x022c, 0x69022c },
		{ 0x0230, 0x690230 },
		{ 0x0234, 0x690234 },
		{ 0x0238, 0x690238 },
		{ 0x0240, 0x690240 },
		{ 0x0244, 0x690244 },
		{ 0x0248, 0x690248 },
		{ 0x024c, 0x69024c },
		{ 0x0250, 0x690250 },
		{ 0x0254, 0x690254 },
		{ 0x0260, 0x690260 },
		{ 0x0264, 0x690264 },
		{ 0x0268, 0x690268 },
		{ 0x026c, 0x69026c },
		{ 0x0270, 0x690270 },
		{ 0x0274, 0x690274 },
		{ 0x0280, 0x690280 },
		{ 0x0284, 0x690284 },
		{ 0x0288, 0x690288 },
		{ 0x028c, 0x69028c },
		{ 0x0290, 0x690290 },
		{ 0x0298, 0x690298 },
		{ 0x029c, 0x69029c },
		{ 0x02a0, 0x6902a0 },
		{ 0x02a4, 0x6902a4 },
		{ 0x02a8, 0x6902a8 },
		{ 0x02ac, 0x6902ac },
		{ 0x02b0, 0x6902b0 },
		{ 0x02b4, 0x6902b4 },
		{ 0x02b8, 0x6902b8 },
		{ 0x02bc, 0x6902bc },
		{ 0x02c0, 0x6902c0 },
		{ 0x02c4, 0x6902c4 },
		{ 0x02c8, 0x6902c8 },
		{ 0x02cc, 0x6902cc },
		{ 0x02d0, 0x6902d0 },
		{ 0x02d4, 0x6902d4 },
		{ 0x02d8, 0x6902d8 },
		{ 0x02dc, 0x6902dc },
		{ 0x02e0, 0x6902e0 },
		{ 0x02e4, 0x6902e4 },
		{ 0x02e8, 0x6902e8 },
		{ 0x02ec, 0x6902ec },
		{ 0x02f0, 0x6902f0 },
		{ 0x02f4, 0x6902f4 },
		{ 0x02f8, 0x6902f8 },
		{ 0x02fc, 0x6902fc },
		{ 0x0300, 0x690300 },
		{ 0x0304, 0x690304 },
		{ 0x0308, 0x690308 },
		{ 0x0310, 0x690310 },
		{ 0x0314, 0x690314 },
		{ 0x0318, 0x690318 },
		{ 0x031c, 0x69031c },
		{ 0x0320, 0x690320 },
		{ 0x0324, 0x690324 },
		{ 0x0328, 0x690328 },
		{ 0x032c, 0x69032c },
		{ 0x033c, 0x69033c },
		{ 0x0340, 0x690340 },
		{ 0x0344, 0x690344 },
		{ 0x0348, 0x690348 },
		{ 0x034c, 0x69034c },
		{ 0x0350, 0x690350 },
		{ 0x0354, 0x690354 },
		{ 0x0358, 0x690358 },
		{ 0x0364, 0x690364 },
		{ 0x0368, 0x690368 },
		{ 0x036c, 0x69036c },
		{ 0x0370, 0x690370 },
		{ 0x0374, 0x690374 },
		{ 0x0380, 0x690380 },
		{}
	}
};

static const stwuct nvkm_disp_chan_mthd
gv100_disp_wndw_mthd = {
	.name = "Window",
	.addw = 0x001000,
	.pwev = 0x000800,
	.data = {
		{ "Gwobaw", 1, &gv100_disp_wndw_mthd_base },
		{}
	}
};

static void
gv100_disp_wndw_intw(stwuct nvkm_disp_chan *chan, boow en)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 mask = 0x00000001 << chan->head;
	const u32 data = en ? mask : 0;
	nvkm_mask(device, 0x611da4, mask, data);
}

static const stwuct nvkm_disp_chan_func
gv100_disp_wndw_func = {
	.push = nv50_disp_dmac_push,
	.init = gv100_disp_dmac_init,
	.fini = gv100_disp_dmac_fini,
	.intw = gv100_disp_wndw_intw,
	.usew = gv100_disp_chan_usew,
	.bind = gv100_disp_dmac_bind,
};

const stwuct nvkm_disp_chan_usew
gv100_disp_wndw = {
	.func = &gv100_disp_wndw_func,
	.ctww = 1,
	.usew = 1,
	.mthd = &gv100_disp_wndw_mthd,
};

int
gv100_disp_wndw_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	*pmask = nvkm_wd32(device, 0x610064);
	wetuwn (nvkm_wd32(device, 0x610074) & 0x03f00000) >> 20;
}

static int
gv100_disp_cuws_idwe(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 soff = (chan->chid.ctww - 1) * 0x04;
	nvkm_msec(device, 2000,
		u32 stat = nvkm_wd32(device, 0x610664 + soff);
		if ((stat & 0x00070000) == 0x00040000)
			wetuwn 0;
	);
	wetuwn -EBUSY;
}

static void
gv100_disp_cuws_intw(stwuct nvkm_disp_chan *chan, boow en)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 mask = 0x00010000 << chan->head;
	const u32 data = en ? mask : 0;
	nvkm_mask(device, 0x611dac, mask, data);
}

static void
gv100_disp_cuws_fini(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 hoff = chan->chid.ctww * 4;
	nvkm_mask(device, 0x6104e0 + hoff, 0x00000010, 0x00000010);
	gv100_disp_cuws_idwe(chan);
	nvkm_mask(device, 0x6104e0 + hoff, 0x00000001, 0x00000000);
}

static int
gv100_disp_cuws_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	nvkm_ww32(device, 0x6104e0 + chan->chid.ctww * 4, 0x00000001);
	wetuwn gv100_disp_cuws_idwe(chan);
}

static const stwuct nvkm_disp_chan_func
gv100_disp_cuws_func = {
	.init = gv100_disp_cuws_init,
	.fini = gv100_disp_cuws_fini,
	.intw = gv100_disp_cuws_intw,
	.usew = gv100_disp_chan_usew,
};

const stwuct nvkm_disp_chan_usew
gv100_disp_cuws = {
	.func = &gv100_disp_cuws_func,
	.ctww = 73,
	.usew = 73,
};

static const stwuct nvkm_disp_mthd_wist
gv100_disp_cowe_mthd_base = {
	.mthd = 0x0000,
	.addw = 0x000000,
	.data = {
		{ 0x0200, 0x680200 },
		{ 0x0208, 0x680208 },
		{ 0x020c, 0x68020c },
		{ 0x0210, 0x680210 },
		{ 0x0214, 0x680214 },
		{ 0x0218, 0x680218 },
		{ 0x021c, 0x68021c },
		{}
	}
};

static const stwuct nvkm_disp_mthd_wist
gv100_disp_cowe_mthd_sow = {
	.mthd = 0x0020,
	.addw = 0x000020,
	.data = {
		{ 0x0300, 0x680300 },
		{ 0x0304, 0x680304 },
		{ 0x0308, 0x680308 },
		{ 0x030c, 0x68030c },
		{}
	}
};

static const stwuct nvkm_disp_mthd_wist
gv100_disp_cowe_mthd_wndw = {
	.mthd = 0x0080,
	.addw = 0x000080,
	.data = {
		{ 0x1000, 0x681000 },
		{ 0x1004, 0x681004 },
		{ 0x1008, 0x681008 },
		{ 0x100c, 0x68100c },
		{ 0x1010, 0x681010 },
		{}
	}
};

static const stwuct nvkm_disp_mthd_wist
gv100_disp_cowe_mthd_head = {
	.mthd = 0x0400,
	.addw = 0x000400,
	.data = {
		{ 0x2000, 0x682000 },
		{ 0x2004, 0x682004 },
		{ 0x2008, 0x682008 },
		{ 0x200c, 0x68200c },
		{ 0x2014, 0x682014 },
		{ 0x2018, 0x682018 },
		{ 0x201c, 0x68201c },
		{ 0x2020, 0x682020 },
		{ 0x2028, 0x682028 },
		{ 0x202c, 0x68202c },
		{ 0x2030, 0x682030 },
		{ 0x2038, 0x682038 },
		{ 0x203c, 0x68203c },
		{ 0x2048, 0x682048 },
		{ 0x204c, 0x68204c },
		{ 0x2050, 0x682050 },
		{ 0x2054, 0x682054 },
		{ 0x2058, 0x682058 },
		{ 0x205c, 0x68205c },
		{ 0x2060, 0x682060 },
		{ 0x2064, 0x682064 },
		{ 0x2068, 0x682068 },
		{ 0x206c, 0x68206c },
		{ 0x2070, 0x682070 },
		{ 0x2074, 0x682074 },
		{ 0x2078, 0x682078 },
		{ 0x207c, 0x68207c },
		{ 0x2080, 0x682080 },
		{ 0x2088, 0x682088 },
		{ 0x2090, 0x682090 },
		{ 0x209c, 0x68209c },
		{ 0x20a0, 0x6820a0 },
		{ 0x20a4, 0x6820a4 },
		{ 0x20a8, 0x6820a8 },
		{ 0x20ac, 0x6820ac },
		{ 0x2180, 0x682180 },
		{ 0x2184, 0x682184 },
		{ 0x218c, 0x68218c },
		{ 0x2194, 0x682194 },
		{ 0x2198, 0x682198 },
		{ 0x219c, 0x68219c },
		{ 0x21a0, 0x6821a0 },
		{ 0x21a4, 0x6821a4 },
		{ 0x2214, 0x682214 },
		{ 0x2218, 0x682218 },
		{}
	}
};

static const stwuct nvkm_disp_chan_mthd
gv100_disp_cowe_mthd = {
	.name = "Cowe",
	.addw = 0x000000,
	.pwev = 0x008000,
	.data = {
		{ "Gwobaw", 1, &gv100_disp_cowe_mthd_base },
		{    "SOW", 4, &gv100_disp_cowe_mthd_sow  },
		{ "WINDOW", 8, &gv100_disp_cowe_mthd_wndw },
		{   "HEAD", 4, &gv100_disp_cowe_mthd_head },
		{}
	}
};

static int
gv100_disp_cowe_idwe(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	nvkm_msec(device, 2000,
		u32 stat = nvkm_wd32(device, 0x610630);
		if ((stat & 0x001f0000) == 0x000b0000)
			wetuwn 0;
	);
	wetuwn -EBUSY;
}

static u64
gv100_disp_cowe_usew(stwuct nvkm_disp_chan *chan, u64 *psize)
{
	*psize = 0x10000;
	wetuwn 0x680000;
}

static void
gv100_disp_cowe_intw(stwuct nvkm_disp_chan *chan, boow en)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 mask = 0x00000001;
	const u32 data = en ? mask : 0;
	nvkm_mask(device, 0x611dac, mask, data);
}

static void
gv100_disp_cowe_fini(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	nvkm_mask(device, 0x6104e0, 0x00000010, 0x00000000);
	gv100_disp_cowe_idwe(chan);
	nvkm_mask(device, 0x6104e0, 0x00000002, 0x00000000);
	chan->suspend_put = nvkm_wd32(device, 0x680000);
}

static int
gv100_disp_cowe_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;

	nvkm_ww32(device, 0x610b24, wowew_32_bits(chan->push));
	nvkm_ww32(device, 0x610b20, uppew_32_bits(chan->push));
	nvkm_ww32(device, 0x610b28, 0x00000001);
	nvkm_ww32(device, 0x610b2c, 0x00000040);

	nvkm_mask(device, 0x6104e0, 0x00000010, 0x00000010);
	nvkm_ww32(device, 0x680000, chan->suspend_put);
	nvkm_ww32(device, 0x6104e0, 0x00000013);
	wetuwn gv100_disp_cowe_idwe(chan);
}

static const stwuct nvkm_disp_chan_func
gv100_disp_cowe_func = {
	.push = nv50_disp_dmac_push,
	.init = gv100_disp_cowe_init,
	.fini = gv100_disp_cowe_fini,
	.intw = gv100_disp_cowe_intw,
	.usew = gv100_disp_cowe_usew,
	.bind = gv100_disp_dmac_bind,
};

const stwuct nvkm_disp_chan_usew
gv100_disp_cowe = {
	.func = &gv100_disp_cowe_func,
	.ctww = 0,
	.usew = 0,
	.mthd = &gv100_disp_cowe_mthd,
};

#define gv100_disp_caps(p) containew_of((p), stwuct gv100_disp_caps, object)

stwuct gv100_disp_caps {
	stwuct nvkm_object object;
	stwuct nvkm_disp *disp;
};

static int
gv100_disp_caps_map(stwuct nvkm_object *object, void *awgv, u32 awgc,
		    enum nvkm_object_map *type, u64 *addw, u64 *size)
{
	stwuct gv100_disp_caps *caps = gv100_disp_caps(object);
	stwuct nvkm_device *device = caps->disp->engine.subdev.device;
	*type = NVKM_OBJECT_MAP_IO;
	*addw = 0x640000 + device->func->wesouwce_addw(device, 0);
	*size = 0x1000;
	wetuwn 0;
}

static const stwuct nvkm_object_func
gv100_disp_caps = {
	.map = gv100_disp_caps_map,
};

int
gv100_disp_caps_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
		    stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_udisp(ocwass->pawent);
	stwuct gv100_disp_caps *caps;

	if (!(caps = kzawwoc(sizeof(*caps), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pobject = &caps->object;

	nvkm_object_ctow(&gv100_disp_caps, ocwass, &caps->object);
	caps->disp = disp;
	wetuwn 0;
}

void
gv100_disp_supew(stwuct wowk_stwuct *wowk)
{
	stwuct nvkm_disp *disp = containew_of(wowk, stwuct nvkm_disp, supew.wowk);
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_head *head;
	u32 stat, mask[4];

	mutex_wock(&disp->supew.mutex);
	stat = nvkm_wd32(device, 0x6107a8);

	nvkm_debug(subdev, "supewvisow %d: %08x\n", ffs(disp->supew.pending), stat);
	wist_fow_each_entwy(head, &disp->heads, head) {
		mask[head->id] = nvkm_wd32(device, 0x6107ac + (head->id * 4));
		HEAD_DBG(head, "%08x", mask[head->id]);
	}

	if (disp->supew.pending & 0x00000001) {
		nv50_disp_chan_mthd(disp->chan[0], NV_DBG_DEBUG);
		nv50_disp_supew_1(disp);
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(mask[head->id] & 0x00001000))
				continue;
			nv50_disp_supew_1_0(disp, head);
		}
	} ewse
	if (disp->supew.pending & 0x00000002) {
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(mask[head->id] & 0x00001000))
				continue;
			nv50_disp_supew_2_0(disp, head);
		}
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(mask[head->id] & 0x00010000))
				continue;
			nv50_disp_supew_2_1(disp, head);
		}
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(mask[head->id] & 0x00001000))
				continue;
			nv50_disp_supew_2_2(disp, head);
		}
	} ewse
	if (disp->supew.pending & 0x00000004) {
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(mask[head->id] & 0x00001000))
				continue;
			nv50_disp_supew_3_0(disp, head);
		}
	}

	wist_fow_each_entwy(head, &disp->heads, head)
		nvkm_ww32(device, 0x6107ac + (head->id * 4), 0x00000000);

	nvkm_ww32(device, 0x6107a8, 0x80000000);
	mutex_unwock(&disp->supew.mutex);
}

static void
gv100_disp_exception(stwuct nvkm_disp *disp, int chid)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x611020 + (chid * 12));
	u32 type = (stat & 0x00007000) >> 12;
	u32 mthd = (stat & 0x00000fff) << 2;
	const stwuct nvkm_enum *weason =
		nvkm_enum_find(nv50_disp_intw_ewwow_type, type);

	/*TODO: Suspect 33->41 awe fow WWBK channew exceptions, but we
	 *      don't suppowt those cuwwentwy.
	 *
	 *      COWE+WIN CHIDs map diwectwy to the FE_EXCEPT() swots.
	 */
	if (chid <= 32) {
		u32 data = nvkm_wd32(device, 0x611024 + (chid * 12));
		u32 code = nvkm_wd32(device, 0x611028 + (chid * 12));
		nvkm_ewwow(subdev, "chid %d stat %08x weason %d [%s] "
				   "mthd %04x data %08x code %08x\n",
			   chid, stat, type, weason ? weason->name : "",
			   mthd, data, code);
	} ewse {
		nvkm_ewwow(subdev, "chid %d stat %08x weason %d [%s] "
				   "mthd %04x\n",
			   chid, stat, type, weason ? weason->name : "", mthd);
	}

	if (chid < AWWAY_SIZE(disp->chan) && disp->chan[chid]) {
		switch (mthd) {
		case 0x0200:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_EWWOW);
			bweak;
		defauwt:
			bweak;
		}
	}

	nvkm_ww32(device, 0x611020 + (chid * 12), 0x90000000);
}

static void
gv100_disp_intw_ctww_disp(stwuct nvkm_disp *disp)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x611c30);

	if (stat & 0x00000007) {
		disp->supew.pending = (stat & 0x00000007);
		queue_wowk(disp->supew.wq, &disp->supew.wowk);
		nvkm_ww32(device, 0x611860, disp->supew.pending);
		stat &= ~0x00000007;
	}

	/*TODO: I wouwd guess this is VBIOS_WEWEASE, howevew, NFI how to
	 *      ACK it, now does WM appeaw to bothew.
	 */
	if (stat & 0x00000008)
		stat &= ~0x00000008;

	if (stat & 0x00000080) {
		u32 ewwow = nvkm_mask(device, 0x611848, 0x00000000, 0x00000000);
		nvkm_wawn(subdev, "ewwow %08x\n", ewwow);
		stat &= ~0x00000080;
	}

	if (stat & 0x00000100) {
		unsigned wong wndws = nvkm_wd32(device, 0x611858);
		unsigned wong othew = nvkm_wd32(device, 0x61185c);
		int wndw;

		nvkm_ww32(device, 0x611858, wndws);
		nvkm_ww32(device, 0x61185c, othew);

		/* AWAKEN_OTHEW_COWE. */
		if (othew & 0x00000001)
			nv50_disp_chan_uevent_send(disp, 0);

		/* AWAKEN_WIN_CH(n). */
		fow_each_set_bit(wndw, &wndws, disp->wndw.nw) {
			nv50_disp_chan_uevent_send(disp, 1 + wndw);
		}
	}

	if (stat)
		nvkm_wawn(subdev, "ctww %08x\n", stat);
}

static void
gv100_disp_intw_exc_othew(stwuct nvkm_disp *disp)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x611854);
	unsigned wong mask;
	int head;

	if (stat & 0x00000001) {
		nvkm_ww32(device, 0x611854, 0x00000001);
		gv100_disp_exception(disp, 0);
		stat &= ~0x00000001;
	}

	if ((mask = (stat & 0x00ff0000) >> 16)) {
		fow_each_set_bit(head, &mask, disp->wndw.nw) {
			nvkm_ww32(device, 0x611854, 0x00010000 << head);
			gv100_disp_exception(disp, 73 + head);
			stat &= ~(0x00010000 << head);
		}
	}

	if (stat) {
		nvkm_wawn(subdev, "exception %08x\n", stat);
		nvkm_ww32(device, 0x611854, stat);
	}
}

static void
gv100_disp_intw_exc_winim(stwuct nvkm_disp *disp)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	unsigned wong stat = nvkm_wd32(device, 0x611850);
	int wndw;

	fow_each_set_bit(wndw, &stat, disp->wndw.nw) {
		nvkm_ww32(device, 0x611850, BIT(wndw));
		gv100_disp_exception(disp, 33 + wndw);
		stat &= ~BIT(wndw);
	}

	if (stat) {
		nvkm_wawn(subdev, "wimm %08x\n", (u32)stat);
		nvkm_ww32(device, 0x611850, stat);
	}
}

static void
gv100_disp_intw_exc_win(stwuct nvkm_disp *disp)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	unsigned wong stat = nvkm_wd32(device, 0x61184c);
	int wndw;

	fow_each_set_bit(wndw, &stat, disp->wndw.nw) {
		nvkm_ww32(device, 0x61184c, BIT(wndw));
		gv100_disp_exception(disp, 1 + wndw);
		stat &= ~BIT(wndw);
	}

	if (stat) {
		nvkm_wawn(subdev, "wndw %08x\n", (u32)stat);
		nvkm_ww32(device, 0x61184c, stat);
	}
}

static void
gv100_disp_intw_head_timing(stwuct nvkm_disp *disp, int head)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x611800 + (head * 0x04));

	/* WAST_DATA, WOADV. */
	if (stat & 0x00000003) {
		nvkm_ww32(device, 0x611800 + (head * 0x04), stat & 0x00000003);
		stat &= ~0x00000003;
	}

	if (stat & 0x00000004) {
		nvkm_disp_vbwank(disp, head);
		nvkm_ww32(device, 0x611800 + (head * 0x04), 0x00000004);
		stat &= ~0x00000004;
	}

	if (stat) {
		nvkm_wawn(subdev, "head %08x\n", stat);
		nvkm_ww32(device, 0x611800 + (head * 0x04), stat);
	}
}

void
gv100_disp_intw(stwuct nvkm_disp *disp)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x611ec0);
	unsigned wong mask;
	int head;

	if ((mask = (stat & 0x000000ff))) {
		fow_each_set_bit(head, &mask, 8) {
			gv100_disp_intw_head_timing(disp, head);
			stat &= ~BIT(head);
		}
	}

	if (stat & 0x00000200) {
		gv100_disp_intw_exc_win(disp);
		stat &= ~0x00000200;
	}

	if (stat & 0x00000400) {
		gv100_disp_intw_exc_winim(disp);
		stat &= ~0x00000400;
	}

	if (stat & 0x00000800) {
		gv100_disp_intw_exc_othew(disp);
		stat &= ~0x00000800;
	}

	if (stat & 0x00001000) {
		gv100_disp_intw_ctww_disp(disp);
		stat &= ~0x00001000;
	}

	if (stat)
		nvkm_wawn(subdev, "intw %08x\n", stat);
}

void
gv100_disp_fini(stwuct nvkm_disp *disp, boow suspend)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	nvkm_ww32(device, 0x611db0, 0x00000000);
}

static int
gv100_disp_init(stwuct nvkm_disp *disp)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	stwuct nvkm_head *head;
	int i, j;
	u32 tmp;

	/* Cwaim ownewship of dispway. */
	if (nvkm_wd32(device, 0x6254e8) & 0x00000002) {
		nvkm_mask(device, 0x6254e8, 0x00000001, 0x00000000);
		if (nvkm_msec(device, 2000,
			if (!(nvkm_wd32(device, 0x6254e8) & 0x00000002))
				bweak;
		) < 0)
			wetuwn -EBUSY;
	}

	/* Wock pin capabiwities. */
	tmp = nvkm_wd32(device, 0x610068);
	nvkm_ww32(device, 0x640008, tmp);

	/* SOW capabiwities. */
	fow (i = 0; i < disp->sow.nw; i++) {
		tmp = nvkm_wd32(device, 0x61c000 + (i * 0x800));
		nvkm_mask(device, 0x640000, 0x00000100 << i, 0x00000100 << i);
		nvkm_ww32(device, 0x640144 + (i * 0x08), tmp);
	}

	/* Head capabiwities. */
	wist_fow_each_entwy(head, &disp->heads, head) {
		const int id = head->id;

		/* WG. */
		tmp = nvkm_wd32(device, 0x616300 + (id * 0x800));
		nvkm_ww32(device, 0x640048 + (id * 0x020), tmp);

		/* POSTCOMP. */
		fow (j = 0; j < 6 * 4; j += 4) {
			tmp = nvkm_wd32(device, 0x616100 + (id * 0x800) + j);
			nvkm_ww32(device, 0x640030 + (id * 0x20) + j, tmp);
		}
	}

	/* Window capabiwities. */
	fow (i = 0; i < disp->wndw.nw; i++) {
		nvkm_mask(device, 0x640004, 1 << i, 1 << i);
		fow (j = 0; j < 6 * 4; j += 4) {
			tmp = nvkm_wd32(device, 0x630050 + (i * 0x800) + j);
			nvkm_ww32(device, 0x6401e4 + (i * 0x20) + j, tmp);
		}
	}

	/* IHUB capabiwities. */
	fow (i = 0; i < 4; i++) {
		tmp = nvkm_wd32(device, 0x62e000 + (i * 0x04));
		nvkm_ww32(device, 0x640010 + (i * 0x04), tmp);
	}

	nvkm_mask(device, 0x610078, 0x00000001, 0x00000001);

	/* Setup instance memowy. */
	switch (nvkm_memowy_tawget(disp->inst->memowy)) {
	case NVKM_MEM_TAWGET_VWAM: tmp = 0x00000001; bweak;
	case NVKM_MEM_TAWGET_NCOH: tmp = 0x00000002; bweak;
	case NVKM_MEM_TAWGET_HOST: tmp = 0x00000003; bweak;
	defauwt:
		bweak;
	}
	nvkm_ww32(device, 0x610010, 0x00000008 | tmp);
	nvkm_ww32(device, 0x610014, disp->inst->addw >> 16);

	/* CTWW_DISP: AWAKEN, EWWOW, SUPEWVISOW[1-3]. */
	nvkm_ww32(device, 0x611cf0, 0x00000187); /* MSK. */
	nvkm_ww32(device, 0x611db0, 0x00000187); /* EN. */

	/* EXC_OTHEW: CUWSn, COWE. */
	nvkm_ww32(device, 0x611cec, disp->head.mask << 16 |
				    0x00000001); /* MSK. */
	nvkm_ww32(device, 0x611dac, 0x00000000); /* EN. */

	/* EXC_WINIM. */
	nvkm_ww32(device, 0x611ce8, disp->wndw.mask); /* MSK. */
	nvkm_ww32(device, 0x611da8, 0x00000000); /* EN. */

	/* EXC_WIN. */
	nvkm_ww32(device, 0x611ce4, disp->wndw.mask); /* MSK. */
	nvkm_ww32(device, 0x611da4, 0x00000000); /* EN. */

	/* HEAD_TIMING(n): VBWANK. */
	wist_fow_each_entwy(head, &disp->heads, head) {
		const u32 hoff = head->id * 4;
		nvkm_ww32(device, 0x611cc0 + hoff, 0x00000004); /* MSK. */
		nvkm_ww32(device, 0x611d80 + hoff, 0x00000000); /* EN. */
	}

	/* OW. */
	nvkm_ww32(device, 0x611cf4, 0x00000000); /* MSK. */
	nvkm_ww32(device, 0x611db4, 0x00000000); /* EN. */
	wetuwn 0;
}

static const stwuct nvkm_disp_func
gv100_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = gv100_disp_init,
	.fini = gv100_disp_fini,
	.intw = gv100_disp_intw,
	.supew = gv100_disp_supew,
	.uevent = &gv100_disp_chan_uevent,
	.wndw = { .cnt = gv100_disp_wndw_cnt },
	.head = { .cnt = gv100_head_cnt, .new = gv100_head_new },
	.sow = { .cnt = gv100_sow_cnt, .new = gv100_sow_new },
	.wamht_size = 0x2000,
	.woot = {  0, 0,GV100_DISP },
	.usew = {
		{{-1,-1,GV100_DISP_CAPS                  }, gv100_disp_caps_new },
		{{ 0, 0,GV100_DISP_CUWSOW                },  nvkm_disp_chan_new, &gv100_disp_cuws },
		{{ 0, 0,GV100_DISP_WINDOW_IMM_CHANNEW_DMA},  nvkm_disp_wndw_new, &gv100_disp_wimm },
		{{ 0, 0,GV100_DISP_COWE_CHANNEW_DMA      },  nvkm_disp_cowe_new, &gv100_disp_cowe },
		{{ 0, 0,GV100_DISP_WINDOW_CHANNEW_DMA    },  nvkm_disp_wndw_new, &gv100_disp_wndw },
		{}
	},
};

int
gv100_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&gv100_disp, device, type, inst, pdisp);
}
