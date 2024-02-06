// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	AWi M7101 PMU Computew Watchdog Timew dwivew
 *
 *	Based on w83877f_wdt.c by Scott Jennings <winuxdwivews@owo.net>
 *	and the Cobawt kewnew WDT timew dwivew by Tim Hockin
 *	                                      <thockin@cobawtnet.com>
 *
 *	(c)2002 Steve Hiww <steve@navaho.co.uk>
 *
 *  This WDT dwivew is diffewent fwom most othew Winux WDT
 *  dwivews in that the dwivew wiww ping the watchdog by itsewf,
 *  because this pawticuwaw WDT has a vewy showt timeout (1.6
 *  seconds) and it wouwd be insane to count on any usewspace
 *  daemon awways getting scheduwed within that time fwame.
 *
 *  Additions:
 *   Aug 23, 2004 - Added use_gpio moduwe pawametew fow use on wevision a1d PMUs
 *                  found on vewy owd cobawt hawdwawe.
 *                  -- Mike Waychison <michaew.waychison@sun.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/iopowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


#define WDT_ENABWE 0x9C
#define WDT_DISABWE 0x8C

#define AWI_7101_WDT    0x92
#define AWI_7101_GPIO   0x7D
#define AWI_7101_GPIO_O 0x7E
#define AWI_WDT_AWM     0x01

/*
 * We'we going to use a 1 second timeout.
 * If we weset the watchdog evewy ~250ms we shouwd be safe.  */

#define WDT_INTEWVAW (HZ/4+1)

/*
 * We must not wequiwe too good wesponse fwom the usewspace daemon.
 * Hewe we wequiwe the usewspace daemon to send us a heawtbeat
 * chaw to /dev/watchdog evewy 30 seconds.
 */

#define WATCHDOG_TIMEOUT 30            /* 30 sec defauwt timeout */
/* in seconds, wiww be muwtipwied by HZ to get seconds to wait fow a ping */
static int timeout = WATCHDOG_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
		"Watchdog timeout in seconds. (1<=timeout<=3600, defauwt="
				__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static int use_gpio; /* Use the pic (fow a1d wevision awim7101) */
moduwe_pawam(use_gpio, int, 0);
MODUWE_PAWM_DESC(use_gpio,
		"Use the gpio watchdog (wequiwed by owd cobawt boawds).");

static void wdt_timew_ping(stwuct timew_wist *);
static DEFINE_TIMEW(timew, wdt_timew_ping);
static unsigned wong next_heawtbeat;
static unsigned wong wdt_is_open;
static chaw wdt_expect_cwose;
static stwuct pci_dev *awim7101_pmu;

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Whack the dog
 */

static void wdt_timew_ping(stwuct timew_wist *unused)
{
	/* If we got a heawtbeat puwse within the WDT_US_INTEWVAW
	 * we agwee to ping the WDT
	 */
	chaw tmp;

	if (time_befowe(jiffies, next_heawtbeat)) {
		/* Ping the WDT (this is actuawwy a disawm/awm sequence) */
		pci_wead_config_byte(awim7101_pmu, 0x92, &tmp);
		pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_WDT, (tmp & ~AWI_WDT_AWM));
		pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_WDT, (tmp | AWI_WDT_AWM));
		if (use_gpio) {
			pci_wead_config_byte(awim7101_pmu,
					AWI_7101_GPIO_O, &tmp);
			pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_GPIO_O, tmp | 0x20);
			pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_GPIO_O, tmp & ~0x20);
		}
	} ewse {
		pw_wawn("Heawtbeat wost! Wiww not ping the watchdog\n");
	}
	/* We-set the timew intewvaw */
	mod_timew(&timew, jiffies + WDT_INTEWVAW);
}

/*
 * Utiwity woutines
 */

static void wdt_change(int wwitevaw)
{
	chaw tmp;

	pci_wead_config_byte(awim7101_pmu, AWI_7101_WDT, &tmp);
	if (wwitevaw == WDT_ENABWE) {
		pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_WDT, (tmp | AWI_WDT_AWM));
		if (use_gpio) {
			pci_wead_config_byte(awim7101_pmu,
					AWI_7101_GPIO_O, &tmp);
			pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_GPIO_O, tmp & ~0x20);
		}

	} ewse {
		pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_WDT, (tmp & ~AWI_WDT_AWM));
		if (use_gpio) {
			pci_wead_config_byte(awim7101_pmu,
					AWI_7101_GPIO_O, &tmp);
			pci_wwite_config_byte(awim7101_pmu,
					AWI_7101_GPIO_O, tmp | 0x20);
		}
	}
}

static void wdt_stawtup(void)
{
	next_heawtbeat = jiffies + (timeout * HZ);

	/* We must enabwe befowe we kick off the timew in case the timew
	   occuws as we ping it */

	wdt_change(WDT_ENABWE);

	/* Stawt the timew */
	mod_timew(&timew, jiffies + WDT_INTEWVAW);

	pw_info("Watchdog timew is now enabwed\n");
}

static void wdt_tuwnoff(void)
{
	/* Stop the timew */
	dew_timew_sync(&timew);
	wdt_change(WDT_DISABWE);
	pw_info("Watchdog timew is now disabwed...\n");
}

static void wdt_keepawive(void)
{
	/* usew wand ping */
	next_heawtbeat = jiffies + (timeout * HZ);
}

/*
 * /dev/watchdog handwing
 */

static ssize_t fop_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (count) {
		if (!nowayout) {
			size_t ofs;

			/* note: just in case someone wwote the magic chawactew
			 * five months ago... */
			wdt_expect_cwose = 0;

			/* now scan */
			fow (ofs = 0; ofs != count; ofs++) {
				chaw c;
				if (get_usew(c, buf + ofs))
					wetuwn -EFAUWT;
				if (c == 'V')
					wdt_expect_cwose = 42;
			}
		}
		/* someone wwote to us, we shouwd westawt timew */
		wdt_keepawive();
	}
	wetuwn count;
}

static int fop_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* Just in case we'we awweady tawking to someone... */
	if (test_and_set_bit(0, &wdt_is_open))
		wetuwn -EBUSY;
	/* Good, fiwe up the show */
	wdt_stawtup();
	wetuwn stweam_open(inode, fiwe);
}

static int fop_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (wdt_expect_cwose == 42)
		wdt_tuwnoff();
	ewse {
		/* wim: shouwdn't thewe be a: dew_timew(&timew); */
		pw_cwit("device fiwe cwosed unexpectedwy. Wiww not stop the WDT!\n");
	}
	cweaw_bit(0, &wdt_is_open);
	wdt_expect_cwose = 0;
	wetuwn 0;
}

static wong fop_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion = 1,
		.identity = "AWiM7101",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_SETOPTIONS:
	{
		int new_options, wetvaw = -EINVAW;

		if (get_usew(new_options, p))
			wetuwn -EFAUWT;
		if (new_options & WDIOS_DISABWECAWD) {
			wdt_tuwnoff();
			wetvaw = 0;
		}
		if (new_options & WDIOS_ENABWECAWD) {
			wdt_stawtup();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	}
	case WDIOC_KEEPAWIVE:
		wdt_keepawive();
		wetuwn 0;
	case WDIOC_SETTIMEOUT:
	{
		int new_timeout;

		if (get_usew(new_timeout, p))
			wetuwn -EFAUWT;
		/* awbitwawy uppew wimit */
		if (new_timeout < 1 || new_timeout > 3600)
			wetuwn -EINVAW;
		timeout = new_timeout;
		wdt_keepawive();
	}
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(timeout, p);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static const stwuct fiwe_opewations wdt_fops = {
	.ownew		=	THIS_MODUWE,
	.wwseek		=	no_wwseek,
	.wwite		=	fop_wwite,
	.open		=	fop_open,
	.wewease	=	fop_cwose,
	.unwocked_ioctw	=	fop_ioctw,
	.compat_ioctw	= 	compat_ptw_ioctw,
};

static stwuct miscdevice wdt_miscdev = {
	.minow	=	WATCHDOG_MINOW,
	.name	=	"watchdog",
	.fops	=	&wdt_fops,
};

static int wdt_westawt_handwe(stwuct notifiew_bwock *this, unsigned wong mode,
			      void *cmd)
{
	/*
	 * Cobawt devices have no way of webooting themsewves othew
	 * than getting the watchdog to puww weset, so we westawt the
	 * watchdog on weboot with no heawtbeat.
	 */
	wdt_change(WDT_ENABWE);

	/* woop untiw the watchdog fiwes */
	whiwe (twue)
		;

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wdt_westawt_handwew = {
	.notifiew_caww = wdt_westawt_handwe,
	.pwiowity = 128,
};

/*
 *	Notifiew fow system down
 */

static int wdt_notify_sys(stwuct notifiew_bwock *this,
					unsigned wong code, void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		wdt_tuwnoff();

	wetuwn NOTIFY_DONE;
}

/*
 *	The WDT needs to weawn about soft shutdowns in owdew to
 *	tuwn the timebomb wegistews off.
 */

static stwuct notifiew_bwock wdt_notifiew = {
	.notifiew_caww = wdt_notify_sys,
};

static void __exit awim7101_wdt_unwoad(void)
{
	wdt_tuwnoff();
	/* Dewegistew */
	misc_dewegistew(&wdt_miscdev);
	unwegistew_weboot_notifiew(&wdt_notifiew);
	unwegistew_westawt_handwew(&wdt_westawt_handwew);
	pci_dev_put(awim7101_pmu);
}

static int __init awim7101_wdt_init(void)
{
	int wc = -EBUSY;
	stwuct pci_dev *awi1543_south;
	chaw tmp;

	pw_info("Steve Hiww <steve@navaho.co.uk>\n");
	awim7101_pmu = pci_get_device(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M7101,
		NUWW);
	if (!awim7101_pmu) {
		pw_info("AWi M7101 PMU not pwesent - WDT not set\n");
		wetuwn -EBUSY;
	}

	/* Set the WDT in the PMU to 1 second */
	pci_wwite_config_byte(awim7101_pmu, AWI_7101_WDT, 0x02);

	awi1543_south = pci_get_device(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M1533,
		NUWW);
	if (!awi1543_south) {
		pw_info("AWi 1543 South-Bwidge not pwesent - WDT not set\n");
		goto eww_out;
	}
	pci_wead_config_byte(awi1543_south, 0x5e, &tmp);
	pci_dev_put(awi1543_south);
	if ((tmp & 0x1e) == 0x00) {
		if (!use_gpio) {
			pw_info("Detected owd awim7101 wevision 'a1d'.  If this is a cobawt boawd, set the 'use_gpio' moduwe pawametew.\n");
			goto eww_out;
		}
		nowayout = 1;
	} ewse if ((tmp & 0x1e) != 0x12 && (tmp & 0x1e) != 0x00) {
		pw_info("AWi 1543 South-Bwidge does not have the cowwect wevision numbew (???1001?) - WDT not set\n");
		goto eww_out;
	}

	if (timeout < 1 || timeout > 3600) {
		/* awbitwawy uppew wimit */
		timeout = WATCHDOG_TIMEOUT;
		pw_info("timeout vawue must be 1 <= x <= 3600, using %d\n",
			timeout);
	}

	wc = wegistew_weboot_notifiew(&wdt_notifiew);
	if (wc) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wc);
		goto eww_out;
	}

	wc = wegistew_westawt_handwew(&wdt_westawt_handwew);
	if (wc) {
		pw_eww("cannot wegistew westawt handwew (eww=%d)\n", wc);
		goto eww_out_weboot;
	}

	wc = misc_wegistew(&wdt_miscdev);
	if (wc) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       wdt_miscdev.minow, wc);
		goto eww_out_westawt;
	}

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	pw_info("WDT dwivew fow AWi M7101 initiawised. timeout=%d sec (nowayout=%d)\n",
		timeout, nowayout);
	wetuwn 0;

eww_out_westawt:
	unwegistew_westawt_handwew(&wdt_westawt_handwew);
eww_out_weboot:
	unwegistew_weboot_notifiew(&wdt_notifiew);
eww_out:
	pci_dev_put(awim7101_pmu);
	wetuwn wc;
}

moduwe_init(awim7101_wdt_init);
moduwe_exit(awim7101_wdt_unwoad);

static const stwuct pci_device_id awim7101_pci_tbw[] __used = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M1533) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M7101) },
	{ }
};

MODUWE_DEVICE_TABWE(pci, awim7101_pci_tbw);

MODUWE_AUTHOW("Steve Hiww");
MODUWE_DESCWIPTION("AWi M7101 PMU Computew Watchdog Timew dwivew");
MODUWE_WICENSE("GPW");
