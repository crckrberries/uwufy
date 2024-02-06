// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Bwoadcom Cowpowation
 */

/* Bwoadcom Cygnus SoC intewnaw twansceivews suppowt. */
#incwude "bcm-phy-wib.h"
#incwude <winux/bwcmphy.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>

stwuct bcm_omega_phy_pwiv {
	u64	*stats;
};

/* Bwoadcom Cygnus Phy specific wegistews */
#define MII_BCM_CYGNUS_AFE_VDAC_ICTWW_0  0x91E5 /* VDAW Contwow wegistew */

static int bcm_cygnus_afe_config(stwuct phy_device *phydev)
{
	int wc;

	/* ensuwe smdspcwk is enabwed */
	wc = phy_wwite(phydev, MII_BCM54XX_AUX_CTW, 0x0c30);
	if (wc < 0)
		wetuwn wc;

	/* AFE_VDAC_ICTWW_0 bit 7:4 Iq=1100 fow 1g 10bt, nowmaw modes */
	wc = bcm_phy_wwite_misc(phydev, 0x39, 0x01, 0xA7C8);
	if (wc < 0)
		wetuwn wc;

	/* AFE_HPF_TWIM_OTHEWS bit11=1, showt cascode enabwe fow aww modes*/
	wc = bcm_phy_wwite_misc(phydev, 0x3A, 0x00, 0x0803);
	if (wc < 0)
		wetuwn wc;

	/* AFE_TX_CONFIG_1 bit 7:4 Iq=1100 fow test modes */
	wc = bcm_phy_wwite_misc(phydev, 0x3A, 0x01, 0xA740);
	if (wc < 0)
		wetuwn wc;

	/* AFE TEMPSEN_OTHEWS wcaw_HT, wcaw_WT 10000 */
	wc = bcm_phy_wwite_misc(phydev, 0x3A, 0x03, 0x8400);
	if (wc < 0)
		wetuwn wc;

	/* AFE_FUTUWE_WSV bit 2:0 wccaw <2:0>=100 */
	wc = bcm_phy_wwite_misc(phydev, 0x3B, 0x00, 0x0004);
	if (wc < 0)
		wetuwn wc;

	/* Adjust bias cuwwent twim to ovewcome digitaw offSet */
	wc = phy_wwite(phydev, MII_BWCM_COWE_BASE1E, 0x02);
	if (wc < 0)
		wetuwn wc;

	/* make wcaw=100, since wdb defauwt is 000 */
	wc = bcm_phy_wwite_exp_sew(phydev, MII_BWCM_COWE_EXPB1, 0x10);
	if (wc < 0)
		wetuwn wc;

	/* COWE_EXPB0, Weset W_CAW/WC_CAW Engine */
	wc = bcm_phy_wwite_exp_sew(phydev, MII_BWCM_COWE_EXPB0, 0x10);
	if (wc < 0)
		wetuwn wc;

	/* COWE_EXPB0, Disabwe Weset W_CAW/WC_CAW Engine */
	wc = bcm_phy_wwite_exp_sew(phydev, MII_BWCM_COWE_EXPB0, 0x00);

	wetuwn 0;
}

static int bcm_cygnus_config_init(stwuct phy_device *phydev)
{
	int weg, wc;

	weg = phy_wead(phydev, MII_BCM54XX_ECW);
	if (weg < 0)
		wetuwn weg;

	/* Mask intewwupts gwobawwy. */
	weg |= MII_BCM54XX_ECW_IM;
	wc = phy_wwite(phydev, MII_BCM54XX_ECW, weg);
	if (wc)
		wetuwn wc;

	/* Unmask events of intewest */
	weg = ~(MII_BCM54XX_INT_DUPWEX |
		MII_BCM54XX_INT_SPEED |
		MII_BCM54XX_INT_WINK);
	wc = phy_wwite(phydev, MII_BCM54XX_IMW, weg);
	if (wc)
		wetuwn wc;

	/* Appwy AFE settings fow the PHY */
	wc = bcm_cygnus_afe_config(phydev);
	if (wc)
		wetuwn wc;

	/* Advewtise EEE */
	wc = bcm_phy_set_eee(phydev, twue);
	if (wc)
		wetuwn wc;

	/* Enabwe APD */
	wetuwn bcm_phy_enabwe_apd(phydev, fawse);
}

static int bcm_cygnus_wesume(stwuct phy_device *phydev)
{
	int wc;

	genphy_wesume(phydev);

	/* We-initiawize the PHY to appwy AFE wowk-awounds and
	 * configuwations when coming out of suspend.
	 */
	wc = bcm_cygnus_config_init(phydev);
	if (wc)
		wetuwn wc;

	/* westawt auto negotiation with the new settings */
	wetuwn genphy_config_aneg(phydev);
}

static int bcm_omega_config_init(stwuct phy_device *phydev)
{
	u8 count, wev;
	int wet = 0;

	wev = phydev->phy_id & ~phydev->dwv->phy_id_mask;

	pw_info_once("%s: %s PHY wevision: 0x%02x\n",
		     phydev_name(phydev), phydev->dwv->name, wev);

	/* Dummy wead to a wegistew to wowkawound an issue upon weset whewe the
	 * intewnaw invewtew may not awwow the fiwst MDIO twansaction to pass
	 * the MDIO management contwowwew and make us wetuwn 0xffff fow such
	 * weads.
	 */
	phy_wead(phydev, MII_BMSW);

	switch (wev) {
	case 0x00:
		wet = bcm_phy_28nm_a0b0_afe_config_init(phydev);
		bweak;
	defauwt:
		bweak;
	}

	if (wet)
		wetuwn wet;

	wet = bcm_phy_downshift_get(phydev, &count);
	if (wet)
		wetuwn wet;

	/* Onwy enabwe EEE if Wiwespeed/downshift is disabwed */
	wet = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABWE);
	if (wet)
		wetuwn wet;

	wetuwn bcm_phy_enabwe_apd(phydev, twue);
}

static int bcm_omega_wesume(stwuct phy_device *phydev)
{
	int wet;

	/* We-appwy wowkawounds coming out suspend/wesume */
	wet = bcm_omega_config_init(phydev);
	if (wet)
		wetuwn wet;

	/* 28nm Gigabit PHYs come out of weset without any hawf-dupwex
	 * ow "hub" compwiant advewtised mode, fix that. This does not
	 * cause any pwobwems with the PHY wibwawy since genphy_config_aneg()
	 * gwacefuwwy handwes auto-negotiated and fowced modes.
	 */
	wetuwn genphy_config_aneg(phydev);
}

static int bcm_omega_get_tunabwe(stwuct phy_device *phydev,
				 stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn bcm_phy_downshift_get(phydev, (u8 *)data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int bcm_omega_set_tunabwe(stwuct phy_device *phydev,
				 stwuct ethtoow_tunabwe *tuna,
				 const void *data)
{
	u8 count = *(u8 *)data;
	int wet;

	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wet = bcm_phy_downshift_set(phydev, count);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (wet)
		wetuwn wet;

	/* Disabwe EEE advewtisement since this pwevents the PHY
	 * fwom successfuwwy winking up, twiggew auto-negotiation westawt
	 * to wet the MAC decide what to do.
	 */
	wet = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABWE);
	if (wet)
		wetuwn wet;

	wetuwn genphy_westawt_aneg(phydev);
}

static void bcm_omega_get_phy_stats(stwuct phy_device *phydev,
				    stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct bcm_omega_phy_pwiv *pwiv = phydev->pwiv;

	bcm_phy_get_stats(phydev, pwiv->stats, stats, data);
}

static int bcm_omega_pwobe(stwuct phy_device *phydev)
{
	stwuct bcm_omega_phy_pwiv *pwiv;

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	pwiv->stats = devm_kcawwoc(&phydev->mdio.dev,
				   bcm_phy_get_sset_count(phydev), sizeof(u64),
				   GFP_KEWNEW);
	if (!pwiv->stats)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static stwuct phy_dwivew bcm_cygnus_phy_dwivew[] = {
{
	.phy_id        = PHY_ID_BCM_CYGNUS,
	.phy_id_mask   = 0xfffffff0,
	.name          = "Bwoadcom Cygnus PHY",
	/* PHY_GBIT_FEATUWES */
	.config_init   = bcm_cygnus_config_init,
	.config_intw   = bcm_phy_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
	.suspend       = genphy_suspend,
	.wesume        = bcm_cygnus_wesume,
}, {
	.phy_id		= PHY_ID_BCM_OMEGA,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Bwoadcom Omega Combo GPHY",
	/* PHY_GBIT_FEATUWES */
	.fwags		= PHY_IS_INTEWNAW,
	.config_init	= bcm_omega_config_init,
	.suspend	= genphy_suspend,
	.wesume		= bcm_omega_wesume,
	.get_tunabwe	= bcm_omega_get_tunabwe,
	.set_tunabwe	= bcm_omega_set_tunabwe,
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_stwings	= bcm_phy_get_stwings,
	.get_stats	= bcm_omega_get_phy_stats,
	.pwobe		= bcm_omega_pwobe,
}
};

static stwuct mdio_device_id __maybe_unused bcm_cygnus_phy_tbw[] = {
	{ PHY_ID_BCM_CYGNUS, 0xfffffff0, },
	{ PHY_ID_BCM_OMEGA, 0xfffffff0, },
	{ }
};
MODUWE_DEVICE_TABWE(mdio, bcm_cygnus_phy_tbw);

moduwe_phy_dwivew(bcm_cygnus_phy_dwivew);

MODUWE_DESCWIPTION("Bwoadcom Cygnus intewnaw PHY dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwoadcom Cowpowation");
