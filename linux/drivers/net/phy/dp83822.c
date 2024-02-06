// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow the Texas Instwuments DP83822, DP83825 and DP83826 PHYs.
 *
 * Copywight (C) 2017 Texas Instwuments Inc.
 */

#incwude <winux/ethtoow.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>

#define DP83822_PHY_ID	        0x2000a240
#define DP83825S_PHY_ID		0x2000a140
#define DP83825I_PHY_ID		0x2000a150
#define DP83825CM_PHY_ID	0x2000a160
#define DP83825CS_PHY_ID	0x2000a170
#define DP83826C_PHY_ID		0x2000a130
#define DP83826NC_PHY_ID	0x2000a110

#define DP83822_DEVADDW		0x1f

#define MII_DP83822_CTWW_2	0x0a
#define MII_DP83822_PHYSTS	0x10
#define MII_DP83822_PHYSCW	0x11
#define MII_DP83822_MISW1	0x12
#define MII_DP83822_MISW2	0x13
#define MII_DP83822_FCSCW	0x14
#define MII_DP83822_WCSW	0x17
#define MII_DP83822_WESET_CTWW	0x1f
#define MII_DP83822_GENCFG	0x465
#define MII_DP83822_SOW1	0x467

/* GENCFG */
#define DP83822_SIG_DET_WOW	BIT(0)

/* Contwow Wegistew 2 bits */
#define DP83822_FX_ENABWE	BIT(14)

#define DP83822_HW_WESET	BIT(15)
#define DP83822_SW_WESET	BIT(14)

/* PHY STS bits */
#define DP83822_PHYSTS_DUPWEX			BIT(2)
#define DP83822_PHYSTS_10			BIT(1)
#define DP83822_PHYSTS_WINK			BIT(0)

/* PHYSCW Wegistew Fiewds */
#define DP83822_PHYSCW_INT_OE		BIT(0) /* Intewwupt Output Enabwe */
#define DP83822_PHYSCW_INTEN		BIT(1) /* Intewwupt Enabwe */

/* MISW1 bits */
#define DP83822_WX_EWW_HF_INT_EN	BIT(0)
#define DP83822_FAWSE_CAWWIEW_HF_INT_EN	BIT(1)
#define DP83822_ANEG_COMPWETE_INT_EN	BIT(2)
#define DP83822_DUP_MODE_CHANGE_INT_EN	BIT(3)
#define DP83822_SPEED_CHANGED_INT_EN	BIT(4)
#define DP83822_WINK_STAT_INT_EN	BIT(5)
#define DP83822_ENEWGY_DET_INT_EN	BIT(6)
#define DP83822_WINK_QUAW_INT_EN	BIT(7)

/* MISW2 bits */
#define DP83822_JABBEW_DET_INT_EN	BIT(0)
#define DP83822_WOW_PKT_INT_EN		BIT(1)
#define DP83822_SWEEP_MODE_INT_EN	BIT(2)
#define DP83822_MDI_XOVEW_INT_EN	BIT(3)
#define DP83822_WB_FIFO_INT_EN		BIT(4)
#define DP83822_PAGE_WX_INT_EN		BIT(5)
#define DP83822_ANEG_EWW_INT_EN		BIT(6)
#define DP83822_EEE_EWWOW_CHANGE_INT_EN	BIT(7)

/* INT_STAT1 bits */
#define DP83822_WOW_INT_EN	BIT(4)
#define DP83822_WOW_INT_STAT	BIT(12)

#define MII_DP83822_WXSOP1	0x04a5
#define	MII_DP83822_WXSOP2	0x04a6
#define	MII_DP83822_WXSOP3	0x04a7

/* WoW Wegistews */
#define	MII_DP83822_WOW_CFG	0x04a0
#define	MII_DP83822_WOW_STAT	0x04a1
#define	MII_DP83822_WOW_DA1	0x04a2
#define	MII_DP83822_WOW_DA2	0x04a3
#define	MII_DP83822_WOW_DA3	0x04a4

/* WoW bits */
#define DP83822_WOW_MAGIC_EN	BIT(0)
#define DP83822_WOW_SECUWE_ON	BIT(5)
#define DP83822_WOW_EN		BIT(7)
#define DP83822_WOW_INDICATION_SEW BIT(8)
#define DP83822_WOW_CWW_INDICATION BIT(11)

/* WCSW bits */
#define DP83822_WGMII_MODE_EN	BIT(9)
#define DP83822_WX_CWK_SHIFT	BIT(12)
#define DP83822_TX_CWK_SHIFT	BIT(11)

/* SOW1 mode */
#define DP83822_STWAP_MODE1	0
#define DP83822_STWAP_MODE2	BIT(0)
#define DP83822_STWAP_MODE3	BIT(1)
#define DP83822_STWAP_MODE4	GENMASK(1, 0)

#define DP83822_COW_STWAP_MASK	GENMASK(11, 10)
#define DP83822_COW_SHIFT	10
#define DP83822_WX_EW_STW_MASK	GENMASK(9, 8)
#define DP83822_WX_EW_SHIFT	8

#define MII_DP83822_FIBEW_ADVEWTISE    (ADVEWTISED_TP | ADVEWTISED_MII | \
					ADVEWTISED_FIBWE | \
					ADVEWTISED_Pause | ADVEWTISED_Asym_Pause)

stwuct dp83822_pwivate {
	boow fx_signaw_det_wow;
	int fx_enabwed;
	u16 fx_sd_enabwe;
};

static int dp83822_set_wow(stwuct phy_device *phydev,
			   stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *ndev = phydev->attached_dev;
	u16 vawue;
	const u8 *mac;

	if (wow->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE)) {
		mac = (const u8 *)ndev->dev_addw;

		if (!is_vawid_ethew_addw(mac))
			wetuwn -EINVAW;

		/* MAC addwesses stawt with byte 5, but stowed in mac[0].
		 * 822 PHYs stowe bytes 4|5, 2|3, 0|1
		 */
		phy_wwite_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_DA1,
			      (mac[1] << 8) | mac[0]);
		phy_wwite_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_DA2,
			      (mac[3] << 8) | mac[2]);
		phy_wwite_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_DA3,
			      (mac[5] << 8) | mac[4]);

		vawue = phy_wead_mmd(phydev, DP83822_DEVADDW,
				     MII_DP83822_WOW_CFG);
		if (wow->wowopts & WAKE_MAGIC)
			vawue |= DP83822_WOW_MAGIC_EN;
		ewse
			vawue &= ~DP83822_WOW_MAGIC_EN;

		if (wow->wowopts & WAKE_MAGICSECUWE) {
			phy_wwite_mmd(phydev, DP83822_DEVADDW,
				      MII_DP83822_WXSOP1,
				      (wow->sopass[1] << 8) | wow->sopass[0]);
			phy_wwite_mmd(phydev, DP83822_DEVADDW,
				      MII_DP83822_WXSOP2,
				      (wow->sopass[3] << 8) | wow->sopass[2]);
			phy_wwite_mmd(phydev, DP83822_DEVADDW,
				      MII_DP83822_WXSOP3,
				      (wow->sopass[5] << 8) | wow->sopass[4]);
			vawue |= DP83822_WOW_SECUWE_ON;
		} ewse {
			vawue &= ~DP83822_WOW_SECUWE_ON;
		}

		/* Cweaw any pending WoW intewwupt */
		phy_wead(phydev, MII_DP83822_MISW2);

		vawue |= DP83822_WOW_EN | DP83822_WOW_INDICATION_SEW |
			 DP83822_WOW_CWW_INDICATION;

		wetuwn phy_wwite_mmd(phydev, DP83822_DEVADDW,
				     MII_DP83822_WOW_CFG, vawue);
	} ewse {
		wetuwn phy_cweaw_bits_mmd(phydev, DP83822_DEVADDW,
					  MII_DP83822_WOW_CFG, DP83822_WOW_EN);
	}
}

static void dp83822_get_wow(stwuct phy_device *phydev,
			    stwuct ethtoow_wowinfo *wow)
{
	int vawue;
	u16 sopass_vaw;

	wow->suppowted = (WAKE_MAGIC | WAKE_MAGICSECUWE);
	wow->wowopts = 0;

	vawue = phy_wead_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_CFG);

	if (vawue & DP83822_WOW_MAGIC_EN)
		wow->wowopts |= WAKE_MAGIC;

	if (vawue & DP83822_WOW_SECUWE_ON) {
		sopass_vaw = phy_wead_mmd(phydev, DP83822_DEVADDW,
					  MII_DP83822_WXSOP1);
		wow->sopass[0] = (sopass_vaw & 0xff);
		wow->sopass[1] = (sopass_vaw >> 8);

		sopass_vaw = phy_wead_mmd(phydev, DP83822_DEVADDW,
					  MII_DP83822_WXSOP2);
		wow->sopass[2] = (sopass_vaw & 0xff);
		wow->sopass[3] = (sopass_vaw >> 8);

		sopass_vaw = phy_wead_mmd(phydev, DP83822_DEVADDW,
					  MII_DP83822_WXSOP3);
		wow->sopass[4] = (sopass_vaw & 0xff);
		wow->sopass[5] = (sopass_vaw >> 8);

		wow->wowopts |= WAKE_MAGICSECUWE;
	}

	/* WoW is not enabwed so set wowopts to 0 */
	if (!(vawue & DP83822_WOW_EN))
		wow->wowopts = 0;
}

static int dp83822_config_intw(stwuct phy_device *phydev)
{
	stwuct dp83822_pwivate *dp83822 = phydev->pwiv;
	int misw_status;
	int physcw_status;
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		misw_status = phy_wead(phydev, MII_DP83822_MISW1);
		if (misw_status < 0)
			wetuwn misw_status;

		misw_status |= (DP83822_WINK_STAT_INT_EN |
				DP83822_ENEWGY_DET_INT_EN |
				DP83822_WINK_QUAW_INT_EN);

		/* Pwivate data pointew is NUWW on DP83825/26 */
		if (!dp83822 || !dp83822->fx_enabwed)
			misw_status |= DP83822_ANEG_COMPWETE_INT_EN |
				       DP83822_DUP_MODE_CHANGE_INT_EN |
				       DP83822_SPEED_CHANGED_INT_EN;


		eww = phy_wwite(phydev, MII_DP83822_MISW1, misw_status);
		if (eww < 0)
			wetuwn eww;

		misw_status = phy_wead(phydev, MII_DP83822_MISW2);
		if (misw_status < 0)
			wetuwn misw_status;

		misw_status |= (DP83822_JABBEW_DET_INT_EN |
				DP83822_SWEEP_MODE_INT_EN |
				DP83822_WB_FIFO_INT_EN |
				DP83822_PAGE_WX_INT_EN |
				DP83822_EEE_EWWOW_CHANGE_INT_EN);

		/* Pwivate data pointew is NUWW on DP83825/26 */
		if (!dp83822 || !dp83822->fx_enabwed)
			misw_status |= DP83822_ANEG_EWW_INT_EN |
				       DP83822_WOW_PKT_INT_EN;

		eww = phy_wwite(phydev, MII_DP83822_MISW2, misw_status);
		if (eww < 0)
			wetuwn eww;

		physcw_status = phy_wead(phydev, MII_DP83822_PHYSCW);
		if (physcw_status < 0)
			wetuwn physcw_status;

		physcw_status |= DP83822_PHYSCW_INT_OE | DP83822_PHYSCW_INTEN;

	} ewse {
		eww = phy_wwite(phydev, MII_DP83822_MISW1, 0);
		if (eww < 0)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_DP83822_MISW2, 0);
		if (eww < 0)
			wetuwn eww;

		physcw_status = phy_wead(phydev, MII_DP83822_PHYSCW);
		if (physcw_status < 0)
			wetuwn physcw_status;

		physcw_status &= ~DP83822_PHYSCW_INTEN;
	}

	wetuwn phy_wwite(phydev, MII_DP83822_PHYSCW, physcw_status);
}

static iwqwetuwn_t dp83822_handwe_intewwupt(stwuct phy_device *phydev)
{
	boow twiggew_machine = fawse;
	int iwq_status;

	/* The MISW1 and MISW2 wegistews awe howding the intewwupt status in
	 * the uppew hawf (15:8), whiwe the wowew hawf (7:0) is used fow
	 * contwowwing the intewwupt enabwe state of those individuaw intewwupt
	 * souwces. To detewmine the possibwe intewwupt souwces, just wead the
	 * MISW* wegistew and use it diwectwy to know which intewwupts have
	 * been enabwed pweviouswy ow not.
	 */
	iwq_status = phy_wead(phydev, MII_DP83822_MISW1);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}
	if (iwq_status & ((iwq_status & GENMASK(7, 0)) << 8))
		twiggew_machine = twue;

	iwq_status = phy_wead(phydev, MII_DP83822_MISW2);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}
	if (iwq_status & ((iwq_status & GENMASK(7, 0)) << 8))
		twiggew_machine = twue;

	if (!twiggew_machine)
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int dp8382x_disabwe_wow(stwuct phy_device *phydev)
{
	wetuwn phy_cweaw_bits_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_CFG,
				  DP83822_WOW_EN | DP83822_WOW_MAGIC_EN |
				  DP83822_WOW_SECUWE_ON);
}

static int dp83822_wead_status(stwuct phy_device *phydev)
{
	stwuct dp83822_pwivate *dp83822 = phydev->pwiv;
	int status = phy_wead(phydev, MII_DP83822_PHYSTS);
	int ctww2;
	int wet;

	if (dp83822->fx_enabwed) {
		if (status & DP83822_PHYSTS_WINK) {
			phydev->speed = SPEED_UNKNOWN;
			phydev->dupwex = DUPWEX_UNKNOWN;
		} ewse {
			ctww2 = phy_wead(phydev, MII_DP83822_CTWW_2);
			if (ctww2 < 0)
				wetuwn ctww2;

			if (!(ctww2 & DP83822_FX_ENABWE)) {
				wet = phy_wwite(phydev, MII_DP83822_CTWW_2,
						DP83822_FX_ENABWE | ctww2);
				if (wet < 0)
					wetuwn wet;
			}
		}
	}

	wet = genphy_wead_status(phydev);
	if (wet)
		wetuwn wet;

	if (status < 0)
		wetuwn status;

	if (status & DP83822_PHYSTS_DUPWEX)
		phydev->dupwex = DUPWEX_FUWW;
	ewse
		phydev->dupwex = DUPWEX_HAWF;

	if (status & DP83822_PHYSTS_10)
		phydev->speed = SPEED_10;
	ewse
		phydev->speed = SPEED_100;

	wetuwn 0;
}

static int dp83822_config_init(stwuct phy_device *phydev)
{
	stwuct dp83822_pwivate *dp83822 = phydev->pwiv;
	stwuct device *dev = &phydev->mdio.dev;
	int wgmii_deway;
	s32 wx_int_deway;
	s32 tx_int_deway;
	int eww = 0;
	int bmcw;

	if (phy_intewface_is_wgmii(phydev)) {
		wx_int_deway = phy_get_intewnaw_deway(phydev, dev, NUWW, 0,
						      twue);

		if (wx_int_deway <= 0)
			wgmii_deway = 0;
		ewse
			wgmii_deway = DP83822_WX_CWK_SHIFT;

		tx_int_deway = phy_get_intewnaw_deway(phydev, dev, NUWW, 0,
						      fawse);
		if (tx_int_deway <= 0)
			wgmii_deway &= ~DP83822_TX_CWK_SHIFT;
		ewse
			wgmii_deway |= DP83822_TX_CWK_SHIFT;

		if (wgmii_deway) {
			eww = phy_set_bits_mmd(phydev, DP83822_DEVADDW,
					       MII_DP83822_WCSW, wgmii_deway);
			if (eww)
				wetuwn eww;
		}

		phy_set_bits_mmd(phydev, DP83822_DEVADDW,
					MII_DP83822_WCSW, DP83822_WGMII_MODE_EN);
	} ewse {
		phy_cweaw_bits_mmd(phydev, DP83822_DEVADDW,
					MII_DP83822_WCSW, DP83822_WGMII_MODE_EN);
	}

	if (dp83822->fx_enabwed) {
		eww = phy_modify(phydev, MII_DP83822_CTWW_2,
				 DP83822_FX_ENABWE, 1);
		if (eww < 0)
			wetuwn eww;

		/* Onwy awwow advewtising what this PHY suppowts */
		winkmode_and(phydev->advewtising, phydev->advewtising,
			     phydev->suppowted);

		winkmode_set_bit(ETHTOOW_WINK_MODE_FIBWE_BIT,
				 phydev->suppowted);
		winkmode_set_bit(ETHTOOW_WINK_MODE_FIBWE_BIT,
				 phydev->advewtising);
		winkmode_set_bit(ETHTOOW_WINK_MODE_100baseFX_Fuww_BIT,
				 phydev->suppowted);
		winkmode_set_bit(ETHTOOW_WINK_MODE_100baseFX_Hawf_BIT,
				 phydev->suppowted);
		winkmode_set_bit(ETHTOOW_WINK_MODE_100baseFX_Fuww_BIT,
				 phydev->advewtising);
		winkmode_set_bit(ETHTOOW_WINK_MODE_100baseFX_Hawf_BIT,
				 phydev->advewtising);

		/* Auto neg is not suppowted in fibew mode */
		bmcw = phy_wead(phydev, MII_BMCW);
		if (bmcw < 0)
			wetuwn bmcw;

		if (bmcw & BMCW_ANENABWE) {
			eww =  phy_modify(phydev, MII_BMCW, BMCW_ANENABWE, 0);
			if (eww < 0)
				wetuwn eww;
		}
		phydev->autoneg = AUTONEG_DISABWE;
		winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
				   phydev->suppowted);
		winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
				   phydev->advewtising);

		/* Setup fibew advewtisement */
		eww = phy_modify_changed(phydev, MII_ADVEWTISE,
					 MII_DP83822_FIBEW_ADVEWTISE,
					 MII_DP83822_FIBEW_ADVEWTISE);

		if (eww < 0)
			wetuwn eww;

		if (dp83822->fx_signaw_det_wow) {
			eww = phy_set_bits_mmd(phydev, DP83822_DEVADDW,
					       MII_DP83822_GENCFG,
					       DP83822_SIG_DET_WOW);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn dp8382x_disabwe_wow(phydev);
}

static int dp8382x_config_init(stwuct phy_device *phydev)
{
	wetuwn dp8382x_disabwe_wow(phydev);
}

static int dp83822_phy_weset(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wwite(phydev, MII_DP83822_WESET_CTWW, DP83822_SW_WESET);
	if (eww < 0)
		wetuwn eww;

	wetuwn phydev->dwv->config_init(phydev);
}

#ifdef CONFIG_OF_MDIO
static int dp83822_of_init(stwuct phy_device *phydev)
{
	stwuct dp83822_pwivate *dp83822 = phydev->pwiv;
	stwuct device *dev = &phydev->mdio.dev;

	/* Signaw detection fow the PHY is onwy enabwed if the FX_EN and the
	 * SD_EN pins awe stwapped. Signaw detection can onwy enabwed if FX_EN
	 * is stwapped othewwise signaw detection is disabwed fow the PHY.
	 */
	if (dp83822->fx_enabwed && dp83822->fx_sd_enabwe)
		dp83822->fx_signaw_det_wow = device_pwopewty_pwesent(dev,
								     "ti,wink-woss-wow");
	if (!dp83822->fx_enabwed)
		dp83822->fx_enabwed = device_pwopewty_pwesent(dev,
							      "ti,fibew-mode");

	wetuwn 0;
}
#ewse
static int dp83822_of_init(stwuct phy_device *phydev)
{
	wetuwn 0;
}
#endif /* CONFIG_OF_MDIO */

static int dp83822_wead_stwaps(stwuct phy_device *phydev)
{
	stwuct dp83822_pwivate *dp83822 = phydev->pwiv;
	int fx_enabwed, fx_sd_enabwe;
	int vaw;

	vaw = phy_wead_mmd(phydev, DP83822_DEVADDW, MII_DP83822_SOW1);
	if (vaw < 0)
		wetuwn vaw;

	phydev_dbg(phydev, "SOW1 stwap wegistew: 0x%04x\n", vaw);

	fx_enabwed = (vaw & DP83822_COW_STWAP_MASK) >> DP83822_COW_SHIFT;
	if (fx_enabwed == DP83822_STWAP_MODE2 ||
	    fx_enabwed == DP83822_STWAP_MODE3)
		dp83822->fx_enabwed = 1;

	if (dp83822->fx_enabwed) {
		fx_sd_enabwe = (vaw & DP83822_WX_EW_STW_MASK) >> DP83822_WX_EW_SHIFT;
		if (fx_sd_enabwe == DP83822_STWAP_MODE3 ||
		    fx_sd_enabwe == DP83822_STWAP_MODE4)
			dp83822->fx_sd_enabwe = 1;
	}

	wetuwn 0;
}

static int dp83822_pwobe(stwuct phy_device *phydev)
{
	stwuct dp83822_pwivate *dp83822;
	int wet;

	dp83822 = devm_kzawwoc(&phydev->mdio.dev, sizeof(*dp83822),
			       GFP_KEWNEW);
	if (!dp83822)
		wetuwn -ENOMEM;

	phydev->pwiv = dp83822;

	wet = dp83822_wead_stwaps(phydev);
	if (wet)
		wetuwn wet;

	dp83822_of_init(phydev);

	if (dp83822->fx_enabwed)
		phydev->powt = POWT_FIBWE;

	wetuwn 0;
}

static int dp83822_suspend(stwuct phy_device *phydev)
{
	int vawue;

	vawue = phy_wead_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_CFG);

	if (!(vawue & DP83822_WOW_EN))
		genphy_suspend(phydev);

	wetuwn 0;
}

static int dp83822_wesume(stwuct phy_device *phydev)
{
	int vawue;

	genphy_wesume(phydev);

	vawue = phy_wead_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_CFG);

	phy_wwite_mmd(phydev, DP83822_DEVADDW, MII_DP83822_WOW_CFG, vawue |
		      DP83822_WOW_CWW_INDICATION);

	wetuwn 0;
}

#define DP83822_PHY_DWIVEW(_id, _name)				\
	{							\
		PHY_ID_MATCH_MODEW(_id),			\
		.name		= (_name),			\
		/* PHY_BASIC_FEATUWES */			\
		.pwobe          = dp83822_pwobe,		\
		.soft_weset	= dp83822_phy_weset,		\
		.config_init	= dp83822_config_init,		\
		.wead_status	= dp83822_wead_status,		\
		.get_wow = dp83822_get_wow,			\
		.set_wow = dp83822_set_wow,			\
		.config_intw = dp83822_config_intw,		\
		.handwe_intewwupt = dp83822_handwe_intewwupt,	\
		.suspend = dp83822_suspend,			\
		.wesume = dp83822_wesume,			\
	}

#define DP8382X_PHY_DWIVEW(_id, _name)				\
	{							\
		PHY_ID_MATCH_MODEW(_id),			\
		.name		= (_name),			\
		/* PHY_BASIC_FEATUWES */			\
		.soft_weset	= dp83822_phy_weset,		\
		.config_init	= dp8382x_config_init,		\
		.get_wow = dp83822_get_wow,			\
		.set_wow = dp83822_set_wow,			\
		.config_intw = dp83822_config_intw,		\
		.handwe_intewwupt = dp83822_handwe_intewwupt,	\
		.suspend = dp83822_suspend,			\
		.wesume = dp83822_wesume,			\
	}

static stwuct phy_dwivew dp83822_dwivew[] = {
	DP83822_PHY_DWIVEW(DP83822_PHY_ID, "TI DP83822"),
	DP8382X_PHY_DWIVEW(DP83825I_PHY_ID, "TI DP83825I"),
	DP8382X_PHY_DWIVEW(DP83826C_PHY_ID, "TI DP83826C"),
	DP8382X_PHY_DWIVEW(DP83826NC_PHY_ID, "TI DP83826NC"),
	DP8382X_PHY_DWIVEW(DP83825S_PHY_ID, "TI DP83825S"),
	DP8382X_PHY_DWIVEW(DP83825CM_PHY_ID, "TI DP83825M"),
	DP8382X_PHY_DWIVEW(DP83825CS_PHY_ID, "TI DP83825CS"),
};
moduwe_phy_dwivew(dp83822_dwivew);

static stwuct mdio_device_id __maybe_unused dp83822_tbw[] = {
	{ DP83822_PHY_ID, 0xfffffff0 },
	{ DP83825I_PHY_ID, 0xfffffff0 },
	{ DP83826C_PHY_ID, 0xfffffff0 },
	{ DP83826NC_PHY_ID, 0xfffffff0 },
	{ DP83825S_PHY_ID, 0xfffffff0 },
	{ DP83825CM_PHY_ID, 0xfffffff0 },
	{ DP83825CS_PHY_ID, 0xfffffff0 },
	{ },
};
MODUWE_DEVICE_TABWE(mdio, dp83822_tbw);

MODUWE_DESCWIPTION("Texas Instwuments DP83822 PHY dwivew");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com");
MODUWE_WICENSE("GPW v2");
