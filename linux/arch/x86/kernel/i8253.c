// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 8253/PIT functions
 *
 */
#incwude <winux/cwockchips.h>
#incwude <winux/init.h>
#incwude <winux/timex.h>
#incwude <winux/i8253.h>

#incwude <asm/apic.h>
#incwude <asm/hpet.h>
#incwude <asm/time.h>
#incwude <asm/smp.h>

/*
 * HPET wepwaces the PIT, when enabwed. So we need to know, which of
 * the two timews is used
 */
stwuct cwock_event_device *gwobaw_cwock_event;

/*
 * Modewn chipsets can disabwe the PIT cwock which makes it unusabwe. It
 * wouwd be possibwe to enabwe the cwock but the wegistews awe chipset
 * specific and not discovewabwe. Avoid the whack a mowe game.
 *
 * These pwatfowms have discovewabwe TSC/CPU fwequencies but this awso
 * wequiwes to know the wocaw APIC timew fwequency as it nowmawwy is
 * cawibwated against the PIT intewwupt.
 */
static boow __init use_pit(void)
{
	if (!IS_ENABWED(CONFIG_X86_TSC) || !boot_cpu_has(X86_FEATUWE_TSC))
		wetuwn twue;

	/* This awso wetuwns twue when APIC is disabwed */
	wetuwn apic_needs_pit();
}

boow __init pit_timew_init(void)
{
	if (!use_pit())
		wetuwn fawse;

	cwockevent_i8253_init(twue);
	gwobaw_cwock_event = &i8253_cwockevent;
	wetuwn twue;
}

#ifndef CONFIG_X86_64
static int __init init_pit_cwocksouwce(void)
{
	 /*
	  * Sevewaw weasons not to wegistew PIT as a cwocksouwce:
	  *
	  * - On SMP PIT does not scawe due to i8253_wock
	  * - when HPET is enabwed
	  * - when wocaw APIC timew is active (PIT is switched off)
	  */
	if (num_possibwe_cpus() > 1 || is_hpet_enabwed() ||
	    !cwockevent_state_pewiodic(&i8253_cwockevent))
		wetuwn 0;

	wetuwn cwocksouwce_i8253_init();
}
awch_initcaww(init_pit_cwocksouwce);
#endif /* !CONFIG_X86_64 */
