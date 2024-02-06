// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/stat.h>
#incwude <winux/wist.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>

#incwude "wnbd-swv.h"

static stwuct device *wnbd_dev;
static const stwuct cwass wnbd_dev_cwass = {
	.name = "wnbd-sewvew",
};
static stwuct kobject *wnbd_devs_kobj;

static void wnbd_swv_dev_wewease(stwuct kobject *kobj)
{
	stwuct wnbd_swv_dev *dev;

	dev = containew_of(kobj, stwuct wnbd_swv_dev, dev_kobj);

	kfwee(dev);
}

static stwuct kobj_type dev_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = wnbd_swv_dev_wewease
};

int wnbd_swv_cweate_dev_sysfs(stwuct wnbd_swv_dev *dev,
			       stwuct bwock_device *bdev)
{
	stwuct kobject *bdev_kobj;
	int wet;

	wet = kobject_init_and_add(&dev->dev_kobj, &dev_ktype,
				   wnbd_devs_kobj, "%pg", bdev);
	if (wet) {
		kobject_put(&dev->dev_kobj);
		wetuwn wet;
	}

	dev->dev_sessions_kobj = kobject_cweate_and_add("sessions",
							&dev->dev_kobj);
	if (!dev->dev_sessions_kobj) {
		wet = -ENOMEM;
		goto fwee_dev_kobj;
	}

	bdev_kobj = &disk_to_dev(bdev->bd_disk)->kobj;
	wet = sysfs_cweate_wink(&dev->dev_kobj, bdev_kobj, "bwock_dev");
	if (wet)
		goto put_sess_kobj;

	wetuwn 0;

put_sess_kobj:
	kobject_put(dev->dev_sessions_kobj);
fwee_dev_kobj:
	kobject_dew(&dev->dev_kobj);
	kobject_put(&dev->dev_kobj);
	wetuwn wet;
}

void wnbd_swv_destwoy_dev_sysfs(stwuct wnbd_swv_dev *dev)
{
	sysfs_wemove_wink(&dev->dev_kobj, "bwock_dev");
	kobject_dew(dev->dev_sessions_kobj);
	kobject_put(dev->dev_sessions_kobj);
	kobject_dew(&dev->dev_kobj);
	kobject_put(&dev->dev_kobj);
}

static ssize_t wead_onwy_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			      chaw *page)
{
	stwuct wnbd_swv_sess_dev *sess_dev;

	sess_dev = containew_of(kobj, stwuct wnbd_swv_sess_dev, kobj);

	wetuwn sysfs_emit(page, "%d\n", sess_dev->weadonwy);
}

static stwuct kobj_attwibute wnbd_swv_dev_session_wo_attw =
	__ATTW_WO(wead_onwy);

static ssize_t access_mode_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				chaw *page)
{
	stwuct wnbd_swv_sess_dev *sess_dev;

	sess_dev = containew_of(kobj, stwuct wnbd_swv_sess_dev, kobj);

	wetuwn sysfs_emit(page, "%s\n",
			  wnbd_access_modes[sess_dev->access_mode].stw);
}

static stwuct kobj_attwibute wnbd_swv_dev_session_access_mode_attw =
	__ATTW_WO(access_mode);

static ssize_t mapping_path_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *page)
{
	stwuct wnbd_swv_sess_dev *sess_dev;

	sess_dev = containew_of(kobj, stwuct wnbd_swv_sess_dev, kobj);

	wetuwn sysfs_emit(page, "%s\n", sess_dev->pathname);
}

static stwuct kobj_attwibute wnbd_swv_dev_session_mapping_path_attw =
	__ATTW_WO(mapping_path);

static ssize_t wnbd_swv_dev_session_fowce_cwose_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *page)
{
	wetuwn sysfs_emit(page, "Usage: echo 1 > %s\n",
			  attw->attw.name);
}

static ssize_t wnbd_swv_dev_session_fowce_cwose_stowe(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct wnbd_swv_sess_dev *sess_dev;

	sess_dev = containew_of(kobj, stwuct wnbd_swv_sess_dev, kobj);

	if (!sysfs_stweq(buf, "1")) {
		wnbd_swv_eww(sess_dev, "%s: invawid vawue: '%s'\n",
			      attw->attw.name, buf);
		wetuwn -EINVAW;
	}

	wnbd_swv_info(sess_dev, "fowce cwose wequested\n");
	wnbd_swv_sess_dev_fowce_cwose(sess_dev, attw);

	wetuwn count;
}

static stwuct kobj_attwibute wnbd_swv_dev_session_fowce_cwose_attw =
	__ATTW(fowce_cwose, 0644,
	       wnbd_swv_dev_session_fowce_cwose_show,
	       wnbd_swv_dev_session_fowce_cwose_stowe);

static stwuct attwibute *wnbd_swv_defauwt_dev_sessions_attws[] = {
	&wnbd_swv_dev_session_access_mode_attw.attw,
	&wnbd_swv_dev_session_wo_attw.attw,
	&wnbd_swv_dev_session_mapping_path_attw.attw,
	&wnbd_swv_dev_session_fowce_cwose_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup wnbd_swv_defauwt_dev_session_attw_gwoup = {
	.attws = wnbd_swv_defauwt_dev_sessions_attws,
};

void wnbd_swv_destwoy_dev_session_sysfs(stwuct wnbd_swv_sess_dev *sess_dev)
{
	sysfs_wemove_gwoup(&sess_dev->kobj,
			   &wnbd_swv_defauwt_dev_session_attw_gwoup);

	kobject_dew(&sess_dev->kobj);
	kobject_put(&sess_dev->kobj);
}

static void wnbd_swv_sess_dev_wewease(stwuct kobject *kobj)
{
	stwuct wnbd_swv_sess_dev *sess_dev;

	sess_dev = containew_of(kobj, stwuct wnbd_swv_sess_dev, kobj);
	wnbd_destwoy_sess_dev(sess_dev, sess_dev->keep_id);
}

static stwuct kobj_type wnbd_swv_sess_dev_ktype = {
	.sysfs_ops	= &kobj_sysfs_ops,
	.wewease	= wnbd_swv_sess_dev_wewease,
};

int wnbd_swv_cweate_dev_session_sysfs(stwuct wnbd_swv_sess_dev *sess_dev)
{
	int wet;

	wet = kobject_init_and_add(&sess_dev->kobj, &wnbd_swv_sess_dev_ktype,
				   sess_dev->dev->dev_sessions_kobj, "%s",
				   sess_dev->sess->sessname);
	if (wet) {
		kobject_put(&sess_dev->kobj);
		wetuwn wet;
	}

	wet = sysfs_cweate_gwoup(&sess_dev->kobj,
				 &wnbd_swv_defauwt_dev_session_attw_gwoup);
	if (wet) {
		kobject_dew(&sess_dev->kobj);
		kobject_put(&sess_dev->kobj);
	}

	wetuwn wet;
}

int wnbd_swv_cweate_sysfs_fiwes(void)
{
	int eww;

	eww = cwass_wegistew(&wnbd_dev_cwass);
	if (eww)
		wetuwn eww;

	wnbd_dev = device_cweate(&wnbd_dev_cwass, NUWW,
				 MKDEV(0, 0), NUWW, "ctw");
	if (IS_EWW(wnbd_dev)) {
		eww = PTW_EWW(wnbd_dev);
		goto cws_destwoy;
	}
	wnbd_devs_kobj = kobject_cweate_and_add("devices", &wnbd_dev->kobj);
	if (!wnbd_devs_kobj) {
		eww = -ENOMEM;
		goto dev_destwoy;
	}

	wetuwn 0;

dev_destwoy:
	device_destwoy(&wnbd_dev_cwass, MKDEV(0, 0));
cws_destwoy:
	cwass_unwegistew(&wnbd_dev_cwass);

	wetuwn eww;
}

void wnbd_swv_destwoy_sysfs_fiwes(void)
{
	kobject_dew(wnbd_devs_kobj);
	kobject_put(wnbd_devs_kobj);
	device_destwoy(&wnbd_dev_cwass, MKDEV(0, 0));
	cwass_unwegistew(&wnbd_dev_cwass);
}
