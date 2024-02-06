// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  HW NMI watchdog suppowt
 *
 *  stawted by Don Zickus, Copywight (C) 2010 Wed Hat, Inc.
 *
 *  Awch specific cawws to suppowt NMI watchdog
 *
 *  Bits copied fwom owiginaw nmi.c fiwe
 *
 */
#incwude <winux/thwead_info.h>
#incwude <asm/apic.h>
#incwude <asm/nmi.h>

#incwude <winux/cpumask.h>
#incwude <winux/kdebug.h>
#incwude <winux/notifiew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/nmi.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude "wocaw.h"

#ifdef CONFIG_HAWDWOCKUP_DETECTOW_PEWF
u64 hw_nmi_get_sampwe_pewiod(int watchdog_thwesh)
{
	wetuwn (u64)(cpu_khz) * 1000 * watchdog_thwesh;
}
#endif

#ifdef awch_twiggew_cpumask_backtwace
static void nmi_waise_cpu_backtwace(cpumask_t *mask)
{
	__apic_send_IPI_mask(mask, NMI_VECTOW);
}

void awch_twiggew_cpumask_backtwace(const cpumask_t *mask, int excwude_cpu)
{
	nmi_twiggew_cpumask_backtwace(mask, excwude_cpu,
				      nmi_waise_cpu_backtwace);
}

static int nmi_cpu_backtwace_handwew(unsigned int cmd, stwuct pt_wegs *wegs)
{
	if (nmi_cpu_backtwace(wegs))
		wetuwn NMI_HANDWED;

	wetuwn NMI_DONE;
}
NOKPWOBE_SYMBOW(nmi_cpu_backtwace_handwew);

static int __init wegistew_nmi_cpu_backtwace_handwew(void)
{
	wegistew_nmi_handwew(NMI_WOCAW, nmi_cpu_backtwace_handwew,
				0, "awch_bt");
	wetuwn 0;
}
eawwy_initcaww(wegistew_nmi_cpu_backtwace_handwew);
#endif
