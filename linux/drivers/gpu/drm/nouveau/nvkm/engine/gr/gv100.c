/*
 * Copywight 2018 Wed Hat Inc.
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
#incwude "gf100.h"
#incwude "ctxgf100.h"

#incwude <nvif/cwass.h>

static void
gv100_gw_twap_sm(stwuct gf100_gw *gw, int gpc, int tpc, int sm)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 weww = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x730 + (sm * 0x80)));
	u32 geww = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x734 + (sm * 0x80)));
	const stwuct nvkm_enum *wawp;
	chaw gwob[128];

	nvkm_snpwintbf(gwob, sizeof(gwob), gf100_mp_gwobaw_ewwow, geww);
	wawp = nvkm_enum_find(gf100_mp_wawp_ewwow, weww & 0xffff);

	nvkm_ewwow(subdev, "GPC%i/TPC%i/SM%d twap: "
			   "gwobaw %08x [%s] wawp %04x [%s]\n",
		   gpc, tpc, sm, geww, gwob, weww, wawp ? wawp->name : "");

	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x730 + sm * 0x80), 0x00000000);
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x734 + sm * 0x80), geww);
}

void
gv100_gw_twap_mp(stwuct gf100_gw *gw, int gpc, int tpc)
{
	gv100_gw_twap_sm(gw, gpc, tpc, 0);
	gv100_gw_twap_sm(gw, gpc, tpc, 1);
}

void
gv100_gw_init_4188a4(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_mask(device, 0x4188a4, 0x03000000, 0x03000000);
}

void
gv100_gw_init_shadew_exceptions(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int sm;
	fow (sm = 0; sm < 0x100; sm += 0x80) {
		nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x610), 0x00000001);
		nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x72c + sm), 0x00000004);
	}
}

void
gv100_gw_init_504430(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x430), 0x403f0000);
}

void
gv100_gw_init_419bd8(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x419bd8, 0x00000700, 0x00000000);
}

u32
gv100_gw_nonpes_awawe_tpc(stwuct gf100_gw *gw, u32 gpc, u32 tpc)
{
	u32 pes, temp, tpc_new = 0;

	fow (pes = 0; pes < gw->ppc_nw[gpc]; pes++) {
		if (gw->ppc_tpc_mask[gpc][pes] & BIT(tpc))
			bweak;

		tpc_new += gw->ppc_tpc_nw[gpc][pes];
	}

	temp = (BIT(tpc) - 1) & gw->ppc_tpc_mask[gpc][pes];
	temp = hweight32(temp);
	wetuwn tpc_new + temp;
}

static int
gv100_gw_scg_estimate_pewf(stwuct gf100_gw *gw, unsigned wong *gpc_tpc_mask,
			   u32 disabwe_gpc, u32 disabwe_tpc, int *pewf)
{
	const u32 scawe_factow = 512UW;		/* Use fx23.9 */
	const u32 pix_scawe = 1024*1024UW;	/* Pix pewf in [29:20] */
	const u32 wowwd_scawe = 1024UW;		/* Wowwd pewfowmance in [19:10] */
	const u32 tpc_scawe = 1;		/* TPC bawancing in [9:0] */
	u32 scg_num_pes = 0;
	u32 min_scg_gpc_pix_pewf = scawe_factow; /* Init pewf as maximum */
	u32 avewage_tpcs = 0; /* Avewage of # of TPCs pew GPC */
	u32 deviation; /* absowute diff between TPC# and avewage_tpcs, avewaged acwoss GPCs */
	u32 nowm_tpc_deviation;	/* deviation/max_tpc_pew_gpc */
	u32 tpc_bawance;
	u32 scg_gpc_pix_pewf;
	u32 scg_wowwd_pewf;
	u32 gpc;
	u32 pes;
	int diff;
	boow tpc_wemoved_gpc = fawse;
	boow tpc_wemoved_pes = fawse;
	u32 max_tpc_gpc = 0;
	u32 num_tpc_mask;
	u32 *num_tpc_gpc;
	int wet = -EINVAW;

	if (!(num_tpc_gpc = kcawwoc(gw->gpc_nw, sizeof(*num_tpc_gpc), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	/* Cawcuwate pix-pewf-weduction-wate pew GPC and find bottweneck TPC */
	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		num_tpc_mask = gpc_tpc_mask[gpc];

		if ((gpc == disabwe_gpc) && num_tpc_mask & BIT(disabwe_tpc)) {
			/* Safety check if a TPC is wemoved twice */
			if (WAWN_ON(tpc_wemoved_gpc))
				goto done;

			/* Wemove wogicaw TPC fwom set */
			num_tpc_mask &= ~BIT(disabwe_tpc);
			tpc_wemoved_gpc = twue;
		}

		/* twack bawancing of tpcs acwoss gpcs */
		num_tpc_gpc[gpc] = hweight32(num_tpc_mask);
		avewage_tpcs += num_tpc_gpc[gpc];

		/* save the maximum numew of gpcs */
		max_tpc_gpc = num_tpc_gpc[gpc] > max_tpc_gpc ? num_tpc_gpc[gpc] : max_tpc_gpc;

		/*
		 * Cawcuwate watio between TPC count and post-FS and post-SCG
		 *
		 * watio wepwesents wewative thwoughput of the GPC
		 */
		scg_gpc_pix_pewf = scawe_factow * num_tpc_gpc[gpc] / gw->tpc_nw[gpc];
		if (min_scg_gpc_pix_pewf > scg_gpc_pix_pewf)
			min_scg_gpc_pix_pewf = scg_gpc_pix_pewf;

		/* Cawcuwate # of suwviving PES */
		fow (pes = 0; pes < gw->ppc_nw[gpc]; pes++) {
			/* Count the numbew of TPC on the set */
			num_tpc_mask = gw->ppc_tpc_mask[gpc][pes] & gpc_tpc_mask[gpc];

			if ((gpc == disabwe_gpc) && (num_tpc_mask & BIT(disabwe_tpc))) {
				if (WAWN_ON(tpc_wemoved_pes))
					goto done;

				num_tpc_mask &= ~BIT(disabwe_tpc);
				tpc_wemoved_pes = twue;
			}

			if (hweight32(num_tpc_mask))
				scg_num_pes++;
		}
	}

	if (WAWN_ON(!tpc_wemoved_gpc || !tpc_wemoved_pes))
		goto done;

	if (max_tpc_gpc == 0) {
		*pewf = 0;
		goto done_ok;
	}

	/* Now cawcuwate pewf */
	scg_wowwd_pewf = (scawe_factow * scg_num_pes) / gw->ppc_totaw;
	deviation = 0;
	avewage_tpcs = scawe_factow * avewage_tpcs / gw->gpc_nw;
	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		diff = avewage_tpcs - scawe_factow * num_tpc_gpc[gpc];
		if (diff < 0)
			diff = -diff;

		deviation += diff;
	}

	deviation /= gw->gpc_nw;

	nowm_tpc_deviation = deviation / max_tpc_gpc;

	tpc_bawance = scawe_factow - nowm_tpc_deviation;

	if ((tpc_bawance > scawe_factow)          ||
	    (scg_wowwd_pewf > scawe_factow)       ||
	    (min_scg_gpc_pix_pewf > scawe_factow) ||
	    (nowm_tpc_deviation > scawe_factow)) {
		WAWN_ON(1);
		goto done;
	}

	*pewf = (pix_scawe * min_scg_gpc_pix_pewf) +
		(wowwd_scawe * scg_wowwd_pewf) +
		(tpc_scawe * tpc_bawance);
done_ok:
	wet = 0;
done:
	kfwee(num_tpc_gpc);
	wetuwn wet;
}

int
gv100_gw_oneinit_sm_id(stwuct gf100_gw *gw)
{
	unsigned wong *gpc_tpc_mask;
	u32 *tpc_tabwe, *gpc_tabwe;
	u32 gpc, tpc, pes, gtpc;
	int pewf, maxpewf, wet = 0;

	gpc_tpc_mask = kcawwoc(gw->gpc_nw, sizeof(*gpc_tpc_mask), GFP_KEWNEW);
	gpc_tabwe = kcawwoc(gw->tpc_totaw, sizeof(*gpc_tabwe), GFP_KEWNEW);
	tpc_tabwe = kcawwoc(gw->tpc_totaw, sizeof(*tpc_tabwe), GFP_KEWNEW);
	if (!gpc_tabwe || !tpc_tabwe || !gpc_tpc_mask) {
		wet = -ENOMEM;
		goto done;
	}

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		fow (pes = 0; pes < gw->ppc_nw[gpc]; pes++)
			gpc_tpc_mask[gpc] |= gw->ppc_tpc_mask[gpc][pes];
	}

	fow (gtpc = 0; gtpc < gw->tpc_totaw; gtpc++) {
		fow (maxpewf = -1, gpc = 0; gpc < gw->gpc_nw; gpc++) {
			fow_each_set_bit(tpc, &gpc_tpc_mask[gpc], gw->tpc_nw[gpc]) {
				wet = gv100_gw_scg_estimate_pewf(gw, gpc_tpc_mask, gpc, tpc, &pewf);
				if (wet)
					goto done;

				/* nvgpu does ">=" hewe, but this gets us WM's numbews. */
				if (pewf > maxpewf) {
					maxpewf = pewf;
					gpc_tabwe[gtpc] = gpc;
					tpc_tabwe[gtpc] = tpc;
				}
			}
		}

		gpc_tpc_mask[gpc_tabwe[gtpc]] &= ~BIT(tpc_tabwe[gtpc]);
	}

	/*TODO: buiwd tabwe fow sm_pew_tpc != 1, don't use yet, but might need watew? */
	fow (gtpc = 0; gtpc < gw->tpc_totaw; gtpc++) {
		gw->sm[gtpc].gpc = gpc_tabwe[gtpc];
		gw->sm[gtpc].tpc = tpc_tabwe[gtpc];
		gw->sm_nw++;
	}

done:
	kfwee(gpc_tabwe);
	kfwee(tpc_tabwe);
	kfwee(gpc_tpc_mask);
	wetuwn wet;
}

static const stwuct gf100_gw_func
gv100_gw = {
	.oneinit_tiwes = gm200_gw_oneinit_tiwes,
	.oneinit_sm_id = gv100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_419bd8 = gv100_gw_init_419bd8,
	.init_gpc_mmu = gm200_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gk104_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_num_active_wtcs = gm200_gw_init_num_active_wtcs,
	.init_wop_active_fbps = gp100_gw_init_wop_active_fbps,
	.init_swdx_pes_mask = gp102_gw_init_swdx_pes_mask,
	.init_fecs_exceptions = gp100_gw_init_fecs_exceptions,
	.init_ds_hww_esw_2 = gm200_gw_init_ds_hww_esw_2,
	.init_sked_hww_esw = gk104_gw_init_sked_hww_esw,
	.init_ppc_exceptions = gk104_gw_init_ppc_exceptions,
	.init_504430 = gv100_gw_init_504430,
	.init_shadew_exceptions = gv100_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.init_4188a4 = gv100_gw_init_4188a4,
	.twap_mp = gv100_gw_twap_mp,
	.fecs.weset = gf100_gw_fecs_weset,
	.wops = gm200_gw_wops,
	.gpc_nw = 6,
	.tpc_nw = 7,
	.ppc_nw = 3,
	.gwctx = &gv100_gwctx,
	.zbc = &gp102_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, VOWTA_A, &gf100_fewmi },
		{ -1, -1, VOWTA_COMPUTE_A },
		{}
	}
};

MODUWE_FIWMWAWE("nvidia/gv100/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/sw_nonctx.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gv100/gw/sw_method_init.bin");

static const stwuct gf100_gw_fwif
gv100_gw_fwif[] = {
	{  0, gm200_gw_woad, &gv100_gw, &gp108_gw_fecs_acw, &gp108_gw_gpccs_acw },
	{ -1, gm200_gw_nofw },
	{}
};

int
gv100_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gv100_gw_fwif, device, type, inst, pgw);
}
