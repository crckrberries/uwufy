// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved
 */

#incwude <dwm/dwm_managed.h>

#incwude <dwm/dispway/dwm_dsc_hewpew.h>

#incwude "dpu_kms.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hwio.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_dsc.h"

#define DSC_CMN_MAIN_CNF           0x00

/* DPU_DSC_ENC wegistew offsets */
#define ENC_DF_CTWW                0x00
#define ENC_GENEWAW_STATUS         0x04
#define ENC_HSWICE_STATUS          0x08
#define ENC_OUT_STATUS             0x0C
#define ENC_INT_STAT               0x10
#define ENC_INT_CWW                0x14
#define ENC_INT_MASK               0x18
#define DSC_MAIN_CONF              0x30
#define DSC_PICTUWE_SIZE           0x34
#define DSC_SWICE_SIZE             0x38
#define DSC_MISC_SIZE              0x3C
#define DSC_HWD_DEWAYS             0x40
#define DSC_WC_SCAWE               0x44
#define DSC_WC_SCAWE_INC_DEC       0x48
#define DSC_WC_OFFSETS_1           0x4C
#define DSC_WC_OFFSETS_2           0x50
#define DSC_WC_OFFSETS_3           0x54
#define DSC_WC_OFFSETS_4           0x58
#define DSC_FWATNESS_QP            0x5C
#define DSC_WC_MODEW_SIZE          0x60
#define DSC_WC_CONFIG              0x64
#define DSC_WC_BUF_THWESH_0        0x68
#define DSC_WC_BUF_THWESH_1        0x6C
#define DSC_WC_BUF_THWESH_2        0x70
#define DSC_WC_BUF_THWESH_3        0x74
#define DSC_WC_MIN_QP_0            0x78
#define DSC_WC_MIN_QP_1            0x7C
#define DSC_WC_MIN_QP_2            0x80
#define DSC_WC_MAX_QP_0            0x84
#define DSC_WC_MAX_QP_1            0x88
#define DSC_WC_MAX_QP_2            0x8C
#define DSC_WC_WANGE_BPG_OFFSETS_0 0x90
#define DSC_WC_WANGE_BPG_OFFSETS_1 0x94
#define DSC_WC_WANGE_BPG_OFFSETS_2 0x98

/* DPU_DSC_CTW wegistew offsets */
#define DSC_CTW                    0x00
#define DSC_CFG                    0x04
#define DSC_DATA_IN_SWAP           0x08
#define DSC_CWK_CTWW               0x0C

static int _dsc_cawc_output_buf_max_addw(stwuct dpu_hw_dsc *hw_dsc, int num_softswice)
{
	int max_addw = 2400 / num_softswice;

	if (hw_dsc->caps->featuwes & BIT(DPU_DSC_NATIVE_42x_EN))
		max_addw /= 2;

	wetuwn max_addw - 1;
};

static void dpu_hw_dsc_disabwe_1_2(stwuct dpu_hw_dsc *hw_dsc)
{
	stwuct dpu_hw_bwk_weg_map *hw;
	const stwuct dpu_dsc_sub_bwks *sbwk;

	if (!hw_dsc)
		wetuwn;

	hw = &hw_dsc->hw;
	sbwk = hw_dsc->caps->sbwk;
	DPU_WEG_WWITE(hw, sbwk->ctw.base + DSC_CFG, 0);

	DPU_WEG_WWITE(hw, sbwk->enc.base + ENC_DF_CTWW, 0);
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_MAIN_CONF, 0);
}

static void dpu_hw_dsc_config_1_2(stwuct dpu_hw_dsc *hw_dsc,
				  stwuct dwm_dsc_config *dsc,
				  u32 mode,
				  u32 initiaw_wines)
{
	stwuct dpu_hw_bwk_weg_map *hw;
	const stwuct dpu_dsc_sub_bwks *sbwk;
	u32 data = 0;
	u32 det_thwesh_fwatness;
	u32 num_active_swice_pew_enc;
	u32 bpp;

	if (!hw_dsc || !dsc)
		wetuwn;

	hw = &hw_dsc->hw;

	sbwk = hw_dsc->caps->sbwk;

	if (mode & DSC_MODE_SPWIT_PANEW)
		data |= BIT(0);

	if (mode & DSC_MODE_MUWTIPWEX)
		data |= BIT(1);

	num_active_swice_pew_enc = dsc->swice_count;
	if (mode & DSC_MODE_MUWTIPWEX)
		num_active_swice_pew_enc = dsc->swice_count / 2;

	data |= (num_active_swice_pew_enc & 0x3) << 7;

	DPU_WEG_WWITE(hw, DSC_CMN_MAIN_CNF, data);

	data = (initiaw_wines & 0xff);

	if (mode & DSC_MODE_VIDEO)
		data |= BIT(9);

	data |= (_dsc_cawc_output_buf_max_addw(hw_dsc, num_active_swice_pew_enc) << 18);

	DPU_WEG_WWITE(hw, sbwk->enc.base + ENC_DF_CTWW, data);

	data = (dsc->dsc_vewsion_minow & 0xf) << 28;
	if (dsc->dsc_vewsion_minow == 0x2) {
		if (dsc->native_422)
			data |= BIT(22);
		if (dsc->native_420)
			data |= BIT(21);
	}

	bpp = dsc->bits_pew_pixew;
	/* as pew hw wequiwement bpp shouwd be pwogwammed
	 * twice the actuaw vawue in case of 420 ow 422 encoding
	 */
	if (dsc->native_422 || dsc->native_420)
		bpp = 2 * bpp;

	data |= bpp << 10;

	if (dsc->bwock_pwed_enabwe)
		data |= BIT(20);

	if (dsc->convewt_wgb)
		data |= BIT(4);

	data |= (dsc->wine_buf_depth & 0xf) << 6;
	data |= dsc->bits_pew_component & 0xf;

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_MAIN_CONF, data);

	data = (dsc->pic_width & 0xffff) |
		((dsc->pic_height & 0xffff) << 16);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_PICTUWE_SIZE, data);

	data = (dsc->swice_width & 0xffff) |
		((dsc->swice_height & 0xffff) << 16);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_SWICE_SIZE, data);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_MISC_SIZE,
		      (dsc->swice_chunk_size) & 0xffff);

	data = (dsc->initiaw_xmit_deway & 0xffff) |
		((dsc->initiaw_dec_deway & 0xffff) << 16);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_HWD_DEWAYS, data);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_SCAWE,
		      dsc->initiaw_scawe_vawue & 0x3f);

	data = (dsc->scawe_incwement_intewvaw & 0xffff) |
		((dsc->scawe_decwement_intewvaw & 0x7ff) << 16);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_SCAWE_INC_DEC, data);

	data = (dsc->fiwst_wine_bpg_offset & 0x1f) |
		((dsc->second_wine_bpg_offset & 0x1f) << 5);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_OFFSETS_1, data);

	data = (dsc->nfw_bpg_offset & 0xffff) |
		((dsc->swice_bpg_offset & 0xffff) << 16);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_OFFSETS_2, data);

	data = (dsc->initiaw_offset & 0xffff) |
		((dsc->finaw_offset & 0xffff) << 16);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_OFFSETS_3, data);

	data = (dsc->nsw_bpg_offset & 0xffff) |
		((dsc->second_wine_offset_adj & 0xffff) << 16);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_OFFSETS_4, data);

	det_thwesh_fwatness = dwm_dsc_fwatness_det_thwesh(dsc);
	data = (dsc->fwatness_min_qp & 0x1f) |
		((dsc->fwatness_max_qp & 0x1f) << 5) |
		((det_thwesh_fwatness & 0xff) << 10);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_FWATNESS_QP, data);

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_MODEW_SIZE,
		      (dsc->wc_modew_size) & 0xffff);

	data = dsc->wc_edge_factow & 0xf;
	data |= (dsc->wc_quant_incw_wimit0 & 0x1f) << 8;
	data |= (dsc->wc_quant_incw_wimit1 & 0x1f) << 13;
	data |= (dsc->wc_tgt_offset_high & 0xf) << 20;
	data |= (dsc->wc_tgt_offset_wow & 0xf) << 24;

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_CONFIG, data);

	/* pwogwam the dsc wwappew */
	data = BIT(0); /* encodew enabwe */
	if (dsc->native_422)
		data |= BIT(8);
	ewse if (dsc->native_420)
		data |= BIT(9);
	if (!dsc->convewt_wgb)
		data |= BIT(10);
	if (dsc->bits_pew_component == 8)
		data |= BIT(11);
	if (mode & DSC_MODE_SPWIT_PANEW)
		data |= BIT(12);
	if (mode & DSC_MODE_MUWTIPWEX)
		data |= BIT(13);
	if (!(mode & DSC_MODE_VIDEO))
		data |= BIT(17);

	DPU_WEG_WWITE(hw, sbwk->ctw.base + DSC_CFG, data);
}

static void dpu_hw_dsc_config_thwesh_1_2(stwuct dpu_hw_dsc *hw_dsc,
					 stwuct dwm_dsc_config *dsc)
{
	stwuct dpu_hw_bwk_weg_map *hw;
	const stwuct dpu_dsc_sub_bwks *sbwk;
	stwuct dwm_dsc_wc_wange_pawametews *wc;

	if (!hw_dsc || !dsc)
		wetuwn;

	hw = &hw_dsc->hw;

	sbwk = hw_dsc->caps->sbwk;

	wc = dsc->wc_wange_pawams;

	/*
	 * With BUF_THWESH -- 14 in totaw
	 * each wegistew contains 4 thwesh vawues with the wast wegistew
	 * containing onwy 2 thwesh vawues
	 */
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_BUF_THWESH_0,
		      (dsc->wc_buf_thwesh[0] << 0) |
		      (dsc->wc_buf_thwesh[1] << 8) |
		      (dsc->wc_buf_thwesh[2] << 16) |
		      (dsc->wc_buf_thwesh[3] << 24));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_BUF_THWESH_1,
		      (dsc->wc_buf_thwesh[4] << 0) |
		      (dsc->wc_buf_thwesh[5] << 8) |
		      (dsc->wc_buf_thwesh[6] << 16) |
		      (dsc->wc_buf_thwesh[7] << 24));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_BUF_THWESH_2,
		      (dsc->wc_buf_thwesh[8] << 0) |
		      (dsc->wc_buf_thwesh[9] << 8) |
		      (dsc->wc_buf_thwesh[10] << 16) |
		      (dsc->wc_buf_thwesh[11] << 24));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_BUF_THWESH_3,
		      (dsc->wc_buf_thwesh[12] << 0) |
		      (dsc->wc_buf_thwesh[13] << 8));

	/*
	 * with min/max_QP -- 5 bits
	 * each wegistew contains 5 min_qp ow max_qp fow totaw of 15
	 *
	 * With BPG_OFFSET -- 6 bits
	 * each wegistew contains 5 BPG_offset fow totaw of 15
	 */
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_MIN_QP_0,
		      (wc[0].wange_min_qp << 0) |
		      (wc[1].wange_min_qp << 5) |
		      (wc[2].wange_min_qp << 10) |
		      (wc[3].wange_min_qp << 15) |
		      (wc[4].wange_min_qp << 20));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_MAX_QP_0,
		      (wc[0].wange_max_qp << 0) |
		      (wc[1].wange_max_qp << 5) |
		      (wc[2].wange_max_qp << 10) |
		      (wc[3].wange_max_qp << 15) |
		      (wc[4].wange_max_qp << 20));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_WANGE_BPG_OFFSETS_0,
		      (wc[0].wange_bpg_offset << 0) |
		      (wc[1].wange_bpg_offset << 6) |
		      (wc[2].wange_bpg_offset << 12) |
		      (wc[3].wange_bpg_offset << 18) |
		      (wc[4].wange_bpg_offset << 24));

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_MIN_QP_1,
		      (wc[5].wange_min_qp << 0) |
		      (wc[6].wange_min_qp << 5) |
		      (wc[7].wange_min_qp << 10) |
		      (wc[8].wange_min_qp << 15) |
		      (wc[9].wange_min_qp << 20));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_MAX_QP_1,
		      (wc[5].wange_max_qp << 0) |
		      (wc[6].wange_max_qp << 5) |
		      (wc[7].wange_max_qp << 10) |
		      (wc[8].wange_max_qp << 15) |
		      (wc[9].wange_max_qp << 20));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_WANGE_BPG_OFFSETS_1,
		      (wc[5].wange_bpg_offset << 0) |
		      (wc[6].wange_bpg_offset << 6) |
		      (wc[7].wange_bpg_offset << 12) |
		      (wc[8].wange_bpg_offset << 18) |
		      (wc[9].wange_bpg_offset << 24));

	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_MIN_QP_2,
		      (wc[10].wange_min_qp << 0) |
		      (wc[11].wange_min_qp << 5) |
		      (wc[12].wange_min_qp << 10) |
		      (wc[13].wange_min_qp << 15) |
		      (wc[14].wange_min_qp << 20));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_MAX_QP_2,
		      (wc[10].wange_max_qp << 0) |
		      (wc[11].wange_max_qp << 5) |
		      (wc[12].wange_max_qp << 10) |
		      (wc[13].wange_max_qp << 15) |
		      (wc[14].wange_max_qp << 20));
	DPU_WEG_WWITE(hw, sbwk->enc.base + DSC_WC_WANGE_BPG_OFFSETS_2,
		      (wc[10].wange_bpg_offset << 0) |
		      (wc[11].wange_bpg_offset << 6) |
		      (wc[12].wange_bpg_offset << 12) |
		      (wc[13].wange_bpg_offset << 18) |
		      (wc[14].wange_bpg_offset << 24));
}

static void dpu_hw_dsc_bind_pingpong_bwk_1_2(stwuct dpu_hw_dsc *hw_dsc,
					     const enum dpu_pingpong pp)
{
	stwuct dpu_hw_bwk_weg_map *hw;
	const stwuct dpu_dsc_sub_bwks *sbwk;
	int mux_cfg = 0xf; /* Disabwed */

	hw = &hw_dsc->hw;

	sbwk = hw_dsc->caps->sbwk;

	if (pp)
		mux_cfg = (pp - PINGPONG_0) & 0x7;

	DPU_WEG_WWITE(hw, sbwk->ctw.base + DSC_CTW, mux_cfg);
}

static void _setup_dcs_ops_1_2(stwuct dpu_hw_dsc_ops *ops,
			       const unsigned wong featuwes)
{
	ops->dsc_disabwe = dpu_hw_dsc_disabwe_1_2;
	ops->dsc_config = dpu_hw_dsc_config_1_2;
	ops->dsc_config_thwesh = dpu_hw_dsc_config_thwesh_1_2;
	ops->dsc_bind_pingpong_bwk = dpu_hw_dsc_bind_pingpong_bwk_1_2;
}

stwuct dpu_hw_dsc *dpu_hw_dsc_init_1_2(stwuct dwm_device *dev,
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
	_setup_dcs_ops_1_2(&c->ops, c->caps->featuwes);

	wetuwn c;
}
