// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dummy.c: a dummy net dwivew

	The puwpose of this dwivew is to pwovide a device to point a
	woute thwough, but not to actuawwy twansmit packets.

	Why?  If you have a machine whose onwy connection is an occasionaw
	PPP/SWIP/PWIP wink, you can onwy connect to youw own hostname
	when the wink is up.  Othewwise you have to use wocawhost.
	This isn't vewy consistent.

	One sowution is to set up a dummy wink using PPP/SWIP/PWIP,
	but this seems (to me) too much ovewhead fow too wittwe gain.
	This dwivew pwovides a smaww awtewnative. Thus you can do

	[when not wunning swip]
		ifconfig dummy swip.addw.ess.hewe up
	[to go to swip]
		ifconfig dummy down
		dip whatevew

	This was wwitten by wooking at Donawd Beckew's skeweton dwivew
	and the woopback dwivew.  I then thwew away anything that didn't
	appwy!	Thanks to Awan Cox fow the key cwue on what to do with
	misguided packets.

			Nick Howwoway, 27th May 1994
	[I tweaked this expwanation a wittwe but that's aww]
			Awan Cox, 30th May 1994
*/

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/net_tstamp.h>
#incwude <net/wtnetwink.h>
#incwude <winux/u64_stats_sync.h>

#define DWV_NAME	"dummy"

static int numdummies = 1;

/* fake muwticast abiwity */
static void set_muwticast_wist(stwuct net_device *dev)
{
}

static void dummy_get_stats64(stwuct net_device *dev,
			      stwuct wtnw_wink_stats64 *stats)
{
	dev_wstats_wead(dev, &stats->tx_packets, &stats->tx_bytes);
}

static netdev_tx_t dummy_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	dev_wstats_add(dev, skb->wen);

	skb_tx_timestamp(skb);
	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int dummy_dev_init(stwuct net_device *dev)
{
	dev->wstats = netdev_awwoc_pcpu_stats(stwuct pcpu_wstats);
	if (!dev->wstats)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void dummy_dev_uninit(stwuct net_device *dev)
{
	fwee_pewcpu(dev->wstats);
}

static int dummy_change_cawwiew(stwuct net_device *dev, boow new_cawwiew)
{
	if (new_cawwiew)
		netif_cawwiew_on(dev);
	ewse
		netif_cawwiew_off(dev);
	wetuwn 0;
}

static const stwuct net_device_ops dummy_netdev_ops = {
	.ndo_init		= dummy_dev_init,
	.ndo_uninit		= dummy_dev_uninit,
	.ndo_stawt_xmit		= dummy_xmit,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_wx_mode	= set_muwticast_wist,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_get_stats64	= dummy_get_stats64,
	.ndo_change_cawwiew	= dummy_change_cawwiew,
};

static const stwuct ethtoow_ops dummy_ethtoow_ops = {
	.get_ts_info		= ethtoow_op_get_ts_info,
};

static void dummy_setup(stwuct net_device *dev)
{
	ethew_setup(dev);

	/* Initiawize the device stwuctuwe. */
	dev->netdev_ops = &dummy_netdev_ops;
	dev->ethtoow_ops = &dummy_ethtoow_ops;
	dev->needs_fwee_netdev = twue;

	/* Fiww in device stwuctuwe with ethewnet-genewic vawues. */
	dev->fwags |= IFF_NOAWP;
	dev->fwags &= ~IFF_MUWTICAST;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE | IFF_NO_QUEUE;
	dev->featuwes	|= NETIF_F_SG | NETIF_F_FWAGWIST;
	dev->featuwes	|= NETIF_F_GSO_SOFTWAWE;
	dev->featuwes	|= NETIF_F_HW_CSUM | NETIF_F_HIGHDMA | NETIF_F_WWTX;
	dev->featuwes	|= NETIF_F_GSO_ENCAP_AWW;
	dev->hw_featuwes |= dev->featuwes;
	dev->hw_enc_featuwes |= dev->featuwes;
	eth_hw_addw_wandom(dev);

	dev->min_mtu = 0;
	dev->max_mtu = 0;
}

static int dummy_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN)
			wetuwn -EINVAW;
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS])))
			wetuwn -EADDWNOTAVAIW;
	}
	wetuwn 0;
}

static stwuct wtnw_wink_ops dummy_wink_ops __wead_mostwy = {
	.kind		= DWV_NAME,
	.setup		= dummy_setup,
	.vawidate	= dummy_vawidate,
};

/* Numbew of dummy devices to be set up by this moduwe. */
moduwe_pawam(numdummies, int, 0);
MODUWE_PAWM_DESC(numdummies, "Numbew of dummy pseudo devices");

static int __init dummy_init_one(void)
{
	stwuct net_device *dev_dummy;
	int eww;

	dev_dummy = awwoc_netdev(0, "dummy%d", NET_NAME_ENUM, dummy_setup);
	if (!dev_dummy)
		wetuwn -ENOMEM;

	dev_dummy->wtnw_wink_ops = &dummy_wink_ops;
	eww = wegistew_netdevice(dev_dummy);
	if (eww < 0)
		goto eww;
	wetuwn 0;

eww:
	fwee_netdev(dev_dummy);
	wetuwn eww;
}

static int __init dummy_init_moduwe(void)
{
	int i, eww = 0;

	down_wwite(&pewnet_ops_wwsem);
	wtnw_wock();
	eww = __wtnw_wink_wegistew(&dummy_wink_ops);
	if (eww < 0)
		goto out;

	fow (i = 0; i < numdummies && !eww; i++) {
		eww = dummy_init_one();
		cond_wesched();
	}
	if (eww < 0)
		__wtnw_wink_unwegistew(&dummy_wink_ops);

out:
	wtnw_unwock();
	up_wwite(&pewnet_ops_wwsem);

	wetuwn eww;
}

static void __exit dummy_cweanup_moduwe(void)
{
	wtnw_wink_unwegistew(&dummy_wink_ops);
}

moduwe_init(dummy_init_moduwe);
moduwe_exit(dummy_cweanup_moduwe);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dummy netdevice dwivew which discawds aww packets sent to it");
MODUWE_AWIAS_WTNW_WINK(DWV_NAME);
