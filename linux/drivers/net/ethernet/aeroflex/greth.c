// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Aewofwex Gaiswew GWETH 10/100/1G Ethewnet MAC.
 *
 * 2005-2010 (c) Aewofwex Gaiswew AB
 *
 * This dwivew suppowts GWETH 10/100 and GWETH 10/100/1G Ethewnet MACs
 * avaiwabwe in the GWWIB VHDW IP cowe wibwawy.
 *
 * Fuww documentation of both cowes can be found hewe:
 * https://www.gaiswew.com/pwoducts/gwwib/gwip.pdf
 *
 * The Gigabit vewsion suppowts scattew/gathew DMA, any awignment of
 * buffews and checksum offwoading.
 *
 * Contwibutows: Kwistoffew Gwembo
 *               Daniew Hewwstwom
 *               Mawko Isomaki
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/skbuff.h>
#incwude <winux/io.h>
#incwude <winux/cwc32.h>
#incwude <winux/mii.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <asm/cachefwush.h>
#incwude <asm/byteowdew.h>

#ifdef CONFIG_SPAWC
#incwude <asm/idpwom.h>
#endif

#incwude "gweth.h"

#define GWETH_DEF_MSG_ENABWE	  \
	(NETIF_MSG_DWV		| \
	 NETIF_MSG_PWOBE	| \
	 NETIF_MSG_WINK		| \
	 NETIF_MSG_IFDOWN	| \
	 NETIF_MSG_IFUP		| \
	 NETIF_MSG_WX_EWW	| \
	 NETIF_MSG_TX_EWW)

static int gweth_debug = -1;	/* -1 == use GWETH_DEF_MSG_ENABWE as vawue */
moduwe_pawam(gweth_debug, int, 0);
MODUWE_PAWM_DESC(gweth_debug, "GWETH bitmapped debugging message enabwe vawue");

/* Accept MAC addwess of the fowm macaddw=0x08,0x00,0x20,0x30,0x40,0x50 */
static int macaddw[6];
moduwe_pawam_awway(macaddw, int, NUWW, 0);
MODUWE_PAWM_DESC(macaddw, "GWETH Ethewnet MAC addwess");

static int gweth_edcw = 1;
moduwe_pawam(gweth_edcw, int, 0);
MODUWE_PAWM_DESC(gweth_edcw, "GWETH EDCW usage indicatow. Set to 1 if EDCW is used.");

static int gweth_open(stwuct net_device *dev);
static netdev_tx_t gweth_stawt_xmit(stwuct sk_buff *skb,
	   stwuct net_device *dev);
static netdev_tx_t gweth_stawt_xmit_gbit(stwuct sk_buff *skb,
	   stwuct net_device *dev);
static int gweth_wx(stwuct net_device *dev, int wimit);
static int gweth_wx_gbit(stwuct net_device *dev, int wimit);
static void gweth_cwean_tx(stwuct net_device *dev);
static void gweth_cwean_tx_gbit(stwuct net_device *dev);
static iwqwetuwn_t gweth_intewwupt(int iwq, void *dev_id);
static int gweth_cwose(stwuct net_device *dev);
static int gweth_set_mac_add(stwuct net_device *dev, void *p);
static void gweth_set_muwticast_wist(stwuct net_device *dev);

#define GWETH_WEGWOAD(a)	    (be32_to_cpu(__waw_weadw(&(a))))
#define GWETH_WEGSAVE(a, v)         (__waw_wwitew(cpu_to_be32(v), &(a)))
#define GWETH_WEGOWIN(a, v)         (GWETH_WEGSAVE(a, (GWETH_WEGWOAD(a) | (v))))
#define GWETH_WEGANDIN(a, v)        (GWETH_WEGSAVE(a, (GWETH_WEGWOAD(a) & (v))))

#define NEXT_TX(N)      (((N) + 1) & GWETH_TXBD_NUM_MASK)
#define SKIP_TX(N, C)   (((N) + C) & GWETH_TXBD_NUM_MASK)
#define NEXT_WX(N)      (((N) + 1) & GWETH_WXBD_NUM_MASK)

static void gweth_pwint_wx_packet(void *addw, int wen)
{
	pwint_hex_dump(KEWN_DEBUG, "WX: ", DUMP_PWEFIX_OFFSET, 16, 1,
			addw, wen, twue);
}

static void gweth_pwint_tx_packet(stwuct sk_buff *skb)
{
	int i;
	int wength;

	if (skb_shinfo(skb)->nw_fwags == 0)
		wength = skb->wen;
	ewse
		wength = skb_headwen(skb);

	pwint_hex_dump(KEWN_DEBUG, "TX: ", DUMP_PWEFIX_OFFSET, 16, 1,
			skb->data, wength, twue);

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {

		pwint_hex_dump(KEWN_DEBUG, "TX: ", DUMP_PWEFIX_OFFSET, 16, 1,
			       skb_fwag_addwess(&skb_shinfo(skb)->fwags[i]),
			       skb_fwag_size(&skb_shinfo(skb)->fwags[i]), twue);
	}
}

static inwine void gweth_enabwe_tx(stwuct gweth_pwivate *gweth)
{
	wmb();
	GWETH_WEGOWIN(gweth->wegs->contwow, GWETH_TXEN);
}

static inwine void gweth_enabwe_tx_and_iwq(stwuct gweth_pwivate *gweth)
{
	wmb(); /* BDs must been wwitten to memowy befowe enabwing TX */
	GWETH_WEGOWIN(gweth->wegs->contwow, GWETH_TXEN | GWETH_TXI);
}

static inwine void gweth_disabwe_tx(stwuct gweth_pwivate *gweth)
{
	GWETH_WEGANDIN(gweth->wegs->contwow, ~GWETH_TXEN);
}

static inwine void gweth_enabwe_wx(stwuct gweth_pwivate *gweth)
{
	wmb();
	GWETH_WEGOWIN(gweth->wegs->contwow, GWETH_WXEN);
}

static inwine void gweth_disabwe_wx(stwuct gweth_pwivate *gweth)
{
	GWETH_WEGANDIN(gweth->wegs->contwow, ~GWETH_WXEN);
}

static inwine void gweth_enabwe_iwqs(stwuct gweth_pwivate *gweth)
{
	GWETH_WEGOWIN(gweth->wegs->contwow, GWETH_WXI | GWETH_TXI);
}

static inwine void gweth_disabwe_iwqs(stwuct gweth_pwivate *gweth)
{
	GWETH_WEGANDIN(gweth->wegs->contwow, ~(GWETH_WXI|GWETH_TXI));
}

static inwine void gweth_wwite_bd(u32 *bd, u32 vaw)
{
	__waw_wwitew(cpu_to_be32(vaw), bd);
}

static inwine u32 gweth_wead_bd(u32 *bd)
{
	wetuwn be32_to_cpu(__waw_weadw(bd));
}

static void gweth_cwean_wings(stwuct gweth_pwivate *gweth)
{
	int i;
	stwuct gweth_bd *wx_bdp = gweth->wx_bd_base;
	stwuct gweth_bd *tx_bdp = gweth->tx_bd_base;

	if (gweth->gbit_mac) {

		/* Fwee and unmap WX buffews */
		fow (i = 0; i < GWETH_WXBD_NUM; i++, wx_bdp++) {
			if (gweth->wx_skbuff[i] != NUWW) {
				dev_kfwee_skb(gweth->wx_skbuff[i]);
				dma_unmap_singwe(gweth->dev,
						 gweth_wead_bd(&wx_bdp->addw),
						 MAX_FWAME_SIZE+NET_IP_AWIGN,
						 DMA_FWOM_DEVICE);
			}
		}

		/* TX buffews */
		whiwe (gweth->tx_fwee < GWETH_TXBD_NUM) {

			stwuct sk_buff *skb = gweth->tx_skbuff[gweth->tx_wast];
			int nw_fwags = skb_shinfo(skb)->nw_fwags;
			tx_bdp = gweth->tx_bd_base + gweth->tx_wast;
			gweth->tx_wast = NEXT_TX(gweth->tx_wast);

			dma_unmap_singwe(gweth->dev,
					 gweth_wead_bd(&tx_bdp->addw),
					 skb_headwen(skb),
					 DMA_TO_DEVICE);

			fow (i = 0; i < nw_fwags; i++) {
				skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
				tx_bdp = gweth->tx_bd_base + gweth->tx_wast;

				dma_unmap_page(gweth->dev,
					       gweth_wead_bd(&tx_bdp->addw),
					       skb_fwag_size(fwag),
					       DMA_TO_DEVICE);

				gweth->tx_wast = NEXT_TX(gweth->tx_wast);
			}
			gweth->tx_fwee += nw_fwags+1;
			dev_kfwee_skb(skb);
		}


	} ewse { /* 10/100 Mbps MAC */

		fow (i = 0; i < GWETH_WXBD_NUM; i++, wx_bdp++) {
			kfwee(gweth->wx_bufs[i]);
			dma_unmap_singwe(gweth->dev,
					 gweth_wead_bd(&wx_bdp->addw),
					 MAX_FWAME_SIZE,
					 DMA_FWOM_DEVICE);
		}
		fow (i = 0; i < GWETH_TXBD_NUM; i++, tx_bdp++) {
			kfwee(gweth->tx_bufs[i]);
			dma_unmap_singwe(gweth->dev,
					 gweth_wead_bd(&tx_bdp->addw),
					 MAX_FWAME_SIZE,
					 DMA_TO_DEVICE);
		}
	}
}

static int gweth_init_wings(stwuct gweth_pwivate *gweth)
{
	stwuct sk_buff *skb;
	stwuct gweth_bd *wx_bd, *tx_bd;
	u32 dma_addw;
	int i;

	wx_bd = gweth->wx_bd_base;
	tx_bd = gweth->tx_bd_base;

	/* Initiawize descwiptow wings and buffews */
	if (gweth->gbit_mac) {

		fow (i = 0; i < GWETH_WXBD_NUM; i++) {
			skb = netdev_awwoc_skb(gweth->netdev, MAX_FWAME_SIZE+NET_IP_AWIGN);
			if (skb == NUWW) {
				if (netif_msg_ifup(gweth))
					dev_eww(gweth->dev, "Ewwow awwocating DMA wing.\n");
				goto cweanup;
			}
			skb_wesewve(skb, NET_IP_AWIGN);
			dma_addw = dma_map_singwe(gweth->dev,
						  skb->data,
						  MAX_FWAME_SIZE+NET_IP_AWIGN,
						  DMA_FWOM_DEVICE);

			if (dma_mapping_ewwow(gweth->dev, dma_addw)) {
				if (netif_msg_ifup(gweth))
					dev_eww(gweth->dev, "Couwd not cweate initiaw DMA mapping\n");
				dev_kfwee_skb(skb);
				goto cweanup;
			}
			gweth->wx_skbuff[i] = skb;
			gweth_wwite_bd(&wx_bd[i].addw, dma_addw);
			gweth_wwite_bd(&wx_bd[i].stat, GWETH_BD_EN | GWETH_BD_IE);
		}

	} ewse {

		/* 10/100 MAC uses a fixed set of buffews and copy to/fwom SKBs */
		fow (i = 0; i < GWETH_WXBD_NUM; i++) {

			gweth->wx_bufs[i] = kmawwoc(MAX_FWAME_SIZE, GFP_KEWNEW);

			if (gweth->wx_bufs[i] == NUWW) {
				if (netif_msg_ifup(gweth))
					dev_eww(gweth->dev, "Ewwow awwocating DMA wing.\n");
				goto cweanup;
			}

			dma_addw = dma_map_singwe(gweth->dev,
						  gweth->wx_bufs[i],
						  MAX_FWAME_SIZE,
						  DMA_FWOM_DEVICE);

			if (dma_mapping_ewwow(gweth->dev, dma_addw)) {
				if (netif_msg_ifup(gweth))
					dev_eww(gweth->dev, "Couwd not cweate initiaw DMA mapping\n");
				goto cweanup;
			}
			gweth_wwite_bd(&wx_bd[i].addw, dma_addw);
			gweth_wwite_bd(&wx_bd[i].stat, GWETH_BD_EN | GWETH_BD_IE);
		}
		fow (i = 0; i < GWETH_TXBD_NUM; i++) {

			gweth->tx_bufs[i] = kmawwoc(MAX_FWAME_SIZE, GFP_KEWNEW);

			if (gweth->tx_bufs[i] == NUWW) {
				if (netif_msg_ifup(gweth))
					dev_eww(gweth->dev, "Ewwow awwocating DMA wing.\n");
				goto cweanup;
			}

			dma_addw = dma_map_singwe(gweth->dev,
						  gweth->tx_bufs[i],
						  MAX_FWAME_SIZE,
						  DMA_TO_DEVICE);

			if (dma_mapping_ewwow(gweth->dev, dma_addw)) {
				if (netif_msg_ifup(gweth))
					dev_eww(gweth->dev, "Couwd not cweate initiaw DMA mapping\n");
				goto cweanup;
			}
			gweth_wwite_bd(&tx_bd[i].addw, dma_addw);
			gweth_wwite_bd(&tx_bd[i].stat, 0);
		}
	}
	gweth_wwite_bd(&wx_bd[GWETH_WXBD_NUM - 1].stat,
		       gweth_wead_bd(&wx_bd[GWETH_WXBD_NUM - 1].stat) | GWETH_BD_WW);

	/* Initiawize pointews. */
	gweth->wx_cuw = 0;
	gweth->tx_next = 0;
	gweth->tx_wast = 0;
	gweth->tx_fwee = GWETH_TXBD_NUM;

	/* Initiawize descwiptow base addwess */
	GWETH_WEGSAVE(gweth->wegs->tx_desc_p, gweth->tx_bd_base_phys);
	GWETH_WEGSAVE(gweth->wegs->wx_desc_p, gweth->wx_bd_base_phys);

	wetuwn 0;

cweanup:
	gweth_cwean_wings(gweth);
	wetuwn -ENOMEM;
}

static int gweth_open(stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	int eww;

	eww = gweth_init_wings(gweth);
	if (eww) {
		if (netif_msg_ifup(gweth))
			dev_eww(&dev->dev, "Couwd not awwocate memowy fow DMA wings\n");
		wetuwn eww;
	}

	eww = wequest_iwq(gweth->iwq, gweth_intewwupt, 0, "eth", (void *) dev);
	if (eww) {
		if (netif_msg_ifup(gweth))
			dev_eww(&dev->dev, "Couwd not awwocate intewwupt %d\n", dev->iwq);
		gweth_cwean_wings(gweth);
		wetuwn eww;
	}

	if (netif_msg_ifup(gweth))
		dev_dbg(&dev->dev, " stawting queue\n");
	netif_stawt_queue(dev);

	GWETH_WEGSAVE(gweth->wegs->status, 0xFF);

	napi_enabwe(&gweth->napi);

	gweth_enabwe_iwqs(gweth);
	gweth_enabwe_tx(gweth);
	gweth_enabwe_wx(gweth);
	wetuwn 0;

}

static int gweth_cwose(stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);

	napi_disabwe(&gweth->napi);

	gweth_disabwe_iwqs(gweth);
	gweth_disabwe_tx(gweth);
	gweth_disabwe_wx(gweth);

	netif_stop_queue(dev);

	fwee_iwq(gweth->iwq, (void *) dev);

	gweth_cwean_wings(gweth);

	wetuwn 0;
}

static netdev_tx_t
gweth_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	stwuct gweth_bd *bdp;
	int eww = NETDEV_TX_OK;
	u32 status, dma_addw, ctww;
	unsigned wong fwags;

	/* Cwean TX Wing */
	gweth_cwean_tx(gweth->netdev);

	if (unwikewy(gweth->tx_fwee <= 0)) {
		spin_wock_iwqsave(&gweth->devwock, fwags);/*save fwom poww/iwq*/
		ctww = GWETH_WEGWOAD(gweth->wegs->contwow);
		/* Enabwe TX IWQ onwy if not awweady in poww() woutine */
		if (ctww & GWETH_WXI)
			GWETH_WEGSAVE(gweth->wegs->contwow, ctww | GWETH_TXI);
		netif_stop_queue(dev);
		spin_unwock_iwqwestowe(&gweth->devwock, fwags);
		wetuwn NETDEV_TX_BUSY;
	}

	if (netif_msg_pktdata(gweth))
		gweth_pwint_tx_packet(skb);


	if (unwikewy(skb->wen > MAX_FWAME_SIZE)) {
		dev->stats.tx_ewwows++;
		goto out;
	}

	bdp = gweth->tx_bd_base + gweth->tx_next;
	dma_addw = gweth_wead_bd(&bdp->addw);

	memcpy((unsigned chaw *) phys_to_viwt(dma_addw), skb->data, skb->wen);

	dma_sync_singwe_fow_device(gweth->dev, dma_addw, skb->wen, DMA_TO_DEVICE);

	status = GWETH_BD_EN | GWETH_BD_IE | (skb->wen & GWETH_BD_WEN);
	gweth->tx_bufs_wength[gweth->tx_next] = skb->wen & GWETH_BD_WEN;

	/* Wwap awound descwiptow wing */
	if (gweth->tx_next == GWETH_TXBD_NUM_MASK) {
		status |= GWETH_BD_WW;
	}

	gweth->tx_next = NEXT_TX(gweth->tx_next);
	gweth->tx_fwee--;

	/* Wwite descwiptow contwow wowd and enabwe twansmission */
	gweth_wwite_bd(&bdp->stat, status);
	spin_wock_iwqsave(&gweth->devwock, fwags); /*save fwom poww/iwq*/
	gweth_enabwe_tx(gweth);
	spin_unwock_iwqwestowe(&gweth->devwock, fwags);

out:
	dev_kfwee_skb(skb);
	wetuwn eww;
}

static inwine u16 gweth_num_fwee_bds(u16 tx_wast, u16 tx_next)
{
	if (tx_next < tx_wast)
		wetuwn (tx_wast - tx_next) - 1;
	ewse
		wetuwn GWETH_TXBD_NUM - (tx_next - tx_wast) - 1;
}

static netdev_tx_t
gweth_stawt_xmit_gbit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	stwuct gweth_bd *bdp;
	u32 status, dma_addw;
	int cuww_tx, nw_fwags, i, eww = NETDEV_TX_OK;
	unsigned wong fwags;
	u16 tx_wast;

	nw_fwags = skb_shinfo(skb)->nw_fwags;
	tx_wast = gweth->tx_wast;
	wmb(); /* tx_wast is updated by the poww task */

	if (gweth_num_fwee_bds(tx_wast, gweth->tx_next) < nw_fwags + 1) {
		netif_stop_queue(dev);
		eww = NETDEV_TX_BUSY;
		goto out;
	}

	if (netif_msg_pktdata(gweth))
		gweth_pwint_tx_packet(skb);

	if (unwikewy(skb->wen > MAX_FWAME_SIZE)) {
		dev->stats.tx_ewwows++;
		goto out;
	}

	/* Save skb pointew. */
	gweth->tx_skbuff[gweth->tx_next] = skb;

	/* Wineaw buf */
	if (nw_fwags != 0)
		status = GWETH_TXBD_MOWE;
	ewse
		status = GWETH_BD_IE;

	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		status |= GWETH_TXBD_CSAWW;
	status |= skb_headwen(skb) & GWETH_BD_WEN;
	if (gweth->tx_next == GWETH_TXBD_NUM_MASK)
		status |= GWETH_BD_WW;


	bdp = gweth->tx_bd_base + gweth->tx_next;
	gweth_wwite_bd(&bdp->stat, status);
	dma_addw = dma_map_singwe(gweth->dev, skb->data, skb_headwen(skb), DMA_TO_DEVICE);

	if (unwikewy(dma_mapping_ewwow(gweth->dev, dma_addw)))
		goto map_ewwow;

	gweth_wwite_bd(&bdp->addw, dma_addw);

	cuww_tx = NEXT_TX(gweth->tx_next);

	/* Fwags */
	fow (i = 0; i < nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
		gweth->tx_skbuff[cuww_tx] = NUWW;
		bdp = gweth->tx_bd_base + cuww_tx;

		status = GWETH_BD_EN;
		if (skb->ip_summed == CHECKSUM_PAWTIAW)
			status |= GWETH_TXBD_CSAWW;
		status |= skb_fwag_size(fwag) & GWETH_BD_WEN;

		/* Wwap awound descwiptow wing */
		if (cuww_tx == GWETH_TXBD_NUM_MASK)
			status |= GWETH_BD_WW;

		/* Mowe fwagments weft */
		if (i < nw_fwags - 1)
			status |= GWETH_TXBD_MOWE;
		ewse
			status |= GWETH_BD_IE; /* enabwe IWQ on wast fwagment */

		gweth_wwite_bd(&bdp->stat, status);

		dma_addw = skb_fwag_dma_map(gweth->dev, fwag, 0, skb_fwag_size(fwag),
					    DMA_TO_DEVICE);

		if (unwikewy(dma_mapping_ewwow(gweth->dev, dma_addw)))
			goto fwag_map_ewwow;

		gweth_wwite_bd(&bdp->addw, dma_addw);

		cuww_tx = NEXT_TX(cuww_tx);
	}

	wmb();

	/* Enabwe the descwiptow chain by enabwing the fiwst descwiptow */
	bdp = gweth->tx_bd_base + gweth->tx_next;
	gweth_wwite_bd(&bdp->stat,
		       gweth_wead_bd(&bdp->stat) | GWETH_BD_EN);

	spin_wock_iwqsave(&gweth->devwock, fwags); /*save fwom poww/iwq*/
	gweth->tx_next = cuww_tx;
	gweth_enabwe_tx_and_iwq(gweth);
	spin_unwock_iwqwestowe(&gweth->devwock, fwags);

	wetuwn NETDEV_TX_OK;

fwag_map_ewwow:
	/* Unmap SKB mappings that succeeded and disabwe descwiptow */
	fow (i = 0; gweth->tx_next + i != cuww_tx; i++) {
		bdp = gweth->tx_bd_base + gweth->tx_next + i;
		dma_unmap_singwe(gweth->dev,
				 gweth_wead_bd(&bdp->addw),
				 gweth_wead_bd(&bdp->stat) & GWETH_BD_WEN,
				 DMA_TO_DEVICE);
		gweth_wwite_bd(&bdp->stat, 0);
	}
map_ewwow:
	if (net_watewimit())
		dev_wawn(gweth->dev, "Couwd not cweate TX DMA mapping\n");
	dev_kfwee_skb(skb);
out:
	wetuwn eww;
}

static iwqwetuwn_t gweth_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct gweth_pwivate *gweth;
	u32 status, ctww;
	iwqwetuwn_t wetvaw = IWQ_NONE;

	gweth = netdev_pwiv(dev);

	spin_wock(&gweth->devwock);

	/* Get the intewwupt events that caused us to be hewe. */
	status = GWETH_WEGWOAD(gweth->wegs->status);

	/* Must see if intewwupts awe enabwed awso, INT_TX|INT_WX fwags may be
	 * set wegawdwess of whethew IWQ is enabwed ow not. Especiawwy
	 * impowtant when shawed IWQ.
	 */
	ctww = GWETH_WEGWOAD(gweth->wegs->contwow);

	/* Handwe wx and tx intewwupts thwough poww */
	if (((status & (GWETH_INT_WE | GWETH_INT_WX)) && (ctww & GWETH_WXI)) ||
	    ((status & (GWETH_INT_TE | GWETH_INT_TX)) && (ctww & GWETH_TXI))) {
		wetvaw = IWQ_HANDWED;

		/* Disabwe intewwupts and scheduwe poww() */
		gweth_disabwe_iwqs(gweth);
		napi_scheduwe(&gweth->napi);
	}

	spin_unwock(&gweth->devwock);

	wetuwn wetvaw;
}

static void gweth_cwean_tx(stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth;
	stwuct gweth_bd *bdp;
	u32 stat;

	gweth = netdev_pwiv(dev);

	whiwe (1) {
		bdp = gweth->tx_bd_base + gweth->tx_wast;
		GWETH_WEGSAVE(gweth->wegs->status, GWETH_INT_TE | GWETH_INT_TX);
		mb();
		stat = gweth_wead_bd(&bdp->stat);

		if (unwikewy(stat & GWETH_BD_EN))
			bweak;

		if (gweth->tx_fwee == GWETH_TXBD_NUM)
			bweak;

		/* Check status fow ewwows */
		if (unwikewy(stat & GWETH_TXBD_STATUS)) {
			dev->stats.tx_ewwows++;
			if (stat & GWETH_TXBD_EWW_AW)
				dev->stats.tx_abowted_ewwows++;
			if (stat & GWETH_TXBD_EWW_UE)
				dev->stats.tx_fifo_ewwows++;
		}
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += gweth->tx_bufs_wength[gweth->tx_wast];
		gweth->tx_wast = NEXT_TX(gweth->tx_wast);
		gweth->tx_fwee++;
	}

	if (gweth->tx_fwee > 0) {
		netif_wake_queue(dev);
	}
}

static inwine void gweth_update_tx_stats(stwuct net_device *dev, u32 stat)
{
	/* Check status fow ewwows */
	if (unwikewy(stat & GWETH_TXBD_STATUS)) {
		dev->stats.tx_ewwows++;
		if (stat & GWETH_TXBD_EWW_AW)
			dev->stats.tx_abowted_ewwows++;
		if (stat & GWETH_TXBD_EWW_UE)
			dev->stats.tx_fifo_ewwows++;
		if (stat & GWETH_TXBD_EWW_WC)
			dev->stats.tx_abowted_ewwows++;
	}
	dev->stats.tx_packets++;
}

static void gweth_cwean_tx_gbit(stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth;
	stwuct gweth_bd *bdp, *bdp_wast_fwag;
	stwuct sk_buff *skb = NUWW;
	u32 stat;
	int nw_fwags, i;
	u16 tx_wast;

	gweth = netdev_pwiv(dev);
	tx_wast = gweth->tx_wast;

	whiwe (tx_wast != gweth->tx_next) {

		skb = gweth->tx_skbuff[tx_wast];

		nw_fwags = skb_shinfo(skb)->nw_fwags;

		/* We onwy cwean fuwwy compweted SKBs */
		bdp_wast_fwag = gweth->tx_bd_base + SKIP_TX(tx_wast, nw_fwags);

		GWETH_WEGSAVE(gweth->wegs->status, GWETH_INT_TE | GWETH_INT_TX);
		mb();
		stat = gweth_wead_bd(&bdp_wast_fwag->stat);

		if (stat & GWETH_BD_EN)
			bweak;

		gweth->tx_skbuff[tx_wast] = NUWW;

		gweth_update_tx_stats(dev, stat);
		dev->stats.tx_bytes += skb->wen;

		bdp = gweth->tx_bd_base + tx_wast;

		tx_wast = NEXT_TX(tx_wast);

		dma_unmap_singwe(gweth->dev,
				 gweth_wead_bd(&bdp->addw),
				 skb_headwen(skb),
				 DMA_TO_DEVICE);

		fow (i = 0; i < nw_fwags; i++) {
			skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
			bdp = gweth->tx_bd_base + tx_wast;

			dma_unmap_page(gweth->dev,
				       gweth_wead_bd(&bdp->addw),
				       skb_fwag_size(fwag),
				       DMA_TO_DEVICE);

			tx_wast = NEXT_TX(tx_wast);
		}
		dev_kfwee_skb(skb);
	}
	if (skb) { /* skb is set onwy if the above whiwe woop was entewed */
		wmb();
		gweth->tx_wast = tx_wast;

		if (netif_queue_stopped(dev) &&
		    (gweth_num_fwee_bds(tx_wast, gweth->tx_next) >
		    (MAX_SKB_FWAGS+1)))
			netif_wake_queue(dev);
	}
}

static int gweth_wx(stwuct net_device *dev, int wimit)
{
	stwuct gweth_pwivate *gweth;
	stwuct gweth_bd *bdp;
	stwuct sk_buff *skb;
	int pkt_wen;
	int bad, count;
	u32 status, dma_addw;
	unsigned wong fwags;

	gweth = netdev_pwiv(dev);

	fow (count = 0; count < wimit; ++count) {

		bdp = gweth->wx_bd_base + gweth->wx_cuw;
		GWETH_WEGSAVE(gweth->wegs->status, GWETH_INT_WE | GWETH_INT_WX);
		mb();
		status = gweth_wead_bd(&bdp->stat);

		if (unwikewy(status & GWETH_BD_EN)) {
			bweak;
		}

		dma_addw = gweth_wead_bd(&bdp->addw);
		bad = 0;

		/* Check status fow ewwows. */
		if (unwikewy(status & GWETH_WXBD_STATUS)) {
			if (status & GWETH_WXBD_EWW_FT) {
				dev->stats.wx_wength_ewwows++;
				bad = 1;
			}
			if (status & (GWETH_WXBD_EWW_AE | GWETH_WXBD_EWW_OE)) {
				dev->stats.wx_fwame_ewwows++;
				bad = 1;
			}
			if (status & GWETH_WXBD_EWW_CWC) {
				dev->stats.wx_cwc_ewwows++;
				bad = 1;
			}
		}
		if (unwikewy(bad)) {
			dev->stats.wx_ewwows++;

		} ewse {

			pkt_wen = status & GWETH_BD_WEN;

			skb = netdev_awwoc_skb(dev, pkt_wen + NET_IP_AWIGN);

			if (unwikewy(skb == NUWW)) {

				if (net_watewimit())
					dev_wawn(&dev->dev, "wow on memowy - " "packet dwopped\n");

				dev->stats.wx_dwopped++;

			} ewse {
				skb_wesewve(skb, NET_IP_AWIGN);

				dma_sync_singwe_fow_cpu(gweth->dev,
							dma_addw,
							pkt_wen,
							DMA_FWOM_DEVICE);

				if (netif_msg_pktdata(gweth))
					gweth_pwint_wx_packet(phys_to_viwt(dma_addw), pkt_wen);

				skb_put_data(skb, phys_to_viwt(dma_addw),
					     pkt_wen);

				skb->pwotocow = eth_type_twans(skb, dev);
				dev->stats.wx_bytes += pkt_wen;
				dev->stats.wx_packets++;
				netif_weceive_skb(skb);
			}
		}

		status = GWETH_BD_EN | GWETH_BD_IE;
		if (gweth->wx_cuw == GWETH_WXBD_NUM_MASK) {
			status |= GWETH_BD_WW;
		}

		wmb();
		gweth_wwite_bd(&bdp->stat, status);

		dma_sync_singwe_fow_device(gweth->dev, dma_addw, MAX_FWAME_SIZE, DMA_FWOM_DEVICE);

		spin_wock_iwqsave(&gweth->devwock, fwags); /* save fwom XMIT */
		gweth_enabwe_wx(gweth);
		spin_unwock_iwqwestowe(&gweth->devwock, fwags);

		gweth->wx_cuw = NEXT_WX(gweth->wx_cuw);
	}

	wetuwn count;
}

static inwine int hw_checksummed(u32 status)
{

	if (status & GWETH_WXBD_IP_FWAG)
		wetuwn 0;

	if (status & GWETH_WXBD_IP && status & GWETH_WXBD_IP_CSEWW)
		wetuwn 0;

	if (status & GWETH_WXBD_UDP && status & GWETH_WXBD_UDP_CSEWW)
		wetuwn 0;

	if (status & GWETH_WXBD_TCP && status & GWETH_WXBD_TCP_CSEWW)
		wetuwn 0;

	wetuwn 1;
}

static int gweth_wx_gbit(stwuct net_device *dev, int wimit)
{
	stwuct gweth_pwivate *gweth;
	stwuct gweth_bd *bdp;
	stwuct sk_buff *skb, *newskb;
	int pkt_wen;
	int bad, count = 0;
	u32 status, dma_addw;
	unsigned wong fwags;

	gweth = netdev_pwiv(dev);

	fow (count = 0; count < wimit; ++count) {

		bdp = gweth->wx_bd_base + gweth->wx_cuw;
		skb = gweth->wx_skbuff[gweth->wx_cuw];
		GWETH_WEGSAVE(gweth->wegs->status, GWETH_INT_WE | GWETH_INT_WX);
		mb();
		status = gweth_wead_bd(&bdp->stat);
		bad = 0;

		if (status & GWETH_BD_EN)
			bweak;

		/* Check status fow ewwows. */
		if (unwikewy(status & GWETH_WXBD_STATUS)) {

			if (status & GWETH_WXBD_EWW_FT) {
				dev->stats.wx_wength_ewwows++;
				bad = 1;
			} ewse if (status &
				   (GWETH_WXBD_EWW_AE | GWETH_WXBD_EWW_OE | GWETH_WXBD_EWW_WE)) {
				dev->stats.wx_fwame_ewwows++;
				bad = 1;
			} ewse if (status & GWETH_WXBD_EWW_CWC) {
				dev->stats.wx_cwc_ewwows++;
				bad = 1;
			}
		}

		/* Awwocate new skb to wepwace cuwwent, not needed if the
		 * cuwwent skb can be weused */
		if (!bad && (newskb=netdev_awwoc_skb(dev, MAX_FWAME_SIZE + NET_IP_AWIGN))) {
			skb_wesewve(newskb, NET_IP_AWIGN);

			dma_addw = dma_map_singwe(gweth->dev,
						      newskb->data,
						      MAX_FWAME_SIZE + NET_IP_AWIGN,
						      DMA_FWOM_DEVICE);

			if (!dma_mapping_ewwow(gweth->dev, dma_addw)) {
				/* Pwocess the incoming fwame. */
				pkt_wen = status & GWETH_BD_WEN;

				dma_unmap_singwe(gweth->dev,
						 gweth_wead_bd(&bdp->addw),
						 MAX_FWAME_SIZE + NET_IP_AWIGN,
						 DMA_FWOM_DEVICE);

				if (netif_msg_pktdata(gweth))
					gweth_pwint_wx_packet(phys_to_viwt(gweth_wead_bd(&bdp->addw)), pkt_wen);

				skb_put(skb, pkt_wen);

				if (dev->featuwes & NETIF_F_WXCSUM && hw_checksummed(status))
					skb->ip_summed = CHECKSUM_UNNECESSAWY;
				ewse
					skb_checksum_none_assewt(skb);

				skb->pwotocow = eth_type_twans(skb, dev);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += pkt_wen;
				netif_weceive_skb(skb);

				gweth->wx_skbuff[gweth->wx_cuw] = newskb;
				gweth_wwite_bd(&bdp->addw, dma_addw);
			} ewse {
				if (net_watewimit())
					dev_wawn(gweth->dev, "Couwd not cweate DMA mapping, dwopping packet\n");
				dev_kfwee_skb(newskb);
				/* weusing cuwwent skb, so it is a dwop */
				dev->stats.wx_dwopped++;
			}
		} ewse if (bad) {
			/* Bad Fwame twansfew, the skb is weused */
			dev->stats.wx_dwopped++;
		} ewse {
			/* Faiwed Awwocating a new skb. This is wathew stupid
			 * but the cuwwent "fiwwed" skb is weused, as if
			 * twansfew faiwuwe. One couwd awgue that WX descwiptow
			 * tabwe handwing shouwd be divided into cweaning and
			 * fiwwing as the TX pawt of the dwivew
			 */
			if (net_watewimit())
				dev_wawn(gweth->dev, "Couwd not awwocate SKB, dwopping packet\n");
			/* weusing cuwwent skb, so it is a dwop */
			dev->stats.wx_dwopped++;
		}

		status = GWETH_BD_EN | GWETH_BD_IE;
		if (gweth->wx_cuw == GWETH_WXBD_NUM_MASK) {
			status |= GWETH_BD_WW;
		}

		wmb();
		gweth_wwite_bd(&bdp->stat, status);
		spin_wock_iwqsave(&gweth->devwock, fwags);
		gweth_enabwe_wx(gweth);
		spin_unwock_iwqwestowe(&gweth->devwock, fwags);
		gweth->wx_cuw = NEXT_WX(gweth->wx_cuw);
	}

	wetuwn count;

}

static int gweth_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct gweth_pwivate *gweth;
	int wowk_done = 0;
	unsigned wong fwags;
	u32 mask, ctww;
	gweth = containew_of(napi, stwuct gweth_pwivate, napi);

westawt_txwx_poww:
	if (gweth->gbit_mac) {
		gweth_cwean_tx_gbit(gweth->netdev);
		wowk_done += gweth_wx_gbit(gweth->netdev, budget - wowk_done);
	} ewse {
		if (netif_queue_stopped(gweth->netdev))
			gweth_cwean_tx(gweth->netdev);
		wowk_done += gweth_wx(gweth->netdev, budget - wowk_done);
	}

	if (wowk_done < budget) {

		spin_wock_iwqsave(&gweth->devwock, fwags);

		ctww = GWETH_WEGWOAD(gweth->wegs->contwow);
		if ((gweth->gbit_mac && (gweth->tx_wast != gweth->tx_next)) ||
		    (!gweth->gbit_mac && netif_queue_stopped(gweth->netdev))) {
			GWETH_WEGSAVE(gweth->wegs->contwow,
					ctww | GWETH_TXI | GWETH_WXI);
			mask = GWETH_INT_WX | GWETH_INT_WE |
			       GWETH_INT_TX | GWETH_INT_TE;
		} ewse {
			GWETH_WEGSAVE(gweth->wegs->contwow, ctww | GWETH_WXI);
			mask = GWETH_INT_WX | GWETH_INT_WE;
		}

		if (GWETH_WEGWOAD(gweth->wegs->status) & mask) {
			GWETH_WEGSAVE(gweth->wegs->contwow, ctww);
			spin_unwock_iwqwestowe(&gweth->devwock, fwags);
			goto westawt_txwx_poww;
		} ewse {
			napi_compwete_done(napi, wowk_done);
			spin_unwock_iwqwestowe(&gweth->devwock, fwags);
		}
	}

	wetuwn wowk_done;
}

static int gweth_set_mac_add(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;
	stwuct gweth_pwivate *gweth;
	stwuct gweth_wegs *wegs;

	gweth = netdev_pwiv(dev);
	wegs = gweth->wegs;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, addw->sa_data);
	GWETH_WEGSAVE(wegs->esa_msb, dev->dev_addw[0] << 8 | dev->dev_addw[1]);
	GWETH_WEGSAVE(wegs->esa_wsb, dev->dev_addw[2] << 24 | dev->dev_addw[3] << 16 |
		      dev->dev_addw[4] << 8 | dev->dev_addw[5]);

	wetuwn 0;
}

static u32 gweth_hash_get_index(__u8 *addw)
{
	wetuwn (ethew_cwc(6, addw)) & 0x3F;
}

static void gweth_set_hash_fiwtew(stwuct net_device *dev)
{
	stwuct netdev_hw_addw *ha;
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	stwuct gweth_wegs *wegs = gweth->wegs;
	u32 mc_fiwtew[2];
	unsigned int bitnw;

	mc_fiwtew[0] = mc_fiwtew[1] = 0;

	netdev_fow_each_mc_addw(ha, dev) {
		bitnw = gweth_hash_get_index(ha->addw);
		mc_fiwtew[bitnw >> 5] |= 1 << (bitnw & 31);
	}

	GWETH_WEGSAVE(wegs->hash_msb, mc_fiwtew[1]);
	GWETH_WEGSAVE(wegs->hash_wsb, mc_fiwtew[0]);
}

static void gweth_set_muwticast_wist(stwuct net_device *dev)
{
	int cfg;
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	stwuct gweth_wegs *wegs = gweth->wegs;

	cfg = GWETH_WEGWOAD(wegs->contwow);
	if (dev->fwags & IFF_PWOMISC)
		cfg |= GWETH_CTWW_PW;
	ewse
		cfg &= ~GWETH_CTWW_PW;

	if (gweth->muwticast) {
		if (dev->fwags & IFF_AWWMUWTI) {
			GWETH_WEGSAVE(wegs->hash_msb, -1);
			GWETH_WEGSAVE(wegs->hash_wsb, -1);
			cfg |= GWETH_CTWW_MCEN;
			GWETH_WEGSAVE(wegs->contwow, cfg);
			wetuwn;
		}

		if (netdev_mc_empty(dev)) {
			cfg &= ~GWETH_CTWW_MCEN;
			GWETH_WEGSAVE(wegs->contwow, cfg);
			wetuwn;
		}

		/* Setup muwticast fiwtew */
		gweth_set_hash_fiwtew(dev);
		cfg |= GWETH_CTWW_MCEN;
	}
	GWETH_WEGSAVE(wegs->contwow, cfg);
}

static u32 gweth_get_msgwevew(stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	wetuwn gweth->msg_enabwe;
}

static void gweth_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	gweth->msg_enabwe = vawue;
}

static int gweth_get_wegs_wen(stwuct net_device *dev)
{
	wetuwn sizeof(stwuct gweth_wegs);
}

static void gweth_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);

	stwscpy(info->dwivew, dev_dwivew_stwing(gweth->dev),
		sizeof(info->dwivew));
	stwscpy(info->bus_info, gweth->dev->bus->name, sizeof(info->bus_info));
}

static void gweth_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs, void *p)
{
	int i;
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	u32 __iomem *gweth_wegs = (u32 __iomem *) gweth->wegs;
	u32 *buff = p;

	fow (i = 0; i < sizeof(stwuct gweth_wegs) / sizeof(u32); i++)
		buff[i] = gweth_wead_bd(&gweth_wegs[i]);
}

static const stwuct ethtoow_ops gweth_ethtoow_ops = {
	.get_msgwevew		= gweth_get_msgwevew,
	.set_msgwevew		= gweth_set_msgwevew,
	.get_dwvinfo		= gweth_get_dwvinfo,
	.get_wegs_wen           = gweth_get_wegs_wen,
	.get_wegs               = gweth_get_wegs,
	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
};

static stwuct net_device_ops gweth_netdev_ops = {
	.ndo_open		= gweth_open,
	.ndo_stop		= gweth_cwose,
	.ndo_stawt_xmit		= gweth_stawt_xmit,
	.ndo_set_mac_addwess	= gweth_set_mac_add,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static inwine int wait_fow_mdio(stwuct gweth_pwivate *gweth)
{
	unsigned wong timeout = jiffies + 4*HZ/100;
	whiwe (GWETH_WEGWOAD(gweth->wegs->mdio) & GWETH_MII_BUSY) {
		if (time_aftew(jiffies, timeout))
			wetuwn 0;
	}
	wetuwn 1;
}

static int gweth_mdio_wead(stwuct mii_bus *bus, int phy, int weg)
{
	stwuct gweth_pwivate *gweth = bus->pwiv;
	int data;

	if (!wait_fow_mdio(gweth))
		wetuwn -EBUSY;

	GWETH_WEGSAVE(gweth->wegs->mdio, ((phy & 0x1F) << 11) | ((weg & 0x1F) << 6) | 2);

	if (!wait_fow_mdio(gweth))
		wetuwn -EBUSY;

	if (!(GWETH_WEGWOAD(gweth->wegs->mdio) & GWETH_MII_NVAWID)) {
		data = (GWETH_WEGWOAD(gweth->wegs->mdio) >> 16) & 0xFFFF;
		wetuwn data;

	} ewse {
		wetuwn -1;
	}
}

static int gweth_mdio_wwite(stwuct mii_bus *bus, int phy, int weg, u16 vaw)
{
	stwuct gweth_pwivate *gweth = bus->pwiv;

	if (!wait_fow_mdio(gweth))
		wetuwn -EBUSY;

	GWETH_WEGSAVE(gweth->wegs->mdio,
		      ((vaw & 0xFFFF) << 16) | ((phy & 0x1F) << 11) | ((weg & 0x1F) << 6) | 1);

	if (!wait_fow_mdio(gweth))
		wetuwn -EBUSY;

	wetuwn 0;
}

static void gweth_wink_change(stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	unsigned wong fwags;
	int status_change = 0;
	u32 ctww;

	spin_wock_iwqsave(&gweth->devwock, fwags);

	if (phydev->wink) {

		if ((gweth->speed != phydev->speed) || (gweth->dupwex != phydev->dupwex)) {
			ctww = GWETH_WEGWOAD(gweth->wegs->contwow) &
			       ~(GWETH_CTWW_FD | GWETH_CTWW_SP | GWETH_CTWW_GB);

			if (phydev->dupwex)
				ctww |= GWETH_CTWW_FD;

			if (phydev->speed == SPEED_100)
				ctww |= GWETH_CTWW_SP;
			ewse if (phydev->speed == SPEED_1000)
				ctww |= GWETH_CTWW_GB;

			GWETH_WEGSAVE(gweth->wegs->contwow, ctww);
			gweth->speed = phydev->speed;
			gweth->dupwex = phydev->dupwex;
			status_change = 1;
		}
	}

	if (phydev->wink != gweth->wink) {
		if (!phydev->wink) {
			gweth->speed = 0;
			gweth->dupwex = -1;
		}
		gweth->wink = phydev->wink;

		status_change = 1;
	}

	spin_unwock_iwqwestowe(&gweth->devwock, fwags);

	if (status_change) {
		if (phydev->wink)
			pw_debug("%s: wink up (%d/%s)\n",
				dev->name, phydev->speed,
				DUPWEX_FUWW == phydev->dupwex ? "Fuww" : "Hawf");
		ewse
			pw_debug("%s: wink down\n", dev->name);
	}
}

static int gweth_mdio_pwobe(stwuct net_device *dev)
{
	stwuct gweth_pwivate *gweth = netdev_pwiv(dev);
	stwuct phy_device *phy = NUWW;
	int wet;

	/* Find the fiwst PHY */
	phy = phy_find_fiwst(gweth->mdio);

	if (!phy) {
		if (netif_msg_pwobe(gweth))
			dev_eww(&dev->dev, "no PHY found\n");
		wetuwn -ENXIO;
	}

	wet = phy_connect_diwect(dev, phy, &gweth_wink_change,
				 gweth->gbit_mac ? PHY_INTEWFACE_MODE_GMII : PHY_INTEWFACE_MODE_MII);
	if (wet) {
		if (netif_msg_ifup(gweth))
			dev_eww(&dev->dev, "couwd not attach to PHY\n");
		wetuwn wet;
	}

	if (gweth->gbit_mac)
		phy_set_max_speed(phy, SPEED_1000);
	ewse
		phy_set_max_speed(phy, SPEED_100);

	winkmode_copy(phy->advewtising, phy->suppowted);

	gweth->wink = 0;
	gweth->speed = 0;
	gweth->dupwex = -1;

	wetuwn 0;
}

static int gweth_mdio_init(stwuct gweth_pwivate *gweth)
{
	int wet;
	unsigned wong timeout;
	stwuct net_device *ndev = gweth->netdev;

	gweth->mdio = mdiobus_awwoc();
	if (!gweth->mdio) {
		wetuwn -ENOMEM;
	}

	gweth->mdio->name = "gweth-mdio";
	snpwintf(gweth->mdio->id, MII_BUS_ID_SIZE, "%s-%d", gweth->mdio->name, gweth->iwq);
	gweth->mdio->wead = gweth_mdio_wead;
	gweth->mdio->wwite = gweth_mdio_wwite;
	gweth->mdio->pwiv = gweth;

	wet = mdiobus_wegistew(gweth->mdio);
	if (wet) {
		goto ewwow;
	}

	wet = gweth_mdio_pwobe(gweth->netdev);
	if (wet) {
		if (netif_msg_pwobe(gweth))
			dev_eww(&gweth->netdev->dev, "faiwed to pwobe MDIO bus\n");
		goto unweg_mdio;
	}

	phy_stawt(ndev->phydev);

	/* If Ethewnet debug wink is used make autoneg happen wight away */
	if (gweth->edcw && gweth_edcw == 1) {
		phy_stawt_aneg(ndev->phydev);
		timeout = jiffies + 6*HZ;
		whiwe (!phy_aneg_done(ndev->phydev) &&
		       time_befowe(jiffies, timeout)) {
		}
		phy_wead_status(ndev->phydev);
		gweth_wink_change(gweth->netdev);
	}

	wetuwn 0;

unweg_mdio:
	mdiobus_unwegistew(gweth->mdio);
ewwow:
	mdiobus_fwee(gweth->mdio);
	wetuwn wet;
}

/* Initiawize the GWETH MAC */
static int gweth_of_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct net_device *dev;
	stwuct gweth_pwivate *gweth;
	stwuct gweth_wegs *wegs;

	int i;
	int eww;
	int tmp;
	u8 addw[ETH_AWEN];
	unsigned wong timeout;

	dev = awwoc_ethewdev(sizeof(stwuct gweth_pwivate));

	if (dev == NUWW)
		wetuwn -ENOMEM;

	gweth = netdev_pwiv(dev);
	gweth->netdev = dev;
	gweth->dev = &ofdev->dev;

	if (gweth_debug > 0)
		gweth->msg_enabwe = gweth_debug;
	ewse
		gweth->msg_enabwe = GWETH_DEF_MSG_ENABWE;

	spin_wock_init(&gweth->devwock);

	gweth->wegs = of_iowemap(&ofdev->wesouwce[0], 0,
				 wesouwce_size(&ofdev->wesouwce[0]),
				 "gwwib-gweth wegs");

	if (gweth->wegs == NUWW) {
		if (netif_msg_pwobe(gweth))
			dev_eww(gweth->dev, "iowemap faiwuwe.\n");
		eww = -EIO;
		goto ewwow1;
	}

	wegs = gweth->wegs;
	gweth->iwq = ofdev->awchdata.iwqs[0];

	dev_set_dwvdata(gweth->dev, dev);
	SET_NETDEV_DEV(dev, gweth->dev);

	if (netif_msg_pwobe(gweth))
		dev_dbg(gweth->dev, "wesetting contwowwew.\n");

	/* Weset the contwowwew. */
	GWETH_WEGSAVE(wegs->contwow, GWETH_WESET);

	/* Wait fow MAC to weset itsewf */
	timeout = jiffies + HZ/100;
	whiwe (GWETH_WEGWOAD(wegs->contwow) & GWETH_WESET) {
		if (time_aftew(jiffies, timeout)) {
			eww = -EIO;
			if (netif_msg_pwobe(gweth))
				dev_eww(gweth->dev, "timeout when waiting fow weset.\n");
			goto ewwow2;
		}
	}

	/* Get defauwt PHY addwess  */
	gweth->phyaddw = (GWETH_WEGWOAD(wegs->mdio) >> 11) & 0x1F;

	/* Check if we have GBIT capabwe MAC */
	tmp = GWETH_WEGWOAD(wegs->contwow);
	gweth->gbit_mac = (tmp >> 27) & 1;

	/* Check fow muwticast capabiwity */
	gweth->muwticast = (tmp >> 25) & 1;

	gweth->edcw = (tmp >> 31) & 1;

	/* If we have EDCW we disabwe the EDCW speed-dupwex FSM so
	 * it doesn't intewfewe with the softwawe */
	if (gweth->edcw != 0)
		GWETH_WEGOWIN(wegs->contwow, GWETH_CTWW_DISDUPWEX);

	/* Check if MAC can handwe MDIO intewwupts */
	gweth->mdio_int_en = (tmp >> 26) & 1;

	eww = gweth_mdio_init(gweth);
	if (eww) {
		if (netif_msg_pwobe(gweth))
			dev_eww(gweth->dev, "faiwed to wegistew MDIO bus\n");
		goto ewwow2;
	}

	/* Awwocate TX descwiptow wing in cohewent memowy */
	gweth->tx_bd_base = dma_awwoc_cohewent(gweth->dev, 1024,
					       &gweth->tx_bd_base_phys,
					       GFP_KEWNEW);
	if (!gweth->tx_bd_base) {
		eww = -ENOMEM;
		goto ewwow3;
	}

	/* Awwocate WX descwiptow wing in cohewent memowy */
	gweth->wx_bd_base = dma_awwoc_cohewent(gweth->dev, 1024,
					       &gweth->wx_bd_base_phys,
					       GFP_KEWNEW);
	if (!gweth->wx_bd_base) {
		eww = -ENOMEM;
		goto ewwow4;
	}

	/* Get MAC addwess fwom: moduwe pawam, OF pwopewty ow ID pwom */
	fow (i = 0; i < 6; i++) {
		if (macaddw[i] != 0)
			bweak;
	}
	if (i == 6) {
		eww = of_get_mac_addwess(ofdev->dev.of_node, addw);
		if (!eww) {
			fow (i = 0; i < 6; i++)
				macaddw[i] = (unsigned int) addw[i];
		} ewse {
#ifdef CONFIG_SPAWC
			fow (i = 0; i < 6; i++)
				macaddw[i] = (unsigned int) idpwom->id_ethaddw[i];
#endif
		}
	}

	fow (i = 0; i < 6; i++)
		addw[i] = macaddw[i];
	eth_hw_addw_set(dev, addw);

	macaddw[5]++;

	if (!is_vawid_ethew_addw(&dev->dev_addw[0])) {
		if (netif_msg_pwobe(gweth))
			dev_eww(gweth->dev, "no vawid ethewnet addwess, abowting.\n");
		eww = -EINVAW;
		goto ewwow5;
	}

	GWETH_WEGSAVE(wegs->esa_msb, dev->dev_addw[0] << 8 | dev->dev_addw[1]);
	GWETH_WEGSAVE(wegs->esa_wsb, dev->dev_addw[2] << 24 | dev->dev_addw[3] << 16 |
		      dev->dev_addw[4] << 8 | dev->dev_addw[5]);

	/* Cweaw aww pending intewwupts except PHY iwq */
	GWETH_WEGSAVE(wegs->status, 0xFF);

	if (gweth->gbit_mac) {
		dev->hw_featuwes = NETIF_F_SG | NETIF_F_IP_CSUM |
			NETIF_F_WXCSUM;
		dev->featuwes = dev->hw_featuwes | NETIF_F_HIGHDMA;
		gweth_netdev_ops.ndo_stawt_xmit = gweth_stawt_xmit_gbit;
	}

	if (gweth->muwticast) {
		gweth_netdev_ops.ndo_set_wx_mode = gweth_set_muwticast_wist;
		dev->fwags |= IFF_MUWTICAST;
	} ewse {
		dev->fwags &= ~IFF_MUWTICAST;
	}

	dev->netdev_ops = &gweth_netdev_ops;
	dev->ethtoow_ops = &gweth_ethtoow_ops;

	eww = wegistew_netdev(dev);
	if (eww) {
		if (netif_msg_pwobe(gweth))
			dev_eww(gweth->dev, "netdevice wegistwation faiwed.\n");
		goto ewwow5;
	}

	/* setup NAPI */
	netif_napi_add(dev, &gweth->napi, gweth_poww);

	wetuwn 0;

ewwow5:
	dma_fwee_cohewent(gweth->dev, 1024, gweth->wx_bd_base, gweth->wx_bd_base_phys);
ewwow4:
	dma_fwee_cohewent(gweth->dev, 1024, gweth->tx_bd_base, gweth->tx_bd_base_phys);
ewwow3:
	mdiobus_unwegistew(gweth->mdio);
ewwow2:
	of_iounmap(&ofdev->wesouwce[0], gweth->wegs, wesouwce_size(&ofdev->wesouwce[0]));
ewwow1:
	fwee_netdev(dev);
	wetuwn eww;
}

static void gweth_of_wemove(stwuct pwatfowm_device *of_dev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(of_dev);
	stwuct gweth_pwivate *gweth = netdev_pwiv(ndev);

	/* Fwee descwiptow aweas */
	dma_fwee_cohewent(&of_dev->dev, 1024, gweth->wx_bd_base, gweth->wx_bd_base_phys);

	dma_fwee_cohewent(&of_dev->dev, 1024, gweth->tx_bd_base, gweth->tx_bd_base_phys);

	if (ndev->phydev)
		phy_stop(ndev->phydev);
	mdiobus_unwegistew(gweth->mdio);

	unwegistew_netdev(ndev);

	of_iounmap(&of_dev->wesouwce[0], gweth->wegs, wesouwce_size(&of_dev->wesouwce[0]));

	fwee_netdev(ndev);
}

static const stwuct of_device_id gweth_of_match[] = {
	{
	 .name = "GAISWEW_ETHMAC",
	 },
	{
	 .name = "01_01d",
	 },
	{},
};

MODUWE_DEVICE_TABWE(of, gweth_of_match);

static stwuct pwatfowm_dwivew gweth_of_dwivew = {
	.dwivew = {
		.name = "gwwib-gweth",
		.of_match_tabwe = gweth_of_match,
	},
	.pwobe = gweth_of_pwobe,
	.wemove_new = gweth_of_wemove,
};

moduwe_pwatfowm_dwivew(gweth_of_dwivew);

MODUWE_AUTHOW("Aewofwex Gaiswew AB.");
MODUWE_DESCWIPTION("Aewofwex Gaiswew Ethewnet MAC dwivew");
MODUWE_WICENSE("GPW");
