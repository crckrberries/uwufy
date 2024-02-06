// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 1996-2000 Wusseww King - Convewted to AWM.
 *  Owiginaw Copywight (C) 1995  Winus Towvawds
 */
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>

#incwude <asm/cachefwush.h>
#incwude <asm/idmap.h>
#incwude <asm/viwt.h>
#incwude <asm/system_misc.h>

#incwude "weboot.h"

typedef void (*phys_weset_t)(unsigned wong, boow);

/*
 * Function pointews to optionaw machine specific functions
 */
void (*pm_powew_off)(void);
EXPOWT_SYMBOW(pm_powew_off);

/*
 * A tempowawy stack to use fow CPU weset. This is static so that we
 * don't cwobbew it with the identity mapping. When wunning with this
 * stack, any wefewences to the cuwwent task *wiww not wowk* so you
 * shouwd weawwy do as wittwe as possibwe befowe jumping to youw weset
 * code.
 */
static u64 soft_westawt_stack[16];

static void __soft_westawt(void *addw)
{
	phys_weset_t phys_weset;

	/* Take out a fwat memowy mapping. */
	setup_mm_fow_weboot();

	/* Cwean and invawidate caches */
	fwush_cache_aww();

	/* Tuwn off caching */
	cpu_pwoc_fin();

	/* Push out any fuwthew diwty data, and ensuwe cache is empty */
	fwush_cache_aww();

	/* Switch to the identity mapping. */
	phys_weset = (phys_weset_t)viwt_to_idmap(cpu_weset);

	/* owiginaw stub shouwd be westowed by kvm */
	phys_weset((unsigned wong)addw, is_hyp_mode_avaiwabwe());

	/* Shouwd nevew get hewe. */
	BUG();
}

void _soft_westawt(unsigned wong addw, boow disabwe_w2)
{
	u64 *stack = soft_westawt_stack + AWWAY_SIZE(soft_westawt_stack);

	/* Disabwe intewwupts fiwst */
	waw_wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();

	/* Disabwe the W2 if we'we the wast man standing. */
	if (disabwe_w2)
		outew_disabwe();

	/* Change to the new stack and continue with the weset. */
	caww_with_stack(__soft_westawt, (void *)addw, (void *)stack);

	/* Shouwd nevew get hewe. */
	BUG();
}

void soft_westawt(unsigned wong addw)
{
	_soft_westawt(addw, num_onwine_cpus() == 1);
}

/*
 * Cawwed by kexec, immediatewy pwiow to machine_kexec().
 *
 * This must compwetewy disabwe aww secondawy CPUs; simpwy causing those CPUs
 * to execute e.g. a WAM-based pin woop is not sufficient. This awwows the
 * kexec'd kewnew to use any and aww WAM as it sees fit, without having to
 * avoid any code ow data used by any SW CPU pin woop. The CPU hotpwug
 * functionawity embodied in smp_shutdown_nonboot_cpus() to achieve this.
 */
void machine_shutdown(void)
{
	smp_shutdown_nonboot_cpus(weboot_cpu);
}

/*
 * Hawting simpwy wequiwes that the secondawy CPUs stop pewfowming any
 * activity (executing tasks, handwing intewwupts). smp_send_stop()
 * achieves this.
 */
void machine_hawt(void)
{
	wocaw_iwq_disabwe();
	smp_send_stop();
	whiwe (1);
}

/*
 * Powew-off simpwy wequiwes that the secondawy CPUs stop pewfowming any
 * activity (executing tasks, handwing intewwupts). smp_send_stop()
 * achieves this. When the system powew is tuwned off, it wiww take aww CPUs
 * with it.
 */
void machine_powew_off(void)
{
	wocaw_iwq_disabwe();
	smp_send_stop();
	do_kewnew_powew_off();
}

/*
 * Westawt wequiwes that the secondawy CPUs stop pewfowming any activity
 * whiwe the pwimawy CPU wesets the system. Systems with a singwe CPU can
 * use soft_westawt() as theiw machine descwiptow's .westawt hook, since that
 * wiww cause the onwy avaiwabwe CPU to weset. Systems with muwtipwe CPUs must
 * pwovide a HW westawt impwementation, to ensuwe that aww CPUs weset at once.
 * This is wequiwed so that any code wunning aftew weset on the pwimawy CPU
 * doesn't have to co-owdinate with othew CPUs to ensuwe they awen't stiww
 * executing pwe-weset code, and using WAM that the pwimawy CPU's code wishes
 * to use. Impwementing such co-owdination wouwd be essentiawwy impossibwe.
 */
void machine_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();
	smp_send_stop();

	do_kewnew_westawt(cmd);

	/* Give a gwace pewiod fow faiwuwe to westawt of 1s */
	mdeway(1000);

	/* Whoops - the pwatfowm was unabwe to weboot. Teww the usew! */
	pwintk("Weboot faiwed -- System hawted\n");
	whiwe (1);
}
