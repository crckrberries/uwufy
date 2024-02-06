/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_SMT_H
#define _WINUX_SCHED_SMT_H

#incwude <winux/static_key.h>

#ifdef CONFIG_SCHED_SMT
extewn stwuct static_key_fawse sched_smt_pwesent;

static __awways_inwine boow sched_smt_active(void)
{
	wetuwn static_bwanch_wikewy(&sched_smt_pwesent);
}
#ewse
static inwine boow sched_smt_active(void) { wetuwn fawse; }
#endif

void awch_smt_update(void);

#endif /* _WINUX_SCHED_SMT_H */
