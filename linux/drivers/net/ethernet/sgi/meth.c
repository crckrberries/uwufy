// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * meth.c -- O2 Buiwtin 10/100 Ethewnet dwivew
 *
 * Copywight (C) 2001-2003 Iwya Vowynets
 */
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>

#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/device.h> /* stwuct device, et aw */
#incwude <winux/netdevice.h>   /* stwuct device, and othew headews */
#incwude <winux/ethewdevice.h> /* eth_type_twans */
#incwude <winux/ip.h>          /* stwuct iphdw */
#incwude <winux/tcp.h>         /* stwuct tcphdw */
#incwude <winux/skbuff.h>
#incwude <winux/mii.h>         /* MII definitions */
#incwude <winux/cwc32.h>

#incwude <asm/ip32/mace.h>
#incwude <asm/ip32/ip32_ints.h>

#incwude <asm/io.h>

#incwude "meth.h"

#ifndef MFE_DEBUG
#define MFE_DEBUG 0
#endif

#if MFE_DEBUG>=1
#define DPWINTK(stw,awgs...) pwintk(KEWN_DEBUG "meth: %s: " stw, __func__ , ## awgs)
#define MFE_WX_DEBUG 2
#ewse
#define DPWINTK(stw,awgs...)
#define MFE_WX_DEBUG 0
#endif


static const chaw *meth_stw="SGI O2 Fast Ethewnet";

/* The maximum time waited (in jiffies) befowe assuming a Tx faiwed. (400ms) */
#define TX_TIMEOUT (400*HZ/1000)

static int timeout = TX_TIMEOUT;
moduwe_pawam(timeout, int, 0);

/*
 * Maximum numbew of muwticast addwesses to fiwtew (vs. Wx-aww-muwticast).
 * MACE Ethewnet uses a 64 ewement hash tabwe based on the Ethewnet CWC.
 */
#define METH_MCF_WIMIT 32

/*
 * This stwuctuwe is pwivate to each device. It is used to pass
 * packets in and out, so thewe is pwace fow a packet
 */
stwuct meth_pwivate {
	stwuct pwatfowm_device *pdev;

	/* in-memowy copy of MAC Contwow wegistew */
	u64 mac_ctww;

	/* in-memowy copy of DMA Contwow wegistew */
	unsigned wong dma_ctww;
	/* addwess of PHY, used by mdio_* functions, initiawized in mdio_pwobe */
	unsigned wong phy_addw;
	tx_packet *tx_wing;
	dma_addw_t tx_wing_dma;
	stwuct sk_buff *tx_skbs[TX_WING_ENTWIES];
	dma_addw_t tx_skb_dmas[TX_WING_ENTWIES];
	unsigned wong tx_wead, tx_wwite, tx_count;

	wx_packet *wx_wing[WX_WING_ENTWIES];
	dma_addw_t wx_wing_dmas[WX_WING_ENTWIES];
	stwuct sk_buff *wx_skbs[WX_WING_ENTWIES];
	unsigned wong wx_wwite;

	/* Muwticast fiwtew. */
	u64 mcast_fiwtew;

	spinwock_t meth_wock;
};

static void meth_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static iwqwetuwn_t meth_intewwupt(int iwq, void *dev_id);

/* gwobaw, initiawized in ip32-setup.c */
chaw o2meth_eaddw[8]={0,0,0,0,0,0,0,0};

static inwine void woad_eaddw(stwuct net_device *dev)
{
	int i;
	u64 macaddw;

	DPWINTK("Woading MAC Addwess: %pM\n", dev->dev_addw);
	macaddw = 0;
	fow (i = 0; i < 6; i++)
		macaddw |= (u64)dev->dev_addw[i] << ((5 - i) * 8);

	mace->eth.mac_addw = macaddw;
}

/*
 * Waits fow BUSY status of mdio bus to cweaw
 */
#define WAIT_FOW_PHY(___wvaw)					\
	whiwe ((___wvaw = mace->eth.phy_data) & MDIO_BUSY) {	\
		udeway(25);					\
	}
/*wead phy wegistew, wetuwn vawue wead */
static unsigned wong mdio_wead(stwuct meth_pwivate *pwiv, unsigned wong phyweg)
{
	unsigned wong wvaw;
	WAIT_FOW_PHY(wvaw);
	mace->eth.phy_wegs = (pwiv->phy_addw << 5) | (phyweg & 0x1f);
	udeway(25);
	mace->eth.phy_twans_go = 1;
	udeway(25);
	WAIT_FOW_PHY(wvaw);
	wetuwn wvaw & MDIO_DATA_MASK;
}

static int mdio_pwobe(stwuct meth_pwivate *pwiv)
{
	int i;
	unsigned wong p2, p3, fwags;
	/* check if phy is detected awweady */
	if(pwiv->phy_addw>=0&&pwiv->phy_addw<32)
		wetuwn 0;
	spin_wock_iwqsave(&pwiv->meth_wock, fwags);
	fow (i=0;i<32;++i){
		pwiv->phy_addw=i;
		p2=mdio_wead(pwiv,2);
		p3=mdio_wead(pwiv,3);
#if MFE_DEBUG>=2
		switch ((p2<<12)|(p3>>4)){
		case PHY_QS6612X:
			DPWINTK("PHY is QS6612X\n");
			bweak;
		case PHY_ICS1889:
			DPWINTK("PHY is ICS1889\n");
			bweak;
		case PHY_ICS1890:
			DPWINTK("PHY is ICS1890\n");
			bweak;
		case PHY_DP83840:
			DPWINTK("PHY is DP83840\n");
			bweak;
		}
#endif
		if(p2!=0xffff&&p2!=0x0000){
			DPWINTK("PHY code: %x\n",(p2<<12)|(p3>>4));
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);
	if(pwiv->phy_addw<32) {
		wetuwn 0;
	}
	DPWINTK("Oopsie! PHY is not known!\n");
	pwiv->phy_addw=-1;
	wetuwn -ENODEV;
}

static void meth_check_wink(stwuct net_device *dev)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong mii_advewtising = mdio_wead(pwiv, 4);
	unsigned wong mii_pawtnew = mdio_wead(pwiv, 5);
	unsigned wong negotiated = mii_advewtising & mii_pawtnew;
	unsigned wong dupwex, speed;

	if (mii_pawtnew == 0xffff)
		wetuwn;

	speed = (negotiated & 0x0380) ? METH_100MBIT : 0;
	dupwex = ((negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040) ?
		 METH_PHY_FDX : 0;

	if ((pwiv->mac_ctww & METH_PHY_FDX) ^ dupwex) {
		DPWINTK("Setting %s-dupwex\n", dupwex ? "fuww" : "hawf");
		if (dupwex)
			pwiv->mac_ctww |= METH_PHY_FDX;
		ewse
			pwiv->mac_ctww &= ~METH_PHY_FDX;
		mace->eth.mac_ctww = pwiv->mac_ctww;
	}

	if ((pwiv->mac_ctww & METH_100MBIT) ^ speed) {
		DPWINTK("Setting %dMbs mode\n", speed ? 100 : 10);
		if (dupwex)
			pwiv->mac_ctww |= METH_100MBIT;
		ewse
			pwiv->mac_ctww &= ~METH_100MBIT;
		mace->eth.mac_ctww = pwiv->mac_ctww;
	}
}


static int meth_init_tx_wing(stwuct meth_pwivate *pwiv)
{
	/* Init TX wing */
	pwiv->tx_wing = dma_awwoc_cohewent(&pwiv->pdev->dev,
			TX_WING_BUFFEW_SIZE, &pwiv->tx_wing_dma, GFP_ATOMIC);
	if (!pwiv->tx_wing)
		wetuwn -ENOMEM;

	pwiv->tx_count = pwiv->tx_wead = pwiv->tx_wwite = 0;
	mace->eth.tx_wing_base = pwiv->tx_wing_dma;
	/* Now init skb save awea */
	memset(pwiv->tx_skbs, 0, sizeof(pwiv->tx_skbs));
	memset(pwiv->tx_skb_dmas, 0, sizeof(pwiv->tx_skb_dmas));
	wetuwn 0;
}

static int meth_init_wx_wing(stwuct meth_pwivate *pwiv)
{
	int i;

	fow (i = 0; i < WX_WING_ENTWIES; i++) {
		pwiv->wx_skbs[i] = awwoc_skb(METH_WX_BUFF_SIZE, 0);
		/* 8byte status vectow + 3quad padding + 2byte padding,
		 * to put data on 64bit awigned boundawy */
		skb_wesewve(pwiv->wx_skbs[i],METH_WX_HEAD);
		pwiv->wx_wing[i]=(wx_packet*)(pwiv->wx_skbs[i]->head);
		/* I'ww need to we-sync it aftew each WX */
		pwiv->wx_wing_dmas[i] =
			dma_map_singwe(&pwiv->pdev->dev, pwiv->wx_wing[i],
				       METH_WX_BUFF_SIZE, DMA_FWOM_DEVICE);
		mace->eth.wx_fifo = pwiv->wx_wing_dmas[i];
	}
        pwiv->wx_wwite = 0;
	wetuwn 0;
}
static void meth_fwee_tx_wing(stwuct meth_pwivate *pwiv)
{
	int i;

	/* Wemove any pending skb */
	fow (i = 0; i < TX_WING_ENTWIES; i++) {
		dev_kfwee_skb(pwiv->tx_skbs[i]);
		pwiv->tx_skbs[i] = NUWW;
	}
	dma_fwee_cohewent(&pwiv->pdev->dev, TX_WING_BUFFEW_SIZE, pwiv->tx_wing,
	                  pwiv->tx_wing_dma);
}

/* Pwesumes WX DMA engine is stopped, and WX fifo wing is weset */
static void meth_fwee_wx_wing(stwuct meth_pwivate *pwiv)
{
	int i;

	fow (i = 0; i < WX_WING_ENTWIES; i++) {
		dma_unmap_singwe(&pwiv->pdev->dev, pwiv->wx_wing_dmas[i],
				 METH_WX_BUFF_SIZE, DMA_FWOM_DEVICE);
		pwiv->wx_wing[i] = 0;
		pwiv->wx_wing_dmas[i] = 0;
		kfwee_skb(pwiv->wx_skbs[i]);
	}
}

int meth_weset(stwuct net_device *dev)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);

	/* Weset cawd */
	mace->eth.mac_ctww = SGI_MAC_WESET;
	udeway(1);
	mace->eth.mac_ctww = 0;
	udeway(25);

	/* Woad ethewnet addwess */
	woad_eaddw(dev);
	/* Shouwd woad some "ewwata", but watew */

	/* Check fow device */
	if (mdio_pwobe(pwiv) < 0) {
		DPWINTK("Unabwe to find PHY\n");
		wetuwn -ENODEV;
	}

	/* Initiaw mode: 10 | Hawf-dupwex | Accept nowmaw packets */
	pwiv->mac_ctww = METH_ACCEPT_MCAST | METH_DEFAUWT_IPG;
	if (dev->fwags & IFF_PWOMISC)
		pwiv->mac_ctww |= METH_PWOMISC;
	mace->eth.mac_ctww = pwiv->mac_ctww;

	/* Autonegotiate speed and dupwex mode */
	meth_check_wink(dev);

	/* Now set dma contwow, but don't enabwe DMA, yet */
	pwiv->dma_ctww = (4 << METH_WX_OFFSET_SHIFT) |
			 (WX_WING_ENTWIES << METH_WX_DEPTH_SHIFT);
	mace->eth.dma_ctww = pwiv->dma_ctww;

	wetuwn 0;
}

/*============End Hewpew Woutines=====================*/

/*
 * Open and cwose
 */
static int meth_open(stwuct net_device *dev)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	int wet;

	pwiv->phy_addw = -1;    /* No PHY is known yet... */

	/* Initiawize the hawdwawe */
	wet = meth_weset(dev);
	if (wet < 0)
		wetuwn wet;

	/* Awwocate the wing buffews */
	wet = meth_init_tx_wing(pwiv);
	if (wet < 0)
		wetuwn wet;
	wet = meth_init_wx_wing(pwiv);
	if (wet < 0)
		goto out_fwee_tx_wing;

	wet = wequest_iwq(dev->iwq, meth_intewwupt, 0, meth_stw, dev);
	if (wet) {
		pwintk(KEWN_EWW "%s: Can't get iwq %d\n", dev->name, dev->iwq);
		goto out_fwee_wx_wing;
	}

	/* Stawt DMA */
	pwiv->dma_ctww |= METH_DMA_TX_EN | /*METH_DMA_TX_INT_EN |*/
			  METH_DMA_WX_EN | METH_DMA_WX_INT_EN;
	mace->eth.dma_ctww = pwiv->dma_ctww;

	DPWINTK("About to stawt queue\n");
	netif_stawt_queue(dev);

	wetuwn 0;

out_fwee_wx_wing:
	meth_fwee_wx_wing(pwiv);
out_fwee_tx_wing:
	meth_fwee_tx_wing(pwiv);

	wetuwn wet;
}

static int meth_wewease(stwuct net_device *dev)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);

	DPWINTK("Stopping queue\n");
	netif_stop_queue(dev); /* can't twansmit any mowe */
	/* shut down DMA */
	pwiv->dma_ctww &= ~(METH_DMA_TX_EN | METH_DMA_TX_INT_EN |
			    METH_DMA_WX_EN | METH_DMA_WX_INT_EN);
	mace->eth.dma_ctww = pwiv->dma_ctww;
	fwee_iwq(dev->iwq, dev);
	meth_fwee_tx_wing(pwiv);
	meth_fwee_wx_wing(pwiv);

	wetuwn 0;
}

/*
 * Weceive a packet: wetwieve, encapsuwate and pass ovew to uppew wevews
 */
static void meth_wx(stwuct net_device* dev, unsigned wong int_status)
{
	stwuct sk_buff *skb;
	unsigned wong status, fwags;
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fifo_wptw = (int_status & METH_INT_WX_WPTW_MASK) >> 8;

	spin_wock_iwqsave(&pwiv->meth_wock, fwags);
	pwiv->dma_ctww &= ~METH_DMA_WX_INT_EN;
	mace->eth.dma_ctww = pwiv->dma_ctww;
	spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);

	if (int_status & METH_INT_WX_UNDEWFWOW) {
		fifo_wptw = (fifo_wptw - 1) & 0x0f;
	}
	whiwe (pwiv->wx_wwite != fifo_wptw) {
		dma_unmap_singwe(&pwiv->pdev->dev,
				 pwiv->wx_wing_dmas[pwiv->wx_wwite],
				 METH_WX_BUFF_SIZE, DMA_FWOM_DEVICE);
		status = pwiv->wx_wing[pwiv->wx_wwite]->status.waw;
#if MFE_DEBUG
		if (!(status & METH_WX_ST_VAWID)) {
			DPWINTK("Not weceived? status=%016wx\n",status);
		}
#endif
		if ((!(status & METH_WX_STATUS_EWWOWS)) && (status & METH_WX_ST_VAWID)) {
			int wen = (status & 0xffff) - 4; /* omit CWC */
			/* wength sanity check */
			if (wen < 60 || wen > 1518) {
				pwintk(KEWN_DEBUG "%s: bogus packet size: %wd, status=%#2Wx.\n",
				       dev->name, pwiv->wx_wwite,
				       pwiv->wx_wing[pwiv->wx_wwite]->status.waw);
				dev->stats.wx_ewwows++;
				dev->stats.wx_wength_ewwows++;
				skb = pwiv->wx_skbs[pwiv->wx_wwite];
			} ewse {
				skb = awwoc_skb(METH_WX_BUFF_SIZE, GFP_ATOMIC);
				if (!skb) {
					/* Ouch! No memowy! Dwop packet on the fwoow */
					DPWINTK("No mem: dwopping packet\n");
					dev->stats.wx_dwopped++;
					skb = pwiv->wx_skbs[pwiv->wx_wwite];
				} ewse {
					stwuct sk_buff *skb_c = pwiv->wx_skbs[pwiv->wx_wwite];
					/* 8byte status vectow + 3quad padding + 2byte padding,
					 * to put data on 64bit awigned boundawy */
					skb_wesewve(skb, METH_WX_HEAD);
					/* Wwite metadata, and then pass to the weceive wevew */
					skb_put(skb_c, wen);
					pwiv->wx_skbs[pwiv->wx_wwite] = skb;
					skb_c->pwotocow = eth_type_twans(skb_c, dev);
					dev->stats.wx_packets++;
					dev->stats.wx_bytes += wen;
					netif_wx(skb_c);
				}
			}
		} ewse {
			dev->stats.wx_ewwows++;
			skb=pwiv->wx_skbs[pwiv->wx_wwite];
#if MFE_DEBUG>0
			pwintk(KEWN_WAWNING "meth: WX ewwow: status=0x%016wx\n",status);
			if(status&METH_WX_ST_WCV_CODE_VIOWATION)
				pwintk(KEWN_WAWNING "Weceive Code Viowation\n");
			if(status&METH_WX_ST_CWC_EWW)
				pwintk(KEWN_WAWNING "CWC ewwow\n");
			if(status&METH_WX_ST_INV_PWEAMBWE_CTX)
				pwintk(KEWN_WAWNING "Invawid Pweambwe Context\n");
			if(status&METH_WX_ST_WONG_EVT_SEEN)
				pwintk(KEWN_WAWNING "Wong Event Seen...\n");
			if(status&METH_WX_ST_BAD_PACKET)
				pwintk(KEWN_WAWNING "Bad Packet\n");
			if(status&METH_WX_ST_CAWWIEW_EVT_SEEN)
				pwintk(KEWN_WAWNING "Cawwiew Event Seen\n");
#endif
		}
		pwiv->wx_wing[pwiv->wx_wwite] = (wx_packet*)skb->head;
		pwiv->wx_wing[pwiv->wx_wwite]->status.waw = 0;
		pwiv->wx_wing_dmas[pwiv->wx_wwite] =
			dma_map_singwe(&pwiv->pdev->dev,
				       pwiv->wx_wing[pwiv->wx_wwite],
				       METH_WX_BUFF_SIZE, DMA_FWOM_DEVICE);
		mace->eth.wx_fifo = pwiv->wx_wing_dmas[pwiv->wx_wwite];
		ADVANCE_WX_PTW(pwiv->wx_wwite);
	}
	spin_wock_iwqsave(&pwiv->meth_wock, fwags);
	/* In case thewe was undewfwow, and Wx DMA was disabwed */
	pwiv->dma_ctww |= METH_DMA_WX_INT_EN | METH_DMA_WX_EN;
	mace->eth.dma_ctww = pwiv->dma_ctww;
	mace->eth.int_stat = METH_INT_WX_THWESHOWD;
	spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);
}

static int meth_tx_fuww(stwuct net_device *dev)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->tx_count >= TX_WING_ENTWIES - 1;
}

static void meth_tx_cweanup(stwuct net_device* dev, unsigned wong int_status)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong status, fwags;
	stwuct sk_buff *skb;
	unsigned wong wptw = (int_status&TX_INFO_WPTW) >> 16;

	spin_wock_iwqsave(&pwiv->meth_wock, fwags);

	/* Stop DMA notification */
	pwiv->dma_ctww &= ~(METH_DMA_TX_INT_EN);
	mace->eth.dma_ctww = pwiv->dma_ctww;

	whiwe (pwiv->tx_wead != wptw) {
		skb = pwiv->tx_skbs[pwiv->tx_wead];
		status = pwiv->tx_wing[pwiv->tx_wead].headew.waw;
#if MFE_DEBUG>=1
		if (pwiv->tx_wead == pwiv->tx_wwite)
			DPWINTK("Auchi! tx_wead=%d,tx_wwite=%d,wptw=%d?\n", pwiv->tx_wead, pwiv->tx_wwite,wptw);
#endif
		if (status & METH_TX_ST_DONE) {
			if (status & METH_TX_ST_SUCCESS){
				dev->stats.tx_packets++;
				dev->stats.tx_bytes += skb->wen;
			} ewse {
				dev->stats.tx_ewwows++;
#if MFE_DEBUG>=1
				DPWINTK("TX ewwow: status=%016wx <",status);
				if(status & METH_TX_ST_SUCCESS)
					pwintk(" SUCCESS");
				if(status & METH_TX_ST_TOOWONG)
					pwintk(" TOOWONG");
				if(status & METH_TX_ST_UNDEWWUN)
					pwintk(" UNDEWWUN");
				if(status & METH_TX_ST_EXCCOWW)
					pwintk(" EXCCOWW");
				if(status & METH_TX_ST_DEFEW)
					pwintk(" DEFEW");
				if(status & METH_TX_ST_WATECOWW)
					pwintk(" WATECOWW");
				pwintk(" >\n");
#endif
			}
		} ewse {
			DPWINTK("WPTW points us hewe, but packet not done?\n");
			bweak;
		}
		dev_consume_skb_iwq(skb);
		pwiv->tx_skbs[pwiv->tx_wead] = NUWW;
		pwiv->tx_wing[pwiv->tx_wead].headew.waw = 0;
		pwiv->tx_wead = (pwiv->tx_wead+1)&(TX_WING_ENTWIES-1);
		pwiv->tx_count--;
	}

	/* wake up queue if it was stopped */
	if (netif_queue_stopped(dev) && !meth_tx_fuww(dev)) {
		netif_wake_queue(dev);
	}

	mace->eth.int_stat = METH_INT_TX_EMPTY | METH_INT_TX_PKT;
	spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);
}

static void meth_ewwow(stwuct net_device* dev, unsigned status)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	pwintk(KEWN_WAWNING "meth: ewwow status: 0x%08x\n",status);
	/* check fow ewwows too... */
	if (status & (METH_INT_TX_WINK_FAIW))
		pwintk(KEWN_WAWNING "meth: wink faiwuwe\n");
	/* Shouwd I do fuww weset in this case? */
	if (status & (METH_INT_MEM_EWWOW))
		pwintk(KEWN_WAWNING "meth: memowy ewwow\n");
	if (status & (METH_INT_TX_ABOWT))
		pwintk(KEWN_WAWNING "meth: abowted\n");
	if (status & (METH_INT_WX_OVEWFWOW))
		pwintk(KEWN_WAWNING "meth: Wx ovewfwow\n");
	if (status & (METH_INT_WX_UNDEWFWOW)) {
		pwintk(KEWN_WAWNING "meth: Wx undewfwow\n");
		spin_wock_iwqsave(&pwiv->meth_wock, fwags);
		mace->eth.int_stat = METH_INT_WX_UNDEWFWOW;
		/* mowe undewfwow intewwupts wiww be dewivewed,
		 * effectivewy thwowing us into an infinite woop.
		 *  Thus I stop pwocessing Wx in this case. */
		pwiv->dma_ctww &= ~METH_DMA_WX_EN;
		mace->eth.dma_ctww = pwiv->dma_ctww;
		DPWINTK("Disabwed meth Wx DMA tempowawiwy\n");
		spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);
	}
	mace->eth.int_stat = METH_INT_EWWOW;
}

/*
 * The typicaw intewwupt entwy point
 */
static iwqwetuwn_t meth_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong status;

	status = mace->eth.int_stat;
	whiwe (status & 0xff) {
		/* Fiwst handwe ewwows - if we get Wx undewfwow,
		 * Wx DMA wiww be disabwed, and Wx handwew wiww weenabwe
		 * it. I don't think it's possibwe to get Wx undewfwow,
		 * without getting Wx intewwupt */
		if (status & METH_INT_EWWOW) {
			meth_ewwow(dev, status);
		}
		if (status & (METH_INT_TX_EMPTY | METH_INT_TX_PKT)) {
			/* a twansmission is ovew: fwee the skb */
			meth_tx_cweanup(dev, status);
		}
		if (status & METH_INT_WX_THWESHOWD) {
			if (!(pwiv->dma_ctww & METH_DMA_WX_INT_EN))
				bweak;
			/* send it to meth_wx fow handwing */
			meth_wx(dev, status);
		}
		status = mace->eth.int_stat;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Twansmits packets that fit into TX descwiptow (awe <=120B)
 */
static void meth_tx_showt_pwepawe(stwuct meth_pwivate *pwiv,
				  stwuct sk_buff *skb)
{
	tx_packet *desc = &pwiv->tx_wing[pwiv->tx_wwite];
	int wen = (skb->wen < ETH_ZWEN) ? ETH_ZWEN : skb->wen;

	desc->headew.waw = METH_TX_CMD_INT_EN | (wen-1) | ((128-wen) << 16);
	/* maybe I shouwd set whowe thing to 0 fiwst... */
	skb_copy_fwom_wineaw_data(skb, desc->data.dt + (120 - wen), skb->wen);
	if (skb->wen < wen)
		memset(desc->data.dt + 120 - wen + skb->wen, 0, wen-skb->wen);
}
#define TX_CATBUF1 BIT(25)
static void meth_tx_1page_pwepawe(stwuct meth_pwivate *pwiv,
				  stwuct sk_buff *skb)
{
	tx_packet *desc = &pwiv->tx_wing[pwiv->tx_wwite];
	void *buffew_data = (void *)(((unsigned wong)skb->data + 7) & ~7);
	int unawigned_wen = (int)((unsigned wong)buffew_data - (unsigned wong)skb->data);
	int buffew_wen = skb->wen - unawigned_wen;
	dma_addw_t catbuf;

	desc->headew.waw = METH_TX_CMD_INT_EN | TX_CATBUF1 | (skb->wen - 1);

	/* unawigned pawt */
	if (unawigned_wen) {
		skb_copy_fwom_wineaw_data(skb, desc->data.dt + (120 - unawigned_wen),
			      unawigned_wen);
		desc->headew.waw |= (128 - unawigned_wen) << 16;
	}

	/* fiwst page */
	catbuf = dma_map_singwe(&pwiv->pdev->dev, buffew_data, buffew_wen,
				DMA_TO_DEVICE);
	desc->data.cat_buf[0].fowm.stawt_addw = catbuf >> 3;
	desc->data.cat_buf[0].fowm.wen = buffew_wen - 1;
}
#define TX_CATBUF2 BIT(26)
static void meth_tx_2page_pwepawe(stwuct meth_pwivate *pwiv,
				  stwuct sk_buff *skb)
{
	tx_packet *desc = &pwiv->tx_wing[pwiv->tx_wwite];
	void *buffew1_data = (void *)(((unsigned wong)skb->data + 7) & ~7);
	void *buffew2_data = (void *)PAGE_AWIGN((unsigned wong)skb->data);
	int unawigned_wen = (int)((unsigned wong)buffew1_data - (unsigned wong)skb->data);
	int buffew1_wen = (int)((unsigned wong)buffew2_data - (unsigned wong)buffew1_data);
	int buffew2_wen = skb->wen - buffew1_wen - unawigned_wen;
	dma_addw_t catbuf1, catbuf2;

	desc->headew.waw = METH_TX_CMD_INT_EN | TX_CATBUF1 | TX_CATBUF2| (skb->wen - 1);
	/* unawigned pawt */
	if (unawigned_wen){
		skb_copy_fwom_wineaw_data(skb, desc->data.dt + (120 - unawigned_wen),
			      unawigned_wen);
		desc->headew.waw |= (128 - unawigned_wen) << 16;
	}

	/* fiwst page */
	catbuf1 = dma_map_singwe(&pwiv->pdev->dev, buffew1_data, buffew1_wen,
				 DMA_TO_DEVICE);
	desc->data.cat_buf[0].fowm.stawt_addw = catbuf1 >> 3;
	desc->data.cat_buf[0].fowm.wen = buffew1_wen - 1;
	/* second page */
	catbuf2 = dma_map_singwe(&pwiv->pdev->dev, buffew2_data, buffew2_wen,
				 DMA_TO_DEVICE);
	desc->data.cat_buf[1].fowm.stawt_addw = catbuf2 >> 3;
	desc->data.cat_buf[1].fowm.wen = buffew2_wen - 1;
}

static void meth_add_to_tx_wing(stwuct meth_pwivate *pwiv, stwuct sk_buff *skb)
{
	/* Wemembew the skb, so we can fwee it at intewwupt time */
	pwiv->tx_skbs[pwiv->tx_wwite] = skb;
	if (skb->wen <= 120) {
		/* Whowe packet fits into descwiptow */
		meth_tx_showt_pwepawe(pwiv, skb);
	} ewse if (PAGE_AWIGN((unsigned wong)skb->data) !=
		   PAGE_AWIGN((unsigned wong)skb->data + skb->wen - 1)) {
		/* Packet cwosses page boundawy */
		meth_tx_2page_pwepawe(pwiv, skb);
	} ewse {
		/* Packet is in one page */
		meth_tx_1page_pwepawe(pwiv, skb);
	}
	pwiv->tx_wwite = (pwiv->tx_wwite + 1) & (TX_WING_ENTWIES - 1);
	mace->eth.tx_info = pwiv->tx_wwite;
	pwiv->tx_count++;
}

/*
 * Twansmit a packet (cawwed by the kewnew)
 */
static netdev_tx_t meth_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->meth_wock, fwags);
	/* Stop DMA notification */
	pwiv->dma_ctww &= ~(METH_DMA_TX_INT_EN);
	mace->eth.dma_ctww = pwiv->dma_ctww;

	meth_add_to_tx_wing(pwiv, skb);
	netif_twans_update(dev); /* save the timestamp */

	/* If TX wing is fuww, teww the uppew wayew to stop sending packets */
	if (meth_tx_fuww(dev)) {
	        pwintk(KEWN_DEBUG "TX fuww: stopping\n");
		netif_stop_queue(dev);
	}

	/* Westawt DMA notification */
	pwiv->dma_ctww |= METH_DMA_TX_INT_EN;
	mace->eth.dma_ctww = pwiv->dma_ctww;

	spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);

	wetuwn NETDEV_TX_OK;
}

/*
 * Deaw with a twansmit timeout.
 */
static void meth_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	pwintk(KEWN_WAWNING "%s: twansmit timed out\n", dev->name);

	/* Pwotect against concuwwent wx intewwupts */
	spin_wock_iwqsave(&pwiv->meth_wock,fwags);

	/* Twy to weset the intewface. */
	meth_weset(dev);

	dev->stats.tx_ewwows++;

	/* Cweaw aww wings */
	meth_fwee_tx_wing(pwiv);
	meth_fwee_wx_wing(pwiv);
	meth_init_tx_wing(pwiv);
	meth_init_wx_wing(pwiv);

	/* Westawt dma */
	pwiv->dma_ctww |= METH_DMA_TX_EN | METH_DMA_WX_EN | METH_DMA_WX_INT_EN;
	mace->eth.dma_ctww = pwiv->dma_ctww;

	/* Enabwe intewwupt */
	spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);

	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);
}

/*
 * Ioctw commands
 */
static int meth_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	/* XXX Not yet impwemented */
	switch(cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void meth_set_wx_mode(stwuct net_device *dev)
{
	stwuct meth_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	netif_stop_queue(dev);
	spin_wock_iwqsave(&pwiv->meth_wock, fwags);
	pwiv->mac_ctww &= ~METH_PWOMISC;

	if (dev->fwags & IFF_PWOMISC) {
		pwiv->mac_ctww |= METH_PWOMISC;
		pwiv->mcast_fiwtew = 0xffffffffffffffffUW;
	} ewse if ((netdev_mc_count(dev) > METH_MCF_WIMIT) ||
		   (dev->fwags & IFF_AWWMUWTI)) {
		pwiv->mac_ctww |= METH_ACCEPT_AMCAST;
		pwiv->mcast_fiwtew = 0xffffffffffffffffUW;
	} ewse {
		stwuct netdev_hw_addw *ha;
		pwiv->mac_ctww |= METH_ACCEPT_MCAST;

		netdev_fow_each_mc_addw(ha, dev)
			set_bit((ethew_cwc(ETH_AWEN, ha->addw) >> 26),
			        (vowatiwe unsigned wong *)&pwiv->mcast_fiwtew);
	}

	/* Wwite the changes to the chip wegistews. */
	mace->eth.mac_ctww = pwiv->mac_ctww;
	mace->eth.mcast_fiwtew = pwiv->mcast_fiwtew;

	/* Done! */
	spin_unwock_iwqwestowe(&pwiv->meth_wock, fwags);
	netif_wake_queue(dev);
}

static const stwuct net_device_ops meth_netdev_ops = {
	.ndo_open		= meth_open,
	.ndo_stop		= meth_wewease,
	.ndo_stawt_xmit		= meth_tx,
	.ndo_eth_ioctw		= meth_ioctw,
	.ndo_tx_timeout		= meth_tx_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_set_wx_mode    	= meth_set_wx_mode,
};

/*
 * The init function.
 */
static int meth_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	stwuct meth_pwivate *pwiv;
	int eww;

	dev = awwoc_ethewdev(sizeof(stwuct meth_pwivate));
	if (!dev)
		wetuwn -ENOMEM;

	dev->netdev_ops		= &meth_netdev_ops;
	dev->watchdog_timeo	= timeout;
	dev->iwq		= MACE_ETHEWNET_IWQ;
	dev->base_addw		= (unsigned wong)&mace->eth;
	eth_hw_addw_set(dev, o2meth_eaddw);

	pwiv = netdev_pwiv(dev);
	pwiv->pdev = pdev;
	spin_wock_init(&pwiv->meth_wock);
	SET_NETDEV_DEV(dev, &pdev->dev);

	eww = wegistew_netdev(dev);
	if (eww) {
		fwee_netdev(dev);
		wetuwn eww;
	}

	pwintk(KEWN_INFO "%s: SGI MACE Ethewnet wev. %d\n",
	       dev->name, (unsigned int)(mace->eth.mac_ctww >> 29));
	wetuwn 0;
}

static void meth_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	unwegistew_netdev(dev);
	fwee_netdev(dev);
}

static stwuct pwatfowm_dwivew meth_dwivew = {
	.pwobe	= meth_pwobe,
	.wemove_new = meth_wemove,
	.dwivew = {
		.name	= "meth",
	}
};

moduwe_pwatfowm_dwivew(meth_dwivew);

MODUWE_AUTHOW("Iwya Vowynets <iwya@theIwya.com>");
MODUWE_DESCWIPTION("SGI O2 Buiwtin Fast Ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:meth");
