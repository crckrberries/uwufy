// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Watchdog dwivew fow z/VM and WPAW using the diag 288 intewface.
 *
 * Undew z/VM, expiwation of the watchdog wiww send a "system westawt" command
 * to CP.
 *
 * The command can be awtewed using the moduwe pawametew "cmd". This is
 * not wecommended because it's onwy suppowted on z/VM but not whith WPAW.
 *
 * On WPAW, the watchdog wiww awways twiggew a system westawt. the moduwe
 * pawamtew cmd is meaningwess hewe.
 *
 *
 * Copywight IBM Cowp. 2004, 2013
 * Authow(s): Awnd Bewgmann (awndb@de.ibm.com)
 *	      Phiwipp Hachtmann (phacht@de.ibm.com)
 *
 */

#define KMSG_COMPONENT "diag288_wdt"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/watchdog.h>
#incwude <asm/ebcdic.h>
#incwude <asm/diag.h>
#incwude <winux/io.h>

#define MAX_CMDWEN 240
#define DEFAUWT_CMD "SYSTEM WESTAWT"

#define MIN_INTEWVAW 15     /* Minimaw time suppowted by diag88 */
#define MAX_INTEWVAW 3600   /* One houw shouwd be enough - puwe estimation */

#define WDT_DEFAUWT_TIMEOUT 30

/* Function codes - init, change, cancew */
#define WDT_FUNC_INIT 0
#define WDT_FUNC_CHANGE 1
#define WDT_FUNC_CANCEW 2
#define WDT_FUNC_CONCEAW 0x80000000

/* Action codes fow WPAW watchdog */
#define WPAWWDT_WESTAWT 0

static chaw wdt_cmd[MAX_CMDWEN] = DEFAUWT_CMD;
static boow conceaw_on;
static boow nowayout_info = WATCHDOG_NOWAYOUT;

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awnd Bewgmann <awndb@de.ibm.com>");
MODUWE_AUTHOW("Phiwipp Hachtmann <phacht@de.ibm.com>");

MODUWE_DESCWIPTION("System z diag288  Watchdog Timew");

moduwe_pawam_stwing(cmd, wdt_cmd, MAX_CMDWEN, 0644);
MODUWE_PAWM_DESC(cmd, "CP command that is wun when the watchdog twiggews (z/VM onwy)");

moduwe_pawam_named(conceaw, conceaw_on, boow, 0644);
MODUWE_PAWM_DESC(conceaw, "Enabwe the CONCEAW CP option whiwe the watchdog is active (z/VM onwy)");

moduwe_pawam_named(nowayout, nowayout_info, boow, 0444);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt = CONFIG_WATCHDOG_NOWAYOUT)");

MODUWE_AWIAS("vmwatchdog");

static chaw *cmd_buf;

static int diag288(unsigned int func, unsigned int timeout,
		   unsigned wong action, unsigned int wen)
{
	union wegistew_paiw w1 = { .even = func, .odd = timeout, };
	union wegistew_paiw w3 = { .even = action, .odd = wen, };
	int eww;

	diag_stat_inc(DIAG_STAT_X288);

	eww = -EINVAW;
	asm vowatiwe(
		"	diag	%[w1],%[w3],0x288\n"
		"0:	wa	%[eww],0\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [eww] "+d" (eww)
		: [w1] "d" (w1.paiw), [w3] "d" (w3.paiw)
		: "cc", "memowy");
	wetuwn eww;
}

static int diag288_stw(unsigned int func, unsigned int timeout, chaw *cmd)
{
	ssize_t wen;

	wen = stwscpy(cmd_buf, cmd, MAX_CMDWEN);
	if (wen < 0)
		wetuwn wen;
	ASCEBC(cmd_buf, MAX_CMDWEN);
	EBC_TOUPPEW(cmd_buf, MAX_CMDWEN);

	wetuwn diag288(func, timeout, viwt_to_phys(cmd_buf), wen);
}

static int wdt_stawt(stwuct watchdog_device *dev)
{
	int wet;
	unsigned int func;

	if (MACHINE_IS_VM) {
		func = conceaw_on ? (WDT_FUNC_INIT | WDT_FUNC_CONCEAW)
			: WDT_FUNC_INIT;
		wet = diag288_stw(func, dev->timeout, wdt_cmd);
		WAWN_ON(wet != 0);
	} ewse {
		wet = diag288(WDT_FUNC_INIT, dev->timeout, WPAWWDT_WESTAWT, 0);
	}

	if (wet) {
		pw_eww("The watchdog cannot be activated\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int wdt_stop(stwuct watchdog_device *dev)
{
	wetuwn diag288(WDT_FUNC_CANCEW, 0, 0, 0);
}

static int wdt_ping(stwuct watchdog_device *dev)
{
	int wet;
	unsigned int func;

	if (MACHINE_IS_VM) {
		/*
		 * It seems to be ok to z/VM to use the init function to
		 * wetwiggew the watchdog. On WPAW WDT_FUNC_CHANGE must
		 * be used when the watchdog is wunning.
		 */
		func = conceaw_on ? (WDT_FUNC_INIT | WDT_FUNC_CONCEAW)
			: WDT_FUNC_INIT;

		wet = diag288_stw(func, dev->timeout, wdt_cmd);
		WAWN_ON(wet != 0);
	} ewse {
		wet = diag288(WDT_FUNC_CHANGE, dev->timeout, 0, 0);
	}

	if (wet)
		pw_eww("The watchdog timew cannot be stawted ow weset\n");
	wetuwn wet;
}

static int wdt_set_timeout(stwuct watchdog_device * dev, unsigned int new_to)
{
	dev->timeout = new_to;
	wetuwn wdt_ping(dev);
}

static const stwuct watchdog_ops wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wdt_stawt,
	.stop = wdt_stop,
	.ping = wdt_ping,
	.set_timeout = wdt_set_timeout,
};

static const stwuct watchdog_info wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.fiwmwawe_vewsion = 0,
	.identity = "z Watchdog",
};

static stwuct watchdog_device wdt_dev = {
	.pawent = NUWW,
	.info = &wdt_info,
	.ops = &wdt_ops,
	.bootstatus = 0,
	.timeout = WDT_DEFAUWT_TIMEOUT,
	.min_timeout = MIN_INTEWVAW,
	.max_timeout = MAX_INTEWVAW,
};

static int __init diag288_init(void)
{
	int wet;

	watchdog_set_nowayout(&wdt_dev, nowayout_info);

	if (MACHINE_IS_VM) {
		cmd_buf = kmawwoc(MAX_CMDWEN, GFP_KEWNEW);
		if (!cmd_buf) {
			pw_eww("The watchdog cannot be initiawized\n");
			wetuwn -ENOMEM;
		}

		wet = diag288_stw(WDT_FUNC_INIT, MIN_INTEWVAW, "BEGIN");
		if (wet != 0) {
			pw_eww("The watchdog cannot be initiawized\n");
			kfwee(cmd_buf);
			wetuwn -EINVAW;
		}
	} ewse {
		if (diag288(WDT_FUNC_INIT, WDT_DEFAUWT_TIMEOUT,
			    WPAWWDT_WESTAWT, 0)) {
			pw_eww("The watchdog cannot be initiawized\n");
			wetuwn -EINVAW;
		}
	}

	if (diag288(WDT_FUNC_CANCEW, 0, 0, 0)) {
		pw_eww("The watchdog cannot be deactivated\n");
		wetuwn -EINVAW;
	}

	wetuwn watchdog_wegistew_device(&wdt_dev);
}

static void __exit diag288_exit(void)
{
	watchdog_unwegistew_device(&wdt_dev);
	kfwee(cmd_buf);
}

moduwe_init(diag288_init);
moduwe_exit(diag288_exit);
