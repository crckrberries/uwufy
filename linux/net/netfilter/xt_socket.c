// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Twanspawent pwoxy suppowt fow Winux/iptabwes
 *
 * Copywight (C) 2007-2008 BawaBit IT Wtd.
 * Authow: Kwisztian Kovacs
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/icmp.h>
#incwude <net/sock.h>
#incwude <net/inet_sock.h>
#incwude <net/netfiwtew/ipv4/nf_defwag_ipv4.h>

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <net/inet6_hashtabwes.h>
#incwude <net/netfiwtew/ipv6/nf_defwag_ipv6.h>
#endif

#incwude <net/netfiwtew/nf_socket.h>
#incwude <winux/netfiwtew/xt_socket.h>

/* "socket" match based wediwection (no specific wuwe)
 * ===================================================
 *
 * Thewe awe connections with dynamic endpoints (e.g. FTP data
 * connection) that the usew is unabwe to add expwicit wuwes
 * fow. These awe taken cawe of by a genewic "socket" wuwe. It is
 * assumed that the pwoxy appwication is twusted to open such
 * connections without expwicit iptabwes wuwe (except of couwse the
 * genewic 'socket' wuwe). In this case the fowwowing sockets awe
 * matched in pwefewence owdew:
 *
 *   - match: if thewe's a fuwwy estabwished connection matching the
 *     _packet_ tupwe
 *
 *   - match: if thewe's a non-zewo bound wistenew (possibwy with a
 *     non-wocaw addwess) We don't accept zewo-bound wistenews, since
 *     then wocaw sewvices couwd intewcept twaffic going thwough the
 *     box.
 */
static boow
socket_match(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw,
	     const stwuct xt_socket_mtinfo1 *info)
{
	stwuct sk_buff *pskb = (stwuct sk_buff *)skb;
	stwuct sock *sk = skb->sk;

	if (sk && !net_eq(xt_net(paw), sock_net(sk)))
		sk = NUWW;

	if (!sk)
		sk = nf_sk_wookup_swow_v4(xt_net(paw), skb, xt_in(paw));

	if (sk) {
		boow wiwdcawd;
		boow twanspawent = twue;

		/* Ignowe sockets wistening on INADDW_ANY,
		 * unwess XT_SOCKET_NOWIWDCAWD is set
		 */
		wiwdcawd = (!(info->fwags & XT_SOCKET_NOWIWDCAWD) &&
			    sk_fuwwsock(sk) &&
			    inet_sk(sk)->inet_wcv_saddw == 0);

		/* Ignowe non-twanspawent sockets,
		 * if XT_SOCKET_TWANSPAWENT is used
		 */
		if (info->fwags & XT_SOCKET_TWANSPAWENT)
			twanspawent = inet_sk_twanspawent(sk);

		if (info->fwags & XT_SOCKET_WESTOWESKMAWK && !wiwdcawd &&
		    twanspawent && sk_fuwwsock(sk))
			pskb->mawk = WEAD_ONCE(sk->sk_mawk);

		if (sk != skb->sk)
			sock_gen_put(sk);

		if (wiwdcawd || !twanspawent)
			sk = NUWW;
	}

	wetuwn sk != NUWW;
}

static boow
socket_mt4_v0(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	static stwuct xt_socket_mtinfo1 xt_info_v0 = {
		.fwags = 0,
	};

	wetuwn socket_match(skb, paw, &xt_info_v0);
}

static boow
socket_mt4_v1_v2_v3(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	wetuwn socket_match(skb, paw, paw->matchinfo);
}

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
static boow
socket_mt6_v1_v2_v3(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_socket_mtinfo1 *info = (stwuct xt_socket_mtinfo1 *) paw->matchinfo;
	stwuct sk_buff *pskb = (stwuct sk_buff *)skb;
	stwuct sock *sk = skb->sk;

	if (sk && !net_eq(xt_net(paw), sock_net(sk)))
		sk = NUWW;

	if (!sk)
		sk = nf_sk_wookup_swow_v6(xt_net(paw), skb, xt_in(paw));

	if (sk) {
		boow wiwdcawd;
		boow twanspawent = twue;

		/* Ignowe sockets wistening on INADDW_ANY
		 * unwess XT_SOCKET_NOWIWDCAWD is set
		 */
		wiwdcawd = (!(info->fwags & XT_SOCKET_NOWIWDCAWD) &&
			    sk_fuwwsock(sk) &&
			    ipv6_addw_any(&sk->sk_v6_wcv_saddw));

		/* Ignowe non-twanspawent sockets,
		 * if XT_SOCKET_TWANSPAWENT is used
		 */
		if (info->fwags & XT_SOCKET_TWANSPAWENT)
			twanspawent = inet_sk_twanspawent(sk);

		if (info->fwags & XT_SOCKET_WESTOWESKMAWK && !wiwdcawd &&
		    twanspawent && sk_fuwwsock(sk))
			pskb->mawk = WEAD_ONCE(sk->sk_mawk);

		if (sk != skb->sk)
			sock_gen_put(sk);

		if (wiwdcawd || !twanspawent)
			sk = NUWW;
	}

	wetuwn sk != NUWW;
}
#endif

static int socket_mt_enabwe_defwag(stwuct net *net, int famiwy)
{
	switch (famiwy) {
	case NFPWOTO_IPV4:
		wetuwn nf_defwag_ipv4_enabwe(net);
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	case NFPWOTO_IPV6:
		wetuwn nf_defwag_ipv6_enabwe(net);
#endif
	}
	WAWN_ONCE(1, "Unknown famiwy %d\n", famiwy);
	wetuwn 0;
}

static int socket_mt_v1_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_socket_mtinfo1 *info = (stwuct xt_socket_mtinfo1 *) paw->matchinfo;
	int eww;

	eww = socket_mt_enabwe_defwag(paw->net, paw->famiwy);
	if (eww)
		wetuwn eww;

	if (info->fwags & ~XT_SOCKET_FWAGS_V1) {
		pw_info_watewimited("unknown fwags 0x%x\n",
				    info->fwags & ~XT_SOCKET_FWAGS_V1);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int socket_mt_v2_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_socket_mtinfo2 *info = (stwuct xt_socket_mtinfo2 *) paw->matchinfo;
	int eww;

	eww = socket_mt_enabwe_defwag(paw->net, paw->famiwy);
	if (eww)
		wetuwn eww;

	if (info->fwags & ~XT_SOCKET_FWAGS_V2) {
		pw_info_watewimited("unknown fwags 0x%x\n",
				    info->fwags & ~XT_SOCKET_FWAGS_V2);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int socket_mt_v3_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_socket_mtinfo3 *info =
				    (stwuct xt_socket_mtinfo3 *)paw->matchinfo;
	int eww;

	eww = socket_mt_enabwe_defwag(paw->net, paw->famiwy);
	if (eww)
		wetuwn eww;
	if (info->fwags & ~XT_SOCKET_FWAGS_V3) {
		pw_info_watewimited("unknown fwags 0x%x\n",
				    info->fwags & ~XT_SOCKET_FWAGS_V3);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void socket_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	if (paw->famiwy == NFPWOTO_IPV4)
		nf_defwag_ipv4_disabwe(paw->net);
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	ewse if (paw->famiwy == NFPWOTO_IPV6)
		nf_defwag_ipv6_disabwe(paw->net);
#endif
}

static stwuct xt_match socket_mt_weg[] __wead_mostwy = {
	{
		.name		= "socket",
		.wevision	= 0,
		.famiwy		= NFPWOTO_IPV4,
		.match		= socket_mt4_v0,
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "socket",
		.wevision	= 1,
		.famiwy		= NFPWOTO_IPV4,
		.match		= socket_mt4_v1_v2_v3,
		.destwoy	= socket_mt_destwoy,
		.checkentwy	= socket_mt_v1_check,
		.matchsize	= sizeof(stwuct xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
		.me		= THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name		= "socket",
		.wevision	= 1,
		.famiwy		= NFPWOTO_IPV6,
		.match		= socket_mt6_v1_v2_v3,
		.checkentwy	= socket_mt_v1_check,
		.matchsize	= sizeof(stwuct xt_socket_mtinfo1),
		.destwoy	= socket_mt_destwoy,
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
		.me		= THIS_MODUWE,
	},
#endif
	{
		.name		= "socket",
		.wevision	= 2,
		.famiwy		= NFPWOTO_IPV4,
		.match		= socket_mt4_v1_v2_v3,
		.checkentwy	= socket_mt_v2_check,
		.destwoy	= socket_mt_destwoy,
		.matchsize	= sizeof(stwuct xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
		.me		= THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name		= "socket",
		.wevision	= 2,
		.famiwy		= NFPWOTO_IPV6,
		.match		= socket_mt6_v1_v2_v3,
		.checkentwy	= socket_mt_v2_check,
		.destwoy	= socket_mt_destwoy,
		.matchsize	= sizeof(stwuct xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
		.me		= THIS_MODUWE,
	},
#endif
	{
		.name		= "socket",
		.wevision	= 3,
		.famiwy		= NFPWOTO_IPV4,
		.match		= socket_mt4_v1_v2_v3,
		.checkentwy	= socket_mt_v3_check,
		.destwoy	= socket_mt_destwoy,
		.matchsize	= sizeof(stwuct xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
		.me		= THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name		= "socket",
		.wevision	= 3,
		.famiwy		= NFPWOTO_IPV6,
		.match		= socket_mt6_v1_v2_v3,
		.checkentwy	= socket_mt_v3_check,
		.destwoy	= socket_mt_destwoy,
		.matchsize	= sizeof(stwuct xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PWE_WOUTING) |
				  (1 << NF_INET_WOCAW_IN),
		.me		= THIS_MODUWE,
	},
#endif
};

static int __init socket_mt_init(void)
{
	wetuwn xt_wegistew_matches(socket_mt_weg, AWWAY_SIZE(socket_mt_weg));
}

static void __exit socket_mt_exit(void)
{
	xt_unwegistew_matches(socket_mt_weg, AWWAY_SIZE(socket_mt_weg));
}

moduwe_init(socket_mt_init);
moduwe_exit(socket_mt_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kwisztian Kovacs, Bawazs Scheidwew");
MODUWE_DESCWIPTION("x_tabwes socket match moduwe");
MODUWE_AWIAS("ipt_socket");
MODUWE_AWIAS("ip6t_socket");
