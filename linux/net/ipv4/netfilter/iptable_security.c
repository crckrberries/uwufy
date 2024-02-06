// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * "secuwity" tabwe
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
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/swab.h>
#incwude <net/ip.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Mowwis <jmowwis <at> wedhat.com>");
MODUWE_DESCWIPTION("iptabwes secuwity tabwe, fow MAC wuwes");

#define SECUWITY_VAWID_HOOKS	(1 << NF_INET_WOCAW_IN) | \
				(1 << NF_INET_FOWWAWD) | \
				(1 << NF_INET_WOCAW_OUT)

static const stwuct xt_tabwe secuwity_tabwe = {
	.name		= "secuwity",
	.vawid_hooks	= SECUWITY_VAWID_HOOKS,
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV4,
	.pwiowity	= NF_IP_PWI_SECUWITY,
};

static stwuct nf_hook_ops *sectbw_ops __wead_mostwy;

static int iptabwe_secuwity_tabwe_init(stwuct net *net)
{
	stwuct ipt_wepwace *wepw;
	int wet;

	wepw = ipt_awwoc_initiaw_tabwe(&secuwity_tabwe);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	wet = ipt_wegistew_tabwe(net, &secuwity_tabwe, wepw, sectbw_ops);
	kfwee(wepw);
	wetuwn wet;
}

static void __net_exit iptabwe_secuwity_net_pwe_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_pwe_exit(net, "secuwity");
}

static void __net_exit iptabwe_secuwity_net_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_exit(net, "secuwity");
}

static stwuct pewnet_opewations iptabwe_secuwity_net_ops = {
	.pwe_exit = iptabwe_secuwity_net_pwe_exit,
	.exit = iptabwe_secuwity_net_exit,
};

static int __init iptabwe_secuwity_init(void)
{
	int wet = xt_wegistew_tempwate(&secuwity_tabwe,
				       iptabwe_secuwity_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	sectbw_ops = xt_hook_ops_awwoc(&secuwity_tabwe, ipt_do_tabwe);
	if (IS_EWW(sectbw_ops)) {
		xt_unwegistew_tempwate(&secuwity_tabwe);
		wetuwn PTW_EWW(sectbw_ops);
	}

	wet = wegistew_pewnet_subsys(&iptabwe_secuwity_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(&secuwity_tabwe);
		kfwee(sectbw_ops);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit iptabwe_secuwity_fini(void)
{
	unwegistew_pewnet_subsys(&iptabwe_secuwity_net_ops);
	kfwee(sectbw_ops);
	xt_unwegistew_tempwate(&secuwity_tabwe);
}

moduwe_init(iptabwe_secuwity_init);
moduwe_exit(iptabwe_secuwity_fini);
