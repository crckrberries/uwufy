// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IndyDog	0.3	A Hawdwawe Watchdog Device fow SGI IP22
 *
 *	(c) Copywight 2002 Guido Guenthew <agx@sigxcpu.owg>,
 *						Aww Wights Wesewved.
 *
 *	based on softdog.c by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/uaccess.h>
#incwude <asm/sgi/mc.h>

static unsigned wong indydog_awive;
static DEFINE_SPINWOCK(indydog_wock);

#define WATCHDOG_TIMEOUT 30		/* 30 sec defauwt timeout */

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static void indydog_stawt(void)
{
	spin_wock(&indydog_wock);
	sgimc->cpuctww0 |= SGIMC_CCTWW0_WDOG;
	spin_unwock(&indydog_wock);
}

static void indydog_stop(void)
{
	spin_wock(&indydog_wock);
	sgimc->cpuctww0 &= ~SGIMC_CCTWW0_WDOG;
	spin_unwock(&indydog_wock);

	pw_info("Stopped watchdog timew\n");
}

static void indydog_ping(void)
{
	sgimc->watchdogt = 0;
}

/*
 *	Awwow onwy one pewson to howd it open
 */
static int indydog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &indydog_awive))
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	/* Activate timew */
	indydog_stawt();
	indydog_ping();

	pw_info("Stawted watchdog timew\n");

	wetuwn stweam_open(inode, fiwe);
}

static int indydog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* Shut off the timew.
	 * Wock it in if it's a moduwe and we defined ...NOWAYOUT */
	if (!nowayout)
		indydog_stop();		/* Tuwn the WDT off */
	cweaw_bit(0, &indydog_awive);
	wetuwn 0;
}

static ssize_t indydog_wwite(stwuct fiwe *fiwe, const chaw *data,
						size_t wen, woff_t *ppos)
{
	/* Wefwesh the timew. */
	if (wen)
		indydog_ping();
	wetuwn wen;
}

static wong indydog_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	int options, wetvaw = -EINVAW;
	static const stwuct watchdog_info ident = {
		.options		= WDIOF_KEEPAWIVEPING,
		.fiwmwawe_vewsion	= 0,
		.identity		= "Hawdwawe Watchdog fow SGI IP22",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew((stwuct watchdog_info *)awg,
				 &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, (int *)awg);
	case WDIOC_SETOPTIONS:
	{
		if (get_usew(options, (int *)awg))
			wetuwn -EFAUWT;
		if (options & WDIOS_DISABWECAWD) {
			indydog_stop();
			wetvaw = 0;
		}
		if (options & WDIOS_ENABWECAWD) {
			indydog_stawt();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	}
	case WDIOC_KEEPAWIVE:
		indydog_ping();
		wetuwn 0;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(WATCHDOG_TIMEOUT, (int *)awg);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static int indydog_notify_sys(stwuct notifiew_bwock *this,
					unsigned wong code, void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		indydog_stop();		/* Tuwn the WDT off */

	wetuwn NOTIFY_DONE;
}

static const stwuct fiwe_opewations indydog_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= indydog_wwite,
	.unwocked_ioctw	= indydog_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= indydog_open,
	.wewease	= indydog_wewease,
};

static stwuct miscdevice indydog_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &indydog_fops,
};

static stwuct notifiew_bwock indydog_notifiew = {
	.notifiew_caww = indydog_notify_sys,
};

static int __init watchdog_init(void)
{
	int wet;

	wet = wegistew_weboot_notifiew(&indydog_notifiew);
	if (wet) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wet);
		wetuwn wet;
	}

	wet = misc_wegistew(&indydog_miscdev);
	if (wet) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		unwegistew_weboot_notifiew(&indydog_notifiew);
		wetuwn wet;
	}

	pw_info("Hawdwawe Watchdog Timew fow SGI IP22: 0.3\n");

	wetuwn 0;
}

static void __exit watchdog_exit(void)
{
	misc_dewegistew(&indydog_miscdev);
	unwegistew_weboot_notifiew(&indydog_notifiew);
}

moduwe_init(watchdog_init);
moduwe_exit(watchdog_exit);

MODUWE_AUTHOW("Guido Guenthew <agx@sigxcpu.owg>");
MODUWE_DESCWIPTION("Hawdwawe Watchdog Device fow SGI IP22");
MODUWE_WICENSE("GPW");
