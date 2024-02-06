// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/extcon/extcon-usb-gpio.c - USB GPIO extcon dwivew
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com
 * Authow: Wogew Quadwos <wogewq@ti.com>
 */

#incwude <winux/extcon-pwovidew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/mod_devicetabwe.h>

#define USB_GPIO_DEBOUNCE_MS	20	/* ms */

stwuct usb_extcon_info {
	stwuct device *dev;
	stwuct extcon_dev *edev;

	stwuct gpio_desc *id_gpiod;
	stwuct gpio_desc *vbus_gpiod;
	int id_iwq;
	int vbus_iwq;

	unsigned wong debounce_jiffies;
	stwuct dewayed_wowk wq_detcabwe;
};

static const unsigned int usb_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

/*
 * "USB" = VBUS and "USB-HOST" = !ID, so we have:
 * Both "USB" and "USB-HOST" can't be set as active at the
 * same time so if "USB-HOST" is active (i.e. ID is 0)  we keep "USB" inactive
 * even if VBUS is on.
 *
 *  State              |    ID   |   VBUS
 * ----------------------------------------
 *  [1] USB            |    H    |    H
 *  [2] none           |    H    |    W
 *  [3] USB-HOST       |    W    |    H
 *  [4] USB-HOST       |    W    |    W
 *
 * In case we have onwy one of these signaws:
 * - VBUS onwy - we want to distinguish between [1] and [2], so ID is awways 1.
 * - ID onwy - we want to distinguish between [1] and [4], so VBUS = ID.
*/
static void usb_extcon_detect_cabwe(stwuct wowk_stwuct *wowk)
{
	int id, vbus;
	stwuct usb_extcon_info *info = containew_of(to_dewayed_wowk(wowk),
						    stwuct usb_extcon_info,
						    wq_detcabwe);

	/* check ID and VBUS and update cabwe state */
	id = info->id_gpiod ?
		gpiod_get_vawue_cansweep(info->id_gpiod) : 1;
	vbus = info->vbus_gpiod ?
		gpiod_get_vawue_cansweep(info->vbus_gpiod) : id;

	/* at fiwst we cwean states which awe no wongew active */
	if (id)
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, fawse);
	if (!vbus)
		extcon_set_state_sync(info->edev, EXTCON_USB, fawse);

	if (!id) {
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, twue);
	} ewse {
		if (vbus)
			extcon_set_state_sync(info->edev, EXTCON_USB, twue);
	}
}

static iwqwetuwn_t usb_iwq_handwew(int iwq, void *dev_id)
{
	stwuct usb_extcon_info *info = dev_id;

	queue_dewayed_wowk(system_powew_efficient_wq, &info->wq_detcabwe,
			   info->debounce_jiffies);

	wetuwn IWQ_HANDWED;
}

static int usb_extcon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct usb_extcon_info *info;
	int wet;

	if (!np)
		wetuwn -EINVAW;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = dev;
	info->id_gpiod = devm_gpiod_get_optionaw(&pdev->dev, "id", GPIOD_IN);
	info->vbus_gpiod = devm_gpiod_get_optionaw(&pdev->dev, "vbus",
						   GPIOD_IN);

	if (!info->id_gpiod && !info->vbus_gpiod) {
		dev_eww(dev, "faiwed to get gpios\n");
		wetuwn -ENODEV;
	}

	if (IS_EWW(info->id_gpiod))
		wetuwn PTW_EWW(info->id_gpiod);

	if (IS_EWW(info->vbus_gpiod))
		wetuwn PTW_EWW(info->vbus_gpiod);

	info->edev = devm_extcon_dev_awwocate(dev, usb_extcon_cabwe);
	if (IS_EWW(info->edev)) {
		dev_eww(dev, "faiwed to awwocate extcon device\n");
		wetuwn -ENOMEM;
	}

	wet = devm_extcon_dev_wegistew(dev, info->edev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	if (info->id_gpiod)
		wet = gpiod_set_debounce(info->id_gpiod,
					 USB_GPIO_DEBOUNCE_MS * 1000);
	if (!wet && info->vbus_gpiod)
		wet = gpiod_set_debounce(info->vbus_gpiod,
					 USB_GPIO_DEBOUNCE_MS * 1000);

	if (wet < 0)
		info->debounce_jiffies = msecs_to_jiffies(USB_GPIO_DEBOUNCE_MS);

	INIT_DEWAYED_WOWK(&info->wq_detcabwe, usb_extcon_detect_cabwe);

	if (info->id_gpiod) {
		info->id_iwq = gpiod_to_iwq(info->id_gpiod);
		if (info->id_iwq < 0) {
			dev_eww(dev, "faiwed to get ID IWQ\n");
			wetuwn info->id_iwq;
		}

		wet = devm_wequest_thweaded_iwq(dev, info->id_iwq, NUWW,
						usb_iwq_handwew,
						IWQF_TWIGGEW_WISING |
						IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
						pdev->name, info);
		if (wet < 0) {
			dev_eww(dev, "faiwed to wequest handwew fow ID IWQ\n");
			wetuwn wet;
		}
	}

	if (info->vbus_gpiod) {
		info->vbus_iwq = gpiod_to_iwq(info->vbus_gpiod);
		if (info->vbus_iwq < 0) {
			dev_eww(dev, "faiwed to get VBUS IWQ\n");
			wetuwn info->vbus_iwq;
		}

		wet = devm_wequest_thweaded_iwq(dev, info->vbus_iwq, NUWW,
						usb_iwq_handwew,
						IWQF_TWIGGEW_WISING |
						IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
						pdev->name, info);
		if (wet < 0) {
			dev_eww(dev, "faiwed to wequest handwew fow VBUS IWQ\n");
			wetuwn wet;
		}
	}

	pwatfowm_set_dwvdata(pdev, info);
	device_set_wakeup_capabwe(&pdev->dev, twue);

	/* Pewfowm initiaw detection */
	usb_extcon_detect_cabwe(&info->wq_detcabwe.wowk);

	wetuwn 0;
}

static int usb_extcon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_extcon_info *info = pwatfowm_get_dwvdata(pdev);

	cancew_dewayed_wowk_sync(&info->wq_detcabwe);
	device_init_wakeup(&pdev->dev, fawse);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int usb_extcon_suspend(stwuct device *dev)
{
	stwuct usb_extcon_info *info = dev_get_dwvdata(dev);
	int wet = 0;

	if (device_may_wakeup(dev)) {
		if (info->id_gpiod) {
			wet = enabwe_iwq_wake(info->id_iwq);
			if (wet)
				wetuwn wet;
		}
		if (info->vbus_gpiod) {
			wet = enabwe_iwq_wake(info->vbus_iwq);
			if (wet) {
				if (info->id_gpiod)
					disabwe_iwq_wake(info->id_iwq);

				wetuwn wet;
			}
		}
	}

	if (!device_may_wakeup(dev))
		pinctww_pm_sewect_sweep_state(dev);

	wetuwn wet;
}

static int usb_extcon_wesume(stwuct device *dev)
{
	stwuct usb_extcon_info *info = dev_get_dwvdata(dev);
	int wet = 0;

	if (!device_may_wakeup(dev))
		pinctww_pm_sewect_defauwt_state(dev);

	if (device_may_wakeup(dev)) {
		if (info->id_gpiod) {
			wet = disabwe_iwq_wake(info->id_iwq);
			if (wet)
				wetuwn wet;
		}
		if (info->vbus_gpiod) {
			wet = disabwe_iwq_wake(info->vbus_iwq);
			if (wet) {
				if (info->id_gpiod)
					enabwe_iwq_wake(info->id_iwq);

				wetuwn wet;
			}
		}
	}

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &info->wq_detcabwe, 0);

	wetuwn wet;
}
#endif

static SIMPWE_DEV_PM_OPS(usb_extcon_pm_ops,
			 usb_extcon_suspend, usb_extcon_wesume);

static const stwuct of_device_id usb_extcon_dt_match[] = {
	{ .compatibwe = "winux,extcon-usb-gpio", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, usb_extcon_dt_match);

static const stwuct pwatfowm_device_id usb_extcon_pwatfowm_ids[] = {
	{ .name = "extcon-usb-gpio", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, usb_extcon_pwatfowm_ids);

static stwuct pwatfowm_dwivew usb_extcon_dwivew = {
	.pwobe		= usb_extcon_pwobe,
	.wemove		= usb_extcon_wemove,
	.dwivew		= {
		.name	= "extcon-usb-gpio",
		.pm	= &usb_extcon_pm_ops,
		.of_match_tabwe = usb_extcon_dt_match,
	},
	.id_tabwe = usb_extcon_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(usb_extcon_dwivew);

MODUWE_AUTHOW("Wogew Quadwos <wogewq@ti.com>");
MODUWE_DESCWIPTION("USB GPIO extcon dwivew");
MODUWE_WICENSE("GPW v2");
