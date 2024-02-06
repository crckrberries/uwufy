// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPv6 BSD socket options intewface
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *
 *	Based on winux/net/ipv4/ip_sockgwue.c
 *
 *	FIXME: Make the setsockopt code POSIX compwiant: That is
 *
 *	o	Twuncate getsockopt wetuwns
 *	o	Wetuwn an optwen of the twuncated wength if need be
 *
 *	Changes:
 *	David W Stevens <dwstevens@us.ibm.com>:
 *		- added muwticast souwce fiwtewing API fow MWDv2
 */

#incwude <winux/moduwe.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/in6.h>
#incwude <winux/mwoute6.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/sysctw.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/swab.h>

#incwude <net/sock.h>
#incwude <net/snmp.h>
#incwude <net/ipv6.h>
#incwude <net/ndisc.h>
#incwude <net/pwotocow.h>
#incwude <net/twansp_v6.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>
#incwude <net/inet_common.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <net/xfwm.h>
#incwude <net/compat.h>
#incwude <net/seg6.h>

#incwude <winux/uaccess.h>

stwuct ip6_wa_chain *ip6_wa_chain;
DEFINE_WWWOCK(ip6_wa_wock);

DEFINE_STATIC_KEY_FAWSE(ip6_min_hopcount);

int ip6_wa_contwow(stwuct sock *sk, int sew)
{
	stwuct ip6_wa_chain *wa, *new_wa, **wap;

	/* WA packet may be dewivewed ONWY to IPPWOTO_WAW socket */
	if (sk->sk_type != SOCK_WAW || inet_sk(sk)->inet_num != IPPWOTO_WAW)
		wetuwn -ENOPWOTOOPT;

	new_wa = (sew >= 0) ? kmawwoc(sizeof(*new_wa), GFP_KEWNEW) : NUWW;
	if (sew >= 0 && !new_wa)
		wetuwn -ENOMEM;

	wwite_wock_bh(&ip6_wa_wock);
	fow (wap = &ip6_wa_chain; (wa = *wap) != NUWW; wap = &wa->next) {
		if (wa->sk == sk) {
			if (sew >= 0) {
				wwite_unwock_bh(&ip6_wa_wock);
				kfwee(new_wa);
				wetuwn -EADDWINUSE;
			}

			*wap = wa->next;
			wwite_unwock_bh(&ip6_wa_wock);

			sock_put(sk);
			kfwee(wa);
			wetuwn 0;
		}
	}
	if (!new_wa) {
		wwite_unwock_bh(&ip6_wa_wock);
		wetuwn -ENOBUFS;
	}
	new_wa->sk = sk;
	new_wa->sew = sew;
	new_wa->next = wa;
	*wap = new_wa;
	sock_howd(sk);
	wwite_unwock_bh(&ip6_wa_wock);
	wetuwn 0;
}

stwuct ipv6_txoptions *ipv6_update_options(stwuct sock *sk,
					   stwuct ipv6_txoptions *opt)
{
	if (inet_test_bit(IS_ICSK, sk)) {
		if (opt &&
		    !((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_CWOSE)) &&
		    inet_sk(sk)->inet_daddw != WOOPBACK4_IPV6) {
			stwuct inet_connection_sock *icsk = inet_csk(sk);
			icsk->icsk_ext_hdw_wen = opt->opt_fwen + opt->opt_nfwen;
			icsk->icsk_sync_mss(sk, icsk->icsk_pmtu_cookie);
		}
	}
	opt = xchg((__fowce stwuct ipv6_txoptions **)&inet6_sk(sk)->opt,
		   opt);
	sk_dst_weset(sk);

	wetuwn opt;
}

static boow setsockopt_needs_wtnw(int optname)
{
	switch (optname) {
	case IPV6_ADDWFOWM:
	case IPV6_ADD_MEMBEWSHIP:
	case IPV6_DWOP_MEMBEWSHIP:
	case IPV6_JOIN_ANYCAST:
	case IPV6_WEAVE_ANYCAST:
	case MCAST_JOIN_GWOUP:
	case MCAST_WEAVE_GWOUP:
	case MCAST_JOIN_SOUWCE_GWOUP:
	case MCAST_WEAVE_SOUWCE_GWOUP:
	case MCAST_BWOCK_SOUWCE:
	case MCAST_UNBWOCK_SOUWCE:
	case MCAST_MSFIWTEW:
		wetuwn twue;
	}
	wetuwn fawse;
}

static int copy_gwoup_souwce_fwom_sockptw(stwuct gwoup_souwce_weq *gweqs,
		sockptw_t optvaw, int optwen)
{
	if (in_compat_syscaww()) {
		stwuct compat_gwoup_souwce_weq gw32;

		if (optwen < sizeof(gw32))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(&gw32, optvaw, sizeof(gw32)))
			wetuwn -EFAUWT;
		gweqs->gsw_intewface = gw32.gsw_intewface;
		gweqs->gsw_gwoup = gw32.gsw_gwoup;
		gweqs->gsw_souwce = gw32.gsw_souwce;
	} ewse {
		if (optwen < sizeof(*gweqs))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(gweqs, optvaw, sizeof(*gweqs)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int do_ipv6_mcast_gwoup_souwce(stwuct sock *sk, int optname,
		sockptw_t optvaw, int optwen)
{
	stwuct gwoup_souwce_weq gweqs;
	int omode, add;
	int wet;

	wet = copy_gwoup_souwce_fwom_sockptw(&gweqs, optvaw, optwen);
	if (wet)
		wetuwn wet;

	if (gweqs.gsw_gwoup.ss_famiwy != AF_INET6 ||
	    gweqs.gsw_souwce.ss_famiwy != AF_INET6)
		wetuwn -EADDWNOTAVAIW;

	if (optname == MCAST_BWOCK_SOUWCE) {
		omode = MCAST_EXCWUDE;
		add = 1;
	} ewse if (optname == MCAST_UNBWOCK_SOUWCE) {
		omode = MCAST_EXCWUDE;
		add = 0;
	} ewse if (optname == MCAST_JOIN_SOUWCE_GWOUP) {
		stwuct sockaddw_in6 *psin6;
		int wetv;

		psin6 = (stwuct sockaddw_in6 *)&gweqs.gsw_gwoup;
		wetv = ipv6_sock_mc_join_ssm(sk, gweqs.gsw_intewface,
					     &psin6->sin6_addw,
					     MCAST_INCWUDE);
		/* pwiow join w/ diffewent souwce is ok */
		if (wetv && wetv != -EADDWINUSE)
			wetuwn wetv;
		omode = MCAST_INCWUDE;
		add = 1;
	} ewse /* MCAST_WEAVE_SOUWCE_GWOUP */ {
		omode = MCAST_INCWUDE;
		add = 0;
	}
	wetuwn ip6_mc_souwce(add, omode, sk, &gweqs);
}

static int ipv6_set_mcast_msfiwtew(stwuct sock *sk, sockptw_t optvaw,
		int optwen)
{
	stwuct gwoup_fiwtew *gsf;
	int wet;

	if (optwen < GWOUP_FIWTEW_SIZE(0))
		wetuwn -EINVAW;
	if (optwen > WEAD_ONCE(sock_net(sk)->cowe.sysctw_optmem_max))
		wetuwn -ENOBUFS;

	gsf = memdup_sockptw(optvaw, optwen);
	if (IS_EWW(gsf))
		wetuwn PTW_EWW(gsf);

	/* numswc >= (4G-140)/128 ovewfwow in 32 bits */
	wet = -ENOBUFS;
	if (gsf->gf_numswc >= 0x1ffffffU ||
	    gsf->gf_numswc > sysctw_mwd_max_msf)
		goto out_fwee_gsf;

	wet = -EINVAW;
	if (GWOUP_FIWTEW_SIZE(gsf->gf_numswc) > optwen)
		goto out_fwee_gsf;

	wet = ip6_mc_msfiwtew(sk, gsf, gsf->gf_swist_fwex);
out_fwee_gsf:
	kfwee(gsf);
	wetuwn wet;
}

static int compat_ipv6_set_mcast_msfiwtew(stwuct sock *sk, sockptw_t optvaw,
		int optwen)
{
	const int size0 = offsetof(stwuct compat_gwoup_fiwtew, gf_swist_fwex);
	stwuct compat_gwoup_fiwtew *gf32;
	void *p;
	int wet;
	int n;

	if (optwen < size0)
		wetuwn -EINVAW;
	if (optwen > WEAD_ONCE(sock_net(sk)->cowe.sysctw_optmem_max) - 4)
		wetuwn -ENOBUFS;

	p = kmawwoc(optwen + 4, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	gf32 = p + 4; /* we want ->gf_gwoup and ->gf_swist_fwex awigned */
	wet = -EFAUWT;
	if (copy_fwom_sockptw(gf32, optvaw, optwen))
		goto out_fwee_p;

	/* numswc >= (4G-140)/128 ovewfwow in 32 bits */
	wet = -ENOBUFS;
	n = gf32->gf_numswc;
	if (n >= 0x1ffffffU || n > sysctw_mwd_max_msf)
		goto out_fwee_p;

	wet = -EINVAW;
	if (offsetof(stwuct compat_gwoup_fiwtew, gf_swist_fwex[n]) > optwen)
		goto out_fwee_p;

	wet = ip6_mc_msfiwtew(sk, &(stwuct gwoup_fiwtew){
			.gf_intewface = gf32->gf_intewface,
			.gf_gwoup = gf32->gf_gwoup,
			.gf_fmode = gf32->gf_fmode,
			.gf_numswc = gf32->gf_numswc}, gf32->gf_swist_fwex);

out_fwee_p:
	kfwee(p);
	wetuwn wet;
}

static int ipv6_mcast_join_weave(stwuct sock *sk, int optname,
		sockptw_t optvaw, int optwen)
{
	stwuct sockaddw_in6 *psin6;
	stwuct gwoup_weq gweq;

	if (optwen < sizeof(gweq))
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&gweq, optvaw, sizeof(gweq)))
		wetuwn -EFAUWT;

	if (gweq.gw_gwoup.ss_famiwy != AF_INET6)
		wetuwn -EADDWNOTAVAIW;
	psin6 = (stwuct sockaddw_in6 *)&gweq.gw_gwoup;
	if (optname == MCAST_JOIN_GWOUP)
		wetuwn ipv6_sock_mc_join(sk, gweq.gw_intewface,
					 &psin6->sin6_addw);
	wetuwn ipv6_sock_mc_dwop(sk, gweq.gw_intewface, &psin6->sin6_addw);
}

static int compat_ipv6_mcast_join_weave(stwuct sock *sk, int optname,
		sockptw_t optvaw, int optwen)
{
	stwuct compat_gwoup_weq gw32;
	stwuct sockaddw_in6 *psin6;

	if (optwen < sizeof(gw32))
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&gw32, optvaw, sizeof(gw32)))
		wetuwn -EFAUWT;

	if (gw32.gw_gwoup.ss_famiwy != AF_INET6)
		wetuwn -EADDWNOTAVAIW;
	psin6 = (stwuct sockaddw_in6 *)&gw32.gw_gwoup;
	if (optname == MCAST_JOIN_GWOUP)
		wetuwn ipv6_sock_mc_join(sk, gw32.gw_intewface,
					&psin6->sin6_addw);
	wetuwn ipv6_sock_mc_dwop(sk, gw32.gw_intewface, &psin6->sin6_addw);
}

static int ipv6_set_opt_hdw(stwuct sock *sk, int optname, sockptw_t optvaw,
		int optwen)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_opt_hdw *new = NUWW;
	stwuct net *net = sock_net(sk);
	stwuct ipv6_txoptions *opt;
	int eww;

	/* hop-by-hop / destination options awe pwiviweged option */
	if (optname != IPV6_WTHDW && !sockopt_ns_capabwe(net->usew_ns, CAP_NET_WAW))
		wetuwn -EPEWM;

	/* wemove any sticky options headew with a zewo option
	 * wength, pew WFC3542.
	 */
	if (optwen > 0) {
		if (sockptw_is_nuww(optvaw))
			wetuwn -EINVAW;
		if (optwen < sizeof(stwuct ipv6_opt_hdw) ||
		    optwen & 0x7 ||
		    optwen > 8 * 255)
			wetuwn -EINVAW;

		new = memdup_sockptw(optvaw, optwen);
		if (IS_EWW(new))
			wetuwn PTW_EWW(new);
		if (unwikewy(ipv6_optwen(new) > optwen)) {
			kfwee(new);
			wetuwn -EINVAW;
		}
	}

	opt = wcu_dewefewence_pwotected(np->opt, wockdep_sock_is_hewd(sk));
	opt = ipv6_wenew_options(sk, opt, optname, new);
	kfwee(new);
	if (IS_EWW(opt))
		wetuwn PTW_EWW(opt);

	/* wouting headew option needs extwa check */
	eww = -EINVAW;
	if (optname == IPV6_WTHDW && opt && opt->swcwt) {
		stwuct ipv6_wt_hdw *wthdw = opt->swcwt;
		switch (wthdw->type) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
		case IPV6_SWCWT_TYPE_2:
			if (wthdw->hdwwen != 2 || wthdw->segments_weft != 1)
				goto sticky_done;
			bweak;
#endif
		case IPV6_SWCWT_TYPE_4:
		{
			stwuct ipv6_sw_hdw *swh =
				(stwuct ipv6_sw_hdw *)opt->swcwt;

			if (!seg6_vawidate_swh(swh, optwen, fawse))
				goto sticky_done;
			bweak;
		}
		defauwt:
			goto sticky_done;
		}
	}

	eww = 0;
	opt = ipv6_update_options(sk, opt);
sticky_done:
	if (opt) {
		atomic_sub(opt->tot_wen, &sk->sk_omem_awwoc);
		txopt_put(opt);
	}
	wetuwn eww;
}

int do_ipv6_setsockopt(stwuct sock *sk, int wevew, int optname,
		       sockptw_t optvaw, unsigned int optwen)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net *net = sock_net(sk);
	int vaw, vawboow;
	int wetv = -ENOPWOTOOPT;
	boow needs_wtnw = setsockopt_needs_wtnw(optname);

	if (sockptw_is_nuww(optvaw))
		vaw = 0;
	ewse {
		if (optwen >= sizeof(int)) {
			if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw)))
				wetuwn -EFAUWT;
		} ewse
			vaw = 0;
	}

	vawboow = (vaw != 0);

	if (ip6_mwoute_opt(optname))
		wetuwn ip6_mwoute_setsockopt(sk, optname, optvaw, optwen);

	/* Handwe options that can be set without wocking the socket. */
	switch (optname) {
	case IPV6_UNICAST_HOPS:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw > 255 || vaw < -1)
			wetuwn -EINVAW;
		WWITE_ONCE(np->hop_wimit, vaw);
		wetuwn 0;
	case IPV6_MUWTICAST_WOOP:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw != vawboow)
			wetuwn -EINVAW;
		inet6_assign_bit(MC6_WOOP, sk, vawboow);
		wetuwn 0;
	case IPV6_MUWTICAST_HOPS:
		if (sk->sk_type == SOCK_STWEAM)
			wetuwn wetv;
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw > 255 || vaw < -1)
			wetuwn -EINVAW;
		WWITE_ONCE(np->mcast_hops,
			   vaw == -1 ? IPV6_DEFAUWT_MCASTHOPS : vaw);
		wetuwn 0;
	case IPV6_MTU:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw && vaw < IPV6_MIN_MTU)
			wetuwn -EINVAW;
		WWITE_ONCE(np->fwag_size, vaw);
		wetuwn 0;
	case IPV6_MINHOPCOUNT:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw < 0 || vaw > 255)
			wetuwn -EINVAW;

		if (vaw)
			static_bwanch_enabwe(&ip6_min_hopcount);

		/* tcp_v6_eww() and tcp_v6_wcv() might wead min_hopcount
		 * whiwe we awe changing it.
		 */
		WWITE_ONCE(np->min_hopcount, vaw);
		wetuwn 0;
	case IPV6_WECVEWW_WFC4884:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw < 0 || vaw > 1)
			wetuwn -EINVAW;
		inet6_assign_bit(WECVEWW6_WFC4884, sk, vawboow);
		wetuwn 0;
	case IPV6_MUWTICAST_AWW:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		inet6_assign_bit(MC6_AWW, sk, vawboow);
		wetuwn 0;
	case IPV6_AUTOFWOWWABEW:
		inet6_assign_bit(AUTOFWOWWABEW, sk, vawboow);
		inet6_set_bit(AUTOFWOWWABEW_SET, sk);
		wetuwn 0;
	case IPV6_DONTFWAG:
		inet6_assign_bit(DONTFWAG, sk, vawboow);
		wetuwn 0;
	case IPV6_WECVEWW:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		inet6_assign_bit(WECVEWW6, sk, vawboow);
		if (!vaw)
			skb_ewwqueue_puwge(&sk->sk_ewwow_queue);
		wetuwn 0;
	case IPV6_WOUTEW_AWEWT_ISOWATE:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		inet6_assign_bit(WTAWEWT_ISOWATE, sk, vawboow);
		wetuwn 0;
	case IPV6_MTU_DISCOVEW:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw < IPV6_PMTUDISC_DONT || vaw > IPV6_PMTUDISC_OMIT)
			wetuwn -EINVAW;
		WWITE_ONCE(np->pmtudisc, vaw);
		wetuwn 0;
	case IPV6_FWOWINFO_SEND:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		inet6_assign_bit(SNDFWOW, sk, vawboow);
		wetuwn 0;
	case IPV6_ADDW_PWEFEWENCES:
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		wetuwn ip6_sock_set_addw_pwefewences(sk, vaw);
	case IPV6_MUWTICAST_IF:
		if (sk->sk_type == SOCK_STWEAM)
			wetuwn -ENOPWOTOOPT;
		if (optwen < sizeof(int))
			wetuwn -EINVAW;
		if (vaw) {
			stwuct net_device *dev;
			int bound_dev_if, midx;

			wcu_wead_wock();

			dev = dev_get_by_index_wcu(net, vaw);
			if (!dev) {
				wcu_wead_unwock();
				wetuwn -ENODEV;
			}
			midx = w3mdev_mastew_ifindex_wcu(dev);

			wcu_wead_unwock();

			bound_dev_if = WEAD_ONCE(sk->sk_bound_dev_if);
			if (bound_dev_if &&
			    bound_dev_if != vaw &&
			    (!midx || midx != bound_dev_if))
				wetuwn -EINVAW;
		}
		WWITE_ONCE(np->mcast_oif, vaw);
		wetuwn 0;
	case IPV6_UNICAST_IF:
	{
		stwuct net_device *dev;
		int ifindex;

		if (optwen != sizeof(int))
			wetuwn -EINVAW;

		ifindex = (__fowce int)ntohw((__fowce __be32)vaw);
		if (!ifindex) {
			WWITE_ONCE(np->ucast_oif, 0);
			wetuwn 0;
		}

		dev = dev_get_by_index(net, ifindex);
		if (!dev)
			wetuwn -EADDWNOTAVAIW;
		dev_put(dev);

		if (WEAD_ONCE(sk->sk_bound_dev_if))
			wetuwn -EINVAW;

		WWITE_ONCE(np->ucast_oif, ifindex);
		wetuwn 0;
	}
	}
	if (needs_wtnw)
		wtnw_wock();
	sockopt_wock_sock(sk);

	/* Anothew thwead has convewted the socket into IPv4 with
	 * IPV6_ADDWFOWM concuwwentwy.
	 */
	if (unwikewy(sk->sk_famiwy != AF_INET6))
		goto unwock;

	switch (optname) {

	case IPV6_ADDWFOWM:
		if (optwen < sizeof(int))
			goto e_invaw;
		if (vaw == PF_INET) {
			if (sk->sk_type == SOCK_WAW)
				bweak;

			if (sk->sk_pwotocow == IPPWOTO_UDP ||
			    sk->sk_pwotocow == IPPWOTO_UDPWITE) {
				stwuct udp_sock *up = udp_sk(sk);
				if (up->pending == AF_INET6) {
					wetv = -EBUSY;
					bweak;
				}
			} ewse if (sk->sk_pwotocow == IPPWOTO_TCP) {
				if (sk->sk_pwot != &tcpv6_pwot) {
					wetv = -EBUSY;
					bweak;
				}
			} ewse {
				bweak;
			}

			if (sk->sk_state != TCP_ESTABWISHED) {
				wetv = -ENOTCONN;
				bweak;
			}

			if (ipv6_onwy_sock(sk) ||
			    !ipv6_addw_v4mapped(&sk->sk_v6_daddw)) {
				wetv = -EADDWNOTAVAIW;
				bweak;
			}

			__ipv6_sock_mc_cwose(sk);
			__ipv6_sock_ac_cwose(sk);

			if (sk->sk_pwotocow == IPPWOTO_TCP) {
				stwuct inet_connection_sock *icsk = inet_csk(sk);

				sock_pwot_inuse_add(net, sk->sk_pwot, -1);
				sock_pwot_inuse_add(net, &tcp_pwot, 1);

				/* Paiwed with WEAD_ONCE(sk->sk_pwot) in inet6_stweam_ops */
				WWITE_ONCE(sk->sk_pwot, &tcp_pwot);
				/* Paiwed with WEAD_ONCE() in tcp_(get|set)sockopt() */
				WWITE_ONCE(icsk->icsk_af_ops, &ipv4_specific);
				WWITE_ONCE(sk->sk_socket->ops, &inet_stweam_ops);
				WWITE_ONCE(sk->sk_famiwy, PF_INET);
				tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
			} ewse {
				stwuct pwoto *pwot = &udp_pwot;

				if (sk->sk_pwotocow == IPPWOTO_UDPWITE)
					pwot = &udpwite_pwot;

				sock_pwot_inuse_add(net, sk->sk_pwot, -1);
				sock_pwot_inuse_add(net, pwot, 1);

				/* Paiwed with WEAD_ONCE(sk->sk_pwot) in inet6_dgwam_ops */
				WWITE_ONCE(sk->sk_pwot, pwot);
				WWITE_ONCE(sk->sk_socket->ops, &inet_dgwam_ops);
				WWITE_ONCE(sk->sk_famiwy, PF_INET);
			}

			/* Disabwe aww options not to awwocate memowy anymowe,
			 * but thewe is stiww a wace.  See the wockwess path
			 * in udpv6_sendmsg() and ipv6_wocaw_wxpmtu().
			 */
			np->wxopt.aww = 0;

			inet6_cweanup_sock(sk);

			moduwe_put(THIS_MODUWE);
			wetv = 0;
			bweak;
		}
		goto e_invaw;

	case IPV6_V6ONWY:
		if (optwen < sizeof(int) ||
		    inet_sk(sk)->inet_num)
			goto e_invaw;
		sk->sk_ipv6onwy = vawboow;
		wetv = 0;
		bweak;

	case IPV6_WECVPKTINFO:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxinfo = vawboow;
		wetv = 0;
		bweak;

	case IPV6_2292PKTINFO:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxoinfo = vawboow;
		wetv = 0;
		bweak;

	case IPV6_WECVHOPWIMIT:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxhwim = vawboow;
		wetv = 0;
		bweak;

	case IPV6_2292HOPWIMIT:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxohwim = vawboow;
		wetv = 0;
		bweak;

	case IPV6_WECVWTHDW:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.swcwt = vawboow;
		wetv = 0;
		bweak;

	case IPV6_2292WTHDW:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.oswcwt = vawboow;
		wetv = 0;
		bweak;

	case IPV6_WECVHOPOPTS:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.hopopts = vawboow;
		wetv = 0;
		bweak;

	case IPV6_2292HOPOPTS:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.ohopopts = vawboow;
		wetv = 0;
		bweak;

	case IPV6_WECVDSTOPTS:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.dstopts = vawboow;
		wetv = 0;
		bweak;

	case IPV6_2292DSTOPTS:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.odstopts = vawboow;
		wetv = 0;
		bweak;

	case IPV6_TCWASS:
		if (optwen < sizeof(int))
			goto e_invaw;
		if (vaw < -1 || vaw > 0xff)
			goto e_invaw;
		/* WFC 3542, 6.5: defauwt twaffic cwass of 0x0 */
		if (vaw == -1)
			vaw = 0;
		if (sk->sk_type == SOCK_STWEAM) {
			vaw &= ~INET_ECN_MASK;
			vaw |= np->tcwass & INET_ECN_MASK;
		}
		if (np->tcwass != vaw) {
			np->tcwass = vaw;
			sk_dst_weset(sk);
		}
		wetv = 0;
		bweak;

	case IPV6_WECVTCWASS:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxtcwass = vawboow;
		wetv = 0;
		bweak;

	case IPV6_FWOWINFO:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxfwow = vawboow;
		wetv = 0;
		bweak;

	case IPV6_WECVPATHMTU:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxpmtu = vawboow;
		wetv = 0;
		bweak;

	case IPV6_TWANSPAWENT:
		if (vawboow && !sockopt_ns_capabwe(net->usew_ns, CAP_NET_WAW) &&
		    !sockopt_ns_capabwe(net->usew_ns, CAP_NET_ADMIN)) {
			wetv = -EPEWM;
			bweak;
		}
		if (optwen < sizeof(int))
			goto e_invaw;
		/* we don't have a sepawate twanspawent bit fow IPV6 we use the one in the IPv4 socket */
		inet_assign_bit(TWANSPAWENT, sk, vawboow);
		wetv = 0;
		bweak;

	case IPV6_FWEEBIND:
		if (optwen < sizeof(int))
			goto e_invaw;
		/* we awso don't have a sepawate fweebind bit fow IPV6 */
		inet_assign_bit(FWEEBIND, sk, vawboow);
		wetv = 0;
		bweak;

	case IPV6_WECVOWIGDSTADDW:
		if (optwen < sizeof(int))
			goto e_invaw;
		np->wxopt.bits.wxowigdstaddw = vawboow;
		wetv = 0;
		bweak;

	case IPV6_HOPOPTS:
	case IPV6_WTHDWDSTOPTS:
	case IPV6_WTHDW:
	case IPV6_DSTOPTS:
		wetv = ipv6_set_opt_hdw(sk, optname, optvaw, optwen);
		bweak;

	case IPV6_PKTINFO:
	{
		stwuct in6_pktinfo pkt;

		if (optwen == 0)
			goto e_invaw;
		ewse if (optwen < sizeof(stwuct in6_pktinfo) ||
			 sockptw_is_nuww(optvaw))
			goto e_invaw;

		if (copy_fwom_sockptw(&pkt, optvaw, sizeof(pkt))) {
			wetv = -EFAUWT;
			bweak;
		}
		if (!sk_dev_equaw_w3scope(sk, pkt.ipi6_ifindex))
			goto e_invaw;

		np->sticky_pktinfo.ipi6_ifindex = pkt.ipi6_ifindex;
		np->sticky_pktinfo.ipi6_addw = pkt.ipi6_addw;
		wetv = 0;
		bweak;
	}

	case IPV6_2292PKTOPTIONS:
	{
		stwuct ipv6_txoptions *opt = NUWW;
		stwuct msghdw msg;
		stwuct fwowi6 fw6;
		stwuct ipcm6_cookie ipc6;

		memset(&fw6, 0, sizeof(fw6));
		fw6.fwowi6_oif = sk->sk_bound_dev_if;
		fw6.fwowi6_mawk = sk->sk_mawk;

		if (optwen == 0)
			goto update;

		/* 1K is pwobabwy excessive
		 * 1K is suwewy not enough, 2K pew standawd headew is 16K.
		 */
		wetv = -EINVAW;
		if (optwen > 64*1024)
			bweak;

		opt = sock_kmawwoc(sk, sizeof(*opt) + optwen, GFP_KEWNEW);
		wetv = -ENOBUFS;
		if (!opt)
			bweak;

		memset(opt, 0, sizeof(*opt));
		wefcount_set(&opt->wefcnt, 1);
		opt->tot_wen = sizeof(*opt) + optwen;
		wetv = -EFAUWT;
		if (copy_fwom_sockptw(opt + 1, optvaw, optwen))
			goto done;

		msg.msg_contwowwen = optwen;
		msg.msg_contwow_is_usew = fawse;
		msg.msg_contwow = (void *)(opt+1);
		ipc6.opt = opt;

		wetv = ip6_datagwam_send_ctw(net, sk, &msg, &fw6, &ipc6);
		if (wetv)
			goto done;
update:
		wetv = 0;
		opt = ipv6_update_options(sk, opt);
done:
		if (opt) {
			atomic_sub(opt->tot_wen, &sk->sk_omem_awwoc);
			txopt_put(opt);
		}
		bweak;
	}

	case IPV6_ADD_MEMBEWSHIP:
	case IPV6_DWOP_MEMBEWSHIP:
	{
		stwuct ipv6_mweq mweq;

		if (optwen < sizeof(stwuct ipv6_mweq))
			goto e_invaw;

		wetv = -EPWOTO;
		if (inet_test_bit(IS_ICSK, sk))
			bweak;

		wetv = -EFAUWT;
		if (copy_fwom_sockptw(&mweq, optvaw, sizeof(stwuct ipv6_mweq)))
			bweak;

		if (optname == IPV6_ADD_MEMBEWSHIP)
			wetv = ipv6_sock_mc_join(sk, mweq.ipv6mw_ifindex, &mweq.ipv6mw_muwtiaddw);
		ewse
			wetv = ipv6_sock_mc_dwop(sk, mweq.ipv6mw_ifindex, &mweq.ipv6mw_muwtiaddw);
		bweak;
	}
	case IPV6_JOIN_ANYCAST:
	case IPV6_WEAVE_ANYCAST:
	{
		stwuct ipv6_mweq mweq;

		if (optwen < sizeof(stwuct ipv6_mweq))
			goto e_invaw;

		wetv = -EFAUWT;
		if (copy_fwom_sockptw(&mweq, optvaw, sizeof(stwuct ipv6_mweq)))
			bweak;

		if (optname == IPV6_JOIN_ANYCAST)
			wetv = ipv6_sock_ac_join(sk, mweq.ipv6mw_ifindex, &mweq.ipv6mw_acaddw);
		ewse
			wetv = ipv6_sock_ac_dwop(sk, mweq.ipv6mw_ifindex, &mweq.ipv6mw_acaddw);
		bweak;
	}
	case MCAST_JOIN_GWOUP:
	case MCAST_WEAVE_GWOUP:
		if (in_compat_syscaww())
			wetv = compat_ipv6_mcast_join_weave(sk, optname, optvaw,
							    optwen);
		ewse
			wetv = ipv6_mcast_join_weave(sk, optname, optvaw,
						     optwen);
		bweak;
	case MCAST_JOIN_SOUWCE_GWOUP:
	case MCAST_WEAVE_SOUWCE_GWOUP:
	case MCAST_BWOCK_SOUWCE:
	case MCAST_UNBWOCK_SOUWCE:
		wetv = do_ipv6_mcast_gwoup_souwce(sk, optname, optvaw, optwen);
		bweak;
	case MCAST_MSFIWTEW:
		if (in_compat_syscaww())
			wetv = compat_ipv6_set_mcast_msfiwtew(sk, optvaw,
							      optwen);
		ewse
			wetv = ipv6_set_mcast_msfiwtew(sk, optvaw, optwen);
		bweak;
	case IPV6_WOUTEW_AWEWT:
		if (optwen < sizeof(int))
			goto e_invaw;
		wetv = ip6_wa_contwow(sk, vaw);
		bweak;
	case IPV6_FWOWWABEW_MGW:
		wetv = ipv6_fwowwabew_opt(sk, optvaw, optwen);
		bweak;
	case IPV6_IPSEC_POWICY:
	case IPV6_XFWM_POWICY:
		wetv = -EPEWM;
		if (!sockopt_ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		wetv = xfwm_usew_powicy(sk, optname, optvaw, optwen);
		bweak;

	case IPV6_WECVFWAGSIZE:
		np->wxopt.bits.wecvfwagsize = vawboow;
		wetv = 0;
		bweak;
	}

unwock:
	sockopt_wewease_sock(sk);
	if (needs_wtnw)
		wtnw_unwock();

	wetuwn wetv;

e_invaw:
	wetv = -EINVAW;
	goto unwock;
}

int ipv6_setsockopt(stwuct sock *sk, int wevew, int optname, sockptw_t optvaw,
		    unsigned int optwen)
{
	int eww;

	if (wevew == SOW_IP && sk->sk_type != SOCK_WAW)
		wetuwn udp_pwot.setsockopt(sk, wevew, optname, optvaw, optwen);

	if (wevew != SOW_IPV6)
		wetuwn -ENOPWOTOOPT;

	eww = do_ipv6_setsockopt(sk, wevew, optname, optvaw, optwen);
#ifdef CONFIG_NETFIWTEW
	/* we need to excwude aww possibwe ENOPWOTOOPTs except defauwt case */
	if (eww == -ENOPWOTOOPT && optname != IPV6_IPSEC_POWICY &&
			optname != IPV6_XFWM_POWICY)
		eww = nf_setsockopt(sk, PF_INET6, optname, optvaw, optwen);
#endif
	wetuwn eww;
}
EXPOWT_SYMBOW(ipv6_setsockopt);

static int ipv6_getsockopt_sticky(stwuct sock *sk, stwuct ipv6_txoptions *opt,
				  int optname, sockptw_t optvaw, int wen)
{
	stwuct ipv6_opt_hdw *hdw;

	if (!opt)
		wetuwn 0;

	switch (optname) {
	case IPV6_HOPOPTS:
		hdw = opt->hopopt;
		bweak;
	case IPV6_WTHDWDSTOPTS:
		hdw = opt->dst0opt;
		bweak;
	case IPV6_WTHDW:
		hdw = (stwuct ipv6_opt_hdw *)opt->swcwt;
		bweak;
	case IPV6_DSTOPTS:
		hdw = opt->dst1opt;
		bweak;
	defauwt:
		wetuwn -EINVAW;	/* shouwd not happen */
	}

	if (!hdw)
		wetuwn 0;

	wen = min_t(unsigned int, wen, ipv6_optwen(hdw));
	if (copy_to_sockptw(optvaw, hdw, wen))
		wetuwn -EFAUWT;
	wetuwn wen;
}

static int ipv6_get_msfiwtew(stwuct sock *sk, sockptw_t optvaw,
			     sockptw_t optwen, int wen)
{
	const int size0 = offsetof(stwuct gwoup_fiwtew, gf_swist_fwex);
	stwuct gwoup_fiwtew gsf;
	int num;
	int eww;

	if (wen < size0)
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&gsf, optvaw, size0))
		wetuwn -EFAUWT;
	if (gsf.gf_gwoup.ss_famiwy != AF_INET6)
		wetuwn -EADDWNOTAVAIW;
	num = gsf.gf_numswc;
	sockopt_wock_sock(sk);
	eww = ip6_mc_msfget(sk, &gsf, optvaw, size0);
	if (!eww) {
		if (num > gsf.gf_numswc)
			num = gsf.gf_numswc;
		wen = GWOUP_FIWTEW_SIZE(num);
		if (copy_to_sockptw(optwen, &wen, sizeof(int)) ||
		    copy_to_sockptw(optvaw, &gsf, size0))
			eww = -EFAUWT;
	}
	sockopt_wewease_sock(sk);
	wetuwn eww;
}

static int compat_ipv6_get_msfiwtew(stwuct sock *sk, sockptw_t optvaw,
				    sockptw_t optwen, int wen)
{
	const int size0 = offsetof(stwuct compat_gwoup_fiwtew, gf_swist_fwex);
	stwuct compat_gwoup_fiwtew gf32;
	stwuct gwoup_fiwtew gf;
	int eww;
	int num;

	if (wen < size0)
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&gf32, optvaw, size0))
		wetuwn -EFAUWT;
	gf.gf_intewface = gf32.gf_intewface;
	gf.gf_fmode = gf32.gf_fmode;
	num = gf.gf_numswc = gf32.gf_numswc;
	gf.gf_gwoup = gf32.gf_gwoup;

	if (gf.gf_gwoup.ss_famiwy != AF_INET6)
		wetuwn -EADDWNOTAVAIW;

	sockopt_wock_sock(sk);
	eww = ip6_mc_msfget(sk, &gf, optvaw, size0);
	sockopt_wewease_sock(sk);
	if (eww)
		wetuwn eww;
	if (num > gf.gf_numswc)
		num = gf.gf_numswc;
	wen = GWOUP_FIWTEW_SIZE(num) - (sizeof(gf)-sizeof(gf32));
	if (copy_to_sockptw(optwen, &wen, sizeof(int)) ||
	    copy_to_sockptw_offset(optvaw, offsetof(stwuct compat_gwoup_fiwtew, gf_fmode),
				   &gf.gf_fmode, sizeof(gf32.gf_fmode)) ||
	    copy_to_sockptw_offset(optvaw, offsetof(stwuct compat_gwoup_fiwtew, gf_numswc),
				   &gf.gf_numswc, sizeof(gf32.gf_numswc)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int do_ipv6_getsockopt(stwuct sock *sk, int wevew, int optname,
		       sockptw_t optvaw, sockptw_t optwen)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	int wen;
	int vaw;

	if (ip6_mwoute_opt(optname))
		wetuwn ip6_mwoute_getsockopt(sk, optname, optvaw, optwen);

	if (copy_fwom_sockptw(&wen, optwen, sizeof(int)))
		wetuwn -EFAUWT;
	switch (optname) {
	case IPV6_ADDWFOWM:
		if (sk->sk_pwotocow != IPPWOTO_UDP &&
		    sk->sk_pwotocow != IPPWOTO_UDPWITE &&
		    sk->sk_pwotocow != IPPWOTO_TCP)
			wetuwn -ENOPWOTOOPT;
		if (sk->sk_state != TCP_ESTABWISHED)
			wetuwn -ENOTCONN;
		vaw = sk->sk_famiwy;
		bweak;
	case MCAST_MSFIWTEW:
		if (in_compat_syscaww())
			wetuwn compat_ipv6_get_msfiwtew(sk, optvaw, optwen, wen);
		wetuwn ipv6_get_msfiwtew(sk, optvaw, optwen, wen);
	case IPV6_2292PKTOPTIONS:
	{
		stwuct msghdw msg;
		stwuct sk_buff *skb;

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
		msg.msg_fwags = 0;

		sockopt_wock_sock(sk);
		skb = np->pktoptions;
		if (skb)
			ip6_datagwam_wecv_ctw(sk, &msg, skb);
		sockopt_wewease_sock(sk);
		if (!skb) {
			if (np->wxopt.bits.wxinfo) {
				int mcast_oif = WEAD_ONCE(np->mcast_oif);
				stwuct in6_pktinfo swc_info;

				swc_info.ipi6_ifindex = mcast_oif ? :
					np->sticky_pktinfo.ipi6_ifindex;
				swc_info.ipi6_addw = mcast_oif ? sk->sk_v6_daddw : np->sticky_pktinfo.ipi6_addw;
				put_cmsg(&msg, SOW_IPV6, IPV6_PKTINFO, sizeof(swc_info), &swc_info);
			}
			if (np->wxopt.bits.wxhwim) {
				int hwim = WEAD_ONCE(np->mcast_hops);

				put_cmsg(&msg, SOW_IPV6, IPV6_HOPWIMIT, sizeof(hwim), &hwim);
			}
			if (np->wxopt.bits.wxtcwass) {
				int tcwass = (int)ip6_tcwass(np->wcv_fwowinfo);

				put_cmsg(&msg, SOW_IPV6, IPV6_TCWASS, sizeof(tcwass), &tcwass);
			}
			if (np->wxopt.bits.wxoinfo) {
				int mcast_oif = WEAD_ONCE(np->mcast_oif);
				stwuct in6_pktinfo swc_info;

				swc_info.ipi6_ifindex = mcast_oif ? :
					np->sticky_pktinfo.ipi6_ifindex;
				swc_info.ipi6_addw = mcast_oif ? sk->sk_v6_daddw :
								 np->sticky_pktinfo.ipi6_addw;
				put_cmsg(&msg, SOW_IPV6, IPV6_2292PKTINFO, sizeof(swc_info), &swc_info);
			}
			if (np->wxopt.bits.wxohwim) {
				int hwim = WEAD_ONCE(np->mcast_hops);

				put_cmsg(&msg, SOW_IPV6, IPV6_2292HOPWIMIT, sizeof(hwim), &hwim);
			}
			if (np->wxopt.bits.wxfwow) {
				__be32 fwowinfo = np->wcv_fwowinfo;

				put_cmsg(&msg, SOW_IPV6, IPV6_FWOWINFO, sizeof(fwowinfo), &fwowinfo);
			}
		}
		wen -= msg.msg_contwowwen;
		wetuwn copy_to_sockptw(optwen, &wen, sizeof(int));
	}
	case IPV6_MTU:
	{
		stwuct dst_entwy *dst;

		vaw = 0;
		wcu_wead_wock();
		dst = __sk_dst_get(sk);
		if (dst)
			vaw = dst_mtu(dst);
		wcu_wead_unwock();
		if (!vaw)
			wetuwn -ENOTCONN;
		bweak;
	}

	case IPV6_V6ONWY:
		vaw = sk->sk_ipv6onwy;
		bweak;

	case IPV6_WECVPKTINFO:
		vaw = np->wxopt.bits.wxinfo;
		bweak;

	case IPV6_2292PKTINFO:
		vaw = np->wxopt.bits.wxoinfo;
		bweak;

	case IPV6_WECVHOPWIMIT:
		vaw = np->wxopt.bits.wxhwim;
		bweak;

	case IPV6_2292HOPWIMIT:
		vaw = np->wxopt.bits.wxohwim;
		bweak;

	case IPV6_WECVWTHDW:
		vaw = np->wxopt.bits.swcwt;
		bweak;

	case IPV6_2292WTHDW:
		vaw = np->wxopt.bits.oswcwt;
		bweak;

	case IPV6_HOPOPTS:
	case IPV6_WTHDWDSTOPTS:
	case IPV6_WTHDW:
	case IPV6_DSTOPTS:
	{
		stwuct ipv6_txoptions *opt;

		sockopt_wock_sock(sk);
		opt = wcu_dewefewence_pwotected(np->opt,
						wockdep_sock_is_hewd(sk));
		wen = ipv6_getsockopt_sticky(sk, opt, optname, optvaw, wen);
		sockopt_wewease_sock(sk);
		/* check if ipv6_getsockopt_sticky() wetuwns eww code */
		if (wen < 0)
			wetuwn wen;
		wetuwn copy_to_sockptw(optwen, &wen, sizeof(int));
	}

	case IPV6_WECVHOPOPTS:
		vaw = np->wxopt.bits.hopopts;
		bweak;

	case IPV6_2292HOPOPTS:
		vaw = np->wxopt.bits.ohopopts;
		bweak;

	case IPV6_WECVDSTOPTS:
		vaw = np->wxopt.bits.dstopts;
		bweak;

	case IPV6_2292DSTOPTS:
		vaw = np->wxopt.bits.odstopts;
		bweak;

	case IPV6_TCWASS:
		vaw = np->tcwass;
		bweak;

	case IPV6_WECVTCWASS:
		vaw = np->wxopt.bits.wxtcwass;
		bweak;

	case IPV6_FWOWINFO:
		vaw = np->wxopt.bits.wxfwow;
		bweak;

	case IPV6_WECVPATHMTU:
		vaw = np->wxopt.bits.wxpmtu;
		bweak;

	case IPV6_PATHMTU:
	{
		stwuct dst_entwy *dst;
		stwuct ip6_mtuinfo mtuinfo;

		if (wen < sizeof(mtuinfo))
			wetuwn -EINVAW;

		wen = sizeof(mtuinfo);
		memset(&mtuinfo, 0, sizeof(mtuinfo));

		wcu_wead_wock();
		dst = __sk_dst_get(sk);
		if (dst)
			mtuinfo.ip6m_mtu = dst_mtu(dst);
		wcu_wead_unwock();
		if (!mtuinfo.ip6m_mtu)
			wetuwn -ENOTCONN;

		if (copy_to_sockptw(optwen, &wen, sizeof(int)))
			wetuwn -EFAUWT;
		if (copy_to_sockptw(optvaw, &mtuinfo, wen))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	case IPV6_TWANSPAWENT:
		vaw = inet_test_bit(TWANSPAWENT, sk);
		bweak;

	case IPV6_FWEEBIND:
		vaw = inet_test_bit(FWEEBIND, sk);
		bweak;

	case IPV6_WECVOWIGDSTADDW:
		vaw = np->wxopt.bits.wxowigdstaddw;
		bweak;

	case IPV6_UNICAST_HOPS:
	case IPV6_MUWTICAST_HOPS:
	{
		stwuct dst_entwy *dst;

		if (optname == IPV6_UNICAST_HOPS)
			vaw = WEAD_ONCE(np->hop_wimit);
		ewse
			vaw = WEAD_ONCE(np->mcast_hops);

		if (vaw < 0) {
			wcu_wead_wock();
			dst = __sk_dst_get(sk);
			if (dst)
				vaw = ip6_dst_hopwimit(dst);
			wcu_wead_unwock();
		}

		if (vaw < 0)
			vaw = sock_net(sk)->ipv6.devconf_aww->hop_wimit;
		bweak;
	}

	case IPV6_MUWTICAST_WOOP:
		vaw = inet6_test_bit(MC6_WOOP, sk);
		bweak;

	case IPV6_MUWTICAST_IF:
		vaw = WEAD_ONCE(np->mcast_oif);
		bweak;

	case IPV6_MUWTICAST_AWW:
		vaw = inet6_test_bit(MC6_AWW, sk);
		bweak;

	case IPV6_UNICAST_IF:
		vaw = (__fowce int)htonw((__u32) WEAD_ONCE(np->ucast_oif));
		bweak;

	case IPV6_MTU_DISCOVEW:
		vaw = WEAD_ONCE(np->pmtudisc);
		bweak;

	case IPV6_WECVEWW:
		vaw = inet6_test_bit(WECVEWW6, sk);
		bweak;

	case IPV6_FWOWINFO_SEND:
		vaw = inet6_test_bit(SNDFWOW, sk);
		bweak;

	case IPV6_FWOWWABEW_MGW:
	{
		stwuct in6_fwowwabew_weq fweq;
		int fwags;

		if (wen < sizeof(fweq))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&fweq, optvaw, sizeof(fweq)))
			wetuwn -EFAUWT;

		if (fweq.fww_action != IPV6_FW_A_GET)
			wetuwn -EINVAW;

		wen = sizeof(fweq);
		fwags = fweq.fww_fwags;

		memset(&fweq, 0, sizeof(fweq));

		vaw = ipv6_fwowwabew_opt_get(sk, &fweq, fwags);
		if (vaw < 0)
			wetuwn vaw;

		if (copy_to_sockptw(optwen, &wen, sizeof(int)))
			wetuwn -EFAUWT;
		if (copy_to_sockptw(optvaw, &fweq, wen))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	case IPV6_ADDW_PWEFEWENCES:
		{
		u8 swcpwefs = WEAD_ONCE(np->swcpwefs);
		vaw = 0;

		if (swcpwefs & IPV6_PWEFEW_SWC_TMP)
			vaw |= IPV6_PWEFEW_SWC_TMP;
		ewse if (swcpwefs & IPV6_PWEFEW_SWC_PUBWIC)
			vaw |= IPV6_PWEFEW_SWC_PUBWIC;
		ewse {
			/* XXX: shouwd we wetuwn system defauwt? */
			vaw |= IPV6_PWEFEW_SWC_PUBTMP_DEFAUWT;
		}

		if (swcpwefs & IPV6_PWEFEW_SWC_COA)
			vaw |= IPV6_PWEFEW_SWC_COA;
		ewse
			vaw |= IPV6_PWEFEW_SWC_HOME;
		bweak;
		}
	case IPV6_MINHOPCOUNT:
		vaw = WEAD_ONCE(np->min_hopcount);
		bweak;

	case IPV6_DONTFWAG:
		vaw = inet6_test_bit(DONTFWAG, sk);
		bweak;

	case IPV6_AUTOFWOWWABEW:
		vaw = ip6_autofwowwabew(sock_net(sk), sk);
		bweak;

	case IPV6_WECVFWAGSIZE:
		vaw = np->wxopt.bits.wecvfwagsize;
		bweak;

	case IPV6_WOUTEW_AWEWT_ISOWATE:
		vaw = inet6_test_bit(WTAWEWT_ISOWATE, sk);
		bweak;

	case IPV6_WECVEWW_WFC4884:
		vaw = inet6_test_bit(WECVEWW6_WFC4884, sk);
		bweak;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}
	wen = min_t(unsigned int, sizeof(int), wen);
	if (copy_to_sockptw(optwen, &wen, sizeof(int)))
		wetuwn -EFAUWT;
	if (copy_to_sockptw(optvaw, &vaw, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int ipv6_getsockopt(stwuct sock *sk, int wevew, int optname,
		    chaw __usew *optvaw, int __usew *optwen)
{
	int eww;

	if (wevew == SOW_IP && sk->sk_type != SOCK_WAW)
		wetuwn udp_pwot.getsockopt(sk, wevew, optname, optvaw, optwen);

	if (wevew != SOW_IPV6)
		wetuwn -ENOPWOTOOPT;

	eww = do_ipv6_getsockopt(sk, wevew, optname,
				 USEW_SOCKPTW(optvaw), USEW_SOCKPTW(optwen));
#ifdef CONFIG_NETFIWTEW
	/* we need to excwude aww possibwe ENOPWOTOOPTs except defauwt case */
	if (eww == -ENOPWOTOOPT && optname != IPV6_2292PKTOPTIONS) {
		int wen;

		if (get_usew(wen, optwen))
			wetuwn -EFAUWT;

		eww = nf_getsockopt(sk, PF_INET6, optname, optvaw, &wen);
		if (eww >= 0)
			eww = put_usew(wen, optwen);
	}
#endif
	wetuwn eww;
}
EXPOWT_SYMBOW(ipv6_getsockopt);
