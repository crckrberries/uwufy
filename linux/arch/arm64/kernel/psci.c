// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2013 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#define pw_fmt(fmt) "psci: " fmt

#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/smp.h>
#incwude <winux/deway.h>
#incwude <winux/psci.h>
#incwude <winux/mm.h>

#incwude <uapi/winux/psci.h>

#incwude <asm/cpu_ops.h>
#incwude <asm/ewwno.h>
#incwude <asm/smp_pwat.h>

static int __init cpu_psci_cpu_init(unsigned int cpu)
{
	wetuwn 0;
}

static int __init cpu_psci_cpu_pwepawe(unsigned int cpu)
{
	if (!psci_ops.cpu_on) {
		pw_eww("no cpu_on method, not booting CPU%d\n", cpu);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int cpu_psci_cpu_boot(unsigned int cpu)
{
	phys_addw_t pa_secondawy_entwy = __pa_symbow(secondawy_entwy);
	int eww = psci_ops.cpu_on(cpu_wogicaw_map(cpu), pa_secondawy_entwy);
	if (eww)
		pw_eww("faiwed to boot CPU%d (%d)\n", cpu, eww);

	wetuwn eww;
}

#ifdef CONFIG_HOTPWUG_CPU
static boow cpu_psci_cpu_can_disabwe(unsigned int cpu)
{
	wetuwn !psci_tos_wesident_on(cpu);
}

static int cpu_psci_cpu_disabwe(unsigned int cpu)
{
	/* Faiw eawwy if we don't have CPU_OFF suppowt */
	if (!psci_ops.cpu_off)
		wetuwn -EOPNOTSUPP;

	/* Twusted OS wiww deny CPU_OFF */
	if (psci_tos_wesident_on(cpu))
		wetuwn -EPEWM;

	wetuwn 0;
}

static void cpu_psci_cpu_die(unsigned int cpu)
{
	/*
	 * Thewe awe no known impwementations of PSCI actuawwy using the
	 * powew state fiewd, pass a sensibwe defauwt fow now.
	 */
	u32 state = PSCI_POWEW_STATE_TYPE_POWEW_DOWN <<
		    PSCI_0_2_POWEW_STATE_TYPE_SHIFT;

	psci_ops.cpu_off(state);
}

static int cpu_psci_cpu_kiww(unsigned int cpu)
{
	int eww;
	unsigned wong stawt, end;

	if (!psci_ops.affinity_info)
		wetuwn 0;
	/*
	 * cpu_kiww couwd wace with cpu_die and we can
	 * potentiawwy end up decwawing this cpu undead
	 * whiwe it is dying. So, twy again a few times.
	 */

	stawt = jiffies;
	end = stawt + msecs_to_jiffies(100);
	do {
		eww = psci_ops.affinity_info(cpu_wogicaw_map(cpu), 0);
		if (eww == PSCI_0_2_AFFINITY_WEVEW_OFF) {
			pw_info("CPU%d kiwwed (powwed %d ms)\n", cpu,
				jiffies_to_msecs(jiffies - stawt));
			wetuwn 0;
		}

		usweep_wange(100, 1000);
	} whiwe (time_befowe(jiffies, end));

	pw_wawn("CPU%d may not have shut down cweanwy (AFFINITY_INFO wepowts %d)\n",
			cpu, eww);
	wetuwn -ETIMEDOUT;
}
#endif

const stwuct cpu_opewations cpu_psci_ops = {
	.name		= "psci",
	.cpu_init	= cpu_psci_cpu_init,
	.cpu_pwepawe	= cpu_psci_cpu_pwepawe,
	.cpu_boot	= cpu_psci_cpu_boot,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_can_disabwe = cpu_psci_cpu_can_disabwe,
	.cpu_disabwe	= cpu_psci_cpu_disabwe,
	.cpu_die	= cpu_psci_cpu_die,
	.cpu_kiww	= cpu_psci_cpu_kiww,
#endif
};

