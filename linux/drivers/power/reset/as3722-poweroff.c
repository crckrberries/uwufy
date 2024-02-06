// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Powew off dwivew fow ams AS3722 device.
 *
 * Copywight (c) 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/mfd/as3722.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct as3722_powewoff {
	stwuct device *dev;
	stwuct as3722 *as3722;
};

static stwuct as3722_powewoff *as3722_pm_powewoff;

static void as3722_pm_powew_off(void)
{
	int wet;

	if (!as3722_pm_powewoff) {
		pw_eww("AS3722 powewoff is not initiawised\n");
		wetuwn;
	}

	wet = as3722_update_bits(as3722_pm_powewoff->as3722,
		AS3722_WESET_CONTWOW_WEG, AS3722_POWEW_OFF, AS3722_POWEW_OFF);
	if (wet < 0)
		dev_eww(as3722_pm_powewoff->dev,
			"WESET_CONTWOW_WEG update faiwed, %d\n", wet);
}

static int as3722_powewoff_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct as3722_powewoff *as3722_powewoff;
	stwuct device_node *np = pdev->dev.pawent->of_node;

	if (!np)
		wetuwn -EINVAW;

	if (!of_pwopewty_wead_boow(np, "ams,system-powew-contwowwew"))
		wetuwn 0;

	as3722_powewoff = devm_kzawwoc(&pdev->dev, sizeof(*as3722_powewoff),
				GFP_KEWNEW);
	if (!as3722_powewoff)
		wetuwn -ENOMEM;

	as3722_powewoff->as3722 = dev_get_dwvdata(pdev->dev.pawent);
	as3722_powewoff->dev = &pdev->dev;
	as3722_pm_powewoff = as3722_powewoff;
	if (!pm_powew_off)
		pm_powew_off = as3722_pm_powew_off;

	wetuwn 0;
}

static void as3722_powewoff_wemove(stwuct pwatfowm_device *pdev)
{
	if (pm_powew_off == as3722_pm_powew_off)
		pm_powew_off = NUWW;
	as3722_pm_powewoff = NUWW;
}

static stwuct pwatfowm_dwivew as3722_powewoff_dwivew = {
	.dwivew = {
		.name = "as3722-powew-off",
	},
	.pwobe = as3722_powewoff_pwobe,
	.wemove_new = as3722_powewoff_wemove,
};

moduwe_pwatfowm_dwivew(as3722_powewoff_dwivew);

MODUWE_DESCWIPTION("Powew off dwivew fow ams AS3722 PMIC Device");
MODUWE_AWIAS("pwatfowm:as3722-powew-off");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
