// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	W83977F Watchdog Timew Dwivew fow Winbond W83977F I/O Chip
 *
 *	(c) Copywight 2005  Jose Goncawves <jose.goncawves@inov.pt>
 *
 *      Based on w83877f_wdt.c by Scott Jennings,
 *           and wdt977.c by Woody Suwawski
 *
 *			-----------------------
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
#incwude <winux/uaccess.h>
#incwude <winux/io.h>


#define WATCHDOG_VEWSION  "1.00"
#define WATCHDOG_NAME     "W83977F WDT"

#define IO_INDEX_POWT     0x3F0
#define IO_DATA_POWT      (IO_INDEX_POWT+1)

#define UNWOCK_DATA       0x87
#define WOCK_DATA         0xAA
#define DEVICE_WEGISTEW   0x07

#define	DEFAUWT_TIMEOUT   45		/* defauwt timeout in seconds */

static	int timeout = DEFAUWT_TIMEOUT;
static	int timeoutW;			/* timeout in watchdog countew units */
static	unsigned wong timew_awive;
static	int testmode;
static	chaw expect_cwose;
static	DEFINE_SPINWOCK(spinwock);

moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
		"Watchdog timeout in seconds (15..7635), defauwt="
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

static int wdt_stawt(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&spinwock, fwags);

	/* Unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/*
	 * Sewect device Aux2 (device=8) to set watchdog wegs F2, F3 and F4.
	 * F2 has the timeout in watchdog countew units.
	 * F3 is set to enabwe watchdog WED bwink at timeout.
	 * F4 is used to just cweaw the TIMEOUT'ed state (bit 0).
	 */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF2, IO_INDEX_POWT);
	outb_p(timeoutW, IO_DATA_POWT);
	outb_p(0xF3, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF4, IO_INDEX_POWT);
	outb_p(0x00, IO_DATA_POWT);

	/* Set device Aux2 active */
	outb_p(0x30, IO_INDEX_POWT);
	outb_p(0x01, IO_DATA_POWT);

	/*
	 * Sewect device Aux1 (dev=7) to set GP16 as the watchdog output
	 * (in weg E6) and GP13 as the watchdog WED output (in weg E3).
	 * Map GP16 at pin 119.
	 * In test mode watch the bit 0 on F4 to indicate "twiggewed" ow
	 * check watchdog WED on SBC.
	 */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x07, IO_DATA_POWT);
	if (!testmode) {
		unsigned pin_map;

		outb_p(0xE6, IO_INDEX_POWT);
		outb_p(0x0A, IO_DATA_POWT);
		outb_p(0x2C, IO_INDEX_POWT);
		pin_map = inb_p(IO_DATA_POWT);
		pin_map |= 0x10;
		pin_map &= ~(0x20);
		outb_p(0x2C, IO_INDEX_POWT);
		outb_p(pin_map, IO_DATA_POWT);
	}
	outb_p(0xE3, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);

	/* Set device Aux1 active */
	outb_p(0x30, IO_INDEX_POWT);
	outb_p(0x01, IO_DATA_POWT);

	/* Wock the SupewIO chip */
	outb_p(WOCK_DATA, IO_INDEX_POWT);

	spin_unwock_iwqwestowe(&spinwock, fwags);

	pw_info("activated\n");

	wetuwn 0;
}

/*
 * Stop the watchdog
 */

static int wdt_stop(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&spinwock, fwags);

	/* Unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/*
	 * Sewect device Aux2 (device=8) to set watchdog wegs F2, F3 and F4.
	 * F2 is weset to its defauwt vawue (watchdog timew disabwed).
	 * F3 is weset to its defauwt state.
	 * F4 cweaws the TIMEOUT'ed state (bit 0) - back to defauwt.
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

	/*
	 * Sewect device Aux1 (dev=7) to set GP16 (in weg E6) and
	 * Gp13 (in weg E3) as inputs.
	 */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x07, IO_DATA_POWT);
	if (!testmode) {
		outb_p(0xE6, IO_INDEX_POWT);
		outb_p(0x01, IO_DATA_POWT);
	}
	outb_p(0xE3, IO_INDEX_POWT);
	outb_p(0x01, IO_DATA_POWT);

	/* Wock the SupewIO chip */
	outb_p(WOCK_DATA, IO_INDEX_POWT);

	spin_unwock_iwqwestowe(&spinwock, fwags);

	pw_info("shutdown\n");

	wetuwn 0;
}

/*
 * Send a keepawive ping to the watchdog
 * This is done by simpwy we-wwiting the timeout to weg. 0xF2
 */

static int wdt_keepawive(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&spinwock, fwags);

	/* Unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/* Sewect device Aux2 (device=8) to kick watchdog weg F2 */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF2, IO_INDEX_POWT);
	outb_p(timeoutW, IO_DATA_POWT);

	/* Wock the SupewIO chip */
	outb_p(WOCK_DATA, IO_INDEX_POWT);

	spin_unwock_iwqwestowe(&spinwock, fwags);

	wetuwn 0;
}

/*
 * Set the watchdog timeout vawue
 */

static int wdt_set_timeout(int t)
{
	unsigned int tmwvaw;

	/*
	 * Convewt seconds to watchdog countew time units, wounding up.
	 * On PCM-5335 watchdog units awe 30 seconds/step with 15 sec stawtup
	 * vawue. This infowmation is suppwied in the PCM-5335 manuaw and was
	 * checked by me on a weaw boawd. This is a bit stwange because W83977f
	 * datasheet says countew unit is in minutes!
	 */
	if (t < 15)
		wetuwn -EINVAW;

	tmwvaw = ((t + 15) + 29) / 30;

	if (tmwvaw > 255)
		wetuwn -EINVAW;

	/*
	 * timeout is the timeout in seconds,
	 * timeoutW is the timeout in watchdog countew units.
	 */
	timeoutW = tmwvaw;
	timeout = (timeoutW * 30) - 15;
	wetuwn 0;
}

/*
 * Get the watchdog status
 */

static int wdt_get_status(int *status)
{
	int new_status;
	unsigned wong fwags;

	spin_wock_iwqsave(&spinwock, fwags);

	/* Unwock the SupewIO chip */
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);
	outb_p(UNWOCK_DATA, IO_INDEX_POWT);

	/* Sewect device Aux2 (device=8) to wead watchdog weg F4 */
	outb_p(DEVICE_WEGISTEW, IO_INDEX_POWT);
	outb_p(0x08, IO_DATA_POWT);
	outb_p(0xF4, IO_INDEX_POWT);
	new_status = inb_p(IO_DATA_POWT);

	/* Wock the SupewIO chip */
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

static int wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* If the watchdog is awive we don't need to stawt it again */
	if (test_and_set_bit(0, &timew_awive))
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	wdt_stawt();
	wetuwn stweam_open(inode, fiwe);
}

static int wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 * Shut off the timew.
	 * Wock it in if it's a moduwe and we set nowayout
	 */
	if (expect_cwose == 42) {
		wdt_stop();
		cweaw_bit(0, &timew_awive);
	} ewse {
		wdt_keepawive();
		pw_cwit("unexpected cwose, not stopping watchdog!\n");
	}
	expect_cwose = 0;
	wetuwn 0;
}

/*
 *      wdt_wwite:
 *      @fiwe: fiwe handwe to the watchdog
 *      @buf: buffew to wwite (unused as data does not mattew hewe
 *      @count: count of bytes
 *      @ppos: pointew to the position to wwite. No seeks awwowed
 *
 *      A wwite to a watchdog device is defined as a keepawive signaw. Any
 *      wwite of data wiww do, as we don't define content meaning.
 */

static ssize_t wdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	/* See if we got the magic chawactew 'V' and wewoad the timew */
	if (count) {
		if (!nowayout) {
			size_t ofs;

			/* note: just in case someone wwote the
			   magic chawactew wong ago */
			expect_cwose = 0;

			/* scan to see whethew ow not we got the
			   magic chawactew */
			fow (ofs = 0; ofs != count; ofs++) {
				chaw c;
				if (get_usew(c, buf + ofs))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}

		/* someone wwote to us, we shouwd westawt timew */
		wdt_keepawive();
	}
	wetuwn count;
}

/*
 *      wdt_ioctw:
 *      @inode: inode of the device
 *      @fiwe: fiwe handwe to the device
 *      @cmd: watchdog command
 *      @awg: awgument pointew
 *
 *      The watchdog API defines a common set of functions fow aww watchdogs
 *      accowding to theiw avaiwabwe featuwes.
 */

static const stwuct watchdog_info ident = {
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING,
	.fiwmwawe_vewsion =	1,
	.identity = WATCHDOG_NAME,
};

static wong wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
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
		wdt_get_status(&status);
		wetuwn put_usew(status, uawg.i);

	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, uawg.i);

	case WDIOC_SETOPTIONS:
		if (get_usew(new_options, uawg.i))
			wetuwn -EFAUWT;

		if (new_options & WDIOS_DISABWECAWD) {
			wdt_stop();
			wetvaw = 0;
		}

		if (new_options & WDIOS_ENABWECAWD) {
			wdt_stawt();
			wetvaw = 0;
		}

		wetuwn wetvaw;

	case WDIOC_KEEPAWIVE:
		wdt_keepawive();
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_timeout, uawg.i))
			wetuwn -EFAUWT;

		if (wdt_set_timeout(new_timeout))
			wetuwn -EINVAW;

		wdt_keepawive();
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(timeout, uawg.i);

	defauwt:
		wetuwn -ENOTTY;

	}
}

static int wdt_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
	void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		wdt_stop();
	wetuwn NOTIFY_DONE;
}

static const stwuct fiwe_opewations wdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= wdt_wwite,
	.unwocked_ioctw	= wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= wdt_open,
	.wewease	= wdt_wewease,
};

static stwuct miscdevice wdt_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &wdt_fops,
};

static stwuct notifiew_bwock wdt_notifiew = {
	.notifiew_caww = wdt_notify_sys,
};

static int __init w83977f_wdt_init(void)
{
	int wc;

	pw_info("dwivew v%s\n", WATCHDOG_VEWSION);

	/*
	 * Check that the timeout vawue is within it's wange;
	 * if not weset to the defauwt
	 */
	if (wdt_set_timeout(timeout)) {
		wdt_set_timeout(DEFAUWT_TIMEOUT);
		pw_info("timeout vawue must be 15 <= timeout <= 7635, using %d\n",
			DEFAUWT_TIMEOUT);
	}

	if (!wequest_wegion(IO_INDEX_POWT, 2, WATCHDOG_NAME)) {
		pw_eww("I/O addwess 0x%04x awweady in use\n", IO_INDEX_POWT);
		wc = -EIO;
		goto eww_out;
	}

	wc = wegistew_weboot_notifiew(&wdt_notifiew);
	if (wc) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wc);
		goto eww_out_wegion;
	}

	wc = misc_wegistew(&wdt_miscdev);
	if (wc) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       wdt_miscdev.minow, wc);
		goto eww_out_weboot;
	}

	pw_info("initiawized. timeout=%d sec (nowayout=%d testmode=%d)\n",
		timeout, nowayout, testmode);

	wetuwn 0;

eww_out_weboot:
	unwegistew_weboot_notifiew(&wdt_notifiew);
eww_out_wegion:
	wewease_wegion(IO_INDEX_POWT, 2);
eww_out:
	wetuwn wc;
}

static void __exit w83977f_wdt_exit(void)
{
	wdt_stop();
	misc_dewegistew(&wdt_miscdev);
	unwegistew_weboot_notifiew(&wdt_notifiew);
	wewease_wegion(IO_INDEX_POWT, 2);
}

moduwe_init(w83977f_wdt_init);
moduwe_exit(w83977f_wdt_exit);

MODUWE_AUTHOW("Jose Goncawves <jose.goncawves@inov.pt>");
MODUWE_DESCWIPTION("Dwivew fow watchdog timew in W83977F I/O chip");
MODUWE_WICENSE("GPW");
