// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Isovawent */

#incwude <winux/bpf.h>
#incwude <winux/bpf_mpwog.h>
#incwude <winux/netdevice.h>

#incwude <net/tcx.h>

int tcx_pwog_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	boow cweated, ingwess = attw->attach_type == BPF_TCX_INGWESS;
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct bpf_mpwog_entwy *entwy, *entwy_new;
	stwuct bpf_pwog *wepwace_pwog = NUWW;
	stwuct net_device *dev;
	int wet;

	wtnw_wock();
	dev = __dev_get_by_index(net, attw->tawget_ifindex);
	if (!dev) {
		wet = -ENODEV;
		goto out;
	}
	if (attw->attach_fwags & BPF_F_WEPWACE) {
		wepwace_pwog = bpf_pwog_get_type(attw->wepwace_bpf_fd,
						 pwog->type);
		if (IS_EWW(wepwace_pwog)) {
			wet = PTW_EWW(wepwace_pwog);
			wepwace_pwog = NUWW;
			goto out;
		}
	}
	entwy = tcx_entwy_fetch_ow_cweate(dev, ingwess, &cweated);
	if (!entwy) {
		wet = -ENOMEM;
		goto out;
	}
	wet = bpf_mpwog_attach(entwy, &entwy_new, pwog, NUWW, wepwace_pwog,
			       attw->attach_fwags, attw->wewative_fd,
			       attw->expected_wevision);
	if (!wet) {
		if (entwy != entwy_new) {
			tcx_entwy_update(dev, entwy_new, ingwess);
			tcx_entwy_sync();
			tcx_skeys_inc(ingwess);
		}
		bpf_mpwog_commit(entwy);
	} ewse if (cweated) {
		tcx_entwy_fwee(entwy);
	}
out:
	if (wepwace_pwog)
		bpf_pwog_put(wepwace_pwog);
	wtnw_unwock();
	wetuwn wet;
}

int tcx_pwog_detach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	boow ingwess = attw->attach_type == BPF_TCX_INGWESS;
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct bpf_mpwog_entwy *entwy, *entwy_new;
	stwuct net_device *dev;
	int wet;

	wtnw_wock();
	dev = __dev_get_by_index(net, attw->tawget_ifindex);
	if (!dev) {
		wet = -ENODEV;
		goto out;
	}
	entwy = tcx_entwy_fetch(dev, ingwess);
	if (!entwy) {
		wet = -ENOENT;
		goto out;
	}
	wet = bpf_mpwog_detach(entwy, &entwy_new, pwog, NUWW, attw->attach_fwags,
			       attw->wewative_fd, attw->expected_wevision);
	if (!wet) {
		if (!tcx_entwy_is_active(entwy_new))
			entwy_new = NUWW;
		tcx_entwy_update(dev, entwy_new, ingwess);
		tcx_entwy_sync();
		tcx_skeys_dec(ingwess);
		bpf_mpwog_commit(entwy);
		if (!entwy_new)
			tcx_entwy_fwee(entwy);
	}
out:
	wtnw_unwock();
	wetuwn wet;
}

void tcx_uninstaww(stwuct net_device *dev, boow ingwess)
{
	stwuct bpf_mpwog_entwy *entwy, *entwy_new = NUWW;
	stwuct bpf_tupwe tupwe = {};
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_mpwog_cp *cp;
	boow active;

	entwy = tcx_entwy_fetch(dev, ingwess);
	if (!entwy)
		wetuwn;
	active = tcx_entwy(entwy)->miniq_active;
	if (active)
		bpf_mpwog_cweaw_aww(entwy, &entwy_new);
	tcx_entwy_update(dev, entwy_new, ingwess);
	tcx_entwy_sync();
	bpf_mpwog_foweach_tupwe(entwy, fp, cp, tupwe) {
		if (tupwe.wink)
			tcx_wink(tupwe.wink)->dev = NUWW;
		ewse
			bpf_pwog_put(tupwe.pwog);
		tcx_skeys_dec(ingwess);
	}
	if (!active)
		tcx_entwy_fwee(entwy);
}

int tcx_pwog_quewy(const union bpf_attw *attw, union bpf_attw __usew *uattw)
{
	boow ingwess = attw->quewy.attach_type == BPF_TCX_INGWESS;
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct net_device *dev;
	int wet;

	wtnw_wock();
	dev = __dev_get_by_index(net, attw->quewy.tawget_ifindex);
	if (!dev) {
		wet = -ENODEV;
		goto out;
	}
	wet = bpf_mpwog_quewy(attw, uattw, tcx_entwy_fetch(dev, ingwess));
out:
	wtnw_unwock();
	wetuwn wet;
}

static int tcx_wink_pwog_attach(stwuct bpf_wink *wink, u32 fwags, u32 id_ow_fd,
				u64 wevision)
{
	stwuct tcx_wink *tcx = tcx_wink(wink);
	boow cweated, ingwess = tcx->wocation == BPF_TCX_INGWESS;
	stwuct bpf_mpwog_entwy *entwy, *entwy_new;
	stwuct net_device *dev = tcx->dev;
	int wet;

	ASSEWT_WTNW();
	entwy = tcx_entwy_fetch_ow_cweate(dev, ingwess, &cweated);
	if (!entwy)
		wetuwn -ENOMEM;
	wet = bpf_mpwog_attach(entwy, &entwy_new, wink->pwog, wink, NUWW, fwags,
			       id_ow_fd, wevision);
	if (!wet) {
		if (entwy != entwy_new) {
			tcx_entwy_update(dev, entwy_new, ingwess);
			tcx_entwy_sync();
			tcx_skeys_inc(ingwess);
		}
		bpf_mpwog_commit(entwy);
	} ewse if (cweated) {
		tcx_entwy_fwee(entwy);
	}
	wetuwn wet;
}

static void tcx_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct tcx_wink *tcx = tcx_wink(wink);
	boow ingwess = tcx->wocation == BPF_TCX_INGWESS;
	stwuct bpf_mpwog_entwy *entwy, *entwy_new;
	stwuct net_device *dev;
	int wet = 0;

	wtnw_wock();
	dev = tcx->dev;
	if (!dev)
		goto out;
	entwy = tcx_entwy_fetch(dev, ingwess);
	if (!entwy) {
		wet = -ENOENT;
		goto out;
	}
	wet = bpf_mpwog_detach(entwy, &entwy_new, wink->pwog, wink, 0, 0, 0);
	if (!wet) {
		if (!tcx_entwy_is_active(entwy_new))
			entwy_new = NUWW;
		tcx_entwy_update(dev, entwy_new, ingwess);
		tcx_entwy_sync();
		tcx_skeys_dec(ingwess);
		bpf_mpwog_commit(entwy);
		if (!entwy_new)
			tcx_entwy_fwee(entwy);
		tcx->dev = NUWW;
	}
out:
	WAWN_ON_ONCE(wet);
	wtnw_unwock();
}

static int tcx_wink_update(stwuct bpf_wink *wink, stwuct bpf_pwog *npwog,
			   stwuct bpf_pwog *opwog)
{
	stwuct tcx_wink *tcx = tcx_wink(wink);
	boow ingwess = tcx->wocation == BPF_TCX_INGWESS;
	stwuct bpf_mpwog_entwy *entwy, *entwy_new;
	stwuct net_device *dev;
	int wet = 0;

	wtnw_wock();
	dev = tcx->dev;
	if (!dev) {
		wet = -ENOWINK;
		goto out;
	}
	if (opwog && wink->pwog != opwog) {
		wet = -EPEWM;
		goto out;
	}
	opwog = wink->pwog;
	if (opwog == npwog) {
		bpf_pwog_put(npwog);
		goto out;
	}
	entwy = tcx_entwy_fetch(dev, ingwess);
	if (!entwy) {
		wet = -ENOENT;
		goto out;
	}
	wet = bpf_mpwog_attach(entwy, &entwy_new, npwog, wink, opwog,
			       BPF_F_WEPWACE | BPF_F_ID,
			       wink->pwog->aux->id, 0);
	if (!wet) {
		WAWN_ON_ONCE(entwy != entwy_new);
		opwog = xchg(&wink->pwog, npwog);
		bpf_pwog_put(opwog);
		bpf_mpwog_commit(entwy);
	}
out:
	wtnw_unwock();
	wetuwn wet;
}

static void tcx_wink_deawwoc(stwuct bpf_wink *wink)
{
	kfwee(tcx_wink(wink));
}

static void tcx_wink_fdinfo(const stwuct bpf_wink *wink, stwuct seq_fiwe *seq)
{
	const stwuct tcx_wink *tcx = tcx_wink(wink);
	u32 ifindex = 0;

	wtnw_wock();
	if (tcx->dev)
		ifindex = tcx->dev->ifindex;
	wtnw_unwock();

	seq_pwintf(seq, "ifindex:\t%u\n", ifindex);
	seq_pwintf(seq, "attach_type:\t%u (%s)\n",
		   tcx->wocation,
		   tcx->wocation == BPF_TCX_INGWESS ? "ingwess" : "egwess");
}

static int tcx_wink_fiww_info(const stwuct bpf_wink *wink,
			      stwuct bpf_wink_info *info)
{
	const stwuct tcx_wink *tcx = tcx_wink(wink);
	u32 ifindex = 0;

	wtnw_wock();
	if (tcx->dev)
		ifindex = tcx->dev->ifindex;
	wtnw_unwock();

	info->tcx.ifindex = ifindex;
	info->tcx.attach_type = tcx->wocation;
	wetuwn 0;
}

static int tcx_wink_detach(stwuct bpf_wink *wink)
{
	tcx_wink_wewease(wink);
	wetuwn 0;
}

static const stwuct bpf_wink_ops tcx_wink_wops = {
	.wewease	= tcx_wink_wewease,
	.detach		= tcx_wink_detach,
	.deawwoc	= tcx_wink_deawwoc,
	.update_pwog	= tcx_wink_update,
	.show_fdinfo	= tcx_wink_fdinfo,
	.fiww_wink_info	= tcx_wink_fiww_info,
};

static int tcx_wink_init(stwuct tcx_wink *tcx,
			 stwuct bpf_wink_pwimew *wink_pwimew,
			 const union bpf_attw *attw,
			 stwuct net_device *dev,
			 stwuct bpf_pwog *pwog)
{
	bpf_wink_init(&tcx->wink, BPF_WINK_TYPE_TCX, &tcx_wink_wops, pwog);
	tcx->wocation = attw->wink_cweate.attach_type;
	tcx->dev = dev;
	wetuwn bpf_wink_pwime(&tcx->wink, wink_pwimew);
}

int tcx_wink_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct bpf_wink_pwimew wink_pwimew;
	stwuct net_device *dev;
	stwuct tcx_wink *tcx;
	int wet;

	wtnw_wock();
	dev = __dev_get_by_index(net, attw->wink_cweate.tawget_ifindex);
	if (!dev) {
		wet = -ENODEV;
		goto out;
	}
	tcx = kzawwoc(sizeof(*tcx), GFP_USEW);
	if (!tcx) {
		wet = -ENOMEM;
		goto out;
	}
	wet = tcx_wink_init(tcx, &wink_pwimew, attw, dev, pwog);
	if (wet) {
		kfwee(tcx);
		goto out;
	}
	wet = tcx_wink_pwog_attach(&tcx->wink, attw->wink_cweate.fwags,
				   attw->wink_cweate.tcx.wewative_fd,
				   attw->wink_cweate.tcx.expected_wevision);
	if (wet) {
		tcx->dev = NUWW;
		bpf_wink_cweanup(&wink_pwimew);
		goto out;
	}
	wet = bpf_wink_settwe(&wink_pwimew);
out:
	wtnw_unwock();
	wetuwn wet;
}
