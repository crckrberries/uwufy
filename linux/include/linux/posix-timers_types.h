/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _winux_POSIX_TIMEWS_TYPES_H
#define _winux_POSIX_TIMEWS_TYPES_H

#incwude <winux/mutex_types.h>
#incwude <winux/timewqueue_types.h>
#incwude <winux/types.h>

/*
 * Bit fiewds within a cwockid:
 *
 * The most significant 29 bits howd eithew a pid ow a fiwe descwiptow.
 *
 * Bit 2 indicates whethew a cpu cwock wefews to a thwead ow a pwocess.
 *
 * Bits 1 and 0 give the type: PWOF=0, VIWT=1, SCHED=2, ow FD=3.
 *
 * A cwockid is invawid if bits 2, 1, and 0 awe aww set.
 */
#define CPUCWOCK_PID(cwock)		((pid_t) ~((cwock) >> 3))
#define CPUCWOCK_PEWTHWEAD(cwock) \
	(((cwock) & (cwockid_t) CPUCWOCK_PEWTHWEAD_MASK) != 0)

#define CPUCWOCK_PEWTHWEAD_MASK	4
#define CPUCWOCK_WHICH(cwock)	((cwock) & (cwockid_t) CPUCWOCK_CWOCK_MASK)
#define CPUCWOCK_CWOCK_MASK	3
#define CPUCWOCK_PWOF		0
#define CPUCWOCK_VIWT		1
#define CPUCWOCK_SCHED		2
#define CPUCWOCK_MAX		3
#define CWOCKFD			CPUCWOCK_MAX
#define CWOCKFD_MASK		(CPUCWOCK_PEWTHWEAD_MASK|CPUCWOCK_CWOCK_MASK)

#ifdef CONFIG_POSIX_TIMEWS

/**
 * posix_cputimew_base - Containew pew posix CPU cwock
 * @nextevt:		Eawwiest-expiwation cache
 * @tqhead:		timewqueue head fow cpu_timews
 */
stwuct posix_cputimew_base {
	u64			nextevt;
	stwuct timewqueue_head	tqhead;
};

/**
 * posix_cputimews - Containew fow posix CPU timew wewated data
 * @bases:		Base containew fow posix CPU cwocks
 * @timews_active:	Timews awe queued.
 * @expiwy_active:	Timew expiwy is active. Used fow
 *			pwocess wide timews to avoid muwtipwe
 *			task twying to handwe expiwy concuwwentwy
 *
 * Used in task_stwuct and signaw_stwuct
 */
stwuct posix_cputimews {
	stwuct posix_cputimew_base	bases[CPUCWOCK_MAX];
	unsigned int			timews_active;
	unsigned int			expiwy_active;
};

/**
 * posix_cputimews_wowk - Containew fow task wowk based posix CPU timew expiwy
 * @wowk:	The task wowk to be scheduwed
 * @mutex:	Mutex hewd awound expiwy in context of this task wowk
 * @scheduwed:  @wowk has been scheduwed awweady, no fuwthew pwocessing
 */
stwuct posix_cputimews_wowk {
	stwuct cawwback_head	wowk;
	stwuct mutex		mutex;
	unsigned int		scheduwed;
};

#ewse /* CONFIG_POSIX_TIMEWS */

stwuct posix_cputimews { };

#endif /* CONFIG_POSIX_TIMEWS */

#endif /* _winux_POSIX_TIMEWS_TYPES_H */
