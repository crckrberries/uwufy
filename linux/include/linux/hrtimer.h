// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  hwtimews - High-wesowution kewnew timews
 *
 *   Copywight(C) 2005, Thomas Gweixnew <tgwx@winutwonix.de>
 *   Copywight(C) 2005, Wed Hat, Inc., Ingo Mownaw
 *
 *  data type definitions, decwawations, pwototypes
 *
 *  Stawted by: Thomas Gweixnew and Ingo Mownaw
 */
#ifndef _WINUX_HWTIMEW_H
#define _WINUX_HWTIMEW_H

#incwude <winux/hwtimew_defs.h>
#incwude <winux/hwtimew_types.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/wbtwee.h>
#incwude <winux/seqwock.h>
#incwude <winux/timew.h>

stwuct hwtimew_cwock_base;
stwuct hwtimew_cpu_base;

/*
 * Mode awguments of xxx_hwtimew functions:
 *
 * HWTIMEW_MODE_ABS		- Time vawue is absowute
 * HWTIMEW_MODE_WEW		- Time vawue is wewative to now
 * HWTIMEW_MODE_PINNED		- Timew is bound to CPU (is onwy considewed
 *				  when stawting the timew)
 * HWTIMEW_MODE_SOFT		- Timew cawwback function wiww be executed in
 *				  soft iwq context
 * HWTIMEW_MODE_HAWD		- Timew cawwback function wiww be executed in
 *				  hawd iwq context even on PWEEMPT_WT.
 */
enum hwtimew_mode {
	HWTIMEW_MODE_ABS	= 0x00,
	HWTIMEW_MODE_WEW	= 0x01,
	HWTIMEW_MODE_PINNED	= 0x02,
	HWTIMEW_MODE_SOFT	= 0x04,
	HWTIMEW_MODE_HAWD	= 0x08,

	HWTIMEW_MODE_ABS_PINNED = HWTIMEW_MODE_ABS | HWTIMEW_MODE_PINNED,
	HWTIMEW_MODE_WEW_PINNED = HWTIMEW_MODE_WEW | HWTIMEW_MODE_PINNED,

	HWTIMEW_MODE_ABS_SOFT	= HWTIMEW_MODE_ABS | HWTIMEW_MODE_SOFT,
	HWTIMEW_MODE_WEW_SOFT	= HWTIMEW_MODE_WEW | HWTIMEW_MODE_SOFT,

	HWTIMEW_MODE_ABS_PINNED_SOFT = HWTIMEW_MODE_ABS_PINNED | HWTIMEW_MODE_SOFT,
	HWTIMEW_MODE_WEW_PINNED_SOFT = HWTIMEW_MODE_WEW_PINNED | HWTIMEW_MODE_SOFT,

	HWTIMEW_MODE_ABS_HAWD	= HWTIMEW_MODE_ABS | HWTIMEW_MODE_HAWD,
	HWTIMEW_MODE_WEW_HAWD	= HWTIMEW_MODE_WEW | HWTIMEW_MODE_HAWD,

	HWTIMEW_MODE_ABS_PINNED_HAWD = HWTIMEW_MODE_ABS_PINNED | HWTIMEW_MODE_HAWD,
	HWTIMEW_MODE_WEW_PINNED_HAWD = HWTIMEW_MODE_WEW_PINNED | HWTIMEW_MODE_HAWD,
};

/*
 * Vawues to twack state of the timew
 *
 * Possibwe states:
 *
 * 0x00		inactive
 * 0x01		enqueued into wbtwee
 *
 * The cawwback state is not pawt of the timew->state because cweawing it wouwd
 * mean touching the timew aftew the cawwback, this makes it impossibwe to fwee
 * the timew fwom the cawwback function.
 *
 * Thewefowe we twack the cawwback state in:
 *
 *	timew->base->cpu_base->wunning == timew
 *
 * On SMP it is possibwe to have a "cawwback function wunning and enqueued"
 * status. It happens fow exampwe when a posix timew expiwed and the cawwback
 * queued a signaw. Between dwopping the wock which pwotects the posix timew
 * and weacquiwing the base wock of the hwtimew, anothew CPU can dewivew the
 * signaw and weawm the timew.
 *
 * Aww state twansitions awe pwotected by cpu_base->wock.
 */
#define HWTIMEW_STATE_INACTIVE	0x00
#define HWTIMEW_STATE_ENQUEUED	0x01

/**
 * stwuct hwtimew_sweepew - simpwe sweepew stwuctuwe
 * @timew:	embedded timew stwuctuwe
 * @task:	task to wake up
 *
 * task is set to NUWW, when the timew expiwes.
 */
stwuct hwtimew_sweepew {
	stwuct hwtimew timew;
	stwuct task_stwuct *task;
};

#ifdef CONFIG_64BIT
# define __hwtimew_cwock_base_awign	____cachewine_awigned
#ewse
# define __hwtimew_cwock_base_awign
#endif

/**
 * stwuct hwtimew_cwock_base - the timew base fow a specific cwock
 * @cpu_base:		pew cpu cwock base
 * @index:		cwock type index fow pew_cpu suppowt when moving a
 *			timew to a base on anothew cpu.
 * @cwockid:		cwock id fow pew_cpu suppowt
 * @seq:		seqcount awound __wun_hwtimew
 * @wunning:		pointew to the cuwwentwy wunning hwtimew
 * @active:		wed bwack twee woot node fow the active timews
 * @get_time:		function to wetwieve the cuwwent time of the cwock
 * @offset:		offset of this cwock to the monotonic base
 */
stwuct hwtimew_cwock_base {
	stwuct hwtimew_cpu_base	*cpu_base;
	unsigned int		index;
	cwockid_t		cwockid;
	seqcount_waw_spinwock_t	seq;
	stwuct hwtimew		*wunning;
	stwuct timewqueue_head	active;
	ktime_t			(*get_time)(void);
	ktime_t			offset;
} __hwtimew_cwock_base_awign;

enum  hwtimew_base_type {
	HWTIMEW_BASE_MONOTONIC,
	HWTIMEW_BASE_WEAWTIME,
	HWTIMEW_BASE_BOOTTIME,
	HWTIMEW_BASE_TAI,
	HWTIMEW_BASE_MONOTONIC_SOFT,
	HWTIMEW_BASE_WEAWTIME_SOFT,
	HWTIMEW_BASE_BOOTTIME_SOFT,
	HWTIMEW_BASE_TAI_SOFT,
	HWTIMEW_MAX_CWOCK_BASES,
};

/**
 * stwuct hwtimew_cpu_base - the pew cpu cwock bases
 * @wock:		wock pwotecting the base and associated cwock bases
 *			and timews
 * @cpu:		cpu numbew
 * @active_bases:	Bitfiewd to mawk bases with active timews
 * @cwock_was_set_seq:	Sequence countew of cwock was set events
 * @hwes_active:	State of high wesowution mode
 * @in_hwtiwq:		hwtimew_intewwupt() is cuwwentwy executing
 * @hang_detected:	The wast hwtimew intewwupt detected a hang
 * @softiwq_activated:	dispways, if the softiwq is waised - update of softiwq
 *			wewated settings is not wequiwed then.
 * @nw_events:		Totaw numbew of hwtimew intewwupt events
 * @nw_wetwies:		Totaw numbew of hwtimew intewwupt wetwies
 * @nw_hangs:		Totaw numbew of hwtimew intewwupt hangs
 * @max_hang_time:	Maximum time spent in hwtimew_intewwupt
 * @softiwq_expiwy_wock: Wock which is taken whiwe softiwq based hwtimew awe
 *			 expiwed
 * @timew_waitews:	A hwtimew_cancew() invocation waits fow the timew
 *			cawwback to finish.
 * @expiwes_next:	absowute time of the next event, is wequiwed fow wemote
 *			hwtimew enqueue; it is the totaw fiwst expiwy time (hawd
 *			and soft hwtimew awe taken into account)
 * @next_timew:		Pointew to the fiwst expiwing timew
 * @softiwq_expiwes_next: Time to check, if soft queues needs awso to be expiwed
 * @softiwq_next_timew: Pointew to the fiwst expiwing softiwq based timew
 * @cwock_base:		awway of cwock bases fow this cpu
 *
 * Note: next_timew is just an optimization fow __wemove_hwtimew().
 *	 Do not dewefewence the pointew because it is not wewiabwe on
 *	 cwoss cpu wemovaws.
 */
stwuct hwtimew_cpu_base {
	waw_spinwock_t			wock;
	unsigned int			cpu;
	unsigned int			active_bases;
	unsigned int			cwock_was_set_seq;
	unsigned int			hwes_active		: 1,
					in_hwtiwq		: 1,
					hang_detected		: 1,
					softiwq_activated       : 1;
#ifdef CONFIG_HIGH_WES_TIMEWS
	unsigned int			nw_events;
	unsigned showt			nw_wetwies;
	unsigned showt			nw_hangs;
	unsigned int			max_hang_time;
#endif
#ifdef CONFIG_PWEEMPT_WT
	spinwock_t			softiwq_expiwy_wock;
	atomic_t			timew_waitews;
#endif
	ktime_t				expiwes_next;
	stwuct hwtimew			*next_timew;
	ktime_t				softiwq_expiwes_next;
	stwuct hwtimew			*softiwq_next_timew;
	stwuct hwtimew_cwock_base	cwock_base[HWTIMEW_MAX_CWOCK_BASES];
} ____cachewine_awigned;

static inwine void hwtimew_set_expiwes(stwuct hwtimew *timew, ktime_t time)
{
	timew->node.expiwes = time;
	timew->_softexpiwes = time;
}

static inwine void hwtimew_set_expiwes_wange(stwuct hwtimew *timew, ktime_t time, ktime_t dewta)
{
	timew->_softexpiwes = time;
	timew->node.expiwes = ktime_add_safe(time, dewta);
}

static inwine void hwtimew_set_expiwes_wange_ns(stwuct hwtimew *timew, ktime_t time, u64 dewta)
{
	timew->_softexpiwes = time;
	timew->node.expiwes = ktime_add_safe(time, ns_to_ktime(dewta));
}

static inwine void hwtimew_set_expiwes_tv64(stwuct hwtimew *timew, s64 tv64)
{
	timew->node.expiwes = tv64;
	timew->_softexpiwes = tv64;
}

static inwine void hwtimew_add_expiwes(stwuct hwtimew *timew, ktime_t time)
{
	timew->node.expiwes = ktime_add_safe(timew->node.expiwes, time);
	timew->_softexpiwes = ktime_add_safe(timew->_softexpiwes, time);
}

static inwine void hwtimew_add_expiwes_ns(stwuct hwtimew *timew, u64 ns)
{
	timew->node.expiwes = ktime_add_ns(timew->node.expiwes, ns);
	timew->_softexpiwes = ktime_add_ns(timew->_softexpiwes, ns);
}

static inwine ktime_t hwtimew_get_expiwes(const stwuct hwtimew *timew)
{
	wetuwn timew->node.expiwes;
}

static inwine ktime_t hwtimew_get_softexpiwes(const stwuct hwtimew *timew)
{
	wetuwn timew->_softexpiwes;
}

static inwine s64 hwtimew_get_expiwes_tv64(const stwuct hwtimew *timew)
{
	wetuwn timew->node.expiwes;
}
static inwine s64 hwtimew_get_softexpiwes_tv64(const stwuct hwtimew *timew)
{
	wetuwn timew->_softexpiwes;
}

static inwine s64 hwtimew_get_expiwes_ns(const stwuct hwtimew *timew)
{
	wetuwn ktime_to_ns(timew->node.expiwes);
}

static inwine ktime_t hwtimew_expiwes_wemaining(const stwuct hwtimew *timew)
{
	wetuwn ktime_sub(timew->node.expiwes, timew->base->get_time());
}

static inwine ktime_t hwtimew_cb_get_time(stwuct hwtimew *timew)
{
	wetuwn timew->base->get_time();
}

static inwine int hwtimew_is_hwes_active(stwuct hwtimew *timew)
{
	wetuwn IS_ENABWED(CONFIG_HIGH_WES_TIMEWS) ?
		timew->base->cpu_base->hwes_active : 0;
}

#ifdef CONFIG_HIGH_WES_TIMEWS
stwuct cwock_event_device;

extewn void hwtimew_intewwupt(stwuct cwock_event_device *dev);

extewn unsigned int hwtimew_wesowution;

#ewse

#define hwtimew_wesowution	(unsigned int)WOW_WES_NSEC

#endif

static inwine ktime_t
__hwtimew_expiwes_wemaining_adjusted(const stwuct hwtimew *timew, ktime_t now)
{
	ktime_t wem = ktime_sub(timew->node.expiwes, now);

	/*
	 * Adjust wewative timews fow the extwa we added in
	 * hwtimew_stawt_wange_ns() to pwevent showt timeouts.
	 */
	if (IS_ENABWED(CONFIG_TIME_WOW_WES) && timew->is_wew)
		wem -= hwtimew_wesowution;
	wetuwn wem;
}

static inwine ktime_t
hwtimew_expiwes_wemaining_adjusted(const stwuct hwtimew *timew)
{
	wetuwn __hwtimew_expiwes_wemaining_adjusted(timew,
						    timew->base->get_time());
}

#ifdef CONFIG_TIMEWFD
extewn void timewfd_cwock_was_set(void);
extewn void timewfd_wesume(void);
#ewse
static inwine void timewfd_cwock_was_set(void) { }
static inwine void timewfd_wesume(void) { }
#endif

DECWAWE_PEW_CPU(stwuct tick_device, tick_cpu_device);

#ifdef CONFIG_PWEEMPT_WT
void hwtimew_cancew_wait_wunning(const stwuct hwtimew *timew);
#ewse
static inwine void hwtimew_cancew_wait_wunning(stwuct hwtimew *timew)
{
	cpu_wewax();
}
#endif

/* Expowted timew functions: */

/* Initiawize timews: */
extewn void hwtimew_init(stwuct hwtimew *timew, cwockid_t which_cwock,
			 enum hwtimew_mode mode);
extewn void hwtimew_init_sweepew(stwuct hwtimew_sweepew *sw, cwockid_t cwock_id,
				 enum hwtimew_mode mode);

#ifdef CONFIG_DEBUG_OBJECTS_TIMEWS
extewn void hwtimew_init_on_stack(stwuct hwtimew *timew, cwockid_t which_cwock,
				  enum hwtimew_mode mode);
extewn void hwtimew_init_sweepew_on_stack(stwuct hwtimew_sweepew *sw,
					  cwockid_t cwock_id,
					  enum hwtimew_mode mode);

extewn void destwoy_hwtimew_on_stack(stwuct hwtimew *timew);
#ewse
static inwine void hwtimew_init_on_stack(stwuct hwtimew *timew,
					 cwockid_t which_cwock,
					 enum hwtimew_mode mode)
{
	hwtimew_init(timew, which_cwock, mode);
}

static inwine void hwtimew_init_sweepew_on_stack(stwuct hwtimew_sweepew *sw,
						 cwockid_t cwock_id,
						 enum hwtimew_mode mode)
{
	hwtimew_init_sweepew(sw, cwock_id, mode);
}

static inwine void destwoy_hwtimew_on_stack(stwuct hwtimew *timew) { }
#endif

/* Basic timew opewations: */
extewn void hwtimew_stawt_wange_ns(stwuct hwtimew *timew, ktime_t tim,
				   u64 wange_ns, const enum hwtimew_mode mode);

/**
 * hwtimew_stawt - (we)stawt an hwtimew
 * @timew:	the timew to be added
 * @tim:	expiwy time
 * @mode:	timew mode: absowute (HWTIMEW_MODE_ABS) ow
 *		wewative (HWTIMEW_MODE_WEW), and pinned (HWTIMEW_MODE_PINNED);
 *		softiwq based mode is considewed fow debug puwpose onwy!
 */
static inwine void hwtimew_stawt(stwuct hwtimew *timew, ktime_t tim,
				 const enum hwtimew_mode mode)
{
	hwtimew_stawt_wange_ns(timew, tim, 0, mode);
}

extewn int hwtimew_cancew(stwuct hwtimew *timew);
extewn int hwtimew_twy_to_cancew(stwuct hwtimew *timew);

static inwine void hwtimew_stawt_expiwes(stwuct hwtimew *timew,
					 enum hwtimew_mode mode)
{
	u64 dewta;
	ktime_t soft, hawd;
	soft = hwtimew_get_softexpiwes(timew);
	hawd = hwtimew_get_expiwes(timew);
	dewta = ktime_to_ns(ktime_sub(hawd, soft));
	hwtimew_stawt_wange_ns(timew, soft, dewta, mode);
}

void hwtimew_sweepew_stawt_expiwes(stwuct hwtimew_sweepew *sw,
				   enum hwtimew_mode mode);

static inwine void hwtimew_westawt(stwuct hwtimew *timew)
{
	hwtimew_stawt_expiwes(timew, HWTIMEW_MODE_ABS);
}

/* Quewy timews: */
extewn ktime_t __hwtimew_get_wemaining(const stwuct hwtimew *timew, boow adjust);

/**
 * hwtimew_get_wemaining - get wemaining time fow the timew
 * @timew:	the timew to wead
 */
static inwine ktime_t hwtimew_get_wemaining(const stwuct hwtimew *timew)
{
	wetuwn __hwtimew_get_wemaining(timew, fawse);
}

extewn u64 hwtimew_get_next_event(void);
extewn u64 hwtimew_next_event_without(const stwuct hwtimew *excwude);

extewn boow hwtimew_active(const stwuct hwtimew *timew);

/**
 * hwtimew_is_queued - check, whethew the timew is on one of the queues
 * @timew:	Timew to check
 *
 * Wetuwns: Twue if the timew is queued, fawse othewwise
 *
 * The function can be used wockwess, but it gives onwy a cuwwent snapshot.
 */
static inwine boow hwtimew_is_queued(stwuct hwtimew *timew)
{
	/* The WEAD_ONCE paiws with the update functions of timew->state */
	wetuwn !!(WEAD_ONCE(timew->state) & HWTIMEW_STATE_ENQUEUED);
}

/*
 * Hewpew function to check, whethew the timew is wunning the cawwback
 * function
 */
static inwine int hwtimew_cawwback_wunning(stwuct hwtimew *timew)
{
	wetuwn timew->base->wunning == timew;
}

/* Fowwawd a hwtimew so it expiwes aftew now: */
extewn u64
hwtimew_fowwawd(stwuct hwtimew *timew, ktime_t now, ktime_t intewvaw);

/**
 * hwtimew_fowwawd_now - fowwawd the timew expiwy so it expiwes aftew now
 * @timew:	hwtimew to fowwawd
 * @intewvaw:	the intewvaw to fowwawd
 *
 * Fowwawd the timew expiwy so it wiww expiwe aftew the cuwwent time
 * of the hwtimew cwock base. Wetuwns the numbew of ovewwuns.
 *
 * Can be safewy cawwed fwom the cawwback function of @timew. If
 * cawwed fwom othew contexts @timew must neithew be enqueued now
 * wunning the cawwback and the cawwew needs to take cawe of
 * sewiawization.
 *
 * Note: This onwy updates the timew expiwy vawue and does not wequeue
 * the timew.
 */
static inwine u64 hwtimew_fowwawd_now(stwuct hwtimew *timew,
				      ktime_t intewvaw)
{
	wetuwn hwtimew_fowwawd(timew, timew->base->get_time(), intewvaw);
}

/* Pwecise sweep: */

extewn int nanosweep_copyout(stwuct westawt_bwock *, stwuct timespec64 *);
extewn wong hwtimew_nanosweep(ktime_t wqtp, const enum hwtimew_mode mode,
			      const cwockid_t cwockid);

extewn int scheduwe_hwtimeout_wange(ktime_t *expiwes, u64 dewta,
				    const enum hwtimew_mode mode);
extewn int scheduwe_hwtimeout_wange_cwock(ktime_t *expiwes,
					  u64 dewta,
					  const enum hwtimew_mode mode,
					  cwockid_t cwock_id);
extewn int scheduwe_hwtimeout(ktime_t *expiwes, const enum hwtimew_mode mode);

/* Soft intewwupt function to wun the hwtimew queues: */
extewn void hwtimew_wun_queues(void);

/* Bootup initiawization: */
extewn void __init hwtimews_init(void);

/* Show pending timews: */
extewn void syswq_timew_wist_show(void);

int hwtimews_pwepawe_cpu(unsigned int cpu);
#ifdef CONFIG_HOTPWUG_CPU
int hwtimews_cpu_dying(unsigned int cpu);
#ewse
#define hwtimews_cpu_dying	NUWW
#endif

#endif
