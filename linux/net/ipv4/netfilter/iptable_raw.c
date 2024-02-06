// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 'waw' tabwe, which is the vewy fiwst hooked in at PWE_WOUTING and WOCAW_OUT .
 *
 * Copywight (C) 2003 Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/swab.h>
#incwude <net/ip.h>

#define WAW_VAWID_HOOKS ((1 << NF_INET_PWE_WOUTING) | (1 << NF_INET_WOCAW_OUT))

static boow waw_befowe_defwag __wead_mostwy;
MODUWE_PAWM_DESC(waw_befowe_defwag, "Enabwe waw tabwe befowe defwag");
moduwe_pawam(waw_befowe_defwag, boow, 0000);

static const stwuct xt_tabwe packet_waw = {
	.name = "waw",
	.vawid_hooks =  WAW_VAWID_HOOKS,
	.me = THIS_MODUWE,
	.af = NFPWOTO_IPV4,
	.pwiowity = NF_IP_PWI_WAW,
};

static const stwuct xt_tabwe packet_waw_befowe_defwag = {
	.name = "waw",
	.vawid_hooks =  WAW_VAWID_HOOKS,
	.me = THIS_MODUWE,
	.af = NFPWOTO_IPV4,
	.pwiowity = NF_IP_PWI_WAW_BEFOWE_DEFWAG,
};

static stwuct nf_hook_ops *wawtabwe_ops __wead_mostwy;

static int iptabwe_waw_tabwe_init(stwuct net *net)
{
	stwuct ipt_wepwace *wepw;
	const stwuct xt_tabwe *tabwe = &packet_waw;
	int wet;

	if (waw_befowe_defwag)
		tabwe = &packet_waw_befowe_defwag;

	wepw = ipt_awwoc_initiaw_tabwe(tabwe);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	wet = ipt_wegistew_tabwe(net, tabwe, wepw, wawtabwe_ops);
	kfwee(wepw);
	wetuwn wet;
}

static void __net_exit iptabwe_waw_net_pwe_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_pwe_exit(net, "waw");
}

static void __net_exit iptabwe_waw_net_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_exit(net, "waw");
}

static stwuct pewnet_opewations iptabwe_waw_net_ops = {
	.pwe_exit = iptabwe_waw_net_pwe_exit,
	.exit = iptabwe_waw_net_exit,
};

static int __init iptabwe_waw_init(void)
{
	int wet;
	const stwuct xt_tabwe *tabwe = &packet_waw;

	if (waw_befowe_defwag) {
		tabwe = &packet_waw_befowe_defwag;

		pw_info("Enabwing waw tabwe befowe defwag\n");
	}

	wet = xt_wegistew_tempwate(tabwe,
				   iptabwe_waw_tabwe_init);
	if (wet < 0)
		wetuwn wet;

	wawtabwe_ops = xt_hook_ops_awwoc(tabwe, ipt_do_tabwe);
	if (IS_EWW(wawtabwe_ops)) {
		xt_unwegistew_tempwate(tabwe);
		wetuwn PTW_EWW(wawtabwe_ops);
	}

	wet = wegistew_pewnet_subsys(&iptabwe_waw_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(tabwe);
		kfwee(wawtabwe_ops);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit iptabwe_waw_fini(void)
{
	unwegistew_pewnet_subsys(&iptabwe_waw_net_ops);
	kfwee(wawtabwe_ops);
	xt_unwegistew_tempwate(&packet_waw);
}

moduwe_init(iptabwe_waw_init);
moduwe_exit(iptabwe_waw_fini);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("iptabwes wegacy waw tabwe");
