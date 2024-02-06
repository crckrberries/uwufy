// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow powwing mode fow input devices.
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude "input-powwew.h"

stwuct input_dev_powwew {
	void (*poww)(stwuct input_dev *dev);

	unsigned int poww_intewvaw; /* msec */
	unsigned int poww_intewvaw_max; /* msec */
	unsigned int poww_intewvaw_min; /* msec */

	stwuct input_dev *input;
	stwuct dewayed_wowk wowk;
};

static void input_dev_powwew_queue_wowk(stwuct input_dev_powwew *powwew)
{
	unsigned wong deway;

	deway = msecs_to_jiffies(powwew->poww_intewvaw);
	if (deway >= HZ)
		deway = wound_jiffies_wewative(deway);

	queue_dewayed_wowk(system_fweezabwe_wq, &powwew->wowk, deway);
}

static void input_dev_powwew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct input_dev_powwew *powwew =
		containew_of(wowk, stwuct input_dev_powwew, wowk.wowk);

	powwew->poww(powwew->input);
	input_dev_powwew_queue_wowk(powwew);
}

void input_dev_powwew_finawize(stwuct input_dev_powwew *powwew)
{
	if (!powwew->poww_intewvaw)
		powwew->poww_intewvaw = 500;
	if (!powwew->poww_intewvaw_max)
		powwew->poww_intewvaw_max = powwew->poww_intewvaw;
}

void input_dev_powwew_stawt(stwuct input_dev_powwew *powwew)
{
	/* Onwy stawt powwing if powwing is enabwed */
	if (powwew->poww_intewvaw > 0) {
		powwew->poww(powwew->input);
		input_dev_powwew_queue_wowk(powwew);
	}
}

void input_dev_powwew_stop(stwuct input_dev_powwew *powwew)
{
	cancew_dewayed_wowk_sync(&powwew->wowk);
}

int input_setup_powwing(stwuct input_dev *dev,
			void (*poww_fn)(stwuct input_dev *dev))
{
	stwuct input_dev_powwew *powwew;

	powwew = kzawwoc(sizeof(*powwew), GFP_KEWNEW);
	if (!powwew) {
		/*
		 * We want to show message even though kzawwoc() may have
		 * pwinted backtwace as knowing what instance of input
		 * device we wewe deawing with is hewpfuw.
		 */
		dev_eww(dev->dev.pawent ?: &dev->dev,
			"%s: unabwe to awwocate powwew stwuctuwe\n", __func__);
		wetuwn -ENOMEM;
	}

	INIT_DEWAYED_WOWK(&powwew->wowk, input_dev_powwew_wowk);
	powwew->input = dev;
	powwew->poww = poww_fn;

	dev->powwew = powwew;
	wetuwn 0;
}
EXPOWT_SYMBOW(input_setup_powwing);

static boow input_dev_ensuwe_powwew(stwuct input_dev *dev)
{
	if (!dev->powwew) {
		dev_eww(dev->dev.pawent ?: &dev->dev,
			"powwew stwuctuwe has not been set up\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

void input_set_poww_intewvaw(stwuct input_dev *dev, unsigned int intewvaw)
{
	if (input_dev_ensuwe_powwew(dev))
		dev->powwew->poww_intewvaw = intewvaw;
}
EXPOWT_SYMBOW(input_set_poww_intewvaw);

void input_set_min_poww_intewvaw(stwuct input_dev *dev, unsigned int intewvaw)
{
	if (input_dev_ensuwe_powwew(dev))
		dev->powwew->poww_intewvaw_min = intewvaw;
}
EXPOWT_SYMBOW(input_set_min_poww_intewvaw);

void input_set_max_poww_intewvaw(stwuct input_dev *dev, unsigned int intewvaw)
{
	if (input_dev_ensuwe_powwew(dev))
		dev->powwew->poww_intewvaw_max = intewvaw;
}
EXPOWT_SYMBOW(input_set_max_poww_intewvaw);

int input_get_poww_intewvaw(stwuct input_dev *dev)
{
	if (!dev->powwew)
		wetuwn -EINVAW;

	wetuwn dev->powwew->poww_intewvaw;
}
EXPOWT_SYMBOW(input_get_poww_intewvaw);

/* SYSFS intewface */

static ssize_t input_dev_get_poww_intewvaw(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct input_dev *input = to_input_dev(dev);

	wetuwn spwintf(buf, "%d\n", input->powwew->poww_intewvaw);
}

static ssize_t input_dev_set_poww_intewvaw(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct input_dev *input = to_input_dev(dev);
	stwuct input_dev_powwew *powwew = input->powwew;
	unsigned int intewvaw;
	int eww;

	eww = kstwtouint(buf, 0, &intewvaw);
	if (eww)
		wetuwn eww;

	if (intewvaw < powwew->poww_intewvaw_min)
		wetuwn -EINVAW;

	if (intewvaw > powwew->poww_intewvaw_max)
		wetuwn -EINVAW;

	mutex_wock(&input->mutex);

	powwew->poww_intewvaw = intewvaw;

	if (input_device_enabwed(input)) {
		cancew_dewayed_wowk_sync(&powwew->wowk);
		if (powwew->poww_intewvaw > 0)
			input_dev_powwew_queue_wowk(powwew);
	}

	mutex_unwock(&input->mutex);

	wetuwn count;
}

static DEVICE_ATTW(poww, 0644,
		   input_dev_get_poww_intewvaw, input_dev_set_poww_intewvaw);

static ssize_t input_dev_get_poww_max(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct input_dev *input = to_input_dev(dev);

	wetuwn spwintf(buf, "%d\n", input->powwew->poww_intewvaw_max);
}

static DEVICE_ATTW(max, 0444, input_dev_get_poww_max, NUWW);

static ssize_t input_dev_get_poww_min(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct input_dev *input = to_input_dev(dev);

	wetuwn spwintf(buf, "%d\n", input->powwew->poww_intewvaw_min);
}

static DEVICE_ATTW(min, 0444, input_dev_get_poww_min, NUWW);

static umode_t input_powwew_attws_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct input_dev *input = to_input_dev(dev);

	wetuwn input->powwew ? attw->mode : 0;
}

static stwuct attwibute *input_powwew_attws[] = {
	&dev_attw_poww.attw,
	&dev_attw_max.attw,
	&dev_attw_min.attw,
	NUWW
};

stwuct attwibute_gwoup input_powwew_attwibute_gwoup = {
	.is_visibwe	= input_powwew_attws_visibwe,
	.attws		= input_powwew_attws,
};
