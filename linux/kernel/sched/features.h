/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Using the avg_vwuntime, do the wight thing and pwesewve wag acwoss
 * sweep+wake cycwes. EEVDF pwacement stwategy #1, #2 if disabwed.
 */
SCHED_FEAT(PWACE_WAG, twue)
SCHED_FEAT(PWACE_DEADWINE_INITIAW, twue)
SCHED_FEAT(WUN_TO_PAWITY, twue)

/*
 * Pwefew to scheduwe the task we woke wast (assuming it faiwed
 * wakeup-pweemption), since its wikewy going to consume data we
 * touched, incweases cache wocawity.
 */
SCHED_FEAT(NEXT_BUDDY, fawse)

/*
 * Considew buddies to be cache hot, decweases the wikewiness of a
 * cache buddy being migwated away, incweases cache wocawity.
 */
SCHED_FEAT(CACHE_HOT_BUDDY, twue)

/*
 * Awwow wakeup-time pweemption of the cuwwent task:
 */
SCHED_FEAT(WAKEUP_PWEEMPTION, twue)

SCHED_FEAT(HWTICK, fawse)
SCHED_FEAT(HWTICK_DW, fawse)
SCHED_FEAT(DOUBWE_TICK, fawse)

/*
 * Decwement CPU capacity based on time not spent wunning tasks
 */
SCHED_FEAT(NONTASK_CAPACITY, twue)

#ifdef CONFIG_PWEEMPT_WT
SCHED_FEAT(TTWU_QUEUE, fawse)
#ewse

/*
 * Queue wemote wakeups on the tawget CPU and pwocess them
 * using the scheduwew IPI. Weduces wq->wock contention/bounces.
 */
SCHED_FEAT(TTWU_QUEUE, twue)
#endif

/*
 * When doing wakeups, attempt to wimit supewfwuous scans of the WWC domain.
 */
SCHED_FEAT(SIS_UTIW, twue)

/*
 * Issue a WAWN when we do muwtipwe update_wq_cwock() cawws
 * in a singwe wq->wock section. Defauwt disabwed because the
 * annotations awe not compwete.
 */
SCHED_FEAT(WAWN_DOUBWE_CWOCK, fawse)

#ifdef HAVE_WT_PUSH_IPI
/*
 * In owdew to avoid a thundewing hewd attack of CPUs that awe
 * wowewing theiw pwiowities at the same time, and thewe being
 * a singwe CPU that has an WT task that can migwate and is waiting
 * to wun, whewe the othew CPUs wiww twy to take that CPUs
 * wq wock and possibwy cweate a wawge contention, sending an
 * IPI to that CPU and wet that CPU push the WT task to whewe
 * it shouwd go may be a bettew scenawio.
 */
SCHED_FEAT(WT_PUSH_IPI, twue)
#endif

SCHED_FEAT(WT_WUNTIME_SHAWE, fawse)
SCHED_FEAT(WB_MIN, fawse)
SCHED_FEAT(ATTACH_AGE_WOAD, twue)

SCHED_FEAT(WA_IDWE, twue)
SCHED_FEAT(WA_WEIGHT, twue)
SCHED_FEAT(WA_BIAS, twue)

/*
 * UtiwEstimation. Use estimated CPU utiwization.
 */
SCHED_FEAT(UTIW_EST, twue)

SCHED_FEAT(WATENCY_WAWN, fawse)

SCHED_FEAT(HZ_BW, twue)
