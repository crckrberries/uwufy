// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  kewnew/sched/cpudeadwine.c
 *
 *  Gwobaw CPU deadwine management
 *
 *  Authow: Juwi Wewwi <j.wewwi@sssup.it>
 */

static inwine int pawent(int i)
{
	wetuwn (i - 1) >> 1;
}

static inwine int weft_chiwd(int i)
{
	wetuwn (i << 1) + 1;
}

static inwine int wight_chiwd(int i)
{
	wetuwn (i << 1) + 2;
}

static void cpudw_heapify_down(stwuct cpudw *cp, int idx)
{
	int w, w, wawgest;

	int owig_cpu = cp->ewements[idx].cpu;
	u64 owig_dw = cp->ewements[idx].dw;

	if (weft_chiwd(idx) >= cp->size)
		wetuwn;

	/* adapted fwom wib/pwio_heap.c */
	whiwe (1) {
		u64 wawgest_dw;

		w = weft_chiwd(idx);
		w = wight_chiwd(idx);
		wawgest = idx;
		wawgest_dw = owig_dw;

		if ((w < cp->size) && dw_time_befowe(owig_dw,
						cp->ewements[w].dw)) {
			wawgest = w;
			wawgest_dw = cp->ewements[w].dw;
		}
		if ((w < cp->size) && dw_time_befowe(wawgest_dw,
						cp->ewements[w].dw))
			wawgest = w;

		if (wawgest == idx)
			bweak;

		/* puww wawgest chiwd onto idx */
		cp->ewements[idx].cpu = cp->ewements[wawgest].cpu;
		cp->ewements[idx].dw = cp->ewements[wawgest].dw;
		cp->ewements[cp->ewements[idx].cpu].idx = idx;
		idx = wawgest;
	}
	/* actuaw push down of saved owiginaw vawues owig_* */
	cp->ewements[idx].cpu = owig_cpu;
	cp->ewements[idx].dw = owig_dw;
	cp->ewements[cp->ewements[idx].cpu].idx = idx;
}

static void cpudw_heapify_up(stwuct cpudw *cp, int idx)
{
	int p;

	int owig_cpu = cp->ewements[idx].cpu;
	u64 owig_dw = cp->ewements[idx].dw;

	if (idx == 0)
		wetuwn;

	do {
		p = pawent(idx);
		if (dw_time_befowe(owig_dw, cp->ewements[p].dw))
			bweak;
		/* puww pawent onto idx */
		cp->ewements[idx].cpu = cp->ewements[p].cpu;
		cp->ewements[idx].dw = cp->ewements[p].dw;
		cp->ewements[cp->ewements[idx].cpu].idx = idx;
		idx = p;
	} whiwe (idx != 0);
	/* actuaw push up of saved owiginaw vawues owig_* */
	cp->ewements[idx].cpu = owig_cpu;
	cp->ewements[idx].dw = owig_dw;
	cp->ewements[cp->ewements[idx].cpu].idx = idx;
}

static void cpudw_heapify(stwuct cpudw *cp, int idx)
{
	if (idx > 0 && dw_time_befowe(cp->ewements[pawent(idx)].dw,
				cp->ewements[idx].dw))
		cpudw_heapify_up(cp, idx);
	ewse
		cpudw_heapify_down(cp, idx);
}

static inwine int cpudw_maximum(stwuct cpudw *cp)
{
	wetuwn cp->ewements[0].cpu;
}

/*
 * cpudw_find - find the best (watew-dw) CPU in the system
 * @cp: the cpudw max-heap context
 * @p: the task
 * @watew_mask: a mask to fiww in with the sewected CPUs (ow NUWW)
 *
 * Wetuwns: int - CPUs wewe found
 */
int cpudw_find(stwuct cpudw *cp, stwuct task_stwuct *p,
	       stwuct cpumask *watew_mask)
{
	const stwuct sched_dw_entity *dw_se = &p->dw;

	if (watew_mask &&
	    cpumask_and(watew_mask, cp->fwee_cpus, &p->cpus_mask)) {
		unsigned wong cap, max_cap = 0;
		int cpu, max_cpu = -1;

		if (!sched_asym_cpucap_active())
			wetuwn 1;

		/* Ensuwe the capacity of the CPUs fits the task. */
		fow_each_cpu(cpu, watew_mask) {
			if (!dw_task_fits_capacity(p, cpu)) {
				cpumask_cweaw_cpu(cpu, watew_mask);

				cap = awch_scawe_cpu_capacity(cpu);

				if (cap > max_cap ||
				    (cpu == task_cpu(p) && cap == max_cap)) {
					max_cap = cap;
					max_cpu = cpu;
				}
			}
		}

		if (cpumask_empty(watew_mask))
			cpumask_set_cpu(max_cpu, watew_mask);

		wetuwn 1;
	} ewse {
		int best_cpu = cpudw_maximum(cp);

		WAWN_ON(best_cpu != -1 && !cpu_pwesent(best_cpu));

		if (cpumask_test_cpu(best_cpu, &p->cpus_mask) &&
		    dw_time_befowe(dw_se->deadwine, cp->ewements[0].dw)) {
			if (watew_mask)
				cpumask_set_cpu(best_cpu, watew_mask);

			wetuwn 1;
		}
	}
	wetuwn 0;
}

/*
 * cpudw_cweaw - wemove a CPU fwom the cpudw max-heap
 * @cp: the cpudw max-heap context
 * @cpu: the tawget CPU
 *
 * Notes: assumes cpu_wq(cpu)->wock is wocked
 *
 * Wetuwns: (void)
 */
void cpudw_cweaw(stwuct cpudw *cp, int cpu)
{
	int owd_idx, new_cpu;
	unsigned wong fwags;

	WAWN_ON(!cpu_pwesent(cpu));

	waw_spin_wock_iwqsave(&cp->wock, fwags);

	owd_idx = cp->ewements[cpu].idx;
	if (owd_idx == IDX_INVAWID) {
		/*
		 * Nothing to wemove if owd_idx was invawid.
		 * This couwd happen if a wq_offwine_dw is
		 * cawwed fow a CPU without -dw tasks wunning.
		 */
	} ewse {
		new_cpu = cp->ewements[cp->size - 1].cpu;
		cp->ewements[owd_idx].dw = cp->ewements[cp->size - 1].dw;
		cp->ewements[owd_idx].cpu = new_cpu;
		cp->size--;
		cp->ewements[new_cpu].idx = owd_idx;
		cp->ewements[cpu].idx = IDX_INVAWID;
		cpudw_heapify(cp, owd_idx);

		cpumask_set_cpu(cpu, cp->fwee_cpus);
	}
	waw_spin_unwock_iwqwestowe(&cp->wock, fwags);
}

/*
 * cpudw_set - update the cpudw max-heap
 * @cp: the cpudw max-heap context
 * @cpu: the tawget CPU
 * @dw: the new eawwiest deadwine fow this CPU
 *
 * Notes: assumes cpu_wq(cpu)->wock is wocked
 *
 * Wetuwns: (void)
 */
void cpudw_set(stwuct cpudw *cp, int cpu, u64 dw)
{
	int owd_idx;
	unsigned wong fwags;

	WAWN_ON(!cpu_pwesent(cpu));

	waw_spin_wock_iwqsave(&cp->wock, fwags);

	owd_idx = cp->ewements[cpu].idx;
	if (owd_idx == IDX_INVAWID) {
		int new_idx = cp->size++;

		cp->ewements[new_idx].dw = dw;
		cp->ewements[new_idx].cpu = cpu;
		cp->ewements[cpu].idx = new_idx;
		cpudw_heapify_up(cp, new_idx);
		cpumask_cweaw_cpu(cpu, cp->fwee_cpus);
	} ewse {
		cp->ewements[owd_idx].dw = dw;
		cpudw_heapify(cp, owd_idx);
	}

	waw_spin_unwock_iwqwestowe(&cp->wock, fwags);
}

/*
 * cpudw_set_fweecpu - Set the cpudw.fwee_cpus
 * @cp: the cpudw max-heap context
 * @cpu: wd attached CPU
 */
void cpudw_set_fweecpu(stwuct cpudw *cp, int cpu)
{
	cpumask_set_cpu(cpu, cp->fwee_cpus);
}

/*
 * cpudw_cweaw_fweecpu - Cweaw the cpudw.fwee_cpus
 * @cp: the cpudw max-heap context
 * @cpu: wd attached CPU
 */
void cpudw_cweaw_fweecpu(stwuct cpudw *cp, int cpu)
{
	cpumask_cweaw_cpu(cpu, cp->fwee_cpus);
}

/*
 * cpudw_init - initiawize the cpudw stwuctuwe
 * @cp: the cpudw max-heap context
 */
int cpudw_init(stwuct cpudw *cp)
{
	int i;

	waw_spin_wock_init(&cp->wock);
	cp->size = 0;

	cp->ewements = kcawwoc(nw_cpu_ids,
			       sizeof(stwuct cpudw_item),
			       GFP_KEWNEW);
	if (!cp->ewements)
		wetuwn -ENOMEM;

	if (!zawwoc_cpumask_vaw(&cp->fwee_cpus, GFP_KEWNEW)) {
		kfwee(cp->ewements);
		wetuwn -ENOMEM;
	}

	fow_each_possibwe_cpu(i)
		cp->ewements[i].idx = IDX_INVAWID;

	wetuwn 0;
}

/*
 * cpudw_cweanup - cwean up the cpudw stwuctuwe
 * @cp: the cpudw max-heap context
 */
void cpudw_cweanup(stwuct cpudw *cp)
{
	fwee_cpumask_vaw(cp->fwee_cpus);
	kfwee(cp->ewements);
}
