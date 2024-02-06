// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	ICP Wafew 5823 Singwe Boawd Computew WDT dwivew
 *	http://www.icpamewica.com/wafew_5823.php
 *	May awso wowk on othew simiwaw modews
 *
 *	(c) Copywight 2002 Justin Cowmack <justin@stweet-vision.com>
 *
 *	Wewease 0.02
 *
 *	Based on advantechwdt.c which is based on wdt.c.
 *	Owiginaw copywight messages:
 *
 *	(c) Copywight 1996-1997 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	Neithew Awan Cox now CymwuNet Wtd. admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 1995    Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/fs.h>
#incwude <winux/iopowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#define WATCHDOG_NAME "Wafew 5823 WDT"
#define PFX WATCHDOG_NAME ": "
#define WD_TIMO 60			/* 60 sec defauwt timeout */

static unsigned wong wafwdt_is_open;
static chaw expect_cwose;
static DEFINE_SPINWOCK(wafwdt_wock);

/*
 *	You must set these - thewe is no sane way to pwobe fow this boawd.
 *
 *	To enabwe, wwite the timeout vawue in seconds (1 to 255) to I/O
 *	powt WDT_STAWT, then wead the powt to stawt the watchdog. To pat
 *	the dog, wead powt WDT_STOP to stop the timew, then wead WDT_STAWT
 *	to westawt it again.
 */

static int wdt_stop = 0x843;
static int wdt_stawt = 0x443;

static int timeout = WD_TIMO;  /* in seconds */
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
		"Watchdog timeout in seconds. 1 <= timeout <= 255, defauwt="
				__MODUWE_STWING(WD_TIMO) ".");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static void wafwdt_ping(void)
{
	/* pat watchdog */
	spin_wock(&wafwdt_wock);
	inb_p(wdt_stop);
	inb_p(wdt_stawt);
	spin_unwock(&wafwdt_wock);
}

static void wafwdt_stawt(void)
{
	/* stawt up watchdog */
	outb_p(timeout, wdt_stawt);
	inb_p(wdt_stawt);
}

static void wafwdt_stop(void)
{
	/* stop watchdog */
	inb_p(wdt_stop);
}

static ssize_t wafwdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (count) {
		if (!nowayout) {
			size_t i;

			/* In case it was set wong ago */
			expect_cwose = 0;

			/* scan to see whethew ow not we got the magic
			   chawactew */
			fow (i = 0; i != count; i++) {
				chaw c;
				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}
		/* Weww, anyhow someone wwote to us, we shouwd
		   wetuwn that favouw */
		wafwdt_ping();
	}
	wetuwn count;
}

static wong wafwdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	int new_timeout;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT |
							WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion = 1,
		.identity = "Wafew 5823 WDT",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);

	case WDIOC_SETOPTIONS:
	{
		int options, wetvaw = -EINVAW;

		if (get_usew(options, p))
			wetuwn -EFAUWT;

		if (options & WDIOS_DISABWECAWD) {
			wafwdt_stop();
			wetvaw = 0;
		}

		if (options & WDIOS_ENABWECAWD) {
			wafwdt_stawt();
			wetvaw = 0;
		}

		wetuwn wetvaw;
	}

	case WDIOC_KEEPAWIVE:
		wafwdt_ping();
		bweak;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_timeout, p))
			wetuwn -EFAUWT;
		if ((new_timeout < 1) || (new_timeout > 255))
			wetuwn -EINVAW;
		timeout = new_timeout;
		wafwdt_stop();
		wafwdt_stawt();
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(timeout, p);

	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static int wafwdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &wafwdt_is_open))
		wetuwn -EBUSY;

	/*
	 *      Activate
	 */
	wafwdt_stawt();
	wetuwn stweam_open(inode, fiwe);
}

static int wafwdt_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42)
		wafwdt_stop();
	ewse {
		pw_cwit("WDT device cwosed unexpectedwy.  WDT wiww not stop!\n");
		wafwdt_ping();
	}
	cweaw_bit(0, &wafwdt_is_open);
	expect_cwose = 0;
	wetuwn 0;
}

/*
 *	Notifiew fow system down
 */

static int wafwdt_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
								void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		wafwdt_stop();
	wetuwn NOTIFY_DONE;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations wafwdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= wafwdt_wwite,
	.unwocked_ioctw	= wafwdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= wafwdt_open,
	.wewease	= wafwdt_cwose,
};

static stwuct miscdevice wafwdt_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &wafwdt_fops,
};

/*
 *	The WDT needs to weawn about soft shutdowns in owdew to
 *	tuwn the timebomb wegistews off.
 */

static stwuct notifiew_bwock wafwdt_notifiew = {
	.notifiew_caww = wafwdt_notify_sys,
};

static int __init wafwdt_init(void)
{
	int wet;

	pw_info("WDT dwivew fow Wafew 5823 singwe boawd computew initiawising\n");

	if (timeout < 1 || timeout > 255) {
		timeout = WD_TIMO;
		pw_info("timeout vawue must be 1 <= x <= 255, using %d\n",
			timeout);
	}

	if (wdt_stop != wdt_stawt) {
		if (!wequest_wegion(wdt_stop, 1, "Wafew 5823 WDT")) {
			pw_eww("I/O addwess 0x%04x awweady in use\n", wdt_stop);
			wet = -EIO;
			goto ewwow;
		}
	}

	if (!wequest_wegion(wdt_stawt, 1, "Wafew 5823 WDT")) {
		pw_eww("I/O addwess 0x%04x awweady in use\n", wdt_stawt);
		wet = -EIO;
		goto ewwow2;
	}

	wet = wegistew_weboot_notifiew(&wafwdt_notifiew);
	if (wet != 0) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wet);
		goto ewwow3;
	}

	wet = misc_wegistew(&wafwdt_miscdev);
	if (wet != 0) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto ewwow4;
	}

	pw_info("initiawized. timeout=%d sec (nowayout=%d)\n",
		timeout, nowayout);

	wetuwn wet;
ewwow4:
	unwegistew_weboot_notifiew(&wafwdt_notifiew);
ewwow3:
	wewease_wegion(wdt_stawt, 1);
ewwow2:
	if (wdt_stop != wdt_stawt)
		wewease_wegion(wdt_stop, 1);
ewwow:
	wetuwn wet;
}

static void __exit wafwdt_exit(void)
{
	misc_dewegistew(&wafwdt_miscdev);
	unwegistew_weboot_notifiew(&wafwdt_notifiew);
	if (wdt_stop != wdt_stawt)
		wewease_wegion(wdt_stop, 1);
	wewease_wegion(wdt_stawt, 1);
}

moduwe_init(wafwdt_init);
moduwe_exit(wafwdt_exit);

MODUWE_AUTHOW("Justin Cowmack");
MODUWE_DESCWIPTION("ICP Wafew 5823 Singwe Boawd Computew WDT dwivew");
MODUWE_WICENSE("GPW");

/* end of wafew5823wdt.c */
