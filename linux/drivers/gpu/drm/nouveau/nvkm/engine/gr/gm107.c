/*
 * Copywight 2013 Wed Hat Inc.
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
#incwude "gf100.h"
#incwude "ctxgf100.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/P0260.h>
#incwude <subdev/fb.h>

#incwude <nvif/cwass.h>

/*******************************************************************************
 * PGWAPH wegistew wists
 ******************************************************************************/

static const stwuct gf100_gw_init
gm107_gw_init_main_0[] = {
	{ 0x40880c,   1, 0x04, 0x00000000 },
	{ 0x408910,   1, 0x04, 0x00000000 },
	{ 0x408984,   1, 0x04, 0x00000000 },
	{ 0x41a8a0,   1, 0x04, 0x00000000 },
	{ 0x400080,   1, 0x04, 0x003003c2 },
	{ 0x400088,   1, 0x04, 0x0001bfe7 },
	{ 0x40008c,   1, 0x04, 0x00060000 },
	{ 0x400090,   1, 0x04, 0x00000030 },
	{ 0x40013c,   1, 0x04, 0x003901f3 },
	{ 0x400140,   1, 0x04, 0x00000100 },
	{ 0x400144,   1, 0x04, 0x00000000 },
	{ 0x400148,   1, 0x04, 0x00000110 },
	{ 0x400138,   1, 0x04, 0x00000000 },
	{ 0x400130,   2, 0x04, 0x00000000 },
	{ 0x400124,   1, 0x04, 0x00000002 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_ds_0[] = {
	{ 0x405844,   1, 0x04, 0x00ffffff },
	{ 0x405850,   1, 0x04, 0x00000000 },
	{ 0x405900,   1, 0x04, 0x00000000 },
	{ 0x405908,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_scc_0[] = {
	{ 0x40803c,   1, 0x04, 0x00000010 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_sked_0[] = {
	{ 0x407010,   1, 0x04, 0x00000000 },
	{ 0x407040,   1, 0x04, 0x40440424 },
	{ 0x407048,   1, 0x04, 0x0000000a },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_pwop_0[] = {
	{ 0x418408,   1, 0x04, 0x00000000 },
	{ 0x4184a0,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_setup_1[] = {
	{ 0x4188c8,   2, 0x04, 0x00000000 },
	{ 0x4188d0,   1, 0x04, 0x00010000 },
	{ 0x4188d4,   1, 0x04, 0x00010201 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_zcuww_0[] = {
	{ 0x418910,   1, 0x04, 0x00010001 },
	{ 0x418914,   1, 0x04, 0x00000301 },
	{ 0x418918,   1, 0x04, 0x00800000 },
	{ 0x418930,   2, 0x04, 0x00000000 },
	{ 0x418980,   1, 0x04, 0x77777770 },
	{ 0x418984,   3, 0x04, 0x77777777 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_gpc_unk_1[] = {
	{ 0x418d00,   1, 0x04, 0x00000000 },
	{ 0x418f00,   1, 0x04, 0x00000400 },
	{ 0x418f08,   1, 0x04, 0x00000000 },
	{ 0x418e08,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_tpccs_0[] = {
	{ 0x419dc4,   1, 0x04, 0x00000000 },
	{ 0x419dc8,   1, 0x04, 0x00000501 },
	{ 0x419dd0,   1, 0x04, 0x00000000 },
	{ 0x419dd4,   1, 0x04, 0x00000100 },
	{ 0x419dd8,   1, 0x04, 0x00000001 },
	{ 0x419ddc,   1, 0x04, 0x00000002 },
	{ 0x419de0,   1, 0x04, 0x00000001 },
	{ 0x419d0c,   1, 0x04, 0x00000000 },
	{ 0x419d10,   1, 0x04, 0x00000014 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_tex_0[] = {
	{ 0x419ab0,   1, 0x04, 0x00000000 },
	{ 0x419ab8,   1, 0x04, 0x000000e7 },
	{ 0x419abc,   1, 0x04, 0x00000000 },
	{ 0x419acc,   1, 0x04, 0x000000ff },
	{ 0x419ac0,   1, 0x04, 0x00000000 },
	{ 0x419aa8,   2, 0x04, 0x00000000 },
	{ 0x419ad0,   2, 0x04, 0x00000000 },
	{ 0x419ae0,   2, 0x04, 0x00000000 },
	{ 0x419af0,   4, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_pe_0[] = {
	{ 0x419900,   1, 0x04, 0x000000ff },
	{ 0x41980c,   1, 0x04, 0x00000010 },
	{ 0x419844,   1, 0x04, 0x00000000 },
	{ 0x419838,   1, 0x04, 0x000000ff },
	{ 0x419850,   1, 0x04, 0x00000004 },
	{ 0x419854,   2, 0x04, 0x00000000 },
	{ 0x419894,   3, 0x04, 0x00100401 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_w1c_0[] = {
	{ 0x419c98,   1, 0x04, 0x00000000 },
	{ 0x419cc0,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_sm_0[] = {
	{ 0x419e30,   1, 0x04, 0x000000ff },
	{ 0x419e00,   1, 0x04, 0x00000000 },
	{ 0x419ea0,   1, 0x04, 0x00000000 },
	{ 0x419ee4,   1, 0x04, 0x00000000 },
	{ 0x419ea4,   1, 0x04, 0x00000100 },
	{ 0x419ea8,   1, 0x04, 0x01000000 },
	{ 0x419ee8,   1, 0x04, 0x00000091 },
	{ 0x419eb4,   1, 0x04, 0x00000000 },
	{ 0x419ebc,   2, 0x04, 0x00000000 },
	{ 0x419edc,   1, 0x04, 0x000c1810 },
	{ 0x419ed8,   1, 0x04, 0x00000000 },
	{ 0x419ee0,   1, 0x04, 0x00000000 },
	{ 0x419f74,   1, 0x04, 0x00005155 },
	{ 0x419f80,   4, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_w1c_1[] = {
	{ 0x419ccc,   2, 0x04, 0x00000000 },
	{ 0x419c80,   1, 0x04, 0x3f006022 },
	{ 0x419c88,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_pes_0[] = {
	{ 0x41be50,   1, 0x04, 0x000000ff },
	{ 0x41be04,   1, 0x04, 0x00000000 },
	{ 0x41be08,   1, 0x04, 0x00000004 },
	{ 0x41be0c,   1, 0x04, 0x00000008 },
	{ 0x41be10,   1, 0x04, 0x0e3b8bc7 },
	{ 0x41be14,   2, 0x04, 0x00000000 },
	{ 0x41be3c,   5, 0x04, 0x00100401 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_wwdx_0[] = {
	{ 0x41bfd4,   1, 0x04, 0x00800000 },
	{ 0x41bfdc,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gm107_gw_init_cbm_0[] = {
	{ 0x41becc,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_be_0[] = {
	{ 0x408890,   1, 0x04, 0x000000ff },
	{ 0x408850,   1, 0x04, 0x00000004 },
	{ 0x408878,   1, 0x04, 0x00c81603 },
	{ 0x40887c,   1, 0x04, 0x80543432 },
	{ 0x408880,   1, 0x04, 0x0010581e },
	{ 0x408884,   1, 0x04, 0x00001205 },
	{ 0x408974,   1, 0x04, 0x000000ff },
	{ 0x408914,   8, 0x04, 0x00000000 },
	{ 0x408950,   1, 0x04, 0x00000000 },
	{ 0x408954,   1, 0x04, 0x0000ffff },
	{ 0x408958,   1, 0x04, 0x00000034 },
	{ 0x40895c,   1, 0x04, 0x8531a003 },
	{ 0x408960,   1, 0x04, 0x0561985a },
	{ 0x408964,   1, 0x04, 0x04e15c4f },
	{ 0x408968,   1, 0x04, 0x02808833 },
	{ 0x40896c,   1, 0x04, 0x01f02438 },
	{ 0x408970,   1, 0x04, 0x00012c00 },
	{ 0x408988,   1, 0x04, 0x08040201 },
	{ 0x40898c,   1, 0x04, 0x80402010 },
	{}
};

static const stwuct gf100_gw_init
gm107_gw_init_sm_1[] = {
	{ 0x419e5c,   1, 0x04, 0x00000000 },
	{ 0x419e58,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_pack
gm107_gw_pack_mmio[] = {
	{ gm107_gw_init_main_0 },
	{ gk110_gw_init_fe_0 },
	{ gf100_gw_init_pwi_0 },
	{ gf100_gw_init_wstw2d_0 },
	{ gf100_gw_init_pd_0 },
	{ gm107_gw_init_ds_0 },
	{ gm107_gw_init_scc_0 },
	{ gm107_gw_init_sked_0 },
	{ gk110_gw_init_cwd_0 },
	{ gm107_gw_init_pwop_0 },
	{ gk208_gw_init_gpc_unk_0 },
	{ gf100_gw_init_setup_0 },
	{ gf100_gw_init_cwstw_0 },
	{ gm107_gw_init_setup_1 },
	{ gm107_gw_init_zcuww_0 },
	{ gf100_gw_init_gpm_0 },
	{ gm107_gw_init_gpc_unk_1 },
	{ gf100_gw_init_gcc_0 },
	{ gk104_gw_init_gpc_unk_2 },
	{ gm107_gw_init_tpccs_0 },
	{ gm107_gw_init_tex_0 },
	{ gm107_gw_init_pe_0 },
	{ gm107_gw_init_w1c_0 },
	{ gf100_gw_init_mpc_0 },
	{ gm107_gw_init_sm_0 },
	{ gm107_gw_init_w1c_1 },
	{ gm107_gw_init_pes_0 },
	{ gm107_gw_init_wwdx_0 },
	{ gm107_gw_init_cbm_0 },
	{ gm107_gw_init_be_0 },
	{ gm107_gw_init_sm_1 },
	{}
};

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

void
gm107_gw_init_400054(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x400054, 0x2c350f63);
}

void
gm107_gw_init_shadew_exceptions(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x644), 0x00dffffe);
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x64c), 0x00000005);
}

void
gm107_gw_init_504430(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x430), 0xc0000000);
}

static void
gm107_gw_init_bios_2(stwuct gf100_gw *gw)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct bit_entwy bit_P;
	if (!bit_entwy(bios, 'P', &bit_P) &&
	    bit_P.vewsion == 2 && bit_P.wength >= 0x2c) {
		u32 data = nvbios_wd32(bios, bit_P.offset + 0x28);
		if (data) {
			u8 vew = nvbios_wd08(bios, data + 0x00);
			u8 hdw = nvbios_wd08(bios, data + 0x01);
			if (vew == 0x20 && hdw >= 8) {
				data = nvbios_wd32(bios, data + 0x04);
				if (data) {
					u32 save = nvkm_wd32(device, 0x619444);
					nvbios_init(subdev, data);
					nvkm_ww32(device, 0x619444, save);
				}
			}
		}
	}
}

void
gm107_gw_init_bios(stwuct gf100_gw *gw)
{
	static const stwuct {
		u32 ctww;
		u32 data;
	} wegs[] = {
		{ 0x419ed8, 0x419ee0 },
		{ 0x419ad0, 0x419ad4 },
		{ 0x419ae0, 0x419ae4 },
		{ 0x419af0, 0x419af4 },
		{ 0x419af8, 0x419afc },
	};
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvbios_P0260E infoE;
	stwuct nvbios_P0260X infoX;
	int E = -1, X;
	u8 vew, hdw;

	whiwe (nvbios_P0260Ep(bios, ++E, &vew, &hdw, &infoE)) {
		if (X = -1, E < AWWAY_SIZE(wegs)) {
			nvkm_ww32(device, wegs[E].ctww, infoE.data);
			whiwe (nvbios_P0260Xp(bios, ++X, &vew, &hdw, &infoX))
				nvkm_ww32(device, wegs[E].data, infoX.data);
		}
	}
}

static void
gm107_gw_init_gpc_mmu(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nvkm_fb *fb = device->fb;

	nvkm_ww32(device, GPC_BCAST(0x0880), 0x00000000);
	nvkm_ww32(device, GPC_BCAST(0x0890), 0x00000000);
	nvkm_ww32(device, GPC_BCAST(0x0894), 0x00000000);
	nvkm_ww32(device, GPC_BCAST(0x08b4), nvkm_memowy_addw(fb->mmu_ww) >> 8);
	nvkm_ww32(device, GPC_BCAST(0x08b8), nvkm_memowy_addw(fb->mmu_wd) >> 8);
}

#incwude "fuc/hubgm107.fuc5.h"

static stwuct gf100_gw_ucode
gm107_gw_fecs_ucode = {
	.code.data = gm107_gwhub_code,
	.code.size = sizeof(gm107_gwhub_code),
	.data.data = gm107_gwhub_data,
	.data.size = sizeof(gm107_gwhub_data),
};

#incwude "fuc/gpcgm107.fuc5.h"

static stwuct gf100_gw_ucode
gm107_gw_gpccs_ucode = {
	.code.data = gm107_gwgpc_code,
	.code.size = sizeof(gm107_gwgpc_code),
	.data.data = gm107_gwgpc_data,
	.data.size = sizeof(gm107_gwgpc_data),
};

static const stwuct gf100_gw_func
gm107_gw = {
	.oneinit_tiwes = gf100_gw_oneinit_tiwes,
	.oneinit_sm_id = gf100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gm107_gw_init_gpc_mmu,
	.init_bios = gm107_gw_init_bios,
	.init_vsc_stweam_mastew = gk104_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_num_active_wtcs = gf100_gw_init_num_active_wtcs,
	.init_wop_active_fbps = gk104_gw_init_wop_active_fbps,
	.init_bios_2 = gm107_gw_init_bios_2,
	.init_fecs_exceptions = gf100_gw_init_fecs_exceptions,
	.init_sked_hww_esw = gk104_gw_init_sked_hww_esw,
	.init_419cc0 = gf100_gw_init_419cc0,
	.init_ppc_exceptions = gk104_gw_init_ppc_exceptions,
	.init_tex_hww_esw = gf100_gw_init_tex_hww_esw,
	.init_504430 = gm107_gw_init_504430,
	.init_shadew_exceptions = gm107_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.init_400054 = gm107_gw_init_400054,
	.twap_mp = gf100_gw_twap_mp,
	.mmio = gm107_gw_pack_mmio,
	.fecs.ucode = &gm107_gw_fecs_ucode,
	.fecs.weset = gf100_gw_fecs_weset,
	.gpccs.ucode = &gm107_gw_gpccs_ucode,
	.wops = gf100_gw_wops,
	.ppc_nw = 2,
	.gwctx = &gm107_gwctx,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, MAXWEWW_A, &gf100_fewmi },
		{ -1, -1, MAXWEWW_COMPUTE_A },
		{}
	}
};

static const stwuct gf100_gw_fwif
gm107_gw_fwif[] = {
	{ -1, gf100_gw_woad, &gm107_gw },
	{ -1, gf100_gw_nofw, &gm107_gw },
	{}
};

int
gm107_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gm107_gw_fwif, device, type, inst, pgw);
}
