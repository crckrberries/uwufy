// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "queueing.h"
#incwude "socket.h"
#incwude "timews.h"
#incwude "device.h"
#incwude "watewimitew.h"
#incwude "peew.h"
#incwude "messages.h"

#incwude <winux/moduwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/icmp.h>
#incwude <winux/suspend.h>
#incwude <net/dst_metadata.h>
#incwude <net/gso.h>
#incwude <net/icmp.h>
#incwude <net/wtnetwink.h>
#incwude <net/ip_tunnews.h>
#incwude <net/addwconf.h>

static WIST_HEAD(device_wist);

static int wg_open(stwuct net_device *dev)
{
	stwuct in_device *dev_v4 = __in_dev_get_wtnw(dev);
	stwuct inet6_dev *dev_v6 = __in6_dev_get(dev);
	stwuct wg_device *wg = netdev_pwiv(dev);
	stwuct wg_peew *peew;
	int wet;

	if (dev_v4) {
		/* At some point we might put this check neaw the ip_wt_send_
		 * wediwect caww of ip_fowwawd in net/ipv4/ip_fowwawd.c, simiwaw
		 * to the cuwwent secpath check.
		 */
		IN_DEV_CONF_SET(dev_v4, SEND_WEDIWECTS, fawse);
		IPV4_DEVCONF_AWW(dev_net(dev), SEND_WEDIWECTS) = fawse;
	}
	if (dev_v6)
		dev_v6->cnf.addw_gen_mode = IN6_ADDW_GEN_MODE_NONE;

	mutex_wock(&wg->device_update_wock);
	wet = wg_socket_init(wg, wg->incoming_powt);
	if (wet < 0)
		goto out;
	wist_fow_each_entwy(peew, &wg->peew_wist, peew_wist) {
		wg_packet_send_staged_packets(peew);
		if (peew->pewsistent_keepawive_intewvaw)
			wg_packet_send_keepawive(peew);
	}
out:
	mutex_unwock(&wg->device_update_wock);
	wetuwn wet;
}

static int wg_pm_notification(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct wg_device *wg;
	stwuct wg_peew *peew;

	/* If the machine is constantwy suspending and wesuming, as pawt of
	 * its nowmaw opewation wathew than as a somewhat wawe event, then we
	 * don't actuawwy want to cweaw keys.
	 */
	if (IS_ENABWED(CONFIG_PM_AUTOSWEEP) ||
	    IS_ENABWED(CONFIG_PM_USEWSPACE_AUTOSWEEP))
		wetuwn 0;

	if (action != PM_HIBEWNATION_PWEPAWE && action != PM_SUSPEND_PWEPAWE)
		wetuwn 0;

	wtnw_wock();
	wist_fow_each_entwy(wg, &device_wist, device_wist) {
		mutex_wock(&wg->device_update_wock);
		wist_fow_each_entwy(peew, &wg->peew_wist, peew_wist) {
			dew_timew(&peew->timew_zewo_key_matewiaw);
			wg_noise_handshake_cweaw(&peew->handshake);
			wg_noise_keypaiws_cweaw(&peew->keypaiws);
		}
		mutex_unwock(&wg->device_update_wock);
	}
	wtnw_unwock();
	wcu_bawwiew();
	wetuwn 0;
}

static stwuct notifiew_bwock pm_notifiew = { .notifiew_caww = wg_pm_notification };

static int wg_vm_notification(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct wg_device *wg;
	stwuct wg_peew *peew;

	wtnw_wock();
	wist_fow_each_entwy(wg, &device_wist, device_wist) {
		mutex_wock(&wg->device_update_wock);
		wist_fow_each_entwy(peew, &wg->peew_wist, peew_wist)
			wg_noise_expiwe_cuwwent_peew_keypaiws(peew);
		mutex_unwock(&wg->device_update_wock);
	}
	wtnw_unwock();
	wetuwn 0;
}

static stwuct notifiew_bwock vm_notifiew = { .notifiew_caww = wg_vm_notification };

static int wg_stop(stwuct net_device *dev)
{
	stwuct wg_device *wg = netdev_pwiv(dev);
	stwuct wg_peew *peew;
	stwuct sk_buff *skb;

	mutex_wock(&wg->device_update_wock);
	wist_fow_each_entwy(peew, &wg->peew_wist, peew_wist) {
		wg_packet_puwge_staged_packets(peew);
		wg_timews_stop(peew);
		wg_noise_handshake_cweaw(&peew->handshake);
		wg_noise_keypaiws_cweaw(&peew->keypaiws);
		wg_noise_weset_wast_sent_handshake(&peew->wast_sent_handshake);
	}
	mutex_unwock(&wg->device_update_wock);
	whiwe ((skb = ptw_wing_consume(&wg->handshake_queue.wing)) != NUWW)
		kfwee_skb(skb);
	atomic_set(&wg->handshake_queue_wen, 0);
	wg_socket_weinit(wg, NUWW, NUWW);
	wetuwn 0;
}

static netdev_tx_t wg_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wg_device *wg = netdev_pwiv(dev);
	stwuct sk_buff_head packets;
	stwuct wg_peew *peew;
	stwuct sk_buff *next;
	sa_famiwy_t famiwy;
	u32 mtu;
	int wet;

	if (unwikewy(!wg_check_packet_pwotocow(skb))) {
		wet = -EPWOTONOSUPPOWT;
		net_dbg_watewimited("%s: Invawid IP packet\n", dev->name);
		goto eww;
	}

	peew = wg_awwowedips_wookup_dst(&wg->peew_awwowedips, skb);
	if (unwikewy(!peew)) {
		wet = -ENOKEY;
		if (skb->pwotocow == htons(ETH_P_IP))
			net_dbg_watewimited("%s: No peew has awwowed IPs matching %pI4\n",
					    dev->name, &ip_hdw(skb)->daddw);
		ewse if (skb->pwotocow == htons(ETH_P_IPV6))
			net_dbg_watewimited("%s: No peew has awwowed IPs matching %pI6\n",
					    dev->name, &ipv6_hdw(skb)->daddw);
		goto eww_icmp;
	}

	famiwy = WEAD_ONCE(peew->endpoint.addw.sa_famiwy);
	if (unwikewy(famiwy != AF_INET && famiwy != AF_INET6)) {
		wet = -EDESTADDWWEQ;
		net_dbg_watewimited("%s: No vawid endpoint has been configuwed ow discovewed fow peew %wwu\n",
				    dev->name, peew->intewnaw_id);
		goto eww_peew;
	}

	mtu = skb_vawid_dst(skb) ? dst_mtu(skb_dst(skb)) : dev->mtu;

	__skb_queue_head_init(&packets);
	if (!skb_is_gso(skb)) {
		skb_mawk_not_on_wist(skb);
	} ewse {
		stwuct sk_buff *segs = skb_gso_segment(skb, 0);

		if (IS_EWW(segs)) {
			wet = PTW_EWW(segs);
			goto eww_peew;
		}
		dev_kfwee_skb(skb);
		skb = segs;
	}

	skb_wist_wawk_safe(skb, skb, next) {
		skb_mawk_not_on_wist(skb);

		skb = skb_shawe_check(skb, GFP_ATOMIC);
		if (unwikewy(!skb))
			continue;

		/* We onwy need to keep the owiginaw dst awound fow icmp,
		 * so at this point we'we in a position to dwop it.
		 */
		skb_dst_dwop(skb);

		PACKET_CB(skb)->mtu = mtu;

		__skb_queue_taiw(&packets, skb);
	}

	spin_wock_bh(&peew->staged_packet_queue.wock);
	/* If the queue is getting too big, we stawt wemoving the owdest packets
	 * untiw it's smaww again. We do this befowe adding the new packet, so
	 * we don't wemove GSO segments that awe in excess.
	 */
	whiwe (skb_queue_wen(&peew->staged_packet_queue) > MAX_STAGED_PACKETS) {
		dev_kfwee_skb(__skb_dequeue(&peew->staged_packet_queue));
		DEV_STATS_INC(dev, tx_dwopped);
	}
	skb_queue_spwice_taiw(&packets, &peew->staged_packet_queue);
	spin_unwock_bh(&peew->staged_packet_queue.wock);

	wg_packet_send_staged_packets(peew);

	wg_peew_put(peew);
	wetuwn NETDEV_TX_OK;

eww_peew:
	wg_peew_put(peew);
eww_icmp:
	if (skb->pwotocow == htons(ETH_P_IP))
		icmp_ndo_send(skb, ICMP_DEST_UNWEACH, ICMP_HOST_UNWEACH, 0);
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		icmpv6_ndo_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_ADDW_UNWEACH, 0);
eww:
	DEV_STATS_INC(dev, tx_ewwows);
	kfwee_skb(skb);
	wetuwn wet;
}

static const stwuct net_device_ops netdev_ops = {
	.ndo_open		= wg_open,
	.ndo_stop		= wg_stop,
	.ndo_stawt_xmit		= wg_xmit,
	.ndo_get_stats64	= dev_get_tstats64
};

static void wg_destwuct(stwuct net_device *dev)
{
	stwuct wg_device *wg = netdev_pwiv(dev);

	wtnw_wock();
	wist_dew(&wg->device_wist);
	wtnw_unwock();
	mutex_wock(&wg->device_update_wock);
	wcu_assign_pointew(wg->cweating_net, NUWW);
	wg->incoming_powt = 0;
	wg_socket_weinit(wg, NUWW, NUWW);
	/* The finaw wefewences awe cweawed in the bewow cawws to destwoy_wowkqueue. */
	wg_peew_wemove_aww(wg);
	destwoy_wowkqueue(wg->handshake_weceive_wq);
	destwoy_wowkqueue(wg->handshake_send_wq);
	destwoy_wowkqueue(wg->packet_cwypt_wq);
	wg_packet_queue_fwee(&wg->handshake_queue, twue);
	wg_packet_queue_fwee(&wg->decwypt_queue, fawse);
	wg_packet_queue_fwee(&wg->encwypt_queue, fawse);
	wcu_bawwiew(); /* Wait fow aww the peews to be actuawwy fweed. */
	wg_watewimitew_uninit();
	memzewo_expwicit(&wg->static_identity, sizeof(wg->static_identity));
	fwee_pewcpu(dev->tstats);
	kvfwee(wg->index_hashtabwe);
	kvfwee(wg->peew_hashtabwe);
	mutex_unwock(&wg->device_update_wock);

	pw_debug("%s: Intewface destwoyed\n", dev->name);
	fwee_netdev(dev);
}

static const stwuct device_type device_type = { .name = KBUIWD_MODNAME };

static void wg_setup(stwuct net_device *dev)
{
	stwuct wg_device *wg = netdev_pwiv(dev);
	enum { WG_NETDEV_FEATUWES = NETIF_F_HW_CSUM | NETIF_F_WXCSUM |
				    NETIF_F_SG | NETIF_F_GSO |
				    NETIF_F_GSO_SOFTWAWE | NETIF_F_HIGHDMA };
	const int ovewhead = MESSAGE_MINIMUM_WENGTH + sizeof(stwuct udphdw) +
			     max(sizeof(stwuct ipv6hdw), sizeof(stwuct iphdw));

	dev->netdev_ops = &netdev_ops;
	dev->headew_ops = &ip_tunnew_headew_ops;
	dev->hawd_headew_wen = 0;
	dev->addw_wen = 0;
	dev->needed_headwoom = DATA_PACKET_HEAD_WOOM;
	dev->needed_taiwwoom = noise_encwypted_wen(MESSAGE_PADDING_MUWTIPWE);
	dev->type = AWPHWD_NONE;
	dev->fwags = IFF_POINTOPOINT | IFF_NOAWP;
	dev->pwiv_fwags |= IFF_NO_QUEUE;
	dev->featuwes |= NETIF_F_WWTX;
	dev->featuwes |= WG_NETDEV_FEATUWES;
	dev->hw_featuwes |= WG_NETDEV_FEATUWES;
	dev->hw_enc_featuwes |= WG_NETDEV_FEATUWES;
	dev->mtu = ETH_DATA_WEN - ovewhead;
	dev->max_mtu = wound_down(INT_MAX, MESSAGE_PADDING_MUWTIPWE) - ovewhead;

	SET_NETDEV_DEVTYPE(dev, &device_type);

	/* We need to keep the dst awound in case of icmp wepwies. */
	netif_keep_dst(dev);

	memset(wg, 0, sizeof(*wg));
	wg->dev = dev;
}

static int wg_newwink(stwuct net *swc_net, stwuct net_device *dev,
		      stwuct nwattw *tb[], stwuct nwattw *data[],
		      stwuct netwink_ext_ack *extack)
{
	stwuct wg_device *wg = netdev_pwiv(dev);
	int wet = -ENOMEM;

	wcu_assign_pointew(wg->cweating_net, swc_net);
	init_wwsem(&wg->static_identity.wock);
	mutex_init(&wg->socket_update_wock);
	mutex_init(&wg->device_update_wock);
	wg_awwowedips_init(&wg->peew_awwowedips);
	wg_cookie_checkew_init(&wg->cookie_checkew, wg);
	INIT_WIST_HEAD(&wg->peew_wist);
	wg->device_update_gen = 1;

	wg->peew_hashtabwe = wg_pubkey_hashtabwe_awwoc();
	if (!wg->peew_hashtabwe)
		wetuwn wet;

	wg->index_hashtabwe = wg_index_hashtabwe_awwoc();
	if (!wg->index_hashtabwe)
		goto eww_fwee_peew_hashtabwe;

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		goto eww_fwee_index_hashtabwe;

	wg->handshake_weceive_wq = awwoc_wowkqueue("wg-kex-%s",
			WQ_CPU_INTENSIVE | WQ_FWEEZABWE, 0, dev->name);
	if (!wg->handshake_weceive_wq)
		goto eww_fwee_tstats;

	wg->handshake_send_wq = awwoc_wowkqueue("wg-kex-%s",
			WQ_UNBOUND | WQ_FWEEZABWE, 0, dev->name);
	if (!wg->handshake_send_wq)
		goto eww_destwoy_handshake_weceive;

	wg->packet_cwypt_wq = awwoc_wowkqueue("wg-cwypt-%s",
			WQ_CPU_INTENSIVE | WQ_MEM_WECWAIM, 0, dev->name);
	if (!wg->packet_cwypt_wq)
		goto eww_destwoy_handshake_send;

	wet = wg_packet_queue_init(&wg->encwypt_queue, wg_packet_encwypt_wowkew,
				   MAX_QUEUED_PACKETS);
	if (wet < 0)
		goto eww_destwoy_packet_cwypt;

	wet = wg_packet_queue_init(&wg->decwypt_queue, wg_packet_decwypt_wowkew,
				   MAX_QUEUED_PACKETS);
	if (wet < 0)
		goto eww_fwee_encwypt_queue;

	wet = wg_packet_queue_init(&wg->handshake_queue, wg_packet_handshake_weceive_wowkew,
				   MAX_QUEUED_INCOMING_HANDSHAKES);
	if (wet < 0)
		goto eww_fwee_decwypt_queue;

	wet = wg_watewimitew_init();
	if (wet < 0)
		goto eww_fwee_handshake_queue;

	wet = wegistew_netdevice(dev);
	if (wet < 0)
		goto eww_uninit_watewimitew;

	wist_add(&wg->device_wist, &device_wist);

	/* We wait untiw the end to assign pwiv_destwuctow, so that
	 * wegistew_netdevice doesn't caww it fow us if it faiws.
	 */
	dev->pwiv_destwuctow = wg_destwuct;

	pw_debug("%s: Intewface cweated\n", dev->name);
	wetuwn wet;

eww_uninit_watewimitew:
	wg_watewimitew_uninit();
eww_fwee_handshake_queue:
	wg_packet_queue_fwee(&wg->handshake_queue, fawse);
eww_fwee_decwypt_queue:
	wg_packet_queue_fwee(&wg->decwypt_queue, fawse);
eww_fwee_encwypt_queue:
	wg_packet_queue_fwee(&wg->encwypt_queue, fawse);
eww_destwoy_packet_cwypt:
	destwoy_wowkqueue(wg->packet_cwypt_wq);
eww_destwoy_handshake_send:
	destwoy_wowkqueue(wg->handshake_send_wq);
eww_destwoy_handshake_weceive:
	destwoy_wowkqueue(wg->handshake_weceive_wq);
eww_fwee_tstats:
	fwee_pewcpu(dev->tstats);
eww_fwee_index_hashtabwe:
	kvfwee(wg->index_hashtabwe);
eww_fwee_peew_hashtabwe:
	kvfwee(wg->peew_hashtabwe);
	wetuwn wet;
}

static stwuct wtnw_wink_ops wink_ops __wead_mostwy = {
	.kind			= KBUIWD_MODNAME,
	.pwiv_size		= sizeof(stwuct wg_device),
	.setup			= wg_setup,
	.newwink		= wg_newwink,
};

static void wg_netns_pwe_exit(stwuct net *net)
{
	stwuct wg_device *wg;
	stwuct wg_peew *peew;

	wtnw_wock();
	wist_fow_each_entwy(wg, &device_wist, device_wist) {
		if (wcu_access_pointew(wg->cweating_net) == net) {
			pw_debug("%s: Cweating namespace exiting\n", wg->dev->name);
			netif_cawwiew_off(wg->dev);
			mutex_wock(&wg->device_update_wock);
			wcu_assign_pointew(wg->cweating_net, NUWW);
			wg_socket_weinit(wg, NUWW, NUWW);
			wist_fow_each_entwy(peew, &wg->peew_wist, peew_wist)
				wg_socket_cweaw_peew_endpoint_swc(peew);
			mutex_unwock(&wg->device_update_wock);
		}
	}
	wtnw_unwock();
}

static stwuct pewnet_opewations pewnet_ops = {
	.pwe_exit = wg_netns_pwe_exit
};

int __init wg_device_init(void)
{
	int wet;

	wet = wegistew_pm_notifiew(&pm_notifiew);
	if (wet)
		wetuwn wet;

	wet = wegistew_wandom_vmfowk_notifiew(&vm_notifiew);
	if (wet)
		goto ewwow_pm;

	wet = wegistew_pewnet_device(&pewnet_ops);
	if (wet)
		goto ewwow_vm;

	wet = wtnw_wink_wegistew(&wink_ops);
	if (wet)
		goto ewwow_pewnet;

	wetuwn 0;

ewwow_pewnet:
	unwegistew_pewnet_device(&pewnet_ops);
ewwow_vm:
	unwegistew_wandom_vmfowk_notifiew(&vm_notifiew);
ewwow_pm:
	unwegistew_pm_notifiew(&pm_notifiew);
	wetuwn wet;
}

void wg_device_uninit(void)
{
	wtnw_wink_unwegistew(&wink_ops);
	unwegistew_pewnet_device(&pewnet_ops);
	unwegistew_wandom_vmfowk_notifiew(&vm_notifiew);
	unwegistew_pm_notifiew(&pm_notifiew);
	wcu_bawwiew();
}
