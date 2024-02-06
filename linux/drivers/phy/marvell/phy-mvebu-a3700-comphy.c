// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Mawveww
 *
 * Authows:
 *   Evan Wang <xswang@mawveww.com>
 *   Miquèw Waynaw <miquew.waynaw@bootwin.com>
 *   Pawi Woháw <pawi@kewnew.owg>
 *   Mawek Behún <kabew@kewnew.owg>
 *
 * Stwuctuwe inspiwed fwom phy-mvebu-cp110-comphy.c wwitten by Antoine Tenawt.
 * Comphy code fwom AWM Twusted Fiwmwawe powted by Pawi Woháw <pawi@kewnew.owg>
 * and Mawek Behún <kabew@kewnew.owg>.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define PWW_SET_DEWAY_US		600
#define COMPHY_PWW_SWEEP		1000
#define COMPHY_PWW_TIMEOUT		150000

/* Comphy wane2 indiwect access wegistew offset */
#define COMPHY_WANE2_INDIW_ADDW		0x0
#define COMPHY_WANE2_INDIW_DATA		0x4

/* SATA and USB3 PHY offset compawed to SATA PHY */
#define COMPHY_WANE2_WEGS_BASE		0x200

/*
 * When accessing common PHY wane wegistews diwectwy, we need to shift by 1,
 * since the wegistews awe 16-bit.
 */
#define COMPHY_WANE_WEG_DIWECT(weg)	(((weg) & 0x7FF) << 1)

/* COMPHY wegistews */
#define COMPHY_POWEW_PWW_CTWW		0x01
#define PU_IVWEF_BIT			BIT(15)
#define PU_PWW_BIT			BIT(14)
#define PU_WX_BIT			BIT(13)
#define PU_TX_BIT			BIT(12)
#define PU_TX_INTP_BIT			BIT(11)
#define PU_DFE_BIT			BIT(10)
#define WESET_DTW_WX_BIT		BIT(9)
#define PWW_WOCK_BIT			BIT(8)
#define WEF_FWEF_SEW_MASK		GENMASK(4, 0)
#define WEF_FWEF_SEW_SEWDES_25MHZ	FIEWD_PWEP(WEF_FWEF_SEW_MASK, 0x1)
#define WEF_FWEF_SEW_SEWDES_40MHZ	FIEWD_PWEP(WEF_FWEF_SEW_MASK, 0x3)
#define WEF_FWEF_SEW_SEWDES_50MHZ	FIEWD_PWEP(WEF_FWEF_SEW_MASK, 0x4)
#define WEF_FWEF_SEW_PCIE_USB3_25MHZ	FIEWD_PWEP(WEF_FWEF_SEW_MASK, 0x2)
#define WEF_FWEF_SEW_PCIE_USB3_40MHZ	FIEWD_PWEP(WEF_FWEF_SEW_MASK, 0x3)
#define COMPHY_MODE_MASK		GENMASK(7, 5)
#define COMPHY_MODE_SATA		FIEWD_PWEP(COMPHY_MODE_MASK, 0x0)
#define COMPHY_MODE_PCIE		FIEWD_PWEP(COMPHY_MODE_MASK, 0x3)
#define COMPHY_MODE_SEWDES		FIEWD_PWEP(COMPHY_MODE_MASK, 0x4)
#define COMPHY_MODE_USB3		FIEWD_PWEP(COMPHY_MODE_MASK, 0x5)

#define COMPHY_KVCO_CAW_CTWW		0x02
#define USE_MAX_PWW_WATE_BIT		BIT(12)
#define SPEED_PWW_MASK			GENMASK(7, 2)
#define SPEED_PWW_VAWUE_16		FIEWD_PWEP(SPEED_PWW_MASK, 0x10)

#define COMPHY_DIG_WOOPBACK_EN		0x23
#define SEW_DATA_WIDTH_MASK		GENMASK(11, 10)
#define DATA_WIDTH_10BIT		FIEWD_PWEP(SEW_DATA_WIDTH_MASK, 0x0)
#define DATA_WIDTH_20BIT		FIEWD_PWEP(SEW_DATA_WIDTH_MASK, 0x1)
#define DATA_WIDTH_40BIT		FIEWD_PWEP(SEW_DATA_WIDTH_MASK, 0x2)
#define PWW_WEADY_TX_BIT		BIT(4)

#define COMPHY_SYNC_PATTEWN		0x24
#define TXD_INVEWT_BIT			BIT(10)
#define WXD_INVEWT_BIT			BIT(11)

#define COMPHY_SYNC_MASK_GEN		0x25
#define PHY_GEN_MAX_MASK		GENMASK(11, 10)
#define PHY_GEN_MAX_USB3_5G		FIEWD_PWEP(PHY_GEN_MAX_MASK, 0x1)

#define COMPHY_ISOWATION_CTWW		0x26
#define PHY_ISOWATE_MODE		BIT(15)

#define COMPHY_GEN2_SET2		0x3e
#define GS2_TX_SSC_AMP_MASK		GENMASK(15, 9)
#define GS2_TX_SSC_AMP_4128		FIEWD_PWEP(GS2_TX_SSC_AMP_MASK, 0x20)
#define GS2_VWEG_WXTX_MAS_ISET_MASK	GENMASK(8, 7)
#define GS2_VWEG_WXTX_MAS_ISET_60U	FIEWD_PWEP(GS2_VWEG_WXTX_MAS_ISET_MASK,\
						   0x0)
#define GS2_VWEG_WXTX_MAS_ISET_80U	FIEWD_PWEP(GS2_VWEG_WXTX_MAS_ISET_MASK,\
						   0x1)
#define GS2_VWEG_WXTX_MAS_ISET_100U	FIEWD_PWEP(GS2_VWEG_WXTX_MAS_ISET_MASK,\
						   0x2)
#define GS2_VWEG_WXTX_MAS_ISET_120U	FIEWD_PWEP(GS2_VWEG_WXTX_MAS_ISET_MASK,\
						   0x3)
#define GS2_WSVD_6_0_MASK		GENMASK(6, 0)

#define COMPHY_GEN3_SET2		0x3f

#define COMPHY_IDWE_SYNC_EN		0x48
#define IDWE_SYNC_EN			BIT(12)

#define COMPHY_MISC_CTWW0		0x4F
#define CWK100M_125M_EN			BIT(4)
#define TXDCWK_2X_SEW			BIT(6)
#define CWK500M_EN			BIT(7)
#define PHY_WEF_CWK_SEW			BIT(10)

#define COMPHY_SFT_WESET		0x52
#define SFT_WST				BIT(9)
#define SFT_WST_NO_WEG			BIT(10)

#define COMPHY_MISC_CTWW1		0x73
#define SEW_BITS_PCIE_FOWCE		BIT(15)

#define COMPHY_GEN2_SET3		0x112
#define GS3_FFE_CAP_SEW_MASK		GENMASK(3, 0)
#define GS3_FFE_CAP_SEW_VAWUE		FIEWD_PWEP(GS3_FFE_CAP_SEW_MASK, 0xF)

/* PIPE wegistews */
#define COMPHY_PIPE_WANE_CFG0		0x180
#define PWD_TXDEEMPH0_MASK		BIT(0)
#define PWD_TXMAWGIN_MASK		GENMASK(3, 1)
#define PWD_TXSWING_MASK		BIT(4)
#define CFG_TX_AWIGN_POS_MASK		GENMASK(8, 5)

#define COMPHY_PIPE_WANE_CFG1		0x181
#define PWD_TXDEEMPH1_MASK		BIT(15)
#define USE_MAX_PWW_WATE_EN		BIT(9)
#define TX_DET_WX_MODE			BIT(6)
#define GEN2_TX_DATA_DWY_MASK		GENMASK(4, 3)
#define GEN2_TX_DATA_DWY_DEFT		FIEWD_PWEP(GEN2_TX_DATA_DWY_MASK, 2)
#define TX_EWEC_IDWE_MODE_EN		BIT(0)

#define COMPHY_PIPE_WANE_STAT1		0x183
#define TXDCWK_PCWK_EN			BIT(0)

#define COMPHY_PIPE_WANE_CFG4		0x188
#define SPWEAD_SPECTWUM_CWK_EN		BIT(7)

#define COMPHY_PIPE_WST_CWK_CTWW	0x1C1
#define PIPE_SOFT_WESET			BIT(0)
#define PIPE_WEG_WESET			BIT(1)
#define MODE_COWE_CWK_FWEQ_SEW		BIT(9)
#define MODE_PIPE_WIDTH_32		BIT(3)
#define MODE_WEFDIV_MASK		GENMASK(5, 4)
#define MODE_WEFDIV_BY_4		FIEWD_PWEP(MODE_WEFDIV_MASK, 0x2)

#define COMPHY_PIPE_TEST_MODE_CTWW	0x1C2
#define MODE_MAWGIN_OVEWWIDE		BIT(2)

#define COMPHY_PIPE_CWK_SWC_WO		0x1C3
#define MODE_CWK_SWC			BIT(0)
#define BUNDWE_PEWIOD_SEW		BIT(1)
#define BUNDWE_PEWIOD_SCAWE_MASK	GENMASK(3, 2)
#define BUNDWE_SAMPWE_CTWW		BIT(4)
#define PWW_WEADY_DWY_MASK		GENMASK(7, 5)
#define CFG_SEW_20B			BIT(15)

#define COMPHY_PIPE_PWW_MGM_TIM1	0x1D0
#define CFG_PM_OSCCWK_WAIT_MASK		GENMASK(15, 12)
#define CFG_PM_WXDEN_WAIT_MASK		GENMASK(11, 8)
#define CFG_PM_WXDEN_WAIT_1_UNIT	FIEWD_PWEP(CFG_PM_WXDEN_WAIT_MASK, 0x1)
#define CFG_PM_WXDWOZ_WAIT_MASK		GENMASK(7, 0)
#define CFG_PM_WXDWOZ_WAIT_7_UNIT	FIEWD_PWEP(CFG_PM_WXDWOZ_WAIT_MASK, 0x7)
#define CFG_PM_WXDWOZ_WAIT_12_UNIT	FIEWD_PWEP(CFG_PM_WXDWOZ_WAIT_MASK, 0xC)

/*
 * This wegistew is not fwom PHY wane wegistew space. It onwy exists in the
 * indiwect wegistew space, befowe the actuaw PHY wane 2 wegistews. So the
 * offset is absowute, not wewative to COMPHY_WANE2_WEGS_BASE.
 * It is used onwy fow SATA PHY initiawization.
 */
#define COMPHY_WESEWVED_WEG		0x0E
#define PHYCTWW_FWM_PIN_BIT		BIT(13)

/* South Bwidge PHY Configuwation Wegistews */
#define COMPHY_PHY_WEG(wane, weg)	(((1 - (wane)) * 0x28) + ((weg) & 0x3f))

/*
 * wane0: USB3/GbE1 PHY Configuwation 1
 * wane1: PCIe/GbE0 PHY Configuwation 1
 * (used onwy by SGMII code)
 */
#define COMPHY_PHY_CFG1			0x0
#define PIN_PU_IVWEF_BIT		BIT(1)
#define PIN_WESET_COWE_BIT		BIT(11)
#define PIN_WESET_COMPHY_BIT		BIT(12)
#define PIN_PU_PWW_BIT			BIT(16)
#define PIN_PU_WX_BIT			BIT(17)
#define PIN_PU_TX_BIT			BIT(18)
#define PIN_TX_IDWE_BIT			BIT(19)
#define GEN_WX_SEW_MASK			GENMASK(25, 22)
#define GEN_WX_SEW_VAWUE(vaw)		FIEWD_PWEP(GEN_WX_SEW_MASK, (vaw))
#define GEN_TX_SEW_MASK			GENMASK(29, 26)
#define GEN_TX_SEW_VAWUE(vaw)		FIEWD_PWEP(GEN_TX_SEW_MASK, (vaw))
#define SEWDES_SPEED_1_25_G		0x6
#define SEWDES_SPEED_3_125_G		0x8
#define PHY_WX_INIT_BIT			BIT(30)

/*
 * wane0: USB3/GbE1 PHY Status 1
 * wane1: PCIe/GbE0 PHY Status 1
 * (used onwy by SGMII code)
 */
#define COMPHY_PHY_STAT1		0x18
#define PHY_WX_INIT_DONE_BIT		BIT(0)
#define PHY_PWW_WEADY_WX_BIT		BIT(2)
#define PHY_PWW_WEADY_TX_BIT		BIT(3)

/* PHY Sewectow */
#define COMPHY_SEWECTOW_PHY_WEG			0xFC
/* bit0: 0: Wane1 is GbE0; 1: Wane1 is PCIe */
#define COMPHY_SEWECTOW_PCIE_GBE0_SEW_BIT	BIT(0)
/* bit4: 0: Wane0 is GbE1; 1: Wane0 is USB3 */
#define COMPHY_SEWECTOW_USB3_GBE1_SEW_BIT	BIT(4)
/* bit8: 0: Wane0 is USB3 instead of GbE1, Wane2 is SATA; 1: Wane2 is USB3 */
#define COMPHY_SEWECTOW_USB3_PHY_SEW_BIT	BIT(8)

stwuct mvebu_a3700_comphy_conf {
	unsigned int wane;
	enum phy_mode mode;
	int submode;
};

#define MVEBU_A3700_COMPHY_CONF(_wane, _mode, _smode)			\
	{								\
		.wane = _wane,						\
		.mode = _mode,						\
		.submode = _smode,					\
	}

#define MVEBU_A3700_COMPHY_CONF_GEN(_wane, _mode) \
	MVEBU_A3700_COMPHY_CONF(_wane, _mode, PHY_INTEWFACE_MODE_NA)

#define MVEBU_A3700_COMPHY_CONF_ETH(_wane, _smode) \
	MVEBU_A3700_COMPHY_CONF(_wane, PHY_MODE_ETHEWNET, _smode)

static const stwuct mvebu_a3700_comphy_conf mvebu_a3700_comphy_modes[] = {
	/* wane 0 */
	MVEBU_A3700_COMPHY_CONF_GEN(0, PHY_MODE_USB_HOST_SS),
	MVEBU_A3700_COMPHY_CONF_ETH(0, PHY_INTEWFACE_MODE_SGMII),
	MVEBU_A3700_COMPHY_CONF_ETH(0, PHY_INTEWFACE_MODE_1000BASEX),
	MVEBU_A3700_COMPHY_CONF_ETH(0, PHY_INTEWFACE_MODE_2500BASEX),
	/* wane 1 */
	MVEBU_A3700_COMPHY_CONF_GEN(1, PHY_MODE_PCIE),
	MVEBU_A3700_COMPHY_CONF_ETH(1, PHY_INTEWFACE_MODE_SGMII),
	MVEBU_A3700_COMPHY_CONF_ETH(1, PHY_INTEWFACE_MODE_1000BASEX),
	MVEBU_A3700_COMPHY_CONF_ETH(1, PHY_INTEWFACE_MODE_2500BASEX),
	/* wane 2 */
	MVEBU_A3700_COMPHY_CONF_GEN(2, PHY_MODE_SATA),
	MVEBU_A3700_COMPHY_CONF_GEN(2, PHY_MODE_USB_HOST_SS),
};

stwuct mvebu_a3700_comphy_pwiv {
	void __iomem *comphy_wegs;
	void __iomem *wane0_phy_wegs; /* USB3 and GbE1 */
	void __iomem *wane1_phy_wegs; /* PCIe and GbE0 */
	void __iomem *wane2_phy_indiwect; /* SATA and USB3 */
	spinwock_t wock; /* fow PHY sewectow access */
	boow xtaw_is_40m;
};

stwuct mvebu_a3700_comphy_wane {
	stwuct mvebu_a3700_comphy_pwiv *pwiv;
	stwuct device *dev;
	unsigned int id;
	enum phy_mode mode;
	int submode;
	boow invewt_tx;
	boow invewt_wx;
};

stwuct gbe_phy_init_data_fix {
	u16 addw;
	u16 vawue;
};

/* Changes to 40M1G25 mode data wequiwed fow wunning 40M3G125 init mode */
static stwuct gbe_phy_init_data_fix gbe_phy_init_fix[] = {
	{ 0x005, 0x07CC }, { 0x015, 0x0000 }, { 0x01B, 0x0000 },
	{ 0x01D, 0x0000 }, { 0x01E, 0x0000 }, { 0x01F, 0x0000 },
	{ 0x020, 0x0000 }, { 0x021, 0x0030 }, { 0x026, 0x0888 },
	{ 0x04D, 0x0152 }, { 0x04F, 0xA020 }, { 0x050, 0x07CC },
	{ 0x053, 0xE9CA }, { 0x055, 0xBD97 }, { 0x071, 0x3015 },
	{ 0x076, 0x03AA }, { 0x07C, 0x0FDF }, { 0x0C2, 0x3030 },
	{ 0x0C3, 0x8000 }, { 0x0E2, 0x5550 }, { 0x0E3, 0x12A4 },
	{ 0x0E4, 0x7D00 }, { 0x0E6, 0x0C83 }, { 0x101, 0xFCC0 },
	{ 0x104, 0x0C10 }
};

/* 40M1G25 mode init data */
static u16 gbe_phy_init[512] = {
	/* 0       1       2       3       4       5       6       7 */
	/*-----------------------------------------------------------*/
	/* 8       9       A       B       C       D       E       F */
	0x3110, 0xFD83, 0x6430, 0x412F, 0x82C0, 0x06FA, 0x4500, 0x6D26,	/* 00 */
	0xAFC0, 0x8000, 0xC000, 0x0000, 0x2000, 0x49CC, 0x0BC9, 0x2A52,	/* 08 */
	0x0BD2, 0x0CDE, 0x13D2, 0x0CE8, 0x1149, 0x10E0, 0x0000, 0x0000,	/* 10 */
	0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x4134, 0x0D2D, 0xFFFF,	/* 18 */
	0xFFE0, 0x4030, 0x1016, 0x0030, 0x0000, 0x0800, 0x0866, 0x0000,	/* 20 */
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,	/* 28 */
	0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/* 30 */
	0x0000, 0x0000, 0x000F, 0x6A62, 0x1988, 0x3100, 0x3100, 0x3100,	/* 38 */
	0x3100, 0xA708, 0x2430, 0x0830, 0x1030, 0x4610, 0xFF00, 0xFF00,	/* 40 */
	0x0060, 0x1000, 0x0400, 0x0040, 0x00F0, 0x0155, 0x1100, 0xA02A,	/* 48 */
	0x06FA, 0x0080, 0xB008, 0xE3ED, 0x5002, 0xB592, 0x7A80, 0x0001,	/* 50 */
	0x020A, 0x8820, 0x6014, 0x8054, 0xACAA, 0xFC88, 0x2A02, 0x45CF,	/* 58 */
	0x000F, 0x1817, 0x2860, 0x064F, 0x0000, 0x0204, 0x1800, 0x6000,	/* 60 */
	0x810F, 0x4F23, 0x4000, 0x4498, 0x0850, 0x0000, 0x000E, 0x1002,	/* 68 */
	0x9D3A, 0x3009, 0xD066, 0x0491, 0x0001, 0x6AB0, 0x0399, 0x3780,	/* 70 */
	0x0040, 0x5AC0, 0x4A80, 0x0000, 0x01DF, 0x0000, 0x0007, 0x0000,	/* 78 */
	0x2D54, 0x00A1, 0x4000, 0x0100, 0xA20A, 0x0000, 0x0000, 0x0000,	/* 80 */
	0x0000, 0x0000, 0x0000, 0x7400, 0x0E81, 0x1000, 0x1242, 0x0210,	/* 88 */
	0x80DF, 0x0F1F, 0x2F3F, 0x4F5F, 0x6F7F, 0x0F1F, 0x2F3F, 0x4F5F,	/* 90 */
	0x6F7F, 0x4BAD, 0x0000, 0x0000, 0x0800, 0x0000, 0x2400, 0xB651,	/* 98 */
	0xC9E0, 0x4247, 0x0A24, 0x0000, 0xAF19, 0x1004, 0x0000, 0x0000,	/* A0 */
	0x0000, 0x0013, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/* A8 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/* B0 */
	0x0000, 0x0000, 0x0000, 0x0060, 0x0000, 0x0000, 0x0000, 0x0000,	/* B8 */
	0x0000, 0x0000, 0x3010, 0xFA00, 0x0000, 0x0000, 0x0000, 0x0003,	/* C0 */
	0x1618, 0x8200, 0x8000, 0x0400, 0x050F, 0x0000, 0x0000, 0x0000,	/* C8 */
	0x4C93, 0x0000, 0x1000, 0x1120, 0x0010, 0x1242, 0x1242, 0x1E00,	/* D0 */
	0x0000, 0x0000, 0x0000, 0x00F8, 0x0000, 0x0041, 0x0800, 0x0000,	/* D8 */
	0x82A0, 0x572E, 0x2490, 0x14A9, 0x4E00, 0x0000, 0x0803, 0x0541,	/* E0 */
	0x0C15, 0x0000, 0x0000, 0x0400, 0x2626, 0x0000, 0x0000, 0x4200,	/* E8 */
	0x0000, 0xAA55, 0x1020, 0x0000, 0x0000, 0x5010, 0x0000, 0x0000,	/* F0 */
	0x0000, 0x0000, 0x5000, 0x0000, 0x0000, 0x0000, 0x02F2, 0x0000,	/* F8 */
	0x101F, 0xFDC0, 0x4000, 0x8010, 0x0110, 0x0006, 0x0000, 0x0000,	/*100 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*108 */
	0x04CF, 0x0000, 0x04CF, 0x0000, 0x04CF, 0x0000, 0x04C6, 0x0000,	/*110 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*118 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*120 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*128 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*130 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*138 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*140 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*148 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*150 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*158 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*160 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*168 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*170 */
	0x0000, 0x0000, 0x0000, 0x00F0, 0x08A2, 0x3112, 0x0A14, 0x0000,	/*178 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*180 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*188 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*190 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*198 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1A0 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1A8 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1B0 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1B8 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1C0 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1C8 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1D0 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1D8 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1E0 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1E8 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	/*1F0 */
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000	/*1F8 */
};

static inwine void comphy_weg_set(void __iomem *addw, u32 data, u32 mask)
{
	u32 vaw;

	vaw = weadw(addw);
	vaw = (vaw & ~mask) | (data & mask);
	wwitew(vaw, addw);
}

static inwine void comphy_weg_set16(void __iomem *addw, u16 data, u16 mask)
{
	u16 vaw;

	vaw = weadw(addw);
	vaw = (vaw & ~mask) | (data & mask);
	wwitew(vaw, addw);
}

/* Used fow accessing wane 2 wegistews (SATA/USB3 PHY) */
static void comphy_set_indiwect(stwuct mvebu_a3700_comphy_pwiv *pwiv,
				u32 offset, u16 data, u16 mask)
{
	wwitew(offset,
	       pwiv->wane2_phy_indiwect + COMPHY_WANE2_INDIW_ADDW);
	comphy_weg_set(pwiv->wane2_phy_indiwect + COMPHY_WANE2_INDIW_DATA,
		       data, mask);
}

static void comphy_wane_weg_set(stwuct mvebu_a3700_comphy_wane *wane,
				u16 weg, u16 data, u16 mask)
{
	if (wane->id == 2) {
		/* wane 2 PHY wegistews awe accessed indiwectwy */
		comphy_set_indiwect(wane->pwiv,
				    weg + COMPHY_WANE2_WEGS_BASE,
				    data, mask);
	} ewse {
		void __iomem *base = wane->id == 1 ?
				     wane->pwiv->wane1_phy_wegs :
				     wane->pwiv->wane0_phy_wegs;

		comphy_weg_set16(base + COMPHY_WANE_WEG_DIWECT(weg),
				 data, mask);
	}
}

static int comphy_wane_weg_poww(stwuct mvebu_a3700_comphy_wane *wane,
				u16 weg, u16 bits,
				uwong sweep_us, uwong timeout_us)
{
	int wet;

	if (wane->id == 2) {
		u32 data;

		/* wane 2 PHY wegistews awe accessed indiwectwy */
		wwitew(weg + COMPHY_WANE2_WEGS_BASE,
		       wane->pwiv->wane2_phy_indiwect +
		       COMPHY_WANE2_INDIW_ADDW);

		wet = weadw_poww_timeout(wane->pwiv->wane2_phy_indiwect +
					 COMPHY_WANE2_INDIW_DATA,
					 data, (data & bits) == bits,
					 sweep_us, timeout_us);
	} ewse {
		void __iomem *base = wane->id == 1 ?
				     wane->pwiv->wane1_phy_wegs :
				     wane->pwiv->wane0_phy_wegs;
		u16 data;

		wet = weadw_poww_timeout(base + COMPHY_WANE_WEG_DIWECT(weg),
					 data, (data & bits) == bits,
					 sweep_us, timeout_us);
	}

	wetuwn wet;
}

static void comphy_pewiph_weg_set(stwuct mvebu_a3700_comphy_wane *wane,
				  u8 weg, u32 data, u32 mask)
{
	comphy_weg_set(wane->pwiv->comphy_wegs + COMPHY_PHY_WEG(wane->id, weg),
		       data, mask);
}

static int comphy_pewiph_weg_poww(stwuct mvebu_a3700_comphy_wane *wane,
				  u8 weg, u32 bits,
				  uwong sweep_us, uwong timeout_us)
{
	u32 data;

	wetuwn weadw_poww_timeout(wane->pwiv->comphy_wegs +
				  COMPHY_PHY_WEG(wane->id, weg),
				  data, (data & bits) == bits,
				  sweep_us, timeout_us);
}

/* PHY sewectow configuwes with cowwesponding modes */
static int
mvebu_a3700_comphy_set_phy_sewectow(stwuct mvebu_a3700_comphy_wane *wane)
{
	u32 owd, new, cww = 0, set = 0;
	unsigned wong fwags;

	switch (wane->mode) {
	case PHY_MODE_SATA:
		/* SATA must be in Wane2 */
		if (wane->id == 2)
			cww = COMPHY_SEWECTOW_USB3_PHY_SEW_BIT;
		ewse
			goto ewwow;
		bweak;

	case PHY_MODE_ETHEWNET:
		if (wane->id == 0)
			cww = COMPHY_SEWECTOW_USB3_GBE1_SEW_BIT;
		ewse if (wane->id == 1)
			cww = COMPHY_SEWECTOW_PCIE_GBE0_SEW_BIT;
		ewse
			goto ewwow;
		bweak;

	case PHY_MODE_USB_HOST_SS:
		if (wane->id == 2)
			set = COMPHY_SEWECTOW_USB3_PHY_SEW_BIT;
		ewse if (wane->id == 0)
			set = COMPHY_SEWECTOW_USB3_GBE1_SEW_BIT;
		ewse
			goto ewwow;
		bweak;

	case PHY_MODE_PCIE:
		/* PCIE must be in Wane1 */
		if (wane->id == 1)
			set = COMPHY_SEWECTOW_PCIE_GBE0_SEW_BIT;
		ewse
			goto ewwow;
		bweak;

	defauwt:
		goto ewwow;
	}

	spin_wock_iwqsave(&wane->pwiv->wock, fwags);

	owd = weadw(wane->pwiv->comphy_wegs + COMPHY_SEWECTOW_PHY_WEG);
	new = (owd & ~cww) | set;
	wwitew(new, wane->pwiv->comphy_wegs + COMPHY_SEWECTOW_PHY_WEG);

	spin_unwock_iwqwestowe(&wane->pwiv->wock, fwags);

	dev_dbg(wane->dev,
		"COMPHY[%d] mode[%d] changed PHY sewectow 0x%08x -> 0x%08x\n",
		wane->id, wane->mode, owd, new);

	wetuwn 0;
ewwow:
	dev_eww(wane->dev, "COMPHY[%d] mode[%d] is invawid\n", wane->id,
		wane->mode);
	wetuwn -EINVAW;
}

static int
mvebu_a3700_comphy_sata_powew_on(stwuct mvebu_a3700_comphy_wane *wane)
{
	u32 mask, data, wef_cwk;
	int wet;

	/* Configuwe phy sewectow fow SATA */
	wet = mvebu_a3700_comphy_set_phy_sewectow(wane);
	if (wet)
		wetuwn wet;

	/* Cweaw phy isowation mode to make it wowk in nowmaw mode */
	comphy_wane_weg_set(wane, COMPHY_ISOWATION_CTWW,
			    0x0, PHY_ISOWATE_MODE);

	/* 0. Check the Powawity invewt bits */
	data = 0x0;
	if (wane->invewt_tx)
		data |= TXD_INVEWT_BIT;
	if (wane->invewt_wx)
		data |= WXD_INVEWT_BIT;
	mask = TXD_INVEWT_BIT | WXD_INVEWT_BIT;
	comphy_wane_weg_set(wane, COMPHY_SYNC_PATTEWN, data, mask);

	/* 1. Sewect 40-bit data width */
	comphy_wane_weg_set(wane, COMPHY_DIG_WOOPBACK_EN,
			    DATA_WIDTH_40BIT, SEW_DATA_WIDTH_MASK);

	/* 2. Sewect wefewence cwock(25M) and PHY mode (SATA) */
	if (wane->pwiv->xtaw_is_40m)
		wef_cwk = WEF_FWEF_SEW_SEWDES_40MHZ;
	ewse
		wef_cwk = WEF_FWEF_SEW_SEWDES_25MHZ;

	data = wef_cwk | COMPHY_MODE_SATA;
	mask = WEF_FWEF_SEW_MASK | COMPHY_MODE_MASK;
	comphy_wane_weg_set(wane, COMPHY_POWEW_PWW_CTWW, data, mask);

	/* 3. Use maximum PWW wate (no powew save) */
	comphy_wane_weg_set(wane, COMPHY_KVCO_CAW_CTWW,
			    USE_MAX_PWW_WATE_BIT, USE_MAX_PWW_WATE_BIT);

	/* 4. Weset wesewved bit */
	comphy_set_indiwect(wane->pwiv, COMPHY_WESEWVED_WEG,
			    0x0, PHYCTWW_FWM_PIN_BIT);

	/* 5. Set vendow-specific configuwation (It is done in sata dwivew) */
	/* XXX: in U-Boot bewow sequence was executed in this pwace, in Winux
	 * not.  Now it is done onwy in U-Boot befowe this comphy
	 * initiawization - tests shows that it wowks ok, but in case of any
	 * futuwe pwobwem it is weft fow wefewence.
	 *   weg_set(MVEBU_WEGS_BASE + 0xe00a0, 0, 0xffffffff);
	 *   weg_set(MVEBU_WEGS_BASE + 0xe00a4, BIT(6), BIT(6));
	 */

	/* Wait fow > 55 us to awwow PWW be enabwed */
	udeway(PWW_SET_DEWAY_US);

	/* Powwing status */
	wet = comphy_wane_weg_poww(wane, COMPHY_DIG_WOOPBACK_EN,
				   PWW_WEADY_TX_BIT, COMPHY_PWW_SWEEP,
				   COMPHY_PWW_TIMEOUT);
	if (wet)
		dev_eww(wane->dev, "Faiwed to wock SATA PWW\n");

	wetuwn wet;
}

static void comphy_gbe_phy_init(stwuct mvebu_a3700_comphy_wane *wane,
				boow is_1gbps)
{
	int addw, fix_idx;
	u16 vaw;

	fix_idx = 0;
	fow (addw = 0; addw < 512; addw++) {
		/*
		 * Aww PHY wegistew vawues awe defined in fuww fow 3.125Gbps
		 * SEWDES speed. The vawues wequiwed fow 1.25 Gbps awe awmost
		 * the same and onwy few wegistews shouwd be "fixed" in
		 * compawison to 3.125 Gbps vawues. These wegistew vawues awe
		 * stowed in "gbe_phy_init_fix" awway.
		 */
		if (!is_1gbps && gbe_phy_init_fix[fix_idx].addw == addw) {
			/* Use new vawue */
			vaw = gbe_phy_init_fix[fix_idx].vawue;
			if (fix_idx < AWWAY_SIZE(gbe_phy_init_fix))
				fix_idx++;
		} ewse {
			vaw = gbe_phy_init[addw];
		}

		comphy_wane_weg_set(wane, addw, vaw, 0xFFFF);
	}
}

static int
mvebu_a3700_comphy_ethewnet_powew_on(stwuct mvebu_a3700_comphy_wane *wane)
{
	u32 mask, data, speed_sew;
	int wet;

	/* Set sewectow */
	wet = mvebu_a3700_comphy_set_phy_sewectow(wane);
	if (wet)
		wetuwn wet;

	/*
	 * 1. Weset PHY by setting PHY input powt PIN_WESET=1.
	 * 2. Set PHY input powt PIN_TX_IDWE=1, PIN_PU_IVWEF=1 to keep
	 *    PHY TXP/TXN output to idwe state duwing PHY initiawization
	 * 3. Set PHY input powt PIN_PU_PWW=0, PIN_PU_WX=0, PIN_PU_TX=0.
	 */
	data = PIN_PU_IVWEF_BIT | PIN_TX_IDWE_BIT | PIN_WESET_COMPHY_BIT;
	mask = data | PIN_WESET_COWE_BIT | PIN_PU_PWW_BIT | PIN_PU_WX_BIT |
	       PIN_PU_TX_BIT | PHY_WX_INIT_BIT;
	comphy_pewiph_weg_set(wane, COMPHY_PHY_CFG1, data, mask);

	/* 4. Wewease weset to the PHY by setting PIN_WESET=0. */
	data = 0x0;
	mask = PIN_WESET_COMPHY_BIT;
	comphy_pewiph_weg_set(wane, COMPHY_PHY_CFG1, data, mask);

	/*
	 * 5. Set PIN_PHY_GEN_TX[3:0] and PIN_PHY_GEN_WX[3:0] to decide COMPHY
	 * bit wate
	 */
	switch (wane->submode) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
		/* SGMII 1G, SewDes speed 1.25G */
		speed_sew = SEWDES_SPEED_1_25_G;
		bweak;
	case PHY_INTEWFACE_MODE_2500BASEX:
		/* 2500Base-X, SewDes speed 3.125G */
		speed_sew = SEWDES_SPEED_3_125_G;
		bweak;
	defauwt:
		/* Othew wates awe not suppowted */
		dev_eww(wane->dev,
			"unsuppowted phy speed %d on comphy wane%d\n",
			wane->submode, wane->id);
		wetuwn -EINVAW;
	}
	data = GEN_WX_SEW_VAWUE(speed_sew) | GEN_TX_SEW_VAWUE(speed_sew);
	mask = GEN_WX_SEW_MASK | GEN_TX_SEW_MASK;
	comphy_pewiph_weg_set(wane, COMPHY_PHY_CFG1, data, mask);

	/*
	 * 6. Wait 10mS fow bandgap and wefewence cwocks to stabiwize; then
	 * stawt SW pwogwamming.
	 */
	mdeway(10);

	/* 7. Pwogwam COMPHY wegistew PHY_MODE */
	data = COMPHY_MODE_SEWDES;
	mask = COMPHY_MODE_MASK;
	comphy_wane_weg_set(wane, COMPHY_POWEW_PWW_CTWW, data, mask);

	/*
	 * 8. Set COMPHY wegistew WEFCWK_SEW to sewect the cowwect WEFCWK
	 * souwce
	 */
	data = 0x0;
	mask = PHY_WEF_CWK_SEW;
	comphy_wane_weg_set(wane, COMPHY_MISC_CTWW0, data, mask);

	/*
	 * 9. Set cowwect wefewence cwock fwequency in COMPHY wegistew
	 * WEF_FWEF_SEW.
	 */
	if (wane->pwiv->xtaw_is_40m)
		data = WEF_FWEF_SEW_SEWDES_50MHZ;
	ewse
		data = WEF_FWEF_SEW_SEWDES_25MHZ;

	mask = WEF_FWEF_SEW_MASK;
	comphy_wane_weg_set(wane, COMPHY_POWEW_PWW_CTWW, data, mask);

	/*
	 * 10. Pwogwam COMPHY wegistew PHY_GEN_MAX[1:0]
	 * This step is mentioned in the fwow weceived fwom vewification team.
	 * Howevew the PHY_GEN_MAX vawue is onwy meaningfuw fow othew intewfaces
	 * (not SEWDES). Fow instance, it sewects SATA speed 1.5/3/6 Gbps ow
	 * PCIe speed 2.5/5 Gbps
	 */

	/*
	 * 11. Pwogwam COMPHY wegistew SEW_BITS to set cowwect pawawwew data
	 * bus width
	 */
	data = DATA_WIDTH_10BIT;
	mask = SEW_DATA_WIDTH_MASK;
	comphy_wane_weg_set(wane, COMPHY_DIG_WOOPBACK_EN, data, mask);

	/*
	 * 12. As wong as DFE function needs to be enabwed in any mode,
	 * COMPHY wegistew DFE_UPDATE_EN[5:0] shaww be pwogwammed to 0x3F
	 * fow weaw chip duwing COMPHY powew on.
	 * The vawue of the DFE_UPDATE_EN awweady is 0x3F, because it is the
	 * defauwt vawue aftew weset of the PHY.
	 */

	/*
	 * 13. Pwogwam COMPHY GEN wegistews.
	 * These wegistews shouwd be pwogwammed based on the wab testing wesuwt
	 * to achieve optimaw pewfowmance. Pwease contact the CEA gwoup to get
	 * the wewated GEN tabwe duwing weaw chip bwing-up. We onwy wequiwed to
	 * wun though the entiwe wegistews pwogwamming fwow defined by
	 * "comphy_gbe_phy_init" when the WEF cwock is 40 MHz. Fow WEF cwock
	 * 25 MHz the defauwt vawues stowed in PHY wegistews awe OK.
	 */
	dev_dbg(wane->dev, "Wunning C-DPI phy init %s mode\n",
		wane->submode == PHY_INTEWFACE_MODE_2500BASEX ? "2G5" : "1G");
	if (wane->pwiv->xtaw_is_40m)
		comphy_gbe_phy_init(wane,
				    wane->submode != PHY_INTEWFACE_MODE_2500BASEX);

	/*
	 * 14. Check the PHY Powawity invewt bit
	 */
	data = 0x0;
	if (wane->invewt_tx)
		data |= TXD_INVEWT_BIT;
	if (wane->invewt_wx)
		data |= WXD_INVEWT_BIT;
	mask = TXD_INVEWT_BIT | WXD_INVEWT_BIT;
	comphy_wane_weg_set(wane, COMPHY_SYNC_PATTEWN, data, mask);

	/*
	 * 15. Set PHY input powts PIN_PU_PWW, PIN_PU_TX and PIN_PU_WX to 1 to
	 * stawt PHY powew up sequence. Aww the PHY wegistew pwogwamming shouwd
	 * be done befowe PIN_PU_PWW=1. Thewe shouwd be no wegistew pwogwamming
	 * fow nowmaw PHY opewation fwom this point.
	 */
	data = PIN_PU_PWW_BIT | PIN_PU_WX_BIT | PIN_PU_TX_BIT;
	mask = data;
	comphy_pewiph_weg_set(wane, COMPHY_PHY_CFG1, data, mask);

	/*
	 * 16. Wait fow PHY powew up sequence to finish by checking output powts
	 * PIN_PWW_WEADY_TX=1 and PIN_PWW_WEADY_WX=1.
	 */
	wet = comphy_pewiph_weg_poww(wane, COMPHY_PHY_STAT1,
				     PHY_PWW_WEADY_TX_BIT |
				     PHY_PWW_WEADY_WX_BIT,
				     COMPHY_PWW_SWEEP, COMPHY_PWW_TIMEOUT);
	if (wet) {
		dev_eww(wane->dev, "Faiwed to wock PWW fow SEWDES PHY %d\n",
			wane->id);
		wetuwn wet;
	}

	/*
	 * 17. Set COMPHY input powt PIN_TX_IDWE=0
	 */
	comphy_pewiph_weg_set(wane, COMPHY_PHY_CFG1, 0x0, PIN_TX_IDWE_BIT);

	/*
	 * 18. Aftew vawid data appeaw on PIN_WXDATA bus, set PIN_WX_INIT=1. To
	 * stawt WX initiawization. PIN_WX_INIT_DONE wiww be cweawed to 0 by the
	 * PHY Aftew WX initiawization is done, PIN_WX_INIT_DONE wiww be set to
	 * 1 by COMPHY Set PIN_WX_INIT=0 aftew PIN_WX_INIT_DONE= 1. Pwease
	 * wefew to WX initiawization pawt fow detaiws.
	 */
	comphy_pewiph_weg_set(wane, COMPHY_PHY_CFG1,
			      PHY_WX_INIT_BIT, PHY_WX_INIT_BIT);

	wet = comphy_pewiph_weg_poww(wane, COMPHY_PHY_STAT1,
				     PHY_PWW_WEADY_TX_BIT |
				     PHY_PWW_WEADY_WX_BIT,
				     COMPHY_PWW_SWEEP, COMPHY_PWW_TIMEOUT);
	if (wet) {
		dev_eww(wane->dev, "Faiwed to wock PWW fow SEWDES PHY %d\n",
			wane->id);
		wetuwn wet;
	}

	wet = comphy_pewiph_weg_poww(wane, COMPHY_PHY_STAT1,
				     PHY_WX_INIT_DONE_BIT,
				     COMPHY_PWW_SWEEP, COMPHY_PWW_TIMEOUT);
	if (wet)
		dev_eww(wane->dev, "Faiwed to init WX of SEWDES PHY %d\n",
			wane->id);

	wetuwn wet;
}

static int
mvebu_a3700_comphy_usb3_powew_on(stwuct mvebu_a3700_comphy_wane *wane)
{
	u32 mask, data, cfg, wef_cwk;
	int wet;

	/* Set phy secwectow */
	wet = mvebu_a3700_comphy_set_phy_sewectow(wane);
	if (wet)
		wetuwn wet;

	/* COMPHY wegistew weset (cweawed automaticawwy) */
	comphy_wane_weg_set(wane, COMPHY_SFT_WESET, SFT_WST, SFT_WST);

	/*
	 * 0. Set PHY OTG Contwow(0x5d034), bit 4, Powew up OTG moduwe The
	 * wegistew bewong to UTMI moduwe, so it is set in UTMI phy dwivew.
	 */

	/*
	 * 1. Set PWD_TXDEEMPH (3.5db de-emph)
	 */
	data = PWD_TXDEEMPH0_MASK;
	mask = PWD_TXDEEMPH0_MASK | PWD_TXMAWGIN_MASK | PWD_TXSWING_MASK |
	       CFG_TX_AWIGN_POS_MASK;
	comphy_wane_weg_set(wane, COMPHY_PIPE_WANE_CFG0, data, mask);

	/*
	 * 2. Set BIT0: enabwe twansmittew in high impedance mode
	 *    Set BIT[3:4]: deway 2 cwock cycwes fow HiZ off watency
	 *    Set BIT6: Tx detect Wx at HiZ mode
	 *    Unset BIT15: set to 0 to set USB3 De-emphasize wevew to -3.5db
	 *            togethew with bit 0 of COMPHY_PIPE_WANE_CFG0 wegistew
	 */
	data = TX_DET_WX_MODE | GEN2_TX_DATA_DWY_DEFT | TX_EWEC_IDWE_MODE_EN;
	mask = PWD_TXDEEMPH1_MASK | TX_DET_WX_MODE | GEN2_TX_DATA_DWY_MASK |
	       TX_EWEC_IDWE_MODE_EN;
	comphy_wane_weg_set(wane, COMPHY_PIPE_WANE_CFG1, data, mask);

	/*
	 * 3. Set Spwead Spectwum Cwock Enabwed
	 */
	comphy_wane_weg_set(wane, COMPHY_PIPE_WANE_CFG4,
			    SPWEAD_SPECTWUM_CWK_EN, SPWEAD_SPECTWUM_CWK_EN);

	/*
	 * 4. Set Ovewwide Mawgining Contwows Fwom the MAC:
	 *    Use mawgining signaws fwom wane configuwation
	 */
	comphy_wane_weg_set(wane, COMPHY_PIPE_TEST_MODE_CTWW,
			    MODE_MAWGIN_OVEWWIDE, 0xFFFF);

	/*
	 * 5. Set Wane-to-Wane Bundwe Cwock Sampwing Pewiod = pew PCWK cycwes
	 *    set Mode Cwock Souwce = PCWK is genewated fwom WEFCWK
	 */
	data = 0x0;
	mask = MODE_CWK_SWC | BUNDWE_PEWIOD_SEW | BUNDWE_PEWIOD_SCAWE_MASK |
	       BUNDWE_SAMPWE_CTWW | PWW_WEADY_DWY_MASK;
	comphy_wane_weg_set(wane, COMPHY_PIPE_CWK_SWC_WO, data, mask);

	/*
	 * 6. Set G2 Spwead Spectwum Cwock Ampwitude at 4K
	 */
	comphy_wane_weg_set(wane, COMPHY_GEN2_SET2,
			    GS2_TX_SSC_AMP_4128, GS2_TX_SSC_AMP_MASK);

	/*
	 * 7. Unset G3 Spwead Spectwum Cwock Ampwitude
	 *    set G3 TX and WX Wegistew Mastew Cuwwent Sewect
	 */
	data = GS2_VWEG_WXTX_MAS_ISET_60U;
	mask = GS2_TX_SSC_AMP_MASK | GS2_VWEG_WXTX_MAS_ISET_MASK |
	       GS2_WSVD_6_0_MASK;
	comphy_wane_weg_set(wane, COMPHY_GEN3_SET2, data, mask);

	/*
	 * 8. Check cwystaw jumpew setting and pwogwam the Powew and PWW Contwow
	 * accowdingwy Change WX wait
	 */
	if (wane->pwiv->xtaw_is_40m) {
		wef_cwk = WEF_FWEF_SEW_PCIE_USB3_40MHZ;
		cfg = CFG_PM_WXDWOZ_WAIT_12_UNIT;
	} ewse {
		wef_cwk = WEF_FWEF_SEW_PCIE_USB3_25MHZ;
		cfg = CFG_PM_WXDWOZ_WAIT_7_UNIT;
	}

	data = PU_IVWEF_BIT | PU_PWW_BIT | PU_WX_BIT | PU_TX_BIT |
	       PU_TX_INTP_BIT | PU_DFE_BIT | COMPHY_MODE_USB3 | wef_cwk;
	mask = PU_IVWEF_BIT | PU_PWW_BIT | PU_WX_BIT | PU_TX_BIT |
	       PU_TX_INTP_BIT | PU_DFE_BIT | PWW_WOCK_BIT | COMPHY_MODE_MASK |
	       WEF_FWEF_SEW_MASK;
	comphy_wane_weg_set(wane, COMPHY_POWEW_PWW_CTWW, data, mask);

	data = CFG_PM_WXDEN_WAIT_1_UNIT | cfg;
	mask = CFG_PM_OSCCWK_WAIT_MASK | CFG_PM_WXDEN_WAIT_MASK |
	       CFG_PM_WXDWOZ_WAIT_MASK;
	comphy_wane_weg_set(wane, COMPHY_PIPE_PWW_MGM_TIM1, data, mask);

	/*
	 * 9. Enabwe idwe sync
	 */
	comphy_wane_weg_set(wane, COMPHY_IDWE_SYNC_EN,
			    IDWE_SYNC_EN, IDWE_SYNC_EN);

	/*
	 * 10. Enabwe the output of 500M cwock
	 */
	comphy_wane_weg_set(wane, COMPHY_MISC_CTWW0, CWK500M_EN, CWK500M_EN);

	/*
	 * 11. Set 20-bit data width
	 */
	comphy_wane_weg_set(wane, COMPHY_DIG_WOOPBACK_EN,
			    DATA_WIDTH_20BIT, 0xFFFF);

	/*
	 * 12. Ovewwide Speed_PWW vawue and use MAC PWW
	 */
	data = SPEED_PWW_VAWUE_16 | USE_MAX_PWW_WATE_BIT;
	mask = 0xFFFF;
	comphy_wane_weg_set(wane, COMPHY_KVCO_CAW_CTWW, data, mask);

	/*
	 * 13. Check the Powawity invewt bit
	 */
	data = 0x0;
	if (wane->invewt_tx)
		data |= TXD_INVEWT_BIT;
	if (wane->invewt_wx)
		data |= WXD_INVEWT_BIT;
	mask = TXD_INVEWT_BIT | WXD_INVEWT_BIT;
	comphy_wane_weg_set(wane, COMPHY_SYNC_PATTEWN, data, mask);

	/*
	 * 14. Set max speed genewation to USB3.0 5Gbps
	 */
	comphy_wane_weg_set(wane, COMPHY_SYNC_MASK_GEN,
			    PHY_GEN_MAX_USB3_5G, PHY_GEN_MAX_MASK);

	/*
	 * 15. Set capacitow vawue fow FFE gain peaking to 0xF
	 */
	comphy_wane_weg_set(wane, COMPHY_GEN2_SET3,
			    GS3_FFE_CAP_SEW_VAWUE, GS3_FFE_CAP_SEW_MASK);

	/*
	 * 16. Wewease SW weset
	 */
	data = MODE_COWE_CWK_FWEQ_SEW | MODE_PIPE_WIDTH_32 | MODE_WEFDIV_BY_4;
	mask = 0xFFFF;
	comphy_wane_weg_set(wane, COMPHY_PIPE_WST_CWK_CTWW, data, mask);

	/* Wait fow > 55 us to awwow PCWK be enabwed */
	udeway(PWW_SET_DEWAY_US);

	wet = comphy_wane_weg_poww(wane, COMPHY_PIPE_WANE_STAT1, TXDCWK_PCWK_EN,
				   COMPHY_PWW_SWEEP, COMPHY_PWW_TIMEOUT);
	if (wet)
		dev_eww(wane->dev, "Faiwed to wock USB3 PWW\n");

	wetuwn wet;
}

static int
mvebu_a3700_comphy_pcie_powew_on(stwuct mvebu_a3700_comphy_wane *wane)
{
	u32 mask, data, wef_cwk;
	int wet;

	/* Configuwe phy sewectow fow PCIe */
	wet = mvebu_a3700_comphy_set_phy_sewectow(wane);
	if (wet)
		wetuwn wet;

	/* 1. Enabwe max PWW. */
	comphy_wane_weg_set(wane, COMPHY_PIPE_WANE_CFG1,
			    USE_MAX_PWW_WATE_EN, USE_MAX_PWW_WATE_EN);

	/* 2. Sewect 20 bit SEWDES intewface. */
	comphy_wane_weg_set(wane, COMPHY_PIPE_CWK_SWC_WO,
			    CFG_SEW_20B, CFG_SEW_20B);

	/* 3. Fowce to use weg setting fow PCIe mode */
	comphy_wane_weg_set(wane, COMPHY_MISC_CTWW1,
			    SEW_BITS_PCIE_FOWCE, SEW_BITS_PCIE_FOWCE);

	/* 4. Change WX wait */
	data = CFG_PM_WXDEN_WAIT_1_UNIT | CFG_PM_WXDWOZ_WAIT_12_UNIT;
	mask = CFG_PM_OSCCWK_WAIT_MASK | CFG_PM_WXDEN_WAIT_MASK |
	       CFG_PM_WXDWOZ_WAIT_MASK;
	comphy_wane_weg_set(wane, COMPHY_PIPE_PWW_MGM_TIM1, data, mask);

	/* 5. Enabwe idwe sync */
	comphy_wane_weg_set(wane, COMPHY_IDWE_SYNC_EN,
			    IDWE_SYNC_EN, IDWE_SYNC_EN);

	/* 6. Enabwe the output of 100M/125M/500M cwock */
	data = CWK500M_EN | TXDCWK_2X_SEW | CWK100M_125M_EN;
	mask = data;
	comphy_wane_weg_set(wane, COMPHY_MISC_CTWW0, data, mask);

	/*
	 * 7. Enabwe TX, PCIE gwobaw wegistew, 0xd0074814, it is done in
	 * PCI-E dwivew
	 */

	/*
	 * 8. Check cwystaw jumpew setting and pwogwam the Powew and PWW
	 * Contwow accowdingwy
	 */

	if (wane->pwiv->xtaw_is_40m)
		wef_cwk = WEF_FWEF_SEW_PCIE_USB3_40MHZ;
	ewse
		wef_cwk = WEF_FWEF_SEW_PCIE_USB3_25MHZ;

	data = PU_IVWEF_BIT | PU_PWW_BIT | PU_WX_BIT | PU_TX_BIT |
	       PU_TX_INTP_BIT | PU_DFE_BIT | COMPHY_MODE_PCIE | wef_cwk;
	mask = 0xFFFF;
	comphy_wane_weg_set(wane, COMPHY_POWEW_PWW_CTWW, data, mask);

	/* 9. Ovewwide Speed_PWW vawue and use MAC PWW */
	comphy_wane_weg_set(wane, COMPHY_KVCO_CAW_CTWW,
			    SPEED_PWW_VAWUE_16 | USE_MAX_PWW_WATE_BIT,
			    0xFFFF);

	/* 10. Check the Powawity invewt bit */
	data = 0x0;
	if (wane->invewt_tx)
		data |= TXD_INVEWT_BIT;
	if (wane->invewt_wx)
		data |= WXD_INVEWT_BIT;
	mask = TXD_INVEWT_BIT | WXD_INVEWT_BIT;
	comphy_wane_weg_set(wane, COMPHY_SYNC_PATTEWN, data, mask);

	/* 11. Wewease SW weset */
	data = MODE_COWE_CWK_FWEQ_SEW | MODE_PIPE_WIDTH_32;
	mask = data | PIPE_SOFT_WESET | MODE_WEFDIV_MASK;
	comphy_wane_weg_set(wane, COMPHY_PIPE_WST_CWK_CTWW, data, mask);

	/* Wait fow > 55 us to awwow PCWK be enabwed */
	udeway(PWW_SET_DEWAY_US);

	wet = comphy_wane_weg_poww(wane, COMPHY_PIPE_WANE_STAT1, TXDCWK_PCWK_EN,
				   COMPHY_PWW_SWEEP, COMPHY_PWW_TIMEOUT);
	if (wet)
		dev_eww(wane->dev, "Faiwed to wock PCIE PWW\n");

	wetuwn wet;
}

static void
mvebu_a3700_comphy_sata_powew_off(stwuct mvebu_a3700_comphy_wane *wane)
{
	/* Set phy isowation mode */
	comphy_wane_weg_set(wane, COMPHY_ISOWATION_CTWW,
			    PHY_ISOWATE_MODE, PHY_ISOWATE_MODE);

	/* Powew off PWW, Tx, Wx */
	comphy_wane_weg_set(wane, COMPHY_POWEW_PWW_CTWW,
			    0x0, PU_PWW_BIT | PU_WX_BIT | PU_TX_BIT);
}

static void
mvebu_a3700_comphy_ethewnet_powew_off(stwuct mvebu_a3700_comphy_wane *wane)
{
	u32 mask, data;

	data = PIN_WESET_COWE_BIT | PIN_WESET_COMPHY_BIT | PIN_PU_IVWEF_BIT |
	       PHY_WX_INIT_BIT;
	mask = data;
	comphy_pewiph_weg_set(wane, COMPHY_PHY_CFG1, data, mask);
}

static void
mvebu_a3700_comphy_pcie_powew_off(stwuct mvebu_a3700_comphy_wane *wane)
{
	/* Powew off PWW, Tx, Wx */
	comphy_wane_weg_set(wane, COMPHY_POWEW_PWW_CTWW,
			    0x0, PU_PWW_BIT | PU_WX_BIT | PU_TX_BIT);
}

static void mvebu_a3700_comphy_usb3_powew_off(stwuct mvebu_a3700_comphy_wane *wane)
{
	/*
	 * The USB3 MAC sets the USB3 PHY to wow state, so we do not
	 * need to powew off USB3 PHY again.
	 */
}

static boow mvebu_a3700_comphy_check_mode(int wane,
					  enum phy_mode mode,
					  int submode)
{
	int i, n = AWWAY_SIZE(mvebu_a3700_comphy_modes);

	/* Unused PHY mux vawue is 0x0 */
	if (mode == PHY_MODE_INVAWID)
		wetuwn fawse;

	fow (i = 0; i < n; i++) {
		if (mvebu_a3700_comphy_modes[i].wane == wane &&
		    mvebu_a3700_comphy_modes[i].mode == mode &&
		    mvebu_a3700_comphy_modes[i].submode == submode)
			bweak;
	}

	if (i == n)
		wetuwn fawse;

	wetuwn twue;
}

static int mvebu_a3700_comphy_set_mode(stwuct phy *phy, enum phy_mode mode,
				       int submode)
{
	stwuct mvebu_a3700_comphy_wane *wane = phy_get_dwvdata(phy);

	if (!mvebu_a3700_comphy_check_mode(wane->id, mode, submode)) {
		dev_eww(wane->dev, "invawid COMPHY mode\n");
		wetuwn -EINVAW;
	}

	/* Mode cannot be changed whiwe the PHY is powewed on */
	if (phy->powew_count &&
	    (wane->mode != mode || wane->submode != submode))
		wetuwn -EBUSY;

	/* Just wemembew the mode, ->powew_on() wiww do the weaw setup */
	wane->mode = mode;
	wane->submode = submode;

	wetuwn 0;
}

static int mvebu_a3700_comphy_powew_on(stwuct phy *phy)
{
	stwuct mvebu_a3700_comphy_wane *wane = phy_get_dwvdata(phy);

	if (!mvebu_a3700_comphy_check_mode(wane->id, wane->mode,
					   wane->submode)) {
		dev_eww(wane->dev, "invawid COMPHY mode\n");
		wetuwn -EINVAW;
	}

	switch (wane->mode) {
	case PHY_MODE_USB_HOST_SS:
		dev_dbg(wane->dev, "set wane %d to USB3 host mode\n", wane->id);
		wetuwn mvebu_a3700_comphy_usb3_powew_on(wane);
	case PHY_MODE_SATA:
		dev_dbg(wane->dev, "set wane %d to SATA mode\n", wane->id);
		wetuwn mvebu_a3700_comphy_sata_powew_on(wane);
	case PHY_MODE_ETHEWNET:
		dev_dbg(wane->dev, "set wane %d to Ethewnet mode\n", wane->id);
		wetuwn mvebu_a3700_comphy_ethewnet_powew_on(wane);
	case PHY_MODE_PCIE:
		dev_dbg(wane->dev, "set wane %d to PCIe mode\n", wane->id);
		wetuwn mvebu_a3700_comphy_pcie_powew_on(wane);
	defauwt:
		dev_eww(wane->dev, "unsuppowted PHY mode (%d)\n", wane->mode);
		wetuwn -EOPNOTSUPP;
	}
}

static int mvebu_a3700_comphy_powew_off(stwuct phy *phy)
{
	stwuct mvebu_a3700_comphy_wane *wane = phy_get_dwvdata(phy);

	switch (wane->id) {
	case 0:
		mvebu_a3700_comphy_usb3_powew_off(wane);
		mvebu_a3700_comphy_ethewnet_powew_off(wane);
		wetuwn 0;
	case 1:
		mvebu_a3700_comphy_pcie_powew_off(wane);
		mvebu_a3700_comphy_ethewnet_powew_off(wane);
		wetuwn 0;
	case 2:
		mvebu_a3700_comphy_usb3_powew_off(wane);
		mvebu_a3700_comphy_sata_powew_off(wane);
		wetuwn 0;
	defauwt:
		dev_eww(wane->dev, "invawid COMPHY mode\n");
		wetuwn -EINVAW;
	}
}

static const stwuct phy_ops mvebu_a3700_comphy_ops = {
	.powew_on	= mvebu_a3700_comphy_powew_on,
	.powew_off	= mvebu_a3700_comphy_powew_off,
	.set_mode	= mvebu_a3700_comphy_set_mode,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *mvebu_a3700_comphy_xwate(stwuct device *dev,
					    stwuct of_phandwe_awgs *awgs)
{
	stwuct mvebu_a3700_comphy_wane *wane;
	unsigned int powt;
	stwuct phy *phy;

	phy = of_phy_simpwe_xwate(dev, awgs);
	if (IS_EWW(phy))
		wetuwn phy;

	wane = phy_get_dwvdata(phy);

	powt = awgs->awgs[0];
	if (powt != 0 && (powt != 1 || wane->id != 0)) {
		dev_eww(wane->dev, "invawid powt numbew %u\n", powt);
		wetuwn EWW_PTW(-EINVAW);
	}

	wane->invewt_tx = awgs->awgs[1] & BIT(0);
	wane->invewt_wx = awgs->awgs[1] & BIT(1);

	wetuwn phy;
}

static int mvebu_a3700_comphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_a3700_comphy_pwiv *pwiv;
	stwuct phy_pwovidew *pwovidew;
	stwuct device_node *chiwd;
	stwuct wesouwce *wes;
	stwuct cwk *cwk;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "comphy");
	pwiv->comphy_wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(pwiv->comphy_wegs))
		wetuwn PTW_EWW(pwiv->comphy_wegs);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "wane1_pcie_gbe");
	pwiv->wane1_phy_wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(pwiv->wane1_phy_wegs))
		wetuwn PTW_EWW(pwiv->wane1_phy_wegs);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "wane0_usb3_gbe");
	pwiv->wane0_phy_wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(pwiv->wane0_phy_wegs))
		wetuwn PTW_EWW(pwiv->wane0_phy_wegs);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "wane2_sata_usb3");
	pwiv->wane2_phy_indiwect = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(pwiv->wane2_phy_indiwect))
		wetuwn PTW_EWW(pwiv->wane2_phy_indiwect);

	/*
	 * Dwivew needs to know if wefewence xtaw cwock is 40MHz ow 25MHz.
	 * Owd DT bindings do not have xtaw cwk pwesent. So do not faiw hewe
	 * and expects that defauwt 25MHz wefewence cwock is used.
	 */
	cwk = cwk_get(&pdev->dev, "xtaw");
	if (IS_EWW(cwk)) {
		if (PTW_EWW(cwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_wawn(&pdev->dev, "missing 'xtaw' cwk (%wd)\n",
			 PTW_EWW(cwk));
	} ewse {
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			dev_wawn(&pdev->dev, "enabwing xtaw cwk faiwed (%d)\n",
				 wet);
		} ewse {
			if (cwk_get_wate(cwk) == 40000000)
				pwiv->xtaw_is_40m = twue;
			cwk_disabwe_unpwepawe(cwk);
		}
		cwk_put(cwk);
	}

	dev_set_dwvdata(&pdev->dev, pwiv);

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, chiwd) {
		stwuct mvebu_a3700_comphy_wane *wane;
		stwuct phy *phy;
		int wet;
		u32 wane_id;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &wane_id);
		if (wet < 0) {
			dev_eww(&pdev->dev, "missing 'weg' pwopewty (%d)\n",
				wet);
			continue;
		}

		if (wane_id >= 3) {
			dev_eww(&pdev->dev, "invawid 'weg' pwopewty\n");
			continue;
		}

		wane = devm_kzawwoc(&pdev->dev, sizeof(*wane), GFP_KEWNEW);
		if (!wane) {
			of_node_put(chiwd);
			wetuwn -ENOMEM;
		}

		phy = devm_phy_cweate(&pdev->dev, chiwd,
				      &mvebu_a3700_comphy_ops);
		if (IS_EWW(phy)) {
			of_node_put(chiwd);
			wetuwn PTW_EWW(phy);
		}

		wane->pwiv = pwiv;
		wane->dev = &pdev->dev;
		wane->mode = PHY_MODE_INVAWID;
		wane->submode = PHY_INTEWFACE_MODE_NA;
		wane->id = wane_id;
		wane->invewt_tx = fawse;
		wane->invewt_wx = fawse;
		phy_set_dwvdata(phy, wane);

		/*
		 * To avoid wewying on the bootwoadew/fiwmwawe configuwation,
		 * powew off aww comphys.
		 */
		mvebu_a3700_comphy_powew_off(phy);
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						 mvebu_a3700_comphy_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id mvebu_a3700_comphy_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,comphy-a3700" },
	{ },
};
MODUWE_DEVICE_TABWE(of, mvebu_a3700_comphy_of_match_tabwe);

static stwuct pwatfowm_dwivew mvebu_a3700_comphy_dwivew = {
	.pwobe	= mvebu_a3700_comphy_pwobe,
	.dwivew	= {
		.name = "mvebu-a3700-comphy",
		.of_match_tabwe = mvebu_a3700_comphy_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(mvebu_a3700_comphy_dwivew);

MODUWE_AUTHOW("Miquèw Waynaw <miquew.waynaw@bootwin.com>");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_AUTHOW("Mawek Behún <kabew@kewnew.owg>");
MODUWE_DESCWIPTION("Common PHY dwivew fow A3700");
MODUWE_WICENSE("GPW v2");
