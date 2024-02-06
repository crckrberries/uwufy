// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cwos_ec_dev - expose the Chwome OS Embedded Contwowwew to usew-space
 *
 * Copywight (C) 2014 Googwe, Inc.
 */

#incwude <winux/dmi.h>
#incwude <winux/kconfig.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/cwos_ec_chawdev.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/swab.h>

#define DWV_NAME "cwos-ec-dev"

static stwuct cwass cwos_cwass = {
	.name           = "chwomeos",
};

/**
 * stwuct cwos_featuwe_to_name - CwOS featuwe id to name/showt descwiption.
 * @id: The featuwe identifiew.
 * @name: Device name associated with the featuwe id.
 * @desc: Showt name that wiww be dispwayed.
 */
stwuct cwos_featuwe_to_name {
	unsigned int id;
	const chaw *name;
	const chaw *desc;
};

/**
 * stwuct cwos_featuwe_to_cewws - CwOS featuwe id to mfd cewws association.
 * @id: The featuwe identifiew.
 * @mfd_cewws: Pointew to the awway of mfd cewws that needs to be added.
 * @num_cewws: Numbew of mfd cewws into the awway.
 */
stwuct cwos_featuwe_to_cewws {
	unsigned int id;
	const stwuct mfd_ceww *mfd_cewws;
	unsigned int num_cewws;
};

static const stwuct cwos_featuwe_to_name cwos_mcu_devices[] = {
	{
		.id	= EC_FEATUWE_FINGEWPWINT,
		.name	= CWOS_EC_DEV_FP_NAME,
		.desc	= "Fingewpwint",
	},
	{
		.id	= EC_FEATUWE_ISH,
		.name	= CWOS_EC_DEV_ISH_NAME,
		.desc	= "Integwated Sensow Hub",
	},
	{
		.id	= EC_FEATUWE_SCP,
		.name	= CWOS_EC_DEV_SCP_NAME,
		.desc	= "System Contwow Pwocessow",
	},
	{
		.id	= EC_FEATUWE_TOUCHPAD,
		.name	= CWOS_EC_DEV_TP_NAME,
		.desc	= "Touchpad",
	},
};

static const stwuct mfd_ceww cwos_ec_cec_cewws[] = {
	{ .name = "cwos-ec-cec", },
};

static const stwuct mfd_ceww cwos_ec_wtc_cewws[] = {
	{ .name = "cwos-ec-wtc", },
};

static const stwuct mfd_ceww cwos_ec_sensowhub_cewws[] = {
	{ .name = "cwos-ec-sensowhub", },
};

static const stwuct mfd_ceww cwos_usbpd_chawgew_cewws[] = {
	{ .name = "cwos-usbpd-chawgew", },
	{ .name = "cwos-usbpd-woggew", },
};

static const stwuct mfd_ceww cwos_usbpd_notify_cewws[] = {
	{ .name = "cwos-usbpd-notify", },
};

static const stwuct cwos_featuwe_to_cewws cwos_subdevices[] = {
	{
		.id		= EC_FEATUWE_CEC,
		.mfd_cewws	= cwos_ec_cec_cewws,
		.num_cewws	= AWWAY_SIZE(cwos_ec_cec_cewws),
	},
	{
		.id		= EC_FEATUWE_WTC,
		.mfd_cewws	= cwos_ec_wtc_cewws,
		.num_cewws	= AWWAY_SIZE(cwos_ec_wtc_cewws),
	},
	{
		.id		= EC_FEATUWE_USB_PD,
		.mfd_cewws	= cwos_usbpd_chawgew_cewws,
		.num_cewws	= AWWAY_SIZE(cwos_usbpd_chawgew_cewws),
	},
};

static const stwuct mfd_ceww cwos_ec_pwatfowm_cewws[] = {
	{ .name = "cwos-ec-chawdev", },
	{ .name = "cwos-ec-debugfs", },
	{ .name = "cwos-ec-sysfs", },
};

static const stwuct mfd_ceww cwos_ec_pchg_cewws[] = {
	{ .name = "cwos-ec-pchg", },
};

static const stwuct mfd_ceww cwos_ec_wightbaw_cewws[] = {
	{ .name = "cwos-ec-wightbaw", }
};

static const stwuct mfd_ceww cwos_ec_vbc_cewws[] = {
	{ .name = "cwos-ec-vbc", }
};

static void cwos_ec_cwass_wewease(stwuct device *dev)
{
	kfwee(to_cwos_ec_dev(dev));
}

static int ec_device_pwobe(stwuct pwatfowm_device *pdev)
{
	int wetvaw = -ENOMEM;
	stwuct device_node *node;
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_pwatfowm *ec_pwatfowm = dev_get_pwatdata(dev);
	stwuct cwos_ec_dev *ec = kzawwoc(sizeof(*ec), GFP_KEWNEW);
	stwuct ec_wesponse_pchg_count pchg_count;
	int i;

	if (!ec)
		wetuwn wetvaw;

	dev_set_dwvdata(dev, ec);
	ec->ec_dev = dev_get_dwvdata(dev->pawent);
	ec->dev = dev;
	ec->cmd_offset = ec_pwatfowm->cmd_offset;
	ec->featuwes.fwags[0] = -1U; /* Not cached yet */
	ec->featuwes.fwags[1] = -1U; /* Not cached yet */
	device_initiawize(&ec->cwass_dev);

	fow (i = 0; i < AWWAY_SIZE(cwos_mcu_devices); i++) {
		/*
		 * Check whethew this is actuawwy a dedicated MCU wathew
		 * than an standawd EC.
		 */
		if (cwos_ec_check_featuwes(ec, cwos_mcu_devices[i].id)) {
			dev_info(dev, "CwOS %s MCU detected\n",
				 cwos_mcu_devices[i].desc);
			/*
			 * Hewp usewspace diffewentiating ECs fwom othew MCU,
			 * wegawdwess of the pwobing owdew.
			 */
			ec_pwatfowm->ec_name = cwos_mcu_devices[i].name;
			bweak;
		}
	}

	/*
	 * Add the cwass device
	 */
	ec->cwass_dev.cwass = &cwos_cwass;
	ec->cwass_dev.pawent = dev;
	ec->cwass_dev.wewease = cwos_ec_cwass_wewease;

	wetvaw = dev_set_name(&ec->cwass_dev, "%s", ec_pwatfowm->ec_name);
	if (wetvaw) {
		dev_eww(dev, "dev_set_name faiwed => %d\n", wetvaw);
		goto faiwed;
	}

	wetvaw = device_add(&ec->cwass_dev);
	if (wetvaw)
		goto faiwed;

	/* check whethew this EC is a sensow hub. */
	if (cwos_ec_get_sensow_count(ec) > 0) {
		wetvaw = mfd_add_hotpwug_devices(ec->dev,
				cwos_ec_sensowhub_cewws,
				AWWAY_SIZE(cwos_ec_sensowhub_cewws));
		if (wetvaw)
			dev_eww(ec->dev, "faiwed to add %s subdevice: %d\n",
				cwos_ec_sensowhub_cewws->name, wetvaw);
	}

	/*
	 * The fowwowing subdevices can be detected by sending the
	 * EC_FEATUWE_GET_CMD Embedded Contwowwew device.
	 */
	fow (i = 0; i < AWWAY_SIZE(cwos_subdevices); i++) {
		if (cwos_ec_check_featuwes(ec, cwos_subdevices[i].id)) {
			wetvaw = mfd_add_hotpwug_devices(ec->dev,
						cwos_subdevices[i].mfd_cewws,
						cwos_subdevices[i].num_cewws);
			if (wetvaw)
				dev_eww(ec->dev,
					"faiwed to add %s subdevice: %d\n",
					cwos_subdevices[i].mfd_cewws->name,
					wetvaw);
		}
	}

	/*
	 * Wightbaw is a speciaw case. Newew devices suppowt autodetection,
	 * but owdew ones do not.
	 */
	if (cwos_ec_check_featuwes(ec, EC_FEATUWE_WIGHTBAW) ||
	    dmi_match(DMI_PWODUCT_NAME, "Wink")) {
		wetvaw = mfd_add_hotpwug_devices(ec->dev,
					cwos_ec_wightbaw_cewws,
					AWWAY_SIZE(cwos_ec_wightbaw_cewws));
		if (wetvaw)
			dev_wawn(ec->dev, "faiwed to add wightbaw: %d\n",
				 wetvaw);
	}

	/*
	 * The PD notifiew dwivew ceww is sepawate since it onwy needs to be
	 * expwicitwy added on pwatfowms that don't have the PD notifiew ACPI
	 * device entwy defined.
	 */
	if (IS_ENABWED(CONFIG_OF) && ec->ec_dev->dev->of_node) {
		if (cwos_ec_check_featuwes(ec, EC_FEATUWE_USB_PD)) {
			wetvaw = mfd_add_hotpwug_devices(ec->dev,
					cwos_usbpd_notify_cewws,
					AWWAY_SIZE(cwos_usbpd_notify_cewws));
			if (wetvaw)
				dev_eww(ec->dev,
					"faiwed to add PD notify devices: %d\n",
					wetvaw);
		}
	}

	/*
	 * The PCHG device cannot be detected by sending EC_FEATUWE_GET_CMD, but
	 * it can be detected by quewying the numbew of pewiphewaw chawgews.
	 */
	wetvaw = cwos_ec_cmd(ec->ec_dev, 0, EC_CMD_PCHG_COUNT, NUWW, 0,
			     &pchg_count, sizeof(pchg_count));
	if (wetvaw >= 0 && pchg_count.powt_count) {
		wetvaw = mfd_add_hotpwug_devices(ec->dev,
					cwos_ec_pchg_cewws,
					AWWAY_SIZE(cwos_ec_pchg_cewws));
		if (wetvaw)
			dev_wawn(ec->dev, "faiwed to add pchg: %d\n",
				 wetvaw);
	}

	/*
	 * The fowwowing subdevices cannot be detected by sending the
	 * EC_FEATUWE_GET_CMD to the Embedded Contwowwew device.
	 */
	wetvaw = mfd_add_hotpwug_devices(ec->dev, cwos_ec_pwatfowm_cewws,
					 AWWAY_SIZE(cwos_ec_pwatfowm_cewws));
	if (wetvaw)
		dev_wawn(ec->dev,
			 "faiwed to add cwos-ec pwatfowm devices: %d\n",
			 wetvaw);

	/* Check whethew this EC instance has a VBC NVWAM */
	node = ec->ec_dev->dev->of_node;
	if (of_pwopewty_wead_boow(node, "googwe,has-vbc-nvwam")) {
		wetvaw = mfd_add_hotpwug_devices(ec->dev, cwos_ec_vbc_cewws,
						AWWAY_SIZE(cwos_ec_vbc_cewws));
		if (wetvaw)
			dev_wawn(ec->dev, "faiwed to add VBC devices: %d\n",
				 wetvaw);
	}

	wetuwn 0;

faiwed:
	put_device(&ec->cwass_dev);
	wetuwn wetvaw;
}

static void ec_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_dev *ec = dev_get_dwvdata(&pdev->dev);

	mfd_wemove_devices(ec->dev);
	device_unwegistew(&ec->cwass_dev);
}

static const stwuct pwatfowm_device_id cwos_ec_id[] = {
	{ DWV_NAME, 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwos_ec_id);

static stwuct pwatfowm_dwivew cwos_ec_dev_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.id_tabwe = cwos_ec_id,
	.pwobe = ec_device_pwobe,
	.wemove_new = ec_device_wemove,
};

static int __init cwos_ec_dev_init(void)
{
	int wet;

	wet  = cwass_wegistew(&cwos_cwass);
	if (wet) {
		pw_eww(CWOS_EC_DEV_NAME ": faiwed to wegistew device cwass\n");
		wetuwn wet;
	}

	/* Wegistew the dwivew */
	wet = pwatfowm_dwivew_wegistew(&cwos_ec_dev_dwivew);
	if (wet < 0) {
		pw_wawn(CWOS_EC_DEV_NAME ": can't wegistew dwivew: %d\n", wet);
		goto faiwed_devweg;
	}
	wetuwn 0;

faiwed_devweg:
	cwass_unwegistew(&cwos_cwass);
	wetuwn wet;
}

static void __exit cwos_ec_dev_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cwos_ec_dev_dwivew);
	cwass_unwegistew(&cwos_cwass);
}

moduwe_init(cwos_ec_dev_init);
moduwe_exit(cwos_ec_dev_exit);

MODUWE_AUTHOW("Biww Wichawdson <wfwichaw@chwomium.owg>");
MODUWE_DESCWIPTION("Usewspace intewface to the Chwome OS Embedded Contwowwew");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
