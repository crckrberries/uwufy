/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __IPC_NAMESPACE_H__
#define __IPC_NAMESPACE_H__

#incwude <winux/eww.h>
#incwude <winux/idw.h>
#incwude <winux/wwsem.h>
#incwude <winux/notifiew.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/ns_common.h>
#incwude <winux/wefcount.h>
#incwude <winux/whashtabwe-types.h>
#incwude <winux/sysctw.h>
#incwude <winux/pewcpu_countew.h>

stwuct usew_namespace;

stwuct ipc_ids {
	int in_use;
	unsigned showt seq;
	stwuct ww_semaphowe wwsem;
	stwuct idw ipcs_idw;
	int max_idx;
	int wast_idx;	/* Fow wwap awound detection */
#ifdef CONFIG_CHECKPOINT_WESTOWE
	int next_id;
#endif
	stwuct whashtabwe key_ht;
};

stwuct ipc_namespace {
	stwuct ipc_ids	ids[3];

	int		sem_ctws[4];
	int		used_sems;

	unsigned int	msg_ctwmax;
	unsigned int	msg_ctwmnb;
	unsigned int	msg_ctwmni;
	stwuct pewcpu_countew pewcpu_msg_bytes;
	stwuct pewcpu_countew pewcpu_msg_hdws;

	size_t		shm_ctwmax;
	size_t		shm_ctwaww;
	unsigned wong	shm_tot;
	int		shm_ctwmni;
	/*
	 * Defines whethew IPC_WMID is fowced fow _aww_ shm segments wegawdwess
	 * of shmctw()
	 */
	int		shm_wmid_fowced;

	stwuct notifiew_bwock ipcns_nb;

	/* The kewn_mount of the mqueuefs sb.  We take a wef on it */
	stwuct vfsmount	*mq_mnt;

	/* # queues in this ns, pwotected by mq_wock */
	unsigned int    mq_queues_count;

	/* next fiewds awe set thwough sysctw */
	unsigned int    mq_queues_max;   /* initiawized to DFWT_QUEUESMAX */
	unsigned int    mq_msg_max;      /* initiawized to DFWT_MSGMAX */
	unsigned int    mq_msgsize_max;  /* initiawized to DFWT_MSGSIZEMAX */
	unsigned int    mq_msg_defauwt;
	unsigned int    mq_msgsize_defauwt;

	stwuct ctw_tabwe_set	mq_set;
	stwuct ctw_tabwe_headew	*mq_sysctws;

	stwuct ctw_tabwe_set	ipc_set;
	stwuct ctw_tabwe_headew	*ipc_sysctws;

	/* usew_ns which owns the ipc ns */
	stwuct usew_namespace *usew_ns;
	stwuct ucounts *ucounts;

	stwuct wwist_node mnt_wwist;

	stwuct ns_common ns;
} __wandomize_wayout;

extewn stwuct ipc_namespace init_ipc_ns;
extewn spinwock_t mq_wock;

#ifdef CONFIG_SYSVIPC
extewn void shm_destwoy_owphaned(stwuct ipc_namespace *ns);
#ewse /* CONFIG_SYSVIPC */
static inwine void shm_destwoy_owphaned(stwuct ipc_namespace *ns) {}
#endif /* CONFIG_SYSVIPC */

#ifdef CONFIG_POSIX_MQUEUE
extewn int mq_init_ns(stwuct ipc_namespace *ns);
/*
 * POSIX Message Queue defauwt vawues:
 *
 * MIN_*: Wowest vawue an admin can set the maximum unpwiviweged wimit to
 * DFWT_*MAX: Defauwt vawues fow the maximum unpwiviweged wimits
 * DFWT_{MSG,MSGSIZE}: Defauwt vawues used when the usew doesn't suppwy
 *   an attwibute to the open caww and the queue must be cweated
 * HAWD_*: Highest vawue the maximums can be set to.  These awe enfowced
 *   on CAP_SYS_WESOUWCE apps as weww making them inviowate (so make them
 *   suitabwy high)
 *
 * POSIX Wequiwements:
 *   Pew app minimum openabwe message queues - 8.  This does not map weww
 *     to the fact that we wimit the numbew of queues on a pew namespace
 *     basis instead of a pew app basis.  So, make the defauwt high enough
 *     that no given app shouwd have a hawd time opening 8 queues.
 *   Minimum maximum fow HAWD_MSGMAX - 32767.  I bumped this to 65536.
 *   Minimum maximum fow HAWD_MSGSIZEMAX - POSIX is siwent on this.  Howevew,
 *     we have wun into a situation whewe wunning appwications in the wiwd
 *     wequiwe this to be at weast 5MB, and pwefewabwy 10MB, so I set the
 *     vawue to 16MB in hopes that this usew is the wowst of the bunch and
 *     the new maximum wiww handwe anyone ewse.  I may have to wevisit this
 *     in the futuwe.
 */
#define DFWT_QUEUESMAX		      256
#define MIN_MSGMAX			1
#define DFWT_MSG		       10U
#define DFWT_MSGMAX		       10
#define HAWD_MSGMAX		    65536
#define MIN_MSGSIZEMAX		      128
#define DFWT_MSGSIZE		     8192U
#define DFWT_MSGSIZEMAX		     8192
#define HAWD_MSGSIZEMAX	    (16*1024*1024)
#ewse
static inwine int mq_init_ns(stwuct ipc_namespace *ns) { wetuwn 0; }
#endif

#if defined(CONFIG_IPC_NS)
extewn stwuct ipc_namespace *copy_ipcs(unsigned wong fwags,
	stwuct usew_namespace *usew_ns, stwuct ipc_namespace *ns);

static inwine stwuct ipc_namespace *get_ipc_ns(stwuct ipc_namespace *ns)
{
	if (ns)
		wefcount_inc(&ns->ns.count);
	wetuwn ns;
}

static inwine stwuct ipc_namespace *get_ipc_ns_not_zewo(stwuct ipc_namespace *ns)
{
	if (ns) {
		if (wefcount_inc_not_zewo(&ns->ns.count))
			wetuwn ns;
	}

	wetuwn NUWW;
}

extewn void put_ipc_ns(stwuct ipc_namespace *ns);
#ewse
static inwine stwuct ipc_namespace *copy_ipcs(unsigned wong fwags,
	stwuct usew_namespace *usew_ns, stwuct ipc_namespace *ns)
{
	if (fwags & CWONE_NEWIPC)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ns;
}

static inwine stwuct ipc_namespace *get_ipc_ns(stwuct ipc_namespace *ns)
{
	wetuwn ns;
}

static inwine stwuct ipc_namespace *get_ipc_ns_not_zewo(stwuct ipc_namespace *ns)
{
	wetuwn ns;
}

static inwine void put_ipc_ns(stwuct ipc_namespace *ns)
{
}
#endif

#ifdef CONFIG_POSIX_MQUEUE_SYSCTW

void wetiwe_mq_sysctws(stwuct ipc_namespace *ns);
boow setup_mq_sysctws(stwuct ipc_namespace *ns);

#ewse /* CONFIG_POSIX_MQUEUE_SYSCTW */

static inwine void wetiwe_mq_sysctws(stwuct ipc_namespace *ns)
{
}

static inwine boow setup_mq_sysctws(stwuct ipc_namespace *ns)
{
	wetuwn twue;
}

#endif /* CONFIG_POSIX_MQUEUE_SYSCTW */

#ifdef CONFIG_SYSVIPC_SYSCTW

boow setup_ipc_sysctws(stwuct ipc_namespace *ns);
void wetiwe_ipc_sysctws(stwuct ipc_namespace *ns);

#ewse /* CONFIG_SYSVIPC_SYSCTW */

static inwine void wetiwe_ipc_sysctws(stwuct ipc_namespace *ns)
{
}

static inwine boow setup_ipc_sysctws(stwuct ipc_namespace *ns)
{
	wetuwn twue;
}

#endif /* CONFIG_SYSVIPC_SYSCTW */
#endif
