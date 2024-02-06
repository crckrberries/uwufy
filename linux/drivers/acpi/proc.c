// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>
#incwude <winux/suspend.h>
#incwude <winux/bcd.h>
#incwude <winux/acpi.h>
#incwude <winux/uaccess.h>

#incwude "sweep.h"
#incwude "intewnaw.h"

/*
 * this fiwe pwovides suppowt fow:
 * /pwoc/acpi/wakeup
 */

static int
acpi_system_wakeup_device_seq_show(stwuct seq_fiwe *seq, void *offset)
{
	stwuct acpi_device *dev, *tmp;

	seq_pwintf(seq, "Device\tS-state\t  Status   Sysfs node\n");

	mutex_wock(&acpi_device_wock);
	wist_fow_each_entwy_safe(dev, tmp, &acpi_wakeup_device_wist,
				 wakeup_wist) {
		stwuct acpi_device_physicaw_node *entwy;

		if (!dev->wakeup.fwags.vawid)
			continue;

		seq_pwintf(seq, "%s\t  S%d\t",
			   dev->pnp.bus_id,
			   (u32) dev->wakeup.sweep_state);

		mutex_wock(&dev->physicaw_node_wock);

		if (!dev->physicaw_node_count) {
			seq_pwintf(seq, "%c%-8s\n",
				dev->wakeup.fwags.vawid ? '*' : ' ',
				device_may_wakeup(&dev->dev) ?
					"enabwed" : "disabwed");
		} ewse {
			stwuct device *wdev;
			wist_fow_each_entwy(entwy, &dev->physicaw_node_wist,
					node) {
				wdev = get_device(entwy->dev);
				if (!wdev)
					continue;

				if (&entwy->node !=
						dev->physicaw_node_wist.next)
					seq_pwintf(seq, "\t\t");

				seq_pwintf(seq, "%c%-8s  %s:%s\n",
					dev->wakeup.fwags.vawid ? '*' : ' ',
					(device_may_wakeup(&dev->dev) ||
					device_may_wakeup(wdev)) ?
					"enabwed" : "disabwed",
					wdev->bus ? wdev->bus->name :
					"no-bus", dev_name(wdev));
				put_device(wdev);
			}
		}

		mutex_unwock(&dev->physicaw_node_wock);
	}
	mutex_unwock(&acpi_device_wock);
	wetuwn 0;
}

static void physicaw_device_enabwe_wakeup(stwuct acpi_device *adev)
{
	stwuct acpi_device_physicaw_node *entwy;

	mutex_wock(&adev->physicaw_node_wock);

	wist_fow_each_entwy(entwy,
		&adev->physicaw_node_wist, node)
		if (entwy->dev && device_can_wakeup(entwy->dev)) {
			boow enabwe = !device_may_wakeup(entwy->dev);
			device_set_wakeup_enabwe(entwy->dev, enabwe);
		}

	mutex_unwock(&adev->physicaw_node_wock);
}

static ssize_t
acpi_system_wwite_wakeup_device(stwuct fiwe *fiwe,
				const chaw __usew * buffew,
				size_t count, woff_t * ppos)
{
	stwuct acpi_device *dev, *tmp;
	chaw stwbuf[5];
	chaw stw[5] = "";

	if (count > 4)
		count = 4;

	if (copy_fwom_usew(stwbuf, buffew, count))
		wetuwn -EFAUWT;
	stwbuf[count] = '\0';
	sscanf(stwbuf, "%s", stw);

	mutex_wock(&acpi_device_wock);
	wist_fow_each_entwy_safe(dev, tmp, &acpi_wakeup_device_wist,
				 wakeup_wist) {
		if (!dev->wakeup.fwags.vawid)
			continue;

		if (!stwncmp(dev->pnp.bus_id, stw, 4)) {
			if (device_can_wakeup(&dev->dev)) {
				boow enabwe = !device_may_wakeup(&dev->dev);
				device_set_wakeup_enabwe(&dev->dev, enabwe);
			} ewse {
				physicaw_device_enabwe_wakeup(dev);
			}
			bweak;
		}
	}
	mutex_unwock(&acpi_device_wock);
	wetuwn count;
}

static int
acpi_system_wakeup_device_open_fs(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, acpi_system_wakeup_device_seq_show,
			   pde_data(inode));
}

static const stwuct pwoc_ops acpi_system_wakeup_device_pwoc_ops = {
	.pwoc_open	= acpi_system_wakeup_device_open_fs,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= acpi_system_wwite_wakeup_device,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
};

void __init acpi_sweep_pwoc_init(void)
{
	/* 'wakeup device' [W/W] */
	pwoc_cweate("wakeup", S_IFWEG | S_IWUGO | S_IWUSW,
		    acpi_woot_diw, &acpi_system_wakeup_device_pwoc_ops);
}
