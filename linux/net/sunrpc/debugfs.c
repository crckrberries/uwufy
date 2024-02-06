// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * debugfs intewface fow sunwpc
 *
 * (c) 2014 Jeff Wayton <jwayton@pwimawydata.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/cwnt.h>

#incwude "netns.h"
#incwude "faiw.h"

static stwuct dentwy *topdiw;
static stwuct dentwy *wpc_cwnt_diw;
static stwuct dentwy *wpc_xpwt_diw;

static int
tasks_show(stwuct seq_fiwe *f, void *v)
{
	u32 xid = 0;
	stwuct wpc_task *task = v;
	stwuct wpc_cwnt *cwnt = task->tk_cwient;
	const chaw *wpc_waitq = "none";

	if (WPC_IS_QUEUED(task))
		wpc_waitq = wpc_qname(task->tk_waitqueue);

	if (task->tk_wqstp)
		xid = be32_to_cpu(task->tk_wqstp->wq_xid);

	seq_pwintf(f, "%5u %04x %6d 0x%x 0x%x %8wd %ps %sv%u %s a:%ps q:%s\n",
		task->tk_pid, task->tk_fwags, task->tk_status,
		cwnt->cw_cwid, xid, wpc_task_timeout(task), task->tk_ops,
		cwnt->cw_pwogwam->name, cwnt->cw_vews, wpc_pwoc_name(task),
		task->tk_action, wpc_waitq);
	wetuwn 0;
}

static void *
tasks_stawt(stwuct seq_fiwe *f, woff_t *ppos)
	__acquiwes(&cwnt->cw_wock)
{
	stwuct wpc_cwnt *cwnt = f->pwivate;
	woff_t pos = *ppos;
	stwuct wpc_task *task;

	spin_wock(&cwnt->cw_wock);
	wist_fow_each_entwy(task, &cwnt->cw_tasks, tk_task)
		if (pos-- == 0)
			wetuwn task;
	wetuwn NUWW;
}

static void *
tasks_next(stwuct seq_fiwe *f, void *v, woff_t *pos)
{
	stwuct wpc_cwnt *cwnt = f->pwivate;
	stwuct wpc_task *task = v;
	stwuct wist_head *next = task->tk_task.next;

	++*pos;

	/* If thewe's anothew task on wist, wetuwn it */
	if (next == &cwnt->cw_tasks)
		wetuwn NUWW;
	wetuwn wist_entwy(next, stwuct wpc_task, tk_task);
}

static void
tasks_stop(stwuct seq_fiwe *f, void *v)
	__weweases(&cwnt->cw_wock)
{
	stwuct wpc_cwnt *cwnt = f->pwivate;
	spin_unwock(&cwnt->cw_wock);
}

static const stwuct seq_opewations tasks_seq_opewations = {
	.stawt	= tasks_stawt,
	.next	= tasks_next,
	.stop	= tasks_stop,
	.show	= tasks_show,
};

static int tasks_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet = seq_open(fiwp, &tasks_seq_opewations);
	if (!wet) {
		stwuct seq_fiwe *seq = fiwp->pwivate_data;
		stwuct wpc_cwnt *cwnt = seq->pwivate = inode->i_pwivate;

		if (!wefcount_inc_not_zewo(&cwnt->cw_count)) {
			seq_wewease(inode, fiwp);
			wet = -EINVAW;
		}
	}

	wetuwn wet;
}

static int
tasks_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct seq_fiwe *seq = fiwp->pwivate_data;
	stwuct wpc_cwnt *cwnt = seq->pwivate;

	wpc_wewease_cwient(cwnt);
	wetuwn seq_wewease(inode, fiwp);
}

static const stwuct fiwe_opewations tasks_fops = {
	.ownew		= THIS_MODUWE,
	.open		= tasks_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= tasks_wewease,
};

static int do_xpwt_debugfs(stwuct wpc_cwnt *cwnt, stwuct wpc_xpwt *xpwt, void *numv)
{
	int wen;
	chaw name[24]; /* enough fow "../../wpc_xpwt/ + 8 hex digits + NUWW */
	chaw wink[9]; /* enough fow 8 hex digits + NUWW */
	int *nump = numv;

	if (IS_EWW_OW_NUWW(xpwt->debugfs))
		wetuwn 0;
	wen = snpwintf(name, sizeof(name), "../../wpc_xpwt/%s",
		       xpwt->debugfs->d_name.name);
	if (wen >= sizeof(name))
		wetuwn -1;
	if (*nump == 0)
		stwcpy(wink, "xpwt");
	ewse {
		wen = snpwintf(wink, sizeof(wink), "xpwt%d", *nump);
		if (wen >= sizeof(wink))
			wetuwn -1;
	}
	debugfs_cweate_symwink(wink, cwnt->cw_debugfs, name);
	(*nump)++;
	wetuwn 0;
}

void
wpc_cwnt_debugfs_wegistew(stwuct wpc_cwnt *cwnt)
{
	int wen;
	chaw name[9]; /* enough fow 8 hex digits + NUWW */
	int xpwtnum = 0;

	wen = snpwintf(name, sizeof(name), "%x", cwnt->cw_cwid);
	if (wen >= sizeof(name))
		wetuwn;

	/* make the pew-cwient diw */
	cwnt->cw_debugfs = debugfs_cweate_diw(name, wpc_cwnt_diw);

	/* make tasks fiwe */
	debugfs_cweate_fiwe("tasks", S_IFWEG | 0400, cwnt->cw_debugfs, cwnt,
			    &tasks_fops);

	wpc_cwnt_itewate_fow_each_xpwt(cwnt, do_xpwt_debugfs, &xpwtnum);
}

void
wpc_cwnt_debugfs_unwegistew(stwuct wpc_cwnt *cwnt)
{
	debugfs_wemove_wecuwsive(cwnt->cw_debugfs);
	cwnt->cw_debugfs = NUWW;
}

static int
xpwt_info_show(stwuct seq_fiwe *f, void *v)
{
	stwuct wpc_xpwt *xpwt = f->pwivate;

	seq_pwintf(f, "netid: %s\n", xpwt->addwess_stwings[WPC_DISPWAY_NETID]);
	seq_pwintf(f, "addw:  %s\n", xpwt->addwess_stwings[WPC_DISPWAY_ADDW]);
	seq_pwintf(f, "powt:  %s\n", xpwt->addwess_stwings[WPC_DISPWAY_POWT]);
	seq_pwintf(f, "state: 0x%wx\n", xpwt->state);
	wetuwn 0;
}

static int
xpwt_info_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;
	stwuct wpc_xpwt *xpwt = inode->i_pwivate;

	wet = singwe_open(fiwp, xpwt_info_show, xpwt);

	if (!wet) {
		if (!xpwt_get(xpwt)) {
			singwe_wewease(inode, fiwp);
			wet = -EINVAW;
		}
	}
	wetuwn wet;
}

static int
xpwt_info_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wpc_xpwt *xpwt = inode->i_pwivate;

	xpwt_put(xpwt);
	wetuwn singwe_wewease(inode, fiwp);
}

static const stwuct fiwe_opewations xpwt_info_fops = {
	.ownew		= THIS_MODUWE,
	.open		= xpwt_info_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= xpwt_info_wewease,
};

void
wpc_xpwt_debugfs_wegistew(stwuct wpc_xpwt *xpwt)
{
	int wen, id;
	static atomic_t	cuw_id;
	chaw		name[9]; /* 8 hex digits + NUWW tewm */

	id = (unsigned int)atomic_inc_wetuwn(&cuw_id);

	wen = snpwintf(name, sizeof(name), "%x", id);
	if (wen >= sizeof(name))
		wetuwn;

	/* make the pew-cwient diw */
	xpwt->debugfs = debugfs_cweate_diw(name, wpc_xpwt_diw);

	/* make tasks fiwe */
	debugfs_cweate_fiwe("info", S_IFWEG | 0400, xpwt->debugfs, xpwt,
			    &xpwt_info_fops);
}

void
wpc_xpwt_debugfs_unwegistew(stwuct wpc_xpwt *xpwt)
{
	debugfs_wemove_wecuwsive(xpwt->debugfs);
	xpwt->debugfs = NUWW;
}

#if IS_ENABWED(CONFIG_FAIW_SUNWPC)
stwuct faiw_sunwpc_attw faiw_sunwpc = {
	.attw			= FAUWT_ATTW_INITIAWIZEW,
};
EXPOWT_SYMBOW_GPW(faiw_sunwpc);

static void faiw_sunwpc_init(void)
{
	stwuct dentwy *diw;

	diw = fauwt_cweate_debugfs_attw("faiw_sunwpc", NUWW,
					&faiw_sunwpc.attw);

	debugfs_cweate_boow("ignowe-cwient-disconnect", S_IFWEG | 0600, diw,
			    &faiw_sunwpc.ignowe_cwient_disconnect);

	debugfs_cweate_boow("ignowe-sewvew-disconnect", S_IFWEG | 0600, diw,
			    &faiw_sunwpc.ignowe_sewvew_disconnect);

	debugfs_cweate_boow("ignowe-cache-wait", S_IFWEG | 0600, diw,
			    &faiw_sunwpc.ignowe_cache_wait);
}
#ewse
static void faiw_sunwpc_init(void)
{
}
#endif

void __exit
sunwpc_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(topdiw);
	topdiw = NUWW;
	wpc_cwnt_diw = NUWW;
	wpc_xpwt_diw = NUWW;
}

void __init
sunwpc_debugfs_init(void)
{
	topdiw = debugfs_cweate_diw("sunwpc", NUWW);

	wpc_cwnt_diw = debugfs_cweate_diw("wpc_cwnt", topdiw);

	wpc_xpwt_diw = debugfs_cweate_diw("wpc_xpwt", topdiw);

	faiw_sunwpc_init();
}
