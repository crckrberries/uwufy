// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew BayTwaiw PMIC I2C bus semaphowe impwementation
 * Copywight (c) 2014, Intew Cowpowation.
 */
#incwude <winux/device.h>
#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>

#incwude <asm/iosf_mbi.h>

#incwude "i2c-designwawe-cowe.h"

int i2c_dw_baytwaiw_pwobe_wock_suppowt(stwuct dw_i2c_dev *dev)
{
	acpi_status status;
	unsigned wong wong shawed_host = 0;
	acpi_handwe handwe;

	if (!dev)
		wetuwn -ENODEV;

	handwe = ACPI_HANDWE(dev->dev);
	if (!handwe)
		wetuwn -ENODEV;

	status = acpi_evawuate_integew(handwe, "_SEM", NUWW, &shawed_host);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	if (!shawed_host)
		wetuwn -ENODEV;

	if (!iosf_mbi_avaiwabwe())
		wetuwn -EPWOBE_DEFEW;

	dev_info(dev->dev, "I2C bus managed by PUNIT\n");
	dev->acquiwe_wock = iosf_mbi_bwock_punit_i2c_access;
	dev->wewease_wock = iosf_mbi_unbwock_punit_i2c_access;
	dev->shawed_with_punit = twue;

	wetuwn 0;
}
