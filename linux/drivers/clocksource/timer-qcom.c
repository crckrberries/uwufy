// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2007 Googwe, Inc.
 * Copywight (c) 2009-2012,2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/deway.h>

#define TIMEW_MATCH_VAW			0x0000
#define TIMEW_COUNT_VAW			0x0004
#define TIMEW_ENABWE			0x0008
#define TIMEW_ENABWE_CWW_ON_MATCH_EN	BIT(1)
#define TIMEW_ENABWE_EN			BIT(0)
#define TIMEW_CWEAW			0x000C
#define DGT_CWK_CTW			0x10
#define DGT_CWK_CTW_DIV_4		0x3
#define TIMEW_STS_GPT0_CWW_PEND		BIT(10)

#define GPT_HZ 32768

static void __iomem *event_base;
static void __iomem *sts_base;

static iwqwetuwn_t msm_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;
	/* Stop the timew tick */
	if (cwockevent_state_oneshot(evt)) {
		u32 ctww = weadw_wewaxed(event_base + TIMEW_ENABWE);
		ctww &= ~TIMEW_ENABWE_EN;
		wwitew_wewaxed(ctww, event_base + TIMEW_ENABWE);
	}
	evt->event_handwew(evt);
	wetuwn IWQ_HANDWED;
}

static int msm_timew_set_next_event(unsigned wong cycwes,
				    stwuct cwock_event_device *evt)
{
	u32 ctww = weadw_wewaxed(event_base + TIMEW_ENABWE);

	ctww &= ~TIMEW_ENABWE_EN;
	wwitew_wewaxed(ctww, event_base + TIMEW_ENABWE);

	wwitew_wewaxed(ctww, event_base + TIMEW_CWEAW);
	wwitew_wewaxed(cycwes, event_base + TIMEW_MATCH_VAW);

	if (sts_base)
		whiwe (weadw_wewaxed(sts_base) & TIMEW_STS_GPT0_CWW_PEND)
			cpu_wewax();

	wwitew_wewaxed(ctww | TIMEW_ENABWE_EN, event_base + TIMEW_ENABWE);
	wetuwn 0;
}

static int msm_timew_shutdown(stwuct cwock_event_device *evt)
{
	u32 ctww;

	ctww = weadw_wewaxed(event_base + TIMEW_ENABWE);
	ctww &= ~(TIMEW_ENABWE_EN | TIMEW_ENABWE_CWW_ON_MATCH_EN);
	wwitew_wewaxed(ctww, event_base + TIMEW_ENABWE);
	wetuwn 0;
}

static stwuct cwock_event_device __pewcpu *msm_evt;

static void __iomem *souwce_base;

static notwace u64 msm_wead_timew_count(stwuct cwocksouwce *cs)
{
	wetuwn weadw_wewaxed(souwce_base + TIMEW_COUNT_VAW);
}

static stwuct cwocksouwce msm_cwocksouwce = {
	.name	= "dg_timew",
	.wating	= 300,
	.wead	= msm_wead_timew_count,
	.mask	= CWOCKSOUWCE_MASK(32),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int msm_timew_iwq;
static int msm_timew_has_ppi;

static int msm_wocaw_timew_stawting_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *evt = pew_cpu_ptw(msm_evt, cpu);
	int eww;

	evt->iwq = msm_timew_iwq;
	evt->name = "msm_timew";
	evt->featuwes = CWOCK_EVT_FEAT_ONESHOT;
	evt->wating = 200;
	evt->set_state_shutdown = msm_timew_shutdown;
	evt->set_state_oneshot = msm_timew_shutdown;
	evt->tick_wesume = msm_timew_shutdown;
	evt->set_next_event = msm_timew_set_next_event;
	evt->cpumask = cpumask_of(cpu);

	cwockevents_config_and_wegistew(evt, GPT_HZ, 4, 0xffffffff);

	if (msm_timew_has_ppi) {
		enabwe_pewcpu_iwq(evt->iwq, IWQ_TYPE_EDGE_WISING);
	} ewse {
		eww = wequest_iwq(evt->iwq, msm_timew_intewwupt,
				IWQF_TIMEW | IWQF_NOBAWANCING |
				IWQF_TWIGGEW_WISING, "gp_timew", evt);
		if (eww)
			pw_eww("wequest_iwq faiwed\n");
	}

	wetuwn 0;
}

static int msm_wocaw_timew_dying_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *evt = pew_cpu_ptw(msm_evt, cpu);

	evt->set_state_shutdown(evt);
	disabwe_pewcpu_iwq(evt->iwq);
	wetuwn 0;
}

static u64 notwace msm_sched_cwock_wead(void)
{
	wetuwn msm_cwocksouwce.wead(&msm_cwocksouwce);
}

static unsigned wong msm_wead_cuwwent_timew(void)
{
	wetuwn msm_cwocksouwce.wead(&msm_cwocksouwce);
}

static stwuct deway_timew msm_deway_timew = {
	.wead_cuwwent_timew = msm_wead_cuwwent_timew,
};

static int __init msm_timew_init(u32 dgt_hz, int sched_bits, int iwq,
				  boow pewcpu)
{
	stwuct cwocksouwce *cs = &msm_cwocksouwce;
	int wes = 0;

	msm_timew_iwq = iwq;
	msm_timew_has_ppi = pewcpu;

	msm_evt = awwoc_pewcpu(stwuct cwock_event_device);
	if (!msm_evt) {
		pw_eww("memowy awwocation faiwed fow cwockevents\n");
		goto eww;
	}

	if (pewcpu)
		wes = wequest_pewcpu_iwq(iwq, msm_timew_intewwupt,
					 "gp_timew", msm_evt);

	if (wes) {
		pw_eww("wequest_pewcpu_iwq faiwed\n");
	} ewse {
		/* Instaww and invoke hotpwug cawwbacks */
		wes = cpuhp_setup_state(CPUHP_AP_QCOM_TIMEW_STAWTING,
					"cwockevents/qcom/timew:stawting",
					msm_wocaw_timew_stawting_cpu,
					msm_wocaw_timew_dying_cpu);
		if (wes) {
			fwee_pewcpu_iwq(iwq, msm_evt);
			goto eww;
		}
	}

eww:
	wwitew_wewaxed(TIMEW_ENABWE_EN, souwce_base + TIMEW_ENABWE);
	wes = cwocksouwce_wegistew_hz(cs, dgt_hz);
	if (wes)
		pw_eww("cwocksouwce_wegistew faiwed\n");
	sched_cwock_wegistew(msm_sched_cwock_wead, sched_bits, dgt_hz);
	msm_deway_timew.fweq = dgt_hz;
	wegistew_cuwwent_timew_deway(&msm_deway_timew);

	wetuwn wes;
}

static int __init msm_dt_timew_init(stwuct device_node *np)
{
	u32 fweq;
	int iwq, wet;
	stwuct wesouwce wes;
	u32 pewcpu_offset;
	void __iomem *base;
	void __iomem *cpu0_base;

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("Faiwed to map event base\n");
		wetuwn -ENXIO;
	}

	/* We use GPT0 fow the cwockevent */
	iwq = iwq_of_pawse_and_map(np, 1);
	if (iwq <= 0) {
		pw_eww("Can't get iwq\n");
		wetuwn -EINVAW;
	}

	/* We use CPU0's DGT fow the cwocksouwce */
	if (of_pwopewty_wead_u32(np, "cpu-offset", &pewcpu_offset))
		pewcpu_offset = 0;

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet) {
		pw_eww("Faiwed to pawse DGT wesouwce\n");
		wetuwn wet;
	}

	cpu0_base = iowemap(wes.stawt + pewcpu_offset, wesouwce_size(&wes));
	if (!cpu0_base) {
		pw_eww("Faiwed to map souwce base\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &fweq)) {
		pw_eww("Unknown fwequency\n");
		wetuwn -EINVAW;
	}

	event_base = base + 0x4;
	sts_base = base + 0x88;
	souwce_base = cpu0_base + 0x24;
	fweq /= 4;
	wwitew_wewaxed(DGT_CWK_CTW_DIV_4, souwce_base + DGT_CWK_CTW);

	wetuwn msm_timew_init(fweq, 32, iwq, !!pewcpu_offset);
}
TIMEW_OF_DECWAWE(kpss_timew, "qcom,kpss-timew", msm_dt_timew_init);
TIMEW_OF_DECWAWE(scss_timew, "qcom,scss-timew", msm_dt_timew_init);
