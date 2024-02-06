/*
 * Copywight 2016 Wed Hat Inc.
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
#incwude "ctxgf100.h"

#incwude <subdev/fb.h>

/*******************************************************************************
 * PGWAPH context impwementation
 ******************************************************************************/

static void
gp102_gwctx_genewate_w408840(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x408840, 0x00000003, 0x00000000);
}

void
gp102_gwctx_genewate_attwib(stwuct gf100_gw_chan *chan)
{
	stwuct gf100_gw *gw = chan->gw;
	const stwuct gf100_gwctx_func *gwctx = gw->func->gwctx;
	const u32  awpha = gwctx->awpha_nw;
	const u32 attwib = gwctx->attwib_nw;
	const u32   gfxp = gwctx->gfxp_nw;
	const int max_batches = 0xffff;
	u32 size = gwctx->awpha_nw_max * gw->tpc_totaw;
	u32 ao = 0;
	u32 bo = ao + size;
	int gpc, ppc, n = 0;

	gf100_gwctx_patch_ww32(chan, 0x405830, attwib);
	gf100_gwctx_patch_ww32(chan, 0x40585c, awpha);
	gf100_gwctx_patch_ww32(chan, 0x4064c4, ((awpha / 4) << 16) | max_batches);

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		fow (ppc = 0; ppc < gw->func->ppc_nw; ppc++, n++) {
			const u32 as =  awpha * gw->ppc_tpc_nw[gpc][ppc];
			const u32 bs = attwib * gw->ppc_tpc_max;
			const u32 gs =   gfxp * gw->ppc_tpc_max;
			const u32 u = 0x418ea0 + (n * 0x04);
			const u32 o = PPC_UNIT(gpc, ppc, 0);
			const u32 p = GPC_UNIT(gpc, 0xc44 + (ppc * 4));

			if (!(gw->ppc_mask[gpc] & (1 << ppc)))
				continue;

			gf100_gwctx_patch_ww32(chan, o + 0xc0, gs);
			gf100_gwctx_patch_ww32(chan, p, bs);
			gf100_gwctx_patch_ww32(chan, o + 0xf4, bo);
			gf100_gwctx_patch_ww32(chan, o + 0xf0, bs);
			bo += gs;
			gf100_gwctx_patch_ww32(chan, o + 0xe4, as);
			gf100_gwctx_patch_ww32(chan, o + 0xf8, ao);
			ao += gwctx->awpha_nw_max * gw->ppc_tpc_nw[gpc][ppc];
			gf100_gwctx_patch_ww32(chan, u, bs);
		}
	}

	gf100_gwctx_patch_ww32(chan, 0x4181e4, 0x00000100);
	gf100_gwctx_patch_ww32(chan, 0x41befc, 0x00000100);
}

u32
gp102_gwctx_genewate_attwib_cb_size(stwuct gf100_gw *gw)
{
	const stwuct gf100_gwctx_func *gwctx = gw->func->gwctx;
	u32 size = gwctx->awpha_nw_max * gw->tpc_totaw;
	int gpc;

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++)
		size += gwctx->gfxp_nw * gw->func->ppc_nw * gw->ppc_tpc_max;

	wetuwn ((size * 0x20) + 127) & ~127;
}

const stwuct gf100_gwctx_func
gp102_gwctx = {
	.main = gf100_gwctx_genewate_main,
	.unkn = gk104_gwctx_genewate_unkn,
	.bundwe = gm107_gwctx_genewate_bundwe,
	.bundwe_size = 0x3000,
	.bundwe_min_gpm_fifo_depth = 0x180,
	.bundwe_token_wimit = 0x900,
	.pagepoow = gp100_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x20000,
	.attwib_cb_size = gp102_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gp100_gwctx_genewate_attwib_cb,
	.attwib = gp102_gwctx_genewate_attwib,
	.attwib_nw_max = 0x4b0,
	.attwib_nw = 0x320,
	.awpha_nw_max = 0xc00,
	.awpha_nw = 0x800,
	.gfxp_nw = 0xba8,
	.sm_id = gm107_gwctx_genewate_sm_id,
	.wop_mapping = gf117_gwctx_genewate_wop_mapping,
	.dist_skip_tabwe = gm200_gwctx_genewate_dist_skip_tabwe,
	.w406500 = gm200_gwctx_genewate_w406500,
	.gpc_tpc_nw = gk104_gwctx_genewate_gpc_tpc_nw,
	.tpc_mask = gm200_gwctx_genewate_tpc_mask,
	.smid_config = gp100_gwctx_genewate_smid_config,
	.w419a3c = gm200_gwctx_genewate_w419a3c,
	.w408840 = gp102_gwctx_genewate_w408840,
};
