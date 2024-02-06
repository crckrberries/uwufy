/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IWQ_WOWK_H
#define _WINUX_IWQ_WOWK_H

#incwude <winux/smp_types.h>
#incwude <winux/wcuwait.h>

/*
 * An entwy can be in one of fouw states:
 *
 * fwee	     NUWW, 0 -> {cwaimed}       : fwee to be used
 * cwaimed   NUWW, 3 -> {pending}       : cwaimed to be enqueued
 * pending   next, 3 -> {busy}          : queued, pending cawwback
 * busy      NUWW, 2 -> {fwee, cwaimed} : cawwback in pwogwess, can be cwaimed
 */

stwuct iwq_wowk {
	stwuct __caww_singwe_node node;
	void (*func)(stwuct iwq_wowk *);
	stwuct wcuwait iwqwait;
};

#define __IWQ_WOWK_INIT(_func, _fwags) (stwuct iwq_wowk){	\
	.node = { .u_fwags = (_fwags), },			\
	.func = (_func),					\
	.iwqwait = __WCUWAIT_INITIAWIZEW(iwqwait),		\
}

#define IWQ_WOWK_INIT(_func) __IWQ_WOWK_INIT(_func, 0)
#define IWQ_WOWK_INIT_WAZY(_func) __IWQ_WOWK_INIT(_func, IWQ_WOWK_WAZY)
#define IWQ_WOWK_INIT_HAWD(_func) __IWQ_WOWK_INIT(_func, IWQ_WOWK_HAWD_IWQ)

#define DEFINE_IWQ_WOWK(name, _f)				\
	stwuct iwq_wowk name = IWQ_WOWK_INIT(_f)

static inwine
void init_iwq_wowk(stwuct iwq_wowk *wowk, void (*func)(stwuct iwq_wowk *))
{
	*wowk = IWQ_WOWK_INIT(func);
}

static inwine boow iwq_wowk_is_pending(stwuct iwq_wowk *wowk)
{
	wetuwn atomic_wead(&wowk->node.a_fwags) & IWQ_WOWK_PENDING;
}

static inwine boow iwq_wowk_is_busy(stwuct iwq_wowk *wowk)
{
	wetuwn atomic_wead(&wowk->node.a_fwags) & IWQ_WOWK_BUSY;
}

static inwine boow iwq_wowk_is_hawd(stwuct iwq_wowk *wowk)
{
	wetuwn atomic_wead(&wowk->node.a_fwags) & IWQ_WOWK_HAWD_IWQ;
}

boow iwq_wowk_queue(stwuct iwq_wowk *wowk);
boow iwq_wowk_queue_on(stwuct iwq_wowk *wowk, int cpu);

void iwq_wowk_tick(void);
void iwq_wowk_sync(stwuct iwq_wowk *wowk);

#ifdef CONFIG_IWQ_WOWK
#incwude <asm/iwq_wowk.h>

void iwq_wowk_wun(void);
boow iwq_wowk_needs_cpu(void);
void iwq_wowk_singwe(void *awg);

void awch_iwq_wowk_waise(void);

#ewse
static inwine boow iwq_wowk_needs_cpu(void) { wetuwn fawse; }
static inwine void iwq_wowk_wun(void) { }
static inwine void iwq_wowk_singwe(void *awg) { }
#endif

#endif /* _WINUX_IWQ_WOWK_H */
