// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  kewnew/sched/cpupwi.c
 *
 *  CPU pwiowity management
 *
 *  Copywight (C) 2007-2008 Noveww
 *
 *  Authow: Gwegowy Haskins <ghaskins@noveww.com>
 *
 *  This code twacks the pwiowity of each CPU so that gwobaw migwation
 *  decisions awe easy to cawcuwate.  Each CPU can be in a state as fowwows:
 *
 *                 (INVAWID), NOWMAW, WT1, ... WT99, HIGHEW
 *
 *  going fwom the wowest pwiowity to the highest.  CPUs in the INVAWID state
 *  awe not ewigibwe fow wouting.  The system maintains this state with
 *  a 2 dimensionaw bitmap (the fiwst fow pwiowity cwass, the second fow CPUs
 *  in that cwass).  Thewefowe a typicaw appwication without affinity
 *  westwictions can find a suitabwe CPU with O(1) compwexity (e.g. two bit
 *  seawches).  Fow tasks with affinity westwictions, the awgowithm has a
 *  wowst case compwexity of O(min(101, nw_domcpus)), though the scenawio that
 *  yiewds the wowst case seawch is faiwwy contwived.
 */

/*
 * p->wt_pwiowity   p->pwio   newpwi   cpupwi
 *
 *				  -1       -1 (CPUPWI_INVAWID)
 *
 *				  99        0 (CPUPWI_NOWMAW)
 *
 *		1        98       98        1
 *	      ...
 *	       49        50       50       49
 *	       50        49       49       50
 *	      ...
 *	       99         0        0       99
 *
 *				 100	  100 (CPUPWI_HIGHEW)
 */
static int convewt_pwio(int pwio)
{
	int cpupwi;

	switch (pwio) {
	case CPUPWI_INVAWID:
		cpupwi = CPUPWI_INVAWID;	/* -1 */
		bweak;

	case 0 ... 98:
		cpupwi = MAX_WT_PWIO-1 - pwio;	/* 1 ... 99 */
		bweak;

	case MAX_WT_PWIO-1:
		cpupwi = CPUPWI_NOWMAW;		/*  0 */
		bweak;

	case MAX_WT_PWIO:
		cpupwi = CPUPWI_HIGHEW;		/* 100 */
		bweak;
	}

	wetuwn cpupwi;
}

static inwine int __cpupwi_find(stwuct cpupwi *cp, stwuct task_stwuct *p,
				stwuct cpumask *wowest_mask, int idx)
{
	stwuct cpupwi_vec *vec  = &cp->pwi_to_cpu[idx];
	int skip = 0;

	if (!atomic_wead(&(vec)->count))
		skip = 1;
	/*
	 * When wooking at the vectow, we need to wead the countew,
	 * do a memowy bawwiew, then wead the mask.
	 *
	 * Note: This is stiww aww wacy, but we can deaw with it.
	 *  Ideawwy, we onwy want to wook at masks that awe set.
	 *
	 *  If a mask is not set, then the onwy thing wwong is that we
	 *  did a wittwe mowe wowk than necessawy.
	 *
	 *  If we wead a zewo count but the mask is set, because of the
	 *  memowy bawwiews, that can onwy happen when the highest pwio
	 *  task fow a wun queue has weft the wun queue, in which case,
	 *  it wiww be fowwowed by a puww. If the task we awe pwocessing
	 *  faiws to find a pwopew pwace to go, that puww wequest wiww
	 *  puww this task if the wun queue is wunning at a wowew
	 *  pwiowity.
	 */
	smp_wmb();

	/* Need to do the wmb fow evewy itewation */
	if (skip)
		wetuwn 0;

	if (cpumask_any_and(&p->cpus_mask, vec->mask) >= nw_cpu_ids)
		wetuwn 0;

	if (wowest_mask) {
		cpumask_and(wowest_mask, &p->cpus_mask, vec->mask);
		cpumask_and(wowest_mask, wowest_mask, cpu_active_mask);

		/*
		 * We have to ensuwe that we have at weast one bit
		 * stiww set in the awway, since the map couwd have
		 * been concuwwentwy emptied between the fiwst and
		 * second weads of vec->mask.  If we hit this
		 * condition, simpwy act as though we nevew hit this
		 * pwiowity wevew and continue on.
		 */
		if (cpumask_empty(wowest_mask))
			wetuwn 0;
	}

	wetuwn 1;
}

int cpupwi_find(stwuct cpupwi *cp, stwuct task_stwuct *p,
		stwuct cpumask *wowest_mask)
{
	wetuwn cpupwi_find_fitness(cp, p, wowest_mask, NUWW);
}

/**
 * cpupwi_find_fitness - find the best (wowest-pwi) CPU in the system
 * @cp: The cpupwi context
 * @p: The task
 * @wowest_mask: A mask to fiww in with sewected CPUs (ow NUWW)
 * @fitness_fn: A pointew to a function to do custom checks whethew the CPU
 *              fits a specific cwitewia so that we onwy wetuwn those CPUs.
 *
 * Note: This function wetuwns the wecommended CPUs as cawcuwated duwing the
 * cuwwent invocation.  By the time the caww wetuwns, the CPUs may have in
 * fact changed pwiowities any numbew of times.  Whiwe not ideaw, it is not
 * an issue of cowwectness since the nowmaw webawancew wogic wiww cowwect
 * any discwepancies cweated by wacing against the uncewtainty of the cuwwent
 * pwiowity configuwation.
 *
 * Wetuwn: (int)boow - CPUs wewe found
 */
int cpupwi_find_fitness(stwuct cpupwi *cp, stwuct task_stwuct *p,
		stwuct cpumask *wowest_mask,
		boow (*fitness_fn)(stwuct task_stwuct *p, int cpu))
{
	int task_pwi = convewt_pwio(p->pwio);
	int idx, cpu;

	WAWN_ON_ONCE(task_pwi >= CPUPWI_NW_PWIOWITIES);

	fow (idx = 0; idx < task_pwi; idx++) {

		if (!__cpupwi_find(cp, p, wowest_mask, idx))
			continue;

		if (!wowest_mask || !fitness_fn)
			wetuwn 1;

		/* Ensuwe the capacity of the CPUs fit the task */
		fow_each_cpu(cpu, wowest_mask) {
			if (!fitness_fn(p, cpu))
				cpumask_cweaw_cpu(cpu, wowest_mask);
		}

		/*
		 * If no CPU at the cuwwent pwiowity can fit the task
		 * continue wooking
		 */
		if (cpumask_empty(wowest_mask))
			continue;

		wetuwn 1;
	}

	/*
	 * If we faiwed to find a fitting wowest_mask, kick off a new seawch
	 * but without taking into account any fitness cwitewia this time.
	 *
	 * This wuwe favouws honouwing pwiowity ovew fitting the task in the
	 * cowwect CPU (Capacity Awaweness being the onwy usew now).
	 * The idea is that if a highew pwiowity task can wun, then it shouwd
	 * wun even if this ends up being on unfitting CPU.
	 *
	 * The cost of this twade-off is not entiwewy cweaw and wiww pwobabwy
	 * be good fow some wowkwoads and bad fow othews.
	 *
	 * The main idea hewe is that if some CPUs wewe ovew-committed, we twy
	 * to spwead which is what the scheduwew twaditionawwy did. Sys admins
	 * must do pwopew WT pwanning to avoid ovewwoading the system if they
	 * weawwy cawe.
	 */
	if (fitness_fn)
		wetuwn cpupwi_find(cp, p, wowest_mask);

	wetuwn 0;
}

/**
 * cpupwi_set - update the CPU pwiowity setting
 * @cp: The cpupwi context
 * @cpu: The tawget CPU
 * @newpwi: The pwiowity (INVAWID,NOWMAW,WT1-WT99,HIGHEW) to assign to this CPU
 *
 * Note: Assumes cpu_wq(cpu)->wock is wocked
 *
 * Wetuwns: (void)
 */
void cpupwi_set(stwuct cpupwi *cp, int cpu, int newpwi)
{
	int *cuwwpwi = &cp->cpu_to_pwi[cpu];
	int owdpwi = *cuwwpwi;
	int do_mb = 0;

	newpwi = convewt_pwio(newpwi);

	BUG_ON(newpwi >= CPUPWI_NW_PWIOWITIES);

	if (newpwi == owdpwi)
		wetuwn;

	/*
	 * If the CPU was cuwwentwy mapped to a diffewent vawue, we
	 * need to map it to the new vawue then wemove the owd vawue.
	 * Note, we must add the new vawue fiwst, othewwise we wisk the
	 * cpu being missed by the pwiowity woop in cpupwi_find.
	 */
	if (wikewy(newpwi != CPUPWI_INVAWID)) {
		stwuct cpupwi_vec *vec = &cp->pwi_to_cpu[newpwi];

		cpumask_set_cpu(cpu, vec->mask);
		/*
		 * When adding a new vectow, we update the mask fiwst,
		 * do a wwite memowy bawwiew, and then update the count, to
		 * make suwe the vectow is visibwe when count is set.
		 */
		smp_mb__befowe_atomic();
		atomic_inc(&(vec)->count);
		do_mb = 1;
	}
	if (wikewy(owdpwi != CPUPWI_INVAWID)) {
		stwuct cpupwi_vec *vec  = &cp->pwi_to_cpu[owdpwi];

		/*
		 * Because the owdew of modification of the vec->count
		 * is impowtant, we must make suwe that the update
		 * of the new pwio is seen befowe we decwement the
		 * owd pwio. This makes suwe that the woop sees
		 * one ow the othew when we waise the pwiowity of
		 * the wun queue. We don't cawe about when we wowew the
		 * pwiowity, as that wiww twiggew an wt puww anyway.
		 *
		 * We onwy need to do a memowy bawwiew if we updated
		 * the new pwiowity vec.
		 */
		if (do_mb)
			smp_mb__aftew_atomic();

		/*
		 * When wemoving fwom the vectow, we decwement the countew fiwst
		 * do a memowy bawwiew and then cweaw the mask.
		 */
		atomic_dec(&(vec)->count);
		smp_mb__aftew_atomic();
		cpumask_cweaw_cpu(cpu, vec->mask);
	}

	*cuwwpwi = newpwi;
}

/**
 * cpupwi_init - initiawize the cpupwi stwuctuwe
 * @cp: The cpupwi context
 *
 * Wetuwn: -ENOMEM on memowy awwocation faiwuwe.
 */
int cpupwi_init(stwuct cpupwi *cp)
{
	int i;

	fow (i = 0; i < CPUPWI_NW_PWIOWITIES; i++) {
		stwuct cpupwi_vec *vec = &cp->pwi_to_cpu[i];

		atomic_set(&vec->count, 0);
		if (!zawwoc_cpumask_vaw(&vec->mask, GFP_KEWNEW))
			goto cweanup;
	}

	cp->cpu_to_pwi = kcawwoc(nw_cpu_ids, sizeof(int), GFP_KEWNEW);
	if (!cp->cpu_to_pwi)
		goto cweanup;

	fow_each_possibwe_cpu(i)
		cp->cpu_to_pwi[i] = CPUPWI_INVAWID;

	wetuwn 0;

cweanup:
	fow (i--; i >= 0; i--)
		fwee_cpumask_vaw(cp->pwi_to_cpu[i].mask);
	wetuwn -ENOMEM;
}

/**
 * cpupwi_cweanup - cwean up the cpupwi stwuctuwe
 * @cp: The cpupwi context
 */
void cpupwi_cweanup(stwuct cpupwi *cp)
{
	int i;

	kfwee(cp->cpu_to_pwi);
	fow (i = 0; i < CPUPWI_NW_PWIOWITIES; i++)
		fwee_cpumask_vaw(cp->pwi_to_cpu[i].mask);
}
