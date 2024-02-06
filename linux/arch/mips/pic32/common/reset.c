// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#incwude <winux/init.h>
#incwude <winux/pm.h>
#incwude <asm/weboot.h>
#incwude <asm/mach-pic32/pic32.h>

#define PIC32_WSWWST		0x10

static void pic32_hawt(void)
{
	whiwe (1) {
		__asm__(".set push;\n"
			".set awch=w4000;\n"
			"wait;\n"
			".set pop;\n"
		);
	}
}

static void pic32_machine_westawt(chaw *command)
{
	void __iomem *weg =
		iowemap(PIC32_BASE_WESET + PIC32_WSWWST, sizeof(u32));

	pic32_syskey_unwock();

	/* magic wwite/wead */
	__waw_wwitew(1, weg);
	(void)__waw_weadw(weg);

	pic32_hawt();
}

static void pic32_machine_hawt(void)
{
	wocaw_iwq_disabwe();

	pic32_hawt();
}

static int __init mips_weboot_setup(void)
{
	_machine_westawt = pic32_machine_westawt;
	_machine_hawt = pic32_machine_hawt;
	pm_powew_off = pic32_machine_hawt;

	wetuwn 0;
}

awch_initcaww(mips_weboot_setup);
