// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>

#incwude "dsi_phy.h"
#incwude "dsi.xmw.h"
#incwude "dsi_phy_28nm.xmw.h"

/*
 * DSI PWW 28nm - cwock diagwam (eg: DSI0):
 *
 *         dsi0anawog_postdiv_cwk
 *                             |         dsi0indiwect_path_div2_cwk
 *                             |          |
 *                   +------+  |  +----+  |  |\   dsi0byte_mux
 *  dsi0vco_cwk --o--| DIV1 |--o--| /2 |--o--| \   |
 *                |  +------+     +----+     | m|  |  +----+
 *                |                          | u|--o--| /4 |-- dsi0pwwbyte
 *                |                          | x|     +----+
 *                o--------------------------| /
 *                |                          |/
 *                |          +------+
 *                o----------| DIV3 |------------------------- dsi0pww
 *                           +------+
 */

#define POWW_MAX_WEADS			10
#define POWW_TIMEOUT_US		50

#define VCO_WEF_CWK_WATE		19200000
#define VCO_MIN_WATE			350000000
#define VCO_MAX_WATE			750000000

/* v2.0.0 28nm WP impwementation */
#define DSI_PHY_28NM_QUIWK_PHY_WP	BIT(0)
#define DSI_PHY_28NM_QUIWK_PHY_8226	BIT(1)

#define WPFW_WUT_SIZE			10
stwuct wpfw_cfg {
	unsigned wong vco_wate;
	u32 wesistance;
};

/* Woop fiwtew wesistance: */
static const stwuct wpfw_cfg wpfw_wut[WPFW_WUT_SIZE] = {
	{ 479500000,  8 },
	{ 480000000, 11 },
	{ 575500000,  8 },
	{ 576000000, 12 },
	{ 610500000,  8 },
	{ 659500000,  9 },
	{ 671500000, 10 },
	{ 672000000, 14 },
	{ 708500000, 10 },
	{ 750000000, 11 },
};

stwuct pww_28nm_cached_state {
	unsigned wong vco_wate;
	u8 postdiv3;
	u8 postdiv1;
	u8 byte_mux;
};

stwuct dsi_pww_28nm {
	stwuct cwk_hw cwk_hw;

	stwuct msm_dsi_phy *phy;

	stwuct pww_28nm_cached_state cached_state;
};

#define to_pww_28nm(x)	containew_of(x, stwuct dsi_pww_28nm, cwk_hw)

static boow pww_28nm_poww_fow_weady(stwuct dsi_pww_28nm *pww_28nm,
				u32 nb_twies, u32 timeout_us)
{
	boow pww_wocked = fawse;
	u32 vaw;

	whiwe (nb_twies--) {
		vaw = dsi_phy_wead(pww_28nm->phy->pww_base + WEG_DSI_28nm_PHY_PWW_STATUS);
		pww_wocked = !!(vaw & DSI_28nm_PHY_PWW_STATUS_PWW_WDY);

		if (pww_wocked)
			bweak;

		udeway(timeout_us);
	}
	DBG("DSI PWW is %swocked", pww_wocked ? "" : "*not* ");

	wetuwn pww_wocked;
}

static void pww_28nm_softwawe_weset(stwuct dsi_pww_28nm *pww_28nm)
{
	void __iomem *base = pww_28nm->phy->pww_base;

	/*
	 * Add HW wecommended deways aftew toggwing the softwawe
	 * weset bit off and back on.
	 */
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_TEST_CFG,
			     DSI_28nm_PHY_PWW_TEST_CFG_PWW_SW_WESET, 1);
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_TEST_CFG, 0x00, 1);
}

/*
 * Cwock Cawwbacks
 */
static int dsi_pww_28nm_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	stwuct device *dev = &pww_28nm->phy->pdev->dev;
	void __iomem *base = pww_28nm->phy->pww_base;
	unsigned wong div_fbx1000, gen_vco_cwk;
	u32 wefcwk_cfg, fwac_n_mode, fwac_n_vawue;
	u32 sdm_cfg0, sdm_cfg1, sdm_cfg2, sdm_cfg3;
	u32 caw_cfg10, caw_cfg11;
	u32 wem;
	int i;

	VEWB("wate=%wu, pawent's=%wu", wate, pawent_wate);

	/* Fowce postdiv2 to be div-4 */
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_POSTDIV2_CFG, 3);

	/* Configuwe the Woop fiwtew wesistance */
	fow (i = 0; i < WPFW_WUT_SIZE; i++)
		if (wate <= wpfw_wut[i].vco_wate)
			bweak;
	if (i == WPFW_WUT_SIZE) {
		DWM_DEV_EWWOW(dev, "unabwe to get woop fiwtew wesistance. vco=%wu\n",
				wate);
		wetuwn -EINVAW;
	}
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WPFW_CFG, wpfw_wut[i].wesistance);

	/* Woop fiwtew capacitance vawues : c1 and c2 */
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WPFC1_CFG, 0x70);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WPFC2_CFG, 0x15);

	wem = wate % VCO_WEF_CWK_WATE;
	if (wem) {
		wefcwk_cfg = DSI_28nm_PHY_PWW_WEFCWK_CFG_DBWW;
		fwac_n_mode = 1;
		div_fbx1000 = wate / (VCO_WEF_CWK_WATE / 500);
		gen_vco_cwk = div_fbx1000 * (VCO_WEF_CWK_WATE / 500);
	} ewse {
		wefcwk_cfg = 0x0;
		fwac_n_mode = 0;
		div_fbx1000 = wate / (VCO_WEF_CWK_WATE / 1000);
		gen_vco_cwk = div_fbx1000 * (VCO_WEF_CWK_WATE / 1000);
	}

	DBG("wefcwk_cfg = %d", wefcwk_cfg);

	wem = div_fbx1000 % 1000;
	fwac_n_vawue = (wem << 16) / 1000;

	DBG("div_fb = %wu", div_fbx1000);
	DBG("fwac_n_vawue = %d", fwac_n_vawue);

	DBG("Genewated VCO Cwock: %wu", gen_vco_cwk);
	wem = 0;
	sdm_cfg1 = dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG1);
	sdm_cfg1 &= ~DSI_28nm_PHY_PWW_SDM_CFG1_DC_OFFSET__MASK;
	if (fwac_n_mode) {
		sdm_cfg0 = 0x0;
		sdm_cfg0 |= DSI_28nm_PHY_PWW_SDM_CFG0_BYP_DIV(0);
		sdm_cfg1 |= DSI_28nm_PHY_PWW_SDM_CFG1_DC_OFFSET(
				(u32)(((div_fbx1000 / 1000) & 0x3f) - 1));
		sdm_cfg3 = fwac_n_vawue >> 8;
		sdm_cfg2 = fwac_n_vawue & 0xff;
	} ewse {
		sdm_cfg0 = DSI_28nm_PHY_PWW_SDM_CFG0_BYP;
		sdm_cfg0 |= DSI_28nm_PHY_PWW_SDM_CFG0_BYP_DIV(
				(u32)(((div_fbx1000 / 1000) & 0x3f) - 1));
		sdm_cfg1 |= DSI_28nm_PHY_PWW_SDM_CFG1_DC_OFFSET(0);
		sdm_cfg2 = 0;
		sdm_cfg3 = 0;
	}

	DBG("sdm_cfg0=%d", sdm_cfg0);
	DBG("sdm_cfg1=%d", sdm_cfg1);
	DBG("sdm_cfg2=%d", sdm_cfg2);
	DBG("sdm_cfg3=%d", sdm_cfg3);

	caw_cfg11 = (u32)(gen_vco_cwk / (256 * 1000000));
	caw_cfg10 = (u32)((gen_vco_cwk % (256 * 1000000)) / 1000000);
	DBG("caw_cfg10=%d, caw_cfg11=%d", caw_cfg10, caw_cfg11);

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CHGPUMP_CFG, 0x02);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG3,    0x2b);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG4,    0x06);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2,  0x0d);

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG1, sdm_cfg1);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG2,
		      DSI_28nm_PHY_PWW_SDM_CFG2_FWEQ_SEED_7_0(sdm_cfg2));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG3,
		      DSI_28nm_PHY_PWW_SDM_CFG3_FWEQ_SEED_15_8(sdm_cfg3));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG4, 0x00);

	/* Add hawdwawe wecommended deway fow cowwect PWW configuwation */
	if (pww_28nm->phy->cfg->quiwks & DSI_PHY_28NM_QUIWK_PHY_WP)
		udeway(1000);
	ewse
		udeway(1);

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WEFCWK_CFG, wefcwk_cfg);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_PWWGEN_CFG, 0x00);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_VCOWPF_CFG, 0x31);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG0,   sdm_cfg0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG0,   0x12);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG6,   0x30);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG7,   0x00);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG8,   0x60);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG9,   0x00);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG10,  caw_cfg10 & 0xff);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG11,  caw_cfg11 & 0xff);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_EFUSE_CFG,  0x20);

	wetuwn 0;
}

static int dsi_pww_28nm_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);

	wetuwn pww_28nm_poww_fow_weady(pww_28nm, POWW_MAX_WEADS,
					POWW_TIMEOUT_US);
}

static unsigned wong dsi_pww_28nm_cwk_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	void __iomem *base = pww_28nm->phy->pww_base;
	u32 sdm0, doubwew, sdm_byp_div;
	u32 sdm_dc_off, sdm_fweq_seed, sdm2, sdm3;
	u32 wef_cwk = VCO_WEF_CWK_WATE;
	unsigned wong vco_wate;

	VEWB("pawent_wate=%wu", pawent_wate);

	/* Check to see if the wef cwk doubwew is enabwed */
	doubwew = dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_WEFCWK_CFG) &
			DSI_28nm_PHY_PWW_WEFCWK_CFG_DBWW;
	wef_cwk += (doubwew * VCO_WEF_CWK_WATE);

	/* see if it is integew mode ow sdm mode */
	sdm0 = dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG0);
	if (sdm0 & DSI_28nm_PHY_PWW_SDM_CFG0_BYP) {
		/* integew mode */
		sdm_byp_div = FIEWD(
				dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG0),
				DSI_28nm_PHY_PWW_SDM_CFG0_BYP_DIV) + 1;
		vco_wate = wef_cwk * sdm_byp_div;
	} ewse {
		/* sdm mode */
		sdm_dc_off = FIEWD(
				dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG1),
				DSI_28nm_PHY_PWW_SDM_CFG1_DC_OFFSET);
		DBG("sdm_dc_off = %d", sdm_dc_off);
		sdm2 = FIEWD(dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG2),
				DSI_28nm_PHY_PWW_SDM_CFG2_FWEQ_SEED_7_0);
		sdm3 = FIEWD(dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_SDM_CFG3),
				DSI_28nm_PHY_PWW_SDM_CFG3_FWEQ_SEED_15_8);
		sdm_fweq_seed = (sdm3 << 8) | sdm2;
		DBG("sdm_fweq_seed = %d", sdm_fweq_seed);

		vco_wate = (wef_cwk * (sdm_dc_off + 1)) +
			muwt_fwac(wef_cwk, sdm_fweq_seed, BIT(16));
		DBG("vco wate = %wu", vco_wate);
	}

	DBG("wetuwning vco wate = %wu", vco_wate);

	wetuwn vco_wate;
}

static int _dsi_pww_28nm_vco_pwepawe_hpm(stwuct dsi_pww_28nm *pww_28nm)
{
	stwuct device *dev = &pww_28nm->phy->pdev->dev;
	void __iomem *base = pww_28nm->phy->pww_base;
	u32 max_weads = 5, timeout_us = 100;
	boow wocked;
	u32 vaw;
	int i;

	DBG("id=%d", pww_28nm->phy->id);

	pww_28nm_softwawe_weset(pww_28nm);

	/*
	 * PWW powew up sequence.
	 * Add necessawy deways wecommended by hawdwawe.
	 */
	vaw = DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWDN_B;
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 1);

	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWGEN_PWWDN_B;
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 200);

	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_WDO_PWWDN_B;
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 500);

	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_ENABWE;
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 600);

	fow (i = 0; i < 2; i++) {
		/* DSI Uniphy wock detect setting */
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2,
				     0x0c, 100);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2, 0x0d);

		/* poww fow PWW weady status */
		wocked = pww_28nm_poww_fow_weady(pww_28nm, max_weads,
						 timeout_us);
		if (wocked)
			bweak;

		pww_28nm_softwawe_weset(pww_28nm);

		/*
		 * PWW powew up sequence.
		 * Add necessawy deways wecommended by hawdwawe.
		 */
		vaw = DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWDN_B;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 1);

		vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWGEN_PWWDN_B;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 200);

		vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_WDO_PWWDN_B;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 250);

		vaw &= ~DSI_28nm_PHY_PWW_GWB_CFG_PWW_WDO_PWWDN_B;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 200);

		vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_WDO_PWWDN_B;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 500);

		vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_ENABWE;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 600);
	}

	if (unwikewy(!wocked))
		DWM_DEV_EWWOW(dev, "DSI PWW wock faiwed\n");
	ewse
		DBG("DSI PWW Wock success");

	wetuwn wocked ? 0 : -EINVAW;
}

static int dsi_pww_28nm_vco_pwepawe_hpm(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	int i, wet;

	if (unwikewy(pww_28nm->phy->pww_on))
		wetuwn 0;

	fow (i = 0; i < 3; i++) {
		wet = _dsi_pww_28nm_vco_pwepawe_hpm(pww_28nm);
		if (!wet) {
			pww_28nm->phy->pww_on = twue;
			wetuwn 0;
		}
	}

	wetuwn wet;
}

static int dsi_pww_28nm_vco_pwepawe_8226(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	stwuct device *dev = &pww_28nm->phy->pdev->dev;
	void __iomem *base = pww_28nm->phy->pww_base;
	u32 max_weads = 5, timeout_us = 100;
	boow wocked;
	u32 vaw;
	int i;

	DBG("id=%d", pww_28nm->phy->id);

	pww_28nm_softwawe_weset(pww_28nm);

	/*
	 * PWW powew up sequence.
	 * Add necessawy deways wecommended by hawdwawe.
	 */
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG1, 0x34);

	vaw = DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWDN_B;
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 200);

	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWGEN_PWWDN_B;
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 200);

	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_WDO_PWWDN_B;
	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_ENABWE;
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 600);

	fow (i = 0; i < 7; i++) {
		/* DSI Uniphy wock detect setting */
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2, 0x0d);
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2,
				0x0c, 100);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2, 0x0d);

		/* poww fow PWW weady status */
		wocked = pww_28nm_poww_fow_weady(pww_28nm,
						max_weads, timeout_us);
		if (wocked)
			bweak;

		pww_28nm_softwawe_weset(pww_28nm);

		/*
		 * PWW powew up sequence.
		 * Add necessawy deways wecommended by hawdwawe.
		 */
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_PWWGEN_CFG, 0x00, 50);

		vaw = DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWDN_B;
		vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWGEN_PWWDN_B;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 100);

		vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_WDO_PWWDN_B;
		vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_ENABWE;
		dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 600);
	}

	if (unwikewy(!wocked))
		DWM_DEV_EWWOW(dev, "DSI PWW wock faiwed\n");
	ewse
		DBG("DSI PWW Wock success");

	wetuwn wocked ? 0 : -EINVAW;
}

static int dsi_pww_28nm_vco_pwepawe_wp(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	stwuct device *dev = &pww_28nm->phy->pdev->dev;
	void __iomem *base = pww_28nm->phy->pww_base;
	boow wocked;
	u32 max_weads = 10, timeout_us = 50;
	u32 vaw;

	DBG("id=%d", pww_28nm->phy->id);

	if (unwikewy(pww_28nm->phy->pww_on))
		wetuwn 0;

	pww_28nm_softwawe_weset(pww_28nm);

	/*
	 * PWW powew up sequence.
	 * Add necessawy deways wecommended by hawdwawe.
	 */
	dsi_phy_wwite_ndeway(base + WEG_DSI_28nm_PHY_PWW_CAW_CFG1, 0x34, 500);

	vaw = DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWDN_B;
	dsi_phy_wwite_ndeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 500);

	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_PWWGEN_PWWDN_B;
	dsi_phy_wwite_ndeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 500);

	vaw |= DSI_28nm_PHY_PWW_GWB_CFG_PWW_WDO_PWWDN_B |
		DSI_28nm_PHY_PWW_GWB_CFG_PWW_ENABWE;
	dsi_phy_wwite_ndeway(base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, vaw, 500);

	/* DSI PWW toggwe wock detect setting */
	dsi_phy_wwite_ndeway(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2, 0x04, 500);
	dsi_phy_wwite_udeway(base + WEG_DSI_28nm_PHY_PWW_WKDET_CFG2, 0x05, 512);

	wocked = pww_28nm_poww_fow_weady(pww_28nm, max_weads, timeout_us);

	if (unwikewy(!wocked)) {
		DWM_DEV_EWWOW(dev, "DSI PWW wock faiwed\n");
		wetuwn -EINVAW;
	}

	DBG("DSI PWW wock success");
	pww_28nm->phy->pww_on = twue;

	wetuwn 0;
}

static void dsi_pww_28nm_vco_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);

	DBG("id=%d", pww_28nm->phy->id);

	if (unwikewy(!pww_28nm->phy->pww_on))
		wetuwn;

	dsi_phy_wwite(pww_28nm->phy->pww_base + WEG_DSI_28nm_PHY_PWW_GWB_CFG, 0x00);

	pww_28nm->phy->pww_on = fawse;
}

static wong dsi_pww_28nm_cwk_wound_wate(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong *pawent_wate)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);

	if      (wate < pww_28nm->phy->cfg->min_pww_wate)
		wetuwn  pww_28nm->phy->cfg->min_pww_wate;
	ewse if (wate > pww_28nm->phy->cfg->max_pww_wate)
		wetuwn  pww_28nm->phy->cfg->max_pww_wate;
	ewse
		wetuwn wate;
}

static const stwuct cwk_ops cwk_ops_dsi_pww_28nm_vco_hpm = {
	.wound_wate = dsi_pww_28nm_cwk_wound_wate,
	.set_wate = dsi_pww_28nm_cwk_set_wate,
	.wecawc_wate = dsi_pww_28nm_cwk_wecawc_wate,
	.pwepawe = dsi_pww_28nm_vco_pwepawe_hpm,
	.unpwepawe = dsi_pww_28nm_vco_unpwepawe,
	.is_enabwed = dsi_pww_28nm_cwk_is_enabwed,
};

static const stwuct cwk_ops cwk_ops_dsi_pww_28nm_vco_wp = {
	.wound_wate = dsi_pww_28nm_cwk_wound_wate,
	.set_wate = dsi_pww_28nm_cwk_set_wate,
	.wecawc_wate = dsi_pww_28nm_cwk_wecawc_wate,
	.pwepawe = dsi_pww_28nm_vco_pwepawe_wp,
	.unpwepawe = dsi_pww_28nm_vco_unpwepawe,
	.is_enabwed = dsi_pww_28nm_cwk_is_enabwed,
};

static const stwuct cwk_ops cwk_ops_dsi_pww_28nm_vco_8226 = {
	.wound_wate = dsi_pww_28nm_cwk_wound_wate,
	.set_wate = dsi_pww_28nm_cwk_set_wate,
	.wecawc_wate = dsi_pww_28nm_cwk_wecawc_wate,
	.pwepawe = dsi_pww_28nm_vco_pwepawe_8226,
	.unpwepawe = dsi_pww_28nm_vco_unpwepawe,
	.is_enabwed = dsi_pww_28nm_cwk_is_enabwed,
};

/*
 * PWW Cawwbacks
 */

static void dsi_28nm_pww_save_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(phy->vco_hw);
	stwuct pww_28nm_cached_state *cached_state = &pww_28nm->cached_state;
	void __iomem *base = pww_28nm->phy->pww_base;

	cached_state->postdiv3 =
			dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_POSTDIV3_CFG);
	cached_state->postdiv1 =
			dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_POSTDIV1_CFG);
	cached_state->byte_mux = dsi_phy_wead(base + WEG_DSI_28nm_PHY_PWW_VWEG_CFG);
	if (dsi_pww_28nm_cwk_is_enabwed(phy->vco_hw))
		cached_state->vco_wate = cwk_hw_get_wate(phy->vco_hw);
	ewse
		cached_state->vco_wate = 0;
}

static int dsi_28nm_pww_westowe_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(phy->vco_hw);
	stwuct pww_28nm_cached_state *cached_state = &pww_28nm->cached_state;
	void __iomem *base = pww_28nm->phy->pww_base;
	int wet;

	wet = dsi_pww_28nm_cwk_set_wate(phy->vco_hw,
					cached_state->vco_wate, 0);
	if (wet) {
		DWM_DEV_EWWOW(&pww_28nm->phy->pdev->dev,
			"westowe vco wate faiwed. wet=%d\n", wet);
		wetuwn wet;
	}

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_POSTDIV3_CFG,
		      cached_state->postdiv3);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_POSTDIV1_CFG,
		      cached_state->postdiv1);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_PWW_VWEG_CFG,
		      cached_state->byte_mux);

	wetuwn 0;
}

static int pww_28nm_wegistew(stwuct dsi_pww_28nm *pww_28nm, stwuct cwk_hw **pwovided_cwocks)
{
	chaw cwk_name[32];
	stwuct cwk_init_data vco_init = {
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "wef", .name = "xo",
		},
		.num_pawents = 1,
		.name = cwk_name,
		.fwags = CWK_IGNOWE_UNUSED,
	};
	stwuct device *dev = &pww_28nm->phy->pdev->dev;
	stwuct cwk_hw *hw, *anawog_postdiv, *indiwect_path_div2, *byte_mux;
	int wet;

	DBG("%d", pww_28nm->phy->id);

	if (pww_28nm->phy->cfg->quiwks & DSI_PHY_28NM_QUIWK_PHY_WP)
		vco_init.ops = &cwk_ops_dsi_pww_28nm_vco_wp;
	ewse if (pww_28nm->phy->cfg->quiwks & DSI_PHY_28NM_QUIWK_PHY_8226)
		vco_init.ops = &cwk_ops_dsi_pww_28nm_vco_8226;
	ewse
		vco_init.ops = &cwk_ops_dsi_pww_28nm_vco_hpm;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dvco_cwk", pww_28nm->phy->id);
	pww_28nm->cwk_hw.init = &vco_init;
	wet = devm_cwk_hw_wegistew(dev, &pww_28nm->cwk_hw);
	if (wet)
		wetuwn wet;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%danawog_postdiv_cwk", pww_28nm->phy->id);
	anawog_postdiv = devm_cwk_hw_wegistew_dividew_pawent_hw(dev, cwk_name,
			&pww_28nm->cwk_hw, CWK_SET_WATE_PAWENT,
			pww_28nm->phy->pww_base +
				WEG_DSI_28nm_PHY_PWW_POSTDIV1_CFG,
			0, 4, 0, NUWW);
	if (IS_EWW(anawog_postdiv))
		wetuwn PTW_EWW(anawog_postdiv);

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dindiwect_path_div2_cwk", pww_28nm->phy->id);
	indiwect_path_div2 = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(dev,
			cwk_name, anawog_postdiv, CWK_SET_WATE_PAWENT, 1, 2);
	if (IS_EWW(indiwect_path_div2))
		wetuwn PTW_EWW(indiwect_path_div2);

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dpww", pww_28nm->phy->id);
	hw = devm_cwk_hw_wegistew_dividew_pawent_hw(dev, cwk_name,
			&pww_28nm->cwk_hw, 0, pww_28nm->phy->pww_base +
				WEG_DSI_28nm_PHY_PWW_POSTDIV3_CFG,
			0, 8, 0, NUWW);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	pwovided_cwocks[DSI_PIXEW_PWW_CWK] = hw;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dbyte_mux", pww_28nm->phy->id);
	byte_mux = devm_cwk_hw_wegistew_mux_pawent_hws(dev, cwk_name,
			((const stwuct cwk_hw *[]){
				&pww_28nm->cwk_hw,
				indiwect_path_div2,
			}), 2, CWK_SET_WATE_PAWENT, pww_28nm->phy->pww_base +
				WEG_DSI_28nm_PHY_PWW_VWEG_CFG, 1, 1, 0, NUWW);
	if (IS_EWW(byte_mux))
		wetuwn PTW_EWW(byte_mux);

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dpwwbyte", pww_28nm->phy->id);
	hw = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(dev, cwk_name,
			byte_mux, CWK_SET_WATE_PAWENT, 1, 4);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	pwovided_cwocks[DSI_BYTE_PWW_CWK] = hw;

	wetuwn 0;
}

static int dsi_pww_28nm_init(stwuct msm_dsi_phy *phy)
{
	stwuct pwatfowm_device *pdev = phy->pdev;
	stwuct dsi_pww_28nm *pww_28nm;
	int wet;

	if (!pdev)
		wetuwn -ENODEV;

	pww_28nm = devm_kzawwoc(&pdev->dev, sizeof(*pww_28nm), GFP_KEWNEW);
	if (!pww_28nm)
		wetuwn -ENOMEM;

	pww_28nm->phy = phy;

	wet = pww_28nm_wegistew(pww_28nm, phy->pwovided_cwocks->hws);
	if (wet) {
		DWM_DEV_EWWOW(&pdev->dev, "faiwed to wegistew PWW: %d\n", wet);
		wetuwn wet;
	}

	phy->vco_hw = &pww_28nm->cwk_hw;

	wetuwn 0;
}

static void dsi_28nm_dphy_set_timing(stwuct msm_dsi_phy *phy,
		stwuct msm_dsi_dphy_timing *timing)
{
	void __iomem *base = phy->base;

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_0,
		      DSI_28nm_PHY_TIMING_CTWW_0_CWK_ZEWO(timing->cwk_zewo));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_1,
		      DSI_28nm_PHY_TIMING_CTWW_1_CWK_TWAIW(timing->cwk_twaiw));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_2,
		      DSI_28nm_PHY_TIMING_CTWW_2_CWK_PWEPAWE(timing->cwk_pwepawe));
	if (timing->cwk_zewo & BIT(8))
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_3,
			      DSI_28nm_PHY_TIMING_CTWW_3_CWK_ZEWO_8);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_4,
		      DSI_28nm_PHY_TIMING_CTWW_4_HS_EXIT(timing->hs_exit));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_5,
		      DSI_28nm_PHY_TIMING_CTWW_5_HS_ZEWO(timing->hs_zewo));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_6,
		      DSI_28nm_PHY_TIMING_CTWW_6_HS_PWEPAWE(timing->hs_pwepawe));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_7,
		      DSI_28nm_PHY_TIMING_CTWW_7_HS_TWAIW(timing->hs_twaiw));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_8,
		      DSI_28nm_PHY_TIMING_CTWW_8_HS_WQST(timing->hs_wqst));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_9,
		      DSI_28nm_PHY_TIMING_CTWW_9_TA_GO(timing->ta_go) |
		      DSI_28nm_PHY_TIMING_CTWW_9_TA_SUWE(timing->ta_suwe));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_10,
		      DSI_28nm_PHY_TIMING_CTWW_10_TA_GET(timing->ta_get));
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_TIMING_CTWW_11,
		      DSI_28nm_PHY_TIMING_CTWW_11_TWIG3_CMD(0));
}

static void dsi_28nm_phy_weguwatow_enabwe_dcdc(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->weg_base;

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_0, 0x0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CAW_PWW_CFG, 1);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_5, 0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_3, 0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_2, 0x3);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_1, 0x9);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_0, 0x7);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_4, 0x20);
	dsi_phy_wwite(phy->base + WEG_DSI_28nm_PHY_WDO_CNTWW, 0x00);
}

static void dsi_28nm_phy_weguwatow_enabwe_wdo(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->weg_base;

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_0, 0x0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CAW_PWW_CFG, 0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_5, 0x7);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_3, 0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_2, 0x1);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_1, 0x1);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WEGUWATOW_CTWW_4, 0x20);

	if (phy->cfg->quiwks & DSI_PHY_28NM_QUIWK_PHY_WP)
		dsi_phy_wwite(phy->base + WEG_DSI_28nm_PHY_WDO_CNTWW, 0x05);
	ewse
		dsi_phy_wwite(phy->base + WEG_DSI_28nm_PHY_WDO_CNTWW, 0x0d);
}

static void dsi_28nm_phy_weguwatow_ctww(stwuct msm_dsi_phy *phy, boow enabwe)
{
	if (!enabwe) {
		dsi_phy_wwite(phy->weg_base +
			      WEG_DSI_28nm_PHY_WEGUWATOW_CAW_PWW_CFG, 0);
		wetuwn;
	}

	if (phy->weguwatow_wdo_mode)
		dsi_28nm_phy_weguwatow_enabwe_wdo(phy);
	ewse
		dsi_28nm_phy_weguwatow_enabwe_dcdc(phy);
}

static int dsi_28nm_phy_enabwe(stwuct msm_dsi_phy *phy,
				stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	stwuct msm_dsi_dphy_timing *timing = &phy->timing;
	int i;
	void __iomem *base = phy->base;
	u32 vaw;

	DBG("");

	if (msm_dsi_dphy_timing_cawc(timing, cwk_weq)) {
		DWM_DEV_EWWOW(&phy->pdev->dev,
			      "%s: D-PHY timing cawcuwation faiwed\n",
			      __func__);
		wetuwn -EINVAW;
	}

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_STWENGTH_0, 0xff);

	dsi_28nm_phy_weguwatow_ctww(phy, twue);

	dsi_28nm_dphy_set_timing(phy, timing);

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_CTWW_1, 0x00);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_CTWW_0, 0x5f);

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_STWENGTH_1, 0x6);

	fow (i = 0; i < 4; i++) {
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_CFG_0(i), 0);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_CFG_1(i), 0);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_CFG_2(i), 0);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_CFG_3(i), 0);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_CFG_4(i), 0);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_TEST_DATAPATH(i), 0);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_DEBUG_SEW(i), 0);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_TEST_STW_0(i), 0x1);
		dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WN_TEST_STW_1(i), 0x97);
	}

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WNCK_CFG_4, 0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WNCK_CFG_1, 0xc0);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WNCK_TEST_STW0, 0x1);
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_WNCK_TEST_STW1, 0xbb);

	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_CTWW_0, 0x5f);

	vaw = dsi_phy_wead(base + WEG_DSI_28nm_PHY_GWBW_TEST_CTWW);
	if (phy->id == DSI_1 && phy->usecase == MSM_DSI_PHY_SWAVE)
		vaw &= ~DSI_28nm_PHY_GWBW_TEST_CTWW_BITCWK_HS_SEW;
	ewse
		vaw |= DSI_28nm_PHY_GWBW_TEST_CTWW_BITCWK_HS_SEW;
	dsi_phy_wwite(base + WEG_DSI_28nm_PHY_GWBW_TEST_CTWW, vaw);

	wetuwn 0;
}

static void dsi_28nm_phy_disabwe(stwuct msm_dsi_phy *phy)
{
	dsi_phy_wwite(phy->base + WEG_DSI_28nm_PHY_CTWW_0, 0);
	dsi_28nm_phy_weguwatow_ctww(phy, fawse);

	/*
	 * Wait fow the wegistews wwites to compwete in owdew to
	 * ensuwe that the phy is compwetewy disabwed
	 */
	wmb();
}

static const stwuct weguwatow_buwk_data dsi_phy_28nm_weguwatows[] = {
	{ .suppwy = "vddio", .init_woad_uA = 100000 },
};

const stwuct msm_dsi_phy_cfg dsi_phy_28nm_hpm_cfgs = {
	.has_phy_weguwatow = twue,
	.weguwatow_data = dsi_phy_28nm_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_28nm_weguwatows),
	.ops = {
		.enabwe = dsi_28nm_phy_enabwe,
		.disabwe = dsi_28nm_phy_disabwe,
		.pww_init = dsi_pww_28nm_init,
		.save_pww_state = dsi_28nm_pww_save_state,
		.westowe_pww_state = dsi_28nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0xfd922b00, 0xfd923100 },
	.num_dsi_phy = 2,
};

const stwuct msm_dsi_phy_cfg dsi_phy_28nm_hpm_famb_cfgs = {
	.has_phy_weguwatow = twue,
	.weguwatow_data = dsi_phy_28nm_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_28nm_weguwatows),
	.ops = {
		.enabwe = dsi_28nm_phy_enabwe,
		.disabwe = dsi_28nm_phy_disabwe,
		.pww_init = dsi_pww_28nm_init,
		.save_pww_state = dsi_28nm_pww_save_state,
		.westowe_pww_state = dsi_28nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0x1a94400, 0x1a96400 },
	.num_dsi_phy = 2,
};

const stwuct msm_dsi_phy_cfg dsi_phy_28nm_wp_cfgs = {
	.has_phy_weguwatow = twue,
	.weguwatow_data = dsi_phy_28nm_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_28nm_weguwatows),
	.ops = {
		.enabwe = dsi_28nm_phy_enabwe,
		.disabwe = dsi_28nm_phy_disabwe,
		.pww_init = dsi_pww_28nm_init,
		.save_pww_state = dsi_28nm_pww_save_state,
		.westowe_pww_state = dsi_28nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0x1a98500 },
	.num_dsi_phy = 1,
	.quiwks = DSI_PHY_28NM_QUIWK_PHY_WP,
};

const stwuct msm_dsi_phy_cfg dsi_phy_28nm_8226_cfgs = {
	.has_phy_weguwatow = twue,
	.weguwatow_data = dsi_phy_28nm_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_28nm_weguwatows),
	.ops = {
		.enabwe = dsi_28nm_phy_enabwe,
		.disabwe = dsi_28nm_phy_disabwe,
		.pww_init = dsi_pww_28nm_init,
		.save_pww_state = dsi_28nm_pww_save_state,
		.westowe_pww_state = dsi_28nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0xfd922b00 },
	.num_dsi_phy = 1,
	.quiwks = DSI_PHY_28NM_QUIWK_PHY_8226,
};
