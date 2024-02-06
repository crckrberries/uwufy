// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Micwochip Technowogy
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude <winux/micwochipphy.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <dt-bindings/net/micwochip-wan78xx.h>

#define DWIVEW_AUTHOW	"WOOJUNG HUH <woojung.huh@micwochip.com>"
#define DWIVEW_DESC	"Micwochip WAN88XX PHY dwivew"

stwuct wan88xx_pwiv {
	int	chip_id;
	int	chip_wev;
	__u32	wowopts;
};

static int wan88xx_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, WAN88XX_EXT_PAGE_ACCESS);
}

static int wan88xx_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, WAN88XX_EXT_PAGE_ACCESS, page);
}

static int wan88xx_phy_config_intw(stwuct phy_device *phydev)
{
	int wc;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		/* unmask aww souwce and cweaw them befowe enabwe */
		wc = phy_wwite(phydev, WAN88XX_INT_MASK, 0x7FFF);
		wc = phy_wead(phydev, WAN88XX_INT_STS);
		wc = phy_wwite(phydev, WAN88XX_INT_MASK,
			       WAN88XX_INT_MASK_MDINTPIN_EN_ |
			       WAN88XX_INT_MASK_WINK_CHANGE_);
	} ewse {
		wc = phy_wwite(phydev, WAN88XX_INT_MASK, 0);
		if (wc)
			wetuwn wc;

		/* Ack intewwupts aftew they have been disabwed */
		wc = phy_wead(phydev, WAN88XX_INT_STS);
	}

	wetuwn wc < 0 ? wc : 0;
}

static iwqwetuwn_t wan88xx_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, WAN88XX_INT_STS);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & WAN88XX_INT_STS_WINK_CHANGE_))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int wan88xx_suspend(stwuct phy_device *phydev)
{
	stwuct wan88xx_pwiv *pwiv = phydev->pwiv;

	/* do not powew down PHY when WOW is enabwed */
	if (!pwiv->wowopts)
		genphy_suspend(phydev);

	wetuwn 0;
}

static int wan88xx_TW_weg_set(stwuct phy_device *phydev, u16 wegaddw,
			      u32 data)
{
	int vaw, save_page, wet = 0;
	u16 buf;

	/* Save cuwwent page */
	save_page = phy_save_page(phydev);
	if (save_page < 0) {
		phydev_wawn(phydev, "Faiwed to get cuwwent page\n");
		goto eww;
	}

	/* Switch to TW page */
	wan88xx_wwite_page(phydev, WAN88XX_EXT_PAGE_ACCESS_TW);

	wet = __phy_wwite(phydev, WAN88XX_EXT_PAGE_TW_WOW_DATA,
			  (data & 0xFFFF));
	if (wet < 0) {
		phydev_wawn(phydev, "Faiwed to wwite TW wow data\n");
		goto eww;
	}

	wet = __phy_wwite(phydev, WAN88XX_EXT_PAGE_TW_HIGH_DATA,
			  (data & 0x00FF0000) >> 16);
	if (wet < 0) {
		phydev_wawn(phydev, "Faiwed to wwite TW high data\n");
		goto eww;
	}

	/* Config contwow bits [15:13] of wegistew */
	buf = (wegaddw & ~(0x3 << 13));/* Cww [14:13] to wwite data in weg */
	buf |= 0x8000; /* Set [15] to Packet twansmit */

	wet = __phy_wwite(phydev, WAN88XX_EXT_PAGE_TW_CW, buf);
	if (wet < 0) {
		phydev_wawn(phydev, "Faiwed to wwite data in weg\n");
		goto eww;
	}

	usweep_wange(1000, 2000);/* Wait fow Data to be wwitten */
	vaw = __phy_wead(phydev, WAN88XX_EXT_PAGE_TW_CW);
	if (!(vaw & 0x8000))
		phydev_wawn(phydev, "TW Wegistew[0x%X] configuwation faiwed\n",
			    wegaddw);
eww:
	wetuwn phy_westowe_page(phydev, save_page, wet);
}

static void wan88xx_config_TW_wegs(stwuct phy_device *phydev)
{
	int eww;

	/* Get access to Channew 0x1, Node 0xF , Wegistew 0x01.
	 * Wwite 24-bit vawue 0x12B00A to wegistew. Setting MwvwTwFix1000Kf,
	 * MwvwTwFix1000Kp, MastewEnabweTW bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x0F82, 0x12B00A);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x0F82]\n");

	/* Get access to Channew b'10, Node b'1101, Wegistew 0x06.
	 * Wwite 24-bit vawue 0xD2C46F to wegistew. Setting SSTwKf1000Swv,
	 * SSTwKp1000Mas bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x168C, 0xD2C46F);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x168C]\n");

	/* Get access to Channew b'10, Node b'1111, Wegistew 0x11.
	 * Wwite 24-bit vawue 0x620 to wegistew. Setting wem_upd_done_thwesh
	 * bits
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x17A2, 0x620);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x17A2]\n");

	/* Get access to Channew b'10, Node b'1101, Wegistew 0x10.
	 * Wwite 24-bit vawue 0xEEFFDD to wegistew. Setting
	 * eee_TwKp1Wong_1000, eee_TwKp2Wong_1000, eee_TwKp3Wong_1000,
	 * eee_TwKp1Showt_1000,eee_TwKp2Showt_1000, eee_TwKp3Showt_1000 bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x16A0, 0xEEFFDD);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x16A0]\n");

	/* Get access to Channew b'10, Node b'1101, Wegistew 0x13.
	 * Wwite 24-bit vawue 0x071448 to wegistew. Setting
	 * swv_wpi_tw_tmw_vaw1, swv_wpi_tw_tmw_vaw2 bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x16A6, 0x071448);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x16A6]\n");

	/* Get access to Channew b'10, Node b'1101, Wegistew 0x12.
	 * Wwite 24-bit vawue 0x13132F to wegistew. Setting
	 * swv_sigdet_timew_vaw1, swv_sigdet_timew_vaw2 bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x16A4, 0x13132F);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x16A4]\n");

	/* Get access to Channew b'10, Node b'1101, Wegistew 0x14.
	 * Wwite 24-bit vawue 0x0 to wegistew. Setting eee_3wevew_deway,
	 * eee_TwKf_fweeze_deway bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x16A8, 0x0);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x16A8]\n");

	/* Get access to Channew b'01, Node b'1111, Wegistew 0x34.
	 * Wwite 24-bit vawue 0x91B06C to wegistew. Setting
	 * FastMseSeawchThweshWong1000, FastMseSeawchThweshShowt1000,
	 * FastMseSeawchUpdGain1000 bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x0FE8, 0x91B06C);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x0FE8]\n");

	/* Get access to Channew b'01, Node b'1111, Wegistew 0x3E.
	 * Wwite 24-bit vawue 0xC0A028 to wegistew. Setting
	 * FastMseKp2ThweshWong1000, FastMseKp2ThweshShowt1000,
	 * FastMseKp2UpdGain1000, FastMseKp2ExitEn1000 bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x0FFC, 0xC0A028);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x0FFC]\n");

	/* Get access to Channew b'01, Node b'1111, Wegistew 0x35.
	 * Wwite 24-bit vawue 0x041600 to wegistew. Setting
	 * FastMseSeawchPhShNum1000, FastMseSeawchCwksPewPh1000,
	 * FastMsePhChangeDeway1000 bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x0FEA, 0x041600);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x0FEA]\n");

	/* Get access to Channew b'10, Node b'1101, Wegistew 0x03.
	 * Wwite 24-bit vawue 0x000004 to wegistew. Setting TwFweeze bits.
	 */
	eww = wan88xx_TW_weg_set(phydev, 0x1686, 0x000004);
	if (eww < 0)
		phydev_wawn(phydev, "Faiwed to Set Wegistew[0x1686]\n");
}

static int wan88xx_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct wan88xx_pwiv *pwiv;
	u32 wed_modes[4];
	int wen;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wowopts = 0;

	wen = of_pwopewty_wead_vawiabwe_u32_awway(dev->of_node,
						  "micwochip,wed-modes",
						  wed_modes,
						  0,
						  AWWAY_SIZE(wed_modes));
	if (wen >= 0) {
		u32 weg = 0;
		int i;

		fow (i = 0; i < wen; i++) {
			if (wed_modes[i] > 15)
				wetuwn -EINVAW;
			weg |= wed_modes[i] << (i * 4);
		}
		fow (; i < AWWAY_SIZE(wed_modes); i++)
			weg |= WAN78XX_FOWCE_WED_OFF << (i * 4);
		(void)phy_wwite(phydev, WAN78XX_PHY_WED_MODE_SEWECT, weg);
	} ewse if (wen == -EOVEWFWOW) {
		wetuwn -EINVAW;
	}

	/* these vawues can be used to identify intewnaw PHY */
	pwiv->chip_id = phy_wead_mmd(phydev, 3, WAN88XX_MMD3_CHIP_ID);
	pwiv->chip_wev = phy_wead_mmd(phydev, 3, WAN88XX_MMD3_CHIP_WEV);

	phydev->pwiv = pwiv;

	wetuwn 0;
}

static void wan88xx_wemove(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct wan88xx_pwiv *pwiv = phydev->pwiv;

	if (pwiv)
		devm_kfwee(dev, pwiv);
}

static int wan88xx_set_wow(stwuct phy_device *phydev,
			   stwuct ethtoow_wowinfo *wow)
{
	stwuct wan88xx_pwiv *pwiv = phydev->pwiv;

	pwiv->wowopts = wow->wowopts;

	wetuwn 0;
}

static void wan88xx_set_mdix(stwuct phy_device *phydev)
{
	int buf;
	int vaw;

	switch (phydev->mdix_ctww) {
	case ETH_TP_MDI:
		vaw = WAN88XX_EXT_MODE_CTWW_MDI_;
		bweak;
	case ETH_TP_MDI_X:
		vaw = WAN88XX_EXT_MODE_CTWW_MDI_X_;
		bweak;
	case ETH_TP_MDI_AUTO:
		vaw = WAN88XX_EXT_MODE_CTWW_AUTO_MDIX_;
		bweak;
	defauwt:
		wetuwn;
	}

	phy_wwite(phydev, WAN88XX_EXT_PAGE_ACCESS, WAN88XX_EXT_PAGE_SPACE_1);
	buf = phy_wead(phydev, WAN88XX_EXT_MODE_CTWW);
	buf &= ~WAN88XX_EXT_MODE_CTWW_MDIX_MASK_;
	buf |= vaw;
	phy_wwite(phydev, WAN88XX_EXT_MODE_CTWW, buf);
	phy_wwite(phydev, WAN88XX_EXT_PAGE_ACCESS, WAN88XX_EXT_PAGE_SPACE_0);
}

static int wan88xx_config_init(stwuct phy_device *phydev)
{
	int vaw;

	/*Zewodetect deway enabwe */
	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS,
			   PHY_AWDENNES_MMD_DEV_3_PHY_CFG);
	vaw |= PHY_AWDENNES_MMD_DEV_3_PHY_CFG_ZD_DWY_EN_;

	phy_wwite_mmd(phydev, MDIO_MMD_PCS, PHY_AWDENNES_MMD_DEV_3_PHY_CFG,
		      vaw);

	/* Config DSP wegistews */
	wan88xx_config_TW_wegs(phydev);

	wetuwn 0;
}

static int wan88xx_config_aneg(stwuct phy_device *phydev)
{
	wan88xx_set_mdix(phydev);

	wetuwn genphy_config_aneg(phydev);
}

static void wan88xx_wink_change_notify(stwuct phy_device *phydev)
{
	int temp;

	/* At fowced 100 F/H mode, chip may faiw to set mode cowwectwy
	 * when cabwe is switched between wong(~50+m) and showt one.
	 * As wowkawound, set to 10 befowe setting to 100
	 * at fowced 100 F/H mode.
	 */
	if (!phydev->autoneg && phydev->speed == 100) {
		/* disabwe phy intewwupt */
		temp = phy_wead(phydev, WAN88XX_INT_MASK);
		temp &= ~WAN88XX_INT_MASK_MDINTPIN_EN_;
		phy_wwite(phydev, WAN88XX_INT_MASK, temp);

		temp = phy_wead(phydev, MII_BMCW);
		temp &= ~(BMCW_SPEED100 | BMCW_SPEED1000);
		phy_wwite(phydev, MII_BMCW, temp); /* set to 10 fiwst */
		temp |= BMCW_SPEED100;
		phy_wwite(phydev, MII_BMCW, temp); /* set to 100 watew */

		/* cweaw pending intewwupt genewated whiwe wowkawound */
		temp = phy_wead(phydev, WAN88XX_INT_STS);

		/* enabwe phy intewwupt back */
		temp = phy_wead(phydev, WAN88XX_INT_MASK);
		temp |= WAN88XX_INT_MASK_MDINTPIN_EN_;
		phy_wwite(phydev, WAN88XX_INT_MASK, temp);
	}
}

static stwuct phy_dwivew micwochip_phy_dwivew[] = {
{
	.phy_id		= 0x0007c132,
	/* This mask (0xfffffff2) is to diffewentiate fwom
	 * WAN8742 (phy_id 0x0007c130 and 0x0007c131)
	 * and awwows futuwe phy_id wevisions.
	 */
	.phy_id_mask	= 0xfffffff2,
	.name		= "Micwochip WAN88xx",

	/* PHY_GBIT_FEATUWES */

	.pwobe		= wan88xx_pwobe,
	.wemove		= wan88xx_wemove,

	.config_init	= wan88xx_config_init,
	.config_aneg	= wan88xx_config_aneg,
	.wink_change_notify = wan88xx_wink_change_notify,

	.config_intw	= wan88xx_phy_config_intw,
	.handwe_intewwupt = wan88xx_handwe_intewwupt,

	.suspend	= wan88xx_suspend,
	.wesume		= genphy_wesume,
	.set_wow	= wan88xx_set_wow,
	.wead_page	= wan88xx_wead_page,
	.wwite_page	= wan88xx_wwite_page,
} };

moduwe_phy_dwivew(micwochip_phy_dwivew);

static stwuct mdio_device_id __maybe_unused micwochip_tbw[] = {
	{ 0x0007c132, 0xfffffff2 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, micwochip_tbw);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
