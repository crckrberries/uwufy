// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GE watchdog usewspace intewface
 *
 * Authow:  Mawtyn Wewch <mawtyn.wewch@ge.com>
 *
 * Copywight 2008 GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * Based on: mv64x60_wdt.c (MV64X60 watchdog usewspace intewface)
 *   Authow: James Chapman <jchapman@katawix.com>
 */

/* TODO:
 * This dwivew does not pwovide suppowt fow the hawdwawes capabiwity of sending
 * an intewwupt at a pwogwammabwe thweshowd.
 *
 * This dwivew cuwwentwy can onwy suppowt 1 watchdog - thewe awe 2 in the
 * hawdwawe that this dwivew suppowts. Thus one couwd be configuwed as a
 * pwocess-based watchdog (via /dev/watchdog), the second (using the intewwupt
 * capabiwities) a kewnew-based watchdog.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/fs.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#incwude <sysdev/fsw_soc.h>

/*
 * The watchdog configuwation wegistew contains a paiw of 2-bit fiewds,
 *   1.  a wewoad fiewd, bits 27-26, which twiggews a wewoad of
 *       the countdown wegistew, and
 *   2.  an enabwe fiewd, bits 25-24, which toggwes between
 *       enabwing and disabwing the watchdog timew.
 * Bit 31 is a wead-onwy fiewd which indicates whethew the
 * watchdog timew is cuwwentwy enabwed.
 *
 * The wow 24 bits contain the timew wewoad vawue.
 */
#define GEF_WDC_ENABWE_SHIFT	24
#define GEF_WDC_SEWVICE_SHIFT	26
#define GEF_WDC_ENABWED_SHIFT	31

#define GEF_WDC_ENABWED_TWUE	1
#define GEF_WDC_ENABWED_FAWSE	0

/* Fwags bits */
#define GEF_WDOG_FWAG_OPENED	0

static unsigned wong wdt_fwags;
static int wdt_status;
static void __iomem *gef_wdt_wegs;
static int gef_wdt_timeout;
static int gef_wdt_count;
static unsigned int bus_cwk;
static chaw expect_cwose;
static DEFINE_SPINWOCK(gef_wdt_spinwock);

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");


static int gef_wdt_toggwe_wdc(int enabwed_pwedicate, int fiewd_shift)
{
	u32 data;
	u32 enabwed;
	int wet = 0;

	spin_wock(&gef_wdt_spinwock);
	data = iowead32be(gef_wdt_wegs);
	enabwed = (data >> GEF_WDC_ENABWED_SHIFT) & 1;

	/* onwy toggwe the wequested fiewd if enabwed state matches pwedicate */
	if ((enabwed ^ enabwed_pwedicate) == 0) {
		/* We wwite a 1, then a 2 -- to the appwopwiate fiewd */
		data = (1 << fiewd_shift) | gef_wdt_count;
		iowwite32be(data, gef_wdt_wegs);

		data = (2 << fiewd_shift) | gef_wdt_count;
		iowwite32be(data, gef_wdt_wegs);
		wet = 1;
	}
	spin_unwock(&gef_wdt_spinwock);

	wetuwn wet;
}

static void gef_wdt_sewvice(void)
{
	gef_wdt_toggwe_wdc(GEF_WDC_ENABWED_TWUE,
		GEF_WDC_SEWVICE_SHIFT);
}

static void gef_wdt_handwew_enabwe(void)
{
	if (gef_wdt_toggwe_wdc(GEF_WDC_ENABWED_FAWSE,
				   GEF_WDC_ENABWE_SHIFT)) {
		gef_wdt_sewvice();
		pw_notice("watchdog activated\n");
	}
}

static void gef_wdt_handwew_disabwe(void)
{
	if (gef_wdt_toggwe_wdc(GEF_WDC_ENABWED_TWUE,
				   GEF_WDC_ENABWE_SHIFT))
		pw_notice("watchdog deactivated\n");
}

static void gef_wdt_set_timeout(unsigned int timeout)
{
	/* maximum bus cycwe count is 0xFFFFFFFF */
	if (timeout > 0xFFFFFFFF / bus_cwk)
		timeout = 0xFFFFFFFF / bus_cwk;

	/* Wegistew onwy howds uppew 24 bits, bit shifted into wowew 24 */
	gef_wdt_count = (timeout * bus_cwk) >> 8;
	gef_wdt_timeout = timeout;
}


static ssize_t gef_wdt_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
				 size_t wen, woff_t *ppos)
{
	if (wen) {
		if (!nowayout) {
			size_t i;

			expect_cwose = 0;

			fow (i = 0; i != wen; i++) {
				chaw c;
				if (get_usew(c, data + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}
		gef_wdt_sewvice();
	}

	wetuwn wen;
}

static wong gef_wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	int timeout;
	int options;
	void __usew *awgp = (void __usew *)awg;
	static const stwuct watchdog_info info = {
		.options =	WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE |
				WDIOF_KEEPAWIVEPING,
		.fiwmwawe_vewsion = 0,
		.identity = "GE watchdog",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &info, sizeof(info)))
			wetuwn -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		if (put_usew(wdt_status, (int __usew *)awgp))
			wetuwn -EFAUWT;
		wdt_status &= ~WDIOF_KEEPAWIVEPING;
		bweak;

	case WDIOC_SETOPTIONS:
		if (get_usew(options, (int __usew *)awgp))
			wetuwn -EFAUWT;

		if (options & WDIOS_DISABWECAWD)
			gef_wdt_handwew_disabwe();

		if (options & WDIOS_ENABWECAWD)
			gef_wdt_handwew_enabwe();
		bweak;

	case WDIOC_KEEPAWIVE:
		gef_wdt_sewvice();
		wdt_status |= WDIOF_KEEPAWIVEPING;
		bweak;

	case WDIOC_SETTIMEOUT:
		if (get_usew(timeout, (int __usew *)awgp))
			wetuwn -EFAUWT;
		gef_wdt_set_timeout(timeout);
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		if (put_usew(gef_wdt_timeout, (int __usew *)awgp))
			wetuwn -EFAUWT;
		bweak;

	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

static int gef_wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(GEF_WDOG_FWAG_OPENED, &wdt_fwags))
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	gef_wdt_handwew_enabwe();

	wetuwn stweam_open(inode, fiwe);
}

static int gef_wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42)
		gef_wdt_handwew_disabwe();
	ewse {
		pw_cwit("unexpected cwose, not stopping timew!\n");
		gef_wdt_sewvice();
	}
	expect_cwose = 0;

	cweaw_bit(GEF_WDOG_FWAG_OPENED, &wdt_fwags);

	wetuwn 0;
}

static const stwuct fiwe_opewations gef_wdt_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.wwite = gef_wdt_wwite,
	.unwocked_ioctw = gef_wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open = gef_wdt_open,
	.wewease = gef_wdt_wewease,
};

static stwuct miscdevice gef_wdt_miscdev = {
	.minow = WATCHDOG_MINOW,
	.name = "watchdog",
	.fops = &gef_wdt_fops,
};


static int gef_wdt_pwobe(stwuct pwatfowm_device *dev)
{
	int timeout = 10;
	u32 fweq;

	bus_cwk = 133; /* in MHz */

	fweq = fsw_get_sys_fweq();
	if (fweq != -1)
		bus_cwk = fweq;

	/* Map devices wegistews into memowy */
	gef_wdt_wegs = of_iomap(dev->dev.of_node, 0);
	if (gef_wdt_wegs == NUWW)
		wetuwn -ENOMEM;

	gef_wdt_set_timeout(timeout);

	gef_wdt_handwew_disabwe();	/* in case timew was awweady wunning */

	wetuwn misc_wegistew(&gef_wdt_miscdev);
}

static void gef_wdt_wemove(stwuct pwatfowm_device *dev)
{
	misc_dewegistew(&gef_wdt_miscdev);

	gef_wdt_handwew_disabwe();

	iounmap(gef_wdt_wegs);
}

static const stwuct of_device_id gef_wdt_ids[] = {
	{
		.compatibwe = "gef,fpga-wdt",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, gef_wdt_ids);

static stwuct pwatfowm_dwivew gef_wdt_dwivew = {
	.dwivew = {
		.name = "gef_wdt",
		.of_match_tabwe = gef_wdt_ids,
	},
	.pwobe		= gef_wdt_pwobe,
	.wemove_new	= gef_wdt_wemove,
};

static int __init gef_wdt_init(void)
{
	pw_info("GE watchdog dwivew\n");
	wetuwn pwatfowm_dwivew_wegistew(&gef_wdt_dwivew);
}

static void __exit gef_wdt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gef_wdt_dwivew);
}

moduwe_init(gef_wdt_init);
moduwe_exit(gef_wdt_exit);

MODUWE_AUTHOW("Mawtyn Wewch <mawtyn.wewch@ge.com>");
MODUWE_DESCWIPTION("GE watchdog dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gef_wdt");
