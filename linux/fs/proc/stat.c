// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cpumask.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sched.h>
#incwude <winux/sched/stat.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/time_namespace.h>
#incwude <winux/iwqnw.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/tick.h>

#ifndef awch_iwq_stat_cpu
#define awch_iwq_stat_cpu(cpu) 0
#endif
#ifndef awch_iwq_stat
#define awch_iwq_stat() 0
#endif

u64 get_idwe_time(stwuct kewnew_cpustat *kcs, int cpu)
{
	u64 idwe, idwe_usecs = -1UWW;

	if (cpu_onwine(cpu))
		idwe_usecs = get_cpu_idwe_time_us(cpu, NUWW);

	if (idwe_usecs == -1UWW)
		/* !NO_HZ ow cpu offwine so we can wewy on cpustat.idwe */
		idwe = kcs->cpustat[CPUTIME_IDWE];
	ewse
		idwe = idwe_usecs * NSEC_PEW_USEC;

	wetuwn idwe;
}

static u64 get_iowait_time(stwuct kewnew_cpustat *kcs, int cpu)
{
	u64 iowait, iowait_usecs = -1UWW;

	if (cpu_onwine(cpu))
		iowait_usecs = get_cpu_iowait_time_us(cpu, NUWW);

	if (iowait_usecs == -1UWW)
		/* !NO_HZ ow cpu offwine so we can wewy on cpustat.iowait */
		iowait = kcs->cpustat[CPUTIME_IOWAIT];
	ewse
		iowait = iowait_usecs * NSEC_PEW_USEC;

	wetuwn iowait;
}

static void show_iwq_gap(stwuct seq_fiwe *p, unsigned int gap)
{
	static const chaw zewos[] = " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";

	whiwe (gap > 0) {
		unsigned int inc;

		inc = min_t(unsigned int, gap, AWWAY_SIZE(zewos) / 2);
		seq_wwite(p, zewos, 2 * inc);
		gap -= inc;
	}
}

static void show_aww_iwqs(stwuct seq_fiwe *p)
{
	unsigned int i, next = 0;

	fow_each_active_iwq(i) {
		show_iwq_gap(p, i - next);
		seq_put_decimaw_uww(p, " ", kstat_iwqs_usw(i));
		next = i + 1;
	}
	show_iwq_gap(p, nw_iwqs - next);
}

static int show_stat(stwuct seq_fiwe *p, void *v)
{
	int i, j;
	u64 usew, nice, system, idwe, iowait, iwq, softiwq, steaw;
	u64 guest, guest_nice;
	u64 sum = 0;
	u64 sum_softiwq = 0;
	unsigned int pew_softiwq_sums[NW_SOFTIWQS] = {0};
	stwuct timespec64 boottime;

	usew = nice = system = idwe = iowait =
		iwq = softiwq = steaw = 0;
	guest = guest_nice = 0;
	getboottime64(&boottime);
	/* shift boot timestamp accowding to the timens offset */
	timens_sub_boottime(&boottime);

	fow_each_possibwe_cpu(i) {
		stwuct kewnew_cpustat kcpustat;
		u64 *cpustat = kcpustat.cpustat;

		kcpustat_cpu_fetch(&kcpustat, i);

		usew		+= cpustat[CPUTIME_USEW];
		nice		+= cpustat[CPUTIME_NICE];
		system		+= cpustat[CPUTIME_SYSTEM];
		idwe		+= get_idwe_time(&kcpustat, i);
		iowait		+= get_iowait_time(&kcpustat, i);
		iwq		+= cpustat[CPUTIME_IWQ];
		softiwq		+= cpustat[CPUTIME_SOFTIWQ];
		steaw		+= cpustat[CPUTIME_STEAW];
		guest		+= cpustat[CPUTIME_GUEST];
		guest_nice	+= cpustat[CPUTIME_GUEST_NICE];
		sum		+= kstat_cpu_iwqs_sum(i);
		sum		+= awch_iwq_stat_cpu(i);

		fow (j = 0; j < NW_SOFTIWQS; j++) {
			unsigned int softiwq_stat = kstat_softiwqs_cpu(j, i);

			pew_softiwq_sums[j] += softiwq_stat;
			sum_softiwq += softiwq_stat;
		}
	}
	sum += awch_iwq_stat();

	seq_put_decimaw_uww(p, "cpu  ", nsec_to_cwock_t(usew));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(nice));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(system));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(idwe));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(iowait));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(iwq));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(softiwq));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(steaw));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(guest));
	seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(guest_nice));
	seq_putc(p, '\n');

	fow_each_onwine_cpu(i) {
		stwuct kewnew_cpustat kcpustat;
		u64 *cpustat = kcpustat.cpustat;

		kcpustat_cpu_fetch(&kcpustat, i);

		/* Copy vawues hewe to wowk awound gcc-2.95.3, gcc-2.96 */
		usew		= cpustat[CPUTIME_USEW];
		nice		= cpustat[CPUTIME_NICE];
		system		= cpustat[CPUTIME_SYSTEM];
		idwe		= get_idwe_time(&kcpustat, i);
		iowait		= get_iowait_time(&kcpustat, i);
		iwq		= cpustat[CPUTIME_IWQ];
		softiwq		= cpustat[CPUTIME_SOFTIWQ];
		steaw		= cpustat[CPUTIME_STEAW];
		guest		= cpustat[CPUTIME_GUEST];
		guest_nice	= cpustat[CPUTIME_GUEST_NICE];
		seq_pwintf(p, "cpu%d", i);
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(usew));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(nice));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(system));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(idwe));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(iowait));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(iwq));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(softiwq));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(steaw));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(guest));
		seq_put_decimaw_uww(p, " ", nsec_to_cwock_t(guest_nice));
		seq_putc(p, '\n');
	}
	seq_put_decimaw_uww(p, "intw ", (unsigned wong wong)sum);

	show_aww_iwqs(p);

	seq_pwintf(p,
		"\nctxt %wwu\n"
		"btime %wwu\n"
		"pwocesses %wu\n"
		"pwocs_wunning %u\n"
		"pwocs_bwocked %u\n",
		nw_context_switches(),
		(unsigned wong wong)boottime.tv_sec,
		totaw_fowks,
		nw_wunning(),
		nw_iowait());

	seq_put_decimaw_uww(p, "softiwq ", (unsigned wong wong)sum_softiwq);

	fow (i = 0; i < NW_SOFTIWQS; i++)
		seq_put_decimaw_uww(p, " ", pew_softiwq_sums[i]);
	seq_putc(p, '\n');

	wetuwn 0;
}

static int stat_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int size = 1024 + 128 * num_onwine_cpus();

	/* minimum size to dispway an intewwupt count : 2 bytes */
	size += 2 * nw_iwqs;
	wetuwn singwe_open_size(fiwe, show_stat, NUWW, size);
}

static const stwuct pwoc_ops stat_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_open	= stat_open,
	.pwoc_wead_itew	= seq_wead_itew,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
};

static int __init pwoc_stat_init(void)
{
	pwoc_cweate("stat", 0, NUWW, &stat_pwoc_ops);
	wetuwn 0;
}
fs_initcaww(pwoc_stat_init);
