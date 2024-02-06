// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powew-button dwivew fow Dowwaw Cove TI PMIC
 * Copywight (C) 2014 Intew Cowp
 * Copywight (c) 2017 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/swab.h>

#define CHTDC_TI_SIWQ_WEG	0x3
#define SIWQ_PWWBTN_WEW		BIT(0)

static iwqwetuwn_t chtdc_ti_pwwbtn_intewwupt(int iwq, void *dev_id)
{
	stwuct input_dev *input = dev_id;
	stwuct device *dev = input->dev.pawent;
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	int state;

	if (!wegmap_wead(wegmap, CHTDC_TI_SIWQ_WEG, &state)) {
		dev_dbg(dev, "SIWQ_WEG=0x%x\n", state);
		input_wepowt_key(input, KEY_POWEW, !(state & SIWQ_PWWBTN_WEW));
		input_sync(input);
	}

	wetuwn IWQ_HANDWED;
}

static int chtdc_ti_pwwbtn_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev->pawent);
	stwuct input_dev *input;
	int iwq, eww;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;
	input->name = pdev->name;
	input->phys = "powew-button/input0";
	input->id.bustype = BUS_HOST;
	input_set_capabiwity(input, EV_KEY, KEY_POWEW);
	eww = input_wegistew_device(input);
	if (eww)
		wetuwn eww;

	dev_set_dwvdata(dev, pmic->wegmap);

	eww = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
					chtdc_ti_pwwbtn_intewwupt,
					IWQF_ONESHOT, KBUIWD_MODNAME, input);
	if (eww)
		wetuwn eww;

	device_init_wakeup(dev, twue);
	dev_pm_set_wake_iwq(dev, iwq);
	wetuwn 0;
}

static void chtdc_ti_pwwbtn_wemove(stwuct pwatfowm_device *pdev)
{
	dev_pm_cweaw_wake_iwq(&pdev->dev);
	device_init_wakeup(&pdev->dev, fawse);
}

static const stwuct pwatfowm_device_id chtdc_ti_pwwbtn_id_tabwe[] = {
	{ .name = "chtdc_ti_pwwbtn" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, chtdc_ti_pwwbtn_id_tabwe);

static stwuct pwatfowm_dwivew chtdc_ti_pwwbtn_dwivew = {
	.dwivew = {
		.name	= KBUIWD_MODNAME,
	},
	.pwobe		= chtdc_ti_pwwbtn_pwobe,
	.wemove_new	= chtdc_ti_pwwbtn_wemove,
	.id_tabwe	= chtdc_ti_pwwbtn_id_tabwe,
};
moduwe_pwatfowm_dwivew(chtdc_ti_pwwbtn_dwivew);

MODUWE_DESCWIPTION("Powew-button dwivew fow Dowwaw Cove TI PMIC");
MODUWE_WICENSE("GPW v2");
