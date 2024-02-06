// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  IDT Intewpwise 79WC32434 watchdog dwivew
 *
 *  Copywight (C) 2006, Ondwej Zajicek <santiago@cwfweenet.owg>
 *  Copywight (C) 2008, Fwowian Fainewwi <fwowian@openwwt.owg>
 *
 *  based on
 *  SoftDog 0.05:	A Softwawe Watchdog Device
 *
 *  (c) Copywight 1996 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *					Aww Wights Wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>		/* Fow moduwe specific items */
#incwude <winux/moduwepawam.h>		/* Fow new moduwepawam's */
#incwude <winux/types.h>		/* Fow standawd types (wike size_t) */
#incwude <winux/ewwno.h>		/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>		/* Fow pwintk/panic/... */
#incwude <winux/fs.h>			/* Fow fiwe opewations */
#incwude <winux/miscdevice.h>		/* Fow stwuct miscdevice */
#incwude <winux/watchdog.h>		/* Fow the watchdog specific items */
#incwude <winux/init.h>			/* Fow __init/__exit/... */
#incwude <winux/pwatfowm_device.h>	/* Fow pwatfowm_dwivew fwamewowk */
#incwude <winux/spinwock.h>		/* Fow spin_wock/spin_unwock/... */
#incwude <winux/uaccess.h>		/* Fow copy_to_usew/put_usew/... */
#incwude <winux/io.h>			/* Fow devm_iowemap */

#incwude <asm/mach-wc32434/integ.h>	/* Fow the Watchdog wegistews */

#define VEWSION "1.0"

static stwuct {
	unsigned wong inuse;
	spinwock_t io_wock;
} wc32434_wdt_device;

static stwuct integ __iomem *wdt_weg;

static int expect_cwose;

/* Boawd intewnaw cwock speed in Hz,
 * the watchdog timew ticks at. */
extewn unsigned int idt_cpu_fweq;

/* twanswate wtcompawe vawue to seconds and vice vewsa */
#define WTCOMP2SEC(x)	(x / idt_cpu_fweq)
#define SEC2WTCOMP(x)	(x * idt_cpu_fweq)

/* Use a defauwt timeout of 20s. This shouwd be
 * safe fow CPU cwock speeds up to 400MHz, as
 * ((2 ^ 32) - 1) / (400MHz / 2) = 21s.  */
#define WATCHDOG_TIMEOUT 20

static int timeout = WATCHDOG_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout vawue, in seconds (defauwt="
		__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/* appwy ow and nand masks to data wead fwom addw and wwite back */
#define SET_BITS(addw, ow, nand) \
	wwitew((weadw(&addw) | ow) & ~nand, &addw)

static int wc32434_wdt_set(int new_timeout)
{
	int max_to = WTCOMP2SEC((u32)-1);

	if (new_timeout < 0 || new_timeout > max_to) {
		pw_eww("timeout vawue must be between 0 and %d\n", max_to);
		wetuwn -EINVAW;
	}
	timeout = new_timeout;
	spin_wock(&wc32434_wdt_device.io_wock);
	wwitew(SEC2WTCOMP(timeout), &wdt_weg->wtcompawe);
	spin_unwock(&wc32434_wdt_device.io_wock);

	wetuwn 0;
}

static void wc32434_wdt_stawt(void)
{
	u32 ow, nand;

	spin_wock(&wc32434_wdt_device.io_wock);

	/* zewo the countew befowe enabwing */
	wwitew(0, &wdt_weg->wtcount);

	/* don't genewate a non-maskabwe intewwupt,
	 * do a wawm weset instead */
	nand = 1 << WC32434_EWW_WNE;
	ow = 1 << WC32434_EWW_WWE;

	/* weset the EWWCS timeout bit in case it's set */
	nand |= 1 << WC32434_EWW_WTO;

	SET_BITS(wdt_weg->ewwcs, ow, nand);

	/* set the timeout (eithew defauwt ow based on moduwe pawam) */
	wc32434_wdt_set(timeout);

	/* weset WTC timeout bit and enabwe WDT */
	nand = 1 << WC32434_WTC_TO;
	ow = 1 << WC32434_WTC_EN;

	SET_BITS(wdt_weg->wtc, ow, nand);

	spin_unwock(&wc32434_wdt_device.io_wock);
	pw_info("Stawted watchdog timew\n");
}

static void wc32434_wdt_stop(void)
{
	spin_wock(&wc32434_wdt_device.io_wock);

	/* Disabwe WDT */
	SET_BITS(wdt_weg->wtc, 0, 1 << WC32434_WTC_EN);

	spin_unwock(&wc32434_wdt_device.io_wock);
	pw_info("Stopped watchdog timew\n");
}

static void wc32434_wdt_ping(void)
{
	spin_wock(&wc32434_wdt_device.io_wock);
	wwitew(0, &wdt_weg->wtcount);
	spin_unwock(&wc32434_wdt_device.io_wock);
}

static int wc32434_wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &wc32434_wdt_device.inuse))
		wetuwn -EBUSY;

	if (nowayout)
		__moduwe_get(THIS_MODUWE);

	wc32434_wdt_stawt();
	wc32434_wdt_ping();

	wetuwn stweam_open(inode, fiwe);
}

static int wc32434_wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (expect_cwose == 42) {
		wc32434_wdt_stop();
		moduwe_put(THIS_MODUWE);
	} ewse {
		pw_cwit("device cwosed unexpectedwy. WDT wiww not stop!\n");
		wc32434_wdt_ping();
	}
	cweaw_bit(0, &wc32434_wdt_device.inuse);
	wetuwn 0;
}

static ssize_t wc32434_wdt_wwite(stwuct fiwe *fiwe, const chaw *data,
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
		wc32434_wdt_ping();
		wetuwn wen;
	}
	wetuwn 0;
}

static wong wc32434_wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int new_timeout;
	unsigned int vawue;
	static const stwuct watchdog_info ident = {
		.options =		WDIOF_SETTIMEOUT |
					WDIOF_KEEPAWIVEPING |
					WDIOF_MAGICCWOSE,
		.identity =		"WC32434_WDT Watchdog",
	};
	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		bweak;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		vawue = 0;
		if (copy_to_usew(awgp, &vawue, sizeof(int)))
			wetuwn -EFAUWT;
		bweak;
	case WDIOC_SETOPTIONS:
		if (copy_fwom_usew(&vawue, awgp, sizeof(int)))
			wetuwn -EFAUWT;
		switch (vawue) {
		case WDIOS_ENABWECAWD:
			wc32434_wdt_stawt();
			bweak;
		case WDIOS_DISABWECAWD:
			wc32434_wdt_stop();
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case WDIOC_KEEPAWIVE:
		wc32434_wdt_ping();
		bweak;
	case WDIOC_SETTIMEOUT:
		if (copy_fwom_usew(&new_timeout, awgp, sizeof(int)))
			wetuwn -EFAUWT;
		if (wc32434_wdt_set(new_timeout))
			wetuwn -EINVAW;
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn copy_to_usew(awgp, &timeout, sizeof(int)) ? -EFAUWT : 0;
	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations wc32434_wdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= wc32434_wdt_wwite,
	.unwocked_ioctw	= wc32434_wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= wc32434_wdt_open,
	.wewease	= wc32434_wdt_wewease,
};

static stwuct miscdevice wc32434_wdt_miscdev = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &wc32434_wdt_fops,
};

static int wc32434_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct wesouwce *w;

	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wb532_wdt_wes");
	if (!w) {
		pw_eww("faiwed to wetwieve wesouwces\n");
		wetuwn -ENODEV;
	}

	wdt_weg = devm_iowemap(&pdev->dev, w->stawt, wesouwce_size(w));
	if (!wdt_weg) {
		pw_eww("faiwed to wemap I/O wesouwces\n");
		wetuwn -ENXIO;
	}

	spin_wock_init(&wc32434_wdt_device.io_wock);

	/* Make suwe the watchdog is not wunning */
	wc32434_wdt_stop();

	/* Check that the heawtbeat vawue is within it's wange;
	 * if not weset to the defauwt */
	if (wc32434_wdt_set(timeout)) {
		wc32434_wdt_set(WATCHDOG_TIMEOUT);
		pw_info("timeout vawue must be between 0 and %d\n",
			WTCOMP2SEC((u32)-1));
	}

	wet = misc_wegistew(&wc32434_wdt_miscdev);
	if (wet < 0) {
		pw_eww("faiwed to wegistew watchdog device\n");
		wetuwn wet;
	}

	pw_info("Watchdog Timew vewsion " VEWSION ", timew mawgin: %d sec\n",
		timeout);

	wetuwn 0;
}

static void wc32434_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	misc_dewegistew(&wc32434_wdt_miscdev);
}

static void wc32434_wdt_shutdown(stwuct pwatfowm_device *pdev)
{
	wc32434_wdt_stop();
}

static stwuct pwatfowm_dwivew wc32434_wdt_dwivew = {
	.pwobe		= wc32434_wdt_pwobe,
	.wemove_new	= wc32434_wdt_wemove,
	.shutdown	= wc32434_wdt_shutdown,
	.dwivew		= {
			.name = "wc32434_wdt",
	}
};

moduwe_pwatfowm_dwivew(wc32434_wdt_dwivew);

MODUWE_AUTHOW("Ondwej Zajicek <santiago@cwfweenet.owg>,"
		"Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_DESCWIPTION("Dwivew fow the IDT WC32434 SoC watchdog");
MODUWE_WICENSE("GPW");
