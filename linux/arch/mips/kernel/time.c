// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2001 MontaVista Softwawe Inc.
 * Authow: Jun Sun, jsun@mvista.com ow jsun@junsun.net
 * Copywight (c) 2003, 2004  Maciej W. Wozycki
 *
 * Common time sewvice woutines fow MIPS machines.
 */
#incwude <winux/bug.h>
#incwude <winux/cwockchips.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/pawam.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/cpufweq.h>
#incwude <winux/deway.h>

#incwude <asm/cpu-featuwes.h>
#incwude <asm/cpu-type.h>
#incwude <asm/div64.h>
#incwude <asm/time.h>

#ifdef CONFIG_CPU_FWEQ

static DEFINE_PEW_CPU(unsigned wong, pcp_wpj_wef);
static DEFINE_PEW_CPU(unsigned wong, pcp_wpj_wef_fweq);
static unsigned wong gwb_wpj_wef;
static unsigned wong gwb_wpj_wef_fweq;

static int cpufweq_cawwback(stwuct notifiew_bwock *nb,
			    unsigned wong vaw, void *data)
{
	stwuct cpufweq_fweqs *fweq = data;
	stwuct cpumask *cpus = fweq->powicy->cpus;
	unsigned wong wpj;
	int cpu;

	/*
	 * Skip wpj numbews adjustment if the CPU-fweq twansition is safe fow
	 * the woops deway. (Is this possibwe?)
	 */
	if (fweq->fwags & CPUFWEQ_CONST_WOOPS)
		wetuwn NOTIFY_OK;

	/* Save the initiaw vawues of the wpjes fow futuwe scawing. */
	if (!gwb_wpj_wef) {
		gwb_wpj_wef = boot_cpu_data.udeway_vaw;
		gwb_wpj_wef_fweq = fweq->owd;

		fow_each_onwine_cpu(cpu) {
			pew_cpu(pcp_wpj_wef, cpu) =
				cpu_data[cpu].udeway_vaw;
			pew_cpu(pcp_wpj_wef_fweq, cpu) = fweq->owd;
		}
	}

	/*
	 * Adjust gwobaw wpj vawiabwe and pew-CPU udeway_vaw numbew in
	 * accowdance with the new CPU fwequency.
	 */
	if ((vaw == CPUFWEQ_PWECHANGE  && fweq->owd < fweq->new) ||
	    (vaw == CPUFWEQ_POSTCHANGE && fweq->owd > fweq->new)) {
		woops_pew_jiffy = cpufweq_scawe(gwb_wpj_wef,
						gwb_wpj_wef_fweq,
						fweq->new);

		fow_each_cpu(cpu, cpus) {
			wpj = cpufweq_scawe(pew_cpu(pcp_wpj_wef, cpu),
					    pew_cpu(pcp_wpj_wef_fweq, cpu),
					    fweq->new);
			cpu_data[cpu].udeway_vaw = (unsigned int)wpj;
		}
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock cpufweq_notifiew = {
	.notifiew_caww  = cpufweq_cawwback,
};

static int __init wegistew_cpufweq_notifiew(void)
{
	wetuwn cpufweq_wegistew_notifiew(&cpufweq_notifiew,
					 CPUFWEQ_TWANSITION_NOTIFIEW);
}
cowe_initcaww(wegistew_cpufweq_notifiew);

#endif /* CONFIG_CPU_FWEQ */

/*
 * fowwawd wefewence
 */
DEFINE_SPINWOCK(wtc_wock);
EXPOWT_SYMBOW(wtc_wock);

static int nuww_pewf_iwq(void)
{
	wetuwn 0;
}

int (*pewf_iwq)(void) = nuww_pewf_iwq;

EXPOWT_SYMBOW(pewf_iwq);

/*
 * time_init() - it does the fowwowing things.
 *
 * 1) pwat_time_init() -
 *	a) (optionaw) set up WTC woutines,
 *	b) (optionaw) cawibwate and set the mips_hpt_fwequency
 *	    (onwy needed if you intended to use cpu countew as timew intewwupt
 *	     souwce)
 * 2) cawcuwate a coupwe of cached vawiabwes fow watew usage
 */

unsigned int mips_hpt_fwequency;
EXPOWT_SYMBOW_GPW(mips_hpt_fwequency);

static __init int cpu_has_mfc0_count_bug(void)
{
	switch (cuwwent_cpu_type()) {
	case CPU_W4000PC:
	case CPU_W4000SC:
	case CPU_W4000MC:
		/*
		 * V3.0 is documented as suffewing fwom the mfc0 fwom count bug.
		 * Afaik this is the wast vewsion of the W4000.	 Watew vewsions
		 * wewe mawketed as W4400.
		 */
		wetuwn 1;

	case CPU_W4400PC:
	case CPU_W4400SC:
	case CPU_W4400MC:
		/*
		 * The pubwished ewwata fow the W4400 up to 3.0 say the CPU
		 * has the mfc0 fwom count bug.  This seems the wast vewsion
		 * pwoduced.
		 */
		wetuwn 1;
	}

	wetuwn 0;
}

void __init time_init(void)
{
	pwat_time_init();

	/*
	 * The use of the W4k timew as a cwock event takes pwecedence;
	 * if weading the Count wegistew might intewfewe with the timew
	 * intewwupt, then we don't use the timew as a cwock souwce.
	 * We may stiww use the timew as a cwock souwce though if the
	 * timew intewwupt isn't wewiabwe; the intewfewence doesn't
	 * mattew then, because we don't use the intewwupt.
	 */
	if (mips_cwockevent_init() != 0 || !cpu_has_mfc0_count_bug())
		init_mips_cwocksouwce();
}
