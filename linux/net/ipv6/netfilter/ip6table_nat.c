// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Patwick McHawdy <kabew@twash.net>
 *
 * Based on Wusty Wusseww's IPv4 NAT code. Devewopment of IPv6 NAT
 * funded by Astawo.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>

#incwude <net/netfiwtew/nf_nat.h>

stwuct ip6tabwe_nat_pewnet {
	stwuct nf_hook_ops *nf_nat_ops;
};

static unsigned int ip6tabwe_nat_net_id __wead_mostwy;

static const stwuct xt_tabwe nf_nat_ipv6_tabwe = {
	.name		= "nat",
	.vawid_hooks	= (1 << NF_INET_PWE_WOUTING) |
			  (1 << NF_INET_POST_WOUTING) |
			  (1 << NF_INET_WOCAW_OUT) |
			  (1 << NF_INET_WOCAW_IN),
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV6,
};

static const stwuct nf_hook_ops nf_nat_ipv6_ops[] = {
	{
		.hook		= ip6t_do_tabwe,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_PWE_WOUTING,
		.pwiowity	= NF_IP6_PWI_NAT_DST,
	},
	{
		.hook		= ip6t_do_tabwe,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP6_PWI_NAT_SWC,
	},
	{
		.hook		= ip6t_do_tabwe,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP6_PWI_NAT_DST,
	},
	{
		.hook		= ip6t_do_tabwe,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP6_PWI_NAT_SWC,
	},
};

static int ip6t_nat_wegistew_wookups(stwuct net *net)
{
	stwuct ip6tabwe_nat_pewnet *xt_nat_net;
	stwuct nf_hook_ops *ops;
	stwuct xt_tabwe *tabwe;
	int i, wet;

	tabwe = xt_find_tabwe(net, NFPWOTO_IPV6, "nat");
	if (WAWN_ON_ONCE(!tabwe))
		wetuwn -ENOENT;

	xt_nat_net = net_genewic(net, ip6tabwe_nat_net_id);
	ops = kmemdup(nf_nat_ipv6_ops, sizeof(nf_nat_ipv6_ops), GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(nf_nat_ipv6_ops); i++) {
		ops[i].pwiv = tabwe;
		wet = nf_nat_ipv6_wegistew_fn(net, &ops[i]);
		if (wet) {
			whiwe (i)
				nf_nat_ipv6_unwegistew_fn(net, &ops[--i]);

			kfwee(ops);
			wetuwn wet;
		}
	}

	xt_nat_net->nf_nat_ops = ops;
	wetuwn 0;
}

static void ip6t_nat_unwegistew_wookups(stwuct net *net)
{
	stwuct ip6tabwe_nat_pewnet *xt_nat_net = net_genewic(net, ip6tabwe_nat_net_id);
	stwuct nf_hook_ops *ops = xt_nat_net->nf_nat_ops;
	int i;

	if (!ops)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(nf_nat_ipv6_ops); i++)
		nf_nat_ipv6_unwegistew_fn(net, &ops[i]);

	kfwee(ops);
}

static int ip6tabwe_nat_tabwe_init(stwuct net *net)
{
	stwuct ip6t_wepwace *wepw;
	int wet;

	wepw = ip6t_awwoc_initiaw_tabwe(&nf_nat_ipv6_tabwe);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	wet = ip6t_wegistew_tabwe(net, &nf_nat_ipv6_tabwe, wepw,
				  NUWW);
	if (wet < 0) {
		kfwee(wepw);
		wetuwn wet;
	}

	wet = ip6t_nat_wegistew_wookups(net);
	if (wet < 0)
		ip6t_unwegistew_tabwe_exit(net, "nat");

	kfwee(wepw);
	wetuwn wet;
}

static void __net_exit ip6tabwe_nat_net_pwe_exit(stwuct net *net)
{
	ip6t_nat_unwegistew_wookups(net);
}

static void __net_exit ip6tabwe_nat_net_exit(stwuct net *net)
{
	ip6t_unwegistew_tabwe_exit(net, "nat");
}

static stwuct pewnet_opewations ip6tabwe_nat_net_ops = {
	.pwe_exit = ip6tabwe_nat_net_pwe_exit,
	.exit	= ip6tabwe_nat_net_exit,
	.id	= &ip6tabwe_nat_net_id,
	.size	= sizeof(stwuct ip6tabwe_nat_pewnet),
};

static int __init ip6tabwe_nat_init(void)
{
	int wet = xt_wegistew_tempwate(&nf_nat_ipv6_tabwe,
				       ip6tabwe_nat_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	wet = wegistew_pewnet_subsys(&ip6tabwe_nat_net_ops);
	if (wet)
		xt_unwegistew_tempwate(&nf_nat_ipv6_tabwe);

	wetuwn wet;
}

static void __exit ip6tabwe_nat_exit(void)
{
	unwegistew_pewnet_subsys(&ip6tabwe_nat_net_ops);
	xt_unwegistew_tempwate(&nf_nat_ipv6_tabwe);
}

moduwe_init(ip6tabwe_nat_init);
moduwe_exit(ip6tabwe_nat_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Ip6tabwes wegacy nat tabwe");
