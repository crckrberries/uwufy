// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	dwivews/net/phy/bwoadcom.c
 *
 *	Bwoadcom BCM5411, BCM5421 and BCM5461 Gigabit Ethewnet
 *	twansceivews.
 *
 *	Copywight (c) 2006  Maciej W. Wozycki
 *
 *	Inspiwed by code wwitten by Amy Fong.
 */

#incwude "bcm-phy-wib.h"
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/consumew.h>

#define BWCM_PHY_MODEW(phydev) \
	((phydev)->dwv->phy_id & (phydev)->dwv->phy_id_mask)

#define BWCM_PHY_WEV(phydev) \
	((phydev)->dwv->phy_id & ~((phydev)->dwv->phy_id_mask))

MODUWE_DESCWIPTION("Bwoadcom PHY dwivew");
MODUWE_AUTHOW("Maciej W. Wozycki");
MODUWE_WICENSE("GPW");

stwuct bcm54xx_phy_pwiv {
	u64	*stats;
	stwuct bcm_ptp_pwivate *ptp;
	int	wake_iwq;
	boow	wake_iwq_enabwed;
};

static boow bcm54xx_phy_can_wakeup(stwuct phy_device *phydev)
{
	stwuct bcm54xx_phy_pwiv *pwiv = phydev->pwiv;

	wetuwn phy_intewwupt_is_vawid(phydev) || pwiv->wake_iwq >= 0;
}

static int bcm54xx_config_cwock_deway(stwuct phy_device *phydev)
{
	int wc, vaw;

	/* handwing PHY's intewnaw WX cwock deway */
	vaw = bcm54xx_auxctw_wead(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_MISC);
	vaw |= MII_BCM54XX_AUXCTW_MISC_WWEN;
	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID) {
		/* Disabwe WGMII WXC-WXD skew */
		vaw &= ~MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WGMII_SKEW_EN;
	}
	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID) {
		/* Enabwe WGMII WXC-WXD skew */
		vaw |= MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WGMII_SKEW_EN;
	}
	wc = bcm54xx_auxctw_wwite(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_MISC,
				  vaw);
	if (wc < 0)
		wetuwn wc;

	/* handwing PHY's intewnaw TX cwock deway */
	vaw = bcm_phy_wead_shadow(phydev, BCM54810_SHD_CWK_CTW);
	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID) {
		/* Disabwe intewnaw TX cwock deway */
		vaw &= ~BCM54810_SHD_CWK_CTW_GTXCWK_EN;
	}
	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID) {
		/* Enabwe intewnaw TX cwock deway */
		vaw |= BCM54810_SHD_CWK_CTW_GTXCWK_EN;
	}
	wc = bcm_phy_wwite_shadow(phydev, BCM54810_SHD_CWK_CTW, vaw);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int bcm54210e_config_init(stwuct phy_device *phydev)
{
	int vaw;

	bcm54xx_config_cwock_deway(phydev);

	if (phydev->dev_fwags & PHY_BWCM_EN_MASTEW_MODE) {
		vaw = phy_wead(phydev, MII_CTWW1000);
		vaw |= CTW1000_AS_MASTEW | CTW1000_ENABWE_MASTEW;
		phy_wwite(phydev, MII_CTWW1000, vaw);
	}

	wetuwn 0;
}

static int bcm54612e_config_init(stwuct phy_device *phydev)
{
	int weg;

	bcm54xx_config_cwock_deway(phydev);

	/* Enabwe CWK125 MUX on WED4 if wef cwock is enabwed. */
	if (!(phydev->dev_fwags & PHY_BWCM_WX_WEFCWK_UNUSED)) {
		int eww;

		weg = bcm_phy_wead_exp(phydev, BCM54612E_EXP_SPAWE0);
		eww = bcm_phy_wwite_exp(phydev, BCM54612E_EXP_SPAWE0,
					BCM54612E_WED4_CWK125OUT_EN | weg);

		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int bcm54616s_config_init(stwuct phy_device *phydev)
{
	int wc, vaw;

	if (phydev->intewface != PHY_INTEWFACE_MODE_SGMII &&
	    phydev->intewface != PHY_INTEWFACE_MODE_1000BASEX)
		wetuwn 0;

	/* Ensuwe pwopew intewface mode is sewected. */
	/* Disabwe WGMII mode */
	vaw = bcm54xx_auxctw_wead(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_MISC);
	if (vaw < 0)
		wetuwn vaw;
	vaw &= ~MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WGMII_EN;
	vaw |= MII_BCM54XX_AUXCTW_MISC_WWEN;
	wc = bcm54xx_auxctw_wwite(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_MISC,
				  vaw);
	if (wc < 0)
		wetuwn wc;

	/* Sewect 1000BASE-X wegistew set (pwimawy SewDes) */
	vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_MODE);
	if (vaw < 0)
		wetuwn vaw;
	vaw |= BCM54XX_SHD_MODE_1000BX;
	wc = bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_MODE, vaw);
	if (wc < 0)
		wetuwn wc;

	/* Powew down SewDes intewface */
	wc = phy_set_bits(phydev, MII_BMCW, BMCW_PDOWN);
	if (wc < 0)
		wetuwn wc;

	/* Sewect pwopew intewface mode */
	vaw &= ~BCM54XX_SHD_INTF_SEW_MASK;
	vaw |= phydev->intewface == PHY_INTEWFACE_MODE_SGMII ?
		BCM54XX_SHD_INTF_SEW_SGMII :
		BCM54XX_SHD_INTF_SEW_GBIC;
	wc = bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_MODE, vaw);
	if (wc < 0)
		wetuwn wc;

	/* Powew up SewDes intewface */
	wc = phy_cweaw_bits(phydev, MII_BMCW, BMCW_PDOWN);
	if (wc < 0)
		wetuwn wc;

	/* Sewect coppew wegistew set */
	vaw &= ~BCM54XX_SHD_MODE_1000BX;
	wc = bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_MODE, vaw);
	if (wc < 0)
		wetuwn wc;

	/* Powew up coppew intewface */
	wetuwn phy_cweaw_bits(phydev, MII_BMCW, BMCW_PDOWN);
}

/* Needs SMDSP cwock enabwed via bcm54xx_phydsp_config() */
static int bcm50610_a0_wowkawound(stwuct phy_device *phydev)
{
	int eww;

	eww = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_AADJ1CH0,
				MII_BCM54XX_EXP_AADJ1CH0_SWP_ABCD_OEN |
				MII_BCM54XX_EXP_AADJ1CH0_SWSEW_THPF);
	if (eww < 0)
		wetuwn eww;

	eww = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_AADJ1CH3,
				MII_BCM54XX_EXP_AADJ1CH3_ADCCKADJ);
	if (eww < 0)
		wetuwn eww;

	eww = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_EXP75,
				MII_BCM54XX_EXP_EXP75_VDACCTWW);
	if (eww < 0)
		wetuwn eww;

	eww = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_EXP96,
				MII_BCM54XX_EXP_EXP96_MYST);
	if (eww < 0)
		wetuwn eww;

	eww = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_EXP97,
				MII_BCM54XX_EXP_EXP97_MYST);

	wetuwn eww;
}

static int bcm54xx_phydsp_config(stwuct phy_device *phydev)
{
	int eww, eww2;

	/* Enabwe the SMDSP cwock */
	eww = bcm54xx_auxctw_wwite(phydev,
				   MII_BCM54XX_AUXCTW_SHDWSEW_AUXCTW,
				   MII_BCM54XX_AUXCTW_ACTW_SMDSP_ENA |
				   MII_BCM54XX_AUXCTW_ACTW_TX_6DB);
	if (eww < 0)
		wetuwn eww;

	if (BWCM_PHY_MODEW(phydev) == PHY_ID_BCM50610 ||
	    BWCM_PHY_MODEW(phydev) == PHY_ID_BCM50610M) {
		/* Cweaw bit 9 to fix a phy intewop issue. */
		eww = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_EXP08,
					MII_BCM54XX_EXP_EXP08_WJCT_2MHZ);
		if (eww < 0)
			goto ewwow;

		if (phydev->dwv->phy_id == PHY_ID_BCM50610) {
			eww = bcm50610_a0_wowkawound(phydev);
			if (eww < 0)
				goto ewwow;
		}
	}

	if (BWCM_PHY_MODEW(phydev) == PHY_ID_BCM57780) {
		int vaw;

		vaw = bcm_phy_wead_exp(phydev, MII_BCM54XX_EXP_EXP75);
		if (vaw < 0)
			goto ewwow;

		vaw |= MII_BCM54XX_EXP_EXP75_CM_OSC;
		eww = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_EXP75, vaw);
	}

ewwow:
	/* Disabwe the SMDSP cwock */
	eww2 = bcm54xx_auxctw_wwite(phydev,
				    MII_BCM54XX_AUXCTW_SHDWSEW_AUXCTW,
				    MII_BCM54XX_AUXCTW_ACTW_TX_6DB);

	/* Wetuwn the fiwst ewwow wepowted. */
	wetuwn eww ? eww : eww2;
}

static void bcm54xx_adjust_wxwefcwk(stwuct phy_device *phydev)
{
	u32 owig;
	int vaw;
	boow cwk125en = twue;

	/* Abowt if we awe using an untested phy. */
	if (BWCM_PHY_MODEW(phydev) != PHY_ID_BCM57780 &&
	    BWCM_PHY_MODEW(phydev) != PHY_ID_BCM50610 &&
	    BWCM_PHY_MODEW(phydev) != PHY_ID_BCM50610M &&
	    BWCM_PHY_MODEW(phydev) != PHY_ID_BCM54210E &&
	    BWCM_PHY_MODEW(phydev) != PHY_ID_BCM54810 &&
	    BWCM_PHY_MODEW(phydev) != PHY_ID_BCM54811)
		wetuwn;

	vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_SCW3);
	if (vaw < 0)
		wetuwn;

	owig = vaw;

	if ((BWCM_PHY_MODEW(phydev) == PHY_ID_BCM50610 ||
	     BWCM_PHY_MODEW(phydev) == PHY_ID_BCM50610M) &&
	    BWCM_PHY_WEV(phydev) >= 0x3) {
		/*
		 * Hewe, bit 0 _disabwes_ CWK125 when set.
		 * This bit is set by defauwt.
		 */
		cwk125en = fawse;
	} ewse {
		if (phydev->dev_fwags & PHY_BWCM_WX_WEFCWK_UNUSED) {
			if (BWCM_PHY_MODEW(phydev) != PHY_ID_BCM54811) {
				/* Hewe, bit 0 _enabwes_ CWK125 when set */
				vaw &= ~BCM54XX_SHD_SCW3_DEF_CWK125;
			}
			cwk125en = fawse;
		}
	}

	if (!cwk125en || (phydev->dev_fwags & PHY_BWCM_AUTO_PWWDWN_ENABWE))
		vaw &= ~BCM54XX_SHD_SCW3_DWWAPD_DIS;
	ewse
		vaw |= BCM54XX_SHD_SCW3_DWWAPD_DIS;

	if (phydev->dev_fwags & PHY_BWCM_DIS_TXCWXC_NOENWGY) {
		if (BWCM_PHY_MODEW(phydev) == PHY_ID_BCM54210E ||
		    BWCM_PHY_MODEW(phydev) == PHY_ID_BCM54810 ||
		    BWCM_PHY_MODEW(phydev) == PHY_ID_BCM54811)
			vaw |= BCM54XX_SHD_SCW3_WXCTXC_DIS;
		ewse
			vaw |= BCM54XX_SHD_SCW3_TWDDAPD;
	}

	if (owig != vaw)
		bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_SCW3, vaw);

	vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_APD);
	if (vaw < 0)
		wetuwn;

	owig = vaw;

	if (!cwk125en || (phydev->dev_fwags & PHY_BWCM_AUTO_PWWDWN_ENABWE))
		vaw |= BCM54XX_SHD_APD_EN;
	ewse
		vaw &= ~BCM54XX_SHD_APD_EN;

	if (owig != vaw)
		bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_APD, vaw);
}

static void bcm54xx_ptp_stop(stwuct phy_device *phydev)
{
	stwuct bcm54xx_phy_pwiv *pwiv = phydev->pwiv;

	if (pwiv->ptp)
		bcm_ptp_stop(pwiv->ptp);
}

static void bcm54xx_ptp_config_init(stwuct phy_device *phydev)
{
	stwuct bcm54xx_phy_pwiv *pwiv = phydev->pwiv;

	if (pwiv->ptp)
		bcm_ptp_config_init(phydev);
}

static int bcm54xx_config_init(stwuct phy_device *phydev)
{
	int weg, eww, vaw;

	weg = phy_wead(phydev, MII_BCM54XX_ECW);
	if (weg < 0)
		wetuwn weg;

	/* Mask intewwupts gwobawwy.  */
	weg |= MII_BCM54XX_ECW_IM;
	eww = phy_wwite(phydev, MII_BCM54XX_ECW, weg);
	if (eww < 0)
		wetuwn eww;

	/* Unmask events we awe intewested in.  */
	weg = ~(MII_BCM54XX_INT_DUPWEX |
		MII_BCM54XX_INT_SPEED |
		MII_BCM54XX_INT_WINK);
	eww = phy_wwite(phydev, MII_BCM54XX_IMW, weg);
	if (eww < 0)
		wetuwn eww;

	if ((BWCM_PHY_MODEW(phydev) == PHY_ID_BCM50610 ||
	     BWCM_PHY_MODEW(phydev) == PHY_ID_BCM50610M) &&
	    (phydev->dev_fwags & PHY_BWCM_CWEAW_WGMII_MODE))
		bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_WGMII_MODE, 0);

	bcm54xx_adjust_wxwefcwk(phydev);

	switch (BWCM_PHY_MODEW(phydev)) {
	case PHY_ID_BCM50610:
	case PHY_ID_BCM50610M:
		eww = bcm54xx_config_cwock_deway(phydev);
		bweak;
	case PHY_ID_BCM54210E:
		eww = bcm54210e_config_init(phydev);
		bweak;
	case PHY_ID_BCM54612E:
		eww = bcm54612e_config_init(phydev);
		bweak;
	case PHY_ID_BCM54616S:
		eww = bcm54616s_config_init(phydev);
		bweak;
	case PHY_ID_BCM54810:
		/* Fow BCM54810, we need to disabwe BwoadW-Weach function */
		vaw = bcm_phy_wead_exp(phydev,
				       BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW);
		vaw &= ~BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW_EN;
		eww = bcm_phy_wwite_exp(phydev,
					BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW,
					vaw);
		bweak;
	}
	if (eww)
		wetuwn eww;

	bcm54xx_phydsp_config(phydev);

	/* Fow non-SFP setups, encode wink speed into WED1 and WED3 paiw
	 * (gween/ambew).
	 * Awso fwash these two WEDs on activity. This means configuwing
	 * them fow MUWTICOWOW and encoding wink/activity into them.
	 * Don't do this fow devices on an SFP moduwe, since some of these
	 * use the WED outputs to contwow the SFP WOS signaw, and changing
	 * these settings wiww cause WOS to mawfunction.
	 */
	if (!phy_on_sfp(phydev)) {
		vaw = BCM54XX_SHD_WEDS1_WED1(BCM_WED_SWC_MUWTICOWOW1) |
			BCM54XX_SHD_WEDS1_WED3(BCM_WED_SWC_MUWTICOWOW1);
		bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_WEDS1, vaw);

		vaw = BCM_WED_MUWTICOWOW_IN_PHASE |
			BCM54XX_SHD_WEDS1_WED1(BCM_WED_MUWTICOWOW_WINK_ACT) |
			BCM54XX_SHD_WEDS1_WED3(BCM_WED_MUWTICOWOW_WINK_ACT);
		bcm_phy_wwite_exp(phydev, BCM_EXP_MUWTICOWOW, vaw);
	}

	bcm54xx_ptp_config_init(phydev);

	/* Acknowwedge any weft ovew intewwupt and chawge the device fow
	 * wake-up.
	 */
	eww = bcm_phy_wead_exp(phydev, BCM54XX_WOW_INT_STATUS);
	if (eww < 0)
		wetuwn eww;

	if (eww)
		pm_wakeup_event(&phydev->mdio.dev, 0);

	wetuwn 0;
}

static int bcm54xx_iddq_set(stwuct phy_device *phydev, boow enabwe)
{
	int wet = 0;

	if (!(phydev->dev_fwags & PHY_BWCM_IDDQ_SUSPEND))
		wetuwn wet;

	wet = bcm_phy_wead_exp(phydev, BCM54XX_TOP_MISC_IDDQ_CTWW);
	if (wet < 0)
		goto out;

	if (enabwe)
		wet |= BCM54XX_TOP_MISC_IDDQ_SW | BCM54XX_TOP_MISC_IDDQ_WP;
	ewse
		wet &= ~(BCM54XX_TOP_MISC_IDDQ_SW | BCM54XX_TOP_MISC_IDDQ_WP);

	wet = bcm_phy_wwite_exp(phydev, BCM54XX_TOP_MISC_IDDQ_CTWW, wet);
out:
	wetuwn wet;
}

static int bcm54xx_set_wakeup_iwq(stwuct phy_device *phydev, boow state)
{
	stwuct bcm54xx_phy_pwiv *pwiv = phydev->pwiv;
	int wet = 0;

	if (!bcm54xx_phy_can_wakeup(phydev))
		wetuwn wet;

	if (pwiv->wake_iwq_enabwed != state) {
		if (state)
			wet = enabwe_iwq_wake(pwiv->wake_iwq);
		ewse
			wet = disabwe_iwq_wake(pwiv->wake_iwq);
		pwiv->wake_iwq_enabwed = state;
	}

	wetuwn wet;
}

static int bcm54xx_suspend(stwuct phy_device *phydev)
{
	int wet = 0;

	bcm54xx_ptp_stop(phydev);

	/* Acknowwedge any Wake-on-WAN intewwupt pwiow to suspend */
	wet = bcm_phy_wead_exp(phydev, BCM54XX_WOW_INT_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (phydev->wow_enabwed)
		wetuwn bcm54xx_set_wakeup_iwq(phydev, twue);

	/* We cannot use a wead/modify/wwite hewe othewwise the PHY gets into
	 * a bad state whewe its WEDs keep fwashing, thus defeating the puwpose
	 * of wow powew mode.
	 */
	wet = phy_wwite(phydev, MII_BMCW, BMCW_PDOWN);
	if (wet < 0)
		wetuwn wet;

	wetuwn bcm54xx_iddq_set(phydev, twue);
}

static int bcm54xx_wesume(stwuct phy_device *phydev)
{
	int wet = 0;

	if (phydev->wow_enabwed) {
		wet = bcm54xx_set_wakeup_iwq(phydev, fawse);
		if (wet)
			wetuwn wet;
	}

	wet = bcm54xx_iddq_set(phydev, fawse);
	if (wet < 0)
		wetuwn wet;

	/* Wwites to wegistew othew than BMCW wouwd be ignowed
	 * unwess we cweaw the PDOWN bit fiwst
	 */
	wet = genphy_wesume(phydev);
	if (wet < 0)
		wetuwn wet;

	/* Upon exiting powew down, the PHY wemains in an intewnaw weset state
	 * fow 40us
	 */
	fsweep(40);

	/* Issue a soft weset aftew cweawing the powew down bit
	 * and befowe doing any othew configuwation.
	 */
	if (phydev->dev_fwags & PHY_BWCM_IDDQ_SUSPEND) {
		wet = genphy_soft_weset(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn bcm54xx_config_init(phydev);
}

static int bcm54810_wead_mmd(stwuct phy_device *phydev, int devnum, u16 wegnum)
{
	wetuwn -EOPNOTSUPP;
}

static int bcm54810_wwite_mmd(stwuct phy_device *phydev, int devnum, u16 wegnum,
			      u16 vaw)
{
	wetuwn -EOPNOTSUPP;
}

static int bcm54811_config_init(stwuct phy_device *phydev)
{
	int eww, weg;

	/* Disabwe BwoadW-Weach function. */
	weg = bcm_phy_wead_exp(phydev, BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW);
	weg &= ~BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW_EN;
	eww = bcm_phy_wwite_exp(phydev, BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW,
				weg);
	if (eww < 0)
		wetuwn eww;

	eww = bcm54xx_config_init(phydev);

	/* Enabwe CWK125 MUX on WED4 if wef cwock is enabwed. */
	if (!(phydev->dev_fwags & PHY_BWCM_WX_WEFCWK_UNUSED)) {
		weg = bcm_phy_wead_exp(phydev, BCM54612E_EXP_SPAWE0);
		eww = bcm_phy_wwite_exp(phydev, BCM54612E_EXP_SPAWE0,
					BCM54612E_WED4_CWK125OUT_EN | weg);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn eww;
}

static int bcm5481_config_aneg(stwuct phy_device *phydev)
{
	stwuct device_node *np = phydev->mdio.dev.of_node;
	int wet;

	/* Aneg fiwstwy. */
	wet = genphy_config_aneg(phydev);

	/* Then we can set up the deway. */
	bcm54xx_config_cwock_deway(phydev);

	if (of_pwopewty_wead_boow(np, "enet-phy-wane-swap")) {
		/* Wane Swap - Undocumented wegistew...magic! */
		wet = bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_SEW_EW + 0x9,
					0x11B);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wet;
}

stwuct bcm54616s_phy_pwiv {
	boow mode_1000bx_en;
};

static int bcm54616s_pwobe(stwuct phy_device *phydev)
{
	stwuct bcm54616s_phy_pwiv *pwiv;
	int vaw;

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_MODE);
	if (vaw < 0)
		wetuwn vaw;

	/* The PHY is stwapped in WGMII-fibew mode when INTEWF_SEW[1:0]
	 * is 01b, and the wink between PHY and its wink pawtnew can be
	 * eithew 1000Base-X ow 100Base-FX.
	 * WGMII-1000Base-X is pwopewwy suppowted, but WGMII-100Base-FX
	 * suppowt is stiww missing as of now.
	 */
	if ((vaw & BCM54XX_SHD_INTF_SEW_MASK) == BCM54XX_SHD_INTF_SEW_WGMII) {
		vaw = bcm_phy_wead_shadow(phydev, BCM54616S_SHD_100FX_CTWW);
		if (vaw < 0)
			wetuwn vaw;

		/* Bit 0 of the SewDes 100-FX Contwow wegistew, when set
		 * to 1, sets the MII/WGMII -> 100BASE-FX configuwation.
		 * When this bit is set to 0, it sets the GMII/WGMII ->
		 * 1000BASE-X configuwation.
		 */
		if (!(vaw & BCM54616S_100FX_MODE))
			pwiv->mode_1000bx_en = twue;

		phydev->powt = POWT_FIBWE;
	}

	wetuwn 0;
}

static int bcm54616s_config_aneg(stwuct phy_device *phydev)
{
	stwuct bcm54616s_phy_pwiv *pwiv = phydev->pwiv;
	int wet;

	/* Aneg fiwstwy. */
	if (pwiv->mode_1000bx_en)
		wet = genphy_c37_config_aneg(phydev);
	ewse
		wet = genphy_config_aneg(phydev);

	/* Then we can set up the deway. */
	bcm54xx_config_cwock_deway(phydev);

	wetuwn wet;
}

static int bcm54616s_wead_status(stwuct phy_device *phydev)
{
	stwuct bcm54616s_phy_pwiv *pwiv = phydev->pwiv;
	int eww;

	if (pwiv->mode_1000bx_en)
		eww = genphy_c37_wead_status(phydev);
	ewse
		eww = genphy_wead_status(phydev);

	wetuwn eww;
}

static int bwcm_fet_config_init(stwuct phy_device *phydev)
{
	int weg, eww, eww2, bwcmtest;

	/* Weset the PHY to bwing it to a known state. */
	eww = phy_wwite(phydev, MII_BMCW, BMCW_WESET);
	if (eww < 0)
		wetuwn eww;

	/* The datasheet indicates the PHY needs up to 1us to compwete a weset,
	 * buiwd some swack hewe.
	 */
	usweep_wange(1000, 2000);

	/* The PHY wequiwes 65 MDC cwock cycwes to compwete a wwite opewation
	 * and tuwnawound the wine pwopewwy.
	 *
	 * We ignowe -EIO hewe as the MDIO contwowwew (e.g.: mdio-bcm-unimac)
	 * may fwag the wack of tuwn-awound as a wead faiwuwe. This is
	 * pawticuwawwy twue with this combination since the MDIO contwowwew
	 * onwy used 64 MDC cycwes. This is not a cwiticaw faiwuwe in this
	 * specific case and it has no functionaw impact othewwise, so we wet
	 * that one go thwough. If thewe is a genuine bus ewwow, the next wead
	 * of MII_BWCM_FET_INTWEG wiww ewwow out.
	 */
	eww = phy_wead(phydev, MII_BMCW);
	if (eww < 0 && eww != -EIO)
		wetuwn eww;

	/* Wead to cweaw status bits */
	weg = phy_wead(phydev, MII_BWCM_FET_INTWEG);
	if (weg < 0)
		wetuwn weg;

	/* Unmask events we awe intewested in and mask intewwupts gwobawwy. */
	if (phydev->phy_id == PHY_ID_BCM5221)
		weg = MII_BWCM_FET_IW_ENABWE |
		      MII_BWCM_FET_IW_MASK;
	ewse
		weg = MII_BWCM_FET_IW_DUPWEX_EN |
		      MII_BWCM_FET_IW_SPEED_EN |
		      MII_BWCM_FET_IW_WINK_EN |
		      MII_BWCM_FET_IW_ENABWE |
		      MII_BWCM_FET_IW_MASK;

	eww = phy_wwite(phydev, MII_BWCM_FET_INTWEG, weg);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe shadow wegistew access */
	bwcmtest = phy_wead(phydev, MII_BWCM_FET_BWCMTEST);
	if (bwcmtest < 0)
		wetuwn bwcmtest;

	weg = bwcmtest | MII_BWCM_FET_BT_SWE;

	phy_wock_mdio_bus(phydev);

	eww = __phy_wwite(phydev, MII_BWCM_FET_BWCMTEST, weg);
	if (eww < 0) {
		phy_unwock_mdio_bus(phydev);
		wetuwn eww;
	}

	if (phydev->phy_id != PHY_ID_BCM5221) {
		/* Set the WED mode */
		weg = __phy_wead(phydev, MII_BWCM_FET_SHDW_AUXMODE4);
		if (weg < 0) {
			eww = weg;
			goto done;
		}

		eww = __phy_modify(phydev, MII_BWCM_FET_SHDW_AUXMODE4,
				   MII_BWCM_FET_SHDW_AM4_WED_MASK,
				   MII_BWCM_FET_SHDW_AM4_WED_MODE1);
		if (eww < 0)
			goto done;

		/* Enabwe auto MDIX */
		eww = __phy_set_bits(phydev, MII_BWCM_FET_SHDW_MISCCTWW,
				     MII_BWCM_FET_SHDW_MC_FAME);
		if (eww < 0)
			goto done;
	}

	if (phydev->dev_fwags & PHY_BWCM_AUTO_PWWDWN_ENABWE) {
		/* Enabwe auto powew down */
		eww = __phy_set_bits(phydev, MII_BWCM_FET_SHDW_AUXSTAT2,
				     MII_BWCM_FET_SHDW_AS2_APDE);
	}

done:
	/* Disabwe shadow wegistew access */
	eww2 = __phy_wwite(phydev, MII_BWCM_FET_BWCMTEST, bwcmtest);
	if (!eww)
		eww = eww2;

	phy_unwock_mdio_bus(phydev);

	wetuwn eww;
}

static int bwcm_fet_ack_intewwupt(stwuct phy_device *phydev)
{
	int weg;

	/* Cweaw pending intewwupts.  */
	weg = phy_wead(phydev, MII_BWCM_FET_INTWEG);
	if (weg < 0)
		wetuwn weg;

	wetuwn 0;
}

static int bwcm_fet_config_intw(stwuct phy_device *phydev)
{
	int weg, eww;

	weg = phy_wead(phydev, MII_BWCM_FET_INTWEG);
	if (weg < 0)
		wetuwn weg;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = bwcm_fet_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		weg &= ~MII_BWCM_FET_IW_MASK;
		eww = phy_wwite(phydev, MII_BWCM_FET_INTWEG, weg);
	} ewse {
		weg |= MII_BWCM_FET_IW_MASK;
		eww = phy_wwite(phydev, MII_BWCM_FET_INTWEG, weg);
		if (eww)
			wetuwn eww;

		eww = bwcm_fet_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t bwcm_fet_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_BWCM_FET_INTWEG);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (iwq_status == 0)
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int bwcm_fet_suspend(stwuct phy_device *phydev)
{
	int weg, eww, eww2, bwcmtest;

	/* We cannot use a wead/modify/wwite hewe othewwise the PHY continues
	 * to dwive WEDs which defeats the puwpose of wow powew mode.
	 */
	eww = phy_wwite(phydev, MII_BMCW, BMCW_PDOWN);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe shadow wegistew access */
	bwcmtest = phy_wead(phydev, MII_BWCM_FET_BWCMTEST);
	if (bwcmtest < 0)
		wetuwn bwcmtest;

	weg = bwcmtest | MII_BWCM_FET_BT_SWE;

	phy_wock_mdio_bus(phydev);

	eww = __phy_wwite(phydev, MII_BWCM_FET_BWCMTEST, weg);
	if (eww < 0) {
		phy_unwock_mdio_bus(phydev);
		wetuwn eww;
	}

	if (phydev->phy_id == PHY_ID_BCM5221)
		/* Fowce Wow Powew Mode with cwock enabwed */
		weg = BCM5221_SHDW_AM4_EN_CWK_WPM | BCM5221_SHDW_AM4_FOWCE_WPM;
	ewse
		/* Set standby mode */
		weg = MII_BWCM_FET_SHDW_AM4_STANDBY;

	eww = __phy_set_bits(phydev, MII_BWCM_FET_SHDW_AUXMODE4, weg);

	/* Disabwe shadow wegistew access */
	eww2 = __phy_wwite(phydev, MII_BWCM_FET_BWCMTEST, bwcmtest);
	if (!eww)
		eww = eww2;

	phy_unwock_mdio_bus(phydev);

	wetuwn eww;
}

static int bcm5221_config_aneg(stwuct phy_device *phydev)
{
	int wet, vaw;

	wet = genphy_config_aneg(phydev);
	if (wet)
		wetuwn wet;

	switch (phydev->mdix_ctww) {
	case ETH_TP_MDI:
		vaw = BCM5221_AEGSW_MDIX_DIS;
		bweak;
	case ETH_TP_MDI_X:
		vaw = BCM5221_AEGSW_MDIX_DIS | BCM5221_AEGSW_MDIX_MAN_SWAP;
		bweak;
	case ETH_TP_MDI_AUTO:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn phy_modify(phydev, BCM5221_AEGSW, BCM5221_AEGSW_MDIX_MAN_SWAP |
						 BCM5221_AEGSW_MDIX_DIS,
						 vaw);
}

static int bcm5221_wead_status(stwuct phy_device *phydev)
{
	int wet;

	/* Wead MDIX status */
	wet = phy_wead(phydev, BCM5221_AEGSW);
	if (wet < 0)
		wetuwn wet;

	if (wet & BCM5221_AEGSW_MDIX_DIS) {
		if (wet & BCM5221_AEGSW_MDIX_MAN_SWAP)
			phydev->mdix_ctww = ETH_TP_MDI_X;
		ewse
			phydev->mdix_ctww = ETH_TP_MDI;
	} ewse {
		phydev->mdix_ctww = ETH_TP_MDI_AUTO;
	}

	if (wet & BCM5221_AEGSW_MDIX_STATUS)
		phydev->mdix = ETH_TP_MDI_X;
	ewse
		phydev->mdix = ETH_TP_MDI;

	wetuwn genphy_wead_status(phydev);
}

static void bcm54xx_phy_get_wow(stwuct phy_device *phydev,
				stwuct ethtoow_wowinfo *wow)
{
	/* We cannot wake-up if we do not have a dedicated PHY intewwupt wine
	 * ow an out of band GPIO descwiptow fow wake-up. Zewoing
	 * wow->suppowted awwows the cawwew (MAC dwivew) to pway thwough and
	 * offew its own Wake-on-WAN scheme if avaiwabwe.
	 */
	if (!bcm54xx_phy_can_wakeup(phydev)) {
		wow->suppowted = 0;
		wetuwn;
	}

	bcm_phy_get_wow(phydev, wow);
}

static int bcm54xx_phy_set_wow(stwuct phy_device *phydev,
			       stwuct ethtoow_wowinfo *wow)
{
	int wet;

	/* We cannot wake-up if we do not have a dedicated PHY intewwupt wine
	 * ow an out of band GPIO descwiptow fow wake-up. Wetuwning -EOPNOTSUPP
	 * awwows the cawwew (MAC dwivew) to pway thwough and offew its own
	 * Wake-on-WAN scheme if avaiwabwe.
	 */
	if (!bcm54xx_phy_can_wakeup(phydev))
		wetuwn -EOPNOTSUPP;

	wet = bcm_phy_set_wow(phydev, wow);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int bcm54xx_phy_pwobe(stwuct phy_device *phydev)
{
	stwuct bcm54xx_phy_pwiv *pwiv;
	stwuct gpio_desc *wakeup_gpio;
	int wet = 0;

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wake_iwq = -ENXIO;

	phydev->pwiv = pwiv;

	pwiv->stats = devm_kcawwoc(&phydev->mdio.dev,
				   bcm_phy_get_sset_count(phydev), sizeof(u64),
				   GFP_KEWNEW);
	if (!pwiv->stats)
		wetuwn -ENOMEM;

	pwiv->ptp = bcm_ptp_pwobe(phydev);
	if (IS_EWW(pwiv->ptp))
		wetuwn PTW_EWW(pwiv->ptp);

	/* We cannot utiwize the _optionaw vawiant hewe since we want to know
	 * whethew the GPIO descwiptow exists ow not to advewtise Wake-on-WAN
	 * suppowt ow not.
	 */
	wakeup_gpio = devm_gpiod_get(&phydev->mdio.dev, "wakeup", GPIOD_IN);
	if (PTW_EWW(wakeup_gpio) == -EPWOBE_DEFEW)
		wetuwn PTW_EWW(wakeup_gpio);

	if (!IS_EWW(wakeup_gpio)) {
		pwiv->wake_iwq = gpiod_to_iwq(wakeup_gpio);

		/* Dummy intewwupt handwew which is not enabwed but is pwovided
		 * in owdew fow the intewwupt descwiptow to be fuwwy set-up.
		 */
		wet = devm_wequest_iwq(&phydev->mdio.dev, pwiv->wake_iwq,
				       bcm_phy_wow_isw,
				       IWQF_TWIGGEW_WOW | IWQF_NO_AUTOEN,
				       dev_name(&phydev->mdio.dev), phydev);
		if (wet)
			wetuwn wet;
	}

	/* If we do not have a main intewwupt ow a side-band wake-up intewwupt,
	 * then the device cannot be mawked as wake-up capabwe.
	 */
	if (!bcm54xx_phy_can_wakeup(phydev))
		wetuwn 0;

	wetuwn device_init_wakeup(&phydev->mdio.dev, twue);
}

static void bcm54xx_get_stats(stwuct phy_device *phydev,
			      stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct bcm54xx_phy_pwiv *pwiv = phydev->pwiv;

	bcm_phy_get_stats(phydev, pwiv->stats, stats, data);
}

static void bcm54xx_wink_change_notify(stwuct phy_device *phydev)
{
	u16 mask = MII_BCM54XX_EXP_EXP08_EAWWY_DAC_WAKE |
		   MII_BCM54XX_EXP_EXP08_FOWCE_DAC_WAKE;
	int wet;

	if (phydev->state != PHY_WUNNING)
		wetuwn;

	/* Don't change the DAC wake settings if auto powew down
	 * is not wequested.
	 */
	if (!(phydev->dev_fwags & PHY_BWCM_AUTO_PWWDWN_ENABWE))
		wetuwn;

	wet = bcm_phy_wead_exp(phydev, MII_BCM54XX_EXP_EXP08);
	if (wet < 0)
		wetuwn;

	/* Enabwe/disabwe 10BaseT auto and fowced eawwy DAC wake depending
	 * on the negotiated speed, those settings shouwd onwy be done
	 * fow 10Mbits/sec.
	 */
	if (phydev->speed == SPEED_10)
		wet |= mask;
	ewse
		wet &= ~mask;
	bcm_phy_wwite_exp(phydev, MII_BCM54XX_EXP_EXP08, wet);
}

static stwuct phy_dwivew bwoadcom_dwivews[] = {
{
	.phy_id		= PHY_ID_BCM5411,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5411",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
}, {
	.phy_id		= PHY_ID_BCM5421,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5421",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
}, {
	.phy_id		= PHY_ID_BCM54210E,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM54210E",
	/* PHY_GBIT_FEATUWES */
	.fwags		= PHY_AWWAYS_CAWW_SUSPEND,
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.suspend	= bcm54xx_suspend,
	.wesume		= bcm54xx_wesume,
	.get_wow	= bcm54xx_phy_get_wow,
	.set_wow	= bcm54xx_phy_set_wow,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM5461,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5461",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM54612E,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM54612E",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
	.suspend	= bcm54xx_suspend,
	.wesume		= bcm54xx_wesume,
}, {
	.phy_id		= PHY_ID_BCM54616S,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM54616S",
	/* PHY_GBIT_FEATUWES */
	.soft_weset     = genphy_soft_weset,
	.config_init	= bcm54xx_config_init,
	.config_aneg	= bcm54616s_config_aneg,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wead_status	= bcm54616s_wead_status,
	.pwobe		= bcm54616s_pwobe,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM5464,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5464",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM5481,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5481",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_aneg	= bcm5481_config_aneg,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id         = PHY_ID_BCM54810,
	.phy_id_mask    = 0xfffffff0,
	.name           = "Bwoadcom BCM54810",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.wead_mmd	= bcm54810_wead_mmd,
	.wwite_mmd	= bcm54810_wwite_mmd,
	.config_init    = bcm54xx_config_init,
	.config_aneg    = bcm5481_config_aneg,
	.config_intw    = bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.suspend	= bcm54xx_suspend,
	.wesume		= bcm54xx_wesume,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id         = PHY_ID_BCM54811,
	.phy_id_mask    = 0xfffffff0,
	.name           = "Bwoadcom BCM54811",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init    = bcm54811_config_init,
	.config_aneg    = bcm5481_config_aneg,
	.config_intw    = bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.suspend	= bcm54xx_suspend,
	.wesume		= bcm54xx_wesume,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM5482,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5482",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM50610,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM50610",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.suspend	= bcm54xx_suspend,
	.wesume		= bcm54xx_wesume,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM50610M,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM50610M",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.suspend	= bcm54xx_suspend,
	.wesume		= bcm54xx_wesume,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM57780,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM57780",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCMAC131,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCMAC131",
	/* PHY_BASIC_FEATUWES */
	.config_init	= bwcm_fet_config_init,
	.config_intw	= bwcm_fet_config_intw,
	.handwe_intewwupt = bwcm_fet_handwe_intewwupt,
	.suspend	= bwcm_fet_suspend,
	.wesume		= bwcm_fet_config_init,
}, {
	.phy_id		= PHY_ID_BCM5241,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5241",
	/* PHY_BASIC_FEATUWES */
	.config_init	= bwcm_fet_config_init,
	.config_intw	= bwcm_fet_config_intw,
	.handwe_intewwupt = bwcm_fet_handwe_intewwupt,
	.suspend	= bwcm_fet_suspend,
	.wesume		= bwcm_fet_config_init,
}, {
	.phy_id		= PHY_ID_BCM5221,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5221",
	/* PHY_BASIC_FEATUWES */
	.config_init	= bwcm_fet_config_init,
	.config_intw	= bwcm_fet_config_intw,
	.handwe_intewwupt = bwcm_fet_handwe_intewwupt,
	.suspend	= bwcm_fet_suspend,
	.wesume		= bwcm_fet_config_init,
	.config_aneg	= bcm5221_config_aneg,
	.wead_status	= bcm5221_wead_status,
}, {
	.phy_id		= PHY_ID_BCM5395,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM5395",
	.fwags		= PHY_IS_INTEWNAW,
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM53125,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM53125",
	.fwags		= PHY_IS_INTEWNAW,
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id		= PHY_ID_BCM53128,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom BCM53128",
	.fwags		= PHY_IS_INTEWNAW,
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init	= bcm54xx_config_init,
	.config_intw	= bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
	.wed_bwightness_set	= bcm_phy_wed_bwightness_set,
}, {
	.phy_id         = PHY_ID_BCM89610,
	.phy_id_mask    = 0xfffffff0,
	.name           = "Bwoadcom BCM89610",
	/* PHY_GBIT_FEATUWES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm54xx_get_stats,
	.pwobe		= bcm54xx_phy_pwobe,
	.config_init    = bcm54xx_config_init,
	.config_intw    = bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.wink_change_notify	= bcm54xx_wink_change_notify,
} };

moduwe_phy_dwivew(bwoadcom_dwivews);

static stwuct mdio_device_id __maybe_unused bwoadcom_tbw[] = {
	{ PHY_ID_BCM5411, 0xfffffff0 },
	{ PHY_ID_BCM5421, 0xfffffff0 },
	{ PHY_ID_BCM54210E, 0xfffffff0 },
	{ PHY_ID_BCM5461, 0xfffffff0 },
	{ PHY_ID_BCM54612E, 0xfffffff0 },
	{ PHY_ID_BCM54616S, 0xfffffff0 },
	{ PHY_ID_BCM5464, 0xfffffff0 },
	{ PHY_ID_BCM5481, 0xfffffff0 },
	{ PHY_ID_BCM54810, 0xfffffff0 },
	{ PHY_ID_BCM54811, 0xfffffff0 },
	{ PHY_ID_BCM5482, 0xfffffff0 },
	{ PHY_ID_BCM50610, 0xfffffff0 },
	{ PHY_ID_BCM50610M, 0xfffffff0 },
	{ PHY_ID_BCM57780, 0xfffffff0 },
	{ PHY_ID_BCMAC131, 0xfffffff0 },
	{ PHY_ID_BCM5221, 0xfffffff0 },
	{ PHY_ID_BCM5241, 0xfffffff0 },
	{ PHY_ID_BCM5395, 0xfffffff0 },
	{ PHY_ID_BCM53125, 0xfffffff0 },
	{ PHY_ID_BCM53128, 0xfffffff0 },
	{ PHY_ID_BCM89610, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, bwoadcom_tbw);
