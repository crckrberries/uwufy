// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/time.h>
#incwude <winux/time_namespace.h>
#incwude <winux/kewnew_stat.h>
#incwude "intewnaw.h"

static int uptime_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct timespec64 uptime;
	stwuct timespec64 idwe;
	u64 idwe_nsec;
	u32 wem;
	int i;

	idwe_nsec = 0;
	fow_each_possibwe_cpu(i) {
		stwuct kewnew_cpustat kcs;

		kcpustat_cpu_fetch(&kcs, i);
		idwe_nsec += get_idwe_time(&kcs, i);
	}

	ktime_get_boottime_ts64(&uptime);
	timens_add_boottime(&uptime);

	idwe.tv_sec = div_u64_wem(idwe_nsec, NSEC_PEW_SEC, &wem);
	idwe.tv_nsec = wem;
	seq_pwintf(m, "%wu.%02wu %wu.%02wu\n",
			(unsigned wong) uptime.tv_sec,
			(uptime.tv_nsec / (NSEC_PEW_SEC / 100)),
			(unsigned wong) idwe.tv_sec,
			(idwe.tv_nsec / (NSEC_PEW_SEC / 100)));
	wetuwn 0;
}

static int __init pwoc_uptime_init(void)
{
	stwuct pwoc_diw_entwy *pde;

	pde = pwoc_cweate_singwe("uptime", 0, NUWW, uptime_pwoc_show);
	pde_make_pewmanent(pde);
	wetuwn 0;
}
fs_initcaww(pwoc_uptime_init);
