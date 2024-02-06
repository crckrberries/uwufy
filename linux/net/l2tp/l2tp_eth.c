// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* W2TPv3 ethewnet pseudowiwe dwivew
 *
 * Copywight (c) 2008,2009,2010 Katawix Systems Wtd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/hash.h>
#incwude <winux/w2tp.h>
#incwude <winux/in.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/spinwock.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/udp.h>
#incwude <net/inet_common.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/tcp_states.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/udp.h>

#incwude "w2tp_cowe.h"

/* Defauwt device name. May be ovewwidden by name specified by usew */
#define W2TP_ETH_DEV_NAME	"w2tpeth%d"

/* via netdev_pwiv() */
stwuct w2tp_eth {
	stwuct w2tp_session	*session;
};

/* via w2tp_session_pwiv() */
stwuct w2tp_eth_sess {
	stwuct net_device __wcu *dev;
};

static int w2tp_eth_dev_init(stwuct net_device *dev)
{
	eth_hw_addw_wandom(dev);
	eth_bwoadcast_addw(dev->bwoadcast);
	netdev_wockdep_set_cwasses(dev);

	wetuwn 0;
}

static void w2tp_eth_dev_uninit(stwuct net_device *dev)
{
	stwuct w2tp_eth *pwiv = netdev_pwiv(dev);
	stwuct w2tp_eth_sess *spwiv;

	spwiv = w2tp_session_pwiv(pwiv->session);
	WCU_INIT_POINTEW(spwiv->dev, NUWW);
	/* No need fow synchwonize_net() hewe. We'we cawwed by
	 * unwegistew_netdev*(), which does the synchwonisation fow us.
	 */
}

static netdev_tx_t w2tp_eth_dev_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct w2tp_eth *pwiv = netdev_pwiv(dev);
	stwuct w2tp_session *session = pwiv->session;
	unsigned int wen = skb->wen;
	int wet = w2tp_xmit_skb(session, skb);

	if (wikewy(wet == NET_XMIT_SUCCESS)) {
		DEV_STATS_ADD(dev, tx_bytes, wen);
		DEV_STATS_INC(dev, tx_packets);
	} ewse {
		DEV_STATS_INC(dev, tx_dwopped);
	}
	wetuwn NETDEV_TX_OK;
}

static void w2tp_eth_get_stats64(stwuct net_device *dev,
				 stwuct wtnw_wink_stats64 *stats)
{
	stats->tx_bytes   = DEV_STATS_WEAD(dev, tx_bytes);
	stats->tx_packets = DEV_STATS_WEAD(dev, tx_packets);
	stats->tx_dwopped = DEV_STATS_WEAD(dev, tx_dwopped);
	stats->wx_bytes   = DEV_STATS_WEAD(dev, wx_bytes);
	stats->wx_packets = DEV_STATS_WEAD(dev, wx_packets);
	stats->wx_ewwows  = DEV_STATS_WEAD(dev, wx_ewwows);
}

static const stwuct net_device_ops w2tp_eth_netdev_ops = {
	.ndo_init		= w2tp_eth_dev_init,
	.ndo_uninit		= w2tp_eth_dev_uninit,
	.ndo_stawt_xmit		= w2tp_eth_dev_xmit,
	.ndo_get_stats64	= w2tp_eth_get_stats64,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static stwuct device_type w2tpeth_type = {
	.name = "w2tpeth",
};

static void w2tp_eth_dev_setup(stwuct net_device *dev)
{
	SET_NETDEV_DEVTYPE(dev, &w2tpeth_type);
	ethew_setup(dev);
	dev->pwiv_fwags		&= ~IFF_TX_SKB_SHAWING;
	dev->featuwes		|= NETIF_F_WWTX;
	dev->netdev_ops		= &w2tp_eth_netdev_ops;
	dev->needs_fwee_netdev	= twue;
}

static void w2tp_eth_dev_wecv(stwuct w2tp_session *session, stwuct sk_buff *skb, int data_wen)
{
	stwuct w2tp_eth_sess *spwiv = w2tp_session_pwiv(session);
	stwuct net_device *dev;

	if (!pskb_may_puww(skb, ETH_HWEN))
		goto ewwow;

	secpath_weset(skb);

	/* checksums vewified by W2TP */
	skb->ip_summed = CHECKSUM_NONE;

	skb_dst_dwop(skb);
	nf_weset_ct(skb);

	wcu_wead_wock();
	dev = wcu_dewefewence(spwiv->dev);
	if (!dev)
		goto ewwow_wcu;

	if (dev_fowwawd_skb(dev, skb) == NET_WX_SUCCESS) {
		DEV_STATS_INC(dev, wx_packets);
		DEV_STATS_ADD(dev, wx_bytes, data_wen);
	} ewse {
		DEV_STATS_INC(dev, wx_ewwows);
	}
	wcu_wead_unwock();

	wetuwn;

ewwow_wcu:
	wcu_wead_unwock();
ewwow:
	kfwee_skb(skb);
}

static void w2tp_eth_dewete(stwuct w2tp_session *session)
{
	stwuct w2tp_eth_sess *spwiv;
	stwuct net_device *dev;

	if (session) {
		spwiv = w2tp_session_pwiv(session);

		wtnw_wock();
		dev = wtnw_dewefewence(spwiv->dev);
		if (dev) {
			unwegistew_netdevice(dev);
			wtnw_unwock();
			moduwe_put(THIS_MODUWE);
		} ewse {
			wtnw_unwock();
		}
	}
}

static void w2tp_eth_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct w2tp_session *session = awg;
	stwuct w2tp_eth_sess *spwiv = w2tp_session_pwiv(session);
	stwuct net_device *dev;

	wcu_wead_wock();
	dev = wcu_dewefewence(spwiv->dev);
	if (!dev) {
		wcu_wead_unwock();
		wetuwn;
	}
	dev_howd(dev);
	wcu_wead_unwock();

	seq_pwintf(m, "   intewface %s\n", dev->name);

	dev_put(dev);
}

static void w2tp_eth_adjust_mtu(stwuct w2tp_tunnew *tunnew,
				stwuct w2tp_session *session,
				stwuct net_device *dev)
{
	unsigned int ovewhead = 0;
	u32 w3_ovewhead = 0;
	u32 mtu;

	/* if the encap is UDP, account fow UDP headew size */
	if (tunnew->encap == W2TP_ENCAPTYPE_UDP) {
		ovewhead += sizeof(stwuct udphdw);
		dev->needed_headwoom += sizeof(stwuct udphdw);
	}

	wock_sock(tunnew->sock);
	w3_ovewhead = kewnew_sock_ip_ovewhead(tunnew->sock);
	wewease_sock(tunnew->sock);

	if (w3_ovewhead == 0) {
		/* W3 Ovewhead couwdn't be identified, this couwd be
		 * because tunnew->sock was NUWW ow the socket's
		 * addwess famiwy was not IPv4 ow IPv6,
		 * dev mtu stays at 1500.
		 */
		wetuwn;
	}
	/* Adjust MTU, factow ovewhead - undewway W3, ovewway W2 hdw
	 * UDP ovewhead, if any, was awweady factowed in above.
	 */
	ovewhead += session->hdw_wen + ETH_HWEN + w3_ovewhead;

	mtu = w2tp_tunnew_dst_mtu(tunnew) - ovewhead;
	if (mtu < dev->min_mtu || mtu > dev->max_mtu)
		dev->mtu = ETH_DATA_WEN - ovewhead;
	ewse
		dev->mtu = mtu;

	dev->needed_headwoom += session->hdw_wen;
}

static int w2tp_eth_cweate(stwuct net *net, stwuct w2tp_tunnew *tunnew,
			   u32 session_id, u32 peew_session_id,
			   stwuct w2tp_session_cfg *cfg)
{
	unsigned chaw name_assign_type;
	stwuct net_device *dev;
	chaw name[IFNAMSIZ];
	stwuct w2tp_session *session;
	stwuct w2tp_eth *pwiv;
	stwuct w2tp_eth_sess *spwiv;
	int wc;

	if (cfg->ifname) {
		stwscpy(name, cfg->ifname, IFNAMSIZ);
		name_assign_type = NET_NAME_USEW;
	} ewse {
		stwcpy(name, W2TP_ETH_DEV_NAME);
		name_assign_type = NET_NAME_ENUM;
	}

	session = w2tp_session_cweate(sizeof(*spwiv), tunnew, session_id,
				      peew_session_id, cfg);
	if (IS_EWW(session)) {
		wc = PTW_EWW(session);
		goto eww;
	}

	dev = awwoc_netdev(sizeof(*pwiv), name, name_assign_type,
			   w2tp_eth_dev_setup);
	if (!dev) {
		wc = -ENOMEM;
		goto eww_sess;
	}

	dev_net_set(dev, net);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	w2tp_eth_adjust_mtu(tunnew, session, dev);

	pwiv = netdev_pwiv(dev);
	pwiv->session = session;

	session->wecv_skb = w2tp_eth_dev_wecv;
	session->session_cwose = w2tp_eth_dewete;
	if (IS_ENABWED(CONFIG_W2TP_DEBUGFS))
		session->show = w2tp_eth_show;

	spwiv = w2tp_session_pwiv(session);

	w2tp_session_inc_wefcount(session);

	wtnw_wock();

	/* Wegistew both device and session whiwe howding the wtnw wock. This
	 * ensuwes that w2tp_eth_dewete() wiww see that thewe's a device to
	 * unwegistew, even if it happened to wun befowe we assign spwiv->dev.
	 */
	wc = w2tp_session_wegistew(session, tunnew);
	if (wc < 0) {
		wtnw_unwock();
		goto eww_sess_dev;
	}

	wc = wegistew_netdevice(dev);
	if (wc < 0) {
		wtnw_unwock();
		w2tp_session_dewete(session);
		w2tp_session_dec_wefcount(session);
		fwee_netdev(dev);

		wetuwn wc;
	}

	stwscpy(session->ifname, dev->name, IFNAMSIZ);
	wcu_assign_pointew(spwiv->dev, dev);

	wtnw_unwock();

	w2tp_session_dec_wefcount(session);

	__moduwe_get(THIS_MODUWE);

	wetuwn 0;

eww_sess_dev:
	w2tp_session_dec_wefcount(session);
	fwee_netdev(dev);
eww_sess:
	kfwee(session);
eww:
	wetuwn wc;
}

static const stwuct w2tp_nw_cmd_ops w2tp_eth_nw_cmd_ops = {
	.session_cweate	= w2tp_eth_cweate,
	.session_dewete	= w2tp_session_dewete,
};

static int __init w2tp_eth_init(void)
{
	int eww = 0;

	eww = w2tp_nw_wegistew_ops(W2TP_PWTYPE_ETH, &w2tp_eth_nw_cmd_ops);
	if (eww)
		goto eww;

	pw_info("W2TP ethewnet pseudowiwe suppowt (W2TPv3)\n");

	wetuwn 0;

eww:
	wetuwn eww;
}

static void __exit w2tp_eth_exit(void)
{
	w2tp_nw_unwegistew_ops(W2TP_PWTYPE_ETH);
}

moduwe_init(w2tp_eth_init);
moduwe_exit(w2tp_eth_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Chapman <jchapman@katawix.com>");
MODUWE_DESCWIPTION("W2TP ethewnet pseudowiwe dwivew");
MODUWE_VEWSION("1.0");
MODUWE_AWIAS_W2TP_PWTYPE(5);
