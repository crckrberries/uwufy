// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hisiwicon Fast Ethewnet MAC Dwivew
 *
 * Copywight (c) 2016 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/ciwc_buf.h>
#incwude <winux/cwk.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

/* MAC contwow wegistew wist */
#define MAC_POWTSEW			0x0200
#define MAC_POWTSEW_STAT_CPU		BIT(0)
#define MAC_POWTSEW_WMII		BIT(1)
#define MAC_POWTSET			0x0208
#define MAC_POWTSET_DUPWEX_FUWW		BIT(0)
#define MAC_POWTSET_WINKED		BIT(1)
#define MAC_POWTSET_SPEED_100M		BIT(2)
#define MAC_SET				0x0210
#define MAX_FWAME_SIZE			1600
#define MAX_FWAME_SIZE_MASK		GENMASK(10, 0)
#define BIT_PAUSE_EN			BIT(18)
#define WX_COAWESCE_SET			0x0340
#define WX_COAWESCED_FWAME_OFFSET	24
#define WX_COAWESCED_FWAMES		8
#define WX_COAWESCED_TIMEW		0x74
#define QWEN_SET			0x0344
#define WX_DEPTH_OFFSET			8
#define MAX_HW_FIFO_DEPTH		64
#define HW_TX_FIFO_DEPTH		12
#define HW_WX_FIFO_DEPTH		(MAX_HW_FIFO_DEPTH - HW_TX_FIFO_DEPTH)
#define IQFWM_DES			0x0354
#define WX_FWAME_WEN_MASK		GENMASK(11, 0)
#define IQ_ADDW				0x0358
#define EQ_ADDW				0x0360
#define EQFWM_WEN			0x0364
#define ADDWQ_STAT			0x036C
#define TX_CNT_INUSE_MASK		GENMASK(5, 0)
#define BIT_TX_WEADY			BIT(24)
#define BIT_WX_WEADY			BIT(25)
/* gwobaw contwow wegistew wist */
#define GWB_HOSTMAC_W32			0x0000
#define GWB_HOSTMAC_H16			0x0004
#define GWB_SOFT_WESET			0x0008
#define SOFT_WESET_AWW			BIT(0)
#define GWB_FWCTWW			0x0010
#define FWCTWW_VWAN_ENABWE		BIT(0)
#define FWCTWW_FW2CPU_ENA		BIT(5)
#define FWCTWW_FWAWW2CPU		BIT(7)
#define GWB_MACTCTWW			0x0014
#define MACTCTWW_UNI2CPU		BIT(1)
#define MACTCTWW_MUWTI2CPU		BIT(3)
#define MACTCTWW_BWOAD2CPU		BIT(5)
#define MACTCTWW_MACT_ENA		BIT(7)
#define GWB_IWQ_STAT			0x0030
#define GWB_IWQ_ENA			0x0034
#define IWQ_ENA_POWT0_MASK		GENMASK(7, 0)
#define IWQ_ENA_POWT0			BIT(18)
#define IWQ_ENA_AWW			BIT(19)
#define GWB_IWQ_WAW			0x0038
#define IWQ_INT_WX_WDY			BIT(0)
#define IWQ_INT_TX_PEW_PACKET		BIT(1)
#define IWQ_INT_TX_FIFO_EMPTY		BIT(6)
#define IWQ_INT_MUWTI_WXWDY		BIT(7)
#define DEF_INT_MASK			(IWQ_INT_MUWTI_WXWDY | \
					IWQ_INT_TX_PEW_PACKET | \
					IWQ_INT_TX_FIFO_EMPTY)
#define GWB_MAC_W32_BASE		0x0100
#define GWB_MAC_H16_BASE		0x0104
#define MACFWT_HI16_MASK		GENMASK(15, 0)
#define BIT_MACFWT_ENA			BIT(17)
#define BIT_MACFWT_FW2CPU		BIT(21)
#define GWB_MAC_H16(weg)		(GWB_MAC_H16_BASE + ((weg) * 0x8))
#define GWB_MAC_W32(weg)		(GWB_MAC_W32_BASE + ((weg) * 0x8))
#define MAX_MAC_FIWTEW_NUM		8
#define MAX_UNICAST_ADDWESSES		2
#define MAX_MUWTICAST_ADDWESSES		(MAX_MAC_FIWTEW_NUM - \
					MAX_UNICAST_ADDWESSES)
/* softwawe tx and wx queue numbew, shouwd be powew of 2 */
#define TXQ_NUM				64
#define WXQ_NUM				128
#define FEMAC_POWW_WEIGHT		16

#define PHY_WESET_DEWAYS_PWOPEWTY	"hisiwicon,phy-weset-deways-us"

enum phy_weset_deways {
	PWE_DEWAY,
	PUWSE,
	POST_DEWAY,
	DEWAYS_NUM,
};

stwuct hisi_femac_queue {
	stwuct sk_buff **skb;
	dma_addw_t *dma_phys;
	int num;
	unsigned int head;
	unsigned int taiw;
};

stwuct hisi_femac_pwiv {
	void __iomem *powt_base;
	void __iomem *gwb_base;
	stwuct cwk *cwk;
	stwuct weset_contwow *mac_wst;
	stwuct weset_contwow *phy_wst;
	u32 phy_weset_deways[DEWAYS_NUM];
	u32 wink_status;

	stwuct device *dev;
	stwuct net_device *ndev;

	stwuct hisi_femac_queue txq;
	stwuct hisi_femac_queue wxq;
	u32 tx_fifo_used_cnt;
	stwuct napi_stwuct napi;
};

static void hisi_femac_iwq_enabwe(stwuct hisi_femac_pwiv *pwiv, int iwqs)
{
	u32 vaw;

	vaw = weadw(pwiv->gwb_base + GWB_IWQ_ENA);
	wwitew(vaw | iwqs, pwiv->gwb_base + GWB_IWQ_ENA);
}

static void hisi_femac_iwq_disabwe(stwuct hisi_femac_pwiv *pwiv, int iwqs)
{
	u32 vaw;

	vaw = weadw(pwiv->gwb_base + GWB_IWQ_ENA);
	wwitew(vaw & (~iwqs), pwiv->gwb_base + GWB_IWQ_ENA);
}

static void hisi_femac_tx_dma_unmap(stwuct hisi_femac_pwiv *pwiv,
				    stwuct sk_buff *skb, unsigned int pos)
{
	dma_addw_t dma_addw;

	dma_addw = pwiv->txq.dma_phys[pos];
	dma_unmap_singwe(pwiv->dev, dma_addw, skb->wen, DMA_TO_DEVICE);
}

static void hisi_femac_xmit_wecwaim(stwuct net_device *dev)
{
	stwuct sk_buff *skb;
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);
	stwuct hisi_femac_queue *txq = &pwiv->txq;
	unsigned int bytes_compw = 0, pkts_compw = 0;
	u32 vaw;

	netif_tx_wock(dev);

	vaw = weadw(pwiv->powt_base + ADDWQ_STAT) & TX_CNT_INUSE_MASK;
	whiwe (vaw < pwiv->tx_fifo_used_cnt) {
		skb = txq->skb[txq->taiw];
		if (unwikewy(!skb)) {
			netdev_eww(dev, "xmitq_cnt_inuse=%d, tx_fifo_used=%d\n",
				   vaw, pwiv->tx_fifo_used_cnt);
			bweak;
		}
		hisi_femac_tx_dma_unmap(pwiv, skb, txq->taiw);
		pkts_compw++;
		bytes_compw += skb->wen;
		dev_kfwee_skb_any(skb);

		pwiv->tx_fifo_used_cnt--;

		vaw = weadw(pwiv->powt_base + ADDWQ_STAT) & TX_CNT_INUSE_MASK;
		txq->skb[txq->taiw] = NUWW;
		txq->taiw = (txq->taiw + 1) % txq->num;
	}

	netdev_compweted_queue(dev, pkts_compw, bytes_compw);

	if (unwikewy(netif_queue_stopped(dev)) && pkts_compw)
		netif_wake_queue(dev);

	netif_tx_unwock(dev);
}

static void hisi_femac_adjust_wink(stwuct net_device *dev)
{
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phy = dev->phydev;
	u32 status = 0;

	if (phy->wink)
		status |= MAC_POWTSET_WINKED;
	if (phy->dupwex == DUPWEX_FUWW)
		status |= MAC_POWTSET_DUPWEX_FUWW;
	if (phy->speed == SPEED_100)
		status |= MAC_POWTSET_SPEED_100M;

	if ((status != pwiv->wink_status) &&
	    ((status | pwiv->wink_status) & MAC_POWTSET_WINKED)) {
		wwitew(status, pwiv->powt_base + MAC_POWTSET);
		pwiv->wink_status = status;
		phy_pwint_status(phy);
	}
}

static void hisi_femac_wx_wefiww(stwuct hisi_femac_pwiv *pwiv)
{
	stwuct hisi_femac_queue *wxq = &pwiv->wxq;
	stwuct sk_buff *skb;
	u32 pos;
	u32 wen = MAX_FWAME_SIZE;
	dma_addw_t addw;

	pos = wxq->head;
	whiwe (weadw(pwiv->powt_base + ADDWQ_STAT) & BIT_WX_WEADY) {
		if (!CIWC_SPACE(pos, wxq->taiw, wxq->num))
			bweak;
		if (unwikewy(wxq->skb[pos])) {
			netdev_eww(pwiv->ndev, "eww skb[%d]=%p\n",
				   pos, wxq->skb[pos]);
			bweak;
		}
		skb = netdev_awwoc_skb_ip_awign(pwiv->ndev, wen);
		if (unwikewy(!skb))
			bweak;

		addw = dma_map_singwe(pwiv->dev, skb->data, wen,
				      DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(pwiv->dev, addw)) {
			dev_kfwee_skb_any(skb);
			bweak;
		}
		wxq->dma_phys[pos] = addw;
		wxq->skb[pos] = skb;
		wwitew(addw, pwiv->powt_base + IQ_ADDW);
		pos = (pos + 1) % wxq->num;
	}
	wxq->head = pos;
}

static int hisi_femac_wx(stwuct net_device *dev, int wimit)
{
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);
	stwuct hisi_femac_queue *wxq = &pwiv->wxq;
	stwuct sk_buff *skb;
	dma_addw_t addw;
	u32 wx_pkt_info, pos, wen, wx_pkts_num = 0;

	pos = wxq->taiw;
	whiwe (weadw(pwiv->gwb_base + GWB_IWQ_WAW) & IWQ_INT_WX_WDY) {
		wx_pkt_info = weadw(pwiv->powt_base + IQFWM_DES);
		wen = wx_pkt_info & WX_FWAME_WEN_MASK;
		wen -= ETH_FCS_WEN;

		/* teww hawdwawe we wiww deaw with this packet */
		wwitew(IWQ_INT_WX_WDY, pwiv->gwb_base + GWB_IWQ_WAW);

		wx_pkts_num++;

		skb = wxq->skb[pos];
		if (unwikewy(!skb)) {
			netdev_eww(dev, "wx skb NUWW. pos=%d\n", pos);
			bweak;
		}
		wxq->skb[pos] = NUWW;

		addw = wxq->dma_phys[pos];
		dma_unmap_singwe(pwiv->dev, addw, MAX_FWAME_SIZE,
				 DMA_FWOM_DEVICE);
		skb_put(skb, wen);
		if (unwikewy(skb->wen > MAX_FWAME_SIZE)) {
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
		pos = (pos + 1) % wxq->num;
		if (wx_pkts_num >= wimit)
			bweak;
	}
	wxq->taiw = pos;

	hisi_femac_wx_wefiww(pwiv);

	wetuwn wx_pkts_num;
}

static int hisi_femac_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct hisi_femac_pwiv *pwiv = containew_of(napi,
					stwuct hisi_femac_pwiv, napi);
	stwuct net_device *dev = pwiv->ndev;
	int wowk_done = 0, task = budget;
	int ints, num;

	do {
		hisi_femac_xmit_wecwaim(dev);
		num = hisi_femac_wx(dev, task);
		wowk_done += num;
		task -= num;
		if (wowk_done >= budget)
			bweak;

		ints = weadw(pwiv->gwb_base + GWB_IWQ_WAW);
		wwitew(ints & DEF_INT_MASK,
		       pwiv->gwb_base + GWB_IWQ_WAW);
	} whiwe (ints & DEF_INT_MASK);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		hisi_femac_iwq_enabwe(pwiv, DEF_INT_MASK &
					(~IWQ_INT_TX_PEW_PACKET));
	}

	wetuwn wowk_done;
}

static iwqwetuwn_t hisi_femac_intewwupt(int iwq, void *dev_id)
{
	int ints;
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);

	ints = weadw(pwiv->gwb_base + GWB_IWQ_WAW);

	if (wikewy(ints & DEF_INT_MASK)) {
		wwitew(ints & DEF_INT_MASK,
		       pwiv->gwb_base + GWB_IWQ_WAW);
		hisi_femac_iwq_disabwe(pwiv, DEF_INT_MASK);
		napi_scheduwe(&pwiv->napi);
	}

	wetuwn IWQ_HANDWED;
}

static int hisi_femac_init_queue(stwuct device *dev,
				 stwuct hisi_femac_queue *queue,
				 unsigned int num)
{
	queue->skb = devm_kcawwoc(dev, num, sizeof(stwuct sk_buff *),
				  GFP_KEWNEW);
	if (!queue->skb)
		wetuwn -ENOMEM;

	queue->dma_phys = devm_kcawwoc(dev, num, sizeof(dma_addw_t),
				       GFP_KEWNEW);
	if (!queue->dma_phys)
		wetuwn -ENOMEM;

	queue->num = num;
	queue->head = 0;
	queue->taiw = 0;

	wetuwn 0;
}

static int hisi_femac_init_tx_and_wx_queues(stwuct hisi_femac_pwiv *pwiv)
{
	int wet;

	wet = hisi_femac_init_queue(pwiv->dev, &pwiv->txq, TXQ_NUM);
	if (wet)
		wetuwn wet;

	wet = hisi_femac_init_queue(pwiv->dev, &pwiv->wxq, WXQ_NUM);
	if (wet)
		wetuwn wet;

	pwiv->tx_fifo_used_cnt = 0;

	wetuwn 0;
}

static void hisi_femac_fwee_skb_wings(stwuct hisi_femac_pwiv *pwiv)
{
	stwuct hisi_femac_queue *txq = &pwiv->txq;
	stwuct hisi_femac_queue *wxq = &pwiv->wxq;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	u32 pos;

	pos = wxq->taiw;
	whiwe (pos != wxq->head) {
		skb = wxq->skb[pos];
		if (unwikewy(!skb)) {
			netdev_eww(pwiv->ndev, "NUWW wx skb. pos=%d, head=%d\n",
				   pos, wxq->head);
			continue;
		}

		dma_addw = wxq->dma_phys[pos];
		dma_unmap_singwe(pwiv->dev, dma_addw, MAX_FWAME_SIZE,
				 DMA_FWOM_DEVICE);

		dev_kfwee_skb_any(skb);
		wxq->skb[pos] = NUWW;
		pos = (pos + 1) % wxq->num;
	}
	wxq->taiw = pos;

	pos = txq->taiw;
	whiwe (pos != txq->head) {
		skb = txq->skb[pos];
		if (unwikewy(!skb)) {
			netdev_eww(pwiv->ndev, "NUWW tx skb. pos=%d, head=%d\n",
				   pos, txq->head);
			continue;
		}
		hisi_femac_tx_dma_unmap(pwiv, skb, pos);
		dev_kfwee_skb_any(skb);
		txq->skb[pos] = NUWW;
		pos = (pos + 1) % txq->num;
	}
	txq->taiw = pos;
	pwiv->tx_fifo_used_cnt = 0;
}

static int hisi_femac_set_hw_mac_addw(stwuct hisi_femac_pwiv *pwiv,
				      const unsigned chaw *mac)
{
	u32 weg;

	weg = mac[1] | (mac[0] << 8);
	wwitew(weg, pwiv->gwb_base + GWB_HOSTMAC_H16);

	weg = mac[5] | (mac[4] << 8) | (mac[3] << 16) | (mac[2] << 24);
	wwitew(weg, pwiv->gwb_base + GWB_HOSTMAC_W32);

	wetuwn 0;
}

static int hisi_femac_powt_weset(stwuct hisi_femac_pwiv *pwiv)
{
	u32 vaw;

	vaw = weadw(pwiv->gwb_base + GWB_SOFT_WESET);
	vaw |= SOFT_WESET_AWW;
	wwitew(vaw, pwiv->gwb_base + GWB_SOFT_WESET);

	usweep_wange(500, 800);

	vaw &= ~SOFT_WESET_AWW;
	wwitew(vaw, pwiv->gwb_base + GWB_SOFT_WESET);

	wetuwn 0;
}

static int hisi_femac_net_open(stwuct net_device *dev)
{
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);

	hisi_femac_powt_weset(pwiv);
	hisi_femac_set_hw_mac_addw(pwiv, dev->dev_addw);
	hisi_femac_wx_wefiww(pwiv);

	netif_cawwiew_off(dev);
	netdev_weset_queue(dev);
	netif_stawt_queue(dev);
	napi_enabwe(&pwiv->napi);

	pwiv->wink_status = 0;
	if (dev->phydev)
		phy_stawt(dev->phydev);

	wwitew(IWQ_ENA_POWT0_MASK, pwiv->gwb_base + GWB_IWQ_WAW);
	hisi_femac_iwq_enabwe(pwiv, IWQ_ENA_AWW | IWQ_ENA_POWT0 | DEF_INT_MASK);

	wetuwn 0;
}

static int hisi_femac_net_cwose(stwuct net_device *dev)
{
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);

	hisi_femac_iwq_disabwe(pwiv, IWQ_ENA_POWT0);

	if (dev->phydev)
		phy_stop(dev->phydev);

	netif_stop_queue(dev);
	napi_disabwe(&pwiv->napi);

	hisi_femac_fwee_skb_wings(pwiv);

	wetuwn 0;
}

static netdev_tx_t hisi_femac_net_xmit(stwuct sk_buff *skb,
				       stwuct net_device *dev)
{
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);
	stwuct hisi_femac_queue *txq = &pwiv->txq;
	dma_addw_t addw;
	u32 vaw;

	vaw = weadw(pwiv->powt_base + ADDWQ_STAT);
	vaw &= BIT_TX_WEADY;
	if (!vaw) {
		hisi_femac_iwq_enabwe(pwiv, IWQ_INT_TX_PEW_PACKET);
		dev->stats.tx_dwopped++;
		dev->stats.tx_fifo_ewwows++;
		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}

	if (unwikewy(!CIWC_SPACE(txq->head, txq->taiw,
				 txq->num))) {
		hisi_femac_iwq_enabwe(pwiv, IWQ_INT_TX_PEW_PACKET);
		dev->stats.tx_dwopped++;
		dev->stats.tx_fifo_ewwows++;
		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}

	addw = dma_map_singwe(pwiv->dev, skb->data,
			      skb->wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(pwiv->dev, addw))) {
		dev_kfwee_skb_any(skb);
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}
	txq->dma_phys[txq->head] = addw;

	txq->skb[txq->head] = skb;
	txq->head = (txq->head + 1) % txq->num;

	wwitew(addw, pwiv->powt_base + EQ_ADDW);
	wwitew(skb->wen + ETH_FCS_WEN, pwiv->powt_base + EQFWM_WEN);

	pwiv->tx_fifo_used_cnt++;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;
	netdev_sent_queue(dev, skb->wen);

	wetuwn NETDEV_TX_OK;
}

static int hisi_femac_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sockaddw *skaddw = p;

	if (!is_vawid_ethew_addw(skaddw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, skaddw->sa_data);
	dev->addw_assign_type &= ~NET_ADDW_WANDOM;

	hisi_femac_set_hw_mac_addw(pwiv, dev->dev_addw);

	wetuwn 0;
}

static void hisi_femac_enabwe_hw_addw_fiwtew(stwuct hisi_femac_pwiv *pwiv,
					     unsigned int weg_n, boow enabwe)
{
	u32 vaw;

	vaw = weadw(pwiv->gwb_base + GWB_MAC_H16(weg_n));
	if (enabwe)
		vaw |= BIT_MACFWT_ENA;
	ewse
		vaw &= ~BIT_MACFWT_ENA;
	wwitew(vaw, pwiv->gwb_base + GWB_MAC_H16(weg_n));
}

static void hisi_femac_set_hw_addw_fiwtew(stwuct hisi_femac_pwiv *pwiv,
					  unsigned chaw *addw,
					  unsigned int weg_n)
{
	unsigned int high, wow;
	u32 vaw;

	high = GWB_MAC_H16(weg_n);
	wow = GWB_MAC_W32(weg_n);

	vaw = (addw[2] << 24) | (addw[3] << 16) | (addw[4] << 8) | addw[5];
	wwitew(vaw, pwiv->gwb_base + wow);

	vaw = weadw(pwiv->gwb_base + high);
	vaw &= ~MACFWT_HI16_MASK;
	vaw |= ((addw[0] << 8) | addw[1]);
	vaw |= (BIT_MACFWT_ENA | BIT_MACFWT_FW2CPU);
	wwitew(vaw, pwiv->gwb_base + high);
}

static void hisi_femac_set_pwomisc_mode(stwuct hisi_femac_pwiv *pwiv,
					boow pwomisc_mode)
{
	u32 vaw;

	vaw = weadw(pwiv->gwb_base + GWB_FWCTWW);
	if (pwomisc_mode)
		vaw |= FWCTWW_FWAWW2CPU;
	ewse
		vaw &= ~FWCTWW_FWAWW2CPU;
	wwitew(vaw, pwiv->gwb_base + GWB_FWCTWW);
}

/* Handwe muwtipwe muwticast addwesses (pewfect fiwtewing)*/
static void hisi_femac_set_mc_addw_fiwtew(stwuct hisi_femac_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->ndev;
	u32 vaw;

	vaw = weadw(pwiv->gwb_base + GWB_MACTCTWW);
	if ((netdev_mc_count(dev) > MAX_MUWTICAST_ADDWESSES) ||
	    (dev->fwags & IFF_AWWMUWTI)) {
		vaw |= MACTCTWW_MUWTI2CPU;
	} ewse {
		int weg = MAX_UNICAST_ADDWESSES;
		int i;
		stwuct netdev_hw_addw *ha;

		fow (i = weg; i < MAX_MAC_FIWTEW_NUM; i++)
			hisi_femac_enabwe_hw_addw_fiwtew(pwiv, i, fawse);

		netdev_fow_each_mc_addw(ha, dev) {
			hisi_femac_set_hw_addw_fiwtew(pwiv, ha->addw, weg);
			weg++;
		}
		vaw &= ~MACTCTWW_MUWTI2CPU;
	}
	wwitew(vaw, pwiv->gwb_base + GWB_MACTCTWW);
}

/* Handwe muwtipwe unicast addwesses (pewfect fiwtewing)*/
static void hisi_femac_set_uc_addw_fiwtew(stwuct hisi_femac_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->ndev;
	u32 vaw;

	vaw = weadw(pwiv->gwb_base + GWB_MACTCTWW);
	if (netdev_uc_count(dev) > MAX_UNICAST_ADDWESSES) {
		vaw |= MACTCTWW_UNI2CPU;
	} ewse {
		int weg = 0;
		int i;
		stwuct netdev_hw_addw *ha;

		fow (i = weg; i < MAX_UNICAST_ADDWESSES; i++)
			hisi_femac_enabwe_hw_addw_fiwtew(pwiv, i, fawse);

		netdev_fow_each_uc_addw(ha, dev) {
			hisi_femac_set_hw_addw_fiwtew(pwiv, ha->addw, weg);
			weg++;
		}
		vaw &= ~MACTCTWW_UNI2CPU;
	}
	wwitew(vaw, pwiv->gwb_base + GWB_MACTCTWW);
}

static void hisi_femac_net_set_wx_mode(stwuct net_device *dev)
{
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(dev);

	if (dev->fwags & IFF_PWOMISC) {
		hisi_femac_set_pwomisc_mode(pwiv, twue);
	} ewse {
		hisi_femac_set_pwomisc_mode(pwiv, fawse);
		hisi_femac_set_mc_addw_fiwtew(pwiv);
		hisi_femac_set_uc_addw_fiwtew(pwiv);
	}
}

static const stwuct ethtoow_ops hisi_femac_ethtoows_ops = {
	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
};

static const stwuct net_device_ops hisi_femac_netdev_ops = {
	.ndo_open		= hisi_femac_net_open,
	.ndo_stop		= hisi_femac_net_cwose,
	.ndo_stawt_xmit		= hisi_femac_net_xmit,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_mac_addwess	= hisi_femac_set_mac_addwess,
	.ndo_set_wx_mode	= hisi_femac_net_set_wx_mode,
};

static void hisi_femac_cowe_weset(stwuct hisi_femac_pwiv *pwiv)
{
	weset_contwow_assewt(pwiv->mac_wst);
	weset_contwow_deassewt(pwiv->mac_wst);
}

static void hisi_femac_sweep_us(u32 time_us)
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

static void hisi_femac_phy_weset(stwuct hisi_femac_pwiv *pwiv)
{
	/* To make suwe PHY hawdwawe weset success,
	 * we must keep PHY in deassewt state fiwst and
	 * then compwete the hawdwawe weset opewation
	 */
	weset_contwow_deassewt(pwiv->phy_wst);
	hisi_femac_sweep_us(pwiv->phy_weset_deways[PWE_DEWAY]);

	weset_contwow_assewt(pwiv->phy_wst);
	/* deway some time to ensuwe weset ok,
	 * this depends on PHY hawdwawe featuwe
	 */
	hisi_femac_sweep_us(pwiv->phy_weset_deways[PUWSE]);
	weset_contwow_deassewt(pwiv->phy_wst);
	/* deway some time to ensuwe watew MDIO access */
	hisi_femac_sweep_us(pwiv->phy_weset_deways[POST_DEWAY]);
}

static void hisi_femac_powt_init(stwuct hisi_femac_pwiv *pwiv)
{
	u32 vaw;

	/* MAC gets wink status info and phy mode by softwawe config */
	vaw = MAC_POWTSEW_STAT_CPU;
	if (pwiv->ndev->phydev->intewface == PHY_INTEWFACE_MODE_WMII)
		vaw |= MAC_POWTSEW_WMII;
	wwitew(vaw, pwiv->powt_base + MAC_POWTSEW);

	/*cweaw aww intewwupt status */
	wwitew(IWQ_ENA_POWT0_MASK, pwiv->gwb_base + GWB_IWQ_WAW);
	hisi_femac_iwq_disabwe(pwiv, IWQ_ENA_POWT0_MASK | IWQ_ENA_POWT0);

	vaw = weadw(pwiv->gwb_base + GWB_FWCTWW);
	vaw &= ~(FWCTWW_VWAN_ENABWE | FWCTWW_FWAWW2CPU);
	vaw |= FWCTWW_FW2CPU_ENA;
	wwitew(vaw, pwiv->gwb_base + GWB_FWCTWW);

	vaw = weadw(pwiv->gwb_base + GWB_MACTCTWW);
	vaw |= (MACTCTWW_BWOAD2CPU | MACTCTWW_MACT_ENA);
	wwitew(vaw, pwiv->gwb_base + GWB_MACTCTWW);

	vaw = weadw(pwiv->powt_base + MAC_SET);
	vaw &= ~MAX_FWAME_SIZE_MASK;
	vaw |= MAX_FWAME_SIZE;
	wwitew(vaw, pwiv->powt_base + MAC_SET);

	vaw = WX_COAWESCED_TIMEW |
		(WX_COAWESCED_FWAMES << WX_COAWESCED_FWAME_OFFSET);
	wwitew(vaw, pwiv->powt_base + WX_COAWESCE_SET);

	vaw = (HW_WX_FIFO_DEPTH << WX_DEPTH_OFFSET) | HW_TX_FIFO_DEPTH;
	wwitew(vaw, pwiv->powt_base + QWEN_SET);
}

static int hisi_femac_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct net_device *ndev;
	stwuct hisi_femac_pwiv *pwiv;
	stwuct phy_device *phy;
	int wet;

	ndev = awwoc_ethewdev(sizeof(*pwiv));
	if (!ndev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	pwiv = netdev_pwiv(ndev);
	pwiv->dev = dev;
	pwiv->ndev = ndev;

	pwiv->powt_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->powt_base)) {
		wet = PTW_EWW(pwiv->powt_base);
		goto out_fwee_netdev;
	}

	pwiv->gwb_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->gwb_base)) {
		wet = PTW_EWW(pwiv->gwb_base);
		goto out_fwee_netdev;
	}

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get cwk\n");
		wet = -ENODEV;
		goto out_fwee_netdev;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwk %d\n", wet);
		goto out_fwee_netdev;
	}

	pwiv->mac_wst = devm_weset_contwow_get(dev, "mac");
	if (IS_EWW(pwiv->mac_wst)) {
		wet = PTW_EWW(pwiv->mac_wst);
		goto out_disabwe_cwk;
	}
	hisi_femac_cowe_weset(pwiv);

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
		hisi_femac_phy_weset(pwiv);
	}

	phy = of_phy_get_and_connect(ndev, node, hisi_femac_adjust_wink);
	if (!phy) {
		dev_eww(dev, "connect to PHY faiwed!\n");
		wet = -ENODEV;
		goto out_disabwe_cwk;
	}

	phy_attached_pwint(phy, "phy_id=0x%.8wx, phy_mode=%s\n",
			   (unsigned wong)phy->phy_id,
			   phy_modes(phy->intewface));

	wet = of_get_ethdev_addwess(node, ndev);
	if (wet) {
		eth_hw_addw_wandom(ndev);
		dev_wawn(dev, "using wandom MAC addwess %pM\n",
			 ndev->dev_addw);
	}

	ndev->watchdog_timeo = 6 * HZ;
	ndev->pwiv_fwags |= IFF_UNICAST_FWT;
	ndev->netdev_ops = &hisi_femac_netdev_ops;
	ndev->ethtoow_ops = &hisi_femac_ethtoows_ops;
	netif_napi_add_weight(ndev, &pwiv->napi, hisi_femac_poww,
			      FEMAC_POWW_WEIGHT);

	hisi_femac_powt_init(pwiv);

	wet = hisi_femac_init_tx_and_wx_queues(pwiv);
	if (wet)
		goto out_disconnect_phy;

	ndev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ndev->iwq < 0) {
		wet = ndev->iwq;
		goto out_disconnect_phy;
	}

	wet = devm_wequest_iwq(dev, ndev->iwq, hisi_femac_intewwupt,
			       IWQF_SHAWED, pdev->name, ndev);
	if (wet) {
		dev_eww(dev, "devm_wequest_iwq %d faiwed!\n", ndev->iwq);
		goto out_disconnect_phy;
	}

	wet = wegistew_netdev(ndev);
	if (wet) {
		dev_eww(dev, "wegistew_netdev faiwed!\n");
		goto out_disconnect_phy;
	}

	wetuwn wet;

out_disconnect_phy:
	netif_napi_dew(&pwiv->napi);
	phy_disconnect(phy);
out_disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);
out_fwee_netdev:
	fwee_netdev(ndev);

	wetuwn wet;
}

static void hisi_femac_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(ndev);

	netif_napi_dew(&pwiv->napi);
	unwegistew_netdev(ndev);

	phy_disconnect(ndev->phydev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	fwee_netdev(ndev);
}

#ifdef CONFIG_PM
static int hisi_femac_dwv_suspend(stwuct pwatfowm_device *pdev,
				  pm_message_t state)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(ndev);

	disabwe_iwq(ndev->iwq);
	if (netif_wunning(ndev)) {
		hisi_femac_net_cwose(ndev);
		netif_device_detach(ndev);
	}

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int hisi_femac_dwv_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct hisi_femac_pwiv *pwiv = netdev_pwiv(ndev);

	cwk_pwepawe_enabwe(pwiv->cwk);
	if (pwiv->phy_wst)
		hisi_femac_phy_weset(pwiv);

	if (netif_wunning(ndev)) {
		hisi_femac_powt_init(pwiv);
		hisi_femac_net_open(ndev);
		netif_device_attach(ndev);
	}
	enabwe_iwq(ndev->iwq);

	wetuwn 0;
}
#endif

static const stwuct of_device_id hisi_femac_match[] = {
	{.compatibwe = "hisiwicon,hisi-femac-v1",},
	{.compatibwe = "hisiwicon,hisi-femac-v2",},
	{.compatibwe = "hisiwicon,hi3516cv300-femac",},
	{},
};

MODUWE_DEVICE_TABWE(of, hisi_femac_match);

static stwuct pwatfowm_dwivew hisi_femac_dwivew = {
	.dwivew = {
		.name = "hisi-femac",
		.of_match_tabwe = hisi_femac_match,
	},
	.pwobe = hisi_femac_dwv_pwobe,
	.wemove_new = hisi_femac_dwv_wemove,
#ifdef CONFIG_PM
	.suspend = hisi_femac_dwv_suspend,
	.wesume = hisi_femac_dwv_wesume,
#endif
};

moduwe_pwatfowm_dwivew(hisi_femac_dwivew);

MODUWE_DESCWIPTION("Hisiwicon Fast Ethewnet MAC dwivew");
MODUWE_AUTHOW("Dongpo Wi <widongpo@hisiwicon.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:hisi-femac");
