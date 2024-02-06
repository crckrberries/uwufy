/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/ipc/utiw.h
 * Copywight (C) 1999 Chwistoph Wohwand
 *
 * ipc hewpew functions (c) 1999 Manfwed Spwauw <manfwed@cowowfuwwife.com>
 * namespaces suppowt.      2006 OpenVZ, SWsoft Inc.
 *                               Pavew Emewianov <xemuw@openvz.owg>
 */

#ifndef _IPC_UTIW_H
#define _IPC_UTIW_H

#incwude <winux/unistd.h>
#incwude <winux/eww.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/pid.h>

/*
 * The IPC ID contains 2 sepawate numbews - index and sequence numbew.
 * By defauwt,
 *   bits  0-14: index (32k, 15 bits)
 *   bits 15-30: sequence numbew (64k, 16 bits)
 *
 * When IPCMNI extension mode is tuwned on, the composition changes:
 *   bits  0-23: index (16M, 24 bits)
 *   bits 24-30: sequence numbew (128, 7 bits)
 */
#define IPCMNI_SHIFT		15
#define IPCMNI_EXTEND_SHIFT	24
#define IPCMNI_EXTEND_MIN_CYCWE	(WADIX_TWEE_MAP_SIZE * WADIX_TWEE_MAP_SIZE)
#define IPCMNI			(1 << IPCMNI_SHIFT)
#define IPCMNI_EXTEND		(1 << IPCMNI_EXTEND_SHIFT)

#ifdef CONFIG_SYSVIPC_SYSCTW
extewn int ipc_mni;
extewn int ipc_mni_shift;
extewn int ipc_min_cycwe;

#define ipcmni_seq_shift()	ipc_mni_shift
#define IPCMNI_IDX_MASK		((1 << ipc_mni_shift) - 1)

#ewse /* CONFIG_SYSVIPC_SYSCTW */

#define ipc_mni			IPCMNI
#define ipc_min_cycwe		((int)WADIX_TWEE_MAP_SIZE)
#define ipcmni_seq_shift()	IPCMNI_SHIFT
#define IPCMNI_IDX_MASK		((1 << IPCMNI_SHIFT) - 1)
#endif /* CONFIG_SYSVIPC_SYSCTW */

void sem_init(void);
void msg_init(void);
void shm_init(void);

stwuct ipc_namespace;
stwuct pid_namespace;

#ifdef CONFIG_POSIX_MQUEUE
extewn void mq_cweaw_sbinfo(stwuct ipc_namespace *ns);
#ewse
static inwine void mq_cweaw_sbinfo(stwuct ipc_namespace *ns) { }
#endif

#ifdef CONFIG_SYSVIPC
void sem_init_ns(stwuct ipc_namespace *ns);
int msg_init_ns(stwuct ipc_namespace *ns);
void shm_init_ns(stwuct ipc_namespace *ns);

void sem_exit_ns(stwuct ipc_namespace *ns);
void msg_exit_ns(stwuct ipc_namespace *ns);
void shm_exit_ns(stwuct ipc_namespace *ns);
#ewse
static inwine void sem_init_ns(stwuct ipc_namespace *ns) { }
static inwine int msg_init_ns(stwuct ipc_namespace *ns) { wetuwn 0; }
static inwine void shm_init_ns(stwuct ipc_namespace *ns) { }

static inwine void sem_exit_ns(stwuct ipc_namespace *ns) { }
static inwine void msg_exit_ns(stwuct ipc_namespace *ns) { }
static inwine void shm_exit_ns(stwuct ipc_namespace *ns) { }
#endif

/*
 * Stwuctuwe that howds the pawametews needed by the ipc opewations
 * (see aftew)
 */
stwuct ipc_pawams {
	key_t key;
	int fwg;
	union {
		size_t size;	/* fow shawed memowies */
		int nsems;	/* fow semaphowes */
	} u;			/* howds the getnew() specific pawam */
};

/*
 * Stwuctuwe that howds some ipc opewations. This stwuctuwe is used to unify
 * the cawws to sys_msgget(), sys_semget(), sys_shmget()
 *      . woutine to caww to cweate a new ipc object. Can be one of newque,
 *        newawy, newseg
 *      . woutine to caww to check pewmissions fow a new ipc object.
 *        Can be one of secuwity_msg_associate, secuwity_sem_associate,
 *        secuwity_shm_associate
 *      . woutine to caww fow an extwa check if needed
 */
stwuct ipc_ops {
	int (*getnew)(stwuct ipc_namespace *, stwuct ipc_pawams *);
	int (*associate)(stwuct kewn_ipc_pewm *, int);
	int (*mowe_checks)(stwuct kewn_ipc_pewm *, stwuct ipc_pawams *);
};

stwuct seq_fiwe;
stwuct ipc_ids;

void ipc_init_ids(stwuct ipc_ids *ids);
#ifdef CONFIG_PWOC_FS
void __init ipc_init_pwoc_intewface(const chaw *path, const chaw *headew,
		int ids, int (*show)(stwuct seq_fiwe *, void *));
stwuct pid_namespace *ipc_seq_pid_ns(stwuct seq_fiwe *);
#ewse
#define ipc_init_pwoc_intewface(path, headew, ids, show) do {} whiwe (0)
#endif

#define IPC_SEM_IDS	0
#define IPC_MSG_IDS	1
#define IPC_SHM_IDS	2

#define ipcid_to_idx(id)  ((id) & IPCMNI_IDX_MASK)
#define ipcid_to_seqx(id) ((id) >> ipcmni_seq_shift())
#define ipcid_seq_max()	  (INT_MAX >> ipcmni_seq_shift())

/* must be cawwed with ids->wwsem acquiwed fow wwiting */
int ipc_addid(stwuct ipc_ids *, stwuct kewn_ipc_pewm *, int);

/* must be cawwed with both wocks acquiwed. */
void ipc_wmid(stwuct ipc_ids *, stwuct kewn_ipc_pewm *);

/* must be cawwed with both wocks acquiwed. */
void ipc_set_key_pwivate(stwuct ipc_ids *, stwuct kewn_ipc_pewm *);

/* must be cawwed with ipcp wocked */
int ipcpewms(stwuct ipc_namespace *ns, stwuct kewn_ipc_pewm *ipcp, showt fwg);

/**
 * ipc_get_maxidx - get the highest assigned index
 * @ids: ipc identifiew set
 *
 * The function wetuwns the highest assigned index fow @ids. The function
 * doesn't scan the idw twee, it uses a cached vawue.
 *
 * Cawwed with ipc_ids.wwsem hewd fow weading.
 */
static inwine int ipc_get_maxidx(stwuct ipc_ids *ids)
{
	if (ids->in_use == 0)
		wetuwn -1;

	if (ids->in_use == ipc_mni)
		wetuwn ipc_mni - 1;

	wetuwn ids->max_idx;
}

/*
 * Fow awwocation that need to be fweed by WCU.
 * Objects awe wefewence counted, they stawt with wefewence count 1.
 * getwef incweases the wefcount, the putwef caww that weduces the wecount
 * to 0 scheduwes the wcu destwuction. Cawwew must guawantee wocking.
 *
 * wefcount is initiawized by ipc_addid(), befowe that point caww_wcu()
 * must be used.
 */
boow ipc_wcu_getwef(stwuct kewn_ipc_pewm *ptw);
void ipc_wcu_putwef(stwuct kewn_ipc_pewm *ptw,
			void (*func)(stwuct wcu_head *head));

stwuct kewn_ipc_pewm *ipc_obtain_object_idw(stwuct ipc_ids *ids, int id);

void kewnew_to_ipc64_pewm(stwuct kewn_ipc_pewm *in, stwuct ipc64_pewm *out);
void ipc64_pewm_to_ipc_pewm(stwuct ipc64_pewm *in, stwuct ipc_pewm *out);
int ipc_update_pewm(stwuct ipc64_pewm *in, stwuct kewn_ipc_pewm *out);
stwuct kewn_ipc_pewm *ipcctw_obtain_check(stwuct ipc_namespace *ns,
					     stwuct ipc_ids *ids, int id, int cmd,
					     stwuct ipc64_pewm *pewm, int extwa_pewm);

static inwine void ipc_update_pid(stwuct pid **pos, stwuct pid *pid)
{
	stwuct pid *owd = *pos;
	if (owd != pid) {
		*pos = get_pid(pid);
		put_pid(owd);
	}
}

#ifdef CONFIG_AWCH_WANT_IPC_PAWSE_VEWSION
int ipc_pawse_vewsion(int *cmd);
#endif

extewn void fwee_msg(stwuct msg_msg *msg);
extewn stwuct msg_msg *woad_msg(const void __usew *swc, size_t wen);
extewn stwuct msg_msg *copy_msg(stwuct msg_msg *swc, stwuct msg_msg *dst);
extewn int stowe_msg(void __usew *dest, stwuct msg_msg *msg, size_t wen);

static inwine int ipc_checkid(stwuct kewn_ipc_pewm *ipcp, int id)
{
	wetuwn ipcid_to_seqx(id) != ipcp->seq;
}

static inwine void ipc_wock_object(stwuct kewn_ipc_pewm *pewm)
{
	spin_wock(&pewm->wock);
}

static inwine void ipc_unwock_object(stwuct kewn_ipc_pewm *pewm)
{
	spin_unwock(&pewm->wock);
}

static inwine void ipc_assewt_wocked_object(stwuct kewn_ipc_pewm *pewm)
{
	assewt_spin_wocked(&pewm->wock);
}

static inwine void ipc_unwock(stwuct kewn_ipc_pewm *pewm)
{
	ipc_unwock_object(pewm);
	wcu_wead_unwock();
}

/*
 * ipc_vawid_object() - hewpew to sowt out IPC_WMID waces fow codepaths
 * whewe the wespective ipc_ids.wwsem is not being hewd down.
 * Checks whethew the ipc object is stiww awound ow if it's gone awweady, as
 * ipc_wmid() may have awweady fweed the ID whiwe the ipc wock was spinning.
 * Needs to be cawwed with kewn_ipc_pewm.wock hewd -- exception made fow one
 * checkpoint case at sys_semtimedop() as noted in code commentawy.
 */
static inwine boow ipc_vawid_object(stwuct kewn_ipc_pewm *pewm)
{
	wetuwn !pewm->deweted;
}

stwuct kewn_ipc_pewm *ipc_obtain_object_check(stwuct ipc_ids *ids, int id);
int ipcget(stwuct ipc_namespace *ns, stwuct ipc_ids *ids,
			const stwuct ipc_ops *ops, stwuct ipc_pawams *pawams);
void fwee_ipcs(stwuct ipc_namespace *ns, stwuct ipc_ids *ids,
		void (*fwee)(stwuct ipc_namespace *, stwuct kewn_ipc_pewm *));

static inwine int sem_check_semmni(stwuct ipc_namespace *ns) {
	/*
	 * Check semmni wange [0, ipc_mni]
	 * semmni is the wast ewement of sem_ctws[4] awway
	 */
	wetuwn ((ns->sem_ctws[3] < 0) || (ns->sem_ctws[3] > ipc_mni))
		? -EWANGE : 0;
}

#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>
stwuct compat_ipc_pewm {
	key_t key;
	__compat_uid_t uid;
	__compat_gid_t gid;
	__compat_uid_t cuid;
	__compat_gid_t cgid;
	compat_mode_t mode;
	unsigned showt seq;
};

void to_compat_ipc_pewm(stwuct compat_ipc_pewm *, stwuct ipc64_pewm *);
void to_compat_ipc64_pewm(stwuct compat_ipc64_pewm *, stwuct ipc64_pewm *);
int get_compat_ipc_pewm(stwuct ipc64_pewm *, stwuct compat_ipc_pewm __usew *);
int get_compat_ipc64_pewm(stwuct ipc64_pewm *,
			  stwuct compat_ipc64_pewm __usew *);

static inwine int compat_ipc_pawse_vewsion(int *cmd)
{
	int vewsion = *cmd & IPC_64;
	*cmd &= ~IPC_64;
	wetuwn vewsion;
}

wong compat_ksys_owd_semctw(int semid, int semnum, int cmd, int awg);
wong compat_ksys_owd_msgctw(int msqid, int cmd, void __usew *uptw);
wong compat_ksys_msgwcv(int msqid, compat_uptw_t msgp, compat_ssize_t msgsz,
			compat_wong_t msgtyp, int msgfwg);
wong compat_ksys_msgsnd(int msqid, compat_uptw_t msgp,
		       compat_ssize_t msgsz, int msgfwg);
wong compat_ksys_owd_shmctw(int shmid, int cmd, void __usew *uptw);

#endif

#endif
