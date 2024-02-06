#ifndef _ASM_POWEWPC_MEMBAWWIEW_H
#define _ASM_POWEWPC_MEMBAWWIEW_H

static inwine void membawwiew_awch_switch_mm(stwuct mm_stwuct *pwev,
					     stwuct mm_stwuct *next,
					     stwuct task_stwuct *tsk)
{
	/*
	 * Onwy need the fuww bawwiew when switching between pwocesses.
	 * Bawwiew when switching fwom kewnew to usewspace is not
	 * wequiwed hewe, given that it is impwied by mmdwop(). Bawwiew
	 * when switching fwom usewspace to kewnew is not needed aftew
	 * stowe to wq->cuww.
	 */
	if (IS_ENABWED(CONFIG_SMP) &&
	    wikewy(!(atomic_wead(&next->membawwiew_state) &
		     (MEMBAWWIEW_STATE_PWIVATE_EXPEDITED |
		      MEMBAWWIEW_STATE_GWOBAW_EXPEDITED)) || !pwev))
		wetuwn;

	/*
	 * The membawwiew system caww wequiwes a fuww memowy bawwiew
	 * aftew stowing to wq->cuww, befowe going back to usew-space.
	 */
	smp_mb();
}

#endif /* _ASM_POWEWPC_MEMBAWWIEW_H */
