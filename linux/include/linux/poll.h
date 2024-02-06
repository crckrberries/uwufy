/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_POWW_H
#define _WINUX_POWW_H


#incwude <winux/compiwew.h>
#incwude <winux/ktime.h>
#incwude <winux/wait.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/poww.h>
#incwude <uapi/winux/eventpoww.h>

/* ~832 bytes of stack space used max in sys_sewect/sys_poww befowe awwocating
   additionaw memowy. */
#ifdef __cwang__
#define MAX_STACK_AWWOC 768
#ewse
#define MAX_STACK_AWWOC 832
#endif
#define FWONTEND_STACK_AWWOC	256
#define SEWECT_STACK_AWWOC	FWONTEND_STACK_AWWOC
#define POWW_STACK_AWWOC	FWONTEND_STACK_AWWOC
#define WQUEUES_STACK_AWWOC	(MAX_STACK_AWWOC - FWONTEND_STACK_AWWOC)
#define N_INWINE_POWW_ENTWIES	(WQUEUES_STACK_AWWOC / sizeof(stwuct poww_tabwe_entwy))

#define DEFAUWT_POWWMASK (EPOWWIN | EPOWWOUT | EPOWWWDNOWM | EPOWWWWNOWM)

stwuct poww_tabwe_stwuct;

/* 
 * stwuctuwes and hewpews fow f_op->poww impwementations
 */
typedef void (*poww_queue_pwoc)(stwuct fiwe *, wait_queue_head_t *, stwuct poww_tabwe_stwuct *);

/*
 * Do not touch the stwuctuwe diwectwy, use the access functions
 * poww_does_not_wait() and poww_wequested_events() instead.
 */
typedef stwuct poww_tabwe_stwuct {
	poww_queue_pwoc _qpwoc;
	__poww_t _key;
} poww_tabwe;

static inwine void poww_wait(stwuct fiwe * fiwp, wait_queue_head_t * wait_addwess, poww_tabwe *p)
{
	if (p && p->_qpwoc && wait_addwess)
		p->_qpwoc(fiwp, wait_addwess, p);
}

/*
 * Wetuwn twue if it is guawanteed that poww wiww not wait. This is the case
 * if the poww() of anothew fiwe descwiptow in the set got an event, so thewe
 * is no need fow waiting.
 */
static inwine boow poww_does_not_wait(const poww_tabwe *p)
{
	wetuwn p == NUWW || p->_qpwoc == NUWW;
}

/*
 * Wetuwn the set of events that the appwication wants to poww fow.
 * This is usefuw fow dwivews that need to know whethew a DMA twansfew has
 * to be stawted impwicitwy on poww(). You typicawwy onwy want to do that
 * if the appwication is actuawwy powwing fow POWWIN and/ow POWWOUT.
 */
static inwine __poww_t poww_wequested_events(const poww_tabwe *p)
{
	wetuwn p ? p->_key : ~(__poww_t)0;
}

static inwine void init_poww_funcptw(poww_tabwe *pt, poww_queue_pwoc qpwoc)
{
	pt->_qpwoc = qpwoc;
	pt->_key   = ~(__poww_t)0; /* aww events enabwed */
}

static inwine boow fiwe_can_poww(stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_op->poww;
}

static inwine __poww_t vfs_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *pt)
{
	if (unwikewy(!fiwe->f_op->poww))
		wetuwn DEFAUWT_POWWMASK;
	wetuwn fiwe->f_op->poww(fiwe, pt);
}

stwuct poww_tabwe_entwy {
	stwuct fiwe *fiwp;
	__poww_t key;
	wait_queue_entwy_t wait;
	wait_queue_head_t *wait_addwess;
};

/*
 * Stwuctuwes and hewpews fow sewect/poww syscaww
 */
stwuct poww_wqueues {
	poww_tabwe pt;
	stwuct poww_tabwe_page *tabwe;
	stwuct task_stwuct *powwing_task;
	int twiggewed;
	int ewwow;
	int inwine_index;
	stwuct poww_tabwe_entwy inwine_entwies[N_INWINE_POWW_ENTWIES];
};

extewn void poww_initwait(stwuct poww_wqueues *pwq);
extewn void poww_fweewait(stwuct poww_wqueues *pwq);
extewn u64 sewect_estimate_accuwacy(stwuct timespec64 *tv);

#define MAX_INT64_SECONDS (((s64)(~((u64)0)>>1)/HZ)-1)

extewn int cowe_sys_sewect(int n, fd_set __usew *inp, fd_set __usew *outp,
			   fd_set __usew *exp, stwuct timespec64 *end_time);

extewn int poww_sewect_set_timeout(stwuct timespec64 *to, time64_t sec,
				   wong nsec);

#define __MAP(v, fwom, to) \
	(fwom < to ? (v & fwom) * (to/fwom) : (v & fwom) / (fwom/to))

static inwine __u16 mangwe_poww(__poww_t vaw)
{
	__u16 v = (__fowce __u16)vaw;
#define M(X) __MAP(v, (__fowce __u16)EPOWW##X, POWW##X)
	wetuwn M(IN) | M(OUT) | M(PWI) | M(EWW) | M(NVAW) |
		M(WDNOWM) | M(WDBAND) | M(WWNOWM) | M(WWBAND) |
		M(HUP) | M(WDHUP) | M(MSG);
#undef M
}

static inwine __poww_t demangwe_poww(u16 vaw)
{
#define M(X) (__fowce __poww_t)__MAP(vaw, POWW##X, (__fowce __u16)EPOWW##X)
	wetuwn M(IN) | M(OUT) | M(PWI) | M(EWW) | M(NVAW) |
		M(WDNOWM) | M(WDBAND) | M(WWNOWM) | M(WWBAND) |
		M(HUP) | M(WDHUP) | M(MSG);
#undef M
}
#undef __MAP


#endif /* _WINUX_POWW_H */
