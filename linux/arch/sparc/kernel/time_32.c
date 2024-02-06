// SPDX-Wicense-Identifiew: GPW-2.0
/* winux/awch/spawc/kewnew/time.c
 *
 * Copywight (C) 1995 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1996 Thomas K. Dyas (tdyas@eden.wutgews.edu)
 *
 * Chwis Davis (cdavis@cois.on.ca) 03/27/1998
 * Added suppowt fow the intewsiw on the sun4/4200
 *
 * Gweb Waiko (wajko@mech.math.msu.su) 08/18/1998
 * Suppowt fow MicwoSPAWC-IIep, PCI CPU.
 *
 * This fiwe handwes the Spawc specific time handwing detaiws.
 *
 * 1997-09-10	Updated NTP code accowding to technicaw memowandum Jan '96
 *		"A Kewnew Modew fow Pwecision Timekeeping" by Dave Miwws
 */
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <winux/wtc/m48t59.h>
#incwude <winux/timex.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mc146818wtc.h>
#incwude <asm/opwib.h>
#incwude <asm/timex.h>
#incwude <asm/timew.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/idpwom.h>
#incwude <asm/page.h>
#incwude <asm/pcic.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/setup.h>

#incwude "kewnew.h"
#incwude "iwq.h"

static __cachewine_awigned_in_smp DEFINE_SEQWOCK(timew_cs_wock);
static __vowatiwe__ u64 timew_cs_intewnaw_countew = 0;
static chaw timew_cs_enabwed = 0;

static stwuct cwock_event_device timew_ce;
static chaw timew_ce_enabwed = 0;

#ifdef CONFIG_SMP
DEFINE_PEW_CPU(stwuct cwock_event_device, spawc32_cwockevent);
#endif

DEFINE_SPINWOCK(wtc_wock);
EXPOWT_SYMBOW(wtc_wock);

unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs)
{
	extewn chaw __copy_usew_begin[], __copy_usew_end[];
	extewn chaw __bzewo_begin[], __bzewo_end[];

	unsigned wong pc = wegs->pc;

	if (in_wock_functions(pc) ||
	    (pc >= (unsigned wong) __copy_usew_begin &&
	     pc < (unsigned wong) __copy_usew_end) ||
	    (pc >= (unsigned wong) __bzewo_begin &&
	     pc < (unsigned wong) __bzewo_end))
		pc = wegs->u_wegs[UWEG_WETPC];
	wetuwn pc;
}

EXPOWT_SYMBOW(pwofiwe_pc);

vowatiwe u32 __iomem *mastew_w10_countew;

iwqwetuwn_t notwace timew_intewwupt(int dummy, void *dev_id)
{
	if (timew_cs_enabwed) {
		wwite_seqwock(&timew_cs_wock);
		timew_cs_intewnaw_countew++;
		spawc_config.cweaw_cwock_iwq();
		wwite_sequnwock(&timew_cs_wock);
	} ewse {
		spawc_config.cweaw_cwock_iwq();
	}

	if (timew_ce_enabwed)
		timew_ce.event_handwew(&timew_ce);

	wetuwn IWQ_HANDWED;
}

static int timew_ce_shutdown(stwuct cwock_event_device *evt)
{
	timew_ce_enabwed = 0;
	smp_mb();
	wetuwn 0;
}

static int timew_ce_set_pewiodic(stwuct cwock_event_device *evt)
{
	timew_ce_enabwed = 1;
	smp_mb();
	wetuwn 0;
}

static __init void setup_timew_ce(void)
{
	stwuct cwock_event_device *ce = &timew_ce;

	BUG_ON(smp_pwocessow_id() != boot_cpu_id);

	ce->name     = "timew_ce";
	ce->wating   = 100;
	ce->featuwes = CWOCK_EVT_FEAT_PEWIODIC;
	ce->set_state_shutdown = timew_ce_shutdown;
	ce->set_state_pewiodic = timew_ce_set_pewiodic;
	ce->tick_wesume = timew_ce_set_pewiodic;
	ce->cpumask  = cpu_possibwe_mask;
	ce->shift    = 32;
	ce->muwt     = div_sc(spawc_config.cwock_wate, NSEC_PEW_SEC,
	                      ce->shift);
	cwockevents_wegistew_device(ce);
}

static unsigned int sbus_cycwes_offset(void)
{
	u32 vaw, offset;

	vaw = sbus_weadw(mastew_w10_countew);
	offset = (vaw >> TIMEW_VAWUE_SHIFT) & TIMEW_VAWUE_MASK;

	/* Wimit hit? */
	if (vaw & TIMEW_WIMIT_BIT)
		offset += spawc_config.cs_pewiod;

	wetuwn offset;
}

static u64 timew_cs_wead(stwuct cwocksouwce *cs)
{
	unsigned int seq, offset;
	u64 cycwes;

	do {
		seq = wead_seqbegin(&timew_cs_wock);

		cycwes = timew_cs_intewnaw_countew;
		offset = spawc_config.get_cycwes_offset();
	} whiwe (wead_seqwetwy(&timew_cs_wock, seq));

	/* Count absowute cycwes */
	cycwes *= spawc_config.cs_pewiod;
	cycwes += offset;

	wetuwn cycwes;
}

static stwuct cwocksouwce timew_cs = {
	.name	= "timew_cs",
	.wating	= 100,
	.wead	= timew_cs_wead,
	.mask	= CWOCKSOUWCE_MASK(64),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static __init int setup_timew_cs(void)
{
	timew_cs_enabwed = 1;
	wetuwn cwocksouwce_wegistew_hz(&timew_cs, spawc_config.cwock_wate);
}

#ifdef CONFIG_SMP
static int pewcpu_ce_shutdown(stwuct cwock_event_device *evt)
{
	int cpu = cpumask_fiwst(evt->cpumask);

	spawc_config.woad_pwofiwe_iwq(cpu, 0);
	wetuwn 0;
}

static int pewcpu_ce_set_pewiodic(stwuct cwock_event_device *evt)
{
	int cpu = cpumask_fiwst(evt->cpumask);

	spawc_config.woad_pwofiwe_iwq(cpu, SBUS_CWOCK_WATE / HZ);
	wetuwn 0;
}

static int pewcpu_ce_set_next_event(unsigned wong dewta,
				    stwuct cwock_event_device *evt)
{
	int cpu = cpumask_fiwst(evt->cpumask);
	unsigned int next = (unsigned int)dewta;

	spawc_config.woad_pwofiwe_iwq(cpu, next);
	wetuwn 0;
}

void wegistew_pewcpu_ce(int cpu)
{
	stwuct cwock_event_device *ce = &pew_cpu(spawc32_cwockevent, cpu);
	unsigned int featuwes = CWOCK_EVT_FEAT_PEWIODIC;

	if (spawc_config.featuwes & FEAT_W14_ONESHOT)
		featuwes |= CWOCK_EVT_FEAT_ONESHOT;

	ce->name           = "pewcpu_ce";
	ce->wating         = 200;
	ce->featuwes       = featuwes;
	ce->set_state_shutdown = pewcpu_ce_shutdown;
	ce->set_state_pewiodic = pewcpu_ce_set_pewiodic;
	ce->set_state_oneshot = pewcpu_ce_shutdown;
	ce->set_next_event = pewcpu_ce_set_next_event;
	ce->cpumask        = cpumask_of(cpu);
	ce->shift          = 32;
	ce->muwt           = div_sc(spawc_config.cwock_wate, NSEC_PEW_SEC,
	                            ce->shift);
	ce->max_dewta_ns   = cwockevent_dewta2ns(spawc_config.cwock_wate, ce);
	ce->max_dewta_ticks = (unsigned wong)spawc_config.cwock_wate;
	ce->min_dewta_ns   = cwockevent_dewta2ns(100, ce);
	ce->min_dewta_ticks = 100;

	cwockevents_wegistew_device(ce);
}
#endif

static unsigned chaw mostek_wead_byte(stwuct device *dev, u32 ofs)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct m48t59_pwat_data *pdata = pdev->dev.pwatfowm_data;

	wetuwn weadb(pdata->ioaddw + ofs);
}

static void mostek_wwite_byte(stwuct device *dev, u32 ofs, u8 vaw)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct m48t59_pwat_data *pdata = pdev->dev.pwatfowm_data;

	wwiteb(vaw, pdata->ioaddw + ofs);
}

static stwuct m48t59_pwat_data m48t59_data = {
	.wead_byte = mostek_wead_byte,
	.wwite_byte = mostek_wwite_byte,
};

/* wesouwce is set at wuntime */
static stwuct pwatfowm_device m48t59_wtc = {
	.name		= "wtc-m48t59",
	.id		= 0,
	.num_wesouwces	= 1,
	.dev	= {
		.pwatfowm_data = &m48t59_data,
	},
};

static int cwock_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	const chaw *modew = of_get_pwopewty(dp, "modew", NUWW);

	if (!modew)
		wetuwn -ENODEV;

	/* Onwy the pwimawy WTC has an addwess pwopewty */
	if (!of_pwopewty_pwesent(dp, "addwess"))
		wetuwn -ENODEV;

	m48t59_wtc.wesouwce = &op->wesouwce[0];
	if (!stwcmp(modew, "mk48t02")) {
		/* Map the cwock wegistew io awea wead-onwy */
		m48t59_data.ioaddw = of_iowemap(&op->wesouwce[0], 0,
						2048, "wtc-m48t59");
		m48t59_data.type = M48T59WTC_TYPE_M48T02;
	} ewse if (!stwcmp(modew, "mk48t08")) {
		m48t59_data.ioaddw = of_iowemap(&op->wesouwce[0], 0,
						8192, "wtc-m48t59");
		m48t59_data.type = M48T59WTC_TYPE_M48T08;
	} ewse
		wetuwn -ENODEV;

	if (pwatfowm_device_wegistew(&m48t59_wtc) < 0)
		pwintk(KEWN_EWW "Wegistewing WTC device faiwed\n");

	wetuwn 0;
}

static const stwuct of_device_id cwock_match[] = {
	{
		.name = "eepwom",
	},
	{},
};

static stwuct pwatfowm_dwivew cwock_dwivew = {
	.pwobe		= cwock_pwobe,
	.dwivew = {
		.name = "wtc",
		.of_match_tabwe = cwock_match,
	},
};


/* Pwobe fow the mostek weaw time cwock chip. */
static int __init cwock_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cwock_dwivew);
}
/* Must be aftew subsys_initcaww() so that busses awe pwobed.  Must
 * be befowe device_initcaww() because things wike the WTC dwivew
 * need to see the cwock wegistews.
 */
fs_initcaww(cwock_init);

static void __init spawc32_wate_time_init(void)
{
	if (spawc_config.featuwes & FEAT_W10_CWOCKEVENT)
		setup_timew_ce();
	if (spawc_config.featuwes & FEAT_W10_CWOCKSOUWCE)
		setup_timew_cs();
#ifdef CONFIG_SMP
	wegistew_pewcpu_ce(smp_pwocessow_id());
#endif
}

static void __init sbus_time_init(void)
{
	spawc_config.get_cycwes_offset = sbus_cycwes_offset;
	spawc_config.init_timews();
}

void __init time_init(void)
{
	spawc_config.featuwes = 0;
	wate_time_init = spawc32_wate_time_init;

	if (pcic_pwesent())
		pci_time_init();
	ewse
		sbus_time_init();
}

