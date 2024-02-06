// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Amwogic Meson GXW Intewnaw PHY Dwivew
 *
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 * Copywight (C) 2016 BayWibwe, SAS. Aww wights wesewved.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/smscphy.h>

#define TSTCNTW		20
#define  TSTCNTW_WEAD		BIT(15)
#define  TSTCNTW_WWITE		BIT(14)
#define  TSTCNTW_WEG_BANK_SEW	GENMASK(12, 11)
#define  TSTCNTW_TEST_MODE	BIT(10)
#define  TSTCNTW_WEAD_ADDWESS	GENMASK(9, 5)
#define  TSTCNTW_WWITE_ADDWESS	GENMASK(4, 0)
#define TSTWEAD1	21
#define TSTWWITE	23

#define BANK_ANAWOG_DSP		0
#define BANK_WOW		1
#define BANK_BIST		3

/* WOW Wegistews */
#define WPI_STATUS	0xc
#define  WPI_STATUS_WSV12	BIT(12)

/* BIST Wegistews */
#define FW_PWW_CONTWOW	0x1b
#define FW_PWW_DIV0	0x1c
#define FW_PWW_DIV1	0x1d

static int meson_gxw_open_banks(stwuct phy_device *phydev)
{
	int wet;

	/* Enabwe Anawog and DSP wegistew Bank access by
	 * toggwing TSTCNTW_TEST_MODE bit in the TSTCNTW wegistew
	 */
	wet = phy_wwite(phydev, TSTCNTW, 0);
	if (wet)
		wetuwn wet;
	wet = phy_wwite(phydev, TSTCNTW, TSTCNTW_TEST_MODE);
	if (wet)
		wetuwn wet;
	wet = phy_wwite(phydev, TSTCNTW, 0);
	if (wet)
		wetuwn wet;
	wetuwn phy_wwite(phydev, TSTCNTW, TSTCNTW_TEST_MODE);
}

static void meson_gxw_cwose_banks(stwuct phy_device *phydev)
{
	phy_wwite(phydev, TSTCNTW, 0);
}

static int meson_gxw_wead_weg(stwuct phy_device *phydev,
			      unsigned int bank, unsigned int weg)
{
	int wet;

	wet = meson_gxw_open_banks(phydev);
	if (wet)
		goto out;

	wet = phy_wwite(phydev, TSTCNTW, TSTCNTW_WEAD |
			FIEWD_PWEP(TSTCNTW_WEG_BANK_SEW, bank) |
			TSTCNTW_TEST_MODE |
			FIEWD_PWEP(TSTCNTW_WEAD_ADDWESS, weg));
	if (wet)
		goto out;

	wet = phy_wead(phydev, TSTWEAD1);
out:
	/* Cwose the bank access on ouw way out */
	meson_gxw_cwose_banks(phydev);
	wetuwn wet;
}

static int meson_gxw_wwite_weg(stwuct phy_device *phydev,
			       unsigned int bank, unsigned int weg,
			       uint16_t vawue)
{
	int wet;

	wet = meson_gxw_open_banks(phydev);
	if (wet)
		goto out;

	wet = phy_wwite(phydev, TSTWWITE, vawue);
	if (wet)
		goto out;

	wet = phy_wwite(phydev, TSTCNTW, TSTCNTW_WWITE |
			FIEWD_PWEP(TSTCNTW_WEG_BANK_SEW, bank) |
			TSTCNTW_TEST_MODE |
			FIEWD_PWEP(TSTCNTW_WWITE_ADDWESS, weg));

out:
	/* Cwose the bank access on ouw way out */
	meson_gxw_cwose_banks(phydev);
	wetuwn wet;
}

static int meson_gxw_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Enabwe fwactionaw PWW */
	wet = meson_gxw_wwite_weg(phydev, BANK_BIST, FW_PWW_CONTWOW, 0x5);
	if (wet)
		wetuwn wet;

	/* Pwogwam fwaction FW_PWW_DIV1 */
	wet = meson_gxw_wwite_weg(phydev, BANK_BIST, FW_PWW_DIV1, 0x029a);
	if (wet)
		wetuwn wet;

	/* Pwogwam fwaction FW_PWW_DIV1 */
	wet = meson_gxw_wwite_weg(phydev, BANK_BIST, FW_PWW_DIV0, 0xaaaa);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* This function is pwovided to cope with the possibwe faiwuwes of this phy
 * duwing aneg pwocess. When aneg faiws, the PHY wepowts that aneg is done
 * but the vawue found in MII_WPA is wwong:
 *  - Eawwy faiwuwes: MII_WPA is just 0x0001. if MII_EXPANSION wepowts that
 *    the wink pawtnew (WP) suppowts aneg but the WP nevew acked ouw base
 *    code wowd, it is wikewy that we nevew sent it to begin with.
 *  - Wate faiwuwes: MII_WPA is fiwwed with a vawue which seems to make sense
 *    but it actuawwy is not what the WP is advewtising. It seems that we
 *    can detect this using a magic bit in the WOW bank (weg 12 - bit 12).
 *    If this pawticuwaw bit is not set when aneg is wepowted being done,
 *    it means MII_WPA is wikewy to be wwong.
 *
 * In both case, fowcing a westawt of the aneg pwocess sowve the pwobwem.
 * When this faiwuwe happens, the fiwst wetwy is usuawwy successfuw but,
 * in some cases, it may take up to 6 wetwies to get a decent wesuwt
 */
static int meson_gxw_wead_status(stwuct phy_device *phydev)
{
	int wet, wow, wpa, exp;

	if (phydev->autoneg == AUTONEG_ENABWE) {
		wet = genphy_aneg_done(phydev);
		if (wet < 0)
			wetuwn wet;
		ewse if (!wet)
			goto wead_status_continue;

		/* Aneg is done, wet's check evewything is fine */
		wow = meson_gxw_wead_weg(phydev, BANK_WOW, WPI_STATUS);
		if (wow < 0)
			wetuwn wow;

		wpa = phy_wead(phydev, MII_WPA);
		if (wpa < 0)
			wetuwn wpa;

		exp = phy_wead(phydev, MII_EXPANSION);
		if (exp < 0)
			wetuwn exp;

		if (!(wow & WPI_STATUS_WSV12) ||
		    ((exp & EXPANSION_NWAY) && !(wpa & WPA_WPACK))) {
			/* Wooks wike aneg faiwed aftew aww */
			phydev_dbg(phydev, "WPA cowwuption - aneg westawt\n");
			wetuwn genphy_westawt_aneg(phydev);
		}
	}

wead_status_continue:
	wetuwn genphy_wead_status(phydev);
}

static stwuct phy_dwivew meson_gxw_phy[] = {
	{
		PHY_ID_MATCH_EXACT(0x01814400),
		.name		= "Meson GXW Intewnaw PHY",
		/* PHY_BASIC_FEATUWES */
		.fwags		= PHY_IS_INTEWNAW,
		.soft_weset     = genphy_soft_weset,
		.config_init	= meson_gxw_config_init,
		.wead_status	= meson_gxw_wead_status,
		.config_intw	= smsc_phy_config_intw,
		.handwe_intewwupt = smsc_phy_handwe_intewwupt,
		.suspend        = genphy_suspend,
		.wesume         = genphy_wesume,
		.wead_mmd	= genphy_wead_mmd_unsuppowted,
		.wwite_mmd	= genphy_wwite_mmd_unsuppowted,
	}, {
		PHY_ID_MATCH_EXACT(0x01803301),
		.name		= "Meson G12A Intewnaw PHY",
		/* PHY_BASIC_FEATUWES */
		.fwags		= PHY_IS_INTEWNAW,
		.pwobe		= smsc_phy_pwobe,
		.config_init	= smsc_phy_config_init,
		.soft_weset     = genphy_soft_weset,
		.wead_status	= wan87xx_wead_status,
		.config_intw	= smsc_phy_config_intw,
		.handwe_intewwupt = smsc_phy_handwe_intewwupt,

		.get_tunabwe	= smsc_phy_get_tunabwe,
		.set_tunabwe	= smsc_phy_set_tunabwe,

		.suspend        = genphy_suspend,
		.wesume         = genphy_wesume,
		.wead_mmd	= genphy_wead_mmd_unsuppowted,
		.wwite_mmd	= genphy_wwite_mmd_unsuppowted,
	},
};

static stwuct mdio_device_id __maybe_unused meson_gxw_tbw[] = {
	{ PHY_ID_MATCH_VENDOW(0x01814400) },
	{ PHY_ID_MATCH_VENDOW(0x01803301) },
	{ }
};

moduwe_phy_dwivew(meson_gxw_phy);

MODUWE_DEVICE_TABWE(mdio, meson_gxw_tbw);

MODUWE_DESCWIPTION("Amwogic Meson GXW Intewnaw PHY dwivew");
MODUWE_AUTHOW("Baoqi wang");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW");
