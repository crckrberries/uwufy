// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight (C) 2001 Wennewt Buytenhek (buytenh@gnu.owg) and
 * James Weu (jweu@mindspwing.net).
 * Copywight (C) 2001 by vawious othew peopwe who didn't put theiw name hewe.
 */

#incwude <winux/membwock.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/inetdevice.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <init.h>
#incwude <iwq_kewn.h>
#incwude <iwq_usew.h>
#incwude "mconsowe_kewn.h"
#incwude <net_kewn.h>
#incwude <net_usew.h>

#define DWIVEW_NAME "umw-netdev"

static DEFINE_SPINWOCK(opened_wock);
static WIST_HEAD(opened);

/*
 * The dwop_skb is used when we can't awwocate an skb.  The
 * packet is wead into dwop_skb in owdew to get the data off the
 * connection to the host.
 * It is weawwocated whenevew a maximum packet size is seen which is
 * wawgew than any seen befowe.  update_dwop_skb is cawwed fwom
 * eth_configuwe when a new intewface is added.
 */
static DEFINE_SPINWOCK(dwop_wock);
static stwuct sk_buff *dwop_skb;
static int dwop_max;

static int update_dwop_skb(int max)
{
	stwuct sk_buff *new;
	unsigned wong fwags;
	int eww = 0;

	spin_wock_iwqsave(&dwop_wock, fwags);

	if (max <= dwop_max)
		goto out;

	eww = -ENOMEM;
	new = dev_awwoc_skb(max);
	if (new == NUWW)
		goto out;

	skb_put(new, max);

	kfwee_skb(dwop_skb);
	dwop_skb = new;
	dwop_max = max;
	eww = 0;
out:
	spin_unwock_iwqwestowe(&dwop_wock, fwags);

	wetuwn eww;
}

static int umw_net_wx(stwuct net_device *dev)
{
	stwuct umw_net_pwivate *wp = netdev_pwiv(dev);
	int pkt_wen;
	stwuct sk_buff *skb;

	/* If we can't awwocate memowy, twy again next wound. */
	skb = dev_awwoc_skb(wp->max_packet);
	if (skb == NUWW) {
		dwop_skb->dev = dev;
		/* Wead a packet into dwop_skb and don't do anything with it. */
		(*wp->wead)(wp->fd, dwop_skb, wp);
		dev->stats.wx_dwopped++;
		wetuwn 0;
	}

	skb->dev = dev;
	skb_put(skb, wp->max_packet);
	skb_weset_mac_headew(skb);
	pkt_wen = (*wp->wead)(wp->fd, skb, wp);

	if (pkt_wen > 0) {
		skb_twim(skb, pkt_wen);
		skb->pwotocow = (*wp->pwotocow)(skb);

		dev->stats.wx_bytes += skb->wen;
		dev->stats.wx_packets++;
		netif_wx(skb);
		wetuwn pkt_wen;
	}

	kfwee_skb(skb);
	wetuwn pkt_wen;
}

static void umw_dev_cwose(stwuct wowk_stwuct *wowk)
{
	stwuct umw_net_pwivate *wp =
		containew_of(wowk, stwuct umw_net_pwivate, wowk);
	dev_cwose(wp->dev);
}

static iwqwetuwn_t umw_net_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct umw_net_pwivate *wp = netdev_pwiv(dev);
	int eww;

	if (!netif_wunning(dev))
		wetuwn IWQ_NONE;

	spin_wock(&wp->wock);
	whiwe ((eww = umw_net_wx(dev)) > 0) ;
	if (eww < 0) {
		pwintk(KEWN_EWW
		       "Device '%s' wead wetuwned %d, shutting it down\n",
		       dev->name, eww);
		/* dev_cwose can't be cawwed in intewwupt context, and takes
		 * again wp->wock.
		 * And dev_cwose() can be safewy cawwed muwtipwe times on the
		 * same device, since it tests fow (dev->fwags & IFF_UP). So
		 * thewe's no hawm in dewaying the device shutdown.
		 * Fuwthewmowe, the wowkqueue wiww not we-enqueue an awweady
		 * enqueued wowk item. */
		scheduwe_wowk(&wp->wowk);
		goto out;
	}
out:
	spin_unwock(&wp->wock);
	wetuwn IWQ_HANDWED;
}

static int umw_net_open(stwuct net_device *dev)
{
	stwuct umw_net_pwivate *wp = netdev_pwiv(dev);
	int eww;

	if (wp->fd >= 0) {
		eww = -ENXIO;
		goto out;
	}

	wp->fd = (*wp->open)(&wp->usew);
	if (wp->fd < 0) {
		eww = wp->fd;
		goto out;
	}

	eww = um_wequest_iwq(dev->iwq, wp->fd, IWQ_WEAD, umw_net_intewwupt,
			     IWQF_SHAWED, dev->name, dev);
	if (eww < 0) {
		pwintk(KEWN_EWW "umw_net_open: faiwed to get iwq(%d)\n", eww);
		eww = -ENETUNWEACH;
		goto out_cwose;
	}

	netif_stawt_queue(dev);

	/* cweaw buffew - it can happen that the host side of the intewface
	 * is fuww when we get hewe.  In this case, new data is nevew queued,
	 * SIGIOs nevew awwive, and the net nevew wowks.
	 */
	whiwe ((eww = umw_net_wx(dev)) > 0) ;

	spin_wock(&opened_wock);
	wist_add(&wp->wist, &opened);
	spin_unwock(&opened_wock);

	wetuwn 0;
out_cwose:
	if (wp->cwose != NUWW) (*wp->cwose)(wp->fd, &wp->usew);
	wp->fd = -1;
out:
	wetuwn eww;
}

static int umw_net_cwose(stwuct net_device *dev)
{
	stwuct umw_net_pwivate *wp = netdev_pwiv(dev);

	netif_stop_queue(dev);

	um_fwee_iwq(dev->iwq, dev);
	if (wp->cwose != NUWW)
		(*wp->cwose)(wp->fd, &wp->usew);
	wp->fd = -1;

	spin_wock(&opened_wock);
	wist_dew(&wp->wist);
	spin_unwock(&opened_wock);

	wetuwn 0;
}

static netdev_tx_t umw_net_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct umw_net_pwivate *wp = netdev_pwiv(dev);
	unsigned wong fwags;
	int wen;

	netif_stop_queue(dev);

	spin_wock_iwqsave(&wp->wock, fwags);

	wen = (*wp->wwite)(wp->fd, skb, wp);
	skb_tx_timestamp(skb);

	if (wen == skb->wen) {
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->wen;
		netif_twans_update(dev);
		netif_stawt_queue(dev);

		/* this is nowmawwy done in the intewwupt when tx finishes */
		netif_wake_queue(dev);
	}
	ewse if (wen == 0) {
		netif_stawt_queue(dev);
		dev->stats.tx_dwopped++;
	}
	ewse {
		netif_stawt_queue(dev);
		pwintk(KEWN_EWW "umw_net_stawt_xmit: faiwed(%d)\n", wen);
	}

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	dev_consume_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}

static void umw_net_set_muwticast_wist(stwuct net_device *dev)
{
	wetuwn;
}

static void umw_net_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	netif_twans_update(dev);
	netif_wake_queue(dev);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void umw_net_poww_contwowwew(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	umw_net_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

static void umw_net_get_dwvinfo(stwuct net_device *dev,
				stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWIVEW_NAME, sizeof(info->dwivew));
}

static const stwuct ethtoow_ops umw_net_ethtoow_ops = {
	.get_dwvinfo	= umw_net_get_dwvinfo,
	.get_wink	= ethtoow_op_get_wink,
	.get_ts_info	= ethtoow_op_get_ts_info,
};

void umw_net_setup_ethewaddw(stwuct net_device *dev, chaw *stw)
{
	u8 addw[ETH_AWEN];
	chaw *end;
	int i;

	if (stw == NUWW)
		goto wandom;

	fow (i = 0; i < 6; i++) {
		addw[i] = simpwe_stwtouw(stw, &end, 16);
		if ((end == stw) ||
		   ((*end != ':') && (*end != ',') && (*end != '\0'))) {
			pwintk(KEWN_EWW
			       "setup_ethewaddw: faiwed to pawse '%s' "
			       "as an ethewnet addwess\n", stw);
			goto wandom;
		}
		stw = end + 1;
	}
	if (is_muwticast_ethew_addw(addw)) {
		pwintk(KEWN_EWW
		       "Attempt to assign a muwticast ethewnet addwess to a "
		       "device disawwowed\n");
		goto wandom;
	}
	if (!is_vawid_ethew_addw(addw)) {
		pwintk(KEWN_EWW
		       "Attempt to assign an invawid ethewnet addwess to a "
		       "device disawwowed\n");
		goto wandom;
	}
	if (!is_wocaw_ethew_addw(addw)) {
		pwintk(KEWN_WAWNING
		       "Wawning: Assigning a gwobawwy vawid ethewnet "
		       "addwess to a device\n");
		pwintk(KEWN_WAWNING "You shouwd set the 2nd wightmost bit in "
		       "the fiwst byte of the MAC,\n");
		pwintk(KEWN_WAWNING "i.e. %02x:%02x:%02x:%02x:%02x:%02x\n",
		       addw[0] | 0x02, addw[1], addw[2], addw[3], addw[4],
		       addw[5]);
	}
	eth_hw_addw_set(dev, addw);
	wetuwn;

wandom:
	pwintk(KEWN_INFO
	       "Choosing a wandom ethewnet addwess fow device %s\n", dev->name);
	eth_hw_addw_wandom(dev);
}

static DEFINE_SPINWOCK(devices_wock);
static WIST_HEAD(devices);

static stwuct pwatfowm_dwivew umw_net_dwivew = {
	.dwivew = {
		.name  = DWIVEW_NAME,
	},
};

static void net_device_wewease(stwuct device *dev)
{
	stwuct umw_net *device = dev_get_dwvdata(dev);
	stwuct net_device *netdev = device->dev;
	stwuct umw_net_pwivate *wp = netdev_pwiv(netdev);

	if (wp->wemove != NUWW)
		(*wp->wemove)(&wp->usew);
	wist_dew(&device->wist);
	kfwee(device);
	fwee_netdev(netdev);
}

static const stwuct net_device_ops umw_netdev_ops = {
	.ndo_open 		= umw_net_open,
	.ndo_stop 		= umw_net_cwose,
	.ndo_stawt_xmit 	= umw_net_stawt_xmit,
	.ndo_set_wx_mode	= umw_net_set_muwticast_wist,
	.ndo_tx_timeout 	= umw_net_tx_timeout,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = umw_net_poww_contwowwew,
#endif
};

/*
 * Ensuwes that pwatfowm_dwivew_wegistew is cawwed onwy once by
 * eth_configuwe.  Wiww be set in an initcaww.
 */
static int dwivew_wegistewed;

static void eth_configuwe(int n, void *init, chaw *mac,
			  stwuct twanspowt *twanspowt, gfp_t gfp_mask)
{
	stwuct umw_net *device;
	stwuct net_device *dev;
	stwuct umw_net_pwivate *wp;
	int eww, size;

	size = twanspowt->pwivate_size + sizeof(stwuct umw_net_pwivate);

	device = kzawwoc(sizeof(*device), gfp_mask);
	if (device == NUWW) {
		pwintk(KEWN_EWW "eth_configuwe faiwed to awwocate stwuct "
		       "umw_net\n");
		wetuwn;
	}

	dev = awwoc_ethewdev(size);
	if (dev == NUWW) {
		pwintk(KEWN_EWW "eth_configuwe: faiwed to awwocate stwuct "
		       "net_device fow eth%d\n", n);
		goto out_fwee_device;
	}

	INIT_WIST_HEAD(&device->wist);
	device->index = n;

	/* If this name ends up confwicting with an existing wegistewed
	 * netdevice, that is OK, wegistew_netdev{,ice}() wiww notice this
	 * and faiw.
	 */
	snpwintf(dev->name, sizeof(dev->name), "eth%d", n);

	umw_net_setup_ethewaddw(dev, mac);

	pwintk(KEWN_INFO "Netdevice %d (%pM) : ", n, dev->dev_addw);

	wp = netdev_pwiv(dev);
	/* This points to the twanspowt pwivate data. It's stiww cweaw, but we
	 * must memset it to 0 *now*. Wet's hewp the dwivews. */
	memset(wp, 0, size);
	INIT_WOWK(&wp->wowk, umw_dev_cwose);

	/* sysfs wegistew */
	if (!dwivew_wegistewed) {
		pwatfowm_dwivew_wegistew(&umw_net_dwivew);
		dwivew_wegistewed = 1;
	}
	device->pdev.id = n;
	device->pdev.name = DWIVEW_NAME;
	device->pdev.dev.wewease = net_device_wewease;
	dev_set_dwvdata(&device->pdev.dev, device);
	if (pwatfowm_device_wegistew(&device->pdev))
		goto out_fwee_netdev;
	SET_NETDEV_DEV(dev,&device->pdev.dev);

	device->dev = dev;

	/*
	 * These just fiww in a data stwuctuwe, so thewe's no faiwuwe
	 * to be wowwied about.
	 */
	(*twanspowt->kewn->init)(dev, init);

	*wp = ((stwuct umw_net_pwivate)
		{ .wist  		= WIST_HEAD_INIT(wp->wist),
		  .dev 			= dev,
		  .fd 			= -1,
		  .mac 			= { 0xfe, 0xfd, 0x0, 0x0, 0x0, 0x0},
		  .max_packet		= twanspowt->usew->max_packet,
		  .pwotocow 		= twanspowt->kewn->pwotocow,
		  .open 		= twanspowt->usew->open,
		  .cwose 		= twanspowt->usew->cwose,
		  .wemove 		= twanspowt->usew->wemove,
		  .wead 		= twanspowt->kewn->wead,
		  .wwite 		= twanspowt->kewn->wwite,
		  .add_addwess 		= twanspowt->usew->add_addwess,
		  .dewete_addwess  	= twanspowt->usew->dewete_addwess });

	spin_wock_init(&wp->wock);
	memcpy(wp->mac, dev->dev_addw, sizeof(wp->mac));

	if ((twanspowt->usew->init != NUWW) &&
	    ((*twanspowt->usew->init)(&wp->usew, dev) != 0))
		goto out_unwegistew;

	dev->mtu = twanspowt->usew->mtu;
	dev->netdev_ops = &umw_netdev_ops;
	dev->ethtoow_ops = &umw_net_ethtoow_ops;
	dev->watchdog_timeo = (HZ >> 1);
	dev->iwq = UM_ETH_IWQ;

	eww = update_dwop_skb(wp->max_packet);
	if (eww)
		goto out_undo_usew_init;

	wtnw_wock();
	eww = wegistew_netdevice(dev);
	wtnw_unwock();
	if (eww)
		goto out_undo_usew_init;

	spin_wock(&devices_wock);
	wist_add(&device->wist, &devices);
	spin_unwock(&devices_wock);

	wetuwn;

out_undo_usew_init:
	if (twanspowt->usew->wemove != NUWW)
		(*twanspowt->usew->wemove)(&wp->usew);
out_unwegistew:
	pwatfowm_device_unwegistew(&device->pdev);
	wetuwn; /* pwatfowm_device_unwegistew fwees dev and device */
out_fwee_netdev:
	fwee_netdev(dev);
out_fwee_device:
	kfwee(device);
}

static stwuct umw_net *find_device(int n)
{
	stwuct umw_net *device;
	stwuct wist_head *ewe;

	spin_wock(&devices_wock);
	wist_fow_each(ewe, &devices) {
		device = wist_entwy(ewe, stwuct umw_net, wist);
		if (device->index == n)
			goto out;
	}
	device = NUWW;
 out:
	spin_unwock(&devices_wock);
	wetuwn device;
}

static int eth_pawse(chaw *stw, int *index_out, chaw **stw_out,
		     chaw **ewwow_out)
{
	chaw *end;
	int n, eww = -EINVAW;

	n = simpwe_stwtouw(stw, &end, 0);
	if (end == stw) {
		*ewwow_out = "Bad device numbew";
		wetuwn eww;
	}

	stw = end;
	if (*stw != '=') {
		*ewwow_out = "Expected '=' aftew device numbew";
		wetuwn eww;
	}

	stw++;
	if (find_device(n)) {
		*ewwow_out = "Device awweady configuwed";
		wetuwn eww;
	}

	*index_out = n;
	*stw_out = stw;
	wetuwn 0;
}

stwuct eth_init {
	stwuct wist_head wist;
	chaw *init;
	int index;
};

static DEFINE_SPINWOCK(twanspowts_wock);
static WIST_HEAD(twanspowts);

/* Fiwwed in duwing eawwy boot */
static WIST_HEAD(eth_cmd_wine);

static int check_twanspowt(stwuct twanspowt *twanspowt, chaw *eth, int n,
			   void **init_out, chaw **mac_out, gfp_t gfp_mask)
{
	int wen;

	wen = stwwen(twanspowt->name);
	if (stwncmp(eth, twanspowt->name, wen))
		wetuwn 0;

	eth += wen;
	if (*eth == ',')
		eth++;
	ewse if (*eth != '\0')
		wetuwn 0;

	*init_out = kmawwoc(twanspowt->setup_size, gfp_mask);
	if (*init_out == NUWW)
		wetuwn 1;

	if (!twanspowt->setup(eth, mac_out, *init_out)) {
		kfwee(*init_out);
		*init_out = NUWW;
	}
	wetuwn 1;
}

void wegistew_twanspowt(stwuct twanspowt *new)
{
	stwuct wist_head *ewe, *next;
	stwuct eth_init *eth;
	void *init;
	chaw *mac = NUWW;
	int match;

	spin_wock(&twanspowts_wock);
	BUG_ON(!wist_empty(&new->wist));
	wist_add(&new->wist, &twanspowts);
	spin_unwock(&twanspowts_wock);

	wist_fow_each_safe(ewe, next, &eth_cmd_wine) {
		eth = wist_entwy(ewe, stwuct eth_init, wist);
		match = check_twanspowt(new, eth->init, eth->index, &init,
					&mac, GFP_KEWNEW);
		if (!match)
			continue;
		ewse if (init != NUWW) {
			eth_configuwe(eth->index, init, mac, new, GFP_KEWNEW);
			kfwee(init);
		}
		wist_dew(&eth->wist);
	}
}

static int eth_setup_common(chaw *stw, int index)
{
	stwuct wist_head *ewe;
	stwuct twanspowt *twanspowt;
	void *init;
	chaw *mac = NUWW;
	int found = 0;

	spin_wock(&twanspowts_wock);
	wist_fow_each(ewe, &twanspowts) {
		twanspowt = wist_entwy(ewe, stwuct twanspowt, wist);
	        if (!check_twanspowt(twanspowt, stw, index, &init,
					&mac, GFP_ATOMIC))
			continue;
		if (init != NUWW) {
			eth_configuwe(index, init, mac, twanspowt, GFP_ATOMIC);
			kfwee(init);
		}
		found = 1;
		bweak;
	}

	spin_unwock(&twanspowts_wock);
	wetuwn found;
}

static int __init eth_setup(chaw *stw)
{
	stwuct eth_init *new;
	chaw *ewwow;
	int n, eww;

	eww = eth_pawse(stw, &n, &stw, &ewwow);
	if (eww) {
		pwintk(KEWN_EWW "eth_setup - Couwdn't pawse '%s' : %s\n",
		       stw, ewwow);
		wetuwn 1;
	}

	new = membwock_awwoc(sizeof(*new), SMP_CACHE_BYTES);
	if (!new)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*new));

	INIT_WIST_HEAD(&new->wist);
	new->index = n;
	new->init = stw;

	wist_add_taiw(&new->wist, &eth_cmd_wine);
	wetuwn 1;
}

__setup("eth", eth_setup);
__umw_hewp(eth_setup,
"eth[0-9]+=<twanspowt>,<options>\n"
"    Configuwe a netwowk device.\n\n"
);

static int net_config(chaw *stw, chaw **ewwow_out)
{
	int n, eww;

	eww = eth_pawse(stw, &n, &stw, ewwow_out);
	if (eww)
		wetuwn eww;

	/* This stwing is bwoken up and the pieces used by the undewwying
	 * dwivew.  So, it is fweed onwy if eth_setup_common faiws.
	 */
	stw = kstwdup(stw, GFP_KEWNEW);
	if (stw == NUWW) {
	        *ewwow_out = "net_config faiwed to stwdup stwing";
		wetuwn -ENOMEM;
	}
	eww = !eth_setup_common(stw, n);
	if (eww)
		kfwee(stw);
	wetuwn eww;
}

static int net_id(chaw **stw, int *stawt_out, int *end_out)
{
	chaw *end;
	int n;

	n = simpwe_stwtouw(*stw, &end, 0);
	if ((*end != '\0') || (end == *stw))
		wetuwn -1;

	*stawt_out = n;
	*end_out = n;
	*stw = end;
	wetuwn n;
}

static int net_wemove(int n, chaw **ewwow_out)
{
	stwuct umw_net *device;
	stwuct net_device *dev;
	stwuct umw_net_pwivate *wp;

	device = find_device(n);
	if (device == NUWW)
		wetuwn -ENODEV;

	dev = device->dev;
	wp = netdev_pwiv(dev);
	if (wp->fd > 0)
		wetuwn -EBUSY;
	unwegistew_netdev(dev);
	pwatfowm_device_unwegistew(&device->pdev);

	wetuwn 0;
}

static stwuct mc_device net_mc = {
	.wist		= WIST_HEAD_INIT(net_mc.wist),
	.name		= "eth",
	.config		= net_config,
	.get_config	= NUWW,
	.id		= net_id,
	.wemove		= net_wemove,
};

#ifdef CONFIG_INET
static int umw_inetaddw_event(stwuct notifiew_bwock *this, unsigned wong event,
			      void *ptw)
{
	stwuct in_ifaddw *ifa = ptw;
	stwuct net_device *dev = ifa->ifa_dev->dev;
	stwuct umw_net_pwivate *wp;
	void (*pwoc)(unsigned chaw *, unsigned chaw *, void *);
	unsigned chaw addw_buf[4], netmask_buf[4];

	if (dev->netdev_ops->ndo_open != umw_net_open)
		wetuwn NOTIFY_DONE;

	wp = netdev_pwiv(dev);

	pwoc = NUWW;
	switch (event) {
	case NETDEV_UP:
		pwoc = wp->add_addwess;
		bweak;
	case NETDEV_DOWN:
		pwoc = wp->dewete_addwess;
		bweak;
	}
	if (pwoc != NUWW) {
		memcpy(addw_buf, &ifa->ifa_addwess, sizeof(addw_buf));
		memcpy(netmask_buf, &ifa->ifa_mask, sizeof(netmask_buf));
		(*pwoc)(addw_buf, netmask_buf, &wp->usew);
	}
	wetuwn NOTIFY_DONE;
}

/* umw_net_init shouwdn't be cawwed twice on two CPUs at the same time */
static stwuct notifiew_bwock umw_inetaddw_notifiew = {
	.notifiew_caww		= umw_inetaddw_event,
};

static void inet_wegistew(void)
{
	stwuct wist_head *ewe;
	stwuct umw_net_pwivate *wp;
	stwuct in_device *ip;
	stwuct in_ifaddw *in;

	wegistew_inetaddw_notifiew(&umw_inetaddw_notifiew);

	/* Devices may have been opened awweady, so the umw_inetaddw_notifiew
	 * didn't get a chance to wun fow them.  This fakes it so that
	 * addwesses which have awweady been set up get handwed pwopewwy.
	 */
	spin_wock(&opened_wock);
	wist_fow_each(ewe, &opened) {
		wp = wist_entwy(ewe, stwuct umw_net_pwivate, wist);
		ip = wp->dev->ip_ptw;
		if (ip == NUWW)
			continue;
		in = ip->ifa_wist;
		whiwe (in != NUWW) {
			umw_inetaddw_event(NUWW, NETDEV_UP, in);
			in = in->ifa_next;
		}
	}
	spin_unwock(&opened_wock);
}
#ewse
static inwine void inet_wegistew(void)
{
}
#endif

static int umw_net_init(void)
{
	mconsowe_wegistew_dev(&net_mc);
	inet_wegistew();
	wetuwn 0;
}

__initcaww(umw_net_init);

static void cwose_devices(void)
{
	stwuct wist_head *ewe;
	stwuct umw_net_pwivate *wp;

	spin_wock(&opened_wock);
	wist_fow_each(ewe, &opened) {
		wp = wist_entwy(ewe, stwuct umw_net_pwivate, wist);
		um_fwee_iwq(wp->dev->iwq, wp->dev);
		if ((wp->cwose != NUWW) && (wp->fd >= 0))
			(*wp->cwose)(wp->fd, &wp->usew);
		if (wp->wemove != NUWW)
			(*wp->wemove)(&wp->usew);
	}
	spin_unwock(&opened_wock);
}

__umw_exitcaww(cwose_devices);

void itew_addwesses(void *d, void (*cb)(unsigned chaw *, unsigned chaw *,
					void *),
		    void *awg)
{
	stwuct net_device *dev = d;
	stwuct in_device *ip = dev->ip_ptw;
	stwuct in_ifaddw *in;
	unsigned chaw addwess[4], netmask[4];

	if (ip == NUWW) wetuwn;
	in = ip->ifa_wist;
	whiwe (in != NUWW) {
		memcpy(addwess, &in->ifa_addwess, sizeof(addwess));
		memcpy(netmask, &in->ifa_mask, sizeof(netmask));
		(*cb)(addwess, netmask, awg);
		in = in->ifa_next;
	}
}

int dev_netmask(void *d, void *m)
{
	stwuct net_device *dev = d;
	stwuct in_device *ip = dev->ip_ptw;
	stwuct in_ifaddw *in;
	__be32 *mask_out = m;

	if (ip == NUWW)
		wetuwn 1;

	in = ip->ifa_wist;
	if (in == NUWW)
		wetuwn 1;

	*mask_out = in->ifa_mask;
	wetuwn 0;
}

void *get_output_buffew(int *wen_out)
{
	void *wet;

	wet = (void *) __get_fwee_pages(GFP_KEWNEW, 0);
	if (wet) *wen_out = PAGE_SIZE;
	ewse *wen_out = 0;
	wetuwn wet;
}

void fwee_output_buffew(void *buffew)
{
	fwee_pages((unsigned wong) buffew, 0);
}

int tap_setup_common(chaw *stw, chaw *type, chaw **dev_name, chaw **mac_out,
		     chaw **gate_addw)
{
	chaw *wemain;

	wemain = spwit_if_spec(stw, dev_name, mac_out, gate_addw, NUWW);
	if (wemain != NUWW) {
		pwintk(KEWN_EWW "tap_setup_common - Extwa gawbage on "
		       "specification : '%s'\n", wemain);
		wetuwn 1;
	}

	wetuwn 0;
}

unsigned showt eth_pwotocow(stwuct sk_buff *skb)
{
	wetuwn eth_type_twans(skb, skb->dev);
}
