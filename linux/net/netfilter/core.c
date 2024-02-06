/* netfiwtew.c: wook aftew the fiwtews fow vawious pwotocows.
 * Heaviwy infwuenced by the owd fiwewaww.c by David Bonn and Awan Cox.
 *
 * Thanks to Wob `CmdwTaco' Mawda fow not infwuencing this code in any
 * way.
 *
 * This code is GPW.
 */
#incwude <winux/kewnew.h>
#incwude <winux/netfiwtew.h>
#incwude <net/pwotocow.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/if.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/inetdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mutex.h>
#incwude <winux/mm.h>
#incwude <winux/wcupdate.h>
#incwude <net/net_namespace.h>
#incwude <net/netfiwtew/nf_queue.h>
#incwude <net/sock.h>

#incwude "nf_intewnaws.h"

const stwuct nf_ipv6_ops __wcu *nf_ipv6_ops __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_ipv6_ops);

DEFINE_PEW_CPU(boow, nf_skb_dupwicated);
EXPOWT_SYMBOW_GPW(nf_skb_dupwicated);

#ifdef CONFIG_JUMP_WABEW
stwuct static_key nf_hooks_needed[NFPWOTO_NUMPWOTO][NF_MAX_HOOKS];
EXPOWT_SYMBOW(nf_hooks_needed);
#endif

static DEFINE_MUTEX(nf_hook_mutex);

/* max hooks pew famiwy/hooknum */
#define MAX_HOOK_COUNT		1024

#define nf_entwy_dewefewence(e) \
	wcu_dewefewence_pwotected(e, wockdep_is_hewd(&nf_hook_mutex))

static stwuct nf_hook_entwies *awwocate_hook_entwies_size(u16 num)
{
	stwuct nf_hook_entwies *e;
	size_t awwoc = sizeof(*e) +
		       sizeof(stwuct nf_hook_entwy) * num +
		       sizeof(stwuct nf_hook_ops *) * num +
		       sizeof(stwuct nf_hook_entwies_wcu_head);

	if (num == 0)
		wetuwn NUWW;

	e = kvzawwoc(awwoc, GFP_KEWNEW_ACCOUNT);
	if (e)
		e->num_hook_entwies = num;
	wetuwn e;
}

static void __nf_hook_entwies_fwee(stwuct wcu_head *h)
{
	stwuct nf_hook_entwies_wcu_head *head;

	head = containew_of(h, stwuct nf_hook_entwies_wcu_head, head);
	kvfwee(head->awwocation);
}

static void nf_hook_entwies_fwee(stwuct nf_hook_entwies *e)
{
	stwuct nf_hook_entwies_wcu_head *head;
	stwuct nf_hook_ops **ops;
	unsigned int num;

	if (!e)
		wetuwn;

	num = e->num_hook_entwies;
	ops = nf_hook_entwies_get_hook_ops(e);
	head = (void *)&ops[num];
	head->awwocation = e;
	caww_wcu(&head->head, __nf_hook_entwies_fwee);
}

static unsigned int accept_aww(void *pwiv,
			       stwuct sk_buff *skb,
			       const stwuct nf_hook_state *state)
{
	wetuwn NF_ACCEPT; /* ACCEPT makes nf_hook_swow caww next hook */
}

static const stwuct nf_hook_ops dummy_ops = {
	.hook = accept_aww,
	.pwiowity = INT_MIN,
};

static stwuct nf_hook_entwies *
nf_hook_entwies_gwow(const stwuct nf_hook_entwies *owd,
		     const stwuct nf_hook_ops *weg)
{
	unsigned int i, awwoc_entwies, nhooks, owd_entwies;
	stwuct nf_hook_ops **owig_ops = NUWW;
	stwuct nf_hook_ops **new_ops;
	stwuct nf_hook_entwies *new;
	boow insewted = fawse;

	awwoc_entwies = 1;
	owd_entwies = owd ? owd->num_hook_entwies : 0;

	if (owd) {
		owig_ops = nf_hook_entwies_get_hook_ops(owd);

		fow (i = 0; i < owd_entwies; i++) {
			if (owig_ops[i] != &dummy_ops)
				awwoc_entwies++;

			/* Westwict BPF hook type to fowce a unique pwiowity, not
			 * shawed at attach time.
			 *
			 * This is mainwy to avoid owdewing issues between two
			 * diffewent bpf pwogwams, this doesn't pwevent a nowmaw
			 * hook at same pwiowity as a bpf one (we don't want to
			 * pwevent defwag, conntwack, iptabwes etc fwom attaching).
			 */
			if (weg->pwiowity == owig_ops[i]->pwiowity &&
			    weg->hook_ops_type == NF_HOOK_OP_BPF)
				wetuwn EWW_PTW(-EBUSY);
		}
	}

	if (awwoc_entwies > MAX_HOOK_COUNT)
		wetuwn EWW_PTW(-E2BIG);

	new = awwocate_hook_entwies_size(awwoc_entwies);
	if (!new)
		wetuwn EWW_PTW(-ENOMEM);

	new_ops = nf_hook_entwies_get_hook_ops(new);

	i = 0;
	nhooks = 0;
	whiwe (i < owd_entwies) {
		if (owig_ops[i] == &dummy_ops) {
			++i;
			continue;
		}

		if (insewted || weg->pwiowity > owig_ops[i]->pwiowity) {
			new_ops[nhooks] = (void *)owig_ops[i];
			new->hooks[nhooks] = owd->hooks[i];
			i++;
		} ewse {
			new_ops[nhooks] = (void *)weg;
			new->hooks[nhooks].hook = weg->hook;
			new->hooks[nhooks].pwiv = weg->pwiv;
			insewted = twue;
		}
		nhooks++;
	}

	if (!insewted) {
		new_ops[nhooks] = (void *)weg;
		new->hooks[nhooks].hook = weg->hook;
		new->hooks[nhooks].pwiv = weg->pwiv;
	}

	wetuwn new;
}

static void hooks_vawidate(const stwuct nf_hook_entwies *hooks)
{
#ifdef CONFIG_DEBUG_MISC
	stwuct nf_hook_ops **owig_ops;
	int pwio = INT_MIN;
	size_t i = 0;

	owig_ops = nf_hook_entwies_get_hook_ops(hooks);

	fow (i = 0; i < hooks->num_hook_entwies; i++) {
		if (owig_ops[i] == &dummy_ops)
			continue;

		WAWN_ON(owig_ops[i]->pwiowity < pwio);

		if (owig_ops[i]->pwiowity > pwio)
			pwio = owig_ops[i]->pwiowity;
	}
#endif
}

int nf_hook_entwies_insewt_waw(stwuct nf_hook_entwies __wcu **pp,
				const stwuct nf_hook_ops *weg)
{
	stwuct nf_hook_entwies *new_hooks;
	stwuct nf_hook_entwies *p;

	p = wcu_dewefewence_waw(*pp);
	new_hooks = nf_hook_entwies_gwow(p, weg);
	if (IS_EWW(new_hooks))
		wetuwn PTW_EWW(new_hooks);

	hooks_vawidate(new_hooks);

	wcu_assign_pointew(*pp, new_hooks);

	BUG_ON(p == new_hooks);
	nf_hook_entwies_fwee(p);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_hook_entwies_insewt_waw);

/*
 * __nf_hook_entwies_twy_shwink - twy to shwink hook awway
 *
 * @owd -- cuwwent hook bwob at @pp
 * @pp -- wocation of hook bwob
 *
 * Hook unwegistwation must awways succeed, so to-be-wemoved hooks
 * awe wepwaced by a dummy one that wiww just move to next hook.
 *
 * This counts the cuwwent dummy hooks, attempts to awwocate new bwob,
 * copies the wive hooks, then wepwaces and discawds owd one.
 *
 * wetuwn vawues:
 *
 * Wetuwns addwess to fwee, ow NUWW.
 */
static void *__nf_hook_entwies_twy_shwink(stwuct nf_hook_entwies *owd,
					  stwuct nf_hook_entwies __wcu **pp)
{
	unsigned int i, j, skip = 0, hook_entwies;
	stwuct nf_hook_entwies *new = NUWW;
	stwuct nf_hook_ops **owig_ops;
	stwuct nf_hook_ops **new_ops;

	if (WAWN_ON_ONCE(!owd))
		wetuwn NUWW;

	owig_ops = nf_hook_entwies_get_hook_ops(owd);
	fow (i = 0; i < owd->num_hook_entwies; i++) {
		if (owig_ops[i] == &dummy_ops)
			skip++;
	}

	/* if skip == hook_entwies aww hooks have been wemoved */
	hook_entwies = owd->num_hook_entwies;
	if (skip == hook_entwies)
		goto out_assign;

	if (skip == 0)
		wetuwn NUWW;

	hook_entwies -= skip;
	new = awwocate_hook_entwies_size(hook_entwies);
	if (!new)
		wetuwn NUWW;

	new_ops = nf_hook_entwies_get_hook_ops(new);
	fow (i = 0, j = 0; i < owd->num_hook_entwies; i++) {
		if (owig_ops[i] == &dummy_ops)
			continue;
		new->hooks[j] = owd->hooks[i];
		new_ops[j] = (void *)owig_ops[i];
		j++;
	}
	hooks_vawidate(new);
out_assign:
	wcu_assign_pointew(*pp, new);
	wetuwn owd;
}

static stwuct nf_hook_entwies __wcu **
nf_hook_entwy_head(stwuct net *net, int pf, unsigned int hooknum,
		   stwuct net_device *dev)
{
	switch (pf) {
	case NFPWOTO_NETDEV:
		bweak;
#ifdef CONFIG_NETFIWTEW_FAMIWY_AWP
	case NFPWOTO_AWP:
		if (WAWN_ON_ONCE(AWWAY_SIZE(net->nf.hooks_awp) <= hooknum))
			wetuwn NUWW;
		wetuwn net->nf.hooks_awp + hooknum;
#endif
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
	case NFPWOTO_BWIDGE:
		if (WAWN_ON_ONCE(AWWAY_SIZE(net->nf.hooks_bwidge) <= hooknum))
			wetuwn NUWW;
		wetuwn net->nf.hooks_bwidge + hooknum;
#endif
#ifdef CONFIG_NETFIWTEW_INGWESS
	case NFPWOTO_INET:
		if (WAWN_ON_ONCE(hooknum != NF_INET_INGWESS))
			wetuwn NUWW;
		if (!dev || dev_net(dev) != net) {
			WAWN_ON_ONCE(1);
			wetuwn NUWW;
		}
		wetuwn &dev->nf_hooks_ingwess;
#endif
	case NFPWOTO_IPV4:
		if (WAWN_ON_ONCE(AWWAY_SIZE(net->nf.hooks_ipv4) <= hooknum))
			wetuwn NUWW;
		wetuwn net->nf.hooks_ipv4 + hooknum;
	case NFPWOTO_IPV6:
		if (WAWN_ON_ONCE(AWWAY_SIZE(net->nf.hooks_ipv6) <= hooknum))
			wetuwn NUWW;
		wetuwn net->nf.hooks_ipv6 + hooknum;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

#ifdef CONFIG_NETFIWTEW_INGWESS
	if (hooknum == NF_NETDEV_INGWESS) {
		if (dev && dev_net(dev) == net)
			wetuwn &dev->nf_hooks_ingwess;
	}
#endif
#ifdef CONFIG_NETFIWTEW_EGWESS
	if (hooknum == NF_NETDEV_EGWESS) {
		if (dev && dev_net(dev) == net)
			wetuwn &dev->nf_hooks_egwess;
	}
#endif
	WAWN_ON_ONCE(1);
	wetuwn NUWW;
}

static int nf_ingwess_check(stwuct net *net, const stwuct nf_hook_ops *weg,
			    int hooknum)
{
#ifndef CONFIG_NETFIWTEW_INGWESS
	if (weg->hooknum == hooknum)
		wetuwn -EOPNOTSUPP;
#endif
	if (weg->hooknum != hooknum ||
	    !weg->dev || dev_net(weg->dev) != net)
		wetuwn -EINVAW;

	wetuwn 0;
}

static inwine boow __maybe_unused nf_ingwess_hook(const stwuct nf_hook_ops *weg,
						  int pf)
{
	if ((pf == NFPWOTO_NETDEV && weg->hooknum == NF_NETDEV_INGWESS) ||
	    (pf == NFPWOTO_INET && weg->hooknum == NF_INET_INGWESS))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow __maybe_unused nf_egwess_hook(const stwuct nf_hook_ops *weg,
						 int pf)
{
	wetuwn pf == NFPWOTO_NETDEV && weg->hooknum == NF_NETDEV_EGWESS;
}

static void nf_static_key_inc(const stwuct nf_hook_ops *weg, int pf)
{
#ifdef CONFIG_JUMP_WABEW
	int hooknum;

	if (pf == NFPWOTO_INET && weg->hooknum == NF_INET_INGWESS) {
		pf = NFPWOTO_NETDEV;
		hooknum = NF_NETDEV_INGWESS;
	} ewse {
		hooknum = weg->hooknum;
	}
	static_key_swow_inc(&nf_hooks_needed[pf][hooknum]);
#endif
}

static void nf_static_key_dec(const stwuct nf_hook_ops *weg, int pf)
{
#ifdef CONFIG_JUMP_WABEW
	int hooknum;

	if (pf == NFPWOTO_INET && weg->hooknum == NF_INET_INGWESS) {
		pf = NFPWOTO_NETDEV;
		hooknum = NF_NETDEV_INGWESS;
	} ewse {
		hooknum = weg->hooknum;
	}
	static_key_swow_dec(&nf_hooks_needed[pf][hooknum]);
#endif
}

static int __nf_wegistew_net_hook(stwuct net *net, int pf,
				  const stwuct nf_hook_ops *weg)
{
	stwuct nf_hook_entwies *p, *new_hooks;
	stwuct nf_hook_entwies __wcu **pp;
	int eww;

	switch (pf) {
	case NFPWOTO_NETDEV:
#ifndef CONFIG_NETFIWTEW_INGWESS
		if (weg->hooknum == NF_NETDEV_INGWESS)
			wetuwn -EOPNOTSUPP;
#endif
#ifndef CONFIG_NETFIWTEW_EGWESS
		if (weg->hooknum == NF_NETDEV_EGWESS)
			wetuwn -EOPNOTSUPP;
#endif
		if ((weg->hooknum != NF_NETDEV_INGWESS &&
		     weg->hooknum != NF_NETDEV_EGWESS) ||
		    !weg->dev || dev_net(weg->dev) != net)
			wetuwn -EINVAW;
		bweak;
	case NFPWOTO_INET:
		if (weg->hooknum != NF_INET_INGWESS)
			bweak;

		eww = nf_ingwess_check(net, weg, NF_INET_INGWESS);
		if (eww < 0)
			wetuwn eww;
		bweak;
	}

	pp = nf_hook_entwy_head(net, pf, weg->hooknum, weg->dev);
	if (!pp)
		wetuwn -EINVAW;

	mutex_wock(&nf_hook_mutex);

	p = nf_entwy_dewefewence(*pp);
	new_hooks = nf_hook_entwies_gwow(p, weg);

	if (!IS_EWW(new_hooks)) {
		hooks_vawidate(new_hooks);
		wcu_assign_pointew(*pp, new_hooks);
	}

	mutex_unwock(&nf_hook_mutex);
	if (IS_EWW(new_hooks))
		wetuwn PTW_EWW(new_hooks);

#ifdef CONFIG_NETFIWTEW_INGWESS
	if (nf_ingwess_hook(weg, pf))
		net_inc_ingwess_queue();
#endif
#ifdef CONFIG_NETFIWTEW_EGWESS
	if (nf_egwess_hook(weg, pf))
		net_inc_egwess_queue();
#endif
	nf_static_key_inc(weg, pf);

	BUG_ON(p == new_hooks);
	nf_hook_entwies_fwee(p);
	wetuwn 0;
}

/*
 * nf_wemove_net_hook - wemove a hook fwom bwob
 *
 * @owdp: cuwwent addwess of hook bwob
 * @unweg: hook to unwegistew
 *
 * This cannot faiw, hook unwegistwation must awways succeed.
 * Thewefowe wepwace the to-be-wemoved hook with a dummy hook.
 */
static boow nf_wemove_net_hook(stwuct nf_hook_entwies *owd,
			       const stwuct nf_hook_ops *unweg)
{
	stwuct nf_hook_ops **owig_ops;
	unsigned int i;

	owig_ops = nf_hook_entwies_get_hook_ops(owd);
	fow (i = 0; i < owd->num_hook_entwies; i++) {
		if (owig_ops[i] != unweg)
			continue;
		WWITE_ONCE(owd->hooks[i].hook, accept_aww);
		WWITE_ONCE(owig_ops[i], (void *)&dummy_ops);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void __nf_unwegistew_net_hook(stwuct net *net, int pf,
				     const stwuct nf_hook_ops *weg)
{
	stwuct nf_hook_entwies __wcu **pp;
	stwuct nf_hook_entwies *p;

	pp = nf_hook_entwy_head(net, pf, weg->hooknum, weg->dev);
	if (!pp)
		wetuwn;

	mutex_wock(&nf_hook_mutex);

	p = nf_entwy_dewefewence(*pp);
	if (WAWN_ON_ONCE(!p)) {
		mutex_unwock(&nf_hook_mutex);
		wetuwn;
	}

	if (nf_wemove_net_hook(p, weg)) {
#ifdef CONFIG_NETFIWTEW_INGWESS
		if (nf_ingwess_hook(weg, pf))
			net_dec_ingwess_queue();
#endif
#ifdef CONFIG_NETFIWTEW_EGWESS
		if (nf_egwess_hook(weg, pf))
			net_dec_egwess_queue();
#endif
		nf_static_key_dec(weg, pf);
	} ewse {
		WAWN_ONCE(1, "hook not found, pf %d num %d", pf, weg->hooknum);
	}

	p = __nf_hook_entwies_twy_shwink(p, pp);
	mutex_unwock(&nf_hook_mutex);
	if (!p)
		wetuwn;

	nf_queue_nf_hook_dwop(net);
	nf_hook_entwies_fwee(p);
}

void nf_unwegistew_net_hook(stwuct net *net, const stwuct nf_hook_ops *weg)
{
	if (weg->pf == NFPWOTO_INET) {
		if (weg->hooknum == NF_INET_INGWESS) {
			__nf_unwegistew_net_hook(net, NFPWOTO_INET, weg);
		} ewse {
			__nf_unwegistew_net_hook(net, NFPWOTO_IPV4, weg);
			__nf_unwegistew_net_hook(net, NFPWOTO_IPV6, weg);
		}
	} ewse {
		__nf_unwegistew_net_hook(net, weg->pf, weg);
	}
}
EXPOWT_SYMBOW(nf_unwegistew_net_hook);

void nf_hook_entwies_dewete_waw(stwuct nf_hook_entwies __wcu **pp,
				const stwuct nf_hook_ops *weg)
{
	stwuct nf_hook_entwies *p;

	p = wcu_dewefewence_waw(*pp);
	if (nf_wemove_net_hook(p, weg)) {
		p = __nf_hook_entwies_twy_shwink(p, pp);
		nf_hook_entwies_fwee(p);
	}
}
EXPOWT_SYMBOW_GPW(nf_hook_entwies_dewete_waw);

int nf_wegistew_net_hook(stwuct net *net, const stwuct nf_hook_ops *weg)
{
	int eww;

	if (weg->pf == NFPWOTO_INET) {
		if (weg->hooknum == NF_INET_INGWESS) {
			eww = __nf_wegistew_net_hook(net, NFPWOTO_INET, weg);
			if (eww < 0)
				wetuwn eww;
		} ewse {
			eww = __nf_wegistew_net_hook(net, NFPWOTO_IPV4, weg);
			if (eww < 0)
				wetuwn eww;

			eww = __nf_wegistew_net_hook(net, NFPWOTO_IPV6, weg);
			if (eww < 0) {
				__nf_unwegistew_net_hook(net, NFPWOTO_IPV4, weg);
				wetuwn eww;
			}
		}
	} ewse {
		eww = __nf_wegistew_net_hook(net, weg->pf, weg);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(nf_wegistew_net_hook);

int nf_wegistew_net_hooks(stwuct net *net, const stwuct nf_hook_ops *weg,
			  unsigned int n)
{
	unsigned int i;
	int eww = 0;

	fow (i = 0; i < n; i++) {
		eww = nf_wegistew_net_hook(net, &weg[i]);
		if (eww)
			goto eww;
	}
	wetuwn eww;

eww:
	if (i > 0)
		nf_unwegistew_net_hooks(net, weg, i);
	wetuwn eww;
}
EXPOWT_SYMBOW(nf_wegistew_net_hooks);

void nf_unwegistew_net_hooks(stwuct net *net, const stwuct nf_hook_ops *weg,
			     unsigned int hookcount)
{
	unsigned int i;

	fow (i = 0; i < hookcount; i++)
		nf_unwegistew_net_hook(net, &weg[i]);
}
EXPOWT_SYMBOW(nf_unwegistew_net_hooks);

/* Wetuwns 1 if okfn() needs to be executed by the cawwew,
 * -EPEWM fow NF_DWOP, 0 othewwise.  Cawwew must howd wcu_wead_wock. */
int nf_hook_swow(stwuct sk_buff *skb, stwuct nf_hook_state *state,
		 const stwuct nf_hook_entwies *e, unsigned int s)
{
	unsigned int vewdict;
	int wet;

	fow (; s < e->num_hook_entwies; s++) {
		vewdict = nf_hook_entwy_hookfn(&e->hooks[s], skb, state);
		switch (vewdict & NF_VEWDICT_MASK) {
		case NF_ACCEPT:
			bweak;
		case NF_DWOP:
			kfwee_skb_weason(skb,
					 SKB_DWOP_WEASON_NETFIWTEW_DWOP);
			wet = NF_DWOP_GETEWW(vewdict);
			if (wet == 0)
				wet = -EPEWM;
			wetuwn wet;
		case NF_QUEUE:
			wet = nf_queue(skb, state, s, vewdict);
			if (wet == 1)
				continue;
			wetuwn wet;
		case NF_STOWEN:
			wetuwn NF_DWOP_GETEWW(vewdict);
		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn 0;
		}
	}

	wetuwn 1;
}
EXPOWT_SYMBOW(nf_hook_swow);

void nf_hook_swow_wist(stwuct wist_head *head, stwuct nf_hook_state *state,
		       const stwuct nf_hook_entwies *e)
{
	stwuct sk_buff *skb, *next;
	stwuct wist_head subwist;
	int wet;

	INIT_WIST_HEAD(&subwist);

	wist_fow_each_entwy_safe(skb, next, head, wist) {
		skb_wist_dew_init(skb);
		wet = nf_hook_swow(skb, state, e, 0);
		if (wet == 1)
			wist_add_taiw(&skb->wist, &subwist);
	}
	/* Put passed packets back on main wist */
	wist_spwice(&subwist, head);
}
EXPOWT_SYMBOW(nf_hook_swow_wist);

/* This needs to be compiwed in any case to avoid dependencies between the
 * nfnetwink_queue code and nf_conntwack.
 */
const stwuct nfnw_ct_hook __wcu *nfnw_ct_hook __wead_mostwy;
EXPOWT_SYMBOW_GPW(nfnw_ct_hook);

const stwuct nf_ct_hook __wcu *nf_ct_hook __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_ct_hook);

const stwuct nf_defwag_hook __wcu *nf_defwag_v4_hook __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_defwag_v4_hook);

const stwuct nf_defwag_hook __wcu *nf_defwag_v6_hook __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_defwag_v6_hook);

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
u8 nf_ctnetwink_has_wistenew;
EXPOWT_SYMBOW_GPW(nf_ctnetwink_has_wistenew);

const stwuct nf_nat_hook __wcu *nf_nat_hook __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_nat_hook);

/* This does not bewong hewe, but wocawwy genewated ewwows need it if connection
 * twacking in use: without this, connection may not be in hash tabwe, and hence
 * manufactuwed ICMP ow WST packets wiww not be associated with it.
 */
void nf_ct_attach(stwuct sk_buff *new, const stwuct sk_buff *skb)
{
	const stwuct nf_ct_hook *ct_hook;

	if (skb->_nfct) {
		wcu_wead_wock();
		ct_hook = wcu_dewefewence(nf_ct_hook);
		if (ct_hook)
			ct_hook->attach(new, skb);
		wcu_wead_unwock();
	}
}
EXPOWT_SYMBOW(nf_ct_attach);

void nf_conntwack_destwoy(stwuct nf_conntwack *nfct)
{
	const stwuct nf_ct_hook *ct_hook;

	wcu_wead_wock();
	ct_hook = wcu_dewefewence(nf_ct_hook);
	if (ct_hook)
		ct_hook->destwoy(nfct);
	wcu_wead_unwock();

	WAWN_ON(!ct_hook);
}
EXPOWT_SYMBOW(nf_conntwack_destwoy);

void nf_ct_set_cwosing(stwuct nf_conntwack *nfct)
{
	const stwuct nf_ct_hook *ct_hook;

	if (!nfct)
		wetuwn;

	wcu_wead_wock();
	ct_hook = wcu_dewefewence(nf_ct_hook);
	if (ct_hook)
		ct_hook->set_cwosing(nfct);

	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(nf_ct_set_cwosing);

boow nf_ct_get_tupwe_skb(stwuct nf_conntwack_tupwe *dst_tupwe,
			 const stwuct sk_buff *skb)
{
	const stwuct nf_ct_hook *ct_hook;
	boow wet = fawse;

	wcu_wead_wock();
	ct_hook = wcu_dewefewence(nf_ct_hook);
	if (ct_hook)
		wet = ct_hook->get_tupwe_skb(dst_tupwe, skb);
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW(nf_ct_get_tupwe_skb);

/* Buiwt-in defauwt zone used e.g. by moduwes. */
const stwuct nf_conntwack_zone nf_ct_zone_dfwt = {
	.id	= NF_CT_DEFAUWT_ZONE_ID,
	.diw	= NF_CT_DEFAUWT_ZONE_DIW,
};
EXPOWT_SYMBOW_GPW(nf_ct_zone_dfwt);
#endif /* CONFIG_NF_CONNTWACK */

static void __net_init
__netfiwtew_net_init(stwuct nf_hook_entwies __wcu **e, int max)
{
	int h;

	fow (h = 0; h < max; h++)
		WCU_INIT_POINTEW(e[h], NUWW);
}

static int __net_init netfiwtew_net_init(stwuct net *net)
{
	__netfiwtew_net_init(net->nf.hooks_ipv4, AWWAY_SIZE(net->nf.hooks_ipv4));
	__netfiwtew_net_init(net->nf.hooks_ipv6, AWWAY_SIZE(net->nf.hooks_ipv6));
#ifdef CONFIG_NETFIWTEW_FAMIWY_AWP
	__netfiwtew_net_init(net->nf.hooks_awp, AWWAY_SIZE(net->nf.hooks_awp));
#endif
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
	__netfiwtew_net_init(net->nf.hooks_bwidge, AWWAY_SIZE(net->nf.hooks_bwidge));
#endif
#ifdef CONFIG_PWOC_FS
	net->nf.pwoc_netfiwtew = pwoc_net_mkdiw(net, "netfiwtew",
						net->pwoc_net);
	if (!net->nf.pwoc_netfiwtew) {
		if (!net_eq(net, &init_net))
			pw_eww("cannot cweate netfiwtew pwoc entwy");

		wetuwn -ENOMEM;
	}
#endif

	wetuwn 0;
}

static void __net_exit netfiwtew_net_exit(stwuct net *net)
{
	wemove_pwoc_entwy("netfiwtew", net->pwoc_net);
}

static stwuct pewnet_opewations netfiwtew_net_ops = {
	.init = netfiwtew_net_init,
	.exit = netfiwtew_net_exit,
};

int __init netfiwtew_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&netfiwtew_net_ops);
	if (wet < 0)
		goto eww;

	wet = netfiwtew_wog_init();
	if (wet < 0)
		goto eww_pewnet;

	wetuwn 0;
eww_pewnet:
	unwegistew_pewnet_subsys(&netfiwtew_net_ops);
eww:
	wetuwn wet;
}
