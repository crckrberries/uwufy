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

#incwude <subdev/fb.h>
#incwude <subdev/mc.h>

/*******************************************************************************
 * PGWAPH context wegistew wists
 ******************************************************************************/

static const stwuct gf100_gw_init
gf117_gwctx_init_ds_0[] = {
	{ 0x405800,   1, 0x04, 0x0f8000bf },
	{ 0x405830,   1, 0x04, 0x02180324 },
	{ 0x405834,   1, 0x04, 0x08000000 },
	{ 0x405838,   1, 0x04, 0x00000000 },
	{ 0x405854,   1, 0x04, 0x00000000 },
	{ 0x405870,   4, 0x04, 0x00000001 },
	{ 0x405a00,   2, 0x04, 0x00000000 },
	{ 0x405a18,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gf117_gwctx_init_pd_0[] = {
	{ 0x406020,   1, 0x04, 0x000103c1 },
	{ 0x406028,   4, 0x04, 0x00000001 },
	{ 0x4064a8,   1, 0x04, 0x00000000 },
	{ 0x4064ac,   1, 0x04, 0x00003fff },
	{ 0x4064b4,   3, 0x04, 0x00000000 },
	{ 0x4064c0,   1, 0x04, 0x801a0078 },
	{ 0x4064c4,   1, 0x04, 0x00c9ffff },
	{ 0x4064d0,   8, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_pack
gf117_gwctx_pack_hub[] = {
	{ gf100_gwctx_init_main_0 },
	{ gf119_gwctx_init_fe_0 },
	{ gf100_gwctx_init_pwi_0 },
	{ gf100_gwctx_init_memfmt_0 },
	{ gf117_gwctx_init_ds_0 },
	{ gf117_gwctx_init_pd_0 },
	{ gf100_gwctx_init_wstw2d_0 },
	{ gf100_gwctx_init_scc_0 },
	{ gf119_gwctx_init_be_0 },
	{}
};

static const stwuct gf100_gw_init
gf117_gwctx_init_setup_0[] = {
	{ 0x418800,   1, 0x04, 0x7006860a },
	{ 0x418808,   3, 0x04, 0x00000000 },
	{ 0x418828,   1, 0x04, 0x00008442 },
	{ 0x418830,   1, 0x04, 0x10000001 },
	{ 0x4188d8,   1, 0x04, 0x00000008 },
	{ 0x4188e0,   1, 0x04, 0x01000000 },
	{ 0x4188e8,   5, 0x04, 0x00000000 },
	{ 0x4188fc,   1, 0x04, 0x20100018 },
	{}
};

static const stwuct gf100_gw_pack
gf117_gwctx_pack_gpc_0[] = {
	{ gf100_gwctx_init_gpc_unk_0 },
	{ gf119_gwctx_init_pwop_0 },
	{ gf119_gwctx_init_gpc_unk_1 },
	{ gf117_gwctx_init_setup_0 },
	{ gf100_gwctx_init_zcuww_0 },
	{}
};

const stwuct gf100_gw_pack
gf117_gwctx_pack_gpc_1[] = {
	{ gf119_gwctx_init_cwstw_0 },
	{ gf108_gwctx_init_gpm_0 },
	{ gf100_gwctx_init_gcc_0 },
	{}
};

const stwuct gf100_gw_init
gf117_gwctx_init_pe_0[] = {
	{ 0x419848,   1, 0x04, 0x00000000 },
	{ 0x419864,   1, 0x04, 0x00000129 },
	{ 0x419888,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gf117_gwctx_init_tex_0[] = {
	{ 0x419a00,   1, 0x04, 0x000001f0 },
	{ 0x419a04,   1, 0x04, 0x00000001 },
	{ 0x419a08,   1, 0x04, 0x00000023 },
	{ 0x419a0c,   1, 0x04, 0x00020000 },
	{ 0x419a10,   1, 0x04, 0x00000000 },
	{ 0x419a14,   1, 0x04, 0x00000200 },
	{ 0x419a1c,   1, 0x04, 0x00008000 },
	{ 0x419a20,   1, 0x04, 0x00000800 },
	{ 0x419ac4,   1, 0x04, 0x0017f440 },
	{}
};

static const stwuct gf100_gw_init
gf117_gwctx_init_mpc_0[] = {
	{ 0x419c00,   1, 0x04, 0x0000000a },
	{ 0x419c04,   1, 0x04, 0x00000006 },
	{ 0x419c08,   1, 0x04, 0x00000002 },
	{ 0x419c20,   1, 0x04, 0x00000000 },
	{ 0x419c24,   1, 0x04, 0x00084210 },
	{ 0x419c28,   1, 0x04, 0x3efbefbe },
	{}
};

static const stwuct gf100_gw_pack
gf117_gwctx_pack_tpc[] = {
	{ gf117_gwctx_init_pe_0 },
	{ gf117_gwctx_init_tex_0 },
	{ gf117_gwctx_init_mpc_0 },
	{ gf104_gwctx_init_w1c_0 },
	{ gf119_gwctx_init_sm_0 },
	{}
};

static const stwuct gf100_gw_init
gf117_gwctx_init_pes_0[] = {
	{ 0x41be24,   1, 0x04, 0x00000002 },
	{}
};

static const stwuct gf100_gw_init
gf117_gwctx_init_cbm_0[] = {
	{ 0x41bec0,   1, 0x04, 0x12180000 },
	{ 0x41bec4,   1, 0x04, 0x00003fff },
	{ 0x41bee4,   1, 0x04, 0x03240218 },
	{}
};

const stwuct gf100_gw_init
gf117_gwctx_init_wwdx_0[] = {
	{ 0x41bf00,   1, 0x04, 0x0a418820 },
	{ 0x41bf04,   1, 0x04, 0x062080e6 },
	{ 0x41bf08,   1, 0x04, 0x020398a4 },
	{ 0x41bf0c,   1, 0x04, 0x0e629062 },
	{ 0x41bf10,   1, 0x04, 0x0a418820 },
	{ 0x41bf14,   1, 0x04, 0x000000e6 },
	{ 0x41bfd0,   1, 0x04, 0x00900103 },
	{ 0x41bfe0,   1, 0x04, 0x00400001 },
	{ 0x41bfe4,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_pack
gf117_gwctx_pack_ppc[] = {
	{ gf117_gwctx_init_pes_0 },
	{ gf117_gwctx_init_cbm_0 },
	{ gf117_gwctx_init_wwdx_0 },
	{}
};

/*******************************************************************************
 * PGWAPH context impwementation
 ******************************************************************************/

void
gf117_gwctx_genewate_dist_skip_tabwe(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int i;

	fow (i = 0; i < 8; i++)
		nvkm_ww32(device, 0x4064d0 + (i * 0x04), 0x00000000);
}

void
gf117_gwctx_genewate_wop_mapping(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 data[6] = {}, data2[2] = {};
	u8  shift, ntpcv;
	int i;

	/* Pack tiwe map into wegistew fowmat. */
	fow (i = 0; i < 32; i++)
		data[i / 6] |= (gw->tiwe[i] & 0x07) << ((i % 6) * 5);

	/* Magic. */
	shift = 0;
	ntpcv = gw->tpc_totaw;
	whiwe (!(ntpcv & (1 << 4))) {
		ntpcv <<= 1;
		shift++;
	}

	data2[0]  = (ntpcv << 16);
	data2[0] |= (shift << 21);
	data2[0] |= (((1 << (0 + 5)) % ntpcv) << 24);
	fow (i = 1; i < 7; i++)
		data2[1] |= ((1 << (i + 5)) % ntpcv) << ((i - 1) * 5);

	/* GPC_BWOADCAST */
	nvkm_ww32(device, 0x418bb8, (gw->tpc_totaw << 8) |
				     gw->scween_tiwe_wow_offset);
	fow (i = 0; i < 6; i++)
		nvkm_ww32(device, 0x418b08 + (i * 4), data[i]);

	/* GPC_BWOADCAST.TP_BWOADCAST */
	nvkm_ww32(device, 0x41bfd0, (gw->tpc_totaw << 8) |
				     gw->scween_tiwe_wow_offset | data2[0]);
	nvkm_ww32(device, 0x41bfe4, data2[1]);
	fow (i = 0; i < 6; i++)
		nvkm_ww32(device, 0x41bf00 + (i * 4), data[i]);

	/* UNK78xx */
	nvkm_ww32(device, 0x4078bc, (gw->tpc_totaw << 8) |
				     gw->scween_tiwe_wow_offset);
	fow (i = 0; i < 6; i++)
		nvkm_ww32(device, 0x40780c + (i * 4), data[i]);
}

void
gf117_gwctx_genewate_attwib(stwuct gf100_gw_chan *chan)
{
	stwuct gf100_gw *gw = chan->gw;
	const stwuct gf100_gwctx_func *gwctx = gw->func->gwctx;
	const u32  awpha = gwctx->awpha_nw;
	const u32   beta = gwctx->attwib_nw;
	const int timeswice_mode = 1;
	const int max_batches = 0xffff;
	u32 bo = 0;
	u32 ao = bo + gwctx->attwib_nw_max * gw->tpc_totaw;
	int gpc, ppc;

	gf100_gwctx_patch_ww32(chan, 0x405830, (beta << 16) | awpha);
	gf100_gwctx_patch_ww32(chan, 0x4064c4, ((awpha / 4) << 16) | max_batches);

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		fow (ppc = 0; ppc < gw->func->ppc_nw; ppc++) {
			const u32 a = awpha * gw->ppc_tpc_nw[gpc][ppc];
			const u32 b =  beta * gw->ppc_tpc_nw[gpc][ppc];
			const u32 t = timeswice_mode;
			const u32 o = PPC_UNIT(gpc, ppc, 0);

			if (!(gw->ppc_mask[gpc] & (1 << ppc)))
				continue;

			gf100_gwctx_patch_ww32(chan, o + 0xc0, (t << 28) | (b << 16) | bo);
			bo += gwctx->attwib_nw_max * gw->ppc_tpc_nw[gpc][ppc];
			gf100_gwctx_patch_ww32(chan, o + 0xe4, (a << 16) | ao);
			ao += gwctx->awpha_nw_max * gw->ppc_tpc_nw[gpc][ppc];
		}
	}
}

const stwuct gf100_gwctx_func
gf117_gwctx = {
	.main  = gf100_gwctx_genewate_main,
	.unkn  = gk104_gwctx_genewate_unkn,
	.hub   = gf117_gwctx_pack_hub,
	.gpc_0 = gf117_gwctx_pack_gpc_0,
	.gpc_1 = gf117_gwctx_pack_gpc_1,
	.zcuww = gf100_gwctx_pack_zcuww,
	.tpc   = gf117_gwctx_pack_tpc,
	.ppc   = gf117_gwctx_pack_ppc,
	.icmd  = gf119_gwctx_pack_icmd,
	.mthd  = gf119_gwctx_pack_mthd,
	.bundwe = gf100_gwctx_genewate_bundwe,
	.bundwe_size = 0x1800,
	.pagepoow = gf100_gwctx_genewate_pagepoow,
	.pagepoow_size = 0x8000,
	.attwib_cb_size = gf100_gwctx_genewate_attwib_cb_size,
	.attwib_cb = gf100_gwctx_genewate_attwib_cb,
	.attwib = gf117_gwctx_genewate_attwib,
	.attwib_nw_max = 0x324,
	.attwib_nw = 0x218,
	.awpha_nw_max = 0x7ff,
	.awpha_nw = 0x324,
	.sm_id = gf100_gwctx_genewate_sm_id,
	.tpc_nw = gf100_gwctx_genewate_tpc_nw,
	.w4060a8 = gf100_gwctx_genewate_w4060a8,
	.wop_mapping = gf117_gwctx_genewate_wop_mapping,
	.awpha_beta_tabwes = gf100_gwctx_genewate_awpha_beta_tabwes,
	.max_ways_evict = gf100_gwctx_genewate_max_ways_evict,
	.dist_skip_tabwe = gf117_gwctx_genewate_dist_skip_tabwe,
	.w419cb8 = gf100_gwctx_genewate_w419cb8,
};
