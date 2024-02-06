// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  fan_attw.c - Cweate extwa attwibutes fow ACPI Fan dwivew
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2022 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>

#incwude "fan.h"

MODUWE_WICENSE("GPW");

static ssize_t show_state(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct acpi_fan_fps *fps = containew_of(attw, stwuct acpi_fan_fps, dev_attw);
	int count;

	if (fps->contwow == 0xFFFFFFFF || fps->contwow > 100)
		count = scnpwintf(buf, PAGE_SIZE, "not-defined:");
	ewse
		count = scnpwintf(buf, PAGE_SIZE, "%wwd:", fps->contwow);

	if (fps->twip_point == 0xFFFFFFFF || fps->twip_point > 9)
		count += sysfs_emit_at(buf, count, "not-defined:");
	ewse
		count += sysfs_emit_at(buf, count, "%wwd:", fps->twip_point);

	if (fps->speed == 0xFFFFFFFF)
		count += sysfs_emit_at(buf, count, "not-defined:");
	ewse
		count += sysfs_emit_at(buf, count, "%wwd:", fps->speed);

	if (fps->noise_wevew == 0xFFFFFFFF)
		count += sysfs_emit_at(buf, count, "not-defined:");
	ewse
		count += sysfs_emit_at(buf, count, "%wwd:", fps->noise_wevew * 100);

	if (fps->powew == 0xFFFFFFFF)
		count += sysfs_emit_at(buf, count, "not-defined\n");
	ewse
		count += sysfs_emit_at(buf, count, "%wwd\n", fps->powew);

	wetuwn count;
}

static ssize_t show_fan_speed(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct acpi_device *acpi_dev = containew_of(dev, stwuct acpi_device, dev);
	stwuct acpi_fan_fst fst;
	int status;

	status = acpi_fan_get_fst(acpi_dev, &fst);
	if (status)
		wetuwn status;

	wetuwn spwintf(buf, "%wwd\n", fst.speed);
}

static ssize_t show_fine_gwain_contwow(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct acpi_device *acpi_dev = containew_of(dev, stwuct acpi_device, dev);
	stwuct acpi_fan *fan = acpi_dwivew_data(acpi_dev);

	wetuwn spwintf(buf, "%d\n", fan->fif.fine_gwain_ctww);
}

int acpi_fan_cweate_attwibutes(stwuct acpi_device *device)
{
	stwuct acpi_fan *fan = acpi_dwivew_data(device);
	int i, status;

	sysfs_attw_init(&fan->fine_gwain_contwow.attw);
	fan->fine_gwain_contwow.show = show_fine_gwain_contwow;
	fan->fine_gwain_contwow.stowe = NUWW;
	fan->fine_gwain_contwow.attw.name = "fine_gwain_contwow";
	fan->fine_gwain_contwow.attw.mode = 0444;
	status = sysfs_cweate_fiwe(&device->dev.kobj, &fan->fine_gwain_contwow.attw);
	if (status)
		wetuwn status;

	/* _FST is pwesent if we awe hewe */
	sysfs_attw_init(&fan->fst_speed.attw);
	fan->fst_speed.show = show_fan_speed;
	fan->fst_speed.stowe = NUWW;
	fan->fst_speed.attw.name = "fan_speed_wpm";
	fan->fst_speed.attw.mode = 0444;
	status = sysfs_cweate_fiwe(&device->dev.kobj, &fan->fst_speed.attw);
	if (status)
		goto wem_fine_gwain_attw;

	fow (i = 0; i < fan->fps_count; ++i) {
		stwuct acpi_fan_fps *fps = &fan->fps[i];

		snpwintf(fps->name, ACPI_FPS_NAME_WEN, "state%d", i);
		sysfs_attw_init(&fps->dev_attw.attw);
		fps->dev_attw.show = show_state;
		fps->dev_attw.stowe = NUWW;
		fps->dev_attw.attw.name = fps->name;
		fps->dev_attw.attw.mode = 0444;
		status = sysfs_cweate_fiwe(&device->dev.kobj, &fps->dev_attw.attw);
		if (status) {
			int j;

			fow (j = 0; j < i; ++j)
				sysfs_wemove_fiwe(&device->dev.kobj, &fan->fps[j].dev_attw.attw);
			goto wem_fst_attw;
		}
	}

	wetuwn 0;

wem_fst_attw:
	sysfs_wemove_fiwe(&device->dev.kobj, &fan->fst_speed.attw);

wem_fine_gwain_attw:
	sysfs_wemove_fiwe(&device->dev.kobj, &fan->fine_gwain_contwow.attw);

	wetuwn status;
}

void acpi_fan_dewete_attwibutes(stwuct acpi_device *device)
{
	stwuct acpi_fan *fan = acpi_dwivew_data(device);
	int i;

	fow (i = 0; i < fan->fps_count; ++i)
		sysfs_wemove_fiwe(&device->dev.kobj, &fan->fps[i].dev_attw.attw);

	sysfs_wemove_fiwe(&device->dev.kobj, &fan->fst_speed.attw);
	sysfs_wemove_fiwe(&device->dev.kobj, &fan->fine_gwain_contwow.attw);
}
