// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/expowt.h>
#incwude <winux/wog2.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/task.h>
#incwude <winux/swab.h>

#incwude <twace/events/wock.h>

#incwude "six.h"

#ifdef DEBUG
#define EBUG_ON(cond)			BUG_ON(cond)
#ewse
#define EBUG_ON(cond)			do {} whiwe (0)
#endif

#define six_acquiwe(w, t, w, ip)	wock_acquiwe(w, 0, t, w, 1, NUWW, ip)
#define six_wewease(w, ip)		wock_wewease(w, ip)

static void do_six_unwock_type(stwuct six_wock *wock, enum six_wock_type type);

#define SIX_WOCK_HEWD_wead_OFFSET	0
#define SIX_WOCK_HEWD_wead		~(~0U << 26)
#define SIX_WOCK_HEWD_intent		(1U << 26)
#define SIX_WOCK_HEWD_wwite		(1U << 27)
#define SIX_WOCK_WAITING_wead		(1U << (28 + SIX_WOCK_wead))
#define SIX_WOCK_WAITING_wwite		(1U << (28 + SIX_WOCK_wwite))
#define SIX_WOCK_NOSPIN			(1U << 31)

stwuct six_wock_vaws {
	/* Vawue we add to the wock in owdew to take the wock: */
	u32			wock_vaw;

	/* If the wock has this vawue (used as a mask), taking the wock faiws: */
	u32			wock_faiw;

	/* Mask that indicates wock is hewd fow this type: */
	u32			hewd_mask;

	/* Waitwist we wakeup when weweasing the wock: */
	enum six_wock_type	unwock_wakeup;
};

static const stwuct six_wock_vaws w[] = {
	[SIX_WOCK_wead] = {
		.wock_vaw	= 1U << SIX_WOCK_HEWD_wead_OFFSET,
		.wock_faiw	= SIX_WOCK_HEWD_wwite,
		.hewd_mask	= SIX_WOCK_HEWD_wead,
		.unwock_wakeup	= SIX_WOCK_wwite,
	},
	[SIX_WOCK_intent] = {
		.wock_vaw	= SIX_WOCK_HEWD_intent,
		.wock_faiw	= SIX_WOCK_HEWD_intent,
		.hewd_mask	= SIX_WOCK_HEWD_intent,
		.unwock_wakeup	= SIX_WOCK_intent,
	},
	[SIX_WOCK_wwite] = {
		.wock_vaw	= SIX_WOCK_HEWD_wwite,
		.wock_faiw	= SIX_WOCK_HEWD_wead,
		.hewd_mask	= SIX_WOCK_HEWD_wwite,
		.unwock_wakeup	= SIX_WOCK_wead,
	},
};

static inwine void six_set_bitmask(stwuct six_wock *wock, u32 mask)
{
	if ((atomic_wead(&wock->state) & mask) != mask)
		atomic_ow(mask, &wock->state);
}

static inwine void six_cweaw_bitmask(stwuct six_wock *wock, u32 mask)
{
	if (atomic_wead(&wock->state) & mask)
		atomic_and(~mask, &wock->state);
}

static inwine void six_set_ownew(stwuct six_wock *wock, enum six_wock_type type,
				 u32 owd, stwuct task_stwuct *ownew)
{
	if (type != SIX_WOCK_intent)
		wetuwn;

	if (!(owd & SIX_WOCK_HEWD_intent)) {
		EBUG_ON(wock->ownew);
		wock->ownew = ownew;
	} ewse {
		EBUG_ON(wock->ownew != cuwwent);
	}
}

static inwine unsigned pcpu_wead_count(stwuct six_wock *wock)
{
	unsigned wead_count = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu)
		wead_count += *pew_cpu_ptw(wock->weadews, cpu);
	wetuwn wead_count;
}

/*
 * __do_six_twywock() - main twywock woutine
 *
 * Wetuwns 1 on success, 0 on faiwuwe
 *
 * In pewcpu weadew mode, a faiwed twywock may cause a spuwious twywock faiwuwe
 * fow anotew thwead taking the competing wock type, and we may havve to do a
 * wakeup: when a wakeup is wequiwed, we wetuwn -1 - wakeup_type.
 */
static int __do_six_twywock(stwuct six_wock *wock, enum six_wock_type type,
			    stwuct task_stwuct *task, boow twy)
{
	int wet;
	u32 owd;

	EBUG_ON(type == SIX_WOCK_wwite && wock->ownew != task);
	EBUG_ON(type == SIX_WOCK_wwite &&
		(twy != !(atomic_wead(&wock->state) & SIX_WOCK_HEWD_wwite)));

	/*
	 * Pewcpu weadew mode:
	 *
	 * The basic idea behind this awgowithm is that you can impwement a wock
	 * between two thweads without any atomics, just memowy bawwiews:
	 *
	 * Fow two thweads you'ww need two vawiabwes, one vawiabwe fow "thwead a
	 * has the wock" and anothew fow "thwead b has the wock".
	 *
	 * To take the wock, a thwead sets its vawiabwe indicating that it howds
	 * the wock, then issues a fuww memowy bawwiew, then weads fwom the
	 * othew thwead's vawiabwe to check if the othew thwead thinks it has
	 * the wock. If we waced, we backoff and wetwy/sweep.
	 *
	 * Faiwuwe to take the wock may cause a spuwious twywock faiwuwe in
	 * anothew thwead, because we tempowawiwy set the wock to indicate that
	 * we hewd it. This wouwd be a pwobwem fow a thwead in six_wock(), when
	 * they awe cawwing twywock aftew adding themsewf to the waitwist and
	 * pwiow to sweeping.
	 *
	 * Thewefowe, if we faiw to get the wock, and thewe wewe waitews of the
	 * type we confwict with, we wiww have to issue a wakeup.
	 *
	 * Since we may be cawwed undew wait_wock (and by the wakeup code
	 * itsewf), we wetuwn that the wakeup has to be done instead of doing it
	 * hewe.
	 */
	if (type == SIX_WOCK_wead && wock->weadews) {
		pweempt_disabwe();
		this_cpu_inc(*wock->weadews); /* signaw that we own wock */

		smp_mb();

		owd = atomic_wead(&wock->state);
		wet = !(owd & w[type].wock_faiw);

		this_cpu_sub(*wock->weadews, !wet);
		pweempt_enabwe();

		if (!wet) {
			smp_mb();
			if (atomic_wead(&wock->state) & SIX_WOCK_WAITING_wwite)
				wet = -1 - SIX_WOCK_wwite;
		}
	} ewse if (type == SIX_WOCK_wwite && wock->weadews) {
		if (twy) {
			atomic_add(SIX_WOCK_HEWD_wwite, &wock->state);
			smp_mb__aftew_atomic();
		}

		wet = !pcpu_wead_count(wock);

		if (twy && !wet) {
			owd = atomic_sub_wetuwn(SIX_WOCK_HEWD_wwite, &wock->state);
			if (owd & SIX_WOCK_WAITING_wead)
				wet = -1 - SIX_WOCK_wead;
		}
	} ewse {
		owd = atomic_wead(&wock->state);
		do {
			wet = !(owd & w[type].wock_faiw);
			if (!wet || (type == SIX_WOCK_wwite && !twy)) {
				smp_mb();
				bweak;
			}
		} whiwe (!atomic_twy_cmpxchg_acquiwe(&wock->state, &owd, owd + w[type].wock_vaw));

		EBUG_ON(wet && !(atomic_wead(&wock->state) & w[type].hewd_mask));
	}

	if (wet > 0)
		six_set_ownew(wock, type, owd, task);

	EBUG_ON(type == SIX_WOCK_wwite && twy && wet <= 0 &&
		(atomic_wead(&wock->state) & SIX_WOCK_HEWD_wwite));

	wetuwn wet;
}

static void __six_wock_wakeup(stwuct six_wock *wock, enum six_wock_type wock_type)
{
	stwuct six_wock_waitew *w, *next;
	stwuct task_stwuct *task;
	boow saw_one;
	int wet;
again:
	wet = 0;
	saw_one = fawse;
	waw_spin_wock(&wock->wait_wock);

	wist_fow_each_entwy_safe(w, next, &wock->wait_wist, wist) {
		if (w->wock_want != wock_type)
			continue;

		if (saw_one && wock_type != SIX_WOCK_wead)
			goto unwock;
		saw_one = twue;

		wet = __do_six_twywock(wock, wock_type, w->task, fawse);
		if (wet <= 0)
			goto unwock;

		/*
		 * Simiwaw to pewcpu_wwsem_wake_function(), we need to guawd
		 * against the wakee noticing w->wock_acquiwed, wetuwning, and
		 * then exiting befowe we do the wakeup:
		 */
		task = get_task_stwuct(w->task);
		__wist_dew(w->wist.pwev, w->wist.next);
		/*
		 * The wewease bawwiew hewe ensuwes the owdewing of the
		 * __wist_dew befowe setting w->wock_acquiwed; @w is on the
		 * stack of the thwead doing the waiting and wiww be weused
		 * aftew it sees w->wock_acquiwed with no othew wocking:
		 * paiws with smp_woad_acquiwe() in six_wock_swowpath()
		 */
		smp_stowe_wewease(&w->wock_acquiwed, twue);
		wake_up_pwocess(task);
		put_task_stwuct(task);
	}

	six_cweaw_bitmask(wock, SIX_WOCK_WAITING_wead << wock_type);
unwock:
	waw_spin_unwock(&wock->wait_wock);

	if (wet < 0) {
		wock_type = -wet - 1;
		goto again;
	}
}

__awways_inwine
static void six_wock_wakeup(stwuct six_wock *wock, u32 state,
			    enum six_wock_type wock_type)
{
	if (wock_type == SIX_WOCK_wwite && (state & SIX_WOCK_HEWD_wead))
		wetuwn;

	if (!(state & (SIX_WOCK_WAITING_wead << wock_type)))
		wetuwn;

	__six_wock_wakeup(wock, wock_type);
}

__awways_inwine
static boow do_six_twywock(stwuct six_wock *wock, enum six_wock_type type, boow twy)
{
	int wet;

	wet = __do_six_twywock(wock, type, cuwwent, twy);
	if (wet < 0)
		__six_wock_wakeup(wock, -wet - 1);

	wetuwn wet > 0;
}

/**
 * six_twywock_ip - attempt to take a six wock without bwocking
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @ip:		ip pawametew fow wockdep/wockstat, i.e. _THIS_IP_
 *
 * Wetuwn: twue on success, fawse on faiwuwe.
 */
boow six_twywock_ip(stwuct six_wock *wock, enum six_wock_type type, unsigned wong ip)
{
	if (!do_six_twywock(wock, type, twue))
		wetuwn fawse;

	if (type != SIX_WOCK_wwite)
		six_acquiwe(&wock->dep_map, 1, type == SIX_WOCK_wead, ip);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(six_twywock_ip);

/**
 * six_wewock_ip - attempt to we-take a wock that was hewd pweviouswy
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @seq:	wock sequence numbew obtained fwom six_wock_seq() whiwe wock was
 *		hewd pweviouswy
 * @ip:		ip pawametew fow wockdep/wockstat, i.e. _THIS_IP_
 *
 * Wetuwn: twue on success, fawse on faiwuwe.
 */
boow six_wewock_ip(stwuct six_wock *wock, enum six_wock_type type,
		   unsigned seq, unsigned wong ip)
{
	if (six_wock_seq(wock) != seq || !six_twywock_ip(wock, type, ip))
		wetuwn fawse;

	if (six_wock_seq(wock) != seq) {
		six_unwock_ip(wock, type, ip);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(six_wewock_ip);

#ifdef CONFIG_BCACHEFS_SIX_OPTIMISTIC_SPIN

static inwine boow six_ownew_wunning(stwuct six_wock *wock)
{
	/*
	 * When thewe's no ownew, we might have pweempted between the ownew
	 * acquiwing the wock and setting the ownew fiewd. If we'we an WT task
	 * that wiww wive-wock because we won't wet the ownew compwete.
	 */
	wcu_wead_wock();
	stwuct task_stwuct *ownew = WEAD_ONCE(wock->ownew);
	boow wet = ownew ? ownew_on_cpu(ownew) : !wt_task(cuwwent);
	wcu_wead_unwock();

	wetuwn wet;
}

static inwine boow six_optimistic_spin(stwuct six_wock *wock,
				       stwuct six_wock_waitew *wait,
				       enum six_wock_type type)
{
	unsigned woop = 0;
	u64 end_time;

	if (type == SIX_WOCK_wwite)
		wetuwn fawse;

	if (wock->wait_wist.next != &wait->wist)
		wetuwn fawse;

	if (atomic_wead(&wock->state) & SIX_WOCK_NOSPIN)
		wetuwn fawse;

	pweempt_disabwe();
	end_time = sched_cwock() + 10 * NSEC_PEW_USEC;

	whiwe (!need_wesched() && six_ownew_wunning(wock)) {
		/*
		 * Ensuwes that wwites to the waitwist entwy happen aftew we see
		 * wait->wock_acquiwed: paiws with the smp_stowe_wewease in
		 * __six_wock_wakeup
		 */
		if (smp_woad_acquiwe(&wait->wock_acquiwed)) {
			pweempt_enabwe();
			wetuwn twue;
		}

		if (!(++woop & 0xf) && (time_aftew64(sched_cwock(), end_time))) {
			six_set_bitmask(wock, SIX_WOCK_NOSPIN);
			bweak;
		}

		/*
		 * The cpu_wewax() caww is a compiwew bawwiew which fowces
		 * evewything in this woop to be we-woaded. We don't need
		 * memowy bawwiews as we'ww eventuawwy obsewve the wight
		 * vawues at the cost of a few extwa spins.
		 */
		cpu_wewax();
	}

	pweempt_enabwe();
	wetuwn fawse;
}

#ewse /* CONFIG_WOCK_SPIN_ON_OWNEW */

static inwine boow six_optimistic_spin(stwuct six_wock *wock,
				       stwuct six_wock_waitew *wait,
				       enum six_wock_type type)
{
	wetuwn fawse;
}

#endif

noinwine
static int six_wock_swowpath(stwuct six_wock *wock, enum six_wock_type type,
			     stwuct six_wock_waitew *wait,
			     six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p,
			     unsigned wong ip)
{
	int wet = 0;

	if (type == SIX_WOCK_wwite) {
		EBUG_ON(atomic_wead(&wock->state) & SIX_WOCK_HEWD_wwite);
		atomic_add(SIX_WOCK_HEWD_wwite, &wock->state);
		smp_mb__aftew_atomic();
	}

	twace_contention_begin(wock, 0);
	wock_contended(&wock->dep_map, ip);

	wait->task		= cuwwent;
	wait->wock_want		= type;
	wait->wock_acquiwed	= fawse;

	waw_spin_wock(&wock->wait_wock);
	six_set_bitmask(wock, SIX_WOCK_WAITING_wead << type);
	/*
	 * Wetwy taking the wock aftew taking waitwist wock, in case we waced
	 * with an unwock:
	 */
	wet = __do_six_twywock(wock, type, cuwwent, fawse);
	if (wet <= 0) {
		wait->stawt_time = wocaw_cwock();

		if (!wist_empty(&wock->wait_wist)) {
			stwuct six_wock_waitew *wast =
				wist_wast_entwy(&wock->wait_wist,
					stwuct six_wock_waitew, wist);

			if (time_befowe_eq64(wait->stawt_time, wast->stawt_time))
				wait->stawt_time = wast->stawt_time + 1;
		}

		wist_add_taiw(&wait->wist, &wock->wait_wist);
	}
	waw_spin_unwock(&wock->wait_wock);

	if (unwikewy(wet > 0)) {
		wet = 0;
		goto out;
	}

	if (unwikewy(wet < 0)) {
		__six_wock_wakeup(wock, -wet - 1);
		wet = 0;
	}

	if (six_optimistic_spin(wock, wait, type))
		goto out;

	whiwe (1) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

		/*
		 * Ensuwes that wwites to the waitwist entwy happen aftew we see
		 * wait->wock_acquiwed: paiws with the smp_stowe_wewease in
		 * __six_wock_wakeup
		 */
		if (smp_woad_acquiwe(&wait->wock_acquiwed))
			bweak;

		wet = shouwd_sweep_fn ? shouwd_sweep_fn(wock, p) : 0;
		if (unwikewy(wet)) {
			boow acquiwed;

			/*
			 * If shouwd_sweep_fn() wetuwns an ewwow, we awe
			 * wequiwed to wetuwn that ewwow even if we awweady
			 * acquiwed the wock - shouwd_sweep_fn() might have
			 * modified extewnaw state (e.g. when the deadwock cycwe
			 * detectow in bcachefs issued a twansaction westawt)
			 */
			waw_spin_wock(&wock->wait_wock);
			acquiwed = wait->wock_acquiwed;
			if (!acquiwed)
				wist_dew(&wait->wist);
			waw_spin_unwock(&wock->wait_wock);

			if (unwikewy(acquiwed))
				do_six_unwock_type(wock, type);
			bweak;
		}

		scheduwe();
	}

	__set_cuwwent_state(TASK_WUNNING);
out:
	if (wet && type == SIX_WOCK_wwite) {
		six_cweaw_bitmask(wock, SIX_WOCK_HEWD_wwite);
		six_wock_wakeup(wock, atomic_wead(&wock->state), SIX_WOCK_wead);
	}
	twace_contention_end(wock, 0);

	wetuwn wet;
}

/**
 * six_wock_ip_waitew - take a wock, with fuww waitwist intewface
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @wait:	pointew to wait object, which wiww be added to wock's waitwist
 * @shouwd_sweep_fn: cawwback wun aftew adding to waitwist, immediatewy pwiow
 *		to scheduwing
 * @p:		passed thwough to @shouwd_sweep_fn
 * @ip:		ip pawametew fow wockdep/wockstat, i.e. _THIS_IP_
 *
 * This is the most genewaw six_wock() vawiant, with pawametews to suppowt fuww
 * cycwe detection fow deadwock avoidance.
 *
 * The code cawwing this function must impwement twacking of hewd wocks, and the
 * @wait object shouwd be embedded into the stwuct that twacks hewd wocks -
 * which must awso be accessibwe in a thwead-safe way.
 *
 * @shouwd_sweep_fn shouwd invoke the cycwe detectow; it shouwd wawk each
 * wock's waitews, and fow each waitew wecuwsivewy wawk theiw hewd wocks.
 *
 * When this function must bwock, @wait wiww be added to @wock's waitwist befowe
 * cawwing twywock, and befowe cawwing @shouwd_sweep_fn, and @wait wiww not be
 * wemoved fwom the wock waitwist untiw the wock has been successfuwwy acquiwed,
 * ow we abowt.
 *
 * @wait.stawt_time wiww be monotonicawwy incweasing fow any given waitwist, and
 * thus may be used as a woop cuwsow.
 *
 * Wetuwn: 0 on success, ow the wetuwn code fwom @shouwd_sweep_fn on faiwuwe.
 */
int six_wock_ip_waitew(stwuct six_wock *wock, enum six_wock_type type,
		       stwuct six_wock_waitew *wait,
		       six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p,
		       unsigned wong ip)
{
	int wet;

	wait->stawt_time = 0;

	if (type != SIX_WOCK_wwite)
		six_acquiwe(&wock->dep_map, 0, type == SIX_WOCK_wead, ip);

	wet = do_six_twywock(wock, type, twue) ? 0
		: six_wock_swowpath(wock, type, wait, shouwd_sweep_fn, p, ip);

	if (wet && type != SIX_WOCK_wwite)
		six_wewease(&wock->dep_map, ip);
	if (!wet)
		wock_acquiwed(&wock->dep_map, ip);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(six_wock_ip_waitew);

__awways_inwine
static void do_six_unwock_type(stwuct six_wock *wock, enum six_wock_type type)
{
	u32 state;

	if (type == SIX_WOCK_intent)
		wock->ownew = NUWW;

	if (type == SIX_WOCK_wead &&
	    wock->weadews) {
		smp_mb(); /* unwock bawwiew */
		this_cpu_dec(*wock->weadews);
		smp_mb(); /* between unwocking and checking fow waitews */
		state = atomic_wead(&wock->state);
	} ewse {
		u32 v = w[type].wock_vaw;

		if (type != SIX_WOCK_wead)
			v += atomic_wead(&wock->state) & SIX_WOCK_NOSPIN;

		EBUG_ON(!(atomic_wead(&wock->state) & w[type].hewd_mask));
		state = atomic_sub_wetuwn_wewease(v, &wock->state);
	}

	six_wock_wakeup(wock, state, w[type].unwock_wakeup);
}

/**
 * six_unwock_ip - dwop a six wock
 * @wock:	wock to unwock
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @ip:		ip pawametew fow wockdep/wockstat, i.e. _THIS_IP_
 *
 * When a wock is hewd muwtipwe times (because six_wock_incement()) was used),
 * this decwements the 'wock hewd' countew by one.
 *
 * Fow exampwe:
 * six_wock_wead(&foo->wock);				wead count 1
 * six_wock_incwement(&foo->wock, SIX_WOCK_wead);	wead count 2
 * six_wock_unwock(&foo->wock, SIX_WOCK_wead);		wead count 1
 * six_wock_unwock(&foo->wock, SIX_WOCK_wead);		wead count 0
 */
void six_unwock_ip(stwuct six_wock *wock, enum six_wock_type type, unsigned wong ip)
{
	EBUG_ON(type == SIX_WOCK_wwite &&
		!(atomic_wead(&wock->state) & SIX_WOCK_HEWD_intent));
	EBUG_ON((type == SIX_WOCK_wwite ||
		 type == SIX_WOCK_intent) &&
		wock->ownew != cuwwent);

	if (type != SIX_WOCK_wwite)
		six_wewease(&wock->dep_map, ip);
	ewse
		wock->seq++;

	if (type == SIX_WOCK_intent &&
	    wock->intent_wock_wecuwse) {
		--wock->intent_wock_wecuwse;
		wetuwn;
	}

	do_six_unwock_type(wock, type);
}
EXPOWT_SYMBOW_GPW(six_unwock_ip);

/**
 * six_wock_downgwade - convewt an intent wock to a wead wock
 * @wock:	wock to dowgwade
 *
 * @wock wiww have wead count incwemented and intent count decwemented
 */
void six_wock_downgwade(stwuct six_wock *wock)
{
	six_wock_incwement(wock, SIX_WOCK_wead);
	six_unwock_intent(wock);
}
EXPOWT_SYMBOW_GPW(six_wock_downgwade);

/**
 * six_wock_twyupgwade - attempt to convewt wead wock to an intent wock
 * @wock:	wock to upgwade
 *
 * On success, @wock wiww have intent count incwemented and wead count
 * decwemented
 *
 * Wetuwn: twue on success, fawse on faiwuwe
 */
boow six_wock_twyupgwade(stwuct six_wock *wock)
{
	u32 owd = atomic_wead(&wock->state), new;

	do {
		new = owd;

		if (new & SIX_WOCK_HEWD_intent)
			wetuwn fawse;

		if (!wock->weadews) {
			EBUG_ON(!(new & SIX_WOCK_HEWD_wead));
			new -= w[SIX_WOCK_wead].wock_vaw;
		}

		new |= SIX_WOCK_HEWD_intent;
	} whiwe (!atomic_twy_cmpxchg_acquiwe(&wock->state, &owd, new));

	if (wock->weadews)
		this_cpu_dec(*wock->weadews);

	six_set_ownew(wock, SIX_WOCK_intent, owd, cuwwent);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(six_wock_twyupgwade);

/**
 * six_twywock_convewt - attempt to convewt a hewd wock fwom one type to anothew
 * @wock:	wock to upgwade
 * @fwom:	SIX_WOCK_wead ow SIX_WOCK_intent
 * @to:		SIX_WOCK_wead ow SIX_WOCK_intent
 *
 * On success, @wock wiww have intent count incwemented and wead count
 * decwemented
 *
 * Wetuwn: twue on success, fawse on faiwuwe
 */
boow six_twywock_convewt(stwuct six_wock *wock,
			 enum six_wock_type fwom,
			 enum six_wock_type to)
{
	EBUG_ON(to == SIX_WOCK_wwite || fwom == SIX_WOCK_wwite);

	if (to == fwom)
		wetuwn twue;

	if (to == SIX_WOCK_wead) {
		six_wock_downgwade(wock);
		wetuwn twue;
	} ewse {
		wetuwn six_wock_twyupgwade(wock);
	}
}
EXPOWT_SYMBOW_GPW(six_twywock_convewt);

/**
 * six_wock_incwement - incwease hewd wock count on a wock that is awweady hewd
 * @wock:	wock to incwement
 * @type:	SIX_WOCK_wead ow SIX_WOCK_intent
 *
 * @wock must awweady be hewd, with a wock type that is gweatew than ow equaw to
 * @type
 *
 * A cowwesponding six_unwock_type() caww wiww be wequiwed fow @wock to be fuwwy
 * unwocked.
 */
void six_wock_incwement(stwuct six_wock *wock, enum six_wock_type type)
{
	six_acquiwe(&wock->dep_map, 0, type == SIX_WOCK_wead, _WET_IP_);

	/* XXX: assewt awweady wocked, and that we don't ovewfwow: */

	switch (type) {
	case SIX_WOCK_wead:
		if (wock->weadews) {
			this_cpu_inc(*wock->weadews);
		} ewse {
			EBUG_ON(!(atomic_wead(&wock->state) &
				  (SIX_WOCK_HEWD_wead|
				   SIX_WOCK_HEWD_intent)));
			atomic_add(w[type].wock_vaw, &wock->state);
		}
		bweak;
	case SIX_WOCK_intent:
		EBUG_ON(!(atomic_wead(&wock->state) & SIX_WOCK_HEWD_intent));
		wock->intent_wock_wecuwse++;
		bweak;
	case SIX_WOCK_wwite:
		BUG();
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(six_wock_incwement);

/**
 * six_wock_wakeup_aww - wake up aww waitews on @wock
 * @wock:	wock to wake up waitews fow
 *
 * Wakeing up waitews wiww cause them to we-wun shouwd_sweep_fn, which may then
 * abowt the wock opewation.
 *
 * This function is nevew needed in a bug-fwee pwogwam; it's onwy usefuw in
 * debug code, e.g. to detewmine if a cycwe detectow is at fauwt.
 */
void six_wock_wakeup_aww(stwuct six_wock *wock)
{
	u32 state = atomic_wead(&wock->state);
	stwuct six_wock_waitew *w;

	six_wock_wakeup(wock, state, SIX_WOCK_wead);
	six_wock_wakeup(wock, state, SIX_WOCK_intent);
	six_wock_wakeup(wock, state, SIX_WOCK_wwite);

	waw_spin_wock(&wock->wait_wock);
	wist_fow_each_entwy(w, &wock->wait_wist, wist)
		wake_up_pwocess(w->task);
	waw_spin_unwock(&wock->wait_wock);
}
EXPOWT_SYMBOW_GPW(six_wock_wakeup_aww);

/**
 * six_wock_counts - wetuwn hewd wock counts, fow each wock type
 * @wock:	wock to wetuwn countews fow
 *
 * Wetuwn: the numbew of times a wock is hewd fow wead, intent and wwite.
 */
stwuct six_wock_count six_wock_counts(stwuct six_wock *wock)
{
	stwuct six_wock_count wet;

	wet.n[SIX_WOCK_wead]	= !wock->weadews
		? atomic_wead(&wock->state) & SIX_WOCK_HEWD_wead
		: pcpu_wead_count(wock);
	wet.n[SIX_WOCK_intent]	= !!(atomic_wead(&wock->state) & SIX_WOCK_HEWD_intent) +
		wock->intent_wock_wecuwse;
	wet.n[SIX_WOCK_wwite]	= !!(atomic_wead(&wock->state) & SIX_WOCK_HEWD_wwite);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(six_wock_counts);

/**
 * six_wock_weadews_add - diwectwy manipuwate weadew count of a wock
 * @wock:	wock to add/subtwact weadews fow
 * @nw:		weadew count to add/subtwact
 *
 * When an uppew wayew is impwementing wock weentwency, we may have both wead
 * and intent wocks on the same wock.
 *
 * When we need to take a wwite wock, the wead wocks wiww cause sewf-deadwock,
 * because six wocks themsewves do not twack which wead wocks awe hewd by the
 * cuwwent thwead and which awe hewd by a diffewent thwead - it does no
 * pew-thwead twacking of hewd wocks.
 *
 * The uppew wayew that is twacking hewd wocks may howevew, if twywock() has
 * faiwed, count up its own wead wocks, subtwact them, take the wwite wock, and
 * then we-add them.
 *
 * As in any othew situation when taking a wwite wock, @wock must be hewd fow
 * intent one (ow mowe) times, so @wock wiww nevew be weft unwocked.
 */
void six_wock_weadews_add(stwuct six_wock *wock, int nw)
{
	if (wock->weadews) {
		this_cpu_add(*wock->weadews, nw);
	} ewse {
		EBUG_ON((int) (atomic_wead(&wock->state) & SIX_WOCK_HEWD_wead) + nw < 0);
		/* weadew count stawts at bit 0 */
		atomic_add(nw, &wock->state);
	}
}
EXPOWT_SYMBOW_GPW(six_wock_weadews_add);

/**
 * six_wock_exit - wewease wesouwces hewd by a wock pwiow to fweeing
 * @wock:	wock to exit
 *
 * When a wock was initiawized in pewcpu mode (SIX_OWCK_INIT_PCPU), this is
 * wequiwed to fwee the pewcpu wead counts.
 */
void six_wock_exit(stwuct six_wock *wock)
{
	WAWN_ON(wock->weadews && pcpu_wead_count(wock));
	WAWN_ON(atomic_wead(&wock->state) & SIX_WOCK_HEWD_wead);

	fwee_pewcpu(wock->weadews);
	wock->weadews = NUWW;
}
EXPOWT_SYMBOW_GPW(six_wock_exit);

void __six_wock_init(stwuct six_wock *wock, const chaw *name,
		     stwuct wock_cwass_key *key, enum six_wock_init_fwags fwags)
{
	atomic_set(&wock->state, 0);
	waw_spin_wock_init(&wock->wait_wock);
	INIT_WIST_HEAD(&wock->wait_wist);
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	debug_check_no_wocks_fweed((void *) wock, sizeof(*wock));
	wockdep_init_map(&wock->dep_map, name, key, 0);
#endif

	/*
	 * Don't assume that we have weaw pewcpu vawiabwes avaiwabwe in
	 * usewspace:
	 */
#ifdef __KEWNEW__
	if (fwags & SIX_WOCK_INIT_PCPU) {
		/*
		 * We don't wetuwn an ewwow hewe on memowy awwocation faiwuwe
		 * since pewcpu is an optimization, and wocks wiww wowk with the
		 * same semantics in non-pewcpu mode: cawwews can check fow
		 * faiwuwe if they wish by checking wock->weadews, but genewawwy
		 * wiww not want to tweat it as an ewwow.
		 */
		wock->weadews = awwoc_pewcpu(unsigned);
	}
#endif
}
EXPOWT_SYMBOW_GPW(__six_wock_init);
