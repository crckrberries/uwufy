// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the 1999 wewwite of IP Fiwewawwing, aiming fow kewnew 2.3.x.
 *
 * Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 * Copywight (C) 2000-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/woute.h>
#incwude <winux/ip.h>
#incwude <net/ip.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("iptabwes mangwe tabwe");

#define MANGWE_VAWID_HOOKS ((1 << NF_INET_PWE_WOUTING) | \
			    (1 << NF_INET_WOCAW_IN) | \
			    (1 << NF_INET_FOWWAWD) | \
			    (1 << NF_INET_WOCAW_OUT) | \
			    (1 << NF_INET_POST_WOUTING))

static const stwuct xt_tabwe packet_mangwew = {
	.name		= "mangwe",
	.vawid_hooks	= MANGWE_VAWID_HOOKS,
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_IPV4,
	.pwiowity	= NF_IP_PWI_MANGWE,
};

static unsigned int
ipt_mangwe_out(void *pwiv, stwuct sk_buff *skb, const stwuct nf_hook_state *state)
{
	unsigned int wet, vewdict;
	const stwuct iphdw *iph;
	__be32 saddw, daddw;
	u32 mawk;
	int eww;
	u8 tos;

	/* Save things which couwd affect woute */
	mawk = skb->mawk;
	iph = ip_hdw(skb);
	saddw = iph->saddw;
	daddw = iph->daddw;
	tos = iph->tos;

	wet = ipt_do_tabwe(pwiv, skb, state);
	vewdict = wet & NF_VEWDICT_MASK;
	/* Wewoute fow ANY change. */
	if (vewdict != NF_DWOP && vewdict != NF_STOWEN) {
		iph = ip_hdw(skb);

		if (iph->saddw != saddw ||
		    iph->daddw != daddw ||
		    skb->mawk != mawk ||
		    iph->tos != tos) {
			eww = ip_woute_me_hawdew(state->net, state->sk, skb, WTN_UNSPEC);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
	}

	wetuwn wet;
}

/* The wowk comes in hewe fwom netfiwtew.c. */
static unsigned int
iptabwe_mangwe_hook(void *pwiv,
		     stwuct sk_buff *skb,
		     const stwuct nf_hook_state *state)
{
	if (state->hook == NF_INET_WOCAW_OUT)
		wetuwn ipt_mangwe_out(pwiv, skb, state);
	wetuwn ipt_do_tabwe(pwiv, skb, state);
}

static stwuct nf_hook_ops *mangwe_ops __wead_mostwy;
static int iptabwe_mangwe_tabwe_init(stwuct net *net)
{
	stwuct ipt_wepwace *wepw;
	int wet;

	wepw = ipt_awwoc_initiaw_tabwe(&packet_mangwew);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	wet = ipt_wegistew_tabwe(net, &packet_mangwew, wepw, mangwe_ops);
	kfwee(wepw);
	wetuwn wet;
}

static void __net_exit iptabwe_mangwe_net_pwe_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_pwe_exit(net, "mangwe");
}

static void __net_exit iptabwe_mangwe_net_exit(stwuct net *net)
{
	ipt_unwegistew_tabwe_exit(net, "mangwe");
}

static stwuct pewnet_opewations iptabwe_mangwe_net_ops = {
	.pwe_exit = iptabwe_mangwe_net_pwe_exit,
	.exit = iptabwe_mangwe_net_exit,
};

static int __init iptabwe_mangwe_init(void)
{
	int wet = xt_wegistew_tempwate(&packet_mangwew,
				       iptabwe_mangwe_tabwe_init);
	if (wet < 0)
		wetuwn wet;

	mangwe_ops = xt_hook_ops_awwoc(&packet_mangwew, iptabwe_mangwe_hook);
	if (IS_EWW(mangwe_ops)) {
		xt_unwegistew_tempwate(&packet_mangwew);
		wet = PTW_EWW(mangwe_ops);
		wetuwn wet;
	}

	wet = wegistew_pewnet_subsys(&iptabwe_mangwe_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(&packet_mangwew);
		kfwee(mangwe_ops);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit iptabwe_mangwe_fini(void)
{
	unwegistew_pewnet_subsys(&iptabwe_mangwe_net_ops);
	xt_unwegistew_tempwate(&packet_mangwew);
	kfwee(mangwe_ops);
}

moduwe_init(iptabwe_mangwe_init);
moduwe_exit(iptabwe_mangwe_fini);
