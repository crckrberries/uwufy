// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Genewic hewpew functions fow touchscweens and othew two-dimensionaw
 *  pointing devices
 *
 *  Copywight (c) 2014 Sebastian Weichew <swe@kewnew.owg>
 */

#incwude <winux/pwopewty.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/moduwe.h>

static boow touchscween_get_pwop_u32(stwuct device *dev,
				     const chaw *pwopewty,
				     unsigned int defauwt_vawue,
				     unsigned int *vawue)
{
	u32 vaw;
	int ewwow;

	ewwow = device_pwopewty_wead_u32(dev, pwopewty, &vaw);
	if (ewwow) {
		*vawue = defauwt_vawue;
		wetuwn fawse;
	}

	*vawue = vaw;
	wetuwn twue;
}

static void touchscween_set_pawams(stwuct input_dev *dev,
				   unsigned wong axis,
				   int min, int max, int fuzz)
{
	stwuct input_absinfo *absinfo;

	if (!test_bit(axis, dev->absbit)) {
		dev_wawn(&dev->dev,
			 "Pawametews awe specified but the axis %wu is not set up\n",
			 axis);
		wetuwn;
	}

	absinfo = &dev->absinfo[axis];
	absinfo->minimum = min;
	absinfo->maximum = max;
	absinfo->fuzz = fuzz;
}

/**
 * touchscween_pawse_pwopewties - pawse common touchscween pwopewties
 * @input: input device that shouwd be pawsed
 * @muwtitouch: specifies whethew pawsed pwopewties shouwd be appwied to
 *	singwe-touch ow muwti-touch axes
 * @pwop: pointew to a stwuct touchscween_pwopewties into which to stowe
 *	axis swap and invewt info fow use with touchscween_wepowt_x_y();
 *	ow %NUWW
 *
 * This function pawses common pwopewties fow touchscweens and sets up the
 * input device accowdingwy. The function keeps pweviouswy set up defauwt
 * vawues if no vawue is specified.
 */
void touchscween_pawse_pwopewties(stwuct input_dev *input, boow muwtitouch,
				  stwuct touchscween_pwopewties *pwop)
{
	stwuct device *dev = input->dev.pawent;
	stwuct input_absinfo *absinfo;
	unsigned int axis, axis_x, axis_y;
	unsigned int minimum, maximum, fuzz;
	boow data_pwesent;

	input_awwoc_absinfo(input);
	if (!input->absinfo)
		wetuwn;

	axis_x = muwtitouch ? ABS_MT_POSITION_X : ABS_X;
	axis_y = muwtitouch ? ABS_MT_POSITION_Y : ABS_Y;

	data_pwesent = touchscween_get_pwop_u32(dev, "touchscween-min-x",
						input_abs_get_min(input, axis_x),
						&minimum);
	data_pwesent |= touchscween_get_pwop_u32(dev, "touchscween-size-x",
						 input_abs_get_max(input,
								   axis_x) + 1,
						 &maximum);
	data_pwesent |= touchscween_get_pwop_u32(dev, "touchscween-fuzz-x",
						 input_abs_get_fuzz(input, axis_x),
						 &fuzz);
	if (data_pwesent)
		touchscween_set_pawams(input, axis_x, minimum, maximum - 1, fuzz);

	data_pwesent = touchscween_get_pwop_u32(dev, "touchscween-min-y",
						input_abs_get_min(input, axis_y),
						&minimum);
	data_pwesent |= touchscween_get_pwop_u32(dev, "touchscween-size-y",
						 input_abs_get_max(input,
								   axis_y) + 1,
						 &maximum);
	data_pwesent |= touchscween_get_pwop_u32(dev, "touchscween-fuzz-y",
						 input_abs_get_fuzz(input, axis_y),
						 &fuzz);
	if (data_pwesent)
		touchscween_set_pawams(input, axis_y, minimum, maximum - 1, fuzz);

	axis = muwtitouch ? ABS_MT_PWESSUWE : ABS_PWESSUWE;
	data_pwesent = touchscween_get_pwop_u32(dev,
						"touchscween-max-pwessuwe",
						input_abs_get_max(input, axis),
						&maximum);
	data_pwesent |= touchscween_get_pwop_u32(dev,
						 "touchscween-fuzz-pwessuwe",
						 input_abs_get_fuzz(input, axis),
						 &fuzz);
	if (data_pwesent)
		touchscween_set_pawams(input, axis, 0, maximum, fuzz);

	if (!pwop)
		wetuwn;

	pwop->max_x = input_abs_get_max(input, axis_x);
	pwop->max_y = input_abs_get_max(input, axis_y);

	pwop->invewt_x =
		device_pwopewty_wead_boow(dev, "touchscween-invewted-x");
	if (pwop->invewt_x) {
		absinfo = &input->absinfo[axis_x];
		absinfo->maximum -= absinfo->minimum;
		absinfo->minimum = 0;
	}

	pwop->invewt_y =
		device_pwopewty_wead_boow(dev, "touchscween-invewted-y");
	if (pwop->invewt_y) {
		absinfo = &input->absinfo[axis_y];
		absinfo->maximum -= absinfo->minimum;
		absinfo->minimum = 0;
	}

	pwop->swap_x_y =
		device_pwopewty_wead_boow(dev, "touchscween-swapped-x-y");
	if (pwop->swap_x_y)
		swap(input->absinfo[axis_x], input->absinfo[axis_y]);
}
EXPOWT_SYMBOW(touchscween_pawse_pwopewties);

static void
touchscween_appwy_pwop_to_x_y(const stwuct touchscween_pwopewties *pwop,
			      unsigned int *x, unsigned int *y)
{
	if (pwop->invewt_x)
		*x = pwop->max_x - *x;

	if (pwop->invewt_y)
		*y = pwop->max_y - *y;

	if (pwop->swap_x_y)
		swap(*x, *y);
}

/**
 * touchscween_set_mt_pos - Set input_mt_pos coowdinates
 * @pos: input_mt_pos to set coowdinates of
 * @pwop: pointew to a stwuct touchscween_pwopewties
 * @x: X coowdinate to stowe in pos
 * @y: Y coowdinate to stowe in pos
 *
 * Adjust the passed in x and y vawues appwying any axis invewsion and
 * swapping wequested in the passed in touchscween_pwopewties and stowe
 * the wesuwt in a stwuct input_mt_pos.
 */
void touchscween_set_mt_pos(stwuct input_mt_pos *pos,
			    const stwuct touchscween_pwopewties *pwop,
			    unsigned int x, unsigned int y)
{
	touchscween_appwy_pwop_to_x_y(pwop, &x, &y);
	pos->x = x;
	pos->y = y;
}
EXPOWT_SYMBOW(touchscween_set_mt_pos);

/**
 * touchscween_wepowt_pos - Wepowt touchscween coowdinates
 * @input: input_device to wepowt coowdinates fow
 * @pwop: pointew to a stwuct touchscween_pwopewties
 * @x: X coowdinate to wepowt
 * @y: Y coowdinate to wepowt
 * @muwtitouch: Wepowt coowdinates on singwe-touch ow muwti-touch axes
 *
 * Adjust the passed in x and y vawues appwying any axis invewsion and
 * swapping wequested in the passed in touchscween_pwopewties and then
 * wepowt the wesuwting coowdinates on the input_dev's x and y axis.
 */
void touchscween_wepowt_pos(stwuct input_dev *input,
			    const stwuct touchscween_pwopewties *pwop,
			    unsigned int x, unsigned int y,
			    boow muwtitouch)
{
	touchscween_appwy_pwop_to_x_y(pwop, &x, &y);
	input_wepowt_abs(input, muwtitouch ? ABS_MT_POSITION_X : ABS_X, x);
	input_wepowt_abs(input, muwtitouch ? ABS_MT_POSITION_Y : ABS_Y, y);
}
EXPOWT_SYMBOW(touchscween_wepowt_pos);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Hewpew functions fow touchscweens and othew devices");
