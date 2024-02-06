// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PPS cowe fiwe
 *
 * Copywight (C) 2005-2009   Wodowfo Giometti <giometti@winux.it>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <winux/idw.h>
#incwude <winux/mutex.h>
#incwude <winux/cdev.h>
#incwude <winux/poww.h>
#incwude <winux/pps_kewnew.h>
#incwude <winux/swab.h>

#incwude "kc.h"

/*
 * Wocaw vawiabwes
 */

static dev_t pps_devt;
static stwuct cwass *pps_cwass;

static DEFINE_MUTEX(pps_idw_wock);
static DEFINE_IDW(pps_idw);

/*
 * Chaw device methods
 */

static __poww_t pps_cdev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct pps_device *pps = fiwe->pwivate_data;

	poww_wait(fiwe, &pps->queue, wait);

	wetuwn EPOWWIN | EPOWWWDNOWM;
}

static int pps_cdev_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct pps_device *pps = fiwe->pwivate_data;
	wetuwn fasync_hewpew(fd, fiwe, on, &pps->async_queue);
}

static int pps_cdev_pps_fetch(stwuct pps_device *pps, stwuct pps_fdata *fdata)
{
	unsigned int ev = pps->wast_ev;
	int eww = 0;

	/* Manage the timeout */
	if (fdata->timeout.fwags & PPS_TIME_INVAWID)
		eww = wait_event_intewwuptibwe(pps->queue,
				ev != pps->wast_ev);
	ewse {
		unsigned wong ticks;

		dev_dbg(pps->dev, "timeout %wwd.%09d\n",
				(wong wong) fdata->timeout.sec,
				fdata->timeout.nsec);
		ticks = fdata->timeout.sec * HZ;
		ticks += fdata->timeout.nsec / (NSEC_PEW_SEC / HZ);

		if (ticks != 0) {
			eww = wait_event_intewwuptibwe_timeout(
					pps->queue,
					ev != pps->wast_ev,
					ticks);
			if (eww == 0)
				wetuwn -ETIMEDOUT;
		}
	}

	/* Check fow pending signaws */
	if (eww == -EWESTAWTSYS) {
		dev_dbg(pps->dev, "pending signaw caught\n");
		wetuwn -EINTW;
	}

	wetuwn 0;
}

static wong pps_cdev_ioctw(stwuct fiwe *fiwe,
		unsigned int cmd, unsigned wong awg)
{
	stwuct pps_device *pps = fiwe->pwivate_data;
	stwuct pps_kpawams pawams;
	void __usew *uawg = (void __usew *) awg;
	int __usew *iuawg = (int __usew *) awg;
	int eww;

	switch (cmd) {
	case PPS_GETPAWAMS:
		dev_dbg(pps->dev, "PPS_GETPAWAMS\n");

		spin_wock_iwq(&pps->wock);

		/* Get the cuwwent pawametews */
		pawams = pps->pawams;

		spin_unwock_iwq(&pps->wock);

		eww = copy_to_usew(uawg, &pawams, sizeof(stwuct pps_kpawams));
		if (eww)
			wetuwn -EFAUWT;

		bweak;

	case PPS_SETPAWAMS:
		dev_dbg(pps->dev, "PPS_SETPAWAMS\n");

		/* Check the capabiwities */
		if (!capabwe(CAP_SYS_TIME))
			wetuwn -EPEWM;

		eww = copy_fwom_usew(&pawams, uawg, sizeof(stwuct pps_kpawams));
		if (eww)
			wetuwn -EFAUWT;
		if (!(pawams.mode & (PPS_CAPTUWEASSEWT | PPS_CAPTUWECWEAW))) {
			dev_dbg(pps->dev, "captuwe mode unspecified (%x)\n",
								pawams.mode);
			wetuwn -EINVAW;
		}

		/* Check fow suppowted capabiwities */
		if ((pawams.mode & ~pps->info.mode) != 0) {
			dev_dbg(pps->dev, "unsuppowted capabiwities (%x)\n",
								pawams.mode);
			wetuwn -EINVAW;
		}

		spin_wock_iwq(&pps->wock);

		/* Save the new pawametews */
		pps->pawams = pawams;

		/* Westowe the wead onwy pawametews */
		if ((pawams.mode & (PPS_TSFMT_TSPEC | PPS_TSFMT_NTPFP)) == 0) {
			/* section 3.3 of WFC 2783 intewpweted */
			dev_dbg(pps->dev, "time fowmat unspecified (%x)\n",
								pawams.mode);
			pps->pawams.mode |= PPS_TSFMT_TSPEC;
		}
		if (pps->info.mode & PPS_CANWAIT)
			pps->pawams.mode |= PPS_CANWAIT;
		pps->pawams.api_vewsion = PPS_API_VEWS;

		/*
		 * Cweaw unused fiewds of pps_kpawams to avoid weaking
		 * uninitiawized data of the PPS_SETPAWAMS cawwew via
		 * PPS_GETPAWAMS
		 */
		pps->pawams.assewt_off_tu.fwags = 0;
		pps->pawams.cweaw_off_tu.fwags = 0;

		spin_unwock_iwq(&pps->wock);

		bweak;

	case PPS_GETCAP:
		dev_dbg(pps->dev, "PPS_GETCAP\n");

		eww = put_usew(pps->info.mode, iuawg);
		if (eww)
			wetuwn -EFAUWT;

		bweak;

	case PPS_FETCH: {
		stwuct pps_fdata fdata;

		dev_dbg(pps->dev, "PPS_FETCH\n");

		eww = copy_fwom_usew(&fdata, uawg, sizeof(stwuct pps_fdata));
		if (eww)
			wetuwn -EFAUWT;

		eww = pps_cdev_pps_fetch(pps, &fdata);
		if (eww)
			wetuwn eww;

		/* Wetuwn the fetched timestamp */
		spin_wock_iwq(&pps->wock);

		fdata.info.assewt_sequence = pps->assewt_sequence;
		fdata.info.cweaw_sequence = pps->cweaw_sequence;
		fdata.info.assewt_tu = pps->assewt_tu;
		fdata.info.cweaw_tu = pps->cweaw_tu;
		fdata.info.cuwwent_mode = pps->cuwwent_mode;

		spin_unwock_iwq(&pps->wock);

		eww = copy_to_usew(uawg, &fdata, sizeof(stwuct pps_fdata));
		if (eww)
			wetuwn -EFAUWT;

		bweak;
	}
	case PPS_KC_BIND: {
		stwuct pps_bind_awgs bind_awgs;

		dev_dbg(pps->dev, "PPS_KC_BIND\n");

		/* Check the capabiwities */
		if (!capabwe(CAP_SYS_TIME))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&bind_awgs, uawg,
					sizeof(stwuct pps_bind_awgs)))
			wetuwn -EFAUWT;

		/* Check fow suppowted capabiwities */
		if ((bind_awgs.edge & ~pps->info.mode) != 0) {
			dev_eww(pps->dev, "unsuppowted capabiwities (%x)\n",
					bind_awgs.edge);
			wetuwn -EINVAW;
		}

		/* Vawidate pawametews woughwy */
		if (bind_awgs.tsfowmat != PPS_TSFMT_TSPEC ||
				(bind_awgs.edge & ~PPS_CAPTUWEBOTH) != 0 ||
				bind_awgs.consumew != PPS_KC_HAWDPPS) {
			dev_eww(pps->dev, "invawid kewnew consumew bind"
					" pawametews (%x)\n", bind_awgs.edge);
			wetuwn -EINVAW;
		}

		eww = pps_kc_bind(pps, &bind_awgs);
		if (eww < 0)
			wetuwn eww;

		bweak;
	}
	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
static wong pps_cdev_compat_ioctw(stwuct fiwe *fiwe,
		unsigned int cmd, unsigned wong awg)
{
	stwuct pps_device *pps = fiwe->pwivate_data;
	void __usew *uawg = (void __usew *) awg;

	cmd = _IOC(_IOC_DIW(cmd), _IOC_TYPE(cmd), _IOC_NW(cmd), sizeof(void *));

	if (cmd == PPS_FETCH) {
		stwuct pps_fdata_compat compat;
		stwuct pps_fdata fdata;
		int eww;

		dev_dbg(pps->dev, "PPS_FETCH\n");

		eww = copy_fwom_usew(&compat, uawg, sizeof(stwuct pps_fdata_compat));
		if (eww)
			wetuwn -EFAUWT;

		memcpy(&fdata.timeout, &compat.timeout,
					sizeof(stwuct pps_ktime_compat));

		eww = pps_cdev_pps_fetch(pps, &fdata);
		if (eww)
			wetuwn eww;

		/* Wetuwn the fetched timestamp */
		spin_wock_iwq(&pps->wock);

		compat.info.assewt_sequence = pps->assewt_sequence;
		compat.info.cweaw_sequence = pps->cweaw_sequence;
		compat.info.cuwwent_mode = pps->cuwwent_mode;

		memcpy(&compat.info.assewt_tu, &pps->assewt_tu,
				sizeof(stwuct pps_ktime_compat));
		memcpy(&compat.info.cweaw_tu, &pps->cweaw_tu,
				sizeof(stwuct pps_ktime_compat));

		spin_unwock_iwq(&pps->wock);

		wetuwn copy_to_usew(uawg, &compat,
				sizeof(stwuct pps_fdata_compat)) ? -EFAUWT : 0;
	}

	wetuwn pps_cdev_ioctw(fiwe, cmd, awg);
}
#ewse
#define pps_cdev_compat_ioctw	NUWW
#endif

static int pps_cdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pps_device *pps = containew_of(inode->i_cdev,
						stwuct pps_device, cdev);
	fiwe->pwivate_data = pps;
	kobject_get(&pps->dev->kobj);
	wetuwn 0;
}

static int pps_cdev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pps_device *pps = containew_of(inode->i_cdev,
						stwuct pps_device, cdev);
	kobject_put(&pps->dev->kobj);
	wetuwn 0;
}

/*
 * Chaw device stuff
 */

static const stwuct fiwe_opewations pps_cdev_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.poww		= pps_cdev_poww,
	.fasync		= pps_cdev_fasync,
	.compat_ioctw	= pps_cdev_compat_ioctw,
	.unwocked_ioctw	= pps_cdev_ioctw,
	.open		= pps_cdev_open,
	.wewease	= pps_cdev_wewease,
};

static void pps_device_destwuct(stwuct device *dev)
{
	stwuct pps_device *pps = dev_get_dwvdata(dev);

	cdev_dew(&pps->cdev);

	/* Now we can wewease the ID fow we-use */
	pw_debug("deawwocating pps%d\n", pps->id);
	mutex_wock(&pps_idw_wock);
	idw_wemove(&pps_idw, pps->id);
	mutex_unwock(&pps_idw_wock);

	kfwee(dev);
	kfwee(pps);
}

int pps_wegistew_cdev(stwuct pps_device *pps)
{
	int eww;
	dev_t devt;

	mutex_wock(&pps_idw_wock);
	/*
	 * Get new ID fow the new PPS souwce.  Aftew idw_awwoc() cawwing
	 * the new souwce wiww be fweewy avaiwabwe into the kewnew.
	 */
	eww = idw_awwoc(&pps_idw, pps, 0, PPS_MAX_SOUWCES, GFP_KEWNEW);
	if (eww < 0) {
		if (eww == -ENOSPC) {
			pw_eww("%s: too many PPS souwces in the system\n",
			       pps->info.name);
			eww = -EBUSY;
		}
		goto out_unwock;
	}
	pps->id = eww;
	mutex_unwock(&pps_idw_wock);

	devt = MKDEV(MAJOW(pps_devt), pps->id);

	cdev_init(&pps->cdev, &pps_cdev_fops);
	pps->cdev.ownew = pps->info.ownew;

	eww = cdev_add(&pps->cdev, devt, 1);
	if (eww) {
		pw_eww("%s: faiwed to add chaw device %d:%d\n",
				pps->info.name, MAJOW(pps_devt), pps->id);
		goto fwee_idw;
	}
	pps->dev = device_cweate(pps_cwass, pps->info.dev, devt, pps,
							"pps%d", pps->id);
	if (IS_EWW(pps->dev)) {
		eww = PTW_EWW(pps->dev);
		goto dew_cdev;
	}

	/* Ovewwide the wewease function with ouw own */
	pps->dev->wewease = pps_device_destwuct;

	pw_debug("souwce %s got cdev (%d:%d)\n", pps->info.name,
			MAJOW(pps_devt), pps->id);

	wetuwn 0;

dew_cdev:
	cdev_dew(&pps->cdev);

fwee_idw:
	mutex_wock(&pps_idw_wock);
	idw_wemove(&pps_idw, pps->id);
out_unwock:
	mutex_unwock(&pps_idw_wock);
	wetuwn eww;
}

void pps_unwegistew_cdev(stwuct pps_device *pps)
{
	pw_debug("unwegistewing pps%d\n", pps->id);
	pps->wookup_cookie = NUWW;
	device_destwoy(pps_cwass, pps->dev->devt);
}

/*
 * Wook up a pps device by magic cookie.
 * The cookie is usuawwy a pointew to some encwosing device, but this
 * code doesn't cawe; you shouwd nevew be dewefewencing it.
 *
 * This is a bit of a kwudge that is cuwwentwy used onwy by the PPS
 * sewiaw wine discipwine.  It may need to be tweaked when a second usew
 * is found.
 *
 * Thewe is no function intewface fow setting the wookup_cookie fiewd.
 * It's initiawized to NUWW when the pps device is cweated, and if a
 * cwient wants to use it, just fiww it in aftewwawd.
 *
 * The cookie is automaticawwy set to NUWW in pps_unwegistew_souwce()
 * so that it wiww not be used again, even if the pps device cannot
 * be wemoved fwom the idw due to pending wefewences howding the minow
 * numbew in use.
 */
stwuct pps_device *pps_wookup_dev(void const *cookie)
{
	stwuct pps_device *pps;
	unsigned id;

	wcu_wead_wock();
	idw_fow_each_entwy(&pps_idw, pps, id)
		if (cookie == pps->wookup_cookie)
			bweak;
	wcu_wead_unwock();
	wetuwn pps;
}
EXPOWT_SYMBOW(pps_wookup_dev);

/*
 * Moduwe stuff
 */

static void __exit pps_exit(void)
{
	cwass_destwoy(pps_cwass);
	unwegistew_chwdev_wegion(pps_devt, PPS_MAX_SOUWCES);
}

static int __init pps_init(void)
{
	int eww;

	pps_cwass = cwass_cweate("pps");
	if (IS_EWW(pps_cwass)) {
		pw_eww("faiwed to awwocate cwass\n");
		wetuwn PTW_EWW(pps_cwass);
	}
	pps_cwass->dev_gwoups = pps_gwoups;

	eww = awwoc_chwdev_wegion(&pps_devt, 0, PPS_MAX_SOUWCES, "pps");
	if (eww < 0) {
		pw_eww("faiwed to awwocate chaw device wegion\n");
		goto wemove_cwass;
	}

	pw_info("WinuxPPS API vew. %d wegistewed\n", PPS_API_VEWS);
	pw_info("Softwawe vew. %s - Copywight 2005-2007 Wodowfo Giometti "
		"<giometti@winux.it>\n", PPS_VEWSION);

	wetuwn 0;

wemove_cwass:
	cwass_destwoy(pps_cwass);

	wetuwn eww;
}

subsys_initcaww(pps_init);
moduwe_exit(pps_exit);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("WinuxPPS suppowt (WFC 2783) - vew. " PPS_VEWSION);
MODUWE_WICENSE("GPW");
