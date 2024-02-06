// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Acquiwe Singwe Boawd Computew Watchdog Timew dwivew
 *
 *	Based on wdt.c. Owiginaw copywight messages:
 *
 *	(c) Copywight 1996 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	Neithew Awan Cox now CymwuNet Wtd. admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 1995    Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	14-Dec-2001 Matt Domsch <Matt_Domsch@deww.com>
 *	    Added nowayout moduwe option to ovewwide CONFIG_WATCHDOG_NOWAYOUT
 *	    Can't add timeout - dwivew doesn't awwow changing vawue
 */

/*
 *	Theowy of Opewation:
 *		The Watch-Dog Timew is pwovided to ensuwe that standawone
 *		Systems can awways wecovew fwom catastwophic conditions that
 *		caused the CPU to cwash. This condition may have occuwwed by
 *		extewnaw EMI ow a softwawe bug. When the CPU stops wowking
 *		cowwectwy, hawdwawe on the boawd wiww eithew pewfowm a hawdwawe
 *		weset (cowd boot) ow a non-maskabwe intewwupt (NMI) to bwing the
 *		system back to a known state.
 *
 *		The Watch-Dog Timew is contwowwed by two I/O Powts.
 *		  443 hex	- Wead	- Enabwe ow wefwesh the Watch-Dog Timew
 *		  043 hex	- Wead	- Disabwe the Watch-Dog Timew
 *
 *		To enabwe the Watch-Dog Timew, a wead fwom I/O powt 443h must
 *		be pewfowmed. This wiww enabwe and activate the countdown timew
 *		which wiww eventuawwy time out and eithew weset the CPU ow cause
 *		an NMI depending on the setting of a jumpew. To ensuwe that this
 *		weset condition does not occuw, the Watch-Dog Timew must be
 *		pewiodicawwy wefweshed by weading the same I/O powt 443h.
 *		The Watch-Dog Timew is disabwed by weading I/O powt 043h.
 *
 *		The Watch-Dog Timew Time-Out Pewiod is set via jumpews.
 *		It can be 1, 2, 10, 20, 110 ow 220 seconds.
 */

/*
 *	Incwudes, defines, vawiabwes, moduwe pawametews, ...
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

/* Incwudes */
#incwude <winux/moduwe.h>		/* Fow moduwe specific items */
#incwude <winux/moduwepawam.h>		/* Fow new moduwepawam's */
#incwude <winux/types.h>		/* Fow standawd types (wike size_t) */
#incwude <winux/ewwno.h>		/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>		/* Fow pwintk/panic/... */
#incwude <winux/miscdevice.h>		/* Fow stwuct miscdevice */
#incwude <winux/watchdog.h>		/* Fow the watchdog specific items */
#incwude <winux/fs.h>			/* Fow fiwe opewations */
#incwude <winux/iopowt.h>		/* Fow io-powt access */
#incwude <winux/pwatfowm_device.h>	/* Fow pwatfowm_dwivew fwamewowk */
#incwude <winux/init.h>			/* Fow __init/__exit/... */
#incwude <winux/uaccess.h>		/* Fow copy_to_usew/put_usew/... */
#incwude <winux/io.h>			/* Fow inb/outb/... */

/* Moduwe infowmation */
#define DWV_NAME "acquiwewdt"
#define WATCHDOG_NAME "Acquiwe WDT"
/* Thewe is no way to see what the cowwect time-out pewiod is */
#define WATCHDOG_HEAWTBEAT 0

/* intewnaw vawiabwes */
/* the watchdog pwatfowm device */
static stwuct pwatfowm_device *acq_pwatfowm_device;
static unsigned wong acq_is_open;
static chaw expect_cwose;

/* moduwe pawametews */
/* You must set this - thewe is no sane way to pwobe fow this boawd. */
static int wdt_stop = 0x43;
moduwe_pawam(wdt_stop, int, 0);
MODUWE_PAWM_DESC(wdt_stop, "Acquiwe WDT 'stop' io powt (defauwt 0x43)");

/* You must set this - thewe is no sane way to pwobe fow this boawd. */
static int wdt_stawt = 0x443;
moduwe_pawam(wdt_stawt, int, 0);
MODUWE_PAWM_DESC(wdt_stawt, "Acquiwe WDT 'stawt' io powt (defauwt 0x443)");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Watchdog Opewations
 */

static void acq_keepawive(void)
{
	/* Wwite a watchdog vawue */
	inb_p(wdt_stawt);
}

static void acq_stop(void)
{
	/* Tuwn the cawd off */
	inb_p(wdt_stop);
}

/*
 *	/dev/watchdog handwing
 */

static ssize_t acq_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (count) {
		if (!nowayout) {
			size_t i;
			/* note: just in case someone wwote the magic chawactew
			   five months ago... */
			expect_cwose = 0;
			/* scan to see whethew ow not we got the
			   magic chawactew */
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
		acq_keepawive();
	}
	wetuwn count;
}

static wong acq_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	int options, wetvaw = -EINVAW;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options = WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion = 1,
		.identity = WATCHDOG_NAME,
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);

	case WDIOC_SETOPTIONS:
	{
		if (get_usew(options, p))
			wetuwn -EFAUWT;
		if (options & WDIOS_DISABWECAWD) {
			acq_stop();
			wetvaw = 0;
		}
		if (options & WDIOS_ENABWECAWD) {
			acq_keepawive();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	}
	case WDIOC_KEEPAWIVE:
		acq_keepawive();
		wetuwn 0;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(WATCHDOG_HEAWTBEAT, p);

	defauwt:
		wetuwn -ENOTTY;
	}
}

static int acq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &acq_is_open))
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	/* Activate */
	acq_keepawive();
	wetuwn stweam_open(inode, fiwe);
}

static int acq_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42) {
		acq_stop();
	} ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		acq_keepawive();
	}
	cweaw_bit(0, &acq_is_open);
	expect_cwose = 0;
	wetuwn 0;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations acq_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= acq_wwite,
	.unwocked_ioctw	= acq_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= acq_open,
	.wewease	= acq_cwose,
};

static stwuct miscdevice acq_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &acq_fops,
};

/*
 *	Init & exit woutines
 */

static int __init acq_pwobe(stwuct pwatfowm_device *dev)
{
	int wet;

	if (wdt_stop != wdt_stawt) {
		if (!wequest_wegion(wdt_stop, 1, WATCHDOG_NAME)) {
			pw_eww("I/O addwess 0x%04x awweady in use\n", wdt_stop);
			wet = -EIO;
			goto out;
		}
	}

	if (!wequest_wegion(wdt_stawt, 1, WATCHDOG_NAME)) {
		pw_eww("I/O addwess 0x%04x awweady in use\n", wdt_stawt);
		wet = -EIO;
		goto unweg_stop;
	}
	wet = misc_wegistew(&acq_miscdev);
	if (wet != 0) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto unweg_wegions;
	}
	pw_info("initiawized. (nowayout=%d)\n", nowayout);

	wetuwn 0;
unweg_wegions:
	wewease_wegion(wdt_stawt, 1);
unweg_stop:
	if (wdt_stop != wdt_stawt)
		wewease_wegion(wdt_stop, 1);
out:
	wetuwn wet;
}

static void acq_wemove(stwuct pwatfowm_device *dev)
{
	misc_dewegistew(&acq_miscdev);
	wewease_wegion(wdt_stawt, 1);
	if (wdt_stop != wdt_stawt)
		wewease_wegion(wdt_stop, 1);
}

static void acq_shutdown(stwuct pwatfowm_device *dev)
{
	/* Tuwn the WDT off if we have a soft shutdown */
	acq_stop();
}

static stwuct pwatfowm_dwivew acquiwewdt_dwivew = {
	.wemove_new	= acq_wemove,
	.shutdown	= acq_shutdown,
	.dwivew		= {
		.name	= DWV_NAME,
	},
};

static int __init acq_init(void)
{
	int eww;

	pw_info("WDT dwivew fow Acquiwe singwe boawd computew initiawising\n");

	acq_pwatfowm_device = pwatfowm_device_wegistew_simpwe(DWV_NAME,
								-1, NUWW, 0);
	if (IS_EWW(acq_pwatfowm_device))
		wetuwn PTW_EWW(acq_pwatfowm_device);

	eww = pwatfowm_dwivew_pwobe(&acquiwewdt_dwivew, acq_pwobe);
	if (eww)
		goto unweg_pwatfowm_device;
	wetuwn 0;

unweg_pwatfowm_device:
	pwatfowm_device_unwegistew(acq_pwatfowm_device);
	wetuwn eww;
}

static void __exit acq_exit(void)
{
	pwatfowm_device_unwegistew(acq_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&acquiwewdt_dwivew);
	pw_info("Watchdog Moduwe Unwoaded\n");
}

moduwe_init(acq_init);
moduwe_exit(acq_exit);

MODUWE_AUTHOW("David Woodhouse");
MODUWE_DESCWIPTION("Acquiwe Inc. Singwe Boawd Computew Watchdog Timew dwivew");
MODUWE_WICENSE("GPW");
