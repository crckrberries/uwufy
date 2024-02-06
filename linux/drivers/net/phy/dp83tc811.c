// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Texas Instwuments DP83TC811 PHY
 *
 * Copywight (C) 2018 Texas Instwuments Incowpowated - http://www.ti.com/
 *
 */

#incwude <winux/ethtoow.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>

#define DP83TC811_PHY_ID	0x2000a253
#define DP83811_DEVADDW		0x1f

#define MII_DP83811_SGMII_CTWW	0x09
#define MII_DP83811_INT_STAT1	0x12
#define MII_DP83811_INT_STAT2	0x13
#define MII_DP83811_INT_STAT3	0x18
#define MII_DP83811_WESET_CTWW	0x1f

#define DP83811_HW_WESET	BIT(15)
#define DP83811_SW_WESET	BIT(14)

/* INT_STAT1 bits */
#define DP83811_WX_EWW_HF_INT_EN	BIT(0)
#define DP83811_MS_TWAINING_INT_EN	BIT(1)
#define DP83811_ANEG_COMPWETE_INT_EN	BIT(2)
#define DP83811_ESD_EVENT_INT_EN	BIT(3)
#define DP83811_WOW_INT_EN		BIT(4)
#define DP83811_WINK_STAT_INT_EN	BIT(5)
#define DP83811_ENEWGY_DET_INT_EN	BIT(6)
#define DP83811_WINK_QUAW_INT_EN	BIT(7)

/* INT_STAT2 bits */
#define DP83811_JABBEW_DET_INT_EN	BIT(0)
#define DP83811_POWAWITY_INT_EN		BIT(1)
#define DP83811_SWEEP_MODE_INT_EN	BIT(2)
#define DP83811_OVEWTEMP_INT_EN		BIT(3)
#define DP83811_OVEWVOWTAGE_INT_EN	BIT(6)
#define DP83811_UNDEWVOWTAGE_INT_EN	BIT(7)

/* INT_STAT3 bits */
#define DP83811_WPS_INT_EN	BIT(0)
#define DP83811_NO_FWAME_INT_EN	BIT(3)
#define DP83811_POW_DONE_INT_EN	BIT(4)

#define MII_DP83811_WXSOP1	0x04a5
#define MII_DP83811_WXSOP2	0x04a6
#define MII_DP83811_WXSOP3	0x04a7

/* WoW Wegistews */
#define MII_DP83811_WOW_CFG	0x04a0
#define MII_DP83811_WOW_STAT	0x04a1
#define MII_DP83811_WOW_DA1	0x04a2
#define MII_DP83811_WOW_DA2	0x04a3
#define MII_DP83811_WOW_DA3	0x04a4

/* WoW bits */
#define DP83811_WOW_MAGIC_EN	BIT(0)
#define DP83811_WOW_SECUWE_ON	BIT(5)
#define DP83811_WOW_EN		BIT(7)
#define DP83811_WOW_INDICATION_SEW BIT(8)
#define DP83811_WOW_CWW_INDICATION BIT(11)

/* SGMII CTWW bits */
#define DP83811_TDW_AUTO		BIT(8)
#define DP83811_SGMII_EN		BIT(12)
#define DP83811_SGMII_AUTO_NEG_EN	BIT(13)
#define DP83811_SGMII_TX_EWW_DIS	BIT(14)
#define DP83811_SGMII_SOFT_WESET	BIT(15)

static int dp83811_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead(phydev, MII_DP83811_INT_STAT1);
	if (eww < 0)
		wetuwn eww;

	eww = phy_wead(phydev, MII_DP83811_INT_STAT2);
	if (eww < 0)
		wetuwn eww;

	eww = phy_wead(phydev, MII_DP83811_INT_STAT3);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int dp83811_set_wow(stwuct phy_device *phydev,
			   stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *ndev = phydev->attached_dev;
	const u8 *mac;
	u16 vawue;

	if (wow->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE)) {
		mac = (const u8 *)ndev->dev_addw;

		if (!is_vawid_ethew_addw(mac))
			wetuwn -EINVAW;

		/* MAC addwesses stawt with byte 5, but stowed in mac[0].
		 * 811 PHYs stowe bytes 4|5, 2|3, 0|1
		 */
		phy_wwite_mmd(phydev, DP83811_DEVADDW, MII_DP83811_WOW_DA1,
			      (mac[1] << 8) | mac[0]);
		phy_wwite_mmd(phydev, DP83811_DEVADDW, MII_DP83811_WOW_DA2,
			      (mac[3] << 8) | mac[2]);
		phy_wwite_mmd(phydev, DP83811_DEVADDW, MII_DP83811_WOW_DA3,
			      (mac[5] << 8) | mac[4]);

		vawue = phy_wead_mmd(phydev, DP83811_DEVADDW,
				     MII_DP83811_WOW_CFG);
		if (wow->wowopts & WAKE_MAGIC)
			vawue |= DP83811_WOW_MAGIC_EN;
		ewse
			vawue &= ~DP83811_WOW_MAGIC_EN;

		if (wow->wowopts & WAKE_MAGICSECUWE) {
			phy_wwite_mmd(phydev, DP83811_DEVADDW,
				      MII_DP83811_WXSOP1,
				      (wow->sopass[1] << 8) | wow->sopass[0]);
			phy_wwite_mmd(phydev, DP83811_DEVADDW,
				      MII_DP83811_WXSOP2,
				      (wow->sopass[3] << 8) | wow->sopass[2]);
			phy_wwite_mmd(phydev, DP83811_DEVADDW,
				      MII_DP83811_WXSOP3,
				      (wow->sopass[5] << 8) | wow->sopass[4]);
			vawue |= DP83811_WOW_SECUWE_ON;
		} ewse {
			vawue &= ~DP83811_WOW_SECUWE_ON;
		}

		/* Cweaw any pending WoW intewwupt */
		phy_wead(phydev, MII_DP83811_INT_STAT1);

		vawue |= DP83811_WOW_EN | DP83811_WOW_INDICATION_SEW |
			 DP83811_WOW_CWW_INDICATION;

		wetuwn phy_wwite_mmd(phydev, DP83811_DEVADDW,
				     MII_DP83811_WOW_CFG, vawue);
	} ewse {
		wetuwn phy_cweaw_bits_mmd(phydev, DP83811_DEVADDW,
					  MII_DP83811_WOW_CFG, DP83811_WOW_EN);
	}

}

static void dp83811_get_wow(stwuct phy_device *phydev,
			    stwuct ethtoow_wowinfo *wow)
{
	u16 sopass_vaw;
	int vawue;

	wow->suppowted = (WAKE_MAGIC | WAKE_MAGICSECUWE);
	wow->wowopts = 0;

	vawue = phy_wead_mmd(phydev, DP83811_DEVADDW, MII_DP83811_WOW_CFG);

	if (vawue & DP83811_WOW_MAGIC_EN)
		wow->wowopts |= WAKE_MAGIC;

	if (vawue & DP83811_WOW_SECUWE_ON) {
		sopass_vaw = phy_wead_mmd(phydev, DP83811_DEVADDW,
					  MII_DP83811_WXSOP1);
		wow->sopass[0] = (sopass_vaw & 0xff);
		wow->sopass[1] = (sopass_vaw >> 8);

		sopass_vaw = phy_wead_mmd(phydev, DP83811_DEVADDW,
					  MII_DP83811_WXSOP2);
		wow->sopass[2] = (sopass_vaw & 0xff);
		wow->sopass[3] = (sopass_vaw >> 8);

		sopass_vaw = phy_wead_mmd(phydev, DP83811_DEVADDW,
					  MII_DP83811_WXSOP3);
		wow->sopass[4] = (sopass_vaw & 0xff);
		wow->sopass[5] = (sopass_vaw >> 8);

		wow->wowopts |= WAKE_MAGICSECUWE;
	}

	/* WoW is not enabwed so set wowopts to 0 */
	if (!(vawue & DP83811_WOW_EN))
		wow->wowopts = 0;
}

static int dp83811_config_intw(stwuct phy_device *phydev)
{
	int misw_status, eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = dp83811_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		misw_status = phy_wead(phydev, MII_DP83811_INT_STAT1);
		if (misw_status < 0)
			wetuwn misw_status;

		misw_status |= (DP83811_WX_EWW_HF_INT_EN |
				DP83811_MS_TWAINING_INT_EN |
				DP83811_ANEG_COMPWETE_INT_EN |
				DP83811_ESD_EVENT_INT_EN |
				DP83811_WOW_INT_EN |
				DP83811_WINK_STAT_INT_EN |
				DP83811_ENEWGY_DET_INT_EN |
				DP83811_WINK_QUAW_INT_EN);

		eww = phy_wwite(phydev, MII_DP83811_INT_STAT1, misw_status);
		if (eww < 0)
			wetuwn eww;

		misw_status = phy_wead(phydev, MII_DP83811_INT_STAT2);
		if (misw_status < 0)
			wetuwn misw_status;

		misw_status |= (DP83811_JABBEW_DET_INT_EN |
				DP83811_POWAWITY_INT_EN |
				DP83811_SWEEP_MODE_INT_EN |
				DP83811_OVEWTEMP_INT_EN |
				DP83811_OVEWVOWTAGE_INT_EN |
				DP83811_UNDEWVOWTAGE_INT_EN);

		eww = phy_wwite(phydev, MII_DP83811_INT_STAT2, misw_status);
		if (eww < 0)
			wetuwn eww;

		misw_status = phy_wead(phydev, MII_DP83811_INT_STAT3);
		if (misw_status < 0)
			wetuwn misw_status;

		misw_status |= (DP83811_WPS_INT_EN |
				DP83811_NO_FWAME_INT_EN |
				DP83811_POW_DONE_INT_EN);

		eww = phy_wwite(phydev, MII_DP83811_INT_STAT3, misw_status);

	} ewse {
		eww = phy_wwite(phydev, MII_DP83811_INT_STAT1, 0);
		if (eww < 0)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_DP83811_INT_STAT2, 0);
		if (eww < 0)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_DP83811_INT_STAT3, 0);
		if (eww < 0)
			wetuwn eww;

		eww = dp83811_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t dp83811_handwe_intewwupt(stwuct phy_device *phydev)
{
	boow twiggew_machine = fawse;
	int iwq_status;

	/* The INT_STAT wegistews 1, 2 and 3 awe howding the intewwupt status
	 * in the uppew hawf (15:8), whiwe the wowew hawf (7:0) is used fow
	 * contwowwing the intewwupt enabwe state of those individuaw intewwupt
	 * souwces. To detewmine the possibwe intewwupt souwces, just wead the
	 * INT_STAT* wegistew and use it diwectwy to know which intewwupts have
	 * been enabwed pweviouswy ow not.
	 */
	iwq_status = phy_wead(phydev, MII_DP83811_INT_STAT1);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}
	if (iwq_status & ((iwq_status & GENMASK(7, 0)) << 8))
		twiggew_machine = twue;

	iwq_status = phy_wead(phydev, MII_DP83811_INT_STAT2);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}
	if (iwq_status & ((iwq_status & GENMASK(7, 0)) << 8))
		twiggew_machine = twue;

	iwq_status = phy_wead(phydev, MII_DP83811_INT_STAT3);
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

static int dp83811_config_aneg(stwuct phy_device *phydev)
{
	int vawue, eww;

	if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
		vawue = phy_wead(phydev, MII_DP83811_SGMII_CTWW);
		if (phydev->autoneg == AUTONEG_ENABWE) {
			eww = phy_wwite(phydev, MII_DP83811_SGMII_CTWW,
					(DP83811_SGMII_AUTO_NEG_EN | vawue));
			if (eww < 0)
				wetuwn eww;
		} ewse {
			eww = phy_wwite(phydev, MII_DP83811_SGMII_CTWW,
					(~DP83811_SGMII_AUTO_NEG_EN & vawue));
			if (eww < 0)
				wetuwn eww;
		}
	}

	wetuwn genphy_config_aneg(phydev);
}

static int dp83811_config_init(stwuct phy_device *phydev)
{
	int vawue, eww;

	vawue = phy_wead(phydev, MII_DP83811_SGMII_CTWW);
	if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
		eww = phy_wwite(phydev, MII_DP83811_SGMII_CTWW,
					(DP83811_SGMII_EN | vawue));
	} ewse {
		eww = phy_wwite(phydev, MII_DP83811_SGMII_CTWW,
				(~DP83811_SGMII_EN & vawue));
	}

	if (eww < 0)

		wetuwn eww;

	vawue = DP83811_WOW_MAGIC_EN | DP83811_WOW_SECUWE_ON | DP83811_WOW_EN;

	wetuwn phy_cweaw_bits_mmd(phydev, DP83811_DEVADDW, MII_DP83811_WOW_CFG,
				  vawue);
}

static int dp83811_phy_weset(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wwite(phydev, MII_DP83811_WESET_CTWW, DP83811_HW_WESET);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int dp83811_suspend(stwuct phy_device *phydev)
{
	int vawue;

	vawue = phy_wead_mmd(phydev, DP83811_DEVADDW, MII_DP83811_WOW_CFG);

	if (!(vawue & DP83811_WOW_EN))
		genphy_suspend(phydev);

	wetuwn 0;
}

static int dp83811_wesume(stwuct phy_device *phydev)
{
	genphy_wesume(phydev);

	phy_set_bits_mmd(phydev, DP83811_DEVADDW, MII_DP83811_WOW_CFG,
			 DP83811_WOW_CWW_INDICATION);

	wetuwn 0;
}

static stwuct phy_dwivew dp83811_dwivew[] = {
	{
		.phy_id = DP83TC811_PHY_ID,
		.phy_id_mask = 0xfffffff0,
		.name = "TI DP83TC811",
		/* PHY_BASIC_FEATUWES */
		.config_init = dp83811_config_init,
		.config_aneg = dp83811_config_aneg,
		.soft_weset = dp83811_phy_weset,
		.get_wow = dp83811_get_wow,
		.set_wow = dp83811_set_wow,
		.config_intw = dp83811_config_intw,
		.handwe_intewwupt = dp83811_handwe_intewwupt,
		.suspend = dp83811_suspend,
		.wesume = dp83811_wesume,
	 },
};
moduwe_phy_dwivew(dp83811_dwivew);

static stwuct mdio_device_id __maybe_unused dp83811_tbw[] = {
	{ DP83TC811_PHY_ID, 0xfffffff0 },
	{ },
};
MODUWE_DEVICE_TABWE(mdio, dp83811_tbw);

MODUWE_DESCWIPTION("Texas Instwuments DP83TC811 PHY dwivew");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com");
MODUWE_WICENSE("GPW");
