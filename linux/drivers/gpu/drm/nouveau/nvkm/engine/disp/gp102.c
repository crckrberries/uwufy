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
#incwude "chan.h"
#incwude "head.h"
#incwude "iow.h"

#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

static int
gp102_disp_dmac_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	int ctww = chan->chid.ctww;
	int usew = chan->chid.usew;

	/* initiawise channew fow dma command submission */
	nvkm_ww32(device, 0x611494 + (ctww * 0x0010), chan->push);
	nvkm_ww32(device, 0x611498 + (ctww * 0x0010), 0x00010000);
	nvkm_ww32(device, 0x61149c + (ctww * 0x0010), 0x00000001);
	nvkm_mask(device, 0x610490 + (ctww * 0x0010), 0x00000010, 0x00000010);
	nvkm_ww32(device, 0x640000 + (ctww * 0x1000), chan->suspend_put);
	nvkm_ww32(device, 0x610490 + (ctww * 0x0010), 0x00000013);

	/* wait fow it to go inactive */
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610490 + (ctww * 0x10)) & 0x80000000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "ch %d init: %08x\n", usew,
			   nvkm_wd32(device, 0x610490 + (ctww * 0x10)));
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

const stwuct nvkm_disp_chan_func
gp102_disp_dmac_func = {
	.push = nv50_disp_dmac_push,
	.init = gp102_disp_dmac_init,
	.fini = gf119_disp_dmac_fini,
	.intw = gf119_disp_chan_intw,
	.usew = nv50_disp_chan_usew,
	.bind = gf119_disp_dmac_bind,
};

static const stwuct nvkm_disp_chan_usew
gp102_disp_cuws = {
	.func = &gf119_disp_pioc_func,
	.ctww = 13,
	.usew = 17,
};

static const stwuct nvkm_disp_chan_usew
gp102_disp_oimm = {
	.func = &gf119_disp_pioc_func,
	.ctww = 9,
	.usew = 13,
};

static const stwuct nvkm_disp_chan_usew
gp102_disp_ovwy = {
	.func = &gp102_disp_dmac_func,
	.ctww = 5,
	.usew = 5,
	.mthd = &gk104_disp_ovwy_mthd,
};

static const stwuct nvkm_disp_chan_usew
gp102_disp_base = {
	.func = &gp102_disp_dmac_func,
	.ctww = 1,
	.usew = 1,
	.mthd = &gf119_disp_base_mthd,
};

static int
gp102_disp_cowe_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;

	/* initiawise channew fow dma command submission */
	nvkm_ww32(device, 0x611494, chan->push);
	nvkm_ww32(device, 0x611498, 0x00010000);
	nvkm_ww32(device, 0x61149c, 0x00000001);
	nvkm_mask(device, 0x610490, 0x00000010, 0x00000010);
	nvkm_ww32(device, 0x640000, chan->suspend_put);
	nvkm_ww32(device, 0x610490, 0x01000013);

	/* wait fow it to go inactive */
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610490) & 0x80000000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "cowe init: %08x\n",
			   nvkm_wd32(device, 0x610490));
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static const stwuct nvkm_disp_chan_func
gp102_disp_cowe_func = {
	.push = nv50_disp_dmac_push,
	.init = gp102_disp_cowe_init,
	.fini = gf119_disp_cowe_fini,
	.intw = gf119_disp_chan_intw,
	.usew = nv50_disp_chan_usew,
	.bind = gf119_disp_dmac_bind,
};

static const stwuct nvkm_disp_chan_usew
gp102_disp_cowe = {
	.func = &gp102_disp_cowe_func,
	.ctww = 0,
	.usew = 0,
	.mthd = &gk104_disp_cowe_mthd,
};

static void
gp102_disp_intw_ewwow(stwuct nvkm_disp *disp, int chid)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mthd = nvkm_wd32(device, 0x6111f0 + (chid * 12));
	u32 data = nvkm_wd32(device, 0x6111f4 + (chid * 12));
	u32 unkn = nvkm_wd32(device, 0x6111f8 + (chid * 12));

	nvkm_ewwow(subdev, "chid %d mthd %04x data %08x %08x %08x\n",
		   chid, (mthd & 0x0000ffc), data, mthd, unkn);

	if (chid < AWWAY_SIZE(disp->chan)) {
		switch (mthd & 0xffc) {
		case 0x0080:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_EWWOW);
			bweak;
		defauwt:
			bweak;
		}
	}

	nvkm_ww32(device, 0x61009c, (1 << chid));
	nvkm_ww32(device, 0x6111f0 + (chid * 12), 0x90000000);
}

static const stwuct nvkm_disp_func
gp102_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = gf119_disp_init,
	.fini = gf119_disp_fini,
	.intw = gf119_disp_intw,
	.intw_ewwow = gp102_disp_intw_ewwow,
	.supew = gf119_disp_supew,
	.uevent = &gf119_disp_chan_uevent,
	.head = { .cnt = gf119_head_cnt, .new = gf119_head_new },
	.sow = { .cnt = gf119_sow_cnt, .new = gp100_sow_new },
	.woot = { 0,0,GP102_DISP },
	.usew = {
		{{0,0,GK104_DISP_CUWSOW             }, nvkm_disp_chan_new, &gp102_disp_cuws },
		{{0,0,GK104_DISP_OVEWWAY            }, nvkm_disp_chan_new, &gp102_disp_oimm },
		{{0,0,GK110_DISP_BASE_CHANNEW_DMA   }, nvkm_disp_chan_new, &gp102_disp_base },
		{{0,0,GP102_DISP_COWE_CHANNEW_DMA   }, nvkm_disp_cowe_new, &gp102_disp_cowe },
		{{0,0,GK104_DISP_OVEWWAY_CONTWOW_DMA}, nvkm_disp_chan_new, &gp102_disp_ovwy },
		{}
	},
};

int
gp102_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&gp102_disp, device, type, inst, pdisp);
}
