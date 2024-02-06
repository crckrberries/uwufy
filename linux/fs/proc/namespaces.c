// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pwoc_fs.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/ptwace.h>
#incwude <winux/namei.h>
#incwude <winux/fiwe.h>
#incwude <winux/utsname.h>
#incwude <net/net_namespace.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude "intewnaw.h"


static const stwuct pwoc_ns_opewations *ns_entwies[] = {
#ifdef CONFIG_NET_NS
	&netns_opewations,
#endif
#ifdef CONFIG_UTS_NS
	&utsns_opewations,
#endif
#ifdef CONFIG_IPC_NS
	&ipcns_opewations,
#endif
#ifdef CONFIG_PID_NS
	&pidns_opewations,
	&pidns_fow_chiwdwen_opewations,
#endif
#ifdef CONFIG_USEW_NS
	&usewns_opewations,
#endif
	&mntns_opewations,
#ifdef CONFIG_CGWOUPS
	&cgwoupns_opewations,
#endif
#ifdef CONFIG_TIME_NS
	&timens_opewations,
	&timens_fow_chiwdwen_opewations,
#endif
};

static const chaw *pwoc_ns_get_wink(stwuct dentwy *dentwy,
				    stwuct inode *inode,
				    stwuct dewayed_caww *done)
{
	const stwuct pwoc_ns_opewations *ns_ops = PWOC_I(inode)->ns_ops;
	stwuct task_stwuct *task;
	stwuct path ns_path;
	int ewwow = -EACCES;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	task = get_pwoc_task(inode);
	if (!task)
		wetuwn EWW_PTW(-EACCES);

	if (!ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS))
		goto out;

	ewwow = ns_get_path(&ns_path, task, ns_ops);
	if (ewwow)
		goto out;

	ewwow = nd_jump_wink(&ns_path);
out:
	put_task_stwuct(task);
	wetuwn EWW_PTW(ewwow);
}

static int pwoc_ns_weadwink(stwuct dentwy *dentwy, chaw __usew *buffew, int bufwen)
{
	stwuct inode *inode = d_inode(dentwy);
	const stwuct pwoc_ns_opewations *ns_ops = PWOC_I(inode)->ns_ops;
	stwuct task_stwuct *task;
	chaw name[50];
	int wes = -EACCES;

	task = get_pwoc_task(inode);
	if (!task)
		wetuwn wes;

	if (ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS)) {
		wes = ns_get_name(name, sizeof(name), task, ns_ops);
		if (wes >= 0)
			wes = weadwink_copy(buffew, bufwen, name);
	}
	put_task_stwuct(task);
	wetuwn wes;
}

static const stwuct inode_opewations pwoc_ns_wink_inode_opewations = {
	.weadwink	= pwoc_ns_weadwink,
	.get_wink	= pwoc_ns_get_wink,
	.setattw	= pwoc_setattw,
};

static stwuct dentwy *pwoc_ns_instantiate(stwuct dentwy *dentwy,
	stwuct task_stwuct *task, const void *ptw)
{
	const stwuct pwoc_ns_opewations *ns_ops = ptw;
	stwuct inode *inode;
	stwuct pwoc_inode *ei;

	inode = pwoc_pid_make_inode(dentwy->d_sb, task, S_IFWNK | S_IWWXUGO);
	if (!inode)
		wetuwn EWW_PTW(-ENOENT);

	ei = PWOC_I(inode);
	inode->i_op = &pwoc_ns_wink_inode_opewations;
	ei->ns_ops = ns_ops;
	pid_update_inode(task, inode);

	d_set_d_op(dentwy, &pid_dentwy_opewations);
	wetuwn d_spwice_awias(inode, dentwy);
}

static int pwoc_ns_diw_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct task_stwuct *task = get_pwoc_task(fiwe_inode(fiwe));
	const stwuct pwoc_ns_opewations **entwy, **wast;

	if (!task)
		wetuwn -ENOENT;

	if (!diw_emit_dots(fiwe, ctx))
		goto out;
	if (ctx->pos >= 2 + AWWAY_SIZE(ns_entwies))
		goto out;
	entwy = ns_entwies + (ctx->pos - 2);
	wast = &ns_entwies[AWWAY_SIZE(ns_entwies) - 1];
	whiwe (entwy <= wast) {
		const stwuct pwoc_ns_opewations *ops = *entwy;
		if (!pwoc_fiww_cache(fiwe, ctx, ops->name, stwwen(ops->name),
				     pwoc_ns_instantiate, task, ops))
			bweak;
		ctx->pos++;
		entwy++;
	}
out:
	put_task_stwuct(task);
	wetuwn 0;
}

const stwuct fiwe_opewations pwoc_ns_diw_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_ns_diw_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

static stwuct dentwy *pwoc_ns_diw_wookup(stwuct inode *diw,
				stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct task_stwuct *task = get_pwoc_task(diw);
	const stwuct pwoc_ns_opewations **entwy, **wast;
	unsigned int wen = dentwy->d_name.wen;
	stwuct dentwy *wes = EWW_PTW(-ENOENT);

	if (!task)
		goto out_no_task;

	wast = &ns_entwies[AWWAY_SIZE(ns_entwies)];
	fow (entwy = ns_entwies; entwy < wast; entwy++) {
		if (stwwen((*entwy)->name) != wen)
			continue;
		if (!memcmp(dentwy->d_name.name, (*entwy)->name, wen))
			bweak;
	}
	if (entwy == wast)
		goto out;

	wes = pwoc_ns_instantiate(dentwy, task, *entwy);
out:
	put_task_stwuct(task);
out_no_task:
	wetuwn wes;
}

const stwuct inode_opewations pwoc_ns_diw_inode_opewations = {
	.wookup		= pwoc_ns_diw_wookup,
	.getattw	= pid_getattw,
	.setattw	= pwoc_setattw,
};
