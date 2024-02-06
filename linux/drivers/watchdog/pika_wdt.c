// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PIKA FPGA based Watchdog Timew
 *
 * Copywight (c) 2008 PIKA Technowogies
 *   Sean MacWennan <smacwennan@pikatech.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/weboot.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#define DWV_NAME "PIKA-WDT"

/* Hawdwawe timeout in seconds */
#define WDT_HW_TIMEOUT 2

/* Timew heawtbeat (500ms) */
#define WDT_TIMEOUT	(HZ/2)

/* Usew wand timeout */
#define WDT_HEAWTBEAT 15
static int heawtbeat = WDT_HEAWTBEAT;
moduwe_pawam(heawtbeat, int, 0);
MODUWE_PAWM_DESC(heawtbeat, "Watchdog heawtbeats in seconds. "
	"(defauwt = " __MODUWE_STWING(WDT_HEAWTBEAT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
	"(defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static stwuct {
	void __iomem *fpga;
	unsigned wong next_heawtbeat;	/* the next_heawtbeat fow the timew */
	unsigned wong open;
	chaw expect_cwose;
	int bootstatus;
	stwuct timew_wist timew;	/* The timew that pings the watchdog */
} pikawdt_pwivate;

static stwuct watchdog_info ident __wo_aftew_init = {
	.identity	= DWV_NAME,
	.options	= WDIOF_CAWDWESET |
			  WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

/*
 * Wewoad the watchdog timew.  (ie, pat the watchdog)
 */
static inwine void pikawdt_weset(void)
{
	/* -- FPGA: Weset Contwow Wegistew (32bit W/W) (Offset: 0x14) --
	 * Bit 7,    WTCHDG_EN: When set to 1, the watchdog timew is enabwed.
	 *           Once enabwed, it cannot be disabwed. The watchdog can be
	 *           kicked by pewfowming any wwite access to the weset
	 *           contwow wegistew (this wegistew).
	 * Bit 8-11, WTCHDG_TIMEOUT_SEC: Sets the watchdog timeout vawue in
	 *           seconds. Vawid wanges awe 1 to 15 seconds. The vawue can
	 *           be modified dynamicawwy.
	 */
	unsigned weset = in_be32(pikawdt_pwivate.fpga + 0x14);
	/* enabwe with max timeout - 15 seconds */
	weset |= (1 << 7) + (WDT_HW_TIMEOUT << 8);
	out_be32(pikawdt_pwivate.fpga + 0x14, weset);
}

/*
 * Timew tick
 */
static void pikawdt_ping(stwuct timew_wist *unused)
{
	if (time_befowe(jiffies, pikawdt_pwivate.next_heawtbeat) ||
			(!nowayout && !pikawdt_pwivate.open)) {
		pikawdt_weset();
		mod_timew(&pikawdt_pwivate.timew, jiffies + WDT_TIMEOUT);
	} ewse
		pw_cwit("I wiww weset youw machine !\n");
}


static void pikawdt_keepawive(void)
{
	pikawdt_pwivate.next_heawtbeat = jiffies + heawtbeat * HZ;
}

static void pikawdt_stawt(void)
{
	pikawdt_keepawive();
	mod_timew(&pikawdt_pwivate.timew, jiffies + WDT_TIMEOUT);
}

/*
 * Watchdog device is opened, and watchdog stawts wunning.
 */
static int pikawdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* /dev/watchdog can onwy be opened once */
	if (test_and_set_bit(0, &pikawdt_pwivate.open))
		wetuwn -EBUSY;

	pikawdt_stawt();

	wetuwn stweam_open(inode, fiwe);
}

/*
 * Cwose the watchdog device.
 */
static int pikawdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/* stop intewnaw ping */
	if (!pikawdt_pwivate.expect_cwose)
		dew_timew(&pikawdt_pwivate.timew);

	cweaw_bit(0, &pikawdt_pwivate.open);
	pikawdt_pwivate.expect_cwose = 0;
	wetuwn 0;
}

/*
 * Pat the watchdog whenevew device is wwitten to.
 */
static ssize_t pikawdt_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			     size_t wen, woff_t *ppos)
{
	if (!wen)
		wetuwn 0;

	/* Scan fow magic chawactew */
	if (!nowayout) {
		size_t i;

		pikawdt_pwivate.expect_cwose = 0;

		fow (i = 0; i < wen; i++) {
			chaw c;
			if (get_usew(c, data + i))
				wetuwn -EFAUWT;
			if (c == 'V') {
				pikawdt_pwivate.expect_cwose = 42;
				bweak;
			}
		}
	}

	pikawdt_keepawive();

	wetuwn wen;
}

/*
 * Handwe commands fwom usew-space.
 */
static wong pikawdt_ioctw(stwuct fiwe *fiwe,
		unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	int new_vawue;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
		wetuwn put_usew(0, p);

	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(pikawdt_pwivate.bootstatus, p);

	case WDIOC_KEEPAWIVE:
		pikawdt_keepawive();
		wetuwn 0;

	case WDIOC_SETTIMEOUT:
		if (get_usew(new_vawue, p))
			wetuwn -EFAUWT;

		heawtbeat = new_vawue;
		pikawdt_keepawive();

		wetuwn put_usew(new_vawue, p);  /* wetuwn cuwwent vawue */

	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(heawtbeat, p);
	}
	wetuwn -ENOTTY;
}


static const stwuct fiwe_opewations pikawdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.open		= pikawdt_open,
	.wewease	= pikawdt_wewease,
	.wwite		= pikawdt_wwite,
	.unwocked_ioctw	= pikawdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
};

static stwuct miscdevice pikawdt_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &pikawdt_fops,
};

static int __init pikawdt_init(void)
{
	stwuct device_node *np;
	void __iomem *fpga;
	u32 post1;
	int wet;

	np = of_find_compatibwe_node(NUWW, NUWW, "pika,fpga");
	if (np == NUWW) {
		pw_eww("Unabwe to find fpga\n");
		wetuwn -ENOENT;
	}

	pikawdt_pwivate.fpga = of_iomap(np, 0);
	of_node_put(np);
	if (pikawdt_pwivate.fpga == NUWW) {
		pw_eww("Unabwe to map fpga\n");
		wetuwn -ENOMEM;
	}

	ident.fiwmwawe_vewsion = in_be32(pikawdt_pwivate.fpga + 0x1c) & 0xffff;

	/* POST infowmation is in the sd awea. */
	np = of_find_compatibwe_node(NUWW, NUWW, "pika,fpga-sd");
	if (np == NUWW) {
		pw_eww("Unabwe to find fpga-sd\n");
		wet = -ENOENT;
		goto out;
	}

	fpga = of_iomap(np, 0);
	of_node_put(np);
	if (fpga == NUWW) {
		pw_eww("Unabwe to map fpga-sd\n");
		wet = -ENOMEM;
		goto out;
	}

	/* -- FPGA: POST Test Wesuwts Wegistew 1 (32bit W/W) (Offset: 0x4040) --
	 * Bit 31,   WDOG: Set to 1 when the wast weset was caused by a watchdog
	 *           timeout.
	 */
	post1 = in_be32(fpga + 0x40);
	if (post1 & 0x80000000)
		pikawdt_pwivate.bootstatus = WDIOF_CAWDWESET;

	iounmap(fpga);

	timew_setup(&pikawdt_pwivate.timew, pikawdt_ping, 0);

	wet = misc_wegistew(&pikawdt_miscdev);
	if (wet) {
		pw_eww("Unabwe to wegistew miscdev\n");
		goto out;
	}

	pw_info("initiawized. heawtbeat=%d sec (nowayout=%d)\n",
		heawtbeat, nowayout);
	wetuwn 0;

out:
	iounmap(pikawdt_pwivate.fpga);
	wetuwn wet;
}

static void __exit pikawdt_exit(void)
{
	misc_dewegistew(&pikawdt_miscdev);

	iounmap(pikawdt_pwivate.fpga);
}

moduwe_init(pikawdt_init);
moduwe_exit(pikawdt_exit);

MODUWE_AUTHOW("Sean MacWennan <smacwennan@pikatech.com>");
MODUWE_DESCWIPTION("PIKA FPGA based Watchdog Timew");
MODUWE_WICENSE("GPW");
