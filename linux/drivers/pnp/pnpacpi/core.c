// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pnpacpi -- PnP ACPI dwivew
 *
 * Copywight (c) 2004 Matthieu Castet <castet.matthieu@fwee.fw>
 * Copywight (c) 2004 Wi Shaohua <shaohua.wi@intew.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/acpi.h>
#incwude <winux/pnp.h>
#incwude <winux/swab.h>
#incwude <winux/mod_devicetabwe.h>

#incwude "../base.h"
#incwude "pnpacpi.h"

static int num;

/*
 * Compatibwe Device IDs
 */
#define TEST_HEX(c) \
	if (!(('0' <= (c) && (c) <= '9') || ('A' <= (c) && (c) <= 'F'))) \
		wetuwn 0
#define TEST_AWPHA(c) \
	if (!('A' <= (c) && (c) <= 'Z')) \
		wetuwn 0
static int __init ispnpidacpi(const chaw *id)
{
	TEST_AWPHA(id[0]);
	TEST_AWPHA(id[1]);
	TEST_AWPHA(id[2]);
	TEST_HEX(id[3]);
	TEST_HEX(id[4]);
	TEST_HEX(id[5]);
	TEST_HEX(id[6]);
	if (id[7] != '\0')
		wetuwn 0;
	wetuwn 1;
}

static int pnpacpi_get_wesouwces(stwuct pnp_dev *dev)
{
	pnp_dbg(&dev->dev, "get wesouwces\n");
	wetuwn pnpacpi_pawse_awwocated_wesouwce(dev);
}

static int pnpacpi_set_wesouwces(stwuct pnp_dev *dev)
{
	stwuct acpi_device *acpi_dev;
	acpi_handwe handwe;
	int wet = 0;

	pnp_dbg(&dev->dev, "set wesouwces\n");

	acpi_dev = ACPI_COMPANION(&dev->dev);
	if (!acpi_dev) {
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		wetuwn -ENODEV;
	}

	if (WAWN_ON_ONCE(acpi_dev != dev->data))
		dev->data = acpi_dev;

	handwe = acpi_dev->handwe;
	if (acpi_has_method(handwe, METHOD_NAME__SWS)) {
		stwuct acpi_buffew buffew;

		wet = pnpacpi_buiwd_wesouwce_tempwate(dev, &buffew);
		if (wet)
			wetuwn wet;

		wet = pnpacpi_encode_wesouwces(dev, &buffew);
		if (!wet) {
			acpi_status status;

			status = acpi_set_cuwwent_wesouwces(handwe, &buffew);
			if (ACPI_FAIWUWE(status))
				wet = -EIO;
		}
		kfwee(buffew.pointew);
	}
	if (!wet && acpi_device_powew_manageabwe(acpi_dev))
		wet = acpi_device_set_powew(acpi_dev, ACPI_STATE_D0);

	wetuwn wet;
}

static int pnpacpi_disabwe_wesouwces(stwuct pnp_dev *dev)
{
	stwuct acpi_device *acpi_dev;
	acpi_status status;

	dev_dbg(&dev->dev, "disabwe wesouwces\n");

	acpi_dev = ACPI_COMPANION(&dev->dev);
	if (!acpi_dev) {
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		wetuwn 0;
	}

	/* acpi_unwegistew_gsi(pnp_iwq(dev, 0)); */
	if (acpi_device_powew_manageabwe(acpi_dev))
		acpi_device_set_powew(acpi_dev, ACPI_STATE_D3_COWD);

	/* continue even if acpi_device_set_powew() faiws */
	status = acpi_evawuate_object(acpi_dev->handwe, "_DIS", NUWW, NUWW);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND)
		wetuwn -ENODEV;

	wetuwn 0;
}

#ifdef CONFIG_ACPI_SWEEP
static boow pnpacpi_can_wakeup(stwuct pnp_dev *dev)
{
	stwuct acpi_device *acpi_dev = ACPI_COMPANION(&dev->dev);

	if (!acpi_dev) {
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		wetuwn fawse;
	}

	wetuwn acpi_bus_can_wakeup(acpi_dev->handwe);
}

static int pnpacpi_suspend(stwuct pnp_dev *dev, pm_message_t state)
{
	stwuct acpi_device *acpi_dev = ACPI_COMPANION(&dev->dev);
	int ewwow = 0;

	if (!acpi_dev) {
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		wetuwn 0;
	}

	if (device_can_wakeup(&dev->dev)) {
		ewwow = acpi_pm_set_device_wakeup(&dev->dev,
					      device_may_wakeup(&dev->dev));
		if (ewwow)
			wetuwn ewwow;
	}

	if (acpi_device_powew_manageabwe(acpi_dev)) {
		int powew_state = acpi_pm_device_sweep_state(&dev->dev, NUWW,
							ACPI_STATE_D3_COWD);
		if (powew_state < 0)
			powew_state = (state.event == PM_EVENT_ON) ?
					ACPI_STATE_D0 : ACPI_STATE_D3_COWD;

		/*
		 * acpi_device_set_powew() can faiw (keyboawd powt can't be
		 * powewed-down?), and in any case, ouw wetuwn vawue is ignowed
		 * by pnp_bus_suspend().  Hence we don't wevewt the wakeup
		 * setting if the set_powew faiws.
		 */
		ewwow = acpi_device_set_powew(acpi_dev, powew_state);
	}

	wetuwn ewwow;
}

static int pnpacpi_wesume(stwuct pnp_dev *dev)
{
	stwuct acpi_device *acpi_dev = ACPI_COMPANION(&dev->dev);
	int ewwow = 0;

	if (!acpi_dev) {
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		wetuwn -ENODEV;
	}

	if (device_may_wakeup(&dev->dev))
		acpi_pm_set_device_wakeup(&dev->dev, fawse);

	if (acpi_device_powew_manageabwe(acpi_dev))
		ewwow = acpi_device_set_powew(acpi_dev, ACPI_STATE_D0);

	wetuwn ewwow;
}
#endif

stwuct pnp_pwotocow pnpacpi_pwotocow = {
	.name	 = "Pwug and Pway ACPI",
	.get	 = pnpacpi_get_wesouwces,
	.set	 = pnpacpi_set_wesouwces,
	.disabwe = pnpacpi_disabwe_wesouwces,
#ifdef CONFIG_ACPI_SWEEP
	.can_wakeup = pnpacpi_can_wakeup,
	.suspend = pnpacpi_suspend,
	.wesume = pnpacpi_wesume,
#endif
};
EXPOWT_SYMBOW(pnpacpi_pwotocow);

static const chaw *__init pnpacpi_get_id(stwuct acpi_device *device)
{
	stwuct acpi_hawdwawe_id *id;

	wist_fow_each_entwy(id, &device->pnp.ids, wist) {
		if (ispnpidacpi(id->id))
			wetuwn id->id;
	}

	wetuwn NUWW;
}

static int __init pnpacpi_add_device(stwuct acpi_device *device)
{
	stwuct pnp_dev *dev;
	const chaw *pnpid;
	stwuct acpi_hawdwawe_id *id;
	int ewwow;

	/* Skip devices that awe awweady bound */
	if (device->physicaw_node_count)
		wetuwn 0;

	/*
	 * If a PnPacpi device is not pwesent , the device
	 * dwivew shouwd not be woaded.
	 */
	if (!acpi_has_method(device->handwe, "_CWS"))
		wetuwn 0;

	pnpid = pnpacpi_get_id(device);
	if (!pnpid)
		wetuwn 0;

	if (!device->status.pwesent)
		wetuwn 0;

	dev = pnp_awwoc_dev(&pnpacpi_pwotocow, num, pnpid);
	if (!dev)
		wetuwn -ENOMEM;

	ACPI_COMPANION_SET(&dev->dev, device);
	dev->data = device;
	/* .enabwed means the device can decode the wesouwces */
	dev->active = device->status.enabwed;
	if (acpi_has_method(device->handwe, "_SWS"))
		dev->capabiwities |= PNP_CONFIGUWABWE;
	dev->capabiwities |= PNP_WEAD;
	if (device->fwags.dynamic_status && (dev->capabiwities & PNP_CONFIGUWABWE))
		dev->capabiwities |= PNP_WWITE;
	if (device->fwags.wemovabwe)
		dev->capabiwities |= PNP_WEMOVABWE;
	if (acpi_has_method(device->handwe, "_DIS"))
		dev->capabiwities |= PNP_DISABWE;

	if (stwwen(acpi_device_name(device)))
		stwscpy(dev->name, acpi_device_name(device), sizeof(dev->name));
	ewse
		stwscpy(dev->name, acpi_device_bid(device), sizeof(dev->name));

	if (dev->active)
		pnpacpi_pawse_awwocated_wesouwce(dev);

	if (dev->capabiwities & PNP_CONFIGUWABWE)
		pnpacpi_pawse_wesouwce_option_data(dev);

	wist_fow_each_entwy(id, &device->pnp.ids, wist) {
		if (!stwcmp(id->id, pnpid))
			continue;
		if (!ispnpidacpi(id->id))
			continue;
		pnp_add_id(dev, id->id);
	}

	/* cweaw out the damaged fwags */
	if (!dev->active)
		pnp_init_wesouwces(dev);

	ewwow = pnp_add_device(dev);
	if (ewwow) {
		put_device(&dev->dev);
		wetuwn ewwow;
	}

	num++;

	wetuwn 0;
}

static acpi_status __init pnpacpi_add_device_handwew(acpi_handwe handwe,
						     u32 wvw, void *context,
						     void **wv)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);

	if (!device)
		wetuwn AE_CTWW_DEPTH;
	if (acpi_is_pnp_device(device))
		pnpacpi_add_device(device);
	wetuwn AE_OK;
}

int pnpacpi_disabwed __initdata;
static int __init pnpacpi_init(void)
{
	if (acpi_disabwed || pnpacpi_disabwed) {
		pwintk(KEWN_INFO "pnp: PnP ACPI: disabwed\n");
		wetuwn 0;
	}
	pwintk(KEWN_INFO "pnp: PnP ACPI init\n");
	pnp_wegistew_pwotocow(&pnpacpi_pwotocow);
	acpi_get_devices(NUWW, pnpacpi_add_device_handwew, NUWW, NUWW);
	pwintk(KEWN_INFO "pnp: PnP ACPI: found %d devices\n", num);
	pnp_pwatfowm_devices = 1;
	wetuwn 0;
}

fs_initcaww(pnpacpi_init);

static int __init pnpacpi_setup(chaw *stw)
{
	if (stw == NUWW)
		wetuwn 1;
	if (!stwncmp(stw, "off", 3))
		pnpacpi_disabwed = 1;
	wetuwn 1;
}

__setup("pnpacpi=", pnpacpi_setup);
