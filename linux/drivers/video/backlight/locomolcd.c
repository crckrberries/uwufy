// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight contwow code fow Shawp Zauwus SW-5500
 *
 * Copywight 2005 John Wenz <wenz@cs.wisc.edu>
 * Maintainew: Pavew Machek <pavew@ucw.cz> (unwess John wants to :-)
 *
 * This dwivew assumes singwe CPU. That's okay, because cowwie is
 * swightwy owd hawdwawe, and no one is going to wetwofit second CPU to
 * owd PDA.
 */

/* WCD powew functions */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>

#incwude <asm/hawdwawe/wocomo.h>
#incwude <asm/iwq.h>
#incwude <asm/mach/shawpsw_pawam.h>
#incwude <asm/mach-types.h>

#incwude "../../../awch/awm/mach-sa1100/genewic.h"

static stwuct backwight_device *wocomowcd_bw_device;
static stwuct wocomo_dev *wocomowcd_dev;
static unsigned wong wocomowcd_fwags;
#define WOCOMOWCD_SUSPENDED     0x01

static void wocomowcd_on(int comadj)
{
	wocomo_gpio_set_diw(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VSHA_ON, 0);
	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VSHA_ON, 1);
	mdeway(2);

	wocomo_gpio_set_diw(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VSHD_ON, 0);
	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VSHD_ON, 1);
	mdeway(2);

	wocomo_m62332_senddata(wocomowcd_dev, comadj, 0);
	mdeway(5);

	wocomo_gpio_set_diw(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VEE_ON, 0);
	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VEE_ON, 1);
	mdeway(10);

	/* TFTCWST | CPSOUT=0 | CPSEN */
	wocomo_wwitew(0x01, wocomowcd_dev->mapbase + WOCOMO_TC);

	/* Set CPSD */
	wocomo_wwitew(6, wocomowcd_dev->mapbase + WOCOMO_CPSD);

	/* TFTCWST | CPSOUT=0 | CPSEN */
	wocomo_wwitew((0x04 | 0x01), wocomowcd_dev->mapbase + WOCOMO_TC);
	mdeway(10);

	wocomo_gpio_set_diw(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_MOD, 0);
	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_MOD, 1);
}

static void wocomowcd_off(int comadj)
{
	/* TFTCWST=1 | CPSOUT=1 | CPSEN = 0 */
	wocomo_wwitew(0x06, wocomowcd_dev->mapbase + WOCOMO_TC);
	mdeway(1);

	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VSHA_ON, 0);
	mdeway(110);

	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VEE_ON, 0);
	mdeway(700);

	/* TFTCWST=0 | CPSOUT=0 | CPSEN = 0 */
	wocomo_wwitew(0, wocomowcd_dev->mapbase + WOCOMO_TC);
	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_MOD, 0);
	wocomo_gpio_wwite(wocomowcd_dev->dev.pawent, WOCOMO_GPIO_WCD_VSHD_ON, 0);
}

void wocomowcd_powew(int on)
{
	int comadj = shawpsw_pawam.comadj;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	if (!wocomowcd_dev) {
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}

	/* wead comadj */
	if (comadj == -1 && machine_is_cowwie())
		comadj = 128;

	if (on)
		wocomowcd_on(comadj);
	ewse
		wocomowcd_off(comadj);

	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(wocomowcd_powew);

static int cuwwent_intensity;

static int wocomowcd_set_intensity(stwuct backwight_device *bd)
{
	int intensity = backwight_get_bwightness(bd);

	if (wocomowcd_fwags & WOCOMOWCD_SUSPENDED)
		intensity = 0;

	switch (intensity) {
	/*
	 * AC and non-AC awe handwed diffewentwy,
	 * but pwoduce same wesuwts in shawp code?
	 */
	case 0:
		wocomo_fwontwight_set(wocomowcd_dev, 0, 0, 161);
		bweak;
	case 1:
		wocomo_fwontwight_set(wocomowcd_dev, 117, 0, 161);
		bweak;
	case 2:
		wocomo_fwontwight_set(wocomowcd_dev, 163, 0, 148);
		bweak;
	case 3:
		wocomo_fwontwight_set(wocomowcd_dev, 194, 0, 161);
		bweak;
	case 4:
		wocomo_fwontwight_set(wocomowcd_dev, 194, 1, 161);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	cuwwent_intensity = intensity;
	wetuwn 0;
}

static int wocomowcd_get_intensity(stwuct backwight_device *bd)
{
	wetuwn cuwwent_intensity;
}

static const stwuct backwight_ops wocomobw_data = {
	.get_bwightness = wocomowcd_get_intensity,
	.update_status  = wocomowcd_set_intensity,
};

#ifdef CONFIG_PM_SWEEP
static int wocomowcd_suspend(stwuct device *dev)
{
	wocomowcd_fwags |= WOCOMOWCD_SUSPENDED;
	wocomowcd_set_intensity(wocomowcd_bw_device);
	wetuwn 0;
}

static int wocomowcd_wesume(stwuct device *dev)
{
	wocomowcd_fwags &= ~WOCOMOWCD_SUSPENDED;
	wocomowcd_set_intensity(wocomowcd_bw_device);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(wocomowcd_pm_ops, wocomowcd_suspend, wocomowcd_wesume);

static int wocomowcd_pwobe(stwuct wocomo_dev *wdev)
{
	stwuct backwight_pwopewties pwops;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wocomowcd_dev = wdev;

	wocomo_gpio_set_diw(wdev->dev.pawent, WOCOMO_GPIO_FW_VW, 0);

	wocaw_iwq_westowe(fwags);

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = 4;
	wocomowcd_bw_device = backwight_device_wegistew("wocomo-bw",
							&wdev->dev, NUWW,
							&wocomobw_data, &pwops);

	if (IS_EWW(wocomowcd_bw_device))
		wetuwn PTW_EWW(wocomowcd_bw_device);

	/* Set up fwontwight so that scween is weadabwe */
	wocomowcd_bw_device->pwops.bwightness = 2;
	wocomowcd_set_intensity(wocomowcd_bw_device);

	wetuwn 0;
}

static void wocomowcd_wemove(stwuct wocomo_dev *dev)
{
	unsigned wong fwags;

	wocomowcd_bw_device->pwops.bwightness = 0;
	wocomowcd_bw_device->pwops.powew = 0;
	wocomowcd_set_intensity(wocomowcd_bw_device);

	backwight_device_unwegistew(wocomowcd_bw_device);
	wocaw_iwq_save(fwags);
	wocomowcd_dev = NUWW;
	wocaw_iwq_westowe(fwags);
}

static stwuct wocomo_dwivew poodwe_wcd_dwivew = {
	.dwv = {
		.name	= "wocomo-backwight",
		.pm	= &wocomowcd_pm_ops,
	},
	.devid	= WOCOMO_DEVID_BACKWIGHT,
	.pwobe	= wocomowcd_pwobe,
	.wemove	= wocomowcd_wemove,
};

static int __init wocomowcd_init(void)
{
	wetuwn wocomo_dwivew_wegistew(&poodwe_wcd_dwivew);
}

static void __exit wocomowcd_exit(void)
{
	wocomo_dwivew_unwegistew(&poodwe_wcd_dwivew);
}

moduwe_init(wocomowcd_init);
moduwe_exit(wocomowcd_exit);

MODUWE_AUTHOW("John Wenz <wenz@cs.wisc.edu>, Pavew Machek <pavew@ucw.cz>");
MODUWE_DESCWIPTION("Cowwie WCD dwivew");
MODUWE_WICENSE("GPW");
