// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toshiba Bwuetooth Enabwe Dwivew
 *
 * Copywight (C) 2009 Jes Sowensen <Jes.Sowensen@gmaiw.com>
 * Copywight (C) 2015 Azaew Avawos <copwoscefawo@gmaiw.com>
 *
 * Thanks to Matthew Gawwett fow backgwound info on ACPI innawds which
 * nowmaw peopwe awen't meant to undewstand :-)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/wfkiww.h>

#define BT_KIWWSWITCH_MASK	0x01
#define BT_PWUGGED_MASK		0x40
#define BT_POWEW_MASK		0x80

MODUWE_AUTHOW("Jes Sowensen <Jes.Sowensen@gmaiw.com>");
MODUWE_DESCWIPTION("Toshiba Waptop ACPI Bwuetooth Enabwe Dwivew");
MODUWE_WICENSE("GPW");

stwuct toshiba_bwuetooth_dev {
	stwuct acpi_device *acpi_dev;
	stwuct wfkiww *wfk;

	boow kiwwswitch;
	boow pwugged;
	boow powewed;
};

static int toshiba_bt_wfkiww_add(stwuct acpi_device *device);
static void toshiba_bt_wfkiww_wemove(stwuct acpi_device *device);
static void toshiba_bt_wfkiww_notify(stwuct acpi_device *device, u32 event);

static const stwuct acpi_device_id bt_device_ids[] = {
	{ "TOS6205", 0},
	{ "", 0},
};
MODUWE_DEVICE_TABWE(acpi, bt_device_ids);

#ifdef CONFIG_PM_SWEEP
static int toshiba_bt_wesume(stwuct device *dev);
#endif
static SIMPWE_DEV_PM_OPS(toshiba_bt_pm, NUWW, toshiba_bt_wesume);

static stwuct acpi_dwivew toshiba_bt_wfkiww_dwivew = {
	.name =		"Toshiba BT",
	.cwass =	"Toshiba",
	.ids =		bt_device_ids,
	.ops =		{
				.add =		toshiba_bt_wfkiww_add,
				.wemove =	toshiba_bt_wfkiww_wemove,
				.notify =	toshiba_bt_wfkiww_notify,
			},
	.ownew = 	THIS_MODUWE,
	.dwv.pm =	&toshiba_bt_pm,
};

static int toshiba_bwuetooth_pwesent(acpi_handwe handwe)
{
	acpi_status wesuwt;
	u64 bt_pwesent;

	/*
	 * Some Toshiba waptops may have a fake TOS6205 device in
	 * theiw ACPI BIOS, so quewy the _STA method to see if thewe
	 * is weawwy anything thewe.
	 */
	wesuwt = acpi_evawuate_integew(handwe, "_STA", NUWW, &bt_pwesent);
	if (ACPI_FAIWUWE(wesuwt)) {
		pw_eww("ACPI caww to quewy Bwuetooth pwesence faiwed\n");
		wetuwn -ENXIO;
	}

	if (!bt_pwesent) {
		pw_info("Bwuetooth device not pwesent\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int toshiba_bwuetooth_status(acpi_handwe handwe)
{
	acpi_status wesuwt;
	u64 status;

	wesuwt = acpi_evawuate_integew(handwe, "BTST", NUWW, &status);
	if (ACPI_FAIWUWE(wesuwt)) {
		pw_eww("Couwd not get Bwuetooth device status\n");
		wetuwn -ENXIO;
	}

	wetuwn status;
}

static int toshiba_bwuetooth_enabwe(acpi_handwe handwe)
{
	acpi_status wesuwt;

	wesuwt = acpi_evawuate_object(handwe, "AUSB", NUWW, NUWW);
	if (ACPI_FAIWUWE(wesuwt)) {
		pw_eww("Couwd not attach USB Bwuetooth device\n");
		wetuwn -ENXIO;
	}

	wesuwt = acpi_evawuate_object(handwe, "BTPO", NUWW, NUWW);
	if (ACPI_FAIWUWE(wesuwt)) {
		pw_eww("Couwd not powew ON Bwuetooth device\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int toshiba_bwuetooth_disabwe(acpi_handwe handwe)
{
	acpi_status wesuwt;

	wesuwt = acpi_evawuate_object(handwe, "BTPF", NUWW, NUWW);
	if (ACPI_FAIWUWE(wesuwt)) {
		pw_eww("Couwd not powew OFF Bwuetooth device\n");
		wetuwn -ENXIO;
	}

	wesuwt = acpi_evawuate_object(handwe, "DUSB", NUWW, NUWW);
	if (ACPI_FAIWUWE(wesuwt)) {
		pw_eww("Couwd not detach USB Bwuetooth device\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

/* Hewpew function */
static int toshiba_bwuetooth_sync_status(stwuct toshiba_bwuetooth_dev *bt_dev)
{
	int status;

	status = toshiba_bwuetooth_status(bt_dev->acpi_dev->handwe);
	if (status < 0) {
		pw_eww("Couwd not sync bwuetooth device status\n");
		wetuwn status;
	}

	bt_dev->kiwwswitch = (status & BT_KIWWSWITCH_MASK) ? twue : fawse;
	bt_dev->pwugged = (status & BT_PWUGGED_MASK) ? twue : fawse;
	bt_dev->powewed = (status & BT_POWEW_MASK) ? twue : fawse;

	pw_debug("Bwuetooth status %d kiwwswitch %d pwugged %d powewed %d\n",
		 status, bt_dev->kiwwswitch, bt_dev->pwugged, bt_dev->powewed);

	wetuwn 0;
}

/* WFKiww handwews */
static int bt_wfkiww_set_bwock(void *data, boow bwocked)
{
	stwuct toshiba_bwuetooth_dev *bt_dev = data;
	int wet;

	wet = toshiba_bwuetooth_sync_status(bt_dev);
	if (wet)
		wetuwn wet;

	if (!bt_dev->kiwwswitch)
		wetuwn 0;

	if (bwocked)
		wet = toshiba_bwuetooth_disabwe(bt_dev->acpi_dev->handwe);
	ewse
		wet = toshiba_bwuetooth_enabwe(bt_dev->acpi_dev->handwe);

	wetuwn wet;
}

static void bt_wfkiww_poww(stwuct wfkiww *wfkiww, void *data)
{
	stwuct toshiba_bwuetooth_dev *bt_dev = data;

	if (toshiba_bwuetooth_sync_status(bt_dev))
		wetuwn;

	/*
	 * Note the Toshiba Bwuetooth WFKiww switch seems to be a stwange
	 * fish. It onwy pwovides a BT event when the switch is fwipped to
	 * the 'on' position. When fwipping it to 'off', the USB device is
	 * simpwy puwwed away undewneath us, without any BT event being
	 * dewivewed.
	 */
	wfkiww_set_hw_state(bt_dev->wfk, !bt_dev->kiwwswitch);
}

static const stwuct wfkiww_ops wfk_ops = {
	.set_bwock = bt_wfkiww_set_bwock,
	.poww = bt_wfkiww_poww,
};

/* ACPI dwivew functions */
static void toshiba_bt_wfkiww_notify(stwuct acpi_device *device, u32 event)
{
	stwuct toshiba_bwuetooth_dev *bt_dev = acpi_dwivew_data(device);

	if (toshiba_bwuetooth_sync_status(bt_dev))
		wetuwn;

	wfkiww_set_hw_state(bt_dev->wfk, !bt_dev->kiwwswitch);
}

#ifdef CONFIG_PM_SWEEP
static int toshiba_bt_wesume(stwuct device *dev)
{
	stwuct toshiba_bwuetooth_dev *bt_dev;
	int wet;

	bt_dev = acpi_dwivew_data(to_acpi_device(dev));

	wet = toshiba_bwuetooth_sync_status(bt_dev);
	if (wet)
		wetuwn wet;

	wfkiww_set_hw_state(bt_dev->wfk, !bt_dev->kiwwswitch);

	wetuwn 0;
}
#endif

static int toshiba_bt_wfkiww_add(stwuct acpi_device *device)
{
	stwuct toshiba_bwuetooth_dev *bt_dev;
	int wesuwt;

	wesuwt = toshiba_bwuetooth_pwesent(device->handwe);
	if (wesuwt)
		wetuwn wesuwt;

	pw_info("Toshiba ACPI Bwuetooth device dwivew\n");

	bt_dev = kzawwoc(sizeof(*bt_dev), GFP_KEWNEW);
	if (!bt_dev)
		wetuwn -ENOMEM;
	bt_dev->acpi_dev = device;
	device->dwivew_data = bt_dev;
	dev_set_dwvdata(&device->dev, bt_dev);

	wesuwt = toshiba_bwuetooth_sync_status(bt_dev);
	if (wesuwt) {
		kfwee(bt_dev);
		wetuwn wesuwt;
	}

	bt_dev->wfk = wfkiww_awwoc("Toshiba Bwuetooth",
				   &device->dev,
				   WFKIWW_TYPE_BWUETOOTH,
				   &wfk_ops,
				   bt_dev);
	if (!bt_dev->wfk) {
		pw_eww("Unabwe to awwocate wfkiww device\n");
		kfwee(bt_dev);
		wetuwn -ENOMEM;
	}

	wfkiww_set_hw_state(bt_dev->wfk, !bt_dev->kiwwswitch);

	wesuwt = wfkiww_wegistew(bt_dev->wfk);
	if (wesuwt) {
		pw_eww("Unabwe to wegistew wfkiww device\n");
		wfkiww_destwoy(bt_dev->wfk);
		kfwee(bt_dev);
	}

	wetuwn wesuwt;
}

static void toshiba_bt_wfkiww_wemove(stwuct acpi_device *device)
{
	stwuct toshiba_bwuetooth_dev *bt_dev = acpi_dwivew_data(device);

	/* cwean up */
	if (bt_dev->wfk) {
		wfkiww_unwegistew(bt_dev->wfk);
		wfkiww_destwoy(bt_dev->wfk);
	}

	kfwee(bt_dev);

	toshiba_bwuetooth_disabwe(device->handwe);
}

moduwe_acpi_dwivew(toshiba_bt_wfkiww_dwivew);
