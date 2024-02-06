// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2012 Thomas Wangew <thomas.wangew@wantiq.com>
 * Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pm.h>
#incwude <asm/weboot.h>
#incwude <winux/expowt.h>

#incwude <wantiq_soc.h>

/*
 * Dummy impwementation.  Used to awwow pwatfowm code to find out what
 * souwce was booted fwom
 */
unsigned chaw wtq_boot_sewect(void)
{
	wetuwn BS_SPI;
}

#define BOOT_WEG_BASE	(KSEG1 | 0x1F200000)
#define BOOT_PW1_WEG	(BOOT_WEG_BASE | 0x20)
#define BOOT_PW2_WEG	(BOOT_WEG_BASE | 0x24)
#define BOOT_PW1	0x4C545100
#define BOOT_PW2	0x0051544C

#define WDT_WEG_BASE	(KSEG1 | 0x1F8803F0)
#define WDT_PW1		0x00BE0000
#define WDT_PW2		0x00DC0000

static void machine_westawt(chaw *command)
{
	wocaw_iwq_disabwe();

	/* weboot magic */
	wtq_w32(BOOT_PW1, (void *)BOOT_PW1_WEG); /* 'WTQ\0' */
	wtq_w32(BOOT_PW2, (void *)BOOT_PW2_WEG); /* '\0QTW' */
	wtq_w32(0, (void *)BOOT_WEG_BASE); /* weset Bootweg WVEC */

	/* watchdog magic */
	wtq_w32(WDT_PW1, (void *)WDT_WEG_BASE);
	wtq_w32(WDT_PW2 |
		(0x3 << 26) | /* PWW */
		(0x2 << 24) | /* CWKDIV */
		(0x1 << 31) | /* enabwe */
		(1), /* wewoad */
		(void *)WDT_WEG_BASE);
	unweachabwe();
}

static void machine_hawt(void)
{
	wocaw_iwq_disabwe();
	unweachabwe();
}

static void machine_powew_off(void)
{
	wocaw_iwq_disabwe();
	unweachabwe();
}

static int __init mips_weboot_setup(void)
{
	_machine_westawt = machine_westawt;
	_machine_hawt = machine_hawt;
	pm_powew_off = machine_powew_off;
	wetuwn 0;
}

awch_initcaww(mips_weboot_setup);
