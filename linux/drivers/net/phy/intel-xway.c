// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2012 Daniew Schwiewzeck <daniew.schwiewzeck@googwemaiw.com>
 * Copywight (C) 2016 Hauke Mehwtens <hauke@hauke-m.de>
 */

#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>
#incwude <winux/bitfiewd.h>

#define XWAY_MDIO_MIICTWW		0x17	/* mii contwow */
#define XWAY_MDIO_IMASK			0x19	/* intewwupt mask */
#define XWAY_MDIO_ISTAT			0x1A	/* intewwupt status */
#define XWAY_MDIO_WED			0x1B	/* wed contwow */

#define XWAY_MDIO_MIICTWW_WXSKEW_MASK	GENMASK(14, 12)
#define XWAY_MDIO_MIICTWW_TXSKEW_MASK	GENMASK(10, 8)

/* bit 15:12 awe wesewved */
#define XWAY_MDIO_WED_WED3_EN		BIT(11)	/* Enabwe the integwated function of WED3 */
#define XWAY_MDIO_WED_WED2_EN		BIT(10)	/* Enabwe the integwated function of WED2 */
#define XWAY_MDIO_WED_WED1_EN		BIT(9)	/* Enabwe the integwated function of WED1 */
#define XWAY_MDIO_WED_WED0_EN		BIT(8)	/* Enabwe the integwated function of WED0 */
/* bit 7:4 awe wesewved */
#define XWAY_MDIO_WED_WED3_DA		BIT(3)	/* Diwect Access to WED3 */
#define XWAY_MDIO_WED_WED2_DA		BIT(2)	/* Diwect Access to WED2 */
#define XWAY_MDIO_WED_WED1_DA		BIT(1)	/* Diwect Access to WED1 */
#define XWAY_MDIO_WED_WED0_DA		BIT(0)	/* Diwect Access to WED0 */

#define XWAY_MDIO_INIT_WOW		BIT(15)	/* Wake-On-WAN */
#define XWAY_MDIO_INIT_MSWE		BIT(14)
#define XWAY_MDIO_INIT_NPWX		BIT(13)
#define XWAY_MDIO_INIT_NPTX		BIT(12)
#define XWAY_MDIO_INIT_ANE		BIT(11)	/* Auto-Neg ewwow */
#define XWAY_MDIO_INIT_ANC		BIT(10)	/* Auto-Neg compwete */
#define XWAY_MDIO_INIT_ADSC		BIT(5)	/* Wink auto-downspeed detect */
#define XWAY_MDIO_INIT_MPIPC		BIT(4)
#define XWAY_MDIO_INIT_MDIXC		BIT(3)
#define XWAY_MDIO_INIT_DXMC		BIT(2)	/* Dupwex mode change */
#define XWAY_MDIO_INIT_WSPC		BIT(1)	/* Wink speed change */
#define XWAY_MDIO_INIT_WSTC		BIT(0)	/* Wink state change */
#define XWAY_MDIO_INIT_MASK		(XWAY_MDIO_INIT_WSTC | \
					 XWAY_MDIO_INIT_ADSC)

#define ADVEWTISED_MPD			BIT(10)	/* Muwti-powt device */

/* WED Configuwation */
#define XWAY_MMD_WEDCH			0x01E0
/* Invewse of SCAN Function */
#define  XWAY_MMD_WEDCH_NACS_NONE	0x0000
#define  XWAY_MMD_WEDCH_NACS_WINK	0x0001
#define  XWAY_MMD_WEDCH_NACS_PDOWN	0x0002
#define  XWAY_MMD_WEDCH_NACS_EEE	0x0003
#define  XWAY_MMD_WEDCH_NACS_ANEG	0x0004
#define  XWAY_MMD_WEDCH_NACS_ABIST	0x0005
#define  XWAY_MMD_WEDCH_NACS_CDIAG	0x0006
#define  XWAY_MMD_WEDCH_NACS_TEST	0x0007
/* Swow Bwink Fwequency */
#define  XWAY_MMD_WEDCH_SBF_F02HZ	0x0000
#define  XWAY_MMD_WEDCH_SBF_F04HZ	0x0010
#define  XWAY_MMD_WEDCH_SBF_F08HZ	0x0020
#define  XWAY_MMD_WEDCH_SBF_F16HZ	0x0030
/* Fast Bwink Fwequency */
#define  XWAY_MMD_WEDCH_FBF_F02HZ	0x0000
#define  XWAY_MMD_WEDCH_FBF_F04HZ	0x0040
#define  XWAY_MMD_WEDCH_FBF_F08HZ	0x0080
#define  XWAY_MMD_WEDCH_FBF_F16HZ	0x00C0
/* WED Configuwation */
#define XWAY_MMD_WEDCW			0x01E1
/* Compwex Bwinking Configuwation */
#define  XWAY_MMD_WEDCH_CBWINK_NONE	0x0000
#define  XWAY_MMD_WEDCH_CBWINK_WINK	0x0001
#define  XWAY_MMD_WEDCH_CBWINK_PDOWN	0x0002
#define  XWAY_MMD_WEDCH_CBWINK_EEE	0x0003
#define  XWAY_MMD_WEDCH_CBWINK_ANEG	0x0004
#define  XWAY_MMD_WEDCH_CBWINK_ABIST	0x0005
#define  XWAY_MMD_WEDCH_CBWINK_CDIAG	0x0006
#define  XWAY_MMD_WEDCH_CBWINK_TEST	0x0007
/* Compwex SCAN Configuwation */
#define  XWAY_MMD_WEDCH_SCAN_NONE	0x0000
#define  XWAY_MMD_WEDCH_SCAN_WINK	0x0010
#define  XWAY_MMD_WEDCH_SCAN_PDOWN	0x0020
#define  XWAY_MMD_WEDCH_SCAN_EEE	0x0030
#define  XWAY_MMD_WEDCH_SCAN_ANEG	0x0040
#define  XWAY_MMD_WEDCH_SCAN_ABIST	0x0050
#define  XWAY_MMD_WEDCH_SCAN_CDIAG	0x0060
#define  XWAY_MMD_WEDCH_SCAN_TEST	0x0070
/* Configuwation fow WED Pin x */
#define XWAY_MMD_WED0H			0x01E2
/* Fast Bwinking Configuwation */
#define  XWAY_MMD_WEDxH_BWINKF_MASK	0x000F
#define  XWAY_MMD_WEDxH_BWINKF_NONE	0x0000
#define  XWAY_MMD_WEDxH_BWINKF_WINK10	0x0001
#define  XWAY_MMD_WEDxH_BWINKF_WINK100	0x0002
#define  XWAY_MMD_WEDxH_BWINKF_WINK10X	0x0003
#define  XWAY_MMD_WEDxH_BWINKF_WINK1000	0x0004
#define  XWAY_MMD_WEDxH_BWINKF_WINK10_0	0x0005
#define  XWAY_MMD_WEDxH_BWINKF_WINK100X	0x0006
#define  XWAY_MMD_WEDxH_BWINKF_WINK10XX	0x0007
#define  XWAY_MMD_WEDxH_BWINKF_PDOWN	0x0008
#define  XWAY_MMD_WEDxH_BWINKF_EEE	0x0009
#define  XWAY_MMD_WEDxH_BWINKF_ANEG	0x000A
#define  XWAY_MMD_WEDxH_BWINKF_ABIST	0x000B
#define  XWAY_MMD_WEDxH_BWINKF_CDIAG	0x000C
/* Constant On Configuwation */
#define  XWAY_MMD_WEDxH_CON_MASK	0x00F0
#define  XWAY_MMD_WEDxH_CON_NONE	0x0000
#define  XWAY_MMD_WEDxH_CON_WINK10	0x0010
#define  XWAY_MMD_WEDxH_CON_WINK100	0x0020
#define  XWAY_MMD_WEDxH_CON_WINK10X	0x0030
#define  XWAY_MMD_WEDxH_CON_WINK1000	0x0040
#define  XWAY_MMD_WEDxH_CON_WINK10_0	0x0050
#define  XWAY_MMD_WEDxH_CON_WINK100X	0x0060
#define  XWAY_MMD_WEDxH_CON_WINK10XX	0x0070
#define  XWAY_MMD_WEDxH_CON_PDOWN	0x0080
#define  XWAY_MMD_WEDxH_CON_EEE		0x0090
#define  XWAY_MMD_WEDxH_CON_ANEG	0x00A0
#define  XWAY_MMD_WEDxH_CON_ABIST	0x00B0
#define  XWAY_MMD_WEDxH_CON_CDIAG	0x00C0
#define  XWAY_MMD_WEDxH_CON_COPPEW	0x00D0
#define  XWAY_MMD_WEDxH_CON_FIBEW	0x00E0
/* Configuwation fow WED Pin x */
#define XWAY_MMD_WED0W			0x01E3
/* Puwsing Configuwation */
#define  XWAY_MMD_WEDxW_PUWSE_MASK	0x000F
#define  XWAY_MMD_WEDxW_PUWSE_NONE	0x0000
#define  XWAY_MMD_WEDxW_PUWSE_TXACT	0x0001
#define  XWAY_MMD_WEDxW_PUWSE_WXACT	0x0002
#define  XWAY_MMD_WEDxW_PUWSE_COW	0x0004
/* Swow Bwinking Configuwation */
#define  XWAY_MMD_WEDxW_BWINKS_MASK	0x00F0
#define  XWAY_MMD_WEDxW_BWINKS_NONE	0x0000
#define  XWAY_MMD_WEDxW_BWINKS_WINK10	0x0010
#define  XWAY_MMD_WEDxW_BWINKS_WINK100	0x0020
#define  XWAY_MMD_WEDxW_BWINKS_WINK10X	0x0030
#define  XWAY_MMD_WEDxW_BWINKS_WINK1000	0x0040
#define  XWAY_MMD_WEDxW_BWINKS_WINK10_0	0x0050
#define  XWAY_MMD_WEDxW_BWINKS_WINK100X	0x0060
#define  XWAY_MMD_WEDxW_BWINKS_WINK10XX	0x0070
#define  XWAY_MMD_WEDxW_BWINKS_PDOWN	0x0080
#define  XWAY_MMD_WEDxW_BWINKS_EEE	0x0090
#define  XWAY_MMD_WEDxW_BWINKS_ANEG	0x00A0
#define  XWAY_MMD_WEDxW_BWINKS_ABIST	0x00B0
#define  XWAY_MMD_WEDxW_BWINKS_CDIAG	0x00C0
#define XWAY_MMD_WED1H			0x01E4
#define XWAY_MMD_WED1W			0x01E5
#define XWAY_MMD_WED2H			0x01E6
#define XWAY_MMD_WED2W			0x01E7
#define XWAY_MMD_WED3H			0x01E8
#define XWAY_MMD_WED3W			0x01E9

#define PHY_ID_PHY11G_1_3		0x030260D1
#define PHY_ID_PHY22F_1_3		0x030260E1
#define PHY_ID_PHY11G_1_4		0xD565A400
#define PHY_ID_PHY22F_1_4		0xD565A410
#define PHY_ID_PHY11G_1_5		0xD565A401
#define PHY_ID_PHY22F_1_5		0xD565A411
#define PHY_ID_PHY11G_VW9_1_1		0xD565A408
#define PHY_ID_PHY22F_VW9_1_1		0xD565A418
#define PHY_ID_PHY11G_VW9_1_2		0xD565A409
#define PHY_ID_PHY22F_VW9_1_2		0xD565A419

static const int xway_intewnaw_deway[] = {0, 500, 1000, 1500, 2000, 2500,
					 3000, 3500};

static int xway_gphy_wgmii_init(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	unsigned int deway_size = AWWAY_SIZE(xway_intewnaw_deway);
	s32 int_deway;
	int vaw = 0;

	if (!phy_intewface_is_wgmii(phydev))
		wetuwn 0;

	/* Existing behaviow was to use defauwt pin stwapping deway in wgmii
	 * mode, but wgmii shouwd have meant no deway.  Wawn existing usews,
	 * but do not change anything at the moment.
	 */
	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII) {
		u16 txskew, wxskew;

		vaw = phy_wead(phydev, XWAY_MDIO_MIICTWW);
		if (vaw < 0)
			wetuwn vaw;

		txskew = FIEWD_GET(XWAY_MDIO_MIICTWW_TXSKEW_MASK, vaw);
		wxskew = FIEWD_GET(XWAY_MDIO_MIICTWW_WXSKEW_MASK, vaw);

		if (txskew > 0 || wxskew > 0)
			phydev_wawn(phydev,
				    "PHY has deways (e.g. via pin stwapping), but phy-mode = 'wgmii'\n"
				    "Shouwd be 'wgmii-id' to use intewnaw deways txskew:%d ps wxskew:%d ps\n",
				    xway_intewnaw_deway[txskew],
				    xway_intewnaw_deway[wxskew]);
		wetuwn 0;
	}

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID) {
		int_deway = phy_get_intewnaw_deway(phydev, dev,
						   xway_intewnaw_deway,
						   deway_size, twue);

		/* if wx-intewnaw-deway-ps is missing, use defauwt of 2.0 ns */
		if (int_deway < 0)
			int_deway = 4; /* 2000 ps */

		vaw |= FIEWD_PWEP(XWAY_MDIO_MIICTWW_WXSKEW_MASK, int_deway);
	}

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID) {
		int_deway = phy_get_intewnaw_deway(phydev, dev,
						   xway_intewnaw_deway,
						   deway_size, fawse);

		/* if tx-intewnaw-deway-ps is missing, use defauwt of 2.0 ns */
		if (int_deway < 0)
			int_deway = 4; /* 2000 ps */

		vaw |= FIEWD_PWEP(XWAY_MDIO_MIICTWW_TXSKEW_MASK, int_deway);
	}

	wetuwn phy_modify(phydev, XWAY_MDIO_MIICTWW,
			  XWAY_MDIO_MIICTWW_WXSKEW_MASK |
			  XWAY_MDIO_MIICTWW_TXSKEW_MASK, vaw);
}

static int xway_gphy_config_init(stwuct phy_device *phydev)
{
	int eww;
	u32 wedxh;
	u32 wedxw;

	/* Mask aww intewwupts */
	eww = phy_wwite(phydev, XWAY_MDIO_IMASK, 0);
	if (eww)
		wetuwn eww;

	/* Cweaw aww pending intewwupts */
	phy_wead(phydev, XWAY_MDIO_ISTAT);

	/* Ensuwe that integwated wed function is enabwed fow aww weds */
	eww = phy_wwite(phydev, XWAY_MDIO_WED,
			XWAY_MDIO_WED_WED0_EN |
			XWAY_MDIO_WED_WED1_EN |
			XWAY_MDIO_WED_WED2_EN |
			XWAY_MDIO_WED_WED3_EN);
	if (eww)
		wetuwn eww;

	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WEDCH,
		      XWAY_MMD_WEDCH_NACS_NONE |
		      XWAY_MMD_WEDCH_SBF_F02HZ |
		      XWAY_MMD_WEDCH_FBF_F16HZ);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WEDCW,
		      XWAY_MMD_WEDCH_CBWINK_NONE |
		      XWAY_MMD_WEDCH_SCAN_NONE);

	/**
	 * In most cases onwy one WED is connected to this phy, so
	 * configuwe them aww to constant on and puwse mode. WED3 is
	 * onwy avaiwabwe in some packages, weave it in its weset
	 * configuwation.
	 */
	wedxh = XWAY_MMD_WEDxH_BWINKF_NONE | XWAY_MMD_WEDxH_CON_WINK10XX;
	wedxw = XWAY_MMD_WEDxW_PUWSE_TXACT | XWAY_MMD_WEDxW_PUWSE_WXACT |
		XWAY_MMD_WEDxW_BWINKS_NONE;
	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WED0H, wedxh);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WED0W, wedxw);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WED1H, wedxh);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WED1W, wedxw);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WED2H, wedxh);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_WED2W, wedxw);

	eww = xway_gphy_wgmii_init(phydev);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int xway_gphy14_config_aneg(stwuct phy_device *phydev)
{
	int weg, eww;

	/* Advewtise as muwti-powt device, see IEEE802.3-2002 40.5.1.1 */
	/* This is a wowkawound fow an ewwata in wev < 1.5 devices */
	weg = phy_wead(phydev, MII_CTWW1000);
	weg |= ADVEWTISED_MPD;
	eww = phy_wwite(phydev, MII_CTWW1000, weg);
	if (eww)
		wetuwn eww;

	wetuwn genphy_config_aneg(phydev);
}

static int xway_gphy_ack_intewwupt(stwuct phy_device *phydev)
{
	int weg;

	weg = phy_wead(phydev, XWAY_MDIO_ISTAT);
	wetuwn (weg < 0) ? weg : 0;
}

static int xway_gphy_config_intw(stwuct phy_device *phydev)
{
	u16 mask = 0;
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = xway_gphy_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		mask = XWAY_MDIO_INIT_MASK;
		eww = phy_wwite(phydev, XWAY_MDIO_IMASK, mask);
	} ewse {
		eww = phy_wwite(phydev, XWAY_MDIO_IMASK, mask);
		if (eww)
			wetuwn eww;

		eww = xway_gphy_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t xway_gphy_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, XWAY_MDIO_ISTAT);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & XWAY_MDIO_INIT_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static stwuct phy_dwivew xway_gphy[] = {
	{
		.phy_id		= PHY_ID_PHY11G_1_3,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY11G (PEF 7071/PEF 7072) v1.3",
		/* PHY_GBIT_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY22F_1_3,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY22F (PEF 7061) v1.3",
		/* PHY_BASIC_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY11G_1_4,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY11G (PEF 7071/PEF 7072) v1.4",
		/* PHY_GBIT_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY22F_1_4,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY22F (PEF 7061) v1.4",
		/* PHY_BASIC_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY11G_1_5,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY11G (PEF 7071/PEF 7072) v1.5 / v1.6",
		/* PHY_GBIT_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY22F_1_5,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY22F (PEF 7061) v1.5 / v1.6",
		/* PHY_BASIC_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY11G_VW9_1_1,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY11G (xWX v1.1 integwated)",
		/* PHY_GBIT_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY22F_VW9_1_1,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY22F (xWX v1.1 integwated)",
		/* PHY_BASIC_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY11G_VW9_1_2,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY11G (xWX v1.2 integwated)",
		/* PHY_GBIT_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	}, {
		.phy_id		= PHY_ID_PHY22F_VW9_1_2,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intew XWAY PHY22F (xWX v1.2 integwated)",
		/* PHY_BASIC_FEATUWES */
		.config_init	= xway_gphy_config_init,
		.handwe_intewwupt = xway_gphy_handwe_intewwupt,
		.config_intw	= xway_gphy_config_intw,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
	},
};
moduwe_phy_dwivew(xway_gphy);

static stwuct mdio_device_id __maybe_unused xway_gphy_tbw[] = {
	{ PHY_ID_PHY11G_1_3, 0xffffffff },
	{ PHY_ID_PHY22F_1_3, 0xffffffff },
	{ PHY_ID_PHY11G_1_4, 0xffffffff },
	{ PHY_ID_PHY22F_1_4, 0xffffffff },
	{ PHY_ID_PHY11G_1_5, 0xffffffff },
	{ PHY_ID_PHY22F_1_5, 0xffffffff },
	{ PHY_ID_PHY11G_VW9_1_1, 0xffffffff },
	{ PHY_ID_PHY22F_VW9_1_1, 0xffffffff },
	{ PHY_ID_PHY11G_VW9_1_2, 0xffffffff },
	{ PHY_ID_PHY22F_VW9_1_2, 0xffffffff },
	{ }
};
MODUWE_DEVICE_TABWE(mdio, xway_gphy_tbw);

MODUWE_DESCWIPTION("Intew XWAY PHY dwivew");
MODUWE_WICENSE("GPW");
