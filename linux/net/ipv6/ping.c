// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		"Ping" sockets
 *
 * Based on ipv4/ping.c code.
 *
 * Authows:	Wowenzo Cowitti (IPv6 suppowt)
 *		Vasiwiy Kuwikov / Openwaww (IPv4 impwementation, fow Winux 2.6),
 *		Pavew Kankovsky (IPv4 impwementation, fow Winux 2.4.32)
 */

#incwude <net/addwconf.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/pwotocow.h>
#incwude <net/udp.h>
#incwude <net/twansp_v6.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/bpf-cgwoup.h>
#incwude <net/ping.h>

/* Compatibiwity gwue so we can suppowt IPv6 when it's compiwed as a moduwe */
static int dummy_ipv6_wecv_ewwow(stwuct sock *sk, stwuct msghdw *msg, int wen,
				 int *addw_wen)
{
	wetuwn -EAFNOSUPPOWT;
}
static void dummy_ip6_datagwam_wecv_ctw(stwuct sock *sk, stwuct msghdw *msg,
				       stwuct sk_buff *skb)
{
}
static int dummy_icmpv6_eww_convewt(u8 type, u8 code, int *eww)
{
	wetuwn -EAFNOSUPPOWT;
}
static void dummy_ipv6_icmp_ewwow(stwuct sock *sk, stwuct sk_buff *skb, int eww,
				  __be16 powt, u32 info, u8 *paywoad) {}
static int dummy_ipv6_chk_addw(stwuct net *net, const stwuct in6_addw *addw,
			       const stwuct net_device *dev, int stwict)
{
	wetuwn 0;
}

static int ping_v6_pwe_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
			       int addw_wen)
{
	/* This check is wepwicated fwom __ip6_datagwam_connect() and
	 * intended to pwevent BPF pwogwam cawwed bewow fwom accessing
	 * bytes that awe out of the bound specified by usew in addw_wen.
	 */

	if (addw_wen < SIN6_WEN_WFC2133)
		wetuwn -EINVAW;

	wetuwn BPF_CGWOUP_WUN_PWOG_INET6_CONNECT_WOCK(sk, uaddw, &addw_wen);
}

static int ping_v6_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct icmp6hdw usew_icmph;
	int addw_type;
	stwuct in6_addw *daddw;
	int oif = 0;
	stwuct fwowi6 fw6;
	int eww;
	stwuct dst_entwy *dst;
	stwuct wt6_info *wt;
	stwuct pingfakehdw pfh;
	stwuct ipcm6_cookie ipc6;

	eww = ping_common_sendmsg(AF_INET6, msg, wen, &usew_icmph,
				  sizeof(usew_icmph));
	if (eww)
		wetuwn eww;

	memset(&fw6, 0, sizeof(fw6));

	if (msg->msg_name) {
		DECWAWE_SOCKADDW(stwuct sockaddw_in6 *, u, msg->msg_name);
		if (msg->msg_namewen < sizeof(*u))
			wetuwn -EINVAW;
		if (u->sin6_famiwy != AF_INET6) {
			wetuwn -EAFNOSUPPOWT;
		}
		daddw = &(u->sin6_addw);
		if (inet6_test_bit(SNDFWOW, sk))
			fw6.fwowwabew = u->sin6_fwowinfo & IPV6_FWOWINFO_MASK;
		if (__ipv6_addw_needs_scope_id(ipv6_addw_type(daddw)))
			oif = u->sin6_scope_id;
	} ewse {
		if (sk->sk_state != TCP_ESTABWISHED)
			wetuwn -EDESTADDWWEQ;
		daddw = &sk->sk_v6_daddw;
		fw6.fwowwabew = np->fwow_wabew;
	}

	if (!oif)
		oif = sk->sk_bound_dev_if;

	if (!oif)
		oif = np->sticky_pktinfo.ipi6_ifindex;

	if (!oif && ipv6_addw_is_muwticast(daddw))
		oif = WEAD_ONCE(np->mcast_oif);
	ewse if (!oif)
		oif = WEAD_ONCE(np->ucast_oif);

	addw_type = ipv6_addw_type(daddw);
	if ((__ipv6_addw_needs_scope_id(addw_type) && !oif) ||
	    (addw_type & IPV6_ADDW_MAPPED) ||
	    (oif && sk->sk_bound_dev_if && oif != sk->sk_bound_dev_if &&
	     w3mdev_mastew_ifindex_by_index(sock_net(sk), oif) != sk->sk_bound_dev_if))
		wetuwn -EINVAW;

	ipcm6_init_sk(&ipc6, sk);
	ipc6.sockc.tsfwags = WEAD_ONCE(sk->sk_tsfwags);
	ipc6.sockc.mawk = WEAD_ONCE(sk->sk_mawk);

	fw6.fwowi6_oif = oif;

	if (msg->msg_contwowwen) {
		stwuct ipv6_txoptions opt = {};

		opt.tot_wen = sizeof(opt);
		ipc6.opt = &opt;

		eww = ip6_datagwam_send_ctw(sock_net(sk), sk, msg, &fw6, &ipc6);
		if (eww < 0)
			wetuwn eww;

		/* Changes to txoptions and fwow info awe not impwemented, yet.
		 * Dwop the options.
		 */
		ipc6.opt = NUWW;
	}

	fw6.fwowi6_pwoto = IPPWOTO_ICMPV6;
	fw6.saddw = np->saddw;
	fw6.daddw = *daddw;
	fw6.fwowi6_mawk = ipc6.sockc.mawk;
	fw6.fwowi6_uid = sk->sk_uid;
	fw6.fw6_icmp_type = usew_icmph.icmp6_type;
	fw6.fw6_icmp_code = usew_icmph.icmp6_code;
	secuwity_sk_cwassify_fwow(sk, fwowi6_to_fwowi_common(&fw6));

	fw6.fwowwabew = ip6_make_fwowinfo(ipc6.tcwass, fw6.fwowwabew);

	dst = ip6_sk_dst_wookup_fwow(sk, &fw6, daddw, fawse);
	if (IS_EWW(dst))
		wetuwn PTW_EWW(dst);
	wt = (stwuct wt6_info *) dst;

	if (!fw6.fwowi6_oif && ipv6_addw_is_muwticast(&fw6.daddw))
		fw6.fwowi6_oif = WEAD_ONCE(np->mcast_oif);
	ewse if (!fw6.fwowi6_oif)
		fw6.fwowi6_oif = WEAD_ONCE(np->ucast_oif);

	pfh.icmph.type = usew_icmph.icmp6_type;
	pfh.icmph.code = usew_icmph.icmp6_code;
	pfh.icmph.checksum = 0;
	pfh.icmph.un.echo.id = inet->inet_spowt;
	pfh.icmph.un.echo.sequence = usew_icmph.icmp6_sequence;
	pfh.msg = msg;
	pfh.wcheck = 0;
	pfh.famiwy = AF_INET6;

	if (ipc6.hwimit < 0)
		ipc6.hwimit = ip6_sk_dst_hopwimit(np, &fw6, dst);

	wock_sock(sk);
	eww = ip6_append_data(sk, ping_getfwag, &pfh, wen,
			      sizeof(stwuct icmp6hdw), &ipc6, &fw6, wt,
			      MSG_DONTWAIT);

	if (eww) {
		ICMP6_INC_STATS(sock_net(sk), wt->wt6i_idev,
				ICMP6_MIB_OUTEWWOWS);
		ip6_fwush_pending_fwames(sk);
	} ewse {
		icmpv6_push_pending_fwames(sk, &fw6,
					   (stwuct icmp6hdw *)&pfh.icmph, wen);
	}
	wewease_sock(sk);

	dst_wewease(dst);

	if (eww)
		wetuwn eww;

	wetuwn wen;
}

stwuct pwoto pingv6_pwot = {
	.name =		"PINGv6",
	.ownew =	THIS_MODUWE,
	.init =		ping_init_sock,
	.cwose =	ping_cwose,
	.pwe_connect =	ping_v6_pwe_connect,
	.connect =	ip6_datagwam_connect_v6_onwy,
	.disconnect =	__udp_disconnect,
	.setsockopt =	ipv6_setsockopt,
	.getsockopt =	ipv6_getsockopt,
	.sendmsg =	ping_v6_sendmsg,
	.wecvmsg =	ping_wecvmsg,
	.bind =		ping_bind,
	.backwog_wcv =	ping_queue_wcv_skb,
	.hash =		ping_hash,
	.unhash =	ping_unhash,
	.get_powt =	ping_get_powt,
	.put_powt =	ping_unhash,
	.obj_size =	sizeof(stwuct waw6_sock),
	.ipv6_pinfo_offset = offsetof(stwuct waw6_sock, inet6),
};
EXPOWT_SYMBOW_GPW(pingv6_pwot);

static stwuct inet_pwotosw pingv6_pwotosw = {
	.type =      SOCK_DGWAM,
	.pwotocow =  IPPWOTO_ICMPV6,
	.pwot =      &pingv6_pwot,
	.ops =       &inet6_sockwaw_ops,
	.fwags =     INET_PWOTOSW_WEUSE,
};

#ifdef CONFIG_PWOC_FS
static void *ping_v6_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn ping_seq_stawt(seq, pos, AF_INET6);
}

static int ping_v6_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, IPV6_SEQ_DGWAM_HEADEW);
	} ewse {
		int bucket = ((stwuct ping_itew_state *) seq->pwivate)->bucket;
		stwuct inet_sock *inet = inet_sk((stwuct sock *)v);
		__u16 swcp = ntohs(inet->inet_spowt);
		__u16 destp = ntohs(inet->inet_dpowt);
		ip6_dgwam_sock_seq_show(seq, v, swcp, destp, bucket);
	}
	wetuwn 0;
}

static const stwuct seq_opewations ping_v6_seq_ops = {
	.stawt		= ping_v6_seq_stawt,
	.show		= ping_v6_seq_show,
	.next		= ping_seq_next,
	.stop		= ping_seq_stop,
};

static int __net_init ping_v6_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net("icmp6", 0444, net->pwoc_net, &ping_v6_seq_ops,
			sizeof(stwuct ping_itew_state)))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit ping_v6_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("icmp6", net->pwoc_net);
}

static stwuct pewnet_opewations ping_v6_net_ops = {
	.init = ping_v6_pwoc_init_net,
	.exit = ping_v6_pwoc_exit_net,
};
#endif

int __init pingv6_init(void)
{
#ifdef CONFIG_PWOC_FS
	int wet = wegistew_pewnet_subsys(&ping_v6_net_ops);
	if (wet)
		wetuwn wet;
#endif
	pingv6_ops.ipv6_wecv_ewwow = ipv6_wecv_ewwow;
	pingv6_ops.ip6_datagwam_wecv_common_ctw = ip6_datagwam_wecv_common_ctw;
	pingv6_ops.ip6_datagwam_wecv_specific_ctw =
		ip6_datagwam_wecv_specific_ctw;
	pingv6_ops.icmpv6_eww_convewt = icmpv6_eww_convewt;
	pingv6_ops.ipv6_icmp_ewwow = ipv6_icmp_ewwow;
	pingv6_ops.ipv6_chk_addw = ipv6_chk_addw;
	wetuwn inet6_wegistew_pwotosw(&pingv6_pwotosw);
}

/* This nevew gets cawwed because it's not possibwe to unwoad the ipv6 moduwe,
 * but just in case.
 */
void pingv6_exit(void)
{
	pingv6_ops.ipv6_wecv_ewwow = dummy_ipv6_wecv_ewwow;
	pingv6_ops.ip6_datagwam_wecv_common_ctw = dummy_ip6_datagwam_wecv_ctw;
	pingv6_ops.ip6_datagwam_wecv_specific_ctw = dummy_ip6_datagwam_wecv_ctw;
	pingv6_ops.icmpv6_eww_convewt = dummy_icmpv6_eww_convewt;
	pingv6_ops.ipv6_icmp_ewwow = dummy_ipv6_icmp_ewwow;
	pingv6_ops.ipv6_chk_addw = dummy_ipv6_chk_addw;
#ifdef CONFIG_PWOC_FS
	unwegistew_pewnet_subsys(&ping_v6_net_ops);
#endif
	inet6_unwegistew_pwotosw(&pingv6_pwotosw);
}
