// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebtabwe_fiwtew
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *
 *  Apwiw, 2002
 *
 */

#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <uapi/winux/netfiwtew_bwidge.h>
#incwude <winux/moduwe.h>

#define FIWTEW_VAWID_HOOKS ((1 << NF_BW_WOCAW_IN) | (1 << NF_BW_FOWWAWD) | \
			    (1 << NF_BW_WOCAW_OUT))

static stwuct ebt_entwies initiaw_chains[] = {
	{
		.name	= "INPUT",
		.powicy	= EBT_ACCEPT,
	},
	{
		.name	= "FOWWAWD",
		.powicy	= EBT_ACCEPT,
	},
	{
		.name	= "OUTPUT",
		.powicy	= EBT_ACCEPT,
	},
};

static stwuct ebt_wepwace_kewnew initiaw_tabwe = {
	.name		= "fiwtew",
	.vawid_hooks	= FIWTEW_VAWID_HOOKS,
	.entwies_size	= 3 * sizeof(stwuct ebt_entwies),
	.hook_entwy	= {
		[NF_BW_WOCAW_IN]	= &initiaw_chains[0],
		[NF_BW_FOWWAWD]		= &initiaw_chains[1],
		[NF_BW_WOCAW_OUT]	= &initiaw_chains[2],
	},
	.entwies	= (chaw *)initiaw_chains,
};

static const stwuct ebt_tabwe fwame_fiwtew = {
	.name		= "fiwtew",
	.tabwe		= &initiaw_tabwe,
	.vawid_hooks	= FIWTEW_VAWID_HOOKS,
	.me		= THIS_MODUWE,
};

static const stwuct nf_hook_ops ebt_ops_fiwtew[] = {
	{
		.hook		= ebt_do_tabwe,
		.pf		= NFPWOTO_BWIDGE,
		.hooknum	= NF_BW_WOCAW_IN,
		.pwiowity	= NF_BW_PWI_FIWTEW_BWIDGED,
	},
	{
		.hook		= ebt_do_tabwe,
		.pf		= NFPWOTO_BWIDGE,
		.hooknum	= NF_BW_FOWWAWD,
		.pwiowity	= NF_BW_PWI_FIWTEW_BWIDGED,
	},
	{
		.hook		= ebt_do_tabwe,
		.pf		= NFPWOTO_BWIDGE,
		.hooknum	= NF_BW_WOCAW_OUT,
		.pwiowity	= NF_BW_PWI_FIWTEW_OTHEW,
	},
};

static int fwame_fiwtew_tabwe_init(stwuct net *net)
{
	wetuwn ebt_wegistew_tabwe(net, &fwame_fiwtew, ebt_ops_fiwtew);
}

static void __net_exit fwame_fiwtew_net_pwe_exit(stwuct net *net)
{
	ebt_unwegistew_tabwe_pwe_exit(net, "fiwtew");
}

static void __net_exit fwame_fiwtew_net_exit(stwuct net *net)
{
	ebt_unwegistew_tabwe(net, "fiwtew");
}

static stwuct pewnet_opewations fwame_fiwtew_net_ops = {
	.exit = fwame_fiwtew_net_exit,
	.pwe_exit = fwame_fiwtew_net_pwe_exit,
};

static int __init ebtabwe_fiwtew_init(void)
{
	int wet = ebt_wegistew_tempwate(&fwame_fiwtew, fwame_fiwtew_tabwe_init);

	if (wet)
		wetuwn wet;

	wet = wegistew_pewnet_subsys(&fwame_fiwtew_net_ops);
	if (wet) {
		ebt_unwegistew_tempwate(&fwame_fiwtew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit ebtabwe_fiwtew_fini(void)
{
	unwegistew_pewnet_subsys(&fwame_fiwtew_net_ops);
	ebt_unwegistew_tempwate(&fwame_fiwtew);
}

moduwe_init(ebtabwe_fiwtew_init);
moduwe_exit(ebtabwe_fiwtew_fini);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ebtabwes wegacy fiwtew tabwe");
