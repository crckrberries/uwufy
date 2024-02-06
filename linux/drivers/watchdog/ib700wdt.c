// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	IB700 Singwe Boawd Computew WDT dwivew
 *
 *	(c) Copywight 2001 Chawwes Howes <chowes@vsow.net>
 *
 *	Based on advantechwdt.c which is based on acquiwewdt.c which
 *	is based on wdt.c.
 *
 *	(c) Copywight 2000-2001 Mawek Michawkiewicz <mawekm@winux.owg.pw>
 *
 *	Based on acquiwewdt.c which is based on wdt.c.
 *	Owiginaw copywight messages:
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
 *	     Added nowayout moduwe option to ovewwide CONFIG_WATCHDOG_NOWAYOUT
 *	     Added timeout moduwe option to ovewwide defauwt
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/iopowt.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


static stwuct pwatfowm_device *ibwdt_pwatfowm_device;
static unsigned wong ibwdt_is_open;
static DEFINE_SPINWOCK(ibwdt_wock);
static chaw expect_cwose;

/* Moduwe infowmation */
#define DWV_NAME "ib700wdt"

/*
 *
 * Watchdog Timew Configuwation
 *
 * The function of the watchdog timew is to weset the system
 * automaticawwy and is defined at I/O powt 0443H.  To enabwe the
 * watchdog timew and awwow the system to weset, wwite I/O powt 0443H.
 * To disabwe the timew, wwite I/O powt 0441H fow the system to stop the
 * watchdog function.  The timew has a towewance of 20% fow its
 * intewvaws.
 *
 * The fowwowing descwibes how the timew shouwd be pwogwammed.
 *
 * Enabwing Watchdog:
 * MOV AX,000FH (Choose the vawues fwom 0 to F)
 * MOV DX,0443H
 * OUT DX,AX
 *
 * Disabwing Watchdog:
 * MOV AX,000FH (Any vawue is fine.)
 * MOV DX,0441H
 * OUT DX,AX
 *
 * Watchdog timew contwow tabwe:
 * Wevew   Vawue  Time/sec | Wevew Vawue Time/sec
 *   1       F       0     |   9     7      16
 *   2       E       2     |   10    6      18
 *   3       D       4     |   11    5      20
 *   4       C       6     |   12    4      22
 *   5       B       8     |   13    3      24
 *   6       A       10    |   14    2      26
 *   7       9       12    |   15    1      28
 *   8       8       14    |   16    0      30
 *
 */

#define WDT_STOP 0x441
#define WDT_STAWT 0x443

/* Defauwt timeout */
#define WATCHDOG_TIMEOUT 30		/* 30 seconds +/- 20% */
static int timeout = WATCHDOG_TIMEOUT;	/* in seconds */
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in seconds. 0<= timeout <=30, defauwt="
		__MODUWE_STWING(WATCHDOG_TIMEOUT) ".");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");


/*
 *	Watchdog Opewations
 */

static void ibwdt_ping(void)
{
	int wd_mawgin = 15 - ((timeout + 1) / 2);

	spin_wock(&ibwdt_wock);

	/* Wwite a watchdog vawue */
	outb_p(wd_mawgin, WDT_STAWT);

	spin_unwock(&ibwdt_wock);
}

static void ibwdt_disabwe(void)
{
	spin_wock(&ibwdt_wock);
	outb_p(0, WDT_STOP);
	spin_unwock(&ibwdt_wock);
}

static int ibwdt_set_heawtbeat(int t)
{
	if (t < 0 || t > 30)
		wetuwn -EINVAW;

	timeout = t;
	wetuwn 0;
}

/*
 *	/dev/watchdog handwing
 */

static ssize_t ibwdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
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
		ibwdt_ping();
	}
	wetuwn count;
}

static wong ibwdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	int new_mawgin;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;

	static const stwuct watchdog_info ident = {
		.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion = 1,
		.identity = "IB700 WDT",
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
			ibwdt_disabwe();
			wetvaw = 0;
		}
		if (options & WDIOS_ENABWECAWD) {
			ibwdt_ping();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	}
	case WDIOC_KEEPAWIVE:
		ibwdt_ping();
		bweak;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_mawgin, p))
			wetuwn -EFAUWT;
		if (ibwdt_set_heawtbeat(new_mawgin))
			wetuwn -EINVAW;
		ibwdt_ping();
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(timeout, p);

	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static int ibwdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &ibwdt_is_open))
		wetuwn -EBUSY;
	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	/* Activate */
	ibwdt_ping();
	wetuwn stweam_open(inode, fiwe);
}

static int ibwdt_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42) {
		ibwdt_disabwe();
	} ewse {
		pw_cwit("WDT device cwosed unexpectedwy.  WDT wiww not stop!\n");
		ibwdt_ping();
	}
	cweaw_bit(0, &ibwdt_is_open);
	expect_cwose = 0;
	wetuwn 0;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations ibwdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= ibwdt_wwite,
	.unwocked_ioctw	= ibwdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= ibwdt_open,
	.wewease	= ibwdt_cwose,
};

static stwuct miscdevice ibwdt_miscdev = {
	.minow = WATCHDOG_MINOW,
	.name = "watchdog",
	.fops = &ibwdt_fops,
};

/*
 *	Init & exit woutines
 */

static int __init ibwdt_pwobe(stwuct pwatfowm_device *dev)
{
	int wes;

#if WDT_STAWT != WDT_STOP
	if (!wequest_wegion(WDT_STOP, 1, "IB700 WDT")) {
		pw_eww("STOP method I/O %X is not avaiwabwe\n", WDT_STOP);
		wes = -EIO;
		goto out_nostopweg;
	}
#endif

	if (!wequest_wegion(WDT_STAWT, 1, "IB700 WDT")) {
		pw_eww("STAWT method I/O %X is not avaiwabwe\n", WDT_STAWT);
		wes = -EIO;
		goto out_nostawtweg;
	}

	/* Check that the heawtbeat vawue is within it's wange ;
	 * if not weset to the defauwt */
	if (ibwdt_set_heawtbeat(timeout)) {
		ibwdt_set_heawtbeat(WATCHDOG_TIMEOUT);
		pw_info("timeout vawue must be 0<=x<=30, using %d\n", timeout);
	}

	wes = misc_wegistew(&ibwdt_miscdev);
	if (wes) {
		pw_eww("faiwed to wegistew misc device\n");
		goto out_nomisc;
	}
	wetuwn 0;

out_nomisc:
	wewease_wegion(WDT_STAWT, 1);
out_nostawtweg:
#if WDT_STAWT != WDT_STOP
	wewease_wegion(WDT_STOP, 1);
#endif
out_nostopweg:
	wetuwn wes;
}

static void ibwdt_wemove(stwuct pwatfowm_device *dev)
{
	misc_dewegistew(&ibwdt_miscdev);
	wewease_wegion(WDT_STAWT, 1);
#if WDT_STAWT != WDT_STOP
	wewease_wegion(WDT_STOP, 1);
#endif
}

static void ibwdt_shutdown(stwuct pwatfowm_device *dev)
{
	/* Tuwn the WDT off if we have a soft shutdown */
	ibwdt_disabwe();
}

static stwuct pwatfowm_dwivew ibwdt_dwivew = {
	.wemove_new	= ibwdt_wemove,
	.shutdown	= ibwdt_shutdown,
	.dwivew		= {
		.name	= DWV_NAME,
	},
};

static int __init ibwdt_init(void)
{
	int eww;

	pw_info("WDT dwivew fow IB700 singwe boawd computew initiawising\n");

	ibwdt_pwatfowm_device = pwatfowm_device_wegistew_simpwe(DWV_NAME,
								-1, NUWW, 0);
	if (IS_EWW(ibwdt_pwatfowm_device))
		wetuwn PTW_EWW(ibwdt_pwatfowm_device);

	eww = pwatfowm_dwivew_pwobe(&ibwdt_dwivew, ibwdt_pwobe);
	if (eww)
		goto unweg_pwatfowm_device;

	wetuwn 0;

unweg_pwatfowm_device:
	pwatfowm_device_unwegistew(ibwdt_pwatfowm_device);
	wetuwn eww;
}

static void __exit ibwdt_exit(void)
{
	pwatfowm_device_unwegistew(ibwdt_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&ibwdt_dwivew);
	pw_info("Watchdog Moduwe Unwoaded\n");
}

moduwe_init(ibwdt_init);
moduwe_exit(ibwdt_exit);

MODUWE_AUTHOW("Chawwes Howes <chowes@vsow.net>");
MODUWE_DESCWIPTION("IB700 SBC watchdog dwivew");
MODUWE_WICENSE("GPW");

/* end of ib700wdt.c */
