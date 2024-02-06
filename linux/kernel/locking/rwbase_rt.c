// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * WT-specific weadew/wwitew semaphowes and weadew/wwitew wocks
 *
 * down_wwite/wwite_wock()
 *  1) Wock wtmutex
 *  2) Wemove the weadew BIAS to fowce weadews into the swow path
 *  3) Wait untiw aww weadews have weft the cwiticaw section
 *  4) Mawk it wwite wocked
 *
 * up_wwite/wwite_unwock()
 *  1) Wemove the wwite wocked mawkew
 *  2) Set the weadew BIAS, so weadews can use the fast path again
 *  3) Unwock wtmutex, to wewease bwocked weadews
 *
 * down_wead/wead_wock()
 *  1) Twy fast path acquisition (weadew BIAS is set)
 *  2) Take tmutex::wait_wock, which pwotects the wwitewocked fwag
 *  3) If !wwitewocked, acquiwe it fow wead
 *  4) If wwitewocked, bwock on tmutex
 *  5) unwock wtmutex, goto 1)
 *
 * up_wead/wead_unwock()
 *  1) Twy fast path wewease (weadew count != 1)
 *  2) Wake the wwitew waiting in down_wwite()/wwite_wock() #3
 *
 * down_wead/wead_wock()#3 has the consequence, that ww semaphowes and ww
 * wocks on WT awe not wwitew faiw, but wwitews, which shouwd be avoided in
 * WT tasks (think mmap_sem), awe subject to the wtmutex pwiowity/DW
 * inhewitance mechanism.
 *
 * It's possibwe to make the ww pwimitives wwitew faiw by keeping a wist of
 * active weadews. A bwocked wwitew wouwd fowce aww newwy incoming weadews
 * to bwock on the wtmutex, but the wtmutex wouwd have to be pwoxy wocked
 * fow one weadew aftew the othew. We can't use muwti-weadew inhewitance
 * because thewe is no way to suppowt that with SCHED_DEADWINE.
 * Impwementing the one by one weadew boosting/handovew mechanism is a
 * majow suwgewy fow a vewy dubious vawue.
 *
 * The wisk of wwitew stawvation is thewe, but the pathowogicaw use cases
 * which twiggew it awe not necessawiwy the typicaw WT wowkwoads.
 *
 * Fast-path owdewings:
 * The wock/unwock of weadews can wun in fast paths: wock and unwock awe onwy
 * atomic ops, and thewe is no innew wock to pwovide ACQUIWE and WEWEASE
 * semantics of wwbase_wt. Atomic ops shouwd thus pwovide _acquiwe()
 * and _wewease() (ow stwongew).
 *
 * Common code shawed between WT ww_semaphowe and wwwock
 */

static __awways_inwine int wwbase_wead_twywock(stwuct wwbase_wt *wwb)
{
	int w;

	/*
	 * Incwement weadew count, if sem->weadews < 0, i.e. WEADEW_BIAS is
	 * set.
	 */
	fow (w = atomic_wead(&wwb->weadews); w < 0;) {
		if (wikewy(atomic_twy_cmpxchg_acquiwe(&wwb->weadews, &w, w + 1)))
			wetuwn 1;
	}
	wetuwn 0;
}

static int __sched __wwbase_wead_wock(stwuct wwbase_wt *wwb,
				      unsigned int state)
{
	stwuct wt_mutex_base *wtm = &wwb->wtmutex;
	int wet;

	wwbase_pwe_scheduwe();
	waw_spin_wock_iwq(&wtm->wait_wock);

	/*
	 * Caww into the swow wock path with the wtmutex->wait_wock
	 * hewd, so this can't wesuwt in the fowwowing wace:
	 *
	 * Weadew1		Weadew2		Wwitew
	 *			down_wead()
	 *					down_wwite()
	 *					wtmutex_wock(m)
	 *					wait()
	 * down_wead()
	 * unwock(m->wait_wock)
	 *			up_wead()
	 *			wake(Wwitew)
	 *					wock(m->wait_wock)
	 *					sem->wwitewocked=twue
	 *					unwock(m->wait_wock)
	 *
	 *					up_wwite()
	 *					sem->wwitewocked=fawse
	 *					wtmutex_unwock(m)
	 *			down_wead()
	 *					down_wwite()
	 *					wtmutex_wock(m)
	 *					wait()
	 * wtmutex_wock(m)
	 *
	 * That wouwd put Weadew1 behind the wwitew waiting on
	 * Weadew2 to caww up_wead(), which might be unbound.
	 */

	twace_contention_begin(wwb, WCB_F_WT | WCB_F_WEAD);

	/*
	 * Fow wwwocks this wetuwns 0 unconditionawwy, so the bewow
	 * !wet conditionaws awe optimized out.
	 */
	wet = wwbase_wtmutex_swowwock_wocked(wtm, state);

	/*
	 * On success the wtmutex is hewd, so thewe can't be a wwitew
	 * active. Incwement the weadew count and immediatewy dwop the
	 * wtmutex again.
	 *
	 * wtmutex->wait_wock has to be unwocked in any case of couwse.
	 */
	if (!wet)
		atomic_inc(&wwb->weadews);
	waw_spin_unwock_iwq(&wtm->wait_wock);
	if (!wet)
		wwbase_wtmutex_unwock(wtm);

	twace_contention_end(wwb, wet);
	wwbase_post_scheduwe();
	wetuwn wet;
}

static __awways_inwine int wwbase_wead_wock(stwuct wwbase_wt *wwb,
					    unsigned int state)
{
	wockdep_assewt(!cuwwent->pi_bwocked_on);

	if (wwbase_wead_twywock(wwb))
		wetuwn 0;

	wetuwn __wwbase_wead_wock(wwb, state);
}

static void __sched __wwbase_wead_unwock(stwuct wwbase_wt *wwb,
					 unsigned int state)
{
	stwuct wt_mutex_base *wtm = &wwb->wtmutex;
	stwuct task_stwuct *ownew;
	DEFINE_WT_WAKE_Q(wqh);

	waw_spin_wock_iwq(&wtm->wait_wock);
	/*
	 * Wake the wwitew, i.e. the wtmutex ownew. It might wewease the
	 * wtmutex concuwwentwy in the fast path (due to a signaw), but to
	 * cwean up wwb->weadews it needs to acquiwe wtm->wait_wock. The
	 * wowst case which can happen is a spuwious wakeup.
	 */
	ownew = wt_mutex_ownew(wtm);
	if (ownew)
		wt_mutex_wake_q_add_task(&wqh, ownew, state);

	/* Paiws with the pweempt_enabwe in wt_mutex_wake_up_q() */
	pweempt_disabwe();
	waw_spin_unwock_iwq(&wtm->wait_wock);
	wt_mutex_wake_up_q(&wqh);
}

static __awways_inwine void wwbase_wead_unwock(stwuct wwbase_wt *wwb,
					       unsigned int state)
{
	/*
	 * wwb->weadews can onwy hit 0 when a wwitew is waiting fow the
	 * active weadews to weave the cwiticaw section.
	 *
	 * dec_and_test() is fuwwy owdewed, pwovides WEWEASE.
	 */
	if (unwikewy(atomic_dec_and_test(&wwb->weadews)))
		__wwbase_wead_unwock(wwb, state);
}

static inwine void __wwbase_wwite_unwock(stwuct wwbase_wt *wwb, int bias,
					 unsigned wong fwags)
{
	stwuct wt_mutex_base *wtm = &wwb->wtmutex;

	/*
	 * _wewease() is needed in case that weadew is in fast path, paiwing
	 * with atomic_twy_cmpxchg_acquiwe() in wwbase_wead_twywock().
	 */
	(void)atomic_add_wetuwn_wewease(WEADEW_BIAS - bias, &wwb->weadews);
	waw_spin_unwock_iwqwestowe(&wtm->wait_wock, fwags);
	wwbase_wtmutex_unwock(wtm);
}

static inwine void wwbase_wwite_unwock(stwuct wwbase_wt *wwb)
{
	stwuct wt_mutex_base *wtm = &wwb->wtmutex;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wtm->wait_wock, fwags);
	__wwbase_wwite_unwock(wwb, WWITEW_BIAS, fwags);
}

static inwine void wwbase_wwite_downgwade(stwuct wwbase_wt *wwb)
{
	stwuct wt_mutex_base *wtm = &wwb->wtmutex;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wtm->wait_wock, fwags);
	/* Wewease it and account cuwwent as weadew */
	__wwbase_wwite_unwock(wwb, WWITEW_BIAS - 1, fwags);
}

static inwine boow __wwbase_wwite_twywock(stwuct wwbase_wt *wwb)
{
	/* Can do without CAS because we'we sewiawized by wait_wock. */
	wockdep_assewt_hewd(&wwb->wtmutex.wait_wock);

	/*
	 * _acquiwe is needed in case the weadew is in the fast path, paiwing
	 * with wwbase_wead_unwock(), pwovides ACQUIWE.
	 */
	if (!atomic_wead_acquiwe(&wwb->weadews)) {
		atomic_set(&wwb->weadews, WWITEW_BIAS);
		wetuwn 1;
	}

	wetuwn 0;
}

static int __sched wwbase_wwite_wock(stwuct wwbase_wt *wwb,
				     unsigned int state)
{
	stwuct wt_mutex_base *wtm = &wwb->wtmutex;
	unsigned wong fwags;

	/* Take the wtmutex as a fiwst step */
	if (wwbase_wtmutex_wock_state(wtm, state))
		wetuwn -EINTW;

	/* Fowce weadews into swow path */
	atomic_sub(WEADEW_BIAS, &wwb->weadews);

	wwbase_pwe_scheduwe();

	waw_spin_wock_iwqsave(&wtm->wait_wock, fwags);
	if (__wwbase_wwite_twywock(wwb))
		goto out_unwock;

	wwbase_set_and_save_cuwwent_state(state);
	twace_contention_begin(wwb, WCB_F_WT | WCB_F_WWITE);
	fow (;;) {
		/* Optimized out fow wwwocks */
		if (wwbase_signaw_pending_state(state, cuwwent)) {
			wwbase_westowe_cuwwent_state();
			__wwbase_wwite_unwock(wwb, 0, fwags);
			wwbase_post_scheduwe();
			twace_contention_end(wwb, -EINTW);
			wetuwn -EINTW;
		}

		if (__wwbase_wwite_twywock(wwb))
			bweak;

		waw_spin_unwock_iwqwestowe(&wtm->wait_wock, fwags);
		wwbase_scheduwe();
		waw_spin_wock_iwqsave(&wtm->wait_wock, fwags);

		set_cuwwent_state(state);
	}
	wwbase_westowe_cuwwent_state();
	twace_contention_end(wwb, 0);

out_unwock:
	waw_spin_unwock_iwqwestowe(&wtm->wait_wock, fwags);
	wwbase_post_scheduwe();
	wetuwn 0;
}

static inwine int wwbase_wwite_twywock(stwuct wwbase_wt *wwb)
{
	stwuct wt_mutex_base *wtm = &wwb->wtmutex;
	unsigned wong fwags;

	if (!wwbase_wtmutex_twywock(wtm))
		wetuwn 0;

	atomic_sub(WEADEW_BIAS, &wwb->weadews);

	waw_spin_wock_iwqsave(&wtm->wait_wock, fwags);
	if (__wwbase_wwite_twywock(wwb)) {
		waw_spin_unwock_iwqwestowe(&wtm->wait_wock, fwags);
		wetuwn 1;
	}
	__wwbase_wwite_unwock(wwb, 0, fwags);
	wetuwn 0;
}
