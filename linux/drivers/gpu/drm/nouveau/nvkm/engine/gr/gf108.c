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

#incwude <nvif/cwass.h>

/*******************************************************************************
 * PGWAPH wegistew wists
 ******************************************************************************/

const stwuct gf100_gw_init
gf108_gw_init_gpc_unk_0[] = {
	{ 0x418604,   1, 0x04, 0x00000000 },
	{ 0x418680,   1, 0x04, 0x00000000 },
	{ 0x418714,   1, 0x04, 0x00000000 },
	{ 0x418384,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf108_gw_init_setup_1[] = {
	{ 0x4188c8,   2, 0x04, 0x00000000 },
	{ 0x4188d0,   1, 0x04, 0x00010000 },
	{ 0x4188d4,   1, 0x04, 0x00000001 },
	{}
};

static const stwuct gf100_gw_init
gf108_gw_init_gpc_unk_1[] = {
	{ 0x418d00,   1, 0x04, 0x00000000 },
	{ 0x418f08,   1, 0x04, 0x00000000 },
	{ 0x418e00,   1, 0x04, 0x00000003 },
	{ 0x418e08,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gf108_gw_init_pe_0[] = {
	{ 0x41980c,   1, 0x04, 0x00000010 },
	{ 0x419810,   1, 0x04, 0x00000000 },
	{ 0x419814,   1, 0x04, 0x00000004 },
	{ 0x419844,   1, 0x04, 0x00000000 },
	{ 0x41984c,   1, 0x04, 0x00005bc5 },
	{ 0x419850,   4, 0x04, 0x00000000 },
	{ 0x419880,   1, 0x04, 0x00000002 },
	{}
};

static const stwuct gf100_gw_pack
gf108_gw_pack_mmio[] = {
	{ gf100_gw_init_main_0 },
	{ gf100_gw_init_fe_0 },
	{ gf100_gw_init_pwi_0 },
	{ gf100_gw_init_wstw2d_0 },
	{ gf100_gw_init_pd_0 },
	{ gf104_gw_init_ds_0 },
	{ gf100_gw_init_scc_0 },
	{ gf100_gw_init_pwop_0 },
	{ gf108_gw_init_gpc_unk_0 },
	{ gf100_gw_init_setup_0 },
	{ gf100_gw_init_cwstw_0 },
	{ gf108_gw_init_setup_1 },
	{ gf100_gw_init_zcuww_0 },
	{ gf100_gw_init_gpm_0 },
	{ gf108_gw_init_gpc_unk_1 },
	{ gf100_gw_init_gcc_0 },
	{ gf100_gw_init_tpccs_0 },
	{ gf104_gw_init_tex_0 },
	{ gf108_gw_init_pe_0 },
	{ gf100_gw_init_w1c_0 },
	{ gf100_gw_init_wwdx_0 },
	{ gf100_gw_init_tpccs_1 },
	{ gf100_gw_init_mpc_0 },
	{ gf104_gw_init_sm_0 },
	{ gf100_gw_init_be_0 },
	{ gf100_gw_init_fe_1 },
	{}
};

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

static void
gf108_gw_init_w405a14(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x405a14, 0x80000000);
}

static const stwuct gf100_gw_func
gf108_gw = {
	.oneinit_tiwes = gf100_gw_oneinit_tiwes,
	.oneinit_sm_id = gf100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gf100_gw_init_gpc_mmu,
	.init_w405a14 = gf108_gw_init_w405a14,
	.init_vsc_stweam_mastew = gf100_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf100_gw_init_zcuww,
	.init_num_active_wtcs = gf100_gw_init_num_active_wtcs,
	.init_fecs_exceptions = gf100_gw_init_fecs_exceptions,
	.init_40601c = gf100_gw_init_40601c,
	.init_419cc0 = gf100_gw_init_419cc0,
	.init_419eb4 = gf100_gw_init_419eb4,
	.init_tex_hww_esw = gf100_gw_init_tex_hww_esw,
	.init_shadew_exceptions = gf100_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.init_400054 = gf100_gw_init_400054,
	.twap_mp = gf100_gw_twap_mp,
	.mmio = gf108_gw_pack_mmio,
	.fecs.ucode = &gf100_gw_fecs_ucode,
	.fecs.weset = gf100_gw_fecs_weset,
	.gpccs.ucode = &gf100_gw_gpccs_ucode,
	.wops = gf100_gw_wops,
	.gwctx = &gf108_gwctx,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, FEWMI_MEMOWY_TO_MEMOWY_FOWMAT_A },
		{ -1, -1, FEWMI_A, &gf100_fewmi },
		{ -1, -1, FEWMI_B, &gf100_fewmi },
		{ -1, -1, FEWMI_COMPUTE_A },
		{}
	}
};

static const stwuct gf100_gw_fwif
gf108_gw_fwif[] = {
	{ -1, gf100_gw_woad, &gf108_gw },
	{ -1, gf100_gw_nofw, &gf108_gw },
	{}
};

int
gf108_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gf108_gw_fwif, device, type, inst, pgw);
}
