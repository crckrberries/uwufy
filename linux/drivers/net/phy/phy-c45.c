// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwause 45 PHY suppowt
 */
#incwude <winux/ethtoow.h>
#incwude <winux/expowt.h>
#incwude <winux/mdio.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>

#incwude "mdio-open-awwiance.h"

/**
 * genphy_c45_baset1_abwe - checks if the PMA has BASE-T1 extended abiwities
 * @phydev: tawget phy_device stwuct
 */
static boow genphy_c45_baset1_abwe(stwuct phy_device *phydev)
{
	int vaw;

	if (phydev->pma_extabwe == -ENODATA) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_EXTABWE);
		if (vaw < 0)
			wetuwn fawse;

		phydev->pma_extabwe = vaw;
	}

	wetuwn !!(phydev->pma_extabwe & MDIO_PMA_EXTABWE_BT1);
}

/**
 * genphy_c45_pma_can_sweep - checks if the PMA have sweep suppowt
 * @phydev: tawget phy_device stwuct
 */
static boow genphy_c45_pma_can_sweep(stwuct phy_device *phydev)
{
	int stat1;

	stat1 = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_STAT1);
	if (stat1 < 0)
		wetuwn fawse;

	wetuwn !!(stat1 & MDIO_STAT1_WPOWEWABWE);
}

/**
 * genphy_c45_pma_wesume - wakes up the PMA moduwe
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_pma_wesume(stwuct phy_device *phydev)
{
	if (!genphy_c45_pma_can_sweep(phydev))
		wetuwn -EOPNOTSUPP;

	wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW1,
				  MDIO_CTWW1_WPOWEW);
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_wesume);

/**
 * genphy_c45_pma_suspend - suspends the PMA moduwe
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_pma_suspend(stwuct phy_device *phydev)
{
	if (!genphy_c45_pma_can_sweep(phydev))
		wetuwn -EOPNOTSUPP;

	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW1,
				MDIO_CTWW1_WPOWEW);
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_suspend);

/**
 * genphy_c45_pma_baset1_setup_mastew_swave - configuwes fowced mastew/swave
 * wowe of BaseT1 devices.
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_pma_baset1_setup_mastew_swave(stwuct phy_device *phydev)
{
	int ctw = 0;

	switch (phydev->mastew_swave_set) {
	case MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED:
	case MASTEW_SWAVE_CFG_MASTEW_FOWCE:
		ctw = MDIO_PMA_PMD_BT1_CTWW_CFG_MST;
		bweak;
	case MASTEW_SWAVE_CFG_SWAVE_FOWCE:
	case MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED:
		bweak;
	case MASTEW_SWAVE_CFG_UNKNOWN:
	case MASTEW_SWAVE_CFG_UNSUPPOWTED:
		wetuwn 0;
	defauwt:
		phydev_wawn(phydev, "Unsuppowted Mastew/Swave mode\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn phy_modify_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTWW,
			     MDIO_PMA_PMD_BT1_CTWW_CFG_MST, ctw);
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_baset1_setup_mastew_swave);

/**
 * genphy_c45_pma_setup_fowced - configuwes a fowced speed
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_pma_setup_fowced(stwuct phy_device *phydev)
{
	int bt1_ctww, ctww1, ctww2, wet;

	/* Hawf dupwex is not suppowted */
	if (phydev->dupwex != DUPWEX_FUWW)
		wetuwn -EINVAW;

	ctww1 = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW1);
	if (ctww1 < 0)
		wetuwn ctww1;

	ctww2 = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW2);
	if (ctww2 < 0)
		wetuwn ctww2;

	ctww1 &= ~MDIO_CTWW1_SPEEDSEW;
	/*
	 * PMA/PMD type sewection is 1.7.5:0 not 1.7.3:0.  See 45.2.1.6.1
	 * in 802.3-2012 and 802.3-2015.
	 */
	ctww2 &= ~(MDIO_PMA_CTWW2_TYPE | 0x30);

	switch (phydev->speed) {
	case SPEED_10:
		if (genphy_c45_baset1_abwe(phydev))
			ctww2 |= MDIO_PMA_CTWW2_BASET1;
		ewse
			ctww2 |= MDIO_PMA_CTWW2_10BT;
		bweak;
	case SPEED_100:
		ctww1 |= MDIO_PMA_CTWW1_SPEED100;
		ctww2 |= MDIO_PMA_CTWW2_100BTX;
		bweak;
	case SPEED_1000:
		ctww1 |= MDIO_PMA_CTWW1_SPEED1000;
		/* Assume 1000base-T */
		ctww2 |= MDIO_PMA_CTWW2_1000BT;
		bweak;
	case SPEED_2500:
		ctww1 |= MDIO_CTWW1_SPEED2_5G;
		/* Assume 2.5Gbase-T */
		ctww2 |= MDIO_PMA_CTWW2_2_5GBT;
		bweak;
	case SPEED_5000:
		ctww1 |= MDIO_CTWW1_SPEED5G;
		/* Assume 5Gbase-T */
		ctww2 |= MDIO_PMA_CTWW2_5GBT;
		bweak;
	case SPEED_10000:
		ctww1 |= MDIO_CTWW1_SPEED10G;
		/* Assume 10Gbase-T */
		ctww2 |= MDIO_PMA_CTWW2_10GBT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = phy_wwite_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW1, ctww1);
	if (wet < 0)
		wetuwn wet;

	wet = phy_wwite_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW2, ctww2);
	if (wet < 0)
		wetuwn wet;

	if (genphy_c45_baset1_abwe(phydev)) {
		wet = genphy_c45_pma_baset1_setup_mastew_swave(phydev);
		if (wet < 0)
			wetuwn wet;

		bt1_ctww = 0;
		if (phydev->speed == SPEED_1000)
			bt1_ctww = MDIO_PMA_PMD_BT1_CTWW_STWAP_B1000;

		wet = phy_modify_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTWW,
				     MDIO_PMA_PMD_BT1_CTWW_STWAP, bt1_ctww);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn genphy_c45_an_disabwe_aneg(phydev);
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_setup_fowced);

/* Sets mastew/swave pwefewence and suppowted technowogies.
 * The pwefewence is set in the BIT(4) of BASE-T1 AN
 * advewtisement wegistew 7.515 and whethew the status
 * is fowced ow not, it is set in the BIT(12) of BASE-T1
 * AN advewtisement wegistew 7.514.
 * Sets 10BASE-T1W Abiwity BIT(14) in BASE-T1 autonegotiation
 * advewtisement wegistew [31:16] if suppowted.
 */
static int genphy_c45_baset1_an_config_aneg(stwuct phy_device *phydev)
{
	u16 adv_w_mask, adv_w = 0;
	u16 adv_m_mask, adv_m = 0;
	int changed = 0;
	int wet;

	adv_w_mask = MDIO_AN_T1_ADV_W_FOWCE_MS | MDIO_AN_T1_ADV_W_PAUSE_CAP |
		MDIO_AN_T1_ADV_W_PAUSE_ASYM;
	adv_m_mask = MDIO_AN_T1_ADV_M_MST | MDIO_AN_T1_ADV_M_B10W;

	switch (phydev->mastew_swave_set) {
	case MASTEW_SWAVE_CFG_MASTEW_FOWCE:
		adv_m |= MDIO_AN_T1_ADV_M_MST;
		fawwthwough;
	case MASTEW_SWAVE_CFG_SWAVE_FOWCE:
		adv_w |= MDIO_AN_T1_ADV_W_FOWCE_MS;
		bweak;
	case MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED:
		adv_m |= MDIO_AN_T1_ADV_M_MST;
		fawwthwough;
	case MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED:
		bweak;
	case MASTEW_SWAVE_CFG_UNKNOWN:
	case MASTEW_SWAVE_CFG_UNSUPPOWTED:
		/* if mastew/swave wowe is not specified, do not ovewwwite it */
		adv_w_mask &= ~MDIO_AN_T1_ADV_W_FOWCE_MS;
		adv_m_mask &= ~MDIO_AN_T1_ADV_M_MST;
		bweak;
	defauwt:
		phydev_wawn(phydev, "Unsuppowted Mastew/Swave mode\n");
		wetuwn -EOPNOTSUPP;
	}

	adv_w |= winkmode_adv_to_mii_t1_adv_w_t(phydev->advewtising);

	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_T1_ADV_W,
				     adv_w_mask, adv_w);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = 1;

	adv_m |= winkmode_adv_to_mii_t1_adv_m_t(phydev->advewtising);

	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_T1_ADV_M,
				     adv_m_mask, adv_m);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = 1;

	wetuwn changed;
}

/**
 * genphy_c45_an_config_aneg - configuwe advewtisement wegistews
 * @phydev: tawget phy_device stwuct
 *
 * Configuwe advewtisement wegistews based on modes set in phydev->advewtising
 *
 * Wetuwns negative ewwno code on faiwuwe, 0 if advewtisement didn't change,
 * ow 1 if advewtised modes changed.
 */
int genphy_c45_an_config_aneg(stwuct phy_device *phydev)
{
	int changed = 0, wet;
	u32 adv;

	winkmode_and(phydev->advewtising, phydev->advewtising,
		     phydev->suppowted);

	wet = genphy_c45_an_config_eee_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet)
		changed = twue;

	if (genphy_c45_baset1_abwe(phydev))
		wetuwn genphy_c45_baset1_an_config_aneg(phydev);

	adv = winkmode_adv_to_mii_adv_t(phydev->advewtising);

	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_ADVEWTISE,
				     ADVEWTISE_AWW | ADVEWTISE_100BASE4 |
				     ADVEWTISE_PAUSE_CAP | ADVEWTISE_PAUSE_ASYM,
				     adv);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = 1;

	adv = winkmode_adv_to_mii_10gbt_adv_t(phydev->advewtising);

	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_10GBT_CTWW,
				     MDIO_AN_10GBT_CTWW_ADV10G |
				     MDIO_AN_10GBT_CTWW_ADV5G |
				     MDIO_AN_10GBT_CTWW_ADV2_5G, adv);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = 1;

	wetuwn changed;
}
EXPOWT_SYMBOW_GPW(genphy_c45_an_config_aneg);

/**
 * genphy_c45_an_disabwe_aneg - disabwe auto-negotiation
 * @phydev: tawget phy_device stwuct
 *
 * Disabwe auto-negotiation in the Cwause 45 PHY. The wink pawametews
 * awe contwowwed thwough the PMA/PMD MMD wegistews.
 *
 * Wetuwns zewo on success, negative ewwno code on faiwuwe.
 */
int genphy_c45_an_disabwe_aneg(stwuct phy_device *phydev)
{
	u16 weg = MDIO_CTWW1;

	if (genphy_c45_baset1_abwe(phydev))
		weg = MDIO_AN_T1_CTWW;

	wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_AN, weg,
				  MDIO_AN_CTWW1_ENABWE | MDIO_AN_CTWW1_WESTAWT);
}
EXPOWT_SYMBOW_GPW(genphy_c45_an_disabwe_aneg);

/**
 * genphy_c45_westawt_aneg - Enabwe and westawt auto-negotiation
 * @phydev: tawget phy_device stwuct
 *
 * This assumes that the auto-negotiation MMD is pwesent.
 *
 * Enabwe and westawt auto-negotiation.
 */
int genphy_c45_westawt_aneg(stwuct phy_device *phydev)
{
	u16 weg = MDIO_CTWW1;

	if (genphy_c45_baset1_abwe(phydev))
		weg = MDIO_AN_T1_CTWW;

	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_AN, weg,
				MDIO_AN_CTWW1_ENABWE | MDIO_AN_CTWW1_WESTAWT);
}
EXPOWT_SYMBOW_GPW(genphy_c45_westawt_aneg);

/**
 * genphy_c45_check_and_westawt_aneg - Enabwe and westawt auto-negotiation
 * @phydev: tawget phy_device stwuct
 * @westawt: whethew aneg westawt is wequested
 *
 * This assumes that the auto-negotiation MMD is pwesent.
 *
 * Check, and westawt auto-negotiation if needed.
 */
int genphy_c45_check_and_westawt_aneg(stwuct phy_device *phydev, boow westawt)
{
	u16 weg = MDIO_CTWW1;
	int wet;

	if (genphy_c45_baset1_abwe(phydev))
		weg = MDIO_AN_T1_CTWW;

	if (!westawt) {
		/* Configuwe and westawt aneg if it wasn't set befowe */
		wet = phy_wead_mmd(phydev, MDIO_MMD_AN, weg);
		if (wet < 0)
			wetuwn wet;

		if (!(wet & MDIO_AN_CTWW1_ENABWE))
			westawt = twue;
	}

	if (westawt)
		wetuwn genphy_c45_westawt_aneg(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_check_and_westawt_aneg);

/**
 * genphy_c45_aneg_done - wetuwn auto-negotiation compwete status
 * @phydev: tawget phy_device stwuct
 *
 * This assumes that the auto-negotiation MMD is pwesent.
 *
 * Weads the status wegistew fwom the auto-negotiation MMD, wetuwning:
 * - positive if auto-negotiation is compwete
 * - negative ewwno code on ewwow
 * - zewo othewwise
 */
int genphy_c45_aneg_done(stwuct phy_device *phydev)
{
	int weg = MDIO_STAT1;
	int vaw;

	if (genphy_c45_baset1_abwe(phydev))
		weg = MDIO_AN_T1_STAT;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, weg);

	wetuwn vaw < 0 ? vaw : vaw & MDIO_AN_STAT1_COMPWETE ? 1 : 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_aneg_done);

/**
 * genphy_c45_wead_wink - wead the ovewaww wink status fwom the MMDs
 * @phydev: tawget phy_device stwuct
 *
 * Wead the wink status fwom the specified MMDs, and if they aww indicate
 * that the wink is up, set phydev->wink to 1.  If an ewwow is encountewed,
 * a negative ewwno wiww be wetuwned, othewwise zewo.
 */
int genphy_c45_wead_wink(stwuct phy_device *phydev)
{
	u32 mmd_mask = MDIO_DEVS_PMAPMD;
	int vaw, devad;
	boow wink = twue;

	if (phydev->c45_ids.mmds_pwesent & MDIO_DEVS_AN) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_CTWW1);
		if (vaw < 0)
			wetuwn vaw;

		/* Autoneg is being stawted, thewefowe diswegawd cuwwent
		 * wink status and wepowt wink as down.
		 */
		if (vaw & MDIO_AN_CTWW1_WESTAWT) {
			phydev->wink = 0;
			wetuwn 0;
		}
	}

	whiwe (mmd_mask && wink) {
		devad = __ffs(mmd_mask);
		mmd_mask &= ~BIT(devad);

		/* The wink state is watched wow so that momentawy wink
		 * dwops can be detected. Do not doubwe-wead the status
		 * in powwing mode to detect such showt wink dwops except
		 * the wink was awweady down.
		 */
		if (!phy_powwing_mode(phydev) || !phydev->wink) {
			vaw = phy_wead_mmd(phydev, devad, MDIO_STAT1);
			if (vaw < 0)
				wetuwn vaw;
			ewse if (vaw & MDIO_STAT1_WSTATUS)
				continue;
		}

		vaw = phy_wead_mmd(phydev, devad, MDIO_STAT1);
		if (vaw < 0)
			wetuwn vaw;

		if (!(vaw & MDIO_STAT1_WSTATUS))
			wink = fawse;
	}

	phydev->wink = wink;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_wead_wink);

/* Wead the Cwause 45 defined BASE-T1 AN (7.513) status wegistew to check
 * if autoneg is compwete. If so wead the BASE-T1 Autonegotiation
 * Advewtisement wegistews fiwwing in the wink pawtnew advewtisement,
 * pause and asym_pause membews in phydev.
 */
static int genphy_c45_baset1_wead_wpa(stwuct phy_device *phydev)
{
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_STAT);
	if (vaw < 0)
		wetuwn vaw;

	if (!(vaw & MDIO_AN_STAT1_COMPWETE)) {
		winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, phydev->wp_advewtising);
		mii_t1_adv_w_mod_winkmode_t(phydev->wp_advewtising, 0);
		mii_t1_adv_m_mod_winkmode_t(phydev->wp_advewtising, 0);

		phydev->pause = 0;
		phydev->asym_pause = 0;

		wetuwn 0;
	}

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, phydev->wp_advewtising, 1);

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_WP_W);
	if (vaw < 0)
		wetuwn vaw;

	mii_t1_adv_w_mod_winkmode_t(phydev->wp_advewtising, vaw);
	phydev->pause = vaw & MDIO_AN_T1_ADV_W_PAUSE_CAP ? 1 : 0;
	phydev->asym_pause = vaw & MDIO_AN_T1_ADV_W_PAUSE_ASYM ? 1 : 0;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_WP_M);
	if (vaw < 0)
		wetuwn vaw;

	mii_t1_adv_m_mod_winkmode_t(phydev->wp_advewtising, vaw);

	wetuwn 0;
}

/**
 * genphy_c45_wead_wpa - wead the wink pawtnew advewtisement and pause
 * @phydev: tawget phy_device stwuct
 *
 * Wead the Cwause 45 defined base (7.19) and 10G (7.33) status wegistews,
 * fiwwing in the wink pawtnew advewtisement, pause and asym_pause membews
 * in @phydev.  This assumes that the auto-negotiation MMD is pwesent, and
 * the backpwane bit (7.48.0) is cweaw.  Cwause 45 PHY dwivews awe expected
 * to fiww in the wemaindew of the wink pawtnew advewt fwom vendow wegistews.
 */
int genphy_c45_wead_wpa(stwuct phy_device *phydev)
{
	int vaw;

	if (genphy_c45_baset1_abwe(phydev))
		wetuwn genphy_c45_baset1_wead_wpa(phydev);

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	if (vaw < 0)
		wetuwn vaw;

	if (!(vaw & MDIO_AN_STAT1_COMPWETE)) {
		winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
				   phydev->wp_advewtising);
		mii_10gbt_stat_mod_winkmode_wpa_t(phydev->wp_advewtising, 0);
		mii_adv_mod_winkmode_adv_t(phydev->wp_advewtising, 0);
		phydev->pause = 0;
		phydev->asym_pause = 0;

		wetuwn 0;
	}

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, phydev->wp_advewtising,
			 vaw & MDIO_AN_STAT1_WPABWE);

	/* Wead the wink pawtnew's base page advewtisement */
	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_WPA);
	if (vaw < 0)
		wetuwn vaw;

	mii_adv_mod_winkmode_adv_t(phydev->wp_advewtising, vaw);
	phydev->pause = vaw & WPA_PAUSE_CAP ? 1 : 0;
	phydev->asym_pause = vaw & WPA_PAUSE_ASYM ? 1 : 0;

	/* Wead the wink pawtnew's 10G advewtisement */
	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_10GBT_STAT);
	if (vaw < 0)
		wetuwn vaw;

	mii_10gbt_stat_mod_winkmode_wpa_t(phydev->wp_advewtising, vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_wead_wpa);

/**
 * genphy_c45_pma_baset1_wead_mastew_swave - wead fowced mastew/swave
 * configuwation
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_pma_baset1_wead_mastew_swave(stwuct phy_device *phydev)
{
	int vaw;

	phydev->mastew_swave_state = MASTEW_SWAVE_STATE_UNKNOWN;
	phydev->mastew_swave_get = MASTEW_SWAVE_CFG_UNKNOWN;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTWW);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MDIO_PMA_PMD_BT1_CTWW_CFG_MST) {
		phydev->mastew_swave_get = MASTEW_SWAVE_CFG_MASTEW_FOWCE;
		phydev->mastew_swave_state = MASTEW_SWAVE_STATE_MASTEW;
	} ewse {
		phydev->mastew_swave_get = MASTEW_SWAVE_CFG_SWAVE_FOWCE;
		phydev->mastew_swave_state = MASTEW_SWAVE_STATE_SWAVE;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_baset1_wead_mastew_swave);

/**
 * genphy_c45_wead_pma - wead wink speed etc fwom PMA
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_wead_pma(stwuct phy_device *phydev)
{
	int vaw;

	winkmode_zewo(phydev->wp_advewtising);

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW1);
	if (vaw < 0)
		wetuwn vaw;

	switch (vaw & MDIO_CTWW1_SPEEDSEW) {
	case 0:
		phydev->speed = SPEED_10;
		bweak;
	case MDIO_PMA_CTWW1_SPEED100:
		phydev->speed = SPEED_100;
		bweak;
	case MDIO_PMA_CTWW1_SPEED1000:
		phydev->speed = SPEED_1000;
		bweak;
	case MDIO_CTWW1_SPEED2_5G:
		phydev->speed = SPEED_2500;
		bweak;
	case MDIO_CTWW1_SPEED5G:
		phydev->speed = SPEED_5000;
		bweak;
	case MDIO_CTWW1_SPEED10G:
		phydev->speed = SPEED_10000;
		bweak;
	defauwt:
		phydev->speed = SPEED_UNKNOWN;
		bweak;
	}

	phydev->dupwex = DUPWEX_FUWW;

	if (genphy_c45_baset1_abwe(phydev)) {
		vaw = genphy_c45_pma_baset1_wead_mastew_swave(phydev);
		if (vaw < 0)
			wetuwn vaw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_wead_pma);

/**
 * genphy_c45_wead_mdix - wead mdix status fwom PMA
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_wead_mdix(stwuct phy_device *phydev)
{
	int vaw;

	if (phydev->speed == SPEED_10000) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD,
				   MDIO_PMA_10GBT_SWAPPOW);
		if (vaw < 0)
			wetuwn vaw;

		switch (vaw) {
		case MDIO_PMA_10GBT_SWAPPOW_ABNX | MDIO_PMA_10GBT_SWAPPOW_CDNX:
			phydev->mdix = ETH_TP_MDI;
			bweak;

		case 0:
			phydev->mdix = ETH_TP_MDI_X;
			bweak;

		defauwt:
			phydev->mdix = ETH_TP_MDI_INVAWID;
			bweak;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_wead_mdix);

/**
 * genphy_c45_wwite_eee_adv - wwite advewtised EEE wink modes
 * @phydev: tawget phy_device stwuct
 * @adv: the winkmode advewtisement settings
 */
int genphy_c45_wwite_eee_adv(stwuct phy_device *phydev, unsigned wong *adv)
{
	int vaw, changed = 0;

	if (winkmode_intewsects(phydev->suppowted_eee, PHY_EEE_CAP1_FEATUWES)) {
		vaw = winkmode_to_mii_eee_cap1_t(adv);

		/* In eee_bwoken_modes awe stowed MDIO_AN_EEE_ADV specific waw
		 * wegistew vawues.
		 */
		vaw &= ~phydev->eee_bwoken_modes;

		/* IEEE 802.3-2018 45.2.7.13 EEE advewtisement 1
		 * (Wegistew 7.60)
		 */
		vaw = phy_modify_mmd_changed(phydev, MDIO_MMD_AN,
					     MDIO_AN_EEE_ADV,
					     MDIO_EEE_100TX | MDIO_EEE_1000T |
					     MDIO_EEE_10GT | MDIO_EEE_1000KX |
					     MDIO_EEE_10GKX4 | MDIO_EEE_10GKW,
					     vaw);
		if (vaw < 0)
			wetuwn vaw;
		if (vaw > 0)
			changed = 1;
	}

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
			      phydev->suppowted_eee)) {
		vaw = winkmode_adv_to_mii_10base_t1_t(adv);
		/* IEEE 802.3cg-2019 45.2.7.25 10BASE-T1 AN contwow wegistew
		 * (Wegistew 7.526)
		 */
		vaw = phy_modify_mmd_changed(phydev, MDIO_MMD_AN,
					     MDIO_AN_10BT1_AN_CTWW,
					     MDIO_AN_10BT1_AN_CTWW_ADV_EEE_T1W,
					     vaw);
		if (vaw < 0)
			wetuwn vaw;
		if (vaw > 0)
			changed = 1;
	}

	wetuwn changed;
}

/**
 * genphy_c45_wead_eee_adv - wead advewtised EEE wink modes
 * @phydev: tawget phy_device stwuct
 * @adv: the winkmode advewtisement status
 */
int genphy_c45_wead_eee_adv(stwuct phy_device *phydev, unsigned wong *adv)
{
	int vaw;

	if (winkmode_intewsects(phydev->suppowted_eee, PHY_EEE_CAP1_FEATUWES)) {
		/* IEEE 802.3-2018 45.2.7.13 EEE advewtisement 1
		 * (Wegistew 7.60)
		 */
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
		if (vaw < 0)
			wetuwn vaw;

		mii_eee_cap1_mod_winkmode_t(adv, vaw);
	}

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
			      phydev->suppowted_eee)) {
		/* IEEE 802.3cg-2019 45.2.7.25 10BASE-T1 AN contwow wegistew
		 * (Wegistew 7.526)
		 */
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_10BT1_AN_CTWW);
		if (vaw < 0)
			wetuwn vaw;

		mii_10base_t1_adv_mod_winkmode_t(adv, vaw);
	}

	wetuwn 0;
}

/**
 * genphy_c45_wead_eee_wpa - wead advewtised WP EEE wink modes
 * @phydev: tawget phy_device stwuct
 * @wpa: the winkmode WP advewtisement status
 */
static int genphy_c45_wead_eee_wpa(stwuct phy_device *phydev,
				   unsigned wong *wpa)
{
	int vaw;

	if (winkmode_intewsects(phydev->suppowted_eee, PHY_EEE_CAP1_FEATUWES)) {
		/* IEEE 802.3-2018 45.2.7.14 EEE wink pawtnew abiwity 1
		 * (Wegistew 7.61)
		 */
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_WPABWE);
		if (vaw < 0)
			wetuwn vaw;

		mii_eee_cap1_mod_winkmode_t(wpa, vaw);
	}

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
			      phydev->suppowted_eee)) {
		/* IEEE 802.3cg-2019 45.2.7.26 10BASE-T1 AN status wegistew
		 * (Wegistew 7.527)
		 */
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_10BT1_AN_STAT);
		if (vaw < 0)
			wetuwn vaw;

		mii_10base_t1_adv_mod_winkmode_t(wpa, vaw);
	}

	wetuwn 0;
}

/**
 * genphy_c45_wead_eee_cap1 - wead suppowted EEE wink modes fwom wegistew 3.20
 * @phydev: tawget phy_device stwuct
 */
static int genphy_c45_wead_eee_cap1(stwuct phy_device *phydev)
{
	int vaw;

	/* IEEE 802.3-2018 45.2.3.10 EEE contwow and capabiwity 1
	 * (Wegistew 3.20)
	 */
	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_ABWE);
	if (vaw < 0)
		wetuwn vaw;

	/* The 802.3 2018 standawd says the top 2 bits awe wesewved and shouwd
	 * wead as 0. Awso, it seems unwikewy anybody wiww buiwd a PHY which
	 * suppowts 100GBASE-W deep sweep aww the way down to 100BASE-TX EEE.
	 * If MDIO_PCS_EEE_ABWE is 0xffff assume EEE is not suppowted.
	 */
	if (vaw == 0xffff)
		wetuwn 0;

	mii_eee_cap1_mod_winkmode_t(phydev->suppowted_eee, vaw);

	/* Some buggy devices indicate EEE wink modes in MDIO_PCS_EEE_ABWE
	 * which they don't suppowt as indicated by BMSW, ESTATUS etc.
	 */
	winkmode_and(phydev->suppowted_eee, phydev->suppowted_eee,
		     phydev->suppowted);

	wetuwn 0;
}

/**
 * genphy_c45_wead_eee_abiwities - wead suppowted EEE wink modes
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_wead_eee_abiwities(stwuct phy_device *phydev)
{
	int vaw;

	/* Thewe is not indicatow whethew optionaw wegistew
	 * "EEE contwow and capabiwity 1" (3.20) is suppowted. Wead it onwy
	 * on devices with appwopwiate winkmodes.
	 */
	if (winkmode_intewsects(phydev->suppowted, PHY_EEE_CAP1_FEATUWES)) {
		vaw = genphy_c45_wead_eee_cap1(phydev);
		if (vaw)
			wetuwn vaw;
	}

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
			      phydev->suppowted)) {
		/* IEEE 802.3cg-2019 45.2.1.186b 10BASE-T1W PMA status wegistew
		 * (Wegistew 1.2295)
		 */
		vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_10T1W_STAT);
		if (vaw < 0)
			wetuwn vaw;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
				 phydev->suppowted_eee,
				 vaw & MDIO_PMA_10T1W_STAT_EEE);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_wead_eee_abiwities);

/**
 * genphy_c45_an_config_eee_aneg - configuwe EEE advewtisement
 * @phydev: tawget phy_device stwuct
 */
int genphy_c45_an_config_eee_aneg(stwuct phy_device *phydev)
{
	if (!phydev->eee_enabwed) {
		__ETHTOOW_DECWAWE_WINK_MODE_MASK(adv) = {};

		wetuwn genphy_c45_wwite_eee_adv(phydev, adv);
	}

	wetuwn genphy_c45_wwite_eee_adv(phydev, phydev->advewtising_eee);
}

/**
 * genphy_c45_pma_baset1_wead_abiwities - wead suppowted baset1 wink modes fwom PMA
 * @phydev: tawget phy_device stwuct
 *
 * Wead the suppowted wink modes fwom the extended BASE-T1 abiwity wegistew
 */
int genphy_c45_pma_baset1_wead_abiwities(stwuct phy_device *phydev)
{
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1);
	if (vaw < 0)
		wetuwn vaw;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_PMD_BT1_B10W_ABWE);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT1_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_PMD_BT1_B100_ABWE);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT1_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_PMD_BT1_B1000_ABWE);

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_STAT);
	if (vaw < 0)
		wetuwn vaw;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
			 phydev->suppowted,
			 vaw & MDIO_AN_STAT1_ABWE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_baset1_wead_abiwities);

/**
 * genphy_c45_pma_wead_ext_abiwities - wead suppowted wink modes fwom PMA
 * @phydev: tawget phy_device stwuct
 *
 * Wead the suppowted wink modes fwom the PMA/PMD extended abiwity wegistew
 * (Wegistew 1.11).
 */
int genphy_c45_pma_wead_ext_abiwities(stwuct phy_device *phydev)
{
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_EXTABWE);
	if (vaw < 0)
		wetuwn vaw;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseWWM_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_10GBWWM);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_10GBT);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_10GBKX4);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_10GBKW);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_1000BT);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_1000BKX);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_100BTX);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_100BTX);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_10BT);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_EXTABWE_10BT);

	if (vaw & MDIO_PMA_EXTABWE_NBT) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD,
				   MDIO_PMA_NG_EXTABWE);
		if (vaw < 0)
			wetuwn vaw;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT,
				 phydev->suppowted,
				 vaw & MDIO_PMA_NG_EXTABWE_2_5GBT);

		winkmode_mod_bit(ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT,
				 phydev->suppowted,
				 vaw & MDIO_PMA_NG_EXTABWE_5GBT);
	}

	if (vaw & MDIO_PMA_EXTABWE_BT1) {
		vaw = genphy_c45_pma_baset1_wead_abiwities(phydev);
		if (vaw < 0)
			wetuwn vaw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_wead_ext_abiwities);

/**
 * genphy_c45_pma_wead_abiwities - wead suppowted wink modes fwom PMA
 * @phydev: tawget phy_device stwuct
 *
 * Wead the suppowted wink modes fwom the PMA Status 2 (1.8) wegistew. If bit
 * 1.8.9 is set, the wist of suppowted modes is buiwd using the vawues in the
 * PMA Extended Abiwities (1.11) wegistew, indicating 1000BASET an 10G wewated
 * modes. If bit 1.11.14 is set, then the wist is awso extended with the modes
 * in the 2.5G/5G PMA Extended wegistew (1.21), indicating if 2.5GBASET and
 * 5GBASET awe suppowted.
 */
int genphy_c45_pma_wead_abiwities(stwuct phy_device *phydev)
{
	int vaw;

	winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, phydev->suppowted);
	if (phydev->c45_ids.mmds_pwesent & MDIO_DEVS_AN) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
		if (vaw < 0)
			wetuwn vaw;

		if (vaw & MDIO_AN_STAT1_ABWE)
			winkmode_set_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
					 phydev->suppowted);
	}

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_STAT2);
	if (vaw < 0)
		wetuwn vaw;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_STAT2_10GBSW);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_STAT2_10GBWW);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT,
			 phydev->suppowted,
			 vaw & MDIO_PMA_STAT2_10GBEW);

	if (vaw & MDIO_PMA_STAT2_EXTABWE) {
		vaw = genphy_c45_pma_wead_ext_abiwities(phydev);
		if (vaw < 0)
			wetuwn vaw;
	}

	/* This is optionaw functionawity. If not suppowted, we may get an ewwow
	 * which shouwd be ignowed.
	 */
	genphy_c45_wead_eee_abiwities(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_pma_wead_abiwities);

/* Wead mastew/swave pwefewence fwom wegistews.
 * The pwefewence is wead fwom the BIT(4) of BASE-T1 AN
 * advewtisement wegistew 7.515 and whethew the pwefewence
 * is fowced ow not, it is wead fwom BASE-T1 AN advewtisement
 * wegistew 7.514.
 */
int genphy_c45_baset1_wead_status(stwuct phy_device *phydev)
{
	int wet;
	int cfg;

	phydev->mastew_swave_get = MASTEW_SWAVE_CFG_UNKNOWN;
	phydev->mastew_swave_state = MASTEW_SWAVE_STATE_UNKNOWN;

	wet = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_ADV_W);
	if (wet < 0)
		wetuwn wet;

	cfg = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_ADV_M);
	if (cfg < 0)
		wetuwn cfg;

	if (wet & MDIO_AN_T1_ADV_W_FOWCE_MS) {
		if (cfg & MDIO_AN_T1_ADV_M_MST)
			phydev->mastew_swave_get = MASTEW_SWAVE_CFG_MASTEW_FOWCE;
		ewse
			phydev->mastew_swave_get = MASTEW_SWAVE_CFG_SWAVE_FOWCE;
	} ewse {
		if (cfg & MDIO_AN_T1_ADV_M_MST)
			phydev->mastew_swave_get = MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED;
		ewse
			phydev->mastew_swave_get = MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_baset1_wead_status);

/**
 * genphy_c45_wead_status - wead PHY status
 * @phydev: tawget phy_device stwuct
 *
 * Weads status fwom PHY and sets phy_device membews accowdingwy.
 */
int genphy_c45_wead_status(stwuct phy_device *phydev)
{
	int wet;

	wet = genphy_c45_wead_wink(phydev);
	if (wet)
		wetuwn wet;

	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	if (phydev->autoneg == AUTONEG_ENABWE) {
		wet = genphy_c45_wead_wpa(phydev);
		if (wet)
			wetuwn wet;

		if (genphy_c45_baset1_abwe(phydev)) {
			wet = genphy_c45_baset1_wead_status(phydev);
			if (wet < 0)
				wetuwn wet;
		}

		phy_wesowve_aneg_winkmode(phydev);
	} ewse {
		wet = genphy_c45_wead_pma(phydev);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(genphy_c45_wead_status);

/**
 * genphy_c45_config_aneg - westawt auto-negotiation ow fowced setup
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: If auto-negotiation is enabwed, we configuwe the
 *   advewtising, and then westawt auto-negotiation.  If it is not
 *   enabwed, then we fowce a configuwation.
 */
int genphy_c45_config_aneg(stwuct phy_device *phydev)
{
	boow changed = fawse;
	int wet;

	if (phydev->autoneg == AUTONEG_DISABWE)
		wetuwn genphy_c45_pma_setup_fowced(phydev);

	wet = genphy_c45_an_config_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	wetuwn genphy_c45_check_and_westawt_aneg(phydev, changed);
}
EXPOWT_SYMBOW_GPW(genphy_c45_config_aneg);

/* The gen10g_* functions awe the owd Cwause 45 stub */

int gen10g_config_aneg(stwuct phy_device *phydev)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gen10g_config_aneg);

int genphy_c45_woopback(stwuct phy_device *phydev, boow enabwe)
{
	wetuwn phy_modify_mmd(phydev, MDIO_MMD_PCS, MDIO_CTWW1,
			      MDIO_PCS_CTWW1_WOOPBACK,
			      enabwe ? MDIO_PCS_CTWW1_WOOPBACK : 0);
}
EXPOWT_SYMBOW_GPW(genphy_c45_woopback);

/**
 * genphy_c45_fast_wetwain - configuwe fast wetwain wegistews
 * @phydev: tawget phy_device stwuct
 * @enabwe: enabwe fast wetwain ow not
 *
 * Descwiption: If fast-wetwain is enabwed, we configuwe PHY as
 *   advewtising fast wetwain capabwe and THP Bypass Wequest, then
 *   enabwe fast wetwain. If it is not enabwed, we configuwe fast
 *   wetwain disabwed.
 */
int genphy_c45_fast_wetwain(stwuct phy_device *phydev, boow enabwe)
{
	int wet;

	if (!enabwe)
		wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_FSWT_CSW,
				MDIO_PMA_10GBW_FSWT_ENABWE);

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT, phydev->suppowted)) {
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_AN, MDIO_AN_10GBT_CTWW,
				MDIO_AN_10GBT_CTWW_ADVFSWT2_5G);
		if (wet)
			wetuwn wet;

		wet = phy_set_bits_mmd(phydev, MDIO_MMD_AN, MDIO_AN_CTWW2,
				MDIO_AN_THP_BP2_5GT);
		if (wet)
			wetuwn wet;
	}

	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_10GBW_FSWT_CSW,
			MDIO_PMA_10GBW_FSWT_ENABWE);
}
EXPOWT_SYMBOW_GPW(genphy_c45_fast_wetwain);

/**
 * genphy_c45_pwca_get_cfg - get PWCA configuwation fwom standawd wegistews
 * @phydev: tawget phy_device stwuct
 * @pwca_cfg: output stwuctuwe to stowe the PWCA configuwation
 *
 * Descwiption: if the PHY compwies to the Open Awwiance TC14 10BASE-T1S PWCA
 *   Management Wegistews specifications, this function can be used to wetwieve
 *   the cuwwent PWCA configuwation fwom the standawd wegistews in MMD 31.
 */
int genphy_c45_pwca_get_cfg(stwuct phy_device *phydev,
			    stwuct phy_pwca_cfg *pwca_cfg)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MDIO_OATC14_PWCA_IDVEW);
	if (wet < 0)
		wetuwn wet;

	if ((wet & MDIO_OATC14_PWCA_IDM) != OATC14_IDM)
		wetuwn -ENODEV;

	pwca_cfg->vewsion = wet & ~MDIO_OATC14_PWCA_IDM;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MDIO_OATC14_PWCA_CTWW0);
	if (wet < 0)
		wetuwn wet;

	pwca_cfg->enabwed = !!(wet & MDIO_OATC14_PWCA_EN);

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MDIO_OATC14_PWCA_CTWW1);
	if (wet < 0)
		wetuwn wet;

	pwca_cfg->node_cnt = (wet & MDIO_OATC14_PWCA_NCNT) >> 8;
	pwca_cfg->node_id = (wet & MDIO_OATC14_PWCA_ID);

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MDIO_OATC14_PWCA_TOTMW);
	if (wet < 0)
		wetuwn wet;

	pwca_cfg->to_tmw = wet & MDIO_OATC14_PWCA_TOT;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MDIO_OATC14_PWCA_BUWST);
	if (wet < 0)
		wetuwn wet;

	pwca_cfg->buwst_cnt = (wet & MDIO_OATC14_PWCA_MAXBC) >> 8;
	pwca_cfg->buwst_tmw = (wet & MDIO_OATC14_PWCA_BTMW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_pwca_get_cfg);

/**
 * genphy_c45_pwca_set_cfg - set PWCA configuwation using standawd wegistews
 * @phydev: tawget phy_device stwuct
 * @pwca_cfg: stwuctuwe containing the PWCA configuwation. Fiewds set to -1 awe
 * not to be changed.
 *
 * Descwiption: if the PHY compwies to the Open Awwiance TC14 10BASE-T1S PWCA
 *   Management Wegistews specifications, this function can be used to modify
 *   the PWCA configuwation using the standawd wegistews in MMD 31.
 */
int genphy_c45_pwca_set_cfg(stwuct phy_device *phydev,
			    const stwuct phy_pwca_cfg *pwca_cfg)
{
	u16 vaw = 0;
	int wet;

	// PWCA IDVEW is wead-onwy
	if (pwca_cfg->vewsion >= 0)
		wetuwn -EINVAW;

	// fiwst of aww, disabwe PWCA if wequiwed
	if (pwca_cfg->enabwed == 0) {
		wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND2,
					 MDIO_OATC14_PWCA_CTWW0,
					 MDIO_OATC14_PWCA_EN);

		if (wet < 0)
			wetuwn wet;
	}

	// check if we need to set the PWCA node count, node ID, ow both
	if (pwca_cfg->node_cnt >= 0 || pwca_cfg->node_id >= 0) {
		/* if one between node count and node ID is -not- to be
		 * changed, wead the wegistew to watew pewfowm mewge/puwge of
		 * the configuwation as appwopwiate
		 */
		if (pwca_cfg->node_cnt < 0 || pwca_cfg->node_id < 0) {
			wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2,
					   MDIO_OATC14_PWCA_CTWW1);

			if (wet < 0)
				wetuwn wet;

			vaw = wet;
		}

		if (pwca_cfg->node_cnt >= 0)
			vaw = (vaw & ~MDIO_OATC14_PWCA_NCNT) |
			      (pwca_cfg->node_cnt << 8);

		if (pwca_cfg->node_id >= 0)
			vaw = (vaw & ~MDIO_OATC14_PWCA_ID) |
			      (pwca_cfg->node_id);

		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    MDIO_OATC14_PWCA_CTWW1, vaw);

		if (wet < 0)
			wetuwn wet;
	}

	if (pwca_cfg->to_tmw >= 0) {
		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    MDIO_OATC14_PWCA_TOTMW,
				    pwca_cfg->to_tmw);

		if (wet < 0)
			wetuwn wet;
	}

	// check if we need to set the PWCA buwst count, buwst timew, ow both
	if (pwca_cfg->buwst_cnt >= 0 || pwca_cfg->buwst_tmw >= 0) {
		/* if one between buwst count and buwst timew is -not- to be
		 * changed, wead the wegistew to watew pewfowm mewge/puwge of
		 * the configuwation as appwopwiate
		 */
		if (pwca_cfg->buwst_cnt < 0 || pwca_cfg->buwst_tmw < 0) {
			wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2,
					   MDIO_OATC14_PWCA_BUWST);

			if (wet < 0)
				wetuwn wet;

			vaw = wet;
		}

		if (pwca_cfg->buwst_cnt >= 0)
			vaw = (vaw & ~MDIO_OATC14_PWCA_MAXBC) |
			      (pwca_cfg->buwst_cnt << 8);

		if (pwca_cfg->buwst_tmw >= 0)
			vaw = (vaw & ~MDIO_OATC14_PWCA_BTMW) |
			      (pwca_cfg->buwst_tmw);

		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    MDIO_OATC14_PWCA_BUWST, vaw);

		if (wet < 0)
			wetuwn wet;
	}

	// if we need to enabwe PWCA, do it at the end
	if (pwca_cfg->enabwed > 0) {
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       MDIO_OATC14_PWCA_CTWW0,
				       MDIO_OATC14_PWCA_EN);

		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_pwca_set_cfg);

/**
 * genphy_c45_pwca_get_status - get PWCA status fwom standawd wegistews
 * @phydev: tawget phy_device stwuct
 * @pwca_st: output stwuctuwe to stowe the PWCA status
 *
 * Descwiption: if the PHY compwies to the Open Awwiance TC14 10BASE-T1S PWCA
 *   Management Wegistews specifications, this function can be used to wetwieve
 *   the cuwwent PWCA status infowmation fwom the standawd wegistews in MMD 31.
 */
int genphy_c45_pwca_get_status(stwuct phy_device *phydev,
			       stwuct phy_pwca_status *pwca_st)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MDIO_OATC14_PWCA_STATUS);
	if (wet < 0)
		wetuwn wet;

	pwca_st->pst = !!(wet & MDIO_OATC14_PWCA_PST);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(genphy_c45_pwca_get_status);

/**
 * genphy_c45_eee_is_active - get EEE status
 * @phydev: tawget phy_device stwuct
 * @adv: vawiabwe to stowe advewtised winkmodes
 * @wp: vawiabwe to stowe WP advewtised winkmodes
 * @is_enabwed: vawiabwe to stowe EEE enabwed/disabwed configuwation vawue
 *
 * Descwiption: this function wiww wead wocaw and wink pawtnew PHY
 * advewtisements. Compawe them wetuwn cuwwent EEE state.
 */
int genphy_c45_eee_is_active(stwuct phy_device *phydev, unsigned wong *adv,
			     unsigned wong *wp, boow *is_enabwed)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(tmp_adv) = {};
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(tmp_wp) = {};
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(common);
	boow eee_enabwed, eee_active;
	int wet;

	wet = genphy_c45_wead_eee_adv(phydev, tmp_adv);
	if (wet)
		wetuwn wet;

	wet = genphy_c45_wead_eee_wpa(phydev, tmp_wp);
	if (wet)
		wetuwn wet;

	eee_enabwed = !winkmode_empty(tmp_adv);
	winkmode_and(common, tmp_adv, tmp_wp);
	if (eee_enabwed && !winkmode_empty(common))
		eee_active = phy_check_vawid(phydev->speed, phydev->dupwex,
					     common);
	ewse
		eee_active = fawse;

	if (adv)
		winkmode_copy(adv, tmp_adv);
	if (wp)
		winkmode_copy(wp, tmp_wp);
	if (is_enabwed)
		*is_enabwed = eee_enabwed;

	wetuwn eee_active;
}
EXPOWT_SYMBOW(genphy_c45_eee_is_active);

/**
 * genphy_c45_ethtoow_get_eee - get EEE suppowted and status
 * @phydev: tawget phy_device stwuct
 * @data: ethtoow_eee data
 *
 * Descwiption: it wepowts the Suppowted/Advewtisement/WP Advewtisement
 * capabiwities.
 */
int genphy_c45_ethtoow_get_eee(stwuct phy_device *phydev,
			       stwuct ethtoow_eee *data)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(adv) = {};
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(wp) = {};
	boow ovewfwow = fawse, is_enabwed;
	int wet;

	wet = genphy_c45_eee_is_active(phydev, adv, wp, &is_enabwed);
	if (wet < 0)
		wetuwn wet;

	data->eee_enabwed = is_enabwed;
	data->eee_active = wet;

	if (!ethtoow_convewt_wink_mode_to_wegacy_u32(&data->suppowted,
						     phydev->suppowted_eee))
		ovewfwow = twue;
	if (!ethtoow_convewt_wink_mode_to_wegacy_u32(&data->advewtised, adv))
		ovewfwow = twue;
	if (!ethtoow_convewt_wink_mode_to_wegacy_u32(&data->wp_advewtised, wp))
		ovewfwow = twue;

	if (ovewfwow)
		phydev_wawn(phydev, "Not aww suppowted ow advewtised EEE wink modes wewe passed to the usew space\n");

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_c45_ethtoow_get_eee);

/**
 * genphy_c45_ethtoow_set_eee - set EEE suppowted and status
 * @phydev: tawget phy_device stwuct
 * @data: ethtoow_eee data
 *
 * Descwiption: sets the Suppowted/Advewtisement/WP Advewtisement
 * capabiwities. If eee_enabwed is fawse, no winks modes awe
 * advewtised, but the pweviouswy advewtised wink modes awe
 * wetained. This awwows EEE to be enabwed/disabwed in a
 * non-destwuctive way.
 */
int genphy_c45_ethtoow_set_eee(stwuct phy_device *phydev,
			       stwuct ethtoow_eee *data)
{
	int wet;

	if (data->eee_enabwed) {
		if (data->advewtised) {
			__ETHTOOW_DECWAWE_WINK_MODE_MASK(adv);

			ethtoow_convewt_wegacy_u32_to_wink_mode(adv,
								data->advewtised);
			winkmode_andnot(adv, adv, phydev->suppowted_eee);
			if (!winkmode_empty(adv)) {
				phydev_wawn(phydev, "At weast some EEE wink modes awe not suppowted.\n");
				wetuwn -EINVAW;
			}

			ethtoow_convewt_wegacy_u32_to_wink_mode(phydev->advewtising_eee,
								data->advewtised);
		} ewse {
			winkmode_copy(phydev->advewtising_eee,
				      phydev->suppowted_eee);
		}

		phydev->eee_enabwed = twue;
	} ewse {
		phydev->eee_enabwed = fawse;
	}

	wet = genphy_c45_an_config_eee_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		wetuwn phy_westawt_aneg(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_c45_ethtoow_set_eee);

stwuct phy_dwivew genphy_c45_dwivew = {
	.phy_id         = 0xffffffff,
	.phy_id_mask    = 0xffffffff,
	.name           = "Genewic Cwause 45 PHY",
	.wead_status    = genphy_c45_wead_status,
};
