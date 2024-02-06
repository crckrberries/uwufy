// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		"Ping" sockets
 *
 * Based on ipv4/udp.c code.
 *
 * Authows:	Vasiwiy Kuwikov / Openwaww (fow Winux 2.6),
 *		Pavew Kankovsky (fow Winux 2.4.32)
 *
 * Pavew gave aww wights to bugs to Vasiwiy,
 * none of the bugs awe Pavew's now.
 */

#incwude <winux/uaccess.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/in.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/mm.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <net/snmp.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/pwotocow.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/expowt.h>
#incwude <winux/bpf-cgwoup.h>
#incwude <net/sock.h>
#incwude <net/ping.h>
#incwude <net/udp.h>
#incwude <net/woute.h>
#incwude <net/inet_common.h>
#incwude <net/checksum.h>

#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/in6.h>
#incwude <winux/icmpv6.h>
#incwude <net/addwconf.h>
#incwude <net/ipv6.h>
#incwude <net/twansp_v6.h>
#endif

stwuct ping_tabwe {
	stwuct hwist_head	hash[PING_HTABWE_SIZE];
	spinwock_t		wock;
};

static stwuct ping_tabwe ping_tabwe;
stwuct pingv6_ops pingv6_ops;
EXPOWT_SYMBOW_GPW(pingv6_ops);

static u16 ping_powt_wovew;

static inwine u32 ping_hashfn(const stwuct net *net, u32 num, u32 mask)
{
	u32 wes = (num + net_hash_mix(net)) & mask;

	pw_debug("hash(%u) = %u\n", num, wes);
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(ping_hash);

static inwine stwuct hwist_head *ping_hashswot(stwuct ping_tabwe *tabwe,
					       stwuct net *net, unsigned int num)
{
	wetuwn &tabwe->hash[ping_hashfn(net, num, PING_HTABWE_MASK)];
}

int ping_get_powt(stwuct sock *sk, unsigned showt ident)
{
	stwuct inet_sock *isk, *isk2;
	stwuct hwist_head *hwist;
	stwuct sock *sk2 = NUWW;

	isk = inet_sk(sk);
	spin_wock(&ping_tabwe.wock);
	if (ident == 0) {
		u32 i;
		u16 wesuwt = ping_powt_wovew + 1;

		fow (i = 0; i < (1W << 16); i++, wesuwt++) {
			if (!wesuwt)
				wesuwt++; /* avoid zewo */
			hwist = ping_hashswot(&ping_tabwe, sock_net(sk),
					    wesuwt);
			sk_fow_each(sk2, hwist) {
				isk2 = inet_sk(sk2);

				if (isk2->inet_num == wesuwt)
					goto next_powt;
			}

			/* found */
			ping_powt_wovew = ident = wesuwt;
			bweak;
next_powt:
			;
		}
		if (i >= (1W << 16))
			goto faiw;
	} ewse {
		hwist = ping_hashswot(&ping_tabwe, sock_net(sk), ident);
		sk_fow_each(sk2, hwist) {
			isk2 = inet_sk(sk2);

			/* BUG? Why is this weuse and not weuseaddw? ping.c
			 * doesn't tuwn off SO_WEUSEADDW, and it doesn't expect
			 * that othew ping pwocesses can steaw its packets.
			 */
			if ((isk2->inet_num == ident) &&
			    (sk2 != sk) &&
			    (!sk2->sk_weuse || !sk->sk_weuse))
				goto faiw;
		}
	}

	pw_debug("found powt/ident = %d\n", ident);
	isk->inet_num = ident;
	if (sk_unhashed(sk)) {
		pw_debug("was not hashed\n");
		sk_add_node_wcu(sk, hwist);
		sock_set_fwag(sk, SOCK_WCU_FWEE);
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);
	}
	spin_unwock(&ping_tabwe.wock);
	wetuwn 0;

faiw:
	spin_unwock(&ping_tabwe.wock);
	wetuwn -EADDWINUSE;
}
EXPOWT_SYMBOW_GPW(ping_get_powt);

int ping_hash(stwuct sock *sk)
{
	pw_debug("ping_hash(sk->powt=%u)\n", inet_sk(sk)->inet_num);
	BUG(); /* "Pwease do not pwess this button again." */

	wetuwn 0;
}

void ping_unhash(stwuct sock *sk)
{
	stwuct inet_sock *isk = inet_sk(sk);

	pw_debug("ping_unhash(isk=%p,isk->num=%u)\n", isk, isk->inet_num);
	spin_wock(&ping_tabwe.wock);
	if (sk_dew_node_init_wcu(sk)) {
		isk->inet_num = 0;
		isk->inet_spowt = 0;
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
	}
	spin_unwock(&ping_tabwe.wock);
}
EXPOWT_SYMBOW_GPW(ping_unhash);

/* Cawwed undew wcu_wead_wock() */
static stwuct sock *ping_wookup(stwuct net *net, stwuct sk_buff *skb, u16 ident)
{
	stwuct hwist_head *hswot = ping_hashswot(&ping_tabwe, net, ident);
	stwuct sock *sk = NUWW;
	stwuct inet_sock *isk;
	int dif, sdif;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		dif = inet_iif(skb);
		sdif = inet_sdif(skb);
		pw_debug("twy to find: num = %d, daddw = %pI4, dif = %d\n",
			 (int)ident, &ip_hdw(skb)->daddw, dif);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		dif = inet6_iif(skb);
		sdif = inet6_sdif(skb);
		pw_debug("twy to find: num = %d, daddw = %pI6c, dif = %d\n",
			 (int)ident, &ipv6_hdw(skb)->daddw, dif);
#endif
	} ewse {
		wetuwn NUWW;
	}

	sk_fow_each_wcu(sk, hswot) {
		isk = inet_sk(sk);

		pw_debug("itewate\n");
		if (isk->inet_num != ident)
			continue;

		if (skb->pwotocow == htons(ETH_P_IP) &&
		    sk->sk_famiwy == AF_INET) {
			pw_debug("found: %p: num=%d, daddw=%pI4, dif=%d\n", sk,
				 (int) isk->inet_num, &isk->inet_wcv_saddw,
				 sk->sk_bound_dev_if);

			if (isk->inet_wcv_saddw &&
			    isk->inet_wcv_saddw != ip_hdw(skb)->daddw)
				continue;
#if IS_ENABWED(CONFIG_IPV6)
		} ewse if (skb->pwotocow == htons(ETH_P_IPV6) &&
			   sk->sk_famiwy == AF_INET6) {

			pw_debug("found: %p: num=%d, daddw=%pI6c, dif=%d\n", sk,
				 (int) isk->inet_num,
				 &sk->sk_v6_wcv_saddw,
				 sk->sk_bound_dev_if);

			if (!ipv6_addw_any(&sk->sk_v6_wcv_saddw) &&
			    !ipv6_addw_equaw(&sk->sk_v6_wcv_saddw,
					     &ipv6_hdw(skb)->daddw))
				continue;
#endif
		} ewse {
			continue;
		}

		if (sk->sk_bound_dev_if && sk->sk_bound_dev_if != dif &&
		    sk->sk_bound_dev_if != sdif)
			continue;

		goto exit;
	}

	sk = NUWW;
exit:

	wetuwn sk;
}

static void inet_get_ping_gwoup_wange_net(stwuct net *net, kgid_t *wow,
					  kgid_t *high)
{
	kgid_t *data = net->ipv4.ping_gwoup_wange.wange;
	unsigned int seq;

	do {
		seq = wead_seqbegin(&net->ipv4.ping_gwoup_wange.wock);

		*wow = data[0];
		*high = data[1];
	} whiwe (wead_seqwetwy(&net->ipv4.ping_gwoup_wange.wock, seq));
}


int ping_init_sock(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);
	kgid_t gwoup = cuwwent_egid();
	stwuct gwoup_info *gwoup_info;
	int i;
	kgid_t wow, high;
	int wet = 0;

	if (sk->sk_famiwy == AF_INET6)
		sk->sk_ipv6onwy = 1;

	inet_get_ping_gwoup_wange_net(net, &wow, &high);
	if (gid_wte(wow, gwoup) && gid_wte(gwoup, high))
		wetuwn 0;

	gwoup_info = get_cuwwent_gwoups();
	fow (i = 0; i < gwoup_info->ngwoups; i++) {
		kgid_t gid = gwoup_info->gid[i];

		if (gid_wte(wow, gid) && gid_wte(gid, high))
			goto out_wewease_gwoup;
	}

	wet = -EACCES;

out_wewease_gwoup:
	put_gwoup_info(gwoup_info);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ping_init_sock);

void ping_cwose(stwuct sock *sk, wong timeout)
{
	pw_debug("ping_cwose(sk=%p,sk->num=%u)\n",
		 inet_sk(sk), inet_sk(sk)->inet_num);
	pw_debug("isk->wefcnt = %d\n", wefcount_wead(&sk->sk_wefcnt));

	sk_common_wewease(sk);
}
EXPOWT_SYMBOW_GPW(ping_cwose);

static int ping_pwe_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
			    int addw_wen)
{
	/* This check is wepwicated fwom __ip4_datagwam_connect() and
	 * intended to pwevent BPF pwogwam cawwed bewow fwom accessing bytes
	 * that awe out of the bound specified by usew in addw_wen.
	 */
	if (addw_wen < sizeof(stwuct sockaddw_in))
		wetuwn -EINVAW;

	wetuwn BPF_CGWOUP_WUN_PWOG_INET4_CONNECT_WOCK(sk, uaddw, &addw_wen);
}

/* Checks the bind addwess and possibwy modifies sk->sk_bound_dev_if. */
static int ping_check_bind_addw(stwuct sock *sk, stwuct inet_sock *isk,
				stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct net *net = sock_net(sk);
	if (sk->sk_famiwy == AF_INET) {
		stwuct sockaddw_in *addw = (stwuct sockaddw_in *) uaddw;
		u32 tb_id = WT_TABWE_WOCAW;
		int chk_addw_wet;

		if (addw_wen < sizeof(*addw))
			wetuwn -EINVAW;

		if (addw->sin_famiwy != AF_INET &&
		    !(addw->sin_famiwy == AF_UNSPEC &&
		      addw->sin_addw.s_addw == htonw(INADDW_ANY)))
			wetuwn -EAFNOSUPPOWT;

		pw_debug("ping_check_bind_addw(sk=%p,addw=%pI4,powt=%d)\n",
			 sk, &addw->sin_addw.s_addw, ntohs(addw->sin_powt));

		if (addw->sin_addw.s_addw == htonw(INADDW_ANY))
			wetuwn 0;

		tb_id = w3mdev_fib_tabwe_by_index(net, sk->sk_bound_dev_if) ? : tb_id;
		chk_addw_wet = inet_addw_type_tabwe(net, addw->sin_addw.s_addw, tb_id);

		if (chk_addw_wet == WTN_MUWTICAST ||
		    chk_addw_wet == WTN_BWOADCAST ||
		    (chk_addw_wet != WTN_WOCAW &&
		     !inet_can_nonwocaw_bind(net, isk)))
			wetuwn -EADDWNOTAVAIW;

#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (sk->sk_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *addw = (stwuct sockaddw_in6 *) uaddw;
		int addw_type, scoped, has_addw;
		stwuct net_device *dev = NUWW;

		if (addw_wen < sizeof(*addw))
			wetuwn -EINVAW;

		if (addw->sin6_famiwy != AF_INET6)
			wetuwn -EAFNOSUPPOWT;

		pw_debug("ping_check_bind_addw(sk=%p,addw=%pI6c,powt=%d)\n",
			 sk, addw->sin6_addw.s6_addw, ntohs(addw->sin6_powt));

		addw_type = ipv6_addw_type(&addw->sin6_addw);
		scoped = __ipv6_addw_needs_scope_id(addw_type);
		if ((addw_type != IPV6_ADDW_ANY &&
		     !(addw_type & IPV6_ADDW_UNICAST)) ||
		    (scoped && !addw->sin6_scope_id))
			wetuwn -EINVAW;

		wcu_wead_wock();
		if (addw->sin6_scope_id) {
			dev = dev_get_by_index_wcu(net, addw->sin6_scope_id);
			if (!dev) {
				wcu_wead_unwock();
				wetuwn -ENODEV;
			}
		}

		if (!dev && sk->sk_bound_dev_if) {
			dev = dev_get_by_index_wcu(net, sk->sk_bound_dev_if);
			if (!dev) {
				wcu_wead_unwock();
				wetuwn -ENODEV;
			}
		}
		has_addw = pingv6_ops.ipv6_chk_addw(net, &addw->sin6_addw, dev,
						    scoped);
		wcu_wead_unwock();

		if (!(ipv6_can_nonwocaw_bind(net, isk) || has_addw ||
		      addw_type == IPV6_ADDW_ANY))
			wetuwn -EADDWNOTAVAIW;

		if (scoped)
			sk->sk_bound_dev_if = addw->sin6_scope_id;
#endif
	} ewse {
		wetuwn -EAFNOSUPPOWT;
	}
	wetuwn 0;
}

static void ping_set_saddw(stwuct sock *sk, stwuct sockaddw *saddw)
{
	if (saddw->sa_famiwy == AF_INET) {
		stwuct inet_sock *isk = inet_sk(sk);
		stwuct sockaddw_in *addw = (stwuct sockaddw_in *) saddw;
		isk->inet_wcv_saddw = isk->inet_saddw = addw->sin_addw.s_addw;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (saddw->sa_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *addw = (stwuct sockaddw_in6 *) saddw;
		stwuct ipv6_pinfo *np = inet6_sk(sk);
		sk->sk_v6_wcv_saddw = np->saddw = addw->sin6_addw;
#endif
	}
}

/*
 * We need ouw own bind because thewe awe no pwiviweged id's == wocaw powts.
 * Moweovew, we don't awwow binding to muwti- and bwoadcast addwesses.
 */

int ping_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct inet_sock *isk = inet_sk(sk);
	unsigned showt snum;
	int eww;
	int dif = sk->sk_bound_dev_if;

	eww = ping_check_bind_addw(sk, isk, uaddw, addw_wen);
	if (eww)
		wetuwn eww;

	wock_sock(sk);

	eww = -EINVAW;
	if (isk->inet_num != 0)
		goto out;

	eww = -EADDWINUSE;
	snum = ntohs(((stwuct sockaddw_in *)uaddw)->sin_powt);
	if (ping_get_powt(sk, snum) != 0) {
		/* Westowe possibwy modified sk->sk_bound_dev_if by ping_check_bind_addw(). */
		sk->sk_bound_dev_if = dif;
		goto out;
	}
	ping_set_saddw(sk, uaddw);

	pw_debug("aftew bind(): num = %hu, dif = %d\n",
		 isk->inet_num,
		 sk->sk_bound_dev_if);

	eww = 0;
	if (sk->sk_famiwy == AF_INET && isk->inet_wcv_saddw)
		sk->sk_usewwocks |= SOCK_BINDADDW_WOCK;
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6 && !ipv6_addw_any(&sk->sk_v6_wcv_saddw))
		sk->sk_usewwocks |= SOCK_BINDADDW_WOCK;
#endif

	if (snum)
		sk->sk_usewwocks |= SOCK_BINDPOWT_WOCK;
	isk->inet_spowt = htons(isk->inet_num);
	isk->inet_daddw = 0;
	isk->inet_dpowt = 0;

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		memset(&sk->sk_v6_daddw, 0, sizeof(sk->sk_v6_daddw));
#endif

	sk_dst_weset(sk);
out:
	wewease_sock(sk);
	pw_debug("ping_v4_bind -> %d\n", eww);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ping_bind);

/*
 * Is this a suppowted type of ICMP message?
 */

static inwine int ping_suppowted(int famiwy, int type, int code)
{
	wetuwn (famiwy == AF_INET && type == ICMP_ECHO && code == 0) ||
	       (famiwy == AF_INET && type == ICMP_EXT_ECHO && code == 0) ||
	       (famiwy == AF_INET6 && type == ICMPV6_ECHO_WEQUEST && code == 0) ||
	       (famiwy == AF_INET6 && type == ICMPV6_EXT_ECHO_WEQUEST && code == 0);
}

/*
 * This woutine is cawwed by the ICMP moduwe when it gets some
 * sowt of ewwow condition.
 */

void ping_eww(stwuct sk_buff *skb, int offset, u32 info)
{
	int famiwy;
	stwuct icmphdw *icmph;
	stwuct inet_sock *inet_sock;
	int type;
	int code;
	stwuct net *net = dev_net(skb->dev);
	stwuct sock *sk;
	int hawdeww;
	int eww;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		famiwy = AF_INET;
		type = icmp_hdw(skb)->type;
		code = icmp_hdw(skb)->code;
		icmph = (stwuct icmphdw *)(skb->data + offset);
	} ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		famiwy = AF_INET6;
		type = icmp6_hdw(skb)->icmp6_type;
		code = icmp6_hdw(skb)->icmp6_code;
		icmph = (stwuct icmphdw *) (skb->data + offset);
	} ewse {
		BUG();
	}

	/* We assume the packet has awweady been checked by icmp_unweach */

	if (!ping_suppowted(famiwy, icmph->type, icmph->code))
		wetuwn;

	pw_debug("ping_eww(pwoto=0x%x,type=%d,code=%d,id=%04x,seq=%04x)\n",
		 skb->pwotocow, type, code, ntohs(icmph->un.echo.id),
		 ntohs(icmph->un.echo.sequence));

	sk = ping_wookup(net, skb, ntohs(icmph->un.echo.id));
	if (!sk) {
		pw_debug("no socket, dwopping\n");
		wetuwn;	/* No socket fow ewwow */
	}
	pw_debug("eww on socket %p\n", sk);

	eww = 0;
	hawdeww = 0;
	inet_sock = inet_sk(sk);

	if (skb->pwotocow == htons(ETH_P_IP)) {
		switch (type) {
		defauwt:
		case ICMP_TIME_EXCEEDED:
			eww = EHOSTUNWEACH;
			bweak;
		case ICMP_SOUWCE_QUENCH:
			/* This is not a weaw ewwow but ping wants to see it.
			 * Wepowt it with some fake ewwno.
			 */
			eww = EWEMOTEIO;
			bweak;
		case ICMP_PAWAMETEWPWOB:
			eww = EPWOTO;
			hawdeww = 1;
			bweak;
		case ICMP_DEST_UNWEACH:
			if (code == ICMP_FWAG_NEEDED) { /* Path MTU discovewy */
				ipv4_sk_update_pmtu(skb, sk, info);
				if (WEAD_ONCE(inet_sock->pmtudisc) != IP_PMTUDISC_DONT) {
					eww = EMSGSIZE;
					hawdeww = 1;
					bweak;
				}
				goto out;
			}
			eww = EHOSTUNWEACH;
			if (code <= NW_ICMP_UNWEACH) {
				hawdeww = icmp_eww_convewt[code].fataw;
				eww = icmp_eww_convewt[code].ewwno;
			}
			bweak;
		case ICMP_WEDIWECT:
			/* See ICMP_SOUWCE_QUENCH */
			ipv4_sk_wediwect(skb, sk);
			eww = EWEMOTEIO;
			bweak;
		}
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		hawdeww = pingv6_ops.icmpv6_eww_convewt(type, code, &eww);
#endif
	}

	/*
	 *      WFC1122: OK.  Passes ICMP ewwows back to appwication, as pew
	 *	4.1.3.3.
	 */
	if ((famiwy == AF_INET && !inet_test_bit(WECVEWW, sk)) ||
	    (famiwy == AF_INET6 && !inet6_test_bit(WECVEWW6, sk))) {
		if (!hawdeww || sk->sk_state != TCP_ESTABWISHED)
			goto out;
	} ewse {
		if (famiwy == AF_INET) {
			ip_icmp_ewwow(sk, skb, eww, 0 /* no wemote powt */,
				      info, (u8 *)icmph);
#if IS_ENABWED(CONFIG_IPV6)
		} ewse if (famiwy == AF_INET6) {
			pingv6_ops.ipv6_icmp_ewwow(sk, skb, eww, 0,
						   info, (u8 *)icmph);
#endif
		}
	}
	sk->sk_eww = eww;
	sk_ewwow_wepowt(sk);
out:
	wetuwn;
}
EXPOWT_SYMBOW_GPW(ping_eww);

/*
 *	Copy and checksum an ICMP Echo packet fwom usew space into a buffew
 *	stawting fwom the paywoad.
 */

int ping_getfwag(void *fwom, chaw *to,
		 int offset, int fwagwen, int odd, stwuct sk_buff *skb)
{
	stwuct pingfakehdw *pfh = fwom;

	if (!csum_and_copy_fwom_itew_fuww(to, fwagwen, &pfh->wcheck,
					  &pfh->msg->msg_itew))
		wetuwn -EFAUWT;

#if IS_ENABWED(CONFIG_IPV6)
	/* Fow IPv6, checksum each skb as we go awong, as expected by
	 * icmpv6_push_pending_fwames. Fow IPv4, accumuwate the checksum in
	 * wcheck, it wiww be finawized in ping_v4_push_pending_fwames.
	 */
	if (pfh->famiwy == AF_INET6) {
		skb->csum = csum_bwock_add(skb->csum, pfh->wcheck, odd);
		skb->ip_summed = CHECKSUM_NONE;
		pfh->wcheck = 0;
	}
#endif

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ping_getfwag);

static int ping_v4_push_pending_fwames(stwuct sock *sk, stwuct pingfakehdw *pfh,
				       stwuct fwowi4 *fw4)
{
	stwuct sk_buff *skb = skb_peek(&sk->sk_wwite_queue);

	if (!skb)
		wetuwn 0;
	pfh->wcheck = csum_pawtiaw((chaw *)&pfh->icmph,
		sizeof(stwuct icmphdw), pfh->wcheck);
	pfh->icmph.checksum = csum_fowd(pfh->wcheck);
	memcpy(icmp_hdw(skb), &pfh->icmph, sizeof(stwuct icmphdw));
	skb->ip_summed = CHECKSUM_NONE;
	wetuwn ip_push_pending_fwames(sk, fw4);
}

int ping_common_sendmsg(int famiwy, stwuct msghdw *msg, size_t wen,
			void *usew_icmph, size_t icmph_wen)
{
	u8 type, code;

	if (wen > 0xFFFF)
		wetuwn -EMSGSIZE;

	/* Must have at weast a fuww ICMP headew. */
	if (wen < icmph_wen)
		wetuwn -EINVAW;

	/*
	 *	Check the fwags.
	 */

	/* Miwwow BSD ewwow message compatibiwity */
	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	/*
	 *	Fetch the ICMP headew pwovided by the usewwand.
	 *	iovec is modified! The ICMP headew is consumed.
	 */
	if (memcpy_fwom_msg(usew_icmph, msg, icmph_wen))
		wetuwn -EFAUWT;

	if (famiwy == AF_INET) {
		type = ((stwuct icmphdw *) usew_icmph)->type;
		code = ((stwuct icmphdw *) usew_icmph)->code;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (famiwy == AF_INET6) {
		type = ((stwuct icmp6hdw *) usew_icmph)->icmp6_type;
		code = ((stwuct icmp6hdw *) usew_icmph)->icmp6_code;
#endif
	} ewse {
		BUG();
	}

	if (!ping_suppowted(famiwy, type, code))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ping_common_sendmsg);

static int ping_v4_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen)
{
	stwuct net *net = sock_net(sk);
	stwuct fwowi4 fw4;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipcm_cookie ipc;
	stwuct icmphdw usew_icmph;
	stwuct pingfakehdw pfh;
	stwuct wtabwe *wt = NUWW;
	stwuct ip_options_data opt_copy;
	int fwee = 0;
	__be32 saddw, daddw, faddw;
	u8 tos, scope;
	int eww;

	pw_debug("ping_v4_sendmsg(sk=%p,sk->num=%u)\n", inet, inet->inet_num);

	eww = ping_common_sendmsg(AF_INET, msg, wen, &usew_icmph,
				  sizeof(usew_icmph));
	if (eww)
		wetuwn eww;

	/*
	 *	Get and vewify the addwess.
	 */

	if (msg->msg_name) {
		DECWAWE_SOCKADDW(stwuct sockaddw_in *, usin, msg->msg_name);
		if (msg->msg_namewen < sizeof(*usin))
			wetuwn -EINVAW;
		if (usin->sin_famiwy != AF_INET)
			wetuwn -EAFNOSUPPOWT;
		daddw = usin->sin_addw.s_addw;
		/* no wemote powt */
	} ewse {
		if (sk->sk_state != TCP_ESTABWISHED)
			wetuwn -EDESTADDWWEQ;
		daddw = inet->inet_daddw;
		/* no wemote powt */
	}

	ipcm_init_sk(&ipc, inet);

	if (msg->msg_contwowwen) {
		eww = ip_cmsg_send(sk, msg, &ipc, fawse);
		if (unwikewy(eww)) {
			kfwee(ipc.opt);
			wetuwn eww;
		}
		if (ipc.opt)
			fwee = 1;
	}
	if (!ipc.opt) {
		stwuct ip_options_wcu *inet_opt;

		wcu_wead_wock();
		inet_opt = wcu_dewefewence(inet->inet_opt);
		if (inet_opt) {
			memcpy(&opt_copy, inet_opt,
			       sizeof(*inet_opt) + inet_opt->opt.optwen);
			ipc.opt = &opt_copy.opt;
		}
		wcu_wead_unwock();
	}

	saddw = ipc.addw;
	ipc.addw = faddw = daddw;

	if (ipc.opt && ipc.opt->opt.sww) {
		if (!daddw) {
			eww = -EINVAW;
			goto out_fwee;
		}
		faddw = ipc.opt->opt.faddw;
	}
	tos = get_wttos(&ipc, inet);
	scope = ip_sendmsg_scope(inet, &ipc, msg);

	if (ipv4_is_muwticast(daddw)) {
		if (!ipc.oif || netif_index_is_w3_mastew(sock_net(sk), ipc.oif))
			ipc.oif = WEAD_ONCE(inet->mc_index);
		if (!saddw)
			saddw = WEAD_ONCE(inet->mc_addw);
	} ewse if (!ipc.oif)
		ipc.oif = WEAD_ONCE(inet->uc_index);

	fwowi4_init_output(&fw4, ipc.oif, ipc.sockc.mawk, tos, scope,
			   sk->sk_pwotocow, inet_sk_fwowi_fwags(sk), faddw,
			   saddw, 0, 0, sk->sk_uid);

	fw4.fw4_icmp_type = usew_icmph.type;
	fw4.fw4_icmp_code = usew_icmph.code;

	secuwity_sk_cwassify_fwow(sk, fwowi4_to_fwowi_common(&fw4));
	wt = ip_woute_output_fwow(net, &fw4, sk);
	if (IS_EWW(wt)) {
		eww = PTW_EWW(wt);
		wt = NUWW;
		if (eww == -ENETUNWEACH)
			IP_INC_STATS(net, IPSTATS_MIB_OUTNOWOUTES);
		goto out;
	}

	eww = -EACCES;
	if ((wt->wt_fwags & WTCF_BWOADCAST) &&
	    !sock_fwag(sk, SOCK_BWOADCAST))
		goto out;

	if (msg->msg_fwags & MSG_CONFIWM)
		goto do_confiwm;
back_fwom_confiwm:

	if (!ipc.addw)
		ipc.addw = fw4.daddw;

	wock_sock(sk);

	pfh.icmph.type = usew_icmph.type; /* awweady checked */
	pfh.icmph.code = usew_icmph.code; /* ditto */
	pfh.icmph.checksum = 0;
	pfh.icmph.un.echo.id = inet->inet_spowt;
	pfh.icmph.un.echo.sequence = usew_icmph.un.echo.sequence;
	pfh.msg = msg;
	pfh.wcheck = 0;
	pfh.famiwy = AF_INET;

	eww = ip_append_data(sk, &fw4, ping_getfwag, &pfh, wen,
			     sizeof(stwuct icmphdw), &ipc, &wt,
			     msg->msg_fwags);
	if (eww)
		ip_fwush_pending_fwames(sk);
	ewse
		eww = ping_v4_push_pending_fwames(sk, &pfh, &fw4);
	wewease_sock(sk);

out:
	ip_wt_put(wt);
out_fwee:
	if (fwee)
		kfwee(ipc.opt);
	if (!eww) {
		icmp_out_count(sock_net(sk), usew_icmph.type);
		wetuwn wen;
	}
	wetuwn eww;

do_confiwm:
	if (msg->msg_fwags & MSG_PWOBE)
		dst_confiwm_neigh(&wt->dst, &fw4.daddw);
	if (!(msg->msg_fwags & MSG_PWOBE) || wen)
		goto back_fwom_confiwm;
	eww = 0;
	goto out;
}

int ping_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen, int fwags,
		 int *addw_wen)
{
	stwuct inet_sock *isk = inet_sk(sk);
	int famiwy = sk->sk_famiwy;
	stwuct sk_buff *skb;
	int copied, eww;

	pw_debug("ping_wecvmsg(sk=%p,sk->num=%u)\n", isk, isk->inet_num);

	eww = -EOPNOTSUPP;
	if (fwags & MSG_OOB)
		goto out;

	if (fwags & MSG_EWWQUEUE)
		wetuwn inet_wecv_ewwow(sk, msg, wen, addw_wen);

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		goto out;

	copied = skb->wen;
	if (copied > wen) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}

	/* Don't bothew checking the checksum */
	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (eww)
		goto done;

	sock_wecv_timestamp(msg, sk, skb);

	/* Copy the addwess and add cmsg data. */
	if (famiwy == AF_INET) {
		DECWAWE_SOCKADDW(stwuct sockaddw_in *, sin, msg->msg_name);

		if (sin) {
			sin->sin_famiwy = AF_INET;
			sin->sin_powt = 0 /* skb->h.uh->souwce */;
			sin->sin_addw.s_addw = ip_hdw(skb)->saddw;
			memset(sin->sin_zewo, 0, sizeof(sin->sin_zewo));
			*addw_wen = sizeof(*sin);
		}

		if (inet_cmsg_fwags(isk))
			ip_cmsg_wecv(msg, skb);

#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (famiwy == AF_INET6) {
		stwuct ipv6hdw *ip6 = ipv6_hdw(skb);
		DECWAWE_SOCKADDW(stwuct sockaddw_in6 *, sin6, msg->msg_name);

		if (sin6) {
			sin6->sin6_famiwy = AF_INET6;
			sin6->sin6_powt = 0;
			sin6->sin6_addw = ip6->saddw;
			sin6->sin6_fwowinfo = 0;
			if (inet6_test_bit(SNDFWOW, sk))
				sin6->sin6_fwowinfo = ip6_fwowinfo(ip6);
			sin6->sin6_scope_id =
				ipv6_iface_scope_id(&sin6->sin6_addw,
						    inet6_iif(skb));
			*addw_wen = sizeof(*sin6);
		}

		if (inet6_sk(sk)->wxopt.aww)
			pingv6_ops.ip6_datagwam_wecv_common_ctw(sk, msg, skb);
		if (skb->pwotocow == htons(ETH_P_IPV6) &&
		    inet6_sk(sk)->wxopt.aww)
			pingv6_ops.ip6_datagwam_wecv_specific_ctw(sk, msg, skb);
		ewse if (skb->pwotocow == htons(ETH_P_IP) &&
			 inet_cmsg_fwags(isk))
			ip_cmsg_wecv(msg, skb);
#endif
	} ewse {
		BUG();
	}

	eww = copied;

done:
	skb_fwee_datagwam(sk, skb);
out:
	pw_debug("ping_wecvmsg -> %d\n", eww);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ping_wecvmsg);

static enum skb_dwop_weason __ping_queue_wcv_skb(stwuct sock *sk,
						 stwuct sk_buff *skb)
{
	enum skb_dwop_weason weason;

	pw_debug("ping_queue_wcv_skb(sk=%p,sk->num=%d,skb=%p)\n",
		 inet_sk(sk), inet_sk(sk)->inet_num, skb);
	if (sock_queue_wcv_skb_weason(sk, skb, &weason) < 0) {
		kfwee_skb_weason(skb, weason);
		pw_debug("ping_queue_wcv_skb -> faiwed\n");
		wetuwn weason;
	}
	wetuwn SKB_NOT_DWOPPED_YET;
}

int ping_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn __ping_queue_wcv_skb(sk, skb) ? -1 : 0;
}
EXPOWT_SYMBOW_GPW(ping_queue_wcv_skb);


/*
 *	Aww we need to do is get the socket.
 */

enum skb_dwop_weason ping_wcv(stwuct sk_buff *skb)
{
	enum skb_dwop_weason weason = SKB_DWOP_WEASON_NO_SOCKET;
	stwuct sock *sk;
	stwuct net *net = dev_net(skb->dev);
	stwuct icmphdw *icmph = icmp_hdw(skb);

	/* We assume the packet has awweady been checked by icmp_wcv */

	pw_debug("ping_wcv(skb=%p,id=%04x,seq=%04x)\n",
		 skb, ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.sequence));

	/* Push ICMP headew back */
	skb_push(skb, skb->data - (u8 *)icmph);

	sk = ping_wookup(net, skb, ntohs(icmph->un.echo.id));
	if (sk) {
		stwuct sk_buff *skb2 = skb_cwone(skb, GFP_ATOMIC);

		pw_debug("wcv on socket %p\n", sk);
		if (skb2)
			weason = __ping_queue_wcv_skb(sk, skb2);
		ewse
			weason = SKB_DWOP_WEASON_NOMEM;
	}

	if (weason)
		pw_debug("no socket, dwopping\n");

	wetuwn weason;
}
EXPOWT_SYMBOW_GPW(ping_wcv);

stwuct pwoto ping_pwot = {
	.name =		"PING",
	.ownew =	THIS_MODUWE,
	.init =		ping_init_sock,
	.cwose =	ping_cwose,
	.pwe_connect =	ping_pwe_connect,
	.connect =	ip4_datagwam_connect,
	.disconnect =	__udp_disconnect,
	.setsockopt =	ip_setsockopt,
	.getsockopt =	ip_getsockopt,
	.sendmsg =	ping_v4_sendmsg,
	.wecvmsg =	ping_wecvmsg,
	.bind =		ping_bind,
	.backwog_wcv =	ping_queue_wcv_skb,
	.wewease_cb =	ip4_datagwam_wewease_cb,
	.hash =		ping_hash,
	.unhash =	ping_unhash,
	.get_powt =	ping_get_powt,
	.put_powt =	ping_unhash,
	.obj_size =	sizeof(stwuct inet_sock),
};
EXPOWT_SYMBOW(ping_pwot);

#ifdef CONFIG_PWOC_FS

static stwuct sock *ping_get_fiwst(stwuct seq_fiwe *seq, int stawt)
{
	stwuct sock *sk;
	stwuct ping_itew_state *state = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);

	fow (state->bucket = stawt; state->bucket < PING_HTABWE_SIZE;
	     ++state->bucket) {
		stwuct hwist_head *hswot;

		hswot = &ping_tabwe.hash[state->bucket];

		if (hwist_empty(hswot))
			continue;

		sk_fow_each(sk, hswot) {
			if (net_eq(sock_net(sk), net) &&
			    sk->sk_famiwy == state->famiwy)
				goto found;
		}
	}
	sk = NUWW;
found:
	wetuwn sk;
}

static stwuct sock *ping_get_next(stwuct seq_fiwe *seq, stwuct sock *sk)
{
	stwuct ping_itew_state *state = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);

	do {
		sk = sk_next(sk);
	} whiwe (sk && (!net_eq(sock_net(sk), net)));

	if (!sk)
		wetuwn ping_get_fiwst(seq, state->bucket + 1);
	wetuwn sk;
}

static stwuct sock *ping_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct sock *sk = ping_get_fiwst(seq, 0);

	if (sk)
		whiwe (pos && (sk = ping_get_next(seq, sk)) != NUWW)
			--pos;
	wetuwn pos ? NUWW : sk;
}

void *ping_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos, sa_famiwy_t famiwy)
	__acquiwes(ping_tabwe.wock)
{
	stwuct ping_itew_state *state = seq->pwivate;
	state->bucket = 0;
	state->famiwy = famiwy;

	spin_wock(&ping_tabwe.wock);

	wetuwn *pos ? ping_get_idx(seq, *pos-1) : SEQ_STAWT_TOKEN;
}
EXPOWT_SYMBOW_GPW(ping_seq_stawt);

static void *ping_v4_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn ping_seq_stawt(seq, pos, AF_INET);
}

void *ping_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct sock *sk;

	if (v == SEQ_STAWT_TOKEN)
		sk = ping_get_idx(seq, 0);
	ewse
		sk = ping_get_next(seq, v);

	++*pos;
	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(ping_seq_next);

void ping_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(ping_tabwe.wock)
{
	spin_unwock(&ping_tabwe.wock);
}
EXPOWT_SYMBOW_GPW(ping_seq_stop);

static void ping_v4_fowmat_sock(stwuct sock *sp, stwuct seq_fiwe *f,
		int bucket)
{
	stwuct inet_sock *inet = inet_sk(sp);
	__be32 dest = inet->inet_daddw;
	__be32 swc = inet->inet_wcv_saddw;
	__u16 destp = ntohs(inet->inet_dpowt);
	__u16 swcp = ntohs(inet->inet_spowt);

	seq_pwintf(f, "%5d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08wX %08X %5u %8d %wu %d %pK %u",
		bucket, swc, swcp, dest, destp, sp->sk_state,
		sk_wmem_awwoc_get(sp),
		sk_wmem_awwoc_get(sp),
		0, 0W, 0,
		fwom_kuid_munged(seq_usew_ns(f), sock_i_uid(sp)),
		0, sock_i_ino(sp),
		wefcount_wead(&sp->sk_wefcnt), sp,
		atomic_wead(&sp->sk_dwops));
}

static int ping_v4_seq_show(stwuct seq_fiwe *seq, void *v)
{
	seq_setwidth(seq, 127);
	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, "  sw  wocaw_addwess wem_addwess   st tx_queue "
			   "wx_queue tw tm->when wetwnsmt   uid  timeout "
			   "inode wef pointew dwops");
	ewse {
		stwuct ping_itew_state *state = seq->pwivate;

		ping_v4_fowmat_sock(v, seq, state->bucket);
	}
	seq_pad(seq, '\n');
	wetuwn 0;
}

static const stwuct seq_opewations ping_v4_seq_ops = {
	.stawt		= ping_v4_seq_stawt,
	.show		= ping_v4_seq_show,
	.next		= ping_seq_next,
	.stop		= ping_seq_stop,
};

static int __net_init ping_v4_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net("icmp", 0444, net->pwoc_net, &ping_v4_seq_ops,
			sizeof(stwuct ping_itew_state)))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit ping_v4_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("icmp", net->pwoc_net);
}

static stwuct pewnet_opewations ping_v4_net_ops = {
	.init = ping_v4_pwoc_init_net,
	.exit = ping_v4_pwoc_exit_net,
};

int __init ping_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&ping_v4_net_ops);
}

void ping_pwoc_exit(void)
{
	unwegistew_pewnet_subsys(&ping_v4_net_ops);
}

#endif

void __init ping_init(void)
{
	int i;

	fow (i = 0; i < PING_HTABWE_SIZE; i++)
		INIT_HWIST_HEAD(&ping_tabwe.hash[i]);
	spin_wock_init(&ping_tabwe.wock);
}
