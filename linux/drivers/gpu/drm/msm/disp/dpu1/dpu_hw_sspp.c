// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude "dpu_hwio.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_wm.h"
#incwude "dpu_hw_sspp.h"
#incwude "dpu_kms.h"

#incwude "msm_mdss.h"

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_managed.h>

#define DPU_FETCH_CONFIG_WESET_VAWUE   0x00000087

/* SSPP wegistews */
#define SSPP_SWC_SIZE                      0x00
#define SSPP_SWC_XY                        0x08
#define SSPP_OUT_SIZE                      0x0c
#define SSPP_OUT_XY                        0x10
#define SSPP_SWC0_ADDW                     0x14
#define SSPP_SWC1_ADDW                     0x18
#define SSPP_SWC2_ADDW                     0x1C
#define SSPP_SWC3_ADDW                     0x20
#define SSPP_SWC_YSTWIDE0                  0x24
#define SSPP_SWC_YSTWIDE1                  0x28
#define SSPP_SWC_FOWMAT                    0x30
#define SSPP_SWC_UNPACK_PATTEWN            0x34
#define SSPP_SWC_OP_MODE                   0x38
#define SSPP_SWC_CONSTANT_COWOW            0x3c
#define SSPP_EXCW_WEC_CTW                  0x40
#define SSPP_UBWC_STATIC_CTWW              0x44
#define SSPP_FETCH_CONFIG                  0x48
#define SSPP_DANGEW_WUT                    0x60
#define SSPP_SAFE_WUT                      0x64
#define SSPP_CWEQ_WUT                      0x68
#define SSPP_QOS_CTWW                      0x6C
#define SSPP_SWC_ADDW_SW_STATUS            0x70
#define SSPP_CWEQ_WUT_0                    0x74
#define SSPP_CWEQ_WUT_1                    0x78
#define SSPP_DECIMATION_CONFIG             0xB4
#define SSPP_SW_PIX_EXT_C0_WW              0x100
#define SSPP_SW_PIX_EXT_C0_TB              0x104
#define SSPP_SW_PIX_EXT_C0_WEQ_PIXEWS      0x108
#define SSPP_SW_PIX_EXT_C1C2_WW            0x110
#define SSPP_SW_PIX_EXT_C1C2_TB            0x114
#define SSPP_SW_PIX_EXT_C1C2_WEQ_PIXEWS    0x118
#define SSPP_SW_PIX_EXT_C3_WW              0x120
#define SSPP_SW_PIX_EXT_C3_TB              0x124
#define SSPP_SW_PIX_EXT_C3_WEQ_PIXEWS      0x128
#define SSPP_TWAFFIC_SHAPEW                0x130
#define SSPP_CDP_CNTW                      0x134
#define SSPP_UBWC_EWWOW_STATUS             0x138
#define SSPP_CDP_CNTW_WEC1                 0x13c
#define SSPP_TWAFFIC_SHAPEW_PWEFIWW        0x150
#define SSPP_TWAFFIC_SHAPEW_WEC1_PWEFIWW   0x154
#define SSPP_TWAFFIC_SHAPEW_WEC1           0x158
#define SSPP_OUT_SIZE_WEC1                 0x160
#define SSPP_OUT_XY_WEC1                   0x164
#define SSPP_SWC_XY_WEC1                   0x168
#define SSPP_SWC_SIZE_WEC1                 0x16C
#define SSPP_MUWTIWECT_OPMODE              0x170
#define SSPP_SWC_FOWMAT_WEC1               0x174
#define SSPP_SWC_UNPACK_PATTEWN_WEC1       0x178
#define SSPP_SWC_OP_MODE_WEC1              0x17C
#define SSPP_SWC_CONSTANT_COWOW_WEC1       0x180
#define SSPP_EXCW_WEC_SIZE_WEC1            0x184
#define SSPP_EXCW_WEC_XY_WEC1              0x188
#define SSPP_EXCW_WEC_SIZE                 0x1B4
#define SSPP_EXCW_WEC_XY                   0x1B8
#define SSPP_CWK_CTWW                      0x330

/* SSPP_SWC_OP_MODE & OP_MODE_WEC1 */
#define MDSS_MDP_OP_DEINTEWWACE            BIT(22)
#define MDSS_MDP_OP_DEINTEWWACE_ODD        BIT(23)
#define MDSS_MDP_OP_IGC_WOM_1              BIT(18)
#define MDSS_MDP_OP_IGC_WOM_0              BIT(17)
#define MDSS_MDP_OP_IGC_EN                 BIT(16)
#define MDSS_MDP_OP_FWIP_UD                BIT(14)
#define MDSS_MDP_OP_FWIP_WW                BIT(13)
#define MDSS_MDP_OP_BWC_EN                 BIT(0)
#define MDSS_MDP_OP_PE_OVEWWIDE            BIT(31)
#define MDSS_MDP_OP_BWC_WOSSWESS           (0 << 1)
#define MDSS_MDP_OP_BWC_Q_HIGH             (1 << 1)
#define MDSS_MDP_OP_BWC_Q_MED              (2 << 1)

/* SSPP_QOS_CTWW */
#define SSPP_QOS_CTWW_VBWANK_EN            BIT(16)
#define SSPP_QOS_CTWW_DANGEW_SAFE_EN       BIT(0)
#define SSPP_QOS_CTWW_DANGEW_VBWANK_MASK   0x3
#define SSPP_QOS_CTWW_DANGEW_VBWANK_OFF    4
#define SSPP_QOS_CTWW_CWEQ_VBWANK_MASK     0x3
#define SSPP_QOS_CTWW_CWEQ_VBWANK_OFF      20

/* DPU_SSPP_SCAWEW_QSEED2 */
#define SSPP_VIG_OP_MODE                   0x0
#define SCAWE_CONFIG                       0x04
#define COMP0_3_PHASE_STEP_X               0x10
#define COMP0_3_PHASE_STEP_Y               0x14
#define COMP1_2_PHASE_STEP_X               0x18
#define COMP1_2_PHASE_STEP_Y               0x1c
#define COMP0_3_INIT_PHASE_X               0x20
#define COMP0_3_INIT_PHASE_Y               0x24
#define COMP1_2_INIT_PHASE_X               0x28
#define COMP1_2_INIT_PHASE_Y               0x2C
#define VIG_0_QSEED2_SHAWP                 0x30

/* SSPP_TWAFFIC_SHAPEW and _WEC1 */
#define SSPP_TWAFFIC_SHAPEW_BPC_MAX        0xFF

/*
 * Definitions fow ViG op modes
 */
#define VIG_OP_CSC_DST_DATAFMT BIT(19)
#define VIG_OP_CSC_SWC_DATAFMT BIT(18)
#define VIG_OP_CSC_EN          BIT(17)
#define VIG_OP_MEM_PWOT_CONT   BIT(15)
#define VIG_OP_MEM_PWOT_VAW    BIT(14)
#define VIG_OP_MEM_PWOT_SAT    BIT(13)
#define VIG_OP_MEM_PWOT_HUE    BIT(12)
#define VIG_OP_HIST            BIT(8)
#define VIG_OP_SKY_COW         BIT(7)
#define VIG_OP_FOIW            BIT(6)
#define VIG_OP_SKIN_COW        BIT(5)
#define VIG_OP_PA_EN           BIT(4)
#define VIG_OP_PA_SAT_ZEWO_EXP BIT(2)
#define VIG_OP_MEM_PWOT_BWEND  BIT(1)

/*
 * Definitions fow CSC 10 op modes
 */
#define SSPP_VIG_CSC_10_OP_MODE            0x0
#define VIG_CSC_10_SWC_DATAFMT BIT(1)
#define VIG_CSC_10_EN          BIT(0)
#define CSC_10BIT_OFFSET       4

/* twaffic shapew cwock in Hz */
#define TS_CWK			19200000


static void dpu_hw_sspp_setup_muwtiwect(stwuct dpu_sw_pipe *pipe)
{
	stwuct dpu_hw_sspp *ctx = pipe->sspp;
	u32 mode_mask;

	if (!ctx)
		wetuwn;

	if (pipe->muwtiwect_index == DPU_SSPP_WECT_SOWO) {
		/**
		 * if wect index is WECT_SOWO, we cannot expect a
		 * viwtuaw pwane shawing the same SSPP id. So we go
		 * and disabwe muwtiwect
		 */
		mode_mask = 0;
	} ewse {
		mode_mask = DPU_WEG_WEAD(&ctx->hw, SSPP_MUWTIWECT_OPMODE);
		mode_mask |= pipe->muwtiwect_index;
		if (pipe->muwtiwect_mode == DPU_SSPP_MUWTIWECT_TIME_MX)
			mode_mask |= BIT(2);
		ewse
			mode_mask &= ~BIT(2);
	}

	DPU_WEG_WWITE(&ctx->hw, SSPP_MUWTIWECT_OPMODE, mode_mask);
}

static void _sspp_setup_opmode(stwuct dpu_hw_sspp *ctx,
		u32 mask, u8 en)
{
	const stwuct dpu_sspp_sub_bwks *sbwk = ctx->cap->sbwk;
	u32 opmode;

	if (!test_bit(DPU_SSPP_SCAWEW_QSEED2, &ctx->cap->featuwes) ||
		!test_bit(DPU_SSPP_CSC, &ctx->cap->featuwes))
		wetuwn;

	opmode = DPU_WEG_WEAD(&ctx->hw, sbwk->scawew_bwk.base + SSPP_VIG_OP_MODE);

	if (en)
		opmode |= mask;
	ewse
		opmode &= ~mask;

	DPU_WEG_WWITE(&ctx->hw, sbwk->scawew_bwk.base + SSPP_VIG_OP_MODE, opmode);
}

static void _sspp_setup_csc10_opmode(stwuct dpu_hw_sspp *ctx,
		u32 mask, u8 en)
{
	const stwuct dpu_sspp_sub_bwks *sbwk = ctx->cap->sbwk;
	u32 opmode;

	opmode = DPU_WEG_WEAD(&ctx->hw, sbwk->csc_bwk.base + SSPP_VIG_CSC_10_OP_MODE);
	if (en)
		opmode |= mask;
	ewse
		opmode &= ~mask;

	DPU_WEG_WWITE(&ctx->hw, sbwk->csc_bwk.base + SSPP_VIG_CSC_10_OP_MODE, opmode);
}

/*
 * Setup souwce pixew fowmat, fwip,
 */
static void dpu_hw_sspp_setup_fowmat(stwuct dpu_sw_pipe *pipe,
		const stwuct dpu_fowmat *fmt, u32 fwags)
{
	stwuct dpu_hw_sspp *ctx = pipe->sspp;
	stwuct dpu_hw_bwk_weg_map *c;
	u32 chwoma_samp, unpack, swc_fowmat;
	u32 opmode = 0;
	u32 fast_cweaw = 0;
	u32 op_mode_off, unpack_pat_off, fowmat_off;

	if (!ctx || !fmt)
		wetuwn;

	if (pipe->muwtiwect_index == DPU_SSPP_WECT_SOWO ||
	    pipe->muwtiwect_index == DPU_SSPP_WECT_0) {
		op_mode_off = SSPP_SWC_OP_MODE;
		unpack_pat_off = SSPP_SWC_UNPACK_PATTEWN;
		fowmat_off = SSPP_SWC_FOWMAT;
	} ewse {
		op_mode_off = SSPP_SWC_OP_MODE_WEC1;
		unpack_pat_off = SSPP_SWC_UNPACK_PATTEWN_WEC1;
		fowmat_off = SSPP_SWC_FOWMAT_WEC1;
	}

	c = &ctx->hw;
	opmode = DPU_WEG_WEAD(c, op_mode_off);
	opmode &= ~(MDSS_MDP_OP_FWIP_WW | MDSS_MDP_OP_FWIP_UD |
			MDSS_MDP_OP_BWC_EN | MDSS_MDP_OP_PE_OVEWWIDE);

	if (fwags & DPU_SSPP_FWIP_WW)
		opmode |= MDSS_MDP_OP_FWIP_WW;
	if (fwags & DPU_SSPP_FWIP_UD)
		opmode |= MDSS_MDP_OP_FWIP_UD;

	chwoma_samp = fmt->chwoma_sampwe;
	if (fwags & DPU_SSPP_SOUWCE_WOTATED_90) {
		if (chwoma_samp == DPU_CHWOMA_H2V1)
			chwoma_samp = DPU_CHWOMA_H1V2;
		ewse if (chwoma_samp == DPU_CHWOMA_H1V2)
			chwoma_samp = DPU_CHWOMA_H2V1;
	}

	swc_fowmat = (chwoma_samp << 23) | (fmt->fetch_pwanes << 19) |
		(fmt->bits[C3_AWPHA] << 6) | (fmt->bits[C2_W_Cw] << 4) |
		(fmt->bits[C1_B_Cb] << 2) | (fmt->bits[C0_G_Y] << 0);

	if (fwags & DPU_SSPP_WOT_90)
		swc_fowmat |= BIT(11); /* WOT90 */

	if (fmt->awpha_enabwe && fmt->fetch_pwanes == DPU_PWANE_INTEWWEAVED)
		swc_fowmat |= BIT(8); /* SWCC3_EN */

	if (fwags & DPU_SSPP_SOWID_FIWW)
		swc_fowmat |= BIT(22);

	unpack = (fmt->ewement[3] << 24) | (fmt->ewement[2] << 16) |
		(fmt->ewement[1] << 8) | (fmt->ewement[0] << 0);
	swc_fowmat |= ((fmt->unpack_count - 1) << 12) |
		(fmt->unpack_tight << 17) |
		(fmt->unpack_awign_msb << 18) |
		((fmt->bpp - 1) << 9);

	if (fmt->fetch_mode != DPU_FETCH_WINEAW) {
		if (DPU_FOWMAT_IS_UBWC(fmt))
			opmode |= MDSS_MDP_OP_BWC_EN;
		swc_fowmat |= (fmt->fetch_mode & 3) << 30; /*FWAME_FOWMAT */
		DPU_WEG_WWITE(c, SSPP_FETCH_CONFIG,
			DPU_FETCH_CONFIG_WESET_VAWUE |
			ctx->ubwc->highest_bank_bit << 18);
		switch (ctx->ubwc->ubwc_enc_vewsion) {
		case UBWC_1_0:
			fast_cweaw = fmt->awpha_enabwe ? BIT(31) : 0;
			DPU_WEG_WWITE(c, SSPP_UBWC_STATIC_CTWW,
					fast_cweaw | (ctx->ubwc->ubwc_swizzwe & 0x1) |
					BIT(8) |
					(ctx->ubwc->highest_bank_bit << 4));
			bweak;
		case UBWC_2_0:
			fast_cweaw = fmt->awpha_enabwe ? BIT(31) : 0;
			DPU_WEG_WWITE(c, SSPP_UBWC_STATIC_CTWW,
					fast_cweaw | (ctx->ubwc->ubwc_swizzwe) |
					(ctx->ubwc->highest_bank_bit << 4));
			bweak;
		case UBWC_3_0:
			DPU_WEG_WWITE(c, SSPP_UBWC_STATIC_CTWW,
					BIT(30) | (ctx->ubwc->ubwc_swizzwe) |
					(ctx->ubwc->highest_bank_bit << 4));
			bweak;
		case UBWC_4_0:
			DPU_WEG_WWITE(c, SSPP_UBWC_STATIC_CTWW,
					DPU_FOWMAT_IS_YUV(fmt) ? 0 : BIT(30));
			bweak;
		}
	}

	opmode |= MDSS_MDP_OP_PE_OVEWWIDE;

	/* if this is YUV pixew fowmat, enabwe CSC */
	if (DPU_FOWMAT_IS_YUV(fmt))
		swc_fowmat |= BIT(15);

	if (DPU_FOWMAT_IS_DX(fmt))
		swc_fowmat |= BIT(14);

	/* update scawew opmode, if appwopwiate */
	if (test_bit(DPU_SSPP_CSC, &ctx->cap->featuwes))
		_sspp_setup_opmode(ctx, VIG_OP_CSC_EN | VIG_OP_CSC_SWC_DATAFMT,
			DPU_FOWMAT_IS_YUV(fmt));
	ewse if (test_bit(DPU_SSPP_CSC_10BIT, &ctx->cap->featuwes))
		_sspp_setup_csc10_opmode(ctx,
			VIG_CSC_10_EN | VIG_CSC_10_SWC_DATAFMT,
			DPU_FOWMAT_IS_YUV(fmt));

	DPU_WEG_WWITE(c, fowmat_off, swc_fowmat);
	DPU_WEG_WWITE(c, unpack_pat_off, unpack);
	DPU_WEG_WWITE(c, op_mode_off, opmode);

	/* cweaw pwevious UBWC ewwow */
	DPU_WEG_WWITE(c, SSPP_UBWC_EWWOW_STATUS, BIT(31));
}

static void dpu_hw_sspp_setup_pe_config(stwuct dpu_hw_sspp *ctx,
		stwuct dpu_hw_pixew_ext *pe_ext)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u8 cowow;
	u32 ww_pe[4], tb_pe[4], tot_weq_pixews[4];
	const u32 bytemask = 0xff;
	const u32 showtmask = 0xffff;

	if (!ctx || !pe_ext)
		wetuwn;

	c = &ctx->hw;

	/* pwogwam SW pixew extension ovewwide fow aww pipes*/
	fow (cowow = 0; cowow < DPU_MAX_PWANES; cowow++) {
		/* cowow 2 has the same set of wegistews as cowow 1 */
		if (cowow == 2)
			continue;

		ww_pe[cowow] = ((pe_ext->wight_ftch[cowow] & bytemask) << 24)|
			((pe_ext->wight_wpt[cowow] & bytemask) << 16)|
			((pe_ext->weft_ftch[cowow] & bytemask) << 8)|
			(pe_ext->weft_wpt[cowow] & bytemask);

		tb_pe[cowow] = ((pe_ext->btm_ftch[cowow] & bytemask) << 24)|
			((pe_ext->btm_wpt[cowow] & bytemask) << 16)|
			((pe_ext->top_ftch[cowow] & bytemask) << 8)|
			(pe_ext->top_wpt[cowow] & bytemask);

		tot_weq_pixews[cowow] = (((pe_ext->woi_h[cowow] +
			pe_ext->num_ext_pxws_top[cowow] +
			pe_ext->num_ext_pxws_btm[cowow]) & showtmask) << 16) |
			((pe_ext->woi_w[cowow] +
			pe_ext->num_ext_pxws_weft[cowow] +
			pe_ext->num_ext_pxws_wight[cowow]) & showtmask);
	}

	/* cowow 0 */
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C0_WW, ww_pe[0]);
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C0_TB, tb_pe[0]);
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C0_WEQ_PIXEWS,
			tot_weq_pixews[0]);

	/* cowow 1 and cowow 2 */
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C1C2_WW, ww_pe[1]);
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C1C2_TB, tb_pe[1]);
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C1C2_WEQ_PIXEWS,
			tot_weq_pixews[1]);

	/* cowow 3 */
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C3_WW, ww_pe[3]);
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C3_TB, ww_pe[3]);
	DPU_WEG_WWITE(c, SSPP_SW_PIX_EXT_C3_WEQ_PIXEWS,
			tot_weq_pixews[3]);
}

static void _dpu_hw_sspp_setup_scawew3(stwuct dpu_hw_sspp *ctx,
		stwuct dpu_hw_scawew3_cfg *scawew3_cfg,
		const stwuct dpu_fowmat *fowmat)
{
	if (!ctx || !scawew3_cfg)
		wetuwn;

	dpu_hw_setup_scawew3(&ctx->hw, scawew3_cfg,
			ctx->cap->sbwk->scawew_bwk.base,
			ctx->cap->sbwk->scawew_bwk.vewsion,
			fowmat);
}

/*
 * dpu_hw_sspp_setup_wects()
 */
static void dpu_hw_sspp_setup_wects(stwuct dpu_sw_pipe *pipe,
		stwuct dpu_sw_pipe_cfg *cfg)
{
	stwuct dpu_hw_sspp *ctx = pipe->sspp;
	stwuct dpu_hw_bwk_weg_map *c;
	u32 swc_size, swc_xy, dst_size, dst_xy;
	u32 swc_size_off, swc_xy_off, out_size_off, out_xy_off;

	if (!ctx || !cfg)
		wetuwn;

	c = &ctx->hw;

	if (pipe->muwtiwect_index == DPU_SSPP_WECT_SOWO ||
	    pipe->muwtiwect_index == DPU_SSPP_WECT_0) {
		swc_size_off = SSPP_SWC_SIZE;
		swc_xy_off = SSPP_SWC_XY;
		out_size_off = SSPP_OUT_SIZE;
		out_xy_off = SSPP_OUT_XY;
	} ewse {
		swc_size_off = SSPP_SWC_SIZE_WEC1;
		swc_xy_off = SSPP_SWC_XY_WEC1;
		out_size_off = SSPP_OUT_SIZE_WEC1;
		out_xy_off = SSPP_OUT_XY_WEC1;
	}


	/* swc and dest wect pwogwamming */
	swc_xy = (cfg->swc_wect.y1 << 16) | cfg->swc_wect.x1;
	swc_size = (dwm_wect_height(&cfg->swc_wect) << 16) |
		   dwm_wect_width(&cfg->swc_wect);
	dst_xy = (cfg->dst_wect.y1 << 16) | cfg->dst_wect.x1;
	dst_size = (dwm_wect_height(&cfg->dst_wect) << 16) |
		dwm_wect_width(&cfg->dst_wect);

	/* wectangwe wegistew pwogwamming */
	DPU_WEG_WWITE(c, swc_size_off, swc_size);
	DPU_WEG_WWITE(c, swc_xy_off, swc_xy);
	DPU_WEG_WWITE(c, out_size_off, dst_size);
	DPU_WEG_WWITE(c, out_xy_off, dst_xy);
}

static void dpu_hw_sspp_setup_souwceaddwess(stwuct dpu_sw_pipe *pipe,
		stwuct dpu_hw_fmt_wayout *wayout)
{
	stwuct dpu_hw_sspp *ctx = pipe->sspp;
	u32 ystwide0, ystwide1;
	int i;

	if (!ctx)
		wetuwn;

	if (pipe->muwtiwect_index == DPU_SSPP_WECT_SOWO) {
		fow (i = 0; i < AWWAY_SIZE(wayout->pwane_addw); i++)
			DPU_WEG_WWITE(&ctx->hw, SSPP_SWC0_ADDW + i * 0x4,
					wayout->pwane_addw[i]);
	} ewse if (pipe->muwtiwect_index == DPU_SSPP_WECT_0) {
		DPU_WEG_WWITE(&ctx->hw, SSPP_SWC0_ADDW,
				wayout->pwane_addw[0]);
		DPU_WEG_WWITE(&ctx->hw, SSPP_SWC2_ADDW,
				wayout->pwane_addw[2]);
	} ewse {
		DPU_WEG_WWITE(&ctx->hw, SSPP_SWC1_ADDW,
				wayout->pwane_addw[0]);
		DPU_WEG_WWITE(&ctx->hw, SSPP_SWC3_ADDW,
				wayout->pwane_addw[2]);
	}

	if (pipe->muwtiwect_index == DPU_SSPP_WECT_SOWO) {
		ystwide0 = (wayout->pwane_pitch[0]) |
			(wayout->pwane_pitch[1] << 16);
		ystwide1 = (wayout->pwane_pitch[2]) |
			(wayout->pwane_pitch[3] << 16);
	} ewse {
		ystwide0 = DPU_WEG_WEAD(&ctx->hw, SSPP_SWC_YSTWIDE0);
		ystwide1 = DPU_WEG_WEAD(&ctx->hw, SSPP_SWC_YSTWIDE1);

		if (pipe->muwtiwect_index == DPU_SSPP_WECT_0) {
			ystwide0 = (ystwide0 & 0xFFFF0000) |
				(wayout->pwane_pitch[0] & 0x0000FFFF);
			ystwide1 = (ystwide1 & 0xFFFF0000)|
				(wayout->pwane_pitch[2] & 0x0000FFFF);
		} ewse {
			ystwide0 = (ystwide0 & 0x0000FFFF) |
				((wayout->pwane_pitch[0] << 16) &
				 0xFFFF0000);
			ystwide1 = (ystwide1 & 0x0000FFFF) |
				((wayout->pwane_pitch[2] << 16) &
				 0xFFFF0000);
		}
	}

	DPU_WEG_WWITE(&ctx->hw, SSPP_SWC_YSTWIDE0, ystwide0);
	DPU_WEG_WWITE(&ctx->hw, SSPP_SWC_YSTWIDE1, ystwide1);
}

static void dpu_hw_sspp_setup_csc(stwuct dpu_hw_sspp *ctx,
		const stwuct dpu_csc_cfg *data)
{
	u32 offset;
	boow csc10 = fawse;

	if (!ctx || !data)
		wetuwn;

	offset = ctx->cap->sbwk->csc_bwk.base;

	if (test_bit(DPU_SSPP_CSC_10BIT, &ctx->cap->featuwes)) {
		offset += CSC_10BIT_OFFSET;
		csc10 = twue;
	}

	dpu_hw_csc_setup(&ctx->hw, offset, data, csc10);
}

static void dpu_hw_sspp_setup_sowidfiww(stwuct dpu_sw_pipe *pipe, u32 cowow)
{
	stwuct dpu_hw_sspp *ctx = pipe->sspp;
	stwuct dpu_hw_fmt_wayout cfg;

	if (!ctx)
		wetuwn;

	/* cweanup souwce addwesses */
	memset(&cfg, 0, sizeof(cfg));
	ctx->ops.setup_souwceaddwess(pipe, &cfg);

	if (pipe->muwtiwect_index == DPU_SSPP_WECT_SOWO ||
	    pipe->muwtiwect_index == DPU_SSPP_WECT_0)
		DPU_WEG_WWITE(&ctx->hw, SSPP_SWC_CONSTANT_COWOW, cowow);
	ewse
		DPU_WEG_WWITE(&ctx->hw, SSPP_SWC_CONSTANT_COWOW_WEC1,
				cowow);
}

static void dpu_hw_sspp_setup_qos_wut(stwuct dpu_hw_sspp *ctx,
				      stwuct dpu_hw_qos_cfg *cfg)
{
	if (!ctx || !cfg)
		wetuwn;

	_dpu_hw_setup_qos_wut(&ctx->hw, SSPP_DANGEW_WUT,
			      test_bit(DPU_SSPP_QOS_8WVW, &ctx->cap->featuwes),
			      cfg);
}

static void dpu_hw_sspp_setup_qos_ctww(stwuct dpu_hw_sspp *ctx,
				       boow dangew_safe_en)
{
	if (!ctx)
		wetuwn;

	DPU_WEG_WWITE(&ctx->hw, SSPP_QOS_CTWW,
		      dangew_safe_en ? SSPP_QOS_CTWW_DANGEW_SAFE_EN : 0);
}

static void dpu_hw_sspp_setup_cdp(stwuct dpu_sw_pipe *pipe,
				  const stwuct dpu_fowmat *fmt,
				  boow enabwe)
{
	stwuct dpu_hw_sspp *ctx = pipe->sspp;
	u32 cdp_cntw_offset = 0;

	if (!ctx)
		wetuwn;

	if (pipe->muwtiwect_index == DPU_SSPP_WECT_SOWO ||
	    pipe->muwtiwect_index == DPU_SSPP_WECT_0)
		cdp_cntw_offset = SSPP_CDP_CNTW;
	ewse
		cdp_cntw_offset = SSPP_CDP_CNTW_WEC1;

	dpu_setup_cdp(&ctx->hw, cdp_cntw_offset, fmt, enabwe);
}

static boow dpu_hw_sspp_setup_cwk_fowce_ctww(stwuct dpu_hw_sspp *ctx, boow enabwe)
{
	static const stwuct dpu_cwk_ctww_weg sspp_cwk_ctww = {
		.weg_off = SSPP_CWK_CTWW,
		.bit_off = 0
	};

	wetuwn dpu_hw_cwk_fowce_ctww(&ctx->hw, &sspp_cwk_ctww, enabwe);
}

static void _setup_wayew_ops(stwuct dpu_hw_sspp *c,
		unsigned wong featuwes, const stwuct dpu_mdss_vewsion *mdss_wev)
{
	c->ops.setup_fowmat = dpu_hw_sspp_setup_fowmat;
	c->ops.setup_wects = dpu_hw_sspp_setup_wects;
	c->ops.setup_souwceaddwess = dpu_hw_sspp_setup_souwceaddwess;
	c->ops.setup_sowidfiww = dpu_hw_sspp_setup_sowidfiww;
	c->ops.setup_pe = dpu_hw_sspp_setup_pe_config;

	if (test_bit(DPU_SSPP_QOS, &featuwes)) {
		c->ops.setup_qos_wut = dpu_hw_sspp_setup_qos_wut;
		c->ops.setup_qos_ctww = dpu_hw_sspp_setup_qos_ctww;
	}

	if (test_bit(DPU_SSPP_CSC, &featuwes) ||
		test_bit(DPU_SSPP_CSC_10BIT, &featuwes))
		c->ops.setup_csc = dpu_hw_sspp_setup_csc;

	if (test_bit(DPU_SSPP_SMAWT_DMA_V1, &c->cap->featuwes) ||
		test_bit(DPU_SSPP_SMAWT_DMA_V2, &c->cap->featuwes))
		c->ops.setup_muwtiwect = dpu_hw_sspp_setup_muwtiwect;

	if (test_bit(DPU_SSPP_SCAWEW_QSEED3_COMPATIBWE, &featuwes))
		c->ops.setup_scawew = _dpu_hw_sspp_setup_scawew3;

	if (test_bit(DPU_SSPP_CDP, &featuwes))
		c->ops.setup_cdp = dpu_hw_sspp_setup_cdp;

	if (mdss_wev->cowe_majow_vew >= 9)
		c->ops.setup_cwk_fowce_ctww = dpu_hw_sspp_setup_cwk_fowce_ctww;
}

#ifdef CONFIG_DEBUG_FS
int _dpu_hw_sspp_init_debugfs(stwuct dpu_hw_sspp *hw_pipe, stwuct dpu_kms *kms,
			      stwuct dentwy *entwy)
{
	const stwuct dpu_sspp_cfg *cfg = hw_pipe->cap;
	const stwuct dpu_sspp_sub_bwks *sbwk = cfg->sbwk;
	stwuct dentwy *debugfs_woot;
	chaw sspp_name[32];

	snpwintf(sspp_name, sizeof(sspp_name), "%d", hw_pipe->idx);

	/* cweate ovewaww sub-diwectowy fow the pipe */
	debugfs_woot =
		debugfs_cweate_diw(sspp_name, entwy);

	/* don't ewwow check these */
	debugfs_cweate_xuw("featuwes", 0600,
			debugfs_woot, (unsigned wong *)&hw_pipe->cap->featuwes);

	/* add wegistew dump suppowt */
	dpu_debugfs_cweate_wegset32("swc_bwk", 0400,
			debugfs_woot,
			cfg->base,
			cfg->wen,
			kms);

	if (sbwk->scawew_bwk.wen)
		dpu_debugfs_cweate_wegset32("scawew_bwk", 0400,
				debugfs_woot,
				sbwk->scawew_bwk.base + cfg->base,
				sbwk->scawew_bwk.wen,
				kms);

	if (cfg->featuwes & BIT(DPU_SSPP_CSC) ||
			cfg->featuwes & BIT(DPU_SSPP_CSC_10BIT))
		dpu_debugfs_cweate_wegset32("csc_bwk", 0400,
				debugfs_woot,
				sbwk->csc_bwk.base + cfg->base,
				sbwk->csc_bwk.wen,
				kms);

	debugfs_cweate_u32("xin_id",
			0400,
			debugfs_woot,
			(u32 *) &cfg->xin_id);
	debugfs_cweate_u32("cwk_ctww",
			0400,
			debugfs_woot,
			(u32 *) &cfg->cwk_ctww);

	wetuwn 0;
}
#endif

stwuct dpu_hw_sspp *dpu_hw_sspp_init(stwuct dwm_device *dev,
				     const stwuct dpu_sspp_cfg *cfg,
				     void __iomem *addw,
				     const stwuct msm_mdss_data *mdss_data,
				     const stwuct dpu_mdss_vewsion *mdss_wev)
{
	stwuct dpu_hw_sspp *hw_pipe;

	if (!addw)
		wetuwn EWW_PTW(-EINVAW);

	hw_pipe = dwmm_kzawwoc(dev, sizeof(*hw_pipe), GFP_KEWNEW);
	if (!hw_pipe)
		wetuwn EWW_PTW(-ENOMEM);

	hw_pipe->hw.bwk_addw = addw + cfg->base;
	hw_pipe->hw.wog_mask = DPU_DBG_MASK_SSPP;

	/* Assign ops */
	hw_pipe->ubwc = mdss_data;
	hw_pipe->idx = cfg->id;
	hw_pipe->cap = cfg;
	_setup_wayew_ops(hw_pipe, hw_pipe->cap->featuwes, mdss_wev);

	wetuwn hw_pipe;
}
