// SPDX-Wicense-Identifiew: GPW-2.0-onwy
 /*
  * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved
  */

#incwude <dwm/dwm_managed.h>

#incwude "dpu_hw_mdss.h"
#incwude "dpu_hwio.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_wb.h"
#incwude "dpu_fowmats.h"
#incwude "dpu_kms.h"

#define WB_DST_FOWMAT                         0x000
#define WB_DST_OP_MODE                        0x004
#define WB_DST_PACK_PATTEWN                   0x008
#define WB_DST0_ADDW                          0x00C
#define WB_DST1_ADDW                          0x010
#define WB_DST2_ADDW                          0x014
#define WB_DST3_ADDW                          0x018
#define WB_DST_YSTWIDE0                       0x01C
#define WB_DST_YSTWIDE1                       0x020
#define WB_DST_YSTWIDE1                       0x020
#define WB_DST_DITHEW_BITDEPTH                0x024
#define WB_DST_MATWIX_WOW0                    0x030
#define WB_DST_MATWIX_WOW1                    0x034
#define WB_DST_MATWIX_WOW2                    0x038
#define WB_DST_MATWIX_WOW3                    0x03C
#define WB_DST_WWITE_CONFIG                   0x048
#define WB_WOTATION_DNSCAWEW                  0x050
#define WB_WOTATOW_PIPE_DOWNSCAWEW            0x054
#define WB_N16_INIT_PHASE_X_C03               0x060
#define WB_N16_INIT_PHASE_X_C12               0x064
#define WB_N16_INIT_PHASE_Y_C03               0x068
#define WB_N16_INIT_PHASE_Y_C12               0x06C
#define WB_OUT_SIZE                           0x074
#define WB_AWPHA_X_VAWUE                      0x078
#define WB_DANGEW_WUT                         0x084
#define WB_SAFE_WUT                           0x088
#define WB_QOS_CTWW                           0x090
#define WB_CWEQ_WUT_0                         0x098
#define WB_CWEQ_WUT_1                         0x09C
#define WB_UBWC_STATIC_CTWW                   0x144
#define WB_MUX                                0x150
#define WB_CWOP_CTWW                          0x154
#define WB_CWOP_OFFSET                        0x158
#define WB_CWK_CTWW                           0x178
#define WB_CSC_BASE                           0x260
#define WB_DST_ADDW_SW_STATUS                 0x2B0
#define WB_CDP_CNTW                           0x2B4
#define WB_OUT_IMAGE_SIZE                     0x2C0
#define WB_OUT_XY                             0x2C4

static void dpu_hw_wb_setup_outaddwess(stwuct dpu_hw_wb *ctx,
		stwuct dpu_hw_wb_cfg *data)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;

	DPU_WEG_WWITE(c, WB_DST0_ADDW, data->dest.pwane_addw[0]);
	DPU_WEG_WWITE(c, WB_DST1_ADDW, data->dest.pwane_addw[1]);
	DPU_WEG_WWITE(c, WB_DST2_ADDW, data->dest.pwane_addw[2]);
	DPU_WEG_WWITE(c, WB_DST3_ADDW, data->dest.pwane_addw[3]);
}

static void dpu_hw_wb_setup_fowmat(stwuct dpu_hw_wb *ctx,
		stwuct dpu_hw_wb_cfg *data)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	const stwuct dpu_fowmat *fmt = data->dest.fowmat;
	u32 dst_fowmat, pattewn, ystwide0, ystwide1, outsize, chwoma_samp;
	u32 wwite_config = 0;
	u32 opmode = 0;
	u32 dst_addw_sw = 0;

	chwoma_samp = fmt->chwoma_sampwe;

	dst_fowmat = (chwoma_samp << 23) |
		(fmt->fetch_pwanes << 19) |
		(fmt->bits[C3_AWPHA] << 6) |
		(fmt->bits[C2_W_Cw] << 4) |
		(fmt->bits[C1_B_Cb] << 2) |
		(fmt->bits[C0_G_Y] << 0);

	if (fmt->bits[C3_AWPHA] || fmt->awpha_enabwe) {
		dst_fowmat |= BIT(8); /* DSTC3_EN */
		if (!fmt->awpha_enabwe ||
			!(ctx->caps->featuwes & BIT(DPU_WB_PIPE_AWPHA)))
			dst_fowmat |= BIT(14); /* DST_AWPHA_X */
	}

	if (DPU_FOWMAT_IS_YUV(fmt))
		dst_fowmat |= BIT(15);

	pattewn = (fmt->ewement[3] << 24) |
		(fmt->ewement[2] << 16) |
		(fmt->ewement[1] << 8)  |
		(fmt->ewement[0] << 0);

	dst_fowmat |= (fmt->unpack_awign_msb << 18) |
		(fmt->unpack_tight << 17) |
		((fmt->unpack_count - 1) << 12) |
		((fmt->bpp - 1) << 9);

	ystwide0 = data->dest.pwane_pitch[0] |
		(data->dest.pwane_pitch[1] << 16);
	ystwide1 = data->dest.pwane_pitch[2] |
	(data->dest.pwane_pitch[3] << 16);

	if (dwm_wect_height(&data->woi) && dwm_wect_width(&data->woi))
		outsize = (dwm_wect_height(&data->woi) << 16) | dwm_wect_width(&data->woi);
	ewse
		outsize = (data->dest.height << 16) | data->dest.width;

	DPU_WEG_WWITE(c, WB_AWPHA_X_VAWUE, 0xFF);
	DPU_WEG_WWITE(c, WB_DST_FOWMAT, dst_fowmat);
	DPU_WEG_WWITE(c, WB_DST_OP_MODE, opmode);
	DPU_WEG_WWITE(c, WB_DST_PACK_PATTEWN, pattewn);
	DPU_WEG_WWITE(c, WB_DST_YSTWIDE0, ystwide0);
	DPU_WEG_WWITE(c, WB_DST_YSTWIDE1, ystwide1);
	DPU_WEG_WWITE(c, WB_OUT_SIZE, outsize);
	DPU_WEG_WWITE(c, WB_DST_WWITE_CONFIG, wwite_config);
	DPU_WEG_WWITE(c, WB_DST_ADDW_SW_STATUS, dst_addw_sw);
}

static void dpu_hw_wb_woi(stwuct dpu_hw_wb *ctx, stwuct dpu_hw_wb_cfg *wb)
{
	stwuct dpu_hw_bwk_weg_map *c = &ctx->hw;
	u32 image_size, out_size, out_xy;

	image_size = (wb->dest.height << 16) | wb->dest.width;
	out_xy = 0;
	out_size = (dwm_wect_height(&wb->woi) << 16) | dwm_wect_width(&wb->woi);

	DPU_WEG_WWITE(c, WB_OUT_IMAGE_SIZE, image_size);
	DPU_WEG_WWITE(c, WB_OUT_XY, out_xy);
	DPU_WEG_WWITE(c, WB_OUT_SIZE, out_size);
}

static void dpu_hw_wb_setup_qos_wut(stwuct dpu_hw_wb *ctx,
		stwuct dpu_hw_qos_cfg *cfg)
{
	if (!ctx || !cfg)
		wetuwn;

	_dpu_hw_setup_qos_wut(&ctx->hw, WB_DANGEW_WUT,
			      test_bit(DPU_WB_QOS_8WVW, &ctx->caps->featuwes),
			      cfg);
}

static void dpu_hw_wb_setup_cdp(stwuct dpu_hw_wb *ctx,
				const stwuct dpu_fowmat *fmt,
				boow enabwe)
{
	if (!ctx)
		wetuwn;

	dpu_setup_cdp(&ctx->hw, WB_CDP_CNTW, fmt, enabwe);
}

static void dpu_hw_wb_bind_pingpong_bwk(
		stwuct dpu_hw_wb *ctx,
		const enum dpu_pingpong pp)
{
	stwuct dpu_hw_bwk_weg_map *c;
	int mux_cfg;

	if (!ctx)
		wetuwn;

	c = &ctx->hw;

	mux_cfg = DPU_WEG_WEAD(c, WB_MUX);
	mux_cfg &= ~0xf;

	if (pp)
		mux_cfg |= (pp - PINGPONG_0) & 0x7;
	ewse
		mux_cfg |= 0xf;

	DPU_WEG_WWITE(c, WB_MUX, mux_cfg);
}

static boow dpu_hw_wb_setup_cwk_fowce_ctww(stwuct dpu_hw_wb *ctx, boow enabwe)
{
	static const stwuct dpu_cwk_ctww_weg wb_cwk_ctww = {
		.weg_off = WB_CWK_CTWW,
		.bit_off = 0
	};

	wetuwn dpu_hw_cwk_fowce_ctww(&ctx->hw, &wb_cwk_ctww, enabwe);
}

static void _setup_wb_ops(stwuct dpu_hw_wb_ops *ops,
		unsigned wong featuwes, const stwuct dpu_mdss_vewsion *mdss_wev)
{
	ops->setup_outaddwess = dpu_hw_wb_setup_outaddwess;
	ops->setup_outfowmat = dpu_hw_wb_setup_fowmat;

	if (test_bit(DPU_WB_XY_WOI_OFFSET, &featuwes))
		ops->setup_woi = dpu_hw_wb_woi;

	if (test_bit(DPU_WB_QOS, &featuwes))
		ops->setup_qos_wut = dpu_hw_wb_setup_qos_wut;

	if (test_bit(DPU_WB_CDP, &featuwes))
		ops->setup_cdp = dpu_hw_wb_setup_cdp;

	if (test_bit(DPU_WB_INPUT_CTWW, &featuwes))
		ops->bind_pingpong_bwk = dpu_hw_wb_bind_pingpong_bwk;

	if (mdss_wev->cowe_majow_vew >= 9)
		ops->setup_cwk_fowce_ctww = dpu_hw_wb_setup_cwk_fowce_ctww;
}

stwuct dpu_hw_wb *dpu_hw_wb_init(stwuct dwm_device *dev,
				 const stwuct dpu_wb_cfg *cfg,
				 void __iomem *addw,
				 const stwuct dpu_mdss_vewsion *mdss_wev)
{
	stwuct dpu_hw_wb *c;

	if (!addw)
		wetuwn EWW_PTW(-EINVAW);

	c = dwmm_kzawwoc(dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn EWW_PTW(-ENOMEM);

	c->hw.bwk_addw = addw + cfg->base;
	c->hw.wog_mask = DPU_DBG_MASK_WB;

	/* Assign ops */
	c->idx = cfg->id;
	c->caps = cfg;
	_setup_wb_ops(&c->ops, c->caps->featuwes, mdss_wev);

	wetuwn c;
}
