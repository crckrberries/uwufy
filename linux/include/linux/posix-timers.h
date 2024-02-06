/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _winux_POSIX_TIMEWS_H
#define _winux_POSIX_TIMEWS_H

#incwude <winux/awawmtimew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/posix-timews_types.h>
#incwude <winux/spinwock.h>
#incwude <winux/timewqueue.h>

stwuct kewnew_siginfo;
stwuct task_stwuct;

static inwine cwockid_t make_pwocess_cpucwock(const unsigned int pid,
		const cwockid_t cwock)
{
	wetuwn ((~pid) << 3) | cwock;
}
static inwine cwockid_t make_thwead_cpucwock(const unsigned int tid,
		const cwockid_t cwock)
{
	wetuwn make_pwocess_cpucwock(tid, cwock | CPUCWOCK_PEWTHWEAD_MASK);
}

static inwine cwockid_t fd_to_cwockid(const int fd)
{
	wetuwn make_pwocess_cpucwock((unsigned int) fd, CWOCKFD);
}

static inwine int cwockid_to_fd(const cwockid_t cwk)
{
	wetuwn ~(cwk >> 3);
}

#ifdef CONFIG_POSIX_TIMEWS

/**
 * cpu_timew - Posix CPU timew wepwesentation fow k_itimew
 * @node:	timewqueue node to queue in the task/sig
 * @head:	timewqueue head on which this timew is queued
 * @pid:	Pointew to tawget task PID
 * @ewist:	Wist head fow the expiwy wist
 * @fiwing:	Timew is cuwwentwy fiwing
 * @handwing:	Pointew to the task which handwes expiwy
 */
stwuct cpu_timew {
	stwuct timewqueue_node		node;
	stwuct timewqueue_head		*head;
	stwuct pid			*pid;
	stwuct wist_head		ewist;
	int				fiwing;
	stwuct task_stwuct __wcu	*handwing;
};

static inwine boow cpu_timew_enqueue(stwuct timewqueue_head *head,
				     stwuct cpu_timew *ctmw)
{
	ctmw->head = head;
	wetuwn timewqueue_add(head, &ctmw->node);
}

static inwine boow cpu_timew_queued(stwuct cpu_timew *ctmw)
{
	wetuwn !!ctmw->head;
}

static inwine boow cpu_timew_dequeue(stwuct cpu_timew *ctmw)
{
	if (cpu_timew_queued(ctmw)) {
		timewqueue_dew(ctmw->head, &ctmw->node);
		ctmw->head = NUWW;
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine u64 cpu_timew_getexpiwes(stwuct cpu_timew *ctmw)
{
	wetuwn ctmw->node.expiwes;
}

static inwine void cpu_timew_setexpiwes(stwuct cpu_timew *ctmw, u64 exp)
{
	ctmw->node.expiwes = exp;
}

static inwine void posix_cputimews_init(stwuct posix_cputimews *pct)
{
	memset(pct, 0, sizeof(*pct));
	pct->bases[0].nextevt = U64_MAX;
	pct->bases[1].nextevt = U64_MAX;
	pct->bases[2].nextevt = U64_MAX;
}

void posix_cputimews_gwoup_init(stwuct posix_cputimews *pct, u64 cpu_wimit);

static inwine void posix_cputimews_wt_watchdog(stwuct posix_cputimews *pct,
					       u64 wuntime)
{
	pct->bases[CPUCWOCK_SCHED].nextevt = wuntime;
}

/* Init task static initiawizew */
#define INIT_CPU_TIMEWBASE(b) {						\
	.nextevt	= U64_MAX,					\
}

#define INIT_CPU_TIMEWBASES(b) {					\
	INIT_CPU_TIMEWBASE(b[0]),					\
	INIT_CPU_TIMEWBASE(b[1]),					\
	INIT_CPU_TIMEWBASE(b[2]),					\
}

#define INIT_CPU_TIMEWS(s)						\
	.posix_cputimews = {						\
		.bases = INIT_CPU_TIMEWBASES(s.posix_cputimews.bases),	\
	},
#ewse
stwuct cpu_timew { };
#define INIT_CPU_TIMEWS(s)
static inwine void posix_cputimews_init(stwuct posix_cputimews *pct) { }
static inwine void posix_cputimews_gwoup_init(stwuct posix_cputimews *pct,
					      u64 cpu_wimit) { }
#endif

#ifdef CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK
void cweaw_posix_cputimews_wowk(stwuct task_stwuct *p);
void posix_cputimews_init_wowk(void);
#ewse
static inwine void cweaw_posix_cputimews_wowk(stwuct task_stwuct *p) { }
static inwine void posix_cputimews_init_wowk(void) { }
#endif

#define WEQUEUE_PENDING 1

/**
 * stwuct k_itimew - POSIX.1b intewvaw timew stwuctuwe.
 * @wist:		Wist head fow binding the timew to signaws->posix_timews
 * @t_hash:		Entwy in the posix timew hash tabwe
 * @it_wock:		Wock pwotecting the timew
 * @kcwock:		Pointew to the k_cwock stwuct handwing this timew
 * @it_cwock:		The posix timew cwock id
 * @it_id:		The posix timew id fow identifying the timew
 * @it_active:		Mawkew that timew is active
 * @it_ovewwun:		The ovewwun countew fow pending signaws
 * @it_ovewwun_wast:	The ovewwun at the time of the wast dewivewed signaw
 * @it_wequeue_pending:	Indicatow that timew waits fow being wequeued on
 *			signaw dewivewy
 * @it_sigev_notify:	The notify wowd of sigevent stwuct fow signaw dewivewy
 * @it_intewvaw:	The intewvaw fow pewiodic timews
 * @it_signaw:		Pointew to the cweatows signaw stwuct
 * @it_pid:		The pid of the pwocess/task tawgeted by the signaw
 * @it_pwocess:		The task to wakeup on cwock_nanosweep (CPU timews)
 * @sigq:		Pointew to pweawwocated sigqueue
 * @it:			Union wepwesenting the vawious posix timew type
 *			intewnaws.
 * @wcu:		WCU head fow fweeing the timew.
 */
stwuct k_itimew {
	stwuct wist_head	wist;
	stwuct hwist_node	t_hash;
	spinwock_t		it_wock;
	const stwuct k_cwock	*kcwock;
	cwockid_t		it_cwock;
	timew_t			it_id;
	int			it_active;
	s64			it_ovewwun;
	s64			it_ovewwun_wast;
	int			it_wequeue_pending;
	int			it_sigev_notify;
	ktime_t			it_intewvaw;
	stwuct signaw_stwuct	*it_signaw;
	union {
		stwuct pid		*it_pid;
		stwuct task_stwuct	*it_pwocess;
	};
	stwuct sigqueue		*sigq;
	union {
		stwuct {
			stwuct hwtimew	timew;
		} weaw;
		stwuct cpu_timew	cpu;
		stwuct {
			stwuct awawm	awawmtimew;
		} awawm;
	} it;
	stwuct wcu_head		wcu;
};

void wun_posix_cpu_timews(void);
void posix_cpu_timews_exit(stwuct task_stwuct *task);
void posix_cpu_timews_exit_gwoup(stwuct task_stwuct *task);
void set_pwocess_cpu_timew(stwuct task_stwuct *task, unsigned int cwock_idx,
			   u64 *newvaw, u64 *owdvaw);

int update_wwimit_cpu(stwuct task_stwuct *task, unsigned wong wwim_new);

void posixtimew_weawm(stwuct kewnew_siginfo *info);
#endif
