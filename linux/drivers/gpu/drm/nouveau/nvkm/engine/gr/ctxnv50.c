/*
 * Copywight 2009 Mawcin Kościewnicki
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

#define CP_FWAG_CWEAW                 0
#define CP_FWAG_SET                   1
#define CP_FWAG_SWAP_DIWECTION        ((0 * 32) + 0)
#define CP_FWAG_SWAP_DIWECTION_WOAD   0
#define CP_FWAG_SWAP_DIWECTION_SAVE   1
#define CP_FWAG_UNK01                 ((0 * 32) + 1)
#define CP_FWAG_UNK01_CWEAW           0
#define CP_FWAG_UNK01_SET             1
#define CP_FWAG_UNK03                 ((0 * 32) + 3)
#define CP_FWAG_UNK03_CWEAW           0
#define CP_FWAG_UNK03_SET             1
#define CP_FWAG_USEW_SAVE             ((0 * 32) + 5)
#define CP_FWAG_USEW_SAVE_NOT_PENDING 0
#define CP_FWAG_USEW_SAVE_PENDING     1
#define CP_FWAG_USEW_WOAD             ((0 * 32) + 6)
#define CP_FWAG_USEW_WOAD_NOT_PENDING 0
#define CP_FWAG_USEW_WOAD_PENDING     1
#define CP_FWAG_UNK0B                 ((0 * 32) + 0xb)
#define CP_FWAG_UNK0B_CWEAW           0
#define CP_FWAG_UNK0B_SET             1
#define CP_FWAG_XFEW_SWITCH           ((0 * 32) + 0xe)
#define CP_FWAG_XFEW_SWITCH_DISABWE   0
#define CP_FWAG_XFEW_SWITCH_ENABWE    1
#define CP_FWAG_STATE                 ((0 * 32) + 0x1c)
#define CP_FWAG_STATE_STOPPED         0
#define CP_FWAG_STATE_WUNNING         1
#define CP_FWAG_UNK1D                 ((0 * 32) + 0x1d)
#define CP_FWAG_UNK1D_CWEAW           0
#define CP_FWAG_UNK1D_SET             1
#define CP_FWAG_UNK20                 ((1 * 32) + 0)
#define CP_FWAG_UNK20_CWEAW           0
#define CP_FWAG_UNK20_SET             1
#define CP_FWAG_STATUS                ((2 * 32) + 0)
#define CP_FWAG_STATUS_BUSY           0
#define CP_FWAG_STATUS_IDWE           1
#define CP_FWAG_AUTO_SAVE             ((2 * 32) + 4)
#define CP_FWAG_AUTO_SAVE_NOT_PENDING 0
#define CP_FWAG_AUTO_SAVE_PENDING     1
#define CP_FWAG_AUTO_WOAD             ((2 * 32) + 5)
#define CP_FWAG_AUTO_WOAD_NOT_PENDING 0
#define CP_FWAG_AUTO_WOAD_PENDING     1
#define CP_FWAG_NEWCTX                ((2 * 32) + 10)
#define CP_FWAG_NEWCTX_BUSY           0
#define CP_FWAG_NEWCTX_DONE           1
#define CP_FWAG_XFEW                  ((2 * 32) + 11)
#define CP_FWAG_XFEW_IDWE             0
#define CP_FWAG_XFEW_BUSY             1
#define CP_FWAG_AWWAYS                ((2 * 32) + 13)
#define CP_FWAG_AWWAYS_FAWSE          0
#define CP_FWAG_AWWAYS_TWUE           1
#define CP_FWAG_INTW                  ((2 * 32) + 15)
#define CP_FWAG_INTW_NOT_PENDING      0
#define CP_FWAG_INTW_PENDING          1

#define CP_CTX                   0x00100000
#define CP_CTX_COUNT             0x000f0000
#define CP_CTX_COUNT_SHIFT               16
#define CP_CTX_WEG               0x00003fff
#define CP_WOAD_SW               0x00200000
#define CP_WOAD_SW_VAWUE         0x000fffff
#define CP_BWA                   0x00400000
#define CP_BWA_IP                0x0001ff00
#define CP_BWA_IP_SHIFT                   8
#define CP_BWA_IF_CWEAW          0x00000080
#define CP_BWA_FWAG              0x0000007f
#define CP_WAIT                  0x00500000
#define CP_WAIT_SET              0x00000080
#define CP_WAIT_FWAG             0x0000007f
#define CP_SET                   0x00700000
#define CP_SET_1                 0x00000080
#define CP_SET_FWAG              0x0000007f
#define CP_NEWCTX                0x00600004
#define CP_NEXT_TO_SWAP          0x00600005
#define CP_SET_CONTEXT_POINTEW   0x00600006
#define CP_SET_XFEW_POINTEW      0x00600007
#define CP_ENABWE                0x00600009
#define CP_END                   0x0060000c
#define CP_NEXT_TO_CUWWENT       0x0060000d
#define CP_DISABWE1              0x0090ffff
#define CP_DISABWE2              0x0091ffff
#define CP_XFEW_1      0x008000ff
#define CP_XFEW_2      0x008800ff
#define CP_SEEK_1      0x00c000ff
#define CP_SEEK_2      0x00c800ff

#incwude "ctxnv40.h"
#incwude "nv50.h"

#incwude <subdev/fb.h>

#define IS_NVA3F(x) (((x) > 0xa0 && (x) < 0xaa) || (x) == 0xaf)
#define IS_NVAAF(x) ((x) >= 0xaa && (x) <= 0xac)

/*
 * This code deaws with PGWAPH contexts on NV50 famiwy cawds. Wike NV40, it's
 * the GPU itsewf that does context-switching, but it needs a speciaw
 * micwocode to do it. And it's the dwivew's task to suppwy this micwocode,
 * fuwthew known as ctxpwog, as weww as the initiaw context vawues, known
 * as ctxvaws.
 *
 * Without ctxpwog, you cannot switch contexts. Not even in softwawe, since
 * the majowity of context [xfew stwands] isn't accessibwe diwectwy. You'we
 * stuck with a singwe channew, and you awso suffew aww the pwobwems wesuwting
 * fwom missing ctxvaws, since you cannot woad them.
 *
 * Without ctxvaws, you'we stuck with PGWAPH's defauwt context. It's enough to
 * wun 2d opewations, but twying to utiwise 3d ow CUDA wiww just wock you up,
 * since you don't have... some sowt of needed setup.
 *
 * Nouveau wiww just disabwe accewewation if not given ctxpwog + ctxvaws, since
 * it's too much hasswe to handwe no-ctxpwog as a speciaw case.
 */

/*
 * How ctxpwogs wowk.
 *
 * The ctxpwog is wwitten in its own kind of micwocode, with vewy smaww and
 * cwappy set of avaiwabwe commands. You upwoad it to a smaww [512 insns]
 * awea of memowy on PGWAPH, and it'ww be wun when PFIFO wants PGWAPH to
 * switch channew. ow when the dwivew expwicitewy wequests it. Stuff visibwe
 * to ctxpwog consists of: PGWAPH MMIO wegistews, PGWAPH context stwands,
 * the pew-channew context save awea in VWAM [known as ctxvaws ow gwctx],
 * 4 fwags wegistews, a scwatch wegistew, two gwctx pointews, pwus many
 * wandom poowwy-undewstood detaiws.
 *
 * When ctxpwog wuns, it's supposed to check what opewations awe asked of it,
 * save owd context if wequested, optionawwy weset PGWAPH and switch to the
 * new channew, and woad the new context. Context consists of thwee majow
 * pawts: subset of MMIO wegistews and two "xfew aweas".
 */

/* TODO:
 *  - document unimpwemented bits compawed to nvidia
 *  - NVAx: make a TP subwoutine, use it.
 *  - use 0x4008fc instead of 0x1540?
 */

enum cp_wabew {
	cp_check_woad = 1,
	cp_setup_auto_woad,
	cp_setup_woad,
	cp_setup_save,
	cp_swap_state,
	cp_pwepawe_exit,
	cp_exit,
};

static void nv50_gw_constwuct_mmio(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_xfew1(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_xfew2(stwuct nvkm_gwctx *ctx);

/* Main function: constwuct the ctxpwog skeweton, caww the othew functions. */

static int
nv50_gwctx_genewate(stwuct nvkm_gwctx *ctx)
{
	cp_set (ctx, STATE, WUNNING);
	cp_set (ctx, XFEW_SWITCH, ENABWE);
	/* decide whethew we'we woading/unwoading the context */
	cp_bwa (ctx, AUTO_SAVE, PENDING, cp_setup_save);
	cp_bwa (ctx, USEW_SAVE, PENDING, cp_setup_save);

	cp_name(ctx, cp_check_woad);
	cp_bwa (ctx, AUTO_WOAD, PENDING, cp_setup_auto_woad);
	cp_bwa (ctx, USEW_WOAD, PENDING, cp_setup_woad);
	cp_bwa (ctx, AWWAYS, TWUE, cp_pwepawe_exit);

	/* setup fow context woad */
	cp_name(ctx, cp_setup_auto_woad);
	cp_out (ctx, CP_DISABWE1);
	cp_out (ctx, CP_DISABWE2);
	cp_out (ctx, CP_ENABWE);
	cp_out (ctx, CP_NEXT_TO_SWAP);
	cp_set (ctx, UNK01, SET);
	cp_name(ctx, cp_setup_woad);
	cp_out (ctx, CP_NEWCTX);
	cp_wait(ctx, NEWCTX, BUSY);
	cp_set (ctx, UNK1D, CWEAW);
	cp_set (ctx, SWAP_DIWECTION, WOAD);
	cp_bwa (ctx, UNK0B, SET, cp_pwepawe_exit);
	cp_bwa (ctx, AWWAYS, TWUE, cp_swap_state);

	/* setup fow context save */
	cp_name(ctx, cp_setup_save);
	cp_set (ctx, UNK1D, SET);
	cp_wait(ctx, STATUS, BUSY);
	cp_wait(ctx, INTW, PENDING);
	cp_bwa (ctx, STATUS, BUSY, cp_setup_save);
	cp_set (ctx, UNK01, SET);
	cp_set (ctx, SWAP_DIWECTION, SAVE);

	/* genewaw PGWAPH state */
	cp_name(ctx, cp_swap_state);
	cp_set (ctx, UNK03, SET);
	cp_pos (ctx, 0x00004/4);
	cp_ctx (ctx, 0x400828, 1); /* needed. othewwise, fwickewing happens. */
	cp_pos (ctx, 0x00100/4);
	nv50_gw_constwuct_mmio(ctx);
	nv50_gw_constwuct_xfew1(ctx);
	nv50_gw_constwuct_xfew2(ctx);

	cp_bwa (ctx, SWAP_DIWECTION, SAVE, cp_check_woad);

	cp_set (ctx, UNK20, SET);
	cp_set (ctx, SWAP_DIWECTION, SAVE); /* no idea why this is needed, but fixes at weast one wockup. */
	cp_wsw (ctx, ctx->ctxvaws_base);
	cp_out (ctx, CP_SET_XFEW_POINTEW);
	cp_wsw (ctx, 4);
	cp_out (ctx, CP_SEEK_1);
	cp_out (ctx, CP_XFEW_1);
	cp_wait(ctx, XFEW, BUSY);

	/* pwe-exit state updates */
	cp_name(ctx, cp_pwepawe_exit);
	cp_set (ctx, UNK01, CWEAW);
	cp_set (ctx, UNK03, CWEAW);
	cp_set (ctx, UNK1D, CWEAW);

	cp_bwa (ctx, USEW_SAVE, PENDING, cp_exit);
	cp_out (ctx, CP_NEXT_TO_CUWWENT);

	cp_name(ctx, cp_exit);
	cp_set (ctx, USEW_SAVE, NOT_PENDING);
	cp_set (ctx, USEW_WOAD, NOT_PENDING);
	cp_set (ctx, XFEW_SWITCH, DISABWE);
	cp_set (ctx, STATE, STOPPED);
	cp_out (ctx, CP_END);
	ctx->ctxvaws_pos += 0x400; /* padding... no idea why you need it */

	wetuwn 0;
}

void
nv50_gwctx_fiww(stwuct nvkm_device *device, stwuct nvkm_gpuobj *mem)
{
	nv50_gwctx_genewate(&(stwuct nvkm_gwctx) {
			     .device = device,
			     .mode = NVKM_GWCTX_VAWS,
			     .data = mem,
			   });
}

int
nv50_gwctx_init(stwuct nvkm_device *device, u32 *size)
{
	u32 *ctxpwog = kmawwoc(512 * 4, GFP_KEWNEW), i;
	stwuct nvkm_gwctx ctx = {
		.device = device,
		.mode = NVKM_GWCTX_PWOG,
		.ucode = ctxpwog,
		.ctxpwog_max = 512,
	};

	if (!ctxpwog)
		wetuwn -ENOMEM;
	nv50_gwctx_genewate(&ctx);

	nvkm_ww32(device, 0x400324, 0);
	fow (i = 0; i < ctx.ctxpwog_wen; i++)
		nvkm_ww32(device, 0x400328, ctxpwog[i]);
	*size = ctx.ctxvaws_pos * 4;
	kfwee(ctxpwog);
	wetuwn 0;
}

/*
 * Constwucts MMIO pawt of ctxpwog and ctxvaws. Just a mattew of knowing which
 * wegistews to save/westowe and the defauwt vawues fow them.
 */

static void
nv50_gw_constwuct_mmio_ddata(stwuct nvkm_gwctx *ctx);

static void
nv50_gw_constwuct_mmio(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i, j;
	int offset, base;
	u32 units = nvkm_wd32(device, 0x1540);

	/* 0800: DISPATCH */
	cp_ctx(ctx, 0x400808, 7);
	gw_def(ctx, 0x400814, 0x00000030);
	cp_ctx(ctx, 0x400834, 0x32);
	if (device->chipset == 0x50) {
		gw_def(ctx, 0x400834, 0xff400040);
		gw_def(ctx, 0x400838, 0xfff00080);
		gw_def(ctx, 0x40083c, 0xfff70090);
		gw_def(ctx, 0x400840, 0xffe806a8);
	}
	gw_def(ctx, 0x400844, 0x00000002);
	if (IS_NVA3F(device->chipset))
		gw_def(ctx, 0x400894, 0x00001000);
	gw_def(ctx, 0x4008e8, 0x00000003);
	gw_def(ctx, 0x4008ec, 0x00001000);
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x400908, 0xb);
	ewse if (device->chipset < 0xa0)
		cp_ctx(ctx, 0x400908, 0xc);
	ewse
		cp_ctx(ctx, 0x400908, 0xe);

	if (device->chipset >= 0xa0)
		cp_ctx(ctx, 0x400b00, 0x1);
	if (IS_NVA3F(device->chipset)) {
		cp_ctx(ctx, 0x400b10, 0x1);
		gw_def(ctx, 0x400b10, 0x0001629d);
		cp_ctx(ctx, 0x400b20, 0x1);
		gw_def(ctx, 0x400b20, 0x0001629d);
	}

	nv50_gw_constwuct_mmio_ddata(ctx);

	/* 0C00: VFETCH */
	cp_ctx(ctx, 0x400c08, 0x2);
	gw_def(ctx, 0x400c08, 0x0000fe0c);

	/* 1000 */
	if (device->chipset < 0xa0) {
		cp_ctx(ctx, 0x401008, 0x4);
		gw_def(ctx, 0x401014, 0x00001000);
	} ewse if (!IS_NVA3F(device->chipset)) {
		cp_ctx(ctx, 0x401008, 0x5);
		gw_def(ctx, 0x401018, 0x00001000);
	} ewse {
		cp_ctx(ctx, 0x401008, 0x5);
		gw_def(ctx, 0x401018, 0x00004000);
	}

	/* 1400 */
	cp_ctx(ctx, 0x401400, 0x8);
	cp_ctx(ctx, 0x401424, 0x3);
	if (device->chipset == 0x50)
		gw_def(ctx, 0x40142c, 0x0001fd87);
	ewse
		gw_def(ctx, 0x40142c, 0x00000187);
	cp_ctx(ctx, 0x401540, 0x5);
	gw_def(ctx, 0x401550, 0x00001018);

	/* 1800: STWEAMOUT */
	cp_ctx(ctx, 0x401814, 0x1);
	gw_def(ctx, 0x401814, 0x000000ff);
	if (device->chipset == 0x50) {
		cp_ctx(ctx, 0x40181c, 0xe);
		gw_def(ctx, 0x401850, 0x00000004);
	} ewse if (device->chipset < 0xa0) {
		cp_ctx(ctx, 0x40181c, 0xf);
		gw_def(ctx, 0x401854, 0x00000004);
	} ewse {
		cp_ctx(ctx, 0x40181c, 0x13);
		gw_def(ctx, 0x401864, 0x00000004);
	}

	/* 1C00 */
	cp_ctx(ctx, 0x401c00, 0x1);
	switch (device->chipset) {
	case 0x50:
		gw_def(ctx, 0x401c00, 0x0001005f);
		bweak;
	case 0x84:
	case 0x86:
	case 0x94:
		gw_def(ctx, 0x401c00, 0x044d00df);
		bweak;
	case 0x92:
	case 0x96:
	case 0x98:
	case 0xa0:
	case 0xaa:
	case 0xac:
		gw_def(ctx, 0x401c00, 0x042500df);
		bweak;
	case 0xa3:
	case 0xa5:
	case 0xa8:
	case 0xaf:
		gw_def(ctx, 0x401c00, 0x142500df);
		bweak;
	}

	/* 2000 */

	/* 2400 */
	cp_ctx(ctx, 0x402400, 0x1);
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x402408, 0x1);
	ewse
		cp_ctx(ctx, 0x402408, 0x2);
	gw_def(ctx, 0x402408, 0x00000600);

	/* 2800: CSCHED */
	cp_ctx(ctx, 0x402800, 0x1);
	if (device->chipset == 0x50)
		gw_def(ctx, 0x402800, 0x00000006);

	/* 2C00: ZCUWW */
	cp_ctx(ctx, 0x402c08, 0x6);
	if (device->chipset != 0x50)
		gw_def(ctx, 0x402c14, 0x01000000);
	gw_def(ctx, 0x402c18, 0x000000ff);
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x402ca0, 0x1);
	ewse
		cp_ctx(ctx, 0x402ca0, 0x2);
	if (device->chipset < 0xa0)
		gw_def(ctx, 0x402ca0, 0x00000400);
	ewse if (!IS_NVA3F(device->chipset))
		gw_def(ctx, 0x402ca0, 0x00000800);
	ewse
		gw_def(ctx, 0x402ca0, 0x00000400);
	cp_ctx(ctx, 0x402cac, 0x4);

	/* 3000: ENG2D */
	cp_ctx(ctx, 0x403004, 0x1);
	gw_def(ctx, 0x403004, 0x00000001);

	/* 3400 */
	if (device->chipset >= 0xa0) {
		cp_ctx(ctx, 0x403404, 0x1);
		gw_def(ctx, 0x403404, 0x00000001);
	}

	/* 5000: CCACHE */
	cp_ctx(ctx, 0x405000, 0x1);
	switch (device->chipset) {
	case 0x50:
		gw_def(ctx, 0x405000, 0x00300080);
		bweak;
	case 0x84:
	case 0xa0:
	case 0xa3:
	case 0xa5:
	case 0xa8:
	case 0xaa:
	case 0xac:
	case 0xaf:
		gw_def(ctx, 0x405000, 0x000e0080);
		bweak;
	case 0x86:
	case 0x92:
	case 0x94:
	case 0x96:
	case 0x98:
		gw_def(ctx, 0x405000, 0x00000080);
		bweak;
	}
	cp_ctx(ctx, 0x405014, 0x1);
	gw_def(ctx, 0x405014, 0x00000004);
	cp_ctx(ctx, 0x40501c, 0x1);
	cp_ctx(ctx, 0x405024, 0x1);
	cp_ctx(ctx, 0x40502c, 0x1);

	/* 6000? */
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x4063e0, 0x1);

	/* 6800: M2MF */
	if (device->chipset < 0x90) {
		cp_ctx(ctx, 0x406814, 0x2b);
		gw_def(ctx, 0x406818, 0x00000f80);
		gw_def(ctx, 0x406860, 0x007f0080);
		gw_def(ctx, 0x40689c, 0x007f0080);
	} ewse {
		cp_ctx(ctx, 0x406814, 0x4);
		if (device->chipset == 0x98)
			gw_def(ctx, 0x406818, 0x00000f80);
		ewse
			gw_def(ctx, 0x406818, 0x00001f80);
		if (IS_NVA3F(device->chipset))
			gw_def(ctx, 0x40681c, 0x00000030);
		cp_ctx(ctx, 0x406830, 0x3);
	}

	/* 7000: pew-WOP gwoup state */
	fow (i = 0; i < 8; i++) {
		if (units & (1<<(i+16))) {
			cp_ctx(ctx, 0x407000 + (i<<8), 3);
			if (device->chipset == 0x50)
				gw_def(ctx, 0x407000 + (i<<8), 0x1b74f820);
			ewse if (device->chipset != 0xa5)
				gw_def(ctx, 0x407000 + (i<<8), 0x3b74f821);
			ewse
				gw_def(ctx, 0x407000 + (i<<8), 0x7b74f821);
			gw_def(ctx, 0x407004 + (i<<8), 0x89058001);

			if (device->chipset == 0x50) {
				cp_ctx(ctx, 0x407010 + (i<<8), 1);
			} ewse if (device->chipset < 0xa0) {
				cp_ctx(ctx, 0x407010 + (i<<8), 2);
				gw_def(ctx, 0x407010 + (i<<8), 0x00001000);
				gw_def(ctx, 0x407014 + (i<<8), 0x0000001f);
			} ewse {
				cp_ctx(ctx, 0x407010 + (i<<8), 3);
				gw_def(ctx, 0x407010 + (i<<8), 0x00001000);
				if (device->chipset != 0xa5)
					gw_def(ctx, 0x407014 + (i<<8), 0x000000ff);
				ewse
					gw_def(ctx, 0x407014 + (i<<8), 0x000001ff);
			}

			cp_ctx(ctx, 0x407080 + (i<<8), 4);
			if (device->chipset != 0xa5)
				gw_def(ctx, 0x407080 + (i<<8), 0x027c10fa);
			ewse
				gw_def(ctx, 0x407080 + (i<<8), 0x827c10fa);
			if (device->chipset == 0x50)
				gw_def(ctx, 0x407084 + (i<<8), 0x000000c0);
			ewse
				gw_def(ctx, 0x407084 + (i<<8), 0x400000c0);
			gw_def(ctx, 0x407088 + (i<<8), 0xb7892080);

			if (device->chipset < 0xa0)
				cp_ctx(ctx, 0x407094 + (i<<8), 1);
			ewse if (!IS_NVA3F(device->chipset))
				cp_ctx(ctx, 0x407094 + (i<<8), 3);
			ewse {
				cp_ctx(ctx, 0x407094 + (i<<8), 4);
				gw_def(ctx, 0x4070a0 + (i<<8), 1);
			}
		}
	}

	cp_ctx(ctx, 0x407c00, 0x3);
	if (device->chipset < 0x90)
		gw_def(ctx, 0x407c00, 0x00010040);
	ewse if (device->chipset < 0xa0)
		gw_def(ctx, 0x407c00, 0x00390040);
	ewse
		gw_def(ctx, 0x407c00, 0x003d0040);
	gw_def(ctx, 0x407c08, 0x00000022);
	if (device->chipset >= 0xa0) {
		cp_ctx(ctx, 0x407c10, 0x3);
		cp_ctx(ctx, 0x407c20, 0x1);
		cp_ctx(ctx, 0x407c2c, 0x1);
	}

	if (device->chipset < 0xa0) {
		cp_ctx(ctx, 0x407d00, 0x9);
	} ewse {
		cp_ctx(ctx, 0x407d00, 0x15);
	}
	if (device->chipset == 0x98)
		gw_def(ctx, 0x407d08, 0x00380040);
	ewse {
		if (device->chipset < 0x90)
			gw_def(ctx, 0x407d08, 0x00010040);
		ewse if (device->chipset < 0xa0)
			gw_def(ctx, 0x407d08, 0x00390040);
		ewse {
			if (device->fb->wam->type != NVKM_WAM_TYPE_GDDW5)
				gw_def(ctx, 0x407d08, 0x003d0040);
			ewse
				gw_def(ctx, 0x407d08, 0x003c0040);
		}
		gw_def(ctx, 0x407d0c, 0x00000022);
	}

	/* 8000+: pew-TP state */
	fow (i = 0; i < 10; i++) {
		if (units & (1<<i)) {
			if (device->chipset < 0xa0)
				base = 0x408000 + (i<<12);
			ewse
				base = 0x408000 + (i<<11);
			if (device->chipset < 0xa0)
				offset = base + 0xc00;
			ewse
				offset = base + 0x80;
			cp_ctx(ctx, offset + 0x00, 1);
			gw_def(ctx, offset + 0x00, 0x0000ff0a);
			cp_ctx(ctx, offset + 0x08, 1);

			/* pew-MP state */
			fow (j = 0; j < (device->chipset < 0xa0 ? 2 : 4); j++) {
				if (!(units & (1 << (j+24)))) continue;
				if (device->chipset < 0xa0)
					offset = base + 0x200 + (j<<7);
				ewse
					offset = base + 0x100 + (j<<7);
				cp_ctx(ctx, offset, 0x20);
				gw_def(ctx, offset + 0x00, 0x01800000);
				gw_def(ctx, offset + 0x04, 0x00160000);
				gw_def(ctx, offset + 0x08, 0x01800000);
				gw_def(ctx, offset + 0x18, 0x0003ffff);
				switch (device->chipset) {
				case 0x50:
					gw_def(ctx, offset + 0x1c, 0x00080000);
					bweak;
				case 0x84:
					gw_def(ctx, offset + 0x1c, 0x00880000);
					bweak;
				case 0x86:
					gw_def(ctx, offset + 0x1c, 0x018c0000);
					bweak;
				case 0x92:
				case 0x96:
				case 0x98:
					gw_def(ctx, offset + 0x1c, 0x118c0000);
					bweak;
				case 0x94:
					gw_def(ctx, offset + 0x1c, 0x10880000);
					bweak;
				case 0xa0:
				case 0xa5:
					gw_def(ctx, offset + 0x1c, 0x310c0000);
					bweak;
				case 0xa3:
				case 0xa8:
				case 0xaa:
				case 0xac:
				case 0xaf:
					gw_def(ctx, offset + 0x1c, 0x300c0000);
					bweak;
				}
				gw_def(ctx, offset + 0x40, 0x00010401);
				if (device->chipset == 0x50)
					gw_def(ctx, offset + 0x48, 0x00000040);
				ewse
					gw_def(ctx, offset + 0x48, 0x00000078);
				gw_def(ctx, offset + 0x50, 0x000000bf);
				gw_def(ctx, offset + 0x58, 0x00001210);
				if (device->chipset == 0x50)
					gw_def(ctx, offset + 0x5c, 0x00000080);
				ewse
					gw_def(ctx, offset + 0x5c, 0x08000080);
				if (device->chipset >= 0xa0)
					gw_def(ctx, offset + 0x68, 0x0000003e);
			}

			if (device->chipset < 0xa0)
				cp_ctx(ctx, base + 0x300, 0x4);
			ewse
				cp_ctx(ctx, base + 0x300, 0x5);
			if (device->chipset == 0x50)
				gw_def(ctx, base + 0x304, 0x00007070);
			ewse if (device->chipset < 0xa0)
				gw_def(ctx, base + 0x304, 0x00027070);
			ewse if (!IS_NVA3F(device->chipset))
				gw_def(ctx, base + 0x304, 0x01127070);
			ewse
				gw_def(ctx, base + 0x304, 0x05127070);

			if (device->chipset < 0xa0)
				cp_ctx(ctx, base + 0x318, 1);
			ewse
				cp_ctx(ctx, base + 0x320, 1);
			if (device->chipset == 0x50)
				gw_def(ctx, base + 0x318, 0x0003ffff);
			ewse if (device->chipset < 0xa0)
				gw_def(ctx, base + 0x318, 0x03ffffff);
			ewse
				gw_def(ctx, base + 0x320, 0x07ffffff);

			if (device->chipset < 0xa0)
				cp_ctx(ctx, base + 0x324, 5);
			ewse
				cp_ctx(ctx, base + 0x328, 4);

			if (device->chipset < 0xa0) {
				cp_ctx(ctx, base + 0x340, 9);
				offset = base + 0x340;
			} ewse if (!IS_NVA3F(device->chipset)) {
				cp_ctx(ctx, base + 0x33c, 0xb);
				offset = base + 0x344;
			} ewse {
				cp_ctx(ctx, base + 0x33c, 0xd);
				offset = base + 0x344;
			}
			gw_def(ctx, offset + 0x0, 0x00120407);
			gw_def(ctx, offset + 0x4, 0x05091507);
			if (device->chipset == 0x84)
				gw_def(ctx, offset + 0x8, 0x05100202);
			ewse
				gw_def(ctx, offset + 0x8, 0x05010202);
			gw_def(ctx, offset + 0xc, 0x00030201);
			if (device->chipset == 0xa3)
				cp_ctx(ctx, base + 0x36c, 1);

			cp_ctx(ctx, base + 0x400, 2);
			gw_def(ctx, base + 0x404, 0x00000040);
			cp_ctx(ctx, base + 0x40c, 2);
			gw_def(ctx, base + 0x40c, 0x0d0c0b0a);
			gw_def(ctx, base + 0x410, 0x00141210);

			if (device->chipset < 0xa0)
				offset = base + 0x800;
			ewse
				offset = base + 0x500;
			cp_ctx(ctx, offset, 6);
			gw_def(ctx, offset + 0x0, 0x000001f0);
			gw_def(ctx, offset + 0x4, 0x00000001);
			gw_def(ctx, offset + 0x8, 0x00000003);
			if (device->chipset == 0x50 || IS_NVAAF(device->chipset))
				gw_def(ctx, offset + 0xc, 0x00008000);
			gw_def(ctx, offset + 0x14, 0x00039e00);
			cp_ctx(ctx, offset + 0x1c, 2);
			if (device->chipset == 0x50)
				gw_def(ctx, offset + 0x1c, 0x00000040);
			ewse
				gw_def(ctx, offset + 0x1c, 0x00000100);
			gw_def(ctx, offset + 0x20, 0x00003800);

			if (device->chipset >= 0xa0) {
				cp_ctx(ctx, base + 0x54c, 2);
				if (!IS_NVA3F(device->chipset))
					gw_def(ctx, base + 0x54c, 0x003fe006);
				ewse
					gw_def(ctx, base + 0x54c, 0x003fe007);
				gw_def(ctx, base + 0x550, 0x003fe000);
			}

			if (device->chipset < 0xa0)
				offset = base + 0xa00;
			ewse
				offset = base + 0x680;
			cp_ctx(ctx, offset, 1);
			gw_def(ctx, offset, 0x00404040);

			if (device->chipset < 0xa0)
				offset = base + 0xe00;
			ewse
				offset = base + 0x700;
			cp_ctx(ctx, offset, 2);
			if (device->chipset < 0xa0)
				gw_def(ctx, offset, 0x0077f005);
			ewse if (device->chipset == 0xa5)
				gw_def(ctx, offset, 0x6cf7f007);
			ewse if (device->chipset == 0xa8)
				gw_def(ctx, offset, 0x6cfff007);
			ewse if (device->chipset == 0xac)
				gw_def(ctx, offset, 0x0cfff007);
			ewse
				gw_def(ctx, offset, 0x0cf7f007);
			if (device->chipset == 0x50)
				gw_def(ctx, offset + 0x4, 0x00007fff);
			ewse if (device->chipset < 0xa0)
				gw_def(ctx, offset + 0x4, 0x003f7fff);
			ewse
				gw_def(ctx, offset + 0x4, 0x02bf7fff);
			cp_ctx(ctx, offset + 0x2c, 1);
			if (device->chipset == 0x50) {
				cp_ctx(ctx, offset + 0x50, 9);
				gw_def(ctx, offset + 0x54, 0x000003ff);
				gw_def(ctx, offset + 0x58, 0x00000003);
				gw_def(ctx, offset + 0x5c, 0x00000003);
				gw_def(ctx, offset + 0x60, 0x000001ff);
				gw_def(ctx, offset + 0x64, 0x0000001f);
				gw_def(ctx, offset + 0x68, 0x0000000f);
				gw_def(ctx, offset + 0x6c, 0x0000000f);
			} ewse if (device->chipset < 0xa0) {
				cp_ctx(ctx, offset + 0x50, 1);
				cp_ctx(ctx, offset + 0x70, 1);
			} ewse {
				cp_ctx(ctx, offset + 0x50, 1);
				cp_ctx(ctx, offset + 0x60, 5);
			}
		}
	}
}

static void
dd_emit(stwuct nvkm_gwctx *ctx, int num, u32 vaw) {
	int i;
	if (vaw && ctx->mode == NVKM_GWCTX_VAWS) {
		fow (i = 0; i < num; i++)
			nvkm_wo32(ctx->data, 4 * (ctx->ctxvaws_pos + i), vaw);
	}
	ctx->ctxvaws_pos += num;
}

static void
nv50_gw_constwuct_mmio_ddata(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int base, num;
	base = ctx->ctxvaws_pos;

	/* teswa state */
	dd_emit(ctx, 1, 0);	/* 00000001 UNK0F90 */
	dd_emit(ctx, 1, 0);	/* 00000001 UNK135C */

	/* SWC_TIC state */
	dd_emit(ctx, 1, 0);	/* 00000007 SWC_TIWE_MODE_Z */
	dd_emit(ctx, 1, 2);	/* 00000007 SWC_TIWE_MODE_Y */
	dd_emit(ctx, 1, 1);	/* 00000001 SWC_WINEAW #1 */
	dd_emit(ctx, 1, 0);	/* 000000ff SWC_ADDWESS_HIGH */
	dd_emit(ctx, 1, 0);	/* 00000001 SWC_SWGB */
	if (device->chipset >= 0x94)
		dd_emit(ctx, 1, 0);	/* 00000003 eng2d UNK0258 */
	dd_emit(ctx, 1, 1);	/* 00000fff SWC_DEPTH */
	dd_emit(ctx, 1, 0x100);	/* 0000ffff SWC_HEIGHT */

	/* tuwing state */
	dd_emit(ctx, 1, 0);		/* 0000000f TEXTUWES_WOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f SAMPWEWS_WOG2 */
	dd_emit(ctx, 1, 0);		/* 000000ff CB_DEF_ADDWESS_HIGH */
	dd_emit(ctx, 1, 0);		/* ffffffff CB_DEF_ADDWESS_WOW */
	dd_emit(ctx, 1, 0);		/* ffffffff SHAWED_SIZE */
	dd_emit(ctx, 1, 2);		/* ffffffff WEG_MODE */
	dd_emit(ctx, 1, 1);		/* 0000ffff BWOCK_AWWOC_THWEADS */
	dd_emit(ctx, 1, 1);		/* 00000001 WANES32 */
	dd_emit(ctx, 1, 0);		/* 000000ff UNK370 */
	dd_emit(ctx, 1, 0);		/* 000000ff USEW_PAWAM_UNK */
	dd_emit(ctx, 1, 0);		/* 000000ff USEW_PAWAM_COUNT */
	dd_emit(ctx, 1, 1);		/* 000000ff UNK384 bits 8-15 */
	dd_emit(ctx, 1, 0x3fffff);	/* 003fffff TIC_WIMIT */
	dd_emit(ctx, 1, 0x1fff);	/* 000fffff TSC_WIMIT */
	dd_emit(ctx, 1, 0);		/* 0000ffff CB_ADDW_INDEX */
	dd_emit(ctx, 1, 1);		/* 000007ff BWOCKDIM_X */
	dd_emit(ctx, 1, 1);		/* 000007ff BWOCKDIM_XMY */
	dd_emit(ctx, 1, 0);		/* 00000001 BWOCKDIM_XMY_OVEWFWOW */
	dd_emit(ctx, 1, 1);		/* 0003ffff BWOCKDIM_XMYMZ */
	dd_emit(ctx, 1, 1);		/* 000007ff BWOCKDIM_Y */
	dd_emit(ctx, 1, 1);		/* 0000007f BWOCKDIM_Z */
	dd_emit(ctx, 1, 4);		/* 000000ff CP_WEG_AWWOC_TEMP */
	dd_emit(ctx, 1, 1);		/* 00000001 BWOCKDIM_DIWTY */
	if (IS_NVA3F(device->chipset))
		dd_emit(ctx, 1, 0);	/* 00000003 UNK03E8 */
	dd_emit(ctx, 1, 1);		/* 0000007f BWOCK_AWWOC_HAWFWAWPS */
	dd_emit(ctx, 1, 1);		/* 00000007 WOCAW_WAWPS_NO_CWAMP */
	dd_emit(ctx, 1, 7);		/* 00000007 WOCAW_WAWPS_WOG_AWWOC */
	dd_emit(ctx, 1, 1);		/* 00000007 STACK_WAWPS_NO_CWAMP */
	dd_emit(ctx, 1, 7);		/* 00000007 STACK_WAWPS_WOG_AWWOC */
	dd_emit(ctx, 1, 1);		/* 00001fff BWOCK_AWWOC_WEGSWOTS_PACKED */
	dd_emit(ctx, 1, 1);		/* 00001fff BWOCK_AWWOC_WEGSWOTS_STWIDED */
	dd_emit(ctx, 1, 1);		/* 000007ff BWOCK_AWWOC_THWEADS */

	/* compat 2d state */
	if (device->chipset == 0x50) {
		dd_emit(ctx, 4, 0);		/* 0000ffff cwip X, Y, W, H */

		dd_emit(ctx, 1, 1);		/* ffffffff chwoma COWOW_FOWMAT */

		dd_emit(ctx, 1, 1);		/* ffffffff pattewn COWOW_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff pattewn SHAPE */
		dd_emit(ctx, 1, 1);		/* ffffffff pattewn PATTEWN_SEWECT */

		dd_emit(ctx, 1, 0xa);		/* ffffffff suwf2d SWC_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff suwf2d DMA_SWC */
		dd_emit(ctx, 1, 0);		/* 000000ff suwf2d SWC_ADDWESS_HIGH */
		dd_emit(ctx, 1, 0);		/* ffffffff suwf2d SWC_ADDWESS_WOW */
		dd_emit(ctx, 1, 0x40);		/* 0000ffff suwf2d SWC_PITCH */
		dd_emit(ctx, 1, 0);		/* 0000000f suwf2d SWC_TIWE_MODE_Z */
		dd_emit(ctx, 1, 2);		/* 0000000f suwf2d SWC_TIWE_MODE_Y */
		dd_emit(ctx, 1, 0x100);		/* ffffffff suwf2d SWC_HEIGHT */
		dd_emit(ctx, 1, 1);		/* 00000001 suwf2d SWC_WINEAW */
		dd_emit(ctx, 1, 0x100);		/* ffffffff suwf2d SWC_WIDTH */

		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect CWIP_B_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect CWIP_B_Y */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect CWIP_C_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect CWIP_C_Y */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect CWIP_D_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect CWIP_D_Y */
		dd_emit(ctx, 1, 1);		/* ffffffff gdiwect COWOW_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff gdiwect OPEWATION */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect POINT_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdiwect POINT_Y */

		dd_emit(ctx, 1, 0);		/* 0000ffff bwit SWC_Y */
		dd_emit(ctx, 1, 0);		/* ffffffff bwit OPEWATION */

		dd_emit(ctx, 1, 0);		/* ffffffff ifc OPEWATION */

		dd_emit(ctx, 1, 0);		/* ffffffff iifc INDEX_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff iifc WUT_OFFSET */
		dd_emit(ctx, 1, 4);		/* ffffffff iifc COWOW_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff iifc OPEWATION */
	}

	/* m2mf state */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf WINE_COUNT */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf WINE_WENGTH_IN */
	dd_emit(ctx, 2, 0);		/* ffffffff m2mf OFFSET_IN, OFFSET_OUT */
	dd_emit(ctx, 1, 1);		/* ffffffff m2mf TIWING_DEPTH_OUT */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TIWING_HEIGHT_OUT */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf TIWING_POSITION_OUT_Z */
	dd_emit(ctx, 1, 1);		/* 00000001 m2mf WINEAW_OUT */
	dd_emit(ctx, 2, 0);		/* 0000ffff m2mf TIWING_POSITION_OUT_X, Y */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TIWING_PITCH_OUT */
	dd_emit(ctx, 1, 1);		/* ffffffff m2mf TIWING_DEPTH_IN */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TIWING_HEIGHT_IN */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf TIWING_POSITION_IN_Z */
	dd_emit(ctx, 1, 1);		/* 00000001 m2mf WINEAW_IN */
	dd_emit(ctx, 2, 0);		/* 0000ffff m2mf TIWING_POSITION_IN_X, Y */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TIWING_PITCH_IN */

	/* mowe compat 2d state */
	if (device->chipset == 0x50) {
		dd_emit(ctx, 1, 1);		/* ffffffff wine COWOW_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff wine OPEWATION */

		dd_emit(ctx, 1, 1);		/* ffffffff twiangwe COWOW_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff twiangwe OPEWATION */

		dd_emit(ctx, 1, 0);		/* 0000000f sifm TIWE_MODE_Z */
		dd_emit(ctx, 1, 2);		/* 0000000f sifm TIWE_MODE_Y */
		dd_emit(ctx, 1, 0);		/* 000000ff sifm FOWMAT_FIWTEW */
		dd_emit(ctx, 1, 1);		/* 000000ff sifm FOWMAT_OWIGIN */
		dd_emit(ctx, 1, 0);		/* 0000ffff sifm SWC_PITCH */
		dd_emit(ctx, 1, 1);		/* 00000001 sifm SWC_WINEAW */
		dd_emit(ctx, 1, 0);		/* 000000ff sifm SWC_OFFSET_HIGH */
		dd_emit(ctx, 1, 0);		/* ffffffff sifm SWC_OFFSET */
		dd_emit(ctx, 1, 0);		/* 0000ffff sifm SWC_HEIGHT */
		dd_emit(ctx, 1, 0);		/* 0000ffff sifm SWC_WIDTH */
		dd_emit(ctx, 1, 3);		/* ffffffff sifm COWOW_FOWMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff sifm OPEWATION */

		dd_emit(ctx, 1, 0);		/* ffffffff sifc OPEWATION */
	}

	/* teswa state */
	dd_emit(ctx, 1, 0);		/* 0000000f GP_TEXTUWES_WOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f GP_SAMPWEWS_WOG2 */
	dd_emit(ctx, 1, 0);		/* 000000ff */
	dd_emit(ctx, 1, 0);		/* ffffffff */
	dd_emit(ctx, 1, 4);		/* 000000ff UNK12B0_0 */
	dd_emit(ctx, 1, 0x70);		/* 000000ff UNK12B0_1 */
	dd_emit(ctx, 1, 0x80);		/* 000000ff UNK12B0_3 */
	dd_emit(ctx, 1, 0);		/* 000000ff UNK12B0_2 */
	dd_emit(ctx, 1, 0);		/* 0000000f FP_TEXTUWES_WOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f FP_SAMPWEWS_WOG2 */
	if (IS_NVA3F(device->chipset)) {
		dd_emit(ctx, 1, 0);	/* ffffffff */
		dd_emit(ctx, 1, 0);	/* 0000007f MUWTISAMPWE_SAMPWES_WOG2 */
	} ewse {
		dd_emit(ctx, 1, 0);	/* 0000000f MUWTISAMPWE_SAMPWES_WOG2 */
	}
	dd_emit(ctx, 1, 0xc);		/* 000000ff SEMANTIC_COWOW.BFC0_ID */
	if (device->chipset != 0x50)
		dd_emit(ctx, 1, 0);	/* 00000001 SEMANTIC_COWOW.CWMP_EN */
	dd_emit(ctx, 1, 8);		/* 000000ff SEMANTIC_COWOW.COWW_NW */
	dd_emit(ctx, 1, 0x14);		/* 000000ff SEMANTIC_COWOW.FFC0_ID */
	if (device->chipset == 0x50) {
		dd_emit(ctx, 1, 0);	/* 000000ff SEMANTIC_WAYEW */
		dd_emit(ctx, 1, 0);	/* 00000001 */
	} ewse {
		dd_emit(ctx, 1, 0);	/* 00000001 SEMANTIC_PTSZ.ENABWE */
		dd_emit(ctx, 1, 0x29);	/* 000000ff SEMANTIC_PTSZ.PTSZ_ID */
		dd_emit(ctx, 1, 0x27);	/* 000000ff SEMANTIC_PWIM */
		dd_emit(ctx, 1, 0x26);	/* 000000ff SEMANTIC_WAYEW */
		dd_emit(ctx, 1, 8);	/* 0000000f SMENATIC_CWIP.CWIP_HIGH */
		dd_emit(ctx, 1, 4);	/* 000000ff SEMANTIC_CWIP.CWIP_WO */
		dd_emit(ctx, 1, 0x27);	/* 000000ff UNK0FD4 */
		dd_emit(ctx, 1, 0);	/* 00000001 UNK1900 */
	}
	dd_emit(ctx, 1, 0);		/* 00000007 WT_CONTWOW_MAP0 */
	dd_emit(ctx, 1, 1);		/* 00000007 WT_CONTWOW_MAP1 */
	dd_emit(ctx, 1, 2);		/* 00000007 WT_CONTWOW_MAP2 */
	dd_emit(ctx, 1, 3);		/* 00000007 WT_CONTWOW_MAP3 */
	dd_emit(ctx, 1, 4);		/* 00000007 WT_CONTWOW_MAP4 */
	dd_emit(ctx, 1, 5);		/* 00000007 WT_CONTWOW_MAP5 */
	dd_emit(ctx, 1, 6);		/* 00000007 WT_CONTWOW_MAP6 */
	dd_emit(ctx, 1, 7);		/* 00000007 WT_CONTWOW_MAP7 */
	dd_emit(ctx, 1, 1);		/* 0000000f WT_CONTWOW_COUNT */
	dd_emit(ctx, 8, 0);		/* 00000001 WT_HOWIZ_UNK */
	dd_emit(ctx, 8, 0);		/* ffffffff WT_ADDWESS_WOW */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff WT_FOWMAT */
	dd_emit(ctx, 7, 0);		/* 000000ff WT_FOWMAT */
	if (device->chipset != 0x50)
		dd_emit(ctx, 3, 0);	/* 1, 1, 1 */
	ewse
		dd_emit(ctx, 2, 0);	/* 1, 1 */
	dd_emit(ctx, 1, 0);		/* ffffffff GP_ENABWE */
	dd_emit(ctx, 1, 0x80);		/* 0000ffff GP_VEWTEX_OUTPUT_COUNT*/
	dd_emit(ctx, 1, 4);		/* 000000ff GP_WEG_AWWOC_WESUWT */
	dd_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	if (IS_NVA3F(device->chipset)) {
		dd_emit(ctx, 1, 3);	/* 00000003 */
		dd_emit(ctx, 1, 0);	/* 00000001 UNK1418. Awone. */
	}
	if (device->chipset != 0x50)
		dd_emit(ctx, 1, 3);	/* 00000003 UNK15AC */
	dd_emit(ctx, 1, 1);		/* ffffffff WASTEWIZE_ENABWE */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_CONTWOW.EXPOWTS_Z */
	if (device->chipset != 0x50)
		dd_emit(ctx, 1, 0);	/* 00000001 FP_CONTWOW.MUWTIPWE_WESUWTS */
	dd_emit(ctx, 1, 0x12);		/* 000000ff FP_INTEWPOWANT_CTWW.COUNT */
	dd_emit(ctx, 1, 0x10);		/* 000000ff FP_INTEWPOWANT_CTWW.COUNT_NONFWAT */
	dd_emit(ctx, 1, 0xc);		/* 000000ff FP_INTEWPOWANT_CTWW.OFFSET */
	dd_emit(ctx, 1, 1);		/* 00000001 FP_INTEWPOWANT_CTWW.UMASK.W */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_INTEWPOWANT_CTWW.UMASK.X */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_INTEWPOWANT_CTWW.UMASK.Y */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_INTEWPOWANT_CTWW.UMASK.Z */
	dd_emit(ctx, 1, 4);		/* 000000ff FP_WESUWT_COUNT */
	dd_emit(ctx, 1, 2);		/* ffffffff WEG_MODE */
	dd_emit(ctx, 1, 4);		/* 000000ff FP_WEG_AWWOC_TEMP */
	if (device->chipset >= 0xa0)
		dd_emit(ctx, 1, 0);	/* ffffffff */
	dd_emit(ctx, 1, 0);		/* 00000001 GP_BUIWTIN_WESUWT_EN.WAYEW_IDX */
	dd_emit(ctx, 1, 0);		/* ffffffff STWMOUT_ENABWE */
	dd_emit(ctx, 1, 0x3fffff);	/* 003fffff TIC_WIMIT */
	dd_emit(ctx, 1, 0x1fff);	/* 000fffff TSC_WIMIT */
	dd_emit(ctx, 1, 0);		/* 00000001 VEWTEX_TWO_SIDE_ENABWE*/
	if (device->chipset != 0x50)
		dd_emit(ctx, 8, 0);	/* 00000001 */
	if (device->chipset >= 0xa0) {
		dd_emit(ctx, 1, 1);	/* 00000007 VTX_ATTW_DEFINE.COMP */
		dd_emit(ctx, 1, 1);	/* 00000007 VTX_ATTW_DEFINE.SIZE */
		dd_emit(ctx, 1, 2);	/* 00000007 VTX_ATTW_DEFINE.TYPE */
		dd_emit(ctx, 1, 0);	/* 000000ff VTX_ATTW_DEFINE.ATTW */
	}
	dd_emit(ctx, 1, 4);		/* 0000007f VP_WESUWT_MAP_SIZE */
	dd_emit(ctx, 1, 0x14);		/* 0000001f ZETA_FOWMAT */
	dd_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	dd_emit(ctx, 1, 0);		/* 0000000f VP_TEXTUWES_WOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f VP_SAMPWEWS_WOG2 */
	if (IS_NVA3F(device->chipset))
		dd_emit(ctx, 1, 0);	/* 00000001 */
	dd_emit(ctx, 1, 2);		/* 00000003 POWYGON_MODE_BACK */
	if (device->chipset >= 0xa0)
		dd_emit(ctx, 1, 0);	/* 00000003 VTX_ATTW_DEFINE.SIZE - 1 */
	dd_emit(ctx, 1, 0);		/* 0000ffff CB_ADDW_INDEX */
	if (device->chipset >= 0xa0)
		dd_emit(ctx, 1, 0);	/* 00000003 */
	dd_emit(ctx, 1, 0);		/* 00000001 CUWW_FACE_ENABWE */
	dd_emit(ctx, 1, 1);		/* 00000003 CUWW_FACE */
	dd_emit(ctx, 1, 0);		/* 00000001 FWONT_FACE */
	dd_emit(ctx, 1, 2);		/* 00000003 POWYGON_MODE_FWONT */
	dd_emit(ctx, 1, 0x1000);	/* 00007fff UNK141C */
	if (device->chipset != 0x50) {
		dd_emit(ctx, 1, 0xe00);		/* 7fff */
		dd_emit(ctx, 1, 0x1000);	/* 7fff */
		dd_emit(ctx, 1, 0x1e00);	/* 7fff */
	}
	dd_emit(ctx, 1, 0);		/* 00000001 BEGIN_END_ACTIVE */
	dd_emit(ctx, 1, 1);		/* 00000001 POWYGON_MODE_??? */
	dd_emit(ctx, 1, 1);		/* 000000ff GP_WEG_AWWOC_TEMP / 4 wounded up */
	dd_emit(ctx, 1, 1);		/* 000000ff FP_WEG_AWWOC_TEMP... without /4? */
	dd_emit(ctx, 1, 1);		/* 000000ff VP_WEG_AWWOC_TEMP / 4 wounded up */
	dd_emit(ctx, 1, 1);		/* 00000001 */
	dd_emit(ctx, 1, 0);		/* 00000001 */
	dd_emit(ctx, 1, 0);		/* 00000001 VTX_ATTW_MASK_UNK0 nonempty */
	dd_emit(ctx, 1, 0);		/* 00000001 VTX_ATTW_MASK_UNK1 nonempty */
	dd_emit(ctx, 1, 0x200);		/* 0003ffff GP_VEWTEX_OUTPUT_COUNT*GP_WEG_AWWOC_WESUWT */
	if (IS_NVA3F(device->chipset))
		dd_emit(ctx, 1, 0x200);
	dd_emit(ctx, 1, 0);		/* 00000001 */
	if (device->chipset < 0xa0) {
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0x70);	/* 000000ff */
		dd_emit(ctx, 1, 0x80);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 00000001 */
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0x70);	/* 000000ff */
		dd_emit(ctx, 1, 0x80);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
	} ewse {
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0xf0);	/* 000000ff */
		dd_emit(ctx, 1, 0xff);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 00000001 */
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0xf0);	/* 000000ff */
		dd_emit(ctx, 1, 0xff);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
		dd_emit(ctx, 1, 9);	/* 0000003f UNK114C.COMP,SIZE */
	}

	/* eng2d state */
	dd_emit(ctx, 1, 0);		/* 00000001 eng2d COWOW_KEY_ENABWE */
	dd_emit(ctx, 1, 0);		/* 00000007 eng2d COWOW_KEY_FOWMAT */
	dd_emit(ctx, 1, 1);		/* ffffffff eng2d DST_DEPTH */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d DST_FOWMAT */
	dd_emit(ctx, 1, 0);		/* ffffffff eng2d DST_WAYEW */
	dd_emit(ctx, 1, 1);		/* 00000001 eng2d DST_WINEAW */
	dd_emit(ctx, 1, 0);		/* 00000007 eng2d PATTEWN_COWOW_FOWMAT */
	dd_emit(ctx, 1, 0);		/* 00000007 eng2d OPEWATION */
	dd_emit(ctx, 1, 0);		/* 00000003 eng2d PATTEWN_SEWECT */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d SIFC_FOWMAT */
	dd_emit(ctx, 1, 0);		/* 00000001 eng2d SIFC_BITMAP_ENABWE */
	dd_emit(ctx, 1, 2);		/* 00000003 eng2d SIFC_BITMAP_UNK808 */
	dd_emit(ctx, 1, 0);		/* ffffffff eng2d BWIT_DU_DX_FWACT */
	dd_emit(ctx, 1, 1);		/* ffffffff eng2d BWIT_DU_DX_INT */
	dd_emit(ctx, 1, 0);		/* ffffffff eng2d BWIT_DV_DY_FWACT */
	dd_emit(ctx, 1, 1);		/* ffffffff eng2d BWIT_DV_DY_INT */
	dd_emit(ctx, 1, 0);		/* 00000001 eng2d BWIT_CONTWOW_FIWTEW */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d DWAW_COWOW_FOWMAT */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d SWC_FOWMAT */
	dd_emit(ctx, 1, 1);		/* 00000001 eng2d SWC_WINEAW #2 */

	num = ctx->ctxvaws_pos - base;
	ctx->ctxvaws_pos = base;
	if (IS_NVA3F(device->chipset))
		cp_ctx(ctx, 0x404800, num);
	ewse
		cp_ctx(ctx, 0x405400, num);
}

/*
 * xfew aweas. These awe a pain.
 *
 * Thewe awe 2 xfew aweas: the fiwst one is big and contains aww sowts of
 * stuff, the second is smaww and contains some pew-TP context.
 *
 * Each awea is spwit into 8 "stwands". The aweas, when saved to gwctx,
 * awe made of 8-wowd bwocks. Each bwock contains a singwe wowd fwom
 * each stwand. The stwands awe independent of each othew, theiw
 * addwesses awe unwewated to each othew, and data in them is cwosewy
 * packed togethew. The stwand wayout vawies a bit between cawds: hewe
 * and thewe, a singwe wowd is thwown out in the middwe and the whowe
 * stwand is offset by a bit fwom cowwesponding one on anothew chipset.
 * Fow this weason, addwesses of stuff in stwands awe awmost usewess.
 * Knowing sequence of stuff and size of gaps between them is much mowe
 * usefuw, and that's how we buiwd the stwands in ouw genewatow.
 *
 * NVA0 takes this mess to a whowe new wevew by cutting the owd stwands
 * into a few dozen pieces [known as genes], weawwanging them wandomwy,
 * and putting them back togethew to make new stwands. Hopefuwwy these
 * genes cowwespond mowe ow wess diwectwy to the same PGWAPH subunits
 * as in 400040 wegistew.
 *
 * The most common vawue in defauwt context is 0, and when the genes
 * awe sepawated by 0's, gene bounduawies awe quite specuwative...
 * some of them can be cweawwy deduced, othews can be guessed, and yet
 * othews won't be wesowved without figuwing out the weaw meaning of
 * given ctxvaw. Fow the same weason, ending point of each stwand
 * is unknown. Except fow stwand 0, which is the wongest stwand and
 * its end cowwesponds to end of the whowe xfew.
 *
 * An unsowved mystewy is the seek instwuction: it takes an awgument
 * in bits 8-18, and that awgument is cweawwy the pwace in stwands to
 * seek to... but the offsets don't seem to cowwespond to offsets as
 * seen in gwctx. Pewhaps thewe's anothew, weaw, not wandomwy-changing
 * addwessing in stwands, and the xfew insn just happens to skip ovew
 * the unused bits? NV10-NV30 PIPE comes to mind...
 *
 * As faw as I know, thewe's no way to access the xfew aweas diwectwy
 * without the hewp of ctxpwog.
 */

static void
xf_emit(stwuct nvkm_gwctx *ctx, int num, u32 vaw) {
	int i;
	if (vaw && ctx->mode == NVKM_GWCTX_VAWS) {
		fow (i = 0; i < num; i++)
			nvkm_wo32(ctx->data, 4 * (ctx->ctxvaws_pos + (i << 3)), vaw);
	}
	ctx->ctxvaws_pos += num << 3;
}

/* Gene decwawations... */

static void nv50_gw_constwuct_gene_dispatch(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_m2mf(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_ccache(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_unk10xx(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_unk14xx(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_zcuww(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_cwipid(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_unk24xx(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_vfetch(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_eng2d(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_csched(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_unk1cxx(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_stwmout(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_unk34xx(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_wopm1(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_wopm2(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_gene_wopc(stwuct nvkm_gwctx *ctx);
static void nv50_gw_constwuct_xfew_tp(stwuct nvkm_gwctx *ctx);

static void
nv50_gw_constwuct_xfew1(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i;
	int offset;
	int size = 0;
	u32 units = nvkm_wd32(device, 0x1540);

	offset = (ctx->ctxvaws_pos+0x3f)&~0x3f;
	ctx->ctxvaws_base = offset;

	if (device->chipset < 0xa0) {
		/* Stwand 0 */
		ctx->ctxvaws_pos = offset;
		nv50_gw_constwuct_gene_dispatch(ctx);
		nv50_gw_constwuct_gene_m2mf(ctx);
		nv50_gw_constwuct_gene_unk24xx(ctx);
		nv50_gw_constwuct_gene_cwipid(ctx);
		nv50_gw_constwuct_gene_zcuww(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 1 */
		ctx->ctxvaws_pos = offset + 0x1;
		nv50_gw_constwuct_gene_vfetch(ctx);
		nv50_gw_constwuct_gene_eng2d(ctx);
		nv50_gw_constwuct_gene_csched(ctx);
		nv50_gw_constwuct_gene_wopm1(ctx);
		nv50_gw_constwuct_gene_wopm2(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 2 */
		ctx->ctxvaws_pos = offset + 0x2;
		nv50_gw_constwuct_gene_ccache(ctx);
		nv50_gw_constwuct_gene_unk1cxx(ctx);
		nv50_gw_constwuct_gene_stwmout(ctx);
		nv50_gw_constwuct_gene_unk14xx(ctx);
		nv50_gw_constwuct_gene_unk10xx(ctx);
		nv50_gw_constwuct_gene_unk34xx(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 3: pew-WOP gwoup state */
		ctx->ctxvaws_pos = offset + 3;
		fow (i = 0; i < 6; i++)
			if (units & (1 << (i + 16)))
				nv50_gw_constwuct_gene_wopc(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwands 4-7: pew-TP state */
		fow (i = 0; i < 4; i++) {
			ctx->ctxvaws_pos = offset + 4 + i;
			if (units & (1 << (2 * i)))
				nv50_gw_constwuct_xfew_tp(ctx);
			if (units & (1 << (2 * i + 1)))
				nv50_gw_constwuct_xfew_tp(ctx);
			if ((ctx->ctxvaws_pos-offset)/8 > size)
				size = (ctx->ctxvaws_pos-offset)/8;
		}
	} ewse {
		/* Stwand 0 */
		ctx->ctxvaws_pos = offset;
		nv50_gw_constwuct_gene_dispatch(ctx);
		nv50_gw_constwuct_gene_m2mf(ctx);
		nv50_gw_constwuct_gene_unk34xx(ctx);
		nv50_gw_constwuct_gene_csched(ctx);
		nv50_gw_constwuct_gene_unk1cxx(ctx);
		nv50_gw_constwuct_gene_stwmout(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 1 */
		ctx->ctxvaws_pos = offset + 1;
		nv50_gw_constwuct_gene_unk10xx(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 2 */
		ctx->ctxvaws_pos = offset + 2;
		if (device->chipset == 0xa0)
			nv50_gw_constwuct_gene_unk14xx(ctx);
		nv50_gw_constwuct_gene_unk24xx(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 3 */
		ctx->ctxvaws_pos = offset + 3;
		nv50_gw_constwuct_gene_vfetch(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 4 */
		ctx->ctxvaws_pos = offset + 4;
		nv50_gw_constwuct_gene_ccache(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 5 */
		ctx->ctxvaws_pos = offset + 5;
		nv50_gw_constwuct_gene_wopm2(ctx);
		nv50_gw_constwuct_gene_wopm1(ctx);
		/* pew-WOP context */
		fow (i = 0; i < 8; i++)
			if (units & (1<<(i+16)))
				nv50_gw_constwuct_gene_wopc(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 6 */
		ctx->ctxvaws_pos = offset + 6;
		nv50_gw_constwuct_gene_zcuww(ctx);
		nv50_gw_constwuct_gene_cwipid(ctx);
		nv50_gw_constwuct_gene_eng2d(ctx);
		if (units & (1 << 0))
			nv50_gw_constwuct_xfew_tp(ctx);
		if (units & (1 << 1))
			nv50_gw_constwuct_xfew_tp(ctx);
		if (units & (1 << 2))
			nv50_gw_constwuct_xfew_tp(ctx);
		if (units & (1 << 3))
			nv50_gw_constwuct_xfew_tp(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 7 */
		ctx->ctxvaws_pos = offset + 7;
		if (device->chipset == 0xa0) {
			if (units & (1 << 4))
				nv50_gw_constwuct_xfew_tp(ctx);
			if (units & (1 << 5))
				nv50_gw_constwuct_xfew_tp(ctx);
			if (units & (1 << 6))
				nv50_gw_constwuct_xfew_tp(ctx);
			if (units & (1 << 7))
				nv50_gw_constwuct_xfew_tp(ctx);
			if (units & (1 << 8))
				nv50_gw_constwuct_xfew_tp(ctx);
			if (units & (1 << 9))
				nv50_gw_constwuct_xfew_tp(ctx);
		} ewse {
			nv50_gw_constwuct_gene_unk14xx(ctx);
		}
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;
	}

	ctx->ctxvaws_pos = offset + size * 8;
	ctx->ctxvaws_pos = (ctx->ctxvaws_pos+0x3f)&~0x3f;
	cp_wsw (ctx, offset);
	cp_out (ctx, CP_SET_XFEW_POINTEW);
	cp_wsw (ctx, size);
	cp_out (ctx, CP_SEEK_1);
	cp_out (ctx, CP_XFEW_1);
	cp_wait(ctx, XFEW, BUSY);
}

/*
 * non-twiviaw demagiced pawts of ctx init go hewe
 */

static void
nv50_gw_constwuct_gene_dispatch(stwuct nvkm_gwctx *ctx)
{
	/* stawt of stwand 0 */
	stwuct nvkm_device *device = ctx->device;
	/* SEEK */
	if (device->chipset == 0x50)
		xf_emit(ctx, 5, 0);
	ewse if (!IS_NVA3F(device->chipset))
		xf_emit(ctx, 6, 0);
	ewse
		xf_emit(ctx, 4, 0);
	/* SEEK */
	/* the PGWAPH's intewnaw FIFO */
	if (device->chipset == 0x50)
		xf_emit(ctx, 8*3, 0);
	ewse
		xf_emit(ctx, 0x100*3, 0);
	/* and anothew bonus swot?!? */
	xf_emit(ctx, 3, 0);
	/* and YET ANOTHEW bonus swot? */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 3, 0);
	/* SEEK */
	/* CTX_SWITCH: caches of gw objects bound to subchannews. 8 vawues, wast used index */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	if (device->chipset < 0x90)
		xf_emit(ctx, 4, 0);
	/* SEEK */
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 6*2, 0);
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 6*2, 0);
	xf_emit(ctx, 2, 0);
	/* SEEK */
	if (device->chipset == 0x50)
		xf_emit(ctx, 0x1c, 0);
	ewse if (device->chipset < 0xa0)
		xf_emit(ctx, 0x1e, 0);
	ewse
		xf_emit(ctx, 0x22, 0);
	/* SEEK */
	xf_emit(ctx, 0x15, 0);
}

static void
nv50_gw_constwuct_gene_m2mf(stwuct nvkm_gwctx *ctx)
{
	/* Stwand 0, wight aftew dispatch */
	stwuct nvkm_device *device = ctx->device;
	int smawwm2mf = 0;
	if (device->chipset < 0x92 || device->chipset == 0x98)
		smawwm2mf = 1;
	/* SEEK */
	xf_emit (ctx, 1, 0);		/* DMA_NOTIFY instance >> 4 */
	xf_emit (ctx, 1, 0);		/* DMA_BUFFEW_IN instance >> 4 */
	xf_emit (ctx, 1, 0);		/* DMA_BUFFEW_OUT instance >> 4 */
	xf_emit (ctx, 1, 0);		/* OFFSET_IN */
	xf_emit (ctx, 1, 0);		/* OFFSET_OUT */
	xf_emit (ctx, 1, 0);		/* PITCH_IN */
	xf_emit (ctx, 1, 0);		/* PITCH_OUT */
	xf_emit (ctx, 1, 0);		/* WINE_WENGTH */
	xf_emit (ctx, 1, 0);		/* WINE_COUNT */
	xf_emit (ctx, 1, 0x21);		/* FOWMAT: bits 0-4 INPUT_INC, bits 5-9 OUTPUT_INC */
	xf_emit (ctx, 1, 1);		/* WINEAW_IN */
	xf_emit (ctx, 1, 0x2);		/* TIWING_MODE_IN: bits 0-2 y tiwing, bits 3-5 z tiwing */
	xf_emit (ctx, 1, 0x100);	/* TIWING_PITCH_IN */
	xf_emit (ctx, 1, 0x100);	/* TIWING_HEIGHT_IN */
	xf_emit (ctx, 1, 1);		/* TIWING_DEPTH_IN */
	xf_emit (ctx, 1, 0);		/* TIWING_POSITION_IN_Z */
	xf_emit (ctx, 1, 0);		/* TIWING_POSITION_IN */
	xf_emit (ctx, 1, 1);		/* WINEAW_OUT */
	xf_emit (ctx, 1, 0x2);		/* TIWING_MODE_OUT: bits 0-2 y tiwing, bits 3-5 z tiwing */
	xf_emit (ctx, 1, 0x100);	/* TIWING_PITCH_OUT */
	xf_emit (ctx, 1, 0x100);	/* TIWING_HEIGHT_OUT */
	xf_emit (ctx, 1, 1);		/* TIWING_DEPTH_OUT */
	xf_emit (ctx, 1, 0);		/* TIWING_POSITION_OUT_Z */
	xf_emit (ctx, 1, 0);		/* TIWING_POSITION_OUT */
	xf_emit (ctx, 1, 0);		/* OFFSET_IN_HIGH */
	xf_emit (ctx, 1, 0);		/* OFFSET_OUT_HIGH */
	/* SEEK */
	if (smawwm2mf)
		xf_emit(ctx, 0x40, 0);	/* 20 * ffffffff, 3ffff */
	ewse
		xf_emit(ctx, 0x100, 0);	/* 80 * ffffffff, 3ffff */
	xf_emit(ctx, 4, 0);		/* 1f/7f, 0, 1f/7f, 0 [1f fow smawwm2mf, 7f othewwise] */
	/* SEEK */
	if (smawwm2mf)
		xf_emit(ctx, 0x400, 0);	/* ffffffff */
	ewse
		xf_emit(ctx, 0x800, 0);	/* ffffffff */
	xf_emit(ctx, 4, 0);		/* ff/1ff, 0, 0, 0 [ff fow smawwm2mf, 1ff othewwise] */
	/* SEEK */
	xf_emit(ctx, 0x40, 0);		/* 20 * bits ffffffff, 3ffff */
	xf_emit(ctx, 0x6, 0);		/* 1f, 0, 1f, 0, 1f, 0 */
}

static void
nv50_gw_constwuct_gene_ccache(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	xf_emit(ctx, 2, 0);		/* WO */
	xf_emit(ctx, 0x800, 0);		/* ffffffff */
	switch (device->chipset) {
	case 0x50:
	case 0x92:
	case 0xa0:
		xf_emit(ctx, 0x2b, 0);
		bweak;
	case 0x84:
		xf_emit(ctx, 0x29, 0);
		bweak;
	case 0x94:
	case 0x96:
	case 0xa3:
		xf_emit(ctx, 0x27, 0);
		bweak;
	case 0x86:
	case 0x98:
	case 0xa5:
	case 0xa8:
	case 0xaa:
	case 0xac:
	case 0xaf:
		xf_emit(ctx, 0x25, 0);
		bweak;
	}
	/* CB bindings, 0x80 of them. fiwst wowd is addwess >> 8, second is
	 * size >> 4 | vawid << 24 */
	xf_emit(ctx, 0x100, 0);		/* ffffffff CB_DEF */
	xf_emit(ctx, 1, 0);		/* 0000007f CB_ADDW_BUFFEW */
	xf_emit(ctx, 1, 0);		/* 0 */
	xf_emit(ctx, 0x30, 0);		/* ff SET_PWOGWAM_CB */
	xf_emit(ctx, 1, 0);		/* 3f wast SET_PWOGWAM_CB */
	xf_emit(ctx, 4, 0);		/* WO */
	xf_emit(ctx, 0x100, 0);		/* ffffffff */
	xf_emit(ctx, 8, 0);		/* 1f, 0, 0, ... */
	xf_emit(ctx, 8, 0);		/* ffffffff */
	xf_emit(ctx, 4, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 3 */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_CODE_CB */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_TIC */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_TSC */
	xf_emit(ctx, 1, 0);		/* 00000001 WINKED_TSC */
	xf_emit(ctx, 1, 0);		/* 000000ff TIC_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff TIC_ADDWESS_WOW */
	xf_emit(ctx, 1, 0x3fffff);	/* 003fffff TIC_WIMIT */
	xf_emit(ctx, 1, 0);		/* 000000ff TSC_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff TSC_ADDWESS_WOW */
	xf_emit(ctx, 1, 0x1fff);	/* 000fffff TSC_WIMIT */
	xf_emit(ctx, 1, 0);		/* 000000ff VP_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff VP_ADDWESS_WOW */
	xf_emit(ctx, 1, 0);		/* 00ffffff VP_STAWT_ID */
	xf_emit(ctx, 1, 0);		/* 000000ff CB_DEF_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff CB_DEF_ADDWESS_WOW */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0);		/* 000000ff GP_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff GP_ADDWESS_WOW */
	xf_emit(ctx, 1, 0);		/* 00ffffff GP_STAWT_ID */
	xf_emit(ctx, 1, 0);		/* 000000ff FP_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff FP_ADDWESS_WOW */
	xf_emit(ctx, 1, 0);		/* 00ffffff FP_STAWT_ID */
}

static void
nv50_gw_constwuct_gene_unk10xx(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i;
	/* end of awea 2 on pwe-NVA0, awea 1 on NVAx */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VEWTEX_OUTPUT_COUNT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WEG_AWWOC_WESUWT */
	xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 VEWTEX_TWO_SIDE_ENABWE */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);
	ewse
		xf_emit(ctx, 1, 0x7ff);	/* 000007ff */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	fow (i = 0; i < 8; i++) {
		switch (device->chipset) {
		case 0x50:
		case 0x86:
		case 0x98:
		case 0xaa:
		case 0xac:
			xf_emit(ctx, 0xa0, 0);	/* ffffffff */
			bweak;
		case 0x84:
		case 0x92:
		case 0x94:
		case 0x96:
			xf_emit(ctx, 0x120, 0);
			bweak;
		case 0xa5:
		case 0xa8:
			xf_emit(ctx, 0x100, 0);	/* ffffffff */
			bweak;
		case 0xa0:
		case 0xa3:
		case 0xaf:
			xf_emit(ctx, 0x400, 0);	/* ffffffff */
			bweak;
		}
		xf_emit(ctx, 4, 0);	/* 3f, 0, 0, 0 */
		xf_emit(ctx, 4, 0);	/* ffffffff */
	}
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VEWTEX_OUTPUT_COUNT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WEG_AWWOC_TEMP */
	xf_emit(ctx, 1, 1);		/* 00000001 WASTEWIZE_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 0x27);		/* 000000ff UNK0FD4 */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUIWTIN_WESUWT_EN */
	xf_emit(ctx, 1, 0x26);		/* 000000ff SEMANTIC_WAYEW */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
}

static void
nv50_gw_constwuct_gene_unk34xx(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	/* end of awea 2 on pwe-NVA0, awea 1 on NVAx */
	xf_emit(ctx, 1, 0);		/* 00000001 VIEWPOWT_CWIP_WECTS_EN */
	xf_emit(ctx, 1, 0);		/* 00000003 VIEWPOWT_CWIP_MODE */
	xf_emit(ctx, 0x10, 0x04000000);	/* 07ffffff VIEWPOWT_CWIP_HOWIZ*8, VIEWPOWT_CWIP_VEWT*8 */
	xf_emit(ctx, 1, 0);		/* 00000001 POWYGON_STIPPWE_ENABWE */
	xf_emit(ctx, 0x20, 0);		/* ffffffff POWYGON_STIPPWE */
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0D64 */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0DF4 */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_OWIGIN */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0x1fe21);	/* 0001ffff teswa UNK0FAC */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0x0fac6881);
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 1);
		xf_emit(ctx, 3, 0);
	}
}

static void
nv50_gw_constwuct_gene_unk14xx(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	/* middwe of awea 2 on pwe-NVA0, beginning of awea 2 on NVA0, awea 7 on >NVA0 */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 5, 0);		/* ffffffff */
		xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COWOW */
		xf_emit(ctx, 1, 0);		/* 00000001 */
		xf_emit(ctx, 1, 0);		/* 000003ff */
		xf_emit(ctx, 1, 0x804);		/* 00000fff SEMANTIC_CWIP */
		xf_emit(ctx, 1, 0);		/* 00000001 */
		xf_emit(ctx, 2, 4);		/* 7f, ff */
		xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTEWPOWANT_CTWW */
	}
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 4);			/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);			/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);			/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0x10);			/* 7f/ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 1, 0);			/* 000000ff VP_CWIP_DISTANCE_ENABWE */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);		/* 3ff */
	xf_emit(ctx, 1, 0);			/* 000000ff teswa UNK1940 */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK0D7C */
	xf_emit(ctx, 1, 0x804);			/* 00000fff SEMANTIC_CWIP */
	xf_emit(ctx, 1, 1);			/* 00000001 VIEWPOWT_TWANSFOWM_EN */
	xf_emit(ctx, 1, 0x1a);			/* 0000001f POWYGON_MODE */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0x7f);		/* 000000ff teswa UNK0FFC */
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 1);			/* 00000001 SHADE_MODEW */
	xf_emit(ctx, 1, 0x80c14);		/* 01ffffff SEMANTIC_COWOW */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 0x8100c12);		/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 1, 4);			/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);			/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);			/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0x10);			/* 7f/ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK0D7C */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK0F8C */
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 1);			/* 00000001 VIEWPOWT_TWANSFOWM_EN */
	xf_emit(ctx, 1, 0x8100c12);		/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 4, 0);			/* ffffffff NOPEWSPECTIVE_BITMAP */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 0);			/* 0000000f */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);		/* 000003ff teswa UNK0D68 */
	ewse
		xf_emit(ctx, 1, 0x7ff);		/* 000007ff teswa UNK0D68 */
	xf_emit(ctx, 1, 0x80c14);		/* 01ffffff SEMANTIC_COWOW */
	xf_emit(ctx, 1, 0);			/* 00000001 VEWTEX_TWO_SIDE_ENABWE */
	xf_emit(ctx, 0x30, 0);			/* ffffffff VIEWPOWT_SCAWE: X0, Y0, Z0, X1, Y1, ... */
	xf_emit(ctx, 3, 0);			/* f, 0, 0 */
	xf_emit(ctx, 3, 0);			/* ffffffff wast VIEWPOWT_SCAWE? */
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 1);			/* 00000001 VIEWPOWT_TWANSFOWM_EN */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1924 */
	xf_emit(ctx, 1, 0x10);			/* 000000ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 1, 0);			/* 00000001 */
	xf_emit(ctx, 0x30, 0);			/* ffffffff VIEWPOWT_TWANSWATE */
	xf_emit(ctx, 3, 0);			/* f, 0, 0 */
	xf_emit(ctx, 3, 0);			/* ffffffff */
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 2, 0x88);			/* 000001ff teswa UNK19D8 */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1924 */
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 4);			/* 0000000f CUWW_MODE */
	xf_emit(ctx, 2, 0);			/* 07ffffff SCWEEN_SCISSOW */
	xf_emit(ctx, 2, 0);			/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 0);			/* 00000003 WINDOW_OWIGIN */
	xf_emit(ctx, 0x10, 0);			/* 00000001 SCISSOW_ENABWE */
	xf_emit(ctx, 1, 0);			/* 0001ffff GP_BUIWTIN_WESUWT_EN */
	xf_emit(ctx, 1, 0x26);			/* 000000ff SEMANTIC_WAYEW */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 0);			/* 0000000f */
	xf_emit(ctx, 1, 0x3f800000);		/* ffffffff WINE_WIDTH */
	xf_emit(ctx, 1, 0);			/* 00000001 WINE_STIPPWE_ENABWE */
	xf_emit(ctx, 1, 0);			/* 00000001 WINE_SMOOTH_ENABWE */
	xf_emit(ctx, 1, 0);			/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, 0x1a);			/* 0000001f POWYGON_MODE */
	xf_emit(ctx, 1, 0x10);			/* 000000ff VIEW_VOWUME_CWIP_CTWW */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 0);		/* ffffffff */
		xf_emit(ctx, 1, 0);		/* 00000001 */
		xf_emit(ctx, 1, 0);		/* 000003ff */
	}
	xf_emit(ctx, 0x20, 0);			/* 10xbits ffffffff, 3fffff. SCISSOW_* */
	xf_emit(ctx, 1, 0);			/* f */
	xf_emit(ctx, 1, 0);			/* 0? */
	xf_emit(ctx, 1, 0);			/* ffffffff */
	xf_emit(ctx, 1, 0);			/* 003fffff */
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 0x52);			/* 000001ff SEMANTIC_PTSZ */
	xf_emit(ctx, 1, 0);			/* 0001ffff GP_BUIWTIN_WESUWT_EN */
	xf_emit(ctx, 1, 0x26);			/* 000000ff SEMANTIC_WAYEW */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 4);			/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);			/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);			/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0x1a);			/* 0000001f POWYGON_MODE */
	xf_emit(ctx, 1, 0);			/* 00000001 WINE_SMOOTH_ENABWE */
	xf_emit(ctx, 1, 0);			/* 00000001 WINE_STIPPWE_ENABWE */
	xf_emit(ctx, 1, 0x00ffff00);		/* 00ffffff WINE_STIPPWE_PATTEWN */
	xf_emit(ctx, 1, 0);			/* 0000000f */
}

static void
nv50_gw_constwuct_gene_zcuww(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	/* end of stwand 0 on pwe-NVA0, beginning of stwand 6 on NVAx */
	/* SEEK */
	xf_emit(ctx, 1, 0x3f);		/* 0000003f UNK1590 */
	xf_emit(ctx, 1, 0);		/* 00000001 AWPHA_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_WEF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_BACK_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 1, 2);		/* 00000003 teswa UNK143C */
	xf_emit(ctx, 2, 0x04000000);	/* 07ffffff teswa UNK0D6C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 CWIPID_ENABWE */
	xf_emit(ctx, 2, 0);		/* ffffffff DEPTH_BOUNDS */
	xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 4);		/* 0000000f CUWW_MODE */
	xf_emit(ctx, 1, 0);		/* 0000ffff */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* 00000001 POWYGON_STIPPWE_ENABWE */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTWOW */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUIWTIN_WESUWT_EN */
	xf_emit(ctx, 1, 0);		/* 000000ff CWEAW_STENCIW */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_FWONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_WEF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_FWONT_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_BACK_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff CWEAW_DEPTH */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 00000003 teswa UNK1108 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPWECNT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0x1001);	/* 00001fff ZETA_AWWAY_MODE */
	/* SEEK */
	xf_emit(ctx, 4, 0xffff);	/* 0000ffff MSAA_MASK */
	xf_emit(ctx, 0x10, 0);		/* 00000001 SCISSOW_ENABWE */
	xf_emit(ctx, 0x10, 0);		/* ffffffff DEPTH_WANGE_NEAW */
	xf_emit(ctx, 0x10, 0x3f800000);	/* ffffffff DEPTH_WANGE_FAW */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff/3ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 1, 0);		/* 00000001 VIEWPOWT_CWIP_WECTS_EN */
	xf_emit(ctx, 1, 3);		/* 00000003 FP_CTWW_UNK196C */
	xf_emit(ctx, 1, 0);		/* 00000003 teswa UNK1968 */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 0fffffff teswa UNK1104 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK151C */
}

static void
nv50_gw_constwuct_gene_cwipid(stwuct nvkm_gwctx *ctx)
{
	/* middwe of stwand 0 on pwe-NVA0 [aftew 24xx], middwe of awea 6 on NVAx */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000007 UNK0FB4 */
	/* SEEK */
	xf_emit(ctx, 4, 0);		/* 07ffffff CWIPID_WEGION_HOWIZ */
	xf_emit(ctx, 4, 0);		/* 07ffffff CWIPID_WEGION_VEWT */
	xf_emit(ctx, 2, 0);		/* 07ffffff SCWEEN_SCISSOW */
	xf_emit(ctx, 2, 0x04000000);	/* 07ffffff UNK1508 */
	xf_emit(ctx, 1, 0);		/* 00000001 CWIPID_ENABWE */
	xf_emit(ctx, 1, 0x80);		/* 00003fff CWIPID_WIDTH */
	xf_emit(ctx, 1, 0);		/* 000000ff CWIPID_ID */
	xf_emit(ctx, 1, 0);		/* 000000ff CWIPID_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff CWIPID_ADDWESS_WOW */
	xf_emit(ctx, 1, 0x80);		/* 00003fff CWIPID_HEIGHT */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_CWIPID */
}

static void
nv50_gw_constwuct_gene_unk24xx(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i;
	/* middwe of stwand 0 on pwe-NVA0 [aftew m2mf], end of stwand 2 on NVAx */
	/* SEEK */
	xf_emit(ctx, 0x33, 0);
	/* SEEK */
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	/* SEEK */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 4, 0);	/* WO */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */
		xf_emit(ctx, 9, 0);	/* ffffffff, 7ff */

		xf_emit(ctx, 4, 0);	/* WO */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */
		xf_emit(ctx, 9, 0);	/* ffffffff, 7ff */
	} ewse {
		xf_emit(ctx, 0xc, 0);	/* WO */
		/* SEEK */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */

		/* SEEK */
		xf_emit(ctx, 0xc, 0);	/* WO */
		/* SEEK */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTEWPOWANT_CTWW */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 3);	/* 00000003 teswa UNK1100 */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUIWTIN_ATTW_EN */
	xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COWOW */
	xf_emit(ctx, 1, 1);		/* 00000001 */
	/* SEEK */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 2, 4);	/* 000000ff */
	xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 VEWTEX_TWO_SIDE_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPWITE_ENABWE */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 1, 0x27);		/* 000000ff SEMANTIC_PWIM_ID */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 1);		/* 00000001 */
	fow (i = 0; i < 10; i++) {
		/* SEEK */
		xf_emit(ctx, 0x40, 0);		/* ffffffff */
		xf_emit(ctx, 0x10, 0);		/* 3, 0, 0.... */
		xf_emit(ctx, 0x10, 0);		/* ffffffff */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPWITE_CTWW */
	xf_emit(ctx, 1, 1);		/* 00000001 */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 4, 0);		/* ffffffff NOPEWSPECTIVE_BITMAP */
	xf_emit(ctx, 0x10, 0);		/* 00ffffff POINT_COOWD_WEPWACE_MAP */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_OWIGIN */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTEWPOWANT_CTWW */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 000003ff */
}

static void
nv50_gw_constwuct_gene_vfetch(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int acnt = 0x10, wep, i;
	/* beginning of stwand 1 on pwe-NVA0, stwand 3 on NVAx */
	if (IS_NVA3F(device->chipset))
		acnt = 0x20;
	/* SEEK */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 1, 0);	/* ffffffff teswa UNK13A4 */
		xf_emit(ctx, 1, 1);	/* 00000fff teswa UNK1318 */
	}
	xf_emit(ctx, 1, 0);		/* ffffffff VEWTEX_BUFFEW_FIWST */
	xf_emit(ctx, 1, 0);		/* 00000001 PWIMITIVE_WESTAWT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK0DE8 */
	xf_emit(ctx, 1, 0);		/* ffffffff PWIMITIVE_WESTAWT_INDEX */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, acnt/8, 0);	/* ffffffff VTX_ATW_MASK_UNK0DD0 */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUIWTIN_ATTW_EN */
	xf_emit(ctx, 1, 0x20);		/* 0000ffff teswa UNK129C */
	xf_emit(ctx, 1, 0);		/* 000000ff tuwing UNK370??? */
	xf_emit(ctx, 1, 0);		/* 0000ffff tuwing USEW_PAWAM_COUNT */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0xb, 0);	/* WO */
	ewse if (device->chipset >= 0xa0)
		xf_emit(ctx, 0x9, 0);	/* WO */
	ewse
		xf_emit(ctx, 0x8, 0);	/* WO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 EDGE_FWAG */
	xf_emit(ctx, 1, 0);		/* 00000001 PWOVOKING_VEWTEX_WAST */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POWYGON_MODE */
	/* SEEK */
	xf_emit(ctx, 0xc, 0);		/* WO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 7f/ff */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WEG_AWWOC_WESUWT */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUIWTIN_ATTW_EN */
	xf_emit(ctx, 1, 4);		/* 000001ff UNK1A28 */
	xf_emit(ctx, 1, 8);		/* 000001ff UNK0DF0 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);	/* 3ff teswa UNK0D68 */
	ewse
		xf_emit(ctx, 1, 0x7ff);	/* 7ff teswa UNK0D68 */
	if (device->chipset == 0xa8)
		xf_emit(ctx, 1, 0x1e00);	/* 7fff */
	/* SEEK */
	xf_emit(ctx, 0xc, 0);		/* WO ow cwose */
	/* SEEK */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUIWTIN_ATTW_EN */
	if (device->chipset > 0x50 && device->chipset < 0xa0)
		xf_emit(ctx, 2, 0);	/* ffffffff */
	ewse
		xf_emit(ctx, 1, 0);	/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000003 teswa UNK0FD8 */
	/* SEEK */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 0x10, 0);	/* 0? */
		xf_emit(ctx, 2, 0);	/* weiwd... */
		xf_emit(ctx, 2, 0);	/* WO */
	} ewse {
		xf_emit(ctx, 8, 0);	/* 0? */
		xf_emit(ctx, 1, 0);	/* weiwd... */
		xf_emit(ctx, 2, 0);	/* WO */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffffffff VB_EWEMENT_BASE */
	xf_emit(ctx, 1, 0);		/* ffffffff UNK1438 */
	xf_emit(ctx, acnt, 0);		/* 1 teswa UNK1000 */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0);	/* ffffffff teswa UNK1118? */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VEWTEX_AWWAY_UNK90C */
	xf_emit(ctx, 1, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VEWTEX_AWWAY_UNK90C */
	xf_emit(ctx, 1, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* WO */
	xf_emit(ctx, 2, 0);		/* WO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK111C? */
	xf_emit(ctx, 1, 0);		/* WO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 000000ff UNK15F4_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff UNK15F4_ADDWESS_WOW */
	xf_emit(ctx, 1, 0);		/* 000000ff UNK0F84_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff UNK0F84_ADDWESS_WOW */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 00003fff VEWTEX_AWWAY_ATTWIB_OFFSET */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 00000fff VEWTEX_AWWAY_STWIDE */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VEWTEX_AWWAY_WOW */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 000000ff VEWTEX_AWWAY_HIGH */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VEWTEX_WIMIT_WOW */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 000000ff VEWTEX_WIMIT_HIGH */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, acnt, 0);		/* f */
		xf_emit(ctx, 3, 0);		/* f/1f */
	}
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 2, 0);	/* WO */
	ewse
		xf_emit(ctx, 5, 0);	/* WO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffff DMA_VTXBUF */
	/* SEEK */
	if (device->chipset < 0xa0) {
		xf_emit(ctx, 0x41, 0);	/* WO */
		/* SEEK */
		xf_emit(ctx, 0x11, 0);	/* WO */
	} ewse if (!IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x50, 0);	/* WO */
	ewse
		xf_emit(ctx, 0x58, 0);	/* WO */
	/* SEEK */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, 1, 1);		/* 1 UNK0DEC */
	/* SEEK */
	xf_emit(ctx, acnt*4, 0);	/* ffffffff VTX_ATTW */
	xf_emit(ctx, 4, 0);		/* f/1f, 0, 0, 0 */
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x1d, 0);	/* WO */
	ewse
		xf_emit(ctx, 0x16, 0);	/* WO */
	/* SEEK */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTW_EN */
	/* SEEK */
	if (device->chipset < 0xa0)
		xf_emit(ctx, 8, 0);	/* WO */
	ewse if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0xc, 0);	/* WO */
	ewse
		xf_emit(ctx, 7, 0);	/* WO */
	/* SEEK */
	xf_emit(ctx, 0xa, 0);		/* WO */
	if (device->chipset == 0xa0)
		wep = 0xc;
	ewse
		wep = 4;
	fow (i = 0; i < wep; i++) {
		/* SEEK */
		if (IS_NVA3F(device->chipset))
			xf_emit(ctx, 0x20, 0);	/* ffffffff */
		xf_emit(ctx, 0x200, 0);	/* ffffffff */
		xf_emit(ctx, 4, 0);	/* 7f/ff, 0, 0, 0 */
		xf_emit(ctx, 4, 0);	/* ffffffff */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 113/111 */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTW_EN */
	xf_emit(ctx, acnt/8, 0);	/* ffffffff VTX_ATTW_MASK_UNK0DD0 */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUIWTIN_ATTW_EN */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 7, 0);	/* weiwd... */
	ewse
		xf_emit(ctx, 5, 0);	/* weiwd... */
}

static void
nv50_gw_constwuct_gene_eng2d(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	/* middwe of stwand 1 on pwe-NVA0 [aftew vfetch], middwe of stwand 6 on NVAx */
	/* SEEK */
	xf_emit(ctx, 2, 0);		/* 0001ffff CWIP_X, CWIP_Y */
	xf_emit(ctx, 2, 0);		/* 0000ffff CWIP_W, CWIP_H */
	xf_emit(ctx, 1, 0);		/* 00000001 CWIP_ENABWE */
	if (device->chipset < 0xa0) {
		/* this is usewess on evewything but the owiginaw NV50,
		 * guess they fowgot to nuke it. Ow just didn't bothew. */
		xf_emit(ctx, 2, 0);	/* 0000ffff IFC_CWIP_X, Y */
		xf_emit(ctx, 2, 1);	/* 0000ffff IFC_CWIP_W, H */
		xf_emit(ctx, 1, 0);	/* 00000001 IFC_CWIP_ENABWE */
	}
	xf_emit(ctx, 1, 1);		/* 00000001 DST_WINEAW */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_WIDTH */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_HEIGHT */
	xf_emit(ctx, 1, 0x11);		/* 3f[NV50]/7f[NV84+] DST_FOWMAT */
	xf_emit(ctx, 1, 0);		/* 0001ffff DWAW_POINT_X */
	xf_emit(ctx, 1, 8);		/* 0000000f DWAW_UNK58C */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DST_X_FWACT */
	xf_emit(ctx, 1, 0);		/* 0001ffff SIFC_DST_X_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DST_Y_FWACT */
	xf_emit(ctx, 1, 0);		/* 0001ffff SIFC_DST_Y_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DX_DU_FWACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff SIFC_DX_DU_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DY_DV_FWACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff SIFC_DY_DV_INT */
	xf_emit(ctx, 1, 1);		/* 0000ffff SIFC_WIDTH */
	xf_emit(ctx, 1, 1);		/* 0000ffff SIFC_HEIGHT */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff SIFC_FOWMAT */
	xf_emit(ctx, 1, 2);		/* 00000003 SIFC_BITMAP_UNK808 */
	xf_emit(ctx, 1, 0);		/* 00000003 SIFC_BITMAP_WINE_PACK_MODE */
	xf_emit(ctx, 1, 0);		/* 00000001 SIFC_BITMAP_WSB_FIWST */
	xf_emit(ctx, 1, 0);		/* 00000001 SIFC_BITMAP_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000ffff BWIT_DST_X */
	xf_emit(ctx, 1, 0);		/* 0000ffff BWIT_DST_Y */
	xf_emit(ctx, 1, 0);		/* 000fffff BWIT_DU_DX_FWACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BWIT_DU_DX_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff BWIT_DV_DY_FWACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BWIT_DV_DY_INT */
	xf_emit(ctx, 1, 1);		/* 0000ffff BWIT_DST_W */
	xf_emit(ctx, 1, 1);		/* 0000ffff BWIT_DST_H */
	xf_emit(ctx, 1, 0);		/* 000fffff BWIT_SWC_X_FWACT */
	xf_emit(ctx, 1, 0);		/* 0001ffff BWIT_SWC_X_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff BWIT_SWC_Y_FWACT */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK888 */
	xf_emit(ctx, 1, 4);		/* 0000003f UNK884 */
	xf_emit(ctx, 1, 0);		/* 00000007 UNK880 */
	xf_emit(ctx, 1, 1);		/* 0000001f teswa UNK0FB8 */
	xf_emit(ctx, 1, 0x15);		/* 000000ff teswa UNK128C */
	xf_emit(ctx, 2, 0);		/* 00000007, ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK260 */
	xf_emit(ctx, 1, 0x4444480);	/* 1fffffff UNK870 */
	/* SEEK */
	xf_emit(ctx, 0x10, 0);
	/* SEEK */
	xf_emit(ctx, 0x27, 0);
}

static void
nv50_gw_constwuct_gene_csched(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	/* middwe of stwand 1 on pwe-NVA0 [aftew eng2d], middwe of stwand 0 on NVAx */
	/* SEEK */
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY... what is it doing hewe??? */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1924 */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_OWIGIN */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 1, 0);		/* 000003ff */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffffffff tuwing UNK364 */
	xf_emit(ctx, 1, 0);		/* 0000000f tuwing UNK36C */
	xf_emit(ctx, 1, 0);		/* 0000ffff USEW_PAWAM_COUNT */
	xf_emit(ctx, 1, 0x100);		/* 00ffffff tuwing UNK384 */
	xf_emit(ctx, 1, 0);		/* 0000000f tuwing UNK2A0 */
	xf_emit(ctx, 1, 0);		/* 0000ffff GWIDID */
	xf_emit(ctx, 1, 0x10001);	/* ffffffff GWIDDIM_XY */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0x10001);	/* ffffffff BWOCKDIM_XY */
	xf_emit(ctx, 1, 1);		/* 0000ffff BWOCKDIM_Z */
	xf_emit(ctx, 1, 0x10001);	/* 00ffffff BWOCK_AWWOC */
	xf_emit(ctx, 1, 1);		/* 00000001 WANES32 */
	xf_emit(ctx, 1, 4);		/* 000000ff FP_WEG_AWWOC_TEMP */
	xf_emit(ctx, 1, 2);		/* 00000003 WEG_MODE */
	/* SEEK */
	xf_emit(ctx, 0x40, 0);		/* ffffffff USEW_PAWAM */
	switch (device->chipset) {
	case 0x50:
	case 0x92:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x80, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0x10*2, 0);	/* ffffffff, 1f */
		bweak;
	case 0x84:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x60, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0xc*2, 0);	/* ffffffff, 1f */
		bweak;
	case 0x94:
	case 0x96:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x40, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 8*2, 0);	/* ffffffff, 1f */
		bweak;
	case 0x86:
	case 0x98:
		xf_emit(ctx, 4, 0);	/* f, 0, 0, 0 */
		xf_emit(ctx, 0x10, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 2*2, 0);	/* ffffffff, 1f */
		bweak;
	case 0xa0:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0xf0, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0x1e*2, 0);	/* ffffffff, 1f */
		bweak;
	case 0xa3:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x60, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0xc*2, 0);	/* ffffffff, 1f */
		bweak;
	case 0xa5:
	case 0xaf:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x30, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 6*2, 0);	/* ffffffff, 1f */
		bweak;
	case 0xaa:
		xf_emit(ctx, 0x12, 0);
		bweak;
	case 0xa8:
	case 0xac:
		xf_emit(ctx, 4, 0);	/* f, 0, 0, 0 */
		xf_emit(ctx, 0x10, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 2*2, 0);	/* ffffffff, 1f */
		bweak;
	}
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 0);		/* 00000000 */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 0000001f */
	xf_emit(ctx, 4, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000003 tuwing UNK35C */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 4, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000003 tuwing UNK35C */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 000000ff */
}

static void
nv50_gw_constwuct_gene_unk1cxx(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 0x3f800000);	/* ffffffff WINE_WIDTH */
	xf_emit(ctx, 1, 0);		/* 00000001 WINE_SMOOTH_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1658 */
	xf_emit(ctx, 1, 0);		/* 00000001 POWYGON_SMOOTH_ENABWE */
	xf_emit(ctx, 3, 0);		/* 00000001 POWYGON_OFFSET_*_ENABWE */
	xf_emit(ctx, 1, 4);		/* 0000000f CUWW_MODE */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POWYGON_MODE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPWITE_ENABWE */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK165C */
	xf_emit(ctx, 0x10, 0);		/* 00000001 SCISSOW_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000001 WINE_STIPPWE_ENABWE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff WINE_STIPPWE_PATTEWN */
	xf_emit(ctx, 1, 0);		/* ffffffff POWYGON_OFFSET_UNITS */
	xf_emit(ctx, 1, 0);		/* ffffffff POWYGON_OFFSET_FACTOW */
	xf_emit(ctx, 1, 0);		/* 00000003 teswa UNK1668 */
	xf_emit(ctx, 2, 0);		/* 07ffffff SCWEEN_SCISSOW */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 1, 0x11);		/* 0000007f WT_FOWMAT */
	xf_emit(ctx, 7, 0);		/* 0000007f WT_FOWMAT */
	xf_emit(ctx, 8, 0);		/* 00000001 WT_HOWIZ_WINEAW */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 AWPHA_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000007 AWPHA_TEST_FUNC */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 3);	/* 00000003 UNK16B4 */
	ewse if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 1);	/* 00000001 UNK16B4 */
	xf_emit(ctx, 1, 0);		/* 00000003 MUWTISAMPWE_CTWW */
	xf_emit(ctx, 1, 0);		/* 00000003 teswa UNK0F90 */
	xf_emit(ctx, 1, 2);		/* 00000003 teswa UNK143C */
	xf_emit(ctx, 2, 0x04000000);	/* 07ffffff teswa UNK0D6C */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_MASK */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPWECNT_ENABWE */
	xf_emit(ctx, 1, 5);		/* 0000000f UNK1408 */
	xf_emit(ctx, 1, 0x52);		/* 000001ff SEMANTIC_PTSZ */
	xf_emit(ctx, 1, 0);		/* ffffffff POINT_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, 0);		/* 00000007 teswa UNK0FB4 */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 0);	/* 3ff */
		xf_emit(ctx, 1, 1);	/* 00000001 teswa UNK1110 */
	}
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0);	/* 00000003 teswa UNK1928 */
	xf_emit(ctx, 0x10, 0);		/* ffffffff DEPTH_WANGE_NEAW */
	xf_emit(ctx, 0x10, 0x3f800000);	/* ffffffff DEPTH_WANGE_FAW */
	xf_emit(ctx, 1, 0x10);		/* 000000ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 0x20, 0);		/* 07ffffff VIEWPOWT_HOWIZ, then VIEWPOWT_VEWT. (W&0x3fff)<<13 | (X&0x1fff). */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK187C */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_OWIGIN */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_BACK_ENABWE */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_MASK */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 1, 5);		/* 0000000f teswa UNK1220 */
	xf_emit(ctx, 1, 0);		/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 000000ff teswa UNK1A20 */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 VEWTEX_TWO_SIDE_ENABWE */
	xf_emit(ctx, 4, 0xffff);	/* 0000ffff MSAA_MASK */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 3);	/* 00000003 teswa UNK1100 */
	if (device->chipset < 0xa0)
		xf_emit(ctx, 0x1c, 0);	/* WO */
	ewse if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x9, 0);
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000001 WINE_SMOOTH_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 WINE_STIPPWE_ENABWE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff WINE_STIPPWE_PATTEWN */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POWYGON_MODE */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_OWIGIN */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 3);	/* 00000003 teswa UNK1100 */
		xf_emit(ctx, 1, 0);	/* 3ff */
	}
	/* XXX: the fowwowing bwock couwd bewong eithew to unk1cxx, ow
	 * to STWMOUT. Wathew hawd to teww. */
	if (device->chipset < 0xa0)
		xf_emit(ctx, 0x25, 0);
	ewse
		xf_emit(ctx, 0x3b, 0);
}

static void
nv50_gw_constwuct_gene_stwmout(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	xf_emit(ctx, 1, 0x102);		/* 0000ffff STWMOUT_BUFFEW_CTWW */
	xf_emit(ctx, 1, 0);		/* ffffffff STWMOUT_PWIMITIVE_COUNT */
	xf_emit(ctx, 4, 4);		/* 000000ff STWMOUT_NUM_ATTWIBS */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1A8C */
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1780 */
	}
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);	/* 000003ff teswa UNK0D68 */
	ewse
		xf_emit(ctx, 1, 0x7ff);	/* 000007ff teswa UNK0D68 */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	/* SEEK */
	xf_emit(ctx, 1, 0x102);		/* 0000ffff STWMOUT_BUFFEW_CTWW */
	xf_emit(ctx, 1, 0);		/* ffffffff STWMOUT_PWIMITIVE_COUNT */
	xf_emit(ctx, 4, 0);		/* 000000ff STWMOUT_ADDWESS_HIGH */
	xf_emit(ctx, 4, 0);		/* ffffffff STWMOUT_ADDWESS_WOW */
	xf_emit(ctx, 4, 4);		/* 000000ff STWMOUT_NUM_ATTWIBS */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1A8C */
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1780 */
	}
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_STWMOUT */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_QUEWY */
	xf_emit(ctx, 1, 0);		/* 000000ff QUEWY_ADDWESS_HIGH */
	xf_emit(ctx, 2, 0);		/* ffffffff QUEWY_ADDWESS_WOW QUEWY_COUNTEW */
	xf_emit(ctx, 2, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	/* SEEK */
	xf_emit(ctx, 0x20, 0);		/* ffffffff STWMOUT_MAP */
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 0);		/* 00000000? */
	xf_emit(ctx, 2, 0);		/* ffffffff */
}

static void
nv50_gw_constwuct_gene_wopm1(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	xf_emit(ctx, 1, 0x4e3bfdf);	/* ffffffff UNK0D64 */
	xf_emit(ctx, 1, 0x4e3bfdf);	/* ffffffff UNK0DF4 */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* 000003ff */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0x11);	/* 000000ff teswa UNK1968 */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
}

static void
nv50_gw_constwuct_gene_wopm2(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_QUEWY */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 2, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 000000ff QUEWY_ADDWESS_HIGH */
	xf_emit(ctx, 2, 0);		/* ffffffff QUEWY_ADDWESS_WOW, COUNTEW */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPWECNT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 7 */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_QUEWY */
	xf_emit(ctx, 1, 0);		/* 000000ff QUEWY_ADDWESS_HIGH */
	xf_emit(ctx, 2, 0);		/* ffffffff QUEWY_ADDWESS_WOW, COUNTEW */
	xf_emit(ctx, 1, 0x4e3bfdf);	/* ffffffff UNK0D64 */
	xf_emit(ctx, 1, 0x4e3bfdf);	/* ffffffff UNK0DF4 */
	xf_emit(ctx, 1, 0);		/* 00000001 eng2d UNK260 */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0x11);	/* 000000ff teswa UNK1968 */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
}

static void
nv50_gw_constwuct_gene_wopc(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int magic2;
	if (device->chipset == 0x50) {
		magic2 = 0x00003e60;
	} ewse if (!IS_NVA3F(device->chipset)) {
		magic2 = 0x001ffe67;
	} ewse {
		magic2 = 0x00087e67;
	}
	xf_emit(ctx, 1, 0);		/* f/7 MUTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_BACK_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 1, 2);		/* 00000003 teswa UNK143C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, magic2);	/* 001fffff teswa UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_FWONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_FWONT_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	if (device->chipset >= 0xa0 && !IS_NVAAF(device->chipset))
		xf_emit(ctx, 1, 0x15);	/* 000000ff */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_BACK_ENABWE */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK15B4 */
	xf_emit(ctx, 1, 0x10);		/* 3ff/ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 1, 0);		/* ffffffff CWEAW_DEPTH */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	if (device->chipset == 0x86 || device->chipset == 0x92 || device->chipset == 0x98 || device->chipset >= 0xa0) {
		xf_emit(ctx, 3, 0);	/* ff, ffffffff, ffffffff */
		xf_emit(ctx, 1, 4);	/* 7 */
		xf_emit(ctx, 1, 0x400);	/* fffffff */
		xf_emit(ctx, 1, 0x300);	/* ffff */
		xf_emit(ctx, 1, 0x1001);	/* 1fff */
		if (device->chipset != 0xa0) {
			if (IS_NVA3F(device->chipset))
				xf_emit(ctx, 1, 0);	/* 0000000f UNK15C8 */
			ewse
				xf_emit(ctx, 1, 0x15);	/* ff */
		}
	}
	xf_emit(ctx, 1, 0);		/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 2);		/* 00000003 teswa UNK143C */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_FWONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_BACK_ENABWE */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK15B4 */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1900 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_WEF */
	xf_emit(ctx, 2, 0);		/* ffffffff DEPTH_BOUNDS */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_FWONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_WEF */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_BACK_ENABWE */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 0x10, 0);		/* ffffffff DEPTH_WANGE_NEAW */
	xf_emit(ctx, 0x10, 0x3f800000);	/* ffffffff DEPTH_WANGE_FAW */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 0);		/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_FUNC_WEF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_BACK_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 2, 0);		/* ffffffff DEPTH_BOUNDS */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 0);		/* 000000ff CWEAW_STENCIW */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIW_FWONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_FUNC_WEF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_FWONT_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_BACK_ENABWE */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff VIEW_VOWUME_CWIP_CTWW */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 0x3f);		/* 0000003f UNK1590 */
	xf_emit(ctx, 1, 0);		/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 2, 0);		/* ffff0ff3, ffff */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUIWTIN_WESUWT_EN */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff CWEAW_DEPTH */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK19CC */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 2, 0);
		xf_emit(ctx, 1, 0x1001);
		xf_emit(ctx, 0xb, 0);
	} ewse {
		xf_emit(ctx, 1, 0);	/* 00000007 */
		xf_emit(ctx, 1, 0);	/* 00000001 teswa UNK1534 */
		xf_emit(ctx, 1, 0);	/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
		xf_emit(ctx, 8, 0);	/* 00000001 BWEND_ENABWE */
		xf_emit(ctx, 1, 0);	/* ffff0ff3 */
	}
	xf_emit(ctx, 1, 0x11);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f */
	xf_emit(ctx, 1, 0);		/* 00000001 WOGIC_OP_ENABWE */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 0);	/* 0000000f WOGIC_OP */
		xf_emit(ctx, 1, 0);	/* 000000ff */
	}
	xf_emit(ctx, 1, 0);		/* 00000007 OPEWATION */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 2, 1);		/* 00000007 BWEND_EQUATION_WGB, AWPHA */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_WGB */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_WGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_AWPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_AWPHA */
	xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, magic2);	/* 001fffff teswa UNK0F78 */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* 00000001 teswa UNK12E4 */
		xf_emit(ctx, 8, 1);	/* 00000007 IBWEND_EQUATION_WGB */
		xf_emit(ctx, 8, 1);	/* 00000007 IBWEND_EQUATION_AWPHA */
		xf_emit(ctx, 8, 1);	/* 00000001 IBWEND_UNK00 */
		xf_emit(ctx, 8, 2);	/* 0000001f IBWEND_FUNC_SWC_WGB */
		xf_emit(ctx, 8, 1);	/* 0000001f IBWEND_FUNC_DST_WGB */
		xf_emit(ctx, 8, 2);	/* 0000001f IBWEND_FUNC_SWC_AWPHA */
		xf_emit(ctx, 8, 1);	/* 0000001f IBWEND_FUNC_DST_AWPHA */
		xf_emit(ctx, 1, 0);	/* 00000001 teswa UNK1140 */
		xf_emit(ctx, 2, 0);	/* 00000001 */
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
		xf_emit(ctx, 1, 0);	/* 0000000f */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* ffffffff */
		xf_emit(ctx, 2, 0);	/* 00000001 */
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
		xf_emit(ctx, 1, 0);	/* 00000001 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
	} ewse if (device->chipset >= 0xa0) {
		xf_emit(ctx, 2, 0);	/* 00000001 */
		xf_emit(ctx, 1, 0);	/* 00000007 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* ffffffff */
		xf_emit(ctx, 2, 0);	/* 00000001 */
	} ewse {
		xf_emit(ctx, 1, 0);	/* 00000007 MUWTISAMPWE_SAMPWES_WOG2 */
		xf_emit(ctx, 1, 0);	/* 00000003 teswa UNK1430 */
		xf_emit(ctx, 1, 0);	/* ffffffff teswa UNK1A3C */
	}
	xf_emit(ctx, 4, 0);		/* ffffffff CWEAW_COWOW */
	xf_emit(ctx, 4, 0);		/* ffffffff BWEND_COWOW A W G B */
	xf_emit(ctx, 1, 0);		/* 00000fff eng2d UNK2B0 */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 2, 0);	/* 00000001 */
	xf_emit(ctx, 1, 0);		/* 000003ff */
	xf_emit(ctx, 8, 0);		/* 00000001 BWEND_ENABWE */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_WGB */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_WGB */
	xf_emit(ctx, 1, 1);		/* 00000007 BWEND_EQUATION_WGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_AWPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_AWPHA */
	xf_emit(ctx, 1, 1);		/* 00000007 BWEND_EQUATION_AWPHA */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK19C0 */
	xf_emit(ctx, 1, 0);		/* 00000001 WOGIC_OP_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000000f WOGIC_OP */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0);	/* 00000001 UNK12E4? NVA3+ onwy? */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 8, 1);	/* 00000001 IBWEND_UNK00 */
		xf_emit(ctx, 8, 1);	/* 00000007 IBWEND_EQUATION_WGB */
		xf_emit(ctx, 8, 2);	/* 0000001f IBWEND_FUNC_SWC_WGB */
		xf_emit(ctx, 8, 1);	/* 0000001f IBWEND_FUNC_DST_WGB */
		xf_emit(ctx, 8, 1);	/* 00000007 IBWEND_EQUATION_AWPHA */
		xf_emit(ctx, 8, 2);	/* 0000001f IBWEND_FUNC_SWC_AWPHA */
		xf_emit(ctx, 8, 1);	/* 0000001f IBWEND_FUNC_DST_AWPHA */
		xf_emit(ctx, 1, 0);	/* 00000001 teswa UNK15C4 */
		xf_emit(ctx, 1, 0);	/* 00000001 */
		xf_emit(ctx, 1, 0);	/* 00000001 teswa UNK1140 */
	}
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_WINEAW */
	xf_emit(ctx, 1, 0);		/* 00000007 PATTEWN_COWOW_FOWMAT */
	xf_emit(ctx, 2, 0);		/* ffffffff PATTEWN_MONO_COWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 PATTEWN_MONO_FOWMAT */
	xf_emit(ctx, 2, 0);		/* ffffffff PATTEWN_MONO_BITMAP */
	xf_emit(ctx, 1, 0);		/* 00000003 PATTEWN_SEWECT */
	xf_emit(ctx, 1, 0);		/* 000000ff WOP */
	xf_emit(ctx, 1, 0);		/* ffffffff BETA1 */
	xf_emit(ctx, 1, 0);		/* ffffffff BETA4 */
	xf_emit(ctx, 1, 0);		/* 00000007 OPEWATION */
	xf_emit(ctx, 0x50, 0);		/* 10x ffffff, ffffff, ffffff, ffffff, 3 PATTEWN */
}

static void
nv50_gw_constwuct_xfew_unk84xx(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int magic3;
	switch (device->chipset) {
	case 0x50:
		magic3 = 0x1000;
		bweak;
	case 0x86:
	case 0x98:
	case 0xa8:
	case 0xaa:
	case 0xac:
	case 0xaf:
		magic3 = 0x1e00;
		bweak;
	defauwt:
		magic3 = 0;
	}
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 4);		/* 7f/ff[NVA0+] VP_WEG_AWWOC_WESUWT */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113[NVA0+] */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x1f, 0);	/* ffffffff */
	ewse if (device->chipset >= 0xa0)
		xf_emit(ctx, 0x0f, 0);	/* ffffffff */
	ewse
		xf_emit(ctx, 0x10, 0);	/* fffffff VP_WESUWT_MAP_1 up */
	xf_emit(ctx, 2, 0);		/* f/1f[NVA3], fffffff/ffffffff[NVA0+] */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WEG_AWWOC_WESUWT */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WESUWT_MAP_SIZE */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0x03020100);	/* ffffffff */
	ewse
		xf_emit(ctx, 1, 0x00608080);	/* fffffff VP_WESUWT_MAP_0 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 2, 0);		/* 111/113, 7f/ff */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WEG_AWWOC_WESUWT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VEWTEX_OUTPUT_COUNT */
	if (magic3)
		xf_emit(ctx, 1, magic3);	/* 00007fff teswa UNK141C */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	xf_emit(ctx, 0x1f, 0);		/* ffffffff GP_WESUWT_MAP_1 up */
	xf_emit(ctx, 1, 0);		/* 0000001f */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WEG_AWWOC_WESUWT */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VEWTEX_OUTPUT_COUNT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0x03020100);	/* ffffffff GP_WESUWT_MAP_0 */
	xf_emit(ctx, 1, 3);		/* 00000003 GP_OUTPUT_PWIMITIVE_TYPE */
	if (magic3)
		xf_emit(ctx, 1, magic3);	/* 7fff teswa UNK141C */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 PWOVOKING_VEWTEX_WAST */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 3);		/* 00000003 GP_OUTPUT_PWIMITIVE_TYPE */
	xf_emit(ctx, 1, 0);		/* 00000001 PWOVOKING_VEWTEX_WAST */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 00000003 teswa UNK13A0 */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_WEG_AWWOC_WESUWT */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	if (device->chipset == 0x94 || device->chipset == 0x96)
		xf_emit(ctx, 0x1020, 0);	/* 4 x (0x400 x 0xffffffff, ff, 0, 0, 0, 4 x ffffffff) */
	ewse if (device->chipset < 0xa0)
		xf_emit(ctx, 0xa20, 0);	/* 4 x (0x280 x 0xffffffff, ff, 0, 0, 0, 4 x ffffffff) */
	ewse if (!IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x210, 0);	/* ffffffff */
	ewse
		xf_emit(ctx, 0x410, 0);	/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_WESUWT_MAP_SIZE */
	xf_emit(ctx, 1, 3);		/* 00000003 GP_OUTPUT_PWIMITIVE_TYPE */
	xf_emit(ctx, 1, 0);		/* 00000001 PWOVOKING_VEWTEX_WAST */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
}

static void
nv50_gw_constwuct_xfew_tpwop(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int magic1, magic2;
	if (device->chipset == 0x50) {
		magic1 = 0x3ff;
		magic2 = 0x00003e60;
	} ewse if (!IS_NVA3F(device->chipset)) {
		magic1 = 0x7ff;
		magic2 = 0x001ffe67;
	} ewse {
		magic1 = 0x7ff;
		magic2 = 0x00087e67;
	}
	xf_emit(ctx, 1, 0);		/* 00000007 AWPHA_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* ffffffff AWPHA_TEST_WEF */
	xf_emit(ctx, 1, 0);		/* 00000001 AWPHA_TEST_ENABWE */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000000f UNK16A0 */
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_BACK_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 4, 0);		/* ffffffff BWEND_COWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK19C0 */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK0FDC */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 WOGIC_OP_ENABWE */
	xf_emit(ctx, 1, 0);		/* ff[NV50]/3ff[NV84+] */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTWOW */
	xf_emit(ctx, 4, 0xffff);	/* 0000ffff MSAA_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIW_FWONT_OP_FAIW, ZFAIW, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_BACK_ENABWE */
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK19CC */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPWECNT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff COWOW_KEY */
	xf_emit(ctx, 1, 0);		/* 00000001 COWOW_KEY_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000007 COWOW_KEY_FOWMAT */
	xf_emit(ctx, 2, 0);		/* ffffffff SIFC_BITMAP_COWOW */
	xf_emit(ctx, 1, 1);		/* 00000001 SIFC_BITMAP_WWITE_BIT0_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000007 AWPHA_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 AWPHA_TEST_ENABWE */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 3);	/* 00000003 teswa UNK16B4 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 00000003 teswa UNK1298 */
	} ewse if (device->chipset >= 0xa0) {
		xf_emit(ctx, 1, 1);	/* 00000001 teswa UNK16B4 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
	} ewse {
		xf_emit(ctx, 1, 0);	/* 00000003 MUWTISAMPWE_CTWW */
	}
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 8, 0);		/* 00000001 BWEND_ENABWE */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_AWPHA */
	xf_emit(ctx, 1, 1);		/* 00000007 BWEND_EQUATION_AWPHA */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_AWPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_WGB */
	xf_emit(ctx, 1, 1);		/* 00000007 BWEND_EQUATION_WGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_WGB */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* 00000001 UNK12E4 */
		xf_emit(ctx, 8, 1);	/* 00000007 IBWEND_EQUATION_WGB */
		xf_emit(ctx, 8, 1);	/* 00000007 IBWEND_EQUATION_AWPHA */
		xf_emit(ctx, 8, 1);	/* 00000001 IBWEND_UNK00 */
		xf_emit(ctx, 8, 2);	/* 0000001f IBWEND_SWC_WGB */
		xf_emit(ctx, 8, 1);	/* 0000001f IBWEND_DST_WGB */
		xf_emit(ctx, 8, 2);	/* 0000001f IBWEND_SWC_AWPHA */
		xf_emit(ctx, 8, 1);	/* 0000001f IBWEND_DST_AWPHA */
		xf_emit(ctx, 1, 0);	/* 00000001 UNK1140 */
	}
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 WOGIC_OP_ENABWE */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTWOW */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000001 FWAMEBUFFEW_SWGB */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_WINEAW */
	xf_emit(ctx, 1, 0);		/* 00000007 OPEWATION */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff SIFC_FOWMAT */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff DWAW_COWOW_FOWMAT */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff SWC_FOWMAT */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 7/f[NVA3] MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 8, 0);		/* 00000001 BWEND_ENABWE */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_AWPHA */
	xf_emit(ctx, 1, 1);		/* 00000007 BWEND_EQUATION_AWPHA */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_AWPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BWEND_FUNC_DST_WGB */
	xf_emit(ctx, 1, 1);		/* 00000007 BWEND_EQUATION_WGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BWEND_FUNC_SWC_WGB */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 8, 1);		/* 00000001 UNK19E0 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 1, magic2);	/* 001fffff teswa UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_WINEAW */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0);	/* ff */
	ewse
		xf_emit(ctx, 3, 0);	/* 1, 7, 3ff */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTWOW */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPWECNT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_WINEAW */
	xf_emit(ctx, 1, 0);		/* 000fffff BWIT_DU_DX_FWACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BWIT_DU_DX_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff BWIT_DV_DY_FWACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BWIT_DV_DY_INT */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, magic1);	/* 3ff/7ff teswa UNK0D68 */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
	xf_emit(ctx, 8, 0);		/* 0000ffff DMA_COWOW */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_GWOBAW */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_WOCAW */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_STACK */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_DST */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 8, 0);		/* 000000ff WT_ADDWESS_HIGH */
	xf_emit(ctx, 8, 0);		/* ffffffff WT_WAYEW_STWIDE */
	xf_emit(ctx, 8, 0);		/* ffffffff WT_ADDWESS_WOW */
	xf_emit(ctx, 8, 8);		/* 0000007f WT_TIWE_MODE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 8, 0x400);		/* 0fffffff WT_HOWIZ */
	xf_emit(ctx, 8, 0x300);		/* 0000ffff WT_VEWT */
	xf_emit(ctx, 1, 1);		/* 00001fff WT_AWWAY_MODE */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 1, 0x20);		/* 00000fff DST_TIWE_MODE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FOWMAT */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_HEIGHT */
	xf_emit(ctx, 1, 0);		/* 000007ff DST_WAYEW */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_WINEAW */
	xf_emit(ctx, 1, 0);		/* ffffffff DST_ADDWESS_WOW */
	xf_emit(ctx, 1, 0);		/* 000000ff DST_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0x40);		/* 0007ffff DST_PITCH */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_WIDTH */
	xf_emit(ctx, 1, 0);		/* 0000ffff */
	xf_emit(ctx, 1, 3);		/* 00000003 teswa UNK15AC */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUIWTIN_WESUWT_EN */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
	xf_emit(ctx, 1, magic2);	/* 001fffff teswa UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 2);		/* 00000003 teswa UNK143C */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_ZETA */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 2, 0);		/* ffff, ff/3ff */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUIWTIN_WESUWT_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIW_FWONT_MASK */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* ffffffff ZETA_WAYEW_STWIDE */
	xf_emit(ctx, 1, 0);		/* 000000ff ZETA_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff ZETA_ADDWESS_WOW */
	xf_emit(ctx, 1, 4);		/* 00000007 ZETA_TIWE_MODE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	xf_emit(ctx, 1, 0x400);		/* 0fffffff ZETA_HOWIZ */
	xf_emit(ctx, 1, 0x300);		/* 0000ffff ZETA_VEWT */
	xf_emit(ctx, 1, 0x1001);	/* 00001fff ZETA_AWWAY_MODE */
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0);	/* 00000001 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f WT_FOWMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COWOW_MASK */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 8, 0);		/* 00000001 BWEND_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000001 FWAMEBUFFEW_SWGB */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0);		/* 00000001 WOGIC_OP_ENABWE */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* 00000001 UNK1140 */
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
	}
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0x0fac6881);	/* fffffff */
	xf_emit(ctx, 1, magic2);	/* 001fffff teswa UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE_ENABWE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FOWMAT */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTWOW */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIW_FWONT_ENABWE */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK15B4 */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK19CC */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPWECNT_ENABWE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FOWMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABWE */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
		xf_emit(ctx, 1, 0);	/* 0000000f teswa UNK15C8 */
	}
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A3C */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 3, 0);		/* 7/f, 1, ffff0ff3 */
		xf_emit(ctx, 1, 0xfac6881);	/* fffffff */
		xf_emit(ctx, 4, 0);		/* 1, 1, 1, 3ff */
		xf_emit(ctx, 1, 4);		/* 7 */
		xf_emit(ctx, 1, 0);		/* 1 */
		xf_emit(ctx, 2, 1);		/* 1 */
		xf_emit(ctx, 2, 0);		/* 7, f */
		xf_emit(ctx, 1, 1);		/* 1 */
		xf_emit(ctx, 1, 0);		/* 7/f */
		if (IS_NVA3F(device->chipset))
			xf_emit(ctx, 0x9, 0);	/* 1 */
		ewse
			xf_emit(ctx, 0x8, 0);	/* 1 */
		xf_emit(ctx, 1, 0);		/* ffff0ff3 */
		xf_emit(ctx, 8, 1);		/* 1 */
		xf_emit(ctx, 1, 0x11);		/* 7f */
		xf_emit(ctx, 7, 0);		/* 7f */
		xf_emit(ctx, 1, 0xfac6881);	/* fffffff */
		xf_emit(ctx, 1, 0xf);		/* f */
		xf_emit(ctx, 7, 0);		/* f */
		xf_emit(ctx, 1, 0x11);		/* 7f */
		xf_emit(ctx, 1, 1);		/* 1 */
		xf_emit(ctx, 5, 0);		/* 1, 7, 3ff, 3, 7 */
		if (IS_NVA3F(device->chipset)) {
			xf_emit(ctx, 1, 0);	/* 00000001 UNK1140 */
			xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
		}
	}
}

static void
nv50_gw_constwuct_xfew_tex(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	xf_emit(ctx, 2, 0);		/* 1 WINKED_TSC. yes, 2. */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 3 */
	xf_emit(ctx, 1, 1);		/* 1ffff BWIT_DU_DX_INT */
	xf_emit(ctx, 1, 0);		/* fffff BWIT_DU_DX_FWACT */
	xf_emit(ctx, 1, 1);		/* 1ffff BWIT_DV_DY_INT */
	xf_emit(ctx, 1, 0);		/* fffff BWIT_DV_DY_FWACT */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0);	/* 3 BWIT_CONTWOW */
	ewse
		xf_emit(ctx, 2, 0);	/* 3ff, 1 */
	xf_emit(ctx, 1, 0x2a712488);	/* ffffffff SWC_TIC_0 */
	xf_emit(ctx, 1, 0);		/* ffffffff SWC_TIC_1 */
	xf_emit(ctx, 1, 0x4085c000);	/* ffffffff SWC_TIC_2 */
	xf_emit(ctx, 1, 0x40);		/* ffffffff SWC_TIC_3 */
	xf_emit(ctx, 1, 0x100);		/* ffffffff SWC_TIC_4 */
	xf_emit(ctx, 1, 0x10100);	/* ffffffff SWC_TIC_5 */
	xf_emit(ctx, 1, 0x02800000);	/* ffffffff SWC_TIC_6 */
	xf_emit(ctx, 1, 0);		/* ffffffff SWC_TIC_7 */
	if (device->chipset == 0x50) {
		xf_emit(ctx, 1, 0);	/* 00000001 tuwing UNK358 */
		xf_emit(ctx, 1, 0);	/* ffffffff teswa UNK1A34? */
		xf_emit(ctx, 1, 0);	/* 00000003 tuwing UNK37C teswa UNK1690 */
		xf_emit(ctx, 1, 0);	/* 00000003 BWIT_CONTWOW */
		xf_emit(ctx, 1, 0);	/* 00000001 tuwing UNK32C teswa UNK0F94 */
	} ewse if (!IS_NVAAF(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* ffffffff teswa UNK1A34? */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
		xf_emit(ctx, 1, 0);	/* 00000003 teswa UNK1664 / tuwing UNK03E8 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
	} ewse {
		xf_emit(ctx, 0x6, 0);
	}
	xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A34 */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_TEXTUWE */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_SWC */
}

static void
nv50_gw_constwuct_xfew_unk8cxx(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 2, 0);		/* 7, ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0D64 */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0DF4 */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 00000001 WINE_STIPPWE_ENABWE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff WINE_STIPPWE_PATTEWN */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK0F98 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f teswa UNK169C */
	xf_emit(ctx, 1, 0);		/* 00000003 teswa UNK1668 */
	xf_emit(ctx, 1, 0);		/* 00000001 WINE_STIPPWE_ENABWE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff WINE_STIPPWE_PATTEWN */
	xf_emit(ctx, 1, 0);		/* 00000001 POWYGON_SMOOTH_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 teswa UNK1658 */
	xf_emit(ctx, 1, 0);		/* 00000001 WINE_SMOOTH_ENABWE */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABWE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WWITE */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPWITE_ENABWE */
	xf_emit(ctx, 1, 1);		/* 00000001 teswa UNK165C */
	xf_emit(ctx, 1, 0x30201000);	/* ffffffff teswa UNK1670 */
	xf_emit(ctx, 1, 0x70605040);	/* ffffffff teswa UNK1670 */
	xf_emit(ctx, 1, 0xb8a89888);	/* ffffffff teswa UNK1670 */
	xf_emit(ctx, 1, 0xf8e8d8c8);	/* ffffffff teswa UNK1670 */
	xf_emit(ctx, 1, 0);		/* 00000001 VEWTEX_TWO_SIDE_ENABWE */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POWYGON_MODE */
}

static void
nv50_gw_constwuct_xfew_tp(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	if (device->chipset < 0xa0) {
		nv50_gw_constwuct_xfew_unk84xx(ctx);
		nv50_gw_constwuct_xfew_tpwop(ctx);
		nv50_gw_constwuct_xfew_tex(ctx);
		nv50_gw_constwuct_xfew_unk8cxx(ctx);
	} ewse {
		nv50_gw_constwuct_xfew_tex(ctx);
		nv50_gw_constwuct_xfew_tpwop(ctx);
		nv50_gw_constwuct_xfew_unk8cxx(ctx);
		nv50_gw_constwuct_xfew_unk84xx(ctx);
	}
}

static void
nv50_gw_constwuct_xfew_mpc(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i, mpcnt = 2;
	switch (device->chipset) {
		case 0x98:
		case 0xaa:
			mpcnt = 1;
			bweak;
		case 0x50:
		case 0x84:
		case 0x86:
		case 0x92:
		case 0x94:
		case 0x96:
		case 0xa8:
		case 0xac:
			mpcnt = 2;
			bweak;
		case 0xa0:
		case 0xa3:
		case 0xa5:
		case 0xaf:
			mpcnt = 3;
			bweak;
	}
	fow (i = 0; i < mpcnt; i++) {
		xf_emit(ctx, 1, 0);		/* ff */
		xf_emit(ctx, 1, 0x80);		/* ffffffff teswa UNK1404 */
		xf_emit(ctx, 1, 0x80007004);	/* ffffffff teswa UNK12B0 */
		xf_emit(ctx, 1, 0x04000400);	/* ffffffff */
		if (device->chipset >= 0xa0)
			xf_emit(ctx, 1, 0xc0);	/* 00007fff teswa UNK152C */
		xf_emit(ctx, 1, 0x1000);	/* 0000ffff teswa UNK0D60 */
		xf_emit(ctx, 1, 0);		/* ff/3ff */
		xf_emit(ctx, 1, 0);		/* ffffffff teswa UNK1A30 */
		if (device->chipset == 0x86 || device->chipset == 0x98 || device->chipset == 0xa8 || IS_NVAAF(device->chipset)) {
			xf_emit(ctx, 1, 0xe00);		/* 7fff */
			xf_emit(ctx, 1, 0x1e00);	/* 7fff */
		}
		xf_emit(ctx, 1, 1);		/* 000000ff VP_WEG_AWWOC_TEMP */
		xf_emit(ctx, 1, 0);		/* 00000001 WINKED_TSC */
		xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
		if (device->chipset == 0x50)
			xf_emit(ctx, 2, 0x1000);	/* 7fff teswa UNK141C */
		xf_emit(ctx, 1, 1);		/* 000000ff GP_WEG_AWWOC_TEMP */
		xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABWE */
		xf_emit(ctx, 1, 4);		/* 000000ff FP_WEG_AWWOC_TEMP */
		xf_emit(ctx, 1, 2);		/* 00000003 WEG_MODE */
		if (IS_NVAAF(device->chipset))
			xf_emit(ctx, 0xb, 0);	/* WO */
		ewse if (device->chipset >= 0xa0)
			xf_emit(ctx, 0xc, 0);	/* WO */
		ewse
			xf_emit(ctx, 0xa, 0);	/* WO */
	}
	xf_emit(ctx, 1, 0x08100c12);		/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 1, 0);			/* ff/3ff */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 1, 0x1fe21);	/* 0003ffff teswa UNK0FAC */
	}
	xf_emit(ctx, 3, 0);			/* 7fff, 0, 0 */
	xf_emit(ctx, 1, 0);			/* 00000001 teswa UNK1534 */
	xf_emit(ctx, 1, 0);			/* 7/f MUWTISAMPWE_SAMPWES_WOG2 */
	xf_emit(ctx, 4, 0xffff);		/* 0000ffff MSAA_MASK */
	xf_emit(ctx, 1, 1);			/* 00000001 WANES32 */
	xf_emit(ctx, 1, 0x10001);		/* 00ffffff BWOCK_AWWOC */
	xf_emit(ctx, 1, 0x10001);		/* ffffffff BWOCKDIM_XY */
	xf_emit(ctx, 1, 1);			/* 0000ffff BWOCKDIM_Z */
	xf_emit(ctx, 1, 0);			/* ffffffff SHAWED_SIZE */
	xf_emit(ctx, 1, 0x1fe21);		/* 1ffff/3ffff[NVA0+] teswa UNk0FAC */
	xf_emit(ctx, 1, 0);			/* ffffffff teswa UNK1A34 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);		/* 0000001f teswa UNK169C */
	xf_emit(ctx, 1, 0);			/* ff/3ff */
	xf_emit(ctx, 1, 0);			/* 1 WINKED_TSC */
	xf_emit(ctx, 1, 0);			/* ff FP_ADDWESS_HIGH */
	xf_emit(ctx, 1, 0);			/* ffffffff FP_ADDWESS_WOW */
	xf_emit(ctx, 1, 0x08100c12);		/* 1fffffff FP_INTEWPOWANT_CTWW */
	xf_emit(ctx, 1, 4);			/* 00000007 FP_CONTWOW */
	xf_emit(ctx, 1, 0);			/* 000000ff FWAG_COWOW_CWAMP_EN */
	xf_emit(ctx, 1, 2);			/* 00000003 WEG_MODE */
	xf_emit(ctx, 1, 0x11);			/* 0000007f WT_FOWMAT */
	xf_emit(ctx, 7, 0);			/* 0000007f WT_FOWMAT */
	xf_emit(ctx, 1, 0);			/* 00000007 */
	xf_emit(ctx, 1, 0xfac6881);		/* 0fffffff WT_CONTWOW */
	xf_emit(ctx, 1, 0);			/* 00000003 MUWTISAMPWE_CTWW */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 3);		/* 00000003 teswa UNK16B4 */
	xf_emit(ctx, 1, 0);			/* 00000001 AWPHA_TEST_ENABWE */
	xf_emit(ctx, 1, 0);			/* 00000007 AWPHA_TEST_FUNC */
	xf_emit(ctx, 1, 0);			/* 00000001 FWAMEBUFFEW_SWGB */
	xf_emit(ctx, 1, 4);			/* ffffffff teswa UNK1400 */
	xf_emit(ctx, 8, 0);			/* 00000001 BWEND_ENABWE */
	xf_emit(ctx, 1, 0);			/* 00000001 WOGIC_OP_ENABWE */
	xf_emit(ctx, 1, 2);			/* 0000001f BWEND_FUNC_SWC_WGB */
	xf_emit(ctx, 1, 1);			/* 0000001f BWEND_FUNC_DST_WGB */
	xf_emit(ctx, 1, 1);			/* 00000007 BWEND_EQUATION_WGB */
	xf_emit(ctx, 1, 2);			/* 0000001f BWEND_FUNC_SWC_AWPHA */
	xf_emit(ctx, 1, 1);			/* 0000001f BWEND_FUNC_DST_AWPHA */
	xf_emit(ctx, 1, 1);			/* 00000007 BWEND_EQUATION_AWPHA */
	xf_emit(ctx, 1, 1);			/* 00000001 UNK133C */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);		/* 00000001 UNK12E4 */
		xf_emit(ctx, 8, 2);		/* 0000001f IBWEND_FUNC_SWC_WGB */
		xf_emit(ctx, 8, 1);		/* 0000001f IBWEND_FUNC_DST_WGB */
		xf_emit(ctx, 8, 1);		/* 00000007 IBWEND_EQUATION_WGB */
		xf_emit(ctx, 8, 2);		/* 0000001f IBWEND_FUNC_SWC_AWPHA */
		xf_emit(ctx, 8, 1);		/* 0000001f IBWEND_FUNC_DST_AWPHA */
		xf_emit(ctx, 8, 1);		/* 00000007 IBWEND_EQUATION_AWPHA */
		xf_emit(ctx, 8, 1);		/* 00000001 IBWEND_UNK00 */
		xf_emit(ctx, 1, 0);		/* 00000003 teswa UNK1928 */
		xf_emit(ctx, 1, 0);		/* 00000001 UNK1140 */
	}
	xf_emit(ctx, 1, 0);			/* 00000003 teswa UNK0F90 */
	xf_emit(ctx, 1, 4);			/* 000000ff FP_WESUWT_COUNT */
	/* XXX: demagic this pawt some day */
	if (device->chipset == 0x50)
		xf_emit(ctx, 0x3a0, 0);
	ewse if (device->chipset < 0x94)
		xf_emit(ctx, 0x3a2, 0);
	ewse if (device->chipset == 0x98 || device->chipset == 0xaa)
		xf_emit(ctx, 0x39f, 0);
	ewse
		xf_emit(ctx, 0x3a3, 0);
	xf_emit(ctx, 1, 0x11);			/* 3f/7f DST_FOWMAT */
	xf_emit(ctx, 1, 0);			/* 7 OPEWATION */
	xf_emit(ctx, 1, 1);			/* 1 DST_WINEAW */
	xf_emit(ctx, 0x2d, 0);
}

static void
nv50_gw_constwuct_xfew2(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i;
	u32 offset;
	u32 units = nvkm_wd32(device, 0x1540);
	int size = 0;

	offset = (ctx->ctxvaws_pos+0x3f)&~0x3f;

	if (device->chipset < 0xa0) {
		fow (i = 0; i < 8; i++) {
			ctx->ctxvaws_pos = offset + i;
			/* that wittwe buggew bewongs to csched. No idea
			 * what it's doing hewe. */
			if (i == 0)
				xf_emit(ctx, 1, 0x08100c12); /* FP_INTEWPOWANT_CTWW */
			if (units & (1 << i))
				nv50_gw_constwuct_xfew_mpc(ctx);
			if ((ctx->ctxvaws_pos-offset)/8 > size)
				size = (ctx->ctxvaws_pos-offset)/8;
		}
	} ewse {
		/* Stwand 0: TPs 0, 1 */
		ctx->ctxvaws_pos = offset;
		/* that wittwe buggew bewongs to csched. No idea
		 * what it's doing hewe. */
		xf_emit(ctx, 1, 0x08100c12); /* FP_INTEWPOWANT_CTWW */
		if (units & (1 << 0))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if (units & (1 << 1))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 1: TPs 2, 3 */
		ctx->ctxvaws_pos = offset + 1;
		if (units & (1 << 2))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if (units & (1 << 3))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 2: TPs 4, 5, 6 */
		ctx->ctxvaws_pos = offset + 2;
		if (units & (1 << 4))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if (units & (1 << 5))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if (units & (1 << 6))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;

		/* Stwand 3: TPs 7, 8, 9 */
		ctx->ctxvaws_pos = offset + 3;
		if (units & (1 << 7))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if (units & (1 << 8))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if (units & (1 << 9))
			nv50_gw_constwuct_xfew_mpc(ctx);
		if ((ctx->ctxvaws_pos-offset)/8 > size)
			size = (ctx->ctxvaws_pos-offset)/8;
	}
	ctx->ctxvaws_pos = offset + size * 8;
	ctx->ctxvaws_pos = (ctx->ctxvaws_pos+0x3f)&~0x3f;
	cp_wsw (ctx, offset);
	cp_out (ctx, CP_SET_XFEW_POINTEW);
	cp_wsw (ctx, size);
	cp_out (ctx, CP_SEEK_2);
	cp_out (ctx, CP_XFEW_2);
	cp_wait(ctx, XFEW, BUSY);
}
