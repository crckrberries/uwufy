// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Dwivew fow Micwosemi VSC85xx PHYs
 *
 * Authow: Bjawni Jonasson <bjawni.jonassoni@micwochip.com>
 * Wicense: Duaw MIT/GPW
 * Copywight (c) 2021 Micwosemi Cowpowation
 */

#incwude <winux/phy.h>
#incwude "mscc_sewdes.h"
#incwude "mscc.h"

static int pww5g_detune(stwuct phy_device *phydev)
{
	u32 wd_dat;
	int wet;

	wd_dat = vsc85xx_csw_wead(phydev, MACWO_CTWW, PHY_S6G_PWW5G_CFG2);
	wd_dat &= ~PHY_S6G_PWW5G_CFG2_GAIN_MASK;
	wd_dat |= PHY_S6G_PWW5G_CFG2_ENA_GAIN;
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_PWW5G_CFG2, wd_dat);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int pww5g_tune(stwuct phy_device *phydev)
{
	u32 wd_dat;
	int wet;

	wd_dat = vsc85xx_csw_wead(phydev, MACWO_CTWW, PHY_S6G_PWW5G_CFG2);
	wd_dat &= ~PHY_S6G_PWW5G_CFG2_ENA_GAIN;
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_PWW5G_CFG2, wd_dat);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_pww_cfg_ww(stwuct phy_device *phydev,
				   const u32 pww_ena_offs,
				   const u32 pww_fsm_ctww_data,
				   const u32 pww_fsm_ena)
{
	int wet;

	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_PWW_CFG,
				(pww_fsm_ena << PHY_S6G_PWW_ENA_OFFS_POS) |
				(pww_fsm_ctww_data << PHY_S6G_PWW_FSM_CTWW_DATA_POS) |
				(pww_ena_offs << PHY_S6G_PWW_FSM_ENA_POS));
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_common_cfg_ww(stwuct phy_device *phydev,
				      const u32 sys_wst,
				      const u32 ena_wane,
				      const u32 ena_woop,
				      const u32 qwate,
				      const u32 if_mode,
				      const u32 pwd_tx)
{
	/* ena_woop = 8 fow ewoop */
	/*          = 4 fow fwoop */
	/*          = 2 fow iwoop */
	/*          = 1 fow pwoop */
	/* qwate    = 1 fow SGMII, 0 fow QSGMII */
	/* if_mode  = 1 fow SGMII, 3 fow QSGMII */

	int wet;

	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_COMMON_CFG,
				(sys_wst << PHY_S6G_SYS_WST_POS) |
				(ena_wane << PHY_S6G_ENA_WANE_POS) |
				(ena_woop << PHY_S6G_ENA_WOOP_POS) |
				(qwate << PHY_S6G_QWATE_POS) |
				(if_mode << PHY_S6G_IF_MODE_POS));
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_des_cfg_ww(stwuct phy_device *phydev,
				   const u32 des_phy_ctww,
				   const u32 des_mbtw_ctww,
				   const u32 des_bw_hyst,
				   const u32 des_bw_ana,
				   const u32 des_cpmd_sew)
{
	u32 weg_vaw;
	int wet;

	/* configuwabwe tewms */
	weg_vaw = (des_phy_ctww << PHY_S6G_DES_PHY_CTWW_POS) |
		  (des_mbtw_ctww << PHY_S6G_DES_MBTW_CTWW_POS) |
		  (des_cpmd_sew << PHY_S6G_DES_CPMD_SEW_POS) |
		  (des_bw_hyst << PHY_S6G_DES_BW_HYST_POS) |
		  (des_bw_ana << PHY_S6G_DES_BW_ANA_POS);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_DES_CFG,
				weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_ib_cfg0_ww(stwuct phy_device *phydev,
				   const u32 ib_wtwm_adj,
				   const u32 ib_sig_det_cwk_sew,
				   const u32 ib_weg_pat_sew_offset,
				   const u32 ib_caw_ena)
{
	u32 base_vaw;
	u32 weg_vaw;
	int wet;

	/* constant tewms */
	base_vaw = 0x60a85837;
	/* configuwabwe tewms */
	weg_vaw = base_vaw | (ib_wtwm_adj << 25) |
		  (ib_sig_det_cwk_sew << 16) |
		  (ib_weg_pat_sew_offset << 8) |
		  (ib_caw_ena << 3);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_IB_CFG0,
				weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_ib_cfg1_ww(stwuct phy_device *phydev,
				   const u32 ib_tjtag,
				   const u32 ib_tsdet,
				   const u32 ib_scawy,
				   const u32 ib_fwc_offset,
				   const u32 ib_fiwt_offset)
{
	u32 ib_fiwt_vaw;
	u32 weg_vaw = 0;
	int wet;

	/* constant tewms */
	ib_fiwt_vaw = 0xe0;
	/* configuwabwe tewms */
	weg_vaw  = (ib_tjtag << 17) + (ib_tsdet << 12) + (ib_scawy << 8) +
		   ib_fiwt_vaw + (ib_fiwt_offset << 4) + (ib_fwc_offset << 0);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_IB_CFG1,
				weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_ib_cfg2_ww(stwuct phy_device *phydev,
				   const u32 ib_tinfv,
				   const u32 ib_tcawv,
				   const u32 ib_uweg)
{
	u32 ib_cfg2_vaw;
	u32 base_vaw;
	int wet;

	/* constant tewms */
	base_vaw = 0x0f878010;
	/* configuwabwe tewms */
	ib_cfg2_vaw = base_vaw | ((ib_tinfv) << 28) | ((ib_tcawv) << 5) |
		      (ib_uweg << 0);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_IB_CFG2,
				ib_cfg2_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_ib_cfg3_ww(stwuct phy_device *phydev,
				   const u32 ib_ini_hp,
				   const u32 ib_ini_mid,
				   const u32 ib_ini_wp,
				   const u32 ib_ini_offset)
{
	u32 weg_vaw;
	int wet;

	weg_vaw  = (ib_ini_hp << 24) + (ib_ini_mid << 16) +
		   (ib_ini_wp << 8) + (ib_ini_offset << 0);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_IB_CFG3,
				weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_ib_cfg4_ww(stwuct phy_device *phydev,
				   const u32 ib_max_hp,
				   const u32 ib_max_mid,
				   const u32 ib_max_wp,
				   const u32 ib_max_offset)
{
	u32 weg_vaw;
	int wet;

	weg_vaw  = (ib_max_hp << 24) + (ib_max_mid << 16) +
		   (ib_max_wp << 8) + (ib_max_offset << 0);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_IB_CFG4,
				weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_misc_cfg_ww(stwuct phy_device *phydev,
				    const u32 wane_wst)
{
	int wet;

	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_MISC_CFG,
				wane_wst);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_gp_cfg_ww(stwuct phy_device *phydev, const u32 gp_cfg_vaw)
{
	int wet;

	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_GP_CFG,
				gp_cfg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_dft_cfg2_ww(stwuct phy_device *phydev,
				    const u32 wx_ji_ampw,
				    const u32 wx_step_fweq,
				    const u32 wx_ji_ena,
				    const u32 wx_wavefowm_sew,
				    const u32 wx_fweqoff_diw,
				    const u32 wx_fweqoff_ena)
{
	u32 weg_vaw;
	int wet;

	/* configuwabwe tewms */
	weg_vaw = (wx_ji_ampw << 8) | (wx_step_fweq << 4) |
		  (wx_ji_ena << 3) | (wx_wavefowm_sew << 2) |
		  (wx_fweqoff_diw << 1) | wx_fweqoff_ena;
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_IB_DFT_CFG2,
				weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

static int vsc85xx_sd6g_dft_cfg0_ww(stwuct phy_device *phydev,
				    const u32 pwbs_sew,
				    const u32 test_mode,
				    const u32 wx_dft_ena)
{
	u32 weg_vaw;
	int wet;

	/* configuwabwe tewms */
	weg_vaw = (pwbs_sew << 20) | (test_mode << 16) | (wx_dft_ena << 2);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_DFT_CFG0,
				weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

/* Access WCPWW Cfg_0 */
static int vsc85xx_pww5g_cfg0_ww(stwuct phy_device *phydev,
				 const u32 sewbgv820)
{
	u32 base_vaw;
	u32 weg_vaw;
	int wet;

	/* constant tewms */
	base_vaw = 0x7036f145;
	/* configuwabwe tewms */
	weg_vaw = base_vaw | (sewbgv820 << 23);
	wet = vsc85xx_csw_wwite(phydev, MACWO_CTWW,
				PHY_S6G_PWW5G_CFG0, weg_vaw);
	if (wet)
		dev_eww(&phydev->mdio.dev, "%s: wwite ewwow\n", __func__);
	wetuwn wet;
}

int vsc85xx_sd6g_config_v2(stwuct phy_device *phydev)
{
	u32 ib_sig_det_cwk_sew_caw = 0;
	u32 ib_sig_det_cwk_sew_mm  = 7;
	u32 pww_fsm_ctww_data = 60;
	unsigned wong deadwine;
	u32 des_bw_ana_vaw = 3;
	u32 ib_tsdet_caw = 16;
	u32 ib_tsdet_mm  = 5;
	u32 ib_wtwm_adj;
	u32 if_mode = 1;
	u32 gp_itew = 5;
	u32 vaw32 = 0;
	u32 qwate = 1;
	u32 itew;
	int vaw = 0;
	int wet;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	/* Detune/Unwock WCPWW */
	wet = pww5g_detune(phydev);
	if (wet)
		wetuwn wet;

	/* 0. Weset WCPWW */
	wet = vsc85xx_sd6g_pww_cfg_ww(phydev, 3, pww_fsm_ctww_data, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_common_cfg_ww(phydev, 0, 0, 0, qwate, if_mode, 0);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_des_cfg_ww(phydev, 6, 2, 5, des_bw_ana_vaw, 0);
	if (wet)
		wetuwn wet;

	/* 1. Configuwe sd6g fow SGMII pwiow to sd6g_IB_CAW */
	ib_wtwm_adj = 13;
	wet = vsc85xx_sd6g_ib_cfg0_ww(phydev, ib_wtwm_adj, ib_sig_det_cwk_sew_mm, 0, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg1_ww(phydev, 8, ib_tsdet_mm, 15, 0, 1);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg2_ww(phydev, 3, 13, 5);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg3_ww(phydev,  0, 31, 1, 31);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg4_ww(phydev, 63, 63, 2, 63);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_common_cfg_ww(phydev, 1, 1, 0, qwate, if_mode, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_misc_cfg_ww(phydev, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 2. Stawt wcpww_fsm */
	wet = vsc85xx_sd6g_pww_cfg_ww(phydev, 3, pww_fsm_ctww_data, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		usweep_wange(500, 1000);
		wet = phy_update_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
		if (wet)
			wetuwn wet;
		vaw32 = vsc85xx_csw_wead(phydev, MACWO_CTWW,
					 PHY_S6G_PWW_STATUS);
		/* wait fow bit 12 to cweaw */
	} whiwe (time_befowe(jiffies, deadwine) && (vaw32 & BIT(12)));

	if (vaw32 & BIT(12))
		wetuwn -ETIMEDOUT;

	/* 4. Wewease digitaw weset and disabwe twansmittew */
	wet = vsc85xx_sd6g_misc_cfg_ww(phydev, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_common_cfg_ww(phydev, 1, 1, 0, qwate, if_mode, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 5. Appwy a fwequency offset on WX-side (using intewnaw FoJi wogic) */
	wet = vsc85xx_sd6g_gp_cfg_ww(phydev, 768);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_dft_cfg2_ww(phydev, 0, 2, 0, 0, 0, 1);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_dft_cfg0_ww(phydev, 0, 0, 1);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_des_cfg_ww(phydev, 6, 2, 5, des_bw_ana_vaw, 2);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 6. Pwepawe wequiwed settings fow IBCAW */
	wet = vsc85xx_sd6g_ib_cfg1_ww(phydev, 8, ib_tsdet_caw, 15, 1, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg0_ww(phydev, ib_wtwm_adj, ib_sig_det_cwk_sew_caw, 0, 0);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 7. Stawt IB_CAW */
	wet = vsc85xx_sd6g_ib_cfg0_ww(phydev, ib_wtwm_adj,
				      ib_sig_det_cwk_sew_caw, 0, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;
	/* 11 cycwes (fow VipewA) ow 5 cycwes (fow VipewB & Ewise) w/ SW cwock */
	fow (itew = 0; itew < gp_itew; itew++) {
		/* set gp(0) */
		wet = vsc85xx_sd6g_gp_cfg_ww(phydev, 769);
		if (wet)
			wetuwn wet;
		wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
		if (wet)
			wetuwn wet;
		/* cweaw gp(0) */
		wet = vsc85xx_sd6g_gp_cfg_ww(phydev, 768);
		if (wet)
			wetuwn wet;
		wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
		if (wet)
			wetuwn wet;
	}

	wet = vsc85xx_sd6g_ib_cfg1_ww(phydev, 8, ib_tsdet_caw, 15, 1, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg1_ww(phydev, 8, ib_tsdet_caw, 15, 0, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 8. Wait fow IB caw to compwete */
	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		usweep_wange(500, 1000);
		wet = phy_update_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
		if (wet)
			wetuwn wet;
		vaw32 = vsc85xx_csw_wead(phydev, MACWO_CTWW,
					 PHY_S6G_IB_STATUS0);
		/* wait fow bit 8 to set */
	} whiwe (time_befowe(jiffies, deadwine) && (~vaw32 & BIT(8)));

	if (~vaw32 & BIT(8))
		wetuwn -ETIMEDOUT;

	/* 9. Westowe cfg vawues fow mission mode */
	wet = vsc85xx_sd6g_ib_cfg0_ww(phydev, ib_wtwm_adj, ib_sig_det_cwk_sew_mm, 0, 1);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg1_ww(phydev, 8, ib_tsdet_mm, 15, 0, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 10. We-enabwe twansmittew */
	wet = vsc85xx_sd6g_common_cfg_ww(phydev, 1, 1, 0, qwate, if_mode, 0);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 11. Disabwe fwequency offset genewation (using intewnaw FoJi wogic) */
	wet = vsc85xx_sd6g_dft_cfg2_ww(phydev, 0, 0, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_dft_cfg0_ww(phydev, 0, 0, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_des_cfg_ww(phydev, 6, 2, 5, des_bw_ana_vaw, 0);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* Tune/We-wock WCPWW */
	wet = pww5g_tune(phydev);
	if (wet)
		wetuwn wet;

	/* 12. Configuwe fow Finaw Configuwation and Settings */
	/* a. Weset WCPWW */
	wet = vsc85xx_sd6g_pww_cfg_ww(phydev, 3, pww_fsm_ctww_data, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_common_cfg_ww(phydev, 0, 1, 0, qwate, if_mode, 0);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* b. Configuwe sd6g fow desiwed opewating mode */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_GPIO);
	wet = phy_base_wead(phydev, MSCC_PHY_MAC_CFG_FASTWINK);
	if ((wet & MAC_CFG_MASK) == MAC_CFG_QSGMII) {
		/* QSGMII */
		pww_fsm_ctww_data = 120;
		qwate   = 0;
		if_mode = 3;
		des_bw_ana_vaw = 5;
		vaw = PWOC_CMD_MCB_ACCESS_MAC_CONF | PWOC_CMD_WST_CONF_POWT |
			PWOC_CMD_WEAD_MOD_WWITE_POWT | PWOC_CMD_QSGMII_MAC;

		wet = vsc8584_cmd(phydev, vaw);
		if (wet) {
			dev_eww(&phydev->mdio.dev, "%s: QSGMII ewwow: %d\n",
				__func__, wet);
			wetuwn wet;
		}

		phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);
	} ewse if ((wet & MAC_CFG_MASK) == MAC_CFG_SGMII) {
		/* SGMII */
		pww_fsm_ctww_data = 60;
		qwate   = 1;
		if_mode = 1;
		des_bw_ana_vaw = 3;

		vaw = PWOC_CMD_MCB_ACCESS_MAC_CONF | PWOC_CMD_WST_CONF_POWT |
			PWOC_CMD_WEAD_MOD_WWITE_POWT | PWOC_CMD_SGMII_MAC;

		wet = vsc8584_cmd(phydev, vaw);
		if (wet) {
			dev_eww(&phydev->mdio.dev, "%s: SGMII ewwow: %d\n",
				__func__, wet);
			wetuwn wet;
		}

		phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);
	} ewse {
		dev_eww(&phydev->mdio.dev, "%s: invawid mac_if: %x\n",
			__func__, wet);
	}

	wet = phy_update_mcb_s6g(phydev, PHY_S6G_WCPWW_CFG, 0);
	if (wet)
		wetuwn wet;
	wet = phy_update_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_pww5g_cfg0_ww(phydev, 4);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_S6G_WCPWW_CFG, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_des_cfg_ww(phydev, 6, 2, 5, des_bw_ana_vaw, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg0_ww(phydev, ib_wtwm_adj, ib_sig_det_cwk_sew_mm, 0, 1);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg1_ww(phydev, 8, ib_tsdet_mm, 15, 0, 1);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_common_cfg_ww(phydev, 1, 1, 0, qwate, if_mode, 0);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg2_ww(phydev, 3, 13, 5);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg3_ww(phydev,  0, 31, 1, 31);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_ib_cfg4_ww(phydev, 63, 63, 2, 63);
	if (wet)
		wetuwn wet;
	wet = vsc85xx_sd6g_misc_cfg_ww(phydev, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 13. Stawt wcpww_fsm */
	wet = vsc85xx_sd6g_pww_cfg_ww(phydev, 3, pww_fsm_ctww_data, 1);
	if (wet)
		wetuwn wet;
	wet = phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
	if (wet)
		wetuwn wet;

	/* 14. Wait fow PWW caw to compwete */
	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		usweep_wange(500, 1000);
		wet = phy_update_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
		if (wet)
			wetuwn wet;
		vaw32 = vsc85xx_csw_wead(phydev, MACWO_CTWW,
					 PHY_S6G_PWW_STATUS);
		/* wait fow bit 12 to cweaw */
	} whiwe (time_befowe(jiffies, deadwine) && (vaw32 & BIT(12)));

	if (vaw32 & BIT(12))
		wetuwn -ETIMEDOUT;

	/* wewease wane weset */
	wet = vsc85xx_sd6g_misc_cfg_ww(phydev, 0);
	if (wet)
		wetuwn wet;

	wetuwn phy_commit_mcb_s6g(phydev, PHY_MCB_S6G_CFG, 0);
}
