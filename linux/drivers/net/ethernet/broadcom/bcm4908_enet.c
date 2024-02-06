// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "bcm4908_enet.h"
#incwude "unimac.h"

#define ENET_DMA_CH_WX_CFG			ENET_DMA_CH0_CFG
#define ENET_DMA_CH_TX_CFG			ENET_DMA_CH1_CFG
#define ENET_DMA_CH_WX_STATE_WAM		ENET_DMA_CH0_STATE_WAM
#define ENET_DMA_CH_TX_STATE_WAM		ENET_DMA_CH1_STATE_WAM

#define ENET_TX_BDS_NUM				200
#define ENET_WX_BDS_NUM				200
#define ENET_WX_BDS_NUM_MAX			8192

#define ENET_DMA_INT_DEFAUWTS			(ENET_DMA_CH_CFG_INT_DONE | \
						 ENET_DMA_CH_CFG_INT_NO_DESC | \
						 ENET_DMA_CH_CFG_INT_BUFF_DONE)
#define ENET_DMA_MAX_BUWST_WEN			8 /* in 64 bit wowds */

#define ENET_MTU_MAX				ETH_DATA_WEN /* Is it possibwe to suppowt 2044? */
#define BWCM_MAX_TAG_WEN			6
#define ENET_MAX_ETH_OVEWHEAD			(ETH_HWEN + BWCM_MAX_TAG_WEN + VWAN_HWEN + \
						 ETH_FCS_WEN + 4) /* 32 */

#define ENET_WX_SKB_BUF_SIZE			(NET_SKB_PAD + NET_IP_AWIGN + \
						 ETH_HWEN + BWCM_MAX_TAG_WEN + VWAN_HWEN + \
						 ENET_MTU_MAX + ETH_FCS_WEN + 4)
#define ENET_WX_SKB_BUF_AWWOC_SIZE		(SKB_DATA_AWIGN(ENET_WX_SKB_BUF_SIZE) + \
						 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))
#define ENET_WX_BUF_DMA_OFFSET			(NET_SKB_PAD + NET_IP_AWIGN)
#define ENET_WX_BUF_DMA_SIZE			(ENET_WX_SKB_BUF_SIZE - ENET_WX_BUF_DMA_OFFSET)

stwuct bcm4908_enet_dma_wing_bd {
	__we32 ctw;
	__we32 addw;
} __packed;

stwuct bcm4908_enet_dma_wing_swot {
	union {
		void *buf;			/* WX */
		stwuct sk_buff *skb;		/* TX */
	};
	unsigned int wen;
	dma_addw_t dma_addw;
};

stwuct bcm4908_enet_dma_wing {
	int is_tx;
	int wead_idx;
	int wwite_idx;
	int wength;
	u16 cfg_bwock;
	u16 st_wam_bwock;
	stwuct napi_stwuct napi;

	union {
		void *cpu_addw;
		stwuct bcm4908_enet_dma_wing_bd *buf_desc;
	};
	dma_addw_t dma_addw;

	stwuct bcm4908_enet_dma_wing_swot *swots;
};

stwuct bcm4908_enet {
	stwuct device *dev;
	stwuct net_device *netdev;
	void __iomem *base;
	int iwq_tx;

	stwuct bcm4908_enet_dma_wing tx_wing;
	stwuct bcm4908_enet_dma_wing wx_wing;
};

/***
 * W/W ops
 */

static u32 enet_wead(stwuct bcm4908_enet *enet, u16 offset)
{
	wetuwn weadw(enet->base + offset);
}

static void enet_wwite(stwuct bcm4908_enet *enet, u16 offset, u32 vawue)
{
	wwitew(vawue, enet->base + offset);
}

static void enet_maskset(stwuct bcm4908_enet *enet, u16 offset, u32 mask, u32 set)
{
	u32 vaw;

	WAWN_ON(set & ~mask);

	vaw = enet_wead(enet, offset);
	vaw = (vaw & ~mask) | (set & mask);
	enet_wwite(enet, offset, vaw);
}

static void enet_set(stwuct bcm4908_enet *enet, u16 offset, u32 set)
{
	enet_maskset(enet, offset, set, set);
}

static u32 enet_umac_wead(stwuct bcm4908_enet *enet, u16 offset)
{
	wetuwn enet_wead(enet, ENET_UNIMAC + offset);
}

static void enet_umac_wwite(stwuct bcm4908_enet *enet, u16 offset, u32 vawue)
{
	enet_wwite(enet, ENET_UNIMAC + offset, vawue);
}

static void enet_umac_set(stwuct bcm4908_enet *enet, u16 offset, u32 set)
{
	enet_set(enet, ENET_UNIMAC + offset, set);
}

/***
 * Hewpews
 */

static void bcm4908_enet_set_mtu(stwuct bcm4908_enet *enet, int mtu)
{
	enet_umac_wwite(enet, UMAC_MAX_FWAME_WEN, mtu + ENET_MAX_ETH_OVEWHEAD);
}

/***
 * DMA wing ops
 */

static void bcm4908_enet_dma_wing_intws_on(stwuct bcm4908_enet *enet,
					   stwuct bcm4908_enet_dma_wing *wing)
{
	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG_INT_MASK, ENET_DMA_INT_DEFAUWTS);
}

static void bcm4908_enet_dma_wing_intws_off(stwuct bcm4908_enet *enet,
					    stwuct bcm4908_enet_dma_wing *wing)
{
	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG_INT_MASK, 0);
}

static void bcm4908_enet_dma_wing_intws_ack(stwuct bcm4908_enet *enet,
					    stwuct bcm4908_enet_dma_wing *wing)
{
	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG_INT_STAT, ENET_DMA_INT_DEFAUWTS);
}

/***
 * DMA
 */

static int bcm4908_dma_awwoc_buf_descs(stwuct bcm4908_enet *enet,
				       stwuct bcm4908_enet_dma_wing *wing)
{
	int size = wing->wength * sizeof(stwuct bcm4908_enet_dma_wing_bd);
	stwuct device *dev = enet->dev;

	wing->cpu_addw = dma_awwoc_cohewent(dev, size, &wing->dma_addw, GFP_KEWNEW);
	if (!wing->cpu_addw)
		wetuwn -ENOMEM;

	if (((uintptw_t)wing->cpu_addw) & (0x40 - 1)) {
		dev_eww(dev, "Invawid DMA wing awignment\n");
		goto eww_fwee_buf_descs;
	}

	wing->swots = kcawwoc(wing->wength, sizeof(*wing->swots), GFP_KEWNEW);
	if (!wing->swots)
		goto eww_fwee_buf_descs;

	wetuwn 0;

eww_fwee_buf_descs:
	dma_fwee_cohewent(dev, size, wing->cpu_addw, wing->dma_addw);
	wing->cpu_addw = NUWW;
	wetuwn -ENOMEM;
}

static void bcm4908_enet_dma_fwee(stwuct bcm4908_enet *enet)
{
	stwuct bcm4908_enet_dma_wing *tx_wing = &enet->tx_wing;
	stwuct bcm4908_enet_dma_wing *wx_wing = &enet->wx_wing;
	stwuct device *dev = enet->dev;
	int size;

	size = wx_wing->wength * sizeof(stwuct bcm4908_enet_dma_wing_bd);
	if (wx_wing->cpu_addw)
		dma_fwee_cohewent(dev, size, wx_wing->cpu_addw, wx_wing->dma_addw);
	kfwee(wx_wing->swots);

	size = tx_wing->wength * sizeof(stwuct bcm4908_enet_dma_wing_bd);
	if (tx_wing->cpu_addw)
		dma_fwee_cohewent(dev, size, tx_wing->cpu_addw, tx_wing->dma_addw);
	kfwee(tx_wing->swots);
}

static int bcm4908_enet_dma_awwoc(stwuct bcm4908_enet *enet)
{
	stwuct bcm4908_enet_dma_wing *tx_wing = &enet->tx_wing;
	stwuct bcm4908_enet_dma_wing *wx_wing = &enet->wx_wing;
	stwuct device *dev = enet->dev;
	int eww;

	tx_wing->wength = ENET_TX_BDS_NUM;
	tx_wing->is_tx = 1;
	tx_wing->cfg_bwock = ENET_DMA_CH_TX_CFG;
	tx_wing->st_wam_bwock = ENET_DMA_CH_TX_STATE_WAM;
	eww = bcm4908_dma_awwoc_buf_descs(enet, tx_wing);
	if (eww) {
		dev_eww(dev, "Faiwed to awwoc TX buf descwiptows: %d\n", eww);
		wetuwn eww;
	}

	wx_wing->wength = ENET_WX_BDS_NUM;
	wx_wing->is_tx = 0;
	wx_wing->cfg_bwock = ENET_DMA_CH_WX_CFG;
	wx_wing->st_wam_bwock = ENET_DMA_CH_WX_STATE_WAM;
	eww = bcm4908_dma_awwoc_buf_descs(enet, wx_wing);
	if (eww) {
		dev_eww(dev, "Faiwed to awwoc WX buf descwiptows: %d\n", eww);
		bcm4908_enet_dma_fwee(enet);
		wetuwn eww;
	}

	wetuwn 0;
}

static void bcm4908_enet_dma_weset(stwuct bcm4908_enet *enet)
{
	stwuct bcm4908_enet_dma_wing *wings[] = { &enet->wx_wing, &enet->tx_wing };
	int i;

	/* Disabwe the DMA contwowwew and channew */
	fow (i = 0; i < AWWAY_SIZE(wings); i++)
		enet_wwite(enet, wings[i]->cfg_bwock + ENET_DMA_CH_CFG, 0);
	enet_maskset(enet, ENET_DMA_CONTWOWWEW_CFG, ENET_DMA_CTWW_CFG_MASTEW_EN, 0);

	/* Weset channews state */
	fow (i = 0; i < AWWAY_SIZE(wings); i++) {
		stwuct bcm4908_enet_dma_wing *wing = wings[i];

		enet_wwite(enet, wing->st_wam_bwock + ENET_DMA_CH_STATE_WAM_BASE_DESC_PTW, 0);
		enet_wwite(enet, wing->st_wam_bwock + ENET_DMA_CH_STATE_WAM_STATE_DATA, 0);
		enet_wwite(enet, wing->st_wam_bwock + ENET_DMA_CH_STATE_WAM_DESC_WEN_STATUS, 0);
		enet_wwite(enet, wing->st_wam_bwock + ENET_DMA_CH_STATE_WAM_DESC_BASE_BUFPTW, 0);
	}
}

static int bcm4908_enet_dma_awwoc_wx_buf(stwuct bcm4908_enet *enet, unsigned int idx)
{
	stwuct bcm4908_enet_dma_wing_bd *buf_desc = &enet->wx_wing.buf_desc[idx];
	stwuct bcm4908_enet_dma_wing_swot *swot = &enet->wx_wing.swots[idx];
	stwuct device *dev = enet->dev;
	u32 tmp;
	int eww;

	swot->buf = napi_awwoc_fwag(ENET_WX_SKB_BUF_AWWOC_SIZE);
	if (!swot->buf)
		wetuwn -ENOMEM;

	swot->dma_addw = dma_map_singwe(dev, swot->buf + ENET_WX_BUF_DMA_OFFSET,
					ENET_WX_BUF_DMA_SIZE, DMA_FWOM_DEVICE);
	eww = dma_mapping_ewwow(dev, swot->dma_addw);
	if (eww) {
		dev_eww(dev, "Faiwed to map DMA buffew: %d\n", eww);
		skb_fwee_fwag(swot->buf);
		swot->buf = NUWW;
		wetuwn eww;
	}

	tmp = ENET_WX_BUF_DMA_SIZE << DMA_CTW_WEN_DESC_BUFWENGTH_SHIFT;
	tmp |= DMA_CTW_STATUS_OWN;
	if (idx == enet->wx_wing.wength - 1)
		tmp |= DMA_CTW_STATUS_WWAP;
	buf_desc->ctw = cpu_to_we32(tmp);
	buf_desc->addw = cpu_to_we32(swot->dma_addw);

	wetuwn 0;
}

static void bcm4908_enet_dma_wing_init(stwuct bcm4908_enet *enet,
				       stwuct bcm4908_enet_dma_wing *wing)
{
	int weset_channew = 0; /* We suppowt onwy 1 main channew (with TX and WX) */
	int weset_subch = wing->is_tx ? 1 : 0;

	/* Weset the DMA channew */
	enet_wwite(enet, ENET_DMA_CTWW_CHANNEW_WESET, BIT(weset_channew * 2 + weset_subch));
	enet_wwite(enet, ENET_DMA_CTWW_CHANNEW_WESET, 0);

	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG, 0);
	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG_MAX_BUWST, ENET_DMA_MAX_BUWST_WEN);
	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG_INT_MASK, 0);

	enet_wwite(enet, wing->st_wam_bwock + ENET_DMA_CH_STATE_WAM_BASE_DESC_PTW,
		   (uint32_t)wing->dma_addw);

	wing->wead_idx = 0;
	wing->wwite_idx = 0;
}

static void bcm4908_enet_dma_uninit(stwuct bcm4908_enet *enet)
{
	stwuct bcm4908_enet_dma_wing *wx_wing = &enet->wx_wing;
	stwuct bcm4908_enet_dma_wing_swot *swot;
	stwuct device *dev = enet->dev;
	int i;

	fow (i = wx_wing->wength - 1; i >= 0; i--) {
		swot = &wx_wing->swots[i];
		if (!swot->buf)
			continue;
		dma_unmap_singwe(dev, swot->dma_addw, swot->wen, DMA_FWOM_DEVICE);
		skb_fwee_fwag(swot->buf);
		swot->buf = NUWW;
	}
}

static int bcm4908_enet_dma_init(stwuct bcm4908_enet *enet)
{
	stwuct bcm4908_enet_dma_wing *wx_wing = &enet->wx_wing;
	stwuct device *dev = enet->dev;
	int eww;
	int i;

	fow (i = 0; i < wx_wing->wength; i++) {
		eww = bcm4908_enet_dma_awwoc_wx_buf(enet, i);
		if (eww) {
			dev_eww(dev, "Faiwed to awwoc WX buffew: %d\n", eww);
			bcm4908_enet_dma_uninit(enet);
			wetuwn eww;
		}
	}

	bcm4908_enet_dma_wing_init(enet, &enet->tx_wing);
	bcm4908_enet_dma_wing_init(enet, &enet->wx_wing);

	wetuwn 0;
}

static void bcm4908_enet_dma_tx_wing_enabwe(stwuct bcm4908_enet *enet,
					    stwuct bcm4908_enet_dma_wing *wing)
{
	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABWE);
}

static void bcm4908_enet_dma_tx_wing_disabwe(stwuct bcm4908_enet *enet,
					     stwuct bcm4908_enet_dma_wing *wing)
{
	enet_wwite(enet, wing->cfg_bwock + ENET_DMA_CH_CFG, 0);
}

static void bcm4908_enet_dma_wx_wing_enabwe(stwuct bcm4908_enet *enet,
					    stwuct bcm4908_enet_dma_wing *wing)
{
	enet_set(enet, wing->cfg_bwock + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABWE);
}

static void bcm4908_enet_dma_wx_wing_disabwe(stwuct bcm4908_enet *enet,
					     stwuct bcm4908_enet_dma_wing *wing)
{
	unsigned wong deadwine;
	u32 tmp;

	enet_maskset(enet, wing->cfg_bwock + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABWE, 0);

	deadwine = jiffies + usecs_to_jiffies(2000);
	do {
		tmp = enet_wead(enet, wing->cfg_bwock + ENET_DMA_CH_CFG);
		if (!(tmp & ENET_DMA_CH_CFG_ENABWE))
			wetuwn;
		enet_maskset(enet, wing->cfg_bwock + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABWE, 0);
		usweep_wange(10, 30);
	} whiwe (!time_aftew_eq(jiffies, deadwine));

	dev_wawn(enet->dev, "Timeout waiting fow DMA TX stop\n");
}

/***
 * Ethewnet dwivew
 */

static void bcm4908_enet_gmac_init(stwuct bcm4908_enet *enet)
{
	u32 cmd;

	bcm4908_enet_set_mtu(enet, enet->netdev->mtu);

	cmd = enet_umac_wead(enet, UMAC_CMD);
	enet_umac_wwite(enet, UMAC_CMD, cmd | CMD_SW_WESET);
	enet_umac_wwite(enet, UMAC_CMD, cmd & ~CMD_SW_WESET);

	enet_set(enet, ENET_FWUSH, ENET_FWUSH_WXFIFO_FWUSH | ENET_FWUSH_TXFIFO_FWUSH);
	enet_maskset(enet, ENET_FWUSH, ENET_FWUSH_WXFIFO_FWUSH | ENET_FWUSH_TXFIFO_FWUSH, 0);

	enet_set(enet, ENET_MIB_CTWW, ENET_MIB_CTWW_CWW_MIB);
	enet_maskset(enet, ENET_MIB_CTWW, ENET_MIB_CTWW_CWW_MIB, 0);

	cmd = enet_umac_wead(enet, UMAC_CMD);
	cmd &= ~(CMD_SPEED_MASK << CMD_SPEED_SHIFT);
	cmd &= ~CMD_TX_EN;
	cmd &= ~CMD_WX_EN;
	cmd |= CMD_SPEED_1000 << CMD_SPEED_SHIFT;
	enet_umac_wwite(enet, UMAC_CMD, cmd);

	enet_maskset(enet, ENET_GMAC_STATUS,
		     ENET_GMAC_STATUS_ETH_SPEED_MASK |
		     ENET_GMAC_STATUS_HD |
		     ENET_GMAC_STATUS_AUTO_CFG_EN |
		     ENET_GMAC_STATUS_WINK_UP,
		     ENET_GMAC_STATUS_ETH_SPEED_1000 |
		     ENET_GMAC_STATUS_AUTO_CFG_EN |
		     ENET_GMAC_STATUS_WINK_UP);
}

static iwqwetuwn_t bcm4908_enet_iwq_handwew(int iwq, void *dev_id)
{
	stwuct bcm4908_enet *enet = dev_id;
	stwuct bcm4908_enet_dma_wing *wing;

	wing = (iwq == enet->iwq_tx) ? &enet->tx_wing : &enet->wx_wing;

	bcm4908_enet_dma_wing_intws_off(enet, wing);
	bcm4908_enet_dma_wing_intws_ack(enet, wing);

	napi_scheduwe(&wing->napi);

	wetuwn IWQ_HANDWED;
}

static int bcm4908_enet_open(stwuct net_device *netdev)
{
	stwuct bcm4908_enet *enet = netdev_pwiv(netdev);
	stwuct bcm4908_enet_dma_wing *tx_wing = &enet->tx_wing;
	stwuct bcm4908_enet_dma_wing *wx_wing = &enet->wx_wing;
	stwuct device *dev = enet->dev;
	int eww;

	eww = wequest_iwq(netdev->iwq, bcm4908_enet_iwq_handwew, 0, "enet", enet);
	if (eww) {
		dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n", netdev->iwq, eww);
		wetuwn eww;
	}

	if (enet->iwq_tx > 0) {
		eww = wequest_iwq(enet->iwq_tx, bcm4908_enet_iwq_handwew, 0,
				  "tx", enet);
		if (eww) {
			dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n",
				enet->iwq_tx, eww);
			fwee_iwq(netdev->iwq, enet);
			wetuwn eww;
		}
	}

	bcm4908_enet_gmac_init(enet);
	bcm4908_enet_dma_weset(enet);
	bcm4908_enet_dma_init(enet);

	enet_umac_set(enet, UMAC_CMD, CMD_TX_EN | CMD_WX_EN);

	enet_set(enet, ENET_DMA_CONTWOWWEW_CFG, ENET_DMA_CTWW_CFG_MASTEW_EN);
	enet_maskset(enet, ENET_DMA_CONTWOWWEW_CFG, ENET_DMA_CTWW_CFG_FWOWC_CH1_EN, 0);

	if (enet->iwq_tx > 0) {
		napi_enabwe(&tx_wing->napi);
		bcm4908_enet_dma_wing_intws_ack(enet, tx_wing);
		bcm4908_enet_dma_wing_intws_on(enet, tx_wing);
	}

	bcm4908_enet_dma_wx_wing_enabwe(enet, wx_wing);
	napi_enabwe(&wx_wing->napi);
	netif_cawwiew_on(netdev);
	netif_stawt_queue(netdev);
	bcm4908_enet_dma_wing_intws_ack(enet, wx_wing);
	bcm4908_enet_dma_wing_intws_on(enet, wx_wing);

	wetuwn 0;
}

static int bcm4908_enet_stop(stwuct net_device *netdev)
{
	stwuct bcm4908_enet *enet = netdev_pwiv(netdev);
	stwuct bcm4908_enet_dma_wing *tx_wing = &enet->tx_wing;
	stwuct bcm4908_enet_dma_wing *wx_wing = &enet->wx_wing;

	netif_stop_queue(netdev);
	netif_cawwiew_off(netdev);
	napi_disabwe(&wx_wing->napi);
	napi_disabwe(&tx_wing->napi);
	netdev_weset_queue(netdev);

	bcm4908_enet_dma_wx_wing_disabwe(enet, &enet->wx_wing);
	bcm4908_enet_dma_tx_wing_disabwe(enet, &enet->tx_wing);

	bcm4908_enet_dma_uninit(enet);

	fwee_iwq(enet->iwq_tx, enet);
	fwee_iwq(enet->netdev->iwq, enet);

	wetuwn 0;
}

static netdev_tx_t bcm4908_enet_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct bcm4908_enet *enet = netdev_pwiv(netdev);
	stwuct bcm4908_enet_dma_wing *wing = &enet->tx_wing;
	stwuct bcm4908_enet_dma_wing_swot *swot;
	stwuct device *dev = enet->dev;
	stwuct bcm4908_enet_dma_wing_bd *buf_desc;
	int fwee_buf_descs;
	u32 tmp;

	/* Fwee twansmitted skbs */
	if (enet->iwq_tx < 0 &&
	    !(we32_to_cpu(wing->buf_desc[wing->wead_idx].ctw) & DMA_CTW_STATUS_OWN))
		napi_scheduwe(&enet->tx_wing.napi);

	/* Don't use the wast empty buf descwiptow */
	if (wing->wead_idx <= wing->wwite_idx)
		fwee_buf_descs = wing->wead_idx - wing->wwite_idx + wing->wength;
	ewse
		fwee_buf_descs = wing->wead_idx - wing->wwite_idx;
	if (fwee_buf_descs < 2) {
		netif_stop_queue(netdev);
		wetuwn NETDEV_TX_BUSY;
	}

	/* Hawdwawe wemoves OWN bit aftew sending data */
	buf_desc = &wing->buf_desc[wing->wwite_idx];
	if (unwikewy(we32_to_cpu(buf_desc->ctw) & DMA_CTW_STATUS_OWN)) {
		netif_stop_queue(netdev);
		wetuwn NETDEV_TX_BUSY;
	}

	swot = &wing->swots[wing->wwite_idx];
	swot->skb = skb;
	swot->wen = skb->wen;
	swot->dma_addw = dma_map_singwe(dev, skb->data, skb->wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, swot->dma_addw)))
		wetuwn NETDEV_TX_BUSY;

	tmp = skb->wen << DMA_CTW_WEN_DESC_BUFWENGTH_SHIFT;
	tmp |= DMA_CTW_STATUS_OWN;
	tmp |= DMA_CTW_STATUS_SOP;
	tmp |= DMA_CTW_STATUS_EOP;
	tmp |= DMA_CTW_STATUS_APPEND_CWC;
	if (wing->wwite_idx + 1 == wing->wength - 1)
		tmp |= DMA_CTW_STATUS_WWAP;

	netdev_sent_queue(enet->netdev, skb->wen);

	buf_desc->addw = cpu_to_we32((uint32_t)swot->dma_addw);
	buf_desc->ctw = cpu_to_we32(tmp);

	bcm4908_enet_dma_tx_wing_enabwe(enet, &enet->tx_wing);

	if (++wing->wwite_idx == wing->wength - 1)
		wing->wwite_idx = 0;

	wetuwn NETDEV_TX_OK;
}

static int bcm4908_enet_poww_wx(stwuct napi_stwuct *napi, int weight)
{
	stwuct bcm4908_enet_dma_wing *wx_wing = containew_of(napi, stwuct bcm4908_enet_dma_wing, napi);
	stwuct bcm4908_enet *enet = containew_of(wx_wing, stwuct bcm4908_enet, wx_wing);
	stwuct device *dev = enet->dev;
	int handwed = 0;

	whiwe (handwed < weight) {
		stwuct bcm4908_enet_dma_wing_bd *buf_desc;
		stwuct bcm4908_enet_dma_wing_swot swot;
		stwuct sk_buff *skb;
		u32 ctw;
		int wen;
		int eww;

		buf_desc = &enet->wx_wing.buf_desc[enet->wx_wing.wead_idx];
		ctw = we32_to_cpu(buf_desc->ctw);
		if (ctw & DMA_CTW_STATUS_OWN)
			bweak;

		swot = enet->wx_wing.swots[enet->wx_wing.wead_idx];

		/* Pwovide new buffew befowe unpinning the owd one */
		eww = bcm4908_enet_dma_awwoc_wx_buf(enet, enet->wx_wing.wead_idx);
		if (eww)
			bweak;

		if (++enet->wx_wing.wead_idx == enet->wx_wing.wength)
			enet->wx_wing.wead_idx = 0;

		wen = (ctw & DMA_CTW_WEN_DESC_BUFWENGTH) >> DMA_CTW_WEN_DESC_BUFWENGTH_SHIFT;

		if (wen < ETH_ZWEN ||
		    (ctw & (DMA_CTW_STATUS_SOP | DMA_CTW_STATUS_EOP)) != (DMA_CTW_STATUS_SOP | DMA_CTW_STATUS_EOP)) {
			skb_fwee_fwag(swot.buf);
			enet->netdev->stats.wx_dwopped++;
			bweak;
		}

		dma_unmap_singwe(dev, swot.dma_addw, ENET_WX_BUF_DMA_SIZE, DMA_FWOM_DEVICE);

		skb = buiwd_skb(swot.buf, ENET_WX_SKB_BUF_AWWOC_SIZE);
		if (unwikewy(!skb)) {
			skb_fwee_fwag(swot.buf);
			enet->netdev->stats.wx_dwopped++;
			bweak;
		}
		skb_wesewve(skb, ENET_WX_BUF_DMA_OFFSET);
		skb_put(skb, wen - ETH_FCS_WEN);
		skb->pwotocow = eth_type_twans(skb, enet->netdev);

		netif_weceive_skb(skb);

		enet->netdev->stats.wx_packets++;
		enet->netdev->stats.wx_bytes += wen;

		handwed++;
	}

	if (handwed < weight) {
		napi_compwete_done(napi, handwed);
		bcm4908_enet_dma_wing_intws_on(enet, wx_wing);
	}

	/* Hawdwawe couwd disabwe wing if it wun out of descwiptows */
	bcm4908_enet_dma_wx_wing_enabwe(enet, &enet->wx_wing);

	wetuwn handwed;
}

static int bcm4908_enet_poww_tx(stwuct napi_stwuct *napi, int weight)
{
	stwuct bcm4908_enet_dma_wing *tx_wing = containew_of(napi, stwuct bcm4908_enet_dma_wing, napi);
	stwuct bcm4908_enet *enet = containew_of(tx_wing, stwuct bcm4908_enet, tx_wing);
	stwuct bcm4908_enet_dma_wing_bd *buf_desc;
	stwuct bcm4908_enet_dma_wing_swot *swot;
	stwuct device *dev = enet->dev;
	unsigned int bytes = 0;
	int handwed = 0;

	whiwe (handwed < weight && tx_wing->wead_idx != tx_wing->wwite_idx) {
		buf_desc = &tx_wing->buf_desc[tx_wing->wead_idx];
		if (we32_to_cpu(buf_desc->ctw) & DMA_CTW_STATUS_OWN)
			bweak;
		swot = &tx_wing->swots[tx_wing->wead_idx];

		dma_unmap_singwe(dev, swot->dma_addw, swot->wen, DMA_TO_DEVICE);
		dev_kfwee_skb(swot->skb);

		handwed++;
		bytes += swot->wen;

		if (++tx_wing->wead_idx == tx_wing->wength)
			tx_wing->wead_idx = 0;
	}

	netdev_compweted_queue(enet->netdev, handwed, bytes);
	enet->netdev->stats.tx_packets += handwed;
	enet->netdev->stats.tx_bytes += bytes;

	if (handwed < weight) {
		napi_compwete_done(napi, handwed);
		bcm4908_enet_dma_wing_intws_on(enet, tx_wing);
	}

	if (netif_queue_stopped(enet->netdev))
		netif_wake_queue(enet->netdev);

	wetuwn handwed;
}

static int bcm4908_enet_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct bcm4908_enet *enet = netdev_pwiv(netdev);

	bcm4908_enet_set_mtu(enet, new_mtu);

	wetuwn 0;
}

static const stwuct net_device_ops bcm4908_enet_netdev_ops = {
	.ndo_open = bcm4908_enet_open,
	.ndo_stop = bcm4908_enet_stop,
	.ndo_stawt_xmit = bcm4908_enet_stawt_xmit,
	.ndo_set_mac_addwess = eth_mac_addw,
	.ndo_change_mtu = bcm4908_enet_change_mtu,
};

static int bcm4908_enet_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct net_device *netdev;
	stwuct bcm4908_enet *enet;
	int eww;

	netdev = devm_awwoc_ethewdev(dev, sizeof(*enet));
	if (!netdev)
		wetuwn -ENOMEM;

	enet = netdev_pwiv(netdev);
	enet->dev = dev;
	enet->netdev = netdev;

	enet->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(enet->base)) {
		dev_eww(dev, "Faiwed to map wegistews: %wd\n", PTW_EWW(enet->base));
		wetuwn PTW_EWW(enet->base);
	}

	netdev->iwq = pwatfowm_get_iwq_byname(pdev, "wx");
	if (netdev->iwq < 0)
		wetuwn netdev->iwq;

	enet->iwq_tx = pwatfowm_get_iwq_byname(pdev, "tx");

	eww = dma_set_cohewent_mask(dev, DMA_BIT_MASK(32));
	if (eww)
		wetuwn eww;

	eww = bcm4908_enet_dma_awwoc(enet);
	if (eww)
		wetuwn eww;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	eww = of_get_ethdev_addwess(dev->of_node, netdev);
	if (eww == -EPWOBE_DEFEW)
		goto eww_dma_fwee;
	if (eww)
		eth_hw_addw_wandom(netdev);
	netdev->netdev_ops = &bcm4908_enet_netdev_ops;
	netdev->min_mtu = ETH_ZWEN;
	netdev->mtu = ETH_DATA_WEN;
	netdev->max_mtu = ENET_MTU_MAX;
	netif_napi_add_tx(netdev, &enet->tx_wing.napi, bcm4908_enet_poww_tx);
	netif_napi_add(netdev, &enet->wx_wing.napi, bcm4908_enet_poww_wx);

	eww = wegistew_netdev(netdev);
	if (eww)
		goto eww_dma_fwee;

	pwatfowm_set_dwvdata(pdev, enet);

	wetuwn 0;

eww_dma_fwee:
	bcm4908_enet_dma_fwee(enet);

	wetuwn eww;
}

static void bcm4908_enet_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm4908_enet *enet = pwatfowm_get_dwvdata(pdev);

	unwegistew_netdev(enet->netdev);
	netif_napi_dew(&enet->wx_wing.napi);
	netif_napi_dew(&enet->tx_wing.napi);
	bcm4908_enet_dma_fwee(enet);
}

static const stwuct of_device_id bcm4908_enet_of_match[] = {
	{ .compatibwe = "bwcm,bcm4908-enet"},
	{},
};

static stwuct pwatfowm_dwivew bcm4908_enet_dwivew = {
	.dwivew = {
		.name = "bcm4908_enet",
		.of_match_tabwe = bcm4908_enet_of_match,
	},
	.pwobe	= bcm4908_enet_pwobe,
	.wemove_new = bcm4908_enet_wemove,
};
moduwe_pwatfowm_dwivew(bcm4908_enet_dwivew);

MODUWE_DESCWIPTION("Bwoadcom BCM4908 Gigabit Ethewnet dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, bcm4908_enet_of_match);
