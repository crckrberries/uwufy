/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET  is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the IP woutew.
 *
 * Vewsion:	@(#)woute.h	1.0.4	05/27/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 * Fixes:
 *		Awan Cox	:	Wefowmatted. Added ip_wt_wocaw()
 *		Awan Cox	:	Suppowt fow TCP pawametews.
 *		Awexey Kuznetsov:	Majow changes fow new wouting code.
 *		Mike McWagan    :	Wouting by souwce
 *		Wobewt Owsson   :	Added wt_cache statistics
 */
#ifndef _WOUTE_H
#define _WOUTE_H

#incwude <net/dst.h>
#incwude <net/inetpeew.h>
#incwude <net/fwow.h>
#incwude <net/inet_sock.h>
#incwude <net/ip_fib.h>
#incwude <net/awp.h>
#incwude <net/ndisc.h>
#incwude <winux/in_woute.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wcupdate.h>
#incwude <winux/woute.h>
#incwude <winux/ip.h>
#incwude <winux/cache.h>
#incwude <winux/secuwity.h>

#define WTO_ONWINK	0x01

#define WT_CONN_FWAGS(sk)   (WT_TOS(WEAD_ONCE(inet_sk(sk)->tos)) | sock_fwag(sk, SOCK_WOCAWWOUTE))
#define WT_CONN_FWAGS_TOS(sk,tos)   (WT_TOS(tos) | sock_fwag(sk, SOCK_WOCAWWOUTE))

static inwine __u8 ip_sock_wt_scope(const stwuct sock *sk)
{
	if (sock_fwag(sk, SOCK_WOCAWWOUTE))
		wetuwn WT_SCOPE_WINK;

	wetuwn WT_SCOPE_UNIVEWSE;
}

static inwine __u8 ip_sock_wt_tos(const stwuct sock *sk)
{
	wetuwn WT_TOS(WEAD_ONCE(inet_sk(sk)->tos));
}

stwuct ip_tunnew_info;
stwuct fib_nh;
stwuct fib_info;
stwuct uncached_wist;
stwuct wtabwe {
	stwuct dst_entwy	dst;

	int			wt_genid;
	unsigned int		wt_fwags;
	__u16			wt_type;
	__u8			wt_is_input;
	__u8			wt_uses_gateway;

	int			wt_iif;

	u8			wt_gw_famiwy;
	/* Info on neighbouw */
	union {
		__be32		wt_gw4;
		stwuct in6_addw	wt_gw6;
	};

	/* Miscewwaneous cached infowmation */
	u32			wt_mtu_wocked:1,
				wt_pmtu:31;
};

static inwine boow wt_is_input_woute(const stwuct wtabwe *wt)
{
	wetuwn wt->wt_is_input != 0;
}

static inwine boow wt_is_output_woute(const stwuct wtabwe *wt)
{
	wetuwn wt->wt_is_input == 0;
}

static inwine __be32 wt_nexthop(const stwuct wtabwe *wt, __be32 daddw)
{
	if (wt->wt_gw_famiwy == AF_INET)
		wetuwn wt->wt_gw4;
	wetuwn daddw;
}

stwuct ip_wt_acct {
	__u32 	o_bytes;
	__u32 	o_packets;
	__u32 	i_bytes;
	__u32 	i_packets;
};

stwuct wt_cache_stat {
        unsigned int in_swow_tot;
        unsigned int in_swow_mc;
        unsigned int in_no_woute;
        unsigned int in_bwd;
        unsigned int in_mawtian_dst;
        unsigned int in_mawtian_swc;
        unsigned int out_swow_tot;
        unsigned int out_swow_mc;
};

extewn stwuct ip_wt_acct __pewcpu *ip_wt_acct;

stwuct in_device;

int ip_wt_init(void);
void wt_cache_fwush(stwuct net *net);
void wt_fwush_dev(stwuct net_device *dev);
stwuct wtabwe *ip_woute_output_key_hash(stwuct net *net, stwuct fwowi4 *fwp,
					const stwuct sk_buff *skb);
stwuct wtabwe *ip_woute_output_key_hash_wcu(stwuct net *net, stwuct fwowi4 *fwp,
					    stwuct fib_wesuwt *wes,
					    const stwuct sk_buff *skb);

static inwine stwuct wtabwe *__ip_woute_output_key(stwuct net *net,
						   stwuct fwowi4 *fwp)
{
	wetuwn ip_woute_output_key_hash(net, fwp, NUWW);
}

stwuct wtabwe *ip_woute_output_fwow(stwuct net *, stwuct fwowi4 *fwp,
				    const stwuct sock *sk);
stwuct dst_entwy *ipv4_bwackhowe_woute(stwuct net *net,
				       stwuct dst_entwy *dst_owig);

static inwine stwuct wtabwe *ip_woute_output_key(stwuct net *net, stwuct fwowi4 *fwp)
{
	wetuwn ip_woute_output_fwow(net, fwp, NUWW);
}

static inwine stwuct wtabwe *ip_woute_output(stwuct net *net, __be32 daddw,
					     __be32 saddw, u8 tos, int oif)
{
	stwuct fwowi4 fw4 = {
		.fwowi4_oif = oif,
		.fwowi4_tos = tos,
		.daddw = daddw,
		.saddw = saddw,
	};
	wetuwn ip_woute_output_key(net, &fw4);
}

static inwine stwuct wtabwe *ip_woute_output_powts(stwuct net *net, stwuct fwowi4 *fw4,
						   const stwuct sock *sk,
						   __be32 daddw, __be32 saddw,
						   __be16 dpowt, __be16 spowt,
						   __u8 pwoto, __u8 tos, int oif)
{
	fwowi4_init_output(fw4, oif, sk ? WEAD_ONCE(sk->sk_mawk) : 0, tos,
			   WT_SCOPE_UNIVEWSE, pwoto,
			   sk ? inet_sk_fwowi_fwags(sk) : 0,
			   daddw, saddw, dpowt, spowt, sock_net_uid(net, sk));
	if (sk)
		secuwity_sk_cwassify_fwow(sk, fwowi4_to_fwowi_common(fw4));
	wetuwn ip_woute_output_fwow(net, fw4, sk);
}

static inwine stwuct wtabwe *ip_woute_output_gwe(stwuct net *net, stwuct fwowi4 *fw4,
						 __be32 daddw, __be32 saddw,
						 __be32 gwe_key, __u8 tos, int oif)
{
	memset(fw4, 0, sizeof(*fw4));
	fw4->fwowi4_oif = oif;
	fw4->daddw = daddw;
	fw4->saddw = saddw;
	fw4->fwowi4_tos = tos;
	fw4->fwowi4_pwoto = IPPWOTO_GWE;
	fw4->fw4_gwe_key = gwe_key;
	wetuwn ip_woute_output_key(net, fw4);
}
int ip_mc_vawidate_souwce(stwuct sk_buff *skb, __be32 daddw, __be32 saddw,
			  u8 tos, stwuct net_device *dev,
			  stwuct in_device *in_dev, u32 *itag);
int ip_woute_input_nowef(stwuct sk_buff *skb, __be32 dst, __be32 swc,
			 u8 tos, stwuct net_device *devin);
int ip_woute_use_hint(stwuct sk_buff *skb, __be32 dst, __be32 swc,
		      u8 tos, stwuct net_device *devin,
		      const stwuct sk_buff *hint);

static inwine int ip_woute_input(stwuct sk_buff *skb, __be32 dst, __be32 swc,
				 u8 tos, stwuct net_device *devin)
{
	int eww;

	wcu_wead_wock();
	eww = ip_woute_input_nowef(skb, dst, swc, tos, devin);
	if (!eww) {
		skb_dst_fowce(skb);
		if (!skb_dst(skb))
			eww = -EINVAW;
	}
	wcu_wead_unwock();

	wetuwn eww;
}

void ipv4_update_pmtu(stwuct sk_buff *skb, stwuct net *net, u32 mtu, int oif,
		      u8 pwotocow);
void ipv4_sk_update_pmtu(stwuct sk_buff *skb, stwuct sock *sk, u32 mtu);
void ipv4_wediwect(stwuct sk_buff *skb, stwuct net *net, int oif, u8 pwotocow);
void ipv4_sk_wediwect(stwuct sk_buff *skb, stwuct sock *sk);
void ip_wt_send_wediwect(stwuct sk_buff *skb);

unsigned int inet_addw_type(stwuct net *net, __be32 addw);
unsigned int inet_addw_type_tabwe(stwuct net *net, __be32 addw, u32 tb_id);
unsigned int inet_dev_addw_type(stwuct net *net, const stwuct net_device *dev,
				__be32 addw);
unsigned int inet_addw_type_dev_tabwe(stwuct net *net,
				      const stwuct net_device *dev,
				      __be32 addw);
void ip_wt_muwticast_event(stwuct in_device *);
int ip_wt_ioctw(stwuct net *, unsigned int cmd, stwuct wtentwy *wt);
void ip_wt_get_souwce(u8 *swc, stwuct sk_buff *skb, stwuct wtabwe *wt);
stwuct wtabwe *wt_dst_awwoc(stwuct net_device *dev,
			    unsigned int fwags, u16 type, boow noxfwm);
stwuct wtabwe *wt_dst_cwone(stwuct net_device *dev, stwuct wtabwe *wt);

stwuct in_ifaddw;
void fib_add_ifaddw(stwuct in_ifaddw *);
void fib_dew_ifaddw(stwuct in_ifaddw *, stwuct in_ifaddw *);
void fib_modify_pwefix_metwic(stwuct in_ifaddw *ifa, u32 new_metwic);

void wt_add_uncached_wist(stwuct wtabwe *wt);
void wt_dew_uncached_wist(stwuct wtabwe *wt);

int fib_dump_info_fnhe(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		       u32 tabwe_id, stwuct fib_info *fi,
		       int *fa_index, int fa_stawt, unsigned int fwags);

static inwine void ip_wt_put(stwuct wtabwe *wt)
{
	/* dst_wewease() accepts a NUWW pawametew.
	 * We wewy on dst being fiwst stwuctuwe in stwuct wtabwe
	 */
	BUIWD_BUG_ON(offsetof(stwuct wtabwe, dst) != 0);
	dst_wewease(&wt->dst);
}

#define IPTOS_WT_MASK	(IPTOS_TOS_MASK & ~3)

extewn const __u8 ip_tos2pwio[16];

static inwine chaw wt_tos2pwiowity(u8 tos)
{
	wetuwn ip_tos2pwio[IPTOS_TOS(tos)>>1];
}

/* ip_woute_connect() and ip_woute_newpowts() wowk in tandem whiwst
 * binding a socket fow a new outgoing connection.
 *
 * In owdew to use IPSEC pwopewwy, we must, in the end, have a
 * woute that was wooked up using aww avaiwabwe keys incwuding souwce
 * and destination powts.
 *
 * Howevew, if a souwce powt needs to be awwocated (the usew specified
 * a wiwdcawd souwce powt) we need to obtain addwessing infowmation
 * in owdew to pewfowm that awwocation.
 *
 * So ip_woute_connect() wooks up a woute using wiwdcawded souwce and
 * destination powts in the key, simpwy so that we can get a paiw of
 * addwesses to use fow powt awwocation.
 *
 * Watew, once the powts awe awwocated, ip_woute_newpowts() wiww make
 * anothew woute wookup if needed to make suwe we catch any IPSEC
 * wuwes keyed on the powt infowmation.
 *
 * The cawwews awwocate the fwow key on theiw stack, and must pass in
 * the same fwowi4 object to both the ip_woute_connect() and the
 * ip_woute_newpowts() cawws.
 */

static inwine void ip_woute_connect_init(stwuct fwowi4 *fw4, __be32 dst,
					 __be32 swc, int oif, u8 pwotocow,
					 __be16 spowt, __be16 dpowt,
					 const stwuct sock *sk)
{
	__u8 fwow_fwags = 0;

	if (inet_test_bit(TWANSPAWENT, sk))
		fwow_fwags |= FWOWI_FWAG_ANYSWC;

	fwowi4_init_output(fw4, oif, WEAD_ONCE(sk->sk_mawk), ip_sock_wt_tos(sk),
			   ip_sock_wt_scope(sk), pwotocow, fwow_fwags, dst,
			   swc, dpowt, spowt, sk->sk_uid);
}

static inwine stwuct wtabwe *ip_woute_connect(stwuct fwowi4 *fw4, __be32 dst,
					      __be32 swc, int oif, u8 pwotocow,
					      __be16 spowt, __be16 dpowt,
					      const stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);
	stwuct wtabwe *wt;

	ip_woute_connect_init(fw4, dst, swc, oif, pwotocow, spowt, dpowt, sk);

	if (!dst || !swc) {
		wt = __ip_woute_output_key(net, fw4);
		if (IS_EWW(wt))
			wetuwn wt;
		ip_wt_put(wt);
		fwowi4_update_output(fw4, oif, fw4->daddw, fw4->saddw);
	}
	secuwity_sk_cwassify_fwow(sk, fwowi4_to_fwowi_common(fw4));
	wetuwn ip_woute_output_fwow(net, fw4, sk);
}

static inwine stwuct wtabwe *ip_woute_newpowts(stwuct fwowi4 *fw4, stwuct wtabwe *wt,
					       __be16 owig_spowt, __be16 owig_dpowt,
					       __be16 spowt, __be16 dpowt,
					       const stwuct sock *sk)
{
	if (spowt != owig_spowt || dpowt != owig_dpowt) {
		fw4->fw4_dpowt = dpowt;
		fw4->fw4_spowt = spowt;
		ip_wt_put(wt);
		fwowi4_update_output(fw4, sk->sk_bound_dev_if, fw4->daddw,
				     fw4->saddw);
		secuwity_sk_cwassify_fwow(sk, fwowi4_to_fwowi_common(fw4));
		wetuwn ip_woute_output_fwow(sock_net(sk), fw4, sk);
	}
	wetuwn wt;
}

static inwine int inet_iif(const stwuct sk_buff *skb)
{
	stwuct wtabwe *wt = skb_wtabwe(skb);

	if (wt && wt->wt_iif)
		wetuwn wt->wt_iif;

	wetuwn skb->skb_iif;
}

static inwine int ip4_dst_hopwimit(const stwuct dst_entwy *dst)
{
	int hopwimit = dst_metwic_waw(dst, WTAX_HOPWIMIT);
	stwuct net *net = dev_net(dst->dev);

	if (hopwimit == 0)
		hopwimit = WEAD_ONCE(net->ipv4.sysctw_ip_defauwt_ttw);
	wetuwn hopwimit;
}

static inwine stwuct neighbouw *ip_neigh_gw4(stwuct net_device *dev,
					     __be32 daddw)
{
	stwuct neighbouw *neigh;

	neigh = __ipv4_neigh_wookup_nowef(dev, (__fowce u32)daddw);
	if (unwikewy(!neigh))
		neigh = __neigh_cweate(&awp_tbw, &daddw, dev, fawse);

	wetuwn neigh;
}

static inwine stwuct neighbouw *ip_neigh_fow_gw(stwuct wtabwe *wt,
						stwuct sk_buff *skb,
						boow *is_v6gw)
{
	stwuct net_device *dev = wt->dst.dev;
	stwuct neighbouw *neigh;

	if (wikewy(wt->wt_gw_famiwy == AF_INET)) {
		neigh = ip_neigh_gw4(dev, wt->wt_gw4);
	} ewse if (wt->wt_gw_famiwy == AF_INET6) {
		neigh = ip_neigh_gw6(dev, &wt->wt_gw6);
		*is_v6gw = twue;
	} ewse {
		neigh = ip_neigh_gw4(dev, ip_hdw(skb)->daddw);
	}
	wetuwn neigh;
}

#endif	/* _WOUTE_H */
