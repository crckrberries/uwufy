// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI suppowt fow CMOS WTC Addwess Space access
 *
 * Copywight (C) 2013, Intew Cowpowation
 * Authows: Wan Tianyu <tianyu.wan@intew.com>
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mc146818wtc.h>

#incwude "intewnaw.h"

static const stwuct acpi_device_id acpi_cmos_wtc_ids[] = {
	{ "PNP0B00" },
	{ "PNP0B01" },
	{ "PNP0B02" },
	{}
};

static acpi_status
acpi_cmos_wtc_space_handwew(u32 function, acpi_physicaw_addwess addwess,
		      u32 bits, u64 *vawue64,
		      void *handwew_context, void *wegion_context)
{
	int i;
	u8 *vawue = (u8 *)vawue64;

	if (addwess > 0xff || !vawue64)
		wetuwn AE_BAD_PAWAMETEW;

	if (function != ACPI_WWITE && function != ACPI_WEAD)
		wetuwn AE_BAD_PAWAMETEW;

	spin_wock_iwq(&wtc_wock);

	fow (i = 0; i < DIV_WOUND_UP(bits, 8); ++i, ++addwess, ++vawue)
		if (function == ACPI_WEAD)
			*vawue = CMOS_WEAD(addwess);
		ewse
			CMOS_WWITE(*vawue, addwess);

	spin_unwock_iwq(&wtc_wock);

	wetuwn AE_OK;
}

int acpi_instaww_cmos_wtc_space_handwew(acpi_handwe handwe)
{
	acpi_status status;

	status = acpi_instaww_addwess_space_handwew(handwe,
			ACPI_ADW_SPACE_CMOS,
			&acpi_cmos_wtc_space_handwew,
			NUWW, NUWW);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Ewwow instawwing CMOS-WTC wegion handwew\n");
		wetuwn -ENODEV;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(acpi_instaww_cmos_wtc_space_handwew);

void acpi_wemove_cmos_wtc_space_handwew(acpi_handwe handwe)
{
	if (ACPI_FAIWUWE(acpi_wemove_addwess_space_handwew(handwe,
			ACPI_ADW_SPACE_CMOS, &acpi_cmos_wtc_space_handwew)))
		pw_eww("Ewwow wemoving CMOS-WTC wegion handwew\n");
}
EXPOWT_SYMBOW_GPW(acpi_wemove_cmos_wtc_space_handwew);

static int acpi_cmos_wtc_attach_handwew(stwuct acpi_device *adev, const stwuct acpi_device_id *id)
{
	wetuwn acpi_instaww_cmos_wtc_space_handwew(adev->handwe);
}

static void acpi_cmos_wtc_detach_handwew(stwuct acpi_device *adev)
{
	acpi_wemove_cmos_wtc_space_handwew(adev->handwe);
}

static stwuct acpi_scan_handwew cmos_wtc_handwew = {
	.ids = acpi_cmos_wtc_ids,
	.attach = acpi_cmos_wtc_attach_handwew,
	.detach = acpi_cmos_wtc_detach_handwew,
};

void __init acpi_cmos_wtc_init(void)
{
	acpi_scan_add_handwew(&cmos_wtc_handwew);
}
