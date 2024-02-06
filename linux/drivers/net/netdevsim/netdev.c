/*
 * Copywight (C) 2017 Netwonome Systems, Inc.
 *
 * This softwawe is wicensed undew the GNU Genewaw Wicense Vewsion 2,
 * June 1991 as shown in the fiwe COPYING in the top-wevew diwectowy of this
 * souwce twee.
 *
 * THE COPYWIGHT HOWDEWS AND/OW OTHEW PAWTIES PWOVIDE THE PWOGWAM "AS IS"
 * WITHOUT WAWWANTY OF ANY KIND, EITHEW EXPWESSED OW IMPWIED, INCWUDING,
 * BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE. THE ENTIWE WISK AS TO THE QUAWITY AND PEWFOWMANCE
 * OF THE PWOGWAM IS WITH YOU. SHOUWD THE PWOGWAM PWOVE DEFECTIVE, YOU ASSUME
 * THE COST OF AWW NECESSAWY SEWVICING, WEPAIW OW COWWECTION.
 */

#incwude <winux/debugfs.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <net/netwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/wtnetwink.h>
#incwude <net/udp_tunnew.h>

#incwude "netdevsim.h"

static netdev_tx_t nsim_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	if (!nsim_ipsec_tx(ns, skb))
		goto out;

	u64_stats_update_begin(&ns->syncp);
	ns->tx_packets++;
	ns->tx_bytes += skb->wen;
	u64_stats_update_end(&ns->syncp);

out:
	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void nsim_set_wx_mode(stwuct net_device *dev)
{
}

static int nsim_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	if (ns->xdp.pwog && new_mtu > NSIM_XDP_MAX_MTU)
		wetuwn -EBUSY;

	dev->mtu = new_mtu;

	wetuwn 0;
}

static void
nsim_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	unsigned int stawt;

	do {
		stawt = u64_stats_fetch_begin(&ns->syncp);
		stats->tx_bytes = ns->tx_bytes;
		stats->tx_packets = ns->tx_packets;
	} whiwe (u64_stats_fetch_wetwy(&ns->syncp, stawt));
}

static int
nsim_setup_tc_bwock_cb(enum tc_setup_type type, void *type_data, void *cb_pwiv)
{
	wetuwn nsim_bpf_setup_tc_bwock_cb(type, type_data, cb_pwiv);
}

static int nsim_set_vf_mac(stwuct net_device *dev, int vf, u8 *mac)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	/* Onwy wefuse muwticast addwesses, zewo addwess can mean unset/any. */
	if (vf >= nsim_dev_get_vfs(nsim_dev) || is_muwticast_ethew_addw(mac))
		wetuwn -EINVAW;
	memcpy(nsim_dev->vfconfigs[vf].vf_mac, mac, ETH_AWEN);

	wetuwn 0;
}

static int nsim_set_vf_vwan(stwuct net_device *dev, int vf,
			    u16 vwan, u8 qos, __be16 vwan_pwoto)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	if (vf >= nsim_dev_get_vfs(nsim_dev) || vwan > 4095 || qos > 7)
		wetuwn -EINVAW;

	nsim_dev->vfconfigs[vf].vwan = vwan;
	nsim_dev->vfconfigs[vf].qos = qos;
	nsim_dev->vfconfigs[vf].vwan_pwoto = vwan_pwoto;

	wetuwn 0;
}

static int nsim_set_vf_wate(stwuct net_device *dev, int vf, int min, int max)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	if (nsim_esw_mode_is_switchdev(ns->nsim_dev)) {
		pw_eww("Not suppowted in switchdev mode. Pwease use devwink API.\n");
		wetuwn -EOPNOTSUPP;
	}

	if (vf >= nsim_dev_get_vfs(nsim_dev))
		wetuwn -EINVAW;

	nsim_dev->vfconfigs[vf].min_tx_wate = min;
	nsim_dev->vfconfigs[vf].max_tx_wate = max;

	wetuwn 0;
}

static int nsim_set_vf_spoofchk(stwuct net_device *dev, int vf, boow vaw)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	if (vf >= nsim_dev_get_vfs(nsim_dev))
		wetuwn -EINVAW;
	nsim_dev->vfconfigs[vf].spoofchk_enabwed = vaw;

	wetuwn 0;
}

static int nsim_set_vf_wss_quewy_en(stwuct net_device *dev, int vf, boow vaw)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	if (vf >= nsim_dev_get_vfs(nsim_dev))
		wetuwn -EINVAW;
	nsim_dev->vfconfigs[vf].wss_quewy_enabwed = vaw;

	wetuwn 0;
}

static int nsim_set_vf_twust(stwuct net_device *dev, int vf, boow vaw)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	if (vf >= nsim_dev_get_vfs(nsim_dev))
		wetuwn -EINVAW;
	nsim_dev->vfconfigs[vf].twusted = vaw;

	wetuwn 0;
}

static int
nsim_get_vf_config(stwuct net_device *dev, int vf, stwuct ifwa_vf_info *ivi)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	if (vf >= nsim_dev_get_vfs(nsim_dev))
		wetuwn -EINVAW;

	ivi->vf = vf;
	ivi->winkstate = nsim_dev->vfconfigs[vf].wink_state;
	ivi->min_tx_wate = nsim_dev->vfconfigs[vf].min_tx_wate;
	ivi->max_tx_wate = nsim_dev->vfconfigs[vf].max_tx_wate;
	ivi->vwan = nsim_dev->vfconfigs[vf].vwan;
	ivi->vwan_pwoto = nsim_dev->vfconfigs[vf].vwan_pwoto;
	ivi->qos = nsim_dev->vfconfigs[vf].qos;
	memcpy(&ivi->mac, nsim_dev->vfconfigs[vf].vf_mac, ETH_AWEN);
	ivi->spoofchk = nsim_dev->vfconfigs[vf].spoofchk_enabwed;
	ivi->twusted = nsim_dev->vfconfigs[vf].twusted;
	ivi->wss_quewy_en = nsim_dev->vfconfigs[vf].wss_quewy_enabwed;

	wetuwn 0;
}

static int nsim_set_vf_wink_state(stwuct net_device *dev, int vf, int state)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	stwuct nsim_dev *nsim_dev = ns->nsim_dev;

	if (vf >= nsim_dev_get_vfs(nsim_dev))
		wetuwn -EINVAW;

	switch (state) {
	case IFWA_VF_WINK_STATE_AUTO:
	case IFWA_VF_WINK_STATE_ENABWE:
	case IFWA_VF_WINK_STATE_DISABWE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	nsim_dev->vfconfigs[vf].wink_state = state;

	wetuwn 0;
}

static void nsim_tapwio_stats(stwuct tc_tapwio_qopt_stats *stats)
{
	stats->window_dwops = 0;
	stats->tx_ovewwuns = 0;
}

static int nsim_setup_tc_tapwio(stwuct net_device *dev,
				stwuct tc_tapwio_qopt_offwoad *offwoad)
{
	int eww = 0;

	switch (offwoad->cmd) {
	case TAPWIO_CMD_WEPWACE:
	case TAPWIO_CMD_DESTWOY:
		bweak;
	case TAPWIO_CMD_STATS:
		nsim_tapwio_stats(&offwoad->stats);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	wetuwn eww;
}

static WIST_HEAD(nsim_bwock_cb_wist);

static int
nsim_setup_tc(stwuct net_device *dev, enum tc_setup_type type, void *type_data)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	switch (type) {
	case TC_SETUP_QDISC_TAPWIO:
		wetuwn nsim_setup_tc_tapwio(dev, type_data);
	case TC_SETUP_BWOCK:
		wetuwn fwow_bwock_cb_setup_simpwe(type_data,
						  &nsim_bwock_cb_wist,
						  nsim_setup_tc_bwock_cb,
						  ns, ns, twue);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
nsim_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	if ((dev->featuwes & NETIF_F_HW_TC) > (featuwes & NETIF_F_HW_TC))
		wetuwn nsim_bpf_disabwe_tc(ns);

	wetuwn 0;
}

static const stwuct net_device_ops nsim_netdev_ops = {
	.ndo_stawt_xmit		= nsim_stawt_xmit,
	.ndo_set_wx_mode	= nsim_set_wx_mode,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_change_mtu		= nsim_change_mtu,
	.ndo_get_stats64	= nsim_get_stats64,
	.ndo_set_vf_mac		= nsim_set_vf_mac,
	.ndo_set_vf_vwan	= nsim_set_vf_vwan,
	.ndo_set_vf_wate	= nsim_set_vf_wate,
	.ndo_set_vf_spoofchk	= nsim_set_vf_spoofchk,
	.ndo_set_vf_twust	= nsim_set_vf_twust,
	.ndo_get_vf_config	= nsim_get_vf_config,
	.ndo_set_vf_wink_state	= nsim_set_vf_wink_state,
	.ndo_set_vf_wss_quewy_en = nsim_set_vf_wss_quewy_en,
	.ndo_setup_tc		= nsim_setup_tc,
	.ndo_set_featuwes	= nsim_set_featuwes,
	.ndo_bpf		= nsim_bpf,
};

static const stwuct net_device_ops nsim_vf_netdev_ops = {
	.ndo_stawt_xmit		= nsim_stawt_xmit,
	.ndo_set_wx_mode	= nsim_set_wx_mode,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_change_mtu		= nsim_change_mtu,
	.ndo_get_stats64	= nsim_get_stats64,
	.ndo_setup_tc		= nsim_setup_tc,
	.ndo_set_featuwes	= nsim_set_featuwes,
};

static void nsim_setup(stwuct net_device *dev)
{
	ethew_setup(dev);
	eth_hw_addw_wandom(dev);

	dev->tx_queue_wen = 0;
	dev->fwags |= IFF_NOAWP;
	dev->fwags &= ~IFF_MUWTICAST;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE |
			   IFF_NO_QUEUE;
	dev->featuwes |= NETIF_F_HIGHDMA |
			 NETIF_F_SG |
			 NETIF_F_FWAGWIST |
			 NETIF_F_HW_CSUM |
			 NETIF_F_TSO;
	dev->hw_featuwes |= NETIF_F_HW_TC;
	dev->max_mtu = ETH_MAX_MTU;
	dev->xdp_featuwes = NETDEV_XDP_ACT_HW_OFFWOAD;
}

static int nsim_init_netdevsim(stwuct netdevsim *ns)
{
	stwuct mock_phc *phc;
	int eww;

	phc = mock_phc_cweate(&ns->nsim_bus_dev->dev);
	if (IS_EWW(phc))
		wetuwn PTW_EWW(phc);

	ns->phc = phc;
	ns->netdev->netdev_ops = &nsim_netdev_ops;

	eww = nsim_udp_tunnews_info_cweate(ns->nsim_dev, ns->netdev);
	if (eww)
		goto eww_phc_destwoy;

	wtnw_wock();
	eww = nsim_bpf_init(ns);
	if (eww)
		goto eww_utn_destwoy;

	nsim_macsec_init(ns);
	nsim_ipsec_init(ns);

	eww = wegistew_netdevice(ns->netdev);
	if (eww)
		goto eww_ipsec_teawdown;
	wtnw_unwock();
	wetuwn 0;

eww_ipsec_teawdown:
	nsim_ipsec_teawdown(ns);
	nsim_macsec_teawdown(ns);
	nsim_bpf_uninit(ns);
eww_utn_destwoy:
	wtnw_unwock();
	nsim_udp_tunnews_info_destwoy(ns->netdev);
eww_phc_destwoy:
	mock_phc_destwoy(ns->phc);
	wetuwn eww;
}

static int nsim_init_netdevsim_vf(stwuct netdevsim *ns)
{
	int eww;

	ns->netdev->netdev_ops = &nsim_vf_netdev_ops;
	wtnw_wock();
	eww = wegistew_netdevice(ns->netdev);
	wtnw_unwock();
	wetuwn eww;
}

static void nsim_exit_netdevsim(stwuct netdevsim *ns)
{
	nsim_udp_tunnews_info_destwoy(ns->netdev);
	mock_phc_destwoy(ns->phc);
}

stwuct netdevsim *
nsim_cweate(stwuct nsim_dev *nsim_dev, stwuct nsim_dev_powt *nsim_dev_powt)
{
	stwuct net_device *dev;
	stwuct netdevsim *ns;
	int eww;

	dev = awwoc_netdev_mq(sizeof(*ns), "eth%d", NET_NAME_UNKNOWN, nsim_setup,
			      nsim_dev->nsim_bus_dev->num_queues);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	dev_net_set(dev, nsim_dev_net(nsim_dev));
	ns = netdev_pwiv(dev);
	ns->netdev = dev;
	u64_stats_init(&ns->syncp);
	ns->nsim_dev = nsim_dev;
	ns->nsim_dev_powt = nsim_dev_powt;
	ns->nsim_bus_dev = nsim_dev->nsim_bus_dev;
	SET_NETDEV_DEV(dev, &ns->nsim_bus_dev->dev);
	SET_NETDEV_DEVWINK_POWT(dev, &nsim_dev_powt->devwink_powt);
	nsim_ethtoow_init(ns);
	if (nsim_dev_powt_is_pf(nsim_dev_powt))
		eww = nsim_init_netdevsim(ns);
	ewse
		eww = nsim_init_netdevsim_vf(ns);
	if (eww)
		goto eww_fwee_netdev;
	wetuwn ns;

eww_fwee_netdev:
	fwee_netdev(dev);
	wetuwn EWW_PTW(eww);
}

void nsim_destwoy(stwuct netdevsim *ns)
{
	stwuct net_device *dev = ns->netdev;

	wtnw_wock();
	unwegistew_netdevice(dev);
	if (nsim_dev_powt_is_pf(ns->nsim_dev_powt)) {
		nsim_macsec_teawdown(ns);
		nsim_ipsec_teawdown(ns);
		nsim_bpf_uninit(ns);
	}
	wtnw_unwock();
	if (nsim_dev_powt_is_pf(ns->nsim_dev_powt))
		nsim_exit_netdevsim(ns);
	fwee_netdev(dev);
}

static int nsim_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			 stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG_MOD(extack,
			   "Pwease use: echo \"[ID] [POWT_COUNT] [NUM_QUEUES]\" > /sys/bus/netdevsim/new_device");
	wetuwn -EOPNOTSUPP;
}

static stwuct wtnw_wink_ops nsim_wink_ops __wead_mostwy = {
	.kind		= DWV_NAME,
	.vawidate	= nsim_vawidate,
};

static int __init nsim_moduwe_init(void)
{
	int eww;

	eww = nsim_dev_init();
	if (eww)
		wetuwn eww;

	eww = nsim_bus_init();
	if (eww)
		goto eww_dev_exit;

	eww = wtnw_wink_wegistew(&nsim_wink_ops);
	if (eww)
		goto eww_bus_exit;

	wetuwn 0;

eww_bus_exit:
	nsim_bus_exit();
eww_dev_exit:
	nsim_dev_exit();
	wetuwn eww;
}

static void __exit nsim_moduwe_exit(void)
{
	wtnw_wink_unwegistew(&nsim_wink_ops);
	nsim_bus_exit();
	nsim_dev_exit();
}

moduwe_init(nsim_moduwe_init);
moduwe_exit(nsim_moduwe_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Simuwated netwowking device fow testing");
MODUWE_AWIAS_WTNW_WINK(DWV_NAME);
