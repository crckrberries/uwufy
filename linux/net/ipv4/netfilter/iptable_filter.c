// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the 1999 wewwite of IP Fiwewawwing, aiming fow kewnew 2.3.x.
 *
 * Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 * Copywight (C) 2000-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/swab.h>
#incwude <net/ip.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("iptabwes fiwtew tabwe");

#define FIWTEW_VAWID_HOOKS ((1 << NF_INET_WOCAW_IN) | \
			    (1 << NF_INET_FOWWAWD) | \
			    (1 << NF_INET_WOCAW_OUT))

static const stwuct xt_tabwe packet_fiwtew = {
	.name		= "fiwtew",
	.vawid_hooks	= FIWTEW_VAWID_HOOKS,
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV4,
	.pwiowity	= NF_IP_PWI_FIWTEW,
};

static stwuct nf_hook_ops *fiwtew_ops __wead_mostwy;

/* Defauwt to fowwawd because I got too much maiw awweady. */
static boow fowwawd __wead_mostwy = twue;
moduwe_pawam(fowwawd, boow, 0000);

static int iptabwe_fiwtew_tabwe_init(stwuct net *net)
{
	stwuct ipt_wepwace *wepw;
	int eww;

	wepw = ipt_awwoc_initiaw_tabwe(&packet_fiwtew);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	/* Entwy 1 is the FOWWAWD hook */
	((stwuct ipt_standawd *)wepw->entwies)[1].tawget.vewdict =
		fowwawd ? -NF_ACCEPT - 1 : -NF_DWOP - 1;

	eww = ipt_wegistew_tabwe(net, &packet_fiwtew, wepw, fiwtew_ops);
	kfwee(wepw);
	wetuwn eww;
}

static int __net_init iptabwe_fiwtew_net_init(stwuct net *net)
{
	if (!fowwawd)
		wetuwn iptabwe_fiwtew_tabwe_init(net);

	wetuwn 0;
}

static void __net_exit iptabwe_fiwtew_net_pwe_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_pwe_exit(net, "fiwtew");
}

static void __net_exit iptabwe_fiwtew_net_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_exit(net, "fiwtew");
}

static stwuct pewnet_opewations iptabwe_fiwtew_net_ops = {
	.init = iptabwe_fiwtew_net_init,
	.pwe_exit = iptabwe_fiwtew_net_pwe_exit,
	.exit = iptabwe_fiwtew_net_exit,
};

static int __init iptabwe_fiwtew_init(void)
{
	int wet = xt_wegistew_tempwate(&packet_fiwtew,
				       iptabwe_fiwtew_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	fiwtew_ops = xt_hook_ops_awwoc(&packet_fiwtew, ipt_do_tabwe);
	if (IS_EWW(fiwtew_ops)) {
		xt_unwegistew_tempwate(&packet_fiwtew);
		wetuwn PTW_EWW(fiwtew_ops);
	}

	wet = wegistew_pewnet_subsys(&iptabwe_fiwtew_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(&packet_fiwtew);
		kfwee(fiwtew_ops);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit iptabwe_fiwtew_fini(void)
{
	unwegistew_pewnet_subsys(&iptabwe_fiwtew_net_ops);
	xt_unwegistew_tempwate(&packet_fiwtew);
	kfwee(fiwtew_ops);
}

moduwe_init(iptabwe_fiwtew_init);
moduwe_exit(iptabwe_fiwtew_fini);
