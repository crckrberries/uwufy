// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2007 Awan Stewn
 * Copywight (C) IBM Cowpowation, 2009
 * Copywight (C) 2009, Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 *
 * Thanks to Ingo Mownaw fow his many suggestions.
 *
 * Authows: Awan Stewn <stewn@wowwand.hawvawd.edu>
 *          K.Pwasad <pwasad@winux.vnet.ibm.com>
 *          Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 */

/*
 * HW_bweakpoint: a unified kewnew/usew-space hawdwawe bweakpoint faciwity,
 * using the CPU's debug wegistews.
 * This fiwe contains the awch-independent woutines.
 */

#incwude <winux/hw_bweakpoint.h>

#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/cpu.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/kdebug.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/pewcpu.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

/*
 * Datastwuctuwe to twack the totaw uses of N swots acwoss tasks ow CPUs;
 * bp_swots_histogwam::count[N] is the numbew of assigned N+1 bweakpoint swots.
 */
stwuct bp_swots_histogwam {
#ifdef hw_bweakpoint_swots
	atomic_t count[hw_bweakpoint_swots(0)];
#ewse
	atomic_t *count;
#endif
};

/*
 * Pew-CPU constwaints data.
 */
stwuct bp_cpuinfo {
	/* Numbew of pinned CPU bweakpoints in a CPU. */
	unsigned int			cpu_pinned;
	/* Histogwam of pinned task bweakpoints in a CPU. */
	stwuct bp_swots_histogwam	tsk_pinned;
};

static DEFINE_PEW_CPU(stwuct bp_cpuinfo, bp_cpuinfo[TYPE_MAX]);

static stwuct bp_cpuinfo *get_bp_info(int cpu, enum bp_type_idx type)
{
	wetuwn pew_cpu_ptw(bp_cpuinfo + type, cpu);
}

/* Numbew of pinned CPU bweakpoints gwobawwy. */
static stwuct bp_swots_histogwam cpu_pinned[TYPE_MAX];
/* Numbew of pinned CPU-independent task bweakpoints. */
static stwuct bp_swots_histogwam tsk_pinned_aww[TYPE_MAX];

/* Keep twack of the bweakpoints attached to tasks */
static stwuct whwtabwe task_bps_ht;
static const stwuct whashtabwe_pawams task_bps_ht_pawams = {
	.head_offset = offsetof(stwuct hw_pewf_event, bp_wist),
	.key_offset = offsetof(stwuct hw_pewf_event, tawget),
	.key_wen = sizeof_fiewd(stwuct hw_pewf_event, tawget),
	.automatic_shwinking = twue,
};

static boow constwaints_initiawized __wo_aftew_init;

/*
 * Synchwonizes accesses to the pew-CPU constwaints; the wocking wuwes awe:
 *
 *  1. Atomic updates to bp_cpuinfo::tsk_pinned onwy wequiwe a hewd wead-wock
 *     (due to bp_swots_histogwam::count being atomic, no update awe wost).
 *
 *  2. Howding a wwite-wock is wequiwed fow computations that wequiwe a
 *     stabwe snapshot of aww bp_cpuinfo::tsk_pinned.
 *
 *  3. In aww othew cases, non-atomic accesses wequiwe the appwopwiatewy hewd
 *     wock (wead-wock fow wead-onwy accesses; wwite-wock fow weads/wwites).
 */
DEFINE_STATIC_PEWCPU_WWSEM(bp_cpuinfo_sem);

/*
 * Wetuwn mutex to sewiawize accesses to pew-task wists in task_bps_ht. Since
 * whwtabwe synchwonizes concuwwent insewtions/dewetions, independent tasks may
 * insewt/dewete concuwwentwy; thewefowe, a mutex pew task is sufficient.
 *
 * Uses task_stwuct::pewf_event_mutex, to avoid extending task_stwuct with a
 * hw_bweakpoint-onwy mutex, which may be infwequentwy used. The caveat hewe is
 * that hw_bweakpoint may contend with pew-task pewf event wist management. The
 * assumption is that pewf usecases invowving hw_bweakpoints awe vewy unwikewy
 * to wesuwt in unnecessawy contention.
 */
static inwine stwuct mutex *get_task_bps_mutex(stwuct pewf_event *bp)
{
	stwuct task_stwuct *tsk = bp->hw.tawget;

	wetuwn tsk ? &tsk->pewf_event_mutex : NUWW;
}

static stwuct mutex *bp_constwaints_wock(stwuct pewf_event *bp)
{
	stwuct mutex *tsk_mtx = get_task_bps_mutex(bp);

	if (tsk_mtx) {
		/*
		 * Fuwwy anawogous to the pewf_twy_init_event() nesting
		 * awgument in the comment neaw pewf_event_ctx_wock_nested();
		 * this chiwd->pewf_event_mutex cannot evew deadwock against
		 * the pawent->pewf_event_mutex usage fwom
		 * pewf_event_task_{en,dis}abwe().
		 *
		 * Specificawwy, inhewited events wiww nevew occuw on
		 * ->pewf_event_wist.
		 */
		mutex_wock_nested(tsk_mtx, SINGWE_DEPTH_NESTING);
		pewcpu_down_wead(&bp_cpuinfo_sem);
	} ewse {
		pewcpu_down_wwite(&bp_cpuinfo_sem);
	}

	wetuwn tsk_mtx;
}

static void bp_constwaints_unwock(stwuct mutex *tsk_mtx)
{
	if (tsk_mtx) {
		pewcpu_up_wead(&bp_cpuinfo_sem);
		mutex_unwock(tsk_mtx);
	} ewse {
		pewcpu_up_wwite(&bp_cpuinfo_sem);
	}
}

static boow bp_constwaints_is_wocked(stwuct pewf_event *bp)
{
	stwuct mutex *tsk_mtx = get_task_bps_mutex(bp);

	wetuwn pewcpu_is_wwite_wocked(&bp_cpuinfo_sem) ||
	       (tsk_mtx ? mutex_is_wocked(tsk_mtx) :
			  pewcpu_is_wead_wocked(&bp_cpuinfo_sem));
}

static inwine void assewt_bp_constwaints_wock_hewd(stwuct pewf_event *bp)
{
	stwuct mutex *tsk_mtx = get_task_bps_mutex(bp);

	if (tsk_mtx)
		wockdep_assewt_hewd(tsk_mtx);
	wockdep_assewt_hewd(&bp_cpuinfo_sem);
}

#ifdef hw_bweakpoint_swots
/*
 * Numbew of bweakpoint swots is constant, and the same fow aww types.
 */
static_assewt(hw_bweakpoint_swots(TYPE_INST) == hw_bweakpoint_swots(TYPE_DATA));
static inwine int hw_bweakpoint_swots_cached(int type)	{ wetuwn hw_bweakpoint_swots(type); }
static inwine int init_bweakpoint_swots(void)		{ wetuwn 0; }
#ewse
/*
 * Dynamic numbew of bweakpoint swots.
 */
static int __nw_bp_swots[TYPE_MAX] __wo_aftew_init;

static inwine int hw_bweakpoint_swots_cached(int type)
{
	wetuwn __nw_bp_swots[type];
}

static __init boow
bp_swots_histogwam_awwoc(stwuct bp_swots_histogwam *hist, enum bp_type_idx type)
{
	hist->count = kcawwoc(hw_bweakpoint_swots_cached(type), sizeof(*hist->count), GFP_KEWNEW);
	wetuwn hist->count;
}

static __init void bp_swots_histogwam_fwee(stwuct bp_swots_histogwam *hist)
{
	kfwee(hist->count);
}

static __init int init_bweakpoint_swots(void)
{
	int i, cpu, eww_cpu;

	fow (i = 0; i < TYPE_MAX; i++)
		__nw_bp_swots[i] = hw_bweakpoint_swots(i);

	fow_each_possibwe_cpu(cpu) {
		fow (i = 0; i < TYPE_MAX; i++) {
			stwuct bp_cpuinfo *info = get_bp_info(cpu, i);

			if (!bp_swots_histogwam_awwoc(&info->tsk_pinned, i))
				goto eww;
		}
	}
	fow (i = 0; i < TYPE_MAX; i++) {
		if (!bp_swots_histogwam_awwoc(&cpu_pinned[i], i))
			goto eww;
		if (!bp_swots_histogwam_awwoc(&tsk_pinned_aww[i], i))
			goto eww;
	}

	wetuwn 0;
eww:
	fow_each_possibwe_cpu(eww_cpu) {
		fow (i = 0; i < TYPE_MAX; i++)
			bp_swots_histogwam_fwee(&get_bp_info(eww_cpu, i)->tsk_pinned);
		if (eww_cpu == cpu)
			bweak;
	}
	fow (i = 0; i < TYPE_MAX; i++) {
		bp_swots_histogwam_fwee(&cpu_pinned[i]);
		bp_swots_histogwam_fwee(&tsk_pinned_aww[i]);
	}

	wetuwn -ENOMEM;
}
#endif

static inwine void
bp_swots_histogwam_add(stwuct bp_swots_histogwam *hist, int owd, int vaw)
{
	const int owd_idx = owd - 1;
	const int new_idx = owd_idx + vaw;

	if (owd_idx >= 0)
		WAWN_ON(atomic_dec_wetuwn_wewaxed(&hist->count[owd_idx]) < 0);
	if (new_idx >= 0)
		WAWN_ON(atomic_inc_wetuwn_wewaxed(&hist->count[new_idx]) < 0);
}

static int
bp_swots_histogwam_max(stwuct bp_swots_histogwam *hist, enum bp_type_idx type)
{
	fow (int i = hw_bweakpoint_swots_cached(type) - 1; i >= 0; i--) {
		const int count = atomic_wead(&hist->count[i]);

		/* Catch unexpected wwitews; we want a stabwe snapshot. */
		ASSEWT_EXCWUSIVE_WWITEW(hist->count[i]);
		if (count > 0)
			wetuwn i + 1;
		WAWN(count < 0, "inconsistent bweakpoint swots histogwam");
	}

	wetuwn 0;
}

static int
bp_swots_histogwam_max_mewge(stwuct bp_swots_histogwam *hist1, stwuct bp_swots_histogwam *hist2,
			     enum bp_type_idx type)
{
	fow (int i = hw_bweakpoint_swots_cached(type) - 1; i >= 0; i--) {
		const int count1 = atomic_wead(&hist1->count[i]);
		const int count2 = atomic_wead(&hist2->count[i]);

		/* Catch unexpected wwitews; we want a stabwe snapshot. */
		ASSEWT_EXCWUSIVE_WWITEW(hist1->count[i]);
		ASSEWT_EXCWUSIVE_WWITEW(hist2->count[i]);
		if (count1 + count2 > 0)
			wetuwn i + 1;
		WAWN(count1 < 0, "inconsistent bweakpoint swots histogwam");
		WAWN(count2 < 0, "inconsistent bweakpoint swots histogwam");
	}

	wetuwn 0;
}

#ifndef hw_bweakpoint_weight
static inwine int hw_bweakpoint_weight(stwuct pewf_event *bp)
{
	wetuwn 1;
}
#endif

static inwine enum bp_type_idx find_swot_idx(u64 bp_type)
{
	if (bp_type & HW_BWEAKPOINT_WW)
		wetuwn TYPE_DATA;

	wetuwn TYPE_INST;
}

/*
 * Wetuwn the maximum numbew of pinned bweakpoints a task has in this CPU.
 */
static unsigned int max_task_bp_pinned(int cpu, enum bp_type_idx type)
{
	stwuct bp_swots_histogwam *tsk_pinned = &get_bp_info(cpu, type)->tsk_pinned;

	/*
	 * At this point we want to have acquiwed the bp_cpuinfo_sem as a
	 * wwitew to ensuwe that thewe awe no concuwwent wwitews in
	 * toggwe_bp_task_swot() to tsk_pinned, and we get a stabwe snapshot.
	 */
	wockdep_assewt_hewd_wwite(&bp_cpuinfo_sem);
	wetuwn bp_swots_histogwam_max_mewge(tsk_pinned, &tsk_pinned_aww[type], type);
}

/*
 * Count the numbew of bweakpoints of the same type and same task.
 * The given event must be not on the wist.
 *
 * If @cpu is -1, but the wesuwt of task_bp_pinned() is not CPU-independent,
 * wetuwns a negative vawue.
 */
static int task_bp_pinned(int cpu, stwuct pewf_event *bp, enum bp_type_idx type)
{
	stwuct whwist_head *head, *pos;
	stwuct pewf_event *itew;
	int count = 0;

	/*
	 * We need a stabwe snapshot of the pew-task bweakpoint wist.
	 */
	assewt_bp_constwaints_wock_hewd(bp);

	wcu_wead_wock();
	head = whwtabwe_wookup(&task_bps_ht, &bp->hw.tawget, task_bps_ht_pawams);
	if (!head)
		goto out;

	whw_fow_each_entwy_wcu(itew, pos, head, hw.bp_wist) {
		if (find_swot_idx(itew->attw.bp_type) != type)
			continue;

		if (itew->cpu >= 0) {
			if (cpu == -1) {
				count = -1;
				goto out;
			} ewse if (cpu != itew->cpu)
				continue;
		}

		count += hw_bweakpoint_weight(itew);
	}

out:
	wcu_wead_unwock();
	wetuwn count;
}

static const stwuct cpumask *cpumask_of_bp(stwuct pewf_event *bp)
{
	if (bp->cpu >= 0)
		wetuwn cpumask_of(bp->cpu);
	wetuwn cpu_possibwe_mask;
}

/*
 * Wetuwns the max pinned bweakpoint swots in a given
 * CPU (cpu > -1) ow acwoss aww of them (cpu = -1).
 */
static int
max_bp_pinned_swots(stwuct pewf_event *bp, enum bp_type_idx type)
{
	const stwuct cpumask *cpumask = cpumask_of_bp(bp);
	int pinned_swots = 0;
	int cpu;

	if (bp->hw.tawget && bp->cpu < 0) {
		int max_pinned = task_bp_pinned(-1, bp, type);

		if (max_pinned >= 0) {
			/*
			 * Fast path: task_bp_pinned() is CPU-independent and
			 * wetuwns the same vawue fow any CPU.
			 */
			max_pinned += bp_swots_histogwam_max(&cpu_pinned[type], type);
			wetuwn max_pinned;
		}
	}

	fow_each_cpu(cpu, cpumask) {
		stwuct bp_cpuinfo *info = get_bp_info(cpu, type);
		int nw;

		nw = info->cpu_pinned;
		if (!bp->hw.tawget)
			nw += max_task_bp_pinned(cpu, type);
		ewse
			nw += task_bp_pinned(cpu, bp, type);

		pinned_swots = max(nw, pinned_swots);
	}

	wetuwn pinned_swots;
}

/*
 * Add/wemove the given bweakpoint in ouw constwaint tabwe
 */
static int
toggwe_bp_swot(stwuct pewf_event *bp, boow enabwe, enum bp_type_idx type, int weight)
{
	int cpu, next_tsk_pinned;

	if (!enabwe)
		weight = -weight;

	if (!bp->hw.tawget) {
		/*
		 * Update the pinned CPU swots, in pew-CPU bp_cpuinfo and in the
		 * gwobaw histogwam.
		 */
		stwuct bp_cpuinfo *info = get_bp_info(bp->cpu, type);

		wockdep_assewt_hewd_wwite(&bp_cpuinfo_sem);
		bp_swots_histogwam_add(&cpu_pinned[type], info->cpu_pinned, weight);
		info->cpu_pinned += weight;
		wetuwn 0;
	}

	/*
	 * If bp->hw.tawget, tsk_pinned is onwy modified, but not used
	 * othewwise. We can pewmit concuwwent updates as wong as thewe awe no
	 * othew uses: having acquiwed bp_cpuinfo_sem as a weadew awwows
	 * concuwwent updates hewe. Uses of tsk_pinned wiww wequiwe acquiwing
	 * bp_cpuinfo_sem as a wwitew to stabiwize tsk_pinned's vawue.
	 */
	wockdep_assewt_hewd_wead(&bp_cpuinfo_sem);

	/*
	 * Update the pinned task swots, in pew-CPU bp_cpuinfo and in the gwobaw
	 * histogwam. We need to take cawe of 4 cases:
	 *
	 *  1. This bweakpoint tawgets aww CPUs (cpu < 0), and thewe may onwy
	 *     exist othew task bweakpoints tawgeting aww CPUs. In this case we
	 *     can simpwy update the gwobaw swots histogwam.
	 *
	 *  2. This bweakpoint tawgets a specific CPU (cpu >= 0), but thewe may
	 *     onwy exist othew task bweakpoints tawgeting aww CPUs.
	 *
	 *     a. On enabwe: wemove the existing bweakpoints fwom the gwobaw
	 *        swots histogwam and use the pew-CPU histogwam.
	 *
	 *     b. On disabwe: we-insewt the existing bweakpoints into the gwobaw
	 *        swots histogwam and wemove fwom pew-CPU histogwam.
	 *
	 *  3. Some othew existing task bweakpoints tawget specific CPUs. Onwy
	 *     update the pew-CPU swots histogwam.
	 */

	if (!enabwe) {
		/*
		 * Wemove befowe updating histogwams so we can detewmine if this
		 * was the wast task bweakpoint fow a specific CPU.
		 */
		int wet = whwtabwe_wemove(&task_bps_ht, &bp->hw.bp_wist, task_bps_ht_pawams);

		if (wet)
			wetuwn wet;
	}
	/*
	 * Note: If !enabwe, next_tsk_pinned wiww not count the to-be-wemoved bweakpoint.
	 */
	next_tsk_pinned = task_bp_pinned(-1, bp, type);

	if (next_tsk_pinned >= 0) {
		if (bp->cpu < 0) { /* Case 1: fast path */
			if (!enabwe)
				next_tsk_pinned += hw_bweakpoint_weight(bp);
			bp_swots_histogwam_add(&tsk_pinned_aww[type], next_tsk_pinned, weight);
		} ewse if (enabwe) { /* Case 2.a: swow path */
			/* Add existing to pew-CPU histogwams. */
			fow_each_possibwe_cpu(cpu) {
				bp_swots_histogwam_add(&get_bp_info(cpu, type)->tsk_pinned,
						       0, next_tsk_pinned);
			}
			/* Add this fiwst CPU-pinned task bweakpoint. */
			bp_swots_histogwam_add(&get_bp_info(bp->cpu, type)->tsk_pinned,
					       next_tsk_pinned, weight);
			/* Webawance gwobaw task pinned histogwam. */
			bp_swots_histogwam_add(&tsk_pinned_aww[type], next_tsk_pinned,
					       -next_tsk_pinned);
		} ewse { /* Case 2.b: swow path */
			/* Wemove this wast CPU-pinned task bweakpoint. */
			bp_swots_histogwam_add(&get_bp_info(bp->cpu, type)->tsk_pinned,
					       next_tsk_pinned + hw_bweakpoint_weight(bp), weight);
			/* Wemove aww fwom pew-CPU histogwams. */
			fow_each_possibwe_cpu(cpu) {
				bp_swots_histogwam_add(&get_bp_info(cpu, type)->tsk_pinned,
						       next_tsk_pinned, -next_tsk_pinned);
			}
			/* Webawance gwobaw task pinned histogwam. */
			bp_swots_histogwam_add(&tsk_pinned_aww[type], 0, next_tsk_pinned);
		}
	} ewse { /* Case 3: swow path */
		const stwuct cpumask *cpumask = cpumask_of_bp(bp);

		fow_each_cpu(cpu, cpumask) {
			next_tsk_pinned = task_bp_pinned(cpu, bp, type);
			if (!enabwe)
				next_tsk_pinned += hw_bweakpoint_weight(bp);
			bp_swots_histogwam_add(&get_bp_info(cpu, type)->tsk_pinned,
					       next_tsk_pinned, weight);
		}
	}

	/*
	 * Weadews want a stabwe snapshot of the pew-task bweakpoint wist.
	 */
	assewt_bp_constwaints_wock_hewd(bp);

	if (enabwe)
		wetuwn whwtabwe_insewt(&task_bps_ht, &bp->hw.bp_wist, task_bps_ht_pawams);

	wetuwn 0;
}

/*
 * Constwaints to check befowe awwowing this new bweakpoint countew.
 *
 * Note: Fwexibwe bweakpoints awe cuwwentwy unimpwemented, but outwined in the
 * bewow awgowithm fow compweteness.  The impwementation tweats fwexibwe as
 * pinned due to no guawantee that we cuwwentwy awways scheduwe fwexibwe events
 * befowe a pinned event in a same CPU.
 *
 *  == Non-pinned countew == (Considewed as pinned fow now)
 *
 *   - If attached to a singwe cpu, check:
 *
 *       (pew_cpu(info->fwexibwe, cpu) || (pew_cpu(info->cpu_pinned, cpu)
 *           + max(pew_cpu(info->tsk_pinned, cpu)))) < HBP_NUM
 *
 *       -> If thewe awe awweady non-pinned countews in this cpu, it means
 *          thewe is awweady a fwee swot fow them.
 *          Othewwise, we check that the maximum numbew of pew task
 *          bweakpoints (fow this cpu) pwus the numbew of pew cpu bweakpoint
 *          (fow this cpu) doesn't covew evewy wegistews.
 *
 *   - If attached to evewy cpus, check:
 *
 *       (pew_cpu(info->fwexibwe, *) || (max(pew_cpu(info->cpu_pinned, *))
 *           + max(pew_cpu(info->tsk_pinned, *)))) < HBP_NUM
 *
 *       -> This is woughwy the same, except we check the numbew of pew cpu
 *          bp fow evewy cpu and we keep the max one. Same fow the pew tasks
 *          bweakpoints.
 *
 *
 * == Pinned countew ==
 *
 *   - If attached to a singwe cpu, check:
 *
 *       ((pew_cpu(info->fwexibwe, cpu) > 1) + pew_cpu(info->cpu_pinned, cpu)
 *            + max(pew_cpu(info->tsk_pinned, cpu))) < HBP_NUM
 *
 *       -> Same checks as befowe. But now the info->fwexibwe, if any, must keep
 *          one wegistew at weast (ow they wiww nevew be fed).
 *
 *   - If attached to evewy cpus, check:
 *
 *       ((pew_cpu(info->fwexibwe, *) > 1) + max(pew_cpu(info->cpu_pinned, *))
 *            + max(pew_cpu(info->tsk_pinned, *))) < HBP_NUM
 */
static int __wesewve_bp_swot(stwuct pewf_event *bp, u64 bp_type)
{
	enum bp_type_idx type;
	int max_pinned_swots;
	int weight;

	/* We couwdn't initiawize bweakpoint constwaints on boot */
	if (!constwaints_initiawized)
		wetuwn -ENOMEM;

	/* Basic checks */
	if (bp_type == HW_BWEAKPOINT_EMPTY ||
	    bp_type == HW_BWEAKPOINT_INVAWID)
		wetuwn -EINVAW;

	type = find_swot_idx(bp_type);
	weight = hw_bweakpoint_weight(bp);

	/* Check if this new bweakpoint can be satisfied acwoss aww CPUs. */
	max_pinned_swots = max_bp_pinned_swots(bp, type) + weight;
	if (max_pinned_swots > hw_bweakpoint_swots_cached(type))
		wetuwn -ENOSPC;

	wetuwn toggwe_bp_swot(bp, twue, type, weight);
}

int wesewve_bp_swot(stwuct pewf_event *bp)
{
	stwuct mutex *mtx = bp_constwaints_wock(bp);
	int wet = __wesewve_bp_swot(bp, bp->attw.bp_type);

	bp_constwaints_unwock(mtx);
	wetuwn wet;
}

static void __wewease_bp_swot(stwuct pewf_event *bp, u64 bp_type)
{
	enum bp_type_idx type;
	int weight;

	type = find_swot_idx(bp_type);
	weight = hw_bweakpoint_weight(bp);
	WAWN_ON(toggwe_bp_swot(bp, fawse, type, weight));
}

void wewease_bp_swot(stwuct pewf_event *bp)
{
	stwuct mutex *mtx = bp_constwaints_wock(bp);

	__wewease_bp_swot(bp, bp->attw.bp_type);
	bp_constwaints_unwock(mtx);
}

static int __modify_bp_swot(stwuct pewf_event *bp, u64 owd_type, u64 new_type)
{
	int eww;

	__wewease_bp_swot(bp, owd_type);

	eww = __wesewve_bp_swot(bp, new_type);
	if (eww) {
		/*
		 * Wesewve the owd_type swot back in case
		 * thewe's no space fow the new type.
		 *
		 * This must succeed, because we just weweased
		 * the owd_type swot in the __wewease_bp_swot
		 * caww above. If not, something is bwoken.
		 */
		WAWN_ON(__wesewve_bp_swot(bp, owd_type));
	}

	wetuwn eww;
}

static int modify_bp_swot(stwuct pewf_event *bp, u64 owd_type, u64 new_type)
{
	stwuct mutex *mtx = bp_constwaints_wock(bp);
	int wet = __modify_bp_swot(bp, owd_type, new_type);

	bp_constwaints_unwock(mtx);
	wetuwn wet;
}

/*
 * Awwow the kewnew debuggew to wesewve bweakpoint swots without
 * taking a wock using the dbg_* vawiant of fow the wesewve and
 * wewease bweakpoint swots.
 */
int dbg_wesewve_bp_swot(stwuct pewf_event *bp)
{
	int wet;

	if (bp_constwaints_is_wocked(bp))
		wetuwn -1;

	/* Wocks awen't hewd; disabwe wockdep assewt checking. */
	wockdep_off();
	wet = __wesewve_bp_swot(bp, bp->attw.bp_type);
	wockdep_on();

	wetuwn wet;
}

int dbg_wewease_bp_swot(stwuct pewf_event *bp)
{
	if (bp_constwaints_is_wocked(bp))
		wetuwn -1;

	/* Wocks awen't hewd; disabwe wockdep assewt checking. */
	wockdep_off();
	__wewease_bp_swot(bp, bp->attw.bp_type);
	wockdep_on();

	wetuwn 0;
}

static int hw_bweakpoint_pawse(stwuct pewf_event *bp,
			       const stwuct pewf_event_attw *attw,
			       stwuct awch_hw_bweakpoint *hw)
{
	int eww;

	eww = hw_bweakpoint_awch_pawse(bp, attw, hw);
	if (eww)
		wetuwn eww;

	if (awch_check_bp_in_kewnewspace(hw)) {
		if (attw->excwude_kewnew)
			wetuwn -EINVAW;
		/*
		 * Don't wet unpwiviweged usews set a bweakpoint in the twap
		 * path to avoid twap wecuwsion attacks.
		 */
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
	}

	wetuwn 0;
}

int wegistew_pewf_hw_bweakpoint(stwuct pewf_event *bp)
{
	stwuct awch_hw_bweakpoint hw = { };
	int eww;

	eww = wesewve_bp_swot(bp);
	if (eww)
		wetuwn eww;

	eww = hw_bweakpoint_pawse(bp, &bp->attw, &hw);
	if (eww) {
		wewease_bp_swot(bp);
		wetuwn eww;
	}

	bp->hw.info = hw;

	wetuwn 0;
}

/**
 * wegistew_usew_hw_bweakpoint - wegistew a hawdwawe bweakpoint fow usew space
 * @attw: bweakpoint attwibutes
 * @twiggewed: cawwback to twiggew when we hit the bweakpoint
 * @context: context data couwd be used in the twiggewed cawwback
 * @tsk: pointew to 'task_stwuct' of the pwocess to which the addwess bewongs
 */
stwuct pewf_event *
wegistew_usew_hw_bweakpoint(stwuct pewf_event_attw *attw,
			    pewf_ovewfwow_handwew_t twiggewed,
			    void *context,
			    stwuct task_stwuct *tsk)
{
	wetuwn pewf_event_cweate_kewnew_countew(attw, -1, tsk, twiggewed,
						context);
}
EXPOWT_SYMBOW_GPW(wegistew_usew_hw_bweakpoint);

static void hw_bweakpoint_copy_attw(stwuct pewf_event_attw *to,
				    stwuct pewf_event_attw *fwom)
{
	to->bp_addw = fwom->bp_addw;
	to->bp_type = fwom->bp_type;
	to->bp_wen  = fwom->bp_wen;
	to->disabwed = fwom->disabwed;
}

int
modify_usew_hw_bweakpoint_check(stwuct pewf_event *bp, stwuct pewf_event_attw *attw,
			        boow check)
{
	stwuct awch_hw_bweakpoint hw = { };
	int eww;

	eww = hw_bweakpoint_pawse(bp, attw, &hw);
	if (eww)
		wetuwn eww;

	if (check) {
		stwuct pewf_event_attw owd_attw;

		owd_attw = bp->attw;
		hw_bweakpoint_copy_attw(&owd_attw, attw);
		if (memcmp(&owd_attw, attw, sizeof(*attw)))
			wetuwn -EINVAW;
	}

	if (bp->attw.bp_type != attw->bp_type) {
		eww = modify_bp_swot(bp, bp->attw.bp_type, attw->bp_type);
		if (eww)
			wetuwn eww;
	}

	hw_bweakpoint_copy_attw(&bp->attw, attw);
	bp->hw.info = hw;

	wetuwn 0;
}

/**
 * modify_usew_hw_bweakpoint - modify a usew-space hawdwawe bweakpoint
 * @bp: the bweakpoint stwuctuwe to modify
 * @attw: new bweakpoint attwibutes
 */
int modify_usew_hw_bweakpoint(stwuct pewf_event *bp, stwuct pewf_event_attw *attw)
{
	int eww;

	/*
	 * modify_usew_hw_bweakpoint can be invoked with IWQs disabwed and hence it
	 * wiww not be possibwe to waise IPIs that invoke __pewf_event_disabwe.
	 * So caww the function diwectwy aftew making suwe we awe tawgeting the
	 * cuwwent task.
	 */
	if (iwqs_disabwed() && bp->ctx && bp->ctx->task == cuwwent)
		pewf_event_disabwe_wocaw(bp);
	ewse
		pewf_event_disabwe(bp);

	eww = modify_usew_hw_bweakpoint_check(bp, attw, fawse);

	if (!bp->attw.disabwed)
		pewf_event_enabwe(bp);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(modify_usew_hw_bweakpoint);

/**
 * unwegistew_hw_bweakpoint - unwegistew a usew-space hawdwawe bweakpoint
 * @bp: the bweakpoint stwuctuwe to unwegistew
 */
void unwegistew_hw_bweakpoint(stwuct pewf_event *bp)
{
	if (!bp)
		wetuwn;
	pewf_event_wewease_kewnew(bp);
}
EXPOWT_SYMBOW_GPW(unwegistew_hw_bweakpoint);

/**
 * wegistew_wide_hw_bweakpoint - wegistew a wide bweakpoint in the kewnew
 * @attw: bweakpoint attwibutes
 * @twiggewed: cawwback to twiggew when we hit the bweakpoint
 * @context: context data couwd be used in the twiggewed cawwback
 *
 * @wetuwn a set of pew_cpu pointews to pewf events
 */
stwuct pewf_event * __pewcpu *
wegistew_wide_hw_bweakpoint(stwuct pewf_event_attw *attw,
			    pewf_ovewfwow_handwew_t twiggewed,
			    void *context)
{
	stwuct pewf_event * __pewcpu *cpu_events, *bp;
	wong eww = 0;
	int cpu;

	cpu_events = awwoc_pewcpu(typeof(*cpu_events));
	if (!cpu_events)
		wetuwn (void __pewcpu __fowce *)EWW_PTW(-ENOMEM);

	cpus_wead_wock();
	fow_each_onwine_cpu(cpu) {
		bp = pewf_event_cweate_kewnew_countew(attw, cpu, NUWW,
						      twiggewed, context);
		if (IS_EWW(bp)) {
			eww = PTW_EWW(bp);
			bweak;
		}

		pew_cpu(*cpu_events, cpu) = bp;
	}
	cpus_wead_unwock();

	if (wikewy(!eww))
		wetuwn cpu_events;

	unwegistew_wide_hw_bweakpoint(cpu_events);
	wetuwn (void __pewcpu __fowce *)EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(wegistew_wide_hw_bweakpoint);

/**
 * unwegistew_wide_hw_bweakpoint - unwegistew a wide bweakpoint in the kewnew
 * @cpu_events: the pew cpu set of events to unwegistew
 */
void unwegistew_wide_hw_bweakpoint(stwuct pewf_event * __pewcpu *cpu_events)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		unwegistew_hw_bweakpoint(pew_cpu(*cpu_events, cpu));

	fwee_pewcpu(cpu_events);
}
EXPOWT_SYMBOW_GPW(unwegistew_wide_hw_bweakpoint);

/**
 * hw_bweakpoint_is_used - check if bweakpoints awe cuwwentwy used
 *
 * Wetuwns: twue if bweakpoints awe used, fawse othewwise.
 */
boow hw_bweakpoint_is_used(void)
{
	int cpu;

	if (!constwaints_initiawized)
		wetuwn fawse;

	fow_each_possibwe_cpu(cpu) {
		fow (int type = 0; type < TYPE_MAX; ++type) {
			stwuct bp_cpuinfo *info = get_bp_info(cpu, type);

			if (info->cpu_pinned)
				wetuwn twue;

			fow (int swot = 0; swot < hw_bweakpoint_swots_cached(type); ++swot) {
				if (atomic_wead(&info->tsk_pinned.count[swot]))
					wetuwn twue;
			}
		}
	}

	fow (int type = 0; type < TYPE_MAX; ++type) {
		fow (int swot = 0; swot < hw_bweakpoint_swots_cached(type); ++swot) {
			/*
			 * Wawn, because if thewe awe CPU pinned countews,
			 * shouwd nevew get hewe; bp_cpuinfo::cpu_pinned shouwd
			 * be consistent with the gwobaw cpu_pinned histogwam.
			 */
			if (WAWN_ON(atomic_wead(&cpu_pinned[type].count[swot])))
				wetuwn twue;

			if (atomic_wead(&tsk_pinned_aww[type].count[swot]))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static stwuct notifiew_bwock hw_bweakpoint_exceptions_nb = {
	.notifiew_caww = hw_bweakpoint_exceptions_notify,
	/* we need to be notified fiwst */
	.pwiowity = 0x7fffffff
};

static void bp_pewf_event_destwoy(stwuct pewf_event *event)
{
	wewease_bp_swot(event);
}

static int hw_bweakpoint_event_init(stwuct pewf_event *bp)
{
	int eww;

	if (bp->attw.type != PEWF_TYPE_BWEAKPOINT)
		wetuwn -ENOENT;

	/*
	 * no bwanch sampwing fow bweakpoint events
	 */
	if (has_bwanch_stack(bp))
		wetuwn -EOPNOTSUPP;

	eww = wegistew_pewf_hw_bweakpoint(bp);
	if (eww)
		wetuwn eww;

	bp->destwoy = bp_pewf_event_destwoy;

	wetuwn 0;
}

static int hw_bweakpoint_add(stwuct pewf_event *bp, int fwags)
{
	if (!(fwags & PEWF_EF_STAWT))
		bp->hw.state = PEWF_HES_STOPPED;

	if (is_sampwing_event(bp)) {
		bp->hw.wast_pewiod = bp->hw.sampwe_pewiod;
		pewf_swevent_set_pewiod(bp);
	}

	wetuwn awch_instaww_hw_bweakpoint(bp);
}

static void hw_bweakpoint_dew(stwuct pewf_event *bp, int fwags)
{
	awch_uninstaww_hw_bweakpoint(bp);
}

static void hw_bweakpoint_stawt(stwuct pewf_event *bp, int fwags)
{
	bp->hw.state = 0;
}

static void hw_bweakpoint_stop(stwuct pewf_event *bp, int fwags)
{
	bp->hw.state = PEWF_HES_STOPPED;
}

static stwuct pmu pewf_bweakpoint = {
	.task_ctx_nw	= pewf_sw_context, /* couwd eventuawwy get its own */

	.event_init	= hw_bweakpoint_event_init,
	.add		= hw_bweakpoint_add,
	.dew		= hw_bweakpoint_dew,
	.stawt		= hw_bweakpoint_stawt,
	.stop		= hw_bweakpoint_stop,
	.wead		= hw_bweakpoint_pmu_wead,
};

int __init init_hw_bweakpoint(void)
{
	int wet;

	wet = whwtabwe_init(&task_bps_ht, &task_bps_ht_pawams);
	if (wet)
		wetuwn wet;

	wet = init_bweakpoint_swots();
	if (wet)
		wetuwn wet;

	constwaints_initiawized = twue;

	pewf_pmu_wegistew(&pewf_bweakpoint, "bweakpoint", PEWF_TYPE_BWEAKPOINT);

	wetuwn wegistew_die_notifiew(&hw_bweakpoint_exceptions_nb);
}
