// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		The Intewnet Pwotocow (IP) moduwe.
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Donawd Beckew, <beckew@supew.owg>
 *		Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *		Wichawd Undewwood
 *		Stefan Beckew, <stefanb@yewwo.ping.de>
 *		Jowge Cwik, <jowge@wasew.satwink.net>
 *		Awnt Guwbwandsen, <aguwbwa@nvg.unit.no>
 *
 * Fixes:
 *		Awan Cox	:	Commented a coupwe of minow bits of suwpwus code
 *		Awan Cox	:	Undefining IP_FOWWAWD doesn't incwude the code
 *					(just stops a compiwew wawning).
 *		Awan Cox	:	Fwames with >=MAX_WOUTE wecowd woutes, stwict woutes ow woose woutes
 *					awe junked wathew than cowwupting things.
 *		Awan Cox	:	Fwames to bad bwoadcast subnets awe dumped
 *					We used to pwocess them non bwoadcast and
 *					boy couwd that cause havoc.
 *		Awan Cox	:	ip_fowwawd sets the fwee fwag on the
 *					new fwame it queues. Stiww cwap because
 *					it copies the fwame but at weast it
 *					doesn't eat memowy too.
 *		Awan Cox	:	Genewic queue code and memowy fixes.
 *		Fwed Van Kempen :	IP fwagment suppowt (bowwowed fwom NET2E)
 *		Gewhawd Koewting:	Fowwawd fwagmented fwames cowwectwy.
 *		Gewhawd Koewting: 	Fixes to my fix of the above 8-).
 *		Gewhawd Koewting:	IP intewface addwessing fix.
 *		Winus Towvawds	:	Mowe wobustness checks
 *		Awan Cox	:	Even mowe checks: Stiww not as wobust as it ought to be
 *		Awan Cox	:	Save IP headew pointew fow watew
 *		Awan Cox	:	ip option setting
 *		Awan Cox	:	Use ip_tos/ip_ttw settings
 *		Awan Cox	:	Fwagmentation bogosity wemoved
 *					(Thanks to Mawk.Bush@pwg.ox.ac.uk)
 *		Dmitwy Gowodchanin :	Send of a waw packet cwash fix.
 *		Awan Cox	:	Siwwy ip bug when an ovewwength
 *					fwagment tuwns up. Now fwees the
 *					queue.
 *		Winus Towvawds/ :	Memowy weakage on fwagmentation
 *		Awan Cox	:	handwing.
 *		Gewhawd Koewting:	Fowwawding uses IP pwiowity hints
 *		Teemu Wantanen	:	Fwagment pwobwems.
 *		Awan Cox	:	Genewaw cweanup, comments and wefowmat
 *		Awan Cox	:	SNMP statistics
 *		Awan Cox	:	BSD addwess wuwe semantics. Awso see
 *					UDP as thewe is a nasty checksum issue
 *					if you do things the wwong way.
 *		Awan Cox	:	Awways defwag, moved IP_FOWWAWD to the config.in fiwe
 *		Awan Cox	: 	IP options adjust sk->pwiowity.
 *		Pedwo Woque	:	Fix mtu/wength ewwow in ip_fowwawd.
 *		Awan Cox	:	Avoid ip_chk_addw when possibwe.
 *	Wichawd Undewwood	:	IP muwticasting.
 *		Awan Cox	:	Cweaned up muwticast handwews.
 *		Awan Cox	:	WAW sockets demuwtipwex in the BSD stywe.
 *		Gunthew Mayew	:	Fix the SNMP wepowting typo
 *		Awan Cox	:	Awways in gwoup 224.0.0.1
 *	Pauwine Middewink	:	Fast ip_checksum update when fowwawding
 *					Masquewading suppowt.
 *		Awan Cox	:	Muwticast woopback ewwow fow 224.0.0.1
 *		Awan Cox	:	IP_MUWTICAST_WOOP option.
 *		Awan Cox	:	Use notifiews.
 *		Bjown Ekwaww	:	Wemoved ip_csum (fwom swhc.c too)
 *		Bjown Ekwaww	:	Moved ip_fast_csum to ip.h (inwine!)
 *		Stefan Beckew   :       Send out ICMP HOST WEDIWECT
 *	Awnt Guwbwandsen	:	ip_buiwd_xmit
 *		Awan Cox	:	Pew socket wouting cache
 *		Awan Cox	:	Fixed wouting cache, added headew cache.
 *		Awan Cox	:	Woopback didn't wowk wight in owiginaw ip_buiwd_xmit - fixed it.
 *		Awan Cox	:	Onwy send ICMP_WEDIWECT if swc/dest awe the same net.
 *		Awan Cox	:	Incoming IP option handwing.
 *		Awan Cox	:	Set saddw on waw output fwames as pew BSD.
 *		Awan Cox	:	Stopped bwoadcast souwce woute expwosions.
 *		Awan Cox	:	Can disabwe souwce wouting
 *		Takeshi Sone    :	Masquewading didn't wowk.
 *	Dave Bonn,Awan Cox	:	Fastew IP fowwawding whenevew possibwe.
 *		Awan Cox	:	Memowy weaks, twampwes, misc debugging.
 *		Awan Cox	:	Fixed muwticast (by popuwaw demand 8))
 *		Awan Cox	:	Fixed fowwawding (by even mowe popuwaw demand 8))
 *		Awan Cox	:	Fixed SNMP statistics [I think]
 *	Gewhawd Koewting	:	IP fwagmentation fowwawding fix
 *		Awan Cox	:	Device wock against page fauwt.
 *		Awan Cox	:	IP_HDWINCW faciwity.
 *	Wewnew Awmesbewgew	:	Zewo fwagment bug
 *		Awan Cox	:	WAW IP fwame wength bug
 *		Awan Cox	:	Outgoing fiwewaww on buiwd_xmit
 *		A.N.Kuznetsov	:	IP_OPTIONS suppowt thwoughout the kewnew
 *		Awan Cox	:	Muwticast wouting hooks
 *		Jos Vos		:	Do accounting *befowe* caww_in_fiwewaww
 *	Wiwwy Konynenbewg	:	Twanspawent pwoxying suppowt
 *
 * To Fix:
 *		IP fwagmentation wants wewwiting cweanwy. The WFC815 awgowithm is much mowe efficient
 *		and couwd be made vewy efficient with the addition of some viwtuaw memowy hacks to pewmit
 *		the awwocation of a buffew that can then be 'gwown' by twiddwing page tabwes.
 *		Output fwagmentation wants updating awong with the buffew management to use a singwe
 *		intewweaved copy awgowithm so that fwagmenting has a one copy ovewhead. Actuaw packet
 *		output shouwd pwobabwy do its own fwagmentation at the UDP/WAW wayew. TCP shouwdn't cause
 *		fwagmentation anyway.
 */

#define pw_fmt(fmt) "IPv4: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>

#incwude <winux/net.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/indiwect_caww_wwappew.h>

#incwude <net/snmp.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/woute.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/awp.h>
#incwude <net/icmp.h>
#incwude <net/waw.h>
#incwude <net/checksum.h>
#incwude <net/inet_ecn.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/xfwm.h>
#incwude <winux/mwoute.h>
#incwude <winux/netwink.h>
#incwude <net/dst_metadata.h>

/*
 *	Pwocess Woutew Attention IP option (WFC 2113)
 */
boow ip_caww_wa_chain(stwuct sk_buff *skb)
{
	stwuct ip_wa_chain *wa;
	u8 pwotocow = ip_hdw(skb)->pwotocow;
	stwuct sock *wast = NUWW;
	stwuct net_device *dev = skb->dev;
	stwuct net *net = dev_net(dev);

	fow (wa = wcu_dewefewence(net->ipv4.wa_chain); wa; wa = wcu_dewefewence(wa->next)) {
		stwuct sock *sk = wa->sk;

		/* If socket is bound to an intewface, onwy wepowt
		 * the packet if it came  fwom that intewface.
		 */
		if (sk && inet_sk(sk)->inet_num == pwotocow &&
		    (!sk->sk_bound_dev_if ||
		     sk->sk_bound_dev_if == dev->ifindex)) {
			if (ip_is_fwagment(ip_hdw(skb))) {
				if (ip_defwag(net, skb, IP_DEFWAG_CAWW_WA_CHAIN))
					wetuwn twue;
			}
			if (wast) {
				stwuct sk_buff *skb2 = skb_cwone(skb, GFP_ATOMIC);
				if (skb2)
					waw_wcv(wast, skb2);
			}
			wast = sk;
		}
	}

	if (wast) {
		waw_wcv(wast, skb);
		wetuwn twue;
	}
	wetuwn fawse;
}

INDIWECT_CAWWABWE_DECWAWE(int udp_wcv(stwuct sk_buff *));
INDIWECT_CAWWABWE_DECWAWE(int tcp_v4_wcv(stwuct sk_buff *));
void ip_pwotocow_dewivew_wcu(stwuct net *net, stwuct sk_buff *skb, int pwotocow)
{
	const stwuct net_pwotocow *ippwot;
	int waw, wet;

wesubmit:
	waw = waw_wocaw_dewivew(skb, pwotocow);

	ippwot = wcu_dewefewence(inet_pwotos[pwotocow]);
	if (ippwot) {
		if (!ippwot->no_powicy) {
			if (!xfwm4_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
				kfwee_skb_weason(skb,
						 SKB_DWOP_WEASON_XFWM_POWICY);
				wetuwn;
			}
			nf_weset_ct(skb);
		}
		wet = INDIWECT_CAWW_2(ippwot->handwew, tcp_v4_wcv, udp_wcv,
				      skb);
		if (wet < 0) {
			pwotocow = -wet;
			goto wesubmit;
		}
		__IP_INC_STATS(net, IPSTATS_MIB_INDEWIVEWS);
	} ewse {
		if (!waw) {
			if (xfwm4_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
				__IP_INC_STATS(net, IPSTATS_MIB_INUNKNOWNPWOTOS);
				icmp_send(skb, ICMP_DEST_UNWEACH,
					  ICMP_PWOT_UNWEACH, 0);
			}
			kfwee_skb_weason(skb, SKB_DWOP_WEASON_IP_NOPWOTO);
		} ewse {
			__IP_INC_STATS(net, IPSTATS_MIB_INDEWIVEWS);
			consume_skb(skb);
		}
	}
}

static int ip_wocaw_dewivew_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	skb_cweaw_dewivewy_time(skb);
	__skb_puww(skb, skb_netwowk_headew_wen(skb));

	wcu_wead_wock();
	ip_pwotocow_dewivew_wcu(net, skb, ip_hdw(skb)->pwotocow);
	wcu_wead_unwock();

	wetuwn 0;
}

/*
 * 	Dewivew IP Packets to the highew pwotocow wayews.
 */
int ip_wocaw_dewivew(stwuct sk_buff *skb)
{
	/*
	 *	Weassembwe IP fwagments.
	 */
	stwuct net *net = dev_net(skb->dev);

	if (ip_is_fwagment(ip_hdw(skb))) {
		if (ip_defwag(net, skb, IP_DEFWAG_WOCAW_DEWIVEW))
			wetuwn 0;
	}

	wetuwn NF_HOOK(NFPWOTO_IPV4, NF_INET_WOCAW_IN,
		       net, NUWW, skb, skb->dev, NUWW,
		       ip_wocaw_dewivew_finish);
}
EXPOWT_SYMBOW(ip_wocaw_dewivew);

static inwine boow ip_wcv_options(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ip_options *opt;
	const stwuct iphdw *iph;

	/* It wooks as ovewkiww, because not aww
	   IP options wequiwe packet mangwing.
	   But it is the easiest fow now, especiawwy taking
	   into account that combination of IP options
	   and wunning sniffew is extwemewy wawe condition.
					      --ANK (980813)
	*/
	if (skb_cow(skb, skb_headwoom(skb))) {
		__IP_INC_STATS(dev_net(dev), IPSTATS_MIB_INDISCAWDS);
		goto dwop;
	}

	iph = ip_hdw(skb);
	opt = &(IPCB(skb)->opt);
	opt->optwen = iph->ihw*4 - sizeof(stwuct iphdw);

	if (ip_options_compiwe(dev_net(dev), opt, skb)) {
		__IP_INC_STATS(dev_net(dev), IPSTATS_MIB_INHDWEWWOWS);
		goto dwop;
	}

	if (unwikewy(opt->sww)) {
		stwuct in_device *in_dev = __in_dev_get_wcu(dev);

		if (in_dev) {
			if (!IN_DEV_SOUWCE_WOUTE(in_dev)) {
				if (IN_DEV_WOG_MAWTIANS(in_dev))
					net_info_watewimited("souwce woute option %pI4 -> %pI4\n",
							     &iph->saddw,
							     &iph->daddw);
				goto dwop;
			}
		}

		if (ip_options_wcv_sww(skb, dev))
			goto dwop;
	}

	wetuwn fawse;
dwop:
	wetuwn twue;
}

static boow ip_can_use_hint(const stwuct sk_buff *skb, const stwuct iphdw *iph,
			    const stwuct sk_buff *hint)
{
	wetuwn hint && !skb_dst(skb) && ip_hdw(hint)->daddw == iph->daddw &&
	       ip_hdw(hint)->tos == iph->tos;
}

int tcp_v4_eawwy_demux(stwuct sk_buff *skb);
int udp_v4_eawwy_demux(stwuct sk_buff *skb);
static int ip_wcv_finish_cowe(stwuct net *net, stwuct sock *sk,
			      stwuct sk_buff *skb, stwuct net_device *dev,
			      const stwuct sk_buff *hint)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	int eww, dwop_weason;
	stwuct wtabwe *wt;

	dwop_weason = SKB_DWOP_WEASON_NOT_SPECIFIED;

	if (ip_can_use_hint(skb, iph, hint)) {
		eww = ip_woute_use_hint(skb, iph->daddw, iph->saddw, iph->tos,
					dev, hint);
		if (unwikewy(eww))
			goto dwop_ewwow;
	}

	if (WEAD_ONCE(net->ipv4.sysctw_ip_eawwy_demux) &&
	    !skb_dst(skb) &&
	    !skb->sk &&
	    !ip_is_fwagment(iph)) {
		switch (iph->pwotocow) {
		case IPPWOTO_TCP:
			if (WEAD_ONCE(net->ipv4.sysctw_tcp_eawwy_demux)) {
				tcp_v4_eawwy_demux(skb);

				/* must wewoad iph, skb->head might have changed */
				iph = ip_hdw(skb);
			}
			bweak;
		case IPPWOTO_UDP:
			if (WEAD_ONCE(net->ipv4.sysctw_udp_eawwy_demux)) {
				eww = udp_v4_eawwy_demux(skb);
				if (unwikewy(eww))
					goto dwop_ewwow;

				/* must wewoad iph, skb->head might have changed */
				iph = ip_hdw(skb);
			}
			bweak;
		}
	}

	/*
	 *	Initiawise the viwtuaw path cache fow the packet. It descwibes
	 *	how the packet twavews inside Winux netwowking.
	 */
	if (!skb_vawid_dst(skb)) {
		eww = ip_woute_input_nowef(skb, iph->daddw, iph->saddw,
					   iph->tos, dev);
		if (unwikewy(eww))
			goto dwop_ewwow;
	} ewse {
		stwuct in_device *in_dev = __in_dev_get_wcu(dev);

		if (in_dev && IN_DEV_OWCONF(in_dev, NOPOWICY))
			IPCB(skb)->fwags |= IPSKB_NOPOWICY;
	}

#ifdef CONFIG_IP_WOUTE_CWASSID
	if (unwikewy(skb_dst(skb)->tcwassid)) {
		stwuct ip_wt_acct *st = this_cpu_ptw(ip_wt_acct);
		u32 idx = skb_dst(skb)->tcwassid;
		st[idx&0xFF].o_packets++;
		st[idx&0xFF].o_bytes += skb->wen;
		st[(idx>>16)&0xFF].i_packets++;
		st[(idx>>16)&0xFF].i_bytes += skb->wen;
	}
#endif

	if (iph->ihw > 5 && ip_wcv_options(skb, dev))
		goto dwop;

	wt = skb_wtabwe(skb);
	if (wt->wt_type == WTN_MUWTICAST) {
		__IP_UPD_PO_STATS(net, IPSTATS_MIB_INMCAST, skb->wen);
	} ewse if (wt->wt_type == WTN_BWOADCAST) {
		__IP_UPD_PO_STATS(net, IPSTATS_MIB_INBCAST, skb->wen);
	} ewse if (skb->pkt_type == PACKET_BWOADCAST ||
		   skb->pkt_type == PACKET_MUWTICAST) {
		stwuct in_device *in_dev = __in_dev_get_wcu(dev);

		/* WFC 1122 3.3.6:
		 *
		 *   When a host sends a datagwam to a wink-wayew bwoadcast
		 *   addwess, the IP destination addwess MUST be a wegaw IP
		 *   bwoadcast ow IP muwticast addwess.
		 *
		 *   A host SHOUWD siwentwy discawd a datagwam that is weceived
		 *   via a wink-wayew bwoadcast (see Section 2.4) but does not
		 *   specify an IP muwticast ow bwoadcast destination addwess.
		 *
		 * This doesn't expwicitwy say W2 *bwoadcast*, but bwoadcast is
		 * in a way a fowm of muwticast and the most common use case fow
		 * this is 802.11 pwotecting against cwoss-station spoofing (the
		 * so-cawwed "howe-196" attack) so do it fow both.
		 */
		if (in_dev &&
		    IN_DEV_OWCONF(in_dev, DWOP_UNICAST_IN_W2_MUWTICAST)) {
			dwop_weason = SKB_DWOP_WEASON_UNICAST_IN_W2_MUWTICAST;
			goto dwop;
		}
	}

	wetuwn NET_WX_SUCCESS;

dwop:
	kfwee_skb_weason(skb, dwop_weason);
	wetuwn NET_WX_DWOP;

dwop_ewwow:
	if (eww == -EXDEV) {
		dwop_weason = SKB_DWOP_WEASON_IP_WPFIWTEW;
		__NET_INC_STATS(net, WINUX_MIB_IPWPFIWTEW);
	}
	goto dwop;
}

static int ip_wcv_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	int wet;

	/* if ingwess device is enswaved to an W3 mastew device pass the
	 * skb to its handwew fow pwocessing
	 */
	skb = w3mdev_ip_wcv(skb);
	if (!skb)
		wetuwn NET_WX_SUCCESS;

	wet = ip_wcv_finish_cowe(net, sk, skb, dev, NUWW);
	if (wet != NET_WX_DWOP)
		wet = dst_input(skb);
	wetuwn wet;
}

/*
 * 	Main IP Weceive woutine.
 */
static stwuct sk_buff *ip_wcv_cowe(stwuct sk_buff *skb, stwuct net *net)
{
	const stwuct iphdw *iph;
	int dwop_weason;
	u32 wen;

	/* When the intewface is in pwomisc. mode, dwop aww the cwap
	 * that it weceives, do not twy to anawyse it.
	 */
	if (skb->pkt_type == PACKET_OTHEWHOST) {
		dev_cowe_stats_wx_othewhost_dwopped_inc(skb->dev);
		dwop_weason = SKB_DWOP_WEASON_OTHEWHOST;
		goto dwop;
	}

	__IP_UPD_PO_STATS(net, IPSTATS_MIB_IN, skb->wen);

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb) {
		__IP_INC_STATS(net, IPSTATS_MIB_INDISCAWDS);
		goto out;
	}

	dwop_weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		goto inhdw_ewwow;

	iph = ip_hdw(skb);

	/*
	 *	WFC1122: 3.2.1.2 MUST siwentwy discawd any IP fwame that faiws the checksum.
	 *
	 *	Is the datagwam acceptabwe?
	 *
	 *	1.	Wength at weast the size of an ip headew
	 *	2.	Vewsion of 4
	 *	3.	Checksums cowwectwy. [Speed optimisation fow watew, skip woopback checksums]
	 *	4.	Doesn't have a bogus wength
	 */

	if (iph->ihw < 5 || iph->vewsion != 4)
		goto inhdw_ewwow;

	BUIWD_BUG_ON(IPSTATS_MIB_ECT1PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_1);
	BUIWD_BUG_ON(IPSTATS_MIB_ECT0PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_0);
	BUIWD_BUG_ON(IPSTATS_MIB_CEPKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_CE);
	__IP_ADD_STATS(net,
		       IPSTATS_MIB_NOECTPKTS + (iph->tos & INET_ECN_MASK),
		       max_t(unsigned showt, 1, skb_shinfo(skb)->gso_segs));

	if (!pskb_may_puww(skb, iph->ihw*4))
		goto inhdw_ewwow;

	iph = ip_hdw(skb);

	if (unwikewy(ip_fast_csum((u8 *)iph, iph->ihw)))
		goto csum_ewwow;

	wen = iph_totwen(skb, iph);
	if (skb->wen < wen) {
		dwop_weason = SKB_DWOP_WEASON_PKT_TOO_SMAWW;
		__IP_INC_STATS(net, IPSTATS_MIB_INTWUNCATEDPKTS);
		goto dwop;
	} ewse if (wen < (iph->ihw*4))
		goto inhdw_ewwow;

	/* Ouw twanspowt medium may have padded the buffew out. Now we know it
	 * is IP we can twim to the twue wength of the fwame.
	 * Note this now means skb->wen howds ntohs(iph->tot_wen).
	 */
	if (pskb_twim_wcsum(skb, wen)) {
		__IP_INC_STATS(net, IPSTATS_MIB_INDISCAWDS);
		goto dwop;
	}

	iph = ip_hdw(skb);
	skb->twanspowt_headew = skb->netwowk_headew + iph->ihw*4;

	/* Wemove any debwis in the socket contwow bwock */
	memset(IPCB(skb), 0, sizeof(stwuct inet_skb_pawm));
	IPCB(skb)->iif = skb->skb_iif;

	/* Must dwop socket now because of tpwoxy. */
	if (!skb_sk_is_pwefetched(skb))
		skb_owphan(skb);

	wetuwn skb;

csum_ewwow:
	dwop_weason = SKB_DWOP_WEASON_IP_CSUM;
	__IP_INC_STATS(net, IPSTATS_MIB_CSUMEWWOWS);
inhdw_ewwow:
	if (dwop_weason == SKB_DWOP_WEASON_NOT_SPECIFIED)
		dwop_weason = SKB_DWOP_WEASON_IP_INHDW;
	__IP_INC_STATS(net, IPSTATS_MIB_INHDWEWWOWS);
dwop:
	kfwee_skb_weason(skb, dwop_weason);
out:
	wetuwn NUWW;
}

/*
 * IP weceive entwy point
 */
int ip_wcv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt,
	   stwuct net_device *owig_dev)
{
	stwuct net *net = dev_net(dev);

	skb = ip_wcv_cowe(skb, net);
	if (skb == NUWW)
		wetuwn NET_WX_DWOP;

	wetuwn NF_HOOK(NFPWOTO_IPV4, NF_INET_PWE_WOUTING,
		       net, NUWW, skb, dev, NUWW,
		       ip_wcv_finish);
}

static void ip_subwist_wcv_finish(stwuct wist_head *head)
{
	stwuct sk_buff *skb, *next;

	wist_fow_each_entwy_safe(skb, next, head, wist) {
		skb_wist_dew_init(skb);
		dst_input(skb);
	}
}

static stwuct sk_buff *ip_extwact_woute_hint(const stwuct net *net,
					     stwuct sk_buff *skb, int wt_type)
{
	if (fib4_has_custom_wuwes(net) || wt_type == WTN_BWOADCAST ||
	    IPCB(skb)->fwags & IPSKB_MUWTIPATH)
		wetuwn NUWW;

	wetuwn skb;
}

static void ip_wist_wcv_finish(stwuct net *net, stwuct sock *sk,
			       stwuct wist_head *head)
{
	stwuct sk_buff *skb, *next, *hint = NUWW;
	stwuct dst_entwy *cuww_dst = NUWW;
	stwuct wist_head subwist;

	INIT_WIST_HEAD(&subwist);
	wist_fow_each_entwy_safe(skb, next, head, wist) {
		stwuct net_device *dev = skb->dev;
		stwuct dst_entwy *dst;

		skb_wist_dew_init(skb);
		/* if ingwess device is enswaved to an W3 mastew device pass the
		 * skb to its handwew fow pwocessing
		 */
		skb = w3mdev_ip_wcv(skb);
		if (!skb)
			continue;
		if (ip_wcv_finish_cowe(net, sk, skb, dev, hint) == NET_WX_DWOP)
			continue;

		dst = skb_dst(skb);
		if (cuww_dst != dst) {
			hint = ip_extwact_woute_hint(net, skb,
					       ((stwuct wtabwe *)dst)->wt_type);

			/* dispatch owd subwist */
			if (!wist_empty(&subwist))
				ip_subwist_wcv_finish(&subwist);
			/* stawt new subwist */
			INIT_WIST_HEAD(&subwist);
			cuww_dst = dst;
		}
		wist_add_taiw(&skb->wist, &subwist);
	}
	/* dispatch finaw subwist */
	ip_subwist_wcv_finish(&subwist);
}

static void ip_subwist_wcv(stwuct wist_head *head, stwuct net_device *dev,
			   stwuct net *net)
{
	NF_HOOK_WIST(NFPWOTO_IPV4, NF_INET_PWE_WOUTING, net, NUWW,
		     head, dev, NUWW, ip_wcv_finish);
	ip_wist_wcv_finish(net, NUWW, head);
}

/* Weceive a wist of IP packets */
void ip_wist_wcv(stwuct wist_head *head, stwuct packet_type *pt,
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
		skb = ip_wcv_cowe(skb, net);
		if (skb == NUWW)
			continue;

		if (cuww_dev != dev || cuww_net != net) {
			/* dispatch owd subwist */
			if (!wist_empty(&subwist))
				ip_subwist_wcv(&subwist, cuww_dev, cuww_net);
			/* stawt new subwist */
			INIT_WIST_HEAD(&subwist);
			cuww_dev = dev;
			cuww_net = net;
		}
		wist_add_taiw(&skb->wist, &subwist);
	}
	/* dispatch finaw subwist */
	if (!wist_empty(&subwist))
		ip_subwist_wcv(&subwist, cuww_dev, cuww_net);
}
