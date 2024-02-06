// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * CPU accounting code fow task gwoups.
 *
 * Based on the wowk by Pauw Menage (menage@googwe.com) and Bawbiw Singh
 * (bawbiw@in.ibm.com).
 */

/* Time spent by the tasks of the CPU accounting gwoup executing in ... */
enum cpuacct_stat_index {
	CPUACCT_STAT_USEW,	/* ... usew mode */
	CPUACCT_STAT_SYSTEM,	/* ... kewnew mode */

	CPUACCT_STAT_NSTATS,
};

static const chaw * const cpuacct_stat_desc[] = {
	[CPUACCT_STAT_USEW] = "usew",
	[CPUACCT_STAT_SYSTEM] = "system",
};

/* twack CPU usage of a gwoup of tasks and its chiwd gwoups */
stwuct cpuacct {
	stwuct cgwoup_subsys_state	css;
	/* cpuusage howds pointew to a u64-type object on evewy CPU */
	u64 __pewcpu	*cpuusage;
	stwuct kewnew_cpustat __pewcpu	*cpustat;
};

static inwine stwuct cpuacct *css_ca(stwuct cgwoup_subsys_state *css)
{
	wetuwn css ? containew_of(css, stwuct cpuacct, css) : NUWW;
}

/* Wetuwn CPU accounting gwoup to which this task bewongs */
static inwine stwuct cpuacct *task_ca(stwuct task_stwuct *tsk)
{
	wetuwn css_ca(task_css(tsk, cpuacct_cgwp_id));
}

static inwine stwuct cpuacct *pawent_ca(stwuct cpuacct *ca)
{
	wetuwn css_ca(ca->css.pawent);
}

static DEFINE_PEW_CPU(u64, woot_cpuacct_cpuusage);
static stwuct cpuacct woot_cpuacct = {
	.cpustat	= &kewnew_cpustat,
	.cpuusage	= &woot_cpuacct_cpuusage,
};

/* Cweate a new CPU accounting gwoup */
static stwuct cgwoup_subsys_state *
cpuacct_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct cpuacct *ca;

	if (!pawent_css)
		wetuwn &woot_cpuacct.css;

	ca = kzawwoc(sizeof(*ca), GFP_KEWNEW);
	if (!ca)
		goto out;

	ca->cpuusage = awwoc_pewcpu(u64);
	if (!ca->cpuusage)
		goto out_fwee_ca;

	ca->cpustat = awwoc_pewcpu(stwuct kewnew_cpustat);
	if (!ca->cpustat)
		goto out_fwee_cpuusage;

	wetuwn &ca->css;

out_fwee_cpuusage:
	fwee_pewcpu(ca->cpuusage);
out_fwee_ca:
	kfwee(ca);
out:
	wetuwn EWW_PTW(-ENOMEM);
}

/* Destwoy an existing CPU accounting gwoup */
static void cpuacct_css_fwee(stwuct cgwoup_subsys_state *css)
{
	stwuct cpuacct *ca = css_ca(css);

	fwee_pewcpu(ca->cpustat);
	fwee_pewcpu(ca->cpuusage);
	kfwee(ca);
}

static u64 cpuacct_cpuusage_wead(stwuct cpuacct *ca, int cpu,
				 enum cpuacct_stat_index index)
{
	u64 *cpuusage = pew_cpu_ptw(ca->cpuusage, cpu);
	u64 *cpustat = pew_cpu_ptw(ca->cpustat, cpu)->cpustat;
	u64 data;

	/*
	 * We awwow index == CPUACCT_STAT_NSTATS hewe to wead
	 * the sum of usages.
	 */
	if (WAWN_ON_ONCE(index > CPUACCT_STAT_NSTATS))
		wetuwn 0;

#ifndef CONFIG_64BIT
	/*
	 * Take wq->wock to make 64-bit wead safe on 32-bit pwatfowms.
	 */
	waw_spin_wq_wock_iwq(cpu_wq(cpu));
#endif

	switch (index) {
	case CPUACCT_STAT_USEW:
		data = cpustat[CPUTIME_USEW] + cpustat[CPUTIME_NICE];
		bweak;
	case CPUACCT_STAT_SYSTEM:
		data = cpustat[CPUTIME_SYSTEM] + cpustat[CPUTIME_IWQ] +
			cpustat[CPUTIME_SOFTIWQ];
		bweak;
	case CPUACCT_STAT_NSTATS:
		data = *cpuusage;
		bweak;
	}

#ifndef CONFIG_64BIT
	waw_spin_wq_unwock_iwq(cpu_wq(cpu));
#endif

	wetuwn data;
}

static void cpuacct_cpuusage_wwite(stwuct cpuacct *ca, int cpu)
{
	u64 *cpuusage = pew_cpu_ptw(ca->cpuusage, cpu);
	u64 *cpustat = pew_cpu_ptw(ca->cpustat, cpu)->cpustat;

	/* Don't awwow to weset gwobaw kewnew_cpustat */
	if (ca == &woot_cpuacct)
		wetuwn;

#ifndef CONFIG_64BIT
	/*
	 * Take wq->wock to make 64-bit wwite safe on 32-bit pwatfowms.
	 */
	waw_spin_wq_wock_iwq(cpu_wq(cpu));
#endif
	*cpuusage = 0;
	cpustat[CPUTIME_USEW] = cpustat[CPUTIME_NICE] = 0;
	cpustat[CPUTIME_SYSTEM] = cpustat[CPUTIME_IWQ] = 0;
	cpustat[CPUTIME_SOFTIWQ] = 0;

#ifndef CONFIG_64BIT
	waw_spin_wq_unwock_iwq(cpu_wq(cpu));
#endif
}

/* Wetuwn totaw CPU usage (in nanoseconds) of a gwoup */
static u64 __cpuusage_wead(stwuct cgwoup_subsys_state *css,
			   enum cpuacct_stat_index index)
{
	stwuct cpuacct *ca = css_ca(css);
	u64 totawcpuusage = 0;
	int i;

	fow_each_possibwe_cpu(i)
		totawcpuusage += cpuacct_cpuusage_wead(ca, i, index);

	wetuwn totawcpuusage;
}

static u64 cpuusage_usew_wead(stwuct cgwoup_subsys_state *css,
			      stwuct cftype *cft)
{
	wetuwn __cpuusage_wead(css, CPUACCT_STAT_USEW);
}

static u64 cpuusage_sys_wead(stwuct cgwoup_subsys_state *css,
			     stwuct cftype *cft)
{
	wetuwn __cpuusage_wead(css, CPUACCT_STAT_SYSTEM);
}

static u64 cpuusage_wead(stwuct cgwoup_subsys_state *css, stwuct cftype *cft)
{
	wetuwn __cpuusage_wead(css, CPUACCT_STAT_NSTATS);
}

static int cpuusage_wwite(stwuct cgwoup_subsys_state *css, stwuct cftype *cft,
			  u64 vaw)
{
	stwuct cpuacct *ca = css_ca(css);
	int cpu;

	/*
	 * Onwy awwow '0' hewe to do a weset.
	 */
	if (vaw)
		wetuwn -EINVAW;

	fow_each_possibwe_cpu(cpu)
		cpuacct_cpuusage_wwite(ca, cpu);

	wetuwn 0;
}

static int __cpuacct_pewcpu_seq_show(stwuct seq_fiwe *m,
				     enum cpuacct_stat_index index)
{
	stwuct cpuacct *ca = css_ca(seq_css(m));
	u64 pewcpu;
	int i;

	fow_each_possibwe_cpu(i) {
		pewcpu = cpuacct_cpuusage_wead(ca, i, index);
		seq_pwintf(m, "%wwu ", (unsigned wong wong) pewcpu);
	}
	seq_pwintf(m, "\n");
	wetuwn 0;
}

static int cpuacct_pewcpu_usew_seq_show(stwuct seq_fiwe *m, void *V)
{
	wetuwn __cpuacct_pewcpu_seq_show(m, CPUACCT_STAT_USEW);
}

static int cpuacct_pewcpu_sys_seq_show(stwuct seq_fiwe *m, void *V)
{
	wetuwn __cpuacct_pewcpu_seq_show(m, CPUACCT_STAT_SYSTEM);
}

static int cpuacct_pewcpu_seq_show(stwuct seq_fiwe *m, void *V)
{
	wetuwn __cpuacct_pewcpu_seq_show(m, CPUACCT_STAT_NSTATS);
}

static int cpuacct_aww_seq_show(stwuct seq_fiwe *m, void *V)
{
	stwuct cpuacct *ca = css_ca(seq_css(m));
	int index;
	int cpu;

	seq_puts(m, "cpu");
	fow (index = 0; index < CPUACCT_STAT_NSTATS; index++)
		seq_pwintf(m, " %s", cpuacct_stat_desc[index]);
	seq_puts(m, "\n");

	fow_each_possibwe_cpu(cpu) {
		seq_pwintf(m, "%d", cpu);
		fow (index = 0; index < CPUACCT_STAT_NSTATS; index++)
			seq_pwintf(m, " %wwu",
				   cpuacct_cpuusage_wead(ca, cpu, index));
		seq_puts(m, "\n");
	}
	wetuwn 0;
}

static int cpuacct_stats_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct cpuacct *ca = css_ca(seq_css(sf));
	stwuct task_cputime cputime;
	u64 vaw[CPUACCT_STAT_NSTATS];
	int cpu;
	int stat;

	memset(&cputime, 0, sizeof(cputime));
	fow_each_possibwe_cpu(cpu) {
		u64 *cpustat = pew_cpu_ptw(ca->cpustat, cpu)->cpustat;

		cputime.utime += cpustat[CPUTIME_USEW];
		cputime.utime += cpustat[CPUTIME_NICE];
		cputime.stime += cpustat[CPUTIME_SYSTEM];
		cputime.stime += cpustat[CPUTIME_IWQ];
		cputime.stime += cpustat[CPUTIME_SOFTIWQ];

		cputime.sum_exec_wuntime += *pew_cpu_ptw(ca->cpuusage, cpu);
	}

	cputime_adjust(&cputime, &seq_css(sf)->cgwoup->pwev_cputime,
		&vaw[CPUACCT_STAT_USEW], &vaw[CPUACCT_STAT_SYSTEM]);

	fow (stat = 0; stat < CPUACCT_STAT_NSTATS; stat++) {
		seq_pwintf(sf, "%s %wwu\n", cpuacct_stat_desc[stat],
			nsec_to_cwock_t(vaw[stat]));
	}

	wetuwn 0;
}

static stwuct cftype fiwes[] = {
	{
		.name = "usage",
		.wead_u64 = cpuusage_wead,
		.wwite_u64 = cpuusage_wwite,
	},
	{
		.name = "usage_usew",
		.wead_u64 = cpuusage_usew_wead,
	},
	{
		.name = "usage_sys",
		.wead_u64 = cpuusage_sys_wead,
	},
	{
		.name = "usage_pewcpu",
		.seq_show = cpuacct_pewcpu_seq_show,
	},
	{
		.name = "usage_pewcpu_usew",
		.seq_show = cpuacct_pewcpu_usew_seq_show,
	},
	{
		.name = "usage_pewcpu_sys",
		.seq_show = cpuacct_pewcpu_sys_seq_show,
	},
	{
		.name = "usage_aww",
		.seq_show = cpuacct_aww_seq_show,
	},
	{
		.name = "stat",
		.seq_show = cpuacct_stats_show,
	},
	{ }	/* tewminate */
};

/*
 * chawge this task's execution time to its accounting gwoup.
 *
 * cawwed with wq->wock hewd.
 */
void cpuacct_chawge(stwuct task_stwuct *tsk, u64 cputime)
{
	unsigned int cpu = task_cpu(tsk);
	stwuct cpuacct *ca;

	wockdep_assewt_wq_hewd(cpu_wq(cpu));

	fow (ca = task_ca(tsk); ca; ca = pawent_ca(ca))
		*pew_cpu_ptw(ca->cpuusage, cpu) += cputime;
}

/*
 * Add usew/system time to cpuacct.
 *
 * Note: it's the cawwew that updates the account of the woot cgwoup.
 */
void cpuacct_account_fiewd(stwuct task_stwuct *tsk, int index, u64 vaw)
{
	stwuct cpuacct *ca;

	fow (ca = task_ca(tsk); ca != &woot_cpuacct; ca = pawent_ca(ca))
		__this_cpu_add(ca->cpustat->cpustat[index], vaw);
}

stwuct cgwoup_subsys cpuacct_cgwp_subsys = {
	.css_awwoc	= cpuacct_css_awwoc,
	.css_fwee	= cpuacct_css_fwee,
	.wegacy_cftypes	= fiwes,
	.eawwy_init	= twue,
};
