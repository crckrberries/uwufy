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

#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

/*******************************************************************************
 * PGWAPH wegistew wists
 ******************************************************************************/

const stwuct gf100_gw_init
gk110_gw_init_fe_0[] = {
	{ 0x40415c,   1, 0x04, 0x00000000 },
	{ 0x404170,   1, 0x04, 0x00000000 },
	{ 0x4041b4,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk110_gw_init_ds_0[] = {
	{ 0x405844,   1, 0x04, 0x00ffffff },
	{ 0x405850,   1, 0x04, 0x00000000 },
	{ 0x405900,   1, 0x04, 0x0000ff00 },
	{ 0x405908,   1, 0x04, 0x00000000 },
	{ 0x405928,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk110_gw_init_sked_0[] = {
	{ 0x407010,   1, 0x04, 0x00000000 },
	{ 0x407040,   1, 0x04, 0x80440424 },
	{ 0x407048,   1, 0x04, 0x0000000a },
	{}
};

const stwuct gf100_gw_init
gk110_gw_init_cwd_0[] = {
	{ 0x405b44,   1, 0x04, 0x00000000 },
	{ 0x405b50,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk110_gw_init_gpc_unk_1[] = {
	{ 0x418d00,   1, 0x04, 0x00000000 },
	{ 0x418d28,   2, 0x04, 0x00000000 },
	{ 0x418f00,   1, 0x04, 0x00000400 },
	{ 0x418f08,   1, 0x04, 0x00000000 },
	{ 0x418f20,   2, 0x04, 0x00000000 },
	{ 0x418e00,   1, 0x04, 0x00000000 },
	{ 0x418e08,   1, 0x04, 0x00000000 },
	{ 0x418e1c,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk110_gw_init_tex_0[] = {
	{ 0x419ab0,   1, 0x04, 0x00000000 },
	{ 0x419ac8,   1, 0x04, 0x00000000 },
	{ 0x419ab8,   1, 0x04, 0x000000e7 },
	{ 0x419aec,   1, 0x04, 0x00000000 },
	{ 0x419abc,   2, 0x04, 0x00000000 },
	{ 0x419ab4,   1, 0x04, 0x00000000 },
	{ 0x419aa8,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gk110_gw_init_w1c_0[] = {
	{ 0x419c98,   1, 0x04, 0x00000000 },
	{ 0x419ca8,   1, 0x04, 0x00000000 },
	{ 0x419cb0,   1, 0x04, 0x01000000 },
	{ 0x419cb4,   1, 0x04, 0x00000000 },
	{ 0x419cb8,   1, 0x04, 0x00b08bea },
	{ 0x419c84,   1, 0x04, 0x00010384 },
	{ 0x419cbc,   1, 0x04, 0x281b3646 },
	{ 0x419cc0,   2, 0x04, 0x00000000 },
	{ 0x419c80,   1, 0x04, 0x00020230 },
	{ 0x419ccc,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk110_gw_init_sm_0[] = {
	{ 0x419e00,   1, 0x04, 0x00000080 },
	{ 0x419ea0,   1, 0x04, 0x00000000 },
	{ 0x419ee4,   1, 0x04, 0x00000000 },
	{ 0x419ea4,   1, 0x04, 0x00000100 },
	{ 0x419ea8,   1, 0x04, 0x00000000 },
	{ 0x419eb4,   1, 0x04, 0x00000000 },
	{ 0x419ebc,   2, 0x04, 0x00000000 },
	{ 0x419edc,   1, 0x04, 0x00000000 },
	{ 0x419f00,   1, 0x04, 0x00000000 },
	{ 0x419ed0,   1, 0x04, 0x00003234 },
	{ 0x419f74,   1, 0x04, 0x00015555 },
	{ 0x419f80,   4, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_pack
gk110_gw_pack_mmio[] = {
	{ gk104_gw_init_main_0 },
	{ gk110_gw_init_fe_0 },
	{ gf100_gw_init_pwi_0 },
	{ gf100_gw_init_wstw2d_0 },
	{ gf119_gw_init_pd_0 },
	{ gk110_gw_init_ds_0 },
	{ gf100_gw_init_scc_0 },
	{ gk110_gw_init_sked_0 },
	{ gk110_gw_init_cwd_0 },
	{ gf119_gw_init_pwop_0 },
	{ gf108_gw_init_gpc_unk_0 },
	{ gf100_gw_init_setup_0 },
	{ gf100_gw_init_cwstw_0 },
	{ gf108_gw_init_setup_1 },
	{ gf100_gw_init_zcuww_0 },
	{ gf119_gw_init_gpm_0 },
	{ gk110_gw_init_gpc_unk_1 },
	{ gf100_gw_init_gcc_0 },
	{ gk104_gw_init_gpc_unk_2 },
	{ gk104_gw_init_tpccs_0 },
	{ gk110_gw_init_tex_0 },
	{ gk104_gw_init_pe_0 },
	{ gk110_gw_init_w1c_0 },
	{ gf100_gw_init_mpc_0 },
	{ gk110_gw_init_sm_0 },
	{ gf117_gw_init_pes_0 },
	{ gf117_gw_init_wwdx_0 },
	{ gf117_gw_init_cbm_0 },
	{ gk104_gw_init_be_0 },
	{ gf100_gw_init_fe_1 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_bwcg_init_sked_0[] = {
	{ 0x407000, 1, 0x00004041 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_bwcg_init_gpc_gcc_0[] = {
	{ 0x419020, 1, 0x00000042 },
	{ 0x419038, 1, 0x00000042 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_bwcg_init_gpc_w1c_0[] = {
	{ 0x419cd4, 2, 0x00004042 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_bwcg_init_gpc_mp_0[] = {
	{ 0x419fd0, 1, 0x00004043 },
	{ 0x419fd8, 1, 0x00004049 },
	{ 0x419fe0, 2, 0x00004042 },
	{ 0x419ff0, 1, 0x00000046 },
	{ 0x419ff8, 1, 0x00004042 },
	{ 0x419f90, 1, 0x00004042 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_main_0[] = {
	{ 0x4041f4, 1, 0x00000000 },
	{ 0x409894, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_unk_0[] = {
	{ 0x406004, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_sked_0[] = {
	{ 0x407004, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_ctxctw_0[] = {
	{ 0x41a894, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_unk_0[] = {
	{ 0x418504, 1, 0x00000000 },
	{ 0x41860c, 1, 0x00000000 },
	{ 0x41868c, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_esetup_0[] = {
	{ 0x41882c, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_zcuww_0[] = {
	{ 0x418974, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_w1c_0[] = {
	{ 0x419cd8, 2, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_unk_1[] = {
	{ 0x419c74, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_mp_0[] = {
	{ 0x419fd4, 1, 0x00004a4a },
	{ 0x419fdc, 1, 0x00000014 },
	{ 0x419fe4, 1, 0x00000000 },
	{ 0x419ff4, 1, 0x00001724 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_gpc_ppc_0[] = {
	{ 0x41be2c, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_init
gk110_cwkgate_swcg_init_pcountew_0[] = {
	{ 0x1be018, 1, 0x000001ff },
	{ 0x1bc018, 1, 0x000001ff },
	{ 0x1b8018, 1, 0x000001ff },
	{ 0x1b4124, 1, 0x00000000 },
	{}
};

static const stwuct nvkm_thewm_cwkgate_pack
gk110_cwkgate_pack[] = {
	{ gk104_cwkgate_bwcg_init_main_0 },
	{ gk104_cwkgate_bwcg_init_wstw2d_0 },
	{ gk104_cwkgate_bwcg_init_unk_0 },
	{ gk104_cwkgate_bwcg_init_gcc_0 },
	{ gk110_cwkgate_bwcg_init_sked_0 },
	{ gk104_cwkgate_bwcg_init_unk_1 },
	{ gk104_cwkgate_bwcg_init_gpc_ctxctw_0 },
	{ gk104_cwkgate_bwcg_init_gpc_unk_0 },
	{ gk104_cwkgate_bwcg_init_gpc_esetup_0 },
	{ gk104_cwkgate_bwcg_init_gpc_tpbus_0 },
	{ gk104_cwkgate_bwcg_init_gpc_zcuww_0 },
	{ gk104_cwkgate_bwcg_init_gpc_tpconf_0 },
	{ gk104_cwkgate_bwcg_init_gpc_unk_1 },
	{ gk110_cwkgate_bwcg_init_gpc_gcc_0 },
	{ gk104_cwkgate_bwcg_init_gpc_ffb_0 },
	{ gk104_cwkgate_bwcg_init_gpc_tex_0 },
	{ gk104_cwkgate_bwcg_init_gpc_powy_0 },
	{ gk110_cwkgate_bwcg_init_gpc_w1c_0 },
	{ gk104_cwkgate_bwcg_init_gpc_unk_2 },
	{ gk110_cwkgate_bwcg_init_gpc_mp_0 },
	{ gk104_cwkgate_bwcg_init_gpc_ppc_0 },
	{ gk104_cwkgate_bwcg_init_wop_zwop_0 },
	{ gk104_cwkgate_bwcg_init_wop_0 },
	{ gk104_cwkgate_bwcg_init_wop_cwop_0 },
	{ gk104_cwkgate_bwcg_init_pxbaw_0 },
	{ gk110_cwkgate_swcg_init_main_0 },
	{ gk110_cwkgate_swcg_init_unk_0 },
	{ gk110_cwkgate_swcg_init_sked_0 },
	{ gk110_cwkgate_swcg_init_gpc_ctxctw_0 },
	{ gk110_cwkgate_swcg_init_gpc_unk_0 },
	{ gk110_cwkgate_swcg_init_gpc_esetup_0 },
	{ gk110_cwkgate_swcg_init_gpc_zcuww_0 },
	{ gk110_cwkgate_swcg_init_gpc_w1c_0 },
	{ gk110_cwkgate_swcg_init_gpc_unk_1 },
	{ gk110_cwkgate_swcg_init_gpc_mp_0 },
	{ gk110_cwkgate_swcg_init_gpc_ppc_0 },
	{ gk110_cwkgate_swcg_init_pcountew_0 },
	{}
};

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

#incwude "fuc/hubgk110.fuc3.h"

stwuct gf100_gw_ucode
gk110_gw_fecs_ucode = {
	.code.data = gk110_gwhub_code,
	.code.size = sizeof(gk110_gwhub_code),
	.data.data = gk110_gwhub_data,
	.data.size = sizeof(gk110_gwhub_data),
};

#incwude "fuc/gpcgk110.fuc3.h"

stwuct gf100_gw_ucode
gk110_gw_gpccs_ucode = {
	.code.data = gk110_gwgpc_code,
	.code.size = sizeof(gk110_gwgpc_code),
	.data.data = gk110_gwgpc_data,
	.data.size = sizeof(gk110_gwgpc_data),
};

void
gk110_gw_init_419eb4(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x419eb4, 0x00001000, 0x00001000);
	nvkm_mask(device, 0x419eb4, 0x00002000, 0x00002000);
	nvkm_mask(device, 0x419eb4, 0x00004000, 0x00004000);
	nvkm_mask(device, 0x419eb4, 0x00008000, 0x00008000);
	nvkm_mask(device, 0x419eb4, 0x00001000, 0x00000000);
	nvkm_mask(device, 0x419eb4, 0x00002000, 0x00000000);
	nvkm_mask(device, 0x419eb4, 0x00004000, 0x00000000);
	nvkm_mask(device, 0x419eb4, 0x00008000, 0x00000000);
}

static const stwuct gf100_gw_func
gk110_gw = {
	.oneinit_tiwes = gf100_gw_oneinit_tiwes,
	.oneinit_sm_id = gf100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gf100_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gk104_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_num_active_wtcs = gf100_gw_init_num_active_wtcs,
	.init_wop_active_fbps = gk104_gw_init_wop_active_fbps,
	.init_fecs_exceptions = gf100_gw_init_fecs_exceptions,
	.init_sked_hww_esw = gk104_gw_init_sked_hww_esw,
	.init_419cc0 = gf100_gw_init_419cc0,
	.init_419eb4 = gk110_gw_init_419eb4,
	.init_ppc_exceptions = gk104_gw_init_ppc_exceptions,
	.init_tex_hww_esw = gf100_gw_init_tex_hww_esw,
	.init_shadew_exceptions = gf100_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.init_400054 = gf100_gw_init_400054,
	.twap_mp = gf100_gw_twap_mp,
	.mmio = gk110_gw_pack_mmio,
	.fecs.ucode = &gk110_gw_fecs_ucode,
	.fecs.weset = gf100_gw_fecs_weset,
	.gpccs.ucode = &gk110_gw_gpccs_ucode,
	.wops = gf100_gw_wops,
	.ppc_nw = 2,
	.gwctx = &gk110_gwctx,
	.cwkgate_pack = gk110_cwkgate_pack,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, KEPWEW_B, &gf100_fewmi },
		{ -1, -1, KEPWEW_COMPUTE_B },
		{}
	}
};

static const stwuct gf100_gw_fwif
gk110_gw_fwif[] = {
	{ -1, gf100_gw_woad, &gk110_gw },
	{ -1, gf100_gw_nofw, &gk110_gw },
	{}
};

int
gk110_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gk110_gw_fwif, device, type, inst, pgw);
}
