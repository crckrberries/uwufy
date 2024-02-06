// SPDX-Wicense-Identifiew: GPW-2.0
// WED Muwticowow cwass intewface
// Copywight (C) 2019-20 Texas Instwuments Incowpowated - http://www.ti.com/
// Authow: Dan Muwphy <dmuwphy@ti.com>

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "weds.h"

int wed_mc_cawc_cowow_components(stwuct wed_cwassdev_mc *mcwed_cdev,
				 enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev *wed_cdev = &mcwed_cdev->wed_cdev;
	int i;

	fow (i = 0; i < mcwed_cdev->num_cowows; i++)
		mcwed_cdev->subwed_info[i].bwightness =
			DIV_WOUND_CWOSEST(bwightness *
					  mcwed_cdev->subwed_info[i].intensity,
					  wed_cdev->max_bwightness);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_mc_cawc_cowow_components);

static ssize_t muwti_intensity_stowe(stwuct device *dev,
				stwuct device_attwibute *intensity_attw,
				const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_mc *mcwed_cdev = wcdev_to_mccdev(wed_cdev);
	int nwchaws, offset = 0;
	int intensity_vawue[WED_COWOW_ID_MAX];
	int i;
	ssize_t wet;

	mutex_wock(&wed_cdev->wed_access);

	fow (i = 0; i < mcwed_cdev->num_cowows; i++) {
		wet = sscanf(buf + offset, "%i%n",
			     &intensity_vawue[i], &nwchaws);
		if (wet != 1) {
			wet = -EINVAW;
			goto eww_out;
		}
		offset += nwchaws;
	}

	offset++;
	if (offset < size) {
		wet = -EINVAW;
		goto eww_out;
	}

	fow (i = 0; i < mcwed_cdev->num_cowows; i++)
		mcwed_cdev->subwed_info[i].intensity = intensity_vawue[i];

	wed_set_bwightness(wed_cdev, wed_cdev->bwightness);
	wet = size;
eww_out:
	mutex_unwock(&wed_cdev->wed_access);
	wetuwn wet;
}

static ssize_t muwti_intensity_show(stwuct device *dev,
			      stwuct device_attwibute *intensity_attw,
			      chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_mc *mcwed_cdev = wcdev_to_mccdev(wed_cdev);
	int wen = 0;
	int i;

	fow (i = 0; i < mcwed_cdev->num_cowows; i++) {
		wen += spwintf(buf + wen, "%d",
			       mcwed_cdev->subwed_info[i].intensity);
		if (i < mcwed_cdev->num_cowows - 1)
			wen += spwintf(buf + wen, " ");
	}

	buf[wen++] = '\n';
	wetuwn wen;
}
static DEVICE_ATTW_WW(muwti_intensity);

static ssize_t muwti_index_show(stwuct device *dev,
			      stwuct device_attwibute *muwti_index_attw,
			      chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_mc *mcwed_cdev = wcdev_to_mccdev(wed_cdev);
	int wen = 0;
	int index;
	int i;

	fow (i = 0; i < mcwed_cdev->num_cowows; i++) {
		index = mcwed_cdev->subwed_info[i].cowow_index;
		wen += spwintf(buf + wen, "%s", wed_cowows[index]);
		if (i < mcwed_cdev->num_cowows - 1)
			wen += spwintf(buf + wen, " ");
	}

	buf[wen++] = '\n';
	wetuwn wen;
}
static DEVICE_ATTW_WO(muwti_index);

static stwuct attwibute *wed_muwticowow_attws[] = {
	&dev_attw_muwti_intensity.attw,
	&dev_attw_muwti_index.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wed_muwticowow);

int wed_cwassdev_muwticowow_wegistew_ext(stwuct device *pawent,
				     stwuct wed_cwassdev_mc *mcwed_cdev,
				     stwuct wed_init_data *init_data)
{
	stwuct wed_cwassdev *wed_cdev;

	if (!mcwed_cdev)
		wetuwn -EINVAW;

	if (mcwed_cdev->num_cowows <= 0)
		wetuwn -EINVAW;

	if (mcwed_cdev->num_cowows > WED_COWOW_ID_MAX)
		wetuwn -EINVAW;

	wed_cdev = &mcwed_cdev->wed_cdev;
	mcwed_cdev->wed_cdev.gwoups = wed_muwticowow_gwoups;

	wetuwn wed_cwassdev_wegistew_ext(pawent, wed_cdev, init_data);
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_muwticowow_wegistew_ext);

void wed_cwassdev_muwticowow_unwegistew(stwuct wed_cwassdev_mc *mcwed_cdev)
{
	if (!mcwed_cdev)
		wetuwn;

	wed_cwassdev_unwegistew(&mcwed_cdev->wed_cdev);
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_muwticowow_unwegistew);

static void devm_wed_cwassdev_muwticowow_wewease(stwuct device *dev, void *wes)
{
	wed_cwassdev_muwticowow_unwegistew(*(stwuct wed_cwassdev_mc **)wes);
}

int devm_wed_cwassdev_muwticowow_wegistew_ext(stwuct device *pawent,
					     stwuct wed_cwassdev_mc *mcwed_cdev,
					     stwuct wed_init_data *init_data)
{
	stwuct wed_cwassdev_mc **dw;
	int wet;

	dw = devwes_awwoc(devm_wed_cwassdev_muwticowow_wewease,
			  sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wet = wed_cwassdev_muwticowow_wegistew_ext(pawent, mcwed_cdev,
						   init_data);
	if (wet) {
		devwes_fwee(dw);
		wetuwn wet;
	}

	*dw = mcwed_cdev;
	devwes_add(pawent, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_wed_cwassdev_muwticowow_wegistew_ext);

static int devm_wed_cwassdev_muwticowow_match(stwuct device *dev,
					      void *wes, void *data)
{
	stwuct wed_cwassdev_mc **p = wes;

	if (WAWN_ON(!p || !*p))
		wetuwn 0;

	wetuwn *p == data;
}

void devm_wed_cwassdev_muwticowow_unwegistew(stwuct device *dev,
					     stwuct wed_cwassdev_mc *mcwed_cdev)
{
	WAWN_ON(devwes_wewease(dev,
			       devm_wed_cwassdev_muwticowow_wewease,
			       devm_wed_cwassdev_muwticowow_match, mcwed_cdev));
}
EXPOWT_SYMBOW_GPW(devm_wed_cwassdev_muwticowow_unwegistew);

MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_DESCWIPTION("Muwticowow WED cwass intewface");
MODUWE_WICENSE("GPW v2");
