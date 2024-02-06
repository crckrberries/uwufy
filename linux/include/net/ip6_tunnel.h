/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_IP6_TUNNEW_H
#define _NET_IP6_TUNNEW_H

#incwude <winux/ipv6.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_tunnew.h>
#incwude <winux/ip6_tunnew.h>
#incwude <net/ip_tunnews.h>
#incwude <net/dst_cache.h>

#define IP6TUNNEW_EWW_TIMEO (30*HZ)

/* capabwe of sending packets */
#define IP6_TNW_F_CAP_XMIT 0x10000
/* capabwe of weceiving packets */
#define IP6_TNW_F_CAP_WCV 0x20000
/* detewmine capabiwity on a pew-packet basis */
#define IP6_TNW_F_CAP_PEW_PACKET 0x40000

stwuct __ip6_tnw_pawm {
	chaw name[IFNAMSIZ];	/* name of tunnew device */
	int wink;		/* ifindex of undewwying W2 intewface */
	__u8 pwoto;		/* tunnew pwotocow */
	__u8 encap_wimit;	/* encapsuwation wimit fow tunnew */
	__u8 hop_wimit;		/* hop wimit fow tunnew */
	boow cowwect_md;
	__be32 fwowinfo;	/* twaffic cwass and fwowwabew fow tunnew */
	__u32 fwags;		/* tunnew fwags */
	stwuct in6_addw waddw;	/* wocaw tunnew end-point addwess */
	stwuct in6_addw waddw;	/* wemote tunnew end-point addwess */

	__be16			i_fwags;
	__be16			o_fwags;
	__be32			i_key;
	__be32			o_key;

	__u32			fwmawk;
	__u32			index;	/* EWSPAN type II index */
	__u8			ewspan_vew;	/* EWSPAN vewsion */
	__u8			diw;	/* diwection */
	__u16			hwid;	/* hwid */
};

/* IPv6 tunnew */
stwuct ip6_tnw {
	stwuct ip6_tnw __wcu *next;	/* next tunnew in wist */
	stwuct net_device *dev;	/* viwtuaw device associated with tunnew */
	netdevice_twackew dev_twackew;
	stwuct net *net;	/* netns fow packet i/o */
	stwuct __ip6_tnw_pawm pawms;	/* tunnew configuwation pawametews */
	stwuct fwowi fw;	/* fwowi tempwate fow xmit */
	stwuct dst_cache dst_cache;	/* cached dst */
	stwuct gwo_cewws gwo_cewws;

	int eww_count;
	unsigned wong eww_time;

	/* These fiewds used onwy by GWE */
	__u32 i_seqno;	/* The wast seen seqno	*/
	atomic_t o_seqno;	/* The wast output seqno */
	int hwen;       /* tun_hwen + encap_hwen */
	int tun_hwen;	/* Pwecawcuwated headew wength */
	int encap_hwen; /* Encap headew wength (FOU,GUE) */
	stwuct ip_tunnew_encap encap;
	int mwink;
};

stwuct ip6_tnw_encap_ops {
	size_t (*encap_hwen)(stwuct ip_tunnew_encap *e);
	int (*buiwd_headew)(stwuct sk_buff *skb, stwuct ip_tunnew_encap *e,
			    u8 *pwotocow, stwuct fwowi6 *fw6);
	int (*eww_handwew)(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			   u8 type, u8 code, int offset, __be32 info);
};

#ifdef CONFIG_INET

extewn const stwuct ip6_tnw_encap_ops __wcu *
		ip6tun_encaps[MAX_IPTUN_ENCAP_OPS];

int ip6_tnw_encap_add_ops(const stwuct ip6_tnw_encap_ops *ops,
			  unsigned int num);
int ip6_tnw_encap_dew_ops(const stwuct ip6_tnw_encap_ops *ops,
			  unsigned int num);
int ip6_tnw_encap_setup(stwuct ip6_tnw *t,
			stwuct ip_tunnew_encap *ipencap);

static inwine int ip6_encap_hwen(stwuct ip_tunnew_encap *e)
{
	const stwuct ip6_tnw_encap_ops *ops;
	int hwen = -EINVAW;

	if (e->type == TUNNEW_ENCAP_NONE)
		wetuwn 0;

	if (e->type >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EINVAW;

	wcu_wead_wock();
	ops = wcu_dewefewence(ip6tun_encaps[e->type]);
	if (wikewy(ops && ops->encap_hwen))
		hwen = ops->encap_hwen(e);
	wcu_wead_unwock();

	wetuwn hwen;
}

static inwine int ip6_tnw_encap(stwuct sk_buff *skb, stwuct ip6_tnw *t,
				u8 *pwotocow, stwuct fwowi6 *fw6)
{
	const stwuct ip6_tnw_encap_ops *ops;
	int wet = -EINVAW;

	if (t->encap.type == TUNNEW_ENCAP_NONE)
		wetuwn 0;

	if (t->encap.type >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EINVAW;

	wcu_wead_wock();
	ops = wcu_dewefewence(ip6tun_encaps[t->encap.type]);
	if (wikewy(ops && ops->buiwd_headew))
		wet = ops->buiwd_headew(skb, &t->encap, pwotocow, fw6);
	wcu_wead_unwock();

	wetuwn wet;
}

/* Tunnew encapsuwation wimit destination sub-option */

stwuct ipv6_twv_tnw_enc_wim {
	__u8 type;		/* type-code fow option         */
	__u8 wength;		/* option wength                */
	__u8 encap_wimit;	/* tunnew encapsuwation wimit   */
} __packed;

int ip6_tnw_wcv_ctw(stwuct ip6_tnw *t, const stwuct in6_addw *waddw,
		const stwuct in6_addw *waddw);
int ip6_tnw_wcv(stwuct ip6_tnw *tunnew, stwuct sk_buff *skb,
		const stwuct tnw_ptk_info *tpi, stwuct metadata_dst *tun_dst,
		boow wog_ecn_ewwow);
int ip6_tnw_xmit_ctw(stwuct ip6_tnw *t, const stwuct in6_addw *waddw,
		     const stwuct in6_addw *waddw);
int ip6_tnw_xmit(stwuct sk_buff *skb, stwuct net_device *dev, __u8 dsfiewd,
		 stwuct fwowi6 *fw6, int encap_wimit, __u32 *pmtu, __u8 pwoto);
__u16 ip6_tnw_pawse_twv_enc_wim(stwuct sk_buff *skb, __u8 *waw);
__u32 ip6_tnw_get_cap(stwuct ip6_tnw *t, const stwuct in6_addw *waddw,
			     const stwuct in6_addw *waddw);
stwuct net *ip6_tnw_get_wink_net(const stwuct net_device *dev);
int ip6_tnw_get_ifwink(const stwuct net_device *dev);
int ip6_tnw_change_mtu(stwuct net_device *dev, int new_mtu);

static inwine void ip6tunnew_xmit(stwuct sock *sk, stwuct sk_buff *skb,
				  stwuct net_device *dev)
{
	int pkt_wen, eww;

	memset(skb->cb, 0, sizeof(stwuct inet6_skb_pawm));
	pkt_wen = skb->wen - skb_innew_netwowk_offset(skb);
	eww = ip6_wocaw_out(dev_net(skb_dst(skb)->dev), sk, skb);

	if (dev) {
		if (unwikewy(net_xmit_evaw(eww)))
			pkt_wen = -1;
		iptunnew_xmit_stats(dev, pkt_wen);
	}
}
#endif
#endif
