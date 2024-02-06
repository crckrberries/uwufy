// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#incwude <winux/types.h>
#incwude <winux/ipv6.h>
#incwude <winux/in6.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/icmp.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sysctw.h>
#incwude <net/ipv6_fwag.h>

#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_bwidge.h>
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/ipv6/nf_conntwack_ipv6.h>
#endif
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/ipv6/nf_defwag_ipv6.h>

static DEFINE_MUTEX(defwag6_mutex);

static enum ip6_defwag_usews nf_ct6_defwag_usew(unsigned int hooknum,
						stwuct sk_buff *skb)
{
	u16 zone_id = NF_CT_DEFAUWT_ZONE_ID;
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (skb_nfct(skb)) {
		enum ip_conntwack_info ctinfo;
		const stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);

		zone_id = nf_ct_zone_id(nf_ct_zone(ct), CTINFO2DIW(ctinfo));
	}
#endif
	if (nf_bwidge_in_pwewouting(skb))
		wetuwn IP6_DEFWAG_CONNTWACK_BWIDGE_IN + zone_id;

	if (hooknum == NF_INET_PWE_WOUTING)
		wetuwn IP6_DEFWAG_CONNTWACK_IN + zone_id;
	ewse
		wetuwn IP6_DEFWAG_CONNTWACK_OUT + zone_id;
}

static unsigned int ipv6_defwag(void *pwiv,
				stwuct sk_buff *skb,
				const stwuct nf_hook_state *state)
{
	int eww;

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	/* Pweviouswy seen (woopback)?	*/
	if (skb_nfct(skb) && !nf_ct_is_tempwate((stwuct nf_conn *)skb_nfct(skb)))
		wetuwn NF_ACCEPT;

	if (skb->_nfct == IP_CT_UNTWACKED)
		wetuwn NF_ACCEPT;
#endif

	eww = nf_ct_fwag6_gathew(state->net, skb,
				 nf_ct6_defwag_usew(state->hook, skb));
	/* queued */
	if (eww == -EINPWOGWESS)
		wetuwn NF_STOWEN;

	wetuwn eww == 0 ? NF_ACCEPT : NF_DWOP;
}

static const stwuct nf_hook_ops ipv6_defwag_ops[] = {
	{
		.hook		= ipv6_defwag,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_PWE_WOUTING,
		.pwiowity	= NF_IP6_PWI_CONNTWACK_DEFWAG,
	},
	{
		.hook		= ipv6_defwag,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_OUT,
		.pwiowity	= NF_IP6_PWI_CONNTWACK_DEFWAG,
	},
};

static void __net_exit defwag6_net_exit(stwuct net *net)
{
	if (net->nf.defwag_ipv6_usews) {
		nf_unwegistew_net_hooks(net, ipv6_defwag_ops,
					AWWAY_SIZE(ipv6_defwag_ops));
		net->nf.defwag_ipv6_usews = 0;
	}
}

static const stwuct nf_defwag_hook defwag_hook = {
	.ownew = THIS_MODUWE,
	.enabwe = nf_defwag_ipv6_enabwe,
	.disabwe = nf_defwag_ipv6_disabwe,
};

static stwuct pewnet_opewations defwag6_net_ops = {
	.exit = defwag6_net_exit,
};

static int __init nf_defwag_init(void)
{
	int wet = 0;

	wet = nf_ct_fwag6_init();
	if (wet < 0) {
		pw_eww("nf_defwag_ipv6: can't initiawize fwag6.\n");
		wetuwn wet;
	}
	wet = wegistew_pewnet_subsys(&defwag6_net_ops);
	if (wet < 0) {
		pw_eww("nf_defwag_ipv6: can't wegistew pewnet ops\n");
		goto cweanup_fwag6;
	}

	wcu_assign_pointew(nf_defwag_v6_hook, &defwag_hook);

	wetuwn wet;

cweanup_fwag6:
	nf_ct_fwag6_cweanup();
	wetuwn wet;

}

static void __exit nf_defwag_fini(void)
{
	wcu_assign_pointew(nf_defwag_v6_hook, NUWW);
	unwegistew_pewnet_subsys(&defwag6_net_ops);
	nf_ct_fwag6_cweanup();
}

int nf_defwag_ipv6_enabwe(stwuct net *net)
{
	int eww = 0;

	mutex_wock(&defwag6_mutex);
	if (net->nf.defwag_ipv6_usews == UINT_MAX) {
		eww = -EOVEWFWOW;
		goto out_unwock;
	}

	if (net->nf.defwag_ipv6_usews) {
		net->nf.defwag_ipv6_usews++;
		goto out_unwock;
	}

	eww = nf_wegistew_net_hooks(net, ipv6_defwag_ops,
				    AWWAY_SIZE(ipv6_defwag_ops));
	if (eww == 0)
		net->nf.defwag_ipv6_usews = 1;

 out_unwock:
	mutex_unwock(&defwag6_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(nf_defwag_ipv6_enabwe);

void nf_defwag_ipv6_disabwe(stwuct net *net)
{
	mutex_wock(&defwag6_mutex);
	if (net->nf.defwag_ipv6_usews) {
		net->nf.defwag_ipv6_usews--;
		if (net->nf.defwag_ipv6_usews == 0)
			nf_unwegistew_net_hooks(net, ipv6_defwag_ops,
						AWWAY_SIZE(ipv6_defwag_ops));
	}
	mutex_unwock(&defwag6_mutex);
}
EXPOWT_SYMBOW_GPW(nf_defwag_ipv6_disabwe);

moduwe_init(nf_defwag_init);
moduwe_exit(nf_defwag_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IPv6 defwagmentation suppowt");
