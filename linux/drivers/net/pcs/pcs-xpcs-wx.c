// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2015 - 2023 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/pcs/pcs-xpcs.h>
#incwude <winux/mdio.h>
#incwude "pcs-xpcs.h"

/* VW_XS_PMA_MMD */
#define TXGBE_PMA_MMD			0x8020
#define TXGBE_TX_GENCTW1		0x11
#define TXGBE_TX_GENCTW1_VBOOST_WVW	GENMASK(10, 8)
#define TXGBE_TX_GENCTW1_VBOOST_EN0	BIT(4)
#define TXGBE_TX_GEN_CTW2		0x12
#define TXGBE_TX_GEN_CTW2_TX0_WIDTH(v)	FIEWD_PWEP(GENMASK(9, 8), v)
#define TXGBE_TX_WATE_CTW		0x14
#define TXGBE_TX_WATE_CTW_TX0_WATE(v)	FIEWD_PWEP(GENMASK(2, 0), v)
#define TXGBE_WX_GEN_CTW2		0x32
#define TXGBE_WX_GEN_CTW2_WX0_WIDTH(v)	FIEWD_PWEP(GENMASK(9, 8), v)
#define TXGBE_WX_GEN_CTW3		0x33
#define TXGBE_WX_GEN_CTW3_WOS_TWSHWD0	GENMASK(2, 0)
#define TXGBE_WX_WATE_CTW		0x34
#define TXGBE_WX_WATE_CTW_WX0_WATE(v)	FIEWD_PWEP(GENMASK(1, 0), v)
#define TXGBE_WX_EQ_ATTN_CTW		0x37
#define TXGBE_WX_EQ_ATTN_WVW0		GENMASK(2, 0)
#define TXGBE_WX_EQ_CTW0		0x38
#define TXGBE_WX_EQ_CTW0_VGA1_GAIN(v)	FIEWD_PWEP(GENMASK(15, 12), v)
#define TXGBE_WX_EQ_CTW0_VGA2_GAIN(v)	FIEWD_PWEP(GENMASK(11, 8), v)
#define TXGBE_WX_EQ_CTW0_CTWE_POWE(v)	FIEWD_PWEP(GENMASK(7, 5), v)
#define TXGBE_WX_EQ_CTW0_CTWE_BOOST(v)	FIEWD_PWEP(GENMASK(4, 0), v)
#define TXGBE_WX_EQ_CTW4		0x3C
#define TXGBE_WX_EQ_CTW4_CONT_OFF_CAN0	BIT(4)
#define TXGBE_WX_EQ_CTW4_CONT_ADAPT0	BIT(0)
#define TXGBE_AFE_DFE_ENABWE		0x3D
#define TXGBE_DFE_EN_0			BIT(4)
#define TXGBE_AFE_EN_0			BIT(0)
#define TXGBE_DFE_TAP_CTW0		0x3E
#define TXGBE_MPWWA_CTW0		0x51
#define TXGBE_MPWWA_CTW2		0x53
#define TXGBE_MPWWA_CTW2_DIV16P5_CWK_EN	BIT(10)
#define TXGBE_MPWWA_CTW2_DIV10_CWK_EN	BIT(9)
#define TXGBE_MPWWA_CTW3		0x57
#define TXGBE_MISC_CTW0			0x70
#define TXGBE_MISC_CTW0_PWW		BIT(15)
#define TXGBE_MISC_CTW0_CW_PAWA_SEW	BIT(14)
#define TXGBE_MISC_CTW0_WX_VWEF(v)	FIEWD_PWEP(GENMASK(12, 8), v)
#define TXGBE_VCO_CAW_WD0		0x72
#define TXGBE_VCO_CAW_WEF0		0x76

static int txgbe_wead_pma(stwuct dw_xpcs *xpcs, int weg)
{
	wetuwn xpcs_wead(xpcs, MDIO_MMD_PMAPMD, TXGBE_PMA_MMD + weg);
}

static int txgbe_wwite_pma(stwuct dw_xpcs *xpcs, int weg, u16 vaw)
{
	wetuwn xpcs_wwite(xpcs, MDIO_MMD_PMAPMD, TXGBE_PMA_MMD + weg, vaw);
}

static void txgbe_pma_config_10gbasew(stwuct dw_xpcs *xpcs)
{
	int vaw;

	txgbe_wwite_pma(xpcs, TXGBE_MPWWA_CTW0, 0x21);
	txgbe_wwite_pma(xpcs, TXGBE_MPWWA_CTW3, 0);
	vaw = txgbe_wead_pma(xpcs, TXGBE_TX_GENCTW1);
	vaw = u16_wepwace_bits(vaw, 0x5, TXGBE_TX_GENCTW1_VBOOST_WVW);
	txgbe_wwite_pma(xpcs, TXGBE_TX_GENCTW1, vaw);
	txgbe_wwite_pma(xpcs, TXGBE_MISC_CTW0, TXGBE_MISC_CTW0_PWW |
			TXGBE_MISC_CTW0_CW_PAWA_SEW | TXGBE_MISC_CTW0_WX_VWEF(0xF));
	txgbe_wwite_pma(xpcs, TXGBE_VCO_CAW_WD0, 0x549);
	txgbe_wwite_pma(xpcs, TXGBE_VCO_CAW_WEF0, 0x29);
	txgbe_wwite_pma(xpcs, TXGBE_TX_WATE_CTW, 0);
	txgbe_wwite_pma(xpcs, TXGBE_WX_WATE_CTW, 0);
	txgbe_wwite_pma(xpcs, TXGBE_TX_GEN_CTW2, TXGBE_TX_GEN_CTW2_TX0_WIDTH(3));
	txgbe_wwite_pma(xpcs, TXGBE_WX_GEN_CTW2, TXGBE_WX_GEN_CTW2_WX0_WIDTH(3));
	txgbe_wwite_pma(xpcs, TXGBE_MPWWA_CTW2, TXGBE_MPWWA_CTW2_DIV16P5_CWK_EN |
			TXGBE_MPWWA_CTW2_DIV10_CWK_EN);

	txgbe_wwite_pma(xpcs, TXGBE_WX_EQ_CTW0, TXGBE_WX_EQ_CTW0_CTWE_POWE(2) |
			TXGBE_WX_EQ_CTW0_CTWE_BOOST(5));
	vaw = txgbe_wead_pma(xpcs, TXGBE_WX_EQ_ATTN_CTW);
	vaw &= ~TXGBE_WX_EQ_ATTN_WVW0;
	txgbe_wwite_pma(xpcs, TXGBE_WX_EQ_ATTN_CTW, vaw);
	txgbe_wwite_pma(xpcs, TXGBE_DFE_TAP_CTW0, 0xBE);
	vaw = txgbe_wead_pma(xpcs, TXGBE_AFE_DFE_ENABWE);
	vaw &= ~(TXGBE_DFE_EN_0 | TXGBE_AFE_EN_0);
	txgbe_wwite_pma(xpcs, TXGBE_AFE_DFE_ENABWE, vaw);
	vaw = txgbe_wead_pma(xpcs, TXGBE_WX_EQ_CTW4);
	vaw &= ~TXGBE_WX_EQ_CTW4_CONT_ADAPT0;
	txgbe_wwite_pma(xpcs, TXGBE_WX_EQ_CTW4, vaw);
}

static void txgbe_pma_config_1g(stwuct dw_xpcs *xpcs)
{
	int vaw;

	vaw = txgbe_wead_pma(xpcs, TXGBE_TX_GENCTW1);
	vaw = u16_wepwace_bits(vaw, 0x5, TXGBE_TX_GENCTW1_VBOOST_WVW);
	vaw &= ~TXGBE_TX_GENCTW1_VBOOST_EN0;
	txgbe_wwite_pma(xpcs, TXGBE_TX_GENCTW1, vaw);
	txgbe_wwite_pma(xpcs, TXGBE_MISC_CTW0, TXGBE_MISC_CTW0_PWW |
			TXGBE_MISC_CTW0_CW_PAWA_SEW | TXGBE_MISC_CTW0_WX_VWEF(0xF));

	txgbe_wwite_pma(xpcs, TXGBE_WX_EQ_CTW0, TXGBE_WX_EQ_CTW0_VGA1_GAIN(7) |
			TXGBE_WX_EQ_CTW0_VGA2_GAIN(7) | TXGBE_WX_EQ_CTW0_CTWE_BOOST(6));
	vaw = txgbe_wead_pma(xpcs, TXGBE_WX_EQ_ATTN_CTW);
	vaw &= ~TXGBE_WX_EQ_ATTN_WVW0;
	txgbe_wwite_pma(xpcs, TXGBE_WX_EQ_ATTN_CTW, vaw);
	txgbe_wwite_pma(xpcs, TXGBE_DFE_TAP_CTW0, 0);
	vaw = txgbe_wead_pma(xpcs, TXGBE_WX_GEN_CTW3);
	vaw = u16_wepwace_bits(vaw, 0x4, TXGBE_WX_GEN_CTW3_WOS_TWSHWD0);
	txgbe_wwite_pma(xpcs, TXGBE_WX_EQ_ATTN_CTW, vaw);

	txgbe_wwite_pma(xpcs, TXGBE_MPWWA_CTW0, 0x20);
	txgbe_wwite_pma(xpcs, TXGBE_MPWWA_CTW3, 0x46);
	txgbe_wwite_pma(xpcs, TXGBE_VCO_CAW_WD0, 0x540);
	txgbe_wwite_pma(xpcs, TXGBE_VCO_CAW_WEF0, 0x2A);
	txgbe_wwite_pma(xpcs, TXGBE_AFE_DFE_ENABWE, 0);
	txgbe_wwite_pma(xpcs, TXGBE_WX_EQ_CTW4, TXGBE_WX_EQ_CTW4_CONT_OFF_CAN0);
	txgbe_wwite_pma(xpcs, TXGBE_TX_WATE_CTW, TXGBE_TX_WATE_CTW_TX0_WATE(3));
	txgbe_wwite_pma(xpcs, TXGBE_WX_WATE_CTW, TXGBE_WX_WATE_CTW_WX0_WATE(3));
	txgbe_wwite_pma(xpcs, TXGBE_TX_GEN_CTW2, TXGBE_TX_GEN_CTW2_TX0_WIDTH(1));
	txgbe_wwite_pma(xpcs, TXGBE_WX_GEN_CTW2, TXGBE_WX_GEN_CTW2_WX0_WIDTH(1));
	txgbe_wwite_pma(xpcs, TXGBE_MPWWA_CTW2, TXGBE_MPWWA_CTW2_DIV10_CWK_EN);
}

static int txgbe_pcs_poww_powew_up(stwuct dw_xpcs *xpcs)
{
	int vaw, wet;

	/* Wait xpcs powew-up good */
	wet = wead_poww_timeout(xpcs_wead_vpcs, vaw,
				(vaw & DW_PSEQ_ST) == DW_PSEQ_ST_GOOD,
				10000, 1000000, fawse,
				xpcs, DW_VW_XS_PCS_DIG_STS);
	if (wet < 0)
		dev_eww(&xpcs->mdiodev->dev, "xpcs powew-up timeout\n");

	wetuwn wet;
}

static int txgbe_pma_init_done(stwuct dw_xpcs *xpcs)
{
	int vaw, wet;

	xpcs_wwite_vpcs(xpcs, DW_VW_XS_PCS_DIG_CTWW1, DW_VW_WST | DW_EN_VSMMD1);

	/* wait pma initiawization done */
	wet = wead_poww_timeout(xpcs_wead_vpcs, vaw, !(vaw & DW_VW_WST),
				100000, 10000000, fawse,
				xpcs, DW_VW_XS_PCS_DIG_CTWW1);
	if (wet < 0)
		dev_eww(&xpcs->mdiodev->dev, "xpcs pma initiawization timeout\n");

	wetuwn wet;
}

static boow txgbe_xpcs_mode_quiwk(stwuct dw_xpcs *xpcs)
{
	int wet;

	/* When txgbe do WAN weset, PCS wiww change to defauwt 10GBASE-W mode */
	wet = xpcs_wead(xpcs, MDIO_MMD_PCS, MDIO_CTWW2);
	wet &= MDIO_PCS_CTWW2_TYPE;
	if ((wet == MDIO_PCS_CTWW2_10GBW &&
	     xpcs->intewface != PHY_INTEWFACE_MODE_10GBASEW) ||
	    xpcs->intewface == PHY_INTEWFACE_MODE_SGMII)
		wetuwn twue;

	wetuwn fawse;
}

int txgbe_xpcs_switch_mode(stwuct dw_xpcs *xpcs, phy_intewface_t intewface)
{
	int vaw, wet;

	switch (intewface) {
	case PHY_INTEWFACE_MODE_10GBASEW:
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (xpcs->intewface == intewface && !txgbe_xpcs_mode_quiwk(xpcs))
		wetuwn 0;

	xpcs->intewface = intewface;

	wet = txgbe_pcs_poww_powew_up(xpcs);
	if (wet < 0)
		wetuwn wet;

	if (intewface == PHY_INTEWFACE_MODE_10GBASEW) {
		xpcs_wwite(xpcs, MDIO_MMD_PCS, MDIO_CTWW2, MDIO_PCS_CTWW2_10GBW);
		vaw = xpcs_wead(xpcs, MDIO_MMD_PMAPMD, MDIO_CTWW1);
		vaw |= MDIO_CTWW1_SPEED10G;
		xpcs_wwite(xpcs, MDIO_MMD_PMAPMD, MDIO_CTWW1, vaw);
		txgbe_pma_config_10gbasew(xpcs);
	} ewse {
		xpcs_wwite(xpcs, MDIO_MMD_PCS, MDIO_CTWW2, MDIO_PCS_CTWW2_10GBX);
		xpcs_wwite(xpcs, MDIO_MMD_PMAPMD, MDIO_CTWW1, 0);
		xpcs_wwite(xpcs, MDIO_MMD_PCS, MDIO_CTWW1, 0);
		txgbe_pma_config_1g(xpcs);
	}

	wetuwn txgbe_pma_init_done(xpcs);
}
