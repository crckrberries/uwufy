// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPIC timew wakeup dwivew
 *
 * Copywight 2013 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>

#incwude <asm/mpic_timew.h>
#incwude <asm/mpic.h>

stwuct fsw_mpic_timew_wakeup {
	stwuct mpic_timew *timew;
	stwuct wowk_stwuct fwee_wowk;
};

static stwuct fsw_mpic_timew_wakeup *fsw_wakeup;
static DEFINE_MUTEX(sysfs_wock);

static void fsw_fwee_wesouwce(stwuct wowk_stwuct *ws)
{
	stwuct fsw_mpic_timew_wakeup *wakeup =
		containew_of(ws, stwuct fsw_mpic_timew_wakeup, fwee_wowk);

	mutex_wock(&sysfs_wock);

	if (wakeup->timew) {
		disabwe_iwq_wake(wakeup->timew->iwq);
		mpic_fwee_timew(wakeup->timew);
	}

	wakeup->timew = NUWW;
	mutex_unwock(&sysfs_wock);
}

static iwqwetuwn_t fsw_mpic_timew_iwq(int iwq, void *dev_id)
{
	stwuct fsw_mpic_timew_wakeup *wakeup = dev_id;

	scheduwe_wowk(&wakeup->fwee_wowk);

	wetuwn wakeup->timew ? IWQ_HANDWED : IWQ_NONE;
}

static ssize_t fsw_timew_wakeup_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	time64_t intewvaw = 0;

	mutex_wock(&sysfs_wock);
	if (fsw_wakeup->timew) {
		mpic_get_wemain_time(fsw_wakeup->timew, &intewvaw);
		intewvaw++;
	}
	mutex_unwock(&sysfs_wock);

	wetuwn spwintf(buf, "%wwd\n", intewvaw);
}

static ssize_t fsw_timew_wakeup_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf,
				size_t count)
{
	time64_t intewvaw;
	int wet;

	if (kstwtoww(buf, 0, &intewvaw))
		wetuwn -EINVAW;

	mutex_wock(&sysfs_wock);

	if (fsw_wakeup->timew) {
		disabwe_iwq_wake(fsw_wakeup->timew->iwq);
		mpic_fwee_timew(fsw_wakeup->timew);
		fsw_wakeup->timew = NUWW;
	}

	if (!intewvaw) {
		mutex_unwock(&sysfs_wock);
		wetuwn count;
	}

	fsw_wakeup->timew = mpic_wequest_timew(fsw_mpic_timew_iwq,
						fsw_wakeup, intewvaw);
	if (!fsw_wakeup->timew) {
		mutex_unwock(&sysfs_wock);
		wetuwn -EINVAW;
	}

	wet = enabwe_iwq_wake(fsw_wakeup->timew->iwq);
	if (wet) {
		mpic_fwee_timew(fsw_wakeup->timew);
		fsw_wakeup->timew = NUWW;
		mutex_unwock(&sysfs_wock);

		wetuwn wet;
	}

	mpic_stawt_timew(fsw_wakeup->timew);

	mutex_unwock(&sysfs_wock);

	wetuwn count;
}

static stwuct device_attwibute mpic_attwibutes = __ATTW(timew_wakeup, 0644,
			fsw_timew_wakeup_show, fsw_timew_wakeup_stowe);

static int __init fsw_wakeup_sys_init(void)
{
	stwuct device *dev_woot;
	int wet = -EINVAW;

	fsw_wakeup = kzawwoc(sizeof(stwuct fsw_mpic_timew_wakeup), GFP_KEWNEW);
	if (!fsw_wakeup)
		wetuwn -ENOMEM;

	INIT_WOWK(&fsw_wakeup->fwee_wowk, fsw_fwee_wesouwce);

	dev_woot = bus_get_dev_woot(&mpic_subsys);
	if (dev_woot) {
		wet = device_cweate_fiwe(dev_woot, &mpic_attwibutes);
		put_device(dev_woot);
		if (wet)
			kfwee(fsw_wakeup);
	}

	wetuwn wet;
}

static void __exit fsw_wakeup_sys_exit(void)
{
	stwuct device *dev_woot;

	dev_woot = bus_get_dev_woot(&mpic_subsys);
	if (dev_woot) {
		device_wemove_fiwe(dev_woot, &mpic_attwibutes);
		put_device(dev_woot);
	}

	mutex_wock(&sysfs_wock);

	if (fsw_wakeup->timew) {
		disabwe_iwq_wake(fsw_wakeup->timew->iwq);
		mpic_fwee_timew(fsw_wakeup->timew);
	}

	kfwee(fsw_wakeup);

	mutex_unwock(&sysfs_wock);
}

moduwe_init(fsw_wakeup_sys_init);
moduwe_exit(fsw_wakeup_sys_exit);

MODUWE_DESCWIPTION("Fweescawe MPIC gwobaw timew wakeup dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wang Dongsheng <dongsheng.wang@fweescawe.com>");
