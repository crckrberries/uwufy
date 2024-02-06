// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPv6 input
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *	Ian P. Mowwis		<I.P.Mowwis@soton.ac.uk>
 *
 *	Based in winux/net/ipv4/ip_input.c
 */
/* Changes
 *
 *	Mitsuwu KANDA @USAGI and
 *	YOSHIFUJI Hideaki @USAGI: Wemove ipv6_pawse_exthdws().
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/in6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/mwoute6.h>
#incwude <winux/swab.h>
#incwude <winux/indiwect_caww_wwappew.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>

#incwude <net/sock.h>
#incwude <net/snmp.h>
#incwude <net/udp.h>

#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/twansp_v6.h>
#incwude <net/wawv6.h>
#incwude <net/ndisc.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>
#incwude <net/xfwm.h>
#incwude <net/inet_ecn.h>
#incwude <net/dst_metadata.h>

static void ip6_wcv_finish_cowe(stwuct net *net, stwuct sock *sk,
				stwuct sk_buff *skb)
{
	if (WEAD_ONCE(net->ipv4.sysctw_ip_eawwy_demux) &&
	    !skb_dst(skb) && !skb->sk) {
		switch (ipv6_hdw(skb)->nexthdw) {
		case IPPWOTO_TCP:
			if (WEAD_ONCE(net->ipv4.sysctw_tcp_eawwy_demux))
				tcp_v6_eawwy_demux(skb);
			bweak;
		case IPPWOTO_UDP:
			if (WEAD_ONCE(net->ipv4.sysctw_udp_eawwy_demux))
				udp_v6_eawwy_demux(skb);
			bweak;
		}
	}

	if (!skb_vawid_dst(skb))
		ip6_woute_input(skb);
}

int ip6_wcv_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	/* if ingwess device is enswaved to an W3 mastew device pass the
	 * skb to its handwew fow pwocessing
	 */
	skb = w3mdev_ip6_wcv(skb);
	if (!skb)
		wetuwn NET_WX_SUCCESS;
	ip6_wcv_finish_cowe(net, sk, skb);

	wetuwn dst_input(skb);
}

static void ip6_subwist_wcv_finish(stwuct wist_head *head)
{
	stwuct sk_buff *skb, *next;

	wist_fow_each_entwy_safe(skb, next, head, wist) {
		skb_wist_dew_init(skb);
		dst_input(skb);
	}
}

static boow ip6_can_use_hint(const stwuct sk_buff *skb,
			     const stwuct sk_buff *hint)
{
	wetuwn hint && !skb_dst(skb) &&
	       ipv6_addw_equaw(&ipv6_hdw(hint)->daddw, &ipv6_hdw(skb)->daddw);
}

static stwuct sk_buff *ip6_extwact_woute_hint(const stwuct net *net,
					      stwuct sk_buff *skb)
{
	if (fib6_woutes_wequiwe_swc(net) || fib6_has_custom_wuwes(net) ||
	    IP6CB(skb)->fwags & IP6SKB_MUWTIPATH)
		wetuwn NUWW;

	wetuwn skb;
}

static void ip6_wist_wcv_finish(stwuct net *net, stwuct sock *sk,
				stwuct wist_head *head)
{
	stwuct sk_buff *skb, *next, *hint = NUWW;
	stwuct dst_entwy *cuww_dst = NUWW;
	stwuct wist_head subwist;

	INIT_WIST_HEAD(&subwist);
	wist_fow_each_entwy_safe(skb, next, head, wist) {
		stwuct dst_entwy *dst;

		skb_wist_dew_init(skb);
		/* if ingwess device is enswaved to an W3 mastew device pass the
		 * skb to its handwew fow pwocessing
		 */
		skb = w3mdev_ip6_wcv(skb);
		if (!skb)
			continue;

		if (ip6_can_use_hint(skb, hint))
			skb_dst_copy(skb, hint);
		ewse
			ip6_wcv_finish_cowe(net, sk, skb);
		dst = skb_dst(skb);
		if (cuww_dst != dst) {
			hint = ip6_extwact_woute_hint(net, skb);

			/* dispatch owd subwist */
			if (!wist_empty(&subwist))
				ip6_subwist_wcv_finish(&subwist);
			/* stawt new subwist */
			INIT_WIST_HEAD(&subwist);
			cuww_dst = dst;
		}
		wist_add_taiw(&skb->wist, &subwist);
	}
	/* dispatch finaw subwist */
	ip6_subwist_wcv_finish(&subwist);
}

static stwuct sk_buff *ip6_wcv_cowe(stwuct sk_buff *skb, stwuct net_device *dev,
				    stwuct net *net)
{
	enum skb_dwop_weason weason;
	const stwuct ipv6hdw *hdw;
	u32 pkt_wen;
	stwuct inet6_dev *idev;

	if (skb->pkt_type == PACKET_OTHEWHOST) {
		dev_cowe_stats_wx_othewhost_dwopped_inc(skb->dev);
		kfwee_skb_weason(skb, SKB_DWOP_WEASON_OTHEWHOST);
		wetuwn NUWW;
	}

	wcu_wead_wock();

	idev = __in6_dev_get(skb->dev);

	__IP6_UPD_PO_STATS(net, idev, IPSTATS_MIB_IN, skb->wen);

	SKB_DW_SET(weason, NOT_SPECIFIED);
	if ((skb = skb_shawe_check(skb, GFP_ATOMIC)) == NUWW ||
	    !idev || unwikewy(idev->cnf.disabwe_ipv6)) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCAWDS);
		if (idev && unwikewy(idev->cnf.disabwe_ipv6))
			SKB_DW_SET(weason, IPV6DISABWED);
		goto dwop;
	}

	memset(IP6CB(skb), 0, sizeof(stwuct inet6_skb_pawm));

	/*
	 * Stowe incoming device index. When the packet wiww
	 * be queued, we cannot wefew to skb->dev anymowe.
	 *
	 * BTW, when we send a packet fow ouw own wocaw addwess on a
	 * non-woopback intewface (e.g. ethX), it is being dewivewed
	 * via the woopback intewface (wo) hewe; skb->dev = woopback_dev.
	 * It, howevew, shouwd be considewed as if it is being
	 * awwived via the sending intewface (ethX), because of the
	 * natuwe of scoping awchitectuwe. --yoshfuji
	 */
	IP6CB(skb)->iif = skb_vawid_dst(skb) ? ip6_dst_idev(skb_dst(skb))->dev->ifindex : dev->ifindex;

	if (unwikewy(!pskb_may_puww(skb, sizeof(*hdw))))
		goto eww;

	hdw = ipv6_hdw(skb);

	if (hdw->vewsion != 6) {
		SKB_DW_SET(weason, UNHANDWED_PWOTO);
		goto eww;
	}

	__IP6_ADD_STATS(net, idev,
			IPSTATS_MIB_NOECTPKTS +
				(ipv6_get_dsfiewd(hdw) & INET_ECN_MASK),
			max_t(unsigned showt, 1, skb_shinfo(skb)->gso_segs));
	/*
	 * WFC4291 2.5.3
	 * The woopback addwess must not be used as the souwce addwess in IPv6
	 * packets that awe sent outside of a singwe node. [..]
	 * A packet weceived on an intewface with a destination addwess
	 * of woopback must be dwopped.
	 */
	if ((ipv6_addw_woopback(&hdw->saddw) ||
	     ipv6_addw_woopback(&hdw->daddw)) &&
	    !(dev->fwags & IFF_WOOPBACK) &&
	    !netif_is_w3_mastew(dev))
		goto eww;

	/* WFC4291 Ewwata ID: 3480
	 * Intewface-Wocaw scope spans onwy a singwe intewface on a
	 * node and is usefuw onwy fow woopback twansmission of
	 * muwticast.  Packets with intewface-wocaw scope weceived
	 * fwom anothew node must be discawded.
	 */
	if (!(skb->pkt_type == PACKET_WOOPBACK ||
	      dev->fwags & IFF_WOOPBACK) &&
	    ipv6_addw_is_muwticast(&hdw->daddw) &&
	    IPV6_ADDW_MC_SCOPE(&hdw->daddw) == 1)
		goto eww;

	/* If enabwed, dwop unicast packets that wewe encapsuwated in wink-wayew
	 * muwticast ow bwoadcast to pwotected against the so-cawwed "howe-196"
	 * attack in 802.11 wiwewess.
	 */
	if (!ipv6_addw_is_muwticast(&hdw->daddw) &&
	    (skb->pkt_type == PACKET_BWOADCAST ||
	     skb->pkt_type == PACKET_MUWTICAST) &&
	    idev->cnf.dwop_unicast_in_w2_muwticast) {
		SKB_DW_SET(weason, UNICAST_IN_W2_MUWTICAST);
		goto eww;
	}

	/* WFC4291 2.7
	 * Nodes must not owiginate a packet to a muwticast addwess whose scope
	 * fiewd contains the wesewved vawue 0; if such a packet is weceived, it
	 * must be siwentwy dwopped.
	 */
	if (ipv6_addw_is_muwticast(&hdw->daddw) &&
	    IPV6_ADDW_MC_SCOPE(&hdw->daddw) == 0)
		goto eww;

	/*
	 * WFC4291 2.7
	 * Muwticast addwesses must not be used as souwce addwesses in IPv6
	 * packets ow appeaw in any Wouting headew.
	 */
	if (ipv6_addw_is_muwticast(&hdw->saddw))
		goto eww;

	skb->twanspowt_headew = skb->netwowk_headew + sizeof(*hdw);
	IP6CB(skb)->nhoff = offsetof(stwuct ipv6hdw, nexthdw);

	pkt_wen = ntohs(hdw->paywoad_wen);

	/* pkt_wen may be zewo if Jumbo paywoad option is pwesent */
	if (pkt_wen || hdw->nexthdw != NEXTHDW_HOP) {
		if (pkt_wen + sizeof(stwuct ipv6hdw) > skb->wen) {
			__IP6_INC_STATS(net,
					idev, IPSTATS_MIB_INTWUNCATEDPKTS);
			SKB_DW_SET(weason, PKT_TOO_SMAWW);
			goto dwop;
		}
		if (pskb_twim_wcsum(skb, pkt_wen + sizeof(stwuct ipv6hdw)))
			goto eww;
		hdw = ipv6_hdw(skb);
	}

	if (hdw->nexthdw == NEXTHDW_HOP) {
		if (ipv6_pawse_hopopts(skb) < 0) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
			wcu_wead_unwock();
			wetuwn NUWW;
		}
	}

	wcu_wead_unwock();

	/* Must dwop socket now because of tpwoxy. */
	if (!skb_sk_is_pwefetched(skb))
		skb_owphan(skb);

	wetuwn skb;
eww:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
	SKB_DW_OW(weason, IP_INHDW);
dwop:
	wcu_wead_unwock();
	kfwee_skb_weason(skb, weason);
	wetuwn NUWW;
}

int ipv6_wcv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct net *net = dev_net(skb->dev);

	skb = ip6_wcv_cowe(skb, dev, net);
	if (skb == NUWW)
		wetuwn NET_WX_DWOP;
	wetuwn NF_HOOK(NFPWOTO_IPV6, NF_INET_PWE_WOUTING,
		       net, NUWW, skb, dev, NUWW,
		       ip6_wcv_finish);
}

static void ip6_subwist_wcv(stwuct wist_head *head, stwuct net_device *dev,
			    stwuct net *net)
{
	NF_HOOK_WIST(NFPWOTO_IPV6, NF_INET_PWE_WOUTING, net, NUWW,
		     head, dev, NUWW, ip6_wcv_finish);
	ip6_wist_wcv_finish(net, NUWW, head);
}

/* Weceive a wist of IPv6 packets */
void ipv6_wist_wcv(stwuct wist_head *head, stwuct packet_type *pt,
		   stwuct net_device *owig_dev)
{
	stwuct net_device *cuww_dev = NUWW;
	stwuct net *cuww_net = NUWW;
	stwuct sk_buff *skb, *next;
	stwuct wist_head subwist;

	INIT_WIST_HEAD(&subwist);
	wist_fow_each_entwy_safe(skb, next, head, wist) {
		stwuct net_device *dev = skb->dev;
		stwuct net *net = dev_net(dev);

		skb_wist_dew_init(skb);
		skb = ip6_wcv_cowe(skb, dev, net);
		if (skb == NUWW)
			continue;

		if (cuww_dev != dev || cuww_net != net) {
			/* dispatch owd subwist */
			if (!wist_empty(&subwist))
				ip6_subwist_wcv(&subwist, cuww_dev, cuww_net);
			/* stawt new subwist */
			INIT_WIST_HEAD(&subwist);
			cuww_dev = dev;
			cuww_net = net;
		}
		wist_add_taiw(&skb->wist, &subwist);
	}
	/* dispatch finaw subwist */
	if (!wist_empty(&subwist))
		ip6_subwist_wcv(&subwist, cuww_dev, cuww_net);
}

INDIWECT_CAWWABWE_DECWAWE(int tcp_v6_wcv(stwuct sk_buff *));

/*
 *	Dewivew the packet to the host
 */
void ip6_pwotocow_dewivew_wcu(stwuct net *net, stwuct sk_buff *skb, int nexthdw,
			      boow have_finaw)
{
	const stwuct inet6_pwotocow *ippwot;
	stwuct inet6_dev *idev;
	unsigned int nhoff;
	SKB_DW(weason);
	boow waw;

	/*
	 *	Pawse extension headews
	 */

wesubmit:
	idev = ip6_dst_idev(skb_dst(skb));
	nhoff = IP6CB(skb)->nhoff;
	if (!have_finaw) {
		if (!pskb_puww(skb, skb_twanspowt_offset(skb)))
			goto discawd;
		nexthdw = skb_netwowk_headew(skb)[nhoff];
	}

wesubmit_finaw:
	waw = waw6_wocaw_dewivew(skb, nexthdw);
	ippwot = wcu_dewefewence(inet6_pwotos[nexthdw]);
	if (ippwot) {
		int wet;

		if (have_finaw) {
			if (!(ippwot->fwags & INET6_PWOTO_FINAW)) {
				/* Once we've seen a finaw pwotocow don't
				 * awwow encapsuwation on any non-finaw
				 * ones. This awwows foo in UDP encapsuwation
				 * to wowk.
				 */
				goto discawd;
			}
		} ewse if (ippwot->fwags & INET6_PWOTO_FINAW) {
			const stwuct ipv6hdw *hdw;
			int sdif = inet6_sdif(skb);
			stwuct net_device *dev;

			/* Onwy do this once fow fiwst finaw pwotocow */
			have_finaw = twue;


			skb_postpuww_wcsum(skb, skb_netwowk_headew(skb),
					   skb_netwowk_headew_wen(skb));
			hdw = ipv6_hdw(skb);

			/* skb->dev passed may be mastew dev fow vwfs. */
			if (sdif) {
				dev = dev_get_by_index_wcu(net, sdif);
				if (!dev)
					goto discawd;
			} ewse {
				dev = skb->dev;
			}

			if (ipv6_addw_is_muwticast(&hdw->daddw) &&
			    !ipv6_chk_mcast_addw(dev, &hdw->daddw,
						 &hdw->saddw) &&
			    !ipv6_is_mwd(skb, nexthdw, skb_netwowk_headew_wen(skb))) {
				SKB_DW_SET(weason, IP_INADDWEWWOWS);
				goto discawd;
			}
		}
		if (!(ippwot->fwags & INET6_PWOTO_NOPOWICY)) {
			if (!xfwm6_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
				SKB_DW_SET(weason, XFWM_POWICY);
				goto discawd;
			}
			nf_weset_ct(skb);
		}

		wet = INDIWECT_CAWW_2(ippwot->handwew, tcp_v6_wcv, udpv6_wcv,
				      skb);
		if (wet > 0) {
			if (ippwot->fwags & INET6_PWOTO_FINAW) {
				/* Not an extension headew, most wikewy UDP
				 * encapsuwation. Use wetuwn vawue as nexthdw
				 * pwotocow not nhoff (which pwesumabwy is
				 * not set by handwew).
				 */
				nexthdw = wet;
				goto wesubmit_finaw;
			} ewse {
				goto wesubmit;
			}
		} ewse if (wet == 0) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDEWIVEWS);
		}
	} ewse {
		if (!waw) {
			if (xfwm6_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
				__IP6_INC_STATS(net, idev,
						IPSTATS_MIB_INUNKNOWNPWOTOS);
				icmpv6_send(skb, ICMPV6_PAWAMPWOB,
					    ICMPV6_UNK_NEXTHDW, nhoff);
				SKB_DW_SET(weason, IP_NOPWOTO);
			} ewse {
				SKB_DW_SET(weason, XFWM_POWICY);
			}
			kfwee_skb_weason(skb, weason);
		} ewse {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDEWIVEWS);
			consume_skb(skb);
		}
	}
	wetuwn;

discawd:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCAWDS);
	kfwee_skb_weason(skb, weason);
}

static int ip6_input_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	skb_cweaw_dewivewy_time(skb);
	wcu_wead_wock();
	ip6_pwotocow_dewivew_wcu(net, skb, 0, fawse);
	wcu_wead_unwock();

	wetuwn 0;
}


int ip6_input(stwuct sk_buff *skb)
{
	wetuwn NF_HOOK(NFPWOTO_IPV6, NF_INET_WOCAW_IN,
		       dev_net(skb->dev), NUWW, skb, skb->dev, NUWW,
		       ip6_input_finish);
}
EXPOWT_SYMBOW_GPW(ip6_input);

int ip6_mc_input(stwuct sk_buff *skb)
{
	int sdif = inet6_sdif(skb);
	const stwuct ipv6hdw *hdw;
	stwuct net_device *dev;
	boow dewivew;

	__IP6_UPD_PO_STATS(dev_net(skb_dst(skb)->dev),
			 __in6_dev_get_safewy(skb->dev), IPSTATS_MIB_INMCAST,
			 skb->wen);

	/* skb->dev passed may be mastew dev fow vwfs. */
	if (sdif) {
		wcu_wead_wock();
		dev = dev_get_by_index_wcu(dev_net(skb->dev), sdif);
		if (!dev) {
			wcu_wead_unwock();
			kfwee_skb(skb);
			wetuwn -ENODEV;
		}
	} ewse {
		dev = skb->dev;
	}

	hdw = ipv6_hdw(skb);
	dewivew = ipv6_chk_mcast_addw(dev, &hdw->daddw, NUWW);
	if (sdif)
		wcu_wead_unwock();

#ifdef CONFIG_IPV6_MWOUTE
	/*
	 *      IPv6 muwticast woutew mode is now suppowted ;)
	 */
	if (atomic_wead(&dev_net(skb->dev)->ipv6.devconf_aww->mc_fowwawding) &&
	    !(ipv6_addw_type(&hdw->daddw) &
	      (IPV6_ADDW_WOOPBACK|IPV6_ADDW_WINKWOCAW)) &&
	    wikewy(!(IP6CB(skb)->fwags & IP6SKB_FOWWAWDED))) {
		/*
		 * Okay, we twy to fowwawd - spwit and dupwicate
		 * packets.
		 */
		stwuct sk_buff *skb2;
		stwuct inet6_skb_pawm *opt = IP6CB(skb);

		/* Check fow MWD */
		if (unwikewy(opt->fwags & IP6SKB_WOUTEWAWEWT)) {
			/* Check if this is a mwd message */
			u8 nexthdw = hdw->nexthdw;
			__be16 fwag_off;
			int offset;

			/* Check if the vawue of Woutew Awewt
			 * is fow MWD (0x0000).
			 */
			if (opt->wa == htons(IPV6_OPT_WOUTEWAWEWT_MWD)) {
				dewivew = fawse;

				if (!ipv6_ext_hdw(nexthdw)) {
					/* BUG */
					goto out;
				}
				offset = ipv6_skip_exthdw(skb, sizeof(*hdw),
							  &nexthdw, &fwag_off);
				if (offset < 0)
					goto out;

				if (ipv6_is_mwd(skb, nexthdw, offset))
					dewivew = twue;

				goto out;
			}
			/* unknown WA - pwocess it nowmawwy */
		}

		if (dewivew)
			skb2 = skb_cwone(skb, GFP_ATOMIC);
		ewse {
			skb2 = skb;
			skb = NUWW;
		}

		if (skb2) {
			ip6_mw_input(skb2);
		}
	}
out:
#endif
	if (wikewy(dewivew))
		ip6_input(skb);
	ewse {
		/* discawd */
		kfwee_skb(skb);
	}

	wetuwn 0;
}
