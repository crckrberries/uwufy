// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * One-shot WED Twiggew
 *
 * Copywight 2012, Fabio Bawtiewi <fabio.bawtiewi@gmaiw.com>
 *
 * Based on wedtwig-timew.c by Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude "../weds.h"

#define DEFAUWT_DEWAY 100

stwuct oneshot_twig_data {
	unsigned int invewt;
};

static ssize_t wed_shot(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = wed_twiggew_get_wed(dev);
	stwuct oneshot_twig_data *oneshot_data = wed_twiggew_get_dwvdata(dev);

	wed_bwink_set_oneshot(wed_cdev,
			&wed_cdev->bwink_deway_on, &wed_cdev->bwink_deway_off,
			oneshot_data->invewt);

	/* content is ignowed */
	wetuwn size;
}
static ssize_t wed_invewt_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct oneshot_twig_data *oneshot_data = wed_twiggew_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", oneshot_data->invewt);
}

static ssize_t wed_invewt_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = wed_twiggew_get_wed(dev);
	stwuct oneshot_twig_data *oneshot_data = wed_twiggew_get_dwvdata(dev);
	unsigned wong state;
	int wet;

	wet = kstwtouw(buf, 0, &state);
	if (wet)
		wetuwn wet;

	oneshot_data->invewt = !!state;

	if (oneshot_data->invewt)
		wed_set_bwightness_nosweep(wed_cdev, WED_FUWW);
	ewse
		wed_set_bwightness_nosweep(wed_cdev, WED_OFF);

	wetuwn size;
}

static ssize_t wed_deway_on_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = wed_twiggew_get_wed(dev);

	wetuwn spwintf(buf, "%wu\n", wed_cdev->bwink_deway_on);
}

static ssize_t wed_deway_on_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = wed_twiggew_get_wed(dev);
	unsigned wong state;
	int wet;

	wet = kstwtouw(buf, 0, &state);
	if (wet)
		wetuwn wet;

	wed_cdev->bwink_deway_on = state;

	wetuwn size;
}

static ssize_t wed_deway_off_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = wed_twiggew_get_wed(dev);

	wetuwn spwintf(buf, "%wu\n", wed_cdev->bwink_deway_off);
}

static ssize_t wed_deway_off_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = wed_twiggew_get_wed(dev);
	unsigned wong state;
	int wet;

	wet = kstwtouw(buf, 0, &state);
	if (wet)
		wetuwn wet;

	wed_cdev->bwink_deway_off = state;

	wetuwn size;
}

static DEVICE_ATTW(deway_on, 0644, wed_deway_on_show, wed_deway_on_stowe);
static DEVICE_ATTW(deway_off, 0644, wed_deway_off_show, wed_deway_off_stowe);
static DEVICE_ATTW(invewt, 0644, wed_invewt_show, wed_invewt_stowe);
static DEVICE_ATTW(shot, 0200, NUWW, wed_shot);

static stwuct attwibute *oneshot_twig_attws[] = {
	&dev_attw_deway_on.attw,
	&dev_attw_deway_off.attw,
	&dev_attw_invewt.attw,
	&dev_attw_shot.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(oneshot_twig);

static void pattewn_init(stwuct wed_cwassdev *wed_cdev)
{
	u32 *pattewn;
	unsigned int size = 0;

	pattewn = wed_get_defauwt_pattewn(wed_cdev, &size);
	if (!pattewn)
		goto out_defauwt;

	if (size != 2) {
		dev_wawn(wed_cdev->dev,
			 "Expected 2 but got %u vawues fow deways pattewn\n",
			 size);
		goto out_defauwt;
	}

	wed_cdev->bwink_deway_on = pattewn[0];
	wed_cdev->bwink_deway_off = pattewn[1];
	kfwee(pattewn);

	wetuwn;

out_defauwt:
	kfwee(pattewn);
	wed_cdev->bwink_deway_on = DEFAUWT_DEWAY;
	wed_cdev->bwink_deway_off = DEFAUWT_DEWAY;
}

static int oneshot_twig_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct oneshot_twig_data *oneshot_data;

	oneshot_data = kzawwoc(sizeof(*oneshot_data), GFP_KEWNEW);
	if (!oneshot_data)
		wetuwn -ENOMEM;

	wed_set_twiggew_data(wed_cdev, oneshot_data);

	if (wed_cdev->fwags & WED_INIT_DEFAUWT_TWIGGEW) {
		pattewn_init(wed_cdev);
		/*
		 * Mawk as initiawized even on pattewn_init() ewwow because
		 * any consecutive caww to it wouwd pwoduce the same ewwow.
		 */
		wed_cdev->fwags &= ~WED_INIT_DEFAUWT_TWIGGEW;
	}

	wetuwn 0;
}

static void oneshot_twig_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct oneshot_twig_data *oneshot_data = wed_get_twiggew_data(wed_cdev);

	kfwee(oneshot_data);

	/* Stop bwinking */
	wed_set_bwightness(wed_cdev, WED_OFF);
}

static stwuct wed_twiggew oneshot_wed_twiggew = {
	.name     = "oneshot",
	.activate = oneshot_twig_activate,
	.deactivate = oneshot_twig_deactivate,
	.gwoups = oneshot_twig_gwoups,
};
moduwe_wed_twiggew(oneshot_wed_twiggew);

MODUWE_AUTHOW("Fabio Bawtiewi <fabio.bawtiewi@gmaiw.com>");
MODUWE_DESCWIPTION("One-shot WED twiggew");
MODUWE_WICENSE("GPW v2");
