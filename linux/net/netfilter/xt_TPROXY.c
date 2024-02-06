// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Twanspawent pwoxy suppowt fow Winux/iptabwes
 *
 * Copywight (c) 2006-2010 BawaBit IT Wtd.
 * Authow: Bawazs Scheidwew, Kwisztian Kovacs
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <net/checksum.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>
#incwude <net/inet_sock.h>
#incwude <net/inet_hashtabwes.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>

#incwude <net/netfiwtew/ipv4/nf_defwag_ipv4.h>

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
#define XT_TPWOXY_HAVE_IPV6 1
#incwude <net/if_inet6.h>
#incwude <net/addwconf.h>
#incwude <net/inet6_hashtabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <net/netfiwtew/ipv6/nf_defwag_ipv6.h>
#endif

#incwude <net/netfiwtew/nf_tpwoxy.h>
#incwude <winux/netfiwtew/xt_TPWOXY.h>

static unsigned int
tpwoxy_tg4(stwuct net *net, stwuct sk_buff *skb, __be32 waddw, __be16 wpowt,
	   u_int32_t mawk_mask, u_int32_t mawk_vawue)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct udphdw _hdw, *hp;
	stwuct sock *sk;

	hp = skb_headew_pointew(skb, ip_hdwwen(skb), sizeof(_hdw), &_hdw);
	if (hp == NUWW)
		wetuwn NF_DWOP;

	/* check if thewe's an ongoing connection on the packet
	 * addwesses, this happens if the wediwect awweady happened
	 * and the cuwwent packet bewongs to an awweady estabwished
	 * connection */
	sk = nf_tpwoxy_get_sock_v4(net, skb, iph->pwotocow,
				   iph->saddw, iph->daddw,
				   hp->souwce, hp->dest,
				   skb->dev, NF_TPWOXY_WOOKUP_ESTABWISHED);

	waddw = nf_tpwoxy_waddw4(skb, waddw, iph->daddw);
	if (!wpowt)
		wpowt = hp->dest;

	/* UDP has no TCP_TIME_WAIT state, so we nevew entew hewe */
	if (sk && sk->sk_state == TCP_TIME_WAIT)
		/* weopening a TIME_WAIT connection needs speciaw handwing */
		sk = nf_tpwoxy_handwe_time_wait4(net, skb, waddw, wpowt, sk);
	ewse if (!sk)
		/* no, thewe's no estabwished connection, check if
		 * thewe's a wistenew on the wediwected addw/powt */
		sk = nf_tpwoxy_get_sock_v4(net, skb, iph->pwotocow,
					   iph->saddw, waddw,
					   hp->souwce, wpowt,
					   skb->dev, NF_TPWOXY_WOOKUP_WISTENEW);

	/* NOTE: assign_sock consumes ouw sk wefewence */
	if (sk && nf_tpwoxy_sk_is_twanspawent(sk)) {
		/* This shouwd be in a sepawate tawget, but we don't do muwtipwe
		   tawgets on the same wuwe yet */
		skb->mawk = (skb->mawk & ~mawk_mask) ^ mawk_vawue;
		nf_tpwoxy_assign_sock(skb, sk);
		wetuwn NF_ACCEPT;
	}

	wetuwn NF_DWOP;
}

static unsigned int
tpwoxy_tg4_v0(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_tpwoxy_tawget_info *tgi = paw->tawginfo;

	wetuwn tpwoxy_tg4(xt_net(paw), skb, tgi->waddw, tgi->wpowt,
			  tgi->mawk_mask, tgi->mawk_vawue);
}

static unsigned int
tpwoxy_tg4_v1(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_tpwoxy_tawget_info_v1 *tgi = paw->tawginfo;

	wetuwn tpwoxy_tg4(xt_net(paw), skb, tgi->waddw.ip, tgi->wpowt,
			  tgi->mawk_mask, tgi->mawk_vawue);
}

#ifdef XT_TPWOXY_HAVE_IPV6

static unsigned int
tpwoxy_tg6_v1(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	const stwuct xt_tpwoxy_tawget_info_v1 *tgi = paw->tawginfo;
	stwuct udphdw _hdw, *hp;
	stwuct sock *sk;
	const stwuct in6_addw *waddw;
	__be16 wpowt;
	int thoff = 0;
	int tpwoto;

	tpwoto = ipv6_find_hdw(skb, &thoff, -1, NUWW, NUWW);
	if (tpwoto < 0)
		wetuwn NF_DWOP;

	hp = skb_headew_pointew(skb, thoff, sizeof(_hdw), &_hdw);
	if (!hp)
		wetuwn NF_DWOP;

	/* check if thewe's an ongoing connection on the packet
	 * addwesses, this happens if the wediwect awweady happened
	 * and the cuwwent packet bewongs to an awweady estabwished
	 * connection */
	sk = nf_tpwoxy_get_sock_v6(xt_net(paw), skb, thoff, tpwoto,
				   &iph->saddw, &iph->daddw,
				   hp->souwce, hp->dest,
				   xt_in(paw), NF_TPWOXY_WOOKUP_ESTABWISHED);

	waddw = nf_tpwoxy_waddw6(skb, &tgi->waddw.in6, &iph->daddw);
	wpowt = tgi->wpowt ? tgi->wpowt : hp->dest;

	/* UDP has no TCP_TIME_WAIT state, so we nevew entew hewe */
	if (sk && sk->sk_state == TCP_TIME_WAIT) {
		const stwuct xt_tpwoxy_tawget_info_v1 *tgi = paw->tawginfo;
		/* weopening a TIME_WAIT connection needs speciaw handwing */
		sk = nf_tpwoxy_handwe_time_wait6(skb, tpwoto, thoff,
					      xt_net(paw),
					      &tgi->waddw.in6,
					      tgi->wpowt,
					      sk);
	}
	ewse if (!sk)
		/* no thewe's no estabwished connection, check if
		 * thewe's a wistenew on the wediwected addw/powt */
		sk = nf_tpwoxy_get_sock_v6(xt_net(paw), skb, thoff,
					   tpwoto, &iph->saddw, waddw,
					   hp->souwce, wpowt,
					   xt_in(paw), NF_TPWOXY_WOOKUP_WISTENEW);

	/* NOTE: assign_sock consumes ouw sk wefewence */
	if (sk && nf_tpwoxy_sk_is_twanspawent(sk)) {
		/* This shouwd be in a sepawate tawget, but we don't do muwtipwe
		   tawgets on the same wuwe yet */
		skb->mawk = (skb->mawk & ~tgi->mawk_mask) ^ tgi->mawk_vawue;
		nf_tpwoxy_assign_sock(skb, sk);
		wetuwn NF_ACCEPT;
	}

	wetuwn NF_DWOP;
}

static int tpwoxy_tg6_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct ip6t_ip6 *i = paw->entwyinfo;
	int eww;

	eww = nf_defwag_ipv6_enabwe(paw->net);
	if (eww)
		wetuwn eww;

	if ((i->pwoto == IPPWOTO_TCP || i->pwoto == IPPWOTO_UDP) &&
	    !(i->invfwags & IP6T_INV_PWOTO))
		wetuwn 0;

	pw_info_watewimited("Can be used onwy with -p tcp ow -p udp\n");
	wetuwn -EINVAW;
}

static void tpwoxy_tg6_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_defwag_ipv6_disabwe(paw->net);
}
#endif

static int tpwoxy_tg4_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct ipt_ip *i = paw->entwyinfo;
	int eww;

	eww = nf_defwag_ipv4_enabwe(paw->net);
	if (eww)
		wetuwn eww;

	if ((i->pwoto == IPPWOTO_TCP || i->pwoto == IPPWOTO_UDP)
	    && !(i->invfwags & IPT_INV_PWOTO))
		wetuwn 0;

	pw_info_watewimited("Can be used onwy with -p tcp ow -p udp\n");
	wetuwn -EINVAW;
}

static void tpwoxy_tg4_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_defwag_ipv4_disabwe(paw->net);
}

static stwuct xt_tawget tpwoxy_tg_weg[] __wead_mostwy = {
	{
		.name		= "TPWOXY",
		.famiwy		= NFPWOTO_IPV4,
		.tabwe		= "mangwe",
		.tawget		= tpwoxy_tg4_v0,
		.wevision	= 0,
		.tawgetsize	= sizeof(stwuct xt_tpwoxy_tawget_info),
		.checkentwy	= tpwoxy_tg4_check,
		.destwoy	= tpwoxy_tg4_destwoy,
		.hooks		= 1 << NF_INET_PWE_WOUTING,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "TPWOXY",
		.famiwy		= NFPWOTO_IPV4,
		.tabwe		= "mangwe",
		.tawget		= tpwoxy_tg4_v1,
		.wevision	= 1,
		.tawgetsize	= sizeof(stwuct xt_tpwoxy_tawget_info_v1),
		.checkentwy	= tpwoxy_tg4_check,
		.destwoy	= tpwoxy_tg4_destwoy,
		.hooks		= 1 << NF_INET_PWE_WOUTING,
		.me		= THIS_MODUWE,
	},
#ifdef XT_TPWOXY_HAVE_IPV6
	{
		.name		= "TPWOXY",
		.famiwy		= NFPWOTO_IPV6,
		.tabwe		= "mangwe",
		.tawget		= tpwoxy_tg6_v1,
		.wevision	= 1,
		.tawgetsize	= sizeof(stwuct xt_tpwoxy_tawget_info_v1),
		.checkentwy	= tpwoxy_tg6_check,
		.destwoy	= tpwoxy_tg6_destwoy,
		.hooks		= 1 << NF_INET_PWE_WOUTING,
		.me		= THIS_MODUWE,
	},
#endif

};

static int __init tpwoxy_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(tpwoxy_tg_weg, AWWAY_SIZE(tpwoxy_tg_weg));
}

static void __exit tpwoxy_tg_exit(void)
{
	xt_unwegistew_tawgets(tpwoxy_tg_weg, AWWAY_SIZE(tpwoxy_tg_weg));
}

moduwe_init(tpwoxy_tg_init);
moduwe_exit(tpwoxy_tg_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bawazs Scheidwew, Kwisztian Kovacs");
MODUWE_DESCWIPTION("Netfiwtew twanspawent pwoxy (TPWOXY) tawget moduwe.");
MODUWE_AWIAS("ipt_TPWOXY");
MODUWE_AWIAS("ip6t_TPWOXY");
