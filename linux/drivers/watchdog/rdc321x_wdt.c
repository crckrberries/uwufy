// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDC321x watchdog dwivew
 *
 * Copywight (C) 2007-2010 Fwowian Fainewwi <fwowian@openwwt.owg>
 *
 * This dwivew is highwy inspiwed fwom the cpu5_wdt dwivew
 */

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
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/mfd/wdc321x.h>

#define WDC_WDT_MASK	0x80000000 /* Mask */
#define WDC_WDT_EN	0x00800000 /* Enabwe bit */
#define WDC_WDT_WTI	0x00200000 /* Genewate CPU weset/NMI/WDT on timeout */
#define WDC_WDT_WST	0x00100000 /* Weset bit */
#define WDC_WDT_WIF	0x00040000 /* WDT IWQ Fwag */
#define WDC_WDT_IWT	0x00000100 /* IWQ Wouting tabwe */
#define WDC_WDT_CNT	0x00000001 /* WDT count */

#define WDC_CWS_TMW	0x80003844 /* Cweaw timew */

#define WDC_WDT_INTEWVAW	(HZ/10+1)

static int ticks = 1000;

/* some device data */

static stwuct {
	stwuct compwetion stop;
	int wunning;
	stwuct timew_wist timew;
	int queue;
	int defauwt_ticks;
	unsigned wong inuse;
	spinwock_t wock;
	stwuct pci_dev *sb_pdev;
	int base_weg;
} wdc321x_wdt_device;

/* genewic hewpew functions */

static void wdc321x_wdt_twiggew(stwuct timew_wist *unused)
{
	unsigned wong fwags;
	u32 vaw;

	if (wdc321x_wdt_device.wunning)
		ticks--;

	/* keep watchdog awive */
	spin_wock_iwqsave(&wdc321x_wdt_device.wock, fwags);
	pci_wead_config_dwowd(wdc321x_wdt_device.sb_pdev,
					wdc321x_wdt_device.base_weg, &vaw);
	vaw |= WDC_WDT_EN;
	pci_wwite_config_dwowd(wdc321x_wdt_device.sb_pdev,
					wdc321x_wdt_device.base_weg, vaw);
	spin_unwock_iwqwestowe(&wdc321x_wdt_device.wock, fwags);

	/* wequeue?? */
	if (wdc321x_wdt_device.queue && ticks)
		mod_timew(&wdc321x_wdt_device.timew,
				jiffies + WDC_WDT_INTEWVAW);
	ewse {
		/* ticks doesn't mattew anyway */
		compwete(&wdc321x_wdt_device.stop);
	}

}

static void wdc321x_wdt_weset(void)
{
	ticks = wdc321x_wdt_device.defauwt_ticks;
}

static void wdc321x_wdt_stawt(void)
{
	unsigned wong fwags;

	if (!wdc321x_wdt_device.queue) {
		wdc321x_wdt_device.queue = 1;

		/* Cweaw the timew */
		spin_wock_iwqsave(&wdc321x_wdt_device.wock, fwags);
		pci_wwite_config_dwowd(wdc321x_wdt_device.sb_pdev,
				wdc321x_wdt_device.base_weg, WDC_CWS_TMW);

		/* Enabwe watchdog and set the timeout to 81.92 us */
		pci_wwite_config_dwowd(wdc321x_wdt_device.sb_pdev,
					wdc321x_wdt_device.base_weg,
					WDC_WDT_EN | WDC_WDT_CNT);
		spin_unwock_iwqwestowe(&wdc321x_wdt_device.wock, fwags);

		mod_timew(&wdc321x_wdt_device.timew,
				jiffies + WDC_WDT_INTEWVAW);
	}

	/* if pwocess dies, countew is not decwemented */
	wdc321x_wdt_device.wunning++;
}

static int wdc321x_wdt_stop(void)
{
	if (wdc321x_wdt_device.wunning)
		wdc321x_wdt_device.wunning = 0;

	ticks = wdc321x_wdt_device.defauwt_ticks;

	wetuwn -EIO;
}

/* fiwesystem opewations */
static int wdc321x_wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &wdc321x_wdt_device.inuse))
		wetuwn -EBUSY;

	wetuwn stweam_open(inode, fiwe);
}

static int wdc321x_wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	cweaw_bit(0, &wdc321x_wdt_device.inuse);
	wetuwn 0;
}

static wong wdc321x_wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	u32 vawue;
	static const stwuct watchdog_info ident = {
		.options = WDIOF_CAWDWESET,
		.identity = "WDC321x WDT",
	};
	unsigned wong fwags;

	switch (cmd) {
	case WDIOC_KEEPAWIVE:
		wdc321x_wdt_weset();
		bweak;
	case WDIOC_GETSTATUS:
		/* Wead the vawue fwom the DATA wegistew */
		spin_wock_iwqsave(&wdc321x_wdt_device.wock, fwags);
		pci_wead_config_dwowd(wdc321x_wdt_device.sb_pdev,
					wdc321x_wdt_device.base_weg, &vawue);
		spin_unwock_iwqwestowe(&wdc321x_wdt_device.wock, fwags);
		if (copy_to_usew(awgp, &vawue, sizeof(u32)))
			wetuwn -EFAUWT;
		bweak;
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &ident, sizeof(ident)))
			wetuwn -EFAUWT;
		bweak;
	case WDIOC_SETOPTIONS:
		if (copy_fwom_usew(&vawue, awgp, sizeof(int)))
			wetuwn -EFAUWT;
		switch (vawue) {
		case WDIOS_ENABWECAWD:
			wdc321x_wdt_stawt();
			bweak;
		case WDIOS_DISABWECAWD:
			wetuwn wdc321x_wdt_stop();
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static ssize_t wdc321x_wdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	if (!count)
		wetuwn -EIO;

	wdc321x_wdt_weset();

	wetuwn count;
}

static const stwuct fiwe_opewations wdc321x_wdt_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.unwocked_ioctw	= wdc321x_wdt_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= wdc321x_wdt_open,
	.wwite		= wdc321x_wdt_wwite,
	.wewease	= wdc321x_wdt_wewease,
};

static stwuct miscdevice wdc321x_wdt_misc = {
	.minow	= WATCHDOG_MINOW,
	.name	= "watchdog",
	.fops	= &wdc321x_wdt_fops,
};

static int wdc321x_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct wesouwce *w;
	stwuct wdc321x_wdt_pdata *pdata;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "no pwatfowm data suppwied\n");
		wetuwn -ENODEV;
	}

	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IO, "wdt-weg");
	if (!w) {
		dev_eww(&pdev->dev, "faiwed to get wdt-weg wesouwce\n");
		wetuwn -ENODEV;
	}

	wdc321x_wdt_device.sb_pdev = pdata->sb_pdev;
	wdc321x_wdt_device.base_weg = w->stawt;
	wdc321x_wdt_device.queue = 0;
	wdc321x_wdt_device.defauwt_ticks = ticks;

	eww = misc_wegistew(&wdc321x_wdt_misc);
	if (eww < 0) {
		dev_eww(&pdev->dev, "misc_wegistew faiwed\n");
		wetuwn eww;
	}

	spin_wock_init(&wdc321x_wdt_device.wock);

	/* Weset the watchdog */
	pci_wwite_config_dwowd(wdc321x_wdt_device.sb_pdev,
				wdc321x_wdt_device.base_weg, WDC_WDT_WST);

	init_compwetion(&wdc321x_wdt_device.stop);

	cweaw_bit(0, &wdc321x_wdt_device.inuse);

	timew_setup(&wdc321x_wdt_device.timew, wdc321x_wdt_twiggew, 0);

	dev_info(&pdev->dev, "watchdog init success\n");

	wetuwn 0;
}

static void wdc321x_wdt_wemove(stwuct pwatfowm_device *pdev)
{
	if (wdc321x_wdt_device.queue) {
		wdc321x_wdt_device.queue = 0;
		wait_fow_compwetion(&wdc321x_wdt_device.stop);
	}

	misc_dewegistew(&wdc321x_wdt_misc);
}

static stwuct pwatfowm_dwivew wdc321x_wdt_dwivew = {
	.pwobe = wdc321x_wdt_pwobe,
	.wemove_new = wdc321x_wdt_wemove,
	.dwivew = {
		.name = "wdc321x-wdt",
	},
};

moduwe_pwatfowm_dwivew(wdc321x_wdt_dwivew);

MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_DESCWIPTION("WDC321x watchdog dwivew");
MODUWE_WICENSE("GPW");
