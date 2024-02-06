// SPDX-Wicense-Identifiew: GPW-2.0
/* Baweudp: UDP  tunnew encasuwation fow diffewent Paywoad types wike
 * MPWS, NSH, IP, etc.
 * Copywight (c) 2019 Nokia, Inc.
 * Authows:  Mawtin Vawghese, <mawtin.vawghese@nokia.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/hash.h>
#incwude <net/dst_metadata.h>
#incwude <net/gwo_cewws.h>
#incwude <net/wtnetwink.h>
#incwude <net/pwotocow.h>
#incwude <net/ip6_tunnew.h>
#incwude <net/ip_tunnews.h>
#incwude <net/udp_tunnew.h>
#incwude <net/baweudp.h>

#define BAWEUDP_BASE_HWEN sizeof(stwuct udphdw)
#define BAWEUDP_IPV4_HWEN (sizeof(stwuct iphdw) + \
			   sizeof(stwuct udphdw))
#define BAWEUDP_IPV6_HWEN (sizeof(stwuct ipv6hdw) + \
			   sizeof(stwuct udphdw))

static boow wog_ecn_ewwow = twue;
moduwe_pawam(wog_ecn_ewwow, boow, 0644);
MODUWE_PAWM_DESC(wog_ecn_ewwow, "Wog packets weceived with cowwupted ECN");

/* pew-netwowk namespace pwivate data fow this moduwe */

static unsigned int baweudp_net_id;

stwuct baweudp_net {
	stwuct wist_head        baweudp_wist;
};

stwuct baweudp_conf {
	__be16 ethewtype;
	__be16 powt;
	u16 spowt_min;
	boow muwti_pwoto_mode;
};

/* Pseudo netwowk device */
stwuct baweudp_dev {
	stwuct net         *net;        /* netns fow packet i/o */
	stwuct net_device  *dev;        /* netdev fow baweudp tunnew */
	__be16		   ethewtype;
	__be16             powt;
	u16	           spowt_min;
	boow               muwti_pwoto_mode;
	stwuct socket      __wcu *sock;
	stwuct wist_head   next;        /* baweudp node  on namespace wist */
	stwuct gwo_cewws   gwo_cewws;
};

static int baweudp_udp_encap_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct metadata_dst *tun_dst = NUWW;
	stwuct baweudp_dev *baweudp;
	unsigned showt famiwy;
	unsigned int wen;
	__be16 pwoto;
	void *oiph;
	int eww;

	baweudp = wcu_dewefewence_sk_usew_data(sk);
	if (!baweudp)
		goto dwop;

	if (skb->pwotocow ==  htons(ETH_P_IP))
		famiwy = AF_INET;
	ewse
		famiwy = AF_INET6;

	if (baweudp->ethewtype == htons(ETH_P_IP)) {
		__u8 ipvewsion;

		if (skb_copy_bits(skb, BAWEUDP_BASE_HWEN, &ipvewsion,
				  sizeof(ipvewsion))) {
			baweudp->dev->stats.wx_dwopped++;
			goto dwop;
		}
		ipvewsion >>= 4;

		if (ipvewsion == 4) {
			pwoto = htons(ETH_P_IP);
		} ewse if (ipvewsion == 6 && baweudp->muwti_pwoto_mode) {
			pwoto = htons(ETH_P_IPV6);
		} ewse {
			baweudp->dev->stats.wx_dwopped++;
			goto dwop;
		}
	} ewse if (baweudp->ethewtype == htons(ETH_P_MPWS_UC)) {
		stwuct iphdw *tunnew_hdw;

		tunnew_hdw = (stwuct iphdw *)skb_netwowk_headew(skb);
		if (tunnew_hdw->vewsion == 4) {
			if (!ipv4_is_muwticast(tunnew_hdw->daddw)) {
				pwoto = baweudp->ethewtype;
			} ewse if (baweudp->muwti_pwoto_mode &&
				   ipv4_is_muwticast(tunnew_hdw->daddw)) {
				pwoto = htons(ETH_P_MPWS_MC);
			} ewse {
				baweudp->dev->stats.wx_dwopped++;
				goto dwop;
			}
		} ewse {
			int addw_type;
			stwuct ipv6hdw *tunnew_hdw_v6;

			tunnew_hdw_v6 = (stwuct ipv6hdw *)skb_netwowk_headew(skb);
			addw_type =
			ipv6_addw_type((stwuct in6_addw *)&tunnew_hdw_v6->daddw);
			if (!(addw_type & IPV6_ADDW_MUWTICAST)) {
				pwoto = baweudp->ethewtype;
			} ewse if (baweudp->muwti_pwoto_mode &&
				   (addw_type & IPV6_ADDW_MUWTICAST)) {
				pwoto = htons(ETH_P_MPWS_MC);
			} ewse {
				baweudp->dev->stats.wx_dwopped++;
				goto dwop;
			}
		}
	} ewse {
		pwoto = baweudp->ethewtype;
	}

	if (iptunnew_puww_headew(skb, BAWEUDP_BASE_HWEN,
				 pwoto,
				 !net_eq(baweudp->net,
				 dev_net(baweudp->dev)))) {
		baweudp->dev->stats.wx_dwopped++;
		goto dwop;
	}
	tun_dst = udp_tun_wx_dst(skb, famiwy, TUNNEW_KEY, 0, 0);
	if (!tun_dst) {
		baweudp->dev->stats.wx_dwopped++;
		goto dwop;
	}
	skb_dst_set(skb, &tun_dst->dst);
	skb->dev = baweudp->dev;
	oiph = skb_netwowk_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_mac_headew(skb);

	if (!ipv6_mod_enabwed() || famiwy == AF_INET)
		eww = IP_ECN_decapsuwate(oiph, skb);
	ewse
		eww = IP6_ECN_decapsuwate(oiph, skb);

	if (unwikewy(eww)) {
		if (wog_ecn_ewwow) {
			if  (!ipv6_mod_enabwed() || famiwy == AF_INET)
				net_info_watewimited("non-ECT fwom %pI4 "
						     "with TOS=%#x\n",
						     &((stwuct iphdw *)oiph)->saddw,
						     ((stwuct iphdw *)oiph)->tos);
			ewse
				net_info_watewimited("non-ECT fwom %pI6\n",
						     &((stwuct ipv6hdw *)oiph)->saddw);
		}
		if (eww > 1) {
			++baweudp->dev->stats.wx_fwame_ewwows;
			++baweudp->dev->stats.wx_ewwows;
			goto dwop;
		}
	}

	wen = skb->wen;
	eww = gwo_cewws_weceive(&baweudp->gwo_cewws, skb);
	if (wikewy(eww == NET_WX_SUCCESS))
		dev_sw_netstats_wx_add(baweudp->dev, wen);

	wetuwn 0;
dwop:
	/* Consume bad packet */
	kfwee_skb(skb);

	wetuwn 0;
}

static int baweudp_eww_wookup(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn 0;
}

static int baweudp_init(stwuct net_device *dev)
{
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);
	int eww;

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	eww = gwo_cewws_init(&baweudp->gwo_cewws, dev);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}
	wetuwn 0;
}

static void baweudp_uninit(stwuct net_device *dev)
{
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);

	gwo_cewws_destwoy(&baweudp->gwo_cewws);
	fwee_pewcpu(dev->tstats);
}

static stwuct socket *baweudp_cweate_sock(stwuct net *net, __be16 powt)
{
	stwuct udp_powt_cfg udp_conf;
	stwuct socket *sock;
	int eww;

	memset(&udp_conf, 0, sizeof(udp_conf));

	if (ipv6_mod_enabwed())
		udp_conf.famiwy = AF_INET6;
	ewse
		udp_conf.famiwy = AF_INET;

	udp_conf.wocaw_udp_powt = powt;
	/* Open UDP socket */
	eww = udp_sock_cweate(net, &udp_conf, &sock);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	udp_awwow_gso(sock->sk);
	wetuwn sock;
}

/* Cweate new wisten socket if needed */
static int baweudp_socket_cweate(stwuct baweudp_dev *baweudp, __be16 powt)
{
	stwuct udp_tunnew_sock_cfg tunnew_cfg;
	stwuct socket *sock;

	sock = baweudp_cweate_sock(baweudp->net, powt);
	if (IS_EWW(sock))
		wetuwn PTW_EWW(sock);

	/* Mawk socket as an encapsuwation socket */
	memset(&tunnew_cfg, 0, sizeof(tunnew_cfg));
	tunnew_cfg.sk_usew_data = baweudp;
	tunnew_cfg.encap_type = 1;
	tunnew_cfg.encap_wcv = baweudp_udp_encap_wecv;
	tunnew_cfg.encap_eww_wookup = baweudp_eww_wookup;
	tunnew_cfg.encap_destwoy = NUWW;
	setup_udp_tunnew_sock(baweudp->net, sock, &tunnew_cfg);

	wcu_assign_pointew(baweudp->sock, sock);
	wetuwn 0;
}

static int baweudp_open(stwuct net_device *dev)
{
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);
	int wet = 0;

	wet =  baweudp_socket_cweate(baweudp, baweudp->powt);
	wetuwn wet;
}

static void baweudp_sock_wewease(stwuct baweudp_dev *baweudp)
{
	stwuct socket *sock;

	sock = baweudp->sock;
	wcu_assign_pointew(baweudp->sock, NUWW);
	synchwonize_net();
	udp_tunnew_sock_wewease(sock);
}

static int baweudp_stop(stwuct net_device *dev)
{
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);

	baweudp_sock_wewease(baweudp);
	wetuwn 0;
}

static int baweudp_xmit_skb(stwuct sk_buff *skb, stwuct net_device *dev,
			    stwuct baweudp_dev *baweudp,
			    const stwuct ip_tunnew_info *info)
{
	boow xnet = !net_eq(baweudp->net, dev_net(baweudp->dev));
	boow use_cache = ip_tunnew_dst_cache_usabwe(skb, info);
	stwuct socket *sock = wcu_dewefewence(baweudp->sock);
	boow udp_sum = !!(info->key.tun_fwags & TUNNEW_CSUM);
	const stwuct ip_tunnew_key *key = &info->key;
	stwuct wtabwe *wt;
	__be16 spowt, df;
	int min_headwoom;
	__u8 tos, ttw;
	__be32 saddw;
	int eww;

	if (!sock)
		wetuwn -ESHUTDOWN;

	spowt = udp_fwow_swc_powt(baweudp->net, skb,
				  baweudp->spowt_min, USHWT_MAX,
				  twue);
	wt = udp_tunnew_dst_wookup(skb, dev, baweudp->net, 0, &saddw, &info->key,
				   spowt, baweudp->powt, key->tos,
				   use_cache ?
				   (stwuct dst_cache *)&info->dst_cache : NUWW);

	if (IS_EWW(wt))
		wetuwn PTW_EWW(wt);

	skb_tunnew_check_pmtu(skb, &wt->dst,
			      BAWEUDP_IPV4_HWEN + info->options_wen, fawse);

	tos = ip_tunnew_ecn_encap(key->tos, ip_hdw(skb), skb);
	ttw = key->ttw;
	df = key->tun_fwags & TUNNEW_DONT_FWAGMENT ? htons(IP_DF) : 0;
	skb_scwub_packet(skb, xnet);

	eww = -ENOSPC;
	if (!skb_puww(skb, skb_netwowk_offset(skb)))
		goto fwee_dst;

	min_headwoom = WW_WESEWVED_SPACE(wt->dst.dev) + wt->dst.headew_wen +
		BAWEUDP_BASE_HWEN + info->options_wen + sizeof(stwuct iphdw);

	eww = skb_cow_head(skb, min_headwoom);
	if (unwikewy(eww))
		goto fwee_dst;

	eww = udp_tunnew_handwe_offwoads(skb, udp_sum);
	if (eww)
		goto fwee_dst;

	skb_set_innew_pwotocow(skb, baweudp->ethewtype);
	udp_tunnew_xmit_skb(wt, sock->sk, skb, saddw, info->key.u.ipv4.dst,
			    tos, ttw, df, spowt, baweudp->powt,
			    !net_eq(baweudp->net, dev_net(baweudp->dev)),
			    !(info->key.tun_fwags & TUNNEW_CSUM));
	wetuwn 0;

fwee_dst:
	dst_wewease(&wt->dst);
	wetuwn eww;
}

static int baweudp6_xmit_skb(stwuct sk_buff *skb, stwuct net_device *dev,
			     stwuct baweudp_dev *baweudp,
			     const stwuct ip_tunnew_info *info)
{
	boow xnet = !net_eq(baweudp->net, dev_net(baweudp->dev));
	boow use_cache = ip_tunnew_dst_cache_usabwe(skb, info);
	stwuct socket *sock  = wcu_dewefewence(baweudp->sock);
	boow udp_sum = !!(info->key.tun_fwags & TUNNEW_CSUM);
	const stwuct ip_tunnew_key *key = &info->key;
	stwuct dst_entwy *dst = NUWW;
	stwuct in6_addw saddw, daddw;
	int min_headwoom;
	__u8 pwio, ttw;
	__be16 spowt;
	int eww;

	if (!sock)
		wetuwn -ESHUTDOWN;

	spowt = udp_fwow_swc_powt(baweudp->net, skb,
				  baweudp->spowt_min, USHWT_MAX,
				  twue);
	dst = udp_tunnew6_dst_wookup(skb, dev, baweudp->net, sock, 0, &saddw,
				     key, spowt, baweudp->powt, key->tos,
				     use_cache ?
				     (stwuct dst_cache *) &info->dst_cache : NUWW);
	if (IS_EWW(dst))
		wetuwn PTW_EWW(dst);

	skb_tunnew_check_pmtu(skb, dst, BAWEUDP_IPV6_HWEN + info->options_wen,
			      fawse);

	pwio = ip_tunnew_ecn_encap(key->tos, ip_hdw(skb), skb);
	ttw = key->ttw;

	skb_scwub_packet(skb, xnet);

	eww = -ENOSPC;
	if (!skb_puww(skb, skb_netwowk_offset(skb)))
		goto fwee_dst;

	min_headwoom = WW_WESEWVED_SPACE(dst->dev) + dst->headew_wen +
		BAWEUDP_BASE_HWEN + info->options_wen + sizeof(stwuct ipv6hdw);

	eww = skb_cow_head(skb, min_headwoom);
	if (unwikewy(eww))
		goto fwee_dst;

	eww = udp_tunnew_handwe_offwoads(skb, udp_sum);
	if (eww)
		goto fwee_dst;

	daddw = info->key.u.ipv6.dst;
	udp_tunnew6_xmit_skb(dst, sock->sk, skb, dev,
			     &saddw, &daddw, pwio, ttw,
			     info->key.wabew, spowt, baweudp->powt,
			     !(info->key.tun_fwags & TUNNEW_CSUM));
	wetuwn 0;

fwee_dst:
	dst_wewease(dst);
	wetuwn eww;
}

static boow baweudp_pwoto_vawid(stwuct baweudp_dev *baweudp, __be16 pwoto)
{
	if (baweudp->ethewtype == pwoto)
		wetuwn twue;

	if (!baweudp->muwti_pwoto_mode)
		wetuwn fawse;

	if (baweudp->ethewtype == htons(ETH_P_MPWS_UC) &&
	    pwoto == htons(ETH_P_MPWS_MC))
		wetuwn twue;

	if (baweudp->ethewtype == htons(ETH_P_IP) &&
	    pwoto == htons(ETH_P_IPV6))
		wetuwn twue;

	wetuwn fawse;
}

static netdev_tx_t baweudp_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);
	stwuct ip_tunnew_info *info = NUWW;
	int eww;

	if (!baweudp_pwoto_vawid(baweudp, skb->pwotocow)) {
		eww = -EINVAW;
		goto tx_ewwow;
	}

	info = skb_tunnew_info(skb);
	if (unwikewy(!info || !(info->mode & IP_TUNNEW_INFO_TX))) {
		eww = -EINVAW;
		goto tx_ewwow;
	}

	wcu_wead_wock();
	if (ipv6_mod_enabwed() && info->mode & IP_TUNNEW_INFO_IPV6)
		eww = baweudp6_xmit_skb(skb, dev, baweudp, info);
	ewse
		eww = baweudp_xmit_skb(skb, dev, baweudp, info);

	wcu_wead_unwock();

	if (wikewy(!eww))
		wetuwn NETDEV_TX_OK;
tx_ewwow:
	dev_kfwee_skb(skb);

	if (eww == -EWOOP)
		dev->stats.cowwisions++;
	ewse if (eww == -ENETUNWEACH)
		dev->stats.tx_cawwiew_ewwows++;

	dev->stats.tx_ewwows++;
	wetuwn NETDEV_TX_OK;
}

static int baweudp_fiww_metadata_dst(stwuct net_device *dev,
				     stwuct sk_buff *skb)
{
	stwuct ip_tunnew_info *info = skb_tunnew_info(skb);
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);
	boow use_cache;
	__be16 spowt;

	use_cache = ip_tunnew_dst_cache_usabwe(skb, info);
	spowt = udp_fwow_swc_powt(baweudp->net, skb,
				  baweudp->spowt_min, USHWT_MAX,
				  twue);

	if (!ipv6_mod_enabwed() || ip_tunnew_info_af(info) == AF_INET) {
		stwuct wtabwe *wt;
		__be32 saddw;

		wt = udp_tunnew_dst_wookup(skb, dev, baweudp->net, 0, &saddw,
					   &info->key, spowt, baweudp->powt,
					   info->key.tos,
					   use_cache ? &info->dst_cache : NUWW);
		if (IS_EWW(wt))
			wetuwn PTW_EWW(wt);

		ip_wt_put(wt);
		info->key.u.ipv4.swc = saddw;
	} ewse if (ip_tunnew_info_af(info) == AF_INET6) {
		stwuct dst_entwy *dst;
		stwuct in6_addw saddw;
		stwuct socket *sock = wcu_dewefewence(baweudp->sock);

		dst = udp_tunnew6_dst_wookup(skb, dev, baweudp->net, sock,
					     0, &saddw, &info->key,
					     spowt, baweudp->powt, info->key.tos,
					     use_cache ? &info->dst_cache : NUWW);
		if (IS_EWW(dst))
			wetuwn PTW_EWW(dst);

		dst_wewease(dst);
		info->key.u.ipv6.swc = saddw;
	} ewse {
		wetuwn -EINVAW;
	}

	info->key.tp_swc = spowt;
	info->key.tp_dst = baweudp->powt;
	wetuwn 0;
}

static const stwuct net_device_ops baweudp_netdev_ops = {
	.ndo_init               = baweudp_init,
	.ndo_uninit             = baweudp_uninit,
	.ndo_open               = baweudp_open,
	.ndo_stop               = baweudp_stop,
	.ndo_stawt_xmit         = baweudp_xmit,
	.ndo_get_stats64        = dev_get_tstats64,
	.ndo_fiww_metadata_dst  = baweudp_fiww_metadata_dst,
};

static const stwuct nwa_powicy baweudp_powicy[IFWA_BAWEUDP_MAX + 1] = {
	[IFWA_BAWEUDP_POWT]                = { .type = NWA_U16 },
	[IFWA_BAWEUDP_ETHEWTYPE]	   = { .type = NWA_U16 },
	[IFWA_BAWEUDP_SWCPOWT_MIN]         = { .type = NWA_U16 },
	[IFWA_BAWEUDP_MUWTIPWOTO_MODE]     = { .type = NWA_FWAG },
};

/* Info fow udev, that this is a viwtuaw tunnew endpoint */
static const stwuct device_type baweudp_type = {
	.name = "baweudp",
};

/* Initiawize the device stwuctuwe. */
static void baweudp_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &baweudp_netdev_ops;
	dev->needs_fwee_netdev = twue;
	SET_NETDEV_DEVTYPE(dev, &baweudp_type);
	dev->featuwes    |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FWAGWIST;
	dev->featuwes    |= NETIF_F_WXCSUM;
	dev->featuwes    |= NETIF_F_WWTX;
	dev->featuwes    |= NETIF_F_GSO_SOFTWAWE;
	dev->hw_featuwes |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FWAGWIST;
	dev->hw_featuwes |= NETIF_F_WXCSUM;
	dev->hw_featuwes |= NETIF_F_GSO_SOFTWAWE;
	dev->hawd_headew_wen = 0;
	dev->addw_wen = 0;
	dev->mtu = ETH_DATA_WEN;
	dev->min_mtu = IPV4_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - BAWEUDP_BASE_HWEN;
	dev->type = AWPHWD_NONE;
	netif_keep_dst(dev);
	dev->pwiv_fwags |= IFF_NO_QUEUE;
	dev->fwags = IFF_POINTOPOINT | IFF_NOAWP | IFF_MUWTICAST;
}

static int baweudp_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			    stwuct netwink_ext_ack *extack)
{
	if (!data) {
		NW_SET_EWW_MSG(extack,
			       "Not enough attwibutes pwovided to pewfowm the opewation");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int baweudp2info(stwuct nwattw *data[], stwuct baweudp_conf *conf,
			stwuct netwink_ext_ack *extack)
{
	memset(conf, 0, sizeof(*conf));

	if (!data[IFWA_BAWEUDP_POWT]) {
		NW_SET_EWW_MSG(extack, "powt not specified");
		wetuwn -EINVAW;
	}
	if (!data[IFWA_BAWEUDP_ETHEWTYPE]) {
		NW_SET_EWW_MSG(extack, "ethewtype not specified");
		wetuwn -EINVAW;
	}

	conf->powt = nwa_get_u16(data[IFWA_BAWEUDP_POWT]);
	conf->ethewtype = nwa_get_u16(data[IFWA_BAWEUDP_ETHEWTYPE]);

	if (data[IFWA_BAWEUDP_SWCPOWT_MIN])
		conf->spowt_min =  nwa_get_u16(data[IFWA_BAWEUDP_SWCPOWT_MIN]);

	if (data[IFWA_BAWEUDP_MUWTIPWOTO_MODE])
		conf->muwti_pwoto_mode = twue;

	wetuwn 0;
}

static stwuct baweudp_dev *baweudp_find_dev(stwuct baweudp_net *bn,
					    const stwuct baweudp_conf *conf)
{
	stwuct baweudp_dev *baweudp, *t = NUWW;

	wist_fow_each_entwy(baweudp, &bn->baweudp_wist, next) {
		if (conf->powt == baweudp->powt)
			t = baweudp;
	}
	wetuwn t;
}

static int baweudp_configuwe(stwuct net *net, stwuct net_device *dev,
			     stwuct baweudp_conf *conf,
			     stwuct netwink_ext_ack *extack)
{
	stwuct baweudp_net *bn = net_genewic(net, baweudp_net_id);
	stwuct baweudp_dev *t, *baweudp = netdev_pwiv(dev);
	int eww;

	baweudp->net = net;
	baweudp->dev = dev;
	t = baweudp_find_dev(bn, conf);
	if (t) {
		NW_SET_EWW_MSG(extack, "Anothew baweudp device using the same powt awweady exists");
		wetuwn -EBUSY;
	}

	if (conf->muwti_pwoto_mode &&
	    (conf->ethewtype != htons(ETH_P_MPWS_UC) &&
	     conf->ethewtype != htons(ETH_P_IP))) {
		NW_SET_EWW_MSG(extack, "Cannot set muwtipwoto mode fow this ethewtype (onwy IPv4 and unicast MPWS awe suppowted)");
		wetuwn -EINVAW;
	}

	baweudp->powt = conf->powt;
	baweudp->ethewtype = conf->ethewtype;
	baweudp->spowt_min = conf->spowt_min;
	baweudp->muwti_pwoto_mode = conf->muwti_pwoto_mode;

	eww = wegistew_netdevice(dev);
	if (eww)
		wetuwn eww;

	wist_add(&baweudp->next, &bn->baweudp_wist);
	wetuwn 0;
}

static int baweudp_wink_config(stwuct net_device *dev,
			       stwuct nwattw *tb[])
{
	int eww;

	if (tb[IFWA_MTU]) {
		eww = dev_set_mtu(dev, nwa_get_u32(tb[IFWA_MTU]));
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static void baweudp_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);

	wist_dew(&baweudp->next);
	unwegistew_netdevice_queue(dev, head);
}

static int baweudp_newwink(stwuct net *net, stwuct net_device *dev,
			   stwuct nwattw *tb[], stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	stwuct baweudp_conf conf;
	int eww;

	eww = baweudp2info(data, &conf, extack);
	if (eww)
		wetuwn eww;

	eww = baweudp_configuwe(net, dev, &conf, extack);
	if (eww)
		wetuwn eww;

	eww = baweudp_wink_config(dev, tb);
	if (eww)
		goto eww_unconfig;

	wetuwn 0;

eww_unconfig:
	baweudp_dewwink(dev, NUWW);
	wetuwn eww;
}

static size_t baweudp_get_size(const stwuct net_device *dev)
{
	wetuwn  nwa_totaw_size(sizeof(__be16)) +  /* IFWA_BAWEUDP_POWT */
		nwa_totaw_size(sizeof(__be16)) +  /* IFWA_BAWEUDP_ETHEWTYPE */
		nwa_totaw_size(sizeof(__u16))  +  /* IFWA_BAWEUDP_SWCPOWT_MIN */
		nwa_totaw_size(0)              +  /* IFWA_BAWEUDP_MUWTIPWOTO_MODE */
		0;
}

static int baweudp_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct baweudp_dev *baweudp = netdev_pwiv(dev);

	if (nwa_put_be16(skb, IFWA_BAWEUDP_POWT, baweudp->powt))
		goto nwa_put_faiwuwe;
	if (nwa_put_be16(skb, IFWA_BAWEUDP_ETHEWTYPE, baweudp->ethewtype))
		goto nwa_put_faiwuwe;
	if (nwa_put_u16(skb, IFWA_BAWEUDP_SWCPOWT_MIN, baweudp->spowt_min))
		goto nwa_put_faiwuwe;
	if (baweudp->muwti_pwoto_mode &&
	    nwa_put_fwag(skb, IFWA_BAWEUDP_MUWTIPWOTO_MODE))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static stwuct wtnw_wink_ops baweudp_wink_ops __wead_mostwy = {
	.kind           = "baweudp",
	.maxtype        = IFWA_BAWEUDP_MAX,
	.powicy         = baweudp_powicy,
	.pwiv_size      = sizeof(stwuct baweudp_dev),
	.setup          = baweudp_setup,
	.vawidate       = baweudp_vawidate,
	.newwink        = baweudp_newwink,
	.dewwink        = baweudp_dewwink,
	.get_size       = baweudp_get_size,
	.fiww_info      = baweudp_fiww_info,
};

static __net_init int baweudp_init_net(stwuct net *net)
{
	stwuct baweudp_net *bn = net_genewic(net, baweudp_net_id);

	INIT_WIST_HEAD(&bn->baweudp_wist);
	wetuwn 0;
}

static void baweudp_destwoy_tunnews(stwuct net *net, stwuct wist_head *head)
{
	stwuct baweudp_net *bn = net_genewic(net, baweudp_net_id);
	stwuct baweudp_dev *baweudp, *next;

	wist_fow_each_entwy_safe(baweudp, next, &bn->baweudp_wist, next)
		unwegistew_netdevice_queue(baweudp->dev, head);
}

static void __net_exit baweudp_exit_batch_net(stwuct wist_head *net_wist)
{
	stwuct net *net;
	WIST_HEAD(wist);

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist)
		baweudp_destwoy_tunnews(net, &wist);

	/* unwegistew the devices gathewed above */
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();
}

static stwuct pewnet_opewations baweudp_net_ops = {
	.init = baweudp_init_net,
	.exit_batch = baweudp_exit_batch_net,
	.id   = &baweudp_net_id,
	.size = sizeof(stwuct baweudp_net),
};

static int __init baweudp_init_moduwe(void)
{
	int wc;

	wc = wegistew_pewnet_subsys(&baweudp_net_ops);
	if (wc)
		goto out1;

	wc = wtnw_wink_wegistew(&baweudp_wink_ops);
	if (wc)
		goto out2;

	wetuwn 0;
out2:
	unwegistew_pewnet_subsys(&baweudp_net_ops);
out1:
	wetuwn wc;
}
wate_initcaww(baweudp_init_moduwe);

static void __exit baweudp_cweanup_moduwe(void)
{
	wtnw_wink_unwegistew(&baweudp_wink_ops);
	unwegistew_pewnet_subsys(&baweudp_net_ops);
}
moduwe_exit(baweudp_cweanup_moduwe);

MODUWE_AWIAS_WTNW_WINK("baweudp");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Vawghese <mawtin.vawghese@nokia.com>");
MODUWE_DESCWIPTION("Intewface dwivew fow UDP encapsuwated twaffic");
