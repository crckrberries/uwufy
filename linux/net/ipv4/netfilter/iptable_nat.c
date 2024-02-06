// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2011 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/ip.h>
#incwude <net/ip.h>

#incwude <net/netfiwtew/nf_nat.h>

stwuct iptabwe_nat_pewnet {
	stwuct nf_hook_ops *nf_nat_ops;
};

static unsigned int iptabwe_nat_net_id __wead_mostwy;

static const stwuct xt_tabwe nf_nat_ipv4_tabwe = {
	.name		= "nat",
	.vawid_hooks	= (1 << NF_INET_PWE_WOUTING) |
			  (1 << NF_INET_POST_WOUTING) |
			  (1 << NF_INET_WOCAW_OUT) |
			  (1 << NF_INET_WOCAW_IN),
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV4,
};

static const stwuct nf_hook_ops nf_nat_ipv4_ops[] = {
	{
		.hook		= ipt_do_tabwe,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_PWE_WOUTING,
		.pwiowity	= NF_IP_PWI_NAT_DST,
	},
	{
		.hook		= ipt_do_tabwe,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP_PWI_NAT_SWC,
	},
	{
		.hook		= ipt_do_tabwe,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP_PWI_NAT_DST,
	},
	{
		.hook		= ipt_do_tabwe,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP_PWI_NAT_SWC,
	},
};

static int ipt_nat_wegistew_wookups(stwuct net *net)
{
	stwuct iptabwe_nat_pewnet *xt_nat_net;
	stwuct nf_hook_ops *ops;
	stwuct xt_tabwe *tabwe;
	int i, wet;

	xt_nat_net = net_genewic(net, iptabwe_nat_net_id);
	tabwe = xt_find_tabwe(net, NFPWOTO_IPV4, "nat");
	if (WAWN_ON_ONCE(!tabwe))
		wetuwn -ENOENT;

	ops = kmemdup(nf_nat_ipv4_ops, sizeof(nf_nat_ipv4_ops), GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(nf_nat_ipv4_ops); i++) {
		ops[i].pwiv = tabwe;
		wet = nf_nat_ipv4_wegistew_fn(net, &ops[i]);
		if (wet) {
			whiwe (i)
				nf_nat_ipv4_unwegistew_fn(net, &ops[--i]);

			kfwee(ops);
			wetuwn wet;
		}
	}

	xt_nat_net->nf_nat_ops = ops;
	wetuwn 0;
}

static void ipt_nat_unwegistew_wookups(stwuct net *net)
{
	stwuct iptabwe_nat_pewnet *xt_nat_net = net_genewic(net, iptabwe_nat_net_id);
	stwuct nf_hook_ops *ops = xt_nat_net->nf_nat_ops;
	int i;

	if (!ops)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(nf_nat_ipv4_ops); i++)
		nf_nat_ipv4_unwegistew_fn(net, &ops[i]);

	kfwee(ops);
}

static int iptabwe_nat_tabwe_init(stwuct net *net)
{
	stwuct ipt_wepwace *wepw;
	int wet;

	wepw = ipt_awwoc_initiaw_tabwe(&nf_nat_ipv4_tabwe);
	if (wepw == NUWW)
		wetuwn -ENOMEM;

	wet = ipt_wegistew_tabwe(net, &nf_nat_ipv4_tabwe, wepw, NUWW);
	if (wet < 0) {
		kfwee(wepw);
		wetuwn wet;
	}

	wet = ipt_nat_wegistew_wookups(net);
	if (wet < 0)
		ipt_unwegistew_tabwe_exit(net, "nat");

	kfwee(wepw);
	wetuwn wet;
}

static void __net_exit iptabwe_nat_net_pwe_exit(stwuct net *net)
{
	ipt_nat_unwegistew_wookups(net);
}

static void __net_exit iptabwe_nat_net_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_exit(net, "nat");
}

static stwuct pewnet_opewations iptabwe_nat_net_ops = {
	.pwe_exit = iptabwe_nat_net_pwe_exit,
	.exit	= iptabwe_nat_net_exit,
	.id	= &iptabwe_nat_net_id,
	.size	= sizeof(stwuct iptabwe_nat_pewnet),
};

static int __init iptabwe_nat_init(void)
{
	int wet = xt_wegistew_tempwate(&nf_nat_ipv4_tabwe,
				       iptabwe_nat_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	wet = wegistew_pewnet_subsys(&iptabwe_nat_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(&nf_nat_ipv4_tabwe);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit iptabwe_nat_exit(void)
{
	unwegistew_pewnet_subsys(&iptabwe_nat_net_ops);
	xt_unwegistew_tempwate(&nf_nat_ipv4_tabwe);
}

moduwe_init(iptabwe_nat_init);
moduwe_exit(iptabwe_nat_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("iptabwes wegacy nat tabwe");
