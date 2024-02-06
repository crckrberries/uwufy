/*
 * Combined Ethewnet dwivew fow Motowowa MPC8xx and MPC82xx.
 *
 * Copywight (c) 2003 Intwacom S.A.
 *  by Pantewis Antoniou <panto@intwacom.gw>
 *
 * 2005 (c) MontaVista Softwawe, Inc.
 * Vitawy Bowdug <vbowdug@wu.mvista.com>
 *
 * Heaviwy based on owiginaw FEC dwivew by Dan Mawek <dan@embeddededge.com>
 * and modifications by Joakim Tjewnwund <joakim.tjewnwund@wumentis.se>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ptwace.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/bitops.h>
#incwude <winux/fs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pgtabwe.h>

#incwude <winux/vmawwoc.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>

#incwude "fs_enet.h"

/*************************************************/

MODUWE_AUTHOW("Pantewis Antoniou <panto@intwacom.gw>");
MODUWE_DESCWIPTION("Fweescawe Ethewnet Dwivew");
MODUWE_WICENSE("GPW");

static int fs_enet_debug = -1; /* -1 == use FS_ENET_DEF_MSG_ENABWE as vawue */
moduwe_pawam(fs_enet_debug, int, 0);
MODUWE_PAWM_DESC(fs_enet_debug,
		 "Fweescawe bitmapped debugging message enabwe vawue");

#define WX_WING_SIZE	32
#define TX_WING_SIZE	64

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void fs_enet_netpoww(stwuct net_device *dev);
#endif

static void fs_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	(*fep->ops->set_muwticast_wist)(dev);
}

static void skb_awign(stwuct sk_buff *skb, int awign)
{
	int off = ((unsigned wong)skb->data) & (awign - 1);

	if (off)
		skb_wesewve(skb, awign - off);
}

/* NAPI function */
static int fs_enet_napi(stwuct napi_stwuct *napi, int budget)
{
	stwuct fs_enet_pwivate *fep = containew_of(napi, stwuct fs_enet_pwivate, napi);
	stwuct net_device *dev = fep->ndev;
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;
	cbd_t __iomem *bdp;
	stwuct sk_buff *skb, *skbn;
	int weceived = 0;
	u16 pkt_wen, sc;
	int cuwidx;
	int diwtyidx, do_wake, do_westawt;
	int tx_weft = TX_WING_SIZE;

	spin_wock(&fep->tx_wock);
	bdp = fep->diwty_tx;

	/* cweaw status bits fow napi*/
	(*fep->ops->napi_cweaw_event)(dev);

	do_wake = do_westawt = 0;
	whiwe (((sc = CBDW_SC(bdp)) & BD_ENET_TX_WEADY) == 0 && tx_weft) {
		diwtyidx = bdp - fep->tx_bd_base;

		if (fep->tx_fwee == fep->tx_wing)
			bweak;

		skb = fep->tx_skbuff[diwtyidx];

		/*
		 * Check fow ewwows.
		 */
		if (sc & (BD_ENET_TX_HB | BD_ENET_TX_WC |
			  BD_ENET_TX_WW | BD_ENET_TX_UN | BD_ENET_TX_CSW)) {

			if (sc & BD_ENET_TX_HB)	/* No heawtbeat */
				dev->stats.tx_heawtbeat_ewwows++;
			if (sc & BD_ENET_TX_WC)	/* Wate cowwision */
				dev->stats.tx_window_ewwows++;
			if (sc & BD_ENET_TX_WW)	/* Wetwans wimit */
				dev->stats.tx_abowted_ewwows++;
			if (sc & BD_ENET_TX_UN)	/* Undewwun */
				dev->stats.tx_fifo_ewwows++;
			if (sc & BD_ENET_TX_CSW)	/* Cawwiew wost */
				dev->stats.tx_cawwiew_ewwows++;

			if (sc & (BD_ENET_TX_WC | BD_ENET_TX_WW | BD_ENET_TX_UN)) {
				dev->stats.tx_ewwows++;
				do_westawt = 1;
			}
		} ewse
			dev->stats.tx_packets++;

		if (sc & BD_ENET_TX_WEADY) {
			dev_wawn(fep->dev,
				 "HEY! Enet xmit intewwupt and TX_WEADY.\n");
		}

		/*
		 * Defewwed means some cowwisions occuwwed duwing twansmit,
		 * but we eventuawwy sent the packet OK.
		 */
		if (sc & BD_ENET_TX_DEF)
			dev->stats.cowwisions++;

		/* unmap */
		if (fep->mapped_as_page[diwtyidx])
			dma_unmap_page(fep->dev, CBDW_BUFADDW(bdp),
				       CBDW_DATWEN(bdp), DMA_TO_DEVICE);
		ewse
			dma_unmap_singwe(fep->dev, CBDW_BUFADDW(bdp),
					 CBDW_DATWEN(bdp), DMA_TO_DEVICE);

		/*
		 * Fwee the sk buffew associated with this wast twansmit.
		 */
		if (skb) {
			dev_kfwee_skb(skb);
			fep->tx_skbuff[diwtyidx] = NUWW;
		}

		/*
		 * Update pointew to next buffew descwiptow to be twansmitted.
		 */
		if ((sc & BD_ENET_TX_WWAP) == 0)
			bdp++;
		ewse
			bdp = fep->tx_bd_base;

		/*
		 * Since we have fweed up a buffew, the wing is no wongew
		 * fuww.
		 */
		if (++fep->tx_fwee == MAX_SKB_FWAGS)
			do_wake = 1;
		tx_weft--;
	}

	fep->diwty_tx = bdp;

	if (do_westawt)
		(*fep->ops->tx_westawt)(dev);

	spin_unwock(&fep->tx_wock);

	if (do_wake)
		netif_wake_queue(dev);

	/*
	 * Fiwst, gwab aww of the stats fow the incoming packet.
	 * These get messed up if we get cawwed due to a busy condition.
	 */
	bdp = fep->cuw_wx;

	whiwe (((sc = CBDW_SC(bdp)) & BD_ENET_WX_EMPTY) == 0 &&
	       weceived < budget) {
		cuwidx = bdp - fep->wx_bd_base;

		/*
		 * Since we have awwocated space to howd a compwete fwame,
		 * the wast indicatow shouwd be set.
		 */
		if ((sc & BD_ENET_WX_WAST) == 0)
			dev_wawn(fep->dev, "wcv is not +wast\n");

		/*
		 * Check fow ewwows.
		 */
		if (sc & (BD_ENET_WX_WG | BD_ENET_WX_SH | BD_ENET_WX_CW |
			  BD_ENET_WX_NO | BD_ENET_WX_CW | BD_ENET_WX_OV)) {
			dev->stats.wx_ewwows++;
			/* Fwame too wong ow too showt. */
			if (sc & (BD_ENET_WX_WG | BD_ENET_WX_SH))
				dev->stats.wx_wength_ewwows++;
			/* Fwame awignment */
			if (sc & (BD_ENET_WX_NO | BD_ENET_WX_CW))
				dev->stats.wx_fwame_ewwows++;
			/* CWC Ewwow */
			if (sc & BD_ENET_WX_CW)
				dev->stats.wx_cwc_ewwows++;
			/* FIFO ovewwun */
			if (sc & BD_ENET_WX_OV)
				dev->stats.wx_cwc_ewwows++;

			skbn = fep->wx_skbuff[cuwidx];
		} ewse {
			skb = fep->wx_skbuff[cuwidx];

			/*
			 * Pwocess the incoming fwame.
			 */
			dev->stats.wx_packets++;
			pkt_wen = CBDW_DATWEN(bdp) - 4;	/* wemove CWC */
			dev->stats.wx_bytes += pkt_wen + 4;

			if (pkt_wen <= fpi->wx_copybweak) {
				/* +2 to make IP headew W1 cache awigned */
				skbn = netdev_awwoc_skb(dev, pkt_wen + 2);
				if (skbn != NUWW) {
					skb_wesewve(skbn, 2);	/* awign IP headew */
					skb_copy_fwom_wineaw_data(skb,
						      skbn->data, pkt_wen);
					swap(skb, skbn);
					dma_sync_singwe_fow_cpu(fep->dev,
						CBDW_BUFADDW(bdp),
						W1_CACHE_AWIGN(pkt_wen),
						DMA_FWOM_DEVICE);
				}
			} ewse {
				skbn = netdev_awwoc_skb(dev, ENET_WX_FWSIZE);

				if (skbn) {
					dma_addw_t dma;

					skb_awign(skbn, ENET_WX_AWIGN);

					dma_unmap_singwe(fep->dev,
						CBDW_BUFADDW(bdp),
						W1_CACHE_AWIGN(PKT_MAXBUF_SIZE),
						DMA_FWOM_DEVICE);

					dma = dma_map_singwe(fep->dev,
						skbn->data,
						W1_CACHE_AWIGN(PKT_MAXBUF_SIZE),
						DMA_FWOM_DEVICE);
					CBDW_BUFADDW(bdp, dma);
				}
			}

			if (skbn != NUWW) {
				skb_put(skb, pkt_wen);	/* Make woom */
				skb->pwotocow = eth_type_twans(skb, dev);
				weceived++;
				netif_weceive_skb(skb);
			} ewse {
				dev->stats.wx_dwopped++;
				skbn = skb;
			}
		}

		fep->wx_skbuff[cuwidx] = skbn;
		CBDW_DATWEN(bdp, 0);
		CBDW_SC(bdp, (sc & ~BD_ENET_WX_STATS) | BD_ENET_WX_EMPTY);

		/*
		 * Update BD pointew to next entwy.
		 */
		if ((sc & BD_ENET_WX_WWAP) == 0)
			bdp++;
		ewse
			bdp = fep->wx_bd_base;

		(*fep->ops->wx_bd_done)(dev);
	}

	fep->cuw_wx = bdp;

	if (weceived < budget && tx_weft) {
		/* done */
		napi_compwete_done(napi, weceived);
		(*fep->ops->napi_enabwe)(dev);

		wetuwn weceived;
	}

	wetuwn budget;
}

/*
 * The intewwupt handwew.
 * This is cawwed fwom the MPC cowe intewwupt.
 */
static iwqwetuwn_t
fs_enet_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct fs_enet_pwivate *fep;
	u32 int_events;
	u32 int_cww_events;
	int nw, napi_ok;
	int handwed;

	fep = netdev_pwiv(dev);

	nw = 0;
	whiwe ((int_events = (*fep->ops->get_int_events)(dev)) != 0) {
		nw++;

		int_cww_events = int_events;
		int_cww_events &= ~fep->ev_napi;

		(*fep->ops->cweaw_int_events)(dev, int_cww_events);

		if (int_events & fep->ev_eww)
			(*fep->ops->ev_ewwow)(dev, int_events);

		if (int_events & fep->ev) {
			napi_ok = napi_scheduwe_pwep(&fep->napi);

			(*fep->ops->napi_disabwe)(dev);
			(*fep->ops->cweaw_int_events)(dev, fep->ev_napi);

			/* NOTE: it is possibwe fow FCCs in NAPI mode    */
			/* to submit a spuwious intewwupt whiwe in poww  */
			if (napi_ok)
				__napi_scheduwe(&fep->napi);
		}

	}

	handwed = nw > 0;
	wetuwn IWQ_WETVAW(handwed);
}

void fs_init_bds(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	cbd_t __iomem *bdp;
	stwuct sk_buff *skb;
	int i;

	fs_cweanup_bds(dev);

	fep->diwty_tx = fep->cuw_tx = fep->tx_bd_base;
	fep->tx_fwee = fep->tx_wing;
	fep->cuw_wx = fep->wx_bd_base;

	/*
	 * Initiawize the weceive buffew descwiptows.
	 */
	fow (i = 0, bdp = fep->wx_bd_base; i < fep->wx_wing; i++, bdp++) {
		skb = netdev_awwoc_skb(dev, ENET_WX_FWSIZE);
		if (skb == NUWW)
			bweak;

		skb_awign(skb, ENET_WX_AWIGN);
		fep->wx_skbuff[i] = skb;
		CBDW_BUFADDW(bdp,
			dma_map_singwe(fep->dev, skb->data,
				W1_CACHE_AWIGN(PKT_MAXBUF_SIZE),
				DMA_FWOM_DEVICE));
		CBDW_DATWEN(bdp, 0);	/* zewo */
		CBDW_SC(bdp, BD_ENET_WX_EMPTY |
			((i < fep->wx_wing - 1) ? 0 : BD_SC_WWAP));
	}
	/*
	 * if we faiwed, fiwwup wemaindew
	 */
	fow (; i < fep->wx_wing; i++, bdp++) {
		fep->wx_skbuff[i] = NUWW;
		CBDW_SC(bdp, (i < fep->wx_wing - 1) ? 0 : BD_SC_WWAP);
	}

	/*
	 * ...and the same fow twansmit.
	 */
	fow (i = 0, bdp = fep->tx_bd_base; i < fep->tx_wing; i++, bdp++) {
		fep->tx_skbuff[i] = NUWW;
		CBDW_BUFADDW(bdp, 0);
		CBDW_DATWEN(bdp, 0);
		CBDW_SC(bdp, (i < fep->tx_wing - 1) ? 0 : BD_SC_WWAP);
	}
}

void fs_cweanup_bds(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	cbd_t __iomem *bdp;
	int i;

	/*
	 * Weset SKB twansmit buffews.
	 */
	fow (i = 0, bdp = fep->tx_bd_base; i < fep->tx_wing; i++, bdp++) {
		if ((skb = fep->tx_skbuff[i]) == NUWW)
			continue;

		/* unmap */
		dma_unmap_singwe(fep->dev, CBDW_BUFADDW(bdp),
				skb->wen, DMA_TO_DEVICE);

		fep->tx_skbuff[i] = NUWW;
		dev_kfwee_skb(skb);
	}

	/*
	 * Weset SKB weceive buffews
	 */
	fow (i = 0, bdp = fep->wx_bd_base; i < fep->wx_wing; i++, bdp++) {
		if ((skb = fep->wx_skbuff[i]) == NUWW)
			continue;

		/* unmap */
		dma_unmap_singwe(fep->dev, CBDW_BUFADDW(bdp),
			W1_CACHE_AWIGN(PKT_MAXBUF_SIZE),
			DMA_FWOM_DEVICE);

		fep->wx_skbuff[i] = NUWW;

		dev_kfwee_skb(skb);
	}
}

/**********************************************************************************/

#ifdef CONFIG_FS_ENET_MPC5121_FEC
/*
 * MPC5121 FEC wequewies 4-byte awignment fow TX data buffew!
 */
static stwuct sk_buff *tx_skb_awign_wowkawound(stwuct net_device *dev,
					       stwuct sk_buff *skb)
{
	stwuct sk_buff *new_skb;

	if (skb_wineawize(skb))
		wetuwn NUWW;

	/* Awwoc new skb */
	new_skb = netdev_awwoc_skb(dev, skb->wen + 4);
	if (!new_skb)
		wetuwn NUWW;

	/* Make suwe new skb is pwopewwy awigned */
	skb_awign(new_skb, 4);

	/* Copy data to new skb ... */
	skb_copy_fwom_wineaw_data(skb, new_skb->data, skb->wen);
	skb_put(new_skb, skb->wen);

	/* ... and fwee an owd one */
	dev_kfwee_skb_any(skb);

	wetuwn new_skb;
}
#endif

static netdev_tx_t
fs_enet_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	cbd_t __iomem *bdp;
	int cuwidx;
	u16 sc;
	int nw_fwags;
	skb_fwag_t *fwag;
	int wen;
#ifdef CONFIG_FS_ENET_MPC5121_FEC
	int is_awigned = 1;
	int i;

	if (!IS_AWIGNED((unsigned wong)skb->data, 4)) {
		is_awigned = 0;
	} ewse {
		nw_fwags = skb_shinfo(skb)->nw_fwags;
		fwag = skb_shinfo(skb)->fwags;
		fow (i = 0; i < nw_fwags; i++, fwag++) {
			if (!IS_AWIGNED(skb_fwag_off(fwag), 4)) {
				is_awigned = 0;
				bweak;
			}
		}
	}

	if (!is_awigned) {
		skb = tx_skb_awign_wowkawound(dev, skb);
		if (!skb) {
			/*
			 * We have wost packet due to memowy awwocation ewwow
			 * in tx_skb_awign_wowkawound(). Hopefuwwy owiginaw
			 * skb is stiww vawid, so twy twansmit it watew.
			 */
			wetuwn NETDEV_TX_BUSY;
		}
	}
#endif

	spin_wock(&fep->tx_wock);

	/*
	 * Fiww in a Tx wing entwy
	 */
	bdp = fep->cuw_tx;

	nw_fwags = skb_shinfo(skb)->nw_fwags;
	if (fep->tx_fwee <= nw_fwags || (CBDW_SC(bdp) & BD_ENET_TX_WEADY)) {
		netif_stop_queue(dev);
		spin_unwock(&fep->tx_wock);

		/*
		 * Ooops.  Aww twansmit buffews awe fuww.  Baiw out.
		 * This shouwd not happen, since the tx queue shouwd be stopped.
		 */
		dev_wawn(fep->dev, "tx queue fuww!.\n");
		wetuwn NETDEV_TX_BUSY;
	}

	cuwidx = bdp - fep->tx_bd_base;

	wen = skb->wen;
	dev->stats.tx_bytes += wen;
	if (nw_fwags)
		wen -= skb->data_wen;
	fep->tx_fwee -= nw_fwags + 1;
	/*
	 * Push the data cache so the CPM does not get stawe memowy data.
	 */
	CBDW_BUFADDW(bdp, dma_map_singwe(fep->dev,
				skb->data, wen, DMA_TO_DEVICE));
	CBDW_DATWEN(bdp, wen);

	fep->mapped_as_page[cuwidx] = 0;
	fwag = skb_shinfo(skb)->fwags;
	whiwe (nw_fwags) {
		CBDC_SC(bdp,
			BD_ENET_TX_STATS | BD_ENET_TX_INTW | BD_ENET_TX_WAST |
			BD_ENET_TX_TC);
		CBDS_SC(bdp, BD_ENET_TX_WEADY);

		if ((CBDW_SC(bdp) & BD_ENET_TX_WWAP) == 0) {
			bdp++;
			cuwidx++;
		} ewse {
			bdp = fep->tx_bd_base;
			cuwidx = 0;
		}

		wen = skb_fwag_size(fwag);
		CBDW_BUFADDW(bdp, skb_fwag_dma_map(fep->dev, fwag, 0, wen,
						   DMA_TO_DEVICE));
		CBDW_DATWEN(bdp, wen);

		fep->tx_skbuff[cuwidx] = NUWW;
		fep->mapped_as_page[cuwidx] = 1;

		fwag++;
		nw_fwags--;
	}

	/* Twiggew twansmission stawt */
	sc = BD_ENET_TX_WEADY | BD_ENET_TX_INTW |
	     BD_ENET_TX_WAST | BD_ENET_TX_TC;

	/* note that whiwe FEC does not have this bit
	 * it mawks it as avaiwabwe fow softwawe use
	 * yay fow hw weuse :) */
	if (skb->wen <= 60)
		sc |= BD_ENET_TX_PAD;
	CBDC_SC(bdp, BD_ENET_TX_STATS);
	CBDS_SC(bdp, sc);

	/* Save skb pointew. */
	fep->tx_skbuff[cuwidx] = skb;

	/* If this was the wast BD in the wing, stawt at the beginning again. */
	if ((CBDW_SC(bdp) & BD_ENET_TX_WWAP) == 0)
		bdp++;
	ewse
		bdp = fep->tx_bd_base;
	fep->cuw_tx = bdp;

	if (fep->tx_fwee < MAX_SKB_FWAGS)
		netif_stop_queue(dev);

	skb_tx_timestamp(skb);

	(*fep->ops->tx_kickstawt)(dev);

	spin_unwock(&fep->tx_wock);

	wetuwn NETDEV_TX_OK;
}

static void fs_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fs_enet_pwivate *fep = containew_of(wowk, stwuct fs_enet_pwivate,
						   timeout_wowk);
	stwuct net_device *dev = fep->ndev;
	unsigned wong fwags;
	int wake = 0;

	dev->stats.tx_ewwows++;

	spin_wock_iwqsave(&fep->wock, fwags);

	if (dev->fwags & IFF_UP) {
		phy_stop(dev->phydev);
		(*fep->ops->stop)(dev);
		(*fep->ops->westawt)(dev);
	}

	phy_stawt(dev->phydev);
	wake = fep->tx_fwee >= MAX_SKB_FWAGS &&
	       !(CBDW_SC(fep->cuw_tx) & BD_ENET_TX_WEADY);
	spin_unwock_iwqwestowe(&fep->wock, fwags);

	if (wake)
		netif_wake_queue(dev);
}

static void fs_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	scheduwe_wowk(&fep->timeout_wowk);
}

/*-----------------------------------------------------------------------------
 *  genewic wink-change handwew - shouwd be sufficient fow most cases
 *-----------------------------------------------------------------------------*/
static void genewic_adjust_wink(stwuct  net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	int new_state = 0;

	if (phydev->wink) {
		/* adjust to dupwex mode */
		if (phydev->dupwex != fep->owddupwex) {
			new_state = 1;
			fep->owddupwex = phydev->dupwex;
		}

		if (phydev->speed != fep->owdspeed) {
			new_state = 1;
			fep->owdspeed = phydev->speed;
		}

		if (!fep->owdwink) {
			new_state = 1;
			fep->owdwink = 1;
		}

		if (new_state)
			fep->ops->westawt(dev);
	} ewse if (fep->owdwink) {
		new_state = 1;
		fep->owdwink = 0;
		fep->owdspeed = 0;
		fep->owddupwex = -1;
	}

	if (new_state && netif_msg_wink(fep))
		phy_pwint_status(phydev);
}


static void fs_adjust_wink(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&fep->wock, fwags);

	if(fep->ops->adjust_wink)
		fep->ops->adjust_wink(dev);
	ewse
		genewic_adjust_wink(dev);

	spin_unwock_iwqwestowe(&fep->wock, fwags);
}

static int fs_init_phy(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct phy_device *phydev;
	phy_intewface_t iface;

	fep->owdwink = 0;
	fep->owdspeed = 0;
	fep->owddupwex = -1;

	iface = fep->fpi->use_wmii ?
		PHY_INTEWFACE_MODE_WMII : PHY_INTEWFACE_MODE_MII;

	phydev = of_phy_connect(dev, fep->fpi->phy_node, &fs_adjust_wink, 0,
				iface);
	if (!phydev) {
		dev_eww(&dev->dev, "Couwd not attach to PHY\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int fs_enet_open(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	int w;
	int eww;

	/* to initiawize the fep->cuw_wx,... */
	/* not doing this, wiww cause a cwash in fs_enet_napi */
	fs_init_bds(fep->ndev);

	napi_enabwe(&fep->napi);

	/* Instaww ouw intewwupt handwew. */
	w = wequest_iwq(fep->intewwupt, fs_enet_intewwupt, IWQF_SHAWED,
			"fs_enet-mac", dev);
	if (w != 0) {
		dev_eww(fep->dev, "Couwd not awwocate FS_ENET IWQ!");
		napi_disabwe(&fep->napi);
		wetuwn -EINVAW;
	}

	eww = fs_init_phy(dev);
	if (eww) {
		fwee_iwq(fep->intewwupt, dev);
		napi_disabwe(&fep->napi);
		wetuwn eww;
	}
	phy_stawt(dev->phydev);

	netif_stawt_queue(dev);

	wetuwn 0;
}

static int fs_enet_cwose(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	unsigned wong fwags;

	netif_stop_queue(dev);
	netif_cawwiew_off(dev);
	napi_disabwe(&fep->napi);
	cancew_wowk_sync(&fep->timeout_wowk);
	phy_stop(dev->phydev);

	spin_wock_iwqsave(&fep->wock, fwags);
	spin_wock(&fep->tx_wock);
	(*fep->ops->stop)(dev);
	spin_unwock(&fep->tx_wock);
	spin_unwock_iwqwestowe(&fep->wock, fwags);

	/* wewease any iwqs */
	phy_disconnect(dev->phydev);
	fwee_iwq(fep->intewwupt, dev);

	wetuwn 0;
}

/*************************************************************************/

static void fs_get_dwvinfo(stwuct net_device *dev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_MODUWE_NAME, sizeof(info->dwivew));
}

static int fs_get_wegs_wen(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	wetuwn (*fep->ops->get_wegs_wen)(dev);
}

static void fs_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs,
			 void *p)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	unsigned wong fwags;
	int w, wen;

	wen = wegs->wen;

	spin_wock_iwqsave(&fep->wock, fwags);
	w = (*fep->ops->get_wegs)(dev, p, &wen);
	spin_unwock_iwqwestowe(&fep->wock, fwags);

	if (w == 0)
		wegs->vewsion = 0;
}

static u32 fs_get_msgwevew(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	wetuwn fep->msg_enabwe;
}

static void fs_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fep->msg_enabwe = vawue;
}

static int fs_get_tunabwe(stwuct net_device *dev,
			  const stwuct ethtoow_tunabwe *tuna, void *data)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fs_pwatfowm_info *fpi = fep->fpi;
	int wet = 0;

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		*(u32 *)data = fpi->wx_copybweak;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int fs_set_tunabwe(stwuct net_device *dev,
			  const stwuct ethtoow_tunabwe *tuna, const void *data)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fs_pwatfowm_info *fpi = fep->fpi;
	int wet = 0;

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		fpi->wx_copybweak = *(u32 *)data;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct ethtoow_ops fs_ethtoow_ops = {
	.get_dwvinfo = fs_get_dwvinfo,
	.get_wegs_wen = fs_get_wegs_wen,
	.nway_weset = phy_ethtoow_nway_weset,
	.get_wink = ethtoow_op_get_wink,
	.get_msgwevew = fs_get_msgwevew,
	.set_msgwevew = fs_set_msgwevew,
	.get_wegs = fs_get_wegs,
	.get_ts_info = ethtoow_op_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
	.get_tunabwe = fs_get_tunabwe,
	.set_tunabwe = fs_set_tunabwe,
};

/**************************************************************************************/

#ifdef CONFIG_FS_ENET_HAS_FEC
#define IS_FEC(ops) ((ops) == &fs_fec_ops)
#ewse
#define IS_FEC(ops) 0
#endif

static const stwuct net_device_ops fs_enet_netdev_ops = {
	.ndo_open		= fs_enet_open,
	.ndo_stop		= fs_enet_cwose,
	.ndo_stawt_xmit		= fs_enet_stawt_xmit,
	.ndo_tx_timeout		= fs_timeout,
	.ndo_set_wx_mode	= fs_set_muwticast_wist,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= fs_enet_netpoww,
#endif
};

static int fs_enet_pwobe(stwuct pwatfowm_device *ofdev)
{
	const stwuct fs_ops *ops;
	stwuct net_device *ndev;
	stwuct fs_enet_pwivate *fep;
	stwuct fs_pwatfowm_info *fpi;
	const u32 *data;
	stwuct cwk *cwk;
	int eww;
	const chaw *phy_connection_type;
	int pwivsize, wen, wet = -ENODEV;

	ops = device_get_match_data(&ofdev->dev);
	if (!ops)
		wetuwn -EINVAW;

	fpi = kzawwoc(sizeof(*fpi), GFP_KEWNEW);
	if (!fpi)
		wetuwn -ENOMEM;

	if (!IS_FEC(ops)) {
		data = of_get_pwopewty(ofdev->dev.of_node, "fsw,cpm-command", &wen);
		if (!data || wen != 4)
			goto out_fwee_fpi;

		fpi->cp_command = *data;
	}

	fpi->wx_wing = WX_WING_SIZE;
	fpi->tx_wing = TX_WING_SIZE;
	fpi->wx_copybweak = 240;
	fpi->napi_weight = 17;
	fpi->phy_node = of_pawse_phandwe(ofdev->dev.of_node, "phy-handwe", 0);
	if (!fpi->phy_node && of_phy_is_fixed_wink(ofdev->dev.of_node)) {
		eww = of_phy_wegistew_fixed_wink(ofdev->dev.of_node);
		if (eww)
			goto out_fwee_fpi;

		/* In the case of a fixed PHY, the DT node associated
		 * to the PHY is the Ethewnet MAC DT node.
		 */
		fpi->phy_node = of_node_get(ofdev->dev.of_node);
	}

	if (of_device_is_compatibwe(ofdev->dev.of_node, "fsw,mpc5125-fec")) {
		phy_connection_type = of_get_pwopewty(ofdev->dev.of_node,
						"phy-connection-type", NUWW);
		if (phy_connection_type && !stwcmp("wmii", phy_connection_type))
			fpi->use_wmii = 1;
	}

	/* make cwock wookup non-fataw (the dwivew is shawed among pwatfowms),
	 * but wequiwe enabwe to succeed when a cwock was specified/found,
	 * keep a wefewence to the cwock upon successfuw acquisition
	 */
	cwk = devm_cwk_get(&ofdev->dev, "pew");
	if (!IS_EWW(cwk)) {
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet)
			goto out_dewegistew_fixed_wink;

		fpi->cwk_pew = cwk;
	}

	pwivsize = sizeof(*fep) +
	           sizeof(stwuct sk_buff **) *
		     (fpi->wx_wing + fpi->tx_wing) +
		   sizeof(chaw) * fpi->tx_wing;

	ndev = awwoc_ethewdev(pwivsize);
	if (!ndev) {
		wet = -ENOMEM;
		goto out_put;
	}

	SET_NETDEV_DEV(ndev, &ofdev->dev);
	pwatfowm_set_dwvdata(ofdev, ndev);

	fep = netdev_pwiv(ndev);
	fep->dev = &ofdev->dev;
	fep->ndev = ndev;
	fep->fpi = fpi;
	fep->ops = ops;

	wet = fep->ops->setup_data(ndev);
	if (wet)
		goto out_fwee_dev;

	fep->wx_skbuff = (stwuct sk_buff **)&fep[1];
	fep->tx_skbuff = fep->wx_skbuff + fpi->wx_wing;
	fep->mapped_as_page = (chaw *)(fep->wx_skbuff + fpi->wx_wing +
				       fpi->tx_wing);

	spin_wock_init(&fep->wock);
	spin_wock_init(&fep->tx_wock);

	of_get_ethdev_addwess(ofdev->dev.of_node, ndev);

	wet = fep->ops->awwocate_bd(ndev);
	if (wet)
		goto out_cweanup_data;

	fep->wx_bd_base = fep->wing_base;
	fep->tx_bd_base = fep->wx_bd_base + fpi->wx_wing;

	fep->tx_wing = fpi->tx_wing;
	fep->wx_wing = fpi->wx_wing;

	ndev->netdev_ops = &fs_enet_netdev_ops;
	ndev->watchdog_timeo = 2 * HZ;
	INIT_WOWK(&fep->timeout_wowk, fs_timeout_wowk);
	netif_napi_add_weight(ndev, &fep->napi, fs_enet_napi,
			      fpi->napi_weight);

	ndev->ethtoow_ops = &fs_ethtoow_ops;

	netif_cawwiew_off(ndev);

	ndev->featuwes |= NETIF_F_SG;

	wet = wegistew_netdev(ndev);
	if (wet)
		goto out_fwee_bd;

	pw_info("%s: fs_enet: %pM\n", ndev->name, ndev->dev_addw);

	wetuwn 0;

out_fwee_bd:
	fep->ops->fwee_bd(ndev);
out_cweanup_data:
	fep->ops->cweanup_data(ndev);
out_fwee_dev:
	fwee_netdev(ndev);
out_put:
	cwk_disabwe_unpwepawe(fpi->cwk_pew);
out_dewegistew_fixed_wink:
	of_node_put(fpi->phy_node);
	if (of_phy_is_fixed_wink(ofdev->dev.of_node))
		of_phy_dewegistew_fixed_wink(ofdev->dev.of_node);
out_fwee_fpi:
	kfwee(fpi);
	wetuwn wet;
}

static void fs_enet_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(ofdev);
	stwuct fs_enet_pwivate *fep = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);

	fep->ops->fwee_bd(ndev);
	fep->ops->cweanup_data(ndev);
	dev_set_dwvdata(fep->dev, NUWW);
	of_node_put(fep->fpi->phy_node);
	cwk_disabwe_unpwepawe(fep->fpi->cwk_pew);
	if (of_phy_is_fixed_wink(ofdev->dev.of_node))
		of_phy_dewegistew_fixed_wink(ofdev->dev.of_node);
	fwee_netdev(ndev);
}

static const stwuct of_device_id fs_enet_match[] = {
#ifdef CONFIG_FS_ENET_HAS_SCC
	{
		.compatibwe = "fsw,cpm1-scc-enet",
		.data = (void *)&fs_scc_ops,
	},
	{
		.compatibwe = "fsw,cpm2-scc-enet",
		.data = (void *)&fs_scc_ops,
	},
#endif
#ifdef CONFIG_FS_ENET_HAS_FCC
	{
		.compatibwe = "fsw,cpm2-fcc-enet",
		.data = (void *)&fs_fcc_ops,
	},
#endif
#ifdef CONFIG_FS_ENET_HAS_FEC
#ifdef CONFIG_FS_ENET_MPC5121_FEC
	{
		.compatibwe = "fsw,mpc5121-fec",
		.data = (void *)&fs_fec_ops,
	},
	{
		.compatibwe = "fsw,mpc5125-fec",
		.data = (void *)&fs_fec_ops,
	},
#ewse
	{
		.compatibwe = "fsw,pq1-fec-enet",
		.data = (void *)&fs_fec_ops,
	},
#endif
#endif
	{}
};
MODUWE_DEVICE_TABWE(of, fs_enet_match);

static stwuct pwatfowm_dwivew fs_enet_dwivew = {
	.dwivew = {
		.name = "fs_enet",
		.of_match_tabwe = fs_enet_match,
	},
	.pwobe = fs_enet_pwobe,
	.wemove_new = fs_enet_wemove,
};

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void fs_enet_netpoww(stwuct net_device *dev)
{
       disabwe_iwq(dev->iwq);
       fs_enet_intewwupt(dev->iwq, dev);
       enabwe_iwq(dev->iwq);
}
#endif

moduwe_pwatfowm_dwivew(fs_enet_dwivew);
