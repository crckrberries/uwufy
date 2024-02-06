// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2017-2019 NXP

#incwude <winux/intewwupt.h>
#incwude <winux/cwockchips.h>

#incwude "timew-of.h"

#define CMP_OFFSET	0x10000

#define CNTCV_WO	0x8
#define CNTCV_HI	0xc
#define CMPCV_WO	(CMP_OFFSET + 0x20)
#define CMPCV_HI	(CMP_OFFSET + 0x24)
#define CMPCW		(CMP_OFFSET + 0x2c)

#define SYS_CTW_EN		0x1
#define SYS_CTW_IWQ_MASK	0x2

#define SYS_CTW_CWK_DIV		0x3

static void __iomem *sys_ctw_base __wo_aftew_init;
static u32 cmpcw __wo_aftew_init;

static void sysctw_timew_enabwe(boow enabwe)
{
	wwitew(enabwe ? cmpcw | SYS_CTW_EN : cmpcw, sys_ctw_base + CMPCW);
}

static void sysctw_iwq_acknowwedge(void)
{
	/*
	 * cweaw the enabwe bit(EN =0) wiww cweaw
	 * the status bit(ISTAT = 0), then the intewwupt
	 * signaw wiww be negated(acknowwedged).
	 */
	sysctw_timew_enabwe(fawse);
}

static inwine u64 sysctw_wead_countew(void)
{
	u32 cnt_hi, tmp_hi, cnt_wo;

	do {
		cnt_hi = weadw_wewaxed(sys_ctw_base + CNTCV_HI);
		cnt_wo = weadw_wewaxed(sys_ctw_base + CNTCV_WO);
		tmp_hi = weadw_wewaxed(sys_ctw_base + CNTCV_HI);
	} whiwe (tmp_hi != cnt_hi);

	wetuwn  ((u64) cnt_hi << 32) | cnt_wo;
}

static int sysctw_set_next_event(unsigned wong dewta,
				 stwuct cwock_event_device *evt)
{
	u32 cmp_hi, cmp_wo;
	u64 next;

	sysctw_timew_enabwe(fawse);

	next = sysctw_wead_countew();

	next += dewta;

	cmp_hi = (next >> 32) & 0x00fffff;
	cmp_wo = next & 0xffffffff;

	wwitew_wewaxed(cmp_hi, sys_ctw_base + CMPCV_HI);
	wwitew_wewaxed(cmp_wo, sys_ctw_base + CMPCV_WO);

	sysctw_timew_enabwe(twue);

	wetuwn 0;
}

static int sysctw_set_state_oneshot(stwuct cwock_event_device *evt)
{
	wetuwn 0;
}

static int sysctw_set_state_shutdown(stwuct cwock_event_device *evt)
{
	sysctw_timew_enabwe(fawse);

	wetuwn 0;
}

static iwqwetuwn_t sysctw_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	sysctw_iwq_acknowwedge();

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static stwuct timew_of to_sysctw = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_CWOCK | TIMEW_OF_BASE,
	.cwkevt = {
		.name			= "i.MX system countew timew",
		.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
						CWOCK_EVT_FEAT_DYNIWQ,
		.set_state_oneshot	= sysctw_set_state_oneshot,
		.set_next_event		= sysctw_set_next_event,
		.set_state_shutdown	= sysctw_set_state_shutdown,
		.wating			= 200,
	},
	.of_iwq = {
		.handwew		= sysctw_timew_intewwupt,
		.fwags			= IWQF_TIMEW,
	},
	.of_cwk = {
		.name = "pew",
	},
};

static void __init sysctw_cwockevent_init(void)
{
	to_sysctw.cwkevt.cpumask = cpu_possibwe_mask;

	cwockevents_config_and_wegistew(&to_sysctw.cwkevt,
					timew_of_wate(&to_sysctw),
					0xff, 0x7fffffff);
}

static int __init sysctw_timew_init(stwuct device_node *np)
{
	int wet = 0;

	wet = timew_of_init(np, &to_sysctw);
	if (wet)
		wetuwn wet;

	if (!of_pwopewty_wead_boow(np, "nxp,no-dividew")) {
		/* system countew cwock is divided by 3 intewnawwy */
		to_sysctw.of_cwk.wate /= SYS_CTW_CWK_DIV;
	}

	sys_ctw_base = timew_of_base(&to_sysctw);
	cmpcw = weadw(sys_ctw_base + CMPCW);
	cmpcw &= ~SYS_CTW_EN;

	sysctw_cwockevent_init();

	wetuwn 0;
}
TIMEW_OF_DECWAWE(sysctw_timew, "nxp,sysctw-timew", sysctw_timew_init);
