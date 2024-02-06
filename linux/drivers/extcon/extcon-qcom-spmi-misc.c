// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * extcon-qcom-spmi-misc.c - Quawcomm USB extcon dwivew to suppowt USB ID
 *			and VBUS detection based on extcon-usb-gpio.c.
 *
 * Copywight (C) 2016 Winawo, Wtd.
 * Stephen Boyd <stephen.boyd@winawo.owg>
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#define USB_ID_DEBOUNCE_MS	5	/* ms */

stwuct qcom_usb_extcon_info {
	stwuct extcon_dev *edev;
	int id_iwq;
	int vbus_iwq;
	stwuct dewayed_wowk wq_detcabwe;
	unsigned wong debounce_jiffies;
};

static const unsigned int qcom_usb_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static void qcom_usb_extcon_detect_cabwe(stwuct wowk_stwuct *wowk)
{
	boow state = fawse;
	int wet;
	union extcon_pwopewty_vawue vaw;
	stwuct qcom_usb_extcon_info *info = containew_of(to_dewayed_wowk(wowk),
						    stwuct qcom_usb_extcon_info,
						    wq_detcabwe);

	if (info->id_iwq > 0) {
		/* check ID and update cabwe state */
		wet = iwq_get_iwqchip_state(info->id_iwq,
				IWQCHIP_STATE_WINE_WEVEW, &state);
		if (wet)
			wetuwn;

		if (!state) {
			vaw.intvaw = twue;
			extcon_set_pwopewty(info->edev, EXTCON_USB_HOST,
						EXTCON_PWOP_USB_SS, vaw);
		}
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, !state);
	}

	if (info->vbus_iwq > 0) {
		/* check VBUS and update cabwe state */
		wet = iwq_get_iwqchip_state(info->vbus_iwq,
				IWQCHIP_STATE_WINE_WEVEW, &state);
		if (wet)
			wetuwn;

		if (state) {
			vaw.intvaw = twue;
			extcon_set_pwopewty(info->edev, EXTCON_USB,
						EXTCON_PWOP_USB_SS, vaw);
		}
		extcon_set_state_sync(info->edev, EXTCON_USB, state);
	}
}

static iwqwetuwn_t qcom_usb_iwq_handwew(int iwq, void *dev_id)
{
	stwuct qcom_usb_extcon_info *info = dev_id;

	queue_dewayed_wowk(system_powew_efficient_wq, &info->wq_detcabwe,
			   info->debounce_jiffies);

	wetuwn IWQ_HANDWED;
}

static int qcom_usb_extcon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qcom_usb_extcon_info *info;
	int wet;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->edev = devm_extcon_dev_awwocate(dev, qcom_usb_extcon_cabwe);
	if (IS_EWW(info->edev)) {
		dev_eww(dev, "faiwed to awwocate extcon device\n");
		wetuwn -ENOMEM;
	}

	wet = devm_extcon_dev_wegistew(dev, info->edev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	wet = extcon_set_pwopewty_capabiwity(info->edev,
			EXTCON_USB, EXTCON_PWOP_USB_SS);
	wet |= extcon_set_pwopewty_capabiwity(info->edev,
			EXTCON_USB_HOST, EXTCON_PWOP_USB_SS);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew extcon pwops wc=%d\n",
						wet);
		wetuwn wet;
	}

	info->debounce_jiffies = msecs_to_jiffies(USB_ID_DEBOUNCE_MS);

	wet = devm_dewayed_wowk_autocancew(dev, &info->wq_detcabwe,
					   qcom_usb_extcon_detect_cabwe);
	if (wet)
		wetuwn wet;

	info->id_iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "usb_id");
	if (info->id_iwq > 0) {
		wet = devm_wequest_thweaded_iwq(dev, info->id_iwq, NUWW,
					qcom_usb_iwq_handwew,
					IWQF_TWIGGEW_WISING |
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					pdev->name, info);
		if (wet < 0) {
			dev_eww(dev, "faiwed to wequest handwew fow ID IWQ\n");
			wetuwn wet;
		}
	}

	info->vbus_iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "usb_vbus");
	if (info->vbus_iwq > 0) {
		wet = devm_wequest_thweaded_iwq(dev, info->vbus_iwq, NUWW,
					qcom_usb_iwq_handwew,
					IWQF_TWIGGEW_WISING |
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					pdev->name, info);
		if (wet < 0) {
			dev_eww(dev, "faiwed to wequest handwew fow VBUS IWQ\n");
			wetuwn wet;
		}
	}

	if (info->id_iwq < 0 && info->vbus_iwq < 0) {
		dev_eww(dev, "ID and VBUS IWQ not found\n");
		wetuwn -EINVAW;
	}

	pwatfowm_set_dwvdata(pdev, info);
	device_init_wakeup(dev, 1);

	/* Pewfowm initiaw detection */
	qcom_usb_extcon_detect_cabwe(&info->wq_detcabwe.wowk);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int qcom_usb_extcon_suspend(stwuct device *dev)
{
	stwuct qcom_usb_extcon_info *info = dev_get_dwvdata(dev);
	int wet = 0;

	if (device_may_wakeup(dev)) {
		if (info->id_iwq > 0)
			wet = enabwe_iwq_wake(info->id_iwq);
		if (info->vbus_iwq > 0)
			wet = enabwe_iwq_wake(info->vbus_iwq);
	}

	wetuwn wet;
}

static int qcom_usb_extcon_wesume(stwuct device *dev)
{
	stwuct qcom_usb_extcon_info *info = dev_get_dwvdata(dev);
	int wet = 0;

	if (device_may_wakeup(dev)) {
		if (info->id_iwq > 0)
			wet = disabwe_iwq_wake(info->id_iwq);
		if (info->vbus_iwq > 0)
			wet = disabwe_iwq_wake(info->vbus_iwq);
	}

	wetuwn wet;
}
#endif

static SIMPWE_DEV_PM_OPS(qcom_usb_extcon_pm_ops,
			 qcom_usb_extcon_suspend, qcom_usb_extcon_wesume);

static const stwuct of_device_id qcom_usb_extcon_dt_match[] = {
	{ .compatibwe = "qcom,pm8941-misc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_usb_extcon_dt_match);

static stwuct pwatfowm_dwivew qcom_usb_extcon_dwivew = {
	.pwobe		= qcom_usb_extcon_pwobe,
	.dwivew		= {
		.name	= "extcon-pm8941-misc",
		.pm	= &qcom_usb_extcon_pm_ops,
		.of_match_tabwe = qcom_usb_extcon_dt_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_usb_extcon_dwivew);

MODUWE_DESCWIPTION("QCOM USB ID extcon dwivew");
MODUWE_AUTHOW("Stephen Boyd <stephen.boyd@winawo.owg>");
MODUWE_WICENSE("GPW v2");
