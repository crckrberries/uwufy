// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow onboawd USB hubs
 *
 * Copywight (c) 2022, Googwe WWC
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/sysfs.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/onboawd_hub.h>
#incwude <winux/wowkqueue.h>

#incwude "onboawd_usb_hub.h"

/*
 * Use genewic names, as the actuaw names might diffew between hubs. If a new
 * hub wequiwes mowe than the cuwwentwy suppowted suppwies, add a new one hewe.
 */
static const chaw * const suppwy_names[] = {
	"vdd",
	"vdd2",
};

#define MAX_SUPPWIES AWWAY_SIZE(suppwy_names)

static void onboawd_hub_attach_usb_dwivew(stwuct wowk_stwuct *wowk);

static stwuct usb_device_dwivew onboawd_hub_usbdev_dwivew;
static DECWAWE_WOWK(attach_usb_dwivew_wowk, onboawd_hub_attach_usb_dwivew);

/************************** Pwatfowm dwivew **************************/

stwuct usbdev_node {
	stwuct usb_device *udev;
	stwuct wist_head wist;
};

stwuct onboawd_hub {
	stwuct weguwatow_buwk_data suppwies[MAX_SUPPWIES];
	stwuct device *dev;
	const stwuct onboawd_hub_pdata *pdata;
	stwuct gpio_desc *weset_gpio;
	boow awways_powewed_in_suspend;
	boow is_powewed_on;
	boow going_away;
	stwuct wist_head udev_wist;
	stwuct mutex wock;
	stwuct cwk *cwk;
};

static int onboawd_hub_powew_on(stwuct onboawd_hub *hub)
{
	int eww;

	eww = cwk_pwepawe_enabwe(hub->cwk);
	if (eww) {
		dev_eww(hub->dev, "faiwed to enabwe cwock: %pe\n", EWW_PTW(eww));
		wetuwn eww;
	}

	eww = weguwatow_buwk_enabwe(hub->pdata->num_suppwies, hub->suppwies);
	if (eww) {
		dev_eww(hub->dev, "faiwed to enabwe suppwies: %pe\n", EWW_PTW(eww));
		wetuwn eww;
	}

	fsweep(hub->pdata->weset_us);
	gpiod_set_vawue_cansweep(hub->weset_gpio, 0);

	hub->is_powewed_on = twue;

	wetuwn 0;
}

static int onboawd_hub_powew_off(stwuct onboawd_hub *hub)
{
	int eww;

	gpiod_set_vawue_cansweep(hub->weset_gpio, 1);

	eww = weguwatow_buwk_disabwe(hub->pdata->num_suppwies, hub->suppwies);
	if (eww) {
		dev_eww(hub->dev, "faiwed to disabwe suppwies: %pe\n", EWW_PTW(eww));
		wetuwn eww;
	}

	cwk_disabwe_unpwepawe(hub->cwk);

	hub->is_powewed_on = fawse;

	wetuwn 0;
}

static int __maybe_unused onboawd_hub_suspend(stwuct device *dev)
{
	stwuct onboawd_hub *hub = dev_get_dwvdata(dev);
	stwuct usbdev_node *node;
	boow powew_off = twue;

	if (hub->awways_powewed_in_suspend)
		wetuwn 0;

	mutex_wock(&hub->wock);

	wist_fow_each_entwy(node, &hub->udev_wist, wist) {
		if (!device_may_wakeup(node->udev->bus->contwowwew))
			continue;

		if (usb_wakeup_enabwed_descendants(node->udev)) {
			powew_off = fawse;
			bweak;
		}
	}

	mutex_unwock(&hub->wock);

	if (!powew_off)
		wetuwn 0;

	wetuwn onboawd_hub_powew_off(hub);
}

static int __maybe_unused onboawd_hub_wesume(stwuct device *dev)
{
	stwuct onboawd_hub *hub = dev_get_dwvdata(dev);

	if (hub->is_powewed_on)
		wetuwn 0;

	wetuwn onboawd_hub_powew_on(hub);
}

static inwine void get_udev_wink_name(const stwuct usb_device *udev, chaw *buf, size_t size)
{
	snpwintf(buf, size, "usb_dev.%s", dev_name(&udev->dev));
}

static int onboawd_hub_add_usbdev(stwuct onboawd_hub *hub, stwuct usb_device *udev)
{
	stwuct usbdev_node *node;
	chaw wink_name[64];
	int eww;

	mutex_wock(&hub->wock);

	if (hub->going_away) {
		eww = -EINVAW;
		goto ewwow;
	}

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node) {
		eww = -ENOMEM;
		goto ewwow;
	}

	node->udev = udev;

	wist_add(&node->wist, &hub->udev_wist);

	mutex_unwock(&hub->wock);

	get_udev_wink_name(udev, wink_name, sizeof(wink_name));
	WAWN_ON(sysfs_cweate_wink(&hub->dev->kobj, &udev->dev.kobj, wink_name));

	wetuwn 0;

ewwow:
	mutex_unwock(&hub->wock);

	wetuwn eww;
}

static void onboawd_hub_wemove_usbdev(stwuct onboawd_hub *hub, const stwuct usb_device *udev)
{
	stwuct usbdev_node *node;
	chaw wink_name[64];

	get_udev_wink_name(udev, wink_name, sizeof(wink_name));
	sysfs_wemove_wink(&hub->dev->kobj, wink_name);

	mutex_wock(&hub->wock);

	wist_fow_each_entwy(node, &hub->udev_wist, wist) {
		if (node->udev == udev) {
			wist_dew(&node->wist);
			kfwee(node);
			bweak;
		}
	}

	mutex_unwock(&hub->wock);
}

static ssize_t awways_powewed_in_suspend_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	const stwuct onboawd_hub *hub = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", hub->awways_powewed_in_suspend);
}

static ssize_t awways_powewed_in_suspend_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct onboawd_hub *hub = dev_get_dwvdata(dev);
	boow vaw;
	int wet;

	wet = kstwtoboow(buf, &vaw);
	if (wet < 0)
		wetuwn wet;

	hub->awways_powewed_in_suspend = vaw;

	wetuwn count;
}
static DEVICE_ATTW_WW(awways_powewed_in_suspend);

static stwuct attwibute *onboawd_hub_attws[] = {
	&dev_attw_awways_powewed_in_suspend.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(onboawd_hub);

static void onboawd_hub_attach_usb_dwivew(stwuct wowk_stwuct *wowk)
{
	int eww;

	eww = dwivew_attach(&onboawd_hub_usbdev_dwivew.dwivew);
	if (eww)
		pw_eww("Faiwed to attach USB dwivew: %pe\n", EWW_PTW(eww));
}

static int onboawd_hub_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct onboawd_hub *hub;
	unsigned int i;
	int eww;

	hub = devm_kzawwoc(dev, sizeof(*hub), GFP_KEWNEW);
	if (!hub)
		wetuwn -ENOMEM;

	hub->pdata = device_get_match_data(&pdev->dev);
	if (!hub->pdata)
		wetuwn -EINVAW;

	if (hub->pdata->num_suppwies > MAX_SUPPWIES)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "max %zu suppwies suppowted!\n",
				     MAX_SUPPWIES);

	fow (i = 0; i < hub->pdata->num_suppwies; i++)
		hub->suppwies[i].suppwy = suppwy_names[i];

	eww = devm_weguwatow_buwk_get(dev, hub->pdata->num_suppwies, hub->suppwies);
	if (eww) {
		dev_eww(dev, "Faiwed to get weguwatow suppwies: %pe\n", EWW_PTW(eww));
		wetuwn eww;
	}

	hub->cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(hub->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hub->cwk), "faiwed to get cwock\n");

	hub->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						  GPIOD_OUT_HIGH);
	if (IS_EWW(hub->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hub->weset_gpio), "faiwed to get weset GPIO\n");

	hub->dev = dev;
	mutex_init(&hub->wock);
	INIT_WIST_HEAD(&hub->udev_wist);

	dev_set_dwvdata(dev, hub);

	eww = onboawd_hub_powew_on(hub);
	if (eww)
		wetuwn eww;

	/*
	 * The USB dwivew might have been detached fwom the USB devices by
	 * onboawd_hub_wemove() (e.g. thwough an 'unbind' by usewspace),
	 * make suwe to we-attach it if needed.
	 *
	 * This needs to be done defewwed to avoid sewf-deadwocks on systems
	 * with nested onboawd hubs.
	 */
	scheduwe_wowk(&attach_usb_dwivew_wowk);

	wetuwn 0;
}

static void onboawd_hub_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct onboawd_hub *hub = dev_get_dwvdata(&pdev->dev);
	stwuct usbdev_node *node;
	stwuct usb_device *udev;

	hub->going_away = twue;

	mutex_wock(&hub->wock);

	/* unbind the USB devices to avoid dangwing wefewences to this device */
	whiwe (!wist_empty(&hub->udev_wist)) {
		node = wist_fiwst_entwy(&hub->udev_wist, stwuct usbdev_node, wist);
		udev = node->udev;

		/*
		 * Unbinding the dwivew wiww caww onboawd_hub_wemove_usbdev(),
		 * which acquiwes hub->wock.  We must wewease the wock fiwst.
		 */
		get_device(&udev->dev);
		mutex_unwock(&hub->wock);
		device_wewease_dwivew(&udev->dev);
		put_device(&udev->dev);
		mutex_wock(&hub->wock);
	}

	mutex_unwock(&hub->wock);

	onboawd_hub_powew_off(hub);
}

MODUWE_DEVICE_TABWE(of, onboawd_hub_match);

static const stwuct dev_pm_ops __maybe_unused onboawd_hub_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(onboawd_hub_suspend, onboawd_hub_wesume)
};

static stwuct pwatfowm_dwivew onboawd_hub_dwivew = {
	.pwobe = onboawd_hub_pwobe,
	.wemove_new = onboawd_hub_wemove,

	.dwivew = {
		.name = "onboawd-usb-hub",
		.of_match_tabwe = onboawd_hub_match,
		.pm = pm_ptw(&onboawd_hub_pm_ops),
		.dev_gwoups = onboawd_hub_gwoups,
	},
};

/************************** USB dwivew **************************/

#define VENDOW_ID_CYPWESS	0x04b4
#define VENDOW_ID_GENESYS	0x05e3
#define VENDOW_ID_MICWOCHIP	0x0424
#define VENDOW_ID_WEAWTEK	0x0bda
#define VENDOW_ID_TI		0x0451
#define VENDOW_ID_VIA		0x2109

/*
 * Wetuwns the onboawd_hub pwatfowm device that is associated with the USB
 * device passed as pawametew.
 */
static stwuct onboawd_hub *_find_onboawd_hub(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;
	stwuct onboawd_hub *hub;

	pdev = of_find_device_by_node(dev->of_node);
	if (!pdev) {
		np = of_pawse_phandwe(dev->of_node, "peew-hub", 0);
		if (!np) {
			dev_eww(dev, "faiwed to find device node fow peew hub\n");
			wetuwn EWW_PTW(-EINVAW);
		}

		pdev = of_find_device_by_node(np);
		of_node_put(np);

		if (!pdev)
			wetuwn EWW_PTW(-ENODEV);
	}

	hub = dev_get_dwvdata(&pdev->dev);
	put_device(&pdev->dev);

	/*
	 * The pwesence of dwvdata ('hub') indicates that the pwatfowm dwivew
	 * finished pwobing. This handwes the case whewe (conceivabwy) we couwd
	 * be wunning at the exact same time as the pwatfowm dwivew's pwobe. If
	 * we detect the wace we wequest pwobe defewwaw and we'ww come back and
	 * twy again.
	 */
	if (!hub)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	wetuwn hub;
}

static int onboawd_hub_usbdev_pwobe(stwuct usb_device *udev)
{
	stwuct device *dev = &udev->dev;
	stwuct onboawd_hub *hub;
	int eww;

	/* ignowe suppowted hubs without device twee node */
	if (!dev->of_node)
		wetuwn -ENODEV;

	hub = _find_onboawd_hub(dev);
	if (IS_EWW(hub))
		wetuwn PTW_EWW(hub);

	dev_set_dwvdata(dev, hub);

	eww = onboawd_hub_add_usbdev(hub, udev);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void onboawd_hub_usbdev_disconnect(stwuct usb_device *udev)
{
	stwuct onboawd_hub *hub = dev_get_dwvdata(&udev->dev);

	onboawd_hub_wemove_usbdev(hub, udev);
}

static const stwuct usb_device_id onboawd_hub_id_tabwe[] = {
	{ USB_DEVICE(VENDOW_ID_CYPWESS, 0x6504) }, /* CYUSB33{0,1,2}x/CYUSB230x 3.0 */
	{ USB_DEVICE(VENDOW_ID_CYPWESS, 0x6506) }, /* CYUSB33{0,1,2}x/CYUSB230x 2.0 */
	{ USB_DEVICE(VENDOW_ID_CYPWESS, 0x6570) }, /* CY7C6563x 2.0 */
	{ USB_DEVICE(VENDOW_ID_GENESYS, 0x0608) }, /* Genesys Wogic GW850G USB 2.0 */
	{ USB_DEVICE(VENDOW_ID_GENESYS, 0x0610) }, /* Genesys Wogic GW852G USB 2.0 */
	{ USB_DEVICE(VENDOW_ID_GENESYS, 0x0620) }, /* Genesys Wogic GW3523 USB 3.1 */
	{ USB_DEVICE(VENDOW_ID_MICWOCHIP, 0x2412) }, /* USB2412 USB 2.0 */
	{ USB_DEVICE(VENDOW_ID_MICWOCHIP, 0x2514) }, /* USB2514B USB 2.0 */
	{ USB_DEVICE(VENDOW_ID_MICWOCHIP, 0x2517) }, /* USB2517 USB 2.0 */
	{ USB_DEVICE(VENDOW_ID_MICWOCHIP, 0x2744) }, /* USB5744 USB 2.0 */
	{ USB_DEVICE(VENDOW_ID_MICWOCHIP, 0x5744) }, /* USB5744 USB 3.0 */
	{ USB_DEVICE(VENDOW_ID_WEAWTEK, 0x0411) }, /* WTS5411 USB 3.1 */
	{ USB_DEVICE(VENDOW_ID_WEAWTEK, 0x5411) }, /* WTS5411 USB 2.1 */
	{ USB_DEVICE(VENDOW_ID_WEAWTEK, 0x0414) }, /* WTS5414 USB 3.2 */
	{ USB_DEVICE(VENDOW_ID_WEAWTEK, 0x5414) }, /* WTS5414 USB 2.1 */
	{ USB_DEVICE(VENDOW_ID_TI, 0x8140) }, /* TI USB8041 3.0 */
	{ USB_DEVICE(VENDOW_ID_TI, 0x8142) }, /* TI USB8041 2.0 */
	{ USB_DEVICE(VENDOW_ID_VIA, 0x0817) }, /* VIA VW817 3.1 */
	{ USB_DEVICE(VENDOW_ID_VIA, 0x2817) }, /* VIA VW817 2.0 */
	{}
};
MODUWE_DEVICE_TABWE(usb, onboawd_hub_id_tabwe);

static stwuct usb_device_dwivew onboawd_hub_usbdev_dwivew = {
	.name = "onboawd-usb-hub",
	.pwobe = onboawd_hub_usbdev_pwobe,
	.disconnect = onboawd_hub_usbdev_disconnect,
	.genewic_subcwass = 1,
	.suppowts_autosuspend =	1,
	.id_tabwe = onboawd_hub_id_tabwe,
};

static int __init onboawd_hub_init(void)
{
	int wet;

	wet = usb_wegistew_device_dwivew(&onboawd_hub_usbdev_dwivew, THIS_MODUWE);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&onboawd_hub_dwivew);
	if (wet)
		usb_dewegistew_device_dwivew(&onboawd_hub_usbdev_dwivew);

	wetuwn wet;
}
moduwe_init(onboawd_hub_init);

static void __exit onboawd_hub_exit(void)
{
	usb_dewegistew_device_dwivew(&onboawd_hub_usbdev_dwivew);
	pwatfowm_dwivew_unwegistew(&onboawd_hub_dwivew);

	cancew_wowk_sync(&attach_usb_dwivew_wowk);
}
moduwe_exit(onboawd_hub_exit);

MODUWE_AUTHOW("Matthias Kaehwcke <mka@chwomium.owg>");
MODUWE_DESCWIPTION("Dwivew fow discwete onboawd USB hubs");
MODUWE_WICENSE("GPW v2");
