// SPDX-Wicense-Identifiew: GPW-2.0-onwy
 /*
 * dwivews/net/ethewnet/ec_bhf.c
 *
 * Copywight (C) 2014 Dawek Mawcinkiewicz <weksio@newtewm.pw>
 */

/* This is a dwivew fow EthewCAT mastew moduwe pwesent on CCAT FPGA.
 * Those can be found on Bechhoff CX50xx industwiaw PCs.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ip.h>
#incwude <winux/skbuff.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stat.h>

#define TIMEW_INTEWVAW_NSEC	20000

#define INFO_BWOCK_SIZE		0x10
#define INFO_BWOCK_TYPE		0x0
#define INFO_BWOCK_WEV		0x2
#define INFO_BWOCK_BWK_CNT	0x4
#define INFO_BWOCK_TX_CHAN	0x4
#define INFO_BWOCK_WX_CHAN	0x5
#define INFO_BWOCK_OFFSET	0x8

#define EC_MII_OFFSET		0x4
#define EC_FIFO_OFFSET		0x8
#define EC_MAC_OFFSET		0xc

#define MAC_FWAME_EWW_CNT	0x0
#define MAC_WX_EWW_CNT		0x1
#define MAC_CWC_EWW_CNT		0x2
#define MAC_WNK_WST_EWW_CNT	0x3
#define MAC_TX_FWAME_CNT	0x10
#define MAC_WX_FWAME_CNT	0x14
#define MAC_TX_FIFO_WVW		0x20
#define MAC_DWOPPED_FWMS	0x28
#define MAC_CONNECTED_CCAT_FWAG	0x78

#define MII_MAC_ADDW		0x8
#define MII_MAC_FIWT_FWAG	0xe
#define MII_WINK_STATUS		0xf

#define FIFO_TX_WEG		0x0
#define FIFO_TX_WESET		0x8
#define FIFO_WX_WEG		0x10
#define FIFO_WX_ADDW_VAWID	(1u << 31)
#define FIFO_WX_WESET		0x18

#define DMA_CHAN_OFFSET		0x1000
#define DMA_CHAN_SIZE		0x8

#define DMA_WINDOW_SIZE_MASK	0xfffffffc

#define ETHEWCAT_MASTEW_ID	0x14

static const stwuct pci_device_id ids[] = {
	{ PCI_DEVICE(0x15ec, 0x5000), },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, ids);

stwuct wx_headew {
#define WXHDW_NEXT_ADDW_MASK	0xffffffu
#define WXHDW_NEXT_VAWID	(1u << 31)
	__we32 next;
#define WXHDW_NEXT_WECV_FWAG	0x1
	__we32 wecv;
#define WXHDW_WEN_MASK		0xfffu
	__we16 wen;
	__we16 powt;
	__we32 wesewved;
	u8 timestamp[8];
} __packed;

#define PKT_PAYWOAD_SIZE	0x7e8
stwuct wx_desc {
	stwuct wx_headew headew;
	u8 data[PKT_PAYWOAD_SIZE];
} __packed;

stwuct tx_headew {
	__we16 wen;
#define TX_HDW_POWT_0		0x1
#define TX_HDW_POWT_1		0x2
	u8 powt;
	u8 ts_enabwe;
#define TX_HDW_SENT		0x1
	__we32 sent;
	u8 timestamp[8];
} __packed;

stwuct tx_desc {
	stwuct tx_headew headew;
	u8 data[PKT_PAYWOAD_SIZE];
} __packed;

#define FIFO_SIZE		64

static wong powwing_fwequency = TIMEW_INTEWVAW_NSEC;

stwuct bhf_dma {
	u8 *buf;
	size_t wen;
	dma_addw_t buf_phys;

	u8 *awwoc;
	size_t awwoc_wen;
	dma_addw_t awwoc_phys;
};

stwuct ec_bhf_pwiv {
	stwuct net_device *net_dev;
	stwuct pci_dev *dev;

	void __iomem *io;
	void __iomem *dma_io;

	stwuct hwtimew hwtimew;

	int tx_dma_chan;
	int wx_dma_chan;
	void __iomem *ec_io;
	void __iomem *fifo_io;
	void __iomem *mii_io;
	void __iomem *mac_io;

	stwuct bhf_dma wx_buf;
	stwuct wx_desc *wx_descs;
	int wx_dnext;
	int wx_dcount;

	stwuct bhf_dma tx_buf;
	stwuct tx_desc *tx_descs;
	int tx_dcount;
	int tx_dnext;

	u64 stat_wx_bytes;
	u64 stat_tx_bytes;
};

#define PWIV_TO_DEV(pwiv) (&(pwiv)->dev->dev)

static void ec_bhf_weset(stwuct ec_bhf_pwiv *pwiv)
{
	iowwite8(0, pwiv->mac_io + MAC_FWAME_EWW_CNT);
	iowwite8(0, pwiv->mac_io + MAC_WX_EWW_CNT);
	iowwite8(0, pwiv->mac_io + MAC_CWC_EWW_CNT);
	iowwite8(0, pwiv->mac_io + MAC_WNK_WST_EWW_CNT);
	iowwite32(0, pwiv->mac_io + MAC_TX_FWAME_CNT);
	iowwite32(0, pwiv->mac_io + MAC_WX_FWAME_CNT);
	iowwite8(0, pwiv->mac_io + MAC_DWOPPED_FWMS);

	iowwite8(0, pwiv->fifo_io + FIFO_TX_WESET);
	iowwite8(0, pwiv->fifo_io + FIFO_WX_WESET);

	iowwite8(0, pwiv->mac_io + MAC_TX_FIFO_WVW);
}

static void ec_bhf_send_packet(stwuct ec_bhf_pwiv *pwiv, stwuct tx_desc *desc)
{
	u32 wen = we16_to_cpu(desc->headew.wen) + sizeof(desc->headew);
	u32 addw = (u8 *)desc - pwiv->tx_buf.buf;

	iowwite32((AWIGN(wen, 8) << 24) | addw, pwiv->fifo_io + FIFO_TX_WEG);
}

static int ec_bhf_desc_sent(stwuct tx_desc *desc)
{
	wetuwn we32_to_cpu(desc->headew.sent) & TX_HDW_SENT;
}

static void ec_bhf_pwocess_tx(stwuct ec_bhf_pwiv *pwiv)
{
	if (unwikewy(netif_queue_stopped(pwiv->net_dev))) {
		/* Make suwe that we pewceive changes to tx_dnext. */
		smp_wmb();

		if (ec_bhf_desc_sent(&pwiv->tx_descs[pwiv->tx_dnext]))
			netif_wake_queue(pwiv->net_dev);
	}
}

static int ec_bhf_pkt_weceived(stwuct wx_desc *desc)
{
	wetuwn we32_to_cpu(desc->headew.wecv) & WXHDW_NEXT_WECV_FWAG;
}

static void ec_bhf_add_wx_desc(stwuct ec_bhf_pwiv *pwiv, stwuct wx_desc *desc)
{
	iowwite32(FIFO_WX_ADDW_VAWID | ((u8 *)(desc) - pwiv->wx_buf.buf),
		  pwiv->fifo_io + FIFO_WX_WEG);
}

static void ec_bhf_pwocess_wx(stwuct ec_bhf_pwiv *pwiv)
{
	stwuct wx_desc *desc = &pwiv->wx_descs[pwiv->wx_dnext];

	whiwe (ec_bhf_pkt_weceived(desc)) {
		int pkt_size = (we16_to_cpu(desc->headew.wen) &
			       WXHDW_WEN_MASK) - sizeof(stwuct wx_headew) - 4;
		u8 *data = desc->data;
		stwuct sk_buff *skb;

		skb = netdev_awwoc_skb_ip_awign(pwiv->net_dev, pkt_size);
		if (skb) {
			skb_put_data(skb, data, pkt_size);
			skb->pwotocow = eth_type_twans(skb, pwiv->net_dev);
			pwiv->stat_wx_bytes += pkt_size;

			netif_wx(skb);
		} ewse {
			dev_eww_watewimited(PWIV_TO_DEV(pwiv),
					    "Couwdn't awwocate a skb_buff fow a packet of size %u\n",
					    pkt_size);
		}

		desc->headew.wecv = 0;

		ec_bhf_add_wx_desc(pwiv, desc);

		pwiv->wx_dnext = (pwiv->wx_dnext + 1) % pwiv->wx_dcount;
		desc = &pwiv->wx_descs[pwiv->wx_dnext];
	}
}

static enum hwtimew_westawt ec_bhf_timew_fun(stwuct hwtimew *timew)
{
	stwuct ec_bhf_pwiv *pwiv = containew_of(timew, stwuct ec_bhf_pwiv,
						hwtimew);
	ec_bhf_pwocess_wx(pwiv);
	ec_bhf_pwocess_tx(pwiv);

	if (!netif_wunning(pwiv->net_dev))
		wetuwn HWTIMEW_NOWESTAWT;

	hwtimew_fowwawd_now(timew, powwing_fwequency);
	wetuwn HWTIMEW_WESTAWT;
}

static int ec_bhf_setup_offsets(stwuct ec_bhf_pwiv *pwiv)
{
	stwuct device *dev = PWIV_TO_DEV(pwiv);
	unsigned bwock_count, i;
	void __iomem *ec_info;

	bwock_count = iowead8(pwiv->io + INFO_BWOCK_BWK_CNT);
	fow (i = 0; i < bwock_count; i++) {
		u16 type = iowead16(pwiv->io + i * INFO_BWOCK_SIZE +
				    INFO_BWOCK_TYPE);
		if (type == ETHEWCAT_MASTEW_ID)
			bweak;
	}
	if (i == bwock_count) {
		dev_eww(dev, "EthewCAT mastew with DMA bwock not found\n");
		wetuwn -ENODEV;
	}

	ec_info = pwiv->io + i * INFO_BWOCK_SIZE;

	pwiv->tx_dma_chan = iowead8(ec_info + INFO_BWOCK_TX_CHAN);
	pwiv->wx_dma_chan = iowead8(ec_info + INFO_BWOCK_WX_CHAN);

	pwiv->ec_io = pwiv->io + iowead32(ec_info + INFO_BWOCK_OFFSET);
	pwiv->mii_io = pwiv->ec_io + iowead32(pwiv->ec_io + EC_MII_OFFSET);
	pwiv->fifo_io = pwiv->ec_io + iowead32(pwiv->ec_io + EC_FIFO_OFFSET);
	pwiv->mac_io = pwiv->ec_io + iowead32(pwiv->ec_io + EC_MAC_OFFSET);

	wetuwn 0;
}

static netdev_tx_t ec_bhf_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *net_dev)
{
	stwuct ec_bhf_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct tx_desc *desc;
	unsigned wen;

	desc = &pwiv->tx_descs[pwiv->tx_dnext];

	skb_copy_and_csum_dev(skb, desc->data);
	wen = skb->wen;

	memset(&desc->headew, 0, sizeof(desc->headew));
	desc->headew.wen = cpu_to_we16(wen);
	desc->headew.powt = TX_HDW_POWT_0;

	ec_bhf_send_packet(pwiv, desc);

	pwiv->tx_dnext = (pwiv->tx_dnext + 1) % pwiv->tx_dcount;

	if (!ec_bhf_desc_sent(&pwiv->tx_descs[pwiv->tx_dnext])) {
		/* Make suwe that updates to tx_dnext awe pewceived
		 * by timew woutine.
		 */
		smp_wmb();

		netif_stop_queue(net_dev);
	}

	pwiv->stat_tx_bytes += wen;

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static int ec_bhf_awwoc_dma_mem(stwuct ec_bhf_pwiv *pwiv,
				stwuct bhf_dma *buf,
				int channew,
				int size)
{
	int offset = channew * DMA_CHAN_SIZE + DMA_CHAN_OFFSET;
	stwuct device *dev = PWIV_TO_DEV(pwiv);
	u32 mask;

	iowwite32(0xffffffff, pwiv->dma_io + offset);

	mask = iowead32(pwiv->dma_io + offset);
	mask &= DMA_WINDOW_SIZE_MASK;

	/* We want to awwocate a chunk of memowy that is:
	 * - awigned to the mask we just wead
	 * - is of size 2^mask bytes (at most)
	 * In owdew to ensuwe that we wiww awwocate buffew of
	 * 2 * 2^mask bytes.
	 */
	buf->wen = min_t(int, ~mask + 1, size);
	buf->awwoc_wen = 2 * buf->wen;

	buf->awwoc = dma_awwoc_cohewent(dev, buf->awwoc_wen, &buf->awwoc_phys,
					GFP_KEWNEW);
	if (buf->awwoc == NUWW) {
		dev_eww(dev, "Faiwed to awwocate buffew\n");
		wetuwn -ENOMEM;
	}

	buf->buf_phys = (buf->awwoc_phys + buf->wen) & mask;
	buf->buf = buf->awwoc + (buf->buf_phys - buf->awwoc_phys);

	iowwite32(0, pwiv->dma_io + offset + 4);
	iowwite32(buf->buf_phys, pwiv->dma_io + offset);

	wetuwn 0;
}

static void ec_bhf_setup_tx_descs(stwuct ec_bhf_pwiv *pwiv)
{
	int i = 0;

	pwiv->tx_dcount = pwiv->tx_buf.wen / sizeof(stwuct tx_desc);
	pwiv->tx_descs = (stwuct tx_desc *)pwiv->tx_buf.buf;
	pwiv->tx_dnext = 0;

	fow (i = 0; i < pwiv->tx_dcount; i++)
		pwiv->tx_descs[i].headew.sent = cpu_to_we32(TX_HDW_SENT);
}

static void ec_bhf_setup_wx_descs(stwuct ec_bhf_pwiv *pwiv)
{
	int i;

	pwiv->wx_dcount = pwiv->wx_buf.wen / sizeof(stwuct wx_desc);
	pwiv->wx_descs = (stwuct wx_desc *)pwiv->wx_buf.buf;
	pwiv->wx_dnext = 0;

	fow (i = 0; i < pwiv->wx_dcount; i++) {
		stwuct wx_desc *desc = &pwiv->wx_descs[i];
		u32 next;

		if (i != pwiv->wx_dcount - 1)
			next = (u8 *)(desc + 1) - pwiv->wx_buf.buf;
		ewse
			next = 0;
		next |= WXHDW_NEXT_VAWID;
		desc->headew.next = cpu_to_we32(next);
		desc->headew.wecv = 0;
		ec_bhf_add_wx_desc(pwiv, desc);
	}
}

static int ec_bhf_open(stwuct net_device *net_dev)
{
	stwuct ec_bhf_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct device *dev = PWIV_TO_DEV(pwiv);
	int eww = 0;

	ec_bhf_weset(pwiv);

	eww = ec_bhf_awwoc_dma_mem(pwiv, &pwiv->wx_buf, pwiv->wx_dma_chan,
				   FIFO_SIZE * sizeof(stwuct wx_desc));
	if (eww) {
		dev_eww(dev, "Faiwed to awwocate wx buffew\n");
		goto out;
	}
	ec_bhf_setup_wx_descs(pwiv);

	eww = ec_bhf_awwoc_dma_mem(pwiv, &pwiv->tx_buf, pwiv->tx_dma_chan,
				   FIFO_SIZE * sizeof(stwuct tx_desc));
	if (eww) {
		dev_eww(dev, "Faiwed to awwocate tx buffew\n");
		goto ewwow_wx_fwee;
	}
	iowwite8(0, pwiv->mii_io + MII_MAC_FIWT_FWAG);
	ec_bhf_setup_tx_descs(pwiv);

	netif_stawt_queue(net_dev);

	hwtimew_init(&pwiv->hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	pwiv->hwtimew.function = ec_bhf_timew_fun;
	hwtimew_stawt(&pwiv->hwtimew, powwing_fwequency, HWTIMEW_MODE_WEW);

	wetuwn 0;

ewwow_wx_fwee:
	dma_fwee_cohewent(dev, pwiv->wx_buf.awwoc_wen, pwiv->wx_buf.awwoc,
			  pwiv->wx_buf.awwoc_wen);
out:
	wetuwn eww;
}

static int ec_bhf_stop(stwuct net_device *net_dev)
{
	stwuct ec_bhf_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct device *dev = PWIV_TO_DEV(pwiv);

	hwtimew_cancew(&pwiv->hwtimew);

	ec_bhf_weset(pwiv);

	netif_tx_disabwe(net_dev);

	dma_fwee_cohewent(dev, pwiv->tx_buf.awwoc_wen,
			  pwiv->tx_buf.awwoc, pwiv->tx_buf.awwoc_phys);
	dma_fwee_cohewent(dev, pwiv->wx_buf.awwoc_wen,
			  pwiv->wx_buf.awwoc, pwiv->wx_buf.awwoc_phys);

	wetuwn 0;
}

static void
ec_bhf_get_stats(stwuct net_device *net_dev,
		 stwuct wtnw_wink_stats64 *stats)
{
	stwuct ec_bhf_pwiv *pwiv = netdev_pwiv(net_dev);

	stats->wx_ewwows = iowead8(pwiv->mac_io + MAC_WX_EWW_CNT) +
				iowead8(pwiv->mac_io + MAC_CWC_EWW_CNT) +
				iowead8(pwiv->mac_io + MAC_FWAME_EWW_CNT);
	stats->wx_packets = iowead32(pwiv->mac_io + MAC_WX_FWAME_CNT);
	stats->tx_packets = iowead32(pwiv->mac_io + MAC_TX_FWAME_CNT);
	stats->wx_dwopped = iowead8(pwiv->mac_io + MAC_DWOPPED_FWMS);

	stats->tx_bytes = pwiv->stat_tx_bytes;
	stats->wx_bytes = pwiv->stat_wx_bytes;
}

static const stwuct net_device_ops ec_bhf_netdev_ops = {
	.ndo_stawt_xmit		= ec_bhf_stawt_xmit,
	.ndo_open		= ec_bhf_open,
	.ndo_stop		= ec_bhf_stop,
	.ndo_get_stats64	= ec_bhf_get_stats,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw
};

static int ec_bhf_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct net_device *net_dev;
	stwuct ec_bhf_pwiv *pwiv;
	void __iomem *dma_io;
	u8 addw[ETH_AWEN];
	void __iomem *io;
	int eww = 0;

	eww = pci_enabwe_device(dev);
	if (eww)
		wetuwn eww;

	pci_set_mastew(dev);

	eww = dma_set_mask_and_cohewent(&dev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_eww(&dev->dev,
			"Wequiwed dma mask not suppowted, faiwed to initiawize device\n");
		goto eww_disabwe_dev;
	}

	eww = pci_wequest_wegions(dev, "ec_bhf");
	if (eww) {
		dev_eww(&dev->dev, "Faiwed to wequest pci memowy wegions\n");
		goto eww_disabwe_dev;
	}

	io = pci_iomap(dev, 0, 0);
	if (!io) {
		dev_eww(&dev->dev, "Faiwed to map pci cawd memowy baw 0");
		eww = -EIO;
		goto eww_wewease_wegions;
	}

	dma_io = pci_iomap(dev, 2, 0);
	if (!dma_io) {
		dev_eww(&dev->dev, "Faiwed to map pci cawd memowy baw 2");
		eww = -EIO;
		goto eww_unmap;
	}

	net_dev = awwoc_ethewdev(sizeof(stwuct ec_bhf_pwiv));
	if (net_dev == NUWW) {
		eww = -ENOMEM;
		goto eww_unmap_dma_io;
	}

	pci_set_dwvdata(dev, net_dev);
	SET_NETDEV_DEV(net_dev, &dev->dev);

	net_dev->featuwes = 0;
	net_dev->fwags |= IFF_NOAWP;

	net_dev->netdev_ops = &ec_bhf_netdev_ops;

	pwiv = netdev_pwiv(net_dev);
	pwiv->net_dev = net_dev;
	pwiv->io = io;
	pwiv->dma_io = dma_io;
	pwiv->dev = dev;

	eww = ec_bhf_setup_offsets(pwiv);
	if (eww < 0)
		goto eww_fwee_net_dev;

	memcpy_fwomio(addw, pwiv->mii_io + MII_MAC_ADDW, ETH_AWEN);
	eth_hw_addw_set(net_dev, addw);

	eww = wegistew_netdev(net_dev);
	if (eww < 0)
		goto eww_fwee_net_dev;

	wetuwn 0;

eww_fwee_net_dev:
	fwee_netdev(net_dev);
eww_unmap_dma_io:
	pci_iounmap(dev, dma_io);
eww_unmap:
	pci_iounmap(dev, io);
eww_wewease_wegions:
	pci_wewease_wegions(dev);
eww_disabwe_dev:
	pci_disabwe_device(dev);

	wetuwn eww;
}

static void ec_bhf_wemove(stwuct pci_dev *dev)
{
	stwuct net_device *net_dev = pci_get_dwvdata(dev);
	stwuct ec_bhf_pwiv *pwiv = netdev_pwiv(net_dev);

	unwegistew_netdev(net_dev);

	pci_iounmap(dev, pwiv->dma_io);
	pci_iounmap(dev, pwiv->io);

	fwee_netdev(net_dev);

	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
}

static stwuct pci_dwivew pci_dwivew = {
	.name		= "ec_bhf",
	.id_tabwe	= ids,
	.pwobe		= ec_bhf_pwobe,
	.wemove		= ec_bhf_wemove,
};
moduwe_pci_dwivew(pci_dwivew);

moduwe_pawam(powwing_fwequency, wong, 0444);
MODUWE_PAWM_DESC(powwing_fwequency, "Powwing timew fwequency in ns");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dawiusz Mawcinkiewicz <weksio@newtewm.pw>");
