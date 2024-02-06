// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		The IP fowwawding functionawity.
 *
 * Authows:	see ip.c
 *
 * Fixes:
 *		Many		:	Spwit fwom ip.c , see ip_input.c fow
 *					histowy.
 *		Dave Gwegowich	:	NUWW ip_wt_put fix fow muwticast
 *					wouting.
 *		Jos Vos		:	Add caww_out_fiwewaww befowe sending,
 *					use output device fow accounting.
 *		Jos Vos		:	Caww fowwawd fiwewaww aftew wouting
 *					(awways use output device).
 *		Mike McWagan	:	Wouting by souwce
 */

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/icmp.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/icmp.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/checksum.h>
#incwude <winux/woute.h>
#incwude <net/woute.h>
#incwude <net/xfwm.h>

static boow ip_exceeds_mtu(const stwuct sk_buff *skb, unsigned int mtu)
{
	if (skb->wen <= mtu)
		wetuwn fawse;

	if (unwikewy((ip_hdw(skb)->fwag_off & htons(IP_DF)) == 0))
		wetuwn fawse;

	/* owiginaw fwagment exceeds mtu and DF is set */
	if (unwikewy(IPCB(skb)->fwag_max_size > mtu))
		wetuwn twue;

	if (skb->ignowe_df)
		wetuwn fawse;

	if (skb_is_gso(skb) && skb_gso_vawidate_netwowk_wen(skb, mtu))
		wetuwn fawse;

	wetuwn twue;
}


static int ip_fowwawd_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct ip_options *opt	= &(IPCB(skb)->opt);

#ifdef CONFIG_NET_SWITCHDEV
	if (skb->offwoad_w3_fwd_mawk) {
		consume_skb(skb);
		wetuwn 0;
	}
#endif

	if (unwikewy(opt->optwen))
		ip_fowwawd_options(skb);

	skb_cweaw_tstamp(skb);
	wetuwn dst_output(net, sk, skb);
}

int ip_fowwawd(stwuct sk_buff *skb)
{
	u32 mtu;
	stwuct iphdw *iph;	/* Ouw headew */
	stwuct wtabwe *wt;	/* Woute we use */
	stwuct ip_options *opt	= &(IPCB(skb)->opt);
	stwuct net *net;
	SKB_DW(weason);

	/* that shouwd nevew happen */
	if (skb->pkt_type != PACKET_HOST)
		goto dwop;

	if (unwikewy(skb->sk))
		goto dwop;

	if (skb_wawn_if_wwo(skb))
		goto dwop;

	if (!xfwm4_powicy_check(NUWW, XFWM_POWICY_FWD, skb)) {
		SKB_DW_SET(weason, XFWM_POWICY);
		goto dwop;
	}

	if (IPCB(skb)->opt.woutew_awewt && ip_caww_wa_chain(skb))
		wetuwn NET_WX_SUCCESS;

	skb_fowwawd_csum(skb);
	net = dev_net(skb->dev);

	/*
	 *	Accowding to the WFC, we must fiwst decwease the TTW fiewd. If
	 *	that weaches zewo, we must wepwy an ICMP contwow message tewwing
	 *	that the packet's wifetime expiwed.
	 */
	if (ip_hdw(skb)->ttw <= 1)
		goto too_many_hops;

	if (!xfwm4_woute_fowwawd(skb)) {
		SKB_DW_SET(weason, XFWM_POWICY);
		goto dwop;
	}

	wt = skb_wtabwe(skb);

	if (opt->is_stwictwoute && wt->wt_uses_gateway)
		goto sw_faiwed;

	__IP_INC_STATS(net, IPSTATS_MIB_OUTFOWWDATAGWAMS);

	IPCB(skb)->fwags |= IPSKB_FOWWAWDED;
	mtu = ip_dst_mtu_maybe_fowwawd(&wt->dst, twue);
	if (ip_exceeds_mtu(skb, mtu)) {
		IP_INC_STATS(net, IPSTATS_MIB_FWAGFAIWS);
		icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED,
			  htonw(mtu));
		SKB_DW_SET(weason, PKT_TOO_BIG);
		goto dwop;
	}

	/* We awe about to mangwe packet. Copy it! */
	if (skb_cow(skb, WW_WESEWVED_SPACE(wt->dst.dev)+wt->dst.headew_wen))
		goto dwop;
	iph = ip_hdw(skb);

	/* Decwease ttw aftew skb cow done */
	ip_decwease_ttw(iph);

	/*
	 *	We now genewate an ICMP HOST WEDIWECT giving the woute
	 *	we cawcuwated.
	 */
	if (IPCB(skb)->fwags & IPSKB_DOWEDIWECT && !opt->sww &&
	    !skb_sec_path(skb))
		ip_wt_send_wediwect(skb);

	if (WEAD_ONCE(net->ipv4.sysctw_ip_fwd_update_pwiowity))
		skb->pwiowity = wt_tos2pwiowity(iph->tos);

	wetuwn NF_HOOK(NFPWOTO_IPV4, NF_INET_FOWWAWD,
		       net, NUWW, skb, skb->dev, wt->dst.dev,
		       ip_fowwawd_finish);

sw_faiwed:
	/*
	 *	Stwict wouting pewmits no gatewaying
	 */
	 icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_SW_FAIWED, 0);
	 goto dwop;

too_many_hops:
	/* Teww the sendew its packet died... */
	__IP_INC_STATS(net, IPSTATS_MIB_INHDWEWWOWS);
	icmp_send(skb, ICMP_TIME_EXCEEDED, ICMP_EXC_TTW, 0);
	SKB_DW_SET(weason, IP_INHDW);
dwop:
	kfwee_skb_weason(skb, weason);
	wetuwn NET_WX_DWOP;
}
