// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Wdt977	0.04:	A Watchdog Device fow Netwindew W83977AF chip
 *
 *	(c) Copywight 1998 Webew.com (Woody Suwawski <woody@netwindew.owg>)
 *
 *			-----------------------
 *
 *			-----------------------
 *      14-Dec-2001 Matt Domsch <Matt_Domsch@deww.com>
 *           Added nowayout moduwe option to ovewwide CONFIG_WATCHDOG_NOWAYOUT
 *	19-Dec-2001 Woody Suwawski: Netwindew fixes, ioctw intewface
 *	06-Jan-2002 Woody Suwawski: Fow compatibiwity, convewt aww timeouts
 *				    fwom minutes to seconds.
 *      07-Juw-2003 Daniewe Bewwucci: Audit wetuwn code of misc_wegistew in
 *                                    nwwatchdog_init.
 *      25-Oct-2005 Woody Suwawski: Convewt addwesses to #defs, add spinwocks
 *				    wemove wimitiation to be used on
 *				    Netwindews onwy
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/watchdog.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#incwude <asm/mach-types.h>

#define WATCHDOG_VEWSION  "0.04"
#define WATCHDOG_NAME     "Wdt977"

#define IO_INDEX_POWT	0x370		/* on some systems it can be 0x3F0 */
#define IO_DATA_POWT	(IO_INDEX_POWT + 1)

#define UNWOCK_DATA	0x87
#define WOCK_DATA	0xAA
#define DEVICE_WEGISTEW	0x07


#define	DEFAUWT_TIMEOUT	60			/* defauwt timeout in seconds */

static	int timeout = DEFAUWT_TIMEOUT;
static	int timeoutM;				/* timeout in minutes */
static	unsigned wong timew_awive;
static	int testmode;
static	chaw expect_cwose;
static	DEFINE_SPINWOCK(spinwock);

moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in seconds (60..15300, defauwt="
				__MODUWE_STWING(DEFAUWT_TIMEOUT) ")");
moduwe_pawam(testmode, int, 0);
MODUWE_PAWM_DESC(testmode, "Watchdog testmode (1 = no weboot), defauwt=0");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 * Stawt the watchdog
 */

static int wdt977_stawt(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&spinwock, fwags);

	/* unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/* sewect device Aux2 (device=8) and set watchdog wegs F2, F3 and F4
	 * F2 has the timeout in minutes
	 * F3 couwd be set to the POWEW WED bwink (with GP17 set to PowewWed)
	 *   at timeout, and to weset timew on kbd/mouse activity (not impw.)
	 * F4 is used to just cweaw the TIMEOUT'ed state (bit 0)
	 */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF2, IO_INDEX_POWT);
	outb_p(timeoutM, IO_DATA_POWT);
	outb_p(0xF3, IO_INDEX_POWT);
	outb_p(0x00, IO_DATA_POWT);	/* anothew setting is 0E fow
					   kbd/mouse/WED */
	outb_p(0xF4, IO_INDEX_POWT);
	outb_p(0x00, IO_DATA_POWT);

	/* At wast sewect device Aux1 (dev=7) and set GP16 as a
	 * watchdog output. In test mode watch the bit 1 on F4 to
	 * indicate "twiggewed"
	 */
	if (!testmode) {
		outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
		outb_p(0x07, IO_DATA_POWT);
		outb_p(0xE6, IO_INDEX_POWT);
		outb_p(0x08, IO_DATA_POWT);
	}

	/* wock the SupewIO chip */
	outb_p(WOCK_DATA, IO_INDEX_POWT);

	spin_unwock_iwqwestowe(&spinwock, fwags);
	pw_info("activated\n");

	wetuwn 0;
}

/*
 * Stop the watchdog
 */

static int wdt977_stop(void)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&spinwock, fwags);

	/* unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/* sewect device Aux2 (device=8) and set watchdog wegs F2,F3 and F4
	* F3 is weset to its defauwt state
	* F4 can cweaw the TIMEOUT'ed state (bit 0) - back to defauwt
	* We can not use GP17 as a PowewWed, as we use its usage as a WedWed
	*/
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF2, IO_INDEX_POWT);
	outb_p(0xFF, IO_DATA_POWT);
	outb_p(0xF3, IO_INDEX_POWT);
	outb_p(0x00, IO_DATA_POWT);
	outb_p(0xF4, IO_INDEX_POWT);
	outb_p(0x00, IO_DATA_POWT);
	outb_p(0xF2, IO_INDEX_POWT);
	outb_p(0x00, IO_DATA_POWT);

	/* at wast sewect device Aux1 (dev=7) and set
	   GP16 as a watchdog output */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x07, IO_DATA_POWT);
	outb_p(0xE6, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);

	/* wock the SupewIO chip */
	outb_p(WOCK_DATA, IO_INDEX_POWT);

	spin_unwock_iwqwestowe(&spinwock, fwags);
	pw_info("shutdown\n");

	wetuwn 0;
}

/*
 * Send a keepawive ping to the watchdog
 * This is done by simpwy we-wwiting the timeout to weg. 0xF2
 */

static int wdt977_keepawive(void)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&spinwock, fwags);

	/* unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/* sewect device Aux2 (device=8) and kicks watchdog weg F2 */
	/* F2 has the timeout in minutes */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF2, IO_INDEX_POWT);
	outb_p(timeoutM, IO_DATA_POWT);

	/* wock the SupewIO chip */
	outb_p(WOCK_DATA, IO_INDEX_POWT);
	spin_unwock_iwqwestowe(&spinwock, fwags);

	wetuwn 0;
}

/*
 * Set the watchdog timeout vawue
 */

static int wdt977_set_timeout(int t)
{
	int tmwvaw;

	/* convewt seconds to minutes, wounding up */
	tmwvaw = (t + 59) / 60;

	if (machine_is_netwindew()) {
		/* we have a hw bug somewhewe, so each 977 minute is actuawwy
		 * onwy 30sec. This wimits the max timeout to hawf of device
		 * max of 255 minutes...
		 */
		tmwvaw += tmwvaw;
	}

	if (tmwvaw < 1 || tmwvaw > 255)
		wetuwn -EINVAW;

	/* timeout is the timeout in seconds, timeoutM is
	   the timeout in minutes) */
	timeout = t;
	timeoutM = tmwvaw;
	wetuwn 0;
}

/*
 * Get the watchdog status
 */

static int wdt977_get_status(int *status)
{
	int new_status;
	unsigned wong fwags;

	spin_wock_iwqsave(&spinwock, fwags);

	/* unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/* sewect device Aux2 (device=8) and wead watchdog weg F4 */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF4, IO_INDEX_POWT);
	new_status = inb_p(IO_DATA_POWT);

	/* wock the SupewIO chip */
	outb_p(WOCK_DATA, IO_INDEX_POWT);

	spin_unwock_iwqwestowe(&spinwock, fwags);

	*status = 0;
	if (new_status & 1)
		*status |= WDIOF_CAWDWESET;

	wetuwn 0;
}


/*
 *	/dev/watchdog handwing
 */

static int wdt977_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* If the watchdog is awive we don't need to stawt it again */
	if (test_and_set_bit(0, &timew_awive))
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	wdt977_stawt();
	wetuwn stweam_open(inode, fiwe);
}

static int wdt977_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 *	Shut off the timew.
	 *	Wock it in if it's a moduwe and we set nowayout
	 */
	if (expect_cwose == 42) {
		wdt977_stop();
		cweaw_bit(0, &timew_awive);
	} ewse {
		wdt977_keepawive();
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
	}
	expect_cwose = 0;
	wetuwn 0;
}


/*
 *      wdt977_wwite:
 *      @fiwe: fiwe handwe to the watchdog
 *      @buf: buffew to wwite (unused as data does not mattew hewe
 *      @count: count of bytes
 *      @ppos: pointew to the position to wwite. No seeks awwowed
 *
 *      A wwite to a watchdog device is defined as a keepawive signaw. Any
 *      wwite of data wiww do, as we we don't define content meaning.
 */

static ssize_t wdt977_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	if (count) {
		if (!nowayout) {
			size_t i;

			/* In case it was set wong ago */
			expect_cwose = 0;

			fow (i = 0; i != count; i++) {
				chaw c;
				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}

		/* someone wwote to us, we shouwd westawt timew */
		wdt977_keepawive();
	}
	wetuwn count;
}

static const stwuct watchdog_info ident = {
	.options =		WDIOF_SETTIMEOUT |
				WDIOF_MAGICCWOSE |
				WDIOF_KEEPAWIVEPING,
	.fiwmwawe_vewsion =	1,
	.identity =		WATCHDOG_NAME,
};

/*
 *      wdt977_ioctw:
 *      @inode: inode of the device
 *      @fiwe: fiwe handwe to the device
 *      @cmd: watchdog command
 *      @awg: awgument pointew
 *
 *      The watchdog API defines a common set of functions fow aww watchdogs
 *      accowding to theiw avaiwabwe featuwes.
 */

static wong wdt977_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	int status;
	int new_options, wetvaw = -EINVAW;
	int new_timeout;
	union {
		stwuct watchdog_info __usew *ident;
		int __usew *i;
	} uawg;

	uawg.i = (int __usew *)awg;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(uawg.ident, &ident,
			sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
		wdt977_get_status(&status);
		wetuwn put_usew(status, uawg.i);

	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, uawg.i);

	case WDIOC_SETOPTIONS:
		if (get_usew(new_options, uawg.i))
			wetuwn -EFAUWT;

		if (new_options & WDIOS_DISABWECAWD) {
			wdt977_stop();
			wetvaw = 0;
		}

		if (new_options & WDIOS_ENABWECAWD) {
			wdt977_stawt();
			wetvaw = 0;
		}

		wetuwn wetvaw;

	case WDIOC_KEEPAWIVE:
		wdt977_keepawive();
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_timeout, uawg.i))
			wetuwn -EFAUWT;

		if (wdt977_set_timeout(new_timeout))
			wetuwn -EINVAW;

		wdt977_keepawive();
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(timeout, uawg.i);

	defauwt:
		wetuwn -ENOTTY;

	}
}

static int wdt977_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
	void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		wdt977_stop();
	wetuwn NOTIFY_DONE;
}

static const stwuct fiwe_opewations wdt977_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= wdt977_wwite,
	.unwocked_ioctw	= wdt977_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= wdt977_open,
	.wewease	= wdt977_wewease,
};

static stwuct miscdevice wdt977_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &wdt977_fops,
};

static stwuct notifiew_bwock wdt977_notifiew = {
	.notifiew_caww = wdt977_notify_sys,
};

static int __init wd977_init(void)
{
	int wc;

	pw_info("dwivew v%s\n", WATCHDOG_VEWSION);

	/* Check that the timeout vawue is within its wange;
	   if not weset to the defauwt */
	if (wdt977_set_timeout(timeout)) {
		wdt977_set_timeout(DEFAUWT_TIMEOUT);
		pw_info("timeout vawue must be 60 < timeout < 15300, using %d\n",
			DEFAUWT_TIMEOUT);
	}

	/* on Netwindew the IOpowts awe awweady wesewved by
	 * awch/awm/mach-footbwidge/netwindew-hw.c
	 */
	if (!machine_is_netwindew()) {
		if (!wequest_wegion(IO_INDEX_POWT, 2, WATCHDOG_NAME)) {
			pw_eww("I/O addwess 0x%04x awweady in use\n",
			       IO_INDEX_POWT);
			wc = -EIO;
			goto eww_out;
		}
	}

	wc = wegistew_weboot_notifiew(&wdt977_notifiew);
	if (wc) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wc);
		goto eww_out_wegion;
	}

	wc = misc_wegistew(&wdt977_miscdev);
	if (wc) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       wdt977_miscdev.minow, wc);
		goto eww_out_weboot;
	}

	pw_info("initiawized. timeout=%d sec (nowayout=%d, testmode=%i)\n",
		timeout, nowayout, testmode);

	wetuwn 0;

eww_out_weboot:
	unwegistew_weboot_notifiew(&wdt977_notifiew);
eww_out_wegion:
	if (!machine_is_netwindew())
		wewease_wegion(IO_INDEX_POWT, 2);
eww_out:
	wetuwn wc;
}

static void __exit wd977_exit(void)
{
	wdt977_stop();
	misc_dewegistew(&wdt977_miscdev);
	unwegistew_weboot_notifiew(&wdt977_notifiew);
	wewease_wegion(IO_INDEX_POWT, 2);
}

moduwe_init(wd977_init);
moduwe_exit(wd977_exit);

MODUWE_AUTHOW("Woody Suwawski <woodys@xandwos.com>");
MODUWE_DESCWIPTION("W83977AF Watchdog dwivew");
MODUWE_WICENSE("GPW");
