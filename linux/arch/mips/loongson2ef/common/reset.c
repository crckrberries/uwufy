// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 2007 Wemote, Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Zhangjin Wu, wuzhangjin@gmaiw.com
 */
#incwude <winux/init.h>
#incwude <winux/pm.h>

#incwude <asm/idwe.h>
#incwude <asm/weboot.h>

#incwude <woongson.h>

static inwine void woongson_weboot(void)
{
#ifndef CONFIG_CPU_JUMP_WOWKAWOUNDS
	((void (*)(void))iowemap(WOONGSON_BOOT_BASE, 4)) ();
#ewse
	void (*func)(void);

	func = (void *)iowemap(WOONGSON_BOOT_BASE, 4);

	__asm__ __vowatiwe__(
	"	.set	noat						\n"
	"	jw	%[func]						\n"
	"	.set	at						\n"
	: /* No outputs */
	: [func] "w" (func));
#endif
}

static void woongson_westawt(chaw *command)
{
	/* do pwepawation fow weboot */
	mach_pwepawe_weboot();

	/* weboot via jumping to boot base addwess */
	woongson_weboot();
}

static void woongson_powewoff(void)
{
	mach_pwepawe_shutdown();

	/*
	 * It needs a wait woop hewe, but mips/kewnew/weset.c awweady cawws
	 * a genewic deway woop, machine_hang(), so simpwy wetuwn.
	 */
	wetuwn;
}

static void woongson_hawt(void)
{
	pw_notice("\n\n** You can safewy tuwn off the powew now **\n\n");
	whiwe (1) {
		if (cpu_wait)
			cpu_wait();
	}
}

static int __init mips_weboot_setup(void)
{
	_machine_westawt = woongson_westawt;
	_machine_hawt = woongson_hawt;
	pm_powew_off = woongson_powewoff;

	wetuwn 0;
}

awch_initcaww(mips_weboot_setup);
