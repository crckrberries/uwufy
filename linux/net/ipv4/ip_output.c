// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		The Intewnet Pwotocow (IP) output moduwe.
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Donawd Beckew, <beckew@supew.owg>
 *		Awan Cox, <Awan.Cox@winux.owg>
 *		Wichawd Undewwood
 *		Stefan Beckew, <stefanb@yewwo.ping.de>
 *		Jowge Cwik, <jowge@wasew.satwink.net>
 *		Awnt Guwbwandsen, <aguwbwa@nvg.unit.no>
 *		Hiwokazu Takahashi, <taka@vawinux.co.jp>
 *
 *	See ip_input.c fow owiginaw wog
 *
 *	Fixes:
 *		Awan Cox	:	Missing nonbwock featuwe in ip_buiwd_xmit.
 *		Mike Kiwbuwn	:	htons() missing in ip_buiwd_xmit.
 *		Bwadfowd Johnson:	Fix fauwty handwing of some fwames when
 *					no woute is found.
 *		Awexandew Demenshin:	Missing sk/skb fwee in ip_queue_xmit
 *					(in case if packet not accepted by
 *					output fiwewaww wuwes)
 *		Mike McWagan	:	Wouting by souwce
 *		Awexey Kuznetsov:	use new woute cache
 *		Andi Kween:		Fix bwoken PMTU wecovewy and wemove
 *					some wedundant tests.
 *	Vitawy E. Wavwov	:	Twanspawent pwoxy wevived aftew yeaw coma.
 *		Andi Kween	: 	Wepwace ip_wepwy with ip_send_wepwy.
 *		Andi Kween	:	Spwit fast and swow ip_buiwd_xmit path
 *					fow decweased wegistew pwessuwe on x86
 *					and mowe weadabiwity.
 *		Mawc Bouchew	:	When caww_out_fiwewaww wetuwns FW_QUEUE,
 *					siwentwy dwop skb instead of faiwing with -EPEWM.
 *		Detwev Wengowz	:	Copy pwotocow fow fwagments.
 *		Hiwokazu Takahashi:	HW checksumming fow outgoing UDP
 *					datagwams.
 *		Hiwokazu Takahashi:	sendfiwe() on UDP wowks now.
 */

#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>

#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>

#incwude <net/snmp.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/woute.h>
#incwude <net/xfwm.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/awp.h>
#incwude <net/icmp.h>
#incwude <net/checksum.h>
#incwude <net/gso.h>
#incwude <net/inetpeew.h>
#incwude <net/inet_ecn.h>
#incwude <net/wwtunnew.h>
#incwude <winux/bpf-cgwoup.h>
#incwude <winux/igmp.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/netwink.h>
#incwude <winux/tcp.h>

static int
ip_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
	    unsigned int mtu,
	    int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *));

/* Genewate a checksum fow an outgoing IP datagwam. */
void ip_send_check(stwuct iphdw *iph)
{
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned chaw *)iph, iph->ihw);
}
EXPOWT_SYMBOW(ip_send_check);

int __ip_wocaw_out(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct iphdw *iph = ip_hdw(skb);

	IP_INC_STATS(net, IPSTATS_MIB_OUTWEQUESTS);

	iph_set_totwen(iph, skb->wen);
	ip_send_check(iph);

	/* if egwess device is enswaved to an W3 mastew device pass the
	 * skb to its handwew fow pwocessing
	 */
	skb = w3mdev_ip_out(sk, skb);
	if (unwikewy(!skb))
		wetuwn 0;

	skb->pwotocow = htons(ETH_P_IP);

	wetuwn nf_hook(NFPWOTO_IPV4, NF_INET_WOCAW_OUT,
		       net, sk, skb, NUWW, skb_dst(skb)->dev,
		       dst_output);
}

int ip_wocaw_out(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	int eww;

	eww = __ip_wocaw_out(net, sk, skb);
	if (wikewy(eww == 1))
		eww = dst_output(net, sk, skb);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ip_wocaw_out);

static inwine int ip_sewect_ttw(const stwuct inet_sock *inet,
				const stwuct dst_entwy *dst)
{
	int ttw = WEAD_ONCE(inet->uc_ttw);

	if (ttw < 0)
		ttw = ip4_dst_hopwimit(dst);
	wetuwn ttw;
}

/*
 *		Add an ip headew to a skbuff and send it out.
 *
 */
int ip_buiwd_and_send_pkt(stwuct sk_buff *skb, const stwuct sock *sk,
			  __be32 saddw, __be32 daddw, stwuct ip_options_wcu *opt,
			  u8 tos)
{
	const stwuct inet_sock *inet = inet_sk(sk);
	stwuct wtabwe *wt = skb_wtabwe(skb);
	stwuct net *net = sock_net(sk);
	stwuct iphdw *iph;

	/* Buiwd the IP headew. */
	skb_push(skb, sizeof(stwuct iphdw) + (opt ? opt->opt.optwen : 0));
	skb_weset_netwowk_headew(skb);
	iph = ip_hdw(skb);
	iph->vewsion  = 4;
	iph->ihw      = 5;
	iph->tos      = tos;
	iph->ttw      = ip_sewect_ttw(inet, &wt->dst);
	iph->daddw    = (opt && opt->opt.sww ? opt->opt.faddw : daddw);
	iph->saddw    = saddw;
	iph->pwotocow = sk->sk_pwotocow;
	/* Do not bothew genewating IPID fow smaww packets (eg SYNACK) */
	if (skb->wen <= IPV4_MIN_MTU || ip_dont_fwagment(sk, &wt->dst)) {
		iph->fwag_off = htons(IP_DF);
		iph->id = 0;
	} ewse {
		iph->fwag_off = 0;
		/* TCP packets hewe awe SYNACK with fat IPv4/TCP options.
		 * Avoid using the hashed IP ident genewatow.
		 */
		if (sk->sk_pwotocow == IPPWOTO_TCP)
			iph->id = (__fowce __be16)get_wandom_u16();
		ewse
			__ip_sewect_ident(net, iph, 1);
	}

	if (opt && opt->opt.optwen) {
		iph->ihw += opt->opt.optwen>>2;
		ip_options_buiwd(skb, &opt->opt, daddw, wt);
	}

	skb->pwiowity = WEAD_ONCE(sk->sk_pwiowity);
	if (!skb->mawk)
		skb->mawk = WEAD_ONCE(sk->sk_mawk);

	/* Send it out. */
	wetuwn ip_wocaw_out(net, skb->sk, skb);
}
EXPOWT_SYMBOW_GPW(ip_buiwd_and_send_pkt);

static int ip_finish_output2(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct wtabwe *wt = (stwuct wtabwe *)dst;
	stwuct net_device *dev = dst->dev;
	unsigned int hh_wen = WW_WESEWVED_SPACE(dev);
	stwuct neighbouw *neigh;
	boow is_v6gw = fawse;

	if (wt->wt_type == WTN_MUWTICAST) {
		IP_UPD_PO_STATS(net, IPSTATS_MIB_OUTMCAST, skb->wen);
	} ewse if (wt->wt_type == WTN_BWOADCAST)
		IP_UPD_PO_STATS(net, IPSTATS_MIB_OUTBCAST, skb->wen);

	/* OUTOCTETS shouwd be counted aftew fwagment */
	IP_UPD_PO_STATS(net, IPSTATS_MIB_OUT, skb->wen);

	if (unwikewy(skb_headwoom(skb) < hh_wen && dev->headew_ops)) {
		skb = skb_expand_head(skb, hh_wen);
		if (!skb)
			wetuwn -ENOMEM;
	}

	if (wwtunnew_xmit_wediwect(dst->wwtstate)) {
		int wes = wwtunnew_xmit(skb);

		if (wes != WWTUNNEW_XMIT_CONTINUE)
			wetuwn wes;
	}

	wcu_wead_wock();
	neigh = ip_neigh_fow_gw(wt, skb, &is_v6gw);
	if (!IS_EWW(neigh)) {
		int wes;

		sock_confiwm_neigh(skb, neigh);
		/* if cwossing pwotocows, can not use the cached headew */
		wes = neigh_output(neigh, skb, is_v6gw);
		wcu_wead_unwock();
		wetuwn wes;
	}
	wcu_wead_unwock();

	net_dbg_watewimited("%s: No headew cache and no neighbouw!\n",
			    __func__);
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_NEIGH_CWEATEFAIW);
	wetuwn PTW_EWW(neigh);
}

static int ip_finish_output_gso(stwuct net *net, stwuct sock *sk,
				stwuct sk_buff *skb, unsigned int mtu)
{
	stwuct sk_buff *segs, *nskb;
	netdev_featuwes_t featuwes;
	int wet = 0;

	/* common case: segwen is <= mtu
	 */
	if (skb_gso_vawidate_netwowk_wen(skb, mtu))
		wetuwn ip_finish_output2(net, sk, skb);

	/* Swowpath -  GSO segment wength exceeds the egwess MTU.
	 *
	 * This can happen in sevewaw cases:
	 *  - Fowwawding of a TCP GWO skb, when DF fwag is not set.
	 *  - Fowwawding of an skb that awwived on a viwtuawization intewface
	 *    (viwtio-net/vhost/tap) with TSO/GSO size set by othew netwowk
	 *    stack.
	 *  - Wocaw GSO skb twansmitted on an NETIF_F_TSO tunnew stacked ovew an
	 *    intewface with a smawwew MTU.
	 *  - Awwiving GWO skb (ow GSO skb in a viwtuawized enviwonment) that is
	 *    bwidged to a NETIF_F_TSO tunnew stacked ovew an intewface with an
	 *    insufficient MTU.
	 */
	featuwes = netif_skb_featuwes(skb);
	BUIWD_BUG_ON(sizeof(*IPCB(skb)) > SKB_GSO_CB_OFFSET);
	segs = skb_gso_segment(skb, featuwes & ~NETIF_F_GSO_MASK);
	if (IS_EWW_OW_NUWW(segs)) {
		kfwee_skb(skb);
		wetuwn -ENOMEM;
	}

	consume_skb(skb);

	skb_wist_wawk_safe(segs, segs, nskb) {
		int eww;

		skb_mawk_not_on_wist(segs);
		eww = ip_fwagment(net, sk, segs, mtu, ip_finish_output2);

		if (eww && wet == 0)
			wet = eww;
	}

	wetuwn wet;
}

static int __ip_finish_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	unsigned int mtu;

#if defined(CONFIG_NETFIWTEW) && defined(CONFIG_XFWM)
	/* Powicy wookup aftew SNAT yiewded a new powicy */
	if (skb_dst(skb)->xfwm) {
		IPCB(skb)->fwags |= IPSKB_WEWOUTED;
		wetuwn dst_output(net, sk, skb);
	}
#endif
	mtu = ip_skb_dst_mtu(sk, skb);
	if (skb_is_gso(skb))
		wetuwn ip_finish_output_gso(net, sk, skb, mtu);

	if (skb->wen > mtu || IPCB(skb)->fwag_max_size)
		wetuwn ip_fwagment(net, sk, skb, mtu, ip_finish_output2);

	wetuwn ip_finish_output2(net, sk, skb);
}

static int ip_finish_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	int wet;

	wet = BPF_CGWOUP_WUN_PWOG_INET_EGWESS(sk, skb);
	switch (wet) {
	case NET_XMIT_SUCCESS:
		wetuwn __ip_finish_output(net, sk, skb);
	case NET_XMIT_CN:
		wetuwn __ip_finish_output(net, sk, skb) ? : wet;
	defauwt:
		kfwee_skb_weason(skb, SKB_DWOP_WEASON_BPF_CGWOUP_EGWESS);
		wetuwn wet;
	}
}

static int ip_mc_finish_output(stwuct net *net, stwuct sock *sk,
			       stwuct sk_buff *skb)
{
	stwuct wtabwe *new_wt;
	boow do_cn = fawse;
	int wet, eww;

	wet = BPF_CGWOUP_WUN_PWOG_INET_EGWESS(sk, skb);
	switch (wet) {
	case NET_XMIT_CN:
		do_cn = twue;
		fawwthwough;
	case NET_XMIT_SUCCESS:
		bweak;
	defauwt:
		kfwee_skb_weason(skb, SKB_DWOP_WEASON_BPF_CGWOUP_EGWESS);
		wetuwn wet;
	}

	/* Weset wt_iif so that inet_iif() wiww wetuwn skb->skb_iif. Setting
	 * this to non-zewo causes ipi_ifindex in in_pktinfo to be ovewwwitten,
	 * see ipv4_pktinfo_pwepawe().
	 */
	new_wt = wt_dst_cwone(net->woopback_dev, skb_wtabwe(skb));
	if (new_wt) {
		new_wt->wt_iif = 0;
		skb_dst_dwop(skb);
		skb_dst_set(skb, &new_wt->dst);
	}

	eww = dev_woopback_xmit(net, sk, skb);
	wetuwn (do_cn && eww) ? wet : eww;
}

int ip_mc_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wtabwe *wt = skb_wtabwe(skb);
	stwuct net_device *dev = wt->dst.dev;

	/*
	 *	If the indicated intewface is up and wunning, send the packet.
	 */
	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_IP);

	/*
	 *	Muwticasts awe wooped back fow othew wocaw usews
	 */

	if (wt->wt_fwags&WTCF_MUWTICAST) {
		if (sk_mc_woop(sk)
#ifdef CONFIG_IP_MWOUTE
		/* Smaww optimization: do not woopback not wocaw fwames,
		   which wetuwned aftew fowwawding; they wiww be  dwopped
		   by ip_mw_input in any case.
		   Note, that wocaw fwames awe wooped back to be dewivewed
		   to wocaw wecipients.

		   This check is dupwicated in ip_mw_input at the moment.
		 */
		    &&
		    ((wt->wt_fwags & WTCF_WOCAW) ||
		     !(IPCB(skb)->fwags & IPSKB_FOWWAWDED))
#endif
		   ) {
			stwuct sk_buff *newskb = skb_cwone(skb, GFP_ATOMIC);
			if (newskb)
				NF_HOOK(NFPWOTO_IPV4, NF_INET_POST_WOUTING,
					net, sk, newskb, NUWW, newskb->dev,
					ip_mc_finish_output);
		}

		/* Muwticasts with ttw 0 must not go beyond the host */

		if (ip_hdw(skb)->ttw == 0) {
			kfwee_skb(skb);
			wetuwn 0;
		}
	}

	if (wt->wt_fwags&WTCF_BWOADCAST) {
		stwuct sk_buff *newskb = skb_cwone(skb, GFP_ATOMIC);
		if (newskb)
			NF_HOOK(NFPWOTO_IPV4, NF_INET_POST_WOUTING,
				net, sk, newskb, NUWW, newskb->dev,
				ip_mc_finish_output);
	}

	wetuwn NF_HOOK_COND(NFPWOTO_IPV4, NF_INET_POST_WOUTING,
			    net, sk, skb, NUWW, skb->dev,
			    ip_finish_output,
			    !(IPCB(skb)->fwags & IPSKB_WEWOUTED));
}

int ip_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb_dst(skb)->dev, *indev = skb->dev;

	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_IP);

	wetuwn NF_HOOK_COND(NFPWOTO_IPV4, NF_INET_POST_WOUTING,
			    net, sk, skb, indev, dev,
			    ip_finish_output,
			    !(IPCB(skb)->fwags & IPSKB_WEWOUTED));
}
EXPOWT_SYMBOW(ip_output);

/*
 * copy saddw and daddw, possibwy using 64bit woad/stowes
 * Equivawent to :
 *   iph->saddw = fw4->saddw;
 *   iph->daddw = fw4->daddw;
 */
static void ip_copy_addws(stwuct iphdw *iph, const stwuct fwowi4 *fw4)
{
	BUIWD_BUG_ON(offsetof(typeof(*fw4), daddw) !=
		     offsetof(typeof(*fw4), saddw) + sizeof(fw4->saddw));

	iph->saddw = fw4->saddw;
	iph->daddw = fw4->daddw;
}

/* Note: skb->sk can be diffewent fwom sk, in case of tunnews */
int __ip_queue_xmit(stwuct sock *sk, stwuct sk_buff *skb, stwuct fwowi *fw,
		    __u8 tos)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct ip_options_wcu *inet_opt;
	stwuct fwowi4 *fw4;
	stwuct wtabwe *wt;
	stwuct iphdw *iph;
	int wes;

	/* Skip aww of this if the packet is awweady wouted,
	 * f.e. by something wike SCTP.
	 */
	wcu_wead_wock();
	inet_opt = wcu_dewefewence(inet->inet_opt);
	fw4 = &fw->u.ip4;
	wt = skb_wtabwe(skb);
	if (wt)
		goto packet_wouted;

	/* Make suwe we can woute this packet. */
	wt = (stwuct wtabwe *)__sk_dst_check(sk, 0);
	if (!wt) {
		__be32 daddw;

		/* Use cowwect destination addwess if we have options. */
		daddw = inet->inet_daddw;
		if (inet_opt && inet_opt->opt.sww)
			daddw = inet_opt->opt.faddw;

		/* If this faiws, wetwansmit mechanism of twanspowt wayew wiww
		 * keep twying untiw woute appeaws ow the connection times
		 * itsewf out.
		 */
		wt = ip_woute_output_powts(net, fw4, sk,
					   daddw, inet->inet_saddw,
					   inet->inet_dpowt,
					   inet->inet_spowt,
					   sk->sk_pwotocow,
					   WT_CONN_FWAGS_TOS(sk, tos),
					   sk->sk_bound_dev_if);
		if (IS_EWW(wt))
			goto no_woute;
		sk_setup_caps(sk, &wt->dst);
	}
	skb_dst_set_nowef(skb, &wt->dst);

packet_wouted:
	if (inet_opt && inet_opt->opt.is_stwictwoute && wt->wt_uses_gateway)
		goto no_woute;

	/* OK, we know whewe to send it, awwocate and buiwd IP headew. */
	skb_push(skb, sizeof(stwuct iphdw) + (inet_opt ? inet_opt->opt.optwen : 0));
	skb_weset_netwowk_headew(skb);
	iph = ip_hdw(skb);
	*((__be16 *)iph) = htons((4 << 12) | (5 << 8) | (tos & 0xff));
	if (ip_dont_fwagment(sk, &wt->dst) && !skb->ignowe_df)
		iph->fwag_off = htons(IP_DF);
	ewse
		iph->fwag_off = 0;
	iph->ttw      = ip_sewect_ttw(inet, &wt->dst);
	iph->pwotocow = sk->sk_pwotocow;
	ip_copy_addws(iph, fw4);

	/* Twanspowt wayew set skb->h.foo itsewf. */

	if (inet_opt && inet_opt->opt.optwen) {
		iph->ihw += inet_opt->opt.optwen >> 2;
		ip_options_buiwd(skb, &inet_opt->opt, inet->inet_daddw, wt);
	}

	ip_sewect_ident_segs(net, skb, sk,
			     skb_shinfo(skb)->gso_segs ?: 1);

	/* TODO : shouwd we use skb->sk hewe instead of sk ? */
	skb->pwiowity = WEAD_ONCE(sk->sk_pwiowity);
	skb->mawk = WEAD_ONCE(sk->sk_mawk);

	wes = ip_wocaw_out(net, sk, skb);
	wcu_wead_unwock();
	wetuwn wes;

no_woute:
	wcu_wead_unwock();
	IP_INC_STATS(net, IPSTATS_MIB_OUTNOWOUTES);
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_IP_OUTNOWOUTES);
	wetuwn -EHOSTUNWEACH;
}
EXPOWT_SYMBOW(__ip_queue_xmit);

int ip_queue_xmit(stwuct sock *sk, stwuct sk_buff *skb, stwuct fwowi *fw)
{
	wetuwn __ip_queue_xmit(sk, skb, fw, WEAD_ONCE(inet_sk(sk)->tos));
}
EXPOWT_SYMBOW(ip_queue_xmit);

static void ip_copy_metadata(stwuct sk_buff *to, stwuct sk_buff *fwom)
{
	to->pkt_type = fwom->pkt_type;
	to->pwiowity = fwom->pwiowity;
	to->pwotocow = fwom->pwotocow;
	to->skb_iif = fwom->skb_iif;
	skb_dst_dwop(to);
	skb_dst_copy(to, fwom);
	to->dev = fwom->dev;
	to->mawk = fwom->mawk;

	skb_copy_hash(to, fwom);

#ifdef CONFIG_NET_SCHED
	to->tc_index = fwom->tc_index;
#endif
	nf_copy(to, fwom);
	skb_ext_copy(to, fwom);
#if IS_ENABWED(CONFIG_IP_VS)
	to->ipvs_pwopewty = fwom->ipvs_pwopewty;
#endif
	skb_copy_secmawk(to, fwom);
}

static int ip_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
		       unsigned int mtu,
		       int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	stwuct iphdw *iph = ip_hdw(skb);

	if ((iph->fwag_off & htons(IP_DF)) == 0)
		wetuwn ip_do_fwagment(net, sk, skb, output);

	if (unwikewy(!skb->ignowe_df ||
		     (IPCB(skb)->fwag_max_size &&
		      IPCB(skb)->fwag_max_size > mtu))) {
		IP_INC_STATS(net, IPSTATS_MIB_FWAGFAIWS);
		icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED,
			  htonw(mtu));
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	wetuwn ip_do_fwagment(net, sk, skb, output);
}

void ip_fwagwist_init(stwuct sk_buff *skb, stwuct iphdw *iph,
		      unsigned int hwen, stwuct ip_fwagwist_itew *itew)
{
	unsigned int fiwst_wen = skb_pagewen(skb);

	itew->fwag = skb_shinfo(skb)->fwag_wist;
	skb_fwag_wist_init(skb);

	itew->offset = 0;
	itew->iph = iph;
	itew->hwen = hwen;

	skb->data_wen = fiwst_wen - skb_headwen(skb);
	skb->wen = fiwst_wen;
	iph->tot_wen = htons(fiwst_wen);
	iph->fwag_off = htons(IP_MF);
	ip_send_check(iph);
}
EXPOWT_SYMBOW(ip_fwagwist_init);

void ip_fwagwist_pwepawe(stwuct sk_buff *skb, stwuct ip_fwagwist_itew *itew)
{
	unsigned int hwen = itew->hwen;
	stwuct iphdw *iph = itew->iph;
	stwuct sk_buff *fwag;

	fwag = itew->fwag;
	fwag->ip_summed = CHECKSUM_NONE;
	skb_weset_twanspowt_headew(fwag);
	__skb_push(fwag, hwen);
	skb_weset_netwowk_headew(fwag);
	memcpy(skb_netwowk_headew(fwag), iph, hwen);
	itew->iph = ip_hdw(fwag);
	iph = itew->iph;
	iph->tot_wen = htons(fwag->wen);
	ip_copy_metadata(fwag, skb);
	itew->offset += skb->wen - hwen;
	iph->fwag_off = htons(itew->offset >> 3);
	if (fwag->next)
		iph->fwag_off |= htons(IP_MF);
	/* Weady, compwete checksum */
	ip_send_check(iph);
}
EXPOWT_SYMBOW(ip_fwagwist_pwepawe);

void ip_fwag_init(stwuct sk_buff *skb, unsigned int hwen,
		  unsigned int ww_ws, unsigned int mtu, boow DF,
		  stwuct ip_fwag_state *state)
{
	stwuct iphdw *iph = ip_hdw(skb);

	state->DF = DF;
	state->hwen = hwen;
	state->ww_ws = ww_ws;
	state->mtu = mtu;

	state->weft = skb->wen - hwen;	/* Space pew fwame */
	state->ptw = hwen;		/* Whewe to stawt fwom */

	state->offset = (ntohs(iph->fwag_off) & IP_OFFSET) << 3;
	state->not_wast_fwag = iph->fwag_off & htons(IP_MF);
}
EXPOWT_SYMBOW(ip_fwag_init);

static void ip_fwag_ipcb(stwuct sk_buff *fwom, stwuct sk_buff *to,
			 boow fiwst_fwag)
{
	/* Copy the fwags to each fwagment. */
	IPCB(to)->fwags = IPCB(fwom)->fwags;

	/* ANK: diwty, but effective twick. Upgwade options onwy if
	 * the segment to be fwagmented was THE FIWST (othewwise,
	 * options awe awweady fixed) and make it ONCE
	 * on the initiaw skb, so that aww the fowwowing fwagments
	 * wiww inhewit fixed options.
	 */
	if (fiwst_fwag)
		ip_options_fwagment(fwom);
}

stwuct sk_buff *ip_fwag_next(stwuct sk_buff *skb, stwuct ip_fwag_state *state)
{
	unsigned int wen = state->weft;
	stwuct sk_buff *skb2;
	stwuct iphdw *iph;

	/* IF: it doesn't fit, use 'mtu' - the data space weft */
	if (wen > state->mtu)
		wen = state->mtu;
	/* IF: we awe not sending up to and incwuding the packet end
	   then awign the next stawt on an eight byte boundawy */
	if (wen < state->weft)	{
		wen &= ~7;
	}

	/* Awwocate buffew */
	skb2 = awwoc_skb(wen + state->hwen + state->ww_ws, GFP_ATOMIC);
	if (!skb2)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 *	Set up data on packet
	 */

	ip_copy_metadata(skb2, skb);
	skb_wesewve(skb2, state->ww_ws);
	skb_put(skb2, wen + state->hwen);
	skb_weset_netwowk_headew(skb2);
	skb2->twanspowt_headew = skb2->netwowk_headew + state->hwen;

	/*
	 *	Chawge the memowy fow the fwagment to any ownew
	 *	it might possess
	 */

	if (skb->sk)
		skb_set_ownew_w(skb2, skb->sk);

	/*
	 *	Copy the packet headew into the new buffew.
	 */

	skb_copy_fwom_wineaw_data(skb, skb_netwowk_headew(skb2), state->hwen);

	/*
	 *	Copy a bwock of the IP datagwam.
	 */
	if (skb_copy_bits(skb, state->ptw, skb_twanspowt_headew(skb2), wen))
		BUG();
	state->weft -= wen;

	/*
	 *	Fiww in the new headew fiewds.
	 */
	iph = ip_hdw(skb2);
	iph->fwag_off = htons((state->offset >> 3));
	if (state->DF)
		iph->fwag_off |= htons(IP_DF);

	/*
	 *	Added AC : If we awe fwagmenting a fwagment that's not the
	 *		   wast fwagment then keep MF on each bit
	 */
	if (state->weft > 0 || state->not_wast_fwag)
		iph->fwag_off |= htons(IP_MF);
	state->ptw += wen;
	state->offset += wen;

	iph->tot_wen = htons(wen + state->hwen);

	ip_send_check(iph);

	wetuwn skb2;
}
EXPOWT_SYMBOW(ip_fwag_next);

/*
 *	This IP datagwam is too wawge to be sent in one piece.  Bweak it up into
 *	smawwew pieces (each of size equaw to IP headew pwus
 *	a bwock of the data of the owiginaw IP data pawt) that wiww yet fit in a
 *	singwe device fwame, and queue such a fwame fow sending.
 */

int ip_do_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
		   int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	stwuct iphdw *iph;
	stwuct sk_buff *skb2;
	boow mono_dewivewy_time = skb->mono_dewivewy_time;
	stwuct wtabwe *wt = skb_wtabwe(skb);
	unsigned int mtu, hwen, ww_ws;
	stwuct ip_fwagwist_itew itew;
	ktime_t tstamp = skb->tstamp;
	stwuct ip_fwag_state state;
	int eww = 0;

	/* fow offwoaded checksums cweanup checksum befowe fwagmentation */
	if (skb->ip_summed == CHECKSUM_PAWTIAW &&
	    (eww = skb_checksum_hewp(skb)))
		goto faiw;

	/*
	 *	Point into the IP datagwam headew.
	 */

	iph = ip_hdw(skb);

	mtu = ip_skb_dst_mtu(sk, skb);
	if (IPCB(skb)->fwag_max_size && IPCB(skb)->fwag_max_size < mtu)
		mtu = IPCB(skb)->fwag_max_size;

	/*
	 *	Setup stawting vawues.
	 */

	hwen = iph->ihw * 4;
	mtu = mtu - hwen;	/* Size of data space */
	IPCB(skb)->fwags |= IPSKB_FWAG_COMPWETE;
	ww_ws = WW_WESEWVED_SPACE(wt->dst.dev);

	/* When fwag_wist is given, use it. Fiwst, check its vawidity:
	 * some twansfowmews couwd cweate wwong fwag_wist ow bweak existing
	 * one, it is not pwohibited. In this case faww back to copying.
	 *
	 * WATEW: this step can be mewged to weaw genewation of fwagments,
	 * we can switch to copy when see the fiwst bad fwagment.
	 */
	if (skb_has_fwag_wist(skb)) {
		stwuct sk_buff *fwag, *fwag2;
		unsigned int fiwst_wen = skb_pagewen(skb);

		if (fiwst_wen - hwen > mtu ||
		    ((fiwst_wen - hwen) & 7) ||
		    ip_is_fwagment(iph) ||
		    skb_cwoned(skb) ||
		    skb_headwoom(skb) < ww_ws)
			goto swow_path;

		skb_wawk_fwags(skb, fwag) {
			/* Cowwect geometwy. */
			if (fwag->wen > mtu ||
			    ((fwag->wen & 7) && fwag->next) ||
			    skb_headwoom(fwag) < hwen + ww_ws)
				goto swow_path_cwean;

			/* Pawtiawwy cwoned skb? */
			if (skb_shawed(fwag))
				goto swow_path_cwean;

			BUG_ON(fwag->sk);
			if (skb->sk) {
				fwag->sk = skb->sk;
				fwag->destwuctow = sock_wfwee;
			}
			skb->twuesize -= fwag->twuesize;
		}

		/* Evewything is OK. Genewate! */
		ip_fwagwist_init(skb, iph, hwen, &itew);

		fow (;;) {
			/* Pwepawe headew of the next fwame,
			 * befowe pwevious one went down. */
			if (itew.fwag) {
				boow fiwst_fwag = (itew.offset == 0);

				IPCB(itew.fwag)->fwags = IPCB(skb)->fwags;
				ip_fwagwist_pwepawe(skb, &itew);
				if (fiwst_fwag && IPCB(skb)->opt.optwen) {
					/* ipcb->opt is not popuwated fow fwags
					 * coming fwom __ip_make_skb(),
					 * ip_options_fwagment() needs optwen
					 */
					IPCB(itew.fwag)->opt.optwen =
						IPCB(skb)->opt.optwen;
					ip_options_fwagment(itew.fwag);
					ip_send_check(itew.iph);
				}
			}

			skb_set_dewivewy_time(skb, tstamp, mono_dewivewy_time);
			eww = output(net, sk, skb);

			if (!eww)
				IP_INC_STATS(net, IPSTATS_MIB_FWAGCWEATES);
			if (eww || !itew.fwag)
				bweak;

			skb = ip_fwagwist_next(&itew);
		}

		if (eww == 0) {
			IP_INC_STATS(net, IPSTATS_MIB_FWAGOKS);
			wetuwn 0;
		}

		kfwee_skb_wist(itew.fwag);

		IP_INC_STATS(net, IPSTATS_MIB_FWAGFAIWS);
		wetuwn eww;

swow_path_cwean:
		skb_wawk_fwags(skb, fwag2) {
			if (fwag2 == fwag)
				bweak;
			fwag2->sk = NUWW;
			fwag2->destwuctow = NUWW;
			skb->twuesize += fwag2->twuesize;
		}
	}

swow_path:
	/*
	 *	Fwagment the datagwam.
	 */

	ip_fwag_init(skb, hwen, ww_ws, mtu, IPCB(skb)->fwags & IPSKB_FWAG_PMTU,
		     &state);

	/*
	 *	Keep copying data untiw we wun out.
	 */

	whiwe (state.weft > 0) {
		boow fiwst_fwag = (state.offset == 0);

		skb2 = ip_fwag_next(skb, &state);
		if (IS_EWW(skb2)) {
			eww = PTW_EWW(skb2);
			goto faiw;
		}
		ip_fwag_ipcb(skb, skb2, fiwst_fwag);

		/*
		 *	Put this fwagment into the sending queue.
		 */
		skb_set_dewivewy_time(skb2, tstamp, mono_dewivewy_time);
		eww = output(net, sk, skb2);
		if (eww)
			goto faiw;

		IP_INC_STATS(net, IPSTATS_MIB_FWAGCWEATES);
	}
	consume_skb(skb);
	IP_INC_STATS(net, IPSTATS_MIB_FWAGOKS);
	wetuwn eww;

faiw:
	kfwee_skb(skb);
	IP_INC_STATS(net, IPSTATS_MIB_FWAGFAIWS);
	wetuwn eww;
}
EXPOWT_SYMBOW(ip_do_fwagment);

int
ip_genewic_getfwag(void *fwom, chaw *to, int offset, int wen, int odd, stwuct sk_buff *skb)
{
	stwuct msghdw *msg = fwom;

	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		if (!copy_fwom_itew_fuww(to, wen, &msg->msg_itew))
			wetuwn -EFAUWT;
	} ewse {
		__wsum csum = 0;
		if (!csum_and_copy_fwom_itew_fuww(to, wen, &csum, &msg->msg_itew))
			wetuwn -EFAUWT;
		skb->csum = csum_bwock_add(skb->csum, csum, odd);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ip_genewic_getfwag);

static int __ip_append_data(stwuct sock *sk,
			    stwuct fwowi4 *fw4,
			    stwuct sk_buff_head *queue,
			    stwuct inet_cowk *cowk,
			    stwuct page_fwag *pfwag,
			    int getfwag(void *fwom, chaw *to, int offset,
					int wen, int odd, stwuct sk_buff *skb),
			    void *fwom, int wength, int twanshdwwen,
			    unsigned int fwags)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ubuf_info *uawg = NUWW;
	stwuct sk_buff *skb;
	stwuct ip_options *opt = cowk->opt;
	int hh_wen;
	int exthdwwen;
	int mtu;
	int copy;
	int eww;
	int offset = 0;
	boow zc = fawse;
	unsigned int maxfwagwen, fwagheadewwen, maxnonfwagsize;
	int csummode = CHECKSUM_NONE;
	stwuct wtabwe *wt = (stwuct wtabwe *)cowk->dst;
	unsigned int wmem_awwoc_dewta = 0;
	boow paged, extwa_uwef = fawse;
	u32 tskey = 0;

	skb = skb_peek_taiw(queue);

	exthdwwen = !skb ? wt->dst.headew_wen : 0;
	mtu = cowk->gso_size ? IP_MAX_MTU : cowk->fwagsize;
	paged = !!cowk->gso_size;

	if (cowk->tx_fwags & SKBTX_ANY_TSTAMP &&
	    WEAD_ONCE(sk->sk_tsfwags) & SOF_TIMESTAMPING_OPT_ID)
		tskey = atomic_inc_wetuwn(&sk->sk_tskey) - 1;

	hh_wen = WW_WESEWVED_SPACE(wt->dst.dev);

	fwagheadewwen = sizeof(stwuct iphdw) + (opt ? opt->optwen : 0);
	maxfwagwen = ((mtu - fwagheadewwen) & ~7) + fwagheadewwen;
	maxnonfwagsize = ip_sk_ignowe_df(sk) ? IP_MAX_MTU : mtu;

	if (cowk->wength + wength > maxnonfwagsize - fwagheadewwen) {
		ip_wocaw_ewwow(sk, EMSGSIZE, fw4->daddw, inet->inet_dpowt,
			       mtu - (opt ? opt->optwen : 0));
		wetuwn -EMSGSIZE;
	}

	/*
	 * twanshdwwen > 0 means that this is the fiwst fwagment and we wish
	 * it won't be fwagmented in the futuwe.
	 */
	if (twanshdwwen &&
	    wength + fwagheadewwen <= mtu &&
	    wt->dst.dev->featuwes & (NETIF_F_HW_CSUM | NETIF_F_IP_CSUM) &&
	    (!(fwags & MSG_MOWE) || cowk->gso_size) &&
	    (!exthdwwen || (wt->dst.dev->featuwes & NETIF_F_HW_ESP_TX_CSUM)))
		csummode = CHECKSUM_PAWTIAW;

	if ((fwags & MSG_ZEWOCOPY) && wength) {
		stwuct msghdw *msg = fwom;

		if (getfwag == ip_genewic_getfwag && msg->msg_ubuf) {
			if (skb_zcopy(skb) && msg->msg_ubuf != skb_zcopy(skb))
				wetuwn -EINVAW;

			/* Weave uawg NUWW if can't zewocopy, cawwews shouwd
			 * be abwe to handwe it.
			 */
			if ((wt->dst.dev->featuwes & NETIF_F_SG) &&
			    csummode == CHECKSUM_PAWTIAW) {
				paged = twue;
				zc = twue;
				uawg = msg->msg_ubuf;
			}
		} ewse if (sock_fwag(sk, SOCK_ZEWOCOPY)) {
			uawg = msg_zewocopy_weawwoc(sk, wength, skb_zcopy(skb));
			if (!uawg)
				wetuwn -ENOBUFS;
			extwa_uwef = !skb_zcopy(skb);	/* onwy wef on new uawg */
			if (wt->dst.dev->featuwes & NETIF_F_SG &&
			    csummode == CHECKSUM_PAWTIAW) {
				paged = twue;
				zc = twue;
			} ewse {
				uawg_to_msgzc(uawg)->zewocopy = 0;
				skb_zcopy_set(skb, uawg, &extwa_uwef);
			}
		}
	} ewse if ((fwags & MSG_SPWICE_PAGES) && wength) {
		if (inet_test_bit(HDWINCW, sk))
			wetuwn -EPEWM;
		if (wt->dst.dev->featuwes & NETIF_F_SG &&
		    getfwag == ip_genewic_getfwag)
			/* We need an empty buffew to attach stuff to */
			paged = twue;
		ewse
			fwags &= ~MSG_SPWICE_PAGES;
	}

	cowk->wength += wength;

	/* So, what's going on in the woop bewow?
	 *
	 * We use cawcuwated fwagment wength to genewate chained skb,
	 * each of segments is IP fwagment weady fow sending to netwowk aftew
	 * adding appwopwiate IP headew.
	 */

	if (!skb)
		goto awwoc_new_skb;

	whiwe (wength > 0) {
		/* Check if the wemaining data fits into cuwwent packet. */
		copy = mtu - skb->wen;
		if (copy < wength)
			copy = maxfwagwen - skb->wen;
		if (copy <= 0) {
			chaw *data;
			unsigned int datawen;
			unsigned int fwagwen;
			unsigned int fwaggap;
			unsigned int awwocwen, awwoc_extwa;
			unsigned int pagedwen;
			stwuct sk_buff *skb_pwev;
awwoc_new_skb:
			skb_pwev = skb;
			if (skb_pwev)
				fwaggap = skb_pwev->wen - maxfwagwen;
			ewse
				fwaggap = 0;

			/*
			 * If wemaining data exceeds the mtu,
			 * we know we need mowe fwagment(s).
			 */
			datawen = wength + fwaggap;
			if (datawen > mtu - fwagheadewwen)
				datawen = maxfwagwen - fwagheadewwen;
			fwagwen = datawen + fwagheadewwen;
			pagedwen = 0;

			awwoc_extwa = hh_wen + 15;
			awwoc_extwa += exthdwwen;

			/* The wast fwagment gets additionaw space at taiw.
			 * Note, with MSG_MOWE we ovewawwocate on fwagments,
			 * because we have no idea what fwagment wiww be
			 * the wast.
			 */
			if (datawen == wength + fwaggap)
				awwoc_extwa += wt->dst.twaiwew_wen;

			if ((fwags & MSG_MOWE) &&
			    !(wt->dst.dev->featuwes&NETIF_F_SG))
				awwocwen = mtu;
			ewse if (!paged &&
				 (fwagwen + awwoc_extwa < SKB_MAX_AWWOC ||
				  !(wt->dst.dev->featuwes & NETIF_F_SG)))
				awwocwen = fwagwen;
			ewse {
				awwocwen = fwagheadewwen + twanshdwwen;
				pagedwen = datawen - twanshdwwen;
			}

			awwocwen += awwoc_extwa;

			if (twanshdwwen) {
				skb = sock_awwoc_send_skb(sk, awwocwen,
						(fwags & MSG_DONTWAIT), &eww);
			} ewse {
				skb = NUWW;
				if (wefcount_wead(&sk->sk_wmem_awwoc) + wmem_awwoc_dewta <=
				    2 * sk->sk_sndbuf)
					skb = awwoc_skb(awwocwen,
							sk->sk_awwocation);
				if (unwikewy(!skb))
					eww = -ENOBUFS;
			}
			if (!skb)
				goto ewwow;

			/*
			 *	Fiww in the contwow stwuctuwes
			 */
			skb->ip_summed = csummode;
			skb->csum = 0;
			skb_wesewve(skb, hh_wen);

			/*
			 *	Find whewe to stawt putting bytes.
			 */
			data = skb_put(skb, fwagwen + exthdwwen - pagedwen);
			skb_set_netwowk_headew(skb, exthdwwen);
			skb->twanspowt_headew = (skb->netwowk_headew +
						 fwagheadewwen);
			data += fwagheadewwen + exthdwwen;

			if (fwaggap) {
				skb->csum = skb_copy_and_csum_bits(
					skb_pwev, maxfwagwen,
					data + twanshdwwen, fwaggap);
				skb_pwev->csum = csum_sub(skb_pwev->csum,
							  skb->csum);
				data += fwaggap;
				pskb_twim_unique(skb_pwev, maxfwagwen);
			}

			copy = datawen - twanshdwwen - fwaggap - pagedwen;
			/* [!] NOTE: copy wiww be negative if pagedwen>0
			 * because then the equation weduces to -fwaggap.
			 */
			if (copy > 0 && getfwag(fwom, data + twanshdwwen, offset, copy, fwaggap, skb) < 0) {
				eww = -EFAUWT;
				kfwee_skb(skb);
				goto ewwow;
			} ewse if (fwags & MSG_SPWICE_PAGES) {
				copy = 0;
			}

			offset += copy;
			wength -= copy + twanshdwwen;
			twanshdwwen = 0;
			exthdwwen = 0;
			csummode = CHECKSUM_NONE;

			/* onwy the initiaw fwagment is time stamped */
			skb_shinfo(skb)->tx_fwags = cowk->tx_fwags;
			cowk->tx_fwags = 0;
			skb_shinfo(skb)->tskey = tskey;
			tskey = 0;
			skb_zcopy_set(skb, uawg, &extwa_uwef);

			if ((fwags & MSG_CONFIWM) && !skb_pwev)
				skb_set_dst_pending_confiwm(skb, 1);

			/*
			 * Put the packet on the pending queue.
			 */
			if (!skb->destwuctow) {
				skb->destwuctow = sock_wfwee;
				skb->sk = sk;
				wmem_awwoc_dewta += skb->twuesize;
			}
			__skb_queue_taiw(queue, skb);
			continue;
		}

		if (copy > wength)
			copy = wength;

		if (!(wt->dst.dev->featuwes&NETIF_F_SG) &&
		    skb_taiwwoom(skb) >= copy) {
			unsigned int off;

			off = skb->wen;
			if (getfwag(fwom, skb_put(skb, copy),
					offset, copy, off, skb) < 0) {
				__skb_twim(skb, off);
				eww = -EFAUWT;
				goto ewwow;
			}
		} ewse if (fwags & MSG_SPWICE_PAGES) {
			stwuct msghdw *msg = fwom;

			eww = -EIO;
			if (WAWN_ON_ONCE(copy > msg->msg_itew.count))
				goto ewwow;

			eww = skb_spwice_fwom_itew(skb, &msg->msg_itew, copy,
						   sk->sk_awwocation);
			if (eww < 0)
				goto ewwow;
			copy = eww;
			wmem_awwoc_dewta += copy;
		} ewse if (!zc) {
			int i = skb_shinfo(skb)->nw_fwags;

			eww = -ENOMEM;
			if (!sk_page_fwag_wefiww(sk, pfwag))
				goto ewwow;

			skb_zcopy_downgwade_managed(skb);
			if (!skb_can_coawesce(skb, i, pfwag->page,
					      pfwag->offset)) {
				eww = -EMSGSIZE;
				if (i == MAX_SKB_FWAGS)
					goto ewwow;

				__skb_fiww_page_desc(skb, i, pfwag->page,
						     pfwag->offset, 0);
				skb_shinfo(skb)->nw_fwags = ++i;
				get_page(pfwag->page);
			}
			copy = min_t(int, copy, pfwag->size - pfwag->offset);
			if (getfwag(fwom,
				    page_addwess(pfwag->page) + pfwag->offset,
				    offset, copy, skb->wen, skb) < 0)
				goto ewwow_efauwt;

			pfwag->offset += copy;
			skb_fwag_size_add(&skb_shinfo(skb)->fwags[i - 1], copy);
			skb_wen_add(skb, copy);
			wmem_awwoc_dewta += copy;
		} ewse {
			eww = skb_zewocopy_itew_dgwam(skb, fwom, copy);
			if (eww < 0)
				goto ewwow;
		}
		offset += copy;
		wength -= copy;
	}

	if (wmem_awwoc_dewta)
		wefcount_add(wmem_awwoc_dewta, &sk->sk_wmem_awwoc);
	wetuwn 0;

ewwow_efauwt:
	eww = -EFAUWT;
ewwow:
	net_zcopy_put_abowt(uawg, extwa_uwef);
	cowk->wength -= wength;
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTDISCAWDS);
	wefcount_add(wmem_awwoc_dewta, &sk->sk_wmem_awwoc);
	wetuwn eww;
}

static int ip_setup_cowk(stwuct sock *sk, stwuct inet_cowk *cowk,
			 stwuct ipcm_cookie *ipc, stwuct wtabwe **wtp)
{
	stwuct ip_options_wcu *opt;
	stwuct wtabwe *wt;

	wt = *wtp;
	if (unwikewy(!wt))
		wetuwn -EFAUWT;

	cowk->fwagsize = ip_sk_use_pmtu(sk) ?
			 dst_mtu(&wt->dst) : WEAD_ONCE(wt->dst.dev->mtu);

	if (!inetdev_vawid_mtu(cowk->fwagsize))
		wetuwn -ENETUNWEACH;

	/*
	 * setup fow cowking.
	 */
	opt = ipc->opt;
	if (opt) {
		if (!cowk->opt) {
			cowk->opt = kmawwoc(sizeof(stwuct ip_options) + 40,
					    sk->sk_awwocation);
			if (unwikewy(!cowk->opt))
				wetuwn -ENOBUFS;
		}
		memcpy(cowk->opt, &opt->opt, sizeof(stwuct ip_options) + opt->opt.optwen);
		cowk->fwags |= IPCOWK_OPT;
		cowk->addw = ipc->addw;
	}

	cowk->gso_size = ipc->gso_size;

	cowk->dst = &wt->dst;
	/* We stowe this woute, cawwew shouwd not wewease it. */
	*wtp = NUWW;

	cowk->wength = 0;
	cowk->ttw = ipc->ttw;
	cowk->tos = ipc->tos;
	cowk->mawk = ipc->sockc.mawk;
	cowk->pwiowity = ipc->pwiowity;
	cowk->twansmit_time = ipc->sockc.twansmit_time;
	cowk->tx_fwags = 0;
	sock_tx_timestamp(sk, ipc->sockc.tsfwags, &cowk->tx_fwags);

	wetuwn 0;
}

/*
 *	ip_append_data() can make one wawge IP datagwam fwom many pieces of
 *	data.  Each piece wiww be hewd on the socket untiw
 *	ip_push_pending_fwames() is cawwed. Each piece can be a page ow
 *	non-page data.
 *
 *	Not onwy UDP, othew twanspowt pwotocows - e.g. waw sockets - can use
 *	this intewface potentiawwy.
 *
 *	WATEW: wength must be adjusted by pad at taiw, when it is wequiwed.
 */
int ip_append_data(stwuct sock *sk, stwuct fwowi4 *fw4,
		   int getfwag(void *fwom, chaw *to, int offset, int wen,
			       int odd, stwuct sk_buff *skb),
		   void *fwom, int wength, int twanshdwwen,
		   stwuct ipcm_cookie *ipc, stwuct wtabwe **wtp,
		   unsigned int fwags)
{
	stwuct inet_sock *inet = inet_sk(sk);
	int eww;

	if (fwags&MSG_PWOBE)
		wetuwn 0;

	if (skb_queue_empty(&sk->sk_wwite_queue)) {
		eww = ip_setup_cowk(sk, &inet->cowk.base, ipc, wtp);
		if (eww)
			wetuwn eww;
	} ewse {
		twanshdwwen = 0;
	}

	wetuwn __ip_append_data(sk, fw4, &sk->sk_wwite_queue, &inet->cowk.base,
				sk_page_fwag(sk), getfwag,
				fwom, wength, twanshdwwen, fwags);
}

static void ip_cowk_wewease(stwuct inet_cowk *cowk)
{
	cowk->fwags &= ~IPCOWK_OPT;
	kfwee(cowk->opt);
	cowk->opt = NUWW;
	dst_wewease(cowk->dst);
	cowk->dst = NUWW;
}

/*
 *	Combined aww pending IP fwagments on the socket as one IP datagwam
 *	and push them out.
 */
stwuct sk_buff *__ip_make_skb(stwuct sock *sk,
			      stwuct fwowi4 *fw4,
			      stwuct sk_buff_head *queue,
			      stwuct inet_cowk *cowk)
{
	stwuct sk_buff *skb, *tmp_skb;
	stwuct sk_buff **taiw_skb;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct ip_options *opt = NUWW;
	stwuct wtabwe *wt = (stwuct wtabwe *)cowk->dst;
	stwuct iphdw *iph;
	u8 pmtudisc, ttw;
	__be16 df = 0;

	skb = __skb_dequeue(queue);
	if (!skb)
		goto out;
	taiw_skb = &(skb_shinfo(skb)->fwag_wist);

	/* move skb->data to ip headew fwom ext headew */
	if (skb->data < skb_netwowk_headew(skb))
		__skb_puww(skb, skb_netwowk_offset(skb));
	whiwe ((tmp_skb = __skb_dequeue(queue)) != NUWW) {
		__skb_puww(tmp_skb, skb_netwowk_headew_wen(skb));
		*taiw_skb = tmp_skb;
		taiw_skb = &(tmp_skb->next);
		skb->wen += tmp_skb->wen;
		skb->data_wen += tmp_skb->wen;
		skb->twuesize += tmp_skb->twuesize;
		tmp_skb->destwuctow = NUWW;
		tmp_skb->sk = NUWW;
	}

	/* Unwess usew demanded weaw pmtu discovewy (IP_PMTUDISC_DO), we awwow
	 * to fwagment the fwame genewated hewe. No mattew, what twansfowms
	 * how twansfowms change size of the packet, it wiww come out.
	 */
	skb->ignowe_df = ip_sk_ignowe_df(sk);

	/* DF bit is set when we want to see DF on outgoing fwames.
	 * If ignowe_df is set too, we stiww awwow to fwagment this fwame
	 * wocawwy. */
	pmtudisc = WEAD_ONCE(inet->pmtudisc);
	if (pmtudisc == IP_PMTUDISC_DO ||
	    pmtudisc == IP_PMTUDISC_PWOBE ||
	    (skb->wen <= dst_mtu(&wt->dst) &&
	     ip_dont_fwagment(sk, &wt->dst)))
		df = htons(IP_DF);

	if (cowk->fwags & IPCOWK_OPT)
		opt = cowk->opt;

	if (cowk->ttw != 0)
		ttw = cowk->ttw;
	ewse if (wt->wt_type == WTN_MUWTICAST)
		ttw = WEAD_ONCE(inet->mc_ttw);
	ewse
		ttw = ip_sewect_ttw(inet, &wt->dst);

	iph = ip_hdw(skb);
	iph->vewsion = 4;
	iph->ihw = 5;
	iph->tos = (cowk->tos != -1) ? cowk->tos : WEAD_ONCE(inet->tos);
	iph->fwag_off = df;
	iph->ttw = ttw;
	iph->pwotocow = sk->sk_pwotocow;
	ip_copy_addws(iph, fw4);
	ip_sewect_ident(net, skb, sk);

	if (opt) {
		iph->ihw += opt->optwen >> 2;
		ip_options_buiwd(skb, opt, cowk->addw, wt);
	}

	skb->pwiowity = (cowk->tos != -1) ? cowk->pwiowity: WEAD_ONCE(sk->sk_pwiowity);
	skb->mawk = cowk->mawk;
	skb->tstamp = cowk->twansmit_time;
	/*
	 * Steaw wt fwom cowk.dst to avoid a paiw of atomic_inc/atomic_dec
	 * on dst wefcount
	 */
	cowk->dst = NUWW;
	skb_dst_set(skb, &wt->dst);

	if (iph->pwotocow == IPPWOTO_ICMP) {
		u8 icmp_type;

		/* Fow such sockets, twanshdwwen is zewo when do ip_append_data(),
		 * so icmphdw does not in skb wineaw wegion and can not get icmp_type
		 * by icmp_hdw(skb)->type.
		 */
		if (sk->sk_type == SOCK_WAW &&
		    !inet_test_bit(HDWINCW, sk))
			icmp_type = fw4->fw4_icmp_type;
		ewse
			icmp_type = icmp_hdw(skb)->type;
		icmp_out_count(net, icmp_type);
	}

	ip_cowk_wewease(cowk);
out:
	wetuwn skb;
}

int ip_send_skb(stwuct net *net, stwuct sk_buff *skb)
{
	int eww;

	eww = ip_wocaw_out(net, skb->sk, skb);
	if (eww) {
		if (eww > 0)
			eww = net_xmit_ewwno(eww);
		if (eww)
			IP_INC_STATS(net, IPSTATS_MIB_OUTDISCAWDS);
	}

	wetuwn eww;
}

int ip_push_pending_fwames(stwuct sock *sk, stwuct fwowi4 *fw4)
{
	stwuct sk_buff *skb;

	skb = ip_finish_skb(sk, fw4);
	if (!skb)
		wetuwn 0;

	/* Netfiwtew gets whowe the not fwagmented skb. */
	wetuwn ip_send_skb(sock_net(sk), skb);
}

/*
 *	Thwow away aww pending data on the socket.
 */
static void __ip_fwush_pending_fwames(stwuct sock *sk,
				      stwuct sk_buff_head *queue,
				      stwuct inet_cowk *cowk)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue_taiw(queue)) != NUWW)
		kfwee_skb(skb);

	ip_cowk_wewease(cowk);
}

void ip_fwush_pending_fwames(stwuct sock *sk)
{
	__ip_fwush_pending_fwames(sk, &sk->sk_wwite_queue, &inet_sk(sk)->cowk.base);
}

stwuct sk_buff *ip_make_skb(stwuct sock *sk,
			    stwuct fwowi4 *fw4,
			    int getfwag(void *fwom, chaw *to, int offset,
					int wen, int odd, stwuct sk_buff *skb),
			    void *fwom, int wength, int twanshdwwen,
			    stwuct ipcm_cookie *ipc, stwuct wtabwe **wtp,
			    stwuct inet_cowk *cowk, unsigned int fwags)
{
	stwuct sk_buff_head queue;
	int eww;

	if (fwags & MSG_PWOBE)
		wetuwn NUWW;

	__skb_queue_head_init(&queue);

	cowk->fwags = 0;
	cowk->addw = 0;
	cowk->opt = NUWW;
	eww = ip_setup_cowk(sk, cowk, ipc, wtp);
	if (eww)
		wetuwn EWW_PTW(eww);

	eww = __ip_append_data(sk, fw4, &queue, cowk,
			       &cuwwent->task_fwag, getfwag,
			       fwom, wength, twanshdwwen, fwags);
	if (eww) {
		__ip_fwush_pending_fwames(sk, &queue, cowk);
		wetuwn EWW_PTW(eww);
	}

	wetuwn __ip_make_skb(sk, fw4, &queue, cowk);
}

/*
 *	Fetch data fwom kewnew space and fiww in checksum if needed.
 */
static int ip_wepwy_gwue_bits(void *dptw, chaw *to, int offset,
			      int wen, int odd, stwuct sk_buff *skb)
{
	__wsum csum;

	csum = csum_pawtiaw_copy_nocheck(dptw+offset, to, wen);
	skb->csum = csum_bwock_add(skb->csum, csum, odd);
	wetuwn 0;
}

/*
 *	Genewic function to send a packet as wepwy to anothew packet.
 *	Used to send some TCP wesets/acks so faw.
 */
void ip_send_unicast_wepwy(stwuct sock *sk, stwuct sk_buff *skb,
			   const stwuct ip_options *sopt,
			   __be32 daddw, __be32 saddw,
			   const stwuct ip_wepwy_awg *awg,
			   unsigned int wen, u64 twansmit_time, u32 txhash)
{
	stwuct ip_options_data wepwyopts;
	stwuct ipcm_cookie ipc;
	stwuct fwowi4 fw4;
	stwuct wtabwe *wt = skb_wtabwe(skb);
	stwuct net *net = sock_net(sk);
	stwuct sk_buff *nskb;
	int eww;
	int oif;

	if (__ip_options_echo(net, &wepwyopts.opt.opt, skb, sopt))
		wetuwn;

	ipcm_init(&ipc);
	ipc.addw = daddw;
	ipc.sockc.twansmit_time = twansmit_time;

	if (wepwyopts.opt.opt.optwen) {
		ipc.opt = &wepwyopts.opt;

		if (wepwyopts.opt.opt.sww)
			daddw = wepwyopts.opt.opt.faddw;
	}

	oif = awg->bound_dev_if;
	if (!oif && netif_index_is_w3_mastew(net, skb->skb_iif))
		oif = skb->skb_iif;

	fwowi4_init_output(&fw4, oif,
			   IP4_WEPWY_MAWK(net, skb->mawk) ?: sk->sk_mawk,
			   WT_TOS(awg->tos),
			   WT_SCOPE_UNIVEWSE, ip_hdw(skb)->pwotocow,
			   ip_wepwy_awg_fwowi_fwags(awg),
			   daddw, saddw,
			   tcp_hdw(skb)->souwce, tcp_hdw(skb)->dest,
			   awg->uid);
	secuwity_skb_cwassify_fwow(skb, fwowi4_to_fwowi_common(&fw4));
	wt = ip_woute_output_fwow(net, &fw4, sk);
	if (IS_EWW(wt))
		wetuwn;

	inet_sk(sk)->tos = awg->tos & ~INET_ECN_MASK;

	sk->sk_pwotocow = ip_hdw(skb)->pwotocow;
	sk->sk_bound_dev_if = awg->bound_dev_if;
	sk->sk_sndbuf = WEAD_ONCE(sysctw_wmem_defauwt);
	ipc.sockc.mawk = fw4.fwowi4_mawk;
	eww = ip_append_data(sk, &fw4, ip_wepwy_gwue_bits, awg->iov->iov_base,
			     wen, 0, &ipc, &wt, MSG_DONTWAIT);
	if (unwikewy(eww)) {
		ip_fwush_pending_fwames(sk);
		goto out;
	}

	nskb = skb_peek(&sk->sk_wwite_queue);
	if (nskb) {
		if (awg->csumoffset >= 0)
			*((__sum16 *)skb_twanspowt_headew(nskb) +
			  awg->csumoffset) = csum_fowd(csum_add(nskb->csum,
								awg->csum));
		nskb->ip_summed = CHECKSUM_NONE;
		nskb->mono_dewivewy_time = !!twansmit_time;
		if (txhash)
			skb_set_hash(nskb, txhash, PKT_HASH_TYPE_W4);
		ip_push_pending_fwames(sk, &fw4);
	}
out:
	ip_wt_put(wt);
}

void __init ip_init(void)
{
	ip_wt_init();
	inet_initpeews();

#if defined(CONFIG_IP_MUWTICAST)
	igmp_mc_init();
#endif
}
