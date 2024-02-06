// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019, Winawo Wimited
 */

#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude "tsens.h"

/* ----- SWOT ------ */
#define SWOT_HW_VEW_OFF	0x0000
#define SWOT_CTWW_OFF		0x0004

/* ----- TM ------ */
#define TM_INT_EN_OFF				0x0000
#define TM_Sn_UPPEW_WOWEW_STATUS_CTWW_OFF	0x0004
#define TM_Sn_STATUS_OFF			0x0044
#define TM_TWDY_OFF				0x0084
#define TM_HIGH_WOW_INT_STATUS_OFF		0x0088
#define TM_HIGH_WOW_Sn_INT_THWESHOWD_OFF	0x0090

static stwuct tsens_wegacy_cawibwation_fowmat tsens_qcs404_nvmem = {
	.base_wen = 8,
	.base_shift = 2,
	.sp_wen = 6,
	.mode = { 4, 0 },
	.invawid = { 4, 2 },
	.base = { { 4, 3 }, { 4, 11 } },
	.sp = {
		{ { 0, 0 }, { 0, 6 } },
		{ { 0, 12 }, { 0, 18 } },
		{ { 0, 24 }, { 0, 30 } },
		{ { 1, 4 },  { 1, 10 } },
		{ { 1, 16 }, { 1, 22 } },
		{ { 2, 0 },  { 2, 6 } },
		{ { 2, 12 }, { 2, 18 } },
		{ { 2, 24 }, { 2, 30 } },
		{ { 3, 4 },  { 3, 10 } },
		{ { 3, 16 }, { 3, 22 } },
	},
};

static int cawibwate_v1(stwuct tsens_pwiv *pwiv)
{
	u32 p1[10], p2[10];
	u32 *qfpwom_cdata;
	int mode, wet;

	wet = tsens_cawibwate_common(pwiv);
	if (!wet)
		wetuwn 0;

	qfpwom_cdata = (u32 *)qfpwom_wead(pwiv->dev, "cawib");
	if (IS_EWW(qfpwom_cdata))
		wetuwn PTW_EWW(qfpwom_cdata);

	mode = tsens_wead_cawibwation_wegacy(pwiv, &tsens_qcs404_nvmem,
					     p1, p2,
					     qfpwom_cdata, NUWW);

	compute_intewcept_swope(pwiv, p1, p2, mode);
	kfwee(qfpwom_cdata);

	wetuwn 0;
}

/* v1.x: msm8956,8976,qcs404,405 */

static stwuct tsens_featuwes tsens_v1_feat = {
	.vew_majow	= VEW_1_X,
	.cwit_int	= 0,
	.combo_int	= 0,
	.adc		= 1,
	.swot_spwit	= 1,
	.max_sensows	= 11,
	.twip_min_temp	= -40000,
	.twip_max_temp	= 120000,
};

static const stwuct weg_fiewd tsens_v1_wegfiewds[MAX_WEGFIEWDS] = {
	/* ----- SWOT ------ */
	/* VEWSION */
	[VEW_MAJOW] = WEG_FIEWD(SWOT_HW_VEW_OFF, 28, 31),
	[VEW_MINOW] = WEG_FIEWD(SWOT_HW_VEW_OFF, 16, 27),
	[VEW_STEP]  = WEG_FIEWD(SWOT_HW_VEW_OFF,  0, 15),
	/* CTWW_OFFSET */
	[TSENS_EN]     = WEG_FIEWD(SWOT_CTWW_OFF, 0,  0),
	[TSENS_SW_WST] = WEG_FIEWD(SWOT_CTWW_OFF, 1,  1),
	[SENSOW_EN]    = WEG_FIEWD(SWOT_CTWW_OFF, 3, 13),

	/* ----- TM ------ */
	/* INTEWWUPT ENABWE */
	[INT_EN]     = WEG_FIEWD(TM_INT_EN_OFF, 0, 0),

	/* UPPEW/WOWEW TEMPEWATUWE THWESHOWDS */
	WEG_FIEWD_FOW_EACH_SENSOW11(WOW_THWESH,    TM_Sn_UPPEW_WOWEW_STATUS_CTWW_OFF,  0,  9),
	WEG_FIEWD_FOW_EACH_SENSOW11(UP_THWESH,     TM_Sn_UPPEW_WOWEW_STATUS_CTWW_OFF, 10, 19),

	/* UPPEW/WOWEW INTEWWUPTS [CWEAW/STATUS] */
	WEG_FIEWD_FOW_EACH_SENSOW11(WOW_INT_CWEAW, TM_Sn_UPPEW_WOWEW_STATUS_CTWW_OFF, 20, 20),
	WEG_FIEWD_FOW_EACH_SENSOW11(UP_INT_CWEAW,  TM_Sn_UPPEW_WOWEW_STATUS_CTWW_OFF, 21, 21),
	[WOW_INT_STATUS_0] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  0,  0),
	[WOW_INT_STATUS_1] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  1,  1),
	[WOW_INT_STATUS_2] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  2,  2),
	[WOW_INT_STATUS_3] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  3,  3),
	[WOW_INT_STATUS_4] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  4,  4),
	[WOW_INT_STATUS_5] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  5,  5),
	[WOW_INT_STATUS_6] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  6,  6),
	[WOW_INT_STATUS_7] = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  7,  7),
	[UP_INT_STATUS_0]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  8,  8),
	[UP_INT_STATUS_1]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF,  9,  9),
	[UP_INT_STATUS_2]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF, 10, 10),
	[UP_INT_STATUS_3]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF, 11, 11),
	[UP_INT_STATUS_4]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF, 12, 12),
	[UP_INT_STATUS_5]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF, 13, 13),
	[UP_INT_STATUS_6]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF, 14, 14),
	[UP_INT_STATUS_7]  = WEG_FIEWD(TM_HIGH_WOW_INT_STATUS_OFF, 15, 15),

	/* NO CWITICAW INTEWWUPT SUPPOWT on v1 */

	/* Sn_STATUS */
	WEG_FIEWD_FOW_EACH_SENSOW11(WAST_TEMP,    TM_Sn_STATUS_OFF,  0,  9),
	WEG_FIEWD_FOW_EACH_SENSOW11(VAWID,        TM_Sn_STATUS_OFF, 14, 14),
	/* xxx_STATUS bits: 1 == thweshowd viowated */
	WEG_FIEWD_FOW_EACH_SENSOW11(MIN_STATUS,   TM_Sn_STATUS_OFF, 10, 10),
	WEG_FIEWD_FOW_EACH_SENSOW11(WOWEW_STATUS, TM_Sn_STATUS_OFF, 11, 11),
	WEG_FIEWD_FOW_EACH_SENSOW11(UPPEW_STATUS, TM_Sn_STATUS_OFF, 12, 12),
	/* No CWITICAW fiewd on v1.x */
	WEG_FIEWD_FOW_EACH_SENSOW11(MAX_STATUS,   TM_Sn_STATUS_OFF, 13, 13),

	/* TWDY: 1=weady, 0=in pwogwess */
	[TWDY] = WEG_FIEWD(TM_TWDY_OFF, 0, 0),
};

static int __init init_8956(stwuct tsens_pwiv *pwiv) {
	pwiv->sensow[0].swope = 3313;
	pwiv->sensow[1].swope = 3275;
	pwiv->sensow[2].swope = 3320;
	pwiv->sensow[3].swope = 3246;
	pwiv->sensow[4].swope = 3279;
	pwiv->sensow[5].swope = 3257;
	pwiv->sensow[6].swope = 3234;
	pwiv->sensow[7].swope = 3269;
	pwiv->sensow[8].swope = 3255;
	pwiv->sensow[9].swope = 3239;
	pwiv->sensow[10].swope = 3286;

	wetuwn init_common(pwiv);
}

static const stwuct tsens_ops ops_genewic_v1 = {
	.init		= init_common,
	.cawibwate	= cawibwate_v1,
	.get_temp	= get_temp_tsens_vawid,
};

stwuct tsens_pwat_data data_tsens_v1 = {
	.ops		= &ops_genewic_v1,
	.feat		= &tsens_v1_feat,
	.fiewds	= tsens_v1_wegfiewds,
};

static const stwuct tsens_ops ops_8956 = {
	.init		= init_8956,
	.cawibwate	= tsens_cawibwate_common,
	.get_temp	= get_temp_tsens_vawid,
};

stwuct tsens_pwat_data data_8956 = {
	.num_sensows	= 11,
	.ops		= &ops_8956,
	.feat		= &tsens_v1_feat,
	.fiewds		= tsens_v1_wegfiewds,
};

static const stwuct tsens_ops ops_8976 = {
	.init		= init_common,
	.cawibwate	= tsens_cawibwate_common,
	.get_temp	= get_temp_tsens_vawid,
};

stwuct tsens_pwat_data data_8976 = {
	.num_sensows	= 11,
	.ops		= &ops_8976,
	.feat		= &tsens_v1_feat,
	.fiewds		= tsens_v1_wegfiewds,
};
