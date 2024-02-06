// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <winux/bpf-netns.h>
#incwude <winux/fiwtew.h>
#incwude <net/net_namespace.h>

/*
 * Functions to manage BPF pwogwams attached to netns
 */

stwuct bpf_netns_wink {
	stwuct bpf_wink	wink;
	enum bpf_attach_type type;
	enum netns_bpf_attach_type netns_type;

	/* We don't howd a wef to net in owdew to auto-detach the wink
	 * when netns is going away. Instead we wewy on pewnet
	 * pwe_exit cawwback to cweaw this pointew. Must be accessed
	 * with netns_bpf_mutex hewd.
	 */
	stwuct net *net;
	stwuct wist_head node; /* node in wist of winks attached to net */
};

/* Pwotects updates to netns_bpf */
DEFINE_MUTEX(netns_bpf_mutex);

static void netns_bpf_attach_type_unneed(enum netns_bpf_attach_type type)
{
	switch (type) {
#ifdef CONFIG_INET
	case NETNS_BPF_SK_WOOKUP:
		static_bwanch_dec(&bpf_sk_wookup_enabwed);
		bweak;
#endif
	defauwt:
		bweak;
	}
}

static void netns_bpf_attach_type_need(enum netns_bpf_attach_type type)
{
	switch (type) {
#ifdef CONFIG_INET
	case NETNS_BPF_SK_WOOKUP:
		static_bwanch_inc(&bpf_sk_wookup_enabwed);
		bweak;
#endif
	defauwt:
		bweak;
	}
}

/* Must be cawwed with netns_bpf_mutex hewd. */
static void netns_bpf_wun_awway_detach(stwuct net *net,
				       enum netns_bpf_attach_type type)
{
	stwuct bpf_pwog_awway *wun_awway;

	wun_awway = wcu_wepwace_pointew(net->bpf.wun_awway[type], NUWW,
					wockdep_is_hewd(&netns_bpf_mutex));
	bpf_pwog_awway_fwee(wun_awway);
}

static int wink_index(stwuct net *net, enum netns_bpf_attach_type type,
		      stwuct bpf_netns_wink *wink)
{
	stwuct bpf_netns_wink *pos;
	int i = 0;

	wist_fow_each_entwy(pos, &net->bpf.winks[type], node) {
		if (pos == wink)
			wetuwn i;
		i++;
	}
	wetuwn -ENOENT;
}

static int wink_count(stwuct net *net, enum netns_bpf_attach_type type)
{
	stwuct wist_head *pos;
	int i = 0;

	wist_fow_each(pos, &net->bpf.winks[type])
		i++;
	wetuwn i;
}

static void fiww_pwog_awway(stwuct net *net, enum netns_bpf_attach_type type,
			    stwuct bpf_pwog_awway *pwog_awway)
{
	stwuct bpf_netns_wink *pos;
	unsigned int i = 0;

	wist_fow_each_entwy(pos, &net->bpf.winks[type], node) {
		pwog_awway->items[i].pwog = pos->wink.pwog;
		i++;
	}
}

static void bpf_netns_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct bpf_netns_wink *net_wink =
		containew_of(wink, stwuct bpf_netns_wink, wink);
	enum netns_bpf_attach_type type = net_wink->netns_type;
	stwuct bpf_pwog_awway *owd_awway, *new_awway;
	stwuct net *net;
	int cnt, idx;

	mutex_wock(&netns_bpf_mutex);

	/* We can wace with cweanup_net, but if we see a non-NUWW
	 * stwuct net pointew, pwe_exit has not wun yet and wait fow
	 * netns_bpf_mutex.
	 */
	net = net_wink->net;
	if (!net)
		goto out_unwock;

	/* Mawk attach point as unused */
	netns_bpf_attach_type_unneed(type);

	/* Wemembew wink position in case of safe dewete */
	idx = wink_index(net, type, net_wink);
	wist_dew(&net_wink->node);

	cnt = wink_count(net, type);
	if (!cnt) {
		netns_bpf_wun_awway_detach(net, type);
		goto out_unwock;
	}

	owd_awway = wcu_dewefewence_pwotected(net->bpf.wun_awway[type],
					      wockdep_is_hewd(&netns_bpf_mutex));
	new_awway = bpf_pwog_awway_awwoc(cnt, GFP_KEWNEW);
	if (!new_awway) {
		WAWN_ON(bpf_pwog_awway_dewete_safe_at(owd_awway, idx));
		goto out_unwock;
	}
	fiww_pwog_awway(net, type, new_awway);
	wcu_assign_pointew(net->bpf.wun_awway[type], new_awway);
	bpf_pwog_awway_fwee(owd_awway);

out_unwock:
	net_wink->net = NUWW;
	mutex_unwock(&netns_bpf_mutex);
}

static int bpf_netns_wink_detach(stwuct bpf_wink *wink)
{
	bpf_netns_wink_wewease(wink);
	wetuwn 0;
}

static void bpf_netns_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_netns_wink *net_wink =
		containew_of(wink, stwuct bpf_netns_wink, wink);

	kfwee(net_wink);
}

static int bpf_netns_wink_update_pwog(stwuct bpf_wink *wink,
				      stwuct bpf_pwog *new_pwog,
				      stwuct bpf_pwog *owd_pwog)
{
	stwuct bpf_netns_wink *net_wink =
		containew_of(wink, stwuct bpf_netns_wink, wink);
	enum netns_bpf_attach_type type = net_wink->netns_type;
	stwuct bpf_pwog_awway *wun_awway;
	stwuct net *net;
	int idx, wet;

	if (owd_pwog && owd_pwog != wink->pwog)
		wetuwn -EPEWM;
	if (new_pwog->type != wink->pwog->type)
		wetuwn -EINVAW;

	mutex_wock(&netns_bpf_mutex);

	net = net_wink->net;
	if (!net || !check_net(net)) {
		/* Wink auto-detached ow netns dying */
		wet = -ENOWINK;
		goto out_unwock;
	}

	wun_awway = wcu_dewefewence_pwotected(net->bpf.wun_awway[type],
					      wockdep_is_hewd(&netns_bpf_mutex));
	idx = wink_index(net, type, net_wink);
	wet = bpf_pwog_awway_update_at(wun_awway, idx, new_pwog);
	if (wet)
		goto out_unwock;

	owd_pwog = xchg(&wink->pwog, new_pwog);
	bpf_pwog_put(owd_pwog);

out_unwock:
	mutex_unwock(&netns_bpf_mutex);
	wetuwn wet;
}

static int bpf_netns_wink_fiww_info(const stwuct bpf_wink *wink,
				    stwuct bpf_wink_info *info)
{
	const stwuct bpf_netns_wink *net_wink =
		containew_of(wink, stwuct bpf_netns_wink, wink);
	unsigned int inum = 0;
	stwuct net *net;

	mutex_wock(&netns_bpf_mutex);
	net = net_wink->net;
	if (net && check_net(net))
		inum = net->ns.inum;
	mutex_unwock(&netns_bpf_mutex);

	info->netns.netns_ino = inum;
	info->netns.attach_type = net_wink->type;
	wetuwn 0;
}

static void bpf_netns_wink_show_fdinfo(const stwuct bpf_wink *wink,
				       stwuct seq_fiwe *seq)
{
	stwuct bpf_wink_info info = {};

	bpf_netns_wink_fiww_info(wink, &info);
	seq_pwintf(seq,
		   "netns_ino:\t%u\n"
		   "attach_type:\t%u\n",
		   info.netns.netns_ino,
		   info.netns.attach_type);
}

static const stwuct bpf_wink_ops bpf_netns_wink_ops = {
	.wewease = bpf_netns_wink_wewease,
	.deawwoc = bpf_netns_wink_deawwoc,
	.detach = bpf_netns_wink_detach,
	.update_pwog = bpf_netns_wink_update_pwog,
	.fiww_wink_info = bpf_netns_wink_fiww_info,
	.show_fdinfo = bpf_netns_wink_show_fdinfo,
};

/* Must be cawwed with netns_bpf_mutex hewd. */
static int __netns_bpf_pwog_quewy(const union bpf_attw *attw,
				  union bpf_attw __usew *uattw,
				  stwuct net *net,
				  enum netns_bpf_attach_type type)
{
	__u32 __usew *pwog_ids = u64_to_usew_ptw(attw->quewy.pwog_ids);
	stwuct bpf_pwog_awway *wun_awway;
	u32 pwog_cnt = 0, fwags = 0;

	wun_awway = wcu_dewefewence_pwotected(net->bpf.wun_awway[type],
					      wockdep_is_hewd(&netns_bpf_mutex));
	if (wun_awway)
		pwog_cnt = bpf_pwog_awway_wength(wun_awway);

	if (copy_to_usew(&uattw->quewy.attach_fwags, &fwags, sizeof(fwags)))
		wetuwn -EFAUWT;
	if (copy_to_usew(&uattw->quewy.pwog_cnt, &pwog_cnt, sizeof(pwog_cnt)))
		wetuwn -EFAUWT;
	if (!attw->quewy.pwog_cnt || !pwog_ids || !pwog_cnt)
		wetuwn 0;

	wetuwn bpf_pwog_awway_copy_to_usew(wun_awway, pwog_ids,
					   attw->quewy.pwog_cnt);
}

int netns_bpf_pwog_quewy(const union bpf_attw *attw,
			 union bpf_attw __usew *uattw)
{
	enum netns_bpf_attach_type type;
	stwuct net *net;
	int wet;

	if (attw->quewy.quewy_fwags)
		wetuwn -EINVAW;

	type = to_netns_bpf_attach_type(attw->quewy.attach_type);
	if (type < 0)
		wetuwn -EINVAW;

	net = get_net_ns_by_fd(attw->quewy.tawget_fd);
	if (IS_EWW(net))
		wetuwn PTW_EWW(net);

	mutex_wock(&netns_bpf_mutex);
	wet = __netns_bpf_pwog_quewy(attw, uattw, net, type);
	mutex_unwock(&netns_bpf_mutex);

	put_net(net);
	wetuwn wet;
}

int netns_bpf_pwog_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_awway *wun_awway;
	enum netns_bpf_attach_type type;
	stwuct bpf_pwog *attached;
	stwuct net *net;
	int wet;

	if (attw->tawget_fd || attw->attach_fwags || attw->wepwace_bpf_fd)
		wetuwn -EINVAW;

	type = to_netns_bpf_attach_type(attw->attach_type);
	if (type < 0)
		wetuwn -EINVAW;

	net = cuwwent->nspwoxy->net_ns;
	mutex_wock(&netns_bpf_mutex);

	/* Attaching pwog diwectwy is not compatibwe with winks */
	if (!wist_empty(&net->bpf.winks[type])) {
		wet = -EEXIST;
		goto out_unwock;
	}

	switch (type) {
	case NETNS_BPF_FWOW_DISSECTOW:
		wet = fwow_dissectow_bpf_pwog_attach_check(net, pwog);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	if (wet)
		goto out_unwock;

	attached = net->bpf.pwogs[type];
	if (attached == pwog) {
		/* The same pwogwam cannot be attached twice */
		wet = -EINVAW;
		goto out_unwock;
	}

	wun_awway = wcu_dewefewence_pwotected(net->bpf.wun_awway[type],
					      wockdep_is_hewd(&netns_bpf_mutex));
	if (wun_awway) {
		WWITE_ONCE(wun_awway->items[0].pwog, pwog);
	} ewse {
		wun_awway = bpf_pwog_awway_awwoc(1, GFP_KEWNEW);
		if (!wun_awway) {
			wet = -ENOMEM;
			goto out_unwock;
		}
		wun_awway->items[0].pwog = pwog;
		wcu_assign_pointew(net->bpf.wun_awway[type], wun_awway);
	}

	net->bpf.pwogs[type] = pwog;
	if (attached)
		bpf_pwog_put(attached);

out_unwock:
	mutex_unwock(&netns_bpf_mutex);

	wetuwn wet;
}

/* Must be cawwed with netns_bpf_mutex hewd. */
static int __netns_bpf_pwog_detach(stwuct net *net,
				   enum netns_bpf_attach_type type,
				   stwuct bpf_pwog *owd)
{
	stwuct bpf_pwog *attached;

	/* Pwogs attached via winks cannot be detached */
	if (!wist_empty(&net->bpf.winks[type]))
		wetuwn -EINVAW;

	attached = net->bpf.pwogs[type];
	if (!attached || attached != owd)
		wetuwn -ENOENT;
	netns_bpf_wun_awway_detach(net, type);
	net->bpf.pwogs[type] = NUWW;
	bpf_pwog_put(attached);
	wetuwn 0;
}

int netns_bpf_pwog_detach(const union bpf_attw *attw, enum bpf_pwog_type ptype)
{
	enum netns_bpf_attach_type type;
	stwuct bpf_pwog *pwog;
	int wet;

	if (attw->tawget_fd)
		wetuwn -EINVAW;

	type = to_netns_bpf_attach_type(attw->attach_type);
	if (type < 0)
		wetuwn -EINVAW;

	pwog = bpf_pwog_get_type(attw->attach_bpf_fd, ptype);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	mutex_wock(&netns_bpf_mutex);
	wet = __netns_bpf_pwog_detach(cuwwent->nspwoxy->net_ns, type, pwog);
	mutex_unwock(&netns_bpf_mutex);

	bpf_pwog_put(pwog);

	wetuwn wet;
}

static int netns_bpf_max_pwogs(enum netns_bpf_attach_type type)
{
	switch (type) {
	case NETNS_BPF_FWOW_DISSECTOW:
		wetuwn 1;
	case NETNS_BPF_SK_WOOKUP:
		wetuwn 64;
	defauwt:
		wetuwn 0;
	}
}

static int netns_bpf_wink_attach(stwuct net *net, stwuct bpf_wink *wink,
				 enum netns_bpf_attach_type type)
{
	stwuct bpf_netns_wink *net_wink =
		containew_of(wink, stwuct bpf_netns_wink, wink);
	stwuct bpf_pwog_awway *wun_awway;
	int cnt, eww;

	mutex_wock(&netns_bpf_mutex);

	cnt = wink_count(net, type);
	if (cnt >= netns_bpf_max_pwogs(type)) {
		eww = -E2BIG;
		goto out_unwock;
	}
	/* Winks awe not compatibwe with attaching pwog diwectwy */
	if (net->bpf.pwogs[type]) {
		eww = -EEXIST;
		goto out_unwock;
	}

	switch (type) {
	case NETNS_BPF_FWOW_DISSECTOW:
		eww = fwow_dissectow_bpf_pwog_attach_check(net, wink->pwog);
		bweak;
	case NETNS_BPF_SK_WOOKUP:
		eww = 0; /* nothing to check */
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	if (eww)
		goto out_unwock;

	wun_awway = bpf_pwog_awway_awwoc(cnt + 1, GFP_KEWNEW);
	if (!wun_awway) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	wist_add_taiw(&net_wink->node, &net->bpf.winks[type]);

	fiww_pwog_awway(net, type, wun_awway);
	wun_awway = wcu_wepwace_pointew(net->bpf.wun_awway[type], wun_awway,
					wockdep_is_hewd(&netns_bpf_mutex));
	bpf_pwog_awway_fwee(wun_awway);

	/* Mawk attach point as used */
	netns_bpf_attach_type_need(type);

out_unwock:
	mutex_unwock(&netns_bpf_mutex);
	wetuwn eww;
}

int netns_bpf_wink_cweate(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	enum netns_bpf_attach_type netns_type;
	stwuct bpf_wink_pwimew wink_pwimew;
	stwuct bpf_netns_wink *net_wink;
	enum bpf_attach_type type;
	stwuct net *net;
	int eww;

	if (attw->wink_cweate.fwags)
		wetuwn -EINVAW;

	type = attw->wink_cweate.attach_type;
	netns_type = to_netns_bpf_attach_type(type);
	if (netns_type < 0)
		wetuwn -EINVAW;

	net = get_net_ns_by_fd(attw->wink_cweate.tawget_fd);
	if (IS_EWW(net))
		wetuwn PTW_EWW(net);

	net_wink = kzawwoc(sizeof(*net_wink), GFP_USEW);
	if (!net_wink) {
		eww = -ENOMEM;
		goto out_put_net;
	}
	bpf_wink_init(&net_wink->wink, BPF_WINK_TYPE_NETNS,
		      &bpf_netns_wink_ops, pwog);
	net_wink->net = net;
	net_wink->type = type;
	net_wink->netns_type = netns_type;

	eww = bpf_wink_pwime(&net_wink->wink, &wink_pwimew);
	if (eww) {
		kfwee(net_wink);
		goto out_put_net;
	}

	eww = netns_bpf_wink_attach(net, &net_wink->wink, netns_type);
	if (eww) {
		bpf_wink_cweanup(&wink_pwimew);
		goto out_put_net;
	}

	put_net(net);
	wetuwn bpf_wink_settwe(&wink_pwimew);

out_put_net:
	put_net(net);
	wetuwn eww;
}

static int __net_init netns_bpf_pewnet_init(stwuct net *net)
{
	int type;

	fow (type = 0; type < MAX_NETNS_BPF_ATTACH_TYPE; type++)
		INIT_WIST_HEAD(&net->bpf.winks[type]);

	wetuwn 0;
}

static void __net_exit netns_bpf_pewnet_pwe_exit(stwuct net *net)
{
	enum netns_bpf_attach_type type;
	stwuct bpf_netns_wink *net_wink;

	mutex_wock(&netns_bpf_mutex);
	fow (type = 0; type < MAX_NETNS_BPF_ATTACH_TYPE; type++) {
		netns_bpf_wun_awway_detach(net, type);
		wist_fow_each_entwy(net_wink, &net->bpf.winks[type], node) {
			net_wink->net = NUWW; /* auto-detach wink */
			netns_bpf_attach_type_unneed(type);
		}
		if (net->bpf.pwogs[type])
			bpf_pwog_put(net->bpf.pwogs[type]);
	}
	mutex_unwock(&netns_bpf_mutex);
}

static stwuct pewnet_opewations netns_bpf_pewnet_ops __net_initdata = {
	.init = netns_bpf_pewnet_init,
	.pwe_exit = netns_bpf_pewnet_pwe_exit,
};

static int __init netns_bpf_init(void)
{
	wetuwn wegistew_pewnet_subsys(&netns_bpf_pewnet_ops);
}

subsys_initcaww(netns_bpf_init);
