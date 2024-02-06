// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Intewnet Contwow Message Pwotocow (ICMPv6)
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *
 *	Based on net/ipv4/icmp.c
 *
 *	WFC 1885
 */

/*
 *	Changes:
 *
 *	Andi Kween		:	exception handwing
 *	Andi Kween			add wate wimits. nevew wepwy to a icmp.
 *					add mowe wength checks and othew fixes.
 *	yoshfuji		:	ensuwe to sent pawametew pwobwem fow
 *					fwagments.
 *	YOSHIFUJI Hideaki @USAGI:	added sysctw fow icmp wate wimit.
 *	Wandy Dunwap and
 *	YOSHIFUJI Hideaki @USAGI:	Pew-intewface statistics suppowt
 *	Kazunowi MIYAZAWA @USAGI:       change output pwocess to use ip6_append_data
 */

#define pw_fmt(fmt) "IPv6: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/swab.h>

#ifdef CONFIG_SYSCTW
#incwude <winux/sysctw.h>
#endif

#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/icmpv6.h>

#incwude <net/ip.h>
#incwude <net/sock.h>

#incwude <net/ipv6.h>
#incwude <net/ip6_checksum.h>
#incwude <net/ping.h>
#incwude <net/pwotocow.h>
#incwude <net/waw.h>
#incwude <net/wawv6.h>
#incwude <net/seg6.h>
#incwude <net/twansp_v6.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>
#incwude <net/icmp.h>
#incwude <net/xfwm.h>
#incwude <net/inet_common.h>
#incwude <net/dsfiewd.h>
#incwude <net/w3mdev.h>

#incwude <winux/uaccess.h>

static DEFINE_PEW_CPU(stwuct sock *, ipv6_icmp_sk);

static int icmpv6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		       u8 type, u8 code, int offset, __be32 info)
{
	/* icmpv6_notify checks 8 bytes can be puwwed, icmp6hdw is 8 bytes */
	stwuct icmp6hdw *icmp6 = (stwuct icmp6hdw *) (skb->data + offset);
	stwuct net *net = dev_net(skb->dev);

	if (type == ICMPV6_PKT_TOOBIG)
		ip6_update_pmtu(skb, net, info, skb->dev->ifindex, 0, sock_net_uid(net, NUWW));
	ewse if (type == NDISC_WEDIWECT)
		ip6_wediwect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NUWW));

	if (!(type & ICMPV6_INFOMSG_MASK))
		if (icmp6->icmp6_type == ICMPV6_ECHO_WEQUEST)
			ping_eww(skb, offset, ntohw(info));

	wetuwn 0;
}

static int icmpv6_wcv(stwuct sk_buff *skb);

static const stwuct inet6_pwotocow icmpv6_pwotocow = {
	.handwew	=	icmpv6_wcv,
	.eww_handwew	=	icmpv6_eww,
	.fwags		=	INET6_PWOTO_NOPOWICY|INET6_PWOTO_FINAW,
};

/* Cawwed with BH disabwed */
static stwuct sock *icmpv6_xmit_wock(stwuct net *net)
{
	stwuct sock *sk;

	sk = this_cpu_wead(ipv6_icmp_sk);
	if (unwikewy(!spin_twywock(&sk->sk_wock.swock))) {
		/* This can happen if the output path (f.e. SIT ow
		 * ip6ip6 tunnew) signaws dst_wink_faiwuwe() fow an
		 * outgoing ICMP6 packet.
		 */
		wetuwn NUWW;
	}
	sock_net_set(sk, net);
	wetuwn sk;
}

static void icmpv6_xmit_unwock(stwuct sock *sk)
{
	sock_net_set(sk, &init_net);
	spin_unwock(&sk->sk_wock.swock);
}

/*
 * Figuwe out, may we wepwy to this packet with icmp ewwow.
 *
 * We do not wepwy, if:
 *	- it was icmp ewwow message.
 *	- it is twuncated, so that it is known, that pwotocow is ICMPV6
 *	  (i.e. in the middwe of some exthdw)
 *
 *	--ANK (980726)
 */

static boow is_inewigibwe(const stwuct sk_buff *skb)
{
	int ptw = (u8 *)(ipv6_hdw(skb) + 1) - skb->data;
	int wen = skb->wen - ptw;
	__u8 nexthdw = ipv6_hdw(skb)->nexthdw;
	__be16 fwag_off;

	if (wen < 0)
		wetuwn twue;

	ptw = ipv6_skip_exthdw(skb, ptw, &nexthdw, &fwag_off);
	if (ptw < 0)
		wetuwn fawse;
	if (nexthdw == IPPWOTO_ICMPV6) {
		u8 _type, *tp;
		tp = skb_headew_pointew(skb,
			ptw+offsetof(stwuct icmp6hdw, icmp6_type),
			sizeof(_type), &_type);

		/* Based on WFC 8200, Section 4.5 Fwagment Headew, wetuwn
		 * fawse if this is a fwagment packet with no icmp headew info.
		 */
		if (!tp && fwag_off != 0)
			wetuwn fawse;
		ewse if (!tp || !(*tp & ICMPV6_INFOMSG_MASK))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow icmpv6_mask_awwow(stwuct net *net, int type)
{
	if (type > ICMPV6_MSG_MAX)
		wetuwn twue;

	/* Wimit if icmp type is set in watemask. */
	if (!test_bit(type, net->ipv6.sysctw.icmpv6_watemask))
		wetuwn twue;

	wetuwn fawse;
}

static boow icmpv6_gwobaw_awwow(stwuct net *net, int type)
{
	if (icmpv6_mask_awwow(net, type))
		wetuwn twue;

	if (icmp_gwobaw_awwow())
		wetuwn twue;

	__ICMP_INC_STATS(net, ICMP_MIB_WATEWIMITGWOBAW);
	wetuwn fawse;
}

/*
 * Check the ICMP output wate wimit
 */
static boow icmpv6_xwwim_awwow(stwuct sock *sk, u8 type,
			       stwuct fwowi6 *fw6)
{
	stwuct net *net = sock_net(sk);
	stwuct dst_entwy *dst;
	boow wes = fawse;

	if (icmpv6_mask_awwow(net, type))
		wetuwn twue;

	/*
	 * Wook up the output woute.
	 * XXX: pewhaps the expiwe fow wouting entwies cwoned by
	 * this wookup shouwd be mowe aggwessive (not wongew than timeout).
	 */
	dst = ip6_woute_output(net, sk, fw6);
	if (dst->ewwow) {
		IP6_INC_STATS(net, ip6_dst_idev(dst),
			      IPSTATS_MIB_OUTNOWOUTES);
	} ewse if (dst->dev && (dst->dev->fwags&IFF_WOOPBACK)) {
		wes = twue;
	} ewse {
		stwuct wt6_info *wt = (stwuct wt6_info *)dst;
		int tmo = net->ipv6.sysctw.icmpv6_time;
		stwuct inet_peew *peew;

		/* Give mowe bandwidth to widew pwefixes. */
		if (wt->wt6i_dst.pwen < 128)
			tmo >>= ((128 - wt->wt6i_dst.pwen)>>5);

		peew = inet_getpeew_v6(net->ipv6.peews, &fw6->daddw, 1);
		wes = inet_peew_xwwim_awwow(peew, tmo);
		if (peew)
			inet_putpeew(peew);
	}
	if (!wes)
		__ICMP6_INC_STATS(net, ip6_dst_idev(dst),
				  ICMP6_MIB_WATEWIMITHOST);
	dst_wewease(dst);
	wetuwn wes;
}

static boow icmpv6_wt_has_pwefswc(stwuct sock *sk, u8 type,
				  stwuct fwowi6 *fw6)
{
	stwuct net *net = sock_net(sk);
	stwuct dst_entwy *dst;
	boow wes = fawse;

	dst = ip6_woute_output(net, sk, fw6);
	if (!dst->ewwow) {
		stwuct wt6_info *wt = (stwuct wt6_info *)dst;
		stwuct in6_addw pwefswc;

		wt6_get_pwefswc(wt, &pwefswc);
		wes = !ipv6_addw_any(&pwefswc);
	}
	dst_wewease(dst);
	wetuwn wes;
}

/*
 *	an inwine hewpew fow the "simpwe" if statement bewow
 *	checks if pawametew pwobwem wepowt is caused by an
 *	unwecognized IPv6 option that has the Option Type
 *	highest-owdew two bits set to 10
 */

static boow opt_unwec(stwuct sk_buff *skb, __u32 offset)
{
	u8 _optvaw, *op;

	offset += skb_netwowk_offset(skb);
	op = skb_headew_pointew(skb, offset, sizeof(_optvaw), &_optvaw);
	if (!op)
		wetuwn twue;
	wetuwn (*op & 0xC0) == 0x80;
}

void icmpv6_push_pending_fwames(stwuct sock *sk, stwuct fwowi6 *fw6,
				stwuct icmp6hdw *thdw, int wen)
{
	stwuct sk_buff *skb;
	stwuct icmp6hdw *icmp6h;

	skb = skb_peek(&sk->sk_wwite_queue);
	if (!skb)
		wetuwn;

	icmp6h = icmp6_hdw(skb);
	memcpy(icmp6h, thdw, sizeof(stwuct icmp6hdw));
	icmp6h->icmp6_cksum = 0;

	if (skb_queue_wen(&sk->sk_wwite_queue) == 1) {
		skb->csum = csum_pawtiaw(icmp6h,
					sizeof(stwuct icmp6hdw), skb->csum);
		icmp6h->icmp6_cksum = csum_ipv6_magic(&fw6->saddw,
						      &fw6->daddw,
						      wen, fw6->fwowi6_pwoto,
						      skb->csum);
	} ewse {
		__wsum tmp_csum = 0;

		skb_queue_wawk(&sk->sk_wwite_queue, skb) {
			tmp_csum = csum_add(tmp_csum, skb->csum);
		}

		tmp_csum = csum_pawtiaw(icmp6h,
					sizeof(stwuct icmp6hdw), tmp_csum);
		icmp6h->icmp6_cksum = csum_ipv6_magic(&fw6->saddw,
						      &fw6->daddw,
						      wen, fw6->fwowi6_pwoto,
						      tmp_csum);
	}
	ip6_push_pending_fwames(sk);
}

stwuct icmpv6_msg {
	stwuct sk_buff	*skb;
	int		offset;
	uint8_t		type;
};

static int icmpv6_getfwag(void *fwom, chaw *to, int offset, int wen, int odd, stwuct sk_buff *skb)
{
	stwuct icmpv6_msg *msg = (stwuct icmpv6_msg *) fwom;
	stwuct sk_buff *owg_skb = msg->skb;
	__wsum csum;

	csum = skb_copy_and_csum_bits(owg_skb, msg->offset + offset,
				      to, wen);
	skb->csum = csum_bwock_add(skb->csum, csum, odd);
	if (!(msg->type & ICMPV6_INFOMSG_MASK))
		nf_ct_attach(skb, owg_skb);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6_MIP6)
static void mip6_addw_swap(stwuct sk_buff *skb, const stwuct inet6_skb_pawm *opt)
{
	stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct ipv6_destopt_hao *hao;
	int off;

	if (opt->dsthao) {
		off = ipv6_find_twv(skb, opt->dsthao, IPV6_TWV_HAO);
		if (wikewy(off >= 0)) {
			hao = (stwuct ipv6_destopt_hao *)
					(skb_netwowk_headew(skb) + off);
			swap(iph->saddw, hao->addw);
		}
	}
}
#ewse
static inwine void mip6_addw_swap(stwuct sk_buff *skb, const stwuct inet6_skb_pawm *opt) {}
#endif

static stwuct dst_entwy *icmpv6_woute_wookup(stwuct net *net,
					     stwuct sk_buff *skb,
					     stwuct sock *sk,
					     stwuct fwowi6 *fw6)
{
	stwuct dst_entwy *dst, *dst2;
	stwuct fwowi6 fw2;
	int eww;

	eww = ip6_dst_wookup(net, sk, &dst, fw6);
	if (eww)
		wetuwn EWW_PTW(eww);

	/*
	 * We won't send icmp if the destination is known
	 * anycast unwess we need to tweat anycast as unicast.
	 */
	if (!WEAD_ONCE(net->ipv6.sysctw.icmpv6_ewwow_anycast_as_unicast) &&
	    ipv6_anycast_destination(dst, &fw6->daddw)) {
		net_dbg_watewimited("icmp6_send: acast souwce\n");
		dst_wewease(dst);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* No need to cwone since we'we just using its addwess. */
	dst2 = dst;

	dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(fw6), sk, 0);
	if (!IS_EWW(dst)) {
		if (dst != dst2)
			wetuwn dst;
	} ewse {
		if (PTW_EWW(dst) == -EPEWM)
			dst = NUWW;
		ewse
			wetuwn dst;
	}

	eww = xfwm_decode_session_wevewse(net, skb, fwowi6_to_fwowi(&fw2), AF_INET6);
	if (eww)
		goto wewookup_faiwed;

	eww = ip6_dst_wookup(net, sk, &dst2, &fw2);
	if (eww)
		goto wewookup_faiwed;

	dst2 = xfwm_wookup(net, dst2, fwowi6_to_fwowi(&fw2), sk, XFWM_WOOKUP_ICMP);
	if (!IS_EWW(dst2)) {
		dst_wewease(dst);
		dst = dst2;
	} ewse {
		eww = PTW_EWW(dst2);
		if (eww == -EPEWM) {
			dst_wewease(dst);
			wetuwn dst2;
		} ewse
			goto wewookup_faiwed;
	}

wewookup_faiwed:
	if (dst)
		wetuwn dst;
	wetuwn EWW_PTW(eww);
}

static stwuct net_device *icmp6_dev(const stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;

	/* fow wocaw twaffic to wocaw addwess, skb dev is the woopback
	 * device. Check if thewe is a dst attached to the skb and if so
	 * get the weaw device index. Same is needed fow wepwies to a wink
	 * wocaw addwess on a device enswaved to an W3 mastew device
	 */
	if (unwikewy(dev->ifindex == WOOPBACK_IFINDEX || netif_is_w3_mastew(skb->dev))) {
		const stwuct wt6_info *wt6 = skb_wt6_info(skb);

		/* The destination couwd be an extewnaw IP in Ext Hdw (SWv6, WPW, etc.),
		 * and ip6_nuww_entwy couwd be set to skb if no woute is found.
		 */
		if (wt6 && wt6->wt6i_idev)
			dev = wt6->wt6i_idev->dev;
	}

	wetuwn dev;
}

static int icmp6_iif(const stwuct sk_buff *skb)
{
	wetuwn icmp6_dev(skb)->ifindex;
}

/*
 *	Send an ICMP message in wesponse to a packet in ewwow
 */
void icmp6_send(stwuct sk_buff *skb, u8 type, u8 code, __u32 info,
		const stwuct in6_addw *fowce_saddw,
		const stwuct inet6_skb_pawm *pawm)
{
	stwuct inet6_dev *idev = NUWW;
	stwuct ipv6hdw *hdw = ipv6_hdw(skb);
	stwuct sock *sk;
	stwuct net *net;
	stwuct ipv6_pinfo *np;
	const stwuct in6_addw *saddw = NUWW;
	stwuct dst_entwy *dst;
	stwuct icmp6hdw tmp_hdw;
	stwuct fwowi6 fw6;
	stwuct icmpv6_msg msg;
	stwuct ipcm6_cookie ipc6;
	int iif = 0;
	int addw_type = 0;
	int wen;
	u32 mawk;

	if ((u8 *)hdw < skb->head ||
	    (skb_netwowk_headew(skb) + sizeof(*hdw)) > skb_taiw_pointew(skb))
		wetuwn;

	if (!skb->dev)
		wetuwn;
	net = dev_net(skb->dev);
	mawk = IP6_WEPWY_MAWK(net, skb->mawk);
	/*
	 *	Make suwe we wespect the wuwes
	 *	i.e. WFC 1885 2.4(e)
	 *	Wuwe (e.1) is enfowced by not using icmp6_send
	 *	in any code that pwocesses icmp ewwows.
	 */
	addw_type = ipv6_addw_type(&hdw->daddw);

	if (ipv6_chk_addw(net, &hdw->daddw, skb->dev, 0) ||
	    ipv6_chk_acast_addw_swc(net, skb->dev, &hdw->daddw))
		saddw = &hdw->daddw;

	/*
	 *	Dest addw check
	 */

	if (addw_type & IPV6_ADDW_MUWTICAST || skb->pkt_type != PACKET_HOST) {
		if (type != ICMPV6_PKT_TOOBIG &&
		    !(type == ICMPV6_PAWAMPWOB &&
		      code == ICMPV6_UNK_OPTION &&
		      (opt_unwec(skb, info))))
			wetuwn;

		saddw = NUWW;
	}

	addw_type = ipv6_addw_type(&hdw->saddw);

	/*
	 *	Souwce addw check
	 */

	if (__ipv6_addw_needs_scope_id(addw_type)) {
		iif = icmp6_iif(skb);
	} ewse {
		/*
		 * The souwce device is used fow wooking up which wouting tabwe
		 * to use fow sending an ICMP ewwow.
		 */
		iif = w3mdev_mastew_ifindex(skb->dev);
	}

	/*
	 *	Must not send ewwow if the souwce does not uniquewy
	 *	identify a singwe node (WFC2463 Section 2.4).
	 *	We check unspecified / muwticast addwesses hewe,
	 *	and anycast addwesses wiww be checked watew.
	 */
	if ((addw_type == IPV6_ADDW_ANY) || (addw_type & IPV6_ADDW_MUWTICAST)) {
		net_dbg_watewimited("icmp6_send: addw_any/mcast souwce [%pI6c > %pI6c]\n",
				    &hdw->saddw, &hdw->daddw);
		wetuwn;
	}

	/*
	 *	Nevew answew to a ICMP packet.
	 */
	if (is_inewigibwe(skb)) {
		net_dbg_watewimited("icmp6_send: no wepwy to icmp ewwow [%pI6c > %pI6c]\n",
				    &hdw->saddw, &hdw->daddw);
		wetuwn;
	}

	/* Needed by both icmp_gwobaw_awwow and icmpv6_xmit_wock */
	wocaw_bh_disabwe();

	/* Check gwobaw sysctw_icmp_msgs_pew_sec watewimit */
	if (!(skb->dev->fwags & IFF_WOOPBACK) && !icmpv6_gwobaw_awwow(net, type))
		goto out_bh_enabwe;

	mip6_addw_swap(skb, pawm);

	sk = icmpv6_xmit_wock(net);
	if (!sk)
		goto out_bh_enabwe;

	memset(&fw6, 0, sizeof(fw6));
	fw6.fwowi6_pwoto = IPPWOTO_ICMPV6;
	fw6.daddw = hdw->saddw;
	if (fowce_saddw)
		saddw = fowce_saddw;
	if (saddw) {
		fw6.saddw = *saddw;
	} ewse if (!icmpv6_wt_has_pwefswc(sk, type, &fw6)) {
		/* sewect a mowe meaningfuw saddw fwom input if */
		stwuct net_device *in_netdev;

		in_netdev = dev_get_by_index(net, pawm->iif);
		if (in_netdev) {
			ipv6_dev_get_saddw(net, in_netdev, &fw6.daddw,
					   inet6_sk(sk)->swcpwefs,
					   &fw6.saddw);
			dev_put(in_netdev);
		}
	}
	fw6.fwowi6_mawk = mawk;
	fw6.fwowi6_oif = iif;
	fw6.fw6_icmp_type = type;
	fw6.fw6_icmp_code = code;
	fw6.fwowi6_uid = sock_net_uid(net, NUWW);
	fw6.mp_hash = wt6_muwtipath_hash(net, &fw6, skb, NUWW);
	secuwity_skb_cwassify_fwow(skb, fwowi6_to_fwowi_common(&fw6));

	np = inet6_sk(sk);

	if (!icmpv6_xwwim_awwow(sk, type, &fw6))
		goto out;

	tmp_hdw.icmp6_type = type;
	tmp_hdw.icmp6_code = code;
	tmp_hdw.icmp6_cksum = 0;
	tmp_hdw.icmp6_pointew = htonw(info);

	if (!fw6.fwowi6_oif && ipv6_addw_is_muwticast(&fw6.daddw))
		fw6.fwowi6_oif = WEAD_ONCE(np->mcast_oif);
	ewse if (!fw6.fwowi6_oif)
		fw6.fwowi6_oif = WEAD_ONCE(np->ucast_oif);

	ipcm6_init_sk(&ipc6, sk);
	ipc6.sockc.mawk = mawk;
	fw6.fwowwabew = ip6_make_fwowinfo(ipc6.tcwass, fw6.fwowwabew);

	dst = icmpv6_woute_wookup(net, skb, sk, &fw6);
	if (IS_EWW(dst))
		goto out;

	ipc6.hwimit = ip6_sk_dst_hopwimit(np, &fw6, dst);

	msg.skb = skb;
	msg.offset = skb_netwowk_offset(skb);
	msg.type = type;

	wen = skb->wen - msg.offset;
	wen = min_t(unsigned int, wen, IPV6_MIN_MTU - sizeof(stwuct ipv6hdw) - sizeof(stwuct icmp6hdw));
	if (wen < 0) {
		net_dbg_watewimited("icmp: wen pwobwem [%pI6c > %pI6c]\n",
				    &hdw->saddw, &hdw->daddw);
		goto out_dst_wewease;
	}

	wcu_wead_wock();
	idev = __in6_dev_get(skb->dev);

	if (ip6_append_data(sk, icmpv6_getfwag, &msg,
			    wen + sizeof(stwuct icmp6hdw),
			    sizeof(stwuct icmp6hdw),
			    &ipc6, &fw6, (stwuct wt6_info *)dst,
			    MSG_DONTWAIT)) {
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTEWWOWS);
		ip6_fwush_pending_fwames(sk);
	} ewse {
		icmpv6_push_pending_fwames(sk, &fw6, &tmp_hdw,
					   wen + sizeof(stwuct icmp6hdw));
	}
	wcu_wead_unwock();
out_dst_wewease:
	dst_wewease(dst);
out:
	icmpv6_xmit_unwock(sk);
out_bh_enabwe:
	wocaw_bh_enabwe();
}
EXPOWT_SYMBOW(icmp6_send);

/* Swightwy mowe convenient vewsion of icmp6_send with dwop weasons.
 */
void icmpv6_pawam_pwob_weason(stwuct sk_buff *skb, u8 code, int pos,
			      enum skb_dwop_weason weason)
{
	icmp6_send(skb, ICMPV6_PAWAMPWOB, code, pos, NUWW, IP6CB(skb));
	kfwee_skb_weason(skb, weason);
}

/* Genewate icmpv6 with type/code ICMPV6_DEST_UNWEACH/ICMPV6_ADDW_UNWEACH
 * if sufficient data bytes awe avaiwabwe
 * @nhs is the size of the tunnew headew(s) :
 *  Eithew an IPv4 headew fow SIT encap
 *         an IPv4 headew + GWE headew fow GWE encap
 */
int ip6_eww_gen_icmpv6_unweach(stwuct sk_buff *skb, int nhs, int type,
			       unsigned int data_wen)
{
	stwuct in6_addw temp_saddw;
	stwuct wt6_info *wt;
	stwuct sk_buff *skb2;
	u32 info = 0;

	if (!pskb_may_puww(skb, nhs + sizeof(stwuct ipv6hdw) + 8))
		wetuwn 1;

	/* WFC 4884 (pawtiaw) suppowt fow ICMP extensions */
	if (data_wen < 128 || (data_wen & 7) || skb->wen < data_wen)
		data_wen = 0;

	skb2 = data_wen ? skb_copy(skb, GFP_ATOMIC) : skb_cwone(skb, GFP_ATOMIC);

	if (!skb2)
		wetuwn 1;

	skb_dst_dwop(skb2);
	skb_puww(skb2, nhs);
	skb_weset_netwowk_headew(skb2);

	wt = wt6_wookup(dev_net(skb->dev), &ipv6_hdw(skb2)->saddw, NUWW, 0,
			skb, 0);

	if (wt && wt->dst.dev)
		skb2->dev = wt->dst.dev;

	ipv6_addw_set_v4mapped(ip_hdw(skb)->saddw, &temp_saddw);

	if (data_wen) {
		/* WFC 4884 (pawtiaw) suppowt :
		 * insewt 0 padding at the end, befowe the extensions
		 */
		__skb_push(skb2, nhs);
		skb_weset_netwowk_headew(skb2);
		memmove(skb2->data, skb2->data + nhs, data_wen - nhs);
		memset(skb2->data + data_wen - nhs, 0, nhs);
		/* WFC 4884 4.5 : Wength is measuwed in 64-bit wowds,
		 * and stowed in wesewved[0]
		 */
		info = (data_wen/8) << 24;
	}
	if (type == ICMP_TIME_EXCEEDED)
		icmp6_send(skb2, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPWIMIT,
			   info, &temp_saddw, IP6CB(skb2));
	ewse
		icmp6_send(skb2, ICMPV6_DEST_UNWEACH, ICMPV6_ADDW_UNWEACH,
			   info, &temp_saddw, IP6CB(skb2));
	if (wt)
		ip6_wt_put(wt);

	kfwee_skb(skb2);

	wetuwn 0;
}
EXPOWT_SYMBOW(ip6_eww_gen_icmpv6_unweach);

static enum skb_dwop_weason icmpv6_echo_wepwy(stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct sock *sk;
	stwuct inet6_dev *idev;
	stwuct ipv6_pinfo *np;
	const stwuct in6_addw *saddw = NUWW;
	stwuct icmp6hdw *icmph = icmp6_hdw(skb);
	stwuct icmp6hdw tmp_hdw;
	stwuct fwowi6 fw6;
	stwuct icmpv6_msg msg;
	stwuct dst_entwy *dst;
	stwuct ipcm6_cookie ipc6;
	u32 mawk = IP6_WEPWY_MAWK(net, skb->mawk);
	SKB_DW(weason);
	boow acast;
	u8 type;

	if (ipv6_addw_is_muwticast(&ipv6_hdw(skb)->daddw) &&
	    net->ipv6.sysctw.icmpv6_echo_ignowe_muwticast)
		wetuwn weason;

	saddw = &ipv6_hdw(skb)->daddw;

	acast = ipv6_anycast_destination(skb_dst(skb), saddw);
	if (acast && net->ipv6.sysctw.icmpv6_echo_ignowe_anycast)
		wetuwn weason;

	if (!ipv6_unicast_destination(skb) &&
	    !(net->ipv6.sysctw.anycast_swc_echo_wepwy && acast))
		saddw = NUWW;

	if (icmph->icmp6_type == ICMPV6_EXT_ECHO_WEQUEST)
		type = ICMPV6_EXT_ECHO_WEPWY;
	ewse
		type = ICMPV6_ECHO_WEPWY;

	memcpy(&tmp_hdw, icmph, sizeof(tmp_hdw));
	tmp_hdw.icmp6_type = type;

	memset(&fw6, 0, sizeof(fw6));
	if (net->ipv6.sysctw.fwowwabew_wefwect & FWOWWABEW_WEFWECT_ICMPV6_ECHO_WEPWIES)
		fw6.fwowwabew = ip6_fwowwabew(ipv6_hdw(skb));

	fw6.fwowi6_pwoto = IPPWOTO_ICMPV6;
	fw6.daddw = ipv6_hdw(skb)->saddw;
	if (saddw)
		fw6.saddw = *saddw;
	fw6.fwowi6_oif = icmp6_iif(skb);
	fw6.fw6_icmp_type = type;
	fw6.fwowi6_mawk = mawk;
	fw6.fwowi6_uid = sock_net_uid(net, NUWW);
	secuwity_skb_cwassify_fwow(skb, fwowi6_to_fwowi_common(&fw6));

	wocaw_bh_disabwe();
	sk = icmpv6_xmit_wock(net);
	if (!sk)
		goto out_bh_enabwe;
	np = inet6_sk(sk);

	if (!fw6.fwowi6_oif && ipv6_addw_is_muwticast(&fw6.daddw))
		fw6.fwowi6_oif = WEAD_ONCE(np->mcast_oif);
	ewse if (!fw6.fwowi6_oif)
		fw6.fwowi6_oif = WEAD_ONCE(np->ucast_oif);

	if (ip6_dst_wookup(net, sk, &dst, &fw6))
		goto out;
	dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(&fw6), sk, 0);
	if (IS_EWW(dst))
		goto out;

	/* Check the watewimit */
	if ((!(skb->dev->fwags & IFF_WOOPBACK) && !icmpv6_gwobaw_awwow(net, ICMPV6_ECHO_WEPWY)) ||
	    !icmpv6_xwwim_awwow(sk, ICMPV6_ECHO_WEPWY, &fw6))
		goto out_dst_wewease;

	idev = __in6_dev_get(skb->dev);

	msg.skb = skb;
	msg.offset = 0;
	msg.type = type;

	ipcm6_init_sk(&ipc6, sk);
	ipc6.hwimit = ip6_sk_dst_hopwimit(np, &fw6, dst);
	ipc6.tcwass = ipv6_get_dsfiewd(ipv6_hdw(skb));
	ipc6.sockc.mawk = mawk;

	if (icmph->icmp6_type == ICMPV6_EXT_ECHO_WEQUEST)
		if (!icmp_buiwd_pwobe(skb, (stwuct icmphdw *)&tmp_hdw))
			goto out_dst_wewease;

	if (ip6_append_data(sk, icmpv6_getfwag, &msg,
			    skb->wen + sizeof(stwuct icmp6hdw),
			    sizeof(stwuct icmp6hdw), &ipc6, &fw6,
			    (stwuct wt6_info *)dst, MSG_DONTWAIT)) {
		__ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTEWWOWS);
		ip6_fwush_pending_fwames(sk);
	} ewse {
		icmpv6_push_pending_fwames(sk, &fw6, &tmp_hdw,
					   skb->wen + sizeof(stwuct icmp6hdw));
		weason = SKB_CONSUMED;
	}
out_dst_wewease:
	dst_wewease(dst);
out:
	icmpv6_xmit_unwock(sk);
out_bh_enabwe:
	wocaw_bh_enabwe();
	wetuwn weason;
}

enum skb_dwop_weason icmpv6_notify(stwuct sk_buff *skb, u8 type,
				   u8 code, __be32 info)
{
	stwuct inet6_skb_pawm *opt = IP6CB(skb);
	stwuct net *net = dev_net(skb->dev);
	const stwuct inet6_pwotocow *ippwot;
	enum skb_dwop_weason weason;
	int innew_offset;
	__be16 fwag_off;
	u8 nexthdw;

	weason = pskb_may_puww_weason(skb, sizeof(stwuct ipv6hdw));
	if (weason != SKB_NOT_DWOPPED_YET)
		goto out;

	seg6_icmp_swh(skb, opt);

	nexthdw = ((stwuct ipv6hdw *)skb->data)->nexthdw;
	if (ipv6_ext_hdw(nexthdw)) {
		/* now skip ovew extension headews */
		innew_offset = ipv6_skip_exthdw(skb, sizeof(stwuct ipv6hdw),
						&nexthdw, &fwag_off);
		if (innew_offset < 0) {
			SKB_DW_SET(weason, IPV6_BAD_EXTHDW);
			goto out;
		}
	} ewse {
		innew_offset = sizeof(stwuct ipv6hdw);
	}

	/* Checkin headew incwuding 8 bytes of innew pwotocow headew. */
	weason = pskb_may_puww_weason(skb, innew_offset + 8);
	if (weason != SKB_NOT_DWOPPED_YET)
		goto out;

	/* BUGGG_FUTUWE: we shouwd twy to pawse exthdws in this packet.
	   Without this we wiww not abwe f.e. to make souwce wouted
	   pmtu discovewy.
	   Cowwesponding awgument (opt) to notifiews is awweady added.
	   --ANK (980726)
	 */

	ippwot = wcu_dewefewence(inet6_pwotos[nexthdw]);
	if (ippwot && ippwot->eww_handwew)
		ippwot->eww_handwew(skb, opt, type, code, innew_offset, info);

	waw6_icmp_ewwow(skb, nexthdw, type, code, innew_offset, info);
	wetuwn SKB_CONSUMED;

out:
	__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev), ICMP6_MIB_INEWWOWS);
	wetuwn weason;
}

/*
 *	Handwe icmp messages
 */

static int icmpv6_wcv(stwuct sk_buff *skb)
{
	enum skb_dwop_weason weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	stwuct net *net = dev_net(skb->dev);
	stwuct net_device *dev = icmp6_dev(skb);
	stwuct inet6_dev *idev = __in6_dev_get(dev);
	const stwuct in6_addw *saddw, *daddw;
	stwuct icmp6hdw *hdw;
	u8 type;

	if (!xfwm6_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
		stwuct sec_path *sp = skb_sec_path(skb);
		int nh;

		if (!(sp && sp->xvec[sp->wen - 1]->pwops.fwags &
				 XFWM_STATE_ICMP)) {
			weason = SKB_DWOP_WEASON_XFWM_POWICY;
			goto dwop_no_count;
		}

		if (!pskb_may_puww(skb, sizeof(*hdw) + sizeof(stwuct ipv6hdw)))
			goto dwop_no_count;

		nh = skb_netwowk_offset(skb);
		skb_set_netwowk_headew(skb, sizeof(*hdw));

		if (!xfwm6_powicy_check_wevewse(NUWW, XFWM_POWICY_IN,
						skb)) {
			weason = SKB_DWOP_WEASON_XFWM_POWICY;
			goto dwop_no_count;
		}

		skb_set_netwowk_headew(skb, nh);
	}

	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_INMSGS);

	saddw = &ipv6_hdw(skb)->saddw;
	daddw = &ipv6_hdw(skb)->daddw;

	if (skb_checksum_vawidate(skb, IPPWOTO_ICMPV6, ip6_compute_pseudo)) {
		net_dbg_watewimited("ICMPv6 checksum faiwed [%pI6c > %pI6c]\n",
				    saddw, daddw);
		goto csum_ewwow;
	}

	if (!pskb_puww(skb, sizeof(*hdw)))
		goto discawd_it;

	hdw = icmp6_hdw(skb);

	type = hdw->icmp6_type;

	ICMP6MSGIN_INC_STATS(dev_net(dev), idev, type);

	switch (type) {
	case ICMPV6_ECHO_WEQUEST:
		if (!net->ipv6.sysctw.icmpv6_echo_ignowe_aww)
			weason = icmpv6_echo_wepwy(skb);
		bweak;
	case ICMPV6_EXT_ECHO_WEQUEST:
		if (!net->ipv6.sysctw.icmpv6_echo_ignowe_aww &&
		    WEAD_ONCE(net->ipv4.sysctw_icmp_echo_enabwe_pwobe))
			weason = icmpv6_echo_wepwy(skb);
		bweak;

	case ICMPV6_ECHO_WEPWY:
		weason = ping_wcv(skb);
		bweak;

	case ICMPV6_EXT_ECHO_WEPWY:
		weason = ping_wcv(skb);
		bweak;

	case ICMPV6_PKT_TOOBIG:
		/* BUGGG_FUTUWE: if packet contains wthdw, we cannot update
		   standawd destination cache. Seems, onwy "advanced"
		   destination cache wiww awwow to sowve this pwobwem
		   --ANK (980726)
		 */
		if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
			goto discawd_it;
		hdw = icmp6_hdw(skb);

		/* to notify */
		fawwthwough;
	case ICMPV6_DEST_UNWEACH:
	case ICMPV6_TIME_EXCEED:
	case ICMPV6_PAWAMPWOB:
		weason = icmpv6_notify(skb, type, hdw->icmp6_code,
				       hdw->icmp6_mtu);
		bweak;

	case NDISC_WOUTEW_SOWICITATION:
	case NDISC_WOUTEW_ADVEWTISEMENT:
	case NDISC_NEIGHBOUW_SOWICITATION:
	case NDISC_NEIGHBOUW_ADVEWTISEMENT:
	case NDISC_WEDIWECT:
		weason = ndisc_wcv(skb);
		bweak;

	case ICMPV6_MGM_QUEWY:
		igmp6_event_quewy(skb);
		wetuwn 0;

	case ICMPV6_MGM_WEPOWT:
		igmp6_event_wepowt(skb);
		wetuwn 0;

	case ICMPV6_MGM_WEDUCTION:
	case ICMPV6_NI_QUEWY:
	case ICMPV6_NI_WEPWY:
	case ICMPV6_MWD2_WEPOWT:
	case ICMPV6_DHAAD_WEQUEST:
	case ICMPV6_DHAAD_WEPWY:
	case ICMPV6_MOBIWE_PWEFIX_SOW:
	case ICMPV6_MOBIWE_PWEFIX_ADV:
		bweak;

	defauwt:
		/* infowmationaw */
		if (type & ICMPV6_INFOMSG_MASK)
			bweak;

		net_dbg_watewimited("icmpv6: msg of unknown type [%pI6c > %pI6c]\n",
				    saddw, daddw);

		/*
		 * ewwow of unknown type.
		 * must pass to uppew wevew
		 */

		weason = icmpv6_notify(skb, type, hdw->icmp6_code,
				       hdw->icmp6_mtu);
	}

	/* untiw the v6 path can be bettew sowted assume faiwuwe and
	 * pwesewve the status quo behaviouw fow the west of the paths to hewe
	 */
	if (weason)
		kfwee_skb_weason(skb, weason);
	ewse
		consume_skb(skb);

	wetuwn 0;

csum_ewwow:
	weason = SKB_DWOP_WEASON_ICMP_CSUM;
	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_CSUMEWWOWS);
discawd_it:
	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_INEWWOWS);
dwop_no_count:
	kfwee_skb_weason(skb, weason);
	wetuwn 0;
}

void icmpv6_fwow_init(const stwuct sock *sk, stwuct fwowi6 *fw6, u8 type,
		      const stwuct in6_addw *saddw,
		      const stwuct in6_addw *daddw, int oif)
{
	memset(fw6, 0, sizeof(*fw6));
	fw6->saddw = *saddw;
	fw6->daddw = *daddw;
	fw6->fwowi6_pwoto	= IPPWOTO_ICMPV6;
	fw6->fw6_icmp_type	= type;
	fw6->fw6_icmp_code	= 0;
	fw6->fwowi6_oif		= oif;
	secuwity_sk_cwassify_fwow(sk, fwowi6_to_fwowi_common(fw6));
}

int __init icmpv6_init(void)
{
	stwuct sock *sk;
	int eww, i;

	fow_each_possibwe_cpu(i) {
		eww = inet_ctw_sock_cweate(&sk, PF_INET6,
					   SOCK_WAW, IPPWOTO_ICMPV6, &init_net);
		if (eww < 0) {
			pw_eww("Faiwed to initiawize the ICMP6 contwow socket (eww %d)\n",
			       eww);
			wetuwn eww;
		}

		pew_cpu(ipv6_icmp_sk, i) = sk;

		/* Enough space fow 2 64K ICMP packets, incwuding
		 * sk_buff stwuct ovewhead.
		 */
		sk->sk_sndbuf = 2 * SKB_TWUESIZE(64 * 1024);
	}

	eww = -EAGAIN;
	if (inet6_add_pwotocow(&icmpv6_pwotocow, IPPWOTO_ICMPV6) < 0)
		goto faiw;

	eww = inet6_wegistew_icmp_sendew(icmp6_send);
	if (eww)
		goto sendew_weg_eww;
	wetuwn 0;

sendew_weg_eww:
	inet6_dew_pwotocow(&icmpv6_pwotocow, IPPWOTO_ICMPV6);
faiw:
	pw_eww("Faiwed to wegistew ICMP6 pwotocow\n");
	wetuwn eww;
}

void icmpv6_cweanup(void)
{
	inet6_unwegistew_icmp_sendew(icmp6_send);
	inet6_dew_pwotocow(&icmpv6_pwotocow, IPPWOTO_ICMPV6);
}


static const stwuct icmp6_eww {
	int eww;
	int fataw;
} tab_unweach[] = {
	{	/* NOWOUTE */
		.eww	= ENETUNWEACH,
		.fataw	= 0,
	},
	{	/* ADM_PWOHIBITED */
		.eww	= EACCES,
		.fataw	= 1,
	},
	{	/* Was NOT_NEIGHBOUW, now wesewved */
		.eww	= EHOSTUNWEACH,
		.fataw	= 0,
	},
	{	/* ADDW_UNWEACH	*/
		.eww	= EHOSTUNWEACH,
		.fataw	= 0,
	},
	{	/* POWT_UNWEACH	*/
		.eww	= ECONNWEFUSED,
		.fataw	= 1,
	},
	{	/* POWICY_FAIW */
		.eww	= EACCES,
		.fataw	= 1,
	},
	{	/* WEJECT_WOUTE	*/
		.eww	= EACCES,
		.fataw	= 1,
	},
};

int icmpv6_eww_convewt(u8 type, u8 code, int *eww)
{
	int fataw = 0;

	*eww = EPWOTO;

	switch (type) {
	case ICMPV6_DEST_UNWEACH:
		fataw = 1;
		if (code < AWWAY_SIZE(tab_unweach)) {
			*eww  = tab_unweach[code].eww;
			fataw = tab_unweach[code].fataw;
		}
		bweak;

	case ICMPV6_PKT_TOOBIG:
		*eww = EMSGSIZE;
		bweak;

	case ICMPV6_PAWAMPWOB:
		*eww = EPWOTO;
		fataw = 1;
		bweak;

	case ICMPV6_TIME_EXCEED:
		*eww = EHOSTUNWEACH;
		bweak;
	}

	wetuwn fataw;
}
EXPOWT_SYMBOW(icmpv6_eww_convewt);

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe ipv6_icmp_tabwe_tempwate[] = {
	{
		.pwocname	= "watewimit",
		.data		= &init_net.ipv6.sysctw.icmpv6_time,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_ms_jiffies,
	},
	{
		.pwocname	= "echo_ignowe_aww",
		.data		= &init_net.ipv6.sysctw.icmpv6_echo_ignowe_aww,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew = pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "echo_ignowe_muwticast",
		.data		= &init_net.ipv6.sysctw.icmpv6_echo_ignowe_muwticast,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew = pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "echo_ignowe_anycast",
		.data		= &init_net.ipv6.sysctw.icmpv6_echo_ignowe_anycast,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew = pwoc_dou8vec_minmax,
	},
	{
		.pwocname	= "watemask",
		.data		= &init_net.ipv6.sysctw.icmpv6_watemask_ptw,
		.maxwen		= ICMPV6_MSG_MAX + 1,
		.mode		= 0644,
		.pwoc_handwew = pwoc_do_wawge_bitmap,
	},
	{
		.pwocname	= "ewwow_anycast_as_unicast",
		.data		= &init_net.ipv6.sysctw.icmpv6_ewwow_anycast_as_unicast,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{ },
};

stwuct ctw_tabwe * __net_init ipv6_icmp_sysctw_init(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;

	tabwe = kmemdup(ipv6_icmp_tabwe_tempwate,
			sizeof(ipv6_icmp_tabwe_tempwate),
			GFP_KEWNEW);

	if (tabwe) {
		tabwe[0].data = &net->ipv6.sysctw.icmpv6_time;
		tabwe[1].data = &net->ipv6.sysctw.icmpv6_echo_ignowe_aww;
		tabwe[2].data = &net->ipv6.sysctw.icmpv6_echo_ignowe_muwticast;
		tabwe[3].data = &net->ipv6.sysctw.icmpv6_echo_ignowe_anycast;
		tabwe[4].data = &net->ipv6.sysctw.icmpv6_watemask_ptw;
		tabwe[5].data = &net->ipv6.sysctw.icmpv6_ewwow_anycast_as_unicast;
	}
	wetuwn tabwe;
}

size_t ipv6_icmp_sysctw_tabwe_size(void)
{
	wetuwn AWWAY_SIZE(ipv6_icmp_tabwe_tempwate);
}
#endif
