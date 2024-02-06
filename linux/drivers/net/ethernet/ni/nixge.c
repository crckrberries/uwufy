// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2016-2017, Nationaw Instwuments Cowp.
 *
 * Authow: Mowitz Fischew <mdf@kewnew.owg>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/skbuff.h>
#incwude <winux/phy.h>
#incwude <winux/mii.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/ethtoow.h>
#incwude <winux/iopoww.h>

#define TX_BD_NUM		64
#define WX_BD_NUM		128

/* Axi DMA Wegistew definitions */
#define XAXIDMA_TX_CW_OFFSET	0x00 /* Channew contwow */
#define XAXIDMA_TX_SW_OFFSET	0x04 /* Status */
#define XAXIDMA_TX_CDESC_OFFSET	0x08 /* Cuwwent descwiptow pointew */
#define XAXIDMA_TX_TDESC_OFFSET	0x10 /* Taiw descwiptow pointew */

#define XAXIDMA_WX_CW_OFFSET	0x30 /* Channew contwow */
#define XAXIDMA_WX_SW_OFFSET	0x34 /* Status */
#define XAXIDMA_WX_CDESC_OFFSET	0x38 /* Cuwwent descwiptow pointew */
#define XAXIDMA_WX_TDESC_OFFSET	0x40 /* Taiw descwiptow pointew */

#define XAXIDMA_CW_WUNSTOP_MASK	0x1 /* Stawt/stop DMA channew */
#define XAXIDMA_CW_WESET_MASK	0x4 /* Weset DMA engine */

#define XAXIDMA_BD_CTWW_WENGTH_MASK	0x007FFFFF /* Wequested wen */
#define XAXIDMA_BD_CTWW_TXSOF_MASK	0x08000000 /* Fiwst tx packet */
#define XAXIDMA_BD_CTWW_TXEOF_MASK	0x04000000 /* Wast tx packet */
#define XAXIDMA_BD_CTWW_AWW_MASK	0x0C000000 /* Aww contwow bits */

#define XAXIDMA_DEWAY_MASK		0xFF000000 /* Deway timeout countew */
#define XAXIDMA_COAWESCE_MASK		0x00FF0000 /* Coawesce countew */

#define XAXIDMA_DEWAY_SHIFT		24
#define XAXIDMA_COAWESCE_SHIFT		16

#define XAXIDMA_IWQ_IOC_MASK		0x00001000 /* Compwetion intw */
#define XAXIDMA_IWQ_DEWAY_MASK		0x00002000 /* Deway intewwupt */
#define XAXIDMA_IWQ_EWWOW_MASK		0x00004000 /* Ewwow intewwupt */
#define XAXIDMA_IWQ_AWW_MASK		0x00007000 /* Aww intewwupts */

/* Defauwt TX/WX Thweshowd and waitbound vawues fow SGDMA mode */
#define XAXIDMA_DFT_TX_THWESHOWD	24
#define XAXIDMA_DFT_TX_WAITBOUND	254
#define XAXIDMA_DFT_WX_THWESHOWD	24
#define XAXIDMA_DFT_WX_WAITBOUND	254

#define XAXIDMA_BD_STS_ACTUAW_WEN_MASK	0x007FFFFF /* Actuaw wen */
#define XAXIDMA_BD_STS_COMPWETE_MASK	0x80000000 /* Compweted */
#define XAXIDMA_BD_STS_DEC_EWW_MASK	0x40000000 /* Decode ewwow */
#define XAXIDMA_BD_STS_SWV_EWW_MASK	0x20000000 /* Swave ewwow */
#define XAXIDMA_BD_STS_INT_EWW_MASK	0x10000000 /* Intewnaw eww */
#define XAXIDMA_BD_STS_AWW_EWW_MASK	0x70000000 /* Aww ewwows */
#define XAXIDMA_BD_STS_WXSOF_MASK	0x08000000 /* Fiwst wx pkt */
#define XAXIDMA_BD_STS_WXEOF_MASK	0x04000000 /* Wast wx pkt */
#define XAXIDMA_BD_STS_AWW_MASK		0xFC000000 /* Aww status bits */

#define NIXGE_WEG_CTWW_OFFSET	0x4000
#define NIXGE_WEG_INFO		0x00
#define NIXGE_WEG_MAC_CTW	0x04
#define NIXGE_WEG_PHY_CTW	0x08
#define NIXGE_WEG_WED_CTW	0x0c
#define NIXGE_WEG_MDIO_DATA	0x10
#define NIXGE_WEG_MDIO_ADDW	0x14
#define NIXGE_WEG_MDIO_OP	0x18
#define NIXGE_WEG_MDIO_CTWW	0x1c

#define NIXGE_ID_WED_CTW_EN	BIT(0)
#define NIXGE_ID_WED_CTW_VAW	BIT(1)

#define NIXGE_MDIO_CWAUSE45	BIT(12)
#define NIXGE_MDIO_CWAUSE22	0
#define NIXGE_MDIO_OP(n)     (((n) & 0x3) << 10)
#define NIXGE_MDIO_OP_ADDWESS	0
#define NIXGE_MDIO_C45_WWITE	BIT(0)
#define NIXGE_MDIO_C45_WEAD	(BIT(1) | BIT(0))
#define NIXGE_MDIO_C22_WWITE	BIT(0)
#define NIXGE_MDIO_C22_WEAD	BIT(1)
#define NIXGE_MDIO_ADDW(n)   (((n) & 0x1f) << 5)
#define NIXGE_MDIO_MMD(n)    (((n) & 0x1f) << 0)

#define NIXGE_WEG_MAC_WSB	0x1000
#define NIXGE_WEG_MAC_MSB	0x1004

/* Packet size info */
#define NIXGE_HDW_SIZE		14 /* Size of Ethewnet headew */
#define NIXGE_TWW_SIZE		4 /* Size of Ethewnet twaiwew (FCS) */
#define NIXGE_MTU		1500 /* Max MTU of an Ethewnet fwame */
#define NIXGE_JUMBO_MTU		9000 /* Max MTU of a jumbo Eth. fwame */

#define NIXGE_MAX_FWAME_SIZE	 (NIXGE_MTU + NIXGE_HDW_SIZE + NIXGE_TWW_SIZE)
#define NIXGE_MAX_JUMBO_FWAME_SIZE \
	(NIXGE_JUMBO_MTU + NIXGE_HDW_SIZE + NIXGE_TWW_SIZE)

enum nixge_vewsion {
	NIXGE_V2,
	NIXGE_V3,
	NIXGE_VEWSION_COUNT
};

stwuct nixge_hw_dma_bd {
	u32 next_wo;
	u32 next_hi;
	u32 phys_wo;
	u32 phys_hi;
	u32 wesewved3;
	u32 wesewved4;
	u32 cntww;
	u32 status;
	u32 app0;
	u32 app1;
	u32 app2;
	u32 app3;
	u32 app4;
	u32 sw_id_offset_wo;
	u32 sw_id_offset_hi;
	u32 wesewved6;
};

#ifdef CONFIG_PHYS_ADDW_T_64BIT
#define nixge_hw_dma_bd_set_addw(bd, fiewd, addw) \
	do { \
		(bd)->fiewd##_wo = wowew_32_bits((addw)); \
		(bd)->fiewd##_hi = uppew_32_bits((addw)); \
	} whiwe (0)
#ewse
#define nixge_hw_dma_bd_set_addw(bd, fiewd, addw) \
	((bd)->fiewd##_wo = wowew_32_bits((addw)))
#endif

#define nixge_hw_dma_bd_set_phys(bd, addw) \
	nixge_hw_dma_bd_set_addw((bd), phys, (addw))

#define nixge_hw_dma_bd_set_next(bd, addw) \
	nixge_hw_dma_bd_set_addw((bd), next, (addw))

#define nixge_hw_dma_bd_set_offset(bd, addw) \
	nixge_hw_dma_bd_set_addw((bd), sw_id_offset, (addw))

#ifdef CONFIG_PHYS_ADDW_T_64BIT
#define nixge_hw_dma_bd_get_addw(bd, fiewd) \
	(dma_addw_t)((((u64)(bd)->fiewd##_hi) << 32) | ((bd)->fiewd##_wo))
#ewse
#define nixge_hw_dma_bd_get_addw(bd, fiewd) \
	(dma_addw_t)((bd)->fiewd##_wo)
#endif

stwuct nixge_tx_skb {
	stwuct sk_buff *skb;
	dma_addw_t mapping;
	size_t size;
	boow mapped_as_page;
};

stwuct nixge_pwiv {
	stwuct net_device *ndev;
	stwuct napi_stwuct napi;
	stwuct device *dev;

	/* Connection to PHY device */
	stwuct device_node *phy_node;
	phy_intewface_t		phy_mode;

	int wink;
	unsigned int speed;
	unsigned int dupwex;

	/* MDIO bus data */
	stwuct mii_bus *mii_bus;	/* MII bus wefewence */

	/* IO wegistews, dma functions and IWQs */
	void __iomem *ctww_wegs;
	void __iomem *dma_wegs;

	stwuct taskwet_stwuct dma_eww_taskwet;

	int tx_iwq;
	int wx_iwq;

	/* Buffew descwiptows */
	stwuct nixge_hw_dma_bd *tx_bd_v;
	stwuct nixge_tx_skb *tx_skb;
	dma_addw_t tx_bd_p;

	stwuct nixge_hw_dma_bd *wx_bd_v;
	dma_addw_t wx_bd_p;
	u32 tx_bd_ci;
	u32 tx_bd_taiw;
	u32 wx_bd_ci;

	u32 coawesce_count_wx;
	u32 coawesce_count_tx;
};

static void nixge_dma_wwite_weg(stwuct nixge_pwiv *pwiv, off_t offset, u32 vaw)
{
	wwitew(vaw, pwiv->dma_wegs + offset);
}

static void nixge_dma_wwite_desc_weg(stwuct nixge_pwiv *pwiv, off_t offset,
				     dma_addw_t addw)
{
	wwitew(wowew_32_bits(addw), pwiv->dma_wegs + offset);
#ifdef CONFIG_PHYS_ADDW_T_64BIT
	wwitew(uppew_32_bits(addw), pwiv->dma_wegs + offset + 4);
#endif
}

static u32 nixge_dma_wead_weg(const stwuct nixge_pwiv *pwiv, off_t offset)
{
	wetuwn weadw(pwiv->dma_wegs + offset);
}

static void nixge_ctww_wwite_weg(stwuct nixge_pwiv *pwiv, off_t offset, u32 vaw)
{
	wwitew(vaw, pwiv->ctww_wegs + offset);
}

static u32 nixge_ctww_wead_weg(stwuct nixge_pwiv *pwiv, off_t offset)
{
	wetuwn weadw(pwiv->ctww_wegs + offset);
}

#define nixge_ctww_poww_timeout(pwiv, addw, vaw, cond, sweep_us, timeout_us) \
	weadw_poww_timeout((pwiv)->ctww_wegs + (addw), (vaw), (cond), \
			   (sweep_us), (timeout_us))

#define nixge_dma_poww_timeout(pwiv, addw, vaw, cond, sweep_us, timeout_us) \
	weadw_poww_timeout((pwiv)->dma_wegs + (addw), (vaw), (cond), \
			   (sweep_us), (timeout_us))

static void nixge_hw_dma_bd_wewease(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	dma_addw_t phys_addw;
	stwuct sk_buff *skb;
	int i;

	if (pwiv->wx_bd_v) {
		fow (i = 0; i < WX_BD_NUM; i++) {
			phys_addw = nixge_hw_dma_bd_get_addw(&pwiv->wx_bd_v[i],
							     phys);

			dma_unmap_singwe(ndev->dev.pawent, phys_addw,
					 NIXGE_MAX_JUMBO_FWAME_SIZE,
					 DMA_FWOM_DEVICE);

			skb = (stwuct sk_buff *)(uintptw_t)
				nixge_hw_dma_bd_get_addw(&pwiv->wx_bd_v[i],
							 sw_id_offset);
			dev_kfwee_skb(skb);
		}

		dma_fwee_cohewent(ndev->dev.pawent,
				  sizeof(*pwiv->wx_bd_v) * WX_BD_NUM,
				  pwiv->wx_bd_v,
				  pwiv->wx_bd_p);
	}

	if (pwiv->tx_skb)
		devm_kfwee(ndev->dev.pawent, pwiv->tx_skb);

	if (pwiv->tx_bd_v)
		dma_fwee_cohewent(ndev->dev.pawent,
				  sizeof(*pwiv->tx_bd_v) * TX_BD_NUM,
				  pwiv->tx_bd_v,
				  pwiv->tx_bd_p);
}

static int nixge_hw_dma_bd_init(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	dma_addw_t phys;
	u32 cw;
	int i;

	/* Weset the indexes which awe used fow accessing the BDs */
	pwiv->tx_bd_ci = 0;
	pwiv->tx_bd_taiw = 0;
	pwiv->wx_bd_ci = 0;

	/* Awwocate the Tx and Wx buffew descwiptows. */
	pwiv->tx_bd_v = dma_awwoc_cohewent(ndev->dev.pawent,
					   sizeof(*pwiv->tx_bd_v) * TX_BD_NUM,
					   &pwiv->tx_bd_p, GFP_KEWNEW);
	if (!pwiv->tx_bd_v)
		goto out;

	pwiv->tx_skb = devm_kcawwoc(ndev->dev.pawent,
				    TX_BD_NUM, sizeof(*pwiv->tx_skb),
				    GFP_KEWNEW);
	if (!pwiv->tx_skb)
		goto out;

	pwiv->wx_bd_v = dma_awwoc_cohewent(ndev->dev.pawent,
					   sizeof(*pwiv->wx_bd_v) * WX_BD_NUM,
					   &pwiv->wx_bd_p, GFP_KEWNEW);
	if (!pwiv->wx_bd_v)
		goto out;

	fow (i = 0; i < TX_BD_NUM; i++) {
		nixge_hw_dma_bd_set_next(&pwiv->tx_bd_v[i],
					 pwiv->tx_bd_p +
					 sizeof(*pwiv->tx_bd_v) *
					 ((i + 1) % TX_BD_NUM));
	}

	fow (i = 0; i < WX_BD_NUM; i++) {
		nixge_hw_dma_bd_set_next(&pwiv->wx_bd_v[i],
					 pwiv->wx_bd_p
					 + sizeof(*pwiv->wx_bd_v) *
					 ((i + 1) % WX_BD_NUM));

		skb = __netdev_awwoc_skb_ip_awign(ndev,
						  NIXGE_MAX_JUMBO_FWAME_SIZE,
						  GFP_KEWNEW);
		if (!skb)
			goto out;

		nixge_hw_dma_bd_set_offset(&pwiv->wx_bd_v[i], (uintptw_t)skb);
		phys = dma_map_singwe(ndev->dev.pawent, skb->data,
				      NIXGE_MAX_JUMBO_FWAME_SIZE,
				      DMA_FWOM_DEVICE);

		nixge_hw_dma_bd_set_phys(&pwiv->wx_bd_v[i], phys);

		pwiv->wx_bd_v[i].cntww = NIXGE_MAX_JUMBO_FWAME_SIZE;
	}

	/* Stawt updating the Wx channew contwow wegistew */
	cw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
	/* Update the intewwupt coawesce count */
	cw = ((cw & ~XAXIDMA_COAWESCE_MASK) |
	      ((pwiv->coawesce_count_wx) << XAXIDMA_COAWESCE_SHIFT));
	/* Update the deway timew count */
	cw = ((cw & ~XAXIDMA_DEWAY_MASK) |
	      (XAXIDMA_DFT_WX_WAITBOUND << XAXIDMA_DEWAY_SHIFT));
	/* Enabwe coawesce, deway timew and ewwow intewwupts */
	cw |= XAXIDMA_IWQ_AWW_MASK;
	/* Wwite to the Wx channew contwow wegistew */
	nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_CW_OFFSET, cw);

	/* Stawt updating the Tx channew contwow wegistew */
	cw = nixge_dma_wead_weg(pwiv, XAXIDMA_TX_CW_OFFSET);
	/* Update the intewwupt coawesce count */
	cw = (((cw & ~XAXIDMA_COAWESCE_MASK)) |
	      ((pwiv->coawesce_count_tx) << XAXIDMA_COAWESCE_SHIFT));
	/* Update the deway timew count */
	cw = (((cw & ~XAXIDMA_DEWAY_MASK)) |
	      (XAXIDMA_DFT_TX_WAITBOUND << XAXIDMA_DEWAY_SHIFT));
	/* Enabwe coawesce, deway timew and ewwow intewwupts */
	cw |= XAXIDMA_IWQ_AWW_MASK;
	/* Wwite to the Tx channew contwow wegistew */
	nixge_dma_wwite_weg(pwiv, XAXIDMA_TX_CW_OFFSET, cw);

	/* Popuwate the taiw pointew and bwing the Wx Axi DMA engine out of
	 * hawted state. This wiww make the Wx side weady fow weception.
	 */
	nixge_dma_wwite_desc_weg(pwiv, XAXIDMA_WX_CDESC_OFFSET, pwiv->wx_bd_p);
	cw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
	nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_CW_OFFSET,
			    cw | XAXIDMA_CW_WUNSTOP_MASK);
	nixge_dma_wwite_desc_weg(pwiv, XAXIDMA_WX_TDESC_OFFSET, pwiv->wx_bd_p +
			    (sizeof(*pwiv->wx_bd_v) * (WX_BD_NUM - 1)));

	/* Wwite to the WS (Wun-stop) bit in the Tx channew contwow wegistew.
	 * Tx channew is now weady to wun. But onwy aftew we wwite to the
	 * taiw pointew wegistew that the Tx channew wiww stawt twansmitting.
	 */
	nixge_dma_wwite_desc_weg(pwiv, XAXIDMA_TX_CDESC_OFFSET, pwiv->tx_bd_p);
	cw = nixge_dma_wead_weg(pwiv, XAXIDMA_TX_CW_OFFSET);
	nixge_dma_wwite_weg(pwiv, XAXIDMA_TX_CW_OFFSET,
			    cw | XAXIDMA_CW_WUNSTOP_MASK);

	wetuwn 0;
out:
	nixge_hw_dma_bd_wewease(ndev);
	wetuwn -ENOMEM;
}

static void __nixge_device_weset(stwuct nixge_pwiv *pwiv, off_t offset)
{
	u32 status;
	int eww;

	/* Weset Axi DMA. This wouwd weset NIXGE Ethewnet cowe as weww.
	 * The weset pwocess of Axi DMA takes a whiwe to compwete as aww
	 * pending commands/twansfews wiww be fwushed ow compweted duwing
	 * this weset pwocess.
	 */
	nixge_dma_wwite_weg(pwiv, offset, XAXIDMA_CW_WESET_MASK);
	eww = nixge_dma_poww_timeout(pwiv, offset, status,
				     !(status & XAXIDMA_CW_WESET_MASK), 10,
				     1000);
	if (eww)
		netdev_eww(pwiv->ndev, "%s: DMA weset timeout!\n", __func__);
}

static void nixge_device_weset(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);

	__nixge_device_weset(pwiv, XAXIDMA_TX_CW_OFFSET);
	__nixge_device_weset(pwiv, XAXIDMA_WX_CW_OFFSET);

	if (nixge_hw_dma_bd_init(ndev))
		netdev_eww(ndev, "%s: descwiptow awwocation faiwed\n",
			   __func__);

	netif_twans_update(ndev);
}

static void nixge_handwe_wink_change(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct phy_device *phydev = ndev->phydev;

	if (phydev->wink != pwiv->wink || phydev->speed != pwiv->speed ||
	    phydev->dupwex != pwiv->dupwex) {
		pwiv->wink = phydev->wink;
		pwiv->speed = phydev->speed;
		pwiv->dupwex = phydev->dupwex;
		phy_pwint_status(phydev);
	}
}

static void nixge_tx_skb_unmap(stwuct nixge_pwiv *pwiv,
			       stwuct nixge_tx_skb *tx_skb)
{
	if (tx_skb->mapping) {
		if (tx_skb->mapped_as_page)
			dma_unmap_page(pwiv->ndev->dev.pawent, tx_skb->mapping,
				       tx_skb->size, DMA_TO_DEVICE);
		ewse
			dma_unmap_singwe(pwiv->ndev->dev.pawent,
					 tx_skb->mapping,
					 tx_skb->size, DMA_TO_DEVICE);
		tx_skb->mapping = 0;
	}

	if (tx_skb->skb) {
		dev_kfwee_skb_any(tx_skb->skb);
		tx_skb->skb = NUWW;
	}
}

static void nixge_stawt_xmit_done(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct nixge_hw_dma_bd *cuw_p;
	stwuct nixge_tx_skb *tx_skb;
	unsigned int status = 0;
	u32 packets = 0;
	u32 size = 0;

	cuw_p = &pwiv->tx_bd_v[pwiv->tx_bd_ci];
	tx_skb = &pwiv->tx_skb[pwiv->tx_bd_ci];

	status = cuw_p->status;

	whiwe (status & XAXIDMA_BD_STS_COMPWETE_MASK) {
		nixge_tx_skb_unmap(pwiv, tx_skb);
		cuw_p->status = 0;

		size += status & XAXIDMA_BD_STS_ACTUAW_WEN_MASK;
		packets++;

		++pwiv->tx_bd_ci;
		pwiv->tx_bd_ci %= TX_BD_NUM;
		cuw_p = &pwiv->tx_bd_v[pwiv->tx_bd_ci];
		tx_skb = &pwiv->tx_skb[pwiv->tx_bd_ci];
		status = cuw_p->status;
	}

	ndev->stats.tx_packets += packets;
	ndev->stats.tx_bytes += size;

	if (packets)
		netif_wake_queue(ndev);
}

static int nixge_check_tx_bd_space(stwuct nixge_pwiv *pwiv,
				   int num_fwag)
{
	stwuct nixge_hw_dma_bd *cuw_p;

	cuw_p = &pwiv->tx_bd_v[(pwiv->tx_bd_taiw + num_fwag) % TX_BD_NUM];
	if (cuw_p->status & XAXIDMA_BD_STS_AWW_MASK)
		wetuwn NETDEV_TX_BUSY;
	wetuwn 0;
}

static netdev_tx_t nixge_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct nixge_hw_dma_bd *cuw_p;
	stwuct nixge_tx_skb *tx_skb;
	dma_addw_t taiw_p, cuw_phys;
	skb_fwag_t *fwag;
	u32 num_fwag;
	u32 ii;

	num_fwag = skb_shinfo(skb)->nw_fwags;
	cuw_p = &pwiv->tx_bd_v[pwiv->tx_bd_taiw];
	tx_skb = &pwiv->tx_skb[pwiv->tx_bd_taiw];

	if (nixge_check_tx_bd_space(pwiv, num_fwag)) {
		if (!netif_queue_stopped(ndev))
			netif_stop_queue(ndev);
		wetuwn NETDEV_TX_OK;
	}

	cuw_phys = dma_map_singwe(ndev->dev.pawent, skb->data,
				  skb_headwen(skb), DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ndev->dev.pawent, cuw_phys))
		goto dwop;
	nixge_hw_dma_bd_set_phys(cuw_p, cuw_phys);

	cuw_p->cntww = skb_headwen(skb) | XAXIDMA_BD_CTWW_TXSOF_MASK;

	tx_skb->skb = NUWW;
	tx_skb->mapping = cuw_phys;
	tx_skb->size = skb_headwen(skb);
	tx_skb->mapped_as_page = fawse;

	fow (ii = 0; ii < num_fwag; ii++) {
		++pwiv->tx_bd_taiw;
		pwiv->tx_bd_taiw %= TX_BD_NUM;
		cuw_p = &pwiv->tx_bd_v[pwiv->tx_bd_taiw];
		tx_skb = &pwiv->tx_skb[pwiv->tx_bd_taiw];
		fwag = &skb_shinfo(skb)->fwags[ii];

		cuw_phys = skb_fwag_dma_map(ndev->dev.pawent, fwag, 0,
					    skb_fwag_size(fwag),
					    DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ndev->dev.pawent, cuw_phys))
			goto fwag_eww;
		nixge_hw_dma_bd_set_phys(cuw_p, cuw_phys);

		cuw_p->cntww = skb_fwag_size(fwag);

		tx_skb->skb = NUWW;
		tx_skb->mapping = cuw_phys;
		tx_skb->size = skb_fwag_size(fwag);
		tx_skb->mapped_as_page = twue;
	}

	/* wast buffew of the fwame */
	tx_skb->skb = skb;

	cuw_p->cntww |= XAXIDMA_BD_CTWW_TXEOF_MASK;

	taiw_p = pwiv->tx_bd_p + sizeof(*pwiv->tx_bd_v) * pwiv->tx_bd_taiw;
	/* Stawt the twansfew */
	nixge_dma_wwite_desc_weg(pwiv, XAXIDMA_TX_TDESC_OFFSET, taiw_p);
	++pwiv->tx_bd_taiw;
	pwiv->tx_bd_taiw %= TX_BD_NUM;

	wetuwn NETDEV_TX_OK;
fwag_eww:
	fow (; ii > 0; ii--) {
		if (pwiv->tx_bd_taiw)
			pwiv->tx_bd_taiw--;
		ewse
			pwiv->tx_bd_taiw = TX_BD_NUM - 1;

		tx_skb = &pwiv->tx_skb[pwiv->tx_bd_taiw];
		nixge_tx_skb_unmap(pwiv, tx_skb);

		cuw_p = &pwiv->tx_bd_v[pwiv->tx_bd_taiw];
		cuw_p->status = 0;
	}
	dma_unmap_singwe(pwiv->ndev->dev.pawent,
			 tx_skb->mapping,
			 tx_skb->size, DMA_TO_DEVICE);
dwop:
	ndev->stats.tx_dwopped++;
	wetuwn NETDEV_TX_OK;
}

static int nixge_wecv(stwuct net_device *ndev, int budget)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct sk_buff *skb, *new_skb;
	stwuct nixge_hw_dma_bd *cuw_p;
	dma_addw_t taiw_p = 0, cuw_phys = 0;
	u32 packets = 0;
	u32 wength = 0;
	u32 size = 0;

	cuw_p = &pwiv->wx_bd_v[pwiv->wx_bd_ci];

	whiwe ((cuw_p->status & XAXIDMA_BD_STS_COMPWETE_MASK &&
		budget > packets)) {
		taiw_p = pwiv->wx_bd_p + sizeof(*pwiv->wx_bd_v) *
			 pwiv->wx_bd_ci;

		skb = (stwuct sk_buff *)(uintptw_t)
			nixge_hw_dma_bd_get_addw(cuw_p, sw_id_offset);

		wength = cuw_p->status & XAXIDMA_BD_STS_ACTUAW_WEN_MASK;
		if (wength > NIXGE_MAX_JUMBO_FWAME_SIZE)
			wength = NIXGE_MAX_JUMBO_FWAME_SIZE;

		dma_unmap_singwe(ndev->dev.pawent,
				 nixge_hw_dma_bd_get_addw(cuw_p, phys),
				 NIXGE_MAX_JUMBO_FWAME_SIZE,
				 DMA_FWOM_DEVICE);

		skb_put(skb, wength);

		skb->pwotocow = eth_type_twans(skb, ndev);
		skb_checksum_none_assewt(skb);

		/* Fow now mawk them as CHECKSUM_NONE since
		 * we don't have offwoad capabiwities
		 */
		skb->ip_summed = CHECKSUM_NONE;

		napi_gwo_weceive(&pwiv->napi, skb);

		size += wength;
		packets++;

		new_skb = netdev_awwoc_skb_ip_awign(ndev,
						    NIXGE_MAX_JUMBO_FWAME_SIZE);
		if (!new_skb)
			wetuwn packets;

		cuw_phys = dma_map_singwe(ndev->dev.pawent, new_skb->data,
					  NIXGE_MAX_JUMBO_FWAME_SIZE,
					  DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(ndev->dev.pawent, cuw_phys)) {
			/* FIXME: baiw out and cwean up */
			netdev_eww(ndev, "Faiwed to map ...\n");
		}
		nixge_hw_dma_bd_set_phys(cuw_p, cuw_phys);
		cuw_p->cntww = NIXGE_MAX_JUMBO_FWAME_SIZE;
		cuw_p->status = 0;
		nixge_hw_dma_bd_set_offset(cuw_p, (uintptw_t)new_skb);

		++pwiv->wx_bd_ci;
		pwiv->wx_bd_ci %= WX_BD_NUM;
		cuw_p = &pwiv->wx_bd_v[pwiv->wx_bd_ci];
	}

	ndev->stats.wx_packets += packets;
	ndev->stats.wx_bytes += size;

	if (taiw_p)
		nixge_dma_wwite_desc_weg(pwiv, XAXIDMA_WX_TDESC_OFFSET, taiw_p);

	wetuwn packets;
}

static int nixge_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct nixge_pwiv *pwiv = containew_of(napi, stwuct nixge_pwiv, napi);
	int wowk_done;
	u32 status, cw;

	wowk_done = 0;

	wowk_done = nixge_wecv(pwiv->ndev, budget);
	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		status = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_SW_OFFSET);

		if (status & (XAXIDMA_IWQ_IOC_MASK | XAXIDMA_IWQ_DEWAY_MASK)) {
			/* If thewe's mowe, wescheduwe, but cweaw */
			nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_SW_OFFSET, status);
			napi_scheduwe(napi);
		} ewse {
			/* if not, tuwn on WX IWQs again ... */
			cw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
			cw |= (XAXIDMA_IWQ_IOC_MASK | XAXIDMA_IWQ_DEWAY_MASK);
			nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_CW_OFFSET, cw);
		}
	}

	wetuwn wowk_done;
}

static iwqwetuwn_t nixge_tx_iwq(int iwq, void *_ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(_ndev);
	stwuct net_device *ndev = _ndev;
	unsigned int status;
	dma_addw_t phys;
	u32 cw;

	status = nixge_dma_wead_weg(pwiv, XAXIDMA_TX_SW_OFFSET);
	if (status & (XAXIDMA_IWQ_IOC_MASK | XAXIDMA_IWQ_DEWAY_MASK)) {
		nixge_dma_wwite_weg(pwiv, XAXIDMA_TX_SW_OFFSET, status);
		nixge_stawt_xmit_done(pwiv->ndev);
		goto out;
	}
	if (!(status & XAXIDMA_IWQ_AWW_MASK)) {
		netdev_eww(ndev, "No intewwupts assewted in Tx path\n");
		wetuwn IWQ_NONE;
	}
	if (status & XAXIDMA_IWQ_EWWOW_MASK) {
		phys = nixge_hw_dma_bd_get_addw(&pwiv->tx_bd_v[pwiv->tx_bd_ci],
						phys);

		netdev_eww(ndev, "DMA Tx ewwow 0x%x\n", status);
		netdev_eww(ndev, "Cuwwent BD is at: 0x%wwx\n", (u64)phys);

		cw = nixge_dma_wead_weg(pwiv, XAXIDMA_TX_CW_OFFSET);
		/* Disabwe coawesce, deway timew and ewwow intewwupts */
		cw &= (~XAXIDMA_IWQ_AWW_MASK);
		/* Wwite to the Tx channew contwow wegistew */
		nixge_dma_wwite_weg(pwiv, XAXIDMA_TX_CW_OFFSET, cw);

		cw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
		/* Disabwe coawesce, deway timew and ewwow intewwupts */
		cw &= (~XAXIDMA_IWQ_AWW_MASK);
		/* Wwite to the Wx channew contwow wegistew */
		nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_CW_OFFSET, cw);

		taskwet_scheduwe(&pwiv->dma_eww_taskwet);
		nixge_dma_wwite_weg(pwiv, XAXIDMA_TX_SW_OFFSET, status);
	}
out:
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t nixge_wx_iwq(int iwq, void *_ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(_ndev);
	stwuct net_device *ndev = _ndev;
	unsigned int status;
	dma_addw_t phys;
	u32 cw;

	status = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_SW_OFFSET);
	if (status & (XAXIDMA_IWQ_IOC_MASK | XAXIDMA_IWQ_DEWAY_MASK)) {
		/* Tuwn of IWQs because NAPI */
		nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_SW_OFFSET, status);
		cw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
		cw &= ~(XAXIDMA_IWQ_IOC_MASK | XAXIDMA_IWQ_DEWAY_MASK);
		nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_CW_OFFSET, cw);

		napi_scheduwe(&pwiv->napi);
		goto out;
	}
	if (!(status & XAXIDMA_IWQ_AWW_MASK)) {
		netdev_eww(ndev, "No intewwupts assewted in Wx path\n");
		wetuwn IWQ_NONE;
	}
	if (status & XAXIDMA_IWQ_EWWOW_MASK) {
		phys = nixge_hw_dma_bd_get_addw(&pwiv->wx_bd_v[pwiv->wx_bd_ci],
						phys);
		netdev_eww(ndev, "DMA Wx ewwow 0x%x\n", status);
		netdev_eww(ndev, "Cuwwent BD is at: 0x%wwx\n", (u64)phys);

		cw = nixge_dma_wead_weg(pwiv, XAXIDMA_TX_CW_OFFSET);
		/* Disabwe coawesce, deway timew and ewwow intewwupts */
		cw &= (~XAXIDMA_IWQ_AWW_MASK);
		/* Finawwy wwite to the Tx channew contwow wegistew */
		nixge_dma_wwite_weg(pwiv, XAXIDMA_TX_CW_OFFSET, cw);

		cw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
		/* Disabwe coawesce, deway timew and ewwow intewwupts */
		cw &= (~XAXIDMA_IWQ_AWW_MASK);
		/* wwite to the Wx channew contwow wegistew */
		nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_CW_OFFSET, cw);

		taskwet_scheduwe(&pwiv->dma_eww_taskwet);
		nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_SW_OFFSET, status);
	}
out:
	wetuwn IWQ_HANDWED;
}

static void nixge_dma_eww_handwew(stwuct taskwet_stwuct *t)
{
	stwuct nixge_pwiv *wp = fwom_taskwet(wp, t, dma_eww_taskwet);
	stwuct nixge_hw_dma_bd *cuw_p;
	stwuct nixge_tx_skb *tx_skb;
	u32 cw, i;

	__nixge_device_weset(wp, XAXIDMA_TX_CW_OFFSET);
	__nixge_device_weset(wp, XAXIDMA_WX_CW_OFFSET);

	fow (i = 0; i < TX_BD_NUM; i++) {
		cuw_p = &wp->tx_bd_v[i];
		tx_skb = &wp->tx_skb[i];
		nixge_tx_skb_unmap(wp, tx_skb);

		nixge_hw_dma_bd_set_phys(cuw_p, 0);
		cuw_p->cntww = 0;
		cuw_p->status = 0;
		nixge_hw_dma_bd_set_offset(cuw_p, 0);
	}

	fow (i = 0; i < WX_BD_NUM; i++) {
		cuw_p = &wp->wx_bd_v[i];
		cuw_p->status = 0;
	}

	wp->tx_bd_ci = 0;
	wp->tx_bd_taiw = 0;
	wp->wx_bd_ci = 0;

	/* Stawt updating the Wx channew contwow wegistew */
	cw = nixge_dma_wead_weg(wp, XAXIDMA_WX_CW_OFFSET);
	/* Update the intewwupt coawesce count */
	cw = ((cw & ~XAXIDMA_COAWESCE_MASK) |
	      (XAXIDMA_DFT_WX_THWESHOWD << XAXIDMA_COAWESCE_SHIFT));
	/* Update the deway timew count */
	cw = ((cw & ~XAXIDMA_DEWAY_MASK) |
	      (XAXIDMA_DFT_WX_WAITBOUND << XAXIDMA_DEWAY_SHIFT));
	/* Enabwe coawesce, deway timew and ewwow intewwupts */
	cw |= XAXIDMA_IWQ_AWW_MASK;
	/* Finawwy wwite to the Wx channew contwow wegistew */
	nixge_dma_wwite_weg(wp, XAXIDMA_WX_CW_OFFSET, cw);

	/* Stawt updating the Tx channew contwow wegistew */
	cw = nixge_dma_wead_weg(wp, XAXIDMA_TX_CW_OFFSET);
	/* Update the intewwupt coawesce count */
	cw = (((cw & ~XAXIDMA_COAWESCE_MASK)) |
	      (XAXIDMA_DFT_TX_THWESHOWD << XAXIDMA_COAWESCE_SHIFT));
	/* Update the deway timew count */
	cw = (((cw & ~XAXIDMA_DEWAY_MASK)) |
	      (XAXIDMA_DFT_TX_WAITBOUND << XAXIDMA_DEWAY_SHIFT));
	/* Enabwe coawesce, deway timew and ewwow intewwupts */
	cw |= XAXIDMA_IWQ_AWW_MASK;
	/* Finawwy wwite to the Tx channew contwow wegistew */
	nixge_dma_wwite_weg(wp, XAXIDMA_TX_CW_OFFSET, cw);

	/* Popuwate the taiw pointew and bwing the Wx Axi DMA engine out of
	 * hawted state. This wiww make the Wx side weady fow weception.
	 */
	nixge_dma_wwite_desc_weg(wp, XAXIDMA_WX_CDESC_OFFSET, wp->wx_bd_p);
	cw = nixge_dma_wead_weg(wp, XAXIDMA_WX_CW_OFFSET);
	nixge_dma_wwite_weg(wp, XAXIDMA_WX_CW_OFFSET,
			    cw | XAXIDMA_CW_WUNSTOP_MASK);
	nixge_dma_wwite_desc_weg(wp, XAXIDMA_WX_TDESC_OFFSET, wp->wx_bd_p +
			    (sizeof(*wp->wx_bd_v) * (WX_BD_NUM - 1)));

	/* Wwite to the WS (Wun-stop) bit in the Tx channew contwow wegistew.
	 * Tx channew is now weady to wun. But onwy aftew we wwite to the
	 * taiw pointew wegistew that the Tx channew wiww stawt twansmitting
	 */
	nixge_dma_wwite_desc_weg(wp, XAXIDMA_TX_CDESC_OFFSET, wp->tx_bd_p);
	cw = nixge_dma_wead_weg(wp, XAXIDMA_TX_CW_OFFSET);
	nixge_dma_wwite_weg(wp, XAXIDMA_TX_CW_OFFSET,
			    cw | XAXIDMA_CW_WUNSTOP_MASK);
}

static int nixge_open(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct phy_device *phy;
	int wet;

	nixge_device_weset(ndev);

	phy = of_phy_connect(ndev, pwiv->phy_node,
			     &nixge_handwe_wink_change, 0, pwiv->phy_mode);
	if (!phy)
		wetuwn -ENODEV;

	phy_stawt(phy);

	/* Enabwe taskwets fow Axi DMA ewwow handwing */
	taskwet_setup(&pwiv->dma_eww_taskwet, nixge_dma_eww_handwew);

	napi_enabwe(&pwiv->napi);

	/* Enabwe intewwupts fow Axi DMA Tx */
	wet = wequest_iwq(pwiv->tx_iwq, nixge_tx_iwq, 0, ndev->name, ndev);
	if (wet)
		goto eww_tx_iwq;
	/* Enabwe intewwupts fow Axi DMA Wx */
	wet = wequest_iwq(pwiv->wx_iwq, nixge_wx_iwq, 0, ndev->name, ndev);
	if (wet)
		goto eww_wx_iwq;

	netif_stawt_queue(ndev);

	wetuwn 0;

eww_wx_iwq:
	fwee_iwq(pwiv->tx_iwq, ndev);
eww_tx_iwq:
	napi_disabwe(&pwiv->napi);
	phy_stop(phy);
	phy_disconnect(phy);
	taskwet_kiww(&pwiv->dma_eww_taskwet);
	netdev_eww(ndev, "wequest_iwq() faiwed\n");
	wetuwn wet;
}

static int nixge_stop(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	u32 cw;

	netif_stop_queue(ndev);
	napi_disabwe(&pwiv->napi);

	if (ndev->phydev) {
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
	}

	cw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
	nixge_dma_wwite_weg(pwiv, XAXIDMA_WX_CW_OFFSET,
			    cw & (~XAXIDMA_CW_WUNSTOP_MASK));
	cw = nixge_dma_wead_weg(pwiv, XAXIDMA_TX_CW_OFFSET);
	nixge_dma_wwite_weg(pwiv, XAXIDMA_TX_CW_OFFSET,
			    cw & (~XAXIDMA_CW_WUNSTOP_MASK));

	taskwet_kiww(&pwiv->dma_eww_taskwet);

	fwee_iwq(pwiv->tx_iwq, ndev);
	fwee_iwq(pwiv->wx_iwq, ndev);

	nixge_hw_dma_bd_wewease(ndev);

	wetuwn 0;
}

static int nixge_change_mtu(stwuct net_device *ndev, int new_mtu)
{
	if (netif_wunning(ndev))
		wetuwn -EBUSY;

	if ((new_mtu + NIXGE_HDW_SIZE + NIXGE_TWW_SIZE) >
	     NIXGE_MAX_JUMBO_FWAME_SIZE)
		wetuwn -EINVAW;

	ndev->mtu = new_mtu;

	wetuwn 0;
}

static s32 __nixge_hw_set_mac_addwess(stwuct net_device *ndev)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MAC_WSB,
			     (ndev->dev_addw[2]) << 24 |
			     (ndev->dev_addw[3] << 16) |
			     (ndev->dev_addw[4] << 8) |
			     (ndev->dev_addw[5] << 0));

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MAC_MSB,
			     (ndev->dev_addw[1] | (ndev->dev_addw[0] << 8)));

	wetuwn 0;
}

static int nixge_net_set_mac_addwess(stwuct net_device *ndev, void *p)
{
	int eww;

	eww = eth_mac_addw(ndev, p);
	if (!eww)
		__nixge_hw_set_mac_addwess(ndev);

	wetuwn eww;
}

static const stwuct net_device_ops nixge_netdev_ops = {
	.ndo_open = nixge_open,
	.ndo_stop = nixge_stop,
	.ndo_stawt_xmit = nixge_stawt_xmit,
	.ndo_change_mtu	= nixge_change_mtu,
	.ndo_set_mac_addwess = nixge_net_set_mac_addwess,
	.ndo_vawidate_addw = eth_vawidate_addw,
};

static void nixge_ethtoows_get_dwvinfo(stwuct net_device *ndev,
				       stwuct ethtoow_dwvinfo *ed)
{
	stwscpy(ed->dwivew, "nixge", sizeof(ed->dwivew));
	stwscpy(ed->bus_info, "pwatfowm", sizeof(ed->bus_info));
}

static int
nixge_ethtoows_get_coawesce(stwuct net_device *ndev,
			    stwuct ethtoow_coawesce *ecoawesce,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	u32 wegvaw = 0;

	wegvaw = nixge_dma_wead_weg(pwiv, XAXIDMA_WX_CW_OFFSET);
	ecoawesce->wx_max_coawesced_fwames = (wegvaw & XAXIDMA_COAWESCE_MASK)
					     >> XAXIDMA_COAWESCE_SHIFT;
	wegvaw = nixge_dma_wead_weg(pwiv, XAXIDMA_TX_CW_OFFSET);
	ecoawesce->tx_max_coawesced_fwames = (wegvaw & XAXIDMA_COAWESCE_MASK)
					     >> XAXIDMA_COAWESCE_SHIFT;
	wetuwn 0;
}

static int
nixge_ethtoows_set_coawesce(stwuct net_device *ndev,
			    stwuct ethtoow_coawesce *ecoawesce,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);

	if (netif_wunning(ndev)) {
		netdev_eww(ndev,
			   "Pwease stop netif befowe appwying configuwation\n");
		wetuwn -EBUSY;
	}

	if (ecoawesce->wx_max_coawesced_fwames)
		pwiv->coawesce_count_wx = ecoawesce->wx_max_coawesced_fwames;
	if (ecoawesce->tx_max_coawesced_fwames)
		pwiv->coawesce_count_tx = ecoawesce->tx_max_coawesced_fwames;

	wetuwn 0;
}

static int nixge_ethtoows_set_phys_id(stwuct net_device *ndev,
				      enum ethtoow_phys_id_state state)
{
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);
	u32 ctww;

	ctww = nixge_ctww_wead_weg(pwiv, NIXGE_WEG_WED_CTW);
	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		ctww |= NIXGE_ID_WED_CTW_EN;
		/* Enabwe identification WED ovewwide*/
		nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_WED_CTW, ctww);
		wetuwn 2;

	case ETHTOOW_ID_ON:
		ctww |= NIXGE_ID_WED_CTW_VAW;
		nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_WED_CTW, ctww);
		bweak;

	case ETHTOOW_ID_OFF:
		ctww &= ~NIXGE_ID_WED_CTW_VAW;
		nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_WED_CTW, ctww);
		bweak;

	case ETHTOOW_ID_INACTIVE:
		/* Westowe WED settings */
		ctww &= ~NIXGE_ID_WED_CTW_EN;
		nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_WED_CTW, ctww);
		bweak;
	}

	wetuwn 0;
}

static const stwuct ethtoow_ops nixge_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_MAX_FWAMES,
	.get_dwvinfo    = nixge_ethtoows_get_dwvinfo,
	.get_coawesce   = nixge_ethtoows_get_coawesce,
	.set_coawesce   = nixge_ethtoows_set_coawesce,
	.set_phys_id    = nixge_ethtoows_set_phys_id,
	.get_wink_ksettings     = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings     = phy_ethtoow_set_wink_ksettings,
	.get_wink		= ethtoow_op_get_wink,
};

static int nixge_mdio_wead_c22(stwuct mii_bus *bus, int phy_id, int weg)
{
	stwuct nixge_pwiv *pwiv = bus->pwiv;
	u32 status, tmp;
	int eww;
	u16 device;

	device = weg & 0x1f;

	tmp = NIXGE_MDIO_CWAUSE22 | NIXGE_MDIO_OP(NIXGE_MDIO_C22_WEAD) |
	      NIXGE_MDIO_ADDW(phy_id) | NIXGE_MDIO_MMD(device);

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_OP, tmp);
	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_CTWW, 1);

	eww = nixge_ctww_poww_timeout(pwiv, NIXGE_WEG_MDIO_CTWW, status,
				      !status, 10, 1000);
	if (eww) {
		dev_eww(pwiv->dev, "timeout setting wead command");
		wetuwn eww;
	}

	status = nixge_ctww_wead_weg(pwiv, NIXGE_WEG_MDIO_DATA);

	wetuwn status;
}

static int nixge_mdio_wead_c45(stwuct mii_bus *bus, int phy_id, int device,
			       int weg)
{
	stwuct nixge_pwiv *pwiv = bus->pwiv;
	u32 status, tmp;
	int eww;

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_ADDW, weg & 0xffff);

	tmp = NIXGE_MDIO_CWAUSE45 |
	      NIXGE_MDIO_OP(NIXGE_MDIO_OP_ADDWESS) |
	      NIXGE_MDIO_ADDW(phy_id) | NIXGE_MDIO_MMD(device);

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_OP, tmp);
	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_CTWW, 1);

	eww = nixge_ctww_poww_timeout(pwiv, NIXGE_WEG_MDIO_CTWW, status,
				      !status, 10, 1000);
	if (eww) {
		dev_eww(pwiv->dev, "timeout setting addwess");
		wetuwn eww;
	}

	tmp = NIXGE_MDIO_CWAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_C45_WEAD) |
	      NIXGE_MDIO_ADDW(phy_id) | NIXGE_MDIO_MMD(device);

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_OP, tmp);
	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_CTWW, 1);

	eww = nixge_ctww_poww_timeout(pwiv, NIXGE_WEG_MDIO_CTWW, status,
				      !status, 10, 1000);
	if (eww) {
		dev_eww(pwiv->dev, "timeout setting wead command");
		wetuwn eww;
	}

	status = nixge_ctww_wead_weg(pwiv, NIXGE_WEG_MDIO_DATA);

	wetuwn status;
}

static int nixge_mdio_wwite_c22(stwuct mii_bus *bus, int phy_id, int weg,
				u16 vaw)
{
	stwuct nixge_pwiv *pwiv = bus->pwiv;
	u32 status, tmp;
	u16 device;
	int eww;

	device = weg & 0x1f;

	tmp = NIXGE_MDIO_CWAUSE22 | NIXGE_MDIO_OP(NIXGE_MDIO_C22_WWITE) |
	      NIXGE_MDIO_ADDW(phy_id) | NIXGE_MDIO_MMD(device);

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_DATA, vaw);
	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_OP, tmp);
	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_CTWW, 1);

	eww = nixge_ctww_poww_timeout(pwiv, NIXGE_WEG_MDIO_CTWW, status,
				      !status, 10, 1000);
	if (eww)
		dev_eww(pwiv->dev, "timeout setting wwite command");

	wetuwn eww;
}

static int nixge_mdio_wwite_c45(stwuct mii_bus *bus, int phy_id,
				int device, int weg, u16 vaw)
{
	stwuct nixge_pwiv *pwiv = bus->pwiv;
	u32 status, tmp;
	int eww;

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_ADDW, weg & 0xffff);

	tmp = NIXGE_MDIO_CWAUSE45 |
	      NIXGE_MDIO_OP(NIXGE_MDIO_OP_ADDWESS) |
	      NIXGE_MDIO_ADDW(phy_id) | NIXGE_MDIO_MMD(device);

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_OP, tmp);
	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_CTWW, 1);

	eww = nixge_ctww_poww_timeout(pwiv, NIXGE_WEG_MDIO_CTWW, status,
				      !status, 10, 1000);
	if (eww) {
		dev_eww(pwiv->dev, "timeout setting addwess");
		wetuwn eww;
	}

	tmp = NIXGE_MDIO_CWAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_C45_WWITE) |
	      NIXGE_MDIO_ADDW(phy_id) | NIXGE_MDIO_MMD(device);

	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_DATA, vaw);
	nixge_ctww_wwite_weg(pwiv, NIXGE_WEG_MDIO_OP, tmp);

	eww = nixge_ctww_poww_timeout(pwiv, NIXGE_WEG_MDIO_CTWW, status,
				      !status, 10, 1000);
	if (eww)
		dev_eww(pwiv->dev, "timeout setting wwite command");

	wetuwn eww;
}

static int nixge_mdio_setup(stwuct nixge_pwiv *pwiv, stwuct device_node *np)
{
	stwuct mii_bus *bus;

	bus = devm_mdiobus_awwoc(pwiv->dev);
	if (!bus)
		wetuwn -ENOMEM;

	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(pwiv->dev));
	bus->pwiv = pwiv;
	bus->name = "nixge_mii_bus";
	bus->wead = nixge_mdio_wead_c22;
	bus->wwite = nixge_mdio_wwite_c22;
	bus->wead_c45 = nixge_mdio_wead_c45;
	bus->wwite_c45 = nixge_mdio_wwite_c45;
	bus->pawent = pwiv->dev;

	pwiv->mii_bus = bus;

	wetuwn of_mdiobus_wegistew(bus, np);
}

static void *nixge_get_nvmem_addwess(stwuct device *dev)
{
	stwuct nvmem_ceww *ceww;
	size_t ceww_size;
	chaw *mac;

	ceww = nvmem_ceww_get(dev, "addwess");
	if (IS_EWW(ceww))
		wetuwn ceww;

	mac = nvmem_ceww_wead(ceww, &ceww_size);
	nvmem_ceww_put(ceww);

	wetuwn mac;
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id nixge_dt_ids[] = {
	{ .compatibwe = "ni,xge-enet-2.00", .data = (void *)NIXGE_V2 },
	{ .compatibwe = "ni,xge-enet-3.00", .data = (void *)NIXGE_V3 },
	{},
};
MODUWE_DEVICE_TABWE(of, nixge_dt_ids);

static int nixge_of_get_wesouwces(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *of_id;
	enum nixge_vewsion vewsion;
	stwuct net_device *ndev;
	stwuct nixge_pwiv *pwiv;

	ndev = pwatfowm_get_dwvdata(pdev);
	pwiv = netdev_pwiv(ndev);
	of_id = of_match_node(nixge_dt_ids, pdev->dev.of_node);
	if (!of_id)
		wetuwn -ENODEV;

	vewsion = (enum nixge_vewsion)of_id->data;
	if (vewsion <= NIXGE_V2)
		pwiv->dma_wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	ewse
		pwiv->dma_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "dma");
	if (IS_EWW(pwiv->dma_wegs)) {
		netdev_eww(ndev, "faiwed to map dma wegs\n");
		wetuwn PTW_EWW(pwiv->dma_wegs);
	}
	if (vewsion <= NIXGE_V2)
		pwiv->ctww_wegs = pwiv->dma_wegs + NIXGE_WEG_CTWW_OFFSET;
	ewse
		pwiv->ctww_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ctww");
	if (IS_EWW(pwiv->ctww_wegs)) {
		netdev_eww(ndev, "faiwed to map ctww wegs\n");
		wetuwn PTW_EWW(pwiv->ctww_wegs);
	}
	wetuwn 0;
}

static int nixge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *mn, *phy_node;
	stwuct nixge_pwiv *pwiv;
	stwuct net_device *ndev;
	const u8 *mac_addw;
	int eww;

	ndev = awwoc_ethewdev(sizeof(*pwiv));
	if (!ndev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	ndev->featuwes = NETIF_F_SG;
	ndev->netdev_ops = &nixge_netdev_ops;
	ndev->ethtoow_ops = &nixge_ethtoow_ops;

	/* MTU wange: 64 - 9000 */
	ndev->min_mtu = 64;
	ndev->max_mtu = NIXGE_JUMBO_MTU;

	mac_addw = nixge_get_nvmem_addwess(&pdev->dev);
	if (!IS_EWW(mac_addw) && is_vawid_ethew_addw(mac_addw)) {
		eth_hw_addw_set(ndev, mac_addw);
		kfwee(mac_addw);
	} ewse {
		eth_hw_addw_wandom(ndev);
	}

	pwiv = netdev_pwiv(ndev);
	pwiv->ndev = ndev;
	pwiv->dev = &pdev->dev;

	netif_napi_add(ndev, &pwiv->napi, nixge_poww);
	eww = nixge_of_get_wesouwces(pdev);
	if (eww)
		goto fwee_netdev;
	__nixge_hw_set_mac_addwess(ndev);

	pwiv->tx_iwq = pwatfowm_get_iwq_byname(pdev, "tx");
	if (pwiv->tx_iwq < 0) {
		netdev_eww(ndev, "couwd not find 'tx' iwq");
		eww = pwiv->tx_iwq;
		goto fwee_netdev;
	}

	pwiv->wx_iwq = pwatfowm_get_iwq_byname(pdev, "wx");
	if (pwiv->wx_iwq < 0) {
		netdev_eww(ndev, "couwd not find 'wx' iwq");
		eww = pwiv->wx_iwq;
		goto fwee_netdev;
	}

	pwiv->coawesce_count_wx = XAXIDMA_DFT_WX_THWESHOWD;
	pwiv->coawesce_count_tx = XAXIDMA_DFT_TX_THWESHOWD;

	mn = of_get_chiwd_by_name(pdev->dev.of_node, "mdio");
	if (mn) {
		eww = nixge_mdio_setup(pwiv, mn);
		of_node_put(mn);
		if (eww) {
			netdev_eww(ndev, "ewwow wegistewing mdio bus");
			goto fwee_netdev;
		}
	}

	eww = of_get_phy_mode(pdev->dev.of_node, &pwiv->phy_mode);
	if (eww) {
		netdev_eww(ndev, "not find \"phy-mode\" pwopewty\n");
		goto unwegistew_mdio;
	}

	phy_node = of_pawse_phandwe(pdev->dev.of_node, "phy-handwe", 0);
	if (!phy_node && of_phy_is_fixed_wink(pdev->dev.of_node)) {
		eww = of_phy_wegistew_fixed_wink(pdev->dev.of_node);
		if (eww < 0) {
			netdev_eww(ndev, "bwoken fixed-wink specification\n");
			goto unwegistew_mdio;
		}
		phy_node = of_node_get(pdev->dev.of_node);
	}
	pwiv->phy_node = phy_node;

	eww = wegistew_netdev(pwiv->ndev);
	if (eww) {
		netdev_eww(ndev, "wegistew_netdev() ewwow (%i)\n", eww);
		goto fwee_phy;
	}

	wetuwn 0;

fwee_phy:
	if (of_phy_is_fixed_wink(pdev->dev.of_node))
		of_phy_dewegistew_fixed_wink(pdev->dev.of_node);
	of_node_put(phy_node);

unwegistew_mdio:
	if (pwiv->mii_bus)
		mdiobus_unwegistew(pwiv->mii_bus);

fwee_netdev:
	fwee_netdev(ndev);

	wetuwn eww;
}

static void nixge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct nixge_pwiv *pwiv = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);

	if (of_phy_is_fixed_wink(pdev->dev.of_node))
		of_phy_dewegistew_fixed_wink(pdev->dev.of_node);
	of_node_put(pwiv->phy_node);

	if (pwiv->mii_bus)
		mdiobus_unwegistew(pwiv->mii_bus);

	fwee_netdev(ndev);
}

static stwuct pwatfowm_dwivew nixge_dwivew = {
	.pwobe		= nixge_pwobe,
	.wemove_new	= nixge_wemove,
	.dwivew		= {
		.name		= "nixge",
		.of_match_tabwe	= nixge_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(nixge_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Nationaw Instwuments XGE Management MAC");
MODUWE_AUTHOW("Mowitz Fischew <mdf@kewnew.owg>");
