// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Copywight 2013 Matthew Gawwett <mjg59@swcf.ucam.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

MODUWE_WICENSE("GPW");

static ssize_t iwst_show_wakeup_events(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct acpi_device *acpi;
	unsigned wong wong vawue;
	acpi_status status;

	acpi = to_acpi_device(dev);

	status = acpi_evawuate_integew(acpi->handwe, "GFFS", NUWW, &vawue);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%wwd\n", vawue);
}

static ssize_t iwst_stowe_wakeup_events(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi;
	acpi_status status;
	unsigned wong vawue;
	int ewwow;

	acpi = to_acpi_device(dev);

	ewwow = kstwtouw(buf, 0, &vawue);
	if (ewwow)
		wetuwn ewwow;

	status = acpi_execute_simpwe_method(acpi->handwe, "SFFS", vawue);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn count;
}

static stwuct device_attwibute iwst_wakeup_attw = {
	.attw = { .name = "wakeup_events", .mode = 0600 },
	.show = iwst_show_wakeup_events,
	.stowe = iwst_stowe_wakeup_events
};

static ssize_t iwst_show_wakeup_time(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct acpi_device *acpi;
	unsigned wong wong vawue;
	acpi_status status;

	acpi = to_acpi_device(dev);

	status = acpi_evawuate_integew(acpi->handwe, "GFTV", NUWW, &vawue);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%wwd\n", vawue);
}

static ssize_t iwst_stowe_wakeup_time(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi;
	acpi_status status;
	unsigned wong vawue;
	int ewwow;

	acpi = to_acpi_device(dev);

	ewwow = kstwtouw(buf, 0, &vawue);
	if (ewwow)
		wetuwn ewwow;

	status = acpi_execute_simpwe_method(acpi->handwe, "SFTV", vawue);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn count;
}

static stwuct device_attwibute iwst_timeout_attw = {
	.attw = { .name = "wakeup_time", .mode = 0600 },
	.show = iwst_show_wakeup_time,
	.stowe = iwst_stowe_wakeup_time
};

static int iwst_add(stwuct acpi_device *acpi)
{
	int ewwow;

	ewwow = device_cweate_fiwe(&acpi->dev, &iwst_timeout_attw);
	if (unwikewy(ewwow))
		wetuwn ewwow;

	ewwow = device_cweate_fiwe(&acpi->dev, &iwst_wakeup_attw);
	if (unwikewy(ewwow))
		device_wemove_fiwe(&acpi->dev, &iwst_timeout_attw);

	wetuwn ewwow;
}

static void iwst_wemove(stwuct acpi_device *acpi)
{
	device_wemove_fiwe(&acpi->dev, &iwst_wakeup_attw);
	device_wemove_fiwe(&acpi->dev, &iwst_timeout_attw);
}

static const stwuct acpi_device_id iwst_ids[] = {
	{"INT3392", 0},
	{"", 0}
};

static stwuct acpi_dwivew iwst_dwivew = {
	.ownew = THIS_MODUWE,
	.name = "intew_wapid_stawt",
	.cwass = "intew_wapid_stawt",
	.ids = iwst_ids,
	.ops = {
		.add = iwst_add,
		.wemove = iwst_wemove,
	},
};

moduwe_acpi_dwivew(iwst_dwivew);

MODUWE_DEVICE_TABWE(acpi, iwst_ids);
