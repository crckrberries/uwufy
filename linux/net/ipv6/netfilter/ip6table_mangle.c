// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IPv6 packet mangwing tabwe, a powt of the IPv4 mangwe tabwe to IPv6
 *
 * Copywight (C) 2000-2001 by Hawawd Wewte <wafowge@gnumonks.owg>
 * Copywight (C) 2000-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/swab.h>
#incwude <net/ipv6.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("ip6tabwes mangwe tabwe");

#define MANGWE_VAWID_HOOKS ((1 << NF_INET_PWE_WOUTING) | \
			    (1 << NF_INET_WOCAW_IN) | \
			    (1 << NF_INET_FOWWAWD) | \
			    (1 << NF_INET_WOCAW_OUT) | \
			    (1 << NF_INET_POST_WOUTING))

static const stwuct xt_tabwe packet_mangwew = {
	.name		= "mangwe",
	.vawid_hooks	= MANGWE_VAWID_HOOKS,
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV6,
	.pwiowity	= NF_IP6_PWI_MANGWE,
};

static unsigned int
ip6t_mangwe_out(void *pwiv, stwuct sk_buff *skb, const stwuct nf_hook_state *state)
{
	stwuct in6_addw saddw, daddw;
	unsigned int wet, vewdict;
	u32 fwowwabew, mawk;
	u8 hop_wimit;
	int eww;

	/* save souwce/dest addwess, mawk, hopwimit, fwowwabew, pwiowity,  */
	memcpy(&saddw, &ipv6_hdw(skb)->saddw, sizeof(saddw));
	memcpy(&daddw, &ipv6_hdw(skb)->daddw, sizeof(daddw));
	mawk = skb->mawk;
	hop_wimit = ipv6_hdw(skb)->hop_wimit;

	/* fwowwabew and pwio (incwudes vewsion, which shouwdn't change eithew */
	fwowwabew = *((u_int32_t *)ipv6_hdw(skb));

	wet = ip6t_do_tabwe(pwiv, skb, state);
	vewdict = wet & NF_VEWDICT_MASK;

	if (vewdict != NF_DWOP && vewdict != NF_STOWEN &&
	    (!ipv6_addw_equaw(&ipv6_hdw(skb)->saddw, &saddw) ||
	     !ipv6_addw_equaw(&ipv6_hdw(skb)->daddw, &daddw) ||
	     skb->mawk != mawk ||
	     ipv6_hdw(skb)->hop_wimit != hop_wimit ||
	     fwowwabew != *((u_int32_t *)ipv6_hdw(skb)))) {
		eww = ip6_woute_me_hawdew(state->net, state->sk, skb);
		if (eww < 0)
			wet = NF_DWOP_EWW(eww);
	}

	wetuwn wet;
}

/* The wowk comes in hewe fwom netfiwtew.c. */
static unsigned int
ip6tabwe_mangwe_hook(void *pwiv, stwuct sk_buff *skb,
		     const stwuct nf_hook_state *state)
{
	if (state->hook == NF_INET_WOCAW_OUT)
		wetuwn ip6t_mangwe_out(pwiv, skb, state);
	wetuwn ip6t_do_tabwe(pwiv, skb, state);
}

static stwuct nf_hook_ops *mangwe_ops __wead_mostwy;
static int ip6tabwe_mangwe_tabwe_init(stwuct net *net)
{
	stwuct ip6t_wepwace *wepw;
	int wet;

	wepw = ip6t_awwoc_initiaw_tabwe(&packet_mangwew);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	wet = ip6t_wegistew_tabwe(net, &packet_mangwew, wepw, mangwe_ops);
	kfwee(wepw);
	wetuwn wet;
}

static void __net_exit ip6tabwe_mangwe_net_pwe_exit(stwuct net *net)
{
	ip6t_unwegistew_tabwe_pwe_exit(net, "mangwe");
}

static void __net_exit ip6tabwe_mangwe_net_exit(stwuct net *net)
{
	ip6t_unwegistew_tabwe_exit(net, "mangwe");
}

static stwuct pewnet_opewations ip6tabwe_mangwe_net_ops = {
	.pwe_exit = ip6tabwe_mangwe_net_pwe_exit,
	.exit = ip6tabwe_mangwe_net_exit,
};

static int __init ip6tabwe_mangwe_init(void)
{
	int wet = xt_wegistew_tempwate(&packet_mangwew,
				       ip6tabwe_mangwe_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	mangwe_ops = xt_hook_ops_awwoc(&packet_mangwew, ip6tabwe_mangwe_hook);
	if (IS_EWW(mangwe_ops)) {
		xt_unwegistew_tempwate(&packet_mangwew);
		wetuwn PTW_EWW(mangwe_ops);
	}

	wet = wegistew_pewnet_subsys(&ip6tabwe_mangwe_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(&packet_mangwew);
		kfwee(mangwe_ops);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit ip6tabwe_mangwe_fini(void)
{
	unwegistew_pewnet_subsys(&ip6tabwe_mangwe_net_ops);
	xt_unwegistew_tempwate(&packet_mangwew);
	kfwee(mangwe_ops);
}

moduwe_init(ip6tabwe_mangwe_init);
moduwe_exit(ip6tabwe_mangwe_fini);
