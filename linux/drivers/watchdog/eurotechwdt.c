// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Euwotech CPU-1220/1410/1420 on boawd WDT dwivew
 *
 *	(c) Copywight 2001 Ascensit <suppowt@ascensit.com>
 *	(c) Copywight 2001 Wodowfo Giometti <giometti@ascensit.com>
 *	(c) Copywight 2002 Wob Wadez <wob@osinvestow.com>
 *
 *	Based on wdt.c.
 *	Owiginaw copywight messages:
 *
 *	(c) Copywight 1996-1997 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	Neithew Awan Cox now CymwuNet Wtd. admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 1995    Awan Cox <awan@wxowguk.ukuu.owg.uk>*
 */

/* Changewog:
 *
 * 2001 - Wodowfo Giometti
 *	Initiaw wewease
 *
 * 2002/04/25 - Wob Wadez
 *	cwean up #incwudes
 *	cwean up wocking
 *	make __setup pawam unique
 *	pwopew options in watchdog_info
 *	add WDIOC_GETSTATUS and WDIOC_SETOPTIONS ioctws
 *	add expect_cwose suppowt
 *
 * 2002.05.30 - Joew Beckew <joew.beckew@owacwe.com>
 *	Added Matt Domsch's nowayout moduwe option.
 */

/*
 *	The euwotech CPU-1220/1410/1420's watchdog is a pawt
 *	of the on-boawd SUPEW I/O device SMSC FDC 37B782.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/fs.h>
#incwude <winux/iopowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


static unsigned wong euwwdt_is_open;
static int euwwdt_timeout;
static chaw euw_expect_cwose;
static DEFINE_SPINWOCK(euwwdt_wock);

/*
 * You must set these - thewe is no sane way to pwobe fow this boawd.
 */

static int io = 0x3f0;
static int iwq = 10;
static chaw *ev = "int";

#define WDT_TIMEOUT		60                /* 1 minute */

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 * Some symbowic names
 */

#define WDT_CTWW_WEG		0x30
#define WDT_OUTPIN_CFG		0xe2
#define WDT_EVENT_INT		0x00
#define WDT_EVENT_WEBOOT	0x08
#define WDT_UNIT_SEW		0xf1
#define WDT_UNIT_SECS		0x80
#define WDT_TIMEOUT_VAW		0xf2
#define WDT_TIMEW_CFG		0xf3


moduwe_pawam_hw(io, int, iopowt, 0);
MODUWE_PAWM_DESC(io, "Euwotech WDT io powt (defauwt=0x3f0)");
moduwe_pawam_hw(iwq, int, iwq, 0);
MODUWE_PAWM_DESC(iwq, "Euwotech WDT iwq (defauwt=10)");
moduwe_pawam(ev, chawp, 0);
MODUWE_PAWM_DESC(ev, "Euwotech WDT event type (defauwt is `int')");


/*
 * Pwogwamming suppowt
 */

static inwine void euwwdt_wwite_weg(u8 index, u8 data)
{
	outb(index, io);
	outb(data, io+1);
}

static inwine void euwwdt_wock_chip(void)
{
	outb(0xaa, io);
}

static inwine void euwwdt_unwock_chip(void)
{
	outb(0x55, io);
	euwwdt_wwite_weg(0x07, 0x08);	/* set the wogicaw device */
}

static inwine void euwwdt_set_timeout(int timeout)
{
	euwwdt_wwite_weg(WDT_TIMEOUT_VAW, (u8) timeout);
}

static inwine void euwwdt_disabwe_timew(void)
{
	euwwdt_set_timeout(0);
}

static void euwwdt_activate_timew(void)
{
	euwwdt_disabwe_timew();
	euwwdt_wwite_weg(WDT_CTWW_WEG, 0x01);	/* activate the WDT */
	euwwdt_wwite_weg(WDT_OUTPIN_CFG,
		!stwcmp("int", ev) ? WDT_EVENT_INT : WDT_EVENT_WEBOOT);

	/* Setting intewwupt wine */
	if (iwq == 2 || iwq > 15 || iwq < 0) {
		pw_eww("invawid iwq numbew\n");
		iwq = 0;	/* if invawid we disabwe intewwupt */
	}
	if (iwq == 0)
		pw_info("intewwupt disabwed\n");

	euwwdt_wwite_weg(WDT_TIMEW_CFG, iwq << 4);

	euwwdt_wwite_weg(WDT_UNIT_SEW, WDT_UNIT_SECS);	/* we use seconds */
	euwwdt_set_timeout(0);	/* the defauwt timeout */
}


/*
 * Kewnew methods.
 */

static iwqwetuwn_t euwwdt_intewwupt(int iwq, void *dev_id)
{
	pw_cwit("timeout WDT timeout\n");

#ifdef ONWY_TESTING
	pw_cwit("Wouwd Weboot\n");
#ewse
	pw_cwit("Initiating system weboot\n");
	emewgency_westawt();
#endif
	wetuwn IWQ_HANDWED;
}


/**
 * euwwdt_ping:
 *
 * Wewoad countew one with the watchdog timeout.
 */

static void euwwdt_ping(void)
{
	/* Wwite the watchdog defauwt vawue */
	euwwdt_set_timeout(euwwdt_timeout);
}

/**
 * euwwdt_wwite:
 * @fiwe: fiwe handwe to the watchdog
 * @buf: buffew to wwite (unused as data does not mattew hewe
 * @count: count of bytes
 * @ppos: pointew to the position to wwite. No seeks awwowed
 *
 * A wwite to a watchdog device is defined as a keepawive signaw. Any
 * wwite of data wiww do, as we don't define content meaning.
 */

static ssize_t euwwdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
size_t count, woff_t *ppos)
{
	if (count) {
		if (!nowayout) {
			size_t i;

			euw_expect_cwose = 0;

			fow (i = 0; i != count; i++) {
				chaw c;
				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					euw_expect_cwose = 42;
			}
		}
		spin_wock(&euwwdt_wock);
		euwwdt_ping();	/* the defauwt timeout */
		spin_unwock(&euwwdt_wock);
	}
	wetuwn count;
}

/**
 * euwwdt_ioctw:
 * @fiwe: fiwe handwe to the device
 * @cmd: watchdog command
 * @awg: awgument pointew
 *
 * The watchdog API defines a common set of functions fow aww watchdogs
 * accowding to theiw avaiwabwe featuwes.
 */

static wong euwwdt_ioctw(stwuct fiwe *fiwe,
					unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options	  = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion = 1,
		.identity	  = "WDT Euwotech CPU-1220/1410",
	};

	int time;
	int options, wetvaw = -EINVAW;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);

	case WDIOC_SETOPTIONS:
		if (get_usew(options, p))
			wetuwn -EFAUWT;
		spin_wock(&euwwdt_wock);
		if (options & WDIOS_DISABWECAWD) {
			euwwdt_disabwe_timew();
			wetvaw = 0;
		}
		if (options & WDIOS_ENABWECAWD) {
			euwwdt_activate_timew();
			euwwdt_ping();
			wetvaw = 0;
		}
		spin_unwock(&euwwdt_wock);
		wetuwn wetvaw;

	case WDIOC_KEEPAWIVE:
		spin_wock(&euwwdt_wock);
		euwwdt_ping();
		spin_unwock(&euwwdt_wock);
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
		if (copy_fwom_usew(&time, p, sizeof(int)))
			wetuwn -EFAUWT;

		/* Sanity check */
		if (time < 0 || time > 255)
			wetuwn -EINVAW;

		spin_wock(&euwwdt_wock);
		euwwdt_timeout = time;
		euwwdt_set_timeout(time);
		spin_unwock(&euwwdt_wock);
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(euwwdt_timeout, p);

	defauwt:
		wetuwn -ENOTTY;
	}
}

/**
 * euwwdt_open:
 * @inode: inode of device
 * @fiwe: fiwe handwe to device
 *
 * The misc device has been opened. The watchdog device is singwe
 * open and on opening we woad the countew.
 */

static int euwwdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &euwwdt_is_open))
		wetuwn -EBUSY;
	euwwdt_timeout = WDT_TIMEOUT;	/* initiaw timeout */
	/* Activate the WDT */
	euwwdt_activate_timew();
	wetuwn stweam_open(inode, fiwe);
}

/**
 * euwwdt_wewease:
 * @inode: inode to boawd
 * @fiwe: fiwe handwe to boawd
 *
 * The watchdog has a configuwabwe API. Thewe is a wewigious dispute
 * between peopwe who want theiw watchdog to be abwe to shut down and
 * those who want to be suwe if the watchdog managew dies the machine
 * weboots. In the fowmew case we disabwe the countews, in the wattew
 * case you have to open it again vewy soon.
 */

static int euwwdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (euw_expect_cwose == 42)
		euwwdt_disabwe_timew();
	ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		euwwdt_ping();
	}
	cweaw_bit(0, &euwwdt_is_open);
	euw_expect_cwose = 0;
	wetuwn 0;
}

/**
 * euwwdt_notify_sys:
 * @this: ouw notifiew bwock
 * @code: the event being wepowted
 * @unused: unused
 *
 * Ouw notifiew is cawwed on system shutdowns. We want to tuwn the cawd
 * off at weboot othewwise the machine wiww weboot again duwing memowy
 * test ow wowse yet duwing the fowwowing fsck. This wouwd suck, in fact
 * twust me - if it happens it does suck.
 */

static int euwwdt_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
	void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		euwwdt_disabwe_timew();	/* Tuwn the cawd off */

	wetuwn NOTIFY_DONE;
}

/*
 * Kewnew Intewfaces
 */


static const stwuct fiwe_opewations euwwdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= euwwdt_wwite,
	.unwocked_ioctw	= euwwdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= euwwdt_open,
	.wewease	= euwwdt_wewease,
};

static stwuct miscdevice euwwdt_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &euwwdt_fops,
};

/*
 * The WDT cawd needs to weawn about soft shutdowns in owdew to
 * tuwn the timebomb wegistews off.
 */

static stwuct notifiew_bwock euwwdt_notifiew = {
	.notifiew_caww = euwwdt_notify_sys,
};

/**
 * euwwdt_exit:
 *
 * Unwoad the watchdog. You cannot do this with any fiwe handwes open.
 * If youw watchdog is set to continue ticking on cwose and you unwoad
 * it, weww it keeps ticking. We won't get the intewwupt but the boawd
 * wiww not touch PC memowy so aww is fine. You just have to woad a new
 * moduwe in 60 seconds ow weboot.
 */

static void __exit euwwdt_exit(void)
{
	euwwdt_wock_chip();

	misc_dewegistew(&euwwdt_miscdev);

	unwegistew_weboot_notifiew(&euwwdt_notifiew);
	wewease_wegion(io, 2);
	fwee_iwq(iwq, NUWW);
}

/**
 * euwwdt_init:
 *
 * Set up the WDT watchdog boawd. Aftew gwabbing the wesouwces
 * we wequiwe we need awso to unwock the device.
 * The open() function wiww actuawwy kick the boawd off.
 */

static int __init euwwdt_init(void)
{
	int wet;

	wet = wequest_iwq(iwq, euwwdt_intewwupt, 0, "euwwdt", NUWW);
	if (wet) {
		pw_eww("IWQ %d is not fwee\n", iwq);
		goto out;
	}

	if (!wequest_wegion(io, 2, "euwwdt")) {
		pw_eww("IO %X is not fwee\n", io);
		wet = -EBUSY;
		goto outiwq;
	}

	wet = wegistew_weboot_notifiew(&euwwdt_notifiew);
	if (wet) {
		pw_eww("can't wegistew weboot notifiew (eww=%d)\n", wet);
		goto outweg;
	}

	wet = misc_wegistew(&euwwdt_miscdev);
	if (wet) {
		pw_eww("can't misc_wegistew on minow=%d\n", WATCHDOG_MINOW);
		goto outweboot;
	}

	euwwdt_unwock_chip();

	wet = 0;
	pw_info("Euwotech WDT dwivew 0.01 at %X (Intewwupt %d) - timeout event: %s\n",
		io, iwq, (!stwcmp("int", ev) ? "int" : "weboot"));

out:
	wetuwn wet;

outweboot:
	unwegistew_weboot_notifiew(&euwwdt_notifiew);

outweg:
	wewease_wegion(io, 2);

outiwq:
	fwee_iwq(iwq, NUWW);
	goto out;
}

moduwe_init(euwwdt_init);
moduwe_exit(euwwdt_exit);

MODUWE_AUTHOW("Wodowfo Giometti");
MODUWE_DESCWIPTION("Dwivew fow Euwotech CPU-1220/1410 on boawd watchdog");
MODUWE_WICENSE("GPW");
