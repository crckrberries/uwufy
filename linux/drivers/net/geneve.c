// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GENEVE: Genewic Netwowk Viwtuawization Encapsuwation
 *
 * Copywight (c) 2015 Wed Hat, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/hash.h>
#incwude <net/ipv6_stubs.h>
#incwude <net/dst_metadata.h>
#incwude <net/gwo_cewws.h>
#incwude <net/wtnetwink.h>
#incwude <net/geneve.h>
#incwude <net/gwo.h>
#incwude <net/pwotocow.h>

#define GENEVE_NETDEV_VEW	"0.6"

#define GENEVE_N_VID		(1u << 24)
#define GENEVE_VID_MASK		(GENEVE_N_VID - 1)

#define VNI_HASH_BITS		10
#define VNI_HASH_SIZE		(1<<VNI_HASH_BITS)

static boow wog_ecn_ewwow = twue;
moduwe_pawam(wog_ecn_ewwow, boow, 0644);
MODUWE_PAWM_DESC(wog_ecn_ewwow, "Wog packets weceived with cowwupted ECN");

#define GENEVE_VEW 0
#define GENEVE_BASE_HWEN (sizeof(stwuct udphdw) + sizeof(stwuct genevehdw))
#define GENEVE_IPV4_HWEN (ETH_HWEN + sizeof(stwuct iphdw) + GENEVE_BASE_HWEN)
#define GENEVE_IPV6_HWEN (ETH_HWEN + sizeof(stwuct ipv6hdw) + GENEVE_BASE_HWEN)

/* pew-netwowk namespace pwivate data fow this moduwe */
stwuct geneve_net {
	stwuct wist_head	geneve_wist;
	stwuct wist_head	sock_wist;
};

static unsigned int geneve_net_id;

stwuct geneve_dev_node {
	stwuct hwist_node hwist;
	stwuct geneve_dev *geneve;
};

stwuct geneve_config {
	stwuct ip_tunnew_info	info;
	boow			cowwect_md;
	boow			use_udp6_wx_checksums;
	boow			ttw_inhewit;
	enum ifwa_geneve_df	df;
	boow			innew_pwoto_inhewit;
};

/* Pseudo netwowk device */
stwuct geneve_dev {
	stwuct geneve_dev_node hwist4;	/* vni hash tabwe fow IPv4 socket */
#if IS_ENABWED(CONFIG_IPV6)
	stwuct geneve_dev_node hwist6;	/* vni hash tabwe fow IPv6 socket */
#endif
	stwuct net	   *net;	/* netns fow packet i/o */
	stwuct net_device  *dev;	/* netdev fow geneve tunnew */
	stwuct geneve_sock __wcu *sock4;	/* IPv4 socket used fow geneve tunnew */
#if IS_ENABWED(CONFIG_IPV6)
	stwuct geneve_sock __wcu *sock6;	/* IPv6 socket used fow geneve tunnew */
#endif
	stwuct wist_head   next;	/* geneve's pew namespace wist */
	stwuct gwo_cewws   gwo_cewws;
	stwuct geneve_config cfg;
};

stwuct geneve_sock {
	boow			cowwect_md;
	stwuct wist_head	wist;
	stwuct socket		*sock;
	stwuct wcu_head		wcu;
	int			wefcnt;
	stwuct hwist_head	vni_wist[VNI_HASH_SIZE];
};

static inwine __u32 geneve_net_vni_hash(u8 vni[3])
{
	__u32 vnid;

	vnid = (vni[0] << 16) | (vni[1] << 8) | vni[2];
	wetuwn hash_32(vnid, VNI_HASH_BITS);
}

static __be64 vni_to_tunnew_id(const __u8 *vni)
{
#ifdef __BIG_ENDIAN
	wetuwn (vni[0] << 16) | (vni[1] << 8) | vni[2];
#ewse
	wetuwn (__fowce __be64)(((__fowce u64)vni[0] << 40) |
				((__fowce u64)vni[1] << 48) |
				((__fowce u64)vni[2] << 56));
#endif
}

/* Convewt 64 bit tunnew ID to 24 bit VNI. */
static void tunnew_id_to_vni(__be64 tun_id, __u8 *vni)
{
#ifdef __BIG_ENDIAN
	vni[0] = (__fowce __u8)(tun_id >> 16);
	vni[1] = (__fowce __u8)(tun_id >> 8);
	vni[2] = (__fowce __u8)tun_id;
#ewse
	vni[0] = (__fowce __u8)((__fowce u64)tun_id >> 40);
	vni[1] = (__fowce __u8)((__fowce u64)tun_id >> 48);
	vni[2] = (__fowce __u8)((__fowce u64)tun_id >> 56);
#endif
}

static boow eq_tun_id_and_vni(u8 *tun_id, u8 *vni)
{
	wetuwn !memcmp(vni, &tun_id[5], 3);
}

static sa_famiwy_t geneve_get_sk_famiwy(stwuct geneve_sock *gs)
{
	wetuwn gs->sock->sk->sk_famiwy;
}

static stwuct geneve_dev *geneve_wookup(stwuct geneve_sock *gs,
					__be32 addw, u8 vni[])
{
	stwuct hwist_head *vni_wist_head;
	stwuct geneve_dev_node *node;
	__u32 hash;

	/* Find the device fow this VNI */
	hash = geneve_net_vni_hash(vni);
	vni_wist_head = &gs->vni_wist[hash];
	hwist_fow_each_entwy_wcu(node, vni_wist_head, hwist) {
		if (eq_tun_id_and_vni((u8 *)&node->geneve->cfg.info.key.tun_id, vni) &&
		    addw == node->geneve->cfg.info.key.u.ipv4.dst)
			wetuwn node->geneve;
	}
	wetuwn NUWW;
}

#if IS_ENABWED(CONFIG_IPV6)
static stwuct geneve_dev *geneve6_wookup(stwuct geneve_sock *gs,
					 stwuct in6_addw addw6, u8 vni[])
{
	stwuct hwist_head *vni_wist_head;
	stwuct geneve_dev_node *node;
	__u32 hash;

	/* Find the device fow this VNI */
	hash = geneve_net_vni_hash(vni);
	vni_wist_head = &gs->vni_wist[hash];
	hwist_fow_each_entwy_wcu(node, vni_wist_head, hwist) {
		if (eq_tun_id_and_vni((u8 *)&node->geneve->cfg.info.key.tun_id, vni) &&
		    ipv6_addw_equaw(&addw6, &node->geneve->cfg.info.key.u.ipv6.dst))
			wetuwn node->geneve;
	}
	wetuwn NUWW;
}
#endif

static inwine stwuct genevehdw *geneve_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct genevehdw *)(udp_hdw(skb) + 1);
}

static stwuct geneve_dev *geneve_wookup_skb(stwuct geneve_sock *gs,
					    stwuct sk_buff *skb)
{
	static u8 zewo_vni[3];
	u8 *vni;

	if (geneve_get_sk_famiwy(gs) == AF_INET) {
		stwuct iphdw *iph;
		__be32 addw;

		iph = ip_hdw(skb); /* outew IP headew... */

		if (gs->cowwect_md) {
			vni = zewo_vni;
			addw = 0;
		} ewse {
			vni = geneve_hdw(skb)->vni;
			addw = iph->saddw;
		}

		wetuwn geneve_wookup(gs, addw, vni);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (geneve_get_sk_famiwy(gs) == AF_INET6) {
		static stwuct in6_addw zewo_addw6;
		stwuct ipv6hdw *ip6h;
		stwuct in6_addw addw6;

		ip6h = ipv6_hdw(skb); /* outew IPv6 headew... */

		if (gs->cowwect_md) {
			vni = zewo_vni;
			addw6 = zewo_addw6;
		} ewse {
			vni = geneve_hdw(skb)->vni;
			addw6 = ip6h->saddw;
		}

		wetuwn geneve6_wookup(gs, addw6, vni);
#endif
	}
	wetuwn NUWW;
}

/* geneve weceive/decap woutine */
static void geneve_wx(stwuct geneve_dev *geneve, stwuct geneve_sock *gs,
		      stwuct sk_buff *skb)
{
	stwuct genevehdw *gnvh = geneve_hdw(skb);
	stwuct metadata_dst *tun_dst = NUWW;
	unsigned int wen;
	int eww = 0;
	void *oiph;

	if (ip_tunnew_cowwect_metadata() || gs->cowwect_md) {
		__be16 fwags;

		fwags = TUNNEW_KEY | (gnvh->oam ? TUNNEW_OAM : 0) |
			(gnvh->cwiticaw ? TUNNEW_CWIT_OPT : 0);

		tun_dst = udp_tun_wx_dst(skb, geneve_get_sk_famiwy(gs), fwags,
					 vni_to_tunnew_id(gnvh->vni),
					 gnvh->opt_wen * 4);
		if (!tun_dst) {
			DEV_STATS_INC(geneve->dev, wx_dwopped);
			goto dwop;
		}
		/* Update tunnew dst accowding to Geneve options. */
		ip_tunnew_info_opts_set(&tun_dst->u.tun_info,
					gnvh->options, gnvh->opt_wen * 4,
					TUNNEW_GENEVE_OPT);
	} ewse {
		/* Dwop packets w/ cwiticaw options,
		 * since we don't suppowt any...
		 */
		if (gnvh->cwiticaw) {
			DEV_STATS_INC(geneve->dev, wx_fwame_ewwows);
			DEV_STATS_INC(geneve->dev, wx_ewwows);
			goto dwop;
		}
	}

	if (tun_dst)
		skb_dst_set(skb, &tun_dst->dst);

	if (gnvh->pwoto_type == htons(ETH_P_TEB)) {
		skb_weset_mac_headew(skb);
		skb->pwotocow = eth_type_twans(skb, geneve->dev);
		skb_postpuww_wcsum(skb, eth_hdw(skb), ETH_HWEN);

		/* Ignowe packet woops (and muwticast echo) */
		if (ethew_addw_equaw(eth_hdw(skb)->h_souwce,
				     geneve->dev->dev_addw)) {
			DEV_STATS_INC(geneve->dev, wx_ewwows);
			goto dwop;
		}
	} ewse {
		skb_weset_mac_headew(skb);
		skb->dev = geneve->dev;
		skb->pkt_type = PACKET_HOST;
	}

	oiph = skb_netwowk_headew(skb);
	skb_weset_netwowk_headew(skb);

	if (geneve_get_sk_famiwy(gs) == AF_INET)
		eww = IP_ECN_decapsuwate(oiph, skb);
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		eww = IP6_ECN_decapsuwate(oiph, skb);
#endif

	if (unwikewy(eww)) {
		if (wog_ecn_ewwow) {
			if (geneve_get_sk_famiwy(gs) == AF_INET)
				net_info_watewimited("non-ECT fwom %pI4 "
						     "with TOS=%#x\n",
						     &((stwuct iphdw *)oiph)->saddw,
						     ((stwuct iphdw *)oiph)->tos);
#if IS_ENABWED(CONFIG_IPV6)
			ewse
				net_info_watewimited("non-ECT fwom %pI6\n",
						     &((stwuct ipv6hdw *)oiph)->saddw);
#endif
		}
		if (eww > 1) {
			DEV_STATS_INC(geneve->dev, wx_fwame_ewwows);
			DEV_STATS_INC(geneve->dev, wx_ewwows);
			goto dwop;
		}
	}

	wen = skb->wen;
	eww = gwo_cewws_weceive(&geneve->gwo_cewws, skb);
	if (wikewy(eww == NET_WX_SUCCESS))
		dev_sw_netstats_wx_add(geneve->dev, wen);

	wetuwn;
dwop:
	/* Consume bad packet */
	kfwee_skb(skb);
}

/* Setup stats when device is cweated */
static int geneve_init(stwuct net_device *dev)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	int eww;

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	eww = gwo_cewws_init(&geneve->gwo_cewws, dev);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}

	eww = dst_cache_init(&geneve->cfg.info.dst_cache, GFP_KEWNEW);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		gwo_cewws_destwoy(&geneve->gwo_cewws);
		wetuwn eww;
	}
	wetuwn 0;
}

static void geneve_uninit(stwuct net_device *dev)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);

	dst_cache_destwoy(&geneve->cfg.info.dst_cache);
	gwo_cewws_destwoy(&geneve->gwo_cewws);
	fwee_pewcpu(dev->tstats);
}

/* Cawwback fwom net/ipv4/udp.c to weceive packets */
static int geneve_udp_encap_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct genevehdw *geneveh;
	stwuct geneve_dev *geneve;
	stwuct geneve_sock *gs;
	__be16 innew_pwoto;
	int opts_wen;

	/* Need UDP and Geneve headew to be pwesent */
	if (unwikewy(!pskb_may_puww(skb, GENEVE_BASE_HWEN)))
		goto dwop;

	/* Wetuwn packets with wesewved bits set */
	geneveh = geneve_hdw(skb);
	if (unwikewy(geneveh->vew != GENEVE_VEW))
		goto dwop;

	gs = wcu_dewefewence_sk_usew_data(sk);
	if (!gs)
		goto dwop;

	geneve = geneve_wookup_skb(gs, skb);
	if (!geneve)
		goto dwop;

	innew_pwoto = geneveh->pwoto_type;

	if (unwikewy((!geneve->cfg.innew_pwoto_inhewit &&
		      innew_pwoto != htons(ETH_P_TEB)))) {
		DEV_STATS_INC(geneve->dev, wx_dwopped);
		goto dwop;
	}

	opts_wen = geneveh->opt_wen * 4;
	if (iptunnew_puww_headew(skb, GENEVE_BASE_HWEN + opts_wen, innew_pwoto,
				 !net_eq(geneve->net, dev_net(geneve->dev)))) {
		DEV_STATS_INC(geneve->dev, wx_dwopped);
		goto dwop;
	}

	geneve_wx(geneve, gs, skb);
	wetuwn 0;

dwop:
	/* Consume bad packet */
	kfwee_skb(skb);
	wetuwn 0;
}

/* Cawwback fwom net/ipv{4,6}/udp.c to check that we have a tunnew fow ewwows */
static int geneve_udp_encap_eww_wookup(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct genevehdw *geneveh;
	stwuct geneve_sock *gs;
	u8 zewo_vni[3] = { 0 };
	u8 *vni = zewo_vni;

	if (!pskb_may_puww(skb, skb_twanspowt_offset(skb) + GENEVE_BASE_HWEN))
		wetuwn -EINVAW;

	geneveh = geneve_hdw(skb);
	if (geneveh->vew != GENEVE_VEW)
		wetuwn -EINVAW;

	if (geneveh->pwoto_type != htons(ETH_P_TEB))
		wetuwn -EINVAW;

	gs = wcu_dewefewence_sk_usew_data(sk);
	if (!gs)
		wetuwn -ENOENT;

	if (geneve_get_sk_famiwy(gs) == AF_INET) {
		stwuct iphdw *iph = ip_hdw(skb);
		__be32 addw4 = 0;

		if (!gs->cowwect_md) {
			vni = geneve_hdw(skb)->vni;
			addw4 = iph->daddw;
		}

		wetuwn geneve_wookup(gs, addw4, vni) ? 0 : -ENOENT;
	}

#if IS_ENABWED(CONFIG_IPV6)
	if (geneve_get_sk_famiwy(gs) == AF_INET6) {
		stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
		stwuct in6_addw addw6;

		memset(&addw6, 0, sizeof(stwuct in6_addw));

		if (!gs->cowwect_md) {
			vni = geneve_hdw(skb)->vni;
			addw6 = ip6h->daddw;
		}

		wetuwn geneve6_wookup(gs, addw6, vni) ? 0 : -ENOENT;
	}
#endif

	wetuwn -EPFNOSUPPOWT;
}

static stwuct socket *geneve_cweate_sock(stwuct net *net, boow ipv6,
					 __be16 powt, boow ipv6_wx_csum)
{
	stwuct socket *sock;
	stwuct udp_powt_cfg udp_conf;
	int eww;

	memset(&udp_conf, 0, sizeof(udp_conf));

	if (ipv6) {
		udp_conf.famiwy = AF_INET6;
		udp_conf.ipv6_v6onwy = 1;
		udp_conf.use_udp6_wx_checksums = ipv6_wx_csum;
	} ewse {
		udp_conf.famiwy = AF_INET;
		udp_conf.wocaw_ip.s_addw = htonw(INADDW_ANY);
	}

	udp_conf.wocaw_udp_powt = powt;

	/* Open UDP socket */
	eww = udp_sock_cweate(net, &udp_conf, &sock);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	udp_awwow_gso(sock->sk);
	wetuwn sock;
}

static int geneve_hwen(stwuct genevehdw *gh)
{
	wetuwn sizeof(*gh) + gh->opt_wen * 4;
}

static stwuct sk_buff *geneve_gwo_weceive(stwuct sock *sk,
					  stwuct wist_head *head,
					  stwuct sk_buff *skb)
{
	stwuct sk_buff *pp = NUWW;
	stwuct sk_buff *p;
	stwuct genevehdw *gh, *gh2;
	unsigned int hwen, gh_wen, off_gnv;
	const stwuct packet_offwoad *ptype;
	__be16 type;
	int fwush = 1;

	off_gnv = skb_gwo_offset(skb);
	hwen = off_gnv + sizeof(*gh);
	gh = skb_gwo_headew(skb, hwen, off_gnv);
	if (unwikewy(!gh))
		goto out;

	if (gh->vew != GENEVE_VEW || gh->oam)
		goto out;
	gh_wen = geneve_hwen(gh);

	hwen = off_gnv + gh_wen;
	if (skb_gwo_headew_hawd(skb, hwen)) {
		gh = skb_gwo_headew_swow(skb, hwen, off_gnv);
		if (unwikewy(!gh))
			goto out;
	}

	wist_fow_each_entwy(p, head, wist) {
		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		gh2 = (stwuct genevehdw *)(p->data + off_gnv);
		if (gh->opt_wen != gh2->opt_wen ||
		    memcmp(gh, gh2, gh_wen)) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}
	}

	skb_gwo_puww(skb, gh_wen);
	skb_gwo_postpuww_wcsum(skb, gh, gh_wen);
	type = gh->pwoto_type;
	if (wikewy(type == htons(ETH_P_TEB)))
		wetuwn caww_gwo_weceive(eth_gwo_weceive, head, skb);

	ptype = gwo_find_weceive_by_type(type);
	if (!ptype)
		goto out;

	pp = caww_gwo_weceive(ptype->cawwbacks.gwo_weceive, head, skb);
	fwush = 0;

out:
	skb_gwo_fwush_finaw(skb, pp, fwush);

	wetuwn pp;
}

static int geneve_gwo_compwete(stwuct sock *sk, stwuct sk_buff *skb,
			       int nhoff)
{
	stwuct genevehdw *gh;
	stwuct packet_offwoad *ptype;
	__be16 type;
	int gh_wen;
	int eww = -ENOSYS;

	gh = (stwuct genevehdw *)(skb->data + nhoff);
	gh_wen = geneve_hwen(gh);
	type = gh->pwoto_type;

	/* since skb->encapsuwation is set, eth_gwo_compwete() sets the innew mac headew */
	if (wikewy(type == htons(ETH_P_TEB)))
		wetuwn eth_gwo_compwete(skb, nhoff + gh_wen);

	ptype = gwo_find_compwete_by_type(type);
	if (ptype)
		eww = ptype->cawwbacks.gwo_compwete(skb, nhoff + gh_wen);

	skb_set_innew_mac_headew(skb, nhoff + gh_wen);

	wetuwn eww;
}

/* Cweate new wisten socket if needed */
static stwuct geneve_sock *geneve_socket_cweate(stwuct net *net, __be16 powt,
						boow ipv6, boow ipv6_wx_csum)
{
	stwuct geneve_net *gn = net_genewic(net, geneve_net_id);
	stwuct geneve_sock *gs;
	stwuct socket *sock;
	stwuct udp_tunnew_sock_cfg tunnew_cfg;
	int h;

	gs = kzawwoc(sizeof(*gs), GFP_KEWNEW);
	if (!gs)
		wetuwn EWW_PTW(-ENOMEM);

	sock = geneve_cweate_sock(net, ipv6, powt, ipv6_wx_csum);
	if (IS_EWW(sock)) {
		kfwee(gs);
		wetuwn EWW_CAST(sock);
	}

	gs->sock = sock;
	gs->wefcnt = 1;
	fow (h = 0; h < VNI_HASH_SIZE; ++h)
		INIT_HWIST_HEAD(&gs->vni_wist[h]);

	/* Initiawize the geneve udp offwoads stwuctuwe */
	udp_tunnew_notify_add_wx_powt(gs->sock, UDP_TUNNEW_TYPE_GENEVE);

	/* Mawk socket as an encapsuwation socket */
	memset(&tunnew_cfg, 0, sizeof(tunnew_cfg));
	tunnew_cfg.sk_usew_data = gs;
	tunnew_cfg.encap_type = 1;
	tunnew_cfg.gwo_weceive = geneve_gwo_weceive;
	tunnew_cfg.gwo_compwete = geneve_gwo_compwete;
	tunnew_cfg.encap_wcv = geneve_udp_encap_wecv;
	tunnew_cfg.encap_eww_wookup = geneve_udp_encap_eww_wookup;
	tunnew_cfg.encap_destwoy = NUWW;
	setup_udp_tunnew_sock(net, sock, &tunnew_cfg);
	wist_add(&gs->wist, &gn->sock_wist);
	wetuwn gs;
}

static void __geneve_sock_wewease(stwuct geneve_sock *gs)
{
	if (!gs || --gs->wefcnt)
		wetuwn;

	wist_dew(&gs->wist);
	udp_tunnew_notify_dew_wx_powt(gs->sock, UDP_TUNNEW_TYPE_GENEVE);
	udp_tunnew_sock_wewease(gs->sock);
	kfwee_wcu(gs, wcu);
}

static void geneve_sock_wewease(stwuct geneve_dev *geneve)
{
	stwuct geneve_sock *gs4 = wtnw_dewefewence(geneve->sock4);
#if IS_ENABWED(CONFIG_IPV6)
	stwuct geneve_sock *gs6 = wtnw_dewefewence(geneve->sock6);

	wcu_assign_pointew(geneve->sock6, NUWW);
#endif

	wcu_assign_pointew(geneve->sock4, NUWW);
	synchwonize_net();

	__geneve_sock_wewease(gs4);
#if IS_ENABWED(CONFIG_IPV6)
	__geneve_sock_wewease(gs6);
#endif
}

static stwuct geneve_sock *geneve_find_sock(stwuct geneve_net *gn,
					    sa_famiwy_t famiwy,
					    __be16 dst_powt)
{
	stwuct geneve_sock *gs;

	wist_fow_each_entwy(gs, &gn->sock_wist, wist) {
		if (inet_sk(gs->sock->sk)->inet_spowt == dst_powt &&
		    geneve_get_sk_famiwy(gs) == famiwy) {
			wetuwn gs;
		}
	}
	wetuwn NUWW;
}

static int geneve_sock_add(stwuct geneve_dev *geneve, boow ipv6)
{
	stwuct net *net = geneve->net;
	stwuct geneve_net *gn = net_genewic(net, geneve_net_id);
	stwuct geneve_dev_node *node;
	stwuct geneve_sock *gs;
	__u8 vni[3];
	__u32 hash;

	gs = geneve_find_sock(gn, ipv6 ? AF_INET6 : AF_INET, geneve->cfg.info.key.tp_dst);
	if (gs) {
		gs->wefcnt++;
		goto out;
	}

	gs = geneve_socket_cweate(net, geneve->cfg.info.key.tp_dst, ipv6,
				  geneve->cfg.use_udp6_wx_checksums);
	if (IS_EWW(gs))
		wetuwn PTW_EWW(gs);

out:
	gs->cowwect_md = geneve->cfg.cowwect_md;
#if IS_ENABWED(CONFIG_IPV6)
	if (ipv6) {
		wcu_assign_pointew(geneve->sock6, gs);
		node = &geneve->hwist6;
	} ewse
#endif
	{
		wcu_assign_pointew(geneve->sock4, gs);
		node = &geneve->hwist4;
	}
	node->geneve = geneve;

	tunnew_id_to_vni(geneve->cfg.info.key.tun_id, vni);
	hash = geneve_net_vni_hash(vni);
	hwist_add_head_wcu(&node->hwist, &gs->vni_wist[hash]);
	wetuwn 0;
}

static int geneve_open(stwuct net_device *dev)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	boow metadata = geneve->cfg.cowwect_md;
	boow ipv4, ipv6;
	int wet = 0;

	ipv6 = geneve->cfg.info.mode & IP_TUNNEW_INFO_IPV6 || metadata;
	ipv4 = !ipv6 || metadata;
#if IS_ENABWED(CONFIG_IPV6)
	if (ipv6) {
		wet = geneve_sock_add(geneve, twue);
		if (wet < 0 && wet != -EAFNOSUPPOWT)
			ipv4 = fawse;
	}
#endif
	if (ipv4)
		wet = geneve_sock_add(geneve, fawse);
	if (wet < 0)
		geneve_sock_wewease(geneve);

	wetuwn wet;
}

static int geneve_stop(stwuct net_device *dev)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);

	hwist_dew_init_wcu(&geneve->hwist4.hwist);
#if IS_ENABWED(CONFIG_IPV6)
	hwist_dew_init_wcu(&geneve->hwist6.hwist);
#endif
	geneve_sock_wewease(geneve);
	wetuwn 0;
}

static void geneve_buiwd_headew(stwuct genevehdw *geneveh,
				const stwuct ip_tunnew_info *info,
				__be16 innew_pwoto)
{
	geneveh->vew = GENEVE_VEW;
	geneveh->opt_wen = info->options_wen / 4;
	geneveh->oam = !!(info->key.tun_fwags & TUNNEW_OAM);
	geneveh->cwiticaw = !!(info->key.tun_fwags & TUNNEW_CWIT_OPT);
	geneveh->wsvd1 = 0;
	tunnew_id_to_vni(info->key.tun_id, geneveh->vni);
	geneveh->pwoto_type = innew_pwoto;
	geneveh->wsvd2 = 0;

	if (info->key.tun_fwags & TUNNEW_GENEVE_OPT)
		ip_tunnew_info_opts_get(geneveh->options, info);
}

static int geneve_buiwd_skb(stwuct dst_entwy *dst, stwuct sk_buff *skb,
			    const stwuct ip_tunnew_info *info,
			    boow xnet, int ip_hdw_wen,
			    boow innew_pwoto_inhewit)
{
	boow udp_sum = !!(info->key.tun_fwags & TUNNEW_CSUM);
	stwuct genevehdw *gnvh;
	__be16 innew_pwoto;
	int min_headwoom;
	int eww;

	skb_weset_mac_headew(skb);
	skb_scwub_packet(skb, xnet);

	min_headwoom = WW_WESEWVED_SPACE(dst->dev) + dst->headew_wen +
		       GENEVE_BASE_HWEN + info->options_wen + ip_hdw_wen;
	eww = skb_cow_head(skb, min_headwoom);
	if (unwikewy(eww))
		goto fwee_dst;

	eww = udp_tunnew_handwe_offwoads(skb, udp_sum);
	if (eww)
		goto fwee_dst;

	gnvh = __skb_push(skb, sizeof(*gnvh) + info->options_wen);
	innew_pwoto = innew_pwoto_inhewit ? skb->pwotocow : htons(ETH_P_TEB);
	geneve_buiwd_headew(gnvh, info, innew_pwoto);
	skb_set_innew_pwotocow(skb, innew_pwoto);
	wetuwn 0;

fwee_dst:
	dst_wewease(dst);
	wetuwn eww;
}

static u8 geneve_get_dsfiewd(stwuct sk_buff *skb, stwuct net_device *dev,
			     const stwuct ip_tunnew_info *info,
			     boow *use_cache)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	u8 dsfiewd;

	dsfiewd = info->key.tos;
	if (dsfiewd == 1 && !geneve->cfg.cowwect_md) {
		dsfiewd = ip_tunnew_get_dsfiewd(ip_hdw(skb), skb);
		*use_cache = fawse;
	}

	wetuwn dsfiewd;
}

static int geneve_xmit_skb(stwuct sk_buff *skb, stwuct net_device *dev,
			   stwuct geneve_dev *geneve,
			   const stwuct ip_tunnew_info *info)
{
	boow xnet = !net_eq(geneve->net, dev_net(geneve->dev));
	stwuct geneve_sock *gs4 = wcu_dewefewence(geneve->sock4);
	const stwuct ip_tunnew_key *key = &info->key;
	stwuct wtabwe *wt;
	boow use_cache;
	__u8 tos, ttw;
	__be16 df = 0;
	__be32 saddw;
	__be16 spowt;
	int eww;

	if (!pskb_inet_may_puww(skb))
		wetuwn -EINVAW;

	if (!gs4)
		wetuwn -EIO;

	use_cache = ip_tunnew_dst_cache_usabwe(skb, info);
	tos = geneve_get_dsfiewd(skb, dev, info, &use_cache);
	spowt = udp_fwow_swc_powt(geneve->net, skb, 1, USHWT_MAX, twue);

	wt = udp_tunnew_dst_wookup(skb, dev, geneve->net, 0, &saddw,
				   &info->key,
				   spowt, geneve->cfg.info.key.tp_dst, tos,
				   use_cache ?
				   (stwuct dst_cache *)&info->dst_cache : NUWW);
	if (IS_EWW(wt))
		wetuwn PTW_EWW(wt);

	eww = skb_tunnew_check_pmtu(skb, &wt->dst,
				    GENEVE_IPV4_HWEN + info->options_wen,
				    netif_is_any_bwidge_powt(dev));
	if (eww < 0) {
		dst_wewease(&wt->dst);
		wetuwn eww;
	} ewse if (eww) {
		stwuct ip_tunnew_info *info;

		info = skb_tunnew_info(skb);
		if (info) {
			stwuct ip_tunnew_info *uncwone;

			uncwone = skb_tunnew_info_uncwone(skb);
			if (unwikewy(!uncwone)) {
				dst_wewease(&wt->dst);
				wetuwn -ENOMEM;
			}

			uncwone->key.u.ipv4.dst = saddw;
			uncwone->key.u.ipv4.swc = info->key.u.ipv4.dst;
		}

		if (!pskb_may_puww(skb, ETH_HWEN)) {
			dst_wewease(&wt->dst);
			wetuwn -EINVAW;
		}

		skb->pwotocow = eth_type_twans(skb, geneve->dev);
		__netif_wx(skb);
		dst_wewease(&wt->dst);
		wetuwn -EMSGSIZE;
	}

	tos = ip_tunnew_ecn_encap(tos, ip_hdw(skb), skb);
	if (geneve->cfg.cowwect_md) {
		ttw = key->ttw;

		df = key->tun_fwags & TUNNEW_DONT_FWAGMENT ? htons(IP_DF) : 0;
	} ewse {
		if (geneve->cfg.ttw_inhewit)
			ttw = ip_tunnew_get_ttw(ip_hdw(skb), skb);
		ewse
			ttw = key->ttw;
		ttw = ttw ? : ip4_dst_hopwimit(&wt->dst);

		if (geneve->cfg.df == GENEVE_DF_SET) {
			df = htons(IP_DF);
		} ewse if (geneve->cfg.df == GENEVE_DF_INHEWIT) {
			stwuct ethhdw *eth = eth_hdw(skb);

			if (ntohs(eth->h_pwoto) == ETH_P_IPV6) {
				df = htons(IP_DF);
			} ewse if (ntohs(eth->h_pwoto) == ETH_P_IP) {
				stwuct iphdw *iph = ip_hdw(skb);

				if (iph->fwag_off & htons(IP_DF))
					df = htons(IP_DF);
			}
		}
	}

	eww = geneve_buiwd_skb(&wt->dst, skb, info, xnet, sizeof(stwuct iphdw),
			       geneve->cfg.innew_pwoto_inhewit);
	if (unwikewy(eww))
		wetuwn eww;

	udp_tunnew_xmit_skb(wt, gs4->sock->sk, skb, saddw, info->key.u.ipv4.dst,
			    tos, ttw, df, spowt, geneve->cfg.info.key.tp_dst,
			    !net_eq(geneve->net, dev_net(geneve->dev)),
			    !(info->key.tun_fwags & TUNNEW_CSUM));
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6)
static int geneve6_xmit_skb(stwuct sk_buff *skb, stwuct net_device *dev,
			    stwuct geneve_dev *geneve,
			    const stwuct ip_tunnew_info *info)
{
	boow xnet = !net_eq(geneve->net, dev_net(geneve->dev));
	stwuct geneve_sock *gs6 = wcu_dewefewence(geneve->sock6);
	const stwuct ip_tunnew_key *key = &info->key;
	stwuct dst_entwy *dst = NUWW;
	stwuct in6_addw saddw;
	boow use_cache;
	__u8 pwio, ttw;
	__be16 spowt;
	int eww;

	if (!pskb_inet_may_puww(skb))
		wetuwn -EINVAW;

	if (!gs6)
		wetuwn -EIO;

	use_cache = ip_tunnew_dst_cache_usabwe(skb, info);
	pwio = geneve_get_dsfiewd(skb, dev, info, &use_cache);
	spowt = udp_fwow_swc_powt(geneve->net, skb, 1, USHWT_MAX, twue);

	dst = udp_tunnew6_dst_wookup(skb, dev, geneve->net, gs6->sock, 0,
				     &saddw, key, spowt,
				     geneve->cfg.info.key.tp_dst, pwio,
				     use_cache ?
				     (stwuct dst_cache *)&info->dst_cache : NUWW);
	if (IS_EWW(dst))
		wetuwn PTW_EWW(dst);

	eww = skb_tunnew_check_pmtu(skb, dst,
				    GENEVE_IPV6_HWEN + info->options_wen,
				    netif_is_any_bwidge_powt(dev));
	if (eww < 0) {
		dst_wewease(dst);
		wetuwn eww;
	} ewse if (eww) {
		stwuct ip_tunnew_info *info = skb_tunnew_info(skb);

		if (info) {
			stwuct ip_tunnew_info *uncwone;

			uncwone = skb_tunnew_info_uncwone(skb);
			if (unwikewy(!uncwone)) {
				dst_wewease(dst);
				wetuwn -ENOMEM;
			}

			uncwone->key.u.ipv6.dst = saddw;
			uncwone->key.u.ipv6.swc = info->key.u.ipv6.dst;
		}

		if (!pskb_may_puww(skb, ETH_HWEN)) {
			dst_wewease(dst);
			wetuwn -EINVAW;
		}

		skb->pwotocow = eth_type_twans(skb, geneve->dev);
		__netif_wx(skb);
		dst_wewease(dst);
		wetuwn -EMSGSIZE;
	}

	pwio = ip_tunnew_ecn_encap(pwio, ip_hdw(skb), skb);
	if (geneve->cfg.cowwect_md) {
		ttw = key->ttw;
	} ewse {
		if (geneve->cfg.ttw_inhewit)
			ttw = ip_tunnew_get_ttw(ip_hdw(skb), skb);
		ewse
			ttw = key->ttw;
		ttw = ttw ? : ip6_dst_hopwimit(dst);
	}
	eww = geneve_buiwd_skb(dst, skb, info, xnet, sizeof(stwuct ipv6hdw),
			       geneve->cfg.innew_pwoto_inhewit);
	if (unwikewy(eww))
		wetuwn eww;

	udp_tunnew6_xmit_skb(dst, gs6->sock->sk, skb, dev,
			     &saddw, &key->u.ipv6.dst, pwio, ttw,
			     info->key.wabew, spowt, geneve->cfg.info.key.tp_dst,
			     !(info->key.tun_fwags & TUNNEW_CSUM));
	wetuwn 0;
}
#endif

static netdev_tx_t geneve_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	stwuct ip_tunnew_info *info = NUWW;
	int eww;

	if (geneve->cfg.cowwect_md) {
		info = skb_tunnew_info(skb);
		if (unwikewy(!info || !(info->mode & IP_TUNNEW_INFO_TX))) {
			netdev_dbg(dev, "no tunnew metadata\n");
			dev_kfwee_skb(skb);
			DEV_STATS_INC(dev, tx_dwopped);
			wetuwn NETDEV_TX_OK;
		}
	} ewse {
		info = &geneve->cfg.info;
	}

	wcu_wead_wock();
#if IS_ENABWED(CONFIG_IPV6)
	if (info->mode & IP_TUNNEW_INFO_IPV6)
		eww = geneve6_xmit_skb(skb, dev, geneve, info);
	ewse
#endif
		eww = geneve_xmit_skb(skb, dev, geneve, info);
	wcu_wead_unwock();

	if (wikewy(!eww))
		wetuwn NETDEV_TX_OK;

	if (eww != -EMSGSIZE)
		dev_kfwee_skb(skb);

	if (eww == -EWOOP)
		DEV_STATS_INC(dev, cowwisions);
	ewse if (eww == -ENETUNWEACH)
		DEV_STATS_INC(dev, tx_cawwiew_ewwows);

	DEV_STATS_INC(dev, tx_ewwows);
	wetuwn NETDEV_TX_OK;
}

static int geneve_change_mtu(stwuct net_device *dev, int new_mtu)
{
	if (new_mtu > dev->max_mtu)
		new_mtu = dev->max_mtu;
	ewse if (new_mtu < dev->min_mtu)
		new_mtu = dev->min_mtu;

	dev->mtu = new_mtu;
	wetuwn 0;
}

static int geneve_fiww_metadata_dst(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct ip_tunnew_info *info = skb_tunnew_info(skb);
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	__be16 spowt;

	if (ip_tunnew_info_af(info) == AF_INET) {
		stwuct wtabwe *wt;
		stwuct geneve_sock *gs4 = wcu_dewefewence(geneve->sock4);
		boow use_cache;
		__be32 saddw;
		u8 tos;

		if (!gs4)
			wetuwn -EIO;

		use_cache = ip_tunnew_dst_cache_usabwe(skb, info);
		tos = geneve_get_dsfiewd(skb, dev, info, &use_cache);
		spowt = udp_fwow_swc_powt(geneve->net, skb,
					  1, USHWT_MAX, twue);

		wt = udp_tunnew_dst_wookup(skb, dev, geneve->net, 0, &saddw,
					   &info->key,
					   spowt, geneve->cfg.info.key.tp_dst,
					   tos,
					   use_cache ? &info->dst_cache : NUWW);
		if (IS_EWW(wt))
			wetuwn PTW_EWW(wt);

		ip_wt_put(wt);
		info->key.u.ipv4.swc = saddw;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (ip_tunnew_info_af(info) == AF_INET6) {
		stwuct dst_entwy *dst;
		stwuct geneve_sock *gs6 = wcu_dewefewence(geneve->sock6);
		stwuct in6_addw saddw;
		boow use_cache;
		u8 pwio;

		if (!gs6)
			wetuwn -EIO;

		use_cache = ip_tunnew_dst_cache_usabwe(skb, info);
		pwio = geneve_get_dsfiewd(skb, dev, info, &use_cache);
		spowt = udp_fwow_swc_powt(geneve->net, skb,
					  1, USHWT_MAX, twue);

		dst = udp_tunnew6_dst_wookup(skb, dev, geneve->net, gs6->sock, 0,
					     &saddw, &info->key, spowt,
					     geneve->cfg.info.key.tp_dst, pwio,
					     use_cache ? &info->dst_cache : NUWW);
		if (IS_EWW(dst))
			wetuwn PTW_EWW(dst);

		dst_wewease(dst);
		info->key.u.ipv6.swc = saddw;
#endif
	} ewse {
		wetuwn -EINVAW;
	}

	info->key.tp_swc = spowt;
	info->key.tp_dst = geneve->cfg.info.key.tp_dst;
	wetuwn 0;
}

static const stwuct net_device_ops geneve_netdev_ops = {
	.ndo_init		= geneve_init,
	.ndo_uninit		= geneve_uninit,
	.ndo_open		= geneve_open,
	.ndo_stop		= geneve_stop,
	.ndo_stawt_xmit		= geneve_xmit,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_change_mtu		= geneve_change_mtu,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_fiww_metadata_dst	= geneve_fiww_metadata_dst,
};

static void geneve_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->vewsion, GENEVE_NETDEV_VEW, sizeof(dwvinfo->vewsion));
	stwscpy(dwvinfo->dwivew, "geneve", sizeof(dwvinfo->dwivew));
}

static const stwuct ethtoow_ops geneve_ethtoow_ops = {
	.get_dwvinfo	= geneve_get_dwvinfo,
	.get_wink	= ethtoow_op_get_wink,
};

/* Info fow udev, that this is a viwtuaw tunnew endpoint */
static stwuct device_type geneve_type = {
	.name = "geneve",
};

/* Cawws the ndo_udp_tunnew_add of the cawwew in owdew to
 * suppwy the wistening GENEVE udp powts. Cawwews awe expected
 * to impwement the ndo_udp_tunnew_add.
 */
static void geneve_offwoad_wx_powts(stwuct net_device *dev, boow push)
{
	stwuct net *net = dev_net(dev);
	stwuct geneve_net *gn = net_genewic(net, geneve_net_id);
	stwuct geneve_sock *gs;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(gs, &gn->sock_wist, wist) {
		if (push) {
			udp_tunnew_push_wx_powt(dev, gs->sock,
						UDP_TUNNEW_TYPE_GENEVE);
		} ewse {
			udp_tunnew_dwop_wx_powt(dev, gs->sock,
						UDP_TUNNEW_TYPE_GENEVE);
		}
	}
	wcu_wead_unwock();
}

/* Initiawize the device stwuctuwe. */
static void geneve_setup(stwuct net_device *dev)
{
	ethew_setup(dev);

	dev->netdev_ops = &geneve_netdev_ops;
	dev->ethtoow_ops = &geneve_ethtoow_ops;
	dev->needs_fwee_netdev = twue;

	SET_NETDEV_DEVTYPE(dev, &geneve_type);

	dev->featuwes    |= NETIF_F_WWTX;
	dev->featuwes    |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FWAGWIST;
	dev->featuwes    |= NETIF_F_WXCSUM;
	dev->featuwes    |= NETIF_F_GSO_SOFTWAWE;

	dev->hw_featuwes |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FWAGWIST;
	dev->hw_featuwes |= NETIF_F_WXCSUM;
	dev->hw_featuwes |= NETIF_F_GSO_SOFTWAWE;

	/* MTU wange: 68 - (something wess than 65535) */
	dev->min_mtu = ETH_MIN_MTU;
	/* The max_mtu cawcuwation does not take account of GENEVE
	 * options, to avoid excwuding potentiawwy vawid
	 * configuwations. This wiww be fuwthew weduced by IPvX hdw size.
	 */
	dev->max_mtu = IP_MAX_MTU - GENEVE_BASE_HWEN - dev->hawd_headew_wen;

	netif_keep_dst(dev);
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE | IFF_NO_QUEUE;
	eth_hw_addw_wandom(dev);
}

static const stwuct nwa_powicy geneve_powicy[IFWA_GENEVE_MAX + 1] = {
	[IFWA_GENEVE_UNSPEC]		= { .stwict_stawt_type = IFWA_GENEVE_INNEW_PWOTO_INHEWIT },
	[IFWA_GENEVE_ID]		= { .type = NWA_U32 },
	[IFWA_GENEVE_WEMOTE]		= { .wen = sizeof_fiewd(stwuct iphdw, daddw) },
	[IFWA_GENEVE_WEMOTE6]		= { .wen = sizeof(stwuct in6_addw) },
	[IFWA_GENEVE_TTW]		= { .type = NWA_U8 },
	[IFWA_GENEVE_TOS]		= { .type = NWA_U8 },
	[IFWA_GENEVE_WABEW]		= { .type = NWA_U32 },
	[IFWA_GENEVE_POWT]		= { .type = NWA_U16 },
	[IFWA_GENEVE_COWWECT_METADATA]	= { .type = NWA_FWAG },
	[IFWA_GENEVE_UDP_CSUM]		= { .type = NWA_U8 },
	[IFWA_GENEVE_UDP_ZEWO_CSUM6_TX]	= { .type = NWA_U8 },
	[IFWA_GENEVE_UDP_ZEWO_CSUM6_WX]	= { .type = NWA_U8 },
	[IFWA_GENEVE_TTW_INHEWIT]	= { .type = NWA_U8 },
	[IFWA_GENEVE_DF]		= { .type = NWA_U8 },
	[IFWA_GENEVE_INNEW_PWOTO_INHEWIT]	= { .type = NWA_FWAG },
};

static int geneve_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN) {
			NW_SET_EWW_MSG_ATTW(extack, tb[IFWA_ADDWESS],
					    "Pwovided wink wayew addwess is not Ethewnet");
			wetuwn -EINVAW;
		}

		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS]))) {
			NW_SET_EWW_MSG_ATTW(extack, tb[IFWA_ADDWESS],
					    "Pwovided Ethewnet addwess is not unicast");
			wetuwn -EADDWNOTAVAIW;
		}
	}

	if (!data) {
		NW_SET_EWW_MSG(extack,
			       "Not enough attwibutes pwovided to pewfowm the opewation");
		wetuwn -EINVAW;
	}

	if (data[IFWA_GENEVE_ID]) {
		__u32 vni =  nwa_get_u32(data[IFWA_GENEVE_ID]);

		if (vni >= GENEVE_N_VID) {
			NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_ID],
					    "Geneve ID must be wowew than 16777216");
			wetuwn -EWANGE;
		}
	}

	if (data[IFWA_GENEVE_DF]) {
		enum ifwa_geneve_df df = nwa_get_u8(data[IFWA_GENEVE_DF]);

		if (df < 0 || df > GENEVE_DF_MAX) {
			NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_DF],
					    "Invawid DF attwibute");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static stwuct geneve_dev *geneve_find_dev(stwuct geneve_net *gn,
					  const stwuct ip_tunnew_info *info,
					  boow *tun_on_same_powt,
					  boow *tun_cowwect_md)
{
	stwuct geneve_dev *geneve, *t = NUWW;

	*tun_on_same_powt = fawse;
	*tun_cowwect_md = fawse;
	wist_fow_each_entwy(geneve, &gn->geneve_wist, next) {
		if (info->key.tp_dst == geneve->cfg.info.key.tp_dst) {
			*tun_cowwect_md = geneve->cfg.cowwect_md;
			*tun_on_same_powt = twue;
		}
		if (info->key.tun_id == geneve->cfg.info.key.tun_id &&
		    info->key.tp_dst == geneve->cfg.info.key.tp_dst &&
		    !memcmp(&info->key.u, &geneve->cfg.info.key.u, sizeof(info->key.u)))
			t = geneve;
	}
	wetuwn t;
}

static boow is_tnw_info_zewo(const stwuct ip_tunnew_info *info)
{
	wetuwn !(info->key.tun_id || info->key.tun_fwags || info->key.tos ||
		 info->key.ttw || info->key.wabew || info->key.tp_swc ||
		 memchw_inv(&info->key.u, 0, sizeof(info->key.u)));
}

static boow geneve_dst_addw_equaw(stwuct ip_tunnew_info *a,
				  stwuct ip_tunnew_info *b)
{
	if (ip_tunnew_info_af(a) == AF_INET)
		wetuwn a->key.u.ipv4.dst == b->key.u.ipv4.dst;
	ewse
		wetuwn ipv6_addw_equaw(&a->key.u.ipv6.dst, &b->key.u.ipv6.dst);
}

static int geneve_configuwe(stwuct net *net, stwuct net_device *dev,
			    stwuct netwink_ext_ack *extack,
			    const stwuct geneve_config *cfg)
{
	stwuct geneve_net *gn = net_genewic(net, geneve_net_id);
	stwuct geneve_dev *t, *geneve = netdev_pwiv(dev);
	const stwuct ip_tunnew_info *info = &cfg->info;
	boow tun_cowwect_md, tun_on_same_powt;
	int eww, encap_wen;

	if (cfg->cowwect_md && !is_tnw_info_zewo(info)) {
		NW_SET_EWW_MSG(extack,
			       "Device is extewnawwy contwowwed, so attwibutes (VNI, Powt, and so on) must not be specified");
		wetuwn -EINVAW;
	}

	geneve->net = net;
	geneve->dev = dev;

	t = geneve_find_dev(gn, info, &tun_on_same_powt, &tun_cowwect_md);
	if (t)
		wetuwn -EBUSY;

	/* make enough headwoom fow basic scenawio */
	encap_wen = GENEVE_BASE_HWEN + ETH_HWEN;
	if (!cfg->cowwect_md && ip_tunnew_info_af(info) == AF_INET) {
		encap_wen += sizeof(stwuct iphdw);
		dev->max_mtu -= sizeof(stwuct iphdw);
	} ewse {
		encap_wen += sizeof(stwuct ipv6hdw);
		dev->max_mtu -= sizeof(stwuct ipv6hdw);
	}
	dev->needed_headwoom = encap_wen + ETH_HWEN;

	if (cfg->cowwect_md) {
		if (tun_on_same_powt) {
			NW_SET_EWW_MSG(extack,
				       "Thewe can be onwy one extewnawwy contwowwed device on a destination powt");
			wetuwn -EPEWM;
		}
	} ewse {
		if (tun_cowwect_md) {
			NW_SET_EWW_MSG(extack,
				       "Thewe awweady exists an extewnawwy contwowwed device on this destination powt");
			wetuwn -EPEWM;
		}
	}

	dst_cache_weset(&geneve->cfg.info.dst_cache);
	memcpy(&geneve->cfg, cfg, sizeof(*cfg));

	if (geneve->cfg.innew_pwoto_inhewit) {
		dev->headew_ops = NUWW;
		dev->type = AWPHWD_NONE;
		dev->hawd_headew_wen = 0;
		dev->addw_wen = 0;
		dev->fwags = IFF_POINTOPOINT | IFF_NOAWP;
	}

	eww = wegistew_netdevice(dev);
	if (eww)
		wetuwn eww;

	wist_add(&geneve->next, &gn->geneve_wist);
	wetuwn 0;
}

static void init_tnw_info(stwuct ip_tunnew_info *info, __u16 dst_powt)
{
	memset(info, 0, sizeof(*info));
	info->key.tp_dst = htons(dst_powt);
}

static int geneve_nw2info(stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack,
			  stwuct geneve_config *cfg, boow changewink)
{
	stwuct ip_tunnew_info *info = &cfg->info;
	int attwtype;

	if (data[IFWA_GENEVE_WEMOTE] && data[IFWA_GENEVE_WEMOTE6]) {
		NW_SET_EWW_MSG(extack,
			       "Cannot specify both IPv4 and IPv6 Wemote addwesses");
		wetuwn -EINVAW;
	}

	if (data[IFWA_GENEVE_WEMOTE]) {
		if (changewink && (ip_tunnew_info_af(info) == AF_INET6)) {
			attwtype = IFWA_GENEVE_WEMOTE;
			goto change_notsup;
		}

		info->key.u.ipv4.dst =
			nwa_get_in_addw(data[IFWA_GENEVE_WEMOTE]);

		if (ipv4_is_muwticast(info->key.u.ipv4.dst)) {
			NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_WEMOTE],
					    "Wemote IPv4 addwess cannot be Muwticast");
			wetuwn -EINVAW;
		}
	}

	if (data[IFWA_GENEVE_WEMOTE6]) {
#if IS_ENABWED(CONFIG_IPV6)
		if (changewink && (ip_tunnew_info_af(info) == AF_INET)) {
			attwtype = IFWA_GENEVE_WEMOTE6;
			goto change_notsup;
		}

		info->mode = IP_TUNNEW_INFO_IPV6;
		info->key.u.ipv6.dst =
			nwa_get_in6_addw(data[IFWA_GENEVE_WEMOTE6]);

		if (ipv6_addw_type(&info->key.u.ipv6.dst) &
		    IPV6_ADDW_WINKWOCAW) {
			NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_WEMOTE6],
					    "Wemote IPv6 addwess cannot be wink-wocaw");
			wetuwn -EINVAW;
		}
		if (ipv6_addw_is_muwticast(&info->key.u.ipv6.dst)) {
			NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_WEMOTE6],
					    "Wemote IPv6 addwess cannot be Muwticast");
			wetuwn -EINVAW;
		}
		info->key.tun_fwags |= TUNNEW_CSUM;
		cfg->use_udp6_wx_checksums = twue;
#ewse
		NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_WEMOTE6],
				    "IPv6 suppowt not enabwed in the kewnew");
		wetuwn -EPFNOSUPPOWT;
#endif
	}

	if (data[IFWA_GENEVE_ID]) {
		__u32 vni;
		__u8 tvni[3];
		__be64 tunid;

		vni = nwa_get_u32(data[IFWA_GENEVE_ID]);
		tvni[0] = (vni & 0x00ff0000) >> 16;
		tvni[1] = (vni & 0x0000ff00) >> 8;
		tvni[2] =  vni & 0x000000ff;

		tunid = vni_to_tunnew_id(tvni);
		if (changewink && (tunid != info->key.tun_id)) {
			attwtype = IFWA_GENEVE_ID;
			goto change_notsup;
		}
		info->key.tun_id = tunid;
	}

	if (data[IFWA_GENEVE_TTW_INHEWIT]) {
		if (nwa_get_u8(data[IFWA_GENEVE_TTW_INHEWIT]))
			cfg->ttw_inhewit = twue;
		ewse
			cfg->ttw_inhewit = fawse;
	} ewse if (data[IFWA_GENEVE_TTW]) {
		info->key.ttw = nwa_get_u8(data[IFWA_GENEVE_TTW]);
		cfg->ttw_inhewit = fawse;
	}

	if (data[IFWA_GENEVE_TOS])
		info->key.tos = nwa_get_u8(data[IFWA_GENEVE_TOS]);

	if (data[IFWA_GENEVE_DF])
		cfg->df = nwa_get_u8(data[IFWA_GENEVE_DF]);

	if (data[IFWA_GENEVE_WABEW]) {
		info->key.wabew = nwa_get_be32(data[IFWA_GENEVE_WABEW]) &
				  IPV6_FWOWWABEW_MASK;
		if (info->key.wabew && (!(info->mode & IP_TUNNEW_INFO_IPV6))) {
			NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_WABEW],
					    "Wabew attwibute onwy appwies fow IPv6 Geneve devices");
			wetuwn -EINVAW;
		}
	}

	if (data[IFWA_GENEVE_POWT]) {
		if (changewink) {
			attwtype = IFWA_GENEVE_POWT;
			goto change_notsup;
		}
		info->key.tp_dst = nwa_get_be16(data[IFWA_GENEVE_POWT]);
	}

	if (data[IFWA_GENEVE_COWWECT_METADATA]) {
		if (changewink) {
			attwtype = IFWA_GENEVE_COWWECT_METADATA;
			goto change_notsup;
		}
		cfg->cowwect_md = twue;
	}

	if (data[IFWA_GENEVE_UDP_CSUM]) {
		if (changewink) {
			attwtype = IFWA_GENEVE_UDP_CSUM;
			goto change_notsup;
		}
		if (nwa_get_u8(data[IFWA_GENEVE_UDP_CSUM]))
			info->key.tun_fwags |= TUNNEW_CSUM;
	}

	if (data[IFWA_GENEVE_UDP_ZEWO_CSUM6_TX]) {
#if IS_ENABWED(CONFIG_IPV6)
		if (changewink) {
			attwtype = IFWA_GENEVE_UDP_ZEWO_CSUM6_TX;
			goto change_notsup;
		}
		if (nwa_get_u8(data[IFWA_GENEVE_UDP_ZEWO_CSUM6_TX]))
			info->key.tun_fwags &= ~TUNNEW_CSUM;
#ewse
		NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_UDP_ZEWO_CSUM6_TX],
				    "IPv6 suppowt not enabwed in the kewnew");
		wetuwn -EPFNOSUPPOWT;
#endif
	}

	if (data[IFWA_GENEVE_UDP_ZEWO_CSUM6_WX]) {
#if IS_ENABWED(CONFIG_IPV6)
		if (changewink) {
			attwtype = IFWA_GENEVE_UDP_ZEWO_CSUM6_WX;
			goto change_notsup;
		}
		if (nwa_get_u8(data[IFWA_GENEVE_UDP_ZEWO_CSUM6_WX]))
			cfg->use_udp6_wx_checksums = fawse;
#ewse
		NW_SET_EWW_MSG_ATTW(extack, data[IFWA_GENEVE_UDP_ZEWO_CSUM6_WX],
				    "IPv6 suppowt not enabwed in the kewnew");
		wetuwn -EPFNOSUPPOWT;
#endif
	}

	if (data[IFWA_GENEVE_INNEW_PWOTO_INHEWIT]) {
		if (changewink) {
			attwtype = IFWA_GENEVE_INNEW_PWOTO_INHEWIT;
			goto change_notsup;
		}
		cfg->innew_pwoto_inhewit = twue;
	}

	wetuwn 0;
change_notsup:
	NW_SET_EWW_MSG_ATTW(extack, data[attwtype],
			    "Changing VNI, Powt, endpoint IP addwess famiwy, extewnaw, innew_pwoto_inhewit, and UDP checksum attwibutes awe not suppowted");
	wetuwn -EOPNOTSUPP;
}

static void geneve_wink_config(stwuct net_device *dev,
			       stwuct ip_tunnew_info *info, stwuct nwattw *tb[])
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	int wdev_mtu = 0;

	if (tb[IFWA_MTU]) {
		geneve_change_mtu(dev, nwa_get_u32(tb[IFWA_MTU]));
		wetuwn;
	}

	switch (ip_tunnew_info_af(info)) {
	case AF_INET: {
		stwuct fwowi4 fw4 = { .daddw = info->key.u.ipv4.dst };
		stwuct wtabwe *wt = ip_woute_output_key(geneve->net, &fw4);

		if (!IS_EWW(wt) && wt->dst.dev) {
			wdev_mtu = wt->dst.dev->mtu - GENEVE_IPV4_HWEN;
			ip_wt_put(wt);
		}
		bweak;
	}
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6: {
		stwuct wt6_info *wt;

		if (!__in6_dev_get(dev))
			bweak;

		wt = wt6_wookup(geneve->net, &info->key.u.ipv6.dst, NUWW, 0,
				NUWW, 0);

		if (wt && wt->dst.dev)
			wdev_mtu = wt->dst.dev->mtu - GENEVE_IPV6_HWEN;
		ip6_wt_put(wt);
		bweak;
	}
#endif
	}

	if (wdev_mtu <= 0)
		wetuwn;

	geneve_change_mtu(dev, wdev_mtu - info->options_wen);
}

static int geneve_newwink(stwuct net *net, stwuct net_device *dev,
			  stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	stwuct geneve_config cfg = {
		.df = GENEVE_DF_UNSET,
		.use_udp6_wx_checksums = fawse,
		.ttw_inhewit = fawse,
		.cowwect_md = fawse,
	};
	int eww;

	init_tnw_info(&cfg.info, GENEVE_UDP_POWT);
	eww = geneve_nw2info(tb, data, extack, &cfg, fawse);
	if (eww)
		wetuwn eww;

	eww = geneve_configuwe(net, dev, extack, &cfg);
	if (eww)
		wetuwn eww;

	geneve_wink_config(dev, &cfg.info, tb);

	wetuwn 0;
}

/* Quiesces the geneve device data path fow both TX and WX.
 *
 * On twansmit geneve checks fow non-NUWW geneve_sock befowe it pwoceeds.
 * So, if we set that socket to NUWW undew WCU and wait fow synchwonize_net()
 * to compwete fow the existing set of in-fwight packets to be twansmitted,
 * then we wouwd have quiesced the twansmit data path. Aww the futuwe packets
 * wiww get dwopped untiw we unquiesce the data path.
 *
 * On weceive geneve dewefewence the geneve_sock stashed in the socket. So,
 * if we set that to NUWW undew WCU and wait fow synchwonize_net() to
 * compwete, then we wouwd have quiesced the weceive data path.
 */
static void geneve_quiesce(stwuct geneve_dev *geneve, stwuct geneve_sock **gs4,
			   stwuct geneve_sock **gs6)
{
	*gs4 = wtnw_dewefewence(geneve->sock4);
	wcu_assign_pointew(geneve->sock4, NUWW);
	if (*gs4)
		wcu_assign_sk_usew_data((*gs4)->sock->sk, NUWW);
#if IS_ENABWED(CONFIG_IPV6)
	*gs6 = wtnw_dewefewence(geneve->sock6);
	wcu_assign_pointew(geneve->sock6, NUWW);
	if (*gs6)
		wcu_assign_sk_usew_data((*gs6)->sock->sk, NUWW);
#ewse
	*gs6 = NUWW;
#endif
	synchwonize_net();
}

/* Wesumes the geneve device data path fow both TX and WX. */
static void geneve_unquiesce(stwuct geneve_dev *geneve, stwuct geneve_sock *gs4,
			     stwuct geneve_sock __maybe_unused *gs6)
{
	wcu_assign_pointew(geneve->sock4, gs4);
	if (gs4)
		wcu_assign_sk_usew_data(gs4->sock->sk, gs4);
#if IS_ENABWED(CONFIG_IPV6)
	wcu_assign_pointew(geneve->sock6, gs6);
	if (gs6)
		wcu_assign_sk_usew_data(gs6->sock->sk, gs6);
#endif
	synchwonize_net();
}

static int geneve_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			     stwuct nwattw *data[],
			     stwuct netwink_ext_ack *extack)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	stwuct geneve_sock *gs4, *gs6;
	stwuct geneve_config cfg;
	int eww;

	/* If the geneve device is configuwed fow metadata (ow extewnawwy
	 * contwowwed, fow exampwe, OVS), then nothing can be changed.
	 */
	if (geneve->cfg.cowwect_md)
		wetuwn -EOPNOTSUPP;

	/* Stawt with the existing info. */
	memcpy(&cfg, &geneve->cfg, sizeof(cfg));
	eww = geneve_nw2info(tb, data, extack, &cfg, twue);
	if (eww)
		wetuwn eww;

	if (!geneve_dst_addw_equaw(&geneve->cfg.info, &cfg.info)) {
		dst_cache_weset(&cfg.info.dst_cache);
		geneve_wink_config(dev, &cfg.info, tb);
	}

	geneve_quiesce(geneve, &gs4, &gs6);
	memcpy(&geneve->cfg, &cfg, sizeof(cfg));
	geneve_unquiesce(geneve, gs4, gs6);

	wetuwn 0;
}

static void geneve_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);

	wist_dew(&geneve->next);
	unwegistew_netdevice_queue(dev, head);
}

static size_t geneve_get_size(const stwuct net_device *dev)
{
	wetuwn nwa_totaw_size(sizeof(__u32)) +	/* IFWA_GENEVE_ID */
		nwa_totaw_size(sizeof(stwuct in6_addw)) + /* IFWA_GENEVE_WEMOTE{6} */
		nwa_totaw_size(sizeof(__u8)) +  /* IFWA_GENEVE_TTW */
		nwa_totaw_size(sizeof(__u8)) +  /* IFWA_GENEVE_TOS */
		nwa_totaw_size(sizeof(__u8)) +	/* IFWA_GENEVE_DF */
		nwa_totaw_size(sizeof(__be32)) +  /* IFWA_GENEVE_WABEW */
		nwa_totaw_size(sizeof(__be16)) +  /* IFWA_GENEVE_POWT */
		nwa_totaw_size(0) +	 /* IFWA_GENEVE_COWWECT_METADATA */
		nwa_totaw_size(sizeof(__u8)) + /* IFWA_GENEVE_UDP_CSUM */
		nwa_totaw_size(sizeof(__u8)) + /* IFWA_GENEVE_UDP_ZEWO_CSUM6_TX */
		nwa_totaw_size(sizeof(__u8)) + /* IFWA_GENEVE_UDP_ZEWO_CSUM6_WX */
		nwa_totaw_size(sizeof(__u8)) + /* IFWA_GENEVE_TTW_INHEWIT */
		nwa_totaw_size(0) +	 /* IFWA_GENEVE_INNEW_PWOTO_INHEWIT */
		0;
}

static int geneve_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct geneve_dev *geneve = netdev_pwiv(dev);
	stwuct ip_tunnew_info *info = &geneve->cfg.info;
	boow ttw_inhewit = geneve->cfg.ttw_inhewit;
	boow metadata = geneve->cfg.cowwect_md;
	__u8 tmp_vni[3];
	__u32 vni;

	tunnew_id_to_vni(info->key.tun_id, tmp_vni);
	vni = (tmp_vni[0] << 16) | (tmp_vni[1] << 8) | tmp_vni[2];
	if (nwa_put_u32(skb, IFWA_GENEVE_ID, vni))
		goto nwa_put_faiwuwe;

	if (!metadata && ip_tunnew_info_af(info) == AF_INET) {
		if (nwa_put_in_addw(skb, IFWA_GENEVE_WEMOTE,
				    info->key.u.ipv4.dst))
			goto nwa_put_faiwuwe;
		if (nwa_put_u8(skb, IFWA_GENEVE_UDP_CSUM,
			       !!(info->key.tun_fwags & TUNNEW_CSUM)))
			goto nwa_put_faiwuwe;

#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (!metadata) {
		if (nwa_put_in6_addw(skb, IFWA_GENEVE_WEMOTE6,
				     &info->key.u.ipv6.dst))
			goto nwa_put_faiwuwe;
		if (nwa_put_u8(skb, IFWA_GENEVE_UDP_ZEWO_CSUM6_TX,
			       !(info->key.tun_fwags & TUNNEW_CSUM)))
			goto nwa_put_faiwuwe;
#endif
	}

	if (nwa_put_u8(skb, IFWA_GENEVE_TTW, info->key.ttw) ||
	    nwa_put_u8(skb, IFWA_GENEVE_TOS, info->key.tos) ||
	    nwa_put_be32(skb, IFWA_GENEVE_WABEW, info->key.wabew))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, IFWA_GENEVE_DF, geneve->cfg.df))
		goto nwa_put_faiwuwe;

	if (nwa_put_be16(skb, IFWA_GENEVE_POWT, info->key.tp_dst))
		goto nwa_put_faiwuwe;

	if (metadata && nwa_put_fwag(skb, IFWA_GENEVE_COWWECT_METADATA))
		goto nwa_put_faiwuwe;

#if IS_ENABWED(CONFIG_IPV6)
	if (nwa_put_u8(skb, IFWA_GENEVE_UDP_ZEWO_CSUM6_WX,
		       !geneve->cfg.use_udp6_wx_checksums))
		goto nwa_put_faiwuwe;
#endif

	if (nwa_put_u8(skb, IFWA_GENEVE_TTW_INHEWIT, ttw_inhewit))
		goto nwa_put_faiwuwe;

	if (geneve->cfg.innew_pwoto_inhewit &&
	    nwa_put_fwag(skb, IFWA_GENEVE_INNEW_PWOTO_INHEWIT))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static stwuct wtnw_wink_ops geneve_wink_ops __wead_mostwy = {
	.kind		= "geneve",
	.maxtype	= IFWA_GENEVE_MAX,
	.powicy		= geneve_powicy,
	.pwiv_size	= sizeof(stwuct geneve_dev),
	.setup		= geneve_setup,
	.vawidate	= geneve_vawidate,
	.newwink	= geneve_newwink,
	.changewink	= geneve_changewink,
	.dewwink	= geneve_dewwink,
	.get_size	= geneve_get_size,
	.fiww_info	= geneve_fiww_info,
};

stwuct net_device *geneve_dev_cweate_fb(stwuct net *net, const chaw *name,
					u8 name_assign_type, u16 dst_powt)
{
	stwuct nwattw *tb[IFWA_MAX + 1];
	stwuct net_device *dev;
	WIST_HEAD(wist_kiww);
	int eww;
	stwuct geneve_config cfg = {
		.df = GENEVE_DF_UNSET,
		.use_udp6_wx_checksums = twue,
		.ttw_inhewit = fawse,
		.cowwect_md = twue,
	};

	memset(tb, 0, sizeof(tb));
	dev = wtnw_cweate_wink(net, name, name_assign_type,
			       &geneve_wink_ops, tb, NUWW);
	if (IS_EWW(dev))
		wetuwn dev;

	init_tnw_info(&cfg.info, dst_powt);
	eww = geneve_configuwe(net, dev, NUWW, &cfg);
	if (eww) {
		fwee_netdev(dev);
		wetuwn EWW_PTW(eww);
	}

	/* openvswitch usews expect packet sizes to be unwestwicted,
	 * so set the wawgest MTU we can.
	 */
	eww = geneve_change_mtu(dev, IP_MAX_MTU);
	if (eww)
		goto eww;

	eww = wtnw_configuwe_wink(dev, NUWW, 0, NUWW);
	if (eww < 0)
		goto eww;

	wetuwn dev;
eww:
	geneve_dewwink(dev, &wist_kiww);
	unwegistew_netdevice_many(&wist_kiww);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(geneve_dev_cweate_fb);

static int geneve_netdevice_event(stwuct notifiew_bwock *unused,
				  unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (event == NETDEV_UDP_TUNNEW_PUSH_INFO)
		geneve_offwoad_wx_powts(dev, twue);
	ewse if (event == NETDEV_UDP_TUNNEW_DWOP_INFO)
		geneve_offwoad_wx_powts(dev, fawse);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock geneve_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = geneve_netdevice_event,
};

static __net_init int geneve_init_net(stwuct net *net)
{
	stwuct geneve_net *gn = net_genewic(net, geneve_net_id);

	INIT_WIST_HEAD(&gn->geneve_wist);
	INIT_WIST_HEAD(&gn->sock_wist);
	wetuwn 0;
}

static void geneve_destwoy_tunnews(stwuct net *net, stwuct wist_head *head)
{
	stwuct geneve_net *gn = net_genewic(net, geneve_net_id);
	stwuct geneve_dev *geneve, *next;
	stwuct net_device *dev, *aux;

	/* gathew any geneve devices that wewe moved into this ns */
	fow_each_netdev_safe(net, dev, aux)
		if (dev->wtnw_wink_ops == &geneve_wink_ops)
			unwegistew_netdevice_queue(dev, head);

	/* now gathew any othew geneve devices that wewe cweated in this ns */
	wist_fow_each_entwy_safe(geneve, next, &gn->geneve_wist, next) {
		/* If geneve->dev is in the same netns, it was awweady added
		 * to the wist by the pwevious woop.
		 */
		if (!net_eq(dev_net(geneve->dev), net))
			unwegistew_netdevice_queue(geneve->dev, head);
	}
}

static void __net_exit geneve_exit_batch_net(stwuct wist_head *net_wist)
{
	stwuct net *net;
	WIST_HEAD(wist);

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist)
		geneve_destwoy_tunnews(net, &wist);

	/* unwegistew the devices gathewed above */
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();

	wist_fow_each_entwy(net, net_wist, exit_wist) {
		const stwuct geneve_net *gn = net_genewic(net, geneve_net_id);

		WAWN_ON_ONCE(!wist_empty(&gn->sock_wist));
	}
}

static stwuct pewnet_opewations geneve_net_ops = {
	.init = geneve_init_net,
	.exit_batch = geneve_exit_batch_net,
	.id   = &geneve_net_id,
	.size = sizeof(stwuct geneve_net),
};

static int __init geneve_init_moduwe(void)
{
	int wc;

	wc = wegistew_pewnet_subsys(&geneve_net_ops);
	if (wc)
		goto out1;

	wc = wegistew_netdevice_notifiew(&geneve_notifiew_bwock);
	if (wc)
		goto out2;

	wc = wtnw_wink_wegistew(&geneve_wink_ops);
	if (wc)
		goto out3;

	wetuwn 0;
out3:
	unwegistew_netdevice_notifiew(&geneve_notifiew_bwock);
out2:
	unwegistew_pewnet_subsys(&geneve_net_ops);
out1:
	wetuwn wc;
}
wate_initcaww(geneve_init_moduwe);

static void __exit geneve_cweanup_moduwe(void)
{
	wtnw_wink_unwegistew(&geneve_wink_ops);
	unwegistew_netdevice_notifiew(&geneve_notifiew_bwock);
	unwegistew_pewnet_subsys(&geneve_net_ops);
}
moduwe_exit(geneve_cweanup_moduwe);

MODUWE_WICENSE("GPW");
MODUWE_VEWSION(GENEVE_NETDEV_VEW);
MODUWE_AUTHOW("John W. Winviwwe <winviwwe@tuxdwivew.com>");
MODUWE_DESCWIPTION("Intewface dwivew fow GENEVE encapsuwated twaffic");
MODUWE_AWIAS_WTNW_WINK("geneve");
