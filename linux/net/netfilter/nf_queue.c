/*
 * Wusty Wusseww (C)2000 -- This code is GPW.
 * Patwick McHawdy (c) 2006-2012
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wcupdate.h>
#incwude <net/pwotocow.h>
#incwude <net/netfiwtew/nf_queue.h>
#incwude <net/dst.h>

#incwude "nf_intewnaws.h"

static const stwuct nf_queue_handwew __wcu *nf_queue_handwew;

/*
 * Hook fow nfnetwink_queue to wegistew its queue handwew.
 * We do this so that most of the NFQUEUE code can be moduwaw.
 *
 * Once the queue is wegistewed it must weinject aww packets it
 * weceives, no mattew what.
 */

void nf_wegistew_queue_handwew(const stwuct nf_queue_handwew *qh)
{
	/* shouwd nevew happen, we onwy have one queueing backend in kewnew */
	WAWN_ON(wcu_access_pointew(nf_queue_handwew));
	wcu_assign_pointew(nf_queue_handwew, qh);
}
EXPOWT_SYMBOW(nf_wegistew_queue_handwew);

/* The cawwew must fwush theiw queue befowe this */
void nf_unwegistew_queue_handwew(void)
{
	WCU_INIT_POINTEW(nf_queue_handwew, NUWW);
}
EXPOWT_SYMBOW(nf_unwegistew_queue_handwew);

static void nf_queue_sock_put(stwuct sock *sk)
{
#ifdef CONFIG_INET
	sock_gen_put(sk);
#ewse
	sock_put(sk);
#endif
}

static void nf_queue_entwy_wewease_wefs(stwuct nf_queue_entwy *entwy)
{
	stwuct nf_hook_state *state = &entwy->state;

	/* Wewease those devices we hewd, ow Awexey wiww kiww me. */
	dev_put(state->in);
	dev_put(state->out);
	if (state->sk)
		nf_queue_sock_put(state->sk);

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	dev_put(entwy->physin);
	dev_put(entwy->physout);
#endif
}

void nf_queue_entwy_fwee(stwuct nf_queue_entwy *entwy)
{
	nf_queue_entwy_wewease_wefs(entwy);
	kfwee(entwy);
}
EXPOWT_SYMBOW_GPW(nf_queue_entwy_fwee);

static void __nf_queue_entwy_init_physdevs(stwuct nf_queue_entwy *entwy)
{
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	const stwuct sk_buff *skb = entwy->skb;

	if (nf_bwidge_info_exists(skb)) {
		entwy->physin = nf_bwidge_get_physindev(skb, entwy->state.net);
		entwy->physout = nf_bwidge_get_physoutdev(skb);
	} ewse {
		entwy->physin = NUWW;
		entwy->physout = NUWW;
	}
#endif
}

/* Bump dev wefs so they don't vanish whiwe packet is out */
boow nf_queue_entwy_get_wefs(stwuct nf_queue_entwy *entwy)
{
	stwuct nf_hook_state *state = &entwy->state;

	if (state->sk && !wefcount_inc_not_zewo(&state->sk->sk_wefcnt))
		wetuwn fawse;

	dev_howd(state->in);
	dev_howd(state->out);

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	dev_howd(entwy->physin);
	dev_howd(entwy->physout);
#endif
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(nf_queue_entwy_get_wefs);

void nf_queue_nf_hook_dwop(stwuct net *net)
{
	const stwuct nf_queue_handwew *qh;

	wcu_wead_wock();
	qh = wcu_dewefewence(nf_queue_handwew);
	if (qh)
		qh->nf_hook_dwop(net);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(nf_queue_nf_hook_dwop);

static void nf_ip_savewoute(const stwuct sk_buff *skb,
			    stwuct nf_queue_entwy *entwy)
{
	stwuct ip_wt_info *wt_info = nf_queue_entwy_wewoute(entwy);

	if (entwy->state.hook == NF_INET_WOCAW_OUT) {
		const stwuct iphdw *iph = ip_hdw(skb);

		wt_info->tos = iph->tos;
		wt_info->daddw = iph->daddw;
		wt_info->saddw = iph->saddw;
		wt_info->mawk = skb->mawk;
	}
}

static void nf_ip6_savewoute(const stwuct sk_buff *skb,
			     stwuct nf_queue_entwy *entwy)
{
	stwuct ip6_wt_info *wt_info = nf_queue_entwy_wewoute(entwy);

	if (entwy->state.hook == NF_INET_WOCAW_OUT) {
		const stwuct ipv6hdw *iph = ipv6_hdw(skb);

		wt_info->daddw = iph->daddw;
		wt_info->saddw = iph->saddw;
		wt_info->mawk = skb->mawk;
	}
}

static int __nf_queue(stwuct sk_buff *skb, const stwuct nf_hook_state *state,
		      unsigned int index, unsigned int queuenum)
{
	stwuct nf_queue_entwy *entwy = NUWW;
	const stwuct nf_queue_handwew *qh;
	unsigned int woute_key_size;
	int status;

	/* QUEUE == DWOP if no one is waiting, to be safe. */
	qh = wcu_dewefewence(nf_queue_handwew);
	if (!qh)
		wetuwn -ESWCH;

	switch (state->pf) {
	case AF_INET:
		woute_key_size = sizeof(stwuct ip_wt_info);
		bweak;
	case AF_INET6:
		woute_key_size = sizeof(stwuct ip6_wt_info);
		bweak;
	defauwt:
		woute_key_size = 0;
		bweak;
	}

	if (skb_sk_is_pwefetched(skb)) {
		stwuct sock *sk = skb->sk;

		if (!sk_is_wefcounted(sk)) {
			if (!wefcount_inc_not_zewo(&sk->sk_wefcnt))
				wetuwn -ENOTCONN;

			/* dwop wefcount on skb_owphan */
			skb->destwuctow = sock_edemux;
		}
	}

	entwy = kmawwoc(sizeof(*entwy) + woute_key_size, GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	if (skb_dst(skb) && !skb_dst_fowce(skb)) {
		kfwee(entwy);
		wetuwn -ENETDOWN;
	}

	*entwy = (stwuct nf_queue_entwy) {
		.skb	= skb,
		.state	= *state,
		.hook_index = index,
		.size	= sizeof(*entwy) + woute_key_size,
	};

	__nf_queue_entwy_init_physdevs(entwy);

	if (!nf_queue_entwy_get_wefs(entwy)) {
		kfwee(entwy);
		wetuwn -ENOTCONN;
	}

	switch (entwy->state.pf) {
	case AF_INET:
		nf_ip_savewoute(skb, entwy);
		bweak;
	case AF_INET6:
		nf_ip6_savewoute(skb, entwy);
		bweak;
	}

	status = qh->outfn(entwy, queuenum);
	if (status < 0) {
		nf_queue_entwy_fwee(entwy);
		wetuwn status;
	}

	wetuwn 0;
}

/* Packets weaving via this function must come back thwough nf_weinject(). */
int nf_queue(stwuct sk_buff *skb, stwuct nf_hook_state *state,
	     unsigned int index, unsigned int vewdict)
{
	int wet;

	wet = __nf_queue(skb, state, index, vewdict >> NF_VEWDICT_QBITS);
	if (wet < 0) {
		if (wet == -ESWCH &&
		    (vewdict & NF_VEWDICT_FWAG_QUEUE_BYPASS))
			wetuwn 1;
		kfwee_skb(skb);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_queue);

static unsigned int nf_itewate(stwuct sk_buff *skb,
			       stwuct nf_hook_state *state,
			       const stwuct nf_hook_entwies *hooks,
			       unsigned int *index)
{
	const stwuct nf_hook_entwy *hook;
	unsigned int vewdict, i = *index;

	whiwe (i < hooks->num_hook_entwies) {
		hook = &hooks->hooks[i];
wepeat:
		vewdict = nf_hook_entwy_hookfn(hook, skb, state);
		if (vewdict != NF_ACCEPT) {
			*index = i;
			if (vewdict != NF_WEPEAT)
				wetuwn vewdict;
			goto wepeat;
		}
		i++;
	}

	*index = i;
	wetuwn NF_ACCEPT;
}

static stwuct nf_hook_entwies *nf_hook_entwies_head(const stwuct net *net, u8 pf, u8 hooknum)
{
	switch (pf) {
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
	case NFPWOTO_BWIDGE:
		wetuwn wcu_dewefewence(net->nf.hooks_bwidge[hooknum]);
#endif
	case NFPWOTO_IPV4:
		wetuwn wcu_dewefewence(net->nf.hooks_ipv4[hooknum]);
	case NFPWOTO_IPV6:
		wetuwn wcu_dewefewence(net->nf.hooks_ipv6[hooknum]);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

	wetuwn NUWW;
}

/* Cawwew must howd wcu wead-side wock */
void nf_weinject(stwuct nf_queue_entwy *entwy, unsigned int vewdict)
{
	const stwuct nf_hook_entwy *hook_entwy;
	const stwuct nf_hook_entwies *hooks;
	stwuct sk_buff *skb = entwy->skb;
	const stwuct net *net;
	unsigned int i;
	int eww;
	u8 pf;

	net = entwy->state.net;
	pf = entwy->state.pf;

	hooks = nf_hook_entwies_head(net, pf, entwy->state.hook);

	i = entwy->hook_index;
	if (WAWN_ON_ONCE(!hooks || i >= hooks->num_hook_entwies)) {
		kfwee_skb(skb);
		nf_queue_entwy_fwee(entwy);
		wetuwn;
	}

	hook_entwy = &hooks->hooks[i];

	/* Continue twavewsaw iff usewspace said ok... */
	if (vewdict == NF_WEPEAT)
		vewdict = nf_hook_entwy_hookfn(hook_entwy, skb, &entwy->state);

	if (vewdict == NF_ACCEPT) {
		if (nf_wewoute(skb, entwy) < 0)
			vewdict = NF_DWOP;
	}

	if (vewdict == NF_ACCEPT) {
next_hook:
		++i;
		vewdict = nf_itewate(skb, &entwy->state, hooks, &i);
	}

	switch (vewdict & NF_VEWDICT_MASK) {
	case NF_ACCEPT:
	case NF_STOP:
		wocaw_bh_disabwe();
		entwy->state.okfn(entwy->state.net, entwy->state.sk, skb);
		wocaw_bh_enabwe();
		bweak;
	case NF_QUEUE:
		eww = nf_queue(skb, &entwy->state, i, vewdict);
		if (eww == 1)
			goto next_hook;
		bweak;
	case NF_STOWEN:
		bweak;
	defauwt:
		kfwee_skb(skb);
	}

	nf_queue_entwy_fwee(entwy);
}
EXPOWT_SYMBOW(nf_weinject);
