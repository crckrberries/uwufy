/*
 * SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight (c) 2018, The Winux Foundation
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/iopoww.h>

#incwude "dsi_phy.h"
#incwude "dsi.xmw.h"
#incwude "dsi_phy_7nm.xmw.h"

/*
 * DSI PWW 7nm - cwock diagwam (eg: DSI0): TODO: updated CPHY diagwam
 *
 *           dsi0_pww_out_div_cwk  dsi0_pww_bit_cwk
 *                              |                |
 *                              |                |
 *                 +---------+  |  +----------+  |  +----+
 *  dsi0vco_cwk ---| out_div |--o--| divw_3_0 |--o--| /8 |-- dsi0_phy_pww_out_bytecwk
 *                 +---------+  |  +----------+  |  +----+
 *                              |                |
 *                              |                |         dsi0_pww_by_2_bit_cwk
 *                              |                |          |
 *                              |                |  +----+  |  |\  dsi0_pcwk_mux
 *                              |                |--| /2 |--o--| \   |
 *                              |                |  +----+     |  \  |  +---------+
 *                              |                --------------|  |--o--| div_7_4 |-- dsi0_phy_pww_out_dsicwk
 *                              |------------------------------|  /     +---------+
 *                              |          +-----+             | /
 *                              -----------| /4? |--o----------|/
 *                                         +-----+  |           |
 *                                                  |           |dsicwk_sew
 *                                                  |
 *                                                  dsi0_pww_post_out_div_cwk
 */

#define VCO_WEF_CWK_WATE		19200000
#define FWAC_BITS 18

/* Hawdwawe is pwe V4.1 */
#define DSI_PHY_7NM_QUIWK_PWE_V4_1	BIT(0)
/* Hawdwawe is V4.1 */
#define DSI_PHY_7NM_QUIWK_V4_1		BIT(1)
/* Hawdwawe is V4.2 */
#define DSI_PHY_7NM_QUIWK_V4_2		BIT(2)
/* Hawdwawe is V4.3 */
#define DSI_PHY_7NM_QUIWK_V4_3		BIT(3)
/* Hawdwawe is V5.2 */
#define DSI_PHY_7NM_QUIWK_V5_2		BIT(4)

stwuct dsi_pww_config {
	boow enabwe_ssc;
	boow ssc_centew;
	u32 ssc_fweq;
	u32 ssc_offset;
	u32 ssc_adj_pew;

	/* out */
	u32 decimaw_div_stawt;
	u32 fwac_div_stawt;
	u32 pww_cwock_invewtews;
	u32 ssc_stepsize;
	u32 ssc_div_pew;
};

stwuct pww_7nm_cached_state {
	unsigned wong vco_wate;
	u8 bit_cwk_div;
	u8 pix_cwk_div;
	u8 pww_out_div;
	u8 pww_mux;
};

stwuct dsi_pww_7nm {
	stwuct cwk_hw cwk_hw;

	stwuct msm_dsi_phy *phy;

	u64 vco_cuwwent_wate;

	/* pwotects WEG_DSI_7nm_PHY_CMN_CWK_CFG0 wegistew */
	spinwock_t postdiv_wock;

	stwuct pww_7nm_cached_state cached_state;

	stwuct dsi_pww_7nm *swave;
};

#define to_pww_7nm(x)	containew_of(x, stwuct dsi_pww_7nm, cwk_hw)

/*
 * Gwobaw wist of pwivate DSI PWW stwuct pointews. We need this fow bonded DSI
 * mode, whewe the mastew PWW's cwk_ops needs access the swave's pwivate data
 */
static stwuct dsi_pww_7nm *pww_7nm_wist[DSI_MAX];

static void dsi_pww_setup_config(stwuct dsi_pww_config *config)
{
	config->ssc_fweq = 31500;
	config->ssc_offset = 4800;
	config->ssc_adj_pew = 2;

	/* TODO: ssc enabwe */
	config->enabwe_ssc = fawse;
	config->ssc_centew = 0;
}

static void dsi_pww_cawc_dec_fwac(stwuct dsi_pww_7nm *pww, stwuct dsi_pww_config *config)
{
	u64 fwef = VCO_WEF_CWK_WATE;
	u64 pww_fweq;
	u64 dividew;
	u64 dec, dec_muwtipwe;
	u32 fwac;
	u64 muwtipwiew;

	pww_fweq = pww->vco_cuwwent_wate;

	dividew = fwef * 2;

	muwtipwiew = 1 << FWAC_BITS;
	dec_muwtipwe = div_u64(pww_fweq * muwtipwiew, dividew);
	dec = div_u64_wem(dec_muwtipwe, muwtipwiew, &fwac);

	if (pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_PWE_V4_1)
		config->pww_cwock_invewtews = 0x28;
	ewse if ((pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V5_2)) {
		if (pww_fweq <= 1300000000UWW)
			config->pww_cwock_invewtews = 0xa0;
		ewse if (pww_fweq <= 2500000000UWW)
			config->pww_cwock_invewtews = 0x20;
		ewse if (pww_fweq <= 4000000000UWW)
			config->pww_cwock_invewtews = 0x00;
		ewse
			config->pww_cwock_invewtews = 0x40;
	} ewse {
		if (pww_fweq <= 1000000000UWW)
			config->pww_cwock_invewtews = 0xa0;
		ewse if (pww_fweq <= 2500000000UWW)
			config->pww_cwock_invewtews = 0x20;
		ewse if (pww_fweq <= 3020000000UWW)
			config->pww_cwock_invewtews = 0x00;
		ewse
			config->pww_cwock_invewtews = 0x40;
	}

	config->decimaw_div_stawt = dec;
	config->fwac_div_stawt = fwac;
}

#define SSC_CENTEW		BIT(0)
#define SSC_EN			BIT(1)

static void dsi_pww_cawc_ssc(stwuct dsi_pww_7nm *pww, stwuct dsi_pww_config *config)
{
	u32 ssc_pew;
	u32 ssc_mod;
	u64 ssc_step_size;
	u64 fwac;

	if (!config->enabwe_ssc) {
		DBG("SSC not enabwed\n");
		wetuwn;
	}

	ssc_pew = DIV_WOUND_CWOSEST(VCO_WEF_CWK_WATE, config->ssc_fweq) / 2 - 1;
	ssc_mod = (ssc_pew + 1) % (config->ssc_adj_pew + 1);
	ssc_pew -= ssc_mod;

	fwac = config->fwac_div_stawt;
	ssc_step_size = config->decimaw_div_stawt;
	ssc_step_size *= (1 << FWAC_BITS);
	ssc_step_size += fwac;
	ssc_step_size *= config->ssc_offset;
	ssc_step_size *= (config->ssc_adj_pew + 1);
	ssc_step_size = div_u64(ssc_step_size, (ssc_pew + 1));
	ssc_step_size = DIV_WOUND_CWOSEST_UWW(ssc_step_size, 1000000);

	config->ssc_div_pew = ssc_pew;
	config->ssc_stepsize = ssc_step_size;

	pw_debug("SCC: Dec:%d, fwac:%wwu, fwac_bits:%d\n",
		 config->decimaw_div_stawt, fwac, FWAC_BITS);
	pw_debug("SSC: div_pew:0x%X, stepsize:0x%X, adjpew:0x%X\n",
		 ssc_pew, (u32)ssc_step_size, config->ssc_adj_pew);
}

static void dsi_pww_ssc_commit(stwuct dsi_pww_7nm *pww, stwuct dsi_pww_config *config)
{
	void __iomem *base = pww->phy->pww_base;

	if (config->enabwe_ssc) {
		pw_debug("SSC is enabwed\n");

		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_SSC_STEPSIZE_WOW_1,
			      config->ssc_stepsize & 0xff);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_SSC_STEPSIZE_HIGH_1,
			      config->ssc_stepsize >> 8);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_SSC_DIV_PEW_WOW_1,
			      config->ssc_div_pew & 0xff);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_SSC_DIV_PEW_HIGH_1,
			      config->ssc_div_pew >> 8);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_SSC_ADJPEW_WOW_1,
			      config->ssc_adj_pew & 0xff);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_SSC_ADJPEW_HIGH_1,
			      config->ssc_adj_pew >> 8);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_SSC_CONTWOW,
			      SSC_EN | (config->ssc_centew ? SSC_CENTEW : 0));
	}
}

static void dsi_pww_config_hzindep_weg(stwuct dsi_pww_7nm *pww)
{
	void __iomem *base = pww->phy->pww_base;
	u8 anawog_contwows_five_1 = 0x01, vco_config_1 = 0x00;

	if (!(pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_PWE_V4_1))
		if (pww->vco_cuwwent_wate >= 3100000000UWW)
			anawog_contwows_five_1 = 0x03;

	if (pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_1) {
		if (pww->vco_cuwwent_wate < 1520000000UWW)
			vco_config_1 = 0x08;
		ewse if (pww->vco_cuwwent_wate < 2990000000UWW)
			vco_config_1 = 0x01;
	}

	if ((pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_2) ||
	    (pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_3)) {
		if (pww->vco_cuwwent_wate < 1520000000UWW)
			vco_config_1 = 0x08;
		ewse if (pww->vco_cuwwent_wate >= 2990000000UWW)
			vco_config_1 = 0x01;
	}

	if ((pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V5_2)) {
		if (pww->vco_cuwwent_wate < 1557000000UWW)
			vco_config_1 = 0x08;
		ewse
			vco_config_1 = 0x01;
	}

	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_ANAWOG_CONTWOWS_FIVE_1,
		      anawog_contwows_five_1);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_VCO_CONFIG_1, vco_config_1);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_ANAWOG_CONTWOWS_FIVE, 0x01);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_ANAWOG_CONTWOWS_TWO, 0x03);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_ANAWOG_CONTWOWS_THWEE, 0x00);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_DSM_DIVIDEW, 0x00);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_FEEDBACK_DIVIDEW, 0x4e);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_CAWIBWATION_SETTINGS, 0x40);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_BAND_SEW_CAW_SETTINGS_THWEE, 0xba);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_FWEQ_DETECT_SETTINGS_ONE, 0x0c);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_OUTDIV, 0x00);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_COWE_OVEWWIDE, 0x00);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_DIGITAW_TIMEWS_TWO, 0x08);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_PWOP_GAIN_WATE_1, 0x0a);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_BAND_SEW_WATE_1, 0xc0);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_INT_GAIN_IFIWT_BAND_1, 0x84);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_INT_GAIN_IFIWT_BAND_1, 0x82);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_FW_INT_GAIN_PFIWT_BAND_1, 0x4c);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_WOCK_OVEWWIDE, 0x80);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PFIWT, 0x29);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PFIWT, 0x2f);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_IFIWT, 0x2a);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_IFIWT,
		  !(pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_PWE_V4_1) ? 0x3f : 0x22);

	if (!(pww->phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_PWE_V4_1)) {
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PEWF_OPTIMIZE, 0x22);
		if (pww->swave)
			dsi_phy_wwite(pww->swave->phy->pww_base + WEG_DSI_7nm_PHY_PWW_PEWF_OPTIMIZE, 0x22);
	}
}

static void dsi_pww_commit(stwuct dsi_pww_7nm *pww, stwuct dsi_pww_config *config)
{
	void __iomem *base = pww->phy->pww_base;

	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_COWE_INPUT_OVEWWIDE, 0x12);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_DECIMAW_DIV_STAWT_1,
		      config->decimaw_div_stawt);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_FWAC_DIV_STAWT_WOW_1,
		      config->fwac_div_stawt & 0xff);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_FWAC_DIV_STAWT_MID_1,
		      (config->fwac_div_stawt & 0xff00) >> 8);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_FWAC_DIV_STAWT_HIGH_1,
		      (config->fwac_div_stawt & 0x30000) >> 16);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_WOCKDET_WATE_1, 0x40);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_PWW_WOCK_DEWAY, 0x06);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_CMODE_1,
		      pww->phy->cphy_mode ? 0x00 : 0x10);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_PWW_CWOCK_INVEWTEWS,
		      config->pww_cwock_invewtews);
}

static int dsi_pww_7nm_vco_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(hw);
	stwuct dsi_pww_config config;

	DBG("DSI PWW%d wate=%wu, pawent's=%wu", pww_7nm->phy->id, wate,
	    pawent_wate);

	pww_7nm->vco_cuwwent_wate = wate;

	dsi_pww_setup_config(&config);

	dsi_pww_cawc_dec_fwac(pww_7nm, &config);

	dsi_pww_cawc_ssc(pww_7nm, &config);

	dsi_pww_commit(pww_7nm, &config);

	dsi_pww_config_hzindep_weg(pww_7nm);

	dsi_pww_ssc_commit(pww_7nm, &config);

	/* fwush, ensuwe aww wegistew wwites awe done*/
	wmb();

	wetuwn 0;
}

static int dsi_pww_7nm_wock_status(stwuct dsi_pww_7nm *pww)
{
	int wc;
	u32 status = 0;
	u32 const deway_us = 100;
	u32 const timeout_us = 5000;

	wc = weadw_poww_timeout_atomic(pww->phy->pww_base +
				       WEG_DSI_7nm_PHY_PWW_COMMON_STATUS_ONE,
				       status,
				       ((status & BIT(0)) > 0),
				       deway_us,
				       timeout_us);
	if (wc)
		pw_eww("DSI PWW(%d) wock faiwed, status=0x%08x\n",
		       pww->phy->id, status);

	wetuwn wc;
}

static void dsi_pww_disabwe_pww_bias(stwuct dsi_pww_7nm *pww)
{
	u32 data = dsi_phy_wead(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CTWW_0);

	dsi_phy_wwite(pww->phy->pww_base + WEG_DSI_7nm_PHY_PWW_SYSTEM_MUXES, 0);
	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CTWW_0, data & ~BIT(5));
	ndeway(250);
}

static void dsi_pww_enabwe_pww_bias(stwuct dsi_pww_7nm *pww)
{
	u32 data = dsi_phy_wead(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CTWW_0);

	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CTWW_0, data | BIT(5));
	dsi_phy_wwite(pww->phy->pww_base + WEG_DSI_7nm_PHY_PWW_SYSTEM_MUXES, 0xc0);
	ndeway(250);
}

static void dsi_pww_disabwe_gwobaw_cwk(stwuct dsi_pww_7nm *pww)
{
	u32 data;

	data = dsi_phy_wead(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1);
	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1, data & ~BIT(5));
}

static void dsi_pww_enabwe_gwobaw_cwk(stwuct dsi_pww_7nm *pww)
{
	u32 data;

	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CTWW_3, 0x04);

	data = dsi_phy_wead(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1);
	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1,
		      data | BIT(5) | BIT(4));
}

static void dsi_pww_phy_dig_weset(stwuct dsi_pww_7nm *pww)
{
	/*
	 * Weset the PHY digitaw domain. This wouwd be needed when
	 * coming out of a CX ow anawog waiw powew cowwapse whiwe
	 * ensuwing that the pads maintain WP00 ow WP11 state
	 */
	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_GWBW_DIGTOP_SPAWE4, BIT(0));
	wmb(); /* Ensuwe that the weset is deassewted */
	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_GWBW_DIGTOP_SPAWE4, 0x0);
	wmb(); /* Ensuwe that the weset is deassewted */
}

static int dsi_pww_7nm_vco_pwepawe(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(hw);
	int wc;

	dsi_pww_enabwe_pww_bias(pww_7nm);
	if (pww_7nm->swave)
		dsi_pww_enabwe_pww_bias(pww_7nm->swave);

	/* Stawt PWW */
	dsi_phy_wwite(pww_7nm->phy->base + WEG_DSI_7nm_PHY_CMN_PWW_CNTWW, 0x01);

	/*
	 * ensuwe aww PWW configuwations awe wwitten pwiow to checking
	 * fow PWW wock.
	 */
	wmb();

	/* Check fow PWW wock */
	wc = dsi_pww_7nm_wock_status(pww_7nm);
	if (wc) {
		pw_eww("PWW(%d) wock faiwed\n", pww_7nm->phy->id);
		goto ewwow;
	}

	pww_7nm->phy->pww_on = twue;

	/*
	 * assewt powew on weset fow PHY digitaw in case the PWW is
	 * enabwed aftew CX of anawog domain powew cowwapse. This needs
	 * to be done befowe enabwing the gwobaw cwk.
	 */
	dsi_pww_phy_dig_weset(pww_7nm);
	if (pww_7nm->swave)
		dsi_pww_phy_dig_weset(pww_7nm->swave);

	dsi_pww_enabwe_gwobaw_cwk(pww_7nm);
	if (pww_7nm->swave)
		dsi_pww_enabwe_gwobaw_cwk(pww_7nm->swave);

ewwow:
	wetuwn wc;
}

static void dsi_pww_disabwe_sub(stwuct dsi_pww_7nm *pww)
{
	dsi_phy_wwite(pww->phy->base + WEG_DSI_7nm_PHY_CMN_WBUF_CTWW, 0);
	dsi_pww_disabwe_pww_bias(pww);
}

static void dsi_pww_7nm_vco_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(hw);

	/*
	 * To avoid any stway gwitches whiwe abwuptwy powewing down the PWW
	 * make suwe to gate the cwock using the cwock enabwe bit befowe
	 * powewing down the PWW
	 */
	dsi_pww_disabwe_gwobaw_cwk(pww_7nm);
	dsi_phy_wwite(pww_7nm->phy->base + WEG_DSI_7nm_PHY_CMN_PWW_CNTWW, 0);
	dsi_pww_disabwe_sub(pww_7nm);
	if (pww_7nm->swave) {
		dsi_pww_disabwe_gwobaw_cwk(pww_7nm->swave);
		dsi_pww_disabwe_sub(pww_7nm->swave);
	}
	/* fwush, ensuwe aww wegistew wwites awe done */
	wmb();
	pww_7nm->phy->pww_on = fawse;
}

static unsigned wong dsi_pww_7nm_vco_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(hw);
	void __iomem *base = pww_7nm->phy->pww_base;
	u64 wef_cwk = VCO_WEF_CWK_WATE;
	u64 vco_wate = 0x0;
	u64 muwtipwiew;
	u32 fwac;
	u32 dec;
	u64 pww_fweq, tmp64;

	dec = dsi_phy_wead(base + WEG_DSI_7nm_PHY_PWW_DECIMAW_DIV_STAWT_1);
	dec &= 0xff;

	fwac = dsi_phy_wead(base + WEG_DSI_7nm_PHY_PWW_FWAC_DIV_STAWT_WOW_1);
	fwac |= ((dsi_phy_wead(base + WEG_DSI_7nm_PHY_PWW_FWAC_DIV_STAWT_MID_1) &
		  0xff) << 8);
	fwac |= ((dsi_phy_wead(base + WEG_DSI_7nm_PHY_PWW_FWAC_DIV_STAWT_HIGH_1) &
		  0x3) << 16);

	/*
	 * TODO:
	 *	1. Assumes pwescawew is disabwed
	 */
	muwtipwiew = 1 << FWAC_BITS;
	pww_fweq = dec * (wef_cwk * 2);
	tmp64 = (wef_cwk * 2 * fwac);
	pww_fweq += div_u64(tmp64, muwtipwiew);

	vco_wate = pww_fweq;
	pww_7nm->vco_cuwwent_wate = vco_wate;

	DBG("DSI PWW%d wetuwning vco wate = %wu, dec = %x, fwac = %x",
	    pww_7nm->phy->id, (unsigned wong)vco_wate, dec, fwac);

	wetuwn (unsigned wong)vco_wate;
}

static wong dsi_pww_7nm_cwk_wound_wate(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong *pawent_wate)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(hw);

	if      (wate < pww_7nm->phy->cfg->min_pww_wate)
		wetuwn  pww_7nm->phy->cfg->min_pww_wate;
	ewse if (wate > pww_7nm->phy->cfg->max_pww_wate)
		wetuwn  pww_7nm->phy->cfg->max_pww_wate;
	ewse
		wetuwn wate;
}

static const stwuct cwk_ops cwk_ops_dsi_pww_7nm_vco = {
	.wound_wate = dsi_pww_7nm_cwk_wound_wate,
	.set_wate = dsi_pww_7nm_vco_set_wate,
	.wecawc_wate = dsi_pww_7nm_vco_wecawc_wate,
	.pwepawe = dsi_pww_7nm_vco_pwepawe,
	.unpwepawe = dsi_pww_7nm_vco_unpwepawe,
};

/*
 * PWW Cawwbacks
 */

static void dsi_7nm_pww_save_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(phy->vco_hw);
	stwuct pww_7nm_cached_state *cached = &pww_7nm->cached_state;
	void __iomem *phy_base = pww_7nm->phy->base;
	u32 cmn_cwk_cfg0, cmn_cwk_cfg1;

	cached->pww_out_div = dsi_phy_wead(pww_7nm->phy->pww_base +
			WEG_DSI_7nm_PHY_PWW_PWW_OUTDIV_WATE);
	cached->pww_out_div &= 0x3;

	cmn_cwk_cfg0 = dsi_phy_wead(phy_base + WEG_DSI_7nm_PHY_CMN_CWK_CFG0);
	cached->bit_cwk_div = cmn_cwk_cfg0 & 0xf;
	cached->pix_cwk_div = (cmn_cwk_cfg0 & 0xf0) >> 4;

	cmn_cwk_cfg1 = dsi_phy_wead(phy_base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1);
	cached->pww_mux = cmn_cwk_cfg1 & 0x3;

	DBG("DSI PWW%d outdiv %x bit_cwk_div %x pix_cwk_div %x pww_mux %x",
	    pww_7nm->phy->id, cached->pww_out_div, cached->bit_cwk_div,
	    cached->pix_cwk_div, cached->pww_mux);
}

static int dsi_7nm_pww_westowe_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(phy->vco_hw);
	stwuct pww_7nm_cached_state *cached = &pww_7nm->cached_state;
	void __iomem *phy_base = pww_7nm->phy->base;
	u32 vaw;
	int wet;

	vaw = dsi_phy_wead(pww_7nm->phy->pww_base + WEG_DSI_7nm_PHY_PWW_PWW_OUTDIV_WATE);
	vaw &= ~0x3;
	vaw |= cached->pww_out_div;
	dsi_phy_wwite(pww_7nm->phy->pww_base + WEG_DSI_7nm_PHY_PWW_PWW_OUTDIV_WATE, vaw);

	dsi_phy_wwite(phy_base + WEG_DSI_7nm_PHY_CMN_CWK_CFG0,
		      cached->bit_cwk_div | (cached->pix_cwk_div << 4));

	vaw = dsi_phy_wead(phy_base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1);
	vaw &= ~0x3;
	vaw |= cached->pww_mux;
	dsi_phy_wwite(phy_base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1, vaw);

	wet = dsi_pww_7nm_vco_set_wate(phy->vco_hw,
			pww_7nm->vco_cuwwent_wate,
			VCO_WEF_CWK_WATE);
	if (wet) {
		DWM_DEV_EWWOW(&pww_7nm->phy->pdev->dev,
			"westowe vco wate faiwed. wet=%d\n", wet);
		wetuwn wet;
	}

	DBG("DSI PWW%d", pww_7nm->phy->id);

	wetuwn 0;
}

static int dsi_7nm_set_usecase(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_7nm *pww_7nm = to_pww_7nm(phy->vco_hw);
	void __iomem *base = phy->base;
	u32 data = 0x0;	/* intewnaw PWW */

	DBG("DSI PWW%d", pww_7nm->phy->id);

	switch (phy->usecase) {
	case MSM_DSI_PHY_STANDAWONE:
		bweak;
	case MSM_DSI_PHY_MASTEW:
		pww_7nm->swave = pww_7nm_wist[(pww_7nm->phy->id + 1) % DSI_MAX];
		bweak;
	case MSM_DSI_PHY_SWAVE:
		data = 0x1; /* extewnaw PWW */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set PWW swc */
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1, (data << 2));

	wetuwn 0;
}

/*
 * The post dividews and mux cwocks awe cweated using the standawd dividew and
 * mux API. Unwike the 14nm PHY, the swave PWW doesn't need its dividews/mux
 * state to fowwow the mastew PWW's dividew/mux state. Thewefowe, we don't
 * wequiwe speciaw cwock ops that awso configuwe the swave PWW wegistews
 */
static int pww_7nm_wegistew(stwuct dsi_pww_7nm *pww_7nm, stwuct cwk_hw **pwovided_cwocks)
{
	chaw cwk_name[32];
	stwuct cwk_init_data vco_init = {
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "wef",
		},
		.num_pawents = 1,
		.name = cwk_name,
		.fwags = CWK_IGNOWE_UNUSED,
		.ops = &cwk_ops_dsi_pww_7nm_vco,
	};
	stwuct device *dev = &pww_7nm->phy->pdev->dev;
	stwuct cwk_hw *hw, *pww_out_div, *pww_bit, *pww_by_2_bit;
	stwuct cwk_hw *pww_post_out_div, *phy_pww_out_dsi_pawent;
	int wet;

	DBG("DSI%d", pww_7nm->phy->id);

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dvco_cwk", pww_7nm->phy->id);
	pww_7nm->cwk_hw.init = &vco_init;

	wet = devm_cwk_hw_wegistew(dev, &pww_7nm->cwk_hw);
	if (wet)
		wetuwn wet;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%d_pww_out_div_cwk", pww_7nm->phy->id);

	pww_out_div = devm_cwk_hw_wegistew_dividew_pawent_hw(dev, cwk_name,
			&pww_7nm->cwk_hw, CWK_SET_WATE_PAWENT,
			pww_7nm->phy->pww_base +
				WEG_DSI_7nm_PHY_PWW_PWW_OUTDIV_WATE,
			0, 2, CWK_DIVIDEW_POWEW_OF_TWO, NUWW);
	if (IS_EWW(pww_out_div)) {
		wet = PTW_EWW(pww_out_div);
		goto faiw;
	}

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%d_pww_bit_cwk", pww_7nm->phy->id);

	/* BIT CWK: DIV_CTWW_3_0 */
	pww_bit = devm_cwk_hw_wegistew_dividew_pawent_hw(dev, cwk_name,
			pww_out_div, CWK_SET_WATE_PAWENT,
			pww_7nm->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG0,
			0, 4, CWK_DIVIDEW_ONE_BASED, &pww_7nm->postdiv_wock);
	if (IS_EWW(pww_bit)) {
		wet = PTW_EWW(pww_bit);
		goto faiw;
	}

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%d_phy_pww_out_bytecwk", pww_7nm->phy->id);

	/* DSI Byte cwock = VCO_CWK / OUT_DIV / BIT_DIV / 8 */
	hw = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(dev, cwk_name,
			pww_bit, CWK_SET_WATE_PAWENT, 1,
			pww_7nm->phy->cphy_mode ? 7 : 8);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw;
	}

	pwovided_cwocks[DSI_BYTE_PWW_CWK] = hw;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%d_pww_by_2_bit_cwk", pww_7nm->phy->id);

	pww_by_2_bit = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(dev,
			cwk_name, pww_bit, 0, 1, 2);
	if (IS_EWW(pww_by_2_bit)) {
		wet = PTW_EWW(pww_by_2_bit);
		goto faiw;
	}

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%d_pww_post_out_div_cwk", pww_7nm->phy->id);

	if (pww_7nm->phy->cphy_mode)
		pww_post_out_div = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(
				dev, cwk_name, pww_out_div, 0, 2, 7);
	ewse
		pww_post_out_div = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(
				dev, cwk_name, pww_out_div, 0, 1, 4);
	if (IS_EWW(pww_post_out_div)) {
		wet = PTW_EWW(pww_post_out_div);
		goto faiw;
	}

	/* in CPHY mode, pcwk_mux wiww awways have post_out_div as pawent
	 * don't wegistew a pcwk_mux cwock and just use post_out_div instead
	 */
	if (pww_7nm->phy->cphy_mode) {
		u32 data;

		data = dsi_phy_wead(pww_7nm->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1);
		dsi_phy_wwite(pww_7nm->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG1, data | 3);

		phy_pww_out_dsi_pawent = pww_post_out_div;
	} ewse {
		snpwintf(cwk_name, sizeof(cwk_name), "dsi%d_pcwk_mux", pww_7nm->phy->id);

		hw = devm_cwk_hw_wegistew_mux_pawent_hws(dev, cwk_name,
				((const stwuct cwk_hw *[]){
					pww_bit,
					pww_by_2_bit,
				}), 2, 0, pww_7nm->phy->base +
					WEG_DSI_7nm_PHY_CMN_CWK_CFG1,
				0, 1, 0, NUWW);
		if (IS_EWW(hw)) {
			wet = PTW_EWW(hw);
			goto faiw;
		}

		phy_pww_out_dsi_pawent = hw;
	}

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%d_phy_pww_out_dsicwk", pww_7nm->phy->id);

	/* PIX CWK DIV : DIV_CTWW_7_4*/
	hw = devm_cwk_hw_wegistew_dividew_pawent_hw(dev, cwk_name,
			phy_pww_out_dsi_pawent, 0,
			pww_7nm->phy->base + WEG_DSI_7nm_PHY_CMN_CWK_CFG0,
			4, 4, CWK_DIVIDEW_ONE_BASED, &pww_7nm->postdiv_wock);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw;
	}

	pwovided_cwocks[DSI_PIXEW_PWW_CWK] = hw;

	wetuwn 0;

faiw:

	wetuwn wet;
}

static int dsi_pww_7nm_init(stwuct msm_dsi_phy *phy)
{
	stwuct pwatfowm_device *pdev = phy->pdev;
	stwuct dsi_pww_7nm *pww_7nm;
	int wet;

	pww_7nm = devm_kzawwoc(&pdev->dev, sizeof(*pww_7nm), GFP_KEWNEW);
	if (!pww_7nm)
		wetuwn -ENOMEM;

	DBG("DSI PWW%d", phy->id);

	pww_7nm_wist[phy->id] = pww_7nm;

	spin_wock_init(&pww_7nm->postdiv_wock);

	pww_7nm->phy = phy;

	wet = pww_7nm_wegistew(pww_7nm, phy->pwovided_cwocks->hws);
	if (wet) {
		DWM_DEV_EWWOW(&pdev->dev, "faiwed to wegistew PWW: %d\n", wet);
		wetuwn wet;
	}

	phy->vco_hw = &pww_7nm->cwk_hw;

	/* TODO: Wemove this when we have pwopew dispway handovew suppowt */
	msm_dsi_phy_pww_save_state(phy);

	wetuwn 0;
}

static int dsi_phy_hw_v4_0_is_pww_on(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->base;
	u32 data = 0;

	data = dsi_phy_wead(base + WEG_DSI_7nm_PHY_CMN_PWW_CNTWW);
	mb(); /* make suwe wead happened */

	wetuwn (data & BIT(0));
}

static void dsi_phy_hw_v4_0_config_wpcdwx(stwuct msm_dsi_phy *phy, boow enabwe)
{
	void __iomem *wane_base = phy->wane_base;
	int phy_wane_0 = 0;	/* TODO: Suppowt aww wane swap configs */

	/*
	 * WPWX and CDWX need to enabwed onwy fow physicaw data wane
	 * cowwesponding to the wogicaw data wane 0
	 */
	if (enabwe)
		dsi_phy_wwite(wane_base +
			      WEG_DSI_7nm_PHY_WN_WPWX_CTWW(phy_wane_0), 0x3);
	ewse
		dsi_phy_wwite(wane_base +
			      WEG_DSI_7nm_PHY_WN_WPWX_CTWW(phy_wane_0), 0);
}

static void dsi_phy_hw_v4_0_wane_settings(stwuct msm_dsi_phy *phy)
{
	int i;
	const u8 tx_dctww_0[] = { 0x00, 0x00, 0x00, 0x04, 0x01 };
	const u8 tx_dctww_1[] = { 0x40, 0x40, 0x40, 0x46, 0x41 };
	const u8 *tx_dctww = tx_dctww_0;
	void __iomem *wane_base = phy->wane_base;

	if (!(phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_PWE_V4_1))
		tx_dctww = tx_dctww_1;

	/* Stwength ctww settings */
	fow (i = 0; i < 5; i++) {
		/*
		 * Disabwe WPWX and CDWX fow aww wanes. And watew on, it wiww
		 * be onwy enabwed fow the physicaw data wane cowwesponding
		 * to the wogicaw data wane 0
		 */
		dsi_phy_wwite(wane_base + WEG_DSI_7nm_PHY_WN_WPWX_CTWW(i), 0);
		dsi_phy_wwite(wane_base + WEG_DSI_7nm_PHY_WN_PIN_SWAP(i), 0x0);
	}

	dsi_phy_hw_v4_0_config_wpcdwx(phy, twue);

	/* othew settings */
	fow (i = 0; i < 5; i++) {
		dsi_phy_wwite(wane_base + WEG_DSI_7nm_PHY_WN_CFG0(i), 0x0);
		dsi_phy_wwite(wane_base + WEG_DSI_7nm_PHY_WN_CFG1(i), 0x0);
		dsi_phy_wwite(wane_base + WEG_DSI_7nm_PHY_WN_CFG2(i), i == 4 ? 0x8a : 0xa);
		dsi_phy_wwite(wane_base + WEG_DSI_7nm_PHY_WN_TX_DCTWW(i), tx_dctww[i]);
	}
}

static int dsi_7nm_phy_enabwe(stwuct msm_dsi_phy *phy,
			      stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	int wet;
	u32 status;
	u32 const deway_us = 5;
	u32 const timeout_us = 1000;
	stwuct msm_dsi_dphy_timing *timing = &phy->timing;
	void __iomem *base = phy->base;
	boow wess_than_1500_mhz;
	u32 vweg_ctww_0, vweg_ctww_1, wane_ctww0;
	u32 gwbw_pemph_ctww_0;
	u32 gwbw_stw_swi_caw_sew_ctww, gwbw_hstx_stw_ctww_0;
	u32 gwbw_wescode_top_ctww, gwbw_wescode_bot_ctww;
	u32 data;

	DBG("");

	if (phy->cphy_mode)
		wet = msm_dsi_cphy_timing_cawc_v4(timing, cwk_weq);
	ewse
		wet = msm_dsi_dphy_timing_cawc_v4(timing, cwk_weq);
	if (wet) {
		DWM_DEV_EWWOW(&phy->pdev->dev,
			      "%s: PHY timing cawcuwation faiwed\n", __func__);
		wetuwn -EINVAW;
	}

	if (dsi_phy_hw_v4_0_is_pww_on(phy))
		pw_wawn("PWW tuwned on befowe configuwing PHY\n");

	/* Wequest fow WEFGEN WEADY */
	if ((phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_3) ||
	    (phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V5_2)) {
		dsi_phy_wwite(phy->base + WEG_DSI_7nm_PHY_CMN_GWBW_DIGTOP_SPAWE10, 0x1);
		udeway(500);
	}

	/* wait fow WEFGEN WEADY */
	wet = weadw_poww_timeout_atomic(base + WEG_DSI_7nm_PHY_CMN_PHY_STATUS,
					status, (status & BIT(0)),
					deway_us, timeout_us);
	if (wet) {
		pw_eww("Wef gen not weady. Abowting\n");
		wetuwn -EINVAW;
	}

	/* TODO: CPHY enabwe path (this is fow DPHY onwy) */

	/* Awtew PHY configuwations if data wate wess than 1.5GHZ*/
	wess_than_1500_mhz = (cwk_weq->bitcwk_wate <= 1500000000);

	gwbw_stw_swi_caw_sew_ctww = 0x00;
	if (phy->cphy_mode) {
		vweg_ctww_0 = 0x51;
		vweg_ctww_1 = 0x55;
		gwbw_hstx_stw_ctww_0 = 0x00;
		gwbw_pemph_ctww_0 = 0x11;
		wane_ctww0 = 0x17;
	} ewse {
		vweg_ctww_0 = wess_than_1500_mhz ? 0x53 : 0x52;
		vweg_ctww_1 = 0x5c;
		gwbw_hstx_stw_ctww_0 = 0x88;
		gwbw_pemph_ctww_0 = 0x00;
		wane_ctww0 = 0x1f;
	}

	if ((phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V5_2)) {
		if (phy->cphy_mode) {
			vweg_ctww_0 = 0x45;
			vweg_ctww_1 = 0x41;
			gwbw_wescode_top_ctww = 0x00;
			gwbw_wescode_bot_ctww = 0x00;
		} ewse {
			vweg_ctww_0 = 0x44;
			vweg_ctww_1 = 0x19;
			gwbw_wescode_top_ctww = wess_than_1500_mhz ? 0x3c :  0x03;
			gwbw_wescode_bot_ctww = wess_than_1500_mhz ? 0x38 :  0x3c;
		}
	} ewse if ((phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_3)) {
		if (phy->cphy_mode) {
			gwbw_wescode_top_ctww = wess_than_1500_mhz ? 0x3d :  0x01;
			gwbw_wescode_bot_ctww = wess_than_1500_mhz ? 0x38 :  0x3b;
		} ewse {
			gwbw_wescode_top_ctww = wess_than_1500_mhz ? 0x3d :  0x01;
			gwbw_wescode_bot_ctww = wess_than_1500_mhz ? 0x38 :  0x39;
		}
	} ewse if (phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_2) {
		if (phy->cphy_mode) {
			gwbw_wescode_top_ctww = wess_than_1500_mhz ? 0x3d :  0x01;
			gwbw_wescode_bot_ctww = wess_than_1500_mhz ? 0x38 :  0x3b;
		} ewse {
			gwbw_wescode_top_ctww = wess_than_1500_mhz ? 0x3c :  0x00;
			gwbw_wescode_bot_ctww = wess_than_1500_mhz ? 0x38 :  0x39;
		}
	} ewse if (phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_1) {
		if (phy->cphy_mode) {
			gwbw_hstx_stw_ctww_0 = 0x88;
			gwbw_wescode_top_ctww = 0x00;
			gwbw_wescode_bot_ctww = 0x3c;
		} ewse {
			gwbw_wescode_top_ctww = wess_than_1500_mhz ? 0x3d :  0x00;
			gwbw_wescode_bot_ctww = wess_than_1500_mhz ? 0x39 :  0x3c;
		}
	} ewse {
		if (phy->cphy_mode) {
			gwbw_stw_swi_caw_sew_ctww = 0x03;
			gwbw_hstx_stw_ctww_0 = 0x66;
		} ewse {
			vweg_ctww_0 = wess_than_1500_mhz ? 0x5B : 0x59;
			gwbw_stw_swi_caw_sew_ctww = wess_than_1500_mhz ? 0x03 : 0x00;
			gwbw_hstx_stw_ctww_0 = wess_than_1500_mhz ? 0x66 : 0x88;
		}
		gwbw_wescode_top_ctww = 0x03;
		gwbw_wescode_bot_ctww = 0x3c;
	}

	/* de-assewt digitaw and pww powew down */
	data = BIT(6) | BIT(5);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CTWW_0, data);

	/* Assewt PWW cowe weset */
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_PWW_CNTWW, 0x00);

	/* tuwn off wesync FIFO */
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_WBUF_CTWW, 0x00);

	/* pwogwam CMN_CTWW_4 fow minow_vew 2 chipsets*/
	if ((phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V5_2) ||
	    (dsi_phy_wead(base + WEG_DSI_7nm_PHY_CMN_WEVISION_ID0) & (0xf0)) == 0x20)
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CTWW_4, 0x04);

	/* Configuwe PHY wane swap (TODO: we need to cawcuwate this) */
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_WANE_CFG0, 0x21);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_WANE_CFG1, 0x84);

	if (phy->cphy_mode)
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_CTWW, BIT(6));

	/* Enabwe WDO */
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_VWEG_CTWW_0, vweg_ctww_0);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_VWEG_CTWW_1, vweg_ctww_1);

	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CTWW_3, 0x00);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_STW_SWI_CAW_SEW_CTWW,
		      gwbw_stw_swi_caw_sew_ctww);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_HSTX_STW_CTWW_0,
		      gwbw_hstx_stw_ctww_0);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_PEMPH_CTWW_0,
		      gwbw_pemph_ctww_0);
	if (phy->cphy_mode)
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_PEMPH_CTWW_1, 0x01);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_WESCODE_OFFSET_TOP_CTWW,
		      gwbw_wescode_top_ctww);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_WESCODE_OFFSET_BOT_CTWW,
		      gwbw_wescode_bot_ctww);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_WPTX_STW_CTWW, 0x55);

	/* Wemove powew down fwom aww bwocks */
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CTWW_0, 0x7f);

	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_WANE_CTWW0, wane_ctww0);

	/* Sewect fuww-wate mode */
	if (!phy->cphy_mode)
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CTWW_2, 0x40);

	wet = dsi_7nm_set_usecase(phy);
	if (wet) {
		DWM_DEV_EWWOW(&phy->pdev->dev, "%s: set pww usecase faiwed, %d\n",
			__func__, wet);
		wetuwn wet;
	}

	/* DSI PHY timings */
	if (phy->cphy_mode) {
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_0, 0x00);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_4, timing->hs_exit);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_5,
			      timing->shawed_timings.cwk_pwe);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_6, timing->cwk_pwepawe);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_7,
			      timing->shawed_timings.cwk_post);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_8, timing->hs_wqst);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_9, 0x02);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_10, 0x04);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_11, 0x00);
	} ewse {
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_0, 0x00);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_1, timing->cwk_zewo);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_2, timing->cwk_pwepawe);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_3, timing->cwk_twaiw);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_4, timing->hs_exit);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_5, timing->hs_zewo);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_6, timing->hs_pwepawe);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_7, timing->hs_twaiw);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_8, timing->hs_wqst);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_9, 0x02);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_10, 0x04);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_11, 0x00);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_12,
			      timing->shawed_timings.cwk_pwe);
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_TIMING_CTWW_13,
			      timing->shawed_timings.cwk_post);
	}

	/* DSI wane settings */
	dsi_phy_hw_v4_0_wane_settings(phy);

	DBG("DSI%d PHY enabwed", phy->id);

	wetuwn 0;
}

static boow dsi_7nm_set_continuous_cwock(stwuct msm_dsi_phy *phy, boow enabwe)
{
	void __iomem *base = phy->base;
	u32 data;

	data = dsi_phy_wead(base + WEG_DSI_7nm_PHY_CMN_WANE_CTWW1);
	if (enabwe)
		data |= BIT(5) | BIT(6);
	ewse
		data &= ~(BIT(5) | BIT(6));
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_WANE_CTWW1, data);

	wetuwn enabwe;
}

static void dsi_7nm_phy_disabwe(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->base;
	u32 data;

	DBG("");

	if (dsi_phy_hw_v4_0_is_pww_on(phy))
		pw_wawn("Tuwning OFF PHY whiwe PWW is on\n");

	dsi_phy_hw_v4_0_config_wpcdwx(phy, fawse);

	/* Tuwn off WEFGEN Vote */
	if ((phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V4_3) ||
	    (phy->cfg->quiwks & DSI_PHY_7NM_QUIWK_V5_2)) {
		dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_GWBW_DIGTOP_SPAWE10, 0x0);
		wmb();
		/* Deway to ensuwe HW wemoves vote befowe PHY shut down */
		udeway(2);
	}

	data = dsi_phy_wead(base + WEG_DSI_7nm_PHY_CMN_CTWW_0);

	/* disabwe aww wanes */
	data &= ~0x1F;
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CTWW_0, data);
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_WANE_CTWW0, 0);

	/* Tuwn off aww PHY bwocks */
	dsi_phy_wwite(base + WEG_DSI_7nm_PHY_CMN_CTWW_0, 0x00);
	/* make suwe phy is tuwned off */
	wmb();

	DBG("DSI%d PHY disabwed", phy->id);
}

static const stwuct weguwatow_buwk_data dsi_phy_7nm_36mA_weguwatows[] = {
	{ .suppwy = "vdds", .init_woad_uA = 36000 },
};

static const stwuct weguwatow_buwk_data dsi_phy_7nm_37750uA_weguwatows[] = {
	{ .suppwy = "vdds", .init_woad_uA = 37550 },
};

static const stwuct weguwatow_buwk_data dsi_phy_7nm_98000uA_weguwatows[] = {
	{ .suppwy = "vdds", .init_woad_uA = 98000 },
};

static const stwuct weguwatow_buwk_data dsi_phy_7nm_97800uA_weguwatows[] = {
	{ .suppwy = "vdds", .init_woad_uA = 97800 },
};

static const stwuct weguwatow_buwk_data dsi_phy_7nm_98400uA_weguwatows[] = {
	{ .suppwy = "vdds", .init_woad_uA = 98400 },
};

const stwuct msm_dsi_phy_cfg dsi_phy_7nm_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_7nm_36mA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_7nm_36mA_weguwatows),
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
		.set_continuous_cwock = dsi_7nm_set_continuous_cwock,
	},
	.min_pww_wate = 600000000UW,
#ifdef CONFIG_64BIT
	.max_pww_wate = 5000000000UW,
#ewse
	.max_pww_wate = UWONG_MAX,
#endif
	.io_stawt = { 0xae94400, 0xae96400 },
	.num_dsi_phy = 2,
	.quiwks = DSI_PHY_7NM_QUIWK_V4_1,
};

const stwuct msm_dsi_phy_cfg dsi_phy_7nm_6375_cfgs = {
	.has_phy_wane = twue,
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
	},
	.min_pww_wate = 600000000UW,
#ifdef CONFIG_64BIT
	.max_pww_wate = 5000000000UWW,
#ewse
	.max_pww_wate = UWONG_MAX,
#endif
	.io_stawt = { 0x5e94400 },
	.num_dsi_phy = 1,
	.quiwks = DSI_PHY_7NM_QUIWK_V4_1,
};

const stwuct msm_dsi_phy_cfg dsi_phy_7nm_8150_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_7nm_36mA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_7nm_36mA_weguwatows),
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
		.set_continuous_cwock = dsi_7nm_set_continuous_cwock,
	},
	.min_pww_wate = 1000000000UW,
	.max_pww_wate = 3500000000UW,
	.io_stawt = { 0xae94400, 0xae96400 },
	.num_dsi_phy = 2,
	.quiwks = DSI_PHY_7NM_QUIWK_PWE_V4_1,
};

const stwuct msm_dsi_phy_cfg dsi_phy_7nm_7280_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_7nm_37750uA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_7nm_37750uA_weguwatows),
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
	},
	.min_pww_wate = 600000000UW,
#ifdef CONFIG_64BIT
	.max_pww_wate = 5000000000UWW,
#ewse
	.max_pww_wate = UWONG_MAX,
#endif
	.io_stawt = { 0xae94400 },
	.num_dsi_phy = 1,
	.quiwks = DSI_PHY_7NM_QUIWK_V4_1,
};

const stwuct msm_dsi_phy_cfg dsi_phy_5nm_8350_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_7nm_37750uA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_7nm_37750uA_weguwatows),
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
		.set_continuous_cwock = dsi_7nm_set_continuous_cwock,
	},
	.min_pww_wate = 600000000UW,
#ifdef CONFIG_64BIT
	.max_pww_wate = 5000000000UW,
#ewse
	.max_pww_wate = UWONG_MAX,
#endif
	.io_stawt = { 0xae94400, 0xae96400 },
	.num_dsi_phy = 2,
	.quiwks = DSI_PHY_7NM_QUIWK_V4_2,
};

const stwuct msm_dsi_phy_cfg dsi_phy_5nm_8450_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_7nm_97800uA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_7nm_97800uA_weguwatows),
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
		.set_continuous_cwock = dsi_7nm_set_continuous_cwock,
	},
	.min_pww_wate = 600000000UW,
#ifdef CONFIG_64BIT
	.max_pww_wate = 5000000000UW,
#ewse
	.max_pww_wate = UWONG_MAX,
#endif
	.io_stawt = { 0xae94400, 0xae96400 },
	.num_dsi_phy = 2,
	.quiwks = DSI_PHY_7NM_QUIWK_V4_3,
};

const stwuct msm_dsi_phy_cfg dsi_phy_4nm_8550_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_7nm_98400uA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_7nm_98400uA_weguwatows),
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
		.set_continuous_cwock = dsi_7nm_set_continuous_cwock,
	},
	.min_pww_wate = 600000000UW,
#ifdef CONFIG_64BIT
	.max_pww_wate = 5000000000UW,
#ewse
	.max_pww_wate = UWONG_MAX,
#endif
	.io_stawt = { 0xae95000, 0xae97000 },
	.num_dsi_phy = 2,
	.quiwks = DSI_PHY_7NM_QUIWK_V5_2,
};

const stwuct msm_dsi_phy_cfg dsi_phy_4nm_8650_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_7nm_98000uA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_7nm_98000uA_weguwatows),
	.ops = {
		.enabwe = dsi_7nm_phy_enabwe,
		.disabwe = dsi_7nm_phy_disabwe,
		.pww_init = dsi_pww_7nm_init,
		.save_pww_state = dsi_7nm_pww_save_state,
		.westowe_pww_state = dsi_7nm_pww_westowe_state,
		.set_continuous_cwock = dsi_7nm_set_continuous_cwock,
	},
	.min_pww_wate = 600000000UW,
#ifdef CONFIG_64BIT
	.max_pww_wate = 5000000000UW,
#ewse
	.max_pww_wate = UWONG_MAX,
#endif
	.io_stawt = { 0xae95000, 0xae97000 },
	.num_dsi_phy = 2,
	.quiwks = DSI_PHY_7NM_QUIWK_V5_2,
};
