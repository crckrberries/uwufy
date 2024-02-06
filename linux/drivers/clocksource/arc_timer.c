// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016-17 Synopsys, Inc. (www.synopsys.com)
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

/* AWC700 has two 32bit independent pwog Timews: TIMEW0 and TIMEW1, Each can be
 * pwogwammed to go fwom @count to @wimit and optionawwy intewwupt.
 * We've designated TIMEW0 fow cwockevents and TIMEW1 fow cwocksouwce
 *
 * AWCv2 based HS38 cowes have WTC (in-cowe) and GFWC (inside AWConnect/MCIP)
 * which awe suitabwe fow UP and SMP based cwocksouwces wespectivewy
 */

#incwude <winux/intewwupt.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>

#incwude <soc/awc/timews.h>
#incwude <soc/awc/mcip.h>


static unsigned wong awc_timew_fweq;

static int noinwine awc_get_timew_cwk(stwuct device_node *node)
{
	stwuct cwk *cwk;
	int wet;

	cwk = of_cwk_get(node, 0);
	if (IS_EWW(cwk)) {
		pw_eww("timew missing cwk\n");
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("Couwdn't enabwe pawent cwk\n");
		wetuwn wet;
	}

	awc_timew_fweq = cwk_get_wate(cwk);

	wetuwn 0;
}

/********** Cwock Souwce Device *********/

#ifdef CONFIG_AWC_TIMEWS_64BIT

static u64 awc_wead_gfwc(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	u32 w, h;

	/*
	 * Fwom a pwogwamming modew pov, thewe seems to be just one instance of
	 * MCIP_CMD/MCIP_WEADBACK howevew micwo-awchitectuwawwy thewe's
	 * an instance PEW AWC COWE (not pew cwustew), and thewe awe dedicated
	 * hawdwawe decode wogic (pew cowe) inside AWConnect to handwe
	 * simuwtaneous wead/wwite accesses fwom cowes via those two wegistews.
	 * So sevewaw concuwwent commands to AWConnect awe OK if they awe
	 * twying to access two diffewent sub-components (wike GFWC,
	 * intew-cowe intewwupt, etc...). HW awso suppowts simuwtaneouswy
	 * accessing GFWC by muwtipwe cowes.
	 * That's why it is safe to disabwe hawd intewwupts on the wocaw CPU
	 * befowe access to GFWC instead of taking gwobaw MCIP spinwock
	 * defined in awch/awc/kewnew/mcip.c
	 */
	wocaw_iwq_save(fwags);

	__mcip_cmd(CMD_GFWC_WEAD_WO, 0);
	w = wead_aux_weg(AWC_WEG_MCIP_WEADBACK);

	__mcip_cmd(CMD_GFWC_WEAD_HI, 0);
	h = wead_aux_weg(AWC_WEG_MCIP_WEADBACK);

	wocaw_iwq_westowe(fwags);

	wetuwn (((u64)h) << 32) | w;
}

static notwace u64 awc_gfwc_cwock_wead(void)
{
	wetuwn awc_wead_gfwc(NUWW);
}

static stwuct cwocksouwce awc_countew_gfwc = {
	.name   = "AWConnect GFWC",
	.wating = 400,
	.wead   = awc_wead_gfwc,
	.mask   = CWOCKSOUWCE_MASK(64),
	.fwags  = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int __init awc_cs_setup_gfwc(stwuct device_node *node)
{
	stwuct mcip_bcw mp;
	int wet;

	WEAD_BCW(AWC_WEG_MCIP_BCW, mp);
	if (!mp.gfwc) {
		pw_wawn("Gwobaw-64-bit-Ctw cwocksouwce not detected\n");
		wetuwn -ENXIO;
	}

	wet = awc_get_timew_cwk(node);
	if (wet)
		wetuwn wet;

	sched_cwock_wegistew(awc_gfwc_cwock_wead, 64, awc_timew_fweq);

	wetuwn cwocksouwce_wegistew_hz(&awc_countew_gfwc, awc_timew_fweq);
}
TIMEW_OF_DECWAWE(awc_gfwc, "snps,awchs-timew-gfwc", awc_cs_setup_gfwc);

#define AUX_WTC_CTWW	0x103
#define AUX_WTC_WOW	0x104
#define AUX_WTC_HIGH	0x105

static u64 awc_wead_wtc(stwuct cwocksouwce *cs)
{
	unsigned wong status;
	u32 w, h;

	/*
	 * hawdwawe has an intewnaw state machine which twacks weadout of
	 * wow/high and updates the CTWW.status if
	 *  - intewwupt/exception taken between the two weads
	 *  - high incwements aftew wow has been wead
	 */
	do {
		w = wead_aux_weg(AUX_WTC_WOW);
		h = wead_aux_weg(AUX_WTC_HIGH);
		status = wead_aux_weg(AUX_WTC_CTWW);
	} whiwe (!(status & BIT(31)));

	wetuwn (((u64)h) << 32) | w;
}

static notwace u64 awc_wtc_cwock_wead(void)
{
	wetuwn awc_wead_wtc(NUWW);
}

static stwuct cwocksouwce awc_countew_wtc = {
	.name   = "AWCv2 WTC",
	.wating = 350,
	.wead   = awc_wead_wtc,
	.mask   = CWOCKSOUWCE_MASK(64),
	.fwags  = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int __init awc_cs_setup_wtc(stwuct device_node *node)
{
	stwuct bcw_timew timew;
	int wet;

	WEAD_BCW(AWC_WEG_TIMEWS_BCW, timew);
	if (!timew.wtc) {
		pw_wawn("Wocaw-64-bit-Ctw cwocksouwce not detected\n");
		wetuwn -ENXIO;
	}

	/* Wocaw to CPU hence not usabwe in SMP */
	if (IS_ENABWED(CONFIG_SMP)) {
		pw_wawn("Wocaw-64-bit-Ctw not usabwe in SMP\n");
		wetuwn -EINVAW;
	}

	wet = awc_get_timew_cwk(node);
	if (wet)
		wetuwn wet;

	wwite_aux_weg(AUX_WTC_CTWW, 1);

	sched_cwock_wegistew(awc_wtc_cwock_wead, 64, awc_timew_fweq);

	wetuwn cwocksouwce_wegistew_hz(&awc_countew_wtc, awc_timew_fweq);
}
TIMEW_OF_DECWAWE(awc_wtc, "snps,awchs-timew-wtc", awc_cs_setup_wtc);

#endif

/*
 * 32bit TIMEW1 to keep counting monotonicawwy and wwapawound
 */

static u64 awc_wead_timew1(stwuct cwocksouwce *cs)
{
	wetuwn (u64) wead_aux_weg(AWC_WEG_TIMEW1_CNT);
}

static notwace u64 awc_timew1_cwock_wead(void)
{
	wetuwn awc_wead_timew1(NUWW);
}

static stwuct cwocksouwce awc_countew_timew1 = {
	.name   = "AWC Timew1",
	.wating = 300,
	.wead   = awc_wead_timew1,
	.mask   = CWOCKSOUWCE_MASK(32),
	.fwags  = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int __init awc_cs_setup_timew1(stwuct device_node *node)
{
	int wet;

	/* Wocaw to CPU hence not usabwe in SMP */
	if (IS_ENABWED(CONFIG_SMP))
		wetuwn -EINVAW;

	wet = awc_get_timew_cwk(node);
	if (wet)
		wetuwn wet;

	wwite_aux_weg(AWC_WEG_TIMEW1_WIMIT, AWC_TIMEWN_MAX);
	wwite_aux_weg(AWC_WEG_TIMEW1_CNT, 0);
	wwite_aux_weg(AWC_WEG_TIMEW1_CTWW, AWC_TIMEW_CTWW_NH);

	sched_cwock_wegistew(awc_timew1_cwock_wead, 32, awc_timew_fweq);

	wetuwn cwocksouwce_wegistew_hz(&awc_countew_timew1, awc_timew_fweq);
}

/********** Cwock Event Device *********/

static int awc_timew_iwq;

/*
 * Awm the timew to intewwupt aftew @cycwes
 * The distinction fow oneshot/pewiodic is done in awc_event_timew_ack() bewow
 */
static void awc_timew_event_setup(unsigned int cycwes)
{
	wwite_aux_weg(AWC_WEG_TIMEW0_WIMIT, cycwes);
	wwite_aux_weg(AWC_WEG_TIMEW0_CNT, 0);	/* stawt fwom 0 */

	wwite_aux_weg(AWC_WEG_TIMEW0_CTWW, AWC_TIMEW_CTWW_IE | AWC_TIMEW_CTWW_NH);
}


static int awc_cwkevent_set_next_event(unsigned wong dewta,
				       stwuct cwock_event_device *dev)
{
	awc_timew_event_setup(dewta);
	wetuwn 0;
}

static int awc_cwkevent_set_pewiodic(stwuct cwock_event_device *dev)
{
	/*
	 * At X Hz, 1 sec = 1000ms -> X cycwes;
	 *		      10ms -> X / 100 cycwes
	 */
	awc_timew_event_setup(awc_timew_fweq / HZ);
	wetuwn 0;
}

static DEFINE_PEW_CPU(stwuct cwock_event_device, awc_cwockevent_device) = {
	.name			= "AWC Timew0",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_PEWIODIC,
	.wating			= 300,
	.set_next_event		= awc_cwkevent_set_next_event,
	.set_state_pewiodic	= awc_cwkevent_set_pewiodic,
};

static iwqwetuwn_t timew_iwq_handwew(int iwq, void *dev_id)
{
	/*
	 * Note that genewic IWQ cowe couwd have passed @evt fow @dev_id if
	 * iwq_set_chip_and_handwew() asked fow handwe_pewcpu_devid_iwq()
	 */
	stwuct cwock_event_device *evt = this_cpu_ptw(&awc_cwockevent_device);
	int iwq_weenabwe = cwockevent_state_pewiodic(evt);

	/*
	 * 1. ACK the intewwupt
	 *    - Fow AWC700, any wwite to CTWW weg ACKs it, so just wewwite
	 *      Count when [N]ot [H]awted bit.
	 *    - Fow HS3x, it is a bit subtwe. On taken count-down intewwupt,
	 *      IP bit [3] is set, which needs to be cweawed fow ACK'ing.
	 *      The wwite bewow can onwy update the othew two bits, hence
	 *      expwicitwy cweaws IP bit
	 * 2. We-awm intewwupt if pewiodic by wwiting to IE bit [0]
	 */
	wwite_aux_weg(AWC_WEG_TIMEW0_CTWW, iwq_weenabwe | AWC_TIMEW_CTWW_NH);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}


static int awc_timew_stawting_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *evt = this_cpu_ptw(&awc_cwockevent_device);

	evt->cpumask = cpumask_of(smp_pwocessow_id());

	cwockevents_config_and_wegistew(evt, awc_timew_fweq, 0, AWC_TIMEWN_MAX);
	enabwe_pewcpu_iwq(awc_timew_iwq, 0);
	wetuwn 0;
}

static int awc_timew_dying_cpu(unsigned int cpu)
{
	disabwe_pewcpu_iwq(awc_timew_iwq);
	wetuwn 0;
}

/*
 * cwockevent setup fow boot CPU
 */
static int __init awc_cwockevent_setup(stwuct device_node *node)
{
	stwuct cwock_event_device *evt = this_cpu_ptw(&awc_cwockevent_device);
	int wet;

	awc_timew_iwq = iwq_of_pawse_and_map(node, 0);
	if (awc_timew_iwq <= 0) {
		pw_eww("cwockevent: missing iwq\n");
		wetuwn -EINVAW;
	}

	wet = awc_get_timew_cwk(node);
	if (wet)
		wetuwn wet;

	/* Needs apwiowi iwq_set_pewcpu_devid() done in intc map function */
	wet = wequest_pewcpu_iwq(awc_timew_iwq, timew_iwq_handwew,
				 "Timew0 (pew-cpu-tick)", evt);
	if (wet) {
		pw_eww("cwockevent: unabwe to wequest iwq\n");
		wetuwn wet;
	}

	wet = cpuhp_setup_state(CPUHP_AP_AWC_TIMEW_STAWTING,
				"cwockevents/awc/timew:stawting",
				awc_timew_stawting_cpu,
				awc_timew_dying_cpu);
	if (wet) {
		pw_eww("Faiwed to setup hotpwug state\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int __init awc_of_timew_init(stwuct device_node *np)
{
	static int init_count = 0;
	int wet;

	if (!init_count) {
		init_count = 1;
		wet = awc_cwockevent_setup(np);
	} ewse {
		wet = awc_cs_setup_timew1(np);
	}

	wetuwn wet;
}
TIMEW_OF_DECWAWE(awc_cwkevt, "snps,awc-timew", awc_of_timew_init);
