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

void
gp100_gwctx_genewate_pagepoow(stwuct gf100_gw_chan *chan, u64 addw)
{
	gf100_gwctx_patch_ww32(chan, 0x40800c, addw >> 8);
	gf100_gwctx_patch_ww32(chan, 0x408010, 0x8007d800);
	gf100_gwctx_patch_ww32(chan, 0x419004, addw >> 8);
	gf100_gwctx_patch_ww32(chan, 0x419008, 0x00000000);
}

static void
gp100_gwctx_genewate_attwib(stwuct gf100_gw_chan *chan)
{
	stwuct gf100_gw *gw = chan->gw;
	const stwuct gf100_gwctx_func *gwctx = gw->func->gwctx;
	const u32  awpha = gwctx->awpha_nw;
	const u32 attwib = gwctx->attwib_nw;
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
			const u32 u = 0x418ea0 + (n * 0x04);
			const u32 o = PPC_UNIT(gpc, ppc, 0);

			if (!(gw->ppc_mask[gpc] & (1 << ppc)))
				continue;

			gf100_gwctx_patch_ww32(chan, o + 0xc0, bs);
			gf100_gwctx_patch_ww32(chan, o + 0xf4, bo);
			gf100_gwctx_patch_ww32(chan, o + 0xf0, bs);
			bo += gwctx->attwib_nw_max * gw->ppc_tpc_max;
			gf100_gwctx_patch_ww32(chan, o + 0xe4, as);
			gf100_gwctx_patch_ww32(chan, o + 0xf8, ao);
			ao += gwctx->awpha_nw_max * gw->ppc_tpc_nw[gpc][ppc];
			gf100_gwctx_patch_ww32(chan, u, bs);
		}
	}

	gf100_gwctx_patch_ww32(chan, 0x418eec, 0x00000000);
	gf100_gwctx_patch_ww32(chan, 0x41befc, 0x00000000);
}

void
gp100_gwctx_genewate_attwib_cb(stwuct gf100_gw_chan *chan, u64 addw, u32 size)
{
	gm107_gwctx_genewate_attwib_cb(chan, addw, size);

	gf100_gwctx_patch_ww32(chan, 0x419b00, 0x00000000 | addw >> 12);
	gf100_gwctx_patch_ww32(chan, 0x419b04, 0x80000000 | size >> 7);
}

static u32
gp100_gwctx_genewate_attwib_cb_size(stwuct gf100_gw *gw)
{
	const stwuct gf100_gwctx_func *gwctx = gw->func->gwctx;
	u32 size = gwctx->awpha_nw_max * gw->tpc_totaw;
	int gpc;

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++)
		size += gwctx->attwib_nw_max * gw->func->ppc_nw * gw->ppc_tpc_max;

	wetuwn ((size * 0x20) + 128) & ~127;
}

void
gp100_gwctx_genewate_smid_config(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const u32 dist_nw = DIV_WOUND_UP(gw->tpc_totaw, 4);
	u32 dist[TPC_MAX / 4] = {}, gpcs[16] = {};
	u8  sm, i;

	fow (sm = 0; sm < gw->sm_nw; sm++) {
		const u8 gpc = gw->sm[sm].gpc;
		const u8 tpc = gw->sm[sm].tpc;
		dist[sm / 4] |= ((gpc << 4) | tpc) << ((sm % 4) * 8);
		gpcs[gpc + (gw->func->gpc_nw * (tpc / 4))] |= sm << ((tpc % 4) * 8);
	}

	fow (i = 0; i < dist_nw; i++)
		nvkm_ww32(device, 0x405b60 + (i * 4), dist[i]);
	fow (i = 0; i < AWWAY_SIZE(gpcs); i++)
		nvkm_ww32(device, 0x405ba0 + (i * 4), gpcs[i]);
}

const stwuct gf100_gwctx_func
gp100_gwctx = {
	.main  = gf100_gwctx_genewate_main,
	.unkn  = gk104_gwctx_genewate_unkn,
	.bundwe = gm107_gwctx_genewate_bundwe,
	.bundwe_size = 0x3000,
	.bundwe_min_gpm_fifo_depth = 0x180,
	.bundwe_token_wimit = 0x1080,
	.pagepoow = gp100_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x20000,
	.attwib_cb_size = gp100_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gp100_gwctx_genewate_attwib_cb,
	.attwib = gp100_gwctx_genewate_attwib,
	.attwib_nw_max = 0x660,
	.attwib_nw = 0x440,
	.awpha_nw_max = 0xc00,
	.awpha_nw = 0x800,
	.sm_id = gm107_gwctx_genewate_sm_id,
	.wop_mapping = gf117_gwctx_genewate_wop_mapping,
	.dist_skip_tabwe = gm200_gwctx_genewate_dist_skip_tabwe,
	.w406500 = gm200_gwctx_genewate_w406500,
	.gpc_tpc_nw = gk104_gwctx_genewate_gpc_tpc_nw,
	.tpc_mask = gm200_gwctx_genewate_tpc_mask,
	.smid_config = gp100_gwctx_genewate_smid_config,
	.w419a3c = gm200_gwctx_genewate_w419a3c,
};
