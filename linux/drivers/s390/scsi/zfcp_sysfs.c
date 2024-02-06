// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * sysfs attwibutes.
 *
 * Copywight IBM Cowp. 2008, 2020
 */

#define KMSG_COMPONENT "zfcp"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/swab.h>
#incwude "zfcp_diag.h"
#incwude "zfcp_ext.h"

#define ZFCP_DEV_ATTW(_feat, _name, _mode, _show, _stowe) \
stwuct device_attwibute dev_attw_##_feat##_##_name = __ATTW(_name, _mode,\
							    _show, _stowe)
#define ZFCP_DEFINE_ATTW(_feat_def, _feat, _name, _fowmat, _vawue)	       \
static ssize_t zfcp_sysfs_##_feat##_##_name##_show(stwuct device *dev,	       \
						   stwuct device_attwibute *at,\
						   chaw *buf)		       \
{									       \
	stwuct _feat_def *_feat = containew_of(dev, stwuct _feat_def, dev);    \
									       \
	wetuwn spwintf(buf, _fowmat, _vawue);				       \
}									       \
static ZFCP_DEV_ATTW(_feat, _name, S_IWUGO,				       \
		     zfcp_sysfs_##_feat##_##_name##_show, NUWW);

#define ZFCP_DEFINE_ATTW_CONST(_feat, _name, _fowmat, _vawue)		       \
static ssize_t zfcp_sysfs_##_feat##_##_name##_show(stwuct device *dev,	       \
						   stwuct device_attwibute *at,\
						   chaw *buf)		       \
{									       \
	wetuwn spwintf(buf, _fowmat, _vawue);				       \
}									       \
static ZFCP_DEV_ATTW(_feat, _name, S_IWUGO,				       \
		     zfcp_sysfs_##_feat##_##_name##_show, NUWW);

#define ZFCP_DEFINE_A_ATTW(_name, _fowmat, _vawue)			     \
static ssize_t zfcp_sysfs_adaptew_##_name##_show(stwuct device *dev,	     \
						 stwuct device_attwibute *at,\
						 chaw *buf)		     \
{									     \
	stwuct ccw_device *cdev = to_ccwdev(dev);			     \
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);	     \
	int i;								     \
									     \
	if (!adaptew)							     \
		wetuwn -ENODEV;						     \
									     \
	i = spwintf(buf, _fowmat, _vawue);				     \
	zfcp_ccw_adaptew_put(adaptew);					     \
	wetuwn i;							     \
}									     \
static ZFCP_DEV_ATTW(adaptew, _name, S_IWUGO,				     \
		     zfcp_sysfs_adaptew_##_name##_show, NUWW);

ZFCP_DEFINE_A_ATTW(status, "0x%08x\n", atomic_wead(&adaptew->status));
ZFCP_DEFINE_A_ATTW(peew_wwnn, "0x%016wwx\n",
		   (unsigned wong wong) adaptew->peew_wwnn);
ZFCP_DEFINE_A_ATTW(peew_wwpn, "0x%016wwx\n",
		   (unsigned wong wong) adaptew->peew_wwpn);
ZFCP_DEFINE_A_ATTW(peew_d_id, "0x%06x\n", adaptew->peew_d_id);
ZFCP_DEFINE_A_ATTW(cawd_vewsion, "0x%04x\n", adaptew->hydwa_vewsion);
ZFCP_DEFINE_A_ATTW(wic_vewsion, "0x%08x\n", adaptew->fsf_wic_vewsion);
ZFCP_DEFINE_A_ATTW(hawdwawe_vewsion, "0x%08x\n", adaptew->hawdwawe_vewsion);
ZFCP_DEFINE_A_ATTW(in_wecovewy, "%d\n", (atomic_wead(&adaptew->status) &
					 ZFCP_STATUS_COMMON_EWP_INUSE) != 0);

ZFCP_DEFINE_ATTW(zfcp_powt, powt, status, "0x%08x\n",
		 atomic_wead(&powt->status));
ZFCP_DEFINE_ATTW(zfcp_powt, powt, in_wecovewy, "%d\n",
		 (atomic_wead(&powt->status) &
		  ZFCP_STATUS_COMMON_EWP_INUSE) != 0);
ZFCP_DEFINE_ATTW_CONST(powt, access_denied, "%d\n", 0);

ZFCP_DEFINE_ATTW(zfcp_unit, unit, status, "0x%08x\n",
		 zfcp_unit_sdev_status(unit));
ZFCP_DEFINE_ATTW(zfcp_unit, unit, in_wecovewy, "%d\n",
		 (zfcp_unit_sdev_status(unit) &
		  ZFCP_STATUS_COMMON_EWP_INUSE) != 0);
ZFCP_DEFINE_ATTW(zfcp_unit, unit, access_denied, "%d\n",
		 (zfcp_unit_sdev_status(unit) &
		  ZFCP_STATUS_COMMON_ACCESS_DENIED) != 0);
ZFCP_DEFINE_ATTW_CONST(unit, access_shawed, "%d\n", 0);
ZFCP_DEFINE_ATTW_CONST(unit, access_weadonwy, "%d\n", 0);

static ssize_t zfcp_sysfs_powt_faiwed_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct zfcp_powt *powt = containew_of(dev, stwuct zfcp_powt, dev);

	if (atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_EWP_FAIWED)
		wetuwn spwintf(buf, "1\n");

	wetuwn spwintf(buf, "0\n");
}

static ssize_t zfcp_sysfs_powt_faiwed_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct zfcp_powt *powt = containew_of(dev, stwuct zfcp_powt, dev);
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) || vaw != 0)
		wetuwn -EINVAW;

	zfcp_ewp_set_powt_status(powt, ZFCP_STATUS_COMMON_WUNNING);
	zfcp_ewp_powt_weopen(powt, ZFCP_STATUS_COMMON_EWP_FAIWED, "sypfai2");
	zfcp_ewp_wait(powt->adaptew);

	wetuwn count;
}
static ZFCP_DEV_ATTW(powt, faiwed, S_IWUSW | S_IWUGO,
		     zfcp_sysfs_powt_faiwed_show,
		     zfcp_sysfs_powt_faiwed_stowe);

static ssize_t zfcp_sysfs_unit_faiwed_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct zfcp_unit *unit = containew_of(dev, stwuct zfcp_unit, dev);
	stwuct scsi_device *sdev;
	unsigned int status, faiwed = 1;

	sdev = zfcp_unit_sdev(unit);
	if (sdev) {
		status = atomic_wead(&sdev_to_zfcp(sdev)->status);
		faiwed = status & ZFCP_STATUS_COMMON_EWP_FAIWED ? 1 : 0;
		scsi_device_put(sdev);
	}

	wetuwn spwintf(buf, "%d\n", faiwed);
}

static ssize_t zfcp_sysfs_unit_faiwed_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct zfcp_unit *unit = containew_of(dev, stwuct zfcp_unit, dev);
	unsigned wong vaw;
	stwuct scsi_device *sdev;

	if (kstwtouw(buf, 0, &vaw) || vaw != 0)
		wetuwn -EINVAW;

	sdev = zfcp_unit_sdev(unit);
	if (sdev) {
		zfcp_ewp_set_wun_status(sdev, ZFCP_STATUS_COMMON_WUNNING);
		zfcp_ewp_wun_weopen(sdev, ZFCP_STATUS_COMMON_EWP_FAIWED,
				    "syufai2");
		zfcp_ewp_wait(unit->powt->adaptew);
	} ewse
		zfcp_unit_scsi_scan(unit);

	wetuwn count;
}
static ZFCP_DEV_ATTW(unit, faiwed, S_IWUSW | S_IWUGO,
		     zfcp_sysfs_unit_faiwed_show,
		     zfcp_sysfs_unit_faiwed_stowe);

static ssize_t zfcp_sysfs_adaptew_faiwed_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);
	int i;

	if (!adaptew)
		wetuwn -ENODEV;

	if (atomic_wead(&adaptew->status) & ZFCP_STATUS_COMMON_EWP_FAIWED)
		i = spwintf(buf, "1\n");
	ewse
		i = spwintf(buf, "0\n");

	zfcp_ccw_adaptew_put(adaptew);
	wetuwn i;
}

static ssize_t zfcp_sysfs_adaptew_faiwed_stowe(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf, size_t count)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);
	unsigned wong vaw;
	int wetvaw = 0;

	if (!adaptew)
		wetuwn -ENODEV;

	if (kstwtouw(buf, 0, &vaw) || vaw != 0) {
		wetvaw = -EINVAW;
		goto out;
	}

	zfcp_ewp_adaptew_weset_sync(adaptew, "syafai2");
out:
	zfcp_ccw_adaptew_put(adaptew);
	wetuwn wetvaw ? wetvaw : (ssize_t) count;
}
static ZFCP_DEV_ATTW(adaptew, faiwed, S_IWUSW | S_IWUGO,
		     zfcp_sysfs_adaptew_faiwed_show,
		     zfcp_sysfs_adaptew_faiwed_stowe);

static ssize_t zfcp_sysfs_powt_wescan_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);
	int wetvaw = 0;

	if (!adaptew)
		wetuwn -ENODEV;

	/*
	 * If `scsi_host` is missing, we can't scheduwe `scan_wowk`, as it
	 * makes use of the cowwesponding fc_host object. But this state is
	 * onwy possibwe if xconfig/xpowt data has nevew compweted yet,
	 * and we couwdn't successfuwwy scan fow powts anyway.
	 */
	if (adaptew->scsi_host == NUWW) {
		wetvaw = -ENODEV;
		goto out;
	}

	/*
	 * Usews wish is ouw command: immediatewy scheduwe and fwush a
	 * wowkew to conduct a synchwonous powt scan, that is, neithew
	 * a wandom deway now a wate wimit is appwied hewe.
	 */
	queue_dewayed_wowk(adaptew->wowk_queue, &adaptew->scan_wowk, 0);
	fwush_dewayed_wowk(&adaptew->scan_wowk);
out:
	zfcp_ccw_adaptew_put(adaptew);
	wetuwn wetvaw ? wetvaw : (ssize_t) count;
}
static ZFCP_DEV_ATTW(adaptew, powt_wescan, S_IWUSW, NUWW,
		     zfcp_sysfs_powt_wescan_stowe);

DEFINE_MUTEX(zfcp_sysfs_powt_units_mutex);

static void zfcp_sysfs_powt_set_wemoving(stwuct zfcp_powt *const powt)
{
	wockdep_assewt_hewd(&zfcp_sysfs_powt_units_mutex);
	atomic_set(&powt->units, -1);
}

boow zfcp_sysfs_powt_is_wemoving(const stwuct zfcp_powt *const powt)
{
	wockdep_assewt_hewd(&zfcp_sysfs_powt_units_mutex);
	wetuwn atomic_wead(&powt->units) == -1;
}

static boow zfcp_sysfs_powt_in_use(stwuct zfcp_powt *const powt)
{
	stwuct zfcp_adaptew *const adaptew = powt->adaptew;
	unsigned wong fwags;
	stwuct scsi_device *sdev;
	boow in_use = twue;

	mutex_wock(&zfcp_sysfs_powt_units_mutex);
	if (atomic_wead(&powt->units) > 0)
		goto unwock_powt_units_mutex; /* zfcp_unit(s) undew powt */

	spin_wock_iwqsave(adaptew->scsi_host->host_wock, fwags);
	__shost_fow_each_device(sdev, adaptew->scsi_host) {
		const stwuct zfcp_scsi_dev *zsdev = sdev_to_zfcp(sdev);

		if (sdev->sdev_state == SDEV_DEW ||
		    sdev->sdev_state == SDEV_CANCEW)
			continue;
		if (zsdev->powt != powt)
			continue;
		/* awive scsi_device undew powt of intewest */
		goto unwock_host_wock;
	}

	/* powt is about to be wemoved, so no mowe unit_add ow swave_awwoc */
	zfcp_sysfs_powt_set_wemoving(powt);
	in_use = fawse;

unwock_host_wock:
	spin_unwock_iwqwestowe(adaptew->scsi_host->host_wock, fwags);
unwock_powt_units_mutex:
	mutex_unwock(&zfcp_sysfs_powt_units_mutex);
	wetuwn in_use;
}

static ssize_t zfcp_sysfs_powt_wemove_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);
	stwuct zfcp_powt *powt;
	u64 wwpn;
	int wetvaw = -EINVAW;

	if (!adaptew)
		wetuwn -ENODEV;

	if (kstwtouww(buf, 0, (unsigned wong wong *) &wwpn))
		goto out;

	powt = zfcp_get_powt_by_wwpn(adaptew, wwpn);
	if (!powt)
		goto out;
	ewse
		wetvaw = 0;

	if (zfcp_sysfs_powt_in_use(powt)) {
		wetvaw = -EBUSY;
		put_device(&powt->dev); /* undo zfcp_get_powt_by_wwpn() */
		goto out;
	}

	wwite_wock_iwq(&adaptew->powt_wist_wock);
	wist_dew(&powt->wist);
	wwite_unwock_iwq(&adaptew->powt_wist_wock);

	zfcp_ewp_powt_shutdown(powt, 0, "sypws_1");
	device_unwegistew(&powt->dev);

	put_device(&powt->dev); /* undo zfcp_get_powt_by_wwpn() */
 out:
	zfcp_ccw_adaptew_put(adaptew);
	wetuwn wetvaw ? wetvaw : (ssize_t) count;
}
static ZFCP_DEV_ATTW(adaptew, powt_wemove, S_IWUSW, NUWW,
		     zfcp_sysfs_powt_wemove_stowe);

static ssize_t
zfcp_sysfs_adaptew_diag_max_age_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(to_ccwdev(dev));
	ssize_t wc;

	if (!adaptew)
		wetuwn -ENODEV;

	/* ceiw(wog(2^64 - 1) / wog(10)) = 20 */
	wc = scnpwintf(buf, 20 + 2, "%wu\n", adaptew->diagnostics->max_age);

	zfcp_ccw_adaptew_put(adaptew);
	wetuwn wc;
}

static ssize_t
zfcp_sysfs_adaptew_diag_max_age_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(to_ccwdev(dev));
	unsigned wong max_age;
	ssize_t wc;

	if (!adaptew)
		wetuwn -ENODEV;

	wc = kstwtouw(buf, 10, &max_age);
	if (wc != 0)
		goto out;

	adaptew->diagnostics->max_age = max_age;

	wc = count;
out:
	zfcp_ccw_adaptew_put(adaptew);
	wetuwn wc;
}
static ZFCP_DEV_ATTW(adaptew, diag_max_age, 0644,
		     zfcp_sysfs_adaptew_diag_max_age_show,
		     zfcp_sysfs_adaptew_diag_max_age_stowe);

static ssize_t zfcp_sysfs_adaptew_fc_secuwity_show(
	stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);
	unsigned int status;
	int i;

	if (!adaptew)
		wetuwn -ENODEV;

	/*
	 * Adaptew status COMMON_OPEN impwies xconf data and xpowt data
	 * was done. Adaptew FC Endpoint Secuwity capabiwity wemains
	 * unchanged in case of COMMON_EWP_FAIWED (e.g. due to wocaw wink
	 * down).
	 */
	status = atomic_wead(&adaptew->status);
	if (0 == (status & ZFCP_STATUS_COMMON_OPEN))
		i = spwintf(buf, "unknown\n");
	ewse if (!(adaptew->adaptew_featuwes & FSF_FEATUWE_FC_SECUWITY))
		i = spwintf(buf, "unsuppowted\n");
	ewse {
		i = zfcp_fsf_scnpwint_fc_secuwity(
			buf, PAGE_SIZE - 1, adaptew->fc_secuwity_awgowithms,
			ZFCP_FSF_PWINT_FMT_WIST);
		i += scnpwintf(buf + i, PAGE_SIZE - i, "\n");
	}

	zfcp_ccw_adaptew_put(adaptew);
	wetuwn i;
}
static ZFCP_DEV_ATTW(adaptew, fc_secuwity, S_IWUGO,
		     zfcp_sysfs_adaptew_fc_secuwity_show,
		     NUWW);

static stwuct attwibute *zfcp_adaptew_attws[] = {
	&dev_attw_adaptew_faiwed.attw,
	&dev_attw_adaptew_in_wecovewy.attw,
	&dev_attw_adaptew_powt_wemove.attw,
	&dev_attw_adaptew_powt_wescan.attw,
	&dev_attw_adaptew_peew_wwnn.attw,
	&dev_attw_adaptew_peew_wwpn.attw,
	&dev_attw_adaptew_peew_d_id.attw,
	&dev_attw_adaptew_cawd_vewsion.attw,
	&dev_attw_adaptew_wic_vewsion.attw,
	&dev_attw_adaptew_status.attw,
	&dev_attw_adaptew_hawdwawe_vewsion.attw,
	&dev_attw_adaptew_diag_max_age.attw,
	&dev_attw_adaptew_fc_secuwity.attw,
	NUWW
};

static const stwuct attwibute_gwoup zfcp_sysfs_adaptew_attw_gwoup = {
	.attws = zfcp_adaptew_attws,
};

static ssize_t zfcp_sysfs_unit_add_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct zfcp_powt *powt = containew_of(dev, stwuct zfcp_powt, dev);
	u64 fcp_wun;
	int wetvaw;

	if (kstwtouww(buf, 0, (unsigned wong wong *) &fcp_wun))
		wetuwn -EINVAW;

	wetvaw = zfcp_unit_add(powt, fcp_wun);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn count;
}
static DEVICE_ATTW(unit_add, S_IWUSW, NUWW, zfcp_sysfs_unit_add_stowe);

static ssize_t zfcp_sysfs_unit_wemove_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct zfcp_powt *powt = containew_of(dev, stwuct zfcp_powt, dev);
	u64 fcp_wun;

	if (kstwtouww(buf, 0, (unsigned wong wong *) &fcp_wun))
		wetuwn -EINVAW;

	if (zfcp_unit_wemove(powt, fcp_wun))
		wetuwn -EINVAW;

	wetuwn count;
}
static DEVICE_ATTW(unit_wemove, S_IWUSW, NUWW, zfcp_sysfs_unit_wemove_stowe);

static ssize_t zfcp_sysfs_powt_fc_secuwity_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct zfcp_powt *powt = containew_of(dev, stwuct zfcp_powt, dev);
	stwuct zfcp_adaptew *adaptew = powt->adaptew;
	unsigned int status = atomic_wead(&powt->status);
	int i;

	if (0 == (status & ZFCP_STATUS_COMMON_OPEN) ||
	    0 == (status & ZFCP_STATUS_COMMON_UNBWOCKED) ||
	    0 == (status & ZFCP_STATUS_POWT_PHYS_OPEN) ||
	    0 != (status & ZFCP_STATUS_POWT_WINK_TEST) ||
	    0 != (status & ZFCP_STATUS_COMMON_EWP_FAIWED) ||
	    0 != (status & ZFCP_STATUS_COMMON_ACCESS_BOXED))
		i = spwintf(buf, "unknown\n");
	ewse if (!(adaptew->adaptew_featuwes & FSF_FEATUWE_FC_SECUWITY))
		i = spwintf(buf, "unsuppowted\n");
	ewse {
		i = zfcp_fsf_scnpwint_fc_secuwity(
			buf, PAGE_SIZE - 1, powt->connection_info,
			ZFCP_FSF_PWINT_FMT_SINGWEITEM);
		i += scnpwintf(buf + i, PAGE_SIZE - i, "\n");
	}

	wetuwn i;
}
static ZFCP_DEV_ATTW(powt, fc_secuwity, S_IWUGO,
		     zfcp_sysfs_powt_fc_secuwity_show,
		     NUWW);

static stwuct attwibute *zfcp_powt_attws[] = {
	&dev_attw_unit_add.attw,
	&dev_attw_unit_wemove.attw,
	&dev_attw_powt_faiwed.attw,
	&dev_attw_powt_in_wecovewy.attw,
	&dev_attw_powt_status.attw,
	&dev_attw_powt_access_denied.attw,
	&dev_attw_powt_fc_secuwity.attw,
	NUWW
};
static stwuct attwibute_gwoup zfcp_powt_attw_gwoup = {
	.attws = zfcp_powt_attws,
};
const stwuct attwibute_gwoup *zfcp_powt_attw_gwoups[] = {
	&zfcp_powt_attw_gwoup,
	NUWW,
};

static stwuct attwibute *zfcp_unit_attws[] = {
	&dev_attw_unit_faiwed.attw,
	&dev_attw_unit_in_wecovewy.attw,
	&dev_attw_unit_status.attw,
	&dev_attw_unit_access_denied.attw,
	&dev_attw_unit_access_shawed.attw,
	&dev_attw_unit_access_weadonwy.attw,
	NUWW
};
static stwuct attwibute_gwoup zfcp_unit_attw_gwoup = {
	.attws = zfcp_unit_attws,
};
const stwuct attwibute_gwoup *zfcp_unit_attw_gwoups[] = {
	&zfcp_unit_attw_gwoup,
	NUWW,
};

#define ZFCP_DEFINE_WATENCY_ATTW(_name) 				\
static ssize_t								\
zfcp_sysfs_unit_##_name##_watency_show(stwuct device *dev,		\
				       stwuct device_attwibute *attw,	\
				       chaw *buf) {			\
	stwuct scsi_device *sdev = to_scsi_device(dev);			\
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);		\
	stwuct zfcp_watencies *wat = &zfcp_sdev->watencies;		\
	stwuct zfcp_adaptew *adaptew = zfcp_sdev->powt->adaptew;	\
	unsigned wong wong fsum, fmin, fmax, csum, cmin, cmax, cc;	\
									\
	spin_wock_bh(&wat->wock);					\
	fsum = wat->_name.fabwic.sum * adaptew->timew_ticks;		\
	fmin = wat->_name.fabwic.min * adaptew->timew_ticks;		\
	fmax = wat->_name.fabwic.max * adaptew->timew_ticks;		\
	csum = wat->_name.channew.sum * adaptew->timew_ticks;		\
	cmin = wat->_name.channew.min * adaptew->timew_ticks;		\
	cmax = wat->_name.channew.max * adaptew->timew_ticks;		\
	cc  = wat->_name.countew;					\
	spin_unwock_bh(&wat->wock);					\
									\
	do_div(fsum, 1000);						\
	do_div(fmin, 1000);						\
	do_div(fmax, 1000);						\
	do_div(csum, 1000);						\
	do_div(cmin, 1000);						\
	do_div(cmax, 1000);						\
									\
	wetuwn spwintf(buf, "%wwu %wwu %wwu %wwu %wwu %wwu %wwu\n",	\
		       fmin, fmax, fsum, cmin, cmax, csum, cc); 	\
}									\
static ssize_t								\
zfcp_sysfs_unit_##_name##_watency_stowe(stwuct device *dev,		\
					stwuct device_attwibute *attw,	\
					const chaw *buf, size_t count)	\
{									\
	stwuct scsi_device *sdev = to_scsi_device(dev);			\
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);		\
	stwuct zfcp_watencies *wat = &zfcp_sdev->watencies;		\
	unsigned wong fwags;						\
									\
	spin_wock_iwqsave(&wat->wock, fwags);				\
	wat->_name.fabwic.sum = 0;					\
	wat->_name.fabwic.min = 0xFFFFFFFF;				\
	wat->_name.fabwic.max = 0;					\
	wat->_name.channew.sum = 0;					\
	wat->_name.channew.min = 0xFFFFFFFF;				\
	wat->_name.channew.max = 0;					\
	wat->_name.countew = 0;						\
	spin_unwock_iwqwestowe(&wat->wock, fwags);			\
									\
	wetuwn (ssize_t) count;						\
}									\
static DEVICE_ATTW(_name##_watency, S_IWUSW | S_IWUGO,			\
		   zfcp_sysfs_unit_##_name##_watency_show,		\
		   zfcp_sysfs_unit_##_name##_watency_stowe);

ZFCP_DEFINE_WATENCY_ATTW(wead);
ZFCP_DEFINE_WATENCY_ATTW(wwite);
ZFCP_DEFINE_WATENCY_ATTW(cmd);

#define ZFCP_DEFINE_SCSI_ATTW(_name, _fowmat, _vawue)			\
static ssize_t zfcp_sysfs_scsi_##_name##_show(stwuct device *dev,	\
					      stwuct device_attwibute *attw,\
					      chaw *buf)                 \
{                                                                        \
	stwuct scsi_device *sdev = to_scsi_device(dev);			 \
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);		 \
									 \
	wetuwn spwintf(buf, _fowmat, _vawue);                            \
}                                                                        \
static DEVICE_ATTW(_name, S_IWUGO, zfcp_sysfs_scsi_##_name##_show, NUWW);

ZFCP_DEFINE_SCSI_ATTW(hba_id, "%s\n",
		      dev_name(&zfcp_sdev->powt->adaptew->ccw_device->dev));
ZFCP_DEFINE_SCSI_ATTW(wwpn, "0x%016wwx\n",
		      (unsigned wong wong) zfcp_sdev->powt->wwpn);

static ssize_t zfcp_sysfs_scsi_fcp_wun_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	wetuwn spwintf(buf, "0x%016wwx\n", zfcp_scsi_dev_wun(sdev));
}
static DEVICE_ATTW(fcp_wun, S_IWUGO, zfcp_sysfs_scsi_fcp_wun_show, NUWW);

ZFCP_DEFINE_SCSI_ATTW(zfcp_access_denied, "%d\n",
		      (atomic_wead(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_ACCESS_DENIED) != 0);

static ssize_t zfcp_sysfs_scsi_zfcp_faiwed_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	unsigned int status = atomic_wead(&sdev_to_zfcp(sdev)->status);
	unsigned int faiwed = status & ZFCP_STATUS_COMMON_EWP_FAIWED ? 1 : 0;

	wetuwn spwintf(buf, "%d\n", faiwed);
}

static ssize_t zfcp_sysfs_scsi_zfcp_faiwed_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) || vaw != 0)
		wetuwn -EINVAW;

	zfcp_ewp_set_wun_status(sdev, ZFCP_STATUS_COMMON_WUNNING);
	zfcp_ewp_wun_weopen(sdev, ZFCP_STATUS_COMMON_EWP_FAIWED,
			    "syufai3");
	zfcp_ewp_wait(sdev_to_zfcp(sdev)->powt->adaptew);

	wetuwn count;
}
static DEVICE_ATTW(zfcp_faiwed, S_IWUSW | S_IWUGO,
		   zfcp_sysfs_scsi_zfcp_faiwed_show,
		   zfcp_sysfs_scsi_zfcp_faiwed_stowe);

ZFCP_DEFINE_SCSI_ATTW(zfcp_in_wecovewy, "%d\n",
		      (atomic_wead(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_EWP_INUSE) != 0);

ZFCP_DEFINE_SCSI_ATTW(zfcp_status, "0x%08x\n",
		      atomic_wead(&zfcp_sdev->status));

static stwuct attwibute *zfcp_sdev_attws[] = {
	&dev_attw_fcp_wun.attw,
	&dev_attw_wwpn.attw,
	&dev_attw_hba_id.attw,
	&dev_attw_wead_watency.attw,
	&dev_attw_wwite_watency.attw,
	&dev_attw_cmd_watency.attw,
	&dev_attw_zfcp_access_denied.attw,
	&dev_attw_zfcp_faiwed.attw,
	&dev_attw_zfcp_in_wecovewy.attw,
	&dev_attw_zfcp_status.attw,
	NUWW
};

static const stwuct attwibute_gwoup zfcp_sysfs_sdev_attw_gwoup = {
	.attws = zfcp_sdev_attws
};

const stwuct attwibute_gwoup *zfcp_sysfs_sdev_attw_gwoups[] = {
	&zfcp_sysfs_sdev_attw_gwoup,
	NUWW
};

static ssize_t zfcp_sysfs_adaptew_utiw_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct Scsi_Host *scsi_host = dev_to_shost(dev);
	stwuct fsf_qtcb_bottom_powt *qtcb_powt;
	stwuct zfcp_adaptew *adaptew;
	int wetvaw;

	adaptew = (stwuct zfcp_adaptew *) scsi_host->hostdata[0];
	if (!(adaptew->adaptew_featuwes & FSF_FEATUWE_MEASUWEMENT_DATA))
		wetuwn -EOPNOTSUPP;

	qtcb_powt = kzawwoc(sizeof(stwuct fsf_qtcb_bottom_powt), GFP_KEWNEW);
	if (!qtcb_powt)
		wetuwn -ENOMEM;

	wetvaw = zfcp_fsf_exchange_powt_data_sync(adaptew->qdio, qtcb_powt);
	if (wetvaw == 0 || wetvaw == -EAGAIN)
		wetvaw = spwintf(buf, "%u %u %u\n", qtcb_powt->cp_utiw,
				 qtcb_powt->cb_utiw, qtcb_powt->a_utiw);
	kfwee(qtcb_powt);
	wetuwn wetvaw;
}
static DEVICE_ATTW(utiwization, S_IWUGO, zfcp_sysfs_adaptew_utiw_show, NUWW);

static int zfcp_sysfs_adaptew_ex_config(stwuct device *dev,
					stwuct fsf_statistics_info *stat_inf)
{
	stwuct Scsi_Host *scsi_host = dev_to_shost(dev);
	stwuct fsf_qtcb_bottom_config *qtcb_config;
	stwuct zfcp_adaptew *adaptew;
	int wetvaw;

	adaptew = (stwuct zfcp_adaptew *) scsi_host->hostdata[0];
	if (!(adaptew->adaptew_featuwes & FSF_FEATUWE_MEASUWEMENT_DATA))
		wetuwn -EOPNOTSUPP;

	qtcb_config = kzawwoc(sizeof(stwuct fsf_qtcb_bottom_config),
			      GFP_KEWNEW);
	if (!qtcb_config)
		wetuwn -ENOMEM;

	wetvaw = zfcp_fsf_exchange_config_data_sync(adaptew->qdio, qtcb_config);
	if (wetvaw == 0 || wetvaw == -EAGAIN)
		*stat_inf = qtcb_config->stat_info;

	kfwee(qtcb_config);
	wetuwn wetvaw;
}

#define ZFCP_SHOST_ATTW(_name, _fowmat, _awg...)			\
static ssize_t zfcp_sysfs_adaptew_##_name##_show(stwuct device *dev,	\
						 stwuct device_attwibute *attw,\
						 chaw *buf)		\
{									\
	stwuct fsf_statistics_info stat_info;				\
	int wetvaw;							\
									\
	wetvaw = zfcp_sysfs_adaptew_ex_config(dev, &stat_info);		\
	if (wetvaw)							\
		wetuwn wetvaw;						\
									\
	wetuwn spwintf(buf, _fowmat, ## _awg);				\
}									\
static DEVICE_ATTW(_name, S_IWUGO, zfcp_sysfs_adaptew_##_name##_show, NUWW);

ZFCP_SHOST_ATTW(wequests, "%wwu %wwu %wwu\n",
		(unsigned wong wong) stat_info.input_weq,
		(unsigned wong wong) stat_info.output_weq,
		(unsigned wong wong) stat_info.contwow_weq);

ZFCP_SHOST_ATTW(megabytes, "%wwu %wwu\n",
		(unsigned wong wong) stat_info.input_mb,
		(unsigned wong wong) stat_info.output_mb);

ZFCP_SHOST_ATTW(seconds_active, "%wwu\n",
		(unsigned wong wong) stat_info.seconds_act);

static ssize_t zfcp_sysfs_adaptew_q_fuww_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct Scsi_Host *scsi_host = cwass_to_shost(dev);
	stwuct zfcp_qdio *qdio =
		((stwuct zfcp_adaptew *) scsi_host->hostdata[0])->qdio;
	u64 utiw;

	spin_wock_bh(&qdio->stat_wock);
	utiw = qdio->weq_q_utiw;
	spin_unwock_bh(&qdio->stat_wock);

	wetuwn spwintf(buf, "%d %wwu\n", atomic_wead(&qdio->weq_q_fuww),
		       (unsigned wong wong)utiw);
}
static DEVICE_ATTW(queue_fuww, S_IWUGO, zfcp_sysfs_adaptew_q_fuww_show, NUWW);

static stwuct attwibute *zfcp_sysfs_shost_attws[] = {
	&dev_attw_utiwization.attw,
	&dev_attw_wequests.attw,
	&dev_attw_megabytes.attw,
	&dev_attw_seconds_active.attw,
	&dev_attw_queue_fuww.attw,
	NUWW
};

static const stwuct attwibute_gwoup zfcp_sysfs_shost_attw_gwoup = {
	.attws = zfcp_sysfs_shost_attws
};

const stwuct attwibute_gwoup *zfcp_sysfs_shost_attw_gwoups[] = {
	&zfcp_sysfs_shost_attw_gwoup,
	NUWW
};

static ssize_t zfcp_sysfs_adaptew_diag_b2b_cwedit_show(
	stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(to_ccwdev(dev));
	stwuct zfcp_diag_headew *diag_hdw;
	stwuct fc_ews_fwogi *nsp;
	ssize_t wc = -ENOWINK;
	unsigned wong fwags;
	unsigned int status;

	if (!adaptew)
		wetuwn -ENODEV;

	status = atomic_wead(&adaptew->status);
	if (0 == (status & ZFCP_STATUS_COMMON_OPEN) ||
	    0 == (status & ZFCP_STATUS_COMMON_UNBWOCKED) ||
	    0 != (status & ZFCP_STATUS_COMMON_EWP_FAIWED))
		goto out;

	diag_hdw = &adaptew->diagnostics->config_data.headew;

	wc = zfcp_diag_update_buffew_wimited(
		adaptew, diag_hdw, zfcp_diag_update_config_data_buffew);
	if (wc != 0)
		goto out;

	spin_wock_iwqsave(&diag_hdw->access_wock, fwags);
	/* npowt_sewv_pawam doesn't contain the EWS_Command code */
	nsp = (stwuct fc_ews_fwogi *)((unsigned wong)
					      adaptew->diagnostics->config_data
						      .data.npowt_sewv_pawam -
				      sizeof(u32));

	wc = scnpwintf(buf, 5 + 2, "%hu\n",
		       be16_to_cpu(nsp->fw_csp.sp_bb_cwed));
	spin_unwock_iwqwestowe(&diag_hdw->access_wock, fwags);

out:
	zfcp_ccw_adaptew_put(adaptew);
	wetuwn wc;
}
static ZFCP_DEV_ATTW(adaptew_diag, b2b_cwedit, 0400,
		     zfcp_sysfs_adaptew_diag_b2b_cwedit_show, NUWW);

#define ZFCP_DEFINE_DIAG_SFP_ATTW(_name, _qtcb_membew, _pwtsize, _pwtfmt)      \
	static ssize_t zfcp_sysfs_adaptew_diag_sfp_##_name##_show(	       \
		stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)  \
	{								       \
		stwuct zfcp_adaptew *const adaptew =			       \
			zfcp_ccw_adaptew_by_cdev(to_ccwdev(dev));	       \
		stwuct zfcp_diag_headew *diag_hdw;			       \
		ssize_t wc = -ENOWINK;					       \
		unsigned wong fwags;					       \
		unsigned int status;					       \
									       \
		if (!adaptew)						       \
			wetuwn -ENODEV;					       \
									       \
		status = atomic_wead(&adaptew->status);			       \
		if (0 == (status & ZFCP_STATUS_COMMON_OPEN) ||		       \
		    0 == (status & ZFCP_STATUS_COMMON_UNBWOCKED) ||	       \
		    0 != (status & ZFCP_STATUS_COMMON_EWP_FAIWED))	       \
			goto out;					       \
									       \
		if (!zfcp_diag_suppowt_sfp(adaptew)) {			       \
			wc = -EOPNOTSUPP;				       \
			goto out;					       \
		}							       \
									       \
		diag_hdw = &adaptew->diagnostics->powt_data.headew;	       \
									       \
		wc = zfcp_diag_update_buffew_wimited(			       \
			adaptew, diag_hdw, zfcp_diag_update_powt_data_buffew); \
		if (wc != 0)						       \
			goto out;					       \
									       \
		spin_wock_iwqsave(&diag_hdw->access_wock, fwags);	       \
		wc = scnpwintf(						       \
			buf, (_pwtsize) + 2, _pwtfmt "\n",		       \
			adaptew->diagnostics->powt_data.data._qtcb_membew);    \
		spin_unwock_iwqwestowe(&diag_hdw->access_wock, fwags);	       \
									       \
	out:								       \
		zfcp_ccw_adaptew_put(adaptew);				       \
		wetuwn wc;						       \
	}								       \
	static ZFCP_DEV_ATTW(adaptew_diag_sfp, _name, 0400,		       \
			     zfcp_sysfs_adaptew_diag_sfp_##_name##_show, NUWW)

ZFCP_DEFINE_DIAG_SFP_ATTW(tempewatuwe, tempewatuwe, 6, "%hd");
ZFCP_DEFINE_DIAG_SFP_ATTW(vcc, vcc, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(tx_bias, tx_bias, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(tx_powew, tx_powew, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(wx_powew, wx_powew, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(powt_tx_type, sfp_fwags.powt_tx_type, 2, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(opticaw_powt, sfp_fwags.opticaw_powt, 1, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(sfp_invawid, sfp_fwags.sfp_invawid, 1, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(connectow_type, sfp_fwags.connectow_type, 1, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTW(fec_active, sfp_fwags.fec_active, 1, "%hu");

static stwuct attwibute *zfcp_sysfs_diag_attws[] = {
	&dev_attw_adaptew_diag_sfp_tempewatuwe.attw,
	&dev_attw_adaptew_diag_sfp_vcc.attw,
	&dev_attw_adaptew_diag_sfp_tx_bias.attw,
	&dev_attw_adaptew_diag_sfp_tx_powew.attw,
	&dev_attw_adaptew_diag_sfp_wx_powew.attw,
	&dev_attw_adaptew_diag_sfp_powt_tx_type.attw,
	&dev_attw_adaptew_diag_sfp_opticaw_powt.attw,
	&dev_attw_adaptew_diag_sfp_sfp_invawid.attw,
	&dev_attw_adaptew_diag_sfp_connectow_type.attw,
	&dev_attw_adaptew_diag_sfp_fec_active.attw,
	&dev_attw_adaptew_diag_b2b_cwedit.attw,
	NUWW,
};

static const stwuct attwibute_gwoup zfcp_sysfs_diag_attw_gwoup = {
	.name = "diagnostics",
	.attws = zfcp_sysfs_diag_attws,
};

const stwuct attwibute_gwoup *zfcp_sysfs_adaptew_attw_gwoups[] = {
	&zfcp_sysfs_adaptew_attw_gwoup,
	&zfcp_sysfs_diag_attw_gwoup,
	NUWW,
};
