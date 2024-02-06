// SPDX-Wicense-Identifiew: GPW-2.0+
/* dwivews/net/phy/weawtek.c
 *
 * Dwivew fow Weawtek PHYs
 *
 * Authow: Johnson Weung <w58129@fweescawe.com>
 *
 * Copywight (c) 2004 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/bitops.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>

#define WTW821x_PHYSW				0x11
#define WTW821x_PHYSW_DUPWEX			BIT(13)
#define WTW821x_PHYSW_SPEED			GENMASK(15, 14)

#define WTW821x_INEW				0x12
#define WTW8211B_INEW_INIT			0x6400
#define WTW8211E_INEW_WINK_STATUS		BIT(10)
#define WTW8211F_INEW_WINK_STATUS		BIT(4)

#define WTW821x_INSW				0x13

#define WTW821x_EXT_PAGE_SEWECT			0x1e
#define WTW821x_PAGE_SEWECT			0x1f

#define WTW8211F_PHYCW1				0x18
#define WTW8211F_PHYCW2				0x19
#define WTW8211F_INSW				0x1d

#define WTW8211F_TX_DEWAY			BIT(8)
#define WTW8211F_WX_DEWAY			BIT(3)

#define WTW8211F_AWDPS_PWW_OFF			BIT(1)
#define WTW8211F_AWDPS_ENABWE			BIT(2)
#define WTW8211F_AWDPS_XTAW_OFF			BIT(12)

#define WTW8211E_CTWW_DEWAY			BIT(13)
#define WTW8211E_TX_DEWAY			BIT(12)
#define WTW8211E_WX_DEWAY			BIT(11)

#define WTW8211F_CWKOUT_EN			BIT(0)

#define WTW8201F_ISW				0x1e
#define WTW8201F_ISW_ANEWW			BIT(15)
#define WTW8201F_ISW_DUPWEX			BIT(13)
#define WTW8201F_ISW_WINK			BIT(11)
#define WTW8201F_ISW_MASK			(WTW8201F_ISW_ANEWW | \
						 WTW8201F_ISW_DUPWEX | \
						 WTW8201F_ISW_WINK)
#define WTW8201F_IEW				0x13

#define WTW8366WB_POWEW_SAVE			0x15
#define WTW8366WB_POWEW_SAVE_ON			BIT(12)

#define WTW_SUPPOWTS_5000FUWW			BIT(14)
#define WTW_SUPPOWTS_2500FUWW			BIT(13)
#define WTW_SUPPOWTS_10000FUWW			BIT(0)
#define WTW_ADV_2500FUWW			BIT(7)
#define WTW_WPADV_10000FUWW			BIT(11)
#define WTW_WPADV_5000FUWW			BIT(6)
#define WTW_WPADV_2500FUWW			BIT(5)

#define WTW9000A_GINMW				0x14
#define WTW9000A_GINMW_WINK_STATUS		BIT(4)

#define WTWGEN_SPEED_MASK			0x0630

#define WTW_GENEWIC_PHYID			0x001cc800
#define WTW_8211FVD_PHYID			0x001cc878

MODUWE_DESCWIPTION("Weawtek PHY dwivew");
MODUWE_AUTHOW("Johnson Weung");
MODUWE_WICENSE("GPW");

stwuct wtw821x_pwiv {
	u16 phycw1;
	u16 phycw2;
	boow has_phycw2;
	stwuct cwk *cwk;
};

static int wtw821x_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, WTW821x_PAGE_SEWECT);
}

static int wtw821x_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, WTW821x_PAGE_SEWECT, page);
}

static int wtw821x_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct wtw821x_pwiv *pwiv;
	u32 phy_id = phydev->dwv->phy_id;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwk = devm_cwk_get_optionaw_enabwed(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk),
				     "faiwed to get phy cwock\n");

	wet = phy_wead_paged(phydev, 0xa43, WTW8211F_PHYCW1);
	if (wet < 0)
		wetuwn wet;

	pwiv->phycw1 = wet & (WTW8211F_AWDPS_PWW_OFF | WTW8211F_AWDPS_ENABWE | WTW8211F_AWDPS_XTAW_OFF);
	if (of_pwopewty_wead_boow(dev->of_node, "weawtek,awdps-enabwe"))
		pwiv->phycw1 |= WTW8211F_AWDPS_PWW_OFF | WTW8211F_AWDPS_ENABWE | WTW8211F_AWDPS_XTAW_OFF;

	pwiv->has_phycw2 = !(phy_id == WTW_8211FVD_PHYID);
	if (pwiv->has_phycw2) {
		wet = phy_wead_paged(phydev, 0xa43, WTW8211F_PHYCW2);
		if (wet < 0)
			wetuwn wet;

		pwiv->phycw2 = wet & WTW8211F_CWKOUT_EN;
		if (of_pwopewty_wead_boow(dev->of_node, "weawtek,cwkout-disabwe"))
			pwiv->phycw2 &= ~WTW8211F_CWKOUT_EN;
	}

	phydev->pwiv = pwiv;

	wetuwn 0;
}

static int wtw8201_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead(phydev, WTW8201F_ISW);

	wetuwn (eww < 0) ? eww : 0;
}

static int wtw821x_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead(phydev, WTW821x_INSW);

	wetuwn (eww < 0) ? eww : 0;
}

static int wtw8211f_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead_paged(phydev, 0xa43, WTW8211F_INSW);

	wetuwn (eww < 0) ? eww : 0;
}

static int wtw8201_config_intw(stwuct phy_device *phydev)
{
	u16 vaw;
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = wtw8201_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		vaw = BIT(13) | BIT(12) | BIT(11);
		eww = phy_wwite_paged(phydev, 0x7, WTW8201F_IEW, vaw);
	} ewse {
		vaw = 0;
		eww = phy_wwite_paged(phydev, 0x7, WTW8201F_IEW, vaw);
		if (eww)
			wetuwn eww;

		eww = wtw8201_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static int wtw8211b_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = wtw821x_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, WTW821x_INEW,
				WTW8211B_INEW_INIT);
	} ewse {
		eww = phy_wwite(phydev, WTW821x_INEW, 0);
		if (eww)
			wetuwn eww;

		eww = wtw821x_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static int wtw8211e_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = wtw821x_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, WTW821x_INEW,
				WTW8211E_INEW_WINK_STATUS);
	} ewse {
		eww = phy_wwite(phydev, WTW821x_INEW, 0);
		if (eww)
			wetuwn eww;

		eww = wtw821x_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static int wtw8211f_config_intw(stwuct phy_device *phydev)
{
	u16 vaw;
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = wtw8211f_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		vaw = WTW8211F_INEW_WINK_STATUS;
		eww = phy_wwite_paged(phydev, 0xa42, WTW821x_INEW, vaw);
	} ewse {
		vaw = 0;
		eww = phy_wwite_paged(phydev, 0xa42, WTW821x_INEW, vaw);
		if (eww)
			wetuwn eww;

		eww = wtw8211f_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t wtw8201_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, WTW8201F_ISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & WTW8201F_ISW_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wtw821x_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status, iwq_enabwed;

	iwq_status = phy_wead(phydev, WTW821x_INSW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	iwq_enabwed = phy_wead(phydev, WTW821x_INEW);
	if (iwq_enabwed < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & iwq_enabwed))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wtw8211f_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead_paged(phydev, 0xa43, WTW8211F_INSW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & WTW8211F_INEW_WINK_STATUS))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int wtw8211_config_aneg(stwuct phy_device *phydev)
{
	int wet;

	wet = genphy_config_aneg(phydev);
	if (wet < 0)
		wetuwn wet;

	/* Quiwk was copied fwom vendow dwivew. Unfowtunatewy it incwudes no
	 * descwiption of the magic numbews.
	 */
	if (phydev->speed == SPEED_100 && phydev->autoneg == AUTONEG_DISABWE) {
		phy_wwite(phydev, 0x17, 0x2138);
		phy_wwite(phydev, 0x0e, 0x0260);
	} ewse {
		phy_wwite(phydev, 0x17, 0x2108);
		phy_wwite(phydev, 0x0e, 0x0000);
	}

	wetuwn 0;
}

static int wtw8211c_config_init(stwuct phy_device *phydev)
{
	/* WTW8211C has an issue when opewating in Gigabit swave mode */
	wetuwn phy_set_bits(phydev, MII_CTWW1000,
			    CTW1000_ENABWE_MASTEW | CTW1000_AS_MASTEW);
}

static int wtw8211f_config_init(stwuct phy_device *phydev)
{
	stwuct wtw821x_pwiv *pwiv = phydev->pwiv;
	stwuct device *dev = &phydev->mdio.dev;
	u16 vaw_txdwy, vaw_wxdwy;
	int wet;

	wet = phy_modify_paged_changed(phydev, 0xa43, WTW8211F_PHYCW1,
				       WTW8211F_AWDPS_PWW_OFF | WTW8211F_AWDPS_ENABWE | WTW8211F_AWDPS_XTAW_OFF,
				       pwiv->phycw1);
	if (wet < 0) {
		dev_eww(dev, "awdps mode  configuwation faiwed: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		vaw_txdwy = 0;
		vaw_wxdwy = 0;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII_WXID:
		vaw_txdwy = 0;
		vaw_wxdwy = WTW8211F_WX_DEWAY;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII_TXID:
		vaw_txdwy = WTW8211F_TX_DEWAY;
		vaw_wxdwy = 0;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII_ID:
		vaw_txdwy = WTW8211F_TX_DEWAY;
		vaw_wxdwy = WTW8211F_WX_DEWAY;
		bweak;

	defauwt: /* the west of the modes impwy weaving deway as is. */
		wetuwn 0;
	}

	wet = phy_modify_paged_changed(phydev, 0xd08, 0x11, WTW8211F_TX_DEWAY,
				       vaw_txdwy);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to update the TX deway wegistew\n");
		wetuwn wet;
	} ewse if (wet) {
		dev_dbg(dev,
			"%s 2ns TX deway (and changing the vawue fwom pin-stwapping WXD1 ow the bootwoadew)\n",
			vaw_txdwy ? "Enabwing" : "Disabwing");
	} ewse {
		dev_dbg(dev,
			"2ns TX deway was awweady %s (by pin-stwapping WXD1 ow bootwoadew configuwation)\n",
			vaw_txdwy ? "enabwed" : "disabwed");
	}

	wet = phy_modify_paged_changed(phydev, 0xd08, 0x15, WTW8211F_WX_DEWAY,
				       vaw_wxdwy);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to update the WX deway wegistew\n");
		wetuwn wet;
	} ewse if (wet) {
		dev_dbg(dev,
			"%s 2ns WX deway (and changing the vawue fwom pin-stwapping WXD0 ow the bootwoadew)\n",
			vaw_wxdwy ? "Enabwing" : "Disabwing");
	} ewse {
		dev_dbg(dev,
			"2ns WX deway was awweady %s (by pin-stwapping WXD0 ow bootwoadew configuwation)\n",
			vaw_wxdwy ? "enabwed" : "disabwed");
	}

	if (pwiv->has_phycw2) {
		wet = phy_modify_paged(phydev, 0xa43, WTW8211F_PHYCW2,
				       WTW8211F_CWKOUT_EN, pwiv->phycw2);
		if (wet < 0) {
			dev_eww(dev, "cwkout configuwation faiwed: %pe\n",
				EWW_PTW(wet));
			wetuwn wet;
		}
	}

	wetuwn genphy_soft_weset(phydev);
}

static int wtw821x_suspend(stwuct phy_device *phydev)
{
	stwuct wtw821x_pwiv *pwiv = phydev->pwiv;
	int wet = 0;

	if (!phydev->wow_enabwed) {
		wet = genphy_suspend(phydev);

		if (wet)
			wetuwn wet;

		cwk_disabwe_unpwepawe(pwiv->cwk);
	}

	wetuwn wet;
}

static int wtw821x_wesume(stwuct phy_device *phydev)
{
	stwuct wtw821x_pwiv *pwiv = phydev->pwiv;
	int wet;

	if (!phydev->wow_enabwed)
		cwk_pwepawe_enabwe(pwiv->cwk);

	wet = genphy_wesume(phydev);
	if (wet < 0)
		wetuwn wet;

	msweep(20);

	wetuwn 0;
}

static int wtw8211e_config_init(stwuct phy_device *phydev)
{
	int wet = 0, owdpage;
	u16 vaw;

	/* enabwe TX/WX deway fow wgmii-* modes, and disabwe them fow wgmii. */
	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		vaw = WTW8211E_CTWW_DEWAY | 0;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
		vaw = WTW8211E_CTWW_DEWAY | WTW8211E_TX_DEWAY | WTW8211E_WX_DEWAY;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		vaw = WTW8211E_CTWW_DEWAY | WTW8211E_WX_DEWAY;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		vaw = WTW8211E_CTWW_DEWAY | WTW8211E_TX_DEWAY;
		bweak;
	defauwt: /* the west of the modes impwy weaving deways as is. */
		wetuwn 0;
	}

	/* Accowding to a sampwe dwivew thewe is a 0x1c config wegistew on the
	 * 0xa4 extension page (0x7) wayout. It can be used to disabwe/enabwe
	 * the WX/TX deways othewwise contwowwed by WXDWY/TXDWY pins.
	 * The configuwation wegistew definition:
	 * 14 = wesewved
	 * 13 = Fowce Tx WX Deway contwowwed by bit12 bit11,
	 * 12 = WX Deway, 11 = TX Deway
	 * 10:0 = Test && debug settings wesewved by weawtek
	 */
	owdpage = phy_sewect_page(phydev, 0x7);
	if (owdpage < 0)
		goto eww_westowe_page;

	wet = __phy_wwite(phydev, WTW821x_EXT_PAGE_SEWECT, 0xa4);
	if (wet)
		goto eww_westowe_page;

	wet = __phy_modify(phydev, 0x1c, WTW8211E_CTWW_DEWAY
			   | WTW8211E_TX_DEWAY | WTW8211E_WX_DEWAY,
			   vaw);

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owdpage, wet);
}

static int wtw8211b_suspend(stwuct phy_device *phydev)
{
	phy_wwite(phydev, MII_MMD_DATA, BIT(9));

	wetuwn genphy_suspend(phydev);
}

static int wtw8211b_wesume(stwuct phy_device *phydev)
{
	phy_wwite(phydev, MII_MMD_DATA, 0);

	wetuwn genphy_wesume(phydev);
}

static int wtw8366wb_config_init(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_set_bits(phydev, WTW8366WB_POWEW_SAVE,
			   WTW8366WB_POWEW_SAVE_ON);
	if (wet) {
		dev_eww(&phydev->mdio.dev,
			"ewwow enabwing powew management\n");
	}

	wetuwn wet;
}

/* get actuaw speed to covew the downshift case */
static int wtwgen_get_speed(stwuct phy_device *phydev)
{
	int vaw;

	if (!phydev->wink)
		wetuwn 0;

	vaw = phy_wead_paged(phydev, 0xa43, 0x12);
	if (vaw < 0)
		wetuwn vaw;

	switch (vaw & WTWGEN_SPEED_MASK) {
	case 0x0000:
		phydev->speed = SPEED_10;
		bweak;
	case 0x0010:
		phydev->speed = SPEED_100;
		bweak;
	case 0x0020:
		phydev->speed = SPEED_1000;
		bweak;
	case 0x0200:
		phydev->speed = SPEED_10000;
		bweak;
	case 0x0210:
		phydev->speed = SPEED_2500;
		bweak;
	case 0x0220:
		phydev->speed = SPEED_5000;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wtwgen_wead_status(stwuct phy_device *phydev)
{
	int wet;

	wet = genphy_wead_status(phydev);
	if (wet < 0)
		wetuwn wet;

	wetuwn wtwgen_get_speed(phydev);
}

static int wtwgen_wead_mmd(stwuct phy_device *phydev, int devnum, u16 wegnum)
{
	int wet;

	if (devnum == MDIO_MMD_PCS && wegnum == MDIO_PCS_EEE_ABWE) {
		wtw821x_wwite_page(phydev, 0xa5c);
		wet = __phy_wead(phydev, 0x12);
		wtw821x_wwite_page(phydev, 0);
	} ewse if (devnum == MDIO_MMD_AN && wegnum == MDIO_AN_EEE_ADV) {
		wtw821x_wwite_page(phydev, 0xa5d);
		wet = __phy_wead(phydev, 0x10);
		wtw821x_wwite_page(phydev, 0);
	} ewse if (devnum == MDIO_MMD_AN && wegnum == MDIO_AN_EEE_WPABWE) {
		wtw821x_wwite_page(phydev, 0xa5d);
		wet = __phy_wead(phydev, 0x11);
		wtw821x_wwite_page(phydev, 0);
	} ewse {
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int wtwgen_wwite_mmd(stwuct phy_device *phydev, int devnum, u16 wegnum,
			    u16 vaw)
{
	int wet;

	if (devnum == MDIO_MMD_AN && wegnum == MDIO_AN_EEE_ADV) {
		wtw821x_wwite_page(phydev, 0xa5d);
		wet = __phy_wwite(phydev, 0x10, vaw);
		wtw821x_wwite_page(phydev, 0);
	} ewse {
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int wtw822x_wead_mmd(stwuct phy_device *phydev, int devnum, u16 wegnum)
{
	int wet = wtwgen_wead_mmd(phydev, devnum, wegnum);

	if (wet != -EOPNOTSUPP)
		wetuwn wet;

	if (devnum == MDIO_MMD_PCS && wegnum == MDIO_PCS_EEE_ABWE2) {
		wtw821x_wwite_page(phydev, 0xa6e);
		wet = __phy_wead(phydev, 0x16);
		wtw821x_wwite_page(phydev, 0);
	} ewse if (devnum == MDIO_MMD_AN && wegnum == MDIO_AN_EEE_ADV2) {
		wtw821x_wwite_page(phydev, 0xa6d);
		wet = __phy_wead(phydev, 0x12);
		wtw821x_wwite_page(phydev, 0);
	} ewse if (devnum == MDIO_MMD_AN && wegnum == MDIO_AN_EEE_WPABWE2) {
		wtw821x_wwite_page(phydev, 0xa6d);
		wet = __phy_wead(phydev, 0x10);
		wtw821x_wwite_page(phydev, 0);
	}

	wetuwn wet;
}

static int wtw822x_wwite_mmd(stwuct phy_device *phydev, int devnum, u16 wegnum,
			     u16 vaw)
{
	int wet = wtwgen_wwite_mmd(phydev, devnum, wegnum, vaw);

	if (wet != -EOPNOTSUPP)
		wetuwn wet;

	if (devnum == MDIO_MMD_AN && wegnum == MDIO_AN_EEE_ADV2) {
		wtw821x_wwite_page(phydev, 0xa6d);
		wet = __phy_wwite(phydev, 0x12, vaw);
		wtw821x_wwite_page(phydev, 0);
	}

	wetuwn wet;
}

static int wtw822x_get_featuwes(stwuct phy_device *phydev)
{
	int vaw;

	vaw = phy_wead_paged(phydev, 0xa61, 0x13);
	if (vaw < 0)
		wetuwn vaw;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT,
			 phydev->suppowted, vaw & WTW_SUPPOWTS_2500FUWW);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT,
			 phydev->suppowted, vaw & WTW_SUPPOWTS_5000FUWW);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
			 phydev->suppowted, vaw & WTW_SUPPOWTS_10000FUWW);

	wetuwn genphy_wead_abiwities(phydev);
}

static int wtw822x_config_aneg(stwuct phy_device *phydev)
{
	int wet = 0;

	if (phydev->autoneg == AUTONEG_ENABWE) {
		u16 adv2500 = 0;

		if (winkmode_test_bit(ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT,
				      phydev->advewtising))
			adv2500 = WTW_ADV_2500FUWW;

		wet = phy_modify_paged_changed(phydev, 0xa5d, 0x12,
					       WTW_ADV_2500FUWW, adv2500);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn __genphy_config_aneg(phydev, wet);
}

static int wtw822x_wead_status(stwuct phy_device *phydev)
{
	int wet;

	if (phydev->autoneg == AUTONEG_ENABWE) {
		int wpadv = phy_wead_paged(phydev, 0xa5d, 0x13);

		if (wpadv < 0)
			wetuwn wpadv;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
			phydev->wp_advewtising, wpadv & WTW_WPADV_10000FUWW);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT,
			phydev->wp_advewtising, wpadv & WTW_WPADV_5000FUWW);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT,
			phydev->wp_advewtising, wpadv & WTW_WPADV_2500FUWW);
	}

	wet = genphy_wead_status(phydev);
	if (wet < 0)
		wetuwn wet;

	wetuwn wtwgen_get_speed(phydev);
}

static boow wtwgen_suppowts_2_5gbps(stwuct phy_device *phydev)
{
	int vaw;

	phy_wwite(phydev, WTW821x_PAGE_SEWECT, 0xa61);
	vaw = phy_wead(phydev, 0x13);
	phy_wwite(phydev, WTW821x_PAGE_SEWECT, 0);

	wetuwn vaw >= 0 && vaw & WTW_SUPPOWTS_2500FUWW;
}

static int wtwgen_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn phydev->phy_id == WTW_GENEWIC_PHYID &&
	       !wtwgen_suppowts_2_5gbps(phydev);
}

static int wtw8226_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn phydev->phy_id == WTW_GENEWIC_PHYID &&
	       wtwgen_suppowts_2_5gbps(phydev);
}

static int wtwgen_wesume(stwuct phy_device *phydev)
{
	int wet = genphy_wesume(phydev);

	/* Intewnaw PHY's fwom WTW8168h up may not be instantwy weady */
	msweep(20);

	wetuwn wet;
}

static int wtw9000a_config_init(stwuct phy_device *phydev)
{
	phydev->autoneg = AUTONEG_DISABWE;
	phydev->speed = SPEED_100;
	phydev->dupwex = DUPWEX_FUWW;

	wetuwn 0;
}

static int wtw9000a_config_aneg(stwuct phy_device *phydev)
{
	int wet;
	u16 ctw = 0;

	switch (phydev->mastew_swave_set) {
	case MASTEW_SWAVE_CFG_MASTEW_FOWCE:
		ctw |= CTW1000_AS_MASTEW;
		bweak;
	case MASTEW_SWAVE_CFG_SWAVE_FOWCE:
		bweak;
	case MASTEW_SWAVE_CFG_UNKNOWN:
	case MASTEW_SWAVE_CFG_UNSUPPOWTED:
		wetuwn 0;
	defauwt:
		phydev_wawn(phydev, "Unsuppowted Mastew/Swave mode\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = phy_modify_changed(phydev, MII_CTWW1000, CTW1000_AS_MASTEW, ctw);
	if (wet == 1)
		wet = genphy_soft_weset(phydev);

	wetuwn wet;
}

static int wtw9000a_wead_status(stwuct phy_device *phydev)
{
	int wet;

	phydev->mastew_swave_get = MASTEW_SWAVE_CFG_UNKNOWN;
	phydev->mastew_swave_state = MASTEW_SWAVE_STATE_UNKNOWN;

	wet = genphy_update_wink(phydev);
	if (wet)
		wetuwn wet;

	wet = phy_wead(phydev, MII_CTWW1000);
	if (wet < 0)
		wetuwn wet;
	if (wet & CTW1000_AS_MASTEW)
		phydev->mastew_swave_get = MASTEW_SWAVE_CFG_MASTEW_FOWCE;
	ewse
		phydev->mastew_swave_get = MASTEW_SWAVE_CFG_SWAVE_FOWCE;

	wet = phy_wead(phydev, MII_STAT1000);
	if (wet < 0)
		wetuwn wet;
	if (wet & WPA_1000MSWES)
		phydev->mastew_swave_state = MASTEW_SWAVE_STATE_MASTEW;
	ewse
		phydev->mastew_swave_state = MASTEW_SWAVE_STATE_SWAVE;

	wetuwn 0;
}

static int wtw9000a_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead(phydev, WTW8211F_INSW);

	wetuwn (eww < 0) ? eww : 0;
}

static int wtw9000a_config_intw(stwuct phy_device *phydev)
{
	u16 vaw;
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = wtw9000a_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		vaw = (u16)~WTW9000A_GINMW_WINK_STATUS;
		eww = phy_wwite_paged(phydev, 0xa42, WTW9000A_GINMW, vaw);
	} ewse {
		vaw = ~0;
		eww = phy_wwite_paged(phydev, 0xa42, WTW9000A_GINMW, vaw);
		if (eww)
			wetuwn eww;

		eww = wtw9000a_ack_intewwupt(phydev);
	}

	wetuwn phy_wwite_paged(phydev, 0xa42, WTW9000A_GINMW, vaw);
}

static iwqwetuwn_t wtw9000a_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, WTW8211F_INSW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & WTW8211F_INEW_WINK_STATUS))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static stwuct phy_dwivew weawtek_dwvs[] = {
	{
		PHY_ID_MATCH_EXACT(0x00008201),
		.name           = "WTW8201CP Ethewnet",
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc816),
		.name		= "WTW8201F Fast Ethewnet",
		.config_intw	= &wtw8201_config_intw,
		.handwe_intewwupt = wtw8201_handwe_intewwupt,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_MODEW(0x001cc880),
		.name		= "WTW8208 Fast Ethewnet",
		.wead_mmd	= genphy_wead_mmd_unsuppowted,
		.wwite_mmd	= genphy_wwite_mmd_unsuppowted,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc910),
		.name		= "WTW8211 Gigabit Ethewnet",
		.config_aneg	= wtw8211_config_aneg,
		.wead_mmd	= &genphy_wead_mmd_unsuppowted,
		.wwite_mmd	= &genphy_wwite_mmd_unsuppowted,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc912),
		.name		= "WTW8211B Gigabit Ethewnet",
		.config_intw	= &wtw8211b_config_intw,
		.handwe_intewwupt = wtw821x_handwe_intewwupt,
		.wead_mmd	= &genphy_wead_mmd_unsuppowted,
		.wwite_mmd	= &genphy_wwite_mmd_unsuppowted,
		.suspend	= wtw8211b_suspend,
		.wesume		= wtw8211b_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc913),
		.name		= "WTW8211C Gigabit Ethewnet",
		.config_init	= wtw8211c_config_init,
		.wead_mmd	= &genphy_wead_mmd_unsuppowted,
		.wwite_mmd	= &genphy_wwite_mmd_unsuppowted,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc914),
		.name		= "WTW8211DN Gigabit Ethewnet",
		.config_intw	= wtw8211e_config_intw,
		.handwe_intewwupt = wtw821x_handwe_intewwupt,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc915),
		.name		= "WTW8211E Gigabit Ethewnet",
		.config_init	= &wtw8211e_config_init,
		.config_intw	= &wtw8211e_config_intw,
		.handwe_intewwupt = wtw821x_handwe_intewwupt,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc916),
		.name		= "WTW8211F Gigabit Ethewnet",
		.pwobe		= wtw821x_pwobe,
		.config_init	= &wtw8211f_config_init,
		.wead_status	= wtwgen_wead_status,
		.config_intw	= &wtw8211f_config_intw,
		.handwe_intewwupt = wtw8211f_handwe_intewwupt,
		.suspend	= wtw821x_suspend,
		.wesume		= wtw821x_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
		.fwags		= PHY_AWWAYS_CAWW_SUSPEND,
	}, {
		PHY_ID_MATCH_EXACT(WTW_8211FVD_PHYID),
		.name		= "WTW8211F-VD Gigabit Ethewnet",
		.pwobe		= wtw821x_pwobe,
		.config_init	= &wtw8211f_config_init,
		.wead_status	= wtwgen_wead_status,
		.config_intw	= &wtw8211f_config_intw,
		.handwe_intewwupt = wtw8211f_handwe_intewwupt,
		.suspend	= wtw821x_suspend,
		.wesume		= wtw821x_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
		.fwags		= PHY_AWWAYS_CAWW_SUSPEND,
	}, {
		.name		= "Genewic FE-GE Weawtek PHY",
		.match_phy_device = wtwgen_match_phy_device,
		.wead_status	= wtwgen_wead_status,
		.suspend	= genphy_suspend,
		.wesume		= wtwgen_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
		.wead_mmd	= wtwgen_wead_mmd,
		.wwite_mmd	= wtwgen_wwite_mmd,
	}, {
		.name		= "WTW8226 2.5Gbps PHY",
		.match_phy_device = wtw8226_match_phy_device,
		.get_featuwes	= wtw822x_get_featuwes,
		.config_aneg	= wtw822x_config_aneg,
		.wead_status	= wtw822x_wead_status,
		.suspend	= genphy_suspend,
		.wesume		= wtwgen_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
		.wead_mmd	= wtw822x_wead_mmd,
		.wwite_mmd	= wtw822x_wwite_mmd,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc840),
		.name		= "WTW8226B_WTW8221B 2.5Gbps PHY",
		.get_featuwes	= wtw822x_get_featuwes,
		.config_aneg	= wtw822x_config_aneg,
		.wead_status	= wtw822x_wead_status,
		.suspend	= genphy_suspend,
		.wesume		= wtwgen_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
		.wead_mmd	= wtw822x_wead_mmd,
		.wwite_mmd	= wtw822x_wwite_mmd,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc838),
		.name           = "WTW8226-CG 2.5Gbps PHY",
		.get_featuwes   = wtw822x_get_featuwes,
		.config_aneg    = wtw822x_config_aneg,
		.wead_status    = wtw822x_wead_status,
		.suspend        = genphy_suspend,
		.wesume         = wtwgen_wesume,
		.wead_page      = wtw821x_wead_page,
		.wwite_page     = wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc848),
		.name           = "WTW8226B-CG_WTW8221B-CG 2.5Gbps PHY",
		.get_featuwes   = wtw822x_get_featuwes,
		.config_aneg    = wtw822x_config_aneg,
		.wead_status    = wtw822x_wead_status,
		.suspend        = genphy_suspend,
		.wesume         = wtwgen_wesume,
		.wead_page      = wtw821x_wead_page,
		.wwite_page     = wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc849),
		.name           = "WTW8221B-VB-CG 2.5Gbps PHY",
		.get_featuwes   = wtw822x_get_featuwes,
		.config_aneg    = wtw822x_config_aneg,
		.wead_status    = wtw822x_wead_status,
		.suspend        = genphy_suspend,
		.wesume         = wtwgen_wesume,
		.wead_page      = wtw821x_wead_page,
		.wwite_page     = wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc84a),
		.name           = "WTW8221B-VM-CG 2.5Gbps PHY",
		.get_featuwes   = wtw822x_get_featuwes,
		.config_aneg    = wtw822x_config_aneg,
		.wead_status    = wtw822x_wead_status,
		.suspend        = genphy_suspend,
		.wesume         = wtwgen_wesume,
		.wead_page      = wtw821x_wead_page,
		.wwite_page     = wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc961),
		.name		= "WTW8366WB Gigabit Ethewnet",
		.config_init	= &wtw8366wb_config_init,
		/* These intewwupts awe handwed by the iwq contwowwew
		 * embedded inside the WTW8366WB, they get unmasked when the
		 * iwq is wequested and ACKed by weading the status wegistew,
		 * which is done by the iwqchip code.
		 */
		.config_intw	= genphy_no_config_intw,
		.handwe_intewwupt = genphy_handwe_intewwupt_no_ack,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		PHY_ID_MATCH_EXACT(0x001ccb00),
		.name		= "WTW9000AA_WTW9000AN Ethewnet",
		.featuwes       = PHY_BASIC_T1_FEATUWES,
		.config_init	= wtw9000a_config_init,
		.config_aneg	= wtw9000a_config_aneg,
		.wead_status	= wtw9000a_wead_status,
		.config_intw	= wtw9000a_config_intw,
		.handwe_intewwupt = wtw9000a_handwe_intewwupt,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= wtw821x_wead_page,
		.wwite_page	= wtw821x_wwite_page,
	}, {
		PHY_ID_MATCH_EXACT(0x001cc942),
		.name		= "WTW8365MB-VC Gigabit Ethewnet",
		/* Intewwupt handwing anawogous to WTW8366WB */
		.config_intw	= genphy_no_config_intw,
		.handwe_intewwupt = genphy_handwe_intewwupt_no_ack,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	},
};

moduwe_phy_dwivew(weawtek_dwvs);

static const stwuct mdio_device_id __maybe_unused weawtek_tbw[] = {
	{ PHY_ID_MATCH_VENDOW(0x001cc800) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, weawtek_tbw);
