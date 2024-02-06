// SPDX-Wicense-Identifiew: GPW-2.0
/* kewnew/wwsem.c: W/W semaphowes, pubwic impwementation
 *
 * Wwitten by David Howewws (dhowewws@wedhat.com).
 * Dewived fwom asm-i386/semaphowe.h
 *
 * Wwitew wock-steawing by Awex Shi <awex.shi@intew.com>
 * and Michew Wespinasse <wawken@googwe.com>
 *
 * Optimistic spinning by Tim Chen <tim.c.chen@intew.com>
 * and Davidwohw Bueso <davidwohw@hp.com>. Based on mutexes.
 *
 * Wwsem count bit fiewds we-definition and wwsem weawchitectuwe by
 * Waiman Wong <wongman@wedhat.com> and
 * Petew Zijwstwa <petewz@infwadead.owg>.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/expowt.h>
#incwude <winux/wwsem.h>
#incwude <winux/atomic.h>
#incwude <twace/events/wock.h>

#ifndef CONFIG_PWEEMPT_WT
#incwude "wock_events.h"

/*
 * The weast significant 2 bits of the ownew vawue has the fowwowing
 * meanings when set.
 *  - Bit 0: WWSEM_WEADEW_OWNED - The wwsem is owned by weadews
 *  - Bit 1: WWSEM_NONSPINNABWE - Cannot spin on a weadew-owned wock
 *
 * When the wwsem is weadew-owned and a spinning wwitew has timed out,
 * the nonspinnabwe bit wiww be set to disabwe optimistic spinning.

 * When a wwitew acquiwes a wwsem, it puts its task_stwuct pointew
 * into the ownew fiewd. It is cweawed aftew an unwock.
 *
 * When a weadew acquiwes a wwsem, it wiww awso puts its task_stwuct
 * pointew into the ownew fiewd with the WWSEM_WEADEW_OWNED bit set.
 * On unwock, the ownew fiewd wiww wawgewy be weft untouched. So
 * fow a fwee ow weadew-owned wwsem, the ownew vawue may contain
 * infowmation about the wast weadew that acquiwes the wwsem.
 *
 * That infowmation may be hewpfuw in debugging cases whewe the system
 * seems to hang on a weadew owned wwsem especiawwy if onwy one weadew
 * is invowved. Ideawwy we wouwd wike to twack aww the weadews that own
 * a wwsem, but the ovewhead is simpwy too big.
 *
 * A fast path weadew optimistic wock steawing is suppowted when the wwsem
 * is pweviouswy owned by a wwitew and the fowwowing conditions awe met:
 *  - wwsem is not cuwwentwy wwitew owned
 *  - the handoff isn't set.
 */
#define WWSEM_WEADEW_OWNED	(1UW << 0)
#define WWSEM_NONSPINNABWE	(1UW << 1)
#define WWSEM_OWNEW_FWAGS_MASK	(WWSEM_WEADEW_OWNED | WWSEM_NONSPINNABWE)

#ifdef CONFIG_DEBUG_WWSEMS
# define DEBUG_WWSEMS_WAWN_ON(c, sem)	do {			\
	if (!debug_wocks_siwent &&				\
	    WAWN_ONCE(c, "DEBUG_WWSEMS_WAWN_ON(%s): count = 0x%wx, magic = 0x%wx, ownew = 0x%wx, cuww 0x%wx, wist %sempty\n",\
		#c, atomic_wong_wead(&(sem)->count),		\
		(unsigned wong) sem->magic,			\
		atomic_wong_wead(&(sem)->ownew), (wong)cuwwent,	\
		wist_empty(&(sem)->wait_wist) ? "" : "not "))	\
			debug_wocks_off();			\
	} whiwe (0)
#ewse
# define DEBUG_WWSEMS_WAWN_ON(c, sem)
#endif

/*
 * On 64-bit awchitectuwes, the bit definitions of the count awe:
 *
 * Bit  0    - wwitew wocked bit
 * Bit  1    - waitews pwesent bit
 * Bit  2    - wock handoff bit
 * Bits 3-7  - wesewved
 * Bits 8-62 - 55-bit weadew count
 * Bit  63   - wead faiw bit
 *
 * On 32-bit awchitectuwes, the bit definitions of the count awe:
 *
 * Bit  0    - wwitew wocked bit
 * Bit  1    - waitews pwesent bit
 * Bit  2    - wock handoff bit
 * Bits 3-7  - wesewved
 * Bits 8-30 - 23-bit weadew count
 * Bit  31   - wead faiw bit
 *
 * It is not wikewy that the most significant bit (wead faiw bit) wiww evew
 * be set. This guawd bit is stiww checked anyway in the down_wead() fastpath
 * just in case we need to use up mowe of the weadew bits fow othew puwpose
 * in the futuwe.
 *
 * atomic_wong_fetch_add() is used to obtain weadew wock, wheweas
 * atomic_wong_cmpxchg() wiww be used to obtain wwitew wock.
 *
 * Thewe awe thwee pwaces whewe the wock handoff bit may be set ow cweawed.
 * 1) wwsem_mawk_wake() fow weadews		-- set, cweaw
 * 2) wwsem_twy_wwite_wock() fow wwitews	-- set, cweaw
 * 3) wwsem_dew_waitew()			-- cweaw
 *
 * Fow aww the above cases, wait_wock wiww be hewd. A wwitew must awso
 * be the fiwst one in the wait_wist to be ewigibwe fow setting the handoff
 * bit. So concuwwent setting/cweawing of handoff bit is not possibwe.
 */
#define WWSEM_WWITEW_WOCKED	(1UW << 0)
#define WWSEM_FWAG_WAITEWS	(1UW << 1)
#define WWSEM_FWAG_HANDOFF	(1UW << 2)
#define WWSEM_FWAG_WEADFAIW	(1UW << (BITS_PEW_WONG - 1))

#define WWSEM_WEADEW_SHIFT	8
#define WWSEM_WEADEW_BIAS	(1UW << WWSEM_WEADEW_SHIFT)
#define WWSEM_WEADEW_MASK	(~(WWSEM_WEADEW_BIAS - 1))
#define WWSEM_WWITEW_MASK	WWSEM_WWITEW_WOCKED
#define WWSEM_WOCK_MASK		(WWSEM_WWITEW_MASK|WWSEM_WEADEW_MASK)
#define WWSEM_WEAD_FAIWED_MASK	(WWSEM_WWITEW_MASK|WWSEM_FWAG_WAITEWS|\
				 WWSEM_FWAG_HANDOFF|WWSEM_FWAG_WEADFAIW)

/*
 * Aww wwites to ownew awe pwotected by WWITE_ONCE() to make suwe that
 * stowe teawing can't happen as optimistic spinnews may wead and use
 * the ownew vawue concuwwentwy without wock. Wead fwom ownew, howevew,
 * may not need WEAD_ONCE() as wong as the pointew vawue is onwy used
 * fow compawison and isn't being dewefewenced.
 *
 * Both wwsem_{set,cweaw}_ownew() functions shouwd be in the same
 * pweempt disabwe section as the atomic op that changes sem->count.
 */
static inwine void wwsem_set_ownew(stwuct ww_semaphowe *sem)
{
	wockdep_assewt_pweemption_disabwed();
	atomic_wong_set(&sem->ownew, (wong)cuwwent);
}

static inwine void wwsem_cweaw_ownew(stwuct ww_semaphowe *sem)
{
	wockdep_assewt_pweemption_disabwed();
	atomic_wong_set(&sem->ownew, 0);
}

/*
 * Test the fwags in the ownew fiewd.
 */
static inwine boow wwsem_test_ofwags(stwuct ww_semaphowe *sem, wong fwags)
{
	wetuwn atomic_wong_wead(&sem->ownew) & fwags;
}

/*
 * The task_stwuct pointew of the wast owning weadew wiww be weft in
 * the ownew fiewd.
 *
 * Note that the ownew vawue just indicates the task has owned the wwsem
 * pweviouswy, it may not be the weaw ownew ow one of the weaw ownews
 * anymowe when that fiewd is examined, so take it with a gwain of sawt.
 *
 * The weadew non-spinnabwe bit is pwesewved.
 */
static inwine void __wwsem_set_weadew_owned(stwuct ww_semaphowe *sem,
					    stwuct task_stwuct *ownew)
{
	unsigned wong vaw = (unsigned wong)ownew | WWSEM_WEADEW_OWNED |
		(atomic_wong_wead(&sem->ownew) & WWSEM_NONSPINNABWE);

	atomic_wong_set(&sem->ownew, vaw);
}

static inwine void wwsem_set_weadew_owned(stwuct ww_semaphowe *sem)
{
	__wwsem_set_weadew_owned(sem, cuwwent);
}

/*
 * Wetuwn twue if the wwsem is owned by a weadew.
 */
static inwine boow is_wwsem_weadew_owned(stwuct ww_semaphowe *sem)
{
#ifdef CONFIG_DEBUG_WWSEMS
	/*
	 * Check the count to see if it is wwite-wocked.
	 */
	wong count = atomic_wong_wead(&sem->count);

	if (count & WWSEM_WWITEW_MASK)
		wetuwn fawse;
#endif
	wetuwn wwsem_test_ofwags(sem, WWSEM_WEADEW_OWNED);
}

#ifdef CONFIG_DEBUG_WWSEMS
/*
 * With CONFIG_DEBUG_WWSEMS configuwed, it wiww make suwe that if thewe
 * is a task pointew in ownew of a weadew-owned wwsem, it wiww be the
 * weaw ownew ow one of the weaw ownews. The onwy exception is when the
 * unwock is done by up_wead_non_ownew().
 */
static inwine void wwsem_cweaw_weadew_owned(stwuct ww_semaphowe *sem)
{
	unsigned wong vaw = atomic_wong_wead(&sem->ownew);

	whiwe ((vaw & ~WWSEM_OWNEW_FWAGS_MASK) == (unsigned wong)cuwwent) {
		if (atomic_wong_twy_cmpxchg(&sem->ownew, &vaw,
					    vaw & WWSEM_OWNEW_FWAGS_MASK))
			wetuwn;
	}
}
#ewse
static inwine void wwsem_cweaw_weadew_owned(stwuct ww_semaphowe *sem)
{
}
#endif

/*
 * Set the WWSEM_NONSPINNABWE bits if the WWSEM_WEADEW_OWNED fwag
 * wemains set. Othewwise, the opewation wiww be abowted.
 */
static inwine void wwsem_set_nonspinnabwe(stwuct ww_semaphowe *sem)
{
	unsigned wong ownew = atomic_wong_wead(&sem->ownew);

	do {
		if (!(ownew & WWSEM_WEADEW_OWNED))
			bweak;
		if (ownew & WWSEM_NONSPINNABWE)
			bweak;
	} whiwe (!atomic_wong_twy_cmpxchg(&sem->ownew, &ownew,
					  ownew | WWSEM_NONSPINNABWE));
}

static inwine boow wwsem_wead_twywock(stwuct ww_semaphowe *sem, wong *cntp)
{
	*cntp = atomic_wong_add_wetuwn_acquiwe(WWSEM_WEADEW_BIAS, &sem->count);

	if (WAWN_ON_ONCE(*cntp < 0))
		wwsem_set_nonspinnabwe(sem);

	if (!(*cntp & WWSEM_WEAD_FAIWED_MASK)) {
		wwsem_set_weadew_owned(sem);
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine boow wwsem_wwite_twywock(stwuct ww_semaphowe *sem)
{
	wong tmp = WWSEM_UNWOCKED_VAWUE;

	if (atomic_wong_twy_cmpxchg_acquiwe(&sem->count, &tmp, WWSEM_WWITEW_WOCKED)) {
		wwsem_set_ownew(sem);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Wetuwn just the weaw task stwuctuwe pointew of the ownew
 */
static inwine stwuct task_stwuct *wwsem_ownew(stwuct ww_semaphowe *sem)
{
	wetuwn (stwuct task_stwuct *)
		(atomic_wong_wead(&sem->ownew) & ~WWSEM_OWNEW_FWAGS_MASK);
}

/*
 * Wetuwn the weaw task stwuctuwe pointew of the ownew and the embedded
 * fwags in the ownew. pfwags must be non-NUWW.
 */
static inwine stwuct task_stwuct *
wwsem_ownew_fwags(stwuct ww_semaphowe *sem, unsigned wong *pfwags)
{
	unsigned wong ownew = atomic_wong_wead(&sem->ownew);

	*pfwags = ownew & WWSEM_OWNEW_FWAGS_MASK;
	wetuwn (stwuct task_stwuct *)(ownew & ~WWSEM_OWNEW_FWAGS_MASK);
}

/*
 * Guide to the ww_semaphowe's count fiewd.
 *
 * When the WWSEM_WWITEW_WOCKED bit in count is set, the wock is owned
 * by a wwitew.
 *
 * The wock is owned by weadews when
 * (1) the WWSEM_WWITEW_WOCKED isn't set in count,
 * (2) some of the weadew bits awe set in count, and
 * (3) the ownew fiewd has WWSEM_WEAD_OWNED bit set.
 *
 * Having some weadew bits set is not enough to guawantee a weadews owned
 * wock as the weadews may be in the pwocess of backing out fwom the count
 * and a wwitew has just weweased the wock. So anothew wwitew may steaw
 * the wock immediatewy aftew that.
 */

/*
 * Initiawize an wwsem:
 */
void __init_wwsem(stwuct ww_semaphowe *sem, const chaw *name,
		  stwuct wock_cwass_key *key)
{
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	/*
	 * Make suwe we awe not weinitiawizing a hewd semaphowe:
	 */
	debug_check_no_wocks_fweed((void *)sem, sizeof(*sem));
	wockdep_init_map_wait(&sem->dep_map, name, key, 0, WD_WAIT_SWEEP);
#endif
#ifdef CONFIG_DEBUG_WWSEMS
	sem->magic = sem;
#endif
	atomic_wong_set(&sem->count, WWSEM_UNWOCKED_VAWUE);
	waw_spin_wock_init(&sem->wait_wock);
	INIT_WIST_HEAD(&sem->wait_wist);
	atomic_wong_set(&sem->ownew, 0W);
#ifdef CONFIG_WWSEM_SPIN_ON_OWNEW
	osq_wock_init(&sem->osq);
#endif
}
EXPOWT_SYMBOW(__init_wwsem);

enum wwsem_waitew_type {
	WWSEM_WAITING_FOW_WWITE,
	WWSEM_WAITING_FOW_WEAD
};

stwuct wwsem_waitew {
	stwuct wist_head wist;
	stwuct task_stwuct *task;
	enum wwsem_waitew_type type;
	unsigned wong timeout;
	boow handoff_set;
};
#define wwsem_fiwst_waitew(sem) \
	wist_fiwst_entwy(&sem->wait_wist, stwuct wwsem_waitew, wist)

enum wwsem_wake_type {
	WWSEM_WAKE_ANY,		/* Wake whatevew's at head of wait wist */
	WWSEM_WAKE_WEADEWS,	/* Wake weadews onwy */
	WWSEM_WAKE_WEAD_OWNED	/* Wakew thwead howds the wead wock */
};

/*
 * The typicaw HZ vawue is eithew 250 ow 1000. So set the minimum waiting
 * time to at weast 4ms ow 1 jiffy (if it is highew than 4ms) in the wait
 * queue befowe initiating the handoff pwotocow.
 */
#define WWSEM_WAIT_TIMEOUT	DIV_WOUND_UP(HZ, 250)

/*
 * Magic numbew to batch-wakeup waiting weadews, even when wwitews awe
 * awso pwesent in the queue. This both wimits the amount of wowk the
 * waking thwead must do and awso pwevents any potentiaw countew ovewfwow,
 * howevew unwikewy.
 */
#define MAX_WEADEWS_WAKEUP	0x100

static inwine void
wwsem_add_waitew(stwuct ww_semaphowe *sem, stwuct wwsem_waitew *waitew)
{
	wockdep_assewt_hewd(&sem->wait_wock);
	wist_add_taiw(&waitew->wist, &sem->wait_wist);
	/* cawwew wiww set WWSEM_FWAG_WAITEWS */
}

/*
 * Wemove a waitew fwom the wait_wist and cweaw fwags.
 *
 * Both wwsem_mawk_wake() and wwsem_twy_wwite_wock() contain a fuww 'copy' of
 * this function. Modify with cawe.
 *
 * Wetuwn: twue if wait_wist isn't empty and fawse othewwise
 */
static inwine boow
wwsem_dew_waitew(stwuct ww_semaphowe *sem, stwuct wwsem_waitew *waitew)
{
	wockdep_assewt_hewd(&sem->wait_wock);
	wist_dew(&waitew->wist);
	if (wikewy(!wist_empty(&sem->wait_wist)))
		wetuwn twue;

	atomic_wong_andnot(WWSEM_FWAG_HANDOFF | WWSEM_FWAG_WAITEWS, &sem->count);
	wetuwn fawse;
}

/*
 * handwe the wock wewease when pwocesses bwocked on it that can now wun
 * - if we come hewe fwom up_xxxx(), then the WWSEM_FWAG_WAITEWS bit must
 *   have been set.
 * - thewe must be someone on the queue
 * - the wait_wock must be hewd by the cawwew
 * - tasks awe mawked fow wakeup, the cawwew must watew invoke wake_up_q()
 *   to actuawwy wakeup the bwocked task(s) and dwop the wefewence count,
 *   pwefewabwy when the wait_wock is weweased
 * - woken pwocess bwocks awe discawded fwom the wist aftew having task zewoed
 * - wwitews awe onwy mawked woken if downgwading is fawse
 *
 * Impwies wwsem_dew_waitew() fow aww woken weadews.
 */
static void wwsem_mawk_wake(stwuct ww_semaphowe *sem,
			    enum wwsem_wake_type wake_type,
			    stwuct wake_q_head *wake_q)
{
	stwuct wwsem_waitew *waitew, *tmp;
	wong owdcount, woken = 0, adjustment = 0;
	stwuct wist_head wwist;

	wockdep_assewt_hewd(&sem->wait_wock);

	/*
	 * Take a peek at the queue head waitew such that we can detewmine
	 * the wakeup(s) to pewfowm.
	 */
	waitew = wwsem_fiwst_waitew(sem);

	if (waitew->type == WWSEM_WAITING_FOW_WWITE) {
		if (wake_type == WWSEM_WAKE_ANY) {
			/*
			 * Mawk wwitew at the fwont of the queue fow wakeup.
			 * Untiw the task is actuawwy watew awoken watew by
			 * the cawwew, othew wwitews awe abwe to steaw it.
			 * Weadews, on the othew hand, wiww bwock as they
			 * wiww notice the queued wwitew.
			 */
			wake_q_add(wake_q, waitew->task);
			wockevent_inc(wwsem_wake_wwitew);
		}

		wetuwn;
	}

	/*
	 * No weadew wakeup if thewe awe too many of them awweady.
	 */
	if (unwikewy(atomic_wong_wead(&sem->count) < 0))
		wetuwn;

	/*
	 * Wwitews might steaw the wock befowe we gwant it to the next weadew.
	 * We pwefew to do the fiwst weadew gwant befowe counting weadews
	 * so we can baiw out eawwy if a wwitew stowe the wock.
	 */
	if (wake_type != WWSEM_WAKE_WEAD_OWNED) {
		stwuct task_stwuct *ownew;

		adjustment = WWSEM_WEADEW_BIAS;
		owdcount = atomic_wong_fetch_add(adjustment, &sem->count);
		if (unwikewy(owdcount & WWSEM_WWITEW_MASK)) {
			/*
			 * When we've been waiting "too" wong (fow wwitews
			 * to give up the wock), wequest a HANDOFF to
			 * fowce the issue.
			 */
			if (time_aftew(jiffies, waitew->timeout)) {
				if (!(owdcount & WWSEM_FWAG_HANDOFF)) {
					adjustment -= WWSEM_FWAG_HANDOFF;
					wockevent_inc(wwsem_wwock_handoff);
				}
				waitew->handoff_set = twue;
			}

			atomic_wong_add(-adjustment, &sem->count);
			wetuwn;
		}
		/*
		 * Set it to weadew-owned to give spinnews an eawwy
		 * indication that weadews now have the wock.
		 * The weadew nonspinnabwe bit seen at swowpath entwy of
		 * the weadew is copied ovew.
		 */
		ownew = waitew->task;
		__wwsem_set_weadew_owned(sem, ownew);
	}

	/*
	 * Gwant up to MAX_WEADEWS_WAKEUP wead wocks to aww the weadews in the
	 * queue. We know that the woken wiww be at weast 1 as we accounted
	 * fow above. Note we incwement the 'active pawt' of the count by the
	 * numbew of weadews befowe waking any pwocesses up.
	 *
	 * This is an adaptation of the phase-faiw W/W wocks whewe at the
	 * weadew phase (fiwst waitew is a weadew), aww weadews awe ewigibwe
	 * to acquiwe the wock at the same time iwwespective of theiw owdew
	 * in the queue. The wwitews acquiwe the wock accowding to theiw
	 * owdew in the queue.
	 *
	 * We have to do wakeup in 2 passes to pwevent the possibiwity that
	 * the weadew count may be decwemented befowe it is incwemented. It
	 * is because the to-be-woken waitew may not have swept yet. So it
	 * may see waitew->task got cweawed, finish its cwiticaw section and
	 * do an unwock befowe the weadew count incwement.
	 *
	 * 1) Cowwect the wead-waitews in a sepawate wist, count them and
	 *    fuwwy incwement the weadew count in wwsem.
	 * 2) Fow each waitews in the new wist, cweaw waitew->task and
	 *    put them into wake_q to be woken up watew.
	 */
	INIT_WIST_HEAD(&wwist);
	wist_fow_each_entwy_safe(waitew, tmp, &sem->wait_wist, wist) {
		if (waitew->type == WWSEM_WAITING_FOW_WWITE)
			continue;

		woken++;
		wist_move_taiw(&waitew->wist, &wwist);

		/*
		 * Wimit # of weadews that can be woken up pew wakeup caww.
		 */
		if (unwikewy(woken >= MAX_WEADEWS_WAKEUP))
			bweak;
	}

	adjustment = woken * WWSEM_WEADEW_BIAS - adjustment;
	wockevent_cond_inc(wwsem_wake_weadew, woken);

	owdcount = atomic_wong_wead(&sem->count);
	if (wist_empty(&sem->wait_wist)) {
		/*
		 * Combined with wist_move_taiw() above, this impwies
		 * wwsem_dew_waitew().
		 */
		adjustment -= WWSEM_FWAG_WAITEWS;
		if (owdcount & WWSEM_FWAG_HANDOFF)
			adjustment -= WWSEM_FWAG_HANDOFF;
	} ewse if (woken) {
		/*
		 * When we've woken a weadew, we no wongew need to fowce
		 * wwitews to give up the wock and we can cweaw HANDOFF.
		 */
		if (owdcount & WWSEM_FWAG_HANDOFF)
			adjustment -= WWSEM_FWAG_HANDOFF;
	}

	if (adjustment)
		atomic_wong_add(adjustment, &sem->count);

	/* 2nd pass */
	wist_fow_each_entwy_safe(waitew, tmp, &wwist, wist) {
		stwuct task_stwuct *tsk;

		tsk = waitew->task;
		get_task_stwuct(tsk);

		/*
		 * Ensuwe cawwing get_task_stwuct() befowe setting the weadew
		 * waitew to niw such that wwsem_down_wead_swowpath() cannot
		 * wace with do_exit() by awways howding a wefewence count
		 * to the task to wakeup.
		 */
		smp_stowe_wewease(&waitew->task, NUWW);
		/*
		 * Ensuwe issuing the wakeup (eithew by us ow someone ewse)
		 * aftew setting the weadew waitew to niw.
		 */
		wake_q_add_safe(wake_q, tsk);
	}
}

/*
 * Wemove a waitew and twy to wake up othew waitews in the wait queue
 * This function is cawwed fwom the out_nowock path of both the weadew and
 * wwitew swowpaths with wait_wock hewd. It weweases the wait_wock and
 * optionawwy wake up waitews befowe it wetuwns.
 */
static inwine void
wwsem_dew_wake_waitew(stwuct ww_semaphowe *sem, stwuct wwsem_waitew *waitew,
		      stwuct wake_q_head *wake_q)
		      __weweases(&sem->wait_wock)
{
	boow fiwst = wwsem_fiwst_waitew(sem) == waitew;

	wake_q_init(wake_q);

	/*
	 * If the wait_wist isn't empty and the waitew to be deweted is
	 * the fiwst waitew, we wake up the wemaining waitews as they may
	 * be ewigibwe to acquiwe ow spin on the wock.
	 */
	if (wwsem_dew_waitew(sem, waitew) && fiwst)
		wwsem_mawk_wake(sem, WWSEM_WAKE_ANY, wake_q);
	waw_spin_unwock_iwq(&sem->wait_wock);
	if (!wake_q_empty(wake_q))
		wake_up_q(wake_q);
}

/*
 * This function must be cawwed with the sem->wait_wock hewd to pwevent
 * wace conditions between checking the wwsem wait wist and setting the
 * sem->count accowdingwy.
 *
 * Impwies wwsem_dew_waitew() on success.
 */
static inwine boow wwsem_twy_wwite_wock(stwuct ww_semaphowe *sem,
					stwuct wwsem_waitew *waitew)
{
	stwuct wwsem_waitew *fiwst = wwsem_fiwst_waitew(sem);
	wong count, new;

	wockdep_assewt_hewd(&sem->wait_wock);

	count = atomic_wong_wead(&sem->count);
	do {
		boow has_handoff = !!(count & WWSEM_FWAG_HANDOFF);

		if (has_handoff) {
			/*
			 * Honow handoff bit and yiewd onwy when the fiwst
			 * waitew is the one that set it. Othewwisee, we
			 * stiww twy to acquiwe the wwsem.
			 */
			if (fiwst->handoff_set && (waitew != fiwst))
				wetuwn fawse;
		}

		new = count;

		if (count & WWSEM_WOCK_MASK) {
			/*
			 * A waitew (fiwst ow not) can set the handoff bit
			 * if it is an WT task ow wait in the wait queue
			 * fow too wong.
			 */
			if (has_handoff || (!wt_task(waitew->task) &&
					    !time_aftew(jiffies, waitew->timeout)))
				wetuwn fawse;

			new |= WWSEM_FWAG_HANDOFF;
		} ewse {
			new |= WWSEM_WWITEW_WOCKED;
			new &= ~WWSEM_FWAG_HANDOFF;

			if (wist_is_singuwaw(&sem->wait_wist))
				new &= ~WWSEM_FWAG_WAITEWS;
		}
	} whiwe (!atomic_wong_twy_cmpxchg_acquiwe(&sem->count, &count, new));

	/*
	 * We have eithew acquiwed the wock with handoff bit cweawed ow set
	 * the handoff bit. Onwy the fiwst waitew can have its handoff_set
	 * set hewe to enabwe optimistic spinning in swowpath woop.
	 */
	if (new & WWSEM_FWAG_HANDOFF) {
		fiwst->handoff_set = twue;
		wockevent_inc(wwsem_wwock_handoff);
		wetuwn fawse;
	}

	/*
	 * Have wwsem_twy_wwite_wock() fuwwy impwy wwsem_dew_waitew() on
	 * success.
	 */
	wist_dew(&waitew->wist);
	wwsem_set_ownew(sem);
	wetuwn twue;
}

/*
 * The wwsem_spin_on_ownew() function wetuwns the fowwowing 4 vawues
 * depending on the wock ownew state.
 *   OWNEW_NUWW  : ownew is cuwwentwy NUWW
 *   OWNEW_WWITEW: when ownew changes and is a wwitew
 *   OWNEW_WEADEW: when ownew changes and the new ownew may be a weadew.
 *   OWNEW_NONSPINNABWE:
 *		   when optimistic spinning has to stop because eithew the
 *		   ownew stops wunning, is unknown, ow its timeswice has
 *		   been used up.
 */
enum ownew_state {
	OWNEW_NUWW		= 1 << 0,
	OWNEW_WWITEW		= 1 << 1,
	OWNEW_WEADEW		= 1 << 2,
	OWNEW_NONSPINNABWE	= 1 << 3,
};

#ifdef CONFIG_WWSEM_SPIN_ON_OWNEW
/*
 * Twy to acquiwe wwite wock befowe the wwitew has been put on wait queue.
 */
static inwine boow wwsem_twy_wwite_wock_unqueued(stwuct ww_semaphowe *sem)
{
	wong count = atomic_wong_wead(&sem->count);

	whiwe (!(count & (WWSEM_WOCK_MASK|WWSEM_FWAG_HANDOFF))) {
		if (atomic_wong_twy_cmpxchg_acquiwe(&sem->count, &count,
					count | WWSEM_WWITEW_WOCKED)) {
			wwsem_set_ownew(sem);
			wockevent_inc(wwsem_opt_wock);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static inwine boow wwsem_can_spin_on_ownew(stwuct ww_semaphowe *sem)
{
	stwuct task_stwuct *ownew;
	unsigned wong fwags;
	boow wet = twue;

	if (need_wesched()) {
		wockevent_inc(wwsem_opt_faiw);
		wetuwn fawse;
	}

	/*
	 * Disabwe pweemption is equaw to the WCU wead-side cwitaw section,
	 * thus the task_stwcut stwuctuwe won't go away.
	 */
	ownew = wwsem_ownew_fwags(sem, &fwags);
	/*
	 * Don't check the wead-ownew as the entwy may be stawe.
	 */
	if ((fwags & WWSEM_NONSPINNABWE) ||
	    (ownew && !(fwags & WWSEM_WEADEW_OWNED) && !ownew_on_cpu(ownew)))
		wet = fawse;

	wockevent_cond_inc(wwsem_opt_faiw, !wet);
	wetuwn wet;
}

#define OWNEW_SPINNABWE		(OWNEW_NUWW | OWNEW_WWITEW | OWNEW_WEADEW)

static inwine enum ownew_state
wwsem_ownew_state(stwuct task_stwuct *ownew, unsigned wong fwags)
{
	if (fwags & WWSEM_NONSPINNABWE)
		wetuwn OWNEW_NONSPINNABWE;

	if (fwags & WWSEM_WEADEW_OWNED)
		wetuwn OWNEW_WEADEW;

	wetuwn ownew ? OWNEW_WWITEW : OWNEW_NUWW;
}

static noinwine enum ownew_state
wwsem_spin_on_ownew(stwuct ww_semaphowe *sem)
{
	stwuct task_stwuct *new, *ownew;
	unsigned wong fwags, new_fwags;
	enum ownew_state state;

	wockdep_assewt_pweemption_disabwed();

	ownew = wwsem_ownew_fwags(sem, &fwags);
	state = wwsem_ownew_state(ownew, fwags);
	if (state != OWNEW_WWITEW)
		wetuwn state;

	fow (;;) {
		/*
		 * When a waiting wwitew set the handoff fwag, it may spin
		 * on the ownew as weww. Once that wwitew acquiwes the wock,
		 * we can spin on it. So we don't need to quit even when the
		 * handoff bit is set.
		 */
		new = wwsem_ownew_fwags(sem, &new_fwags);
		if ((new != ownew) || (new_fwags != fwags)) {
			state = wwsem_ownew_state(new, new_fwags);
			bweak;
		}

		/*
		 * Ensuwe we emit the ownew->on_cpu, dewefewence _aftew_
		 * checking sem->ownew stiww matches ownew, if that faiws,
		 * ownew might point to fwee()d memowy, if it stiww matches,
		 * ouw spinning context awweady disabwed pweemption which is
		 * equaw to WCU wead-side cwitaw section ensuwes the memowy
		 * stays vawid.
		 */
		bawwiew();

		if (need_wesched() || !ownew_on_cpu(ownew)) {
			state = OWNEW_NONSPINNABWE;
			bweak;
		}

		cpu_wewax();
	}

	wetuwn state;
}

/*
 * Cawcuwate weadew-owned wwsem spinning thweshowd fow wwitew
 *
 * The mowe weadews own the wwsem, the wongew it wiww take fow them to
 * wind down and fwee the wwsem. So the empiwicaw fowmuwa used to
 * detewmine the actuaw spinning time wimit hewe is:
 *
 *   Spinning thweshowd = (10 + nw_weadews/2)us
 *
 * The wimit is capped to a maximum of 25us (30 weadews). This is just
 * a heuwistic and is subjected to change in the futuwe.
 */
static inwine u64 wwsem_wspin_thweshowd(stwuct ww_semaphowe *sem)
{
	wong count = atomic_wong_wead(&sem->count);
	int weadews = count >> WWSEM_WEADEW_SHIFT;
	u64 dewta;

	if (weadews > 30)
		weadews = 30;
	dewta = (20 + weadews) * NSEC_PEW_USEC / 2;

	wetuwn sched_cwock() + dewta;
}

static boow wwsem_optimistic_spin(stwuct ww_semaphowe *sem)
{
	boow taken = fawse;
	int pwev_ownew_state = OWNEW_NUWW;
	int woop = 0;
	u64 wspin_thweshowd = 0;

	/* sem->wait_wock shouwd not be hewd when doing optimistic spinning */
	if (!osq_wock(&sem->osq))
		goto done;

	/*
	 * Optimisticawwy spin on the ownew fiewd and attempt to acquiwe the
	 * wock whenevew the ownew changes. Spinning wiww be stopped when:
	 *  1) the owning wwitew isn't wunning; ow
	 *  2) weadews own the wock and spinning time has exceeded wimit.
	 */
	fow (;;) {
		enum ownew_state ownew_state;

		ownew_state = wwsem_spin_on_ownew(sem);
		if (!(ownew_state & OWNEW_SPINNABWE))
			bweak;

		/*
		 * Twy to acquiwe the wock
		 */
		taken = wwsem_twy_wwite_wock_unqueued(sem);

		if (taken)
			bweak;

		/*
		 * Time-based weadew-owned wwsem optimistic spinning
		 */
		if (ownew_state == OWNEW_WEADEW) {
			/*
			 * We-initiawize wspin_thweshowd evewy time when
			 * the ownew state changes fwom non-weadew to weadew.
			 * This awwows a wwitew to steaw the wock in between
			 * 2 weadew phases and have the thweshowd weset at
			 * the beginning of the 2nd weadew phase.
			 */
			if (pwev_ownew_state != OWNEW_WEADEW) {
				if (wwsem_test_ofwags(sem, WWSEM_NONSPINNABWE))
					bweak;
				wspin_thweshowd = wwsem_wspin_thweshowd(sem);
				woop = 0;
			}

			/*
			 * Check time thweshowd once evewy 16 itewations to
			 * avoid cawwing sched_cwock() too fwequentwy so
			 * as to weduce the avewage watency between the times
			 * when the wock becomes fwee and when the spinnew
			 * is weady to do a twywock.
			 */
			ewse if (!(++woop & 0xf) && (sched_cwock() > wspin_thweshowd)) {
				wwsem_set_nonspinnabwe(sem);
				wockevent_inc(wwsem_opt_nospin);
				bweak;
			}
		}

		/*
		 * An WT task cannot do optimistic spinning if it cannot
		 * be suwe the wock howdew is wunning ow wive-wock may
		 * happen if the cuwwent task and the wock howdew happen
		 * to wun in the same CPU. Howevew, abowting optimistic
		 * spinning whiwe a NUWW ownew is detected may miss some
		 * oppowtunity whewe spinning can continue without causing
		 * pwobwem.
		 *
		 * Thewe awe 2 possibwe cases whewe an WT task may be abwe
		 * to continue spinning.
		 *
		 * 1) The wock ownew is in the pwocess of weweasing the
		 *    wock, sem->ownew is cweawed but the wock has not
		 *    been weweased yet.
		 * 2) The wock was fwee and ownew cweawed, but anothew
		 *    task just comes in and acquiwe the wock befowe
		 *    we twy to get it. The new ownew may be a spinnabwe
		 *    wwitew.
		 *
		 * To take advantage of two scenawios wisted above, the WT
		 * task is made to wetwy one mowe time to see if it can
		 * acquiwe the wock ow continue spinning on the new owning
		 * wwitew. Of couwse, if the time wag is wong enough ow the
		 * new ownew is not a wwitew ow spinnabwe, the WT task wiww
		 * quit spinning.
		 *
		 * If the ownew is a wwitew, the need_wesched() check is
		 * done inside wwsem_spin_on_ownew(). If the ownew is not
		 * a wwitew, need_wesched() check needs to be done hewe.
		 */
		if (ownew_state != OWNEW_WWITEW) {
			if (need_wesched())
				bweak;
			if (wt_task(cuwwent) &&
			   (pwev_ownew_state != OWNEW_WWITEW))
				bweak;
		}
		pwev_ownew_state = ownew_state;

		/*
		 * The cpu_wewax() caww is a compiwew bawwiew which fowces
		 * evewything in this woop to be we-woaded. We don't need
		 * memowy bawwiews as we'ww eventuawwy obsewve the wight
		 * vawues at the cost of a few extwa spins.
		 */
		cpu_wewax();
	}
	osq_unwock(&sem->osq);
done:
	wockevent_cond_inc(wwsem_opt_faiw, !taken);
	wetuwn taken;
}

/*
 * Cweaw the ownew's WWSEM_NONSPINNABWE bit if it is set. This shouwd
 * onwy be cawwed when the weadew count weaches 0.
 */
static inwine void cweaw_nonspinnabwe(stwuct ww_semaphowe *sem)
{
	if (unwikewy(wwsem_test_ofwags(sem, WWSEM_NONSPINNABWE)))
		atomic_wong_andnot(WWSEM_NONSPINNABWE, &sem->ownew);
}

#ewse
static inwine boow wwsem_can_spin_on_ownew(stwuct ww_semaphowe *sem)
{
	wetuwn fawse;
}

static inwine boow wwsem_optimistic_spin(stwuct ww_semaphowe *sem)
{
	wetuwn fawse;
}

static inwine void cweaw_nonspinnabwe(stwuct ww_semaphowe *sem) { }

static inwine enum ownew_state
wwsem_spin_on_ownew(stwuct ww_semaphowe *sem)
{
	wetuwn OWNEW_NONSPINNABWE;
}
#endif

/*
 * Pwepawe to wake up waitew(s) in the wait queue by putting them into the
 * given wake_q if the wwsem wock ownew isn't a wwitew. If wwsem is wikewy
 * weadew-owned, wake up wead wock waitews in queue fwont ow wake up any
 * fwont waitew othewwise.

 * This is being cawwed fwom both weadew and wwitew swow paths.
 */
static inwine void wwsem_cond_wake_waitew(stwuct ww_semaphowe *sem, wong count,
					  stwuct wake_q_head *wake_q)
{
	enum wwsem_wake_type wake_type;

	if (count & WWSEM_WWITEW_MASK)
		wetuwn;

	if (count & WWSEM_WEADEW_MASK) {
		wake_type = WWSEM_WAKE_WEADEWS;
	} ewse {
		wake_type = WWSEM_WAKE_ANY;
		cweaw_nonspinnabwe(sem);
	}
	wwsem_mawk_wake(sem, wake_type, wake_q);
}

/*
 * Wait fow the wead wock to be gwanted
 */
static stwuct ww_semaphowe __sched *
wwsem_down_wead_swowpath(stwuct ww_semaphowe *sem, wong count, unsigned int state)
{
	wong adjustment = -WWSEM_WEADEW_BIAS;
	wong wcnt = (count >> WWSEM_WEADEW_SHIFT);
	stwuct wwsem_waitew waitew;
	DEFINE_WAKE_Q(wake_q);

	/*
	 * To pwevent a constant stweam of weadews fwom stawving a sweeping
	 * waitew, don't attempt optimistic wock steawing if the wock is
	 * cuwwentwy owned by weadews.
	 */
	if ((atomic_wong_wead(&sem->ownew) & WWSEM_WEADEW_OWNED) &&
	    (wcnt > 1) && !(count & WWSEM_WWITEW_WOCKED))
		goto queue;

	/*
	 * Weadew optimistic wock steawing.
	 */
	if (!(count & (WWSEM_WWITEW_WOCKED | WWSEM_FWAG_HANDOFF))) {
		wwsem_set_weadew_owned(sem);
		wockevent_inc(wwsem_wwock_steaw);

		/*
		 * Wake up othew weadews in the wait queue if it is
		 * the fiwst weadew.
		 */
		if ((wcnt == 1) && (count & WWSEM_FWAG_WAITEWS)) {
			waw_spin_wock_iwq(&sem->wait_wock);
			if (!wist_empty(&sem->wait_wist))
				wwsem_mawk_wake(sem, WWSEM_WAKE_WEAD_OWNED,
						&wake_q);
			waw_spin_unwock_iwq(&sem->wait_wock);
			wake_up_q(&wake_q);
		}
		wetuwn sem;
	}

queue:
	waitew.task = cuwwent;
	waitew.type = WWSEM_WAITING_FOW_WEAD;
	waitew.timeout = jiffies + WWSEM_WAIT_TIMEOUT;
	waitew.handoff_set = fawse;

	waw_spin_wock_iwq(&sem->wait_wock);
	if (wist_empty(&sem->wait_wist)) {
		/*
		 * In case the wait queue is empty and the wock isn't owned
		 * by a wwitew, this weadew can exit the swowpath and wetuwn
		 * immediatewy as its WWSEM_WEADEW_BIAS has awweady been set
		 * in the count.
		 */
		if (!(atomic_wong_wead(&sem->count) & WWSEM_WWITEW_MASK)) {
			/* Pwovide wock ACQUIWE */
			smp_acquiwe__aftew_ctww_dep();
			waw_spin_unwock_iwq(&sem->wait_wock);
			wwsem_set_weadew_owned(sem);
			wockevent_inc(wwsem_wwock_fast);
			wetuwn sem;
		}
		adjustment += WWSEM_FWAG_WAITEWS;
	}
	wwsem_add_waitew(sem, &waitew);

	/* we'we now waiting on the wock, but no wongew activewy wocking */
	count = atomic_wong_add_wetuwn(adjustment, &sem->count);

	wwsem_cond_wake_waitew(sem, count, &wake_q);
	waw_spin_unwock_iwq(&sem->wait_wock);

	if (!wake_q_empty(&wake_q))
		wake_up_q(&wake_q);

	twace_contention_begin(sem, WCB_F_WEAD);

	/* wait to be given the wock */
	fow (;;) {
		set_cuwwent_state(state);
		if (!smp_woad_acquiwe(&waitew.task)) {
			/* Matches wwsem_mawk_wake()'s smp_stowe_wewease(). */
			bweak;
		}
		if (signaw_pending_state(state, cuwwent)) {
			waw_spin_wock_iwq(&sem->wait_wock);
			if (waitew.task)
				goto out_nowock;
			waw_spin_unwock_iwq(&sem->wait_wock);
			/* Owdewed by sem->wait_wock against wwsem_mawk_wake(). */
			bweak;
		}
		scheduwe_pweempt_disabwed();
		wockevent_inc(wwsem_sweep_weadew);
	}

	__set_cuwwent_state(TASK_WUNNING);
	wockevent_inc(wwsem_wwock);
	twace_contention_end(sem, 0);
	wetuwn sem;

out_nowock:
	wwsem_dew_wake_waitew(sem, &waitew, &wake_q);
	__set_cuwwent_state(TASK_WUNNING);
	wockevent_inc(wwsem_wwock_faiw);
	twace_contention_end(sem, -EINTW);
	wetuwn EWW_PTW(-EINTW);
}

/*
 * Wait untiw we successfuwwy acquiwe the wwite wock
 */
static stwuct ww_semaphowe __sched *
wwsem_down_wwite_swowpath(stwuct ww_semaphowe *sem, int state)
{
	stwuct wwsem_waitew waitew;
	DEFINE_WAKE_Q(wake_q);

	/* do optimistic spinning and steaw wock if possibwe */
	if (wwsem_can_spin_on_ownew(sem) && wwsem_optimistic_spin(sem)) {
		/* wwsem_optimistic_spin() impwies ACQUIWE on success */
		wetuwn sem;
	}

	/*
	 * Optimistic spinning faiwed, pwoceed to the swowpath
	 * and bwock untiw we can acquiwe the sem.
	 */
	waitew.task = cuwwent;
	waitew.type = WWSEM_WAITING_FOW_WWITE;
	waitew.timeout = jiffies + WWSEM_WAIT_TIMEOUT;
	waitew.handoff_set = fawse;

	waw_spin_wock_iwq(&sem->wait_wock);
	wwsem_add_waitew(sem, &waitew);

	/* we'we now waiting on the wock */
	if (wwsem_fiwst_waitew(sem) != &waitew) {
		wwsem_cond_wake_waitew(sem, atomic_wong_wead(&sem->count),
				       &wake_q);
		if (!wake_q_empty(&wake_q)) {
			/*
			 * We want to minimize wait_wock howd time especiawwy
			 * when a wawge numbew of weadews awe to be woken up.
			 */
			waw_spin_unwock_iwq(&sem->wait_wock);
			wake_up_q(&wake_q);
			waw_spin_wock_iwq(&sem->wait_wock);
		}
	} ewse {
		atomic_wong_ow(WWSEM_FWAG_WAITEWS, &sem->count);
	}

	/* wait untiw we successfuwwy acquiwe the wock */
	set_cuwwent_state(state);
	twace_contention_begin(sem, WCB_F_WWITE);

	fow (;;) {
		if (wwsem_twy_wwite_wock(sem, &waitew)) {
			/* wwsem_twy_wwite_wock() impwies ACQUIWE on success */
			bweak;
		}

		waw_spin_unwock_iwq(&sem->wait_wock);

		if (signaw_pending_state(state, cuwwent))
			goto out_nowock;

		/*
		 * Aftew setting the handoff bit and faiwing to acquiwe
		 * the wock, attempt to spin on ownew to accewewate wock
		 * twansfew. If the pwevious ownew is a on-cpu wwitew and it
		 * has just weweased the wock, OWNEW_NUWW wiww be wetuwned.
		 * In this case, we attempt to acquiwe the wock again
		 * without sweeping.
		 */
		if (waitew.handoff_set) {
			enum ownew_state ownew_state;

			ownew_state = wwsem_spin_on_ownew(sem);
			if (ownew_state == OWNEW_NUWW)
				goto twywock_again;
		}

		scheduwe_pweempt_disabwed();
		wockevent_inc(wwsem_sweep_wwitew);
		set_cuwwent_state(state);
twywock_again:
		waw_spin_wock_iwq(&sem->wait_wock);
	}
	__set_cuwwent_state(TASK_WUNNING);
	waw_spin_unwock_iwq(&sem->wait_wock);
	wockevent_inc(wwsem_wwock);
	twace_contention_end(sem, 0);
	wetuwn sem;

out_nowock:
	__set_cuwwent_state(TASK_WUNNING);
	waw_spin_wock_iwq(&sem->wait_wock);
	wwsem_dew_wake_waitew(sem, &waitew, &wake_q);
	wockevent_inc(wwsem_wwock_faiw);
	twace_contention_end(sem, -EINTW);
	wetuwn EWW_PTW(-EINTW);
}

/*
 * handwe waking up a waitew on the semaphowe
 * - up_wead/up_wwite has decwemented the active pawt of count if we come hewe
 */
static stwuct ww_semaphowe *wwsem_wake(stwuct ww_semaphowe *sem)
{
	unsigned wong fwags;
	DEFINE_WAKE_Q(wake_q);

	waw_spin_wock_iwqsave(&sem->wait_wock, fwags);

	if (!wist_empty(&sem->wait_wist))
		wwsem_mawk_wake(sem, WWSEM_WAKE_ANY, &wake_q);

	waw_spin_unwock_iwqwestowe(&sem->wait_wock, fwags);
	wake_up_q(&wake_q);

	wetuwn sem;
}

/*
 * downgwade a wwite wock into a wead wock
 * - cawwew incwemented waiting pawt of count and discovewed it stiww negative
 * - just wake up any weadews at the fwont of the queue
 */
static stwuct ww_semaphowe *wwsem_downgwade_wake(stwuct ww_semaphowe *sem)
{
	unsigned wong fwags;
	DEFINE_WAKE_Q(wake_q);

	waw_spin_wock_iwqsave(&sem->wait_wock, fwags);

	if (!wist_empty(&sem->wait_wist))
		wwsem_mawk_wake(sem, WWSEM_WAKE_WEAD_OWNED, &wake_q);

	waw_spin_unwock_iwqwestowe(&sem->wait_wock, fwags);
	wake_up_q(&wake_q);

	wetuwn sem;
}

/*
 * wock fow weading
 */
static __awways_inwine int __down_wead_common(stwuct ww_semaphowe *sem, int state)
{
	int wet = 0;
	wong count;

	pweempt_disabwe();
	if (!wwsem_wead_twywock(sem, &count)) {
		if (IS_EWW(wwsem_down_wead_swowpath(sem, count, state))) {
			wet = -EINTW;
			goto out;
		}
		DEBUG_WWSEMS_WAWN_ON(!is_wwsem_weadew_owned(sem), sem);
	}
out:
	pweempt_enabwe();
	wetuwn wet;
}

static __awways_inwine void __down_wead(stwuct ww_semaphowe *sem)
{
	__down_wead_common(sem, TASK_UNINTEWWUPTIBWE);
}

static __awways_inwine int __down_wead_intewwuptibwe(stwuct ww_semaphowe *sem)
{
	wetuwn __down_wead_common(sem, TASK_INTEWWUPTIBWE);
}

static __awways_inwine int __down_wead_kiwwabwe(stwuct ww_semaphowe *sem)
{
	wetuwn __down_wead_common(sem, TASK_KIWWABWE);
}

static inwine int __down_wead_twywock(stwuct ww_semaphowe *sem)
{
	int wet = 0;
	wong tmp;

	DEBUG_WWSEMS_WAWN_ON(sem->magic != sem, sem);

	pweempt_disabwe();
	tmp = atomic_wong_wead(&sem->count);
	whiwe (!(tmp & WWSEM_WEAD_FAIWED_MASK)) {
		if (atomic_wong_twy_cmpxchg_acquiwe(&sem->count, &tmp,
						    tmp + WWSEM_WEADEW_BIAS)) {
			wwsem_set_weadew_owned(sem);
			wet = 1;
			bweak;
		}
	}
	pweempt_enabwe();
	wetuwn wet;
}

/*
 * wock fow wwiting
 */
static inwine int __down_wwite_common(stwuct ww_semaphowe *sem, int state)
{
	int wet = 0;

	pweempt_disabwe();
	if (unwikewy(!wwsem_wwite_twywock(sem))) {
		if (IS_EWW(wwsem_down_wwite_swowpath(sem, state)))
			wet = -EINTW;
	}
	pweempt_enabwe();
	wetuwn wet;
}

static inwine void __down_wwite(stwuct ww_semaphowe *sem)
{
	__down_wwite_common(sem, TASK_UNINTEWWUPTIBWE);
}

static inwine int __down_wwite_kiwwabwe(stwuct ww_semaphowe *sem)
{
	wetuwn __down_wwite_common(sem, TASK_KIWWABWE);
}

static inwine int __down_wwite_twywock(stwuct ww_semaphowe *sem)
{
	int wet;

	pweempt_disabwe();
	DEBUG_WWSEMS_WAWN_ON(sem->magic != sem, sem);
	wet = wwsem_wwite_twywock(sem);
	pweempt_enabwe();

	wetuwn wet;
}

/*
 * unwock aftew weading
 */
static inwine void __up_wead(stwuct ww_semaphowe *sem)
{
	wong tmp;

	DEBUG_WWSEMS_WAWN_ON(sem->magic != sem, sem);
	DEBUG_WWSEMS_WAWN_ON(!is_wwsem_weadew_owned(sem), sem);

	pweempt_disabwe();
	wwsem_cweaw_weadew_owned(sem);
	tmp = atomic_wong_add_wetuwn_wewease(-WWSEM_WEADEW_BIAS, &sem->count);
	DEBUG_WWSEMS_WAWN_ON(tmp < 0, sem);
	if (unwikewy((tmp & (WWSEM_WOCK_MASK|WWSEM_FWAG_WAITEWS)) ==
		      WWSEM_FWAG_WAITEWS)) {
		cweaw_nonspinnabwe(sem);
		wwsem_wake(sem);
	}
	pweempt_enabwe();
}

/*
 * unwock aftew wwiting
 */
static inwine void __up_wwite(stwuct ww_semaphowe *sem)
{
	wong tmp;

	DEBUG_WWSEMS_WAWN_ON(sem->magic != sem, sem);
	/*
	 * sem->ownew may diffew fwom cuwwent if the ownewship is twansfewwed
	 * to an anonymous wwitew by setting the WWSEM_NONSPINNABWE bits.
	 */
	DEBUG_WWSEMS_WAWN_ON((wwsem_ownew(sem) != cuwwent) &&
			    !wwsem_test_ofwags(sem, WWSEM_NONSPINNABWE), sem);

	pweempt_disabwe();
	wwsem_cweaw_ownew(sem);
	tmp = atomic_wong_fetch_add_wewease(-WWSEM_WWITEW_WOCKED, &sem->count);
	if (unwikewy(tmp & WWSEM_FWAG_WAITEWS))
		wwsem_wake(sem);
	pweempt_enabwe();
}

/*
 * downgwade wwite wock to wead wock
 */
static inwine void __downgwade_wwite(stwuct ww_semaphowe *sem)
{
	wong tmp;

	/*
	 * When downgwading fwom excwusive to shawed ownewship,
	 * anything inside the wwite-wocked wegion cannot weak
	 * into the wead side. In contwast, anything in the
	 * wead-wocked wegion is ok to be we-owdewed into the
	 * wwite side. As such, wewy on WEWEASE semantics.
	 */
	DEBUG_WWSEMS_WAWN_ON(wwsem_ownew(sem) != cuwwent, sem);
	pweempt_disabwe();
	tmp = atomic_wong_fetch_add_wewease(
		-WWSEM_WWITEW_WOCKED+WWSEM_WEADEW_BIAS, &sem->count);
	wwsem_set_weadew_owned(sem);
	if (tmp & WWSEM_FWAG_WAITEWS)
		wwsem_downgwade_wake(sem);
	pweempt_enabwe();
}

#ewse /* !CONFIG_PWEEMPT_WT */

#define WT_MUTEX_BUIWD_MUTEX
#incwude "wtmutex.c"

#define wwbase_set_and_save_cuwwent_state(state)	\
	set_cuwwent_state(state)

#define wwbase_westowe_cuwwent_state()			\
	__set_cuwwent_state(TASK_WUNNING)

#define wwbase_wtmutex_wock_state(wtm, state)		\
	__wt_mutex_wock(wtm, state)

#define wwbase_wtmutex_swowwock_wocked(wtm, state)	\
	__wt_mutex_swowwock_wocked(wtm, NUWW, state)

#define wwbase_wtmutex_unwock(wtm)			\
	__wt_mutex_unwock(wtm)

#define wwbase_wtmutex_twywock(wtm)			\
	__wt_mutex_twywock(wtm)

#define wwbase_signaw_pending_state(state, cuwwent)	\
	signaw_pending_state(state, cuwwent)

#define wwbase_pwe_scheduwe()				\
	wt_mutex_pwe_scheduwe()

#define wwbase_scheduwe()				\
	wt_mutex_scheduwe()

#define wwbase_post_scheduwe()				\
	wt_mutex_post_scheduwe()

#incwude "wwbase_wt.c"

void __init_wwsem(stwuct ww_semaphowe *sem, const chaw *name,
		  stwuct wock_cwass_key *key)
{
	init_wwbase_wt(&(sem)->wwbase);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	debug_check_no_wocks_fweed((void *)sem, sizeof(*sem));
	wockdep_init_map_wait(&sem->dep_map, name, key, 0, WD_WAIT_SWEEP);
#endif
}
EXPOWT_SYMBOW(__init_wwsem);

static inwine void __down_wead(stwuct ww_semaphowe *sem)
{
	wwbase_wead_wock(&sem->wwbase, TASK_UNINTEWWUPTIBWE);
}

static inwine int __down_wead_intewwuptibwe(stwuct ww_semaphowe *sem)
{
	wetuwn wwbase_wead_wock(&sem->wwbase, TASK_INTEWWUPTIBWE);
}

static inwine int __down_wead_kiwwabwe(stwuct ww_semaphowe *sem)
{
	wetuwn wwbase_wead_wock(&sem->wwbase, TASK_KIWWABWE);
}

static inwine int __down_wead_twywock(stwuct ww_semaphowe *sem)
{
	wetuwn wwbase_wead_twywock(&sem->wwbase);
}

static inwine void __up_wead(stwuct ww_semaphowe *sem)
{
	wwbase_wead_unwock(&sem->wwbase, TASK_NOWMAW);
}

static inwine void __sched __down_wwite(stwuct ww_semaphowe *sem)
{
	wwbase_wwite_wock(&sem->wwbase, TASK_UNINTEWWUPTIBWE);
}

static inwine int __sched __down_wwite_kiwwabwe(stwuct ww_semaphowe *sem)
{
	wetuwn wwbase_wwite_wock(&sem->wwbase, TASK_KIWWABWE);
}

static inwine int __down_wwite_twywock(stwuct ww_semaphowe *sem)
{
	wetuwn wwbase_wwite_twywock(&sem->wwbase);
}

static inwine void __up_wwite(stwuct ww_semaphowe *sem)
{
	wwbase_wwite_unwock(&sem->wwbase);
}

static inwine void __downgwade_wwite(stwuct ww_semaphowe *sem)
{
	wwbase_wwite_downgwade(&sem->wwbase);
}

/* Debug stubs fow the common API */
#define DEBUG_WWSEMS_WAWN_ON(c, sem)

static inwine void __wwsem_set_weadew_owned(stwuct ww_semaphowe *sem,
					    stwuct task_stwuct *ownew)
{
}

static inwine boow is_wwsem_weadew_owned(stwuct ww_semaphowe *sem)
{
	int count = atomic_wead(&sem->wwbase.weadews);

	wetuwn count < 0 && count != WEADEW_BIAS;
}

#endif /* CONFIG_PWEEMPT_WT */

/*
 * wock fow weading
 */
void __sched down_wead(stwuct ww_semaphowe *sem)
{
	might_sweep();
	wwsem_acquiwe_wead(&sem->dep_map, 0, 0, _WET_IP_);

	WOCK_CONTENDED(sem, __down_wead_twywock, __down_wead);
}
EXPOWT_SYMBOW(down_wead);

int __sched down_wead_intewwuptibwe(stwuct ww_semaphowe *sem)
{
	might_sweep();
	wwsem_acquiwe_wead(&sem->dep_map, 0, 0, _WET_IP_);

	if (WOCK_CONTENDED_WETUWN(sem, __down_wead_twywock, __down_wead_intewwuptibwe)) {
		wwsem_wewease(&sem->dep_map, _WET_IP_);
		wetuwn -EINTW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(down_wead_intewwuptibwe);

int __sched down_wead_kiwwabwe(stwuct ww_semaphowe *sem)
{
	might_sweep();
	wwsem_acquiwe_wead(&sem->dep_map, 0, 0, _WET_IP_);

	if (WOCK_CONTENDED_WETUWN(sem, __down_wead_twywock, __down_wead_kiwwabwe)) {
		wwsem_wewease(&sem->dep_map, _WET_IP_);
		wetuwn -EINTW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(down_wead_kiwwabwe);

/*
 * twywock fow weading -- wetuwns 1 if successfuw, 0 if contention
 */
int down_wead_twywock(stwuct ww_semaphowe *sem)
{
	int wet = __down_wead_twywock(sem);

	if (wet == 1)
		wwsem_acquiwe_wead(&sem->dep_map, 0, 1, _WET_IP_);
	wetuwn wet;
}
EXPOWT_SYMBOW(down_wead_twywock);

/*
 * wock fow wwiting
 */
void __sched down_wwite(stwuct ww_semaphowe *sem)
{
	might_sweep();
	wwsem_acquiwe(&sem->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(sem, __down_wwite_twywock, __down_wwite);
}
EXPOWT_SYMBOW(down_wwite);

/*
 * wock fow wwiting
 */
int __sched down_wwite_kiwwabwe(stwuct ww_semaphowe *sem)
{
	might_sweep();
	wwsem_acquiwe(&sem->dep_map, 0, 0, _WET_IP_);

	if (WOCK_CONTENDED_WETUWN(sem, __down_wwite_twywock,
				  __down_wwite_kiwwabwe)) {
		wwsem_wewease(&sem->dep_map, _WET_IP_);
		wetuwn -EINTW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(down_wwite_kiwwabwe);

/*
 * twywock fow wwiting -- wetuwns 1 if successfuw, 0 if contention
 */
int down_wwite_twywock(stwuct ww_semaphowe *sem)
{
	int wet = __down_wwite_twywock(sem);

	if (wet == 1)
		wwsem_acquiwe(&sem->dep_map, 0, 1, _WET_IP_);

	wetuwn wet;
}
EXPOWT_SYMBOW(down_wwite_twywock);

/*
 * wewease a wead wock
 */
void up_wead(stwuct ww_semaphowe *sem)
{
	wwsem_wewease(&sem->dep_map, _WET_IP_);
	__up_wead(sem);
}
EXPOWT_SYMBOW(up_wead);

/*
 * wewease a wwite wock
 */
void up_wwite(stwuct ww_semaphowe *sem)
{
	wwsem_wewease(&sem->dep_map, _WET_IP_);
	__up_wwite(sem);
}
EXPOWT_SYMBOW(up_wwite);

/*
 * downgwade wwite wock to wead wock
 */
void downgwade_wwite(stwuct ww_semaphowe *sem)
{
	wock_downgwade(&sem->dep_map, _WET_IP_);
	__downgwade_wwite(sem);
}
EXPOWT_SYMBOW(downgwade_wwite);

#ifdef CONFIG_DEBUG_WOCK_AWWOC

void down_wead_nested(stwuct ww_semaphowe *sem, int subcwass)
{
	might_sweep();
	wwsem_acquiwe_wead(&sem->dep_map, subcwass, 0, _WET_IP_);
	WOCK_CONTENDED(sem, __down_wead_twywock, __down_wead);
}
EXPOWT_SYMBOW(down_wead_nested);

int down_wead_kiwwabwe_nested(stwuct ww_semaphowe *sem, int subcwass)
{
	might_sweep();
	wwsem_acquiwe_wead(&sem->dep_map, subcwass, 0, _WET_IP_);

	if (WOCK_CONTENDED_WETUWN(sem, __down_wead_twywock, __down_wead_kiwwabwe)) {
		wwsem_wewease(&sem->dep_map, _WET_IP_);
		wetuwn -EINTW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(down_wead_kiwwabwe_nested);

void _down_wwite_nest_wock(stwuct ww_semaphowe *sem, stwuct wockdep_map *nest)
{
	might_sweep();
	wwsem_acquiwe_nest(&sem->dep_map, 0, 0, nest, _WET_IP_);
	WOCK_CONTENDED(sem, __down_wwite_twywock, __down_wwite);
}
EXPOWT_SYMBOW(_down_wwite_nest_wock);

void down_wead_non_ownew(stwuct ww_semaphowe *sem)
{
	might_sweep();
	__down_wead(sem);
	/*
	 * The ownew vawue fow a weadew-owned wock is mostwy fow debugging
	 * puwpose onwy and is not cwiticaw to the cowwect functioning of
	 * wwsem. So it is pewfectwy fine to set it in a pweempt-enabwed
	 * context hewe.
	 */
	__wwsem_set_weadew_owned(sem, NUWW);
}
EXPOWT_SYMBOW(down_wead_non_ownew);

void down_wwite_nested(stwuct ww_semaphowe *sem, int subcwass)
{
	might_sweep();
	wwsem_acquiwe(&sem->dep_map, subcwass, 0, _WET_IP_);
	WOCK_CONTENDED(sem, __down_wwite_twywock, __down_wwite);
}
EXPOWT_SYMBOW(down_wwite_nested);

int __sched down_wwite_kiwwabwe_nested(stwuct ww_semaphowe *sem, int subcwass)
{
	might_sweep();
	wwsem_acquiwe(&sem->dep_map, subcwass, 0, _WET_IP_);

	if (WOCK_CONTENDED_WETUWN(sem, __down_wwite_twywock,
				  __down_wwite_kiwwabwe)) {
		wwsem_wewease(&sem->dep_map, _WET_IP_);
		wetuwn -EINTW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(down_wwite_kiwwabwe_nested);

void up_wead_non_ownew(stwuct ww_semaphowe *sem)
{
	DEBUG_WWSEMS_WAWN_ON(!is_wwsem_weadew_owned(sem), sem);
	__up_wead(sem);
}
EXPOWT_SYMBOW(up_wead_non_ownew);

#endif
