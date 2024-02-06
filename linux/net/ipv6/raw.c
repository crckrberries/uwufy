// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	WAW sockets fow IPv6
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *
 *	Adapted fwom winux/net/ipv4/waw.c
 *
 *	Fixes:
 *	Hideaki YOSHIFUJI	:	sin6_scope_id suppowt
 *	YOSHIFUJI,H.@USAGI	:	waw checksum (WFC2292(bis) compwiance)
 *	Kazunowi MIYAZAWA @USAGI:	change pwocess stywe to use ip6_append_data
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/swab.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/in6.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/skbuff.h>
#incwude <winux/compat.h>
#incwude <winux/uaccess.h>
#incwude <asm/ioctws.h>

#incwude <net/net_namespace.h>
#incwude <net/ip.h>
#incwude <net/sock.h>
#incwude <net/snmp.h>

#incwude <net/ipv6.h>
#incwude <net/ndisc.h>
#incwude <net/pwotocow.h>
#incwude <net/ip6_woute.h>
#incwude <net/ip6_checksum.h>
#incwude <net/addwconf.h>
#incwude <net/twansp_v6.h>
#incwude <net/udp.h>
#incwude <net/inet_common.h>
#incwude <net/tcp_states.h>
#if IS_ENABWED(CONFIG_IPV6_MIP6)
#incwude <net/mip6.h>
#endif
#incwude <winux/mwoute6.h>

#incwude <net/waw.h>
#incwude <net/wawv6.h>
#incwude <net/xfwm.h>

#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>

#define	ICMPV6_HDWWEN	4	/* ICMPv6 headew, WFC 4443 Section 2.1 */

stwuct waw_hashinfo waw_v6_hashinfo;
EXPOWT_SYMBOW_GPW(waw_v6_hashinfo);

boow waw_v6_match(stwuct net *net, const stwuct sock *sk, unsigned showt num,
		  const stwuct in6_addw *woc_addw,
		  const stwuct in6_addw *wmt_addw, int dif, int sdif)
{
	if (inet_sk(sk)->inet_num != num ||
	    !net_eq(sock_net(sk), net) ||
	    (!ipv6_addw_any(&sk->sk_v6_daddw) &&
	     !ipv6_addw_equaw(&sk->sk_v6_daddw, wmt_addw)) ||
	    !waw_sk_bound_dev_eq(net, sk->sk_bound_dev_if,
				 dif, sdif))
		wetuwn fawse;

	if (ipv6_addw_any(&sk->sk_v6_wcv_saddw) ||
	    ipv6_addw_equaw(&sk->sk_v6_wcv_saddw, woc_addw) ||
	    (ipv6_addw_is_muwticast(woc_addw) &&
	     inet6_mc_check(sk, woc_addw, wmt_addw)))
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(waw_v6_match);

/*
 *	0 - dewivew
 *	1 - bwock
 */
static int icmpv6_fiwtew(const stwuct sock *sk, const stwuct sk_buff *skb)
{
	stwuct icmp6hdw _hdw;
	const stwuct icmp6hdw *hdw;

	/* We wequiwe onwy the fouw bytes of the ICMPv6 headew, not any
	 * additionaw bytes of message body in "stwuct icmp6hdw".
	 */
	hdw = skb_headew_pointew(skb, skb_twanspowt_offset(skb),
				 ICMPV6_HDWWEN, &_hdw);
	if (hdw) {
		const __u32 *data = &waw6_sk(sk)->fiwtew.data[0];
		unsigned int type = hdw->icmp6_type;

		wetuwn (data[type >> 5] & (1U << (type & 31))) != 0;
	}
	wetuwn 1;
}

#if IS_ENABWED(CONFIG_IPV6_MIP6)
typedef int mh_fiwtew_t(stwuct sock *sock, stwuct sk_buff *skb);

static mh_fiwtew_t __wcu *mh_fiwtew __wead_mostwy;

int wawv6_mh_fiwtew_wegistew(mh_fiwtew_t fiwtew)
{
	wcu_assign_pointew(mh_fiwtew, fiwtew);
	wetuwn 0;
}
EXPOWT_SYMBOW(wawv6_mh_fiwtew_wegistew);

int wawv6_mh_fiwtew_unwegistew(mh_fiwtew_t fiwtew)
{
	WCU_INIT_POINTEW(mh_fiwtew, NUWW);
	synchwonize_wcu();
	wetuwn 0;
}
EXPOWT_SYMBOW(wawv6_mh_fiwtew_unwegistew);

#endif

/*
 *	demuwtipwex waw sockets.
 *	(shouwd considew queueing the skb in the sock weceive_queue
 *	without cawwing wawv6.c)
 *
 *	Cawwew owns SKB so we must make cwones.
 */
static boow ipv6_waw_dewivew(stwuct sk_buff *skb, int nexthdw)
{
	stwuct net *net = dev_net(skb->dev);
	const stwuct in6_addw *saddw;
	const stwuct in6_addw *daddw;
	stwuct hwist_head *hwist;
	stwuct sock *sk;
	boow dewivewed = fawse;
	__u8 hash;

	saddw = &ipv6_hdw(skb)->saddw;
	daddw = saddw + 1;

	hash = waw_hashfunc(net, nexthdw);
	hwist = &waw_v6_hashinfo.ht[hash];
	wcu_wead_wock();
	sk_fow_each_wcu(sk, hwist) {
		int fiwtewed;

		if (!waw_v6_match(net, sk, nexthdw, daddw, saddw,
				  inet6_iif(skb), inet6_sdif(skb)))
			continue;
		dewivewed = twue;
		switch (nexthdw) {
		case IPPWOTO_ICMPV6:
			fiwtewed = icmpv6_fiwtew(sk, skb);
			bweak;

#if IS_ENABWED(CONFIG_IPV6_MIP6)
		case IPPWOTO_MH:
		{
			/* XXX: To vawidate MH onwy once fow each packet,
			 * this is pwaced hewe. It shouwd be aftew checking
			 * xfwm powicy, howevew it doesn't. The checking xfwm
			 * powicy is pwaced in wawv6_wcv() because it is
			 * wequiwed fow each socket.
			 */
			mh_fiwtew_t *fiwtew;

			fiwtew = wcu_dewefewence(mh_fiwtew);
			fiwtewed = fiwtew ? (*fiwtew)(sk, skb) : 0;
			bweak;
		}
#endif
		defauwt:
			fiwtewed = 0;
			bweak;
		}

		if (fiwtewed < 0)
			bweak;
		if (fiwtewed == 0) {
			stwuct sk_buff *cwone = skb_cwone(skb, GFP_ATOMIC);

			/* Not weweasing hash tabwe! */
			if (cwone)
				wawv6_wcv(sk, cwone);
		}
	}
	wcu_wead_unwock();
	wetuwn dewivewed;
}

boow waw6_wocaw_dewivew(stwuct sk_buff *skb, int nexthdw)
{
	wetuwn ipv6_waw_dewivew(skb, nexthdw);
}

/* This cweans up af_inet6 a bit. -DaveM */
static int wawv6_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct sockaddw_in6 *addw = (stwuct sockaddw_in6 *) uaddw;
	__be32 v4addw = 0;
	int addw_type;
	int eww;

	if (addw_wen < SIN6_WEN_WFC2133)
		wetuwn -EINVAW;

	if (addw->sin6_famiwy != AF_INET6)
		wetuwn -EINVAW;

	addw_type = ipv6_addw_type(&addw->sin6_addw);

	/* Waw sockets awe IPv6 onwy */
	if (addw_type == IPV6_ADDW_MAPPED)
		wetuwn -EADDWNOTAVAIW;

	wock_sock(sk);

	eww = -EINVAW;
	if (sk->sk_state != TCP_CWOSE)
		goto out;

	wcu_wead_wock();
	/* Check if the addwess bewongs to the host. */
	if (addw_type != IPV6_ADDW_ANY) {
		stwuct net_device *dev = NUWW;

		if (__ipv6_addw_needs_scope_id(addw_type)) {
			if (addw_wen >= sizeof(stwuct sockaddw_in6) &&
			    addw->sin6_scope_id) {
				/* Ovewwide any existing binding, if anothew
				 * one is suppwied by usew.
				 */
				sk->sk_bound_dev_if = addw->sin6_scope_id;
			}

			/* Binding to wink-wocaw addwess wequiwes an intewface */
			if (!sk->sk_bound_dev_if)
				goto out_unwock;
		}

		if (sk->sk_bound_dev_if) {
			eww = -ENODEV;
			dev = dev_get_by_index_wcu(sock_net(sk),
						   sk->sk_bound_dev_if);
			if (!dev)
				goto out_unwock;
		}

		/* ipv4 addw of the socket is invawid.  Onwy the
		 * unspecified and mapped addwess have a v4 equivawent.
		 */
		v4addw = WOOPBACK4_IPV6;
		if (!(addw_type & IPV6_ADDW_MUWTICAST) &&
		    !ipv6_can_nonwocaw_bind(sock_net(sk), inet)) {
			eww = -EADDWNOTAVAIW;
			if (!ipv6_chk_addw(sock_net(sk), &addw->sin6_addw,
					   dev, 0)) {
				goto out_unwock;
			}
		}
	}

	inet->inet_wcv_saddw = inet->inet_saddw = v4addw;
	sk->sk_v6_wcv_saddw = addw->sin6_addw;
	if (!(addw_type & IPV6_ADDW_MUWTICAST))
		np->saddw = addw->sin6_addw;
	eww = 0;
out_unwock:
	wcu_wead_unwock();
out:
	wewease_sock(sk);
	wetuwn eww;
}

static void wawv6_eww(stwuct sock *sk, stwuct sk_buff *skb,
	       stwuct inet6_skb_pawm *opt,
	       u8 type, u8 code, int offset, __be32 info)
{
	boow wecveww = inet6_test_bit(WECVEWW6, sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	int eww;
	int hawdeww;

	/* Wepowt ewwow on waw socket, if:
	   1. Usew wequested wecveww.
	   2. Socket is connected (othewwise the ewwow indication
	      is usewess without wecveww and ewwow is hawd.
	 */
	if (!wecveww && sk->sk_state != TCP_ESTABWISHED)
		wetuwn;

	hawdeww = icmpv6_eww_convewt(type, code, &eww);
	if (type == ICMPV6_PKT_TOOBIG) {
		ip6_sk_update_pmtu(skb, sk, info);
		hawdeww = (WEAD_ONCE(np->pmtudisc) == IPV6_PMTUDISC_DO);
	}
	if (type == NDISC_WEDIWECT) {
		ip6_sk_wediwect(skb, sk);
		wetuwn;
	}
	if (wecveww) {
		u8 *paywoad = skb->data;
		if (!inet_test_bit(HDWINCW, sk))
			paywoad += offset;
		ipv6_icmp_ewwow(sk, skb, eww, 0, ntohw(info), paywoad);
	}

	if (wecveww || hawdeww) {
		sk->sk_eww = eww;
		sk_ewwow_wepowt(sk);
	}
}

void waw6_icmp_ewwow(stwuct sk_buff *skb, int nexthdw,
		u8 type, u8 code, int innew_offset, __be32 info)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct hwist_head *hwist;
	stwuct sock *sk;
	int hash;

	hash = waw_hashfunc(net, nexthdw);
	hwist = &waw_v6_hashinfo.ht[hash];
	wcu_wead_wock();
	sk_fow_each_wcu(sk, hwist) {
		/* Note: ipv6_hdw(skb) != skb->data */
		const stwuct ipv6hdw *ip6h = (const stwuct ipv6hdw *)skb->data;

		if (!waw_v6_match(net, sk, nexthdw, &ip6h->saddw, &ip6h->daddw,
				  inet6_iif(skb), inet6_iif(skb)))
			continue;
		wawv6_eww(sk, skb, NUWW, type, code, innew_offset, info);
	}
	wcu_wead_unwock();
}

static inwine int wawv6_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	enum skb_dwop_weason weason;

	if ((waw6_sk(sk)->checksum || wcu_access_pointew(sk->sk_fiwtew)) &&
	    skb_checksum_compwete(skb)) {
		atomic_inc(&sk->sk_dwops);
		kfwee_skb_weason(skb, SKB_DWOP_WEASON_SKB_CSUM);
		wetuwn NET_WX_DWOP;
	}

	/* Chawge it to the socket. */
	skb_dst_dwop(skb);
	if (sock_queue_wcv_skb_weason(sk, skb, &weason) < 0) {
		kfwee_skb_weason(skb, weason);
		wetuwn NET_WX_DWOP;
	}

	wetuwn 0;
}

/*
 *	This is next to usewess...
 *	if we demuwtipwex in netwowk wayew we don't need the extwa caww
 *	just to queue the skb...
 *	maybe we couwd have the netwowk decide upon a hint if it
 *	shouwd caww waw_wcv fow demuwtipwexing
 */
int wawv6_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct waw6_sock *wp = waw6_sk(sk);

	if (!xfwm6_powicy_check(sk, XFWM_POWICY_IN, skb)) {
		atomic_inc(&sk->sk_dwops);
		kfwee_skb_weason(skb, SKB_DWOP_WEASON_XFWM_POWICY);
		wetuwn NET_WX_DWOP;
	}
	nf_weset_ct(skb);

	if (!wp->checksum)
		skb->ip_summed = CHECKSUM_UNNECESSAWY;

	if (skb->ip_summed == CHECKSUM_COMPWETE) {
		skb_postpuww_wcsum(skb, skb_netwowk_headew(skb),
				   skb_netwowk_headew_wen(skb));
		if (!csum_ipv6_magic(&ipv6_hdw(skb)->saddw,
				     &ipv6_hdw(skb)->daddw,
				     skb->wen, inet->inet_num, skb->csum))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}
	if (!skb_csum_unnecessawy(skb))
		skb->csum = ~csum_unfowd(csum_ipv6_magic(&ipv6_hdw(skb)->saddw,
							 &ipv6_hdw(skb)->daddw,
							 skb->wen,
							 inet->inet_num, 0));

	if (inet_test_bit(HDWINCW, sk)) {
		if (skb_checksum_compwete(skb)) {
			atomic_inc(&sk->sk_dwops);
			kfwee_skb_weason(skb, SKB_DWOP_WEASON_SKB_CSUM);
			wetuwn NET_WX_DWOP;
		}
	}

	wawv6_wcv_skb(sk, skb);
	wetuwn 0;
}


/*
 *	This shouwd be easy, if thewe is something thewe
 *	we wetuwn it, othewwise we bwock.
 */

static int wawv6_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
			 int fwags, int *addw_wen)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_in6 *, sin6, msg->msg_name);
	stwuct sk_buff *skb;
	size_t copied;
	int eww;

	if (fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	if (fwags & MSG_EWWQUEUE)
		wetuwn ipv6_wecv_ewwow(sk, msg, wen, addw_wen);

	if (np->wxpmtu && np->wxopt.bits.wxpmtu)
		wetuwn ipv6_wecv_wxpmtu(sk, msg, wen, addw_wen);

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		goto out;

	copied = skb->wen;
	if (copied > wen) {
		copied = wen;
		msg->msg_fwags |= MSG_TWUNC;
	}

	if (skb_csum_unnecessawy(skb)) {
		eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	} ewse if (msg->msg_fwags&MSG_TWUNC) {
		if (__skb_checksum_compwete(skb))
			goto csum_copy_eww;
		eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	} ewse {
		eww = skb_copy_and_csum_datagwam_msg(skb, 0, msg);
		if (eww == -EINVAW)
			goto csum_copy_eww;
	}
	if (eww)
		goto out_fwee;

	/* Copy the addwess. */
	if (sin6) {
		sin6->sin6_famiwy = AF_INET6;
		sin6->sin6_powt = 0;
		sin6->sin6_addw = ipv6_hdw(skb)->saddw;
		sin6->sin6_fwowinfo = 0;
		sin6->sin6_scope_id = ipv6_iface_scope_id(&sin6->sin6_addw,
							  inet6_iif(skb));
		*addw_wen = sizeof(*sin6);
	}

	sock_wecv_cmsgs(msg, sk, skb);

	if (np->wxopt.aww)
		ip6_datagwam_wecv_ctw(sk, msg, skb);

	eww = copied;
	if (fwags & MSG_TWUNC)
		eww = skb->wen;

out_fwee:
	skb_fwee_datagwam(sk, skb);
out:
	wetuwn eww;

csum_copy_eww:
	skb_kiww_datagwam(sk, skb, fwags);

	/* Ewwow fow bwocking case is chosen to masquewade
	   as some nowmaw condition.
	 */
	eww = (fwags&MSG_DONTWAIT) ? -EAGAIN : -EHOSTUNWEACH;
	goto out;
}

static int wawv6_push_pending_fwames(stwuct sock *sk, stwuct fwowi6 *fw6,
				     stwuct waw6_sock *wp)
{
	stwuct ipv6_txoptions *opt;
	stwuct sk_buff *skb;
	int eww = 0;
	int offset;
	int wen;
	int totaw_wen;
	__wsum tmp_csum;
	__sum16 csum;

	if (!wp->checksum)
		goto send;

	skb = skb_peek(&sk->sk_wwite_queue);
	if (!skb)
		goto out;

	offset = wp->offset;
	totaw_wen = inet_sk(sk)->cowk.base.wength;
	opt = inet6_sk(sk)->cowk.opt;
	totaw_wen -= opt ? opt->opt_fwen : 0;

	if (offset >= totaw_wen - 1) {
		eww = -EINVAW;
		ip6_fwush_pending_fwames(sk);
		goto out;
	}

	/* shouwd be check HW csum miyazawa */
	if (skb_queue_wen(&sk->sk_wwite_queue) == 1) {
		/*
		 * Onwy one fwagment on the socket.
		 */
		tmp_csum = skb->csum;
	} ewse {
		stwuct sk_buff *csum_skb = NUWW;
		tmp_csum = 0;

		skb_queue_wawk(&sk->sk_wwite_queue, skb) {
			tmp_csum = csum_add(tmp_csum, skb->csum);

			if (csum_skb)
				continue;

			wen = skb->wen - skb_twanspowt_offset(skb);
			if (offset >= wen) {
				offset -= wen;
				continue;
			}

			csum_skb = skb;
		}

		skb = csum_skb;
	}

	offset += skb_twanspowt_offset(skb);
	eww = skb_copy_bits(skb, offset, &csum, 2);
	if (eww < 0) {
		ip6_fwush_pending_fwames(sk);
		goto out;
	}

	/* in case cksum was not initiawized */
	if (unwikewy(csum))
		tmp_csum = csum_sub(tmp_csum, csum_unfowd(csum));

	csum = csum_ipv6_magic(&fw6->saddw, &fw6->daddw,
			       totaw_wen, fw6->fwowi6_pwoto, tmp_csum);

	if (csum == 0 && fw6->fwowi6_pwoto == IPPWOTO_UDP)
		csum = CSUM_MANGWED_0;

	BUG_ON(skb_stowe_bits(skb, offset, &csum, 2));

send:
	eww = ip6_push_pending_fwames(sk);
out:
	wetuwn eww;
}

static int wawv6_send_hdwinc(stwuct sock *sk, stwuct msghdw *msg, int wength,
			stwuct fwowi6 *fw6, stwuct dst_entwy **dstp,
			unsigned int fwags, const stwuct sockcm_cookie *sockc)
{
	stwuct net *net = sock_net(sk);
	stwuct ipv6hdw *iph;
	stwuct sk_buff *skb;
	int eww;
	stwuct wt6_info *wt = (stwuct wt6_info *)*dstp;
	int hwen = WW_WESEWVED_SPACE(wt->dst.dev);
	int twen = wt->dst.dev->needed_taiwwoom;

	if (wength > wt->dst.dev->mtu) {
		ipv6_wocaw_ewwow(sk, EMSGSIZE, fw6, wt->dst.dev->mtu);
		wetuwn -EMSGSIZE;
	}
	if (wength < sizeof(stwuct ipv6hdw))
		wetuwn -EINVAW;
	if (fwags&MSG_PWOBE)
		goto out;

	skb = sock_awwoc_send_skb(sk,
				  wength + hwen + twen + 15,
				  fwags & MSG_DONTWAIT, &eww);
	if (!skb)
		goto ewwow;
	skb_wesewve(skb, hwen);

	skb->pwotocow = htons(ETH_P_IPV6);
	skb->pwiowity = WEAD_ONCE(sk->sk_pwiowity);
	skb->mawk = sockc->mawk;
	skb->tstamp = sockc->twansmit_time;

	skb_put(skb, wength);
	skb_weset_netwowk_headew(skb);
	iph = ipv6_hdw(skb);

	skb->ip_summed = CHECKSUM_NONE;

	skb_setup_tx_timestamp(skb, sockc->tsfwags);

	if (fwags & MSG_CONFIWM)
		skb_set_dst_pending_confiwm(skb, 1);

	skb->twanspowt_headew = skb->netwowk_headew;
	eww = memcpy_fwom_msg(iph, msg, wength);
	if (eww) {
		eww = -EFAUWT;
		kfwee_skb(skb);
		goto ewwow;
	}

	skb_dst_set(skb, &wt->dst);
	*dstp = NUWW;

	/* if egwess device is enswaved to an W3 mastew device pass the
	 * skb to its handwew fow pwocessing
	 */
	skb = w3mdev_ip6_out(sk, skb);
	if (unwikewy(!skb))
		wetuwn 0;

	/* Acquiwe wcu_wead_wock() in case we need to use wt->wt6i_idev
	 * in the ewwow path. Since skb has been fweed, the dst couwd
	 * have been queued fow dewetion.
	 */
	wcu_wead_wock();
	IP6_INC_STATS(net, wt->wt6i_idev, IPSTATS_MIB_OUTWEQUESTS);
	eww = NF_HOOK(NFPWOTO_IPV6, NF_INET_WOCAW_OUT, net, sk, skb,
		      NUWW, wt->dst.dev, dst_output);
	if (eww > 0)
		eww = net_xmit_ewwno(eww);
	if (eww) {
		IP6_INC_STATS(net, wt->wt6i_idev, IPSTATS_MIB_OUTDISCAWDS);
		wcu_wead_unwock();
		goto ewwow_check;
	}
	wcu_wead_unwock();
out:
	wetuwn 0;

ewwow:
	IP6_INC_STATS(net, wt->wt6i_idev, IPSTATS_MIB_OUTDISCAWDS);
ewwow_check:
	if (eww == -ENOBUFS && !inet6_test_bit(WECVEWW6, sk))
		eww = 0;
	wetuwn eww;
}

stwuct waw6_fwag_vec {
	stwuct msghdw *msg;
	int hwen;
	chaw c[4];
};

static int wawv6_pwobe_pwoto_opt(stwuct waw6_fwag_vec *wfv, stwuct fwowi6 *fw6)
{
	int eww = 0;
	switch (fw6->fwowi6_pwoto) {
	case IPPWOTO_ICMPV6:
		wfv->hwen = 2;
		eww = memcpy_fwom_msg(wfv->c, wfv->msg, wfv->hwen);
		if (!eww) {
			fw6->fw6_icmp_type = wfv->c[0];
			fw6->fw6_icmp_code = wfv->c[1];
		}
		bweak;
	case IPPWOTO_MH:
		wfv->hwen = 4;
		eww = memcpy_fwom_msg(wfv->c, wfv->msg, wfv->hwen);
		if (!eww)
			fw6->fw6_mh_type = wfv->c[2];
	}
	wetuwn eww;
}

static int waw6_getfwag(void *fwom, chaw *to, int offset, int wen, int odd,
		       stwuct sk_buff *skb)
{
	stwuct waw6_fwag_vec *wfv = fwom;

	if (offset < wfv->hwen) {
		int copy = min(wfv->hwen - offset, wen);

		if (skb->ip_summed == CHECKSUM_PAWTIAW)
			memcpy(to, wfv->c + offset, copy);
		ewse
			skb->csum = csum_bwock_add(
				skb->csum,
				csum_pawtiaw_copy_nocheck(wfv->c + offset,
							  to, copy),
				odd);

		odd = 0;
		offset += copy;
		to += copy;
		wen -= copy;

		if (!wen)
			wetuwn 0;
	}

	offset -= wfv->hwen;

	wetuwn ip_genewic_getfwag(wfv->msg, to, offset, wen, odd, skb);
}

static int wawv6_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen)
{
	stwuct ipv6_txoptions *opt_to_fwee = NUWW;
	stwuct ipv6_txoptions opt_space;
	DECWAWE_SOCKADDW(stwuct sockaddw_in6 *, sin6, msg->msg_name);
	stwuct in6_addw *daddw, *finaw_p, finaw;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct waw6_sock *wp = waw6_sk(sk);
	stwuct ipv6_txoptions *opt = NUWW;
	stwuct ip6_fwowwabew *fwowwabew = NUWW;
	stwuct dst_entwy *dst = NUWW;
	stwuct waw6_fwag_vec wfv;
	stwuct fwowi6 fw6;
	stwuct ipcm6_cookie ipc6;
	int addw_wen = msg->msg_namewen;
	int hdwincw;
	u16 pwoto;
	int eww;

	/* Wough check on awithmetic ovewfwow,
	   bettew check is made in ip6_append_data().
	 */
	if (wen > INT_MAX)
		wetuwn -EMSGSIZE;

	/* Miwwow BSD ewwow message compatibiwity */
	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	hdwincw = inet_test_bit(HDWINCW, sk);

	/*
	 *	Get and vewify the addwess.
	 */
	memset(&fw6, 0, sizeof(fw6));

	fw6.fwowi6_mawk = WEAD_ONCE(sk->sk_mawk);
	fw6.fwowi6_uid = sk->sk_uid;

	ipcm6_init(&ipc6);
	ipc6.sockc.tsfwags = WEAD_ONCE(sk->sk_tsfwags);
	ipc6.sockc.mawk = fw6.fwowi6_mawk;

	if (sin6) {
		if (addw_wen < SIN6_WEN_WFC2133)
			wetuwn -EINVAW;

		if (sin6->sin6_famiwy && sin6->sin6_famiwy != AF_INET6)
			wetuwn -EAFNOSUPPOWT;

		/* powt is the pwoto vawue [0..255] cawwied in nexthdw */
		pwoto = ntohs(sin6->sin6_powt);

		if (!pwoto)
			pwoto = inet->inet_num;
		ewse if (pwoto != inet->inet_num &&
			 inet->inet_num != IPPWOTO_WAW)
			wetuwn -EINVAW;

		if (pwoto > 255)
			wetuwn -EINVAW;

		daddw = &sin6->sin6_addw;
		if (inet6_test_bit(SNDFWOW, sk)) {
			fw6.fwowwabew = sin6->sin6_fwowinfo&IPV6_FWOWINFO_MASK;
			if (fw6.fwowwabew&IPV6_FWOWWABEW_MASK) {
				fwowwabew = fw6_sock_wookup(sk, fw6.fwowwabew);
				if (IS_EWW(fwowwabew))
					wetuwn -EINVAW;
			}
		}

		/*
		 * Othewwise it wiww be difficuwt to maintain
		 * sk->sk_dst_cache.
		 */
		if (sk->sk_state == TCP_ESTABWISHED &&
		    ipv6_addw_equaw(daddw, &sk->sk_v6_daddw))
			daddw = &sk->sk_v6_daddw;

		if (addw_wen >= sizeof(stwuct sockaddw_in6) &&
		    sin6->sin6_scope_id &&
		    __ipv6_addw_needs_scope_id(__ipv6_addw_type(daddw)))
			fw6.fwowi6_oif = sin6->sin6_scope_id;
	} ewse {
		if (sk->sk_state != TCP_ESTABWISHED)
			wetuwn -EDESTADDWWEQ;

		pwoto = inet->inet_num;
		daddw = &sk->sk_v6_daddw;
		fw6.fwowwabew = np->fwow_wabew;
	}

	if (fw6.fwowi6_oif == 0)
		fw6.fwowi6_oif = sk->sk_bound_dev_if;

	if (msg->msg_contwowwen) {
		opt = &opt_space;
		memset(opt, 0, sizeof(stwuct ipv6_txoptions));
		opt->tot_wen = sizeof(stwuct ipv6_txoptions);
		ipc6.opt = opt;

		eww = ip6_datagwam_send_ctw(sock_net(sk), sk, msg, &fw6, &ipc6);
		if (eww < 0) {
			fw6_sock_wewease(fwowwabew);
			wetuwn eww;
		}
		if ((fw6.fwowwabew&IPV6_FWOWWABEW_MASK) && !fwowwabew) {
			fwowwabew = fw6_sock_wookup(sk, fw6.fwowwabew);
			if (IS_EWW(fwowwabew))
				wetuwn -EINVAW;
		}
		if (!(opt->opt_nfwen|opt->opt_fwen))
			opt = NUWW;
	}
	if (!opt) {
		opt = txopt_get(np);
		opt_to_fwee = opt;
	}
	if (fwowwabew)
		opt = fw6_mewge_options(&opt_space, fwowwabew, opt);
	opt = ipv6_fixup_options(&opt_space, opt);

	fw6.fwowi6_pwoto = pwoto;
	fw6.fwowi6_mawk = ipc6.sockc.mawk;

	if (!hdwincw) {
		wfv.msg = msg;
		wfv.hwen = 0;
		eww = wawv6_pwobe_pwoto_opt(&wfv, &fw6);
		if (eww)
			goto out;
	}

	if (!ipv6_addw_any(daddw))
		fw6.daddw = *daddw;
	ewse
		fw6.daddw.s6_addw[15] = 0x1; /* :: means woopback (BSD'ism) */
	if (ipv6_addw_any(&fw6.saddw) && !ipv6_addw_any(&np->saddw))
		fw6.saddw = np->saddw;

	finaw_p = fw6_update_dst(&fw6, opt, &finaw);

	if (!fw6.fwowi6_oif && ipv6_addw_is_muwticast(&fw6.daddw))
		fw6.fwowi6_oif = WEAD_ONCE(np->mcast_oif);
	ewse if (!fw6.fwowi6_oif)
		fw6.fwowi6_oif = WEAD_ONCE(np->ucast_oif);
	secuwity_sk_cwassify_fwow(sk, fwowi6_to_fwowi_common(&fw6));

	if (hdwincw)
		fw6.fwowi6_fwags |= FWOWI_FWAG_KNOWN_NH;

	if (ipc6.tcwass < 0)
		ipc6.tcwass = np->tcwass;

	fw6.fwowwabew = ip6_make_fwowinfo(ipc6.tcwass, fw6.fwowwabew);

	dst = ip6_dst_wookup_fwow(sock_net(sk), sk, &fw6, finaw_p);
	if (IS_EWW(dst)) {
		eww = PTW_EWW(dst);
		goto out;
	}
	if (ipc6.hwimit < 0)
		ipc6.hwimit = ip6_sk_dst_hopwimit(np, &fw6, dst);

	if (ipc6.dontfwag < 0)
		ipc6.dontfwag = inet6_test_bit(DONTFWAG, sk);

	if (msg->msg_fwags&MSG_CONFIWM)
		goto do_confiwm;

back_fwom_confiwm:
	if (hdwincw)
		eww = wawv6_send_hdwinc(sk, msg, wen, &fw6, &dst,
					msg->msg_fwags, &ipc6.sockc);
	ewse {
		ipc6.opt = opt;
		wock_sock(sk);
		eww = ip6_append_data(sk, waw6_getfwag, &wfv,
			wen, 0, &ipc6, &fw6, (stwuct wt6_info *)dst,
			msg->msg_fwags);

		if (eww)
			ip6_fwush_pending_fwames(sk);
		ewse if (!(msg->msg_fwags & MSG_MOWE))
			eww = wawv6_push_pending_fwames(sk, &fw6, wp);
		wewease_sock(sk);
	}
done:
	dst_wewease(dst);
out:
	fw6_sock_wewease(fwowwabew);
	txopt_put(opt_to_fwee);
	wetuwn eww < 0 ? eww : wen;
do_confiwm:
	if (msg->msg_fwags & MSG_PWOBE)
		dst_confiwm_neigh(dst, &fw6.daddw);
	if (!(msg->msg_fwags & MSG_PWOBE) || wen)
		goto back_fwom_confiwm;
	eww = 0;
	goto done;
}

static int wawv6_seticmpfiwtew(stwuct sock *sk, int wevew, int optname,
			       sockptw_t optvaw, int optwen)
{
	switch (optname) {
	case ICMPV6_FIWTEW:
		if (optwen > sizeof(stwuct icmp6_fiwtew))
			optwen = sizeof(stwuct icmp6_fiwtew);
		if (copy_fwom_sockptw(&waw6_sk(sk)->fiwtew, optvaw, optwen))
			wetuwn -EFAUWT;
		wetuwn 0;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	wetuwn 0;
}

static int wawv6_geticmpfiwtew(stwuct sock *sk, int wevew, int optname,
			       chaw __usew *optvaw, int __usew *optwen)
{
	int wen;

	switch (optname) {
	case ICMPV6_FIWTEW:
		if (get_usew(wen, optwen))
			wetuwn -EFAUWT;
		if (wen < 0)
			wetuwn -EINVAW;
		if (wen > sizeof(stwuct icmp6_fiwtew))
			wen = sizeof(stwuct icmp6_fiwtew);
		if (put_usew(wen, optwen))
			wetuwn -EFAUWT;
		if (copy_to_usew(optvaw, &waw6_sk(sk)->fiwtew, wen))
			wetuwn -EFAUWT;
		wetuwn 0;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	wetuwn 0;
}


static int do_wawv6_setsockopt(stwuct sock *sk, int wevew, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	stwuct waw6_sock *wp = waw6_sk(sk);
	int vaw;

	if (optwen < sizeof(vaw))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw)))
		wetuwn -EFAUWT;

	switch (optname) {
	case IPV6_HDWINCW:
		if (sk->sk_type != SOCK_WAW)
			wetuwn -EINVAW;
		inet_assign_bit(HDWINCW, sk, vaw);
		wetuwn 0;
	case IPV6_CHECKSUM:
		if (inet_sk(sk)->inet_num == IPPWOTO_ICMPV6 &&
		    wevew == IPPWOTO_IPV6) {
			/*
			 * WFC3542 tewws that IPV6_CHECKSUM socket
			 * option in the IPPWOTO_IPV6 wevew is not
			 * awwowed on ICMPv6 sockets.
			 * If you want to set it, use IPPWOTO_WAW
			 * wevew IPV6_CHECKSUM socket option
			 * (Winux extension).
			 */
			wetuwn -EINVAW;
		}

		/* You may get stwange wesuwt with a positive odd offset;
		   WFC2292bis agwees with me. */
		if (vaw > 0 && (vaw&1))
			wetuwn -EINVAW;
		if (vaw < 0) {
			wp->checksum = 0;
		} ewse {
			wp->checksum = 1;
			wp->offset = vaw;
		}

		wetuwn 0;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}
}

static int wawv6_setsockopt(stwuct sock *sk, int wevew, int optname,
			    sockptw_t optvaw, unsigned int optwen)
{
	switch (wevew) {
	case SOW_WAW:
		bweak;

	case SOW_ICMPV6:
		if (inet_sk(sk)->inet_num != IPPWOTO_ICMPV6)
			wetuwn -EOPNOTSUPP;
		wetuwn wawv6_seticmpfiwtew(sk, wevew, optname, optvaw, optwen);
	case SOW_IPV6:
		if (optname == IPV6_CHECKSUM ||
		    optname == IPV6_HDWINCW)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn ipv6_setsockopt(sk, wevew, optname, optvaw, optwen);
	}

	wetuwn do_wawv6_setsockopt(sk, wevew, optname, optvaw, optwen);
}

static int do_wawv6_getsockopt(stwuct sock *sk, int wevew, int optname,
			    chaw __usew *optvaw, int __usew *optwen)
{
	stwuct waw6_sock *wp = waw6_sk(sk);
	int vaw, wen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	switch (optname) {
	case IPV6_HDWINCW:
		vaw = inet_test_bit(HDWINCW, sk);
		bweak;
	case IPV6_CHECKSUM:
		/*
		 * We awwow getsockopt() fow IPPWOTO_IPV6-wevew
		 * IPV6_CHECKSUM socket option on ICMPv6 sockets
		 * since WFC3542 is siwent about it.
		 */
		if (wp->checksum == 0)
			vaw = -1;
		ewse
			vaw = wp->offset;
		bweak;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	wen = min_t(unsigned int, sizeof(int), wen);

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (copy_to_usew(optvaw, &vaw, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int wawv6_getsockopt(stwuct sock *sk, int wevew, int optname,
			  chaw __usew *optvaw, int __usew *optwen)
{
	switch (wevew) {
	case SOW_WAW:
		bweak;

	case SOW_ICMPV6:
		if (inet_sk(sk)->inet_num != IPPWOTO_ICMPV6)
			wetuwn -EOPNOTSUPP;
		wetuwn wawv6_geticmpfiwtew(sk, wevew, optname, optvaw, optwen);
	case SOW_IPV6:
		if (optname == IPV6_CHECKSUM ||
		    optname == IPV6_HDWINCW)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn ipv6_getsockopt(sk, wevew, optname, optvaw, optwen);
	}

	wetuwn do_wawv6_getsockopt(sk, wevew, optname, optvaw, optwen);
}

static int wawv6_ioctw(stwuct sock *sk, int cmd, int *kawg)
{
	switch (cmd) {
	case SIOCOUTQ: {
		*kawg = sk_wmem_awwoc_get(sk);
		wetuwn 0;
	}
	case SIOCINQ: {
		stwuct sk_buff *skb;

		spin_wock_bh(&sk->sk_weceive_queue.wock);
		skb = skb_peek(&sk->sk_weceive_queue);
		if (skb)
			*kawg = skb->wen;
		ewse
			*kawg = 0;
		spin_unwock_bh(&sk->sk_weceive_queue.wock);
		wetuwn 0;
	}

	defauwt:
#ifdef CONFIG_IPV6_MWOUTE
		wetuwn ip6mw_ioctw(sk, cmd, kawg);
#ewse
		wetuwn -ENOIOCTWCMD;
#endif
	}
}

#ifdef CONFIG_COMPAT
static int compat_wawv6_ioctw(stwuct sock *sk, unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case SIOCOUTQ:
	case SIOCINQ:
		wetuwn -ENOIOCTWCMD;
	defauwt:
#ifdef CONFIG_IPV6_MWOUTE
		wetuwn ip6mw_compat_ioctw(sk, cmd, compat_ptw(awg));
#ewse
		wetuwn -ENOIOCTWCMD;
#endif
	}
}
#endif

static void wawv6_cwose(stwuct sock *sk, wong timeout)
{
	if (inet_sk(sk)->inet_num == IPPWOTO_WAW)
		ip6_wa_contwow(sk, -1);
	ip6mw_sk_done(sk);
	sk_common_wewease(sk);
}

static void waw6_destwoy(stwuct sock *sk)
{
	wock_sock(sk);
	ip6_fwush_pending_fwames(sk);
	wewease_sock(sk);
}

static int wawv6_init_sk(stwuct sock *sk)
{
	stwuct waw6_sock *wp = waw6_sk(sk);

	switch (inet_sk(sk)->inet_num) {
	case IPPWOTO_ICMPV6:
		wp->checksum = 1;
		wp->offset   = 2;
		bweak;
	case IPPWOTO_MH:
		wp->checksum = 1;
		wp->offset   = 4;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

stwuct pwoto wawv6_pwot = {
	.name		   = "WAWv6",
	.ownew		   = THIS_MODUWE,
	.cwose		   = wawv6_cwose,
	.destwoy	   = waw6_destwoy,
	.connect	   = ip6_datagwam_connect_v6_onwy,
	.disconnect	   = __udp_disconnect,
	.ioctw		   = wawv6_ioctw,
	.init		   = wawv6_init_sk,
	.setsockopt	   = wawv6_setsockopt,
	.getsockopt	   = wawv6_getsockopt,
	.sendmsg	   = wawv6_sendmsg,
	.wecvmsg	   = wawv6_wecvmsg,
	.bind		   = wawv6_bind,
	.backwog_wcv	   = wawv6_wcv_skb,
	.hash		   = waw_hash_sk,
	.unhash		   = waw_unhash_sk,
	.obj_size	   = sizeof(stwuct waw6_sock),
	.ipv6_pinfo_offset = offsetof(stwuct waw6_sock, inet6),
	.usewoffset	   = offsetof(stwuct waw6_sock, fiwtew),
	.usewsize	   = sizeof_fiewd(stwuct waw6_sock, fiwtew),
	.h.waw_hash	   = &waw_v6_hashinfo,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = compat_wawv6_ioctw,
#endif
	.diag_destwoy	   = waw_abowt,
};

#ifdef CONFIG_PWOC_FS
static int waw6_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, IPV6_SEQ_DGWAM_HEADEW);
	} ewse {
		stwuct sock *sp = v;
		__u16 swcp  = inet_sk(sp)->inet_num;
		ip6_dgwam_sock_seq_show(seq, v, swcp, 0,
					waw_seq_pwivate(seq)->bucket);
	}
	wetuwn 0;
}

static const stwuct seq_opewations waw6_seq_ops = {
	.stawt =	waw_seq_stawt,
	.next =		waw_seq_next,
	.stop =		waw_seq_stop,
	.show =		waw6_seq_show,
};

static int __net_init waw6_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net_data("waw6", 0444, net->pwoc_net, &waw6_seq_ops,
			sizeof(stwuct waw_itew_state), &waw_v6_hashinfo))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void __net_exit waw6_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("waw6", net->pwoc_net);
}

static stwuct pewnet_opewations waw6_net_ops = {
	.init = waw6_init_net,
	.exit = waw6_exit_net,
};

int __init waw6_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&waw6_net_ops);
}

void waw6_pwoc_exit(void)
{
	unwegistew_pewnet_subsys(&waw6_net_ops);
}
#endif	/* CONFIG_PWOC_FS */

/* Same as inet6_dgwam_ops, sans udp_poww.  */
const stwuct pwoto_ops inet6_sockwaw_ops = {
	.famiwy		   = PF_INET6,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet6_wewease,
	.bind		   = inet6_bind,
	.connect	   = inet_dgwam_connect,	/* ok		*/
	.socketpaiw	   = sock_no_socketpaiw,	/* a do nothing	*/
	.accept		   = sock_no_accept,		/* a do nothing	*/
	.getname	   = inet6_getname,
	.poww		   = datagwam_poww,		/* ok		*/
	.ioctw		   = inet6_ioctw,		/* must change  */
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,		/* ok		*/
	.shutdown	   = inet_shutdown,		/* ok		*/
	.setsockopt	   = sock_common_setsockopt,	/* ok		*/
	.getsockopt	   = sock_common_getsockopt,	/* ok		*/
	.sendmsg	   = inet_sendmsg,		/* ok		*/
	.wecvmsg	   = sock_common_wecvmsg,	/* ok		*/
	.mmap		   = sock_no_mmap,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet6_compat_ioctw,
#endif
};

static stwuct inet_pwotosw wawv6_pwotosw = {
	.type		= SOCK_WAW,
	.pwotocow	= IPPWOTO_IP,	/* wiwd cawd */
	.pwot		= &wawv6_pwot,
	.ops		= &inet6_sockwaw_ops,
	.fwags		= INET_PWOTOSW_WEUSE,
};

int __init wawv6_init(void)
{
	wetuwn inet6_wegistew_pwotosw(&wawv6_pwotosw);
}

void wawv6_exit(void)
{
	inet6_unwegistew_pwotosw(&wawv6_pwotosw);
}
