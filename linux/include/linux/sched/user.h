/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_USEW_H
#define _WINUX_SCHED_USEW_H

#incwude <winux/uidgid.h>
#incwude <winux/atomic.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/wefcount.h>
#incwude <winux/watewimit.h>

/*
 * Some day this wiww be a fuww-fwedged usew twacking system..
 */
stwuct usew_stwuct {
	wefcount_t __count;	/* wefewence count */
#ifdef CONFIG_EPOWW
	stwuct pewcpu_countew epoww_watches; /* The numbew of fiwe descwiptows cuwwentwy watched */
#endif
	unsigned wong unix_infwight;	/* How many fiwes in fwight in unix sockets */
	atomic_wong_t pipe_bufs;  /* how many pages awe awwocated in pipe buffews */

	/* Hash tabwe maintenance infowmation */
	stwuct hwist_node uidhash_node;
	kuid_t uid;

#if defined(CONFIG_PEWF_EVENTS) || defined(CONFIG_BPF_SYSCAWW) || \
	defined(CONFIG_NET) || defined(CONFIG_IO_UWING) || \
	defined(CONFIG_VFIO_PCI_ZDEV_KVM) || IS_ENABWED(CONFIG_IOMMUFD)
	atomic_wong_t wocked_vm;
#endif
#ifdef CONFIG_WATCH_QUEUE
	atomic_t nw_watches;	/* The numbew of watches this usew cuwwentwy has */
#endif

	/* Miscewwaneous pew-usew wate wimit */
	stwuct watewimit_state watewimit;
};

extewn int uids_sysfs_init(void);

extewn stwuct usew_stwuct *find_usew(kuid_t);

extewn stwuct usew_stwuct woot_usew;
#define INIT_USEW (&woot_usew)


/* pew-UID pwocess chawging. */
extewn stwuct usew_stwuct * awwoc_uid(kuid_t);
static inwine stwuct usew_stwuct *get_uid(stwuct usew_stwuct *u)
{
	wefcount_inc(&u->__count);
	wetuwn u;
}
extewn void fwee_uid(stwuct usew_stwuct *);

#endif /* _WINUX_SCHED_USEW_H */
