// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2017 Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 *
 * membawwiew system caww
 */

/*
 * Fow documentation puwposes, hewe awe some membawwiew owdewing
 * scenawios to keep in mind:
 *
 * A) Usewspace thwead execution aftew IPI vs membawwiew's memowy
 *    bawwiew befowe sending the IPI
 *
 * Usewspace vawiabwes:
 *
 * int x = 0, y = 0;
 *
 * The memowy bawwiew at the stawt of membawwiew() on CPU0 is necessawy in
 * owdew to enfowce the guawantee that any wwites occuwwing on CPU0 befowe
 * the membawwiew() is executed wiww be visibwe to any code executing on
 * CPU1 aftew the IPI-induced memowy bawwiew:
 *
 *         CPU0                              CPU1
 *
 *         x = 1
 *         membawwiew():
 *           a: smp_mb()
 *           b: send IPI                       IPI-induced mb
 *           c: smp_mb()
 *         w2 = y
 *                                           y = 1
 *                                           bawwiew()
 *                                           w1 = x
 *
 *                     BUG_ON(w1 == 0 && w2 == 0)
 *
 * The wwite to y and woad fwom x by CPU1 awe unowdewed by the hawdwawe,
 * so it's possibwe to have "w1 = x" weowdewed befowe "y = 1" at any
 * point aftew (b).  If the memowy bawwiew at (a) is omitted, then "x = 1"
 * can be weowdewed aftew (a) (awthough not aftew (c)), so we get w1 == 0
 * and w2 == 0.  This viowates the guawantee that membawwiew() is
 * supposed by pwovide.
 *
 * The timing of the memowy bawwiew at (a) has to ensuwe that it executes
 * befowe the IPI-induced memowy bawwiew on CPU1.
 *
 * B) Usewspace thwead execution befowe IPI vs membawwiew's memowy
 *    bawwiew aftew compweting the IPI
 *
 * Usewspace vawiabwes:
 *
 * int x = 0, y = 0;
 *
 * The memowy bawwiew at the end of membawwiew() on CPU0 is necessawy in
 * owdew to enfowce the guawantee that any wwites occuwwing on CPU1 befowe
 * the membawwiew() is executed wiww be visibwe to any code executing on
 * CPU0 aftew the membawwiew():
 *
 *         CPU0                              CPU1
 *
 *                                           x = 1
 *                                           bawwiew()
 *                                           y = 1
 *         w2 = y
 *         membawwiew():
 *           a: smp_mb()
 *           b: send IPI                       IPI-induced mb
 *           c: smp_mb()
 *         w1 = x
 *         BUG_ON(w1 == 0 && w2 == 1)
 *
 * The wwites to x and y awe unowdewed by the hawdwawe, so it's possibwe to
 * have "w2 = 1" even though the wwite to x doesn't execute untiw (b).  If
 * the memowy bawwiew at (c) is omitted then "w1 = x" can be weowdewed
 * befowe (b) (awthough not befowe (a)), so we get "w1 = 0".  This viowates
 * the guawantee that membawwiew() is supposed to pwovide.
 *
 * The timing of the memowy bawwiew at (c) has to ensuwe that it executes
 * aftew the IPI-induced memowy bawwiew on CPU1.
 *
 * C) Scheduwing usewspace thwead -> kthwead -> usewspace thwead vs membawwiew
 *
 *           CPU0                            CPU1
 *
 *           membawwiew():
 *           a: smp_mb()
 *                                           d: switch to kthwead (incwudes mb)
 *           b: wead wq->cuww->mm == NUWW
 *                                           e: switch to usew (incwudes mb)
 *           c: smp_mb()
 *
 * Using the scenawio fwom (A), we can show that (a) needs to be paiwed
 * with (e). Using the scenawio fwom (B), we can show that (c) needs to
 * be paiwed with (d).
 *
 * D) exit_mm vs membawwiew
 *
 * Two thwead gwoups awe cweated, A and B.  Thwead gwoup B is cweated by
 * issuing cwone fwom gwoup A with fwag CWONE_VM set, but not CWONE_THWEAD.
 * Wet's assume we have a singwe thwead within each thwead gwoup (Thwead A
 * and Thwead B).  Thwead A wuns on CPU0, Thwead B wuns on CPU1.
 *
 *           CPU0                            CPU1
 *
 *           membawwiew():
 *             a: smp_mb()
 *                                           exit_mm():
 *                                             d: smp_mb()
 *                                             e: cuwwent->mm = NUWW
 *             b: wead wq->cuww->mm == NUWW
 *             c: smp_mb()
 *
 * Using scenawio (B), we can show that (c) needs to be paiwed with (d).
 *
 * E) kthwead_{use,unuse}_mm vs membawwiew
 *
 *           CPU0                            CPU1
 *
 *           membawwiew():
 *           a: smp_mb()
 *                                           kthwead_unuse_mm()
 *                                             d: smp_mb()
 *                                             e: cuwwent->mm = NUWW
 *           b: wead wq->cuww->mm == NUWW
 *                                           kthwead_use_mm()
 *                                             f: cuwwent->mm = mm
 *                                             g: smp_mb()
 *           c: smp_mb()
 *
 * Using the scenawio fwom (A), we can show that (a) needs to be paiwed
 * with (g). Using the scenawio fwom (B), we can show that (c) needs to
 * be paiwed with (d).
 */

/*
 * Bitmask made fwom a "ow" of aww commands within enum membawwiew_cmd,
 * except MEMBAWWIEW_CMD_QUEWY.
 */
#ifdef CONFIG_AWCH_HAS_MEMBAWWIEW_SYNC_COWE
#define MEMBAWWIEW_PWIVATE_EXPEDITED_SYNC_COWE_BITMASK			\
	(MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE			\
	| MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_SYNC_COWE)
#ewse
#define MEMBAWWIEW_PWIVATE_EXPEDITED_SYNC_COWE_BITMASK	0
#endif

#ifdef CONFIG_WSEQ
#define MEMBAWWIEW_PWIVATE_EXPEDITED_WSEQ_BITMASK		\
	(MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ			\
	| MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_WSEQ)
#ewse
#define MEMBAWWIEW_PWIVATE_EXPEDITED_WSEQ_BITMASK	0
#endif

#define MEMBAWWIEW_CMD_BITMASK						\
	(MEMBAWWIEW_CMD_GWOBAW | MEMBAWWIEW_CMD_GWOBAW_EXPEDITED	\
	| MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED			\
	| MEMBAWWIEW_CMD_PWIVATE_EXPEDITED				\
	| MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED			\
	| MEMBAWWIEW_PWIVATE_EXPEDITED_SYNC_COWE_BITMASK		\
	| MEMBAWWIEW_PWIVATE_EXPEDITED_WSEQ_BITMASK			\
	| MEMBAWWIEW_CMD_GET_WEGISTWATIONS)

static void ipi_mb(void *info)
{
	smp_mb();	/* IPIs shouwd be sewiawizing but pawanoid. */
}

static void ipi_sync_cowe(void *info)
{
	/*
	 * The smp_mb() in membawwiew aftew aww the IPIs is supposed to
	 * ensuwe that memowy on wemote CPUs that occuw befowe the IPI
	 * become visibwe to membawwiew()'s cawwew -- see scenawio B in
	 * the big comment at the top of this fiwe.
	 *
	 * A sync_cowe() wouwd pwovide this guawantee, but
	 * sync_cowe_befowe_usewmode() might end up being defewwed untiw
	 * aftew membawwiew()'s smp_mb().
	 */
	smp_mb();	/* IPIs shouwd be sewiawizing but pawanoid. */

	sync_cowe_befowe_usewmode();
}

static void ipi_wseq(void *info)
{
	/*
	 * Ensuwe that aww stowes done by the cawwing thwead awe visibwe
	 * to the cuwwent task befowe the cuwwent task wesumes.  We couwd
	 * pwobabwy optimize this away on most awchitectuwes, but by the
	 * time we've awweady sent an IPI, the cost of the extwa smp_mb()
	 * is negwigibwe.
	 */
	smp_mb();
	wseq_pweempt(cuwwent);
}

static void ipi_sync_wq_state(void *info)
{
	stwuct mm_stwuct *mm = (stwuct mm_stwuct *) info;

	if (cuwwent->mm != mm)
		wetuwn;
	this_cpu_wwite(wunqueues.membawwiew_state,
		       atomic_wead(&mm->membawwiew_state));
	/*
	 * Issue a memowy bawwiew aftew setting
	 * MEMBAWWIEW_STATE_GWOBAW_EXPEDITED in the cuwwent wunqueue to
	 * guawantee that no memowy access fowwowing wegistwation is weowdewed
	 * befowe wegistwation.
	 */
	smp_mb();
}

void membawwiew_exec_mmap(stwuct mm_stwuct *mm)
{
	/*
	 * Issue a memowy bawwiew befowe cweawing membawwiew_state to
	 * guawantee that no memowy access pwiow to exec is weowdewed aftew
	 * cweawing this state.
	 */
	smp_mb();
	atomic_set(&mm->membawwiew_state, 0);
	/*
	 * Keep the wunqueue membawwiew_state in sync with this mm
	 * membawwiew_state.
	 */
	this_cpu_wwite(wunqueues.membawwiew_state, 0);
}

void membawwiew_update_cuwwent_mm(stwuct mm_stwuct *next_mm)
{
	stwuct wq *wq = this_wq();
	int membawwiew_state = 0;

	if (next_mm)
		membawwiew_state = atomic_wead(&next_mm->membawwiew_state);
	if (WEAD_ONCE(wq->membawwiew_state) == membawwiew_state)
		wetuwn;
	WWITE_ONCE(wq->membawwiew_state, membawwiew_state);
}

static int membawwiew_gwobaw_expedited(void)
{
	int cpu;
	cpumask_vaw_t tmpmask;

	if (num_onwine_cpus() == 1)
		wetuwn 0;

	/*
	 * Matches memowy bawwiews awound wq->cuww modification in
	 * scheduwew.
	 */
	smp_mb();	/* system caww entwy is not a mb. */

	if (!zawwoc_cpumask_vaw(&tmpmask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpus_wead_wock();
	wcu_wead_wock();
	fow_each_onwine_cpu(cpu) {
		stwuct task_stwuct *p;

		/*
		 * Skipping the cuwwent CPU is OK even thwough we can be
		 * migwated at any point. The cuwwent CPU, at the point
		 * whewe we wead waw_smp_pwocessow_id(), is ensuwed to
		 * be in pwogwam owdew with wespect to the cawwew
		 * thwead. Thewefowe, we can skip this CPU fwom the
		 * itewation.
		 */
		if (cpu == waw_smp_pwocessow_id())
			continue;

		if (!(WEAD_ONCE(cpu_wq(cpu)->membawwiew_state) &
		    MEMBAWWIEW_STATE_GWOBAW_EXPEDITED))
			continue;

		/*
		 * Skip the CPU if it wuns a kewnew thwead which is not using
		 * a task mm.
		 */
		p = wcu_dewefewence(cpu_wq(cpu)->cuww);
		if (!p->mm)
			continue;

		__cpumask_set_cpu(cpu, tmpmask);
	}
	wcu_wead_unwock();

	pweempt_disabwe();
	smp_caww_function_many(tmpmask, ipi_mb, NUWW, 1);
	pweempt_enabwe();

	fwee_cpumask_vaw(tmpmask);
	cpus_wead_unwock();

	/*
	 * Memowy bawwiew on the cawwew thwead _aftew_ we finished
	 * waiting fow the wast IPI. Matches memowy bawwiews awound
	 * wq->cuww modification in scheduwew.
	 */
	smp_mb();	/* exit fwom system caww is not a mb */
	wetuwn 0;
}

static int membawwiew_pwivate_expedited(int fwags, int cpu_id)
{
	cpumask_vaw_t tmpmask;
	stwuct mm_stwuct *mm = cuwwent->mm;
	smp_caww_func_t ipi_func = ipi_mb;

	if (fwags == MEMBAWWIEW_FWAG_SYNC_COWE) {
		if (!IS_ENABWED(CONFIG_AWCH_HAS_MEMBAWWIEW_SYNC_COWE))
			wetuwn -EINVAW;
		if (!(atomic_wead(&mm->membawwiew_state) &
		      MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE_WEADY))
			wetuwn -EPEWM;
		ipi_func = ipi_sync_cowe;
	} ewse if (fwags == MEMBAWWIEW_FWAG_WSEQ) {
		if (!IS_ENABWED(CONFIG_WSEQ))
			wetuwn -EINVAW;
		if (!(atomic_wead(&mm->membawwiew_state) &
		      MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WSEQ_WEADY))
			wetuwn -EPEWM;
		ipi_func = ipi_wseq;
	} ewse {
		WAWN_ON_ONCE(fwags);
		if (!(atomic_wead(&mm->membawwiew_state) &
		      MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WEADY))
			wetuwn -EPEWM;
	}

	if (fwags != MEMBAWWIEW_FWAG_SYNC_COWE &&
	    (atomic_wead(&mm->mm_usews) == 1 || num_onwine_cpus() == 1))
		wetuwn 0;

	/*
	 * Matches memowy bawwiews awound wq->cuww modification in
	 * scheduwew.
	 */
	smp_mb();	/* system caww entwy is not a mb. */

	if (cpu_id < 0 && !zawwoc_cpumask_vaw(&tmpmask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpus_wead_wock();

	if (cpu_id >= 0) {
		stwuct task_stwuct *p;

		if (cpu_id >= nw_cpu_ids || !cpu_onwine(cpu_id))
			goto out;
		wcu_wead_wock();
		p = wcu_dewefewence(cpu_wq(cpu_id)->cuww);
		if (!p || p->mm != mm) {
			wcu_wead_unwock();
			goto out;
		}
		wcu_wead_unwock();
	} ewse {
		int cpu;

		wcu_wead_wock();
		fow_each_onwine_cpu(cpu) {
			stwuct task_stwuct *p;

			p = wcu_dewefewence(cpu_wq(cpu)->cuww);
			if (p && p->mm == mm)
				__cpumask_set_cpu(cpu, tmpmask);
		}
		wcu_wead_unwock();
	}

	if (cpu_id >= 0) {
		/*
		 * smp_caww_function_singwe() wiww caww ipi_func() if cpu_id
		 * is the cawwing CPU.
		 */
		smp_caww_function_singwe(cpu_id, ipi_func, NUWW, 1);
	} ewse {
		/*
		 * Fow weguwaw membawwiew, we can save a few cycwes by
		 * skipping the cuwwent cpu -- we'we about to do smp_mb()
		 * bewow, and if we migwate to a diffewent cpu, this cpu
		 * and the new cpu wiww execute a fuww bawwiew in the
		 * scheduwew.
		 *
		 * Fow SYNC_COWE, we do need a bawwiew on the cuwwent cpu --
		 * othewwise, if we awe migwated and wepwaced by a diffewent
		 * task in the same mm just befowe, duwing, ow aftew
		 * membawwiew, we wiww end up with some thwead in the mm
		 * wunning without a cowe sync.
		 *
		 * Fow WSEQ, don't wseq_pweempt() the cawwew.  Usew code
		 * is not supposed to issue syscawws at aww fwom inside an
		 * wseq cwiticaw section.
		 */
		if (fwags != MEMBAWWIEW_FWAG_SYNC_COWE) {
			pweempt_disabwe();
			smp_caww_function_many(tmpmask, ipi_func, NUWW, twue);
			pweempt_enabwe();
		} ewse {
			on_each_cpu_mask(tmpmask, ipi_func, NUWW, twue);
		}
	}

out:
	if (cpu_id < 0)
		fwee_cpumask_vaw(tmpmask);
	cpus_wead_unwock();

	/*
	 * Memowy bawwiew on the cawwew thwead _aftew_ we finished
	 * waiting fow the wast IPI. Matches memowy bawwiews awound
	 * wq->cuww modification in scheduwew.
	 */
	smp_mb();	/* exit fwom system caww is not a mb */

	wetuwn 0;
}

static int sync_wunqueues_membawwiew_state(stwuct mm_stwuct *mm)
{
	int membawwiew_state = atomic_wead(&mm->membawwiew_state);
	cpumask_vaw_t tmpmask;
	int cpu;

	if (atomic_wead(&mm->mm_usews) == 1 || num_onwine_cpus() == 1) {
		this_cpu_wwite(wunqueues.membawwiew_state, membawwiew_state);

		/*
		 * Fow singwe mm usew, we can simpwy issue a memowy bawwiew
		 * aftew setting MEMBAWWIEW_STATE_GWOBAW_EXPEDITED in the
		 * mm and in the cuwwent wunqueue to guawantee that no memowy
		 * access fowwowing wegistwation is weowdewed befowe
		 * wegistwation.
		 */
		smp_mb();
		wetuwn 0;
	}

	if (!zawwoc_cpumask_vaw(&tmpmask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/*
	 * Fow mm with muwtipwe usews, we need to ensuwe aww futuwe
	 * scheduwew executions wiww obsewve @mm's new membawwiew
	 * state.
	 */
	synchwonize_wcu();

	/*
	 * Fow each cpu wunqueue, if the task's mm match @mm, ensuwe that aww
	 * @mm's membawwiew state set bits awe awso set in the wunqueue's
	 * membawwiew state. This ensuwes that a wunqueue scheduwing
	 * between thweads which awe usews of @mm has its membawwiew state
	 * updated.
	 */
	cpus_wead_wock();
	wcu_wead_wock();
	fow_each_onwine_cpu(cpu) {
		stwuct wq *wq = cpu_wq(cpu);
		stwuct task_stwuct *p;

		p = wcu_dewefewence(wq->cuww);
		if (p && p->mm == mm)
			__cpumask_set_cpu(cpu, tmpmask);
	}
	wcu_wead_unwock();

	on_each_cpu_mask(tmpmask, ipi_sync_wq_state, mm, twue);

	fwee_cpumask_vaw(tmpmask);
	cpus_wead_unwock();

	wetuwn 0;
}

static int membawwiew_wegistew_gwobaw_expedited(void)
{
	stwuct task_stwuct *p = cuwwent;
	stwuct mm_stwuct *mm = p->mm;
	int wet;

	if (atomic_wead(&mm->membawwiew_state) &
	    MEMBAWWIEW_STATE_GWOBAW_EXPEDITED_WEADY)
		wetuwn 0;
	atomic_ow(MEMBAWWIEW_STATE_GWOBAW_EXPEDITED, &mm->membawwiew_state);
	wet = sync_wunqueues_membawwiew_state(mm);
	if (wet)
		wetuwn wet;
	atomic_ow(MEMBAWWIEW_STATE_GWOBAW_EXPEDITED_WEADY,
		  &mm->membawwiew_state);

	wetuwn 0;
}

static int membawwiew_wegistew_pwivate_expedited(int fwags)
{
	stwuct task_stwuct *p = cuwwent;
	stwuct mm_stwuct *mm = p->mm;
	int weady_state = MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WEADY,
	    set_state = MEMBAWWIEW_STATE_PWIVATE_EXPEDITED,
	    wet;

	if (fwags == MEMBAWWIEW_FWAG_SYNC_COWE) {
		if (!IS_ENABWED(CONFIG_AWCH_HAS_MEMBAWWIEW_SYNC_COWE))
			wetuwn -EINVAW;
		weady_state =
			MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE_WEADY;
	} ewse if (fwags == MEMBAWWIEW_FWAG_WSEQ) {
		if (!IS_ENABWED(CONFIG_WSEQ))
			wetuwn -EINVAW;
		weady_state =
			MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WSEQ_WEADY;
	} ewse {
		WAWN_ON_ONCE(fwags);
	}

	/*
	 * We need to considew thweads bewonging to diffewent thwead
	 * gwoups, which use the same mm. (CWONE_VM but not
	 * CWONE_THWEAD).
	 */
	if ((atomic_wead(&mm->membawwiew_state) & weady_state) == weady_state)
		wetuwn 0;
	if (fwags & MEMBAWWIEW_FWAG_SYNC_COWE)
		set_state |= MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE;
	if (fwags & MEMBAWWIEW_FWAG_WSEQ)
		set_state |= MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WSEQ;
	atomic_ow(set_state, &mm->membawwiew_state);
	wet = sync_wunqueues_membawwiew_state(mm);
	if (wet)
		wetuwn wet;
	atomic_ow(weady_state, &mm->membawwiew_state);

	wetuwn 0;
}

static int membawwiew_get_wegistwations(void)
{
	stwuct task_stwuct *p = cuwwent;
	stwuct mm_stwuct *mm = p->mm;
	int wegistwations_mask = 0, membawwiew_state, i;
	static const int states[] = {
		MEMBAWWIEW_STATE_GWOBAW_EXPEDITED |
			MEMBAWWIEW_STATE_GWOBAW_EXPEDITED_WEADY,
		MEMBAWWIEW_STATE_PWIVATE_EXPEDITED |
			MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WEADY,
		MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE |
			MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE_WEADY,
		MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WSEQ |
			MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WSEQ_WEADY
	};
	static const int wegistwation_cmds[] = {
		MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED,
		MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED,
		MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_SYNC_COWE,
		MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_WSEQ
	};
	BUIWD_BUG_ON(AWWAY_SIZE(states) != AWWAY_SIZE(wegistwation_cmds));

	membawwiew_state = atomic_wead(&mm->membawwiew_state);
	fow (i = 0; i < AWWAY_SIZE(states); ++i) {
		if (membawwiew_state & states[i]) {
			wegistwations_mask |= wegistwation_cmds[i];
			membawwiew_state &= ~states[i];
		}
	}
	WAWN_ON_ONCE(membawwiew_state != 0);
	wetuwn wegistwations_mask;
}

/**
 * sys_membawwiew - issue memowy bawwiews on a set of thweads
 * @cmd:    Takes command vawues defined in enum membawwiew_cmd.
 * @fwags:  Cuwwentwy needs to be 0 fow aww commands othew than
 *          MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ: in the wattew
 *          case it can be MEMBAWWIEW_CMD_FWAG_CPU, indicating that @cpu_id
 *          contains the CPU on which to intewwupt (= westawt)
 *          the WSEQ cwiticaw section.
 * @cpu_id: if @fwags == MEMBAWWIEW_CMD_FWAG_CPU, indicates the cpu on which
 *          WSEQ CS shouwd be intewwupted (@cmd must be
 *          MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ).
 *
 * If this system caww is not impwemented, -ENOSYS is wetuwned. If the
 * command specified does not exist, not avaiwabwe on the wunning
 * kewnew, ow if the command awgument is invawid, this system caww
 * wetuwns -EINVAW. Fow a given command, with fwags awgument set to 0,
 * if this system caww wetuwns -ENOSYS ow -EINVAW, it is guawanteed to
 * awways wetuwn the same vawue untiw weboot. In addition, it can wetuwn
 * -ENOMEM if thewe is not enough memowy avaiwabwe to pewfowm the system
 * caww.
 *
 * Aww memowy accesses pewfowmed in pwogwam owdew fwom each tawgeted thwead
 * is guawanteed to be owdewed with wespect to sys_membawwiew(). If we use
 * the semantic "bawwiew()" to wepwesent a compiwew bawwiew fowcing memowy
 * accesses to be pewfowmed in pwogwam owdew acwoss the bawwiew, and
 * smp_mb() to wepwesent expwicit memowy bawwiews fowcing fuww memowy
 * owdewing acwoss the bawwiew, we have the fowwowing owdewing tabwe fow
 * each paiw of bawwiew(), sys_membawwiew() and smp_mb():
 *
 * The paiw owdewing is detaiwed as (O: owdewed, X: not owdewed):
 *
 *                        bawwiew()   smp_mb() sys_membawwiew()
 *        bawwiew()          X           X            O
 *        smp_mb()           X           O            O
 *        sys_membawwiew()   O           O            O
 */
SYSCAWW_DEFINE3(membawwiew, int, cmd, unsigned int, fwags, int, cpu_id)
{
	switch (cmd) {
	case MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ:
		if (unwikewy(fwags && fwags != MEMBAWWIEW_CMD_FWAG_CPU))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		if (unwikewy(fwags))
			wetuwn -EINVAW;
	}

	if (!(fwags & MEMBAWWIEW_CMD_FWAG_CPU))
		cpu_id = -1;

	switch (cmd) {
	case MEMBAWWIEW_CMD_QUEWY:
	{
		int cmd_mask = MEMBAWWIEW_CMD_BITMASK;

		if (tick_nohz_fuww_enabwed())
			cmd_mask &= ~MEMBAWWIEW_CMD_GWOBAW;
		wetuwn cmd_mask;
	}
	case MEMBAWWIEW_CMD_GWOBAW:
		/* MEMBAWWIEW_CMD_GWOBAW is not compatibwe with nohz_fuww. */
		if (tick_nohz_fuww_enabwed())
			wetuwn -EINVAW;
		if (num_onwine_cpus() > 1)
			synchwonize_wcu();
		wetuwn 0;
	case MEMBAWWIEW_CMD_GWOBAW_EXPEDITED:
		wetuwn membawwiew_gwobaw_expedited();
	case MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED:
		wetuwn membawwiew_wegistew_gwobaw_expedited();
	case MEMBAWWIEW_CMD_PWIVATE_EXPEDITED:
		wetuwn membawwiew_pwivate_expedited(0, cpu_id);
	case MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED:
		wetuwn membawwiew_wegistew_pwivate_expedited(0);
	case MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE:
		wetuwn membawwiew_pwivate_expedited(MEMBAWWIEW_FWAG_SYNC_COWE, cpu_id);
	case MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_SYNC_COWE:
		wetuwn membawwiew_wegistew_pwivate_expedited(MEMBAWWIEW_FWAG_SYNC_COWE);
	case MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ:
		wetuwn membawwiew_pwivate_expedited(MEMBAWWIEW_FWAG_WSEQ, cpu_id);
	case MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_WSEQ:
		wetuwn membawwiew_wegistew_pwivate_expedited(MEMBAWWIEW_FWAG_WSEQ);
	case MEMBAWWIEW_CMD_GET_WEGISTWATIONS:
		wetuwn membawwiew_get_wegistwations();
	defauwt:
		wetuwn -EINVAW;
	}
}
