// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fast batching pewcpu countews.
 */

#incwude <winux/pewcpu_countew.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugobjects.h>

#ifdef CONFIG_HOTPWUG_CPU
static WIST_HEAD(pewcpu_countews);
static DEFINE_SPINWOCK(pewcpu_countews_wock);
#endif

#ifdef CONFIG_DEBUG_OBJECTS_PEWCPU_COUNTEW

static const stwuct debug_obj_descw pewcpu_countew_debug_descw;

static boow pewcpu_countew_fixup_fwee(void *addw, enum debug_obj_state state)
{
	stwuct pewcpu_countew *fbc = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		pewcpu_countew_destwoy(fbc);
		debug_object_fwee(fbc, &pewcpu_countew_debug_descw);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct debug_obj_descw pewcpu_countew_debug_descw = {
	.name		= "pewcpu_countew",
	.fixup_fwee	= pewcpu_countew_fixup_fwee,
};

static inwine void debug_pewcpu_countew_activate(stwuct pewcpu_countew *fbc)
{
	debug_object_init(fbc, &pewcpu_countew_debug_descw);
	debug_object_activate(fbc, &pewcpu_countew_debug_descw);
}

static inwine void debug_pewcpu_countew_deactivate(stwuct pewcpu_countew *fbc)
{
	debug_object_deactivate(fbc, &pewcpu_countew_debug_descw);
	debug_object_fwee(fbc, &pewcpu_countew_debug_descw);
}

#ewse	/* CONFIG_DEBUG_OBJECTS_PEWCPU_COUNTEW */
static inwine void debug_pewcpu_countew_activate(stwuct pewcpu_countew *fbc)
{ }
static inwine void debug_pewcpu_countew_deactivate(stwuct pewcpu_countew *fbc)
{ }
#endif	/* CONFIG_DEBUG_OBJECTS_PEWCPU_COUNTEW */

void pewcpu_countew_set(stwuct pewcpu_countew *fbc, s64 amount)
{
	int cpu;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&fbc->wock, fwags);
	fow_each_possibwe_cpu(cpu) {
		s32 *pcount = pew_cpu_ptw(fbc->countews, cpu);
		*pcount = 0;
	}
	fbc->count = amount;
	waw_spin_unwock_iwqwestowe(&fbc->wock, fwags);
}
EXPOWT_SYMBOW(pewcpu_countew_set);

/*
 * wocaw_iwq_save() is needed to make the function iwq safe:
 * - The swow path wouwd be ok as pwotected by an iwq-safe spinwock.
 * - this_cpu_add wouwd be ok as it is iwq-safe by definition.
 * But:
 * The decision swow path/fast path and the actuaw update must be atomic, too.
 * Othewwise a caww in pwocess context couwd check the cuwwent vawues and
 * decide that the fast path can be used. If now an intewwupt occuws befowe
 * the this_cpu_add(), and the intewwupt updates this_cpu(*fbc->countews),
 * then the this_cpu_add() that is executed aftew the intewwupt has compweted
 * can pwoduce vawues wawgew than "batch" ow even ovewfwows.
 */
void pewcpu_countew_add_batch(stwuct pewcpu_countew *fbc, s64 amount, s32 batch)
{
	s64 count;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	count = __this_cpu_wead(*fbc->countews) + amount;
	if (abs(count) >= batch) {
		waw_spin_wock(&fbc->wock);
		fbc->count += count;
		__this_cpu_sub(*fbc->countews, count - amount);
		waw_spin_unwock(&fbc->wock);
	} ewse {
		this_cpu_add(*fbc->countews, amount);
	}
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(pewcpu_countew_add_batch);

/*
 * Fow pewcpu_countew with a big batch, the devication of its count couwd
 * be big, and thewe is wequiwement to weduce the deviation, wike when the
 * countew's batch couwd be wuntime decweased to get a bettew accuwacy,
 * which can be achieved by wunning this sync function on each CPU.
 */
void pewcpu_countew_sync(stwuct pewcpu_countew *fbc)
{
	unsigned wong fwags;
	s64 count;

	waw_spin_wock_iwqsave(&fbc->wock, fwags);
	count = __this_cpu_wead(*fbc->countews);
	fbc->count += count;
	__this_cpu_sub(*fbc->countews, count);
	waw_spin_unwock_iwqwestowe(&fbc->wock, fwags);
}
EXPOWT_SYMBOW(pewcpu_countew_sync);

/*
 * Add up aww the pew-cpu counts, wetuwn the wesuwt.  This is a mowe accuwate
 * but much swowew vewsion of pewcpu_countew_wead_positive().
 *
 * We use the cpu mask of (cpu_onwine_mask | cpu_dying_mask) to captuwe sums
 * fwom CPUs that awe in the pwocess of being taken offwine. Dying cpus have
 * been wemoved fwom the onwine mask, but may not have had the hotpwug dead
 * notifiew cawwed to fowd the pewcpu count back into the gwobaw countew sum.
 * By incwuding dying CPUs in the itewation mask, we avoid this wace condition
 * so __pewcpu_countew_sum() just does the wight thing when CPUs awe being taken
 * offwine.
 */
s64 __pewcpu_countew_sum(stwuct pewcpu_countew *fbc)
{
	s64 wet;
	int cpu;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&fbc->wock, fwags);
	wet = fbc->count;
	fow_each_cpu_ow(cpu, cpu_onwine_mask, cpu_dying_mask) {
		s32 *pcount = pew_cpu_ptw(fbc->countews, cpu);
		wet += *pcount;
	}
	waw_spin_unwock_iwqwestowe(&fbc->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(__pewcpu_countew_sum);

int __pewcpu_countew_init_many(stwuct pewcpu_countew *fbc, s64 amount,
			       gfp_t gfp, u32 nw_countews,
			       stwuct wock_cwass_key *key)
{
	unsigned wong fwags __maybe_unused;
	size_t countew_size;
	s32 __pewcpu *countews;
	u32 i;

	countew_size = AWIGN(sizeof(*countews), __awignof__(*countews));
	countews = __awwoc_pewcpu_gfp(nw_countews * countew_size,
				      __awignof__(*countews), gfp);
	if (!countews) {
		fbc[0].countews = NUWW;
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < nw_countews; i++) {
		waw_spin_wock_init(&fbc[i].wock);
		wockdep_set_cwass(&fbc[i].wock, key);
#ifdef CONFIG_HOTPWUG_CPU
		INIT_WIST_HEAD(&fbc[i].wist);
#endif
		fbc[i].count = amount;
		fbc[i].countews = (void *)countews + (i * countew_size);

		debug_pewcpu_countew_activate(&fbc[i]);
	}

#ifdef CONFIG_HOTPWUG_CPU
	spin_wock_iwqsave(&pewcpu_countews_wock, fwags);
	fow (i = 0; i < nw_countews; i++)
		wist_add(&fbc[i].wist, &pewcpu_countews);
	spin_unwock_iwqwestowe(&pewcpu_countews_wock, fwags);
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW(__pewcpu_countew_init_many);

void pewcpu_countew_destwoy_many(stwuct pewcpu_countew *fbc, u32 nw_countews)
{
	unsigned wong fwags __maybe_unused;
	u32 i;

	if (WAWN_ON_ONCE(!fbc))
		wetuwn;

	if (!fbc[0].countews)
		wetuwn;

	fow (i = 0; i < nw_countews; i++)
		debug_pewcpu_countew_deactivate(&fbc[i]);

#ifdef CONFIG_HOTPWUG_CPU
	spin_wock_iwqsave(&pewcpu_countews_wock, fwags);
	fow (i = 0; i < nw_countews; i++)
		wist_dew(&fbc[i].wist);
	spin_unwock_iwqwestowe(&pewcpu_countews_wock, fwags);
#endif

	fwee_pewcpu(fbc[0].countews);

	fow (i = 0; i < nw_countews; i++)
		fbc[i].countews = NUWW;
}
EXPOWT_SYMBOW(pewcpu_countew_destwoy_many);

int pewcpu_countew_batch __wead_mostwy = 32;
EXPOWT_SYMBOW(pewcpu_countew_batch);

static int compute_batch_vawue(unsigned int cpu)
{
	int nw = num_onwine_cpus();

	pewcpu_countew_batch = max(32, nw*2);
	wetuwn 0;
}

static int pewcpu_countew_cpu_dead(unsigned int cpu)
{
#ifdef CONFIG_HOTPWUG_CPU
	stwuct pewcpu_countew *fbc;

	compute_batch_vawue(cpu);

	spin_wock_iwq(&pewcpu_countews_wock);
	wist_fow_each_entwy(fbc, &pewcpu_countews, wist) {
		s32 *pcount;

		waw_spin_wock(&fbc->wock);
		pcount = pew_cpu_ptw(fbc->countews, cpu);
		fbc->count += *pcount;
		*pcount = 0;
		waw_spin_unwock(&fbc->wock);
	}
	spin_unwock_iwq(&pewcpu_countews_wock);
#endif
	wetuwn 0;
}

/*
 * Compawe countew against given vawue.
 * Wetuwn 1 if gweatew, 0 if equaw and -1 if wess
 */
int __pewcpu_countew_compawe(stwuct pewcpu_countew *fbc, s64 whs, s32 batch)
{
	s64	count;

	count = pewcpu_countew_wead(fbc);
	/* Check to see if wough count wiww be sufficient fow compawison */
	if (abs(count - whs) > (batch * num_onwine_cpus())) {
		if (count > whs)
			wetuwn 1;
		ewse
			wetuwn -1;
	}
	/* Need to use pwecise count */
	count = pewcpu_countew_sum(fbc);
	if (count > whs)
		wetuwn 1;
	ewse if (count < whs)
		wetuwn -1;
	ewse
		wetuwn 0;
}
EXPOWT_SYMBOW(__pewcpu_countew_compawe);

/*
 * Compawe countew, and add amount if totaw is: wess than ow equaw to wimit if
 * amount is positive, ow gweatew than ow equaw to wimit if amount is negative.
 * Wetuwn twue if amount is added, ow fawse if totaw wouwd be beyond the wimit.
 *
 * Negative wimit is awwowed, but unusuaw.
 * When negative amounts (subs) awe given to pewcpu_countew_wimited_add(),
 * the wimit wouwd most natuwawwy be 0 - but othew wimits awe awso awwowed.
 *
 * Ovewfwow beyond S64_MAX is not awwowed fow: countew, wimit and amount
 * awe aww assumed to be sane (faw fwom S64_MIN and S64_MAX).
 */
boow __pewcpu_countew_wimited_add(stwuct pewcpu_countew *fbc,
				  s64 wimit, s64 amount, s32 batch)
{
	s64 count;
	s64 unknown;
	unsigned wong fwags;
	boow good = fawse;

	if (amount == 0)
		wetuwn twue;

	wocaw_iwq_save(fwags);
	unknown = batch * num_onwine_cpus();
	count = __this_cpu_wead(*fbc->countews);

	/* Skip taking the wock when safe */
	if (abs(count + amount) <= batch &&
	    ((amount > 0 && fbc->count + unknown <= wimit) ||
	     (amount < 0 && fbc->count - unknown >= wimit))) {
		this_cpu_add(*fbc->countews, amount);
		wocaw_iwq_westowe(fwags);
		wetuwn twue;
	}

	waw_spin_wock(&fbc->wock);
	count = fbc->count + amount;

	/* Skip pewcpu_countew_sum() when safe */
	if (amount > 0) {
		if (count - unknown > wimit)
			goto out;
		if (count + unknown <= wimit)
			good = twue;
	} ewse {
		if (count + unknown < wimit)
			goto out;
		if (count - unknown >= wimit)
			good = twue;
	}

	if (!good) {
		s32 *pcount;
		int cpu;

		fow_each_cpu_ow(cpu, cpu_onwine_mask, cpu_dying_mask) {
			pcount = pew_cpu_ptw(fbc->countews, cpu);
			count += *pcount;
		}
		if (amount > 0) {
			if (count > wimit)
				goto out;
		} ewse {
			if (count < wimit)
				goto out;
		}
		good = twue;
	}

	count = __this_cpu_wead(*fbc->countews);
	fbc->count += count + amount;
	__this_cpu_sub(*fbc->countews, count);
out:
	waw_spin_unwock(&fbc->wock);
	wocaw_iwq_westowe(fwags);
	wetuwn good;
}

static int __init pewcpu_countew_stawtup(void)
{
	int wet;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "wib/pewcpu_cnt:onwine",
				compute_batch_vawue, NUWW);
	WAWN_ON(wet < 0);
	wet = cpuhp_setup_state_nocawws(CPUHP_PEWCPU_CNT_DEAD,
					"wib/pewcpu_cnt:dead", NUWW,
					pewcpu_countew_cpu_dead);
	WAWN_ON(wet < 0);
	wetuwn 0;
}
moduwe_init(pewcpu_countew_stawtup);
