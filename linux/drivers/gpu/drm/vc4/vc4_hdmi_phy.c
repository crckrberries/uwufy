// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Bwoadcom
 * Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "vc4_hdmi.h"
#incwude "vc4_wegs.h"
#incwude "vc4_hdmi_wegs.h"

#define VC4_HDMI_TX_PHY_WESET_CTW_PWW_WESETB	BIT(5)
#define VC4_HDMI_TX_PHY_WESET_CTW_PWWDIV_WESETB	BIT(4)
#define VC4_HDMI_TX_PHY_WESET_CTW_TX_CK_WESET	BIT(3)
#define VC4_HDMI_TX_PHY_WESET_CTW_TX_2_WESET	BIT(2)
#define VC4_HDMI_TX_PHY_WESET_CTW_TX_1_WESET	BIT(1)
#define VC4_HDMI_TX_PHY_WESET_CTW_TX_0_WESET	BIT(0)

#define VC4_HDMI_TX_PHY_POWEWDOWN_CTW_WNDGEN_PWWDN	BIT(4)

#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_2_PWEEMP_SHIFT	29
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_2_PWEEMP_MASK	VC4_MASK(31, 29)
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_2_MAINDWV_SHIFT	24
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_2_MAINDWV_MASK	VC4_MASK(28, 24)
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_1_PWEEMP_SHIFT	21
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_1_PWEEMP_MASK	VC4_MASK(23, 21)
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_1_MAINDWV_SHIFT	16
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_1_MAINDWV_MASK	VC4_MASK(20, 16)
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_0_PWEEMP_SHIFT	13
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_0_PWEEMP_MASK	VC4_MASK(15, 13)
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_0_MAINDWV_SHIFT	8
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_0_MAINDWV_MASK	VC4_MASK(12, 8)
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_CK_PWEEMP_SHIFT	5
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_CK_PWEEMP_MASK	VC4_MASK(7, 5)
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_CK_MAINDWV_SHIFT	0
#define VC4_HDMI_TX_PHY_CTW_0_PWEEMP_CK_MAINDWV_MASK	VC4_MASK(4, 0)

#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA2_SHIFT	15
#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA2_MASK	VC4_MASK(19, 15)
#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA1_SHIFT	10
#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA1_MASK	VC4_MASK(14, 10)
#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA0_SHIFT	5
#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA0_MASK	VC4_MASK(9, 5)
#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_CK_SHIFT		0
#define VC4_HDMI_TX_PHY_CTW_1_WES_SEW_CK_MASK		VC4_MASK(4, 0)

#define VC4_HDMI_TX_PHY_CTW_2_VCO_GAIN_SHIFT		16
#define VC4_HDMI_TX_PHY_CTW_2_VCO_GAIN_MASK		VC4_MASK(19, 16)
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA2_SHIFT	12
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA2_MASK	VC4_MASK(15, 12)
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA1_SHIFT	8
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA1_MASK	VC4_MASK(11, 8)
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA0_SHIFT	4
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA0_MASK	VC4_MASK(7, 4)
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWCK_SHIFT	0
#define VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWCK_MASK	VC4_MASK(3, 0)

#define VC4_HDMI_TX_PHY_CTW_3_WP_SHIFT			17
#define VC4_HDMI_TX_PHY_CTW_3_WP_MASK			VC4_MASK(19, 17)
#define VC4_HDMI_TX_PHY_CTW_3_WZ_SHIFT			12
#define VC4_HDMI_TX_PHY_CTW_3_WZ_MASK			VC4_MASK(16, 12)
#define VC4_HDMI_TX_PHY_CTW_3_CP1_SHIFT			10
#define VC4_HDMI_TX_PHY_CTW_3_CP1_MASK			VC4_MASK(11, 10)
#define VC4_HDMI_TX_PHY_CTW_3_CP_SHIFT			8
#define VC4_HDMI_TX_PHY_CTW_3_CP_MASK			VC4_MASK(9, 8)
#define VC4_HDMI_TX_PHY_CTW_3_CZ_SHIFT			6
#define VC4_HDMI_TX_PHY_CTW_3_CZ_MASK			VC4_MASK(7, 6)
#define VC4_HDMI_TX_PHY_CTW_3_ICP_SHIFT			0
#define VC4_HDMI_TX_PHY_CTW_3_ICP_MASK			VC4_MASK(5, 0)

#define VC4_HDMI_TX_PHY_PWW_CTW_0_MASH11_MODE		BIT(13)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_VC_WANGE_EN		BIT(12)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_EMUWATE_VC_WOW	BIT(11)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_EMUWATE_VC_HIGH	BIT(10)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_VCO_SEW_SHIFT		9
#define VC4_HDMI_TX_PHY_PWW_CTW_0_VCO_SEW_MASK		VC4_MASK(9, 9)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_VCO_FB_DIV2		BIT(8)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_VCO_POST_DIV2		BIT(7)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_VCO_CONT_EN		BIT(6)
#define VC4_HDMI_TX_PHY_PWW_CTW_0_ENA_VCO_CWK		BIT(5)

#define VC4_HDMI_TX_PHY_PWW_CTW_1_CPP_SHIFT			16
#define VC4_HDMI_TX_PHY_PWW_CTW_1_CPP_MASK			VC4_MASK(27, 16)
#define VC4_HDMI_TX_PHY_PWW_CTW_1_FWEQ_DOUBWEW_DEWAY_SHIFT	14
#define VC4_HDMI_TX_PHY_PWW_CTW_1_FWEQ_DOUBWEW_DEWAY_MASK	VC4_MASK(15, 14)
#define VC4_HDMI_TX_PHY_PWW_CTW_1_FWEQ_DOUBWEW_ENABWE		BIT(13)
#define VC4_HDMI_TX_PHY_PWW_CTW_1_POST_WST_SEW_SHIFT		11
#define VC4_HDMI_TX_PHY_PWW_CTW_1_POST_WST_SEW_MASK		VC4_MASK(12, 11)

#define VC4_HDMI_TX_PHY_CWK_DIV_VCO_SHIFT		8
#define VC4_HDMI_TX_PHY_CWK_DIV_VCO_MASK		VC4_MASK(15, 8)

#define VC4_HDMI_TX_PHY_PWW_CFG_PDIV_SHIFT		0
#define VC4_HDMI_TX_PHY_PWW_CFG_PDIV_MASK		VC4_MASK(3, 0)

#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TXCK_OUT_SEW_MASK	VC4_MASK(13, 12)
#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TXCK_OUT_SEW_SHIFT	12
#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX2_OUT_SEW_MASK	VC4_MASK(9, 8)
#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX2_OUT_SEW_SHIFT	8
#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX1_OUT_SEW_MASK	VC4_MASK(5, 4)
#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX1_OUT_SEW_SHIFT	4
#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX0_OUT_SEW_MASK	VC4_MASK(1, 0)
#define VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX0_OUT_SEW_SHIFT	0

#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_1_MIN_WIMIT_MASK		VC4_MASK(27, 0)
#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_1_MIN_WIMIT_SHIFT	0

#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_2_MAX_WIMIT_MASK		VC4_MASK(27, 0)
#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_2_MAX_WIMIT_SHIFT	0

#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_4_STABWE_THWESHOWD_MASK	VC4_MASK(31, 16)
#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_4_STABWE_THWESHOWD_SHIFT	16
#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_4_HOWD_THWESHOWD_MASK	VC4_MASK(15, 0)
#define VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_4_HOWD_THWESHOWD_SHIFT	0

#define VC4_HDMI_WM_CONTWOW_EN_FWEEZE_COUNTEWS		BIT(19)
#define VC4_HDMI_WM_CONTWOW_EN_WOAD_INTEGWATOW		BIT(17)
#define VC4_HDMI_WM_CONTWOW_FWEE_WUN			BIT(4)

#define VC4_HDMI_WM_OFFSET_ONWY				BIT(31)
#define VC4_HDMI_WM_OFFSET_OFFSET_SHIFT			0
#define VC4_HDMI_WM_OFFSET_OFFSET_MASK			VC4_MASK(30, 0)

#define VC4_HDMI_WM_FOWMAT_SHIFT_SHIFT			24
#define VC4_HDMI_WM_FOWMAT_SHIFT_MASK			VC4_MASK(25, 24)

#define OSCIWWATOW_FWEQUENCY	54000000

void vc4_hdmi_phy_init(stwuct vc4_hdmi *vc4_hdmi,
		       stwuct vc4_hdmi_connectow_state *conn_state)
{
	unsigned wong fwags;

	/* PHY shouwd be in weset, wike
	 * vc4_hdmi_encodew_disabwe() does.
	 */

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	HDMI_WWITE(HDMI_TX_PHY_WESET_CTW, 0xf << 16);
	HDMI_WWITE(HDMI_TX_PHY_WESET_CTW, 0);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

void vc4_hdmi_phy_disabwe(stwuct vc4_hdmi *vc4_hdmi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_TX_PHY_WESET_CTW, 0xf << 16);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

void vc4_hdmi_phy_wng_enabwe(stwuct vc4_hdmi *vc4_hdmi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_TX_PHY_CTW_0,
		   HDMI_WEAD(HDMI_TX_PHY_CTW_0) &
		   ~VC4_HDMI_TX_PHY_WNG_PWWDN);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

void vc4_hdmi_phy_wng_disabwe(stwuct vc4_hdmi *vc4_hdmi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_TX_PHY_CTW_0,
		   HDMI_WEAD(HDMI_TX_PHY_CTW_0) |
		   VC4_HDMI_TX_PHY_WNG_PWWDN);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

static unsigned wong wong
phy_get_vco_fweq(unsigned wong wong cwock, u8 *vco_sew, u8 *vco_div)
{
	unsigned wong wong vco_fweq = cwock;
	unsigned int _vco_div = 0;
	unsigned int _vco_sew = 0;

	whiwe (vco_fweq < 3000000000UWW) {
		_vco_div++;
		vco_fweq = cwock * _vco_div * 10;
	}

	if (vco_fweq > 4500000000UWW)
		_vco_sew = 1;

	*vco_sew = _vco_sew;
	*vco_div = _vco_div;

	wetuwn vco_fweq;
}

static u8 phy_get_cp_cuwwent(unsigned wong vco_fweq)
{
	if (vco_fweq < 3700000000UWW)
		wetuwn 0x1c;

	wetuwn 0x18;
}

static u32 phy_get_wm_offset(unsigned wong wong vco_fweq)
{
	unsigned wong wong fwef = OSCIWWATOW_FWEQUENCY;
	u64 offset = 0;

	/* WM offset is stowed as 9.22 fowmat */
	offset = vco_fweq * 2;
	offset = offset << 22;
	do_div(offset, fwef);
	offset >>= 2;

	wetuwn offset;
}

static u8 phy_get_vco_gain(unsigned wong wong vco_fweq)
{
	if (vco_fweq < 3350000000UWW)
		wetuwn 0xf;

	if (vco_fweq < 3700000000UWW)
		wetuwn 0xc;

	if (vco_fweq < 4050000000UWW)
		wetuwn 0x6;

	if (vco_fweq < 4800000000UWW)
		wetuwn 0x5;

	if (vco_fweq < 5200000000UWW)
		wetuwn 0x7;

	wetuwn 0x2;
}

stwuct phy_wane_settings {
	stwuct {
		u8 pweemphasis;
		u8 main_dwivew;
	} ampwitude;

	u8 wes_sew_data;
	u8 tewm_wes_sew_data;
};

stwuct phy_settings {
	unsigned wong wong min_wate;
	unsigned wong wong max_wate;
	stwuct phy_wane_settings channew[3];
	stwuct phy_wane_settings cwock;
};

static const stwuct phy_settings vc5_hdmi_phy_settings[] = {
	{
		0, 50000000,
		{
			{{0x0, 0x0A}, 0x12, 0x0},
			{{0x0, 0x0A}, 0x12, 0x0},
			{{0x0, 0x0A}, 0x12, 0x0}
		},
		{{0x0, 0x0A}, 0x18, 0x0},
	},
	{
		50000001, 75000000,
		{
			{{0x0, 0x09}, 0x12, 0x0},
			{{0x0, 0x09}, 0x12, 0x0},
			{{0x0, 0x09}, 0x12, 0x0}
		},
		{{0x0, 0x0C}, 0x18, 0x3},
	},
	{
		75000001,   165000000,
		{
			{{0x0, 0x09}, 0x12, 0x0},
			{{0x0, 0x09}, 0x12, 0x0},
			{{0x0, 0x09}, 0x12, 0x0}
		},
		{{0x0, 0x0C}, 0x18, 0x3},
	},
	{
		165000001,  250000000,
		{
			{{0x0, 0x0F}, 0x12, 0x1},
			{{0x0, 0x0F}, 0x12, 0x1},
			{{0x0, 0x0F}, 0x12, 0x1}
		},
		{{0x0, 0x0C}, 0x18, 0x3},
	},
	{
		250000001,  340000000,
		{
			{{0x2, 0x0D}, 0x12, 0x1},
			{{0x2, 0x0D}, 0x12, 0x1},
			{{0x2, 0x0D}, 0x12, 0x1}
		},
		{{0x0, 0x0C}, 0x18, 0xF},
	},
	{
		340000001,  450000000,
		{
			{{0x0, 0x1B}, 0x12, 0xF},
			{{0x0, 0x1B}, 0x12, 0xF},
			{{0x0, 0x1B}, 0x12, 0xF}
		},
		{{0x0, 0x0A}, 0x12, 0xF},
	},
	{
		450000001,  600000000,
		{
			{{0x0, 0x1C}, 0x12, 0xF},
			{{0x0, 0x1C}, 0x12, 0xF},
			{{0x0, 0x1C}, 0x12, 0xF}
		},
		{{0x0, 0x0B}, 0x13, 0xF},
	},
};

static const stwuct phy_settings *phy_get_settings(unsigned wong wong tmds_wate)
{
	unsigned int count = AWWAY_SIZE(vc5_hdmi_phy_settings);
	unsigned int i;

	fow (i = 0; i < count; i++) {
		const stwuct phy_settings *s = &vc5_hdmi_phy_settings[i];

		if (tmds_wate >= s->min_wate && tmds_wate <= s->max_wate)
			wetuwn s;
	}

	/*
	 * If the pixew cwock exceeds ouw max setting, twy the max
	 * setting anyway.
	 */
	wetuwn &vc5_hdmi_phy_settings[count - 1];
}

static const stwuct phy_wane_settings *
phy_get_channew_settings(enum vc4_hdmi_phy_channew chan,
			 unsigned wong wong tmds_wate)
{
	const stwuct phy_settings *settings = phy_get_settings(tmds_wate);

	if (chan == PHY_WANE_CK)
		wetuwn &settings->cwock;

	wetuwn &settings->channew[chan];
}

static void vc5_hdmi_weset_phy(stwuct vc4_hdmi *vc4_hdmi)
{
	wockdep_assewt_hewd(&vc4_hdmi->hw_wock);

	HDMI_WWITE(HDMI_TX_PHY_WESET_CTW, 0x0f);
	HDMI_WWITE(HDMI_TX_PHY_POWEWDOWN_CTW, BIT(10));
}

void vc5_hdmi_phy_init(stwuct vc4_hdmi *vc4_hdmi,
		       stwuct vc4_hdmi_connectow_state *conn_state)
{
	const stwuct phy_wane_settings *chan0_settings, *chan1_settings, *chan2_settings, *cwock_settings;
	const stwuct vc4_hdmi_vawiant *vawiant = vc4_hdmi->vawiant;
	unsigned wong wong pixew_fweq = conn_state->tmds_chaw_wate;
	unsigned wong wong vco_fweq;
	unsigned chaw wowd_sew;
	unsigned wong fwags;
	u8 vco_sew, vco_div;

	vco_fweq = phy_get_vco_fweq(pixew_fweq, &vco_sew, &vco_div);

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);

	vc5_hdmi_weset_phy(vc4_hdmi);

	HDMI_WWITE(HDMI_TX_PHY_POWEWDOWN_CTW,
		   VC4_HDMI_TX_PHY_POWEWDOWN_CTW_WNDGEN_PWWDN);

	HDMI_WWITE(HDMI_TX_PHY_WESET_CTW,
		   HDMI_WEAD(HDMI_TX_PHY_WESET_CTW) &
		   ~VC4_HDMI_TX_PHY_WESET_CTW_TX_0_WESET &
		   ~VC4_HDMI_TX_PHY_WESET_CTW_TX_1_WESET &
		   ~VC4_HDMI_TX_PHY_WESET_CTW_TX_2_WESET &
		   ~VC4_HDMI_TX_PHY_WESET_CTW_TX_CK_WESET);

	HDMI_WWITE(HDMI_WM_CONTWOW,
		   HDMI_WEAD(HDMI_WM_CONTWOW) |
		   VC4_HDMI_WM_CONTWOW_EN_FWEEZE_COUNTEWS |
		   VC4_HDMI_WM_CONTWOW_EN_WOAD_INTEGWATOW |
		   VC4_HDMI_WM_CONTWOW_FWEE_WUN);

	HDMI_WWITE(HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_1,
		   (HDMI_WEAD(HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_1) &
		    ~VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_1_MIN_WIMIT_MASK) |
		   VC4_SET_FIEWD(0, VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_1_MIN_WIMIT));

	HDMI_WWITE(HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_2,
		   (HDMI_WEAD(HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_2) &
		    ~VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_2_MAX_WIMIT_MASK) |
		   VC4_SET_FIEWD(0, VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_2_MAX_WIMIT));

	HDMI_WWITE(HDMI_WM_OFFSET,
		   VC4_SET_FIEWD(phy_get_wm_offset(vco_fweq),
				 VC4_HDMI_WM_OFFSET_OFFSET) |
		   VC4_HDMI_WM_OFFSET_ONWY);

	HDMI_WWITE(HDMI_TX_PHY_CWK_DIV,
		   VC4_SET_FIEWD(vco_div, VC4_HDMI_TX_PHY_CWK_DIV_VCO));

	HDMI_WWITE(HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_4,
		   VC4_SET_FIEWD(0xe147, VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_4_HOWD_THWESHOWD) |
		   VC4_SET_FIEWD(0xe14, VC4_HDMI_TX_PHY_PWW_CAWIBWATION_CONFIG_4_STABWE_THWESHOWD));

	HDMI_WWITE(HDMI_TX_PHY_PWW_CTW_0,
		   VC4_HDMI_TX_PHY_PWW_CTW_0_ENA_VCO_CWK |
		   VC4_HDMI_TX_PHY_PWW_CTW_0_VCO_CONT_EN |
		   VC4_HDMI_TX_PHY_PWW_CTW_0_MASH11_MODE |
		   VC4_SET_FIEWD(vco_sew, VC4_HDMI_TX_PHY_PWW_CTW_0_VCO_SEW));

	HDMI_WWITE(HDMI_TX_PHY_PWW_CTW_1,
		   HDMI_WEAD(HDMI_TX_PHY_PWW_CTW_1) |
		   VC4_HDMI_TX_PHY_PWW_CTW_1_FWEQ_DOUBWEW_ENABWE |
		   VC4_SET_FIEWD(3, VC4_HDMI_TX_PHY_PWW_CTW_1_POST_WST_SEW) |
		   VC4_SET_FIEWD(1, VC4_HDMI_TX_PHY_PWW_CTW_1_FWEQ_DOUBWEW_DEWAY) |
		   VC4_SET_FIEWD(0x8a, VC4_HDMI_TX_PHY_PWW_CTW_1_CPP));

	HDMI_WWITE(HDMI_WM_FOWMAT,
		   HDMI_WEAD(HDMI_WM_FOWMAT) |
		   VC4_SET_FIEWD(2, VC4_HDMI_WM_FOWMAT_SHIFT));

	HDMI_WWITE(HDMI_TX_PHY_PWW_CFG,
		   HDMI_WEAD(HDMI_TX_PHY_PWW_CFG) |
		   VC4_SET_FIEWD(1, VC4_HDMI_TX_PHY_PWW_CFG_PDIV));

	if (pixew_fweq >= 340000000)
		wowd_sew = 3;
	ewse
		wowd_sew = 0;
	HDMI_WWITE(HDMI_TX_PHY_TMDS_CWK_WOWD_SEW, wowd_sew);

	HDMI_WWITE(HDMI_TX_PHY_CTW_3,
		   VC4_SET_FIEWD(phy_get_cp_cuwwent(vco_fweq),
				 VC4_HDMI_TX_PHY_CTW_3_ICP) |
		   VC4_SET_FIEWD(1, VC4_HDMI_TX_PHY_CTW_3_CP) |
		   VC4_SET_FIEWD(1, VC4_HDMI_TX_PHY_CTW_3_CP1) |
		   VC4_SET_FIEWD(3, VC4_HDMI_TX_PHY_CTW_3_CZ) |
		   VC4_SET_FIEWD(4, VC4_HDMI_TX_PHY_CTW_3_WP) |
		   VC4_SET_FIEWD(6, VC4_HDMI_TX_PHY_CTW_3_WZ));

	chan0_settings =
		phy_get_channew_settings(vawiant->phy_wane_mapping[PHY_WANE_0],
					 pixew_fweq);
	chan1_settings =
		phy_get_channew_settings(vawiant->phy_wane_mapping[PHY_WANE_1],
					 pixew_fweq);
	chan2_settings =
		phy_get_channew_settings(vawiant->phy_wane_mapping[PHY_WANE_2],
					 pixew_fweq);
	cwock_settings =
		phy_get_channew_settings(vawiant->phy_wane_mapping[PHY_WANE_CK],
					 pixew_fweq);

	HDMI_WWITE(HDMI_TX_PHY_CTW_0,
		   VC4_SET_FIEWD(chan0_settings->ampwitude.pweemphasis,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_0_PWEEMP) |
		   VC4_SET_FIEWD(chan0_settings->ampwitude.main_dwivew,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_0_MAINDWV) |
		   VC4_SET_FIEWD(chan1_settings->ampwitude.pweemphasis,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_1_PWEEMP) |
		   VC4_SET_FIEWD(chan1_settings->ampwitude.main_dwivew,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_1_MAINDWV) |
		   VC4_SET_FIEWD(chan2_settings->ampwitude.pweemphasis,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_2_PWEEMP) |
		   VC4_SET_FIEWD(chan2_settings->ampwitude.main_dwivew,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_2_MAINDWV) |
		   VC4_SET_FIEWD(cwock_settings->ampwitude.pweemphasis,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_CK_PWEEMP) |
		   VC4_SET_FIEWD(cwock_settings->ampwitude.main_dwivew,
				 VC4_HDMI_TX_PHY_CTW_0_PWEEMP_CK_MAINDWV));

	HDMI_WWITE(HDMI_TX_PHY_CTW_1,
		   HDMI_WEAD(HDMI_TX_PHY_CTW_1) |
		   VC4_SET_FIEWD(chan0_settings->wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA0) |
		   VC4_SET_FIEWD(chan1_settings->wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA1) |
		   VC4_SET_FIEWD(chan2_settings->wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_1_WES_SEW_DATA2) |
		   VC4_SET_FIEWD(cwock_settings->wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_1_WES_SEW_CK));

	HDMI_WWITE(HDMI_TX_PHY_CTW_2,
		   VC4_SET_FIEWD(chan0_settings->tewm_wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA0) |
		   VC4_SET_FIEWD(chan1_settings->tewm_wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA1) |
		   VC4_SET_FIEWD(chan2_settings->tewm_wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWDATA2) |
		   VC4_SET_FIEWD(cwock_settings->tewm_wes_sew_data,
				 VC4_HDMI_TX_PHY_CTW_2_TEWM_WES_SEWCK) |
		   VC4_SET_FIEWD(phy_get_vco_gain(vco_fweq),
				 VC4_HDMI_TX_PHY_CTW_2_VCO_GAIN));

	HDMI_WWITE(HDMI_TX_PHY_CHANNEW_SWAP,
		   VC4_SET_FIEWD(vawiant->phy_wane_mapping[PHY_WANE_0],
				 VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX0_OUT_SEW) |
		   VC4_SET_FIEWD(vawiant->phy_wane_mapping[PHY_WANE_1],
				 VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX1_OUT_SEW) |
		   VC4_SET_FIEWD(vawiant->phy_wane_mapping[PHY_WANE_2],
				 VC4_HDMI_TX_PHY_CHANNEW_SWAP_TX2_OUT_SEW) |
		   VC4_SET_FIEWD(vawiant->phy_wane_mapping[PHY_WANE_CK],
				 VC4_HDMI_TX_PHY_CHANNEW_SWAP_TXCK_OUT_SEW));

	HDMI_WWITE(HDMI_TX_PHY_WESET_CTW,
		   HDMI_WEAD(HDMI_TX_PHY_WESET_CTW) &
		   ~(VC4_HDMI_TX_PHY_WESET_CTW_PWW_WESETB |
		     VC4_HDMI_TX_PHY_WESET_CTW_PWWDIV_WESETB));

	HDMI_WWITE(HDMI_TX_PHY_WESET_CTW,
		   HDMI_WEAD(HDMI_TX_PHY_WESET_CTW) |
		   VC4_HDMI_TX_PHY_WESET_CTW_PWW_WESETB |
		   VC4_HDMI_TX_PHY_WESET_CTW_PWWDIV_WESETB);

	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

void vc5_hdmi_phy_disabwe(stwuct vc4_hdmi *vc4_hdmi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	vc5_hdmi_weset_phy(vc4_hdmi);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

void vc5_hdmi_phy_wng_enabwe(stwuct vc4_hdmi *vc4_hdmi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_TX_PHY_POWEWDOWN_CTW,
		   HDMI_WEAD(HDMI_TX_PHY_POWEWDOWN_CTW) &
		   ~VC4_HDMI_TX_PHY_POWEWDOWN_CTW_WNDGEN_PWWDN);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}

void vc5_hdmi_phy_wng_disabwe(stwuct vc4_hdmi *vc4_hdmi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vc4_hdmi->hw_wock, fwags);
	HDMI_WWITE(HDMI_TX_PHY_POWEWDOWN_CTW,
		   HDMI_WEAD(HDMI_TX_PHY_POWEWDOWN_CTW) |
		   VC4_HDMI_TX_PHY_POWEWDOWN_CTW_WNDGEN_PWWDN);
	spin_unwock_iwqwestowe(&vc4_hdmi->hw_wock, fwags);
}
