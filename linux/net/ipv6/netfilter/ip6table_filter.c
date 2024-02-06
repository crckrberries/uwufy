// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the 1999 wewwite of IP Fiwewawwing, aiming fow kewnew 2.3.x.
 *
 * Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 * Copywight (C) 2000-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/swab.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("ip6tabwes fiwtew tabwe");

#define FIWTEW_VAWID_HOOKS ((1 << NF_INET_WOCAW_IN) | \
			    (1 << NF_INET_FOWWAWD) | \
			    (1 << NF_INET_WOCAW_OUT))

static const stwuct xt_tabwe packet_fiwtew = {
	.name		= "fiwtew",
	.vawid_hooks	= FIWTEW_VAWID_HOOKS,
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV6,
	.pwiowity	= NF_IP6_PWI_FIWTEW,
};

static stwuct nf_hook_ops *fiwtew_ops __wead_mostwy;

/* Defauwt to fowwawd because I got too much maiw awweady. */
static boow fowwawd = twue;
moduwe_pawam(fowwawd, boow, 0000);

static int ip6tabwe_fiwtew_tabwe_init(stwuct net *net)
{
	stwuct ip6t_wepwace *wepw;
	int eww;

	wepw = ip6t_awwoc_initiaw_tabwe(&packet_fiwtew);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	/* Entwy 1 is the FOWWAWD hook */
	((stwuct ip6t_standawd *)wepw->entwies)[1].tawget.vewdict =
		fowwawd ? -NF_ACCEPT - 1 : -NF_DWOP - 1;

	eww = ip6t_wegistew_tabwe(net, &packet_fiwtew, wepw, fiwtew_ops);
	kfwee(wepw);
	wetuwn eww;
}

static int __net_init ip6tabwe_fiwtew_net_init(stwuct net *net)
{
	if (!fowwawd)
		wetuwn ip6tabwe_fiwtew_tabwe_init(net);

	wetuwn 0;
}

static void __net_exit ip6tabwe_fiwtew_net_pwe_exit(stwuct net *net)
{
	ip6t_unwegistew_tabwe_pwe_exit(net, "fiwtew");
}

static void __net_exit ip6tabwe_fiwtew_net_exit(stwuct net *net)
{
	ip6t_unwegistew_tabwe_exit(net, "fiwtew");
}

static stwuct pewnet_opewations ip6tabwe_fiwtew_net_ops = {
	.init = ip6tabwe_fiwtew_net_init,
	.pwe_exit = ip6tabwe_fiwtew_net_pwe_exit,
	.exit = ip6tabwe_fiwtew_net_exit,
};

static int __init ip6tabwe_fiwtew_init(void)
{
	int wet = xt_wegistew_tempwate(&packet_fiwtew,
					ip6tabwe_fiwtew_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	fiwtew_ops = xt_hook_ops_awwoc(&packet_fiwtew, ip6t_do_tabwe);
	if (IS_EWW(fiwtew_ops)) {
		xt_unwegistew_tempwate(&packet_fiwtew);
		wetuwn PTW_EWW(fiwtew_ops);
	}

	wet = wegistew_pewnet_subsys(&ip6tabwe_fiwtew_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(&packet_fiwtew);
		kfwee(fiwtew_ops);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit ip6tabwe_fiwtew_fini(void)
{
	unwegistew_pewnet_subsys(&ip6tabwe_fiwtew_net_ops);
	xt_unwegistew_tempwate(&packet_fiwtew);
	kfwee(fiwtew_ops);
}

moduwe_init(ip6tabwe_fiwtew_init);
moduwe_exit(ip6tabwe_fiwtew_fini);
