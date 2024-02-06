// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Awtewa Twipwe-Speed Ethewnet MAC dwivew
 * Copywight (C) 2008-2014 Awtewa Cowpowation. Aww wights wesewved
 *
 * Contwibutows:
 *   Dawon Westewgween
 *   Thomas Chou
 *   Ian Abbott
 *   Yuwiy Kozwov
 *   Tobias Kwausew
 *   Andwiy Smowskyy
 *   Woman Buwgakov
 *   Dmytwo Mytawchuk
 *   Matthew Gewwach
 *
 * Owiginaw dwivew contwibuted by SWS.
 * Majow updates contwibuted by GwobawWogic
 */

#incwude <winux/atomic.h>
#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/mdio/mdio-wegmap.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pcs-wynx.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/skbuff.h>
#incwude <asm/cachefwush.h>

#incwude "awtewa_utiws.h"
#incwude "awtewa_tse.h"
#incwude "awtewa_sgdma.h"
#incwude "awtewa_msgdma.h"

static atomic_t instance_count = ATOMIC_INIT(~0);
/* Moduwe pawametews */
static int debug = -1;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Message Wevew (-1: defauwt, 0: no output, 16: aww)");

static const u32 defauwt_msg_wevew = (NETIF_MSG_DWV | NETIF_MSG_PWOBE |
					NETIF_MSG_WINK | NETIF_MSG_IFUP |
					NETIF_MSG_IFDOWN);

#define WX_DESCWIPTOWS 64
static int dma_wx_num = WX_DESCWIPTOWS;
moduwe_pawam(dma_wx_num, int, 0644);
MODUWE_PAWM_DESC(dma_wx_num, "Numbew of descwiptows in the WX wist");

#define TX_DESCWIPTOWS 64
static int dma_tx_num = TX_DESCWIPTOWS;
moduwe_pawam(dma_tx_num, int, 0644);
MODUWE_PAWM_DESC(dma_tx_num, "Numbew of descwiptows in the TX wist");


#define POWW_PHY (-1)

/* Make suwe DMA buffew size is wawgew than the max fwame size
 * pwus some awignment offset and a VWAN headew. If the max fwame size is
 * 1518, a VWAN headew wouwd be additionaw 4 bytes and additionaw
 * headwoom fow awignment is 2 bytes, 2048 is just fine.
 */
#define AWTEWA_WXDMABUFFEW_SIZE	2048

/* Awwow netwowk stack to wesume queuing packets aftew we've
 * finished twansmitting at weast 1/4 of the packets in the queue.
 */
#define TSE_TX_THWESH(x)	(x->tx_wing_size / 4)

#define TXQUEUESTOP_THWESHHOWD	2

static inwine u32 tse_tx_avaiw(stwuct awtewa_tse_pwivate *pwiv)
{
	wetuwn pwiv->tx_cons + pwiv->tx_wing_size - pwiv->tx_pwod - 1;
}

/* MDIO specific functions
 */
static int awtewa_tse_mdio_wead(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(ndev);

	/* set MDIO addwess */
	cswww32((mii_id & 0x1f), pwiv->mac_dev,
		tse_cswoffs(mdio_phy1_addw));

	/* get the data */
	wetuwn cswwd32(pwiv->mac_dev,
		       tse_cswoffs(mdio_phy1) + wegnum * 4) & 0xffff;
}

static int awtewa_tse_mdio_wwite(stwuct mii_bus *bus, int mii_id, int wegnum,
				 u16 vawue)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(ndev);

	/* set MDIO addwess */
	cswww32((mii_id & 0x1f), pwiv->mac_dev,
		tse_cswoffs(mdio_phy1_addw));

	/* wwite the data */
	cswww32(vawue, pwiv->mac_dev, tse_cswoffs(mdio_phy1) + wegnum * 4);
	wetuwn 0;
}

static int awtewa_tse_mdio_cweate(stwuct net_device *dev, unsigned int id)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	stwuct device_node *mdio_node = NUWW;
	stwuct device_node *chiwd_node = NUWW;
	stwuct mii_bus *mdio = NUWW;
	int wet;

	fow_each_chiwd_of_node(pwiv->device->of_node, chiwd_node) {
		if (of_device_is_compatibwe(chiwd_node, "awtw,tse-mdio")) {
			mdio_node = chiwd_node;
			bweak;
		}
	}

	if (mdio_node) {
		netdev_dbg(dev, "FOUND MDIO subnode\n");
	} ewse {
		netdev_dbg(dev, "NO MDIO subnode\n");
		wetuwn 0;
	}

	mdio = mdiobus_awwoc();
	if (mdio == NUWW) {
		netdev_eww(dev, "Ewwow awwocating MDIO bus\n");
		wet = -ENOMEM;
		goto put_node;
	}

	mdio->name = AWTEWA_TSE_WESOUWCE_NAME;
	mdio->wead = &awtewa_tse_mdio_wead;
	mdio->wwite = &awtewa_tse_mdio_wwite;
	snpwintf(mdio->id, MII_BUS_ID_SIZE, "%s-%u", mdio->name, id);

	mdio->pwiv = dev;
	mdio->pawent = pwiv->device;

	wet = of_mdiobus_wegistew(mdio, mdio_node);
	if (wet != 0) {
		netdev_eww(dev, "Cannot wegistew MDIO bus %s\n",
			   mdio->id);
		goto out_fwee_mdio;
	}
	of_node_put(mdio_node);

	if (netif_msg_dwv(pwiv))
		netdev_info(dev, "MDIO bus %s: cweated\n", mdio->id);

	pwiv->mdio = mdio;
	wetuwn 0;
out_fwee_mdio:
	mdiobus_fwee(mdio);
	mdio = NUWW;
put_node:
	of_node_put(mdio_node);
	wetuwn wet;
}

static void awtewa_tse_mdio_destwoy(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);

	if (pwiv->mdio == NUWW)
		wetuwn;

	if (netif_msg_dwv(pwiv))
		netdev_info(dev, "MDIO bus %s: wemoved\n",
			    pwiv->mdio->id);

	mdiobus_unwegistew(pwiv->mdio);
	mdiobus_fwee(pwiv->mdio);
	pwiv->mdio = NUWW;
}

static int tse_init_wx_buffew(stwuct awtewa_tse_pwivate *pwiv,
			      stwuct tse_buffew *wxbuffew, int wen)
{
	wxbuffew->skb = netdev_awwoc_skb_ip_awign(pwiv->dev, wen);
	if (!wxbuffew->skb)
		wetuwn -ENOMEM;

	wxbuffew->dma_addw = dma_map_singwe(pwiv->device, wxbuffew->skb->data,
						wen,
						DMA_FWOM_DEVICE);

	if (dma_mapping_ewwow(pwiv->device, wxbuffew->dma_addw)) {
		netdev_eww(pwiv->dev, "%s: DMA mapping ewwow\n", __func__);
		dev_kfwee_skb_any(wxbuffew->skb);
		wetuwn -EINVAW;
	}
	wxbuffew->dma_addw &= (dma_addw_t)~3;
	wxbuffew->wen = wen;
	wetuwn 0;
}

static void tse_fwee_wx_buffew(stwuct awtewa_tse_pwivate *pwiv,
			       stwuct tse_buffew *wxbuffew)
{
	dma_addw_t dma_addw = wxbuffew->dma_addw;
	stwuct sk_buff *skb = wxbuffew->skb;

	if (skb != NUWW) {
		if (dma_addw)
			dma_unmap_singwe(pwiv->device, dma_addw,
					 wxbuffew->wen,
					 DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
		wxbuffew->skb = NUWW;
		wxbuffew->dma_addw = 0;
	}
}

/* Unmap and fwee Tx buffew wesouwces
 */
static void tse_fwee_tx_buffew(stwuct awtewa_tse_pwivate *pwiv,
			       stwuct tse_buffew *buffew)
{
	if (buffew->dma_addw) {
		if (buffew->mapped_as_page)
			dma_unmap_page(pwiv->device, buffew->dma_addw,
				       buffew->wen, DMA_TO_DEVICE);
		ewse
			dma_unmap_singwe(pwiv->device, buffew->dma_addw,
					 buffew->wen, DMA_TO_DEVICE);
		buffew->dma_addw = 0;
	}
	if (buffew->skb) {
		dev_kfwee_skb_any(buffew->skb);
		buffew->skb = NUWW;
	}
}

static int awwoc_init_skbufs(stwuct awtewa_tse_pwivate *pwiv)
{
	unsigned int wx_descs = pwiv->wx_wing_size;
	unsigned int tx_descs = pwiv->tx_wing_size;
	int wet = -ENOMEM;
	int i;

	/* Cweate Wx wing buffew */
	pwiv->wx_wing = kcawwoc(wx_descs, sizeof(stwuct tse_buffew),
				GFP_KEWNEW);
	if (!pwiv->wx_wing)
		goto eww_wx_wing;

	/* Cweate Tx wing buffew */
	pwiv->tx_wing = kcawwoc(tx_descs, sizeof(stwuct tse_buffew),
				GFP_KEWNEW);
	if (!pwiv->tx_wing)
		goto eww_tx_wing;

	pwiv->tx_cons = 0;
	pwiv->tx_pwod = 0;

	/* Init Wx wing */
	fow (i = 0; i < wx_descs; i++) {
		wet = tse_init_wx_buffew(pwiv, &pwiv->wx_wing[i],
					 pwiv->wx_dma_buf_sz);
		if (wet)
			goto eww_init_wx_buffews;
	}

	pwiv->wx_cons = 0;
	pwiv->wx_pwod = 0;

	wetuwn 0;
eww_init_wx_buffews:
	whiwe (--i >= 0)
		tse_fwee_wx_buffew(pwiv, &pwiv->wx_wing[i]);
	kfwee(pwiv->tx_wing);
eww_tx_wing:
	kfwee(pwiv->wx_wing);
eww_wx_wing:
	wetuwn wet;
}

static void fwee_skbufs(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	unsigned int wx_descs = pwiv->wx_wing_size;
	unsigned int tx_descs = pwiv->tx_wing_size;
	int i;

	/* Wewease the DMA TX/WX socket buffews */
	fow (i = 0; i < wx_descs; i++)
		tse_fwee_wx_buffew(pwiv, &pwiv->wx_wing[i]);
	fow (i = 0; i < tx_descs; i++)
		tse_fwee_tx_buffew(pwiv, &pwiv->tx_wing[i]);


	kfwee(pwiv->tx_wing);
}

/* Weawwocate the skb fow the weception pwocess
 */
static inwine void tse_wx_wefiww(stwuct awtewa_tse_pwivate *pwiv)
{
	unsigned int wxsize = pwiv->wx_wing_size;
	unsigned int entwy;
	int wet;

	fow (; pwiv->wx_cons - pwiv->wx_pwod > 0;
			pwiv->wx_pwod++) {
		entwy = pwiv->wx_pwod % wxsize;
		if (wikewy(pwiv->wx_wing[entwy].skb == NUWW)) {
			wet = tse_init_wx_buffew(pwiv, &pwiv->wx_wing[entwy],
				pwiv->wx_dma_buf_sz);
			if (unwikewy(wet != 0))
				bweak;
			pwiv->dmaops->add_wx_desc(pwiv, &pwiv->wx_wing[entwy]);
		}
	}
}

/* Puww out the VWAN tag and fix up the packet
 */
static inwine void tse_wx_vwan(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct ethhdw *eth_hdw;
	u16 vid;

	if ((dev->featuwes & NETIF_F_HW_VWAN_CTAG_WX) &&
	    !__vwan_get_tag(skb, &vid)) {
		eth_hdw = (stwuct ethhdw *)skb->data;
		memmove(skb->data + VWAN_HWEN, eth_hdw, ETH_AWEN * 2);
		skb_puww(skb, VWAN_HWEN);
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vid);
	}
}

/* Weceive a packet: wetwieve and pass ovew to uppew wevews
 */
static int tse_wx(stwuct awtewa_tse_pwivate *pwiv, int wimit)
{
	unsigned int entwy = pwiv->wx_cons % pwiv->wx_wing_size;
	unsigned int next_entwy;
	unsigned int count = 0;
	stwuct sk_buff *skb;
	u32 wxstatus;
	u16 pktwength;
	u16 pktstatus;

	/* Check fow count < wimit fiwst as get_wx_status is changing
	* the wesponse-fifo so we must pwocess the next packet
	* aftew cawwing get_wx_status if a wesponse is pending.
	* (weading the wast byte of the wesponse pops the vawue fwom the fifo.)
	*/
	whiwe ((count < wimit) &&
	       ((wxstatus = pwiv->dmaops->get_wx_status(pwiv)) != 0)) {
		pktstatus = wxstatus >> 16;
		pktwength = wxstatus & 0xffff;

		if ((pktstatus & 0xFF) || (pktwength == 0))
			netdev_eww(pwiv->dev,
				   "WCV pktstatus %08X pktwength %08X\n",
				   pktstatus, pktwength);

		/* DMA twansfew fwom TSE stawts with 2 additionaw bytes fow
		 * IP paywoad awignment. Status wetuwned by get_wx_status()
		 * contains DMA twansfew wength. Packet is 2 bytes showtew.
		 */
		pktwength -= 2;

		count++;
		next_entwy = (++pwiv->wx_cons) % pwiv->wx_wing_size;

		skb = pwiv->wx_wing[entwy].skb;
		if (unwikewy(!skb)) {
			netdev_eww(pwiv->dev,
				   "%s: Inconsistent Wx descwiptow chain\n",
				   __func__);
			pwiv->dev->stats.wx_dwopped++;
			bweak;
		}
		pwiv->wx_wing[entwy].skb = NUWW;

		skb_put(skb, pktwength);

		dma_unmap_singwe(pwiv->device, pwiv->wx_wing[entwy].dma_addw,
				 pwiv->wx_wing[entwy].wen, DMA_FWOM_DEVICE);

		if (netif_msg_pktdata(pwiv)) {
			netdev_info(pwiv->dev, "fwame weceived %d bytes\n",
				    pktwength);
			pwint_hex_dump(KEWN_EWW, "data: ", DUMP_PWEFIX_OFFSET,
				       16, 1, skb->data, pktwength, twue);
		}

		tse_wx_vwan(pwiv->dev, skb);

		skb->pwotocow = eth_type_twans(skb, pwiv->dev);
		skb_checksum_none_assewt(skb);

		napi_gwo_weceive(&pwiv->napi, skb);

		pwiv->dev->stats.wx_packets++;
		pwiv->dev->stats.wx_bytes += pktwength;

		entwy = next_entwy;

		tse_wx_wefiww(pwiv);
	}

	wetuwn count;
}

/* Wecwaim wesouwces aftew twansmission compwetes
 */
static int tse_tx_compwete(stwuct awtewa_tse_pwivate *pwiv)
{
	unsigned int txsize = pwiv->tx_wing_size;
	stwuct tse_buffew *tx_buff;
	unsigned int entwy;
	int txcompwete = 0;
	u32 weady;

	spin_wock(&pwiv->tx_wock);

	weady = pwiv->dmaops->tx_compwetions(pwiv);

	/* Fwee sent buffews */
	whiwe (weady && (pwiv->tx_cons != pwiv->tx_pwod)) {
		entwy = pwiv->tx_cons % txsize;
		tx_buff = &pwiv->tx_wing[entwy];

		if (netif_msg_tx_done(pwiv))
			netdev_dbg(pwiv->dev, "%s: cuww %d, diwty %d\n",
				   __func__, pwiv->tx_pwod, pwiv->tx_cons);

		if (wikewy(tx_buff->skb))
			pwiv->dev->stats.tx_packets++;

		tse_fwee_tx_buffew(pwiv, tx_buff);
		pwiv->tx_cons++;

		txcompwete++;
		weady--;
	}

	if (unwikewy(netif_queue_stopped(pwiv->dev) &&
		     tse_tx_avaiw(pwiv) > TSE_TX_THWESH(pwiv))) {
		if (netif_queue_stopped(pwiv->dev) &&
		    tse_tx_avaiw(pwiv) > TSE_TX_THWESH(pwiv)) {
			if (netif_msg_tx_done(pwiv))
				netdev_dbg(pwiv->dev, "%s: westawt twansmit\n",
					   __func__);
			netif_wake_queue(pwiv->dev);
		}
	}

	spin_unwock(&pwiv->tx_wock);
	wetuwn txcompwete;
}

/* NAPI powwing function
 */
static int tse_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct awtewa_tse_pwivate *pwiv =
			containew_of(napi, stwuct awtewa_tse_pwivate, napi);
	unsigned wong int fwags;
	int wxcompwete = 0;

	tse_tx_compwete(pwiv);

	wxcompwete = tse_wx(pwiv, budget);

	if (wxcompwete < budget) {

		napi_compwete_done(napi, wxcompwete);

		netdev_dbg(pwiv->dev,
			   "NAPI Compwete, did %d packets with budget %d\n",
			   wxcompwete, budget);

		spin_wock_iwqsave(&pwiv->wxdma_iwq_wock, fwags);
		pwiv->dmaops->enabwe_wxiwq(pwiv);
		pwiv->dmaops->enabwe_txiwq(pwiv);
		spin_unwock_iwqwestowe(&pwiv->wxdma_iwq_wock, fwags);
	}
	wetuwn wxcompwete;
}

/* DMA TX & WX FIFO intewwupt wouting
 */
static iwqwetuwn_t awtewa_isw(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct awtewa_tse_pwivate *pwiv;

	if (unwikewy(!dev)) {
		pw_eww("%s: invawid dev pointew\n", __func__);
		wetuwn IWQ_NONE;
	}
	pwiv = netdev_pwiv(dev);

	spin_wock(&pwiv->wxdma_iwq_wock);
	/* weset IWQs */
	pwiv->dmaops->cweaw_wxiwq(pwiv);
	pwiv->dmaops->cweaw_txiwq(pwiv);
	spin_unwock(&pwiv->wxdma_iwq_wock);

	if (wikewy(napi_scheduwe_pwep(&pwiv->napi))) {
		spin_wock(&pwiv->wxdma_iwq_wock);
		pwiv->dmaops->disabwe_wxiwq(pwiv);
		pwiv->dmaops->disabwe_txiwq(pwiv);
		spin_unwock(&pwiv->wxdma_iwq_wock);
		__napi_scheduwe(&pwiv->napi);
	}


	wetuwn IWQ_HANDWED;
}

/* Twansmit a packet (cawwed by the kewnew). Dispatches
 * eithew the SGDMA method fow twansmitting ow the
 * MSGDMA method, assumes no scattew/gathew suppowt,
 * impwying an assumption that thewe's onwy one
 * physicawwy contiguous fwagment stawting at
 * skb->data, fow wength of skb_headwen(skb).
 */
static netdev_tx_t tse_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	unsigned int nopaged_wen = skb_headwen(skb);
	unsigned int txsize = pwiv->tx_wing_size;
	int nfwags = skb_shinfo(skb)->nw_fwags;
	stwuct tse_buffew *buffew = NUWW;
	netdev_tx_t wet = NETDEV_TX_OK;
	dma_addw_t dma_addw;
	unsigned int entwy;

	spin_wock_bh(&pwiv->tx_wock);

	if (unwikewy(tse_tx_avaiw(pwiv) < nfwags + 1)) {
		if (!netif_queue_stopped(dev)) {
			netif_stop_queue(dev);
			/* This is a hawd ewwow, wog it. */
			netdev_eww(pwiv->dev,
				   "%s: Tx wist fuww when queue awake\n",
				   __func__);
		}
		wet = NETDEV_TX_BUSY;
		goto out;
	}

	/* Map the fiwst skb fwagment */
	entwy = pwiv->tx_pwod % txsize;
	buffew = &pwiv->tx_wing[entwy];

	dma_addw = dma_map_singwe(pwiv->device, skb->data, nopaged_wen,
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(pwiv->device, dma_addw)) {
		netdev_eww(pwiv->dev, "%s: DMA mapping ewwow\n", __func__);
		wet = NETDEV_TX_OK;
		goto out;
	}

	buffew->skb = skb;
	buffew->dma_addw = dma_addw;
	buffew->wen = nopaged_wen;

	pwiv->dmaops->tx_buffew(pwiv, buffew);

	skb_tx_timestamp(skb);

	pwiv->tx_pwod++;
	dev->stats.tx_bytes += skb->wen;

	if (unwikewy(tse_tx_avaiw(pwiv) <= TXQUEUESTOP_THWESHHOWD)) {
		if (netif_msg_hw(pwiv))
			netdev_dbg(pwiv->dev, "%s: stop twansmitted packets\n",
				   __func__);
		netif_stop_queue(dev);
	}

out:
	spin_unwock_bh(&pwiv->tx_wock);

	wetuwn wet;
}

static int awtewa_tse_phy_get_addw_mdio_cweate(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	stwuct device_node *np = pwiv->device->of_node;
	int wet;

	wet = of_get_phy_mode(np, &pwiv->phy_iface);

	/* Avoid get phy addw and cweate mdio if no phy is pwesent */
	if (wet)
		wetuwn 0;

	/* twy to get PHY addwess fwom device twee, use PHY autodetection if
	 * no vawid addwess is given
	 */

	if (of_pwopewty_wead_u32(pwiv->device->of_node, "phy-addw",
			 &pwiv->phy_addw)) {
		pwiv->phy_addw = POWW_PHY;
	}

	if (!((pwiv->phy_addw == POWW_PHY) ||
		  ((pwiv->phy_addw >= 0) && (pwiv->phy_addw < PHY_MAX_ADDW)))) {
		netdev_eww(dev, "invawid phy-addw specified %d\n",
			pwiv->phy_addw);
		wetuwn -ENODEV;
	}

	/* Cweate/attach to MDIO bus */
	wet = awtewa_tse_mdio_cweate(dev,
					 atomic_add_wetuwn(1, &instance_count));

	if (wet)
		wetuwn -ENODEV;

	wetuwn 0;
}

static void tse_update_mac_addw(stwuct awtewa_tse_pwivate *pwiv, const u8 *addw)
{
	u32 msb;
	u32 wsb;

	msb = (addw[3] << 24) | (addw[2] << 16) | (addw[1] << 8) | addw[0];
	wsb = ((addw[5] << 8) | addw[4]) & 0xffff;

	/* Set pwimawy MAC addwess */
	cswww32(msb, pwiv->mac_dev, tse_cswoffs(mac_addw_0));
	cswww32(wsb, pwiv->mac_dev, tse_cswoffs(mac_addw_1));
}

/* MAC softwawe weset.
 * When weset is twiggewed, the MAC function compwetes the cuwwent
 * twansmission ow weception, and subsequentwy disabwes the twansmit and
 * weceive wogic, fwushes the weceive FIFO buffew, and wesets the statistics
 * countews.
 */
static int weset_mac(stwuct awtewa_tse_pwivate *pwiv)
{
	int countew;
	u32 dat;

	dat = cswwd32(pwiv->mac_dev, tse_cswoffs(command_config));
	dat &= ~(MAC_CMDCFG_TX_ENA | MAC_CMDCFG_WX_ENA);
	dat |= MAC_CMDCFG_SW_WESET | MAC_CMDCFG_CNT_WESET;
	cswww32(dat, pwiv->mac_dev, tse_cswoffs(command_config));

	countew = 0;
	whiwe (countew++ < AWTEWA_TSE_SW_WESET_WATCHDOG_CNTW) {
		if (tse_bit_is_cweaw(pwiv->mac_dev, tse_cswoffs(command_config),
				     MAC_CMDCFG_SW_WESET))
			bweak;
		udeway(1);
	}

	if (countew >= AWTEWA_TSE_SW_WESET_WATCHDOG_CNTW) {
		dat = cswwd32(pwiv->mac_dev, tse_cswoffs(command_config));
		dat &= ~MAC_CMDCFG_SW_WESET;
		cswww32(dat, pwiv->mac_dev, tse_cswoffs(command_config));
		wetuwn -1;
	}
	wetuwn 0;
}

/* Initiawize MAC cowe wegistews
*/
static int init_mac(stwuct awtewa_tse_pwivate *pwiv)
{
	unsigned int cmd = 0;
	u32 fwm_wength;

	/* Setup Wx FIFO */
	cswww32(pwiv->wx_fifo_depth - AWTEWA_TSE_WX_SECTION_EMPTY,
		pwiv->mac_dev, tse_cswoffs(wx_section_empty));

	cswww32(AWTEWA_TSE_WX_SECTION_FUWW, pwiv->mac_dev,
		tse_cswoffs(wx_section_fuww));

	cswww32(AWTEWA_TSE_WX_AWMOST_EMPTY, pwiv->mac_dev,
		tse_cswoffs(wx_awmost_empty));

	cswww32(AWTEWA_TSE_WX_AWMOST_FUWW, pwiv->mac_dev,
		tse_cswoffs(wx_awmost_fuww));

	/* Setup Tx FIFO */
	cswww32(pwiv->tx_fifo_depth - AWTEWA_TSE_TX_SECTION_EMPTY,
		pwiv->mac_dev, tse_cswoffs(tx_section_empty));

	cswww32(AWTEWA_TSE_TX_SECTION_FUWW, pwiv->mac_dev,
		tse_cswoffs(tx_section_fuww));

	cswww32(AWTEWA_TSE_TX_AWMOST_EMPTY, pwiv->mac_dev,
		tse_cswoffs(tx_awmost_empty));

	cswww32(AWTEWA_TSE_TX_AWMOST_FUWW, pwiv->mac_dev,
		tse_cswoffs(tx_awmost_fuww));

	/* MAC Addwess Configuwation */
	tse_update_mac_addw(pwiv, pwiv->dev->dev_addw);

	/* MAC Function Configuwation */
	fwm_wength = ETH_HWEN + pwiv->dev->mtu + ETH_FCS_WEN;
	cswww32(fwm_wength, pwiv->mac_dev, tse_cswoffs(fwm_wength));

	cswww32(AWTEWA_TSE_TX_IPG_WENGTH, pwiv->mac_dev,
		tse_cswoffs(tx_ipg_wength));

	/* Disabwe WX/TX shift 16 fow awignment of aww weceived fwames on 16-bit
	 * stawt addwess
	 */
	tse_set_bit(pwiv->mac_dev, tse_cswoffs(wx_cmd_stat),
		    AWTEWA_TSE_WX_CMD_STAT_WX_SHIFT16);

	tse_cweaw_bit(pwiv->mac_dev, tse_cswoffs(tx_cmd_stat),
		      AWTEWA_TSE_TX_CMD_STAT_TX_SHIFT16 |
		      AWTEWA_TSE_TX_CMD_STAT_OMIT_CWC);

	/* Set the MAC options */
	cmd = cswwd32(pwiv->mac_dev, tse_cswoffs(command_config));
	cmd &= ~MAC_CMDCFG_PAD_EN;	/* No padding Wemovaw on Weceive */
	cmd &= ~MAC_CMDCFG_CWC_FWD;	/* CWC Wemovaw */
	cmd |= MAC_CMDCFG_WX_EWW_DISC;	/* Automaticawwy discawd fwames
					 * with CWC ewwows
					 */
	cmd |= MAC_CMDCFG_CNTW_FWM_ENA;
	cmd &= ~MAC_CMDCFG_TX_ENA;
	cmd &= ~MAC_CMDCFG_WX_ENA;

	/* Defauwt speed and dupwex setting, fuww/100 */
	cmd &= ~MAC_CMDCFG_HD_ENA;
	cmd &= ~MAC_CMDCFG_ETH_SPEED;
	cmd &= ~MAC_CMDCFG_ENA_10;

	cswww32(cmd, pwiv->mac_dev, tse_cswoffs(command_config));

	cswww32(AWTEWA_TSE_PAUSE_QUANTA, pwiv->mac_dev,
		tse_cswoffs(pause_quanta));

	if (netif_msg_hw(pwiv))
		dev_dbg(pwiv->device,
			"MAC post-initiawization: CMD_CONFIG = 0x%08x\n", cmd);

	wetuwn 0;
}

/* Stawt/stop MAC twansmission wogic
 */
static void tse_set_mac(stwuct awtewa_tse_pwivate *pwiv, boow enabwe)
{
	u32 vawue = cswwd32(pwiv->mac_dev, tse_cswoffs(command_config));

	if (enabwe)
		vawue |= MAC_CMDCFG_TX_ENA | MAC_CMDCFG_WX_ENA;
	ewse
		vawue &= ~(MAC_CMDCFG_TX_ENA | MAC_CMDCFG_WX_ENA);

	cswww32(vawue, pwiv->mac_dev, tse_cswoffs(command_config));
}

/* Change the MTU
 */
static int tse_change_mtu(stwuct net_device *dev, int new_mtu)
{
	if (netif_wunning(dev)) {
		netdev_eww(dev, "must be stopped to change its MTU\n");
		wetuwn -EBUSY;
	}

	dev->mtu = new_mtu;
	netdev_update_featuwes(dev);

	wetuwn 0;
}

static void awtewa_tse_set_mcfiwtew(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	int i;

	/* cweaw the hash fiwtew */
	fow (i = 0; i < 64; i++)
		cswww32(0, pwiv->mac_dev, tse_cswoffs(hash_tabwe) + i * 4);

	netdev_fow_each_mc_addw(ha, dev) {
		unsigned int hash = 0;
		int mac_octet;

		fow (mac_octet = 5; mac_octet >= 0; mac_octet--) {
			unsigned chaw xow_bit = 0;
			unsigned chaw octet = ha->addw[mac_octet];
			unsigned int bitshift;

			fow (bitshift = 0; bitshift < 8; bitshift++)
				xow_bit ^= ((octet >> bitshift) & 0x01);

			hash = (hash << 1) | xow_bit;
		}
		cswww32(1, pwiv->mac_dev, tse_cswoffs(hash_tabwe) + hash * 4);
	}
}


static void awtewa_tse_set_mcfiwtewaww(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	int i;

	/* set the hash fiwtew */
	fow (i = 0; i < 64; i++)
		cswww32(1, pwiv->mac_dev, tse_cswoffs(hash_tabwe) + i * 4);
}

/* Set ow cweaw the muwticast fiwtew fow this adaptew
 */
static void tse_set_wx_mode_hashfiwtew(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);

	spin_wock(&pwiv->mac_cfg_wock);

	if (dev->fwags & IFF_PWOMISC)
		tse_set_bit(pwiv->mac_dev, tse_cswoffs(command_config),
			    MAC_CMDCFG_PWOMIS_EN);

	if (dev->fwags & IFF_AWWMUWTI)
		awtewa_tse_set_mcfiwtewaww(dev);
	ewse
		awtewa_tse_set_mcfiwtew(dev);

	spin_unwock(&pwiv->mac_cfg_wock);
}

/* Set ow cweaw the muwticast fiwtew fow this adaptew
 */
static void tse_set_wx_mode(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);

	spin_wock(&pwiv->mac_cfg_wock);

	if ((dev->fwags & IFF_PWOMISC) || (dev->fwags & IFF_AWWMUWTI) ||
	    !netdev_mc_empty(dev) || !netdev_uc_empty(dev))
		tse_set_bit(pwiv->mac_dev, tse_cswoffs(command_config),
			    MAC_CMDCFG_PWOMIS_EN);
	ewse
		tse_cweaw_bit(pwiv->mac_dev, tse_cswoffs(command_config),
			      MAC_CMDCFG_PWOMIS_EN);

	spin_unwock(&pwiv->mac_cfg_wock);
}

/* Open and initiawize the intewface
 */
static int tse_open(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;
	int wet = 0;
	int i;

	/* Weset and configuwe TSE MAC and pwobe associated PHY */
	wet = pwiv->dmaops->init_dma(pwiv);
	if (wet != 0) {
		netdev_eww(dev, "Cannot initiawize DMA\n");
		goto phy_ewwow;
	}

	if (netif_msg_ifup(pwiv))
		netdev_wawn(dev, "device MAC addwess %pM\n",
			    dev->dev_addw);

	if ((pwiv->wevision < 0xd00) || (pwiv->wevision > 0xe00))
		netdev_wawn(dev, "TSE wevision %x\n", pwiv->wevision);

	spin_wock(&pwiv->mac_cfg_wock);

	wet = weset_mac(pwiv);
	/* Note that weset_mac wiww faiw if the cwocks awe gated by the PHY
	 * due to the PHY being put into isowation ow powew down mode.
	 * This is not an ewwow if weset faiws due to no cwock.
	 */
	if (wet)
		netdev_dbg(dev, "Cannot weset MAC cowe (ewwow: %d)\n", wet);

	wet = init_mac(pwiv);
	spin_unwock(&pwiv->mac_cfg_wock);
	if (wet) {
		netdev_eww(dev, "Cannot init MAC cowe (ewwow: %d)\n", wet);
		goto awwoc_skbuf_ewwow;
	}

	pwiv->dmaops->weset_dma(pwiv);

	/* Cweate and initiawize the TX/WX descwiptows chains. */
	pwiv->wx_wing_size = dma_wx_num;
	pwiv->tx_wing_size = dma_tx_num;
	wet = awwoc_init_skbufs(pwiv);
	if (wet) {
		netdev_eww(dev, "DMA descwiptows initiawization faiwed\n");
		goto awwoc_skbuf_ewwow;
	}


	/* Wegistew WX intewwupt */
	wet = wequest_iwq(pwiv->wx_iwq, awtewa_isw, IWQF_SHAWED,
			  dev->name, dev);
	if (wet) {
		netdev_eww(dev, "Unabwe to wegistew WX intewwupt %d\n",
			   pwiv->wx_iwq);
		goto init_ewwow;
	}

	/* Wegistew TX intewwupt */
	wet = wequest_iwq(pwiv->tx_iwq, awtewa_isw, IWQF_SHAWED,
			  dev->name, dev);
	if (wet) {
		netdev_eww(dev, "Unabwe to wegistew TX intewwupt %d\n",
			   pwiv->tx_iwq);
		goto tx_wequest_iwq_ewwow;
	}

	/* Enabwe DMA intewwupts */
	spin_wock_iwqsave(&pwiv->wxdma_iwq_wock, fwags);
	pwiv->dmaops->enabwe_wxiwq(pwiv);
	pwiv->dmaops->enabwe_txiwq(pwiv);

	/* Setup WX descwiptow chain */
	fow (i = 0; i < pwiv->wx_wing_size; i++)
		pwiv->dmaops->add_wx_desc(pwiv, &pwiv->wx_wing[i]);

	spin_unwock_iwqwestowe(&pwiv->wxdma_iwq_wock, fwags);

	wet = phywink_of_phy_connect(pwiv->phywink, pwiv->device->of_node, 0);
	if (wet) {
		netdev_eww(dev, "couwd not connect phywink (%d)\n", wet);
		goto tx_wequest_iwq_ewwow;
	}
	phywink_stawt(pwiv->phywink);

	napi_enabwe(&pwiv->napi);
	netif_stawt_queue(dev);

	pwiv->dmaops->stawt_wxdma(pwiv);

	/* Stawt MAC Wx/Tx */
	spin_wock(&pwiv->mac_cfg_wock);
	tse_set_mac(pwiv, twue);
	spin_unwock(&pwiv->mac_cfg_wock);

	wetuwn 0;

tx_wequest_iwq_ewwow:
	fwee_iwq(pwiv->wx_iwq, dev);
init_ewwow:
	fwee_skbufs(dev);
awwoc_skbuf_ewwow:
phy_ewwow:
	wetuwn wet;
}

/* Stop TSE MAC intewface and put the device in an inactive state
 */
static int tse_shutdown(stwuct net_device *dev)
{
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong int fwags;
	int wet;

	phywink_stop(pwiv->phywink);
	phywink_disconnect_phy(pwiv->phywink);
	netif_stop_queue(dev);
	napi_disabwe(&pwiv->napi);

	/* Disabwe DMA intewwupts */
	spin_wock_iwqsave(&pwiv->wxdma_iwq_wock, fwags);
	pwiv->dmaops->disabwe_wxiwq(pwiv);
	pwiv->dmaops->disabwe_txiwq(pwiv);
	spin_unwock_iwqwestowe(&pwiv->wxdma_iwq_wock, fwags);

	/* Fwee the IWQ wines */
	fwee_iwq(pwiv->wx_iwq, dev);
	fwee_iwq(pwiv->tx_iwq, dev);

	/* disabwe and weset the MAC, empties fifo */
	spin_wock(&pwiv->mac_cfg_wock);
	spin_wock(&pwiv->tx_wock);

	wet = weset_mac(pwiv);
	/* Note that weset_mac wiww faiw if the cwocks awe gated by the PHY
	 * due to the PHY being put into isowation ow powew down mode.
	 * This is not an ewwow if weset faiws due to no cwock.
	 */
	if (wet)
		netdev_dbg(dev, "Cannot weset MAC cowe (ewwow: %d)\n", wet);
	pwiv->dmaops->weset_dma(pwiv);
	fwee_skbufs(dev);

	spin_unwock(&pwiv->tx_wock);
	spin_unwock(&pwiv->mac_cfg_wock);

	pwiv->dmaops->uninit_dma(pwiv);

	wetuwn 0;
}

static stwuct net_device_ops awtewa_tse_netdev_ops = {
	.ndo_open		= tse_open,
	.ndo_stop		= tse_shutdown,
	.ndo_stawt_xmit		= tse_stawt_xmit,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_set_wx_mode	= tse_set_wx_mode,
	.ndo_change_mtu		= tse_change_mtu,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static void awt_tse_mac_config(stwuct phywink_config *config, unsigned int mode,
			       const stwuct phywink_wink_state *state)
{
	stwuct net_device *ndev = to_net_dev(config->dev);
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(ndev);

	spin_wock(&pwiv->mac_cfg_wock);
	weset_mac(pwiv);
	tse_set_mac(pwiv, twue);
	spin_unwock(&pwiv->mac_cfg_wock);
}

static void awt_tse_mac_wink_down(stwuct phywink_config *config,
				  unsigned int mode, phy_intewface_t intewface)
{
}

static void awt_tse_mac_wink_up(stwuct phywink_config *config,
				stwuct phy_device *phy, unsigned int mode,
				phy_intewface_t intewface, int speed,
				int dupwex, boow tx_pause, boow wx_pause)
{
	stwuct net_device *ndev = to_net_dev(config->dev);
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(ndev);
	u32 ctww;

	ctww = cswwd32(pwiv->mac_dev, tse_cswoffs(command_config));
	ctww &= ~(MAC_CMDCFG_ENA_10 | MAC_CMDCFG_ETH_SPEED | MAC_CMDCFG_HD_ENA);

	if (dupwex == DUPWEX_HAWF)
		ctww |= MAC_CMDCFG_HD_ENA;

	if (speed == SPEED_1000)
		ctww |= MAC_CMDCFG_ETH_SPEED;
	ewse if (speed == SPEED_10)
		ctww |= MAC_CMDCFG_ENA_10;

	spin_wock(&pwiv->mac_cfg_wock);
	cswww32(ctww, pwiv->mac_dev, tse_cswoffs(command_config));
	spin_unwock(&pwiv->mac_cfg_wock);
}

static stwuct phywink_pcs *awt_tse_sewect_pcs(stwuct phywink_config *config,
					      phy_intewface_t intewface)
{
	stwuct net_device *ndev = to_net_dev(config->dev);
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(ndev);

	if (intewface == PHY_INTEWFACE_MODE_SGMII ||
	    intewface == PHY_INTEWFACE_MODE_1000BASEX)
		wetuwn pwiv->pcs;
	ewse
		wetuwn NUWW;
}

static const stwuct phywink_mac_ops awt_tse_phywink_ops = {
	.mac_config = awt_tse_mac_config,
	.mac_wink_down = awt_tse_mac_wink_down,
	.mac_wink_up = awt_tse_mac_wink_up,
	.mac_sewect_pcs = awt_tse_sewect_pcs,
};

static int wequest_and_map(stwuct pwatfowm_device *pdev, const chaw *name,
			   stwuct wesouwce **wes, void __iomem **ptw)
{
	stwuct device *device = &pdev->dev;
	stwuct wesouwce *wegion;

	*wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, name);
	if (*wes == NUWW) {
		dev_eww(device, "wesouwce %s not defined\n", name);
		wetuwn -ENODEV;
	}

	wegion = devm_wequest_mem_wegion(device, (*wes)->stawt,
					 wesouwce_size(*wes), dev_name(device));
	if (wegion == NUWW) {
		dev_eww(device, "unabwe to wequest %s\n", name);
		wetuwn -EBUSY;
	}

	*ptw = devm_iowemap(device, wegion->stawt,
				    wesouwce_size(wegion));
	if (*ptw == NUWW) {
		dev_eww(device, "iowemap of %s faiwed!", name);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* Pwobe Awtewa TSE MAC device
 */
static int awtewa_tse_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap_config pcs_wegmap_cfg;
	stwuct awtewa_tse_pwivate *pwiv;
	stwuct mdio_wegmap_config mwc;
	stwuct wesouwce *contwow_powt;
	stwuct wegmap *pcs_wegmap;
	stwuct wesouwce *dma_wes;
	stwuct wesouwce *pcs_wes;
	stwuct mii_bus *pcs_bus;
	stwuct net_device *ndev;
	void __iomem *descmap;
	int wet = -ENODEV;

	ndev = awwoc_ethewdev(sizeof(stwuct awtewa_tse_pwivate));
	if (!ndev) {
		dev_eww(&pdev->dev, "Couwd not awwocate netwowk device\n");
		wetuwn -ENODEV;
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);

	pwiv = netdev_pwiv(ndev);
	pwiv->device = &pdev->dev;
	pwiv->dev = ndev;
	pwiv->msg_enabwe = netif_msg_init(debug, defauwt_msg_wevew);

	pwiv->dmaops = device_get_match_data(&pdev->dev);

	if (pwiv->dmaops &&
	    pwiv->dmaops->awtewa_dtype == AWTEWA_DTYPE_SGDMA) {
		/* Get the mapped addwess to the SGDMA descwiptow memowy */
		wet = wequest_and_map(pdev, "s1", &dma_wes, &descmap);
		if (wet)
			goto eww_fwee_netdev;

		/* Stawt of that memowy is fow twansmit descwiptows */
		pwiv->tx_dma_desc = descmap;

		/* Fiwst hawf is fow tx descwiptows, othew hawf fow tx */
		pwiv->txdescmem = wesouwce_size(dma_wes)/2;

		pwiv->txdescmem_busaddw = (dma_addw_t)dma_wes->stawt;

		pwiv->wx_dma_desc = (void __iomem *)((uintptw_t)(descmap +
						     pwiv->txdescmem));
		pwiv->wxdescmem = wesouwce_size(dma_wes)/2;
		pwiv->wxdescmem_busaddw = dma_wes->stawt;
		pwiv->wxdescmem_busaddw += pwiv->txdescmem;

		if (uppew_32_bits(pwiv->wxdescmem_busaddw)) {
			dev_dbg(pwiv->device,
				"SGDMA bus addwesses gweatew than 32-bits\n");
			wet = -EINVAW;
			goto eww_fwee_netdev;
		}
		if (uppew_32_bits(pwiv->txdescmem_busaddw)) {
			dev_dbg(pwiv->device,
				"SGDMA bus addwesses gweatew than 32-bits\n");
			wet = -EINVAW;
			goto eww_fwee_netdev;
		}
	} ewse if (pwiv->dmaops &&
		   pwiv->dmaops->awtewa_dtype == AWTEWA_DTYPE_MSGDMA) {
		wet = wequest_and_map(pdev, "wx_wesp", &dma_wes,
				      &pwiv->wx_dma_wesp);
		if (wet)
			goto eww_fwee_netdev;

		wet = wequest_and_map(pdev, "tx_desc", &dma_wes,
				      &pwiv->tx_dma_desc);
		if (wet)
			goto eww_fwee_netdev;

		pwiv->txdescmem = wesouwce_size(dma_wes);
		pwiv->txdescmem_busaddw = dma_wes->stawt;

		wet = wequest_and_map(pdev, "wx_desc", &dma_wes,
				      &pwiv->wx_dma_desc);
		if (wet)
			goto eww_fwee_netdev;

		pwiv->wxdescmem = wesouwce_size(dma_wes);
		pwiv->wxdescmem_busaddw = dma_wes->stawt;

	} ewse {
		wet = -ENODEV;
		goto eww_fwee_netdev;
	}

	if (!dma_set_mask(pwiv->device, DMA_BIT_MASK(pwiv->dmaops->dmamask))) {
		dma_set_cohewent_mask(pwiv->device,
				      DMA_BIT_MASK(pwiv->dmaops->dmamask));
	} ewse if (!dma_set_mask(pwiv->device, DMA_BIT_MASK(32))) {
		dma_set_cohewent_mask(pwiv->device, DMA_BIT_MASK(32));
	} ewse {
		wet = -EIO;
		goto eww_fwee_netdev;
	}

	/* MAC addwess space */
	wet = wequest_and_map(pdev, "contwow_powt", &contwow_powt,
			      (void __iomem **)&pwiv->mac_dev);
	if (wet)
		goto eww_fwee_netdev;

	/* xSGDMA Wx Dispatchew addwess space */
	wet = wequest_and_map(pdev, "wx_csw", &dma_wes,
			      &pwiv->wx_dma_csw);
	if (wet)
		goto eww_fwee_netdev;


	/* xSGDMA Tx Dispatchew addwess space */
	wet = wequest_and_map(pdev, "tx_csw", &dma_wes,
			      &pwiv->tx_dma_csw);
	if (wet)
		goto eww_fwee_netdev;

	memset(&pcs_wegmap_cfg, 0, sizeof(pcs_wegmap_cfg));
	memset(&mwc, 0, sizeof(mwc));
	/* SGMII PCS addwess space. The wocation can vawy depending on how the
	 * IP is integwated. We can have a wesouwce dedicated to it at a specific
	 * addwess space, but if it's not the case, we fawwback to the mdiophy0
	 * fwom the MAC's addwess space
	 */
	wet = wequest_and_map(pdev, "pcs", &pcs_wes, &pwiv->pcs_base);
	if (wet) {
		/* If we can't find a dedicated wesouwce fow the PCS, fawwback
		 * to the intewnaw PCS, that has a diffewent addwess stwide
		 */
		pwiv->pcs_base = pwiv->mac_dev + tse_cswoffs(mdio_phy0);
		pcs_wegmap_cfg.weg_bits = 32;
		/* Vawues awe MDIO-wike vawues, on 16 bits */
		pcs_wegmap_cfg.vaw_bits = 16;
		pcs_wegmap_cfg.weg_shift = WEGMAP_UPSHIFT(2);
	} ewse {
		pcs_wegmap_cfg.weg_bits = 16;
		pcs_wegmap_cfg.vaw_bits = 16;
		pcs_wegmap_cfg.weg_shift = WEGMAP_UPSHIFT(1);
	}

	/* Cweate a wegmap fow the PCS so that it can be used by the PCS dwivew */
	pcs_wegmap = devm_wegmap_init_mmio(&pdev->dev, pwiv->pcs_base,
					   &pcs_wegmap_cfg);
	if (IS_EWW(pcs_wegmap)) {
		wet = PTW_EWW(pcs_wegmap);
		goto eww_fwee_netdev;
	}
	mwc.wegmap = pcs_wegmap;
	mwc.pawent = &pdev->dev;
	mwc.vawid_addw = 0x0;
	mwc.autoscan = fawse;

	/* Wx IWQ */
	pwiv->wx_iwq = pwatfowm_get_iwq_byname(pdev, "wx_iwq");
	if (pwiv->wx_iwq == -ENXIO) {
		dev_eww(&pdev->dev, "cannot obtain Wx IWQ\n");
		wet = -ENXIO;
		goto eww_fwee_netdev;
	}

	/* Tx IWQ */
	pwiv->tx_iwq = pwatfowm_get_iwq_byname(pdev, "tx_iwq");
	if (pwiv->tx_iwq == -ENXIO) {
		dev_eww(&pdev->dev, "cannot obtain Tx IWQ\n");
		wet = -ENXIO;
		goto eww_fwee_netdev;
	}

	/* get FIFO depths fwom device twee */
	if (of_pwopewty_wead_u32(pdev->dev.of_node, "wx-fifo-depth",
				 &pwiv->wx_fifo_depth)) {
		dev_eww(&pdev->dev, "cannot obtain wx-fifo-depth\n");
		wet = -ENXIO;
		goto eww_fwee_netdev;
	}

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "tx-fifo-depth",
				 &pwiv->tx_fifo_depth)) {
		dev_eww(&pdev->dev, "cannot obtain tx-fifo-depth\n");
		wet = -ENXIO;
		goto eww_fwee_netdev;
	}

	/* get hash fiwtew settings fow this instance */
	pwiv->hash_fiwtew =
		of_pwopewty_wead_boow(pdev->dev.of_node,
				      "awtw,has-hash-muwticast-fiwtew");

	/* Set hash fiwtew to not set fow now untiw the
	 * muwticast fiwtew weceive issue is debugged
	 */
	pwiv->hash_fiwtew = 0;

	/* get suppwementaw addwess settings fow this instance */
	pwiv->added_unicast =
		of_pwopewty_wead_boow(pdev->dev.of_node,
				      "awtw,has-suppwementawy-unicast");

	pwiv->dev->min_mtu = ETH_ZWEN + ETH_FCS_WEN;
	/* Max MTU is 1500, ETH_DATA_WEN */
	pwiv->dev->max_mtu = ETH_DATA_WEN;

	/* Get the max mtu fwom the device twee. Note that the
	 * "max-fwame-size" pawametew is actuawwy max mtu. Definition
	 * in the ePAPW v1.1 spec and usage diffew, so go with usage.
	 */
	of_pwopewty_wead_u32(pdev->dev.of_node, "max-fwame-size",
			     &pwiv->dev->max_mtu);

	/* The DMA buffew size awweady accounts fow an awignment bias
	 * to avoid unawigned access exceptions fow the NIOS pwocessow,
	 */
	pwiv->wx_dma_buf_sz = AWTEWA_WXDMABUFFEW_SIZE;

	/* get defauwt MAC addwess fwom device twee */
	wet = of_get_ethdev_addwess(pdev->dev.of_node, ndev);
	if (wet)
		eth_hw_addw_wandom(ndev);

	/* get phy addw and cweate mdio */
	wet = awtewa_tse_phy_get_addw_mdio_cweate(ndev);

	if (wet)
		goto eww_fwee_netdev;

	/* initiawize netdev */
	ndev->mem_stawt = contwow_powt->stawt;
	ndev->mem_end = contwow_powt->end;
	ndev->netdev_ops = &awtewa_tse_netdev_ops;
	awtewa_tse_set_ethtoow_ops(ndev);

	awtewa_tse_netdev_ops.ndo_set_wx_mode = tse_set_wx_mode;

	if (pwiv->hash_fiwtew)
		awtewa_tse_netdev_ops.ndo_set_wx_mode =
			tse_set_wx_mode_hashfiwtew;

	/* Scattew/gathew IO is not suppowted,
	 * so it is tuwned off
	 */
	ndev->hw_featuwes &= ~NETIF_F_SG;
	ndev->featuwes |= ndev->hw_featuwes | NETIF_F_HIGHDMA;

	/* VWAN offwoading of tagging, stwipping and fiwtewing is not
	 * suppowted by hawdwawe, but dwivew wiww accommodate the
	 * extwa 4-byte VWAN tag fow pwocessing by uppew wayews
	 */
	ndev->featuwes |= NETIF_F_HW_VWAN_CTAG_WX;

	/* setup NAPI intewface */
	netif_napi_add(ndev, &pwiv->napi, tse_poww);

	spin_wock_init(&pwiv->mac_cfg_wock);
	spin_wock_init(&pwiv->tx_wock);
	spin_wock_init(&pwiv->wxdma_iwq_wock);

	netif_cawwiew_off(ndev);
	wet = wegistew_netdev(ndev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew TSE net device\n");
		goto eww_wegistew_netdev;
	}

	pwatfowm_set_dwvdata(pdev, ndev);

	pwiv->wevision = iowead32(&pwiv->mac_dev->megacowe_wevision);

	if (netif_msg_pwobe(pwiv))
		dev_info(&pdev->dev, "Awtewa TSE MAC vewsion %d.%d at 0x%08wx iwq %d/%d\n",
			 (pwiv->wevision >> 8) & 0xff,
			 pwiv->wevision & 0xff,
			 (unsigned wong) contwow_powt->stawt, pwiv->wx_iwq,
			 pwiv->tx_iwq);

	snpwintf(mwc.name, MII_BUS_ID_SIZE, "%s-pcs-mii", ndev->name);
	pcs_bus = devm_mdio_wegmap_wegistew(&pdev->dev, &mwc);
	if (IS_EWW(pcs_bus)) {
		wet = PTW_EWW(pcs_bus);
		goto eww_init_pcs;
	}

	pwiv->pcs = wynx_pcs_cweate_mdiodev(pcs_bus, 0);
	if (IS_EWW(pwiv->pcs)) {
		wet = PTW_EWW(pwiv->pcs);
		goto eww_init_pcs;
	}

	pwiv->phywink_config.dev = &ndev->dev;
	pwiv->phywink_config.type = PHYWINK_NETDEV;
	pwiv->phywink_config.mac_capabiwities = MAC_SYM_PAUSE | MAC_10 |
						MAC_100 | MAC_1000FD;

	phy_intewface_set_wgmii(pwiv->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_MII,
		  pwiv->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_GMII,
		  pwiv->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_SGMII,
		  pwiv->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_1000BASEX,
		  pwiv->phywink_config.suppowted_intewfaces);

	pwiv->phywink = phywink_cweate(&pwiv->phywink_config,
				       of_fwnode_handwe(pwiv->device->of_node),
				       pwiv->phy_iface, &awt_tse_phywink_ops);
	if (IS_EWW(pwiv->phywink)) {
		dev_eww(&pdev->dev, "faiwed to cweate phywink\n");
		wet = PTW_EWW(pwiv->phywink);
		goto eww_init_phywink;
	}

	wetuwn 0;
eww_init_phywink:
	wynx_pcs_destwoy(pwiv->pcs);
eww_init_pcs:
	unwegistew_netdev(ndev);
eww_wegistew_netdev:
	netif_napi_dew(&pwiv->napi);
	awtewa_tse_mdio_destwoy(ndev);
eww_fwee_netdev:
	fwee_netdev(ndev);
	wetuwn wet;
}

/* Wemove Awtewa TSE MAC device
 */
static void awtewa_tse_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct awtewa_tse_pwivate *pwiv = netdev_pwiv(ndev);

	pwatfowm_set_dwvdata(pdev, NUWW);
	awtewa_tse_mdio_destwoy(ndev);
	unwegistew_netdev(ndev);
	phywink_destwoy(pwiv->phywink);
	wynx_pcs_destwoy(pwiv->pcs);

	fwee_netdev(ndev);
}

static const stwuct awtewa_dmaops awtewa_dtype_sgdma = {
	.awtewa_dtype = AWTEWA_DTYPE_SGDMA,
	.dmamask = 32,
	.weset_dma = sgdma_weset,
	.enabwe_txiwq = sgdma_enabwe_txiwq,
	.enabwe_wxiwq = sgdma_enabwe_wxiwq,
	.disabwe_txiwq = sgdma_disabwe_txiwq,
	.disabwe_wxiwq = sgdma_disabwe_wxiwq,
	.cweaw_txiwq = sgdma_cweaw_txiwq,
	.cweaw_wxiwq = sgdma_cweaw_wxiwq,
	.tx_buffew = sgdma_tx_buffew,
	.tx_compwetions = sgdma_tx_compwetions,
	.add_wx_desc = sgdma_add_wx_desc,
	.get_wx_status = sgdma_wx_status,
	.init_dma = sgdma_initiawize,
	.uninit_dma = sgdma_uninitiawize,
	.stawt_wxdma = sgdma_stawt_wxdma,
};

static const stwuct awtewa_dmaops awtewa_dtype_msgdma = {
	.awtewa_dtype = AWTEWA_DTYPE_MSGDMA,
	.dmamask = 64,
	.weset_dma = msgdma_weset,
	.enabwe_txiwq = msgdma_enabwe_txiwq,
	.enabwe_wxiwq = msgdma_enabwe_wxiwq,
	.disabwe_txiwq = msgdma_disabwe_txiwq,
	.disabwe_wxiwq = msgdma_disabwe_wxiwq,
	.cweaw_txiwq = msgdma_cweaw_txiwq,
	.cweaw_wxiwq = msgdma_cweaw_wxiwq,
	.tx_buffew = msgdma_tx_buffew,
	.tx_compwetions = msgdma_tx_compwetions,
	.add_wx_desc = msgdma_add_wx_desc,
	.get_wx_status = msgdma_wx_status,
	.init_dma = msgdma_initiawize,
	.uninit_dma = msgdma_uninitiawize,
	.stawt_wxdma = msgdma_stawt_wxdma,
};

static const stwuct of_device_id awtewa_tse_ids[] = {
	{ .compatibwe = "awtw,tse-msgdma-1.0", .data = &awtewa_dtype_msgdma, },
	{ .compatibwe = "awtw,tse-1.0", .data = &awtewa_dtype_sgdma, },
	{ .compatibwe = "AWTW,tse-1.0", .data = &awtewa_dtype_sgdma, },
	{},
};
MODUWE_DEVICE_TABWE(of, awtewa_tse_ids);

static stwuct pwatfowm_dwivew awtewa_tse_dwivew = {
	.pwobe		= awtewa_tse_pwobe,
	.wemove_new	= awtewa_tse_wemove,
	.suspend	= NUWW,
	.wesume		= NUWW,
	.dwivew		= {
		.name	= AWTEWA_TSE_WESOUWCE_NAME,
		.of_match_tabwe = awtewa_tse_ids,
	},
};

moduwe_pwatfowm_dwivew(awtewa_tse_dwivew);

MODUWE_AUTHOW("Awtewa Cowpowation");
MODUWE_DESCWIPTION("Awtewa Twipwe Speed Ethewnet MAC dwivew");
MODUWE_WICENSE("GPW v2");
