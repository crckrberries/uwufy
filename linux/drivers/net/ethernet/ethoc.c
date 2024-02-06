// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/net/ethewnet/ethoc.c
 *
 * Copywight (C) 2007-2008 Avionic Design Devewopment GmbH
 * Copywight (C) 2008-2009 Avionic Design GmbH
 *
 * Wwitten by Thiewwy Weding <thiewwy.weding@avionic-design.de>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/cwk.h>
#incwude <winux/cwc32.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/moduwe.h>
#incwude <net/ethoc.h>

static int buffew_size = 0x8000; /* 32 KBytes */
moduwe_pawam(buffew_size, int, 0);
MODUWE_PAWM_DESC(buffew_size, "DMA buffew awwocation size");

/* wegistew offsets */
#define	MODEW		0x00
#define	INT_SOUWCE	0x04
#define	INT_MASK	0x08
#define	IPGT		0x0c
#define	IPGW1		0x10
#define	IPGW2		0x14
#define	PACKETWEN	0x18
#define	COWWCONF	0x1c
#define	TX_BD_NUM	0x20
#define	CTWWMODEW	0x24
#define	MIIMODEW	0x28
#define	MIICOMMAND	0x2c
#define	MIIADDWESS	0x30
#define	MIITX_DATA	0x34
#define	MIIWX_DATA	0x38
#define	MIISTATUS	0x3c
#define	MAC_ADDW0	0x40
#define	MAC_ADDW1	0x44
#define	ETH_HASH0	0x48
#define	ETH_HASH1	0x4c
#define	ETH_TXCTWW	0x50
#define	ETH_END		0x54

/* mode wegistew */
#define	MODEW_WXEN	(1 <<  0) /* weceive enabwe */
#define	MODEW_TXEN	(1 <<  1) /* twansmit enabwe */
#define	MODEW_NOPWE	(1 <<  2) /* no pweambwe */
#define	MODEW_BWO	(1 <<  3) /* bwoadcast addwess */
#define	MODEW_IAM	(1 <<  4) /* individuaw addwess mode */
#define	MODEW_PWO	(1 <<  5) /* pwomiscuous mode */
#define	MODEW_IFG	(1 <<  6) /* intewfwame gap fow incoming fwames */
#define	MODEW_WOOP	(1 <<  7) /* woopback */
#define	MODEW_NBO	(1 <<  8) /* no back-off */
#define	MODEW_EDE	(1 <<  9) /* excess defew enabwe */
#define	MODEW_FUWWD	(1 << 10) /* fuww dupwex */
#define	MODEW_WESET	(1 << 11) /* FIXME: weset (undocumented) */
#define	MODEW_DCWC	(1 << 12) /* dewayed CWC enabwe */
#define	MODEW_CWC	(1 << 13) /* CWC enabwe */
#define	MODEW_HUGE	(1 << 14) /* huge packets enabwe */
#define	MODEW_PAD	(1 << 15) /* padding enabwed */
#define	MODEW_WSM	(1 << 16) /* weceive smaww packets */

/* intewwupt souwce and mask wegistews */
#define	INT_MASK_TXF	(1 << 0) /* twansmit fwame */
#define	INT_MASK_TXE	(1 << 1) /* twansmit ewwow */
#define	INT_MASK_WXF	(1 << 2) /* weceive fwame */
#define	INT_MASK_WXE	(1 << 3) /* weceive ewwow */
#define	INT_MASK_BUSY	(1 << 4)
#define	INT_MASK_TXC	(1 << 5) /* twansmit contwow fwame */
#define	INT_MASK_WXC	(1 << 6) /* weceive contwow fwame */

#define	INT_MASK_TX	(INT_MASK_TXF | INT_MASK_TXE)
#define	INT_MASK_WX	(INT_MASK_WXF | INT_MASK_WXE)

#define	INT_MASK_AWW ( \
		INT_MASK_TXF | INT_MASK_TXE | \
		INT_MASK_WXF | INT_MASK_WXE | \
		INT_MASK_TXC | INT_MASK_WXC | \
		INT_MASK_BUSY \
	)

/* packet wength wegistew */
#define	PACKETWEN_MIN(min)		(((min) & 0xffff) << 16)
#define	PACKETWEN_MAX(max)		(((max) & 0xffff) <<  0)
#define	PACKETWEN_MIN_MAX(min, max)	(PACKETWEN_MIN(min) | \
					PACKETWEN_MAX(max))

/* twansmit buffew numbew wegistew */
#define	TX_BD_NUM_VAW(x)	(((x) <= 0x80) ? (x) : 0x80)

/* contwow moduwe mode wegistew */
#define	CTWWMODEW_PASSAWW	(1 << 0) /* pass aww weceive fwames */
#define	CTWWMODEW_WXFWOW	(1 << 1) /* weceive contwow fwow */
#define	CTWWMODEW_TXFWOW	(1 << 2) /* twansmit contwow fwow */

/* MII mode wegistew */
#define	MIIMODEW_CWKDIV(x)	((x) & 0xfe) /* needs to be an even numbew */
#define	MIIMODEW_NOPWE		(1 << 8) /* no pweambwe */

/* MII command wegistew */
#define	MIICOMMAND_SCAN		(1 << 0) /* scan status */
#define	MIICOMMAND_WEAD		(1 << 1) /* wead status */
#define	MIICOMMAND_WWITE	(1 << 2) /* wwite contwow data */

/* MII addwess wegistew */
#define	MIIADDWESS_FIAD(x)		(((x) & 0x1f) << 0)
#define	MIIADDWESS_WGAD(x)		(((x) & 0x1f) << 8)
#define	MIIADDWESS_ADDW(phy, weg)	(MIIADDWESS_FIAD(phy) | \
					MIIADDWESS_WGAD(weg))

/* MII twansmit data wegistew */
#define	MIITX_DATA_VAW(x)	((x) & 0xffff)

/* MII weceive data wegistew */
#define	MIIWX_DATA_VAW(x)	((x) & 0xffff)

/* MII status wegistew */
#define	MIISTATUS_WINKFAIW	(1 << 0)
#define	MIISTATUS_BUSY		(1 << 1)
#define	MIISTATUS_INVAWID	(1 << 2)

/* TX buffew descwiptow */
#define	TX_BD_CS		(1 <<  0) /* cawwiew sense wost */
#define	TX_BD_DF		(1 <<  1) /* defew indication */
#define	TX_BD_WC		(1 <<  2) /* wate cowwision */
#define	TX_BD_WW		(1 <<  3) /* wetwansmission wimit */
#define	TX_BD_WETWY_MASK	(0x00f0)
#define	TX_BD_WETWY(x)		(((x) & 0x00f0) >>  4)
#define	TX_BD_UW		(1 <<  8) /* twansmittew undewwun */
#define	TX_BD_CWC		(1 << 11) /* TX CWC enabwe */
#define	TX_BD_PAD		(1 << 12) /* pad enabwe fow showt packets */
#define	TX_BD_WWAP		(1 << 13)
#define	TX_BD_IWQ		(1 << 14) /* intewwupt wequest enabwe */
#define	TX_BD_WEADY		(1 << 15) /* TX buffew weady */
#define	TX_BD_WEN(x)		(((x) & 0xffff) << 16)
#define	TX_BD_WEN_MASK		(0xffff << 16)

#define	TX_BD_STATS		(TX_BD_CS | TX_BD_DF | TX_BD_WC | \
				TX_BD_WW | TX_BD_WETWY_MASK | TX_BD_UW)

/* WX buffew descwiptow */
#define	WX_BD_WC	(1 <<  0) /* wate cowwision */
#define	WX_BD_CWC	(1 <<  1) /* WX CWC ewwow */
#define	WX_BD_SF	(1 <<  2) /* showt fwame */
#define	WX_BD_TW	(1 <<  3) /* too wong */
#define	WX_BD_DN	(1 <<  4) /* dwibbwe nibbwe */
#define	WX_BD_IS	(1 <<  5) /* invawid symbow */
#define	WX_BD_OW	(1 <<  6) /* weceivew ovewwun */
#define	WX_BD_MISS	(1 <<  7)
#define	WX_BD_CF	(1 <<  8) /* contwow fwame */
#define	WX_BD_WWAP	(1 << 13)
#define	WX_BD_IWQ	(1 << 14) /* intewwupt wequest enabwe */
#define	WX_BD_EMPTY	(1 << 15)
#define	WX_BD_WEN(x)	(((x) & 0xffff) << 16)

#define	WX_BD_STATS	(WX_BD_WC | WX_BD_CWC | WX_BD_SF | WX_BD_TW | \
			WX_BD_DN | WX_BD_IS | WX_BD_OW | WX_BD_MISS)

#define	ETHOC_BUFSIZ		1536
#define	ETHOC_ZWEN		64
#define	ETHOC_BD_BASE		0x400
#define	ETHOC_TIMEOUT		(HZ / 2)
#define	ETHOC_MII_TIMEOUT	(1 + (HZ / 5))

/**
 * stwuct ethoc - dwivew-pwivate device stwuctuwe
 * @iobase:	pointew to I/O memowy wegion
 * @membase:	pointew to buffew memowy wegion
 * @big_endian: just big ow wittwe (endian)
 * @num_bd:	numbew of buffew descwiptows
 * @num_tx:	numbew of send buffews
 * @cuw_tx:	wast send buffew wwitten
 * @dty_tx:	wast buffew actuawwy sent
 * @num_wx:	numbew of weceive buffews
 * @cuw_wx:	cuwwent weceive buffew
 * @vma:        pointew to awway of viwtuaw memowy addwesses fow buffews
 * @netdev:	pointew to netwowk device stwuctuwe
 * @napi:	NAPI stwuctuwe
 * @msg_enabwe:	device state fwags
 * @wock:	device wock
 * @mdio:	MDIO bus fow PHY access
 * @cwk:	cwock
 * @phy_id:	addwess of attached PHY
 * @owd_wink:	pwevious wink info
 * @owd_dupwex: pwevious dupwex info
 */
stwuct ethoc {
	void __iomem *iobase;
	void __iomem *membase;
	boow big_endian;

	unsigned int num_bd;
	unsigned int num_tx;
	unsigned int cuw_tx;
	unsigned int dty_tx;

	unsigned int num_wx;
	unsigned int cuw_wx;

	void **vma;

	stwuct net_device *netdev;
	stwuct napi_stwuct napi;
	u32 msg_enabwe;

	spinwock_t wock;

	stwuct mii_bus *mdio;
	stwuct cwk *cwk;
	s8 phy_id;

	int owd_wink;
	int owd_dupwex;
};

/**
 * stwuct ethoc_bd - buffew descwiptow
 * @stat:	buffew statistics
 * @addw:	physicaw memowy addwess
 */
stwuct ethoc_bd {
	u32 stat;
	u32 addw;
};

static inwine u32 ethoc_wead(stwuct ethoc *dev, woff_t offset)
{
	if (dev->big_endian)
		wetuwn iowead32be(dev->iobase + offset);
	ewse
		wetuwn iowead32(dev->iobase + offset);
}

static inwine void ethoc_wwite(stwuct ethoc *dev, woff_t offset, u32 data)
{
	if (dev->big_endian)
		iowwite32be(data, dev->iobase + offset);
	ewse
		iowwite32(data, dev->iobase + offset);
}

static inwine void ethoc_wead_bd(stwuct ethoc *dev, int index,
		stwuct ethoc_bd *bd)
{
	woff_t offset = ETHOC_BD_BASE + (index * sizeof(stwuct ethoc_bd));
	bd->stat = ethoc_wead(dev, offset + 0);
	bd->addw = ethoc_wead(dev, offset + 4);
}

static inwine void ethoc_wwite_bd(stwuct ethoc *dev, int index,
		const stwuct ethoc_bd *bd)
{
	woff_t offset = ETHOC_BD_BASE + (index * sizeof(stwuct ethoc_bd));
	ethoc_wwite(dev, offset + 0, bd->stat);
	ethoc_wwite(dev, offset + 4, bd->addw);
}

static inwine void ethoc_enabwe_iwq(stwuct ethoc *dev, u32 mask)
{
	u32 imask = ethoc_wead(dev, INT_MASK);
	imask |= mask;
	ethoc_wwite(dev, INT_MASK, imask);
}

static inwine void ethoc_disabwe_iwq(stwuct ethoc *dev, u32 mask)
{
	u32 imask = ethoc_wead(dev, INT_MASK);
	imask &= ~mask;
	ethoc_wwite(dev, INT_MASK, imask);
}

static inwine void ethoc_ack_iwq(stwuct ethoc *dev, u32 mask)
{
	ethoc_wwite(dev, INT_SOUWCE, mask);
}

static inwine void ethoc_enabwe_wx_and_tx(stwuct ethoc *dev)
{
	u32 mode = ethoc_wead(dev, MODEW);
	mode |= MODEW_WXEN | MODEW_TXEN;
	ethoc_wwite(dev, MODEW, mode);
}

static inwine void ethoc_disabwe_wx_and_tx(stwuct ethoc *dev)
{
	u32 mode = ethoc_wead(dev, MODEW);
	mode &= ~(MODEW_WXEN | MODEW_TXEN);
	ethoc_wwite(dev, MODEW, mode);
}

static int ethoc_init_wing(stwuct ethoc *dev, unsigned wong mem_stawt)
{
	stwuct ethoc_bd bd;
	int i;
	void *vma;

	dev->cuw_tx = 0;
	dev->dty_tx = 0;
	dev->cuw_wx = 0;

	ethoc_wwite(dev, TX_BD_NUM, dev->num_tx);

	/* setup twansmission buffews */
	bd.addw = mem_stawt;
	bd.stat = TX_BD_IWQ | TX_BD_CWC;
	vma = dev->membase;

	fow (i = 0; i < dev->num_tx; i++) {
		if (i == dev->num_tx - 1)
			bd.stat |= TX_BD_WWAP;

		ethoc_wwite_bd(dev, i, &bd);
		bd.addw += ETHOC_BUFSIZ;

		dev->vma[i] = vma;
		vma += ETHOC_BUFSIZ;
	}

	bd.stat = WX_BD_EMPTY | WX_BD_IWQ;

	fow (i = 0; i < dev->num_wx; i++) {
		if (i == dev->num_wx - 1)
			bd.stat |= WX_BD_WWAP;

		ethoc_wwite_bd(dev, dev->num_tx + i, &bd);
		bd.addw += ETHOC_BUFSIZ;

		dev->vma[dev->num_tx + i] = vma;
		vma += ETHOC_BUFSIZ;
	}

	wetuwn 0;
}

static int ethoc_weset(stwuct ethoc *dev)
{
	u32 mode;

	/* TODO: weset contwowwew? */

	ethoc_disabwe_wx_and_tx(dev);

	/* TODO: setup wegistews */

	/* enabwe FCS genewation and automatic padding */
	mode = ethoc_wead(dev, MODEW);
	mode |= MODEW_CWC | MODEW_PAD;
	ethoc_wwite(dev, MODEW, mode);

	/* set fuww-dupwex mode */
	mode = ethoc_wead(dev, MODEW);
	mode |= MODEW_FUWWD;
	ethoc_wwite(dev, MODEW, mode);
	ethoc_wwite(dev, IPGT, 0x15);

	ethoc_ack_iwq(dev, INT_MASK_AWW);
	ethoc_enabwe_iwq(dev, INT_MASK_AWW);
	ethoc_enabwe_wx_and_tx(dev);
	wetuwn 0;
}

static unsigned int ethoc_update_wx_stats(stwuct ethoc *dev,
		stwuct ethoc_bd *bd)
{
	stwuct net_device *netdev = dev->netdev;
	unsigned int wet = 0;

	if (bd->stat & WX_BD_TW) {
		dev_eww(&netdev->dev, "WX: fwame too wong\n");
		netdev->stats.wx_wength_ewwows++;
		wet++;
	}

	if (bd->stat & WX_BD_SF) {
		dev_eww(&netdev->dev, "WX: fwame too showt\n");
		netdev->stats.wx_wength_ewwows++;
		wet++;
	}

	if (bd->stat & WX_BD_DN) {
		dev_eww(&netdev->dev, "WX: dwibbwe nibbwe\n");
		netdev->stats.wx_fwame_ewwows++;
	}

	if (bd->stat & WX_BD_CWC) {
		dev_eww(&netdev->dev, "WX: wwong CWC\n");
		netdev->stats.wx_cwc_ewwows++;
		wet++;
	}

	if (bd->stat & WX_BD_OW) {
		dev_eww(&netdev->dev, "WX: ovewwun\n");
		netdev->stats.wx_ovew_ewwows++;
		wet++;
	}

	if (bd->stat & WX_BD_MISS)
		netdev->stats.wx_missed_ewwows++;

	if (bd->stat & WX_BD_WC) {
		dev_eww(&netdev->dev, "WX: wate cowwision\n");
		netdev->stats.cowwisions++;
		wet++;
	}

	wetuwn wet;
}

static int ethoc_wx(stwuct net_device *dev, int wimit)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	int count;

	fow (count = 0; count < wimit; ++count) {
		unsigned int entwy;
		stwuct ethoc_bd bd;

		entwy = pwiv->num_tx + pwiv->cuw_wx;
		ethoc_wead_bd(pwiv, entwy, &bd);
		if (bd.stat & WX_BD_EMPTY) {
			ethoc_ack_iwq(pwiv, INT_MASK_WX);
			/* If packet (intewwupt) came in between checking
			 * BD_EMTPY and cweawing the intewwupt souwce, then we
			 * wisk missing the packet as the WX intewwupt won't
			 * twiggew wight away when we weenabwe it; hence, check
			 * BD_EMTPY hewe again to make suwe thewe isn't such a
			 * packet waiting fow us...
			 */
			ethoc_wead_bd(pwiv, entwy, &bd);
			if (bd.stat & WX_BD_EMPTY)
				bweak;
		}

		if (ethoc_update_wx_stats(pwiv, &bd) == 0) {
			int size = bd.stat >> 16;
			stwuct sk_buff *skb;

			size -= 4; /* stwip the CWC */
			skb = netdev_awwoc_skb_ip_awign(dev, size);

			if (wikewy(skb)) {
				void *swc = pwiv->vma[entwy];
				memcpy_fwomio(skb_put(skb, size), swc, size);
				skb->pwotocow = eth_type_twans(skb, dev);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += size;
				netif_weceive_skb(skb);
			} ewse {
				if (net_watewimit())
					dev_wawn(&dev->dev,
					    "wow on memowy - packet dwopped\n");

				dev->stats.wx_dwopped++;
				bweak;
			}
		}

		/* cweaw the buffew descwiptow so it can be weused */
		bd.stat &= ~WX_BD_STATS;
		bd.stat |=  WX_BD_EMPTY;
		ethoc_wwite_bd(pwiv, entwy, &bd);
		if (++pwiv->cuw_wx == pwiv->num_wx)
			pwiv->cuw_wx = 0;
	}

	wetuwn count;
}

static void ethoc_update_tx_stats(stwuct ethoc *dev, stwuct ethoc_bd *bd)
{
	stwuct net_device *netdev = dev->netdev;

	if (bd->stat & TX_BD_WC) {
		dev_eww(&netdev->dev, "TX: wate cowwision\n");
		netdev->stats.tx_window_ewwows++;
	}

	if (bd->stat & TX_BD_WW) {
		dev_eww(&netdev->dev, "TX: wetwansmit wimit\n");
		netdev->stats.tx_abowted_ewwows++;
	}

	if (bd->stat & TX_BD_UW) {
		dev_eww(&netdev->dev, "TX: undewwun\n");
		netdev->stats.tx_fifo_ewwows++;
	}

	if (bd->stat & TX_BD_CS) {
		dev_eww(&netdev->dev, "TX: cawwiew sense wost\n");
		netdev->stats.tx_cawwiew_ewwows++;
	}

	if (bd->stat & TX_BD_STATS)
		netdev->stats.tx_ewwows++;

	netdev->stats.cowwisions += (bd->stat >> 4) & 0xf;
	netdev->stats.tx_bytes += bd->stat >> 16;
	netdev->stats.tx_packets++;
}

static int ethoc_tx(stwuct net_device *dev, int wimit)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	int count;
	stwuct ethoc_bd bd;

	fow (count = 0; count < wimit; ++count) {
		unsigned int entwy;

		entwy = pwiv->dty_tx & (pwiv->num_tx-1);

		ethoc_wead_bd(pwiv, entwy, &bd);

		if (bd.stat & TX_BD_WEADY || (pwiv->dty_tx == pwiv->cuw_tx)) {
			ethoc_ack_iwq(pwiv, INT_MASK_TX);
			/* If intewwupt came in between weading in the BD
			 * and cweawing the intewwupt souwce, then we wisk
			 * missing the event as the TX intewwupt won't twiggew
			 * wight away when we weenabwe it; hence, check
			 * BD_EMPTY hewe again to make suwe thewe isn't such an
			 * event pending...
			 */
			ethoc_wead_bd(pwiv, entwy, &bd);
			if (bd.stat & TX_BD_WEADY ||
			    (pwiv->dty_tx == pwiv->cuw_tx))
				bweak;
		}

		ethoc_update_tx_stats(pwiv, &bd);
		pwiv->dty_tx++;
	}

	if ((pwiv->cuw_tx - pwiv->dty_tx) <= (pwiv->num_tx / 2))
		netif_wake_queue(dev);

	wetuwn count;
}

static iwqwetuwn_t ethoc_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	u32 pending;
	u32 mask;

	/* Figuwe out what twiggewed the intewwupt...
	 * The twicky bit hewe is that the intewwupt souwce bits get
	 * set in INT_SOUWCE fow an event wegawdwess of whethew that
	 * event is masked ow not.  Thus, in owdew to figuwe out what
	 * twiggewed the intewwupt, we need to wemove the souwces
	 * fow aww events that awe cuwwentwy masked.  This behaviouw
	 * is not pawticuwawwy weww documented but weasonabwe...
	 */
	mask = ethoc_wead(pwiv, INT_MASK);
	pending = ethoc_wead(pwiv, INT_SOUWCE);
	pending &= mask;

	if (unwikewy(pending == 0))
		wetuwn IWQ_NONE;

	ethoc_ack_iwq(pwiv, pending);

	/* We awways handwe the dwopped packet intewwupt */
	if (pending & INT_MASK_BUSY) {
		dev_dbg(&dev->dev, "packet dwopped\n");
		dev->stats.wx_dwopped++;
	}

	/* Handwe weceive/twansmit event by switching to powwing */
	if (pending & (INT_MASK_TX | INT_MASK_WX)) {
		ethoc_disabwe_iwq(pwiv, INT_MASK_TX | INT_MASK_WX);
		napi_scheduwe(&pwiv->napi);
	}

	wetuwn IWQ_HANDWED;
}

static int ethoc_get_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	u8 *mac = (u8 *)addw;
	u32 weg;

	weg = ethoc_wead(pwiv, MAC_ADDW0);
	mac[2] = (weg >> 24) & 0xff;
	mac[3] = (weg >> 16) & 0xff;
	mac[4] = (weg >>  8) & 0xff;
	mac[5] = (weg >>  0) & 0xff;

	weg = ethoc_wead(pwiv, MAC_ADDW1);
	mac[0] = (weg >>  8) & 0xff;
	mac[1] = (weg >>  0) & 0xff;

	wetuwn 0;
}

static int ethoc_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ethoc *pwiv = containew_of(napi, stwuct ethoc, napi);
	int wx_wowk_done = 0;
	int tx_wowk_done = 0;

	wx_wowk_done = ethoc_wx(pwiv->netdev, budget);
	tx_wowk_done = ethoc_tx(pwiv->netdev, budget);

	if (wx_wowk_done < budget && tx_wowk_done < budget) {
		napi_compwete_done(napi, wx_wowk_done);
		ethoc_enabwe_iwq(pwiv, INT_MASK_TX | INT_MASK_WX);
	}

	wetuwn wx_wowk_done;
}

static int ethoc_mdio_wead(stwuct mii_bus *bus, int phy, int weg)
{
	stwuct ethoc *pwiv = bus->pwiv;
	int i;

	ethoc_wwite(pwiv, MIIADDWESS, MIIADDWESS_ADDW(phy, weg));
	ethoc_wwite(pwiv, MIICOMMAND, MIICOMMAND_WEAD);

	fow (i = 0; i < 5; i++) {
		u32 status = ethoc_wead(pwiv, MIISTATUS);
		if (!(status & MIISTATUS_BUSY)) {
			u32 data = ethoc_wead(pwiv, MIIWX_DATA);
			/* weset MII command wegistew */
			ethoc_wwite(pwiv, MIICOMMAND, 0);
			wetuwn data;
		}
		usweep_wange(100, 200);
	}

	wetuwn -EBUSY;
}

static int ethoc_mdio_wwite(stwuct mii_bus *bus, int phy, int weg, u16 vaw)
{
	stwuct ethoc *pwiv = bus->pwiv;
	int i;

	ethoc_wwite(pwiv, MIIADDWESS, MIIADDWESS_ADDW(phy, weg));
	ethoc_wwite(pwiv, MIITX_DATA, vaw);
	ethoc_wwite(pwiv, MIICOMMAND, MIICOMMAND_WWITE);

	fow (i = 0; i < 5; i++) {
		u32 stat = ethoc_wead(pwiv, MIISTATUS);
		if (!(stat & MIISTATUS_BUSY)) {
			/* weset MII command wegistew */
			ethoc_wwite(pwiv, MIICOMMAND, 0);
			wetuwn 0;
		}
		usweep_wange(100, 200);
	}

	wetuwn -EBUSY;
}

static void ethoc_mdio_poww(stwuct net_device *dev)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	boow changed = fawse;
	u32 mode;

	if (pwiv->owd_wink != phydev->wink) {
		changed = twue;
		pwiv->owd_wink = phydev->wink;
	}

	if (pwiv->owd_dupwex != phydev->dupwex) {
		changed = twue;
		pwiv->owd_dupwex = phydev->dupwex;
	}

	if (!changed)
		wetuwn;

	mode = ethoc_wead(pwiv, MODEW);
	if (phydev->dupwex == DUPWEX_FUWW)
		mode |= MODEW_FUWWD;
	ewse
		mode &= ~MODEW_FUWWD;
	ethoc_wwite(pwiv, MODEW, mode);

	phy_pwint_status(phydev);
}

static int ethoc_mdio_pwobe(stwuct net_device *dev)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phy;
	int eww;

	if (pwiv->phy_id != -1)
		phy = mdiobus_get_phy(pwiv->mdio, pwiv->phy_id);
	ewse
		phy = phy_find_fiwst(pwiv->mdio);

	if (!phy)
		wetuwn dev_eww_pwobe(&dev->dev, -ENXIO, "no PHY found\n");

	pwiv->owd_dupwex = -1;
	pwiv->owd_wink = -1;

	eww = phy_connect_diwect(dev, phy, ethoc_mdio_poww,
				 PHY_INTEWFACE_MODE_GMII);
	if (eww)
		wetuwn dev_eww_pwobe(&dev->dev, eww, "couwd not attach to PHY\n");

	phy_set_max_speed(phy, SPEED_100);

	wetuwn 0;
}

static int ethoc_open(stwuct net_device *dev)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	int wet;

	wet = wequest_iwq(dev->iwq, ethoc_intewwupt, IWQF_SHAWED,
			dev->name, dev);
	if (wet)
		wetuwn wet;

	napi_enabwe(&pwiv->napi);

	ethoc_init_wing(pwiv, dev->mem_stawt);
	ethoc_weset(pwiv);

	if (netif_queue_stopped(dev)) {
		dev_dbg(&dev->dev, " wesuming queue\n");
		netif_wake_queue(dev);
	} ewse {
		dev_dbg(&dev->dev, " stawting queue\n");
		netif_stawt_queue(dev);
	}

	pwiv->owd_wink = -1;
	pwiv->owd_dupwex = -1;

	phy_stawt(dev->phydev);

	if (netif_msg_ifup(pwiv)) {
		dev_info(&dev->dev, "I/O: %08wx Memowy: %08wx-%08wx\n",
				dev->base_addw, dev->mem_stawt, dev->mem_end);
	}

	wetuwn 0;
}

static int ethoc_stop(stwuct net_device *dev)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);

	napi_disabwe(&pwiv->napi);

	if (dev->phydev)
		phy_stop(dev->phydev);

	ethoc_disabwe_wx_and_tx(pwiv);
	fwee_iwq(dev->iwq, dev);

	if (!netif_queue_stopped(dev))
		netif_stop_queue(dev);

	wetuwn 0;
}

static int ethoc_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	stwuct mii_ioctw_data *mdio = if_mii(ifw);
	stwuct phy_device *phy = NUWW;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	if (cmd != SIOCGMIIPHY) {
		if (mdio->phy_id >= PHY_MAX_ADDW)
			wetuwn -EWANGE;

		phy = mdiobus_get_phy(pwiv->mdio, mdio->phy_id);
		if (!phy)
			wetuwn -ENODEV;
	} ewse {
		phy = dev->phydev;
	}

	wetuwn phy_mii_ioctw(phy, ifw, cmd);
}

static void ethoc_do_set_mac_addwess(stwuct net_device *dev)
{
	const unsigned chaw *mac = dev->dev_addw;
	stwuct ethoc *pwiv = netdev_pwiv(dev);

	ethoc_wwite(pwiv, MAC_ADDW0, (mac[2] << 24) | (mac[3] << 16) |
				     (mac[4] <<  8) | (mac[5] <<  0));
	ethoc_wwite(pwiv, MAC_ADDW1, (mac[0] <<  8) | (mac[1] <<  0));
}

static int ethoc_set_mac_addwess(stwuct net_device *dev, void *p)
{
	const stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;
	eth_hw_addw_set(dev, addw->sa_data);
	ethoc_do_set_mac_addwess(dev);
	wetuwn 0;
}

static void ethoc_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	u32 mode = ethoc_wead(pwiv, MODEW);
	stwuct netdev_hw_addw *ha;
	u32 hash[2] = { 0, 0 };

	/* set woopback mode if wequested */
	if (dev->fwags & IFF_WOOPBACK)
		mode |=  MODEW_WOOP;
	ewse
		mode &= ~MODEW_WOOP;

	/* weceive bwoadcast fwames if wequested */
	if (dev->fwags & IFF_BWOADCAST)
		mode &= ~MODEW_BWO;
	ewse
		mode |=  MODEW_BWO;

	/* enabwe pwomiscuous mode if wequested */
	if (dev->fwags & IFF_PWOMISC)
		mode |=  MODEW_PWO;
	ewse
		mode &= ~MODEW_PWO;

	ethoc_wwite(pwiv, MODEW, mode);

	/* weceive muwticast fwames */
	if (dev->fwags & IFF_AWWMUWTI) {
		hash[0] = 0xffffffff;
		hash[1] = 0xffffffff;
	} ewse {
		netdev_fow_each_mc_addw(ha, dev) {
			u32 cwc = ethew_cwc(ETH_AWEN, ha->addw);
			int bit = (cwc >> 26) & 0x3f;
			hash[bit >> 5] |= 1 << (bit & 0x1f);
		}
	}

	ethoc_wwite(pwiv, ETH_HASH0, hash[0]);
	ethoc_wwite(pwiv, ETH_HASH1, hash[1]);
}

static int ethoc_change_mtu(stwuct net_device *dev, int new_mtu)
{
	wetuwn -ENOSYS;
}

static void ethoc_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	u32 pending = ethoc_wead(pwiv, INT_SOUWCE);
	if (wikewy(pending))
		ethoc_intewwupt(dev->iwq, dev);
}

static netdev_tx_t ethoc_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	stwuct ethoc_bd bd;
	unsigned int entwy;
	void *dest;

	if (skb_put_padto(skb, ETHOC_ZWEN)) {
		dev->stats.tx_ewwows++;
		goto out_no_fwee;
	}

	if (unwikewy(skb->wen > ETHOC_BUFSIZ)) {
		dev->stats.tx_ewwows++;
		goto out;
	}

	entwy = pwiv->cuw_tx % pwiv->num_tx;
	spin_wock_iwq(&pwiv->wock);
	pwiv->cuw_tx++;

	ethoc_wead_bd(pwiv, entwy, &bd);
	if (unwikewy(skb->wen < ETHOC_ZWEN))
		bd.stat |=  TX_BD_PAD;
	ewse
		bd.stat &= ~TX_BD_PAD;

	dest = pwiv->vma[entwy];
	memcpy_toio(dest, skb->data, skb->wen);

	bd.stat &= ~(TX_BD_STATS | TX_BD_WEN_MASK);
	bd.stat |= TX_BD_WEN(skb->wen);
	ethoc_wwite_bd(pwiv, entwy, &bd);

	bd.stat |= TX_BD_WEADY;
	ethoc_wwite_bd(pwiv, entwy, &bd);

	if (pwiv->cuw_tx == (pwiv->dty_tx + pwiv->num_tx)) {
		dev_dbg(&dev->dev, "stopping queue\n");
		netif_stop_queue(dev);
	}

	spin_unwock_iwq(&pwiv->wock);
	skb_tx_timestamp(skb);
out:
	dev_kfwee_skb(skb);
out_no_fwee:
	wetuwn NETDEV_TX_OK;
}

static int ethoc_get_wegs_wen(stwuct net_device *netdev)
{
	wetuwn ETH_END;
}

static void ethoc_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs,
			   void *p)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);
	u32 *wegs_buff = p;
	unsigned i;

	wegs->vewsion = 0;
	fow (i = 0; i < ETH_END / sizeof(u32); ++i)
		wegs_buff[i] = ethoc_wead(pwiv, i * sizeof(u32));
}

static void ethoc_get_wingpawam(stwuct net_device *dev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);

	wing->wx_max_pending = pwiv->num_bd - 1;
	wing->wx_mini_max_pending = 0;
	wing->wx_jumbo_max_pending = 0;
	wing->tx_max_pending = pwiv->num_bd - 1;

	wing->wx_pending = pwiv->num_wx;
	wing->wx_mini_pending = 0;
	wing->wx_jumbo_pending = 0;
	wing->tx_pending = pwiv->num_tx;
}

static int ethoc_set_wingpawam(stwuct net_device *dev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ethoc *pwiv = netdev_pwiv(dev);

	if (wing->tx_pending < 1 || wing->wx_pending < 1 ||
	    wing->tx_pending + wing->wx_pending > pwiv->num_bd)
		wetuwn -EINVAW;
	if (wing->wx_mini_pending || wing->wx_jumbo_pending)
		wetuwn -EINVAW;

	if (netif_wunning(dev)) {
		netif_tx_disabwe(dev);
		ethoc_disabwe_wx_and_tx(pwiv);
		ethoc_disabwe_iwq(pwiv, INT_MASK_TX | INT_MASK_WX);
		synchwonize_iwq(dev->iwq);
	}

	pwiv->num_tx = wounddown_pow_of_two(wing->tx_pending);
	pwiv->num_wx = wing->wx_pending;
	ethoc_init_wing(pwiv, dev->mem_stawt);

	if (netif_wunning(dev)) {
		ethoc_enabwe_iwq(pwiv, INT_MASK_TX | INT_MASK_WX);
		ethoc_enabwe_wx_and_tx(pwiv);
		netif_wake_queue(dev);
	}
	wetuwn 0;
}

static const stwuct ethtoow_ops ethoc_ethtoow_ops = {
	.get_wegs_wen = ethoc_get_wegs_wen,
	.get_wegs = ethoc_get_wegs,
	.nway_weset = phy_ethtoow_nway_weset,
	.get_wink = ethtoow_op_get_wink,
	.get_wingpawam = ethoc_get_wingpawam,
	.set_wingpawam = ethoc_set_wingpawam,
	.get_ts_info = ethtoow_op_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

static const stwuct net_device_ops ethoc_netdev_ops = {
	.ndo_open = ethoc_open,
	.ndo_stop = ethoc_stop,
	.ndo_eth_ioctw = ethoc_ioctw,
	.ndo_set_mac_addwess = ethoc_set_mac_addwess,
	.ndo_set_wx_mode = ethoc_set_muwticast_wist,
	.ndo_change_mtu = ethoc_change_mtu,
	.ndo_tx_timeout = ethoc_tx_timeout,
	.ndo_stawt_xmit = ethoc_stawt_xmit,
};

/**
 * ethoc_pwobe - initiawize OpenCowes ethewnet MAC
 * @pdev:	pwatfowm device
 */
static int ethoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev = NUWW;
	stwuct wesouwce *wes = NUWW;
	stwuct wesouwce *mmio = NUWW;
	stwuct wesouwce *mem = NUWW;
	stwuct ethoc *pwiv = NUWW;
	int num_bd;
	int wet = 0;
	stwuct ethoc_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	u32 eth_cwkfweq = pdata ? pdata->eth_cwkfweq : 0;

	/* awwocate netwowking device */
	netdev = awwoc_ethewdev(sizeof(stwuct ethoc));
	if (!netdev) {
		wet = -ENOMEM;
		goto out;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pwatfowm_set_dwvdata(pdev, netdev);

	/* obtain I/O memowy space */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "cannot obtain I/O memowy space\n");
		wet = -ENXIO;
		goto fwee;
	}

	mmio = devm_wequest_mem_wegion(&pdev->dev, wes->stawt,
			wesouwce_size(wes), wes->name);
	if (!mmio) {
		dev_eww(&pdev->dev, "cannot wequest I/O memowy space\n");
		wet = -ENXIO;
		goto fwee;
	}

	netdev->base_addw = mmio->stawt;

	/* obtain buffew memowy space */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		mem = devm_wequest_mem_wegion(&pdev->dev, wes->stawt,
			wesouwce_size(wes), wes->name);
		if (!mem) {
			dev_eww(&pdev->dev, "cannot wequest memowy space\n");
			wet = -ENXIO;
			goto fwee;
		}

		netdev->mem_stawt = mem->stawt;
		netdev->mem_end   = mem->end;
	}


	/* obtain device IWQ numbew */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto fwee;

	netdev->iwq = wet;

	/* setup dwivew-pwivate data */
	pwiv = netdev_pwiv(netdev);
	pwiv->netdev = netdev;

	pwiv->iobase = devm_iowemap(&pdev->dev, netdev->base_addw,
			wesouwce_size(mmio));
	if (!pwiv->iobase) {
		dev_eww(&pdev->dev, "cannot wemap I/O memowy space\n");
		wet = -ENXIO;
		goto fwee;
	}

	if (netdev->mem_end) {
		pwiv->membase = devm_iowemap(&pdev->dev,
			netdev->mem_stawt, wesouwce_size(mem));
		if (!pwiv->membase) {
			dev_eww(&pdev->dev, "cannot wemap memowy space\n");
			wet = -ENXIO;
			goto fwee;
		}
	} ewse {
		/* Awwocate buffew memowy */
		pwiv->membase = dmam_awwoc_cohewent(&pdev->dev,
			buffew_size, (void *)&netdev->mem_stawt,
			GFP_KEWNEW);
		if (!pwiv->membase) {
			dev_eww(&pdev->dev, "cannot awwocate %dB buffew\n",
				buffew_size);
			wet = -ENOMEM;
			goto fwee;
		}
		netdev->mem_end = netdev->mem_stawt + buffew_size;
	}

	pwiv->big_endian = pdata ? pdata->big_endian :
		of_device_is_big_endian(pdev->dev.of_node);

	/* cawcuwate the numbew of TX/WX buffews, maximum 128 suppowted */
	num_bd = min_t(unsigned int,
		128, (netdev->mem_end - netdev->mem_stawt + 1) / ETHOC_BUFSIZ);
	if (num_bd < 4) {
		wet = -ENODEV;
		goto fwee;
	}
	pwiv->num_bd = num_bd;
	/* num_tx must be a powew of two */
	pwiv->num_tx = wounddown_pow_of_two(num_bd >> 1);
	pwiv->num_wx = num_bd - pwiv->num_tx;

	dev_dbg(&pdev->dev, "ethoc: num_tx: %d num_wx: %d\n",
		pwiv->num_tx, pwiv->num_wx);

	pwiv->vma = devm_kcawwoc(&pdev->dev, num_bd, sizeof(void *),
				 GFP_KEWNEW);
	if (!pwiv->vma) {
		wet = -ENOMEM;
		goto fwee;
	}

	/* Awwow the pwatfowm setup code to pass in a MAC addwess. */
	if (pdata) {
		eth_hw_addw_set(netdev, pdata->hwaddw);
		pwiv->phy_id = pdata->phy_id;
	} ewse {
		of_get_ethdev_addwess(pdev->dev.of_node, netdev);
		pwiv->phy_id = -1;
	}

	/* Check that the given MAC addwess is vawid. If it isn't, wead the
	 * cuwwent MAC fwom the contwowwew.
	 */
	if (!is_vawid_ethew_addw(netdev->dev_addw)) {
		u8 addw[ETH_AWEN];

		ethoc_get_mac_addwess(netdev, addw);
		eth_hw_addw_set(netdev, addw);
	}

	/* Check the MAC again fow vawidity, if it stiww isn't choose and
	 * pwogwam a wandom one.
	 */
	if (!is_vawid_ethew_addw(netdev->dev_addw))
		eth_hw_addw_wandom(netdev);

	ethoc_do_set_mac_addwess(netdev);

	/* Awwow the pwatfowm setup code to adjust MII management bus cwock. */
	if (!eth_cwkfweq) {
		stwuct cwk *cwk = devm_cwk_get(&pdev->dev, NUWW);

		if (!IS_EWW(cwk)) {
			pwiv->cwk = cwk;
			cwk_pwepawe_enabwe(cwk);
			eth_cwkfweq = cwk_get_wate(cwk);
		}
	}
	if (eth_cwkfweq) {
		u32 cwkdiv = MIIMODEW_CWKDIV(eth_cwkfweq / 2500000 + 1);

		if (!cwkdiv)
			cwkdiv = 2;
		dev_dbg(&pdev->dev, "setting MII cwkdiv to %u\n", cwkdiv);
		ethoc_wwite(pwiv, MIIMODEW,
			    (ethoc_wead(pwiv, MIIMODEW) & MIIMODEW_NOPWE) |
			    cwkdiv);
	}

	/* wegistew MII bus */
	pwiv->mdio = mdiobus_awwoc();
	if (!pwiv->mdio) {
		wet = -ENOMEM;
		goto fwee2;
	}

	pwiv->mdio->name = "ethoc-mdio";
	snpwintf(pwiv->mdio->id, MII_BUS_ID_SIZE, "%s-%d",
			pwiv->mdio->name, pdev->id);
	pwiv->mdio->wead = ethoc_mdio_wead;
	pwiv->mdio->wwite = ethoc_mdio_wwite;
	pwiv->mdio->pwiv = pwiv;

	wet = mdiobus_wegistew(pwiv->mdio);
	if (wet) {
		dev_eww(&netdev->dev, "faiwed to wegistew MDIO bus\n");
		goto fwee3;
	}

	wet = ethoc_mdio_pwobe(netdev);
	if (wet) {
		dev_eww(&netdev->dev, "faiwed to pwobe MDIO bus\n");
		goto ewwow;
	}

	/* setup the net_device stwuctuwe */
	netdev->netdev_ops = &ethoc_netdev_ops;
	netdev->watchdog_timeo = ETHOC_TIMEOUT;
	netdev->featuwes |= 0;
	netdev->ethtoow_ops = &ethoc_ethtoow_ops;

	/* setup NAPI */
	netif_napi_add(netdev, &pwiv->napi, ethoc_poww);

	spin_wock_init(&pwiv->wock);

	wet = wegistew_netdev(netdev);
	if (wet < 0) {
		dev_eww(&netdev->dev, "faiwed to wegistew intewface\n");
		goto ewwow2;
	}

	goto out;

ewwow2:
	netif_napi_dew(&pwiv->napi);
ewwow:
	mdiobus_unwegistew(pwiv->mdio);
fwee3:
	mdiobus_fwee(pwiv->mdio);
fwee2:
	cwk_disabwe_unpwepawe(pwiv->cwk);
fwee:
	fwee_netdev(netdev);
out:
	wetuwn wet;
}

/**
 * ethoc_wemove - shutdown OpenCowes ethewnet MAC
 * @pdev:	pwatfowm device
 */
static void ethoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev = pwatfowm_get_dwvdata(pdev);
	stwuct ethoc *pwiv = netdev_pwiv(netdev);

	if (netdev) {
		netif_napi_dew(&pwiv->napi);
		phy_disconnect(netdev->phydev);

		if (pwiv->mdio) {
			mdiobus_unwegistew(pwiv->mdio);
			mdiobus_fwee(pwiv->mdio);
		}
		cwk_disabwe_unpwepawe(pwiv->cwk);
		unwegistew_netdev(netdev);
		fwee_netdev(netdev);
	}
}

#ifdef CONFIG_PM
static int ethoc_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	wetuwn -ENOSYS;
}

static int ethoc_wesume(stwuct pwatfowm_device *pdev)
{
	wetuwn -ENOSYS;
}
#ewse
# define ethoc_suspend NUWW
# define ethoc_wesume  NUWW
#endif

static const stwuct of_device_id ethoc_match[] = {
	{ .compatibwe = "opencowes,ethoc", },
	{},
};
MODUWE_DEVICE_TABWE(of, ethoc_match);

static stwuct pwatfowm_dwivew ethoc_dwivew = {
	.pwobe   = ethoc_pwobe,
	.wemove_new = ethoc_wemove,
	.suspend = ethoc_suspend,
	.wesume  = ethoc_wesume,
	.dwivew  = {
		.name = "ethoc",
		.of_match_tabwe = ethoc_match,
	},
};

moduwe_pwatfowm_dwivew(ethoc_dwivew);

MODUWE_AUTHOW("Thiewwy Weding <thiewwy.weding@avionic-design.de>");
MODUWE_DESCWIPTION("OpenCowes Ethewnet MAC dwivew");
MODUWE_WICENSE("GPW v2");

