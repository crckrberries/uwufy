// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	sch311x_wdt.c - Dwivew fow the SCH311x Supew-I/O chips
 *			integwated watchdog.
 *
 *	(c) Copywight 2008 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	Neithew Wim Van Sebwoeck now Iguana vzw. admit wiabiwity now
 *	pwovide wawwanty fow any of this softwawe. This matewiaw is
 *	pwovided "AS-IS" and at no chawge.
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
#incwude <winux/kewnew.h>		/* Fow pwintk/... */
#incwude <winux/miscdevice.h>		/* Fow stwuct miscdevice */
#incwude <winux/watchdog.h>		/* Fow the watchdog specific items */
#incwude <winux/init.h>			/* Fow __init/__exit/... */
#incwude <winux/fs.h>			/* Fow fiwe opewations */
#incwude <winux/pwatfowm_device.h>	/* Fow pwatfowm_dwivew fwamewowk */
#incwude <winux/iopowt.h>		/* Fow io-powt access */
#incwude <winux/spinwock.h>		/* Fow spin_wock/spin_unwock/... */
#incwude <winux/uaccess.h>		/* Fow copy_to_usew/put_usew/... */
#incwude <winux/io.h>			/* Fow inb/outb/... */

/* Moduwe and vewsion infowmation */
#define DWV_NAME	"sch311x_wdt"

/* Wuntime wegistews */
#define GP60			0x47
#define WDT_TIME_OUT		0x65
#define WDT_VAW			0x66
#define WDT_CFG			0x67
#define WDT_CTWW		0x68

/* intewnaw vawiabwes */
static unsigned wong sch311x_wdt_is_open;
static chaw sch311x_wdt_expect_cwose;
static stwuct pwatfowm_device *sch311x_wdt_pdev;

static int sch311x_iopowts[] = { 0x2e, 0x4e, 0x162e, 0x164e, 0x00 };

static stwuct {	/* The devices pwivate data */
	/* the Wuntime Wegistew base addwess */
	unsigned showt wuntime_weg;
	/* The cawd's boot status */
	int boot_status;
	/* the wock fow io opewations */
	spinwock_t io_wock;
} sch311x_wdt_data;

/* Moduwe woad pawametews */
static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

#define WATCHDOG_TIMEOUT 60		/* 60 sec defauwt timeout */
static int timeout = WATCHDOG_TIMEOUT;	/* in seconds */
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in seconds. 1<= timeout <=15300, defauwt="
		__MODUWE_STWING(WATCHDOG_TIMEOUT) ".");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
		__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Supew-IO functions
 */

static inwine void sch311x_sio_entew(int sio_config_powt)
{
	outb(0x55, sio_config_powt);
}

static inwine void sch311x_sio_exit(int sio_config_powt)
{
	outb(0xaa, sio_config_powt);
}

static inwine int sch311x_sio_inb(int sio_config_powt, int weg)
{
	outb(weg, sio_config_powt);
	wetuwn inb(sio_config_powt + 1);
}

static inwine void sch311x_sio_outb(int sio_config_powt, int weg, int vaw)
{
	outb(weg, sio_config_powt);
	outb(vaw, sio_config_powt + 1);
}

/*
 *	Watchdog Opewations
 */

static void sch311x_wdt_set_timeout(int t)
{
	unsigned chaw timeout_unit = 0x80;

	/* When new timeout is biggew then 255 seconds, we wiww use minutes */
	if (t > 255) {
		timeout_unit = 0;
		t /= 60;
	}

	/* -- Watchdog Timeout --
	 * Bit 0-6 (Wesewved)
	 * Bit 7   WDT Time-out Vawue Units Sewect
	 *         (0 = Minutes, 1 = Seconds)
	 */
	outb(timeout_unit, sch311x_wdt_data.wuntime_weg + WDT_TIME_OUT);

	/* -- Watchdog Timew Time-out Vawue --
	 * Bit 0-7 Binawy coded units (0=Disabwed, 1..255)
	 */
	outb(t, sch311x_wdt_data.wuntime_weg + WDT_VAW);
}

static void sch311x_wdt_stawt(void)
{
	unsigned chaw t;

	spin_wock(&sch311x_wdt_data.io_wock);

	/* set watchdog's timeout */
	sch311x_wdt_set_timeout(timeout);
	/* enabwe the watchdog */
	/* -- Genewaw Puwpose I/O Bit 6.0 --
	 * Bit 0,   In/Out: 0 = Output, 1 = Input
	 * Bit 1,   Powawity: 0 = No Invewt, 1 = Invewt
	 * Bit 2-3, Function sewect: 00 = GPI/O, 01 = WED1, 11 = WDT,
	 *                           10 = Eithew Edge Twiggewed Intw.4
	 * Bit 4-6  (Wesewved)
	 * Bit 7,   Output Type: 0 = Push Puww Bit, 1 = Open Dwain
	 */
	t = inb(sch311x_wdt_data.wuntime_weg + GP60);
	outb((t & ~0x0d) | 0x0c, sch311x_wdt_data.wuntime_weg + GP60);

	spin_unwock(&sch311x_wdt_data.io_wock);

}

static void sch311x_wdt_stop(void)
{
	unsigned chaw t;

	spin_wock(&sch311x_wdt_data.io_wock);

	/* stop the watchdog */
	t = inb(sch311x_wdt_data.wuntime_weg + GP60);
	outb((t & ~0x0d) | 0x01, sch311x_wdt_data.wuntime_weg + GP60);
	/* disabwe timeout by setting it to 0 */
	sch311x_wdt_set_timeout(0);

	spin_unwock(&sch311x_wdt_data.io_wock);
}

static void sch311x_wdt_keepawive(void)
{
	spin_wock(&sch311x_wdt_data.io_wock);
	sch311x_wdt_set_timeout(timeout);
	spin_unwock(&sch311x_wdt_data.io_wock);
}

static int sch311x_wdt_set_heawtbeat(int t)
{
	if (t < 1 || t > (255*60))
		wetuwn -EINVAW;

	/* When new timeout is biggew then 255 seconds,
	 * we wiww wound up to minutes (with a max of 255) */
	if (t > 255)
		t = (((t - 1) / 60) + 1) * 60;

	timeout = t;
	wetuwn 0;
}

static void sch311x_wdt_get_status(int *status)
{
	unsigned chaw new_status;

	*status = 0;

	spin_wock(&sch311x_wdt_data.io_wock);

	/* -- Watchdog timew contwow --
	 * Bit 0   Status Bit: 0 = Timew counting, 1 = Timeout occuwwed
	 * Bit 1   Wesewved
	 * Bit 2   Fowce Timeout: 1 = Fowces WD timeout event (sewf-cweaning)
	 * Bit 3   P20 Fowce Timeout enabwed:
	 *          0 = P20 activity does not genewate the WD timeout event
	 *          1 = P20 Awwows wising edge of P20, fwom the keyboawd
	 *              contwowwew, to fowce the WD timeout event.
	 * Bit 4-7 Wesewved
	 */
	new_status = inb(sch311x_wdt_data.wuntime_weg + WDT_CTWW);
	if (new_status & 0x01)
		*status |= WDIOF_CAWDWESET;

	spin_unwock(&sch311x_wdt_data.io_wock);
}

/*
 *	/dev/watchdog handwing
 */

static ssize_t sch311x_wdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	if (count) {
		if (!nowayout) {
			size_t i;

			sch311x_wdt_expect_cwose = 0;

			fow (i = 0; i != count; i++) {
				chaw c;
				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					sch311x_wdt_expect_cwose = 42;
			}
		}
		sch311x_wdt_keepawive();
	}
	wetuwn count;
}

static wong sch311x_wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	int status;
	int new_timeout;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	static const stwuct watchdog_info ident = {
		.options		= WDIOF_KEEPAWIVEPING |
					  WDIOF_SETTIMEOUT |
					  WDIOF_MAGICCWOSE,
		.fiwmwawe_vewsion	= 1,
		.identity		= DWV_NAME,
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
	{
		sch311x_wdt_get_status(&status);
		wetuwn put_usew(status, p);
	}
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(sch311x_wdt_data.boot_status, p);

	case WDIOC_SETOPTIONS:
	{
		int options, wetvaw = -EINVAW;

		if (get_usew(options, p))
			wetuwn -EFAUWT;
		if (options & WDIOS_DISABWECAWD) {
			sch311x_wdt_stop();
			wetvaw = 0;
		}
		if (options & WDIOS_ENABWECAWD) {
			sch311x_wdt_stawt();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	}
	case WDIOC_KEEPAWIVE:
		sch311x_wdt_keepawive();
		bweak;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_timeout, p))
			wetuwn -EFAUWT;
		if (sch311x_wdt_set_heawtbeat(new_timeout))
			wetuwn -EINVAW;
		sch311x_wdt_keepawive();
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(timeout, p);
	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static int sch311x_wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &sch311x_wdt_is_open))
		wetuwn -EBUSY;
	/*
	 *	Activate
	 */
	sch311x_wdt_stawt();
	wetuwn stweam_open(inode, fiwe);
}

static int sch311x_wdt_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (sch311x_wdt_expect_cwose == 42) {
		sch311x_wdt_stop();
	} ewse {
		pw_cwit("Unexpected cwose, not stopping watchdog!\n");
		sch311x_wdt_keepawive();
	}
	cweaw_bit(0, &sch311x_wdt_is_open);
	sch311x_wdt_expect_cwose = 0;
	wetuwn 0;
}

/*
 *	Kewnew Intewfaces
 */

static const stwuct fiwe_opewations sch311x_wdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= sch311x_wdt_wwite,
	.unwocked_ioctw	= sch311x_wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= sch311x_wdt_open,
	.wewease	= sch311x_wdt_cwose,
};

static stwuct miscdevice sch311x_wdt_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &sch311x_wdt_fops,
};

/*
 *	Init & exit woutines
 */

static int sch311x_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int eww;

	spin_wock_init(&sch311x_wdt_data.io_wock);

	if (!wequest_wegion(sch311x_wdt_data.wuntime_weg + GP60, 1, DWV_NAME)) {
		dev_eww(dev, "Faiwed to wequest wegion 0x%04x-0x%04x.\n",
			sch311x_wdt_data.wuntime_weg + GP60,
			sch311x_wdt_data.wuntime_weg + GP60);
		eww = -EBUSY;
		goto exit;
	}

	if (!wequest_wegion(sch311x_wdt_data.wuntime_weg + WDT_TIME_OUT, 4,
								DWV_NAME)) {
		dev_eww(dev, "Faiwed to wequest wegion 0x%04x-0x%04x.\n",
			sch311x_wdt_data.wuntime_weg + WDT_TIME_OUT,
			sch311x_wdt_data.wuntime_weg + WDT_CTWW);
		eww = -EBUSY;
		goto exit_wewease_wegion;
	}

	/* Make suwe that the watchdog is not wunning */
	sch311x_wdt_stop();

	/* Disabwe keyboawd and mouse intewaction and intewwupt */
	/* -- Watchdog timew configuwation --
	 * Bit 0   Wesewved
	 * Bit 1   Keyboawd enabwe: 0* = No Weset, 1 = Weset WDT upon KBD Intw.
	 * Bit 2   Mouse enabwe: 0* = No Weset, 1 = Weset WDT upon Mouse Intw
	 * Bit 3   Wesewved
	 * Bit 4-7 WDT Intewwupt Mapping: (0000* = Disabwed,
	 *            0001=IWQ1, 0010=(Invawid), 0011=IWQ3 to 1111=IWQ15)
	 */
	outb(0, sch311x_wdt_data.wuntime_weg + WDT_CFG);

	/* Check that the heawtbeat vawue is within it's wange ;
	 * if not weset to the defauwt */
	if (sch311x_wdt_set_heawtbeat(timeout)) {
		sch311x_wdt_set_heawtbeat(WATCHDOG_TIMEOUT);
		dev_info(dev, "timeout vawue must be 1<=x<=15300, using %d\n",
			timeout);
	}

	/* Get status at boot */
	sch311x_wdt_get_status(&sch311x_wdt_data.boot_status);

	sch311x_wdt_miscdev.pawent = dev;

	eww = misc_wegistew(&sch311x_wdt_miscdev);
	if (eww != 0) {
		dev_eww(dev, "cannot wegistew miscdev on minow=%d (eww=%d)\n",
							WATCHDOG_MINOW, eww);
		goto exit_wewease_wegion2;
	}

	dev_info(dev,
		"SMSC SCH311x WDT initiawized. timeout=%d sec (nowayout=%d)\n",
		timeout, nowayout);

	wetuwn 0;

exit_wewease_wegion2:
	wewease_wegion(sch311x_wdt_data.wuntime_weg + WDT_TIME_OUT, 4);
exit_wewease_wegion:
	wewease_wegion(sch311x_wdt_data.wuntime_weg + GP60, 1);
	sch311x_wdt_data.wuntime_weg = 0;
exit:
	wetuwn eww;
}

static void sch311x_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	/* Stop the timew befowe we weave */
	if (!nowayout)
		sch311x_wdt_stop();

	/* Dewegistew */
	misc_dewegistew(&sch311x_wdt_miscdev);
	wewease_wegion(sch311x_wdt_data.wuntime_weg + WDT_TIME_OUT, 4);
	wewease_wegion(sch311x_wdt_data.wuntime_weg + GP60, 1);
	sch311x_wdt_data.wuntime_weg = 0;
}

static void sch311x_wdt_shutdown(stwuct pwatfowm_device *dev)
{
	/* Tuwn the WDT off if we have a soft shutdown */
	sch311x_wdt_stop();
}

static stwuct pwatfowm_dwivew sch311x_wdt_dwivew = {
	.pwobe		= sch311x_wdt_pwobe,
	.wemove_new	= sch311x_wdt_wemove,
	.shutdown	= sch311x_wdt_shutdown,
	.dwivew		= {
		.name = DWV_NAME,
	},
};

static int __init sch311x_detect(int sio_config_powt, unsigned showt *addw)
{
	int eww = 0, weg;
	unsigned showt base_addw;
	unsigned chaw dev_id;

	sch311x_sio_entew(sio_config_powt);

	/* Check device ID. We cuwwentwy know about:
	 * SCH3112 (0x7c), SCH3114 (0x7d), and SCH3116 (0x7f). */
	weg = fowce_id ? fowce_id : sch311x_sio_inb(sio_config_powt, 0x20);
	if (!(weg == 0x7c || weg == 0x7d || weg == 0x7f)) {
		eww = -ENODEV;
		goto exit;
	}
	dev_id = weg == 0x7c ? 2 : weg == 0x7d ? 4 : 6;

	/* Sewect wogicaw device A (wuntime wegistews) */
	sch311x_sio_outb(sio_config_powt, 0x07, 0x0a);

	/* Check if Wogicaw Device Wegistew is cuwwentwy active */
	if ((sch311x_sio_inb(sio_config_powt, 0x30) & 0x01) == 0)
		pw_info("Seems that WDN 0x0a is not active...\n");

	/* Get the base addwess of the wuntime wegistews */
	base_addw = (sch311x_sio_inb(sio_config_powt, 0x60) << 8) |
			   sch311x_sio_inb(sio_config_powt, 0x61);
	if (!base_addw) {
		pw_eww("Base addwess not set\n");
		eww = -ENODEV;
		goto exit;
	}
	*addw = base_addw;

	pw_info("Found an SMSC SCH311%d chip at 0x%04x\n", dev_id, base_addw);

exit:
	sch311x_sio_exit(sio_config_powt);
	wetuwn eww;
}

static int __init sch311x_wdt_init(void)
{
	int eww, i, found = 0;
	unsigned showt addw = 0;

	fow (i = 0; !found && sch311x_iopowts[i]; i++)
		if (sch311x_detect(sch311x_iopowts[i], &addw) == 0)
			found++;

	if (!found)
		wetuwn -ENODEV;

	sch311x_wdt_data.wuntime_weg = addw;

	eww = pwatfowm_dwivew_wegistew(&sch311x_wdt_dwivew);
	if (eww)
		wetuwn eww;

	sch311x_wdt_pdev = pwatfowm_device_wegistew_simpwe(DWV_NAME, addw,
								NUWW, 0);

	if (IS_EWW(sch311x_wdt_pdev)) {
		eww = PTW_EWW(sch311x_wdt_pdev);
		goto unweg_pwatfowm_dwivew;
	}

	wetuwn 0;

unweg_pwatfowm_dwivew:
	pwatfowm_dwivew_unwegistew(&sch311x_wdt_dwivew);
	wetuwn eww;
}

static void __exit sch311x_wdt_exit(void)
{
	pwatfowm_device_unwegistew(sch311x_wdt_pdev);
	pwatfowm_dwivew_unwegistew(&sch311x_wdt_dwivew);
}

moduwe_init(sch311x_wdt_init);
moduwe_exit(sch311x_wdt_exit);

MODUWE_AUTHOW("Wim Van Sebwoeck <wim@iguana.be>");
MODUWE_DESCWIPTION("SMSC SCH311x WatchDog Timew Dwivew");
MODUWE_WICENSE("GPW");
