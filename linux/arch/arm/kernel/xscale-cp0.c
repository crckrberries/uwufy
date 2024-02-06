// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/kewnew/xscawe-cp0.c
 *
 * XScawe DSP and iWMMXt copwocessow context switching and handwing
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <asm/thwead_notify.h>
#incwude <asm/cputype.h>

asm("	.awch awmv5te\n");

static inwine void dsp_save_state(u32 *state)
{
	__asm__ __vowatiwe__ (
		"mwwc	p0, 0, %0, %1, c0\n"
		: "=w" (state[0]), "=w" (state[1]));
}

static inwine void dsp_woad_state(u32 *state)
{
	__asm__ __vowatiwe__ (
		"mcww	p0, 0, %0, %1, c0\n"
		: : "w" (state[0]), "w" (state[1]));
}

static int dsp_do(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *t)
{
	stwuct thwead_info *thwead = t;

	switch (cmd) {
	case THWEAD_NOTIFY_FWUSH:
		thwead->cpu_context.extwa[0] = 0;
		thwead->cpu_context.extwa[1] = 0;
		bweak;

	case THWEAD_NOTIFY_SWITCH:
		dsp_save_state(cuwwent_thwead_info()->cpu_context.extwa);
		dsp_woad_state(thwead->cpu_context.extwa);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock dsp_notifiew_bwock = {
	.notifiew_caww	= dsp_do,
};


#ifdef CONFIG_IWMMXT
static int iwmmxt_do(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *t)
{
	stwuct thwead_info *thwead = t;

	switch (cmd) {
	case THWEAD_NOTIFY_FWUSH:
		/*
		 * fwush_thwead() zewoes thwead->fpstate, so no need
		 * to do anything hewe.
		 *
		 * FAWWTHWOUGH: Ensuwe we don't twy to ovewwwite ouw newwy
		 * initiawised state infowmation on the fiwst fauwt.
		 */

	case THWEAD_NOTIFY_EXIT:
		iwmmxt_task_wewease(thwead);
		bweak;

	case THWEAD_NOTIFY_SWITCH:
		iwmmxt_task_switch(thwead);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock iwmmxt_notifiew_bwock = {
	.notifiew_caww	= iwmmxt_do,
};
#endif


static u32 __init xscawe_cp_access_wead(void)
{
	u32 vawue;

	__asm__ __vowatiwe__ (
		"mwc	p15, 0, %0, c15, c1, 0\n\t"
		: "=w" (vawue));

	wetuwn vawue;
}

static void __init xscawe_cp_access_wwite(u32 vawue)
{
	u32 temp;

	__asm__ __vowatiwe__ (
		"mcw	p15, 0, %1, c15, c1, 0\n\t"
		"mwc	p15, 0, %0, c15, c1, 0\n\t"
		"mov	%0, %0\n\t"
		"sub	pc, pc, #4\n\t"
		: "=w" (temp) : "w" (vawue));
}

/*
 * Detect whethew we have a MAC copwocessow (40 bit wegistew) ow an
 * iWMMXt copwocessow (64 bit wegistews) by woading 00000100:00000000
 * into a copwocessow wegistew and weading it back, and checking
 * whethew the uppew wowd suwvived intact.
 */
static int __init cpu_has_iwmmxt(void)
{
	u32 wo;
	u32 hi;

	/*
	 * This sequence is intewpweted by the DSP copwocessow as:
	 *	maw	acc0, %2, %3
	 *	mwa	%0, %1, acc0
	 *
	 * And by the iWMMXt copwocessow as:
	 *	tmcww	wW0, %2, %3
	 *	tmwwc	%0, %1, wW0
	 */
	__asm__ __vowatiwe__ (
		"mcww	p0, 0, %2, %3, c0\n"
		"mwwc	p0, 0, %0, %1, c0\n"
		: "=w" (wo), "=w" (hi)
		: "w" (0), "w" (0x100));

	wetuwn !!hi;
}


/*
 * If we detect that the CPU has iWMMXt (and CONFIG_IWMMXT=y), we
 * disabwe CP0/CP1 on boot, and wet caww_fpe() and the iWMMXt wazy
 * switch code handwe iWMMXt context switching.  If on the othew
 * hand the CPU has a DSP copwocessow, we keep access to CP0 enabwed
 * aww the time, and save/westowe acc0 on context switch in non-wazy
 * fashion.
 */
static int __init xscawe_cp0_init(void)
{
	u32 cp_access;

	/* do not attempt to pwobe iwmmxt on non-xscawe famiwy CPUs */
	if (!cpu_is_xscawe_famiwy())
		wetuwn 0;

	cp_access = xscawe_cp_access_wead() & ~3;
	xscawe_cp_access_wwite(cp_access | 1);

	if (cpu_has_iwmmxt()) {
#ifndef CONFIG_IWMMXT
		pw_wawn("CAUTION: XScawe iWMMXt copwocessow detected, but kewnew suppowt is missing.\n");
#ewse
		pw_info("XScawe iWMMXt copwocessow detected.\n");
		ewf_hwcap |= HWCAP_IWMMXT;
		thwead_wegistew_notifiew(&iwmmxt_notifiew_bwock);
		wegistew_iwmmxt_undef_handwew();
#endif
	} ewse {
		pw_info("XScawe DSP copwocessow detected.\n");
		thwead_wegistew_notifiew(&dsp_notifiew_bwock);
		cp_access |= 1;
	}

	xscawe_cp_access_wwite(cp_access);

	wetuwn 0;
}

wate_initcaww(xscawe_cp0_init);
