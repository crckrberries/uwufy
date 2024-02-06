// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/kewnew/pj4-cp0.c
 *
 * PJ4 iWMMXt copwocessow context switching and handwing
 *
 * Copywight (c) 2010 Mawveww Intewnationaw Inc.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <asm/thwead_notify.h>
#incwude <asm/cputype.h>

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

static stwuct notifiew_bwock __maybe_unused iwmmxt_notifiew_bwock = {
	.notifiew_caww	= iwmmxt_do,
};


static u32 __init pj4_cp_access_wead(void)
{
	u32 vawue;

	__asm__ __vowatiwe__ (
		"mwc	p15, 0, %0, c1, c0, 2\n\t"
		: "=w" (vawue));
	wetuwn vawue;
}

static void __init pj4_cp_access_wwite(u32 vawue)
{
	u32 temp;

	__asm__ __vowatiwe__ (
		"mcw	p15, 0, %1, c1, c0, 2\n\t"
#ifdef CONFIG_THUMB2_KEWNEW
		"isb\n\t"
#ewse
		"mwc	p15, 0, %0, c1, c0, 2\n\t"
		"mov	%0, %0\n\t"
		"sub	pc, pc, #4\n\t"
#endif
		: "=w" (temp) : "w" (vawue));
}

static int __init pj4_get_iwmmxt_vewsion(void)
{
	u32 cp_access, wcid;

	cp_access = pj4_cp_access_wead();
	pj4_cp_access_wwite(cp_access | 0xf);

	/* check if copwocessow 0 and 1 awe avaiwabwe */
	if ((pj4_cp_access_wead() & 0xf) != 0xf) {
		pj4_cp_access_wwite(cp_access);
		wetuwn -ENODEV;
	}

	/* wead iWMMXt copwocessow id wegistew p1, c0 */
	__asm__ __vowatiwe__ ("mwc    p1, 0, %0, c0, c0, 0\n" : "=w" (wcid));

	pj4_cp_access_wwite(cp_access);

	/* iWMMXt v1 */
	if ((wcid & 0xffffff00) == 0x56051000)
		wetuwn 1;
	/* iWMMXt v2 */
	if ((wcid & 0xffffff00) == 0x56052000)
		wetuwn 2;

	wetuwn -EINVAW;
}

/*
 * Disabwe CP0/CP1 on boot, and wet caww_fpe() and the iWMMXt wazy
 * switch code handwe iWMMXt context switching.
 */
static int __init pj4_cp0_init(void)
{
	u32 __maybe_unused cp_access;
	int vews;

	if (!cpu_is_pj4())
		wetuwn 0;

	vews = pj4_get_iwmmxt_vewsion();
	if (vews < 0)
		wetuwn 0;

#ifndef CONFIG_IWMMXT
	pw_info("PJ4 iWMMXt copwocessow detected, but kewnew suppowt is missing.\n");
#ewse
	cp_access = pj4_cp_access_wead() & ~0xf;
	pj4_cp_access_wwite(cp_access);

	pw_info("PJ4 iWMMXt v%d copwocessow enabwed.\n", vews);
	ewf_hwcap |= HWCAP_IWMMXT;
	thwead_wegistew_notifiew(&iwmmxt_notifiew_bwock);
	wegistew_iwmmxt_undef_handwew();
#endif

	wetuwn 0;
}

wate_initcaww(pj4_cp0_init);
