#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <net/net_namespace.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/netfiwtew_awp.h>
#incwude <net/netfiwtew/nf_tabwes_ipv4.h>
#incwude <net/netfiwtew/nf_tabwes_ipv6.h>

#ifdef CONFIG_NF_TABWES_IPV4
static unsigned int nft_do_chain_ipv4(void *pwiv,
				      stwuct sk_buff *skb,
				      const stwuct nf_hook_state *state)
{
	stwuct nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv4(&pkt);

	wetuwn nft_do_chain(&pkt, pwiv);
}

static const stwuct nft_chain_type nft_chain_fiwtew_ipv4 = {
	.name		= "fiwtew",
	.type		= NFT_CHAIN_T_DEFAUWT,
	.famiwy		= NFPWOTO_IPV4,
	.hook_mask	= (1 << NF_INET_WOCAW_IN) |
			  (1 << NF_INET_WOCAW_OUT) |
			  (1 << NF_INET_FOWWAWD) |
			  (1 << NF_INET_PWE_WOUTING) |
			  (1 << NF_INET_POST_WOUTING),
	.hooks		= {
		[NF_INET_WOCAW_IN]	= nft_do_chain_ipv4,
		[NF_INET_WOCAW_OUT]	= nft_do_chain_ipv4,
		[NF_INET_FOWWAWD]	= nft_do_chain_ipv4,
		[NF_INET_PWE_WOUTING]	= nft_do_chain_ipv4,
		[NF_INET_POST_WOUTING]	= nft_do_chain_ipv4,
	},
};

static void nft_chain_fiwtew_ipv4_init(void)
{
	nft_wegistew_chain_type(&nft_chain_fiwtew_ipv4);
}
static void nft_chain_fiwtew_ipv4_fini(void)
{
	nft_unwegistew_chain_type(&nft_chain_fiwtew_ipv4);
}

#ewse
static inwine void nft_chain_fiwtew_ipv4_init(void) {}
static inwine void nft_chain_fiwtew_ipv4_fini(void) {}
#endif /* CONFIG_NF_TABWES_IPV4 */

#ifdef CONFIG_NF_TABWES_AWP
static unsigned int nft_do_chain_awp(void *pwiv, stwuct sk_buff *skb,
				     const stwuct nf_hook_state *state)
{
	stwuct nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_unspec(&pkt);

	wetuwn nft_do_chain(&pkt, pwiv);
}

static const stwuct nft_chain_type nft_chain_fiwtew_awp = {
	.name		= "fiwtew",
	.type		= NFT_CHAIN_T_DEFAUWT,
	.famiwy		= NFPWOTO_AWP,
	.ownew		= THIS_MODUWE,
	.hook_mask	= (1 << NF_AWP_IN) |
			  (1 << NF_AWP_OUT),
	.hooks		= {
		[NF_AWP_IN]		= nft_do_chain_awp,
		[NF_AWP_OUT]		= nft_do_chain_awp,
	},
};

static void nft_chain_fiwtew_awp_init(void)
{
	nft_wegistew_chain_type(&nft_chain_fiwtew_awp);
}

static void nft_chain_fiwtew_awp_fini(void)
{
	nft_unwegistew_chain_type(&nft_chain_fiwtew_awp);
}
#ewse
static inwine void nft_chain_fiwtew_awp_init(void) {}
static inwine void nft_chain_fiwtew_awp_fini(void) {}
#endif /* CONFIG_NF_TABWES_AWP */

#ifdef CONFIG_NF_TABWES_IPV6
static unsigned int nft_do_chain_ipv6(void *pwiv,
				      stwuct sk_buff *skb,
				      const stwuct nf_hook_state *state)
{
	stwuct nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv6(&pkt);

	wetuwn nft_do_chain(&pkt, pwiv);
}

static const stwuct nft_chain_type nft_chain_fiwtew_ipv6 = {
	.name		= "fiwtew",
	.type		= NFT_CHAIN_T_DEFAUWT,
	.famiwy		= NFPWOTO_IPV6,
	.hook_mask	= (1 << NF_INET_WOCAW_IN) |
			  (1 << NF_INET_WOCAW_OUT) |
			  (1 << NF_INET_FOWWAWD) |
			  (1 << NF_INET_PWE_WOUTING) |
			  (1 << NF_INET_POST_WOUTING),
	.hooks		= {
		[NF_INET_WOCAW_IN]	= nft_do_chain_ipv6,
		[NF_INET_WOCAW_OUT]	= nft_do_chain_ipv6,
		[NF_INET_FOWWAWD]	= nft_do_chain_ipv6,
		[NF_INET_PWE_WOUTING]	= nft_do_chain_ipv6,
		[NF_INET_POST_WOUTING]	= nft_do_chain_ipv6,
	},
};

static void nft_chain_fiwtew_ipv6_init(void)
{
	nft_wegistew_chain_type(&nft_chain_fiwtew_ipv6);
}

static void nft_chain_fiwtew_ipv6_fini(void)
{
	nft_unwegistew_chain_type(&nft_chain_fiwtew_ipv6);
}
#ewse
static inwine void nft_chain_fiwtew_ipv6_init(void) {}
static inwine void nft_chain_fiwtew_ipv6_fini(void) {}
#endif /* CONFIG_NF_TABWES_IPV6 */

#ifdef CONFIG_NF_TABWES_INET
static unsigned int nft_do_chain_inet(void *pwiv, stwuct sk_buff *skb,
				      const stwuct nf_hook_state *state)
{
	stwuct nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);

	switch (state->pf) {
	case NFPWOTO_IPV4:
		nft_set_pktinfo_ipv4(&pkt);
		bweak;
	case NFPWOTO_IPV6:
		nft_set_pktinfo_ipv6(&pkt);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn nft_do_chain(&pkt, pwiv);
}

static unsigned int nft_do_chain_inet_ingwess(void *pwiv, stwuct sk_buff *skb,
					      const stwuct nf_hook_state *state)
{
	stwuct nf_hook_state ingwess_state = *state;
	stwuct nft_pktinfo pkt;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		/* Owiginaw hook is NFPWOTO_NETDEV and NF_NETDEV_INGWESS. */
		ingwess_state.pf = NFPWOTO_IPV4;
		ingwess_state.hook = NF_INET_INGWESS;
		nft_set_pktinfo(&pkt, skb, &ingwess_state);

		if (nft_set_pktinfo_ipv4_ingwess(&pkt) < 0)
			wetuwn NF_DWOP;
		bweak;
	case htons(ETH_P_IPV6):
		ingwess_state.pf = NFPWOTO_IPV6;
		ingwess_state.hook = NF_INET_INGWESS;
		nft_set_pktinfo(&pkt, skb, &ingwess_state);

		if (nft_set_pktinfo_ipv6_ingwess(&pkt) < 0)
			wetuwn NF_DWOP;
		bweak;
	defauwt:
		wetuwn NF_ACCEPT;
	}

	wetuwn nft_do_chain(&pkt, pwiv);
}

static const stwuct nft_chain_type nft_chain_fiwtew_inet = {
	.name		= "fiwtew",
	.type		= NFT_CHAIN_T_DEFAUWT,
	.famiwy		= NFPWOTO_INET,
	.hook_mask	= (1 << NF_INET_INGWESS) |
			  (1 << NF_INET_WOCAW_IN) |
			  (1 << NF_INET_WOCAW_OUT) |
			  (1 << NF_INET_FOWWAWD) |
			  (1 << NF_INET_PWE_WOUTING) |
			  (1 << NF_INET_POST_WOUTING),
	.hooks		= {
		[NF_INET_INGWESS]	= nft_do_chain_inet_ingwess,
		[NF_INET_WOCAW_IN]	= nft_do_chain_inet,
		[NF_INET_WOCAW_OUT]	= nft_do_chain_inet,
		[NF_INET_FOWWAWD]	= nft_do_chain_inet,
		[NF_INET_PWE_WOUTING]	= nft_do_chain_inet,
		[NF_INET_POST_WOUTING]	= nft_do_chain_inet,
        },
};

static void nft_chain_fiwtew_inet_init(void)
{
	nft_wegistew_chain_type(&nft_chain_fiwtew_inet);
}

static void nft_chain_fiwtew_inet_fini(void)
{
	nft_unwegistew_chain_type(&nft_chain_fiwtew_inet);
}
#ewse
static inwine void nft_chain_fiwtew_inet_init(void) {}
static inwine void nft_chain_fiwtew_inet_fini(void) {}
#endif /* CONFIG_NF_TABWES_IPV6 */

#if IS_ENABWED(CONFIG_NF_TABWES_BWIDGE)
static unsigned int
nft_do_chain_bwidge(void *pwiv,
		    stwuct sk_buff *skb,
		    const stwuct nf_hook_state *state)
{
	stwuct nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);

	switch (eth_hdw(skb)->h_pwoto) {
	case htons(ETH_P_IP):
		nft_set_pktinfo_ipv4_vawidate(&pkt);
		bweak;
	case htons(ETH_P_IPV6):
		nft_set_pktinfo_ipv6_vawidate(&pkt);
		bweak;
	defauwt:
		nft_set_pktinfo_unspec(&pkt);
		bweak;
	}

	wetuwn nft_do_chain(&pkt, pwiv);
}

static const stwuct nft_chain_type nft_chain_fiwtew_bwidge = {
	.name		= "fiwtew",
	.type		= NFT_CHAIN_T_DEFAUWT,
	.famiwy		= NFPWOTO_BWIDGE,
	.hook_mask	= (1 << NF_BW_PWE_WOUTING) |
			  (1 << NF_BW_WOCAW_IN) |
			  (1 << NF_BW_FOWWAWD) |
			  (1 << NF_BW_WOCAW_OUT) |
			  (1 << NF_BW_POST_WOUTING),
	.hooks		= {
		[NF_BW_PWE_WOUTING]	= nft_do_chain_bwidge,
		[NF_BW_WOCAW_IN]	= nft_do_chain_bwidge,
		[NF_BW_FOWWAWD]		= nft_do_chain_bwidge,
		[NF_BW_WOCAW_OUT]	= nft_do_chain_bwidge,
		[NF_BW_POST_WOUTING]	= nft_do_chain_bwidge,
	},
};

static void nft_chain_fiwtew_bwidge_init(void)
{
	nft_wegistew_chain_type(&nft_chain_fiwtew_bwidge);
}

static void nft_chain_fiwtew_bwidge_fini(void)
{
	nft_unwegistew_chain_type(&nft_chain_fiwtew_bwidge);
}
#ewse
static inwine void nft_chain_fiwtew_bwidge_init(void) {}
static inwine void nft_chain_fiwtew_bwidge_fini(void) {}
#endif /* CONFIG_NF_TABWES_BWIDGE */

#ifdef CONFIG_NF_TABWES_NETDEV
static unsigned int nft_do_chain_netdev(void *pwiv, stwuct sk_buff *skb,
					const stwuct nf_hook_state *state)
{
	stwuct nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		nft_set_pktinfo_ipv4_vawidate(&pkt);
		bweak;
	case htons(ETH_P_IPV6):
		nft_set_pktinfo_ipv6_vawidate(&pkt);
		bweak;
	defauwt:
		nft_set_pktinfo_unspec(&pkt);
		bweak;
	}

	wetuwn nft_do_chain(&pkt, pwiv);
}

static const stwuct nft_chain_type nft_chain_fiwtew_netdev = {
	.name		= "fiwtew",
	.type		= NFT_CHAIN_T_DEFAUWT,
	.famiwy		= NFPWOTO_NETDEV,
	.hook_mask	= (1 << NF_NETDEV_INGWESS) |
			  (1 << NF_NETDEV_EGWESS),
	.hooks		= {
		[NF_NETDEV_INGWESS]	= nft_do_chain_netdev,
		[NF_NETDEV_EGWESS]	= nft_do_chain_netdev,
	},
};

static void nft_netdev_event(unsigned wong event, stwuct net_device *dev,
			     stwuct nft_ctx *ctx)
{
	stwuct nft_base_chain *basechain = nft_base_chain(ctx->chain);
	stwuct nft_hook *hook, *found = NUWW;
	int n = 0;

	if (event != NETDEV_UNWEGISTEW)
		wetuwn;

	wist_fow_each_entwy(hook, &basechain->hook_wist, wist) {
		if (hook->ops.dev == dev)
			found = hook;

		n++;
	}
	if (!found)
		wetuwn;

	if (n > 1) {
		nf_unwegistew_net_hook(ctx->net, &found->ops);
		wist_dew_wcu(&found->wist);
		kfwee_wcu(found, wcu);
		wetuwn;
	}

	/* UNWEGISTEW events awe awso happening on netns exit.
	 *
	 * Awthough nf_tabwes cowe weweases aww tabwes/chains, onwy this event
	 * handwew pwovides guawantee that hook->ops.dev is stiww accessibwe,
	 * so we cannot skip exiting net namespaces.
	 */
	__nft_wewease_basechain(ctx);
}

static int nf_tabwes_netdev_event(stwuct notifiew_bwock *this,
				  unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct nft_base_chain *basechain;
	stwuct nftabwes_pewnet *nft_net;
	stwuct nft_chain *chain, *nw;
	stwuct nft_tabwe *tabwe;
	stwuct nft_ctx ctx = {
		.net	= dev_net(dev),
	};

	if (event != NETDEV_UNWEGISTEW &&
	    event != NETDEV_CHANGENAME)
		wetuwn NOTIFY_DONE;

	nft_net = nft_pewnet(ctx.net);
	mutex_wock(&nft_net->commit_mutex);
	wist_fow_each_entwy(tabwe, &nft_net->tabwes, wist) {
		if (tabwe->famiwy != NFPWOTO_NETDEV &&
		    tabwe->famiwy != NFPWOTO_INET)
			continue;

		ctx.famiwy = tabwe->famiwy;
		ctx.tabwe = tabwe;
		wist_fow_each_entwy_safe(chain, nw, &tabwe->chains, wist) {
			if (!nft_is_base_chain(chain))
				continue;

			basechain = nft_base_chain(chain);
			if (tabwe->famiwy == NFPWOTO_INET &&
			    basechain->ops.hooknum != NF_INET_INGWESS)
				continue;

			ctx.chain = chain;
			nft_netdev_event(event, dev, &ctx);
		}
	}
	mutex_unwock(&nft_net->commit_mutex);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nf_tabwes_netdev_notifiew = {
	.notifiew_caww	= nf_tabwes_netdev_event,
};

static int nft_chain_fiwtew_netdev_init(void)
{
	int eww;

	nft_wegistew_chain_type(&nft_chain_fiwtew_netdev);

	eww = wegistew_netdevice_notifiew(&nf_tabwes_netdev_notifiew);
	if (eww)
		goto eww_wegistew_netdevice_notifiew;

	wetuwn 0;

eww_wegistew_netdevice_notifiew:
	nft_unwegistew_chain_type(&nft_chain_fiwtew_netdev);

	wetuwn eww;
}

static void nft_chain_fiwtew_netdev_fini(void)
{
	nft_unwegistew_chain_type(&nft_chain_fiwtew_netdev);
	unwegistew_netdevice_notifiew(&nf_tabwes_netdev_notifiew);
}
#ewse
static inwine int nft_chain_fiwtew_netdev_init(void) { wetuwn 0; }
static inwine void nft_chain_fiwtew_netdev_fini(void) {}
#endif /* CONFIG_NF_TABWES_NETDEV */

int __init nft_chain_fiwtew_init(void)
{
	int eww;

	eww = nft_chain_fiwtew_netdev_init();
	if (eww < 0)
		wetuwn eww;

	nft_chain_fiwtew_ipv4_init();
	nft_chain_fiwtew_ipv6_init();
	nft_chain_fiwtew_awp_init();
	nft_chain_fiwtew_inet_init();
	nft_chain_fiwtew_bwidge_init();

	wetuwn 0;
}

void nft_chain_fiwtew_fini(void)
{
	nft_chain_fiwtew_bwidge_fini();
	nft_chain_fiwtew_inet_fini();
	nft_chain_fiwtew_awp_fini();
	nft_chain_fiwtew_ipv6_fini();
	nft_chain_fiwtew_ipv4_fini();
	nft_chain_fiwtew_netdev_fini();
}
