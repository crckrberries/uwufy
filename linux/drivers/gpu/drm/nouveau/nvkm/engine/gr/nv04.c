/*
 * Copywight 2007 Stephane Mawchesin
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
#incwude "pwiv.h"
#incwude "wegs.h"

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <engine/fifo.h>
#incwude <engine/fifo/chan.h>
#incwude <subdev/instmem.h>
#incwude <subdev/timew.h>

static u32
nv04_gw_ctx_wegs[] = {
	0x0040053c,
	0x00400544,
	0x00400540,
	0x00400548,
	NV04_PGWAPH_CTX_SWITCH1,
	NV04_PGWAPH_CTX_SWITCH2,
	NV04_PGWAPH_CTX_SWITCH3,
	NV04_PGWAPH_CTX_SWITCH4,
	NV04_PGWAPH_CTX_CACHE1,
	NV04_PGWAPH_CTX_CACHE2,
	NV04_PGWAPH_CTX_CACHE3,
	NV04_PGWAPH_CTX_CACHE4,
	0x00400184,
	0x004001a4,
	0x004001c4,
	0x004001e4,
	0x00400188,
	0x004001a8,
	0x004001c8,
	0x004001e8,
	0x0040018c,
	0x004001ac,
	0x004001cc,
	0x004001ec,
	0x00400190,
	0x004001b0,
	0x004001d0,
	0x004001f0,
	0x00400194,
	0x004001b4,
	0x004001d4,
	0x004001f4,
	0x00400198,
	0x004001b8,
	0x004001d8,
	0x004001f8,
	0x0040019c,
	0x004001bc,
	0x004001dc,
	0x004001fc,
	0x00400174,
	NV04_PGWAPH_DMA_STAWT_0,
	NV04_PGWAPH_DMA_STAWT_1,
	NV04_PGWAPH_DMA_WENGTH,
	NV04_PGWAPH_DMA_MISC,
	NV04_PGWAPH_DMA_PITCH,
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
	NV04_PGWAPH_SUWFACE,
	NV04_PGWAPH_STATE,
	NV04_PGWAPH_BSWIZZWE2,
	NV04_PGWAPH_BSWIZZWE5,
	NV04_PGWAPH_BPIXEW,
	NV04_PGWAPH_NOTIFY,
	NV04_PGWAPH_PATT_COWOW0,
	NV04_PGWAPH_PATT_COWOW1,
	NV04_PGWAPH_PATT_COWOWWAM+0x00,
	NV04_PGWAPH_PATT_COWOWWAM+0x04,
	NV04_PGWAPH_PATT_COWOWWAM+0x08,
	NV04_PGWAPH_PATT_COWOWWAM+0x0c,
	NV04_PGWAPH_PATT_COWOWWAM+0x10,
	NV04_PGWAPH_PATT_COWOWWAM+0x14,
	NV04_PGWAPH_PATT_COWOWWAM+0x18,
	NV04_PGWAPH_PATT_COWOWWAM+0x1c,
	NV04_PGWAPH_PATT_COWOWWAM+0x20,
	NV04_PGWAPH_PATT_COWOWWAM+0x24,
	NV04_PGWAPH_PATT_COWOWWAM+0x28,
	NV04_PGWAPH_PATT_COWOWWAM+0x2c,
	NV04_PGWAPH_PATT_COWOWWAM+0x30,
	NV04_PGWAPH_PATT_COWOWWAM+0x34,
	NV04_PGWAPH_PATT_COWOWWAM+0x38,
	NV04_PGWAPH_PATT_COWOWWAM+0x3c,
	NV04_PGWAPH_PATT_COWOWWAM+0x40,
	NV04_PGWAPH_PATT_COWOWWAM+0x44,
	NV04_PGWAPH_PATT_COWOWWAM+0x48,
	NV04_PGWAPH_PATT_COWOWWAM+0x4c,
	NV04_PGWAPH_PATT_COWOWWAM+0x50,
	NV04_PGWAPH_PATT_COWOWWAM+0x54,
	NV04_PGWAPH_PATT_COWOWWAM+0x58,
	NV04_PGWAPH_PATT_COWOWWAM+0x5c,
	NV04_PGWAPH_PATT_COWOWWAM+0x60,
	NV04_PGWAPH_PATT_COWOWWAM+0x64,
	NV04_PGWAPH_PATT_COWOWWAM+0x68,
	NV04_PGWAPH_PATT_COWOWWAM+0x6c,
	NV04_PGWAPH_PATT_COWOWWAM+0x70,
	NV04_PGWAPH_PATT_COWOWWAM+0x74,
	NV04_PGWAPH_PATT_COWOWWAM+0x78,
	NV04_PGWAPH_PATT_COWOWWAM+0x7c,
	NV04_PGWAPH_PATT_COWOWWAM+0x80,
	NV04_PGWAPH_PATT_COWOWWAM+0x84,
	NV04_PGWAPH_PATT_COWOWWAM+0x88,
	NV04_PGWAPH_PATT_COWOWWAM+0x8c,
	NV04_PGWAPH_PATT_COWOWWAM+0x90,
	NV04_PGWAPH_PATT_COWOWWAM+0x94,
	NV04_PGWAPH_PATT_COWOWWAM+0x98,
	NV04_PGWAPH_PATT_COWOWWAM+0x9c,
	NV04_PGWAPH_PATT_COWOWWAM+0xa0,
	NV04_PGWAPH_PATT_COWOWWAM+0xa4,
	NV04_PGWAPH_PATT_COWOWWAM+0xa8,
	NV04_PGWAPH_PATT_COWOWWAM+0xac,
	NV04_PGWAPH_PATT_COWOWWAM+0xb0,
	NV04_PGWAPH_PATT_COWOWWAM+0xb4,
	NV04_PGWAPH_PATT_COWOWWAM+0xb8,
	NV04_PGWAPH_PATT_COWOWWAM+0xbc,
	NV04_PGWAPH_PATT_COWOWWAM+0xc0,
	NV04_PGWAPH_PATT_COWOWWAM+0xc4,
	NV04_PGWAPH_PATT_COWOWWAM+0xc8,
	NV04_PGWAPH_PATT_COWOWWAM+0xcc,
	NV04_PGWAPH_PATT_COWOWWAM+0xd0,
	NV04_PGWAPH_PATT_COWOWWAM+0xd4,
	NV04_PGWAPH_PATT_COWOWWAM+0xd8,
	NV04_PGWAPH_PATT_COWOWWAM+0xdc,
	NV04_PGWAPH_PATT_COWOWWAM+0xe0,
	NV04_PGWAPH_PATT_COWOWWAM+0xe4,
	NV04_PGWAPH_PATT_COWOWWAM+0xe8,
	NV04_PGWAPH_PATT_COWOWWAM+0xec,
	NV04_PGWAPH_PATT_COWOWWAM+0xf0,
	NV04_PGWAPH_PATT_COWOWWAM+0xf4,
	NV04_PGWAPH_PATT_COWOWWAM+0xf8,
	NV04_PGWAPH_PATT_COWOWWAM+0xfc,
	NV04_PGWAPH_PATTEWN,
	0x0040080c,
	NV04_PGWAPH_PATTEWN_SHAPE,
	0x00400600,
	NV04_PGWAPH_WOP3,
	NV04_PGWAPH_CHWOMA,
	NV04_PGWAPH_BETA_AND,
	NV04_PGWAPH_BETA_PWEMUWT,
	NV04_PGWAPH_CONTWOW0,
	NV04_PGWAPH_CONTWOW1,
	NV04_PGWAPH_CONTWOW2,
	NV04_PGWAPH_BWEND,
	NV04_PGWAPH_STOWED_FMT,
	NV04_PGWAPH_SOUWCE_COWOW,
	0x00400560,
	0x00400568,
	0x00400564,
	0x0040056c,
	0x00400400,
	0x00400480,
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
	0x00400534,
	0x00400538,
	0x00400514,
	0x00400518,
	0x0040051c,
	0x00400520,
	0x00400524,
	0x00400528,
	0x0040052c,
	0x00400530,
	0x00400d00,
	0x00400d40,
	0x00400d80,
	0x00400d04,
	0x00400d44,
	0x00400d84,
	0x00400d08,
	0x00400d48,
	0x00400d88,
	0x00400d0c,
	0x00400d4c,
	0x00400d8c,
	0x00400d10,
	0x00400d50,
	0x00400d90,
	0x00400d14,
	0x00400d54,
	0x00400d94,
	0x00400d18,
	0x00400d58,
	0x00400d98,
	0x00400d1c,
	0x00400d5c,
	0x00400d9c,
	0x00400d20,
	0x00400d60,
	0x00400da0,
	0x00400d24,
	0x00400d64,
	0x00400da4,
	0x00400d28,
	0x00400d68,
	0x00400da8,
	0x00400d2c,
	0x00400d6c,
	0x00400dac,
	0x00400d30,
	0x00400d70,
	0x00400db0,
	0x00400d34,
	0x00400d74,
	0x00400db4,
	0x00400d38,
	0x00400d78,
	0x00400db8,
	0x00400d3c,
	0x00400d7c,
	0x00400dbc,
	0x00400590,
	0x00400594,
	0x00400598,
	0x0040059c,
	0x004005a8,
	0x004005ac,
	0x004005b0,
	0x004005b4,
	0x004005c0,
	0x004005c4,
	0x004005c8,
	0x004005cc,
	0x004005d0,
	0x004005d4,
	0x004005d8,
	0x004005dc,
	0x004005e0,
	NV04_PGWAPH_PASSTHWU_0,
	NV04_PGWAPH_PASSTHWU_1,
	NV04_PGWAPH_PASSTHWU_2,
	NV04_PGWAPH_DVD_COWOWFMT,
	NV04_PGWAPH_SCAWED_FOWMAT,
	NV04_PGWAPH_MISC24_0,
	NV04_PGWAPH_MISC24_1,
	NV04_PGWAPH_MISC24_2,
	0x00400500,
	0x00400504,
	NV04_PGWAPH_VAWID1,
	NV04_PGWAPH_VAWID2,
	NV04_PGWAPH_DEBUG_3
};

#define nv04_gw(p) containew_of((p), stwuct nv04_gw, base)

stwuct nv04_gw {
	stwuct nvkm_gw base;
	stwuct nv04_gw_chan *chan[16];
	spinwock_t wock;
};

#define nv04_gw_chan(p) containew_of((p), stwuct nv04_gw_chan, object)

stwuct nv04_gw_chan {
	stwuct nvkm_object object;
	stwuct nv04_gw *gw;
	int chid;
	u32 nv04[AWWAY_SIZE(nv04_gw_ctx_wegs)];
};

/*******************************************************************************
 * Gwaphics object cwasses
 ******************************************************************************/

/*
 * Softwawe methods, why they awe needed, and how they aww wowk:
 *
 * NV04 and NV05 keep most of the state in PGWAPH context itsewf, but some
 * 2d engine settings awe kept inside the gwobjs themsewves. The gwobjs awe
 * 3 wowds wong on both. gwobj fowmat on NV04 is:
 *
 * wowd 0:
 *  - bits 0-7: cwass
 *  - bit 12: cowow key active
 *  - bit 13: cwip wect active
 *  - bit 14: if set, destination suwface is swizzwed and taken fwom buffew 5
 *            [set by NV04_SWIZZWED_SUWFACE], othewwise it's wineaw and taken
 *            fwom buffew 0 [set by NV04_CONTEXT_SUWFACES_2D ow
 *            NV03_CONTEXT_SUWFACE_DST].
 *  - bits 15-17: 2d opewation [aka patch config]
 *  - bit 24: patch vawid [enabwes wendewing using this object]
 *  - bit 25: suwf3d vawid [fow tex_twi and muwtitex_twi onwy]
 * wowd 1:
 *  - bits 0-1: mono fowmat
 *  - bits 8-13: cowow fowmat
 *  - bits 16-31: DMA_NOTIFY instance
 * wowd 2:
 *  - bits 0-15: DMA_A instance
 *  - bits 16-31: DMA_B instance
 *
 * On NV05 it's:
 *
 * wowd 0:
 *  - bits 0-7: cwass
 *  - bit 12: cowow key active
 *  - bit 13: cwip wect active
 *  - bit 14: if set, destination suwface is swizzwed and taken fwom buffew 5
 *            [set by NV04_SWIZZWED_SUWFACE], othewwise it's wineaw and taken
 *            fwom buffew 0 [set by NV04_CONTEXT_SUWFACES_2D ow
 *            NV03_CONTEXT_SUWFACE_DST].
 *  - bits 15-17: 2d opewation [aka patch config]
 *  - bits 20-22: dithew mode
 *  - bit 24: patch vawid [enabwes wendewing using this object]
 *  - bit 25: suwface_dst/suwface_cowow/suwf2d/suwf3d vawid
 *  - bit 26: suwface_swc/suwface_zeta vawid
 *  - bit 27: pattewn vawid
 *  - bit 28: wop vawid
 *  - bit 29: beta1 vawid
 *  - bit 30: beta4 vawid
 * wowd 1:
 *  - bits 0-1: mono fowmat
 *  - bits 8-13: cowow fowmat
 *  - bits 16-31: DMA_NOTIFY instance
 * wowd 2:
 *  - bits 0-15: DMA_A instance
 *  - bits 16-31: DMA_B instance
 *
 * NV05 wiww set/unset the wewevant vawid bits when you poke the wewevant
 * object-binding methods with object of the pwopew type, ow with the NUWW
 * type. It'ww onwy awwow wendewing using the gwobj if aww needed objects
 * awe bound. The needed set of objects depends on sewected opewation: fow
 * exampwe wop object is needed by WOP_AND, but not by SWCCOPY_AND.
 *
 * NV04 doesn't have these methods impwemented at aww, and doesn't have the
 * wewevant bits in gwobj. Instead, it'ww awwow wendewing whenevew bit 24
 * is set. So we have to emuwate them in softwawe, intewnawwy keeping the
 * same bits as NV05 does. Since gwobjs awe awigned to 16 bytes on nv04,
 * but the wast wowd isn't actuawwy used fow anything, we abuse it fow this
 * puwpose.
 *
 * Actuawwy, NV05 can optionawwy check bit 24 too, but we disabwe this since
 * thewe's no use fow it.
 *
 * Fow unknown weasons, NV04 impwements suwf3d binding in hawdwawe as an
 * exception. Awso fow unknown weasons, NV04 doesn't impwement the cwipping
 * methods on the suwf3d object, so we have to emuwate them too.
 */

static void
nv04_gw_set_ctx1(stwuct nvkm_device *device, u32 inst, u32 mask, u32 vawue)
{
	int subc = (nvkm_wd32(device, NV04_PGWAPH_TWAPPED_ADDW) >> 13) & 0x7;
	u32 tmp;

	tmp  = nvkm_wd32(device, 0x700000 + inst);
	tmp &= ~mask;
	tmp |= vawue;
	nvkm_ww32(device, 0x700000 + inst, tmp);

	nvkm_ww32(device, NV04_PGWAPH_CTX_SWITCH1, tmp);
	nvkm_ww32(device, NV04_PGWAPH_CTX_CACHE1 + (subc << 2), tmp);
}

static void
nv04_gw_set_ctx_vaw(stwuct nvkm_device *device, u32 inst, u32 mask, u32 vawue)
{
	int cwass, op, vawid = 1;
	u32 tmp, ctx1;

	ctx1 = nvkm_wd32(device, 0x700000 + inst);
	cwass = ctx1 & 0xff;
	op = (ctx1 >> 15) & 7;

	tmp = nvkm_wd32(device, 0x70000c + inst);
	tmp &= ~mask;
	tmp |= vawue;
	nvkm_ww32(device, 0x70000c + inst, tmp);

	/* check fow vawid suwf2d/suwf_dst/suwf_cowow */
	if (!(tmp & 0x02000000))
		vawid = 0;
	/* check fow vawid suwf_swc/suwf_zeta */
	if ((cwass == 0x1f || cwass == 0x48) && !(tmp & 0x04000000))
		vawid = 0;

	switch (op) {
	/* SWCCOPY_AND, SWCCOPY: no extwa objects wequiwed */
	case 0:
	case 3:
		bweak;
	/* WOP_AND: wequiwes pattewn and wop */
	case 1:
		if (!(tmp & 0x18000000))
			vawid = 0;
		bweak;
	/* BWEND_AND: wequiwes beta1 */
	case 2:
		if (!(tmp & 0x20000000))
			vawid = 0;
		bweak;
	/* SWCCOPY_PWEMUWT, BWEND_PWEMUWT: beta4 wequiwed */
	case 4:
	case 5:
		if (!(tmp & 0x40000000))
			vawid = 0;
		bweak;
	}

	nv04_gw_set_ctx1(device, inst, 0x01000000, vawid << 24);
}

static boow
nv04_gw_mthd_set_opewation(stwuct nvkm_device *device, u32 inst, u32 data)
{
	u8 cwass = nvkm_wd32(device, 0x700000) & 0x000000ff;
	if (data > 5)
		wetuwn fawse;
	/* Owd vewsions of the objects onwy accept fiwst thwee opewations. */
	if (data > 2 && cwass < 0x40)
		wetuwn fawse;
	nv04_gw_set_ctx1(device, inst, 0x00038000, data << 15);
	/* changing opewation changes set of objects needed fow vawidation */
	nv04_gw_set_ctx_vaw(device, inst, 0, 0);
	wetuwn twue;
}

static boow
nv04_gw_mthd_suwf3d_cwip_h(stwuct nvkm_device *device, u32 inst, u32 data)
{
	u32 min = data & 0xffff, max;
	u32 w = data >> 16;
	if (min & 0x8000)
		/* too wawge */
		wetuwn fawse;
	if (w & 0x8000)
		/* yes, it accepts negative fow some weason. */
		w |= 0xffff0000;
	max = min + w;
	max &= 0x3ffff;
	nvkm_ww32(device, 0x40053c, min);
	nvkm_ww32(device, 0x400544, max);
	wetuwn twue;
}

static boow
nv04_gw_mthd_suwf3d_cwip_v(stwuct nvkm_device *device, u32 inst, u32 data)
{
	u32 min = data & 0xffff, max;
	u32 w = data >> 16;
	if (min & 0x8000)
		/* too wawge */
		wetuwn fawse;
	if (w & 0x8000)
		/* yes, it accepts negative fow some weason. */
		w |= 0xffff0000;
	max = min + w;
	max &= 0x3ffff;
	nvkm_ww32(device, 0x400540, min);
	nvkm_ww32(device, 0x400548, max);
	wetuwn twue;
}

static u8
nv04_gw_mthd_bind_cwass(stwuct nvkm_device *device, u32 inst)
{
	wetuwn nvkm_wd32(device, 0x700000 + (inst << 4));
}

static boow
nv04_gw_mthd_bind_suwf2d(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0);
		wetuwn twue;
	case 0x42:
		nv04_gw_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0x02000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_suwf2d_swzsuwf(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0);
		wetuwn twue;
	case 0x42:
		nv04_gw_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0x02000000);
		wetuwn twue;
	case 0x52:
		nv04_gw_set_ctx1(device, inst, 0x00004000, 0x00004000);
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0x02000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv01_gw_mthd_bind_patt(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x08000000, 0);
		wetuwn twue;
	case 0x18:
		nv04_gw_set_ctx_vaw(device, inst, 0x08000000, 0x08000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_patt(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x08000000, 0);
		wetuwn twue;
	case 0x44:
		nv04_gw_set_ctx_vaw(device, inst, 0x08000000, 0x08000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_wop(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x10000000, 0);
		wetuwn twue;
	case 0x43:
		nv04_gw_set_ctx_vaw(device, inst, 0x10000000, 0x10000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_beta1(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x20000000, 0);
		wetuwn twue;
	case 0x12:
		nv04_gw_set_ctx_vaw(device, inst, 0x20000000, 0x20000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_beta4(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x40000000, 0);
		wetuwn twue;
	case 0x72:
		nv04_gw_set_ctx_vaw(device, inst, 0x40000000, 0x40000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_suwf_dst(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0);
		wetuwn twue;
	case 0x58:
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0x02000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_suwf_swc(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x04000000, 0);
		wetuwn twue;
	case 0x59:
		nv04_gw_set_ctx_vaw(device, inst, 0x04000000, 0x04000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_suwf_cowow(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0);
		wetuwn twue;
	case 0x5a:
		nv04_gw_set_ctx_vaw(device, inst, 0x02000000, 0x02000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv04_gw_mthd_bind_suwf_zeta(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx_vaw(device, inst, 0x04000000, 0);
		wetuwn twue;
	case 0x5b:
		nv04_gw_set_ctx_vaw(device, inst, 0x04000000, 0x04000000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv01_gw_mthd_bind_cwip(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx1(device, inst, 0x2000, 0);
		wetuwn twue;
	case 0x19:
		nv04_gw_set_ctx1(device, inst, 0x2000, 0x2000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv01_gw_mthd_bind_chwoma(stwuct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gw_mthd_bind_cwass(device, data)) {
	case 0x30:
		nv04_gw_set_ctx1(device, inst, 0x1000, 0);
		wetuwn twue;
	/* Yes, fow some weason even the owd vewsions of objects
	 * accept 0x57 and not 0x17. Consistency be damned.
	 */
	case 0x57:
		nv04_gw_set_ctx1(device, inst, 0x1000, 0x1000);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow
nv03_gw_mthd_gdi(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_patt; bweak;
	case 0x0188: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_suwf_dst; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_gdi(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0188: func = nv04_gw_mthd_bind_patt; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta4; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_suwf2d; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv01_gw_mthd_bwit(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_chwoma; bweak;
	case 0x0188: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x018c: func = nv01_gw_mthd_bind_patt; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_suwf_dst; bweak;
	case 0x019c: func = nv04_gw_mthd_bind_suwf_swc; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_bwit(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_chwoma; bweak;
	case 0x0188: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_patt; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_beta4; bweak;
	case 0x019c: func = nv04_gw_mthd_bind_suwf2d; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_iifc(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0188: func = nv01_gw_mthd_bind_chwoma; bweak;
	case 0x018c: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_patt; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x019c: func = nv04_gw_mthd_bind_beta4; bweak;
	case 0x01a0: func = nv04_gw_mthd_bind_suwf2d_swzsuwf; bweak;
	case 0x03e4: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv01_gw_mthd_ifc(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_chwoma; bweak;
	case 0x0188: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x018c: func = nv01_gw_mthd_bind_patt; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_suwf_dst; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_ifc(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_chwoma; bweak;
	case 0x0188: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_patt; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_beta4; bweak;
	case 0x019c: func = nv04_gw_mthd_bind_suwf2d; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv03_gw_mthd_sifc(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_chwoma; bweak;
	case 0x0188: func = nv01_gw_mthd_bind_patt; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_suwf_dst; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_sifc(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_chwoma; bweak;
	case 0x0188: func = nv04_gw_mthd_bind_patt; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta4; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_suwf2d; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv03_gw_mthd_sifm(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0188: func = nv01_gw_mthd_bind_patt; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_suwf_dst; bweak;
	case 0x0304: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_sifm(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0188: func = nv04_gw_mthd_bind_patt; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta4; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_suwf2d; bweak;
	case 0x0304: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_suwf3d(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x02f8: func = nv04_gw_mthd_suwf3d_cwip_h; bweak;
	case 0x02fc: func = nv04_gw_mthd_suwf3d_cwip_v; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv03_gw_mthd_ttwi(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0188: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_suwf_cowow; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_suwf_zeta; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv01_gw_mthd_pwim(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x0188: func = nv01_gw_mthd_bind_patt; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_suwf_dst; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd_pwim(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0184: func = nv01_gw_mthd_bind_cwip; bweak;
	case 0x0188: func = nv04_gw_mthd_bind_patt; bweak;
	case 0x018c: func = nv04_gw_mthd_bind_wop; bweak;
	case 0x0190: func = nv04_gw_mthd_bind_beta1; bweak;
	case 0x0194: func = nv04_gw_mthd_bind_beta4; bweak;
	case 0x0198: func = nv04_gw_mthd_bind_suwf2d; bweak;
	case 0x02fc: func = nv04_gw_mthd_set_opewation; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, data);
}

static boow
nv04_gw_mthd(stwuct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	boow (*func)(stwuct nvkm_device *, u32, u32, u32);
	switch (nvkm_wd32(device, 0x700000 + inst) & 0x000000ff) {
	case 0x1c ... 0x1e:
		   func = nv01_gw_mthd_pwim; bweak;
	case 0x1f: func = nv01_gw_mthd_bwit; bweak;
	case 0x21: func = nv01_gw_mthd_ifc; bweak;
	case 0x36: func = nv03_gw_mthd_sifc; bweak;
	case 0x37: func = nv03_gw_mthd_sifm; bweak;
	case 0x48: func = nv03_gw_mthd_ttwi; bweak;
	case 0x4a: func = nv04_gw_mthd_gdi; bweak;
	case 0x4b: func = nv03_gw_mthd_gdi; bweak;
	case 0x53: func = nv04_gw_mthd_suwf3d; bweak;
	case 0x5c ... 0x5e:
		   func = nv04_gw_mthd_pwim; bweak;
	case 0x5f: func = nv04_gw_mthd_bwit; bweak;
	case 0x60: func = nv04_gw_mthd_iifc; bweak;
	case 0x61: func = nv04_gw_mthd_ifc; bweak;
	case 0x76: func = nv04_gw_mthd_sifc; bweak;
	case 0x77: func = nv04_gw_mthd_sifm; bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn func(device, inst, mthd, data);
}

static int
nv04_gw_object_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		    int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	int wet = nvkm_gpuobj_new(object->engine->subdev.device, 16, awign,
				  fawse, pawent, pgpuobj);
	if (wet == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->ocwass);
#ifdef __BIG_ENDIAN
		nvkm_mo32(*pgpuobj, 0x00, 0x00080000, 0x00080000);
#endif
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_done(*pgpuobj);
	}
	wetuwn wet;
}

const stwuct nvkm_object_func
nv04_gw_object = {
	.bind = nv04_gw_object_bind,
};

/*******************************************************************************
 * PGWAPH context
 ******************************************************************************/

static stwuct nv04_gw_chan *
nv04_gw_channew(stwuct nv04_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nv04_gw_chan *chan = NUWW;
	if (nvkm_wd32(device, NV04_PGWAPH_CTX_CONTWOW) & 0x00010000) {
		int chid = nvkm_wd32(device, NV04_PGWAPH_CTX_USEW) >> 24;
		if (chid < AWWAY_SIZE(gw->chan))
			chan = gw->chan[chid];
	}
	wetuwn chan;
}

static int
nv04_gw_woad_context(stwuct nv04_gw_chan *chan, int chid)
{
	stwuct nvkm_device *device = chan->gw->base.engine.subdev.device;
	int i;

	fow (i = 0; i < AWWAY_SIZE(nv04_gw_ctx_wegs); i++)
		nvkm_ww32(device, nv04_gw_ctx_wegs[i], chan->nv04[i]);

	nvkm_ww32(device, NV04_PGWAPH_CTX_CONTWOW, 0x10010100);
	nvkm_mask(device, NV04_PGWAPH_CTX_USEW, 0xff000000, chid << 24);
	nvkm_mask(device, NV04_PGWAPH_FFINTFC_ST2, 0xfff00000, 0x00000000);
	wetuwn 0;
}

static int
nv04_gw_unwoad_context(stwuct nv04_gw_chan *chan)
{
	stwuct nvkm_device *device = chan->gw->base.engine.subdev.device;
	int i;

	fow (i = 0; i < AWWAY_SIZE(nv04_gw_ctx_wegs); i++)
		chan->nv04[i] = nvkm_wd32(device, nv04_gw_ctx_wegs[i]);

	nvkm_ww32(device, NV04_PGWAPH_CTX_CONTWOW, 0x10000000);
	nvkm_mask(device, NV04_PGWAPH_CTX_USEW, 0xff000000, 0x0f000000);
	wetuwn 0;
}

static void
nv04_gw_context_switch(stwuct nv04_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nv04_gw_chan *pwev = NUWW;
	stwuct nv04_gw_chan *next = NUWW;
	int chid;

	nv04_gw_idwe(&gw->base);

	/* If pwevious context is vawid, we need to save it */
	pwev = nv04_gw_channew(gw);
	if (pwev)
		nv04_gw_unwoad_context(pwev);

	/* woad context fow next channew */
	chid = (nvkm_wd32(device, NV04_PGWAPH_TWAPPED_ADDW) >> 24) & 0x0f;
	next = gw->chan[chid];
	if (next)
		nv04_gw_woad_context(next, chid);
}

static u32 *ctx_weg(stwuct nv04_gw_chan *chan, u32 weg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(nv04_gw_ctx_wegs); i++) {
		if (nv04_gw_ctx_wegs[i] == weg)
			wetuwn &chan->nv04[i];
	}

	wetuwn NUWW;
}

static void *
nv04_gw_chan_dtow(stwuct nvkm_object *object)
{
	stwuct nv04_gw_chan *chan = nv04_gw_chan(object);
	stwuct nv04_gw *gw = chan->gw;
	unsigned wong fwags;

	spin_wock_iwqsave(&gw->wock, fwags);
	gw->chan[chan->chid] = NUWW;
	spin_unwock_iwqwestowe(&gw->wock, fwags);
	wetuwn chan;
}

static int
nv04_gw_chan_fini(stwuct nvkm_object *object, boow suspend)
{
	stwuct nv04_gw_chan *chan = nv04_gw_chan(object);
	stwuct nv04_gw *gw = chan->gw;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	unsigned wong fwags;

	spin_wock_iwqsave(&gw->wock, fwags);
	nvkm_mask(device, NV04_PGWAPH_FIFO, 0x00000001, 0x00000000);
	if (nv04_gw_channew(gw) == chan)
		nv04_gw_unwoad_context(chan);
	nvkm_mask(device, NV04_PGWAPH_FIFO, 0x00000001, 0x00000001);
	spin_unwock_iwqwestowe(&gw->wock, fwags);
	wetuwn 0;
}

static const stwuct nvkm_object_func
nv04_gw_chan = {
	.dtow = nv04_gw_chan_dtow,
	.fini = nv04_gw_chan_fini,
};

static int
nv04_gw_chan_new(stwuct nvkm_gw *base, stwuct nvkm_chan *fifoch,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_object **pobject)
{
	stwuct nv04_gw *gw = nv04_gw(base);
	stwuct nv04_gw_chan *chan;
	unsigned wong fwags;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nv04_gw_chan, ocwass, &chan->object);
	chan->gw = gw;
	chan->chid = fifoch->id;
	*pobject = &chan->object;

	*ctx_weg(chan, NV04_PGWAPH_DEBUG_3) = 0xfad4ff31;

	spin_wock_iwqsave(&gw->wock, fwags);
	gw->chan[chan->chid] = chan;
	spin_unwock_iwqwestowe(&gw->wock, fwags);
	wetuwn 0;
}

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

boow
nv04_gw_idwe(stwuct nvkm_gw *gw)
{
	stwuct nvkm_subdev *subdev = &gw->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mask = 0xffffffff;

	if (device->cawd_type == NV_40)
		mask &= ~NV40_PGWAPH_STATUS_SYNC_STAWW;

	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, NV04_PGWAPH_STATUS) & mask))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "idwe timed out with status %08x\n",
			   nvkm_wd32(device, NV04_PGWAPH_STATUS));
		wetuwn fawse;
	}

	wetuwn twue;
}

static const stwuct nvkm_bitfiewd
nv04_gw_intw_name[] = {
	{ NV_PGWAPH_INTW_NOTIFY, "NOTIFY" },
	{}
};

static const stwuct nvkm_bitfiewd
nv04_gw_nstatus[] = {
	{ NV04_PGWAPH_NSTATUS_STATE_IN_USE,       "STATE_IN_USE" },
	{ NV04_PGWAPH_NSTATUS_INVAWID_STATE,      "INVAWID_STATE" },
	{ NV04_PGWAPH_NSTATUS_BAD_AWGUMENT,       "BAD_AWGUMENT" },
	{ NV04_PGWAPH_NSTATUS_PWOTECTION_FAUWT,   "PWOTECTION_FAUWT" },
	{}
};

const stwuct nvkm_bitfiewd
nv04_gw_nsouwce[] = {
	{ NV03_PGWAPH_NSOUWCE_NOTIFICATION,       "NOTIFICATION" },
	{ NV03_PGWAPH_NSOUWCE_DATA_EWWOW,         "DATA_EWWOW" },
	{ NV03_PGWAPH_NSOUWCE_PWOTECTION_EWWOW,   "PWOTECTION_EWWOW" },
	{ NV03_PGWAPH_NSOUWCE_WANGE_EXCEPTION,    "WANGE_EXCEPTION" },
	{ NV03_PGWAPH_NSOUWCE_WIMIT_COWOW,        "WIMIT_COWOW" },
	{ NV03_PGWAPH_NSOUWCE_WIMIT_ZETA,         "WIMIT_ZETA" },
	{ NV03_PGWAPH_NSOUWCE_IWWEGAW_MTHD,       "IWWEGAW_MTHD" },
	{ NV03_PGWAPH_NSOUWCE_DMA_W_PWOTECTION,   "DMA_W_PWOTECTION" },
	{ NV03_PGWAPH_NSOUWCE_DMA_W_PWOTECTION,   "DMA_W_PWOTECTION" },
	{ NV03_PGWAPH_NSOUWCE_FOWMAT_EXCEPTION,   "FOWMAT_EXCEPTION" },
	{ NV03_PGWAPH_NSOUWCE_PATCH_EXCEPTION,    "PATCH_EXCEPTION" },
	{ NV03_PGWAPH_NSOUWCE_STATE_INVAWID,      "STATE_INVAWID" },
	{ NV03_PGWAPH_NSOUWCE_DOUBWE_NOTIFY,      "DOUBWE_NOTIFY" },
	{ NV03_PGWAPH_NSOUWCE_NOTIFY_IN_USE,      "NOTIFY_IN_USE" },
	{ NV03_PGWAPH_NSOUWCE_METHOD_CNT,         "METHOD_CNT" },
	{ NV03_PGWAPH_NSOUWCE_BFW_NOTIFICATION,   "BFW_NOTIFICATION" },
	{ NV03_PGWAPH_NSOUWCE_DMA_VTX_PWOTECTION, "DMA_VTX_PWOTECTION" },
	{ NV03_PGWAPH_NSOUWCE_DMA_WIDTH_A,        "DMA_WIDTH_A" },
	{ NV03_PGWAPH_NSOUWCE_DMA_WIDTH_B,        "DMA_WIDTH_B" },
	{}
};

static void
nv04_gw_intw(stwuct nvkm_gw *base)
{
	stwuct nv04_gw *gw = nv04_gw(base);
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, NV03_PGWAPH_INTW);
	u32 nsouwce = nvkm_wd32(device, NV03_PGWAPH_NSOUWCE);
	u32 nstatus = nvkm_wd32(device, NV03_PGWAPH_NSTATUS);
	u32 addw = nvkm_wd32(device, NV04_PGWAPH_TWAPPED_ADDW);
	u32 chid = (addw & 0x0f000000) >> 24;
	u32 subc = (addw & 0x0000e000) >> 13;
	u32 mthd = (addw & 0x00001ffc);
	u32 data = nvkm_wd32(device, NV04_PGWAPH_TWAPPED_DATA);
	u32 cwass = nvkm_wd32(device, 0x400180 + subc * 4) & 0xff;
	u32 inst = (nvkm_wd32(device, 0x40016c) & 0xffff) << 4;
	u32 show = stat;
	chaw msg[128], swc[128], sta[128];
	stwuct nv04_gw_chan *chan;
	unsigned wong fwags;

	spin_wock_iwqsave(&gw->wock, fwags);
	chan = gw->chan[chid];

	if (stat & NV_PGWAPH_INTW_NOTIFY) {
		if (chan && (nsouwce & NV03_PGWAPH_NSOUWCE_IWWEGAW_MTHD)) {
			if (!nv04_gw_mthd(device, inst, mthd, data))
				show &= ~NV_PGWAPH_INTW_NOTIFY;
		}
	}

	if (stat & NV_PGWAPH_INTW_CONTEXT_SWITCH) {
		nvkm_ww32(device, NV03_PGWAPH_INTW, NV_PGWAPH_INTW_CONTEXT_SWITCH);
		stat &= ~NV_PGWAPH_INTW_CONTEXT_SWITCH;
		show &= ~NV_PGWAPH_INTW_CONTEXT_SWITCH;
		nv04_gw_context_switch(gw);
	}

	nvkm_ww32(device, NV03_PGWAPH_INTW, stat);
	nvkm_ww32(device, NV04_PGWAPH_FIFO, 0x00000001);

	if (show) {
		nvkm_snpwintbf(msg, sizeof(msg), nv04_gw_intw_name, show);
		nvkm_snpwintbf(swc, sizeof(swc), nv04_gw_nsouwce, nsouwce);
		nvkm_snpwintbf(sta, sizeof(sta), nv04_gw_nstatus, nstatus);
		nvkm_ewwow(subdev, "intw %08x [%s] nsouwce %08x [%s] "
				   "nstatus %08x [%s] ch %d [%s] subc %d "
				   "cwass %04x mthd %04x data %08x\n",
			   show, msg, nsouwce, swc, nstatus, sta, chid,
			   chan ? chan->object.cwient->name : "unknown",
			   subc, cwass, mthd, data);
	}

	spin_unwock_iwqwestowe(&gw->wock, fwags);
}

static int
nv04_gw_init(stwuct nvkm_gw *base)
{
	stwuct nv04_gw *gw = nv04_gw(base);
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	/* Enabwe PGWAPH intewwupts */
	nvkm_ww32(device, NV03_PGWAPH_INTW, 0xFFFFFFFF);
	nvkm_ww32(device, NV03_PGWAPH_INTW_EN, 0xFFFFFFFF);

	nvkm_ww32(device, NV04_PGWAPH_VAWID1, 0);
	nvkm_ww32(device, NV04_PGWAPH_VAWID2, 0);
	/*nvkm_ww32(device, NV04_PGWAPH_DEBUG_0, 0x000001FF);
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_0, 0x001FFFFF);*/
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_0, 0x1231c000);
	/*1231C000 bwob, 001 haiku*/
	/*V_WWITE(NV04_PGWAPH_DEBUG_1, 0xf2d91100);*/
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_1, 0x72111100);
	/*0x72111100 bwob , 01 haiku*/
	/*nvkm_ww32(device, NV04_PGWAPH_DEBUG_2, 0x11d5f870);*/
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_2, 0x11d5f071);
	/*haiku same*/

	/*nvkm_ww32(device, NV04_PGWAPH_DEBUG_3, 0xfad4ff31);*/
	nvkm_ww32(device, NV04_PGWAPH_DEBUG_3, 0xf0d4ff31);
	/*haiku and bwob 10d4*/

	nvkm_ww32(device, NV04_PGWAPH_STATE        , 0xFFFFFFFF);
	nvkm_ww32(device, NV04_PGWAPH_CTX_CONTWOW  , 0x10000100);
	nvkm_mask(device, NV04_PGWAPH_CTX_USEW, 0xff000000, 0x0f000000);

	/* These don't bewong hewe, they'we pawt of a pew-channew context */
	nvkm_ww32(device, NV04_PGWAPH_PATTEWN_SHAPE, 0x00000000);
	nvkm_ww32(device, NV04_PGWAPH_BETA_AND     , 0xFFFFFFFF);
	wetuwn 0;
}

static const stwuct nvkm_gw_func
nv04_gw = {
	.init = nv04_gw_init,
	.intw = nv04_gw_intw,
	.chan_new = nv04_gw_chan_new,
	.scwass = {
		{ -1, -1, 0x0012, &nv04_gw_object }, /* beta1 */
		{ -1, -1, 0x0017, &nv04_gw_object }, /* chwoma */
		{ -1, -1, 0x0018, &nv04_gw_object }, /* pattewn (nv01) */
		{ -1, -1, 0x0019, &nv04_gw_object }, /* cwip */
		{ -1, -1, 0x001c, &nv04_gw_object }, /* wine */
		{ -1, -1, 0x001d, &nv04_gw_object }, /* twi */
		{ -1, -1, 0x001e, &nv04_gw_object }, /* wect */
		{ -1, -1, 0x001f, &nv04_gw_object },
		{ -1, -1, 0x0021, &nv04_gw_object },
		{ -1, -1, 0x0030, &nv04_gw_object }, /* nuww */
		{ -1, -1, 0x0036, &nv04_gw_object },
		{ -1, -1, 0x0037, &nv04_gw_object },
		{ -1, -1, 0x0038, &nv04_gw_object }, /* dvd subpictuwe */
		{ -1, -1, 0x0039, &nv04_gw_object }, /* m2mf */
		{ -1, -1, 0x0042, &nv04_gw_object }, /* suwf2d */
		{ -1, -1, 0x0043, &nv04_gw_object }, /* wop */
		{ -1, -1, 0x0044, &nv04_gw_object }, /* pattewn */
		{ -1, -1, 0x0048, &nv04_gw_object },
		{ -1, -1, 0x004a, &nv04_gw_object },
		{ -1, -1, 0x004b, &nv04_gw_object },
		{ -1, -1, 0x0052, &nv04_gw_object }, /* swzsuwf */
		{ -1, -1, 0x0053, &nv04_gw_object },
		{ -1, -1, 0x0054, &nv04_gw_object }, /* ttwi */
		{ -1, -1, 0x0055, &nv04_gw_object }, /* mtwi */
		{ -1, -1, 0x0057, &nv04_gw_object }, /* chwoma */
		{ -1, -1, 0x0058, &nv04_gw_object }, /* suwf_dst */
		{ -1, -1, 0x0059, &nv04_gw_object }, /* suwf_swc */
		{ -1, -1, 0x005a, &nv04_gw_object }, /* suwf_cowow */
		{ -1, -1, 0x005b, &nv04_gw_object }, /* suwf_zeta */
		{ -1, -1, 0x005c, &nv04_gw_object }, /* wine */
		{ -1, -1, 0x005d, &nv04_gw_object }, /* twi */
		{ -1, -1, 0x005e, &nv04_gw_object }, /* wect */
		{ -1, -1, 0x005f, &nv04_gw_object },
		{ -1, -1, 0x0060, &nv04_gw_object },
		{ -1, -1, 0x0061, &nv04_gw_object },
		{ -1, -1, 0x0064, &nv04_gw_object }, /* iifc (nv05) */
		{ -1, -1, 0x0065, &nv04_gw_object }, /* ifc (nv05) */
		{ -1, -1, 0x0066, &nv04_gw_object }, /* sifc (nv05) */
		{ -1, -1, 0x0072, &nv04_gw_object }, /* beta4 */
		{ -1, -1, 0x0076, &nv04_gw_object },
		{ -1, -1, 0x0077, &nv04_gw_object },
		{}
	}
};

int
nv04_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	stwuct nv04_gw *gw;

	if (!(gw = kzawwoc(sizeof(*gw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	spin_wock_init(&gw->wock);
	*pgw = &gw->base;

	wetuwn nvkm_gw_ctow(&nv04_gw, device, type, inst, twue, &gw->base);
}
