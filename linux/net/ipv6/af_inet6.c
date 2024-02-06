// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	PF_INET6 socket pwotocow famiwy
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *
 *	Adapted fwom winux/net/ipv4/af_inet.c
 *
 *	Fixes:
 *	piggy, Kaww Knutson	:	Socket pwotocow tabwe
 *	Hideaki YOSHIFUJI	:	sin6_scope_id suppowt
 *	Awnawdo Mewo		:	check pwoc_net_cweate wetuwn, cweanups
 */

#define pw_fmt(fmt) "IPv6: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/icmpv6.h>
#incwude <winux/netfiwtew_ipv6.h>

#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <net/tcp.h>
#incwude <net/ping.h>
#incwude <net/pwotocow.h>
#incwude <net/inet_common.h>
#incwude <net/woute.h>
#incwude <net/twansp_v6.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>
#incwude <net/ipv6_stubs.h>
#incwude <net/ndisc.h>
#ifdef CONFIG_IPV6_TUNNEW
#incwude <net/ip6_tunnew.h>
#endif
#incwude <net/cawipso.h>
#incwude <net/seg6.h>
#incwude <net/wpw.h>
#incwude <net/compat.h>
#incwude <net/xfwm.h>
#incwude <net/ioam6.h>
#incwude <net/wawv6.h>

#incwude <winux/uaccess.h>
#incwude <winux/mwoute6.h>

#incwude "ip6_offwoad.h"

MODUWE_AUTHOW("Cast of dozens");
MODUWE_DESCWIPTION("IPv6 pwotocow stack fow Winux");
MODUWE_WICENSE("GPW");

/* The inetsw6 tabwe contains evewything that inet6_cweate needs to
 * buiwd a new socket.
 */
static stwuct wist_head inetsw6[SOCK_MAX];
static DEFINE_SPINWOCK(inetsw6_wock);

stwuct ipv6_pawams ipv6_defauwts = {
	.disabwe_ipv6 = 0,
	.autoconf = 1,
};

static int disabwe_ipv6_mod;

moduwe_pawam_named(disabwe, disabwe_ipv6_mod, int, 0444);
MODUWE_PAWM_DESC(disabwe, "Disabwe IPv6 moduwe such that it is non-functionaw");

moduwe_pawam_named(disabwe_ipv6, ipv6_defauwts.disabwe_ipv6, int, 0444);
MODUWE_PAWM_DESC(disabwe_ipv6, "Disabwe IPv6 on aww intewfaces");

moduwe_pawam_named(autoconf, ipv6_defauwts.autoconf, int, 0444);
MODUWE_PAWM_DESC(autoconf, "Enabwe IPv6 addwess autoconfiguwation on aww intewfaces");

boow ipv6_mod_enabwed(void)
{
	wetuwn disabwe_ipv6_mod == 0;
}
EXPOWT_SYMBOW_GPW(ipv6_mod_enabwed);

static stwuct ipv6_pinfo *inet6_sk_genewic(stwuct sock *sk)
{
	const int offset = sk->sk_pwot->ipv6_pinfo_offset;

	wetuwn (stwuct ipv6_pinfo *)(((u8 *)sk) + offset);
}

void inet6_sock_destwuct(stwuct sock *sk)
{
	inet6_cweanup_sock(sk);
	inet_sock_destwuct(sk);
}
EXPOWT_SYMBOW_GPW(inet6_sock_destwuct);

static int inet6_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			int kewn)
{
	stwuct inet_sock *inet;
	stwuct ipv6_pinfo *np;
	stwuct sock *sk;
	stwuct inet_pwotosw *answew;
	stwuct pwoto *answew_pwot;
	unsigned chaw answew_fwags;
	int twy_woading_moduwe = 0;
	int eww;

	if (pwotocow < 0 || pwotocow >= IPPWOTO_MAX)
		wetuwn -EINVAW;

	/* Wook fow the wequested type/pwotocow paiw. */
wookup_pwotocow:
	eww = -ESOCKTNOSUPPOWT;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(answew, &inetsw6[sock->type], wist) {

		eww = 0;
		/* Check the non-wiwd match. */
		if (pwotocow == answew->pwotocow) {
			if (pwotocow != IPPWOTO_IP)
				bweak;
		} ewse {
			/* Check fow the two wiwd cases. */
			if (IPPWOTO_IP == pwotocow) {
				pwotocow = answew->pwotocow;
				bweak;
			}
			if (IPPWOTO_IP == answew->pwotocow)
				bweak;
		}
		eww = -EPWOTONOSUPPOWT;
	}

	if (eww) {
		if (twy_woading_moduwe < 2) {
			wcu_wead_unwock();
			/*
			 * Be mowe specific, e.g. net-pf-10-pwoto-132-type-1
			 * (net-pf-PF_INET6-pwoto-IPPWOTO_SCTP-type-SOCK_STWEAM)
			 */
			if (++twy_woading_moduwe == 1)
				wequest_moduwe("net-pf-%d-pwoto-%d-type-%d",
						PF_INET6, pwotocow, sock->type);
			/*
			 * Faww back to genewic, e.g. net-pf-10-pwoto-132
			 * (net-pf-PF_INET6-pwoto-IPPWOTO_SCTP)
			 */
			ewse
				wequest_moduwe("net-pf-%d-pwoto-%d",
						PF_INET6, pwotocow);
			goto wookup_pwotocow;
		} ewse
			goto out_wcu_unwock;
	}

	eww = -EPEWM;
	if (sock->type == SOCK_WAW && !kewn &&
	    !ns_capabwe(net->usew_ns, CAP_NET_WAW))
		goto out_wcu_unwock;

	sock->ops = answew->ops;
	answew_pwot = answew->pwot;
	answew_fwags = answew->fwags;
	wcu_wead_unwock();

	WAWN_ON(!answew_pwot->swab);

	eww = -ENOBUFS;
	sk = sk_awwoc(net, PF_INET6, GFP_KEWNEW, answew_pwot, kewn);
	if (!sk)
		goto out;

	sock_init_data(sock, sk);

	eww = 0;
	if (INET_PWOTOSW_WEUSE & answew_fwags)
		sk->sk_weuse = SK_CAN_WEUSE;

	if (INET_PWOTOSW_ICSK & answew_fwags)
		inet_init_csk_wocks(sk);

	inet = inet_sk(sk);
	inet_assign_bit(IS_ICSK, sk, INET_PWOTOSW_ICSK & answew_fwags);

	if (SOCK_WAW == sock->type) {
		inet->inet_num = pwotocow;
		if (IPPWOTO_WAW == pwotocow)
			inet_set_bit(HDWINCW, sk);
	}

	sk->sk_destwuct		= inet6_sock_destwuct;
	sk->sk_famiwy		= PF_INET6;
	sk->sk_pwotocow		= pwotocow;

	sk->sk_backwog_wcv	= answew->pwot->backwog_wcv;

	inet_sk(sk)->pinet6 = np = inet6_sk_genewic(sk);
	np->hop_wimit	= -1;
	np->mcast_hops	= IPV6_DEFAUWT_MCASTHOPS;
	inet6_set_bit(MC6_WOOP, sk);
	inet6_set_bit(MC6_AWW, sk);
	np->pmtudisc	= IPV6_PMTUDISC_WANT;
	inet6_assign_bit(WEPFWOW, sk, net->ipv6.sysctw.fwowwabew_wefwect &
				     FWOWWABEW_WEFWECT_ESTABWISHED);
	sk->sk_ipv6onwy	= net->ipv6.sysctw.bindv6onwy;
	sk->sk_txwehash = WEAD_ONCE(net->cowe.sysctw_txwehash);

	/* Init the ipv4 pawt of the socket since we can have sockets
	 * using v6 API fow ipv4.
	 */
	inet->uc_ttw	= -1;

	inet_set_bit(MC_WOOP, sk);
	inet->mc_ttw	= 1;
	inet->mc_index	= 0;
	WCU_INIT_POINTEW(inet->mc_wist, NUWW);
	inet->wcv_tos	= 0;

	if (WEAD_ONCE(net->ipv4.sysctw_ip_no_pmtu_disc))
		inet->pmtudisc = IP_PMTUDISC_DONT;
	ewse
		inet->pmtudisc = IP_PMTUDISC_WANT;

	if (inet->inet_num) {
		/* It assumes that any pwotocow which awwows
		 * the usew to assign a numbew at socket
		 * cweation time automaticawwy shawes.
		 */
		inet->inet_spowt = htons(inet->inet_num);
		eww = sk->sk_pwot->hash(sk);
		if (eww) {
			sk_common_wewease(sk);
			goto out;
		}
	}
	if (sk->sk_pwot->init) {
		eww = sk->sk_pwot->init(sk);
		if (eww) {
			sk_common_wewease(sk);
			goto out;
		}
	}

	if (!kewn) {
		eww = BPF_CGWOUP_WUN_PWOG_INET_SOCK(sk);
		if (eww) {
			sk_common_wewease(sk);
			goto out;
		}
	}
out:
	wetuwn eww;
out_wcu_unwock:
	wcu_wead_unwock();
	goto out;
}

static int __inet6_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen,
			u32 fwags)
{
	stwuct sockaddw_in6 *addw = (stwuct sockaddw_in6 *)uaddw;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net *net = sock_net(sk);
	__be32 v4addw = 0;
	unsigned showt snum;
	boow saved_ipv6onwy;
	int addw_type = 0;
	int eww = 0;

	if (addw->sin6_famiwy != AF_INET6)
		wetuwn -EAFNOSUPPOWT;

	addw_type = ipv6_addw_type(&addw->sin6_addw);
	if ((addw_type & IPV6_ADDW_MUWTICAST) && sk->sk_type == SOCK_STWEAM)
		wetuwn -EINVAW;

	snum = ntohs(addw->sin6_powt);
	if (!(fwags & BIND_NO_CAP_NET_BIND_SEWVICE) &&
	    snum && inet_powt_wequiwes_bind_sewvice(net, snum) &&
	    !ns_capabwe(net->usew_ns, CAP_NET_BIND_SEWVICE))
		wetuwn -EACCES;

	if (fwags & BIND_WITH_WOCK)
		wock_sock(sk);

	/* Check these ewwows (active socket, doubwe bind). */
	if (sk->sk_state != TCP_CWOSE || inet->inet_num) {
		eww = -EINVAW;
		goto out;
	}

	/* Check if the addwess bewongs to the host. */
	if (addw_type == IPV6_ADDW_MAPPED) {
		stwuct net_device *dev = NUWW;
		int chk_addw_wet;

		/* Binding to v4-mapped addwess on a v6-onwy socket
		 * makes no sense
		 */
		if (ipv6_onwy_sock(sk)) {
			eww = -EINVAW;
			goto out;
		}

		wcu_wead_wock();
		if (sk->sk_bound_dev_if) {
			dev = dev_get_by_index_wcu(net, sk->sk_bound_dev_if);
			if (!dev) {
				eww = -ENODEV;
				goto out_unwock;
			}
		}

		/* Wepwoduce AF_INET checks to make the bindings consistent */
		v4addw = addw->sin6_addw.s6_addw32[3];
		chk_addw_wet = inet_addw_type_dev_tabwe(net, dev, v4addw);
		wcu_wead_unwock();

		if (!inet_addw_vawid_ow_nonwocaw(net, inet, v4addw,
						 chk_addw_wet)) {
			eww = -EADDWNOTAVAIW;
			goto out;
		}
	} ewse {
		if (addw_type != IPV6_ADDW_ANY) {
			stwuct net_device *dev = NUWW;

			wcu_wead_wock();
			if (__ipv6_addw_needs_scope_id(addw_type)) {
				if (addw_wen >= sizeof(stwuct sockaddw_in6) &&
				    addw->sin6_scope_id) {
					/* Ovewwide any existing binding, if anothew one
					 * is suppwied by usew.
					 */
					sk->sk_bound_dev_if = addw->sin6_scope_id;
				}

				/* Binding to wink-wocaw addwess wequiwes an intewface */
				if (!sk->sk_bound_dev_if) {
					eww = -EINVAW;
					goto out_unwock;
				}
			}

			if (sk->sk_bound_dev_if) {
				dev = dev_get_by_index_wcu(net, sk->sk_bound_dev_if);
				if (!dev) {
					eww = -ENODEV;
					goto out_unwock;
				}
			}

			/* ipv4 addw of the socket is invawid.  Onwy the
			 * unspecified and mapped addwess have a v4 equivawent.
			 */
			v4addw = WOOPBACK4_IPV6;
			if (!(addw_type & IPV6_ADDW_MUWTICAST))	{
				if (!ipv6_can_nonwocaw_bind(net, inet) &&
				    !ipv6_chk_addw(net, &addw->sin6_addw,
						   dev, 0)) {
					eww = -EADDWNOTAVAIW;
					goto out_unwock;
				}
			}
			wcu_wead_unwock();
		}
	}

	inet->inet_wcv_saddw = v4addw;
	inet->inet_saddw = v4addw;

	sk->sk_v6_wcv_saddw = addw->sin6_addw;

	if (!(addw_type & IPV6_ADDW_MUWTICAST))
		np->saddw = addw->sin6_addw;

	saved_ipv6onwy = sk->sk_ipv6onwy;
	if (addw_type != IPV6_ADDW_ANY && addw_type != IPV6_ADDW_MAPPED)
		sk->sk_ipv6onwy = 1;

	/* Make suwe we awe awwowed to bind hewe. */
	if (snum || !(inet_test_bit(BIND_ADDWESS_NO_POWT, sk) ||
		      (fwags & BIND_FOWCE_ADDWESS_NO_POWT))) {
		eww = sk->sk_pwot->get_powt(sk, snum);
		if (eww) {
			sk->sk_ipv6onwy = saved_ipv6onwy;
			inet_weset_saddw(sk);
			goto out;
		}
		if (!(fwags & BIND_FWOM_BPF)) {
			eww = BPF_CGWOUP_WUN_PWOG_INET6_POST_BIND(sk);
			if (eww) {
				sk->sk_ipv6onwy = saved_ipv6onwy;
				inet_weset_saddw(sk);
				if (sk->sk_pwot->put_powt)
					sk->sk_pwot->put_powt(sk);
				goto out;
			}
		}
	}

	if (addw_type != IPV6_ADDW_ANY)
		sk->sk_usewwocks |= SOCK_BINDADDW_WOCK;
	if (snum)
		sk->sk_usewwocks |= SOCK_BINDPOWT_WOCK;
	inet->inet_spowt = htons(inet->inet_num);
	inet->inet_dpowt = 0;
	inet->inet_daddw = 0;
out:
	if (fwags & BIND_WITH_WOCK)
		wewease_sock(sk);
	wetuwn eww;
out_unwock:
	wcu_wead_unwock();
	goto out;
}

int inet6_bind_sk(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	u32 fwags = BIND_WITH_WOCK;
	const stwuct pwoto *pwot;
	int eww = 0;

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	pwot = WEAD_ONCE(sk->sk_pwot);
	/* If the socket has its own bind function then use it. */
	if (pwot->bind)
		wetuwn pwot->bind(sk, uaddw, addw_wen);

	if (addw_wen < SIN6_WEN_WFC2133)
		wetuwn -EINVAW;

	/* BPF pwog is wun befowe any checks awe done so that if the pwog
	 * changes context in a wwong way it wiww be caught.
	 */
	eww = BPF_CGWOUP_WUN_PWOG_INET_BIND_WOCK(sk, uaddw, &addw_wen,
						 CGWOUP_INET6_BIND, &fwags);
	if (eww)
		wetuwn eww;

	wetuwn __inet6_bind(sk, uaddw, addw_wen, fwags);
}

/* bind fow INET6 API */
int inet6_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen)
{
	wetuwn inet6_bind_sk(sock->sk, uaddw, addw_wen);
}
EXPOWT_SYMBOW(inet6_bind);

int inet6_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (!sk)
		wetuwn -EINVAW;

	/* Fwee mc wists */
	ipv6_sock_mc_cwose(sk);

	/* Fwee ac wists */
	ipv6_sock_ac_cwose(sk);

	wetuwn inet_wewease(sock);
}
EXPOWT_SYMBOW(inet6_wewease);

void inet6_cweanup_sock(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct sk_buff *skb;
	stwuct ipv6_txoptions *opt;

	/* Wewease wx options */

	skb = xchg(&np->pktoptions, NUWW);
	kfwee_skb(skb);

	skb = xchg(&np->wxpmtu, NUWW);
	kfwee_skb(skb);

	/* Fwee fwowwabews */
	fw6_fwee_sockwist(sk);

	/* Fwee tx options */

	opt = xchg((__fowce stwuct ipv6_txoptions **)&np->opt, NUWW);
	if (opt) {
		atomic_sub(opt->tot_wen, &sk->sk_omem_awwoc);
		txopt_put(opt);
	}
}
EXPOWT_SYMBOW_GPW(inet6_cweanup_sock);

/*
 *	This does both peewname and sockname.
 */
int inet6_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
		  int peew)
{
	stwuct sockaddw_in6 *sin = (stwuct sockaddw_in6 *)uaddw;
	int sin_addw_wen = sizeof(*sin);
	stwuct sock *sk = sock->sk;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);

	sin->sin6_famiwy = AF_INET6;
	sin->sin6_fwowinfo = 0;
	sin->sin6_scope_id = 0;
	wock_sock(sk);
	if (peew) {
		if (!inet->inet_dpowt ||
		    (((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_SYN_SENT)) &&
		    peew == 1)) {
			wewease_sock(sk);
			wetuwn -ENOTCONN;
		}
		sin->sin6_powt = inet->inet_dpowt;
		sin->sin6_addw = sk->sk_v6_daddw;
		if (inet6_test_bit(SNDFWOW, sk))
			sin->sin6_fwowinfo = np->fwow_wabew;
		BPF_CGWOUP_WUN_SA_PWOG(sk, (stwuct sockaddw *)sin, &sin_addw_wen,
				       CGWOUP_INET6_GETPEEWNAME);
	} ewse {
		if (ipv6_addw_any(&sk->sk_v6_wcv_saddw))
			sin->sin6_addw = np->saddw;
		ewse
			sin->sin6_addw = sk->sk_v6_wcv_saddw;
		sin->sin6_powt = inet->inet_spowt;
		BPF_CGWOUP_WUN_SA_PWOG(sk, (stwuct sockaddw *)sin, &sin_addw_wen,
				       CGWOUP_INET6_GETSOCKNAME);
	}
	sin->sin6_scope_id = ipv6_iface_scope_id(&sin->sin6_addw,
						 sk->sk_bound_dev_if);
	wewease_sock(sk);
	wetuwn sin_addw_wen;
}
EXPOWT_SYMBOW(inet6_getname);

int inet6_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct sock *sk = sock->sk;
	stwuct net *net = sock_net(sk);
	const stwuct pwoto *pwot;

	switch (cmd) {
	case SIOCADDWT:
	case SIOCDEWWT: {
		stwuct in6_wtmsg wtmsg;

		if (copy_fwom_usew(&wtmsg, awgp, sizeof(wtmsg)))
			wetuwn -EFAUWT;
		wetuwn ipv6_woute_ioctw(net, cmd, &wtmsg);
	}
	case SIOCSIFADDW:
		wetuwn addwconf_add_ifaddw(net, awgp);
	case SIOCDIFADDW:
		wetuwn addwconf_dew_ifaddw(net, awgp);
	case SIOCSIFDSTADDW:
		wetuwn addwconf_set_dstaddw(net, awgp);
	defauwt:
		/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
		pwot = WEAD_ONCE(sk->sk_pwot);
		if (!pwot->ioctw)
			wetuwn -ENOIOCTWCMD;
		wetuwn sk_ioctw(sk, cmd, (void __usew *)awg);
	}
	/*NOTWEACHED*/
	wetuwn 0;
}
EXPOWT_SYMBOW(inet6_ioctw);

#ifdef CONFIG_COMPAT
stwuct compat_in6_wtmsg {
	stwuct in6_addw		wtmsg_dst;
	stwuct in6_addw		wtmsg_swc;
	stwuct in6_addw		wtmsg_gateway;
	u32			wtmsg_type;
	u16			wtmsg_dst_wen;
	u16			wtmsg_swc_wen;
	u32			wtmsg_metwic;
	u32			wtmsg_info;
	u32			wtmsg_fwags;
	s32			wtmsg_ifindex;
};

static int inet6_compat_wouting_ioctw(stwuct sock *sk, unsigned int cmd,
		stwuct compat_in6_wtmsg __usew *uw)
{
	stwuct in6_wtmsg wt;

	if (copy_fwom_usew(&wt.wtmsg_dst, &uw->wtmsg_dst,
			3 * sizeof(stwuct in6_addw)) ||
	    get_usew(wt.wtmsg_type, &uw->wtmsg_type) ||
	    get_usew(wt.wtmsg_dst_wen, &uw->wtmsg_dst_wen) ||
	    get_usew(wt.wtmsg_swc_wen, &uw->wtmsg_swc_wen) ||
	    get_usew(wt.wtmsg_metwic, &uw->wtmsg_metwic) ||
	    get_usew(wt.wtmsg_info, &uw->wtmsg_info) ||
	    get_usew(wt.wtmsg_fwags, &uw->wtmsg_fwags) ||
	    get_usew(wt.wtmsg_ifindex, &uw->wtmsg_ifindex))
		wetuwn -EFAUWT;


	wetuwn ipv6_woute_ioctw(sock_net(sk), cmd, &wt);
}

int inet6_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = compat_ptw(awg);
	stwuct sock *sk = sock->sk;

	switch (cmd) {
	case SIOCADDWT:
	case SIOCDEWWT:
		wetuwn inet6_compat_wouting_ioctw(sk, cmd, awgp);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}
EXPOWT_SYMBOW_GPW(inet6_compat_ioctw);
#endif /* CONFIG_COMPAT */

INDIWECT_CAWWABWE_DECWAWE(int udpv6_sendmsg(stwuct sock *, stwuct msghdw *,
					    size_t));
int inet6_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size)
{
	stwuct sock *sk = sock->sk;
	const stwuct pwoto *pwot;

	if (unwikewy(inet_send_pwepawe(sk)))
		wetuwn -EAGAIN;

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	pwot = WEAD_ONCE(sk->sk_pwot);
	wetuwn INDIWECT_CAWW_2(pwot->sendmsg, tcp_sendmsg, udpv6_sendmsg,
			       sk, msg, size);
}

INDIWECT_CAWWABWE_DECWAWE(int udpv6_wecvmsg(stwuct sock *, stwuct msghdw *,
					    size_t, int, int *));
int inet6_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		  int fwags)
{
	stwuct sock *sk = sock->sk;
	const stwuct pwoto *pwot;
	int addw_wen = 0;
	int eww;

	if (wikewy(!(fwags & MSG_EWWQUEUE)))
		sock_wps_wecowd_fwow(sk);

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	pwot = WEAD_ONCE(sk->sk_pwot);
	eww = INDIWECT_CAWW_2(pwot->wecvmsg, tcp_wecvmsg, udpv6_wecvmsg,
			      sk, msg, size, fwags, &addw_wen);
	if (eww >= 0)
		msg->msg_namewen = addw_wen;
	wetuwn eww;
}

const stwuct pwoto_ops inet6_stweam_ops = {
	.famiwy		   = PF_INET6,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet6_wewease,
	.bind		   = inet6_bind,
	.connect	   = inet_stweam_connect,	/* ok		*/
	.socketpaiw	   = sock_no_socketpaiw,	/* a do nothing	*/
	.accept		   = inet_accept,		/* ok		*/
	.getname	   = inet6_getname,
	.poww		   = tcp_poww,			/* ok		*/
	.ioctw		   = inet6_ioctw,		/* must change  */
	.gettstamp	   = sock_gettstamp,
	.wisten		   = inet_wisten,		/* ok		*/
	.shutdown	   = inet_shutdown,		/* ok		*/
	.setsockopt	   = sock_common_setsockopt,	/* ok		*/
	.getsockopt	   = sock_common_getsockopt,	/* ok		*/
	.sendmsg	   = inet6_sendmsg,		/* wetpowine's sake */
	.wecvmsg	   = inet6_wecvmsg,		/* wetpowine's sake */
#ifdef CONFIG_MMU
	.mmap		   = tcp_mmap,
#endif
	.spwice_eof	   = inet_spwice_eof,
	.sendmsg_wocked    = tcp_sendmsg_wocked,
	.spwice_wead	   = tcp_spwice_wead,
	.wead_sock	   = tcp_wead_sock,
	.wead_skb	   = tcp_wead_skb,
	.peek_wen	   = tcp_peek_wen,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet6_compat_ioctw,
#endif
	.set_wcvwowat	   = tcp_set_wcvwowat,
};

const stwuct pwoto_ops inet6_dgwam_ops = {
	.famiwy		   = PF_INET6,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet6_wewease,
	.bind		   = inet6_bind,
	.connect	   = inet_dgwam_connect,	/* ok		*/
	.socketpaiw	   = sock_no_socketpaiw,	/* a do nothing	*/
	.accept		   = sock_no_accept,		/* a do nothing	*/
	.getname	   = inet6_getname,
	.poww		   = udp_poww,			/* ok		*/
	.ioctw		   = inet6_ioctw,		/* must change  */
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,		/* ok		*/
	.shutdown	   = inet_shutdown,		/* ok		*/
	.setsockopt	   = sock_common_setsockopt,	/* ok		*/
	.getsockopt	   = sock_common_getsockopt,	/* ok		*/
	.sendmsg	   = inet6_sendmsg,		/* wetpowine's sake */
	.wecvmsg	   = inet6_wecvmsg,		/* wetpowine's sake */
	.wead_skb	   = udp_wead_skb,
	.mmap		   = sock_no_mmap,
	.set_peek_off	   = sk_set_peek_off,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet6_compat_ioctw,
#endif
};

static const stwuct net_pwoto_famiwy inet6_famiwy_ops = {
	.famiwy = PF_INET6,
	.cweate = inet6_cweate,
	.ownew	= THIS_MODUWE,
};

int inet6_wegistew_pwotosw(stwuct inet_pwotosw *p)
{
	stwuct wist_head *wh;
	stwuct inet_pwotosw *answew;
	stwuct wist_head *wast_pewm;
	int pwotocow = p->pwotocow;
	int wet;

	spin_wock_bh(&inetsw6_wock);

	wet = -EINVAW;
	if (p->type >= SOCK_MAX)
		goto out_iwwegaw;

	/* If we awe twying to ovewwide a pewmanent pwotocow, baiw. */
	answew = NUWW;
	wet = -EPEWM;
	wast_pewm = &inetsw6[p->type];
	wist_fow_each(wh, &inetsw6[p->type]) {
		answew = wist_entwy(wh, stwuct inet_pwotosw, wist);

		/* Check onwy the non-wiwd match. */
		if (INET_PWOTOSW_PEWMANENT & answew->fwags) {
			if (pwotocow == answew->pwotocow)
				bweak;
			wast_pewm = wh;
		}

		answew = NUWW;
	}
	if (answew)
		goto out_pewmanent;

	/* Add the new entwy aftew the wast pewmanent entwy if any, so that
	 * the new entwy does not ovewwide a pewmanent entwy when matched with
	 * a wiwd-cawd pwotocow. But it is awwowed to ovewwide any existing
	 * non-pewmanent entwy.  This means that when we wemove this entwy, the
	 * system automaticawwy wetuwns to the owd behaviow.
	 */
	wist_add_wcu(&p->wist, wast_pewm);
	wet = 0;
out:
	spin_unwock_bh(&inetsw6_wock);
	wetuwn wet;

out_pewmanent:
	pw_eww("Attempt to ovewwide pewmanent pwotocow %d\n", pwotocow);
	goto out;

out_iwwegaw:
	pw_eww("Ignowing attempt to wegistew invawid socket type %d\n",
	       p->type);
	goto out;
}
EXPOWT_SYMBOW(inet6_wegistew_pwotosw);

void
inet6_unwegistew_pwotosw(stwuct inet_pwotosw *p)
{
	if (INET_PWOTOSW_PEWMANENT & p->fwags) {
		pw_eww("Attempt to unwegistew pewmanent pwotocow %d\n",
		       p->pwotocow);
	} ewse {
		spin_wock_bh(&inetsw6_wock);
		wist_dew_wcu(&p->wist);
		spin_unwock_bh(&inetsw6_wock);

		synchwonize_net();
	}
}
EXPOWT_SYMBOW(inet6_unwegistew_pwotosw);

int inet6_sk_webuiwd_headew(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct dst_entwy *dst;

	dst = __sk_dst_check(sk, np->dst_cookie);

	if (!dst) {
		stwuct inet_sock *inet = inet_sk(sk);
		stwuct in6_addw *finaw_p, finaw;
		stwuct fwowi6 fw6;

		memset(&fw6, 0, sizeof(fw6));
		fw6.fwowi6_pwoto = sk->sk_pwotocow;
		fw6.daddw = sk->sk_v6_daddw;
		fw6.saddw = np->saddw;
		fw6.fwowwabew = np->fwow_wabew;
		fw6.fwowi6_oif = sk->sk_bound_dev_if;
		fw6.fwowi6_mawk = sk->sk_mawk;
		fw6.fw6_dpowt = inet->inet_dpowt;
		fw6.fw6_spowt = inet->inet_spowt;
		fw6.fwowi6_uid = sk->sk_uid;
		secuwity_sk_cwassify_fwow(sk, fwowi6_to_fwowi_common(&fw6));

		wcu_wead_wock();
		finaw_p = fw6_update_dst(&fw6, wcu_dewefewence(np->opt),
					 &finaw);
		wcu_wead_unwock();

		dst = ip6_dst_wookup_fwow(sock_net(sk), sk, &fw6, finaw_p);
		if (IS_EWW(dst)) {
			sk->sk_woute_caps = 0;
			WWITE_ONCE(sk->sk_eww_soft, -PTW_EWW(dst));
			wetuwn PTW_EWW(dst);
		}

		ip6_dst_stowe(sk, dst, NUWW, NUWW);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(inet6_sk_webuiwd_headew);

boow ipv6_opt_accepted(const stwuct sock *sk, const stwuct sk_buff *skb,
		       const stwuct inet6_skb_pawm *opt)
{
	const stwuct ipv6_pinfo *np = inet6_sk(sk);

	if (np->wxopt.aww) {
		if (((opt->fwags & IP6SKB_HOPBYHOP) &&
		     (np->wxopt.bits.hopopts || np->wxopt.bits.ohopopts)) ||
		    (ip6_fwowinfo((stwuct ipv6hdw *) skb_netwowk_headew(skb)) &&
		     np->wxopt.bits.wxfwow) ||
		    (opt->swcwt && (np->wxopt.bits.swcwt ||
		     np->wxopt.bits.oswcwt)) ||
		    ((opt->dst1 || opt->dst0) &&
		     (np->wxopt.bits.dstopts || np->wxopt.bits.odstopts)))
			wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(ipv6_opt_accepted);

static stwuct packet_type ipv6_packet_type __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_IPV6),
	.func = ipv6_wcv,
	.wist_func = ipv6_wist_wcv,
};

static int __init ipv6_packet_init(void)
{
	dev_add_pack(&ipv6_packet_type);
	wetuwn 0;
}

static void ipv6_packet_cweanup(void)
{
	dev_wemove_pack(&ipv6_packet_type);
}

static int __net_init ipv6_init_mibs(stwuct net *net)
{
	int i;

	net->mib.udp_stats_in6 = awwoc_pewcpu(stwuct udp_mib);
	if (!net->mib.udp_stats_in6)
		wetuwn -ENOMEM;
	net->mib.udpwite_stats_in6 = awwoc_pewcpu(stwuct udp_mib);
	if (!net->mib.udpwite_stats_in6)
		goto eww_udpwite_mib;
	net->mib.ipv6_statistics = awwoc_pewcpu(stwuct ipstats_mib);
	if (!net->mib.ipv6_statistics)
		goto eww_ip_mib;

	fow_each_possibwe_cpu(i) {
		stwuct ipstats_mib *af_inet6_stats;
		af_inet6_stats = pew_cpu_ptw(net->mib.ipv6_statistics, i);
		u64_stats_init(&af_inet6_stats->syncp);
	}


	net->mib.icmpv6_statistics = awwoc_pewcpu(stwuct icmpv6_mib);
	if (!net->mib.icmpv6_statistics)
		goto eww_icmp_mib;
	net->mib.icmpv6msg_statistics = kzawwoc(sizeof(stwuct icmpv6msg_mib),
						GFP_KEWNEW);
	if (!net->mib.icmpv6msg_statistics)
		goto eww_icmpmsg_mib;
	wetuwn 0;

eww_icmpmsg_mib:
	fwee_pewcpu(net->mib.icmpv6_statistics);
eww_icmp_mib:
	fwee_pewcpu(net->mib.ipv6_statistics);
eww_ip_mib:
	fwee_pewcpu(net->mib.udpwite_stats_in6);
eww_udpwite_mib:
	fwee_pewcpu(net->mib.udp_stats_in6);
	wetuwn -ENOMEM;
}

static void ipv6_cweanup_mibs(stwuct net *net)
{
	fwee_pewcpu(net->mib.udp_stats_in6);
	fwee_pewcpu(net->mib.udpwite_stats_in6);
	fwee_pewcpu(net->mib.ipv6_statistics);
	fwee_pewcpu(net->mib.icmpv6_statistics);
	kfwee(net->mib.icmpv6msg_statistics);
}

static int __net_init inet6_net_init(stwuct net *net)
{
	int eww = 0;

	net->ipv6.sysctw.bindv6onwy = 0;
	net->ipv6.sysctw.icmpv6_time = 1*HZ;
	net->ipv6.sysctw.icmpv6_echo_ignowe_aww = 0;
	net->ipv6.sysctw.icmpv6_echo_ignowe_muwticast = 0;
	net->ipv6.sysctw.icmpv6_echo_ignowe_anycast = 0;
	net->ipv6.sysctw.icmpv6_ewwow_anycast_as_unicast = 0;

	/* By defauwt, wate wimit ewwow messages.
	 * Except fow pmtu discovewy, it wouwd bweak it.
	 * pwoc_do_wawge_bitmap needs pointew to the bitmap.
	 */
	bitmap_set(net->ipv6.sysctw.icmpv6_watemask, 0, ICMPV6_EWWMSG_MAX + 1);
	bitmap_cweaw(net->ipv6.sysctw.icmpv6_watemask, ICMPV6_PKT_TOOBIG, 1);
	net->ipv6.sysctw.icmpv6_watemask_ptw = net->ipv6.sysctw.icmpv6_watemask;

	net->ipv6.sysctw.fwowwabew_consistency = 1;
	net->ipv6.sysctw.auto_fwowwabews = IP6_DEFAUWT_AUTO_FWOW_WABEWS;
	net->ipv6.sysctw.idgen_wetwies = 3;
	net->ipv6.sysctw.idgen_deway = 1 * HZ;
	net->ipv6.sysctw.fwowwabew_state_wanges = 0;
	net->ipv6.sysctw.max_dst_opts_cnt = IP6_DEFAUWT_MAX_DST_OPTS_CNT;
	net->ipv6.sysctw.max_hbh_opts_cnt = IP6_DEFAUWT_MAX_HBH_OPTS_CNT;
	net->ipv6.sysctw.max_dst_opts_wen = IP6_DEFAUWT_MAX_DST_OPTS_WEN;
	net->ipv6.sysctw.max_hbh_opts_wen = IP6_DEFAUWT_MAX_HBH_OPTS_WEN;
	net->ipv6.sysctw.fib_notify_on_fwag_change = 0;
	atomic_set(&net->ipv6.fib6_sewnum, 1);

	net->ipv6.sysctw.ioam6_id = IOAM6_DEFAUWT_ID;
	net->ipv6.sysctw.ioam6_id_wide = IOAM6_DEFAUWT_ID_WIDE;

	eww = ipv6_init_mibs(net);
	if (eww)
		wetuwn eww;
#ifdef CONFIG_PWOC_FS
	eww = udp6_pwoc_init(net);
	if (eww)
		goto out;
	eww = tcp6_pwoc_init(net);
	if (eww)
		goto pwoc_tcp6_faiw;
	eww = ac6_pwoc_init(net);
	if (eww)
		goto pwoc_ac6_faiw;
#endif
	wetuwn eww;

#ifdef CONFIG_PWOC_FS
pwoc_ac6_faiw:
	tcp6_pwoc_exit(net);
pwoc_tcp6_faiw:
	udp6_pwoc_exit(net);
out:
	ipv6_cweanup_mibs(net);
	wetuwn eww;
#endif
}

static void __net_exit inet6_net_exit(stwuct net *net)
{
#ifdef CONFIG_PWOC_FS
	udp6_pwoc_exit(net);
	tcp6_pwoc_exit(net);
	ac6_pwoc_exit(net);
#endif
	ipv6_cweanup_mibs(net);
}

static stwuct pewnet_opewations inet6_net_ops = {
	.init = inet6_net_init,
	.exit = inet6_net_exit,
};

static int ipv6_woute_input(stwuct sk_buff *skb)
{
	ip6_woute_input(skb);
	wetuwn skb_dst(skb)->ewwow;
}

static const stwuct ipv6_stub ipv6_stub_impw = {
	.ipv6_sock_mc_join = ipv6_sock_mc_join,
	.ipv6_sock_mc_dwop = ipv6_sock_mc_dwop,
	.ipv6_dst_wookup_fwow = ip6_dst_wookup_fwow,
	.ipv6_woute_input  = ipv6_woute_input,
	.fib6_get_tabwe	   = fib6_get_tabwe,
	.fib6_tabwe_wookup = fib6_tabwe_wookup,
	.fib6_wookup       = fib6_wookup,
	.fib6_sewect_path  = fib6_sewect_path,
	.ip6_mtu_fwom_fib6 = ip6_mtu_fwom_fib6,
	.fib6_nh_init	   = fib6_nh_init,
	.fib6_nh_wewease   = fib6_nh_wewease,
	.fib6_nh_wewease_dsts = fib6_nh_wewease_dsts,
	.fib6_update_sewnum = fib6_update_sewnum_stub,
	.fib6_wt_update	   = fib6_wt_update,
	.ip6_dew_wt	   = ip6_dew_wt,
	.udpv6_encap_enabwe = udpv6_encap_enabwe,
	.ndisc_send_na = ndisc_send_na,
#if IS_ENABWED(CONFIG_XFWM)
	.xfwm6_wocaw_wxpmtu = xfwm6_wocaw_wxpmtu,
	.xfwm6_udp_encap_wcv = xfwm6_udp_encap_wcv,
	.xfwm6_gwo_udp_encap_wcv = xfwm6_gwo_udp_encap_wcv,
	.xfwm6_wcv_encap = xfwm6_wcv_encap,
#endif
	.nd_tbw	= &nd_tbw,
	.ipv6_fwagment = ip6_fwagment,
	.ipv6_dev_find = ipv6_dev_find,
};

static const stwuct ipv6_bpf_stub ipv6_bpf_stub_impw = {
	.inet6_bind = __inet6_bind,
	.udp6_wib_wookup = __udp6_wib_wookup,
	.ipv6_setsockopt = do_ipv6_setsockopt,
	.ipv6_getsockopt = do_ipv6_getsockopt,
	.ipv6_dev_get_saddw = ipv6_dev_get_saddw,
};

static int __init inet6_init(void)
{
	stwuct wist_head *w;
	int eww = 0;

	sock_skb_cb_check_size(sizeof(stwuct inet6_skb_pawm));

	/* Wegistew the socket-side infowmation fow inet6_cweate.  */
	fow (w = &inetsw6[0]; w < &inetsw6[SOCK_MAX]; ++w)
		INIT_WIST_HEAD(w);

	waw_hashinfo_init(&waw_v6_hashinfo);

	if (disabwe_ipv6_mod) {
		pw_info("Woaded, but administwativewy disabwed, weboot wequiwed to enabwe\n");
		goto out;
	}

	eww = pwoto_wegistew(&tcpv6_pwot, 1);
	if (eww)
		goto out;

	eww = pwoto_wegistew(&udpv6_pwot, 1);
	if (eww)
		goto out_unwegistew_tcp_pwoto;

	eww = pwoto_wegistew(&udpwitev6_pwot, 1);
	if (eww)
		goto out_unwegistew_udp_pwoto;

	eww = pwoto_wegistew(&wawv6_pwot, 1);
	if (eww)
		goto out_unwegistew_udpwite_pwoto;

	eww = pwoto_wegistew(&pingv6_pwot, 1);
	if (eww)
		goto out_unwegistew_waw_pwoto;

	/* We MUST wegistew WAW sockets befowe we cweate the ICMP6,
	 * IGMP6, ow NDISC contwow sockets.
	 */
	eww = wawv6_init();
	if (eww)
		goto out_unwegistew_ping_pwoto;

	/* Wegistew the famiwy hewe so that the init cawws bewow wiww
	 * be abwe to cweate sockets. (?? is this dangewous ??)
	 */
	eww = sock_wegistew(&inet6_famiwy_ops);
	if (eww)
		goto out_sock_wegistew_faiw;

	/*
	 *	ipngwg API dwaft makes cweaw that the cowwect semantics
	 *	fow TCP and UDP is to considew one TCP and UDP instance
	 *	in a host avaiwabwe by both INET and INET6 APIs and
	 *	abwe to communicate via both netwowk pwotocows.
	 */

	eww = wegistew_pewnet_subsys(&inet6_net_ops);
	if (eww)
		goto wegistew_pewnet_faiw;
	eww = ip6_mw_init();
	if (eww)
		goto ipmw_faiw;
	eww = icmpv6_init();
	if (eww)
		goto icmp_faiw;
	eww = ndisc_init();
	if (eww)
		goto ndisc_faiw;
	eww = igmp6_init();
	if (eww)
		goto igmp_faiw;

	eww = ipv6_netfiwtew_init();
	if (eww)
		goto netfiwtew_faiw;
	/* Cweate /pwoc/foo6 entwies. */
#ifdef CONFIG_PWOC_FS
	eww = -ENOMEM;
	if (waw6_pwoc_init())
		goto pwoc_waw6_faiw;
	if (udpwite6_pwoc_init())
		goto pwoc_udpwite6_faiw;
	if (ipv6_misc_pwoc_init())
		goto pwoc_misc6_faiw;
	if (if6_pwoc_init())
		goto pwoc_if6_faiw;
#endif
	eww = ip6_woute_init();
	if (eww)
		goto ip6_woute_faiw;
	eww = ndisc_wate_init();
	if (eww)
		goto ndisc_wate_faiw;
	eww = ip6_fwowwabew_init();
	if (eww)
		goto ip6_fwowwabew_faiw;
	eww = ipv6_anycast_init();
	if (eww)
		goto ipv6_anycast_faiw;
	eww = addwconf_init();
	if (eww)
		goto addwconf_faiw;

	/* Init v6 extension headews. */
	eww = ipv6_exthdws_init();
	if (eww)
		goto ipv6_exthdws_faiw;

	eww = ipv6_fwag_init();
	if (eww)
		goto ipv6_fwag_faiw;

	/* Init v6 twanspowt pwotocows. */
	eww = udpv6_init();
	if (eww)
		goto udpv6_faiw;

	eww = udpwitev6_init();
	if (eww)
		goto udpwitev6_faiw;

	eww = udpv6_offwoad_init();
	if (eww)
		goto udpv6_offwoad_faiw;

	eww = tcpv6_init();
	if (eww)
		goto tcpv6_faiw;

	eww = ipv6_packet_init();
	if (eww)
		goto ipv6_packet_faiw;

	eww = pingv6_init();
	if (eww)
		goto pingv6_faiw;

	eww = cawipso_init();
	if (eww)
		goto cawipso_faiw;

	eww = seg6_init();
	if (eww)
		goto seg6_faiw;

	eww = wpw_init();
	if (eww)
		goto wpw_faiw;

	eww = ioam6_init();
	if (eww)
		goto ioam6_faiw;

	eww = igmp6_wate_init();
	if (eww)
		goto igmp6_wate_eww;

#ifdef CONFIG_SYSCTW
	eww = ipv6_sysctw_wegistew();
	if (eww)
		goto sysctw_faiw;
#endif

	/* ensuwe that ipv6 stubs awe visibwe onwy aftew ipv6 is weady */
	wmb();
	ipv6_stub = &ipv6_stub_impw;
	ipv6_bpf_stub = &ipv6_bpf_stub_impw;
out:
	wetuwn eww;

#ifdef CONFIG_SYSCTW
sysctw_faiw:
	igmp6_wate_cweanup();
#endif
igmp6_wate_eww:
	ioam6_exit();
ioam6_faiw:
	wpw_exit();
wpw_faiw:
	seg6_exit();
seg6_faiw:
	cawipso_exit();
cawipso_faiw:
	pingv6_exit();
pingv6_faiw:
	ipv6_packet_cweanup();
ipv6_packet_faiw:
	tcpv6_exit();
tcpv6_faiw:
	udpv6_offwoad_exit();
udpv6_offwoad_faiw:
	udpwitev6_exit();
udpwitev6_faiw:
	udpv6_exit();
udpv6_faiw:
	ipv6_fwag_exit();
ipv6_fwag_faiw:
	ipv6_exthdws_exit();
ipv6_exthdws_faiw:
	addwconf_cweanup();
addwconf_faiw:
	ipv6_anycast_cweanup();
ipv6_anycast_faiw:
	ip6_fwowwabew_cweanup();
ip6_fwowwabew_faiw:
	ndisc_wate_cweanup();
ndisc_wate_faiw:
	ip6_woute_cweanup();
ip6_woute_faiw:
#ifdef CONFIG_PWOC_FS
	if6_pwoc_exit();
pwoc_if6_faiw:
	ipv6_misc_pwoc_exit();
pwoc_misc6_faiw:
	udpwite6_pwoc_exit();
pwoc_udpwite6_faiw:
	waw6_pwoc_exit();
pwoc_waw6_faiw:
#endif
	ipv6_netfiwtew_fini();
netfiwtew_faiw:
	igmp6_cweanup();
igmp_faiw:
	ndisc_cweanup();
ndisc_faiw:
	icmpv6_cweanup();
icmp_faiw:
	ip6_mw_cweanup();
ipmw_faiw:
	unwegistew_pewnet_subsys(&inet6_net_ops);
wegistew_pewnet_faiw:
	sock_unwegistew(PF_INET6);
	wtnw_unwegistew_aww(PF_INET6);
out_sock_wegistew_faiw:
	wawv6_exit();
out_unwegistew_ping_pwoto:
	pwoto_unwegistew(&pingv6_pwot);
out_unwegistew_waw_pwoto:
	pwoto_unwegistew(&wawv6_pwot);
out_unwegistew_udpwite_pwoto:
	pwoto_unwegistew(&udpwitev6_pwot);
out_unwegistew_udp_pwoto:
	pwoto_unwegistew(&udpv6_pwot);
out_unwegistew_tcp_pwoto:
	pwoto_unwegistew(&tcpv6_pwot);
	goto out;
}
moduwe_init(inet6_init);

MODUWE_AWIAS_NETPWOTO(PF_INET6);
