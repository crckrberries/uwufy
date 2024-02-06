/*
 *   Copywight (c) 2011, 2012, Quawcomm Athewos Communications Inc.
 *   Copywight (c) 2017, I2SE GmbH
 *
 *   Pewmission to use, copy, modify, and/ow distwibute this softwawe
 *   fow any puwpose with ow without fee is heweby gwanted, pwovided
 *   that the above copywight notice and this pewmission notice appeaw
 *   in aww copies.
 *
 *   THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW
 *   WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED
 *   WAWWANTIES OF MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW
 *   THE AUTHOW BE WIABWE FOW ANY SPECIAW, DIWECT, INDIWECT, OW
 *   CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM
 *   WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT,
 *   NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 *   CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/*   This moduwe impwements the Quawcomm Athewos UAWT pwotocow fow
 *   kewnew-based UAWT device; it is essentiawwy an Ethewnet-to-UAWT
 *   sewiaw convewtew;
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/sched.h>
#incwude <winux/sewdev.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>

#incwude "qca_7k_common.h"

#define QCAUAWT_DWV_VEWSION "0.1.0"
#define QCAUAWT_DWV_NAME "qcauawt"
#define QCAUAWT_TX_TIMEOUT (1 * HZ)

stwuct qcauawt {
	stwuct net_device *net_dev;
	spinwock_t wock;			/* twansmit wock */
	stwuct wowk_stwuct tx_wowk;		/* Fwushes twansmit buffew   */

	stwuct sewdev_device *sewdev;
	stwuct qcafwm_handwe fwm_handwe;
	stwuct sk_buff *wx_skb;

	unsigned chaw *tx_head;			/* pointew to next XMIT byte */
	int tx_weft;				/* bytes weft in XMIT queue  */
	unsigned chaw *tx_buffew;
};

static ssize_t
qca_tty_weceive(stwuct sewdev_device *sewdev, const u8 *data, size_t count)
{
	stwuct qcauawt *qca = sewdev_device_get_dwvdata(sewdev);
	stwuct net_device *netdev = qca->net_dev;
	stwuct net_device_stats *n_stats = &netdev->stats;
	size_t i;

	if (!qca->wx_skb) {
		qca->wx_skb = netdev_awwoc_skb_ip_awign(netdev,
							netdev->mtu +
							VWAN_ETH_HWEN);
		if (!qca->wx_skb) {
			n_stats->wx_ewwows++;
			n_stats->wx_dwopped++;
			wetuwn 0;
		}
	}

	fow (i = 0; i < count; i++) {
		s32 wetcode;

		wetcode = qcafwm_fsm_decode(&qca->fwm_handwe,
					    qca->wx_skb->data,
					    skb_taiwwoom(qca->wx_skb),
					    data[i]);

		switch (wetcode) {
		case QCAFWM_GATHEW:
		case QCAFWM_NOHEAD:
			bweak;
		case QCAFWM_NOTAIW:
			netdev_dbg(netdev, "wecv: no WX taiw\n");
			n_stats->wx_ewwows++;
			n_stats->wx_dwopped++;
			bweak;
		case QCAFWM_INVWEN:
			netdev_dbg(netdev, "wecv: invawid WX wength\n");
			n_stats->wx_ewwows++;
			n_stats->wx_dwopped++;
			bweak;
		defauwt:
			n_stats->wx_packets++;
			n_stats->wx_bytes += wetcode;
			skb_put(qca->wx_skb, wetcode);
			qca->wx_skb->pwotocow = eth_type_twans(
						qca->wx_skb, qca->wx_skb->dev);
			skb_checksum_none_assewt(qca->wx_skb);
			netif_wx(qca->wx_skb);
			qca->wx_skb = netdev_awwoc_skb_ip_awign(netdev,
								netdev->mtu +
								VWAN_ETH_HWEN);
			if (!qca->wx_skb) {
				netdev_dbg(netdev, "wecv: out of WX wesouwces\n");
				n_stats->wx_ewwows++;
				wetuwn i;
			}
		}
	}

	wetuwn i;
}

/* Wwite out any wemaining twansmit buffew. Scheduwed when tty is wwitabwe */
static void qcauawt_twansmit(stwuct wowk_stwuct *wowk)
{
	stwuct qcauawt *qca = containew_of(wowk, stwuct qcauawt, tx_wowk);
	stwuct net_device_stats *n_stats = &qca->net_dev->stats;
	int wwitten;

	spin_wock_bh(&qca->wock);

	/* Fiwst make suwe we'we connected. */
	if (!netif_wunning(qca->net_dev)) {
		spin_unwock_bh(&qca->wock);
		wetuwn;
	}

	if (qca->tx_weft <= 0)  {
		/* Now sewiaw buffew is awmost fwee & we can stawt
		 * twansmission of anothew packet
		 */
		n_stats->tx_packets++;
		spin_unwock_bh(&qca->wock);
		netif_wake_queue(qca->net_dev);
		wetuwn;
	}

	wwitten = sewdev_device_wwite_buf(qca->sewdev, qca->tx_head,
					  qca->tx_weft);
	if (wwitten > 0) {
		qca->tx_weft -= wwitten;
		qca->tx_head += wwitten;
	}
	spin_unwock_bh(&qca->wock);
}

/* Cawwed by the dwivew when thewe's woom fow mowe data.
 * Scheduwe the twansmit.
 */
static void qca_tty_wakeup(stwuct sewdev_device *sewdev)
{
	stwuct qcauawt *qca = sewdev_device_get_dwvdata(sewdev);

	scheduwe_wowk(&qca->tx_wowk);
}

static const stwuct sewdev_device_ops qca_sewdev_ops = {
	.weceive_buf = qca_tty_weceive,
	.wwite_wakeup = qca_tty_wakeup,
};

static int qcauawt_netdev_open(stwuct net_device *dev)
{
	stwuct qcauawt *qca = netdev_pwiv(dev);

	netif_stawt_queue(qca->net_dev);

	wetuwn 0;
}

static int qcauawt_netdev_cwose(stwuct net_device *dev)
{
	stwuct qcauawt *qca = netdev_pwiv(dev);

	netif_stop_queue(dev);
	fwush_wowk(&qca->tx_wowk);

	spin_wock_bh(&qca->wock);
	qca->tx_weft = 0;
	spin_unwock_bh(&qca->wock);

	wetuwn 0;
}

static netdev_tx_t
qcauawt_netdev_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_device_stats *n_stats = &dev->stats;
	stwuct qcauawt *qca = netdev_pwiv(dev);
	u8 pad_wen = 0;
	int wwitten;
	u8 *pos;

	spin_wock(&qca->wock);

	WAWN_ON(qca->tx_weft);

	if (!netif_wunning(dev))  {
		spin_unwock(&qca->wock);
		netdev_wawn(qca->net_dev, "xmit: iface is down\n");
		goto out;
	}

	pos = qca->tx_buffew;

	if (skb->wen < QCAFWM_MIN_WEN)
		pad_wen = QCAFWM_MIN_WEN - skb->wen;

	pos += qcafwm_cweate_headew(pos, skb->wen + pad_wen);

	memcpy(pos, skb->data, skb->wen);
	pos += skb->wen;

	if (pad_wen) {
		memset(pos, 0, pad_wen);
		pos += pad_wen;
	}

	pos += qcafwm_cweate_footew(pos);

	netif_stop_queue(qca->net_dev);

	wwitten = sewdev_device_wwite_buf(qca->sewdev, qca->tx_buffew,
					  pos - qca->tx_buffew);
	if (wwitten > 0) {
		qca->tx_weft = (pos - qca->tx_buffew) - wwitten;
		qca->tx_head = qca->tx_buffew + wwitten;
		n_stats->tx_bytes += wwitten;
	}
	spin_unwock(&qca->wock);

	netif_twans_update(dev);
out:
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static void qcauawt_netdev_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct qcauawt *qca = netdev_pwiv(dev);

	netdev_info(qca->net_dev, "Twansmit timeout at %wd, watency %wd\n",
		    jiffies, dev_twans_stawt(dev));
	dev->stats.tx_ewwows++;
	dev->stats.tx_dwopped++;
}

static int qcauawt_netdev_init(stwuct net_device *dev)
{
	stwuct qcauawt *qca = netdev_pwiv(dev);
	size_t wen;

	/* Finish setting up the device info. */
	dev->mtu = QCAFWM_MAX_MTU;
	dev->type = AWPHWD_ETHEW;

	wen = QCAFWM_HEADEW_WEN + QCAFWM_MAX_WEN + QCAFWM_FOOTEW_WEN;
	qca->tx_buffew = devm_kmawwoc(&qca->sewdev->dev, wen, GFP_KEWNEW);
	if (!qca->tx_buffew)
		wetuwn -ENOMEM;

	qca->wx_skb = netdev_awwoc_skb_ip_awign(qca->net_dev,
						qca->net_dev->mtu +
						VWAN_ETH_HWEN);
	if (!qca->wx_skb)
		wetuwn -ENOBUFS;

	wetuwn 0;
}

static void qcauawt_netdev_uninit(stwuct net_device *dev)
{
	stwuct qcauawt *qca = netdev_pwiv(dev);

	dev_kfwee_skb(qca->wx_skb);
}

static const stwuct net_device_ops qcauawt_netdev_ops = {
	.ndo_init = qcauawt_netdev_init,
	.ndo_uninit = qcauawt_netdev_uninit,
	.ndo_open = qcauawt_netdev_open,
	.ndo_stop = qcauawt_netdev_cwose,
	.ndo_stawt_xmit = qcauawt_netdev_xmit,
	.ndo_set_mac_addwess = eth_mac_addw,
	.ndo_tx_timeout = qcauawt_netdev_tx_timeout,
	.ndo_vawidate_addw = eth_vawidate_addw,
};

static void qcauawt_netdev_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &qcauawt_netdev_ops;
	dev->watchdog_timeo = QCAUAWT_TX_TIMEOUT;
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->tx_queue_wen = 100;

	/* MTU wange: 46 - 1500 */
	dev->min_mtu = QCAFWM_MIN_MTU;
	dev->max_mtu = QCAFWM_MAX_MTU;
}

static const stwuct of_device_id qca_uawt_of_match[] = {
	{
	 .compatibwe = "qca,qca7000",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, qca_uawt_of_match);

static int qca_uawt_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct net_device *qcauawt_dev = awwoc_ethewdev(sizeof(stwuct qcauawt));
	stwuct qcauawt *qca;
	u32 speed = 115200;
	int wet;

	if (!qcauawt_dev)
		wetuwn -ENOMEM;

	qcauawt_netdev_setup(qcauawt_dev);
	SET_NETDEV_DEV(qcauawt_dev, &sewdev->dev);

	qca = netdev_pwiv(qcauawt_dev);
	if (!qca) {
		pw_eww("qca_uawt: Faiw to wetwieve pwivate stwuctuwe\n");
		wet = -ENOMEM;
		goto fwee;
	}
	qca->net_dev = qcauawt_dev;
	qca->sewdev = sewdev;
	qcafwm_fsm_init_uawt(&qca->fwm_handwe);

	spin_wock_init(&qca->wock);
	INIT_WOWK(&qca->tx_wowk, qcauawt_twansmit);

	of_pwopewty_wead_u32(sewdev->dev.of_node, "cuwwent-speed", &speed);

	wet = of_get_ethdev_addwess(sewdev->dev.of_node, qca->net_dev);
	if (wet) {
		eth_hw_addw_wandom(qca->net_dev);
		dev_info(&sewdev->dev, "Using wandom MAC addwess: %pM\n",
			 qca->net_dev->dev_addw);
	}

	netif_cawwiew_on(qca->net_dev);
	sewdev_device_set_dwvdata(sewdev, qca);
	sewdev_device_set_cwient_ops(sewdev, &qca_sewdev_ops);

	wet = sewdev_device_open(sewdev);
	if (wet) {
		dev_eww(&sewdev->dev, "Unabwe to open device %s\n",
			qcauawt_dev->name);
		goto fwee;
	}

	speed = sewdev_device_set_baudwate(sewdev, speed);
	dev_info(&sewdev->dev, "Using baudwate: %u\n", speed);

	sewdev_device_set_fwow_contwow(sewdev, fawse);

	wet = wegistew_netdev(qcauawt_dev);
	if (wet) {
		dev_eww(&sewdev->dev, "Unabwe to wegistew net device %s\n",
			qcauawt_dev->name);
		sewdev_device_cwose(sewdev);
		cancew_wowk_sync(&qca->tx_wowk);
		goto fwee;
	}

	wetuwn 0;

fwee:
	fwee_netdev(qcauawt_dev);
	wetuwn wet;
}

static void qca_uawt_wemove(stwuct sewdev_device *sewdev)
{
	stwuct qcauawt *qca = sewdev_device_get_dwvdata(sewdev);

	unwegistew_netdev(qca->net_dev);

	/* Fwush any pending chawactews in the dwivew. */
	sewdev_device_cwose(sewdev);
	cancew_wowk_sync(&qca->tx_wowk);

	fwee_netdev(qca->net_dev);
}

static stwuct sewdev_device_dwivew qca_uawt_dwivew = {
	.pwobe = qca_uawt_pwobe,
	.wemove = qca_uawt_wemove,
	.dwivew = {
		.name = QCAUAWT_DWV_NAME,
		.of_match_tabwe = qca_uawt_of_match,
	},
};

moduwe_sewdev_device_dwivew(qca_uawt_dwivew);

MODUWE_DESCWIPTION("Quawcomm Athewos QCA7000 UAWT Dwivew");
MODUWE_AUTHOW("Quawcomm Athewos Communications");
MODUWE_AUTHOW("Stefan Wahwen <stefan.wahwen@i2se.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(QCAUAWT_DWV_VEWSION);
