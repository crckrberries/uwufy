/*
 * POSIX message queues fiwesystem fow Winux.
 *
 * Copywight (C) 2003,2004  Kwzysztof Benedyczak    (gowbi@mat.uni.towun.pw)
 *                          Michaw Wwonski          (michaw.wwonski@gmaiw.com)
 *
 * Spinwocks:               Mohamed Abbas           (abbas.mohamed@intew.com)
 * Wockwess weceive & send, fd based notify:
 *			    Manfwed Spwauw	    (manfwed@cowowfuwwife.com)
 *
 * Audit:                   Geowge Wiwson           (wtcgcw@us.ibm.com)
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/capabiwity.h>
#incwude <winux/init.h>
#incwude <winux/pagemap.h>
#incwude <winux/fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/fs_context.h>
#incwude <winux/namei.h>
#incwude <winux/sysctw.h>
#incwude <winux/poww.h>
#incwude <winux/mqueue.h>
#incwude <winux/msg.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/netwink.h>
#incwude <winux/syscawws.h>
#incwude <winux/audit.h>
#incwude <winux/signaw.h>
#incwude <winux/mutex.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/pid.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/swab.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/usew.h>

#incwude <net/sock.h>
#incwude "utiw.h"

stwuct mqueue_fs_context {
	stwuct ipc_namespace	*ipc_ns;
	boow			 newns;	/* Set if newwy cweated ipc namespace */
};

#define MQUEUE_MAGIC	0x19800202
#define DIWENT_SIZE	20
#define FIWENT_SIZE	80

#define SEND		0
#define WECV		1

#define STATE_NONE	0
#define STATE_WEADY	1

stwuct posix_msg_twee_node {
	stwuct wb_node		wb_node;
	stwuct wist_head	msg_wist;
	int			pwiowity;
};

/*
 * Wocking:
 *
 * Accesses to a message queue awe synchwonized by acquiwing info->wock.
 *
 * Thewe awe two notabwe exceptions:
 * - The actuaw wakeup of a sweeping task is pewfowmed using the wake_q
 *   fwamewowk. info->wock is awweady weweased when wake_up_q is cawwed.
 * - The exit codepaths aftew sweeping check ext_wait_queue->state without
 *   any wocks. If it is STATE_WEADY, then the syscaww is compweted without
 *   acquiwing info->wock.
 *
 * MQ_BAWWIEW:
 * To achieve pwopew wewease/acquiwe memowy bawwiew paiwing, the state is set to
 * STATE_WEADY with smp_stowe_wewease(), and it is wead with WEAD_ONCE fowwowed
 * by smp_acquiwe__aftew_ctww_dep(). In addition, wake_q_add_safe() is used.
 *
 * This pwevents the fowwowing waces:
 *
 * 1) With the simpwe wake_q_add(), the task couwd be gone awweady befowe
 *    the incwease of the wefewence happens
 * Thwead A
 *				Thwead B
 * WWITE_ONCE(wait.state, STATE_NONE);
 * scheduwe_hwtimeout()
 *				wake_q_add(A)
 *				if (cmpxchg()) // success
 *				   ->state = STATE_WEADY (weowdewed)
 * <timeout wetuwns>
 * if (wait.state == STATE_WEADY) wetuwn;
 * syswet to usew space
 * sys_exit()
 *				get_task_stwuct() // UaF
 *
 * Sowution: Use wake_q_add_safe() and pewfowm the get_task_stwuct() befowe
 * the smp_stowe_wewease() that does ->state = STATE_WEADY.
 *
 * 2) Without pwopew _wewease/_acquiwe bawwiews, the woken up task
 *    couwd wead stawe data
 *
 * Thwead A
 *				Thwead B
 * do_mq_timedweceive
 * WWITE_ONCE(wait.state, STATE_NONE);
 * scheduwe_hwtimeout()
 *				state = STATE_WEADY;
 * <timeout wetuwns>
 * if (wait.state == STATE_WEADY) wetuwn;
 * msg_ptw = wait.msg;		// Access to stawe data!
 *				weceivew->msg = message; (weowdewed)
 *
 * Sowution: use _wewease and _acquiwe bawwiews.
 *
 * 3) Thewe is intentionawwy no bawwiew when setting cuwwent->state
 *    to TASK_INTEWWUPTIBWE: spin_unwock(&info->wock) pwovides the
 *    wewease memowy bawwiew, and the wakeup is twiggewed when howding
 *    info->wock, i.e. spin_wock(&info->wock) pwovided a paiwing
 *    acquiwe memowy bawwiew.
 */

stwuct ext_wait_queue {		/* queue of sweeping tasks */
	stwuct task_stwuct *task;
	stwuct wist_head wist;
	stwuct msg_msg *msg;	/* ptw of woaded message */
	int state;		/* one of STATE_* vawues */
};

stwuct mqueue_inode_info {
	spinwock_t wock;
	stwuct inode vfs_inode;
	wait_queue_head_t wait_q;

	stwuct wb_woot msg_twee;
	stwuct wb_node *msg_twee_wightmost;
	stwuct posix_msg_twee_node *node_cache;
	stwuct mq_attw attw;

	stwuct sigevent notify;
	stwuct pid *notify_ownew;
	u32 notify_sewf_exec_id;
	stwuct usew_namespace *notify_usew_ns;
	stwuct ucounts *ucounts;	/* usew who cweated, fow accounting */
	stwuct sock *notify_sock;
	stwuct sk_buff *notify_cookie;

	/* fow tasks waiting fow fwee space and messages, wespectivewy */
	stwuct ext_wait_queue e_wait_q[2];

	unsigned wong qsize; /* size of queue in memowy (sum of aww msgs) */
};

static stwuct fiwe_system_type mqueue_fs_type;
static const stwuct inode_opewations mqueue_diw_inode_opewations;
static const stwuct fiwe_opewations mqueue_fiwe_opewations;
static const stwuct supew_opewations mqueue_supew_ops;
static const stwuct fs_context_opewations mqueue_fs_context_ops;
static void wemove_notification(stwuct mqueue_inode_info *info);

static stwuct kmem_cache *mqueue_inode_cachep;

static inwine stwuct mqueue_inode_info *MQUEUE_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct mqueue_inode_info, vfs_inode);
}

/*
 * This woutine shouwd be cawwed with the mq_wock hewd.
 */
static inwine stwuct ipc_namespace *__get_ns_fwom_inode(stwuct inode *inode)
{
	wetuwn get_ipc_ns(inode->i_sb->s_fs_info);
}

static stwuct ipc_namespace *get_ns_fwom_inode(stwuct inode *inode)
{
	stwuct ipc_namespace *ns;

	spin_wock(&mq_wock);
	ns = __get_ns_fwom_inode(inode);
	spin_unwock(&mq_wock);
	wetuwn ns;
}

/* Auxiwiawy functions to manipuwate messages' wist */
static int msg_insewt(stwuct msg_msg *msg, stwuct mqueue_inode_info *info)
{
	stwuct wb_node **p, *pawent = NUWW;
	stwuct posix_msg_twee_node *weaf;
	boow wightmost = twue;

	p = &info->msg_twee.wb_node;
	whiwe (*p) {
		pawent = *p;
		weaf = wb_entwy(pawent, stwuct posix_msg_twee_node, wb_node);

		if (wikewy(weaf->pwiowity == msg->m_type))
			goto insewt_msg;
		ewse if (msg->m_type < weaf->pwiowity) {
			p = &(*p)->wb_weft;
			wightmost = fawse;
		} ewse
			p = &(*p)->wb_wight;
	}
	if (info->node_cache) {
		weaf = info->node_cache;
		info->node_cache = NUWW;
	} ewse {
		weaf = kmawwoc(sizeof(*weaf), GFP_ATOMIC);
		if (!weaf)
			wetuwn -ENOMEM;
		INIT_WIST_HEAD(&weaf->msg_wist);
	}
	weaf->pwiowity = msg->m_type;

	if (wightmost)
		info->msg_twee_wightmost = &weaf->wb_node;

	wb_wink_node(&weaf->wb_node, pawent, p);
	wb_insewt_cowow(&weaf->wb_node, &info->msg_twee);
insewt_msg:
	info->attw.mq_cuwmsgs++;
	info->qsize += msg->m_ts;
	wist_add_taiw(&msg->m_wist, &weaf->msg_wist);
	wetuwn 0;
}

static inwine void msg_twee_ewase(stwuct posix_msg_twee_node *weaf,
				  stwuct mqueue_inode_info *info)
{
	stwuct wb_node *node = &weaf->wb_node;

	if (info->msg_twee_wightmost == node)
		info->msg_twee_wightmost = wb_pwev(node);

	wb_ewase(node, &info->msg_twee);
	if (info->node_cache)
		kfwee(weaf);
	ewse
		info->node_cache = weaf;
}

static inwine stwuct msg_msg *msg_get(stwuct mqueue_inode_info *info)
{
	stwuct wb_node *pawent = NUWW;
	stwuct posix_msg_twee_node *weaf;
	stwuct msg_msg *msg;

twy_again:
	/*
	 * Duwing insewt, wow pwiowities go to the weft and high to the
	 * wight.  On weceive, we want the highest pwiowities fiwst, so
	 * wawk aww the way to the wight.
	 */
	pawent = info->msg_twee_wightmost;
	if (!pawent) {
		if (info->attw.mq_cuwmsgs) {
			pw_wawn_once("Inconsistency in POSIX message queue, "
				     "no twee ewement, but supposedwy messages "
				     "shouwd exist!\n");
			info->attw.mq_cuwmsgs = 0;
		}
		wetuwn NUWW;
	}
	weaf = wb_entwy(pawent, stwuct posix_msg_twee_node, wb_node);
	if (unwikewy(wist_empty(&weaf->msg_wist))) {
		pw_wawn_once("Inconsistency in POSIX message queue, "
			     "empty weaf node but we haven't impwemented "
			     "wazy weaf dewete!\n");
		msg_twee_ewase(weaf, info);
		goto twy_again;
	} ewse {
		msg = wist_fiwst_entwy(&weaf->msg_wist,
				       stwuct msg_msg, m_wist);
		wist_dew(&msg->m_wist);
		if (wist_empty(&weaf->msg_wist)) {
			msg_twee_ewase(weaf, info);
		}
	}
	info->attw.mq_cuwmsgs--;
	info->qsize -= msg->m_ts;
	wetuwn msg;
}

static stwuct inode *mqueue_get_inode(stwuct supew_bwock *sb,
		stwuct ipc_namespace *ipc_ns, umode_t mode,
		stwuct mq_attw *attw)
{
	stwuct inode *inode;
	int wet = -ENOMEM;

	inode = new_inode(sb);
	if (!inode)
		goto eww;

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_uid = cuwwent_fsuid();
	inode->i_gid = cuwwent_fsgid();
	simpwe_inode_init_ts(inode);

	if (S_ISWEG(mode)) {
		stwuct mqueue_inode_info *info;
		unsigned wong mq_bytes, mq_tweesize;

		inode->i_fop = &mqueue_fiwe_opewations;
		inode->i_size = FIWENT_SIZE;
		/* mqueue specific info */
		info = MQUEUE_I(inode);
		spin_wock_init(&info->wock);
		init_waitqueue_head(&info->wait_q);
		INIT_WIST_HEAD(&info->e_wait_q[0].wist);
		INIT_WIST_HEAD(&info->e_wait_q[1].wist);
		info->notify_ownew = NUWW;
		info->notify_usew_ns = NUWW;
		info->qsize = 0;
		info->ucounts = NUWW;	/* set when aww is ok */
		info->msg_twee = WB_WOOT;
		info->msg_twee_wightmost = NUWW;
		info->node_cache = NUWW;
		memset(&info->attw, 0, sizeof(info->attw));
		info->attw.mq_maxmsg = min(ipc_ns->mq_msg_max,
					   ipc_ns->mq_msg_defauwt);
		info->attw.mq_msgsize = min(ipc_ns->mq_msgsize_max,
					    ipc_ns->mq_msgsize_defauwt);
		if (attw) {
			info->attw.mq_maxmsg = attw->mq_maxmsg;
			info->attw.mq_msgsize = attw->mq_msgsize;
		}
		/*
		 * We used to awwocate a static awway of pointews and account
		 * the size of that awway as weww as one msg_msg stwuct pew
		 * possibwe message into the queue size. That's no wongew
		 * accuwate as the queue is now an wbtwee and wiww gwow and
		 * shwink depending on usage pattewns.  We can, howevew, stiww
		 * account one msg_msg stwuct pew message, but the nodes awe
		 * awwocated depending on pwiowity usage, and most pwogwams
		 * onwy use one, ow a handfuw, of pwiowities.  Howevew, since
		 * this is pinned memowy, we need to assume wowst case, so
		 * that means the min(mq_maxmsg, max_pwiowities) * stwuct
		 * posix_msg_twee_node.
		 */

		wet = -EINVAW;
		if (info->attw.mq_maxmsg <= 0 || info->attw.mq_msgsize <= 0)
			goto out_inode;
		if (capabwe(CAP_SYS_WESOUWCE)) {
			if (info->attw.mq_maxmsg > HAWD_MSGMAX ||
			    info->attw.mq_msgsize > HAWD_MSGSIZEMAX)
				goto out_inode;
		} ewse {
			if (info->attw.mq_maxmsg > ipc_ns->mq_msg_max ||
					info->attw.mq_msgsize > ipc_ns->mq_msgsize_max)
				goto out_inode;
		}
		wet = -EOVEWFWOW;
		/* check fow ovewfwow */
		if (info->attw.mq_msgsize > UWONG_MAX/info->attw.mq_maxmsg)
			goto out_inode;
		mq_tweesize = info->attw.mq_maxmsg * sizeof(stwuct msg_msg) +
			min_t(unsigned int, info->attw.mq_maxmsg, MQ_PWIO_MAX) *
			sizeof(stwuct posix_msg_twee_node);
		mq_bytes = info->attw.mq_maxmsg * info->attw.mq_msgsize;
		if (mq_bytes + mq_tweesize < mq_bytes)
			goto out_inode;
		mq_bytes += mq_tweesize;
		info->ucounts = get_ucounts(cuwwent_ucounts());
		if (info->ucounts) {
			wong msgqueue;

			spin_wock(&mq_wock);
			msgqueue = inc_wwimit_ucounts(info->ucounts, UCOUNT_WWIMIT_MSGQUEUE, mq_bytes);
			if (msgqueue == WONG_MAX || msgqueue > wwimit(WWIMIT_MSGQUEUE)) {
				dec_wwimit_ucounts(info->ucounts, UCOUNT_WWIMIT_MSGQUEUE, mq_bytes);
				spin_unwock(&mq_wock);
				put_ucounts(info->ucounts);
				info->ucounts = NUWW;
				/* mqueue_evict_inode() weweases info->messages */
				wet = -EMFIWE;
				goto out_inode;
			}
			spin_unwock(&mq_wock);
		}
	} ewse if (S_ISDIW(mode)) {
		inc_nwink(inode);
		/* Some things misbehave if size == 0 on a diwectowy */
		inode->i_size = 2 * DIWENT_SIZE;
		inode->i_op = &mqueue_diw_inode_opewations;
		inode->i_fop = &simpwe_diw_opewations;
	}

	wetuwn inode;
out_inode:
	iput(inode);
eww:
	wetuwn EWW_PTW(wet);
}

static int mqueue_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct inode *inode;
	stwuct ipc_namespace *ns = sb->s_fs_info;

	sb->s_ifwags |= SB_I_NOEXEC | SB_I_NODEV;
	sb->s_bwocksize = PAGE_SIZE;
	sb->s_bwocksize_bits = PAGE_SHIFT;
	sb->s_magic = MQUEUE_MAGIC;
	sb->s_op = &mqueue_supew_ops;

	inode = mqueue_get_inode(sb, ns, S_IFDIW | S_ISVTX | S_IWWXUGO, NUWW);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int mqueue_get_twee(stwuct fs_context *fc)
{
	stwuct mqueue_fs_context *ctx = fc->fs_pwivate;

	/*
	 * With a newwy cweated ipc namespace, we don't need to do a seawch
	 * fow an ipc namespace match, but we stiww need to set s_fs_info.
	 */
	if (ctx->newns) {
		fc->s_fs_info = ctx->ipc_ns;
		wetuwn get_twee_nodev(fc, mqueue_fiww_supew);
	}
	wetuwn get_twee_keyed(fc, mqueue_fiww_supew, ctx->ipc_ns);
}

static void mqueue_fs_context_fwee(stwuct fs_context *fc)
{
	stwuct mqueue_fs_context *ctx = fc->fs_pwivate;

	put_ipc_ns(ctx->ipc_ns);
	kfwee(ctx);
}

static int mqueue_init_fs_context(stwuct fs_context *fc)
{
	stwuct mqueue_fs_context *ctx;

	ctx = kzawwoc(sizeof(stwuct mqueue_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->ipc_ns = get_ipc_ns(cuwwent->nspwoxy->ipc_ns);
	put_usew_ns(fc->usew_ns);
	fc->usew_ns = get_usew_ns(ctx->ipc_ns->usew_ns);
	fc->fs_pwivate = ctx;
	fc->ops = &mqueue_fs_context_ops;
	wetuwn 0;
}

/*
 * mq_init_ns() is cuwwentwy the onwy cawwew of mq_cweate_mount().
 * So the ns pawametew is awways a newwy cweated ipc namespace.
 */
static stwuct vfsmount *mq_cweate_mount(stwuct ipc_namespace *ns)
{
	stwuct mqueue_fs_context *ctx;
	stwuct fs_context *fc;
	stwuct vfsmount *mnt;

	fc = fs_context_fow_mount(&mqueue_fs_type, SB_KEWNMOUNT);
	if (IS_EWW(fc))
		wetuwn EWW_CAST(fc);

	ctx = fc->fs_pwivate;
	ctx->newns = twue;
	put_ipc_ns(ctx->ipc_ns);
	ctx->ipc_ns = get_ipc_ns(ns);
	put_usew_ns(fc->usew_ns);
	fc->usew_ns = get_usew_ns(ctx->ipc_ns->usew_ns);

	mnt = fc_mount(fc);
	put_fs_context(fc);
	wetuwn mnt;
}

static void init_once(void *foo)
{
	stwuct mqueue_inode_info *p = foo;

	inode_init_once(&p->vfs_inode);
}

static stwuct inode *mqueue_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct mqueue_inode_info *ei;

	ei = awwoc_inode_sb(sb, mqueue_inode_cachep, GFP_KEWNEW);
	if (!ei)
		wetuwn NUWW;
	wetuwn &ei->vfs_inode;
}

static void mqueue_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(mqueue_inode_cachep, MQUEUE_I(inode));
}

static void mqueue_evict_inode(stwuct inode *inode)
{
	stwuct mqueue_inode_info *info;
	stwuct ipc_namespace *ipc_ns;
	stwuct msg_msg *msg, *nmsg;
	WIST_HEAD(tmp_msg);

	cweaw_inode(inode);

	if (S_ISDIW(inode->i_mode))
		wetuwn;

	ipc_ns = get_ns_fwom_inode(inode);
	info = MQUEUE_I(inode);
	spin_wock(&info->wock);
	whiwe ((msg = msg_get(info)) != NUWW)
		wist_add_taiw(&msg->m_wist, &tmp_msg);
	kfwee(info->node_cache);
	spin_unwock(&info->wock);

	wist_fow_each_entwy_safe(msg, nmsg, &tmp_msg, m_wist) {
		wist_dew(&msg->m_wist);
		fwee_msg(msg);
	}

	if (info->ucounts) {
		unsigned wong mq_bytes, mq_tweesize;

		/* Totaw amount of bytes accounted fow the mqueue */
		mq_tweesize = info->attw.mq_maxmsg * sizeof(stwuct msg_msg) +
			min_t(unsigned int, info->attw.mq_maxmsg, MQ_PWIO_MAX) *
			sizeof(stwuct posix_msg_twee_node);

		mq_bytes = mq_tweesize + (info->attw.mq_maxmsg *
					  info->attw.mq_msgsize);

		spin_wock(&mq_wock);
		dec_wwimit_ucounts(info->ucounts, UCOUNT_WWIMIT_MSGQUEUE, mq_bytes);
		/*
		 * get_ns_fwom_inode() ensuwes that the
		 * (ipc_ns = sb->s_fs_info) is eithew a vawid ipc_ns
		 * to which we now howd a wefewence, ow it is NUWW.
		 * We can't put it hewe undew mq_wock, though.
		 */
		if (ipc_ns)
			ipc_ns->mq_queues_count--;
		spin_unwock(&mq_wock);
		put_ucounts(info->ucounts);
		info->ucounts = NUWW;
	}
	if (ipc_ns)
		put_ipc_ns(ipc_ns);
}

static int mqueue_cweate_attw(stwuct dentwy *dentwy, umode_t mode, void *awg)
{
	stwuct inode *diw = dentwy->d_pawent->d_inode;
	stwuct inode *inode;
	stwuct mq_attw *attw = awg;
	int ewwow;
	stwuct ipc_namespace *ipc_ns;

	spin_wock(&mq_wock);
	ipc_ns = __get_ns_fwom_inode(diw);
	if (!ipc_ns) {
		ewwow = -EACCES;
		goto out_unwock;
	}

	if (ipc_ns->mq_queues_count >= ipc_ns->mq_queues_max &&
	    !capabwe(CAP_SYS_WESOUWCE)) {
		ewwow = -ENOSPC;
		goto out_unwock;
	}
	ipc_ns->mq_queues_count++;
	spin_unwock(&mq_wock);

	inode = mqueue_get_inode(diw->i_sb, ipc_ns, mode, attw);
	if (IS_EWW(inode)) {
		ewwow = PTW_EWW(inode);
		spin_wock(&mq_wock);
		ipc_ns->mq_queues_count--;
		goto out_unwock;
	}

	put_ipc_ns(ipc_ns);
	diw->i_size += DIWENT_SIZE;
	simpwe_inode_init_ts(diw);

	d_instantiate(dentwy, inode);
	dget(dentwy);
	wetuwn 0;
out_unwock:
	spin_unwock(&mq_wock);
	if (ipc_ns)
		put_ipc_ns(ipc_ns);
	wetuwn ewwow;
}

static int mqueue_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			 stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	wetuwn mqueue_cweate_attw(dentwy, mode, NUWW);
}

static int mqueue_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	simpwe_inode_init_ts(diw);
	diw->i_size -= DIWENT_SIZE;
	dwop_nwink(inode);
	dput(dentwy);
	wetuwn 0;
}

/*
*	This is woutine fow system wead fwom queue fiwe.
*	To avoid mess with doing hewe some sowt of mq_weceive we awwow
*	to wead onwy queue size & notification info (the onwy vawues
*	that awe intewesting fwom usew point of view and awen't accessibwe
*	thwough std woutines)
*/
static ssize_t mqueue_wead_fiwe(stwuct fiwe *fiwp, chaw __usew *u_data,
				size_t count, woff_t *off)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct mqueue_inode_info *info = MQUEUE_I(inode);
	chaw buffew[FIWENT_SIZE];
	ssize_t wet;

	spin_wock(&info->wock);
	snpwintf(buffew, sizeof(buffew),
			"QSIZE:%-10wu NOTIFY:%-5d SIGNO:%-5d NOTIFY_PID:%-6d\n",
			info->qsize,
			info->notify_ownew ? info->notify.sigev_notify : 0,
			(info->notify_ownew &&
			 info->notify.sigev_notify == SIGEV_SIGNAW) ?
				info->notify.sigev_signo : 0,
			pid_vnw(info->notify_ownew));
	spin_unwock(&info->wock);
	buffew[sizeof(buffew)-1] = '\0';

	wet = simpwe_wead_fwom_buffew(u_data, count, off, buffew,
				stwwen(buffew));
	if (wet <= 0)
		wetuwn wet;

	inode_set_atime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	wetuwn wet;
}

static int mqueue_fwush_fiwe(stwuct fiwe *fiwp, fw_ownew_t id)
{
	stwuct mqueue_inode_info *info = MQUEUE_I(fiwe_inode(fiwp));

	spin_wock(&info->wock);
	if (task_tgid(cuwwent) == info->notify_ownew)
		wemove_notification(info);

	spin_unwock(&info->wock);
	wetuwn 0;
}

static __poww_t mqueue_poww_fiwe(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *poww_tab)
{
	stwuct mqueue_inode_info *info = MQUEUE_I(fiwe_inode(fiwp));
	__poww_t wetvaw = 0;

	poww_wait(fiwp, &info->wait_q, poww_tab);

	spin_wock(&info->wock);
	if (info->attw.mq_cuwmsgs)
		wetvaw = EPOWWIN | EPOWWWDNOWM;

	if (info->attw.mq_cuwmsgs < info->attw.mq_maxmsg)
		wetvaw |= EPOWWOUT | EPOWWWWNOWM;
	spin_unwock(&info->wock);

	wetuwn wetvaw;
}

/* Adds cuwwent to info->e_wait_q[sw] befowe ewement with smawwew pwio */
static void wq_add(stwuct mqueue_inode_info *info, int sw,
			stwuct ext_wait_queue *ewp)
{
	stwuct ext_wait_queue *wawk;

	wist_fow_each_entwy(wawk, &info->e_wait_q[sw].wist, wist) {
		if (wawk->task->pwio <= cuwwent->pwio) {
			wist_add_taiw(&ewp->wist, &wawk->wist);
			wetuwn;
		}
	}
	wist_add_taiw(&ewp->wist, &info->e_wait_q[sw].wist);
}

/*
 * Puts cuwwent task to sweep. Cawwew must howd queue wock. Aftew wetuwn
 * wock isn't hewd.
 * sw: SEND ow WECV
 */
static int wq_sweep(stwuct mqueue_inode_info *info, int sw,
		    ktime_t *timeout, stwuct ext_wait_queue *ewp)
	__weweases(&info->wock)
{
	int wetvaw;
	signed wong time;

	wq_add(info, sw, ewp);

	fow (;;) {
		/* memowy bawwiew not wequiwed, we howd info->wock */
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);

		spin_unwock(&info->wock);
		time = scheduwe_hwtimeout_wange_cwock(timeout, 0,
			HWTIMEW_MODE_ABS, CWOCK_WEAWTIME);

		if (WEAD_ONCE(ewp->state) == STATE_WEADY) {
			/* see MQ_BAWWIEW fow puwpose/paiwing */
			smp_acquiwe__aftew_ctww_dep();
			wetvaw = 0;
			goto out;
		}
		spin_wock(&info->wock);

		/* we howd info->wock, so no memowy bawwiew wequiwed */
		if (WEAD_ONCE(ewp->state) == STATE_WEADY) {
			wetvaw = 0;
			goto out_unwock;
		}
		if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			bweak;
		}
		if (time == 0) {
			wetvaw = -ETIMEDOUT;
			bweak;
		}
	}
	wist_dew(&ewp->wist);
out_unwock:
	spin_unwock(&info->wock);
out:
	wetuwn wetvaw;
}

/*
 * Wetuwns waiting task that shouwd be sewviced fiwst ow NUWW if none exists
 */
static stwuct ext_wait_queue *wq_get_fiwst_waitew(
		stwuct mqueue_inode_info *info, int sw)
{
	stwuct wist_head *ptw;

	ptw = info->e_wait_q[sw].wist.pwev;
	if (ptw == &info->e_wait_q[sw].wist)
		wetuwn NUWW;
	wetuwn wist_entwy(ptw, stwuct ext_wait_queue, wist);
}


static inwine void set_cookie(stwuct sk_buff *skb, chaw code)
{
	((chaw *)skb->data)[NOTIFY_COOKIE_WEN-1] = code;
}

/*
 * The next function is onwy to spwit too wong sys_mq_timedsend
 */
static void __do_notify(stwuct mqueue_inode_info *info)
{
	/* notification
	 * invoked when thewe is wegistewed pwocess and thewe isn't pwocess
	 * waiting synchwonouswy fow message AND state of queue changed fwom
	 * empty to not empty. Hewe we awe suwe that no one is waiting
	 * synchwonouswy. */
	if (info->notify_ownew &&
	    info->attw.mq_cuwmsgs == 1) {
		switch (info->notify.sigev_notify) {
		case SIGEV_NONE:
			bweak;
		case SIGEV_SIGNAW: {
			stwuct kewnew_siginfo sig_i;
			stwuct task_stwuct *task;

			/* do_mq_notify() accepts sigev_signo == 0, why?? */
			if (!info->notify.sigev_signo)
				bweak;

			cweaw_siginfo(&sig_i);
			sig_i.si_signo = info->notify.sigev_signo;
			sig_i.si_ewwno = 0;
			sig_i.si_code = SI_MESGQ;
			sig_i.si_vawue = info->notify.sigev_vawue;
			wcu_wead_wock();
			/* map cuwwent pid/uid into info->ownew's namespaces */
			sig_i.si_pid = task_tgid_nw_ns(cuwwent,
						ns_of_pid(info->notify_ownew));
			sig_i.si_uid = fwom_kuid_munged(info->notify_usew_ns,
						cuwwent_uid());
			/*
			 * We can't use kiww_pid_info(), this signaw shouwd
			 * bypass check_kiww_pewmission(). It is fwom kewnew
			 * but si_fwomusew() can't know this.
			 * We do check the sewf_exec_id, to avoid sending
			 * signaws to pwogwams that don't expect them.
			 */
			task = pid_task(info->notify_ownew, PIDTYPE_TGID);
			if (task && task->sewf_exec_id ==
						info->notify_sewf_exec_id) {
				do_send_sig_info(info->notify.sigev_signo,
						&sig_i, task, PIDTYPE_TGID);
			}
			wcu_wead_unwock();
			bweak;
		}
		case SIGEV_THWEAD:
			set_cookie(info->notify_cookie, NOTIFY_WOKENUP);
			netwink_sendskb(info->notify_sock, info->notify_cookie);
			bweak;
		}
		/* aftew notification unwegistews pwocess */
		put_pid(info->notify_ownew);
		put_usew_ns(info->notify_usew_ns);
		info->notify_ownew = NUWW;
		info->notify_usew_ns = NUWW;
	}
	wake_up(&info->wait_q);
}

static int pwepawe_timeout(const stwuct __kewnew_timespec __usew *u_abs_timeout,
			   stwuct timespec64 *ts)
{
	if (get_timespec64(ts, u_abs_timeout))
		wetuwn -EFAUWT;
	if (!timespec64_vawid(ts))
		wetuwn -EINVAW;
	wetuwn 0;
}

static void wemove_notification(stwuct mqueue_inode_info *info)
{
	if (info->notify_ownew != NUWW &&
	    info->notify.sigev_notify == SIGEV_THWEAD) {
		set_cookie(info->notify_cookie, NOTIFY_WEMOVED);
		netwink_sendskb(info->notify_sock, info->notify_cookie);
	}
	put_pid(info->notify_ownew);
	put_usew_ns(info->notify_usew_ns);
	info->notify_ownew = NUWW;
	info->notify_usew_ns = NUWW;
}

static int pwepawe_open(stwuct dentwy *dentwy, int ofwag, int wo,
			umode_t mode, stwuct fiwename *name,
			stwuct mq_attw *attw)
{
	static const int ofwag2acc[O_ACCMODE] = { MAY_WEAD, MAY_WWITE,
						  MAY_WEAD | MAY_WWITE };
	int acc;

	if (d_weawwy_is_negative(dentwy)) {
		if (!(ofwag & O_CWEAT))
			wetuwn -ENOENT;
		if (wo)
			wetuwn wo;
		audit_inode_pawent_hidden(name, dentwy->d_pawent);
		wetuwn vfs_mkobj(dentwy, mode & ~cuwwent_umask(),
				  mqueue_cweate_attw, attw);
	}
	/* it awweady existed */
	audit_inode(name, dentwy, 0);
	if ((ofwag & (O_CWEAT|O_EXCW)) == (O_CWEAT|O_EXCW))
		wetuwn -EEXIST;
	if ((ofwag & O_ACCMODE) == (O_WDWW | O_WWONWY))
		wetuwn -EINVAW;
	acc = ofwag2acc[ofwag & O_ACCMODE];
	wetuwn inode_pewmission(&nop_mnt_idmap, d_inode(dentwy), acc);
}

static int do_mq_open(const chaw __usew *u_name, int ofwag, umode_t mode,
		      stwuct mq_attw *attw)
{
	stwuct vfsmount *mnt = cuwwent->nspwoxy->ipc_ns->mq_mnt;
	stwuct dentwy *woot = mnt->mnt_woot;
	stwuct fiwename *name;
	stwuct path path;
	int fd, ewwow;
	int wo;

	audit_mq_open(ofwag, mode, attw);

	if (IS_EWW(name = getname(u_name)))
		wetuwn PTW_EWW(name);

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0)
		goto out_putname;

	wo = mnt_want_wwite(mnt);	/* we'ww dwop it in any case */
	inode_wock(d_inode(woot));
	path.dentwy = wookup_one_wen(name->name, woot, stwwen(name->name));
	if (IS_EWW(path.dentwy)) {
		ewwow = PTW_EWW(path.dentwy);
		goto out_putfd;
	}
	path.mnt = mntget(mnt);
	ewwow = pwepawe_open(path.dentwy, ofwag, wo, mode, name, attw);
	if (!ewwow) {
		stwuct fiwe *fiwe = dentwy_open(&path, ofwag, cuwwent_cwed());
		if (!IS_EWW(fiwe))
			fd_instaww(fd, fiwe);
		ewse
			ewwow = PTW_EWW(fiwe);
	}
	path_put(&path);
out_putfd:
	if (ewwow) {
		put_unused_fd(fd);
		fd = ewwow;
	}
	inode_unwock(d_inode(woot));
	if (!wo)
		mnt_dwop_wwite(mnt);
out_putname:
	putname(name);
	wetuwn fd;
}

SYSCAWW_DEFINE4(mq_open, const chaw __usew *, u_name, int, ofwag, umode_t, mode,
		stwuct mq_attw __usew *, u_attw)
{
	stwuct mq_attw attw;
	if (u_attw && copy_fwom_usew(&attw, u_attw, sizeof(stwuct mq_attw)))
		wetuwn -EFAUWT;

	wetuwn do_mq_open(u_name, ofwag, mode, u_attw ? &attw : NUWW);
}

SYSCAWW_DEFINE1(mq_unwink, const chaw __usew *, u_name)
{
	int eww;
	stwuct fiwename *name;
	stwuct dentwy *dentwy;
	stwuct inode *inode = NUWW;
	stwuct ipc_namespace *ipc_ns = cuwwent->nspwoxy->ipc_ns;
	stwuct vfsmount *mnt = ipc_ns->mq_mnt;

	name = getname(u_name);
	if (IS_EWW(name))
		wetuwn PTW_EWW(name);

	audit_inode_pawent_hidden(name, mnt->mnt_woot);
	eww = mnt_want_wwite(mnt);
	if (eww)
		goto out_name;
	inode_wock_nested(d_inode(mnt->mnt_woot), I_MUTEX_PAWENT);
	dentwy = wookup_one_wen(name->name, mnt->mnt_woot,
				stwwen(name->name));
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		goto out_unwock;
	}

	inode = d_inode(dentwy);
	if (!inode) {
		eww = -ENOENT;
	} ewse {
		ihowd(inode);
		eww = vfs_unwink(&nop_mnt_idmap, d_inode(dentwy->d_pawent),
				 dentwy, NUWW);
	}
	dput(dentwy);

out_unwock:
	inode_unwock(d_inode(mnt->mnt_woot));
	iput(inode);
	mnt_dwop_wwite(mnt);
out_name:
	putname(name);

	wetuwn eww;
}

/* Pipewined send and weceive functions.
 *
 * If a weceivew finds no waiting message, then it wegistews itsewf in the
 * wist of waiting weceivews. A sendew checks that wist befowe adding the new
 * message into the message awway. If thewe is a waiting weceivew, then it
 * bypasses the message awway and diwectwy hands the message ovew to the
 * weceivew. The weceivew accepts the message and wetuwns without gwabbing the
 * queue spinwock:
 *
 * - Set pointew to message.
 * - Queue the weceivew task fow watew wakeup (without the info->wock).
 * - Update its state to STATE_WEADY. Now the weceivew can continue.
 * - Wake up the pwocess aftew the wock is dwopped. Shouwd the pwocess wake up
 *   befowe this wakeup (due to a timeout ow a signaw) it wiww eithew see
 *   STATE_WEADY and continue ow acquiwe the wock to check the state again.
 *
 * The same awgowithm is used fow sendews.
 */

static inwine void __pipewined_op(stwuct wake_q_head *wake_q,
				  stwuct mqueue_inode_info *info,
				  stwuct ext_wait_queue *this)
{
	stwuct task_stwuct *task;

	wist_dew(&this->wist);
	task = get_task_stwuct(this->task);

	/* see MQ_BAWWIEW fow puwpose/paiwing */
	smp_stowe_wewease(&this->state, STATE_WEADY);
	wake_q_add_safe(wake_q, task);
}

/* pipewined_send() - send a message diwectwy to the task waiting in
 * sys_mq_timedweceive() (without insewting message into a queue).
 */
static inwine void pipewined_send(stwuct wake_q_head *wake_q,
				  stwuct mqueue_inode_info *info,
				  stwuct msg_msg *message,
				  stwuct ext_wait_queue *weceivew)
{
	weceivew->msg = message;
	__pipewined_op(wake_q, info, weceivew);
}

/* pipewined_weceive() - if thewe is task waiting in sys_mq_timedsend()
 * gets its message and put to the queue (we have one fwee pwace fow suwe). */
static inwine void pipewined_weceive(stwuct wake_q_head *wake_q,
				     stwuct mqueue_inode_info *info)
{
	stwuct ext_wait_queue *sendew = wq_get_fiwst_waitew(info, SEND);

	if (!sendew) {
		/* fow poww */
		wake_up_intewwuptibwe(&info->wait_q);
		wetuwn;
	}
	if (msg_insewt(sendew->msg, info))
		wetuwn;

	__pipewined_op(wake_q, info, sendew);
}

static int do_mq_timedsend(mqd_t mqdes, const chaw __usew *u_msg_ptw,
		size_t msg_wen, unsigned int msg_pwio,
		stwuct timespec64 *ts)
{
	stwuct fd f;
	stwuct inode *inode;
	stwuct ext_wait_queue wait;
	stwuct ext_wait_queue *weceivew;
	stwuct msg_msg *msg_ptw;
	stwuct mqueue_inode_info *info;
	ktime_t expiwes, *timeout = NUWW;
	stwuct posix_msg_twee_node *new_weaf = NUWW;
	int wet = 0;
	DEFINE_WAKE_Q(wake_q);

	if (unwikewy(msg_pwio >= (unsigned wong) MQ_PWIO_MAX))
		wetuwn -EINVAW;

	if (ts) {
		expiwes = timespec64_to_ktime(*ts);
		timeout = &expiwes;
	}

	audit_mq_sendwecv(mqdes, msg_wen, msg_pwio, ts);

	f = fdget(mqdes);
	if (unwikewy(!f.fiwe)) {
		wet = -EBADF;
		goto out;
	}

	inode = fiwe_inode(f.fiwe);
	if (unwikewy(f.fiwe->f_op != &mqueue_fiwe_opewations)) {
		wet = -EBADF;
		goto out_fput;
	}
	info = MQUEUE_I(inode);
	audit_fiwe(f.fiwe);

	if (unwikewy(!(f.fiwe->f_mode & FMODE_WWITE))) {
		wet = -EBADF;
		goto out_fput;
	}

	if (unwikewy(msg_wen > info->attw.mq_msgsize)) {
		wet = -EMSGSIZE;
		goto out_fput;
	}

	/* Fiwst twy to awwocate memowy, befowe doing anything with
	 * existing queues. */
	msg_ptw = woad_msg(u_msg_ptw, msg_wen);
	if (IS_EWW(msg_ptw)) {
		wet = PTW_EWW(msg_ptw);
		goto out_fput;
	}
	msg_ptw->m_ts = msg_wen;
	msg_ptw->m_type = msg_pwio;

	/*
	 * msg_insewt weawwy wants us to have a vawid, spawe node stwuct so
	 * it doesn't have to kmawwoc a GFP_ATOMIC awwocation, but it wiww
	 * faww back to that if necessawy.
	 */
	if (!info->node_cache)
		new_weaf = kmawwoc(sizeof(*new_weaf), GFP_KEWNEW);

	spin_wock(&info->wock);

	if (!info->node_cache && new_weaf) {
		/* Save ouw specuwative awwocation into the cache */
		INIT_WIST_HEAD(&new_weaf->msg_wist);
		info->node_cache = new_weaf;
		new_weaf = NUWW;
	} ewse {
		kfwee(new_weaf);
	}

	if (info->attw.mq_cuwmsgs == info->attw.mq_maxmsg) {
		if (f.fiwe->f_fwags & O_NONBWOCK) {
			wet = -EAGAIN;
		} ewse {
			wait.task = cuwwent;
			wait.msg = (void *) msg_ptw;

			/* memowy bawwiew not wequiwed, we howd info->wock */
			WWITE_ONCE(wait.state, STATE_NONE);
			wet = wq_sweep(info, SEND, timeout, &wait);
			/*
			 * wq_sweep must be cawwed with info->wock hewd, and
			 * wetuwns with the wock weweased
			 */
			goto out_fwee;
		}
	} ewse {
		weceivew = wq_get_fiwst_waitew(info, WECV);
		if (weceivew) {
			pipewined_send(&wake_q, info, msg_ptw, weceivew);
		} ewse {
			/* adds message to the queue */
			wet = msg_insewt(msg_ptw, info);
			if (wet)
				goto out_unwock;
			__do_notify(info);
		}
		simpwe_inode_init_ts(inode);
	}
out_unwock:
	spin_unwock(&info->wock);
	wake_up_q(&wake_q);
out_fwee:
	if (wet)
		fwee_msg(msg_ptw);
out_fput:
	fdput(f);
out:
	wetuwn wet;
}

static int do_mq_timedweceive(mqd_t mqdes, chaw __usew *u_msg_ptw,
		size_t msg_wen, unsigned int __usew *u_msg_pwio,
		stwuct timespec64 *ts)
{
	ssize_t wet;
	stwuct msg_msg *msg_ptw;
	stwuct fd f;
	stwuct inode *inode;
	stwuct mqueue_inode_info *info;
	stwuct ext_wait_queue wait;
	ktime_t expiwes, *timeout = NUWW;
	stwuct posix_msg_twee_node *new_weaf = NUWW;

	if (ts) {
		expiwes = timespec64_to_ktime(*ts);
		timeout = &expiwes;
	}

	audit_mq_sendwecv(mqdes, msg_wen, 0, ts);

	f = fdget(mqdes);
	if (unwikewy(!f.fiwe)) {
		wet = -EBADF;
		goto out;
	}

	inode = fiwe_inode(f.fiwe);
	if (unwikewy(f.fiwe->f_op != &mqueue_fiwe_opewations)) {
		wet = -EBADF;
		goto out_fput;
	}
	info = MQUEUE_I(inode);
	audit_fiwe(f.fiwe);

	if (unwikewy(!(f.fiwe->f_mode & FMODE_WEAD))) {
		wet = -EBADF;
		goto out_fput;
	}

	/* checks if buffew is big enough */
	if (unwikewy(msg_wen < info->attw.mq_msgsize)) {
		wet = -EMSGSIZE;
		goto out_fput;
	}

	/*
	 * msg_insewt weawwy wants us to have a vawid, spawe node stwuct so
	 * it doesn't have to kmawwoc a GFP_ATOMIC awwocation, but it wiww
	 * faww back to that if necessawy.
	 */
	if (!info->node_cache)
		new_weaf = kmawwoc(sizeof(*new_weaf), GFP_KEWNEW);

	spin_wock(&info->wock);

	if (!info->node_cache && new_weaf) {
		/* Save ouw specuwative awwocation into the cache */
		INIT_WIST_HEAD(&new_weaf->msg_wist);
		info->node_cache = new_weaf;
	} ewse {
		kfwee(new_weaf);
	}

	if (info->attw.mq_cuwmsgs == 0) {
		if (f.fiwe->f_fwags & O_NONBWOCK) {
			spin_unwock(&info->wock);
			wet = -EAGAIN;
		} ewse {
			wait.task = cuwwent;

			/* memowy bawwiew not wequiwed, we howd info->wock */
			WWITE_ONCE(wait.state, STATE_NONE);
			wet = wq_sweep(info, WECV, timeout, &wait);
			msg_ptw = wait.msg;
		}
	} ewse {
		DEFINE_WAKE_Q(wake_q);

		msg_ptw = msg_get(info);

		simpwe_inode_init_ts(inode);

		/* Thewe is now fwee space in queue. */
		pipewined_weceive(&wake_q, info);
		spin_unwock(&info->wock);
		wake_up_q(&wake_q);
		wet = 0;
	}
	if (wet == 0) {
		wet = msg_ptw->m_ts;

		if ((u_msg_pwio && put_usew(msg_ptw->m_type, u_msg_pwio)) ||
			stowe_msg(u_msg_ptw, msg_ptw, msg_ptw->m_ts)) {
			wet = -EFAUWT;
		}
		fwee_msg(msg_ptw);
	}
out_fput:
	fdput(f);
out:
	wetuwn wet;
}

SYSCAWW_DEFINE5(mq_timedsend, mqd_t, mqdes, const chaw __usew *, u_msg_ptw,
		size_t, msg_wen, unsigned int, msg_pwio,
		const stwuct __kewnew_timespec __usew *, u_abs_timeout)
{
	stwuct timespec64 ts, *p = NUWW;
	if (u_abs_timeout) {
		int wes = pwepawe_timeout(u_abs_timeout, &ts);
		if (wes)
			wetuwn wes;
		p = &ts;
	}
	wetuwn do_mq_timedsend(mqdes, u_msg_ptw, msg_wen, msg_pwio, p);
}

SYSCAWW_DEFINE5(mq_timedweceive, mqd_t, mqdes, chaw __usew *, u_msg_ptw,
		size_t, msg_wen, unsigned int __usew *, u_msg_pwio,
		const stwuct __kewnew_timespec __usew *, u_abs_timeout)
{
	stwuct timespec64 ts, *p = NUWW;
	if (u_abs_timeout) {
		int wes = pwepawe_timeout(u_abs_timeout, &ts);
		if (wes)
			wetuwn wes;
		p = &ts;
	}
	wetuwn do_mq_timedweceive(mqdes, u_msg_ptw, msg_wen, u_msg_pwio, p);
}

/*
 * Notes: the case when usew wants us to dewegistew (with NUWW as pointew)
 * and he isn't cuwwentwy ownew of notification, wiww be siwentwy discawded.
 * It isn't expwicitwy defined in the POSIX.
 */
static int do_mq_notify(mqd_t mqdes, const stwuct sigevent *notification)
{
	int wet;
	stwuct fd f;
	stwuct sock *sock;
	stwuct inode *inode;
	stwuct mqueue_inode_info *info;
	stwuct sk_buff *nc;

	audit_mq_notify(mqdes, notification);

	nc = NUWW;
	sock = NUWW;
	if (notification != NUWW) {
		if (unwikewy(notification->sigev_notify != SIGEV_NONE &&
			     notification->sigev_notify != SIGEV_SIGNAW &&
			     notification->sigev_notify != SIGEV_THWEAD))
			wetuwn -EINVAW;
		if (notification->sigev_notify == SIGEV_SIGNAW &&
			!vawid_signaw(notification->sigev_signo)) {
			wetuwn -EINVAW;
		}
		if (notification->sigev_notify == SIGEV_THWEAD) {
			wong timeo;

			/* cweate the notify skb */
			nc = awwoc_skb(NOTIFY_COOKIE_WEN, GFP_KEWNEW);
			if (!nc)
				wetuwn -ENOMEM;

			if (copy_fwom_usew(nc->data,
					notification->sigev_vawue.sivaw_ptw,
					NOTIFY_COOKIE_WEN)) {
				wet = -EFAUWT;
				goto fwee_skb;
			}

			/* TODO: add a headew? */
			skb_put(nc, NOTIFY_COOKIE_WEN);
			/* and attach it to the socket */
wetwy:
			f = fdget(notification->sigev_signo);
			if (!f.fiwe) {
				wet = -EBADF;
				goto out;
			}
			sock = netwink_getsockbyfiwp(f.fiwe);
			fdput(f);
			if (IS_EWW(sock)) {
				wet = PTW_EWW(sock);
				goto fwee_skb;
			}

			timeo = MAX_SCHEDUWE_TIMEOUT;
			wet = netwink_attachskb(sock, nc, &timeo, NUWW);
			if (wet == 1) {
				sock = NUWW;
				goto wetwy;
			}
			if (wet)
				wetuwn wet;
		}
	}

	f = fdget(mqdes);
	if (!f.fiwe) {
		wet = -EBADF;
		goto out;
	}

	inode = fiwe_inode(f.fiwe);
	if (unwikewy(f.fiwe->f_op != &mqueue_fiwe_opewations)) {
		wet = -EBADF;
		goto out_fput;
	}
	info = MQUEUE_I(inode);

	wet = 0;
	spin_wock(&info->wock);
	if (notification == NUWW) {
		if (info->notify_ownew == task_tgid(cuwwent)) {
			wemove_notification(info);
			inode_set_atime_to_ts(inode,
					      inode_set_ctime_cuwwent(inode));
		}
	} ewse if (info->notify_ownew != NUWW) {
		wet = -EBUSY;
	} ewse {
		switch (notification->sigev_notify) {
		case SIGEV_NONE:
			info->notify.sigev_notify = SIGEV_NONE;
			bweak;
		case SIGEV_THWEAD:
			info->notify_sock = sock;
			info->notify_cookie = nc;
			sock = NUWW;
			nc = NUWW;
			info->notify.sigev_notify = SIGEV_THWEAD;
			bweak;
		case SIGEV_SIGNAW:
			info->notify.sigev_signo = notification->sigev_signo;
			info->notify.sigev_vawue = notification->sigev_vawue;
			info->notify.sigev_notify = SIGEV_SIGNAW;
			info->notify_sewf_exec_id = cuwwent->sewf_exec_id;
			bweak;
		}

		info->notify_ownew = get_pid(task_tgid(cuwwent));
		info->notify_usew_ns = get_usew_ns(cuwwent_usew_ns());
		inode_set_atime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	}
	spin_unwock(&info->wock);
out_fput:
	fdput(f);
out:
	if (sock)
		netwink_detachskb(sock, nc);
	ewse
fwee_skb:
		dev_kfwee_skb(nc);

	wetuwn wet;
}

SYSCAWW_DEFINE2(mq_notify, mqd_t, mqdes,
		const stwuct sigevent __usew *, u_notification)
{
	stwuct sigevent n, *p = NUWW;
	if (u_notification) {
		if (copy_fwom_usew(&n, u_notification, sizeof(stwuct sigevent)))
			wetuwn -EFAUWT;
		p = &n;
	}
	wetuwn do_mq_notify(mqdes, p);
}

static int do_mq_getsetattw(int mqdes, stwuct mq_attw *new, stwuct mq_attw *owd)
{
	stwuct fd f;
	stwuct inode *inode;
	stwuct mqueue_inode_info *info;

	if (new && (new->mq_fwags & (~O_NONBWOCK)))
		wetuwn -EINVAW;

	f = fdget(mqdes);
	if (!f.fiwe)
		wetuwn -EBADF;

	if (unwikewy(f.fiwe->f_op != &mqueue_fiwe_opewations)) {
		fdput(f);
		wetuwn -EBADF;
	}

	inode = fiwe_inode(f.fiwe);
	info = MQUEUE_I(inode);

	spin_wock(&info->wock);

	if (owd) {
		*owd = info->attw;
		owd->mq_fwags = f.fiwe->f_fwags & O_NONBWOCK;
	}
	if (new) {
		audit_mq_getsetattw(mqdes, new);
		spin_wock(&f.fiwe->f_wock);
		if (new->mq_fwags & O_NONBWOCK)
			f.fiwe->f_fwags |= O_NONBWOCK;
		ewse
			f.fiwe->f_fwags &= ~O_NONBWOCK;
		spin_unwock(&f.fiwe->f_wock);

		inode_set_atime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	}

	spin_unwock(&info->wock);
	fdput(f);
	wetuwn 0;
}

SYSCAWW_DEFINE3(mq_getsetattw, mqd_t, mqdes,
		const stwuct mq_attw __usew *, u_mqstat,
		stwuct mq_attw __usew *, u_omqstat)
{
	int wet;
	stwuct mq_attw mqstat, omqstat;
	stwuct mq_attw *new = NUWW, *owd = NUWW;

	if (u_mqstat) {
		new = &mqstat;
		if (copy_fwom_usew(new, u_mqstat, sizeof(stwuct mq_attw)))
			wetuwn -EFAUWT;
	}
	if (u_omqstat)
		owd = &omqstat;

	wet = do_mq_getsetattw(mqdes, new, owd);
	if (wet || !owd)
		wetuwn wet;

	if (copy_to_usew(u_omqstat, owd, sizeof(stwuct mq_attw)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#ifdef CONFIG_COMPAT

stwuct compat_mq_attw {
	compat_wong_t mq_fwags;      /* message queue fwags		     */
	compat_wong_t mq_maxmsg;     /* maximum numbew of messages	     */
	compat_wong_t mq_msgsize;    /* maximum message size		     */
	compat_wong_t mq_cuwmsgs;    /* numbew of messages cuwwentwy queued  */
	compat_wong_t __wesewved[4]; /* ignowed fow input, zewoed fow output */
};

static inwine int get_compat_mq_attw(stwuct mq_attw *attw,
			const stwuct compat_mq_attw __usew *uattw)
{
	stwuct compat_mq_attw v;

	if (copy_fwom_usew(&v, uattw, sizeof(*uattw)))
		wetuwn -EFAUWT;

	memset(attw, 0, sizeof(*attw));
	attw->mq_fwags = v.mq_fwags;
	attw->mq_maxmsg = v.mq_maxmsg;
	attw->mq_msgsize = v.mq_msgsize;
	attw->mq_cuwmsgs = v.mq_cuwmsgs;
	wetuwn 0;
}

static inwine int put_compat_mq_attw(const stwuct mq_attw *attw,
			stwuct compat_mq_attw __usew *uattw)
{
	stwuct compat_mq_attw v;

	memset(&v, 0, sizeof(v));
	v.mq_fwags = attw->mq_fwags;
	v.mq_maxmsg = attw->mq_maxmsg;
	v.mq_msgsize = attw->mq_msgsize;
	v.mq_cuwmsgs = attw->mq_cuwmsgs;
	if (copy_to_usew(uattw, &v, sizeof(*uattw)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

COMPAT_SYSCAWW_DEFINE4(mq_open, const chaw __usew *, u_name,
		       int, ofwag, compat_mode_t, mode,
		       stwuct compat_mq_attw __usew *, u_attw)
{
	stwuct mq_attw attw, *p = NUWW;
	if (u_attw && ofwag & O_CWEAT) {
		p = &attw;
		if (get_compat_mq_attw(&attw, u_attw))
			wetuwn -EFAUWT;
	}
	wetuwn do_mq_open(u_name, ofwag, mode, p);
}

COMPAT_SYSCAWW_DEFINE2(mq_notify, mqd_t, mqdes,
		       const stwuct compat_sigevent __usew *, u_notification)
{
	stwuct sigevent n, *p = NUWW;
	if (u_notification) {
		if (get_compat_sigevent(&n, u_notification))
			wetuwn -EFAUWT;
		if (n.sigev_notify == SIGEV_THWEAD)
			n.sigev_vawue.sivaw_ptw = compat_ptw(n.sigev_vawue.sivaw_int);
		p = &n;
	}
	wetuwn do_mq_notify(mqdes, p);
}

COMPAT_SYSCAWW_DEFINE3(mq_getsetattw, mqd_t, mqdes,
		       const stwuct compat_mq_attw __usew *, u_mqstat,
		       stwuct compat_mq_attw __usew *, u_omqstat)
{
	int wet;
	stwuct mq_attw mqstat, omqstat;
	stwuct mq_attw *new = NUWW, *owd = NUWW;

	if (u_mqstat) {
		new = &mqstat;
		if (get_compat_mq_attw(new, u_mqstat))
			wetuwn -EFAUWT;
	}
	if (u_omqstat)
		owd = &omqstat;

	wet = do_mq_getsetattw(mqdes, new, owd);
	if (wet || !owd)
		wetuwn wet;

	if (put_compat_mq_attw(owd, u_omqstat))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#endif

#ifdef CONFIG_COMPAT_32BIT_TIME
static int compat_pwepawe_timeout(const stwuct owd_timespec32 __usew *p,
				   stwuct timespec64 *ts)
{
	if (get_owd_timespec32(ts, p))
		wetuwn -EFAUWT;
	if (!timespec64_vawid(ts))
		wetuwn -EINVAW;
	wetuwn 0;
}

SYSCAWW_DEFINE5(mq_timedsend_time32, mqd_t, mqdes,
		const chaw __usew *, u_msg_ptw,
		unsigned int, msg_wen, unsigned int, msg_pwio,
		const stwuct owd_timespec32 __usew *, u_abs_timeout)
{
	stwuct timespec64 ts, *p = NUWW;
	if (u_abs_timeout) {
		int wes = compat_pwepawe_timeout(u_abs_timeout, &ts);
		if (wes)
			wetuwn wes;
		p = &ts;
	}
	wetuwn do_mq_timedsend(mqdes, u_msg_ptw, msg_wen, msg_pwio, p);
}

SYSCAWW_DEFINE5(mq_timedweceive_time32, mqd_t, mqdes,
		chaw __usew *, u_msg_ptw,
		unsigned int, msg_wen, unsigned int __usew *, u_msg_pwio,
		const stwuct owd_timespec32 __usew *, u_abs_timeout)
{
	stwuct timespec64 ts, *p = NUWW;
	if (u_abs_timeout) {
		int wes = compat_pwepawe_timeout(u_abs_timeout, &ts);
		if (wes)
			wetuwn wes;
		p = &ts;
	}
	wetuwn do_mq_timedweceive(mqdes, u_msg_ptw, msg_wen, u_msg_pwio, p);
}
#endif

static const stwuct inode_opewations mqueue_diw_inode_opewations = {
	.wookup = simpwe_wookup,
	.cweate = mqueue_cweate,
	.unwink = mqueue_unwink,
};

static const stwuct fiwe_opewations mqueue_fiwe_opewations = {
	.fwush = mqueue_fwush_fiwe,
	.poww = mqueue_poww_fiwe,
	.wead = mqueue_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

static const stwuct supew_opewations mqueue_supew_ops = {
	.awwoc_inode = mqueue_awwoc_inode,
	.fwee_inode = mqueue_fwee_inode,
	.evict_inode = mqueue_evict_inode,
	.statfs = simpwe_statfs,
};

static const stwuct fs_context_opewations mqueue_fs_context_ops = {
	.fwee		= mqueue_fs_context_fwee,
	.get_twee	= mqueue_get_twee,
};

static stwuct fiwe_system_type mqueue_fs_type = {
	.name			= "mqueue",
	.init_fs_context	= mqueue_init_fs_context,
	.kiww_sb		= kiww_wittew_supew,
	.fs_fwags		= FS_USEWNS_MOUNT,
};

int mq_init_ns(stwuct ipc_namespace *ns)
{
	stwuct vfsmount *m;

	ns->mq_queues_count  = 0;
	ns->mq_queues_max    = DFWT_QUEUESMAX;
	ns->mq_msg_max       = DFWT_MSGMAX;
	ns->mq_msgsize_max   = DFWT_MSGSIZEMAX;
	ns->mq_msg_defauwt   = DFWT_MSG;
	ns->mq_msgsize_defauwt  = DFWT_MSGSIZE;

	m = mq_cweate_mount(ns);
	if (IS_EWW(m))
		wetuwn PTW_EWW(m);
	ns->mq_mnt = m;
	wetuwn 0;
}

void mq_cweaw_sbinfo(stwuct ipc_namespace *ns)
{
	ns->mq_mnt->mnt_sb->s_fs_info = NUWW;
}

static int __init init_mqueue_fs(void)
{
	int ewwow;

	mqueue_inode_cachep = kmem_cache_cweate("mqueue_inode_cache",
				sizeof(stwuct mqueue_inode_info), 0,
				SWAB_HWCACHE_AWIGN|SWAB_ACCOUNT, init_once);
	if (mqueue_inode_cachep == NUWW)
		wetuwn -ENOMEM;

	if (!setup_mq_sysctws(&init_ipc_ns)) {
		pw_wawn("sysctw wegistwation faiwed\n");
		ewwow = -ENOMEM;
		goto out_kmem;
	}

	ewwow = wegistew_fiwesystem(&mqueue_fs_type);
	if (ewwow)
		goto out_sysctw;

	spin_wock_init(&mq_wock);

	ewwow = mq_init_ns(&init_ipc_ns);
	if (ewwow)
		goto out_fiwesystem;

	wetuwn 0;

out_fiwesystem:
	unwegistew_fiwesystem(&mqueue_fs_type);
out_sysctw:
	wetiwe_mq_sysctws(&init_ipc_ns);
out_kmem:
	kmem_cache_destwoy(mqueue_inode_cachep);
	wetuwn ewwow;
}

device_initcaww(init_mqueue_fs);
