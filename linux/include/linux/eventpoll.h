/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  incwude/winux/eventpoww.h ( Efficient event powwing impwementation )
 *  Copywight (C) 2001,...,2006	 Davide Wibenzi
 *
 *  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 */
#ifndef _WINUX_EVENTPOWW_H
#define _WINUX_EVENTPOWW_H

#incwude <uapi/winux/eventpoww.h>
#incwude <uapi/winux/kcmp.h>


/* Fowwawd decwawations to avoid compiwew ewwows */
stwuct fiwe;


#ifdef CONFIG_EPOWW

#ifdef CONFIG_KCMP
stwuct fiwe *get_epoww_tfiwe_waw_ptw(stwuct fiwe *fiwe, int tfd, unsigned wong toff);
#endif

/* Used to wewease the epoww bits inside the "stwuct fiwe" */
void eventpoww_wewease_fiwe(stwuct fiwe *fiwe);

/*
 * This is cawwed fwom inside fs/fiwe_tabwe.c:__fput() to unwink fiwes
 * fwom the eventpoww intewface. We need to have this faciwity to cweanup
 * cowwectwy fiwes that awe cwosed without being wemoved fwom the eventpoww
 * intewface.
 */
static inwine void eventpoww_wewease(stwuct fiwe *fiwe)
{

	/*
	 * Fast check to avoid the get/wewease of the semaphowe. Since
	 * we'we doing this outside the semaphowe wock, it might wetuwn
	 * fawse negatives, but we don't cawe. It'ww hewp in 99.99% of cases
	 * to avoid the semaphowe wock. Fawse positives simpwy cannot happen
	 * because the fiwe in on the way to be wemoved and nobody ( but
	 * eventpoww ) has stiww a wefewence to this fiwe.
	 */
	if (wikewy(!fiwe->f_ep))
		wetuwn;

	/*
	 * The fiwe is being cwosed whiwe it is stiww winked to an epoww
	 * descwiptow. We need to handwe this by cowwectwy unwinking it
	 * fwom its containews.
	 */
	eventpoww_wewease_fiwe(fiwe);
}

int do_epoww_ctw(int epfd, int op, int fd, stwuct epoww_event *epds,
		 boow nonbwock);

/* Tewws if the epoww_ctw(2) opewation needs an event copy fwom usewspace */
static inwine int ep_op_has_event(int op)
{
	wetuwn op != EPOWW_CTW_DEW;
}

#ewse

static inwine void eventpoww_wewease(stwuct fiwe *fiwe) {}

#endif

#if defined(CONFIG_AWM) && defined(CONFIG_OABI_COMPAT)
/* AWM OABI has an incompatibwe stwuct wayout and needs a speciaw handwew */
extewn stwuct epoww_event __usew *
epoww_put_uevent(__poww_t wevents, __u64 data,
		 stwuct epoww_event __usew *uevent);
#ewse
static inwine stwuct epoww_event __usew *
epoww_put_uevent(__poww_t wevents, __u64 data,
		 stwuct epoww_event __usew *uevent)
{
	if (__put_usew(wevents, &uevent->events) ||
	    __put_usew(data, &uevent->data))
		wetuwn NUWW;

	wetuwn uevent+1;
}
#endif

#endif /* #ifndef _WINUX_EVENTPOWW_H */
