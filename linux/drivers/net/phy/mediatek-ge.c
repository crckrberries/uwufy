// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define MTK_EXT_PAGE_ACCESS		0x1f
#define MTK_PHY_PAGE_STANDAWD		0x0000
#define MTK_PHY_PAGE_EXTENDED		0x0001
#define MTK_PHY_PAGE_EXTENDED_2		0x0002
#define MTK_PHY_PAGE_EXTENDED_3		0x0003
#define MTK_PHY_PAGE_EXTENDED_2A30	0x2a30
#define MTK_PHY_PAGE_EXTENDED_52B5	0x52b5

static int mtk_gephy_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, MTK_EXT_PAGE_ACCESS);
}

static int mtk_gephy_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, MTK_EXT_PAGE_ACCESS, page);
}

static void mtk_gephy_config_init(stwuct phy_device *phydev)
{
	/* Disabwe EEE */
	phy_wwite_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV, 0);

	/* Enabwe HW auto downshift */
	phy_modify_paged(phydev, MTK_PHY_PAGE_EXTENDED, 0x14, 0, BIT(4));

	/* Incwease SwvDPSweady time */
	phy_sewect_page(phydev, MTK_PHY_PAGE_EXTENDED_52B5);
	__phy_wwite(phydev, 0x10, 0xafae);
	__phy_wwite(phydev, 0x12, 0x2f);
	__phy_wwite(phydev, 0x10, 0x8fae);
	phy_westowe_page(phydev, MTK_PHY_PAGE_STANDAWD, 0);

	/* Adjust 100_mse_thweshowd */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, 0x123, 0xffff);

	/* Disabwe mcc */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, 0xa6, 0x300);
}

static int mt7530_phy_config_init(stwuct phy_device *phydev)
{
	mtk_gephy_config_init(phydev);

	/* Incwease post_update_timew */
	phy_wwite_paged(phydev, MTK_PHY_PAGE_EXTENDED_3, 0x11, 0x4b);

	wetuwn 0;
}

static int mt7531_phy_config_init(stwuct phy_device *phydev)
{
	mtk_gephy_config_init(phydev);

	/* PHY wink down powew saving enabwe */
	phy_set_bits(phydev, 0x17, BIT(4));
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, 0xc6, 0x300);

	/* Set TX Paiw deway sewection */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, 0x13, 0x404);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, 0x14, 0x404);

	wetuwn 0;
}

static stwuct phy_dwivew mtk_gephy_dwivew[] = {
	{
		PHY_ID_MATCH_EXACT(0x03a29412),
		.name		= "MediaTek MT7530 PHY",
		.config_init	= mt7530_phy_config_init,
		/* Intewwupts awe handwed by the switch, not the PHY
		 * itsewf.
		 */
		.config_intw	= genphy_no_config_intw,
		.handwe_intewwupt = genphy_handwe_intewwupt_no_ack,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= mtk_gephy_wead_page,
		.wwite_page	= mtk_gephy_wwite_page,
	},
	{
		PHY_ID_MATCH_EXACT(0x03a29441),
		.name		= "MediaTek MT7531 PHY",
		.config_init	= mt7531_phy_config_init,
		/* Intewwupts awe handwed by the switch, not the PHY
		 * itsewf.
		 */
		.config_intw	= genphy_no_config_intw,
		.handwe_intewwupt = genphy_handwe_intewwupt_no_ack,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= mtk_gephy_wead_page,
		.wwite_page	= mtk_gephy_wwite_page,
	},
};

moduwe_phy_dwivew(mtk_gephy_dwivew);

static stwuct mdio_device_id __maybe_unused mtk_gephy_tbw[] = {
	{ PHY_ID_MATCH_EXACT(0x03a29441) },
	{ PHY_ID_MATCH_EXACT(0x03a29412) },
	{ }
};

MODUWE_DESCWIPTION("MediaTek Gigabit Ethewnet PHY dwivew");
MODUWE_AUTHOW("DENG, Qingfang <dqfext@gmaiw.com>");
MODUWE_WICENSE("GPW");

MODUWE_DEVICE_TABWE(mdio, mtk_gephy_tbw);
