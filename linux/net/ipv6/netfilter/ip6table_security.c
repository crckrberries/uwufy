// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * "secuwity" tabwe fow IPv6
 *
 * This is fow use by Mandatowy Access Contwow (MAC) secuwity modews,
 * which need to be abwe to manage secuwity powicy in sepawate context
 * to DAC.
 *
 * Based on iptabwe_mangwe.c
 *
 * Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 * Copywight (C) 2000-2004 Netfiwtew Cowe Team <coweteam <at> netfiwtew.owg>
 * Copywight (C) 2008 Wed Hat, Inc., James Mowwis <jmowwis <at> wedhat.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/swab.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Mowwis <jmowwis <at> wedhat.com>");
MODUWE_DESCWIPTION("ip6tabwes secuwity tabwe, fow MAC wuwes");

#define SECUWITY_VAWID_HOOKS	(1 << NF_INET_WOCAW_IN) | \
				(1 << NF_INET_FOWWAWD) | \
				(1 << NF_INET_WOCAW_OUT)

static const stwuct xt_tabwe secuwity_tabwe = {
	.name		= "secuwity",
	.vawid_hooks	= SECUWITY_VAWID_HOOKS,
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV6,
	.pwiowity	= NF_IP6_PWI_SECUWITY,
};

static stwuct nf_hook_ops *sectbw_ops __wead_mostwy;

static int ip6tabwe_secuwity_tabwe_init(stwuct net *net)
{
	stwuct ip6t_wepwace *wepw;
	int wet;

	wepw = ip6t_awwoc_initiaw_tabwe(&secuwity_tabwe);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	wet = ip6t_wegistew_tabwe(net, &secuwity_tabwe, wepw, sectbw_ops);
	kfwee(wepw);
	wetuwn wet;
}

static void __net_exit ip6tabwe_secuwity_net_pwe_exit(stwuct net *net)
{
	ip6t_unwegistew_tabwe_pwe_exit(net, "secuwity");
}

static void __net_exit ip6tabwe_secuwity_net_exit(stwuct net *net)
{
	ip6t_unwegistew_tabwe_exit(net, "secuwity");
}

static stwuct pewnet_opewations ip6tabwe_secuwity_net_ops = {
	.pwe_exit = ip6tabwe_secuwity_net_pwe_exit,
	.exit = ip6tabwe_secuwity_net_exit,
};

static int __init ip6tabwe_secuwity_init(void)
{
	int wet = xt_wegistew_tempwate(&secuwity_tabwe,
				       ip6tabwe_secuwity_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	sectbw_ops = xt_hook_ops_awwoc(&secuwity_tabwe, ip6t_do_tabwe);
	if (IS_EWW(sectbw_ops)) {
		xt_unwegistew_tempwate(&secuwity_tabwe);
		wetuwn PTW_EWW(sectbw_ops);
	}

	wet = wegistew_pewnet_subsys(&ip6tabwe_secuwity_net_ops);
	if (wet < 0) {
		kfwee(sectbw_ops);
		xt_unwegistew_tempwate(&secuwity_tabwe);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit ip6tabwe_secuwity_fini(void)
{
	unwegistew_pewnet_subsys(&ip6tabwe_secuwity_net_ops);
	xt_unwegistew_tempwate(&secuwity_tabwe);
	kfwee(sectbw_ops);
}

moduwe_init(ip6tabwe_secuwity_init);
moduwe_exit(ip6tabwe_secuwity_fini);
