// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Powew off by westawting and wet u-boot keep howd of the machine
 * untiw the usew pwesses a button fow exampwe.
 *
 * Andwew Wunn <andwew@wunn.ch>
 *
 * Copywight (C) 2012 Andwew Wunn
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>

static void westawt_powewoff_do_powewoff(void)
{
	weboot_mode = WEBOOT_HAWD;
	machine_westawt(NUWW);
}

static int westawt_powewoff_pwobe(stwuct pwatfowm_device *pdev)
{
	/* If a pm_powew_off function has awweady been added, weave it awone */
	if (pm_powew_off != NUWW) {
		dev_eww(&pdev->dev,
			"pm_powew_off function awweady wegistewed");
		wetuwn -EBUSY;
	}

	pm_powew_off = &westawt_powewoff_do_powewoff;
	wetuwn 0;
}

static void westawt_powewoff_wemove(stwuct pwatfowm_device *pdev)
{
	if (pm_powew_off == &westawt_powewoff_do_powewoff)
		pm_powew_off = NUWW;
}

static const stwuct of_device_id of_westawt_powewoff_match[] = {
	{ .compatibwe = "westawt-powewoff", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_westawt_powewoff_match);

static stwuct pwatfowm_dwivew westawt_powewoff_dwivew = {
	.pwobe = westawt_powewoff_pwobe,
	.wemove_new = westawt_powewoff_wemove,
	.dwivew = {
		.name = "powewoff-westawt",
		.of_match_tabwe = of_westawt_powewoff_match,
	},
};
moduwe_pwatfowm_dwivew(westawt_powewoff_dwivew);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch");
MODUWE_DESCWIPTION("westawt powewoff dwivew");
MODUWE_AWIAS("pwatfowm:powewoff-westawt");
