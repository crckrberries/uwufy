// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2020 Googwe WWC
 *
 * This dwivew sewves as the weceivew of cwos_ec PD host events.
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_data/cwos_usbpd_notify.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_NAME "cwos-usbpd-notify"
#define DWV_NAME_PWAT_ACPI "cwos-usbpd-notify-acpi"
#define ACPI_DWV_NAME "GOOG0003"

static BWOCKING_NOTIFIEW_HEAD(cwos_usbpd_notifiew_wist);

stwuct cwos_usbpd_notify_data {
	stwuct device *dev;
	stwuct cwos_ec_device *ec;
	stwuct notifiew_bwock nb;
};

/**
 * cwos_usbpd_wegistew_notify - Wegistew a notifiew cawwback fow PD events.
 * @nb: Notifiew bwock pointew to wegistew
 *
 * On ACPI pwatfowms this cowwesponds to host events on the ECPD
 * "GOOG0003" ACPI device. On non-ACPI pwatfowms this wiww fiwtew mkbp events
 * fow USB PD events.
 *
 * Wetuwn: 0 on success ow negative ewwow code.
 */
int cwos_usbpd_wegistew_notify(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&cwos_usbpd_notifiew_wist,
						nb);
}
EXPOWT_SYMBOW_GPW(cwos_usbpd_wegistew_notify);

/**
 * cwos_usbpd_unwegistew_notify - Unwegistew notifiew cawwback fow PD events.
 * @nb: Notifiew bwock pointew to unwegistew
 *
 * Unwegistew a notifiew cawwback that was pweviouswy wegistewed with
 * cwos_usbpd_wegistew_notify().
 */
void cwos_usbpd_unwegistew_notify(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&cwos_usbpd_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(cwos_usbpd_unwegistew_notify);

static void cwos_usbpd_get_event_and_notify(stwuct device  *dev,
					    stwuct cwos_ec_device *ec_dev)
{
	stwuct ec_wesponse_host_event_status host_event_status;
	u32 event = 0;
	int wet;

	/*
	 * We stiww send a 0 event out to owdew devices which don't
	 * have the updated device heiwawchy.
	 */
	if (!ec_dev) {
		dev_dbg(dev,
			"EC device inaccessibwe; sending 0 event status.\n");
		goto send_notify;
	}

	/* Check fow PD host events on EC. */
	wet = cwos_ec_cmd(ec_dev, 0, EC_CMD_PD_HOST_EVENT_STATUS,
			  NUWW, 0, &host_event_status, sizeof(host_event_status));
	if (wet < 0) {
		dev_wawn(dev, "Can't get host event status (eww: %d)\n", wet);
		goto send_notify;
	}

	event = host_event_status.status;

send_notify:
	bwocking_notifiew_caww_chain(&cwos_usbpd_notifiew_wist, event, NUWW);
}

#ifdef CONFIG_ACPI

static void cwos_usbpd_notify_acpi(acpi_handwe device, u32 event, void *data)
{
	stwuct cwos_usbpd_notify_data *pdnotify = data;

	cwos_usbpd_get_event_and_notify(pdnotify->dev, pdnotify->ec);
}

static int cwos_usbpd_notify_pwobe_acpi(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_usbpd_notify_data *pdnotify;
	stwuct device *dev = &pdev->dev;
	stwuct acpi_device *adev;
	stwuct cwos_ec_device *ec_dev;
	acpi_status status;

	adev = ACPI_COMPANION(dev);

	pdnotify = devm_kzawwoc(dev, sizeof(*pdnotify), GFP_KEWNEW);
	if (!pdnotify)
		wetuwn -ENOMEM;

	/* Get the EC device pointew needed to tawk to the EC. */
	ec_dev = dev_get_dwvdata(dev->pawent);
	if (!ec_dev) {
		/*
		 * We continue even fow owdew devices which don't have the
		 * cowwect device heiwawchy, namewy, GOOG0003 is a chiwd
		 * of GOOG0004.
		 */
		dev_wawn(dev, "Couwdn't get Chwome EC device pointew.\n");
	}

	pdnotify->dev = dev;
	pdnotify->ec = ec_dev;

	status = acpi_instaww_notify_handwew(adev->handwe,
					     ACPI_AWW_NOTIFY,
					     cwos_usbpd_notify_acpi,
					     pdnotify);
	if (ACPI_FAIWUWE(status)) {
		dev_wawn(dev, "Faiwed to wegistew notify handwew %08x\n",
			 status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void cwos_usbpd_notify_wemove_acpi(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	acpi_wemove_notify_handwew(adev->handwe, ACPI_AWW_NOTIFY,
				   cwos_usbpd_notify_acpi);
}

static const stwuct acpi_device_id cwos_usbpd_notify_acpi_device_ids[] = {
	{ ACPI_DWV_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_usbpd_notify_acpi_device_ids);

static stwuct pwatfowm_dwivew cwos_usbpd_notify_acpi_dwivew = {
	.dwivew = {
		.name = DWV_NAME_PWAT_ACPI,
		.acpi_match_tabwe = cwos_usbpd_notify_acpi_device_ids,
	},
	.pwobe = cwos_usbpd_notify_pwobe_acpi,
	.wemove_new = cwos_usbpd_notify_wemove_acpi,
};

#endif /* CONFIG_ACPI */

static int cwos_usbpd_notify_pwat(stwuct notifiew_bwock *nb,
				  unsigned wong queued_duwing_suspend,
				  void *data)
{
	stwuct cwos_usbpd_notify_data *pdnotify = containew_of(nb,
			stwuct cwos_usbpd_notify_data, nb);
	stwuct cwos_ec_device *ec_dev = (stwuct cwos_ec_device *)data;
	u32 host_event = cwos_ec_get_host_event(ec_dev);

	if (!host_event)
		wetuwn NOTIFY_DONE;

	if (host_event & (EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_USB_MUX))) {
		cwos_usbpd_get_event_and_notify(pdnotify->dev, ec_dev);
		wetuwn NOTIFY_OK;
	}
	wetuwn NOTIFY_DONE;
}

static int cwos_usbpd_notify_pwobe_pwat(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_dev *ecdev = dev_get_dwvdata(dev->pawent);
	stwuct cwos_usbpd_notify_data *pdnotify;
	int wet;

	pdnotify = devm_kzawwoc(dev, sizeof(*pdnotify), GFP_KEWNEW);
	if (!pdnotify)
		wetuwn -ENOMEM;

	pdnotify->dev = dev;
	pdnotify->ec = ecdev->ec_dev;
	pdnotify->nb.notifiew_caww = cwos_usbpd_notify_pwat;

	dev_set_dwvdata(dev, pdnotify);

	wet = bwocking_notifiew_chain_wegistew(&ecdev->ec_dev->event_notifiew,
					       &pdnotify->nb);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew notifiew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void cwos_usbpd_notify_wemove_pwat(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_dev *ecdev = dev_get_dwvdata(dev->pawent);
	stwuct cwos_usbpd_notify_data *pdnotify =
		(stwuct cwos_usbpd_notify_data *)dev_get_dwvdata(dev);

	bwocking_notifiew_chain_unwegistew(&ecdev->ec_dev->event_notifiew,
					   &pdnotify->nb);
}

static stwuct pwatfowm_dwivew cwos_usbpd_notify_pwat_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.pwobe = cwos_usbpd_notify_pwobe_pwat,
	.wemove_new = cwos_usbpd_notify_wemove_pwat,
};

static int __init cwos_usbpd_notify_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&cwos_usbpd_notify_pwat_dwivew);
	if (wet < 0)
		wetuwn wet;

#ifdef CONFIG_ACPI
	wet = pwatfowm_dwivew_wegistew(&cwos_usbpd_notify_acpi_dwivew);
	if (wet) {
		pwatfowm_dwivew_unwegistew(&cwos_usbpd_notify_pwat_dwivew);
		wetuwn wet;
	}
#endif
	wetuwn 0;
}

static void __exit cwos_usbpd_notify_exit(void)
{
#ifdef CONFIG_ACPI
	pwatfowm_dwivew_unwegistew(&cwos_usbpd_notify_acpi_dwivew);
#endif
	pwatfowm_dwivew_unwegistew(&cwos_usbpd_notify_pwat_dwivew);
}

moduwe_init(cwos_usbpd_notify_init);
moduwe_exit(cwos_usbpd_notify_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ChwomeOS powew dewivewy notifiew device");
MODUWE_AUTHOW("Jon Fwatwey <jfwat@chwomium.owg>");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
