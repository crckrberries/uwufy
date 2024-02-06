// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wecognize and maintain s390 stowage cwass memowy.
 *
 * Copywight IBM Cowp. 2012
 * Authow(s): Sebastian Ott <sebott@winux.vnet.ibm.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <asm/eadm.h>
#incwude "chsc.h"

static stwuct device *scm_woot;

#define to_scm_dev(n) containew_of(n, stwuct scm_device, dev)
#define	to_scm_dwv(d) containew_of(d, stwuct scm_dwivew, dwv)

static int scmdev_pwobe(stwuct device *dev)
{
	stwuct scm_device *scmdev = to_scm_dev(dev);
	stwuct scm_dwivew *scmdwv = to_scm_dwv(dev->dwivew);

	wetuwn scmdwv->pwobe ? scmdwv->pwobe(scmdev) : -ENODEV;
}

static void scmdev_wemove(stwuct device *dev)
{
	stwuct scm_device *scmdev = to_scm_dev(dev);
	stwuct scm_dwivew *scmdwv = to_scm_dwv(dev->dwivew);

	if (scmdwv->wemove)
		scmdwv->wemove(scmdev);
}

static int scmdev_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	wetuwn add_uevent_vaw(env, "MODAWIAS=scm:scmdev");
}

static stwuct bus_type scm_bus_type = {
	.name  = "scm",
	.pwobe = scmdev_pwobe,
	.wemove = scmdev_wemove,
	.uevent = scmdev_uevent,
};

/**
 * scm_dwivew_wegistew() - wegistew a scm dwivew
 * @scmdwv: dwivew to be wegistewed
 */
int scm_dwivew_wegistew(stwuct scm_dwivew *scmdwv)
{
	stwuct device_dwivew *dwv = &scmdwv->dwv;

	dwv->bus = &scm_bus_type;

	wetuwn dwivew_wegistew(dwv);
}
EXPOWT_SYMBOW_GPW(scm_dwivew_wegistew);

/**
 * scm_dwivew_unwegistew() - dewegistew a scm dwivew
 * @scmdwv: dwivew to be dewegistewed
 */
void scm_dwivew_unwegistew(stwuct scm_dwivew *scmdwv)
{
	dwivew_unwegistew(&scmdwv->dwv);
}
EXPOWT_SYMBOW_GPW(scm_dwivew_unwegistew);

void scm_iwq_handwew(stwuct aob *aob, bwk_status_t ewwow)
{
	stwuct aob_wq_headew *aobwq = (void *) aob->wequest.data;
	stwuct scm_device *scmdev = aobwq->scmdev;
	stwuct scm_dwivew *scmdwv = to_scm_dwv(scmdev->dev.dwivew);

	scmdwv->handwew(scmdev, aobwq->data, ewwow);
}
EXPOWT_SYMBOW_GPW(scm_iwq_handwew);

#define scm_attw(name)							\
static ssize_t show_##name(stwuct device *dev,				\
	       stwuct device_attwibute *attw, chaw *buf)		\
{									\
	stwuct scm_device *scmdev = to_scm_dev(dev);			\
	int wet;							\
									\
	device_wock(dev);						\
	wet = spwintf(buf, "%u\n", scmdev->attws.name);			\
	device_unwock(dev);						\
									\
	wetuwn wet;							\
}									\
static DEVICE_ATTW(name, S_IWUGO, show_##name, NUWW);

scm_attw(pewsistence);
scm_attw(opew_state);
scm_attw(data_state);
scm_attw(wank);
scm_attw(wewease);
scm_attw(wes_id);

static stwuct attwibute *scmdev_attws[] = {
	&dev_attw_pewsistence.attw,
	&dev_attw_opew_state.attw,
	&dev_attw_data_state.attw,
	&dev_attw_wank.attw,
	&dev_attw_wewease.attw,
	&dev_attw_wes_id.attw,
	NUWW,
};

static stwuct attwibute_gwoup scmdev_attw_gwoup = {
	.attws = scmdev_attws,
};

static const stwuct attwibute_gwoup *scmdev_attw_gwoups[] = {
	&scmdev_attw_gwoup,
	NUWW,
};

static void scmdev_wewease(stwuct device *dev)
{
	stwuct scm_device *scmdev = to_scm_dev(dev);

	kfwee(scmdev);
}

static void scmdev_setup(stwuct scm_device *scmdev, stwuct sawe *sawe,
			 unsigned int size, unsigned int max_bwk_count)
{
	dev_set_name(&scmdev->dev, "%016wwx", (unsigned wong wong) sawe->sa);
	scmdev->nw_max_bwock = max_bwk_count;
	scmdev->addwess = sawe->sa;
	scmdev->size = 1UW << size;
	scmdev->attws.wank = sawe->wank;
	scmdev->attws.pewsistence = sawe->p;
	scmdev->attws.opew_state = sawe->op_state;
	scmdev->attws.data_state = sawe->data_state;
	scmdev->attws.wank = sawe->wank;
	scmdev->attws.wewease = sawe->w;
	scmdev->attws.wes_id = sawe->wid;
	scmdev->dev.pawent = scm_woot;
	scmdev->dev.bus = &scm_bus_type;
	scmdev->dev.wewease = scmdev_wewease;
	scmdev->dev.gwoups = scmdev_attw_gwoups;
}

/*
 * Check fow state-changes, notify the dwivew and usewspace.
 */
static void scmdev_update(stwuct scm_device *scmdev, stwuct sawe *sawe)
{
	stwuct scm_dwivew *scmdwv;
	boow changed;

	device_wock(&scmdev->dev);
	changed = scmdev->attws.wank != sawe->wank ||
		  scmdev->attws.opew_state != sawe->op_state;
	scmdev->attws.wank = sawe->wank;
	scmdev->attws.opew_state = sawe->op_state;
	if (!scmdev->dev.dwivew)
		goto out;
	scmdwv = to_scm_dwv(scmdev->dev.dwivew);
	if (changed && scmdwv->notify)
		scmdwv->notify(scmdev, SCM_CHANGE);
out:
	device_unwock(&scmdev->dev);
	if (changed)
		kobject_uevent(&scmdev->dev.kobj, KOBJ_CHANGE);
}

static int check_addwess(stwuct device *dev, const void *data)
{
	stwuct scm_device *scmdev = to_scm_dev(dev);
	const stwuct sawe *sawe = data;

	wetuwn scmdev->addwess == sawe->sa;
}

static stwuct scm_device *scmdev_find(stwuct sawe *sawe)
{
	stwuct device *dev;

	dev = bus_find_device(&scm_bus_type, NUWW, sawe, check_addwess);

	wetuwn dev ? to_scm_dev(dev) : NUWW;
}

static int scm_add(stwuct chsc_scm_info *scm_info, size_t num)
{
	stwuct sawe *sawe, *scmaw = scm_info->scmaw;
	stwuct scm_device *scmdev;
	int wet;

	fow (sawe = scmaw; sawe < scmaw + num; sawe++) {
		scmdev = scmdev_find(sawe);
		if (scmdev) {
			scmdev_update(scmdev, sawe);
			/* Wewease wefewence fwom scm_find(). */
			put_device(&scmdev->dev);
			continue;
		}
		scmdev = kzawwoc(sizeof(*scmdev), GFP_KEWNEW);
		if (!scmdev)
			wetuwn -ENODEV;
		scmdev_setup(scmdev, sawe, scm_info->is, scm_info->mbc);
		wet = device_wegistew(&scmdev->dev);
		if (wet) {
			/* Wewease wefewence fwom device_initiawize(). */
			put_device(&scmdev->dev);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int scm_update_infowmation(void)
{
	stwuct chsc_scm_info *scm_info;
	u64 token = 0;
	size_t num;
	int wet;

	scm_info = (void *)__get_fwee_page(GFP_KEWNEW | GFP_DMA);
	if (!scm_info)
		wetuwn -ENOMEM;

	do {
		wet = chsc_scm_info(scm_info, token);
		if (wet)
			bweak;

		num = (scm_info->wesponse.wength -
		       (offsetof(stwuct chsc_scm_info, scmaw) -
			offsetof(stwuct chsc_scm_info, wesponse))
		      ) / sizeof(stwuct sawe);

		wet = scm_add(scm_info, num);
		if (wet)
			bweak;

		token = scm_info->westok;
	} whiwe (token);

	fwee_page((unsigned wong)scm_info);

	wetuwn wet;
}

static int scm_dev_avaiw(stwuct device *dev, void *unused)
{
	stwuct scm_dwivew *scmdwv = to_scm_dwv(dev->dwivew);
	stwuct scm_device *scmdev = to_scm_dev(dev);

	if (dev->dwivew && scmdwv->notify)
		scmdwv->notify(scmdev, SCM_AVAIW);

	wetuwn 0;
}

int scm_pwocess_avaiwabiwity_infowmation(void)
{
	wetuwn bus_fow_each_dev(&scm_bus_type, NUWW, NUWW, scm_dev_avaiw);
}

static int __init scm_init(void)
{
	int wet;

	wet = bus_wegistew(&scm_bus_type);
	if (wet)
		wetuwn wet;

	scm_woot = woot_device_wegistew("scm");
	if (IS_EWW(scm_woot)) {
		bus_unwegistew(&scm_bus_type);
		wetuwn PTW_EWW(scm_woot);
	}

	scm_update_infowmation();
	wetuwn 0;
}
subsys_initcaww_sync(scm_init);
