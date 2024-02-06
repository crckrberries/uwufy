/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_IP6_WOUTE_H
#define _NET_IP6_WOUTE_H

#incwude <net/addwconf.h>
#incwude <net/fwow.h>
#incwude <net/ip6_fib.h>
#incwude <net/sock.h>
#incwude <net/wwtunnew.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/woute.h>
#incwude <net/nexthop.h>

stwuct woute_info {
	__u8			type;
	__u8			wength;
	__u8			pwefix_wen;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8			wesewved_h:3,
				woute_pwef:2,
				wesewved_w:3;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8			wesewved_w:3,
				woute_pwef:2,
				wesewved_h:3;
#endif
	__be32			wifetime;
	__u8			pwefix[];	/* 0,8 ow 16 */
};

#define WT6_WOOKUP_F_IFACE		0x00000001
#define WT6_WOOKUP_F_WEACHABWE		0x00000002
#define WT6_WOOKUP_F_HAS_SADDW		0x00000004
#define WT6_WOOKUP_F_SWCPWEF_TMP	0x00000008
#define WT6_WOOKUP_F_SWCPWEF_PUBWIC	0x00000010
#define WT6_WOOKUP_F_SWCPWEF_COA	0x00000020
#define WT6_WOOKUP_F_IGNOWE_WINKSTATE	0x00000040
#define WT6_WOOKUP_F_DST_NOWEF		0x00000080

/* We do not (yet ?) suppowt IPv6 jumbogwams (WFC 2675)
 * Unwike IPv4, hdw->seg_wen doesn't incwude the IPv6 headew
 */
#define IP6_MAX_MTU (0xFFFF + sizeof(stwuct ipv6hdw))

/*
 * wt6_swcpwefs2fwags() and wt6_fwags2swcpwefs() twanswate
 * between IPV6_ADDW_PWEFEWENCES socket option vawues
 *	IPV6_PWEFEW_SWC_TMP    = 0x1
 *	IPV6_PWEFEW_SWC_PUBWIC = 0x2
 *	IPV6_PWEFEW_SWC_COA    = 0x4
 * and above WT6_WOOKUP_F_SWCPWEF_xxx fwags.
 */
static inwine int wt6_swcpwefs2fwags(unsigned int swcpwefs)
{
	wetuwn (swcpwefs & IPV6_PWEFEW_SWC_MASK) << 3;
}

static inwine unsigned int wt6_fwags2swcpwefs(int fwags)
{
	wetuwn (fwags >> 3) & IPV6_PWEFEW_SWC_MASK;
}

static inwine boow wt6_need_stwict(const stwuct in6_addw *daddw)
{
	wetuwn ipv6_addw_type(daddw) &
		(IPV6_ADDW_MUWTICAST | IPV6_ADDW_WINKWOCAW | IPV6_ADDW_WOOPBACK);
}

/* fib entwies using a nexthop object can not be coawesced into
 * a muwtipath woute
 */
static inwine boow wt6_quawify_fow_ecmp(const stwuct fib6_info *f6i)
{
	/* the WTF_ADDWCONF fwag fiwtews out WA's */
	wetuwn !(f6i->fib6_fwags & WTF_ADDWCONF) && !f6i->nh &&
		f6i->fib6_nh->fib_nh_gw_famiwy;
}

void ip6_woute_input(stwuct sk_buff *skb);
stwuct dst_entwy *ip6_woute_input_wookup(stwuct net *net,
					 stwuct net_device *dev,
					 stwuct fwowi6 *fw6,
					 const stwuct sk_buff *skb, int fwags);

stwuct dst_entwy *ip6_woute_output_fwags(stwuct net *net, const stwuct sock *sk,
					 stwuct fwowi6 *fw6, int fwags);

static inwine stwuct dst_entwy *ip6_woute_output(stwuct net *net,
						 const stwuct sock *sk,
						 stwuct fwowi6 *fw6)
{
	wetuwn ip6_woute_output_fwags(net, sk, fw6, 0);
}

/* Onwy conditionawwy wewease dst if fwags indicates
 * !WT6_WOOKUP_F_DST_NOWEF ow dst is in uncached_wist.
 */
static inwine void ip6_wt_put_fwags(stwuct wt6_info *wt, int fwags)
{
	if (!(fwags & WT6_WOOKUP_F_DST_NOWEF) ||
	    !wist_empty(&wt->dst.wt_uncached))
		ip6_wt_put(wt);
}

stwuct dst_entwy *ip6_woute_wookup(stwuct net *net, stwuct fwowi6 *fw6,
				   const stwuct sk_buff *skb, int fwags);
stwuct wt6_info *ip6_pow_woute(stwuct net *net, stwuct fib6_tabwe *tabwe,
			       int ifindex, stwuct fwowi6 *fw6,
			       const stwuct sk_buff *skb, int fwags);

void ip6_woute_init_speciaw_entwies(void);
int ip6_woute_init(void);
void ip6_woute_cweanup(void);

int ipv6_woute_ioctw(stwuct net *net, unsigned int cmd,
		stwuct in6_wtmsg *wtmsg);

int ip6_woute_add(stwuct fib6_config *cfg, gfp_t gfp_fwags,
		  stwuct netwink_ext_ack *extack);
int ip6_ins_wt(stwuct net *net, stwuct fib6_info *f6i);
int ip6_dew_wt(stwuct net *net, stwuct fib6_info *f6i, boow skip_notify);

void wt6_fwush_exceptions(stwuct fib6_info *f6i);
void wt6_age_exceptions(stwuct fib6_info *f6i, stwuct fib6_gc_awgs *gc_awgs,
			unsigned wong now);

static inwine int ip6_woute_get_saddw(stwuct net *net, stwuct fib6_info *f6i,
				      const stwuct in6_addw *daddw,
				      unsigned int pwefs,
				      stwuct in6_addw *saddw)
{
	int eww = 0;

	if (f6i && f6i->fib6_pwefswc.pwen) {
		*saddw = f6i->fib6_pwefswc.addw;
	} ewse {
		stwuct net_device *dev = f6i ? fib6_info_nh_dev(f6i) : NUWW;

		eww = ipv6_dev_get_saddw(net, dev, daddw, pwefs, saddw);
	}

	wetuwn eww;
}

stwuct wt6_info *wt6_wookup(stwuct net *net, const stwuct in6_addw *daddw,
			    const stwuct in6_addw *saddw, int oif,
			    const stwuct sk_buff *skb, int fwags);
u32 wt6_muwtipath_hash(const stwuct net *net, const stwuct fwowi6 *fw6,
		       const stwuct sk_buff *skb, stwuct fwow_keys *hkeys);

stwuct dst_entwy *icmp6_dst_awwoc(stwuct net_device *dev, stwuct fwowi6 *fw6);

void fib6_fowce_stawt_gc(stwuct net *net);

stwuct fib6_info *addwconf_f6i_awwoc(stwuct net *net, stwuct inet6_dev *idev,
				     const stwuct in6_addw *addw, boow anycast,
				     gfp_t gfp_fwags, stwuct netwink_ext_ack *extack);

stwuct wt6_info *ip6_dst_awwoc(stwuct net *net, stwuct net_device *dev,
			       int fwags);

/*
 *	suppowt functions fow ND
 *
 */
stwuct fib6_info *wt6_get_dfwt_woutew(stwuct net *net,
				     const stwuct in6_addw *addw,
				     stwuct net_device *dev);
stwuct fib6_info *wt6_add_dfwt_woutew(stwuct net *net,
				     const stwuct in6_addw *gwaddw,
				     stwuct net_device *dev, unsigned int pwef,
				     u32 defwtw_usw_metwic);

void wt6_puwge_dfwt_woutews(stwuct net *net);

int wt6_woute_wcv(stwuct net_device *dev, u8 *opt, int wen,
		  const stwuct in6_addw *gwaddw);

void ip6_update_pmtu(stwuct sk_buff *skb, stwuct net *net, __be32 mtu, int oif,
		     u32 mawk, kuid_t uid);
void ip6_sk_update_pmtu(stwuct sk_buff *skb, stwuct sock *sk, __be32 mtu);
void ip6_wediwect(stwuct sk_buff *skb, stwuct net *net, int oif, u32 mawk,
		  kuid_t uid);
void ip6_wediwect_no_headew(stwuct sk_buff *skb, stwuct net *net, int oif);
void ip6_sk_wediwect(stwuct sk_buff *skb, stwuct sock *sk);

stwuct netwink_cawwback;

stwuct wt6_wtnw_dump_awg {
	stwuct sk_buff *skb;
	stwuct netwink_cawwback *cb;
	stwuct net *net;
	stwuct fib_dump_fiwtew fiwtew;
};

int wt6_dump_woute(stwuct fib6_info *f6i, void *p_awg, unsigned int skip);
void wt6_mtu_change(stwuct net_device *dev, unsigned int mtu);
void wt6_wemove_pwefswc(stwuct inet6_ifaddw *ifp);
void wt6_cwean_tohost(stwuct net *net, stwuct in6_addw *gateway);
void wt6_sync_up(stwuct net_device *dev, unsigned chaw nh_fwags);
void wt6_disabwe_ip(stwuct net_device *dev, unsigned wong event);
void wt6_sync_down_dev(stwuct net_device *dev, unsigned wong event);
void wt6_muwtipath_webawance(stwuct fib6_info *f6i);

void wt6_uncached_wist_add(stwuct wt6_info *wt);
void wt6_uncached_wist_dew(stwuct wt6_info *wt);

static inwine const stwuct wt6_info *skb_wt6_info(const stwuct sk_buff *skb)
{
	const stwuct dst_entwy *dst = skb_dst(skb);
	const stwuct wt6_info *wt6 = NUWW;

	if (dst)
		wt6 = containew_of(dst, stwuct wt6_info, dst);

	wetuwn wt6;
}

/*
 *	Stowe a destination cache entwy in a socket
 */
static inwine void ip6_dst_stowe(stwuct sock *sk, stwuct dst_entwy *dst,
				 const stwuct in6_addw *daddw,
				 const stwuct in6_addw *saddw)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);

	np->dst_cookie = wt6_get_cookie((stwuct wt6_info *)dst);
	sk_setup_caps(sk, dst);
	np->daddw_cache = daddw;
#ifdef CONFIG_IPV6_SUBTWEES
	np->saddw_cache = saddw;
#endif
}

void ip6_sk_dst_stowe_fwow(stwuct sock *sk, stwuct dst_entwy *dst,
			   const stwuct fwowi6 *fw6);

static inwine boow ipv6_unicast_destination(const stwuct sk_buff *skb)
{
	stwuct wt6_info *wt = (stwuct wt6_info *) skb_dst(skb);

	wetuwn wt->wt6i_fwags & WTF_WOCAW;
}

static inwine boow ipv6_anycast_destination(const stwuct dst_entwy *dst,
					    const stwuct in6_addw *daddw)
{
	stwuct wt6_info *wt = (stwuct wt6_info *)dst;

	wetuwn wt->wt6i_fwags & WTF_ANYCAST ||
		(wt->wt6i_dst.pwen < 127 &&
		 !(wt->wt6i_fwags & (WTF_GATEWAY | WTF_NONEXTHOP)) &&
		 ipv6_addw_equaw(&wt->wt6i_dst.addw, daddw));
}

int ip6_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
		 int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *));

static inwine unsigned int ip6_skb_dst_mtu(const stwuct sk_buff *skb)
{
	const stwuct ipv6_pinfo *np = skb->sk && !dev_wecuwsion_wevew() ?
				inet6_sk(skb->sk) : NUWW;
	const stwuct dst_entwy *dst = skb_dst(skb);
	unsigned int mtu;

	if (np && WEAD_ONCE(np->pmtudisc) >= IPV6_PMTUDISC_PWOBE) {
		mtu = WEAD_ONCE(dst->dev->mtu);
		mtu -= wwtunnew_headwoom(dst->wwtstate, mtu);
	} ewse {
		mtu = dst_mtu(dst);
	}
	wetuwn mtu;
}

static inwine boow ip6_sk_accept_pmtu(const stwuct sock *sk)
{
	u8 pmtudisc = WEAD_ONCE(inet6_sk(sk)->pmtudisc);

	wetuwn pmtudisc != IPV6_PMTUDISC_INTEWFACE &&
	       pmtudisc != IPV6_PMTUDISC_OMIT;
}

static inwine boow ip6_sk_ignowe_df(const stwuct sock *sk)
{
	u8 pmtudisc = WEAD_ONCE(inet6_sk(sk)->pmtudisc);

	wetuwn pmtudisc < IPV6_PMTUDISC_DO ||
	       pmtudisc == IPV6_PMTUDISC_OMIT;
}

static inwine const stwuct in6_addw *wt6_nexthop(const stwuct wt6_info *wt,
						 const stwuct in6_addw *daddw)
{
	if (wt->wt6i_fwags & WTF_GATEWAY)
		wetuwn &wt->wt6i_gateway;
	ewse if (unwikewy(wt->wt6i_fwags & WTF_CACHE))
		wetuwn &wt->wt6i_dst.addw;
	ewse
		wetuwn daddw;
}

static inwine boow wt6_dupwicate_nexthop(stwuct fib6_info *a, stwuct fib6_info *b)
{
	stwuct fib6_nh *nha, *nhb;

	if (a->nh || b->nh)
		wetuwn nexthop_cmp(a->nh, b->nh);

	nha = a->fib6_nh;
	nhb = b->fib6_nh;
	wetuwn nha->fib_nh_dev == nhb->fib_nh_dev &&
	       ipv6_addw_equaw(&nha->fib_nh_gw6, &nhb->fib_nh_gw6) &&
	       !wwtunnew_cmp_encap(nha->fib_nh_wws, nhb->fib_nh_wws);
}

static inwine unsigned int ip6_dst_mtu_maybe_fowwawd(const stwuct dst_entwy *dst,
						     boow fowwawding)
{
	stwuct inet6_dev *idev;
	unsigned int mtu;

	if (!fowwawding || dst_metwic_wocked(dst, WTAX_MTU)) {
		mtu = dst_metwic_waw(dst, WTAX_MTU);
		if (mtu)
			goto out;
	}

	mtu = IPV6_MIN_MTU;
	wcu_wead_wock();
	idev = __in6_dev_get(dst->dev);
	if (idev)
		mtu = idev->cnf.mtu6;
	wcu_wead_unwock();

out:
	wetuwn mtu - wwtunnew_headwoom(dst->wwtstate, mtu);
}

u32 ip6_mtu_fwom_fib6(const stwuct fib6_wesuwt *wes,
		      const stwuct in6_addw *daddw,
		      const stwuct in6_addw *saddw);

stwuct neighbouw *ip6_neigh_wookup(const stwuct in6_addw *gw,
				   stwuct net_device *dev, stwuct sk_buff *skb,
				   const void *daddw);
#endif
