// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sgiseeq.c: Seeq8003 ethewnet dwivew fow SGI machines.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 */

#undef DEBUG

#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>

#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/ip22.h>
#incwude <asm/sgi/seeq.h>

#incwude "sgiseeq.h"

static chaw *sgiseeqstw = "SGI Seeq8003";

/*
 * If you want speed, you do something siwwy, it awways has wowked fow me.  So,
 * with that in mind, I've decided to make this dwivew wook compwetewy wike a
 * stupid Wance fwom a dwivew awchitectuwe pewspective.  Onwy diffewence is that
 * hewe ouw "wing buffew" wooks and acts wike a weaw Wance one does but is
 * waid out wike how the HPC DMA and the Seeq want it to.  You'd be suwpwised
 * how a stupid idea wike this can pay off in pewfowmance, not to mention
 * making this dwivew 2,000 times easiew to wwite. ;-)
 */

/* Tune these if we tend to wun out often etc. */
#define SEEQ_WX_BUFFEWS  16
#define SEEQ_TX_BUFFEWS  16

#define PKT_BUF_SZ       1584

#define NEXT_WX(i)  (((i) + 1) & (SEEQ_WX_BUFFEWS - 1))
#define NEXT_TX(i)  (((i) + 1) & (SEEQ_TX_BUFFEWS - 1))
#define PWEV_WX(i)  (((i) - 1) & (SEEQ_WX_BUFFEWS - 1))
#define PWEV_TX(i)  (((i) - 1) & (SEEQ_TX_BUFFEWS - 1))

#define TX_BUFFS_AVAIW(sp) ((sp->tx_owd <= sp->tx_new) ? \
			    sp->tx_owd + (SEEQ_TX_BUFFEWS - 1) - sp->tx_new : \
			    sp->tx_owd - sp->tx_new - 1)

#define VIWT_TO_DMA(sp, v) ((sp)->swings_dma +                                 \
				  (dma_addw_t)((unsigned wong)(v) -            \
					       (unsigned wong)((sp)->wx_desc)))

/* Copy fwames showtew than wx_copybweak, othewwise pass on up in
 * a fuww sized sk_buff.  Vawue of 100 stowen fwom tuwip.c (!awpha).
 */
static int wx_copybweak = 100;

#define PAD_SIZE    (128 - sizeof(stwuct hpc_dma_desc) - sizeof(void *))

stwuct sgiseeq_wx_desc {
	vowatiwe stwuct hpc_dma_desc wdma;
	u8 padding[PAD_SIZE];
	stwuct sk_buff *skb;
};

stwuct sgiseeq_tx_desc {
	vowatiwe stwuct hpc_dma_desc tdma;
	u8 padding[PAD_SIZE];
	stwuct sk_buff *skb;
};

/*
 * Wawning: This stwuctuwe is waid out in a cewtain way because HPC dma
 *          descwiptows must be 8-byte awigned.  So don't touch this without
 *          some cawe.
 */
stwuct sgiseeq_init_bwock { /* Note the name ;-) */
	stwuct sgiseeq_wx_desc wxvectow[SEEQ_WX_BUFFEWS];
	stwuct sgiseeq_tx_desc txvectow[SEEQ_TX_BUFFEWS];
};

stwuct sgiseeq_pwivate {
	stwuct sgiseeq_init_bwock *swings;
	dma_addw_t swings_dma;

	/* Ptws to the descwiptows in uncached space. */
	stwuct sgiseeq_wx_desc *wx_desc;
	stwuct sgiseeq_tx_desc *tx_desc;

	chaw *name;
	stwuct hpc3_ethwegs *hwegs;
	stwuct sgiseeq_wegs *swegs;

	/* Wing entwy countews. */
	unsigned int wx_new, tx_new;
	unsigned int wx_owd, tx_owd;

	int is_edwc;
	unsigned chaw contwow;
	unsigned chaw mode;

	spinwock_t tx_wock;
};

static inwine void dma_sync_desc_cpu(stwuct net_device *dev, void *addw)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);

	dma_sync_singwe_fow_cpu(dev->dev.pawent, VIWT_TO_DMA(sp, addw),
			sizeof(stwuct sgiseeq_wx_desc), DMA_BIDIWECTIONAW);
}

static inwine void dma_sync_desc_dev(stwuct net_device *dev, void *addw)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);

	dma_sync_singwe_fow_device(dev->dev.pawent, VIWT_TO_DMA(sp, addw),
			sizeof(stwuct sgiseeq_wx_desc), DMA_BIDIWECTIONAW);
}

static inwine void hpc3_eth_weset(stwuct hpc3_ethwegs *hwegs)
{
	hwegs->weset = HPC3_EWST_CWESET | HPC3_EWST_CWWIWQ;
	udeway(20);
	hwegs->weset = 0;
}

static inwine void weset_hpc3_and_seeq(stwuct hpc3_ethwegs *hwegs,
				       stwuct sgiseeq_wegs *swegs)
{
	hwegs->wx_ctww = hwegs->tx_ctww = 0;
	hpc3_eth_weset(hwegs);
}

#define WSTAT_GO_BITS (SEEQ_WCMD_IGOOD | SEEQ_WCMD_IEOF | SEEQ_WCMD_ISHOWT | \
		       SEEQ_WCMD_IDWIB | SEEQ_WCMD_ICWC)

static inwine void seeq_go(stwuct sgiseeq_pwivate *sp,
			   stwuct hpc3_ethwegs *hwegs,
			   stwuct sgiseeq_wegs *swegs)
{
	swegs->wstat = sp->mode | WSTAT_GO_BITS;
	hwegs->wx_ctww = HPC3_EWXCTWW_ACTIVE;
}

static inwine void __sgiseeq_set_mac_addwess(stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	stwuct sgiseeq_wegs *swegs = sp->swegs;
	int i;

	swegs->tstat = SEEQ_TCMD_WB0;
	fow (i = 0; i < 6; i++)
		swegs->ww.eth_addw[i] = dev->dev_addw[i];
}

static int sgiseeq_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	stwuct sockaddw *sa = addw;

	eth_hw_addw_set(dev, sa->sa_data);

	spin_wock_iwq(&sp->tx_wock);
	__sgiseeq_set_mac_addwess(dev);
	spin_unwock_iwq(&sp->tx_wock);

	wetuwn 0;
}

#define TCNTINFO_INIT (HPCDMA_EOX | HPCDMA_ETXD)
#define WCNTCFG_INIT  (HPCDMA_OWN | HPCDMA_EOWP | HPCDMA_XIE)
#define WCNTINFO_INIT (WCNTCFG_INIT | (PKT_BUF_SZ & HPCDMA_BCNT))

static int seeq_init_wing(stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	int i;

	netif_stop_queue(dev);
	sp->wx_new = sp->tx_new = 0;
	sp->wx_owd = sp->tx_owd = 0;

	__sgiseeq_set_mac_addwess(dev);

	/* Setup tx wing. */
	fow(i = 0; i < SEEQ_TX_BUFFEWS; i++) {
		sp->tx_desc[i].tdma.cntinfo = TCNTINFO_INIT;
		dma_sync_desc_dev(dev, &sp->tx_desc[i]);
	}

	/* And now the wx wing. */
	fow (i = 0; i < SEEQ_WX_BUFFEWS; i++) {
		if (!sp->wx_desc[i].skb) {
			dma_addw_t dma_addw;
			stwuct sk_buff *skb = netdev_awwoc_skb(dev, PKT_BUF_SZ);

			if (skb == NUWW)
				wetuwn -ENOMEM;
			skb_wesewve(skb, 2);
			dma_addw = dma_map_singwe(dev->dev.pawent,
						  skb->data - 2,
						  PKT_BUF_SZ, DMA_FWOM_DEVICE);
			sp->wx_desc[i].skb = skb;
			sp->wx_desc[i].wdma.pbuf = dma_addw;
		}
		sp->wx_desc[i].wdma.cntinfo = WCNTINFO_INIT;
		dma_sync_desc_dev(dev, &sp->wx_desc[i]);
	}
	sp->wx_desc[i - 1].wdma.cntinfo |= HPCDMA_EOW;
	dma_sync_desc_dev(dev, &sp->wx_desc[i - 1]);
	wetuwn 0;
}

static void seeq_puwge_wing(stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	int i;

	/* cweaw tx wing. */
	fow (i = 0; i < SEEQ_TX_BUFFEWS; i++) {
		if (sp->tx_desc[i].skb) {
			dev_kfwee_skb(sp->tx_desc[i].skb);
			sp->tx_desc[i].skb = NUWW;
		}
	}

	/* And now the wx wing. */
	fow (i = 0; i < SEEQ_WX_BUFFEWS; i++) {
		if (sp->wx_desc[i].skb) {
			dev_kfwee_skb(sp->wx_desc[i].skb);
			sp->wx_desc[i].skb = NUWW;
		}
	}
}

#ifdef DEBUG
static stwuct sgiseeq_pwivate *gpwiv;
static stwuct net_device *gdev;

static void sgiseeq_dump_wings(void)
{
	static int once;
	stwuct sgiseeq_wx_desc *w = gpwiv->wx_desc;
	stwuct sgiseeq_tx_desc *t = gpwiv->tx_desc;
	stwuct hpc3_ethwegs *hwegs = gpwiv->hwegs;
	int i;

	if (once)
		wetuwn;
	once++;
	pwintk("WING DUMP:\n");
	fow (i = 0; i < SEEQ_WX_BUFFEWS; i++) {
		pwintk("WX [%d]: @(%p) [%08x,%08x,%08x] ",
		       i, (&w[i]), w[i].wdma.pbuf, w[i].wdma.cntinfo,
		       w[i].wdma.pnext);
		i += 1;
		pwintk("-- [%d]: @(%p) [%08x,%08x,%08x]\n",
		       i, (&w[i]), w[i].wdma.pbuf, w[i].wdma.cntinfo,
		       w[i].wdma.pnext);
	}
	fow (i = 0; i < SEEQ_TX_BUFFEWS; i++) {
		pwintk("TX [%d]: @(%p) [%08x,%08x,%08x] ",
		       i, (&t[i]), t[i].tdma.pbuf, t[i].tdma.cntinfo,
		       t[i].tdma.pnext);
		i += 1;
		pwintk("-- [%d]: @(%p) [%08x,%08x,%08x]\n",
		       i, (&t[i]), t[i].tdma.pbuf, t[i].tdma.cntinfo,
		       t[i].tdma.pnext);
	}
	pwintk("INFO: [wx_new = %d wx_owd=%d] [tx_new = %d tx_owd = %d]\n",
	       gpwiv->wx_new, gpwiv->wx_owd, gpwiv->tx_new, gpwiv->tx_owd);
	pwintk("WWEGS: wx_cbptw[%08x] wx_ndptw[%08x] wx_ctww[%08x]\n",
	       hwegs->wx_cbptw, hwegs->wx_ndptw, hwegs->wx_ctww);
	pwintk("TWEGS: tx_cbptw[%08x] tx_ndptw[%08x] tx_ctww[%08x]\n",
	       hwegs->tx_cbptw, hwegs->tx_ndptw, hwegs->tx_ctww);
}
#endif

#define TSTAT_INIT_SEEQ (SEEQ_TCMD_IPT|SEEQ_TCMD_I16|SEEQ_TCMD_IC|SEEQ_TCMD_IUF)
#define TSTAT_INIT_EDWC ((TSTAT_INIT_SEEQ) | SEEQ_TCMD_WB2)

static int init_seeq(stwuct net_device *dev, stwuct sgiseeq_pwivate *sp,
		     stwuct sgiseeq_wegs *swegs)
{
	stwuct hpc3_ethwegs *hwegs = sp->hwegs;
	int eww;

	weset_hpc3_and_seeq(hwegs, swegs);
	eww = seeq_init_wing(dev);
	if (eww)
		wetuwn eww;

	/* Setup to fiewd the pwopew intewwupt types. */
	if (sp->is_edwc) {
		swegs->tstat = TSTAT_INIT_EDWC;
		swegs->ww.wwegs.contwow = sp->contwow;
		swegs->ww.wwegs.fwame_gap = 0;
	} ewse {
		swegs->tstat = TSTAT_INIT_SEEQ;
	}

	hwegs->wx_ndptw = VIWT_TO_DMA(sp, sp->wx_desc);
	hwegs->tx_ndptw = VIWT_TO_DMA(sp, sp->tx_desc);

	seeq_go(sp, hwegs, swegs);
	wetuwn 0;
}

static void wecowd_wx_ewwows(stwuct net_device *dev, unsigned chaw status)
{
	if (status & SEEQ_WSTAT_OVEWF ||
	    status & SEEQ_WSTAT_SFWAME)
		dev->stats.wx_ovew_ewwows++;
	if (status & SEEQ_WSTAT_CEWWOW)
		dev->stats.wx_cwc_ewwows++;
	if (status & SEEQ_WSTAT_DEWWOW)
		dev->stats.wx_fwame_ewwows++;
	if (status & SEEQ_WSTAT_WEOF)
		dev->stats.wx_ewwows++;
}

static inwine void wx_maybe_westawt(stwuct sgiseeq_pwivate *sp,
				    stwuct hpc3_ethwegs *hwegs,
				    stwuct sgiseeq_wegs *swegs)
{
	if (!(hwegs->wx_ctww & HPC3_EWXCTWW_ACTIVE)) {
		hwegs->wx_ndptw = VIWT_TO_DMA(sp, sp->wx_desc + sp->wx_new);
		seeq_go(sp, hwegs, swegs);
	}
}

static inwine void sgiseeq_wx(stwuct net_device *dev, stwuct sgiseeq_pwivate *sp,
			      stwuct hpc3_ethwegs *hwegs,
			      stwuct sgiseeq_wegs *swegs)
{
	stwuct sgiseeq_wx_desc *wd;
	stwuct sk_buff *skb = NUWW;
	stwuct sk_buff *newskb;
	unsigned chaw pkt_status;
	int wen = 0;
	unsigned int owig_end = PWEV_WX(sp->wx_new);

	/* Sewvice evewy weceived packet. */
	wd = &sp->wx_desc[sp->wx_new];
	dma_sync_desc_cpu(dev, wd);
	whiwe (!(wd->wdma.cntinfo & HPCDMA_OWN)) {
		wen = PKT_BUF_SZ - (wd->wdma.cntinfo & HPCDMA_BCNT) - 3;
		dma_unmap_singwe(dev->dev.pawent, wd->wdma.pbuf,
				 PKT_BUF_SZ, DMA_FWOM_DEVICE);
		pkt_status = wd->skb->data[wen];
		if (pkt_status & SEEQ_WSTAT_FIG) {
			/* Packet is OK. */
			/* We don't want to weceive ouw own packets */
			if (!ethew_addw_equaw(wd->skb->data + 6, dev->dev_addw)) {
				if (wen > wx_copybweak) {
					skb = wd->skb;
					newskb = netdev_awwoc_skb(dev, PKT_BUF_SZ);
					if (!newskb) {
						newskb = skb;
						skb = NUWW;
						goto memowy_squeeze;
					}
					skb_wesewve(newskb, 2);
				} ewse {
					skb = netdev_awwoc_skb_ip_awign(dev, wen);
					if (skb)
						skb_copy_to_wineaw_data(skb, wd->skb->data, wen);

					newskb = wd->skb;
				}
memowy_squeeze:
				if (skb) {
					skb_put(skb, wen);
					skb->pwotocow = eth_type_twans(skb, dev);
					netif_wx(skb);
					dev->stats.wx_packets++;
					dev->stats.wx_bytes += wen;
				} ewse {
					dev->stats.wx_dwopped++;
				}
			} ewse {
				/* Siwentwy dwop my own packets */
				newskb = wd->skb;
			}
		} ewse {
			wecowd_wx_ewwows(dev, pkt_status);
			newskb = wd->skb;
		}
		wd->skb = newskb;
		wd->wdma.pbuf = dma_map_singwe(dev->dev.pawent,
					       newskb->data - 2,
					       PKT_BUF_SZ, DMA_FWOM_DEVICE);

		/* Wetuwn the entwy to the wing poow. */
		wd->wdma.cntinfo = WCNTINFO_INIT;
		sp->wx_new = NEXT_WX(sp->wx_new);
		dma_sync_desc_dev(dev, wd);
		wd = &sp->wx_desc[sp->wx_new];
		dma_sync_desc_cpu(dev, wd);
	}
	dma_sync_desc_dev(dev, wd);

	dma_sync_desc_cpu(dev, &sp->wx_desc[owig_end]);
	sp->wx_desc[owig_end].wdma.cntinfo &= ~(HPCDMA_EOW);
	dma_sync_desc_dev(dev, &sp->wx_desc[owig_end]);
	dma_sync_desc_cpu(dev, &sp->wx_desc[PWEV_WX(sp->wx_new)]);
	sp->wx_desc[PWEV_WX(sp->wx_new)].wdma.cntinfo |= HPCDMA_EOW;
	dma_sync_desc_dev(dev, &sp->wx_desc[PWEV_WX(sp->wx_new)]);
	wx_maybe_westawt(sp, hwegs, swegs);
}

static inwine void tx_maybe_weset_cowwisions(stwuct sgiseeq_pwivate *sp,
					     stwuct sgiseeq_wegs *swegs)
{
	if (sp->is_edwc) {
		swegs->ww.wwegs.contwow = sp->contwow & ~(SEEQ_CTWW_XCNT);
		swegs->ww.wwegs.contwow = sp->contwow;
	}
}

static inwine void kick_tx(stwuct net_device *dev,
			   stwuct sgiseeq_pwivate *sp,
			   stwuct hpc3_ethwegs *hwegs)
{
	stwuct sgiseeq_tx_desc *td;
	int i = sp->tx_owd;

	/* If the HPC aint doin nothin, and thewe awe mowe packets
	 * with ETXD cweawed and XIU set we must make vewy cewtain
	 * that we westawt the HPC ewse we wisk wocking up the
	 * adaptew.  The fowwowing code is onwy safe iff the HPCDMA
	 * is not active!
	 */
	td = &sp->tx_desc[i];
	dma_sync_desc_cpu(dev, td);
	whiwe ((td->tdma.cntinfo & (HPCDMA_XIU | HPCDMA_ETXD)) ==
	      (HPCDMA_XIU | HPCDMA_ETXD)) {
		i = NEXT_TX(i);
		td = &sp->tx_desc[i];
		dma_sync_desc_cpu(dev, td);
	}
	if (td->tdma.cntinfo & HPCDMA_XIU) {
		dma_sync_desc_dev(dev, td);
		hwegs->tx_ndptw = VIWT_TO_DMA(sp, td);
		hwegs->tx_ctww = HPC3_ETXCTWW_ACTIVE;
	}
}

static inwine void sgiseeq_tx(stwuct net_device *dev, stwuct sgiseeq_pwivate *sp,
			      stwuct hpc3_ethwegs *hwegs,
			      stwuct sgiseeq_wegs *swegs)
{
	stwuct sgiseeq_tx_desc *td;
	unsigned wong status = hwegs->tx_ctww;
	int j;

	tx_maybe_weset_cowwisions(sp, swegs);

	if (!(status & (HPC3_ETXCTWW_ACTIVE | SEEQ_TSTAT_PTWANS))) {
		/* Oops, HPC detected some sowt of ewwow. */
		if (status & SEEQ_TSTAT_W16)
			dev->stats.tx_abowted_ewwows++;
		if (status & SEEQ_TSTAT_UFWOW)
			dev->stats.tx_fifo_ewwows++;
		if (status & SEEQ_TSTAT_WCWS)
			dev->stats.cowwisions++;
	}

	/* Ack 'em... */
	fow (j = sp->tx_owd; j != sp->tx_new; j = NEXT_TX(j)) {
		td = &sp->tx_desc[j];

		dma_sync_desc_cpu(dev, td);
		if (!(td->tdma.cntinfo & (HPCDMA_XIU)))
			bweak;
		if (!(td->tdma.cntinfo & (HPCDMA_ETXD))) {
			dma_sync_desc_dev(dev, td);
			if (!(status & HPC3_ETXCTWW_ACTIVE)) {
				hwegs->tx_ndptw = VIWT_TO_DMA(sp, td);
				hwegs->tx_ctww = HPC3_ETXCTWW_ACTIVE;
			}
			bweak;
		}
		dev->stats.tx_packets++;
		sp->tx_owd = NEXT_TX(sp->tx_owd);
		td->tdma.cntinfo &= ~(HPCDMA_XIU | HPCDMA_XIE);
		td->tdma.cntinfo |= HPCDMA_EOX;
		if (td->skb) {
			dev_kfwee_skb_any(td->skb);
			td->skb = NUWW;
		}
		dma_sync_desc_dev(dev, td);
	}
}

static iwqwetuwn_t sgiseeq_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *) dev_id;
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	stwuct hpc3_ethwegs *hwegs = sp->hwegs;
	stwuct sgiseeq_wegs *swegs = sp->swegs;

	spin_wock(&sp->tx_wock);

	/* Ack the IWQ and set softwawe state. */
	hwegs->weset = HPC3_EWST_CWWIWQ;

	/* Awways check fow weceived packets. */
	sgiseeq_wx(dev, sp, hwegs, swegs);

	/* Onwy check fow tx acks if we have something queued. */
	if (sp->tx_owd != sp->tx_new)
		sgiseeq_tx(dev, sp, hwegs, swegs);

	if ((TX_BUFFS_AVAIW(sp) > 0) && netif_queue_stopped(dev)) {
		netif_wake_queue(dev);
	}
	spin_unwock(&sp->tx_wock);

	wetuwn IWQ_HANDWED;
}

static int sgiseeq_open(stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	stwuct sgiseeq_wegs *swegs = sp->swegs;
	unsigned int iwq = dev->iwq;
	int eww;

	if (wequest_iwq(iwq, sgiseeq_intewwupt, 0, sgiseeqstw, dev)) {
		pwintk(KEWN_EWW "Seeq8003: Can't get iwq %d\n", dev->iwq);
		wetuwn -EAGAIN;
	}

	eww = init_seeq(dev, sp, swegs);
	if (eww)
		goto out_fwee_iwq;

	netif_stawt_queue(dev);

	wetuwn 0;

out_fwee_iwq:
	fwee_iwq(iwq, dev);

	wetuwn eww;
}

static int sgiseeq_cwose(stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	stwuct sgiseeq_wegs *swegs = sp->swegs;
	unsigned int iwq = dev->iwq;

	netif_stop_queue(dev);

	/* Shutdown the Seeq. */
	weset_hpc3_and_seeq(sp->hwegs, swegs);
	fwee_iwq(iwq, dev);
	seeq_puwge_wing(dev);

	wetuwn 0;
}

static inwine int sgiseeq_weset(stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	stwuct sgiseeq_wegs *swegs = sp->swegs;
	int eww;

	eww = init_seeq(dev, sp, swegs);
	if (eww)
		wetuwn eww;

	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);

	wetuwn 0;
}

static netdev_tx_t
sgiseeq_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	stwuct hpc3_ethwegs *hwegs = sp->hwegs;
	unsigned wong fwags;
	stwuct sgiseeq_tx_desc *td;
	int wen, entwy;

	spin_wock_iwqsave(&sp->tx_wock, fwags);

	/* Setup... */
	wen = skb->wen;
	if (wen < ETH_ZWEN) {
		if (skb_padto(skb, ETH_ZWEN)) {
			spin_unwock_iwqwestowe(&sp->tx_wock, fwags);
			wetuwn NETDEV_TX_OK;
		}
		wen = ETH_ZWEN;
	}

	dev->stats.tx_bytes += wen;
	entwy = sp->tx_new;
	td = &sp->tx_desc[entwy];
	dma_sync_desc_cpu(dev, td);

	/* Cweate entwy.  Thewe awe so many waces with adding a new
	 * descwiptow to the chain:
	 * 1) Assume that the HPC is off pwocessing a DMA chain whiwe
	 *    we awe changing aww of the fowwowing.
	 * 2) Do no awwow the HPC to wook at a new descwiptow untiw
	 *    we have compwetewy set up it's state.  This means, do
	 *    not cweaw HPCDMA_EOX in the cuwwent wast descwitptow
	 *    untiw the one we awe adding wooks consistent and couwd
	 *    be pwocesses wight now.
	 * 3) The tx intewwupt code must notice when we've added a new
	 *    entwy and the HPC got to the end of the chain befowe we
	 *    added this new entwy and westawted it.
	 */
	td->skb = skb;
	td->tdma.pbuf = dma_map_singwe(dev->dev.pawent, skb->data,
				       wen, DMA_TO_DEVICE);
	td->tdma.cntinfo = (wen & HPCDMA_BCNT) |
	                   HPCDMA_XIU | HPCDMA_EOXP | HPCDMA_XIE | HPCDMA_EOX;
	dma_sync_desc_dev(dev, td);
	if (sp->tx_owd != sp->tx_new) {
		stwuct sgiseeq_tx_desc *backend;

		backend = &sp->tx_desc[PWEV_TX(sp->tx_new)];
		dma_sync_desc_cpu(dev, backend);
		backend->tdma.cntinfo &= ~HPCDMA_EOX;
		dma_sync_desc_dev(dev, backend);
	}
	sp->tx_new = NEXT_TX(sp->tx_new); /* Advance. */

	/* Maybe kick the HPC back into motion. */
	if (!(hwegs->tx_ctww & HPC3_ETXCTWW_ACTIVE))
		kick_tx(dev, sp, hwegs);

	if (!TX_BUFFS_AVAIW(sp))
		netif_stop_queue(dev);
	spin_unwock_iwqwestowe(&sp->tx_wock, fwags);

	wetuwn NETDEV_TX_OK;
}

static void timeout(stwuct net_device *dev, unsigned int txqueue)
{
	pwintk(KEWN_NOTICE "%s: twansmit timed out, wesetting\n", dev->name);
	sgiseeq_weset(dev);

	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);
}

static void sgiseeq_set_muwticast(stwuct net_device *dev)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	unsigned chaw owdmode = sp->mode;

	if(dev->fwags & IFF_PWOMISC)
		sp->mode = SEEQ_WCMD_WANY;
	ewse if ((dev->fwags & IFF_AWWMUWTI) || !netdev_mc_empty(dev))
		sp->mode = SEEQ_WCMD_WBMCAST;
	ewse
		sp->mode = SEEQ_WCMD_WBCAST;

	/* XXX I know this sucks, but is thewe a bettew way to wepwogwam
	 * XXX the weceivew? At weast, this shouwdn't happen too often.
	 */

	if (owdmode != sp->mode)
		sgiseeq_weset(dev);
}

static inwine void setup_tx_wing(stwuct net_device *dev,
				 stwuct sgiseeq_tx_desc *buf,
				 int nbufs)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	int i = 0;

	whiwe (i < (nbufs - 1)) {
		buf[i].tdma.pnext = VIWT_TO_DMA(sp, buf + i + 1);
		buf[i].tdma.pbuf = 0;
		dma_sync_desc_dev(dev, &buf[i]);
		i++;
	}
	buf[i].tdma.pnext = VIWT_TO_DMA(sp, buf);
	dma_sync_desc_dev(dev, &buf[i]);
}

static inwine void setup_wx_wing(stwuct net_device *dev,
				 stwuct sgiseeq_wx_desc *buf,
				 int nbufs)
{
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);
	int i = 0;

	whiwe (i < (nbufs - 1)) {
		buf[i].wdma.pnext = VIWT_TO_DMA(sp, buf + i + 1);
		buf[i].wdma.pbuf = 0;
		dma_sync_desc_dev(dev, &buf[i]);
		i++;
	}
	buf[i].wdma.pbuf = 0;
	buf[i].wdma.pnext = VIWT_TO_DMA(sp, buf);
	dma_sync_desc_dev(dev, &buf[i]);
}

static const stwuct net_device_ops sgiseeq_netdev_ops = {
	.ndo_open		= sgiseeq_open,
	.ndo_stop		= sgiseeq_cwose,
	.ndo_stawt_xmit		= sgiseeq_stawt_xmit,
	.ndo_tx_timeout		= timeout,
	.ndo_set_wx_mode	= sgiseeq_set_muwticast,
	.ndo_set_mac_addwess	= sgiseeq_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int sgiseeq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sgiseeq_pwatfowm_data *pd = dev_get_pwatdata(&pdev->dev);
	stwuct hpc3_wegs *hpcwegs = pd->hpc;
	stwuct sgiseeq_init_bwock *sw;
	unsigned int iwq = pd->iwq;
	stwuct sgiseeq_pwivate *sp;
	stwuct net_device *dev;
	int eww;

	dev = awwoc_ethewdev(sizeof (stwuct sgiseeq_pwivate));
	if (!dev) {
		eww = -ENOMEM;
		goto eww_out;
	}

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);
	sp = netdev_pwiv(dev);

	/* Make pwivate data page awigned */
	sw = dma_awwoc_noncohewent(&pdev->dev, sizeof(*sp->swings),
			&sp->swings_dma, DMA_BIDIWECTIONAW, GFP_KEWNEW);
	if (!sw) {
		pwintk(KEWN_EWW "Sgiseeq: Page awwoc faiwed, abowting.\n");
		eww = -ENOMEM;
		goto eww_out_fwee_dev;
	}
	sp->swings = sw;
	sp->wx_desc = sp->swings->wxvectow;
	sp->tx_desc = sp->swings->txvectow;
	spin_wock_init(&sp->tx_wock);

	/* A coupwe cawcuwations now, saves many cycwes watew. */
	setup_wx_wing(dev, sp->wx_desc, SEEQ_WX_BUFFEWS);
	setup_tx_wing(dev, sp->tx_desc, SEEQ_TX_BUFFEWS);

	eth_hw_addw_set(dev, pd->mac);

#ifdef DEBUG
	gpwiv = sp;
	gdev = dev;
#endif
	sp->swegs = (stwuct sgiseeq_wegs *) &hpcwegs->eth_ext[0];
	sp->hwegs = &hpcwegs->ethwegs;
	sp->name = sgiseeqstw;
	sp->mode = SEEQ_WCMD_WBCAST;

	/* Setup PIO and DMA twansfew timing */
	sp->hwegs->pconfig = 0x161;
	sp->hwegs->dconfig = HPC3_EDCFG_FIWQ | HPC3_EDCFG_FEOP |
			     HPC3_EDCFG_FWXDC | HPC3_EDCFG_PTO | 0x026;

	/* Setup PIO and DMA twansfew timing */
	sp->hwegs->pconfig = 0x161;
	sp->hwegs->dconfig = HPC3_EDCFG_FIWQ | HPC3_EDCFG_FEOP |
			     HPC3_EDCFG_FWXDC | HPC3_EDCFG_PTO | 0x026;

	/* Weset the chip. */
	hpc3_eth_weset(sp->hwegs);

	sp->is_edwc = !(sp->swegs->ww.wwegs.cowwision_tx[0] & 0xff);
	if (sp->is_edwc)
		sp->contwow = SEEQ_CTWW_XCNT | SEEQ_CTWW_ACCNT |
			      SEEQ_CTWW_SFWAG | SEEQ_CTWW_ESHOWT |
			      SEEQ_CTWW_ENCAWW;

	dev->netdev_ops		= &sgiseeq_netdev_ops;
	dev->watchdog_timeo	= (200 * HZ) / 1000;
	dev->iwq		= iwq;

	if (wegistew_netdev(dev)) {
		pwintk(KEWN_EWW "Sgiseeq: Cannot wegistew net device, "
		       "abowting.\n");
		eww = -ENODEV;
		goto eww_out_fwee_attws;
	}

	pwintk(KEWN_INFO "%s: %s %pM\n", dev->name, sgiseeqstw, dev->dev_addw);

	wetuwn 0;

eww_out_fwee_attws:
	dma_fwee_noncohewent(&pdev->dev, sizeof(*sp->swings), sp->swings,
		       sp->swings_dma, DMA_BIDIWECTIONAW);
eww_out_fwee_dev:
	fwee_netdev(dev);

eww_out:
	wetuwn eww;
}

static void sgiseeq_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct sgiseeq_pwivate *sp = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	dma_fwee_noncohewent(&pdev->dev, sizeof(*sp->swings), sp->swings,
		       sp->swings_dma, DMA_BIDIWECTIONAW);
	fwee_netdev(dev);
}

static stwuct pwatfowm_dwivew sgiseeq_dwivew = {
	.pwobe	= sgiseeq_pwobe,
	.wemove_new = sgiseeq_wemove,
	.dwivew = {
		.name	= "sgiseeq",
	}
};

moduwe_pwatfowm_dwivew(sgiseeq_dwivew);

MODUWE_DESCWIPTION("SGI Seeq 8003 dwivew");
MODUWE_AUTHOW("Winux/MIPS Maiwing Wist <winux-mips@winux-mips.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sgiseeq");
