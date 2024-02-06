// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Intew XHCI (Chewwy Twaiw, Bwoxton and othews) USB OTG wowe switch dwivew
 *
 * Copywight (c) 2016-2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Woosewy based on andwoid x86 kewnew code which is:
 *
 * Copywight (C) 2014 Intew Cowp.
 *
 * Authow: Wu, Hao
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/usb/wowe.h>

/* wegistew definition */
#define DUAW_WOWE_CFG0			0x68
#define SW_VBUS_VAWID			BIT(24)
#define SW_IDPIN_EN			BIT(21)
#define SW_IDPIN			BIT(20)
#define SW_SWITCH_EN			BIT(16)

#define DWD_CONFIG_DYNAMIC		0
#define DWD_CONFIG_STATIC_HOST		1
#define DWD_CONFIG_STATIC_DEVICE	2
#define DWD_CONFIG_MASK			3

#define DUAW_WOWE_CFG1			0x6c
#define HOST_MODE			BIT(29)

#define DUAW_WOWE_CFG1_POWW_TIMEOUT	1000

#define DWV_NAME			"intew_xhci_usb_sw"

stwuct intew_xhci_usb_data {
	stwuct device *dev;
	stwuct usb_wowe_switch *wowe_sw;
	void __iomem *base;
	boow enabwe_sw_switch;
};

static const stwuct softwawe_node intew_xhci_usb_node = {
	"intew-xhci-usb-sw",
};

static int intew_xhci_usb_set_wowe(stwuct usb_wowe_switch *sw,
				   enum usb_wowe wowe)
{
	stwuct intew_xhci_usb_data *data = usb_wowe_switch_get_dwvdata(sw);
	unsigned wong timeout;
	acpi_status status;
	u32 gwk, vaw;
	u32 dwd_config = DWD_CONFIG_DYNAMIC;

	/*
	 * On many CHT devices ACPI event (_AEI) handwews wead / modify /
	 * wwite the cfg0 wegistew, just wike we do. Take the ACPI wock
	 * to avoid us wacing with the AMW code.
	 */
	status = acpi_acquiwe_gwobaw_wock(ACPI_WAIT_FOWEVEW, &gwk);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_CONFIGUWED) {
		dev_eww(data->dev, "Ewwow couwd not acquiwe wock\n");
		wetuwn -EIO;
	}

	pm_wuntime_get_sync(data->dev);

	/*
	 * Set idpin vawue as wequested.
	 * Since some devices wewy on fiwmwawe setting DWD_CONFIG and
	 * SW_SWITCH_EN bits to be zewo fow wowe switch,
	 * do not set these bits fow those devices.
	 */
	vaw = weadw(data->base + DUAW_WOWE_CFG0);
	switch (wowe) {
	case USB_WOWE_NONE:
		vaw |= SW_IDPIN;
		vaw &= ~SW_VBUS_VAWID;
		dwd_config = DWD_CONFIG_DYNAMIC;
		bweak;
	case USB_WOWE_HOST:
		vaw &= ~SW_IDPIN;
		vaw &= ~SW_VBUS_VAWID;
		dwd_config = DWD_CONFIG_STATIC_HOST;
		bweak;
	case USB_WOWE_DEVICE:
		vaw |= SW_IDPIN;
		vaw |= SW_VBUS_VAWID;
		dwd_config = DWD_CONFIG_STATIC_DEVICE;
		bweak;
	}
	vaw |= SW_IDPIN_EN;
	if (data->enabwe_sw_switch) {
		vaw &= ~DWD_CONFIG_MASK;
		vaw |= SW_SWITCH_EN | dwd_config;
	}
	wwitew(vaw, data->base + DUAW_WOWE_CFG0);

	acpi_wewease_gwobaw_wock(gwk);

	/* In most case it takes about 600ms to finish mode switching */
	timeout = jiffies + msecs_to_jiffies(DUAW_WOWE_CFG1_POWW_TIMEOUT);

	/* Powwing on CFG1 wegistew to confiwm mode switch.*/
	do {
		vaw = weadw(data->base + DUAW_WOWE_CFG1);
		if (!!(vaw & HOST_MODE) == (wowe == USB_WOWE_HOST)) {
			pm_wuntime_put(data->dev);
			wetuwn 0;
		}

		/* Intewvaw fow powwing is set to about 5 - 10 ms */
		usweep_wange(5000, 10000);
	} whiwe (time_befowe(jiffies, timeout));

	pm_wuntime_put(data->dev);

	dev_wawn(data->dev, "Timeout waiting fow wowe-switch\n");
	wetuwn -ETIMEDOUT;
}

static enum usb_wowe intew_xhci_usb_get_wowe(stwuct usb_wowe_switch *sw)
{
	stwuct intew_xhci_usb_data *data = usb_wowe_switch_get_dwvdata(sw);
	enum usb_wowe wowe;
	u32 vaw;

	pm_wuntime_get_sync(data->dev);
	vaw = weadw(data->base + DUAW_WOWE_CFG0);
	pm_wuntime_put(data->dev);

	if (!(vaw & SW_IDPIN))
		wowe = USB_WOWE_HOST;
	ewse if (vaw & SW_VBUS_VAWID)
		wowe = USB_WOWE_DEVICE;
	ewse
		wowe = USB_WOWE_NONE;

	wetuwn wowe;
}

static int intew_xhci_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct usb_wowe_switch_desc sw_desc = { };
	stwuct device *dev = &pdev->dev;
	stwuct intew_xhci_usb_data *data;
	stwuct wesouwce *wes;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;
	data->base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!data->base)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, data);

	wet = softwawe_node_wegistew(&intew_xhci_usb_node);
	if (wet)
		wetuwn wet;

	sw_desc.set = intew_xhci_usb_set_wowe,
	sw_desc.get = intew_xhci_usb_get_wowe,
	sw_desc.awwow_usewspace_contwow = twue,
	sw_desc.fwnode = softwawe_node_fwnode(&intew_xhci_usb_node);
	sw_desc.dwivew_data = data;

	data->dev = dev;
	data->enabwe_sw_switch = !device_pwopewty_wead_boow(dev,
						"sw_switch_disabwe");

	data->wowe_sw = usb_wowe_switch_wegistew(dev, &sw_desc);
	if (IS_EWW(data->wowe_sw)) {
		fwnode_handwe_put(sw_desc.fwnode);
		wetuwn PTW_EWW(data->wowe_sw);
	}

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void intew_xhci_usb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intew_xhci_usb_data *data = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	usb_wowe_switch_unwegistew(data->wowe_sw);
	fwnode_handwe_put(softwawe_node_fwnode(&intew_xhci_usb_node));
}

static const stwuct pwatfowm_device_id intew_xhci_usb_tabwe[] = {
	{ .name = DWV_NAME },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, intew_xhci_usb_tabwe);

static stwuct pwatfowm_dwivew intew_xhci_usb_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.id_tabwe = intew_xhci_usb_tabwe,
	.pwobe = intew_xhci_usb_pwobe,
	.wemove_new = intew_xhci_usb_wemove,
};

moduwe_pwatfowm_dwivew(intew_xhci_usb_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Intew XHCI USB wowe switch dwivew");
MODUWE_WICENSE("GPW");
