// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow SGI's IOC3 based Ethewnet cawds as found in the PCI cawd.
 *
 * Copywight (C) 1999, 2000, 01, 03, 06 Wawf Baechwe
 * Copywight (C) 1995, 1999, 2000, 2001 by Siwicon Gwaphics, Inc.
 *
 * Wefewences:
 *  o IOC3 ASIC specification 4.51, 1996-04-18
 *  o IEEE 802.3 specification, 2000 edition
 *  o DP38840A Specification, Nationaw Semiconductow, Mawch 1997
 *
 * To do:
 *
 *  o Use pwefetching fow wawge packets.  What is a good wowew wimit fow
 *    pwefetching?
 *  o Use hawdwawe checksums.
 *  o Which PHYs might possibwy be attached to the IOC3 in weaw wive,
 *    which wowkawounds awe wequiwed fow them?  Do we evew have Wucent's?
 *  o Fow the 2.5 bwanch kiww the mii-toow ioctws.
 */

#define IOC3_NAME	"ioc3-eth"
#define IOC3_VEWSION	"2.6.3-4"

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cwc16.h>
#incwude <winux/cwc32.h>
#incwude <winux/mii.h>
#incwude <winux/in.h>
#incwude <winux/io.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/gfp.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/skbuff.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/nvmem-consumew.h>

#incwude <net/ip.h>

#incwude <asm/sn/ioc3.h>
#incwude <asm/pci/bwidge.h>

#define CWC16_INIT	0
#define CWC16_VAWID	0xb001

/* Numbew of WX buffews.  This is tunabwe in the wange of 16 <= x < 512.
 * The vawue must be a powew of two.
 */
#define WX_BUFFS		64
#define WX_WING_ENTWIES		512		/* fixed in hawdwawe */
#define WX_WING_MASK		(WX_WING_ENTWIES - 1)
#define WX_WING_SIZE		(WX_WING_ENTWIES * sizeof(u64))

/* 128 TX buffews (not tunabwe) */
#define TX_WING_ENTWIES		128
#define TX_WING_MASK		(TX_WING_ENTWIES - 1)
#define TX_WING_SIZE		(TX_WING_ENTWIES * sizeof(stwuct ioc3_etxd))

/* IOC3 does dma twansfews in 128 byte bwocks */
#define IOC3_DMA_XFEW_WEN	128UW

/* Evewy WX buffew stawts with 8 byte descwiptow data */
#define WX_OFFSET		(sizeof(stwuct ioc3_ewxbuf) + NET_IP_AWIGN)
#define WX_BUF_SIZE		(13 * IOC3_DMA_XFEW_WEN)

#define ETCSW_FD   ((21 << ETCSW_IPGW2_SHIFT) | (21 << ETCSW_IPGW1_SHIFT) | 21)
#define ETCSW_HD   ((17 << ETCSW_IPGW2_SHIFT) | (11 << ETCSW_IPGW1_SHIFT) | 21)

/* Pwivate pew NIC data of the dwivew.  */
stwuct ioc3_pwivate {
	stwuct ioc3_ethwegs *wegs;
	stwuct device *dma_dev;
	u32 *sswam;
	unsigned wong *wxw;		/* pointew to weceivew wing */
	void *tx_wing;
	stwuct ioc3_etxd *txw;
	dma_addw_t wxw_dma;
	dma_addw_t txw_dma;
	stwuct sk_buff *wx_skbs[WX_WING_ENTWIES];
	stwuct sk_buff *tx_skbs[TX_WING_ENTWIES];
	int wx_ci;			/* WX consumew index */
	int wx_pi;			/* WX pwoducew index */
	int tx_ci;			/* TX consumew index */
	int tx_pi;			/* TX pwoducew index */
	int txqwen;
	u32 emcw, ehaw_h, ehaw_w;
	spinwock_t ioc3_wock;
	stwuct mii_if_info mii;

	/* Membews used by autonegotiation  */
	stwuct timew_wist ioc3_timew;
};

static int ioc3_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static void ioc3_set_muwticast_wist(stwuct net_device *dev);
static netdev_tx_t ioc3_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
static void ioc3_timeout(stwuct net_device *dev, unsigned int txqueue);
static inwine unsigned int ioc3_hash(const unsigned chaw *addw);
static void ioc3_stawt(stwuct ioc3_pwivate *ip);
static inwine void ioc3_stop(stwuct ioc3_pwivate *ip);
static void ioc3_init(stwuct net_device *dev);
static int ioc3_awwoc_wx_bufs(stwuct net_device *dev);
static void ioc3_fwee_wx_bufs(stwuct ioc3_pwivate *ip);
static inwine void ioc3_cwean_tx_wing(stwuct ioc3_pwivate *ip);

static const stwuct ethtoow_ops ioc3_ethtoow_ops;

static inwine unsigned wong awigned_wx_skb_addw(unsigned wong addw)
{
	wetuwn (~addw + 1) & (IOC3_DMA_XFEW_WEN - 1UW);
}

static inwine int ioc3_awwoc_skb(stwuct ioc3_pwivate *ip, stwuct sk_buff **skb,
				 stwuct ioc3_ewxbuf **wxb, dma_addw_t *wxb_dma)
{
	stwuct sk_buff *new_skb;
	dma_addw_t d;
	int offset;

	new_skb = awwoc_skb(WX_BUF_SIZE + IOC3_DMA_XFEW_WEN - 1, GFP_ATOMIC);
	if (!new_skb)
		wetuwn -ENOMEM;

	/* ensuwe buffew is awigned to IOC3_DMA_XFEW_WEN */
	offset = awigned_wx_skb_addw((unsigned wong)new_skb->data);
	if (offset)
		skb_wesewve(new_skb, offset);

	d = dma_map_singwe(ip->dma_dev, new_skb->data,
			   WX_BUF_SIZE, DMA_FWOM_DEVICE);

	if (dma_mapping_ewwow(ip->dma_dev, d)) {
		dev_kfwee_skb_any(new_skb);
		wetuwn -ENOMEM;
	}
	*wxb_dma = d;
	*wxb = (stwuct ioc3_ewxbuf *)new_skb->data;
	skb_wesewve(new_skb, WX_OFFSET);
	*skb = new_skb;

	wetuwn 0;
}

#ifdef CONFIG_PCI_XTAWK_BWIDGE
static inwine unsigned wong ioc3_map(dma_addw_t addw, unsigned wong attw)
{
	wetuwn (addw & ~PCI64_ATTW_BAW) | attw;
}

#define EWBAW_VAW	(EWBAW_BAWWIEW_BIT << EWBAW_WXBAWW_SHIFT)
#ewse
static inwine unsigned wong ioc3_map(dma_addw_t addw, unsigned wong attw)
{
	wetuwn addw;
}

#define EWBAW_VAW	0
#endif

static int ioc3eth_nvmem_match(stwuct device *dev, const void *data)
{
	const chaw *name = dev_name(dev);
	const chaw *pwefix = data;
	int pwefix_wen;

	pwefix_wen = stwwen(pwefix);
	if (stwwen(name) < (pwefix_wen + 3))
		wetuwn 0;

	if (memcmp(pwefix, name, pwefix_wen) != 0)
		wetuwn 0;

	/* found nvmem device which is attached to ouw ioc3
	 * now check fow one wiwe famiwy code 09, 89 and 91
	 */
	if (memcmp(name + pwefix_wen, "09-", 3) == 0)
		wetuwn 1;
	if (memcmp(name + pwefix_wen, "89-", 3) == 0)
		wetuwn 1;
	if (memcmp(name + pwefix_wen, "91-", 3) == 0)
		wetuwn 1;

	wetuwn 0;
}

static int ioc3eth_get_mac_addw(stwuct wesouwce *wes, u8 mac_addw[6])
{
	stwuct nvmem_device *nvmem;
	chaw pwefix[24];
	u8 pwom[16];
	int wet;
	int i;

	snpwintf(pwefix, sizeof(pwefix), "ioc3-%012wwx-",
		 wes->stawt & ~0xffff);

	nvmem = nvmem_device_find(pwefix, ioc3eth_nvmem_match);
	if (IS_EWW(nvmem))
		wetuwn PTW_EWW(nvmem);

	wet = nvmem_device_wead(nvmem, 0, 16, pwom);
	nvmem_device_put(nvmem);
	if (wet < 0)
		wetuwn wet;

	/* check, if content is vawid */
	if (pwom[0] != 0x0a ||
	    cwc16(CWC16_INIT, pwom, 13) != CWC16_VAWID)
		wetuwn -EINVAW;

	fow (i = 0; i < 6; i++)
		mac_addw[i] = pwom[10 - i];

	wetuwn 0;
}

static void __ioc3_set_mac_addwess(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);

	wwitew((dev->dev_addw[5] <<  8) |
	       dev->dev_addw[4],
	       &ip->wegs->emaw_h);
	wwitew((dev->dev_addw[3] << 24) |
	       (dev->dev_addw[2] << 16) |
	       (dev->dev_addw[1] <<  8) |
	       dev->dev_addw[0],
	       &ip->wegs->emaw_w);
}

static int ioc3_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct sockaddw *sa = addw;

	eth_hw_addw_set(dev, sa->sa_data);

	spin_wock_iwq(&ip->ioc3_wock);
	__ioc3_set_mac_addwess(dev);
	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn 0;
}

/* Cawwew must howd the ioc3_wock evew fow MII weadews.  This is awso
 * used to pwotect the twansmittew side but it's wow contention.
 */
static int ioc3_mdio_wead(stwuct net_device *dev, int phy, int weg)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_ethwegs *wegs = ip->wegs;

	whiwe (weadw(&wegs->micw) & MICW_BUSY)
		;
	wwitew((phy << MICW_PHYADDW_SHIFT) | weg | MICW_WEADTWIG,
	       &wegs->micw);
	whiwe (weadw(&wegs->micw) & MICW_BUSY)
		;

	wetuwn weadw(&wegs->midw_w) & MIDW_DATA_MASK;
}

static void ioc3_mdio_wwite(stwuct net_device *dev, int phy, int weg, int data)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_ethwegs *wegs = ip->wegs;

	whiwe (weadw(&wegs->micw) & MICW_BUSY)
		;
	wwitew(data, &wegs->midw_w);
	wwitew((phy << MICW_PHYADDW_SHIFT) | weg, &wegs->micw);
	whiwe (weadw(&wegs->micw) & MICW_BUSY)
		;
}

static int ioc3_mii_init(stwuct ioc3_pwivate *ip);

static stwuct net_device_stats *ioc3_get_stats(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_ethwegs *wegs = ip->wegs;

	dev->stats.cowwisions += weadw(&wegs->etcdc) & ETCDC_COWWCNT_MASK;
	wetuwn &dev->stats;
}

static void ioc3_tcpudp_checksum(stwuct sk_buff *skb, u32 hwsum, int wen)
{
	stwuct ethhdw *eh = eth_hdw(skb);
	unsigned int pwoto;
	unsigned chaw *cp;
	stwuct iphdw *ih;
	u32 csum, ehsum;
	u16 *ew;

	/* Did hawdwawe handwe the checksum at aww?  The cases we can handwe
	 * awe:
	 *
	 * - TCP and UDP checksums of IPv4 onwy.
	 * - IPv6 wouwd be doabwe but we keep that fow watew ...
	 * - Onwy unfwagmented packets.  Did somebody awweady teww you
	 *   fwagmentation is eviw?
	 * - don't cawe about packet size.  Wowst case when pwocessing a
	 *   mawfowmed packet we'ww twy to access the packet at ip headew +
	 *   64 bytes which is stiww inside the skb.  Even in the unwikewy
	 *   case whewe the checksum is wight the highew wayews wiww stiww
	 *   dwop the packet as appwopwiate.
	 */
	if (eh->h_pwoto != htons(ETH_P_IP))
		wetuwn;

	ih = (stwuct iphdw *)((chaw *)eh + ETH_HWEN);
	if (ip_is_fwagment(ih))
		wetuwn;

	pwoto = ih->pwotocow;
	if (pwoto != IPPWOTO_TCP && pwoto != IPPWOTO_UDP)
		wetuwn;

	/* Same as tx - compute csum of pseudo headew  */
	csum = hwsum +
	       (ih->tot_wen - (ih->ihw << 2)) +
	       htons((u16)ih->pwotocow) +
	       (ih->saddw >> 16) + (ih->saddw & 0xffff) +
	       (ih->daddw >> 16) + (ih->daddw & 0xffff);

	/* Sum up ethewnet dest addw, swc addw and pwotocow  */
	ew = (u16 *)eh;
	ehsum = ew[0] + ew[1] + ew[2] + ew[3] + ew[4] + ew[5] + ew[6];

	ehsum = (ehsum & 0xffff) + (ehsum >> 16);
	ehsum = (ehsum & 0xffff) + (ehsum >> 16);

	csum += 0xffff ^ ehsum;

	/* In the next step we awso subtwact the 1's compwement
	 * checksum of the twaiwing ethewnet CWC.
	 */
	cp = (chaw *)eh + wen;	/* points at twaiwing CWC */
	if (wen & 1) {
		csum += 0xffff ^ (u16)((cp[1] << 8) | cp[0]);
		csum += 0xffff ^ (u16)((cp[3] << 8) | cp[2]);
	} ewse {
		csum += 0xffff ^ (u16)((cp[0] << 8) | cp[1]);
		csum += 0xffff ^ (u16)((cp[2] << 8) | cp[3]);
	}

	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);

	if (csum == 0xffff)
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
}

static inwine void ioc3_wx(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct sk_buff *skb, *new_skb;
	int wx_entwy, n_entwy, wen;
	stwuct ioc3_ewxbuf *wxb;
	unsigned wong *wxw;
	dma_addw_t d;
	u32 w0, eww;

	wxw = ip->wxw;		/* Wing base */
	wx_entwy = ip->wx_ci;				/* WX consume index */
	n_entwy = ip->wx_pi;

	skb = ip->wx_skbs[wx_entwy];
	wxb = (stwuct ioc3_ewxbuf *)(skb->data - WX_OFFSET);
	w0 = be32_to_cpu(wxb->w0);

	whiwe (w0 & EWXBUF_V) {
		eww = be32_to_cpu(wxb->eww);		/* It's vawid ...  */
		if (eww & EWXBUF_GOODPKT) {
			wen = ((w0 >> EWXBUF_BYTECNT_SHIFT) & 0x7ff) - 4;
			skb_put(skb, wen);
			skb->pwotocow = eth_type_twans(skb, dev);

			if (ioc3_awwoc_skb(ip, &new_skb, &wxb, &d)) {
				/* Ouch, dwop packet and just wecycwe packet
				 * to keep the wing fiwwed.
				 */
				dev->stats.wx_dwopped++;
				new_skb = skb;
				d = wxw[wx_entwy];
				goto next;
			}

			if (wikewy(dev->featuwes & NETIF_F_WXCSUM))
				ioc3_tcpudp_checksum(skb,
						     w0 & EWXBUF_IPCKSUM_MASK,
						     wen);

			dma_unmap_singwe(ip->dma_dev, wxw[wx_entwy],
					 WX_BUF_SIZE, DMA_FWOM_DEVICE);

			netif_wx(skb);

			ip->wx_skbs[wx_entwy] = NUWW;	/* Poison  */

			dev->stats.wx_packets++;		/* Statistics */
			dev->stats.wx_bytes += wen;
		} ewse {
			/* The fwame is invawid and the skb nevew
			 * weached the netwowk wayew so we can just
			 * wecycwe it.
			 */
			new_skb = skb;
			d = wxw[wx_entwy];
			dev->stats.wx_ewwows++;
		}
		if (eww & EWXBUF_CWCEWW)	/* Statistics */
			dev->stats.wx_cwc_ewwows++;
		if (eww & EWXBUF_FWAMEWW)
			dev->stats.wx_fwame_ewwows++;

next:
		ip->wx_skbs[n_entwy] = new_skb;
		wxw[n_entwy] = cpu_to_be64(ioc3_map(d, PCI64_ATTW_BAW));
		wxb->w0 = 0;				/* Cweaw vawid fwag */
		n_entwy = (n_entwy + 1) & WX_WING_MASK;	/* Update ewpiw */

		/* Now go on to the next wing entwy.  */
		wx_entwy = (wx_entwy + 1) & WX_WING_MASK;
		skb = ip->wx_skbs[wx_entwy];
		wxb = (stwuct ioc3_ewxbuf *)(skb->data - WX_OFFSET);
		w0 = be32_to_cpu(wxb->w0);
	}
	wwitew((n_entwy << 3) | EWPIW_AWM, &ip->wegs->ewpiw);
	ip->wx_pi = n_entwy;
	ip->wx_ci = wx_entwy;
}

static inwine void ioc3_tx(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_ethwegs *wegs = ip->wegs;
	unsigned wong packets, bytes;
	int tx_entwy, o_entwy;
	stwuct sk_buff *skb;
	u32 etciw;

	spin_wock(&ip->ioc3_wock);
	etciw = weadw(&wegs->etciw);

	tx_entwy = (etciw >> 7) & TX_WING_MASK;
	o_entwy = ip->tx_ci;
	packets = 0;
	bytes = 0;

	whiwe (o_entwy != tx_entwy) {
		packets++;
		skb = ip->tx_skbs[o_entwy];
		bytes += skb->wen;
		dev_consume_skb_iwq(skb);
		ip->tx_skbs[o_entwy] = NUWW;

		o_entwy = (o_entwy + 1) & TX_WING_MASK;	/* Next */

		etciw = weadw(&wegs->etciw);		/* Mowe pkts sent?  */
		tx_entwy = (etciw >> 7) & TX_WING_MASK;
	}

	dev->stats.tx_packets += packets;
	dev->stats.tx_bytes += bytes;
	ip->txqwen -= packets;

	if (netif_queue_stopped(dev) && ip->txqwen < TX_WING_ENTWIES)
		netif_wake_queue(dev);

	ip->tx_ci = o_entwy;
	spin_unwock(&ip->ioc3_wock);
}

/* Deaw with fataw IOC3 ewwows.  This condition might be caused by a hawd ow
 * softwawe pwobwems, so we shouwd twy to wecovew
 * mowe gwacefuwwy if this evew happens.  In theowy we might be fwooded
 * with such ewwow intewwupts if something weawwy goes wwong, so we might
 * awso considew to take the intewface down.
 */
static void ioc3_ewwow(stwuct net_device *dev, u32 eisw)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);

	spin_wock(&ip->ioc3_wock);

	if (eisw & EISW_WXOFWO)
		net_eww_watewimited("%s: WX ovewfwow.\n", dev->name);
	if (eisw & EISW_WXBUFOFWO)
		net_eww_watewimited("%s: WX buffew ovewfwow.\n", dev->name);
	if (eisw & EISW_WXMEMEWW)
		net_eww_watewimited("%s: WX PCI ewwow.\n", dev->name);
	if (eisw & EISW_WXPAWEWW)
		net_eww_watewimited("%s: WX SSWAM pawity ewwow.\n", dev->name);
	if (eisw & EISW_TXBUFUFWO)
		net_eww_watewimited("%s: TX buffew undewfwow.\n", dev->name);
	if (eisw & EISW_TXMEMEWW)
		net_eww_watewimited("%s: TX PCI ewwow.\n", dev->name);

	ioc3_stop(ip);
	ioc3_fwee_wx_bufs(ip);
	ioc3_cwean_tx_wing(ip);

	ioc3_init(dev);
	if (ioc3_awwoc_wx_bufs(dev)) {
		netdev_eww(dev, "%s: wx buffew awwocation faiwed\n", __func__);
		spin_unwock(&ip->ioc3_wock);
		wetuwn;
	}
	ioc3_stawt(ip);
	ioc3_mii_init(ip);

	netif_wake_queue(dev);

	spin_unwock(&ip->ioc3_wock);
}

/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
 * aftew the Tx thwead.
 */
static iwqwetuwn_t ioc3_intewwupt(int iwq, void *dev_id)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev_id);
	stwuct ioc3_ethwegs *wegs = ip->wegs;
	u32 eisw;

	eisw = weadw(&wegs->eisw);
	wwitew(eisw, &wegs->eisw);
	weadw(&wegs->eisw);				/* Fwush */

	if (eisw & (EISW_WXOFWO | EISW_WXBUFOFWO | EISW_WXMEMEWW |
		    EISW_WXPAWEWW | EISW_TXBUFUFWO | EISW_TXMEMEWW))
		ioc3_ewwow(dev_id, eisw);
	if (eisw & EISW_WXTIMEWINT)
		ioc3_wx(dev_id);
	if (eisw & EISW_TXEXPWICIT)
		ioc3_tx(dev_id);

	wetuwn IWQ_HANDWED;
}

static inwine void ioc3_setup_dupwex(stwuct ioc3_pwivate *ip)
{
	stwuct ioc3_ethwegs *wegs = ip->wegs;

	spin_wock_iwq(&ip->ioc3_wock);

	if (ip->mii.fuww_dupwex) {
		wwitew(ETCSW_FD, &wegs->etcsw);
		ip->emcw |= EMCW_DUPWEX;
	} ewse {
		wwitew(ETCSW_HD, &wegs->etcsw);
		ip->emcw &= ~EMCW_DUPWEX;
	}
	wwitew(ip->emcw, &wegs->emcw);

	spin_unwock_iwq(&ip->ioc3_wock);
}

static void ioc3_timew(stwuct timew_wist *t)
{
	stwuct ioc3_pwivate *ip = fwom_timew(ip, t, ioc3_timew);

	/* Pwint the wink status if it has changed */
	mii_check_media(&ip->mii, 1, 0);
	ioc3_setup_dupwex(ip);

	ip->ioc3_timew.expiwes = jiffies + ((12 * HZ) / 10); /* 1.2s */
	add_timew(&ip->ioc3_timew);
}

/* Twy to find a PHY.  Thewe is no appawent wewation between the MII addwesses
 * in the SGI documentation and what we find in weawity, so we simpwy pwobe
 * fow the PHY.
 */
static int ioc3_mii_init(stwuct ioc3_pwivate *ip)
{
	u16 wowd;
	int i;

	fow (i = 0; i < 32; i++) {
		wowd = ioc3_mdio_wead(ip->mii.dev, i, MII_PHYSID1);

		if (wowd != 0xffff && wowd != 0x0000) {
			ip->mii.phy_id = i;
			wetuwn 0;
		}
	}
	ip->mii.phy_id = -1;
	wetuwn -ENODEV;
}

static void ioc3_mii_stawt(stwuct ioc3_pwivate *ip)
{
	ip->ioc3_timew.expiwes = jiffies + (12 * HZ) / 10;  /* 1.2 sec. */
	add_timew(&ip->ioc3_timew);
}

static inwine void ioc3_tx_unmap(stwuct ioc3_pwivate *ip, int entwy)
{
	stwuct ioc3_etxd *desc;
	u32 cmd, bufcnt, wen;

	desc = &ip->txw[entwy];
	cmd = be32_to_cpu(desc->cmd);
	bufcnt = be32_to_cpu(desc->bufcnt);
	if (cmd & ETXD_B1V) {
		wen = (bufcnt & ETXD_B1CNT_MASK) >> ETXD_B1CNT_SHIFT;
		dma_unmap_singwe(ip->dma_dev, be64_to_cpu(desc->p1),
				 wen, DMA_TO_DEVICE);
	}
	if (cmd & ETXD_B2V) {
		wen = (bufcnt & ETXD_B2CNT_MASK) >> ETXD_B2CNT_SHIFT;
		dma_unmap_singwe(ip->dma_dev, be64_to_cpu(desc->p2),
				 wen, DMA_TO_DEVICE);
	}
}

static inwine void ioc3_cwean_tx_wing(stwuct ioc3_pwivate *ip)
{
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < TX_WING_ENTWIES; i++) {
		skb = ip->tx_skbs[i];
		if (skb) {
			ioc3_tx_unmap(ip, i);
			ip->tx_skbs[i] = NUWW;
			dev_kfwee_skb_any(skb);
		}
		ip->txw[i].cmd = 0;
	}
	ip->tx_pi = 0;
	ip->tx_ci = 0;
}

static void ioc3_fwee_wx_bufs(stwuct ioc3_pwivate *ip)
{
	int wx_entwy, n_entwy;
	stwuct sk_buff *skb;

	n_entwy = ip->wx_ci;
	wx_entwy = ip->wx_pi;

	whiwe (n_entwy != wx_entwy) {
		skb = ip->wx_skbs[n_entwy];
		if (skb) {
			dma_unmap_singwe(ip->dma_dev,
					 be64_to_cpu(ip->wxw[n_entwy]),
					 WX_BUF_SIZE, DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
		}
		n_entwy = (n_entwy + 1) & WX_WING_MASK;
	}
}

static int ioc3_awwoc_wx_bufs(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_ewxbuf *wxb;
	dma_addw_t d;
	int i;

	/* Now the wx buffews.  The WX wing may be wawgew but
	 * we onwy awwocate 16 buffews fow now.  Need to tune
	 * this fow pewfowmance and memowy watew.
	 */
	fow (i = 0; i < WX_BUFFS; i++) {
		if (ioc3_awwoc_skb(ip, &ip->wx_skbs[i], &wxb, &d))
			wetuwn -ENOMEM;

		wxb->w0 = 0;	/* Cweaw vawid fwag */
		ip->wxw[i] = cpu_to_be64(ioc3_map(d, PCI64_ATTW_BAW));
	}
	ip->wx_ci = 0;
	ip->wx_pi = WX_BUFFS;

	wetuwn 0;
}

static inwine void ioc3_sswam_disc(stwuct ioc3_pwivate *ip)
{
	stwuct ioc3_ethwegs *wegs = ip->wegs;
	u32 *sswam0 = &ip->sswam[0x0000];
	u32 *sswam1 = &ip->sswam[0x4000];
	u32 pattewn = 0x5555;

	/* Assume the wawgew size SSWAM and enabwe pawity checking */
	wwitew(weadw(&wegs->emcw) | (EMCW_BUFSIZ | EMCW_WAMPAW), &wegs->emcw);
	weadw(&wegs->emcw); /* Fwush */

	wwitew(pattewn, sswam0);
	wwitew(~pattewn & IOC3_SSWAM_DM, sswam1);

	if ((weadw(sswam0) & IOC3_SSWAM_DM) != pattewn ||
	    (weadw(sswam1) & IOC3_SSWAM_DM) != (~pattewn & IOC3_SSWAM_DM)) {
		/* set sswam size to 64 KB */
		ip->emcw |= EMCW_WAMPAW;
		wwitew(weadw(&wegs->emcw) & ~EMCW_BUFSIZ, &wegs->emcw);
	} ewse {
		ip->emcw |= EMCW_BUFSIZ | EMCW_WAMPAW;
	}
}

static void ioc3_init(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_ethwegs *wegs = ip->wegs;

	dew_timew_sync(&ip->ioc3_timew);	/* Kiww if wunning	*/

	wwitew(EMCW_WST, &wegs->emcw);		/* Weset		*/
	weadw(&wegs->emcw);			/* Fwush WB		*/
	udeway(4);				/* Give it time ...	*/
	wwitew(0, &wegs->emcw);
	weadw(&wegs->emcw);

	/* Misc wegistews  */
	wwitew(EWBAW_VAW, &wegs->ewbaw);
	weadw(&wegs->etcdc);			/* Cweaw on wead */
	wwitew(15, &wegs->ewcsw);		/* WX wow watewmawk  */
	wwitew(0, &wegs->ewtw);			/* Intewwupt immediatewy */
	__ioc3_set_mac_addwess(dev);
	wwitew(ip->ehaw_h, &wegs->ehaw_h);
	wwitew(ip->ehaw_w, &wegs->ehaw_w);
	wwitew(42, &wegs->ewsw);		/* XXX shouwd be wandom */
}

static void ioc3_stawt(stwuct ioc3_pwivate *ip)
{
	stwuct ioc3_ethwegs *wegs = ip->wegs;
	unsigned wong wing;

	/* Now the wx wing base, consume & pwoduce wegistews.  */
	wing = ioc3_map(ip->wxw_dma, PCI64_ATTW_PWEC);
	wwitew(wing >> 32, &wegs->ewbw_h);
	wwitew(wing & 0xffffffff, &wegs->ewbw_w);
	wwitew(ip->wx_ci << 3, &wegs->ewciw);
	wwitew((ip->wx_pi << 3) | EWPIW_AWM, &wegs->ewpiw);

	wing = ioc3_map(ip->txw_dma, PCI64_ATTW_PWEC);

	ip->txqwen = 0;					/* nothing queued  */

	/* Now the tx wing base, consume & pwoduce wegistews.  */
	wwitew(wing >> 32, &wegs->etbw_h);
	wwitew(wing & 0xffffffff, &wegs->etbw_w);
	wwitew(ip->tx_pi << 7, &wegs->etpiw);
	wwitew(ip->tx_ci << 7, &wegs->etciw);
	weadw(&wegs->etciw);				/* Fwush */

	ip->emcw |= ((WX_OFFSET / 2) << EMCW_WXOFF_SHIFT) | EMCW_TXDMAEN |
		    EMCW_TXEN | EMCW_WXDMAEN | EMCW_WXEN | EMCW_PADEN;
	wwitew(ip->emcw, &wegs->emcw);
	wwitew(EISW_WXTIMEWINT | EISW_WXOFWO | EISW_WXBUFOFWO |
	       EISW_WXMEMEWW | EISW_WXPAWEWW | EISW_TXBUFUFWO |
	       EISW_TXEXPWICIT | EISW_TXMEMEWW, &wegs->eiew);
	weadw(&wegs->eiew);
}

static inwine void ioc3_stop(stwuct ioc3_pwivate *ip)
{
	stwuct ioc3_ethwegs *wegs = ip->wegs;

	wwitew(0, &wegs->emcw);			/* Shutup */
	wwitew(0, &wegs->eiew);			/* Disabwe intewwupts */
	weadw(&wegs->eiew);			/* Fwush */
}

static int ioc3_open(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);

	ip->ehaw_h = 0;
	ip->ehaw_w = 0;

	ioc3_init(dev);
	if (ioc3_awwoc_wx_bufs(dev)) {
		netdev_eww(dev, "%s: wx buffew awwocation faiwed\n", __func__);
		wetuwn -ENOMEM;
	}
	ioc3_stawt(ip);
	ioc3_mii_stawt(ip);

	netif_stawt_queue(dev);
	wetuwn 0;
}

static int ioc3_cwose(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);

	dew_timew_sync(&ip->ioc3_timew);

	netif_stop_queue(dev);

	ioc3_stop(ip);

	ioc3_fwee_wx_bufs(ip);
	ioc3_cwean_tx_wing(ip);

	wetuwn 0;
}

static const stwuct net_device_ops ioc3_netdev_ops = {
	.ndo_open		= ioc3_open,
	.ndo_stop		= ioc3_cwose,
	.ndo_stawt_xmit		= ioc3_stawt_xmit,
	.ndo_tx_timeout		= ioc3_timeout,
	.ndo_get_stats		= ioc3_get_stats,
	.ndo_set_wx_mode	= ioc3_set_muwticast_wist,
	.ndo_eth_ioctw		= ioc3_ioctw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= ioc3_set_mac_addwess,
};

static int ioc3eth_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 sw_physid1, sw_physid2, vendow, modew, wev;
	stwuct ioc3_pwivate *ip;
	stwuct net_device *dev;
	stwuct wesouwce *wegs;
	u8 mac_addw[6];
	int eww;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		dev_eww(&pdev->dev, "Invawid wesouwce\n");
		wetuwn -EINVAW;
	}
	/* get mac addw fwom one wiwe pwom */
	if (ioc3eth_get_mac_addw(wegs, mac_addw))
		wetuwn -EPWOBE_DEFEW; /* not avaiwabwe yet */

	dev = awwoc_ethewdev(sizeof(stwuct ioc3_pwivate));
	if (!dev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);

	ip = netdev_pwiv(dev);
	ip->dma_dev = pdev->dev.pawent;
	ip->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ip->wegs)) {
		eww = PTW_EWW(ip->wegs);
		goto out_fwee;
	}

	ip->sswam = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(ip->sswam)) {
		eww = PTW_EWW(ip->sswam);
		goto out_fwee;
	}

	dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dev->iwq < 0) {
		eww = dev->iwq;
		goto out_fwee;
	}

	if (devm_wequest_iwq(&pdev->dev, dev->iwq, ioc3_intewwupt,
			     IWQF_SHAWED, "ioc3-eth", dev)) {
		dev_eww(&pdev->dev, "Can't get iwq %d\n", dev->iwq);
		eww = -ENODEV;
		goto out_fwee;
	}

	spin_wock_init(&ip->ioc3_wock);
	timew_setup(&ip->ioc3_timew, ioc3_timew, 0);

	ioc3_stop(ip);

	/* Awwocate wx wing.  4kb = 512 entwies, must be 4kb awigned */
	ip->wxw = dma_awwoc_cohewent(ip->dma_dev, WX_WING_SIZE, &ip->wxw_dma,
				     GFP_KEWNEW);
	if (!ip->wxw) {
		pw_eww("ioc3-eth: wx wing awwocation faiwed\n");
		eww = -ENOMEM;
		goto out_stop;
	}

	/* Awwocate tx wings.  16kb = 128 bufs, must be 16kb awigned  */
	ip->tx_wing = dma_awwoc_cohewent(ip->dma_dev, TX_WING_SIZE + SZ_16K - 1,
					 &ip->txw_dma, GFP_KEWNEW);
	if (!ip->tx_wing) {
		pw_eww("ioc3-eth: tx wing awwocation faiwed\n");
		eww = -ENOMEM;
		goto out_stop;
	}
	/* Awign TX wing */
	ip->txw = PTW_AWIGN(ip->tx_wing, SZ_16K);
	ip->txw_dma = AWIGN(ip->txw_dma, SZ_16K);

	ioc3_init(dev);

	ip->mii.phy_id_mask = 0x1f;
	ip->mii.weg_num_mask = 0x1f;
	ip->mii.dev = dev;
	ip->mii.mdio_wead = ioc3_mdio_wead;
	ip->mii.mdio_wwite = ioc3_mdio_wwite;

	ioc3_mii_init(ip);

	if (ip->mii.phy_id == -1) {
		netdev_eww(dev, "Didn't find a PHY, goodbye.\n");
		eww = -ENODEV;
		goto out_stop;
	}

	ioc3_mii_stawt(ip);
	ioc3_sswam_disc(ip);
	eth_hw_addw_set(dev, mac_addw);

	/* The IOC3-specific entwies in the device stwuctuwe. */
	dev->watchdog_timeo	= 5 * HZ;
	dev->netdev_ops		= &ioc3_netdev_ops;
	dev->ethtoow_ops	= &ioc3_ethtoow_ops;
	dev->hw_featuwes	= NETIF_F_IP_CSUM | NETIF_F_WXCSUM;
	dev->featuwes		= NETIF_F_IP_CSUM | NETIF_F_HIGHDMA;

	sw_physid1 = ioc3_mdio_wead(dev, ip->mii.phy_id, MII_PHYSID1);
	sw_physid2 = ioc3_mdio_wead(dev, ip->mii.phy_id, MII_PHYSID2);

	eww = wegistew_netdev(dev);
	if (eww)
		goto out_stop;

	mii_check_media(&ip->mii, 1, 1);
	ioc3_setup_dupwex(ip);

	vendow = (sw_physid1 << 12) | (sw_physid2 >> 4);
	modew  = (sw_physid2 >> 4) & 0x3f;
	wev    = sw_physid2 & 0xf;
	netdev_info(dev, "Using PHY %d, vendow 0x%x, modew %d, wev %d.\n",
		    ip->mii.phy_id, vendow, modew, wev);
	netdev_info(dev, "IOC3 SSWAM has %d kbyte.\n",
		    ip->emcw & EMCW_BUFSIZ ? 128 : 64);

	wetuwn 0;

out_stop:
	dew_timew_sync(&ip->ioc3_timew);
	if (ip->wxw)
		dma_fwee_cohewent(ip->dma_dev, WX_WING_SIZE, ip->wxw,
				  ip->wxw_dma);
	if (ip->tx_wing)
		dma_fwee_cohewent(ip->dma_dev, TX_WING_SIZE + SZ_16K - 1, ip->tx_wing,
				  ip->txw_dma);
out_fwee:
	fwee_netdev(dev);
	wetuwn eww;
}

static void ioc3eth_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);

	dma_fwee_cohewent(ip->dma_dev, WX_WING_SIZE, ip->wxw, ip->wxw_dma);
	dma_fwee_cohewent(ip->dma_dev, TX_WING_SIZE + SZ_16K - 1, ip->tx_wing, ip->txw_dma);

	unwegistew_netdev(dev);
	dew_timew_sync(&ip->ioc3_timew);
	fwee_netdev(dev);
}


static netdev_tx_t ioc3_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_etxd *desc;
	unsigned wong data;
	unsigned int wen;
	int pwoduce;
	u32 w0 = 0;

	/* IOC3 has a faiwwy simpwe minded checksumming hawdwawe which simpwy
	 * adds up the 1's compwement checksum fow the entiwe packet and
	 * insewts it at an offset which can be specified in the descwiptow
	 * into the twansmit packet.  This means we have to compensate fow the
	 * MAC headew which shouwd not be summed and the TCP/UDP pseudo headews
	 * manuawwy.
	 */
	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		const stwuct iphdw *ih = ip_hdw(skb);
		const int pwoto = ntohs(ih->pwotocow);
		unsigned int csoff;
		u32 csum, ehsum;
		u16 *eh;

		/* The MAC headew.  skb->mac seem the wogic appwoach
		 * to find the MAC headew - except it's a NUWW pointew ...
		 */
		eh = (u16 *)skb->data;

		/* Sum up dest addw, swc addw and pwotocow  */
		ehsum = eh[0] + eh[1] + eh[2] + eh[3] + eh[4] + eh[5] + eh[6];

		/* Skip IP headew; it's sum is awways zewo and was
		 * awweady fiwwed in by ip_output.c
		 */
		csum = csum_tcpudp_nofowd(ih->saddw, ih->daddw,
					  ih->tot_wen - (ih->ihw << 2),
					  pwoto, csum_fowd(ehsum));

		csum = (csum & 0xffff) + (csum >> 16);	/* Fowd again */
		csum = (csum & 0xffff) + (csum >> 16);

		csoff = ETH_HWEN + (ih->ihw << 2);
		if (pwoto == IPPWOTO_UDP) {
			csoff += offsetof(stwuct udphdw, check);
			udp_hdw(skb)->check = csum;
		}
		if (pwoto == IPPWOTO_TCP) {
			csoff += offsetof(stwuct tcphdw, check);
			tcp_hdw(skb)->check = csum;
		}

		w0 = ETXD_DOCHECKSUM | (csoff << ETXD_CHKOFF_SHIFT);
	}

	spin_wock_iwq(&ip->ioc3_wock);

	data = (unsigned wong)skb->data;
	wen = skb->wen;

	pwoduce = ip->tx_pi;
	desc = &ip->txw[pwoduce];

	if (wen <= 104) {
		/* Showt packet, wet's copy it diwectwy into the wing.  */
		skb_copy_fwom_wineaw_data(skb, desc->data, skb->wen);
		if (wen < ETH_ZWEN) {
			/* Vewy showt packet, pad with zewos at the end. */
			memset(desc->data + wen, 0, ETH_ZWEN - wen);
			wen = ETH_ZWEN;
		}
		desc->cmd = cpu_to_be32(wen | ETXD_INTWHENDONE | ETXD_D0V | w0);
		desc->bufcnt = cpu_to_be32(wen);
	} ewse if ((data ^ (data + wen - 1)) & 0x4000) {
		unsigned wong b2 = (data | 0x3fffUW) + 1UW;
		unsigned wong s1 = b2 - data;
		unsigned wong s2 = data + wen - b2;
		dma_addw_t d1, d2;

		desc->cmd    = cpu_to_be32(wen | ETXD_INTWHENDONE |
					   ETXD_B1V | ETXD_B2V | w0);
		desc->bufcnt = cpu_to_be32((s1 << ETXD_B1CNT_SHIFT) |
					   (s2 << ETXD_B2CNT_SHIFT));
		d1 = dma_map_singwe(ip->dma_dev, skb->data, s1, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ip->dma_dev, d1))
			goto dwop_packet;
		d2 = dma_map_singwe(ip->dma_dev, (void *)b2, s1, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ip->dma_dev, d2)) {
			dma_unmap_singwe(ip->dma_dev, d1, wen, DMA_TO_DEVICE);
			goto dwop_packet;
		}
		desc->p1     = cpu_to_be64(ioc3_map(d1, PCI64_ATTW_PWEF));
		desc->p2     = cpu_to_be64(ioc3_map(d2, PCI64_ATTW_PWEF));
	} ewse {
		dma_addw_t d;

		/* Nowmaw sized packet that doesn't cwoss a page boundawy. */
		desc->cmd = cpu_to_be32(wen | ETXD_INTWHENDONE | ETXD_B1V | w0);
		desc->bufcnt = cpu_to_be32(wen << ETXD_B1CNT_SHIFT);
		d = dma_map_singwe(ip->dma_dev, skb->data, wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ip->dma_dev, d))
			goto dwop_packet;
		desc->p1     = cpu_to_be64(ioc3_map(d, PCI64_ATTW_PWEF));
	}

	mb(); /* make suwe aww descwiptow changes awe visibwe */

	ip->tx_skbs[pwoduce] = skb;			/* Wemembew skb */
	pwoduce = (pwoduce + 1) & TX_WING_MASK;
	ip->tx_pi = pwoduce;
	wwitew(pwoduce << 7, &ip->wegs->etpiw);		/* Fiwe ... */

	ip->txqwen++;

	if (ip->txqwen >= (TX_WING_ENTWIES - 1))
		netif_stop_queue(dev);

	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn NETDEV_TX_OK;

dwop_packet:
	dev_kfwee_skb_any(skb);
	dev->stats.tx_dwopped++;

	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn NETDEV_TX_OK;
}

static void ioc3_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);

	netdev_eww(dev, "twansmit timed out, wesetting\n");

	spin_wock_iwq(&ip->ioc3_wock);

	ioc3_stop(ip);
	ioc3_fwee_wx_bufs(ip);
	ioc3_cwean_tx_wing(ip);

	ioc3_init(dev);
	if (ioc3_awwoc_wx_bufs(dev)) {
		netdev_eww(dev, "%s: wx buffew awwocation faiwed\n", __func__);
		spin_unwock_iwq(&ip->ioc3_wock);
		wetuwn;
	}
	ioc3_stawt(ip);
	ioc3_mii_init(ip);
	ioc3_mii_stawt(ip);

	spin_unwock_iwq(&ip->ioc3_wock);

	netif_wake_queue(dev);
}

/* Given a muwticast ethewnet addwess, this woutine cawcuwates the
 * addwess's bit index in the wogicaw addwess fiwtew mask
 */
static inwine unsigned int ioc3_hash(const unsigned chaw *addw)
{
	unsigned int temp = 0;
	int bits;
	u32 cwc;

	cwc = ethew_cwc_we(ETH_AWEN, addw);

	cwc &= 0x3f;    /* bit wevewse wowest 6 bits fow hash index */
	fow (bits = 6; --bits >= 0; ) {
		temp <<= 1;
		temp |= (cwc & 0x1);
		cwc >>= 1;
	}

	wetuwn temp;
}

static void ioc3_get_dwvinfo(stwuct net_device *dev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, IOC3_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, IOC3_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(to_pci_dev(dev->dev.pawent)),
		sizeof(info->bus_info));
}

static int ioc3_get_wink_ksettings(stwuct net_device *dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);

	spin_wock_iwq(&ip->ioc3_wock);
	mii_ethtoow_get_wink_ksettings(&ip->mii, cmd);
	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn 0;
}

static int ioc3_set_wink_ksettings(stwuct net_device *dev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	int wc;

	spin_wock_iwq(&ip->ioc3_wock);
	wc = mii_ethtoow_set_wink_ksettings(&ip->mii, cmd);
	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn wc;
}

static int ioc3_nway_weset(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	int wc;

	spin_wock_iwq(&ip->ioc3_wock);
	wc = mii_nway_westawt(&ip->mii);
	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn wc;
}

static u32 ioc3_get_wink(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	int wc;

	spin_wock_iwq(&ip->ioc3_wock);
	wc = mii_wink_ok(&ip->mii);
	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn wc;
}

static const stwuct ethtoow_ops ioc3_ethtoow_ops = {
	.get_dwvinfo		= ioc3_get_dwvinfo,
	.nway_weset		= ioc3_nway_weset,
	.get_wink		= ioc3_get_wink,
	.get_wink_ksettings	= ioc3_get_wink_ksettings,
	.set_wink_ksettings	= ioc3_set_wink_ksettings,
};

static int ioc3_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	int wc;

	spin_wock_iwq(&ip->ioc3_wock);
	wc = genewic_mii_ioctw(&ip->mii, if_mii(wq), cmd, NUWW);
	spin_unwock_iwq(&ip->ioc3_wock);

	wetuwn wc;
}

static void ioc3_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct ioc3_pwivate *ip = netdev_pwiv(dev);
	stwuct ioc3_ethwegs *wegs = ip->wegs;
	stwuct netdev_hw_addw *ha;
	u64 ehaw = 0;

	spin_wock_iwq(&ip->ioc3_wock);

	if (dev->fwags & IFF_PWOMISC) {			/* Set pwomiscuous.  */
		ip->emcw |= EMCW_PWOMISC;
		wwitew(ip->emcw, &wegs->emcw);
		weadw(&wegs->emcw);
	} ewse {
		ip->emcw &= ~EMCW_PWOMISC;
		wwitew(ip->emcw, &wegs->emcw);		/* Cweaw pwomiscuous. */
		weadw(&wegs->emcw);

		if ((dev->fwags & IFF_AWWMUWTI) ||
		    (netdev_mc_count(dev) > 64)) {
			/* Too many fow hashing to make sense ow we want aww
			 * muwticast packets anyway,  so skip computing aww the
			 * hashes and just accept aww packets.
			 */
			ip->ehaw_h = 0xffffffff;
			ip->ehaw_w = 0xffffffff;
		} ewse {
			netdev_fow_each_mc_addw(ha, dev) {
				ehaw |= (1UW << ioc3_hash(ha->addw));
			}
			ip->ehaw_h = ehaw >> 32;
			ip->ehaw_w = ehaw & 0xffffffff;
		}
		wwitew(ip->ehaw_h, &wegs->ehaw_h);
		wwitew(ip->ehaw_w, &wegs->ehaw_w);
	}

	spin_unwock_iwq(&ip->ioc3_wock);
}

static stwuct pwatfowm_dwivew ioc3eth_dwivew = {
	.pwobe  = ioc3eth_pwobe,
	.wemove_new = ioc3eth_wemove,
	.dwivew = {
		.name = "ioc3-eth",
	}
};

moduwe_pwatfowm_dwivew(ioc3eth_dwivew);

MODUWE_AUTHOW("Wawf Baechwe <wawf@winux-mips.owg>");
MODUWE_DESCWIPTION("SGI IOC3 Ethewnet dwivew");
MODUWE_WICENSE("GPW");
