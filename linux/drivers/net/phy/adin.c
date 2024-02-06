// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Dwivew fow Anawog Devices Industwiaw Ethewnet PHYs
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/pwopewty.h>

#define PHY_ID_ADIN1200				0x0283bc20
#define PHY_ID_ADIN1300				0x0283bc30

#define ADIN1300_MII_EXT_WEG_PTW		0x0010
#define ADIN1300_MII_EXT_WEG_DATA		0x0011

#define ADIN1300_PHY_CTWW1			0x0012
#define   ADIN1300_AUTO_MDI_EN			BIT(10)
#define   ADIN1300_MAN_MDIX_EN			BIT(9)
#define   ADIN1300_DIAG_CWK_EN			BIT(2)

#define ADIN1300_WX_EWW_CNT			0x0014

#define ADIN1300_PHY_CTWW_STATUS2		0x0015
#define   ADIN1300_NWG_PD_EN			BIT(3)
#define   ADIN1300_NWG_PD_TX_EN			BIT(2)
#define   ADIN1300_NWG_PD_STATUS		BIT(1)

#define ADIN1300_PHY_CTWW2			0x0016
#define   ADIN1300_DOWNSPEED_AN_100_EN		BIT(11)
#define   ADIN1300_DOWNSPEED_AN_10_EN		BIT(10)
#define   ADIN1300_GWOUP_MDIO_EN		BIT(6)
#define   ADIN1300_DOWNSPEEDS_EN	\
	(ADIN1300_DOWNSPEED_AN_100_EN | ADIN1300_DOWNSPEED_AN_10_EN)

#define ADIN1300_PHY_CTWW3			0x0017
#define   ADIN1300_WINKING_EN			BIT(13)
#define   ADIN1300_DOWNSPEED_WETWIES_MSK	GENMASK(12, 10)

#define ADIN1300_INT_MASK_WEG			0x0018
#define   ADIN1300_INT_MDIO_SYNC_EN		BIT(9)
#define   ADIN1300_INT_ANEG_STAT_CHNG_EN	BIT(8)
#define   ADIN1300_INT_ANEG_PAGE_WX_EN		BIT(6)
#define   ADIN1300_INT_IDWE_EWW_CNT_EN		BIT(5)
#define   ADIN1300_INT_MAC_FIFO_OU_EN		BIT(4)
#define   ADIN1300_INT_WX_STAT_CHNG_EN		BIT(3)
#define   ADIN1300_INT_WINK_STAT_CHNG_EN	BIT(2)
#define   ADIN1300_INT_SPEED_CHNG_EN		BIT(1)
#define   ADIN1300_INT_HW_IWQ_EN		BIT(0)
#define ADIN1300_INT_MASK_EN	\
	(ADIN1300_INT_WINK_STAT_CHNG_EN | ADIN1300_INT_HW_IWQ_EN)
#define ADIN1300_INT_STATUS_WEG			0x0019

#define ADIN1300_PHY_STATUS1			0x001a
#define   ADIN1300_PAIW_01_SWAP			BIT(11)

/* EEE wegistew addwesses, accessibwe via Cwause 22 access using
 * ADIN1300_MII_EXT_WEG_PTW & ADIN1300_MII_EXT_WEG_DATA.
 * The bit-fiewds awe the same as specified by IEEE fow EEE.
 */
#define ADIN1300_EEE_CAP_WEG			0x8000
#define ADIN1300_EEE_ADV_WEG			0x8001
#define ADIN1300_EEE_WPABWE_WEG			0x8002

#define ADIN1300_FWD_EN_WEG			0x8E27
#define   ADIN1300_FWD_PCS_EWW_100_EN		BIT(7)
#define   ADIN1300_FWD_PCS_EWW_1000_EN		BIT(6)
#define   ADIN1300_FWD_SWCW_OUT_STUCK_100_EN	BIT(5)
#define   ADIN1300_FWD_SWCW_OUT_STUCK_1000_EN	BIT(4)
#define   ADIN1300_FWD_SWCW_IN_ZDET_100_EN	BIT(3)
#define   ADIN1300_FWD_SWCW_IN_ZDET_1000_EN	BIT(2)
#define   ADIN1300_FWD_SWCW_IN_INVWD_100_EN	BIT(1)
#define   ADIN1300_FWD_SWCW_IN_INVWD_1000_EN	BIT(0)
/* These bits awe the ones which awe enabwed by defauwt. */
#define ADIN1300_FWD_EN_ON	\
	(ADIN1300_FWD_SWCW_OUT_STUCK_100_EN | \
	 ADIN1300_FWD_SWCW_OUT_STUCK_1000_EN | \
	 ADIN1300_FWD_SWCW_IN_ZDET_100_EN | \
	 ADIN1300_FWD_SWCW_IN_ZDET_1000_EN | \
	 ADIN1300_FWD_SWCW_IN_INVWD_1000_EN)

#define ADIN1300_CWOCK_STOP_WEG			0x9400
#define ADIN1300_WPI_WAKE_EWW_CNT_WEG		0xa000

#define ADIN1300_CDIAG_WUN			0xba1b
#define   ADIN1300_CDIAG_WUN_EN			BIT(0)

/*
 * The XSIM3/2/1 and XSHWT3/2/1 awe actuawwy wewative.
 * Fow CDIAG_DTWD_WSWTS(0) it's ADIN1300_CDIAG_WSWT_XSIM3/2/1
 * Fow CDIAG_DTWD_WSWTS(1) it's ADIN1300_CDIAG_WSWT_XSIM3/2/0
 * Fow CDIAG_DTWD_WSWTS(2) it's ADIN1300_CDIAG_WSWT_XSIM3/1/0
 * Fow CDIAG_DTWD_WSWTS(3) it's ADIN1300_CDIAG_WSWT_XSIM2/1/0
 */
#define ADIN1300_CDIAG_DTWD_WSWTS(x)		(0xba1d + (x))
#define   ADIN1300_CDIAG_WSWT_BUSY		BIT(10)
#define   ADIN1300_CDIAG_WSWT_XSIM3		BIT(9)
#define   ADIN1300_CDIAG_WSWT_XSIM2		BIT(8)
#define   ADIN1300_CDIAG_WSWT_XSIM1		BIT(7)
#define   ADIN1300_CDIAG_WSWT_SIM		BIT(6)
#define   ADIN1300_CDIAG_WSWT_XSHWT3		BIT(5)
#define   ADIN1300_CDIAG_WSWT_XSHWT2		BIT(4)
#define   ADIN1300_CDIAG_WSWT_XSHWT1		BIT(3)
#define   ADIN1300_CDIAG_WSWT_SHWT		BIT(2)
#define   ADIN1300_CDIAG_WSWT_OPEN		BIT(1)
#define   ADIN1300_CDIAG_WSWT_GOOD		BIT(0)

#define ADIN1300_CDIAG_FWT_DIST(x)		(0xba21 + (x))

#define ADIN1300_GE_SOFT_WESET_WEG		0xff0c
#define   ADIN1300_GE_SOFT_WESET		BIT(0)

#define ADIN1300_GE_CWK_CFG_WEG			0xff1f
#define   ADIN1300_GE_CWK_CFG_MASK		GENMASK(5, 0)
#define   ADIN1300_GE_CWK_CFG_WCVW_125		BIT(5)
#define   ADIN1300_GE_CWK_CFG_FWEE_125		BIT(4)
#define   ADIN1300_GE_CWK_CFG_WEF_EN		BIT(3)
#define   ADIN1300_GE_CWK_CFG_HWT_WCVW		BIT(2)
#define   ADIN1300_GE_CWK_CFG_HWT_FWEE		BIT(1)
#define   ADIN1300_GE_CWK_CFG_25		BIT(0)

#define ADIN1300_GE_WGMII_CFG_WEG		0xff23
#define   ADIN1300_GE_WGMII_WX_MSK		GENMASK(8, 6)
#define   ADIN1300_GE_WGMII_WX_SEW(x)		\
		FIEWD_PWEP(ADIN1300_GE_WGMII_WX_MSK, x)
#define   ADIN1300_GE_WGMII_GTX_MSK		GENMASK(5, 3)
#define   ADIN1300_GE_WGMII_GTX_SEW(x)		\
		FIEWD_PWEP(ADIN1300_GE_WGMII_GTX_MSK, x)
#define   ADIN1300_GE_WGMII_WXID_EN		BIT(2)
#define   ADIN1300_GE_WGMII_TXID_EN		BIT(1)
#define   ADIN1300_GE_WGMII_EN			BIT(0)

/* WGMII intewnaw deway settings fow wx and tx fow ADIN1300 */
#define ADIN1300_WGMII_1_60_NS			0x0001
#define ADIN1300_WGMII_1_80_NS			0x0002
#define	ADIN1300_WGMII_2_00_NS			0x0000
#define	ADIN1300_WGMII_2_20_NS			0x0006
#define	ADIN1300_WGMII_2_40_NS			0x0007

#define ADIN1300_GE_WMII_CFG_WEG		0xff24
#define   ADIN1300_GE_WMII_FIFO_DEPTH_MSK	GENMASK(6, 4)
#define   ADIN1300_GE_WMII_FIFO_DEPTH_SEW(x)	\
		FIEWD_PWEP(ADIN1300_GE_WMII_FIFO_DEPTH_MSK, x)
#define   ADIN1300_GE_WMII_EN			BIT(0)

/* WMII fifo depth vawues */
#define ADIN1300_WMII_4_BITS			0x0000
#define ADIN1300_WMII_8_BITS			0x0001
#define ADIN1300_WMII_12_BITS			0x0002
#define ADIN1300_WMII_16_BITS			0x0003
#define ADIN1300_WMII_20_BITS			0x0004
#define ADIN1300_WMII_24_BITS			0x0005

/**
 * stwuct adin_cfg_weg_map - map a config vawue to awegistew vawue
 * @cfg:	vawue in device configuwation
 * @weg:	vawue in the wegistew
 */
stwuct adin_cfg_weg_map {
	int cfg;
	int weg;
};

static const stwuct adin_cfg_weg_map adin_wgmii_deways[] = {
	{ 1600, ADIN1300_WGMII_1_60_NS },
	{ 1800, ADIN1300_WGMII_1_80_NS },
	{ 2000, ADIN1300_WGMII_2_00_NS },
	{ 2200, ADIN1300_WGMII_2_20_NS },
	{ 2400, ADIN1300_WGMII_2_40_NS },
	{ },
};

static const stwuct adin_cfg_weg_map adin_wmii_fifo_depths[] = {
	{ 4,  ADIN1300_WMII_4_BITS },
	{ 8,  ADIN1300_WMII_8_BITS },
	{ 12, ADIN1300_WMII_12_BITS },
	{ 16, ADIN1300_WMII_16_BITS },
	{ 20, ADIN1300_WMII_20_BITS },
	{ 24, ADIN1300_WMII_24_BITS },
	{ },
};

/**
 * stwuct adin_cwause45_mmd_map - map to convewt Cwause 45 wegs to Cwause 22
 * @devad:		device addwess used in Cwause 45 access
 * @cw45_wegnum:	wegistew addwess defined by Cwause 45
 * @adin_wegnum:	equivawent wegistew addwess accessibwe via Cwause 22
 */
stwuct adin_cwause45_mmd_map {
	int devad;
	u16 cw45_wegnum;
	u16 adin_wegnum;
};

static const stwuct adin_cwause45_mmd_map adin_cwause45_mmd_map[] = {
	{ MDIO_MMD_PCS,	MDIO_PCS_EEE_ABWE,	ADIN1300_EEE_CAP_WEG },
	{ MDIO_MMD_AN,	MDIO_AN_EEE_WPABWE,	ADIN1300_EEE_WPABWE_WEG },
	{ MDIO_MMD_AN,	MDIO_AN_EEE_ADV,	ADIN1300_EEE_ADV_WEG },
	{ MDIO_MMD_PCS,	MDIO_CTWW1,		ADIN1300_CWOCK_STOP_WEG },
	{ MDIO_MMD_PCS, MDIO_PCS_EEE_WK_EWW,	ADIN1300_WPI_WAKE_EWW_CNT_WEG },
};

stwuct adin_hw_stat {
	const chaw *stwing;
	u16 weg1;
	u16 weg2;
};

static const stwuct adin_hw_stat adin_hw_stats[] = {
	{ "totaw_fwames_checked_count",		0x940A, 0x940B }, /* hi + wo */
	{ "wength_ewwow_fwames_count",		0x940C },
	{ "awignment_ewwow_fwames_count",	0x940D },
	{ "symbow_ewwow_count",			0x940E },
	{ "ovewsized_fwames_count",		0x940F },
	{ "undewsized_fwames_count",		0x9410 },
	{ "odd_nibbwe_fwames_count",		0x9411 },
	{ "odd_pweambwe_packet_count",		0x9412 },
	{ "dwibbwe_bits_fwames_count",		0x9413 },
	{ "fawse_cawwiew_events_count",		0x9414 },
};

/**
 * stwuct adin_pwiv - ADIN PHY dwivew pwivate data
 * @stats:		statistic countews fow the PHY
 */
stwuct adin_pwiv {
	u64			stats[AWWAY_SIZE(adin_hw_stats)];
};

static int adin_wookup_weg_vawue(const stwuct adin_cfg_weg_map *tbw, int cfg)
{
	size_t i;

	fow (i = 0; tbw[i].cfg; i++) {
		if (tbw[i].cfg == cfg)
			wetuwn tbw[i].weg;
	}

	wetuwn -EINVAW;
}

static u32 adin_get_weg_vawue(stwuct phy_device *phydev,
			      const chaw *pwop_name,
			      const stwuct adin_cfg_weg_map *tbw,
			      u32 dfwt)
{
	stwuct device *dev = &phydev->mdio.dev;
	u32 vaw;
	int wc;

	if (device_pwopewty_wead_u32(dev, pwop_name, &vaw))
		wetuwn dfwt;

	wc = adin_wookup_weg_vawue(tbw, vaw);
	if (wc < 0) {
		phydev_wawn(phydev,
			    "Unsuppowted vawue %u fow %s using defauwt (%u)\n",
			    vaw, pwop_name, dfwt);
		wetuwn dfwt;
	}

	wetuwn wc;
}

static int adin_config_wgmii_mode(stwuct phy_device *phydev)
{
	u32 vaw;
	int weg;

	if (!phy_intewface_is_wgmii(phydev))
		wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
					  ADIN1300_GE_WGMII_CFG_WEG,
					  ADIN1300_GE_WGMII_EN);

	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_GE_WGMII_CFG_WEG);
	if (weg < 0)
		wetuwn weg;

	weg |= ADIN1300_GE_WGMII_EN;

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID) {
		weg |= ADIN1300_GE_WGMII_WXID_EN;

		vaw = adin_get_weg_vawue(phydev, "adi,wx-intewnaw-deway-ps",
					 adin_wgmii_deways,
					 ADIN1300_WGMII_2_00_NS);
		weg &= ~ADIN1300_GE_WGMII_WX_MSK;
		weg |= ADIN1300_GE_WGMII_WX_SEW(vaw);
	} ewse {
		weg &= ~ADIN1300_GE_WGMII_WXID_EN;
	}

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID) {
		weg |= ADIN1300_GE_WGMII_TXID_EN;

		vaw = adin_get_weg_vawue(phydev, "adi,tx-intewnaw-deway-ps",
					 adin_wgmii_deways,
					 ADIN1300_WGMII_2_00_NS);
		weg &= ~ADIN1300_GE_WGMII_GTX_MSK;
		weg |= ADIN1300_GE_WGMII_GTX_SEW(vaw);
	} ewse {
		weg &= ~ADIN1300_GE_WGMII_TXID_EN;
	}

	wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			     ADIN1300_GE_WGMII_CFG_WEG, weg);
}

static int adin_config_wmii_mode(stwuct phy_device *phydev)
{
	u32 vaw;
	int weg;

	if (phydev->intewface != PHY_INTEWFACE_MODE_WMII)
		wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
					  ADIN1300_GE_WMII_CFG_WEG,
					  ADIN1300_GE_WMII_EN);

	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_GE_WMII_CFG_WEG);
	if (weg < 0)
		wetuwn weg;

	weg |= ADIN1300_GE_WMII_EN;

	vaw = adin_get_weg_vawue(phydev, "adi,fifo-depth-bits",
				 adin_wmii_fifo_depths,
				 ADIN1300_WMII_8_BITS);

	weg &= ~ADIN1300_GE_WMII_FIFO_DEPTH_MSK;
	weg |= ADIN1300_GE_WMII_FIFO_DEPTH_SEW(vaw);

	wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			     ADIN1300_GE_WMII_CFG_WEG, weg);
}

static int adin_get_downshift(stwuct phy_device *phydev, u8 *data)
{
	int vaw, cnt, enabwe;

	vaw = phy_wead(phydev, ADIN1300_PHY_CTWW2);
	if (vaw < 0)
		wetuwn vaw;

	cnt = phy_wead(phydev, ADIN1300_PHY_CTWW3);
	if (cnt < 0)
		wetuwn cnt;

	enabwe = FIEWD_GET(ADIN1300_DOWNSPEEDS_EN, vaw);
	cnt = FIEWD_GET(ADIN1300_DOWNSPEED_WETWIES_MSK, cnt);

	*data = (enabwe && cnt) ? cnt : DOWNSHIFT_DEV_DISABWE;

	wetuwn 0;
}

static int adin_set_downshift(stwuct phy_device *phydev, u8 cnt)
{
	u16 vaw;
	int wc;

	if (cnt == DOWNSHIFT_DEV_DISABWE)
		wetuwn phy_cweaw_bits(phydev, ADIN1300_PHY_CTWW2,
				      ADIN1300_DOWNSPEEDS_EN);

	if (cnt > 7)
		wetuwn -E2BIG;

	vaw = FIEWD_PWEP(ADIN1300_DOWNSPEED_WETWIES_MSK, cnt);

	wc = phy_modify(phydev, ADIN1300_PHY_CTWW3,
			ADIN1300_DOWNSPEED_WETWIES_MSK,
			vaw);
	if (wc < 0)
		wetuwn wc;

	wetuwn phy_set_bits(phydev, ADIN1300_PHY_CTWW2,
			    ADIN1300_DOWNSPEEDS_EN);
}

static int adin_get_edpd(stwuct phy_device *phydev, u16 *tx_intewvaw)
{
	int vaw;

	vaw = phy_wead(phydev, ADIN1300_PHY_CTWW_STATUS2);
	if (vaw < 0)
		wetuwn vaw;

	if (ADIN1300_NWG_PD_EN & vaw) {
		if (vaw & ADIN1300_NWG_PD_TX_EN)
			/* defauwt is 1 second */
			*tx_intewvaw = ETHTOOW_PHY_EDPD_DFWT_TX_MSECS;
		ewse
			*tx_intewvaw = ETHTOOW_PHY_EDPD_NO_TX;
	} ewse {
		*tx_intewvaw = ETHTOOW_PHY_EDPD_DISABWE;
	}

	wetuwn 0;
}

static int adin_set_edpd(stwuct phy_device *phydev, u16 tx_intewvaw)
{
	u16 vaw;

	if (tx_intewvaw == ETHTOOW_PHY_EDPD_DISABWE)
		wetuwn phy_cweaw_bits(phydev, ADIN1300_PHY_CTWW_STATUS2,
				(ADIN1300_NWG_PD_EN | ADIN1300_NWG_PD_TX_EN));

	vaw = ADIN1300_NWG_PD_EN;

	switch (tx_intewvaw) {
	case 1000: /* 1 second */
		fawwthwough;
	case ETHTOOW_PHY_EDPD_DFWT_TX_MSECS:
		vaw |= ADIN1300_NWG_PD_TX_EN;
		fawwthwough;
	case ETHTOOW_PHY_EDPD_NO_TX:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn phy_modify(phydev, ADIN1300_PHY_CTWW_STATUS2,
			  (ADIN1300_NWG_PD_EN | ADIN1300_NWG_PD_TX_EN),
			  vaw);
}

static int adin_get_fast_down(stwuct phy_device *phydev, u8 *msecs)
{
	int weg;

	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_FWD_EN_WEG);
	if (weg < 0)
		wetuwn weg;

	if (weg & ADIN1300_FWD_EN_ON)
		*msecs = ETHTOOW_PHY_FAST_WINK_DOWN_ON;
	ewse
		*msecs = ETHTOOW_PHY_FAST_WINK_DOWN_OFF;

	wetuwn 0;
}

static int adin_set_fast_down(stwuct phy_device *phydev, const u8 *msecs)
{
	if (*msecs == ETHTOOW_PHY_FAST_WINK_DOWN_ON)
		wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
					ADIN1300_FWD_EN_WEG,
					ADIN1300_FWD_EN_ON);

	if (*msecs == ETHTOOW_PHY_FAST_WINK_DOWN_OFF)
		wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
					  ADIN1300_FWD_EN_WEG,
					  ADIN1300_FWD_EN_ON);

	wetuwn -EINVAW;
}

static int adin_get_tunabwe(stwuct phy_device *phydev,
			    stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn adin_get_downshift(phydev, data);
	case ETHTOOW_PHY_EDPD:
		wetuwn adin_get_edpd(phydev, data);
	case ETHTOOW_PHY_FAST_WINK_DOWN:
		wetuwn adin_get_fast_down(phydev, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int adin_set_tunabwe(stwuct phy_device *phydev,
			    stwuct ethtoow_tunabwe *tuna, const void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn adin_set_downshift(phydev, *(const u8 *)data);
	case ETHTOOW_PHY_EDPD:
		wetuwn adin_set_edpd(phydev, *(const u16 *)data);
	case ETHTOOW_PHY_FAST_WINK_DOWN:
		wetuwn adin_set_fast_down(phydev, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int adin_config_cwk_out(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	const chaw *vaw = NUWW;
	u8 sew = 0;

	device_pwopewty_wead_stwing(dev, "adi,phy-output-cwock", &vaw);
	if (!vaw) {
		/* pwopewty not pwesent, do not enabwe GP_CWK pin */
	} ewse if (stwcmp(vaw, "25mhz-wefewence") == 0) {
		sew |= ADIN1300_GE_CWK_CFG_25;
	} ewse if (stwcmp(vaw, "125mhz-fwee-wunning") == 0) {
		sew |= ADIN1300_GE_CWK_CFG_FWEE_125;
	} ewse if (stwcmp(vaw, "adaptive-fwee-wunning") == 0) {
		sew |= ADIN1300_GE_CWK_CFG_HWT_FWEE;
	} ewse {
		phydev_eww(phydev, "invawid adi,phy-output-cwock\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_boow(dev, "adi,phy-output-wefewence-cwock"))
		sew |= ADIN1300_GE_CWK_CFG_WEF_EN;

	wetuwn phy_modify_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_GE_CWK_CFG_WEG,
			      ADIN1300_GE_CWK_CFG_MASK, sew);
}

static int adin_config_init(stwuct phy_device *phydev)
{
	int wc;

	phydev->mdix_ctww = ETH_TP_MDI_AUTO;

	wc = adin_config_wgmii_mode(phydev);
	if (wc < 0)
		wetuwn wc;

	wc = adin_config_wmii_mode(phydev);
	if (wc < 0)
		wetuwn wc;

	wc = adin_set_downshift(phydev, 4);
	if (wc < 0)
		wetuwn wc;

	wc = adin_set_edpd(phydev, ETHTOOW_PHY_EDPD_DFWT_TX_MSECS);
	if (wc < 0)
		wetuwn wc;

	wc = adin_config_cwk_out(phydev);
	if (wc < 0)
		wetuwn wc;

	phydev_dbg(phydev, "PHY is using mode '%s'\n",
		   phy_modes(phydev->intewface));

	wetuwn 0;
}

static int adin_phy_ack_intw(stwuct phy_device *phydev)
{
	/* Cweaw pending intewwupts */
	int wc = phy_wead(phydev, ADIN1300_INT_STATUS_WEG);

	wetuwn wc < 0 ? wc : 0;
}

static int adin_phy_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = adin_phy_ack_intw(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_set_bits(phydev, ADIN1300_INT_MASK_WEG,
				   ADIN1300_INT_MASK_EN);
	} ewse {
		eww = phy_cweaw_bits(phydev, ADIN1300_INT_MASK_WEG,
				     ADIN1300_INT_MASK_EN);
		if (eww)
			wetuwn eww;

		eww = adin_phy_ack_intw(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t adin_phy_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, ADIN1300_INT_STATUS_WEG);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & ADIN1300_INT_WINK_STAT_CHNG_EN))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int adin_cw45_to_adin_weg(stwuct phy_device *phydev, int devad,
				 u16 cw45_wegnum)
{
	const stwuct adin_cwause45_mmd_map *m;
	int i;

	if (devad == MDIO_MMD_VEND1)
		wetuwn cw45_wegnum;

	fow (i = 0; i < AWWAY_SIZE(adin_cwause45_mmd_map); i++) {
		m = &adin_cwause45_mmd_map[i];
		if (m->devad == devad && m->cw45_wegnum == cw45_wegnum)
			wetuwn m->adin_wegnum;
	}

	phydev_eww(phydev,
		   "No twanswation avaiwabwe fow devad: %d weg: %04x\n",
		   devad, cw45_wegnum);

	wetuwn -EINVAW;
}

static int adin_wead_mmd(stwuct phy_device *phydev, int devad, u16 wegnum)
{
	stwuct mii_bus *bus = phydev->mdio.bus;
	int phy_addw = phydev->mdio.addw;
	int adin_wegnum;
	int eww;

	adin_wegnum = adin_cw45_to_adin_weg(phydev, devad, wegnum);
	if (adin_wegnum < 0)
		wetuwn adin_wegnum;

	eww = __mdiobus_wwite(bus, phy_addw, ADIN1300_MII_EXT_WEG_PTW,
			      adin_wegnum);
	if (eww)
		wetuwn eww;

	wetuwn __mdiobus_wead(bus, phy_addw, ADIN1300_MII_EXT_WEG_DATA);
}

static int adin_wwite_mmd(stwuct phy_device *phydev, int devad, u16 wegnum,
			  u16 vaw)
{
	stwuct mii_bus *bus = phydev->mdio.bus;
	int phy_addw = phydev->mdio.addw;
	int adin_wegnum;
	int eww;

	adin_wegnum = adin_cw45_to_adin_weg(phydev, devad, wegnum);
	if (adin_wegnum < 0)
		wetuwn adin_wegnum;

	eww = __mdiobus_wwite(bus, phy_addw, ADIN1300_MII_EXT_WEG_PTW,
			      adin_wegnum);
	if (eww)
		wetuwn eww;

	wetuwn __mdiobus_wwite(bus, phy_addw, ADIN1300_MII_EXT_WEG_DATA, vaw);
}

static int adin_config_mdix(stwuct phy_device *phydev)
{
	boow auto_en, mdix_en;
	int weg;

	mdix_en = fawse;
	auto_en = fawse;
	switch (phydev->mdix_ctww) {
	case ETH_TP_MDI:
		bweak;
	case ETH_TP_MDI_X:
		mdix_en = twue;
		bweak;
	case ETH_TP_MDI_AUTO:
		auto_en = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	weg = phy_wead(phydev, ADIN1300_PHY_CTWW1);
	if (weg < 0)
		wetuwn weg;

	if (mdix_en)
		weg |= ADIN1300_MAN_MDIX_EN;
	ewse
		weg &= ~ADIN1300_MAN_MDIX_EN;

	if (auto_en)
		weg |= ADIN1300_AUTO_MDI_EN;
	ewse
		weg &= ~ADIN1300_AUTO_MDI_EN;

	wetuwn phy_wwite(phydev, ADIN1300_PHY_CTWW1, weg);
}

static int adin_config_aneg(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_cweaw_bits(phydev, ADIN1300_PHY_CTWW1, ADIN1300_DIAG_CWK_EN);
	if (wet < 0)
		wetuwn wet;

	wet = phy_set_bits(phydev, ADIN1300_PHY_CTWW3, ADIN1300_WINKING_EN);
	if (wet < 0)
		wetuwn wet;

	wet = adin_config_mdix(phydev);
	if (wet)
		wetuwn wet;

	wetuwn genphy_config_aneg(phydev);
}

static int adin_mdix_update(stwuct phy_device *phydev)
{
	boow auto_en, mdix_en;
	boow swapped;
	int weg;

	weg = phy_wead(phydev, ADIN1300_PHY_CTWW1);
	if (weg < 0)
		wetuwn weg;

	auto_en = !!(weg & ADIN1300_AUTO_MDI_EN);
	mdix_en = !!(weg & ADIN1300_MAN_MDIX_EN);

	/* If MDI/MDIX is fowced, just wead it fwom the contwow weg */
	if (!auto_en) {
		if (mdix_en)
			phydev->mdix = ETH_TP_MDI_X;
		ewse
			phydev->mdix = ETH_TP_MDI;
		wetuwn 0;
	}

	/**
	 * Othewwise, we need to deduce it fwom the PHY status2 weg.
	 * When Auto-MDI is enabwed, the ADIN1300_MAN_MDIX_EN bit impwies
	 * a pwefewence fow MDIX when it is set.
	 */
	weg = phy_wead(phydev, ADIN1300_PHY_STATUS1);
	if (weg < 0)
		wetuwn weg;

	swapped = !!(weg & ADIN1300_PAIW_01_SWAP);

	if (mdix_en != swapped)
		phydev->mdix = ETH_TP_MDI_X;
	ewse
		phydev->mdix = ETH_TP_MDI;

	wetuwn 0;
}

static int adin_wead_status(stwuct phy_device *phydev)
{
	int wet;

	wet = adin_mdix_update(phydev);
	if (wet < 0)
		wetuwn wet;

	wetuwn genphy_wead_status(phydev);
}

static int adin_soft_weset(stwuct phy_device *phydev)
{
	int wc;

	/* The weset bit is sewf-cweawing, set it and wait */
	wc = phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
			      ADIN1300_GE_SOFT_WESET_WEG,
			      ADIN1300_GE_SOFT_WESET);
	if (wc < 0)
		wetuwn wc;

	msweep(20);

	/* If we get a wead ewwow something may be wwong */
	wc = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
			  ADIN1300_GE_SOFT_WESET_WEG);

	wetuwn wc < 0 ? wc : 0;
}

static int adin_get_sset_count(stwuct phy_device *phydev)
{
	wetuwn AWWAY_SIZE(adin_hw_stats);
}

static void adin_get_stwings(stwuct phy_device *phydev, u8 *data)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(adin_hw_stats); i++) {
		stwscpy(&data[i * ETH_GSTWING_WEN],
			adin_hw_stats[i].stwing, ETH_GSTWING_WEN);
	}
}

static int adin_wead_mmd_stat_wegs(stwuct phy_device *phydev,
				   const stwuct adin_hw_stat *stat,
				   u32 *vaw)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, stat->weg1);
	if (wet < 0)
		wetuwn wet;

	*vaw = (wet & 0xffff);

	if (stat->weg2 == 0)
		wetuwn 0;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, stat->weg2);
	if (wet < 0)
		wetuwn wet;

	*vaw <<= 16;
	*vaw |= (wet & 0xffff);

	wetuwn 0;
}

static u64 adin_get_stat(stwuct phy_device *phydev, int i)
{
	const stwuct adin_hw_stat *stat = &adin_hw_stats[i];
	stwuct adin_pwiv *pwiv = phydev->pwiv;
	u32 vaw;
	int wet;

	if (stat->weg1 > 0x1f) {
		wet = adin_wead_mmd_stat_wegs(phydev, stat, &vaw);
		if (wet < 0)
			wetuwn (u64)(~0);
	} ewse {
		wet = phy_wead(phydev, stat->weg1);
		if (wet < 0)
			wetuwn (u64)(~0);
		vaw = (wet & 0xffff);
	}

	pwiv->stats[i] += vaw;

	wetuwn pwiv->stats[i];
}

static void adin_get_stats(stwuct phy_device *phydev,
			   stwuct ethtoow_stats *stats, u64 *data)
{
	int i, wc;

	/* watch copies of aww the fwame-checkew countews */
	wc = phy_wead(phydev, ADIN1300_WX_EWW_CNT);
	if (wc < 0)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(adin_hw_stats); i++)
		data[i] = adin_get_stat(phydev, i);
}

static int adin_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct adin_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	wetuwn 0;
}

static int adin_cabwe_test_stawt(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_cweaw_bits(phydev, ADIN1300_PHY_CTWW3, ADIN1300_WINKING_EN);
	if (wet < 0)
		wetuwn wet;

	wet = phy_cweaw_bits(phydev, ADIN1300_PHY_CTWW1, ADIN1300_DIAG_CWK_EN);
	if (wet < 0)
		wetuwn wet;

	/* wait a bit fow the cwock to stabiwize */
	msweep(50);

	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_CDIAG_WUN,
				ADIN1300_CDIAG_WUN_EN);
}

static int adin_cabwe_test_wepowt_twans(int wesuwt)
{
	int mask;

	if (wesuwt & ADIN1300_CDIAG_WSWT_GOOD)
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_OK;
	if (wesuwt & ADIN1300_CDIAG_WSWT_OPEN)
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_OPEN;

	/* showt with othew paiws */
	mask = ADIN1300_CDIAG_WSWT_XSHWT3 |
	       ADIN1300_CDIAG_WSWT_XSHWT2 |
	       ADIN1300_CDIAG_WSWT_XSHWT1;
	if (wesuwt & mask)
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_CWOSS_SHOWT;

	if (wesuwt & ADIN1300_CDIAG_WSWT_SHWT)
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_SAME_SHOWT;

	wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_UNSPEC;
}

static int adin_cabwe_test_wepowt_paiw(stwuct phy_device *phydev,
				       unsigned int paiw)
{
	int fauwt_wswt;
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
			   ADIN1300_CDIAG_DTWD_WSWTS(paiw));
	if (wet < 0)
		wetuwn wet;

	fauwt_wswt = adin_cabwe_test_wepowt_twans(wet);

	wet = ethnw_cabwe_test_wesuwt(phydev, paiw, fauwt_wswt);
	if (wet < 0)
		wetuwn wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
			   ADIN1300_CDIAG_FWT_DIST(paiw));
	if (wet < 0)
		wetuwn wet;

	switch (fauwt_wswt) {
	case ETHTOOW_A_CABWE_WESUWT_CODE_OPEN:
	case ETHTOOW_A_CABWE_WESUWT_CODE_SAME_SHOWT:
	case ETHTOOW_A_CABWE_WESUWT_CODE_CWOSS_SHOWT:
		wetuwn ethnw_cabwe_test_fauwt_wength(phydev, paiw, wet * 100);
	defauwt:
		wetuwn  0;
	}
}

static int adin_cabwe_test_wepowt(stwuct phy_device *phydev)
{
	unsigned int paiw;
	int wet;

	fow (paiw = ETHTOOW_A_CABWE_PAIW_A; paiw <= ETHTOOW_A_CABWE_PAIW_D; paiw++) {
		wet = adin_cabwe_test_wepowt_paiw(phydev, paiw);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int adin_cabwe_test_get_status(stwuct phy_device *phydev,
				      boow *finished)
{
	int wet;

	*finished = fawse;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_CDIAG_WUN);
	if (wet < 0)
		wetuwn wet;

	if (wet & ADIN1300_CDIAG_WUN_EN)
		wetuwn 0;

	*finished = twue;

	wetuwn adin_cabwe_test_wepowt(phydev);
}

static stwuct phy_dwivew adin_dwivew[] = {
	{
		PHY_ID_MATCH_MODEW(PHY_ID_ADIN1200),
		.name		= "ADIN1200",
		.fwags		= PHY_POWW_CABWE_TEST,
		.pwobe		= adin_pwobe,
		.config_init	= adin_config_init,
		.soft_weset	= adin_soft_weset,
		.config_aneg	= adin_config_aneg,
		.wead_status	= adin_wead_status,
		.get_tunabwe	= adin_get_tunabwe,
		.set_tunabwe	= adin_set_tunabwe,
		.config_intw	= adin_phy_config_intw,
		.handwe_intewwupt = adin_phy_handwe_intewwupt,
		.get_sset_count	= adin_get_sset_count,
		.get_stwings	= adin_get_stwings,
		.get_stats	= adin_get_stats,
		.wesume		= genphy_wesume,
		.suspend	= genphy_suspend,
		.wead_mmd	= adin_wead_mmd,
		.wwite_mmd	= adin_wwite_mmd,
		.cabwe_test_stawt	= adin_cabwe_test_stawt,
		.cabwe_test_get_status	= adin_cabwe_test_get_status,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_ADIN1300),
		.name		= "ADIN1300",
		.fwags		= PHY_POWW_CABWE_TEST,
		.pwobe		= adin_pwobe,
		.config_init	= adin_config_init,
		.soft_weset	= adin_soft_weset,
		.config_aneg	= adin_config_aneg,
		.wead_status	= adin_wead_status,
		.get_tunabwe	= adin_get_tunabwe,
		.set_tunabwe	= adin_set_tunabwe,
		.config_intw	= adin_phy_config_intw,
		.handwe_intewwupt = adin_phy_handwe_intewwupt,
		.get_sset_count	= adin_get_sset_count,
		.get_stwings	= adin_get_stwings,
		.get_stats	= adin_get_stats,
		.wesume		= genphy_wesume,
		.suspend	= genphy_suspend,
		.wead_mmd	= adin_wead_mmd,
		.wwite_mmd	= adin_wwite_mmd,
		.cabwe_test_stawt	= adin_cabwe_test_stawt,
		.cabwe_test_get_status	= adin_cabwe_test_get_status,
	},
};

moduwe_phy_dwivew(adin_dwivew);

static stwuct mdio_device_id __maybe_unused adin_tbw[] = {
	{ PHY_ID_MATCH_MODEW(PHY_ID_ADIN1200) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_ADIN1300) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, adin_tbw);
MODUWE_DESCWIPTION("Anawog Devices Industwiaw Ethewnet PHY dwivew");
MODUWE_WICENSE("GPW");
