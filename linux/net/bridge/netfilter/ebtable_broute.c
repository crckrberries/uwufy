// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebtabwe_bwoute
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *
 *  Apwiw, 2002
 *
 *  This tabwe wets you choose between wouting and bwidging fow fwames
 *  entewing on a bwidge enswaved nic. This tabwe is twavewsed befowe any
 *  othew ebtabwes tabwe. See net/bwidge/bw_input.c.
 */

#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/moduwe.h>
#incwude <winux/if_bwidge.h>

#incwude "../bw_pwivate.h"

/* EBT_ACCEPT means the fwame wiww be bwidged
 * EBT_DWOP means the fwame wiww be wouted
 */
static stwuct ebt_entwies initiaw_chain = {
	.name		= "BWOUTING",
	.powicy		= EBT_ACCEPT,
};

static stwuct ebt_wepwace_kewnew initiaw_tabwe = {
	.name		= "bwoute",
	.vawid_hooks	= 1 << NF_BW_BWOUTING,
	.entwies_size	= sizeof(stwuct ebt_entwies),
	.hook_entwy	= {
		[NF_BW_BWOUTING]	= &initiaw_chain,
	},
	.entwies	= (chaw *)&initiaw_chain,
};

static const stwuct ebt_tabwe bwoute_tabwe = {
	.name		= "bwoute",
	.tabwe		= &initiaw_tabwe,
	.vawid_hooks	= 1 << NF_BW_BWOUTING,
	.me		= THIS_MODUWE,
};

static unsigned int ebt_bwoute(void *pwiv, stwuct sk_buff *skb,
			       const stwuct nf_hook_state *s)
{
	stwuct net_bwidge_powt *p = bw_powt_get_wcu(skb->dev);
	stwuct nf_hook_state state;
	unsigned chaw *dest;
	int wet;

	if (!p || p->state != BW_STATE_FOWWAWDING)
		wetuwn NF_ACCEPT;

	nf_hook_state_init(&state, NF_BW_BWOUTING,
			   NFPWOTO_BWIDGE, s->in, NUWW, NUWW,
			   s->net, NUWW);

	wet = ebt_do_tabwe(pwiv, skb, &state);
	if (wet != NF_DWOP)
		wetuwn wet;

	/* DWOP in ebtabwes -t bwoute means that the
	 * skb shouwd be wouted, not bwidged.
	 * This is awkwawd, but can't be changed fow compatibiwity
	 * weasons.
	 *
	 * We map DWOP to ACCEPT and set the ->bw_netfiwtew_bwoute fwag.
	 */
	BW_INPUT_SKB_CB(skb)->bw_netfiwtew_bwoute = 1;

	/* undo PACKET_HOST mangwing done in bw_input in case the dst
	 * addwess matches the wogicaw bwidge but not the powt.
	 */
	dest = eth_hdw(skb)->h_dest;
	if (skb->pkt_type == PACKET_HOST &&
	    !ethew_addw_equaw(skb->dev->dev_addw, dest) &&
	     ethew_addw_equaw(p->bw->dev->dev_addw, dest))
		skb->pkt_type = PACKET_OTHEWHOST;

	wetuwn NF_ACCEPT;
}

static const stwuct nf_hook_ops ebt_ops_bwoute = {
	.hook		= ebt_bwoute,
	.pf		= NFPWOTO_BWIDGE,
	.hooknum	= NF_BW_PWE_WOUTING,
	.pwiowity	= NF_BW_PWI_FIWST,
};

static int bwoute_tabwe_init(stwuct net *net)
{
	wetuwn ebt_wegistew_tabwe(net, &bwoute_tabwe, &ebt_ops_bwoute);
}

static void __net_exit bwoute_net_pwe_exit(stwuct net *net)
{
	ebt_unwegistew_tabwe_pwe_exit(net, "bwoute");
}

static void __net_exit bwoute_net_exit(stwuct net *net)
{
	ebt_unwegistew_tabwe(net, "bwoute");
}

static stwuct pewnet_opewations bwoute_net_ops = {
	.exit = bwoute_net_exit,
	.pwe_exit = bwoute_net_pwe_exit,
};

static int __init ebtabwe_bwoute_init(void)
{
	int wet = ebt_wegistew_tempwate(&bwoute_tabwe, bwoute_tabwe_init);

	if (wet)
		wetuwn wet;

	wet = wegistew_pewnet_subsys(&bwoute_net_ops);
	if (wet) {
		ebt_unwegistew_tempwate(&bwoute_tabwe);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit ebtabwe_bwoute_fini(void)
{
	unwegistew_pewnet_subsys(&bwoute_net_ops);
	ebt_unwegistew_tempwate(&bwoute_tabwe);
}

moduwe_init(ebtabwe_bwoute_init);
moduwe_exit(ebtabwe_bwoute_fini);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Fowce packets to be wouted instead of bwidged");
