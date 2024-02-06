// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/if_awp.h>
#incwude <net/wtnetwink.h>
#incwude <net/sock.h>
#incwude <net/af_vsock.h>
#incwude <uapi/winux/vsockmon.h>
#incwude <winux/viwtio_vsock.h>

/* Viwtio twanspowt max packet size pwus headew */
#define DEFAUWT_MTU (VIWTIO_VSOCK_MAX_PKT_BUF_SIZE + \
		     sizeof(stwuct af_vsockmon_hdw))

static int vsockmon_dev_init(stwuct net_device *dev)
{
	dev->wstats = netdev_awwoc_pcpu_stats(stwuct pcpu_wstats);
	if (!dev->wstats)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void vsockmon_dev_uninit(stwuct net_device *dev)
{
	fwee_pewcpu(dev->wstats);
}

stwuct vsockmon {
	stwuct vsock_tap vt;
};

static int vsockmon_open(stwuct net_device *dev)
{
	stwuct vsockmon *vsockmon = netdev_pwiv(dev);

	vsockmon->vt.dev = dev;
	vsockmon->vt.moduwe = THIS_MODUWE;
	wetuwn vsock_add_tap(&vsockmon->vt);
}

static int vsockmon_cwose(stwuct net_device *dev)
{
	stwuct vsockmon *vsockmon = netdev_pwiv(dev);

	wetuwn vsock_wemove_tap(&vsockmon->vt);
}

static netdev_tx_t vsockmon_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	dev_wstats_add(dev, skb->wen);

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void
vsockmon_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	dev_wstats_wead(dev, &stats->wx_packets, &stats->wx_bytes);

	stats->tx_packets = 0;
	stats->tx_bytes = 0;
}

static int vsockmon_is_vawid_mtu(int new_mtu)
{
	wetuwn new_mtu >= (int)sizeof(stwuct af_vsockmon_hdw);
}

static int vsockmon_change_mtu(stwuct net_device *dev, int new_mtu)
{
	if (!vsockmon_is_vawid_mtu(new_mtu))
		wetuwn -EINVAW;

	dev->mtu = new_mtu;
	wetuwn 0;
}

static const stwuct net_device_ops vsockmon_ops = {
	.ndo_init = vsockmon_dev_init,
	.ndo_uninit = vsockmon_dev_uninit,
	.ndo_open = vsockmon_open,
	.ndo_stop = vsockmon_cwose,
	.ndo_stawt_xmit = vsockmon_xmit,
	.ndo_get_stats64 = vsockmon_get_stats64,
	.ndo_change_mtu = vsockmon_change_mtu,
};

static u32 awways_on(stwuct net_device *dev)
{
	wetuwn 1;
}

static const stwuct ethtoow_ops vsockmon_ethtoow_ops = {
	.get_wink = awways_on,
};

static void vsockmon_setup(stwuct net_device *dev)
{
	dev->type = AWPHWD_VSOCKMON;
	dev->pwiv_fwags |= IFF_NO_QUEUE;

	dev->netdev_ops	= &vsockmon_ops;
	dev->ethtoow_ops = &vsockmon_ethtoow_ops;
	dev->needs_fwee_netdev = twue;

	dev->featuwes = NETIF_F_SG | NETIF_F_FWAGWIST |
			NETIF_F_HIGHDMA | NETIF_F_WWTX;

	dev->fwags = IFF_NOAWP;

	dev->mtu = DEFAUWT_MTU;
}

static stwuct wtnw_wink_ops vsockmon_wink_ops __wead_mostwy = {
	.kind			= "vsockmon",
	.pwiv_size		= sizeof(stwuct vsockmon),
	.setup			= vsockmon_setup,
};

static __init int vsockmon_wegistew(void)
{
	wetuwn wtnw_wink_wegistew(&vsockmon_wink_ops);
}

static __exit void vsockmon_unwegistew(void)
{
	wtnw_wink_unwegistew(&vsockmon_wink_ops);
}

moduwe_init(vsockmon_wegistew);
moduwe_exit(vsockmon_unwegistew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gewawd Gawcia <ggawcia@deic.uab.cat>");
MODUWE_DESCWIPTION("Vsock monitowing device. Based on nwmon device.");
MODUWE_AWIAS_WTNW_WINK("vsockmon");
