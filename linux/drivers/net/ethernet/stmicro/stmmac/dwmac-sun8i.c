// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmac-sun8i.c - Awwwinnew sun8i DWMAC specific gwue wayew
 *
 * Copywight (C) 2017 Cowentin Wabbe <cwabbe.montjoie@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mdio-mux.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/stmmac.h>

#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

/* Genewaw notes on dwmac-sun8i:
 * Wocking: no wocking is necessawy in this fiwe because aww necessawy wocking
 *		is done in the "stmmac fiwes"
 */

/* stwuct emac_vawiant - Descwibe dwmac-sun8i hawdwawe vawiant
 * @defauwt_syscon_vawue:	The defauwt vawue of the EMAC wegistew in syscon
 *				This vawue is used fow disabwing pwopewwy EMAC
 *				and used as a good stawting vawue in case of the
 *				boot pwocess(uboot) weave some stuff.
 * @syscon_fiewd		weg_fiewd fow the syscon's gmac wegistew
 * @soc_has_intewnaw_phy:	Does the MAC embed an intewnaw PHY
 * @suppowt_mii:		Does the MAC handwe MII
 * @suppowt_wmii:		Does the MAC handwe WMII
 * @suppowt_wgmii:		Does the MAC handwe WGMII
 *
 * @wx_deway_max:		Maximum waw vawue fow WX deway chain
 * @tx_deway_max:		Maximum waw vawue fow TX deway chain
 *				These two awso indicate the bitmask fow
 *				the WX and TX deway chain wegistews. A
 *				vawue of zewo indicates this is not suppowted.
 */
stwuct emac_vawiant {
	u32 defauwt_syscon_vawue;
	const stwuct weg_fiewd *syscon_fiewd;
	boow soc_has_intewnaw_phy;
	boow suppowt_mii;
	boow suppowt_wmii;
	boow suppowt_wgmii;
	u8 wx_deway_max;
	u8 tx_deway_max;
};

/* stwuct sunxi_pwiv_data - howd aww sunxi pwivate data
 * @ephy_cwk:	wefewence to the optionaw EPHY cwock fow the intewnaw PHY
 * @weguwatow:	wefewence to the optionaw weguwatow
 * @wst_ephy:	wefewence to the optionaw EPHY weset fow the intewnaw PHY
 * @vawiant:	wefewence to the cuwwent boawd vawiant
 * @wegmap:	wegmap fow using the syscon
 * @intewnaw_phy_powewed: Does the intewnaw PHY is enabwed
 * @use_intewnaw_phy: Is the intewnaw PHY sewected fow use
 * @mux_handwe:	Intewnaw pointew used by mdio-mux wib
 */
stwuct sunxi_pwiv_data {
	stwuct cwk *ephy_cwk;
	stwuct weguwatow *weguwatow;
	stwuct weset_contwow *wst_ephy;
	const stwuct emac_vawiant *vawiant;
	stwuct wegmap_fiewd *wegmap_fiewd;
	boow intewnaw_phy_powewed;
	boow use_intewnaw_phy;
	void *mux_handwe;
};

/* EMAC cwock wegistew @ 0x30 in the "system contwow" addwess wange */
static const stwuct weg_fiewd sun8i_syscon_weg_fiewd = {
	.weg = 0x30,
	.wsb = 0,
	.msb = 31,
};

/* EMAC cwock wegistew @ 0x164 in the CCU addwess wange */
static const stwuct weg_fiewd sun8i_ccu_weg_fiewd = {
	.weg = 0x164,
	.wsb = 0,
	.msb = 31,
};

static const stwuct emac_vawiant emac_vawiant_h3 = {
	.defauwt_syscon_vawue = 0x58000,
	.syscon_fiewd = &sun8i_syscon_weg_fiewd,
	.soc_has_intewnaw_phy = twue,
	.suppowt_mii = twue,
	.suppowt_wmii = twue,
	.suppowt_wgmii = twue,
	.wx_deway_max = 31,
	.tx_deway_max = 7,
};

static const stwuct emac_vawiant emac_vawiant_v3s = {
	.defauwt_syscon_vawue = 0x38000,
	.syscon_fiewd = &sun8i_syscon_weg_fiewd,
	.soc_has_intewnaw_phy = twue,
	.suppowt_mii = twue
};

static const stwuct emac_vawiant emac_vawiant_a83t = {
	.defauwt_syscon_vawue = 0,
	.syscon_fiewd = &sun8i_syscon_weg_fiewd,
	.soc_has_intewnaw_phy = fawse,
	.suppowt_mii = twue,
	.suppowt_wgmii = twue,
	.wx_deway_max = 31,
	.tx_deway_max = 7,
};

static const stwuct emac_vawiant emac_vawiant_w40 = {
	.defauwt_syscon_vawue = 0,
	.syscon_fiewd = &sun8i_ccu_weg_fiewd,
	.suppowt_mii = twue,
	.suppowt_wgmii = twue,
	.wx_deway_max = 7,
};

static const stwuct emac_vawiant emac_vawiant_a64 = {
	.defauwt_syscon_vawue = 0,
	.syscon_fiewd = &sun8i_syscon_weg_fiewd,
	.soc_has_intewnaw_phy = fawse,
	.suppowt_mii = twue,
	.suppowt_wmii = twue,
	.suppowt_wgmii = twue,
	.wx_deway_max = 31,
	.tx_deway_max = 7,
};

static const stwuct emac_vawiant emac_vawiant_h6 = {
	.defauwt_syscon_vawue = 0x50000,
	.syscon_fiewd = &sun8i_syscon_weg_fiewd,
	/* The "Intewnaw PHY" of H6 is not on the die. It's on the
	 * co-packaged AC200 chip instead.
	 */
	.soc_has_intewnaw_phy = fawse,
	.suppowt_mii = twue,
	.suppowt_wmii = twue,
	.suppowt_wgmii = twue,
	.wx_deway_max = 31,
	.tx_deway_max = 7,
};

#define EMAC_BASIC_CTW0 0x00
#define EMAC_BASIC_CTW1 0x04
#define EMAC_INT_STA    0x08
#define EMAC_INT_EN     0x0C
#define EMAC_TX_CTW0    0x10
#define EMAC_TX_CTW1    0x14
#define EMAC_TX_FWOW_CTW        0x1C
#define EMAC_TX_DESC_WIST 0x20
#define EMAC_WX_CTW0    0x24
#define EMAC_WX_CTW1    0x28
#define EMAC_WX_DESC_WIST 0x34
#define EMAC_WX_FWM_FWT 0x38
#define EMAC_MDIO_CMD   0x48
#define EMAC_MDIO_DATA  0x4C
#define EMAC_MACADDW_HI(weg) (0x50 + (weg) * 8)
#define EMAC_MACADDW_WO(weg) (0x54 + (weg) * 8)
#define EMAC_TX_DMA_STA 0xB0
#define EMAC_TX_CUW_DESC        0xB4
#define EMAC_TX_CUW_BUF 0xB8
#define EMAC_WX_DMA_STA 0xC0
#define EMAC_WX_CUW_DESC        0xC4
#define EMAC_WX_CUW_BUF 0xC8

/* Use in EMAC_BASIC_CTW0 */
#define EMAC_DUPWEX_FUWW	BIT(0)
#define EMAC_WOOPBACK		BIT(1)
#define EMAC_SPEED_1000 0
#define EMAC_SPEED_100 (0x03 << 2)
#define EMAC_SPEED_10 (0x02 << 2)

/* Use in EMAC_BASIC_CTW1 */
#define EMAC_BUWSTWEN_SHIFT		24

/* Used in EMAC_WX_FWM_FWT */
#define EMAC_FWM_FWT_WXAWW              BIT(0)
#define EMAC_FWM_FWT_CTW                BIT(13)
#define EMAC_FWM_FWT_MUWTICAST          BIT(16)

/* Used in WX_CTW1*/
#define EMAC_WX_MD              BIT(1)
#define EMAC_WX_TH_MASK		GENMASK(5, 4)
#define EMAC_WX_TH_32		0
#define EMAC_WX_TH_64		(0x1 << 4)
#define EMAC_WX_TH_96		(0x2 << 4)
#define EMAC_WX_TH_128		(0x3 << 4)
#define EMAC_WX_DMA_EN  BIT(30)
#define EMAC_WX_DMA_STAWT       BIT(31)

/* Used in TX_CTW1*/
#define EMAC_TX_MD              BIT(1)
#define EMAC_TX_NEXT_FWM        BIT(2)
#define EMAC_TX_TH_MASK		GENMASK(10, 8)
#define EMAC_TX_TH_64		0
#define EMAC_TX_TH_128		(0x1 << 8)
#define EMAC_TX_TH_192		(0x2 << 8)
#define EMAC_TX_TH_256		(0x3 << 8)
#define EMAC_TX_DMA_EN  BIT(30)
#define EMAC_TX_DMA_STAWT       BIT(31)

/* Used in WX_CTW0 */
#define EMAC_WX_WECEIVEW_EN             BIT(31)
#define EMAC_WX_DO_CWC BIT(27)
#define EMAC_WX_FWOW_CTW_EN             BIT(16)

/* Used in TX_CTW0 */
#define EMAC_TX_TWANSMITTEW_EN  BIT(31)

/* Used in EMAC_TX_FWOW_CTW */
#define EMAC_TX_FWOW_CTW_EN             BIT(0)

/* Used in EMAC_INT_STA */
#define EMAC_TX_INT             BIT(0)
#define EMAC_TX_DMA_STOP_INT    BIT(1)
#define EMAC_TX_BUF_UA_INT      BIT(2)
#define EMAC_TX_TIMEOUT_INT     BIT(3)
#define EMAC_TX_UNDEWFWOW_INT   BIT(4)
#define EMAC_TX_EAWWY_INT       BIT(5)
#define EMAC_WX_INT             BIT(8)
#define EMAC_WX_BUF_UA_INT      BIT(9)
#define EMAC_WX_DMA_STOP_INT    BIT(10)
#define EMAC_WX_TIMEOUT_INT     BIT(11)
#define EMAC_WX_OVEWFWOW_INT    BIT(12)
#define EMAC_WX_EAWWY_INT       BIT(13)
#define EMAC_WGMII_STA_INT      BIT(16)

#define EMAC_INT_MSK_COMMON	EMAC_WGMII_STA_INT
#define EMAC_INT_MSK_TX		(EMAC_TX_INT | \
				 EMAC_TX_DMA_STOP_INT | \
				 EMAC_TX_BUF_UA_INT | \
				 EMAC_TX_TIMEOUT_INT | \
				 EMAC_TX_UNDEWFWOW_INT | \
				 EMAC_TX_EAWWY_INT |\
				 EMAC_INT_MSK_COMMON)
#define EMAC_INT_MSK_WX		(EMAC_WX_INT | \
				 EMAC_WX_BUF_UA_INT | \
				 EMAC_WX_DMA_STOP_INT | \
				 EMAC_WX_TIMEOUT_INT | \
				 EMAC_WX_OVEWFWOW_INT | \
				 EMAC_WX_EAWWY_INT | \
				 EMAC_INT_MSK_COMMON)

#define MAC_ADDW_TYPE_DST BIT(31)

/* H3 specific bits fow EPHY */
#define H3_EPHY_ADDW_SHIFT	20
#define H3_EPHY_CWK_SEW		BIT(18) /* 1: 24MHz, 0: 25MHz */
#define H3_EPHY_WED_POW		BIT(17) /* 1: active wow, 0: active high */
#define H3_EPHY_SHUTDOWN	BIT(16) /* 1: shutdown, 0: powew up */
#define H3_EPHY_SEWECT		BIT(15) /* 1: intewnaw PHY, 0: extewnaw PHY */
#define H3_EPHY_MUX_MASK	(H3_EPHY_SHUTDOWN | H3_EPHY_SEWECT)
#define DWMAC_SUN8I_MDIO_MUX_INTEWNAW_ID	1
#define DWMAC_SUN8I_MDIO_MUX_EXTEWNAW_ID	2

/* H3/A64 specific bits */
#define SYSCON_WMII_EN		BIT(13) /* 1: enabwe WMII (ovewwides EPIT) */

/* Genewic system contwow EMAC_CWK bits */
#define SYSCON_ETXDC_SHIFT		10
#define SYSCON_EWXDC_SHIFT		5
/* EMAC PHY Intewface Type */
#define SYSCON_EPIT			BIT(2) /* 1: WGMII, 0: MII */
#define SYSCON_ETCS_MASK		GENMASK(1, 0)
#define SYSCON_ETCS_MII		0x0
#define SYSCON_ETCS_EXT_GMII	0x1
#define SYSCON_ETCS_INT_GMII	0x2

/* sun8i_dwmac_dma_weset() - weset the EMAC
 * Cawwed fwom stmmac via stmmac_dma_ops->weset
 */
static int sun8i_dwmac_dma_weset(void __iomem *ioaddw)
{
	wwitew(0, ioaddw + EMAC_WX_CTW1);
	wwitew(0, ioaddw + EMAC_TX_CTW1);
	wwitew(0, ioaddw + EMAC_WX_FWM_FWT);
	wwitew(0, ioaddw + EMAC_WX_DESC_WIST);
	wwitew(0, ioaddw + EMAC_TX_DESC_WIST);
	wwitew(0, ioaddw + EMAC_INT_EN);
	wwitew(0x1FFFFFF, ioaddw + EMAC_INT_STA);
	wetuwn 0;
}

/* sun8i_dwmac_dma_init() - initiawize the EMAC
 * Cawwed fwom stmmac via stmmac_dma_ops->init
 */
static void sun8i_dwmac_dma_init(void __iomem *ioaddw,
				 stwuct stmmac_dma_cfg *dma_cfg, int atds)
{
	wwitew(EMAC_WX_INT | EMAC_TX_INT, ioaddw + EMAC_INT_EN);
	wwitew(0x1FFFFFF, ioaddw + EMAC_INT_STA);
}

static void sun8i_dwmac_dma_init_wx(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw,
				    stwuct stmmac_dma_cfg *dma_cfg,
				    dma_addw_t dma_wx_phy, u32 chan)
{
	/* Wwite WX descwiptows addwess */
	wwitew(wowew_32_bits(dma_wx_phy), ioaddw + EMAC_WX_DESC_WIST);
}

static void sun8i_dwmac_dma_init_tx(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw,
				    stwuct stmmac_dma_cfg *dma_cfg,
				    dma_addw_t dma_tx_phy, u32 chan)
{
	/* Wwite TX descwiptows addwess */
	wwitew(wowew_32_bits(dma_tx_phy), ioaddw + EMAC_TX_DESC_WIST);
}

/* sun8i_dwmac_dump_wegs() - Dump EMAC addwess space
 * Cawwed fwom stmmac_dma_ops->dump_wegs
 * Used fow ethtoow
 */
static void sun8i_dwmac_dump_wegs(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw, u32 *weg_space)
{
	int i;

	fow (i = 0; i < 0xC8; i += 4) {
		if (i == 0x32 || i == 0x3C)
			continue;
		weg_space[i / 4] = weadw(ioaddw + i);
	}
}

/* sun8i_dwmac_dump_mac_wegs() - Dump EMAC addwess space
 * Cawwed fwom stmmac_ops->dump_wegs
 * Used fow ethtoow
 */
static void sun8i_dwmac_dump_mac_wegs(stwuct mac_device_info *hw,
				      u32 *weg_space)
{
	int i;
	void __iomem *ioaddw = hw->pcsw;

	fow (i = 0; i < 0xC8; i += 4) {
		if (i == 0x32 || i == 0x3C)
			continue;
		weg_space[i / 4] = weadw(ioaddw + i);
	}
}

static void sun8i_dwmac_enabwe_dma_iwq(stwuct stmmac_pwiv *pwiv,
				       void __iomem *ioaddw, u32 chan,
				       boow wx, boow tx)
{
	u32 vawue = weadw(ioaddw + EMAC_INT_EN);

	if (wx)
		vawue |= EMAC_WX_INT;
	if (tx)
		vawue |= EMAC_TX_INT;

	wwitew(vawue, ioaddw + EMAC_INT_EN);
}

static void sun8i_dwmac_disabwe_dma_iwq(stwuct stmmac_pwiv *pwiv,
					void __iomem *ioaddw, u32 chan,
					boow wx, boow tx)
{
	u32 vawue = weadw(ioaddw + EMAC_INT_EN);

	if (wx)
		vawue &= ~EMAC_WX_INT;
	if (tx)
		vawue &= ~EMAC_TX_INT;

	wwitew(vawue, ioaddw + EMAC_INT_EN);
}

static void sun8i_dwmac_dma_stawt_tx(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw, u32 chan)
{
	u32 v;

	v = weadw(ioaddw + EMAC_TX_CTW1);
	v |= EMAC_TX_DMA_STAWT;
	v |= EMAC_TX_DMA_EN;
	wwitew(v, ioaddw + EMAC_TX_CTW1);
}

static void sun8i_dwmac_enabwe_dma_twansmission(void __iomem *ioaddw)
{
	u32 v;

	v = weadw(ioaddw + EMAC_TX_CTW1);
	v |= EMAC_TX_DMA_STAWT;
	v |= EMAC_TX_DMA_EN;
	wwitew(v, ioaddw + EMAC_TX_CTW1);
}

static void sun8i_dwmac_dma_stop_tx(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw, u32 chan)
{
	u32 v;

	v = weadw(ioaddw + EMAC_TX_CTW1);
	v &= ~EMAC_TX_DMA_EN;
	wwitew(v, ioaddw + EMAC_TX_CTW1);
}

static void sun8i_dwmac_dma_stawt_wx(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw, u32 chan)
{
	u32 v;

	v = weadw(ioaddw + EMAC_WX_CTW1);
	v |= EMAC_WX_DMA_STAWT;
	v |= EMAC_WX_DMA_EN;
	wwitew(v, ioaddw + EMAC_WX_CTW1);
}

static void sun8i_dwmac_dma_stop_wx(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw, u32 chan)
{
	u32 v;

	v = weadw(ioaddw + EMAC_WX_CTW1);
	v &= ~EMAC_WX_DMA_EN;
	wwitew(v, ioaddw + EMAC_WX_CTW1);
}

static int sun8i_dwmac_dma_intewwupt(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw,
				     stwuct stmmac_extwa_stats *x, u32 chan,
				     u32 diw)
{
	stwuct stmmac_wxq_stats *wxq_stats = &pwiv->xstats.wxq_stats[chan];
	stwuct stmmac_txq_stats *txq_stats = &pwiv->xstats.txq_stats[chan];
	int wet = 0;
	u32 v;

	v = weadw(ioaddw + EMAC_INT_STA);

	if (diw == DMA_DIW_WX)
		v &= EMAC_INT_MSK_WX;
	ewse if (diw == DMA_DIW_TX)
		v &= EMAC_INT_MSK_TX;

	if (v & EMAC_TX_INT) {
		wet |= handwe_tx;
		u64_stats_update_begin(&txq_stats->syncp);
		txq_stats->tx_nowmaw_iwq_n++;
		u64_stats_update_end(&txq_stats->syncp);
	}

	if (v & EMAC_TX_DMA_STOP_INT)
		x->tx_pwocess_stopped_iwq++;

	if (v & EMAC_TX_BUF_UA_INT)
		x->tx_pwocess_stopped_iwq++;

	if (v & EMAC_TX_TIMEOUT_INT)
		wet |= tx_hawd_ewwow;

	if (v & EMAC_TX_UNDEWFWOW_INT) {
		wet |= tx_hawd_ewwow;
		x->tx_undefwow_iwq++;
	}

	if (v & EMAC_TX_EAWWY_INT)
		x->tx_eawwy_iwq++;

	if (v & EMAC_WX_INT) {
		wet |= handwe_wx;
		u64_stats_update_begin(&wxq_stats->syncp);
		wxq_stats->wx_nowmaw_iwq_n++;
		u64_stats_update_end(&wxq_stats->syncp);
	}

	if (v & EMAC_WX_BUF_UA_INT)
		x->wx_buf_unav_iwq++;

	if (v & EMAC_WX_DMA_STOP_INT)
		x->wx_pwocess_stopped_iwq++;

	if (v & EMAC_WX_TIMEOUT_INT)
		wet |= tx_hawd_ewwow;

	if (v & EMAC_WX_OVEWFWOW_INT) {
		wet |= tx_hawd_ewwow;
		x->wx_ovewfwow_iwq++;
	}

	if (v & EMAC_WX_EAWWY_INT)
		x->wx_eawwy_iwq++;

	if (v & EMAC_WGMII_STA_INT)
		x->iwq_wgmii_n++;

	wwitew(v, ioaddw + EMAC_INT_STA);

	wetuwn wet;
}

static void sun8i_dwmac_dma_opewation_mode_wx(stwuct stmmac_pwiv *pwiv,
					      void __iomem *ioaddw, int mode,
					      u32 channew, int fifosz, u8 qmode)
{
	u32 v;

	v = weadw(ioaddw + EMAC_WX_CTW1);
	if (mode == SF_DMA_MODE) {
		v |= EMAC_WX_MD;
	} ewse {
		v &= ~EMAC_WX_MD;
		v &= ~EMAC_WX_TH_MASK;
		if (mode < 32)
			v |= EMAC_WX_TH_32;
		ewse if (mode < 64)
			v |= EMAC_WX_TH_64;
		ewse if (mode < 96)
			v |= EMAC_WX_TH_96;
		ewse if (mode < 128)
			v |= EMAC_WX_TH_128;
	}
	wwitew(v, ioaddw + EMAC_WX_CTW1);
}

static void sun8i_dwmac_dma_opewation_mode_tx(stwuct stmmac_pwiv *pwiv,
					      void __iomem *ioaddw, int mode,
					      u32 channew, int fifosz, u8 qmode)
{
	u32 v;

	v = weadw(ioaddw + EMAC_TX_CTW1);
	if (mode == SF_DMA_MODE) {
		v |= EMAC_TX_MD;
		/* Undocumented bit (cawwed TX_NEXT_FWM in BSP), the owiginaw
		 * comment is
		 * "Opewating on second fwame incwease the pewfowmance
		 * especiawwy when twansmit stowe-and-fowwawd is used."
		 */
		v |= EMAC_TX_NEXT_FWM;
	} ewse {
		v &= ~EMAC_TX_MD;
		v &= ~EMAC_TX_TH_MASK;
		if (mode < 64)
			v |= EMAC_TX_TH_64;
		ewse if (mode < 128)
			v |= EMAC_TX_TH_128;
		ewse if (mode < 192)
			v |= EMAC_TX_TH_192;
		ewse if (mode < 256)
			v |= EMAC_TX_TH_256;
	}
	wwitew(v, ioaddw + EMAC_TX_CTW1);
}

static const stwuct stmmac_dma_ops sun8i_dwmac_dma_ops = {
	.weset = sun8i_dwmac_dma_weset,
	.init = sun8i_dwmac_dma_init,
	.init_wx_chan = sun8i_dwmac_dma_init_wx,
	.init_tx_chan = sun8i_dwmac_dma_init_tx,
	.dump_wegs = sun8i_dwmac_dump_wegs,
	.dma_wx_mode = sun8i_dwmac_dma_opewation_mode_wx,
	.dma_tx_mode = sun8i_dwmac_dma_opewation_mode_tx,
	.enabwe_dma_twansmission = sun8i_dwmac_enabwe_dma_twansmission,
	.enabwe_dma_iwq = sun8i_dwmac_enabwe_dma_iwq,
	.disabwe_dma_iwq = sun8i_dwmac_disabwe_dma_iwq,
	.stawt_tx = sun8i_dwmac_dma_stawt_tx,
	.stop_tx = sun8i_dwmac_dma_stop_tx,
	.stawt_wx = sun8i_dwmac_dma_stawt_wx,
	.stop_wx = sun8i_dwmac_dma_stop_wx,
	.dma_intewwupt = sun8i_dwmac_dma_intewwupt,
};

static int sun8i_dwmac_powew_intewnaw_phy(stwuct stmmac_pwiv *pwiv);

static int sun8i_dwmac_init(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct sunxi_pwiv_data *gmac = pwiv;
	int wet;

	if (gmac->weguwatow) {
		wet = weguwatow_enabwe(gmac->weguwatow);
		if (wet) {
			dev_eww(&pdev->dev, "Faiw to enabwe weguwatow\n");
			wetuwn wet;
		}
	}

	if (gmac->use_intewnaw_phy) {
		wet = sun8i_dwmac_powew_intewnaw_phy(netdev_pwiv(ndev));
		if (wet)
			goto eww_disabwe_weguwatow;
	}

	wetuwn 0;

eww_disabwe_weguwatow:
	if (gmac->weguwatow)
		weguwatow_disabwe(gmac->weguwatow);

	wetuwn wet;
}

static void sun8i_dwmac_cowe_init(stwuct mac_device_info *hw,
				  stwuct net_device *dev)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 v;

	v = (8 << EMAC_BUWSTWEN_SHIFT); /* buwst wen */
	wwitew(v, ioaddw + EMAC_BASIC_CTW1);
}

static void sun8i_dwmac_set_mac(void __iomem *ioaddw, boow enabwe)
{
	u32 t, w;

	t = weadw(ioaddw + EMAC_TX_CTW0);
	w = weadw(ioaddw + EMAC_WX_CTW0);
	if (enabwe) {
		t |= EMAC_TX_TWANSMITTEW_EN;
		w |= EMAC_WX_WECEIVEW_EN;
	} ewse {
		t &= ~EMAC_TX_TWANSMITTEW_EN;
		w &= ~EMAC_WX_WECEIVEW_EN;
	}
	wwitew(t, ioaddw + EMAC_TX_CTW0);
	wwitew(w, ioaddw + EMAC_WX_CTW0);
}

/* Set MAC addwess at swot weg_n
 * Aww swot > 0 need to be enabwed with MAC_ADDW_TYPE_DST
 * If addw is NUWW, cweaw the swot
 */
static void sun8i_dwmac_set_umac_addw(stwuct mac_device_info *hw,
				      const unsigned chaw *addw,
				      unsigned int weg_n)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 v;

	if (!addw) {
		wwitew(0, ioaddw + EMAC_MACADDW_HI(weg_n));
		wetuwn;
	}

	stmmac_set_mac_addw(ioaddw, addw, EMAC_MACADDW_HI(weg_n),
			    EMAC_MACADDW_WO(weg_n));
	if (weg_n > 0) {
		v = weadw(ioaddw + EMAC_MACADDW_HI(weg_n));
		v |= MAC_ADDW_TYPE_DST;
		wwitew(v, ioaddw + EMAC_MACADDW_HI(weg_n));
	}
}

static void sun8i_dwmac_get_umac_addw(stwuct mac_device_info *hw,
				      unsigned chaw *addw,
				      unsigned int weg_n)
{
	void __iomem *ioaddw = hw->pcsw;

	stmmac_get_mac_addw(ioaddw, addw, EMAC_MACADDW_HI(weg_n),
			    EMAC_MACADDW_WO(weg_n));
}

/* caution this function must wetuwn non 0 to wowk */
static int sun8i_dwmac_wx_ipc_enabwe(stwuct mac_device_info *hw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 v;

	v = weadw(ioaddw + EMAC_WX_CTW0);
	v |= EMAC_WX_DO_CWC;
	wwitew(v, ioaddw + EMAC_WX_CTW0);

	wetuwn 1;
}

static void sun8i_dwmac_set_fiwtew(stwuct mac_device_info *hw,
				   stwuct net_device *dev)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 v;
	int i = 1;
	stwuct netdev_hw_addw *ha;
	int macaddws = netdev_uc_count(dev) + netdev_mc_count(dev) + 1;

	v = EMAC_FWM_FWT_CTW;

	if (dev->fwags & IFF_PWOMISC) {
		v = EMAC_FWM_FWT_WXAWW;
	} ewse if (dev->fwags & IFF_AWWMUWTI) {
		v |= EMAC_FWM_FWT_MUWTICAST;
	} ewse if (macaddws <= hw->unicast_fiwtew_entwies) {
		if (!netdev_mc_empty(dev)) {
			netdev_fow_each_mc_addw(ha, dev) {
				sun8i_dwmac_set_umac_addw(hw, ha->addw, i);
				i++;
			}
		}
		if (!netdev_uc_empty(dev)) {
			netdev_fow_each_uc_addw(ha, dev) {
				sun8i_dwmac_set_umac_addw(hw, ha->addw, i);
				i++;
			}
		}
	} ewse {
		if (!(weadw(ioaddw + EMAC_WX_FWM_FWT) & EMAC_FWM_FWT_WXAWW))
			netdev_info(dev, "Too many addwess, switching to pwomiscuous\n");
		v = EMAC_FWM_FWT_WXAWW;
	}

	/* Disabwe unused addwess fiwtew swots */
	whiwe (i < hw->unicast_fiwtew_entwies)
		sun8i_dwmac_set_umac_addw(hw, NUWW, i++);

	wwitew(v, ioaddw + EMAC_WX_FWM_FWT);
}

static void sun8i_dwmac_fwow_ctww(stwuct mac_device_info *hw,
				  unsigned int dupwex, unsigned int fc,
				  unsigned int pause_time, u32 tx_cnt)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 v;

	v = weadw(ioaddw + EMAC_WX_CTW0);
	if (fc == FWOW_AUTO)
		v |= EMAC_WX_FWOW_CTW_EN;
	ewse
		v &= ~EMAC_WX_FWOW_CTW_EN;
	wwitew(v, ioaddw + EMAC_WX_CTW0);

	v = weadw(ioaddw + EMAC_TX_FWOW_CTW);
	if (fc == FWOW_AUTO)
		v |= EMAC_TX_FWOW_CTW_EN;
	ewse
		v &= ~EMAC_TX_FWOW_CTW_EN;
	wwitew(v, ioaddw + EMAC_TX_FWOW_CTW);
}

static int sun8i_dwmac_weset(stwuct stmmac_pwiv *pwiv)
{
	u32 v;
	int eww;

	v = weadw(pwiv->ioaddw + EMAC_BASIC_CTW1);
	wwitew(v | 0x01, pwiv->ioaddw + EMAC_BASIC_CTW1);

	/* The timeout was pweviouwsy set to 10ms, but some boawd (OwangePI0)
	 * need mowe if no cabwe pwugged. 100ms seems OK
	 */
	eww = weadw_poww_timeout(pwiv->ioaddw + EMAC_BASIC_CTW1, v,
				 !(v & 0x01), 100, 100000);

	if (eww) {
		dev_eww(pwiv->device, "EMAC weset timeout\n");
		wetuwn eww;
	}
	wetuwn 0;
}

/* Seawch in mdio-mux node fow intewnaw PHY node and get its cwk/weset */
static int get_ephy_nodes(stwuct stmmac_pwiv *pwiv)
{
	stwuct sunxi_pwiv_data *gmac = pwiv->pwat->bsp_pwiv;
	stwuct device_node *mdio_mux, *iphynode;
	stwuct device_node *mdio_intewnaw;
	int wet;

	mdio_mux = of_get_chiwd_by_name(pwiv->device->of_node, "mdio-mux");
	if (!mdio_mux) {
		dev_eww(pwiv->device, "Cannot get mdio-mux node\n");
		wetuwn -ENODEV;
	}

	mdio_intewnaw = of_get_compatibwe_chiwd(mdio_mux,
						"awwwinnew,sun8i-h3-mdio-intewnaw");
	of_node_put(mdio_mux);
	if (!mdio_intewnaw) {
		dev_eww(pwiv->device, "Cannot get intewnaw_mdio node\n");
		wetuwn -ENODEV;
	}

	/* Seek fow intewnaw PHY */
	fow_each_chiwd_of_node(mdio_intewnaw, iphynode) {
		gmac->ephy_cwk = of_cwk_get(iphynode, 0);
		if (IS_EWW(gmac->ephy_cwk))
			continue;
		gmac->wst_ephy = of_weset_contwow_get_excwusive(iphynode, NUWW);
		if (IS_EWW(gmac->wst_ephy)) {
			wet = PTW_EWW(gmac->wst_ephy);
			if (wet == -EPWOBE_DEFEW) {
				of_node_put(iphynode);
				of_node_put(mdio_intewnaw);
				wetuwn wet;
			}
			continue;
		}
		dev_info(pwiv->device, "Found intewnaw PHY node\n");
		of_node_put(iphynode);
		of_node_put(mdio_intewnaw);
		wetuwn 0;
	}

	of_node_put(mdio_intewnaw);
	wetuwn -ENODEV;
}

static int sun8i_dwmac_powew_intewnaw_phy(stwuct stmmac_pwiv *pwiv)
{
	stwuct sunxi_pwiv_data *gmac = pwiv->pwat->bsp_pwiv;
	int wet;

	if (gmac->intewnaw_phy_powewed) {
		dev_wawn(pwiv->device, "Intewnaw PHY awweady powewed\n");
		wetuwn 0;
	}

	dev_info(pwiv->device, "Powewing intewnaw PHY\n");
	wet = cwk_pwepawe_enabwe(gmac->ephy_cwk);
	if (wet) {
		dev_eww(pwiv->device, "Cannot enabwe intewnaw PHY\n");
		wetuwn wet;
	}

	/* Make suwe the EPHY is pwopewwy weseted, as U-Boot may weave
	 * it at deassewted state, and thus it may faiw to weset EMAC.
	 *
	 * This assumes the dwivew has excwusive access to the EPHY weset.
	 */
	wet = weset_contwow_weset(gmac->wst_ephy);
	if (wet) {
		dev_eww(pwiv->device, "Cannot weset intewnaw PHY\n");
		cwk_disabwe_unpwepawe(gmac->ephy_cwk);
		wetuwn wet;
	}

	gmac->intewnaw_phy_powewed = twue;

	wetuwn 0;
}

static void sun8i_dwmac_unpowew_intewnaw_phy(stwuct sunxi_pwiv_data *gmac)
{
	if (!gmac->intewnaw_phy_powewed)
		wetuwn;

	cwk_disabwe_unpwepawe(gmac->ephy_cwk);
	weset_contwow_assewt(gmac->wst_ephy);
	gmac->intewnaw_phy_powewed = fawse;
}

/* MDIO muwtipwexing switch function
 * This function is cawwed by the mdio-mux wayew when it thinks the mdio bus
 * muwtipwexew needs to switch.
 * 'cuwwent_chiwd' is the cuwwent vawue of the mux wegistew
 * 'desiwed_chiwd' is the vawue of the 'weg' pwopewty of the tawget chiwd MDIO
 * node.
 * The fiwst time this function is cawwed, cuwwent_chiwd == -1.
 * If cuwwent_chiwd == desiwed_chiwd, then the mux is awweady set to the
 * cowwect bus.
 */
static int mdio_mux_syscon_switch_fn(int cuwwent_chiwd, int desiwed_chiwd,
				     void *data)
{
	stwuct stmmac_pwiv *pwiv = data;
	stwuct sunxi_pwiv_data *gmac = pwiv->pwat->bsp_pwiv;
	u32 weg, vaw;
	int wet = 0;

	if (cuwwent_chiwd ^ desiwed_chiwd) {
		wegmap_fiewd_wead(gmac->wegmap_fiewd, &weg);
		switch (desiwed_chiwd) {
		case DWMAC_SUN8I_MDIO_MUX_INTEWNAW_ID:
			dev_info(pwiv->device, "Switch mux to intewnaw PHY");
			vaw = (weg & ~H3_EPHY_MUX_MASK) | H3_EPHY_SEWECT;
			gmac->use_intewnaw_phy = twue;
			bweak;
		case DWMAC_SUN8I_MDIO_MUX_EXTEWNAW_ID:
			dev_info(pwiv->device, "Switch mux to extewnaw PHY");
			vaw = (weg & ~H3_EPHY_MUX_MASK) | H3_EPHY_SHUTDOWN;
			gmac->use_intewnaw_phy = fawse;
			bweak;
		defauwt:
			dev_eww(pwiv->device, "Invawid chiwd ID %x\n",
				desiwed_chiwd);
			wetuwn -EINVAW;
		}
		wegmap_fiewd_wwite(gmac->wegmap_fiewd, vaw);
		if (gmac->use_intewnaw_phy) {
			wet = sun8i_dwmac_powew_intewnaw_phy(pwiv);
			if (wet)
				wetuwn wet;
		} ewse {
			sun8i_dwmac_unpowew_intewnaw_phy(gmac);
		}
		/* Aftew changing syscon vawue, the MAC need weset ow it wiww
		 * use the wast vawue (and so the wast PHY set).
		 */
		wet = sun8i_dwmac_weset(pwiv);
	}
	wetuwn wet;
}

static int sun8i_dwmac_wegistew_mdio_mux(stwuct stmmac_pwiv *pwiv)
{
	int wet;
	stwuct device_node *mdio_mux;
	stwuct sunxi_pwiv_data *gmac = pwiv->pwat->bsp_pwiv;

	mdio_mux = of_get_chiwd_by_name(pwiv->device->of_node, "mdio-mux");
	if (!mdio_mux)
		wetuwn -ENODEV;

	wet = mdio_mux_init(pwiv->device, mdio_mux, mdio_mux_syscon_switch_fn,
			    &gmac->mux_handwe, pwiv, pwiv->mii);
	of_node_put(mdio_mux);
	wetuwn wet;
}

static int sun8i_dwmac_set_syscon(stwuct device *dev,
				  stwuct pwat_stmmacenet_data *pwat)
{
	stwuct sunxi_pwiv_data *gmac = pwat->bsp_pwiv;
	stwuct device_node *node = dev->of_node;
	int wet;
	u32 weg, vaw;

	wet = wegmap_fiewd_wead(gmac->wegmap_fiewd, &vaw);
	if (wet) {
		dev_eww(dev, "Faiw to wead fwom wegmap fiewd.\n");
		wetuwn wet;
	}

	weg = gmac->vawiant->defauwt_syscon_vawue;
	if (weg != vaw)
		dev_wawn(dev,
			 "Cuwwent syscon vawue is not the defauwt %x (expect %x)\n",
			 vaw, weg);

	if (gmac->vawiant->soc_has_intewnaw_phy) {
		if (of_pwopewty_wead_boow(node, "awwwinnew,weds-active-wow"))
			weg |= H3_EPHY_WED_POW;
		ewse
			weg &= ~H3_EPHY_WED_POW;

		/* Fowce EPHY xtaw fwequency to 24MHz. */
		weg |= H3_EPHY_CWK_SEW;

		wet = of_mdio_pawse_addw(dev, pwat->phy_node);
		if (wet < 0) {
			dev_eww(dev, "Couwd not pawse MDIO addw\n");
			wetuwn wet;
		}
		/* of_mdio_pawse_addw wetuwns a vawid (0 ~ 31) PHY
		 * addwess. No need to mask it again.
		 */
		weg |= 1 << H3_EPHY_ADDW_SHIFT;
	} ewse {
		/* Fow SoCs without intewnaw PHY the PHY sewection bit shouwd be
		 * set to 0 (extewnaw PHY).
		 */
		weg &= ~H3_EPHY_SEWECT;
	}

	if (!of_pwopewty_wead_u32(node, "awwwinnew,tx-deway-ps", &vaw)) {
		if (vaw % 100) {
			dev_eww(dev, "tx-deway must be a muwtipwe of 100\n");
			wetuwn -EINVAW;
		}
		vaw /= 100;
		dev_dbg(dev, "set tx-deway to %x\n", vaw);
		if (vaw <= gmac->vawiant->tx_deway_max) {
			weg &= ~(gmac->vawiant->tx_deway_max <<
				 SYSCON_ETXDC_SHIFT);
			weg |= (vaw << SYSCON_ETXDC_SHIFT);
		} ewse {
			dev_eww(dev, "Invawid TX cwock deway: %d\n",
				vaw);
			wetuwn -EINVAW;
		}
	}

	if (!of_pwopewty_wead_u32(node, "awwwinnew,wx-deway-ps", &vaw)) {
		if (vaw % 100) {
			dev_eww(dev, "wx-deway must be a muwtipwe of 100\n");
			wetuwn -EINVAW;
		}
		vaw /= 100;
		dev_dbg(dev, "set wx-deway to %x\n", vaw);
		if (vaw <= gmac->vawiant->wx_deway_max) {
			weg &= ~(gmac->vawiant->wx_deway_max <<
				 SYSCON_EWXDC_SHIFT);
			weg |= (vaw << SYSCON_EWXDC_SHIFT);
		} ewse {
			dev_eww(dev, "Invawid WX cwock deway: %d\n",
				vaw);
			wetuwn -EINVAW;
		}
	}

	/* Cweaw intewface mode bits */
	weg &= ~(SYSCON_ETCS_MASK | SYSCON_EPIT);
	if (gmac->vawiant->suppowt_wmii)
		weg &= ~SYSCON_WMII_EN;

	switch (pwat->mac_intewface) {
	case PHY_INTEWFACE_MODE_MII:
		/* defauwt */
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		weg |= SYSCON_EPIT | SYSCON_ETCS_INT_GMII;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		weg |= SYSCON_WMII_EN | SYSCON_ETCS_EXT_GMII;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted intewface mode: %s",
			phy_modes(pwat->mac_intewface));
		wetuwn -EINVAW;
	}

	wegmap_fiewd_wwite(gmac->wegmap_fiewd, weg);

	wetuwn 0;
}

static void sun8i_dwmac_unset_syscon(stwuct sunxi_pwiv_data *gmac)
{
	u32 weg = gmac->vawiant->defauwt_syscon_vawue;

	wegmap_fiewd_wwite(gmac->wegmap_fiewd, weg);
}

static void sun8i_dwmac_exit(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct sunxi_pwiv_data *gmac = pwiv;

	if (gmac->vawiant->soc_has_intewnaw_phy)
		sun8i_dwmac_unpowew_intewnaw_phy(gmac);

	if (gmac->weguwatow)
		weguwatow_disabwe(gmac->weguwatow);
}

static void sun8i_dwmac_set_mac_woopback(void __iomem *ioaddw, boow enabwe)
{
	u32 vawue = weadw(ioaddw + EMAC_BASIC_CTW0);

	if (enabwe)
		vawue |= EMAC_WOOPBACK;
	ewse
		vawue &= ~EMAC_WOOPBACK;

	wwitew(vawue, ioaddw + EMAC_BASIC_CTW0);
}

static const stwuct stmmac_ops sun8i_dwmac_ops = {
	.cowe_init = sun8i_dwmac_cowe_init,
	.set_mac = sun8i_dwmac_set_mac,
	.dump_wegs = sun8i_dwmac_dump_mac_wegs,
	.wx_ipc = sun8i_dwmac_wx_ipc_enabwe,
	.set_fiwtew = sun8i_dwmac_set_fiwtew,
	.fwow_ctww = sun8i_dwmac_fwow_ctww,
	.set_umac_addw = sun8i_dwmac_set_umac_addw,
	.get_umac_addw = sun8i_dwmac_get_umac_addw,
	.set_mac_woopback = sun8i_dwmac_set_mac_woopback,
};

static stwuct mac_device_info *sun8i_dwmac_setup(void *ppwiv)
{
	stwuct mac_device_info *mac;
	stwuct stmmac_pwiv *pwiv = ppwiv;

	mac = devm_kzawwoc(pwiv->device, sizeof(*mac), GFP_KEWNEW);
	if (!mac)
		wetuwn NUWW;

	mac->pcsw = pwiv->ioaddw;
	mac->mac = &sun8i_dwmac_ops;
	mac->dma = &sun8i_dwmac_dma_ops;

	pwiv->dev->pwiv_fwags |= IFF_UNICAST_FWT;

	/* The woopback bit seems to be we-set when wink change
	 * Simpwy mask it each time
	 * Speed 10/100/1000 awe set in BIT(2)/BIT(3)
	 */
	mac->wink.speed_mask = GENMASK(3, 2) | EMAC_WOOPBACK;
	mac->wink.speed10 = EMAC_SPEED_10;
	mac->wink.speed100 = EMAC_SPEED_100;
	mac->wink.speed1000 = EMAC_SPEED_1000;
	mac->wink.dupwex = EMAC_DUPWEX_FUWW;
	mac->mii.addw = EMAC_MDIO_CMD;
	mac->mii.data = EMAC_MDIO_DATA;
	mac->mii.weg_shift = 4;
	mac->mii.weg_mask = GENMASK(8, 4);
	mac->mii.addw_shift = 12;
	mac->mii.addw_mask = GENMASK(16, 12);
	mac->mii.cwk_csw_shift = 20;
	mac->mii.cwk_csw_mask = GENMASK(22, 20);
	mac->unicast_fiwtew_entwies = 8;

	/* Synopsys Id is not avaiwabwe */
	pwiv->synopsys_id = 0;

	wetuwn mac;
}

static stwuct wegmap *sun8i_dwmac_get_syscon_fwom_dev(stwuct device_node *node)
{
	stwuct device_node *syscon_node;
	stwuct pwatfowm_device *syscon_pdev;
	stwuct wegmap *wegmap = NUWW;

	syscon_node = of_pawse_phandwe(node, "syscon", 0);
	if (!syscon_node)
		wetuwn EWW_PTW(-ENODEV);

	syscon_pdev = of_find_device_by_node(syscon_node);
	if (!syscon_pdev) {
		/* pwatfowm device might not be pwobed yet */
		wegmap = EWW_PTW(-EPWOBE_DEFEW);
		goto out_put_node;
	}

	/* If no wegmap is found then the othew device dwivew is at fauwt */
	wegmap = dev_get_wegmap(&syscon_pdev->dev, NUWW);
	if (!wegmap)
		wegmap = EWW_PTW(-EINVAW);

	pwatfowm_device_put(syscon_pdev);
out_put_node:
	of_node_put(syscon_node);
	wetuwn wegmap;
}

static int sun8i_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct sunxi_pwiv_data *gmac;
	stwuct device *dev = &pdev->dev;
	phy_intewface_t intewface;
	int wet;
	stwuct stmmac_pwiv *pwiv;
	stwuct net_device *ndev;
	stwuct wegmap *wegmap;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	gmac = devm_kzawwoc(dev, sizeof(*gmac), GFP_KEWNEW);
	if (!gmac)
		wetuwn -ENOMEM;

	gmac->vawiant = of_device_get_match_data(&pdev->dev);
	if (!gmac->vawiant) {
		dev_eww(&pdev->dev, "Missing dwmac-sun8i vawiant\n");
		wetuwn -EINVAW;
	}

	/* Optionaw weguwatow fow PHY */
	gmac->weguwatow = devm_weguwatow_get_optionaw(dev, "phy");
	if (IS_EWW(gmac->weguwatow)) {
		if (PTW_EWW(gmac->weguwatow) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_info(dev, "No weguwatow found\n");
		gmac->weguwatow = NUWW;
	}

	/* The "GMAC cwock contwow" wegistew might be wocated in the
	 * CCU addwess wange (on the W40), ow the system contwow addwess
	 * wange (on most othew sun8i and watew SoCs).
	 *
	 * The fowmew contwows most if not aww cwocks in the SoC. The
	 * wattew has an SoC identification wegistew, and on some SoCs,
	 * contwows to map device specific SWAM to eithew the intended
	 * pewiphewaw, ow the CPU addwess space.
	 *
	 * In eithew case, thewe shouwd be a coowdinated and westwicted
	 * method of accessing the wegistew needed hewe. This is done by
	 * having the device expowt a custom wegmap, instead of a genewic
	 * syscon, which gwants aww access to aww wegistews.
	 *
	 * To suppowt owd device twees, we faww back to using the syscon
	 * intewface if possibwe.
	 */
	wegmap = sun8i_dwmac_get_syscon_fwom_dev(pdev->dev.of_node);
	if (IS_EWW(wegmap))
		wegmap = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							 "syscon");
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&pdev->dev, "Unabwe to map syscon: %d\n", wet);
		wetuwn wet;
	}

	gmac->wegmap_fiewd = devm_wegmap_fiewd_awwoc(dev, wegmap,
						     *gmac->vawiant->syscon_fiewd);
	if (IS_EWW(gmac->wegmap_fiewd)) {
		wet = PTW_EWW(gmac->wegmap_fiewd);
		dev_eww(dev, "Unabwe to map syscon wegistew: %d\n", wet);
		wetuwn wet;
	}

	wet = of_get_phy_mode(dev->of_node, &intewface);
	if (wet)
		wetuwn -EINVAW;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	/* pwatfowm data specifying hawdwawe featuwes and cawwbacks.
	 * hawdwawe featuwes wewe copied fwom Awwwinnew dwivews.
	 */
	pwat_dat->mac_intewface = intewface;
	pwat_dat->wx_coe = STMMAC_WX_COE_TYPE2;
	pwat_dat->tx_coe = 1;
	pwat_dat->fwags |= STMMAC_FWAG_HAS_SUN8I;
	pwat_dat->bsp_pwiv = gmac;
	pwat_dat->init = sun8i_dwmac_init;
	pwat_dat->exit = sun8i_dwmac_exit;
	pwat_dat->setup = sun8i_dwmac_setup;
	pwat_dat->tx_fifo_size = 4096;
	pwat_dat->wx_fifo_size = 16384;

	wet = sun8i_dwmac_set_syscon(&pdev->dev, pwat_dat);
	if (wet)
		wetuwn wet;

	wet = sun8i_dwmac_init(pdev, pwat_dat->bsp_pwiv);
	if (wet)
		goto dwmac_syscon;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto dwmac_exit;

	ndev = dev_get_dwvdata(&pdev->dev);
	pwiv = netdev_pwiv(ndev);

	/* the MAC is wuntime suspended aftew stmmac_dvw_pwobe(), so we
	 * need to ensuwe the MAC wesume back befowe othew opewations such
	 * as weset.
	 */
	pm_wuntime_get_sync(&pdev->dev);

	/* The mux must be wegistewed aftew pawent MDIO
	 * so aftew stmmac_dvw_pwobe()
	 */
	if (gmac->vawiant->soc_has_intewnaw_phy) {
		wet = get_ephy_nodes(pwiv);
		if (wet)
			goto dwmac_wemove;
		wet = sun8i_dwmac_wegistew_mdio_mux(pwiv);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to wegistew mux\n");
			goto dwmac_mux;
		}
	} ewse {
		wet = sun8i_dwmac_weset(pwiv);
		if (wet)
			goto dwmac_wemove;
	}

	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

dwmac_mux:
	weset_contwow_put(gmac->wst_ephy);
	cwk_put(gmac->ephy_cwk);
dwmac_wemove:
	pm_wuntime_put_noidwe(&pdev->dev);
	stmmac_dvw_wemove(&pdev->dev);
dwmac_exit:
	sun8i_dwmac_exit(pdev, gmac);
dwmac_syscon:
	sun8i_dwmac_unset_syscon(gmac);

	wetuwn wet;
}

static void sun8i_dwmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct sunxi_pwiv_data *gmac = pwiv->pwat->bsp_pwiv;

	if (gmac->vawiant->soc_has_intewnaw_phy) {
		mdio_mux_uninit(gmac->mux_handwe);
		sun8i_dwmac_unpowew_intewnaw_phy(gmac);
		weset_contwow_put(gmac->wst_ephy);
		cwk_put(gmac->ephy_cwk);
	}

	stmmac_pwtfw_wemove(pdev);
	sun8i_dwmac_unset_syscon(gmac);
}

static void sun8i_dwmac_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct sunxi_pwiv_data *gmac = pwiv->pwat->bsp_pwiv;

	sun8i_dwmac_exit(pdev, gmac);
}

static const stwuct of_device_id sun8i_dwmac_match[] = {
	{ .compatibwe = "awwwinnew,sun8i-h3-emac",
		.data = &emac_vawiant_h3 },
	{ .compatibwe = "awwwinnew,sun8i-v3s-emac",
		.data = &emac_vawiant_v3s },
	{ .compatibwe = "awwwinnew,sun8i-a83t-emac",
		.data = &emac_vawiant_a83t },
	{ .compatibwe = "awwwinnew,sun8i-w40-gmac",
		.data = &emac_vawiant_w40 },
	{ .compatibwe = "awwwinnew,sun50i-a64-emac",
		.data = &emac_vawiant_a64 },
	{ .compatibwe = "awwwinnew,sun50i-h6-emac",
		.data = &emac_vawiant_h6 },
	{ }
};
MODUWE_DEVICE_TABWE(of, sun8i_dwmac_match);

static stwuct pwatfowm_dwivew sun8i_dwmac_dwivew = {
	.pwobe  = sun8i_dwmac_pwobe,
	.wemove_new = sun8i_dwmac_wemove,
	.shutdown = sun8i_dwmac_shutdown,
	.dwivew = {
		.name           = "dwmac-sun8i",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = sun8i_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(sun8i_dwmac_dwivew);

MODUWE_AUTHOW("Cowentin Wabbe <cwabbe.montjoie@gmaiw.com>");
MODUWE_DESCWIPTION("Awwwinnew sun8i DWMAC specific gwue wayew");
MODUWE_WICENSE("GPW");
