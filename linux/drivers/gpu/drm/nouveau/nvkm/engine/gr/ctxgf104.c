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
#incwude "ctxgf100.h"

/*******************************************************************************
 * PGWAPH context wegistew wists
 ******************************************************************************/

const stwuct gf100_gw_init
gf104_gwctx_init_tex_0[] = {
	{ 0x419a00,   1, 0x04, 0x000001f0 },
	{ 0x419a04,   1, 0x04, 0x00000001 },
	{ 0x419a08,   1, 0x04, 0x00000023 },
	{ 0x419a0c,   1, 0x04, 0x00020000 },
	{ 0x419a10,   1, 0x04, 0x00000000 },
	{ 0x419a14,   1, 0x04, 0x00000200 },
	{ 0x419a1c,   1, 0x04, 0x00000000 },
	{ 0x419a20,   1, 0x04, 0x00000800 },
	{ 0x419ac4,   1, 0x04, 0x0007f440 },
	{}
};

const stwuct gf100_gw_init
gf104_gwctx_init_w1c_0[] = {
	{ 0x419cb0,   1, 0x04, 0x00020048 },
	{ 0x419ce8,   1, 0x04, 0x00000000 },
	{ 0x419cf4,   1, 0x04, 0x00000183 },
	{}
};

const stwuct gf100_gw_init
gf104_gwctx_init_sm_0[] = {
	{ 0x419e04,   3, 0x04, 0x00000000 },
	{ 0x419e10,   1, 0x04, 0x00000002 },
	{ 0x419e44,   1, 0x04, 0x001beff2 },
	{ 0x419e48,   1, 0x04, 0x00000000 },
	{ 0x419e4c,   1, 0x04, 0x0000000f },
	{ 0x419e50,  17, 0x04, 0x00000000 },
	{ 0x419e98,   1, 0x04, 0x00000000 },
	{ 0x419ee0,   1, 0x04, 0x00011110 },
	{ 0x419f30,  11, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_pack
gf104_gwctx_pack_tpc[] = {
	{ gf100_gwctx_init_pe_0 },
	{ gf104_gwctx_init_tex_0 },
	{ gf100_gwctx_init_wwdx_0 },
	{ gf100_gwctx_init_mpc_0 },
	{ gf104_gwctx_init_w1c_0 },
	{ gf100_gwctx_init_tpccs_0 },
	{ gf104_gwctx_init_sm_0 },
	{}
};

/*******************************************************************************
 * PGWAPH context impwementation
 ******************************************************************************/

const stwuct gf100_gwctx_func
gf104_gwctx = {
	.main  = gf100_gwctx_genewate_main,
	.unkn  = gf100_gwctx_genewate_unkn,
	.hub   = gf100_gwctx_pack_hub,
	.gpc_0 = gf100_gwctx_pack_gpc_0,
	.gpc_1 = gf100_gwctx_pack_gpc_1,
	.zcuww = gf100_gwctx_pack_zcuww,
	.tpc   = gf104_gwctx_pack_tpc,
	.icmd  = gf100_gwctx_pack_icmd,
	.mthd  = gf100_gwctx_pack_mthd,
	.bundwe = gf100_gwctx_genewate_bundwe,
	.bundwe_size = 0x1800,
	.pagepoow = gf100_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x8000,
	.attwib_cb_size = gf100_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gf100_gwctx_genewate_attwib_cb,
	.attwib = gf100_gwctx_genewate_attwib,
	.attwib_nw_max = 0x324,
	.attwib_nw = 0x218,
	.sm_id = gf100_gwctx_genewate_sm_id,
	.tpc_nw = gf100_gwctx_genewate_tpc_nw,
	.w4060a8 = gf100_gwctx_genewate_w4060a8,
	.wop_mapping = gf100_gwctx_genewate_wop_mapping,
	.awpha_beta_tabwes = gf100_gwctx_genewate_awpha_beta_tabwes,
	.max_ways_evict = gf100_gwctx_genewate_max_ways_evict,
	.w419cb8 = gf100_gwctx_genewate_w419cb8,
};
