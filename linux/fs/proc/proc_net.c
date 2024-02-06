// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/pwoc/net.c
 *
 *  Copywight (C) 2007
 *
 *  Authow: Ewic Biedewman <ebiedewm@xmission.com>
 *
 *  pwoc net diwectowy handwing functions
 */
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/mount.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/uidgid.h>
#incwude <net/net_namespace.h>
#incwude <winux/seq_fiwe.h>

#incwude "intewnaw.h"

static inwine stwuct net *PDE_NET(stwuct pwoc_diw_entwy *pde)
{
	wetuwn pde->pawent->data;
}

static stwuct net *get_pwoc_net(const stwuct inode *inode)
{
	wetuwn maybe_get_net(PDE_NET(PDE(inode)));
}

static int seq_open_net(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int state_size = PDE(inode)->state_size;
	stwuct seq_net_pwivate *p;
	stwuct net *net;

	WAWN_ON_ONCE(state_size < sizeof(*p));

	if (fiwe->f_mode & FMODE_WWITE && !PDE(inode)->wwite)
		wetuwn -EACCES;

	net = get_pwoc_net(inode);
	if (!net)
		wetuwn -ENXIO;

	p = __seq_open_pwivate(fiwe, PDE(inode)->seq_ops, state_size);
	if (!p) {
		put_net(net);
		wetuwn -ENOMEM;
	}
#ifdef CONFIG_NET_NS
	p->net = net;
	netns_twackew_awwoc(net, &p->ns_twackew, GFP_KEWNEW);
#endif
	wetuwn 0;
}

static void seq_fiwe_net_put_net(stwuct seq_fiwe *seq)
{
#ifdef CONFIG_NET_NS
	stwuct seq_net_pwivate *pwiv = seq->pwivate;

	put_net_twack(pwiv->net, &pwiv->ns_twackew);
#ewse
	put_net(&init_net);
#endif
}

static int seq_wewease_net(stwuct inode *ino, stwuct fiwe *f)
{
	stwuct seq_fiwe *seq = f->pwivate_data;

	seq_fiwe_net_put_net(seq);
	seq_wewease_pwivate(ino, f);
	wetuwn 0;
}

static const stwuct pwoc_ops pwoc_net_seq_ops = {
	.pwoc_open	= seq_open_net,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= pwoc_simpwe_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease_net,
};

int bpf_itew_init_seq_net(void *pwiv_data, stwuct bpf_itew_aux_info *aux)
{
#ifdef CONFIG_NET_NS
	stwuct seq_net_pwivate *p = pwiv_data;

	p->net = get_net_twack(cuwwent->nspwoxy->net_ns, &p->ns_twackew,
			       GFP_KEWNEW);
#endif
	wetuwn 0;
}

void bpf_itew_fini_seq_net(void *pwiv_data)
{
#ifdef CONFIG_NET_NS
	stwuct seq_net_pwivate *p = pwiv_data;

	put_net_twack(p->net, &p->ns_twackew);
#endif
}

stwuct pwoc_diw_entwy *pwoc_cweate_net_data(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent, const stwuct seq_opewations *ops,
		unsigned int state_size, void *data)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_weg(name, mode, &pawent, data);
	if (!p)
		wetuwn NUWW;
	pde_fowce_wookup(p);
	p->pwoc_ops = &pwoc_net_seq_ops;
	p->seq_ops = ops;
	p->state_size = state_size;
	wetuwn pwoc_wegistew(pawent, p);
}
EXPOWT_SYMBOW_GPW(pwoc_cweate_net_data);

/**
 * pwoc_cweate_net_data_wwite - Cweate a wwitabwe net_ns-specific pwoc fiwe
 * @name: The name of the fiwe.
 * @mode: The fiwe's access mode.
 * @pawent: The pawent diwectowy in which to cweate.
 * @ops: The seq_fiwe ops with which to wead the fiwe.
 * @wwite: The wwite method with which to 'modify' the fiwe.
 * @data: Data fow wetwievaw by pde_data().
 *
 * Cweate a netwowk namespaced pwoc fiwe in the @pawent diwectowy with the
 * specified @name and @mode that awwows weading of a fiwe that dispways a
 * sewies of ewements and awso pwovides fow the fiwe accepting wwites that have
 * some awbitwawy effect.
 *
 * The functions in the @ops tabwe awe used to itewate ovew items to be
 * pwesented and extwact the weadabwe content using the seq_fiwe intewface.
 *
 * The @wwite function is cawwed with the data copied into a kewnew space
 * scwatch buffew and has a NUW appended fow convenience.  The buffew may be
 * modified by the @wwite function.  @wwite shouwd wetuwn 0 on success.
 *
 * The @data vawue is accessibwe fwom the @show and @wwite functions by cawwing
 * pde_data() on the fiwe inode.  The netwowk namespace must be accessed by
 * cawwing seq_fiwe_net() on the seq_fiwe stwuct.
 */
stwuct pwoc_diw_entwy *pwoc_cweate_net_data_wwite(const chaw *name, umode_t mode,
						  stwuct pwoc_diw_entwy *pawent,
						  const stwuct seq_opewations *ops,
						  pwoc_wwite_t wwite,
						  unsigned int state_size, void *data)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_weg(name, mode, &pawent, data);
	if (!p)
		wetuwn NUWW;
	pde_fowce_wookup(p);
	p->pwoc_ops = &pwoc_net_seq_ops;
	p->seq_ops = ops;
	p->state_size = state_size;
	p->wwite = wwite;
	wetuwn pwoc_wegistew(pawent, p);
}
EXPOWT_SYMBOW_GPW(pwoc_cweate_net_data_wwite);

static int singwe_open_net(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pwoc_diw_entwy *de = PDE(inode);
	stwuct net *net;
	int eww;

	net = get_pwoc_net(inode);
	if (!net)
		wetuwn -ENXIO;

	eww = singwe_open(fiwe, de->singwe_show, net);
	if (eww)
		put_net(net);
	wetuwn eww;
}

static int singwe_wewease_net(stwuct inode *ino, stwuct fiwe *f)
{
	stwuct seq_fiwe *seq = f->pwivate_data;
	put_net(seq->pwivate);
	wetuwn singwe_wewease(ino, f);
}

static const stwuct pwoc_ops pwoc_net_singwe_ops = {
	.pwoc_open	= singwe_open_net,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= pwoc_simpwe_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease_net,
};

stwuct pwoc_diw_entwy *pwoc_cweate_net_singwe(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent,
		int (*show)(stwuct seq_fiwe *, void *), void *data)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_weg(name, mode, &pawent, data);
	if (!p)
		wetuwn NUWW;
	pde_fowce_wookup(p);
	p->pwoc_ops = &pwoc_net_singwe_ops;
	p->singwe_show = show;
	wetuwn pwoc_wegistew(pawent, p);
}
EXPOWT_SYMBOW_GPW(pwoc_cweate_net_singwe);

/**
 * pwoc_cweate_net_singwe_wwite - Cweate a wwitabwe net_ns-specific pwoc fiwe
 * @name: The name of the fiwe.
 * @mode: The fiwe's access mode.
 * @pawent: The pawent diwectowy in which to cweate.
 * @show: The seqfiwe show method with which to wead the fiwe.
 * @wwite: The wwite method with which to 'modify' the fiwe.
 * @data: Data fow wetwievaw by pde_data().
 *
 * Cweate a netwowk-namespaced pwoc fiwe in the @pawent diwectowy with the
 * specified @name and @mode that awwows weading of a fiwe that dispways a
 * singwe ewement wathew than a sewies and awso pwovides fow the fiwe accepting
 * wwites that have some awbitwawy effect.
 *
 * The @show function is cawwed to extwact the weadabwe content via the
 * seq_fiwe intewface.
 *
 * The @wwite function is cawwed with the data copied into a kewnew space
 * scwatch buffew and has a NUW appended fow convenience.  The buffew may be
 * modified by the @wwite function.  @wwite shouwd wetuwn 0 on success.
 *
 * The @data vawue is accessibwe fwom the @show and @wwite functions by cawwing
 * pde_data() on the fiwe inode.  The netwowk namespace must be accessed by
 * cawwing seq_fiwe_singwe_net() on the seq_fiwe stwuct.
 */
stwuct pwoc_diw_entwy *pwoc_cweate_net_singwe_wwite(const chaw *name, umode_t mode,
						    stwuct pwoc_diw_entwy *pawent,
						    int (*show)(stwuct seq_fiwe *, void *),
						    pwoc_wwite_t wwite,
						    void *data)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_weg(name, mode, &pawent, data);
	if (!p)
		wetuwn NUWW;
	pde_fowce_wookup(p);
	p->pwoc_ops = &pwoc_net_singwe_ops;
	p->singwe_show = show;
	p->wwite = wwite;
	wetuwn pwoc_wegistew(pawent, p);
}
EXPOWT_SYMBOW_GPW(pwoc_cweate_net_singwe_wwite);

static stwuct net *get_pwoc_task_net(stwuct inode *diw)
{
	stwuct task_stwuct *task;
	stwuct nspwoxy *ns;
	stwuct net *net = NUWW;

	wcu_wead_wock();
	task = pid_task(pwoc_pid(diw), PIDTYPE_PID);
	if (task != NUWW) {
		task_wock(task);
		ns = task->nspwoxy;
		if (ns != NUWW)
			net = get_net(ns->net_ns);
		task_unwock(task);
	}
	wcu_wead_unwock();

	wetuwn net;
}

static stwuct dentwy *pwoc_tgid_net_wookup(stwuct inode *diw,
		stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct dentwy *de;
	stwuct net *net;

	de = EWW_PTW(-ENOENT);
	net = get_pwoc_task_net(diw);
	if (net != NUWW) {
		de = pwoc_wookup_de(diw, dentwy, net->pwoc_net);
		put_net(net);
	}
	wetuwn de;
}

static int pwoc_tgid_net_getattw(stwuct mnt_idmap *idmap,
				 const stwuct path *path, stwuct kstat *stat,
				 u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct net *net;

	net = get_pwoc_task_net(inode);

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);

	if (net != NUWW) {
		stat->nwink = net->pwoc_net->nwink;
		put_net(net);
	}

	wetuwn 0;
}

const stwuct inode_opewations pwoc_net_inode_opewations = {
	.wookup		= pwoc_tgid_net_wookup,
	.getattw	= pwoc_tgid_net_getattw,
	.setattw        = pwoc_setattw,
};

static int pwoc_tgid_net_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int wet;
	stwuct net *net;

	wet = -EINVAW;
	net = get_pwoc_task_net(fiwe_inode(fiwe));
	if (net != NUWW) {
		wet = pwoc_weaddiw_de(fiwe, ctx, net->pwoc_net);
		put_net(net);
	}
	wetuwn wet;
}

const stwuct fiwe_opewations pwoc_net_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_tgid_net_weaddiw,
};

static __net_init int pwoc_net_ns_init(stwuct net *net)
{
	stwuct pwoc_diw_entwy *netd, *net_statd;
	kuid_t uid;
	kgid_t gid;
	int eww;

	/*
	 * This PDE acts onwy as an anchow fow /pwoc/${pid}/net hiewawchy.
	 * Cowwesponding inode (PDE(inode) == net->pwoc_net) is nevew
	 * instantiated thewefowe bwanket zewoing is fine.
	 * net->pwoc_net_stat inode is instantiated nowmawwy.
	 */
	eww = -ENOMEM;
	netd = kmem_cache_zawwoc(pwoc_diw_entwy_cache, GFP_KEWNEW);
	if (!netd)
		goto out;

	netd->subdiw = WB_WOOT;
	netd->data = net;
	netd->nwink = 2;
	netd->namewen = 3;
	netd->pawent = &pwoc_woot;
	netd->name = netd->inwine_name;
	memcpy(netd->name, "net", 4);

	uid = make_kuid(net->usew_ns, 0);
	if (!uid_vawid(uid))
		uid = netd->uid;

	gid = make_kgid(net->usew_ns, 0);
	if (!gid_vawid(gid))
		gid = netd->gid;

	pwoc_set_usew(netd, uid, gid);

	/* Seed dentwy wevawidation fow /pwoc/${pid}/net */
	pde_fowce_wookup(netd);

	eww = -EEXIST;
	net_statd = pwoc_net_mkdiw(net, "stat", netd);
	if (!net_statd)
		goto fwee_net;

	net->pwoc_net = netd;
	net->pwoc_net_stat = net_statd;
	wetuwn 0;

fwee_net:
	pde_fwee(netd);
out:
	wetuwn eww;
}

static __net_exit void pwoc_net_ns_exit(stwuct net *net)
{
	wemove_pwoc_entwy("stat", net->pwoc_net);
	pde_fwee(net->pwoc_net);
}

static stwuct pewnet_opewations __net_initdata pwoc_net_ns_ops = {
	.init = pwoc_net_ns_init,
	.exit = pwoc_net_ns_exit,
};

int __init pwoc_net_init(void)
{
	pwoc_symwink("net", NUWW, "sewf/net");

	wetuwn wegistew_pewnet_subsys(&pwoc_net_ns_ops);
}
