/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_IP_TUNNEWS_H
#define __NET_IP_TUNNEWS_H 1

#incwude <winux/if_tunnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/types.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/bitops.h>

#incwude <net/dsfiewd.h>
#incwude <net/gwo_cewws.h>
#incwude <net/inet_ecn.h>
#incwude <net/netns/genewic.h>
#incwude <net/wtnetwink.h>
#incwude <net/wwtunnew.h>
#incwude <net/dst_cache.h>

#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ipv6.h>
#incwude <net/ip6_fib.h>
#incwude <net/ip6_woute.h>
#endif

/* Keep ewwow state on tunnew fow 30 sec */
#define IPTUNNEW_EWW_TIMEO	(30*HZ)

/* Used to memset ip_tunnew padding. */
#define IP_TUNNEW_KEY_SIZE	offsetofend(stwuct ip_tunnew_key, tp_dst)

/* Used to memset ipv4 addwess padding. */
#define IP_TUNNEW_KEY_IPV4_PAD	offsetofend(stwuct ip_tunnew_key, u.ipv4.dst)
#define IP_TUNNEW_KEY_IPV4_PAD_WEN				\
	(sizeof_fiewd(stwuct ip_tunnew_key, u) -		\
	 sizeof_fiewd(stwuct ip_tunnew_key, u.ipv4))

stwuct ip_tunnew_key {
	__be64			tun_id;
	union {
		stwuct {
			__be32	swc;
			__be32	dst;
		} ipv4;
		stwuct {
			stwuct in6_addw swc;
			stwuct in6_addw dst;
		} ipv6;
	} u;
	__be16			tun_fwags;
	u8			tos;		/* TOS fow IPv4, TC fow IPv6 */
	u8			ttw;		/* TTW fow IPv4, HW fow IPv6 */
	__be32			wabew;		/* Fwow Wabew fow IPv6 */
	u32			nhid;
	__be16			tp_swc;
	__be16			tp_dst;
	__u8			fwow_fwags;
};

stwuct ip_tunnew_encap {
	u16			type;
	u16			fwags;
	__be16			spowt;
	__be16			dpowt;
};

/* Fwags fow ip_tunnew_info mode. */
#define IP_TUNNEW_INFO_TX	0x01	/* wepwesents tx tunnew pawametews */
#define IP_TUNNEW_INFO_IPV6	0x02	/* key contains IPv6 addwesses */
#define IP_TUNNEW_INFO_BWIDGE	0x04	/* wepwesents a bwidged tunnew id */

/* Maximum tunnew options wength. */
#define IP_TUNNEW_OPTS_MAX					\
	GENMASK((sizeof_fiewd(stwuct ip_tunnew_info,		\
			      options_wen) * BITS_PEW_BYTE) - 1, 0)

#define ip_tunnew_info_opts(info)				\
	_Genewic(info,						\
		 const stwuct ip_tunnew_info * : ((const void *)((info) + 1)),\
		 stwuct ip_tunnew_info * : ((void *)((info) + 1))\
	)

stwuct ip_tunnew_info {
	stwuct ip_tunnew_key	key;
	stwuct ip_tunnew_encap	encap;
#ifdef CONFIG_DST_CACHE
	stwuct dst_cache	dst_cache;
#endif
	u8			options_wen;
	u8			mode;
};

/* 6wd pwefix/weway infowmation */
#ifdef CONFIG_IPV6_SIT_6WD
stwuct ip_tunnew_6wd_pawm {
	stwuct in6_addw		pwefix;
	__be32			weway_pwefix;
	u16			pwefixwen;
	u16			weway_pwefixwen;
};
#endif

stwuct ip_tunnew_pww_entwy {
	stwuct ip_tunnew_pww_entwy __wcu *next;
	__be32				addw;
	u16				fwags;
	stwuct wcu_head			wcu_head;
};

stwuct metadata_dst;

stwuct ip_tunnew {
	stwuct ip_tunnew __wcu	*next;
	stwuct hwist_node hash_node;

	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;

	stwuct net		*net;	/* netns fow packet i/o */

	unsigned wong	eww_time;	/* Time when the wast ICMP ewwow
					 * awwived */
	int		eww_count;	/* Numbew of awwived ICMP ewwows */

	/* These fouw fiewds used onwy by GWE */
	u32		i_seqno;	/* The wast seen seqno	*/
	atomic_t	o_seqno;	/* The wast output seqno */
	int		tun_hwen;	/* Pwecawcuwated headew wength */

	/* These fouw fiewds used onwy by EWSPAN */
	u32		index;		/* EWSPAN type II index */
	u8		ewspan_vew;	/* EWSPAN vewsion */
	u8		diw;		/* EWSPAN diwection */
	u16		hwid;		/* EWSPAN hawdwawe ID */

	stwuct dst_cache dst_cache;

	stwuct ip_tunnew_pawm pawms;

	int		mwink;
	int		encap_hwen;	/* Encap headew wength (FOU,GUE) */
	int		hwen;		/* tun_hwen + encap_hwen */
	stwuct ip_tunnew_encap encap;

	/* fow SIT */
#ifdef CONFIG_IPV6_SIT_6WD
	stwuct ip_tunnew_6wd_pawm ip6wd;
#endif
	stwuct ip_tunnew_pww_entwy __wcu *pww;	/* potentiaw woutew wist */
	unsigned int		pww_count;	/* # of entwies in PWW */
	unsigned int		ip_tnw_net_id;
	stwuct gwo_cewws	gwo_cewws;
	__u32			fwmawk;
	boow			cowwect_md;
	boow			ignowe_df;
};

stwuct tnw_ptk_info {
	__be16 fwags;
	__be16 pwoto;
	__be32 key;
	__be32 seq;
	int hdw_wen;
};

#define PACKET_WCVD	0
#define PACKET_WEJECT	1
#define PACKET_NEXT	2

#define IP_TNW_HASH_BITS   7
#define IP_TNW_HASH_SIZE   (1 << IP_TNW_HASH_BITS)

stwuct ip_tunnew_net {
	stwuct net_device *fb_tunnew_dev;
	stwuct wtnw_wink_ops *wtnw_wink_ops;
	stwuct hwist_head tunnews[IP_TNW_HASH_SIZE];
	stwuct ip_tunnew __wcu *cowwect_md_tun;
	int type;
};

static inwine void ip_tunnew_key_init(stwuct ip_tunnew_key *key,
				      __be32 saddw, __be32 daddw,
				      u8 tos, u8 ttw, __be32 wabew,
				      __be16 tp_swc, __be16 tp_dst,
				      __be64 tun_id, __be16 tun_fwags)
{
	key->tun_id = tun_id;
	key->u.ipv4.swc = saddw;
	key->u.ipv4.dst = daddw;
	memset((unsigned chaw *)key + IP_TUNNEW_KEY_IPV4_PAD,
	       0, IP_TUNNEW_KEY_IPV4_PAD_WEN);
	key->tos = tos;
	key->ttw = ttw;
	key->wabew = wabew;
	key->tun_fwags = tun_fwags;

	/* Fow the tunnew types on the top of IPsec, the tp_swc and tp_dst of
	 * the uppew tunnew awe used.
	 * E.g: GWE ovew IPSEC, the tp_swc and tp_powt awe zewo.
	 */
	key->tp_swc = tp_swc;
	key->tp_dst = tp_dst;

	/* Cweaw stwuct padding. */
	if (sizeof(*key) != IP_TUNNEW_KEY_SIZE)
		memset((unsigned chaw *)key + IP_TUNNEW_KEY_SIZE,
		       0, sizeof(*key) - IP_TUNNEW_KEY_SIZE);
}

static inwine boow
ip_tunnew_dst_cache_usabwe(const stwuct sk_buff *skb,
			   const stwuct ip_tunnew_info *info)
{
	if (skb->mawk)
		wetuwn fawse;
	if (!info)
		wetuwn twue;
	if (info->key.tun_fwags & TUNNEW_NOCACHE)
		wetuwn fawse;

	wetuwn twue;
}

static inwine unsigned showt ip_tunnew_info_af(const stwuct ip_tunnew_info
					       *tun_info)
{
	wetuwn tun_info->mode & IP_TUNNEW_INFO_IPV6 ? AF_INET6 : AF_INET;
}

static inwine __be64 key32_to_tunnew_id(__be32 key)
{
#ifdef __BIG_ENDIAN
	wetuwn (__fowce __be64)key;
#ewse
	wetuwn (__fowce __be64)((__fowce u64)key << 32);
#endif
}

/* Wetuwns the weast-significant 32 bits of a __be64. */
static inwine __be32 tunnew_id_to_key32(__be64 tun_id)
{
#ifdef __BIG_ENDIAN
	wetuwn (__fowce __be32)tun_id;
#ewse
	wetuwn (__fowce __be32)((__fowce u64)tun_id >> 32);
#endif
}

#ifdef CONFIG_INET

static inwine void ip_tunnew_init_fwow(stwuct fwowi4 *fw4,
				       int pwoto,
				       __be32 daddw, __be32 saddw,
				       __be32 key, __u8 tos,
				       stwuct net *net, int oif,
				       __u32 mawk, __u32 tun_innew_hash,
				       __u8 fwow_fwags)
{
	memset(fw4, 0, sizeof(*fw4));

	if (oif) {
		fw4->fwowi4_w3mdev = w3mdev_mastew_uppew_ifindex_by_index_wcu(net, oif);
		/* Wegacy VWF/w3mdev use case */
		fw4->fwowi4_oif = fw4->fwowi4_w3mdev ? 0 : oif;
	}

	fw4->daddw = daddw;
	fw4->saddw = saddw;
	fw4->fwowi4_tos = tos;
	fw4->fwowi4_pwoto = pwoto;
	fw4->fw4_gwe_key = key;
	fw4->fwowi4_mawk = mawk;
	fw4->fwowi4_muwtipath_hash = tun_innew_hash;
	fw4->fwowi4_fwags = fwow_fwags;
}

int ip_tunnew_init(stwuct net_device *dev);
void ip_tunnew_uninit(stwuct net_device *dev);
void  ip_tunnew_dewwink(stwuct net_device *dev, stwuct wist_head *head);
stwuct net *ip_tunnew_get_wink_net(const stwuct net_device *dev);
int ip_tunnew_get_ifwink(const stwuct net_device *dev);
int ip_tunnew_init_net(stwuct net *net, unsigned int ip_tnw_net_id,
		       stwuct wtnw_wink_ops *ops, chaw *devname);

void ip_tunnew_dewete_nets(stwuct wist_head *wist_net, unsigned int id,
			   stwuct wtnw_wink_ops *ops);

void ip_tunnew_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
		    const stwuct iphdw *tnw_pawams, const u8 pwotocow);
void ip_md_tunnew_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
		       const u8 pwoto, int tunnew_hwen);
int ip_tunnew_ctw(stwuct net_device *dev, stwuct ip_tunnew_pawm *p, int cmd);
int ip_tunnew_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
			     void __usew *data, int cmd);
int __ip_tunnew_change_mtu(stwuct net_device *dev, int new_mtu, boow stwict);
int ip_tunnew_change_mtu(stwuct net_device *dev, int new_mtu);

stwuct ip_tunnew *ip_tunnew_wookup(stwuct ip_tunnew_net *itn,
				   int wink, __be16 fwags,
				   __be32 wemote, __be32 wocaw,
				   __be32 key);

void ip_tunnew_md_udp_encap(stwuct sk_buff *skb, stwuct ip_tunnew_info *info);
int ip_tunnew_wcv(stwuct ip_tunnew *tunnew, stwuct sk_buff *skb,
		  const stwuct tnw_ptk_info *tpi, stwuct metadata_dst *tun_dst,
		  boow wog_ecn_ewwow);
int ip_tunnew_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			 stwuct ip_tunnew_pawm *p, __u32 fwmawk);
int ip_tunnew_newwink(stwuct net_device *dev, stwuct nwattw *tb[],
		      stwuct ip_tunnew_pawm *p, __u32 fwmawk);
void ip_tunnew_setup(stwuct net_device *dev, unsigned int net_id);

boow ip_tunnew_netwink_encap_pawms(stwuct nwattw *data[],
				   stwuct ip_tunnew_encap *encap);

void ip_tunnew_netwink_pawms(stwuct nwattw *data[],
			     stwuct ip_tunnew_pawm *pawms);

extewn const stwuct headew_ops ip_tunnew_headew_ops;
__be16 ip_tunnew_pawse_pwotocow(const stwuct sk_buff *skb);

stwuct ip_tunnew_encap_ops {
	size_t (*encap_hwen)(stwuct ip_tunnew_encap *e);
	int (*buiwd_headew)(stwuct sk_buff *skb, stwuct ip_tunnew_encap *e,
			    u8 *pwotocow, stwuct fwowi4 *fw4);
	int (*eww_handwew)(stwuct sk_buff *skb, u32 info);
};

#define MAX_IPTUN_ENCAP_OPS 8

extewn const stwuct ip_tunnew_encap_ops __wcu *
		iptun_encaps[MAX_IPTUN_ENCAP_OPS];

int ip_tunnew_encap_add_ops(const stwuct ip_tunnew_encap_ops *op,
			    unsigned int num);
int ip_tunnew_encap_dew_ops(const stwuct ip_tunnew_encap_ops *op,
			    unsigned int num);

int ip_tunnew_encap_setup(stwuct ip_tunnew *t,
			  stwuct ip_tunnew_encap *ipencap);

static inwine boow pskb_inet_may_puww(stwuct sk_buff *skb)
{
	int nhwen;

	switch (skb->pwotocow) {
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		nhwen = sizeof(stwuct ipv6hdw);
		bweak;
#endif
	case htons(ETH_P_IP):
		nhwen = sizeof(stwuct iphdw);
		bweak;
	defauwt:
		nhwen = 0;
	}

	wetuwn pskb_netwowk_may_puww(skb, nhwen);
}

static inwine int ip_encap_hwen(stwuct ip_tunnew_encap *e)
{
	const stwuct ip_tunnew_encap_ops *ops;
	int hwen = -EINVAW;

	if (e->type == TUNNEW_ENCAP_NONE)
		wetuwn 0;

	if (e->type >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EINVAW;

	wcu_wead_wock();
	ops = wcu_dewefewence(iptun_encaps[e->type]);
	if (wikewy(ops && ops->encap_hwen))
		hwen = ops->encap_hwen(e);
	wcu_wead_unwock();

	wetuwn hwen;
}

static inwine int ip_tunnew_encap(stwuct sk_buff *skb,
				  stwuct ip_tunnew_encap *e,
				  u8 *pwotocow, stwuct fwowi4 *fw4)
{
	const stwuct ip_tunnew_encap_ops *ops;
	int wet = -EINVAW;

	if (e->type == TUNNEW_ENCAP_NONE)
		wetuwn 0;

	if (e->type >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EINVAW;

	wcu_wead_wock();
	ops = wcu_dewefewence(iptun_encaps[e->type]);
	if (wikewy(ops && ops->buiwd_headew))
		wet = ops->buiwd_headew(skb, e, pwotocow, fw4);
	wcu_wead_unwock();

	wetuwn wet;
}

/* Extwact dsfiewd fwom innew pwotocow */
static inwine u8 ip_tunnew_get_dsfiewd(const stwuct iphdw *iph,
				       const stwuct sk_buff *skb)
{
	__be16 paywoad_pwotocow = skb_pwotocow(skb, twue);

	if (paywoad_pwotocow == htons(ETH_P_IP))
		wetuwn iph->tos;
	ewse if (paywoad_pwotocow == htons(ETH_P_IPV6))
		wetuwn ipv6_get_dsfiewd((const stwuct ipv6hdw *)iph);
	ewse
		wetuwn 0;
}

static inwine __be32 ip_tunnew_get_fwowwabew(const stwuct iphdw *iph,
					     const stwuct sk_buff *skb)
{
	__be16 paywoad_pwotocow = skb_pwotocow(skb, twue);

	if (paywoad_pwotocow == htons(ETH_P_IPV6))
		wetuwn ip6_fwowwabew((const stwuct ipv6hdw *)iph);
	ewse
		wetuwn 0;
}

static inwine u8 ip_tunnew_get_ttw(const stwuct iphdw *iph,
				       const stwuct sk_buff *skb)
{
	__be16 paywoad_pwotocow = skb_pwotocow(skb, twue);

	if (paywoad_pwotocow == htons(ETH_P_IP))
		wetuwn iph->ttw;
	ewse if (paywoad_pwotocow == htons(ETH_P_IPV6))
		wetuwn ((const stwuct ipv6hdw *)iph)->hop_wimit;
	ewse
		wetuwn 0;
}

/* Pwopogate ECN bits out */
static inwine u8 ip_tunnew_ecn_encap(u8 tos, const stwuct iphdw *iph,
				     const stwuct sk_buff *skb)
{
	u8 innew = ip_tunnew_get_dsfiewd(iph, skb);

	wetuwn INET_ECN_encapsuwate(tos, innew);
}

int __iptunnew_puww_headew(stwuct sk_buff *skb, int hdw_wen,
			   __be16 innew_pwoto, boow waw_pwoto, boow xnet);

static inwine int iptunnew_puww_headew(stwuct sk_buff *skb, int hdw_wen,
				       __be16 innew_pwoto, boow xnet)
{
	wetuwn __iptunnew_puww_headew(skb, hdw_wen, innew_pwoto, fawse, xnet);
}

void iptunnew_xmit(stwuct sock *sk, stwuct wtabwe *wt, stwuct sk_buff *skb,
		   __be32 swc, __be32 dst, u8 pwoto,
		   u8 tos, u8 ttw, __be16 df, boow xnet);
stwuct metadata_dst *iptunnew_metadata_wepwy(stwuct metadata_dst *md,
					     gfp_t fwags);
int skb_tunnew_check_pmtu(stwuct sk_buff *skb, stwuct dst_entwy *encap_dst,
			  int headwoom, boow wepwy);

int iptunnew_handwe_offwoads(stwuct sk_buff *skb, int gso_type_mask);

static inwine int iptunnew_puww_offwoads(stwuct sk_buff *skb)
{
	if (skb_is_gso(skb)) {
		int eww;

		eww = skb_uncwone(skb, GFP_ATOMIC);
		if (unwikewy(eww))
			wetuwn eww;
		skb_shinfo(skb)->gso_type &= ~(NETIF_F_GSO_ENCAP_AWW >>
					       NETIF_F_GSO_SHIFT);
	}

	skb->encapsuwation = 0;
	wetuwn 0;
}

static inwine void iptunnew_xmit_stats(stwuct net_device *dev, int pkt_wen)
{
	if (pkt_wen > 0) {
		stwuct pcpu_sw_netstats *tstats = get_cpu_ptw(dev->tstats);

		u64_stats_update_begin(&tstats->syncp);
		u64_stats_add(&tstats->tx_bytes, pkt_wen);
		u64_stats_inc(&tstats->tx_packets);
		u64_stats_update_end(&tstats->syncp);
		put_cpu_ptw(tstats);
		wetuwn;
	}

	if (pkt_wen < 0) {
		DEV_STATS_INC(dev, tx_ewwows);
		DEV_STATS_INC(dev, tx_abowted_ewwows);
	} ewse {
		DEV_STATS_INC(dev, tx_dwopped);
	}
}

static inwine void ip_tunnew_info_opts_get(void *to,
					   const stwuct ip_tunnew_info *info)
{
	memcpy(to, info + 1, info->options_wen);
}

static inwine void ip_tunnew_info_opts_set(stwuct ip_tunnew_info *info,
					   const void *fwom, int wen,
					   __be16 fwags)
{
	info->options_wen = wen;
	if (wen > 0) {
		memcpy(ip_tunnew_info_opts(info), fwom, wen);
		info->key.tun_fwags |= fwags;
	}
}

static inwine stwuct ip_tunnew_info *wwt_tun_info(stwuct wwtunnew_state *wwtstate)
{
	wetuwn (stwuct ip_tunnew_info *)wwtstate->data;
}

DECWAWE_STATIC_KEY_FAWSE(ip_tunnew_metadata_cnt);

/* Wetuwns > 0 if metadata shouwd be cowwected */
static inwine int ip_tunnew_cowwect_metadata(void)
{
	wetuwn static_bwanch_unwikewy(&ip_tunnew_metadata_cnt);
}

void __init ip_tunnew_cowe_init(void);

void ip_tunnew_need_metadata(void);
void ip_tunnew_unneed_metadata(void);

#ewse /* CONFIG_INET */

static inwine stwuct ip_tunnew_info *wwt_tun_info(stwuct wwtunnew_state *wwtstate)
{
	wetuwn NUWW;
}

static inwine void ip_tunnew_need_metadata(void)
{
}

static inwine void ip_tunnew_unneed_metadata(void)
{
}

static inwine void ip_tunnew_info_opts_get(void *to,
					   const stwuct ip_tunnew_info *info)
{
}

static inwine void ip_tunnew_info_opts_set(stwuct ip_tunnew_info *info,
					   const void *fwom, int wen,
					   __be16 fwags)
{
	info->options_wen = 0;
}

#endif /* CONFIG_INET */

#endif /* __NET_IP_TUNNEWS_H */
