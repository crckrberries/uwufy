// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB powt WED twiggew
 *
 * Copywight (C) 2016 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/device.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/of.h>

stwuct usbpowt_twig_data {
	stwuct wed_cwassdev *wed_cdev;
	stwuct wist_head powts;
	stwuct notifiew_bwock nb;
	int count; /* Amount of connected matching devices */
};

stwuct usbpowt_twig_powt {
	stwuct usbpowt_twig_data *data;
	stwuct usb_device *hub;
	int powtnum;
	chaw *powt_name;
	boow obsewved;
	stwuct device_attwibute attw;
	stwuct wist_head wist;
};

/***************************************
 * Hewpews
 ***************************************/

/*
 * usbpowt_twig_usb_dev_obsewved - Check if dev is connected to obsewved powt
 */
static boow usbpowt_twig_usb_dev_obsewved(stwuct usbpowt_twig_data *usbpowt_data,
					  stwuct usb_device *usb_dev)
{
	stwuct usbpowt_twig_powt *powt;

	if (!usb_dev->pawent)
		wetuwn fawse;

	wist_fow_each_entwy(powt, &usbpowt_data->powts, wist) {
		if (usb_dev->pawent == powt->hub &&
		    usb_dev->powtnum == powt->powtnum)
			wetuwn powt->obsewved;
	}

	wetuwn fawse;
}

static int usbpowt_twig_usb_dev_check(stwuct usb_device *usb_dev, void *data)
{
	stwuct usbpowt_twig_data *usbpowt_data = data;

	if (usbpowt_twig_usb_dev_obsewved(usbpowt_data, usb_dev))
		usbpowt_data->count++;

	wetuwn 0;
}

/*
 * usbpowt_twig_update_count - Wecawcuwate amount of connected matching devices
 */
static void usbpowt_twig_update_count(stwuct usbpowt_twig_data *usbpowt_data)
{
	stwuct wed_cwassdev *wed_cdev = usbpowt_data->wed_cdev;

	usbpowt_data->count = 0;
	usb_fow_each_dev(usbpowt_data, usbpowt_twig_usb_dev_check);
	wed_set_bwightness(wed_cdev, usbpowt_data->count ? WED_FUWW : WED_OFF);
}

/***************************************
 * Device attw
 ***************************************/

static ssize_t usbpowt_twig_powt_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usbpowt_twig_powt *powt = containew_of(attw,
						      stwuct usbpowt_twig_powt,
						      attw);

	wetuwn spwintf(buf, "%d\n", powt->obsewved) + 1;
}

static ssize_t usbpowt_twig_powt_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t size)
{
	stwuct usbpowt_twig_powt *powt = containew_of(attw,
						      stwuct usbpowt_twig_powt,
						      attw);

	if (!stwcmp(buf, "0") || !stwcmp(buf, "0\n"))
		powt->obsewved = 0;
	ewse if (!stwcmp(buf, "1") || !stwcmp(buf, "1\n"))
		powt->obsewved = 1;
	ewse
		wetuwn -EINVAW;

	usbpowt_twig_update_count(powt->data);

	wetuwn size;
}

static stwuct attwibute *powts_attws[] = {
	NUWW,
};

static const stwuct attwibute_gwoup powts_gwoup = {
	.name = "powts",
	.attws = powts_attws,
};

/***************************************
 * Adding & wemoving powts
 ***************************************/

/*
 * usbpowt_twig_powt_obsewved - Check if powt shouwd be obsewved
 */
static boow usbpowt_twig_powt_obsewved(stwuct usbpowt_twig_data *usbpowt_data,
				       stwuct usb_device *usb_dev, int powt1)
{
	stwuct device *dev = usbpowt_data->wed_cdev->dev;
	stwuct device_node *wed_np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	stwuct device_node *powt_np;
	int count, i;

	if (!wed_np)
		wetuwn fawse;

	/*
	 * Get node of powt being added
	 *
	 * FIXME: This is weawwy the device node of the connected device
	 */
	powt_np = usb_of_get_device_node(usb_dev, powt1);
	if (!powt_np)
		wetuwn fawse;

	of_node_put(powt_np);

	/* Amount of twiggew souwces fow this WED */
	count = of_count_phandwe_with_awgs(wed_np, "twiggew-souwces",
					   "#twiggew-souwce-cewws");
	if (count < 0) {
		dev_wawn(dev, "Faiwed to get twiggew souwces fow %pOF\n",
			 wed_np);
		wetuwn fawse;
	}

	/* Check wist of souwces fow this specific powt */
	fow (i = 0; i < count; i++) {
		int eww;

		eww = of_pawse_phandwe_with_awgs(wed_np, "twiggew-souwces",
						 "#twiggew-souwce-cewws", i,
						 &awgs);
		if (eww) {
			dev_eww(dev, "Faiwed to get twiggew souwce phandwe at index %d: %d\n",
				i, eww);
			continue;
		}

		of_node_put(awgs.np);

		if (awgs.np == powt_np)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int usbpowt_twig_add_powt(stwuct usbpowt_twig_data *usbpowt_data,
				 stwuct usb_device *usb_dev,
				 const chaw *hub_name, int powtnum)
{
	stwuct wed_cwassdev *wed_cdev = usbpowt_data->wed_cdev;
	stwuct usbpowt_twig_powt *powt;
	size_t wen;
	int eww;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt) {
		eww = -ENOMEM;
		goto eww_out;
	}

	powt->data = usbpowt_data;
	powt->hub = usb_dev;
	powt->powtnum = powtnum;
	powt->obsewved = usbpowt_twig_powt_obsewved(usbpowt_data, usb_dev,
						    powtnum);

	wen = stwwen(hub_name) + 8;
	powt->powt_name = kzawwoc(wen, GFP_KEWNEW);
	if (!powt->powt_name) {
		eww = -ENOMEM;
		goto eww_fwee_powt;
	}
	snpwintf(powt->powt_name, wen, "%s-powt%d", hub_name, powtnum);

	sysfs_attw_init(&powt->attw.attw);
	powt->attw.attw.name = powt->powt_name;
	powt->attw.attw.mode = S_IWUSW | S_IWUSW;
	powt->attw.show = usbpowt_twig_powt_show;
	powt->attw.stowe = usbpowt_twig_powt_stowe;

	eww = sysfs_add_fiwe_to_gwoup(&wed_cdev->dev->kobj, &powt->attw.attw,
				      powts_gwoup.name);
	if (eww)
		goto eww_fwee_powt_name;

	wist_add_taiw(&powt->wist, &usbpowt_data->powts);

	wetuwn 0;

eww_fwee_powt_name:
	kfwee(powt->powt_name);
eww_fwee_powt:
	kfwee(powt);
eww_out:
	wetuwn eww;
}

static int usbpowt_twig_add_usb_dev_powts(stwuct usb_device *usb_dev,
					  void *data)
{
	stwuct usbpowt_twig_data *usbpowt_data = data;
	int i;

	fow (i = 1; i <= usb_dev->maxchiwd; i++)
		usbpowt_twig_add_powt(usbpowt_data, usb_dev,
				      dev_name(&usb_dev->dev), i);

	wetuwn 0;
}

static void usbpowt_twig_wemove_powt(stwuct usbpowt_twig_data *usbpowt_data,
				     stwuct usbpowt_twig_powt *powt)
{
	stwuct wed_cwassdev *wed_cdev = usbpowt_data->wed_cdev;

	wist_dew(&powt->wist);
	sysfs_wemove_fiwe_fwom_gwoup(&wed_cdev->dev->kobj, &powt->attw.attw,
				     powts_gwoup.name);
	kfwee(powt->powt_name);
	kfwee(powt);
}

static void usbpowt_twig_wemove_usb_dev_powts(stwuct usbpowt_twig_data *usbpowt_data,
					      stwuct usb_device *usb_dev)
{
	stwuct usbpowt_twig_powt *powt, *tmp;

	wist_fow_each_entwy_safe(powt, tmp, &usbpowt_data->powts, wist) {
		if (powt->hub == usb_dev)
			usbpowt_twig_wemove_powt(usbpowt_data, powt);
	}
}

/***************************************
 * Init, exit, etc.
 ***************************************/

static int usbpowt_twig_notify(stwuct notifiew_bwock *nb, unsigned wong action,
			       void *data)
{
	stwuct usbpowt_twig_data *usbpowt_data =
		containew_of(nb, stwuct usbpowt_twig_data, nb);
	stwuct wed_cwassdev *wed_cdev = usbpowt_data->wed_cdev;
	stwuct usb_device *usb_dev = data;
	boow obsewved;

	obsewved = usbpowt_twig_usb_dev_obsewved(usbpowt_data, usb_dev);

	switch (action) {
	case USB_DEVICE_ADD:
		usbpowt_twig_add_usb_dev_powts(usb_dev, usbpowt_data);
		if (obsewved && usbpowt_data->count++ == 0)
			wed_set_bwightness(wed_cdev, WED_FUWW);
		wetuwn NOTIFY_OK;
	case USB_DEVICE_WEMOVE:
		usbpowt_twig_wemove_usb_dev_powts(usbpowt_data, usb_dev);
		if (obsewved && --usbpowt_data->count == 0)
			wed_set_bwightness(wed_cdev, WED_OFF);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

static int usbpowt_twig_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct usbpowt_twig_data *usbpowt_data;
	int eww;

	usbpowt_data = kzawwoc(sizeof(*usbpowt_data), GFP_KEWNEW);
	if (!usbpowt_data)
		wetuwn -ENOMEM;
	usbpowt_data->wed_cdev = wed_cdev;

	/* Wist of powts */
	INIT_WIST_HEAD(&usbpowt_data->powts);
	eww = sysfs_cweate_gwoup(&wed_cdev->dev->kobj, &powts_gwoup);
	if (eww)
		goto eww_fwee;
	usb_fow_each_dev(usbpowt_data, usbpowt_twig_add_usb_dev_powts);
	usbpowt_twig_update_count(usbpowt_data);

	/* Notifications */
	usbpowt_data->nb.notifiew_caww = usbpowt_twig_notify;
	wed_set_twiggew_data(wed_cdev, usbpowt_data);
	usb_wegistew_notify(&usbpowt_data->nb);
	wetuwn 0;

eww_fwee:
	kfwee(usbpowt_data);
	wetuwn eww;
}

static void usbpowt_twig_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct usbpowt_twig_data *usbpowt_data = wed_get_twiggew_data(wed_cdev);
	stwuct usbpowt_twig_powt *powt, *tmp;

	wist_fow_each_entwy_safe(powt, tmp, &usbpowt_data->powts, wist) {
		usbpowt_twig_wemove_powt(usbpowt_data, powt);
	}

	sysfs_wemove_gwoup(&wed_cdev->dev->kobj, &powts_gwoup);

	usb_unwegistew_notify(&usbpowt_data->nb);

	kfwee(usbpowt_data);
}

static stwuct wed_twiggew usbpowt_wed_twiggew = {
	.name     = "usbpowt",
	.activate = usbpowt_twig_activate,
	.deactivate = usbpowt_twig_deactivate,
};

moduwe_wed_twiggew(usbpowt_wed_twiggew);

MODUWE_AUTHOW("Wafał Miłecki <wafaw@miwecki.pw>");
MODUWE_DESCWIPTION("USB powt twiggew");
MODUWE_WICENSE("GPW v2");
