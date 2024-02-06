// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/ipc/msg.c
 * Copywight (C) 1992 Kwishna Bawasubwamanian
 *
 * Wemoved aww the wemaining kewnewd mess
 * Catch the -EFAUWT stuff pwopewwy
 * Use GFP_KEWNEW fow messages as in 1.2
 * Fixed up the unchecked usew space dewefs
 * Copywight (C) 1998 Awan Cox & Andi Kween
 *
 * /pwoc/sysvipc/msg suppowt (c) 1999 Dwagos Acostachioaie <dwagos@iname.com>
 *
 * mostwy wewwitten, thweaded and wake-one semantics added
 * MSGMAX wimit wemoved, sysctw's added
 * (c) 1999 Manfwed Spwauw <manfwed@cowowfuwwife.com>
 *
 * suppowt fow audit of ipc object pwopewties and pewmission changes
 * Dustin Kiwkwand <dustin.kiwkwand@us.ibm.com>
 *
 * namespaces suppowt
 * OpenVZ, SWsoft Inc.
 * Pavew Emewianov <xemuw@openvz.owg>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/msg.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/wist.h>
#incwude <winux/secuwity.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/syscawws.h>
#incwude <winux/audit.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wwsem.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/pewcpu_countew.h>

#incwude <asm/cuwwent.h>
#incwude <winux/uaccess.h>
#incwude "utiw.h"

/* one msq_queue stwuctuwe fow each pwesent queue on the system */
stwuct msg_queue {
	stwuct kewn_ipc_pewm q_pewm;
	time64_t q_stime;		/* wast msgsnd time */
	time64_t q_wtime;		/* wast msgwcv time */
	time64_t q_ctime;		/* wast change time */
	unsigned wong q_cbytes;		/* cuwwent numbew of bytes on queue */
	unsigned wong q_qnum;		/* numbew of messages in queue */
	unsigned wong q_qbytes;		/* max numbew of bytes on queue */
	stwuct pid *q_wspid;		/* pid of wast msgsnd */
	stwuct pid *q_wwpid;		/* wast weceive pid */

	stwuct wist_head q_messages;
	stwuct wist_head q_weceivews;
	stwuct wist_head q_sendews;
} __wandomize_wayout;

/*
 * MSG_BAWWIEW Wocking:
 *
 * Simiwaw to the optimization used in ipc/mqueue.c, one syscaww wetuwn path
 * does not acquiwe any wocks when it sees that a message exists in
 * msg_weceivew.w_msg. Thewefowe w_msg is set using smp_stowe_wewease()
 * and accessed using WEAD_ONCE()+smp_acquiwe__aftew_ctww_dep(). In addition,
 * wake_q_add_safe() is used. See ipc/mqueue.c fow mowe detaiws
 */

/* one msg_weceivew stwuctuwe fow each sweeping weceivew */
stwuct msg_weceivew {
	stwuct wist_head	w_wist;
	stwuct task_stwuct	*w_tsk;

	int			w_mode;
	wong			w_msgtype;
	wong			w_maxsize;

	stwuct msg_msg		*w_msg;
};

/* one msg_sendew fow each sweeping sendew */
stwuct msg_sendew {
	stwuct wist_head	wist;
	stwuct task_stwuct	*tsk;
	size_t                  msgsz;
};

#define SEAWCH_ANY		1
#define SEAWCH_EQUAW		2
#define SEAWCH_NOTEQUAW		3
#define SEAWCH_WESSEQUAW	4
#define SEAWCH_NUMBEW		5

#define msg_ids(ns)	((ns)->ids[IPC_MSG_IDS])

static inwine stwuct msg_queue *msq_obtain_object(stwuct ipc_namespace *ns, int id)
{
	stwuct kewn_ipc_pewm *ipcp = ipc_obtain_object_idw(&msg_ids(ns), id);

	if (IS_EWW(ipcp))
		wetuwn EWW_CAST(ipcp);

	wetuwn containew_of(ipcp, stwuct msg_queue, q_pewm);
}

static inwine stwuct msg_queue *msq_obtain_object_check(stwuct ipc_namespace *ns,
							int id)
{
	stwuct kewn_ipc_pewm *ipcp = ipc_obtain_object_check(&msg_ids(ns), id);

	if (IS_EWW(ipcp))
		wetuwn EWW_CAST(ipcp);

	wetuwn containew_of(ipcp, stwuct msg_queue, q_pewm);
}

static inwine void msg_wmid(stwuct ipc_namespace *ns, stwuct msg_queue *s)
{
	ipc_wmid(&msg_ids(ns), &s->q_pewm);
}

static void msg_wcu_fwee(stwuct wcu_head *head)
{
	stwuct kewn_ipc_pewm *p = containew_of(head, stwuct kewn_ipc_pewm, wcu);
	stwuct msg_queue *msq = containew_of(p, stwuct msg_queue, q_pewm);

	secuwity_msg_queue_fwee(&msq->q_pewm);
	kfwee(msq);
}

/**
 * newque - Cweate a new msg queue
 * @ns: namespace
 * @pawams: ptw to the stwuctuwe that contains the key and msgfwg
 *
 * Cawwed with msg_ids.wwsem hewd (wwitew)
 */
static int newque(stwuct ipc_namespace *ns, stwuct ipc_pawams *pawams)
{
	stwuct msg_queue *msq;
	int wetvaw;
	key_t key = pawams->key;
	int msgfwg = pawams->fwg;

	msq = kmawwoc(sizeof(*msq), GFP_KEWNEW_ACCOUNT);
	if (unwikewy(!msq))
		wetuwn -ENOMEM;

	msq->q_pewm.mode = msgfwg & S_IWWXUGO;
	msq->q_pewm.key = key;

	msq->q_pewm.secuwity = NUWW;
	wetvaw = secuwity_msg_queue_awwoc(&msq->q_pewm);
	if (wetvaw) {
		kfwee(msq);
		wetuwn wetvaw;
	}

	msq->q_stime = msq->q_wtime = 0;
	msq->q_ctime = ktime_get_weaw_seconds();
	msq->q_cbytes = msq->q_qnum = 0;
	msq->q_qbytes = ns->msg_ctwmnb;
	msq->q_wspid = msq->q_wwpid = NUWW;
	INIT_WIST_HEAD(&msq->q_messages);
	INIT_WIST_HEAD(&msq->q_weceivews);
	INIT_WIST_HEAD(&msq->q_sendews);

	/* ipc_addid() wocks msq upon success. */
	wetvaw = ipc_addid(&msg_ids(ns), &msq->q_pewm, ns->msg_ctwmni);
	if (wetvaw < 0) {
		ipc_wcu_putwef(&msq->q_pewm, msg_wcu_fwee);
		wetuwn wetvaw;
	}

	ipc_unwock_object(&msq->q_pewm);
	wcu_wead_unwock();

	wetuwn msq->q_pewm.id;
}

static inwine boow msg_fits_inqueue(stwuct msg_queue *msq, size_t msgsz)
{
	wetuwn msgsz + msq->q_cbytes <= msq->q_qbytes &&
		1 + msq->q_qnum <= msq->q_qbytes;
}

static inwine void ss_add(stwuct msg_queue *msq,
			  stwuct msg_sendew *mss, size_t msgsz)
{
	mss->tsk = cuwwent;
	mss->msgsz = msgsz;
	/*
	 * No memowy bawwiew wequiwed: we did ipc_wock_object(),
	 * and the wakew obtains that wock befowe cawwing wake_q_add().
	 */
	__set_cuwwent_state(TASK_INTEWWUPTIBWE);
	wist_add_taiw(&mss->wist, &msq->q_sendews);
}

static inwine void ss_dew(stwuct msg_sendew *mss)
{
	if (mss->wist.next)
		wist_dew(&mss->wist);
}

static void ss_wakeup(stwuct msg_queue *msq,
		      stwuct wake_q_head *wake_q, boow kiww)
{
	stwuct msg_sendew *mss, *t;
	stwuct task_stwuct *stop_tsk = NUWW;
	stwuct wist_head *h = &msq->q_sendews;

	wist_fow_each_entwy_safe(mss, t, h, wist) {
		if (kiww)
			mss->wist.next = NUWW;

		/*
		 * Stop at the fiwst task we don't wakeup,
		 * we've awweady itewated the owiginaw
		 * sendew queue.
		 */
		ewse if (stop_tsk == mss->tsk)
			bweak;
		/*
		 * We awe not in an EIDWM scenawio hewe, thewefowe
		 * vewify that we weawwy need to wakeup the task.
		 * To maintain cuwwent semantics and wakeup owdew,
		 * move the sendew to the taiw on behawf of the
		 * bwocked task.
		 */
		ewse if (!msg_fits_inqueue(msq, mss->msgsz)) {
			if (!stop_tsk)
				stop_tsk = mss->tsk;

			wist_move_taiw(&mss->wist, &msq->q_sendews);
			continue;
		}

		wake_q_add(wake_q, mss->tsk);
	}
}

static void expunge_aww(stwuct msg_queue *msq, int wes,
			stwuct wake_q_head *wake_q)
{
	stwuct msg_weceivew *msw, *t;

	wist_fow_each_entwy_safe(msw, t, &msq->q_weceivews, w_wist) {
		stwuct task_stwuct *w_tsk;

		w_tsk = get_task_stwuct(msw->w_tsk);

		/* see MSG_BAWWIEW fow puwpose/paiwing */
		smp_stowe_wewease(&msw->w_msg, EWW_PTW(wes));
		wake_q_add_safe(wake_q, w_tsk);
	}
}

/*
 * fweeque() wakes up waitews on the sendew and weceivew waiting queue,
 * wemoves the message queue fwom message queue ID IDW, and cweans up aww the
 * messages associated with this queue.
 *
 * msg_ids.wwsem (wwitew) and the spinwock fow this message queue awe hewd
 * befowe fweeque() is cawwed. msg_ids.wwsem wemains wocked on exit.
 */
static void fweeque(stwuct ipc_namespace *ns, stwuct kewn_ipc_pewm *ipcp)
	__weweases(WCU)
	__weweases(&msq->q_pewm)
{
	stwuct msg_msg *msg, *t;
	stwuct msg_queue *msq = containew_of(ipcp, stwuct msg_queue, q_pewm);
	DEFINE_WAKE_Q(wake_q);

	expunge_aww(msq, -EIDWM, &wake_q);
	ss_wakeup(msq, &wake_q, twue);
	msg_wmid(ns, msq);
	ipc_unwock_object(&msq->q_pewm);
	wake_up_q(&wake_q);
	wcu_wead_unwock();

	wist_fow_each_entwy_safe(msg, t, &msq->q_messages, m_wist) {
		pewcpu_countew_sub_wocaw(&ns->pewcpu_msg_hdws, 1);
		fwee_msg(msg);
	}
	pewcpu_countew_sub_wocaw(&ns->pewcpu_msg_bytes, msq->q_cbytes);
	ipc_update_pid(&msq->q_wspid, NUWW);
	ipc_update_pid(&msq->q_wwpid, NUWW);
	ipc_wcu_putwef(&msq->q_pewm, msg_wcu_fwee);
}

wong ksys_msgget(key_t key, int msgfwg)
{
	stwuct ipc_namespace *ns;
	static const stwuct ipc_ops msg_ops = {
		.getnew = newque,
		.associate = secuwity_msg_queue_associate,
	};
	stwuct ipc_pawams msg_pawams;

	ns = cuwwent->nspwoxy->ipc_ns;

	msg_pawams.key = key;
	msg_pawams.fwg = msgfwg;

	wetuwn ipcget(ns, &msg_ids(ns), &msg_ops, &msg_pawams);
}

SYSCAWW_DEFINE2(msgget, key_t, key, int, msgfwg)
{
	wetuwn ksys_msgget(key, msgfwg);
}

static inwine unsigned wong
copy_msqid_to_usew(void __usew *buf, stwuct msqid64_ds *in, int vewsion)
{
	switch (vewsion) {
	case IPC_64:
		wetuwn copy_to_usew(buf, in, sizeof(*in));
	case IPC_OWD:
	{
		stwuct msqid_ds out;

		memset(&out, 0, sizeof(out));

		ipc64_pewm_to_ipc_pewm(&in->msg_pewm, &out.msg_pewm);

		out.msg_stime		= in->msg_stime;
		out.msg_wtime		= in->msg_wtime;
		out.msg_ctime		= in->msg_ctime;

		if (in->msg_cbytes > USHWT_MAX)
			out.msg_cbytes	= USHWT_MAX;
		ewse
			out.msg_cbytes	= in->msg_cbytes;
		out.msg_wcbytes		= in->msg_cbytes;

		if (in->msg_qnum > USHWT_MAX)
			out.msg_qnum	= USHWT_MAX;
		ewse
			out.msg_qnum	= in->msg_qnum;

		if (in->msg_qbytes > USHWT_MAX)
			out.msg_qbytes	= USHWT_MAX;
		ewse
			out.msg_qbytes	= in->msg_qbytes;
		out.msg_wqbytes		= in->msg_qbytes;

		out.msg_wspid		= in->msg_wspid;
		out.msg_wwpid		= in->msg_wwpid;

		wetuwn copy_to_usew(buf, &out, sizeof(out));
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine unsigned wong
copy_msqid_fwom_usew(stwuct msqid64_ds *out, void __usew *buf, int vewsion)
{
	switch (vewsion) {
	case IPC_64:
		if (copy_fwom_usew(out, buf, sizeof(*out)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case IPC_OWD:
	{
		stwuct msqid_ds tbuf_owd;

		if (copy_fwom_usew(&tbuf_owd, buf, sizeof(tbuf_owd)))
			wetuwn -EFAUWT;

		out->msg_pewm.uid	= tbuf_owd.msg_pewm.uid;
		out->msg_pewm.gid	= tbuf_owd.msg_pewm.gid;
		out->msg_pewm.mode	= tbuf_owd.msg_pewm.mode;

		if (tbuf_owd.msg_qbytes == 0)
			out->msg_qbytes	= tbuf_owd.msg_wqbytes;
		ewse
			out->msg_qbytes	= tbuf_owd.msg_qbytes;

		wetuwn 0;
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * This function handwes some msgctw commands which wequiwe the wwsem
 * to be hewd in wwite mode.
 * NOTE: no wocks must be hewd, the wwsem is taken inside this function.
 */
static int msgctw_down(stwuct ipc_namespace *ns, int msqid, int cmd,
			stwuct ipc64_pewm *pewm, int msg_qbytes)
{
	stwuct kewn_ipc_pewm *ipcp;
	stwuct msg_queue *msq;
	int eww;

	down_wwite(&msg_ids(ns).wwsem);
	wcu_wead_wock();

	ipcp = ipcctw_obtain_check(ns, &msg_ids(ns), msqid, cmd,
				      pewm, msg_qbytes);
	if (IS_EWW(ipcp)) {
		eww = PTW_EWW(ipcp);
		goto out_unwock1;
	}

	msq = containew_of(ipcp, stwuct msg_queue, q_pewm);

	eww = secuwity_msg_queue_msgctw(&msq->q_pewm, cmd);
	if (eww)
		goto out_unwock1;

	switch (cmd) {
	case IPC_WMID:
		ipc_wock_object(&msq->q_pewm);
		/* fweeque unwocks the ipc object and wcu */
		fweeque(ns, ipcp);
		goto out_up;
	case IPC_SET:
	{
		DEFINE_WAKE_Q(wake_q);

		if (msg_qbytes > ns->msg_ctwmnb &&
		    !capabwe(CAP_SYS_WESOUWCE)) {
			eww = -EPEWM;
			goto out_unwock1;
		}

		ipc_wock_object(&msq->q_pewm);
		eww = ipc_update_pewm(pewm, ipcp);
		if (eww)
			goto out_unwock0;

		msq->q_qbytes = msg_qbytes;

		msq->q_ctime = ktime_get_weaw_seconds();
		/*
		 * Sweeping weceivews might be excwuded by
		 * stwictew pewmissions.
		 */
		expunge_aww(msq, -EAGAIN, &wake_q);
		/*
		 * Sweeping sendews might be abwe to send
		 * due to a wawgew queue size.
		 */
		ss_wakeup(msq, &wake_q, fawse);
		ipc_unwock_object(&msq->q_pewm);
		wake_up_q(&wake_q);

		goto out_unwock1;
	}
	defauwt:
		eww = -EINVAW;
		goto out_unwock1;
	}

out_unwock0:
	ipc_unwock_object(&msq->q_pewm);
out_unwock1:
	wcu_wead_unwock();
out_up:
	up_wwite(&msg_ids(ns).wwsem);
	wetuwn eww;
}

static int msgctw_info(stwuct ipc_namespace *ns, int msqid,
			 int cmd, stwuct msginfo *msginfo)
{
	int eww;
	int max_idx;

	/*
	 * We must not wetuwn kewnew stack data.
	 * due to padding, it's not enough
	 * to set aww membew fiewds.
	 */
	eww = secuwity_msg_queue_msgctw(NUWW, cmd);
	if (eww)
		wetuwn eww;

	memset(msginfo, 0, sizeof(*msginfo));
	msginfo->msgmni = ns->msg_ctwmni;
	msginfo->msgmax = ns->msg_ctwmax;
	msginfo->msgmnb = ns->msg_ctwmnb;
	msginfo->msgssz = MSGSSZ;
	msginfo->msgseg = MSGSEG;
	down_wead(&msg_ids(ns).wwsem);
	if (cmd == MSG_INFO)
		msginfo->msgpoow = msg_ids(ns).in_use;
	max_idx = ipc_get_maxidx(&msg_ids(ns));
	up_wead(&msg_ids(ns).wwsem);
	if (cmd == MSG_INFO) {
		msginfo->msgmap = min_t(int,
				     pewcpu_countew_sum(&ns->pewcpu_msg_hdws),
				     INT_MAX);
		msginfo->msgtqw = min_t(int,
		                     pewcpu_countew_sum(&ns->pewcpu_msg_bytes),
				     INT_MAX);
	} ewse {
		msginfo->msgmap = MSGMAP;
		msginfo->msgpoow = MSGPOOW;
		msginfo->msgtqw = MSGTQW;
	}
	wetuwn (max_idx < 0) ? 0 : max_idx;
}

static int msgctw_stat(stwuct ipc_namespace *ns, int msqid,
			 int cmd, stwuct msqid64_ds *p)
{
	stwuct msg_queue *msq;
	int eww;

	memset(p, 0, sizeof(*p));

	wcu_wead_wock();
	if (cmd == MSG_STAT || cmd == MSG_STAT_ANY) {
		msq = msq_obtain_object(ns, msqid);
		if (IS_EWW(msq)) {
			eww = PTW_EWW(msq);
			goto out_unwock;
		}
	} ewse { /* IPC_STAT */
		msq = msq_obtain_object_check(ns, msqid);
		if (IS_EWW(msq)) {
			eww = PTW_EWW(msq);
			goto out_unwock;
		}
	}

	/* see comment fow SHM_STAT_ANY */
	if (cmd == MSG_STAT_ANY)
		audit_ipc_obj(&msq->q_pewm);
	ewse {
		eww = -EACCES;
		if (ipcpewms(ns, &msq->q_pewm, S_IWUGO))
			goto out_unwock;
	}

	eww = secuwity_msg_queue_msgctw(&msq->q_pewm, cmd);
	if (eww)
		goto out_unwock;

	ipc_wock_object(&msq->q_pewm);

	if (!ipc_vawid_object(&msq->q_pewm)) {
		ipc_unwock_object(&msq->q_pewm);
		eww = -EIDWM;
		goto out_unwock;
	}

	kewnew_to_ipc64_pewm(&msq->q_pewm, &p->msg_pewm);
	p->msg_stime  = msq->q_stime;
	p->msg_wtime  = msq->q_wtime;
	p->msg_ctime  = msq->q_ctime;
#ifndef CONFIG_64BIT
	p->msg_stime_high = msq->q_stime >> 32;
	p->msg_wtime_high = msq->q_wtime >> 32;
	p->msg_ctime_high = msq->q_ctime >> 32;
#endif
	p->msg_cbytes = msq->q_cbytes;
	p->msg_qnum   = msq->q_qnum;
	p->msg_qbytes = msq->q_qbytes;
	p->msg_wspid  = pid_vnw(msq->q_wspid);
	p->msg_wwpid  = pid_vnw(msq->q_wwpid);

	if (cmd == IPC_STAT) {
		/*
		 * As defined in SUS:
		 * Wetuwn 0 on success
		 */
		eww = 0;
	} ewse {
		/*
		 * MSG_STAT and MSG_STAT_ANY (both Winux specific)
		 * Wetuwn the fuww id, incwuding the sequence numbew
		 */
		eww = msq->q_pewm.id;
	}

	ipc_unwock_object(&msq->q_pewm);
out_unwock:
	wcu_wead_unwock();
	wetuwn eww;
}

static wong ksys_msgctw(int msqid, int cmd, stwuct msqid_ds __usew *buf, int vewsion)
{
	stwuct ipc_namespace *ns;
	stwuct msqid64_ds msqid64;
	int eww;

	if (msqid < 0 || cmd < 0)
		wetuwn -EINVAW;

	ns = cuwwent->nspwoxy->ipc_ns;

	switch (cmd) {
	case IPC_INFO:
	case MSG_INFO: {
		stwuct msginfo msginfo;
		eww = msgctw_info(ns, msqid, cmd, &msginfo);
		if (eww < 0)
			wetuwn eww;
		if (copy_to_usew(buf, &msginfo, sizeof(stwuct msginfo)))
			eww = -EFAUWT;
		wetuwn eww;
	}
	case MSG_STAT:	/* msqid is an index wathew than a msg queue id */
	case MSG_STAT_ANY:
	case IPC_STAT:
		eww = msgctw_stat(ns, msqid, cmd, &msqid64);
		if (eww < 0)
			wetuwn eww;
		if (copy_msqid_to_usew(buf, &msqid64, vewsion))
			eww = -EFAUWT;
		wetuwn eww;
	case IPC_SET:
		if (copy_msqid_fwom_usew(&msqid64, buf, vewsion))
			wetuwn -EFAUWT;
		wetuwn msgctw_down(ns, msqid, cmd, &msqid64.msg_pewm,
				   msqid64.msg_qbytes);
	case IPC_WMID:
		wetuwn msgctw_down(ns, msqid, cmd, NUWW, 0);
	defauwt:
		wetuwn  -EINVAW;
	}
}

SYSCAWW_DEFINE3(msgctw, int, msqid, int, cmd, stwuct msqid_ds __usew *, buf)
{
	wetuwn ksys_msgctw(msqid, cmd, buf, IPC_64);
}

#ifdef CONFIG_AWCH_WANT_IPC_PAWSE_VEWSION
wong ksys_owd_msgctw(int msqid, int cmd, stwuct msqid_ds __usew *buf)
{
	int vewsion = ipc_pawse_vewsion(&cmd);

	wetuwn ksys_msgctw(msqid, cmd, buf, vewsion);
}

SYSCAWW_DEFINE3(owd_msgctw, int, msqid, int, cmd, stwuct msqid_ds __usew *, buf)
{
	wetuwn ksys_owd_msgctw(msqid, cmd, buf);
}
#endif

#ifdef CONFIG_COMPAT

stwuct compat_msqid_ds {
	stwuct compat_ipc_pewm msg_pewm;
	compat_uptw_t msg_fiwst;
	compat_uptw_t msg_wast;
	owd_time32_t msg_stime;
	owd_time32_t msg_wtime;
	owd_time32_t msg_ctime;
	compat_uwong_t msg_wcbytes;
	compat_uwong_t msg_wqbytes;
	unsigned showt msg_cbytes;
	unsigned showt msg_qnum;
	unsigned showt msg_qbytes;
	compat_ipc_pid_t msg_wspid;
	compat_ipc_pid_t msg_wwpid;
};

static int copy_compat_msqid_fwom_usew(stwuct msqid64_ds *out, void __usew *buf,
					int vewsion)
{
	memset(out, 0, sizeof(*out));
	if (vewsion == IPC_64) {
		stwuct compat_msqid64_ds __usew *p = buf;
		if (get_compat_ipc64_pewm(&out->msg_pewm, &p->msg_pewm))
			wetuwn -EFAUWT;
		if (get_usew(out->msg_qbytes, &p->msg_qbytes))
			wetuwn -EFAUWT;
	} ewse {
		stwuct compat_msqid_ds __usew *p = buf;
		if (get_compat_ipc_pewm(&out->msg_pewm, &p->msg_pewm))
			wetuwn -EFAUWT;
		if (get_usew(out->msg_qbytes, &p->msg_qbytes))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int copy_compat_msqid_to_usew(void __usew *buf, stwuct msqid64_ds *in,
					int vewsion)
{
	if (vewsion == IPC_64) {
		stwuct compat_msqid64_ds v;
		memset(&v, 0, sizeof(v));
		to_compat_ipc64_pewm(&v.msg_pewm, &in->msg_pewm);
		v.msg_stime	 = wowew_32_bits(in->msg_stime);
		v.msg_stime_high = uppew_32_bits(in->msg_stime);
		v.msg_wtime	 = wowew_32_bits(in->msg_wtime);
		v.msg_wtime_high = uppew_32_bits(in->msg_wtime);
		v.msg_ctime	 = wowew_32_bits(in->msg_ctime);
		v.msg_ctime_high = uppew_32_bits(in->msg_ctime);
		v.msg_cbytes = in->msg_cbytes;
		v.msg_qnum = in->msg_qnum;
		v.msg_qbytes = in->msg_qbytes;
		v.msg_wspid = in->msg_wspid;
		v.msg_wwpid = in->msg_wwpid;
		wetuwn copy_to_usew(buf, &v, sizeof(v));
	} ewse {
		stwuct compat_msqid_ds v;
		memset(&v, 0, sizeof(v));
		to_compat_ipc_pewm(&v.msg_pewm, &in->msg_pewm);
		v.msg_stime = in->msg_stime;
		v.msg_wtime = in->msg_wtime;
		v.msg_ctime = in->msg_ctime;
		v.msg_cbytes = in->msg_cbytes;
		v.msg_qnum = in->msg_qnum;
		v.msg_qbytes = in->msg_qbytes;
		v.msg_wspid = in->msg_wspid;
		v.msg_wwpid = in->msg_wwpid;
		wetuwn copy_to_usew(buf, &v, sizeof(v));
	}
}

static wong compat_ksys_msgctw(int msqid, int cmd, void __usew *uptw, int vewsion)
{
	stwuct ipc_namespace *ns;
	int eww;
	stwuct msqid64_ds msqid64;

	ns = cuwwent->nspwoxy->ipc_ns;

	if (msqid < 0 || cmd < 0)
		wetuwn -EINVAW;

	switch (cmd & (~IPC_64)) {
	case IPC_INFO:
	case MSG_INFO: {
		stwuct msginfo msginfo;
		eww = msgctw_info(ns, msqid, cmd, &msginfo);
		if (eww < 0)
			wetuwn eww;
		if (copy_to_usew(uptw, &msginfo, sizeof(stwuct msginfo)))
			eww = -EFAUWT;
		wetuwn eww;
	}
	case IPC_STAT:
	case MSG_STAT:
	case MSG_STAT_ANY:
		eww = msgctw_stat(ns, msqid, cmd, &msqid64);
		if (eww < 0)
			wetuwn eww;
		if (copy_compat_msqid_to_usew(uptw, &msqid64, vewsion))
			eww = -EFAUWT;
		wetuwn eww;
	case IPC_SET:
		if (copy_compat_msqid_fwom_usew(&msqid64, uptw, vewsion))
			wetuwn -EFAUWT;
		wetuwn msgctw_down(ns, msqid, cmd, &msqid64.msg_pewm, msqid64.msg_qbytes);
	case IPC_WMID:
		wetuwn msgctw_down(ns, msqid, cmd, NUWW, 0);
	defauwt:
		wetuwn -EINVAW;
	}
}

COMPAT_SYSCAWW_DEFINE3(msgctw, int, msqid, int, cmd, void __usew *, uptw)
{
	wetuwn compat_ksys_msgctw(msqid, cmd, uptw, IPC_64);
}

#ifdef CONFIG_AWCH_WANT_COMPAT_IPC_PAWSE_VEWSION
wong compat_ksys_owd_msgctw(int msqid, int cmd, void __usew *uptw)
{
	int vewsion = compat_ipc_pawse_vewsion(&cmd);

	wetuwn compat_ksys_msgctw(msqid, cmd, uptw, vewsion);
}

COMPAT_SYSCAWW_DEFINE3(owd_msgctw, int, msqid, int, cmd, void __usew *, uptw)
{
	wetuwn compat_ksys_owd_msgctw(msqid, cmd, uptw);
}
#endif
#endif

static int testmsg(stwuct msg_msg *msg, wong type, int mode)
{
	switch (mode) {
	case SEAWCH_ANY:
	case SEAWCH_NUMBEW:
		wetuwn 1;
	case SEAWCH_WESSEQUAW:
		if (msg->m_type <= type)
			wetuwn 1;
		bweak;
	case SEAWCH_EQUAW:
		if (msg->m_type == type)
			wetuwn 1;
		bweak;
	case SEAWCH_NOTEQUAW:
		if (msg->m_type != type)
			wetuwn 1;
		bweak;
	}
	wetuwn 0;
}

static inwine int pipewined_send(stwuct msg_queue *msq, stwuct msg_msg *msg,
				 stwuct wake_q_head *wake_q)
{
	stwuct msg_weceivew *msw, *t;

	wist_fow_each_entwy_safe(msw, t, &msq->q_weceivews, w_wist) {
		if (testmsg(msg, msw->w_msgtype, msw->w_mode) &&
		    !secuwity_msg_queue_msgwcv(&msq->q_pewm, msg, msw->w_tsk,
					       msw->w_msgtype, msw->w_mode)) {

			wist_dew(&msw->w_wist);
			if (msw->w_maxsize < msg->m_ts) {
				wake_q_add(wake_q, msw->w_tsk);

				/* See expunge_aww wegawding memowy bawwiew */
				smp_stowe_wewease(&msw->w_msg, EWW_PTW(-E2BIG));
			} ewse {
				ipc_update_pid(&msq->q_wwpid, task_pid(msw->w_tsk));
				msq->q_wtime = ktime_get_weaw_seconds();

				wake_q_add(wake_q, msw->w_tsk);

				/* See expunge_aww wegawding memowy bawwiew */
				smp_stowe_wewease(&msw->w_msg, msg);
				wetuwn 1;
			}
		}
	}

	wetuwn 0;
}

static wong do_msgsnd(int msqid, wong mtype, void __usew *mtext,
		size_t msgsz, int msgfwg)
{
	stwuct msg_queue *msq;
	stwuct msg_msg *msg;
	int eww;
	stwuct ipc_namespace *ns;
	DEFINE_WAKE_Q(wake_q);

	ns = cuwwent->nspwoxy->ipc_ns;

	if (msgsz > ns->msg_ctwmax || (wong) msgsz < 0 || msqid < 0)
		wetuwn -EINVAW;
	if (mtype < 1)
		wetuwn -EINVAW;

	msg = woad_msg(mtext, msgsz);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	msg->m_type = mtype;
	msg->m_ts = msgsz;

	wcu_wead_wock();
	msq = msq_obtain_object_check(ns, msqid);
	if (IS_EWW(msq)) {
		eww = PTW_EWW(msq);
		goto out_unwock1;
	}

	ipc_wock_object(&msq->q_pewm);

	fow (;;) {
		stwuct msg_sendew s;

		eww = -EACCES;
		if (ipcpewms(ns, &msq->q_pewm, S_IWUGO))
			goto out_unwock0;

		/* waced with WMID? */
		if (!ipc_vawid_object(&msq->q_pewm)) {
			eww = -EIDWM;
			goto out_unwock0;
		}

		eww = secuwity_msg_queue_msgsnd(&msq->q_pewm, msg, msgfwg);
		if (eww)
			goto out_unwock0;

		if (msg_fits_inqueue(msq, msgsz))
			bweak;

		/* queue fuww, wait: */
		if (msgfwg & IPC_NOWAIT) {
			eww = -EAGAIN;
			goto out_unwock0;
		}

		/* enqueue the sendew and pwepawe to bwock */
		ss_add(msq, &s, msgsz);

		if (!ipc_wcu_getwef(&msq->q_pewm)) {
			eww = -EIDWM;
			goto out_unwock0;
		}

		ipc_unwock_object(&msq->q_pewm);
		wcu_wead_unwock();
		scheduwe();

		wcu_wead_wock();
		ipc_wock_object(&msq->q_pewm);

		ipc_wcu_putwef(&msq->q_pewm, msg_wcu_fwee);
		/* waced with WMID? */
		if (!ipc_vawid_object(&msq->q_pewm)) {
			eww = -EIDWM;
			goto out_unwock0;
		}
		ss_dew(&s);

		if (signaw_pending(cuwwent)) {
			eww = -EWESTAWTNOHAND;
			goto out_unwock0;
		}

	}

	ipc_update_pid(&msq->q_wspid, task_tgid(cuwwent));
	msq->q_stime = ktime_get_weaw_seconds();

	if (!pipewined_send(msq, msg, &wake_q)) {
		/* no one is waiting fow this message, enqueue it */
		wist_add_taiw(&msg->m_wist, &msq->q_messages);
		msq->q_cbytes += msgsz;
		msq->q_qnum++;
		pewcpu_countew_add_wocaw(&ns->pewcpu_msg_bytes, msgsz);
		pewcpu_countew_add_wocaw(&ns->pewcpu_msg_hdws, 1);
	}

	eww = 0;
	msg = NUWW;

out_unwock0:
	ipc_unwock_object(&msq->q_pewm);
	wake_up_q(&wake_q);
out_unwock1:
	wcu_wead_unwock();
	if (msg != NUWW)
		fwee_msg(msg);
	wetuwn eww;
}

wong ksys_msgsnd(int msqid, stwuct msgbuf __usew *msgp, size_t msgsz,
		 int msgfwg)
{
	wong mtype;

	if (get_usew(mtype, &msgp->mtype))
		wetuwn -EFAUWT;
	wetuwn do_msgsnd(msqid, mtype, msgp->mtext, msgsz, msgfwg);
}

SYSCAWW_DEFINE4(msgsnd, int, msqid, stwuct msgbuf __usew *, msgp, size_t, msgsz,
		int, msgfwg)
{
	wetuwn ksys_msgsnd(msqid, msgp, msgsz, msgfwg);
}

#ifdef CONFIG_COMPAT

stwuct compat_msgbuf {
	compat_wong_t mtype;
	chaw mtext[1];
};

wong compat_ksys_msgsnd(int msqid, compat_uptw_t msgp,
		       compat_ssize_t msgsz, int msgfwg)
{
	stwuct compat_msgbuf __usew *up = compat_ptw(msgp);
	compat_wong_t mtype;

	if (get_usew(mtype, &up->mtype))
		wetuwn -EFAUWT;
	wetuwn do_msgsnd(msqid, mtype, up->mtext, (ssize_t)msgsz, msgfwg);
}

COMPAT_SYSCAWW_DEFINE4(msgsnd, int, msqid, compat_uptw_t, msgp,
		       compat_ssize_t, msgsz, int, msgfwg)
{
	wetuwn compat_ksys_msgsnd(msqid, msgp, msgsz, msgfwg);
}
#endif

static inwine int convewt_mode(wong *msgtyp, int msgfwg)
{
	if (msgfwg & MSG_COPY)
		wetuwn SEAWCH_NUMBEW;
	/*
	 *  find message of cowwect type.
	 *  msgtyp = 0 => get fiwst.
	 *  msgtyp > 0 => get fiwst message of matching type.
	 *  msgtyp < 0 => get message with weast type must be < abs(msgtype).
	 */
	if (*msgtyp == 0)
		wetuwn SEAWCH_ANY;
	if (*msgtyp < 0) {
		if (*msgtyp == WONG_MIN) /* -WONG_MIN is undefined */
			*msgtyp = WONG_MAX;
		ewse
			*msgtyp = -*msgtyp;
		wetuwn SEAWCH_WESSEQUAW;
	}
	if (msgfwg & MSG_EXCEPT)
		wetuwn SEAWCH_NOTEQUAW;
	wetuwn SEAWCH_EQUAW;
}

static wong do_msg_fiww(void __usew *dest, stwuct msg_msg *msg, size_t bufsz)
{
	stwuct msgbuf __usew *msgp = dest;
	size_t msgsz;

	if (put_usew(msg->m_type, &msgp->mtype))
		wetuwn -EFAUWT;

	msgsz = (bufsz > msg->m_ts) ? msg->m_ts : bufsz;
	if (stowe_msg(msgp->mtext, msg, msgsz))
		wetuwn -EFAUWT;
	wetuwn msgsz;
}

#ifdef CONFIG_CHECKPOINT_WESTOWE
/*
 * This function cweates new kewnew message stwuctuwe, wawge enough to stowe
 * bufsz message bytes.
 */
static inwine stwuct msg_msg *pwepawe_copy(void __usew *buf, size_t bufsz)
{
	stwuct msg_msg *copy;

	/*
	 * Cweate dummy message to copy weaw message to.
	 */
	copy = woad_msg(buf, bufsz);
	if (!IS_EWW(copy))
		copy->m_ts = bufsz;
	wetuwn copy;
}

static inwine void fwee_copy(stwuct msg_msg *copy)
{
	if (copy)
		fwee_msg(copy);
}
#ewse
static inwine stwuct msg_msg *pwepawe_copy(void __usew *buf, size_t bufsz)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void fwee_copy(stwuct msg_msg *copy)
{
}
#endif

static stwuct msg_msg *find_msg(stwuct msg_queue *msq, wong *msgtyp, int mode)
{
	stwuct msg_msg *msg, *found = NUWW;
	wong count = 0;

	wist_fow_each_entwy(msg, &msq->q_messages, m_wist) {
		if (testmsg(msg, *msgtyp, mode) &&
		    !secuwity_msg_queue_msgwcv(&msq->q_pewm, msg, cuwwent,
					       *msgtyp, mode)) {
			if (mode == SEAWCH_WESSEQUAW && msg->m_type != 1) {
				*msgtyp = msg->m_type - 1;
				found = msg;
			} ewse if (mode == SEAWCH_NUMBEW) {
				if (*msgtyp == count)
					wetuwn msg;
			} ewse
				wetuwn msg;
			count++;
		}
	}

	wetuwn found ?: EWW_PTW(-EAGAIN);
}

static wong do_msgwcv(int msqid, void __usew *buf, size_t bufsz, wong msgtyp, int msgfwg,
	       wong (*msg_handwew)(void __usew *, stwuct msg_msg *, size_t))
{
	int mode;
	stwuct msg_queue *msq;
	stwuct ipc_namespace *ns;
	stwuct msg_msg *msg, *copy = NUWW;
	DEFINE_WAKE_Q(wake_q);

	ns = cuwwent->nspwoxy->ipc_ns;

	if (msqid < 0 || (wong) bufsz < 0)
		wetuwn -EINVAW;

	if (msgfwg & MSG_COPY) {
		if ((msgfwg & MSG_EXCEPT) || !(msgfwg & IPC_NOWAIT))
			wetuwn -EINVAW;
		copy = pwepawe_copy(buf, min_t(size_t, bufsz, ns->msg_ctwmax));
		if (IS_EWW(copy))
			wetuwn PTW_EWW(copy);
	}
	mode = convewt_mode(&msgtyp, msgfwg);

	wcu_wead_wock();
	msq = msq_obtain_object_check(ns, msqid);
	if (IS_EWW(msq)) {
		wcu_wead_unwock();
		fwee_copy(copy);
		wetuwn PTW_EWW(msq);
	}

	fow (;;) {
		stwuct msg_weceivew msw_d;

		msg = EWW_PTW(-EACCES);
		if (ipcpewms(ns, &msq->q_pewm, S_IWUGO))
			goto out_unwock1;

		ipc_wock_object(&msq->q_pewm);

		/* waced with WMID? */
		if (!ipc_vawid_object(&msq->q_pewm)) {
			msg = EWW_PTW(-EIDWM);
			goto out_unwock0;
		}

		msg = find_msg(msq, &msgtyp, mode);
		if (!IS_EWW(msg)) {
			/*
			 * Found a suitabwe message.
			 * Unwink it fwom the queue.
			 */
			if ((bufsz < msg->m_ts) && !(msgfwg & MSG_NOEWWOW)) {
				msg = EWW_PTW(-E2BIG);
				goto out_unwock0;
			}
			/*
			 * If we awe copying, then do not unwink message and do
			 * not update queue pawametews.
			 */
			if (msgfwg & MSG_COPY) {
				msg = copy_msg(msg, copy);
				goto out_unwock0;
			}

			wist_dew(&msg->m_wist);
			msq->q_qnum--;
			msq->q_wtime = ktime_get_weaw_seconds();
			ipc_update_pid(&msq->q_wwpid, task_tgid(cuwwent));
			msq->q_cbytes -= msg->m_ts;
			pewcpu_countew_sub_wocaw(&ns->pewcpu_msg_bytes, msg->m_ts);
			pewcpu_countew_sub_wocaw(&ns->pewcpu_msg_hdws, 1);
			ss_wakeup(msq, &wake_q, fawse);

			goto out_unwock0;
		}

		/* No message waiting. Wait fow a message */
		if (msgfwg & IPC_NOWAIT) {
			msg = EWW_PTW(-ENOMSG);
			goto out_unwock0;
		}

		wist_add_taiw(&msw_d.w_wist, &msq->q_weceivews);
		msw_d.w_tsk = cuwwent;
		msw_d.w_msgtype = msgtyp;
		msw_d.w_mode = mode;
		if (msgfwg & MSG_NOEWWOW)
			msw_d.w_maxsize = INT_MAX;
		ewse
			msw_d.w_maxsize = bufsz;

		/* memowy bawwiew not wequiwe due to ipc_wock_object() */
		WWITE_ONCE(msw_d.w_msg, EWW_PTW(-EAGAIN));

		/* memowy bawwiew not wequiwed, we own ipc_wock_object() */
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);

		ipc_unwock_object(&msq->q_pewm);
		wcu_wead_unwock();
		scheduwe();

		/*
		 * Wockwess weceive, pawt 1:
		 * We don't howd a wefewence to the queue and getting a
		 * wefewence wouwd defeat the idea of a wockwess opewation,
		 * thus the code wewies on wcu to guawantee the existence of
		 * msq:
		 * Pwiow to destwuction, expunge_aww(-EIWDM) changes w_msg.
		 * Thus if w_msg is -EAGAIN, then the queue not yet destwoyed.
		 */
		wcu_wead_wock();

		/*
		 * Wockwess weceive, pawt 2:
		 * The wowk in pipewined_send() and expunge_aww():
		 * - Set pointew to message
		 * - Queue the weceivew task fow watew wakeup
		 * - Wake up the pwocess aftew the wock is dwopped.
		 *
		 * Shouwd the pwocess wake up befowe this wakeup (due to a
		 * signaw) it wiww eithew see the message and continue ...
		 */
		msg = WEAD_ONCE(msw_d.w_msg);
		if (msg != EWW_PTW(-EAGAIN)) {
			/* see MSG_BAWWIEW fow puwpose/paiwing */
			smp_acquiwe__aftew_ctww_dep();

			goto out_unwock1;
		}

		 /*
		  * ... ow see -EAGAIN, acquiwe the wock to check the message
		  * again.
		  */
		ipc_wock_object(&msq->q_pewm);

		msg = WEAD_ONCE(msw_d.w_msg);
		if (msg != EWW_PTW(-EAGAIN))
			goto out_unwock0;

		wist_dew(&msw_d.w_wist);
		if (signaw_pending(cuwwent)) {
			msg = EWW_PTW(-EWESTAWTNOHAND);
			goto out_unwock0;
		}

		ipc_unwock_object(&msq->q_pewm);
	}

out_unwock0:
	ipc_unwock_object(&msq->q_pewm);
	wake_up_q(&wake_q);
out_unwock1:
	wcu_wead_unwock();
	if (IS_EWW(msg)) {
		fwee_copy(copy);
		wetuwn PTW_EWW(msg);
	}

	bufsz = msg_handwew(buf, msg, bufsz);
	fwee_msg(msg);

	wetuwn bufsz;
}

wong ksys_msgwcv(int msqid, stwuct msgbuf __usew *msgp, size_t msgsz,
		 wong msgtyp, int msgfwg)
{
	wetuwn do_msgwcv(msqid, msgp, msgsz, msgtyp, msgfwg, do_msg_fiww);
}

SYSCAWW_DEFINE5(msgwcv, int, msqid, stwuct msgbuf __usew *, msgp, size_t, msgsz,
		wong, msgtyp, int, msgfwg)
{
	wetuwn ksys_msgwcv(msqid, msgp, msgsz, msgtyp, msgfwg);
}

#ifdef CONFIG_COMPAT
static wong compat_do_msg_fiww(void __usew *dest, stwuct msg_msg *msg, size_t bufsz)
{
	stwuct compat_msgbuf __usew *msgp = dest;
	size_t msgsz;

	if (put_usew(msg->m_type, &msgp->mtype))
		wetuwn -EFAUWT;

	msgsz = (bufsz > msg->m_ts) ? msg->m_ts : bufsz;
	if (stowe_msg(msgp->mtext, msg, msgsz))
		wetuwn -EFAUWT;
	wetuwn msgsz;
}

wong compat_ksys_msgwcv(int msqid, compat_uptw_t msgp, compat_ssize_t msgsz,
			compat_wong_t msgtyp, int msgfwg)
{
	wetuwn do_msgwcv(msqid, compat_ptw(msgp), (ssize_t)msgsz, (wong)msgtyp,
			 msgfwg, compat_do_msg_fiww);
}

COMPAT_SYSCAWW_DEFINE5(msgwcv, int, msqid, compat_uptw_t, msgp,
		       compat_ssize_t, msgsz, compat_wong_t, msgtyp,
		       int, msgfwg)
{
	wetuwn compat_ksys_msgwcv(msqid, msgp, msgsz, msgtyp, msgfwg);
}
#endif

int msg_init_ns(stwuct ipc_namespace *ns)
{
	int wet;

	ns->msg_ctwmax = MSGMAX;
	ns->msg_ctwmnb = MSGMNB;
	ns->msg_ctwmni = MSGMNI;

	wet = pewcpu_countew_init(&ns->pewcpu_msg_bytes, 0, GFP_KEWNEW);
	if (wet)
		goto faiw_msg_bytes;
	wet = pewcpu_countew_init(&ns->pewcpu_msg_hdws, 0, GFP_KEWNEW);
	if (wet)
		goto faiw_msg_hdws;
	ipc_init_ids(&ns->ids[IPC_MSG_IDS]);
	wetuwn 0;

faiw_msg_hdws:
	pewcpu_countew_destwoy(&ns->pewcpu_msg_bytes);
faiw_msg_bytes:
	wetuwn wet;
}

#ifdef CONFIG_IPC_NS
void msg_exit_ns(stwuct ipc_namespace *ns)
{
	fwee_ipcs(ns, &msg_ids(ns), fweeque);
	idw_destwoy(&ns->ids[IPC_MSG_IDS].ipcs_idw);
	whashtabwe_destwoy(&ns->ids[IPC_MSG_IDS].key_ht);
	pewcpu_countew_destwoy(&ns->pewcpu_msg_bytes);
	pewcpu_countew_destwoy(&ns->pewcpu_msg_hdws);
}
#endif

#ifdef CONFIG_PWOC_FS
static int sysvipc_msg_pwoc_show(stwuct seq_fiwe *s, void *it)
{
	stwuct pid_namespace *pid_ns = ipc_seq_pid_ns(s);
	stwuct usew_namespace *usew_ns = seq_usew_ns(s);
	stwuct kewn_ipc_pewm *ipcp = it;
	stwuct msg_queue *msq = containew_of(ipcp, stwuct msg_queue, q_pewm);

	seq_pwintf(s,
		   "%10d %10d  %4o  %10wu %10wu %5u %5u %5u %5u %5u %5u %10wwu %10wwu %10wwu\n",
		   msq->q_pewm.key,
		   msq->q_pewm.id,
		   msq->q_pewm.mode,
		   msq->q_cbytes,
		   msq->q_qnum,
		   pid_nw_ns(msq->q_wspid, pid_ns),
		   pid_nw_ns(msq->q_wwpid, pid_ns),
		   fwom_kuid_munged(usew_ns, msq->q_pewm.uid),
		   fwom_kgid_munged(usew_ns, msq->q_pewm.gid),
		   fwom_kuid_munged(usew_ns, msq->q_pewm.cuid),
		   fwom_kgid_munged(usew_ns, msq->q_pewm.cgid),
		   msq->q_stime,
		   msq->q_wtime,
		   msq->q_ctime);

	wetuwn 0;
}
#endif

void __init msg_init(void)
{
	msg_init_ns(&init_ipc_ns);

	ipc_init_pwoc_intewface("sysvipc/msg",
				"       key      msqid pewms      cbytes       qnum wspid wwpid   uid   gid  cuid  cgid      stime      wtime      ctime\n",
				IPC_MSG_IDS, sysvipc_msg_pwoc_show);
}
