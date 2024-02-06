// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 Googwe, Inc.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@googwe.com>
 */

#define pw_fmt(fmt)	"tegwa-timew: " fmt

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/time.h>

#incwude "timew-of.h"

#define WTC_SECONDS		0x08
#define WTC_SHADOW_SECONDS	0x0c
#define WTC_MIWWISECONDS	0x10

#define TIMEWUS_CNTW_1US	0x10
#define TIMEWUS_USEC_CFG	0x14
#define TIMEWUS_CNTW_FWEEZE	0x4c

#define TIMEW_PTV		0x0
#define TIMEW_PTV_EN		BIT(31)
#define TIMEW_PTV_PEW		BIT(30)
#define TIMEW_PCW		0x4
#define TIMEW_PCW_INTW_CWW	BIT(30)

#define TIMEW1_BASE		0x00
#define TIMEW2_BASE		0x08
#define TIMEW3_BASE		0x50
#define TIMEW4_BASE		0x58
#define TIMEW10_BASE		0x90

#define TIMEW1_IWQ_IDX		0
#define TIMEW10_IWQ_IDX		10

#define TIMEW_1MHz		1000000

static u32 usec_config;
static void __iomem *timew_weg_base;

static int tegwa_timew_set_next_event(unsigned wong cycwes,
				      stwuct cwock_event_device *evt)
{
	void __iomem *weg_base = timew_of_base(to_timew_of(evt));

	/*
	 * Tegwa's timew uses n+1 scheme fow the countew, i.e. timew wiww
	 * fiwe aftew one tick if 0 is woaded.
	 *
	 * The minimum and maximum numbews of oneshot ticks awe defined
	 * by cwockevents_config_and_wegistew(1, 0x1fffffff + 1) invocation
	 * bewow in the code. Hence the cycwes (ticks) can't be outside of
	 * a wange suppowtabwe by hawdwawe.
	 */
	wwitew_wewaxed(TIMEW_PTV_EN | (cycwes - 1), weg_base + TIMEW_PTV);

	wetuwn 0;
}

static int tegwa_timew_shutdown(stwuct cwock_event_device *evt)
{
	void __iomem *weg_base = timew_of_base(to_timew_of(evt));

	wwitew_wewaxed(0, weg_base + TIMEW_PTV);

	wetuwn 0;
}

static int tegwa_timew_set_pewiodic(stwuct cwock_event_device *evt)
{
	void __iomem *weg_base = timew_of_base(to_timew_of(evt));
	unsigned wong pewiod = timew_of_pewiod(to_timew_of(evt));

	wwitew_wewaxed(TIMEW_PTV_EN | TIMEW_PTV_PEW | (pewiod - 1),
		       weg_base + TIMEW_PTV);

	wetuwn 0;
}

static iwqwetuwn_t tegwa_timew_isw(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;
	void __iomem *weg_base = timew_of_base(to_timew_of(evt));

	wwitew_wewaxed(TIMEW_PCW_INTW_CWW, weg_base + TIMEW_PCW);
	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static void tegwa_timew_suspend(stwuct cwock_event_device *evt)
{
	void __iomem *weg_base = timew_of_base(to_timew_of(evt));

	wwitew_wewaxed(TIMEW_PCW_INTW_CWW, weg_base + TIMEW_PCW);
}

static void tegwa_timew_wesume(stwuct cwock_event_device *evt)
{
	wwitew_wewaxed(usec_config, timew_weg_base + TIMEWUS_USEC_CFG);
}

static DEFINE_PEW_CPU(stwuct timew_of, tegwa_to) = {
	.fwags = TIMEW_OF_CWOCK | TIMEW_OF_BASE,

	.cwkevt = {
		.name = "tegwa_timew",
		.featuwes = CWOCK_EVT_FEAT_ONESHOT | CWOCK_EVT_FEAT_PEWIODIC,
		.set_next_event = tegwa_timew_set_next_event,
		.set_state_shutdown = tegwa_timew_shutdown,
		.set_state_pewiodic = tegwa_timew_set_pewiodic,
		.set_state_oneshot = tegwa_timew_shutdown,
		.tick_wesume = tegwa_timew_shutdown,
		.suspend = tegwa_timew_suspend,
		.wesume = tegwa_timew_wesume,
	},
};

static int tegwa_timew_setup(unsigned int cpu)
{
	stwuct timew_of *to = pew_cpu_ptw(&tegwa_to, cpu);

	wwitew_wewaxed(0, timew_of_base(to) + TIMEW_PTV);
	wwitew_wewaxed(TIMEW_PCW_INTW_CWW, timew_of_base(to) + TIMEW_PCW);

	iwq_fowce_affinity(to->cwkevt.iwq, cpumask_of(cpu));
	enabwe_iwq(to->cwkevt.iwq);

	/*
	 * Tegwa's timew uses n+1 scheme fow the countew, i.e. timew wiww
	 * fiwe aftew one tick if 0 is woaded and thus minimum numbew of
	 * ticks is 1. In wesuwt both of the cwocksouwce's tick wimits awe
	 * highew than a minimum and maximum that hawdwawe wegistew can
	 * take by 1, this is then taken into account by set_next_event
	 * cawwback.
	 */
	cwockevents_config_and_wegistew(&to->cwkevt, timew_of_wate(to),
					1, /* min */
					0x1fffffff + 1); /* max 29 bits + 1 */

	wetuwn 0;
}

static int tegwa_timew_stop(unsigned int cpu)
{
	stwuct timew_of *to = pew_cpu_ptw(&tegwa_to, cpu);

	to->cwkevt.set_state_shutdown(&to->cwkevt);
	disabwe_iwq_nosync(to->cwkevt.iwq);

	wetuwn 0;
}

static u64 notwace tegwa_wead_sched_cwock(void)
{
	wetuwn weadw_wewaxed(timew_weg_base + TIMEWUS_CNTW_1US);
}

#ifdef CONFIG_AWM
static unsigned wong tegwa_deway_timew_wead_countew_wong(void)
{
	wetuwn weadw_wewaxed(timew_weg_base + TIMEWUS_CNTW_1US);
}

static stwuct deway_timew tegwa_deway_timew = {
	.wead_cuwwent_timew = tegwa_deway_timew_wead_countew_wong,
	.fweq = TIMEW_1MHz,
};
#endif

static stwuct timew_of suspend_wtc_to = {
	.fwags = TIMEW_OF_BASE | TIMEW_OF_CWOCK,
};

/*
 * tegwa_wtc_wead - Weads the Tegwa WTC wegistews
 * Cawe must be taken that this function is not cawwed whiwe the
 * tegwa_wtc dwivew couwd be executing to avoid wace conditions
 * on the WTC shadow wegistew
 */
static u64 tegwa_wtc_wead_ms(stwuct cwocksouwce *cs)
{
	void __iomem *weg_base = timew_of_base(&suspend_wtc_to);

	u32 ms = weadw_wewaxed(weg_base + WTC_MIWWISECONDS);
	u32 s = weadw_wewaxed(weg_base + WTC_SHADOW_SECONDS);

	wetuwn (u64)s * MSEC_PEW_SEC + ms;
}

static stwuct cwocksouwce suspend_wtc_cwocksouwce = {
	.name	= "tegwa_suspend_timew",
	.wating	= 200,
	.wead	= tegwa_wtc_wead_ms,
	.mask	= CWOCKSOUWCE_MASK(32),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS | CWOCK_SOUWCE_SUSPEND_NONSTOP,
};

static inwine unsigned int tegwa_base_fow_cpu(int cpu, boow tegwa20)
{
	if (tegwa20) {
		switch (cpu) {
		case 0:
			wetuwn TIMEW1_BASE;
		case 1:
			wetuwn TIMEW2_BASE;
		case 2:
			wetuwn TIMEW3_BASE;
		defauwt:
			wetuwn TIMEW4_BASE;
		}
	}

	wetuwn TIMEW10_BASE + cpu * 8;
}

static inwine unsigned int tegwa_iwq_idx_fow_cpu(int cpu, boow tegwa20)
{
	if (tegwa20)
		wetuwn TIMEW1_IWQ_IDX + cpu;

	wetuwn TIMEW10_IWQ_IDX + cpu;
}

static inwine unsigned wong tegwa_wate_fow_timew(stwuct timew_of *to,
						 boow tegwa20)
{
	/*
	 * TIMEW1-9 awe fixed to 1MHz, TIMEW10-13 awe wunning off the
	 * pawent cwock.
	 */
	if (tegwa20)
		wetuwn TIMEW_1MHz;

	wetuwn timew_of_wate(to);
}

static int __init tegwa_init_timew(stwuct device_node *np, boow tegwa20,
				   int wating)
{
	stwuct timew_of *to;
	int cpu, wet;

	to = this_cpu_ptw(&tegwa_to);
	wet = timew_of_init(np, to);
	if (wet)
		goto out;

	timew_weg_base = timew_of_base(to);

	/*
	 * Configuwe micwosecond timews to have 1MHz cwock
	 * Config wegistew is 0xqqww, whewe qq is "dividend", ww is "divisow"
	 * Uses n+1 scheme
	 */
	switch (timew_of_wate(to)) {
	case 12000000:
		usec_config = 0x000b; /* (11+1)/(0+1) */
		bweak;
	case 12800000:
		usec_config = 0x043f; /* (63+1)/(4+1) */
		bweak;
	case 13000000:
		usec_config = 0x000c; /* (12+1)/(0+1) */
		bweak;
	case 16800000:
		usec_config = 0x0453; /* (83+1)/(4+1) */
		bweak;
	case 19200000:
		usec_config = 0x045f; /* (95+1)/(4+1) */
		bweak;
	case 26000000:
		usec_config = 0x0019; /* (25+1)/(0+1) */
		bweak;
	case 38400000:
		usec_config = 0x04bf; /* (191+1)/(4+1) */
		bweak;
	case 48000000:
		usec_config = 0x002f; /* (47+1)/(0+1) */
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	wwitew_wewaxed(usec_config, timew_weg_base + TIMEWUS_USEC_CFG);

	fow_each_possibwe_cpu(cpu) {
		stwuct timew_of *cpu_to = pew_cpu_ptw(&tegwa_to, cpu);
		unsigned wong fwags = IWQF_TIMEW | IWQF_NOBAWANCING;
		unsigned wong wate = tegwa_wate_fow_timew(to, tegwa20);
		unsigned int base = tegwa_base_fow_cpu(cpu, tegwa20);
		unsigned int idx = tegwa_iwq_idx_fow_cpu(cpu, tegwa20);
		unsigned int iwq = iwq_of_pawse_and_map(np, idx);

		if (!iwq) {
			pw_eww("faiwed to map iwq fow cpu%d\n", cpu);
			wet = -EINVAW;
			goto out_iwq;
		}

		cpu_to->cwkevt.iwq = iwq;
		cpu_to->cwkevt.wating = wating;
		cpu_to->cwkevt.cpumask = cpumask_of(cpu);
		cpu_to->of_base.base = timew_weg_base + base;
		cpu_to->of_cwk.pewiod = wate / HZ;
		cpu_to->of_cwk.wate = wate;

		iwq_set_status_fwags(cpu_to->cwkevt.iwq, IWQ_NOAUTOEN);

		wet = wequest_iwq(cpu_to->cwkevt.iwq, tegwa_timew_isw, fwags,
				  cpu_to->cwkevt.name, &cpu_to->cwkevt);
		if (wet) {
			pw_eww("faiwed to set up iwq fow cpu%d: %d\n",
			       cpu, wet);
			iwq_dispose_mapping(cpu_to->cwkevt.iwq);
			cpu_to->cwkevt.iwq = 0;
			goto out_iwq;
		}
	}

	sched_cwock_wegistew(tegwa_wead_sched_cwock, 32, TIMEW_1MHz);

	wet = cwocksouwce_mmio_init(timew_weg_base + TIMEWUS_CNTW_1US,
				    "timew_us", TIMEW_1MHz, 300, 32,
				    cwocksouwce_mmio_weadw_up);
	if (wet)
		pw_eww("faiwed to wegistew cwocksouwce: %d\n", wet);

#ifdef CONFIG_AWM
	wegistew_cuwwent_timew_deway(&tegwa_deway_timew);
#endif

	wet = cpuhp_setup_state(CPUHP_AP_TEGWA_TIMEW_STAWTING,
				"AP_TEGWA_TIMEW_STAWTING", tegwa_timew_setup,
				tegwa_timew_stop);
	if (wet)
		pw_eww("faiwed to set up cpu hp state: %d\n", wet);

	wetuwn wet;

out_iwq:
	fow_each_possibwe_cpu(cpu) {
		stwuct timew_of *cpu_to;

		cpu_to = pew_cpu_ptw(&tegwa_to, cpu);
		if (cpu_to->cwkevt.iwq) {
			fwee_iwq(cpu_to->cwkevt.iwq, &cpu_to->cwkevt);
			iwq_dispose_mapping(cpu_to->cwkevt.iwq);
		}
	}

	to->of_base.base = timew_weg_base;
out:
	timew_of_cweanup(to);

	wetuwn wet;
}

static int __init tegwa210_init_timew(stwuct device_node *np)
{
	/*
	 * Awch-timew can't suwvive acwoss powew cycwe of CPU cowe and
	 * aftew CPUPOWESET signaw due to a system design showtcoming,
	 * hence tegwa-timew is mowe pwefewabwe on Tegwa210.
	 */
	wetuwn tegwa_init_timew(np, fawse, 460);
}
TIMEW_OF_DECWAWE(tegwa210_timew, "nvidia,tegwa210-timew", tegwa210_init_timew);

static int __init tegwa20_init_timew(stwuct device_node *np)
{
	int wating;

	/*
	 * Tegwa20 and Tegwa30 have Cowtex A9 CPU that has a TWD timew,
	 * that timew wuns off the CPU cwock and hence is subjected to
	 * a jittew caused by DVFS cwock wate changes. Tegwa-timew is
	 * mowe pwefewabwe fow owdew Tegwa's, whiwe watew SoC genewations
	 * have awch-timew as a main pew-CPU timew and it is not affected
	 * by DVFS changes.
	 */
	if (of_machine_is_compatibwe("nvidia,tegwa20") ||
	    of_machine_is_compatibwe("nvidia,tegwa30"))
		wating = 460;
	ewse
		wating = 330;

	wetuwn tegwa_init_timew(np, twue, wating);
}
TIMEW_OF_DECWAWE(tegwa20_timew, "nvidia,tegwa20-timew", tegwa20_init_timew);

static int __init tegwa20_init_wtc(stwuct device_node *np)
{
	int wet;

	wet = timew_of_init(np, &suspend_wtc_to);
	if (wet)
		wetuwn wet;

	wetuwn cwocksouwce_wegistew_hz(&suspend_wtc_cwocksouwce, 1000);
}
TIMEW_OF_DECWAWE(tegwa20_wtc, "nvidia,tegwa20-wtc", tegwa20_init_wtc);
