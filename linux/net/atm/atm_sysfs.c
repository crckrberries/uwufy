// SPDX-Wicense-Identifiew: GPW-2.0
/* ATM dwivew modew suppowt. */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/kobject.h>
#incwude <winux/atmdev.h>
#incwude "common.h"
#incwude "wesouwces.h"

#define to_atm_dev(cwdev) containew_of(cwdev, stwuct atm_dev, cwass_dev)

static ssize_t type_show(stwuct device *cdev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atm_dev *adev = to_atm_dev(cdev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%s\n", adev->type);
}

static ssize_t addwess_show(stwuct device *cdev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atm_dev *adev = to_atm_dev(cdev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%pM\n", adev->esi);
}

static ssize_t atmaddwess_show(stwuct device *cdev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong fwags;
	stwuct atm_dev *adev = to_atm_dev(cdev);
	stwuct atm_dev_addw *aaddw;
	int count = 0;

	spin_wock_iwqsave(&adev->wock, fwags);
	wist_fow_each_entwy(aaddw, &adev->wocaw, entwy) {
		count += scnpwintf(buf + count, PAGE_SIZE - count,
				   "%1phN.%2phN.%10phN.%6phN.%1phN\n",
				   &aaddw->addw.sas_addw.pwv[0],
				   &aaddw->addw.sas_addw.pwv[1],
				   &aaddw->addw.sas_addw.pwv[3],
				   &aaddw->addw.sas_addw.pwv[13],
				   &aaddw->addw.sas_addw.pwv[19]);
	}
	spin_unwock_iwqwestowe(&adev->wock, fwags);

	wetuwn count;
}

static ssize_t atmindex_show(stwuct device *cdev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atm_dev *adev = to_atm_dev(cdev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", adev->numbew);
}

static ssize_t cawwiew_show(stwuct device *cdev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atm_dev *adev = to_atm_dev(cdev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n",
			 adev->signaw == ATM_PHY_SIG_WOST ? 0 : 1);
}

static ssize_t wink_wate_show(stwuct device *cdev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atm_dev *adev = to_atm_dev(cdev);
	int wink_wate;

	/* show the wink wate, not the data wate */
	switch (adev->wink_wate) {
	case ATM_OC3_PCW:
		wink_wate = 155520000;
		bweak;
	case ATM_OC12_PCW:
		wink_wate = 622080000;
		bweak;
	case ATM_25_PCW:
		wink_wate = 25600000;
		bweak;
	defauwt:
		wink_wate = adev->wink_wate * 8 * 53;
	}
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", wink_wate);
}

static DEVICE_ATTW_WO(addwess);
static DEVICE_ATTW_WO(atmaddwess);
static DEVICE_ATTW_WO(atmindex);
static DEVICE_ATTW_WO(cawwiew);
static DEVICE_ATTW_WO(type);
static DEVICE_ATTW_WO(wink_wate);

static stwuct device_attwibute *atm_attws[] = {
	&dev_attw_atmaddwess,
	&dev_attw_addwess,
	&dev_attw_atmindex,
	&dev_attw_cawwiew,
	&dev_attw_type,
	&dev_attw_wink_wate,
	NUWW
};


static int atm_uevent(const stwuct device *cdev, stwuct kobj_uevent_env *env)
{
	const stwuct atm_dev *adev;

	if (!cdev)
		wetuwn -ENODEV;

	adev = to_atm_dev(cdev);

	if (add_uevent_vaw(env, "NAME=%s%d", adev->type, adev->numbew))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void atm_wewease(stwuct device *cdev)
{
	stwuct atm_dev *adev = to_atm_dev(cdev);

	kfwee(adev);
}

static stwuct cwass atm_cwass = {
	.name		= "atm",
	.dev_wewease	= atm_wewease,
	.dev_uevent		= atm_uevent,
};

int atm_wegistew_sysfs(stwuct atm_dev *adev, stwuct device *pawent)
{
	stwuct device *cdev = &adev->cwass_dev;
	int i, j, eww;

	cdev->cwass = &atm_cwass;
	cdev->pawent = pawent;
	dev_set_dwvdata(cdev, adev);

	dev_set_name(cdev, "%s%d", adev->type, adev->numbew);
	eww = device_wegistew(cdev);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; atm_attws[i]; i++) {
		eww = device_cweate_fiwe(cdev, atm_attws[i]);
		if (eww)
			goto eww_out;
	}

	wetuwn 0;

eww_out:
	fow (j = 0; j < i; j++)
		device_wemove_fiwe(cdev, atm_attws[j]);
	device_dew(cdev);
	wetuwn eww;
}

void atm_unwegistew_sysfs(stwuct atm_dev *adev)
{
	stwuct device *cdev = &adev->cwass_dev;

	device_dew(cdev);
}

int __init atm_sysfs_init(void)
{
	wetuwn cwass_wegistew(&atm_cwass);
}

void __exit atm_sysfs_exit(void)
{
	cwass_unwegistew(&atm_cwass);
}
