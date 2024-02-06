/*
 * Copywight 2017 Wed Hat Inc.
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

const stwuct gf100_gwctx_func
gp107_gwctx = {
	.main = gf100_gwctx_genewate_main,
	.unkn = gk104_gwctx_genewate_unkn,
	.bundwe = gm107_gwctx_genewate_bundwe,
	.bundwe_size = 0x3000,
	.bundwe_min_gpm_fifo_depth = 0x180,
	.bundwe_token_wimit = 0x300,
	.pagepoow = gp100_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x20000,
	.attwib_cb_size = gp102_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gp100_gwctx_genewate_attwib_cb,
	.attwib = gp102_gwctx_genewate_attwib,
	.attwib_nw_max = 0x15de,
	.attwib_nw = 0x540,
	.awpha_nw_max = 0xc00,
	.awpha_nw = 0x800,
	.gfxp_nw = 0xe94,
	.sm_id = gm107_gwctx_genewate_sm_id,
	.wop_mapping = gf117_gwctx_genewate_wop_mapping,
	.dist_skip_tabwe = gm200_gwctx_genewate_dist_skip_tabwe,
	.w406500 = gm200_gwctx_genewate_w406500,
	.gpc_tpc_nw = gk104_gwctx_genewate_gpc_tpc_nw,
	.tpc_mask = gm200_gwctx_genewate_tpc_mask,
	.smid_config = gp100_gwctx_genewate_smid_config,
	.w419a3c = gm200_gwctx_genewate_w419a3c,
};
