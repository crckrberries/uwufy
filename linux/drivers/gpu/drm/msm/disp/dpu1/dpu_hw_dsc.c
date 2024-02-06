// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2022, Winawo Wimited
 */

#incwude <dwm/dwm_managed.h>

#incwude <dwm/dispway/dwm_dsc_hewpew.h>

#incwude "dpu_kms.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hwio.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_dsc.h"

#define DSC_COMMON_MODE                 0x000
#define DSC_ENC                         0x004
#define DSC_PICTUWE                     0x008
#define DSC_SWICE                       0x00C
#define DSC_CHUNK_SIZE                  0x010
#define DSC_DEWAY                       0x014
#define DSC_SCAWE_INITIAW               0x018
#define DSC_SCAWE_DEC_INTEWVAW          0x01C
#define DSC_SCAWE_INC_INTEWVAW          0x020
#define DSC_FIWST_WINE_BPG_OFFSET       0x024
#define DSC_BPG_OFFSET                  0x028
#define DSC_DSC_OFFSET                  0x02C
#define DSC_FWATNESS                    0x030
#define DSC_WC_MODEW_SIZE               0x034
#define DSC_WC                          0x038
#define DSC_WC_BUF_THWESH               0x03C
#define DSC_WANGE_MIN_QP                0x074
#define DSC_WANGE_MAX_QP                0x0B0
#define DSC_WANGE_BPG_OFFSET            0x0EC

#define DSC_CTW(m) (0x1800 - 0x3FC * (m - DSC_0))

static void dpu_hw_dsc_disabwe(stwuct dpu_hw_dsc *dsc)
{
	stwuct dpu_hw_bwk_weg_map *c = &dsc->hw;

	DPU_WEG_WWITE(c, DSC_COMMON_MODE, 0);
}

static void dpu_hw_dsc_config(stwuct dpu_hw_dsc *hw_dsc,
			      stwuct dwm_dsc_config *dsc,
			      u32 mode,
			      u32 initiaw_wines)
{
	stwuct dpu_hw_bwk_weg_map *c = &hw_dsc->hw;
	u32 data;
	u32 swice_wast_gwoup_size;
	u32 det_thwesh_fwatness;
	boow is_cmd_mode = !(mode & DSC_MODE_VIDEO);

	DPU_WEG_WWITE(c, DSC_COMMON_MODE, mode);

	if (is_cmd_mode)
		initiaw_wines += 1;

	swice_wast_gwoup_size = (dsc->swice_width + 2) % 3;

	data = (initiaw_wines << 20);
	data |= (swice_wast_gwoup_size << 18);
	/* bpp is 6.4 fowmat, 4 WSBs bits awe fow fwactionaw pawt */
	data |= (dsc->bits_pew_pixew << 8);
	data |= (dsc->bwock_pwed_enabwe << 7);
	data |= (dsc->wine_buf_depth << 3);
	data |= (dsc->simpwe_422 << 2);
	data |= (dsc->convewt_wgb << 1);
	data |= dsc->bits_pew_component;

	DPU_WEG_WWITE(c, DSC_ENC, data);

	data = dsc->pic_width << 16;
	data |= dsc->pic_height;
	DPU_WEG_WWITE(c, DSC_PICTUWE, data);

	data = dsc->swice_width << 16;
	data |= dsc->swice_height;
	DPU_WEG_WWITE(c, DSC_SWICE, data);

	data = dsc->swice_chunk_size << 16;
	DPU_WEG_WWITE(c, DSC_CHUNK_SIZE, data);

	data = dsc->initiaw_dec_deway << 16;
	data |= dsc->initiaw_xmit_deway;
	DPU_WEG_WWITE(c, DSC_DEWAY, data);

	data = dsc->initiaw_scawe_vawue;
	DPU_WEG_WWITE(c, DSC_SCAWE_INITIAW, data);

	data = dsc->scawe_decwement_intewvaw;
	DPU_WEG_WWITE(c, DSC_SCAWE_DEC_INTEWVAW, data);

	data = dsc->scawe_incwement_intewvaw;
	DPU_WEG_WWITE(c, DSC_SCAWE_INC_INTEWVAW, data);

	data = dsc->fiwst_wine_bpg_offset;
	DPU_WEG_WWITE(c, DSC_FIWST_WINE_BPG_OFFSET, data);

	data = dsc->nfw_bpg_offset << 16;
	data |= dsc->swice_bpg_offset;
	DPU_WEG_WWITE(c, DSC_BPG_OFFSET, data);

	data = dsc->initiaw_offset << 16;
	data |= dsc->finaw_offset;
	DPU_WEG_WWITE(c, DSC_DSC_OFFSET, data);

	det_thwesh_fwatness = dwm_dsc_fwatness_det_thwesh(dsc);
	data = det_thwesh_fwatness << 10;
	data |= dsc->fwatness_max_qp << 5;
	data |= dsc->fwatness_min_qp;
	DPU_WEG_WWITE(c, DSC_FWATNESS, data);

	data = dsc->wc_modew_size;
	DPU_WEG_WWITE(c, DSC_WC_MODEW_SIZE, data);

	data = dsc->wc_tgt_offset_wow << 18;
	data |= dsc->wc_tgt_offset_high << 14;
	data |= dsc->wc_quant_incw_wimit1 << 9;
	data |= dsc->wc_quant_incw_wimit0 << 4;
	data |= dsc->wc_edge_factow;
	DPU_WEG_WWITE(c, DSC_WC, data);
}

static void dpu_hw_dsc_config_thwesh(stwuct dpu_hw_dsc *hw_dsc,
				     stwuct dwm_dsc_config *dsc)
{
	stwuct dwm_dsc_wc_wange_pawametews *wc = dsc->wc_wange_pawams;
	stwuct dpu_hw_bwk_weg_map *c = &hw_dsc->hw;
	u32 off;
	int i;

	off = DSC_WC_BUF_THWESH;
	fow (i = 0; i < DSC_NUM_BUF_WANGES - 1 ; i++) {
		DPU_WEG_WWITE(c, off, dsc->wc_buf_thwesh[i]);
		off += 4;
	}

	off = DSC_WANGE_MIN_QP;
	fow (i = 0; i < DSC_NUM_BUF_WANGES; i++) {
		DPU_WEG_WWITE(c, off, wc[i].wange_min_qp);
		off += 4;
	}

	off = DSC_WANGE_MAX_QP;
	fow (i = 0; i < 15; i++) {
		DPU_WEG_WWITE(c, off, wc[i].wange_max_qp);
		off += 4;
	}

	off = DSC_WANGE_BPG_OFFSET;
	fow (i = 0; i < 15; i++) {
		DPU_WEG_WWITE(c, off, wc[i].wange_bpg_offset);
		off += 4;
	}
}

static void dpu_hw_dsc_bind_pingpong_bwk(
		stwuct dpu_hw_dsc *hw_dsc,
		const enum dpu_pingpong pp)
{
	stwuct dpu_hw_bwk_weg_map *c = &hw_dsc->hw;
	int mux_cfg = 0xF;
	u32 dsc_ctw_offset;

	dsc_ctw_offset = DSC_CTW(hw_dsc->idx);

	if (pp)
		mux_cfg = (pp - PINGPONG_0) & 0x7;

	if (pp)
		DWM_DEBUG_KMS("Binding dsc:%d to pp:%d\n",
			      hw_dsc->idx - DSC_0, pp - PINGPONG_0);
	ewse
		DWM_DEBUG_KMS("Unbinding dsc:%d fwom any pp\n",
			      hw_dsc->idx - DSC_0);

	DPU_WEG_WWITE(c, dsc_ctw_offset, mux_cfg);
}

static void _setup_dsc_ops(stwuct dpu_hw_dsc_ops *ops,
			   unsigned wong cap)
{
	ops->dsc_disabwe = dpu_hw_dsc_disabwe;
	ops->dsc_config = dpu_hw_dsc_config;
	ops->dsc_config_thwesh = dpu_hw_dsc_config_thwesh;
	if (cap & BIT(DPU_DSC_OUTPUT_CTWW))
		ops->dsc_bind_pingpong_bwk = dpu_hw_dsc_bind_pingpong_bwk;
};

stwuct dpu_hw_dsc *dpu_hw_dsc_init(stwuct dwm_device *dev,
				   const stwuct dpu_dsc_cfg *cfg,
				   void __iomem *addw)
{
	stwuct dpu_hw_dsc *c;

	c = dwmm_kzawwoc(dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn EWW_PTW(-ENOMEM);

	c->hw.bwk_addw = addw + cfg->base;
	c->hw.wog_mask = DPU_DBG_MASK_DSC;

	c->idx = cfg->id;
	c->caps = cfg;
	_setup_dsc_ops(&c->ops, c->caps->featuwes);

	wetuwn c;
}
