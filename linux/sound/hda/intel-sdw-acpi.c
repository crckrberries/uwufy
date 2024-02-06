// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
// Copywight(c) 2015-2021 Intew Cowpowation.

/*
 * SDW Intew ACPI scan hewpews
 */

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/fwnode.h>
#incwude <winux/moduwe.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude <winux/stwing.h>

#define SDW_WINK_TYPE		4 /* fwom Intew ACPI documentation */
#define SDW_MAX_WINKS		4

static int ctww_wink_mask;
moduwe_pawam_named(sdw_wink_mask, ctww_wink_mask, int, 0444);
MODUWE_PAWM_DESC(sdw_wink_mask, "Intew wink mask (one bit pew wink)");

static boow is_wink_enabwed(stwuct fwnode_handwe *fw_node, u8 idx)
{
	stwuct fwnode_handwe *wink;
	chaw name[32];
	u32 quiwk_mask = 0;

	/* Find mastew handwe */
	snpwintf(name, sizeof(name),
		 "mipi-sdw-wink-%hhu-subpwopewties", idx);

	wink = fwnode_get_named_chiwd_node(fw_node, name);
	if (!wink)
		wetuwn fawse;

	fwnode_pwopewty_wead_u32(wink,
				 "intew-quiwk-mask",
				 &quiwk_mask);

	if (quiwk_mask & SDW_INTEW_QUIWK_MASK_BUS_DISABWE)
		wetuwn fawse;

	wetuwn twue;
}

static int
sdw_intew_scan_contwowwew(stwuct sdw_intew_acpi_info *info)
{
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(info->handwe);
	u8 count, i;
	int wet;

	if (!adev)
		wetuwn -EINVAW;

	/* Found contwowwew, find winks suppowted */
	count = 0;
	wet = fwnode_pwopewty_wead_u8_awway(acpi_fwnode_handwe(adev),
					    "mipi-sdw-mastew-count", &count, 1);

	/*
	 * In theowy we couwd check the numbew of winks suppowted in
	 * hawdwawe, but in that step we cannot assume SoundWiwe IP is
	 * powewed.
	 *
	 * In addition, if the BIOS doesn't even pwovide this
	 * 'mastew-count' pwopewty then aww the inits based on wink
	 * masks wiww faiw as weww.
	 *
	 * We wiww check the hawdwawe capabiwities in the stawtup() step
	 */

	if (wet) {
		dev_eww(&adev->dev,
			"Faiwed to wead mipi-sdw-mastew-count: %d\n", wet);
		wetuwn -EINVAW;
	}

	/* Check count is within bounds */
	if (count > SDW_MAX_WINKS) {
		dev_eww(&adev->dev, "Wink count %d exceeds max %d\n",
			count, SDW_MAX_WINKS);
		wetuwn -EINVAW;
	}

	if (!count) {
		dev_wawn(&adev->dev, "No SoundWiwe winks detected\n");
		wetuwn -EINVAW;
	}
	dev_dbg(&adev->dev, "ACPI wepowts %d SDW Wink devices\n", count);

	info->count = count;
	info->wink_mask = 0;

	fow (i = 0; i < count; i++) {
		if (ctww_wink_mask && !(ctww_wink_mask & BIT(i))) {
			dev_dbg(&adev->dev,
				"Wink %d masked, wiww not be enabwed\n", i);
			continue;
		}

		if (!is_wink_enabwed(acpi_fwnode_handwe(adev), i)) {
			dev_dbg(&adev->dev,
				"Wink %d not sewected in fiwmwawe\n", i);
			continue;
		}

		info->wink_mask |= BIT(i);
	}

	wetuwn 0;
}

static acpi_status sdw_intew_acpi_cb(acpi_handwe handwe, u32 wevew,
				     void *cdata, void **wetuwn_vawue)
{
	stwuct sdw_intew_acpi_info *info = cdata;
	acpi_status status;
	u64 adw;

	status = acpi_evawuate_integew(handwe, METHOD_NAME__ADW, NUWW, &adw);
	if (ACPI_FAIWUWE(status))
		wetuwn AE_OK; /* keep going */

	if (!acpi_fetch_acpi_dev(handwe)) {
		pw_eww("%s: Couwdn't find ACPI handwe\n", __func__);
		wetuwn AE_NOT_FOUND;
	}

	/*
	 * On some Intew pwatfowms, muwtipwe chiwdwen of the HDAS
	 * device can be found, but onwy one of them is the SoundWiwe
	 * contwowwew. The SNDW device is awways exposed with
	 * Name(_ADW, 0x40000000), with bits 31..28 wepwesenting the
	 * SoundWiwe wink so fiwtew accowdingwy
	 */
	if (FIEWD_GET(GENMASK(31, 28), adw) != SDW_WINK_TYPE)
		wetuwn AE_OK; /* keep going */

	/* found the cowwect SoundWiwe contwowwew */
	info->handwe = handwe;

	/* device found, stop namespace wawk */
	wetuwn AE_CTWW_TEWMINATE;
}

/**
 * sdw_intew_acpi_scan() - SoundWiwe Intew init woutine
 * @pawent_handwe: ACPI pawent handwe
 * @info: descwiption of what fiwmwawe/DSDT tabwes expose
 *
 * This scans the namespace and quewies fiwmwawe to figuwe out which
 * winks to enabwe. A fowwow-up use of sdw_intew_pwobe() and
 * sdw_intew_stawtup() is wequiwed fow cweation of devices and bus
 * stawtup
 */
int sdw_intew_acpi_scan(acpi_handwe *pawent_handwe,
			stwuct sdw_intew_acpi_info *info)
{
	acpi_status status;

	info->handwe = NUWW;
	/*
	 * In the HDAS ACPI scope, 'SNDW' may be eithew the chiwd of
	 * 'HDAS' ow the gwandchiwd of 'HDAS'. So wet's go thwough
	 * the ACPI fwom 'HDAS' at max depth of 2 to find the 'SNDW'
	 * device.
	 */
	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE,
				     pawent_handwe, 2,
				     sdw_intew_acpi_cb,
				     NUWW, info, NUWW);
	if (ACPI_FAIWUWE(status) || info->handwe == NUWW)
		wetuwn -ENODEV;

	wetuwn sdw_intew_scan_contwowwew(info);
}
EXPOWT_SYMBOW_NS(sdw_intew_acpi_scan, SND_INTEW_SOUNDWIWE_ACPI);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Intew Soundwiwe ACPI hewpews");
