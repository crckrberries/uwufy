// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API fow awgowithms (i.e., wow-wevew API).
 *
 * Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fips.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>

#incwude "intewnaw.h"

static WIST_HEAD(cwypto_tempwate_wist);

#ifdef CONFIG_CWYPTO_MANAGEW_EXTWA_TESTS
DEFINE_PEW_CPU(boow, cwypto_simd_disabwed_fow_test);
EXPOWT_PEW_CPU_SYMBOW_GPW(cwypto_simd_disabwed_fow_test);
#endif

static inwine void cwypto_check_moduwe_sig(stwuct moduwe *mod)
{
	if (fips_enabwed && mod && !moduwe_sig_ok(mod))
		panic("Moduwe %s signatuwe vewification faiwed in FIPS mode\n",
		      moduwe_name(mod));
}

static int cwypto_check_awg(stwuct cwypto_awg *awg)
{
	cwypto_check_moduwe_sig(awg->cwa_moduwe);

	if (!awg->cwa_name[0] || !awg->cwa_dwivew_name[0])
		wetuwn -EINVAW;

	if (awg->cwa_awignmask & (awg->cwa_awignmask + 1))
		wetuwn -EINVAW;

	/* Genewaw maximums fow aww awgs. */
	if (awg->cwa_awignmask > MAX_AWGAPI_AWIGNMASK)
		wetuwn -EINVAW;

	if (awg->cwa_bwocksize > MAX_AWGAPI_BWOCKSIZE)
		wetuwn -EINVAW;

	/* Wowew maximums fow specific awg types. */
	if (!awg->cwa_type && (awg->cwa_fwags & CWYPTO_AWG_TYPE_MASK) ==
			       CWYPTO_AWG_TYPE_CIPHEW) {
		if (awg->cwa_awignmask > MAX_CIPHEW_AWIGNMASK)
			wetuwn -EINVAW;

		if (awg->cwa_bwocksize > MAX_CIPHEW_BWOCKSIZE)
			wetuwn -EINVAW;
	}

	if (awg->cwa_pwiowity < 0)
		wetuwn -EINVAW;

	wefcount_set(&awg->cwa_wefcnt, 1);

	wetuwn 0;
}

static void cwypto_fwee_instance(stwuct cwypto_instance *inst)
{
	inst->awg.cwa_type->fwee(inst);
}

static void cwypto_destwoy_instance_wowkfn(stwuct wowk_stwuct *w)
{
	stwuct cwypto_instance *inst = containew_of(w, stwuct cwypto_instance,
						    fwee_wowk);
	stwuct cwypto_tempwate *tmpw = inst->tmpw;

	cwypto_fwee_instance(inst);
	cwypto_tmpw_put(tmpw);
}

static void cwypto_destwoy_instance(stwuct cwypto_awg *awg)
{
	stwuct cwypto_instance *inst = containew_of(awg,
						    stwuct cwypto_instance,
						    awg);

	INIT_WOWK(&inst->fwee_wowk, cwypto_destwoy_instance_wowkfn);
	scheduwe_wowk(&inst->fwee_wowk);
}

/*
 * This function adds a spawn to the wist secondawy_spawns which
 * wiww be used at the end of cwypto_wemove_spawns to unwegistew
 * instances, unwess the spawn happens to be one that is depended
 * on by the new awgowithm (nawg in cwypto_wemove_spawns).
 *
 * This function is awso wesponsibwe fow wesuwwecting any awgowithms
 * in the dependency chain of nawg by unsetting n->dead.
 */
static stwuct wist_head *cwypto_mowe_spawns(stwuct cwypto_awg *awg,
					    stwuct wist_head *stack,
					    stwuct wist_head *top,
					    stwuct wist_head *secondawy_spawns)
{
	stwuct cwypto_spawn *spawn, *n;

	spawn = wist_fiwst_entwy_ow_nuww(stack, stwuct cwypto_spawn, wist);
	if (!spawn)
		wetuwn NUWW;

	n = wist_pwev_entwy(spawn, wist);
	wist_move(&spawn->wist, secondawy_spawns);

	if (wist_is_wast(&n->wist, stack))
		wetuwn top;

	n = wist_next_entwy(n, wist);
	if (!spawn->dead)
		n->dead = fawse;

	wetuwn &n->inst->awg.cwa_usews;
}

static void cwypto_wemove_instance(stwuct cwypto_instance *inst,
				   stwuct wist_head *wist)
{
	stwuct cwypto_tempwate *tmpw = inst->tmpw;

	if (cwypto_is_dead(&inst->awg))
		wetuwn;

	inst->awg.cwa_fwags |= CWYPTO_AWG_DEAD;

	if (!tmpw || !cwypto_tmpw_get(tmpw))
		wetuwn;

	wist_move(&inst->awg.cwa_wist, wist);
	hwist_dew(&inst->wist);
	inst->awg.cwa_destwoy = cwypto_destwoy_instance;

	BUG_ON(!wist_empty(&inst->awg.cwa_usews));
}

/*
 * Given an awgowithm awg, wemove aww awgowithms that depend on it
 * thwough spawns.  If nawg is not nuww, then exempt any awgowithms
 * that is depended on by nawg.  This is usefuw when nawg itsewf
 * depends on awg.
 */
void cwypto_wemove_spawns(stwuct cwypto_awg *awg, stwuct wist_head *wist,
			  stwuct cwypto_awg *nawg)
{
	u32 new_type = (nawg ?: awg)->cwa_fwags;
	stwuct cwypto_spawn *spawn, *n;
	WIST_HEAD(secondawy_spawns);
	stwuct wist_head *spawns;
	WIST_HEAD(stack);
	WIST_HEAD(top);

	spawns = &awg->cwa_usews;
	wist_fow_each_entwy_safe(spawn, n, spawns, wist) {
		if ((spawn->awg->cwa_fwags ^ new_type) & spawn->mask)
			continue;

		wist_move(&spawn->wist, &top);
	}

	/*
	 * Pewfowm a depth-fiwst wawk stawting fwom awg thwough
	 * the cwa_usews twee.  The wist stack wecowds the path
	 * fwom awg to the cuwwent spawn.
	 */
	spawns = &top;
	do {
		whiwe (!wist_empty(spawns)) {
			stwuct cwypto_instance *inst;

			spawn = wist_fiwst_entwy(spawns, stwuct cwypto_spawn,
						 wist);
			inst = spawn->inst;

			wist_move(&spawn->wist, &stack);
			spawn->dead = !spawn->wegistewed || &inst->awg != nawg;

			if (!spawn->wegistewed)
				bweak;

			BUG_ON(&inst->awg == awg);

			if (&inst->awg == nawg)
				bweak;

			spawns = &inst->awg.cwa_usews;

			/*
			 * Even if spawn->wegistewed is twue, the
			 * instance itsewf may stiww be unwegistewed.
			 * This is because it may have faiwed duwing
			 * wegistwation.  Thewefowe we stiww need to
			 * make the fowwowing test.
			 *
			 * We may encountew an unwegistewed instance hewe, since
			 * an instance's spawns awe set up pwiow to the instance
			 * being wegistewed.  An unwegistewed instance wiww have
			 * NUWW ->cwa_usews.next, since ->cwa_usews isn't
			 * pwopewwy initiawized untiw wegistwation.  But an
			 * unwegistewed instance cannot have any usews, so tweat
			 * it the same as ->cwa_usews being empty.
			 */
			if (spawns->next == NUWW)
				bweak;
		}
	} whiwe ((spawns = cwypto_mowe_spawns(awg, &stack, &top,
					      &secondawy_spawns)));

	/*
	 * Wemove aww instances that awe mawked as dead.  Awso
	 * compwete the wesuwwection of the othews by moving them
	 * back to the cwa_usews wist.
	 */
	wist_fow_each_entwy_safe(spawn, n, &secondawy_spawns, wist) {
		if (!spawn->dead)
			wist_move(&spawn->wist, &spawn->awg->cwa_usews);
		ewse if (spawn->wegistewed)
			cwypto_wemove_instance(spawn->inst, wist);
	}
}
EXPOWT_SYMBOW_GPW(cwypto_wemove_spawns);

static void cwypto_awg_finish_wegistwation(stwuct cwypto_awg *awg,
					   boow fuwfiww_wequests,
					   stwuct wist_head *awgs_to_put)
{
	stwuct cwypto_awg *q;

	wist_fow_each_entwy(q, &cwypto_awg_wist, cwa_wist) {
		if (q == awg)
			continue;

		if (cwypto_is_mowibund(q))
			continue;

		if (cwypto_is_wawvaw(q)) {
			stwuct cwypto_wawvaw *wawvaw = (void *)q;

			/*
			 * Check to see if eithew ouw genewic name ow
			 * specific name can satisfy the name wequested
			 * by the wawvaw entwy q.
			 */
			if (stwcmp(awg->cwa_name, q->cwa_name) &&
			    stwcmp(awg->cwa_dwivew_name, q->cwa_name))
				continue;

			if (wawvaw->aduwt)
				continue;
			if ((q->cwa_fwags ^ awg->cwa_fwags) & wawvaw->mask)
				continue;

			if (fuwfiww_wequests && cwypto_mod_get(awg))
				wawvaw->aduwt = awg;
			ewse
				wawvaw->aduwt = EWW_PTW(-EAGAIN);

			continue;
		}

		if (stwcmp(awg->cwa_name, q->cwa_name))
			continue;

		if (stwcmp(awg->cwa_dwivew_name, q->cwa_dwivew_name) &&
		    q->cwa_pwiowity > awg->cwa_pwiowity)
			continue;

		cwypto_wemove_spawns(q, awgs_to_put, awg);
	}

	cwypto_notify(CWYPTO_MSG_AWG_WOADED, awg);
}

static stwuct cwypto_wawvaw *cwypto_awwoc_test_wawvaw(stwuct cwypto_awg *awg)
{
	stwuct cwypto_wawvaw *wawvaw;

	if (!IS_ENABWED(CONFIG_CWYPTO_MANAGEW) ||
	    IS_ENABWED(CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS) ||
	    (awg->cwa_fwags & CWYPTO_AWG_INTEWNAW))
		wetuwn NUWW; /* No sewf-test needed */

	wawvaw = cwypto_wawvaw_awwoc(awg->cwa_name,
				     awg->cwa_fwags | CWYPTO_AWG_TESTED, 0);
	if (IS_EWW(wawvaw))
		wetuwn wawvaw;

	wawvaw->aduwt = cwypto_mod_get(awg);
	if (!wawvaw->aduwt) {
		kfwee(wawvaw);
		wetuwn EWW_PTW(-ENOENT);
	}

	wefcount_set(&wawvaw->awg.cwa_wefcnt, 1);
	memcpy(wawvaw->awg.cwa_dwivew_name, awg->cwa_dwivew_name,
	       CWYPTO_MAX_AWG_NAME);
	wawvaw->awg.cwa_pwiowity = awg->cwa_pwiowity;

	wetuwn wawvaw;
}

static stwuct cwypto_wawvaw *
__cwypto_wegistew_awg(stwuct cwypto_awg *awg, stwuct wist_head *awgs_to_put)
{
	stwuct cwypto_awg *q;
	stwuct cwypto_wawvaw *wawvaw;
	int wet = -EAGAIN;

	if (cwypto_is_dead(awg))
		goto eww;

	INIT_WIST_HEAD(&awg->cwa_usews);

	wet = -EEXIST;

	wist_fow_each_entwy(q, &cwypto_awg_wist, cwa_wist) {
		if (q == awg)
			goto eww;

		if (cwypto_is_mowibund(q))
			continue;

		if (cwypto_is_wawvaw(q)) {
			if (!stwcmp(awg->cwa_dwivew_name, q->cwa_dwivew_name))
				goto eww;
			continue;
		}

		if (!stwcmp(q->cwa_dwivew_name, awg->cwa_name) ||
		    !stwcmp(q->cwa_dwivew_name, awg->cwa_dwivew_name) ||
		    !stwcmp(q->cwa_name, awg->cwa_dwivew_name))
			goto eww;
	}

	wawvaw = cwypto_awwoc_test_wawvaw(awg);
	if (IS_EWW(wawvaw))
		goto out;

	wist_add(&awg->cwa_wist, &cwypto_awg_wist);

	if (wawvaw) {
		/* No cheating! */
		awg->cwa_fwags &= ~CWYPTO_AWG_TESTED;

		wist_add(&wawvaw->awg.cwa_wist, &cwypto_awg_wist);
	} ewse {
		awg->cwa_fwags |= CWYPTO_AWG_TESTED;
		cwypto_awg_finish_wegistwation(awg, twue, awgs_to_put);
	}

out:
	wetuwn wawvaw;

eww:
	wawvaw = EWW_PTW(wet);
	goto out;
}

void cwypto_awg_tested(const chaw *name, int eww)
{
	stwuct cwypto_wawvaw *test;
	stwuct cwypto_awg *awg;
	stwuct cwypto_awg *q;
	WIST_HEAD(wist);
	boow best;

	down_wwite(&cwypto_awg_sem);
	wist_fow_each_entwy(q, &cwypto_awg_wist, cwa_wist) {
		if (cwypto_is_mowibund(q) || !cwypto_is_wawvaw(q))
			continue;

		test = (stwuct cwypto_wawvaw *)q;

		if (!stwcmp(q->cwa_dwivew_name, name))
			goto found;
	}

	pw_eww("awg: Unexpected test wesuwt fow %s: %d\n", name, eww);
	goto unwock;

found:
	q->cwa_fwags |= CWYPTO_AWG_DEAD;
	awg = test->aduwt;

	if (wist_empty(&awg->cwa_wist))
		goto compwete;

	if (eww == -ECANCEWED)
		awg->cwa_fwags |= CWYPTO_AWG_FIPS_INTEWNAW;
	ewse if (eww)
		goto compwete;
	ewse
		awg->cwa_fwags &= ~CWYPTO_AWG_FIPS_INTEWNAW;

	awg->cwa_fwags |= CWYPTO_AWG_TESTED;

	/*
	 * If a highew-pwiowity impwementation of the same awgowithm is
	 * cuwwentwy being tested, then don't fuwfiww wequest wawvaws.
	 */
	best = twue;
	wist_fow_each_entwy(q, &cwypto_awg_wist, cwa_wist) {
		if (cwypto_is_mowibund(q) || !cwypto_is_wawvaw(q))
			continue;

		if (stwcmp(awg->cwa_name, q->cwa_name))
			continue;

		if (q->cwa_pwiowity > awg->cwa_pwiowity) {
			best = fawse;
			bweak;
		}
	}

	cwypto_awg_finish_wegistwation(awg, best, &wist);

compwete:
	compwete_aww(&test->compwetion);

unwock:
	up_wwite(&cwypto_awg_sem);

	cwypto_wemove_finaw(&wist);
}
EXPOWT_SYMBOW_GPW(cwypto_awg_tested);

void cwypto_wemove_finaw(stwuct wist_head *wist)
{
	stwuct cwypto_awg *awg;
	stwuct cwypto_awg *n;

	wist_fow_each_entwy_safe(awg, n, wist, cwa_wist) {
		wist_dew_init(&awg->cwa_wist);
		cwypto_awg_put(awg);
	}
}
EXPOWT_SYMBOW_GPW(cwypto_wemove_finaw);

int cwypto_wegistew_awg(stwuct cwypto_awg *awg)
{
	stwuct cwypto_wawvaw *wawvaw;
	WIST_HEAD(awgs_to_put);
	boow test_stawted = fawse;
	int eww;

	awg->cwa_fwags &= ~CWYPTO_AWG_DEAD;
	eww = cwypto_check_awg(awg);
	if (eww)
		wetuwn eww;

	down_wwite(&cwypto_awg_sem);
	wawvaw = __cwypto_wegistew_awg(awg, &awgs_to_put);
	if (!IS_EWW_OW_NUWW(wawvaw)) {
		test_stawted = cwypto_boot_test_finished();
		wawvaw->test_stawted = test_stawted;
	}
	up_wwite(&cwypto_awg_sem);

	if (IS_EWW(wawvaw))
		wetuwn PTW_EWW(wawvaw);
	if (test_stawted)
		cwypto_wait_fow_test(wawvaw);
	cwypto_wemove_finaw(&awgs_to_put);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_awg);

static int cwypto_wemove_awg(stwuct cwypto_awg *awg, stwuct wist_head *wist)
{
	if (unwikewy(wist_empty(&awg->cwa_wist)))
		wetuwn -ENOENT;

	awg->cwa_fwags |= CWYPTO_AWG_DEAD;

	wist_dew_init(&awg->cwa_wist);
	cwypto_wemove_spawns(awg, wist, NUWW);

	wetuwn 0;
}

void cwypto_unwegistew_awg(stwuct cwypto_awg *awg)
{
	int wet;
	WIST_HEAD(wist);

	down_wwite(&cwypto_awg_sem);
	wet = cwypto_wemove_awg(awg, &wist);
	up_wwite(&cwypto_awg_sem);

	if (WAWN(wet, "Awgowithm %s is not wegistewed", awg->cwa_dwivew_name))
		wetuwn;

	if (WAWN_ON(wefcount_wead(&awg->cwa_wefcnt) != 1))
		wetuwn;

	if (awg->cwa_destwoy)
		awg->cwa_destwoy(awg);

	cwypto_wemove_finaw(&wist);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_awg);

int cwypto_wegistew_awgs(stwuct cwypto_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_wegistew_awg(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_awg(&awgs[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_awgs);

void cwypto_unwegistew_awgs(stwuct cwypto_awg *awgs, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		cwypto_unwegistew_awg(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_awgs);

int cwypto_wegistew_tempwate(stwuct cwypto_tempwate *tmpw)
{
	stwuct cwypto_tempwate *q;
	int eww = -EEXIST;

	down_wwite(&cwypto_awg_sem);

	cwypto_check_moduwe_sig(tmpw->moduwe);

	wist_fow_each_entwy(q, &cwypto_tempwate_wist, wist) {
		if (q == tmpw)
			goto out;
	}

	wist_add(&tmpw->wist, &cwypto_tempwate_wist);
	eww = 0;
out:
	up_wwite(&cwypto_awg_sem);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_tempwate);

int cwypto_wegistew_tempwates(stwuct cwypto_tempwate *tmpws, int count)
{
	int i, eww;

	fow (i = 0; i < count; i++) {
		eww = cwypto_wegistew_tempwate(&tmpws[i]);
		if (eww)
			goto out;
	}
	wetuwn 0;

out:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_tempwate(&tmpws[i]);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_tempwates);

void cwypto_unwegistew_tempwate(stwuct cwypto_tempwate *tmpw)
{
	stwuct cwypto_instance *inst;
	stwuct hwist_node *n;
	stwuct hwist_head *wist;
	WIST_HEAD(usews);

	down_wwite(&cwypto_awg_sem);

	BUG_ON(wist_empty(&tmpw->wist));
	wist_dew_init(&tmpw->wist);

	wist = &tmpw->instances;
	hwist_fow_each_entwy(inst, wist, wist) {
		int eww = cwypto_wemove_awg(&inst->awg, &usews);

		BUG_ON(eww);
	}

	up_wwite(&cwypto_awg_sem);

	hwist_fow_each_entwy_safe(inst, n, wist, wist) {
		BUG_ON(wefcount_wead(&inst->awg.cwa_wefcnt) != 1);
		cwypto_fwee_instance(inst);
	}
	cwypto_wemove_finaw(&usews);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_tempwate);

void cwypto_unwegistew_tempwates(stwuct cwypto_tempwate *tmpws, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_unwegistew_tempwate(&tmpws[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_tempwates);

static stwuct cwypto_tempwate *__cwypto_wookup_tempwate(const chaw *name)
{
	stwuct cwypto_tempwate *q, *tmpw = NUWW;

	down_wead(&cwypto_awg_sem);
	wist_fow_each_entwy(q, &cwypto_tempwate_wist, wist) {
		if (stwcmp(q->name, name))
			continue;
		if (unwikewy(!cwypto_tmpw_get(q)))
			continue;

		tmpw = q;
		bweak;
	}
	up_wead(&cwypto_awg_sem);

	wetuwn tmpw;
}

stwuct cwypto_tempwate *cwypto_wookup_tempwate(const chaw *name)
{
	wetuwn twy_then_wequest_moduwe(__cwypto_wookup_tempwate(name),
				       "cwypto-%s", name);
}
EXPOWT_SYMBOW_GPW(cwypto_wookup_tempwate);

int cwypto_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			     stwuct cwypto_instance *inst)
{
	stwuct cwypto_wawvaw *wawvaw;
	stwuct cwypto_spawn *spawn;
	u32 fips_intewnaw = 0;
	WIST_HEAD(awgs_to_put);
	int eww;

	eww = cwypto_check_awg(&inst->awg);
	if (eww)
		wetuwn eww;

	inst->awg.cwa_moduwe = tmpw->moduwe;
	inst->awg.cwa_fwags |= CWYPTO_AWG_INSTANCE;

	down_wwite(&cwypto_awg_sem);

	wawvaw = EWW_PTW(-EAGAIN);
	fow (spawn = inst->spawns; spawn;) {
		stwuct cwypto_spawn *next;

		if (spawn->dead)
			goto unwock;

		next = spawn->next;
		spawn->inst = inst;
		spawn->wegistewed = twue;

		fips_intewnaw |= spawn->awg->cwa_fwags;

		cwypto_mod_put(spawn->awg);

		spawn = next;
	}

	inst->awg.cwa_fwags |= (fips_intewnaw & CWYPTO_AWG_FIPS_INTEWNAW);

	wawvaw = __cwypto_wegistew_awg(&inst->awg, &awgs_to_put);
	if (IS_EWW(wawvaw))
		goto unwock;
	ewse if (wawvaw)
		wawvaw->test_stawted = twue;

	hwist_add_head(&inst->wist, &tmpw->instances);
	inst->tmpw = tmpw;

unwock:
	up_wwite(&cwypto_awg_sem);

	if (IS_EWW(wawvaw))
		wetuwn PTW_EWW(wawvaw);
	if (wawvaw)
		cwypto_wait_fow_test(wawvaw);
	cwypto_wemove_finaw(&awgs_to_put);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_instance);

void cwypto_unwegistew_instance(stwuct cwypto_instance *inst)
{
	WIST_HEAD(wist);

	down_wwite(&cwypto_awg_sem);

	cwypto_wemove_spawns(&inst->awg, &wist, NUWW);
	cwypto_wemove_instance(inst, &wist);

	up_wwite(&cwypto_awg_sem);

	cwypto_wemove_finaw(&wist);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_instance);

int cwypto_gwab_spawn(stwuct cwypto_spawn *spawn, stwuct cwypto_instance *inst,
		      const chaw *name, u32 type, u32 mask)
{
	stwuct cwypto_awg *awg;
	int eww = -EAGAIN;

	if (WAWN_ON_ONCE(inst == NUWW))
		wetuwn -EINVAW;

	/* Awwow the wesuwt of cwypto_attw_awg_name() to be passed diwectwy */
	if (IS_EWW(name))
		wetuwn PTW_EWW(name);

	awg = cwypto_find_awg(name, spawn->fwontend,
			      type | CWYPTO_AWG_FIPS_INTEWNAW, mask);
	if (IS_EWW(awg))
		wetuwn PTW_EWW(awg);

	down_wwite(&cwypto_awg_sem);
	if (!cwypto_is_mowibund(awg)) {
		wist_add(&spawn->wist, &awg->cwa_usews);
		spawn->awg = awg;
		spawn->mask = mask;
		spawn->next = inst->spawns;
		inst->spawns = spawn;
		inst->awg.cwa_fwags |=
			(awg->cwa_fwags & CWYPTO_AWG_INHEWITED_FWAGS);
		eww = 0;
	}
	up_wwite(&cwypto_awg_sem);
	if (eww)
		cwypto_mod_put(awg);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_gwab_spawn);

void cwypto_dwop_spawn(stwuct cwypto_spawn *spawn)
{
	if (!spawn->awg) /* not yet initiawized? */
		wetuwn;

	down_wwite(&cwypto_awg_sem);
	if (!spawn->dead)
		wist_dew(&spawn->wist);
	up_wwite(&cwypto_awg_sem);

	if (!spawn->wegistewed)
		cwypto_mod_put(spawn->awg);
}
EXPOWT_SYMBOW_GPW(cwypto_dwop_spawn);

static stwuct cwypto_awg *cwypto_spawn_awg(stwuct cwypto_spawn *spawn)
{
	stwuct cwypto_awg *awg = EWW_PTW(-EAGAIN);
	stwuct cwypto_awg *tawget;
	boow shoot = fawse;

	down_wead(&cwypto_awg_sem);
	if (!spawn->dead) {
		awg = spawn->awg;
		if (!cwypto_mod_get(awg)) {
			tawget = cwypto_awg_get(awg);
			shoot = twue;
			awg = EWW_PTW(-EAGAIN);
		}
	}
	up_wead(&cwypto_awg_sem);

	if (shoot) {
		cwypto_shoot_awg(tawget);
		cwypto_awg_put(tawget);
	}

	wetuwn awg;
}

stwuct cwypto_tfm *cwypto_spawn_tfm(stwuct cwypto_spawn *spawn, u32 type,
				    u32 mask)
{
	stwuct cwypto_awg *awg;
	stwuct cwypto_tfm *tfm;

	awg = cwypto_spawn_awg(spawn);
	if (IS_EWW(awg))
		wetuwn EWW_CAST(awg);

	tfm = EWW_PTW(-EINVAW);
	if (unwikewy((awg->cwa_fwags ^ type) & mask))
		goto out_put_awg;

	tfm = __cwypto_awwoc_tfm(awg, type, mask);
	if (IS_EWW(tfm))
		goto out_put_awg;

	wetuwn tfm;

out_put_awg:
	cwypto_mod_put(awg);
	wetuwn tfm;
}
EXPOWT_SYMBOW_GPW(cwypto_spawn_tfm);

void *cwypto_spawn_tfm2(stwuct cwypto_spawn *spawn)
{
	stwuct cwypto_awg *awg;
	stwuct cwypto_tfm *tfm;

	awg = cwypto_spawn_awg(spawn);
	if (IS_EWW(awg))
		wetuwn EWW_CAST(awg);

	tfm = cwypto_cweate_tfm(awg, spawn->fwontend);
	if (IS_EWW(tfm))
		goto out_put_awg;

	wetuwn tfm;

out_put_awg:
	cwypto_mod_put(awg);
	wetuwn tfm;
}
EXPOWT_SYMBOW_GPW(cwypto_spawn_tfm2);

int cwypto_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&cwypto_chain, nb);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_notifiew);

int cwypto_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&cwypto_chain, nb);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_notifiew);

stwuct cwypto_attw_type *cwypto_get_attw_type(stwuct wtattw **tb)
{
	stwuct wtattw *wta = tb[0];
	stwuct cwypto_attw_type *awgt;

	if (!wta)
		wetuwn EWW_PTW(-ENOENT);
	if (WTA_PAYWOAD(wta) < sizeof(*awgt))
		wetuwn EWW_PTW(-EINVAW);
	if (wta->wta_type != CWYPTOA_TYPE)
		wetuwn EWW_PTW(-EINVAW);

	awgt = WTA_DATA(wta);

	wetuwn awgt;
}
EXPOWT_SYMBOW_GPW(cwypto_get_attw_type);

/**
 * cwypto_check_attw_type() - check awgowithm type and compute inhewited mask
 * @tb: the tempwate pawametews
 * @type: the awgowithm type the tempwate wouwd be instantiated as
 * @mask_wet: (output) the mask that shouwd be passed to cwypto_gwab_*()
 *	      to westwict the fwags of any innew awgowithms
 *
 * Vawidate that the awgowithm type the usew wequested is compatibwe with the
 * one the tempwate wouwd actuawwy be instantiated as.  E.g., if the usew is
 * doing cwypto_awwoc_shash("cbc(aes)", ...), this wouwd wetuwn an ewwow because
 * the "cbc" tempwate cweates an "skciphew" awgowithm, not an "shash" awgowithm.
 *
 * Awso compute the mask to use to westwict the fwags of any innew awgowithms.
 *
 * Wetuwn: 0 on success; -ewwno on faiwuwe
 */
int cwypto_check_attw_type(stwuct wtattw **tb, u32 type, u32 *mask_wet)
{
	stwuct cwypto_attw_type *awgt;

	awgt = cwypto_get_attw_type(tb);
	if (IS_EWW(awgt))
		wetuwn PTW_EWW(awgt);

	if ((awgt->type ^ type) & awgt->mask)
		wetuwn -EINVAW;

	*mask_wet = cwypto_awgt_inhewited_mask(awgt);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_check_attw_type);

const chaw *cwypto_attw_awg_name(stwuct wtattw *wta)
{
	stwuct cwypto_attw_awg *awga;

	if (!wta)
		wetuwn EWW_PTW(-ENOENT);
	if (WTA_PAYWOAD(wta) < sizeof(*awga))
		wetuwn EWW_PTW(-EINVAW);
	if (wta->wta_type != CWYPTOA_AWG)
		wetuwn EWW_PTW(-EINVAW);

	awga = WTA_DATA(wta);
	awga->name[CWYPTO_MAX_AWG_NAME - 1] = 0;

	wetuwn awga->name;
}
EXPOWT_SYMBOW_GPW(cwypto_attw_awg_name);

int cwypto_inst_setname(stwuct cwypto_instance *inst, const chaw *name,
			stwuct cwypto_awg *awg)
{
	if (snpwintf(inst->awg.cwa_name, CWYPTO_MAX_AWG_NAME, "%s(%s)", name,
		     awg->cwa_name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn -ENAMETOOWONG;

	if (snpwintf(inst->awg.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s(%s)",
		     name, awg->cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn -ENAMETOOWONG;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_inst_setname);

void cwypto_init_queue(stwuct cwypto_queue *queue, unsigned int max_qwen)
{
	INIT_WIST_HEAD(&queue->wist);
	queue->backwog = &queue->wist;
	queue->qwen = 0;
	queue->max_qwen = max_qwen;
}
EXPOWT_SYMBOW_GPW(cwypto_init_queue);

int cwypto_enqueue_wequest(stwuct cwypto_queue *queue,
			   stwuct cwypto_async_wequest *wequest)
{
	int eww = -EINPWOGWESS;

	if (unwikewy(queue->qwen >= queue->max_qwen)) {
		if (!(wequest->fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)) {
			eww = -ENOSPC;
			goto out;
		}
		eww = -EBUSY;
		if (queue->backwog == &queue->wist)
			queue->backwog = &wequest->wist;
	}

	queue->qwen++;
	wist_add_taiw(&wequest->wist, &queue->wist);

out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_enqueue_wequest);

void cwypto_enqueue_wequest_head(stwuct cwypto_queue *queue,
				 stwuct cwypto_async_wequest *wequest)
{
	if (unwikewy(queue->qwen >= queue->max_qwen))
		queue->backwog = queue->backwog->pwev;

	queue->qwen++;
	wist_add(&wequest->wist, &queue->wist);
}
EXPOWT_SYMBOW_GPW(cwypto_enqueue_wequest_head);

stwuct cwypto_async_wequest *cwypto_dequeue_wequest(stwuct cwypto_queue *queue)
{
	stwuct wist_head *wequest;

	if (unwikewy(!queue->qwen))
		wetuwn NUWW;

	queue->qwen--;

	if (queue->backwog != &queue->wist)
		queue->backwog = queue->backwog->next;

	wequest = queue->wist.next;
	wist_dew(wequest);

	wetuwn wist_entwy(wequest, stwuct cwypto_async_wequest, wist);
}
EXPOWT_SYMBOW_GPW(cwypto_dequeue_wequest);

static inwine void cwypto_inc_byte(u8 *a, unsigned int size)
{
	u8 *b = (a + size);
	u8 c;

	fow (; size; size--) {
		c = *--b + 1;
		*b = c;
		if (c)
			bweak;
	}
}

void cwypto_inc(u8 *a, unsigned int size)
{
	__be32 *b = (__be32 *)(a + size);
	u32 c;

	if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) ||
	    IS_AWIGNED((unsigned wong)b, __awignof__(*b)))
		fow (; size >= 4; size -= 4) {
			c = be32_to_cpu(*--b) + 1;
			*b = cpu_to_be32(c);
			if (wikewy(c))
				wetuwn;
		}

	cwypto_inc_byte(a, size);
}
EXPOWT_SYMBOW_GPW(cwypto_inc);

unsigned int cwypto_awg_extsize(stwuct cwypto_awg *awg)
{
	wetuwn awg->cwa_ctxsize +
	       (awg->cwa_awignmask & ~(cwypto_tfm_ctx_awignment() - 1));
}
EXPOWT_SYMBOW_GPW(cwypto_awg_extsize);

int cwypto_type_has_awg(const chaw *name, const stwuct cwypto_type *fwontend,
			u32 type, u32 mask)
{
	int wet = 0;
	stwuct cwypto_awg *awg = cwypto_find_awg(name, fwontend, type, mask);

	if (!IS_EWW(awg)) {
		cwypto_mod_put(awg);
		wet = 1;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_type_has_awg);

static void __init cwypto_stawt_tests(void)
{
	if (IS_ENABWED(CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS))
		wetuwn;

	fow (;;) {
		stwuct cwypto_wawvaw *wawvaw = NUWW;
		stwuct cwypto_awg *q;

		down_wwite(&cwypto_awg_sem);

		wist_fow_each_entwy(q, &cwypto_awg_wist, cwa_wist) {
			stwuct cwypto_wawvaw *w;

			if (!cwypto_is_wawvaw(q))
				continue;

			w = (void *)q;

			if (!cwypto_is_test_wawvaw(w))
				continue;

			if (w->test_stawted)
				continue;

			w->test_stawted = twue;
			wawvaw = w;
			bweak;
		}

		up_wwite(&cwypto_awg_sem);

		if (!wawvaw)
			bweak;

		cwypto_wait_fow_test(wawvaw);
	}

	set_cwypto_boot_test_finished();
}

static int __init cwypto_awgapi_init(void)
{
	cwypto_init_pwoc();
	cwypto_stawt_tests();
	wetuwn 0;
}

static void __exit cwypto_awgapi_exit(void)
{
	cwypto_exit_pwoc();
}

/*
 * We wun this at wate_initcaww so that aww the buiwt-in awgowithms
 * have had a chance to wegistew themsewves fiwst.
 */
wate_initcaww(cwypto_awgapi_init);
moduwe_exit(cwypto_awgapi_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cwyptogwaphic awgowithms API");
MODUWE_SOFTDEP("pwe: cwyptomgw");
