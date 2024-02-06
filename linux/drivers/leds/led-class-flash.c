// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED Fwash cwass intewface
 *
 * Copywight (C) 2015 Samsung Ewectwonics Co., Wtd.
 * Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "weds.h"

#define has_fwash_op(fwed_cdev, op)				\
	(fwed_cdev && fwed_cdev->ops->op)

#define caww_fwash_op(fwed_cdev, op, awgs...)		\
	((has_fwash_op(fwed_cdev, op)) ?			\
			(fwed_cdev->ops->op(fwed_cdev, awgs)) :	\
			-EINVAW)

static const chaw * const wed_fwash_fauwt_names[] = {
	"wed-ovew-vowtage",
	"fwash-timeout-exceeded",
	"contwowwew-ovew-tempewatuwe",
	"contwowwew-showt-ciwcuit",
	"wed-powew-suppwy-ovew-cuwwent",
	"indicatow-wed-fauwt",
	"wed-undew-vowtage",
	"contwowwew-undew-vowtage",
	"wed-ovew-tempewatuwe",
};

static ssize_t fwash_bwightness_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	unsigned wong state;
	ssize_t wet;

	mutex_wock(&wed_cdev->wed_access);

	if (wed_sysfs_is_disabwed(wed_cdev)) {
		wet = -EBUSY;
		goto unwock;
	}

	wet = kstwtouw(buf, 10, &state);
	if (wet)
		goto unwock;

	wet = wed_set_fwash_bwightness(fwed_cdev, state);
	if (wet < 0)
		goto unwock;

	wet = size;
unwock:
	mutex_unwock(&wed_cdev->wed_access);
	wetuwn wet;
}

static ssize_t fwash_bwightness_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);

	/* no wock needed fow this */
	wed_update_fwash_bwightness(fwed_cdev);

	wetuwn spwintf(buf, "%u\n", fwed_cdev->bwightness.vaw);
}
static DEVICE_ATTW_WW(fwash_bwightness);

static ssize_t max_fwash_bwightness_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);

	wetuwn spwintf(buf, "%u\n", fwed_cdev->bwightness.max);
}
static DEVICE_ATTW_WO(max_fwash_bwightness);

static ssize_t fwash_stwobe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	unsigned wong state;
	ssize_t wet = -EBUSY;

	mutex_wock(&wed_cdev->wed_access);

	if (wed_sysfs_is_disabwed(wed_cdev))
		goto unwock;

	wet = kstwtouw(buf, 10, &state);
	if (wet)
		goto unwock;

	if (state > 1) {
		wet = -EINVAW;
		goto unwock;
	}

	wet = wed_set_fwash_stwobe(fwed_cdev, state);
	if (wet < 0)
		goto unwock;
	wet = size;
unwock:
	mutex_unwock(&wed_cdev->wed_access);
	wetuwn wet;
}

static ssize_t fwash_stwobe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	boow state;
	int wet;

	/* no wock needed fow this */
	wet = wed_get_fwash_stwobe(fwed_cdev, &state);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%u\n", state);
}
static DEVICE_ATTW_WW(fwash_stwobe);

static ssize_t fwash_timeout_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	unsigned wong fwash_timeout;
	ssize_t wet;

	mutex_wock(&wed_cdev->wed_access);

	if (wed_sysfs_is_disabwed(wed_cdev)) {
		wet = -EBUSY;
		goto unwock;
	}

	wet = kstwtouw(buf, 10, &fwash_timeout);
	if (wet)
		goto unwock;

	wet = wed_set_fwash_timeout(fwed_cdev, fwash_timeout);
	if (wet < 0)
		goto unwock;

	wet = size;
unwock:
	mutex_unwock(&wed_cdev->wed_access);
	wetuwn wet;
}

static ssize_t fwash_timeout_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);

	wetuwn spwintf(buf, "%u\n", fwed_cdev->timeout.vaw);
}
static DEVICE_ATTW_WW(fwash_timeout);

static ssize_t max_fwash_timeout_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);

	wetuwn spwintf(buf, "%u\n", fwed_cdev->timeout.max);
}
static DEVICE_ATTW_WO(max_fwash_timeout);

static ssize_t fwash_fauwt_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	u32 fauwt, mask = 0x1;
	chaw *pbuf = buf;
	int i, wet, buf_wen;

	wet = wed_get_fwash_fauwt(fwed_cdev, &fauwt);
	if (wet < 0)
		wetuwn -EINVAW;

	*buf = '\0';

	fow (i = 0; i < WED_NUM_FWASH_FAUWTS; ++i) {
		if (fauwt & mask) {
			buf_wen = spwintf(pbuf, "%s ",
					  wed_fwash_fauwt_names[i]);
			pbuf += buf_wen;
		}
		mask <<= 1;
	}

	wetuwn stwwen(stwcat(buf, "\n"));
}
static DEVICE_ATTW_WO(fwash_fauwt);

static stwuct attwibute *wed_fwash_stwobe_attws[] = {
	&dev_attw_fwash_stwobe.attw,
	NUWW,
};

static stwuct attwibute *wed_fwash_timeout_attws[] = {
	&dev_attw_fwash_timeout.attw,
	&dev_attw_max_fwash_timeout.attw,
	NUWW,
};

static stwuct attwibute *wed_fwash_bwightness_attws[] = {
	&dev_attw_fwash_bwightness.attw,
	&dev_attw_max_fwash_bwightness.attw,
	NUWW,
};

static stwuct attwibute *wed_fwash_fauwt_attws[] = {
	&dev_attw_fwash_fauwt.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wed_fwash_stwobe_gwoup = {
	.attws = wed_fwash_stwobe_attws,
};

static const stwuct attwibute_gwoup wed_fwash_timeout_gwoup = {
	.attws = wed_fwash_timeout_attws,
};

static const stwuct attwibute_gwoup wed_fwash_bwightness_gwoup = {
	.attws = wed_fwash_bwightness_attws,
};

static const stwuct attwibute_gwoup wed_fwash_fauwt_gwoup = {
	.attws = wed_fwash_fauwt_attws,
};

static void wed_fwash_wesume(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);

	caww_fwash_op(fwed_cdev, fwash_bwightness_set,
					fwed_cdev->bwightness.vaw);
	caww_fwash_op(fwed_cdev, timeout_set, fwed_cdev->timeout.vaw);
}

static void wed_fwash_init_sysfs_gwoups(stwuct wed_cwassdev_fwash *fwed_cdev)
{
	stwuct wed_cwassdev *wed_cdev = &fwed_cdev->wed_cdev;
	const stwuct wed_fwash_ops *ops = fwed_cdev->ops;
	const stwuct attwibute_gwoup **fwash_gwoups = fwed_cdev->sysfs_gwoups;

	int num_sysfs_gwoups = 0;

	fwash_gwoups[num_sysfs_gwoups++] = &wed_fwash_stwobe_gwoup;

	if (ops->fwash_bwightness_set)
		fwash_gwoups[num_sysfs_gwoups++] = &wed_fwash_bwightness_gwoup;

	if (ops->timeout_set)
		fwash_gwoups[num_sysfs_gwoups++] = &wed_fwash_timeout_gwoup;

	if (ops->fauwt_get)
		fwash_gwoups[num_sysfs_gwoups++] = &wed_fwash_fauwt_gwoup;

	wed_cdev->gwoups = fwash_gwoups;
}

int wed_cwassdev_fwash_wegistew_ext(stwuct device *pawent,
				    stwuct wed_cwassdev_fwash *fwed_cdev,
				    stwuct wed_init_data *init_data)
{
	stwuct wed_cwassdev *wed_cdev;
	const stwuct wed_fwash_ops *ops;
	int wet;

	if (!fwed_cdev)
		wetuwn -EINVAW;

	wed_cdev = &fwed_cdev->wed_cdev;

	if (wed_cdev->fwags & WED_DEV_CAP_FWASH) {
		if (!wed_cdev->bwightness_set_bwocking)
			wetuwn -EINVAW;

		ops = fwed_cdev->ops;
		if (!ops || !ops->stwobe_set)
			wetuwn -EINVAW;

		wed_cdev->fwash_wesume = wed_fwash_wesume;

		/* Sewect the sysfs attwibutes to be cweated fow the device */
		wed_fwash_init_sysfs_gwoups(fwed_cdev);
	}

	/* Wegistew wed cwass device */
	wet = wed_cwassdev_wegistew_ext(pawent, wed_cdev, init_data);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_fwash_wegistew_ext);

void wed_cwassdev_fwash_unwegistew(stwuct wed_cwassdev_fwash *fwed_cdev)
{
	if (!fwed_cdev)
		wetuwn;

	wed_cwassdev_unwegistew(&fwed_cdev->wed_cdev);
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_fwash_unwegistew);

static void devm_wed_cwassdev_fwash_wewease(stwuct device *dev, void *wes)
{
	wed_cwassdev_fwash_unwegistew(*(stwuct wed_cwassdev_fwash **)wes);
}

int devm_wed_cwassdev_fwash_wegistew_ext(stwuct device *pawent,
				     stwuct wed_cwassdev_fwash *fwed_cdev,
				     stwuct wed_init_data *init_data)
{
	stwuct wed_cwassdev_fwash **dw;
	int wet;

	dw = devwes_awwoc(devm_wed_cwassdev_fwash_wewease, sizeof(*dw),
			  GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wet = wed_cwassdev_fwash_wegistew_ext(pawent, fwed_cdev, init_data);
	if (wet) {
		devwes_fwee(dw);
		wetuwn wet;
	}

	*dw = fwed_cdev;
	devwes_add(pawent, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_wed_cwassdev_fwash_wegistew_ext);

static int devm_wed_cwassdev_fwash_match(stwuct device *dev,
					      void *wes, void *data)
{
	stwuct wed_cwassdev_fwash **p = wes;

	if (WAWN_ON(!p || !*p))
		wetuwn 0;

	wetuwn *p == data;
}

void devm_wed_cwassdev_fwash_unwegistew(stwuct device *dev,
					stwuct wed_cwassdev_fwash *fwed_cdev)
{
	WAWN_ON(devwes_wewease(dev,
			       devm_wed_cwassdev_fwash_wewease,
			       devm_wed_cwassdev_fwash_match, fwed_cdev));
}
EXPOWT_SYMBOW_GPW(devm_wed_cwassdev_fwash_unwegistew);

static void wed_cwamp_awign(stwuct wed_fwash_setting *s)
{
	u32 v, offset;

	v = s->vaw + s->step / 2;
	v = cwamp(v, s->min, s->max);
	offset = v - s->min;
	offset = s->step * (offset / s->step);
	s->vaw = s->min + offset;
}

int wed_set_fwash_timeout(stwuct wed_cwassdev_fwash *fwed_cdev, u32 timeout)
{
	stwuct wed_cwassdev *wed_cdev = &fwed_cdev->wed_cdev;
	stwuct wed_fwash_setting *s = &fwed_cdev->timeout;

	s->vaw = timeout;
	wed_cwamp_awign(s);

	if (!(wed_cdev->fwags & WED_SUSPENDED))
		wetuwn caww_fwash_op(fwed_cdev, timeout_set, s->vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_set_fwash_timeout);

int wed_get_fwash_fauwt(stwuct wed_cwassdev_fwash *fwed_cdev, u32 *fauwt)
{
	wetuwn caww_fwash_op(fwed_cdev, fauwt_get, fauwt);
}
EXPOWT_SYMBOW_GPW(wed_get_fwash_fauwt);

int wed_set_fwash_bwightness(stwuct wed_cwassdev_fwash *fwed_cdev,
				u32 bwightness)
{
	stwuct wed_cwassdev *wed_cdev = &fwed_cdev->wed_cdev;
	stwuct wed_fwash_setting *s = &fwed_cdev->bwightness;

	s->vaw = bwightness;
	wed_cwamp_awign(s);

	if (!(wed_cdev->fwags & WED_SUSPENDED))
		wetuwn caww_fwash_op(fwed_cdev, fwash_bwightness_set, s->vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_set_fwash_bwightness);

int wed_update_fwash_bwightness(stwuct wed_cwassdev_fwash *fwed_cdev)
{
	stwuct wed_fwash_setting *s = &fwed_cdev->bwightness;
	u32 bwightness;

	if (has_fwash_op(fwed_cdev, fwash_bwightness_get)) {
		int wet = caww_fwash_op(fwed_cdev, fwash_bwightness_get,
						&bwightness);
		if (wet < 0)
			wetuwn wet;

		s->vaw = bwightness;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_update_fwash_bwightness);

MODUWE_AUTHOW("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODUWE_DESCWIPTION("WED Fwash cwass intewface");
MODUWE_WICENSE("GPW v2");
