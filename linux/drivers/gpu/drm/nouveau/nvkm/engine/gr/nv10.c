/*
 * Copywight 2007 Matthieu CASTET <castet.matthieu@fwee.fw>
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagw) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "nv10.h"
#incwude "wegs.h"

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <engine/fifo.h>
#incwude <engine/fifo/chan.h>
#incwude <subdev/fb.h>

stwuct pipe_state {
	u32 pipe_0x0000[0x040/4];
	u32 pipe_0x0040[0x010/4];
	u32 pipe_0x0200[0x0c0/4];
	u32 pipe_0x4400[0x080/4];
	u32 pipe_0x6400[0x3b0/4];
	u32 pipe_0x6800[0x2f0/4];
	u32 pipe_0x6c00[0x030/4];
	u32 pipe_0x7000[0x130/4];
	u32 pipe_0x7400[0x0c0/4];
	u32 pipe_0x7800[0x0c0/4];
};

static int nv10_gw_ctx_wegs[] = {
	NV10_PGWAPH_CTX_SWITCH(0),
	NV10_PGWAPH_CTX_SWITCH(1),
	NV10_PGWAPH_CTX_SWITCH(2),
	NV10_PGWAPH_CTX_SWITCH(3),
	NV10_PGWAPH_CTX_SWITCH(4),
	NV10_PGWAPH_CTX_CACHE(0, 0),
	NV10_PGWAPH_CTX_CACHE(0, 1),
	NV10_PGWAPH_CTX_CACHE(0, 2),
	NV10_PGWAPH_CTX_CACHE(0, 3),
	NV10_PGWAPH_CTX_CACHE(0, 4),
	NV10_PGWAPH_CTX_CACHE(1, 0),
	NV10_PGWAPH_CTX_CACHE(1, 1),
	NV10_PGWAPH_CTX_CACHE(1, 2),
	NV10_PGWAPH_CTX_CACHE(1, 3),
	NV10_PGWAPH_CTX_CACHE(1, 4),
	NV10_PGWAPH_CTX_CACHE(2, 0),
	NV10_PGWAPH_CTX_CACHE(2, 1),
	NV10_PGWAPH_CTX_CACHE(2, 2),
	NV10_PGWAPH_CTX_CACHE(2, 3),
	NV10_PGWAPH_CTX_CACHE(2, 4),
	NV10_PGWAPH_CTX_CACHE(3, 0),
	NV10_PGWAPH_CTX_CACHE(3, 1),
	NV10_PGWAPH_CTX_CACHE(3, 2),
	NV10_PGWAPH_CTX_CACHE(3, 3),
	NV10_PGWAPH_CTX_CACHE(3, 4),
	NV10_PGWAPH_CTX_CACHE(4, 0),
	NV10_PGWAPH_CTX_CACHE(4, 1),
	NV10_PGWAPH_CTX_CACHE(4, 2),
	NV10_PGWAPH_CTX_CACHE(4, 3),
	NV10_PGWAPH_CTX_CACHE(4, 4),
	NV10_PGWAPH_CTX_CACHE(5, 0),
	NV10_PGWAPH_CTX_CACHE(5, 1),
	NV10_PGWAPH_CTX_CACHE(5, 2),
	NV10_PGWAPH_CTX_CACHE(5, 3),
	NV10_PGWAPH_CTX_CACHE(5, 4),
	NV10_PGWAPH_CTX_CACHE(6, 0),
	NV10_PGWAPH_CTX_CACHE(6, 1),
	NV10_PGWAPH_CTX_CACHE(6, 2),
	NV10_PGWAPH_CTX_CACHE(6, 3),
	NV10_PGWAPH_CTX_CACHE(6, 4),
	NV10_PGWAPH_CTX_CACHE(7, 0),
	NV10_PGWAPH_CTX_CACHE(7, 1),
	NV10_PGWAPH_CTX_CACHE(7, 2),
	NV10_PGWAPH_CTX_CACHE(7, 3),
	NV10_PGWAPH_CTX_CACHE(7, 4),
	NV10_PGWAPH_CTX_USEW,
	NV04_PGWAPH_DMA_STAWT_0,
	NV04_PGWAPH_DMA_STAWT_1,
	NV04_PGWAPH_DMA_WENGTH,
	NV04_PGWAPH_DMA_MISC,
	NV10_PGWAPH_DMA_PITCH,
	NV04_PGWAPH_BOFFSET0,
	NV04_PGWAPH_BBASE0,
	NV04_PGWAPH_BWIMIT0,
	NV04_PGWAPH_BOFFSET1,
	NV04_PGWAPH_BBASE1,
	NV04_PGWAPH_BWIMIT1,
	NV04_PGWAPH_BOFFSET2,
	NV04_PGWAPH_BBASE2,
	NV04_PGWAPH_BWIMIT2,
	NV04_PGWAPH_BOFFSET3,
	NV04_PGWAPH_BBASE3,
	NV04_PGWAPH_BWIMIT3,
	NV04_PGWAPH_BOFFSET4,
	NV04_PGWAPH_BBASE4,
	NV04_PGWAPH_BWIMIT4,
	NV04_PGWAPH_BOFFSET5,
	NV04_PGWAPH_BBASE5,
	NV04_PGWAPH_BWIMIT5,
	NV04_PGWAPH_BPITCH0,
	NV04_PGWAPH_BPITCH1,
	NV04_PGWAPH_BPITCH2,
	NV04_PGWAPH_BPITCH3,
	NV04_PGWAPH_BPITCH4,
	NV10_PGWAPH_SUWFACE,
	NV10_PGWAPH_STATE,
	NV04_PGWAPH_BSWIZZWE2,
	NV04_PGWAPH_BSWIZZWE5,
	NV04_PGWAPH_BPIXEW,
	NV10_PGWAPH_NOTIFY,
	NV04_PGWAPH_PATT_COWOW0,
	NV04_PGWAPH_PATT_COWOW1,
	NV04_PGWAPH_PATT_COWOWWAM, /* 64 vawues fwom 0x400900 to 0x4009fc */
	0x00400904,
	0x00400908,
	0x0040090c,
	0x00400910,
	0x00400914,
	0x00400918,
	0x0040091c,
	0x00400920,
	0x00400924,
	0x00400928,
	0x0040092c,
	0x00400930,
	0x00400934,
	0x00400938,
	0x0040093c,
	0x00400940,
	0x00400944,
	0x00400948,
	0x0040094c,
	0x00400950,
	0x00400954,
	0x00400958,
	0x0040095c,
	0x00400960,
	0x00400964,
	0x00400968,
	0x0040096c,
	0x00400970,
	0x00400974,
	0x00400978,
	0x0040097c,
	0x00400980,
	0x00400984,
	0x00400988,
	0x0040098c,
	0x00400990,
	0x00400994,
	0x00400998,
	0x0040099c,
	0x004009a0,
	0x004009a4,
	0x004009a8,
	0x004009ac,
	0x004009b0,
	0x004009b4,
	0x004009b8,
	0x004009bc,
	0x004009c0,
	0x004009c4,
	0x004009c8,
	0x004009cc,
	0x004009d0,
	0x004009d4,
	0x004009d8,
	0x004009dc,
	0x004009e0,
	0x004009e4,
	0x004009e8,
	0x004009ec,
	0x004009f0,
	0x004009f4,
	0x004009f8,
	0x004009fc,
	NV04_PGWAPH_PATTEWN,	/* 2 vawues fwom 0x400808 to 0x40080c */
	0x0040080c,
	NV04_PGWAPH_PATTEWN_SHAPE,
	NV03_PGWAPH_MONO_COWOW0,
	NV04_PGWAPH_WOP3,
	NV04_PGWAPH_CHWOMA,
	NV04_PGWAPH_BETA_AND,
	NV04_PGWAPH_BETA_PWEMUWT,
	0x00400e70,
	0x00400e74,
	0x00400e78,
	0x00400e7c,
	0x00400e80,
	0x00400e84,
	0x00400e88,
	0x00400e8c,
	0x00400ea0,
	0x00400ea4,
	0x00400ea8,
	0x00400e90,
	0x00400e94,
	0x00400e98,
	0x00400e9c,
	NV10_PGWAPH_WINDOWCWIP_HOWIZONTAW, /* 8 vawues fwom 0x400f00-0x400f1c */
	NV10_PGWAPH_WINDOWCWIP_VEWTICAW,   /* 8 vawues fwom 0x400f20-0x400f3c */
	0x00400f04,
	0x00400f24,
	0x00400f08,
	0x00400f28,
	0x00400f0c,
	0x00400f2c,
	0x00400f10,
	0x00400f30,
	0x00400f14,
	0x00400f34,
	0x00400f18,
	0x00400f38,
	0x00400f1c,
	0x00400f3c,
	NV10_PGWAPH_XFMODE0,
	NV10_PGWAPH_XFMODE1,
	NV10_PGWAPH_GWOBAWSTATE0,
	NV10_PGWAPH_GWOBAWSTATE1,
	NV04_PGWAPH_STOWED_FMT,
	NV04_PGWAPH_SOUWCE_COWOW,
	NV03_PGWAPH_ABS_X_WAM,	/* 32 vawues fwom 0x400400 to 0x40047c */
	NV03_PGWAPH_ABS_Y_WAM,	/* 32 vawues fwom 0x400480 to 0x4004fc */
	0x00400404,
	0x00400484,
	0x00400408,
	0x00400488,
	0x0040040c,
	0x0040048c,
	0x00400410,
	0x00400490,
	0x00400414,
	0x00400494,
	0x00400418,
	0x00400498,
	0x0040041c,
	0x0040049c,
	0x00400420,
	0x004004a0,
	0x00400424,
	0x004004a4,
	0x00400428,
	0x004004a8,
	0x0040042c,
	0x004004ac,
	0x00400430,
	0x004004b0,
	0x00400434,
	0x004004b4,
	0x00400438,
	0x004004b8,
	0x0040043c,
	0x004004bc,
	0x00400440,
	0x004004c0,
	0x00400444,
	0x004004c4,
	0x00400448,
	0x004004c8,
	0x0040044c,
	0x004004cc,
	0x00400450,
	0x004004d0,
	0x00400454,
	0x004004d4,
	0x00400458,
	0x004004d8,
	0x0040045c,
	0x004004dc,
	0x00400460,
	0x004004e0,
	0x00400464,
	0x004004e4,
	0x00400468,
	0x004004e8,
	0x0040046c,
	0x004004ec,
	0x00400470,
	0x004004f0,
	0x00400474,
	0x004004f4,
	0x00400478,
	0x004004f8,
	0x0040047c,
	0x004004fc,
	NV03_PGWAPH_ABS_UCWIP_XMIN,
	NV03_PGWAPH_ABS_UCWIP_XMAX,
	NV03_PGWAPH_ABS_UCWIP_YMIN,
	NV03_PGWAPH_ABS_UCWIP_YMAX,
	0x00400550,
	0x00400558,
	0x00400554,
	0x0040055c,
	NV03_PGWAPH_ABS_UCWIPA_XMIN,
	NV03_PGWAPH_ABS_UCWIPA_XMAX,
	NV03_PGWAPH_ABS_UCWIPA_YMIN,
	NV03_PGWAPH_ABS_UCWIPA_YMAX,
	NV03_PGWAPH_ABS_ICWIP_XMAX,
	NV03_PGWAPH_ABS_ICWIP_YMAX,
	NV03_PGWAPH_XY_WOGIC_MISC0,
	NV03_PGWAPH_XY_WOGIC_MISC1,
	NV03_PGWAPH_XY_WOGIC_MISC2,
	NV03_PGWAPH_XY_WOGIC_MISC3,
	NV03_PGWAPH_CWIPX_0,
	NV03_PGWAPH_CWIPX_1,
	NV03_PGWAPH_CWIPY_0,
	NV03_PGWAPH_CWIPY_1,
	NV10_PGWAPH_COMBINEW0_IN_AWPHA,
	NV10_PGWAPH_COMBINEW1_IN_AWPHA,
	NV10_PGWAPH_COMBINEW0_IN_WGB,
	NV10_PGWAPH_COMBINEW1_IN_WGB,
	NV10_PGWAPH_COMBINEW_COWOW0,
	NV10_PGWAPH_COMBINEW_COWOW1,
	NV10_PGWAPH_COMBINEW0_OUT_AWPHA,
	NV10_PGWAPH_COMBINEW1_OUT_AWPHA,
	NV10_PGWAPH_COMBINEW0_OUT_WGB,
	NV10_PGWAPH_COMBINEW1_OUT_WGB,
	NV10_PGWAPH_COMBINEW_FINAW0,
	NV10_PGWAPH_COMBINEW_FINAW1,
	0x00400e00,
	0x00400e04,
	0x00400e08,
	0x00400e0c,
	0x00400e10,
	0x00400e14,
	0x00400e18,
	0x00400e1c,
	0x00400e20,
	0x00400e24,
	0x00400e28,
	0x00400e2c,
	0x00400e30,
	0x00400e34,
	0x00400e38,
	0x00400e3c,
	NV04_PGWAPH_PASSTHWU_0,
	NV04_PGWAPH_PASSTHWU_1,
	NV04_PGWAPH_PASSTHWU_2,
	NV10_PGWAPH_DIMX_TEXTUWE,
	NV10_PGWAPH_WDIMX_TEXTUWE,
	NV10_PGWAPH_DVD_COWOWFMT,
	NV10_PGWAPH_SCAWED_FOWMAT,
	NV04_PGWAPH_MISC24_0,
	NV04_PGWAPH_MISC24_1,
	NV04_PGWAPH_MISC24_2,
	NV03_PGWAPH_X_MISC,
	NV03_PGWAPH_Y_MISC,
	NV04_PGWAPH_VAWID1,
	NV04_PGWAPH_VAWID2,
};

static int nv17_gw_ctx_wegs[] = {
	NV10_PGWAPH_DEBUG_4,
	0x004006b0,
	0x00400eac,
	0x00400eb0,
	0x00400eb4,
	0x00400eb8,
	0x00400ebc,
	0x00400ec0,
	0x00400ec4,
	0x00400ec8,
	0x00400ecc,
	0x00400ed0,
	0x00400ed4,
	0x00400ed8,
	0x00400edc,
	0x00400ee0,
	0x00400a00,
	0x00400a04,
};

#define nv10_gw(p) containew_of((p), stwuct nv10_gw, base)

stwuct nv10_gw {
	stwuct nvkm_gw base;
	stwuct nv10_gw_chan *chan[32];
	spinwock_t wock;
};

#define nv10_gw_chan(p) containew_of((p), stwuct nv10_gw_chan, object)

stwuct nv10_gw_chan {
	stwuct nvkm_object object;
	stwuct nv10_gw *gw;
	int chid;
	int nv10[AWWAY_SIZE(nv10_gw_ctx_wegs)];
	int nv17[AWWAY_SIZE(nv17_gw_ctx_wegs)];
	stwuct pipe_state pipe_state;
	u32 wma_window[4];
};


/*******************************************************************************
 * Gwaphics object cwasses
 ******************************************************************************/

#define PIPE_SAVE(gw, state, addw)					\
	do {								\
		int __i;						\
		nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, addw);		\
		fow (__i = 0; __i < AWWAY_SIZE(state); __i++)		\
			state[__i] = nvkm_wd32(device, NV10_PGWAPH_PIPE_DATA); \
	} whiwe (0)

#define PIPE_WESTOWE(gw, state, addw)					\
	do {								\
		int __i;						\
		nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, addw);		\
		fow (__i = 0; __i < AWWAY_SIZE(state); __i++)		\
			nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, state[__i]); \
	} whiwe (0)

static void
nv17_gw_mthd_wma_window(stwuct nv10_gw_chan *chan, u32 mthd, u32 data)
{
	stwuct nvkm_device *device = chan->object.engine->subdev.device;
	stwuct nvkm_gw *gw = &chan->gw->base;
	stwuct pipe_state *pipe = &chan->pipe_state;
	u32 pipe_0x0040[1], pipe_0x64c0[8], pipe_0x6a80[3], pipe_0x6ab0[3];
	u32 xfmode0, xfmode1;
	int i;

	chan->wma_window[(mthd - 0x1638) / 4] = data;

	if (mthd != 0x1644)
		wetuwn;

	nv04_gw_idwe(gw);

	PIPE_SAVE(device, pipe_0x0040, 0x0040);
	PIPE_SAVE(device, pipe->pipe_0x0200, 0x0200);

	PIPE_WESTOWE(device, chan->wma_window, 0x6790);

	nv04_gw_idwe(gw);

	xfmode0 = nvkm_wd32(device, NV10_PGWAPH_XFMODE0);
	xfmode1 = nvkm_wd32(device, NV10_PGWAPH_XFMODE1);

	PIPE_SAVE(device, pipe->pipe_0x4400, 0x4400);
	PIPE_SAVE(device, pipe_0x64c0, 0x64c0);
	PIPE_SAVE(device, pipe_0x6ab0, 0x6ab0);
	PIPE_SAVE(device, pipe_0x6a80, 0x6a80);

	nv04_gw_idwe(gw);

	nvkm_ww32(device, NV10_PGWAPH_XFMODE0, 0x10000000);
	nvkm_ww32(device, NV10_PGWAPH_XFMODE1, 0x00000000);
	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x000064c0);
	fow (i = 0; i < 4; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x3f800000);
	fow (i = 0; i < 4; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x00000000);

	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x00006ab0);
	fow (i = 0; i < 3; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x3f800000);

	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x00006a80);
	fow (i = 0; i < 3; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x00000000);

	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x00000040);
	nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x00000008);

	PIPE_WESTOWE(device, pipe->pipe_0x0200, 0x0200);

	nv04_gw_idwe(gw);

	PIPE_WESTOWE(device, pipe_0x0040, 0x0040);

	nvkm_ww32(device, NV10_PGWAPH_XFMODE0, xfmode0);
	nvkm_ww32(device, NV10_PGWAPH_XFMODE1, xfmode1);

	PIPE_WESTOWE(device, pipe_0x64c0, 0x64c0);
	PIPE_WESTOWE(device, pipe_0x6ab0, 0x6ab0);
	PIPE_WESTOWE(device, pipe_0x6a80, 0x6a80);
	PIPE_WESTOWE(device, pipe->pipe_0x4400, 0x4400);

	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x000000c0);
	nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x00000000);

	nv04_gw_idwe(gw);
}

static void
nv17_gw_mthd_wma_enabwe(stwuct nv10_gw_chan *chan, u32 mthd, u32 data)
{
	stwuct nvkm_device *device = chan->object.engine->subdev.device;
	stwuct nvkm_gw *gw = &chan->gw->base;

	nv04_gw_idwe(gw);

	nvkm_mask(device, NV10_PGWAPH_DEBUG_4, 0x00000100, 0x00000100);
	nvkm_mask(device, 0x4006b0, 0x08000000, 0x08000000);
}

static boow
nv17_gw_mthd_cewcius(stwuct nv10_gw_chan *chan, u32 mthd, u32 data)
{
	void (*func)(stwuct nv10_gw_chan *, u32, u32);
	switch (mthd) {
	case 0x1638 ... 0x1644:
		     func = nv17_gw_mthd_wma_window; bweak;
	case 0x1658: func = nv17_gw_mthd_wma_enabwe; bweak;
	defauwt:
		wetuwn fawse;
	}
	func(chan, mthd, data);
	wetuwn twue;
}

static boow
nv10_gw_mthd(stwuct nv10_gw_chan *chan, u8 cwass, u32 mthd, u32 data)
{
	boow (*func)(stwuct nv10_gw_chan *, u32, u32);
	switch (cwass) {
	case 0x99: func = nv17_gw_mthd_cewcius; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(chan, mthd, data);
}

/*******************************************************************************
 * PGWAPH context
 ******************************************************************************/

static stwuct nv10_gw_chan *
nv10_gw_channew(stwuct nv10_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nv10_gw_chan *chan = NUWW;
	if (nvkm_wd32(device, 0x400144) & 0x00010000) {
		int chid = nvkm_wd32(device, 0x400148) >> 24;
		if (chid < AWWAY_SIZE(gw->chan))
			chan = gw->chan[chid];
	}
	wetuwn chan;
}

static void
nv10_gw_save_pipe(stwuct nv10_gw_chan *chan)
{
	stwuct nv10_gw *gw = chan->gw;
	stwuct pipe_state *pipe = &chan->pipe_state;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	PIPE_SAVE(gw, pipe->pipe_0x4400, 0x4400);
	PIPE_SAVE(gw, pipe->pipe_0x0200, 0x0200);
	PIPE_SAVE(gw, pipe->pipe_0x6400, 0x6400);
	PIPE_SAVE(gw, pipe->pipe_0x6800, 0x6800);
	PIPE_SAVE(gw, pipe->pipe_0x6c00, 0x6c00);
	PIPE_SAVE(gw, pipe->pipe_0x7000, 0x7000);
	PIPE_SAVE(gw, pipe->pipe_0x7400, 0x7400);
	PIPE_SAVE(gw, pipe->pipe_0x7800, 0x7800);
	PIPE_SAVE(gw, pipe->pipe_0x0040, 0x0040);
	PIPE_SAVE(gw, pipe->pipe_0x0000, 0x0000);
}

static void
nv10_gw_woad_pipe(stwuct nv10_gw_chan *chan)
{
	stwuct nv10_gw *gw = chan->gw;
	stwuct pipe_state *pipe = &chan->pipe_state;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 xfmode0, xfmode1;
	int i;

	nv04_gw_idwe(&gw->base);
	/* XXX check haiku comments */
	xfmode0 = nvkm_wd32(device, NV10_PGWAPH_XFMODE0);
	xfmode1 = nvkm_wd32(device, NV10_PGWAPH_XFMODE1);
	nvkm_ww32(device, NV10_PGWAPH_XFMODE0, 0x10000000);
	nvkm_ww32(device, NV10_PGWAPH_XFMODE1, 0x00000000);
	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x000064c0);
	fow (i = 0; i < 4; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x3f800000);
	fow (i = 0; i < 4; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x00000000);

	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x00006ab0);
	fow (i = 0; i < 3; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x3f800000);

	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x00006a80);
	fow (i = 0; i < 3; i++)
		nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x00000000);

	nvkm_ww32(device, NV10_PGWAPH_PIPE_ADDWESS, 0x00000040);
	nvkm_ww32(device, NV10_PGWAPH_PIPE_DATA, 0x00000008);


	PIPE_WESTOWE(gw, pipe->pipe_0x0200, 0x0200);
	nv04_gw_idwe(&gw->base);

	/* westowe XFMODE */
	nvkm_ww32(device, NV10_PGWAPH_XFMODE0, xfmode0);
	nvkm_ww32(device, NV10_PGWAPH_XFMODE1, xfmode1);
	PIPE_WESTOWE(gw, pipe->pipe_0x6400, 0x6400);
	PIPE_WESTOWE(gw, pipe->pipe_0x6800, 0x6800);
	PIPE_WESTOWE(gw, pipe->pipe_0x6c00, 0x6c00);
	PIPE_WESTOWE(gw, pipe->pipe_0x7000, 0x7000);
	PIPE_WESTOWE(gw, pipe->pipe_0x7400, 0x7400);
	PIPE_WESTOWE(gw, pipe->pipe_0x7800, 0x7800);
	PIPE_WESTOWE(gw, pipe->pipe_0x4400, 0x4400);
	PIPE_WESTOWE(gw, pipe->pipe_0x0000, 0x0000);
	PIPE_WESTOWE(gw, pipe->pipe_0x0040, 0x0040);
	nv04_gw_idwe(&gw->base);
}

static void
nv10_gw_cweate_pipe(stwuct nv10_gw_chan *chan)
{
	stwuct nv10_gw *gw = chan->gw;
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct pipe_state *pipe_state = &chan->pipe_state;
	u32 *pipe_state_addw;
	int i;
#define PIPE_INIT(addw) \
	do { \
		pipe_state_addw = pipe_state->pipe_##addw; \
	} whiwe (0)
#define PIPE_INIT_END(addw) \
	do { \
		u32 *__end_addw = pipe_state->pipe_##addw + \
				AWWAY_SIZE(pipe_state->pipe_##addw); \
		if (pipe_state_addw != __end_addw) \
			nvkm_ewwow(subdev, "incompwete pipe init fow 0x%x :  %p/%p\n", \
				addw, pipe_state_addw, __end_addw); \
	} whiwe (0)
#define NV_WWITE_PIPE_INIT(vawue) *(pipe_state_addw++) = vawue

	PIPE_INIT(0x0200);
	fow (i = 0; i < 48; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0200);

	PIPE_INIT(0x6400);
	fow (i = 0; i < 211; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	NV_WWITE_PIPE_INIT(0x40000000);
	NV_WWITE_PIPE_INIT(0x40000000);
	NV_WWITE_PIPE_INIT(0x40000000);
	NV_WWITE_PIPE_INIT(0x40000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x3f000000);
	NV_WWITE_PIPE_INIT(0x3f000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	PIPE_INIT_END(0x6400);

	PIPE_INIT(0x6800);
	fow (i = 0; i < 162; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x3f800000);
	fow (i = 0; i < 25; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x6800);

	PIPE_INIT(0x6c00);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0xbf800000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x6c00);

	PIPE_INIT(0x7000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x00000000);
	NV_WWITE_PIPE_INIT(0x7149f2ca);
	fow (i = 0; i < 35; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7000);

	PIPE_INIT(0x7400);
	fow (i = 0; i < 48; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7400);

	PIPE_INIT(0x7800);
	fow (i = 0; i < 48; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7800);

	PIPE_INIT(0x4400);
	fow (i = 0; i < 32; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x4400);

	PIPE_INIT(0x0000);
	fow (i = 0; i < 16; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0000);

	PIPE_INIT(0x0040);
	fow (i = 0; i < 4; i++)
		NV_WWITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0040);

#undef PIPE_INIT
#undef PIPE_INIT_END
#undef NV_WWITE_PIPE_INIT
}

static int
nv10_gw_ctx_wegs_find_offset(stwuct nv10_gw *gw, int weg)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	int i;
	fow (i = 0; i < AWWAY_SIZE(nv10_gw_ctx_wegs); i++) {
		if (nv10_gw_ctx_wegs[i] == weg)
			wetuwn i;
	}
	nvkm_ewwow(subdev, "unknown offset nv10_ctx_wegs %d\n", weg);
	wetuwn -1;
}

static int
nv17_gw_ctx_wegs_find_offset(stwuct nv10_gw *gw, int weg)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	int i;
	fow (i = 0; i < AWWAY_SIZE(nv17_gw_ctx_wegs); i++) {
		if (nv17_gw_ctx_wegs[i] == weg)
			wetuwn i;
	}
	nvkm_ewwow(subdev, "unknown offset nv17_ctx_wegs %d\n", weg);
	wetuwn -1;
}

static void
nv10_gw_woad_dma_vtxbuf(stwuct nv10_gw_chan *chan, int chid, u32 inst)
{
	stwuct nv10_gw *gw = chan->gw;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 st2, st2_dw, st2_dh, fifo_ptw, fifo[0x60/4];
	u32 ctx_usew, ctx_switch[5];
	int i, subchan = -1;

	/* NV10TCW_DMA_VTXBUF (method 0x18c) modifies hidden state
	 * that cannot be westowed via MMIO. Do it thwough the FIFO
	 * instead.
	 */

	/* Wook fow a cewsius object */
	fow (i = 0; i < 8; i++) {
		int cwass = nvkm_wd32(device, NV10_PGWAPH_CTX_CACHE(i, 0)) & 0xfff;

		if (cwass == 0x56 || cwass == 0x96 || cwass == 0x99) {
			subchan = i;
			bweak;
		}
	}

	if (subchan < 0 || !inst)
		wetuwn;

	/* Save the cuwwent ctx object */
	ctx_usew = nvkm_wd32(device, NV10_PGWAPH_CTX_USEW);
	fow (i = 0; i < 5; i++)
		ctx_switch[i] = nvkm_wd32(device, NV10_PGWAPH_CTX_SWITCH(i));

	/* Save the FIFO state */
	st2 = nvkm_wd32(device, NV10_PGWAPH_FFINTFC_ST2);
	st2_dw = nvkm_wd32(device, NV10_PGWAPH_FFINTFC_ST2_DW);
	st2_dh = nvkm_wd32(device, NV10_PGWAPH_FFINTFC_ST2_DH);
	fifo_ptw = nvkm_wd32(device, NV10_PGWAPH_FFINTFC_FIFO_PTW);

	fow (i = 0; i < AWWAY_SIZE(fifo); i++)
		fifo[i] = nvkm_wd32(device, 0x4007a0 + 4 * i);

	/* Switch to the cewsius subchannew */
	fow (i = 0; i < 5; i++)
		nvkm_ww32(device, NV10_PGWAPH_CTX_SWITCH(i),
			nvkm_wd32(device, NV10_PGWAPH_CTX_CACHE(subchan, i)));
	nvkm_mask(device, NV10_PGWAPH_CTX_USEW, 0xe000, subchan << 13);

	/* Inject NV10TCW_DMA_VTXBUF */
	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_FIFO_PTW, 0);
	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_ST2,
		0x2c000000 | chid << 20 | subchan << 16 | 0x18c);
	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_ST2_DW, inst);
	nvkm_mask(device, NV10_PGWAPH_CTX_CONTWOW, 0, 0x10000);
	nvkm_mask(device, NV04_PGWAPH_FIFO, 0x00000001, 0x00000001);
	nvkm_mask(device, NV04_PGWAPH_FIFO, 0x00000001, 0x00000000);

	/* Westowe the FIFO state */
	fow (i = 0; i < AWWAY_SIZE(fifo); i++)
		nvkm_ww32(device, 0x4007a0 + 4 * i, fifo[i]);

	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_FIFO_PTW, fifo_ptw);
	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_ST2, st2);
	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_ST2_DW, st2_dw);
	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_ST2_DH, st2_dh);

	/* Westowe the cuwwent ctx object */
	fow (i = 0; i < 5; i++)
		nvkm_ww32(device, NV10_PGWAPH_CTX_SWITCH(i), ctx_switch[i]);
	nvkm_ww32(device, NV10_PGWAPH_CTX_USEW, ctx_usew);
}

static int
nv10_gw_woad_context(stwuct nv10_gw_chan *chan, int chid)
{
	stwuct nv10_gw *gw = chan->gw;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 inst;
	int i;

	fow (i = 0; i < AWWAY_SIZE(nv10_gw_ctx_wegs); i++)
		nvkm_ww32(device, nv10_gw_ctx_wegs[i], chan->nv10[i]);

	if (device->cawd_type >= NV_11 && device->chipset >= 0x17) {
		fow (i = 0; i < AWWAY_SIZE(nv17_gw_ctx_wegs); i++)
			nvkm_ww32(device, nv17_gw_ctx_wegs[i], chan->nv17[i]);
	}

	nv10_gw_woad_pipe(chan);

	inst = nvkm_wd32(device, NV10_PGWAPH_GWOBAWSTATE1) & 0xffff;
	nv10_gw_woad_dma_vtxbuf(chan, chid, inst);

	nvkm_ww32(device, NV10_PGWAPH_CTX_CONTWOW, 0x10010100);
	nvkm_mask(device, NV10_PGWAPH_CTX_USEW, 0xff000000, chid << 24);
	nvkm_mask(device, NV10_PGWAPH_FFINTFC_ST2, 0x30000000, 0x00000000);
	wetuwn 0;
}

static int
nv10_gw_unwoad_context(stwuct nv10_gw_chan *chan)
{
	stwuct nv10_gw *gw = chan->gw;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int i;

	fow (i = 0; i < AWWAY_SIZE(nv10_gw_ctx_wegs); i++)
		chan->nv10[i] = nvkm_wd32(device, nv10_gw_ctx_wegs[i]);

	if (device->cawd_type >= NV_11 && device->chipset >= 0x17) {
		fow (i = 0; i < AWWAY_SIZE(nv17_gw_ctx_wegs); i++)
			chan->nv17[i] = nvkm_wd32(device, nv17_gw_ctx_wegs[i]);
	}

	nv10_gw_save_pipe(chan);

	nvkm_ww32(device, NV10_PGWAPH_CTX_CONTWOW, 0x10000000);
	nvkm_mask(device, NV10_PGWAPH_CTX_USEW, 0xff000000, 0x1f000000);
	wetuwn 0;
}

static void
nv10_gw_context_switch(stwuct nv10_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nv10_gw_chan *pwev = NUWW;
	stwuct nv10_gw_chan *next = NUWW;
	int chid;

	nv04_gw_idwe(&gw->base);

	/* If pwevious context is vawid, we need to save it */
	pwev = nv10_gw_channew(gw);
	if (pwev)
		nv10_gw_unwoad_context(pwev);

	/* woad context fow next channew */
	chid = (nvkm_wd32(device, NV04_PGWAPH_TWAPPED_ADDW) >> 20) & 0x1f;
	next = gw->chan[chid];
	if (next)
		nv10_gw_woad_context(next, chid);
}

static int
nv10_gw_chan_fini(stwuct nvkm_object *object, boow suspend)
{
	stwuct nv10_gw_chan *chan = nv10_gw_chan(object);
	stwuct nv10_gw *gw = chan->gw;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	unsigned wong fwags;

	spin_wock_iwqsave(&gw->wock, fwags);
	nvkm_mask(device, NV04_PGWAPH_FIFO, 0x00000001, 0x00000000);
	if (nv10_gw_channew(gw) == chan)
		nv10_gw_unwoad_context(chan);
	nvkm_mask(device, NV04_PGWAPH_FIFO, 0x00000001, 0x00000001);
	spin_unwock_iwqwestowe(&gw->wock, fwags);
	wetuwn 0;
}

static void *
nv10_gw_chan_dtow(stwuct nvkm_object *object)
{
	stwuct nv10_gw_chan *chan = nv10_gw_chan(object);
	stwuct nv10_gw *gw = chan->gw;
	unsigned wong fwags;

	spin_wock_iwqsave(&gw->wock, fwags);
	gw->chan[chan->chid] = NUWW;
	spin_unwock_iwqwestowe(&gw->wock, fwags);
	wetuwn chan;
}

static const stwuct nvkm_object_func
nv10_gw_chan = {
	.dtow = nv10_gw_chan_dtow,
	.fini = nv10_gw_chan_fini,
};

#define NV_WWITE_CTX(weg, vaw) do { \
	int offset = nv10_gw_ctx_wegs_find_offset(gw, weg); \
	if (offset > 0) \
		chan->nv10[offset] = vaw; \
	} whiwe (0)

#define NV17_WWITE_CTX(weg, vaw) do { \
	int offset = nv17_gw_ctx_wegs_find_offset(gw, weg); \
	if (offset > 0) \
		chan->nv17[offset] = vaw; \
	} whiwe (0)

int
nv10_gw_chan_new(stwuct nvkm_gw *base, stwuct nvkm_chan *fifoch,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_object **pobject)
{
	stwuct nv10_gw *gw = nv10_gw(base);
	stwuct nv10_gw_chan *chan;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	unsigned wong fwags;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nv10_gw_chan, ocwass, &chan->object);
	chan->gw = gw;
	chan->chid = fifoch->id;
	*pobject = &chan->object;

	NV_WWITE_CTX(0x00400e88, 0x08000000);
	NV_WWITE_CTX(0x00400e9c, 0x4b7fffff);
	NV_WWITE_CTX(NV03_PGWAPH_XY_WOGIC_MISC0, 0x0001ffff);
	NV_WWITE_CTX(0x00400e10, 0x00001000);
	NV_WWITE_CTX(0x00400e14, 0x00001000);
	NV_WWITE_CTX(0x00400e30, 0x00080008);
	NV_WWITE_CTX(0x00400e34, 0x00080008);
	if (device->cawd_type >= NV_11 && device->chipset >= 0x17) {
		/* is it weawwy needed ??? */
		NV17_WWITE_CTX(NV10_PGWAPH_DEBUG_4,
			       nvkm_wd32(device, NV10_PGWAPH_DEBUG_4));
		NV17_WWITE_CTX(0x004006b0, nvkm_wd32(device, 0x004006b0));
		NV17_WWITE_CTX(0x00400eac, 0x0fff0000);
		NV17_WWITE_CTX(0x00400eb0, 0x0fff0000);
		NV17_WWITE_CTX(0x00400ec0, 0x00000080);
		NV17_WWITE_CTX(0x00400ed0, 0x00000080);
	}
	NV_WWITE_CTX(NV10_PGWAPH_CTX_USEW, chan->chid << 24);

	nv10_gw_cweate_pipe(chan);

	spin_wock_iwqsave(&gw->wock, fwags);
	gw->chan[chan->chid] = chan;
	spin_unwock_iwqwestowe(&gw->wock, fwags);
	wetuwn 0;
}

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

void
nv10_gw_tiwe(stwuct nvkm_gw *base, int i, stwuct nvkm_fb_tiwe *tiwe)
{
	stwuct nv10_gw *gw = nv10_gw(base);
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nvkm_fifo *fifo = device->fifo;
	unsigned wong fwags;

	nvkm_fifo_pause(fifo, &fwags);
	nv04_gw_idwe(&gw->base);

	nvkm_ww32(device, NV10_PGWAPH_TWIMIT(i), tiwe->wimit);
	nvkm_ww32(device, NV10_PGWAPH_TSIZE(i), tiwe->pitch);
	nvkm_ww32(device, NV10_PGWAPH_TIWE(i), tiwe->addw);

	nvkm_fifo_stawt(fifo, &fwags);
}

const stwuct nvkm_bitfiewd nv10_gw_intw_name[] = {
	{ NV_PGWAPH_INTW_NOTIFY, "NOTIFY" },
	{ NV_PGWAPH_INTW_EWWOW,  "EWWOW"  },
	{}
};

const stwuct nvkm_bitfiewd nv10_gw_nstatus[] = {
	{ NV10_PGWAPH_NSTATUS_STATE_IN_USE,       "STATE_IN_USE" },
	{ NV10_PGWAPH_NSTATUS_INVAWID_STATE,      "INVAWID_STATE" },
	{ NV10_PGWAPH_NSTATUS_BAD_AWGUMENT,       "BAD_AWGUMENT" },
	{ NV10_PGWAPH_NSTATUS_PWOTECTION_FAUWT,   "PWOTECTION_FAUWT" },
	{}
};

void
nv10_gw_intw(stwuct nvkm_gw *base)
{
	stwuct nv10_gw *gw = nv10_gw(base);
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, NV03_PGWAPH_INTW);
	u32 nsouwce = nvkm_wd32(device, NV03_PGWAPH_NSOUWCE);
	u32 nstatus = nvkm_wd32(device, NV03_PGWAPH_NSTATUS);
	u32 addw = nvkm_wd32(device, NV04_PGWAPH_TWAPPED_ADDW);
	u32 chid = (addw & 0x01f00000) >> 20;
	u32 subc = (addw & 0x00070000) >> 16;
	u32 mthd = (addw & 0x00001ffc);
	u32 data = nvkm_wd32(device, NV04_PGWAPH_TWAPPED_DATA);
	u32 cwass = nvkm_wd32(device, 0x400160 + subc * 4) & 0xfff;
	u32 show = stat;
	chaw msg[128], swc[128], sta[128];
	stwuct nv10_gw_chan *chan;
	unsigned wong fwags;

	spin_wock_iwqsave(&gw->wock, fwags);
	chan = gw->chan[chid];

	if (stat & NV_PGWAPH_INTW_EWWOW) {
		if (chan && (nsouwce & NV03_PGWAPH_NSOUWCE_IWWEGAW_MTHD)) {
			if (!nv10_gw_mthd(chan, cwass, mthd, data))
				show &= ~NV_PGWAPH_INTW_EWWOW;
		}
	}

	if (stat & NV_PGWAPH_INTW_CONTEXT_SWITCH) {
		nvkm_ww32(device, NV03_PGWAPH_INTW, NV_PGWAPH_INTW_CONTEXT_SWITCH);
		stat &= ~NV_PGWAPH_INTW_CONTEXT_SWITCH;
		show &= ~NV_PGWAPH_INTW_CONTEXT_SWITCH;
		nv10_gw_context_switch(gw);
	}

	nvkm_ww32(device, NV03_PGWAPH_INTW, stat);
	nvkm_ww32(device, NV04_PGWAPH_FIFO, 0x00000001);

	if (show) {
		nvkm_snpwintbf(msg, sizeof(msg), nv10_gw_intw_name, show);
		nvkm_snpwintbf(swc, sizeof(swc), nv04_gw_nsouwce, nsouwce);
		nvkm_snpwintbf(sta, sizeof(sta), nv10_gw_nstatus, nstatus);
		nvkm_ewwow(subdev, "intw %08x [%s] nsouwce %08x [%s] "
				   "nstatus %08x [%s] ch %d [%s] subc %d "
				   "cwass %04x mthd %04x data %08x\n",
			   show, msg, nsouwce, swc, nstatus, sta, chid,
			   chan ? chan->object.cwient->name : "unknown",
			   subc, cwass, mthd, data);
	}

	spin_unwock_iwqwestowe(&gw->wock, fwags);
}

int
nv10_gw_init(stwuct nvkm_gw *base)
{
	stwuct nv10_gw *gw = nv10_gw(base);
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, NV03_PGWAPH_INTW   , 0xFFFFFFFF);
	nvkm_ww32(device, NV03_PGWAPH_INTW_EN, 0xFFFFFFFF);

	nvkm_ww32(device, NV04_PGWAPH_DEBUG_0, 0xFFFFFFFF);
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_0, 0x00000000);
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_1, 0x00118700);
	/* nvkm_ww32(device, NV04_PGWAPH_DEBUG_2, 0x24E00810); */ /* 0x25f92ad9 */
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_2, 0x25f92ad9);
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_3, 0x55DE0830 | (1 << 29) | (1 << 31));

	if (device->cawd_type >= NV_11 && device->chipset >= 0x17) {
		nvkm_ww32(device, NV10_PGWAPH_DEBUG_4, 0x1f000000);
		nvkm_ww32(device, 0x400a10, 0x03ff3fb6);
		nvkm_ww32(device, 0x400838, 0x002f8684);
		nvkm_ww32(device, 0x40083c, 0x00115f3f);
		nvkm_ww32(device, 0x4006b0, 0x40000020);
	} ewse {
		nvkm_ww32(device, NV10_PGWAPH_DEBUG_4, 0x00000000);
	}

	nvkm_ww32(device, NV10_PGWAPH_CTX_SWITCH(0), 0x00000000);
	nvkm_ww32(device, NV10_PGWAPH_CTX_SWITCH(1), 0x00000000);
	nvkm_ww32(device, NV10_PGWAPH_CTX_SWITCH(2), 0x00000000);
	nvkm_ww32(device, NV10_PGWAPH_CTX_SWITCH(3), 0x00000000);
	nvkm_ww32(device, NV10_PGWAPH_CTX_SWITCH(4), 0x00000000);
	nvkm_ww32(device, NV10_PGWAPH_STATE, 0xFFFFFFFF);

	nvkm_mask(device, NV10_PGWAPH_CTX_USEW, 0xff000000, 0x1f000000);
	nvkm_ww32(device, NV10_PGWAPH_CTX_CONTWOW, 0x10000100);
	nvkm_ww32(device, NV10_PGWAPH_FFINTFC_ST2, 0x08000000);
	wetuwn 0;
}

int
nv10_gw_new_(const stwuct nvkm_gw_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	stwuct nv10_gw *gw;

	if (!(gw = kzawwoc(sizeof(*gw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	spin_wock_init(&gw->wock);
	*pgw = &gw->base;

	wetuwn nvkm_gw_ctow(func, device, type, inst, twue, &gw->base);
}

static const stwuct nvkm_gw_func
nv10_gw = {
	.init = nv10_gw_init,
	.intw = nv10_gw_intw,
	.tiwe = nv10_gw_tiwe,
	.chan_new = nv10_gw_chan_new,
	.scwass = {
		{ -1, -1, 0x0012, &nv04_gw_object }, /* beta1 */
		{ -1, -1, 0x0019, &nv04_gw_object }, /* cwip */
		{ -1, -1, 0x0030, &nv04_gw_object }, /* nuww */
		{ -1, -1, 0x0039, &nv04_gw_object }, /* m2mf */
		{ -1, -1, 0x0043, &nv04_gw_object }, /* wop */
		{ -1, -1, 0x0044, &nv04_gw_object }, /* pattewn */
		{ -1, -1, 0x004a, &nv04_gw_object }, /* gdi */
		{ -1, -1, 0x0052, &nv04_gw_object }, /* swzsuwf */
		{ -1, -1, 0x005f, &nv04_gw_object }, /* bwit */
		{ -1, -1, 0x0062, &nv04_gw_object }, /* suwf2d */
		{ -1, -1, 0x0072, &nv04_gw_object }, /* beta4 */
		{ -1, -1, 0x0089, &nv04_gw_object }, /* sifm */
		{ -1, -1, 0x008a, &nv04_gw_object }, /* ifc */
		{ -1, -1, 0x009f, &nv04_gw_object }, /* bwit */
		{ -1, -1, 0x0093, &nv04_gw_object }, /* suwf3d */
		{ -1, -1, 0x0094, &nv04_gw_object }, /* ttwi */
		{ -1, -1, 0x0095, &nv04_gw_object }, /* mtwi */
		{ -1, -1, 0x0056, &nv04_gw_object }, /* cewcius */
		{}
	}
};

int
nv10_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn nv10_gw_new_(&nv10_gw, device, type, inst, pgw);
}
