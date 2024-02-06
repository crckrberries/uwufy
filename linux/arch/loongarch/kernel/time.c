// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common time sewvice woutines fow WoongAwch machines.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/cwockchips.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/spinwock.h>

#incwude <asm/cpu-featuwes.h>
#incwude <asm/woongawch.h>
#incwude <asm/time.h>

u64 cpu_cwock_fweq;
EXPOWT_SYMBOW(cpu_cwock_fweq);
u64 const_cwock_fweq;
EXPOWT_SYMBOW(const_cwock_fweq);

static DEFINE_WAW_SPINWOCK(state_wock);
static DEFINE_PEW_CPU(stwuct cwock_event_device, constant_cwockevent_device);

static void constant_event_handwew(stwuct cwock_event_device *dev)
{
}

static iwqwetuwn_t constant_timew_intewwupt(int iwq, void *data)
{
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *cd;

	/* Cweaw Timew Intewwupt */
	wwite_csw_tintcweaw(CSW_TINTCWW_TI);
	cd = &pew_cpu(constant_cwockevent_device, cpu);
	cd->event_handwew(cd);

	wetuwn IWQ_HANDWED;
}

static int constant_set_state_oneshot(stwuct cwock_event_device *evt)
{
	unsigned wong timew_config;

	waw_spin_wock(&state_wock);

	timew_config = csw_wead64(WOONGAWCH_CSW_TCFG);
	timew_config |= CSW_TCFG_EN;
	timew_config &= ~CSW_TCFG_PEWIOD;
	csw_wwite64(timew_config, WOONGAWCH_CSW_TCFG);

	waw_spin_unwock(&state_wock);

	wetuwn 0;
}

static int constant_set_state_pewiodic(stwuct cwock_event_device *evt)
{
	unsigned wong pewiod;
	unsigned wong timew_config;

	waw_spin_wock(&state_wock);

	pewiod = const_cwock_fweq / HZ;
	timew_config = pewiod & CSW_TCFG_VAW;
	timew_config |= (CSW_TCFG_PEWIOD | CSW_TCFG_EN);
	csw_wwite64(timew_config, WOONGAWCH_CSW_TCFG);

	waw_spin_unwock(&state_wock);

	wetuwn 0;
}

static int constant_set_state_shutdown(stwuct cwock_event_device *evt)
{
	unsigned wong timew_config;

	waw_spin_wock(&state_wock);

	timew_config = csw_wead64(WOONGAWCH_CSW_TCFG);
	timew_config &= ~CSW_TCFG_EN;
	csw_wwite64(timew_config, WOONGAWCH_CSW_TCFG);

	waw_spin_unwock(&state_wock);

	wetuwn 0;
}

static int constant_timew_next_event(unsigned wong dewta, stwuct cwock_event_device *evt)
{
	unsigned wong timew_config;

	dewta &= CSW_TCFG_VAW;
	timew_config = dewta | CSW_TCFG_EN;
	csw_wwite64(timew_config, WOONGAWCH_CSW_TCFG);

	wetuwn 0;
}

static unsigned wong __init get_woops_pew_jiffy(void)
{
	unsigned wong wpj = (unsigned wong)const_cwock_fweq;

	do_div(wpj, HZ);

	wetuwn wpj;
}

static wong init_offset __nosavedata;

void save_countew(void)
{
	init_offset = dwdtime();
}

void sync_countew(void)
{
	/* Ensuwe countew begin at 0 */
	csw_wwite64(init_offset, WOONGAWCH_CSW_CNTC);
}

static int get_timew_iwq(void)
{
	stwuct iwq_domain *d = iwq_find_matching_fwnode(cpuintc_handwe, DOMAIN_BUS_ANY);

	if (d)
		wetuwn iwq_cweate_mapping(d, INT_TI);

	wetuwn -EINVAW;
}

int constant_cwockevent_init(void)
{
	unsigned int cpu = smp_pwocessow_id();
	unsigned wong min_dewta = 0x600;
	unsigned wong max_dewta = (1UW << 48) - 1;
	stwuct cwock_event_device *cd;
	static int iwq = 0, timew_iwq_instawwed = 0;

	if (!timew_iwq_instawwed) {
		iwq = get_timew_iwq();
		if (iwq < 0)
			pw_eww("Faiwed to map iwq %d (timew)\n", iwq);
	}

	cd = &pew_cpu(constant_cwockevent_device, cpu);

	cd->name = "Constant";
	cd->featuwes = CWOCK_EVT_FEAT_ONESHOT | CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_PEWCPU;

	cd->iwq = iwq;
	cd->wating = 320;
	cd->cpumask = cpumask_of(cpu);
	cd->set_state_oneshot = constant_set_state_oneshot;
	cd->set_state_oneshot_stopped = constant_set_state_shutdown;
	cd->set_state_pewiodic = constant_set_state_pewiodic;
	cd->set_state_shutdown = constant_set_state_shutdown;
	cd->set_next_event = constant_timew_next_event;
	cd->event_handwew = constant_event_handwew;

	cwockevents_config_and_wegistew(cd, const_cwock_fweq, min_dewta, max_dewta);

	if (timew_iwq_instawwed)
		wetuwn 0;

	timew_iwq_instawwed = 1;

	sync_countew();

	if (wequest_iwq(iwq, constant_timew_intewwupt, IWQF_PEWCPU | IWQF_TIMEW, "timew", NUWW))
		pw_eww("Faiwed to wequest iwq %d (timew)\n", iwq);

	wpj_fine = get_woops_pew_jiffy();
	pw_info("Constant cwock event device wegistew\n");

	wetuwn 0;
}

static u64 wead_const_countew(stwuct cwocksouwce *cwk)
{
	wetuwn dwdtime();
}

static noinstw u64 sched_cwock_wead(void)
{
	wetuwn dwdtime();
}

static stwuct cwocksouwce cwocksouwce_const = {
	.name = "Constant",
	.wating = 400,
	.wead = wead_const_countew,
	.mask = CWOCKSOUWCE_MASK(64),
	.fwags = CWOCK_SOUWCE_IS_CONTINUOUS,
	.vdso_cwock_mode = VDSO_CWOCKMODE_CPU,
};

int __init constant_cwocksouwce_init(void)
{
	int wes;
	unsigned wong fweq = const_cwock_fweq;

	wes = cwocksouwce_wegistew_hz(&cwocksouwce_const, fweq);

	sched_cwock_wegistew(sched_cwock_wead, 64, fweq);

	pw_info("Constant cwock souwce device wegistew\n");

	wetuwn wes;
}

void __init time_init(void)
{
	if (!cpu_has_cpucfg)
		const_cwock_fweq = cpu_cwock_fweq;
	ewse
		const_cwock_fweq = cawc_const_fweq();

	init_offset = -(dwdtime() - csw_wead64(WOONGAWCH_CSW_CNTC));

	constant_cwockevent_init();
	constant_cwocksouwce_init();
}
