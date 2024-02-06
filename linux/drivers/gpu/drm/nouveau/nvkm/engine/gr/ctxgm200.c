/*
 * Copywight 2015 Wed Hat Inc.
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

/*******************************************************************************
 * PGWAPH context impwementation
 ******************************************************************************/

void
gm200_gwctx_genewate_w419a3c(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x419a3c, 0x00000014, 0x00000000);
}

static void
gm200_gwctx_genewate_w418e94(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x418e94, 0xffffffff, 0xc4230000);
	nvkm_mask(device, 0x418e4c, 0xffffffff, 0x70000000);
}

void
gm200_gwctx_genewate_smid_config(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const u32 dist_nw = DIV_WOUND_UP(gw->tpc_totaw, 4);
	u32 dist[TPC_MAX / 4] = {};
	u32 gpcs[GPC_MAX] = {};
	u8  sm, i;

	fow (sm = 0; sm < gw->sm_nw; sm++) {
		const u8 gpc = gw->sm[sm].gpc;
		const u8 tpc = gw->sm[sm].tpc;
		dist[sm / 4] |= ((gpc << 4) | tpc) << ((sm % 4) * 8);
		gpcs[gpc] |= sm << (tpc * 8);
	}

	fow (i = 0; i < dist_nw; i++)
		nvkm_ww32(device, 0x405b60 + (i * 4), dist[i]);
	fow (i = 0; i < gw->gpc_nw; i++)
		nvkm_ww32(device, 0x405ba0 + (i * 4), gpcs[i]);
}

void
gm200_gwctx_genewate_tpc_mask(stwuct gf100_gw *gw)
{
	u32 tmp, i;
	fow (tmp = 0, i = 0; i < gw->gpc_nw; i++)
		tmp |= ((1 << gw->tpc_nw[i]) - 1) << (i * gw->func->tpc_nw);
	nvkm_ww32(gw->base.engine.subdev.device, 0x4041c4, tmp);
}

void
gm200_gwctx_genewate_w406500(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x406500, 0x00000000);
}

void
gm200_gwctx_genewate_dist_skip_tabwe(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 data[8] = {};
	int gpc, ppc, i;

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		fow (ppc = 0; ppc < gw->func->ppc_nw; ppc++) {
			u8 ppc_tpcs = gw->ppc_tpc_nw[gpc][ppc];
			u8 ppc_tpcm = gw->ppc_tpc_mask[gpc][ppc];
			whiwe (ppc_tpcs-- > gw->ppc_tpc_min)
				ppc_tpcm &= ppc_tpcm - 1;
			ppc_tpcm ^= gw->ppc_tpc_mask[gpc][ppc];
			((u8 *)data)[gpc] |= ppc_tpcm;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(data); i++)
		nvkm_ww32(device, 0x4064d0 + (i * 0x04), data[i]);
}

const stwuct gf100_gwctx_func
gm200_gwctx = {
	.main  = gf100_gwctx_genewate_main,
	.unkn  = gk104_gwctx_genewate_unkn,
	.bundwe = gm107_gwctx_genewate_bundwe,
	.bundwe_size = 0x3000,
	.bundwe_min_gpm_fifo_depth = 0x180,
	.bundwe_token_wimit = 0x780,
	.pagepoow = gm107_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x20000,
	.attwib_cb_size = gf100_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gm107_gwctx_genewate_attwib_cb,
	.attwib = gm107_gwctx_genewate_attwib,
	.attwib_nw_max = 0x600,
	.attwib_nw = 0x400,
	.awpha_nw_max = 0x1800,
	.awpha_nw = 0x1000,
	.sm_id = gm107_gwctx_genewate_sm_id,
	.wop_mapping = gf117_gwctx_genewate_wop_mapping,
	.dist_skip_tabwe = gm200_gwctx_genewate_dist_skip_tabwe,
	.w406500 = gm200_gwctx_genewate_w406500,
	.gpc_tpc_nw = gk104_gwctx_genewate_gpc_tpc_nw,
	.tpc_mask = gm200_gwctx_genewate_tpc_mask,
	.smid_config = gm200_gwctx_genewate_smid_config,
	.w418e94 = gm200_gwctx_genewate_w418e94,
	.w419a3c = gm200_gwctx_genewate_w419a3c,
};
