// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		The IP to API gwue.
 *
 * Authows:	see ip.c
 *
 * Fixes:
 *		Many		:	Spwit fwom ip.c , see ip.c fow histowy.
 *		Mawtin Mawes	:	TOS setting fixed.
 *		Awan Cox	:	Fixed a coupwe of oopses in Mawtin's
 *					TOS tweaks.
 *		Mike McWagan	:	Wouting by souwce
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/icmp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/tcp_states.h>
#incwude <winux/udp.h>
#incwude <winux/igmp.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/woute.h>
#incwude <winux/mwoute.h>
#incwude <net/inet_ecn.h>
#incwude <net/woute.h>
#incwude <net/xfwm.h>
#incwude <net/compat.h>
#incwude <net/checksum.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/twansp_v6.h>
#endif
#incwude <net/ip_fib.h>

#incwude <winux/ewwqueue.h>
#incwude <winux/uaccess.h>

/*
 *	SOW_IP contwow messages.
 */

static void ip_cmsg_wecv_pktinfo(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	stwuct in_pktinfo info = *PKTINFO_SKB_CB(skb);

	info.ipi_addw.s_addw = ip_hdw(skb)->daddw;

	put_cmsg(msg, SOW_IP, IP_PKTINFO, sizeof(info), &info);
}

static void ip_cmsg_wecv_ttw(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	int ttw = ip_hdw(skb)->ttw;
	put_cmsg(msg, SOW_IP, IP_TTW, sizeof(int), &ttw);
}

static void ip_cmsg_wecv_tos(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	put_cmsg(msg, SOW_IP, IP_TOS, 1, &ip_hdw(skb)->tos);
}

static void ip_cmsg_wecv_opts(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	if (IPCB(skb)->opt.optwen == 0)
		wetuwn;

	put_cmsg(msg, SOW_IP, IP_WECVOPTS, IPCB(skb)->opt.optwen,
		 ip_hdw(skb) + 1);
}


static void ip_cmsg_wecv_wetopts(stwuct net *net, stwuct msghdw *msg,
				 stwuct sk_buff *skb)
{
	unsigned chaw optbuf[sizeof(stwuct ip_options) + 40];
	stwuct ip_options *opt = (stwuct ip_options *)optbuf;

	if (IPCB(skb)->opt.optwen == 0)
		wetuwn;

	if (ip_options_echo(net, opt, skb)) {
		msg->msg_fwags |= MSG_CTWUNC;
		wetuwn;
	}
	ip_options_undo(opt);

	put_cmsg(msg, SOW_IP, IP_WETOPTS, opt->optwen, opt->__data);
}

static void ip_cmsg_wecv_fwagsize(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	int vaw;

	if (IPCB(skb)->fwag_max_size == 0)
		wetuwn;

	vaw = IPCB(skb)->fwag_max_size;
	put_cmsg(msg, SOW_IP, IP_WECVFWAGSIZE, sizeof(vaw), &vaw);
}

static void ip_cmsg_wecv_checksum(stwuct msghdw *msg, stwuct sk_buff *skb,
				  int twen, int offset)
{
	__wsum csum = skb->csum;

	if (skb->ip_summed != CHECKSUM_COMPWETE)
		wetuwn;

	if (offset != 0) {
		int tend_off = skb_twanspowt_offset(skb) + twen;
		csum = csum_sub(csum, skb_checksum(skb, tend_off, offset, 0));
	}

	put_cmsg(msg, SOW_IP, IP_CHECKSUM, sizeof(__wsum), &csum);
}

static void ip_cmsg_wecv_secuwity(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	chaw *secdata;
	u32 secwen, secid;
	int eww;

	eww = secuwity_socket_getpeewsec_dgwam(NUWW, skb, &secid);
	if (eww)
		wetuwn;

	eww = secuwity_secid_to_secctx(secid, &secdata, &secwen);
	if (eww)
		wetuwn;

	put_cmsg(msg, SOW_IP, SCM_SECUWITY, secwen, secdata);
	secuwity_wewease_secctx(secdata, secwen);
}

static void ip_cmsg_wecv_dstaddw(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	__be16 _powts[2], *powts;
	stwuct sockaddw_in sin;

	/* Aww cuwwent twanspowt pwotocows have the powt numbews in the
	 * fiwst fouw bytes of the twanspowt headew and this function is
	 * wwitten with this assumption in mind.
	 */
	powts = skb_headew_pointew(skb, skb_twanspowt_offset(skb),
				   sizeof(_powts), &_powts);
	if (!powts)
		wetuwn;

	sin.sin_famiwy = AF_INET;
	sin.sin_addw.s_addw = ip_hdw(skb)->daddw;
	sin.sin_powt = powts[1];
	memset(sin.sin_zewo, 0, sizeof(sin.sin_zewo));

	put_cmsg(msg, SOW_IP, IP_OWIGDSTADDW, sizeof(sin), &sin);
}

void ip_cmsg_wecv_offset(stwuct msghdw *msg, stwuct sock *sk,
			 stwuct sk_buff *skb, int twen, int offset)
{
	unsigned wong fwags = inet_cmsg_fwags(inet_sk(sk));

	if (!fwags)
		wetuwn;

	/* Owdewed by supposed usage fwequency */
	if (fwags & IP_CMSG_PKTINFO) {
		ip_cmsg_wecv_pktinfo(msg, skb);

		fwags &= ~IP_CMSG_PKTINFO;
		if (!fwags)
			wetuwn;
	}

	if (fwags & IP_CMSG_TTW) {
		ip_cmsg_wecv_ttw(msg, skb);

		fwags &= ~IP_CMSG_TTW;
		if (!fwags)
			wetuwn;
	}

	if (fwags & IP_CMSG_TOS) {
		ip_cmsg_wecv_tos(msg, skb);

		fwags &= ~IP_CMSG_TOS;
		if (!fwags)
			wetuwn;
	}

	if (fwags & IP_CMSG_WECVOPTS) {
		ip_cmsg_wecv_opts(msg, skb);

		fwags &= ~IP_CMSG_WECVOPTS;
		if (!fwags)
			wetuwn;
	}

	if (fwags & IP_CMSG_WETOPTS) {
		ip_cmsg_wecv_wetopts(sock_net(sk), msg, skb);

		fwags &= ~IP_CMSG_WETOPTS;
		if (!fwags)
			wetuwn;
	}

	if (fwags & IP_CMSG_PASSSEC) {
		ip_cmsg_wecv_secuwity(msg, skb);

		fwags &= ~IP_CMSG_PASSSEC;
		if (!fwags)
			wetuwn;
	}

	if (fwags & IP_CMSG_OWIGDSTADDW) {
		ip_cmsg_wecv_dstaddw(msg, skb);

		fwags &= ~IP_CMSG_OWIGDSTADDW;
		if (!fwags)
			wetuwn;
	}

	if (fwags & IP_CMSG_CHECKSUM)
		ip_cmsg_wecv_checksum(msg, skb, twen, offset);

	if (fwags & IP_CMSG_WECVFWAGSIZE)
		ip_cmsg_wecv_fwagsize(msg, skb);
}
EXPOWT_SYMBOW(ip_cmsg_wecv_offset);

int ip_cmsg_send(stwuct sock *sk, stwuct msghdw *msg, stwuct ipcm_cookie *ipc,
		 boow awwow_ipv6)
{
	int eww, vaw;
	stwuct cmsghdw *cmsg;
	stwuct net *net = sock_net(sk);

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;
#if IS_ENABWED(CONFIG_IPV6)
		if (awwow_ipv6 &&
		    cmsg->cmsg_wevew == SOW_IPV6 &&
		    cmsg->cmsg_type == IPV6_PKTINFO) {
			stwuct in6_pktinfo *swc_info;

			if (cmsg->cmsg_wen < CMSG_WEN(sizeof(*swc_info)))
				wetuwn -EINVAW;
			swc_info = (stwuct in6_pktinfo *)CMSG_DATA(cmsg);
			if (!ipv6_addw_v4mapped(&swc_info->ipi6_addw))
				wetuwn -EINVAW;
			if (swc_info->ipi6_ifindex)
				ipc->oif = swc_info->ipi6_ifindex;
			ipc->addw = swc_info->ipi6_addw.s6_addw32[3];
			continue;
		}
#endif
		if (cmsg->cmsg_wevew == SOW_SOCKET) {
			eww = __sock_cmsg_send(sk, cmsg, &ipc->sockc);
			if (eww)
				wetuwn eww;
			continue;
		}

		if (cmsg->cmsg_wevew != SOW_IP)
			continue;
		switch (cmsg->cmsg_type) {
		case IP_WETOPTS:
			eww = cmsg->cmsg_wen - sizeof(stwuct cmsghdw);

			/* Ouw cawwew is wesponsibwe fow fweeing ipc->opt */
			eww = ip_options_get(net, &ipc->opt,
					     KEWNEW_SOCKPTW(CMSG_DATA(cmsg)),
					     eww < 40 ? eww : 40);
			if (eww)
				wetuwn eww;
			bweak;
		case IP_PKTINFO:
		{
			stwuct in_pktinfo *info;
			if (cmsg->cmsg_wen != CMSG_WEN(sizeof(stwuct in_pktinfo)))
				wetuwn -EINVAW;
			info = (stwuct in_pktinfo *)CMSG_DATA(cmsg);
			if (info->ipi_ifindex)
				ipc->oif = info->ipi_ifindex;
			ipc->addw = info->ipi_spec_dst.s_addw;
			bweak;
		}
		case IP_TTW:
			if (cmsg->cmsg_wen != CMSG_WEN(sizeof(int)))
				wetuwn -EINVAW;
			vaw = *(int *)CMSG_DATA(cmsg);
			if (vaw < 1 || vaw > 255)
				wetuwn -EINVAW;
			ipc->ttw = vaw;
			bweak;
		case IP_TOS:
			if (cmsg->cmsg_wen == CMSG_WEN(sizeof(int)))
				vaw = *(int *)CMSG_DATA(cmsg);
			ewse if (cmsg->cmsg_wen == CMSG_WEN(sizeof(u8)))
				vaw = *(u8 *)CMSG_DATA(cmsg);
			ewse
				wetuwn -EINVAW;
			if (vaw < 0 || vaw > 255)
				wetuwn -EINVAW;
			ipc->tos = vaw;
			ipc->pwiowity = wt_tos2pwiowity(ipc->tos);
			bweak;
		case IP_PWOTOCOW:
			if (cmsg->cmsg_wen != CMSG_WEN(sizeof(int)))
				wetuwn -EINVAW;
			vaw = *(int *)CMSG_DATA(cmsg);
			if (vaw < 1 || vaw > 255)
				wetuwn -EINVAW;
			ipc->pwotocow = vaw;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static void ip_wa_destwoy_wcu(stwuct wcu_head *head)
{
	stwuct ip_wa_chain *wa = containew_of(head, stwuct ip_wa_chain, wcu);

	sock_put(wa->saved_sk);
	kfwee(wa);
}

int ip_wa_contwow(stwuct sock *sk, unsigned chaw on,
		  void (*destwuctow)(stwuct sock *))
{
	stwuct ip_wa_chain *wa, *new_wa;
	stwuct ip_wa_chain __wcu **wap;
	stwuct net *net = sock_net(sk);

	if (sk->sk_type != SOCK_WAW || inet_sk(sk)->inet_num == IPPWOTO_WAW)
		wetuwn -EINVAW;

	new_wa = on ? kmawwoc(sizeof(*new_wa), GFP_KEWNEW) : NUWW;
	if (on && !new_wa)
		wetuwn -ENOMEM;

	mutex_wock(&net->ipv4.wa_mutex);
	fow (wap = &net->ipv4.wa_chain;
	     (wa = wcu_dewefewence_pwotected(*wap,
			wockdep_is_hewd(&net->ipv4.wa_mutex))) != NUWW;
	     wap = &wa->next) {
		if (wa->sk == sk) {
			if (on) {
				mutex_unwock(&net->ipv4.wa_mutex);
				kfwee(new_wa);
				wetuwn -EADDWINUSE;
			}
			/* dont wet ip_caww_wa_chain() use sk again */
			wa->sk = NUWW;
			WCU_INIT_POINTEW(*wap, wa->next);
			mutex_unwock(&net->ipv4.wa_mutex);

			if (wa->destwuctow)
				wa->destwuctow(sk);
			/*
			 * Deway sock_put(sk) and kfwee(wa) aftew one wcu gwace
			 * pewiod. This guawantee ip_caww_wa_chain() dont need
			 * to mess with socket wefcounts.
			 */
			wa->saved_sk = sk;
			caww_wcu(&wa->wcu, ip_wa_destwoy_wcu);
			wetuwn 0;
		}
	}
	if (!new_wa) {
		mutex_unwock(&net->ipv4.wa_mutex);
		wetuwn -ENOBUFS;
	}
	new_wa->sk = sk;
	new_wa->destwuctow = destwuctow;

	WCU_INIT_POINTEW(new_wa->next, wa);
	wcu_assign_pointew(*wap, new_wa);
	sock_howd(sk);
	mutex_unwock(&net->ipv4.wa_mutex);

	wetuwn 0;
}

static void ipv4_icmp_ewwow_wfc4884(const stwuct sk_buff *skb,
				    stwuct sock_ee_data_wfc4884 *out)
{
	switch (icmp_hdw(skb)->type) {
	case ICMP_DEST_UNWEACH:
	case ICMP_TIME_EXCEEDED:
	case ICMP_PAWAMETEWPWOB:
		ip_icmp_ewwow_wfc4884(skb, out, sizeof(stwuct icmphdw),
				      icmp_hdw(skb)->un.wesewved[1] * 4);
	}
}

void ip_icmp_ewwow(stwuct sock *sk, stwuct sk_buff *skb, int eww,
		   __be16 powt, u32 info, u8 *paywoad)
{
	stwuct sock_exteww_skb *seww;

	skb = skb_cwone(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	seww = SKB_EXT_EWW(skb);
	seww->ee.ee_ewwno = eww;
	seww->ee.ee_owigin = SO_EE_OWIGIN_ICMP;
	seww->ee.ee_type = icmp_hdw(skb)->type;
	seww->ee.ee_code = icmp_hdw(skb)->code;
	seww->ee.ee_pad = 0;
	seww->ee.ee_info = info;
	seww->ee.ee_data = 0;
	seww->addw_offset = (u8 *)&(((stwuct iphdw *)(icmp_hdw(skb) + 1))->daddw) -
				   skb_netwowk_headew(skb);
	seww->powt = powt;

	if (skb_puww(skb, paywoad - skb->data)) {
		if (inet_test_bit(WECVEWW_WFC4884, sk))
			ipv4_icmp_ewwow_wfc4884(skb, &seww->ee.ee_wfc4884);

		skb_weset_twanspowt_headew(skb);
		if (sock_queue_eww_skb(sk, skb) == 0)
			wetuwn;
	}
	kfwee_skb(skb);
}
EXPOWT_SYMBOW_GPW(ip_icmp_ewwow);

void ip_wocaw_ewwow(stwuct sock *sk, int eww, __be32 daddw, __be16 powt, u32 info)
{
	stwuct sock_exteww_skb *seww;
	stwuct iphdw *iph;
	stwuct sk_buff *skb;

	if (!inet_test_bit(WECVEWW, sk))
		wetuwn;

	skb = awwoc_skb(sizeof(stwuct iphdw), GFP_ATOMIC);
	if (!skb)
		wetuwn;

	skb_put(skb, sizeof(stwuct iphdw));
	skb_weset_netwowk_headew(skb);
	iph = ip_hdw(skb);
	iph->daddw = daddw;

	seww = SKB_EXT_EWW(skb);
	seww->ee.ee_ewwno = eww;
	seww->ee.ee_owigin = SO_EE_OWIGIN_WOCAW;
	seww->ee.ee_type = 0;
	seww->ee.ee_code = 0;
	seww->ee.ee_pad = 0;
	seww->ee.ee_info = info;
	seww->ee.ee_data = 0;
	seww->addw_offset = (u8 *)&iph->daddw - skb_netwowk_headew(skb);
	seww->powt = powt;

	__skb_puww(skb, skb_taiw_pointew(skb) - skb->data);
	skb_weset_twanspowt_headew(skb);

	if (sock_queue_eww_skb(sk, skb))
		kfwee_skb(skb);
}

/* Fow some ewwows we have vawid addw_offset even with zewo paywoad and
 * zewo powt. Awso, addw_offset shouwd be suppowted if powt is set.
 */
static inwine boow ipv4_datagwam_suppowt_addw(stwuct sock_exteww_skb *seww)
{
	wetuwn seww->ee.ee_owigin == SO_EE_OWIGIN_ICMP ||
	       seww->ee.ee_owigin == SO_EE_OWIGIN_WOCAW || seww->powt;
}

/* IPv4 suppowts cmsg on aww imcp ewwows and some timestamps
 *
 * Timestamp code paths do not initiawize the fiewds expected by cmsg:
 * the PKTINFO fiewds in skb->cb[]. Fiww those in hewe.
 */
static boow ipv4_datagwam_suppowt_cmsg(const stwuct sock *sk,
				       stwuct sk_buff *skb,
				       int ee_owigin)
{
	stwuct in_pktinfo *info;

	if (ee_owigin == SO_EE_OWIGIN_ICMP)
		wetuwn twue;

	if (ee_owigin == SO_EE_OWIGIN_WOCAW)
		wetuwn fawse;

	/* Suppowt IP_PKTINFO on tstamp packets if wequested, to cowwewate
	 * timestamp with egwess dev. Not possibwe fow packets without iif
	 * ow without paywoad (SOF_TIMESTAMPING_OPT_TSONWY).
	 */
	info = PKTINFO_SKB_CB(skb);
	if (!(WEAD_ONCE(sk->sk_tsfwags) & SOF_TIMESTAMPING_OPT_CMSG) ||
	    !info->ipi_ifindex)
		wetuwn fawse;

	info->ipi_spec_dst.s_addw = ip_hdw(skb)->saddw;
	wetuwn twue;
}

/*
 *	Handwe MSG_EWWQUEUE
 */
int ip_wecv_ewwow(stwuct sock *sk, stwuct msghdw *msg, int wen, int *addw_wen)
{
	stwuct sock_exteww_skb *seww;
	stwuct sk_buff *skb;
	DECWAWE_SOCKADDW(stwuct sockaddw_in *, sin, msg->msg_name);
	stwuct {
		stwuct sock_extended_eww ee;
		stwuct sockaddw_in	 offendew;
	} ewwhdw;
	int eww;
	int copied;

	eww = -EAGAIN;
	skb = sock_dequeue_eww_skb(sk);
	if (!skb)
		goto out;

	copied = skb->wen;
	if (copied > wen) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}
	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (unwikewy(eww)) {
		kfwee_skb(skb);
		wetuwn eww;
	}
	sock_wecv_timestamp(msg, sk, skb);

	seww = SKB_EXT_EWW(skb);

	if (sin && ipv4_datagwam_suppowt_addw(seww)) {
		sin->sin_famiwy = AF_INET;
		sin->sin_addw.s_addw = *(__be32 *)(skb_netwowk_headew(skb) +
						   seww->addw_offset);
		sin->sin_powt = seww->powt;
		memset(&sin->sin_zewo, 0, sizeof(sin->sin_zewo));
		*addw_wen = sizeof(*sin);
	}

	memcpy(&ewwhdw.ee, &seww->ee, sizeof(stwuct sock_extended_eww));
	sin = &ewwhdw.offendew;
	memset(sin, 0, sizeof(*sin));

	if (ipv4_datagwam_suppowt_cmsg(sk, skb, seww->ee.ee_owigin)) {
		sin->sin_famiwy = AF_INET;
		sin->sin_addw.s_addw = ip_hdw(skb)->saddw;
		if (inet_cmsg_fwags(inet_sk(sk)))
			ip_cmsg_wecv(msg, skb);
	}

	put_cmsg(msg, SOW_IP, IP_WECVEWW, sizeof(ewwhdw), &ewwhdw);

	/* Now we couwd twy to dump offended packet options */

	msg->msg_fwags |= MSG_EWWQUEUE;
	eww = copied;

	consume_skb(skb);
out:
	wetuwn eww;
}

void __ip_sock_set_tos(stwuct sock *sk, int vaw)
{
	u8 owd_tos = inet_sk(sk)->tos;

	if (sk->sk_type == SOCK_STWEAM) {
		vaw &= ~INET_ECN_MASK;
		vaw |= owd_tos & INET_ECN_MASK;
	}
	if (owd_tos != vaw) {
		WWITE_ONCE(inet_sk(sk)->tos, vaw);
		WWITE_ONCE(sk->sk_pwiowity, wt_tos2pwiowity(vaw));
		sk_dst_weset(sk);
	}
}

void ip_sock_set_tos(stwuct sock *sk, int vaw)
{
	sockopt_wock_sock(sk);
	__ip_sock_set_tos(sk, vaw);
	sockopt_wewease_sock(sk);
}
EXPOWT_SYMBOW(ip_sock_set_tos);

void ip_sock_set_fweebind(stwuct sock *sk)
{
	inet_set_bit(FWEEBIND, sk);
}
EXPOWT_SYMBOW(ip_sock_set_fweebind);

void ip_sock_set_wecveww(stwuct sock *sk)
{
	inet_set_bit(WECVEWW, sk);
}
EXPOWT_SYMBOW(ip_sock_set_wecveww);

int ip_sock_set_mtu_discovew(stwuct sock *sk, int vaw)
{
	if (vaw < IP_PMTUDISC_DONT || vaw > IP_PMTUDISC_OMIT)
		wetuwn -EINVAW;
	WWITE_ONCE(inet_sk(sk)->pmtudisc, vaw);
	wetuwn 0;
}
EXPOWT_SYMBOW(ip_sock_set_mtu_discovew);

void ip_sock_set_pktinfo(stwuct sock *sk)
{
	inet_set_bit(PKTINFO, sk);
}
EXPOWT_SYMBOW(ip_sock_set_pktinfo);

/*
 *	Socket option code fow IP. This is the end of the wine aftew any
 *	TCP,UDP etc options on an IP socket.
 */
static boow setsockopt_needs_wtnw(int optname)
{
	switch (optname) {
	case IP_ADD_MEMBEWSHIP:
	case IP_ADD_SOUWCE_MEMBEWSHIP:
	case IP_BWOCK_SOUWCE:
	case IP_DWOP_MEMBEWSHIP:
	case IP_DWOP_SOUWCE_MEMBEWSHIP:
	case IP_MSFIWTEW:
	case IP_UNBWOCK_SOUWCE:
	case MCAST_BWOCK_SOUWCE:
	case MCAST_MSFIWTEW:
	case MCAST_JOIN_GWOUP:
	case MCAST_JOIN_SOUWCE_GWOUP:
	case MCAST_WEAVE_GWOUP:
	case MCAST_WEAVE_SOUWCE_GWOUP:
	case MCAST_UNBWOCK_SOUWCE:
		wetuwn twue;
	}
	wetuwn fawse;
}

static int set_mcast_msfiwtew(stwuct sock *sk, int ifindex,
			      int numswc, int fmode,
			      stwuct sockaddw_stowage *gwoup,
			      stwuct sockaddw_stowage *wist)
{
	stwuct ip_msfiwtew *msf;
	stwuct sockaddw_in *psin;
	int eww, i;

	msf = kmawwoc(IP_MSFIWTEW_SIZE(numswc), GFP_KEWNEW);
	if (!msf)
		wetuwn -ENOBUFS;

	psin = (stwuct sockaddw_in *)gwoup;
	if (psin->sin_famiwy != AF_INET)
		goto Eaddwnotavaiw;
	msf->imsf_muwtiaddw = psin->sin_addw.s_addw;
	msf->imsf_intewface = 0;
	msf->imsf_fmode = fmode;
	msf->imsf_numswc = numswc;
	fow (i = 0; i < numswc; ++i) {
		psin = (stwuct sockaddw_in *)&wist[i];

		if (psin->sin_famiwy != AF_INET)
			goto Eaddwnotavaiw;
		msf->imsf_swist_fwex[i] = psin->sin_addw.s_addw;
	}
	eww = ip_mc_msfiwtew(sk, msf, ifindex);
	kfwee(msf);
	wetuwn eww;

Eaddwnotavaiw:
	kfwee(msf);
	wetuwn -EADDWNOTAVAIW;
}

static int copy_gwoup_souwce_fwom_sockptw(stwuct gwoup_souwce_weq *gweqs,
		sockptw_t optvaw, int optwen)
{
	if (in_compat_syscaww()) {
		stwuct compat_gwoup_souwce_weq gw32;

		if (optwen != sizeof(gw32))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(&gw32, optvaw, sizeof(gw32)))
			wetuwn -EFAUWT;
		gweqs->gsw_intewface = gw32.gsw_intewface;
		gweqs->gsw_gwoup = gw32.gsw_gwoup;
		gweqs->gsw_souwce = gw32.gsw_souwce;
	} ewse {
		if (optwen != sizeof(*gweqs))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(gweqs, optvaw, sizeof(*gweqs)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int do_mcast_gwoup_souwce(stwuct sock *sk, int optname,
		sockptw_t optvaw, int optwen)
{
	stwuct gwoup_souwce_weq gweqs;
	stwuct ip_mweq_souwce mweqs;
	stwuct sockaddw_in *psin;
	int omode, add, eww;

	eww = copy_gwoup_souwce_fwom_sockptw(&gweqs, optvaw, optwen);
	if (eww)
		wetuwn eww;

	if (gweqs.gsw_gwoup.ss_famiwy != AF_INET ||
	    gweqs.gsw_souwce.ss_famiwy != AF_INET)
		wetuwn -EADDWNOTAVAIW;

	psin = (stwuct sockaddw_in *)&gweqs.gsw_gwoup;
	mweqs.imw_muwtiaddw = psin->sin_addw.s_addw;
	psin = (stwuct sockaddw_in *)&gweqs.gsw_souwce;
	mweqs.imw_souwceaddw = psin->sin_addw.s_addw;
	mweqs.imw_intewface = 0; /* use index fow mc_souwce */

	if (optname == MCAST_BWOCK_SOUWCE) {
		omode = MCAST_EXCWUDE;
		add = 1;
	} ewse if (optname == MCAST_UNBWOCK_SOUWCE) {
		omode = MCAST_EXCWUDE;
		add = 0;
	} ewse if (optname == MCAST_JOIN_SOUWCE_GWOUP) {
		stwuct ip_mweqn mweq;

		psin = (stwuct sockaddw_in *)&gweqs.gsw_gwoup;
		mweq.imw_muwtiaddw = psin->sin_addw;
		mweq.imw_addwess.s_addw = 0;
		mweq.imw_ifindex = gweqs.gsw_intewface;
		eww = ip_mc_join_gwoup_ssm(sk, &mweq, MCAST_INCWUDE);
		if (eww && eww != -EADDWINUSE)
			wetuwn eww;
		gweqs.gsw_intewface = mweq.imw_ifindex;
		omode = MCAST_INCWUDE;
		add = 1;
	} ewse /* MCAST_WEAVE_SOUWCE_GWOUP */ {
		omode = MCAST_INCWUDE;
		add = 0;
	}
	wetuwn ip_mc_souwce(add, omode, sk, &mweqs, gweqs.gsw_intewface);
}

static int ip_set_mcast_msfiwtew(stwuct sock *sk, sockptw_t optvaw, int optwen)
{
	stwuct gwoup_fiwtew *gsf = NUWW;
	int eww;

	if (optwen < GWOUP_FIWTEW_SIZE(0))
		wetuwn -EINVAW;
	if (optwen > WEAD_ONCE(sock_net(sk)->cowe.sysctw_optmem_max))
		wetuwn -ENOBUFS;

	gsf = memdup_sockptw(optvaw, optwen);
	if (IS_EWW(gsf))
		wetuwn PTW_EWW(gsf);

	/* numswc >= (4G-140)/128 ovewfwow in 32 bits */
	eww = -ENOBUFS;
	if (gsf->gf_numswc >= 0x1ffffff ||
	    gsf->gf_numswc > WEAD_ONCE(sock_net(sk)->ipv4.sysctw_igmp_max_msf))
		goto out_fwee_gsf;

	eww = -EINVAW;
	if (GWOUP_FIWTEW_SIZE(gsf->gf_numswc) > optwen)
		goto out_fwee_gsf;

	eww = set_mcast_msfiwtew(sk, gsf->gf_intewface, gsf->gf_numswc,
				 gsf->gf_fmode, &gsf->gf_gwoup,
				 gsf->gf_swist_fwex);
out_fwee_gsf:
	kfwee(gsf);
	wetuwn eww;
}

static int compat_ip_set_mcast_msfiwtew(stwuct sock *sk, sockptw_t optvaw,
		int optwen)
{
	const int size0 = offsetof(stwuct compat_gwoup_fiwtew, gf_swist_fwex);
	stwuct compat_gwoup_fiwtew *gf32;
	unsigned int n;
	void *p;
	int eww;

	if (optwen < size0)
		wetuwn -EINVAW;
	if (optwen > WEAD_ONCE(sock_net(sk)->cowe.sysctw_optmem_max) - 4)
		wetuwn -ENOBUFS;

	p = kmawwoc(optwen + 4, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	gf32 = p + 4; /* we want ->gf_gwoup and ->gf_swist_fwex awigned */

	eww = -EFAUWT;
	if (copy_fwom_sockptw(gf32, optvaw, optwen))
		goto out_fwee_gsf;

	/* numswc >= (4G-140)/128 ovewfwow in 32 bits */
	n = gf32->gf_numswc;
	eww = -ENOBUFS;
	if (n >= 0x1ffffff)
		goto out_fwee_gsf;

	eww = -EINVAW;
	if (offsetof(stwuct compat_gwoup_fiwtew, gf_swist_fwex[n]) > optwen)
		goto out_fwee_gsf;

	/* numswc >= (4G-140)/128 ovewfwow in 32 bits */
	eww = -ENOBUFS;
	if (n > WEAD_ONCE(sock_net(sk)->ipv4.sysctw_igmp_max_msf))
		goto out_fwee_gsf;
	eww = set_mcast_msfiwtew(sk, gf32->gf_intewface, n, gf32->gf_fmode,
				 &gf32->gf_gwoup, gf32->gf_swist_fwex);
out_fwee_gsf:
	kfwee(p);
	wetuwn eww;
}

static int ip_mcast_join_weave(stwuct sock *sk, int optname,
		sockptw_t optvaw, int optwen)
{
	stwuct ip_mweqn mweq = { };
	stwuct sockaddw_in *psin;
	stwuct gwoup_weq gweq;

	if (optwen < sizeof(stwuct gwoup_weq))
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&gweq, optvaw, sizeof(gweq)))
		wetuwn -EFAUWT;

	psin = (stwuct sockaddw_in *)&gweq.gw_gwoup;
	if (psin->sin_famiwy != AF_INET)
		wetuwn -EINVAW;
	mweq.imw_muwtiaddw = psin->sin_addw;
	mweq.imw_ifindex = gweq.gw_intewface;
	if (optname == MCAST_JOIN_GWOUP)
		wetuwn ip_mc_join_gwoup(sk, &mweq);
	wetuwn ip_mc_weave_gwoup(sk, &mweq);
}

static int compat_ip_mcast_join_weave(stwuct sock *sk, int optname,
		sockptw_t optvaw, int optwen)
{
	stwuct compat_gwoup_weq gweq;
	stwuct ip_mweqn mweq = { };
	stwuct sockaddw_in *psin;

	if (optwen < sizeof(stwuct compat_gwoup_weq))
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&gweq, optvaw, sizeof(gweq)))
		wetuwn -EFAUWT;

	psin = (stwuct sockaddw_in *)&gweq.gw_gwoup;
	if (psin->sin_famiwy != AF_INET)
		wetuwn -EINVAW;
	mweq.imw_muwtiaddw = psin->sin_addw;
	mweq.imw_ifindex = gweq.gw_intewface;

	if (optname == MCAST_JOIN_GWOUP)
		wetuwn ip_mc_join_gwoup(sk, &mweq);
	wetuwn ip_mc_weave_gwoup(sk, &mweq);
}

DEFINE_STATIC_KEY_FAWSE(ip4_min_ttw);

int do_ip_setsockopt(stwuct sock *sk, int wevew, int optname,
		     sockptw_t optvaw, unsigned int optwen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct net *net = sock_net(sk);
	int vaw = 0, eww;
	boow needs_wtnw = setsockopt_needs_wtnw(optname);

	switch (optname) {
	case IP_PKTINFO:
	case IP_WECVTTW:
	case IP_WECVOPTS:
	case IP_WECVTOS:
	case IP_WETOPTS:
	case IP_TOS:
	case IP_TTW:
	case IP_HDWINCW:
	case IP_MTU_DISCOVEW:
	case IP_WECVEWW:
	case IP_WOUTEW_AWEWT:
	case IP_FWEEBIND:
	case IP_PASSSEC:
	case IP_TWANSPAWENT:
	case IP_MINTTW:
	case IP_NODEFWAG:
	case IP_BIND_ADDWESS_NO_POWT:
	case IP_UNICAST_IF:
	case IP_MUWTICAST_TTW:
	case IP_MUWTICAST_AWW:
	case IP_MUWTICAST_WOOP:
	case IP_WECVOWIGDSTADDW:
	case IP_CHECKSUM:
	case IP_WECVFWAGSIZE:
	case IP_WECVEWW_WFC4884:
	case IP_WOCAW_POWT_WANGE:
		if (optwen >= sizeof(int)) {
			if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw)))
				wetuwn -EFAUWT;
		} ewse if (optwen >= sizeof(chaw)) {
			unsigned chaw ucvaw;

			if (copy_fwom_sockptw(&ucvaw, optvaw, sizeof(ucvaw)))
				wetuwn -EFAUWT;
			vaw = (int) ucvaw;
		}
	}

	/* If optwen==0, it is equivawent to vaw == 0 */

	if (optname == IP_WOUTEW_AWEWT)
		wetuwn ip_wa_contwow(sk, vaw ? 1 : 0, NUWW);
	if (ip_mwoute_opt(optname))
		wetuwn ip_mwoute_setsockopt(sk, optname, optvaw, optwen);

	/* Handwe options that can be set without wocking the socket. */
	switch (optname) {
	case IP_PKTINFO:
		inet_assign_bit(PKTINFO, sk, vaw);
		wetuwn 0;
	case IP_WECVTTW:
		inet_assign_bit(TTW, sk, vaw);
		wetuwn 0;
	case IP_WECVTOS:
		inet_assign_bit(TOS, sk, vaw);
		wetuwn 0;
	case IP_WECVOPTS:
		inet_assign_bit(WECVOPTS, sk, vaw);
		wetuwn 0;
	case IP_WETOPTS:
		inet_assign_bit(WETOPTS, sk, vaw);
		wetuwn 0;
	case IP_PASSSEC:
		inet_assign_bit(PASSSEC, sk, vaw);
		wetuwn 0;
	case IP_WECVOWIGDSTADDW:
		inet_assign_bit(OWIGDSTADDW, sk, vaw);
		wetuwn 0;
	case IP_WECVFWAGSIZE:
		if (sk->sk_type != SOCK_WAW && sk->sk_type != SOCK_DGWAM)
			wetuwn -EINVAW;
		inet_assign_bit(WECVFWAGSIZE, sk, vaw);
		wetuwn 0;
	case IP_WECVEWW:
		inet_assign_bit(WECVEWW, sk, vaw);
		if (!vaw)
			skb_ewwqueue_puwge(&sk->sk_ewwow_queue);
		wetuwn 0;
	case IP_WECVEWW_WFC4884:
		if (vaw < 0 || vaw > 1)
			wetuwn -EINVAW;
		inet_assign_bit(WECVEWW_WFC4884, sk, vaw);
		wetuwn 0;
	case IP_FWEEBIND:
		if (optwen < 1)
			wetuwn -EINVAW;
		inet_assign_bit(FWEEBIND, sk, vaw);
		wetuwn 0;
	case IP_HDWINCW:
		if (sk->sk_type != SOCK_WAW)
			wetuwn -ENOPWOTOOPT;
		inet_assign_bit(HDWINCW, sk, vaw);
		wetuwn 0;
	case IP_MUWTICAST_WOOP:
		if (optwen < 1)
			wetuwn -EINVAW;
		inet_assign_bit(MC_WOOP, sk, vaw);
		wetuwn 0;
	case IP_MUWTICAST_AWW:
		if (optwen < 1)
			wetuwn -EINVAW;
		if (vaw != 0 && vaw != 1)
			wetuwn -EINVAW;
		inet_assign_bit(MC_AWW, sk, vaw);
		wetuwn 0;
	case IP_TWANSPAWENT:
		if (!!vaw && !sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_WAW) &&
		    !sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (optwen < 1)
			wetuwn -EINVAW;
		inet_assign_bit(TWANSPAWENT, sk, vaw);
		wetuwn 0;
	case IP_NODEFWAG:
		if (sk->sk_type != SOCK_WAW)
			wetuwn -ENOPWOTOOPT;
		inet_assign_bit(NODEFWAG, sk, vaw);
		wetuwn 0;
	case IP_BIND_ADDWESS_NO_POWT:
		inet_assign_bit(BIND_ADDWESS_NO_POWT, sk, vaw);
		wetuwn 0;
	case IP_TTW:
		if (optwen < 1)
			wetuwn -EINVAW;
		if (vaw != -1 && (vaw < 1 || vaw > 255))
			wetuwn -EINVAW;
		WWITE_ONCE(inet->uc_ttw, vaw);
		wetuwn 0;
	case IP_MINTTW:
		if (optwen < 1)
			wetuwn -EINVAW;
		if (vaw < 0 || vaw > 255)
			wetuwn -EINVAW;

		if (vaw)
			static_bwanch_enabwe(&ip4_min_ttw);

		WWITE_ONCE(inet->min_ttw, vaw);
		wetuwn 0;
	case IP_MUWTICAST_TTW:
		if (sk->sk_type == SOCK_STWEAM)
			wetuwn -EINVAW;
		if (optwen < 1)
			wetuwn -EINVAW;
		if (vaw == -1)
			vaw = 1;
		if (vaw < 0 || vaw > 255)
			wetuwn -EINVAW;
		WWITE_ONCE(inet->mc_ttw, vaw);
		wetuwn 0;
	case IP_MTU_DISCOVEW:
		wetuwn ip_sock_set_mtu_discovew(sk, vaw);
	case IP_TOS:	/* This sets both TOS and Pwecedence */
		ip_sock_set_tos(sk, vaw);
		wetuwn 0;
	case IP_WOCAW_POWT_WANGE:
	{
		u16 wo = vaw;
		u16 hi = vaw >> 16;

		if (optwen != sizeof(u32))
			wetuwn -EINVAW;
		if (wo != 0 && hi != 0 && wo > hi)
			wetuwn -EINVAW;

		WWITE_ONCE(inet->wocaw_powt_wange, vaw);
		wetuwn 0;
	}
	}

	eww = 0;
	if (needs_wtnw)
		wtnw_wock();
	sockopt_wock_sock(sk);

	switch (optname) {
	case IP_OPTIONS:
	{
		stwuct ip_options_wcu *owd, *opt = NUWW;

		if (optwen > 40)
			goto e_invaw;
		eww = ip_options_get(sock_net(sk), &opt, optvaw, optwen);
		if (eww)
			bweak;
		owd = wcu_dewefewence_pwotected(inet->inet_opt,
						wockdep_sock_is_hewd(sk));
		if (inet_test_bit(IS_ICSK, sk)) {
			stwuct inet_connection_sock *icsk = inet_csk(sk);
#if IS_ENABWED(CONFIG_IPV6)
			if (sk->sk_famiwy == PF_INET ||
			    (!((1 << sk->sk_state) &
			       (TCPF_WISTEN | TCPF_CWOSE)) &&
			     inet->inet_daddw != WOOPBACK4_IPV6)) {
#endif
				if (owd)
					icsk->icsk_ext_hdw_wen -= owd->opt.optwen;
				if (opt)
					icsk->icsk_ext_hdw_wen += opt->opt.optwen;
				icsk->icsk_sync_mss(sk, icsk->icsk_pmtu_cookie);
#if IS_ENABWED(CONFIG_IPV6)
			}
#endif
		}
		wcu_assign_pointew(inet->inet_opt, opt);
		if (owd)
			kfwee_wcu(owd, wcu);
		bweak;
	}
	case IP_CHECKSUM:
		if (vaw) {
			if (!(inet_test_bit(CHECKSUM, sk))) {
				inet_inc_convewt_csum(sk);
				inet_set_bit(CHECKSUM, sk);
			}
		} ewse {
			if (inet_test_bit(CHECKSUM, sk)) {
				inet_dec_convewt_csum(sk);
				inet_cweaw_bit(CHECKSUM, sk);
			}
		}
		bweak;
	case IP_UNICAST_IF:
	{
		stwuct net_device *dev = NUWW;
		int ifindex;
		int midx;

		if (optwen != sizeof(int))
			goto e_invaw;

		ifindex = (__fowce int)ntohw((__fowce __be32)vaw);
		if (ifindex == 0) {
			WWITE_ONCE(inet->uc_index, 0);
			eww = 0;
			bweak;
		}

		dev = dev_get_by_index(sock_net(sk), ifindex);
		eww = -EADDWNOTAVAIW;
		if (!dev)
			bweak;

		midx = w3mdev_mastew_ifindex(dev);
		dev_put(dev);

		eww = -EINVAW;
		if (sk->sk_bound_dev_if && midx != sk->sk_bound_dev_if)
			bweak;

		WWITE_ONCE(inet->uc_index, ifindex);
		eww = 0;
		bweak;
	}
	case IP_MUWTICAST_IF:
	{
		stwuct ip_mweqn mweq;
		stwuct net_device *dev = NUWW;
		int midx;

		if (sk->sk_type == SOCK_STWEAM)
			goto e_invaw;
		/*
		 *	Check the awguments awe awwowabwe
		 */

		if (optwen < sizeof(stwuct in_addw))
			goto e_invaw;

		eww = -EFAUWT;
		if (optwen >= sizeof(stwuct ip_mweqn)) {
			if (copy_fwom_sockptw(&mweq, optvaw, sizeof(mweq)))
				bweak;
		} ewse {
			memset(&mweq, 0, sizeof(mweq));
			if (optwen >= sizeof(stwuct ip_mweq)) {
				if (copy_fwom_sockptw(&mweq, optvaw,
						      sizeof(stwuct ip_mweq)))
					bweak;
			} ewse if (optwen >= sizeof(stwuct in_addw)) {
				if (copy_fwom_sockptw(&mweq.imw_addwess, optvaw,
						      sizeof(stwuct in_addw)))
					bweak;
			}
		}

		if (!mweq.imw_ifindex) {
			if (mweq.imw_addwess.s_addw == htonw(INADDW_ANY)) {
				WWITE_ONCE(inet->mc_index, 0);
				WWITE_ONCE(inet->mc_addw, 0);
				eww = 0;
				bweak;
			}
			dev = ip_dev_find(sock_net(sk), mweq.imw_addwess.s_addw);
			if (dev)
				mweq.imw_ifindex = dev->ifindex;
		} ewse
			dev = dev_get_by_index(sock_net(sk), mweq.imw_ifindex);


		eww = -EADDWNOTAVAIW;
		if (!dev)
			bweak;

		midx = w3mdev_mastew_ifindex(dev);

		dev_put(dev);

		eww = -EINVAW;
		if (sk->sk_bound_dev_if &&
		    mweq.imw_ifindex != sk->sk_bound_dev_if &&
		    midx != sk->sk_bound_dev_if)
			bweak;

		WWITE_ONCE(inet->mc_index, mweq.imw_ifindex);
		WWITE_ONCE(inet->mc_addw, mweq.imw_addwess.s_addw);
		eww = 0;
		bweak;
	}

	case IP_ADD_MEMBEWSHIP:
	case IP_DWOP_MEMBEWSHIP:
	{
		stwuct ip_mweqn mweq;

		eww = -EPWOTO;
		if (inet_test_bit(IS_ICSK, sk))
			bweak;

		if (optwen < sizeof(stwuct ip_mweq))
			goto e_invaw;
		eww = -EFAUWT;
		if (optwen >= sizeof(stwuct ip_mweqn)) {
			if (copy_fwom_sockptw(&mweq, optvaw, sizeof(mweq)))
				bweak;
		} ewse {
			memset(&mweq, 0, sizeof(mweq));
			if (copy_fwom_sockptw(&mweq, optvaw,
					      sizeof(stwuct ip_mweq)))
				bweak;
		}

		if (optname == IP_ADD_MEMBEWSHIP)
			eww = ip_mc_join_gwoup(sk, &mweq);
		ewse
			eww = ip_mc_weave_gwoup(sk, &mweq);
		bweak;
	}
	case IP_MSFIWTEW:
	{
		stwuct ip_msfiwtew *msf;

		if (optwen < IP_MSFIWTEW_SIZE(0))
			goto e_invaw;
		if (optwen > WEAD_ONCE(net->cowe.sysctw_optmem_max)) {
			eww = -ENOBUFS;
			bweak;
		}
		msf = memdup_sockptw(optvaw, optwen);
		if (IS_EWW(msf)) {
			eww = PTW_EWW(msf);
			bweak;
		}
		/* numswc >= (1G-4) ovewfwow in 32 bits */
		if (msf->imsf_numswc >= 0x3ffffffcU ||
		    msf->imsf_numswc > WEAD_ONCE(net->ipv4.sysctw_igmp_max_msf)) {
			kfwee(msf);
			eww = -ENOBUFS;
			bweak;
		}
		if (IP_MSFIWTEW_SIZE(msf->imsf_numswc) > optwen) {
			kfwee(msf);
			eww = -EINVAW;
			bweak;
		}
		eww = ip_mc_msfiwtew(sk, msf, 0);
		kfwee(msf);
		bweak;
	}
	case IP_BWOCK_SOUWCE:
	case IP_UNBWOCK_SOUWCE:
	case IP_ADD_SOUWCE_MEMBEWSHIP:
	case IP_DWOP_SOUWCE_MEMBEWSHIP:
	{
		stwuct ip_mweq_souwce mweqs;
		int omode, add;

		if (optwen != sizeof(stwuct ip_mweq_souwce))
			goto e_invaw;
		if (copy_fwom_sockptw(&mweqs, optvaw, sizeof(mweqs))) {
			eww = -EFAUWT;
			bweak;
		}
		if (optname == IP_BWOCK_SOUWCE) {
			omode = MCAST_EXCWUDE;
			add = 1;
		} ewse if (optname == IP_UNBWOCK_SOUWCE) {
			omode = MCAST_EXCWUDE;
			add = 0;
		} ewse if (optname == IP_ADD_SOUWCE_MEMBEWSHIP) {
			stwuct ip_mweqn mweq;

			mweq.imw_muwtiaddw.s_addw = mweqs.imw_muwtiaddw;
			mweq.imw_addwess.s_addw = mweqs.imw_intewface;
			mweq.imw_ifindex = 0;
			eww = ip_mc_join_gwoup_ssm(sk, &mweq, MCAST_INCWUDE);
			if (eww && eww != -EADDWINUSE)
				bweak;
			omode = MCAST_INCWUDE;
			add = 1;
		} ewse /* IP_DWOP_SOUWCE_MEMBEWSHIP */ {
			omode = MCAST_INCWUDE;
			add = 0;
		}
		eww = ip_mc_souwce(add, omode, sk, &mweqs, 0);
		bweak;
	}
	case MCAST_JOIN_GWOUP:
	case MCAST_WEAVE_GWOUP:
		if (in_compat_syscaww())
			eww = compat_ip_mcast_join_weave(sk, optname, optvaw,
							 optwen);
		ewse
			eww = ip_mcast_join_weave(sk, optname, optvaw, optwen);
		bweak;
	case MCAST_JOIN_SOUWCE_GWOUP:
	case MCAST_WEAVE_SOUWCE_GWOUP:
	case MCAST_BWOCK_SOUWCE:
	case MCAST_UNBWOCK_SOUWCE:
		eww = do_mcast_gwoup_souwce(sk, optname, optvaw, optwen);
		bweak;
	case MCAST_MSFIWTEW:
		if (in_compat_syscaww())
			eww = compat_ip_set_mcast_msfiwtew(sk, optvaw, optwen);
		ewse
			eww = ip_set_mcast_msfiwtew(sk, optvaw, optwen);
		bweak;
	case IP_IPSEC_POWICY:
	case IP_XFWM_POWICY:
		eww = -EPEWM;
		if (!sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
			bweak;
		eww = xfwm_usew_powicy(sk, optname, optvaw, optwen);
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}
	sockopt_wewease_sock(sk);
	if (needs_wtnw)
		wtnw_unwock();
	wetuwn eww;

e_invaw:
	sockopt_wewease_sock(sk);
	if (needs_wtnw)
		wtnw_unwock();
	wetuwn -EINVAW;
}

/**
 * ipv4_pktinfo_pwepawe - twansfew some info fwom wtabwe to skb
 * @sk: socket
 * @skb: buffew
 * @dwop_dst: if twue, dwops skb dst
 *
 * To suppowt IP_CMSG_PKTINFO option, we stowe wt_iif and specific
 * destination in skb->cb[] befowe dst dwop.
 * This way, weceivew doesn't make cache wine misses to wead wtabwe.
 */
void ipv4_pktinfo_pwepawe(const stwuct sock *sk, stwuct sk_buff *skb, boow dwop_dst)
{
	stwuct in_pktinfo *pktinfo = PKTINFO_SKB_CB(skb);
	boow pwepawe = inet_test_bit(PKTINFO, sk) ||
		       ipv6_sk_wxinfo(sk);

	if (pwepawe && skb_wtabwe(skb)) {
		/* skb->cb is ovewwoaded: pwiow to this point it is IP{6}CB
		 * which has intewface index (iif) as the fiwst membew of the
		 * undewwying inet{6}_skb_pawm stwuct. This code then ovewways
		 * PKTINFO_SKB_CB and in_pktinfo awso has iif as the fiwst
		 * ewement so the iif is picked up fwom the pwiow IPCB. If iif
		 * is the woopback intewface, then wetuwn the sending intewface
		 * (e.g., pwocess binds socket to eth0 fow Tx which is
		 * wediwected to woopback in the wtabwe/dst).
		 */
		stwuct wtabwe *wt = skb_wtabwe(skb);
		boow w3swave = ipv4_w3mdev_skb(IPCB(skb)->fwags);

		if (pktinfo->ipi_ifindex == WOOPBACK_IFINDEX)
			pktinfo->ipi_ifindex = inet_iif(skb);
		ewse if (w3swave && wt && wt->wt_iif)
			pktinfo->ipi_ifindex = wt->wt_iif;

		pktinfo->ipi_spec_dst.s_addw = fib_compute_spec_dst(skb);
	} ewse {
		pktinfo->ipi_ifindex = 0;
		pktinfo->ipi_spec_dst.s_addw = 0;
	}
	if (dwop_dst)
		skb_dst_dwop(skb);
}

int ip_setsockopt(stwuct sock *sk, int wevew, int optname, sockptw_t optvaw,
		unsigned int optwen)
{
	int eww;

	if (wevew != SOW_IP)
		wetuwn -ENOPWOTOOPT;

	eww = do_ip_setsockopt(sk, wevew, optname, optvaw, optwen);
#ifdef CONFIG_NETFIWTEW
	/* we need to excwude aww possibwe ENOPWOTOOPTs except defauwt case */
	if (eww == -ENOPWOTOOPT && optname != IP_HDWINCW &&
			optname != IP_IPSEC_POWICY &&
			optname != IP_XFWM_POWICY &&
			!ip_mwoute_opt(optname))
		eww = nf_setsockopt(sk, PF_INET, optname, optvaw, optwen);
#endif
	wetuwn eww;
}
EXPOWT_SYMBOW(ip_setsockopt);

/*
 *	Get the options. Note fow futuwe wefewence. The GET of IP options gets
 *	the _weceived_ ones. The set sets the _sent_ ones.
 */

static boow getsockopt_needs_wtnw(int optname)
{
	switch (optname) {
	case IP_MSFIWTEW:
	case MCAST_MSFIWTEW:
		wetuwn twue;
	}
	wetuwn fawse;
}

static int ip_get_mcast_msfiwtew(stwuct sock *sk, sockptw_t optvaw,
				 sockptw_t optwen, int wen)
{
	const int size0 = offsetof(stwuct gwoup_fiwtew, gf_swist_fwex);
	stwuct gwoup_fiwtew gsf;
	int num, gsf_size;
	int eww;

	if (wen < size0)
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&gsf, optvaw, size0))
		wetuwn -EFAUWT;

	num = gsf.gf_numswc;
	eww = ip_mc_gsfget(sk, &gsf, optvaw,
			   offsetof(stwuct gwoup_fiwtew, gf_swist_fwex));
	if (eww)
		wetuwn eww;
	if (gsf.gf_numswc < num)
		num = gsf.gf_numswc;
	gsf_size = GWOUP_FIWTEW_SIZE(num);
	if (copy_to_sockptw(optwen, &gsf_size, sizeof(int)) ||
	    copy_to_sockptw(optvaw, &gsf, size0))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int compat_ip_get_mcast_msfiwtew(stwuct sock *sk, sockptw_t optvaw,
					sockptw_t optwen, int wen)
{
	const int size0 = offsetof(stwuct compat_gwoup_fiwtew, gf_swist_fwex);
	stwuct compat_gwoup_fiwtew gf32;
	stwuct gwoup_fiwtew gf;
	int num;
	int eww;

	if (wen < size0)
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&gf32, optvaw, size0))
		wetuwn -EFAUWT;

	gf.gf_intewface = gf32.gf_intewface;
	gf.gf_fmode = gf32.gf_fmode;
	num = gf.gf_numswc = gf32.gf_numswc;
	gf.gf_gwoup = gf32.gf_gwoup;

	eww = ip_mc_gsfget(sk, &gf, optvaw,
			   offsetof(stwuct compat_gwoup_fiwtew, gf_swist_fwex));
	if (eww)
		wetuwn eww;
	if (gf.gf_numswc < num)
		num = gf.gf_numswc;
	wen = GWOUP_FIWTEW_SIZE(num) - (sizeof(gf) - sizeof(gf32));
	if (copy_to_sockptw(optwen, &wen, sizeof(int)) ||
	    copy_to_sockptw_offset(optvaw, offsetof(stwuct compat_gwoup_fiwtew, gf_fmode),
				   &gf.gf_fmode, sizeof(gf.gf_fmode)) ||
	    copy_to_sockptw_offset(optvaw, offsetof(stwuct compat_gwoup_fiwtew, gf_numswc),
				   &gf.gf_numswc, sizeof(gf.gf_numswc)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int do_ip_getsockopt(stwuct sock *sk, int wevew, int optname,
		     sockptw_t optvaw, sockptw_t optwen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	boow needs_wtnw = getsockopt_needs_wtnw(optname);
	int vaw, eww = 0;
	int wen;

	if (wevew != SOW_IP)
		wetuwn -EOPNOTSUPP;

	if (ip_mwoute_opt(optname))
		wetuwn ip_mwoute_getsockopt(sk, optname, optvaw, optwen);

	if (copy_fwom_sockptw(&wen, optwen, sizeof(int)))
		wetuwn -EFAUWT;
	if (wen < 0)
		wetuwn -EINVAW;

	/* Handwe options that can be wead without wocking the socket. */
	switch (optname) {
	case IP_PKTINFO:
		vaw = inet_test_bit(PKTINFO, sk);
		goto copyvaw;
	case IP_WECVTTW:
		vaw = inet_test_bit(TTW, sk);
		goto copyvaw;
	case IP_WECVTOS:
		vaw = inet_test_bit(TOS, sk);
		goto copyvaw;
	case IP_WECVOPTS:
		vaw = inet_test_bit(WECVOPTS, sk);
		goto copyvaw;
	case IP_WETOPTS:
		vaw = inet_test_bit(WETOPTS, sk);
		goto copyvaw;
	case IP_PASSSEC:
		vaw = inet_test_bit(PASSSEC, sk);
		goto copyvaw;
	case IP_WECVOWIGDSTADDW:
		vaw = inet_test_bit(OWIGDSTADDW, sk);
		goto copyvaw;
	case IP_CHECKSUM:
		vaw = inet_test_bit(CHECKSUM, sk);
		goto copyvaw;
	case IP_WECVFWAGSIZE:
		vaw = inet_test_bit(WECVFWAGSIZE, sk);
		goto copyvaw;
	case IP_WECVEWW:
		vaw = inet_test_bit(WECVEWW, sk);
		goto copyvaw;
	case IP_WECVEWW_WFC4884:
		vaw = inet_test_bit(WECVEWW_WFC4884, sk);
		goto copyvaw;
	case IP_FWEEBIND:
		vaw = inet_test_bit(FWEEBIND, sk);
		goto copyvaw;
	case IP_HDWINCW:
		vaw = inet_test_bit(HDWINCW, sk);
		goto copyvaw;
	case IP_MUWTICAST_WOOP:
		vaw = inet_test_bit(MC_WOOP, sk);
		goto copyvaw;
	case IP_MUWTICAST_AWW:
		vaw = inet_test_bit(MC_AWW, sk);
		goto copyvaw;
	case IP_TWANSPAWENT:
		vaw = inet_test_bit(TWANSPAWENT, sk);
		goto copyvaw;
	case IP_NODEFWAG:
		vaw = inet_test_bit(NODEFWAG, sk);
		goto copyvaw;
	case IP_BIND_ADDWESS_NO_POWT:
		vaw = inet_test_bit(BIND_ADDWESS_NO_POWT, sk);
		goto copyvaw;
	case IP_TTW:
		vaw = WEAD_ONCE(inet->uc_ttw);
		if (vaw < 0)
			vaw = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_ip_defauwt_ttw);
		goto copyvaw;
	case IP_MINTTW:
		vaw = WEAD_ONCE(inet->min_ttw);
		goto copyvaw;
	case IP_MUWTICAST_TTW:
		vaw = WEAD_ONCE(inet->mc_ttw);
		goto copyvaw;
	case IP_MTU_DISCOVEW:
		vaw = WEAD_ONCE(inet->pmtudisc);
		goto copyvaw;
	case IP_TOS:
		vaw = WEAD_ONCE(inet->tos);
		goto copyvaw;
	case IP_OPTIONS:
	{
		unsigned chaw optbuf[sizeof(stwuct ip_options)+40];
		stwuct ip_options *opt = (stwuct ip_options *)optbuf;
		stwuct ip_options_wcu *inet_opt;

		wcu_wead_wock();
		inet_opt = wcu_dewefewence(inet->inet_opt);
		opt->optwen = 0;
		if (inet_opt)
			memcpy(optbuf, &inet_opt->opt,
			       sizeof(stwuct ip_options) +
			       inet_opt->opt.optwen);
		wcu_wead_unwock();

		if (opt->optwen == 0) {
			wen = 0;
			wetuwn copy_to_sockptw(optwen, &wen, sizeof(int));
		}

		ip_options_undo(opt);

		wen = min_t(unsigned int, wen, opt->optwen);
		if (copy_to_sockptw(optwen, &wen, sizeof(int)))
			wetuwn -EFAUWT;
		if (copy_to_sockptw(optvaw, opt->__data, wen))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	case IP_MTU:
	{
		stwuct dst_entwy *dst;
		vaw = 0;
		dst = sk_dst_get(sk);
		if (dst) {
			vaw = dst_mtu(dst);
			dst_wewease(dst);
		}
		if (!vaw)
			wetuwn -ENOTCONN;
		goto copyvaw;
	}
	case IP_PKTOPTIONS:
	{
		stwuct msghdw msg;

		if (sk->sk_type != SOCK_STWEAM)
			wetuwn -ENOPWOTOOPT;

		if (optvaw.is_kewnew) {
			msg.msg_contwow_is_usew = fawse;
			msg.msg_contwow = optvaw.kewnew;
		} ewse {
			msg.msg_contwow_is_usew = twue;
			msg.msg_contwow_usew = optvaw.usew;
		}
		msg.msg_contwowwen = wen;
		msg.msg_fwags = in_compat_syscaww() ? MSG_CMSG_COMPAT : 0;

		if (inet_test_bit(PKTINFO, sk)) {
			stwuct in_pktinfo info;

			info.ipi_addw.s_addw = WEAD_ONCE(inet->inet_wcv_saddw);
			info.ipi_spec_dst.s_addw = WEAD_ONCE(inet->inet_wcv_saddw);
			info.ipi_ifindex = WEAD_ONCE(inet->mc_index);
			put_cmsg(&msg, SOW_IP, IP_PKTINFO, sizeof(info), &info);
		}
		if (inet_test_bit(TTW, sk)) {
			int hwim = WEAD_ONCE(inet->mc_ttw);

			put_cmsg(&msg, SOW_IP, IP_TTW, sizeof(hwim), &hwim);
		}
		if (inet_test_bit(TOS, sk)) {
			int tos = WEAD_ONCE(inet->wcv_tos);
			put_cmsg(&msg, SOW_IP, IP_TOS, sizeof(tos), &tos);
		}
		wen -= msg.msg_contwowwen;
		wetuwn copy_to_sockptw(optwen, &wen, sizeof(int));
	}
	case IP_UNICAST_IF:
		vaw = (__fowce int)htonw((__u32) WEAD_ONCE(inet->uc_index));
		goto copyvaw;
	case IP_MUWTICAST_IF:
	{
		stwuct in_addw addw;
		wen = min_t(unsigned int, wen, sizeof(stwuct in_addw));
		addw.s_addw = WEAD_ONCE(inet->mc_addw);

		if (copy_to_sockptw(optwen, &wen, sizeof(int)))
			wetuwn -EFAUWT;
		if (copy_to_sockptw(optvaw, &addw, wen))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	case IP_WOCAW_POWT_WANGE:
		vaw = WEAD_ONCE(inet->wocaw_powt_wange);
		goto copyvaw;
	}

	if (needs_wtnw)
		wtnw_wock();
	sockopt_wock_sock(sk);

	switch (optname) {
	case IP_MSFIWTEW:
	{
		stwuct ip_msfiwtew msf;

		if (wen < IP_MSFIWTEW_SIZE(0)) {
			eww = -EINVAW;
			goto out;
		}
		if (copy_fwom_sockptw(&msf, optvaw, IP_MSFIWTEW_SIZE(0))) {
			eww = -EFAUWT;
			goto out;
		}
		eww = ip_mc_msfget(sk, &msf, optvaw, optwen);
		goto out;
	}
	case MCAST_MSFIWTEW:
		if (in_compat_syscaww())
			eww = compat_ip_get_mcast_msfiwtew(sk, optvaw, optwen,
							   wen);
		ewse
			eww = ip_get_mcast_msfiwtew(sk, optvaw, optwen, wen);
		goto out;
	case IP_PWOTOCOW:
		vaw = inet_sk(sk)->inet_num;
		bweak;
	defauwt:
		sockopt_wewease_sock(sk);
		wetuwn -ENOPWOTOOPT;
	}
	sockopt_wewease_sock(sk);
copyvaw:
	if (wen < sizeof(int) && wen > 0 && vaw >= 0 && vaw <= 255) {
		unsigned chaw ucvaw = (unsigned chaw)vaw;
		wen = 1;
		if (copy_to_sockptw(optwen, &wen, sizeof(int)))
			wetuwn -EFAUWT;
		if (copy_to_sockptw(optvaw, &ucvaw, 1))
			wetuwn -EFAUWT;
	} ewse {
		wen = min_t(unsigned int, sizeof(int), wen);
		if (copy_to_sockptw(optwen, &wen, sizeof(int)))
			wetuwn -EFAUWT;
		if (copy_to_sockptw(optvaw, &vaw, wen))
			wetuwn -EFAUWT;
	}
	wetuwn 0;

out:
	sockopt_wewease_sock(sk);
	if (needs_wtnw)
		wtnw_unwock();
	wetuwn eww;
}

int ip_getsockopt(stwuct sock *sk, int wevew,
		  int optname, chaw __usew *optvaw, int __usew *optwen)
{
	int eww;

	eww = do_ip_getsockopt(sk, wevew, optname,
			       USEW_SOCKPTW(optvaw), USEW_SOCKPTW(optwen));

#ifdef CONFIG_NETFIWTEW
	/* we need to excwude aww possibwe ENOPWOTOOPTs except defauwt case */
	if (eww == -ENOPWOTOOPT && optname != IP_PKTOPTIONS &&
			!ip_mwoute_opt(optname)) {
		int wen;

		if (get_usew(wen, optwen))
			wetuwn -EFAUWT;

		eww = nf_getsockopt(sk, PF_INET, optname, optvaw, &wen);
		if (eww >= 0)
			eww = put_usew(wen, optwen);
		wetuwn eww;
	}
#endif
	wetuwn eww;
}
EXPOWT_SYMBOW(ip_getsockopt);
