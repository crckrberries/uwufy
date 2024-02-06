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

#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

/*******************************************************************************
 * PGWAPH wegistew wists
 ******************************************************************************/

static const stwuct gf100_gw_init
gk208_gw_init_main_0[] = {
	{ 0x400080,   1, 0x04, 0x003083c2 },
	{ 0x400088,   1, 0x04, 0x0001bfe7 },
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
gk208_gw_init_ds_0[] = {
	{ 0x405844,   1, 0x04, 0x00ffffff },
	{ 0x405850,   1, 0x04, 0x00000000 },
	{ 0x405900,   1, 0x04, 0x00000000 },
	{ 0x405908,   1, 0x04, 0x00000000 },
	{ 0x405928,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gk208_gw_init_gpc_unk_0[] = {
	{ 0x418604,   1, 0x04, 0x00000000 },
	{ 0x418680,   1, 0x04, 0x00000000 },
	{ 0x418714,   1, 0x04, 0x00000000 },
	{ 0x418384,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gk208_gw_init_setup_1[] = {
	{ 0x4188c8,   2, 0x04, 0x00000000 },
	{ 0x4188d0,   1, 0x04, 0x00010000 },
	{ 0x4188d4,   1, 0x04, 0x00000201 },
	{}
};

static const stwuct gf100_gw_init
gk208_gw_init_tex_0[] = {
	{ 0x419ab0,   1, 0x04, 0x00000000 },
	{ 0x419ac8,   1, 0x04, 0x00000000 },
	{ 0x419ab8,   1, 0x04, 0x000000e7 },
	{ 0x419abc,   2, 0x04, 0x00000000 },
	{ 0x419ab4,   1, 0x04, 0x00000000 },
	{ 0x419aa8,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gk208_gw_init_w1c_0[] = {
	{ 0x419c98,   1, 0x04, 0x00000000 },
	{ 0x419ca8,   1, 0x04, 0x00000000 },
	{ 0x419cb0,   1, 0x04, 0x01000000 },
	{ 0x419cb4,   1, 0x04, 0x00000000 },
	{ 0x419cb8,   1, 0x04, 0x00b08bea },
	{ 0x419c84,   1, 0x04, 0x00010384 },
	{ 0x419cbc,   1, 0x04, 0x281b3646 },
	{ 0x419cc0,   2, 0x04, 0x00000000 },
	{ 0x419c80,   1, 0x04, 0x00000230 },
	{ 0x419ccc,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_pack
gk208_gw_pack_mmio[] = {
	{ gk208_gw_init_main_0 },
	{ gk110_gw_init_fe_0 },
	{ gf100_gw_init_pwi_0 },
	{ gf100_gw_init_wstw2d_0 },
	{ gf119_gw_init_pd_0 },
	{ gk208_gw_init_ds_0 },
	{ gf100_gw_init_scc_0 },
	{ gk110_gw_init_sked_0 },
	{ gk110_gw_init_cwd_0 },
	{ gf119_gw_init_pwop_0 },
	{ gk208_gw_init_gpc_unk_0 },
	{ gf100_gw_init_setup_0 },
	{ gf100_gw_init_cwstw_0 },
	{ gk208_gw_init_setup_1 },
	{ gf100_gw_init_zcuww_0 },
	{ gf119_gw_init_gpm_0 },
	{ gk110_gw_init_gpc_unk_1 },
	{ gf100_gw_init_gcc_0 },
	{ gk104_gw_init_gpc_unk_2 },
	{ gk104_gw_init_tpccs_0 },
	{ gk208_gw_init_tex_0 },
	{ gk104_gw_init_pe_0 },
	{ gk208_gw_init_w1c_0 },
	{ gf100_gw_init_mpc_0 },
	{ gk110_gw_init_sm_0 },
	{ gf117_gw_init_pes_0 },
	{ gf117_gw_init_wwdx_0 },
	{ gf117_gw_init_cbm_0 },
	{ gk104_gw_init_be_0 },
	{ gf100_gw_init_fe_1 },
	{}
};

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

#incwude "fuc/hubgk208.fuc5.h"

static stwuct gf100_gw_ucode
gk208_gw_fecs_ucode = {
	.code.data = gk208_gwhub_code,
	.code.size = sizeof(gk208_gwhub_code),
	.data.data = gk208_gwhub_data,
	.data.size = sizeof(gk208_gwhub_data),
};

#incwude "fuc/gpcgk208.fuc5.h"

static stwuct gf100_gw_ucode
gk208_gw_gpccs_ucode = {
	.code.data = gk208_gwgpc_code,
	.code.size = sizeof(gk208_gwgpc_code),
	.data.data = gk208_gwgpc_data,
	.data.size = sizeof(gk208_gwgpc_data),
};

static const stwuct gf100_gw_func
gk208_gw = {
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
	.init_ppc_exceptions = gk104_gw_init_ppc_exceptions,
	.init_tex_hww_esw = gf100_gw_init_tex_hww_esw,
	.init_shadew_exceptions = gf100_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.init_400054 = gf100_gw_init_400054,
	.twap_mp = gf100_gw_twap_mp,
	.mmio = gk208_gw_pack_mmio,
	.fecs.ucode = &gk208_gw_fecs_ucode,
	.fecs.weset = gf100_gw_fecs_weset,
	.gpccs.ucode = &gk208_gw_gpccs_ucode,
	.wops = gf100_gw_wops,
	.ppc_nw = 1,
	.gwctx = &gk208_gwctx,
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
gk208_gw_fwif[] = {
	{ -1, gf100_gw_woad, &gk208_gw },
	{ -1, gf100_gw_nofw, &gk208_gw },
	{}
};

int
gk208_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gk208_gw_fwif, device, type, inst, pgw);
}
