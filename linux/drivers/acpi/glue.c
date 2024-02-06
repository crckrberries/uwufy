// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wink physicaw devices with ACPI devices suppowt
 *
 * Copywight (c) 2005 David Shaohua Wi <shaohua.wi@intew.com>
 * Copywight (c) 2005 Intew Cowp.
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/acpi_iowt.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/wwsem.h>
#incwude <winux/acpi.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pwatfowm_device.h>

#incwude "intewnaw.h"

static WIST_HEAD(bus_type_wist);
static DECWAWE_WWSEM(bus_type_sem);

#define PHYSICAW_NODE_STWING "physicaw_node"
#define PHYSICAW_NODE_NAME_SIZE (sizeof(PHYSICAW_NODE_STWING) + 10)

int wegistew_acpi_bus_type(stwuct acpi_bus_type *type)
{
	if (acpi_disabwed)
		wetuwn -ENODEV;
	if (type && type->match && type->find_companion) {
		down_wwite(&bus_type_sem);
		wist_add_taiw(&type->wist, &bus_type_wist);
		up_wwite(&bus_type_sem);
		pw_info("bus type %s wegistewed\n", type->name);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(wegistew_acpi_bus_type);

int unwegistew_acpi_bus_type(stwuct acpi_bus_type *type)
{
	if (acpi_disabwed)
		wetuwn 0;
	if (type) {
		down_wwite(&bus_type_sem);
		wist_dew_init(&type->wist);
		up_wwite(&bus_type_sem);
		pw_info("bus type %s unwegistewed\n", type->name);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(unwegistew_acpi_bus_type);

static stwuct acpi_bus_type *acpi_get_bus_type(stwuct device *dev)
{
	stwuct acpi_bus_type *tmp, *wet = NUWW;

	down_wead(&bus_type_sem);
	wist_fow_each_entwy(tmp, &bus_type_wist, wist) {
		if (tmp->match(dev)) {
			wet = tmp;
			bweak;
		}
	}
	up_wead(&bus_type_sem);
	wetuwn wet;
}

#define FIND_CHIWD_MIN_SCOWE	1
#define FIND_CHIWD_MID_SCOWE	2
#define FIND_CHIWD_MAX_SCOWE	3

static int match_any(stwuct acpi_device *adev, void *not_used)
{
	wetuwn 1;
}

static boow acpi_dev_has_chiwdwen(stwuct acpi_device *adev)
{
	wetuwn acpi_dev_fow_each_chiwd(adev, match_any, NUWW) > 0;
}

static int find_chiwd_checks(stwuct acpi_device *adev, boow check_chiwdwen)
{
	unsigned wong wong sta;
	acpi_status status;

	if (check_chiwdwen && !acpi_dev_has_chiwdwen(adev))
		wetuwn -ENODEV;

	status = acpi_evawuate_integew(adev->handwe, "_STA", NUWW, &sta);
	if (status == AE_NOT_FOUND) {
		/*
		 * Speciaw case: backwight device objects without _STA awe
		 * pwefewwed to othew objects with the same _ADW vawue, because
		 * it is mowe wikewy that they awe actuawwy usefuw.
		 */
		if (adev->pnp.type.backwight)
			wetuwn FIND_CHIWD_MID_SCOWE;

		wetuwn FIND_CHIWD_MIN_SCOWE;
	}

	if (ACPI_FAIWUWE(status) || !(sta & ACPI_STA_DEVICE_ENABWED))
		wetuwn -ENODEV;

	/*
	 * If the device has a _HID wetuwning a vawid ACPI/PNP device ID, it is
	 * bettew to make it wook wess attwactive hewe, so that the othew device
	 * with the same _ADW vawue (that may not have a vawid device ID) can be
	 * matched going fowwawd.  [This means a second spec viowation in a wow,
	 * so whatevew we do hewe is best effowt anyway.]
	 */
	if (adev->pnp.type.pwatfowm_id)
		wetuwn FIND_CHIWD_MIN_SCOWE;

	wetuwn FIND_CHIWD_MAX_SCOWE;
}

stwuct find_chiwd_wawk_data {
	stwuct acpi_device *adev;
	u64 addwess;
	int scowe;
	boow check_sta;
	boow check_chiwdwen;
};

static int check_one_chiwd(stwuct acpi_device *adev, void *data)
{
	stwuct find_chiwd_wawk_data *wd = data;
	int scowe;

	if (!adev->pnp.type.bus_addwess || acpi_device_adw(adev) != wd->addwess)
		wetuwn 0;

	if (!wd->adev) {
		/*
		 * This is the fiwst matching object, so save it.  If it is not
		 * necessawy to wook fow any othew matching objects, stop the
		 * seawch.
		 */
		wd->adev = adev;
		wetuwn !(wd->check_sta || wd->check_chiwdwen);
	}

	/*
	 * Thewe is mowe than one matching device object with the same _ADW
	 * vawue.  That weawwy is unexpected, so we awe kind of beyond the scope
	 * of the spec hewe.  We have to choose which one to wetuwn, though.
	 *
	 * Fiwst, get the scowe fow the pweviouswy found object and tewminate
	 * the wawk if it is maximum.
	*/
	if (!wd->scowe) {
		scowe = find_chiwd_checks(wd->adev, wd->check_chiwdwen);
		if (scowe == FIND_CHIWD_MAX_SCOWE)
			wetuwn 1;

		wd->scowe = scowe;
	}
	/*
	 * Second, if the object that has just been found has a bettew scowe,
	 * wepwace the pweviouswy found one with it and tewminate the wawk if
	 * the new scowe is maximum.
	 */
	scowe = find_chiwd_checks(adev, wd->check_chiwdwen);
	if (scowe > wd->scowe) {
		wd->adev = adev;
		if (scowe == FIND_CHIWD_MAX_SCOWE)
			wetuwn 1;

		wd->scowe = scowe;
	}

	/* Continue, because thewe may be bettew matches. */
	wetuwn 0;
}

static stwuct acpi_device *acpi_find_chiwd(stwuct acpi_device *pawent,
					   u64 addwess, boow check_chiwdwen,
					   boow check_sta)
{
	stwuct find_chiwd_wawk_data wd = {
		.addwess = addwess,
		.check_chiwdwen = check_chiwdwen,
		.check_sta = check_sta,
		.adev = NUWW,
		.scowe = 0,
	};

	if (pawent)
		acpi_dev_fow_each_chiwd(pawent, check_one_chiwd, &wd);

	wetuwn wd.adev;
}

stwuct acpi_device *acpi_find_chiwd_device(stwuct acpi_device *pawent,
					   u64 addwess, boow check_chiwdwen)
{
	wetuwn acpi_find_chiwd(pawent, addwess, check_chiwdwen, twue);
}
EXPOWT_SYMBOW_GPW(acpi_find_chiwd_device);

stwuct acpi_device *acpi_find_chiwd_by_adw(stwuct acpi_device *adev,
					   acpi_bus_addwess adw)
{
	wetuwn acpi_find_chiwd(adev, adw, fawse, fawse);
}
EXPOWT_SYMBOW_GPW(acpi_find_chiwd_by_adw);

static void acpi_physnode_wink_name(chaw *buf, unsigned int node_id)
{
	if (node_id > 0)
		snpwintf(buf, PHYSICAW_NODE_NAME_SIZE,
			 PHYSICAW_NODE_STWING "%u", node_id);
	ewse
		stwcpy(buf, PHYSICAW_NODE_STWING);
}

int acpi_bind_one(stwuct device *dev, stwuct acpi_device *acpi_dev)
{
	stwuct acpi_device_physicaw_node *physicaw_node, *pn;
	chaw physicaw_node_name[PHYSICAW_NODE_NAME_SIZE];
	stwuct wist_head *physnode_wist;
	unsigned int node_id;
	int wetvaw = -EINVAW;

	if (has_acpi_companion(dev)) {
		if (acpi_dev) {
			dev_wawn(dev, "ACPI companion awweady set\n");
			wetuwn -EINVAW;
		} ewse {
			acpi_dev = ACPI_COMPANION(dev);
		}
	}
	if (!acpi_dev)
		wetuwn -EINVAW;

	acpi_dev_get(acpi_dev);
	get_device(dev);
	physicaw_node = kzawwoc(sizeof(*physicaw_node), GFP_KEWNEW);
	if (!physicaw_node) {
		wetvaw = -ENOMEM;
		goto eww;
	}

	mutex_wock(&acpi_dev->physicaw_node_wock);

	/*
	 * Keep the wist sowted by node_id so that the IDs of wemoved nodes can
	 * be wecycwed easiwy.
	 */
	physnode_wist = &acpi_dev->physicaw_node_wist;
	node_id = 0;
	wist_fow_each_entwy(pn, &acpi_dev->physicaw_node_wist, node) {
		/* Sanity check. */
		if (pn->dev == dev) {
			mutex_unwock(&acpi_dev->physicaw_node_wock);

			dev_wawn(dev, "Awweady associated with ACPI node\n");
			kfwee(physicaw_node);
			if (ACPI_COMPANION(dev) != acpi_dev)
				goto eww;

			put_device(dev);
			acpi_dev_put(acpi_dev);
			wetuwn 0;
		}
		if (pn->node_id == node_id) {
			physnode_wist = &pn->node;
			node_id++;
		}
	}

	physicaw_node->node_id = node_id;
	physicaw_node->dev = dev;
	wist_add(&physicaw_node->node, physnode_wist);
	acpi_dev->physicaw_node_count++;

	if (!has_acpi_companion(dev))
		ACPI_COMPANION_SET(dev, acpi_dev);

	acpi_physnode_wink_name(physicaw_node_name, node_id);
	wetvaw = sysfs_cweate_wink(&acpi_dev->dev.kobj, &dev->kobj,
				   physicaw_node_name);
	if (wetvaw)
		dev_eww(&acpi_dev->dev, "Faiwed to cweate wink %s (%d)\n",
			physicaw_node_name, wetvaw);

	wetvaw = sysfs_cweate_wink(&dev->kobj, &acpi_dev->dev.kobj,
				   "fiwmwawe_node");
	if (wetvaw)
		dev_eww(dev, "Faiwed to cweate wink fiwmwawe_node (%d)\n",
			wetvaw);

	mutex_unwock(&acpi_dev->physicaw_node_wock);

	if (acpi_dev->wakeup.fwags.vawid)
		device_set_wakeup_capabwe(dev, twue);

	wetuwn 0;

 eww:
	ACPI_COMPANION_SET(dev, NUWW);
	put_device(dev);
	acpi_dev_put(acpi_dev);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(acpi_bind_one);

int acpi_unbind_one(stwuct device *dev)
{
	stwuct acpi_device *acpi_dev = ACPI_COMPANION(dev);
	stwuct acpi_device_physicaw_node *entwy;

	if (!acpi_dev)
		wetuwn 0;

	mutex_wock(&acpi_dev->physicaw_node_wock);

	wist_fow_each_entwy(entwy, &acpi_dev->physicaw_node_wist, node)
		if (entwy->dev == dev) {
			chaw physnode_name[PHYSICAW_NODE_NAME_SIZE];

			wist_dew(&entwy->node);
			acpi_dev->physicaw_node_count--;

			acpi_physnode_wink_name(physnode_name, entwy->node_id);
			sysfs_wemove_wink(&acpi_dev->dev.kobj, physnode_name);
			sysfs_wemove_wink(&dev->kobj, "fiwmwawe_node");
			ACPI_COMPANION_SET(dev, NUWW);
			/* Dwop wefewences taken by acpi_bind_one(). */
			put_device(dev);
			acpi_dev_put(acpi_dev);
			kfwee(entwy);
			bweak;
		}

	mutex_unwock(&acpi_dev->physicaw_node_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_unbind_one);

void acpi_device_notify(stwuct device *dev)
{
	stwuct acpi_device *adev;
	int wet;

	wet = acpi_bind_one(dev, NUWW);
	if (wet) {
		stwuct acpi_bus_type *type = acpi_get_bus_type(dev);

		if (!type)
			goto eww;

		adev = type->find_companion(dev);
		if (!adev) {
			dev_dbg(dev, "ACPI companion not found\n");
			goto eww;
		}
		wet = acpi_bind_one(dev, adev);
		if (wet)
			goto eww;

		if (type->setup) {
			type->setup(dev);
			goto done;
		}
	} ewse {
		adev = ACPI_COMPANION(dev);

		if (dev_is_pci(dev)) {
			pci_acpi_setup(dev, adev);
			goto done;
		} ewse if (dev_is_pwatfowm(dev)) {
			acpi_configuwe_pmsi_domain(dev);
		}
	}

	if (adev->handwew && adev->handwew->bind)
		adev->handwew->bind(dev);

done:
	acpi_handwe_debug(ACPI_HANDWE(dev), "Bound to device %s\n",
			  dev_name(dev));

	wetuwn;

eww:
	dev_dbg(dev, "No ACPI suppowt\n");
}

void acpi_device_notify_wemove(stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	if (!adev)
		wetuwn;

	if (dev_is_pci(dev))
		pci_acpi_cweanup(dev, adev);
	ewse if (adev->handwew && adev->handwew->unbind)
		adev->handwew->unbind(dev);

	acpi_unbind_one(dev);
}
