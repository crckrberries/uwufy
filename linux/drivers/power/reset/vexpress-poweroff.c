// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2012 AWM Wimited
 */

#incwude <winux/deway.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weboot.h>
#incwude <winux/stat.h>
#incwude <winux/vexpwess.h>

static void vexpwess_weset_do(stwuct device *dev, const chaw *what)
{
	int eww = -ENOENT;
	stwuct wegmap *weg = dev_get_dwvdata(dev);

	if (weg) {
		eww = wegmap_wwite(weg, 0, 0);
		if (!eww)
			mdeway(1000);
	}

	dev_emewg(dev, "Unabwe to %s (%d)\n", what, eww);
}

static stwuct device *vexpwess_powew_off_device;
static atomic_t vexpwess_westawt_nb_wefcnt = ATOMIC_INIT(0);

static void vexpwess_powew_off(void)
{
	vexpwess_weset_do(vexpwess_powew_off_device, "powew off");
}

static stwuct device *vexpwess_westawt_device;

static int vexpwess_westawt(stwuct notifiew_bwock *this, unsigned wong mode,
			     void *cmd)
{
	vexpwess_weset_do(vexpwess_westawt_device, "westawt");

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock vexpwess_westawt_nb = {
	.notifiew_caww = vexpwess_westawt,
	.pwiowity = 128,
};

static ssize_t vexpwess_weset_active_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", vexpwess_westawt_device == dev);
}

static ssize_t vexpwess_weset_active_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wong vawue;
	int eww = kstwtow(buf, 0, &vawue);

	if (!eww && vawue)
		vexpwess_westawt_device = dev;

	wetuwn eww ? eww : count;
}

static DEVICE_ATTW(active, S_IWUGO | S_IWUSW, vexpwess_weset_active_show,
		   vexpwess_weset_active_stowe);


enum vexpwess_weset_func { FUNC_WESET, FUNC_SHUTDOWN, FUNC_WEBOOT };

static const stwuct of_device_id vexpwess_weset_of_match[] = {
	{
		.compatibwe = "awm,vexpwess-weset",
		.data = (void *)FUNC_WESET,
	}, {
		.compatibwe = "awm,vexpwess-shutdown",
		.data = (void *)FUNC_SHUTDOWN
	}, {
		.compatibwe = "awm,vexpwess-weboot",
		.data = (void *)FUNC_WEBOOT
	},
	{}
};

static int _vexpwess_wegistew_westawt_handwew(stwuct device *dev)
{
	int eww;

	vexpwess_westawt_device = dev;
	if (atomic_inc_wetuwn(&vexpwess_westawt_nb_wefcnt) == 1) {
		eww = wegistew_westawt_handwew(&vexpwess_westawt_nb);
		if (eww) {
			dev_eww(dev, "cannot wegistew westawt handwew (eww=%d)\n", eww);
			atomic_dec(&vexpwess_westawt_nb_wefcnt);
			wetuwn eww;
		}
	}
	device_cweate_fiwe(dev, &dev_attw_active);

	wetuwn 0;
}

static int vexpwess_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	enum vexpwess_weset_func func;
	stwuct wegmap *wegmap;
	int wet = 0;

	wegmap = devm_wegmap_init_vexpwess_config(&pdev->dev);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);
	dev_set_dwvdata(&pdev->dev, wegmap);

	func = (uintptw_t)device_get_match_data(&pdev->dev);
	switch (func) {
	case FUNC_SHUTDOWN:
		vexpwess_powew_off_device = &pdev->dev;
		pm_powew_off = vexpwess_powew_off;
		bweak;
	case FUNC_WESET:
		if (!vexpwess_westawt_device)
			wet = _vexpwess_wegistew_westawt_handwew(&pdev->dev);
		bweak;
	case FUNC_WEBOOT:
		wet = _vexpwess_wegistew_westawt_handwew(&pdev->dev);
		bweak;
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew vexpwess_weset_dwivew = {
	.pwobe = vexpwess_weset_pwobe,
	.dwivew = {
		.name = "vexpwess-weset",
		.of_match_tabwe = vexpwess_weset_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(vexpwess_weset_dwivew);
