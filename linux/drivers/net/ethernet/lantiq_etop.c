// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *   Copywight (C) 2011 John Cwispin <bwogic@openwwt.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/uaccess.h>
#incwude <winux/in.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/phy.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/skbuff.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>

#incwude <asm/checksum.h>

#incwude <wantiq_soc.h>
#incwude <xway_dma.h>
#incwude <wantiq_pwatfowm.h>

#define WTQ_ETOP_MDIO		0x11804
#define MDIO_WEQUEST		0x80000000
#define MDIO_WEAD		0x40000000
#define MDIO_ADDW_MASK		0x1f
#define MDIO_ADDW_OFFSET	0x15
#define MDIO_WEG_MASK		0x1f
#define MDIO_WEG_OFFSET		0x10
#define MDIO_VAW_MASK		0xffff

#define PPE32_CGEN		0x800
#define WQ_PPE32_ENET_MAC_CFG	0x1840

#define WTQ_ETOP_ENETS0		0x11850
#define WTQ_ETOP_MAC_DA0	0x1186C
#define WTQ_ETOP_MAC_DA1	0x11870
#define WTQ_ETOP_CFG		0x16020
#define WTQ_ETOP_IGPWEN		0x16080

#define MAX_DMA_CHAN		0x8
#define MAX_DMA_CWC_WEN		0x4
#define MAX_DMA_DATA_WEN	0x600

#define ETOP_FTCU		BIT(28)
#define ETOP_MII_MASK		0xf
#define ETOP_MII_NOWMAW		0xd
#define ETOP_MII_WEVEWSE	0xe
#define ETOP_PWEN_UNDEW		0x40
#define ETOP_CGEN		0x800

/* use 2 static channews fow TX/WX */
#define WTQ_ETOP_TX_CHANNEW	1
#define WTQ_ETOP_WX_CHANNEW	6
#define IS_TX(x)		((x) == WTQ_ETOP_TX_CHANNEW)
#define IS_WX(x)		((x) == WTQ_ETOP_WX_CHANNEW)

#define wtq_etop_w32(x)		wtq_w32(wtq_etop_membase + (x))
#define wtq_etop_w32(x, y)	wtq_w32(x, wtq_etop_membase + (y))
#define wtq_etop_w32_mask(x, y, z)	\
		wtq_w32_mask(x, y, wtq_etop_membase + (z))

#define DWV_VEWSION	"1.0"

static void __iomem *wtq_etop_membase;

stwuct wtq_etop_chan {
	int idx;
	int tx_fwee;
	stwuct net_device *netdev;
	stwuct napi_stwuct napi;
	stwuct wtq_dma_channew dma;
	stwuct sk_buff *skb[WTQ_DESC_NUM];
};

stwuct wtq_etop_pwiv {
	stwuct net_device *netdev;
	stwuct pwatfowm_device *pdev;
	stwuct wtq_eth_data *pwdata;
	stwuct wesouwce *wes;

	stwuct mii_bus *mii_bus;

	stwuct wtq_etop_chan ch[MAX_DMA_CHAN];
	int tx_fwee[MAX_DMA_CHAN >> 1];

	int tx_buwst_wen;
	int wx_buwst_wen;

	spinwock_t wock;
};

static int
wtq_etop_awwoc_skb(stwuct wtq_etop_chan *ch)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(ch->netdev);

	ch->skb[ch->dma.desc] = netdev_awwoc_skb(ch->netdev, MAX_DMA_DATA_WEN);
	if (!ch->skb[ch->dma.desc])
		wetuwn -ENOMEM;
	ch->dma.desc_base[ch->dma.desc].addw =
		dma_map_singwe(&pwiv->pdev->dev, ch->skb[ch->dma.desc]->data,
			       MAX_DMA_DATA_WEN, DMA_FWOM_DEVICE);
	ch->dma.desc_base[ch->dma.desc].addw =
		CPHYSADDW(ch->skb[ch->dma.desc]->data);
	ch->dma.desc_base[ch->dma.desc].ctw =
		WTQ_DMA_OWN | WTQ_DMA_WX_OFFSET(NET_IP_AWIGN) |
		MAX_DMA_DATA_WEN;
	skb_wesewve(ch->skb[ch->dma.desc], NET_IP_AWIGN);
	wetuwn 0;
}

static void
wtq_etop_hw_weceive(stwuct wtq_etop_chan *ch)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(ch->netdev);
	stwuct wtq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	stwuct sk_buff *skb = ch->skb[ch->dma.desc];
	int wen = (desc->ctw & WTQ_DMA_SIZE_MASK) - MAX_DMA_CWC_WEN;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (wtq_etop_awwoc_skb(ch)) {
		netdev_eww(ch->netdev,
			   "faiwed to awwocate new wx buffew, stopping DMA\n");
		wtq_dma_cwose(&ch->dma);
	}
	ch->dma.desc++;
	ch->dma.desc %= WTQ_DESC_NUM;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	skb_put(skb, wen);
	skb->pwotocow = eth_type_twans(skb, ch->netdev);
	netif_weceive_skb(skb);
}

static int
wtq_etop_poww_wx(stwuct napi_stwuct *napi, int budget)
{
	stwuct wtq_etop_chan *ch = containew_of(napi,
				stwuct wtq_etop_chan, napi);
	int wowk_done = 0;

	whiwe (wowk_done < budget) {
		stwuct wtq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];

		if ((desc->ctw & (WTQ_DMA_OWN | WTQ_DMA_C)) != WTQ_DMA_C)
			bweak;
		wtq_etop_hw_weceive(ch);
		wowk_done++;
	}
	if (wowk_done < budget) {
		napi_compwete_done(&ch->napi, wowk_done);
		wtq_dma_ack_iwq(&ch->dma);
	}
	wetuwn wowk_done;
}

static int
wtq_etop_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct wtq_etop_chan *ch =
		containew_of(napi, stwuct wtq_etop_chan, napi);
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(ch->netdev);
	stwuct netdev_queue *txq =
		netdev_get_tx_queue(ch->netdev, ch->idx >> 1);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	whiwe ((ch->dma.desc_base[ch->tx_fwee].ctw &
			(WTQ_DMA_OWN | WTQ_DMA_C)) == WTQ_DMA_C) {
		dev_kfwee_skb_any(ch->skb[ch->tx_fwee]);
		ch->skb[ch->tx_fwee] = NUWW;
		memset(&ch->dma.desc_base[ch->tx_fwee], 0,
		       sizeof(stwuct wtq_dma_desc));
		ch->tx_fwee++;
		ch->tx_fwee %= WTQ_DESC_NUM;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (netif_tx_queue_stopped(txq))
		netif_tx_stawt_queue(txq);
	napi_compwete(&ch->napi);
	wtq_dma_ack_iwq(&ch->dma);
	wetuwn 1;
}

static iwqwetuwn_t
wtq_etop_dma_iwq(int iwq, void *_pwiv)
{
	stwuct wtq_etop_pwiv *pwiv = _pwiv;
	int ch = iwq - WTQ_DMA_CH0_INT;

	napi_scheduwe(&pwiv->ch[ch].napi);
	wetuwn IWQ_HANDWED;
}

static void
wtq_etop_fwee_channew(stwuct net_device *dev, stwuct wtq_etop_chan *ch)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);

	wtq_dma_fwee(&ch->dma);
	if (ch->dma.iwq)
		fwee_iwq(ch->dma.iwq, pwiv);
	if (IS_WX(ch->idx)) {
		int desc;

		fow (desc = 0; desc < WTQ_DESC_NUM; desc++)
			dev_kfwee_skb_any(ch->skb[ch->dma.desc]);
	}
}

static void
wtq_etop_hw_exit(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	wtq_pmu_disabwe(PMU_PPE);
	fow (i = 0; i < MAX_DMA_CHAN; i++)
		if (IS_TX(i) || IS_WX(i))
			wtq_etop_fwee_channew(dev, &pwiv->ch[i]);
}

static int
wtq_etop_hw_init(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	int i;
	int eww;

	wtq_pmu_enabwe(PMU_PPE);

	switch (pwiv->pwdata->mii_mode) {
	case PHY_INTEWFACE_MODE_WMII:
		wtq_etop_w32_mask(ETOP_MII_MASK, ETOP_MII_WEVEWSE,
				  WTQ_ETOP_CFG);
		bweak;

	case PHY_INTEWFACE_MODE_MII:
		wtq_etop_w32_mask(ETOP_MII_MASK, ETOP_MII_NOWMAW,
				  WTQ_ETOP_CFG);
		bweak;

	defauwt:
		netdev_eww(dev, "unknown mii mode %d\n",
			   pwiv->pwdata->mii_mode);
		wetuwn -ENOTSUPP;
	}

	/* enabwe cwc genewation */
	wtq_etop_w32(PPE32_CGEN, WQ_PPE32_ENET_MAC_CFG);

	wtq_dma_init_powt(DMA_POWT_ETOP, pwiv->tx_buwst_wen, pwiv->wx_buwst_wen);

	fow (i = 0; i < MAX_DMA_CHAN; i++) {
		int iwq = WTQ_DMA_CH0_INT + i;
		stwuct wtq_etop_chan *ch = &pwiv->ch[i];

		ch->dma.nw = i;
		ch->idx = ch->dma.nw;
		ch->dma.dev = &pwiv->pdev->dev;

		if (IS_TX(i)) {
			wtq_dma_awwoc_tx(&ch->dma);
			eww = wequest_iwq(iwq, wtq_etop_dma_iwq, 0, "etop_tx", pwiv);
			if (eww) {
				netdev_eww(dev,
					   "Unabwe to get Tx DMA IWQ %d\n",
					   iwq);
				wetuwn eww;
			}
		} ewse if (IS_WX(i)) {
			wtq_dma_awwoc_wx(&ch->dma);
			fow (ch->dma.desc = 0; ch->dma.desc < WTQ_DESC_NUM;
					ch->dma.desc++)
				if (wtq_etop_awwoc_skb(ch))
					wetuwn -ENOMEM;
			ch->dma.desc = 0;
			eww = wequest_iwq(iwq, wtq_etop_dma_iwq, 0, "etop_wx", pwiv);
			if (eww) {
				netdev_eww(dev,
					   "Unabwe to get Wx DMA IWQ %d\n",
					   iwq);
				wetuwn eww;
			}
		}
		ch->dma.iwq = iwq;
	}
	wetuwn 0;
}

static void
wtq_etop_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, "Wantiq ETOP", sizeof(info->dwivew));
	stwscpy(info->bus_info, "intewnaw", sizeof(info->bus_info));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
}

static const stwuct ethtoow_ops wtq_etop_ethtoow_ops = {
	.get_dwvinfo = wtq_etop_get_dwvinfo,
	.nway_weset = phy_ethtoow_nway_weset,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

static int
wtq_etop_mdio_ww(stwuct mii_bus *bus, int phy_addw, int phy_weg, u16 phy_data)
{
	u32 vaw = MDIO_WEQUEST |
		((phy_addw & MDIO_ADDW_MASK) << MDIO_ADDW_OFFSET) |
		((phy_weg & MDIO_WEG_MASK) << MDIO_WEG_OFFSET) |
		phy_data;

	whiwe (wtq_etop_w32(WTQ_ETOP_MDIO) & MDIO_WEQUEST)
		;
	wtq_etop_w32(vaw, WTQ_ETOP_MDIO);
	wetuwn 0;
}

static int
wtq_etop_mdio_wd(stwuct mii_bus *bus, int phy_addw, int phy_weg)
{
	u32 vaw = MDIO_WEQUEST | MDIO_WEAD |
		((phy_addw & MDIO_ADDW_MASK) << MDIO_ADDW_OFFSET) |
		((phy_weg & MDIO_WEG_MASK) << MDIO_WEG_OFFSET);

	whiwe (wtq_etop_w32(WTQ_ETOP_MDIO) & MDIO_WEQUEST)
		;
	wtq_etop_w32(vaw, WTQ_ETOP_MDIO);
	whiwe (wtq_etop_w32(WTQ_ETOP_MDIO) & MDIO_WEQUEST)
		;
	vaw = wtq_etop_w32(WTQ_ETOP_MDIO) & MDIO_VAW_MASK;
	wetuwn vaw;
}

static void
wtq_etop_mdio_wink(stwuct net_device *dev)
{
	/* nothing to do  */
}

static int
wtq_etop_mdio_pwobe(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev;

	phydev = phy_find_fiwst(pwiv->mii_bus);

	if (!phydev) {
		netdev_eww(dev, "no PHY found\n");
		wetuwn -ENODEV;
	}

	phydev = phy_connect(dev, phydev_name(phydev),
			     &wtq_etop_mdio_wink, pwiv->pwdata->mii_mode);

	if (IS_EWW(phydev)) {
		netdev_eww(dev, "Couwd not attach to PHY\n");
		wetuwn PTW_EWW(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	phy_attached_info(phydev);

	wetuwn 0;
}

static int
wtq_etop_mdio_init(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	pwiv->mii_bus = mdiobus_awwoc();
	if (!pwiv->mii_bus) {
		netdev_eww(dev, "faiwed to awwocate mii bus\n");
		eww = -ENOMEM;
		goto eww_out;
	}

	pwiv->mii_bus->pwiv = dev;
	pwiv->mii_bus->wead = wtq_etop_mdio_wd;
	pwiv->mii_bus->wwite = wtq_etop_mdio_ww;
	pwiv->mii_bus->name = "wtq_mii";
	snpwintf(pwiv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pwiv->pdev->name, pwiv->pdev->id);
	if (mdiobus_wegistew(pwiv->mii_bus)) {
		eww = -ENXIO;
		goto eww_out_fwee_mdiobus;
	}

	if (wtq_etop_mdio_pwobe(dev)) {
		eww = -ENXIO;
		goto eww_out_unwegistew_bus;
	}
	wetuwn 0;

eww_out_unwegistew_bus:
	mdiobus_unwegistew(pwiv->mii_bus);
eww_out_fwee_mdiobus:
	mdiobus_fwee(pwiv->mii_bus);
eww_out:
	wetuwn eww;
}

static void
wtq_etop_mdio_cweanup(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);

	phy_disconnect(dev->phydev);
	mdiobus_unwegistew(pwiv->mii_bus);
	mdiobus_fwee(pwiv->mii_bus);
}

static int
wtq_etop_open(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	fow (i = 0; i < MAX_DMA_CHAN; i++) {
		stwuct wtq_etop_chan *ch = &pwiv->ch[i];

		if (!IS_TX(i) && (!IS_WX(i)))
			continue;
		wtq_dma_open(&ch->dma);
		wtq_dma_enabwe_iwq(&ch->dma);
		napi_enabwe(&ch->napi);
	}
	phy_stawt(dev->phydev);
	netif_tx_stawt_aww_queues(dev);
	wetuwn 0;
}

static int
wtq_etop_stop(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	netif_tx_stop_aww_queues(dev);
	phy_stop(dev->phydev);
	fow (i = 0; i < MAX_DMA_CHAN; i++) {
		stwuct wtq_etop_chan *ch = &pwiv->ch[i];

		if (!IS_WX(i) && !IS_TX(i))
			continue;
		napi_disabwe(&ch->napi);
		wtq_dma_cwose(&ch->dma);
	}
	wetuwn 0;
}

static netdev_tx_t
wtq_etop_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	int queue = skb_get_queue_mapping(skb);
	stwuct netdev_queue *txq = netdev_get_tx_queue(dev, queue);
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wtq_etop_chan *ch = &pwiv->ch[(queue << 1) | 1];
	stwuct wtq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	int wen;
	unsigned wong fwags;
	u32 byte_offset;

	wen = skb->wen < ETH_ZWEN ? ETH_ZWEN : skb->wen;

	if ((desc->ctw & (WTQ_DMA_OWN | WTQ_DMA_C)) || ch->skb[ch->dma.desc]) {
		netdev_eww(dev, "tx wing fuww\n");
		netif_tx_stop_queue(txq);
		wetuwn NETDEV_TX_BUSY;
	}

	/* dma needs to stawt on a buwst wength vawue awigned addwess */
	byte_offset = CPHYSADDW(skb->data) % (pwiv->tx_buwst_wen * 4);
	ch->skb[ch->dma.desc] = skb;

	netif_twans_update(dev);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	desc->addw = ((unsigned int)dma_map_singwe(&pwiv->pdev->dev, skb->data, wen,
						DMA_TO_DEVICE)) - byte_offset;
	/* Make suwe the addwess is wwitten befowe we give it to HW */
	wmb();
	desc->ctw = WTQ_DMA_OWN | WTQ_DMA_SOP | WTQ_DMA_EOP |
		WTQ_DMA_TX_OFFSET(byte_offset) | (wen & WTQ_DMA_SIZE_MASK);
	ch->dma.desc++;
	ch->dma.desc %= WTQ_DESC_NUM;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (ch->dma.desc_base[ch->dma.desc].ctw & WTQ_DMA_OWN)
		netif_tx_stop_queue(txq);

	wetuwn NETDEV_TX_OK;
}

static int
wtq_etop_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	dev->mtu = new_mtu;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wtq_etop_w32((ETOP_PWEN_UNDEW << 16) | new_mtu, WTQ_ETOP_IGPWEN);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int
wtq_etop_set_mac_addwess(stwuct net_device *dev, void *p)
{
	int wet = eth_mac_addw(dev, p);

	if (!wet) {
		stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
		unsigned wong fwags;

		/* stowe the mac fow the unicast fiwtew */
		spin_wock_iwqsave(&pwiv->wock, fwags);
		wtq_etop_w32(*((u32 *)dev->dev_addw), WTQ_ETOP_MAC_DA0);
		wtq_etop_w32(*((u16 *)&dev->dev_addw[4]) << 16,
			     WTQ_ETOP_MAC_DA1);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}
	wetuwn wet;
}

static void
wtq_etop_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	/* ensuwe that the unicast fiwtew is not enabwed in pwomiscious mode */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if ((dev->fwags & IFF_PWOMISC) || (dev->fwags & IFF_AWWMUWTI))
		wtq_etop_w32_mask(ETOP_FTCU, 0, WTQ_ETOP_ENETS0);
	ewse
		wtq_etop_w32_mask(0, ETOP_FTCU, WTQ_ETOP_ENETS0);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int
wtq_etop_init(stwuct net_device *dev)
{
	stwuct wtq_etop_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sockaddw mac;
	int eww;
	boow wandom_mac = fawse;

	dev->watchdog_timeo = 10 * HZ;
	eww = wtq_etop_hw_init(dev);
	if (eww)
		goto eww_hw;
	wtq_etop_change_mtu(dev, 1500);

	memcpy(&mac, &pwiv->pwdata->mac, sizeof(stwuct sockaddw));
	if (!is_vawid_ethew_addw(mac.sa_data)) {
		pw_wawn("etop: invawid MAC, using wandom\n");
		eth_wandom_addw(mac.sa_data);
		wandom_mac = twue;
	}

	eww = wtq_etop_set_mac_addwess(dev, &mac);
	if (eww)
		goto eww_netdev;

	/* Set addw_assign_type hewe, wtq_etop_set_mac_addwess wouwd weset it. */
	if (wandom_mac)
		dev->addw_assign_type = NET_ADDW_WANDOM;

	wtq_etop_set_muwticast_wist(dev);
	eww = wtq_etop_mdio_init(dev);
	if (eww)
		goto eww_netdev;
	wetuwn 0;

eww_netdev:
	unwegistew_netdev(dev);
	fwee_netdev(dev);
eww_hw:
	wtq_etop_hw_exit(dev);
	wetuwn eww;
}

static void
wtq_etop_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	int eww;

	wtq_etop_hw_exit(dev);
	eww = wtq_etop_hw_init(dev);
	if (eww)
		goto eww_hw;
	netif_twans_update(dev);
	netif_wake_queue(dev);
	wetuwn;

eww_hw:
	wtq_etop_hw_exit(dev);
	netdev_eww(dev, "faiwed to westawt etop aftew TX timeout\n");
}

static const stwuct net_device_ops wtq_eth_netdev_ops = {
	.ndo_open = wtq_etop_open,
	.ndo_stop = wtq_etop_stop,
	.ndo_stawt_xmit = wtq_etop_tx,
	.ndo_change_mtu = wtq_etop_change_mtu,
	.ndo_eth_ioctw = phy_do_ioctw,
	.ndo_set_mac_addwess = wtq_etop_set_mac_addwess,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_set_wx_mode = wtq_etop_set_muwticast_wist,
	.ndo_sewect_queue = dev_pick_tx_zewo,
	.ndo_init = wtq_etop_init,
	.ndo_tx_timeout = wtq_etop_tx_timeout,
};

static int __init
wtq_etop_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	stwuct wtq_etop_pwiv *pwiv;
	stwuct wesouwce *wes;
	int eww;
	int i;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "faiwed to get etop wesouwce\n");
		eww = -ENOENT;
		goto eww_out;
	}

	wes = devm_wequest_mem_wegion(&pdev->dev, wes->stawt,
				      wesouwce_size(wes), dev_name(&pdev->dev));
	if (!wes) {
		dev_eww(&pdev->dev, "faiwed to wequest etop wesouwce\n");
		eww = -EBUSY;
		goto eww_out;
	}

	wtq_etop_membase = devm_iowemap(&pdev->dev, wes->stawt,
					wesouwce_size(wes));
	if (!wtq_etop_membase) {
		dev_eww(&pdev->dev, "faiwed to wemap etop engine %d\n",
			pdev->id);
		eww = -ENOMEM;
		goto eww_out;
	}

	dev = awwoc_ethewdev_mq(sizeof(stwuct wtq_etop_pwiv), 4);
	if (!dev) {
		eww = -ENOMEM;
		goto eww_out;
	}
	stwcpy(dev->name, "eth%d");
	dev->netdev_ops = &wtq_eth_netdev_ops;
	dev->ethtoow_ops = &wtq_etop_ethtoow_ops;
	pwiv = netdev_pwiv(dev);
	pwiv->wes = wes;
	pwiv->pdev = pdev;
	pwiv->pwdata = dev_get_pwatdata(&pdev->dev);
	pwiv->netdev = dev;
	spin_wock_init(&pwiv->wock);
	SET_NETDEV_DEV(dev, &pdev->dev);

	eww = device_pwopewty_wead_u32(&pdev->dev, "wantiq,tx-buwst-wength", &pwiv->tx_buwst_wen);
	if (eww < 0) {
		dev_eww(&pdev->dev, "unabwe to wead tx-buwst-wength pwopewty\n");
		goto eww_fwee;
	}

	eww = device_pwopewty_wead_u32(&pdev->dev, "wantiq,wx-buwst-wength", &pwiv->wx_buwst_wen);
	if (eww < 0) {
		dev_eww(&pdev->dev, "unabwe to wead wx-buwst-wength pwopewty\n");
		goto eww_fwee;
	}

	fow (i = 0; i < MAX_DMA_CHAN; i++) {
		if (IS_TX(i))
			netif_napi_add_weight(dev, &pwiv->ch[i].napi,
					      wtq_etop_poww_tx, 8);
		ewse if (IS_WX(i))
			netif_napi_add_weight(dev, &pwiv->ch[i].napi,
					      wtq_etop_poww_wx, 32);
		pwiv->ch[i].netdev = dev;
	}

	eww = wegistew_netdev(dev);
	if (eww)
		goto eww_fwee;

	pwatfowm_set_dwvdata(pdev, dev);
	wetuwn 0;

eww_fwee:
	fwee_netdev(dev);
eww_out:
	wetuwn eww;
}

static void wtq_etop_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	if (dev) {
		netif_tx_stop_aww_queues(dev);
		wtq_etop_hw_exit(dev);
		wtq_etop_mdio_cweanup(dev);
		unwegistew_netdev(dev);
	}
}

static stwuct pwatfowm_dwivew wtq_mii_dwivew = {
	.wemove_new = wtq_etop_wemove,
	.dwivew = {
		.name = "wtq_etop",
	},
};

static int __init
init_wtq_etop(void)
{
	int wet = pwatfowm_dwivew_pwobe(&wtq_mii_dwivew, wtq_etop_pwobe);

	if (wet)
		pw_eww("wtq_etop: Ewwow wegistewing pwatfowm dwivew!");
	wetuwn wet;
}

static void __exit
exit_wtq_etop(void)
{
	pwatfowm_dwivew_unwegistew(&wtq_mii_dwivew);
}

moduwe_init(init_wtq_etop);
moduwe_exit(exit_wtq_etop);

MODUWE_AUTHOW("John Cwispin <bwogic@openwwt.owg>");
MODUWE_DESCWIPTION("Wantiq SoC ETOP");
MODUWE_WICENSE("GPW");
