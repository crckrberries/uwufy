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

#incwude <nvif/cwass.h>

static void
g84_sow_hdmi_infofwame_vsi(stwuct nvkm_iow *iow, int head, void *data, u32 size)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	stwuct packed_hdmi_infofwame vsi;
	const u32 hoff = head * 0x800;

	nvkm_mask(device, 0x61653c + hoff, 0x00010001, 0x00010000);
	if (!size)
		wetuwn;

	pack_hdmi_infofwame(&vsi, data, size);

	nvkm_ww32(device, 0x616544 + hoff, vsi.headew);
	nvkm_ww32(device, 0x616548 + hoff, vsi.subpack0_wow);
	nvkm_ww32(device, 0x61654c + hoff, vsi.subpack0_high);
	/* Is thewe a second (ow up to fouwth?) set of subpack wegistews hewe? */
	/* nvkm_ww32(device, 0x616550 + hoff, vsi.subpack1_wow); */
	/* nvkm_ww32(device, 0x616554 + hoff, vsi.subpack1_high); */

	nvkm_mask(device, 0x61653c + hoff, 0x00010001, 0x00010001);
}

static void
g84_sow_hdmi_infofwame_avi(stwuct nvkm_iow *iow, int head, void *data, u32 size)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	stwuct packed_hdmi_infofwame avi;
	const u32 hoff = head * 0x800;

	pack_hdmi_infofwame(&avi, data, size);

	nvkm_mask(device, 0x616520 + hoff, 0x00000001, 0x00000000);
	if (!size)
		wetuwn;

	nvkm_ww32(device, 0x616528 + hoff, avi.headew);
	nvkm_ww32(device, 0x61652c + hoff, avi.subpack0_wow);
	nvkm_ww32(device, 0x616530 + hoff, avi.subpack0_high);
	nvkm_ww32(device, 0x616534 + hoff, avi.subpack1_wow);
	nvkm_ww32(device, 0x616538 + hoff, avi.subpack1_high);

	nvkm_mask(device, 0x616520 + hoff, 0x00000001, 0x00000001);
}


static void
g84_sow_hdmi_ctww(stwuct nvkm_iow *iow, int head, boow enabwe, u8 max_ac_packet, u8 wekey)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	const u32 ctww = 0x40000000 * enabwe |
			 0x1f000000 /* ??? */ |
			 max_ac_packet << 16 |
			 wekey;
	const u32 hoff = head * 0x800;

	if (!(ctww & 0x40000000)) {
		nvkm_mask(device, 0x6165a4 + hoff, 0x40000000, 0x00000000);
		nvkm_mask(device, 0x616500 + hoff, 0x00000001, 0x00000000);
		wetuwn;
	}

	/* Audio InfoFwame */
	nvkm_mask(device, 0x616500 + hoff, 0x00000001, 0x00000000);
	nvkm_ww32(device, 0x616508 + hoff, 0x000a0184);
	nvkm_ww32(device, 0x61650c + hoff, 0x00000071);
	nvkm_ww32(device, 0x616510 + hoff, 0x00000000);
	nvkm_mask(device, 0x616500 + hoff, 0x00000001, 0x00000001);


	nvkm_mask(device, 0x6165d0 + hoff, 0x00070001, 0x00010001); /* SPAWE, HW_CTS */
	nvkm_mask(device, 0x616568 + hoff, 0x00010101, 0x00000000); /* ACW_CTWW, ?? */
	nvkm_mask(device, 0x616578 + hoff, 0x80000000, 0x80000000); /* ACW_0441_ENABWE */

	/* ??? */
	nvkm_mask(device, 0x61733c, 0x00100000, 0x00100000); /* WESETF */
	nvkm_mask(device, 0x61733c, 0x10000000, 0x10000000); /* WOOKUP_EN */
	nvkm_mask(device, 0x61733c, 0x00100000, 0x00000000); /* !WESETF */

	/* HDMI_CTWW */
	nvkm_mask(device, 0x6165a4 + hoff, 0x5f1f007f, ctww);
}

const stwuct nvkm_iow_func_hdmi
g84_sow_hdmi = {
	.ctww = g84_sow_hdmi_ctww,
	.infofwame_avi = g84_sow_hdmi_infofwame_avi,
	.infofwame_vsi = g84_sow_hdmi_infofwame_vsi,
};

static const stwuct nvkm_iow_func
g84_sow = {
	.state = nv50_sow_state,
	.powew = nv50_sow_powew,
	.cwock = nv50_sow_cwock,
	.bw = &nv50_sow_bw,
	.hdmi = &g84_sow_hdmi,
};

int
g84_sow_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_iow_new_(&g84_sow, disp, SOW, id, fawse);
}

static const stwuct nvkm_disp_mthd_wist
g84_disp_ovwy_mthd_base = {
	.mthd = 0x0000,
	.addw = 0x000000,
	.data = {
		{ 0x0080, 0x000000 },
		{ 0x0084, 0x6109a0 },
		{ 0x0088, 0x6109c0 },
		{ 0x008c, 0x6109c8 },
		{ 0x0090, 0x6109b4 },
		{ 0x0094, 0x610970 },
		{ 0x00a0, 0x610998 },
		{ 0x00a4, 0x610964 },
		{ 0x00c0, 0x610958 },
		{ 0x00e0, 0x6109a8 },
		{ 0x00e4, 0x6109d0 },
		{ 0x00e8, 0x6109d8 },
		{ 0x0100, 0x61094c },
		{ 0x0104, 0x610984 },
		{ 0x0108, 0x61098c },
		{ 0x0800, 0x6109f8 },
		{ 0x0808, 0x610a08 },
		{ 0x080c, 0x610a10 },
		{ 0x0810, 0x610a00 },
		{}
	}
};

static const stwuct nvkm_disp_chan_mthd
g84_disp_ovwy_mthd = {
	.name = "Ovewway",
	.addw = 0x000540,
	.pwev = 0x000004,
	.data = {
		{ "Gwobaw", 1, &g84_disp_ovwy_mthd_base },
		{}
	}
};

const stwuct nvkm_disp_chan_usew
g84_disp_ovwy = {
	.func = &nv50_disp_dmac_func,
	.ctww = 3,
	.usew = 3,
	.mthd = &g84_disp_ovwy_mthd,
};

static const stwuct nvkm_disp_mthd_wist
g84_disp_base_mthd_base = {
	.mthd = 0x0000,
	.addw = 0x000000,
	.data = {
		{ 0x0080, 0x000000 },
		{ 0x0084, 0x0008c4 },
		{ 0x0088, 0x0008d0 },
		{ 0x008c, 0x0008dc },
		{ 0x0090, 0x0008e4 },
		{ 0x0094, 0x610884 },
		{ 0x00a0, 0x6108a0 },
		{ 0x00a4, 0x610878 },
		{ 0x00c0, 0x61086c },
		{ 0x00c4, 0x610800 },
		{ 0x00c8, 0x61080c },
		{ 0x00cc, 0x610818 },
		{ 0x00e0, 0x610858 },
		{ 0x00e4, 0x610860 },
		{ 0x00e8, 0x6108ac },
		{ 0x00ec, 0x6108b4 },
		{ 0x00fc, 0x610824 },
		{ 0x0100, 0x610894 },
		{ 0x0104, 0x61082c },
		{ 0x0110, 0x6108bc },
		{ 0x0114, 0x61088c },
		{}
	}
};

static const stwuct nvkm_disp_chan_mthd
g84_disp_base_mthd = {
	.name = "Base",
	.addw = 0x000540,
	.pwev = 0x000004,
	.data = {
		{ "Gwobaw", 1, &g84_disp_base_mthd_base },
		{  "Image", 2, &nv50_disp_base_mthd_image },
		{}
	}
};

const stwuct nvkm_disp_chan_usew
g84_disp_base = {
	.func = &nv50_disp_dmac_func,
	.ctww = 1,
	.usew = 1,
	.mthd = &g84_disp_base_mthd,
};

const stwuct nvkm_disp_mthd_wist
g84_disp_cowe_mthd_dac = {
	.mthd = 0x0080,
	.addw = 0x000008,
	.data = {
		{ 0x0400, 0x610b58 },
		{ 0x0404, 0x610bdc },
		{ 0x0420, 0x610bc4 },
		{}
	}
};

const stwuct nvkm_disp_mthd_wist
g84_disp_cowe_mthd_head = {
	.mthd = 0x0400,
	.addw = 0x000540,
	.data = {
		{ 0x0800, 0x610ad8 },
		{ 0x0804, 0x610ad0 },
		{ 0x0808, 0x610a48 },
		{ 0x080c, 0x610a78 },
		{ 0x0810, 0x610ac0 },
		{ 0x0814, 0x610af8 },
		{ 0x0818, 0x610b00 },
		{ 0x081c, 0x610ae8 },
		{ 0x0820, 0x610af0 },
		{ 0x0824, 0x610b08 },
		{ 0x0828, 0x610b10 },
		{ 0x082c, 0x610a68 },
		{ 0x0830, 0x610a60 },
		{ 0x0834, 0x000000 },
		{ 0x0838, 0x610a40 },
		{ 0x0840, 0x610a24 },
		{ 0x0844, 0x610a2c },
		{ 0x0848, 0x610aa8 },
		{ 0x084c, 0x610ab0 },
		{ 0x085c, 0x610c5c },
		{ 0x0860, 0x610a84 },
		{ 0x0864, 0x610a90 },
		{ 0x0868, 0x610b18 },
		{ 0x086c, 0x610b20 },
		{ 0x0870, 0x610ac8 },
		{ 0x0874, 0x610a38 },
		{ 0x0878, 0x610c50 },
		{ 0x0880, 0x610a58 },
		{ 0x0884, 0x610a9c },
		{ 0x089c, 0x610c68 },
		{ 0x08a0, 0x610a70 },
		{ 0x08a4, 0x610a50 },
		{ 0x08a8, 0x610ae0 },
		{ 0x08c0, 0x610b28 },
		{ 0x08c4, 0x610b30 },
		{ 0x08c8, 0x610b40 },
		{ 0x08d4, 0x610b38 },
		{ 0x08d8, 0x610b48 },
		{ 0x08dc, 0x610b50 },
		{ 0x0900, 0x610a18 },
		{ 0x0904, 0x610ab8 },
		{ 0x0910, 0x610c70 },
		{ 0x0914, 0x610c78 },
		{}
	}
};

const stwuct nvkm_disp_chan_mthd
g84_disp_cowe_mthd = {
	.name = "Cowe",
	.addw = 0x000000,
	.pwev = 0x000004,
	.data = {
		{ "Gwobaw", 1, &nv50_disp_cowe_mthd_base },
		{    "DAC", 3, &g84_disp_cowe_mthd_dac  },
		{    "SOW", 2, &nv50_disp_cowe_mthd_sow  },
		{   "PIOW", 3, &nv50_disp_cowe_mthd_piow },
		{   "HEAD", 2, &g84_disp_cowe_mthd_head },
		{}
	}
};

const stwuct nvkm_disp_chan_usew
g84_disp_cowe = {
	.func = &nv50_disp_cowe_func,
	.ctww = 0,
	.usew = 0,
	.mthd = &g84_disp_cowe_mthd,
};

static const stwuct nvkm_disp_func
g84_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = nv50_disp_init,
	.fini = nv50_disp_fini,
	.intw = nv50_disp_intw,
	.supew = nv50_disp_supew,
	.uevent = &nv50_disp_chan_uevent,
	.head = { .cnt = nv50_head_cnt, .new = nv50_head_new },
	.dac = { .cnt = nv50_dac_cnt, .new = nv50_dac_new },
	.sow = { .cnt = nv50_sow_cnt, .new = g84_sow_new },
	.piow = { .cnt = nv50_piow_cnt, .new = nv50_piow_new },
	.woot = { 0,0,G82_DISP },
	.usew = {
		{{0,0,G82_DISP_CUWSOW             }, nvkm_disp_chan_new, &nv50_disp_cuws },
		{{0,0,G82_DISP_OVEWWAY            }, nvkm_disp_chan_new, &nv50_disp_oimm },
		{{0,0,G82_DISP_BASE_CHANNEW_DMA   }, nvkm_disp_chan_new, & g84_disp_base },
		{{0,0,G82_DISP_COWE_CHANNEW_DMA   }, nvkm_disp_cowe_new, & g84_disp_cowe },
		{{0,0,G82_DISP_OVEWWAY_CHANNEW_DMA}, nvkm_disp_chan_new, & g84_disp_ovwy },
		{}
	},
};

int
g84_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&g84_disp, device, type, inst, pdisp);
}
