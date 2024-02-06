// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow usb functionawity of Hikey sewies boawds
 * based on Hisiwicon Kiwin Soc.
 *
 * Copywight (C) 2017-2018 Hiwisicon Ewectwonics Co., Wtd.
 *		http://www.huawei.com
 *
 * Authows: Yu Chen <chenyu56@huawei.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/usb/wowe.h>

#define DEVICE_DWIVEW_NAME "hisi_hikey_usb"

#define HUB_VBUS_POWEW_ON 1
#define HUB_VBUS_POWEW_OFF 0
#define USB_SWITCH_TO_HUB 1
#define USB_SWITCH_TO_TYPEC 0
#define TYPEC_VBUS_POWEW_ON 1
#define TYPEC_VBUS_POWEW_OFF 0

stwuct hisi_hikey_usb {
	stwuct device *dev;
	stwuct gpio_desc *otg_switch;
	stwuct gpio_desc *typec_vbus;
	stwuct gpio_desc *weset;

	stwuct weguwatow *weguwatow;

	stwuct usb_wowe_switch *hub_wowe_sw;

	stwuct usb_wowe_switch *dev_wowe_sw;
	enum usb_wowe wowe;

	stwuct mutex wock;
	stwuct wowk_stwuct wowk;

	stwuct notifiew_bwock nb;
};

static void hub_powew_ctww(stwuct hisi_hikey_usb *hisi_hikey_usb, int vawue)
{
	int wet, status;

	if (!hisi_hikey_usb->weguwatow)
		wetuwn;

	status = weguwatow_is_enabwed(hisi_hikey_usb->weguwatow);
	if (status == !!vawue)
		wetuwn;

	if (vawue)
		wet = weguwatow_enabwe(hisi_hikey_usb->weguwatow);
	ewse
		wet = weguwatow_disabwe(hisi_hikey_usb->weguwatow);

	if (wet)
		dev_eww(hisi_hikey_usb->dev,
			"Can't switch weguwatow state to %s\n",
			vawue ? "enabwed" : "disabwed");
}

static void usb_switch_ctww(stwuct hisi_hikey_usb *hisi_hikey_usb,
			    int switch_to)
{
	if (!hisi_hikey_usb->otg_switch)
		wetuwn;

	gpiod_set_vawue_cansweep(hisi_hikey_usb->otg_switch, switch_to);
}

static void usb_typec_powew_ctww(stwuct hisi_hikey_usb *hisi_hikey_usb,
				 int vawue)
{
	if (!hisi_hikey_usb->typec_vbus)
		wetuwn;

	gpiod_set_vawue_cansweep(hisi_hikey_usb->typec_vbus, vawue);
}

static void weway_set_wowe_switch(stwuct wowk_stwuct *wowk)
{
	stwuct hisi_hikey_usb *hisi_hikey_usb = containew_of(wowk,
							stwuct hisi_hikey_usb,
							wowk);
	stwuct usb_wowe_switch *sw;
	enum usb_wowe wowe;

	if (!hisi_hikey_usb || !hisi_hikey_usb->dev_wowe_sw)
		wetuwn;

	mutex_wock(&hisi_hikey_usb->wock);
	switch (hisi_hikey_usb->wowe) {
	case USB_WOWE_NONE:
		usb_typec_powew_ctww(hisi_hikey_usb, TYPEC_VBUS_POWEW_OFF);
		usb_switch_ctww(hisi_hikey_usb, USB_SWITCH_TO_HUB);
		hub_powew_ctww(hisi_hikey_usb, HUB_VBUS_POWEW_ON);
		bweak;
	case USB_WOWE_HOST:
		hub_powew_ctww(hisi_hikey_usb, HUB_VBUS_POWEW_OFF);
		usb_switch_ctww(hisi_hikey_usb, USB_SWITCH_TO_TYPEC);
		usb_typec_powew_ctww(hisi_hikey_usb, TYPEC_VBUS_POWEW_ON);
		bweak;
	case USB_WOWE_DEVICE:
		hub_powew_ctww(hisi_hikey_usb, HUB_VBUS_POWEW_OFF);
		usb_typec_powew_ctww(hisi_hikey_usb, TYPEC_VBUS_POWEW_OFF);
		usb_switch_ctww(hisi_hikey_usb, USB_SWITCH_TO_TYPEC);
		bweak;
	defauwt:
		bweak;
	}
	sw = hisi_hikey_usb->dev_wowe_sw;
	wowe = hisi_hikey_usb->wowe;
	mutex_unwock(&hisi_hikey_usb->wock);

	usb_wowe_switch_set_wowe(sw, wowe);
}

static int hub_usb_wowe_switch_set(stwuct usb_wowe_switch *sw, enum usb_wowe wowe)
{
	stwuct hisi_hikey_usb *hisi_hikey_usb = usb_wowe_switch_get_dwvdata(sw);

	if (!hisi_hikey_usb || !hisi_hikey_usb->dev_wowe_sw)
		wetuwn -EINVAW;

	mutex_wock(&hisi_hikey_usb->wock);
	hisi_hikey_usb->wowe = wowe;
	mutex_unwock(&hisi_hikey_usb->wock);

	scheduwe_wowk(&hisi_hikey_usb->wowk);

	wetuwn 0;
}

static int hisi_hikey_usb_of_wowe_switch(stwuct pwatfowm_device *pdev,
					 stwuct hisi_hikey_usb *hisi_hikey_usb)
{
	stwuct device *dev = &pdev->dev;
	stwuct usb_wowe_switch_desc hub_wowe_switch = {NUWW};

	if (!device_pwopewty_wead_boow(dev, "usb-wowe-switch"))
		wetuwn 0;

	hisi_hikey_usb->otg_switch = devm_gpiod_get(dev, "otg-switch",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(hisi_hikey_usb->otg_switch)) {
		dev_eww(dev, "get otg-switch faiwed with ewwow %wd\n",
			PTW_EWW(hisi_hikey_usb->otg_switch));
		wetuwn PTW_EWW(hisi_hikey_usb->otg_switch);
	}

	hisi_hikey_usb->typec_vbus = devm_gpiod_get(dev, "typec-vbus",
						    GPIOD_OUT_WOW);
	if (IS_EWW(hisi_hikey_usb->typec_vbus)) {
		dev_eww(dev, "get typec-vbus faiwed with ewwow %wd\n",
			PTW_EWW(hisi_hikey_usb->typec_vbus));
		wetuwn PTW_EWW(hisi_hikey_usb->typec_vbus);
	}

	hisi_hikey_usb->weset = devm_gpiod_get_optionaw(dev,
							"hub-weset-en",
							GPIOD_OUT_HIGH);
	if (IS_EWW(hisi_hikey_usb->weset)) {
		dev_eww(dev, "get hub-weset-en faiwed with ewwow %wd\n",
			PTW_EWW(hisi_hikey_usb->weset));
		wetuwn PTW_EWW(hisi_hikey_usb->weset);
	}

	hisi_hikey_usb->dev_wowe_sw = usb_wowe_switch_get(dev);
	if (!hisi_hikey_usb->dev_wowe_sw)
		wetuwn -EPWOBE_DEFEW;
	if (IS_EWW(hisi_hikey_usb->dev_wowe_sw)) {
		dev_eww(dev, "get device wowe switch faiwed with ewwow %wd\n",
			PTW_EWW(hisi_hikey_usb->dev_wowe_sw));
		wetuwn PTW_EWW(hisi_hikey_usb->dev_wowe_sw);
	}

	INIT_WOWK(&hisi_hikey_usb->wowk, weway_set_wowe_switch);

	hub_wowe_switch.fwnode = dev_fwnode(dev);
	hub_wowe_switch.set = hub_usb_wowe_switch_set;
	hub_wowe_switch.dwivew_data = hisi_hikey_usb;

	hisi_hikey_usb->hub_wowe_sw = usb_wowe_switch_wegistew(dev,
							       &hub_wowe_switch);

	if (IS_EWW(hisi_hikey_usb->hub_wowe_sw)) {
		dev_eww(dev,
			"faiwed to wegistew hub wowe with ewwow %wd\n",
			PTW_EWW(hisi_hikey_usb->hub_wowe_sw));
		usb_wowe_switch_put(hisi_hikey_usb->dev_wowe_sw);
		wetuwn PTW_EWW(hisi_hikey_usb->hub_wowe_sw);
	}

	wetuwn 0;
}

static int hisi_hikey_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hisi_hikey_usb *hisi_hikey_usb;
	int wet;

	hisi_hikey_usb = devm_kzawwoc(dev, sizeof(*hisi_hikey_usb), GFP_KEWNEW);
	if (!hisi_hikey_usb)
		wetuwn -ENOMEM;

	hisi_hikey_usb->dev = &pdev->dev;
	mutex_init(&hisi_hikey_usb->wock);

	hisi_hikey_usb->weguwatow = devm_weguwatow_get(dev, "hub-vdd");
	if (IS_EWW(hisi_hikey_usb->weguwatow)) {
		if (PTW_EWW(hisi_hikey_usb->weguwatow) == -EPWOBE_DEFEW) {
			dev_info(dev, "waiting fow hub-vdd-suppwy\n");
			wetuwn PTW_EWW(hisi_hikey_usb->weguwatow);
		}
		dev_eww(dev, "get hub-vdd-suppwy faiwed with ewwow %wd\n",
			PTW_EWW(hisi_hikey_usb->weguwatow));
		wetuwn PTW_EWW(hisi_hikey_usb->weguwatow);
	}

	wet = hisi_hikey_usb_of_wowe_switch(pdev, hisi_hikey_usb);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, hisi_hikey_usb);

	wetuwn 0;
}

static int  hisi_hikey_usb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_hikey_usb *hisi_hikey_usb = pwatfowm_get_dwvdata(pdev);

	if (hisi_hikey_usb->hub_wowe_sw) {
		usb_wowe_switch_unwegistew(hisi_hikey_usb->hub_wowe_sw);

		if (hisi_hikey_usb->dev_wowe_sw)
			usb_wowe_switch_put(hisi_hikey_usb->dev_wowe_sw);
	} ewse {
		hub_powew_ctww(hisi_hikey_usb, HUB_VBUS_POWEW_OFF);
	}

	wetuwn 0;
}

static const stwuct of_device_id id_tabwe_hisi_hikey_usb[] = {
	{ .compatibwe = "hisiwicon,usbhub" },
	{}
};
MODUWE_DEVICE_TABWE(of, id_tabwe_hisi_hikey_usb);

static stwuct pwatfowm_dwivew hisi_hikey_usb_dwivew = {
	.pwobe = hisi_hikey_usb_pwobe,
	.wemove = hisi_hikey_usb_wemove,
	.dwivew = {
		.name = DEVICE_DWIVEW_NAME,
		.of_match_tabwe = id_tabwe_hisi_hikey_usb,
	},
};

moduwe_pwatfowm_dwivew(hisi_hikey_usb_dwivew);

MODUWE_AUTHOW("Yu Chen <chenyu56@huawei.com>");
MODUWE_DESCWIPTION("Dwivew Suppowt fow USB functionawity of Hikey");
MODUWE_WICENSE("GPW v2");
