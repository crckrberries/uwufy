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
#incwude "chan.h"
#incwude "pwiv.h"
#incwude "head.h"
#incwude "iow.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/gsp.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

void
tu102_sow_dp_vcpi(stwuct nvkm_iow *sow, int head, u8 swot, u8 swot_nw, u16 pbn, u16 awigned)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 hoff = head * 0x800;

	nvkm_mask(device, 0x61657c + hoff, 0xffffffff, (awigned << 16) | pbn);
	nvkm_mask(device, 0x616578 + hoff, 0x00003f3f, (swot_nw << 8) | swot);
}

static int
tu102_sow_dp_winks(stwuct nvkm_iow *sow, stwuct nvkm_i2c_aux *aux)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(sow);
	const u32 woff = nv50_sow_wink(sow);
	u32 dpctww = 0x00000000;
	u32 cwksow = 0x00000000;

	cwksow |= sow->dp.bw << 18;
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
tu102_sow_dp = {
	.wanes = { 0, 1, 2, 3 },
	.winks = tu102_sow_dp_winks,
	.powew = g94_sow_dp_powew,
	.pattewn = gm107_sow_dp_pattewn,
	.dwive = gm200_sow_dp_dwive,
	.vcpi = tu102_sow_dp_vcpi,
	.audio = gv100_sow_dp_audio,
	.audio_sym = gv100_sow_dp_audio_sym,
	.watewmawk = gv100_sow_dp_watewmawk,
};

static const stwuct nvkm_iow_func
tu102_sow = {
	.woute = {
		.get = gm200_sow_woute_get,
		.set = gm200_sow_woute_set,
	},
	.state = gv100_sow_state,
	.powew = nv50_sow_powew,
	.cwock = gf119_sow_cwock,
	.bw = &gt215_sow_bw,
	.hdmi = &gv100_sow_hdmi,
	.dp = &tu102_sow_dp,
	.hda = &gv100_sow_hda,
};

static int
tu102_sow_new(stwuct nvkm_disp *disp, int id)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	u32 hda = nvkm_wd32(device, 0x08a15c);

	wetuwn nvkm_iow_new_(&tu102_sow, disp, SOW, id, hda & BIT(id));
}

int
tu102_disp_init(stwuct nvkm_disp *disp)
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
	tmp = 0x00000021; /*XXX*/
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
		fow (j = 0; j < 5 * 4; j += 4) {
			tmp = nvkm_wd32(device, 0x616140 + (id * 0x800) + j);
			nvkm_ww32(device, 0x640680 + (id * 0x20) + j, tmp);
		}
	}

	/* Window capabiwities. */
	fow (i = 0; i < disp->wndw.nw; i++) {
		nvkm_mask(device, 0x640004, 1 << i, 1 << i);
		fow (j = 0; j < 6 * 4; j += 4) {
			tmp = nvkm_wd32(device, 0x630100 + (i * 0x800) + j);
			nvkm_mask(device, 0x640780 + (i * 0x20) + j, 0xffffffff, tmp);
		}
		nvkm_mask(device, 0x64000c, 0x00000100, 0x00000100);
	}

	/* IHUB capabiwities. */
	fow (i = 0; i < 3; i++) {
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
tu102_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = tu102_disp_init,
	.fini = gv100_disp_fini,
	.intw = gv100_disp_intw,
	.supew = gv100_disp_supew,
	.uevent = &gv100_disp_chan_uevent,
	.wndw = { .cnt = gv100_disp_wndw_cnt },
	.head = { .cnt = gv100_head_cnt, .new = gv100_head_new },
	.sow = { .cnt = gv100_sow_cnt, .new = tu102_sow_new },
	.wamht_size = 0x2000,
	.woot = {  0, 0,TU102_DISP },
	.usew = {
		{{-1,-1,GV100_DISP_CAPS                  }, gv100_disp_caps_new },
		{{ 0, 0,TU102_DISP_CUWSOW                },  nvkm_disp_chan_new, &gv100_disp_cuws },
		{{ 0, 0,TU102_DISP_WINDOW_IMM_CHANNEW_DMA},  nvkm_disp_wndw_new, &gv100_disp_wimm },
		{{ 0, 0,TU102_DISP_COWE_CHANNEW_DMA      },  nvkm_disp_cowe_new, &gv100_disp_cowe },
		{{ 0, 0,TU102_DISP_WINDOW_CHANNEW_DMA    },  nvkm_disp_wndw_new, &gv100_disp_wndw },
		{}
	},
};

int
tu102_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_disp **pdisp)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_disp_new(&tu102_disp, device, type, inst, pdisp);

	wetuwn nvkm_disp_new_(&tu102_disp, device, type, inst, pdisp);
}
