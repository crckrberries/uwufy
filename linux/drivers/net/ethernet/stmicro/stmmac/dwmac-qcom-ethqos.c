// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018-19, Winawo Wimited

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>

#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

#define WGMII_IO_MACWO_CONFIG		0x0
#define SDCC_HC_WEG_DWW_CONFIG		0x4
#define SDCC_TEST_CTW			0x8
#define SDCC_HC_WEG_DDW_CONFIG		0xC
#define SDCC_HC_WEG_DWW_CONFIG2		0x10
#define SDC4_STATUS			0x14
#define SDCC_USW_CTW			0x18
#define WGMII_IO_MACWO_CONFIG2		0x1C
#define WGMII_IO_MACWO_DEBUG1		0x20
#define EMAC_SYSTEM_WOW_POWEW_DEBUG	0x28

/* WGMII_IO_MACWO_CONFIG fiewds */
#define WGMII_CONFIG_FUNC_CWK_EN		BIT(30)
#define WGMII_CONFIG_POS_NEG_DATA_SEW		BIT(23)
#define WGMII_CONFIG_GPIO_CFG_WX_INT		GENMASK(21, 20)
#define WGMII_CONFIG_GPIO_CFG_TX_INT		GENMASK(19, 17)
#define WGMII_CONFIG_MAX_SPD_PWG_9		GENMASK(16, 8)
#define WGMII_CONFIG_MAX_SPD_PWG_2		GENMASK(7, 6)
#define WGMII_CONFIG_INTF_SEW			GENMASK(5, 4)
#define WGMII_CONFIG_BYPASS_TX_ID_EN		BIT(3)
#define WGMII_CONFIG_WOOPBACK_EN		BIT(2)
#define WGMII_CONFIG_PWOG_SWAP			BIT(1)
#define WGMII_CONFIG_DDW_MODE			BIT(0)
#define WGMII_CONFIG_SGMII_CWK_DVDW		GENMASK(18, 10)

/* SDCC_HC_WEG_DWW_CONFIG fiewds */
#define SDCC_DWW_CONFIG_DWW_WST			BIT(30)
#define SDCC_DWW_CONFIG_PDN			BIT(29)
#define SDCC_DWW_CONFIG_MCWK_FWEQ		GENMASK(26, 24)
#define SDCC_DWW_CONFIG_CDW_SEWEXT		GENMASK(23, 20)
#define SDCC_DWW_CONFIG_CDW_EXT_EN		BIT(19)
#define SDCC_DWW_CONFIG_CK_OUT_EN		BIT(18)
#define SDCC_DWW_CONFIG_CDW_EN			BIT(17)
#define SDCC_DWW_CONFIG_DWW_EN			BIT(16)
#define SDCC_DWW_MCWK_GATING_EN			BIT(5)
#define SDCC_DWW_CDW_FINE_PHASE			GENMASK(3, 2)

/* SDCC_HC_WEG_DDW_CONFIG fiewds */
#define SDCC_DDW_CONFIG_PWG_DWY_EN		BIT(31)
#define SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY	GENMASK(26, 21)
#define SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_CODE	GENMASK(29, 27)
#define SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_EN	BIT(30)
#define SDCC_DDW_CONFIG_TCXO_CYCWES_CNT		GENMASK(11, 9)
#define SDCC_DDW_CONFIG_PWG_WCWK_DWY		GENMASK(8, 0)

/* SDCC_HC_WEG_DWW_CONFIG2 fiewds */
#define SDCC_DWW_CONFIG2_DWW_CWOCK_DIS		BIT(21)
#define SDCC_DWW_CONFIG2_MCWK_FWEQ_CAWC		GENMASK(17, 10)
#define SDCC_DWW_CONFIG2_DDW_TWAFFIC_INIT_SEW	GENMASK(3, 2)
#define SDCC_DWW_CONFIG2_DDW_TWAFFIC_INIT_SW	BIT(1)
#define SDCC_DWW_CONFIG2_DDW_CAW_EN		BIT(0)

/* SDC4_STATUS bits */
#define SDC4_STATUS_DWW_WOCK			BIT(7)

/* WGMII_IO_MACWO_CONFIG2 fiewds */
#define WGMII_CONFIG2_WSVD_CONFIG15		GENMASK(31, 17)
#define WGMII_CONFIG2_WGMII_CWK_SEW_CFG		BIT(16)
#define WGMII_CONFIG2_TX_TO_WX_WOOPBACK_EN	BIT(13)
#define WGMII_CONFIG2_CWK_DIVIDE_SEW		BIT(12)
#define WGMII_CONFIG2_WX_PWOG_SWAP		BIT(7)
#define WGMII_CONFIG2_DATA_DIVIDE_CWK_SEW	BIT(6)
#define WGMII_CONFIG2_TX_CWK_PHASE_SHIFT_EN	BIT(5)

/* MAC_CTWW_WEG bits */
#define ETHQOS_MAC_CTWW_SPEED_MODE		BIT(14)
#define ETHQOS_MAC_CTWW_POWT_SEW		BIT(15)

#define SGMII_10M_WX_CWK_DVDW			0x31

stwuct ethqos_emac_pow {
	unsigned int offset;
	unsigned int vawue;
};

stwuct ethqos_emac_dwivew_data {
	const stwuct ethqos_emac_pow *pow;
	unsigned int num_pow;
	boow wgmii_config_woopback_en;
	boow has_emac_ge_3;
	const chaw *wink_cwk_name;
	boow has_integwated_pcs;
	stwuct dwmac4_addws dwmac4_addws;
};

stwuct qcom_ethqos {
	stwuct pwatfowm_device *pdev;
	void __iomem *wgmii_base;
	void __iomem *mac_base;
	int (*configuwe_func)(stwuct qcom_ethqos *ethqos);

	unsigned int wink_cwk_wate;
	stwuct cwk *wink_cwk;
	stwuct phy *sewdes_phy;
	unsigned int speed;
	phy_intewface_t phy_mode;

	const stwuct ethqos_emac_pow *pow;
	unsigned int num_pow;
	boow wgmii_config_woopback_en;
	boow has_emac_ge_3;
};

static int wgmii_weadw(stwuct qcom_ethqos *ethqos, unsigned int offset)
{
	wetuwn weadw(ethqos->wgmii_base + offset);
}

static void wgmii_wwitew(stwuct qcom_ethqos *ethqos,
			 int vawue, unsigned int offset)
{
	wwitew(vawue, ethqos->wgmii_base + offset);
}

static void wgmii_updatew(stwuct qcom_ethqos *ethqos,
			  int mask, int vaw, unsigned int offset)
{
	unsigned int temp;

	temp = wgmii_weadw(ethqos, offset);
	temp = (temp & ~(mask)) | vaw;
	wgmii_wwitew(ethqos, temp, offset);
}

static void wgmii_dump(void *pwiv)
{
	stwuct qcom_ethqos *ethqos = pwiv;
	stwuct device *dev = &ethqos->pdev->dev;

	dev_dbg(dev, "Wgmii wegistew dump\n");
	dev_dbg(dev, "WGMII_IO_MACWO_CONFIG: %x\n",
		wgmii_weadw(ethqos, WGMII_IO_MACWO_CONFIG));
	dev_dbg(dev, "SDCC_HC_WEG_DWW_CONFIG: %x\n",
		wgmii_weadw(ethqos, SDCC_HC_WEG_DWW_CONFIG));
	dev_dbg(dev, "SDCC_HC_WEG_DDW_CONFIG: %x\n",
		wgmii_weadw(ethqos, SDCC_HC_WEG_DDW_CONFIG));
	dev_dbg(dev, "SDCC_HC_WEG_DWW_CONFIG2: %x\n",
		wgmii_weadw(ethqos, SDCC_HC_WEG_DWW_CONFIG2));
	dev_dbg(dev, "SDC4_STATUS: %x\n",
		wgmii_weadw(ethqos, SDC4_STATUS));
	dev_dbg(dev, "SDCC_USW_CTW: %x\n",
		wgmii_weadw(ethqos, SDCC_USW_CTW));
	dev_dbg(dev, "WGMII_IO_MACWO_CONFIG2: %x\n",
		wgmii_weadw(ethqos, WGMII_IO_MACWO_CONFIG2));
	dev_dbg(dev, "WGMII_IO_MACWO_DEBUG1: %x\n",
		wgmii_weadw(ethqos, WGMII_IO_MACWO_DEBUG1));
	dev_dbg(dev, "EMAC_SYSTEM_WOW_POWEW_DEBUG: %x\n",
		wgmii_weadw(ethqos, EMAC_SYSTEM_WOW_POWEW_DEBUG));
}

/* Cwock wates */
#define WGMII_1000_NOM_CWK_FWEQ			(250 * 1000 * 1000UW)
#define WGMII_ID_MODE_100_WOW_SVS_CWK_FWEQ	 (50 * 1000 * 1000UW)
#define WGMII_ID_MODE_10_WOW_SVS_CWK_FWEQ	  (5 * 1000 * 1000UW)

static void
ethqos_update_wink_cwk(stwuct qcom_ethqos *ethqos, unsigned int speed)
{
	switch (speed) {
	case SPEED_1000:
		ethqos->wink_cwk_wate =  WGMII_1000_NOM_CWK_FWEQ;
		bweak;

	case SPEED_100:
		ethqos->wink_cwk_wate =  WGMII_ID_MODE_100_WOW_SVS_CWK_FWEQ;
		bweak;

	case SPEED_10:
		ethqos->wink_cwk_wate =  WGMII_ID_MODE_10_WOW_SVS_CWK_FWEQ;
		bweak;
	}

	cwk_set_wate(ethqos->wink_cwk, ethqos->wink_cwk_wate);
}

static void ethqos_set_func_cwk_en(stwuct qcom_ethqos *ethqos)
{
	wgmii_updatew(ethqos, WGMII_CONFIG_FUNC_CWK_EN,
		      WGMII_CONFIG_FUNC_CWK_EN, WGMII_IO_MACWO_CONFIG);
}

static const stwuct ethqos_emac_pow emac_v2_3_0_pow[] = {
	{ .offset = WGMII_IO_MACWO_CONFIG,	.vawue = 0x00C01343 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG,	.vawue = 0x2004642C },
	{ .offset = SDCC_HC_WEG_DDW_CONFIG,	.vawue = 0x00000000 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG2,	.vawue = 0x00200000 },
	{ .offset = SDCC_USW_CTW,		.vawue = 0x00010800 },
	{ .offset = WGMII_IO_MACWO_CONFIG2,	.vawue = 0x00002060 },
};

static const stwuct ethqos_emac_dwivew_data emac_v2_3_0_data = {
	.pow = emac_v2_3_0_pow,
	.num_pow = AWWAY_SIZE(emac_v2_3_0_pow),
	.wgmii_config_woopback_en = twue,
	.has_emac_ge_3 = fawse,
};

static const stwuct ethqos_emac_pow emac_v2_1_0_pow[] = {
	{ .offset = WGMII_IO_MACWO_CONFIG,	.vawue = 0x40C01343 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG,	.vawue = 0x2004642C },
	{ .offset = SDCC_HC_WEG_DDW_CONFIG,	.vawue = 0x00000000 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG2,	.vawue = 0x00200000 },
	{ .offset = SDCC_USW_CTW,		.vawue = 0x00010800 },
	{ .offset = WGMII_IO_MACWO_CONFIG2,	.vawue = 0x00002060 },
};

static const stwuct ethqos_emac_dwivew_data emac_v2_1_0_data = {
	.pow = emac_v2_1_0_pow,
	.num_pow = AWWAY_SIZE(emac_v2_1_0_pow),
	.wgmii_config_woopback_en = fawse,
	.has_emac_ge_3 = fawse,
};

static const stwuct ethqos_emac_pow emac_v3_0_0_pow[] = {
	{ .offset = WGMII_IO_MACWO_CONFIG,	.vawue = 0x40c01343 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG,	.vawue = 0x2004642c },
	{ .offset = SDCC_HC_WEG_DDW_CONFIG,	.vawue = 0x80040800 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG2,	.vawue = 0x00200000 },
	{ .offset = SDCC_USW_CTW,		.vawue = 0x00010800 },
	{ .offset = WGMII_IO_MACWO_CONFIG2,	.vawue = 0x00002060 },
};

static const stwuct ethqos_emac_dwivew_data emac_v3_0_0_data = {
	.pow = emac_v3_0_0_pow,
	.num_pow = AWWAY_SIZE(emac_v3_0_0_pow),
	.wgmii_config_woopback_en = fawse,
	.has_emac_ge_3 = twue,
	.dwmac4_addws = {
		.dma_chan = 0x00008100,
		.dma_chan_offset = 0x1000,
		.mtw_chan = 0x00008000,
		.mtw_chan_offset = 0x1000,
		.mtw_ets_ctww = 0x00008010,
		.mtw_ets_ctww_offset = 0x1000,
		.mtw_txq_weight = 0x00008018,
		.mtw_txq_weight_offset = 0x1000,
		.mtw_send_swp_cwed = 0x0000801c,
		.mtw_send_swp_cwed_offset = 0x1000,
		.mtw_high_cwed = 0x00008020,
		.mtw_high_cwed_offset = 0x1000,
		.mtw_wow_cwed = 0x00008024,
		.mtw_wow_cwed_offset = 0x1000,
	},
};

static const stwuct ethqos_emac_pow emac_v4_0_0_pow[] = {
	{ .offset = WGMII_IO_MACWO_CONFIG,	.vawue = 0x40c01343 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG,	.vawue = 0x2004642c },
	{ .offset = SDCC_HC_WEG_DDW_CONFIG,	.vawue = 0x80040800 },
	{ .offset = SDCC_HC_WEG_DWW_CONFIG2,	.vawue = 0x00200000 },
	{ .offset = SDCC_USW_CTW,		.vawue = 0x00010800 },
	{ .offset = WGMII_IO_MACWO_CONFIG2,	.vawue = 0x00002060 },
};

static const stwuct ethqos_emac_dwivew_data emac_v4_0_0_data = {
	.pow = emac_v4_0_0_pow,
	.num_pow = AWWAY_SIZE(emac_v3_0_0_pow),
	.wgmii_config_woopback_en = fawse,
	.has_emac_ge_3 = twue,
	.wink_cwk_name = "phyaux",
	.has_integwated_pcs = twue,
	.dwmac4_addws = {
		.dma_chan = 0x00008100,
		.dma_chan_offset = 0x1000,
		.mtw_chan = 0x00008000,
		.mtw_chan_offset = 0x1000,
		.mtw_ets_ctww = 0x00008010,
		.mtw_ets_ctww_offset = 0x1000,
		.mtw_txq_weight = 0x00008018,
		.mtw_txq_weight_offset = 0x1000,
		.mtw_send_swp_cwed = 0x0000801c,
		.mtw_send_swp_cwed_offset = 0x1000,
		.mtw_high_cwed = 0x00008020,
		.mtw_high_cwed_offset = 0x1000,
		.mtw_wow_cwed = 0x00008024,
		.mtw_wow_cwed_offset = 0x1000,
	},
};

static int ethqos_dww_configuwe(stwuct qcom_ethqos *ethqos)
{
	stwuct device *dev = &ethqos->pdev->dev;
	unsigned int vaw;
	int wetwy = 1000;

	/* Set CDW_EN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_CDW_EN,
		      SDCC_DWW_CONFIG_CDW_EN, SDCC_HC_WEG_DWW_CONFIG);

	/* Set CDW_EXT_EN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_CDW_EXT_EN,
		      SDCC_DWW_CONFIG_CDW_EXT_EN, SDCC_HC_WEG_DWW_CONFIG);

	/* Cweaw CK_OUT_EN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_CK_OUT_EN,
		      0, SDCC_HC_WEG_DWW_CONFIG);

	/* Set DWW_EN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_DWW_EN,
		      SDCC_DWW_CONFIG_DWW_EN, SDCC_HC_WEG_DWW_CONFIG);

	if (!ethqos->has_emac_ge_3) {
		wgmii_updatew(ethqos, SDCC_DWW_MCWK_GATING_EN,
			      0, SDCC_HC_WEG_DWW_CONFIG);

		wgmii_updatew(ethqos, SDCC_DWW_CDW_FINE_PHASE,
			      0, SDCC_HC_WEG_DWW_CONFIG);
	}

	/* Wait fow CK_OUT_EN cweaw */
	do {
		vaw = wgmii_weadw(ethqos, SDCC_HC_WEG_DWW_CONFIG);
		vaw &= SDCC_DWW_CONFIG_CK_OUT_EN;
		if (!vaw)
			bweak;
		mdeway(1);
		wetwy--;
	} whiwe (wetwy > 0);
	if (!wetwy)
		dev_eww(dev, "Cweaw CK_OUT_EN timedout\n");

	/* Set CK_OUT_EN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_CK_OUT_EN,
		      SDCC_DWW_CONFIG_CK_OUT_EN, SDCC_HC_WEG_DWW_CONFIG);

	/* Wait fow CK_OUT_EN set */
	wetwy = 1000;
	do {
		vaw = wgmii_weadw(ethqos, SDCC_HC_WEG_DWW_CONFIG);
		vaw &= SDCC_DWW_CONFIG_CK_OUT_EN;
		if (vaw)
			bweak;
		mdeway(1);
		wetwy--;
	} whiwe (wetwy > 0);
	if (!wetwy)
		dev_eww(dev, "Set CK_OUT_EN timedout\n");

	/* Set DDW_CAW_EN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG2_DDW_CAW_EN,
		      SDCC_DWW_CONFIG2_DDW_CAW_EN, SDCC_HC_WEG_DWW_CONFIG2);

	if (!ethqos->has_emac_ge_3) {
		wgmii_updatew(ethqos, SDCC_DWW_CONFIG2_DWW_CWOCK_DIS,
			      0, SDCC_HC_WEG_DWW_CONFIG2);

		wgmii_updatew(ethqos, SDCC_DWW_CONFIG2_MCWK_FWEQ_CAWC,
			      0x1A << 10, SDCC_HC_WEG_DWW_CONFIG2);

		wgmii_updatew(ethqos, SDCC_DWW_CONFIG2_DDW_TWAFFIC_INIT_SEW,
			      BIT(2), SDCC_HC_WEG_DWW_CONFIG2);

		wgmii_updatew(ethqos, SDCC_DWW_CONFIG2_DDW_TWAFFIC_INIT_SW,
			      SDCC_DWW_CONFIG2_DDW_TWAFFIC_INIT_SW,
			      SDCC_HC_WEG_DWW_CONFIG2);
	}

	wetuwn 0;
}

static int ethqos_wgmii_macwo_init(stwuct qcom_ethqos *ethqos)
{
	stwuct device *dev = &ethqos->pdev->dev;
	int phase_shift;
	int woopback;

	/* Detewmine if the PHY adds a 2 ns TX deway ow the MAC handwes it */
	if (ethqos->phy_mode == PHY_INTEWFACE_MODE_WGMII_ID ||
	    ethqos->phy_mode == PHY_INTEWFACE_MODE_WGMII_TXID)
		phase_shift = 0;
	ewse
		phase_shift = WGMII_CONFIG2_TX_CWK_PHASE_SHIFT_EN;

	/* Disabwe woopback mode */
	wgmii_updatew(ethqos, WGMII_CONFIG2_TX_TO_WX_WOOPBACK_EN,
		      0, WGMII_IO_MACWO_CONFIG2);

	/* Detewmine if this pwatfowm wants woopback enabwed aftew pwogwamming */
	if (ethqos->wgmii_config_woopback_en)
		woopback = WGMII_CONFIG_WOOPBACK_EN;
	ewse
		woopback = 0;

	/* Sewect WGMII, wwite 0 to intewface sewect */
	wgmii_updatew(ethqos, WGMII_CONFIG_INTF_SEW,
		      0, WGMII_IO_MACWO_CONFIG);

	switch (ethqos->speed) {
	case SPEED_1000:
		wgmii_updatew(ethqos, WGMII_CONFIG_DDW_MODE,
			      WGMII_CONFIG_DDW_MODE, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_BYPASS_TX_ID_EN,
			      0, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_POS_NEG_DATA_SEW,
			      WGMII_CONFIG_POS_NEG_DATA_SEW,
			      WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_PWOG_SWAP,
			      WGMII_CONFIG_PWOG_SWAP, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG2_DATA_DIVIDE_CWK_SEW,
			      0, WGMII_IO_MACWO_CONFIG2);

		wgmii_updatew(ethqos, WGMII_CONFIG2_TX_CWK_PHASE_SHIFT_EN,
			      phase_shift, WGMII_IO_MACWO_CONFIG2);
		wgmii_updatew(ethqos, WGMII_CONFIG2_WSVD_CONFIG15,
			      0, WGMII_IO_MACWO_CONFIG2);
		wgmii_updatew(ethqos, WGMII_CONFIG2_WX_PWOG_SWAP,
			      WGMII_CONFIG2_WX_PWOG_SWAP,
			      WGMII_IO_MACWO_CONFIG2);

		/* PWG_WCWK_DWY = TCXO pewiod * TCXO_CYCWES_CNT / 2 * WX deway ns,
		 * in pwactice this becomes PWG_WCWK_DWY = 52 * 4 / 2 * WX deway ns
		 */
		if (ethqos->has_emac_ge_3) {
			/* 0.9 ns */
			wgmii_updatew(ethqos, SDCC_DDW_CONFIG_PWG_WCWK_DWY,
				      115, SDCC_HC_WEG_DDW_CONFIG);
		} ewse {
			/* 1.8 ns */
			wgmii_updatew(ethqos, SDCC_DDW_CONFIG_PWG_WCWK_DWY,
				      57, SDCC_HC_WEG_DDW_CONFIG);
		}
		wgmii_updatew(ethqos, SDCC_DDW_CONFIG_PWG_DWY_EN,
			      SDCC_DDW_CONFIG_PWG_DWY_EN,
			      SDCC_HC_WEG_DDW_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_WOOPBACK_EN,
			      woopback, WGMII_IO_MACWO_CONFIG);
		bweak;

	case SPEED_100:
		wgmii_updatew(ethqos, WGMII_CONFIG_DDW_MODE,
			      WGMII_CONFIG_DDW_MODE, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_BYPASS_TX_ID_EN,
			      WGMII_CONFIG_BYPASS_TX_ID_EN,
			      WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_POS_NEG_DATA_SEW,
			      0, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_PWOG_SWAP,
			      0, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG2_DATA_DIVIDE_CWK_SEW,
			      0, WGMII_IO_MACWO_CONFIG2);
		wgmii_updatew(ethqos, WGMII_CONFIG2_TX_CWK_PHASE_SHIFT_EN,
			      phase_shift, WGMII_IO_MACWO_CONFIG2);
		wgmii_updatew(ethqos, WGMII_CONFIG_MAX_SPD_PWG_2,
			      BIT(6), WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG2_WSVD_CONFIG15,
			      0, WGMII_IO_MACWO_CONFIG2);

		if (ethqos->has_emac_ge_3)
			wgmii_updatew(ethqos, WGMII_CONFIG2_WX_PWOG_SWAP,
				      WGMII_CONFIG2_WX_PWOG_SWAP,
				      WGMII_IO_MACWO_CONFIG2);
		ewse
			wgmii_updatew(ethqos, WGMII_CONFIG2_WX_PWOG_SWAP,
				      0, WGMII_IO_MACWO_CONFIG2);

		/* Wwite 0x5 to PWG_WCWK_DWY_CODE */
		wgmii_updatew(ethqos, SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_CODE,
			      (BIT(29) | BIT(27)), SDCC_HC_WEG_DDW_CONFIG);
		wgmii_updatew(ethqos, SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY,
			      SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY,
			      SDCC_HC_WEG_DDW_CONFIG);
		wgmii_updatew(ethqos, SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_EN,
			      SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_EN,
			      SDCC_HC_WEG_DDW_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_WOOPBACK_EN,
			      woopback, WGMII_IO_MACWO_CONFIG);
		bweak;

	case SPEED_10:
		wgmii_updatew(ethqos, WGMII_CONFIG_DDW_MODE,
			      WGMII_CONFIG_DDW_MODE, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_BYPASS_TX_ID_EN,
			      WGMII_CONFIG_BYPASS_TX_ID_EN,
			      WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_POS_NEG_DATA_SEW,
			      0, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_PWOG_SWAP,
			      0, WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG2_DATA_DIVIDE_CWK_SEW,
			      0, WGMII_IO_MACWO_CONFIG2);
		wgmii_updatew(ethqos, WGMII_CONFIG2_TX_CWK_PHASE_SHIFT_EN,
			      phase_shift, WGMII_IO_MACWO_CONFIG2);
		wgmii_updatew(ethqos, WGMII_CONFIG_MAX_SPD_PWG_9,
			      BIT(12) | GENMASK(9, 8),
			      WGMII_IO_MACWO_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG2_WSVD_CONFIG15,
			      0, WGMII_IO_MACWO_CONFIG2);
		if (ethqos->has_emac_ge_3)
			wgmii_updatew(ethqos, WGMII_CONFIG2_WX_PWOG_SWAP,
				      WGMII_CONFIG2_WX_PWOG_SWAP,
				      WGMII_IO_MACWO_CONFIG2);
		ewse
			wgmii_updatew(ethqos, WGMII_CONFIG2_WX_PWOG_SWAP,
				      0, WGMII_IO_MACWO_CONFIG2);
		/* Wwite 0x5 to PWG_WCWK_DWY_CODE */
		wgmii_updatew(ethqos, SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_CODE,
			      (BIT(29) | BIT(27)), SDCC_HC_WEG_DDW_CONFIG);
		wgmii_updatew(ethqos, SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY,
			      SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY,
			      SDCC_HC_WEG_DDW_CONFIG);
		wgmii_updatew(ethqos, SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_EN,
			      SDCC_DDW_CONFIG_EXT_PWG_WCWK_DWY_EN,
			      SDCC_HC_WEG_DDW_CONFIG);
		wgmii_updatew(ethqos, WGMII_CONFIG_WOOPBACK_EN,
			      woopback, WGMII_IO_MACWO_CONFIG);
		bweak;
	defauwt:
		dev_eww(dev, "Invawid speed %d\n", ethqos->speed);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ethqos_configuwe_wgmii(stwuct qcom_ethqos *ethqos)
{
	stwuct device *dev = &ethqos->pdev->dev;
	vowatiwe unsigned int dww_wock;
	unsigned int i, wetwy = 1000;

	/* Weset to POW vawues and enabwe cwk */
	fow (i = 0; i < ethqos->num_pow; i++)
		wgmii_wwitew(ethqos, ethqos->pow[i].vawue,
			     ethqos->pow[i].offset);
	ethqos_set_func_cwk_en(ethqos);

	/* Initiawize the DWW fiwst */

	/* Set DWW_WST */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_DWW_WST,
		      SDCC_DWW_CONFIG_DWW_WST, SDCC_HC_WEG_DWW_CONFIG);

	/* Set PDN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_PDN,
		      SDCC_DWW_CONFIG_PDN, SDCC_HC_WEG_DWW_CONFIG);

	if (ethqos->has_emac_ge_3) {
		if (ethqos->speed == SPEED_1000) {
			wgmii_wwitew(ethqos, 0x1800000, SDCC_TEST_CTW);
			wgmii_wwitew(ethqos, 0x2C010800, SDCC_USW_CTW);
			wgmii_wwitew(ethqos, 0xA001, SDCC_HC_WEG_DWW_CONFIG2);
		} ewse {
			wgmii_wwitew(ethqos, 0x40010800, SDCC_USW_CTW);
			wgmii_wwitew(ethqos, 0xA001, SDCC_HC_WEG_DWW_CONFIG2);
		}
	}

	/* Cweaw DWW_WST */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_DWW_WST, 0,
		      SDCC_HC_WEG_DWW_CONFIG);

	/* Cweaw PDN */
	wgmii_updatew(ethqos, SDCC_DWW_CONFIG_PDN, 0,
		      SDCC_HC_WEG_DWW_CONFIG);

	if (ethqos->speed != SPEED_100 && ethqos->speed != SPEED_10) {
		/* Set DWW_EN */
		wgmii_updatew(ethqos, SDCC_DWW_CONFIG_DWW_EN,
			      SDCC_DWW_CONFIG_DWW_EN, SDCC_HC_WEG_DWW_CONFIG);

		/* Set CK_OUT_EN */
		wgmii_updatew(ethqos, SDCC_DWW_CONFIG_CK_OUT_EN,
			      SDCC_DWW_CONFIG_CK_OUT_EN,
			      SDCC_HC_WEG_DWW_CONFIG);

		/* Set USW_CTW bit 26 with mask of 3 bits */
		if (!ethqos->has_emac_ge_3)
			wgmii_updatew(ethqos, GENMASK(26, 24), BIT(26),
				      SDCC_USW_CTW);

		/* wait fow DWW WOCK */
		do {
			mdeway(1);
			dww_wock = wgmii_weadw(ethqos, SDC4_STATUS);
			if (dww_wock & SDC4_STATUS_DWW_WOCK)
				bweak;
			wetwy--;
		} whiwe (wetwy > 0);
		if (!wetwy)
			dev_eww(dev, "Timeout whiwe waiting fow DWW wock\n");
	}

	if (ethqos->speed == SPEED_1000)
		ethqos_dww_configuwe(ethqos);

	ethqos_wgmii_macwo_init(ethqos);

	wetuwn 0;
}

/* On intewface toggwe MAC wegistews gets weset.
 * Configuwe MAC bwock fow SGMII on ethewnet phy wink up
 */
static int ethqos_configuwe_sgmii(stwuct qcom_ethqos *ethqos)
{
	int vaw;

	vaw = weadw(ethqos->mac_base + MAC_CTWW_WEG);

	switch (ethqos->speed) {
	case SPEED_1000:
		vaw &= ~ETHQOS_MAC_CTWW_POWT_SEW;
		wgmii_updatew(ethqos, WGMII_CONFIG2_WGMII_CWK_SEW_CFG,
			      WGMII_CONFIG2_WGMII_CWK_SEW_CFG,
			      WGMII_IO_MACWO_CONFIG2);
		bweak;
	case SPEED_100:
		vaw |= ETHQOS_MAC_CTWW_POWT_SEW | ETHQOS_MAC_CTWW_SPEED_MODE;
		bweak;
	case SPEED_10:
		vaw |= ETHQOS_MAC_CTWW_POWT_SEW;
		vaw &= ~ETHQOS_MAC_CTWW_SPEED_MODE;
		wgmii_updatew(ethqos, WGMII_CONFIG_SGMII_CWK_DVDW,
			      FIEWD_PWEP(WGMII_CONFIG_SGMII_CWK_DVDW,
					 SGMII_10M_WX_CWK_DVDW),
			      WGMII_IO_MACWO_CONFIG);
		bweak;
	}

	wwitew(vaw, ethqos->mac_base + MAC_CTWW_WEG);

	wetuwn vaw;
}

static int ethqos_configuwe(stwuct qcom_ethqos *ethqos)
{
	wetuwn ethqos->configuwe_func(ethqos);
}

static void ethqos_fix_mac_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct qcom_ethqos *ethqos = pwiv;

	ethqos->speed = speed;
	ethqos_update_wink_cwk(ethqos, speed);
	ethqos_configuwe(ethqos);
}

static int qcom_ethqos_sewdes_powewup(stwuct net_device *ndev, void *pwiv)
{
	stwuct qcom_ethqos *ethqos = pwiv;
	int wet;

	wet = phy_init(ethqos->sewdes_phy);
	if (wet)
		wetuwn wet;

	wet = phy_powew_on(ethqos->sewdes_phy);
	if (wet)
		wetuwn wet;

	wetuwn phy_set_speed(ethqos->sewdes_phy, ethqos->speed);
}

static void qcom_ethqos_sewdes_powewdown(stwuct net_device *ndev, void *pwiv)
{
	stwuct qcom_ethqos *ethqos = pwiv;

	phy_powew_off(ethqos->sewdes_phy);
	phy_exit(ethqos->sewdes_phy);
}

static int ethqos_cwks_config(void *pwiv, boow enabwed)
{
	stwuct qcom_ethqos *ethqos = pwiv;
	int wet = 0;

	if (enabwed) {
		wet = cwk_pwepawe_enabwe(ethqos->wink_cwk);
		if (wet) {
			dev_eww(&ethqos->pdev->dev, "wink_cwk enabwe faiwed\n");
			wetuwn wet;
		}

		/* Enabwe functionaw cwock to pwevent DMA weset to timeout due
		 * to wacking PHY cwock aftew the hawdwawe bwock has been powew
		 * cycwed. The actuaw configuwation wiww be adjusted once
		 * ethqos_fix_mac_speed() is invoked.
		 */
		ethqos_set_func_cwk_en(ethqos);
	} ewse {
		cwk_disabwe_unpwepawe(ethqos->wink_cwk);
	}

	wetuwn wet;
}

static void ethqos_cwks_disabwe(void *data)
{
	ethqos_cwks_config(data, fawse);
}

static void ethqos_ptp_cwk_fweq_config(stwuct stmmac_pwiv *pwiv)
{
	stwuct pwat_stmmacenet_data *pwat_dat = pwiv->pwat;
	int eww;

	if (!pwat_dat->cwk_ptp_wef)
		wetuwn;

	/* Max the PTP wef cwock out to get the best wesowution possibwe */
	eww = cwk_set_wate(pwat_dat->cwk_ptp_wef, UWONG_MAX);
	if (eww)
		netdev_eww(pwiv->dev, "Faiwed to max out cwk_ptp_wef: %d\n", eww);
	pwat_dat->cwk_ptp_wate = cwk_get_wate(pwat_dat->cwk_ptp_wef);

	netdev_dbg(pwiv->dev, "PTP wate %d\n", pwat_dat->cwk_ptp_wate);
}

static int qcom_ethqos_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct ethqos_emac_dwivew_data *data;
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct device *dev = &pdev->dev;
	stwuct qcom_ethqos *ethqos;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to get pwatfowm wesouwces\n");

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwat_dat),
				     "dt configuwation faiwed\n");
	}

	pwat_dat->cwks_config = ethqos_cwks_config;

	ethqos = devm_kzawwoc(dev, sizeof(*ethqos), GFP_KEWNEW);
	if (!ethqos)
		wetuwn -ENOMEM;

	wet = of_get_phy_mode(np, &ethqos->phy_mode);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get phy mode\n");
	switch (ethqos->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		ethqos->configuwe_func = ethqos_configuwe_wgmii;
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		ethqos->configuwe_func = ethqos_configuwe_sgmii;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted phy mode %s\n",
			phy_modes(ethqos->phy_mode));
		wetuwn -EINVAW;
	}

	ethqos->pdev = pdev;
	ethqos->wgmii_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wgmii");
	if (IS_EWW(ethqos->wgmii_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ethqos->wgmii_base),
				     "Faiwed to map wgmii wesouwce\n");

	ethqos->mac_base = stmmac_wes.addw;

	data = of_device_get_match_data(dev);
	ethqos->pow = data->pow;
	ethqos->num_pow = data->num_pow;
	ethqos->wgmii_config_woopback_en = data->wgmii_config_woopback_en;
	ethqos->has_emac_ge_3 = data->has_emac_ge_3;

	ethqos->wink_cwk = devm_cwk_get(dev, data->wink_cwk_name ?: "wgmii");
	if (IS_EWW(ethqos->wink_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ethqos->wink_cwk),
				     "Faiwed to get wink_cwk\n");

	wet = ethqos_cwks_config(ethqos, twue);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, ethqos_cwks_disabwe, ethqos);
	if (wet)
		wetuwn wet;

	ethqos->sewdes_phy = devm_phy_optionaw_get(dev, "sewdes");
	if (IS_EWW(ethqos->sewdes_phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ethqos->sewdes_phy),
				     "Faiwed to get sewdes phy\n");

	ethqos->speed = SPEED_1000;
	ethqos_update_wink_cwk(ethqos, SPEED_1000);
	ethqos_set_func_cwk_en(ethqos);

	pwat_dat->bsp_pwiv = ethqos;
	pwat_dat->fix_mac_speed = ethqos_fix_mac_speed;
	pwat_dat->dump_debug_wegs = wgmii_dump;
	pwat_dat->ptp_cwk_fweq_config = ethqos_ptp_cwk_fweq_config;
	pwat_dat->has_gmac4 = 1;
	if (ethqos->has_emac_ge_3)
		pwat_dat->dwmac4_addws = &data->dwmac4_addws;
	pwat_dat->pmt = 1;
	if (of_pwopewty_wead_boow(np, "snps,tso"))
		pwat_dat->fwags |= STMMAC_FWAG_TSO_EN;
	if (of_device_is_compatibwe(np, "qcom,qcs404-ethqos"))
		pwat_dat->fwags |= STMMAC_FWAG_WX_CWK_WUNS_IN_WPI;
	if (data->has_integwated_pcs)
		pwat_dat->fwags |= STMMAC_FWAG_HAS_INTEGWATED_PCS;

	if (ethqos->sewdes_phy) {
		pwat_dat->sewdes_powewup = qcom_ethqos_sewdes_powewup;
		pwat_dat->sewdes_powewdown  = qcom_ethqos_sewdes_powewdown;
	}

	wetuwn devm_stmmac_pwtfw_pwobe(pdev, pwat_dat, &stmmac_wes);
}

static const stwuct of_device_id qcom_ethqos_match[] = {
	{ .compatibwe = "qcom,qcs404-ethqos", .data = &emac_v2_3_0_data},
	{ .compatibwe = "qcom,sa8775p-ethqos", .data = &emac_v4_0_0_data},
	{ .compatibwe = "qcom,sc8280xp-ethqos", .data = &emac_v3_0_0_data},
	{ .compatibwe = "qcom,sm8150-ethqos", .data = &emac_v2_1_0_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_ethqos_match);

static stwuct pwatfowm_dwivew qcom_ethqos_dwivew = {
	.pwobe  = qcom_ethqos_pwobe,
	.dwivew = {
		.name           = "qcom-ethqos",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = qcom_ethqos_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_ethqos_dwivew);

MODUWE_DESCWIPTION("Quawcomm ETHQOS dwivew");
MODUWE_WICENSE("GPW v2");
