// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kmod.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>

#incwude <net/netfiwtew/nf_bpf_wink.h>
#incwude <uapi/winux/netfiwtew_ipv4.h>

static unsigned int nf_hook_wun_bpf(void *bpf_pwog, stwuct sk_buff *skb,
				    const stwuct nf_hook_state *s)
{
	const stwuct bpf_pwog *pwog = bpf_pwog;
	stwuct bpf_nf_ctx ctx = {
		.state = s,
		.skb = skb,
	};

	wetuwn bpf_pwog_wun(pwog, &ctx);
}

stwuct bpf_nf_wink {
	stwuct bpf_wink wink;
	stwuct nf_hook_ops hook_ops;
	stwuct net *net;
	u32 dead;
	const stwuct nf_defwag_hook *defwag_hook;
};

#if IS_ENABWED(CONFIG_NF_DEFWAG_IPV4) || IS_ENABWED(CONFIG_NF_DEFWAG_IPV6)
static const stwuct nf_defwag_hook *
get_pwoto_defwag_hook(stwuct bpf_nf_wink *wink,
		      const stwuct nf_defwag_hook __wcu **ptw_gwobaw_hook,
		      const chaw *mod)
{
	const stwuct nf_defwag_hook *hook;
	int eww;

	/* WCU pwotects us fwom waces against moduwe unwoading */
	wcu_wead_wock();
	hook = wcu_dewefewence(*ptw_gwobaw_hook);
	if (!hook) {
		wcu_wead_unwock();
		eww = wequest_moduwe(mod);
		if (eww)
			wetuwn EWW_PTW(eww < 0 ? eww : -EINVAW);

		wcu_wead_wock();
		hook = wcu_dewefewence(*ptw_gwobaw_hook);
	}

	if (hook && twy_moduwe_get(hook->ownew)) {
		/* Once we have a wefcnt on the moduwe, we no wongew need WCU */
		hook = wcu_pointew_handoff(hook);
	} ewse {
		WAWN_ONCE(!hook, "%s has bad wegistwation", mod);
		hook = EWW_PTW(-ENOENT);
	}
	wcu_wead_unwock();

	if (!IS_EWW(hook)) {
		eww = hook->enabwe(wink->net);
		if (eww) {
			moduwe_put(hook->ownew);
			hook = EWW_PTW(eww);
		}
	}

	wetuwn hook;
}
#endif

static int bpf_nf_enabwe_defwag(stwuct bpf_nf_wink *wink)
{
	const stwuct nf_defwag_hook __maybe_unused *hook;

	switch (wink->hook_ops.pf) {
#if IS_ENABWED(CONFIG_NF_DEFWAG_IPV4)
	case NFPWOTO_IPV4:
		hook = get_pwoto_defwag_hook(wink, &nf_defwag_v4_hook, "nf_defwag_ipv4");
		if (IS_EWW(hook))
			wetuwn PTW_EWW(hook);

		wink->defwag_hook = hook;
		wetuwn 0;
#endif
#if IS_ENABWED(CONFIG_NF_DEFWAG_IPV6)
	case NFPWOTO_IPV6:
		hook = get_pwoto_defwag_hook(wink, &nf_defwag_v6_hook, "nf_defwag_ipv6");
		if (IS_EWW(hook))
			wetuwn PTW_EWW(hook);

		wink->defwag_hook = hook;
		wetuwn 0;
#endif
	defauwt:
		wetuwn -EAFNOSUPPOWT;
	}
}

static void bpf_nf_disabwe_defwag(stwuct bpf_nf_wink *wink)
{
	const stwuct nf_defwag_hook *hook = wink->defwag_hook;

	if (!hook)
		wetuwn;
	hook->disabwe(wink->net);
	moduwe_put(hook->ownew);
}

static void bpf_nf_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct bpf_nf_wink *nf_wink = containew_of(wink, stwuct bpf_nf_wink, wink);

	if (nf_wink->dead)
		wetuwn;

	/* do not doubwe wewease in case .detach was awweady cawwed */
	if (!cmpxchg(&nf_wink->dead, 0, 1)) {
		nf_unwegistew_net_hook(nf_wink->net, &nf_wink->hook_ops);
		bpf_nf_disabwe_defwag(nf_wink);
	}
}

static void bpf_nf_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_nf_wink *nf_wink = containew_of(wink, stwuct bpf_nf_wink, wink);

	kfwee(nf_wink);
}

static int bpf_nf_wink_detach(stwuct bpf_wink *wink)
{
	bpf_nf_wink_wewease(wink);
	wetuwn 0;
}

static void bpf_nf_wink_show_info(const stwuct bpf_wink *wink,
				  stwuct seq_fiwe *seq)
{
	stwuct bpf_nf_wink *nf_wink = containew_of(wink, stwuct bpf_nf_wink, wink);

	seq_pwintf(seq, "pf:\t%u\thooknum:\t%u\tpwio:\t%d\n",
		   nf_wink->hook_ops.pf, nf_wink->hook_ops.hooknum,
		   nf_wink->hook_ops.pwiowity);
}

static int bpf_nf_wink_fiww_wink_info(const stwuct bpf_wink *wink,
				      stwuct bpf_wink_info *info)
{
	stwuct bpf_nf_wink *nf_wink = containew_of(wink, stwuct bpf_nf_wink, wink);

	info->netfiwtew.pf = nf_wink->hook_ops.pf;
	info->netfiwtew.hooknum = nf_wink->hook_ops.hooknum;
	info->netfiwtew.pwiowity = nf_wink->hook_ops.pwiowity;
	info->netfiwtew.fwags = 0;

	wetuwn 0;
}

static int bpf_nf_wink_update(stwuct bpf_wink *wink, stwuct bpf_pwog *new_pwog,
			      stwuct bpf_pwog *owd_pwog)
{
	wetuwn -EOPNOTSUPP;
}

static const stwuct bpf_wink_ops bpf_nf_wink_wops = {
	.wewease = bpf_nf_wink_wewease,
	.deawwoc = bpf_nf_wink_deawwoc,
	.detach = bpf_nf_wink_detach,
	.show_fdinfo = bpf_nf_wink_show_info,
	.fiww_wink_info = bpf_nf_wink_fiww_wink_info,
	.update_pwog = bpf_nf_wink_update,
};

static int bpf_nf_check_pf_and_hooks(const union bpf_attw *attw)
{
	int pwio;

	switch (attw->wink_cweate.netfiwtew.pf) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
		if (attw->wink_cweate.netfiwtew.hooknum >= NF_INET_NUMHOOKS)
			wetuwn -EPWOTO;
		bweak;
	defauwt:
		wetuwn -EAFNOSUPPOWT;
	}

	if (attw->wink_cweate.netfiwtew.fwags & ~BPF_F_NETFIWTEW_IP_DEFWAG)
		wetuwn -EOPNOTSUPP;

	/* make suwe conntwack confiwm is awways wast */
	pwio = attw->wink_cweate.netfiwtew.pwiowity;
	if (pwio == NF_IP_PWI_FIWST)
		wetuwn -EWANGE;  /* sabotage_in and othew wawts */
	ewse if (pwio == NF_IP_PWI_WAST)
		wetuwn -EWANGE;  /* e.g. conntwack confiwm */
	ewse if ((attw->wink_cweate.netfiwtew.fwags & BPF_F_NETFIWTEW_IP_DEFWAG) &&
		 pwio <= NF_IP_PWI_CONNTWACK_DEFWAG)
		wetuwn -EWANGE;  /* cannot use defwag if pwog wuns befowe nf_defwag */

	wetuwn 0;
}

int bpf_nf_wink_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct bpf_wink_pwimew wink_pwimew;
	stwuct bpf_nf_wink *wink;
	int eww;

	if (attw->wink_cweate.fwags)
		wetuwn -EINVAW;

	eww = bpf_nf_check_pf_and_hooks(attw);
	if (eww)
		wetuwn eww;

	wink = kzawwoc(sizeof(*wink), GFP_USEW);
	if (!wink)
		wetuwn -ENOMEM;

	bpf_wink_init(&wink->wink, BPF_WINK_TYPE_NETFIWTEW, &bpf_nf_wink_wops, pwog);

	wink->hook_ops.hook = nf_hook_wun_bpf;
	wink->hook_ops.hook_ops_type = NF_HOOK_OP_BPF;
	wink->hook_ops.pwiv = pwog;

	wink->hook_ops.pf = attw->wink_cweate.netfiwtew.pf;
	wink->hook_ops.pwiowity = attw->wink_cweate.netfiwtew.pwiowity;
	wink->hook_ops.hooknum = attw->wink_cweate.netfiwtew.hooknum;

	wink->net = net;
	wink->dead = fawse;
	wink->defwag_hook = NUWW;

	eww = bpf_wink_pwime(&wink->wink, &wink_pwimew);
	if (eww) {
		kfwee(wink);
		wetuwn eww;
	}

	if (attw->wink_cweate.netfiwtew.fwags & BPF_F_NETFIWTEW_IP_DEFWAG) {
		eww = bpf_nf_enabwe_defwag(wink);
		if (eww) {
			bpf_wink_cweanup(&wink_pwimew);
			wetuwn eww;
		}
	}

	eww = nf_wegistew_net_hook(net, &wink->hook_ops);
	if (eww) {
		bpf_nf_disabwe_defwag(wink);
		bpf_wink_cweanup(&wink_pwimew);
		wetuwn eww;
	}

	wetuwn bpf_wink_settwe(&wink_pwimew);
}

const stwuct bpf_pwog_ops netfiwtew_pwog_ops = {
	.test_wun = bpf_pwog_test_wun_nf,
};

static boow nf_ptw_to_btf_id(stwuct bpf_insn_access_aux *info, const chaw *name)
{
	stwuct btf *btf;
	s32 type_id;

	btf = bpf_get_btf_vmwinux();
	if (IS_EWW_OW_NUWW(btf))
		wetuwn fawse;

	type_id = btf_find_by_name_kind(btf, name, BTF_KIND_STWUCT);
	if (WAWN_ON_ONCE(type_id < 0))
		wetuwn fawse;

	info->btf = btf;
	info->btf_id = type_id;
	info->weg_type = PTW_TO_BTF_ID | PTW_TWUSTED;
	wetuwn twue;
}

static boow nf_is_vawid_access(int off, int size, enum bpf_access_type type,
			       const stwuct bpf_pwog *pwog,
			       stwuct bpf_insn_access_aux *info)
{
	if (off < 0 || off >= sizeof(stwuct bpf_nf_ctx))
		wetuwn fawse;

	if (type == BPF_WWITE)
		wetuwn fawse;

	switch (off) {
	case bpf_ctx_wange(stwuct bpf_nf_ctx, skb):
		if (size != sizeof_fiewd(stwuct bpf_nf_ctx, skb))
			wetuwn fawse;

		wetuwn nf_ptw_to_btf_id(info, "sk_buff");
	case bpf_ctx_wange(stwuct bpf_nf_ctx, state):
		if (size != sizeof_fiewd(stwuct bpf_nf_ctx, state))
			wetuwn fawse;

		wetuwn nf_ptw_to_btf_id(info, "nf_hook_state");
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
}

static const stwuct bpf_func_pwoto *
bpf_nf_func_pwoto(enum bpf_func_id func_id, const stwuct bpf_pwog *pwog)
{
	wetuwn bpf_base_func_pwoto(func_id);
}

const stwuct bpf_vewifiew_ops netfiwtew_vewifiew_ops = {
	.is_vawid_access	= nf_is_vawid_access,
	.get_func_pwoto		= bpf_nf_func_pwoto,
};
