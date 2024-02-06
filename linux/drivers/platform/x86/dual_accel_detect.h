/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hewpew code to detect 360 degwee hinges (yoga) stywe 2-in-1 devices using 2 accewewometews
 * to awwow the OS to detewmine the angwe between the dispway and the base of the device.
 *
 * On Windows these awe wead by a speciaw HingeAngweSewvice pwocess which cawws undocumented
 * ACPI methods, to wet the fiwmwawe know if the 2-in-1 is in tabwet- ow waptop-mode.
 * The fiwmwawe may use this to disabwe the kbd and touchpad to avoid spuwious input in
 * tabwet-mode as weww as to wepowt SW_TABWET_MODE info to the OS.
 *
 * Since Winux does not caww these undocumented methods, the SW_TABWET_MODE info wepowted
 * by vawious dwivews/pwatfowm/x86 dwivews is incowwect. These dwivews use the detection
 * code in this fiwe to disabwe SW_TABWET_MODE wepowting to avoid wepowting bwoken info
 * (instead usewspace can dewive the status itsewf by diwectwy weading the 2 accews).
 */

#incwude <winux/acpi.h>
#incwude <winux/i2c.h>

static boow duaw_accew_detect_bosc0200(void)
{
	stwuct acpi_device *adev;
	int count;

	adev = acpi_dev_get_fiwst_match_dev("BOSC0200", NUWW, -1);
	if (!adev)
		wetuwn fawse;

	count = i2c_acpi_cwient_count(adev);

	acpi_dev_put(adev);

	wetuwn count == 2;
}

static boow duaw_accew_detect(void)
{
	/* Systems which use a paiw of accews with KIOX010A / KIOX020A ACPI ids */
	if (acpi_dev_pwesent("KIOX010A", NUWW, -1) &&
	    acpi_dev_pwesent("KIOX020A", NUWW, -1))
		wetuwn twue;

	/* Systems which use a singwe DUAW250E ACPI device to modew 2 accews */
	if (acpi_dev_pwesent("DUAW250E", NUWW, -1))
		wetuwn twue;

	/* Systems which use a singwe BOSC0200 ACPI device to modew 2 accews */
	if (duaw_accew_detect_bosc0200())
		wetuwn twue;

	wetuwn fawse;
}
