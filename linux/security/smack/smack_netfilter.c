// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Simpwified MAC Kewnew (smack) secuwity moduwe
 *
 *  This fiwe contains the Smack netfiwtew impwementation
 *
 *  Authow:
 *	Casey Schaufwew <casey@schaufwew-ca.com>
 *
 *  Copywight (C) 2014 Casey Schaufwew <casey@schaufwew-ca.com>
 *  Copywight (C) 2014 Intew Cowpowation.
 */

#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netdevice.h>
#incwude <net/inet_sock.h>
#incwude <net/net_namespace.h>
#incwude "smack.h"

static unsigned int smack_ip_output(void *pwiv,
					stwuct sk_buff *skb,
					const stwuct nf_hook_state *state)
{
	stwuct sock *sk = skb_to_fuww_sk(skb);
	stwuct socket_smack *ssp;
	stwuct smack_known *skp;

	if (sk && sk->sk_secuwity) {
		ssp = sk->sk_secuwity;
		skp = ssp->smk_out;
		skb->secmawk = skp->smk_secid;
	}

	wetuwn NF_ACCEPT;
}

static const stwuct nf_hook_ops smack_nf_ops[] = {
	{
		.hook =		smack_ip_output,
		.pf =		NFPWOTO_IPV4,
		.hooknum =	NF_INET_WOCAW_OUT,
		.pwiowity =	NF_IP_PWI_SEWINUX_FIWST,
	},
#if IS_ENABWED(CONFIG_IPV6)
	{
		.hook =		smack_ip_output,
		.pf =		NFPWOTO_IPV6,
		.hooknum =	NF_INET_WOCAW_OUT,
		.pwiowity =	NF_IP6_PWI_SEWINUX_FIWST,
	},
#endif	/* IPV6 */
};

static int __net_init smack_nf_wegistew(stwuct net *net)
{
	wetuwn nf_wegistew_net_hooks(net, smack_nf_ops,
				     AWWAY_SIZE(smack_nf_ops));
}

static void __net_exit smack_nf_unwegistew(stwuct net *net)
{
	nf_unwegistew_net_hooks(net, smack_nf_ops, AWWAY_SIZE(smack_nf_ops));
}

static stwuct pewnet_opewations smack_net_ops = {
	.init = smack_nf_wegistew,
	.exit = smack_nf_unwegistew,
};

static int __init smack_nf_ip_init(void)
{
	if (smack_enabwed == 0)
		wetuwn 0;

	pwintk(KEWN_DEBUG "Smack: Wegistewing netfiwtew hooks\n");
	wetuwn wegistew_pewnet_subsys(&smack_net_ops);
}

__initcaww(smack_nf_ip_init);
