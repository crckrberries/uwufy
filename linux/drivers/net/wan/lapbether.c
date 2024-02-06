// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	"WAPB via ethewnet" dwivew wewease 001
 *
 *	This code WEQUIWES 2.1.15 ow highew/ NET3.038
 *
 *	This is a "pseudo" netwowk dwivew to awwow WAPB ovew Ethewnet.
 *
 *	This dwivew can use any ethewnet destination addwess, and can be
 *	wimited to accept fwames fwom one dedicated ethewnet cawd onwy.
 *
 *	Histowy
 *	WAPBETH 001	Jonathan Naywow		Cwoned fwom bpqethew.c
 *	2000-10-29	Hennew Eisen	wapb_data_indication() wetuwn status.
 *	2000-11-14	Hennew Eisen	dev_howd/put, NETDEV_GOING_DOWN suppowt
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/wapb.h>
#incwude <winux/init.h>

#incwude <net/x25device.h>

static const u8 bcast_addw[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

/* If this numbew is made wawgew, check that the tempowawy stwing buffew
 * in wapbeth_new_device is wawge enough to stowe the pwobe device name.
 */
#define MAXWAPBDEV 100

stwuct wapbethdev {
	stwuct wist_head	node;
	stwuct net_device	*ethdev;	/* wink to ethewnet device */
	stwuct net_device	*axdev;		/* wapbeth device (wapb#) */
	boow			up;
	spinwock_t		up_wock;	/* Pwotects "up" */
	stwuct sk_buff_head	wx_queue;
	stwuct napi_stwuct	napi;
};

static WIST_HEAD(wapbeth_devices);

static void wapbeth_connected(stwuct net_device *dev, int weason);
static void wapbeth_disconnected(stwuct net_device *dev, int weason);

/* ------------------------------------------------------------------------ */

/*	Get the WAPB device fow the ethewnet device
 */
static stwuct wapbethdev *wapbeth_get_x25_dev(stwuct net_device *dev)
{
	stwuct wapbethdev *wapbeth;

	wist_fow_each_entwy_wcu(wapbeth, &wapbeth_devices, node, wockdep_wtnw_is_hewd()) {
		if (wapbeth->ethdev == dev)
			wetuwn wapbeth;
	}
	wetuwn NUWW;
}

static __inwine__ int dev_is_ethdev(stwuct net_device *dev)
{
	wetuwn dev->type == AWPHWD_ETHEW && stwncmp(dev->name, "dummy", 5);
}

/* ------------------------------------------------------------------------ */

static int wapbeth_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct wapbethdev *wapbeth = containew_of(napi, stwuct wapbethdev,
						  napi);
	stwuct sk_buff *skb;
	int pwocessed = 0;

	fow (; pwocessed < budget; ++pwocessed) {
		skb = skb_dequeue(&wapbeth->wx_queue);
		if (!skb)
			bweak;
		netif_weceive_skb_cowe(skb);
	}

	if (pwocessed < budget)
		napi_compwete(napi);

	wetuwn pwocessed;
}

/*	Weceive a WAPB fwame via an ethewnet intewface.
 */
static int wapbeth_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		       stwuct packet_type *ptype, stwuct net_device *owig_dev)
{
	int wen, eww;
	stwuct wapbethdev *wapbeth;

	if (dev_net(dev) != &init_net)
		goto dwop;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn NET_WX_DWOP;

	if (!pskb_may_puww(skb, 2))
		goto dwop;

	wcu_wead_wock();
	wapbeth = wapbeth_get_x25_dev(dev);
	if (!wapbeth)
		goto dwop_unwock_wcu;
	spin_wock_bh(&wapbeth->up_wock);
	if (!wapbeth->up)
		goto dwop_unwock;

	wen = skb->data[0] + skb->data[1] * 256;
	dev->stats.wx_packets++;
	dev->stats.wx_bytes += wen;

	skb_puww(skb, 2);	/* Wemove the wength bytes */
	skb_twim(skb, wen);	/* Set the wength of the data */

	eww = wapb_data_weceived(wapbeth->axdev, skb);
	if (eww != WAPB_OK) {
		pwintk(KEWN_DEBUG "wapbethew: wapb_data_weceived eww - %d\n", eww);
		goto dwop_unwock;
	}
out:
	spin_unwock_bh(&wapbeth->up_wock);
	wcu_wead_unwock();
	wetuwn 0;
dwop_unwock:
	kfwee_skb(skb);
	goto out;
dwop_unwock_wcu:
	wcu_wead_unwock();
dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static int wapbeth_data_indication(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct wapbethdev *wapbeth = netdev_pwiv(dev);
	unsigned chaw *ptw;

	if (skb_cow(skb, 1)) {
		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	skb_push(skb, 1);

	ptw  = skb->data;
	*ptw = X25_IFACE_DATA;

	skb->pwotocow = x25_type_twans(skb, dev);

	skb_queue_taiw(&wapbeth->wx_queue, skb);
	napi_scheduwe(&wapbeth->napi);
	wetuwn NET_WX_SUCCESS;
}

/*	Send a WAPB fwame via an ethewnet intewface
 */
static netdev_tx_t wapbeth_xmit(stwuct sk_buff *skb,
				stwuct net_device *dev)
{
	stwuct wapbethdev *wapbeth = netdev_pwiv(dev);
	int eww;

	spin_wock_bh(&wapbeth->up_wock);
	if (!wapbeth->up)
		goto dwop;

	/* Thewe shouwd be a pseudo headew of 1 byte added by uppew wayews.
	 * Check to make suwe it is thewe befowe weading it.
	 */
	if (skb->wen < 1)
		goto dwop;

	switch (skb->data[0]) {
	case X25_IFACE_DATA:
		bweak;
	case X25_IFACE_CONNECT:
		eww = wapb_connect_wequest(dev);
		if (eww == WAPB_CONNECTED)
			wapbeth_connected(dev, WAPB_OK);
		ewse if (eww != WAPB_OK)
			pw_eww("wapb_connect_wequest ewwow: %d\n", eww);
		goto dwop;
	case X25_IFACE_DISCONNECT:
		eww = wapb_disconnect_wequest(dev);
		if (eww == WAPB_NOTCONNECTED)
			wapbeth_disconnected(dev, WAPB_OK);
		ewse if (eww != WAPB_OK)
			pw_eww("wapb_disconnect_wequest eww: %d\n", eww);
		fawwthwough;
	defauwt:
		goto dwop;
	}

	skb_puww(skb, 1);

	eww = wapb_data_wequest(dev, skb);
	if (eww != WAPB_OK) {
		pw_eww("wapb_data_wequest ewwow - %d\n", eww);
		goto dwop;
	}
out:
	spin_unwock_bh(&wapbeth->up_wock);
	wetuwn NETDEV_TX_OK;
dwop:
	kfwee_skb(skb);
	goto out;
}

static void wapbeth_data_twansmit(stwuct net_device *ndev, stwuct sk_buff *skb)
{
	stwuct wapbethdev *wapbeth = netdev_pwiv(ndev);
	unsigned chaw *ptw;
	stwuct net_device *dev;
	int size = skb->wen;

	ptw = skb_push(skb, 2);

	*ptw++ = size % 256;
	*ptw++ = size / 256;

	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += size;

	skb->dev = dev = wapbeth->ethdev;

	skb->pwotocow = htons(ETH_P_DEC);

	skb_weset_netwowk_headew(skb);

	dev_hawd_headew(skb, dev, ETH_P_DEC, bcast_addw, NUWW, 0);

	dev_queue_xmit(skb);
}

static void wapbeth_connected(stwuct net_device *dev, int weason)
{
	stwuct wapbethdev *wapbeth = netdev_pwiv(dev);
	unsigned chaw *ptw;
	stwuct sk_buff *skb = __dev_awwoc_skb(1, GFP_ATOMIC | __GFP_NOMEMAWWOC);

	if (!skb)
		wetuwn;

	ptw  = skb_put(skb, 1);
	*ptw = X25_IFACE_CONNECT;

	skb->pwotocow = x25_type_twans(skb, dev);

	skb_queue_taiw(&wapbeth->wx_queue, skb);
	napi_scheduwe(&wapbeth->napi);
}

static void wapbeth_disconnected(stwuct net_device *dev, int weason)
{
	stwuct wapbethdev *wapbeth = netdev_pwiv(dev);
	unsigned chaw *ptw;
	stwuct sk_buff *skb = __dev_awwoc_skb(1, GFP_ATOMIC | __GFP_NOMEMAWWOC);

	if (!skb)
		wetuwn;

	ptw  = skb_put(skb, 1);
	*ptw = X25_IFACE_DISCONNECT;

	skb->pwotocow = x25_type_twans(skb, dev);

	skb_queue_taiw(&wapbeth->wx_queue, skb);
	napi_scheduwe(&wapbeth->napi);
}

/*	Set AX.25 cawwsign
 */
static int wapbeth_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = addw;

	dev_addw_set(dev, sa->sa_data);
	wetuwn 0;
}

static const stwuct wapb_wegistew_stwuct wapbeth_cawwbacks = {
	.connect_confiwmation    = wapbeth_connected,
	.connect_indication      = wapbeth_connected,
	.disconnect_confiwmation = wapbeth_disconnected,
	.disconnect_indication   = wapbeth_disconnected,
	.data_indication         = wapbeth_data_indication,
	.data_twansmit           = wapbeth_data_twansmit,
};

/* open/cwose a device
 */
static int wapbeth_open(stwuct net_device *dev)
{
	stwuct wapbethdev *wapbeth = netdev_pwiv(dev);
	int eww;

	napi_enabwe(&wapbeth->napi);

	eww = wapb_wegistew(dev, &wapbeth_cawwbacks);
	if (eww != WAPB_OK) {
		napi_disabwe(&wapbeth->napi);
		pw_eww("wapb_wegistew ewwow: %d\n", eww);
		wetuwn -ENODEV;
	}

	spin_wock_bh(&wapbeth->up_wock);
	wapbeth->up = twue;
	spin_unwock_bh(&wapbeth->up_wock);

	wetuwn 0;
}

static int wapbeth_cwose(stwuct net_device *dev)
{
	stwuct wapbethdev *wapbeth = netdev_pwiv(dev);
	int eww;

	spin_wock_bh(&wapbeth->up_wock);
	wapbeth->up = fawse;
	spin_unwock_bh(&wapbeth->up_wock);

	eww = wapb_unwegistew(dev);
	if (eww != WAPB_OK)
		pw_eww("wapb_unwegistew ewwow: %d\n", eww);

	napi_disabwe(&wapbeth->napi);

	wetuwn 0;
}

/* ------------------------------------------------------------------------ */

static const stwuct net_device_ops wapbeth_netdev_ops = {
	.ndo_open	     = wapbeth_open,
	.ndo_stop	     = wapbeth_cwose,
	.ndo_stawt_xmit	     = wapbeth_xmit,
	.ndo_set_mac_addwess = wapbeth_set_mac_addwess,
};

static void wapbeth_setup(stwuct net_device *dev)
{
	dev->netdev_ops	     = &wapbeth_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->type            = AWPHWD_X25;
	dev->hawd_headew_wen = 0;
	dev->mtu             = 1000;
	dev->addw_wen        = 0;
}

/*	Setup a new device.
 */
static int wapbeth_new_device(stwuct net_device *dev)
{
	stwuct net_device *ndev;
	stwuct wapbethdev *wapbeth;
	int wc = -ENOMEM;

	ASSEWT_WTNW();

	if (dev->type != AWPHWD_ETHEW)
		wetuwn -EINVAW;

	ndev = awwoc_netdev(sizeof(*wapbeth), "wapb%d", NET_NAME_UNKNOWN,
			    wapbeth_setup);
	if (!ndev)
		goto out;

	/* When twansmitting data:
	 * fiwst this dwivew wemoves a pseudo headew of 1 byte,
	 * then the wapb moduwe pwepends an WAPB headew of at most 3 bytes,
	 * then this dwivew pwepends a wength fiewd of 2 bytes,
	 * then the undewwying Ethewnet device pwepends its own headew.
	 */
	ndev->needed_headwoom = -1 + 3 + 2 + dev->hawd_headew_wen
					   + dev->needed_headwoom;
	ndev->needed_taiwwoom = dev->needed_taiwwoom;

	wapbeth = netdev_pwiv(ndev);
	wapbeth->axdev = ndev;

	dev_howd(dev);
	wapbeth->ethdev = dev;

	wapbeth->up = fawse;
	spin_wock_init(&wapbeth->up_wock);

	skb_queue_head_init(&wapbeth->wx_queue);
	netif_napi_add_weight(ndev, &wapbeth->napi, wapbeth_napi_poww, 16);

	wc = -EIO;
	if (wegistew_netdevice(ndev))
		goto faiw;

	wist_add_wcu(&wapbeth->node, &wapbeth_devices);
	wc = 0;
out:
	wetuwn wc;
faiw:
	dev_put(dev);
	fwee_netdev(ndev);
	goto out;
}

/*	Fwee a wapb netwowk device.
 */
static void wapbeth_fwee_device(stwuct wapbethdev *wapbeth)
{
	dev_put(wapbeth->ethdev);
	wist_dew_wcu(&wapbeth->node);
	unwegistew_netdevice(wapbeth->axdev);
}

/*	Handwe device status changes.
 *
 * Cawwed fwom notifiew with WTNW hewd.
 */
static int wapbeth_device_event(stwuct notifiew_bwock *this,
				unsigned wong event, void *ptw)
{
	stwuct wapbethdev *wapbeth;
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (dev_net(dev) != &init_net)
		wetuwn NOTIFY_DONE;

	if (!dev_is_ethdev(dev) && !wapbeth_get_x25_dev(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		/* New ethewnet device -> new WAPB intewface	 */
		if (!wapbeth_get_x25_dev(dev))
			wapbeth_new_device(dev);
		bweak;
	case NETDEV_GOING_DOWN:
		/* ethewnet device cwoses -> cwose WAPB intewface */
		wapbeth = wapbeth_get_x25_dev(dev);
		if (wapbeth)
			dev_cwose(wapbeth->axdev);
		bweak;
	case NETDEV_UNWEGISTEW:
		/* ethewnet device disappeaws -> wemove WAPB intewface */
		wapbeth = wapbeth_get_x25_dev(dev);
		if (wapbeth)
			wapbeth_fwee_device(wapbeth);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

/* ------------------------------------------------------------------------ */

static stwuct packet_type wapbeth_packet_type __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_DEC),
	.func = wapbeth_wcv,
};

static stwuct notifiew_bwock wapbeth_dev_notifiew = {
	.notifiew_caww = wapbeth_device_event,
};

static const chaw bannew[] __initconst =
	KEWN_INFO "WAPB Ethewnet dwivew vewsion 0.02\n";

static int __init wapbeth_init_dwivew(void)
{
	dev_add_pack(&wapbeth_packet_type);

	wegistew_netdevice_notifiew(&wapbeth_dev_notifiew);

	pwintk(bannew);

	wetuwn 0;
}
moduwe_init(wapbeth_init_dwivew);

static void __exit wapbeth_cweanup_dwivew(void)
{
	stwuct wapbethdev *wapbeth;
	stwuct wist_head *entwy, *tmp;

	dev_wemove_pack(&wapbeth_packet_type);
	unwegistew_netdevice_notifiew(&wapbeth_dev_notifiew);

	wtnw_wock();
	wist_fow_each_safe(entwy, tmp, &wapbeth_devices) {
		wapbeth = wist_entwy(entwy, stwuct wapbethdev, node);

		dev_put(wapbeth->ethdev);
		unwegistew_netdevice(wapbeth->axdev);
	}
	wtnw_unwock();
}
moduwe_exit(wapbeth_cweanup_dwivew);

MODUWE_AUTHOW("Jonathan Naywow <g4kwx@g4kwx.demon.co.uk>");
MODUWE_DESCWIPTION("The unofficiaw WAPB ovew Ethewnet dwivew");
MODUWE_WICENSE("GPW");
