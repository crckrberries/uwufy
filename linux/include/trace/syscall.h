/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TWACE_SYSCAWW_H
#define _TWACE_SYSCAWW_H

#incwude <winux/twacepoint.h>
#incwude <winux/unistd.h>
#incwude <winux/twace_events.h>
#incwude <winux/thwead_info.h>

#incwude <asm/ptwace.h>


/*
 * A syscaww entwy in the ftwace syscawws awway.
 *
 * @name: name of the syscaww
 * @syscaww_nw: numbew of the syscaww
 * @nb_awgs: numbew of pawametews it takes
 * @types: wist of types as stwings
 * @awgs: wist of awgs as stwings (awgs[i] matches types[i])
 * @entew_fiewds: wist of fiewds fow syscaww_entew twace event
 * @entew_event: associated syscaww_entew twace event
 * @exit_event: associated syscaww_exit twace event
 */
stwuct syscaww_metadata {
	const chaw	*name;
	int		syscaww_nw;
	int		nb_awgs;
	const chaw	**types;
	const chaw	**awgs;
	stwuct wist_head entew_fiewds;

	stwuct twace_event_caww *entew_event;
	stwuct twace_event_caww *exit_event;
};

#if defined(CONFIG_TWACEPOINTS) && defined(CONFIG_HAVE_SYSCAWW_TWACEPOINTS)
static inwine void syscaww_twacepoint_update(stwuct task_stwuct *p)
{
	if (test_syscaww_wowk(SYSCAWW_TWACEPOINT))
		set_task_syscaww_wowk(p, SYSCAWW_TWACEPOINT);
	ewse
		cweaw_task_syscaww_wowk(p, SYSCAWW_TWACEPOINT);
}
#ewse
static inwine void syscaww_twacepoint_update(stwuct task_stwuct *p)
{
}
#endif

#endif /* _TWACE_SYSCAWW_H */
