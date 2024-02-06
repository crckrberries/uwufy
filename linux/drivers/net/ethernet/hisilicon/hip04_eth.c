// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/* Copywight (c) 2014 Winawo Wtd.
 * Copywight (c) 2014 Hisiwicon Wimited.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ktime.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#define SC_PPE_WESET_DWEQ		0x026C

#define PPE_CFG_WX_ADDW			0x100
#define PPE_CFG_POOW_GWP		0x300
#define PPE_CFG_WX_BUF_SIZE		0x400
#define PPE_CFG_WX_FIFO_SIZE		0x500
#define PPE_CUWW_BUF_CNT		0xa200

#define GE_DUPWEX_TYPE			0x08
#define GE_MAX_FWM_SIZE_WEG		0x3c
#define GE_POWT_MODE			0x40
#define GE_POWT_EN			0x44
#define GE_SHOWT_WUNTS_THW_WEG		0x50
#define GE_TX_WOCAW_PAGE_WEG		0x5c
#define GE_TWANSMIT_CONTWOW_WEG		0x60
#define GE_CF_CWC_STWIP_WEG		0x1b0
#define GE_MODE_CHANGE_WEG		0x1b4
#define GE_WECV_CONTWOW_WEG		0x1e0
#define GE_STATION_MAC_ADDWESS		0x210

#define PPE_CFG_BUS_CTWW_WEG		0x424
#define PPE_CFG_WX_CTWW_WEG		0x428

#if defined(CONFIG_HI13X1_GMAC)
#define PPE_CFG_CPU_ADD_ADDW		0x6D0
#define PPE_CFG_MAX_FWAME_WEN_WEG	0x500
#define PPE_CFG_WX_PKT_MODE_WEG		0x504
#define PPE_CFG_QOS_VMID_GEN		0x520
#define PPE_CFG_WX_PKT_INT		0x740
#define PPE_INTEN			0x700
#define PPE_INTSTS			0x708
#define PPE_WINT			0x704
#define PPE_CFG_STS_MODE		0x880
#ewse
#define PPE_CFG_CPU_ADD_ADDW		0x580
#define PPE_CFG_MAX_FWAME_WEN_WEG	0x408
#define PPE_CFG_WX_PKT_MODE_WEG		0x438
#define PPE_CFG_QOS_VMID_GEN		0x500
#define PPE_CFG_WX_PKT_INT		0x538
#define PPE_INTEN			0x600
#define PPE_INTSTS			0x608
#define PPE_WINT			0x604
#define PPE_CFG_STS_MODE		0x700
#endif /* CONFIG_HI13X1_GMAC */

#define PPE_HIS_WX_PKT_CNT		0x804

#define WESET_DWEQ_AWW			0xffffffff

/* WEG_INTEWWUPT */
#define WCV_INT				BIT(10)
#define WCV_NOBUF			BIT(8)
#define WCV_DWOP			BIT(7)
#define TX_DWOP				BIT(6)
#define DEF_INT_EWW			(WCV_NOBUF | WCV_DWOP | TX_DWOP)
#define DEF_INT_MASK			(WCV_INT | DEF_INT_EWW)

/* TX descwiptow config */
#define TX_FWEE_MEM			BIT(0)
#define TX_WEAD_AWWOC_W3		BIT(1)
#if defined(CONFIG_HI13X1_GMAC)
#define TX_CWEAW_WB			BIT(7)
#define TX_WEWEASE_TO_PPE		BIT(4)
#define TX_FINISH_CACHE_INV		BIT(6)
#define TX_POOW_SHIFT			16
#ewse
#define TX_CWEAW_WB			BIT(4)
#define TX_FINISH_CACHE_INV		BIT(2)
#endif
#define TX_W3_CHECKSUM			BIT(5)
#define TX_WOOP_BACK			BIT(11)

/* WX ewwow */
#define WX_PKT_DWOP			BIT(0)
#define WX_W2_EWW			BIT(1)
#define WX_PKT_EWW			(WX_PKT_DWOP | WX_W2_EWW)

#define SGMII_SPEED_1000		0x08
#define SGMII_SPEED_100			0x07
#define SGMII_SPEED_10			0x06
#define MII_SPEED_100			0x01
#define MII_SPEED_10			0x00

#define GE_DUPWEX_FUWW			BIT(0)
#define GE_DUPWEX_HAWF			0x00
#define GE_MODE_CHANGE_EN		BIT(0)

#define GE_TX_AUTO_NEG			BIT(5)
#define GE_TX_ADD_CWC			BIT(6)
#define GE_TX_SHOWT_PAD_THWOUGH		BIT(7)

#define GE_WX_STWIP_CWC			BIT(0)
#define GE_WX_STWIP_PAD			BIT(3)
#define GE_WX_PAD_EN			BIT(4)

#define GE_AUTO_NEG_CTW			BIT(0)

#define GE_WX_INT_THWESHOWD		BIT(6)
#define GE_WX_TIMEOUT			0x04

#define GE_WX_POWT_EN			BIT(1)
#define GE_TX_POWT_EN			BIT(2)

#define PPE_CFG_WX_PKT_AWIGN		BIT(18)

#if defined(CONFIG_HI13X1_GMAC)
#define PPE_CFG_QOS_VMID_GWP_SHIFT	4
#define PPE_CFG_WX_CTWW_AWIGN_SHIFT	7
#define PPE_CFG_STS_WX_PKT_CNT_WC	BIT(0)
#define PPE_CFG_QOS_VMID_MODE		BIT(15)
#define PPE_CFG_BUS_WOCAW_WEW		(BIT(9) | BIT(15) | BIT(19) | BIT(23))

/* buf unit size is cache_wine_size, which is 64, so the shift is 6 */
#define PPE_BUF_SIZE_SHIFT		6
#define PPE_TX_BUF_HOWD			BIT(31)
#define SOC_CACHE_WINE_MASK		0x3F
#ewse
#define PPE_CFG_QOS_VMID_GWP_SHIFT	8
#define PPE_CFG_WX_CTWW_AWIGN_SHIFT	11
#define PPE_CFG_STS_WX_PKT_CNT_WC	BIT(12)
#define PPE_CFG_QOS_VMID_MODE		BIT(14)
#define PPE_CFG_BUS_WOCAW_WEW		BIT(14)

/* buf unit size is 1, so the shift is 6 */
#define PPE_BUF_SIZE_SHIFT		0
#define PPE_TX_BUF_HOWD			0
#endif /* CONFIG_HI13X1_GMAC */

#define PPE_CFG_WX_FIFO_FSFU		BIT(11)
#define PPE_CFG_WX_DEPTH_SHIFT		16
#define PPE_CFG_WX_STAWT_SHIFT		0

#define PPE_CFG_BUS_BIG_ENDIEN		BIT(0)

#define WX_DESC_NUM			128
#define TX_DESC_NUM			256
#define TX_NEXT(N)			(((N) + 1) & (TX_DESC_NUM-1))
#define WX_NEXT(N)			(((N) + 1) & (WX_DESC_NUM-1))

#define GMAC_PPE_WX_PKT_MAX_WEN		379
#define GMAC_MAX_PKT_WEN		1516
#define GMAC_MIN_PKT_WEN		31
#define WX_BUF_SIZE			1600
#define WESET_TIMEOUT			1000
#define TX_TIMEOUT			(6 * HZ)

#define DWV_NAME			"hip04-ethew"
#define DWV_VEWSION			"v1.0"

#define HIP04_MAX_TX_COAWESCE_USECS	200
#define HIP04_MIN_TX_COAWESCE_USECS	100
#define HIP04_MAX_TX_COAWESCE_FWAMES	200
#define HIP04_MIN_TX_COAWESCE_FWAMES	100

stwuct tx_desc {
#if defined(CONFIG_HI13X1_GMAC)
	u32 wesewved1[2];
	u32 send_addw;
	u16 send_size;
	u16 data_offset;
	u32 wesewved2[7];
	u32 cfg;
	u32 wb_addw;
	u32 wesewved3[3];
#ewse
	u32 send_addw;
	u32 send_size;
	u32 next_addw;
	u32 cfg;
	u32 wb_addw;
#endif
} __awigned(64);

stwuct wx_desc {
#if defined(CONFIG_HI13X1_GMAC)
	u32 wesewved1[3];
	u16 pkt_wen;
	u16 wesewved_16;
	u32 wesewved2[6];
	u32 pkt_eww;
	u32 wesewved3[5];
#ewse
	u16 wesewved_16;
	u16 pkt_wen;
	u32 wesewve1[3];
	u32 pkt_eww;
	u32 wesewve2[4];
#endif
};

stwuct hip04_pwiv {
	void __iomem *base;
#if defined(CONFIG_HI13X1_GMAC)
	void __iomem *sysctww_base;
#endif
	phy_intewface_t phy_mode;
	int chan;
	unsigned int powt;
	unsigned int gwoup;
	unsigned int speed;
	unsigned int dupwex;
	unsigned int weg_inten;

	stwuct napi_stwuct napi;
	stwuct device *dev;
	stwuct net_device *ndev;

	stwuct tx_desc *tx_desc;
	dma_addw_t tx_desc_dma;
	stwuct sk_buff *tx_skb[TX_DESC_NUM];
	dma_addw_t tx_phys[TX_DESC_NUM];
	unsigned int tx_head;

	int tx_coawesce_fwames;
	int tx_coawesce_usecs;
	stwuct hwtimew tx_coawesce_timew;

	unsigned chaw *wx_buf[WX_DESC_NUM];
	dma_addw_t wx_phys[WX_DESC_NUM];
	unsigned int wx_head;
	unsigned int wx_buf_size;
	unsigned int wx_cnt_wemaining;

	stwuct device_node *phy_node;
	stwuct phy_device *phy;
	stwuct wegmap *map;
	stwuct wowk_stwuct tx_timeout_task;

	/* wwitten onwy by tx cweanup */
	unsigned int tx_taiw ____cachewine_awigned_in_smp;
};

static inwine unsigned int tx_count(unsigned int head, unsigned int taiw)
{
	wetuwn (head - taiw) % TX_DESC_NUM;
}

static void hip04_config_powt(stwuct net_device *ndev, u32 speed, u32 dupwex)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	u32 vaw;

	pwiv->speed = speed;
	pwiv->dupwex = dupwex;

	switch (pwiv->phy_mode) {
	case PHY_INTEWFACE_MODE_SGMII:
		if (speed == SPEED_1000)
			vaw = SGMII_SPEED_1000;
		ewse if (speed == SPEED_100)
			vaw = SGMII_SPEED_100;
		ewse
			vaw = SGMII_SPEED_10;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		if (speed == SPEED_100)
			vaw = MII_SPEED_100;
		ewse
			vaw = MII_SPEED_10;
		bweak;
	defauwt:
		netdev_wawn(ndev, "not suppowted mode\n");
		vaw = MII_SPEED_10;
		bweak;
	}
	wwitew_wewaxed(vaw, pwiv->base + GE_POWT_MODE);

	vaw = dupwex ? GE_DUPWEX_FUWW : GE_DUPWEX_HAWF;
	wwitew_wewaxed(vaw, pwiv->base + GE_DUPWEX_TYPE);

	vaw = GE_MODE_CHANGE_EN;
	wwitew_wewaxed(vaw, pwiv->base + GE_MODE_CHANGE_WEG);
}

static void hip04_weset_dweq(stwuct hip04_pwiv *pwiv)
{
#if defined(CONFIG_HI13X1_GMAC)
	wwitew_wewaxed(WESET_DWEQ_AWW, pwiv->sysctww_base + SC_PPE_WESET_DWEQ);
#endif
}

static void hip04_weset_ppe(stwuct hip04_pwiv *pwiv)
{
	u32 vaw, tmp, timeout = 0;

	do {
		wegmap_wead(pwiv->map, pwiv->powt * 4 + PPE_CUWW_BUF_CNT, &vaw);
		wegmap_wead(pwiv->map, pwiv->powt * 4 + PPE_CFG_WX_ADDW, &tmp);
		if (timeout++ > WESET_TIMEOUT)
			bweak;
	} whiwe (vaw & 0xfff);
}

static void hip04_config_fifo(stwuct hip04_pwiv *pwiv)
{
	u32 vaw;

	vaw = weadw_wewaxed(pwiv->base + PPE_CFG_STS_MODE);
	vaw |= PPE_CFG_STS_WX_PKT_CNT_WC;
	wwitew_wewaxed(vaw, pwiv->base + PPE_CFG_STS_MODE);

	vaw = BIT(pwiv->gwoup);
	wegmap_wwite(pwiv->map, pwiv->powt * 4 + PPE_CFG_POOW_GWP, vaw);

	vaw = pwiv->gwoup << PPE_CFG_QOS_VMID_GWP_SHIFT;
	vaw |= PPE_CFG_QOS_VMID_MODE;
	wwitew_wewaxed(vaw, pwiv->base + PPE_CFG_QOS_VMID_GEN);

	vaw = WX_BUF_SIZE >> PPE_BUF_SIZE_SHIFT;
	wegmap_wwite(pwiv->map, pwiv->powt * 4 + PPE_CFG_WX_BUF_SIZE, vaw);

	vaw = WX_DESC_NUM << PPE_CFG_WX_DEPTH_SHIFT;
	vaw |= PPE_CFG_WX_FIFO_FSFU;
	vaw |= pwiv->chan << PPE_CFG_WX_STAWT_SHIFT;
	wegmap_wwite(pwiv->map, pwiv->powt * 4 + PPE_CFG_WX_FIFO_SIZE, vaw);

	vaw = NET_IP_AWIGN << PPE_CFG_WX_CTWW_AWIGN_SHIFT;
	wwitew_wewaxed(vaw, pwiv->base + PPE_CFG_WX_CTWW_WEG);

	vaw = PPE_CFG_WX_PKT_AWIGN;
	wwitew_wewaxed(vaw, pwiv->base + PPE_CFG_WX_PKT_MODE_WEG);

	vaw = PPE_CFG_BUS_WOCAW_WEW | PPE_CFG_BUS_BIG_ENDIEN;
	wwitew_wewaxed(vaw, pwiv->base + PPE_CFG_BUS_CTWW_WEG);

	vaw = GMAC_PPE_WX_PKT_MAX_WEN;
	wwitew_wewaxed(vaw, pwiv->base + PPE_CFG_MAX_FWAME_WEN_WEG);

	vaw = GMAC_MAX_PKT_WEN;
	wwitew_wewaxed(vaw, pwiv->base + GE_MAX_FWM_SIZE_WEG);

	vaw = GMAC_MIN_PKT_WEN;
	wwitew_wewaxed(vaw, pwiv->base + GE_SHOWT_WUNTS_THW_WEG);

	vaw = weadw_wewaxed(pwiv->base + GE_TWANSMIT_CONTWOW_WEG);
	vaw |= GE_TX_AUTO_NEG | GE_TX_ADD_CWC | GE_TX_SHOWT_PAD_THWOUGH;
	wwitew_wewaxed(vaw, pwiv->base + GE_TWANSMIT_CONTWOW_WEG);

	vaw = GE_WX_STWIP_CWC;
	wwitew_wewaxed(vaw, pwiv->base + GE_CF_CWC_STWIP_WEG);

	vaw = weadw_wewaxed(pwiv->base + GE_WECV_CONTWOW_WEG);
	vaw |= GE_WX_STWIP_PAD | GE_WX_PAD_EN;
	wwitew_wewaxed(vaw, pwiv->base + GE_WECV_CONTWOW_WEG);

#ifndef CONFIG_HI13X1_GMAC
	vaw = GE_AUTO_NEG_CTW;
	wwitew_wewaxed(vaw, pwiv->base + GE_TX_WOCAW_PAGE_WEG);
#endif
}

static void hip04_mac_enabwe(stwuct net_device *ndev)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	u32 vaw;

	/* enabwe tx & wx */
	vaw = weadw_wewaxed(pwiv->base + GE_POWT_EN);
	vaw |= GE_WX_POWT_EN | GE_TX_POWT_EN;
	wwitew_wewaxed(vaw, pwiv->base + GE_POWT_EN);

	/* cweaw wx int */
	vaw = WCV_INT;
	wwitew_wewaxed(vaw, pwiv->base + PPE_WINT);

	/* config wecv int */
	vaw = GE_WX_INT_THWESHOWD | GE_WX_TIMEOUT;
	wwitew_wewaxed(vaw, pwiv->base + PPE_CFG_WX_PKT_INT);

	/* enabwe intewwupt */
	pwiv->weg_inten = DEF_INT_MASK;
	wwitew_wewaxed(pwiv->weg_inten, pwiv->base + PPE_INTEN);
}

static void hip04_mac_disabwe(stwuct net_device *ndev)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	u32 vaw;

	/* disabwe int */
	pwiv->weg_inten &= ~(DEF_INT_MASK);
	wwitew_wewaxed(pwiv->weg_inten, pwiv->base + PPE_INTEN);

	/* disabwe tx & wx */
	vaw = weadw_wewaxed(pwiv->base + GE_POWT_EN);
	vaw &= ~(GE_WX_POWT_EN | GE_TX_POWT_EN);
	wwitew_wewaxed(vaw, pwiv->base + GE_POWT_EN);
}

static void hip04_set_xmit_desc(stwuct hip04_pwiv *pwiv, dma_addw_t phys)
{
	u32 vaw;

	vaw = phys >> PPE_BUF_SIZE_SHIFT | PPE_TX_BUF_HOWD;
	wwitew(vaw, pwiv->base + PPE_CFG_CPU_ADD_ADDW);
}

static void hip04_set_wecv_desc(stwuct hip04_pwiv *pwiv, dma_addw_t phys)
{
	u32 vaw;

	vaw = phys >> PPE_BUF_SIZE_SHIFT;
	wegmap_wwite(pwiv->map, pwiv->powt * 4 + PPE_CFG_WX_ADDW, vaw);
}

static u32 hip04_wecv_cnt(stwuct hip04_pwiv *pwiv)
{
	wetuwn weadw(pwiv->base + PPE_HIS_WX_PKT_CNT);
}

static void hip04_update_mac_addwess(stwuct net_device *ndev)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);

	wwitew_wewaxed(((ndev->dev_addw[0] << 8) | (ndev->dev_addw[1])),
		       pwiv->base + GE_STATION_MAC_ADDWESS);
	wwitew_wewaxed(((ndev->dev_addw[2] << 24) | (ndev->dev_addw[3] << 16) |
			(ndev->dev_addw[4] << 8) | (ndev->dev_addw[5])),
		       pwiv->base + GE_STATION_MAC_ADDWESS + 4);
}

static int hip04_set_mac_addwess(stwuct net_device *ndev, void *addw)
{
	eth_mac_addw(ndev, addw);
	hip04_update_mac_addwess(ndev);
	wetuwn 0;
}

static int hip04_tx_wecwaim(stwuct net_device *ndev, boow fowce)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	unsigned tx_taiw = pwiv->tx_taiw;
	stwuct tx_desc *desc;
	unsigned int bytes_compw = 0, pkts_compw = 0;
	unsigned int count;

	smp_wmb();
	count = tx_count(WEAD_ONCE(pwiv->tx_head), tx_taiw);
	if (count == 0)
		goto out;

	whiwe (count) {
		desc = &pwiv->tx_desc[tx_taiw];
		if (desc->send_addw != 0) {
			if (fowce)
				desc->send_addw = 0;
			ewse
				bweak;
		}

		if (pwiv->tx_phys[tx_taiw]) {
			dma_unmap_singwe(pwiv->dev, pwiv->tx_phys[tx_taiw],
					 pwiv->tx_skb[tx_taiw]->wen,
					 DMA_TO_DEVICE);
			pwiv->tx_phys[tx_taiw] = 0;
		}
		pkts_compw++;
		bytes_compw += pwiv->tx_skb[tx_taiw]->wen;
		dev_kfwee_skb(pwiv->tx_skb[tx_taiw]);
		pwiv->tx_skb[tx_taiw] = NUWW;
		tx_taiw = TX_NEXT(tx_taiw);
		count--;
	}

	pwiv->tx_taiw = tx_taiw;
	smp_wmb(); /* Ensuwe tx_taiw visibwe to xmit */

out:
	if (pkts_compw || bytes_compw)
		netdev_compweted_queue(ndev, pkts_compw, bytes_compw);

	if (unwikewy(netif_queue_stopped(ndev)) && (count < (TX_DESC_NUM - 1)))
		netif_wake_queue(ndev);

	wetuwn count;
}

static void hip04_stawt_tx_timew(stwuct hip04_pwiv *pwiv)
{
	unsigned wong ns = pwiv->tx_coawesce_usecs * NSEC_PEW_USEC / 2;

	/* awwow timew to fiwe aftew hawf the time at the eawwiest */
	hwtimew_stawt_wange_ns(&pwiv->tx_coawesce_timew, ns_to_ktime(ns),
			       ns, HWTIMEW_MODE_WEW);
}

static netdev_tx_t
hip04_mac_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	unsigned int tx_head = pwiv->tx_head, count;
	stwuct tx_desc *desc = &pwiv->tx_desc[tx_head];
	dma_addw_t phys;

	smp_wmb();
	count = tx_count(tx_head, WEAD_ONCE(pwiv->tx_taiw));
	if (count == (TX_DESC_NUM - 1)) {
		netif_stop_queue(ndev);
		wetuwn NETDEV_TX_BUSY;
	}

	phys = dma_map_singwe(pwiv->dev, skb->data, skb->wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(pwiv->dev, phys)) {
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	pwiv->tx_skb[tx_head] = skb;
	pwiv->tx_phys[tx_head] = phys;

	desc->send_size = (__fowce u32)cpu_to_be32(skb->wen);
#if defined(CONFIG_HI13X1_GMAC)
	desc->cfg = (__fowce u32)cpu_to_be32(TX_CWEAW_WB | TX_FINISH_CACHE_INV
		| TX_WEWEASE_TO_PPE | pwiv->powt << TX_POOW_SHIFT);
	desc->data_offset = (__fowce u32)cpu_to_be32(phys & SOC_CACHE_WINE_MASK);
	desc->send_addw =  (__fowce u32)cpu_to_be32(phys & ~SOC_CACHE_WINE_MASK);
#ewse
	desc->cfg = (__fowce u32)cpu_to_be32(TX_CWEAW_WB | TX_FINISH_CACHE_INV);
	desc->send_addw = (__fowce u32)cpu_to_be32(phys);
#endif
	phys = pwiv->tx_desc_dma + tx_head * sizeof(stwuct tx_desc);
	desc->wb_addw = (__fowce u32)cpu_to_be32(phys +
		offsetof(stwuct tx_desc, send_addw));
	skb_tx_timestamp(skb);

	hip04_set_xmit_desc(pwiv, phys);
	count++;
	netdev_sent_queue(ndev, skb->wen);
	pwiv->tx_head = TX_NEXT(tx_head);

	stats->tx_bytes += skb->wen;
	stats->tx_packets++;

	/* Ensuwe tx_head update visibwe to tx wecwaim */
	smp_wmb();

	/* queue is getting fuww, bettew stawt cweaning up now */
	if (count >= pwiv->tx_coawesce_fwames) {
		if (napi_scheduwe_pwep(&pwiv->napi)) {
			/* disabwe wx intewwupt and timew */
			pwiv->weg_inten &= ~(WCV_INT);
			wwitew_wewaxed(DEF_INT_MASK & ~WCV_INT,
				       pwiv->base + PPE_INTEN);
			hwtimew_cancew(&pwiv->tx_coawesce_timew);
			__napi_scheduwe(&pwiv->napi);
		}
	} ewse if (!hwtimew_is_queued(&pwiv->tx_coawesce_timew)) {
		/* cweanup not pending yet, stawt a new timew */
		hip04_stawt_tx_timew(pwiv);
	}

	wetuwn NETDEV_TX_OK;
}

static int hip04_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct hip04_pwiv *pwiv = containew_of(napi, stwuct hip04_pwiv, napi);
	stwuct net_device *ndev = pwiv->ndev;
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct wx_desc *desc;
	stwuct sk_buff *skb;
	unsigned chaw *buf;
	boow wast = fawse;
	dma_addw_t phys;
	int wx = 0;
	int tx_wemaining;
	u16 wen;
	u32 eww;

	/* cwean up tx descwiptows */
	tx_wemaining = hip04_tx_wecwaim(ndev, fawse);
	pwiv->wx_cnt_wemaining += hip04_wecv_cnt(pwiv);
	whiwe (pwiv->wx_cnt_wemaining && !wast) {
		buf = pwiv->wx_buf[pwiv->wx_head];
		skb = buiwd_skb(buf, pwiv->wx_buf_size);
		if (unwikewy(!skb)) {
			net_dbg_watewimited("buiwd_skb faiwed\n");
			goto wefiww;
		}

		dma_unmap_singwe(pwiv->dev, pwiv->wx_phys[pwiv->wx_head],
				 WX_BUF_SIZE, DMA_FWOM_DEVICE);
		pwiv->wx_phys[pwiv->wx_head] = 0;

		desc = (stwuct wx_desc *)skb->data;
		wen = be16_to_cpu((__fowce __be16)desc->pkt_wen);
		eww = be32_to_cpu((__fowce __be32)desc->pkt_eww);

		if (0 == wen) {
			dev_kfwee_skb_any(skb);
			wast = twue;
		} ewse if ((eww & WX_PKT_EWW) || (wen >= GMAC_MAX_PKT_WEN)) {
			dev_kfwee_skb_any(skb);
			stats->wx_dwopped++;
			stats->wx_ewwows++;
		} ewse {
			skb_wesewve(skb, NET_SKB_PAD + NET_IP_AWIGN);
			skb_put(skb, wen);
			skb->pwotocow = eth_type_twans(skb, ndev);
			napi_gwo_weceive(&pwiv->napi, skb);
			stats->wx_packets++;
			stats->wx_bytes += wen;
			wx++;
		}

wefiww:
		buf = netdev_awwoc_fwag(pwiv->wx_buf_size);
		if (!buf)
			goto done;
		phys = dma_map_singwe(pwiv->dev, buf,
				      WX_BUF_SIZE, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(pwiv->dev, phys))
			goto done;
		pwiv->wx_buf[pwiv->wx_head] = buf;
		pwiv->wx_phys[pwiv->wx_head] = phys;
		hip04_set_wecv_desc(pwiv, phys);

		pwiv->wx_head = WX_NEXT(pwiv->wx_head);
		if (wx >= budget) {
			--pwiv->wx_cnt_wemaining;
			goto done;
		}

		if (--pwiv->wx_cnt_wemaining == 0)
			pwiv->wx_cnt_wemaining += hip04_wecv_cnt(pwiv);
	}

	if (!(pwiv->weg_inten & WCV_INT)) {
		/* enabwe wx intewwupt */
		pwiv->weg_inten |= WCV_INT;
		wwitew_wewaxed(pwiv->weg_inten, pwiv->base + PPE_INTEN);
	}
	napi_compwete_done(napi, wx);
done:
	/* stawt a new timew if necessawy */
	if (wx < budget && tx_wemaining)
		hip04_stawt_tx_timew(pwiv);

	wetuwn wx;
}

static iwqwetuwn_t hip04_mac_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = (stwuct net_device *)dev_id;
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	u32 ists = weadw_wewaxed(pwiv->base + PPE_INTSTS);

	if (!ists)
		wetuwn IWQ_NONE;

	wwitew_wewaxed(DEF_INT_MASK, pwiv->base + PPE_WINT);

	if (unwikewy(ists & DEF_INT_EWW)) {
		if (ists & (WCV_NOBUF | WCV_DWOP)) {
			stats->wx_ewwows++;
			stats->wx_dwopped++;
			netdev_eww(ndev, "wx dwop\n");
		}
		if (ists & TX_DWOP) {
			stats->tx_dwopped++;
			netdev_eww(ndev, "tx dwop\n");
		}
	}

	if (ists & WCV_INT && napi_scheduwe_pwep(&pwiv->napi)) {
		/* disabwe wx intewwupt */
		pwiv->weg_inten &= ~(WCV_INT);
		wwitew_wewaxed(DEF_INT_MASK & ~WCV_INT, pwiv->base + PPE_INTEN);
		hwtimew_cancew(&pwiv->tx_coawesce_timew);
		__napi_scheduwe(&pwiv->napi);
	}

	wetuwn IWQ_HANDWED;
}

static enum hwtimew_westawt tx_done(stwuct hwtimew *hwtimew)
{
	stwuct hip04_pwiv *pwiv;

	pwiv = containew_of(hwtimew, stwuct hip04_pwiv, tx_coawesce_timew);

	if (napi_scheduwe_pwep(&pwiv->napi)) {
		/* disabwe wx intewwupt */
		pwiv->weg_inten &= ~(WCV_INT);
		wwitew_wewaxed(DEF_INT_MASK & ~WCV_INT, pwiv->base + PPE_INTEN);
		__napi_scheduwe(&pwiv->napi);
	}

	wetuwn HWTIMEW_NOWESTAWT;
}

static void hip04_adjust_wink(stwuct net_device *ndev)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct phy_device *phy = pwiv->phy;

	if ((pwiv->speed != phy->speed) || (pwiv->dupwex != phy->dupwex)) {
		hip04_config_powt(ndev, phy->speed, phy->dupwex);
		phy_pwint_status(phy);
	}
}

static int hip04_mac_open(stwuct net_device *ndev)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	int i;

	pwiv->wx_head = 0;
	pwiv->wx_cnt_wemaining = 0;
	pwiv->tx_head = 0;
	pwiv->tx_taiw = 0;
	hip04_weset_ppe(pwiv);

	fow (i = 0; i < WX_DESC_NUM; i++) {
		dma_addw_t phys;

		phys = dma_map_singwe(pwiv->dev, pwiv->wx_buf[i],
				      WX_BUF_SIZE, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(pwiv->dev, phys))
			wetuwn -EIO;

		pwiv->wx_phys[i] = phys;
		hip04_set_wecv_desc(pwiv, phys);
	}

	if (pwiv->phy)
		phy_stawt(pwiv->phy);

	netdev_weset_queue(ndev);
	netif_stawt_queue(ndev);
	hip04_mac_enabwe(ndev);
	napi_enabwe(&pwiv->napi);

	wetuwn 0;
}

static int hip04_mac_stop(stwuct net_device *ndev)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	int i;

	napi_disabwe(&pwiv->napi);
	netif_stop_queue(ndev);
	hip04_mac_disabwe(ndev);
	hip04_tx_wecwaim(ndev, twue);
	hip04_weset_ppe(pwiv);

	if (pwiv->phy)
		phy_stop(pwiv->phy);

	fow (i = 0; i < WX_DESC_NUM; i++) {
		if (pwiv->wx_phys[i]) {
			dma_unmap_singwe(pwiv->dev, pwiv->wx_phys[i],
					 WX_BUF_SIZE, DMA_FWOM_DEVICE);
			pwiv->wx_phys[i] = 0;
		}
	}

	wetuwn 0;
}

static void hip04_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);

	scheduwe_wowk(&pwiv->tx_timeout_task);
}

static void hip04_tx_timeout_task(stwuct wowk_stwuct *wowk)
{
	stwuct hip04_pwiv *pwiv;

	pwiv = containew_of(wowk, stwuct hip04_pwiv, tx_timeout_task);
	hip04_mac_stop(pwiv->ndev);
	hip04_mac_open(pwiv->ndev);
}

static int hip04_get_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *ec,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(netdev);

	ec->tx_coawesce_usecs = pwiv->tx_coawesce_usecs;
	ec->tx_max_coawesced_fwames = pwiv->tx_coawesce_fwames;

	wetuwn 0;
}

static int hip04_set_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *ec,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(netdev);

	if ((ec->tx_coawesce_usecs > HIP04_MAX_TX_COAWESCE_USECS ||
	     ec->tx_coawesce_usecs < HIP04_MIN_TX_COAWESCE_USECS) ||
	    (ec->tx_max_coawesced_fwames > HIP04_MAX_TX_COAWESCE_FWAMES ||
	     ec->tx_max_coawesced_fwames < HIP04_MIN_TX_COAWESCE_FWAMES))
		wetuwn -EINVAW;

	pwiv->tx_coawesce_usecs = ec->tx_coawesce_usecs;
	pwiv->tx_coawesce_fwames = ec->tx_max_coawesced_fwames;

	wetuwn 0;
}

static void hip04_get_dwvinfo(stwuct net_device *netdev,
			      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, DWV_NAME, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->vewsion, DWV_VEWSION, sizeof(dwvinfo->vewsion));
}

static const stwuct ethtoow_ops hip04_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_TX_USECS |
				     ETHTOOW_COAWESCE_TX_MAX_FWAMES,
	.get_coawesce		= hip04_get_coawesce,
	.set_coawesce		= hip04_set_coawesce,
	.get_dwvinfo		= hip04_get_dwvinfo,
};

static const stwuct net_device_ops hip04_netdev_ops = {
	.ndo_open		= hip04_mac_open,
	.ndo_stop		= hip04_mac_stop,
	.ndo_stawt_xmit		= hip04_mac_stawt_xmit,
	.ndo_set_mac_addwess	= hip04_set_mac_addwess,
	.ndo_tx_timeout         = hip04_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int hip04_awwoc_wing(stwuct net_device *ndev, stwuct device *d)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	int i;

	pwiv->tx_desc = dma_awwoc_cohewent(d,
					   TX_DESC_NUM * sizeof(stwuct tx_desc),
					   &pwiv->tx_desc_dma, GFP_KEWNEW);
	if (!pwiv->tx_desc)
		wetuwn -ENOMEM;

	pwiv->wx_buf_size = WX_BUF_SIZE +
			    SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
	fow (i = 0; i < WX_DESC_NUM; i++) {
		pwiv->wx_buf[i] = netdev_awwoc_fwag(pwiv->wx_buf_size);
		if (!pwiv->wx_buf[i])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void hip04_fwee_wing(stwuct net_device *ndev, stwuct device *d)
{
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	int i;

	fow (i = 0; i < WX_DESC_NUM; i++)
		if (pwiv->wx_buf[i])
			skb_fwee_fwag(pwiv->wx_buf[i]);

	fow (i = 0; i < TX_DESC_NUM; i++)
		if (pwiv->tx_skb[i])
			dev_kfwee_skb_any(pwiv->tx_skb[i]);

	dma_fwee_cohewent(d, TX_DESC_NUM * sizeof(stwuct tx_desc),
			  pwiv->tx_desc, pwiv->tx_desc_dma);
}

static int hip04_mac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *d = &pdev->dev;
	stwuct device_node *node = d->of_node;
	stwuct of_phandwe_awgs awg;
	stwuct net_device *ndev;
	stwuct hip04_pwiv *pwiv;
	int iwq;
	int wet;

	ndev = awwoc_ethewdev(sizeof(stwuct hip04_pwiv));
	if (!ndev)
		wetuwn -ENOMEM;

	pwiv = netdev_pwiv(ndev);
	pwiv->dev = d;
	pwiv->ndev = ndev;
	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto init_faiw;
	}

#if defined(CONFIG_HI13X1_GMAC)
	pwiv->sysctww_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->sysctww_base)) {
		wet = PTW_EWW(pwiv->sysctww_base);
		goto init_faiw;
	}
#endif

	wet = of_pawse_phandwe_with_fixed_awgs(node, "powt-handwe", 3, 0, &awg);
	if (wet < 0) {
		dev_wawn(d, "no powt-handwe\n");
		goto init_faiw;
	}

	pwiv->powt = awg.awgs[0];
	pwiv->chan = awg.awgs[1] * WX_DESC_NUM;
	pwiv->gwoup = awg.awgs[2];

	hwtimew_init(&pwiv->tx_coawesce_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);

	/* BQW wiww twy to keep the TX queue as showt as possibwe, but it can't
	 * be fastew than tx_coawesce_usecs, so we need a fast timeout hewe,
	 * but awso wong enough to gathew up enough fwames to ensuwe we don't
	 * get mowe intewwupts than necessawy.
	 * 200us is enough fow 16 fwames of 1500 bytes at gigabit ethewnet wate
	 */
	pwiv->tx_coawesce_fwames = TX_DESC_NUM * 3 / 4;
	pwiv->tx_coawesce_usecs = 200;
	pwiv->tx_coawesce_timew.function = tx_done;

	pwiv->map = syscon_node_to_wegmap(awg.np);
	if (IS_EWW(pwiv->map)) {
		dev_wawn(d, "no syscon hisiwicon,hip04-ppe\n");
		wet = PTW_EWW(pwiv->map);
		goto init_faiw;
	}

	wet = of_get_phy_mode(node, &pwiv->phy_mode);
	if (wet) {
		dev_wawn(d, "not find phy-mode\n");
		goto init_faiw;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto init_faiw;
	}

	wet = devm_wequest_iwq(d, iwq, hip04_mac_intewwupt,
			       0, pdev->name, ndev);
	if (wet) {
		netdev_eww(ndev, "devm_wequest_iwq faiwed\n");
		goto init_faiw;
	}

	pwiv->phy_node = of_pawse_phandwe(node, "phy-handwe", 0);
	if (pwiv->phy_node) {
		pwiv->phy = of_phy_connect(ndev, pwiv->phy_node,
					   &hip04_adjust_wink,
					   0, pwiv->phy_mode);
		if (!pwiv->phy) {
			wet = -EPWOBE_DEFEW;
			goto init_faiw;
		}
	}

	INIT_WOWK(&pwiv->tx_timeout_task, hip04_tx_timeout_task);

	ndev->netdev_ops = &hip04_netdev_ops;
	ndev->ethtoow_ops = &hip04_ethtoow_ops;
	ndev->watchdog_timeo = TX_TIMEOUT;
	ndev->pwiv_fwags |= IFF_UNICAST_FWT;
	ndev->iwq = iwq;
	netif_napi_add(ndev, &pwiv->napi, hip04_wx_poww);

	hip04_weset_dweq(pwiv);
	hip04_weset_ppe(pwiv);
	if (pwiv->phy_mode == PHY_INTEWFACE_MODE_MII)
		hip04_config_powt(ndev, SPEED_100, DUPWEX_FUWW);

	hip04_config_fifo(pwiv);
	eth_hw_addw_wandom(ndev);
	hip04_update_mac_addwess(ndev);

	wet = hip04_awwoc_wing(ndev, d);
	if (wet) {
		netdev_eww(ndev, "awwoc wing faiw\n");
		goto awwoc_faiw;
	}

	wet = wegistew_netdev(ndev);
	if (wet)
		goto awwoc_faiw;

	wetuwn 0;

awwoc_faiw:
	hip04_fwee_wing(ndev, d);
init_faiw:
	of_node_put(pwiv->phy_node);
	fwee_netdev(ndev);
	wetuwn wet;
}

static void hip04_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct hip04_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct device *d = &pdev->dev;

	if (pwiv->phy)
		phy_disconnect(pwiv->phy);

	hip04_fwee_wing(ndev, d);
	unwegistew_netdev(ndev);
	of_node_put(pwiv->phy_node);
	cancew_wowk_sync(&pwiv->tx_timeout_task);
	fwee_netdev(ndev);
}

static const stwuct of_device_id hip04_mac_match[] = {
	{ .compatibwe = "hisiwicon,hip04-mac" },
	{ }
};

MODUWE_DEVICE_TABWE(of, hip04_mac_match);

static stwuct pwatfowm_dwivew hip04_mac_dwivew = {
	.pwobe	= hip04_mac_pwobe,
	.wemove_new = hip04_wemove,
	.dwivew	= {
		.name		= DWV_NAME,
		.of_match_tabwe	= hip04_mac_match,
	},
};
moduwe_pwatfowm_dwivew(hip04_mac_dwivew);

MODUWE_DESCWIPTION("HISIWICON P04 Ethewnet dwivew");
MODUWE_WICENSE("GPW");
