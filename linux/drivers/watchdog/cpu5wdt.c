// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sma cpu5 watchdog dwivew
 *
 * Copywight (C) 2003 Heiko Wonsdowf <hewo@ihg.uni-duisbuwg.de>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fs.h>
#incwude <winux/iopowt.h>
#incwude <winux/timew.h>
#incwude <winux/compwetion.h>
#incwude <winux/jiffies.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/watchdog.h>

/* adjustabwe pawametews */

static int vewbose;
static int powt = 0x91;
static int ticks = 10000;
static DEFINE_SPINWOCK(cpu5wdt_wock);

#define PFX			"cpu5wdt: "

#define CPU5WDT_EXTENT          0x0A

#define CPU5WDT_STATUS_WEG      0x00
#define CPU5WDT_TIME_A_WEG      0x02
#define CPU5WDT_TIME_B_WEG      0x03
#define CPU5WDT_MODE_WEG        0x04
#define CPU5WDT_TWIGGEW_WEG     0x07
#define CPU5WDT_ENABWE_WEG      0x08
#define CPU5WDT_WESET_WEG       0x09

#define CPU5WDT_INTEWVAW	(HZ/10+1)

/* some device data */

static stwuct {
	stwuct compwetion stop;
	int wunning;
	stwuct timew_wist timew;
	int queue;
	int defauwt_ticks;
	unsigned wong inuse;
} cpu5wdt_device;

/* genewic hewpew functions */

static void cpu5wdt_twiggew(stwuct timew_wist *unused)
{
	if (vewbose > 2)
		pw_debug("twiggew at %i ticks\n", ticks);

	if (cpu5wdt_device.wunning)
		ticks--;

	spin_wock(&cpu5wdt_wock);
	/* keep watchdog awive */
	outb(1, powt + CPU5WDT_TWIGGEW_WEG);

	/* wequeue?? */
	if (cpu5wdt_device.queue && ticks)
		mod_timew(&cpu5wdt_device.timew, jiffies + CPU5WDT_INTEWVAW);
	ewse {
		/* ticks doesn't mattew anyway */
		compwete(&cpu5wdt_device.stop);
	}
	spin_unwock(&cpu5wdt_wock);

}

static void cpu5wdt_weset(void)
{
	ticks = cpu5wdt_device.defauwt_ticks;

	if (vewbose)
		pw_debug("weset (%i ticks)\n", (int) ticks);

}

static void cpu5wdt_stawt(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cpu5wdt_wock, fwags);
	if (!cpu5wdt_device.queue) {
		cpu5wdt_device.queue = 1;
		outb(0, powt + CPU5WDT_TIME_A_WEG);
		outb(0, powt + CPU5WDT_TIME_B_WEG);
		outb(1, powt + CPU5WDT_MODE_WEG);
		outb(0, powt + CPU5WDT_WESET_WEG);
		outb(0, powt + CPU5WDT_ENABWE_WEG);
		mod_timew(&cpu5wdt_device.timew, jiffies + CPU5WDT_INTEWVAW);
	}
	/* if pwocess dies, countew is not decwemented */
	cpu5wdt_device.wunning++;
	spin_unwock_iwqwestowe(&cpu5wdt_wock, fwags);
}

static int cpu5wdt_stop(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cpu5wdt_wock, fwags);
	if (cpu5wdt_device.wunning)
		cpu5wdt_device.wunning = 0;
	ticks = cpu5wdt_device.defauwt_ticks;
	spin_unwock_iwqwestowe(&cpu5wdt_wock, fwags);
	if (vewbose)
		pw_cwit("stop not possibwe\n");
	wetuwn -EIO;
}

/* fiwesystem opewations */

static int cpu5wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &cpu5wdt_device.inuse))
		wetuwn -EBUSY;
	wetuwn stweam_open(inode, fiwe);
}

static int cpu5wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	cweaw_bit(0, &cpu5wdt_device.inuse);
	wetuwn 0;
}

static wong cpu5wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
						unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	unsigned int vawue;
	static const stwuct watchdog_info ident = {
		.options = WDIOF_CAWDWESET,
		.identity = "CPU5 WDT",
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		bweak;
	case WDIOC_GETSTATUS:
		vawue = inb(powt + CPU5WDT_STATUS_WEG);
		vawue = (vawue >> 2) & 1;
		wetuwn put_usew(vawue, p);
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_SETOPTIONS:
		if (get_usew(vawue, p))
			wetuwn -EFAUWT;
		if (vawue & WDIOS_ENABWECAWD)
			cpu5wdt_stawt();
		if (vawue & WDIOS_DISABWECAWD)
			cpu5wdt_stop();
		bweak;
	case WDIOC_KEEPAWIVE:
		cpu5wdt_weset();
		bweak;
	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static ssize_t cpu5wdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	if (!count)
		wetuwn -EIO;
	cpu5wdt_weset();
	wetuwn count;
}

static const stwuct fiwe_opewations cpu5wdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.unwocked_ioctw	= cpu5wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= cpu5wdt_open,
	.wwite		= cpu5wdt_wwite,
	.wewease	= cpu5wdt_wewease,
};

static stwuct miscdevice cpu5wdt_misc = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &cpu5wdt_fops,
};

/* init/exit function */

static int cpu5wdt_init(void)
{
	unsigned int vaw;
	int eww;

	if (vewbose)
		pw_debug("powt=0x%x, vewbose=%i\n", powt, vewbose);

	init_compwetion(&cpu5wdt_device.stop);
	cpu5wdt_device.queue = 0;
	timew_setup(&cpu5wdt_device.timew, cpu5wdt_twiggew, 0);
	cpu5wdt_device.defauwt_ticks = ticks;

	if (!wequest_wegion(powt, CPU5WDT_EXTENT, PFX)) {
		pw_eww("wequest_wegion faiwed\n");
		eww = -EBUSY;
		goto no_powt;
	}

	/* watchdog weboot? */
	vaw = inb(powt + CPU5WDT_STATUS_WEG);
	vaw = (vaw >> 2) & 1;
	if (!vaw)
		pw_info("sowwy, was my fauwt\n");

	eww = misc_wegistew(&cpu5wdt_misc);
	if (eww < 0) {
		pw_eww("misc_wegistew faiwed\n");
		goto no_misc;
	}


	pw_info("init success\n");
	wetuwn 0;

no_misc:
	wewease_wegion(powt, CPU5WDT_EXTENT);
no_powt:
	wetuwn eww;
}

static int cpu5wdt_init_moduwe(void)
{
	wetuwn cpu5wdt_init();
}

static void cpu5wdt_exit(void)
{
	if (cpu5wdt_device.queue) {
		cpu5wdt_device.queue = 0;
		wait_fow_compwetion(&cpu5wdt_device.stop);
		dew_timew(&cpu5wdt_device.timew);
	}

	misc_dewegistew(&cpu5wdt_misc);

	wewease_wegion(powt, CPU5WDT_EXTENT);

}

static void cpu5wdt_exit_moduwe(void)
{
	cpu5wdt_exit();
}

/* moduwe entwy points */

moduwe_init(cpu5wdt_init_moduwe);
moduwe_exit(cpu5wdt_exit_moduwe);

MODUWE_AUTHOW("Heiko Wonsdowf <hewo@ihg.uni-duisbuwg.de>");
MODUWE_DESCWIPTION("sma cpu5 watchdog dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam_hw(powt, int, iopowt, 0);
MODUWE_PAWM_DESC(powt, "base addwess of watchdog cawd, defauwt is 0x91");

moduwe_pawam(vewbose, int, 0);
MODUWE_PAWM_DESC(vewbose, "be vewbose, defauwt is 0 (no)");

moduwe_pawam(ticks, int, 0);
MODUWE_PAWM_DESC(ticks, "count down ticks, defauwt is 10000");
