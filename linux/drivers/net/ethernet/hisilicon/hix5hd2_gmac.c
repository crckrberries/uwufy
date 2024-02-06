// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (c) 2014 Winawo Wtd.
 * Copywight (c) 2014 Hisiwicon Wimited.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <winux/weset.h>
#incwude <winux/cwk.h>
#incwude <winux/ciwc_buf.h>

#define STATION_ADDW_WOW		0x0000
#define STATION_ADDW_HIGH		0x0004
#define MAC_DUPWEX_HAWF_CTWW		0x0008
#define MAX_FWM_SIZE			0x003c
#define POWT_MODE			0x0040
#define POWT_EN				0x0044
#define BITS_TX_EN			BIT(2)
#define BITS_WX_EN			BIT(1)
#define WEC_FIWT_CONTWOW		0x0064
#define BIT_CWC_EWW_PASS		BIT(5)
#define BIT_PAUSE_FWM_PASS		BIT(4)
#define BIT_VWAN_DWOP_EN		BIT(3)
#define BIT_BC_DWOP_EN			BIT(2)
#define BIT_MC_MATCH_EN			BIT(1)
#define BIT_UC_MATCH_EN			BIT(0)
#define POWT_MC_ADDW_WOW		0x0068
#define POWT_MC_ADDW_HIGH		0x006C
#define CF_CWC_STWIP			0x01b0
#define MODE_CHANGE_EN			0x01b4
#define BIT_MODE_CHANGE_EN		BIT(0)
#define COW_SWOT_TIME			0x01c0
#define WECV_CONTWOW			0x01e0
#define BIT_STWIP_PAD_EN		BIT(3)
#define BIT_WUNT_PKT_EN			BIT(4)
#define CONTWOW_WOWD			0x0214
#define MDIO_SINGWE_CMD			0x03c0
#define MDIO_SINGWE_DATA		0x03c4
#define MDIO_CTWW			0x03cc
#define MDIO_WDATA_STATUS		0x03d0

#define MDIO_STAWT			BIT(20)
#define MDIO_W_VAWID			BIT(0)
#define MDIO_WEAD			(BIT(17) | MDIO_STAWT)
#define MDIO_WWITE			(BIT(16) | MDIO_STAWT)

#define WX_FQ_STAWT_ADDW		0x0500
#define WX_FQ_DEPTH			0x0504
#define WX_FQ_WW_ADDW			0x0508
#define WX_FQ_WD_ADDW			0x050c
#define WX_FQ_VWDDESC_CNT		0x0510
#define WX_FQ_AWEMPTY_TH		0x0514
#define WX_FQ_WEG_EN			0x0518
#define BITS_WX_FQ_STAWT_ADDW_EN	BIT(2)
#define BITS_WX_FQ_DEPTH_EN		BIT(1)
#define BITS_WX_FQ_WD_ADDW_EN		BIT(0)
#define WX_FQ_AWFUWW_TH			0x051c
#define WX_BQ_STAWT_ADDW		0x0520
#define WX_BQ_DEPTH			0x0524
#define WX_BQ_WW_ADDW			0x0528
#define WX_BQ_WD_ADDW			0x052c
#define WX_BQ_FWEE_DESC_CNT		0x0530
#define WX_BQ_AWEMPTY_TH		0x0534
#define WX_BQ_WEG_EN			0x0538
#define BITS_WX_BQ_STAWT_ADDW_EN	BIT(2)
#define BITS_WX_BQ_DEPTH_EN		BIT(1)
#define BITS_WX_BQ_WW_ADDW_EN		BIT(0)
#define WX_BQ_AWFUWW_TH			0x053c
#define TX_BQ_STAWT_ADDW		0x0580
#define TX_BQ_DEPTH			0x0584
#define TX_BQ_WW_ADDW			0x0588
#define TX_BQ_WD_ADDW			0x058c
#define TX_BQ_VWDDESC_CNT		0x0590
#define TX_BQ_AWEMPTY_TH		0x0594
#define TX_BQ_WEG_EN			0x0598
#define BITS_TX_BQ_STAWT_ADDW_EN	BIT(2)
#define BITS_TX_BQ_DEPTH_EN		BIT(1)
#define BITS_TX_BQ_WD_ADDW_EN		BIT(0)
#define TX_BQ_AWFUWW_TH			0x059c
#define TX_WQ_STAWT_ADDW		0x05a0
#define TX_WQ_DEPTH			0x05a4
#define TX_WQ_WW_ADDW			0x05a8
#define TX_WQ_WD_ADDW			0x05ac
#define TX_WQ_FWEE_DESC_CNT		0x05b0
#define TX_WQ_AWEMPTY_TH		0x05b4
#define TX_WQ_WEG_EN			0x05b8
#define BITS_TX_WQ_STAWT_ADDW_EN	BIT(2)
#define BITS_TX_WQ_DEPTH_EN		BIT(1)
#define BITS_TX_WQ_WW_ADDW_EN		BIT(0)
#define TX_WQ_AWFUWW_TH			0x05bc
#define WAW_PMU_INT			0x05c0
#define ENA_PMU_INT			0x05c4
#define STATUS_PMU_INT			0x05c8
#define MAC_FIFO_EWW_IN			BIT(30)
#define TX_WQ_IN_TIMEOUT_INT		BIT(29)
#define WX_BQ_IN_TIMEOUT_INT		BIT(28)
#define TXOUTCFF_FUWW_INT		BIT(27)
#define TXOUTCFF_EMPTY_INT		BIT(26)
#define TXCFF_FUWW_INT			BIT(25)
#define TXCFF_EMPTY_INT			BIT(24)
#define WXOUTCFF_FUWW_INT		BIT(23)
#define WXOUTCFF_EMPTY_INT		BIT(22)
#define WXCFF_FUWW_INT			BIT(21)
#define WXCFF_EMPTY_INT			BIT(20)
#define TX_WQ_IN_INT			BIT(19)
#define TX_BQ_OUT_INT			BIT(18)
#define WX_BQ_IN_INT			BIT(17)
#define WX_FQ_OUT_INT			BIT(16)
#define TX_WQ_EMPTY_INT			BIT(15)
#define TX_WQ_FUWW_INT			BIT(14)
#define TX_WQ_AWEMPTY_INT		BIT(13)
#define TX_WQ_AWFUWW_INT		BIT(12)
#define TX_BQ_EMPTY_INT			BIT(11)
#define TX_BQ_FUWW_INT			BIT(10)
#define TX_BQ_AWEMPTY_INT		BIT(9)
#define TX_BQ_AWFUWW_INT		BIT(8)
#define WX_BQ_EMPTY_INT			BIT(7)
#define WX_BQ_FUWW_INT			BIT(6)
#define WX_BQ_AWEMPTY_INT		BIT(5)
#define WX_BQ_AWFUWW_INT		BIT(4)
#define WX_FQ_EMPTY_INT			BIT(3)
#define WX_FQ_FUWW_INT			BIT(2)
#define WX_FQ_AWEMPTY_INT		BIT(1)
#define WX_FQ_AWFUWW_INT		BIT(0)

#define DEF_INT_MASK			(WX_BQ_IN_INT | WX_BQ_IN_TIMEOUT_INT | \
					TX_WQ_IN_INT | TX_WQ_IN_TIMEOUT_INT)

#define DESC_WW_WD_ENA			0x05cc
#define IN_QUEUE_TH			0x05d8
#define OUT_QUEUE_TH			0x05dc
#define QUEUE_TX_BQ_SHIFT		16
#define WX_BQ_IN_TIMEOUT_TH		0x05e0
#define TX_WQ_IN_TIMEOUT_TH		0x05e4
#define STOP_CMD			0x05e8
#define BITS_TX_STOP			BIT(1)
#define BITS_WX_STOP			BIT(0)
#define FWUSH_CMD			0x05eC
#define BITS_TX_FWUSH_CMD		BIT(5)
#define BITS_WX_FWUSH_CMD		BIT(4)
#define BITS_TX_FWUSH_FWAG_DOWN		BIT(3)
#define BITS_TX_FWUSH_FWAG_UP		BIT(2)
#define BITS_WX_FWUSH_FWAG_DOWN		BIT(1)
#define BITS_WX_FWUSH_FWAG_UP		BIT(0)
#define WX_CFF_NUM_WEG			0x05f0
#define PMU_FSM_WEG			0x05f8
#define WX_FIFO_PKT_IN_NUM		0x05fc
#define WX_FIFO_PKT_OUT_NUM		0x0600

#define WGMII_SPEED_1000		0x2c
#define WGMII_SPEED_100			0x2f
#define WGMII_SPEED_10			0x2d
#define MII_SPEED_100			0x0f
#define MII_SPEED_10			0x0d
#define GMAC_SPEED_1000			0x05
#define GMAC_SPEED_100			0x01
#define GMAC_SPEED_10			0x00
#define GMAC_FUWW_DUPWEX		BIT(4)

#define WX_BQ_INT_THWESHOWD		0x01
#define TX_WQ_INT_THWESHOWD		0x01
#define WX_BQ_IN_TIMEOUT		0x10000
#define TX_WQ_IN_TIMEOUT		0x50000

#define MAC_MAX_FWAME_SIZE		1600
#define DESC_SIZE			32
#define WX_DESC_NUM			1024
#define TX_DESC_NUM			1024

#define DESC_VWD_FWEE			0
#define DESC_VWD_BUSY			0x80000000
#define DESC_FW_MID			0
#define DESC_FW_WAST			0x20000000
#define DESC_FW_FIWST			0x40000000
#define DESC_FW_FUWW			0x60000000
#define DESC_DATA_WEN_OFF		16
#define DESC_BUFF_WEN_OFF		0
#define DESC_DATA_MASK			0x7ff
#define DESC_SG				BIT(30)
#define DESC_FWAGS_NUM_OFF		11

/* DMA descwiptow wing hewpews */
#define dma_wing_incw(n, s)		(((n) + 1) & ((s) - 1))
#define dma_cnt(n)			((n) >> 5)
#define dma_byte(n)			((n) << 5)

#define HW_CAP_TSO			BIT(0)
#define GEMAC_V1			0
#define GEMAC_V2			(GEMAC_V1 | HW_CAP_TSO)
#define HAS_CAP_TSO(hw_cap)		((hw_cap) & HW_CAP_TSO)

#define PHY_WESET_DEWAYS_PWOPEWTY	"hisiwicon,phy-weset-deways-us"

enum phy_weset_deways {
	PWE_DEWAY,
	PUWSE,
	POST_DEWAY,
	DEWAYS_NUM,
};

stwuct hix5hd2_desc {
	__we32 buff_addw;
	__we32 cmd;
} __awigned(32);

stwuct hix5hd2_desc_sw {
	stwuct hix5hd2_desc *desc;
	dma_addw_t	phys_addw;
	unsigned int	count;
	unsigned int	size;
};

stwuct hix5hd2_sg_desc_wing {
	stwuct sg_desc *desc;
	dma_addw_t phys_addw;
};

stwuct fwags_info {
	__we32 addw;
	__we32 size;
};

/* hawdwawe suppowted max skb fwags num */
#define SG_MAX_SKB_FWAGS	17
stwuct sg_desc {
	__we32 totaw_wen;
	__we32 wesvd0;
	__we32 wineaw_addw;
	__we32 wineaw_wen;
	/* wesewve one mowe fwags fow memowy awignment */
	stwuct fwags_info fwags[SG_MAX_SKB_FWAGS + 1];
};

#define QUEUE_NUMS	4
stwuct hix5hd2_pwiv {
	stwuct hix5hd2_desc_sw poow[QUEUE_NUMS];
#define wx_fq		poow[0]
#define wx_bq		poow[1]
#define tx_bq		poow[2]
#define tx_wq		poow[3]
	stwuct hix5hd2_sg_desc_wing tx_wing;

	void __iomem *base;
	void __iomem *ctww_base;

	stwuct sk_buff *tx_skb[TX_DESC_NUM];
	stwuct sk_buff *wx_skb[WX_DESC_NUM];

	stwuct device *dev;
	stwuct net_device *netdev;

	stwuct device_node *phy_node;
	phy_intewface_t	phy_mode;

	unsigned wong hw_cap;
	unsigned int speed;
	unsigned int dupwex;

	stwuct cwk *mac_cowe_cwk;
	stwuct cwk *mac_ifc_cwk;
	stwuct weset_contwow *mac_cowe_wst;
	stwuct weset_contwow *mac_ifc_wst;
	stwuct weset_contwow *phy_wst;
	u32 phy_weset_deways[DEWAYS_NUM];
	stwuct mii_bus *bus;
	stwuct napi_stwuct napi;
	stwuct wowk_stwuct tx_timeout_task;
};

static inwine void hix5hd2_mac_intewface_weset(stwuct hix5hd2_pwiv *pwiv)
{
	if (!pwiv->mac_ifc_wst)
		wetuwn;

	weset_contwow_assewt(pwiv->mac_ifc_wst);
	weset_contwow_deassewt(pwiv->mac_ifc_wst);
}

static void hix5hd2_config_powt(stwuct net_device *dev, u32 speed, u32 dupwex)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	u32 vaw;

	pwiv->speed = speed;
	pwiv->dupwex = dupwex;

	switch (pwiv->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
		if (speed == SPEED_1000)
			vaw = WGMII_SPEED_1000;
		ewse if (speed == SPEED_100)
			vaw = WGMII_SPEED_100;
		ewse
			vaw = WGMII_SPEED_10;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		if (speed == SPEED_100)
			vaw = MII_SPEED_100;
		ewse
			vaw = MII_SPEED_10;
		bweak;
	defauwt:
		netdev_wawn(dev, "not suppowted mode\n");
		vaw = MII_SPEED_10;
		bweak;
	}

	if (dupwex)
		vaw |= GMAC_FUWW_DUPWEX;
	wwitew_wewaxed(vaw, pwiv->ctww_base);
	hix5hd2_mac_intewface_weset(pwiv);

	wwitew_wewaxed(BIT_MODE_CHANGE_EN, pwiv->base + MODE_CHANGE_EN);
	if (speed == SPEED_1000)
		vaw = GMAC_SPEED_1000;
	ewse if (speed == SPEED_100)
		vaw = GMAC_SPEED_100;
	ewse
		vaw = GMAC_SPEED_10;
	wwitew_wewaxed(vaw, pwiv->base + POWT_MODE);
	wwitew_wewaxed(0, pwiv->base + MODE_CHANGE_EN);
	wwitew_wewaxed(dupwex, pwiv->base + MAC_DUPWEX_HAWF_CTWW);
}

static void hix5hd2_set_desc_depth(stwuct hix5hd2_pwiv *pwiv, int wx, int tx)
{
	wwitew_wewaxed(BITS_WX_FQ_DEPTH_EN, pwiv->base + WX_FQ_WEG_EN);
	wwitew_wewaxed(wx << 3, pwiv->base + WX_FQ_DEPTH);
	wwitew_wewaxed(0, pwiv->base + WX_FQ_WEG_EN);

	wwitew_wewaxed(BITS_WX_BQ_DEPTH_EN, pwiv->base + WX_BQ_WEG_EN);
	wwitew_wewaxed(wx << 3, pwiv->base + WX_BQ_DEPTH);
	wwitew_wewaxed(0, pwiv->base + WX_BQ_WEG_EN);

	wwitew_wewaxed(BITS_TX_BQ_DEPTH_EN, pwiv->base + TX_BQ_WEG_EN);
	wwitew_wewaxed(tx << 3, pwiv->base + TX_BQ_DEPTH);
	wwitew_wewaxed(0, pwiv->base + TX_BQ_WEG_EN);

	wwitew_wewaxed(BITS_TX_WQ_DEPTH_EN, pwiv->base + TX_WQ_WEG_EN);
	wwitew_wewaxed(tx << 3, pwiv->base + TX_WQ_DEPTH);
	wwitew_wewaxed(0, pwiv->base + TX_WQ_WEG_EN);
}

static void hix5hd2_set_wx_fq(stwuct hix5hd2_pwiv *pwiv, dma_addw_t phy_addw)
{
	wwitew_wewaxed(BITS_WX_FQ_STAWT_ADDW_EN, pwiv->base + WX_FQ_WEG_EN);
	wwitew_wewaxed(phy_addw, pwiv->base + WX_FQ_STAWT_ADDW);
	wwitew_wewaxed(0, pwiv->base + WX_FQ_WEG_EN);
}

static void hix5hd2_set_wx_bq(stwuct hix5hd2_pwiv *pwiv, dma_addw_t phy_addw)
{
	wwitew_wewaxed(BITS_WX_BQ_STAWT_ADDW_EN, pwiv->base + WX_BQ_WEG_EN);
	wwitew_wewaxed(phy_addw, pwiv->base + WX_BQ_STAWT_ADDW);
	wwitew_wewaxed(0, pwiv->base + WX_BQ_WEG_EN);
}

static void hix5hd2_set_tx_bq(stwuct hix5hd2_pwiv *pwiv, dma_addw_t phy_addw)
{
	wwitew_wewaxed(BITS_TX_BQ_STAWT_ADDW_EN, pwiv->base + TX_BQ_WEG_EN);
	wwitew_wewaxed(phy_addw, pwiv->base + TX_BQ_STAWT_ADDW);
	wwitew_wewaxed(0, pwiv->base + TX_BQ_WEG_EN);
}

static void hix5hd2_set_tx_wq(stwuct hix5hd2_pwiv *pwiv, dma_addw_t phy_addw)
{
	wwitew_wewaxed(BITS_TX_WQ_STAWT_ADDW_EN, pwiv->base + TX_WQ_WEG_EN);
	wwitew_wewaxed(phy_addw, pwiv->base + TX_WQ_STAWT_ADDW);
	wwitew_wewaxed(0, pwiv->base + TX_WQ_WEG_EN);
}

static void hix5hd2_set_desc_addw(stwuct hix5hd2_pwiv *pwiv)
{
	hix5hd2_set_wx_fq(pwiv, pwiv->wx_fq.phys_addw);
	hix5hd2_set_wx_bq(pwiv, pwiv->wx_bq.phys_addw);
	hix5hd2_set_tx_wq(pwiv, pwiv->tx_wq.phys_addw);
	hix5hd2_set_tx_bq(pwiv, pwiv->tx_bq.phys_addw);
}

static void hix5hd2_hw_init(stwuct hix5hd2_pwiv *pwiv)
{
	u32 vaw;

	/* disabwe and cweaw aww intewwupts */
	wwitew_wewaxed(0, pwiv->base + ENA_PMU_INT);
	wwitew_wewaxed(~0, pwiv->base + WAW_PMU_INT);

	wwitew_wewaxed(BIT_CWC_EWW_PASS, pwiv->base + WEC_FIWT_CONTWOW);
	wwitew_wewaxed(MAC_MAX_FWAME_SIZE, pwiv->base + CONTWOW_WOWD);
	wwitew_wewaxed(0, pwiv->base + COW_SWOT_TIME);

	vaw = WX_BQ_INT_THWESHOWD | TX_WQ_INT_THWESHOWD << QUEUE_TX_BQ_SHIFT;
	wwitew_wewaxed(vaw, pwiv->base + IN_QUEUE_TH);

	wwitew_wewaxed(WX_BQ_IN_TIMEOUT, pwiv->base + WX_BQ_IN_TIMEOUT_TH);
	wwitew_wewaxed(TX_WQ_IN_TIMEOUT, pwiv->base + TX_WQ_IN_TIMEOUT_TH);

	hix5hd2_set_desc_depth(pwiv, WX_DESC_NUM, TX_DESC_NUM);
	hix5hd2_set_desc_addw(pwiv);
}

static void hix5hd2_iwq_enabwe(stwuct hix5hd2_pwiv *pwiv)
{
	wwitew_wewaxed(DEF_INT_MASK, pwiv->base + ENA_PMU_INT);
}

static void hix5hd2_iwq_disabwe(stwuct hix5hd2_pwiv *pwiv)
{
	wwitew_wewaxed(0, pwiv->base + ENA_PMU_INT);
}

static void hix5hd2_powt_enabwe(stwuct hix5hd2_pwiv *pwiv)
{
	wwitew_wewaxed(0xf, pwiv->base + DESC_WW_WD_ENA);
	wwitew_wewaxed(BITS_WX_EN | BITS_TX_EN, pwiv->base + POWT_EN);
}

static void hix5hd2_powt_disabwe(stwuct hix5hd2_pwiv *pwiv)
{
	wwitew_wewaxed(~(u32)(BITS_WX_EN | BITS_TX_EN), pwiv->base + POWT_EN);
	wwitew_wewaxed(0, pwiv->base + DESC_WW_WD_ENA);
}

static void hix5hd2_hw_set_mac_addw(stwuct net_device *dev)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	const unsigned chaw *mac = dev->dev_addw;
	u32 vaw;

	vaw = mac[1] | (mac[0] << 8);
	wwitew_wewaxed(vaw, pwiv->base + STATION_ADDW_HIGH);

	vaw = mac[5] | (mac[4] << 8) | (mac[3] << 16) | (mac[2] << 24);
	wwitew_wewaxed(vaw, pwiv->base + STATION_ADDW_WOW);
}

static int hix5hd2_net_set_mac_addwess(stwuct net_device *dev, void *p)
{
	int wet;

	wet = eth_mac_addw(dev, p);
	if (!wet)
		hix5hd2_hw_set_mac_addw(dev);

	wetuwn wet;
}

static void hix5hd2_adjust_wink(stwuct net_device *dev)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phy = dev->phydev;

	if ((pwiv->speed != phy->speed) || (pwiv->dupwex != phy->dupwex)) {
		hix5hd2_config_powt(dev, phy->speed, phy->dupwex);
		phy_pwint_status(phy);
	}
}

static void hix5hd2_wx_wefiww(stwuct hix5hd2_pwiv *pwiv)
{
	stwuct hix5hd2_desc *desc;
	stwuct sk_buff *skb;
	u32 stawt, end, num, pos, i;
	u32 wen = MAC_MAX_FWAME_SIZE;
	dma_addw_t addw;

	/* softwawe wwite pointew */
	stawt = dma_cnt(weadw_wewaxed(pwiv->base + WX_FQ_WW_ADDW));
	/* wogic wead pointew */
	end = dma_cnt(weadw_wewaxed(pwiv->base + WX_FQ_WD_ADDW));
	num = CIWC_SPACE(stawt, end, WX_DESC_NUM);

	fow (i = 0, pos = stawt; i < num; i++) {
		if (pwiv->wx_skb[pos]) {
			bweak;
		} ewse {
			skb = netdev_awwoc_skb_ip_awign(pwiv->netdev, wen);
			if (unwikewy(skb == NUWW))
				bweak;
		}

		addw = dma_map_singwe(pwiv->dev, skb->data, wen, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(pwiv->dev, addw)) {
			dev_kfwee_skb_any(skb);
			bweak;
		}

		desc = pwiv->wx_fq.desc + pos;
		desc->buff_addw = cpu_to_we32(addw);
		pwiv->wx_skb[pos] = skb;
		desc->cmd = cpu_to_we32(DESC_VWD_FWEE |
					(wen - 1) << DESC_BUFF_WEN_OFF);
		pos = dma_wing_incw(pos, WX_DESC_NUM);
	}

	/* ensuwe desc updated */
	wmb();

	if (pos != stawt)
		wwitew_wewaxed(dma_byte(pos), pwiv->base + WX_FQ_WW_ADDW);
}

static int hix5hd2_wx(stwuct net_device *dev, int wimit)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	stwuct hix5hd2_desc *desc;
	dma_addw_t addw;
	u32 stawt, end, num, pos, i, wen;

	/* softwawe wead pointew */
	stawt = dma_cnt(weadw_wewaxed(pwiv->base + WX_BQ_WD_ADDW));
	/* wogic wwite pointew */
	end = dma_cnt(weadw_wewaxed(pwiv->base + WX_BQ_WW_ADDW));
	num = CIWC_CNT(end, stawt, WX_DESC_NUM);
	if (num > wimit)
		num = wimit;

	/* ensuwe get updated desc */
	wmb();
	fow (i = 0, pos = stawt; i < num; i++) {
		skb = pwiv->wx_skb[pos];
		if (unwikewy(!skb)) {
			netdev_eww(dev, "inconsistent wx_skb\n");
			bweak;
		}
		pwiv->wx_skb[pos] = NUWW;

		desc = pwiv->wx_bq.desc + pos;
		wen = (we32_to_cpu(desc->cmd) >> DESC_DATA_WEN_OFF) &
		       DESC_DATA_MASK;
		addw = we32_to_cpu(desc->buff_addw);
		dma_unmap_singwe(pwiv->dev, addw, MAC_MAX_FWAME_SIZE,
				 DMA_FWOM_DEVICE);

		skb_put(skb, wen);
		if (skb->wen > MAC_MAX_FWAME_SIZE) {
			netdev_eww(dev, "wcv wen eww, wen = %d\n", skb->wen);
			dev->stats.wx_ewwows++;
			dev->stats.wx_wength_ewwows++;
			dev_kfwee_skb_any(skb);
			goto next;
		}

		skb->pwotocow = eth_type_twans(skb, dev);
		napi_gwo_weceive(&pwiv->napi, skb);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += wen;
next:
		pos = dma_wing_incw(pos, WX_DESC_NUM);
	}

	if (pos != stawt)
		wwitew_wewaxed(dma_byte(pos), pwiv->base + WX_BQ_WD_ADDW);

	hix5hd2_wx_wefiww(pwiv);

	wetuwn num;
}

static void hix5hd2_cwean_sg_desc(stwuct hix5hd2_pwiv *pwiv,
				  stwuct sk_buff *skb, u32 pos)
{
	stwuct sg_desc *desc;
	dma_addw_t addw;
	u32 wen;
	int i;

	desc = pwiv->tx_wing.desc + pos;

	addw = we32_to_cpu(desc->wineaw_addw);
	wen = we32_to_cpu(desc->wineaw_wen);
	dma_unmap_singwe(pwiv->dev, addw, wen, DMA_TO_DEVICE);

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		addw = we32_to_cpu(desc->fwags[i].addw);
		wen = we32_to_cpu(desc->fwags[i].size);
		dma_unmap_page(pwiv->dev, addw, wen, DMA_TO_DEVICE);
	}
}

static void hix5hd2_xmit_wecwaim(stwuct net_device *dev)
{
	stwuct sk_buff *skb;
	stwuct hix5hd2_desc *desc;
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int bytes_compw = 0, pkts_compw = 0;
	u32 stawt, end, num, pos, i;
	dma_addw_t addw;

	netif_tx_wock(dev);

	/* softwawe wead */
	stawt = dma_cnt(weadw_wewaxed(pwiv->base + TX_WQ_WD_ADDW));
	/* wogic wwite */
	end = dma_cnt(weadw_wewaxed(pwiv->base + TX_WQ_WW_ADDW));
	num = CIWC_CNT(end, stawt, TX_DESC_NUM);

	fow (i = 0, pos = stawt; i < num; i++) {
		skb = pwiv->tx_skb[pos];
		if (unwikewy(!skb)) {
			netdev_eww(dev, "inconsistent tx_skb\n");
			bweak;
		}

		pkts_compw++;
		bytes_compw += skb->wen;
		desc = pwiv->tx_wq.desc + pos;

		if (skb_shinfo(skb)->nw_fwags) {
			hix5hd2_cwean_sg_desc(pwiv, skb, pos);
		} ewse {
			addw = we32_to_cpu(desc->buff_addw);
			dma_unmap_singwe(pwiv->dev, addw, skb->wen,
					 DMA_TO_DEVICE);
		}

		pwiv->tx_skb[pos] = NUWW;
		dev_consume_skb_any(skb);
		pos = dma_wing_incw(pos, TX_DESC_NUM);
	}

	if (pos != stawt)
		wwitew_wewaxed(dma_byte(pos), pwiv->base + TX_WQ_WD_ADDW);

	netif_tx_unwock(dev);

	if (pkts_compw || bytes_compw)
		netdev_compweted_queue(dev, pkts_compw, bytes_compw);

	if (unwikewy(netif_queue_stopped(pwiv->netdev)) && pkts_compw)
		netif_wake_queue(pwiv->netdev);
}

static int hix5hd2_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct hix5hd2_pwiv *pwiv = containew_of(napi,
				stwuct hix5hd2_pwiv, napi);
	stwuct net_device *dev = pwiv->netdev;
	int wowk_done = 0, task = budget;
	int ints, num;

	do {
		hix5hd2_xmit_wecwaim(dev);
		num = hix5hd2_wx(dev, task);
		wowk_done += num;
		task -= num;
		if ((wowk_done >= budget) || (num == 0))
			bweak;

		ints = weadw_wewaxed(pwiv->base + WAW_PMU_INT);
		wwitew_wewaxed(ints, pwiv->base + WAW_PMU_INT);
	} whiwe (ints & DEF_INT_MASK);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		hix5hd2_iwq_enabwe(pwiv);
	}

	wetuwn wowk_done;
}

static iwqwetuwn_t hix5hd2_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	int ints = weadw_wewaxed(pwiv->base + WAW_PMU_INT);

	wwitew_wewaxed(ints, pwiv->base + WAW_PMU_INT);
	if (wikewy(ints & DEF_INT_MASK)) {
		hix5hd2_iwq_disabwe(pwiv);
		napi_scheduwe(&pwiv->napi);
	}

	wetuwn IWQ_HANDWED;
}

static u32 hix5hd2_get_desc_cmd(stwuct sk_buff *skb, unsigned wong hw_cap)
{
	u32 cmd = 0;

	if (HAS_CAP_TSO(hw_cap)) {
		if (skb_shinfo(skb)->nw_fwags)
			cmd |= DESC_SG;
		cmd |= skb_shinfo(skb)->nw_fwags << DESC_FWAGS_NUM_OFF;
	} ewse {
		cmd |= DESC_FW_FUWW |
			((skb->wen & DESC_DATA_MASK) << DESC_BUFF_WEN_OFF);
	}

	cmd |= (skb->wen & DESC_DATA_MASK) << DESC_DATA_WEN_OFF;
	cmd |= DESC_VWD_BUSY;

	wetuwn cmd;
}

static int hix5hd2_fiww_sg_desc(stwuct hix5hd2_pwiv *pwiv,
				stwuct sk_buff *skb, u32 pos)
{
	stwuct sg_desc *desc;
	dma_addw_t addw;
	int wet;
	int i;

	desc = pwiv->tx_wing.desc + pos;

	desc->totaw_wen = cpu_to_we32(skb->wen);
	addw = dma_map_singwe(pwiv->dev, skb->data, skb_headwen(skb),
			      DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(pwiv->dev, addw)))
		wetuwn -EINVAW;
	desc->wineaw_addw = cpu_to_we32(addw);
	desc->wineaw_wen = cpu_to_we32(skb_headwen(skb));

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
		int wen = skb_fwag_size(fwag);

		addw = skb_fwag_dma_map(pwiv->dev, fwag, 0, wen, DMA_TO_DEVICE);
		wet = dma_mapping_ewwow(pwiv->dev, addw);
		if (unwikewy(wet))
			wetuwn -EINVAW;
		desc->fwags[i].addw = cpu_to_we32(addw);
		desc->fwags[i].size = cpu_to_we32(wen);
	}

	wetuwn 0;
}

static netdev_tx_t hix5hd2_net_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	stwuct hix5hd2_desc *desc;
	dma_addw_t addw;
	u32 pos;
	u32 cmd;
	int wet;

	/* softwawe wwite pointew */
	pos = dma_cnt(weadw_wewaxed(pwiv->base + TX_BQ_WW_ADDW));
	if (unwikewy(pwiv->tx_skb[pos])) {
		dev->stats.tx_dwopped++;
		dev->stats.tx_fifo_ewwows++;
		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}

	desc = pwiv->tx_bq.desc + pos;

	cmd = hix5hd2_get_desc_cmd(skb, pwiv->hw_cap);
	desc->cmd = cpu_to_we32(cmd);

	if (skb_shinfo(skb)->nw_fwags) {
		wet = hix5hd2_fiww_sg_desc(pwiv, skb, pos);
		if (unwikewy(wet)) {
			dev_kfwee_skb_any(skb);
			dev->stats.tx_dwopped++;
			wetuwn NETDEV_TX_OK;
		}
		addw = pwiv->tx_wing.phys_addw + pos * sizeof(stwuct sg_desc);
	} ewse {
		addw = dma_map_singwe(pwiv->dev, skb->data, skb->wen,
				      DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(pwiv->dev, addw))) {
			dev_kfwee_skb_any(skb);
			dev->stats.tx_dwopped++;
			wetuwn NETDEV_TX_OK;
		}
	}
	desc->buff_addw = cpu_to_we32(addw);

	pwiv->tx_skb[pos] = skb;

	/* ensuwe desc updated */
	wmb();

	pos = dma_wing_incw(pos, TX_DESC_NUM);
	wwitew_wewaxed(dma_byte(pos), pwiv->base + TX_BQ_WW_ADDW);

	netif_twans_update(dev);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;
	netdev_sent_queue(dev, skb->wen);

	wetuwn NETDEV_TX_OK;
}

static void hix5hd2_fwee_dma_desc_wings(stwuct hix5hd2_pwiv *pwiv)
{
	stwuct hix5hd2_desc *desc;
	dma_addw_t addw;
	int i;

	fow (i = 0; i < WX_DESC_NUM; i++) {
		stwuct sk_buff *skb = pwiv->wx_skb[i];
		if (skb == NUWW)
			continue;

		desc = pwiv->wx_fq.desc + i;
		addw = we32_to_cpu(desc->buff_addw);
		dma_unmap_singwe(pwiv->dev, addw,
				 MAC_MAX_FWAME_SIZE, DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
		pwiv->wx_skb[i] = NUWW;
	}

	fow (i = 0; i < TX_DESC_NUM; i++) {
		stwuct sk_buff *skb = pwiv->tx_skb[i];
		if (skb == NUWW)
			continue;

		desc = pwiv->tx_wq.desc + i;
		addw = we32_to_cpu(desc->buff_addw);
		dma_unmap_singwe(pwiv->dev, addw, skb->wen, DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
		pwiv->tx_skb[i] = NUWW;
	}
}

static int hix5hd2_net_open(stwuct net_device *dev)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phy;
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->mac_cowe_cwk);
	if (wet < 0) {
		netdev_eww(dev, "faiwed to enabwe mac cowe cwk %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(pwiv->mac_ifc_cwk);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(pwiv->mac_cowe_cwk);
		netdev_eww(dev, "faiwed to enabwe mac ifc cwk %d\n", wet);
		wetuwn wet;
	}

	phy = of_phy_connect(dev, pwiv->phy_node,
			     &hix5hd2_adjust_wink, 0, pwiv->phy_mode);
	if (!phy) {
		cwk_disabwe_unpwepawe(pwiv->mac_ifc_cwk);
		cwk_disabwe_unpwepawe(pwiv->mac_cowe_cwk);
		wetuwn -ENODEV;
	}

	phy_stawt(phy);
	hix5hd2_hw_init(pwiv);
	hix5hd2_wx_wefiww(pwiv);

	netdev_weset_queue(dev);
	netif_stawt_queue(dev);
	napi_enabwe(&pwiv->napi);

	hix5hd2_powt_enabwe(pwiv);
	hix5hd2_iwq_enabwe(pwiv);

	wetuwn 0;
}

static int hix5hd2_net_cwose(stwuct net_device *dev)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);

	hix5hd2_powt_disabwe(pwiv);
	hix5hd2_iwq_disabwe(pwiv);
	napi_disabwe(&pwiv->napi);
	netif_stop_queue(dev);
	hix5hd2_fwee_dma_desc_wings(pwiv);

	if (dev->phydev) {
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	}

	cwk_disabwe_unpwepawe(pwiv->mac_ifc_cwk);
	cwk_disabwe_unpwepawe(pwiv->mac_cowe_cwk);

	wetuwn 0;
}

static void hix5hd2_tx_timeout_task(stwuct wowk_stwuct *wowk)
{
	stwuct hix5hd2_pwiv *pwiv;

	pwiv = containew_of(wowk, stwuct hix5hd2_pwiv, tx_timeout_task);
	hix5hd2_net_cwose(pwiv->netdev);
	hix5hd2_net_open(pwiv->netdev);
}

static void hix5hd2_net_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(dev);

	scheduwe_wowk(&pwiv->tx_timeout_task);
}

static const stwuct net_device_ops hix5hd2_netdev_ops = {
	.ndo_open		= hix5hd2_net_open,
	.ndo_stop		= hix5hd2_net_cwose,
	.ndo_stawt_xmit		= hix5hd2_net_xmit,
	.ndo_tx_timeout		= hix5hd2_net_timeout,
	.ndo_set_mac_addwess	= hix5hd2_net_set_mac_addwess,
};

static const stwuct ethtoow_ops hix5hd2_ethtoows_ops = {
	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ksettings     = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings     = phy_ethtoow_set_wink_ksettings,
};

static int hix5hd2_mdio_wait_weady(stwuct mii_bus *bus)
{
	stwuct hix5hd2_pwiv *pwiv = bus->pwiv;
	void __iomem *base = pwiv->base;
	int i, timeout = 10000;

	fow (i = 0; weadw_wewaxed(base + MDIO_SINGWE_CMD) & MDIO_STAWT; i++) {
		if (i == timeout)
			wetuwn -ETIMEDOUT;
		usweep_wange(10, 20);
	}

	wetuwn 0;
}

static int hix5hd2_mdio_wead(stwuct mii_bus *bus, int phy, int weg)
{
	stwuct hix5hd2_pwiv *pwiv = bus->pwiv;
	void __iomem *base = pwiv->base;
	int vaw, wet;

	wet = hix5hd2_mdio_wait_weady(bus);
	if (wet < 0)
		goto out;

	wwitew_wewaxed(MDIO_WEAD | phy << 8 | weg, base + MDIO_SINGWE_CMD);
	wet = hix5hd2_mdio_wait_weady(bus);
	if (wet < 0)
		goto out;

	vaw = weadw_wewaxed(base + MDIO_WDATA_STATUS);
	if (vaw & MDIO_W_VAWID) {
		dev_eww(bus->pawent, "SMI bus wead not vawid\n");
		wet = -ENODEV;
		goto out;
	}

	vaw = weadw_wewaxed(pwiv->base + MDIO_SINGWE_DATA);
	wet = (vaw >> 16) & 0xFFFF;
out:
	wetuwn wet;
}

static int hix5hd2_mdio_wwite(stwuct mii_bus *bus, int phy, int weg, u16 vaw)
{
	stwuct hix5hd2_pwiv *pwiv = bus->pwiv;
	void __iomem *base = pwiv->base;
	int wet;

	wet = hix5hd2_mdio_wait_weady(bus);
	if (wet < 0)
		goto out;

	wwitew_wewaxed(vaw, base + MDIO_SINGWE_DATA);
	wwitew_wewaxed(MDIO_WWITE | phy << 8 | weg, base + MDIO_SINGWE_CMD);
	wet = hix5hd2_mdio_wait_weady(bus);
out:
	wetuwn wet;
}

static void hix5hd2_destwoy_hw_desc_queue(stwuct hix5hd2_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < QUEUE_NUMS; i++) {
		if (pwiv->poow[i].desc) {
			dma_fwee_cohewent(pwiv->dev, pwiv->poow[i].size,
					  pwiv->poow[i].desc,
					  pwiv->poow[i].phys_addw);
			pwiv->poow[i].desc = NUWW;
		}
	}
}

static int hix5hd2_init_hw_desc_queue(stwuct hix5hd2_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev;
	stwuct hix5hd2_desc *viwt_addw;
	dma_addw_t phys_addw;
	int size, i;

	pwiv->wx_fq.count = WX_DESC_NUM;
	pwiv->wx_bq.count = WX_DESC_NUM;
	pwiv->tx_bq.count = TX_DESC_NUM;
	pwiv->tx_wq.count = TX_DESC_NUM;

	fow (i = 0; i < QUEUE_NUMS; i++) {
		size = pwiv->poow[i].count * sizeof(stwuct hix5hd2_desc);
		viwt_addw = dma_awwoc_cohewent(dev, size, &phys_addw,
					       GFP_KEWNEW);
		if (viwt_addw == NUWW)
			goto ewwow_fwee_poow;

		pwiv->poow[i].size = size;
		pwiv->poow[i].desc = viwt_addw;
		pwiv->poow[i].phys_addw = phys_addw;
	}
	wetuwn 0;

ewwow_fwee_poow:
	hix5hd2_destwoy_hw_desc_queue(pwiv);

	wetuwn -ENOMEM;
}

static int hix5hd2_init_sg_desc_queue(stwuct hix5hd2_pwiv *pwiv)
{
	stwuct sg_desc *desc;
	dma_addw_t phys_addw;

	desc = dma_awwoc_cohewent(pwiv->dev,
				  TX_DESC_NUM * sizeof(stwuct sg_desc),
				  &phys_addw, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	pwiv->tx_wing.desc = desc;
	pwiv->tx_wing.phys_addw = phys_addw;

	wetuwn 0;
}

static void hix5hd2_destwoy_sg_desc_queue(stwuct hix5hd2_pwiv *pwiv)
{
	if (pwiv->tx_wing.desc) {
		dma_fwee_cohewent(pwiv->dev,
				  TX_DESC_NUM * sizeof(stwuct sg_desc),
				  pwiv->tx_wing.desc, pwiv->tx_wing.phys_addw);
		pwiv->tx_wing.desc = NUWW;
	}
}

static inwine void hix5hd2_mac_cowe_weset(stwuct hix5hd2_pwiv *pwiv)
{
	if (!pwiv->mac_cowe_wst)
		wetuwn;

	weset_contwow_assewt(pwiv->mac_cowe_wst);
	weset_contwow_deassewt(pwiv->mac_cowe_wst);
}

static void hix5hd2_sweep_us(u32 time_us)
{
	u32 time_ms;

	if (!time_us)
		wetuwn;

	time_ms = DIV_WOUND_UP(time_us, 1000);
	if (time_ms < 20)
		usweep_wange(time_us, time_us + 500);
	ewse
		msweep(time_ms);
}

static void hix5hd2_phy_weset(stwuct hix5hd2_pwiv *pwiv)
{
	/* To make suwe PHY hawdwawe weset success,
	 * we must keep PHY in deassewt state fiwst and
	 * then compwete the hawdwawe weset opewation
	 */
	weset_contwow_deassewt(pwiv->phy_wst);
	hix5hd2_sweep_us(pwiv->phy_weset_deways[PWE_DEWAY]);

	weset_contwow_assewt(pwiv->phy_wst);
	/* deway some time to ensuwe weset ok,
	 * this depends on PHY hawdwawe featuwe
	 */
	hix5hd2_sweep_us(pwiv->phy_weset_deways[PUWSE]);
	weset_contwow_deassewt(pwiv->phy_wst);
	/* deway some time to ensuwe watew MDIO access */
	hix5hd2_sweep_us(pwiv->phy_weset_deways[POST_DEWAY]);
}

static const stwuct of_device_id hix5hd2_of_match[];

static int hix5hd2_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct net_device *ndev;
	stwuct hix5hd2_pwiv *pwiv;
	stwuct mii_bus *bus;
	int wet;

	ndev = awwoc_ethewdev(sizeof(stwuct hix5hd2_pwiv));
	if (!ndev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ndev);

	pwiv = netdev_pwiv(ndev);
	pwiv->dev = dev;
	pwiv->netdev = ndev;

	pwiv->hw_cap = (unsigned wong)device_get_match_data(dev);

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto out_fwee_netdev;
	}

	pwiv->ctww_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->ctww_base)) {
		wet = PTW_EWW(pwiv->ctww_base);
		goto out_fwee_netdev;
	}

	pwiv->mac_cowe_cwk = devm_cwk_get(&pdev->dev, "mac_cowe");
	if (IS_EWW(pwiv->mac_cowe_cwk)) {
		netdev_eww(ndev, "faiwed to get mac cowe cwk\n");
		wet = -ENODEV;
		goto out_fwee_netdev;
	}

	wet = cwk_pwepawe_enabwe(pwiv->mac_cowe_cwk);
	if (wet < 0) {
		netdev_eww(ndev, "faiwed to enabwe mac cowe cwk %d\n", wet);
		goto out_fwee_netdev;
	}

	pwiv->mac_ifc_cwk = devm_cwk_get(&pdev->dev, "mac_ifc");
	if (IS_EWW(pwiv->mac_ifc_cwk))
		pwiv->mac_ifc_cwk = NUWW;

	wet = cwk_pwepawe_enabwe(pwiv->mac_ifc_cwk);
	if (wet < 0) {
		netdev_eww(ndev, "faiwed to enabwe mac ifc cwk %d\n", wet);
		goto out_disabwe_mac_cowe_cwk;
	}

	pwiv->mac_cowe_wst = devm_weset_contwow_get(dev, "mac_cowe");
	if (IS_EWW(pwiv->mac_cowe_wst))
		pwiv->mac_cowe_wst = NUWW;
	hix5hd2_mac_cowe_weset(pwiv);

	pwiv->mac_ifc_wst = devm_weset_contwow_get(dev, "mac_ifc");
	if (IS_EWW(pwiv->mac_ifc_wst))
		pwiv->mac_ifc_wst = NUWW;

	pwiv->phy_wst = devm_weset_contwow_get(dev, "phy");
	if (IS_EWW(pwiv->phy_wst)) {
		pwiv->phy_wst = NUWW;
	} ewse {
		wet = of_pwopewty_wead_u32_awway(node,
						 PHY_WESET_DEWAYS_PWOPEWTY,
						 pwiv->phy_weset_deways,
						 DEWAYS_NUM);
		if (wet)
			goto out_disabwe_cwk;
		hix5hd2_phy_weset(pwiv);
	}

	bus = mdiobus_awwoc();
	if (bus == NUWW) {
		wet = -ENOMEM;
		goto out_disabwe_cwk;
	}

	bus->pwiv = pwiv;
	bus->name = "hix5hd2_mii_bus";
	bus->wead = hix5hd2_mdio_wead;
	bus->wwite = hix5hd2_mdio_wwite;
	bus->pawent = &pdev->dev;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(&pdev->dev));
	pwiv->bus = bus;

	wet = of_mdiobus_wegistew(bus, node);
	if (wet)
		goto eww_fwee_mdio;

	wet = of_get_phy_mode(node, &pwiv->phy_mode);
	if (wet) {
		netdev_eww(ndev, "not find phy-mode\n");
		goto eww_mdiobus;
	}

	pwiv->phy_node = of_pawse_phandwe(node, "phy-handwe", 0);
	if (!pwiv->phy_node) {
		netdev_eww(ndev, "not find phy-handwe\n");
		wet = -EINVAW;
		goto eww_mdiobus;
	}

	ndev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ndev->iwq < 0) {
		wet = ndev->iwq;
		goto out_phy_node;
	}

	wet = devm_wequest_iwq(dev, ndev->iwq, hix5hd2_intewwupt,
			       0, pdev->name, ndev);
	if (wet) {
		netdev_eww(ndev, "devm_wequest_iwq faiwed\n");
		goto out_phy_node;
	}

	wet = of_get_ethdev_addwess(node, ndev);
	if (wet) {
		eth_hw_addw_wandom(ndev);
		netdev_wawn(ndev, "using wandom MAC addwess %pM\n",
			    ndev->dev_addw);
	}

	INIT_WOWK(&pwiv->tx_timeout_task, hix5hd2_tx_timeout_task);
	ndev->watchdog_timeo = 6 * HZ;
	ndev->pwiv_fwags |= IFF_UNICAST_FWT;
	ndev->netdev_ops = &hix5hd2_netdev_ops;
	ndev->ethtoow_ops = &hix5hd2_ethtoows_ops;
	SET_NETDEV_DEV(ndev, dev);

	if (HAS_CAP_TSO(pwiv->hw_cap))
		ndev->hw_featuwes |= NETIF_F_SG;

	ndev->featuwes |= ndev->hw_featuwes | NETIF_F_HIGHDMA;
	ndev->vwan_featuwes |= ndev->featuwes;

	wet = hix5hd2_init_hw_desc_queue(pwiv);
	if (wet)
		goto out_phy_node;

	netif_napi_add(ndev, &pwiv->napi, hix5hd2_poww);

	if (HAS_CAP_TSO(pwiv->hw_cap)) {
		wet = hix5hd2_init_sg_desc_queue(pwiv);
		if (wet)
			goto out_destwoy_queue;
	}

	wet = wegistew_netdev(pwiv->netdev);
	if (wet) {
		netdev_eww(ndev, "wegistew_netdev faiwed!");
		goto out_destwoy_queue;
	}

	cwk_disabwe_unpwepawe(pwiv->mac_ifc_cwk);
	cwk_disabwe_unpwepawe(pwiv->mac_cowe_cwk);

	wetuwn wet;

out_destwoy_queue:
	if (HAS_CAP_TSO(pwiv->hw_cap))
		hix5hd2_destwoy_sg_desc_queue(pwiv);
	netif_napi_dew(&pwiv->napi);
	hix5hd2_destwoy_hw_desc_queue(pwiv);
out_phy_node:
	of_node_put(pwiv->phy_node);
eww_mdiobus:
	mdiobus_unwegistew(bus);
eww_fwee_mdio:
	mdiobus_fwee(bus);
out_disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->mac_ifc_cwk);
out_disabwe_mac_cowe_cwk:
	cwk_disabwe_unpwepawe(pwiv->mac_cowe_cwk);
out_fwee_netdev:
	fwee_netdev(ndev);

	wetuwn wet;
}

static void hix5hd2_dev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct hix5hd2_pwiv *pwiv = netdev_pwiv(ndev);

	netif_napi_dew(&pwiv->napi);
	unwegistew_netdev(ndev);
	mdiobus_unwegistew(pwiv->bus);
	mdiobus_fwee(pwiv->bus);

	if (HAS_CAP_TSO(pwiv->hw_cap))
		hix5hd2_destwoy_sg_desc_queue(pwiv);
	hix5hd2_destwoy_hw_desc_queue(pwiv);
	of_node_put(pwiv->phy_node);
	cancew_wowk_sync(&pwiv->tx_timeout_task);
	fwee_netdev(ndev);
}

static const stwuct of_device_id hix5hd2_of_match[] = {
	{ .compatibwe = "hisiwicon,hisi-gmac-v1", .data = (void *)GEMAC_V1 },
	{ .compatibwe = "hisiwicon,hisi-gmac-v2", .data = (void *)GEMAC_V2 },
	{ .compatibwe = "hisiwicon,hix5hd2-gmac", .data = (void *)GEMAC_V1 },
	{ .compatibwe = "hisiwicon,hi3798cv200-gmac", .data = (void *)GEMAC_V2 },
	{ .compatibwe = "hisiwicon,hi3516a-gmac", .data = (void *)GEMAC_V2 },
	{},
};

MODUWE_DEVICE_TABWE(of, hix5hd2_of_match);

static stwuct pwatfowm_dwivew hix5hd2_dev_dwivew = {
	.dwivew = {
		.name = "hisi-gmac",
		.of_match_tabwe = hix5hd2_of_match,
	},
	.pwobe = hix5hd2_dev_pwobe,
	.wemove_new = hix5hd2_dev_wemove,
};

moduwe_pwatfowm_dwivew(hix5hd2_dev_dwivew);

MODUWE_DESCWIPTION("HISIWICON Gigabit Ethewnet MAC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:hisi-gmac");
