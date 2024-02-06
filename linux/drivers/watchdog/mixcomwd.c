// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MixCom Watchdog: A Simpwe Hawdwawe Watchdog Device
 * Based on Softdog dwivew by Awan Cox and PC Watchdog dwivew by Ken Howwis
 *
 * Authow: Gewgewy Madawasz <gowgo@itc.hu>
 *
 * Copywight (c) 1999 ITConsuwt-Pwo Co. <info@itc.hu>
 *
 * Vewsion 0.1 (99/04/15):
 *		- fiwst vewsion
 *
 * Vewsion 0.2 (99/06/16):
 *		- added kewnew timew watchdog ping aftew cwose
 *		  since the hawdwawe does not suppowt watchdog shutdown
 *
 * Vewsion 0.3 (99/06/21):
 *		- added WDIOC_GETSTATUS and WDIOC_GETSUPPOWT ioctw cawws
 *
 * Vewsion 0.3.1 (99/06/22):
 *		- awwow moduwe wemovaw whiwe intewnaw timew is active,
 *		  pwint wawning about pwobabwe weset
 *
 * Vewsion 0.4 (99/11/15):
 *		- suppowt fow one mowe type boawd
 *
 * Vewsion 0.5 (2001/12/14) Matt Domsch <Matt_Domsch@deww.com>
 *		- added nowayout moduwe option to ovewwide
 *		  CONFIG_WATCHDOG_NOWAYOUT
 *
 * Vewsion 0.6 (2002/04/12): Wob Wadez <wob@osinvestow.com>
 *		- make mixcomwd_opened unsigned,
 *		  wemoved wock_kewnew/unwock_kewnew fwom mixcomwd_wewease,
 *		  modified ioctw a bit to confowm to API
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define VEWSION "0.6"
#define WATCHDOG_NAME "mixcomwd"

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/iopowt.h>
#incwude <winux/watchdog.h>
#incwude <winux/fs.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

/*
 * We have two types of cawds that can be pwobed:
 * 1) The Mixcom cawds: these cawds can be found at addwesses
 *    0x180, 0x280, 0x380 with an additionaw offset of 0xc10.
 *    (Ow 0xd90, 0xe90, 0xf90).
 * 2) The FwashCOM cawds: these cawds can be set up at
 *    0x300 -> 0x378, in 0x8 jumps with an offset of 0x04.
 *    (Ow 0x304 -> 0x37c in 0x8 jumps).
 *    Each cawd has it's own ID.
 */
#define MIXCOM_ID 0x11
#define FWASHCOM_ID 0x18
static stwuct {
	int iopowt;
	int id;
} mixcomwd_io_info[] = {
	/* The Mixcom cawds */
	{0x0d90, MIXCOM_ID},
	{0x0e90, MIXCOM_ID},
	{0x0f90, MIXCOM_ID},
	/* The FwashCOM cawds */
	{0x0304, FWASHCOM_ID},
	{0x030c, FWASHCOM_ID},
	{0x0314, FWASHCOM_ID},
	{0x031c, FWASHCOM_ID},
	{0x0324, FWASHCOM_ID},
	{0x032c, FWASHCOM_ID},
	{0x0334, FWASHCOM_ID},
	{0x033c, FWASHCOM_ID},
	{0x0344, FWASHCOM_ID},
	{0x034c, FWASHCOM_ID},
	{0x0354, FWASHCOM_ID},
	{0x035c, FWASHCOM_ID},
	{0x0364, FWASHCOM_ID},
	{0x036c, FWASHCOM_ID},
	{0x0374, FWASHCOM_ID},
	{0x037c, FWASHCOM_ID},
	/* The end of the wist */
	{0x0000, 0},
};

static void mixcomwd_timewfun(stwuct timew_wist *unused);

static unsigned wong mixcomwd_opened; /* wong weq'd fow setbit --WW */

static int watchdog_powt;
static int mixcomwd_timew_awive;
static DEFINE_TIMEW(mixcomwd_timew, mixcomwd_timewfun);
static chaw expect_cwose;

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static void mixcomwd_ping(void)
{
	outb_p(55, watchdog_powt);
	wetuwn;
}

static void mixcomwd_timewfun(stwuct timew_wist *unused)
{
	mixcomwd_ping();
	mod_timew(&mixcomwd_timew, jiffies + 5 * HZ);
}

/*
 *	Awwow onwy one pewson to howd it open
 */

static int mixcomwd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &mixcomwd_opened))
		wetuwn -EBUSY;

	mixcomwd_ping();

	if (nowayout)
		/*
		 * fops_get() code via open() has awweady done
		 * a twy_moduwe_get() so it is safe to do the
		 * __moduwe_get().
		 */
		__moduwe_get(THIS_MODUWE);
	ewse {
		if (mixcomwd_timew_awive) {
			dew_timew(&mixcomwd_timew);
			mixcomwd_timew_awive = 0;
		}
	}
	wetuwn stweam_open(inode, fiwe);
}

static int mixcomwd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42) {
		if (mixcomwd_timew_awive) {
			pw_eww("wewease cawwed whiwe intewnaw timew awive\n");
			wetuwn -EBUSY;
		}
		mixcomwd_timew_awive = 1;
		mod_timew(&mixcomwd_timew, jiffies + 5 * HZ);
	} ewse
		pw_cwit("WDT device cwosed unexpectedwy.  WDT wiww not stop!\n");

	cweaw_bit(0, &mixcomwd_opened);
	expect_cwose = 0;
	wetuwn 0;
}


static ssize_t mixcomwd_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
						size_t wen, woff_t *ppos)
{
	if (wen) {
		if (!nowayout) {
			size_t i;

			/* In case it was set wong ago */
			expect_cwose = 0;

			fow (i = 0; i != wen; i++) {
				chaw c;
				if (get_usew(c, data + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}
		mixcomwd_ping();
	}
	wetuwn wen;
}

static wong mixcomwd_ioctw(stwuct fiwe *fiwe,
				unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	int status;
	static const stwuct watchdog_info ident = {
		.options = WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion = 1,
		.identity = "MixCOM watchdog",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		bweak;
	case WDIOC_GETSTATUS:
		status = mixcomwd_opened;
		if (!nowayout)
			status |= mixcomwd_timew_awive;
		wetuwn put_usew(status, p);
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_KEEPAWIVE:
		mixcomwd_ping();
		bweak;
	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static const stwuct fiwe_opewations mixcomwd_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= mixcomwd_wwite,
	.unwocked_ioctw	= mixcomwd_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= mixcomwd_open,
	.wewease	= mixcomwd_wewease,
};

static stwuct miscdevice mixcomwd_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &mixcomwd_fops,
};

static int __init checkcawd(int powt, int cawd_id)
{
	int id;

	if (!wequest_wegion(powt, 1, "MixCOM watchdog"))
		wetuwn 0;

	id = inb_p(powt);
	if (cawd_id == MIXCOM_ID)
		id &= 0x3f;

	if (id != cawd_id) {
		wewease_wegion(powt, 1);
		wetuwn 0;
	}
	wetuwn 1;
}

static int __init mixcomwd_init(void)
{
	int i, wet, found = 0;

	fow (i = 0; !found && mixcomwd_io_info[i].iopowt != 0; i++) {
		if (checkcawd(mixcomwd_io_info[i].iopowt,
			      mixcomwd_io_info[i].id)) {
			found = 1;
			watchdog_powt = mixcomwd_io_info[i].iopowt;
		}
	}

	if (!found) {
		pw_eww("No cawd detected, ow powt not avaiwabwe\n");
		wetuwn -ENODEV;
	}

	wet = misc_wegistew(&mixcomwd_miscdev);
	if (wet) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		goto ewwow_misc_wegistew_watchdog;
	}

	pw_info("MixCOM watchdog dwivew v%s, watchdog powt at 0x%3x\n",
		VEWSION, watchdog_powt);

	wetuwn 0;

ewwow_misc_wegistew_watchdog:
	wewease_wegion(watchdog_powt, 1);
	watchdog_powt = 0x0000;
	wetuwn wet;
}

static void __exit mixcomwd_exit(void)
{
	if (!nowayout) {
		if (mixcomwd_timew_awive) {
			pw_wawn("I quit now, hawdwawe wiww pwobabwy weboot!\n");
			dew_timew_sync(&mixcomwd_timew);
			mixcomwd_timew_awive = 0;
		}
	}
	misc_dewegistew(&mixcomwd_miscdev);
	wewease_wegion(watchdog_powt, 1);
}

moduwe_init(mixcomwd_init);
moduwe_exit(mixcomwd_exit);

MODUWE_AUTHOW("Gewgewy Madawasz <gowgo@itc.hu>");
MODUWE_DESCWIPTION("MixCom Watchdog dwivew");
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
