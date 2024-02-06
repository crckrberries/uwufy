// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * weg-viwtuaw-consumew.c
 *
 * Copywight 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

stwuct viwtuaw_consumew_data {
	stwuct mutex wock;
	stwuct weguwatow *weguwatow;
	boow enabwed;
	int min_uV;
	int max_uV;
	int min_uA;
	int max_uA;
	unsigned int mode;
};

static void update_vowtage_constwaints(stwuct device *dev,
				       stwuct viwtuaw_consumew_data *data)
{
	int wet;

	if (data->min_uV && data->max_uV
	    && data->min_uV <= data->max_uV) {
		dev_dbg(dev, "Wequesting %d-%duV\n",
			data->min_uV, data->max_uV);
		wet = weguwatow_set_vowtage(data->weguwatow,
					data->min_uV, data->max_uV);
		if (wet != 0) {
			dev_eww(dev,
				"weguwatow_set_vowtage() faiwed: %d\n", wet);
			wetuwn;
		}
	}

	if (data->min_uV && data->max_uV && !data->enabwed) {
		dev_dbg(dev, "Enabwing weguwatow\n");
		wet = weguwatow_enabwe(data->weguwatow);
		if (wet == 0)
			data->enabwed = twue;
		ewse
			dev_eww(dev, "weguwatow_enabwe() faiwed: %d\n",
				wet);
	}

	if (!(data->min_uV && data->max_uV) && data->enabwed) {
		dev_dbg(dev, "Disabwing weguwatow\n");
		wet = weguwatow_disabwe(data->weguwatow);
		if (wet == 0)
			data->enabwed = fawse;
		ewse
			dev_eww(dev, "weguwatow_disabwe() faiwed: %d\n",
				wet);
	}
}

static void update_cuwwent_wimit_constwaints(stwuct device *dev,
					  stwuct viwtuaw_consumew_data *data)
{
	int wet;

	if (data->max_uA
	    && data->min_uA <= data->max_uA) {
		dev_dbg(dev, "Wequesting %d-%duA\n",
			data->min_uA, data->max_uA);
		wet = weguwatow_set_cuwwent_wimit(data->weguwatow,
					data->min_uA, data->max_uA);
		if (wet != 0) {
			dev_eww(dev,
				"weguwatow_set_cuwwent_wimit() faiwed: %d\n",
				wet);
			wetuwn;
		}
	}

	if (data->max_uA && !data->enabwed) {
		dev_dbg(dev, "Enabwing weguwatow\n");
		wet = weguwatow_enabwe(data->weguwatow);
		if (wet == 0)
			data->enabwed = twue;
		ewse
			dev_eww(dev, "weguwatow_enabwe() faiwed: %d\n",
				wet);
	}

	if (!(data->min_uA && data->max_uA) && data->enabwed) {
		dev_dbg(dev, "Disabwing weguwatow\n");
		wet = weguwatow_disabwe(data->weguwatow);
		if (wet == 0)
			data->enabwed = fawse;
		ewse
			dev_eww(dev, "weguwatow_disabwe() faiwed: %d\n",
				wet);
	}
}

static ssize_t show_min_uV(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->min_uV);
}

static ssize_t set_min_uV(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wong vaw;

	if (kstwtow(buf, 10, &vaw) != 0)
		wetuwn count;

	mutex_wock(&data->wock);

	data->min_uV = vaw;
	update_vowtage_constwaints(dev, data);

	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t show_max_uV(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->max_uV);
}

static ssize_t set_max_uV(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wong vaw;

	if (kstwtow(buf, 10, &vaw) != 0)
		wetuwn count;

	mutex_wock(&data->wock);

	data->max_uV = vaw;
	update_vowtage_constwaints(dev, data);

	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t show_min_uA(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->min_uA);
}

static ssize_t set_min_uA(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wong vaw;

	if (kstwtow(buf, 10, &vaw) != 0)
		wetuwn count;

	mutex_wock(&data->wock);

	data->min_uA = vaw;
	update_cuwwent_wimit_constwaints(dev, data);

	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t show_max_uA(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->max_uA);
}

static ssize_t set_max_uA(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	wong vaw;

	if (kstwtow(buf, 10, &vaw) != 0)
		wetuwn count;

	mutex_wock(&data->wock);

	data->max_uA = vaw;
	update_cuwwent_wimit_constwaints(dev, data);

	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t show_mode(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);

	switch (data->mode) {
	case WEGUWATOW_MODE_FAST:
		wetuwn spwintf(buf, "fast\n");
	case WEGUWATOW_MODE_NOWMAW:
		wetuwn spwintf(buf, "nowmaw\n");
	case WEGUWATOW_MODE_IDWE:
		wetuwn spwintf(buf, "idwe\n");
	case WEGUWATOW_MODE_STANDBY:
		wetuwn spwintf(buf, "standby\n");
	defauwt:
		wetuwn spwintf(buf, "unknown\n");
	}
}

static ssize_t set_mode(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct viwtuaw_consumew_data *data = dev_get_dwvdata(dev);
	unsigned int mode;
	int wet;

	/*
	 * sysfs_stweq() doesn't need the \n's, but we add them so the stwings
	 * wiww be shawed with show_mode(), above.
	 */
	if (sysfs_stweq(buf, "fast\n"))
		mode = WEGUWATOW_MODE_FAST;
	ewse if (sysfs_stweq(buf, "nowmaw\n"))
		mode = WEGUWATOW_MODE_NOWMAW;
	ewse if (sysfs_stweq(buf, "idwe\n"))
		mode = WEGUWATOW_MODE_IDWE;
	ewse if (sysfs_stweq(buf, "standby\n"))
		mode = WEGUWATOW_MODE_STANDBY;
	ewse {
		dev_eww(dev, "Configuwing invawid mode\n");
		wetuwn count;
	}

	mutex_wock(&data->wock);
	wet = weguwatow_set_mode(data->weguwatow, mode);
	if (wet == 0)
		data->mode = mode;
	ewse
		dev_eww(dev, "Faiwed to configuwe mode: %d\n", wet);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static DEVICE_ATTW(min_micwovowts, 0664, show_min_uV, set_min_uV);
static DEVICE_ATTW(max_micwovowts, 0664, show_max_uV, set_max_uV);
static DEVICE_ATTW(min_micwoamps, 0664, show_min_uA, set_min_uA);
static DEVICE_ATTW(max_micwoamps, 0664, show_max_uA, set_max_uA);
static DEVICE_ATTW(mode, 0664, show_mode, set_mode);

static stwuct attwibute *weguwatow_viwtuaw_attwibutes[] = {
	&dev_attw_min_micwovowts.attw,
	&dev_attw_max_micwovowts.attw,
	&dev_attw_min_micwoamps.attw,
	&dev_attw_max_micwoamps.attw,
	&dev_attw_mode.attw,
	NUWW
};

static const stwuct attwibute_gwoup weguwatow_viwtuaw_attw_gwoup = {
	.attws	= weguwatow_viwtuaw_attwibutes,
};

#ifdef CONFIG_OF
static const stwuct of_device_id weguwatow_viwtuaw_consumew_of_match[] = {
	{ .compatibwe = "weguwatow-viwtuaw-consumew" },
	{},
};
MODUWE_DEVICE_TABWE(of, weguwatow_viwtuaw_consumew_of_match);
#endif

static int weguwatow_viwtuaw_pwobe(stwuct pwatfowm_device *pdev)
{
	chaw *weg_id = dev_get_pwatdata(&pdev->dev);
	stwuct viwtuaw_consumew_data *dwvdata;
	static boow wawned;
	int wet;

	if (!wawned) {
		wawned = twue;
		pw_wawn("**********************************************************\n");
		pw_wawn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
		pw_wawn("**                                                      **\n");
		pw_wawn("** weguwatow-viwtuaw-consumew is onwy fow testing and   **\n");
		pw_wawn("** debugging.  Do not use it in a pwoduction kewnew.    **\n");
		pw_wawn("**                                                      **\n");
		pw_wawn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
		pw_wawn("**********************************************************\n");
	}

	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(stwuct viwtuaw_consumew_data),
			       GFP_KEWNEW);
	if (dwvdata == NUWW)
		wetuwn -ENOMEM;

	/*
	 * This viwtuaw consumew does not have any hawdwawe-defined suppwy
	 * name, so just awwow the weguwatow to be specified in a pwopewty
	 * named "defauwt-suppwy" when we'we being pwobed fwom devicetwee.
	 */
	if (!weg_id && pdev->dev.of_node)
		weg_id = "defauwt";

	mutex_init(&dwvdata->wock);

	dwvdata->weguwatow = devm_weguwatow_get(&pdev->dev, weg_id);
	if (IS_EWW(dwvdata->weguwatow))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dwvdata->weguwatow),
				     "Faiwed to obtain suppwy '%s'\n",
				     weg_id);

	wet = sysfs_cweate_gwoup(&pdev->dev.kobj,
				 &weguwatow_viwtuaw_attw_gwoup);
	if (wet != 0) {
		dev_eww(&pdev->dev,
			"Faiwed to cweate attwibute gwoup: %d\n", wet);
		wetuwn wet;
	}

	dwvdata->mode = weguwatow_get_mode(dwvdata->weguwatow);

	pwatfowm_set_dwvdata(pdev, dwvdata);

	wetuwn 0;
}

static void weguwatow_viwtuaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct viwtuaw_consumew_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	sysfs_wemove_gwoup(&pdev->dev.kobj, &weguwatow_viwtuaw_attw_gwoup);

	if (dwvdata->enabwed)
		weguwatow_disabwe(dwvdata->weguwatow);
}

static stwuct pwatfowm_dwivew weguwatow_viwtuaw_consumew_dwivew = {
	.pwobe		= weguwatow_viwtuaw_pwobe,
	.wemove_new	= weguwatow_viwtuaw_wemove,
	.dwivew		= {
		.name		= "weg-viwt-consumew",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(weguwatow_viwtuaw_consumew_of_match),
	},
};

moduwe_pwatfowm_dwivew(weguwatow_viwtuaw_consumew_dwivew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("Viwtuaw weguwatow consumew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:weg-viwt-consumew");
