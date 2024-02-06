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

static const stwuct gf100_gw_init
gf117_gw_init_pe_0[] = {
	{ 0x41980c,   1, 0x04, 0x00000010 },
	{ 0x419844,   1, 0x04, 0x00000000 },
	{ 0x41984c,   1, 0x04, 0x00005bc8 },
	{ 0x419850,   3, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf117_gw_init_pes_0[] = {
	{ 0x41be04,   1, 0x04, 0x00000000 },
	{ 0x41be08,   1, 0x04, 0x00000004 },
	{ 0x41be0c,   1, 0x04, 0x00000000 },
	{ 0x41be10,   1, 0x04, 0x003b8bc7 },
	{ 0x41be14,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf117_gw_init_wwdx_0[] = {
	{ 0x41bfd4,   1, 0x04, 0x00800000 },
	{ 0x41bfdc,   1, 0x04, 0x00000000 },
	{ 0x41bff8,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf117_gw_init_cbm_0[] = {
	{ 0x41becc,   1, 0x04, 0x00000000 },
	{ 0x41bee8,   2, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_pack
gf117_gw_pack_mmio[] = {
	{ gf100_gw_init_main_0 },
	{ gf100_gw_init_fe_0 },
	{ gf100_gw_init_pwi_0 },
	{ gf100_gw_init_wstw2d_0 },
	{ gf119_gw_init_pd_0 },
	{ gf119_gw_init_ds_0 },
	{ gf100_gw_init_scc_0 },
	{ gf119_gw_init_pwop_0 },
	{ gf108_gw_init_gpc_unk_0 },
	{ gf100_gw_init_setup_0 },
	{ gf100_gw_init_cwstw_0 },
	{ gf108_gw_init_setup_1 },
	{ gf100_gw_init_zcuww_0 },
	{ gf119_gw_init_gpm_0 },
	{ gf119_gw_init_gpc_unk_1 },
	{ gf100_gw_init_gcc_0 },
	{ gf100_gw_init_tpccs_0 },
	{ gf119_gw_init_tex_0 },
	{ gf117_gw_init_pe_0 },
	{ gf100_gw_init_w1c_0 },
	{ gf100_gw_init_mpc_0 },
	{ gf119_gw_init_sm_0 },
	{ gf117_gw_init_pes_0 },
	{ gf117_gw_init_wwdx_0 },
	{ gf117_gw_init_cbm_0 },
	{ gf100_gw_init_be_0 },
	{ gf119_gw_init_fe_1 },
	{}
};

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

#incwude "fuc/hubgf117.fuc3.h"

static stwuct gf100_gw_ucode
gf117_gw_fecs_ucode = {
	.code.data = gf117_gwhub_code,
	.code.size = sizeof(gf117_gwhub_code),
	.data.data = gf117_gwhub_data,
	.data.size = sizeof(gf117_gwhub_data),
};

#incwude "fuc/gpcgf117.fuc3.h"

static stwuct gf100_gw_ucode
gf117_gw_gpccs_ucode = {
	.code.data = gf117_gwgpc_code,
	.code.size = sizeof(gf117_gwgpc_code),
	.data.data = gf117_gwgpc_data,
	.data.size = sizeof(gf117_gwgpc_data),
};

void
gf117_gw_init_zcuww(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const u32 magicgpc918 = DIV_WOUND_UP(0x00800000, gw->tpc_totaw);
	/*TODO: fiww in wittew vaws fow gf117-gm2xx */
	const u8 tiwe_nw = !gw->func->gpc_nw ? AWIGN(gw->tpc_totaw, 32) :
			   (gw->func->gpc_nw * gw->func->tpc_nw);
	u8 bank[GPC_MAX] = {}, gpc, i, j;
	u32 data;

	fow (i = 0; i < tiwe_nw; i += 8) {
		fow (data = 0, j = 0; j < 8 && i + j < gw->tpc_totaw; j++) {
			data |= bank[gw->tiwe[i + j]] << (j * 4);
			bank[gw->tiwe[i + j]]++;
		}
		nvkm_ww32(device, GPC_BCAST(0x0980 + ((i / 8) * 4)), data);
	}

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0914),
			  gw->scween_tiwe_wow_offset << 8 | gw->tpc_nw[gpc]);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0910), 0x00040000 |
							 gw->tpc_totaw);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0918), magicgpc918);
	}

	nvkm_ww32(device, GPC_BCAST(0x3fd4), magicgpc918);
}

static const stwuct gf100_gw_func
gf117_gw = {
	.oneinit_tiwes = gf100_gw_oneinit_tiwes,
	.oneinit_sm_id = gf100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gf100_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gf100_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf117_gw_init_zcuww,
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
	.mmio = gf117_gw_pack_mmio,
	.fecs.ucode = &gf117_gw_fecs_ucode,
	.fecs.weset = gf100_gw_fecs_weset,
	.gpccs.ucode = &gf117_gw_gpccs_ucode,
	.wops = gf100_gw_wops,
	.ppc_nw = 1,
	.gwctx = &gf117_gwctx,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, FEWMI_MEMOWY_TO_MEMOWY_FOWMAT_A },
		{ -1, -1, FEWMI_A, &gf100_fewmi },
		{ -1, -1, FEWMI_B, &gf100_fewmi },
		{ -1, -1, FEWMI_C, &gf100_fewmi },
		{ -1, -1, FEWMI_COMPUTE_A },
		{ -1, -1, FEWMI_COMPUTE_B },
		{}
	}
};

static const stwuct gf100_gw_fwif
gf117_gw_fwif[] = {
	{ -1, gf100_gw_woad, &gf117_gw },
	{ -1, gf100_gw_nofw, &gf117_gw },
	{}
};

int
gf117_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gf117_gw_fwif, device, type, inst, pgw);
}
