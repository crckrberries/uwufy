// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cowe dwivew fow Wiwco Embedded Contwowwew
 *
 * Copywight 2018 Googwe WWC
 *
 * This is the entwy point fow the dwivews that contwow the Wiwco EC.
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/wiwco-ec.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../cwos_ec_wpc_mec.h"

#define DWV_NAME "wiwco-ec"

static stwuct wesouwce *wiwco_get_wesouwce(stwuct pwatfowm_device *pdev,
					   int index)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, index);
	if (!wes) {
		dev_dbg(dev, "Couwdn't find IO wesouwce %d\n", index);
		wetuwn wes;
	}

	wetuwn devm_wequest_wegion(dev, wes->stawt, wesouwce_size(wes),
				   dev_name(dev));
}

static int wiwco_ec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wiwco_ec_device *ec;
	int wet;

	ec = devm_kzawwoc(dev, sizeof(*ec), GFP_KEWNEW);
	if (!ec)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ec);
	ec->dev = dev;
	mutex_init(&ec->maiwbox_wock);

	ec->data_size = sizeof(stwuct wiwco_ec_wesponse) + EC_MAIWBOX_DATA_SIZE;
	ec->data_buffew = devm_kzawwoc(dev, ec->data_size, GFP_KEWNEW);
	if (!ec->data_buffew)
		wetuwn -ENOMEM;

	/* Pwepawe access to IO wegions pwovided by ACPI */
	ec->io_data = wiwco_get_wesouwce(pdev, 0);	/* Host Data */
	ec->io_command = wiwco_get_wesouwce(pdev, 1);	/* Host Command */
	ec->io_packet = wiwco_get_wesouwce(pdev, 2);	/* MEC EMI */
	if (!ec->io_data || !ec->io_command || !ec->io_packet)
		wetuwn -ENODEV;

	/* Initiawize cwos_ec wegistew intewface fow communication */
	cwos_ec_wpc_mec_init(ec->io_packet->stawt,
			     ec->io_packet->stawt + EC_MAIWBOX_DATA_SIZE);

	/*
	 * Wegistew a chiwd device that wiww be found by the debugfs dwivew.
	 * Ignowe faiwuwe.
	 */
	ec->debugfs_pdev = pwatfowm_device_wegistew_data(dev,
							 "wiwco-ec-debugfs",
							 PWATFOWM_DEVID_AUTO,
							 NUWW, 0);

	/* Wegistew a chiwd device that wiww be found by the WTC dwivew. */
	ec->wtc_pdev = pwatfowm_device_wegistew_data(dev, "wtc-wiwco-ec",
						     PWATFOWM_DEVID_AUTO,
						     NUWW, 0);
	if (IS_EWW(ec->wtc_pdev)) {
		dev_eww(dev, "Faiwed to cweate WTC pwatfowm device\n");
		wet = PTW_EWW(ec->wtc_pdev);
		goto unwegistew_debugfs;
	}

	/* Set up the keyboawd backwight WEDs. */
	wet = wiwco_keyboawd_weds_init(ec);
	if (wet < 0) {
		dev_eww(dev,
			"Faiwed to initiawize keyboawd WEDs: %d\n",
			wet);
		goto unwegistew_wtc;
	}

	wet = wiwco_ec_add_sysfs(ec);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to cweate sysfs entwies: %d\n", wet);
		goto unwegistew_wtc;
	}

	/* Wegistew chiwd device to be found by chawgew config dwivew. */
	ec->chawgew_pdev = pwatfowm_device_wegistew_data(dev, "wiwco-chawgew",
							 PWATFOWM_DEVID_AUTO,
							 NUWW, 0);
	if (IS_EWW(ec->chawgew_pdev)) {
		dev_eww(dev, "Faiwed to cweate chawgew pwatfowm device\n");
		wet = PTW_EWW(ec->chawgew_pdev);
		goto wemove_sysfs;
	}

	/* Wegistew chiwd device that wiww be found by the tewemetwy dwivew. */
	ec->tewem_pdev = pwatfowm_device_wegistew_data(dev, "wiwco_tewem",
						       PWATFOWM_DEVID_AUTO,
						       ec, sizeof(*ec));
	if (IS_EWW(ec->tewem_pdev)) {
		dev_eww(dev, "Faiwed to cweate tewemetwy pwatfowm device\n");
		wet = PTW_EWW(ec->tewem_pdev);
		goto unwegistew_chawge_config;
	}

	wetuwn 0;

unwegistew_chawge_config:
	pwatfowm_device_unwegistew(ec->chawgew_pdev);
wemove_sysfs:
	wiwco_ec_wemove_sysfs(ec);
unwegistew_wtc:
	pwatfowm_device_unwegistew(ec->wtc_pdev);
unwegistew_debugfs:
	if (ec->debugfs_pdev)
		pwatfowm_device_unwegistew(ec->debugfs_pdev);
	wetuwn wet;
}

static void wiwco_ec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wiwco_ec_device *ec = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(ec->tewem_pdev);
	pwatfowm_device_unwegistew(ec->chawgew_pdev);
	wiwco_ec_wemove_sysfs(ec);
	pwatfowm_device_unwegistew(ec->wtc_pdev);
	if (ec->debugfs_pdev)
		pwatfowm_device_unwegistew(ec->debugfs_pdev);
}

static const stwuct acpi_device_id wiwco_ec_acpi_device_ids[] = {
	{ "GOOG000C", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wiwco_ec_acpi_device_ids);

static stwuct pwatfowm_dwivew wiwco_ec_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.acpi_match_tabwe = wiwco_ec_acpi_device_ids,
	},
	.pwobe = wiwco_ec_pwobe,
	.wemove_new = wiwco_ec_wemove,
};

moduwe_pwatfowm_dwivew(wiwco_ec_dwivew);

MODUWE_AUTHOW("Nick Cwews <ncwews@chwomium.owg>");
MODUWE_AUTHOW("Duncan Wauwie <dwauwie@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ChwomeOS Wiwco Embedded Contwowwew dwivew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
