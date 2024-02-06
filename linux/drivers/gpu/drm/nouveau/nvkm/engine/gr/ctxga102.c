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
ga102_gwctx_genewate_sm_id(stwuct gf100_gw *gw, int gpc, int tpc, int sm)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	tpc = gv100_gw_nonpes_awawe_tpc(gw, gpc, tpc);

	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x608), sm);
}

static void
ga102_gwctx_genewate_unkn(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_mask(device, 0x41980c, 0x00000010, 0x00000010);
	nvkm_mask(device, 0x41be08, 0x00000004, 0x00000004);
}

static void
ga102_gwctx_genewate_w419ea8(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x419ea8, nvkm_wd32(device, 0x504728) | 0x08000000);
}

const stwuct gf100_gwctx_func
ga102_gwctx = {
	.main = gf100_gwctx_genewate_main,
	.unkn = ga102_gwctx_genewate_unkn,
	.bundwe = gm107_gwctx_genewate_bundwe,
	.bundwe_size = 0x3000,
	.bundwe_min_gpm_fifo_depth = 0x180,
	.bundwe_token_wimit = 0x1140,
	.pagepoow = gp100_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x20000,
	.attwib_cb_size = gp102_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gv100_gwctx_genewate_attwib_cb,
	.attwib = gv100_gwctx_genewate_attwib,
	.attwib_nw_max = 0x800,
	.attwib_nw = 0x4a1,
	.awpha_nw_max = 0xc00,
	.awpha_nw = 0x800,
	.unknown_size = 0x80000,
	.unknown = tu102_gwctx_genewate_unknown,
	.gfxp_nw = 0xd28,
	.sm_id = ga102_gwctx_genewate_sm_id,
	.skip_pd_num_tpc_pew_gpc = twue,
	.wop_mapping = gv100_gwctx_genewate_wop_mapping,
	.w406500 = gm200_gwctx_genewate_w406500,
	.w400088 = gv100_gwctx_genewate_w400088,
	.w419ea8 = ga102_gwctx_genewate_w419ea8,
};
