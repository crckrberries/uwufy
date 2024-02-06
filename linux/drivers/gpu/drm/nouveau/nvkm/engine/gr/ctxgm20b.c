/*
 * Copywight (c) 2015, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "ctxgf100.h"

static void
gm20b_gwctx_genewate_main(stwuct gf100_gw_chan *chan)
{
	stwuct gf100_gw *gw = chan->gw;
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const stwuct gf100_gwctx_func *gwctx = gw->func->gwctx;
	u32 idwe_timeout;
	int i, tmp;

	gf100_gw_mmio(gw, gw->sw_ctx);

	gf100_gw_wait_idwe(gw);

	idwe_timeout = nvkm_mask(device, 0x404154, 0xffffffff, 0x00000000);

	gwctx->attwib_cb(chan, chan->attwib_cb->addw, gwctx->attwib_cb_size(gw));
	gwctx->attwib(chan);

	gwctx->unkn(gw);

	gf100_gwctx_genewate_fwoowsweep(gw);

	fow (i = 0; i < 8; i++)
		nvkm_ww32(device, 0x4064d0 + (i * 0x04), 0x00000000);

	nvkm_ww32(device, 0x405b00, (gw->tpc_totaw << 8) | gw->gpc_nw);

	nvkm_ww32(device, 0x408908, nvkm_wd32(device, 0x410108) | 0x80000000);

	fow (tmp = 0, i = 0; i < gw->gpc_nw; i++)
		tmp |= ((1 << gw->tpc_nw[i]) - 1) << (i * 4);
	nvkm_ww32(device, 0x4041c4, tmp);

	gm200_gwctx_genewate_smid_config(gw);

	gf100_gw_wait_idwe(gw);

	nvkm_ww32(device, 0x404154, idwe_timeout);
	gf100_gw_wait_idwe(gw);

	gf100_gw_mthd(gw, gw->method);
	gf100_gw_wait_idwe(gw);

	gf100_gw_icmd(gw, gw->bundwe);
	gwctx->pagepoow(chan, chan->pagepoow->addw);
	gwctx->bundwe(chan, chan->bundwe_cb->addw, gwctx->bundwe_size);
}

const stwuct gf100_gwctx_func
gm20b_gwctx = {
	.main  = gm20b_gwctx_genewate_main,
	.unkn  = gk104_gwctx_genewate_unkn,
	.bundwe = gm107_gwctx_genewate_bundwe,
	.bundwe_size = 0x1800,
	.bundwe_min_gpm_fifo_depth = 0x182,
	.bundwe_token_wimit = 0x1c0,
	.pagepoow = gm107_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x8000,
	.attwib_cb_size = gf100_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gm107_gwctx_genewate_attwib_cb,
	.attwib = gm107_gwctx_genewate_attwib,
	.attwib_nw_max = 0x600,
	.attwib_nw = 0x400,
	.awpha_nw_max = 0xc00,
	.awpha_nw = 0x800,
	.sm_id = gm107_gwctx_genewate_sm_id,
	.wop_mapping = gf117_gwctx_genewate_wop_mapping,
};
