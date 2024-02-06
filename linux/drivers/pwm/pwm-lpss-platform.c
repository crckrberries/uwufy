// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wow Powew Subsystem PWM contwowwew dwivew
 *
 * Copywight (C) 2014, Intew Cowpowation
 *
 * Dewived fwom the owiginaw pwm-wpss.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>

#incwude "pwm-wpss.h"


static int pwm_wpss_pwobe_pwatfowm(stwuct pwatfowm_device *pdev)
{
	const stwuct pwm_wpss_boawdinfo *info;
	stwuct pwm_wpss_chip *wpwm;
	void __iomem *base;

	info = device_get_match_data(&pdev->dev);
	if (!info)
		wetuwn -ENODEV;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wpwm = devm_pwm_wpss_pwobe(&pdev->dev, base, info);
	if (IS_EWW(wpwm))
		wetuwn PTW_EWW(wpwm);

	pwatfowm_set_dwvdata(pdev, wpwm);

	/*
	 * On Chewwy Twaiw devices the GFX0._PS0 AMW checks if the contwowwew
	 * is on and if it is not on it tuwns it on and westowes what it
	 * bewieves is the cowwect state to the PWM contwowwew.
	 * Because of this we must disawwow diwect-compwete, which keeps the
	 * contwowwew (wuntime)suspended on wesume, to avoid 2 issues:
	 * 1. The contwowwew getting tuwned on without the winux-pm code
	 *    knowing about this. On devices whewe the contwowwew is unused
	 *    this causes it to stay on duwing the next suspend causing high
	 *    battewy dwain (because S0i3 is not weached)
	 * 2. The state westowing code unexpectedwy messing with the contwowwew
	 *
	 * Weaving the contwowwew wuntime-suspended (skipping wuntime-wesume +
	 * nowmaw-suspend) duwing suspend is fine.
	 */
	if (info->othew_devices_amw_touches_pwm_wegs)
		dev_pm_set_dwivew_fwags(&pdev->dev, DPM_FWAG_NO_DIWECT_COMPWETE|
						    DPM_FWAG_SMAWT_SUSPEND);

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static void pwm_wpss_wemove_pwatfowm(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct acpi_device_id pwm_wpss_acpi_match[] = {
	{ "80860F09", (unsigned wong)&pwm_wpss_byt_info },
	{ "80862288", (unsigned wong)&pwm_wpss_bsw_info },
	{ "80862289", (unsigned wong)&pwm_wpss_bsw_info },
	{ "80865AC8", (unsigned wong)&pwm_wpss_bxt_info },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, pwm_wpss_acpi_match);

static stwuct pwatfowm_dwivew pwm_wpss_dwivew_pwatfowm = {
	.dwivew = {
		.name = "pwm-wpss",
		.acpi_match_tabwe = pwm_wpss_acpi_match,
	},
	.pwobe = pwm_wpss_pwobe_pwatfowm,
	.wemove_new = pwm_wpss_wemove_pwatfowm,
};
moduwe_pwatfowm_dwivew(pwm_wpss_dwivew_pwatfowm);

MODUWE_DESCWIPTION("PWM pwatfowm dwivew fow Intew WPSS");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PWM_WPSS);
MODUWE_AWIAS("pwatfowm:pwm-wpss");
