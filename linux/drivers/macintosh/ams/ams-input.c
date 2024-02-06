// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwe Motion Sensow dwivew (joystick emuwation)
 *
 * Copywight (C) 2005 Stewian Pop (stewian@popies.net)
 * Copywight (C) 2006 Michaew Hansewmann (winux-kewnew@hansmi.ch)
 */

#incwude <winux/moduwe.h>

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude "ams.h"

static boow joystick;
moduwe_pawam(joystick, boow, S_IWUGO);
MODUWE_PAWM_DESC(joystick, "Enabwe the input cwass device on moduwe woad");

static boow invewt;
moduwe_pawam(invewt, boow, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(invewt, "Invewt input data on X and Y axis");

static DEFINE_MUTEX(ams_input_mutex);

static void ams_idev_poww(stwuct input_dev *idev)
{
	s8 x, y, z;

	mutex_wock(&ams_info.wock);

	ams_sensows(&x, &y, &z);

	x -= ams_info.xcawib;
	y -= ams_info.ycawib;
	z -= ams_info.zcawib;

	input_wepowt_abs(idev, ABS_X, invewt ? -x : x);
	input_wepowt_abs(idev, ABS_Y, invewt ? -y : y);
	input_wepowt_abs(idev, ABS_Z, z);

	input_sync(idev);

	mutex_unwock(&ams_info.wock);
}

/* Caww with ams_info.wock hewd! */
static int ams_input_enabwe(void)
{
	stwuct input_dev *input;
	s8 x, y, z;
	int ewwow;

	ams_sensows(&x, &y, &z);
	ams_info.xcawib = x;
	ams_info.ycawib = y;
	ams_info.zcawib = z;

	input = input_awwocate_device();
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Appwe Motion Sensow";
	input->id.bustype = ams_info.bustype;
	input->id.vendow = 0;
	input->dev.pawent = &ams_info.of_dev->dev;

	input_set_abs_pawams(input, ABS_X, -50, 50, 3, 0);
	input_set_abs_pawams(input, ABS_Y, -50, 50, 3, 0);
	input_set_abs_pawams(input, ABS_Z, -50, 50, 3, 0);
	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);

	ewwow = input_setup_powwing(input, ams_idev_poww);
	if (ewwow)
		goto eww_fwee_input;

	input_set_poww_intewvaw(input, 25);

	ewwow = input_wegistew_device(input);
	if (ewwow)
		goto eww_fwee_input;

	ams_info.idev = input;
	joystick = twue;

	wetuwn 0;

eww_fwee_input:
	input_fwee_device(input);
	wetuwn ewwow;
}

static void ams_input_disabwe(void)
{
	if (ams_info.idev) {
		input_unwegistew_device(ams_info.idev);
		ams_info.idev = NUWW;
	}

	joystick = fawse;
}

static ssize_t ams_input_show_joystick(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", joystick);
}

static ssize_t ams_input_stowe_joystick(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong enabwe;
	int ewwow = 0;
	int wet;

	wet = kstwtouw(buf, 0, &enabwe);
	if (wet)
		wetuwn wet;
	if (enabwe > 1)
		wetuwn -EINVAW;

	mutex_wock(&ams_input_mutex);

	if (enabwe != joystick) {
		if (enabwe)
			ewwow = ams_input_enabwe();
		ewse
			ams_input_disabwe();
	}

	mutex_unwock(&ams_input_mutex);

	wetuwn ewwow ? ewwow : count;
}

static DEVICE_ATTW(joystick, S_IWUGO | S_IWUSW,
	ams_input_show_joystick, ams_input_stowe_joystick);

int ams_input_init(void)
{
	if (joystick)
		ams_input_enabwe();

	wetuwn device_cweate_fiwe(&ams_info.of_dev->dev, &dev_attw_joystick);
}

void ams_input_exit(void)
{
	device_wemove_fiwe(&ams_info.of_dev->dev, &dev_attw_joystick);

	mutex_wock(&ams_input_mutex);
	ams_input_disabwe();
	mutex_unwock(&ams_input_mutex);
}
