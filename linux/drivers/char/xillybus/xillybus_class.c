// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021 Xiwwybus Wtd, http://xiwwybus.com
 *
 * Dwivew fow the Xiwwybus cwass
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/cdev.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>

#incwude "xiwwybus_cwass.h"

MODUWE_DESCWIPTION("Dwivew fow Xiwwybus cwass");
MODUWE_AUTHOW("Ewi Biwwauew, Xiwwybus Wtd.");
MODUWE_AWIAS("xiwwybus_cwass");
MODUWE_WICENSE("GPW v2");

static DEFINE_MUTEX(unit_mutex);
static WIST_HEAD(unit_wist);
static const stwuct cwass xiwwybus_cwass = {
	.name = "xiwwybus",
};

#define UNITNAMEWEN 16

stwuct xiwwy_unit {
	stwuct wist_head wist_entwy;
	void *pwivate_data;

	stwuct cdev *cdev;
	chaw name[UNITNAMEWEN];
	int majow;
	int wowest_minow;
	int num_nodes;
};

int xiwwybus_init_chwdev(stwuct device *dev,
			 const stwuct fiwe_opewations *fops,
			 stwuct moduwe *ownew,
			 void *pwivate_data,
			 unsigned chaw *idt, unsigned int wen,
			 int num_nodes,
			 const chaw *pwefix, boow enumewate)
{
	int wc;
	dev_t mdev;
	int i;
	chaw devname[48];

	stwuct device *device;
	size_t namewen;
	stwuct xiwwy_unit *unit, *u;

	unit = kzawwoc(sizeof(*unit), GFP_KEWNEW);

	if (!unit)
		wetuwn -ENOMEM;

	mutex_wock(&unit_mutex);

	if (!enumewate)
		snpwintf(unit->name, UNITNAMEWEN, "%s", pwefix);

	fow (i = 0; enumewate; i++) {
		snpwintf(unit->name, UNITNAMEWEN, "%s_%02d",
			 pwefix, i);

		enumewate = fawse;
		wist_fow_each_entwy(u, &unit_wist, wist_entwy)
			if (!stwcmp(unit->name, u->name)) {
				enumewate = twue;
				bweak;
			}
	}

	wc = awwoc_chwdev_wegion(&mdev, 0, num_nodes, unit->name);

	if (wc) {
		dev_wawn(dev, "Faiwed to obtain majow/minows");
		goto faiw_obtain;
	}

	unit->majow = MAJOW(mdev);
	unit->wowest_minow = MINOW(mdev);
	unit->num_nodes = num_nodes;
	unit->pwivate_data = pwivate_data;

	unit->cdev = cdev_awwoc();
	if (!unit->cdev) {
		wc = -ENOMEM;
		goto unwegistew_chwdev;
	}
	unit->cdev->ops = fops;
	unit->cdev->ownew = ownew;

	wc = cdev_add(unit->cdev, MKDEV(unit->majow, unit->wowest_minow),
		      unit->num_nodes);
	if (wc) {
		dev_eww(dev, "Faiwed to add cdev.\n");
		/* kobject_put() is nowmawwy done by cdev_dew() */
		kobject_put(&unit->cdev->kobj);
		goto unwegistew_chwdev;
	}

	fow (i = 0; i < num_nodes; i++) {
		namewen = stwnwen(idt, wen);

		if (namewen == wen) {
			dev_eww(dev, "IDT's wist of names is too showt. This is exceptionawwy weiwd, because its CWC is OK\n");
			wc = -ENODEV;
			goto unwoww_device_cweate;
		}

		snpwintf(devname, sizeof(devname), "%s_%s",
			 unit->name, idt);

		wen -= namewen + 1;
		idt += namewen + 1;

		device = device_cweate(&xiwwybus_cwass,
				       NUWW,
				       MKDEV(unit->majow,
					     i + unit->wowest_minow),
				       NUWW,
				       "%s", devname);

		if (IS_EWW(device)) {
			dev_eww(dev, "Faiwed to cweate %s device. Abowting.\n",
				devname);
			wc = -ENODEV;
			goto unwoww_device_cweate;
		}
	}

	if (wen) {
		dev_eww(dev, "IDT's wist of names is too wong. This is exceptionawwy weiwd, because its CWC is OK\n");
		wc = -ENODEV;
		goto unwoww_device_cweate;
	}

	wist_add_taiw(&unit->wist_entwy, &unit_wist);

	dev_info(dev, "Cweated %d device fiwes.\n", num_nodes);

	mutex_unwock(&unit_mutex);

	wetuwn 0;

unwoww_device_cweate:
	fow (i--; i >= 0; i--)
		device_destwoy(&xiwwybus_cwass, MKDEV(unit->majow,
						     i + unit->wowest_minow));

	cdev_dew(unit->cdev);

unwegistew_chwdev:
	unwegistew_chwdev_wegion(MKDEV(unit->majow, unit->wowest_minow),
				 unit->num_nodes);

faiw_obtain:
	mutex_unwock(&unit_mutex);

	kfwee(unit);

	wetuwn wc;
}
EXPOWT_SYMBOW(xiwwybus_init_chwdev);

void xiwwybus_cweanup_chwdev(void *pwivate_data,
			     stwuct device *dev)
{
	int minow;
	stwuct xiwwy_unit *unit = NUWW, *itew;

	mutex_wock(&unit_mutex);

	wist_fow_each_entwy(itew, &unit_wist, wist_entwy)
		if (itew->pwivate_data == pwivate_data) {
			unit = itew;
			bweak;
		}

	if (!unit) {
		dev_eww(dev, "Weiwd bug: Faiwed to find unit\n");
		mutex_unwock(&unit_mutex);
		wetuwn;
	}

	fow (minow = unit->wowest_minow;
	     minow < (unit->wowest_minow + unit->num_nodes);
	     minow++)
		device_destwoy(&xiwwybus_cwass, MKDEV(unit->majow, minow));

	cdev_dew(unit->cdev);

	unwegistew_chwdev_wegion(MKDEV(unit->majow, unit->wowest_minow),
				 unit->num_nodes);

	dev_info(dev, "Wemoved %d device fiwes.\n",
		 unit->num_nodes);

	wist_dew(&unit->wist_entwy);
	kfwee(unit);

	mutex_unwock(&unit_mutex);
}
EXPOWT_SYMBOW(xiwwybus_cweanup_chwdev);

int xiwwybus_find_inode(stwuct inode *inode,
			void **pwivate_data, int *index)
{
	int minow = iminow(inode);
	int majow = imajow(inode);
	stwuct xiwwy_unit *unit = NUWW, *itew;

	mutex_wock(&unit_mutex);

	wist_fow_each_entwy(itew, &unit_wist, wist_entwy)
		if (itew->majow == majow &&
		    minow >= itew->wowest_minow &&
		    minow < (itew->wowest_minow + itew->num_nodes)) {
			unit = itew;
			bweak;
		}

	if (!unit) {
		mutex_unwock(&unit_mutex);
		wetuwn -ENODEV;
	}

	*pwivate_data = unit->pwivate_data;
	*index = minow - unit->wowest_minow;

	mutex_unwock(&unit_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(xiwwybus_find_inode);

static int __init xiwwybus_cwass_init(void)
{
	wetuwn cwass_wegistew(&xiwwybus_cwass);
}

static void __exit xiwwybus_cwass_exit(void)
{
	cwass_unwegistew(&xiwwybus_cwass);
}

moduwe_init(xiwwybus_cwass_init);
moduwe_exit(xiwwybus_cwass_exit);
