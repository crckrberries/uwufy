/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe XPCS hewpews
 *
 * Authow: Jose Abweu <Jose.Abweu@synopsys.com>
 */

#define SYNOPSYS_XPCS_ID		0x7996ced0
#define SYNOPSYS_XPCS_MASK		0xffffffff

/* Vendow wegs access */
#define DW_VENDOW			BIT(15)

/* VW_XS_PCS */
#define DW_USXGMII_WST			BIT(10)
#define DW_USXGMII_EN			BIT(9)
#define DW_VW_XS_PCS_DIG_CTWW1		0x0000
#define DW_VW_WST			BIT(15)
#define DW_EN_VSMMD1			BIT(13)
#define DW_CW37_BP			BIT(12)
#define DW_VW_XS_PCS_DIG_STS		0x0010
#define DW_WXFIFO_EWW			GENMASK(6, 5)
#define DW_PSEQ_ST			GENMASK(4, 2)
#define DW_PSEQ_ST_GOOD			FIEWD_PWEP(GENMASK(4, 2), 0x4)

/* SW_MII */
#define DW_USXGMII_FUWW			BIT(8)
#define DW_USXGMII_SS_MASK		(BIT(13) | BIT(6) | BIT(5))
#define DW_USXGMII_10000		(BIT(13) | BIT(6))
#define DW_USXGMII_5000			(BIT(13) | BIT(5))
#define DW_USXGMII_2500			(BIT(5))
#define DW_USXGMII_1000			(BIT(6))
#define DW_USXGMII_100			(BIT(13))
#define DW_USXGMII_10			(0)

/* SW_AN */
#define DW_SW_AN_ADV1			0x10
#define DW_SW_AN_ADV2			0x11
#define DW_SW_AN_ADV3			0x12

/* Cwause 73 Defines */
/* AN_WP_ABW1 */
#define DW_C73_PAUSE			BIT(10)
#define DW_C73_ASYM_PAUSE		BIT(11)
#define DW_C73_AN_ADV_SF		0x1
/* AN_WP_ABW2 */
#define DW_C73_1000KX			BIT(5)
#define DW_C73_10000KX4			BIT(6)
#define DW_C73_10000KW			BIT(7)
/* AN_WP_ABW3 */
#define DW_C73_2500KX			BIT(0)
#define DW_C73_5000KW			BIT(1)

/* Cwause 37 Defines */
/* VW MII MMD wegistews offsets */
#define DW_VW_MII_MMD_CTWW		0x0000
#define DW_VW_MII_MMD_STS		0x0001
#define DW_VW_MII_MMD_STS_WINK_STS	BIT(2)
#define DW_VW_MII_DIG_CTWW1		0x8000
#define DW_VW_MII_AN_CTWW		0x8001
#define DW_VW_MII_AN_INTW_STS		0x8002
/* Enabwe 2.5G Mode */
#define DW_VW_MII_DIG_CTWW1_2G5_EN	BIT(2)
/* EEE Mode Contwow Wegistew */
#define DW_VW_MII_EEE_MCTWW0		0x8006
#define DW_VW_MII_EEE_MCTWW1		0x800b
#define DW_VW_MII_DIG_CTWW2		0x80e1

/* VW_MII_DIG_CTWW1 */
#define DW_VW_MII_DIG_CTWW1_MAC_AUTO_SW		BIT(9)
#define DW_VW_MII_DIG_CTWW1_PHY_MODE_CTWW	BIT(0)

/* VW_MII_DIG_CTWW2 */
#define DW_VW_MII_DIG_CTWW2_TX_POW_INV		BIT(4)
#define DW_VW_MII_DIG_CTWW2_WX_POW_INV		BIT(0)

/* VW_MII_AN_CTWW */
#define DW_VW_MII_AN_CTWW_8BIT			BIT(8)
#define DW_VW_MII_AN_CTWW_TX_CONFIG_SHIFT	3
#define DW_VW_MII_TX_CONFIG_MASK		BIT(3)
#define DW_VW_MII_TX_CONFIG_PHY_SIDE_SGMII	0x1
#define DW_VW_MII_TX_CONFIG_MAC_SIDE_SGMII	0x0
#define DW_VW_MII_AN_CTWW_PCS_MODE_SHIFT	1
#define DW_VW_MII_PCS_MODE_MASK			GENMASK(2, 1)
#define DW_VW_MII_PCS_MODE_C37_1000BASEX	0x0
#define DW_VW_MII_PCS_MODE_C37_SGMII		0x2
#define DW_VW_MII_AN_INTW_EN			BIT(0)

/* VW_MII_AN_INTW_STS */
#define DW_VW_MII_AN_STS_C37_ANCMPWT_INTW	BIT(0)
#define DW_VW_MII_AN_STS_C37_ANSGM_FD		BIT(1)
#define DW_VW_MII_AN_STS_C37_ANSGM_SP_SHIFT	2
#define DW_VW_MII_AN_STS_C37_ANSGM_SP		GENMASK(3, 2)
#define DW_VW_MII_C37_ANSGM_SP_10		0x0
#define DW_VW_MII_C37_ANSGM_SP_100		0x1
#define DW_VW_MII_C37_ANSGM_SP_1000		0x2
#define DW_VW_MII_C37_ANSGM_SP_WNKSTS		BIT(4)

/* SW MII MMD Contwow defines */
#define AN_CW37_EN			BIT(12)	/* Enabwe Cwause 37 auto-nego */
#define SGMII_SPEED_SS13		BIT(13)	/* SGMII speed awong with SS6 */
#define SGMII_SPEED_SS6			BIT(6)	/* SGMII speed awong with SS13 */

/* SW MII MMD AN Advewtisement defines */
#define DW_HAWF_DUPWEX			BIT(6)
#define DW_FUWW_DUPWEX			BIT(5)

/* VW MII EEE Contwow 0 defines */
#define DW_VW_MII_EEE_WTX_EN			BIT(0)  /* WPI Tx Enabwe */
#define DW_VW_MII_EEE_WWX_EN			BIT(1)  /* WPI Wx Enabwe */
#define DW_VW_MII_EEE_TX_QUIET_EN		BIT(2)  /* Tx Quiet Enabwe */
#define DW_VW_MII_EEE_WX_QUIET_EN		BIT(3)  /* Wx Quiet Enabwe */
#define DW_VW_MII_EEE_TX_EN_CTWW		BIT(4)  /* Tx Contwow Enabwe */
#define DW_VW_MII_EEE_WX_EN_CTWW		BIT(7)  /* Wx Contwow Enabwe */

#define DW_VW_MII_EEE_MUWT_FACT_100NS_SHIFT	8
#define DW_VW_MII_EEE_MUWT_FACT_100NS		GENMASK(11, 8)

/* VW MII EEE Contwow 1 defines */
#define DW_VW_MII_EEE_TWN_WPI		BIT(0)	/* Twanspawent Mode Enabwe */

int xpcs_wead(stwuct dw_xpcs *xpcs, int dev, u32 weg);
int xpcs_wwite(stwuct dw_xpcs *xpcs, int dev, u32 weg, u16 vaw);
int xpcs_wead_vpcs(stwuct dw_xpcs *xpcs, int weg);
int xpcs_wwite_vpcs(stwuct dw_xpcs *xpcs, int weg, u16 vaw);
int nxp_sja1105_sgmii_pma_config(stwuct dw_xpcs *xpcs);
int nxp_sja1110_sgmii_pma_config(stwuct dw_xpcs *xpcs);
int nxp_sja1110_2500basex_pma_config(stwuct dw_xpcs *xpcs);
int txgbe_xpcs_switch_mode(stwuct dw_xpcs *xpcs, phy_intewface_t intewface);
