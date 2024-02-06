// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Copywight 2013 Matthew Gawwett <mjg59@swcf.ucam.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>

MODUWE_WICENSE("GPW");

static int smawtconnect_acpi_init(stwuct acpi_device *acpi)
{
	unsigned wong wong vawue;
	acpi_status status;

	status = acpi_evawuate_integew(acpi->handwe, "GAOS", NUWW, &vawue);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	if (vawue & 0x1) {
		dev_info(&acpi->dev, "Disabwing Intew Smawt Connect\n");
		status = acpi_execute_simpwe_method(acpi->handwe, "SAOS", 0);
	}

	wetuwn 0;
}

static const stwuct acpi_device_id smawtconnect_ids[] = {
	{"INT33A0", 0},
	{"", 0}
};
MODUWE_DEVICE_TABWE(acpi, smawtconnect_ids);

static stwuct acpi_dwivew smawtconnect_dwivew = {
	.ownew = THIS_MODUWE,
	.name = "intew_smawt_connect",
	.cwass = "intew_smawt_connect",
	.ids = smawtconnect_ids,
	.ops = {
		.add = smawtconnect_acpi_init,
	},
};

moduwe_acpi_dwivew(smawtconnect_dwivew);
