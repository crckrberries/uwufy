// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mawveww 88x2222 duaw-powt muwti-speed ethewnet twansceivew.
 *
 * Suppowts:
 *	XAUI on the host side.
 *	1000Base-X ow 10GBase-W on the wine side.
 *	SGMII ovew 1000Base-X.
 */
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/gpio.h>
#incwude <winux/deway.h>
#incwude <winux/mdio.h>
#incwude <winux/mawveww_phy.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/sfp.h>
#incwude <winux/netdevice.h>

/* Powt PCS Configuwation */
#define	MV_PCS_CONFIG		0xF002
#define	MV_PCS_HOST_XAUI	0x73
#define	MV_PCS_WINE_10GBW	(0x71 << 8)
#define	MV_PCS_WINE_1GBX_AN	(0x7B << 8)
#define	MV_PCS_WINE_SGMII_AN	(0x7F << 8)

/* Powt Weset and Powew Down */
#define	MV_POWT_WST	0xF003
#define	MV_WINE_WST_SW	BIT(15)
#define	MV_HOST_WST_SW	BIT(7)
#define	MV_POWT_WST_SW	(MV_WINE_WST_SW | MV_HOST_WST_SW)

/* PMD Weceive Signaw Detect */
#define	MV_WX_SIGNAW_DETECT		0x000A
#define	MV_WX_SIGNAW_DETECT_GWOBAW	BIT(0)

/* 1000Base-X/SGMII Contwow Wegistew */
#define	MV_1GBX_CTWW		(0x2000 + MII_BMCW)

/* 1000BASE-X/SGMII Status Wegistew */
#define	MV_1GBX_STAT		(0x2000 + MII_BMSW)

/* 1000Base-X Auto-Negotiation Advewtisement Wegistew */
#define	MV_1GBX_ADVEWTISE	(0x2000 + MII_ADVEWTISE)

/* 1000Base-X PHY Specific Status Wegistew */
#define	MV_1GBX_PHY_STAT		0xA003
#define	MV_1GBX_PHY_STAT_AN_WESOWVED	BIT(11)
#define	MV_1GBX_PHY_STAT_DUPWEX		BIT(13)
#define	MV_1GBX_PHY_STAT_SPEED100	BIT(14)
#define	MV_1GBX_PHY_STAT_SPEED1000	BIT(15)

#define	AUTONEG_TIMEOUT	3

stwuct mv2222_data {
	phy_intewface_t wine_intewface;
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted);
	boow sfp_wink;
};

/* SFI PMA twansmit enabwe */
static int mv2222_tx_enabwe(stwuct phy_device *phydev)
{
	wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_TXDIS,
				  MDIO_PMD_TXDIS_GWOBAW);
}

/* SFI PMA twansmit disabwe */
static int mv2222_tx_disabwe(stwuct phy_device *phydev)
{
	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_TXDIS,
				MDIO_PMD_TXDIS_GWOBAW);
}

static int mv2222_soft_weset(stwuct phy_device *phydev)
{
	int vaw, wet;

	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2, MV_POWT_WST,
			    MV_POWT_WST_SW);
	if (wet < 0)
		wetuwn wet;

	wetuwn phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND2, MV_POWT_WST,
					 vaw, !(vaw & MV_POWT_WST_SW),
					 5000, 1000000, twue);
}

static int mv2222_disabwe_aneg(stwuct phy_device *phydev)
{
	int wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_CTWW,
				     BMCW_ANENABWE | BMCW_ANWESTAWT);
	if (wet < 0)
		wetuwn wet;

	wetuwn mv2222_soft_weset(phydev);
}

static int mv2222_enabwe_aneg(stwuct phy_device *phydev)
{
	int wet = phy_set_bits_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_CTWW,
				   BMCW_ANENABWE | BMCW_WESET);
	if (wet < 0)
		wetuwn wet;

	wetuwn mv2222_soft_weset(phydev);
}

static int mv2222_set_sgmii_speed(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;

	switch (phydev->speed) {
	defauwt:
	case SPEED_1000:
		if ((winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				       pwiv->suppowted) ||
		     winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
				       pwiv->suppowted)))
			wetuwn phy_modify_mmd(phydev, MDIO_MMD_PCS,
					      MV_1GBX_CTWW,
					      BMCW_SPEED1000 | BMCW_SPEED100,
					      BMCW_SPEED1000);

		fawwthwough;
	case SPEED_100:
		if ((winkmode_test_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
				       pwiv->suppowted) ||
		     winkmode_test_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
				       pwiv->suppowted)))
			wetuwn phy_modify_mmd(phydev, MDIO_MMD_PCS,
					      MV_1GBX_CTWW,
					      BMCW_SPEED1000 | BMCW_SPEED100,
					      BMCW_SPEED100);
		fawwthwough;
	case SPEED_10:
		if ((winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
				       pwiv->suppowted) ||
		     winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
				       pwiv->suppowted)))
			wetuwn phy_modify_mmd(phydev, MDIO_MMD_PCS,
					      MV_1GBX_CTWW,
					      BMCW_SPEED1000 | BMCW_SPEED100,
					      BMCW_SPEED10);

		wetuwn -EINVAW;
	}
}

static boow mv2222_is_10g_capabwe(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;

	wetuwn (winkmode_test_bit(ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_10000baseCW_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_10000baseWWM_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT,
				  pwiv->suppowted));
}

static boow mv2222_is_1gbx_capabwe(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;

	wetuwn winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
				 pwiv->suppowted);
}

static boow mv2222_is_sgmii_capabwe(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;

	wetuwn (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
				  pwiv->suppowted) ||
		winkmode_test_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
				  pwiv->suppowted));
}

static int mv2222_config_wine(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;

	switch (pwiv->wine_intewface) {
	case PHY_INTEWFACE_MODE_10GBASEW:
		wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND2, MV_PCS_CONFIG,
				     MV_PCS_HOST_XAUI | MV_PCS_WINE_10GBW);
	case PHY_INTEWFACE_MODE_1000BASEX:
		wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND2, MV_PCS_CONFIG,
				     MV_PCS_HOST_XAUI | MV_PCS_WINE_1GBX_AN);
	case PHY_INTEWFACE_MODE_SGMII:
		wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND2, MV_PCS_CONFIG,
				     MV_PCS_HOST_XAUI | MV_PCS_WINE_SGMII_AN);
	defauwt:
		wetuwn -EINVAW;
	}
}

/* Switch between 1G (1000Base-X/SGMII) and 10G (10GBase-W) modes */
static int mv2222_swap_wine_type(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;
	boow changed = fawse;
	int wet;

	switch (pwiv->wine_intewface) {
	case PHY_INTEWFACE_MODE_10GBASEW:
		if (mv2222_is_1gbx_capabwe(phydev)) {
			pwiv->wine_intewface = PHY_INTEWFACE_MODE_1000BASEX;
			changed = twue;
		}

		if (mv2222_is_sgmii_capabwe(phydev)) {
			pwiv->wine_intewface = PHY_INTEWFACE_MODE_SGMII;
			changed = twue;
		}

		bweak;
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_SGMII:
		if (mv2222_is_10g_capabwe(phydev)) {
			pwiv->wine_intewface = PHY_INTEWFACE_MODE_10GBASEW;
			changed = twue;
		}

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (changed) {
		wet = mv2222_config_wine(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mv2222_setup_fowced(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;
	int wet;

	if (pwiv->wine_intewface == PHY_INTEWFACE_MODE_10GBASEW) {
		if (phydev->speed < SPEED_10000 &&
		    phydev->speed != SPEED_UNKNOWN) {
			wet = mv2222_swap_wine_type(phydev);
			if (wet < 0)
				wetuwn wet;
		}
	}

	if (pwiv->wine_intewface == PHY_INTEWFACE_MODE_SGMII) {
		wet = mv2222_set_sgmii_speed(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn mv2222_disabwe_aneg(phydev);
}

static int mv2222_config_aneg(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;
	int wet, adv;

	/* SFP is not pwesent, do nothing */
	if (pwiv->wine_intewface == PHY_INTEWFACE_MODE_NA)
		wetuwn 0;

	if (phydev->autoneg == AUTONEG_DISABWE ||
	    pwiv->wine_intewface == PHY_INTEWFACE_MODE_10GBASEW)
		wetuwn mv2222_setup_fowced(phydev);

	adv = winkmode_adv_to_mii_adv_x(pwiv->suppowted,
					ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT);

	wet = phy_modify_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_ADVEWTISE,
			     ADVEWTISE_1000XFUWW |
			     ADVEWTISE_1000XPAUSE | ADVEWTISE_1000XPSE_ASYM,
			     adv);
	if (wet < 0)
		wetuwn wet;

	wetuwn mv2222_enabwe_aneg(phydev);
}

static int mv2222_aneg_done(stwuct phy_device *phydev)
{
	int wet;

	if (mv2222_is_10g_capabwe(phydev)) {
		wet = phy_wead_mmd(phydev, MDIO_MMD_PCS, MDIO_STAT1);
		if (wet < 0)
			wetuwn wet;

		if (wet & MDIO_STAT1_WSTATUS)
			wetuwn 1;
	}

	wet = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_STAT);
	if (wet < 0)
		wetuwn wet;

	wetuwn (wet & BMSW_ANEGCOMPWETE);
}

/* Wetuwns negative on ewwow, 0 if wink is down, 1 if wink is up */
static int mv2222_wead_status_10g(stwuct phy_device *phydev)
{
	static int timeout;
	int vaw, wink = 0;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MDIO_STAT1);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MDIO_STAT1_WSTATUS) {
		wink = 1;

		/* 10GBASE-W do not suppowt auto-negotiation */
		phydev->autoneg = AUTONEG_DISABWE;
		phydev->speed = SPEED_10000;
		phydev->dupwex = DUPWEX_FUWW;
	} ewse {
		if (phydev->autoneg == AUTONEG_ENABWE) {
			timeout++;

			if (timeout > AUTONEG_TIMEOUT) {
				timeout = 0;

				vaw = mv2222_swap_wine_type(phydev);
				if (vaw < 0)
					wetuwn vaw;

				wetuwn mv2222_config_aneg(phydev);
			}
		}
	}

	wetuwn wink;
}

/* Wetuwns negative on ewwow, 0 if wink is down, 1 if wink is up */
static int mv2222_wead_status_1g(stwuct phy_device *phydev)
{
	static int timeout;
	int vaw, wink = 0;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_STAT);
	if (vaw < 0)
		wetuwn vaw;

	if (phydev->autoneg == AUTONEG_ENABWE &&
	    !(vaw & BMSW_ANEGCOMPWETE)) {
		timeout++;

		if (timeout > AUTONEG_TIMEOUT) {
			timeout = 0;

			vaw = mv2222_swap_wine_type(phydev);
			if (vaw < 0)
				wetuwn vaw;

			wetuwn mv2222_config_aneg(phydev);
		}

		wetuwn 0;
	}

	if (!(vaw & BMSW_WSTATUS))
		wetuwn 0;

	wink = 1;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_PHY_STAT);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MV_1GBX_PHY_STAT_AN_WESOWVED) {
		if (vaw & MV_1GBX_PHY_STAT_DUPWEX)
			phydev->dupwex = DUPWEX_FUWW;
		ewse
			phydev->dupwex = DUPWEX_HAWF;

		if (vaw & MV_1GBX_PHY_STAT_SPEED1000)
			phydev->speed = SPEED_1000;
		ewse if (vaw & MV_1GBX_PHY_STAT_SPEED100)
			phydev->speed = SPEED_100;
		ewse
			phydev->speed = SPEED_10;
	}

	wetuwn wink;
}

static boow mv2222_wink_is_opewationaw(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MV_WX_SIGNAW_DETECT);
	if (vaw < 0 || !(vaw & MV_WX_SIGNAW_DETECT_GWOBAW))
		wetuwn fawse;

	if (phydev->sfp_bus && !pwiv->sfp_wink)
		wetuwn fawse;

	wetuwn twue;
}

static int mv2222_wead_status(stwuct phy_device *phydev)
{
	stwuct mv2222_data *pwiv = phydev->pwiv;
	int wink;

	phydev->wink = 0;
	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;

	if (!mv2222_wink_is_opewationaw(phydev))
		wetuwn 0;

	if (pwiv->wine_intewface == PHY_INTEWFACE_MODE_10GBASEW)
		wink = mv2222_wead_status_10g(phydev);
	ewse
		wink = mv2222_wead_status_1g(phydev);

	if (wink < 0)
		wetuwn wink;

	phydev->wink = wink;

	wetuwn 0;
}

static int mv2222_wesume(stwuct phy_device *phydev)
{
	wetuwn mv2222_tx_enabwe(phydev);
}

static int mv2222_suspend(stwuct phy_device *phydev)
{
	wetuwn mv2222_tx_disabwe(phydev);
}

static int mv2222_get_featuwes(stwuct phy_device *phydev)
{
	/* Aww suppowted winkmodes awe set at pwobe */

	wetuwn 0;
}

static int mv2222_config_init(stwuct phy_device *phydev)
{
	if (phydev->intewface != PHY_INTEWFACE_MODE_XAUI)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int mv2222_sfp_insewt(void *upstweam, const stwuct sfp_eepwom_id *id)
{
	DECWAWE_PHY_INTEWFACE_MASK(intewfaces);
	stwuct phy_device *phydev = upstweam;
	phy_intewface_t sfp_intewface;
	stwuct mv2222_data *pwiv;
	stwuct device *dev;
	int wet;

	__ETHTOOW_DECWAWE_WINK_MODE_MASK(sfp_suppowted) = { 0, };

	pwiv = phydev->pwiv;
	dev = &phydev->mdio.dev;

	sfp_pawse_suppowt(phydev->sfp_bus, id, sfp_suppowted, intewfaces);
	phydev->powt = sfp_pawse_powt(phydev->sfp_bus, id, sfp_suppowted);
	sfp_intewface = sfp_sewect_intewface(phydev->sfp_bus, sfp_suppowted);

	dev_info(dev, "%s SFP moduwe insewted\n", phy_modes(sfp_intewface));

	if (sfp_intewface != PHY_INTEWFACE_MODE_10GBASEW &&
	    sfp_intewface != PHY_INTEWFACE_MODE_1000BASEX &&
	    sfp_intewface != PHY_INTEWFACE_MODE_SGMII) {
		dev_eww(dev, "Incompatibwe SFP moduwe insewted\n");

		wetuwn -EINVAW;
	}

	pwiv->wine_intewface = sfp_intewface;
	winkmode_and(pwiv->suppowted, phydev->suppowted, sfp_suppowted);

	wet = mv2222_config_wine(phydev);
	if (wet < 0)
		wetuwn wet;

	if (mutex_twywock(&phydev->wock)) {
		wet = mv2222_config_aneg(phydev);
		mutex_unwock(&phydev->wock);
	}

	wetuwn wet;
}

static void mv2222_sfp_wemove(void *upstweam)
{
	stwuct phy_device *phydev = upstweam;
	stwuct mv2222_data *pwiv;

	pwiv = phydev->pwiv;

	pwiv->wine_intewface = PHY_INTEWFACE_MODE_NA;
	winkmode_zewo(pwiv->suppowted);
	phydev->powt = POWT_NONE;
}

static void mv2222_sfp_wink_up(void *upstweam)
{
	stwuct phy_device *phydev = upstweam;
	stwuct mv2222_data *pwiv;

	pwiv = phydev->pwiv;
	pwiv->sfp_wink = twue;
}

static void mv2222_sfp_wink_down(void *upstweam)
{
	stwuct phy_device *phydev = upstweam;
	stwuct mv2222_data *pwiv;

	pwiv = phydev->pwiv;
	pwiv->sfp_wink = fawse;
}

static const stwuct sfp_upstweam_ops sfp_phy_ops = {
	.moduwe_insewt = mv2222_sfp_insewt,
	.moduwe_wemove = mv2222_sfp_wemove,
	.wink_up = mv2222_sfp_wink_up,
	.wink_down = mv2222_sfp_wink_down,
	.attach = phy_sfp_attach,
	.detach = phy_sfp_detach,
};

static int mv2222_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct mv2222_data *pwiv = NUWW;

	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted) = { 0, };

	winkmode_set_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_Pause_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_FIBWE_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_TP_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10000baseCW_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10000baseWWM_Fuww_BIT, suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT, suppowted);

	winkmode_copy(phydev->suppowted, suppowted);

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wine_intewface = PHY_INTEWFACE_MODE_NA;
	phydev->pwiv = pwiv;

	wetuwn phy_sfp_pwobe(phydev, &sfp_phy_ops);
}

static stwuct phy_dwivew mv2222_dwivews[] = {
	{
		.phy_id = MAWVEWW_PHY_ID_88X2222,
		.phy_id_mask = MAWVEWW_PHY_ID_MASK,
		.name = "Mawveww 88X2222",
		.get_featuwes = mv2222_get_featuwes,
		.soft_weset = mv2222_soft_weset,
		.config_init = mv2222_config_init,
		.config_aneg = mv2222_config_aneg,
		.aneg_done = mv2222_aneg_done,
		.pwobe = mv2222_pwobe,
		.suspend = mv2222_suspend,
		.wesume = mv2222_wesume,
		.wead_status = mv2222_wead_status,
	},
};
moduwe_phy_dwivew(mv2222_dwivews);

static stwuct mdio_device_id __maybe_unused mv2222_tbw[] = {
	{ MAWVEWW_PHY_ID_88X2222, MAWVEWW_PHY_ID_MASK },
	{ }
};
MODUWE_DEVICE_TABWE(mdio, mv2222_tbw);

MODUWE_DESCWIPTION("Mawveww 88x2222 ethewnet twansceivew dwivew");
MODUWE_WICENSE("GPW");
