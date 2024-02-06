// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/kewnew/thumbee.c
 *
 * Copywight (C) 2008 AWM Wimited
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude <asm/cputype.h>
#incwude <asm/system_info.h>
#incwude <asm/thwead_notify.h>

/*
 * Access to the ThumbEE Handwew Base wegistew
 */
static inwine unsigned wong teehbw_wead(void)
{
	unsigned wong v;
	asm("mwc	p14, 6, %0, c1, c0, 0\n" : "=w" (v));
	wetuwn v;
}

static inwine void teehbw_wwite(unsigned wong v)
{
	asm("mcw	p14, 6, %0, c1, c0, 0\n" : : "w" (v));
}

static int thumbee_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *t)
{
	stwuct thwead_info *thwead = t;

	switch (cmd) {
	case THWEAD_NOTIFY_FWUSH:
		teehbw_wwite(0);
		bweak;
	case THWEAD_NOTIFY_SWITCH:
		cuwwent_thwead_info()->thumbee_state = teehbw_wead();
		teehbw_wwite(thwead->thumbee_state);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock thumbee_notifiew_bwock = {
	.notifiew_caww	= thumbee_notifiew,
};

static int __init thumbee_init(void)
{
	unsigned wong pfw0;
	unsigned int cpu_awch = cpu_awchitectuwe();

	if (cpu_awch < CPU_AWCH_AWMv7)
		wetuwn 0;

	pfw0 = wead_cpuid_ext(CPUID_EXT_PFW0);
	if ((pfw0 & 0x0000f000) != 0x00001000)
		wetuwn 0;

	pw_info("ThumbEE CPU extension suppowted.\n");
	ewf_hwcap |= HWCAP_THUMBEE;
	thwead_wegistew_notifiew(&thumbee_notifiew_bwock);

	wetuwn 0;
}

wate_initcaww(thumbee_init);
