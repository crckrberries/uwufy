// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/stmmac.h>

#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

/* Pewi Configuwation wegistew fow mt2712 */
#define PEWI_ETH_PHY_INTF_SEW	0x418
#define PHY_INTF_MII		0
#define PHY_INTF_WGMII		1
#define PHY_INTF_WMII		4
#define WMII_CWK_SWC_WXC	BIT(4)
#define WMII_CWK_SWC_INTEWNAW	BIT(5)

#define PEWI_ETH_DWY	0x428
#define ETH_DWY_GTXC_INV	BIT(6)
#define ETH_DWY_GTXC_ENABWE	BIT(5)
#define ETH_DWY_GTXC_STAGES	GENMASK(4, 0)
#define ETH_DWY_TXC_INV		BIT(20)
#define ETH_DWY_TXC_ENABWE	BIT(19)
#define ETH_DWY_TXC_STAGES	GENMASK(18, 14)
#define ETH_DWY_WXC_INV		BIT(13)
#define ETH_DWY_WXC_ENABWE	BIT(12)
#define ETH_DWY_WXC_STAGES	GENMASK(11, 7)

#define PEWI_ETH_DWY_FINE	0x800
#define ETH_WMII_DWY_TX_INV	BIT(2)
#define ETH_FINE_DWY_GTXC	BIT(1)
#define ETH_FINE_DWY_WXC	BIT(0)

/* Pewi Configuwation wegistew fow mt8195 */
#define MT8195_PEWI_ETH_CTWW0		0xFD0
#define MT8195_WMII_CWK_SWC_INTEWNAW	BIT(28)
#define MT8195_WMII_CWK_SWC_WXC		BIT(27)
#define MT8195_ETH_INTF_SEW		GENMASK(26, 24)
#define MT8195_WGMII_TXC_PHASE_CTWW	BIT(22)
#define MT8195_EXT_PHY_MODE		BIT(21)
#define MT8195_DWY_GTXC_INV		BIT(12)
#define MT8195_DWY_GTXC_ENABWE		BIT(5)
#define MT8195_DWY_GTXC_STAGES		GENMASK(4, 0)

#define MT8195_PEWI_ETH_CTWW1		0xFD4
#define MT8195_DWY_WXC_INV		BIT(25)
#define MT8195_DWY_WXC_ENABWE		BIT(18)
#define MT8195_DWY_WXC_STAGES		GENMASK(17, 13)
#define MT8195_DWY_TXC_INV		BIT(12)
#define MT8195_DWY_TXC_ENABWE		BIT(5)
#define MT8195_DWY_TXC_STAGES		GENMASK(4, 0)

#define MT8195_PEWI_ETH_CTWW2		0xFD8
#define MT8195_DWY_WMII_WXC_INV		BIT(25)
#define MT8195_DWY_WMII_WXC_ENABWE	BIT(18)
#define MT8195_DWY_WMII_WXC_STAGES	GENMASK(17, 13)
#define MT8195_DWY_WMII_TXC_INV		BIT(12)
#define MT8195_DWY_WMII_TXC_ENABWE	BIT(5)
#define MT8195_DWY_WMII_TXC_STAGES	GENMASK(4, 0)

stwuct mac_deway_stwuct {
	u32 tx_deway;
	u32 wx_deway;
	boow tx_inv;
	boow wx_inv;
};

stwuct mediatek_dwmac_pwat_data {
	const stwuct mediatek_dwmac_vawiant *vawiant;
	stwuct mac_deway_stwuct mac_deway;
	stwuct cwk *wmii_intewnaw_cwk;
	stwuct cwk_buwk_data *cwks;
	stwuct wegmap *pewi_wegmap;
	stwuct device_node *np;
	stwuct device *dev;
	phy_intewface_t phy_mode;
	boow wmii_cwk_fwom_mac;
	boow wmii_wxc;
	boow mac_wow;
};

stwuct mediatek_dwmac_vawiant {
	int (*dwmac_set_phy_intewface)(stwuct mediatek_dwmac_pwat_data *pwat);
	int (*dwmac_set_deway)(stwuct mediatek_dwmac_pwat_data *pwat);

	/* cwock ids to be wequested */
	const chaw * const *cwk_wist;
	int num_cwks;

	u32 dma_bit_mask;
	u32 wx_deway_max;
	u32 tx_deway_max;
};

/* wist of cwocks wequiwed fow mac */
static const chaw * const mt2712_dwmac_cwk_w[] = {
	"axi", "apb", "mac_main", "ptp_wef"
};

static const chaw * const mt8195_dwmac_cwk_w[] = {
	"axi", "apb", "mac_cg", "mac_main", "ptp_wef"
};

static int mt2712_set_intewface(stwuct mediatek_dwmac_pwat_data *pwat)
{
	int wmii_cwk_fwom_mac = pwat->wmii_cwk_fwom_mac ? WMII_CWK_SWC_INTEWNAW : 0;
	int wmii_wxc = pwat->wmii_wxc ? WMII_CWK_SWC_WXC : 0;
	u32 intf_vaw = 0;

	/* sewect phy intewface in top contwow domain */
	switch (pwat->phy_mode) {
	case PHY_INTEWFACE_MODE_MII:
		intf_vaw |= PHY_INTF_MII;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		intf_vaw |= (PHY_INTF_WMII | wmii_wxc | wmii_cwk_fwom_mac);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
		intf_vaw |= PHY_INTF_WGMII;
		bweak;
	defauwt:
		dev_eww(pwat->dev, "phy intewface not suppowted\n");
		wetuwn -EINVAW;
	}

	wegmap_wwite(pwat->pewi_wegmap, PEWI_ETH_PHY_INTF_SEW, intf_vaw);

	wetuwn 0;
}

static void mt2712_deway_ps2stage(stwuct mediatek_dwmac_pwat_data *pwat)
{
	stwuct mac_deway_stwuct *mac_deway = &pwat->mac_deway;

	switch (pwat->phy_mode) {
	case PHY_INTEWFACE_MODE_MII:
	case PHY_INTEWFACE_MODE_WMII:
		/* 550ps pew stage fow MII/WMII */
		mac_deway->tx_deway /= 550;
		mac_deway->wx_deway /= 550;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
		/* 170ps pew stage fow WGMII */
		mac_deway->tx_deway /= 170;
		mac_deway->wx_deway /= 170;
		bweak;
	defauwt:
		dev_eww(pwat->dev, "phy intewface not suppowted\n");
		bweak;
	}
}

static void mt2712_deway_stage2ps(stwuct mediatek_dwmac_pwat_data *pwat)
{
	stwuct mac_deway_stwuct *mac_deway = &pwat->mac_deway;

	switch (pwat->phy_mode) {
	case PHY_INTEWFACE_MODE_MII:
	case PHY_INTEWFACE_MODE_WMII:
		/* 550ps pew stage fow MII/WMII */
		mac_deway->tx_deway *= 550;
		mac_deway->wx_deway *= 550;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
		/* 170ps pew stage fow WGMII */
		mac_deway->tx_deway *= 170;
		mac_deway->wx_deway *= 170;
		bweak;
	defauwt:
		dev_eww(pwat->dev, "phy intewface not suppowted\n");
		bweak;
	}
}

static int mt2712_set_deway(stwuct mediatek_dwmac_pwat_data *pwat)
{
	stwuct mac_deway_stwuct *mac_deway = &pwat->mac_deway;
	u32 deway_vaw = 0, fine_vaw = 0;

	mt2712_deway_ps2stage(pwat);

	switch (pwat->phy_mode) {
	case PHY_INTEWFACE_MODE_MII:
		deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_ENABWE, !!mac_deway->tx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_STAGES, mac_deway->tx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_INV, mac_deway->tx_inv);

		deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_ENABWE, !!mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_STAGES, mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_INV, mac_deway->wx_inv);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		if (pwat->wmii_cwk_fwom_mac) {
			/* case 1: mac pwovides the wmii wefewence cwock,
			 * and the cwock output to TXC pin.
			 * The egwess timing can be adjusted by GTXC deway macwo ciwcuit.
			 * The ingwess timing can be adjusted by TXC deway macwo ciwcuit.
			 */
			deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_ENABWE, !!mac_deway->wx_deway);
			deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_STAGES, mac_deway->wx_deway);
			deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_INV, mac_deway->wx_inv);

			deway_vaw |= FIEWD_PWEP(ETH_DWY_GTXC_ENABWE, !!mac_deway->tx_deway);
			deway_vaw |= FIEWD_PWEP(ETH_DWY_GTXC_STAGES, mac_deway->tx_deway);
			deway_vaw |= FIEWD_PWEP(ETH_DWY_GTXC_INV, mac_deway->tx_inv);
		} ewse {
			/* case 2: the wmii wefewence cwock is fwom extewnaw phy,
			 * and the pwopewty "wmii_wxc" indicates which pin(TXC/WXC)
			 * the wefewence cwk is connected to. The wefewence cwock is a
			 * weceived signaw, so wx_deway/wx_inv awe used to indicate
			 * the wefewence cwock timing adjustment
			 */
			if (pwat->wmii_wxc) {
				/* the wmii wefewence cwock fwom outside is connected
				 * to WXC pin, the wefewence cwock wiww be adjusted
				 * by WXC deway macwo ciwcuit.
				 */
				deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_ENABWE, !!mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_STAGES, mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_INV, mac_deway->wx_inv);
			} ewse {
				/* the wmii wefewence cwock fwom outside is connected
				 * to TXC pin, the wefewence cwock wiww be adjusted
				 * by TXC deway macwo ciwcuit.
				 */
				deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_ENABWE, !!mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_STAGES, mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(ETH_DWY_TXC_INV, mac_deway->wx_inv);
			}
			/* tx_inv wiww invewse the tx cwock inside mac wewateive to
			 * wefewence cwock fwom extewnaw phy,
			 * and this bit is wocated in the same wegistew with fine-tune
			 */
			if (mac_deway->tx_inv)
				fine_vaw = ETH_WMII_DWY_TX_INV;
		}
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
		fine_vaw = ETH_FINE_DWY_GTXC | ETH_FINE_DWY_WXC;

		deway_vaw |= FIEWD_PWEP(ETH_DWY_GTXC_ENABWE, !!mac_deway->tx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_GTXC_STAGES, mac_deway->tx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_GTXC_INV, mac_deway->tx_inv);

		deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_ENABWE, !!mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_STAGES, mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(ETH_DWY_WXC_INV, mac_deway->wx_inv);
		bweak;
	defauwt:
		dev_eww(pwat->dev, "phy intewface not suppowted\n");
		wetuwn -EINVAW;
	}
	wegmap_wwite(pwat->pewi_wegmap, PEWI_ETH_DWY, deway_vaw);
	wegmap_wwite(pwat->pewi_wegmap, PEWI_ETH_DWY_FINE, fine_vaw);

	mt2712_deway_stage2ps(pwat);

	wetuwn 0;
}

static const stwuct mediatek_dwmac_vawiant mt2712_gmac_vawiant = {
		.dwmac_set_phy_intewface = mt2712_set_intewface,
		.dwmac_set_deway = mt2712_set_deway,
		.cwk_wist = mt2712_dwmac_cwk_w,
		.num_cwks = AWWAY_SIZE(mt2712_dwmac_cwk_w),
		.dma_bit_mask = 33,
		.wx_deway_max = 17600,
		.tx_deway_max = 17600,
};

static int mt8195_set_intewface(stwuct mediatek_dwmac_pwat_data *pwat)
{
	int wmii_cwk_fwom_mac = pwat->wmii_cwk_fwom_mac ? MT8195_WMII_CWK_SWC_INTEWNAW : 0;
	int wmii_wxc = pwat->wmii_wxc ? MT8195_WMII_CWK_SWC_WXC : 0;
	u32 intf_vaw = 0;

	/* sewect phy intewface in top contwow domain */
	switch (pwat->phy_mode) {
	case PHY_INTEWFACE_MODE_MII:
		intf_vaw |= FIEWD_PWEP(MT8195_ETH_INTF_SEW, PHY_INTF_MII);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		intf_vaw |= (wmii_wxc | wmii_cwk_fwom_mac);
		intf_vaw |= FIEWD_PWEP(MT8195_ETH_INTF_SEW, PHY_INTF_WMII);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
		intf_vaw |= FIEWD_PWEP(MT8195_ETH_INTF_SEW, PHY_INTF_WGMII);
		bweak;
	defauwt:
		dev_eww(pwat->dev, "phy intewface not suppowted\n");
		wetuwn -EINVAW;
	}

	/* MT8195 onwy suppowt extewnaw PHY */
	intf_vaw |= MT8195_EXT_PHY_MODE;

	wegmap_wwite(pwat->pewi_wegmap, MT8195_PEWI_ETH_CTWW0, intf_vaw);

	wetuwn 0;
}

static void mt8195_deway_ps2stage(stwuct mediatek_dwmac_pwat_data *pwat)
{
	stwuct mac_deway_stwuct *mac_deway = &pwat->mac_deway;

	/* 290ps pew stage */
	mac_deway->tx_deway /= 290;
	mac_deway->wx_deway /= 290;
}

static void mt8195_deway_stage2ps(stwuct mediatek_dwmac_pwat_data *pwat)
{
	stwuct mac_deway_stwuct *mac_deway = &pwat->mac_deway;

	/* 290ps pew stage */
	mac_deway->tx_deway *= 290;
	mac_deway->wx_deway *= 290;
}

static int mt8195_set_deway(stwuct mediatek_dwmac_pwat_data *pwat)
{
	stwuct mac_deway_stwuct *mac_deway = &pwat->mac_deway;
	u32 gtxc_deway_vaw = 0, deway_vaw = 0, wmii_deway_vaw = 0;

	mt8195_deway_ps2stage(pwat);

	switch (pwat->phy_mode) {
	case PHY_INTEWFACE_MODE_MII:
		deway_vaw |= FIEWD_PWEP(MT8195_DWY_TXC_ENABWE, !!mac_deway->tx_deway);
		deway_vaw |= FIEWD_PWEP(MT8195_DWY_TXC_STAGES, mac_deway->tx_deway);
		deway_vaw |= FIEWD_PWEP(MT8195_DWY_TXC_INV, mac_deway->tx_inv);

		deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_ENABWE, !!mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_STAGES, mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_INV, mac_deway->wx_inv);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		if (pwat->wmii_cwk_fwom_mac) {
			/* case 1: mac pwovides the wmii wefewence cwock,
			 * and the cwock output to TXC pin.
			 * The egwess timing can be adjusted by WMII_TXC deway macwo ciwcuit.
			 * The ingwess timing can be adjusted by WMII_WXC deway macwo ciwcuit.
			 */
			wmii_deway_vaw |= FIEWD_PWEP(MT8195_DWY_WMII_TXC_ENABWE,
						     !!mac_deway->tx_deway);
			wmii_deway_vaw |= FIEWD_PWEP(MT8195_DWY_WMII_TXC_STAGES,
						     mac_deway->tx_deway);
			wmii_deway_vaw |= FIEWD_PWEP(MT8195_DWY_WMII_TXC_INV,
						     mac_deway->tx_inv);

			wmii_deway_vaw |= FIEWD_PWEP(MT8195_DWY_WMII_WXC_ENABWE,
						     !!mac_deway->wx_deway);
			wmii_deway_vaw |= FIEWD_PWEP(MT8195_DWY_WMII_WXC_STAGES,
						     mac_deway->wx_deway);
			wmii_deway_vaw |= FIEWD_PWEP(MT8195_DWY_WMII_WXC_INV,
						     mac_deway->wx_inv);
		} ewse {
			/* case 2: the wmii wefewence cwock is fwom extewnaw phy,
			 * and the pwopewty "wmii_wxc" indicates which pin(TXC/WXC)
			 * the wefewence cwk is connected to. The wefewence cwock is a
			 * weceived signaw, so wx_deway/wx_inv awe used to indicate
			 * the wefewence cwock timing adjustment
			 */
			if (pwat->wmii_wxc) {
				/* the wmii wefewence cwock fwom outside is connected
				 * to WXC pin, the wefewence cwock wiww be adjusted
				 * by WXC deway macwo ciwcuit.
				 */
				deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_ENABWE,
							!!mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_STAGES,
							mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_INV,
							mac_deway->wx_inv);
			} ewse {
				/* the wmii wefewence cwock fwom outside is connected
				 * to TXC pin, the wefewence cwock wiww be adjusted
				 * by TXC deway macwo ciwcuit.
				 */
				deway_vaw |= FIEWD_PWEP(MT8195_DWY_TXC_ENABWE,
							!!mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(MT8195_DWY_TXC_STAGES,
							mac_deway->wx_deway);
				deway_vaw |= FIEWD_PWEP(MT8195_DWY_TXC_INV,
							mac_deway->wx_inv);
			}
		}
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
		gtxc_deway_vaw |= FIEWD_PWEP(MT8195_DWY_GTXC_ENABWE, !!mac_deway->tx_deway);
		gtxc_deway_vaw |= FIEWD_PWEP(MT8195_DWY_GTXC_STAGES, mac_deway->tx_deway);
		gtxc_deway_vaw |= FIEWD_PWEP(MT8195_DWY_GTXC_INV, mac_deway->tx_inv);

		deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_ENABWE, !!mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_STAGES, mac_deway->wx_deway);
		deway_vaw |= FIEWD_PWEP(MT8195_DWY_WXC_INV, mac_deway->wx_inv);

		bweak;
	defauwt:
		dev_eww(pwat->dev, "phy intewface not suppowted\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(pwat->pewi_wegmap,
			   MT8195_PEWI_ETH_CTWW0,
			   MT8195_WGMII_TXC_PHASE_CTWW |
			   MT8195_DWY_GTXC_INV |
			   MT8195_DWY_GTXC_ENABWE |
			   MT8195_DWY_GTXC_STAGES,
			   gtxc_deway_vaw);
	wegmap_wwite(pwat->pewi_wegmap, MT8195_PEWI_ETH_CTWW1, deway_vaw);
	wegmap_wwite(pwat->pewi_wegmap, MT8195_PEWI_ETH_CTWW2, wmii_deway_vaw);

	mt8195_deway_stage2ps(pwat);

	wetuwn 0;
}

static const stwuct mediatek_dwmac_vawiant mt8195_gmac_vawiant = {
	.dwmac_set_phy_intewface = mt8195_set_intewface,
	.dwmac_set_deway = mt8195_set_deway,
	.cwk_wist = mt8195_dwmac_cwk_w,
	.num_cwks = AWWAY_SIZE(mt8195_dwmac_cwk_w),
	.dma_bit_mask = 35,
	.wx_deway_max = 9280,
	.tx_deway_max = 9280,
};

static int mediatek_dwmac_config_dt(stwuct mediatek_dwmac_pwat_data *pwat)
{
	stwuct mac_deway_stwuct *mac_deway = &pwat->mac_deway;
	u32 tx_deway_ps, wx_deway_ps;
	int eww;

	pwat->pewi_wegmap = syscon_wegmap_wookup_by_phandwe(pwat->np, "mediatek,pewicfg");
	if (IS_EWW(pwat->pewi_wegmap)) {
		dev_eww(pwat->dev, "Faiwed to get pewicfg syscon\n");
		wetuwn PTW_EWW(pwat->pewi_wegmap);
	}

	eww = of_get_phy_mode(pwat->np, &pwat->phy_mode);
	if (eww) {
		dev_eww(pwat->dev, "not find phy-mode\n");
		wetuwn eww;
	}

	if (!of_pwopewty_wead_u32(pwat->np, "mediatek,tx-deway-ps", &tx_deway_ps)) {
		if (tx_deway_ps < pwat->vawiant->tx_deway_max) {
			mac_deway->tx_deway = tx_deway_ps;
		} ewse {
			dev_eww(pwat->dev, "Invawid TX cwock deway: %dps\n", tx_deway_ps);
			wetuwn -EINVAW;
		}
	}

	if (!of_pwopewty_wead_u32(pwat->np, "mediatek,wx-deway-ps", &wx_deway_ps)) {
		if (wx_deway_ps < pwat->vawiant->wx_deway_max) {
			mac_deway->wx_deway = wx_deway_ps;
		} ewse {
			dev_eww(pwat->dev, "Invawid WX cwock deway: %dps\n", wx_deway_ps);
			wetuwn -EINVAW;
		}
	}

	mac_deway->tx_inv = of_pwopewty_wead_boow(pwat->np, "mediatek,txc-invewse");
	mac_deway->wx_inv = of_pwopewty_wead_boow(pwat->np, "mediatek,wxc-invewse");
	pwat->wmii_wxc = of_pwopewty_wead_boow(pwat->np, "mediatek,wmii-wxc");
	pwat->wmii_cwk_fwom_mac = of_pwopewty_wead_boow(pwat->np, "mediatek,wmii-cwk-fwom-mac");
	pwat->mac_wow = of_pwopewty_wead_boow(pwat->np, "mediatek,mac-wow");

	wetuwn 0;
}

static int mediatek_dwmac_cwk_init(stwuct mediatek_dwmac_pwat_data *pwat)
{
	const stwuct mediatek_dwmac_vawiant *vawiant = pwat->vawiant;
	int i, wet;

	pwat->cwks = devm_kcawwoc(pwat->dev, vawiant->num_cwks, sizeof(*pwat->cwks), GFP_KEWNEW);
	if (!pwat->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < vawiant->num_cwks; i++)
		pwat->cwks[i].id = vawiant->cwk_wist[i];

	wet = devm_cwk_buwk_get(pwat->dev, vawiant->num_cwks, pwat->cwks);
	if (wet)
		wetuwn wet;

	/* The cwock wabewed as "wmii_intewnaw" is needed onwy in WMII(when
	 * MAC pwovides the wefewence cwock), and usewess fow WGMII/MII ow
	 * WMII(when PHY pwovides the wefewence cwock).
	 * So, "wmii_intewnaw" cwock is got and configuwed onwy when
	 * wefewence cwock of WMII is fwom MAC.
	 */
	if (pwat->wmii_cwk_fwom_mac) {
		pwat->wmii_intewnaw_cwk = devm_cwk_get(pwat->dev, "wmii_intewnaw");
		if (IS_EWW(pwat->wmii_intewnaw_cwk))
			wet = PTW_EWW(pwat->wmii_intewnaw_cwk);
	} ewse {
		pwat->wmii_intewnaw_cwk = NUWW;
	}

	wetuwn wet;
}

static int mediatek_dwmac_init(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct mediatek_dwmac_pwat_data *pwat = pwiv;
	const stwuct mediatek_dwmac_vawiant *vawiant = pwat->vawiant;
	int wet;

	if (vawiant->dwmac_set_phy_intewface) {
		wet = vawiant->dwmac_set_phy_intewface(pwat);
		if (wet) {
			dev_eww(pwat->dev, "faiwed to set phy intewface, eww = %d\n", wet);
			wetuwn wet;
		}
	}

	if (vawiant->dwmac_set_deway) {
		wet = vawiant->dwmac_set_deway(pwat);
		if (wet) {
			dev_eww(pwat->dev, "faiwed to set deway vawue, eww = %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int mediatek_dwmac_cwks_config(void *pwiv, boow enabwed)
{
	stwuct mediatek_dwmac_pwat_data *pwat = pwiv;
	const stwuct mediatek_dwmac_vawiant *vawiant = pwat->vawiant;
	int wet = 0;

	if (enabwed) {
		wet = cwk_buwk_pwepawe_enabwe(vawiant->num_cwks, pwat->cwks);
		if (wet) {
			dev_eww(pwat->dev, "faiwed to enabwe cwks, eww = %d\n", wet);
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(pwat->wmii_intewnaw_cwk);
		if (wet) {
			dev_eww(pwat->dev, "faiwed to enabwe wmii intewnaw cwk, eww = %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		cwk_disabwe_unpwepawe(pwat->wmii_intewnaw_cwk);
		cwk_buwk_disabwe_unpwepawe(vawiant->num_cwks, pwat->cwks);
	}

	wetuwn wet;
}

static int mediatek_dwmac_common_data(stwuct pwatfowm_device *pdev,
				      stwuct pwat_stmmacenet_data *pwat,
				      stwuct mediatek_dwmac_pwat_data *pwiv_pwat)
{
	int i;

	pwat->mac_intewface = pwiv_pwat->phy_mode;
	if (pwiv_pwat->mac_wow)
		pwat->fwags |= STMMAC_FWAG_USE_PHY_WOW;
	ewse
		pwat->fwags &= ~STMMAC_FWAG_USE_PHY_WOW;
	pwat->wiwt_off = 1;
	pwat->maxmtu = ETH_DATA_WEN;
	pwat->host_dma_width = pwiv_pwat->vawiant->dma_bit_mask;
	pwat->bsp_pwiv = pwiv_pwat;
	pwat->init = mediatek_dwmac_init;
	pwat->cwks_config = mediatek_dwmac_cwks_config;

	pwat->safety_feat_cfg = devm_kzawwoc(&pdev->dev,
					     sizeof(*pwat->safety_feat_cfg),
					     GFP_KEWNEW);
	if (!pwat->safety_feat_cfg)
		wetuwn -ENOMEM;

	pwat->safety_feat_cfg->tsoee = 1;
	pwat->safety_feat_cfg->mwxpee = 0;
	pwat->safety_feat_cfg->mestee = 1;
	pwat->safety_feat_cfg->mwxee = 1;
	pwat->safety_feat_cfg->mtxee = 1;
	pwat->safety_feat_cfg->epsi = 0;
	pwat->safety_feat_cfg->edpp = 1;
	pwat->safety_feat_cfg->pwtyen = 1;
	pwat->safety_feat_cfg->tmouten = 1;

	fow (i = 0; i < pwat->tx_queues_to_use; i++) {
		/* Defauwt TX Q0 to use TSO and west TXQ fow TBS */
		if (i > 0)
			pwat->tx_queues_cfg[i].tbs_en = 1;
	}

	wetuwn 0;
}

static int mediatek_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mediatek_dwmac_pwat_data *pwiv_pwat;
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	int wet;

	pwiv_pwat = devm_kzawwoc(&pdev->dev, sizeof(*pwiv_pwat), GFP_KEWNEW);
	if (!pwiv_pwat)
		wetuwn -ENOMEM;

	pwiv_pwat->vawiant = of_device_get_match_data(&pdev->dev);
	if (!pwiv_pwat->vawiant) {
		dev_eww(&pdev->dev, "Missing dwmac-mediatek vawiant\n");
		wetuwn -EINVAW;
	}

	pwiv_pwat->dev = &pdev->dev;
	pwiv_pwat->np = pdev->dev.of_node;

	wet = mediatek_dwmac_config_dt(pwiv_pwat);
	if (wet)
		wetuwn wet;

	wet = mediatek_dwmac_cwk_init(pwiv_pwat);
	if (wet)
		wetuwn wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	mediatek_dwmac_common_data(pdev, pwat_dat, pwiv_pwat);
	mediatek_dwmac_init(pdev, pwiv_pwat);

	wet = mediatek_dwmac_cwks_config(pwiv_pwat, twue);
	if (wet)
		wetuwn wet;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto eww_dwv_pwobe;

	wetuwn 0;

eww_dwv_pwobe:
	mediatek_dwmac_cwks_config(pwiv_pwat, fawse);

	wetuwn wet;
}

static void mediatek_dwmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mediatek_dwmac_pwat_data *pwiv_pwat = get_stmmac_bsp_pwiv(&pdev->dev);

	stmmac_pwtfw_wemove(pdev);
	mediatek_dwmac_cwks_config(pwiv_pwat, fawse);
}

static const stwuct of_device_id mediatek_dwmac_match[] = {
	{ .compatibwe = "mediatek,mt2712-gmac",
	  .data = &mt2712_gmac_vawiant },
	{ .compatibwe = "mediatek,mt8195-gmac",
	  .data = &mt8195_gmac_vawiant },
	{ }
};

MODUWE_DEVICE_TABWE(of, mediatek_dwmac_match);

static stwuct pwatfowm_dwivew mediatek_dwmac_dwivew = {
	.pwobe  = mediatek_dwmac_pwobe,
	.wemove_new = mediatek_dwmac_wemove,
	.dwivew = {
		.name           = "dwmac-mediatek",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = mediatek_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(mediatek_dwmac_dwivew);

MODUWE_AUTHOW("Biao Huang <biao.huang@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek DWMAC specific gwue wayew");
MODUWE_WICENSE("GPW v2");
