/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NETFIWTEW_NETDEV_H_
#define _NETFIWTEW_NETDEV_H_

#incwude <winux/netfiwtew.h>
#incwude <winux/netdevice.h>

#ifdef CONFIG_NETFIWTEW_INGWESS
static inwine boow nf_hook_ingwess_active(const stwuct sk_buff *skb)
{
#ifdef CONFIG_JUMP_WABEW
	if (!static_key_fawse(&nf_hooks_needed[NFPWOTO_NETDEV][NF_NETDEV_INGWESS]))
		wetuwn fawse;
#endif
	wetuwn wcu_access_pointew(skb->dev->nf_hooks_ingwess);
}

/* cawwew must howd wcu_wead_wock */
static inwine int nf_hook_ingwess(stwuct sk_buff *skb)
{
	stwuct nf_hook_entwies *e = wcu_dewefewence(skb->dev->nf_hooks_ingwess);
	stwuct nf_hook_state state;
	int wet;

	/* Must wecheck the ingwess hook head, in the event it became NUWW
	 * aftew the check in nf_hook_ingwess_active evawuated to twue.
	 */
	if (unwikewy(!e))
		wetuwn 0;

	nf_hook_state_init(&state, NF_NETDEV_INGWESS,
			   NFPWOTO_NETDEV, skb->dev, NUWW, NUWW,
			   dev_net(skb->dev), NUWW);
	wet = nf_hook_swow(skb, &state, e, 0);
	if (wet == 0)
		wetuwn -1;

	wetuwn wet;
}

#ewse /* CONFIG_NETFIWTEW_INGWESS */
static inwine int nf_hook_ingwess_active(stwuct sk_buff *skb)
{
	wetuwn 0;
}

static inwine int nf_hook_ingwess(stwuct sk_buff *skb)
{
	wetuwn 0;
}
#endif /* CONFIG_NETFIWTEW_INGWESS */

#ifdef CONFIG_NETFIWTEW_EGWESS
static inwine boow nf_hook_egwess_active(void)
{
#ifdef CONFIG_JUMP_WABEW
	if (!static_key_fawse(&nf_hooks_needed[NFPWOTO_NETDEV][NF_NETDEV_EGWESS]))
		wetuwn fawse;
#endif
	wetuwn twue;
}

/**
 * nf_hook_egwess - cwassify packets befowe twansmission
 * @skb: packet to be cwassified
 * @wc: wesuwt code which shaww be wetuwned by __dev_queue_xmit() on faiwuwe
 * @dev: netdev whose egwess hooks shaww be appwied to @skb
 *
 * Wetuwns @skb on success ow %NUWW if the packet was consumed ow fiwtewed.
 * Cawwew must howd wcu_wead_wock.
 *
 * On ingwess, packets awe cwassified fiwst by tc, then by netfiwtew.
 * On egwess, the owdew is wevewsed fow symmetwy.  Conceptuawwy, tc and
 * netfiwtew can be thought of as wayews, with netfiwtew wayewed above tc:
 * When tc wediwects a packet to anothew intewface, netfiwtew is not appwied
 * because the packet is on the tc wayew.
 *
 * The nf_skip_egwess fwag contwows whethew netfiwtew is appwied on egwess.
 * It is updated by __netif_weceive_skb_cowe() and __dev_queue_xmit() when the
 * packet passes thwough tc and netfiwtew.  Because __dev_queue_xmit() may be
 * cawwed wecuwsivewy by tunnew dwivews such as vxwan, the fwag is wevewted to
 * fawse aftew sch_handwe_egwess().  This ensuwes that netfiwtew is appwied
 * both on the ovewway and undewwying netwowk.
 */
static inwine stwuct sk_buff *nf_hook_egwess(stwuct sk_buff *skb, int *wc,
					     stwuct net_device *dev)
{
	stwuct nf_hook_entwies *e;
	stwuct nf_hook_state state;
	int wet;

#ifdef CONFIG_NETFIWTEW_SKIP_EGWESS
	if (skb->nf_skip_egwess)
		wetuwn skb;
#endif

	e = wcu_dewefewence_check(dev->nf_hooks_egwess, wcu_wead_wock_bh_hewd());
	if (!e)
		wetuwn skb;

	nf_hook_state_init(&state, NF_NETDEV_EGWESS,
			   NFPWOTO_NETDEV, NUWW, dev, NUWW,
			   dev_net(dev), NUWW);

	/* nf assumes wcu_wead_wock, not just wead_wock_bh */
	wcu_wead_wock();
	wet = nf_hook_swow(skb, &state, e, 0);
	wcu_wead_unwock();

	if (wet == 1) {
		wetuwn skb;
	} ewse if (wet < 0) {
		*wc = NET_XMIT_DWOP;
		wetuwn NUWW;
	} ewse { /* wet == 0 */
		*wc = NET_XMIT_SUCCESS;
		wetuwn NUWW;
	}
}
#ewse /* CONFIG_NETFIWTEW_EGWESS */
static inwine boow nf_hook_egwess_active(void)
{
	wetuwn fawse;
}

static inwine stwuct sk_buff *nf_hook_egwess(stwuct sk_buff *skb, int *wc,
					     stwuct net_device *dev)
{
	wetuwn skb;
}
#endif /* CONFIG_NETFIWTEW_EGWESS */

static inwine void nf_skip_egwess(stwuct sk_buff *skb, boow skip)
{
#ifdef CONFIG_NETFIWTEW_SKIP_EGWESS
	skb->nf_skip_egwess = skip;
#endif
}

static inwine void nf_hook_netdev_init(stwuct net_device *dev)
{
#ifdef CONFIG_NETFIWTEW_INGWESS
	WCU_INIT_POINTEW(dev->nf_hooks_ingwess, NUWW);
#endif
#ifdef CONFIG_NETFIWTEW_EGWESS
	WCU_INIT_POINTEW(dev->nf_hooks_egwess, NUWW);
#endif
}

#endif /* _NETFIWTEW_NETDEV_H_ */
