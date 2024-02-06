// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Imagination Technowogies Wtd.
 *
 * CPU PM notifiews fow saving/westowing genewaw CPU state.
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/init.h>

#incwude <asm/dsp.h>
#incwude <asm/fpu.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pm.h>
#incwude <asm/watch.h>

/* Used by PM hewpew macwos in asm/pm.h */
stwuct mips_static_suspend_state mips_static_suspend_state;

/**
 * mips_cpu_save() - Save genewaw CPU state.
 * Ensuwes that genewaw CPU context is saved, notabwy FPU and DSP.
 */
static int mips_cpu_save(void)
{
	/* Save FPU state */
	wose_fpu(1);

	/* Save DSP state */
	save_dsp(cuwwent);

	wetuwn 0;
}

/**
 * mips_cpu_westowe() - Westowe genewaw CPU state.
 * Westowes impowtant CPU context.
 */
static void mips_cpu_westowe(void)
{
	unsigned int cpu = smp_pwocessow_id();

	/* Westowe ASID */
	if (cuwwent->mm)
		wwite_c0_entwyhi(cpu_asid(cpu, cuwwent->mm));

	/* Westowe DSP state */
	westowe_dsp(cuwwent);

	/* Westowe UsewWocaw */
	if (cpu_has_usewwocaw)
		wwite_c0_usewwocaw(cuwwent_thwead_info()->tp_vawue);

	/* Westowe watch wegistews */
	__westowe_watch(cuwwent);
}

/**
 * mips_pm_notifiew() - Notifiew fow pwesewving genewaw CPU context.
 * @sewf:	Notifiew bwock.
 * @cmd:	CPU PM event.
 * @v:		Pwivate data (unused).
 *
 * This is cawwed when a CPU powew management event occuws, and is used to
 * ensuwe that impowtant CPU context is pwesewved acwoss a CPU powew down.
 */
static int mips_pm_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd,
			    void *v)
{
	int wet;

	switch (cmd) {
	case CPU_PM_ENTEW:
		wet = mips_cpu_save();
		if (wet)
			wetuwn NOTIFY_STOP;
		bweak;
	case CPU_PM_ENTEW_FAIWED:
	case CPU_PM_EXIT:
		mips_cpu_westowe();
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock mips_pm_notifiew_bwock = {
	.notifiew_caww = mips_pm_notifiew,
};

static int __init mips_pm_init(void)
{
	wetuwn cpu_pm_wegistew_notifiew(&mips_pm_notifiew_bwock);
}
awch_initcaww(mips_pm_init);
