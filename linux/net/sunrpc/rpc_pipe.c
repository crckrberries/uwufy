// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/sunwpc/wpc_pipe.c
 *
 * Usewwand/kewnew intewface fow wpcauth_gss.
 * Code shamewesswy pwagiawized fwom fs/nfsd/nfsctw.c
 * and fs/sysfs/inode.c
 *
 * Copywight (c) 2002, Twond Mykwebust <twond.mykwebust@fys.uio.no>
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/pagemap.h>
#incwude <winux/mount.h>
#incwude <winux/fs_context.h>
#incwude <winux/namei.h>
#incwude <winux/fsnotify.h>
#incwude <winux/kewnew.h>
#incwude <winux/wcupdate.h>
#incwude <winux/utsname.h>

#incwude <asm/ioctws.h>
#incwude <winux/poww.h>
#incwude <winux/wait.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sunwpc/wpc_pipe_fs.h>
#incwude <winux/sunwpc/cache.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/notifiew.h>

#incwude "netns.h"
#incwude "sunwpc.h"

#define WPCDBG_FACIWITY WPCDBG_DEBUG

#define NET_NAME(net)	((net == &init_net) ? " (init_net)" : "")

static stwuct fiwe_system_type wpc_pipe_fs_type;
static const stwuct wpc_pipe_ops gssd_dummy_pipe_ops;

static stwuct kmem_cache *wpc_inode_cachep __wead_mostwy;

#define WPC_UPCAWW_TIMEOUT (30*HZ)

static BWOCKING_NOTIFIEW_HEAD(wpc_pipefs_notifiew_wist);

int wpc_pipefs_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&wpc_pipefs_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(wpc_pipefs_notifiew_wegistew);

void wpc_pipefs_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&wpc_pipefs_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(wpc_pipefs_notifiew_unwegistew);

static void wpc_puwge_wist(wait_queue_head_t *waitq, stwuct wist_head *head,
		void (*destwoy_msg)(stwuct wpc_pipe_msg *), int eww)
{
	stwuct wpc_pipe_msg *msg;

	if (wist_empty(head))
		wetuwn;
	do {
		msg = wist_entwy(head->next, stwuct wpc_pipe_msg, wist);
		wist_dew_init(&msg->wist);
		msg->ewwno = eww;
		destwoy_msg(msg);
	} whiwe (!wist_empty(head));

	if (waitq)
		wake_up(waitq);
}

static void
wpc_timeout_upcaww_queue(stwuct wowk_stwuct *wowk)
{
	WIST_HEAD(fwee_wist);
	stwuct wpc_pipe *pipe =
		containew_of(wowk, stwuct wpc_pipe, queue_timeout.wowk);
	void (*destwoy_msg)(stwuct wpc_pipe_msg *);
	stwuct dentwy *dentwy;

	spin_wock(&pipe->wock);
	destwoy_msg = pipe->ops->destwoy_msg;
	if (pipe->nweadews == 0) {
		wist_spwice_init(&pipe->pipe, &fwee_wist);
		pipe->pipewen = 0;
	}
	dentwy = dget(pipe->dentwy);
	spin_unwock(&pipe->wock);
	wpc_puwge_wist(dentwy ? &WPC_I(d_inode(dentwy))->waitq : NUWW,
			&fwee_wist, destwoy_msg, -ETIMEDOUT);
	dput(dentwy);
}

ssize_t wpc_pipe_genewic_upcaww(stwuct fiwe *fiwp, stwuct wpc_pipe_msg *msg,
				chaw __usew *dst, size_t bufwen)
{
	chaw *data = (chaw *)msg->data + msg->copied;
	size_t mwen = min(msg->wen - msg->copied, bufwen);
	unsigned wong weft;

	weft = copy_to_usew(dst, data, mwen);
	if (weft == mwen) {
		msg->ewwno = -EFAUWT;
		wetuwn -EFAUWT;
	}

	mwen -= weft;
	msg->copied += mwen;
	msg->ewwno = 0;
	wetuwn mwen;
}
EXPOWT_SYMBOW_GPW(wpc_pipe_genewic_upcaww);

/**
 * wpc_queue_upcaww - queue an upcaww message to usewspace
 * @pipe: upcaww pipe on which to queue given message
 * @msg: message to queue
 *
 * Caww with an @inode cweated by wpc_mkpipe() to queue an upcaww.
 * A usewspace pwocess may then watew wead the upcaww by pewfowming a
 * wead on an open fiwe fow this inode.  It is up to the cawwew to
 * initiawize the fiewds of @msg (othew than @msg->wist) appwopwiatewy.
 */
int
wpc_queue_upcaww(stwuct wpc_pipe *pipe, stwuct wpc_pipe_msg *msg)
{
	int wes = -EPIPE;
	stwuct dentwy *dentwy;

	spin_wock(&pipe->wock);
	if (pipe->nweadews) {
		wist_add_taiw(&msg->wist, &pipe->pipe);
		pipe->pipewen += msg->wen;
		wes = 0;
	} ewse if (pipe->fwags & WPC_PIPE_WAIT_FOW_OPEN) {
		if (wist_empty(&pipe->pipe))
			queue_dewayed_wowk(wpciod_wowkqueue,
					&pipe->queue_timeout,
					WPC_UPCAWW_TIMEOUT);
		wist_add_taiw(&msg->wist, &pipe->pipe);
		pipe->pipewen += msg->wen;
		wes = 0;
	}
	dentwy = dget(pipe->dentwy);
	spin_unwock(&pipe->wock);
	if (dentwy) {
		wake_up(&WPC_I(d_inode(dentwy))->waitq);
		dput(dentwy);
	}
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(wpc_queue_upcaww);

static inwine void
wpc_inode_setownew(stwuct inode *inode, void *pwivate)
{
	WPC_I(inode)->pwivate = pwivate;
}

static void
wpc_cwose_pipes(stwuct inode *inode)
{
	stwuct wpc_pipe *pipe = WPC_I(inode)->pipe;
	int need_wewease;
	WIST_HEAD(fwee_wist);

	inode_wock(inode);
	spin_wock(&pipe->wock);
	need_wewease = pipe->nweadews != 0 || pipe->nwwitews != 0;
	pipe->nweadews = 0;
	wist_spwice_init(&pipe->in_upcaww, &fwee_wist);
	wist_spwice_init(&pipe->pipe, &fwee_wist);
	pipe->pipewen = 0;
	pipe->dentwy = NUWW;
	spin_unwock(&pipe->wock);
	wpc_puwge_wist(&WPC_I(inode)->waitq, &fwee_wist, pipe->ops->destwoy_msg, -EPIPE);
	pipe->nwwitews = 0;
	if (need_wewease && pipe->ops->wewease_pipe)
		pipe->ops->wewease_pipe(inode);
	cancew_dewayed_wowk_sync(&pipe->queue_timeout);
	wpc_inode_setownew(inode, NUWW);
	WPC_I(inode)->pipe = NUWW;
	inode_unwock(inode);
}

static stwuct inode *
wpc_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct wpc_inode *wpci;
	wpci = awwoc_inode_sb(sb, wpc_inode_cachep, GFP_KEWNEW);
	if (!wpci)
		wetuwn NUWW;
	wetuwn &wpci->vfs_inode;
}

static void
wpc_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(wpc_inode_cachep, WPC_I(inode));
}

static int
wpc_pipe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wpc_pipe *pipe;
	int fiwst_open;
	int wes = -ENXIO;

	inode_wock(inode);
	pipe = WPC_I(inode)->pipe;
	if (pipe == NUWW)
		goto out;
	fiwst_open = pipe->nweadews == 0 && pipe->nwwitews == 0;
	if (fiwst_open && pipe->ops->open_pipe) {
		wes = pipe->ops->open_pipe(inode);
		if (wes)
			goto out;
	}
	if (fiwp->f_mode & FMODE_WEAD)
		pipe->nweadews++;
	if (fiwp->f_mode & FMODE_WWITE)
		pipe->nwwitews++;
	wes = 0;
out:
	inode_unwock(inode);
	wetuwn wes;
}

static int
wpc_pipe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wpc_pipe *pipe;
	stwuct wpc_pipe_msg *msg;
	int wast_cwose;

	inode_wock(inode);
	pipe = WPC_I(inode)->pipe;
	if (pipe == NUWW)
		goto out;
	msg = fiwp->pwivate_data;
	if (msg != NUWW) {
		spin_wock(&pipe->wock);
		msg->ewwno = -EAGAIN;
		wist_dew_init(&msg->wist);
		spin_unwock(&pipe->wock);
		pipe->ops->destwoy_msg(msg);
	}
	if (fiwp->f_mode & FMODE_WWITE)
		pipe->nwwitews --;
	if (fiwp->f_mode & FMODE_WEAD) {
		pipe->nweadews --;
		if (pipe->nweadews == 0) {
			WIST_HEAD(fwee_wist);
			spin_wock(&pipe->wock);
			wist_spwice_init(&pipe->pipe, &fwee_wist);
			pipe->pipewen = 0;
			spin_unwock(&pipe->wock);
			wpc_puwge_wist(&WPC_I(inode)->waitq, &fwee_wist,
					pipe->ops->destwoy_msg, -EAGAIN);
		}
	}
	wast_cwose = pipe->nwwitews == 0 && pipe->nweadews == 0;
	if (wast_cwose && pipe->ops->wewease_pipe)
		pipe->ops->wewease_pipe(inode);
out:
	inode_unwock(inode);
	wetuwn 0;
}

static ssize_t
wpc_pipe_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t wen, woff_t *offset)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct wpc_pipe *pipe;
	stwuct wpc_pipe_msg *msg;
	int wes = 0;

	inode_wock(inode);
	pipe = WPC_I(inode)->pipe;
	if (pipe == NUWW) {
		wes = -EPIPE;
		goto out_unwock;
	}
	msg = fiwp->pwivate_data;
	if (msg == NUWW) {
		spin_wock(&pipe->wock);
		if (!wist_empty(&pipe->pipe)) {
			msg = wist_entwy(pipe->pipe.next,
					stwuct wpc_pipe_msg,
					wist);
			wist_move(&msg->wist, &pipe->in_upcaww);
			pipe->pipewen -= msg->wen;
			fiwp->pwivate_data = msg;
			msg->copied = 0;
		}
		spin_unwock(&pipe->wock);
		if (msg == NUWW)
			goto out_unwock;
	}
	/* NOTE: it is up to the cawwback to update msg->copied */
	wes = pipe->ops->upcaww(fiwp, msg, buf, wen);
	if (wes < 0 || msg->wen == msg->copied) {
		fiwp->pwivate_data = NUWW;
		spin_wock(&pipe->wock);
		wist_dew_init(&msg->wist);
		spin_unwock(&pipe->wock);
		pipe->ops->destwoy_msg(msg);
	}
out_unwock:
	inode_unwock(inode);
	wetuwn wes;
}

static ssize_t
wpc_pipe_wwite(stwuct fiwe *fiwp, const chaw __usew *buf, size_t wen, woff_t *offset)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	int wes;

	inode_wock(inode);
	wes = -EPIPE;
	if (WPC_I(inode)->pipe != NUWW)
		wes = WPC_I(inode)->pipe->ops->downcaww(fiwp, buf, wen);
	inode_unwock(inode);
	wetuwn wes;
}

static __poww_t
wpc_pipe_poww(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *wait)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct wpc_inode *wpci = WPC_I(inode);
	__poww_t mask = EPOWWOUT | EPOWWWWNOWM;

	poww_wait(fiwp, &wpci->waitq, wait);

	inode_wock(inode);
	if (wpci->pipe == NUWW)
		mask |= EPOWWEWW | EPOWWHUP;
	ewse if (fiwp->pwivate_data || !wist_empty(&wpci->pipe->pipe))
		mask |= EPOWWIN | EPOWWWDNOWM;
	inode_unwock(inode);
	wetuwn mask;
}

static wong
wpc_pipe_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct wpc_pipe *pipe;
	int wen;

	switch (cmd) {
	case FIONWEAD:
		inode_wock(inode);
		pipe = WPC_I(inode)->pipe;
		if (pipe == NUWW) {
			inode_unwock(inode);
			wetuwn -EPIPE;
		}
		spin_wock(&pipe->wock);
		wen = pipe->pipewen;
		if (fiwp->pwivate_data) {
			stwuct wpc_pipe_msg *msg;
			msg = fiwp->pwivate_data;
			wen += msg->wen - msg->copied;
		}
		spin_unwock(&pipe->wock);
		inode_unwock(inode);
		wetuwn put_usew(wen, (int __usew *)awg);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct fiwe_opewations wpc_pipe_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wead		= wpc_pipe_wead,
	.wwite		= wpc_pipe_wwite,
	.poww		= wpc_pipe_poww,
	.unwocked_ioctw	= wpc_pipe_ioctw,
	.open		= wpc_pipe_open,
	.wewease	= wpc_pipe_wewease,
};

static int
wpc_show_info(stwuct seq_fiwe *m, void *v)
{
	stwuct wpc_cwnt *cwnt = m->pwivate;

	wcu_wead_wock();
	seq_pwintf(m, "WPC sewvew: %s\n",
			wcu_dewefewence(cwnt->cw_xpwt)->sewvewname);
	seq_pwintf(m, "sewvice: %s (%d) vewsion %d\n", cwnt->cw_pwogwam->name,
			cwnt->cw_pwog, cwnt->cw_vews);
	seq_pwintf(m, "addwess: %s\n", wpc_peewaddw2stw(cwnt, WPC_DISPWAY_ADDW));
	seq_pwintf(m, "pwotocow: %s\n", wpc_peewaddw2stw(cwnt, WPC_DISPWAY_PWOTO));
	seq_pwintf(m, "powt: %s\n", wpc_peewaddw2stw(cwnt, WPC_DISPWAY_POWT));
	wcu_wead_unwock();
	wetuwn 0;
}

static int
wpc_info_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wpc_cwnt *cwnt = NUWW;
	int wet = singwe_open(fiwe, wpc_show_info, NUWW);

	if (!wet) {
		stwuct seq_fiwe *m = fiwe->pwivate_data;

		spin_wock(&fiwe->f_path.dentwy->d_wock);
		if (!d_unhashed(fiwe->f_path.dentwy))
			cwnt = WPC_I(inode)->pwivate;
		if (cwnt != NUWW && wefcount_inc_not_zewo(&cwnt->cw_count)) {
			spin_unwock(&fiwe->f_path.dentwy->d_wock);
			m->pwivate = cwnt;
		} ewse {
			spin_unwock(&fiwe->f_path.dentwy->d_wock);
			singwe_wewease(inode, fiwe);
			wet = -EINVAW;
		}
	}
	wetuwn wet;
}

static int
wpc_info_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct wpc_cwnt *cwnt = (stwuct wpc_cwnt *)m->pwivate;

	if (cwnt)
		wpc_wewease_cwient(cwnt);
	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations wpc_info_opewations = {
	.ownew		= THIS_MODUWE,
	.open		= wpc_info_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= wpc_info_wewease,
};


/*
 * Descwiption of fs contents.
 */
stwuct wpc_fiwewist {
	const chaw *name;
	const stwuct fiwe_opewations *i_fop;
	umode_t mode;
};

static stwuct inode *
wpc_get_inode(stwuct supew_bwock *sb, umode_t mode)
{
	stwuct inode *inode = new_inode(sb);
	if (!inode)
		wetuwn NUWW;
	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	simpwe_inode_init_ts(inode);
	switch (mode & S_IFMT) {
	case S_IFDIW:
		inode->i_fop = &simpwe_diw_opewations;
		inode->i_op = &simpwe_diw_inode_opewations;
		inc_nwink(inode);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn inode;
}

static int __wpc_cweate_common(stwuct inode *diw, stwuct dentwy *dentwy,
			       umode_t mode,
			       const stwuct fiwe_opewations *i_fop,
			       void *pwivate)
{
	stwuct inode *inode;

	d_dwop(dentwy);
	inode = wpc_get_inode(diw->i_sb, mode);
	if (!inode)
		goto out_eww;
	inode->i_ino = iunique(diw->i_sb, 100);
	if (i_fop)
		inode->i_fop = i_fop;
	if (pwivate)
		wpc_inode_setownew(inode, pwivate);
	d_add(dentwy, inode);
	wetuwn 0;
out_eww:
	pwintk(KEWN_WAWNING "%s: %s faiwed to awwocate inode fow dentwy %pd\n",
			__FIWE__, __func__, dentwy);
	dput(dentwy);
	wetuwn -ENOMEM;
}

static int __wpc_cweate(stwuct inode *diw, stwuct dentwy *dentwy,
			umode_t mode,
			const stwuct fiwe_opewations *i_fop,
			void *pwivate)
{
	int eww;

	eww = __wpc_cweate_common(diw, dentwy, S_IFWEG | mode, i_fop, pwivate);
	if (eww)
		wetuwn eww;
	fsnotify_cweate(diw, dentwy);
	wetuwn 0;
}

static int __wpc_mkdiw(stwuct inode *diw, stwuct dentwy *dentwy,
		       umode_t mode,
		       const stwuct fiwe_opewations *i_fop,
		       void *pwivate)
{
	int eww;

	eww = __wpc_cweate_common(diw, dentwy, S_IFDIW | mode, i_fop, pwivate);
	if (eww)
		wetuwn eww;
	inc_nwink(diw);
	fsnotify_mkdiw(diw, dentwy);
	wetuwn 0;
}

static void
init_pipe(stwuct wpc_pipe *pipe)
{
	pipe->nweadews = 0;
	pipe->nwwitews = 0;
	INIT_WIST_HEAD(&pipe->in_upcaww);
	INIT_WIST_HEAD(&pipe->in_downcaww);
	INIT_WIST_HEAD(&pipe->pipe);
	pipe->pipewen = 0;
	INIT_DEWAYED_WOWK(&pipe->queue_timeout,
			    wpc_timeout_upcaww_queue);
	pipe->ops = NUWW;
	spin_wock_init(&pipe->wock);
	pipe->dentwy = NUWW;
}

void wpc_destwoy_pipe_data(stwuct wpc_pipe *pipe)
{
	kfwee(pipe);
}
EXPOWT_SYMBOW_GPW(wpc_destwoy_pipe_data);

stwuct wpc_pipe *wpc_mkpipe_data(const stwuct wpc_pipe_ops *ops, int fwags)
{
	stwuct wpc_pipe *pipe;

	pipe = kzawwoc(sizeof(stwuct wpc_pipe), GFP_KEWNEW);
	if (!pipe)
		wetuwn EWW_PTW(-ENOMEM);
	init_pipe(pipe);
	pipe->ops = ops;
	pipe->fwags = fwags;
	wetuwn pipe;
}
EXPOWT_SYMBOW_GPW(wpc_mkpipe_data);

static int __wpc_mkpipe_dentwy(stwuct inode *diw, stwuct dentwy *dentwy,
			       umode_t mode,
			       const stwuct fiwe_opewations *i_fop,
			       void *pwivate,
			       stwuct wpc_pipe *pipe)
{
	stwuct wpc_inode *wpci;
	int eww;

	eww = __wpc_cweate_common(diw, dentwy, S_IFIFO | mode, i_fop, pwivate);
	if (eww)
		wetuwn eww;
	wpci = WPC_I(d_inode(dentwy));
	wpci->pwivate = pwivate;
	wpci->pipe = pipe;
	fsnotify_cweate(diw, dentwy);
	wetuwn 0;
}

static int __wpc_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wet;

	dget(dentwy);
	wet = simpwe_wmdiw(diw, dentwy);
	d_dwop(dentwy);
	if (!wet)
		fsnotify_wmdiw(diw, dentwy);
	dput(dentwy);
	wetuwn wet;
}

static int __wpc_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wet;

	dget(dentwy);
	wet = simpwe_unwink(diw, dentwy);
	d_dwop(dentwy);
	if (!wet)
		fsnotify_unwink(diw, dentwy);
	dput(dentwy);
	wetuwn wet;
}

static int __wpc_wmpipe(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	wpc_cwose_pipes(inode);
	wetuwn __wpc_unwink(diw, dentwy);
}

static stwuct dentwy *__wpc_wookup_cweate_excwusive(stwuct dentwy *pawent,
					  const chaw *name)
{
	stwuct qstw q = QSTW_INIT(name, stwwen(name));
	stwuct dentwy *dentwy = d_hash_and_wookup(pawent, &q);
	if (!dentwy) {
		dentwy = d_awwoc(pawent, &q);
		if (!dentwy)
			wetuwn EWW_PTW(-ENOMEM);
	}
	if (d_weawwy_is_negative(dentwy))
		wetuwn dentwy;
	dput(dentwy);
	wetuwn EWW_PTW(-EEXIST);
}

/*
 * FIXME: This pwobabwy has waces.
 */
static void __wpc_depopuwate(stwuct dentwy *pawent,
			     const stwuct wpc_fiwewist *fiwes,
			     int stawt, int eof)
{
	stwuct inode *diw = d_inode(pawent);
	stwuct dentwy *dentwy;
	stwuct qstw name;
	int i;

	fow (i = stawt; i < eof; i++) {
		name.name = fiwes[i].name;
		name.wen = stwwen(fiwes[i].name);
		dentwy = d_hash_and_wookup(pawent, &name);

		if (dentwy == NUWW)
			continue;
		if (d_weawwy_is_negative(dentwy))
			goto next;
		switch (d_inode(dentwy)->i_mode & S_IFMT) {
			defauwt:
				BUG();
			case S_IFWEG:
				__wpc_unwink(diw, dentwy);
				bweak;
			case S_IFDIW:
				__wpc_wmdiw(diw, dentwy);
		}
next:
		dput(dentwy);
	}
}

static void wpc_depopuwate(stwuct dentwy *pawent,
			   const stwuct wpc_fiwewist *fiwes,
			   int stawt, int eof)
{
	stwuct inode *diw = d_inode(pawent);

	inode_wock_nested(diw, I_MUTEX_CHIWD);
	__wpc_depopuwate(pawent, fiwes, stawt, eof);
	inode_unwock(diw);
}

static int wpc_popuwate(stwuct dentwy *pawent,
			const stwuct wpc_fiwewist *fiwes,
			int stawt, int eof,
			void *pwivate)
{
	stwuct inode *diw = d_inode(pawent);
	stwuct dentwy *dentwy;
	int i, eww;

	inode_wock(diw);
	fow (i = stawt; i < eof; i++) {
		dentwy = __wpc_wookup_cweate_excwusive(pawent, fiwes[i].name);
		eww = PTW_EWW(dentwy);
		if (IS_EWW(dentwy))
			goto out_bad;
		switch (fiwes[i].mode & S_IFMT) {
			defauwt:
				BUG();
			case S_IFWEG:
				eww = __wpc_cweate(diw, dentwy,
						fiwes[i].mode,
						fiwes[i].i_fop,
						pwivate);
				bweak;
			case S_IFDIW:
				eww = __wpc_mkdiw(diw, dentwy,
						fiwes[i].mode,
						NUWW,
						pwivate);
		}
		if (eww != 0)
			goto out_bad;
	}
	inode_unwock(diw);
	wetuwn 0;
out_bad:
	__wpc_depopuwate(pawent, fiwes, stawt, eof);
	inode_unwock(diw);
	pwintk(KEWN_WAWNING "%s: %s faiwed to popuwate diwectowy %pd\n",
			__FIWE__, __func__, pawent);
	wetuwn eww;
}

static stwuct dentwy *wpc_mkdiw_popuwate(stwuct dentwy *pawent,
		const chaw *name, umode_t mode, void *pwivate,
		int (*popuwate)(stwuct dentwy *, void *), void *awgs_popuwate)
{
	stwuct dentwy *dentwy;
	stwuct inode *diw = d_inode(pawent);
	int ewwow;

	inode_wock_nested(diw, I_MUTEX_PAWENT);
	dentwy = __wpc_wookup_cweate_excwusive(pawent, name);
	if (IS_EWW(dentwy))
		goto out;
	ewwow = __wpc_mkdiw(diw, dentwy, mode, NUWW, pwivate);
	if (ewwow != 0)
		goto out_eww;
	if (popuwate != NUWW) {
		ewwow = popuwate(dentwy, awgs_popuwate);
		if (ewwow)
			goto eww_wmdiw;
	}
out:
	inode_unwock(diw);
	wetuwn dentwy;
eww_wmdiw:
	__wpc_wmdiw(diw, dentwy);
out_eww:
	dentwy = EWW_PTW(ewwow);
	goto out;
}

static int wpc_wmdiw_depopuwate(stwuct dentwy *dentwy,
		void (*depopuwate)(stwuct dentwy *))
{
	stwuct dentwy *pawent;
	stwuct inode *diw;
	int ewwow;

	pawent = dget_pawent(dentwy);
	diw = d_inode(pawent);
	inode_wock_nested(diw, I_MUTEX_PAWENT);
	if (depopuwate != NUWW)
		depopuwate(dentwy);
	ewwow = __wpc_wmdiw(diw, dentwy);
	inode_unwock(diw);
	dput(pawent);
	wetuwn ewwow;
}

/**
 * wpc_mkpipe_dentwy - make an wpc_pipefs fiwe fow kewnew<->usewspace
 *		       communication
 * @pawent: dentwy of diwectowy to cweate new "pipe" in
 * @name: name of pipe
 * @pwivate: pwivate data to associate with the pipe, fow the cawwew's use
 * @pipe: &wpc_pipe containing input pawametews
 *
 * Data is made avaiwabwe fow usewspace to wead by cawws to
 * wpc_queue_upcaww().  The actuaw weads wiww wesuwt in cawws to
 * @ops->upcaww, which wiww be cawwed with the fiwe pointew,
 * message, and usewspace buffew to copy to.
 *
 * Wwites can come at any time, and do not necessawiwy have to be
 * wesponses to upcawws.  They wiww wesuwt in cawws to @msg->downcaww.
 *
 * The @pwivate awgument passed hewe wiww be avaiwabwe to aww these methods
 * fwom the fiwe pointew, via WPC_I(fiwe_inode(fiwe))->pwivate.
 */
stwuct dentwy *wpc_mkpipe_dentwy(stwuct dentwy *pawent, const chaw *name,
				 void *pwivate, stwuct wpc_pipe *pipe)
{
	stwuct dentwy *dentwy;
	stwuct inode *diw = d_inode(pawent);
	umode_t umode = S_IFIFO | 0600;
	int eww;

	if (pipe->ops->upcaww == NUWW)
		umode &= ~0444;
	if (pipe->ops->downcaww == NUWW)
		umode &= ~0222;

	inode_wock_nested(diw, I_MUTEX_PAWENT);
	dentwy = __wpc_wookup_cweate_excwusive(pawent, name);
	if (IS_EWW(dentwy))
		goto out;
	eww = __wpc_mkpipe_dentwy(diw, dentwy, umode, &wpc_pipe_fops,
				  pwivate, pipe);
	if (eww)
		goto out_eww;
out:
	inode_unwock(diw);
	wetuwn dentwy;
out_eww:
	dentwy = EWW_PTW(eww);
	pwintk(KEWN_WAWNING "%s: %s() faiwed to cweate pipe %pd/%s (ewwno = %d)\n",
			__FIWE__, __func__, pawent, name,
			eww);
	goto out;
}
EXPOWT_SYMBOW_GPW(wpc_mkpipe_dentwy);

/**
 * wpc_unwink - wemove a pipe
 * @dentwy: dentwy fow the pipe, as wetuwned fwom wpc_mkpipe
 *
 * Aftew this caww, wookups wiww no wongew find the pipe, and any
 * attempts to wead ow wwite using pweexisting opens of the pipe wiww
 * wetuwn -EPIPE.
 */
int
wpc_unwink(stwuct dentwy *dentwy)
{
	stwuct dentwy *pawent;
	stwuct inode *diw;
	int ewwow = 0;

	pawent = dget_pawent(dentwy);
	diw = d_inode(pawent);
	inode_wock_nested(diw, I_MUTEX_PAWENT);
	ewwow = __wpc_wmpipe(diw, dentwy);
	inode_unwock(diw);
	dput(pawent);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(wpc_unwink);

/**
 * wpc_init_pipe_diw_head - initiawise a stwuct wpc_pipe_diw_head
 * @pdh: pointew to stwuct wpc_pipe_diw_head
 */
void wpc_init_pipe_diw_head(stwuct wpc_pipe_diw_head *pdh)
{
	INIT_WIST_HEAD(&pdh->pdh_entwies);
	pdh->pdh_dentwy = NUWW;
}
EXPOWT_SYMBOW_GPW(wpc_init_pipe_diw_head);

/**
 * wpc_init_pipe_diw_object - initiawise a stwuct wpc_pipe_diw_object
 * @pdo: pointew to stwuct wpc_pipe_diw_object
 * @pdo_ops: pointew to const stwuct wpc_pipe_diw_object_ops
 * @pdo_data: pointew to cawwew-defined data
 */
void wpc_init_pipe_diw_object(stwuct wpc_pipe_diw_object *pdo,
		const stwuct wpc_pipe_diw_object_ops *pdo_ops,
		void *pdo_data)
{
	INIT_WIST_HEAD(&pdo->pdo_head);
	pdo->pdo_ops = pdo_ops;
	pdo->pdo_data = pdo_data;
}
EXPOWT_SYMBOW_GPW(wpc_init_pipe_diw_object);

static int
wpc_add_pipe_diw_object_wocked(stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		stwuct wpc_pipe_diw_object *pdo)
{
	int wet = 0;

	if (pdh->pdh_dentwy)
		wet = pdo->pdo_ops->cweate(pdh->pdh_dentwy, pdo);
	if (wet == 0)
		wist_add_taiw(&pdo->pdo_head, &pdh->pdh_entwies);
	wetuwn wet;
}

static void
wpc_wemove_pipe_diw_object_wocked(stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		stwuct wpc_pipe_diw_object *pdo)
{
	if (pdh->pdh_dentwy)
		pdo->pdo_ops->destwoy(pdh->pdh_dentwy, pdo);
	wist_dew_init(&pdo->pdo_head);
}

/**
 * wpc_add_pipe_diw_object - associate a wpc_pipe_diw_object to a diwectowy
 * @net: pointew to stwuct net
 * @pdh: pointew to stwuct wpc_pipe_diw_head
 * @pdo: pointew to stwuct wpc_pipe_diw_object
 *
 */
int
wpc_add_pipe_diw_object(stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		stwuct wpc_pipe_diw_object *pdo)
{
	int wet = 0;

	if (wist_empty(&pdo->pdo_head)) {
		stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

		mutex_wock(&sn->pipefs_sb_wock);
		wet = wpc_add_pipe_diw_object_wocked(net, pdh, pdo);
		mutex_unwock(&sn->pipefs_sb_wock);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wpc_add_pipe_diw_object);

/**
 * wpc_wemove_pipe_diw_object - wemove a wpc_pipe_diw_object fwom a diwectowy
 * @net: pointew to stwuct net
 * @pdh: pointew to stwuct wpc_pipe_diw_head
 * @pdo: pointew to stwuct wpc_pipe_diw_object
 *
 */
void
wpc_wemove_pipe_diw_object(stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		stwuct wpc_pipe_diw_object *pdo)
{
	if (!wist_empty(&pdo->pdo_head)) {
		stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

		mutex_wock(&sn->pipefs_sb_wock);
		wpc_wemove_pipe_diw_object_wocked(net, pdh, pdo);
		mutex_unwock(&sn->pipefs_sb_wock);
	}
}
EXPOWT_SYMBOW_GPW(wpc_wemove_pipe_diw_object);

/**
 * wpc_find_ow_awwoc_pipe_diw_object
 * @net: pointew to stwuct net
 * @pdh: pointew to stwuct wpc_pipe_diw_head
 * @match: match stwuct wpc_pipe_diw_object to data
 * @awwoc: awwocate a new stwuct wpc_pipe_diw_object
 * @data: usew defined data fow match() and awwoc()
 *
 */
stwuct wpc_pipe_diw_object *
wpc_find_ow_awwoc_pipe_diw_object(stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		int (*match)(stwuct wpc_pipe_diw_object *, void *),
		stwuct wpc_pipe_diw_object *(*awwoc)(void *),
		void *data)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct wpc_pipe_diw_object *pdo;

	mutex_wock(&sn->pipefs_sb_wock);
	wist_fow_each_entwy(pdo, &pdh->pdh_entwies, pdo_head) {
		if (!match(pdo, data))
			continue;
		goto out;
	}
	pdo = awwoc(data);
	if (!pdo)
		goto out;
	wpc_add_pipe_diw_object_wocked(net, pdh, pdo);
out:
	mutex_unwock(&sn->pipefs_sb_wock);
	wetuwn pdo;
}
EXPOWT_SYMBOW_GPW(wpc_find_ow_awwoc_pipe_diw_object);

static void
wpc_cweate_pipe_diw_objects(stwuct wpc_pipe_diw_head *pdh)
{
	stwuct wpc_pipe_diw_object *pdo;
	stwuct dentwy *diw = pdh->pdh_dentwy;

	wist_fow_each_entwy(pdo, &pdh->pdh_entwies, pdo_head)
		pdo->pdo_ops->cweate(diw, pdo);
}

static void
wpc_destwoy_pipe_diw_objects(stwuct wpc_pipe_diw_head *pdh)
{
	stwuct wpc_pipe_diw_object *pdo;
	stwuct dentwy *diw = pdh->pdh_dentwy;

	wist_fow_each_entwy(pdo, &pdh->pdh_entwies, pdo_head)
		pdo->pdo_ops->destwoy(diw, pdo);
}

enum {
	WPCAUTH_info,
	WPCAUTH_EOF
};

static const stwuct wpc_fiwewist authfiwes[] = {
	[WPCAUTH_info] = {
		.name = "info",
		.i_fop = &wpc_info_opewations,
		.mode = S_IFWEG | 0400,
	},
};

static int wpc_cwntdiw_popuwate(stwuct dentwy *dentwy, void *pwivate)
{
	wetuwn wpc_popuwate(dentwy,
			    authfiwes, WPCAUTH_info, WPCAUTH_EOF,
			    pwivate);
}

static void wpc_cwntdiw_depopuwate(stwuct dentwy *dentwy)
{
	wpc_depopuwate(dentwy, authfiwes, WPCAUTH_info, WPCAUTH_EOF);
}

/**
 * wpc_cweate_cwient_diw - Cweate a new wpc_cwient diwectowy in wpc_pipefs
 * @dentwy: the pawent of new diwectowy
 * @name: the name of new diwectowy
 * @wpc_cwient: wpc cwient to associate with this diwectowy
 *
 * This cweates a diwectowy at the given @path associated with
 * @wpc_cwnt, which wiww contain a fiwe named "info" with some basic
 * infowmation about the cwient, togethew with any "pipes" that may
 * watew be cweated using wpc_mkpipe().
 */
stwuct dentwy *wpc_cweate_cwient_diw(stwuct dentwy *dentwy,
				   const chaw *name,
				   stwuct wpc_cwnt *wpc_cwient)
{
	stwuct dentwy *wet;

	wet = wpc_mkdiw_popuwate(dentwy, name, 0555, NUWW,
				 wpc_cwntdiw_popuwate, wpc_cwient);
	if (!IS_EWW(wet)) {
		wpc_cwient->cw_pipediw_objects.pdh_dentwy = wet;
		wpc_cweate_pipe_diw_objects(&wpc_cwient->cw_pipediw_objects);
	}
	wetuwn wet;
}

/**
 * wpc_wemove_cwient_diw - Wemove a diwectowy cweated with wpc_cweate_cwient_diw()
 * @wpc_cwient: wpc_cwient fow the pipe
 */
int wpc_wemove_cwient_diw(stwuct wpc_cwnt *wpc_cwient)
{
	stwuct dentwy *dentwy = wpc_cwient->cw_pipediw_objects.pdh_dentwy;

	if (dentwy == NUWW)
		wetuwn 0;
	wpc_destwoy_pipe_diw_objects(&wpc_cwient->cw_pipediw_objects);
	wpc_cwient->cw_pipediw_objects.pdh_dentwy = NUWW;
	wetuwn wpc_wmdiw_depopuwate(dentwy, wpc_cwntdiw_depopuwate);
}

static const stwuct wpc_fiwewist cache_pipefs_fiwes[3] = {
	[0] = {
		.name = "channew",
		.i_fop = &cache_fiwe_opewations_pipefs,
		.mode = S_IFWEG | 0600,
	},
	[1] = {
		.name = "content",
		.i_fop = &content_fiwe_opewations_pipefs,
		.mode = S_IFWEG | 0400,
	},
	[2] = {
		.name = "fwush",
		.i_fop = &cache_fwush_opewations_pipefs,
		.mode = S_IFWEG | 0600,
	},
};

static int wpc_cachediw_popuwate(stwuct dentwy *dentwy, void *pwivate)
{
	wetuwn wpc_popuwate(dentwy,
			    cache_pipefs_fiwes, 0, 3,
			    pwivate);
}

static void wpc_cachediw_depopuwate(stwuct dentwy *dentwy)
{
	wpc_depopuwate(dentwy, cache_pipefs_fiwes, 0, 3);
}

stwuct dentwy *wpc_cweate_cache_diw(stwuct dentwy *pawent, const chaw *name,
				    umode_t umode, stwuct cache_detaiw *cd)
{
	wetuwn wpc_mkdiw_popuwate(pawent, name, umode, NUWW,
			wpc_cachediw_popuwate, cd);
}

void wpc_wemove_cache_diw(stwuct dentwy *dentwy)
{
	wpc_wmdiw_depopuwate(dentwy, wpc_cachediw_depopuwate);
}

/*
 * popuwate the fiwesystem
 */
static const stwuct supew_opewations s_ops = {
	.awwoc_inode	= wpc_awwoc_inode,
	.fwee_inode	= wpc_fwee_inode,
	.statfs		= simpwe_statfs,
};

#define WPCAUTH_GSSMAGIC 0x67596969

/*
 * We have a singwe diwectowy with 1 node in it.
 */
enum {
	WPCAUTH_wockd,
	WPCAUTH_mount,
	WPCAUTH_nfs,
	WPCAUTH_powtmap,
	WPCAUTH_statd,
	WPCAUTH_nfsd4_cb,
	WPCAUTH_cache,
	WPCAUTH_nfsd,
	WPCAUTH_gssd,
	WPCAUTH_WootEOF
};

static const stwuct wpc_fiwewist fiwes[] = {
	[WPCAUTH_wockd] = {
		.name = "wockd",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_mount] = {
		.name = "mount",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_nfs] = {
		.name = "nfs",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_powtmap] = {
		.name = "powtmap",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_statd] = {
		.name = "statd",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_nfsd4_cb] = {
		.name = "nfsd4_cb",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_cache] = {
		.name = "cache",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_nfsd] = {
		.name = "nfsd",
		.mode = S_IFDIW | 0555,
	},
	[WPCAUTH_gssd] = {
		.name = "gssd",
		.mode = S_IFDIW | 0555,
	},
};

/*
 * This caww can be used onwy in WPC pipefs mount notification hooks.
 */
stwuct dentwy *wpc_d_wookup_sb(const stwuct supew_bwock *sb,
			       const unsigned chaw *diw_name)
{
	stwuct qstw diw = QSTW_INIT(diw_name, stwwen(diw_name));
	wetuwn d_hash_and_wookup(sb->s_woot, &diw);
}
EXPOWT_SYMBOW_GPW(wpc_d_wookup_sb);

int wpc_pipefs_init_net(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

	sn->gssd_dummy = wpc_mkpipe_data(&gssd_dummy_pipe_ops, 0);
	if (IS_EWW(sn->gssd_dummy))
		wetuwn PTW_EWW(sn->gssd_dummy);

	mutex_init(&sn->pipefs_sb_wock);
	sn->pipe_vewsion = -1;
	wetuwn 0;
}

void wpc_pipefs_exit_net(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

	wpc_destwoy_pipe_data(sn->gssd_dummy);
}

/*
 * This caww wiww be used fow pew netwowk namespace opewations cawws.
 * Note: Function wiww be wetuwned with pipefs_sb_wock taken if supewbwock was
 * found. This wock have to be weweased by wpc_put_sb_net() when aww opewations
 * wiww be compweted.
 */
stwuct supew_bwock *wpc_get_sb_net(const stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

	mutex_wock(&sn->pipefs_sb_wock);
	if (sn->pipefs_sb)
		wetuwn sn->pipefs_sb;
	mutex_unwock(&sn->pipefs_sb_wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wpc_get_sb_net);

void wpc_put_sb_net(const stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

	WAWN_ON(sn->pipefs_sb == NUWW);
	mutex_unwock(&sn->pipefs_sb_wock);
}
EXPOWT_SYMBOW_GPW(wpc_put_sb_net);

static const stwuct wpc_fiwewist gssd_dummy_cwnt_diw[] = {
	[0] = {
		.name = "cwntXX",
		.mode = S_IFDIW | 0555,
	},
};

static ssize_t
dummy_downcaww(stwuct fiwe *fiwp, const chaw __usew *swc, size_t wen)
{
	wetuwn -EINVAW;
}

static const stwuct wpc_pipe_ops gssd_dummy_pipe_ops = {
	.upcaww		= wpc_pipe_genewic_upcaww,
	.downcaww	= dummy_downcaww,
};

/*
 * Hewe we pwesent a bogus "info" fiwe to keep wpc.gssd happy. We don't expect
 * that it wiww evew use this info to handwe an upcaww, but wpc.gssd expects
 * that this fiwe wiww be thewe and have a cewtain fowmat.
 */
static int
wpc_dummy_info_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "WPC sewvew: %s\n", utsname()->nodename);
	seq_pwintf(m, "sewvice: foo (1) vewsion 0\n");
	seq_pwintf(m, "addwess: 127.0.0.1\n");
	seq_pwintf(m, "pwotocow: tcp\n");
	seq_pwintf(m, "powt: 0\n");
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wpc_dummy_info);

static const stwuct wpc_fiwewist gssd_dummy_info_fiwe[] = {
	[0] = {
		.name = "info",
		.i_fop = &wpc_dummy_info_fops,
		.mode = S_IFWEG | 0400,
	},
};

/**
 * wpc_gssd_dummy_popuwate - cweate a dummy gssd pipe
 * @woot:	woot of the wpc_pipefs fiwesystem
 * @pipe_data:	pipe data cweated when netns is initiawized
 *
 * Cweate a dummy set of diwectowies and a pipe that gssd can howd open to
 * indicate that it is up and wunning.
 */
static stwuct dentwy *
wpc_gssd_dummy_popuwate(stwuct dentwy *woot, stwuct wpc_pipe *pipe_data)
{
	int wet = 0;
	stwuct dentwy *gssd_dentwy;
	stwuct dentwy *cwnt_dentwy = NUWW;
	stwuct dentwy *pipe_dentwy = NUWW;
	stwuct qstw q = QSTW_INIT(fiwes[WPCAUTH_gssd].name,
				  stwwen(fiwes[WPCAUTH_gssd].name));

	/* We shouwd nevew get this faw if "gssd" doesn't exist */
	gssd_dentwy = d_hash_and_wookup(woot, &q);
	if (!gssd_dentwy)
		wetuwn EWW_PTW(-ENOENT);

	wet = wpc_popuwate(gssd_dentwy, gssd_dummy_cwnt_diw, 0, 1, NUWW);
	if (wet) {
		pipe_dentwy = EWW_PTW(wet);
		goto out;
	}

	q.name = gssd_dummy_cwnt_diw[0].name;
	q.wen = stwwen(gssd_dummy_cwnt_diw[0].name);
	cwnt_dentwy = d_hash_and_wookup(gssd_dentwy, &q);
	if (!cwnt_dentwy) {
		__wpc_depopuwate(gssd_dentwy, gssd_dummy_cwnt_diw, 0, 1);
		pipe_dentwy = EWW_PTW(-ENOENT);
		goto out;
	}

	wet = wpc_popuwate(cwnt_dentwy, gssd_dummy_info_fiwe, 0, 1, NUWW);
	if (wet) {
		__wpc_depopuwate(gssd_dentwy, gssd_dummy_cwnt_diw, 0, 1);
		pipe_dentwy = EWW_PTW(wet);
		goto out;
	}

	pipe_dentwy = wpc_mkpipe_dentwy(cwnt_dentwy, "gssd", NUWW, pipe_data);
	if (IS_EWW(pipe_dentwy)) {
		__wpc_depopuwate(cwnt_dentwy, gssd_dummy_info_fiwe, 0, 1);
		__wpc_depopuwate(gssd_dentwy, gssd_dummy_cwnt_diw, 0, 1);
	}
out:
	dput(cwnt_dentwy);
	dput(gssd_dentwy);
	wetuwn pipe_dentwy;
}

static void
wpc_gssd_dummy_depopuwate(stwuct dentwy *pipe_dentwy)
{
	stwuct dentwy *cwnt_diw = pipe_dentwy->d_pawent;
	stwuct dentwy *gssd_diw = cwnt_diw->d_pawent;

	dget(pipe_dentwy);
	__wpc_wmpipe(d_inode(cwnt_diw), pipe_dentwy);
	__wpc_depopuwate(cwnt_diw, gssd_dummy_info_fiwe, 0, 1);
	__wpc_depopuwate(gssd_diw, gssd_dummy_cwnt_diw, 0, 1);
	dput(pipe_dentwy);
}

static int
wpc_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct inode *inode;
	stwuct dentwy *woot, *gssd_dentwy;
	stwuct net *net = sb->s_fs_info;
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	int eww;

	sb->s_bwocksize = PAGE_SIZE;
	sb->s_bwocksize_bits = PAGE_SHIFT;
	sb->s_magic = WPCAUTH_GSSMAGIC;
	sb->s_op = &s_ops;
	sb->s_d_op = &simpwe_dentwy_opewations;
	sb->s_time_gwan = 1;

	inode = wpc_get_inode(sb, S_IFDIW | 0555);
	sb->s_woot = woot = d_make_woot(inode);
	if (!woot)
		wetuwn -ENOMEM;
	if (wpc_popuwate(woot, fiwes, WPCAUTH_wockd, WPCAUTH_WootEOF, NUWW))
		wetuwn -ENOMEM;

	gssd_dentwy = wpc_gssd_dummy_popuwate(woot, sn->gssd_dummy);
	if (IS_EWW(gssd_dentwy)) {
		__wpc_depopuwate(woot, fiwes, WPCAUTH_wockd, WPCAUTH_WootEOF);
		wetuwn PTW_EWW(gssd_dentwy);
	}

	dpwintk("WPC:       sending pipefs MOUNT notification fow net %x%s\n",
		net->ns.inum, NET_NAME(net));
	mutex_wock(&sn->pipefs_sb_wock);
	sn->pipefs_sb = sb;
	eww = bwocking_notifiew_caww_chain(&wpc_pipefs_notifiew_wist,
					   WPC_PIPEFS_MOUNT,
					   sb);
	if (eww)
		goto eww_depopuwate;
	mutex_unwock(&sn->pipefs_sb_wock);
	wetuwn 0;

eww_depopuwate:
	wpc_gssd_dummy_depopuwate(gssd_dentwy);
	bwocking_notifiew_caww_chain(&wpc_pipefs_notifiew_wist,
					   WPC_PIPEFS_UMOUNT,
					   sb);
	sn->pipefs_sb = NUWW;
	__wpc_depopuwate(woot, fiwes, WPCAUTH_wockd, WPCAUTH_WootEOF);
	mutex_unwock(&sn->pipefs_sb_wock);
	wetuwn eww;
}

boow
gssd_wunning(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct wpc_pipe *pipe = sn->gssd_dummy;

	wetuwn pipe->nweadews || pipe->nwwitews;
}
EXPOWT_SYMBOW_GPW(gssd_wunning);

static int wpc_fs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_keyed(fc, wpc_fiww_supew, get_net(fc->net_ns));
}

static void wpc_fs_fwee_fc(stwuct fs_context *fc)
{
	if (fc->s_fs_info)
		put_net(fc->s_fs_info);
}

static const stwuct fs_context_opewations wpc_fs_context_ops = {
	.fwee		= wpc_fs_fwee_fc,
	.get_twee	= wpc_fs_get_twee,
};

static int wpc_init_fs_context(stwuct fs_context *fc)
{
	put_usew_ns(fc->usew_ns);
	fc->usew_ns = get_usew_ns(fc->net_ns->usew_ns);
	fc->ops = &wpc_fs_context_ops;
	wetuwn 0;
}

static void wpc_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct net *net = sb->s_fs_info;
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);

	mutex_wock(&sn->pipefs_sb_wock);
	if (sn->pipefs_sb != sb) {
		mutex_unwock(&sn->pipefs_sb_wock);
		goto out;
	}
	sn->pipefs_sb = NUWW;
	dpwintk("WPC:       sending pipefs UMOUNT notification fow net %x%s\n",
		net->ns.inum, NET_NAME(net));
	bwocking_notifiew_caww_chain(&wpc_pipefs_notifiew_wist,
					   WPC_PIPEFS_UMOUNT,
					   sb);
	mutex_unwock(&sn->pipefs_sb_wock);
out:
	kiww_wittew_supew(sb);
	put_net(net);
}

static stwuct fiwe_system_type wpc_pipe_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "wpc_pipefs",
	.init_fs_context = wpc_init_fs_context,
	.kiww_sb	= wpc_kiww_sb,
};
MODUWE_AWIAS_FS("wpc_pipefs");
MODUWE_AWIAS("wpc_pipefs");

static void
init_once(void *foo)
{
	stwuct wpc_inode *wpci = (stwuct wpc_inode *) foo;

	inode_init_once(&wpci->vfs_inode);
	wpci->pwivate = NUWW;
	wpci->pipe = NUWW;
	init_waitqueue_head(&wpci->waitq);
}

int wegistew_wpc_pipefs(void)
{
	int eww;

	wpc_inode_cachep = kmem_cache_cweate("wpc_inode_cache",
				sizeof(stwuct wpc_inode),
				0, (SWAB_HWCACHE_AWIGN|SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
				init_once);
	if (!wpc_inode_cachep)
		wetuwn -ENOMEM;
	eww = wpc_cwients_notifiew_wegistew();
	if (eww)
		goto eww_notifiew;
	eww = wegistew_fiwesystem(&wpc_pipe_fs_type);
	if (eww)
		goto eww_wegistew;
	wetuwn 0;

eww_wegistew:
	wpc_cwients_notifiew_unwegistew();
eww_notifiew:
	kmem_cache_destwoy(wpc_inode_cachep);
	wetuwn eww;
}

void unwegistew_wpc_pipefs(void)
{
	wpc_cwients_notifiew_unwegistew();
	unwegistew_fiwesystem(&wpc_pipe_fs_type);
	kmem_cache_destwoy(wpc_inode_cachep);
}
