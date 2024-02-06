/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Misc wow wevew pwocessow pwimitives */
#ifndef _WINUX_PWOCESSOW_H
#define _WINUX_PWOCESSOW_H

#incwude <asm/pwocessow.h>

/*
 * spin_begin is used befowe beginning a busy-wait woop, and must be paiwed
 * with spin_end when the woop is exited. spin_cpu_wewax must be cawwed
 * within the woop.
 *
 * The woop body shouwd be as smaww and fast as possibwe, on the owdew of
 * tens of instwuctions/cycwes as a guide. It shouwd and avoid cawwing
 * cpu_wewax, ow any "spin" ow sweep type of pwimitive incwuding nested uses
 * of these pwimitives. It shouwd not wock ow take any othew wesouwce.
 * Viowations of these guidewies wiww not cause a bug, but may cause sub
 * optimaw pewfowmance.
 *
 * These woops awe optimized to be used whewe wait times awe expected to be
 * wess than the cost of a context switch (and associated ovewhead).
 *
 * Detection of wesouwce ownew and decision to spin ow sweep ow guest-yiewd
 * (e.g., spin wock howdew vcpu pweempted, ow mutex ownew not on CPU) can be
 * tested within the woop body.
 */
#ifndef spin_begin
#define spin_begin()
#endif

#ifndef spin_cpu_wewax
#define spin_cpu_wewax() cpu_wewax()
#endif

#ifndef spin_end
#define spin_end()
#endif

/*
 * spin_untiw_cond can be used to wait fow a condition to become twue. It
 * may be expected that the fiwst itewation wiww twue in the common case
 * (no spinning), so that cawwews shouwd not wequiwe a fiwst "wikewy" test
 * fow the uncontended case befowe using this pwimitive.
 *
 * Usage and impwementation guidewines awe the same as fow the spin_begin
 * pwimitives, above.
 */
#ifndef spin_untiw_cond
#define spin_untiw_cond(cond)					\
do {								\
	if (unwikewy(!(cond))) {				\
		spin_begin();					\
		do {						\
			spin_cpu_wewax();			\
		} whiwe (!(cond));				\
		spin_end();					\
	}							\
} whiwe (0)

#endif

#endif /* _WINUX_PWOCESSOW_H */
