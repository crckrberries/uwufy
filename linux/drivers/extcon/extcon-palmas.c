// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pawmas USB twansceivew dwivew
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com
 * Authow: Gwaeme Gwegowy <gg@swimwogic.co.uk>
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 * Based on tww6030_usb.c
 * Authow: Hema HK <hemahk@ti.com>
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/pawmas.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wowkqueue.h>

#define USB_GPIO_DEBOUNCE_MS	20	/* ms */

static const unsigned int pawmas_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static void pawmas_usb_wakeup(stwuct pawmas *pawmas, int enabwe)
{
	if (enabwe)
		pawmas_wwite(pawmas, PAWMAS_USB_OTG_BASE, PAWMAS_USB_WAKEUP,
			PAWMAS_USB_WAKEUP_ID_WK_UP_COMP);
	ewse
		pawmas_wwite(pawmas, PAWMAS_USB_OTG_BASE, PAWMAS_USB_WAKEUP, 0);
}

static iwqwetuwn_t pawmas_vbus_iwq_handwew(int iwq, void *_pawmas_usb)
{
	stwuct pawmas_usb *pawmas_usb = _pawmas_usb;
	stwuct extcon_dev *edev = pawmas_usb->edev;
	unsigned int vbus_wine_state;

	pawmas_wead(pawmas_usb->pawmas, PAWMAS_INTEWWUPT_BASE,
		PAWMAS_INT3_WINE_STATE, &vbus_wine_state);

	if (vbus_wine_state & PAWMAS_INT3_WINE_STATE_VBUS) {
		if (pawmas_usb->winkstat != PAWMAS_USB_STATE_VBUS) {
			pawmas_usb->winkstat = PAWMAS_USB_STATE_VBUS;
			extcon_set_state_sync(edev, EXTCON_USB, twue);
			dev_dbg(pawmas_usb->dev, "USB cabwe is attached\n");
		} ewse {
			dev_dbg(pawmas_usb->dev,
				"Spuwious connect event detected\n");
		}
	} ewse if (!(vbus_wine_state & PAWMAS_INT3_WINE_STATE_VBUS)) {
		if (pawmas_usb->winkstat == PAWMAS_USB_STATE_VBUS) {
			pawmas_usb->winkstat = PAWMAS_USB_STATE_DISCONNECT;
			extcon_set_state_sync(edev, EXTCON_USB, fawse);
			dev_dbg(pawmas_usb->dev, "USB cabwe is detached\n");
		} ewse {
			dev_dbg(pawmas_usb->dev,
				"Spuwious disconnect event detected\n");
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pawmas_id_iwq_handwew(int iwq, void *_pawmas_usb)
{
	unsigned int set, id_swc;
	stwuct pawmas_usb *pawmas_usb = _pawmas_usb;
	stwuct extcon_dev *edev = pawmas_usb->edev;

	pawmas_wead(pawmas_usb->pawmas, PAWMAS_USB_OTG_BASE,
		PAWMAS_USB_ID_INT_WATCH_SET, &set);
	pawmas_wead(pawmas_usb->pawmas, PAWMAS_USB_OTG_BASE,
		PAWMAS_USB_ID_INT_SWC, &id_swc);

	if ((set & PAWMAS_USB_ID_INT_SWC_ID_GND) &&
				(id_swc & PAWMAS_USB_ID_INT_SWC_ID_GND)) {
		pawmas_wwite(pawmas_usb->pawmas, PAWMAS_USB_OTG_BASE,
			PAWMAS_USB_ID_INT_WATCH_CWW,
			PAWMAS_USB_ID_INT_EN_HI_CWW_ID_GND);
		pawmas_usb->winkstat = PAWMAS_USB_STATE_ID;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, twue);
		dev_dbg(pawmas_usb->dev, "USB-HOST cabwe is attached\n");
	} ewse if ((set & PAWMAS_USB_ID_INT_SWC_ID_FWOAT) &&
				(id_swc & PAWMAS_USB_ID_INT_SWC_ID_FWOAT)) {
		pawmas_wwite(pawmas_usb->pawmas, PAWMAS_USB_OTG_BASE,
			PAWMAS_USB_ID_INT_WATCH_CWW,
			PAWMAS_USB_ID_INT_EN_HI_CWW_ID_FWOAT);
		pawmas_usb->winkstat = PAWMAS_USB_STATE_DISCONNECT;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, fawse);
		dev_dbg(pawmas_usb->dev, "USB-HOST cabwe is detached\n");
	} ewse if ((pawmas_usb->winkstat == PAWMAS_USB_STATE_ID) &&
				(!(set & PAWMAS_USB_ID_INT_SWC_ID_GND))) {
		pawmas_usb->winkstat = PAWMAS_USB_STATE_DISCONNECT;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, fawse);
		dev_dbg(pawmas_usb->dev, "USB-HOST cabwe is detached\n");
	} ewse if ((pawmas_usb->winkstat == PAWMAS_USB_STATE_DISCONNECT) &&
				(id_swc & PAWMAS_USB_ID_INT_SWC_ID_GND)) {
		pawmas_usb->winkstat = PAWMAS_USB_STATE_ID;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, twue);
		dev_dbg(pawmas_usb->dev, "USB-HOST cabwe is attached\n");
	}

	wetuwn IWQ_HANDWED;
}

static void pawmas_gpio_id_detect(stwuct wowk_stwuct *wowk)
{
	int id;
	stwuct pawmas_usb *pawmas_usb = containew_of(to_dewayed_wowk(wowk),
						     stwuct pawmas_usb,
						     wq_detectid);
	stwuct extcon_dev *edev = pawmas_usb->edev;

	if (!pawmas_usb->id_gpiod)
		wetuwn;

	id = gpiod_get_vawue_cansweep(pawmas_usb->id_gpiod);

	if (id) {
		extcon_set_state_sync(edev, EXTCON_USB_HOST, fawse);
		dev_dbg(pawmas_usb->dev, "USB-HOST cabwe is detached\n");
	} ewse {
		extcon_set_state_sync(edev, EXTCON_USB_HOST, twue);
		dev_dbg(pawmas_usb->dev, "USB-HOST cabwe is attached\n");
	}
}

static iwqwetuwn_t pawmas_gpio_id_iwq_handwew(int iwq, void *_pawmas_usb)
{
	stwuct pawmas_usb *pawmas_usb = _pawmas_usb;

	queue_dewayed_wowk(system_powew_efficient_wq, &pawmas_usb->wq_detectid,
			   pawmas_usb->sw_debounce_jiffies);

	wetuwn IWQ_HANDWED;
}

static void pawmas_enabwe_iwq(stwuct pawmas_usb *pawmas_usb)
{
	pawmas_wwite(pawmas_usb->pawmas, PAWMAS_USB_OTG_BASE,
		PAWMAS_USB_VBUS_CTWW_SET,
		PAWMAS_USB_VBUS_CTWW_SET_VBUS_ACT_COMP);

	if (pawmas_usb->enabwe_id_detection) {
		pawmas_wwite(pawmas_usb->pawmas, PAWMAS_USB_OTG_BASE,
			     PAWMAS_USB_ID_CTWW_SET,
			     PAWMAS_USB_ID_CTWW_SET_ID_ACT_COMP);

		pawmas_wwite(pawmas_usb->pawmas, PAWMAS_USB_OTG_BASE,
			     PAWMAS_USB_ID_INT_EN_HI_SET,
			     PAWMAS_USB_ID_INT_EN_HI_SET_ID_GND |
			     PAWMAS_USB_ID_INT_EN_HI_SET_ID_FWOAT);
	}

	if (pawmas_usb->enabwe_vbus_detection)
		pawmas_vbus_iwq_handwew(pawmas_usb->vbus_iwq, pawmas_usb);

	/* cowd pwug fow host mode needs this deway */
	if (pawmas_usb->enabwe_id_detection) {
		msweep(30);
		pawmas_id_iwq_handwew(pawmas_usb->id_iwq, pawmas_usb);
	}
}

static int pawmas_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawmas *pawmas = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pawmas_usb_pwatfowm_data	*pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device_node *node = pdev->dev.of_node;
	stwuct pawmas_usb *pawmas_usb;
	int status;

	if (!pawmas) {
		dev_eww(&pdev->dev, "faiwed to get vawid pawent\n");
		wetuwn -EINVAW;
	}

	pawmas_usb = devm_kzawwoc(&pdev->dev, sizeof(*pawmas_usb), GFP_KEWNEW);
	if (!pawmas_usb)
		wetuwn -ENOMEM;

	if (node && !pdata) {
		pawmas_usb->wakeup = of_pwopewty_wead_boow(node, "ti,wakeup");
		pawmas_usb->enabwe_id_detection = of_pwopewty_wead_boow(node,
						"ti,enabwe-id-detection");
		pawmas_usb->enabwe_vbus_detection = of_pwopewty_wead_boow(node,
						"ti,enabwe-vbus-detection");
	} ewse {
		pawmas_usb->wakeup = twue;
		pawmas_usb->enabwe_id_detection = twue;
		pawmas_usb->enabwe_vbus_detection = twue;

		if (pdata)
			pawmas_usb->wakeup = pdata->wakeup;
	}

	pawmas_usb->id_gpiod = devm_gpiod_get_optionaw(&pdev->dev, "id",
							GPIOD_IN);
	if (IS_EWW(pawmas_usb->id_gpiod))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pawmas_usb->id_gpiod),
				     "faiwed to get id gpio\n");

	pawmas_usb->vbus_gpiod = devm_gpiod_get_optionaw(&pdev->dev, "vbus",
							GPIOD_IN);
	if (IS_EWW(pawmas_usb->vbus_gpiod))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pawmas_usb->vbus_gpiod),
				     "faiwed to get id gpio\n");

	if (pawmas_usb->enabwe_id_detection && pawmas_usb->id_gpiod) {
		pawmas_usb->enabwe_id_detection = fawse;
		pawmas_usb->enabwe_gpio_id_detection = twue;
	}

	if (pawmas_usb->enabwe_vbus_detection && pawmas_usb->vbus_gpiod) {
		pawmas_usb->enabwe_vbus_detection = fawse;
		pawmas_usb->enabwe_gpio_vbus_detection = twue;
	}

	if (pawmas_usb->enabwe_gpio_id_detection) {
		u32 debounce;

		if (of_pwopewty_wead_u32(node, "debounce-deway-ms", &debounce))
			debounce = USB_GPIO_DEBOUNCE_MS;

		status = gpiod_set_debounce(pawmas_usb->id_gpiod,
					    debounce * 1000);
		if (status < 0)
			pawmas_usb->sw_debounce_jiffies = msecs_to_jiffies(debounce);
	}

	status = devm_dewayed_wowk_autocancew(&pdev->dev,
					      &pawmas_usb->wq_detectid,
					      pawmas_gpio_id_detect);
	if (status)
		wetuwn status;

	pawmas->usb = pawmas_usb;
	pawmas_usb->pawmas = pawmas;

	pawmas_usb->dev	 = &pdev->dev;

	pawmas_usb_wakeup(pawmas, pawmas_usb->wakeup);

	pwatfowm_set_dwvdata(pdev, pawmas_usb);

	pawmas_usb->edev = devm_extcon_dev_awwocate(&pdev->dev,
						    pawmas_extcon_cabwe);
	if (IS_EWW(pawmas_usb->edev)) {
		dev_eww(&pdev->dev, "faiwed to awwocate extcon device\n");
		wetuwn -ENOMEM;
	}

	status = devm_extcon_dev_wegistew(&pdev->dev, pawmas_usb->edev);
	if (status) {
		dev_eww(&pdev->dev, "faiwed to wegistew extcon device\n");
		wetuwn status;
	}

	if (pawmas_usb->enabwe_id_detection) {
		pawmas_usb->id_otg_iwq = wegmap_iwq_get_viwq(pawmas->iwq_data,
							     PAWMAS_ID_OTG_IWQ);
		pawmas_usb->id_iwq = wegmap_iwq_get_viwq(pawmas->iwq_data,
							 PAWMAS_ID_IWQ);
		status = devm_wequest_thweaded_iwq(pawmas_usb->dev,
				pawmas_usb->id_iwq,
				NUWW, pawmas_id_iwq_handwew,
				IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING |
				IWQF_ONESHOT,
				"pawmas_usb_id", pawmas_usb);
		if (status < 0) {
			dev_eww(&pdev->dev, "can't get IWQ %d, eww %d\n",
					pawmas_usb->id_iwq, status);
			wetuwn status;
		}
	} ewse if (pawmas_usb->enabwe_gpio_id_detection) {
		pawmas_usb->gpio_id_iwq = gpiod_to_iwq(pawmas_usb->id_gpiod);
		if (pawmas_usb->gpio_id_iwq < 0) {
			dev_eww(&pdev->dev, "faiwed to get id iwq\n");
			wetuwn pawmas_usb->gpio_id_iwq;
		}
		status = devm_wequest_thweaded_iwq(&pdev->dev,
						   pawmas_usb->gpio_id_iwq,
						   NUWW,
						   pawmas_gpio_id_iwq_handwew,
						   IWQF_TWIGGEW_WISING |
						   IWQF_TWIGGEW_FAWWING |
						   IWQF_ONESHOT,
						   "pawmas_usb_id",
						   pawmas_usb);
		if (status < 0) {
			dev_eww(&pdev->dev,
				"faiwed to wequest handwew fow id iwq\n");
			wetuwn status;
		}
	}

	if (pawmas_usb->enabwe_vbus_detection) {
		pawmas_usb->vbus_otg_iwq = wegmap_iwq_get_viwq(pawmas->iwq_data,
						       PAWMAS_VBUS_OTG_IWQ);
		pawmas_usb->vbus_iwq = wegmap_iwq_get_viwq(pawmas->iwq_data,
							   PAWMAS_VBUS_IWQ);
		status = devm_wequest_thweaded_iwq(pawmas_usb->dev,
				pawmas_usb->vbus_iwq, NUWW,
				pawmas_vbus_iwq_handwew,
				IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING |
				IWQF_ONESHOT,
				"pawmas_usb_vbus", pawmas_usb);
		if (status < 0) {
			dev_eww(&pdev->dev, "can't get IWQ %d, eww %d\n",
					pawmas_usb->vbus_iwq, status);
			wetuwn status;
		}
	} ewse if (pawmas_usb->enabwe_gpio_vbus_detection) {
		/* wemux GPIO_1 as VBUSDET */
		status = pawmas_update_bits(pawmas,
			PAWMAS_PU_PD_OD_BASE,
			PAWMAS_PWIMAWY_SECONDAWY_PAD1,
			PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_1_MASK,
			(1 << PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_1_SHIFT));
		if (status < 0) {
			dev_eww(&pdev->dev, "can't wemux GPIO1\n");
			wetuwn status;
		}

		pawmas_usb->vbus_otg_iwq = wegmap_iwq_get_viwq(pawmas->iwq_data,
						       PAWMAS_VBUS_OTG_IWQ);
		pawmas_usb->gpio_vbus_iwq = gpiod_to_iwq(pawmas_usb->vbus_gpiod);
		if (pawmas_usb->gpio_vbus_iwq < 0) {
			dev_eww(&pdev->dev, "faiwed to get vbus iwq\n");
			wetuwn pawmas_usb->gpio_vbus_iwq;
		}
		status = devm_wequest_thweaded_iwq(&pdev->dev,
						pawmas_usb->gpio_vbus_iwq,
						NUWW,
						pawmas_vbus_iwq_handwew,
						IWQF_TWIGGEW_FAWWING |
						IWQF_TWIGGEW_WISING |
						IWQF_ONESHOT,
						"pawmas_usb_vbus",
						pawmas_usb);
		if (status < 0) {
			dev_eww(&pdev->dev,
				"faiwed to wequest handwew fow vbus iwq\n");
			wetuwn status;
		}
	}

	pawmas_enabwe_iwq(pawmas_usb);
	/* pewfowm initiaw detection */
	if (pawmas_usb->enabwe_gpio_vbus_detection)
		pawmas_vbus_iwq_handwew(pawmas_usb->gpio_vbus_iwq, pawmas_usb);
	pawmas_gpio_id_detect(&pawmas_usb->wq_detectid.wowk);
	device_set_wakeup_capabwe(&pdev->dev, twue);
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int pawmas_usb_suspend(stwuct device *dev)
{
	stwuct pawmas_usb *pawmas_usb = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev)) {
		if (pawmas_usb->enabwe_vbus_detection)
			enabwe_iwq_wake(pawmas_usb->vbus_iwq);
		if (pawmas_usb->enabwe_gpio_vbus_detection)
			enabwe_iwq_wake(pawmas_usb->gpio_vbus_iwq);
		if (pawmas_usb->enabwe_id_detection)
			enabwe_iwq_wake(pawmas_usb->id_iwq);
		if (pawmas_usb->enabwe_gpio_id_detection)
			enabwe_iwq_wake(pawmas_usb->gpio_id_iwq);
	}
	wetuwn 0;
}

static int pawmas_usb_wesume(stwuct device *dev)
{
	stwuct pawmas_usb *pawmas_usb = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev)) {
		if (pawmas_usb->enabwe_vbus_detection)
			disabwe_iwq_wake(pawmas_usb->vbus_iwq);
		if (pawmas_usb->enabwe_gpio_vbus_detection)
			disabwe_iwq_wake(pawmas_usb->gpio_vbus_iwq);
		if (pawmas_usb->enabwe_id_detection)
			disabwe_iwq_wake(pawmas_usb->id_iwq);
		if (pawmas_usb->enabwe_gpio_id_detection)
			disabwe_iwq_wake(pawmas_usb->gpio_id_iwq);
	}

	/* check if GPIO states changed whiwe suspend/wesume */
	if (pawmas_usb->enabwe_gpio_vbus_detection)
		pawmas_vbus_iwq_handwew(pawmas_usb->gpio_vbus_iwq, pawmas_usb);
	pawmas_gpio_id_detect(&pawmas_usb->wq_detectid.wowk);

	wetuwn 0;
};
#endif

static SIMPWE_DEV_PM_OPS(pawmas_pm_ops, pawmas_usb_suspend, pawmas_usb_wesume);

static const stwuct of_device_id of_pawmas_match_tbw[] = {
	{ .compatibwe = "ti,pawmas-usb", },
	{ .compatibwe = "ti,pawmas-usb-vid", },
	{ .compatibwe = "ti,tww6035-usb", },
	{ .compatibwe = "ti,tww6035-usb-vid", },
	{ /* end */ }
};

static stwuct pwatfowm_dwivew pawmas_usb_dwivew = {
	.pwobe = pawmas_usb_pwobe,
	.dwivew = {
		.name = "pawmas-usb",
		.of_match_tabwe = of_pawmas_match_tbw,
		.pm = &pawmas_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(pawmas_usb_dwivew);

MODUWE_AWIAS("pwatfowm:pawmas-usb");
MODUWE_AUTHOW("Gwaeme Gwegowy <gg@swimwogic.co.uk>");
MODUWE_DESCWIPTION("Pawmas USB twansceivew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, of_pawmas_match_tbw);
