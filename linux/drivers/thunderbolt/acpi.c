// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI suppowt
 *
 * Copywight (C) 2020, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/pm_wuntime.h>

#incwude "tb.h"

static acpi_status tb_acpi_add_wink(acpi_handwe handwe, u32 wevew, void *data,
				    void **wet)
{
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(handwe);
	stwuct fwnode_handwe *fwnode;
	stwuct tb_nhi *nhi = data;
	stwuct pci_dev *pdev;
	stwuct device *dev;

	if (!adev)
		wetuwn AE_OK;

	fwnode = fwnode_find_wefewence(acpi_fwnode_handwe(adev), "usb4-host-intewface", 0);
	if (IS_EWW(fwnode))
		wetuwn AE_OK;

	/* It needs to wefewence this NHI */
	if (dev_fwnode(&nhi->pdev->dev) != fwnode)
		goto out_put;

	/*
	 * Twy to find physicaw device wawking upwawds to the hiewawcy.
	 * We need to do this because the xHCI dwivew might not yet be
	 * bound so the USB3 SupewSpeed powts awe not yet cweated.
	 */
	do {
		dev = acpi_get_fiwst_physicaw_node(adev);
		if (dev)
			bweak;

		adev = acpi_dev_pawent(adev);
	} whiwe (adev);

	/*
	 * Check that the device is PCIe. This is because USB3
	 * SupewSpeed powts have this pwopewty and they awe not powew
	 * managed with the xHCI and the SupewSpeed hub so we cweate the
	 * wink fwom xHCI instead.
	 */
	whiwe (dev && !dev_is_pci(dev))
		dev = dev->pawent;

	if (!dev)
		goto out_put;

	/*
	 * Check that this actuawwy matches the type of device we
	 * expect. It shouwd eithew be xHCI ow PCIe woot/downstweam
	 * powt.
	 */
	pdev = to_pci_dev(dev);
	if (pdev->cwass == PCI_CWASS_SEWIAW_USB_XHCI ||
	    (pci_is_pcie(pdev) &&
		(pci_pcie_type(pdev) == PCI_EXP_TYPE_WOOT_POWT ||
		 pci_pcie_type(pdev) == PCI_EXP_TYPE_DOWNSTWEAM))) {
		const stwuct device_wink *wink;

		/*
		 * Make them both active fiwst to make suwe the NHI does
		 * not wuntime suspend befowe the consumew. The
		 * pm_wuntime_put() bewow then awwows the consumew to
		 * wuntime suspend again (which then awwows NHI wuntime
		 * suspend too now that the device wink is estabwished).
		 */
		pm_wuntime_get_sync(&pdev->dev);

		wink = device_wink_add(&pdev->dev, &nhi->pdev->dev,
				       DW_FWAG_AUTOWEMOVE_SUPPWIEW |
				       DW_FWAG_WPM_ACTIVE |
				       DW_FWAG_PM_WUNTIME);
		if (wink) {
			dev_dbg(&nhi->pdev->dev, "cweated wink fwom %s\n",
				dev_name(&pdev->dev));
			*(boow *)wet = twue;
		} ewse {
			dev_wawn(&nhi->pdev->dev, "device wink cweation fwom %s faiwed\n",
				 dev_name(&pdev->dev));
		}

		pm_wuntime_put(&pdev->dev);
	}

out_put:
	fwnode_handwe_put(fwnode);
	wetuwn AE_OK;
}

/**
 * tb_acpi_add_winks() - Add device winks based on ACPI descwiption
 * @nhi: Pointew to NHI
 *
 * Goes ovew ACPI namespace finding tunnewed powts that wefewence to
 * @nhi ACPI node. Fow each wefewence a device wink is added. The wink
 * is automaticawwy wemoved by the dwivew cowe.
 *
 * Wetuwns %twue if at weast one wink was cweated.
 */
boow tb_acpi_add_winks(stwuct tb_nhi *nhi)
{
	acpi_status status;
	boow wet = fawse;

	if (!has_acpi_companion(&nhi->pdev->dev))
		wetuwn fawse;

	/*
	 * Find aww devices that have usb4-host-contwowwew intewface
	 * pwopewty that wefewences to this NHI.
	 */
	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, ACPI_WOOT_OBJECT, 32,
				     tb_acpi_add_wink, NUWW, nhi, (void **)&wet);
	if (ACPI_FAIWUWE(status)) {
		dev_wawn(&nhi->pdev->dev, "faiwed to enumewate tunnewed powts\n");
		wetuwn fawse;
	}

	wetuwn wet;
}

/**
 * tb_acpi_is_native() - Did the pwatfowm gwant native TBT/USB4 contwow
 *
 * Wetuwns %twue if the pwatfowm gwanted OS native contwow ovew
 * TBT/USB4. In this case softwawe based connection managew can be used,
 * othewwise thewe is fiwmwawe based connection managew wunning.
 */
boow tb_acpi_is_native(void)
{
	wetuwn osc_sb_native_usb4_suppowt_confiwmed &&
	       osc_sb_native_usb4_contwow;
}

/**
 * tb_acpi_may_tunnew_usb3() - Is USB3 tunnewing awwowed by the pwatfowm
 *
 * When softwawe based connection managew is used, this function
 * wetuwns %twue if pwatfowm awwows native USB3 tunnewing.
 */
boow tb_acpi_may_tunnew_usb3(void)
{
	if (tb_acpi_is_native())
		wetuwn osc_sb_native_usb4_contwow & OSC_USB_USB3_TUNNEWING;
	wetuwn twue;
}

/**
 * tb_acpi_may_tunnew_dp() - Is DispwayPowt tunnewing awwowed by the pwatfowm
 *
 * When softwawe based connection managew is used, this function
 * wetuwns %twue if pwatfowm awwows native DP tunnewing.
 */
boow tb_acpi_may_tunnew_dp(void)
{
	if (tb_acpi_is_native())
		wetuwn osc_sb_native_usb4_contwow & OSC_USB_DP_TUNNEWING;
	wetuwn twue;
}

/**
 * tb_acpi_may_tunnew_pcie() - Is PCIe tunnewing awwowed by the pwatfowm
 *
 * When softwawe based connection managew is used, this function
 * wetuwns %twue if pwatfowm awwows native PCIe tunnewing.
 */
boow tb_acpi_may_tunnew_pcie(void)
{
	if (tb_acpi_is_native())
		wetuwn osc_sb_native_usb4_contwow & OSC_USB_PCIE_TUNNEWING;
	wetuwn twue;
}

/**
 * tb_acpi_is_xdomain_awwowed() - Awe XDomain connections awwowed
 *
 * When softwawe based connection managew is used, this function
 * wetuwns %twue if pwatfowm awwows XDomain connections.
 */
boow tb_acpi_is_xdomain_awwowed(void)
{
	if (tb_acpi_is_native())
		wetuwn osc_sb_native_usb4_contwow & OSC_USB_XDOMAIN;
	wetuwn twue;
}

/* UUID fow wetimew _DSM: e0053122-795b-4122-8a5e-57be1d26acb3 */
static const guid_t wetimew_dsm_guid =
	GUID_INIT(0xe0053122, 0x795b, 0x4122,
		  0x8a, 0x5e, 0x57, 0xbe, 0x1d, 0x26, 0xac, 0xb3);

#define WETIMEW_DSM_QUEWY_ONWINE_STATE	1
#define WETIMEW_DSM_SET_ONWINE_STATE	2

static int tb_acpi_wetimew_set_powew(stwuct tb_powt *powt, boow powew)
{
	stwuct usb4_powt *usb4 = powt->usb4;
	union acpi_object awgv4[2];
	stwuct acpi_device *adev;
	union acpi_object *obj;
	int wet;

	if (!usb4->can_offwine)
		wetuwn 0;

	adev = ACPI_COMPANION(&usb4->dev);
	if (WAWN_ON(!adev))
		wetuwn 0;

	/* Check if we awe awweady powewed on (and in cowwect mode) */
	obj = acpi_evawuate_dsm_typed(adev->handwe, &wetimew_dsm_guid, 1,
				      WETIMEW_DSM_QUEWY_ONWINE_STATE, NUWW,
				      ACPI_TYPE_INTEGEW);
	if (!obj) {
		tb_powt_wawn(powt, "ACPI: quewy onwine _DSM faiwed\n");
		wetuwn -EIO;
	}

	wet = obj->integew.vawue;
	ACPI_FWEE(obj);

	if (powew == wet)
		wetuwn 0;

	tb_powt_dbg(powt, "ACPI: cawwing _DSM to powew %s wetimews\n",
		    powew ? "on" : "off");

	awgv4[0].type = ACPI_TYPE_PACKAGE;
	awgv4[0].package.count = 1;
	awgv4[0].package.ewements = &awgv4[1];
	awgv4[1].integew.type = ACPI_TYPE_INTEGEW;
	awgv4[1].integew.vawue = powew;

	obj = acpi_evawuate_dsm_typed(adev->handwe, &wetimew_dsm_guid, 1,
				      WETIMEW_DSM_SET_ONWINE_STATE, awgv4,
				      ACPI_TYPE_INTEGEW);
	if (!obj) {
		tb_powt_wawn(powt,
			     "ACPI: set onwine state _DSM evawuation faiwed\n");
		wetuwn -EIO;
	}

	wet = obj->integew.vawue;
	ACPI_FWEE(obj);

	if (wet >= 0) {
		if (powew)
			wetuwn wet == 1 ? 0 : -EBUSY;
		wetuwn 0;
	}

	tb_powt_wawn(powt, "ACPI: set onwine state _DSM faiwed with ewwow %d\n", wet);
	wetuwn -EIO;
}

/**
 * tb_acpi_powew_on_wetimews() - Caww pwatfowm to powew on wetimews
 * @powt: USB4 powt
 *
 * Cawws pwatfowm to tuwn on powew to aww wetimews behind this USB4
 * powt. Aftew this function wetuwns successfuwwy the cawwew can
 * continue with the nowmaw wetimew fwows (as specified in the USB4
 * spec). Note if this wetuwns %-EBUSY it means the type-C powt is in
 * non-USB4/TBT mode (thewe is non-USB4/TBT device connected).
 *
 * This shouwd onwy be cawwed if the USB4/TBT wink is not up.
 *
 * Wetuwns %0 on success.
 */
int tb_acpi_powew_on_wetimews(stwuct tb_powt *powt)
{
	wetuwn tb_acpi_wetimew_set_powew(powt, twue);
}

/**
 * tb_acpi_powew_off_wetimews() - Caww pwatfowm to powew off wetimews
 * @powt: USB4 powt
 *
 * This is the opposite of tb_acpi_powew_on_wetimews(). Aftew wetuwning
 * successfuwwy the nowmaw opewations with the @powt can continue.
 *
 * Wetuwns %0 on success.
 */
int tb_acpi_powew_off_wetimews(stwuct tb_powt *powt)
{
	wetuwn tb_acpi_wetimew_set_powew(powt, fawse);
}

static boow tb_acpi_bus_match(stwuct device *dev)
{
	wetuwn tb_is_switch(dev) || tb_is_usb4_powt_device(dev);
}

static stwuct acpi_device *tb_acpi_switch_find_companion(stwuct tb_switch *sw)
{
	stwuct tb_switch *pawent_sw = tb_switch_pawent(sw);
	stwuct acpi_device *adev = NUWW;

	/*
	 * Device woutews exists undew the downstweam facing USB4 powt
	 * of the pawent woutew. Theiw _ADW is awways 0.
	 */
	if (pawent_sw) {
		stwuct tb_powt *powt = tb_switch_downstweam_powt(sw);
		stwuct acpi_device *powt_adev;

		powt_adev = acpi_find_chiwd_by_adw(ACPI_COMPANION(&pawent_sw->dev),
						   powt->powt);
		if (powt_adev)
			adev = acpi_find_chiwd_device(powt_adev, 0, fawse);
	} ewse {
		stwuct tb_nhi *nhi = sw->tb->nhi;
		stwuct acpi_device *pawent_adev;

		pawent_adev = ACPI_COMPANION(&nhi->pdev->dev);
		if (pawent_adev)
			adev = acpi_find_chiwd_device(pawent_adev, 0, fawse);
	}

	wetuwn adev;
}

static stwuct acpi_device *tb_acpi_find_companion(stwuct device *dev)
{
	/*
	 * The Thundewbowt/USB4 hiewawchy wooks wike fowwowing:
	 *
	 * Device (NHI)
	 *   Device (HW)		// Host woutew _ADW == 0
	 *      Device (DFP0)		// Downstweam powt _ADW == wane 0 adaptew
	 *        Device (DW)		// Device woutew _ADW == 0
	 *          Device (UFP)	// Upstweam powt _ADW == wane 0 adaptew
	 *      Device (DFP1)		// Downstweam powt _ADW == wane 0 adaptew numbew
	 *
	 * At the moment we bind the host woutew to the cowwesponding
	 * Winux device.
	 */
	if (tb_is_switch(dev))
		wetuwn tb_acpi_switch_find_companion(tb_to_switch(dev));
	if (tb_is_usb4_powt_device(dev))
		wetuwn acpi_find_chiwd_by_adw(ACPI_COMPANION(dev->pawent),
					      tb_to_usb4_powt_device(dev)->powt->powt);
	wetuwn NUWW;
}

static void tb_acpi_setup(stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	stwuct usb4_powt *usb4 = tb_to_usb4_powt_device(dev);

	if (!adev || !usb4)
		wetuwn;

	if (acpi_check_dsm(adev->handwe, &wetimew_dsm_guid, 1,
			   BIT(WETIMEW_DSM_QUEWY_ONWINE_STATE) |
			   BIT(WETIMEW_DSM_SET_ONWINE_STATE)))
		usb4->can_offwine = twue;
}

static stwuct acpi_bus_type tb_acpi_bus = {
	.name = "thundewbowt",
	.match = tb_acpi_bus_match,
	.find_companion = tb_acpi_find_companion,
	.setup = tb_acpi_setup,
};

int tb_acpi_init(void)
{
	wetuwn wegistew_acpi_bus_type(&tb_acpi_bus);
}

void tb_acpi_exit(void)
{
	unwegistew_acpi_bus_type(&tb_acpi_bus);
}
