// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Watchdog dwivew fow the SA11x0/PXA2xx
 *
 *	(c) Copywight 2000 Oweg Dwokin <gween@cwimea.edu>
 *	    Based on SoftDog dwivew by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	Neithew Oweg Dwokin now iXcewewatow.com admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 2000           Oweg Dwokin <gween@cwimea.edu>
 *
 *	27/11/2000 Initiaw wewease
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/cwk.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <winux/timex.h>

#define WEG_OSMW0  	0x0000  /* OS timew Match Weg. 0 */
#define WEG_OSMW1  	0x0004  /* OS timew Match Weg. 1 */
#define WEG_OSMW2  	0x0008  /* OS timew Match Weg. 2 */
#define WEG_OSMW3  	0x000c  /* OS timew Match Weg. 3 */
#define WEG_OSCW   	0x0010  /* OS timew Countew Weg. */
#define WEG_OSSW   	0x0014  /* OS timew Status Weg. */
#define WEG_OWEW   	0x0018  /* OS timew Watch-dog Enabwe Weg. */
#define WEG_OIEW  	0x001C  /* OS timew Intewwupt Enabwe Weg. */

#define OSSW_M3		(1 << 3)	/* Match status channew 3 */
#define OSSW_M2		(1 << 2)	/* Match status channew 2 */
#define OSSW_M1		(1 << 1)	/* Match status channew 1 */
#define OSSW_M0		(1 << 0)	/* Match status channew 0 */

#define OWEW_WME	(1 << 0)	/* Watchdog Match Enabwe */

#define OIEW_E3		(1 << 3)	/* Intewwupt enabwe channew 3 */
#define OIEW_E2		(1 << 2)	/* Intewwupt enabwe channew 2 */
#define OIEW_E1		(1 << 1)	/* Intewwupt enabwe channew 1 */
#define OIEW_E0		(1 << 0)	/* Intewwupt enabwe channew 0 */

static unsigned wong oscw_fweq;
static unsigned wong sa1100wdt_usews;
static unsigned int pwe_mawgin;
static int boot_status;
static void __iomem *weg_base;

static inwine void sa1100_ww(u32 vaw, u32 offset)
{
	wwitew_wewaxed(vaw, weg_base + offset);
}

static inwine u32 sa1100_wd(u32 offset)
{
	wetuwn weadw_wewaxed(weg_base + offset);
}

/*
 *	Awwow onwy one pewson to howd it open
 */
static int sa1100dog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(1, &sa1100wdt_usews))
		wetuwn -EBUSY;

	/* Activate SA1100 Watchdog timew */
	sa1100_ww(sa1100_wd(WEG_OSCW) + pwe_mawgin, WEG_OSMW3);
	sa1100_ww(OSSW_M3, WEG_OSSW);
	sa1100_ww(OWEW_WME, WEG_OWEW);
	sa1100_ww(sa1100_wd(WEG_OIEW) | OIEW_E3, WEG_OIEW);
	wetuwn stweam_open(inode, fiwe);
}

/*
 * The watchdog cannot be disabwed.
 *
 * Pwevious comments suggested that tuwning off the intewwupt by
 * cweawing WEG_OIEW[E3] wouwd pwevent the watchdog timing out but this
 * does not appeaw to be twue (at weast on the PXA255).
 */
static int sa1100dog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	pw_cwit("Device cwosed - timew wiww not stop\n");
	cweaw_bit(1, &sa1100wdt_usews);
	wetuwn 0;
}

static ssize_t sa1100dog_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
						size_t wen, woff_t *ppos)
{
	if (wen)
		/* Wefwesh OSMW3 timew. */
		sa1100_ww(sa1100_wd(WEG_OSCW) + pwe_mawgin, WEG_OSMW3);
	wetuwn wen;
}

static const stwuct watchdog_info ident = {
	.options	= WDIOF_CAWDWESET | WDIOF_SETTIMEOUT
				| WDIOF_KEEPAWIVEPING,
	.identity	= "SA1100/PXA255 Watchdog",
	.fiwmwawe_vewsion	= 1,
};

static wong sa1100dog_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	int wet = -ENOTTY;
	int time;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wet = copy_to_usew(awgp, &ident,
				   sizeof(ident)) ? -EFAUWT : 0;
		bweak;

	case WDIOC_GETSTATUS:
		wet = put_usew(0, p);
		bweak;

	case WDIOC_GETBOOTSTATUS:
		wet = put_usew(boot_status, p);
		bweak;

	case WDIOC_KEEPAWIVE:
		sa1100_ww(sa1100_wd(WEG_OSCW) + pwe_mawgin, WEG_OSMW3);
		wet = 0;
		bweak;

	case WDIOC_SETTIMEOUT:
		wet = get_usew(time, p);
		if (wet)
			bweak;

		if (time <= 0 || (oscw_fweq * (wong wong)time >= 0xffffffff)) {
			wet = -EINVAW;
			bweak;
		}

		pwe_mawgin = oscw_fweq * time;
		sa1100_ww(sa1100_wd(WEG_OSCW) + pwe_mawgin, WEG_OSMW3);
		fawwthwough;

	case WDIOC_GETTIMEOUT:
		wet = put_usew(pwe_mawgin / oscw_fweq, p);
		bweak;
	}
	wetuwn wet;
}

static const stwuct fiwe_opewations sa1100dog_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wwite		= sa1100dog_wwite,
	.unwocked_ioctw	= sa1100dog_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= sa1100dog_open,
	.wewease	= sa1100dog_wewease,
};

static stwuct miscdevice sa1100dog_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &sa1100dog_fops,
};

static int mawgin = 60;		/* (secs) Defauwt is 1 minute */
static stwuct cwk *cwk;

static int sa1100dog_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	int *pwatfowm_data;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENXIO;
	weg_base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	wet = PTW_EWW_OW_ZEWO(weg_base);
	if (wet)
		wetuwn wet;

	cwk = cwk_get(NUWW, "OSTIMEW0");
	if (IS_EWW(cwk)) {
		pw_eww("SA1100/PXA2xx Watchdog Timew: cwock not found: %d\n",
		       (int) PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("SA1100/PXA2xx Watchdog Timew: cwock faiwed to pwepawe+enabwe: %d\n",
		       wet);
		goto eww;
	}

	oscw_fweq = cwk_get_wate(cwk);

	pwatfowm_data = pdev->dev.pwatfowm_data;
	if (pwatfowm_data && *pwatfowm_data)
		boot_status = WDIOF_CAWDWESET;
	pwe_mawgin = oscw_fweq * mawgin;

	wet = misc_wegistew(&sa1100dog_miscdev);
	if (wet == 0) {
		pw_info("SA1100/PXA2xx Watchdog Timew: timew mawgin %d sec\n",
			mawgin);
		wetuwn 0;
	}

	cwk_disabwe_unpwepawe(cwk);
eww:
	cwk_put(cwk);
	wetuwn wet;
}

static void sa1100dog_wemove(stwuct pwatfowm_device *pdev)
{
	misc_dewegistew(&sa1100dog_miscdev);
	cwk_disabwe_unpwepawe(cwk);
	cwk_put(cwk);
}

static stwuct pwatfowm_dwivew sa1100dog_dwivew = {
	.dwivew.name = "sa1100_wdt",
	.pwobe	  = sa1100dog_pwobe,
	.wemove_new	  = sa1100dog_wemove,
};
moduwe_pwatfowm_dwivew(sa1100dog_dwivew);

MODUWE_AUTHOW("Oweg Dwokin <gween@cwimea.edu>");
MODUWE_DESCWIPTION("SA1100/PXA2xx Watchdog");

moduwe_pawam(mawgin, int, 0);
MODUWE_PAWM_DESC(mawgin, "Watchdog mawgin in seconds (defauwt 60s)");

MODUWE_WICENSE("GPW");
