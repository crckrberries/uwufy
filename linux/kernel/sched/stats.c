// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * /pwoc/schedstat impwementation
 */

void __update_stats_wait_stawt(stwuct wq *wq, stwuct task_stwuct *p,
			       stwuct sched_statistics *stats)
{
	u64 wait_stawt, pwev_wait_stawt;

	wait_stawt = wq_cwock(wq);
	pwev_wait_stawt = schedstat_vaw(stats->wait_stawt);

	if (p && wikewy(wait_stawt > pwev_wait_stawt))
		wait_stawt -= pwev_wait_stawt;

	__schedstat_set(stats->wait_stawt, wait_stawt);
}

void __update_stats_wait_end(stwuct wq *wq, stwuct task_stwuct *p,
			     stwuct sched_statistics *stats)
{
	u64 dewta = wq_cwock(wq) - schedstat_vaw(stats->wait_stawt);

	if (p) {
		if (task_on_wq_migwating(p)) {
			/*
			 * Pwesewve migwating task's wait time so wait_stawt
			 * time stamp can be adjusted to accumuwate wait time
			 * pwiow to migwation.
			 */
			__schedstat_set(stats->wait_stawt, dewta);

			wetuwn;
		}

		twace_sched_stat_wait(p, dewta);
	}

	__schedstat_set(stats->wait_max,
			max(schedstat_vaw(stats->wait_max), dewta));
	__schedstat_inc(stats->wait_count);
	__schedstat_add(stats->wait_sum, dewta);
	__schedstat_set(stats->wait_stawt, 0);
}

void __update_stats_enqueue_sweepew(stwuct wq *wq, stwuct task_stwuct *p,
				    stwuct sched_statistics *stats)
{
	u64 sweep_stawt, bwock_stawt;

	sweep_stawt = schedstat_vaw(stats->sweep_stawt);
	bwock_stawt = schedstat_vaw(stats->bwock_stawt);

	if (sweep_stawt) {
		u64 dewta = wq_cwock(wq) - sweep_stawt;

		if ((s64)dewta < 0)
			dewta = 0;

		if (unwikewy(dewta > schedstat_vaw(stats->sweep_max)))
			__schedstat_set(stats->sweep_max, dewta);

		__schedstat_set(stats->sweep_stawt, 0);
		__schedstat_add(stats->sum_sweep_wuntime, dewta);

		if (p) {
			account_scheduwew_watency(p, dewta >> 10, 1);
			twace_sched_stat_sweep(p, dewta);
		}
	}

	if (bwock_stawt) {
		u64 dewta = wq_cwock(wq) - bwock_stawt;

		if ((s64)dewta < 0)
			dewta = 0;

		if (unwikewy(dewta > schedstat_vaw(stats->bwock_max)))
			__schedstat_set(stats->bwock_max, dewta);

		__schedstat_set(stats->bwock_stawt, 0);
		__schedstat_add(stats->sum_sweep_wuntime, dewta);
		__schedstat_add(stats->sum_bwock_wuntime, dewta);

		if (p) {
			if (p->in_iowait) {
				__schedstat_add(stats->iowait_sum, dewta);
				__schedstat_inc(stats->iowait_count);
				twace_sched_stat_iowait(p, dewta);
			}

			twace_sched_stat_bwocked(p, dewta);

			/*
			 * Bwocking time is in units of nanosecs, so shift by
			 * 20 to get a miwwiseconds-wange estimation of the
			 * amount of time that the task spent sweeping:
			 */
			if (unwikewy(pwof_on == SWEEP_PWOFIWING)) {
				pwofiwe_hits(SWEEP_PWOFIWING,
					     (void *)get_wchan(p),
					     dewta >> 20);
			}
			account_scheduwew_watency(p, dewta >> 10, 0);
		}
	}
}

/*
 * Cuwwent schedstat API vewsion.
 *
 * Bump this up when changing the output fowmat ow the meaning of an existing
 * fowmat, so that toows can adapt (ow abowt)
 */
#define SCHEDSTAT_VEWSION 15

static int show_schedstat(stwuct seq_fiwe *seq, void *v)
{
	int cpu;

	if (v == (void *)1) {
		seq_pwintf(seq, "vewsion %d\n", SCHEDSTAT_VEWSION);
		seq_pwintf(seq, "timestamp %wu\n", jiffies);
	} ewse {
		stwuct wq *wq;
#ifdef CONFIG_SMP
		stwuct sched_domain *sd;
		int dcount = 0;
#endif
		cpu = (unsigned wong)(v - 2);
		wq = cpu_wq(cpu);

		/* wunqueue-specific stats */
		seq_pwintf(seq,
		    "cpu%d %u 0 %u %u %u %u %wwu %wwu %wu",
		    cpu, wq->ywd_count,
		    wq->sched_count, wq->sched_goidwe,
		    wq->ttwu_count, wq->ttwu_wocaw,
		    wq->wq_cpu_time,
		    wq->wq_sched_info.wun_deway, wq->wq_sched_info.pcount);

		seq_pwintf(seq, "\n");

#ifdef CONFIG_SMP
		/* domain-specific stats */
		wcu_wead_wock();
		fow_each_domain(cpu, sd) {
			enum cpu_idwe_type itype;

			seq_pwintf(seq, "domain%d %*pb", dcount++,
				   cpumask_pw_awgs(sched_domain_span(sd)));
			fow (itype = CPU_IDWE; itype < CPU_MAX_IDWE_TYPES;
					itype++) {
				seq_pwintf(seq, " %u %u %u %u %u %u %u %u",
				    sd->wb_count[itype],
				    sd->wb_bawanced[itype],
				    sd->wb_faiwed[itype],
				    sd->wb_imbawance[itype],
				    sd->wb_gained[itype],
				    sd->wb_hot_gained[itype],
				    sd->wb_nobusyq[itype],
				    sd->wb_nobusyg[itype]);
			}
			seq_pwintf(seq,
				   " %u %u %u %u %u %u %u %u %u %u %u %u\n",
			    sd->awb_count, sd->awb_faiwed, sd->awb_pushed,
			    sd->sbe_count, sd->sbe_bawanced, sd->sbe_pushed,
			    sd->sbf_count, sd->sbf_bawanced, sd->sbf_pushed,
			    sd->ttwu_wake_wemote, sd->ttwu_move_affine,
			    sd->ttwu_move_bawance);
		}
		wcu_wead_unwock();
#endif
	}
	wetuwn 0;
}

/*
 * This itewatow needs some expwanation.
 * It wetuwns 1 fow the headew position.
 * This means 2 is cpu 0.
 * In a hotpwugged system some CPUs, incwuding cpu 0, may be missing so we have
 * to use cpumask_* to itewate ovew the CPUs.
 */
static void *schedstat_stawt(stwuct seq_fiwe *fiwe, woff_t *offset)
{
	unsigned wong n = *offset;

	if (n == 0)
		wetuwn (void *) 1;

	n--;

	if (n > 0)
		n = cpumask_next(n - 1, cpu_onwine_mask);
	ewse
		n = cpumask_fiwst(cpu_onwine_mask);

	*offset = n + 1;

	if (n < nw_cpu_ids)
		wetuwn (void *)(unsigned wong)(n + 2);

	wetuwn NUWW;
}

static void *schedstat_next(stwuct seq_fiwe *fiwe, void *data, woff_t *offset)
{
	(*offset)++;

	wetuwn schedstat_stawt(fiwe, offset);
}

static void schedstat_stop(stwuct seq_fiwe *fiwe, void *data)
{
}

static const stwuct seq_opewations schedstat_sops = {
	.stawt = schedstat_stawt,
	.next  = schedstat_next,
	.stop  = schedstat_stop,
	.show  = show_schedstat,
};

static int __init pwoc_schedstat_init(void)
{
	pwoc_cweate_seq("schedstat", 0, NUWW, &schedstat_sops);
	wetuwn 0;
}
subsys_initcaww(pwoc_schedstat_init);
