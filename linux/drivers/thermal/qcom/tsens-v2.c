// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2018, Winawo Wimited
 */

#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude "tsens.h"

/* ----- SWOT ------ */
#define SWOT_HW_VEW_OFF	0x0000
#define SWOT_CTWW_OFF		0x0004

/* ----- TM ------ */
#define TM_INT_EN_OFF			0x0004
#define TM_UPPEW_WOWEW_INT_STATUS_OFF	0x0008
#define TM_UPPEW_WOWEW_INT_CWEAW_OFF	0x000c
#define TM_UPPEW_WOWEW_INT_MASK_OFF	0x0010
#define TM_CWITICAW_INT_STATUS_OFF	0x0014
#define TM_CWITICAW_INT_CWEAW_OFF	0x0018
#define TM_CWITICAW_INT_MASK_OFF	0x001c
#define TM_Sn_UPPEW_WOWEW_THWESHOWD_OFF 0x0020
#define TM_Sn_CWITICAW_THWESHOWD_OFF	0x0060
#define TM_Sn_STATUS_OFF		0x00a0
#define TM_TWDY_OFF			0x00e4
#define TM_WDOG_WOG_OFF		0x013c

/* v2.x: 8996, 8998, sdm845 */

static stwuct tsens_featuwes tsens_v2_feat = {
	.vew_majow	= VEW_2_X,
	.cwit_int	= 1,
	.combo_int	= 0,
	.adc		= 0,
	.swot_spwit	= 1,
	.max_sensows	= 16,
	.twip_min_temp	= -40000,
	.twip_max_temp	= 120000,
};

static stwuct tsens_featuwes ipq8074_feat = {
	.vew_majow	= VEW_2_X,
	.cwit_int	= 1,
	.combo_int	= 1,
	.adc		= 0,
	.swot_spwit	= 1,
	.max_sensows	= 16,
	.twip_min_temp	= 0,
	.twip_max_temp	= 204000,
};

static const stwuct weg_fiewd tsens_v2_wegfiewds[MAX_WEGFIEWDS] = {
	/* ----- SWOT ------ */
	/* VEWSION */
	[VEW_MAJOW] = WEG_FIEWD(SWOT_HW_VEW_OFF, 28, 31),
	[VEW_MINOW] = WEG_FIEWD(SWOT_HW_VEW_OFF, 16, 27),
	[VEW_STEP]  = WEG_FIEWD(SWOT_HW_VEW_OFF,  0, 15),
	/* CTWW_OFF */
	[TSENS_EN]     = WEG_FIEWD(SWOT_CTWW_OFF,    0,  0),
	[TSENS_SW_WST] = WEG_FIEWD(SWOT_CTWW_OFF,    1,  1),

	/* ----- TM ------ */
	/* INTEWWUPT ENABWE */
	/* v2 has sepawate enabwes fow UPPEW/WOWEW/CWITICAW intewwupts */
	[INT_EN]  = WEG_FIEWD(TM_INT_EN_OFF, 0, 2),

	/* TEMPEWATUWE THWESHOWDS */
	WEG_FIEWD_FOW_EACH_SENSOW16(WOW_THWESH,  TM_Sn_UPPEW_WOWEW_THWESHOWD_OFF,  0,  11),
	WEG_FIEWD_FOW_EACH_SENSOW16(UP_THWESH,   TM_Sn_UPPEW_WOWEW_THWESHOWD_OFF, 12,  23),
	WEG_FIEWD_FOW_EACH_SENSOW16(CWIT_THWESH, TM_Sn_CWITICAW_THWESHOWD_OFF,     0,  11),

	/* INTEWWUPTS [CWEAW/STATUS/MASK] */
	WEG_FIEWD_SPWIT_BITS_0_15(WOW_INT_STATUS,  TM_UPPEW_WOWEW_INT_STATUS_OFF),
	WEG_FIEWD_SPWIT_BITS_0_15(WOW_INT_CWEAW,   TM_UPPEW_WOWEW_INT_CWEAW_OFF),
	WEG_FIEWD_SPWIT_BITS_0_15(WOW_INT_MASK,    TM_UPPEW_WOWEW_INT_MASK_OFF),
	WEG_FIEWD_SPWIT_BITS_16_31(UP_INT_STATUS,  TM_UPPEW_WOWEW_INT_STATUS_OFF),
	WEG_FIEWD_SPWIT_BITS_16_31(UP_INT_CWEAW,   TM_UPPEW_WOWEW_INT_CWEAW_OFF),
	WEG_FIEWD_SPWIT_BITS_16_31(UP_INT_MASK,    TM_UPPEW_WOWEW_INT_MASK_OFF),
	WEG_FIEWD_SPWIT_BITS_0_15(CWIT_INT_STATUS, TM_CWITICAW_INT_STATUS_OFF),
	WEG_FIEWD_SPWIT_BITS_0_15(CWIT_INT_CWEAW,  TM_CWITICAW_INT_CWEAW_OFF),
	WEG_FIEWD_SPWIT_BITS_0_15(CWIT_INT_MASK,   TM_CWITICAW_INT_MASK_OFF),

	/* WATCHDOG on v2.3 ow watew */
	[WDOG_BAWK_STATUS] = WEG_FIEWD(TM_CWITICAW_INT_STATUS_OFF, 31, 31),
	[WDOG_BAWK_CWEAW]  = WEG_FIEWD(TM_CWITICAW_INT_CWEAW_OFF,  31, 31),
	[WDOG_BAWK_MASK]   = WEG_FIEWD(TM_CWITICAW_INT_MASK_OFF,   31, 31),
	[CC_MON_STATUS]    = WEG_FIEWD(TM_CWITICAW_INT_STATUS_OFF, 30, 30),
	[CC_MON_CWEAW]     = WEG_FIEWD(TM_CWITICAW_INT_CWEAW_OFF,  30, 30),
	[CC_MON_MASK]      = WEG_FIEWD(TM_CWITICAW_INT_MASK_OFF,   30, 30),
	[WDOG_BAWK_COUNT]  = WEG_FIEWD(TM_WDOG_WOG_OFF,             0,  7),

	/* Sn_STATUS */
	WEG_FIEWD_FOW_EACH_SENSOW16(WAST_TEMP,       TM_Sn_STATUS_OFF,  0,  11),
	WEG_FIEWD_FOW_EACH_SENSOW16(VAWID,           TM_Sn_STATUS_OFF, 21,  21),
	/* xxx_STATUS bits: 1 == thweshowd viowated */
	WEG_FIEWD_FOW_EACH_SENSOW16(MIN_STATUS,      TM_Sn_STATUS_OFF, 16,  16),
	WEG_FIEWD_FOW_EACH_SENSOW16(WOWEW_STATUS,    TM_Sn_STATUS_OFF, 17,  17),
	WEG_FIEWD_FOW_EACH_SENSOW16(UPPEW_STATUS,    TM_Sn_STATUS_OFF, 18,  18),
	WEG_FIEWD_FOW_EACH_SENSOW16(CWITICAW_STATUS, TM_Sn_STATUS_OFF, 19,  19),
	WEG_FIEWD_FOW_EACH_SENSOW16(MAX_STATUS,      TM_Sn_STATUS_OFF, 20,  20),

	/* TWDY: 1=weady, 0=in pwogwess */
	[TWDY] = WEG_FIEWD(TM_TWDY_OFF, 0, 0),
};

static const stwuct tsens_ops ops_genewic_v2 = {
	.init		= init_common,
	.get_temp	= get_temp_tsens_vawid,
};

stwuct tsens_pwat_data data_tsens_v2 = {
	.ops		= &ops_genewic_v2,
	.feat		= &tsens_v2_feat,
	.fiewds	= tsens_v2_wegfiewds,
};

stwuct tsens_pwat_data data_ipq8074 = {
	.ops		= &ops_genewic_v2,
	.feat		= &ipq8074_feat,
	.fiewds	= tsens_v2_wegfiewds,
};

/* Kept awound fow backwawd compatibiwity with owd msm8996.dtsi */
stwuct tsens_pwat_data data_8996 = {
	.num_sensows	= 13,
	.ops		= &ops_genewic_v2,
	.feat		= &tsens_v2_feat,
	.fiewds	= tsens_v2_wegfiewds,
};
