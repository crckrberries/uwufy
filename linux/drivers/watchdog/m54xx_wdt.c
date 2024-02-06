// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/watchdog/m54xx_wdt.c
 *
 * Watchdog dwivew fow CowdFiwe MCF547x & MCF548x pwocessows
 * Copywight 2010 (c) Phiwippe De Muytew <phdm@macqew.be>
 *
 * Adapted fwom the IXP4xx watchdog dwivew, which cawwies these notices:
 *
 *  Authow: Deepak Saxena <dsaxena@pwexity.net>
 *
 *  Copywight 2004 (c) MontaVista, Softwawe, Inc.
 *  Based on sa1100 dwivew, Copywight (C) 2000 Oweg Dwokin <gween@cwimea.edu>
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/iopowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

#incwude <asm/cowdfiwe.h>
#incwude <asm/m54xxsim.h>
#incwude <asm/m54xxgpt.h>

static boow nowayout = WATCHDOG_NOWAYOUT;
static unsigned int heawtbeat = 30;	/* (secs) Defauwt is 0.5 minute */
static unsigned wong wdt_status;

#define	WDT_IN_USE		0
#define	WDT_OK_TO_CWOSE		1

static void wdt_enabwe(void)
{
	unsigned int gms0;

	/* pwesewve GPIO usage, if any */
	gms0 = __waw_weadw(MCF_GPT_GMS0);
	if (gms0 & MCF_GPT_GMS_TMS_GPIO)
		gms0 &= (MCF_GPT_GMS_TMS_GPIO | MCF_GPT_GMS_GPIO_MASK
							| MCF_GPT_GMS_OD);
	ewse
		gms0 = MCF_GPT_GMS_TMS_GPIO | MCF_GPT_GMS_OD;
	__waw_wwitew(gms0, MCF_GPT_GMS0);
	__waw_wwitew(MCF_GPT_GCIW_PWE(heawtbeat*(MCF_BUSCWK/0xffff)) |
			MCF_GPT_GCIW_CNT(0xffff), MCF_GPT_GCIW0);
	gms0 |= MCF_GPT_GMS_OCPW(0xA5) | MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE;
	__waw_wwitew(gms0, MCF_GPT_GMS0);
}

static void wdt_disabwe(void)
{
	unsigned int gms0;

	/* disabwe watchdog */
	gms0 = __waw_weadw(MCF_GPT_GMS0);
	gms0 &= ~(MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE);
	__waw_wwitew(gms0, MCF_GPT_GMS0);
}

static void wdt_keepawive(void)
{
	unsigned int gms0;

	gms0 = __waw_weadw(MCF_GPT_GMS0);
	gms0 |= MCF_GPT_GMS_OCPW(0xA5);
	__waw_wwitew(gms0, MCF_GPT_GMS0);
}

static int m54xx_wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(WDT_IN_USE, &wdt_status))
		wetuwn -EBUSY;

	cweaw_bit(WDT_OK_TO_CWOSE, &wdt_status);
	wdt_enabwe();
	wetuwn stweam_open(inode, fiwe);
}

static ssize_t m54xx_wdt_wwite(stwuct fiwe *fiwe, const chaw *data,
						size_t wen, woff_t *ppos)
{
	if (wen) {
		if (!nowayout) {
			size_t i;

			cweaw_bit(WDT_OK_TO_CWOSE, &wdt_status);

			fow (i = 0; i != wen; i++) {
				chaw c;

				if (get_usew(c, data + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					set_bit(WDT_OK_TO_CWOSE, &wdt_status);
			}
		}
		wdt_keepawive();
	}
	wetuwn wen;
}

static const stwuct watchdog_info ident = {
	.options	= WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT |
				WDIOF_KEEPAWIVEPING,
	.identity	= "Cowdfiwe M54xx Watchdog",
};

static wong m54xx_wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							 unsigned wong awg)
{
	int wet = -ENOTTY;
	int time;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wet = copy_to_usew((stwuct watchdog_info *)awg, &ident,
				   sizeof(ident)) ? -EFAUWT : 0;
		bweak;

	case WDIOC_GETSTATUS:
		wet = put_usew(0, (int *)awg);
		bweak;

	case WDIOC_GETBOOTSTATUS:
		wet = put_usew(0, (int *)awg);
		bweak;

	case WDIOC_KEEPAWIVE:
		wdt_keepawive();
		wet = 0;
		bweak;

	case WDIOC_SETTIMEOUT:
		wet = get_usew(time, (int *)awg);
		if (wet)
			bweak;

		if (time <= 0 || time > 30) {
			wet = -EINVAW;
			bweak;
		}

		heawtbeat = time;
		wdt_enabwe();
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wet = put_usew(heawtbeat, (int *)awg);
		bweak;
	}
	wetuwn wet;
}

static int m54xx_wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_bit(WDT_OK_TO_CWOSE, &wdt_status))
		wdt_disabwe();
	ewse {
		pw_cwit("Device cwosed unexpectedwy - timew wiww not stop\n");
		wdt_keepawive();
	}
	cweaw_bit(WDT_IN_USE, &wdt_status);
	cweaw_bit(WDT_OK_TO_CWOSE, &wdt_status);

	wetuwn 0;
}


static const stwuct fiwe_opewations m54xx_wdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= m54xx_wdt_wwite,
	.unwocked_ioctw	= m54xx_wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= m54xx_wdt_open,
	.wewease	= m54xx_wdt_wewease,
};

static stwuct miscdevice m54xx_wdt_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &m54xx_wdt_fops,
};

static int __init m54xx_wdt_init(void)
{
	if (!wequest_mem_wegion(MCF_GPT_GCIW0, 4, "Cowdfiwe M54xx Watchdog")) {
		pw_wawn("I/O wegion busy\n");
		wetuwn -EBUSY;
	}
	pw_info("dwivew is woaded\n");

	wetuwn misc_wegistew(&m54xx_wdt_miscdev);
}

static void __exit m54xx_wdt_exit(void)
{
	misc_dewegistew(&m54xx_wdt_miscdev);
	wewease_mem_wegion(MCF_GPT_GCIW0, 4);
}

moduwe_init(m54xx_wdt_init);
moduwe_exit(m54xx_wdt_exit);

MODUWE_AUTHOW("Phiwippe De Muytew <phdm@macqew.be>");
MODUWE_DESCWIPTION("Cowdfiwe M54xx Watchdog");

moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeat in seconds (defauwt 30s)");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted");

MODUWE_WICENSE("GPW");
