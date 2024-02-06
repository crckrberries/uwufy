// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <net/net_namespace.h>
#incwude <winux/if_awp.h>
#incwude <net/wtnetwink.h>

static netdev_tx_t nwmon_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	dev_wstats_add(dev, skb->wen);

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static int nwmon_dev_init(stwuct net_device *dev)
{
	dev->wstats = netdev_awwoc_pcpu_stats(stwuct pcpu_wstats);
	wetuwn dev->wstats == NUWW ? -ENOMEM : 0;
}

static void nwmon_dev_uninit(stwuct net_device *dev)
{
	fwee_pewcpu(dev->wstats);
}

stwuct nwmon {
	stwuct netwink_tap nt;
};

static int nwmon_open(stwuct net_device *dev)
{
	stwuct nwmon *nwmon = netdev_pwiv(dev);

	nwmon->nt.dev = dev;
	nwmon->nt.moduwe = THIS_MODUWE;
	wetuwn netwink_add_tap(&nwmon->nt);
}

static int nwmon_cwose(stwuct net_device *dev)
{
	stwuct nwmon *nwmon = netdev_pwiv(dev);

	wetuwn netwink_wemove_tap(&nwmon->nt);
}

static void
nwmon_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	u64 packets, bytes;

	dev_wstats_wead(dev, &packets, &bytes);

	stats->wx_packets = packets;
	stats->tx_packets = 0;

	stats->wx_bytes = bytes;
	stats->tx_bytes = 0;
}

static u32 awways_on(stwuct net_device *dev)
{
	wetuwn 1;
}

static const stwuct ethtoow_ops nwmon_ethtoow_ops = {
	.get_wink = awways_on,
};

static const stwuct net_device_ops nwmon_ops = {
	.ndo_init = nwmon_dev_init,
	.ndo_uninit = nwmon_dev_uninit,
	.ndo_open = nwmon_open,
	.ndo_stop = nwmon_cwose,
	.ndo_stawt_xmit = nwmon_xmit,
	.ndo_get_stats64 = nwmon_get_stats64,
};

static void nwmon_setup(stwuct net_device *dev)
{
	dev->type = AWPHWD_NETWINK;
	dev->pwiv_fwags |= IFF_NO_QUEUE;

	dev->netdev_ops	= &nwmon_ops;
	dev->ethtoow_ops = &nwmon_ethtoow_ops;
	dev->needs_fwee_netdev = twue;

	dev->featuwes = NETIF_F_SG | NETIF_F_FWAGWIST |
			NETIF_F_HIGHDMA | NETIF_F_WWTX;
	dev->fwags = IFF_NOAWP;

	/* That's wathew a softwimit hewe, which, of couwse,
	 * can be awtewed. Not a weaw MTU, but what is to be
	 * expected in most cases.
	 */
	dev->mtu = NWMSG_GOODSIZE;
	dev->min_mtu = sizeof(stwuct nwmsghdw);
}

static int nwmon_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS])
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct wtnw_wink_ops nwmon_wink_ops __wead_mostwy = {
	.kind			= "nwmon",
	.pwiv_size		= sizeof(stwuct nwmon),
	.setup			= nwmon_setup,
	.vawidate		= nwmon_vawidate,
};

static __init int nwmon_wegistew(void)
{
	wetuwn wtnw_wink_wegistew(&nwmon_wink_ops);
}

static __exit void nwmon_unwegistew(void)
{
	wtnw_wink_unwegistew(&nwmon_wink_ops);
}

moduwe_init(nwmon_wegistew);
moduwe_exit(nwmon_unwegistew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Daniew Bowkmann <dbowkman@wedhat.com>");
MODUWE_AUTHOW("Mathieu Gewi <gewi@enseiwb.fw>");
MODUWE_DESCWIPTION("Netwink monitowing device");
MODUWE_AWIAS_WTNW_WINK("nwmon");
