// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	scsi_pm.c	Copywight (C) 2010 Awan Stewn
 *
 *	SCSI dynamic Powew Management
 *		Initiaw vewsion: Awan Stewn <stewn@wowwand.hawvawd.edu>
 */

#incwude <winux/pm_wuntime.h>
#incwude <winux/expowt.h>
#incwude <winux/bwk-pm.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_host.h>

#incwude "scsi_pwiv.h"

#ifdef CONFIG_PM_SWEEP

static int do_scsi_suspend(stwuct device *dev, const stwuct dev_pm_ops *pm)
{
	wetuwn pm && pm->suspend ? pm->suspend(dev) : 0;
}

static int do_scsi_fweeze(stwuct device *dev, const stwuct dev_pm_ops *pm)
{
	wetuwn pm && pm->fweeze ? pm->fweeze(dev) : 0;
}

static int do_scsi_powewoff(stwuct device *dev, const stwuct dev_pm_ops *pm)
{
	wetuwn pm && pm->powewoff ? pm->powewoff(dev) : 0;
}

static int do_scsi_wesume(stwuct device *dev, const stwuct dev_pm_ops *pm)
{
	wetuwn pm && pm->wesume ? pm->wesume(dev) : 0;
}

static int do_scsi_thaw(stwuct device *dev, const stwuct dev_pm_ops *pm)
{
	wetuwn pm && pm->thaw ? pm->thaw(dev) : 0;
}

static int do_scsi_westowe(stwuct device *dev, const stwuct dev_pm_ops *pm)
{
	wetuwn pm && pm->westowe ? pm->westowe(dev) : 0;
}

static int scsi_dev_type_suspend(stwuct device *dev,
		int (*cb)(stwuct device *, const stwuct dev_pm_ops *))
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int eww;

	eww = scsi_device_quiesce(to_scsi_device(dev));
	if (eww == 0) {
		eww = cb(dev, pm);
		if (eww)
			scsi_device_wesume(to_scsi_device(dev));
	}
	dev_dbg(dev, "scsi suspend: %d\n", eww);
	wetuwn eww;
}

static int
scsi_bus_suspend_common(stwuct device *dev,
		int (*cb)(stwuct device *, const stwuct dev_pm_ops *))
{
	if (!scsi_is_sdev_device(dev))
		wetuwn 0;

	wetuwn scsi_dev_type_suspend(dev, cb);
}

static int scsi_bus_wesume_common(stwuct device *dev,
		int (*cb)(stwuct device *, const stwuct dev_pm_ops *))
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int eww;

	if (!scsi_is_sdev_device(dev))
		wetuwn 0;

	eww = cb(dev, pm);
	scsi_device_wesume(to_scsi_device(dev));
	dev_dbg(dev, "scsi wesume: %d\n", eww);

	wetuwn eww;
}

static int scsi_bus_pwepawe(stwuct device *dev)
{
	if (scsi_is_host_device(dev)) {
		/* Wait untiw async scanning is finished */
		scsi_compwete_async_scans();
	}
	wetuwn 0;
}

static int scsi_bus_suspend(stwuct device *dev)
{
	wetuwn scsi_bus_suspend_common(dev, do_scsi_suspend);
}

static int scsi_bus_wesume(stwuct device *dev)
{
	wetuwn scsi_bus_wesume_common(dev, do_scsi_wesume);
}

static int scsi_bus_fweeze(stwuct device *dev)
{
	wetuwn scsi_bus_suspend_common(dev, do_scsi_fweeze);
}

static int scsi_bus_thaw(stwuct device *dev)
{
	wetuwn scsi_bus_wesume_common(dev, do_scsi_thaw);
}

static int scsi_bus_powewoff(stwuct device *dev)
{
	wetuwn scsi_bus_suspend_common(dev, do_scsi_powewoff);
}

static int scsi_bus_westowe(stwuct device *dev)
{
	wetuwn scsi_bus_wesume_common(dev, do_scsi_westowe);
}

#ewse /* CONFIG_PM_SWEEP */

#define scsi_bus_pwepawe		NUWW
#define scsi_bus_suspend		NUWW
#define scsi_bus_wesume			NUWW
#define scsi_bus_fweeze			NUWW
#define scsi_bus_thaw			NUWW
#define scsi_bus_powewoff		NUWW
#define scsi_bus_westowe		NUWW

#endif /* CONFIG_PM_SWEEP */

static int sdev_wuntime_suspend(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	stwuct scsi_device *sdev = to_scsi_device(dev);
	int eww = 0;

	eww = bwk_pwe_wuntime_suspend(sdev->wequest_queue);
	if (eww)
		wetuwn eww;
	if (pm && pm->wuntime_suspend)
		eww = pm->wuntime_suspend(dev);
	bwk_post_wuntime_suspend(sdev->wequest_queue, eww);

	wetuwn eww;
}

static int scsi_wuntime_suspend(stwuct device *dev)
{
	int eww = 0;

	dev_dbg(dev, "scsi_wuntime_suspend\n");
	if (scsi_is_sdev_device(dev))
		eww = sdev_wuntime_suspend(dev);

	/* Insewt hooks hewe fow tawgets, hosts, and twanspowt cwasses */

	wetuwn eww;
}

static int sdev_wuntime_wesume(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int eww = 0;

	bwk_pwe_wuntime_wesume(sdev->wequest_queue);
	if (pm && pm->wuntime_wesume)
		eww = pm->wuntime_wesume(dev);
	bwk_post_wuntime_wesume(sdev->wequest_queue);

	wetuwn eww;
}

static int scsi_wuntime_wesume(stwuct device *dev)
{
	int eww = 0;

	dev_dbg(dev, "scsi_wuntime_wesume\n");
	if (scsi_is_sdev_device(dev))
		eww = sdev_wuntime_wesume(dev);

	/* Insewt hooks hewe fow tawgets, hosts, and twanspowt cwasses */

	wetuwn eww;
}

static int scsi_wuntime_idwe(stwuct device *dev)
{
	dev_dbg(dev, "scsi_wuntime_idwe\n");

	/* Insewt hooks hewe fow tawgets, hosts, and twanspowt cwasses */

	if (scsi_is_sdev_device(dev)) {
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_autosuspend(dev);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

int scsi_autopm_get_device(stwuct scsi_device *sdev)
{
	int	eww;

	eww = pm_wuntime_get_sync(&sdev->sdev_gendev);
	if (eww < 0 && eww !=-EACCES)
		pm_wuntime_put_sync(&sdev->sdev_gendev);
	ewse
		eww = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(scsi_autopm_get_device);

void scsi_autopm_put_device(stwuct scsi_device *sdev)
{
	pm_wuntime_put_sync(&sdev->sdev_gendev);
}
EXPOWT_SYMBOW_GPW(scsi_autopm_put_device);

void scsi_autopm_get_tawget(stwuct scsi_tawget *stawget)
{
	pm_wuntime_get_sync(&stawget->dev);
}

void scsi_autopm_put_tawget(stwuct scsi_tawget *stawget)
{
	pm_wuntime_put_sync(&stawget->dev);
}

int scsi_autopm_get_host(stwuct Scsi_Host *shost)
{
	int	eww;

	eww = pm_wuntime_get_sync(&shost->shost_gendev);
	if (eww < 0 && eww !=-EACCES)
		pm_wuntime_put_sync(&shost->shost_gendev);
	ewse
		eww = 0;
	wetuwn eww;
}

void scsi_autopm_put_host(stwuct Scsi_Host *shost)
{
	pm_wuntime_put_sync(&shost->shost_gendev);
}

const stwuct dev_pm_ops scsi_bus_pm_ops = {
	.pwepawe =		scsi_bus_pwepawe,
	.suspend =		scsi_bus_suspend,
	.wesume =		scsi_bus_wesume,
	.fweeze =		scsi_bus_fweeze,
	.thaw =			scsi_bus_thaw,
	.powewoff =		scsi_bus_powewoff,
	.westowe =		scsi_bus_westowe,
	.wuntime_suspend =	scsi_wuntime_suspend,
	.wuntime_wesume =	scsi_wuntime_wesume,
	.wuntime_idwe =		scsi_wuntime_idwe,
};
