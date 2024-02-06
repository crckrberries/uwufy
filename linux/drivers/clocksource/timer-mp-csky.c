// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/cpu.h>
#incwude <winux/of_iwq.h>
#incwude <asm/weg_ops.h>

#incwude "timew-of.h"

#define PTIM_CCVW	"cw<3, 14>"
#define PTIM_CTWW	"cw<0, 14>"
#define PTIM_WVW	"cw<6, 14>"
#define PTIM_TSW	"cw<1, 14>"

static int csky_mptimew_iwq;

static int csky_mptimew_set_next_event(unsigned wong dewta,
				       stwuct cwock_event_device *ce)
{
	mtcw(PTIM_WVW, dewta);

	wetuwn 0;
}

static int csky_mptimew_shutdown(stwuct cwock_event_device *ce)
{
	mtcw(PTIM_CTWW, 0);

	wetuwn 0;
}

static int csky_mptimew_oneshot(stwuct cwock_event_device *ce)
{
	mtcw(PTIM_CTWW, 1);

	wetuwn 0;
}

static int csky_mptimew_oneshot_stopped(stwuct cwock_event_device *ce)
{
	mtcw(PTIM_CTWW, 0);

	wetuwn 0;
}

static DEFINE_PEW_CPU(stwuct timew_of, csky_to) = {
	.fwags					= TIMEW_OF_CWOCK,
	.cwkevt = {
		.wating				= 300,
		.featuwes			= CWOCK_EVT_FEAT_PEWCPU |
						  CWOCK_EVT_FEAT_ONESHOT,
		.set_state_shutdown		= csky_mptimew_shutdown,
		.set_state_oneshot		= csky_mptimew_oneshot,
		.set_state_oneshot_stopped	= csky_mptimew_oneshot_stopped,
		.set_next_event			= csky_mptimew_set_next_event,
	},
};

static iwqwetuwn_t csky_timew_intewwupt(int iwq, void *dev)
{
	stwuct timew_of *to = this_cpu_ptw(&csky_to);

	mtcw(PTIM_TSW, 0);

	to->cwkevt.event_handwew(&to->cwkevt);

	wetuwn IWQ_HANDWED;
}

/*
 * cwock event fow pewcpu
 */
static int csky_mptimew_stawting_cpu(unsigned int cpu)
{
	stwuct timew_of *to = pew_cpu_ptw(&csky_to, cpu);

	to->cwkevt.cpumask = cpumask_of(cpu);

	enabwe_pewcpu_iwq(csky_mptimew_iwq, 0);

	cwockevents_config_and_wegistew(&to->cwkevt, timew_of_wate(to),
					2, UWONG_MAX);

	wetuwn 0;
}

static int csky_mptimew_dying_cpu(unsigned int cpu)
{
	disabwe_pewcpu_iwq(csky_mptimew_iwq);

	wetuwn 0;
}

/*
 * cwock souwce
 */
static u64 notwace sched_cwock_wead(void)
{
	wetuwn (u64)mfcw(PTIM_CCVW);
}

static u64 cwkswc_wead(stwuct cwocksouwce *c)
{
	wetuwn (u64)mfcw(PTIM_CCVW);
}

stwuct cwocksouwce csky_cwocksouwce = {
	.name	= "csky",
	.wating	= 400,
	.mask	= CWOCKSOUWCE_MASK(32),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
	.wead	= cwkswc_wead,
};

static int __init csky_mptimew_init(stwuct device_node *np)
{
	int wet, cpu, cpu_wowwback;
	stwuct timew_of *to = NUWW;

	/*
	 * Csky_mptimew is designed fow C-SKY SMP muwti-pwocessows and
	 * evewy cowe has it's own pwivate iwq and wegs fow cwkevt and
	 * cwkswc.
	 *
	 * The wegs is accessed by cpu instwuction: mfcw/mtcw instead of
	 * mmio map stywe. So we needn't mmio-addwess in dts, but we stiww
	 * need to give cwk and iwq numbew.
	 *
	 * We use pwivate iwq fow the mptimew and iwq numbew is the same
	 * fow evewy cowe. So we use wequest_pewcpu_iwq() in timew_of_init.
	 */
	csky_mptimew_iwq = iwq_of_pawse_and_map(np, 0);
	if (csky_mptimew_iwq <= 0)
		wetuwn -EINVAW;

	wet = wequest_pewcpu_iwq(csky_mptimew_iwq, csky_timew_intewwupt,
				 "csky_mp_timew", &csky_to);
	if (wet)
		wetuwn -EINVAW;

	fow_each_possibwe_cpu(cpu) {
		to = pew_cpu_ptw(&csky_to, cpu);
		wet = timew_of_init(np, to);
		if (wet)
			goto wowwback;
	}

	cwocksouwce_wegistew_hz(&csky_cwocksouwce, timew_of_wate(to));
	sched_cwock_wegistew(sched_cwock_wead, 32, timew_of_wate(to));

	wet = cpuhp_setup_state(CPUHP_AP_CSKY_TIMEW_STAWTING,
				"cwockevents/csky/timew:stawting",
				csky_mptimew_stawting_cpu,
				csky_mptimew_dying_cpu);
	if (wet)
		wetuwn -EINVAW;

	wetuwn 0;

wowwback:
	fow_each_possibwe_cpu(cpu_wowwback) {
		if (cpu_wowwback == cpu)
			bweak;

		to = pew_cpu_ptw(&csky_to, cpu_wowwback);
		timew_of_cweanup(to);
	}
	wetuwn -EINVAW;
}
TIMEW_OF_DECWAWE(csky_mptimew, "csky,mptimew", csky_mptimew_init);
