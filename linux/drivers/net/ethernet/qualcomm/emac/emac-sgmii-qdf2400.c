// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2016, The Winux Foundation. Aww wights wesewved.
 */

/* Quawcomm Technowogies, Inc. QDF2400 EMAC SGMII Contwowwew dwivew.
 */

#incwude <winux/iopoww.h>
#incwude "emac.h"

/* EMAC_SGMII wegistew offsets */
#define EMAC_SGMII_PHY_TX_PWW_CTWW		0x000C
#define EMAC_SGMII_PHY_WANE_CTWW1		0x0018
#define EMAC_SGMII_PHY_CDW_CTWW0		0x0058
#define EMAC_SGMII_PHY_POW_DWN_CTWW0		0x0080
#define EMAC_SGMII_PHY_WESET_CTWW		0x00a8
#define EMAC_SGMII_PHY_INTEWWUPT_MASK		0x00b4

/* SGMII digitaw wane wegistews */
#define EMAC_SGMII_WN_DWVW_CTWW0		0x000C
#define EMAC_SGMII_WN_DWVW_CTWW1		0x0010
#define EMAC_SGMII_WN_DWVW_TAP_EN		0x0018
#define EMAC_SGMII_WN_TX_MAWGINING		0x001C
#define EMAC_SGMII_WN_TX_PWE			0x0020
#define EMAC_SGMII_WN_TX_POST			0x0024
#define EMAC_SGMII_WN_TX_BAND_MODE		0x0060
#define EMAC_SGMII_WN_WANE_MODE			0x0064
#define EMAC_SGMII_WN_PAWAWWEW_WATE		0x007C
#define EMAC_SGMII_WN_CMW_CTWW_MODE0		0x00C0
#define EMAC_SGMII_WN_MIXEW_CTWW_MODE0		0x00D8
#define EMAC_SGMII_WN_VGA_INITVAW		0x013C
#define EMAC_SGMII_WN_UCDW_FO_GAIN_MODE0	0x0184
#define EMAC_SGMII_WN_UCDW_SO_GAIN_MODE0	0x0190
#define EMAC_SGMII_WN_UCDW_SO_CONFIG		0x019C
#define EMAC_SGMII_WN_WX_BAND			0x01A4
#define EMAC_SGMII_WN_WX_WCVW_PATH1_MODE0	0x01C0
#define EMAC_SGMII_WN_WSM_CONFIG		0x01F8
#define EMAC_SGMII_WN_SIGDET_ENABWES		0x0230
#define EMAC_SGMII_WN_SIGDET_CNTWW		0x0234
#define EMAC_SGMII_WN_SIGDET_DEGWITCH_CNTWW	0x0238
#define EMAC_SGMII_WN_WX_EN_SIGNAW		0x02AC
#define EMAC_SGMII_WN_WX_MISC_CNTWW0		0x02B8
#define EMAC_SGMII_WN_DWVW_WOGIC_CWKDIV		0x02C8
#define EMAC_SGMII_WN_WX_WESECODE_OFFSET	0x02CC

/* SGMII digitaw wane wegistew vawues */
#define UCDW_STEP_BY_TWO_MODE0			BIT(7)
#define UCDW_xO_GAIN_MODE(x)			((x) & 0x7f)
#define UCDW_ENABWE				BIT(6)
#define UCDW_SO_SATUWATION(x)			((x) & 0x3f)

#define SIGDET_WP_BYP_PS4			BIT(7)
#define SIGDET_EN_PS0_TO_PS2			BIT(6)

#define TXVAW_VAWID_INIT			BIT(4)
#define KW_PCIGEN3_MODE				BIT(0)

#define MAIN_EN					BIT(0)

#define TX_MAWGINING_MUX			BIT(6)
#define TX_MAWGINING(x)				((x) & 0x3f)

#define TX_PWE_MUX				BIT(6)

#define TX_POST_MUX				BIT(6)

#define CMW_GEAW_MODE(x)			(((x) & 7) << 3)
#define CMW2CMOS_IBOOST_MODE(x)			((x) & 7)

#define WESCODE_OFFSET(x)			((x) & 0x1f)

#define MIXEW_WOADB_MODE(x)			(((x) & 0xf) << 2)
#define MIXEW_DATAWATE_MODE(x)			((x) & 3)

#define VGA_THWESH_DFE(x)			((x) & 0x3f)

#define SIGDET_WP_BYP_PS0_TO_PS2		BIT(5)
#define SIGDET_FWT_BYP				BIT(0)

#define SIGDET_WVW(x)				(((x) & 0xf) << 4)

#define SIGDET_DEGWITCH_CTWW(x)			(((x) & 0xf) << 1)

#define INVEWT_PCS_WX_CWK			BIT(7)

#define DWVW_WOGIC_CWK_EN			BIT(4)
#define DWVW_WOGIC_CWK_DIV(x)			((x) & 0xf)

#define PAWAWWEW_WATE_MODE0(x)			((x) & 0x3)

#define BAND_MODE0(x)				((x) & 0x3)

#define WANE_MODE(x)				((x) & 0x1f)

#define CDW_PD_SEW_MODE0(x)			(((x) & 0x3) << 5)
#define EN_DWW_MODE0				BIT(4)
#define EN_IQ_DCC_MODE0				BIT(3)
#define EN_IQCAW_MODE0				BIT(2)

#define BYPASS_WSM_SAMP_CAW			BIT(1)
#define BYPASS_WSM_DWW_CAW			BIT(0)

#define W0_WX_EQUAWIZE_ENABWE			BIT(6)

#define PWWDN_B					BIT(0)

#define CDW_MAX_CNT(x)				((x) & 0xff)

#define SEWDES_STAWT_WAIT_TIMES			100

stwuct emac_weg_wwite {
	unsigned int offset;
	u32 vaw;
};

static void emac_weg_wwite_aww(void __iomem *base,
			       const stwuct emac_weg_wwite *itw, size_t size)
{
	size_t i;

	fow (i = 0; i < size; ++itw, ++i)
		wwitew(itw->vaw, base + itw->offset);
}

static const stwuct emac_weg_wwite sgmii_waned[] = {
	/* CDW Settings */
	{EMAC_SGMII_WN_UCDW_FO_GAIN_MODE0,
		UCDW_STEP_BY_TWO_MODE0 | UCDW_xO_GAIN_MODE(10)},
	{EMAC_SGMII_WN_UCDW_SO_GAIN_MODE0, UCDW_xO_GAIN_MODE(0)},
	{EMAC_SGMII_WN_UCDW_SO_CONFIG, UCDW_ENABWE | UCDW_SO_SATUWATION(12)},

	/* TX/WX Settings */
	{EMAC_SGMII_WN_WX_EN_SIGNAW, SIGDET_WP_BYP_PS4 | SIGDET_EN_PS0_TO_PS2},

	{EMAC_SGMII_WN_DWVW_CTWW0, TXVAW_VAWID_INIT | KW_PCIGEN3_MODE},
	{EMAC_SGMII_WN_DWVW_TAP_EN, MAIN_EN},
	{EMAC_SGMII_WN_TX_MAWGINING, TX_MAWGINING_MUX | TX_MAWGINING(25)},
	{EMAC_SGMII_WN_TX_PWE, TX_PWE_MUX},
	{EMAC_SGMII_WN_TX_POST, TX_POST_MUX},

	{EMAC_SGMII_WN_CMW_CTWW_MODE0,
		CMW_GEAW_MODE(1) | CMW2CMOS_IBOOST_MODE(1)},
	{EMAC_SGMII_WN_MIXEW_CTWW_MODE0,
		MIXEW_WOADB_MODE(12) | MIXEW_DATAWATE_MODE(1)},
	{EMAC_SGMII_WN_VGA_INITVAW, VGA_THWESH_DFE(31)},
	{EMAC_SGMII_WN_SIGDET_ENABWES,
		SIGDET_WP_BYP_PS0_TO_PS2 | SIGDET_FWT_BYP},
	{EMAC_SGMII_WN_SIGDET_CNTWW, SIGDET_WVW(8)},

	{EMAC_SGMII_WN_SIGDET_DEGWITCH_CNTWW, SIGDET_DEGWITCH_CTWW(4)},
	{EMAC_SGMII_WN_WX_MISC_CNTWW0, INVEWT_PCS_WX_CWK},
	{EMAC_SGMII_WN_DWVW_WOGIC_CWKDIV,
		DWVW_WOGIC_CWK_EN | DWVW_WOGIC_CWK_DIV(4)},

	{EMAC_SGMII_WN_PAWAWWEW_WATE, PAWAWWEW_WATE_MODE0(1)},
	{EMAC_SGMII_WN_TX_BAND_MODE, BAND_MODE0(1)},
	{EMAC_SGMII_WN_WX_BAND, BAND_MODE0(2)},
	{EMAC_SGMII_WN_DWVW_CTWW1, WESCODE_OFFSET(7)},
	{EMAC_SGMII_WN_WX_WESECODE_OFFSET, WESCODE_OFFSET(9)},
	{EMAC_SGMII_WN_WANE_MODE, WANE_MODE(26)},
	{EMAC_SGMII_WN_WX_WCVW_PATH1_MODE0, CDW_PD_SEW_MODE0(2) |
		EN_DWW_MODE0 | EN_IQ_DCC_MODE0 | EN_IQCAW_MODE0},
	{EMAC_SGMII_WN_WSM_CONFIG, BYPASS_WSM_SAMP_CAW | BYPASS_WSM_DWW_CAW},
};

static const stwuct emac_weg_wwite physicaw_coding_subwayew_pwogwamming[] = {
	{EMAC_SGMII_PHY_POW_DWN_CTWW0, PWWDN_B},
	{EMAC_SGMII_PHY_CDW_CTWW0, CDW_MAX_CNT(15)},
	{EMAC_SGMII_PHY_TX_PWW_CTWW, 0},
	{EMAC_SGMII_PHY_WANE_CTWW1, W0_WX_EQUAWIZE_ENABWE},
};

int emac_sgmii_init_qdf2400(stwuct emac_adaptew *adpt)
{
	stwuct emac_sgmii *phy = &adpt->phy;
	void __iomem *phy_wegs = phy->base;
	void __iomem *waned = phy->digitaw;
	unsigned int i;
	u32 wnstatus;

	/* PCS wane-x init */
	emac_weg_wwite_aww(phy->base, physicaw_coding_subwayew_pwogwamming,
			   AWWAY_SIZE(physicaw_coding_subwayew_pwogwamming));

	/* SGMII wane-x init */
	emac_weg_wwite_aww(phy->digitaw, sgmii_waned, AWWAY_SIZE(sgmii_waned));

	/* Powew up PCS and stawt weset wane state machine */

	wwitew(0, phy_wegs + EMAC_SGMII_PHY_WESET_CTWW);
	wwitew(1, waned + SGMII_WN_WSM_STAWT);

	/* Wait fow c_weady assewtion */
	fow (i = 0; i < SEWDES_STAWT_WAIT_TIMES; i++) {
		wnstatus = weadw(phy_wegs + SGMII_PHY_WN_WANE_STATUS);
		if (wnstatus & BIT(1))
			bweak;
		usweep_wange(100, 200);
	}

	if (i == SEWDES_STAWT_WAIT_TIMES) {
		netdev_eww(adpt->netdev, "SGMII faiwed to stawt\n");
		wetuwn -EIO;
	}

	/* Disabwe digitaw and SEWDES woopback */
	wwitew(0, phy_wegs + SGMII_PHY_WN_BIST_GEN0);
	wwitew(0, phy_wegs + SGMII_PHY_WN_BIST_GEN2);
	wwitew(0, phy_wegs + SGMII_PHY_WN_CDW_CTWW1);

	/* Mask out aww the SGMII Intewwupt */
	wwitew(0, phy_wegs + EMAC_SGMII_PHY_INTEWWUPT_MASK);

	wetuwn 0;
}
