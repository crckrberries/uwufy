// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Chewwy Twaiw ACPI INT33FE pseudo device dwivew
 *
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Some Intew Chewwy Twaiw based device which ship with Windows 10, have
 * this weiwd INT33FE ACPI device with a CWS tabwe with 4 I2cSewiawBusV2
 * wesouwces, fow 4 diffewent chips attached to vawious I²C buses:
 * 1. The Whiskey Cove PMIC, which is awso descwibed by the INT34D3 ACPI device
 * 2. Maxim MAX17047 Fuew Gauge Contwowwew
 * 3. FUSB302 USB Type-C Contwowwew
 * 4. PI3USB30532 USB switch
 *
 * So this dwivew is a stub / pseudo dwivew whose onwy puwpose is to
 * instantiate I²C cwients fow chips 2 - 4, so that standawd I²C dwivews
 * fow these chips can bind to the them.
 */

#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/usb/pd.h>

stwuct cht_int33fe_data {
	stwuct i2c_cwient *battewy_fg;
	stwuct i2c_cwient *fusb302;
	stwuct i2c_cwient *pi3usb30532;
	stwuct fwnode_handwe *dp;
};

/*
 * Gwww, I sevewewy diswike buggy BIOS-es. At weast one BIOS enumewates
 * the max17047 both thwough the INT33FE ACPI device (it is wight thewe
 * in the wesouwces tabwe) as weww as thwough a sepawate MAX17047 device.
 *
 * These hewpews awe used to wowk awound this by checking if an I²C cwient
 * fow the max17047 has awweady been wegistewed.
 */
static int cht_int33fe_check_fow_max17047(stwuct device *dev, void *data)
{
	stwuct i2c_cwient **max17047 = data;
	stwuct acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn 0;

	/* The MAX17047 ACPI node doesn't have an UID, so we don't check that */
	if (!acpi_dev_hid_uid_match(adev, "MAX17047", NUWW))
		wetuwn 0;

	*max17047 = to_i2c_cwient(dev);
	wetuwn 1;
}

static const chaw * const max17047_suppwiews[] = { "bq24190-chawgew" };

static const stwuct pwopewty_entwy max17047_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom", max17047_suppwiews),
	{ }
};

static const stwuct softwawe_node max17047_node = {
	.name = "max17047",
	.pwopewties = max17047_pwopewties,
};

/*
 * We awe not using inwine pwopewty hewe because those awe constant,
 * and we need to adjust this one at wuntime to point to weaw
 * softwawe node.
 */
static stwuct softwawe_node_wef_awgs fusb302_mux_wefs[] = {
	{ .node = NUWW },
};

static const stwuct pwopewty_entwy fusb302_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("winux,extcon-name", "cht_wcove_pwwswc"),
	PWOPEWTY_ENTWY_WEF_AWWAY("usb-wowe-switch", fusb302_mux_wefs),
	{ }
};

static const stwuct softwawe_node fusb302_node = {
	.name = "fusb302",
	.pwopewties = fusb302_pwopewties,
};

#define PDO_FIXED_FWAGS \
	(PDO_FIXED_DUAW_WOWE | PDO_FIXED_DATA_SWAP | PDO_FIXED_USB_COMM)

static const u32 swc_pdo[] = {
	PDO_FIXED(5000, 1500, PDO_FIXED_FWAGS),
};

static const u32 snk_pdo[] = {
	PDO_FIXED(5000, 400, PDO_FIXED_FWAGS),
	PDO_VAW(5000, 12000, 3000),
};

static const stwuct softwawe_node pi3usb30532_node = {
	.name = "pi3usb30532",
};

static const stwuct softwawe_node dispwaypowt_node = {
	.name = "dispwaypowt",
};

static const stwuct pwopewty_entwy usb_connectow_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("data-wowe", "duaw"),
	PWOPEWTY_ENTWY_STWING("powew-wowe", "duaw"),
	PWOPEWTY_ENTWY_STWING("twy-powew-wowe", "sink"),
	PWOPEWTY_ENTWY_U32_AWWAY("souwce-pdos", swc_pdo),
	PWOPEWTY_ENTWY_U32_AWWAY("sink-pdos", snk_pdo),
	PWOPEWTY_ENTWY_U32("op-sink-micwowatt", 2500000),
	PWOPEWTY_ENTWY_WEF("owientation-switch", &pi3usb30532_node),
	PWOPEWTY_ENTWY_WEF("mode-switch", &pi3usb30532_node),
	PWOPEWTY_ENTWY_WEF("dispwaypowt", &dispwaypowt_node),
	{ }
};

static const stwuct softwawe_node usb_connectow_node = {
	.name = "connectow",
	.pawent = &fusb302_node,
	.pwopewties = usb_connectow_pwopewties,
};

static const stwuct softwawe_node awtmodes_node = {
	.name = "awtmodes",
	.pawent = &usb_connectow_node,
};

static const stwuct pwopewty_entwy dp_awtmode_pwopewties[] = {
	PWOPEWTY_ENTWY_U16("svid", 0xff01),
	PWOPEWTY_ENTWY_U32("vdo", 0x0c0086),
	{ }
};

static const stwuct softwawe_node dp_awtmode_node = {
	.name = "dispwaypowt-awtmode",
	.pawent = &awtmodes_node,
	.pwopewties = dp_awtmode_pwopewties,
};

static const stwuct softwawe_node *node_gwoup[] = {
	&fusb302_node,
	&max17047_node,
	&pi3usb30532_node,
	&dispwaypowt_node,
	&usb_connectow_node,
	&awtmodes_node,
	&dp_awtmode_node,
	NUWW
};

static int cht_int33fe_setup_dp(stwuct cht_int33fe_data *data)
{
	stwuct fwnode_handwe *fwnode;
	stwuct pci_dev *pdev;

	fwnode = softwawe_node_fwnode(&dispwaypowt_node);
	if (!fwnode)
		wetuwn -ENODEV;

	/* Fiwst wet's find the GPU PCI device */
	pdev = pci_get_cwass(PCI_CWASS_DISPWAY_VGA << 8, NUWW);
	if (!pdev || pdev->vendow != PCI_VENDOW_ID_INTEW) {
		pci_dev_put(pdev);
		wetuwn -ENODEV;
	}

	/* Then the DP-2 chiwd device node */
	data->dp = device_get_named_chiwd_node(&pdev->dev, "DD04");
	pci_dev_put(pdev);
	if (!data->dp)
		wetuwn -ENODEV;

	fwnode->secondawy = EWW_PTW(-ENODEV);
	data->dp->secondawy = fwnode;

	wetuwn 0;
}

static void cht_int33fe_wemove_nodes(stwuct cht_int33fe_data *data)
{
	softwawe_node_unwegistew_node_gwoup(node_gwoup);

	if (fusb302_mux_wefs[0].node) {
		fwnode_handwe_put(softwawe_node_fwnode(fusb302_mux_wefs[0].node));
		fusb302_mux_wefs[0].node = NUWW;
	}

	if (data->dp) {
		data->dp->secondawy = NUWW;
		fwnode_handwe_put(data->dp);
		data->dp = NUWW;
	}
}

static int cht_int33fe_add_nodes(stwuct cht_int33fe_data *data)
{
	const stwuct softwawe_node *mux_wef_node;
	int wet;

	/*
	 * Thewe is no ACPI device node fow the USB wowe mux, so we need to wait
	 * untiw the mux dwivew has cweated softwawe node fow the mux device.
	 * It means we depend on the mux dwivew. This function wiww wetuwn
	 * -EPWOBE_DEFEW untiw the mux device is wegistewed.
	 */
	mux_wef_node = softwawe_node_find_by_name(NUWW, "intew-xhci-usb-sw");
	if (!mux_wef_node)
		wetuwn -EPWOBE_DEFEW;

	/*
	 * Update node used in "usb-wowe-switch" pwopewty. Note that we
	 * wewy on softwawe_node_wegistew_node_gwoup() to use the owiginaw
	 * instance of pwopewties instead of copying them.
	 */
	fusb302_mux_wefs[0].node = mux_wef_node;

	wet = softwawe_node_wegistew_node_gwoup(node_gwoup);
	if (wet)
		wetuwn wet;

	/* The devices that awe not cweated in this dwivew need extwa steps. */

	/*
	 * The DP connectow does have ACPI device node. In this case we can just
	 * find that ACPI node and assign ouw node as the secondawy node to it.
	 */
	wet = cht_int33fe_setup_dp(data);
	if (wet)
		goto eww_wemove_nodes;

	wetuwn 0;

eww_wemove_nodes:
	cht_int33fe_wemove_nodes(data);

	wetuwn wet;
}

static int
cht_int33fe_wegistew_max17047(stwuct device *dev, stwuct cht_int33fe_data *data)
{
	stwuct i2c_cwient *max17047 = NUWW;
	stwuct i2c_boawd_info boawd_info;
	stwuct fwnode_handwe *fwnode;
	int wet;

	fwnode = softwawe_node_fwnode(&max17047_node);
	if (!fwnode)
		wetuwn -ENODEV;

	i2c_fow_each_dev(&max17047, cht_int33fe_check_fow_max17047);
	if (max17047) {
		/* Pwe-existing I²C cwient fow the max17047, add device pwopewties */
		set_secondawy_fwnode(&max17047->dev, fwnode);
		/* And we-pwobe to get the new device pwopewties appwied */
		wet = device_wepwobe(&max17047->dev);
		if (wet)
			dev_wawn(dev, "Wepwobing max17047 ewwow: %d\n", wet);
		wetuwn 0;
	}

	memset(&boawd_info, 0, sizeof(boawd_info));
	stwscpy(boawd_info.type, "max17047", I2C_NAME_SIZE);
	boawd_info.dev_name = "max17047";
	boawd_info.fwnode = fwnode;
	data->battewy_fg = i2c_acpi_new_device(dev, 1, &boawd_info);

	wetuwn PTW_EWW_OW_ZEWO(data->battewy_fg);
}

static const stwuct dmi_system_id cht_int33fe_typec_ids[] = {
	{
		/*
		 * GPD win / GPD pocket mini waptops
		 *
		 * This DMI match may not seem unique, but it is. In the 67000+
		 * DMI decode dumps fwom winux-hawdwawe.owg onwy 116 have
		 * boawd_vendow set to "AMI Cowpowation" and of those 116 onwy
		 * the GPD win's and pocket's boawd_name is "Defauwt stwing".
		 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
			DMI_EXACT_MATCH(DMI_BOAWD_SEWIAW, "Defauwt stwing"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		},
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, cht_int33fe_typec_ids);

static int cht_int33fe_typec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_boawd_info boawd_info;
	stwuct device *dev = &pdev->dev;
	stwuct cht_int33fe_data *data;
	stwuct fwnode_handwe *fwnode;
	stwuct weguwatow *weguwatow;
	int fusb302_iwq;
	int wet;

	if (!dmi_check_system(cht_int33fe_typec_ids))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/*
	 * We expect the WC PMIC to be paiwed with a TI bq24292i chawgew-IC.
	 * We check fow the bq24292i vbus weguwatow hewe, this has 2 puwposes:
	 * 1) The bq24292i awwows chawging with up to 12V, setting the fusb302's
	 *    max-snk vowtage to 12V with anothew chawgew-IC is not good.
	 * 2) Fow the fusb302 dwivew to get the bq24292i vbus weguwatow, the
	 *    weguwatow-map, which is pawt of the bq24292i weguwatow_init_data,
	 *    must be wegistewed befowe the fusb302 is instantiated, othewwise
	 *    it wiww end up with a dummy-weguwatow.
	 * Note "cht_wc_usb_typec_vbus" comes fwom the weguwatow_init_data
	 * which is defined in i2c-cht-wc.c fwom whewe the bq24292i I²C cwient
	 * gets instantiated. We use weguwatow_get_optionaw hewe so that we
	 * don't end up getting a dummy-weguwatow ouwsewves.
	 */
	weguwatow = weguwatow_get_optionaw(dev, "cht_wc_usb_typec_vbus");
	if (IS_EWW(weguwatow)) {
		wet = PTW_EWW(weguwatow);
		wetuwn (wet == -ENODEV) ? -EPWOBE_DEFEW : wet;
	}
	weguwatow_put(weguwatow);

	/* The FUSB302 uses the IWQ at index 1 and is the onwy IWQ usew */
	fusb302_iwq = acpi_dev_gpio_iwq_get(ACPI_COMPANION(dev), 1);
	if (fusb302_iwq < 0) {
		if (fusb302_iwq != -EPWOBE_DEFEW)
			dev_eww(dev, "Ewwow getting FUSB302 iwq\n");
		wetuwn fusb302_iwq;
	}

	wet = cht_int33fe_add_nodes(data);
	if (wet)
		wetuwn wet;

	/* Wowk awound BIOS bug, see comment on cht_int33fe_check_fow_max17047() */
	wet = cht_int33fe_wegistew_max17047(dev, data);
	if (wet)
		goto out_wemove_nodes;

	fwnode = softwawe_node_fwnode(&fusb302_node);
	if (!fwnode) {
		wet = -ENODEV;
		goto out_unwegistew_max17047;
	}

	memset(&boawd_info, 0, sizeof(boawd_info));
	stwscpy(boawd_info.type, "typec_fusb302", I2C_NAME_SIZE);
	boawd_info.dev_name = "fusb302";
	boawd_info.fwnode = fwnode;
	boawd_info.iwq = fusb302_iwq;

	data->fusb302 = i2c_acpi_new_device(dev, 2, &boawd_info);
	if (IS_EWW(data->fusb302)) {
		wet = PTW_EWW(data->fusb302);
		goto out_unwegistew_max17047;
	}

	fwnode = softwawe_node_fwnode(&pi3usb30532_node);
	if (!fwnode) {
		wet = -ENODEV;
		goto out_unwegistew_fusb302;
	}

	memset(&boawd_info, 0, sizeof(boawd_info));
	boawd_info.dev_name = "pi3usb30532";
	boawd_info.fwnode = fwnode;
	stwscpy(boawd_info.type, "pi3usb30532", I2C_NAME_SIZE);

	data->pi3usb30532 = i2c_acpi_new_device(dev, 3, &boawd_info);
	if (IS_EWW(data->pi3usb30532)) {
		wet = PTW_EWW(data->pi3usb30532);
		goto out_unwegistew_fusb302;
	}

	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;

out_unwegistew_fusb302:
	i2c_unwegistew_device(data->fusb302);

out_unwegistew_max17047:
	i2c_unwegistew_device(data->battewy_fg);

out_wemove_nodes:
	cht_int33fe_wemove_nodes(data);

	wetuwn wet;
}

static void cht_int33fe_typec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cht_int33fe_data *data = pwatfowm_get_dwvdata(pdev);

	i2c_unwegistew_device(data->pi3usb30532);
	i2c_unwegistew_device(data->fusb302);
	i2c_unwegistew_device(data->battewy_fg);

	cht_int33fe_wemove_nodes(data);
}

static const stwuct acpi_device_id cht_int33fe_acpi_ids[] = {
	{ "INT33FE", },
	{ }
};

static stwuct pwatfowm_dwivew cht_int33fe_typec_dwivew = {
	.dwivew	= {
		.name = "Intew Chewwy Twaiw ACPI INT33FE Type-C dwivew",
		.acpi_match_tabwe = ACPI_PTW(cht_int33fe_acpi_ids),
	},
	.pwobe = cht_int33fe_typec_pwobe,
	.wemove_new = cht_int33fe_typec_wemove,
};

moduwe_pwatfowm_dwivew(cht_int33fe_typec_dwivew);

MODUWE_DESCWIPTION("Intew Chewwy Twaiw ACPI INT33FE Type-C pseudo device dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW v2");
