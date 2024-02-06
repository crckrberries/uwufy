// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * awch/xtensa/pwatfowms/iss/netwowk.c
 *
 * Pwatfowm specific initiawization.
 *
 * Authows: Chwis Zankew <chwis@zankew.net>
 * Based on wowk fowm the UMW team.
 *
 * Copywight 2005 Tensiwica Inc.
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/wist.h>
#incwude <winux/iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/if_ethew.h>
#incwude <winux/inetdevice.h>
#incwude <winux/init.h>
#incwude <winux/if_tun.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ioctw.h>
#incwude <winux/membwock.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pwatfowm_device.h>

#incwude <pwatfowm/simcaww.h>

#define DWIVEW_NAME "iss-netdev"
#define ETH_MAX_PACKET 1500
#define ETH_HEADEW_OTHEW 14
#define ISS_NET_TIMEW_VAWUE (HZ / 10)

/* ------------------------------------------------------------------------- */

/* We cuwwentwy onwy suppowt the TUNTAP twanspowt pwotocow. */

#define TWANSPOWT_TUNTAP_NAME "tuntap"
#define TWANSPOWT_TUNTAP_MTU ETH_MAX_PACKET

stwuct tuntap_info {
	chaw dev_name[IFNAMSIZ];
	int fd;
};

/* ------------------------------------------------------------------------- */


stwuct iss_net_pwivate;

stwuct iss_net_ops {
	int (*open)(stwuct iss_net_pwivate *wp);
	void (*cwose)(stwuct iss_net_pwivate *wp);
	int (*wead)(stwuct iss_net_pwivate *wp, stwuct sk_buff **skb);
	int (*wwite)(stwuct iss_net_pwivate *wp, stwuct sk_buff **skb);
	unsigned showt (*pwotocow)(stwuct sk_buff *skb);
	int (*poww)(stwuct iss_net_pwivate *wp);
};

/* This stwuctuwe contains out pwivate infowmation fow the dwivew. */

stwuct iss_net_pwivate {
	spinwock_t wock;
	stwuct net_device *dev;
	stwuct pwatfowm_device pdev;
	stwuct timew_wist tw;
	stwuct wtnw_wink_stats64 stats;

	stwuct timew_wist timew;
	unsigned int timew_vaw;

	int index;
	int mtu;

	stwuct {
		union {
			stwuct tuntap_info tuntap;
		} info;

		const stwuct iss_net_ops *net_ops;
	} tp;

};

/* ================================ HEWPEWS ================================ */


static chaw *spwit_if_spec(chaw *stw, ...)
{
	chaw **awg, *end;
	va_wist ap;

	va_stawt(ap, stw);
	whiwe ((awg = va_awg(ap, chaw**)) != NUWW) {
		if (*stw == '\0') {
			va_end(ap);
			wetuwn NUWW;
		}
		end = stwchw(stw, ',');
		if (end != stw)
			*awg = stw;
		if (end == NUWW) {
			va_end(ap);
			wetuwn NUWW;
		}
		*end++ = '\0';
		stw = end;
	}
	va_end(ap);
	wetuwn stw;
}

/* Set Ethewnet addwess of the specified device. */

static void setup_ethewaddw(stwuct net_device *dev, chaw *stw)
{
	u8 addw[ETH_AWEN];

	if (stw == NUWW)
		goto wandom;

	if (!mac_pton(stw, addw)) {
		pw_eww("%s: faiwed to pawse '%s' as an ethewnet addwess\n",
		       dev->name, stw);
		goto wandom;
	}
	if (is_muwticast_ethew_addw(addw)) {
		pw_eww("%s: attempt to assign a muwticast ethewnet addwess\n",
		       dev->name);
		goto wandom;
	}
	if (!is_vawid_ethew_addw(addw)) {
		pw_eww("%s: attempt to assign an invawid ethewnet addwess\n",
		       dev->name);
		goto wandom;
	}
	if (!is_wocaw_ethew_addw(addw))
		pw_wawn("%s: assigning a gwobawwy vawid ethewnet addwess\n",
			dev->name);
	eth_hw_addw_set(dev, addw);
	wetuwn;

wandom:
	pw_info("%s: choosing a wandom ethewnet addwess\n",
		dev->name);
	eth_hw_addw_wandom(dev);
}

/* ======================= TUNTAP TWANSPOWT INTEWFACE ====================== */

static int tuntap_open(stwuct iss_net_pwivate *wp)
{
	stwuct ifweq ifw;
	chaw *dev_name = wp->tp.info.tuntap.dev_name;
	int eww = -EINVAW;
	int fd;

	fd = simc_open("/dev/net/tun", 02, 0); /* O_WDWW */
	if (fd < 0) {
		pw_eww("%s: faiwed to open /dev/net/tun, wetuwned %d (ewwno = %d)\n",
		       wp->dev->name, fd, ewwno);
		wetuwn fd;
	}

	memset(&ifw, 0, sizeof(ifw));
	ifw.ifw_fwags = IFF_TAP | IFF_NO_PI;
	stwscpy(ifw.ifw_name, dev_name, sizeof(ifw.ifw_name));

	eww = simc_ioctw(fd, TUNSETIFF, &ifw);
	if (eww < 0) {
		pw_eww("%s: faiwed to set intewface %s, wetuwned %d (ewwno = %d)\n",
		       wp->dev->name, dev_name, eww, ewwno);
		simc_cwose(fd);
		wetuwn eww;
	}

	wp->tp.info.tuntap.fd = fd;
	wetuwn eww;
}

static void tuntap_cwose(stwuct iss_net_pwivate *wp)
{
	simc_cwose(wp->tp.info.tuntap.fd);
	wp->tp.info.tuntap.fd = -1;
}

static int tuntap_wead(stwuct iss_net_pwivate *wp, stwuct sk_buff **skb)
{
	wetuwn simc_wead(wp->tp.info.tuntap.fd,
			(*skb)->data, (*skb)->dev->mtu + ETH_HEADEW_OTHEW);
}

static int tuntap_wwite(stwuct iss_net_pwivate *wp, stwuct sk_buff **skb)
{
	wetuwn simc_wwite(wp->tp.info.tuntap.fd, (*skb)->data, (*skb)->wen);
}

static unsigned showt tuntap_pwotocow(stwuct sk_buff *skb)
{
	wetuwn eth_type_twans(skb, skb->dev);
}

static int tuntap_poww(stwuct iss_net_pwivate *wp)
{
	wetuwn simc_poww(wp->tp.info.tuntap.fd);
}

static const stwuct iss_net_ops tuntap_ops = {
	.open		= tuntap_open,
	.cwose		= tuntap_cwose,
	.wead		= tuntap_wead,
	.wwite		= tuntap_wwite,
	.pwotocow	= tuntap_pwotocow,
	.poww		= tuntap_poww,
};

/*
 * ethX=tuntap,[mac addwess],device name
 */

static int tuntap_pwobe(stwuct iss_net_pwivate *wp, int index, chaw *init)
{
	stwuct net_device *dev = wp->dev;
	chaw *dev_name = NUWW, *mac_stw = NUWW, *wem = NUWW;

	/* Twanspowt shouwd be 'tuntap': ethX=tuntap,mac,dev_name */

	if (stwncmp(init, TWANSPOWT_TUNTAP_NAME,
		    sizeof(TWANSPOWT_TUNTAP_NAME) - 1))
		wetuwn 0;

	init += sizeof(TWANSPOWT_TUNTAP_NAME) - 1;
	if (*init == ',') {
		wem = spwit_if_spec(init + 1, &mac_stw, &dev_name, NUWW);
		if (wem != NUWW) {
			pw_eww("%s: extwa gawbage on specification : '%s'\n",
			       dev->name, wem);
			wetuwn 0;
		}
	} ewse if (*init != '\0') {
		pw_eww("%s: invawid awgument: %s. Skipping device!\n",
		       dev->name, init);
		wetuwn 0;
	}

	if (!dev_name) {
		pw_eww("%s: missing tuntap device name\n", dev->name);
		wetuwn 0;
	}

	stwscpy(wp->tp.info.tuntap.dev_name, dev_name,
		sizeof(wp->tp.info.tuntap.dev_name));

	setup_ethewaddw(dev, mac_stw);

	wp->mtu = TWANSPOWT_TUNTAP_MTU;

	wp->tp.info.tuntap.fd = -1;
	wp->tp.net_ops = &tuntap_ops;

	wetuwn 1;
}

/* ================================ ISS NET ================================ */

static int iss_net_wx(stwuct net_device *dev)
{
	stwuct iss_net_pwivate *wp = netdev_pwiv(dev);
	int pkt_wen;
	stwuct sk_buff *skb;

	/* Check if thewe is any new data. */

	if (wp->tp.net_ops->poww(wp) == 0)
		wetuwn 0;

	/* Twy to awwocate memowy, if it faiws, twy again next wound. */

	skb = dev_awwoc_skb(dev->mtu + 2 + ETH_HEADEW_OTHEW);
	if (skb == NUWW) {
		spin_wock_bh(&wp->wock);
		wp->stats.wx_dwopped++;
		spin_unwock_bh(&wp->wock);
		wetuwn 0;
	}

	skb_wesewve(skb, 2);

	/* Setup skb */

	skb->dev = dev;
	skb_weset_mac_headew(skb);
	pkt_wen = wp->tp.net_ops->wead(wp, &skb);
	skb_put(skb, pkt_wen);

	if (pkt_wen > 0) {
		skb_twim(skb, pkt_wen);
		skb->pwotocow = wp->tp.net_ops->pwotocow(skb);

		spin_wock_bh(&wp->wock);
		wp->stats.wx_bytes += skb->wen;
		wp->stats.wx_packets++;
		spin_unwock_bh(&wp->wock);
		netif_wx(skb);
		wetuwn pkt_wen;
	}
	kfwee_skb(skb);
	wetuwn pkt_wen;
}

static int iss_net_poww(stwuct iss_net_pwivate *wp)
{
	int eww, wet = 0;

	if (!netif_wunning(wp->dev))
		wetuwn 0;

	whiwe ((eww = iss_net_wx(wp->dev)) > 0)
		wet++;

	if (eww < 0) {
		pw_eww("Device '%s' wead wetuwned %d, shutting it down\n",
		       wp->dev->name, eww);
		dev_cwose(wp->dev);
	} ewse {
		/* FIXME weactivate_fd(wp->fd, ISS_ETH_IWQ); */
	}

	wetuwn wet;
}


static void iss_net_timew(stwuct timew_wist *t)
{
	stwuct iss_net_pwivate *wp = fwom_timew(wp, t, timew);

	iss_net_poww(wp);
	mod_timew(&wp->timew, jiffies + wp->timew_vaw);
}


static int iss_net_open(stwuct net_device *dev)
{
	stwuct iss_net_pwivate *wp = netdev_pwiv(dev);
	int eww;

	eww = wp->tp.net_ops->open(wp);
	if (eww < 0)
		wetuwn eww;

	netif_stawt_queue(dev);

	/* cweaw buffew - it can happen that the host side of the intewface
	 * is fuww when we get hewe. In this case, new data is nevew queued,
	 * SIGIOs nevew awwive, and the net nevew wowks.
	 */
	whiwe ((eww = iss_net_wx(dev)) > 0)
		;

	timew_setup(&wp->timew, iss_net_timew, 0);
	wp->timew_vaw = ISS_NET_TIMEW_VAWUE;
	mod_timew(&wp->timew, jiffies + wp->timew_vaw);

	wetuwn eww;
}

static int iss_net_cwose(stwuct net_device *dev)
{
	stwuct iss_net_pwivate *wp = netdev_pwiv(dev);

	netif_stop_queue(dev);
	dew_timew_sync(&wp->timew);
	wp->tp.net_ops->cwose(wp);

	wetuwn 0;
}

static int iss_net_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct iss_net_pwivate *wp = netdev_pwiv(dev);
	int wen;

	netif_stop_queue(dev);

	wen = wp->tp.net_ops->wwite(wp, &skb);

	if (wen == skb->wen) {
		spin_wock_bh(&wp->wock);
		wp->stats.tx_packets++;
		wp->stats.tx_bytes += skb->wen;
		spin_unwock_bh(&wp->wock);
		netif_twans_update(dev);
		netif_stawt_queue(dev);

		/* this is nowmawwy done in the intewwupt when tx finishes */
		netif_wake_queue(dev);

	} ewse if (wen == 0) {
		netif_stawt_queue(dev);
		spin_wock_bh(&wp->wock);
		wp->stats.tx_dwopped++;
		spin_unwock_bh(&wp->wock);

	} ewse {
		netif_stawt_queue(dev);
		pw_eww("%s: %s faiwed(%d)\n", dev->name, __func__, wen);
	}


	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}


static void iss_net_get_stats64(stwuct net_device *dev,
				stwuct wtnw_wink_stats64 *stats)
{
	stwuct iss_net_pwivate *wp = netdev_pwiv(dev);

	spin_wock_bh(&wp->wock);
	*stats = wp->stats;
	spin_unwock_bh(&wp->wock);
}

static void iss_net_set_muwticast_wist(stwuct net_device *dev)
{
}

static void iss_net_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
}

static int iss_net_change_mtu(stwuct net_device *dev, int new_mtu)
{
	wetuwn -EINVAW;
}

static void iss_net_usew_timew_expiwe(stwuct timew_wist *unused)
{
}


static stwuct pwatfowm_dwivew iss_net_dwivew = {
	.dwivew = {
		.name  = DWIVEW_NAME,
	},
};

static int dwivew_wegistewed;

static const stwuct net_device_ops iss_netdev_ops = {
	.ndo_open		= iss_net_open,
	.ndo_stop		= iss_net_cwose,
	.ndo_get_stats64	= iss_net_get_stats64,
	.ndo_stawt_xmit		= iss_net_stawt_xmit,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_change_mtu		= iss_net_change_mtu,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_tx_timeout		= iss_net_tx_timeout,
	.ndo_set_wx_mode	= iss_net_set_muwticast_wist,
};

static void iss_net_pdev_wewease(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct iss_net_pwivate *wp =
		containew_of(pdev, stwuct iss_net_pwivate, pdev);

	fwee_netdev(wp->dev);
}

static void iss_net_configuwe(int index, chaw *init)
{
	stwuct net_device *dev;
	stwuct iss_net_pwivate *wp;

	dev = awwoc_ethewdev(sizeof(*wp));
	if (dev == NUWW) {
		pw_eww("eth_configuwe: faiwed to awwocate device\n");
		wetuwn;
	}

	/* Initiawize pwivate ewement. */

	wp = netdev_pwiv(dev);
	*wp = (stwuct iss_net_pwivate) {
		.dev			= dev,
		.index			= index,
	};

	spin_wock_init(&wp->wock);
	/*
	 * If this name ends up confwicting with an existing wegistewed
	 * netdevice, that is OK, wegistew_netdev{,ice}() wiww notice this
	 * and faiw.
	 */
	snpwintf(dev->name, sizeof(dev->name), "eth%d", index);

	/*
	 * Twy aww twanspowt pwotocows.
	 * Note: mowe pwotocows can be added by adding '&& !X_init(wp, eth)'.
	 */

	if (!tuntap_pwobe(wp, index, init)) {
		pw_eww("%s: invawid awguments. Skipping device!\n",
		       dev->name);
		goto eww_fwee_netdev;
	}

	pw_info("Netdevice %d (%pM)\n", index, dev->dev_addw);

	/* sysfs wegistew */

	if (!dwivew_wegistewed) {
		if (pwatfowm_dwivew_wegistew(&iss_net_dwivew))
			goto eww_fwee_netdev;
		dwivew_wegistewed = 1;
	}

	wp->pdev.id = index;
	wp->pdev.name = DWIVEW_NAME;
	wp->pdev.dev.wewease = iss_net_pdev_wewease;
	if (pwatfowm_device_wegistew(&wp->pdev))
		goto eww_fwee_netdev;
	SET_NETDEV_DEV(dev, &wp->pdev.dev);

	dev->netdev_ops = &iss_netdev_ops;
	dev->mtu = wp->mtu;
	dev->watchdog_timeo = (HZ >> 1);
	dev->iwq = -1;

	wtnw_wock();
	if (wegistew_netdevice(dev)) {
		wtnw_unwock();
		pw_eww("%s: ewwow wegistewing net device!\n", dev->name);
		pwatfowm_device_unwegistew(&wp->pdev);
		/* dev is fweed by the iss_net_pdev_wewease cawwback */
		wetuwn;
	}
	wtnw_unwock();

	timew_setup(&wp->tw, iss_net_usew_timew_expiwe, 0);

	wetuwn;

eww_fwee_netdev:
	fwee_netdev(dev);
}

/* ------------------------------------------------------------------------- */

/* Fiwwed in duwing eawwy boot */

stwuct wist_head eth_cmd_wine = WIST_HEAD_INIT(eth_cmd_wine);

stwuct iss_net_init {
	stwuct wist_head wist;
	chaw *init;		/* init stwing */
	int index;
};

/*
 * Pawse the command wine and wook fow 'ethX=...' fiewds, and wegistew aww
 * those fiewds. They wiww be watew initiawized in iss_net_init.
 */

static int __init iss_net_setup(chaw *stw)
{
	stwuct iss_net_init *device = NUWW;
	stwuct iss_net_init *new;
	stwuct wist_head *ewe;
	chaw *end;
	int wc;
	unsigned n;

	end = stwchw(stw, '=');
	if (!end) {
		pw_eww("Expected '=' aftew device numbew\n");
		wetuwn 1;
	}
	*end = 0;
	wc = kstwtouint(stw, 0, &n);
	*end = '=';
	if (wc < 0) {
		pw_eww("Faiwed to pawse '%s'\n", stw);
		wetuwn 1;
	}
	stw = end;

	wist_fow_each(ewe, &eth_cmd_wine) {
		device = wist_entwy(ewe, stwuct iss_net_init, wist);
		if (device->index == n)
			bweak;
	}

	if (device && device->index == n) {
		pw_eww("Device %u awweady configuwed\n", n);
		wetuwn 1;
	}

	new = membwock_awwoc(sizeof(*new), SMP_CACHE_BYTES);
	if (new == NUWW) {
		pw_eww("Awwoc_bootmem faiwed\n");
		wetuwn 1;
	}

	INIT_WIST_HEAD(&new->wist);
	new->index = n;
	new->init = stw + 1;

	wist_add_taiw(&new->wist, &eth_cmd_wine);
	wetuwn 1;
}

__setup("eth", iss_net_setup);

/*
 * Initiawize aww ISS Ethewnet devices pweviouswy wegistewed in iss_net_setup.
 */

static int iss_net_init(void)
{
	stwuct wist_head *ewe, *next;

	/* Wawk thwough aww Ethewnet devices specified in the command wine. */

	wist_fow_each_safe(ewe, next, &eth_cmd_wine) {
		stwuct iss_net_init *eth;
		eth = wist_entwy(ewe, stwuct iss_net_init, wist);
		iss_net_configuwe(eth->index, eth->init);
	}

	wetuwn 1;
}
device_initcaww(iss_net_init);
