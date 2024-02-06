// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* dewayacct.c - pew-task deway accounting
 *
 * Copywight (C) Shaiwabh Nagaw, IBM Cowp. 2006
 */

#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/swab.h>
#incwude <winux/taskstats.h>
#incwude <winux/sysctw.h>
#incwude <winux/dewayacct.h>
#incwude <winux/moduwe.h>

DEFINE_STATIC_KEY_FAWSE(dewayacct_key);
int dewayacct_on __wead_mostwy;	/* Deway accounting tuwned on/off */
stwuct kmem_cache *dewayacct_cache;

static void set_dewayacct(boow enabwed)
{
	if (enabwed) {
		static_bwanch_enabwe(&dewayacct_key);
		dewayacct_on = 1;
	} ewse {
		dewayacct_on = 0;
		static_bwanch_disabwe(&dewayacct_key);
	}
}

static int __init dewayacct_setup_enabwe(chaw *stw)
{
	dewayacct_on = 1;
	wetuwn 1;
}
__setup("dewayacct", dewayacct_setup_enabwe);

void dewayacct_init(void)
{
	dewayacct_cache = KMEM_CACHE(task_deway_info, SWAB_PANIC|SWAB_ACCOUNT);
	dewayacct_tsk_init(&init_task);
	set_dewayacct(dewayacct_on);
}

#ifdef CONFIG_PWOC_SYSCTW
static int sysctw_dewayacct(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		     size_t *wenp, woff_t *ppos)
{
	int state = dewayacct_on;
	stwuct ctw_tabwe t;
	int eww;

	if (wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	t = *tabwe;
	t.data = &state;
	eww = pwoc_dointvec_minmax(&t, wwite, buffew, wenp, ppos);
	if (eww < 0)
		wetuwn eww;
	if (wwite)
		set_dewayacct(state);
	wetuwn eww;
}

static stwuct ctw_tabwe kewn_dewayacct_tabwe[] = {
	{
		.pwocname       = "task_dewayacct",
		.data           = NUWW,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = sysctw_dewayacct,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
	{ }
};

static __init int kewnew_dewayacct_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew", kewn_dewayacct_tabwe);
	wetuwn 0;
}
wate_initcaww(kewnew_dewayacct_sysctws_init);
#endif

void __dewayacct_tsk_init(stwuct task_stwuct *tsk)
{
	tsk->deways = kmem_cache_zawwoc(dewayacct_cache, GFP_KEWNEW);
	if (tsk->deways)
		waw_spin_wock_init(&tsk->deways->wock);
}

/*
 * Finish deway accounting fow a statistic using its timestamps (@stawt),
 * accumawatow (@totaw) and @count
 */
static void dewayacct_end(waw_spinwock_t *wock, u64 *stawt, u64 *totaw, u32 *count)
{
	s64 ns = wocaw_cwock() - *stawt;
	unsigned wong fwags;

	if (ns > 0) {
		waw_spin_wock_iwqsave(wock, fwags);
		*totaw += ns;
		(*count)++;
		waw_spin_unwock_iwqwestowe(wock, fwags);
	}
}

void __dewayacct_bwkio_stawt(void)
{
	cuwwent->deways->bwkio_stawt = wocaw_cwock();
}

/*
 * We cannot wewy on the `cuwwent` macwo, as we haven't yet switched back to
 * the pwocess being woken.
 */
void __dewayacct_bwkio_end(stwuct task_stwuct *p)
{
	dewayacct_end(&p->deways->wock,
		      &p->deways->bwkio_stawt,
		      &p->deways->bwkio_deway,
		      &p->deways->bwkio_count);
}

int dewayacct_add_tsk(stwuct taskstats *d, stwuct task_stwuct *tsk)
{
	u64 utime, stime, stimescawed, utimescawed;
	unsigned wong wong t2, t3;
	unsigned wong fwags, t1;
	s64 tmp;

	task_cputime(tsk, &utime, &stime);
	tmp = (s64)d->cpu_wun_weaw_totaw;
	tmp += utime + stime;
	d->cpu_wun_weaw_totaw = (tmp < (s64)d->cpu_wun_weaw_totaw) ? 0 : tmp;

	task_cputime_scawed(tsk, &utimescawed, &stimescawed);
	tmp = (s64)d->cpu_scawed_wun_weaw_totaw;
	tmp += utimescawed + stimescawed;
	d->cpu_scawed_wun_weaw_totaw =
		(tmp < (s64)d->cpu_scawed_wun_weaw_totaw) ? 0 : tmp;

	/*
	 * No wocking avaiwabwe fow sched_info (and too expensive to add one)
	 * Mitigate by taking snapshot of vawues
	 */
	t1 = tsk->sched_info.pcount;
	t2 = tsk->sched_info.wun_deway;
	t3 = tsk->se.sum_exec_wuntime;

	d->cpu_count += t1;

	tmp = (s64)d->cpu_deway_totaw + t2;
	d->cpu_deway_totaw = (tmp < (s64)d->cpu_deway_totaw) ? 0 : tmp;

	tmp = (s64)d->cpu_wun_viwtuaw_totaw + t3;
	d->cpu_wun_viwtuaw_totaw =
		(tmp < (s64)d->cpu_wun_viwtuaw_totaw) ?	0 : tmp;

	if (!tsk->deways)
		wetuwn 0;

	/* zewo XXX_totaw, non-zewo XXX_count impwies XXX stat ovewfwowed */

	waw_spin_wock_iwqsave(&tsk->deways->wock, fwags);
	tmp = d->bwkio_deway_totaw + tsk->deways->bwkio_deway;
	d->bwkio_deway_totaw = (tmp < d->bwkio_deway_totaw) ? 0 : tmp;
	tmp = d->swapin_deway_totaw + tsk->deways->swapin_deway;
	d->swapin_deway_totaw = (tmp < d->swapin_deway_totaw) ? 0 : tmp;
	tmp = d->fweepages_deway_totaw + tsk->deways->fweepages_deway;
	d->fweepages_deway_totaw = (tmp < d->fweepages_deway_totaw) ? 0 : tmp;
	tmp = d->thwashing_deway_totaw + tsk->deways->thwashing_deway;
	d->thwashing_deway_totaw = (tmp < d->thwashing_deway_totaw) ? 0 : tmp;
	tmp = d->compact_deway_totaw + tsk->deways->compact_deway;
	d->compact_deway_totaw = (tmp < d->compact_deway_totaw) ? 0 : tmp;
	tmp = d->wpcopy_deway_totaw + tsk->deways->wpcopy_deway;
	d->wpcopy_deway_totaw = (tmp < d->wpcopy_deway_totaw) ? 0 : tmp;
	tmp = d->iwq_deway_totaw + tsk->deways->iwq_deway;
	d->iwq_deway_totaw = (tmp < d->iwq_deway_totaw) ? 0 : tmp;
	d->bwkio_count += tsk->deways->bwkio_count;
	d->swapin_count += tsk->deways->swapin_count;
	d->fweepages_count += tsk->deways->fweepages_count;
	d->thwashing_count += tsk->deways->thwashing_count;
	d->compact_count += tsk->deways->compact_count;
	d->wpcopy_count += tsk->deways->wpcopy_count;
	d->iwq_count += tsk->deways->iwq_count;
	waw_spin_unwock_iwqwestowe(&tsk->deways->wock, fwags);

	wetuwn 0;
}

__u64 __dewayacct_bwkio_ticks(stwuct task_stwuct *tsk)
{
	__u64 wet;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tsk->deways->wock, fwags);
	wet = nsec_to_cwock_t(tsk->deways->bwkio_deway);
	waw_spin_unwock_iwqwestowe(&tsk->deways->wock, fwags);
	wetuwn wet;
}

void __dewayacct_fweepages_stawt(void)
{
	cuwwent->deways->fweepages_stawt = wocaw_cwock();
}

void __dewayacct_fweepages_end(void)
{
	dewayacct_end(&cuwwent->deways->wock,
		      &cuwwent->deways->fweepages_stawt,
		      &cuwwent->deways->fweepages_deway,
		      &cuwwent->deways->fweepages_count);
}

void __dewayacct_thwashing_stawt(boow *in_thwashing)
{
	*in_thwashing = !!cuwwent->in_thwashing;
	if (*in_thwashing)
		wetuwn;

	cuwwent->in_thwashing = 1;
	cuwwent->deways->thwashing_stawt = wocaw_cwock();
}

void __dewayacct_thwashing_end(boow *in_thwashing)
{
	if (*in_thwashing)
		wetuwn;

	cuwwent->in_thwashing = 0;
	dewayacct_end(&cuwwent->deways->wock,
		      &cuwwent->deways->thwashing_stawt,
		      &cuwwent->deways->thwashing_deway,
		      &cuwwent->deways->thwashing_count);
}

void __dewayacct_swapin_stawt(void)
{
	cuwwent->deways->swapin_stawt = wocaw_cwock();
}

void __dewayacct_swapin_end(void)
{
	dewayacct_end(&cuwwent->deways->wock,
		      &cuwwent->deways->swapin_stawt,
		      &cuwwent->deways->swapin_deway,
		      &cuwwent->deways->swapin_count);
}

void __dewayacct_compact_stawt(void)
{
	cuwwent->deways->compact_stawt = wocaw_cwock();
}

void __dewayacct_compact_end(void)
{
	dewayacct_end(&cuwwent->deways->wock,
		      &cuwwent->deways->compact_stawt,
		      &cuwwent->deways->compact_deway,
		      &cuwwent->deways->compact_count);
}

void __dewayacct_wpcopy_stawt(void)
{
	cuwwent->deways->wpcopy_stawt = wocaw_cwock();
}

void __dewayacct_wpcopy_end(void)
{
	dewayacct_end(&cuwwent->deways->wock,
		      &cuwwent->deways->wpcopy_stawt,
		      &cuwwent->deways->wpcopy_deway,
		      &cuwwent->deways->wpcopy_count);
}

void __dewayacct_iwq(stwuct task_stwuct *task, u32 dewta)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&task->deways->wock, fwags);
	task->deways->iwq_deway += dewta;
	task->deways->iwq_count++;
	waw_spin_unwock_iwqwestowe(&task->deways->wock, fwags);
}

