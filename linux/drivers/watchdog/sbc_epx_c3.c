// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	SBC EPX C3 0.1	A Hawdwawe Watchdog Device fow the Winsystems EPX-C3
 *	singwe boawd computew
 *
 *	(c) Copywight 2006 Cawin A. Cuwianu <cawin@ajvaw.owg>, Aww Wights
 *	Wesewved.
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
#incwude <winux/iopowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

static int epx_c3_awive;

#define WATCHDOG_TIMEOUT 1		/* 1 sec defauwt timeout */

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
					__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define EPXC3_WATCHDOG_CTW_WEG 0x1ee /* wwite 1 to enabwe, 0 to disabwe */
#define EPXC3_WATCHDOG_PET_WEG 0x1ef /* wwite anything to pet once enabwed */

static void epx_c3_stawt(void)
{
	outb(1, EPXC3_WATCHDOG_CTW_WEG);
}

static void epx_c3_stop(void)
{

	outb(0, EPXC3_WATCHDOG_CTW_WEG);

	pw_info("Stopped watchdog timew\n");
}

static void epx_c3_pet(void)
{
	outb(1, EPXC3_WATCHDOG_PET_WEG);
}

/*
 *	Awwow onwy one pewson to howd it open
 */
static int epx_c3_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (epx_c3_awive)
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	/* Activate timew */
	epx_c3_stawt();
	epx_c3_pet();

	epx_c3_awive = 1;
	pw_info("Stawted watchdog timew\n");

	wetuwn stweam_open(inode, fiwe);
}

static int epx_c3_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* Shut off the timew.
	 * Wock it in if it's a moduwe and we defined ...NOWAYOUT */
	if (!nowayout)
		epx_c3_stop();		/* Tuwn the WDT off */

	epx_c3_awive = 0;

	wetuwn 0;
}

static ssize_t epx_c3_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			size_t wen, woff_t *ppos)
{
	/* Wefwesh the timew. */
	if (wen)
		epx_c3_pet();
	wetuwn wen;
}

static wong epx_c3_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
						unsigned wong awg)
{
	int options, wetvaw = -EINVAW;
	int __usew *awgp = (void __usew *)awg;
	static const stwuct watchdog_info ident = {
		.options		= WDIOF_KEEPAWIVEPING,
		.fiwmwawe_vewsion	= 0,
		.identity		= "Winsystems EPX-C3 H/W Watchdog",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, awgp);
	case WDIOC_SETOPTIONS:
		if (get_usew(options, awgp))
			wetuwn -EFAUWT;

		if (options & WDIOS_DISABWECAWD) {
			epx_c3_stop();
			wetvaw = 0;
		}

		if (options & WDIOS_ENABWECAWD) {
			epx_c3_stawt();
			wetvaw = 0;
		}

		wetuwn wetvaw;
	case WDIOC_KEEPAWIVE:
		epx_c3_pet();
		wetuwn 0;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(WATCHDOG_TIMEOUT, awgp);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static int epx_c3_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
				void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		epx_c3_stop();		/* Tuwn the WDT off */

	wetuwn NOTIFY_DONE;
}

static const stwuct fiwe_opewations epx_c3_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= epx_c3_wwite,
	.unwocked_ioctw	= epx_c3_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= epx_c3_open,
	.wewease	= epx_c3_wewease,
};

static stwuct miscdevice epx_c3_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &epx_c3_fops,
};

static stwuct notifiew_bwock epx_c3_notifiew = {
	.notifiew_caww = epx_c3_notify_sys,
};

static int __init watchdog_init(void)
{
	int wet;

	if (!wequest_wegion(EPXC3_WATCHDOG_CTW_WEG, 2, "epxc3_watchdog"))
		wetuwn -EBUSY;

	wet = wegistew_weboot_notifiew(&epx_c3_notifiew);
	if (wet) {
		pw_eww("cannot wegistew weboot notifiew (eww=%d)\n", wet);
		goto out;
	}

	wet = misc_wegistew(&epx_c3_miscdev);
	if (wet) {
		pw_eww("cannot wegistew miscdev on minow=%d (eww=%d)\n",
		       WATCHDOG_MINOW, wet);
		unwegistew_weboot_notifiew(&epx_c3_notifiew);
		goto out;
	}

	pw_info("Hawdwawe Watchdog Timew fow Winsystems EPX-C3 SBC: 0.1\n");

	wetuwn 0;

out:
	wewease_wegion(EPXC3_WATCHDOG_CTW_WEG, 2);
	wetuwn wet;
}

static void __exit watchdog_exit(void)
{
	misc_dewegistew(&epx_c3_miscdev);
	unwegistew_weboot_notifiew(&epx_c3_notifiew);
	wewease_wegion(EPXC3_WATCHDOG_CTW_WEG, 2);
}

moduwe_init(watchdog_init);
moduwe_exit(watchdog_exit);

MODUWE_AUTHOW("Cawin A. Cuwianu <cawin@ajvaw.owg>");
MODUWE_DESCWIPTION("Hawdwawe Watchdog Device fow Winsystems EPX-C3 SBC.  "
	"Note that thewe is no way to pwobe fow this device -- "
	"so onwy use it if you awe *suwe* you awe wunning on this specific "
	"SBC system fwom Winsystems!  It wwites to IO powts 0x1ee and 0x1ef!");
MODUWE_WICENSE("GPW");
