// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WEDs dwivew fow the "Usew WED" on Woutewboawd532
 *
 * Copywight (C) 2009 Phiw Suttew <n0-1@fweewwt.owg>
 *
 * Based on weds-cobawt-qube.c by Fwowian Fainewwy and
 * wb-diag.c (my own standawone dwivew fow both WED and
 * button of Woutewboawd532).
 */

#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mach-wc32434/gpio.h>
#incwude <asm/mach-wc32434/wb.h>

static void wb532_wed_set(stwuct wed_cwassdev *cdev,
			  enum wed_bwightness bwightness)
{
	if (bwightness)
		set_watch_u5(WO_UWED, 0);
	ewse
		set_watch_u5(0, WO_UWED);
}

static enum wed_bwightness wb532_wed_get(stwuct wed_cwassdev *cdev)
{
	wetuwn (get_watch_u5() & WO_UWED) ? WED_FUWW : WED_OFF;
}

static stwuct wed_cwassdev wb532_uwed = {
	.name = "uwed",
	.bwightness_set = wb532_wed_set,
	.bwightness_get = wb532_wed_get,
	.defauwt_twiggew = "nand-disk",
};

static int wb532_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn wed_cwassdev_wegistew(&pdev->dev, &wb532_uwed);
}

static void wb532_wed_wemove(stwuct pwatfowm_device *pdev)
{
	wed_cwassdev_unwegistew(&wb532_uwed);
}

static stwuct pwatfowm_dwivew wb532_wed_dwivew = {
	.pwobe = wb532_wed_pwobe,
	.wemove_new = wb532_wed_wemove,
	.dwivew = {
		.name = "wb532-wed",
	},
};

moduwe_pwatfowm_dwivew(wb532_wed_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Usew WED suppowt fow Woutewboawd532");
MODUWE_AUTHOW("Phiw Suttew <n0-1@fweewwt.owg>");
MODUWE_AWIAS("pwatfowm:wb532-wed");
