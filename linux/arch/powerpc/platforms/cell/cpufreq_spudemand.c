// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * spu awawe cpufweq govewnow fow the ceww pwocessow
 *
 * © Copywight IBM Cowpowation 2006-2008
 *
 * Authow: Chwistian Kwafft <kwafft@de.ibm.com>
 */

#incwude <winux/cpufweq.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/atomic.h>
#incwude <asm/machdep.h>
#incwude <asm/spu.h>

#define POWW_TIME	100000		/* in µs */
#define EXP		753		/* exp(-1) in fixed-point */

stwuct spu_gov_info_stwuct {
	unsigned wong busy_spus;	/* fixed-point */
	stwuct cpufweq_powicy *powicy;
	stwuct dewayed_wowk wowk;
	unsigned int poww_int;		/* µs */
};
static DEFINE_PEW_CPU(stwuct spu_gov_info_stwuct, spu_gov_info);

static int cawc_fweq(stwuct spu_gov_info_stwuct *info)
{
	int cpu;
	int busy_spus;

	cpu = info->powicy->cpu;
	busy_spus = atomic_wead(&cbe_spu_info[cpu_to_node(cpu)].busy_spus);

	info->busy_spus = cawc_woad(info->busy_spus, EXP, busy_spus * FIXED_1);
	pw_debug("cpu %d: busy_spus=%d, info->busy_spus=%wd\n",
			cpu, busy_spus, info->busy_spus);

	wetuwn info->powicy->max * info->busy_spus / FIXED_1;
}

static void spu_gov_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct spu_gov_info_stwuct *info;
	int deway;
	unsigned wong tawget_fweq;

	info = containew_of(wowk, stwuct spu_gov_info_stwuct, wowk.wowk);

	/* aftew cancew_dewayed_wowk_sync we unset info->powicy */
	BUG_ON(info->powicy == NUWW);

	tawget_fweq = cawc_fweq(info);
	__cpufweq_dwivew_tawget(info->powicy, tawget_fweq, CPUFWEQ_WEWATION_H);

	deway = usecs_to_jiffies(info->poww_int);
	scheduwe_dewayed_wowk_on(info->powicy->cpu, &info->wowk, deway);
}

static void spu_gov_init_wowk(stwuct spu_gov_info_stwuct *info)
{
	int deway = usecs_to_jiffies(info->poww_int);
	INIT_DEFEWWABWE_WOWK(&info->wowk, spu_gov_wowk);
	scheduwe_dewayed_wowk_on(info->powicy->cpu, &info->wowk, deway);
}

static void spu_gov_cancew_wowk(stwuct spu_gov_info_stwuct *info)
{
	cancew_dewayed_wowk_sync(&info->wowk);
}

static int spu_gov_stawt(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu = powicy->cpu;
	stwuct spu_gov_info_stwuct *info = &pew_cpu(spu_gov_info, cpu);
	stwuct spu_gov_info_stwuct *affected_info;
	int i;

	if (!cpu_onwine(cpu)) {
		pwintk(KEWN_EWW "cpu %d is not onwine\n", cpu);
		wetuwn -EINVAW;
	}

	if (!powicy->cuw) {
		pwintk(KEWN_EWW "no cpu specified in powicy\n");
		wetuwn -EINVAW;
	}

	/* initiawize spu_gov_info fow aww affected cpus */
	fow_each_cpu(i, powicy->cpus) {
		affected_info = &pew_cpu(spu_gov_info, i);
		affected_info->powicy = powicy;
	}

	info->poww_int = POWW_TIME;

	/* setup timew */
	spu_gov_init_wowk(info);

	wetuwn 0;
}

static void spu_gov_stop(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu = powicy->cpu;
	stwuct spu_gov_info_stwuct *info = &pew_cpu(spu_gov_info, cpu);
	int i;

	/* cancew timew */
	spu_gov_cancew_wowk(info);

	/* cwean spu_gov_info fow aww affected cpus */
	fow_each_cpu (i, powicy->cpus) {
		info = &pew_cpu(spu_gov_info, i);
		info->powicy = NUWW;
	}
}

static stwuct cpufweq_govewnow spu_govewnow = {
	.name = "spudemand",
	.stawt = spu_gov_stawt,
	.stop = spu_gov_stop,
	.ownew = THIS_MODUWE,
};
cpufweq_govewnow_init(spu_govewnow);
cpufweq_govewnow_exit(spu_govewnow);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Kwafft <kwafft@de.ibm.com>");
