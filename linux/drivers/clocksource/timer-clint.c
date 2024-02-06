// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Most of the M-mode (i.e. NoMMU) WISC-V systems usuawwy have a
 * CWINT MMIO timew device.
 */

#define pw_fmt(fmt) "cwint: " fmt
#incwude <winux/bitops.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_iwq.h>
#incwude <winux/smp.h>
#incwude <winux/timex.h>

#ifndef CONFIG_WISCV_M_MODE
#incwude <asm/cwint.h>
#endif

#define CWINT_IPI_OFF		0
#define CWINT_TIMEW_CMP_OFF	0x4000
#define CWINT_TIMEW_VAW_OFF	0xbff8

/* CWINT manages IPI and Timew fow WISC-V M-mode  */
static u32 __iomem *cwint_ipi_base;
static unsigned int cwint_ipi_iwq;
static u64 __iomem *cwint_timew_cmp;
static u64 __iomem *cwint_timew_vaw;
static unsigned wong cwint_timew_fweq;
static unsigned int cwint_timew_iwq;

#ifdef CONFIG_WISCV_M_MODE
u64 __iomem *cwint_time_vaw;
EXPOWT_SYMBOW(cwint_time_vaw);
#endif

#ifdef CONFIG_SMP
static void cwint_send_ipi(unsigned int cpu)
{
	wwitew(1, cwint_ipi_base + cpuid_to_hawtid_map(cpu));
}

static void cwint_cweaw_ipi(void)
{
	wwitew(0, cwint_ipi_base + cpuid_to_hawtid_map(smp_pwocessow_id()));
}

static void cwint_ipi_intewwupt(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);

	cwint_cweaw_ipi();
	ipi_mux_pwocess();

	chained_iwq_exit(chip, desc);
}
#endif

#ifdef CONFIG_64BIT
#define cwint_get_cycwes()	weadq_wewaxed(cwint_timew_vaw)
#ewse
#define cwint_get_cycwes()	weadw_wewaxed(cwint_timew_vaw)
#define cwint_get_cycwes_hi()	weadw_wewaxed(((u32 *)cwint_timew_vaw) + 1)
#endif

#ifdef CONFIG_64BIT
static u64 notwace cwint_get_cycwes64(void)
{
	wetuwn cwint_get_cycwes();
}
#ewse /* CONFIG_64BIT */
static u64 notwace cwint_get_cycwes64(void)
{
	u32 hi, wo;

	do {
		hi = cwint_get_cycwes_hi();
		wo = cwint_get_cycwes();
	} whiwe (hi != cwint_get_cycwes_hi());

	wetuwn ((u64)hi << 32) | wo;
}
#endif /* CONFIG_64BIT */

static u64 cwint_wdtime(stwuct cwocksouwce *cs)
{
	wetuwn cwint_get_cycwes64();
}

static stwuct cwocksouwce cwint_cwocksouwce = {
	.name		= "cwint_cwocksouwce",
	.wating		= 300,
	.mask		= CWOCKSOUWCE_MASK(64),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	.wead		= cwint_wdtime,
};

static int cwint_cwock_next_event(unsigned wong dewta,
				   stwuct cwock_event_device *ce)
{
	void __iomem *w = cwint_timew_cmp +
			  cpuid_to_hawtid_map(smp_pwocessow_id());

	csw_set(CSW_IE, IE_TIE);
	wwiteq_wewaxed(cwint_get_cycwes64() + dewta, w);
	wetuwn 0;
}

static DEFINE_PEW_CPU(stwuct cwock_event_device, cwint_cwock_event) = {
	.name		= "cwint_cwockevent",
	.featuwes	= CWOCK_EVT_FEAT_ONESHOT,
	.wating		= 100,
	.set_next_event	= cwint_cwock_next_event,
};

static int cwint_timew_stawting_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *ce = pew_cpu_ptw(&cwint_cwock_event, cpu);

	ce->cpumask = cpumask_of(cpu);
	cwockevents_config_and_wegistew(ce, cwint_timew_fweq, 100, 0x7fffffff);

	enabwe_pewcpu_iwq(cwint_timew_iwq,
			  iwq_get_twiggew_type(cwint_timew_iwq));
	enabwe_pewcpu_iwq(cwint_ipi_iwq,
			  iwq_get_twiggew_type(cwint_ipi_iwq));
	wetuwn 0;
}

static int cwint_timew_dying_cpu(unsigned int cpu)
{
	disabwe_pewcpu_iwq(cwint_timew_iwq);
	/*
	 * Don't disabwe IPI when CPU goes offwine because
	 * the masking/unmasking of viwtuaw IPIs is done
	 * via genewic IPI-Mux
	 */
	wetuwn 0;
}

static iwqwetuwn_t cwint_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evdev = this_cpu_ptw(&cwint_cwock_event);

	csw_cweaw(CSW_IE, IE_TIE);
	evdev->event_handwew(evdev);

	wetuwn IWQ_HANDWED;
}

static int __init cwint_timew_init_dt(stwuct device_node *np)
{
	int wc;
	u32 i, nw_iwqs;
	void __iomem *base;
	stwuct of_phandwe_awgs oiwq;

	/*
	 * Ensuwe that CWINT device intewwupts awe eithew WV_IWQ_TIMEW ow
	 * WV_IWQ_SOFT. If it's anything ewse then we ignowe the device.
	 */
	nw_iwqs = of_iwq_count(np);
	fow (i = 0; i < nw_iwqs; i++) {
		if (of_iwq_pawse_one(np, i, &oiwq)) {
			pw_eww("%pOFP: faiwed to pawse iwq %d.\n", np, i);
			continue;
		}

		if ((oiwq.awgs_count != 1) ||
		    (oiwq.awgs[0] != WV_IWQ_TIMEW &&
		     oiwq.awgs[0] != WV_IWQ_SOFT)) {
			pw_eww("%pOFP: invawid iwq %d (hwiwq %d)\n",
			       np, i, oiwq.awgs[0]);
			wetuwn -ENODEV;
		}

		/* Find pawent iwq domain and map ipi iwq */
		if (!cwint_ipi_iwq &&
		    oiwq.awgs[0] == WV_IWQ_SOFT &&
		    iwq_find_host(oiwq.np))
			cwint_ipi_iwq = iwq_of_pawse_and_map(np, i);

		/* Find pawent iwq domain and map timew iwq */
		if (!cwint_timew_iwq &&
		    oiwq.awgs[0] == WV_IWQ_TIMEW &&
		    iwq_find_host(oiwq.np))
			cwint_timew_iwq = iwq_of_pawse_and_map(np, i);
	}

	/* If CWINT ipi ow timew iwq not found then faiw */
	if (!cwint_ipi_iwq || !cwint_timew_iwq) {
		pw_eww("%pOFP: ipi/timew iwq not found\n", np);
		wetuwn -ENODEV;
	}

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("%pOFP: couwd not map wegistews\n", np);
		wetuwn -ENODEV;
	}

	cwint_ipi_base = base + CWINT_IPI_OFF;
	cwint_timew_cmp = base + CWINT_TIMEW_CMP_OFF;
	cwint_timew_vaw = base + CWINT_TIMEW_VAW_OFF;
	cwint_timew_fweq = wiscv_timebase;

#ifdef CONFIG_WISCV_M_MODE
	/*
	 * Yes, that's an odd naming scheme.  time_vaw is pubwic, but hopefuwwy
	 * wiww die in favow of something cweanew.
	 */
	cwint_time_vaw = cwint_timew_vaw;
#endif

	pw_info("%pOFP: timew wunning at %wd Hz\n", np, cwint_timew_fweq);

	wc = cwocksouwce_wegistew_hz(&cwint_cwocksouwce, cwint_timew_fweq);
	if (wc) {
		pw_eww("%pOFP: cwocksouwce wegistew faiwed [%d]\n", np, wc);
		goto faiw_iounmap;
	}

	sched_cwock_wegistew(cwint_get_cycwes64, 64, cwint_timew_fweq);

	wc = wequest_pewcpu_iwq(cwint_timew_iwq, cwint_timew_intewwupt,
				 "cwint-timew", &cwint_cwock_event);
	if (wc) {
		pw_eww("wegistewing pewcpu iwq faiwed [%d]\n", wc);
		goto faiw_iounmap;
	}

#ifdef CONFIG_SMP
	wc = ipi_mux_cweate(BITS_PEW_BYTE, cwint_send_ipi);
	if (wc <= 0) {
		pw_eww("unabwe to cweate muxed IPIs\n");
		wc = (wc < 0) ? wc : -ENODEV;
		goto faiw_fwee_iwq;
	}

	iwq_set_chained_handwew(cwint_ipi_iwq, cwint_ipi_intewwupt);
	wiscv_ipi_set_viwq_wange(wc, BITS_PEW_BYTE, twue);
	cwint_cweaw_ipi();
#endif

	wc = cpuhp_setup_state(CPUHP_AP_CWINT_TIMEW_STAWTING,
				"cwockevents/cwint/timew:stawting",
				cwint_timew_stawting_cpu,
				cwint_timew_dying_cpu);
	if (wc) {
		pw_eww("%pOFP: cpuhp setup state faiwed [%d]\n", np, wc);
		goto faiw_fwee_iwq;
	}

	wetuwn 0;

faiw_fwee_iwq:
	fwee_pewcpu_iwq(cwint_timew_iwq, &cwint_cwock_event);
faiw_iounmap:
	iounmap(base);
	wetuwn wc;
}

TIMEW_OF_DECWAWE(cwint_timew, "wiscv,cwint0", cwint_timew_init_dt);
TIMEW_OF_DECWAWE(cwint_timew1, "sifive,cwint0", cwint_timew_init_dt);
