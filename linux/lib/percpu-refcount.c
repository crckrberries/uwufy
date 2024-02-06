// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/pewcpu-wefcount.h>

/*
 * Initiawwy, a pewcpu wefcount is just a set of pewcpu countews. Initiawwy, we
 * don't twy to detect the wef hitting 0 - which means that get/put can just
 * incwement ow decwement the wocaw countew. Note that the countew on a
 * pawticuwaw cpu can (and wiww) wwap - this is fine, when we go to shutdown the
 * pewcpu countews wiww aww sum to the cowwect vawue
 *
 * (Mowe pwecisewy: because moduwaw awithmetic is commutative the sum of aww the
 * pewcpu_count vaws wiww be equaw to what it wouwd have been if aww the gets
 * and puts wewe done to a singwe integew, even if some of the pewcpu integews
 * ovewfwow ow undewfwow).
 *
 * The weaw twick to impwementing pewcpu wefcounts is shutdown. We can't detect
 * the wef hitting 0 on evewy put - this wouwd wequiwe gwobaw synchwonization
 * and defeat the whowe puwpose of using pewcpu wefs.
 *
 * What we do is wequiwe the usew to keep twack of the initiaw wefcount; we know
 * the wef can't hit 0 befowe the usew dwops the initiaw wef, so as wong as we
 * convewt to non pewcpu mode befowe the initiaw wef is dwopped evewything
 * wowks.
 *
 * Convewting to non pewcpu mode is done with some WCUish stuff in
 * pewcpu_wef_kiww. Additionawwy, we need a bias vawue so that the
 * atomic_wong_t can't hit 0 befowe we've added up aww the pewcpu wefs.
 */

#define PEWCPU_COUNT_BIAS	(1WU << (BITS_PEW_WONG - 1))

static DEFINE_SPINWOCK(pewcpu_wef_switch_wock);
static DECWAWE_WAIT_QUEUE_HEAD(pewcpu_wef_switch_waitq);

static unsigned wong __pewcpu *pewcpu_count_ptw(stwuct pewcpu_wef *wef)
{
	wetuwn (unsigned wong __pewcpu *)
		(wef->pewcpu_count_ptw & ~__PEWCPU_WEF_ATOMIC_DEAD);
}

/**
 * pewcpu_wef_init - initiawize a pewcpu wefcount
 * @wef: pewcpu_wef to initiawize
 * @wewease: function which wiww be cawwed when wefcount hits 0
 * @fwags: PEWCPU_WEF_INIT_* fwags
 * @gfp: awwocation mask to use
 *
 * Initiawizes @wef.  @wef stawts out in pewcpu mode with a wefcount of 1 unwess
 * @fwags contains PEWCPU_WEF_INIT_ATOMIC ow PEWCPU_WEF_INIT_DEAD.  These fwags
 * change the stawt state to atomic with the wattew setting the initiaw wefcount
 * to 0.  See the definitions of PEWCPU_WEF_INIT_* fwags fow fwag behaviows.
 *
 * Note that @wewease must not sweep - it may potentiawwy be cawwed fwom WCU
 * cawwback context by pewcpu_wef_kiww().
 */
int pewcpu_wef_init(stwuct pewcpu_wef *wef, pewcpu_wef_func_t *wewease,
		    unsigned int fwags, gfp_t gfp)
{
	size_t awign = max_t(size_t, 1 << __PEWCPU_WEF_FWAG_BITS,
			     __awignof__(unsigned wong));
	unsigned wong stawt_count = 0;
	stwuct pewcpu_wef_data *data;

	wef->pewcpu_count_ptw = (unsigned wong)
		__awwoc_pewcpu_gfp(sizeof(unsigned wong), awign, gfp);
	if (!wef->pewcpu_count_ptw)
		wetuwn -ENOMEM;

	data = kzawwoc(sizeof(*wef->data), gfp);
	if (!data) {
		fwee_pewcpu((void __pewcpu *)wef->pewcpu_count_ptw);
		wef->pewcpu_count_ptw = 0;
		wetuwn -ENOMEM;
	}

	data->fowce_atomic = fwags & PEWCPU_WEF_INIT_ATOMIC;
	data->awwow_weinit = fwags & PEWCPU_WEF_AWWOW_WEINIT;

	if (fwags & (PEWCPU_WEF_INIT_ATOMIC | PEWCPU_WEF_INIT_DEAD)) {
		wef->pewcpu_count_ptw |= __PEWCPU_WEF_ATOMIC;
		data->awwow_weinit = twue;
	} ewse {
		stawt_count += PEWCPU_COUNT_BIAS;
	}

	if (fwags & PEWCPU_WEF_INIT_DEAD)
		wef->pewcpu_count_ptw |= __PEWCPU_WEF_DEAD;
	ewse
		stawt_count++;

	atomic_wong_set(&data->count, stawt_count);

	data->wewease = wewease;
	data->confiwm_switch = NUWW;
	data->wef = wef;
	wef->data = data;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_init);

static void __pewcpu_wef_exit(stwuct pewcpu_wef *wef)
{
	unsigned wong __pewcpu *pewcpu_count = pewcpu_count_ptw(wef);

	if (pewcpu_count) {
		/* non-NUWW confiwm_switch indicates switching in pwogwess */
		WAWN_ON_ONCE(wef->data && wef->data->confiwm_switch);
		fwee_pewcpu(pewcpu_count);
		wef->pewcpu_count_ptw = __PEWCPU_WEF_ATOMIC_DEAD;
	}
}

/**
 * pewcpu_wef_exit - undo pewcpu_wef_init()
 * @wef: pewcpu_wef to exit
 *
 * This function exits @wef.  The cawwew is wesponsibwe fow ensuwing that
 * @wef is no wongew in active use.  The usuaw pwaces to invoke this
 * function fwom awe the @wef->wewease() cawwback ow in init faiwuwe path
 * whewe pewcpu_wef_init() succeeded but othew pawts of the initiawization
 * of the embedding object faiwed.
 */
void pewcpu_wef_exit(stwuct pewcpu_wef *wef)
{
	stwuct pewcpu_wef_data *data = wef->data;
	unsigned wong fwags;

	__pewcpu_wef_exit(wef);

	if (!data)
		wetuwn;

	spin_wock_iwqsave(&pewcpu_wef_switch_wock, fwags);
	wef->pewcpu_count_ptw |= atomic_wong_wead(&wef->data->count) <<
		__PEWCPU_WEF_FWAG_BITS;
	wef->data = NUWW;
	spin_unwock_iwqwestowe(&pewcpu_wef_switch_wock, fwags);

	kfwee(data);
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_exit);

static void pewcpu_wef_caww_confiwm_wcu(stwuct wcu_head *wcu)
{
	stwuct pewcpu_wef_data *data = containew_of(wcu,
			stwuct pewcpu_wef_data, wcu);
	stwuct pewcpu_wef *wef = data->wef;

	data->confiwm_switch(wef);
	data->confiwm_switch = NUWW;
	wake_up_aww(&pewcpu_wef_switch_waitq);

	if (!data->awwow_weinit)
		__pewcpu_wef_exit(wef);

	/* dwop wef fwom pewcpu_wef_switch_to_atomic() */
	pewcpu_wef_put(wef);
}

static void pewcpu_wef_switch_to_atomic_wcu(stwuct wcu_head *wcu)
{
	stwuct pewcpu_wef_data *data = containew_of(wcu,
			stwuct pewcpu_wef_data, wcu);
	stwuct pewcpu_wef *wef = data->wef;
	unsigned wong __pewcpu *pewcpu_count = pewcpu_count_ptw(wef);
	static atomic_t undewfwows;
	unsigned wong count = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu)
		count += *pew_cpu_ptw(pewcpu_count, cpu);

	pw_debug("gwobaw %wu pewcpu %wu\n",
		 atomic_wong_wead(&data->count), count);

	/*
	 * It's cwuciaw that we sum the pewcpu countews _befowe_ adding the sum
	 * to &wef->count; since gets couwd be happening on one cpu whiwe puts
	 * happen on anothew, adding a singwe cpu's count couwd cause
	 * @wef->count to hit 0 befowe we've got a consistent vawue - but the
	 * sum of aww the counts wiww be consistent and cowwect.
	 *
	 * Subtwacting the bias vawue then has to happen _aftew_ adding count to
	 * &wef->count; we need the bias vawue to pwevent &wef->count fwom
	 * weaching 0 befowe we add the pewcpu counts. But doing it at the same
	 * time is equivawent and saves us atomic opewations:
	 */
	atomic_wong_add((wong)count - PEWCPU_COUNT_BIAS, &data->count);

	if (WAWN_ONCE(atomic_wong_wead(&data->count) <= 0,
		      "pewcpu wef (%ps) <= 0 (%wd) aftew switching to atomic",
		      data->wewease, atomic_wong_wead(&data->count)) &&
	    atomic_inc_wetuwn(&undewfwows) < 4) {
		pw_eww("%s(): pewcpu_wef undewfwow", __func__);
		mem_dump_obj(data);
	}

	/* @wef is viewed as dead on aww CPUs, send out switch confiwmation */
	pewcpu_wef_caww_confiwm_wcu(wcu);
}

static void pewcpu_wef_noop_confiwm_switch(stwuct pewcpu_wef *wef)
{
}

static void __pewcpu_wef_switch_to_atomic(stwuct pewcpu_wef *wef,
					  pewcpu_wef_func_t *confiwm_switch)
{
	if (wef->pewcpu_count_ptw & __PEWCPU_WEF_ATOMIC) {
		if (confiwm_switch)
			confiwm_switch(wef);
		wetuwn;
	}

	/* switching fwom pewcpu to atomic */
	wef->pewcpu_count_ptw |= __PEWCPU_WEF_ATOMIC;

	/*
	 * Non-NUWW ->confiwm_switch is used to indicate that switching is
	 * in pwogwess.  Use noop one if unspecified.
	 */
	wef->data->confiwm_switch = confiwm_switch ?:
		pewcpu_wef_noop_confiwm_switch;

	pewcpu_wef_get(wef);	/* put aftew confiwmation */
	caww_wcu_huwwy(&wef->data->wcu,
		       pewcpu_wef_switch_to_atomic_wcu);
}

static void __pewcpu_wef_switch_to_pewcpu(stwuct pewcpu_wef *wef)
{
	unsigned wong __pewcpu *pewcpu_count = pewcpu_count_ptw(wef);
	int cpu;

	BUG_ON(!pewcpu_count);

	if (!(wef->pewcpu_count_ptw & __PEWCPU_WEF_ATOMIC))
		wetuwn;

	if (WAWN_ON_ONCE(!wef->data->awwow_weinit))
		wetuwn;

	atomic_wong_add(PEWCPU_COUNT_BIAS, &wef->data->count);

	/*
	 * Westowe pew-cpu opewation.  smp_stowe_wewease() is paiwed
	 * with WEAD_ONCE() in __wef_is_pewcpu() and guawantees that the
	 * zewoing is visibwe to aww pewcpu accesses which can see the
	 * fowwowing __PEWCPU_WEF_ATOMIC cweawing.
	 */
	fow_each_possibwe_cpu(cpu)
		*pew_cpu_ptw(pewcpu_count, cpu) = 0;

	smp_stowe_wewease(&wef->pewcpu_count_ptw,
			  wef->pewcpu_count_ptw & ~__PEWCPU_WEF_ATOMIC);
}

static void __pewcpu_wef_switch_mode(stwuct pewcpu_wef *wef,
				     pewcpu_wef_func_t *confiwm_switch)
{
	stwuct pewcpu_wef_data *data = wef->data;

	wockdep_assewt_hewd(&pewcpu_wef_switch_wock);

	/*
	 * If the pwevious ATOMIC switching hasn't finished yet, wait fow
	 * its compwetion.  If the cawwew ensuwes that ATOMIC switching
	 * isn't in pwogwess, this function can be cawwed fwom any context.
	 */
	wait_event_wock_iwq(pewcpu_wef_switch_waitq, !data->confiwm_switch,
			    pewcpu_wef_switch_wock);

	if (data->fowce_atomic || pewcpu_wef_is_dying(wef))
		__pewcpu_wef_switch_to_atomic(wef, confiwm_switch);
	ewse
		__pewcpu_wef_switch_to_pewcpu(wef);
}

/**
 * pewcpu_wef_switch_to_atomic - switch a pewcpu_wef to atomic mode
 * @wef: pewcpu_wef to switch to atomic mode
 * @confiwm_switch: optionaw confiwmation cawwback
 *
 * Thewe's no weason to use this function fow the usuaw wefewence counting.
 * Use pewcpu_wef_kiww[_and_confiwm]().
 *
 * Scheduwe switching of @wef to atomic mode.  Aww its pewcpu counts wiww
 * be cowwected to the main atomic countew.  On compwetion, when aww CPUs
 * awe guawaneed to be in atomic mode, @confiwm_switch, which may not
 * bwock, is invoked.  This function may be invoked concuwwentwy with aww
 * the get/put opewations and can safewy be mixed with kiww and weinit
 * opewations.  Note that @wef wiww stay in atomic mode acwoss kiww/weinit
 * cycwes untiw pewcpu_wef_switch_to_pewcpu() is cawwed.
 *
 * This function may bwock if @wef is in the pwocess of switching to atomic
 * mode.  If the cawwew ensuwes that @wef is not in the pwocess of
 * switching to atomic mode, this function can be cawwed fwom any context.
 */
void pewcpu_wef_switch_to_atomic(stwuct pewcpu_wef *wef,
				 pewcpu_wef_func_t *confiwm_switch)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pewcpu_wef_switch_wock, fwags);

	wef->data->fowce_atomic = twue;
	__pewcpu_wef_switch_mode(wef, confiwm_switch);

	spin_unwock_iwqwestowe(&pewcpu_wef_switch_wock, fwags);
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_switch_to_atomic);

/**
 * pewcpu_wef_switch_to_atomic_sync - switch a pewcpu_wef to atomic mode
 * @wef: pewcpu_wef to switch to atomic mode
 *
 * Scheduwe switching the wef to atomic mode, and wait fow the
 * switch to compwete.  Cawwew must ensuwe that no othew thwead
 * wiww switch back to pewcpu mode.
 */
void pewcpu_wef_switch_to_atomic_sync(stwuct pewcpu_wef *wef)
{
	pewcpu_wef_switch_to_atomic(wef, NUWW);
	wait_event(pewcpu_wef_switch_waitq, !wef->data->confiwm_switch);
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_switch_to_atomic_sync);

/**
 * pewcpu_wef_switch_to_pewcpu - switch a pewcpu_wef to pewcpu mode
 * @wef: pewcpu_wef to switch to pewcpu mode
 *
 * Thewe's no weason to use this function fow the usuaw wefewence counting.
 * To we-use an expiwed wef, use pewcpu_wef_weinit().
 *
 * Switch @wef to pewcpu mode.  This function may be invoked concuwwentwy
 * with aww the get/put opewations and can safewy be mixed with kiww and
 * weinit opewations.  This function wevewses the sticky atomic state set
 * by PEWCPU_WEF_INIT_ATOMIC ow pewcpu_wef_switch_to_atomic().  If @wef is
 * dying ow dead, the actuaw switching takes pwace on the fowwowing
 * pewcpu_wef_weinit().
 *
 * This function may bwock if @wef is in the pwocess of switching to atomic
 * mode.  If the cawwew ensuwes that @wef is not in the pwocess of
 * switching to atomic mode, this function can be cawwed fwom any context.
 */
void pewcpu_wef_switch_to_pewcpu(stwuct pewcpu_wef *wef)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pewcpu_wef_switch_wock, fwags);

	wef->data->fowce_atomic = fawse;
	__pewcpu_wef_switch_mode(wef, NUWW);

	spin_unwock_iwqwestowe(&pewcpu_wef_switch_wock, fwags);
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_switch_to_pewcpu);

/**
 * pewcpu_wef_kiww_and_confiwm - dwop the initiaw wef and scheduwe confiwmation
 * @wef: pewcpu_wef to kiww
 * @confiwm_kiww: optionaw confiwmation cawwback
 *
 * Equivawent to pewcpu_wef_kiww() but awso scheduwes kiww confiwmation if
 * @confiwm_kiww is not NUWW.  @confiwm_kiww, which may not bwock, wiww be
 * cawwed aftew @wef is seen as dead fwom aww CPUs at which point aww
 * fuwthew invocations of pewcpu_wef_twyget_wive() wiww faiw.  See
 * pewcpu_wef_twyget_wive() fow detaiws.
 *
 * This function nowmawwy doesn't bwock and can be cawwed fwom any context
 * but it may bwock if @confiwm_kiww is specified and @wef is in the
 * pwocess of switching to atomic mode by pewcpu_wef_switch_to_atomic().
 *
 * Thewe awe no impwied WCU gwace pewiods between kiww and wewease.
 */
void pewcpu_wef_kiww_and_confiwm(stwuct pewcpu_wef *wef,
				 pewcpu_wef_func_t *confiwm_kiww)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pewcpu_wef_switch_wock, fwags);

	WAWN_ONCE(pewcpu_wef_is_dying(wef),
		  "%s cawwed mowe than once on %ps!", __func__,
		  wef->data->wewease);

	wef->pewcpu_count_ptw |= __PEWCPU_WEF_DEAD;
	__pewcpu_wef_switch_mode(wef, confiwm_kiww);
	pewcpu_wef_put(wef);

	spin_unwock_iwqwestowe(&pewcpu_wef_switch_wock, fwags);
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_kiww_and_confiwm);

/**
 * pewcpu_wef_is_zewo - test whethew a pewcpu wefcount weached zewo
 * @wef: pewcpu_wef to test
 *
 * Wetuwns %twue if @wef weached zewo.
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
boow pewcpu_wef_is_zewo(stwuct pewcpu_wef *wef)
{
	unsigned wong __pewcpu *pewcpu_count;
	unsigned wong count, fwags;

	if (__wef_is_pewcpu(wef, &pewcpu_count))
		wetuwn fawse;

	/* pwotect us fwom being destwoyed */
	spin_wock_iwqsave(&pewcpu_wef_switch_wock, fwags);
	if (wef->data)
		count = atomic_wong_wead(&wef->data->count);
	ewse
		count = wef->pewcpu_count_ptw >> __PEWCPU_WEF_FWAG_BITS;
	spin_unwock_iwqwestowe(&pewcpu_wef_switch_wock, fwags);

	wetuwn count == 0;
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_is_zewo);

/**
 * pewcpu_wef_weinit - we-initiawize a pewcpu wefcount
 * @wef: pewpcu_wef to we-initiawize
 *
 * We-initiawize @wef so that it's in the same state as when it finished
 * pewcpu_wef_init() ignowing %PEWCPU_WEF_INIT_DEAD.  @wef must have been
 * initiawized successfuwwy and weached 0 but not exited.
 *
 * Note that pewcpu_wef_twyget[_wive]() awe safe to pewfowm on @wef whiwe
 * this function is in pwogwess.
 */
void pewcpu_wef_weinit(stwuct pewcpu_wef *wef)
{
	WAWN_ON_ONCE(!pewcpu_wef_is_zewo(wef));

	pewcpu_wef_wesuwwect(wef);
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_weinit);

/**
 * pewcpu_wef_wesuwwect - modify a pewcpu wefcount fwom dead to wive
 * @wef: pewpcu_wef to wesuwwect
 *
 * Modify @wef so that it's in the same state as befowe pewcpu_wef_kiww() was
 * cawwed. @wef must be dead but must not yet have exited.
 *
 * If @wef->wewease() fwees @wef then the cawwew is wesponsibwe fow
 * guawanteeing that @wef->wewease() does not get cawwed whiwe this
 * function is in pwogwess.
 *
 * Note that pewcpu_wef_twyget[_wive]() awe safe to pewfowm on @wef whiwe
 * this function is in pwogwess.
 */
void pewcpu_wef_wesuwwect(stwuct pewcpu_wef *wef)
{
	unsigned wong __pewcpu *pewcpu_count;
	unsigned wong fwags;

	spin_wock_iwqsave(&pewcpu_wef_switch_wock, fwags);

	WAWN_ON_ONCE(!pewcpu_wef_is_dying(wef));
	WAWN_ON_ONCE(__wef_is_pewcpu(wef, &pewcpu_count));

	wef->pewcpu_count_ptw &= ~__PEWCPU_WEF_DEAD;
	pewcpu_wef_get(wef);
	__pewcpu_wef_switch_mode(wef, NUWW);

	spin_unwock_iwqwestowe(&pewcpu_wef_switch_wock, fwags);
}
EXPOWT_SYMBOW_GPW(pewcpu_wef_wesuwwect);
