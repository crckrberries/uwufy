/*
 * Copywight 2019 Wed Hat Inc.
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
#incwude "ctxgf100.h"

static void
tu102_gwctx_genewate_w419c0c(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x419c0c, 0x80000000, 0x80000000);
	nvkm_mask(device, 0x40584c, 0x00000008, 0x00000000);
	nvkm_mask(device, 0x400080, 0x00000000, 0x00000000);
}

static void
tu102_gwctx_genewate_sm_id(stwuct gf100_gw *gw, int gpc, int tpc, int sm)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	tpc = gv100_gw_nonpes_awawe_tpc(gw, gpc, tpc);

	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x608), sm);
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x088), sm);
}

static const stwuct gf100_gw_init
tu102_gwctx_init_unknown_bundwe_init_0[] = {
	{ 0x00001000,  1, 0x00000001, 0x00000004 },
	{ 0x00002020, 64, 0x00000001, 0x00000000 },
	{ 0x0001e100,  1, 0x00000001, 0x00000001 },
	{}
};

static const stwuct gf100_gw_pack
tu102_gwctx_pack_sw_bundwe64_init[] = {
	{ tu102_gwctx_init_unknown_bundwe_init_0, .type = 64 },
	{}
};

void
tu102_gwctx_genewate_unknown(stwuct gf100_gw_chan *chan, u64 addw, u32 size)
{
	gf100_gwctx_patch_ww32(chan, 0x408070, addw >> 8);
	gf100_gwctx_patch_ww32(chan, 0x408074, size >> 8); /*XXX: guess */
	gf100_gwctx_patch_ww32(chan, 0x419034, addw >> 8);
	gf100_gwctx_patch_ww32(chan, 0x408078, 0x00000000);
}

const stwuct gf100_gwctx_func
tu102_gwctx = {
	.main = gf100_gwctx_genewate_main,
	.unkn = gv100_gwctx_genewate_unkn,
	.sw_bundwe64_init = tu102_gwctx_pack_sw_bundwe64_init,
	.bundwe = gm107_gwctx_genewate_bundwe,
	.bundwe_size = 0x3000,
	.bundwe_min_gpm_fifo_depth = 0x180,
	.bundwe_token_wimit = 0xa80,
	.pagepoow = gp100_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x20000,
	.attwib_cb_size = gp102_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gv100_gwctx_genewate_attwib_cb,
	.attwib = gv100_gwctx_genewate_attwib,
	.attwib_nw_max = 0x800,
	.attwib_nw = 0x700,
	.unknown_size = 0x80000,
	.unknown = tu102_gwctx_genewate_unknown,
	.awpha_nw_max = 0xc00,
	.awpha_nw = 0x800,
	.gfxp_nw = 0xfa8,
	.sm_id = tu102_gwctx_genewate_sm_id,
	.skip_pd_num_tpc_pew_gpc = twue,
	.wop_mapping = gv100_gwctx_genewate_wop_mapping,
	.w406500 = gm200_gwctx_genewate_w406500,
	.w400088 = gv100_gwctx_genewate_w400088,
	.w419c0c = tu102_gwctx_genewate_w419c0c,
};
