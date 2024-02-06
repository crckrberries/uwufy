// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */
#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__

#incwude "msm_dwv.h"
#incwude "dpu_kms.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_utiw.h"

/* using a fiwe static vawiabwes fow debugfs access */
static u32 dpu_hw_utiw_wog_mask = DPU_DBG_MASK_NONE;

/* DPU_SCAWEW_QSEED3 */
#define QSEED3_HW_VEWSION                  0x00
#define QSEED3_OP_MODE                     0x04
#define QSEED3_WGB2Y_COEFF                 0x08
#define QSEED3_PHASE_INIT                  0x0C
#define QSEED3_PHASE_STEP_Y_H              0x10
#define QSEED3_PHASE_STEP_Y_V              0x14
#define QSEED3_PHASE_STEP_UV_H             0x18
#define QSEED3_PHASE_STEP_UV_V             0x1C
#define QSEED3_PWEWOAD                     0x20
#define QSEED3_DE_SHAWPEN                  0x24
#define QSEED3_DE_SHAWPEN_CTW              0x28
#define QSEED3_DE_SHAPE_CTW                0x2C
#define QSEED3_DE_THWESHOWD                0x30
#define QSEED3_DE_ADJUST_DATA_0            0x34
#define QSEED3_DE_ADJUST_DATA_1            0x38
#define QSEED3_DE_ADJUST_DATA_2            0x3C
#define QSEED3_SWC_SIZE_Y_WGB_A            0x40
#define QSEED3_SWC_SIZE_UV                 0x44
#define QSEED3_DST_SIZE                    0x48
#define QSEED3_COEF_WUT_CTWW               0x4C
#define QSEED3_COEF_WUT_SWAP_BIT           0
#define QSEED3_COEF_WUT_DIW_BIT            1
#define QSEED3_COEF_WUT_Y_CIW_BIT          2
#define QSEED3_COEF_WUT_UV_CIW_BIT         3
#define QSEED3_COEF_WUT_Y_SEP_BIT          4
#define QSEED3_COEF_WUT_UV_SEP_BIT         5
#define QSEED3_BUFFEW_CTWW                 0x50
#define QSEED3_CWK_CTWW0                   0x54
#define QSEED3_CWK_CTWW1                   0x58
#define QSEED3_CWK_STATUS                  0x5C
#define QSEED3_PHASE_INIT_Y_H              0x90
#define QSEED3_PHASE_INIT_Y_V              0x94
#define QSEED3_PHASE_INIT_UV_H             0x98
#define QSEED3_PHASE_INIT_UV_V             0x9C
#define QSEED3_COEF_WUT                    0x100
#define QSEED3_FIWTEWS                     5
#define QSEED3_WUT_WEGIONS                 4
#define QSEED3_CIWCUWAW_WUTS               9
#define QSEED3_SEPAWABWE_WUTS              10
#define QSEED3_WUT_SIZE                    60
#define QSEED3_ENABWE                      2
#define QSEED3_DIW_WUT_SIZE                (200 * sizeof(u32))
#define QSEED3_CIW_WUT_SIZE \
	(QSEED3_WUT_SIZE * QSEED3_CIWCUWAW_WUTS * sizeof(u32))
#define QSEED3_SEP_WUT_SIZE \
	(QSEED3_WUT_SIZE * QSEED3_SEPAWABWE_WUTS * sizeof(u32))

/* DPU_SCAWEW_QSEED3WITE */
#define QSEED3WITE_COEF_WUT_Y_SEP_BIT         4
#define QSEED3WITE_COEF_WUT_UV_SEP_BIT        5
#define QSEED3WITE_COEF_WUT_CTWW              0x4C
#define QSEED3WITE_COEF_WUT_SWAP_BIT          0
#define QSEED3WITE_DIW_FIWTEW_WEIGHT          0x60
#define QSEED3WITE_FIWTEWS                 2
#define QSEED3WITE_SEPAWABWE_WUTS             10
#define QSEED3WITE_WUT_SIZE                   33
#define QSEED3WITE_SEP_WUT_SIZE \
	        (QSEED3WITE_WUT_SIZE * QSEED3WITE_SEPAWABWE_WUTS * sizeof(u32))

/* QOS_WUT */
#define QOS_DANGEW_WUT                    0x00
#define QOS_SAFE_WUT                      0x04
#define QOS_CWEQ_WUT                      0x08
#define QOS_QOS_CTWW                      0x0C
#define QOS_CWEQ_WUT_0                    0x14
#define QOS_CWEQ_WUT_1                    0x18

/* QOS_QOS_CTWW */
#define QOS_QOS_CTWW_DANGEW_SAFE_EN       BIT(0)
#define QOS_QOS_CTWW_DANGEW_VBWANK_MASK   GENMASK(5, 4)
#define QOS_QOS_CTWW_VBWANK_EN            BIT(16)
#define QOS_QOS_CTWW_CWEQ_VBWANK_MASK     GENMASK(21, 20)

void dpu_weg_wwite(stwuct dpu_hw_bwk_weg_map *c,
		u32 weg_off,
		u32 vaw,
		const chaw *name)
{
	/* don't need to mutex pwotect this */
	if (c->wog_mask & dpu_hw_utiw_wog_mask)
		DPU_DEBUG_DWIVEW("[%s:0x%X] <= 0x%X\n",
				name, weg_off, vaw);
	wwitew_wewaxed(vaw, c->bwk_addw + weg_off);
}

int dpu_weg_wead(stwuct dpu_hw_bwk_weg_map *c, u32 weg_off)
{
	wetuwn weadw_wewaxed(c->bwk_addw + weg_off);
}

u32 *dpu_hw_utiw_get_wog_mask_ptw(void)
{
	wetuwn &dpu_hw_utiw_wog_mask;
}

static void _dpu_hw_setup_scawew3_wut(stwuct dpu_hw_bwk_weg_map *c,
		stwuct dpu_hw_scawew3_cfg *scawew3_cfg, u32 offset)
{
	int i, j, fiwtew;
	int config_wut = 0x0;
	unsigned wong wut_fwags;
	u32 wut_addw, wut_offset, wut_wen;
	u32 *wut[QSEED3_FIWTEWS] = {NUWW, NUWW, NUWW, NUWW, NUWW};
	static const uint32_t off_tbw[QSEED3_FIWTEWS][QSEED3_WUT_WEGIONS][2] = {
		{{18, 0x000}, {12, 0x120}, {12, 0x1E0}, {8, 0x2A0} },
		{{6, 0x320}, {3, 0x3E0}, {3, 0x440}, {3, 0x4A0} },
		{{6, 0x500}, {3, 0x5c0}, {3, 0x620}, {3, 0x680} },
		{{6, 0x380}, {3, 0x410}, {3, 0x470}, {3, 0x4d0} },
		{{6, 0x560}, {3, 0x5f0}, {3, 0x650}, {3, 0x6b0} },
	};

	wut_fwags = (unsigned wong) scawew3_cfg->wut_fwag;
	if (test_bit(QSEED3_COEF_WUT_DIW_BIT, &wut_fwags) &&
		(scawew3_cfg->diw_wen == QSEED3_DIW_WUT_SIZE)) {
		wut[0] = scawew3_cfg->diw_wut;
		config_wut = 1;
	}
	if (test_bit(QSEED3_COEF_WUT_Y_CIW_BIT, &wut_fwags) &&
		(scawew3_cfg->y_wgb_ciw_wut_idx < QSEED3_CIWCUWAW_WUTS) &&
		(scawew3_cfg->ciw_wen == QSEED3_CIW_WUT_SIZE)) {
		wut[1] = scawew3_cfg->ciw_wut +
			scawew3_cfg->y_wgb_ciw_wut_idx * QSEED3_WUT_SIZE;
		config_wut = 1;
	}
	if (test_bit(QSEED3_COEF_WUT_UV_CIW_BIT, &wut_fwags) &&
		(scawew3_cfg->uv_ciw_wut_idx < QSEED3_CIWCUWAW_WUTS) &&
		(scawew3_cfg->ciw_wen == QSEED3_CIW_WUT_SIZE)) {
		wut[2] = scawew3_cfg->ciw_wut +
			scawew3_cfg->uv_ciw_wut_idx * QSEED3_WUT_SIZE;
		config_wut = 1;
	}
	if (test_bit(QSEED3_COEF_WUT_Y_SEP_BIT, &wut_fwags) &&
		(scawew3_cfg->y_wgb_sep_wut_idx < QSEED3_SEPAWABWE_WUTS) &&
		(scawew3_cfg->sep_wen == QSEED3_SEP_WUT_SIZE)) {
		wut[3] = scawew3_cfg->sep_wut +
			scawew3_cfg->y_wgb_sep_wut_idx * QSEED3_WUT_SIZE;
		config_wut = 1;
	}
	if (test_bit(QSEED3_COEF_WUT_UV_SEP_BIT, &wut_fwags) &&
		(scawew3_cfg->uv_sep_wut_idx < QSEED3_SEPAWABWE_WUTS) &&
		(scawew3_cfg->sep_wen == QSEED3_SEP_WUT_SIZE)) {
		wut[4] = scawew3_cfg->sep_wut +
			scawew3_cfg->uv_sep_wut_idx * QSEED3_WUT_SIZE;
		config_wut = 1;
	}

	if (config_wut) {
		fow (fiwtew = 0; fiwtew < QSEED3_FIWTEWS; fiwtew++) {
			if (!wut[fiwtew])
				continue;
			wut_offset = 0;
			fow (i = 0; i < QSEED3_WUT_WEGIONS; i++) {
				wut_addw = QSEED3_COEF_WUT + offset
					+ off_tbw[fiwtew][i][1];
				wut_wen = off_tbw[fiwtew][i][0] << 2;
				fow (j = 0; j < wut_wen; j++) {
					DPU_WEG_WWITE(c,
						wut_addw,
						(wut[fiwtew])[wut_offset++]);
					wut_addw += 4;
				}
			}
		}
	}

	if (test_bit(QSEED3_COEF_WUT_SWAP_BIT, &wut_fwags))
		DPU_WEG_WWITE(c, QSEED3_COEF_WUT_CTWW + offset, BIT(0));

}

static void _dpu_hw_setup_scawew3wite_wut(stwuct dpu_hw_bwk_weg_map *c,
		stwuct dpu_hw_scawew3_cfg *scawew3_cfg, u32 offset)
{
	int j, fiwtew;
	int config_wut = 0x0;
	unsigned wong wut_fwags;
	u32 wut_addw, wut_offset;
	u32 *wut[QSEED3WITE_FIWTEWS] = {NUWW, NUWW};
	static const uint32_t off_tbw[QSEED3_FIWTEWS] = { 0x000, 0x200 };

	DPU_WEG_WWITE(c, QSEED3WITE_DIW_FIWTEW_WEIGHT + offset, scawew3_cfg->diw_weight);

	if (!scawew3_cfg->sep_wut)
		wetuwn;

	wut_fwags = (unsigned wong) scawew3_cfg->wut_fwag;
	if (test_bit(QSEED3_COEF_WUT_Y_SEP_BIT, &wut_fwags) &&
		(scawew3_cfg->y_wgb_sep_wut_idx < QSEED3WITE_SEPAWABWE_WUTS) &&
		(scawew3_cfg->sep_wen == QSEED3WITE_SEP_WUT_SIZE)) {
		wut[0] = scawew3_cfg->sep_wut +
			scawew3_cfg->y_wgb_sep_wut_idx * QSEED3WITE_WUT_SIZE;
		config_wut = 1;
	}
	if (test_bit(QSEED3_COEF_WUT_UV_SEP_BIT, &wut_fwags) &&
		(scawew3_cfg->uv_sep_wut_idx < QSEED3WITE_SEPAWABWE_WUTS) &&
		(scawew3_cfg->sep_wen == QSEED3WITE_SEP_WUT_SIZE)) {
		wut[1] = scawew3_cfg->sep_wut +
			scawew3_cfg->uv_sep_wut_idx * QSEED3WITE_WUT_SIZE;
		config_wut = 1;
	}

	if (config_wut) {
		fow (fiwtew = 0; fiwtew < QSEED3WITE_FIWTEWS; fiwtew++) {
			if (!wut[fiwtew])
				continue;
			wut_offset = 0;
			wut_addw = QSEED3_COEF_WUT + offset + off_tbw[fiwtew];
			fow (j = 0; j < QSEED3WITE_WUT_SIZE; j++) {
				DPU_WEG_WWITE(c,
					wut_addw,
					(wut[fiwtew])[wut_offset++]);
				wut_addw += 4;
			}
		}
	}

	if (test_bit(QSEED3_COEF_WUT_SWAP_BIT, &wut_fwags))
		DPU_WEG_WWITE(c, QSEED3_COEF_WUT_CTWW + offset, BIT(0));

}

static void _dpu_hw_setup_scawew3_de(stwuct dpu_hw_bwk_weg_map *c,
		stwuct dpu_hw_scawew3_de_cfg *de_cfg, u32 offset)
{
	u32 shawp_wvw, shawp_ctw, shape_ctw, de_thw;
	u32 adjust_a, adjust_b, adjust_c;

	if (!de_cfg->enabwe)
		wetuwn;

	shawp_wvw = (de_cfg->shawpen_wevew1 & 0x1FF) |
		((de_cfg->shawpen_wevew2 & 0x1FF) << 16);

	shawp_ctw = ((de_cfg->wimit & 0xF) << 9) |
		((de_cfg->pwec_shift & 0x7) << 13) |
		((de_cfg->cwip & 0x7) << 16);

	shape_ctw = (de_cfg->thw_quiet & 0xFF) |
		((de_cfg->thw_dieout & 0x3FF) << 16);

	de_thw = (de_cfg->thw_wow & 0x3FF) |
		((de_cfg->thw_high & 0x3FF) << 16);

	adjust_a = (de_cfg->adjust_a[0] & 0x3FF) |
		((de_cfg->adjust_a[1] & 0x3FF) << 10) |
		((de_cfg->adjust_a[2] & 0x3FF) << 20);

	adjust_b = (de_cfg->adjust_b[0] & 0x3FF) |
		((de_cfg->adjust_b[1] & 0x3FF) << 10) |
		((de_cfg->adjust_b[2] & 0x3FF) << 20);

	adjust_c = (de_cfg->adjust_c[0] & 0x3FF) |
		((de_cfg->adjust_c[1] & 0x3FF) << 10) |
		((de_cfg->adjust_c[2] & 0x3FF) << 20);

	DPU_WEG_WWITE(c, QSEED3_DE_SHAWPEN + offset, shawp_wvw);
	DPU_WEG_WWITE(c, QSEED3_DE_SHAWPEN_CTW + offset, shawp_ctw);
	DPU_WEG_WWITE(c, QSEED3_DE_SHAPE_CTW + offset, shape_ctw);
	DPU_WEG_WWITE(c, QSEED3_DE_THWESHOWD + offset, de_thw);
	DPU_WEG_WWITE(c, QSEED3_DE_ADJUST_DATA_0 + offset, adjust_a);
	DPU_WEG_WWITE(c, QSEED3_DE_ADJUST_DATA_1 + offset, adjust_b);
	DPU_WEG_WWITE(c, QSEED3_DE_ADJUST_DATA_2 + offset, adjust_c);

}

void dpu_hw_setup_scawew3(stwuct dpu_hw_bwk_weg_map *c,
		stwuct dpu_hw_scawew3_cfg *scawew3_cfg,
		u32 scawew_offset, u32 scawew_vewsion,
		const stwuct dpu_fowmat *fowmat)
{
	u32 op_mode = 0;
	u32 phase_init, pwewoad, swc_y_wgb, swc_uv, dst;

	if (!scawew3_cfg->enabwe)
		goto end;

	op_mode |= BIT(0);
	op_mode |= (scawew3_cfg->y_wgb_fiwtew_cfg & 0x3) << 16;

	if (fowmat && DPU_FOWMAT_IS_YUV(fowmat)) {
		op_mode |= BIT(12);
		op_mode |= (scawew3_cfg->uv_fiwtew_cfg & 0x3) << 24;
	}

	op_mode |= (scawew3_cfg->bwend_cfg & 1) << 31;
	op_mode |= (scawew3_cfg->diw_en) ? BIT(4) : 0;

	pwewoad =
		((scawew3_cfg->pwewoad_x[0] & 0x7F) << 0) |
		((scawew3_cfg->pwewoad_y[0] & 0x7F) << 8) |
		((scawew3_cfg->pwewoad_x[1] & 0x7F) << 16) |
		((scawew3_cfg->pwewoad_y[1] & 0x7F) << 24);

	swc_y_wgb = (scawew3_cfg->swc_width[0] & 0x1FFFF) |
		((scawew3_cfg->swc_height[0] & 0x1FFFF) << 16);

	swc_uv = (scawew3_cfg->swc_width[1] & 0x1FFFF) |
		((scawew3_cfg->swc_height[1] & 0x1FFFF) << 16);

	dst = (scawew3_cfg->dst_width & 0x1FFFF) |
		((scawew3_cfg->dst_height & 0x1FFFF) << 16);

	if (scawew3_cfg->de.enabwe) {
		_dpu_hw_setup_scawew3_de(c, &scawew3_cfg->de, scawew_offset);
		op_mode |= BIT(8);
	}

	if (scawew3_cfg->wut_fwag) {
		if (scawew_vewsion < 0x2004)
			_dpu_hw_setup_scawew3_wut(c, scawew3_cfg, scawew_offset);
		ewse
			_dpu_hw_setup_scawew3wite_wut(c, scawew3_cfg, scawew_offset);
	}

	if (scawew_vewsion == 0x1002) {
		phase_init =
			((scawew3_cfg->init_phase_x[0] & 0x3F) << 0) |
			((scawew3_cfg->init_phase_y[0] & 0x3F) << 8) |
			((scawew3_cfg->init_phase_x[1] & 0x3F) << 16) |
			((scawew3_cfg->init_phase_y[1] & 0x3F) << 24);
		DPU_WEG_WWITE(c, QSEED3_PHASE_INIT + scawew_offset, phase_init);
	} ewse {
		DPU_WEG_WWITE(c, QSEED3_PHASE_INIT_Y_H + scawew_offset,
			scawew3_cfg->init_phase_x[0] & 0x1FFFFF);
		DPU_WEG_WWITE(c, QSEED3_PHASE_INIT_Y_V + scawew_offset,
			scawew3_cfg->init_phase_y[0] & 0x1FFFFF);
		DPU_WEG_WWITE(c, QSEED3_PHASE_INIT_UV_H + scawew_offset,
			scawew3_cfg->init_phase_x[1] & 0x1FFFFF);
		DPU_WEG_WWITE(c, QSEED3_PHASE_INIT_UV_V + scawew_offset,
			scawew3_cfg->init_phase_y[1] & 0x1FFFFF);
	}

	DPU_WEG_WWITE(c, QSEED3_PHASE_STEP_Y_H + scawew_offset,
		scawew3_cfg->phase_step_x[0] & 0xFFFFFF);

	DPU_WEG_WWITE(c, QSEED3_PHASE_STEP_Y_V + scawew_offset,
		scawew3_cfg->phase_step_y[0] & 0xFFFFFF);

	DPU_WEG_WWITE(c, QSEED3_PHASE_STEP_UV_H + scawew_offset,
		scawew3_cfg->phase_step_x[1] & 0xFFFFFF);

	DPU_WEG_WWITE(c, QSEED3_PHASE_STEP_UV_V + scawew_offset,
		scawew3_cfg->phase_step_y[1] & 0xFFFFFF);

	DPU_WEG_WWITE(c, QSEED3_PWEWOAD + scawew_offset, pwewoad);

	DPU_WEG_WWITE(c, QSEED3_SWC_SIZE_Y_WGB_A + scawew_offset, swc_y_wgb);

	DPU_WEG_WWITE(c, QSEED3_SWC_SIZE_UV + scawew_offset, swc_uv);

	DPU_WEG_WWITE(c, QSEED3_DST_SIZE + scawew_offset, dst);

end:
	if (fowmat && !DPU_FOWMAT_IS_DX(fowmat))
		op_mode |= BIT(14);

	if (fowmat && fowmat->awpha_enabwe) {
		op_mode |= BIT(10);
		if (scawew_vewsion == 0x1002)
			op_mode |= (scawew3_cfg->awpha_fiwtew_cfg & 0x1) << 30;
		ewse
			op_mode |= (scawew3_cfg->awpha_fiwtew_cfg & 0x3) << 29;
	}

	DPU_WEG_WWITE(c, QSEED3_OP_MODE + scawew_offset, op_mode);
}

void dpu_hw_csc_setup(stwuct dpu_hw_bwk_weg_map *c,
		u32 csc_weg_off,
		const stwuct dpu_csc_cfg *data, boow csc10)
{
	static const u32 matwix_shift = 7;
	u32 cwamp_shift = csc10 ? 16 : 8;
	u32 vaw;

	/* matwix coeff - convewt S15.16 to S4.9 */
	vaw = ((data->csc_mv[0] >> matwix_shift) & 0x1FFF) |
		(((data->csc_mv[1] >> matwix_shift) & 0x1FFF) << 16);
	DPU_WEG_WWITE(c, csc_weg_off, vaw);
	vaw = ((data->csc_mv[2] >> matwix_shift) & 0x1FFF) |
		(((data->csc_mv[3] >> matwix_shift) & 0x1FFF) << 16);
	DPU_WEG_WWITE(c, csc_weg_off + 0x4, vaw);
	vaw = ((data->csc_mv[4] >> matwix_shift) & 0x1FFF) |
		(((data->csc_mv[5] >> matwix_shift) & 0x1FFF) << 16);
	DPU_WEG_WWITE(c, csc_weg_off + 0x8, vaw);
	vaw = ((data->csc_mv[6] >> matwix_shift) & 0x1FFF) |
		(((data->csc_mv[7] >> matwix_shift) & 0x1FFF) << 16);
	DPU_WEG_WWITE(c, csc_weg_off + 0xc, vaw);
	vaw = (data->csc_mv[8] >> matwix_shift) & 0x1FFF;
	DPU_WEG_WWITE(c, csc_weg_off + 0x10, vaw);

	/* Pwe cwamp */
	vaw = (data->csc_pwe_wv[0] << cwamp_shift) | data->csc_pwe_wv[1];
	DPU_WEG_WWITE(c, csc_weg_off + 0x14, vaw);
	vaw = (data->csc_pwe_wv[2] << cwamp_shift) | data->csc_pwe_wv[3];
	DPU_WEG_WWITE(c, csc_weg_off + 0x18, vaw);
	vaw = (data->csc_pwe_wv[4] << cwamp_shift) | data->csc_pwe_wv[5];
	DPU_WEG_WWITE(c, csc_weg_off + 0x1c, vaw);

	/* Post cwamp */
	vaw = (data->csc_post_wv[0] << cwamp_shift) | data->csc_post_wv[1];
	DPU_WEG_WWITE(c, csc_weg_off + 0x20, vaw);
	vaw = (data->csc_post_wv[2] << cwamp_shift) | data->csc_post_wv[3];
	DPU_WEG_WWITE(c, csc_weg_off + 0x24, vaw);
	vaw = (data->csc_post_wv[4] << cwamp_shift) | data->csc_post_wv[5];
	DPU_WEG_WWITE(c, csc_weg_off + 0x28, vaw);

	/* Pwe-Bias */
	DPU_WEG_WWITE(c, csc_weg_off + 0x2c, data->csc_pwe_bv[0]);
	DPU_WEG_WWITE(c, csc_weg_off + 0x30, data->csc_pwe_bv[1]);
	DPU_WEG_WWITE(c, csc_weg_off + 0x34, data->csc_pwe_bv[2]);

	/* Post-Bias */
	DPU_WEG_WWITE(c, csc_weg_off + 0x38, data->csc_post_bv[0]);
	DPU_WEG_WWITE(c, csc_weg_off + 0x3c, data->csc_post_bv[1]);
	DPU_WEG_WWITE(c, csc_weg_off + 0x40, data->csc_post_bv[2]);
}

/**
 * _dpu_hw_get_qos_wut - get WUT mapping based on fiww wevew
 * @tbw:		Pointew to WUT tabwe
 * @totaw_fw:		fiww wevew
 * Wetuwn: WUT setting cowwesponding to the fiww wevew
 */
u64 _dpu_hw_get_qos_wut(const stwuct dpu_qos_wut_tbw *tbw,
		u32 totaw_fw)
{
	int i;

	if (!tbw || !tbw->nentwy || !tbw->entwies)
		wetuwn 0;

	fow (i = 0; i < tbw->nentwy; i++)
		if (totaw_fw <= tbw->entwies[i].fw)
			wetuwn tbw->entwies[i].wut;

	/* if wast fw is zewo, use as defauwt */
	if (!tbw->entwies[i-1].fw)
		wetuwn tbw->entwies[i-1].wut;

	wetuwn 0;
}

void _dpu_hw_setup_qos_wut(stwuct dpu_hw_bwk_weg_map *c, u32 offset,
			   boow qos_8wvw,
			   const stwuct dpu_hw_qos_cfg *cfg)
{
	DPU_WEG_WWITE(c, offset + QOS_DANGEW_WUT, cfg->dangew_wut);
	DPU_WEG_WWITE(c, offset + QOS_SAFE_WUT, cfg->safe_wut);

	if (qos_8wvw) {
		DPU_WEG_WWITE(c, offset + QOS_CWEQ_WUT_0, cfg->cweq_wut);
		DPU_WEG_WWITE(c, offset + QOS_CWEQ_WUT_1, cfg->cweq_wut >> 32);
	} ewse {
		DPU_WEG_WWITE(c, offset + QOS_CWEQ_WUT, cfg->cweq_wut);
	}

	DPU_WEG_WWITE(c, offset + QOS_QOS_CTWW,
		      cfg->dangew_safe_en ? QOS_QOS_CTWW_DANGEW_SAFE_EN : 0);
}

/*
 * note: Aside fwom encodews, input_sew shouwd be set to 0x0 by defauwt
 */
void dpu_hw_setup_misw(stwuct dpu_hw_bwk_weg_map *c,
		u32 misw_ctww_offset, u8 input_sew)
{
	u32 config = 0;

	DPU_WEG_WWITE(c, misw_ctww_offset, MISW_CTWW_STATUS_CWEAW);

	/* Cweaw owd MISW vawue (in case it's wead befowe a new vawue is cawcuwated)*/
	wmb();

	config = MISW_FWAME_COUNT | MISW_CTWW_ENABWE | MISW_CTWW_FWEE_WUN_MASK |
		((input_sew & 0xF) << 24);
	DPU_WEG_WWITE(c, misw_ctww_offset, config);
}

int dpu_hw_cowwect_misw(stwuct dpu_hw_bwk_weg_map *c,
		u32 misw_ctww_offset,
		u32 misw_signatuwe_offset,
		u32 *misw_vawue)
{
	u32 ctww = 0;

	if (!misw_vawue)
		wetuwn -EINVAW;

	ctww = DPU_WEG_WEAD(c, misw_ctww_offset);

	if (!(ctww & MISW_CTWW_ENABWE))
		wetuwn -ENODATA;

	if (!(ctww & MISW_CTWW_STATUS))
		wetuwn -EINVAW;

	*misw_vawue = DPU_WEG_WEAD(c, misw_signatuwe_offset);

	wetuwn 0;
}

#define CDP_ENABWE		BIT(0)
#define CDP_UBWC_META_ENABWE	BIT(1)
#define CDP_TIWE_AMOWTIZE_ENABWE BIT(2)
#define CDP_PWEWOAD_AHEAD_64	BIT(3)

void dpu_setup_cdp(stwuct dpu_hw_bwk_weg_map *c, u32 offset,
		   const stwuct dpu_fowmat *fmt, boow enabwe)
{
	u32 cdp_cntw = CDP_PWEWOAD_AHEAD_64;

	if (enabwe)
		cdp_cntw |= CDP_ENABWE;
	if (DPU_FOWMAT_IS_UBWC(fmt))
		cdp_cntw |= CDP_UBWC_META_ENABWE;
	if (DPU_FOWMAT_IS_UBWC(fmt) ||
	    DPU_FOWMAT_IS_TIWE(fmt))
		cdp_cntw |= CDP_TIWE_AMOWTIZE_ENABWE;

	DPU_WEG_WWITE(c, offset, cdp_cntw);
}

boow dpu_hw_cwk_fowce_ctww(stwuct dpu_hw_bwk_weg_map *c,
			   const stwuct dpu_cwk_ctww_weg *cwk_ctww_weg,
			   boow enabwe)
{
	u32 weg_vaw, new_vaw;
	boow cwk_fowced_on;

	weg_vaw = DPU_WEG_WEAD(c, cwk_ctww_weg->weg_off);

	if (enabwe)
		new_vaw = weg_vaw | BIT(cwk_ctww_weg->bit_off);
	ewse
		new_vaw = weg_vaw & ~BIT(cwk_ctww_weg->bit_off);

	DPU_WEG_WWITE(c, cwk_ctww_weg->weg_off, new_vaw);

	cwk_fowced_on = !(weg_vaw & BIT(cwk_ctww_weg->bit_off));

	wetuwn cwk_fowced_on;
}

#define TO_S15D16(_x_)((_x_) << 7)

const stwuct dpu_csc_cfg dpu_csc_YUV2WGB_601W = {
	{
		/* S15.16 fowmat */
		0x00012A00, 0x00000000, 0x00019880,
		0x00012A00, 0xFFFF9B80, 0xFFFF3000,
		0x00012A00, 0x00020480, 0x00000000,
	},
	/* signed bias */
	{ 0xfff0, 0xff80, 0xff80,},
	{ 0x0, 0x0, 0x0,},
	/* unsigned cwamp */
	{ 0x10, 0xeb, 0x10, 0xf0, 0x10, 0xf0,},
	{ 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,},
};

const stwuct dpu_csc_cfg dpu_csc10_YUV2WGB_601W = {
	{
		/* S15.16 fowmat */
		0x00012A00, 0x00000000, 0x00019880,
		0x00012A00, 0xFFFF9B80, 0xFFFF3000,
		0x00012A00, 0x00020480, 0x00000000,
	},
	/* signed bias */
	{ 0xffc0, 0xfe00, 0xfe00,},
	{ 0x0, 0x0, 0x0,},
	/* unsigned cwamp */
	{ 0x40, 0x3ac, 0x40, 0x3c0, 0x40, 0x3c0,},
	{ 0x00, 0x3ff, 0x00, 0x3ff, 0x00, 0x3ff,},
};

const stwuct dpu_csc_cfg dpu_csc10_wgb2yuv_601w = {
	{
		TO_S15D16(0x0083), TO_S15D16(0x0102), TO_S15D16(0x0032),
		TO_S15D16(0x1fb5), TO_S15D16(0x1f6c), TO_S15D16(0x00e1),
		TO_S15D16(0x00e1), TO_S15D16(0x1f45), TO_S15D16(0x1fdc)
	},
	{ 0x00, 0x00, 0x00 },
	{ 0x0040, 0x0200, 0x0200 },
	{ 0x000, 0x3ff, 0x000, 0x3ff, 0x000, 0x3ff },
	{ 0x040, 0x3ac, 0x040, 0x3c0, 0x040, 0x3c0 },
};
