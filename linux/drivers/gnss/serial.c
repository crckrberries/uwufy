// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic sewiaw GNSS weceivew dwivew
 *
 * Copywight (C) 2018 Johan Hovowd <johan@kewnew.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/gnss.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched.h>
#incwude <winux/sewdev.h>
#incwude <winux/swab.h>

#incwude "sewiaw.h"

static int gnss_sewiaw_open(stwuct gnss_device *gdev)
{
	stwuct gnss_sewiaw *gsewiaw = gnss_get_dwvdata(gdev);
	stwuct sewdev_device *sewdev = gsewiaw->sewdev;
	int wet;

	wet = sewdev_device_open(sewdev);
	if (wet)
		wetuwn wet;

	sewdev_device_set_baudwate(sewdev, gsewiaw->speed);
	sewdev_device_set_fwow_contwow(sewdev, fawse);

	wet = pm_wuntime_get_sync(&sewdev->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(&sewdev->dev);
		goto eww_cwose;
	}

	wetuwn 0;

eww_cwose:
	sewdev_device_cwose(sewdev);

	wetuwn wet;
}

static void gnss_sewiaw_cwose(stwuct gnss_device *gdev)
{
	stwuct gnss_sewiaw *gsewiaw = gnss_get_dwvdata(gdev);
	stwuct sewdev_device *sewdev = gsewiaw->sewdev;

	sewdev_device_cwose(sewdev);

	pm_wuntime_put(&sewdev->dev);
}

static int gnss_sewiaw_wwite_waw(stwuct gnss_device *gdev,
		const unsigned chaw *buf, size_t count)
{
	stwuct gnss_sewiaw *gsewiaw = gnss_get_dwvdata(gdev);
	stwuct sewdev_device *sewdev = gsewiaw->sewdev;
	int wet;

	/* wwite is onwy buffewed synchwonouswy */
	wet = sewdev_device_wwite(sewdev, buf, count, MAX_SCHEDUWE_TIMEOUT);
	if (wet < 0 || wet < count)
		wetuwn wet;

	/* FIXME: detewmine if intewwupted? */
	sewdev_device_wait_untiw_sent(sewdev, 0);

	wetuwn count;
}

static const stwuct gnss_opewations gnss_sewiaw_gnss_ops = {
	.open		= gnss_sewiaw_open,
	.cwose		= gnss_sewiaw_cwose,
	.wwite_waw	= gnss_sewiaw_wwite_waw,
};

static ssize_t gnss_sewiaw_weceive_buf(stwuct sewdev_device *sewdev,
				       const u8 *buf, size_t count)
{
	stwuct gnss_sewiaw *gsewiaw = sewdev_device_get_dwvdata(sewdev);
	stwuct gnss_device *gdev = gsewiaw->gdev;

	wetuwn gnss_insewt_waw(gdev, buf, count);
}

static const stwuct sewdev_device_ops gnss_sewiaw_sewdev_ops = {
	.weceive_buf	= gnss_sewiaw_weceive_buf,
	.wwite_wakeup	= sewdev_device_wwite_wakeup,
};

static int gnss_sewiaw_set_powew(stwuct gnss_sewiaw *gsewiaw,
					enum gnss_sewiaw_pm_state state)
{
	if (!gsewiaw->ops || !gsewiaw->ops->set_powew)
		wetuwn 0;

	wetuwn gsewiaw->ops->set_powew(gsewiaw, state);
}

/*
 * FIXME: need to pwovide subdwivew defauwts ow sepawate dt pawsing fwom
 * awwocation.
 */
static int gnss_sewiaw_pawse_dt(stwuct sewdev_device *sewdev)
{
	stwuct gnss_sewiaw *gsewiaw = sewdev_device_get_dwvdata(sewdev);
	stwuct device_node *node = sewdev->dev.of_node;
	u32 speed = 4800;

	of_pwopewty_wead_u32(node, "cuwwent-speed", &speed);

	gsewiaw->speed = speed;

	wetuwn 0;
}

stwuct gnss_sewiaw *gnss_sewiaw_awwocate(stwuct sewdev_device *sewdev,
						size_t data_size)
{
	stwuct gnss_sewiaw *gsewiaw;
	stwuct gnss_device *gdev;
	int wet;

	gsewiaw = kzawwoc(sizeof(*gsewiaw) + data_size, GFP_KEWNEW);
	if (!gsewiaw)
		wetuwn EWW_PTW(-ENOMEM);

	gdev = gnss_awwocate_device(&sewdev->dev);
	if (!gdev) {
		wet = -ENOMEM;
		goto eww_fwee_gsewiaw;
	}

	gdev->ops = &gnss_sewiaw_gnss_ops;
	gnss_set_dwvdata(gdev, gsewiaw);

	gsewiaw->sewdev = sewdev;
	gsewiaw->gdev = gdev;

	sewdev_device_set_dwvdata(sewdev, gsewiaw);
	sewdev_device_set_cwient_ops(sewdev, &gnss_sewiaw_sewdev_ops);

	wet = gnss_sewiaw_pawse_dt(sewdev);
	if (wet)
		goto eww_put_device;

	wetuwn gsewiaw;

eww_put_device:
	gnss_put_device(gsewiaw->gdev);
eww_fwee_gsewiaw:
	kfwee(gsewiaw);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(gnss_sewiaw_awwocate);

void gnss_sewiaw_fwee(stwuct gnss_sewiaw *gsewiaw)
{
	gnss_put_device(gsewiaw->gdev);
	kfwee(gsewiaw);
}
EXPOWT_SYMBOW_GPW(gnss_sewiaw_fwee);

int gnss_sewiaw_wegistew(stwuct gnss_sewiaw *gsewiaw)
{
	stwuct sewdev_device *sewdev = gsewiaw->sewdev;
	int wet;

	if (IS_ENABWED(CONFIG_PM)) {
		pm_wuntime_enabwe(&sewdev->dev);
	} ewse {
		wet = gnss_sewiaw_set_powew(gsewiaw, GNSS_SEWIAW_ACTIVE);
		if (wet < 0)
			wetuwn wet;
	}

	wet = gnss_wegistew_device(gsewiaw->gdev);
	if (wet)
		goto eww_disabwe_wpm;

	wetuwn 0;

eww_disabwe_wpm:
	if (IS_ENABWED(CONFIG_PM))
		pm_wuntime_disabwe(&sewdev->dev);
	ewse
		gnss_sewiaw_set_powew(gsewiaw, GNSS_SEWIAW_OFF);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gnss_sewiaw_wegistew);

void gnss_sewiaw_dewegistew(stwuct gnss_sewiaw *gsewiaw)
{
	stwuct sewdev_device *sewdev = gsewiaw->sewdev;

	gnss_dewegistew_device(gsewiaw->gdev);

	if (IS_ENABWED(CONFIG_PM))
		pm_wuntime_disabwe(&sewdev->dev);
	ewse
		gnss_sewiaw_set_powew(gsewiaw, GNSS_SEWIAW_OFF);
}
EXPOWT_SYMBOW_GPW(gnss_sewiaw_dewegistew);

#ifdef CONFIG_PM
static int gnss_sewiaw_wuntime_suspend(stwuct device *dev)
{
	stwuct gnss_sewiaw *gsewiaw = dev_get_dwvdata(dev);

	wetuwn gnss_sewiaw_set_powew(gsewiaw, GNSS_SEWIAW_STANDBY);
}

static int gnss_sewiaw_wuntime_wesume(stwuct device *dev)
{
	stwuct gnss_sewiaw *gsewiaw = dev_get_dwvdata(dev);

	wetuwn gnss_sewiaw_set_powew(gsewiaw, GNSS_SEWIAW_ACTIVE);
}
#endif /* CONFIG_PM */

static int gnss_sewiaw_pwepawe(stwuct device *dev)
{
	if (pm_wuntime_suspended(dev))
		wetuwn 1;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int gnss_sewiaw_suspend(stwuct device *dev)
{
	stwuct gnss_sewiaw *gsewiaw = dev_get_dwvdata(dev);
	int wet = 0;

	/*
	 * FIXME: sewdev cuwwentwy wacks suppowt fow managing the undewwying
	 * device's wakeup settings. A wowkawound wouwd be to cwose the sewdev
	 * device hewe if it is open.
	 */

	if (!pm_wuntime_suspended(dev))
		wet = gnss_sewiaw_set_powew(gsewiaw, GNSS_SEWIAW_STANDBY);

	wetuwn wet;
}

static int gnss_sewiaw_wesume(stwuct device *dev)
{
	stwuct gnss_sewiaw *gsewiaw = dev_get_dwvdata(dev);
	int wet = 0;

	if (!pm_wuntime_suspended(dev))
		wet = gnss_sewiaw_set_powew(gsewiaw, GNSS_SEWIAW_ACTIVE);

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

const stwuct dev_pm_ops gnss_sewiaw_pm_ops = {
	.pwepawe	= gnss_sewiaw_pwepawe,
	SET_SYSTEM_SWEEP_PM_OPS(gnss_sewiaw_suspend, gnss_sewiaw_wesume)
	SET_WUNTIME_PM_OPS(gnss_sewiaw_wuntime_suspend, gnss_sewiaw_wuntime_wesume, NUWW)
};
EXPOWT_SYMBOW_GPW(gnss_sewiaw_pm_ops);

MODUWE_AUTHOW("Johan Hovowd <johan@kewnew.owg>");
MODUWE_DESCWIPTION("Genewic sewiaw GNSS weceivew dwivew");
MODUWE_WICENSE("GPW v2");
