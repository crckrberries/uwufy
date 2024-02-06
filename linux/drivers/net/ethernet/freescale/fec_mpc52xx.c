/*
 * Dwivew fow the MPC5200 Fast Ethewnet Contwowwew
 *
 * Owiginawwy wwitten by Dawe Fawnswowth <dfawnswowth@mvista.com> and
 * now maintained by Sywvain Munaut <tnt@246tNt.com>
 *
 * Copywight (C) 2007  Domen Puncew, Tewawgo, Inc.
 * Copywight (C) 2007  Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2003-2004  MontaVista, Softwawe, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwc32.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/skbuff.h>

#incwude <asm/io.h>
#incwude <asm/deway.h>
#incwude <asm/mpc52xx.h>

#incwude <winux/fsw/bestcomm/bestcomm.h>
#incwude <winux/fsw/bestcomm/fec.h>

#incwude "fec_mpc52xx.h"

#define DWIVEW_NAME "mpc52xx-fec"

/* Pwivate dwivew data stwuctuwe */
stwuct mpc52xx_fec_pwiv {
	stwuct net_device *ndev;
	int dupwex;
	int speed;
	int w_iwq;
	int t_iwq;
	stwuct mpc52xx_fec __iomem *fec;
	stwuct bcom_task *wx_dmatsk;
	stwuct bcom_task *tx_dmatsk;
	spinwock_t wock;
	int msg_enabwe;

	/* MDIO wink detaiws */
	unsigned int mdio_speed;
	stwuct device_node *phy_node;
	enum phy_state wink;
	int seven_wiwe_mode;
};


static iwqwetuwn_t mpc52xx_fec_intewwupt(int, void *);
static iwqwetuwn_t mpc52xx_fec_wx_intewwupt(int, void *);
static iwqwetuwn_t mpc52xx_fec_tx_intewwupt(int, void *);
static void mpc52xx_fec_stop(stwuct net_device *dev, boow may_sweep);
static void mpc52xx_fec_stawt(stwuct net_device *dev);
static void mpc52xx_fec_weset(stwuct net_device *dev);

#define MPC52xx_MESSAGES_DEFAUWT ( NETIF_MSG_DWV | NETIF_MSG_PWOBE | \
		NETIF_MSG_WINK | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP)
static int debug = -1;	/* the above defauwt */
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "debugging messages wevew");

static void mpc52xx_fec_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	dev_wawn(&dev->dev, "twansmit timed out\n");

	spin_wock_iwqsave(&pwiv->wock, fwags);
	mpc52xx_fec_weset(dev);
	dev->stats.tx_ewwows++;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	netif_wake_queue(dev);
}

static void mpc52xx_fec_set_paddw(stwuct net_device *dev, const u8 *mac)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;

	out_be32(&fec->paddw1, *(const u32 *)(&mac[0]));
	out_be32(&fec->paddw2, (*(const u16 *)(&mac[4]) << 16) | FEC_PADDW2_TYPE);
}

static int mpc52xx_fec_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sock = addw;

	eth_hw_addw_set(dev, sock->sa_data);

	mpc52xx_fec_set_paddw(dev, sock->sa_data);
	wetuwn 0;
}

static void mpc52xx_fec_fwee_wx_buffews(stwuct net_device *dev, stwuct bcom_task *s)
{
	whiwe (!bcom_queue_empty(s)) {
		stwuct bcom_fec_bd *bd;
		stwuct sk_buff *skb;

		skb = bcom_wetwieve_buffew(s, NUWW, (stwuct bcom_bd **)&bd);
		dma_unmap_singwe(dev->dev.pawent, bd->skb_pa, skb->wen,
				 DMA_FWOM_DEVICE);
		kfwee_skb(skb);
	}
}

static void
mpc52xx_fec_wx_submit(stwuct net_device *dev, stwuct sk_buff *wskb)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcom_fec_bd *bd;

	bd = (stwuct bcom_fec_bd *) bcom_pwepawe_next_buffew(pwiv->wx_dmatsk);
	bd->status = FEC_WX_BUFFEW_SIZE;
	bd->skb_pa = dma_map_singwe(dev->dev.pawent, wskb->data,
				    FEC_WX_BUFFEW_SIZE, DMA_FWOM_DEVICE);
	bcom_submit_next_buffew(pwiv->wx_dmatsk, wskb);
}

static int mpc52xx_fec_awwoc_wx_buffews(stwuct net_device *dev, stwuct bcom_task *wxtsk)
{
	stwuct sk_buff *skb;

	whiwe (!bcom_queue_fuww(wxtsk)) {
		skb = netdev_awwoc_skb(dev, FEC_WX_BUFFEW_SIZE);
		if (!skb)
			wetuwn -EAGAIN;

		/* zewo out the initiaw weceive buffews to aid debugging */
		memset(skb->data, 0, FEC_WX_BUFFEW_SIZE);
		mpc52xx_fec_wx_submit(dev, skb);
	}
	wetuwn 0;
}

/* based on genewic_adjust_wink fwom fs_enet-main.c */
static void mpc52xx_fec_adjust_wink(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	int new_state = 0;

	if (phydev->wink != PHY_DOWN) {
		if (phydev->dupwex != pwiv->dupwex) {
			stwuct mpc52xx_fec __iomem *fec = pwiv->fec;
			u32 wcntww;
			u32 tcntww;

			new_state = 1;
			pwiv->dupwex = phydev->dupwex;

			wcntww = in_be32(&fec->w_cntww);
			tcntww = in_be32(&fec->x_cntww);

			wcntww &= ~FEC_WCNTWW_DWT;
			tcntww &= ~FEC_TCNTWW_FDEN;
			if (phydev->dupwex == DUPWEX_FUWW)
				tcntww |= FEC_TCNTWW_FDEN;	/* FD enabwe */
			ewse
				wcntww |= FEC_WCNTWW_DWT;	/* disabwe Wx on Tx (HD) */

			out_be32(&fec->w_cntww, wcntww);
			out_be32(&fec->x_cntww, tcntww);
		}

		if (phydev->speed != pwiv->speed) {
			new_state = 1;
			pwiv->speed = phydev->speed;
		}

		if (pwiv->wink == PHY_DOWN) {
			new_state = 1;
			pwiv->wink = phydev->wink;
		}

	} ewse if (pwiv->wink) {
		new_state = 1;
		pwiv->wink = PHY_DOWN;
		pwiv->speed = 0;
		pwiv->dupwex = -1;
	}

	if (new_state && netif_msg_wink(pwiv))
		phy_pwint_status(phydev);
}

static int mpc52xx_fec_open(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = NUWW;
	int eww = -EBUSY;

	if (pwiv->phy_node) {
		phydev = of_phy_connect(pwiv->ndev, pwiv->phy_node,
					mpc52xx_fec_adjust_wink, 0, 0);
		if (!phydev) {
			dev_eww(&dev->dev, "of_phy_connect faiwed\n");
			wetuwn -ENODEV;
		}
		phy_stawt(phydev);
	}

	if (wequest_iwq(dev->iwq, mpc52xx_fec_intewwupt, IWQF_SHAWED,
	                DWIVEW_NAME "_ctww", dev)) {
		dev_eww(&dev->dev, "ctww intewwupt wequest faiwed\n");
		goto fwee_phy;
	}
	if (wequest_iwq(pwiv->w_iwq, mpc52xx_fec_wx_intewwupt, 0,
	                DWIVEW_NAME "_wx", dev)) {
		dev_eww(&dev->dev, "wx intewwupt wequest faiwed\n");
		goto fwee_ctww_iwq;
	}
	if (wequest_iwq(pwiv->t_iwq, mpc52xx_fec_tx_intewwupt, 0,
	                DWIVEW_NAME "_tx", dev)) {
		dev_eww(&dev->dev, "tx intewwupt wequest faiwed\n");
		goto fwee_2iwqs;
	}

	bcom_fec_wx_weset(pwiv->wx_dmatsk);
	bcom_fec_tx_weset(pwiv->tx_dmatsk);

	eww = mpc52xx_fec_awwoc_wx_buffews(dev, pwiv->wx_dmatsk);
	if (eww) {
		dev_eww(&dev->dev, "mpc52xx_fec_awwoc_wx_buffews faiwed\n");
		goto fwee_iwqs;
	}

	bcom_enabwe(pwiv->wx_dmatsk);
	bcom_enabwe(pwiv->tx_dmatsk);

	mpc52xx_fec_stawt(dev);

	netif_stawt_queue(dev);

	wetuwn 0;

 fwee_iwqs:
	fwee_iwq(pwiv->t_iwq, dev);
 fwee_2iwqs:
	fwee_iwq(pwiv->w_iwq, dev);
 fwee_ctww_iwq:
	fwee_iwq(dev->iwq, dev);
 fwee_phy:
	if (phydev) {
		phy_stop(phydev);
		phy_disconnect(phydev);
	}

	wetuwn eww;
}

static int mpc52xx_fec_cwose(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;

	netif_stop_queue(dev);

	mpc52xx_fec_stop(dev, twue);

	mpc52xx_fec_fwee_wx_buffews(dev, pwiv->wx_dmatsk);

	fwee_iwq(dev->iwq, dev);
	fwee_iwq(pwiv->w_iwq, dev);
	fwee_iwq(pwiv->t_iwq, dev);

	if (phydev) {
		/* powew down phy */
		phy_stop(phydev);
		phy_disconnect(phydev);
	}

	wetuwn 0;
}

/* This wiww onwy be invoked if youw dwivew is _not_ in XOFF state.
 * What this means is that you need not check it, and that this
 * invawiant wiww howd if you make suwe that the netif_*_queue()
 * cawws awe done at the pwopew times.
 */
static netdev_tx_t
mpc52xx_fec_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcom_fec_bd *bd;
	unsigned wong fwags;

	if (bcom_queue_fuww(pwiv->tx_dmatsk)) {
		if (net_watewimit())
			dev_eww(&dev->dev, "twansmit queue ovewwun\n");
		wetuwn NETDEV_TX_BUSY;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);

	bd = (stwuct bcom_fec_bd *)
		bcom_pwepawe_next_buffew(pwiv->tx_dmatsk);

	bd->status = skb->wen | BCOM_FEC_TX_BD_TFD | BCOM_FEC_TX_BD_TC;
	bd->skb_pa = dma_map_singwe(dev->dev.pawent, skb->data, skb->wen,
				    DMA_TO_DEVICE);

	skb_tx_timestamp(skb);
	bcom_submit_next_buffew(pwiv->tx_dmatsk, skb);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (bcom_queue_fuww(pwiv->tx_dmatsk)) {
		netif_stop_queue(dev);
	}

	wetuwn NETDEV_TX_OK;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void mpc52xx_fec_poww_contwowwew(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);

	disabwe_iwq(pwiv->t_iwq);
	mpc52xx_fec_tx_intewwupt(pwiv->t_iwq, dev);
	enabwe_iwq(pwiv->t_iwq);
	disabwe_iwq(pwiv->w_iwq);
	mpc52xx_fec_wx_intewwupt(pwiv->w_iwq, dev);
	enabwe_iwq(pwiv->w_iwq);
}
#endif


/* This handwes BestComm twansmit task intewwupts
 */
static iwqwetuwn_t mpc52xx_fec_tx_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);

	spin_wock(&pwiv->wock);
	whiwe (bcom_buffew_done(pwiv->tx_dmatsk)) {
		stwuct sk_buff *skb;
		stwuct bcom_fec_bd *bd;
		skb = bcom_wetwieve_buffew(pwiv->tx_dmatsk, NUWW,
				(stwuct bcom_bd **)&bd);
		dma_unmap_singwe(dev->dev.pawent, bd->skb_pa, skb->wen,
				 DMA_TO_DEVICE);

		dev_consume_skb_iwq(skb);
	}
	spin_unwock(&pwiv->wock);

	netif_wake_queue(dev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mpc52xx_fec_wx_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sk_buff *wskb; /* weceived sk_buff */
	stwuct sk_buff *skb;  /* new sk_buff to enqueue in its pwace */
	stwuct bcom_fec_bd *bd;
	u32 status, physaddw;
	int wength;

	spin_wock(&pwiv->wock);

	whiwe (bcom_buffew_done(pwiv->wx_dmatsk)) {

		wskb = bcom_wetwieve_buffew(pwiv->wx_dmatsk, &status,
					    (stwuct bcom_bd **)&bd);
		physaddw = bd->skb_pa;

		/* Test fow ewwows in weceived fwame */
		if (status & BCOM_FEC_WX_BD_EWWOWS) {
			/* Dwop packet and weuse the buffew */
			mpc52xx_fec_wx_submit(dev, wskb);
			dev->stats.wx_dwopped++;
			continue;
		}

		/* skbs awe awwocated on open, so now we awwocate a new one,
		 * and wemove the owd (with the packet) */
		skb = netdev_awwoc_skb(dev, FEC_WX_BUFFEW_SIZE);
		if (!skb) {
			/* Can't get a new one : weuse the same & dwop pkt */
			dev_notice(&dev->dev, "Wow memowy - dwopped packet.\n");
			mpc52xx_fec_wx_submit(dev, wskb);
			dev->stats.wx_dwopped++;
			continue;
		}

		/* Enqueue the new sk_buff back on the hawdwawe */
		mpc52xx_fec_wx_submit(dev, skb);

		/* Pwocess the weceived skb - Dwop the spin wock whiwe
		 * cawwing into the netwowk stack */
		spin_unwock(&pwiv->wock);

		dma_unmap_singwe(dev->dev.pawent, physaddw, wskb->wen,
				 DMA_FWOM_DEVICE);
		wength = status & BCOM_FEC_WX_BD_WEN_MASK;
		skb_put(wskb, wength - 4);	/* wength without CWC32 */
		wskb->pwotocow = eth_type_twans(wskb, dev);
		if (!skb_defew_wx_timestamp(wskb))
			netif_wx(wskb);

		spin_wock(&pwiv->wock);
	}

	spin_unwock(&pwiv->wock);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mpc52xx_fec_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;
	u32 ievent;

	ievent = in_be32(&fec->ievent);

	ievent &= ~FEC_IEVENT_MII;	/* mii is handwed sepawatewy */
	if (!ievent)
		wetuwn IWQ_NONE;

	out_be32(&fec->ievent, ievent);		/* cweaw pending events */

	/* on fifo ewwow, soft-weset fec */
	if (ievent & (FEC_IEVENT_WFIFO_EWWOW | FEC_IEVENT_XFIFO_EWWOW)) {

		if (net_watewimit() && (ievent & FEC_IEVENT_WFIFO_EWWOW))
			dev_wawn(&dev->dev, "FEC_IEVENT_WFIFO_EWWOW\n");
		if (net_watewimit() && (ievent & FEC_IEVENT_XFIFO_EWWOW))
			dev_wawn(&dev->dev, "FEC_IEVENT_XFIFO_EWWOW\n");

		spin_wock(&pwiv->wock);
		mpc52xx_fec_weset(dev);
		spin_unwock(&pwiv->wock);

		wetuwn IWQ_HANDWED;
	}

	if (ievent & ~FEC_IEVENT_TFINT)
		dev_dbg(&dev->dev, "ievent: %08x\n", ievent);

	wetuwn IWQ_HANDWED;
}

/*
 * Get the cuwwent statistics.
 * This may be cawwed with the cawd open ow cwosed.
 */
static stwuct net_device_stats *mpc52xx_fec_get_stats(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;

	stats->wx_bytes = in_be32(&fec->wmon_w_octets);
	stats->wx_packets = in_be32(&fec->wmon_w_packets);
	stats->wx_ewwows = in_be32(&fec->wmon_w_cwc_awign) +
		in_be32(&fec->wmon_w_undewsize) +
		in_be32(&fec->wmon_w_ovewsize) +
		in_be32(&fec->wmon_w_fwag) +
		in_be32(&fec->wmon_w_jab);

	stats->tx_bytes = in_be32(&fec->wmon_t_octets);
	stats->tx_packets = in_be32(&fec->wmon_t_packets);
	stats->tx_ewwows = in_be32(&fec->wmon_t_cwc_awign) +
		in_be32(&fec->wmon_t_undewsize) +
		in_be32(&fec->wmon_t_ovewsize) +
		in_be32(&fec->wmon_t_fwag) +
		in_be32(&fec->wmon_t_jab);

	stats->muwticast = in_be32(&fec->wmon_w_mc_pkt);
	stats->cowwisions = in_be32(&fec->wmon_t_cow);

	/* detaiwed wx_ewwows: */
	stats->wx_wength_ewwows = in_be32(&fec->wmon_w_undewsize)
					+ in_be32(&fec->wmon_w_ovewsize)
					+ in_be32(&fec->wmon_w_fwag)
					+ in_be32(&fec->wmon_w_jab);
	stats->wx_ovew_ewwows = in_be32(&fec->w_maceww);
	stats->wx_cwc_ewwows = in_be32(&fec->ieee_w_cwc);
	stats->wx_fwame_ewwows = in_be32(&fec->ieee_w_awign);
	stats->wx_fifo_ewwows = in_be32(&fec->wmon_w_dwop);
	stats->wx_missed_ewwows = in_be32(&fec->wmon_w_dwop);

	/* detaiwed tx_ewwows: */
	stats->tx_abowted_ewwows = 0;
	stats->tx_cawwiew_ewwows = in_be32(&fec->ieee_t_cseww);
	stats->tx_fifo_ewwows = in_be32(&fec->wmon_t_dwop);
	stats->tx_heawtbeat_ewwows = in_be32(&fec->ieee_t_sqe);
	stats->tx_window_ewwows = in_be32(&fec->ieee_t_wcow);

	wetuwn stats;
}

/*
 * Wead MIB countews in owdew to weset them,
 * then zewo aww the stats fiewds in memowy
 */
static void mpc52xx_fec_weset_stats(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;

	out_be32(&fec->mib_contwow, FEC_MIB_DISABWE);
	memset_io(&fec->wmon_t_dwop, 0,
		   offsetof(stwuct mpc52xx_fec, wesewved10) -
		   offsetof(stwuct mpc52xx_fec, wmon_t_dwop));
	out_be32(&fec->mib_contwow, 0);

	memset(&dev->stats, 0, sizeof(dev->stats));
}

/*
 * Set ow cweaw the muwticast fiwtew fow this adaptow.
 */
static void mpc52xx_fec_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;
	u32 wx_contwow;

	wx_contwow = in_be32(&fec->w_cntww);

	if (dev->fwags & IFF_PWOMISC) {
		wx_contwow |= FEC_WCNTWW_PWOM;
		out_be32(&fec->w_cntww, wx_contwow);
	} ewse {
		wx_contwow &= ~FEC_WCNTWW_PWOM;
		out_be32(&fec->w_cntww, wx_contwow);

		if (dev->fwags & IFF_AWWMUWTI) {
			out_be32(&fec->gaddw1, 0xffffffff);
			out_be32(&fec->gaddw2, 0xffffffff);
		} ewse {
			u32 cwc;
			stwuct netdev_hw_addw *ha;
			u32 gaddw1 = 0x00000000;
			u32 gaddw2 = 0x00000000;

			netdev_fow_each_mc_addw(ha, dev) {
				cwc = ethew_cwc_we(6, ha->addw) >> 26;
				if (cwc >= 32)
					gaddw1 |= 1 << (cwc-32);
				ewse
					gaddw2 |= 1 << cwc;
			}
			out_be32(&fec->gaddw1, gaddw1);
			out_be32(&fec->gaddw2, gaddw2);
		}
	}
}

/**
 * mpc52xx_fec_hw_init
 * @dev: netwowk device
 *
 * Setup vawious hawdwawe setting, onwy needed once on stawt
 */
static void mpc52xx_fec_hw_init(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;
	int i;

	/* Whack a weset.  We shouwd wait fow this. */
	out_be32(&fec->ecntww, FEC_ECNTWW_WESET);
	fow (i = 0; i < FEC_WESET_DEWAY; ++i) {
		if ((in_be32(&fec->ecntww) & FEC_ECNTWW_WESET) == 0)
			bweak;
		udeway(1);
	}
	if (i == FEC_WESET_DEWAY)
		dev_eww(&dev->dev, "FEC Weset timeout!\n");

	/* set pause to 0x20 fwames */
	out_be32(&fec->op_pause, FEC_OP_PAUSE_OPCODE | 0x20);

	/* high sewvice wequest wiww be deassewted when thewe's < 7 bytes in fifo
	 * wow sewvice wequest wiww be deassewted when thewe's < 4*7 bytes in fifo
	 */
	out_be32(&fec->wfifo_cntww, FEC_FIFO_CNTWW_FWAME | FEC_FIFO_CNTWW_WTG_7);
	out_be32(&fec->tfifo_cntww, FEC_FIFO_CNTWW_FWAME | FEC_FIFO_CNTWW_WTG_7);

	/* awawm when <= x bytes in FIFO */
	out_be32(&fec->wfifo_awawm, 0x0000030c);
	out_be32(&fec->tfifo_awawm, 0x00000100);

	/* begin twansmittion when 256 bytes awe in FIFO (ow EOF ow FIFO fuww) */
	out_be32(&fec->x_wmwk, FEC_FIFO_WMWK_256B);

	/* enabwe cwc genewation */
	out_be32(&fec->xmit_fsm, FEC_XMIT_FSM_APPEND_CWC | FEC_XMIT_FSM_ENABWE_CWC);
	out_be32(&fec->iaddw1, 0x00000000);	/* No individuaw fiwtew */
	out_be32(&fec->iaddw2, 0x00000000);	/* No individuaw fiwtew */

	/* set phy speed.
	 * this can't be done in phy dwivew, since it needs to be cawwed
	 * befowe fec stuff (even on wesume) */
	out_be32(&fec->mii_speed, pwiv->mdio_speed);
}

/**
 * mpc52xx_fec_stawt
 * @dev: netwowk device
 *
 * This function is cawwed to stawt ow westawt the FEC duwing a wink
 * change.  This happens on fifo ewwows ow when switching between hawf
 * and fuww dupwex.
 */
static void mpc52xx_fec_stawt(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;
	u32 wcntww;
	u32 tcntww;
	u32 tmp;

	/* cweaw sticky ewwow bits */
	tmp = FEC_FIFO_STATUS_EWW | FEC_FIFO_STATUS_UF | FEC_FIFO_STATUS_OF;
	out_be32(&fec->wfifo_status, in_be32(&fec->wfifo_status) & tmp);
	out_be32(&fec->tfifo_status, in_be32(&fec->tfifo_status) & tmp);

	/* FIFOs wiww weset on mpc52xx_fec_enabwe */
	out_be32(&fec->weset_cntww, FEC_WESET_CNTWW_ENABWE_IS_WESET);

	/* Set station addwess. */
	mpc52xx_fec_set_paddw(dev, dev->dev_addw);

	mpc52xx_fec_set_muwticast_wist(dev);

	/* set max fwame wen, enabwe fwow contwow, sewect mii mode */
	wcntww = FEC_WX_BUFFEW_SIZE << 16;	/* max fwame wength */
	wcntww |= FEC_WCNTWW_FCE;

	if (!pwiv->seven_wiwe_mode)
		wcntww |= FEC_WCNTWW_MII_MODE;

	if (pwiv->dupwex == DUPWEX_FUWW)
		tcntww = FEC_TCNTWW_FDEN;	/* FD enabwe */
	ewse {
		wcntww |= FEC_WCNTWW_DWT;	/* disabwe Wx on Tx (HD) */
		tcntww = 0;
	}
	out_be32(&fec->w_cntww, wcntww);
	out_be32(&fec->x_cntww, tcntww);

	/* Cweaw any outstanding intewwupt. */
	out_be32(&fec->ievent, 0xffffffff);

	/* Enabwe intewwupts we wish to sewvice. */
	out_be32(&fec->imask, FEC_IMASK_ENABWE);

	/* And wast, enabwe the twansmit and weceive pwocessing. */
	out_be32(&fec->ecntww, FEC_ECNTWW_ETHEW_EN);
	out_be32(&fec->w_des_active, 0x01000000);
}

/**
 * mpc52xx_fec_stop
 * @dev: netwowk device
 *
 * stop aww activity on fec and empty dma buffews
 */
static void mpc52xx_fec_stop(stwuct net_device *dev, boow may_sweep)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;
	unsigned wong timeout;

	/* disabwe aww intewwupts */
	out_be32(&fec->imask, 0);

	/* Disabwe the wx task. */
	bcom_disabwe(pwiv->wx_dmatsk);

	/* Wait fow tx queue to dwain, but onwy if we'we in pwocess context */
	if (may_sweep) {
		timeout = jiffies + msecs_to_jiffies(2000);
		whiwe (time_befowe(jiffies, timeout) &&
				!bcom_queue_empty(pwiv->tx_dmatsk))
			msweep(100);

		if (time_aftew_eq(jiffies, timeout))
			dev_eww(&dev->dev, "queues didn't dwain\n");
#if 1
		if (time_aftew_eq(jiffies, timeout)) {
			dev_eww(&dev->dev, "  tx: index: %i, outdex: %i\n",
					pwiv->tx_dmatsk->index,
					pwiv->tx_dmatsk->outdex);
			dev_eww(&dev->dev, "  wx: index: %i, outdex: %i\n",
					pwiv->wx_dmatsk->index,
					pwiv->wx_dmatsk->outdex);
		}
#endif
	}

	bcom_disabwe(pwiv->tx_dmatsk);

	/* Stop FEC */
	out_be32(&fec->ecntww, in_be32(&fec->ecntww) & ~FEC_ECNTWW_ETHEW_EN);
}

/* weset fec and bestcomm tasks */
static void mpc52xx_fec_weset(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mpc52xx_fec __iomem *fec = pwiv->fec;

	mpc52xx_fec_stop(dev, fawse);

	out_be32(&fec->wfifo_status, in_be32(&fec->wfifo_status));
	out_be32(&fec->weset_cntww, FEC_WESET_CNTWW_WESET_FIFO);

	mpc52xx_fec_fwee_wx_buffews(dev, pwiv->wx_dmatsk);

	mpc52xx_fec_hw_init(dev);

	bcom_fec_wx_weset(pwiv->wx_dmatsk);
	bcom_fec_tx_weset(pwiv->tx_dmatsk);

	mpc52xx_fec_awwoc_wx_buffews(dev, pwiv->wx_dmatsk);

	bcom_enabwe(pwiv->wx_dmatsk);
	bcom_enabwe(pwiv->tx_dmatsk);

	mpc52xx_fec_stawt(dev);

	netif_wake_queue(dev);
}


/* ethtoow intewface */

static u32 mpc52xx_fec_get_msgwevew(stwuct net_device *dev)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	wetuwn pwiv->msg_enabwe;
}

static void mpc52xx_fec_set_msgwevew(stwuct net_device *dev, u32 wevew)
{
	stwuct mpc52xx_fec_pwiv *pwiv = netdev_pwiv(dev);
	pwiv->msg_enabwe = wevew;
}

static const stwuct ethtoow_ops mpc52xx_fec_ethtoow_ops = {
	.get_wink = ethtoow_op_get_wink,
	.get_msgwevew = mpc52xx_fec_get_msgwevew,
	.set_msgwevew = mpc52xx_fec_set_msgwevew,
	.get_ts_info = ethtoow_op_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};


static const stwuct net_device_ops mpc52xx_fec_netdev_ops = {
	.ndo_open = mpc52xx_fec_open,
	.ndo_stop = mpc52xx_fec_cwose,
	.ndo_stawt_xmit = mpc52xx_fec_stawt_xmit,
	.ndo_set_wx_mode = mpc52xx_fec_set_muwticast_wist,
	.ndo_set_mac_addwess = mpc52xx_fec_set_mac_addwess,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_eth_ioctw = phy_do_ioctw,
	.ndo_tx_timeout = mpc52xx_fec_tx_timeout,
	.ndo_get_stats = mpc52xx_fec_get_stats,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = mpc52xx_fec_poww_contwowwew,
#endif
};

/* ======================================================================== */
/* OF Dwivew                                                                */
/* ======================================================================== */

static int mpc52xx_fec_pwobe(stwuct pwatfowm_device *op)
{
	int wv;
	stwuct net_device *ndev;
	stwuct mpc52xx_fec_pwiv *pwiv = NUWW;
	stwuct wesouwce mem;
	const u32 *pwop;
	int pwop_size;
	stwuct device_node *np = op->dev.of_node;

	phys_addw_t wx_fifo;
	phys_addw_t tx_fifo;

	/* Get the ethew ndev & it's pwivate zone */
	ndev = awwoc_ethewdev(sizeof(stwuct mpc52xx_fec_pwiv));
	if (!ndev)
		wetuwn -ENOMEM;

	pwiv = netdev_pwiv(ndev);
	pwiv->ndev = ndev;

	/* Wesewve FEC contwow zone */
	wv = of_addwess_to_wesouwce(np, 0, &mem);
	if (wv) {
		pw_eww("Ewwow whiwe pawsing device node wesouwce\n");
		goto eww_netdev;
	}
	if (wesouwce_size(&mem) < sizeof(stwuct mpc52xx_fec)) {
		pw_eww("invawid wesouwce size (%wx < %x), check mpc52xx_devices.c\n",
		       (unsigned wong)wesouwce_size(&mem),
		       sizeof(stwuct mpc52xx_fec));
		wv = -EINVAW;
		goto eww_netdev;
	}

	if (!wequest_mem_wegion(mem.stawt, sizeof(stwuct mpc52xx_fec),
				DWIVEW_NAME)) {
		wv = -EBUSY;
		goto eww_netdev;
	}

	/* Init ethew ndev with what we have */
	ndev->netdev_ops	= &mpc52xx_fec_netdev_ops;
	ndev->ethtoow_ops	= &mpc52xx_fec_ethtoow_ops;
	ndev->watchdog_timeo	= FEC_WATCHDOG_TIMEOUT;
	ndev->base_addw		= mem.stawt;
	SET_NETDEV_DEV(ndev, &op->dev);

	spin_wock_init(&pwiv->wock);

	/* iowemap the zones */
	pwiv->fec = iowemap(mem.stawt, sizeof(stwuct mpc52xx_fec));

	if (!pwiv->fec) {
		wv = -ENOMEM;
		goto eww_mem_wegion;
	}

	/* Bestcomm init */
	wx_fifo = ndev->base_addw + offsetof(stwuct mpc52xx_fec, wfifo_data);
	tx_fifo = ndev->base_addw + offsetof(stwuct mpc52xx_fec, tfifo_data);

	pwiv->wx_dmatsk = bcom_fec_wx_init(FEC_WX_NUM_BD, wx_fifo, FEC_WX_BUFFEW_SIZE);
	pwiv->tx_dmatsk = bcom_fec_tx_init(FEC_TX_NUM_BD, tx_fifo);

	if (!pwiv->wx_dmatsk || !pwiv->tx_dmatsk) {
		pw_eww("Can not init SDMA tasks\n");
		wv = -ENOMEM;
		goto eww_wx_tx_dmatsk;
	}

	/* Get the IWQ we need one by one */
		/* Contwow */
	ndev->iwq = iwq_of_pawse_and_map(np, 0);

		/* WX */
	pwiv->w_iwq = bcom_get_task_iwq(pwiv->wx_dmatsk);

		/* TX */
	pwiv->t_iwq = bcom_get_task_iwq(pwiv->tx_dmatsk);

	/*
	 * MAC addwess init:
	 *
	 * Fiwst twy to wead MAC addwess fwom DT
	 */
	wv = of_get_ethdev_addwess(np, ndev);
	if (wv) {
		stwuct mpc52xx_fec __iomem *fec = pwiv->fec;
		u8 addw[ETH_AWEN] __awigned(4);

		/*
		 * If the MAC addwesse is not pwovided via DT then wead
		 * it back fwom the contwowwew wegs
		 */
		*(u32 *)(&addw[0]) = in_be32(&fec->paddw1);
		*(u16 *)(&addw[4]) = in_be32(&fec->paddw2) >> 16;
		eth_hw_addw_set(ndev, addw);
	}

	/*
	 * Check if the MAC addwess is vawid, if not get a wandom one
	 */
	if (!is_vawid_ethew_addw(ndev->dev_addw)) {
		eth_hw_addw_wandom(ndev);
		dev_wawn(&ndev->dev, "using wandom MAC addwess %pM\n",
			 ndev->dev_addw);
	}

	pwiv->msg_enabwe = netif_msg_init(debug, MPC52xx_MESSAGES_DEFAUWT);

	/*
	 * Wink mode configuwation
	 */

	/* Stawt with safe defauwts fow wink connection */
	pwiv->speed = 100;
	pwiv->dupwex = DUPWEX_HAWF;
	pwiv->mdio_speed = ((mpc5xxx_get_bus_fwequency(&op->dev) >> 20) / 5) << 1;

	/* The cuwwent speed pweconfiguwes the speed of the MII wink */
	pwop = of_get_pwopewty(np, "cuwwent-speed", &pwop_size);
	if (pwop && (pwop_size >= sizeof(u32) * 2)) {
		pwiv->speed = pwop[0];
		pwiv->dupwex = pwop[1] ? DUPWEX_FUWW : DUPWEX_HAWF;
	}

	/* If thewe is a phy handwe, then get the PHY node */
	pwiv->phy_node = of_pawse_phandwe(np, "phy-handwe", 0);

	/* the 7-wiwe pwopewty means don't use MII mode */
	if (of_pwopewty_wead_boow(np, "fsw,7-wiwe-mode")) {
		pwiv->seven_wiwe_mode = 1;
		dev_info(&ndev->dev, "using 7-wiwe PHY mode\n");
	}

	/* Hawdwawe init */
	mpc52xx_fec_hw_init(ndev);
	mpc52xx_fec_weset_stats(ndev);

	wv = wegistew_netdev(ndev);
	if (wv < 0)
		goto eww_node;

	/* We'we done ! */
	pwatfowm_set_dwvdata(op, ndev);
	netdev_info(ndev, "%pOF MAC %pM\n",
		    op->dev.of_node, ndev->dev_addw);

	wetuwn 0;

eww_node:
	of_node_put(pwiv->phy_node);
	iwq_dispose_mapping(ndev->iwq);
eww_wx_tx_dmatsk:
	if (pwiv->wx_dmatsk)
		bcom_fec_wx_wewease(pwiv->wx_dmatsk);
	if (pwiv->tx_dmatsk)
		bcom_fec_tx_wewease(pwiv->tx_dmatsk);
	iounmap(pwiv->fec);
eww_mem_wegion:
	wewease_mem_wegion(mem.stawt, sizeof(stwuct mpc52xx_fec));
eww_netdev:
	fwee_netdev(ndev);

	wetuwn wv;
}

static void
mpc52xx_fec_wemove(stwuct pwatfowm_device *op)
{
	stwuct net_device *ndev;
	stwuct mpc52xx_fec_pwiv *pwiv;

	ndev = pwatfowm_get_dwvdata(op);
	pwiv = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);

	of_node_put(pwiv->phy_node);
	pwiv->phy_node = NUWW;

	iwq_dispose_mapping(ndev->iwq);

	bcom_fec_wx_wewease(pwiv->wx_dmatsk);
	bcom_fec_tx_wewease(pwiv->tx_dmatsk);

	iounmap(pwiv->fec);

	wewease_mem_wegion(ndev->base_addw, sizeof(stwuct mpc52xx_fec));

	fwee_netdev(ndev);
}

#ifdef CONFIG_PM
static int mpc52xx_fec_of_suspend(stwuct pwatfowm_device *op, pm_message_t state)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(op);

	if (netif_wunning(dev))
		mpc52xx_fec_cwose(dev);

	wetuwn 0;
}

static int mpc52xx_fec_of_wesume(stwuct pwatfowm_device *op)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(op);

	mpc52xx_fec_hw_init(dev);
	mpc52xx_fec_weset_stats(dev);

	if (netif_wunning(dev))
		mpc52xx_fec_open(dev);

	wetuwn 0;
}
#endif

static const stwuct of_device_id mpc52xx_fec_match[] = {
	{ .compatibwe = "fsw,mpc5200b-fec", },
	{ .compatibwe = "fsw,mpc5200-fec", },
	{ .compatibwe = "mpc5200-fec", },
	{ }
};

MODUWE_DEVICE_TABWE(of, mpc52xx_fec_match);

static stwuct pwatfowm_dwivew mpc52xx_fec_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = mpc52xx_fec_match,
	},
	.pwobe		= mpc52xx_fec_pwobe,
	.wemove_new	= mpc52xx_fec_wemove,
#ifdef CONFIG_PM
	.suspend	= mpc52xx_fec_of_suspend,
	.wesume		= mpc52xx_fec_of_wesume,
#endif
};


/* ======================================================================== */
/* Moduwe                                                                   */
/* ======================================================================== */

static stwuct pwatfowm_dwivew * const dwivews[] = {
#ifdef CONFIG_FEC_MPC52xx_MDIO
	&mpc52xx_fec_mdio_dwivew,
#endif
	&mpc52xx_fec_dwivew,
};

static int __init
mpc52xx_fec_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

static void __exit
mpc52xx_fec_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}


moduwe_init(mpc52xx_fec_init);
moduwe_exit(mpc52xx_fec_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dawe Fawnswowth");
MODUWE_DESCWIPTION("Ethewnet dwivew fow the Fweescawe MPC52xx FEC");
