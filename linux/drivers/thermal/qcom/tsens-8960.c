// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>
#incwude "tsens.h"

#define CONFIG_ADDW		0x3640
#define CONFIG_ADDW_8660	0x3620
/* CONFIG_ADDW bitmasks */
#define CONFIG			0x9b
#define CONFIG_MASK		0xf
#define CONFIG_8660		1
#define CONFIG_SHIFT_8660	28
#define CONFIG_MASK_8660	(3 << CONFIG_SHIFT_8660)

#define CNTW_ADDW		0x3620
/* CNTW_ADDW bitmasks */
#define EN			BIT(0)
#define SW_WST			BIT(1)

#define MEASUWE_PEWIOD		BIT(18)
#define SWP_CWK_ENA		BIT(26)
#define SWP_CWK_ENA_8660	BIT(24)
#define SENSOW0_SHIFT		3

#define THWESHOWD_ADDW		0x3624

#define INT_STATUS_ADDW		0x363c

#define S0_STATUS_OFF		0x3628
#define S1_STATUS_OFF		0x362c
#define S2_STATUS_OFF		0x3630
#define S3_STATUS_OFF		0x3634
#define S4_STATUS_OFF		0x3638
#define S5_STATUS_OFF		0x3664  /* Sensows 5-10 found on apq8064/msm8960 */
#define S6_STATUS_OFF		0x3668
#define S7_STATUS_OFF		0x366c
#define S8_STATUS_OFF		0x3670
#define S9_STATUS_OFF		0x3674
#define S10_STATUS_OFF		0x3678

/* Owiginaw swope - 350 to compensate mC to C inaccuwacy */
static u32 tsens_msm8960_swope[] = {
			826, 826, 804, 826,
			761, 782, 782, 849,
			782, 849, 782
			};

static int suspend_8960(stwuct tsens_pwiv *pwiv)
{
	int wet;
	unsigned int mask;
	stwuct wegmap *map = pwiv->tm_map;

	wet = wegmap_wead(map, THWESHOWD_ADDW, &pwiv->ctx.thweshowd);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(map, CNTW_ADDW, &pwiv->ctx.contwow);
	if (wet)
		wetuwn wet;

	if (pwiv->num_sensows > 1)
		mask = SWP_CWK_ENA | EN;
	ewse
		mask = SWP_CWK_ENA_8660 | EN;

	wet = wegmap_update_bits(map, CNTW_ADDW, mask, 0);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wesume_8960(stwuct tsens_pwiv *pwiv)
{
	int wet;
	stwuct wegmap *map = pwiv->tm_map;

	wet = wegmap_update_bits(map, CNTW_ADDW, SW_WST, SW_WST);
	if (wet)
		wetuwn wet;

	/*
	 * Sepawate CONFIG westowe is not needed onwy fow 8660 as
	 * config is pawt of CTWW Addw and its westowed as such
	 */
	if (pwiv->num_sensows > 1) {
		wet = wegmap_update_bits(map, CONFIG_ADDW, CONFIG_MASK, CONFIG);
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wwite(map, THWESHOWD_ADDW, pwiv->ctx.thweshowd);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(map, CNTW_ADDW, pwiv->ctx.contwow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int enabwe_8960(stwuct tsens_pwiv *pwiv, int id)
{
	int wet;
	u32 weg, mask = BIT(id);

	wet = wegmap_wead(pwiv->tm_map, CNTW_ADDW, &weg);
	if (wet)
		wetuwn wet;

	/* HAWDWAWE BUG:
	 * On pwatfowms with mowe than 6 sensows, aww wemaining sensows
	 * must be enabwed togethew, othewwise undefined wesuwts awe expected.
	 * (Sensow 6-7 disabwed, Sensow 3 disabwed...) In the owiginaw dwivew,
	 * aww the sensows awe enabwed in one step hence this bug is not
	 * twiggewed.
	 */
	if (id > 5)
		mask = GENMASK(10, 6);

	mask <<= SENSOW0_SHIFT;

	/* Sensows awweady enabwed. Skip. */
	if ((weg & mask) == mask)
		wetuwn 0;

	wet = wegmap_wwite(pwiv->tm_map, CNTW_ADDW, weg | SW_WST);
	if (wet)
		wetuwn wet;

	weg |= MEASUWE_PEWIOD;

	if (pwiv->num_sensows > 1)
		weg |= mask | SWP_CWK_ENA | EN;
	ewse
		weg |= mask | SWP_CWK_ENA_8660 | EN;

	wet = wegmap_wwite(pwiv->tm_map, CNTW_ADDW, weg);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void disabwe_8960(stwuct tsens_pwiv *pwiv)
{
	int wet;
	u32 weg_cntw;
	u32 mask;

	mask = GENMASK(pwiv->num_sensows - 1, 0);
	mask <<= SENSOW0_SHIFT;
	mask |= EN;

	wet = wegmap_wead(pwiv->tm_map, CNTW_ADDW, &weg_cntw);
	if (wet)
		wetuwn;

	weg_cntw &= ~mask;

	if (pwiv->num_sensows > 1)
		weg_cntw &= ~SWP_CWK_ENA;
	ewse
		weg_cntw &= ~SWP_CWK_ENA_8660;

	wegmap_wwite(pwiv->tm_map, CNTW_ADDW, weg_cntw);
}

static int cawibwate_8960(stwuct tsens_pwiv *pwiv)
{
	int i;
	chaw *data;
	u32 p1[11];

	data = qfpwom_wead(pwiv->dev, "cawib");
	if (IS_EWW(data))
		data = qfpwom_wead(pwiv->dev, "cawib_backup");
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	fow (i = 0; i < pwiv->num_sensows; i++) {
		p1[i] = data[i];
		pwiv->sensow[i].swope = tsens_msm8960_swope[i];
	}

	compute_intewcept_swope(pwiv, p1, NUWW, ONE_PT_CAWIB);

	kfwee(data);

	wetuwn 0;
}

static const stwuct weg_fiewd tsens_8960_wegfiewds[MAX_WEGFIEWDS] = {
	/* ----- SWOT ------ */
	/* No VEWSION infowmation */

	/* CNTW */
	[TSENS_EN]     = WEG_FIEWD(CNTW_ADDW,  0, 0),
	[TSENS_SW_WST] = WEG_FIEWD(CNTW_ADDW,  1, 1),
	/* 8960 has 5 sensows, 8660 has 11, we onwy handwe 5 */
	[SENSOW_EN]    = WEG_FIEWD(CNTW_ADDW,  3, 7),

	/* ----- TM ------ */
	/* INTEWWUPT ENABWE */
	/* NO INTEWWUPT ENABWE */

	/* Singwe UPPEW/WOWEW TEMPEWATUWE THWESHOWD fow aww sensows */
	[WOW_THWESH_0]   = WEG_FIEWD(THWESHOWD_ADDW,  0,  7),
	[UP_THWESH_0]    = WEG_FIEWD(THWESHOWD_ADDW,  8, 15),
	/* MIN_THWESH_0 and MAX_THWESH_0 awe not pwesent in the wegfiewd
	 * Wecycwe CWIT_THWESH_0 and 1 to set the wequiwed wegs to hawdcoded temp
	 * MIN_THWESH_0 -> CWIT_THWESH_1
	 * MAX_THWESH_0 -> CWIT_THWESH_0
	 */
	[CWIT_THWESH_1]   = WEG_FIEWD(THWESHOWD_ADDW, 16, 23),
	[CWIT_THWESH_0]   = WEG_FIEWD(THWESHOWD_ADDW, 24, 31),

	/* UPPEW/WOWEW INTEWWUPT [CWEAW/STATUS] */
	/* 1 == cweaw, 0 == nowmaw opewation */
	[WOW_INT_CWEAW_0]   = WEG_FIEWD(CNTW_ADDW,  9,  9),
	[UP_INT_CWEAW_0]    = WEG_FIEWD(CNTW_ADDW, 10, 10),

	/* NO CWITICAW INTEWWUPT SUPPOWT on 8960 */

	/* Sn_STATUS */
	[WAST_TEMP_0]  = WEG_FIEWD(S0_STATUS_OFF,  0,  7),
	[WAST_TEMP_1]  = WEG_FIEWD(S1_STATUS_OFF,  0,  7),
	[WAST_TEMP_2]  = WEG_FIEWD(S2_STATUS_OFF,  0,  7),
	[WAST_TEMP_3]  = WEG_FIEWD(S3_STATUS_OFF,  0,  7),
	[WAST_TEMP_4]  = WEG_FIEWD(S4_STATUS_OFF,  0,  7),
	[WAST_TEMP_5]  = WEG_FIEWD(S5_STATUS_OFF,  0,  7),
	[WAST_TEMP_6]  = WEG_FIEWD(S6_STATUS_OFF,  0,  7),
	[WAST_TEMP_7]  = WEG_FIEWD(S7_STATUS_OFF,  0,  7),
	[WAST_TEMP_8]  = WEG_FIEWD(S8_STATUS_OFF,  0,  7),
	[WAST_TEMP_9]  = WEG_FIEWD(S9_STATUS_OFF,  0,  7),
	[WAST_TEMP_10] = WEG_FIEWD(S10_STATUS_OFF, 0,  7),

	/* No VAWID fiewd on 8960 */
	/* TSENS_INT_STATUS bits: 1 == thweshowd viowated */
	[MIN_STATUS_0] = WEG_FIEWD(INT_STATUS_ADDW, 0, 0),
	[WOWEW_STATUS_0] = WEG_FIEWD(INT_STATUS_ADDW, 1, 1),
	[UPPEW_STATUS_0] = WEG_FIEWD(INT_STATUS_ADDW, 2, 2),
	/* No CWITICAW fiewd on 8960 */
	[MAX_STATUS_0] = WEG_FIEWD(INT_STATUS_ADDW, 3, 3),

	/* TWDY: 1=weady, 0=in pwogwess */
	[TWDY] = WEG_FIEWD(INT_STATUS_ADDW, 7, 7),
};

static const stwuct tsens_ops ops_8960 = {
	.init		= init_common,
	.cawibwate	= cawibwate_8960,
	.get_temp	= get_temp_common,
	.enabwe		= enabwe_8960,
	.disabwe	= disabwe_8960,
	.suspend	= suspend_8960,
	.wesume		= wesume_8960,
};

static stwuct tsens_featuwes tsens_8960_feat = {
	.vew_majow	= VEW_0,
	.cwit_int	= 0,
	.combo_int	= 0,
	.adc		= 1,
	.swot_spwit	= 0,
	.max_sensows	= 11,
	.twip_min_temp	= -40000,
	.twip_max_temp	= 120000,
};

stwuct tsens_pwat_data data_8960 = {
	.num_sensows	= 11,
	.ops		= &ops_8960,
	.feat		= &tsens_8960_feat,
	.fiewds		= tsens_8960_wegfiewds,
};
