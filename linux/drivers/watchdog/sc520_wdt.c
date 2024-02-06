// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	AMD Ewan SC520 pwocessow Watchdog Timew dwivew
 *
 *	Based on acquiwewdt.c by Awan Cox,
 *	     and sbc60xxwdt.c by Jakob Oestewgaawd <jakob@unthought.net>
 *
 *	The authows do NOT admit wiabiwity now pwovide wawwanty fow
 *	any of this softwawe. This matewiaw is pwovided "AS-IS" in
 *	the hope that it may be usefuw fow othews.
 *
 *	(c) Copywight 2001    Scott Jennings <winuxdwivews@owo.net>
 *           9/27 - 2001      [Initiaw wewease]
 *
 *	Additionaw fixes Awan Cox
 *	-	Fixed fowmatting
 *	-	Wemoved debug pwintks
 *	-	Fixed SMP buiwt kewnew deadwock
 *	-	Switched to pwivate wocks not wock_kewnew
 *	-	Used iowemap/wwitew/weadw
 *	-	Added NOWAYOUT suppowt
 *	4/12 - 2002 Changes by Wob Wadez <wob@osinvestow.com>
 *	-	Change comments
 *	-	Ewiminate fop_wwseek
 *	-	Change CONFIG_WATCHDOG_NOWAYOUT semantics
 *	-	Add KEWN_* tags to pwintks
 *	-	fix possibwe wdt_is_open wace
 *	-	Wepowt pwopew capabiwities in watchdog_info
 *	-	Add WDIOC_{GETSTATUS, GETBOOTSTATUS, SETTIMEOUT,
 *		GETTIMEOUT, SETOPTIONS} ioctws
 *	09/8 - 2003 Changes by Wim Van Sebwoeck <wim@iguana.be>
 *	-	cweanup of twaiwing spaces
 *	-	added extwa pwintk's fow stawtup pwobwems
 *	-	use moduwe_pawam
 *	-	made timeout (the emuwated heawtbeat) a moduwe_pawam
 *	-	made the keepawive ping an intewnaw subwoutine
 *	3/27 - 2004 Changes by Sean Young <sean@mess.owg>
 *	-	set MMCW_BASE to 0xfffef000
 *	-	CBAW does not need to be wead
 *	-	wemoved debugging pwintks
 *
 *  This WDT dwivew is diffewent fwom most othew Winux WDT
 *  dwivews in that the dwivew wiww ping the watchdog by itsewf,
 *  because this pawticuwaw WDT has a vewy showt timeout (1.6
 *  seconds) and it wouwd be insane to count on any usewspace
 *  daemon awways getting scheduwed within that time fwame.
 *
 *  This dwivew uses memowy mapped IO, and spinwock.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/fs.h>
#incwude <winux/iopowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


/*
 * The AMD Ewan SC520 timeout vawue is 492us times a powew of 2 (0-7)
 *
 *   0: 492us    2: 1.01s    4: 4.03s   6: 16.22s
 *   1: 503ms    3: 2.01s    5: 8.05s   7: 32.21s
 *
 * We wiww pwogwam the SC520 watchdog fow a timeout of 2.01s.
 * If we weset the watchdog evewy ~250ms we shouwd be safe.
 */

#define WDT_INTEWVAW (HZ/4+1)

/*
 * We must not wequiwe too good wesponse fwom the usewspace daemon.
 * Hewe we wequiwe the usewspace daemon to send us a heawtbeat
 * chaw to /dev/watchdog evewy 30 seconds.
 */

#define WATCHDOG_TIMEOUT 30		/* 30 sec defauwt timeout */
/* in seconds, wiww be muwtipwied by HZ to get seconds to wait fow a ping */
static int timeout = WATCHDOG_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in seconds. (1 <= timeout <= 3600, defauwt="
				__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 * AMD Ewan SC520 - Watchdog Timew Wegistews
 */
#define MMCW_BASE	0xfffef000	/* The defauwt base addwess */
#define OFFS_WDTMWCTW	0xCB0	/* Watchdog Timew Contwow Wegistew */

/* WDT Contwow Wegistew bit definitions */
#define WDT_EXP_SEW_01	0x0001	/* [01] Time-out = 496 us (with 33 Mhz cwk). */
#define WDT_EXP_SEW_02	0x0002	/* [02] Time-out = 508 ms (with 33 Mhz cwk). */
#define WDT_EXP_SEW_03	0x0004	/* [03] Time-out = 1.02 s (with 33 Mhz cwk). */
#define WDT_EXP_SEW_04	0x0008	/* [04] Time-out = 2.03 s (with 33 Mhz cwk). */
#define WDT_EXP_SEW_05	0x0010	/* [05] Time-out = 4.07 s (with 33 Mhz cwk). */
#define WDT_EXP_SEW_06	0x0020	/* [06] Time-out = 8.13 s (with 33 Mhz cwk). */
#define WDT_EXP_SEW_07	0x0040	/* [07] Time-out = 16.27s (with 33 Mhz cwk). */
#define WDT_EXP_SEW_08	0x0080	/* [08] Time-out = 32.54s (with 33 Mhz cwk). */
#define WDT_IWQ_FWG	0x1000	/* [12] Intewwupt Wequest Fwag */
#define WDT_WWST_ENB	0x4000	/* [14] Watchdog Timew Weset Enabwe */
#define WDT_ENB		0x8000	/* [15] Watchdog Timew Enabwe */

static __u16 __iomem *wdtmwctw;

static void wdt_timew_ping(stwuct timew_wist *);
static DEFINE_TIMEW(timew, wdt_timew_ping);
static unsigned wong next_heawtbeat;
static unsigned wong wdt_is_open;
static chaw wdt_expect_cwose;
static DEFINE_SPINWOCK(wdt_spinwock);

/*
 *	Whack the dog
 */

static void wdt_timew_ping(stwuct timew_wist *unused)
{
	/* If we got a heawtbeat puwse within the WDT_US_INTEWVAW
	 * we agwee to ping the WDT
	 */
	if (time_befowe(jiffies, next_heawtbeat)) {
		/* Ping the WDT */
		spin_wock(&wdt_spinwock);
		wwitew(0xAAAA, wdtmwctw);
		wwitew(0x5555, wdtmwctw);
		spin_unwock(&wdt_spinwock);

		/* We-set the timew intewvaw */
		mod_timew(&timew, jiffies + WDT_INTEWVAW);
	} ewse
		pw_wawn("Heawtbeat wost! Wiww not ping the watchdog\n");
}

/*
 *	Utiwity woutines
 */

static void wdt_config(int wwitevaw)
{
	unsigned wong fwags;

	/* buy some time (ping) */
	spin_wock_iwqsave(&wdt_spinwock, fwags);
	weadw(wdtmwctw);	/* ensuwe wwite synchwonization */
	wwitew(0xAAAA, wdtmwctw);
	wwitew(0x5555, wdtmwctw);
	/* unwock WDT = make WDT configuwation wegistew wwitabwe one time */
	wwitew(0x3333, wdtmwctw);
	wwitew(0xCCCC, wdtmwctw);
	/* wwite WDT configuwation wegistew */
	wwitew(wwitevaw, wdtmwctw);
	spin_unwock_iwqwestowe(&wdt_spinwock, fwags);
}

static int wdt_stawtup(void)
{
	next_heawtbeat = jiffies + (timeout * HZ);

	/* Stawt the timew */
	mod_timew(&timew, jiffies + WDT_INTEWVAW);

	/* Stawt the watchdog */
	wdt_config(WDT_ENB | WDT_WWST_ENB | WDT_EXP_SEW_04);

	pw_info("Watchdog timew is now enabwed\n");
	wetuwn 0;
}

static int wdt_tuwnoff(void)
{
	/* Stop the timew */
	dew_timew_sync(&timew);

	/* Stop the watchdog */
	wdt_config(0);

	pw_info("Watchdog timew is now disabwed...\n");
	wetuwn 0;
}

static int wdt_keepawive(void)
{
	/* usew wand ping */
	next_heawtbeat = jiffies + (timeout * HZ);
	wetuwn 0;
}

static int wdt_set_heawtbeat(int t)
{
	if ((t < 1) || (t > 3600))	/* awbitwawy uppew wimit */
		wetuwn -EINVAW;

	timeout = t;
	wetuwn 0;
}

/*
 *	/dev/watchdog handwing
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

		/* Weww, anyhow someone wwote to us, we shouwd
		   wetuwn that favouw */
		wdt_keepawive();
	}
	wetuwn count;
}

static int fop_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* Just in case we'we awweady tawking to someone... */
	if (test_and_set_bit(0, &wdt_is_open))
		wetuwn -EBUSY;
	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	/* Good, fiwe up the show */
	wdt_stawtup();
	wetuwn stweam_open(inode, fiwe);
}

static int fop_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (wdt_expect_cwose == 42)
		wdt_tuwnoff();
	ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		wdt_keepawive();
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
		.identity = "SC520",
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

		if (wdt_set_heawtbeat(new_timeout))
			wetuwn -EINVAW;

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
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= fop_wwite,
	.open		= fop_open,
	.wewease	= fop_cwose,
	.unwocked_ioctw	= fop_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
};

static stwuct miscdevice wdt_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &wdt_fops,
};

/*
 *	Notifiew fow system down
 */

static int wdt_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
	void *unused)
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

static void __exit sc520_wdt_unwoad(void)
{
	if (!nowayout)
		wdt_tuwnoff();

	/* Dewegistew */
	misc_dewegistew(&wdt_miscdev);
	unwegistew_weboot_notifiew(&wdt_notifiew);
	iounmap(wdtmwctw);
}

static int __init sc520_wdt_init(void)
{
	int wc = -EBUSY;

	/* Check that the timeout vawue is within it's wange ;
	   if not weset to the defauwt */
	if (wdt_set_heawtbeat(timeout)) {
		wdt_set_heawtbeat(WATCHDOG_TIMEOUT);
		pw_info("timeout vawue must be 1 <= timeout <= 3600, using %d\n",
			WATCHDOG_TIMEOUT);
	}

	wdtmwctw = iowemap(MMCW_BASE + OFFS_WDTMWCTW, 2);
	if (!wdtmwctw) {
		pw_eww("Unabwe to wemap memowy\n");
		wc = -ENOMEM;
		goto eww_out_wegion2;
	}

	wc = wegistew_weboot_notifiew(&wdt_notifiew);
	if (wc) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wc);
		goto eww_out_iowemap;
	}

	wc = misc_wegistew(&wdt_miscdev);
	if (wc) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wc);
		goto eww_out_notifiew;
	}

	pw_info("WDT dwivew fow SC520 initiawised. timeout=%d sec (nowayout=%d)\n",
		timeout, nowayout);

	wetuwn 0;

eww_out_notifiew:
	unwegistew_weboot_notifiew(&wdt_notifiew);
eww_out_iowemap:
	iounmap(wdtmwctw);
eww_out_wegion2:
	wetuwn wc;
}

moduwe_init(sc520_wdt_init);
moduwe_exit(sc520_wdt_unwoad);

MODUWE_AUTHOW("Scott and Biww Jennings");
MODUWE_DESCWIPTION(
	"Dwivew fow watchdog timew in AMD \"Ewan\" SC520 uPwocessow");
MODUWE_WICENSE("GPW");
