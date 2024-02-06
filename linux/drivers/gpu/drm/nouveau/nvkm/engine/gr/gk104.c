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
#incwude "gk104.h"
#incwude "ctxgf100.h"

#incwude <nvif/cwass.h>

/*******************************************************************************
 * PGWAPH wegistew wists
 ******************************************************************************/

const stwuct gf100_gw_init
gk104_gw_init_main_0[] = {
	{ 0x400080,   1, 0x04, 0x003083c2 },
	{ 0x400088,   1, 0x04, 0x0001ffe7 },
	{ 0x40008c,   1, 0x04, 0x00000000 },
	{ 0x400090,   1, 0x04, 0x00000030 },
	{ 0x40013c,   1, 0x04, 0x003901f7 },
	{ 0x400140,   1, 0x04, 0x00000100 },
	{ 0x400144,   1, 0x04, 0x00000000 },
	{ 0x400148,   1, 0x04, 0x00000110 },
	{ 0x400138,   1, 0x04, 0x00000000 },
	{ 0x400130,   2, 0x04, 0x00000000 },
	{ 0x400124,   1, 0x04, 0x00000002 },
	{}
};

static const stwuct gf100_gw_init
gk104_gw_init_ds_0[] = {
	{ 0x405844,   1, 0x04, 0x00ffffff },
	{ 0x405850,   1, 0x04, 0x00000000 },
	{ 0x405900,   1, 0x04, 0x0000ff34 },
	{ 0x405908,   1, 0x04, 0x00000000 },
	{ 0x405928,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gk104_gw_init_sked_0[] = {
	{ 0x407010,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gk104_gw_init_cwd_0[] = {
	{ 0x405b50,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gk104_gw_init_gpc_unk_1[] = {
	{ 0x418d00,   1, 0x04, 0x00000000 },
	{ 0x418d28,   2, 0x04, 0x00000000 },
	{ 0x418f00,   1, 0x04, 0x00000000 },
	{ 0x418f08,   1, 0x04, 0x00000000 },
	{ 0x418f20,   2, 0x04, 0x00000000 },
	{ 0x418e00,   1, 0x04, 0x00000060 },
	{ 0x418e08,   1, 0x04, 0x00000000 },
	{ 0x418e1c,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk104_gw_init_gpc_unk_2[] = {
	{ 0x418884,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk104_gw_init_tpccs_0[] = {
	{ 0x419d0c,   1, 0x04, 0x00000000 },
	{ 0x419d10,   1, 0x04, 0x00000014 },
	{}
};

const stwuct gf100_gw_init
gk104_gw_init_pe_0[] = {
	{ 0x41980c,   1, 0x04, 0x00000010 },
	{ 0x419844,   1, 0x04, 0x00000000 },
	{ 0x419850,   1, 0x04, 0x00000004 },
	{ 0x419854,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gk104_gw_init_w1c_0[] = {
	{ 0x419c98,   1, 0x04, 0x00000000 },
	{ 0x419ca8,   1, 0x04, 0x00000000 },
	{ 0x419cb0,   1, 0x04, 0x01000000 },
	{ 0x419cb4,   1, 0x04, 0x00000000 },
	{ 0x419cb8,   1, 0x04, 0x00b08bea },
	{ 0x419c84,   1, 0x04, 0x00010384 },
	{ 0x419cbc,   1, 0x04, 0x28137646 },
	{ 0x419cc0,   2, 0x04, 0x00000000 },
	{ 0x419c80,   1, 0x04, 0x00020232 },
	{}
};

static const stwuct gf100_gw_init
gk104_gw_init_sm_0[] = {
	{ 0x419e00,   1, 0x04, 0x00000000 },
	{ 0x419ea0,   1, 0x04, 0x00000000 },
	{ 0x419ee4,   1, 0x04, 0x00000000 },
	{ 0x419ea4,   1, 0x04, 0x00000100 },
	{ 0x419ea8,   1, 0x04, 0x00000000 },
	{ 0x419eb4,   4, 0x04, 0x00000000 },
	{ 0x419edc,   1, 0x04, 0x00000000 },
	{ 0x419f00,   1, 0x04, 0x00000000 },
	{ 0x419f74,   1, 0x04, 0x00000555 },
	{}
};

const stwuct gf100_gw_init
gk104_gw_init_be_0[] = {
	{ 0x40880c,   1, 0x04, 0x00000000 },
	{ 0x408850,   1, 0x04, 0x00000004 },
	{ 0x408910,   9, 0x04, 0x00000000 },
	{ 0x408950,   1, 0x04, 0x00000000 },
	{ 0x408954,   1, 0x04, 0x0000ffff },
	{ 0x408958,   1, 0x04, 0x00000034 },
	{ 0x408984,   1, 0x04, 0x00000000 },
	{ 0x408988,   1, 0x04, 0x08040201 },
	{ 0x40898c,   1, 0x04, 0x80402010 },
	{}
};

const stwuct gf100_gw_pack
gk104_gw_pack_mmio[] = {
	{ gk104_gw_init_main_0 },
	{ gf100_gw_init_fe_0 },
	{ gf100_gw_init_pwi_0 },
	{ gf100_gw_init_wstw2d_0 },
	{ gf119_gw_init_pd_0 },
	{ gk104_gw_init_ds_0 },
	{ gf100_gw_init_scc_0 },
	{ gk104_gw_init_sked_0 },
	{ gk104_gw_init_cwd_0 },
	{ gf119_gw_init_pwop_0 },
	{ gf108_gw_init_gpc_unk_0 },
	{ gf100_gw_init_setup_0 },
	{ gf100_gw_init_cwstw_0 },
	{ gf108_gw_init_setup_1 },
	{ gf100_gw_init_zcuww_0 },
	{ gf119_gw_init_gpm_0 },
	{ gk104_gw_init_gpc_unk_1 },
	{ gf100_gw_init_gcc_0 },
	{ gk104_gw_init_gpc_unk_2 },
	{ gk104_gw_init_tpccs_0 },
	{ gf119_gw_init_tex_0 },
	{ gk104_gw_init_pe_0 },
	{ gk104_gw_init_w1c_0 },
	{ gf100_gw_init_mpc_0 },
	{ gk104_gw_init_sm_0 },
	{ gf117_gw_init_pes_0 },
	{ gf117_gw_init_wwdx_0 },
	{ gf117_gw_init_cbm_0 },
	{ gk104_gw_init_be_0 },
	{ gf100_gw_init_fe_1 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_main_0[] = {
	{ 0x4041f0, 1, 0x00004046 },
	{ 0x409890, 1, 0x00000045 },
	{ 0x4098b0, 1, 0x0000007f },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_wstw2d_0[] = {
	{ 0x4078c0, 1, 0x00000042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_unk_0[] = {
	{ 0x406000, 1, 0x00004044 },
	{ 0x405860, 1, 0x00004042 },
	{ 0x40590c, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gcc_0[] = {
	{ 0x408040, 1, 0x00004044 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_sked_0[] = {
	{ 0x407000, 1, 0x00004044 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_unk_1[] = {
	{ 0x405bf0, 1, 0x00004044 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_ctxctw_0[] = {
	{ 0x41a890, 1, 0x00000042 },
	{ 0x41a8b0, 1, 0x0000007f },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_unk_0[] = {
	{ 0x418500, 1, 0x00004042 },
	{ 0x418608, 1, 0x00004042 },
	{ 0x418688, 1, 0x00004042 },
	{ 0x418718, 1, 0x00000042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_esetup_0[] = {
	{ 0x418828, 1, 0x00000044 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_tpbus_0[] = {
	{ 0x418bbc, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_zcuww_0[] = {
	{ 0x418970, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_tpconf_0[] = {
	{ 0x418c70, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_unk_1[] = {
	{ 0x418cf0, 1, 0x00004042 },
	{ 0x418d70, 1, 0x00004042 },
	{ 0x418f0c, 1, 0x00004042 },
	{ 0x418e0c, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_gcc_0[] = {
	{ 0x419020, 1, 0x00004042 },
	{ 0x419038, 1, 0x00000042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_ffb_0[] = {
	{ 0x418898, 1, 0x00000042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_tex_0[] = {
	{ 0x419a40, 9, 0x00004042 },
	{ 0x419acc, 1, 0x00004047 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_powy_0[] = {
	{ 0x419868, 1, 0x00000042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_w1c_0[] = {
	{ 0x419ccc, 3, 0x00000042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_unk_2[] = {
	{ 0x419c70, 1, 0x00004045 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_mp_0[] = {
	{ 0x419fd0, 1, 0x00004043 },
	{ 0x419fd8, 1, 0x00004049 },
	{ 0x419fe0, 2, 0x00004042 },
	{ 0x419ff0, 1, 0x00004046 },
	{ 0x419ff8, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_gpc_ppc_0[] = {
	{ 0x41be28, 1, 0x00000042 },
	{ 0x41bfe8, 1, 0x00004042 },
	{ 0x41bed0, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_wop_zwop_0[] = {
	{ 0x408810, 2, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_wop_0[] = {
	{ 0x408a80, 6, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_wop_cwop_0[] = {
	{ 0x4089a8, 1, 0x00004042 },
	{ 0x4089b0, 1, 0x00000042 },
	{ 0x4089b8, 1, 0x00004042 },
	{}
};

const stwuct nvkm_thewm_cwkgate_init
gk104_cwkgate_bwcg_init_pxbaw_0[] = {
	{ 0x13c820, 1, 0x0001007f },
	{ 0x13cbe0, 1, 0x00000042 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_pack
gk104_cwkgate_pack[] = {
	{ gk104_cwkgate_bwcg_init_main_0 },
	{ gk104_cwkgate_bwcg_init_wstw2d_0 },
	{ gk104_cwkgate_bwcg_init_unk_0 },
	{ gk104_cwkgate_bwcg_init_gcc_0 },
	{ gk104_cwkgate_bwcg_init_sked_0 },
	{ gk104_cwkgate_bwcg_init_unk_1 },
	{ gk104_cwkgate_bwcg_init_gpc_ctxctw_0 },
	{ gk104_cwkgate_bwcg_init_gpc_unk_0 },
	{ gk104_cwkgate_bwcg_init_gpc_esetup_0 },
	{ gk104_cwkgate_bwcg_init_gpc_tpbus_0 },
	{ gk104_cwkgate_bwcg_init_gpc_zcuww_0 },
	{ gk104_cwkgate_bwcg_init_gpc_tpconf_0 },
	{ gk104_cwkgate_bwcg_init_gpc_unk_1 },
	{ gk104_cwkgate_bwcg_init_gpc_gcc_0 },
	{ gk104_cwkgate_bwcg_init_gpc_ffb_0 },
	{ gk104_cwkgate_bwcg_init_gpc_tex_0 },
	{ gk104_cwkgate_bwcg_init_gpc_powy_0 },
	{ gk104_cwkgate_bwcg_init_gpc_w1c_0 },
	{ gk104_cwkgate_bwcg_init_gpc_unk_2 },
	{ gk104_cwkgate_bwcg_init_gpc_mp_0 },
	{ gk104_cwkgate_bwcg_init_gpc_ppc_0 },
	{ gk104_cwkgate_bwcg_init_wop_zwop_0 },
	{ gk104_cwkgate_bwcg_init_wop_0 },
	{ gk104_cwkgate_bwcg_init_wop_cwop_0 },
	{ gk104_cwkgate_bwcg_init_pxbaw_0 },
	{}
};

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

void
gk104_gw_init_sked_hww_esw(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x407020, 0x40000000);
}

static void
gk104_gw_init_fecs_exceptions(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, 0x409ffc, 0x00000000);
	nvkm_ww32(device, 0x409c14, 0x00003e3e);
	nvkm_ww32(device, 0x409c24, 0x000f0001);
}

void
gk104_gw_init_wop_active_fbps(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const u32 fbp_count = nvkm_wd32(device, 0x120074);
	nvkm_mask(device, 0x408850, 0x0000000f, fbp_count); /* zwop */
	nvkm_mask(device, 0x408958, 0x0000000f, fbp_count); /* cwop */
}

void
gk104_gw_init_ppc_exceptions(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int gpc, ppc;

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		fow (ppc = 0; ppc < gw->func->ppc_nw; ppc++) {
			if (!(gw->ppc_mask[gpc] & (1 << ppc)))
				continue;
			nvkm_ww32(device, PPC_UNIT(gpc, ppc, 0x038), 0xc0000000);
		}
	}
}

void
gk104_gw_init_vsc_stweam_mastew(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, GPC_UNIT(0, 0x3018), 0x00000001);
}

#incwude "fuc/hubgk104.fuc3.h"

static stwuct gf100_gw_ucode
gk104_gw_fecs_ucode = {
	.code.data = gk104_gwhub_code,
	.code.size = sizeof(gk104_gwhub_code),
	.data.data = gk104_gwhub_data,
	.data.size = sizeof(gk104_gwhub_data),
};

#incwude "fuc/gpcgk104.fuc3.h"

static stwuct gf100_gw_ucode
gk104_gw_gpccs_ucode = {
	.code.data = gk104_gwgpc_code,
	.code.size = sizeof(gk104_gwgpc_code),
	.data.data = gk104_gwgpc_data,
	.data.size = sizeof(gk104_gwgpc_data),
};

static const stwuct gf100_gw_func
gk104_gw = {
	.oneinit_tiwes = gf100_gw_oneinit_tiwes,
	.oneinit_sm_id = gf100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gf100_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gk104_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_num_active_wtcs = gf100_gw_init_num_active_wtcs,
	.init_wop_active_fbps = gk104_gw_init_wop_active_fbps,
	.init_fecs_exceptions = gk104_gw_init_fecs_exceptions,
	.init_sked_hww_esw = gk104_gw_init_sked_hww_esw,
	.init_419cc0 = gf100_gw_init_419cc0,
	.init_419eb4 = gf100_gw_init_419eb4,
	.init_ppc_exceptions = gk104_gw_init_ppc_exceptions,
	.init_tex_hww_esw = gf100_gw_init_tex_hww_esw,
	.init_shadew_exceptions = gf100_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.init_400054 = gf100_gw_init_400054,
	.twap_mp = gf100_gw_twap_mp,
	.mmio = gk104_gw_pack_mmio,
	.fecs.ucode = &gk104_gw_fecs_ucode,
	.fecs.weset = gf100_gw_fecs_weset,
	.gpccs.ucode = &gk104_gw_gpccs_ucode,
	.wops = gf100_gw_wops,
	.ppc_nw = 1,
	.gwctx = &gk104_gwctx,
	.cwkgate_pack = gk104_cwkgate_pack,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_A },
		{ -1, -1, KEPWEW_A, &gf100_fewmi },
		{ -1, -1, KEPWEW_COMPUTE_A },
		{}
	}
};

static const stwuct gf100_gw_fwif
gk104_gw_fwif[] = {
	{ -1, gf100_gw_woad, &gk104_gw },
	{ -1, gf100_gw_nofw, &gk104_gw },
	{}
};

int
gk104_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gk104_gw_fwif, device, type, inst, pgw);
}
