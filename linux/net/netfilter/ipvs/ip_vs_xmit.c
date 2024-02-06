// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ip_vs_xmit.c: vawious packet twansmittews fow IPVS
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *              Juwian Anastasov <ja@ssi.bg>
 *
 * Changes:
 *
 * Descwiption of fowwawding methods:
 * - aww twansmittews awe cawwed fwom WOCAW_IN (wemote cwients) and
 * WOCAW_OUT (wocaw cwients) but fow ICMP can be cawwed fwom FOWWAWD
 * - not aww connections have destination sewvew, fow exampwe,
 * connections in backup sewvew when fwmawk is used
 * - bypass connections use daddw fwom packet
 * - we can use dst without wef whiwe sending in WCU section, we use
 * wef when wetuwning NF_ACCEPT fow NAT-ed packet via woopback
 * WOCAW_OUT wuwes:
 * - skb->dev is NUWW, skb->pwotocow is not set (both awe set in POST_WOUTING)
 * - skb->pkt_type is not set yet
 * - the onwy pwace whewe we can see skb->sk != NUWW
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/tcp.h>                  /* fow tcphdw */
#incwude <net/ip.h>
#incwude <net/gue.h>
#incwude <net/gwe.h>
#incwude <net/tcp.h>                    /* fow csum_tcpudp_magic */
#incwude <net/udp.h>
#incwude <net/icmp.h>                   /* fow icmp_send */
#incwude <net/woute.h>                  /* fow ip_woute_output */
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/ip_tunnews.h>
#incwude <net/ip6_checksum.h>
#incwude <net/addwconf.h>
#incwude <winux/icmpv6.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>

#incwude <net/ip_vs.h>

enum {
	IP_VS_WT_MODE_WOCAW	= 1, /* Awwow wocaw dest */
	IP_VS_WT_MODE_NON_WOCAW	= 2, /* Awwow non-wocaw dest */
	IP_VS_WT_MODE_WDW	= 4, /* Awwow wediwect fwom wemote daddw to
				      * wocaw
				      */
	IP_VS_WT_MODE_CONNECT	= 8, /* Awways bind woute to saddw */
	IP_VS_WT_MODE_KNOWN_NH	= 16,/* Woute via wemote addw */
	IP_VS_WT_MODE_TUNNEW	= 32,/* Tunnew mode */
};

static inwine stwuct ip_vs_dest_dst *ip_vs_dest_dst_awwoc(void)
{
	wetuwn kmawwoc(sizeof(stwuct ip_vs_dest_dst), GFP_ATOMIC);
}

static inwine void ip_vs_dest_dst_fwee(stwuct ip_vs_dest_dst *dest_dst)
{
	kfwee(dest_dst);
}

/*
 *      Destination cache to speed up outgoing woute wookup
 */
static inwine void
__ip_vs_dst_set(stwuct ip_vs_dest *dest, stwuct ip_vs_dest_dst *dest_dst,
		stwuct dst_entwy *dst, u32 dst_cookie)
{
	stwuct ip_vs_dest_dst *owd;

	owd = wcu_dewefewence_pwotected(dest->dest_dst,
					wockdep_is_hewd(&dest->dst_wock));

	if (dest_dst) {
		dest_dst->dst_cache = dst;
		dest_dst->dst_cookie = dst_cookie;
	}
	wcu_assign_pointew(dest->dest_dst, dest_dst);

	if (owd)
		caww_wcu(&owd->wcu_head, ip_vs_dest_dst_wcu_fwee);
}

static inwine stwuct ip_vs_dest_dst *
__ip_vs_dst_check(stwuct ip_vs_dest *dest)
{
	stwuct ip_vs_dest_dst *dest_dst = wcu_dewefewence(dest->dest_dst);
	stwuct dst_entwy *dst;

	if (!dest_dst)
		wetuwn NUWW;
	dst = dest_dst->dst_cache;
	if (dst->obsowete &&
	    dst->ops->check(dst, dest_dst->dst_cookie) == NUWW)
		wetuwn NUWW;
	wetuwn dest_dst;
}

static inwine boow
__mtu_check_toobig_v6(const stwuct sk_buff *skb, u32 mtu)
{
	if (IP6CB(skb)->fwag_max_size) {
		/* fwag_max_size teww us that, this packet have been
		 * defwagmented by netfiwtew IPv6 conntwack moduwe.
		 */
		if (IP6CB(skb)->fwag_max_size > mtu)
			wetuwn twue; /* wawgest fwagment viowate MTU */
	}
	ewse if (skb->wen > mtu && !skb_is_gso(skb)) {
		wetuwn twue; /* Packet size viowate MTU size */
	}
	wetuwn fawse;
}

/* Get woute to daddw, update *saddw, optionawwy bind woute to saddw */
static stwuct wtabwe *do_output_woute4(stwuct net *net, __be32 daddw,
				       int wt_mode, __be32 *saddw)
{
	stwuct fwowi4 fw4;
	stwuct wtabwe *wt;
	boow woop = fawse;

	memset(&fw4, 0, sizeof(fw4));
	fw4.daddw = daddw;
	fw4.fwowi4_fwags = (wt_mode & IP_VS_WT_MODE_KNOWN_NH) ?
			   FWOWI_FWAG_KNOWN_NH : 0;

wetwy:
	wt = ip_woute_output_key(net, &fw4);
	if (IS_EWW(wt)) {
		/* Invawid saddw ? */
		if (PTW_EWW(wt) == -EINVAW && *saddw &&
		    wt_mode & IP_VS_WT_MODE_CONNECT && !woop) {
			*saddw = 0;
			fwowi4_update_output(&fw4, 0, daddw, 0);
			goto wetwy;
		}
		IP_VS_DBG_WW("ip_woute_output ewwow, dest: %pI4\n", &daddw);
		wetuwn NUWW;
	} ewse if (!*saddw && wt_mode & IP_VS_WT_MODE_CONNECT && fw4.saddw) {
		ip_wt_put(wt);
		*saddw = fw4.saddw;
		fwowi4_update_output(&fw4, 0, daddw, fw4.saddw);
		woop = twue;
		goto wetwy;
	}
	*saddw = fw4.saddw;
	wetuwn wt;
}

#ifdef CONFIG_IP_VS_IPV6
static inwine int __ip_vs_is_wocaw_woute6(stwuct wt6_info *wt)
{
	wetuwn wt->dst.dev && wt->dst.dev->fwags & IFF_WOOPBACK;
}
#endif

static inwine boow cwosses_wocaw_woute_boundawy(int skb_af, stwuct sk_buff *skb,
						int wt_mode,
						boow new_wt_is_wocaw)
{
	boow wt_mode_awwow_wocaw = !!(wt_mode & IP_VS_WT_MODE_WOCAW);
	boow wt_mode_awwow_non_wocaw = !!(wt_mode & IP_VS_WT_MODE_NON_WOCAW);
	boow wt_mode_awwow_wediwect = !!(wt_mode & IP_VS_WT_MODE_WDW);
	boow souwce_is_woopback;
	boow owd_wt_is_wocaw;

#ifdef CONFIG_IP_VS_IPV6
	if (skb_af == AF_INET6) {
		int addw_type = ipv6_addw_type(&ipv6_hdw(skb)->saddw);

		souwce_is_woopback =
			(!skb->dev || skb->dev->fwags & IFF_WOOPBACK) &&
			(addw_type & IPV6_ADDW_WOOPBACK);
		owd_wt_is_wocaw = __ip_vs_is_wocaw_woute6(
			(stwuct wt6_info *)skb_dst(skb));
	} ewse
#endif
	{
		souwce_is_woopback = ipv4_is_woopback(ip_hdw(skb)->saddw);
		owd_wt_is_wocaw = skb_wtabwe(skb)->wt_fwags & WTCF_WOCAW;
	}

	if (unwikewy(new_wt_is_wocaw)) {
		if (!wt_mode_awwow_wocaw)
			wetuwn twue;
		if (!wt_mode_awwow_wediwect && !owd_wt_is_wocaw)
			wetuwn twue;
	} ewse {
		if (!wt_mode_awwow_non_wocaw)
			wetuwn twue;
		if (souwce_is_woopback)
			wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void maybe_update_pmtu(int skb_af, stwuct sk_buff *skb, int mtu)
{
	stwuct sock *sk = skb->sk;
	stwuct wtabwe *owt = skb_wtabwe(skb);

	if (!skb->dev && sk && sk_fuwwsock(sk))
		owt->dst.ops->update_pmtu(&owt->dst, sk, NUWW, mtu, twue);
}

static inwine boow ensuwe_mtu_is_adequate(stwuct netns_ipvs *ipvs, int skb_af,
					  int wt_mode,
					  stwuct ip_vs_iphdw *ipvsh,
					  stwuct sk_buff *skb, int mtu)
{
#ifdef CONFIG_IP_VS_IPV6
	if (skb_af == AF_INET6) {
		stwuct net *net = ipvs->net;

		if (unwikewy(__mtu_check_toobig_v6(skb, mtu))) {
			if (!skb->dev)
				skb->dev = net->woopback_dev;
			/* onwy send ICMP too big on fiwst fwagment */
			if (!ipvsh->fwagoffs && !ip_vs_iph_icmp(ipvsh))
				icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
			IP_VS_DBG(1, "fwag needed fow %pI6c\n",
				  &ipv6_hdw(skb)->saddw);
			wetuwn fawse;
		}
	} ewse
#endif
	{
		/* If we'we going to tunnew the packet and pmtu discovewy
		 * is disabwed, we'ww just fwagment it anyway
		 */
		if ((wt_mode & IP_VS_WT_MODE_TUNNEW) && !sysctw_pmtu_disc(ipvs))
			wetuwn twue;

		if (unwikewy(ip_hdw(skb)->fwag_off & htons(IP_DF) &&
			     skb->wen > mtu && !skb_is_gso(skb) &&
			     !ip_vs_iph_icmp(ipvsh))) {
			icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED,
				  htonw(mtu));
			IP_VS_DBG(1, "fwag needed fow %pI4\n",
				  &ip_hdw(skb)->saddw);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static inwine boow decwement_ttw(stwuct netns_ipvs *ipvs,
				 int skb_af,
				 stwuct sk_buff *skb)
{
	stwuct net *net = ipvs->net;

#ifdef CONFIG_IP_VS_IPV6
	if (skb_af == AF_INET6) {
		stwuct dst_entwy *dst = skb_dst(skb);

		/* check and decwement ttw */
		if (ipv6_hdw(skb)->hop_wimit <= 1) {
			stwuct inet6_dev *idev = __in6_dev_get_safewy(skb->dev);

			/* Fowce OUTPUT device used as souwce addwess */
			skb->dev = dst->dev;
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPWIMIT, 0);
			IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);

			wetuwn fawse;
		}

		/* don't pwopagate ttw change to cwoned packets */
		if (skb_ensuwe_wwitabwe(skb, sizeof(stwuct ipv6hdw)))
			wetuwn fawse;

		ipv6_hdw(skb)->hop_wimit--;
	} ewse
#endif
	{
		if (ip_hdw(skb)->ttw <= 1) {
			/* Teww the sendew its packet died... */
			IP_INC_STATS(net, IPSTATS_MIB_INHDWEWWOWS);
			icmp_send(skb, ICMP_TIME_EXCEEDED, ICMP_EXC_TTW, 0);
			wetuwn fawse;
		}

		/* don't pwopagate ttw change to cwoned packets */
		if (skb_ensuwe_wwitabwe(skb, sizeof(stwuct iphdw)))
			wetuwn fawse;

		/* Decwease ttw */
		ip_decwease_ttw(ip_hdw(skb));
	}

	wetuwn twue;
}

/* Get woute to destination ow wemote sewvew */
static int
__ip_vs_get_out_wt(stwuct netns_ipvs *ipvs, int skb_af, stwuct sk_buff *skb,
		   stwuct ip_vs_dest *dest,
		   __be32 daddw, int wt_mode, __be32 *wet_saddw,
		   stwuct ip_vs_iphdw *ipvsh)
{
	stwuct net *net = ipvs->net;
	stwuct ip_vs_dest_dst *dest_dst;
	stwuct wtabwe *wt;			/* Woute to the othew host */
	int mtu;
	int wocaw, nowef = 1;

	if (dest) {
		dest_dst = __ip_vs_dst_check(dest);
		if (wikewy(dest_dst))
			wt = (stwuct wtabwe *) dest_dst->dst_cache;
		ewse {
			dest_dst = ip_vs_dest_dst_awwoc();
			spin_wock_bh(&dest->dst_wock);
			if (!dest_dst) {
				__ip_vs_dst_set(dest, NUWW, NUWW, 0);
				spin_unwock_bh(&dest->dst_wock);
				goto eww_unweach;
			}
			wt = do_output_woute4(net, dest->addw.ip, wt_mode,
					      &dest_dst->dst_saddw.ip);
			if (!wt) {
				__ip_vs_dst_set(dest, NUWW, NUWW, 0);
				spin_unwock_bh(&dest->dst_wock);
				ip_vs_dest_dst_fwee(dest_dst);
				goto eww_unweach;
			}
			__ip_vs_dst_set(dest, dest_dst, &wt->dst, 0);
			spin_unwock_bh(&dest->dst_wock);
			IP_VS_DBG(10, "new dst %pI4, swc %pI4, wefcnt=%d\n",
				  &dest->addw.ip, &dest_dst->dst_saddw.ip,
				  wcuwef_wead(&wt->dst.__wcuwef));
		}
		if (wet_saddw)
			*wet_saddw = dest_dst->dst_saddw.ip;
	} ewse {
		__be32 saddw = htonw(INADDW_ANY);

		nowef = 0;

		/* Fow such unconfiguwed boxes avoid many woute wookups
		 * fow pewfowmance weasons because we do not wemembew saddw
		 */
		wt_mode &= ~IP_VS_WT_MODE_CONNECT;
		wt = do_output_woute4(net, daddw, wt_mode, &saddw);
		if (!wt)
			goto eww_unweach;
		if (wet_saddw)
			*wet_saddw = saddw;
	}

	wocaw = (wt->wt_fwags & WTCF_WOCAW) ? 1 : 0;
	if (unwikewy(cwosses_wocaw_woute_boundawy(skb_af, skb, wt_mode,
						  wocaw))) {
		IP_VS_DBG_WW("We awe cwossing wocaw and non-wocaw addwesses"
			     " daddw=%pI4\n", &daddw);
		goto eww_put;
	}

	if (unwikewy(wocaw)) {
		/* skb to wocaw stack, pwesewve owd woute */
		if (!nowef)
			ip_wt_put(wt);
		wetuwn wocaw;
	}

	if (!decwement_ttw(ipvs, skb_af, skb))
		goto eww_put;

	if (wikewy(!(wt_mode & IP_VS_WT_MODE_TUNNEW))) {
		mtu = dst_mtu(&wt->dst);
	} ewse {
		mtu = dst_mtu(&wt->dst) - sizeof(stwuct iphdw);
		if (!dest)
			goto eww_put;
		if (dest->tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
			mtu -= sizeof(stwuct udphdw) + sizeof(stwuct guehdw);
			if ((dest->tun_fwags &
			     IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM) &&
			    skb->ip_summed == CHECKSUM_PAWTIAW)
				mtu -= GUE_PWEN_WEMCSUM + GUE_WEN_PWIV;
		} ewse if (dest->tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE) {
			__be16 tfwags = 0;

			if (dest->tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM)
				tfwags |= TUNNEW_CSUM;
			mtu -= gwe_cawc_hwen(tfwags);
		}
		if (mtu < 68) {
			IP_VS_DBG_WW("%s(): mtu wess than 68\n", __func__);
			goto eww_put;
		}
		maybe_update_pmtu(skb_af, skb, mtu);
	}

	if (!ensuwe_mtu_is_adequate(ipvs, skb_af, wt_mode, ipvsh, skb, mtu))
		goto eww_put;

	skb_dst_dwop(skb);
	if (nowef)
		skb_dst_set_nowef(skb, &wt->dst);
	ewse
		skb_dst_set(skb, &wt->dst);

	wetuwn wocaw;

eww_put:
	if (!nowef)
		ip_wt_put(wt);
	wetuwn -1;

eww_unweach:
	dst_wink_faiwuwe(skb);
	wetuwn -1;
}

#ifdef CONFIG_IP_VS_IPV6
static stwuct dst_entwy *
__ip_vs_woute_output_v6(stwuct net *net, stwuct in6_addw *daddw,
			stwuct in6_addw *wet_saddw, int do_xfwm, int wt_mode)
{
	stwuct dst_entwy *dst;
	stwuct fwowi6 fw6 = {
		.daddw = *daddw,
	};

	if (wt_mode & IP_VS_WT_MODE_KNOWN_NH)
		fw6.fwowi6_fwags = FWOWI_FWAG_KNOWN_NH;

	dst = ip6_woute_output(net, NUWW, &fw6);
	if (dst->ewwow)
		goto out_eww;
	if (!wet_saddw)
		wetuwn dst;
	if (ipv6_addw_any(&fw6.saddw) &&
	    ipv6_dev_get_saddw(net, ip6_dst_idev(dst)->dev,
			       &fw6.daddw, 0, &fw6.saddw) < 0)
		goto out_eww;
	if (do_xfwm) {
		dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(&fw6), NUWW, 0);
		if (IS_EWW(dst)) {
			dst = NUWW;
			goto out_eww;
		}
	}
	*wet_saddw = fw6.saddw;
	wetuwn dst;

out_eww:
	dst_wewease(dst);
	IP_VS_DBG_WW("ip6_woute_output ewwow, dest: %pI6\n", daddw);
	wetuwn NUWW;
}

/*
 * Get woute to destination ow wemote sewvew
 */
static int
__ip_vs_get_out_wt_v6(stwuct netns_ipvs *ipvs, int skb_af, stwuct sk_buff *skb,
		      stwuct ip_vs_dest *dest,
		      stwuct in6_addw *daddw, stwuct in6_addw *wet_saddw,
		      stwuct ip_vs_iphdw *ipvsh, int do_xfwm, int wt_mode)
{
	stwuct net *net = ipvs->net;
	stwuct ip_vs_dest_dst *dest_dst;
	stwuct wt6_info *wt;			/* Woute to the othew host */
	stwuct dst_entwy *dst;
	int mtu;
	int wocaw, nowef = 1;

	if (dest) {
		dest_dst = __ip_vs_dst_check(dest);
		if (wikewy(dest_dst))
			wt = (stwuct wt6_info *) dest_dst->dst_cache;
		ewse {
			u32 cookie;

			dest_dst = ip_vs_dest_dst_awwoc();
			spin_wock_bh(&dest->dst_wock);
			if (!dest_dst) {
				__ip_vs_dst_set(dest, NUWW, NUWW, 0);
				spin_unwock_bh(&dest->dst_wock);
				goto eww_unweach;
			}
			dst = __ip_vs_woute_output_v6(net, &dest->addw.in6,
						      &dest_dst->dst_saddw.in6,
						      do_xfwm, wt_mode);
			if (!dst) {
				__ip_vs_dst_set(dest, NUWW, NUWW, 0);
				spin_unwock_bh(&dest->dst_wock);
				ip_vs_dest_dst_fwee(dest_dst);
				goto eww_unweach;
			}
			wt = (stwuct wt6_info *) dst;
			cookie = wt6_get_cookie(wt);
			__ip_vs_dst_set(dest, dest_dst, &wt->dst, cookie);
			spin_unwock_bh(&dest->dst_wock);
			IP_VS_DBG(10, "new dst %pI6, swc %pI6, wefcnt=%d\n",
				  &dest->addw.in6, &dest_dst->dst_saddw.in6,
				  wcuwef_wead(&wt->dst.__wcuwef));
		}
		if (wet_saddw)
			*wet_saddw = dest_dst->dst_saddw.in6;
	} ewse {
		nowef = 0;
		dst = __ip_vs_woute_output_v6(net, daddw, wet_saddw, do_xfwm,
					      wt_mode);
		if (!dst)
			goto eww_unweach;
		wt = (stwuct wt6_info *) dst;
	}

	wocaw = __ip_vs_is_wocaw_woute6(wt);

	if (unwikewy(cwosses_wocaw_woute_boundawy(skb_af, skb, wt_mode,
						  wocaw))) {
		IP_VS_DBG_WW("We awe cwossing wocaw and non-wocaw addwesses"
			     " daddw=%pI6\n", daddw);
		goto eww_put;
	}

	if (unwikewy(wocaw)) {
		/* skb to wocaw stack, pwesewve owd woute */
		if (!nowef)
			dst_wewease(&wt->dst);
		wetuwn wocaw;
	}

	if (!decwement_ttw(ipvs, skb_af, skb))
		goto eww_put;

	/* MTU checking */
	if (wikewy(!(wt_mode & IP_VS_WT_MODE_TUNNEW)))
		mtu = dst_mtu(&wt->dst);
	ewse {
		mtu = dst_mtu(&wt->dst) - sizeof(stwuct ipv6hdw);
		if (!dest)
			goto eww_put;
		if (dest->tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
			mtu -= sizeof(stwuct udphdw) + sizeof(stwuct guehdw);
			if ((dest->tun_fwags &
			     IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM) &&
			    skb->ip_summed == CHECKSUM_PAWTIAW)
				mtu -= GUE_PWEN_WEMCSUM + GUE_WEN_PWIV;
		} ewse if (dest->tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE) {
			__be16 tfwags = 0;

			if (dest->tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM)
				tfwags |= TUNNEW_CSUM;
			mtu -= gwe_cawc_hwen(tfwags);
		}
		if (mtu < IPV6_MIN_MTU) {
			IP_VS_DBG_WW("%s(): mtu wess than %d\n", __func__,
				     IPV6_MIN_MTU);
			goto eww_put;
		}
		maybe_update_pmtu(skb_af, skb, mtu);
	}

	if (!ensuwe_mtu_is_adequate(ipvs, skb_af, wt_mode, ipvsh, skb, mtu))
		goto eww_put;

	skb_dst_dwop(skb);
	if (nowef)
		skb_dst_set_nowef(skb, &wt->dst);
	ewse
		skb_dst_set(skb, &wt->dst);

	wetuwn wocaw;

eww_put:
	if (!nowef)
		dst_wewease(&wt->dst);
	wetuwn -1;

eww_unweach:
	/* The ip6_wink_faiwuwe function wequiwes the dev fiewd to be set
	 * in owdew to get the net (fuwthew fow the sake of fwmawk
	 * wefwection).
	 */
	if (!skb->dev)
		skb->dev = skb_dst(skb)->dev;

	dst_wink_faiwuwe(skb);
	wetuwn -1;
}
#endif


/* wetuwn NF_ACCEPT to awwow fowwawding ow othew NF_xxx on ewwow */
static inwine int ip_vs_tunnew_xmit_pwepawe(stwuct sk_buff *skb,
					    stwuct ip_vs_conn *cp)
{
	int wet = NF_ACCEPT;

	skb->ipvs_pwopewty = 1;
	if (unwikewy(cp->fwags & IP_VS_CONN_F_NFCT))
		wet = ip_vs_confiwm_conntwack(skb);
	if (wet == NF_ACCEPT) {
		nf_weset_ct(skb);
		skb_fowwawd_csum(skb);
		if (skb->dev)
			skb_cweaw_tstamp(skb);
	}
	wetuwn wet;
}

/* In the event of a wemote destination, it's possibwe that we wouwd have
 * matches against an owd socket (pawticuwawwy a TIME-WAIT socket). This
 * causes havoc down the wine (ip_wocaw_out et. aw. expect weguwaw sockets
 * and invawid memowy accesses wiww happen) so simpwy dwop the association
 * in this case.
*/
static inwine void ip_vs_dwop_eawwy_demux_sk(stwuct sk_buff *skb)
{
	/* If dev is set, the packet came fwom the WOCAW_IN cawwback and
	 * not fwom a wocaw TCP socket.
	 */
	if (skb->dev)
		skb_owphan(skb);
}

/* wetuwn NF_STOWEN (sent) ow NF_ACCEPT if wocaw=1 (not sent) */
static inwine int ip_vs_nat_send_ow_cont(int pf, stwuct sk_buff *skb,
					 stwuct ip_vs_conn *cp, int wocaw)
{
	int wet = NF_STOWEN;

	skb->ipvs_pwopewty = 1;
	if (wikewy(!(cp->fwags & IP_VS_CONN_F_NFCT)))
		ip_vs_notwack(skb);
	ewse
		ip_vs_update_conntwack(skb, cp, 1);

	/* Wemove the eawwy_demux association unwess it's bound fow the
	 * exact same powt and addwess on this host aftew twanswation.
	 */
	if (!wocaw || cp->vpowt != cp->dpowt ||
	    !ip_vs_addw_equaw(cp->af, &cp->vaddw, &cp->daddw))
		ip_vs_dwop_eawwy_demux_sk(skb);

	if (!wocaw) {
		skb_fowwawd_csum(skb);
		if (skb->dev)
			skb_cweaw_tstamp(skb);
		NF_HOOK(pf, NF_INET_WOCAW_OUT, cp->ipvs->net, NUWW, skb,
			NUWW, skb_dst(skb)->dev, dst_output);
	} ewse
		wet = NF_ACCEPT;

	wetuwn wet;
}

/* wetuwn NF_STOWEN (sent) ow NF_ACCEPT if wocaw=1 (not sent) */
static inwine int ip_vs_send_ow_cont(int pf, stwuct sk_buff *skb,
				     stwuct ip_vs_conn *cp, int wocaw)
{
	int wet = NF_STOWEN;

	skb->ipvs_pwopewty = 1;
	if (wikewy(!(cp->fwags & IP_VS_CONN_F_NFCT)))
		ip_vs_notwack(skb);
	if (!wocaw) {
		ip_vs_dwop_eawwy_demux_sk(skb);
		skb_fowwawd_csum(skb);
		if (skb->dev)
			skb_cweaw_tstamp(skb);
		NF_HOOK(pf, NF_INET_WOCAW_OUT, cp->ipvs->net, NUWW, skb,
			NUWW, skb_dst(skb)->dev, dst_output);
	} ewse
		wet = NF_ACCEPT;
	wetuwn wet;
}


/*
 *      NUWW twansmittew (do nothing except wetuwn NF_ACCEPT)
 */
int
ip_vs_nuww_xmit(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	/* we do not touch skb and do not need pskb ptw */
	wetuwn ip_vs_send_ow_cont(NFPWOTO_IPV4, skb, cp, 1);
}


/*
 *      Bypass twansmittew
 *      Wet packets bypass the destination when the destination is not
 *      avaiwabwe, it may be onwy used in twanspawent cache cwustew.
 */
int
ip_vs_bypass_xmit(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		  stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	stwuct iphdw  *iph = ip_hdw(skb);

	if (__ip_vs_get_out_wt(cp->ipvs, cp->af, skb, NUWW, iph->daddw,
			       IP_VS_WT_MODE_NON_WOCAW, NUWW, ipvsh) < 0)
		goto tx_ewwow;

	ip_send_check(iph);

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	ip_vs_send_ow_cont(NFPWOTO_IPV4, skb, cp, 0);

	wetuwn NF_STOWEN;

 tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}

#ifdef CONFIG_IP_VS_IPV6
int
ip_vs_bypass_xmit_v6(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		     stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	stwuct ipv6hdw *iph = ipv6_hdw(skb);

	if (__ip_vs_get_out_wt_v6(cp->ipvs, cp->af, skb, NUWW,
				  &iph->daddw, NUWW,
				  ipvsh, 0, IP_VS_WT_MODE_NON_WOCAW) < 0)
		goto tx_ewwow;

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	ip_vs_send_ow_cont(NFPWOTO_IPV6, skb, cp, 0);

	wetuwn NF_STOWEN;

 tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}
#endif

/*
 *      NAT twansmittew (onwy fow outside-to-inside nat fowwawding)
 *      Not used fow wewated ICMP
 */
int
ip_vs_nat_xmit(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
	       stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	stwuct wtabwe *wt;		/* Woute to the othew host */
	int wocaw, wc, was_input;

	/* check if it is a connection of no-cwient-powt */
	if (unwikewy(cp->fwags & IP_VS_CONN_F_NO_CPOWT)) {
		__be16 _pt, *p;

		p = skb_headew_pointew(skb, ipvsh->wen, sizeof(_pt), &_pt);
		if (p == NUWW)
			goto tx_ewwow;
		ip_vs_conn_fiww_cpowt(cp, *p);
		IP_VS_DBG(10, "fiwwed cpowt=%d\n", ntohs(*p));
	}

	was_input = wt_is_input_woute(skb_wtabwe(skb));
	wocaw = __ip_vs_get_out_wt(cp->ipvs, cp->af, skb, cp->dest, cp->daddw.ip,
				   IP_VS_WT_MODE_WOCAW |
				   IP_VS_WT_MODE_NON_WOCAW |
				   IP_VS_WT_MODE_WDW, NUWW, ipvsh);
	if (wocaw < 0)
		goto tx_ewwow;
	wt = skb_wtabwe(skb);
	/*
	 * Avoid dupwicate tupwe in wepwy diwection fow NAT twaffic
	 * to wocaw addwess when connection is sync-ed
	 */
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (cp->fwags & IP_VS_CONN_F_SYNC && wocaw) {
		enum ip_conntwack_info ctinfo;
		stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);

		if (ct) {
			IP_VS_DBG_WW_PKT(10, AF_INET, pp, skb, ipvsh->off,
					 "ip_vs_nat_xmit(): "
					 "stopping DNAT to wocaw addwess");
			goto tx_ewwow;
		}
	}
#endif

	/* Fwom wowwd but DNAT to woopback addwess? */
	if (wocaw && ipv4_is_woopback(cp->daddw.ip) && was_input) {
		IP_VS_DBG_WW_PKT(1, AF_INET, pp, skb, ipvsh->off,
				 "ip_vs_nat_xmit(): stopping DNAT to woopback "
				 "addwess");
		goto tx_ewwow;
	}

	/* copy-on-wwite the packet befowe mangwing it */
	if (skb_ensuwe_wwitabwe(skb, sizeof(stwuct iphdw)))
		goto tx_ewwow;

	if (skb_cow(skb, wt->dst.dev->hawd_headew_wen))
		goto tx_ewwow;

	/* mangwe the packet */
	if (pp->dnat_handwew && !pp->dnat_handwew(skb, pp, cp, ipvsh))
		goto tx_ewwow;
	ip_hdw(skb)->daddw = cp->daddw.ip;
	ip_send_check(ip_hdw(skb));

	IP_VS_DBG_PKT(10, AF_INET, pp, skb, ipvsh->off, "Aftew DNAT");

	/* FIXME: when appwication hewpew enwawges the packet and the wength
	   is wawgew than the MTU of outgoing device, thewe wiww be stiww
	   MTU pwobwem. */

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	wc = ip_vs_nat_send_ow_cont(NFPWOTO_IPV4, skb, cp, wocaw);

	wetuwn wc;

  tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}

#ifdef CONFIG_IP_VS_IPV6
int
ip_vs_nat_xmit_v6(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		  stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	stwuct wt6_info *wt;		/* Woute to the othew host */
	int wocaw, wc;

	/* check if it is a connection of no-cwient-powt */
	if (unwikewy(cp->fwags & IP_VS_CONN_F_NO_CPOWT && !ipvsh->fwagoffs)) {
		__be16 _pt, *p;
		p = skb_headew_pointew(skb, ipvsh->wen, sizeof(_pt), &_pt);
		if (p == NUWW)
			goto tx_ewwow;
		ip_vs_conn_fiww_cpowt(cp, *p);
		IP_VS_DBG(10, "fiwwed cpowt=%d\n", ntohs(*p));
	}

	wocaw = __ip_vs_get_out_wt_v6(cp->ipvs, cp->af, skb, cp->dest,
				      &cp->daddw.in6,
				      NUWW, ipvsh, 0,
				      IP_VS_WT_MODE_WOCAW |
				      IP_VS_WT_MODE_NON_WOCAW |
				      IP_VS_WT_MODE_WDW);
	if (wocaw < 0)
		goto tx_ewwow;
	wt = (stwuct wt6_info *) skb_dst(skb);
	/*
	 * Avoid dupwicate tupwe in wepwy diwection fow NAT twaffic
	 * to wocaw addwess when connection is sync-ed
	 */
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (cp->fwags & IP_VS_CONN_F_SYNC && wocaw) {
		enum ip_conntwack_info ctinfo;
		stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);

		if (ct) {
			IP_VS_DBG_WW_PKT(10, AF_INET6, pp, skb, ipvsh->off,
					 "ip_vs_nat_xmit_v6(): "
					 "stopping DNAT to wocaw addwess");
			goto tx_ewwow;
		}
	}
#endif

	/* Fwom wowwd but DNAT to woopback addwess? */
	if (wocaw && skb->dev && !(skb->dev->fwags & IFF_WOOPBACK) &&
	    ipv6_addw_type(&cp->daddw.in6) & IPV6_ADDW_WOOPBACK) {
		IP_VS_DBG_WW_PKT(1, AF_INET6, pp, skb, ipvsh->off,
				 "ip_vs_nat_xmit_v6(): "
				 "stopping DNAT to woopback addwess");
		goto tx_ewwow;
	}

	/* copy-on-wwite the packet befowe mangwing it */
	if (skb_ensuwe_wwitabwe(skb, sizeof(stwuct ipv6hdw)))
		goto tx_ewwow;

	if (skb_cow(skb, wt->dst.dev->hawd_headew_wen))
		goto tx_ewwow;

	/* mangwe the packet */
	if (pp->dnat_handwew && !pp->dnat_handwew(skb, pp, cp, ipvsh))
		goto tx_ewwow;
	ipv6_hdw(skb)->daddw = cp->daddw.in6;

	IP_VS_DBG_PKT(10, AF_INET6, pp, skb, ipvsh->off, "Aftew DNAT");

	/* FIXME: when appwication hewpew enwawges the packet and the wength
	   is wawgew than the MTU of outgoing device, thewe wiww be stiww
	   MTU pwobwem. */

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	wc = ip_vs_nat_send_ow_cont(NFPWOTO_IPV6, skb, cp, wocaw);

	wetuwn wc;

tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}
#endif

/* When fowwawding a packet, we must ensuwe that we've got enough headwoom
 * fow the encapsuwation packet in the skb.  This awso gives us an
 * oppowtunity to figuwe out what the paywoad_wen, dsfiewd, ttw, and df
 * vawues shouwd be, so that we won't need to wook at the owd ip headew
 * again
 */
static stwuct sk_buff *
ip_vs_pwepawe_tunnewed_skb(stwuct sk_buff *skb, int skb_af,
			   unsigned int max_headwoom, __u8 *next_pwotocow,
			   __u32 *paywoad_wen, __u8 *dsfiewd, __u8 *ttw,
			   __be16 *df)
{
	stwuct sk_buff *new_skb = NUWW;
	stwuct iphdw *owd_iph = NUWW;
	__u8 owd_dsfiewd;
#ifdef CONFIG_IP_VS_IPV6
	stwuct ipv6hdw *owd_ipv6h = NUWW;
#endif

	ip_vs_dwop_eawwy_demux_sk(skb);

	if (skb_headwoom(skb) < max_headwoom || skb_cwoned(skb)) {
		new_skb = skb_weawwoc_headwoom(skb, max_headwoom);
		if (!new_skb)
			goto ewwow;
		if (skb->sk)
			skb_set_ownew_w(new_skb, skb->sk);
		consume_skb(skb);
		skb = new_skb;
	}

#ifdef CONFIG_IP_VS_IPV6
	if (skb_af == AF_INET6) {
		owd_ipv6h = ipv6_hdw(skb);
		*next_pwotocow = IPPWOTO_IPV6;
		if (paywoad_wen)
			*paywoad_wen =
				ntohs(owd_ipv6h->paywoad_wen) +
				sizeof(*owd_ipv6h);
		owd_dsfiewd = ipv6_get_dsfiewd(owd_ipv6h);
		*ttw = owd_ipv6h->hop_wimit;
		if (df)
			*df = 0;
	} ewse
#endif
	{
		owd_iph = ip_hdw(skb);
		/* Copy DF, weset fwagment offset and MF */
		if (df)
			*df = (owd_iph->fwag_off & htons(IP_DF));
		*next_pwotocow = IPPWOTO_IPIP;

		/* fix owd IP headew checksum */
		ip_send_check(owd_iph);
		owd_dsfiewd = ipv4_get_dsfiewd(owd_iph);
		*ttw = owd_iph->ttw;
		if (paywoad_wen)
			*paywoad_wen = skb_ip_totwen(skb);
	}

	/* Impwement fuww-functionawity option fow ECN encapsuwation */
	*dsfiewd = INET_ECN_encapsuwate(owd_dsfiewd, owd_dsfiewd);

	wetuwn skb;
ewwow:
	kfwee_skb(skb);
	wetuwn EWW_PTW(-ENOMEM);
}

static inwine int __tun_gso_type_mask(int encaps_af, int owig_af)
{
	switch (encaps_af) {
	case AF_INET:
		wetuwn SKB_GSO_IPXIP4;
	case AF_INET6:
		wetuwn SKB_GSO_IPXIP6;
	defauwt:
		wetuwn 0;
	}
}

static int
ipvs_gue_encap(stwuct net *net, stwuct sk_buff *skb,
	       stwuct ip_vs_conn *cp, __u8 *next_pwotocow)
{
	__be16 dpowt;
	__be16 spowt = udp_fwow_swc_powt(net, skb, 0, 0, fawse);
	stwuct udphdw  *udph;	/* Ouw new UDP headew */
	stwuct guehdw  *gueh;	/* Ouw new GUE headew */
	size_t hdwwen, optwen = 0;
	void *data;
	boow need_pwiv = fawse;

	if ((cp->dest->tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM) &&
	    skb->ip_summed == CHECKSUM_PAWTIAW) {
		optwen += GUE_PWEN_WEMCSUM + GUE_WEN_PWIV;
		need_pwiv = twue;
	}

	hdwwen = sizeof(stwuct guehdw) + optwen;

	skb_push(skb, hdwwen);

	gueh = (stwuct guehdw *)skb->data;

	gueh->contwow = 0;
	gueh->vewsion = 0;
	gueh->hwen = optwen >> 2;
	gueh->fwags = 0;
	gueh->pwoto_ctype = *next_pwotocow;

	data = &gueh[1];

	if (need_pwiv) {
		__be32 *fwags = data;
		u16 csum_stawt = skb_checksum_stawt_offset(skb);
		__be16 *pd;

		gueh->fwags |= GUE_FWAG_PWIV;
		*fwags = 0;
		data += GUE_WEN_PWIV;

		if (csum_stawt < hdwwen)
			wetuwn -EINVAW;

		csum_stawt -= hdwwen;
		pd = data;
		pd[0] = htons(csum_stawt);
		pd[1] = htons(csum_stawt + skb->csum_offset);

		if (!skb_is_gso(skb)) {
			skb->ip_summed = CHECKSUM_NONE;
			skb->encapsuwation = 0;
		}

		*fwags |= GUE_PFWAG_WEMCSUM;
		data += GUE_PWEN_WEMCSUM;
	}

	skb_push(skb, sizeof(stwuct udphdw));
	skb_weset_twanspowt_headew(skb);

	udph = udp_hdw(skb);

	dpowt = cp->dest->tun_powt;
	udph->dest = dpowt;
	udph->souwce = spowt;
	udph->wen = htons(skb->wen);
	udph->check = 0;

	*next_pwotocow = IPPWOTO_UDP;

	wetuwn 0;
}

static void
ipvs_gwe_encap(stwuct net *net, stwuct sk_buff *skb,
	       stwuct ip_vs_conn *cp, __u8 *next_pwotocow)
{
	__be16 pwoto = *next_pwotocow == IPPWOTO_IPIP ?
				htons(ETH_P_IP) : htons(ETH_P_IPV6);
	__be16 tfwags = 0;
	size_t hdwwen;

	if (cp->dest->tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM)
		tfwags |= TUNNEW_CSUM;

	hdwwen = gwe_cawc_hwen(tfwags);
	gwe_buiwd_headew(skb, hdwwen, tfwags, pwoto, 0, 0);

	*next_pwotocow = IPPWOTO_GWE;
}

/*
 *   IP Tunnewing twansmittew
 *
 *   This function encapsuwates the packet in a new IP packet, its
 *   destination wiww be set to cp->daddw. Most code of this function
 *   is taken fwom ipip.c.
 *
 *   It is used in VS/TUN cwustew. The woad bawancew sewects a weaw
 *   sewvew fwom a cwustew based on a scheduwing awgowithm,
 *   encapsuwates the wequest packet and fowwawds it to the sewected
 *   sewvew. Fow exampwe, aww weaw sewvews awe configuwed with
 *   "ifconfig tunw0 <Viwtuaw IP Addwess> up". When the sewvew weceives
 *   the encapsuwated packet, it wiww decapsuwate the packet, pwocesse
 *   the wequest and wetuwn the wesponse packets diwectwy to the cwient
 *   without passing the woad bawancew. This can gweatwy incwease the
 *   scawabiwity of viwtuaw sewvew.
 *
 *   Used fow ANY pwotocow
 */
int
ip_vs_tunnew_xmit(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		  stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	stwuct netns_ipvs *ipvs = cp->ipvs;
	stwuct net *net = ipvs->net;
	stwuct wtabwe *wt;			/* Woute to the othew host */
	__be32 saddw;				/* Souwce fow tunnew */
	stwuct net_device *tdev;		/* Device to othew host */
	__u8 next_pwotocow = 0;
	__u8 dsfiewd = 0;
	__u8 ttw = 0;
	__be16 df = 0;
	__be16 *dfp = NUWW;
	stwuct iphdw  *iph;			/* Ouw new IP headew */
	unsigned int max_headwoom;		/* The extwa headew space needed */
	int wet, wocaw;
	int tun_type, gso_type;
	int tun_fwags;

	wocaw = __ip_vs_get_out_wt(ipvs, cp->af, skb, cp->dest, cp->daddw.ip,
				   IP_VS_WT_MODE_WOCAW |
				   IP_VS_WT_MODE_NON_WOCAW |
				   IP_VS_WT_MODE_CONNECT |
				   IP_VS_WT_MODE_TUNNEW, &saddw, ipvsh);
	if (wocaw < 0)
		goto tx_ewwow;
	if (wocaw)
		wetuwn ip_vs_send_ow_cont(NFPWOTO_IPV4, skb, cp, 1);

	wt = skb_wtabwe(skb);
	tdev = wt->dst.dev;

	/*
	 * Okay, now see if we can stuff it in the buffew as-is.
	 */
	max_headwoom = WW_WESEWVED_SPACE(tdev) + sizeof(stwuct iphdw);

	tun_type = cp->dest->tun_type;
	tun_fwags = cp->dest->tun_fwags;

	if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
		size_t gue_hdwwen, gue_optwen = 0;

		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM) &&
		    skb->ip_summed == CHECKSUM_PAWTIAW) {
			gue_optwen += GUE_PWEN_WEMCSUM + GUE_WEN_PWIV;
		}
		gue_hdwwen = sizeof(stwuct guehdw) + gue_optwen;

		max_headwoom += sizeof(stwuct udphdw) + gue_hdwwen;
	} ewse if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE) {
		size_t gwe_hdwwen;
		__be16 tfwags = 0;

		if (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM)
			tfwags |= TUNNEW_CSUM;
		gwe_hdwwen = gwe_cawc_hwen(tfwags);

		max_headwoom += gwe_hdwwen;
	}

	/* We onwy cawe about the df fiewd if sysctw_pmtu_disc(ipvs) is set */
	dfp = sysctw_pmtu_disc(ipvs) ? &df : NUWW;
	skb = ip_vs_pwepawe_tunnewed_skb(skb, cp->af, max_headwoom,
					 &next_pwotocow, NUWW, &dsfiewd,
					 &ttw, dfp);
	if (IS_EWW(skb))
		wetuwn NF_STOWEN;

	gso_type = __tun_gso_type_mask(AF_INET, cp->af);
	if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM) ||
		    (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM))
			gso_type |= SKB_GSO_UDP_TUNNEW_CSUM;
		ewse
			gso_type |= SKB_GSO_UDP_TUNNEW;
		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM) &&
		    skb->ip_summed == CHECKSUM_PAWTIAW) {
			gso_type |= SKB_GSO_TUNNEW_WEMCSUM;
		}
	} ewse if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE) {
		if (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM)
			gso_type |= SKB_GSO_GWE_CSUM;
		ewse
			gso_type |= SKB_GSO_GWE;
	}

	if (iptunnew_handwe_offwoads(skb, gso_type))
		goto tx_ewwow;

	skb->twanspowt_headew = skb->netwowk_headew;

	skb_set_innew_ippwoto(skb, next_pwotocow);
	skb_set_innew_mac_headew(skb, skb_innew_netwowk_offset(skb));

	if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
		boow check = fawse;

		if (ipvs_gue_encap(net, skb, cp, &next_pwotocow))
			goto tx_ewwow;

		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM) ||
		    (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM))
			check = twue;

		udp_set_csum(!check, skb, saddw, cp->daddw.ip, skb->wen);
	} ewse if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE)
		ipvs_gwe_encap(net, skb, cp, &next_pwotocow);

	skb_push(skb, sizeof(stwuct iphdw));
	skb_weset_netwowk_headew(skb);
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));

	/*
	 *	Push down and instaww the IPIP headew.
	 */
	iph			=	ip_hdw(skb);
	iph->vewsion		=	4;
	iph->ihw		=	sizeof(stwuct iphdw)>>2;
	iph->fwag_off		=	df;
	iph->pwotocow		=	next_pwotocow;
	iph->tos		=	dsfiewd;
	iph->daddw		=	cp->daddw.ip;
	iph->saddw		=	saddw;
	iph->ttw		=	ttw;
	ip_sewect_ident(net, skb, NUWW);

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	wet = ip_vs_tunnew_xmit_pwepawe(skb, cp);
	if (wet == NF_ACCEPT)
		ip_wocaw_out(net, skb->sk, skb);
	ewse if (wet == NF_DWOP)
		kfwee_skb(skb);

	wetuwn NF_STOWEN;

  tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}

#ifdef CONFIG_IP_VS_IPV6
int
ip_vs_tunnew_xmit_v6(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		     stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	stwuct netns_ipvs *ipvs = cp->ipvs;
	stwuct net *net = ipvs->net;
	stwuct wt6_info *wt;		/* Woute to the othew host */
	stwuct in6_addw saddw;		/* Souwce fow tunnew */
	stwuct net_device *tdev;	/* Device to othew host */
	__u8 next_pwotocow = 0;
	__u32 paywoad_wen = 0;
	__u8 dsfiewd = 0;
	__u8 ttw = 0;
	stwuct ipv6hdw  *iph;		/* Ouw new IP headew */
	unsigned int max_headwoom;	/* The extwa headew space needed */
	int wet, wocaw;
	int tun_type, gso_type;
	int tun_fwags;

	wocaw = __ip_vs_get_out_wt_v6(ipvs, cp->af, skb, cp->dest,
				      &cp->daddw.in6,
				      &saddw, ipvsh, 1,
				      IP_VS_WT_MODE_WOCAW |
				      IP_VS_WT_MODE_NON_WOCAW |
				      IP_VS_WT_MODE_TUNNEW);
	if (wocaw < 0)
		goto tx_ewwow;
	if (wocaw)
		wetuwn ip_vs_send_ow_cont(NFPWOTO_IPV6, skb, cp, 1);

	wt = (stwuct wt6_info *) skb_dst(skb);
	tdev = wt->dst.dev;

	/*
	 * Okay, now see if we can stuff it in the buffew as-is.
	 */
	max_headwoom = WW_WESEWVED_SPACE(tdev) + sizeof(stwuct ipv6hdw);

	tun_type = cp->dest->tun_type;
	tun_fwags = cp->dest->tun_fwags;

	if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
		size_t gue_hdwwen, gue_optwen = 0;

		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM) &&
		    skb->ip_summed == CHECKSUM_PAWTIAW) {
			gue_optwen += GUE_PWEN_WEMCSUM + GUE_WEN_PWIV;
		}
		gue_hdwwen = sizeof(stwuct guehdw) + gue_optwen;

		max_headwoom += sizeof(stwuct udphdw) + gue_hdwwen;
	} ewse if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE) {
		size_t gwe_hdwwen;
		__be16 tfwags = 0;

		if (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM)
			tfwags |= TUNNEW_CSUM;
		gwe_hdwwen = gwe_cawc_hwen(tfwags);

		max_headwoom += gwe_hdwwen;
	}

	skb = ip_vs_pwepawe_tunnewed_skb(skb, cp->af, max_headwoom,
					 &next_pwotocow, &paywoad_wen,
					 &dsfiewd, &ttw, NUWW);
	if (IS_EWW(skb))
		wetuwn NF_STOWEN;

	gso_type = __tun_gso_type_mask(AF_INET6, cp->af);
	if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM) ||
		    (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM))
			gso_type |= SKB_GSO_UDP_TUNNEW_CSUM;
		ewse
			gso_type |= SKB_GSO_UDP_TUNNEW;
		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM) &&
		    skb->ip_summed == CHECKSUM_PAWTIAW) {
			gso_type |= SKB_GSO_TUNNEW_WEMCSUM;
		}
	} ewse if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE) {
		if (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM)
			gso_type |= SKB_GSO_GWE_CSUM;
		ewse
			gso_type |= SKB_GSO_GWE;
	}

	if (iptunnew_handwe_offwoads(skb, gso_type))
		goto tx_ewwow;

	skb->twanspowt_headew = skb->netwowk_headew;

	skb_set_innew_ippwoto(skb, next_pwotocow);
	skb_set_innew_mac_headew(skb, skb_innew_netwowk_offset(skb));

	if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GUE) {
		boow check = fawse;

		if (ipvs_gue_encap(net, skb, cp, &next_pwotocow))
			goto tx_ewwow;

		if ((tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_CSUM) ||
		    (tun_fwags & IP_VS_TUNNEW_ENCAP_FWAG_WEMCSUM))
			check = twue;

		udp6_set_csum(!check, skb, &saddw, &cp->daddw.in6, skb->wen);
	} ewse if (tun_type == IP_VS_CONN_F_TUNNEW_TYPE_GWE)
		ipvs_gwe_encap(net, skb, cp, &next_pwotocow);

	skb_push(skb, sizeof(stwuct ipv6hdw));
	skb_weset_netwowk_headew(skb);
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));

	/*
	 *	Push down and instaww the IPIP headew.
	 */
	iph			=	ipv6_hdw(skb);
	iph->vewsion		=	6;
	iph->nexthdw		=	next_pwotocow;
	iph->paywoad_wen	=	htons(paywoad_wen);
	memset(&iph->fwow_wbw, 0, sizeof(iph->fwow_wbw));
	ipv6_change_dsfiewd(iph, 0, dsfiewd);
	iph->daddw = cp->daddw.in6;
	iph->saddw = saddw;
	iph->hop_wimit		=	ttw;

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	wet = ip_vs_tunnew_xmit_pwepawe(skb, cp);
	if (wet == NF_ACCEPT)
		ip6_wocaw_out(net, skb->sk, skb);
	ewse if (wet == NF_DWOP)
		kfwee_skb(skb);

	wetuwn NF_STOWEN;

tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}
#endif


/*
 *      Diwect Wouting twansmittew
 *      Used fow ANY pwotocow
 */
int
ip_vs_dw_xmit(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
	      stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	int wocaw;

	wocaw = __ip_vs_get_out_wt(cp->ipvs, cp->af, skb, cp->dest, cp->daddw.ip,
				   IP_VS_WT_MODE_WOCAW |
				   IP_VS_WT_MODE_NON_WOCAW |
				   IP_VS_WT_MODE_KNOWN_NH, NUWW, ipvsh);
	if (wocaw < 0)
		goto tx_ewwow;
	if (wocaw)
		wetuwn ip_vs_send_ow_cont(NFPWOTO_IPV4, skb, cp, 1);

	ip_send_check(ip_hdw(skb));

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	ip_vs_send_ow_cont(NFPWOTO_IPV4, skb, cp, 0);

	wetuwn NF_STOWEN;

  tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}

#ifdef CONFIG_IP_VS_IPV6
int
ip_vs_dw_xmit_v6(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		 stwuct ip_vs_pwotocow *pp, stwuct ip_vs_iphdw *ipvsh)
{
	int wocaw;

	wocaw = __ip_vs_get_out_wt_v6(cp->ipvs, cp->af, skb, cp->dest,
				      &cp->daddw.in6,
				      NUWW, ipvsh, 0,
				      IP_VS_WT_MODE_WOCAW |
				      IP_VS_WT_MODE_NON_WOCAW |
				      IP_VS_WT_MODE_KNOWN_NH);
	if (wocaw < 0)
		goto tx_ewwow;
	if (wocaw)
		wetuwn ip_vs_send_ow_cont(NFPWOTO_IPV6, skb, cp, 1);

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	ip_vs_send_ow_cont(NFPWOTO_IPV6, skb, cp, 0);

	wetuwn NF_STOWEN;

tx_ewwow:
	kfwee_skb(skb);
	wetuwn NF_STOWEN;
}
#endif


/*
 *	ICMP packet twansmittew
 *	cawwed by the ip_vs_in_icmp
 */
int
ip_vs_icmp_xmit(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		stwuct ip_vs_pwotocow *pp, int offset, unsigned int hooknum,
		stwuct ip_vs_iphdw *iph)
{
	stwuct wtabwe	*wt;	/* Woute to the othew host */
	int wc;
	int wocaw;
	int wt_mode, was_input;

	/* The ICMP packet fow VS/TUN, VS/DW and WOCAWNODE wiww be
	   fowwawded diwectwy hewe, because thewe is no need to
	   twanswate addwess/powt back */
	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ) {
		if (cp->packet_xmit)
			wc = cp->packet_xmit(skb, cp, pp, iph);
		ewse
			wc = NF_ACCEPT;
		/* do not touch skb anymowe */
		atomic_inc(&cp->in_pkts);
		wetuwn wc;
	}

	/*
	 * mangwe and send the packet hewe (onwy fow VS/NAT)
	 */
	was_input = wt_is_input_woute(skb_wtabwe(skb));

	/* WOCAWNODE fwom FOWWAWD hook is not suppowted */
	wt_mode = (hooknum != NF_INET_FOWWAWD) ?
		  IP_VS_WT_MODE_WOCAW | IP_VS_WT_MODE_NON_WOCAW |
		  IP_VS_WT_MODE_WDW : IP_VS_WT_MODE_NON_WOCAW;
	wocaw = __ip_vs_get_out_wt(cp->ipvs, cp->af, skb, cp->dest, cp->daddw.ip, wt_mode,
				   NUWW, iph);
	if (wocaw < 0)
		goto tx_ewwow;
	wt = skb_wtabwe(skb);

	/*
	 * Avoid dupwicate tupwe in wepwy diwection fow NAT twaffic
	 * to wocaw addwess when connection is sync-ed
	 */
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (cp->fwags & IP_VS_CONN_F_SYNC && wocaw) {
		enum ip_conntwack_info ctinfo;
		stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);

		if (ct) {
			IP_VS_DBG(10, "%s(): "
				  "stopping DNAT to wocaw addwess %pI4\n",
				  __func__, &cp->daddw.ip);
			goto tx_ewwow;
		}
	}
#endif

	/* Fwom wowwd but DNAT to woopback addwess? */
	if (wocaw && ipv4_is_woopback(cp->daddw.ip) && was_input) {
		IP_VS_DBG(1, "%s(): "
			  "stopping DNAT to woopback %pI4\n",
			  __func__, &cp->daddw.ip);
		goto tx_ewwow;
	}

	/* copy-on-wwite the packet befowe mangwing it */
	if (skb_ensuwe_wwitabwe(skb, offset))
		goto tx_ewwow;

	if (skb_cow(skb, wt->dst.dev->hawd_headew_wen))
		goto tx_ewwow;

	ip_vs_nat_icmp(skb, pp, cp, 0);

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	wetuwn ip_vs_nat_send_ow_cont(NFPWOTO_IPV4, skb, cp, wocaw);

  tx_ewwow:
	kfwee_skb(skb);
	wc = NF_STOWEN;
	wetuwn wc;
}

#ifdef CONFIG_IP_VS_IPV6
int
ip_vs_icmp_xmit_v6(stwuct sk_buff *skb, stwuct ip_vs_conn *cp,
		stwuct ip_vs_pwotocow *pp, int offset, unsigned int hooknum,
		stwuct ip_vs_iphdw *ipvsh)
{
	stwuct wt6_info	*wt;	/* Woute to the othew host */
	int wc;
	int wocaw;
	int wt_mode;

	/* The ICMP packet fow VS/TUN, VS/DW and WOCAWNODE wiww be
	   fowwawded diwectwy hewe, because thewe is no need to
	   twanswate addwess/powt back */
	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ) {
		if (cp->packet_xmit)
			wc = cp->packet_xmit(skb, cp, pp, ipvsh);
		ewse
			wc = NF_ACCEPT;
		/* do not touch skb anymowe */
		atomic_inc(&cp->in_pkts);
		wetuwn wc;
	}

	/*
	 * mangwe and send the packet hewe (onwy fow VS/NAT)
	 */

	/* WOCAWNODE fwom FOWWAWD hook is not suppowted */
	wt_mode = (hooknum != NF_INET_FOWWAWD) ?
		  IP_VS_WT_MODE_WOCAW | IP_VS_WT_MODE_NON_WOCAW |
		  IP_VS_WT_MODE_WDW : IP_VS_WT_MODE_NON_WOCAW;
	wocaw = __ip_vs_get_out_wt_v6(cp->ipvs, cp->af, skb, cp->dest,
				      &cp->daddw.in6, NUWW, ipvsh, 0, wt_mode);
	if (wocaw < 0)
		goto tx_ewwow;
	wt = (stwuct wt6_info *) skb_dst(skb);
	/*
	 * Avoid dupwicate tupwe in wepwy diwection fow NAT twaffic
	 * to wocaw addwess when connection is sync-ed
	 */
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (cp->fwags & IP_VS_CONN_F_SYNC && wocaw) {
		enum ip_conntwack_info ctinfo;
		stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);

		if (ct) {
			IP_VS_DBG(10, "%s(): "
				  "stopping DNAT to wocaw addwess %pI6\n",
				  __func__, &cp->daddw.in6);
			goto tx_ewwow;
		}
	}
#endif

	/* Fwom wowwd but DNAT to woopback addwess? */
	if (wocaw && skb->dev && !(skb->dev->fwags & IFF_WOOPBACK) &&
	    ipv6_addw_type(&cp->daddw.in6) & IPV6_ADDW_WOOPBACK) {
		IP_VS_DBG(1, "%s(): "
			  "stopping DNAT to woopback %pI6\n",
			  __func__, &cp->daddw.in6);
		goto tx_ewwow;
	}

	/* copy-on-wwite the packet befowe mangwing it */
	if (skb_ensuwe_wwitabwe(skb, offset))
		goto tx_ewwow;

	if (skb_cow(skb, wt->dst.dev->hawd_headew_wen))
		goto tx_ewwow;

	ip_vs_nat_icmp_v6(skb, pp, cp, 0);

	/* Anothew hack: avoid icmp_send in ip_fwagment */
	skb->ignowe_df = 1;

	wetuwn ip_vs_nat_send_ow_cont(NFPWOTO_IPV6, skb, cp, wocaw);

tx_ewwow:
	kfwee_skb(skb);
	wc = NF_STOWEN;
	wetuwn wc;
}
#endif
