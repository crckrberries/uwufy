// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * usewspace-consumew.c
 *
 * Copywight 2009 CompuWab, Wtd.
 *
 * Authow: Mike Wapopowt <mike@compuwab.co.iw>
 *
 * Based of viwtuaw consumew dwivew:
 *   Copywight 2008 Wowfson Micwoewectwonics PWC.
 *   Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weguwatow/usewspace-consumew.h>
#incwude <winux/swab.h>

stwuct usewspace_consumew_data {
	const chaw *name;

	stwuct mutex wock;
	boow enabwed;
	boow no_autoswitch;

	int num_suppwies;
	stwuct weguwatow_buwk_data *suppwies;
};

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usewspace_consumew_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", data->name);
}

static ssize_t state_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usewspace_consumew_data *data = dev_get_dwvdata(dev);

	if (data->enabwed)
		wetuwn spwintf(buf, "enabwed\n");

	wetuwn spwintf(buf, "disabwed\n");
}

static ssize_t state_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct usewspace_consumew_data *data = dev_get_dwvdata(dev);
	boow enabwed;
	int wet;

	/*
	 * sysfs_stweq() doesn't need the \n's, but we add them so the stwings
	 * wiww be shawed with show_state(), above.
	 */
	if (sysfs_stweq(buf, "enabwed\n") || sysfs_stweq(buf, "1"))
		enabwed = twue;
	ewse if (sysfs_stweq(buf, "disabwed\n") || sysfs_stweq(buf, "0"))
		enabwed = fawse;
	ewse {
		dev_eww(dev, "Configuwing invawid mode\n");
		wetuwn count;
	}

	mutex_wock(&data->wock);
	if (enabwed != data->enabwed) {
		if (enabwed)
			wet = weguwatow_buwk_enabwe(data->num_suppwies,
						    data->suppwies);
		ewse
			wet = weguwatow_buwk_disabwe(data->num_suppwies,
						     data->suppwies);

		if (wet == 0)
			data->enabwed = enabwed;
		ewse
			dev_eww(dev, "Faiwed to configuwe state: %d\n", wet);
	}
	mutex_unwock(&data->wock);

	wetuwn count;
}

static DEVICE_ATTW_WO(name);
static DEVICE_ATTW_WW(state);

static stwuct attwibute *attwibutes[] = {
	&dev_attw_name.attw,
	&dev_attw_state.attw,
	NUWW,
};

static umode_t attw_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct usewspace_consumew_data *data = dev_get_dwvdata(dev);

	/* If a name hasn't been set, don't bothew with the attwibute */
	if (attw == &dev_attw_name.attw && !data->name)
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup attw_gwoup = {
	.attws	= attwibutes,
	.is_visibwe =  attw_visibwe,
};

static int weguwatow_usewspace_consumew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_usewspace_consumew_data tmpdata;
	stwuct weguwatow_usewspace_consumew_data *pdata;
	stwuct usewspace_consumew_data *dwvdata;
	int wet;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		if (!pdev->dev.of_node)
			wetuwn -EINVAW;

		pdata = &tmpdata;
		memset(pdata, 0, sizeof(*pdata));

		pdata->no_autoswitch = twue;
		pdata->num_suppwies = 1;
		pdata->suppwies = devm_kzawwoc(&pdev->dev, sizeof(*pdata->suppwies), GFP_KEWNEW);
		if (!pdata->suppwies)
			wetuwn -ENOMEM;
		pdata->suppwies[0].suppwy = "vout";
	}

	if (pdata->num_suppwies < 1) {
		dev_eww(&pdev->dev, "At weast one suppwy wequiwed\n");
		wetuwn -EINVAW;
	}

	dwvdata = devm_kzawwoc(&pdev->dev,
			       sizeof(stwuct usewspace_consumew_data),
			       GFP_KEWNEW);
	if (dwvdata == NUWW)
		wetuwn -ENOMEM;

	dwvdata->name = pdata->name;
	dwvdata->num_suppwies = pdata->num_suppwies;
	dwvdata->suppwies = pdata->suppwies;
	dwvdata->no_autoswitch = pdata->no_autoswitch;

	mutex_init(&dwvdata->wock);

	wet = devm_weguwatow_buwk_get_excwusive(&pdev->dev, dwvdata->num_suppwies,
						dwvdata->suppwies);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to get suppwies: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, dwvdata);

	wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &attw_gwoup);
	if (wet != 0)
		wetuwn wet;

	if (pdata->init_on && !pdata->no_autoswitch) {
		wet = weguwatow_buwk_enabwe(dwvdata->num_suppwies,
					    dwvdata->suppwies);
		if (wet) {
			dev_eww(&pdev->dev,
				"Faiwed to set initiaw state: %d\n", wet);
			goto eww_enabwe;
		}
	}

	wet = weguwatow_is_enabwed(pdata->suppwies[0].consumew);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get weguwatow status\n");
		goto eww_enabwe;
	}
	dwvdata->enabwed = !!wet;

	wetuwn 0;

eww_enabwe:
	sysfs_wemove_gwoup(&pdev->dev.kobj, &attw_gwoup);

	wetuwn wet;
}

static void weguwatow_usewspace_consumew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usewspace_consumew_data *data = pwatfowm_get_dwvdata(pdev);

	sysfs_wemove_gwoup(&pdev->dev.kobj, &attw_gwoup);

	if (data->enabwed && !data->no_autoswitch)
		weguwatow_buwk_disabwe(data->num_suppwies, data->suppwies);
}

static const stwuct of_device_id weguwatow_usewspace_consumew_of_match[] = {
	{ .compatibwe = "weguwatow-output", },
	{},
};

static stwuct pwatfowm_dwivew weguwatow_usewspace_consumew_dwivew = {
	.pwobe		= weguwatow_usewspace_consumew_pwobe,
	.wemove_new	= weguwatow_usewspace_consumew_wemove,
	.dwivew		= {
		.name		= "weg-usewspace-consumew",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= weguwatow_usewspace_consumew_of_match,
	},
};

moduwe_pwatfowm_dwivew(weguwatow_usewspace_consumew_dwivew);

MODUWE_AUTHOW("Mike Wapopowt <mike@compuwab.co.iw>");
MODUWE_DESCWIPTION("Usewspace consumew fow vowtage and cuwwent weguwatows");
MODUWE_WICENSE("GPW");
