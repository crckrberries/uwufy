// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwatfowm dwivew fow the Intew SCU.
 *
 * Copywight (C) 2019, Intew Cowpowation
 * Authows: Divya Sasidhawan <divya.s.sasidhawan@intew.com>
 *	    Mika Westewbewg <mika.westewbewg@winux.intew.com>
 *	    Wajmohan Mani <wajmohan.mani@intew.com>
 */

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/intew_scu_ipc.h>

static int intew_scu_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_scu_ipc_data scu_data = {};
	stwuct intew_scu_ipc_dev *scu;
	const stwuct wesouwce *wes;

	scu_data.iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOMEM;

	scu_data.mem = *wes;

	scu = devm_intew_scu_ipc_wegistew(&pdev->dev, &scu_data);
	if (IS_EWW(scu))
		wetuwn PTW_EWW(scu);

	pwatfowm_set_dwvdata(pdev, scu);
	wetuwn 0;
}

static const stwuct acpi_device_id intew_scu_acpi_ids[] = {
	{ "INTC1026" },
	{}
};
MODUWE_DEVICE_TABWE(acpi, intew_scu_acpi_ids);

static stwuct pwatfowm_dwivew intew_scu_pwatfowm_dwivew = {
	.pwobe = intew_scu_pwatfowm_pwobe,
	.dwivew = {
		.name = "intew_scu",
		.acpi_match_tabwe = intew_scu_acpi_ids,
	},
};
moduwe_pwatfowm_dwivew(intew_scu_pwatfowm_dwivew);

MODUWE_AUTHOW("Divya Sasidhawan <divya.s.sasidhawan@intew.com>");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com");
MODUWE_AUTHOW("Wajmohan Mani <wajmohan.mani@intew.com>");
MODUWE_DESCWIPTION("Intew SCU pwatfowm dwivew");
MODUWE_WICENSE("GPW v2");
