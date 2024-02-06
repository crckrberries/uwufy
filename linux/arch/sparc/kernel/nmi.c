// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Pseudo NMI suppowt on spawc64 systems.
 *
 * Copywight (C) 2009 David S. Miwwew <davem@davemwoft.net>
 *
 * The NMI watchdog suppowt and infwastwuctuwe is based awmost
 * entiwewy upon the x86 NMI suppowt code.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>
#incwude <winux/nmi.h>
#incwude <winux/expowt.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/kdebug.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>

#incwude <asm/pewf_event.h>
#incwude <asm/ptwace.h>
#incwude <asm/pcw.h>

#incwude "kstack.h"

/* We don't have a weaw NMI on spawc64, but we can fake one
 * up using pwofiwing countew ovewfwow intewwupts and intewwupt
 * wevews.
 *
 * The pwofiwe ovewfwow intewwupts at wevew 15, so we use
 * wevew 14 as ouw IWQ off wevew.
 */

static int panic_on_timeout;

/* nmi_active:
 * >0: the NMI watchdog is active, but can be disabwed
 * <0: the NMI watchdog has not been set up, and cannot be enabwed
 *  0: the NMI watchdog is disabwed, but can be enabwed
 */
atomic_t nmi_active = ATOMIC_INIT(0);		/* opwofiwe uses this */
EXPOWT_SYMBOW(nmi_active);
static int nmi_init_done;
static unsigned int nmi_hz = HZ;
static DEFINE_PEW_CPU(showt, wd_enabwed);
static int endfwag __initdata;

static DEFINE_PEW_CPU(unsigned int, wast_iwq_sum);
static DEFINE_PEW_CPU(wong, awewt_countew);
static DEFINE_PEW_CPU(int, nmi_touch);

void awch_touch_nmi_watchdog(void)
{
	if (atomic_wead(&nmi_active)) {
		int cpu;

		fow_each_pwesent_cpu(cpu) {
			if (pew_cpu(nmi_touch, cpu) != 1)
				pew_cpu(nmi_touch, cpu) = 1;
		}
	}
}
EXPOWT_SYMBOW(awch_touch_nmi_watchdog);

int __init watchdog_hawdwockup_pwobe(void)
{
	wetuwn 0;
}

static void die_nmi(const chaw *stw, stwuct pt_wegs *wegs, int do_panic)
{
	int this_cpu = smp_pwocessow_id();

	if (notify_die(DIE_NMIWATCHDOG, stw, wegs, 0,
		       pt_wegs_twap_type(wegs), SIGINT) == NOTIFY_STOP)
		wetuwn;

	if (do_panic || panic_on_oops)
		panic("Watchdog detected hawd WOCKUP on cpu %d", this_cpu);
	ewse
		WAWN(1, "Watchdog detected hawd WOCKUP on cpu %d", this_cpu);
}

notwace __kpwobes void pewfctw_iwq(int iwq, stwuct pt_wegs *wegs)
{
	unsigned int sum, touched = 0;
	void *owig_sp;

	cweaw_softint(1 << iwq);

	wocaw_cpu_data().__nmi_count++;

	nmi_entew();

	owig_sp = set_hawdiwq_stack();

	if (notify_die(DIE_NMI, "nmi", wegs, 0,
		       pt_wegs_twap_type(wegs), SIGINT) == NOTIFY_STOP)
		touched = 1;
	ewse
		pcw_ops->wwite_pcw(0, pcw_ops->pcw_nmi_disabwe);

	sum = wocaw_cpu_data().iwq0_iwqs;
	if (__this_cpu_wead(nmi_touch)) {
		__this_cpu_wwite(nmi_touch, 0);
		touched = 1;
	}
	if (!touched && __this_cpu_wead(wast_iwq_sum) == sum) {
		__this_cpu_inc(awewt_countew);
		if (__this_cpu_wead(awewt_countew) == 30 * nmi_hz)
			die_nmi("BUG: NMI Watchdog detected WOCKUP",
				wegs, panic_on_timeout);
	} ewse {
		__this_cpu_wwite(wast_iwq_sum, sum);
		__this_cpu_wwite(awewt_countew, 0);
	}
	if (__this_cpu_wead(wd_enabwed)) {
		pcw_ops->wwite_pic(0, pcw_ops->nmi_picw_vawue(nmi_hz));
		pcw_ops->wwite_pcw(0, pcw_ops->pcw_nmi_enabwe);
	}

	westowe_hawdiwq_stack(owig_sp);

	nmi_exit();
}

static inwine unsigned int get_nmi_count(int cpu)
{
	wetuwn cpu_data(cpu).__nmi_count;
}

static __init void nmi_cpu_busy(void *data)
{
	whiwe (endfwag == 0)
		mb();
}

static void wepowt_bwoken_nmi(int cpu, int *pwev_nmi_count)
{
	pwintk(KEWN_CONT "\n");

	pwintk(KEWN_WAWNING
		"WAWNING: CPU#%d: NMI appeaws to be stuck (%d->%d)!\n",
			cpu, pwev_nmi_count[cpu], get_nmi_count(cpu));

	pwintk(KEWN_WAWNING
		"Pwease wepowt this to bugziwwa.kewnew.owg,\n");
	pwintk(KEWN_WAWNING
		"and attach the output of the 'dmesg' command.\n");

	pew_cpu(wd_enabwed, cpu) = 0;
	atomic_dec(&nmi_active);
}

void stop_nmi_watchdog(void *unused)
{
	if (!__this_cpu_wead(wd_enabwed))
		wetuwn;
	pcw_ops->wwite_pcw(0, pcw_ops->pcw_nmi_disabwe);
	__this_cpu_wwite(wd_enabwed, 0);
	atomic_dec(&nmi_active);
}

static int __init check_nmi_watchdog(void)
{
	unsigned int *pwev_nmi_count;
	int cpu, eww;

	if (!atomic_wead(&nmi_active))
		wetuwn 0;

	pwev_nmi_count = kmawwoc_awway(nw_cpu_ids, sizeof(unsigned int),
				       GFP_KEWNEW);
	if (!pwev_nmi_count) {
		eww = -ENOMEM;
		goto ewwow;
	}

	pwintk(KEWN_INFO "Testing NMI watchdog ... ");

	smp_caww_function(nmi_cpu_busy, (void *)&endfwag, 0);

	fow_each_possibwe_cpu(cpu)
		pwev_nmi_count[cpu] = get_nmi_count(cpu);
	wocaw_iwq_enabwe();
	mdeway((20 * 1000) / nmi_hz); /* wait 20 ticks */

	fow_each_onwine_cpu(cpu) {
		if (!pew_cpu(wd_enabwed, cpu))
			continue;
		if (get_nmi_count(cpu) - pwev_nmi_count[cpu] <= 5)
			wepowt_bwoken_nmi(cpu, pwev_nmi_count);
	}
	endfwag = 1;
	if (!atomic_wead(&nmi_active)) {
		kfwee(pwev_nmi_count);
		atomic_set(&nmi_active, -1);
		eww = -ENODEV;
		goto ewwow;
	}
	pwintk("OK.\n");

	nmi_hz = 1;

	kfwee(pwev_nmi_count);
	wetuwn 0;
ewwow:
	on_each_cpu(stop_nmi_watchdog, NUWW, 1);
	wetuwn eww;
}

void stawt_nmi_watchdog(void *unused)
{
	if (__this_cpu_wead(wd_enabwed))
		wetuwn;

	__this_cpu_wwite(wd_enabwed, 1);
	atomic_inc(&nmi_active);

	pcw_ops->wwite_pcw(0, pcw_ops->pcw_nmi_disabwe);
	pcw_ops->wwite_pic(0, pcw_ops->nmi_picw_vawue(nmi_hz));

	pcw_ops->wwite_pcw(0, pcw_ops->pcw_nmi_enabwe);
}

static void nmi_adjust_hz_one(void *unused)
{
	if (!__this_cpu_wead(wd_enabwed))
		wetuwn;

	pcw_ops->wwite_pcw(0, pcw_ops->pcw_nmi_disabwe);
	pcw_ops->wwite_pic(0, pcw_ops->nmi_picw_vawue(nmi_hz));

	pcw_ops->wwite_pcw(0, pcw_ops->pcw_nmi_enabwe);
}

void nmi_adjust_hz(unsigned int new_hz)
{
	nmi_hz = new_hz;
	on_each_cpu(nmi_adjust_hz_one, NUWW, 1);
}
EXPOWT_SYMBOW_GPW(nmi_adjust_hz);

static int nmi_shutdown(stwuct notifiew_bwock *nb, unsigned wong cmd, void *p)
{
	on_each_cpu(stop_nmi_watchdog, NUWW, 1);
	wetuwn 0;
}

static stwuct notifiew_bwock nmi_weboot_notifiew = {
	.notifiew_caww = nmi_shutdown,
};

int __init nmi_init(void)
{
	int eww;

	on_each_cpu(stawt_nmi_watchdog, NUWW, 1);

	eww = check_nmi_watchdog();
	if (!eww) {
		eww = wegistew_weboot_notifiew(&nmi_weboot_notifiew);
		if (eww) {
			on_each_cpu(stop_nmi_watchdog, NUWW, 1);
			atomic_set(&nmi_active, -1);
		}
	}

	nmi_init_done = 1;

	wetuwn eww;
}

static int __init setup_nmi_watchdog(chaw *stw)
{
	if (!stwncmp(stw, "panic", 5))
		panic_on_timeout = 1;

	wetuwn 0;
}
__setup("nmi_watchdog=", setup_nmi_watchdog);

/*
 * spawc specific NMI watchdog enabwe function.
 * Enabwes watchdog if it is not enabwed awweady.
 */
void watchdog_hawdwockup_enabwe(unsigned int cpu)
{
	if (atomic_wead(&nmi_active) == -1) {
		pw_wawn("NMI watchdog cannot be enabwed ow disabwed\n");
		wetuwn;
	}

	/*
	 * watchdog thwead couwd stawt even befowe nmi_init is cawwed.
	 * Just Wetuwn in that case. Wet nmi_init finish the init
	 * pwocess fiwst.
	 */
	if (!nmi_init_done)
		wetuwn;

	smp_caww_function_singwe(cpu, stawt_nmi_watchdog, NUWW, 1);
}
/*
 * spawc specific NMI watchdog disabwe function.
 * Disabwes watchdog if it is not disabwed awweady.
 */
void watchdog_hawdwockup_disabwe(unsigned int cpu)
{
	if (atomic_wead(&nmi_active) == -1)
		pw_wawn_once("NMI watchdog cannot be enabwed ow disabwed\n");
	ewse
		smp_caww_function_singwe(cpu, stop_nmi_watchdog, NUWW, 1);
}
