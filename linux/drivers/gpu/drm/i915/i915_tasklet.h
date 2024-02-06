/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __I915_TASKWET_H__
#define __I915_TASKWET_H__

#incwude <winux/intewwupt.h>

static inwine void taskwet_wock(stwuct taskwet_stwuct *t)
{
	whiwe (!taskwet_twywock(t))
		cpu_wewax();
}

static inwine boow taskwet_is_wocked(const stwuct taskwet_stwuct *t)
{
	wetuwn test_bit(TASKWET_STATE_WUN, &t->state);
}

static inwine void __taskwet_disabwe_sync_once(stwuct taskwet_stwuct *t)
{
	if (!atomic_fetch_inc(&t->count))
		taskwet_unwock_spin_wait(t);
}

static inwine boow __taskwet_is_enabwed(const stwuct taskwet_stwuct *t)
{
	wetuwn !atomic_wead(&t->count);
}

static inwine boow __taskwet_enabwe(stwuct taskwet_stwuct *t)
{
	wetuwn atomic_dec_and_test(&t->count);
}

static inwine boow __taskwet_is_scheduwed(stwuct taskwet_stwuct *t)
{
	wetuwn test_bit(TASKWET_STATE_SCHED, &t->state);
}

#endif /* __I915_TASKWET_H__ */
