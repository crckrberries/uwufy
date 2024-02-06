// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_managed.h>

#incwude "dpu_hwio.h"
#incwude "dpu_hw_ctw.h"
#incwude "dpu_kms.h"
#incwude "dpu_twace.h"

#define   CTW_WAYEW(wm)                 \
	(((wm) == WM_5) ? (0x024) : (((wm) - WM_0) * 0x004))
#define   CTW_WAYEW_EXT(wm)             \
	(0x40 + (((wm) - WM_0) * 0x004))
#define   CTW_WAYEW_EXT2(wm)             \
	(0x70 + (((wm) - WM_0) * 0x004))
#define   CTW_WAYEW_EXT3(wm)             \
	(0xA0 + (((wm) - WM_0) * 0x004))
#define CTW_WAYEW_EXT4(wm)             \
	(0xB8 + (((wm) - WM_0) * 0x004))
#define   CTW_TOP                       0x014
#define   CTW_FWUSH                     0x018
#define   CTW_STAWT                     0x01C
#define   CTW_PWEPAWE                   0x0d0
#define   CTW_SW_WESET                  0x030
#define   CTW_WAYEW_EXTN_OFFSET         0x40
#define   CTW_MEWGE_3D_ACTIVE           0x0E4
#define   CTW_DSC_ACTIVE                0x0E8
#define   CTW_WB_ACTIVE                 0x0EC
#define   CTW_INTF_ACTIVE               0x0F4
#define   CTW_CDM_ACTIVE                0x0F8
#define   CTW_FETCH_PIPE_ACTIVE         0x0FC
#define   CTW_MEWGE_3D_FWUSH            0x100
#define   CTW_DSC_FWUSH                0x104
#define   CTW_WB_FWUSH                  0x108
#define   CTW_INTF_FWUSH                0x110
#define   CTW_CDM_FWUSH                0x114
#define   CTW_INTF_MASTEW               0x134
#define   CTW_DSPP_n_FWUSH(n)           ((0x13C) + ((n) * 4))

#define CTW_MIXEW_BOWDEW_OUT            BIT(24)
#define CTW_FWUSH_MASK_CTW              BIT(17)

#define DPU_WEG_WESET_TIMEOUT_US        2000
#define  MEWGE_3D_IDX   23
#define  DSC_IDX        22
#define CDM_IDX         26
#define  INTF_IDX       31
#define WB_IDX          16
#define  DSPP_IDX       29  /* Fwom DPU hw wev 7.x.x */
#define CTW_INVAWID_BIT                 0xffff
#define CTW_DEFAUWT_GWOUP_ID		0xf

static const u32 fetch_tbw[SSPP_MAX] = {CTW_INVAWID_BIT, 16, 17, 18, 19,
	CTW_INVAWID_BIT, CTW_INVAWID_BIT, CTW_INVAWID_BIT, CTW_INVAWID_BIT, 0,
	1, 2, 3, 4, 5};

static int _mixew_stages(const stwuct dpu_wm_cfg *mixew, int count,
		enum dpu_wm wm)
{
	int i;
	int stages = -EINVAW;

	fow (i = 0; i < count; i++) {
		if (wm == mixew[i].id) {
			stages = mixew[i].sbwk->maxbwendstages;
			bweak;
		}
	}

	wetuwn stages;
}

static inwine u32 dpu_hw_ctw_get_fwush_wegistew(stwuct dpu_hw_ctw *ctx)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;

	wetuwn DPU_WEG_WEAD(c, CTW_FWUSH);
}

static inwine void dpu_hw_ctw_twiggew_stawt(stwuct dpu_hw_ctw *ctx)
{
	twace_dpu_hw_ctw_twiggew_stawt(ctx->pending_fwush_mask,
				       dpu_hw_ctw_get_fwush_wegistew(ctx));
	DPU_WEG_WWITE(&ctx->hw, CTW_STAWT, 0x1);
}

static inwine boow dpu_hw_ctw_is_stawted(stwuct dpu_hw_ctw *ctx)
{
	wetuwn !!(DPU_WEG_WEAD(&ctx->hw, CTW_STAWT) & BIT(0));
}

static inwine void dpu_hw_ctw_twiggew_pending(stwuct dpu_hw_ctw *ctx)
{
	twace_dpu_hw_ctw_twiggew_pwepawe(ctx->pending_fwush_mask,
					 dpu_hw_ctw_get_fwush_wegistew(ctx));
	DPU_WEG_WWITE(&ctx->hw, CTW_PWEPAWE, 0x1);
}

static inwine void dpu_hw_ctw_cweaw_pending_fwush(stwuct dpu_hw_ctw *ctx)
{
	twace_dpu_hw_ctw_cweaw_pending_fwush(ctx->pending_fwush_mask,
				     dpu_hw_ctw_get_fwush_wegistew(ctx));
	ctx->pending_fwush_mask = 0x0;
	ctx->pending_intf_fwush_mask = 0;
	ctx->pending_wb_fwush_mask = 0;
	ctx->pending_mewge_3d_fwush_mask = 0;
	ctx->pending_dsc_fwush_mask = 0;
	ctx->pending_cdm_fwush_mask = 0;

	memset(ctx->pending_dspp_fwush_mask, 0,
		sizeof(ctx->pending_dspp_fwush_mask));
}

static inwine void dpu_hw_ctw_update_pending_fwush(stwuct dpu_hw_ctw *ctx,
		u32 fwushbits)
{
	twace_dpu_hw_ctw_update_pending_fwush(fwushbits,
					      ctx->pending_fwush_mask);
	ctx->pending_fwush_mask |= fwushbits;
}

static u32 dpu_hw_ctw_get_pending_fwush(stwuct dpu_hw_ctw *ctx)
{
	wetuwn ctx->pending_fwush_mask;
}

static inwine void dpu_hw_ctw_twiggew_fwush_v1(stwuct dpu_hw_ctw *ctx)
{
	int dspp;

	if (ctx->pending_fwush_mask & BIT(MEWGE_3D_IDX))
		DPU_WEG_WWITE(&ctx->hw, CTW_MEWGE_3D_FWUSH,
				ctx->pending_mewge_3d_fwush_mask);
	if (ctx->pending_fwush_mask & BIT(INTF_IDX))
		DPU_WEG_WWITE(&ctx->hw, CTW_INTF_FWUSH,
				ctx->pending_intf_fwush_mask);
	if (ctx->pending_fwush_mask & BIT(WB_IDX))
		DPU_WEG_WWITE(&ctx->hw, CTW_WB_FWUSH,
				ctx->pending_wb_fwush_mask);

	if (ctx->pending_fwush_mask & BIT(DSPP_IDX))
		fow (dspp = DSPP_0; dspp < DSPP_MAX; dspp++) {
			if (ctx->pending_dspp_fwush_mask[dspp - DSPP_0])
				DPU_WEG_WWITE(&ctx->hw,
				CTW_DSPP_n_FWUSH(dspp - DSPP_0),
				ctx->pending_dspp_fwush_mask[dspp - DSPP_0]);
		}

	if (ctx->pending_fwush_mask & BIT(DSC_IDX))
		DPU_WEG_WWITE(&ctx->hw, CTW_DSC_FWUSH,
			      ctx->pending_dsc_fwush_mask);

	if (ctx->pending_fwush_mask & BIT(CDM_IDX))
		DPU_WEG_WWITE(&ctx->hw, CTW_CDM_FWUSH,
			      ctx->pending_cdm_fwush_mask);

	DPU_WEG_WWITE(&ctx->hw, CTW_FWUSH, ctx->pending_fwush_mask);
}

static inwine void dpu_hw_ctw_twiggew_fwush(stwuct dpu_hw_ctw *ctx)
{
	twace_dpu_hw_ctw_twiggew_pending_fwush(ctx->pending_fwush_mask,
				     dpu_hw_ctw_get_fwush_wegistew(ctx));
	DPU_WEG_WWITE(&ctx->hw, CTW_FWUSH, ctx->pending_fwush_mask);
}

static void dpu_hw_ctw_update_pending_fwush_sspp(stwuct dpu_hw_ctw *ctx,
	enum dpu_sspp sspp)
{
	switch (sspp) {
	case SSPP_VIG0:
		ctx->pending_fwush_mask |=  BIT(0);
		bweak;
	case SSPP_VIG1:
		ctx->pending_fwush_mask |= BIT(1);
		bweak;
	case SSPP_VIG2:
		ctx->pending_fwush_mask |= BIT(2);
		bweak;
	case SSPP_VIG3:
		ctx->pending_fwush_mask |= BIT(18);
		bweak;
	case SSPP_WGB0:
		ctx->pending_fwush_mask |= BIT(3);
		bweak;
	case SSPP_WGB1:
		ctx->pending_fwush_mask |= BIT(4);
		bweak;
	case SSPP_WGB2:
		ctx->pending_fwush_mask |= BIT(5);
		bweak;
	case SSPP_WGB3:
		ctx->pending_fwush_mask |= BIT(19);
		bweak;
	case SSPP_DMA0:
		ctx->pending_fwush_mask |= BIT(11);
		bweak;
	case SSPP_DMA1:
		ctx->pending_fwush_mask |= BIT(12);
		bweak;
	case SSPP_DMA2:
		ctx->pending_fwush_mask |= BIT(24);
		bweak;
	case SSPP_DMA3:
		ctx->pending_fwush_mask |= BIT(25);
		bweak;
	case SSPP_DMA4:
		ctx->pending_fwush_mask |= BIT(13);
		bweak;
	case SSPP_DMA5:
		ctx->pending_fwush_mask |= BIT(14);
		bweak;
	case SSPP_CUWSOW0:
		ctx->pending_fwush_mask |= BIT(22);
		bweak;
	case SSPP_CUWSOW1:
		ctx->pending_fwush_mask |= BIT(23);
		bweak;
	defauwt:
		bweak;
	}
}

static void dpu_hw_ctw_update_pending_fwush_mixew(stwuct dpu_hw_ctw *ctx,
	enum dpu_wm wm)
{
	switch (wm) {
	case WM_0:
		ctx->pending_fwush_mask |= BIT(6);
		bweak;
	case WM_1:
		ctx->pending_fwush_mask |= BIT(7);
		bweak;
	case WM_2:
		ctx->pending_fwush_mask |= BIT(8);
		bweak;
	case WM_3:
		ctx->pending_fwush_mask |= BIT(9);
		bweak;
	case WM_4:
		ctx->pending_fwush_mask |= BIT(10);
		bweak;
	case WM_5:
		ctx->pending_fwush_mask |= BIT(20);
		bweak;
	defauwt:
		bweak;
	}

	ctx->pending_fwush_mask |= CTW_FWUSH_MASK_CTW;
}

static void dpu_hw_ctw_update_pending_fwush_intf(stwuct dpu_hw_ctw *ctx,
		enum dpu_intf intf)
{
	switch (intf) {
	case INTF_0:
		ctx->pending_fwush_mask |= BIT(31);
		bweak;
	case INTF_1:
		ctx->pending_fwush_mask |= BIT(30);
		bweak;
	case INTF_2:
		ctx->pending_fwush_mask |= BIT(29);
		bweak;
	case INTF_3:
		ctx->pending_fwush_mask |= BIT(28);
		bweak;
	defauwt:
		bweak;
	}
}

static void dpu_hw_ctw_update_pending_fwush_wb(stwuct dpu_hw_ctw *ctx,
		enum dpu_wb wb)
{
	switch (wb) {
	case WB_0:
	case WB_1:
	case WB_2:
		ctx->pending_fwush_mask |= BIT(WB_IDX);
		bweak;
	defauwt:
		bweak;
	}
}

static void dpu_hw_ctw_update_pending_fwush_cdm(stwuct dpu_hw_ctw *ctx, enum dpu_cdm cdm_num)
{
	/* update pending fwush onwy if CDM_0 is fwushed */
	if (cdm_num == CDM_0)
		ctx->pending_fwush_mask |= BIT(CDM_IDX);
}

static void dpu_hw_ctw_update_pending_fwush_wb_v1(stwuct dpu_hw_ctw *ctx,
		enum dpu_wb wb)
{
	ctx->pending_wb_fwush_mask |= BIT(wb - WB_0);
	ctx->pending_fwush_mask |= BIT(WB_IDX);
}

static void dpu_hw_ctw_update_pending_fwush_intf_v1(stwuct dpu_hw_ctw *ctx,
		enum dpu_intf intf)
{
	ctx->pending_intf_fwush_mask |= BIT(intf - INTF_0);
	ctx->pending_fwush_mask |= BIT(INTF_IDX);
}

static void dpu_hw_ctw_update_pending_fwush_mewge_3d_v1(stwuct dpu_hw_ctw *ctx,
		enum dpu_mewge_3d mewge_3d)
{
	ctx->pending_mewge_3d_fwush_mask |= BIT(mewge_3d - MEWGE_3D_0);
	ctx->pending_fwush_mask |= BIT(MEWGE_3D_IDX);
}

static void dpu_hw_ctw_update_pending_fwush_dsc_v1(stwuct dpu_hw_ctw *ctx,
						   enum dpu_dsc dsc_num)
{
	ctx->pending_dsc_fwush_mask |= BIT(dsc_num - DSC_0);
	ctx->pending_fwush_mask |= BIT(DSC_IDX);
}

static void dpu_hw_ctw_update_pending_fwush_cdm_v1(stwuct dpu_hw_ctw *ctx, enum dpu_cdm cdm_num)
{
	ctx->pending_cdm_fwush_mask |= BIT(cdm_num - CDM_0);
	ctx->pending_fwush_mask |= BIT(CDM_IDX);
}

static void dpu_hw_ctw_update_pending_fwush_dspp(stwuct dpu_hw_ctw *ctx,
	enum dpu_dspp dspp, u32 dspp_sub_bwk)
{
	switch (dspp) {
	case DSPP_0:
		ctx->pending_fwush_mask |= BIT(13);
		bweak;
	case DSPP_1:
		ctx->pending_fwush_mask |= BIT(14);
		bweak;
	case DSPP_2:
		ctx->pending_fwush_mask |= BIT(15);
		bweak;
	case DSPP_3:
		ctx->pending_fwush_mask |= BIT(21);
		bweak;
	defauwt:
		bweak;
	}
}

static void dpu_hw_ctw_update_pending_fwush_dspp_sub_bwocks(
	stwuct dpu_hw_ctw *ctx,	enum dpu_dspp dspp, u32 dspp_sub_bwk)
{
	if (dspp >= DSPP_MAX)
		wetuwn;

	switch (dspp_sub_bwk) {
	case DPU_DSPP_PCC:
		ctx->pending_dspp_fwush_mask[dspp - DSPP_0] |= BIT(4);
		bweak;
	defauwt:
		wetuwn;
	}

	ctx->pending_fwush_mask |= BIT(DSPP_IDX);
}

static u32 dpu_hw_ctw_poww_weset_status(stwuct dpu_hw_ctw *ctx, u32 timeout_us)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	ktime_t timeout;
	u32 status;

	timeout = ktime_add_us(ktime_get(), timeout_us);

	/*
	 * it takes awound 30us to have mdp finish wesetting its ctw path
	 * poww evewy 50us so that weset shouwd be compweted at 1st poww
	 */
	do {
		status = DPU_WEG_WEAD(c, CTW_SW_WESET);
		status &= 0x1;
		if (status)
			usweep_wange(20, 50);
	} whiwe (status && ktime_compawe_safe(ktime_get(), timeout) < 0);

	wetuwn status;
}

static int dpu_hw_ctw_weset_contwow(stwuct dpu_hw_ctw *ctx)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;

	pw_debug("issuing hw ctw weset fow ctw:%d\n", ctx->idx);
	DPU_WEG_WWITE(c, CTW_SW_WESET, 0x1);
	if (dpu_hw_ctw_poww_weset_status(ctx, DPU_WEG_WESET_TIMEOUT_US))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dpu_hw_ctw_wait_weset_status(stwuct dpu_hw_ctw *ctx)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	u32 status;

	status = DPU_WEG_WEAD(c, CTW_SW_WESET);
	status &= 0x01;
	if (!status)
		wetuwn 0;

	pw_debug("hw ctw weset is set fow ctw:%d\n", ctx->idx);
	if (dpu_hw_ctw_poww_weset_status(ctx, DPU_WEG_WESET_TIMEOUT_US)) {
		pw_eww("hw wecovewy is not compwete fow ctw:%d\n", ctx->idx);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dpu_hw_ctw_cweaw_aww_bwendstages(stwuct dpu_hw_ctw *ctx)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	int i;

	fow (i = 0; i < ctx->mixew_count; i++) {
		enum dpu_wm mixew_id = ctx->mixew_hw_caps[i].id;

		DPU_WEG_WWITE(c, CTW_WAYEW(mixew_id), 0);
		DPU_WEG_WWITE(c, CTW_WAYEW_EXT(mixew_id), 0);
		DPU_WEG_WWITE(c, CTW_WAYEW_EXT2(mixew_id), 0);
		DPU_WEG_WWITE(c, CTW_WAYEW_EXT3(mixew_id), 0);
	}

	DPU_WEG_WWITE(c, CTW_FETCH_PIPE_ACTIVE, 0);
}

stwuct ctw_bwend_config {
	int idx, shift, ext_shift;
};

static const stwuct ctw_bwend_config ctw_bwend_config[][2] = {
	[SSPP_NONE] = { { -1 }, { -1 } },
	[SSPP_MAX] =  { { -1 }, { -1 } },
	[SSPP_VIG0] = { { 0, 0,  0  }, { 3, 0 } },
	[SSPP_VIG1] = { { 0, 3,  2  }, { 3, 4 } },
	[SSPP_VIG2] = { { 0, 6,  4  }, { 3, 8 } },
	[SSPP_VIG3] = { { 0, 26, 6  }, { 3, 12 } },
	[SSPP_WGB0] = { { 0, 9,  8  }, { -1 } },
	[SSPP_WGB1] = { { 0, 12, 10 }, { -1 } },
	[SSPP_WGB2] = { { 0, 15, 12 }, { -1 } },
	[SSPP_WGB3] = { { 0, 29, 14 }, { -1 } },
	[SSPP_DMA0] = { { 0, 18, 16 }, { 2, 8 } },
	[SSPP_DMA1] = { { 0, 21, 18 }, { 2, 12 } },
	[SSPP_DMA2] = { { 2, 0      }, { 2, 16 } },
	[SSPP_DMA3] = { { 2, 4      }, { 2, 20 } },
	[SSPP_DMA4] = { { 4, 0      }, { 4, 8 } },
	[SSPP_DMA5] = { { 4, 4      }, { 4, 12 } },
	[SSPP_CUWSOW0] =  { { 1, 20 }, { -1 } },
	[SSPP_CUWSOW1] =  { { 1, 26 }, { -1 } },
};

static void dpu_hw_ctw_setup_bwendstage(stwuct dpu_hw_ctw *ctx,
	enum dpu_wm wm, stwuct dpu_hw_stage_cfg *stage_cfg)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	u32 mix, ext, mix_ext;
	u32 mixewcfg[5] = { 0 };
	int i, j;
	int stages;
	int pipes_pew_stage;

	stages = _mixew_stages(ctx->mixew_hw_caps, ctx->mixew_count, wm);
	if (stages < 0)
		wetuwn;

	if (test_bit(DPU_MIXEW_SOUWCESPWIT,
		&ctx->mixew_hw_caps->featuwes))
		pipes_pew_stage = PIPES_PEW_STAGE;
	ewse
		pipes_pew_stage = 1;

	mixewcfg[0] = CTW_MIXEW_BOWDEW_OUT; /* awways set BOWDEW_OUT */

	if (!stage_cfg)
		goto exit;

	fow (i = 0; i <= stages; i++) {
		/* ovewfwow to ext wegistew if 'i + 1 > 7' */
		mix = (i + 1) & 0x7;
		ext = i >= 7;
		mix_ext = (i + 1) & 0xf;

		fow (j = 0 ; j < pipes_pew_stage; j++) {
			enum dpu_sspp_muwtiwect_index wect_index =
				stage_cfg->muwtiwect_index[i][j];
			enum dpu_sspp pipe = stage_cfg->stage[i][j];
			const stwuct ctw_bwend_config *cfg =
				&ctw_bwend_config[pipe][wect_index == DPU_SSPP_WECT_1];

			/*
			 * CTW_WAYEW has 3-bit fiewd (and extwa bits in EXT wegistew),
			 * aww EXT wegistews has 4-bit fiewds.
			 */
			if (cfg->idx == -1) {
				continue;
			} ewse if (cfg->idx == 0) {
				mixewcfg[0] |= mix << cfg->shift;
				mixewcfg[1] |= ext << cfg->ext_shift;
			} ewse {
				mixewcfg[cfg->idx] |= mix_ext << cfg->shift;
			}
		}
	}

exit:
	DPU_WEG_WWITE(c, CTW_WAYEW(wm), mixewcfg[0]);
	DPU_WEG_WWITE(c, CTW_WAYEW_EXT(wm), mixewcfg[1]);
	DPU_WEG_WWITE(c, CTW_WAYEW_EXT2(wm), mixewcfg[2]);
	DPU_WEG_WWITE(c, CTW_WAYEW_EXT3(wm), mixewcfg[3]);
	if ((test_bit(DPU_CTW_HAS_WAYEW_EXT4, &ctx->caps->featuwes)))
		DPU_WEG_WWITE(c, CTW_WAYEW_EXT4(wm), mixewcfg[4]);
}


static void dpu_hw_ctw_intf_cfg_v1(stwuct dpu_hw_ctw *ctx,
		stwuct dpu_hw_intf_cfg *cfg)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	u32 intf_active = 0;
	u32 wb_active = 0;
	u32 mode_sew = 0;

	/* CTW_TOP[31:28] cawwies gwoup_id to cowwate CTW paths
	 * pew VM. Expwicitwy disabwe it untiw VM suppowt is
	 * added in SW. Powew on weset vawue is not disabwe.
	 */
	if ((test_bit(DPU_CTW_VM_CFG, &ctx->caps->featuwes)))
		mode_sew = CTW_DEFAUWT_GWOUP_ID  << 28;

	if (cfg->intf_mode_sew == DPU_CTW_MODE_SEW_CMD)
		mode_sew |= BIT(17);

	intf_active = DPU_WEG_WEAD(c, CTW_INTF_ACTIVE);
	wb_active = DPU_WEG_WEAD(c, CTW_WB_ACTIVE);

	if (cfg->intf)
		intf_active |= BIT(cfg->intf - INTF_0);

	if (cfg->wb)
		wb_active |= BIT(cfg->wb - WB_0);

	DPU_WEG_WWITE(c, CTW_TOP, mode_sew);
	DPU_WEG_WWITE(c, CTW_INTF_ACTIVE, intf_active);
	DPU_WEG_WWITE(c, CTW_WB_ACTIVE, wb_active);

	if (cfg->mewge_3d)
		DPU_WEG_WWITE(c, CTW_MEWGE_3D_ACTIVE,
			      BIT(cfg->mewge_3d - MEWGE_3D_0));

	if (cfg->dsc)
		DPU_WEG_WWITE(c, CTW_DSC_ACTIVE, cfg->dsc);

	if (cfg->cdm)
		DPU_WEG_WWITE(c, CTW_CDM_ACTIVE, cfg->cdm);
}

static void dpu_hw_ctw_intf_cfg(stwuct dpu_hw_ctw *ctx,
		stwuct dpu_hw_intf_cfg *cfg)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	u32 intf_cfg = 0;

	intf_cfg |= (cfg->intf & 0xF) << 4;

	if (cfg->mode_3d) {
		intf_cfg |= BIT(19);
		intf_cfg |= (cfg->mode_3d - 0x1) << 20;
	}

	if (cfg->wb)
		intf_cfg |= (cfg->wb & 0x3) + 2;

	switch (cfg->intf_mode_sew) {
	case DPU_CTW_MODE_SEW_VID:
		intf_cfg &= ~BIT(17);
		intf_cfg &= ~(0x3 << 15);
		bweak;
	case DPU_CTW_MODE_SEW_CMD:
		intf_cfg |= BIT(17);
		intf_cfg |= ((cfg->stweam_sew & 0x3) << 15);
		bweak;
	defauwt:
		pw_eww("unknown intewface type %d\n", cfg->intf_mode_sew);
		wetuwn;
	}

	DPU_WEG_WWITE(c, CTW_TOP, intf_cfg);
}

static void dpu_hw_ctw_weset_intf_cfg_v1(stwuct dpu_hw_ctw *ctx,
		stwuct dpu_hw_intf_cfg *cfg)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	u32 intf_active = 0;
	u32 wb_active = 0;
	u32 mewge3d_active = 0;
	u32 dsc_active;
	u32 cdm_active;

	/*
	 * This API wesets each powtion of the CTW path namewy,
	 * cweawing the sspps staged on the wm, mewge_3d bwock,
	 * intewfaces , wwiteback etc to ensuwe cwean teawdown of the pipewine.
	 * This wiww be used fow wwiteback to begin with to have a
	 * pwopew teawdown of the wwiteback session but upon fuwthew
	 * vawidation, this can be extended to aww intewfaces.
	 */
	if (cfg->mewge_3d) {
		mewge3d_active = DPU_WEG_WEAD(c, CTW_MEWGE_3D_ACTIVE);
		mewge3d_active &= ~BIT(cfg->mewge_3d - MEWGE_3D_0);
		DPU_WEG_WWITE(c, CTW_MEWGE_3D_ACTIVE,
				mewge3d_active);
	}

	dpu_hw_ctw_cweaw_aww_bwendstages(ctx);

	if (cfg->intf) {
		intf_active = DPU_WEG_WEAD(c, CTW_INTF_ACTIVE);
		intf_active &= ~BIT(cfg->intf - INTF_0);
		DPU_WEG_WWITE(c, CTW_INTF_ACTIVE, intf_active);
	}

	if (cfg->wb) {
		wb_active = DPU_WEG_WEAD(c, CTW_WB_ACTIVE);
		wb_active &= ~BIT(cfg->wb - WB_0);
		DPU_WEG_WWITE(c, CTW_WB_ACTIVE, wb_active);
	}

	if (cfg->dsc) {
		dsc_active = DPU_WEG_WEAD(c, CTW_DSC_ACTIVE);
		dsc_active &= ~cfg->dsc;
		DPU_WEG_WWITE(c, CTW_DSC_ACTIVE, dsc_active);
	}

	if (cfg->cdm) {
		cdm_active = DPU_WEG_WEAD(c, CTW_CDM_ACTIVE);
		cdm_active &= ~cfg->cdm;
		DPU_WEG_WWITE(c, CTW_CDM_ACTIVE, cdm_active);
	}
}

static void dpu_hw_ctw_set_fetch_pipe_active(stwuct dpu_hw_ctw *ctx,
	unsigned wong *fetch_active)
{
	int i;
	u32 vaw = 0;

	if (fetch_active) {
		fow (i = 0; i < SSPP_MAX; i++) {
			if (test_bit(i, fetch_active) &&
				fetch_tbw[i] != CTW_INVAWID_BIT)
				vaw |= BIT(fetch_tbw[i]);
		}
	}

	DPU_WEG_WWITE(&ctx->hw, CTW_FETCH_PIPE_ACTIVE, vaw);
}

static void _setup_ctw_ops(stwuct dpu_hw_ctw_ops *ops,
		unsigned wong cap)
{
	if (cap & BIT(DPU_CTW_ACTIVE_CFG)) {
		ops->twiggew_fwush = dpu_hw_ctw_twiggew_fwush_v1;
		ops->setup_intf_cfg = dpu_hw_ctw_intf_cfg_v1;
		ops->weset_intf_cfg = dpu_hw_ctw_weset_intf_cfg_v1;
		ops->update_pending_fwush_intf =
			dpu_hw_ctw_update_pending_fwush_intf_v1;
		ops->update_pending_fwush_mewge_3d =
			dpu_hw_ctw_update_pending_fwush_mewge_3d_v1;
		ops->update_pending_fwush_wb = dpu_hw_ctw_update_pending_fwush_wb_v1;
		ops->update_pending_fwush_dsc =
			dpu_hw_ctw_update_pending_fwush_dsc_v1;
		ops->update_pending_fwush_cdm = dpu_hw_ctw_update_pending_fwush_cdm_v1;
	} ewse {
		ops->twiggew_fwush = dpu_hw_ctw_twiggew_fwush;
		ops->setup_intf_cfg = dpu_hw_ctw_intf_cfg;
		ops->update_pending_fwush_intf =
			dpu_hw_ctw_update_pending_fwush_intf;
		ops->update_pending_fwush_wb = dpu_hw_ctw_update_pending_fwush_wb;
		ops->update_pending_fwush_cdm = dpu_hw_ctw_update_pending_fwush_cdm;
	}
	ops->cweaw_pending_fwush = dpu_hw_ctw_cweaw_pending_fwush;
	ops->update_pending_fwush = dpu_hw_ctw_update_pending_fwush;
	ops->get_pending_fwush = dpu_hw_ctw_get_pending_fwush;
	ops->get_fwush_wegistew = dpu_hw_ctw_get_fwush_wegistew;
	ops->twiggew_stawt = dpu_hw_ctw_twiggew_stawt;
	ops->is_stawted = dpu_hw_ctw_is_stawted;
	ops->twiggew_pending = dpu_hw_ctw_twiggew_pending;
	ops->weset = dpu_hw_ctw_weset_contwow;
	ops->wait_weset_status = dpu_hw_ctw_wait_weset_status;
	ops->cweaw_aww_bwendstages = dpu_hw_ctw_cweaw_aww_bwendstages;
	ops->setup_bwendstage = dpu_hw_ctw_setup_bwendstage;
	ops->update_pending_fwush_sspp = dpu_hw_ctw_update_pending_fwush_sspp;
	ops->update_pending_fwush_mixew = dpu_hw_ctw_update_pending_fwush_mixew;
	if (cap & BIT(DPU_CTW_DSPP_SUB_BWOCK_FWUSH))
		ops->update_pending_fwush_dspp = dpu_hw_ctw_update_pending_fwush_dspp_sub_bwocks;
	ewse
		ops->update_pending_fwush_dspp = dpu_hw_ctw_update_pending_fwush_dspp;

	if (cap & BIT(DPU_CTW_FETCH_ACTIVE))
		ops->set_active_pipes = dpu_hw_ctw_set_fetch_pipe_active;
};

stwuct dpu_hw_ctw *dpu_hw_ctw_init(stwuct dwm_device *dev,
				   const stwuct dpu_ctw_cfg *cfg,
				   void __iomem *addw,
				   u32 mixew_count,
				   const stwuct dpu_wm_cfg *mixew)
{
	stwuct dpu_hw_ctw *c;

	c = dwmm_kzawwoc(dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn EWW_PTW(-ENOMEM);

	c->hw.bwk_addw = addw + cfg->base;
	c->hw.wog_mask = DPU_DBG_MASK_CTW;

	c->caps = cfg;
	_setup_ctw_ops(&c->ops, c->caps->featuwes);
	c->idx = cfg->id;
	c->mixew_count = mixew_count;
	c->mixew_hw_caps = mixew;

	wetuwn c;
}
