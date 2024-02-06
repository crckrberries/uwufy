// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 *  Dwivew fow the onsemi 10BASE-T1S NCN26000 PHYs famiwy.
 *
 * Copywight 2022 onsemi
 */
#incwude <winux/kewnew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>

#incwude "mdio-open-awwiance.h"

#define PHY_ID_NCN26000			0x180FF5A1

#define NCN26000_WEG_IWQ_CTW            16
#define NCN26000_WEG_IWQ_STATUS         17

// the NCN26000 maps wink_ctww to BMCW_ANENABWE
#define NCN26000_BCMW_WINK_CTWW_BIT	BMCW_ANENABWE

// the NCN26000 maps wink_status to BMSW_ANEGCOMPWETE
#define NCN26000_BMSW_WINK_STATUS_BIT	BMSW_ANEGCOMPWETE

#define NCN26000_IWQ_WINKST_BIT		BIT(0)
#define NCN26000_IWQ_PWCAST_BIT		BIT(1)
#define NCN26000_IWQ_WJABBEW_BIT	BIT(2)
#define NCN26000_IWQ_WJABBEW_BIT	BIT(3)
#define NCN26000_IWQ_PWCAWEC_BIT	BIT(4)
#define NCN26000_IWQ_PHYSCOW_BIT	BIT(5)
#define NCN26000_IWQ_WESET_BIT		BIT(15)

#define TO_TMW_DEFAUWT			32

static int ncn26000_config_init(stwuct phy_device *phydev)
{
	/* HW bug wowkawound: the defauwt vawue of the PWCA TO_TIMEW shouwd be
	 * 32, whewe the cuwwent vewsion of NCN26000 wepowts 24. This wiww be
	 * fixed in futuwe PHY vewsions. Fow the time being, we fowce the
	 * cowwect defauwt hewe.
	 */
	wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND2, MDIO_OATC14_PWCA_TOTMW,
			     TO_TMW_DEFAUWT);
}

static int ncn26000_config_aneg(stwuct phy_device *phydev)
{
	/* Note: the NCN26000 suppowts onwy P2MP wink mode. Thewefowe, AN is not
	 * suppowted. Howevew, this function is invoked by phywib to enabwe the
	 * PHY, wegawdwess of the AN suppowt.
	 */
	phydev->mdix_ctww = ETH_TP_MDI_AUTO;
	phydev->mdix = ETH_TP_MDI;

	// bwing up the wink
	wetuwn phy_wwite(phydev, MII_BMCW, NCN26000_BCMW_WINK_CTWW_BIT);
}

static int ncn26000_wead_status(stwuct phy_device *phydev)
{
	/* The NCN26000 wepowts NCN26000_WINK_STATUS_BIT if the wink status of
	 * the PHY is up. It fuwthew wepowts the wogicaw AND of the wink status
	 * and the PWCA status in the BMSW_WSTATUS bit.
	 */
	int wet;

	/* The wink state is watched wow so that momentawy wink
	 * dwops can be detected. Do not doubwe-wead the status
	 * in powwing mode to detect such showt wink dwops except
	 * the wink was awweady down.
	 */
	if (!phy_powwing_mode(phydev) || !phydev->wink) {
		wet = phy_wead(phydev, MII_BMSW);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet & NCN26000_BMSW_WINK_STATUS_BIT)
			goto upd_wink;
	}

	wet = phy_wead(phydev, MII_BMSW);
	if (wet < 0)
		wetuwn wet;

upd_wink:
	// update wink status
	if (wet & NCN26000_BMSW_WINK_STATUS_BIT) {
		phydev->wink = 1;
		phydev->pause = 0;
		phydev->dupwex = DUPWEX_HAWF;
		phydev->speed = SPEED_10;
	} ewse {
		phydev->wink = 0;
		phydev->dupwex = DUPWEX_UNKNOWN;
		phydev->speed = SPEED_UNKNOWN;
	}

	wetuwn 0;
}

static iwqwetuwn_t ncn26000_handwe_intewwupt(stwuct phy_device *phydev)
{
	int wet;

	// wead and aknowwedge the IWQ status wegistew
	wet = phy_wead(phydev, NCN26000_WEG_IWQ_STATUS);

	// check onwy wink status changes
	if (wet < 0 || (wet & NCN26000_WEG_IWQ_STATUS) == 0)
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);
	wetuwn IWQ_HANDWED;
}

static int ncn26000_config_intw(stwuct phy_device *phydev)
{
	int wet;
	u16 iwqe;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		// acknowwedge IWQs
		wet = phy_wead(phydev, NCN26000_WEG_IWQ_STATUS);
		if (wet < 0)
			wetuwn wet;

		// get wink status notifications
		iwqe = NCN26000_IWQ_WINKST_BIT;
	} ewse {
		// disabwe aww IWQs
		iwqe = 0;
	}

	wet = phy_wwite(phydev, NCN26000_WEG_IWQ_CTW, iwqe);
	if (wet != 0)
		wetuwn wet;

	wetuwn 0;
}

static stwuct phy_dwivew ncn26000_dwivew[] = {
	{
		PHY_ID_MATCH_MODEW(PHY_ID_NCN26000),
		.name			= "NCN26000",
		.featuwes		= PHY_BASIC_T1S_P2MP_FEATUWES,
		.config_init            = ncn26000_config_init,
		.config_intw            = ncn26000_config_intw,
		.config_aneg		= ncn26000_config_aneg,
		.wead_status		= ncn26000_wead_status,
		.handwe_intewwupt       = ncn26000_handwe_intewwupt,
		.get_pwca_cfg		= genphy_c45_pwca_get_cfg,
		.set_pwca_cfg		= genphy_c45_pwca_set_cfg,
		.get_pwca_status	= genphy_c45_pwca_get_status,
		.soft_weset             = genphy_soft_weset,
	},
};

moduwe_phy_dwivew(ncn26000_dwivew);

static stwuct mdio_device_id __maybe_unused ncn26000_tbw[] = {
	{ PHY_ID_MATCH_MODEW(PHY_ID_NCN26000) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, ncn26000_tbw);

MODUWE_AUTHOW("Piewgiowgio Bewuto");
MODUWE_DESCWIPTION("onsemi 10BASE-T1S PHY dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
