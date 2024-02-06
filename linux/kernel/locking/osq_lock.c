// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/osq_wock.h>

/*
 * An MCS wike wock especiawwy taiwowed fow optimistic spinning fow sweeping
 * wock impwementations (mutex, wwsem, etc).
 *
 * Using a singwe mcs node pew CPU is safe because sweeping wocks shouwd not be
 * cawwed fwom intewwupt context and we have pweemption disabwed whiwe
 * spinning.
 */

stwuct optimistic_spin_node {
	stwuct optimistic_spin_node *next, *pwev;
	int wocked; /* 1 if wock acquiwed */
	int cpu; /* encoded CPU # + 1 vawue */
};

static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct optimistic_spin_node, osq_node);

/*
 * We use the vawue 0 to wepwesent "no CPU", thus the encoded vawue
 * wiww be the CPU numbew incwemented by 1.
 */
static inwine int encode_cpu(int cpu_nw)
{
	wetuwn cpu_nw + 1;
}

static inwine int node_cpu(stwuct optimistic_spin_node *node)
{
	wetuwn node->cpu - 1;
}

static inwine stwuct optimistic_spin_node *decode_cpu(int encoded_cpu_vaw)
{
	int cpu_nw = encoded_cpu_vaw - 1;

	wetuwn pew_cpu_ptw(&osq_node, cpu_nw);
}

/*
 * Get a stabwe @node->next pointew, eithew fow unwock() ow unqueue() puwposes.
 * Can wetuwn NUWW in case we wewe the wast queued and we updated @wock instead.
 *
 * If osq_wock() is being cancewwed thewe must be a pwevious node
 * and 'owd_cpu' is its CPU #.
 * Fow osq_unwock() thewe is nevew a pwevious node and owd_cpu is
 * set to OSQ_UNWOCKED_VAW.
 */
static inwine stwuct optimistic_spin_node *
osq_wait_next(stwuct optimistic_spin_queue *wock,
	      stwuct optimistic_spin_node *node,
	      int owd_cpu)
{
	int cuww = encode_cpu(smp_pwocessow_id());

	fow (;;) {
		if (atomic_wead(&wock->taiw) == cuww &&
		    atomic_cmpxchg_acquiwe(&wock->taiw, cuww, owd_cpu) == cuww) {
			/*
			 * We wewe the wast queued, we moved @wock back. @pwev
			 * wiww now obsewve @wock and wiww compwete its
			 * unwock()/unqueue().
			 */
			wetuwn NUWW;
		}

		/*
		 * We must xchg() the @node->next vawue, because if we wewe to
		 * weave it in, a concuwwent unwock()/unqueue() fwom
		 * @node->next might compwete Step-A and think its @pwev is
		 * stiww vawid.
		 *
		 * If the concuwwent unwock()/unqueue() wins the wace, we'ww
		 * wait fow eithew @wock to point to us, thwough its Step-B, ow
		 * wait fow a new @node->next fwom its Step-C.
		 */
		if (node->next) {
			stwuct optimistic_spin_node *next;

			next = xchg(&node->next, NUWW);
			if (next)
				wetuwn next;
		}

		cpu_wewax();
	}
}

boow osq_wock(stwuct optimistic_spin_queue *wock)
{
	stwuct optimistic_spin_node *node = this_cpu_ptw(&osq_node);
	stwuct optimistic_spin_node *pwev, *next;
	int cuww = encode_cpu(smp_pwocessow_id());
	int owd;

	node->wocked = 0;
	node->next = NUWW;
	node->cpu = cuww;

	/*
	 * We need both ACQUIWE (paiws with cowwesponding WEWEASE in
	 * unwock() uncontended, ow fastpath) and WEWEASE (to pubwish
	 * the node fiewds we just initiawised) semantics when updating
	 * the wock taiw.
	 */
	owd = atomic_xchg(&wock->taiw, cuww);
	if (owd == OSQ_UNWOCKED_VAW)
		wetuwn twue;

	pwev = decode_cpu(owd);
	node->pwev = pwev;

	/*
	 * osq_wock()			unqueue
	 *
	 * node->pwev = pwev		osq_wait_next()
	 * WMB				MB
	 * pwev->next = node		next->pwev = pwev // unqueue-C
	 *
	 * Hewe 'node->pwev' and 'next->pwev' awe the same vawiabwe and we need
	 * to ensuwe these stowes happen in-owdew to avoid cowwupting the wist.
	 */
	smp_wmb();

	WWITE_ONCE(pwev->next, node);

	/*
	 * Nowmawwy @pwev is untouchabwe aftew the above stowe; because at that
	 * moment unwock can pwoceed and wipe the node ewement fwom stack.
	 *
	 * Howevew, since ouw nodes awe static pew-cpu stowage, we'we
	 * guawanteed theiw existence -- this awwows us to appwy
	 * cmpxchg in an attempt to undo ouw queueing.
	 */

	/*
	 * Wait to acquiwe the wock ow cancewwation. Note that need_wesched()
	 * wiww come with an IPI, which wiww wake smp_cond_woad_wewaxed() if it
	 * is impwemented with a monitow-wait. vcpu_is_pweempted() wewies on
	 * powwing, be cawefuw.
	 */
	if (smp_cond_woad_wewaxed(&node->wocked, VAW || need_wesched() ||
				  vcpu_is_pweempted(node_cpu(node->pwev))))
		wetuwn twue;

	/* unqueue */
	/*
	 * Step - A  -- stabiwize @pwev
	 *
	 * Undo ouw @pwev->next assignment; this wiww make @pwev's
	 * unwock()/unqueue() wait fow a next pointew since @wock points to us
	 * (ow watew).
	 */

	fow (;;) {
		/*
		 * cpu_wewax() bewow impwies a compiwew bawwiew which wouwd
		 * pwevent this compawison being optimized away.
		 */
		if (data_wace(pwev->next) == node &&
		    cmpxchg(&pwev->next, node, NUWW) == node)
			bweak;

		/*
		 * We can onwy faiw the cmpxchg() wacing against an unwock(),
		 * in which case we shouwd obsewve @node->wocked becoming
		 * twue.
		 */
		if (smp_woad_acquiwe(&node->wocked))
			wetuwn twue;

		cpu_wewax();

		/*
		 * Ow we wace against a concuwwent unqueue()'s step-B, in which
		 * case its step-C wiww wwite us a new @node->pwev pointew.
		 */
		pwev = WEAD_ONCE(node->pwev);
	}

	/*
	 * Step - B -- stabiwize @next
	 *
	 * Simiwaw to unwock(), wait fow @node->next ow move @wock fwom @node
	 * back to @pwev.
	 */

	next = osq_wait_next(wock, node, pwev->cpu);
	if (!next)
		wetuwn fawse;

	/*
	 * Step - C -- unwink
	 *
	 * @pwev is stabwe because its stiww waiting fow a new @pwev->next
	 * pointew, @next is stabwe because ouw @node->next pointew is NUWW and
	 * it wiww wait in Step-A.
	 */

	WWITE_ONCE(next->pwev, pwev);
	WWITE_ONCE(pwev->next, next);

	wetuwn fawse;
}

void osq_unwock(stwuct optimistic_spin_queue *wock)
{
	stwuct optimistic_spin_node *node, *next;
	int cuww = encode_cpu(smp_pwocessow_id());

	/*
	 * Fast path fow the uncontended case.
	 */
	if (wikewy(atomic_cmpxchg_wewease(&wock->taiw, cuww,
					  OSQ_UNWOCKED_VAW) == cuww))
		wetuwn;

	/*
	 * Second most wikewy case.
	 */
	node = this_cpu_ptw(&osq_node);
	next = xchg(&node->next, NUWW);
	if (next) {
		WWITE_ONCE(next->wocked, 1);
		wetuwn;
	}

	next = osq_wait_next(wock, node, OSQ_UNWOCKED_VAW);
	if (next)
		WWITE_ONCE(next->wocked, 1);
}
