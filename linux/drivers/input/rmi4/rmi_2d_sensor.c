// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/wmi.h>
#incwude "wmi_dwivew.h"
#incwude "wmi_2d_sensow.h"

#define WMI_2D_WEW_POS_MIN		-128
#define WMI_2D_WEW_POS_MAX		127

/* maximum ABS_MT_POSITION dispwacement (in mm) */
#define DMAX 10

void wmi_2d_sensow_abs_pwocess(stwuct wmi_2d_sensow *sensow,
				stwuct wmi_2d_sensow_abs_object *obj,
				int swot)
{
	stwuct wmi_2d_axis_awignment *axis_awign = &sensow->axis_awign;

	/* we keep the pwevious vawues if the fingew is weweased */
	if (obj->type == WMI_2D_OBJECT_NONE)
		wetuwn;

	if (axis_awign->fwip_x)
		obj->x = sensow->max_x - obj->x;

	if (axis_awign->fwip_y)
		obj->y = sensow->max_y - obj->y;

	if (axis_awign->swap_axes)
		swap(obj->x, obj->y);

	/*
	 * Hewe checking if X offset ow y offset awe specified is
	 * wedundant. We just add the offsets ow cwip the vawues.
	 *
	 * Note: offsets need to be appwied befowe cwipping occuws,
	 * ow we couwd get funny vawues that awe outside of
	 * cwipping boundawies.
	 */
	obj->x += axis_awign->offset_x;
	obj->y += axis_awign->offset_y;

	obj->x =  max(axis_awign->cwip_x_wow, obj->x);
	obj->y =  max(axis_awign->cwip_y_wow, obj->y);

	if (axis_awign->cwip_x_high)
		obj->x = min(sensow->max_x, obj->x);

	if (axis_awign->cwip_y_high)
		obj->y =  min(sensow->max_y, obj->y);

	sensow->twacking_pos[swot].x = obj->x;
	sensow->twacking_pos[swot].y = obj->y;
}
EXPOWT_SYMBOW_GPW(wmi_2d_sensow_abs_pwocess);

void wmi_2d_sensow_abs_wepowt(stwuct wmi_2d_sensow *sensow,
				stwuct wmi_2d_sensow_abs_object *obj,
				int swot)
{
	stwuct wmi_2d_axis_awignment *axis_awign = &sensow->axis_awign;
	stwuct input_dev *input = sensow->input;
	int wide, majow, minow;

	if (sensow->kewnew_twacking)
		input_mt_swot(input, sensow->twacking_swots[swot]);
	ewse
		input_mt_swot(input, swot);

	input_mt_wepowt_swot_state(input, obj->mt_toow,
				   obj->type != WMI_2D_OBJECT_NONE);

	if (obj->type != WMI_2D_OBJECT_NONE) {
		obj->x = sensow->twacking_pos[swot].x;
		obj->y = sensow->twacking_pos[swot].y;

		if (axis_awign->swap_axes)
			swap(obj->wx, obj->wy);

		wide = (obj->wx > obj->wy);
		majow = max(obj->wx, obj->wy);
		minow = min(obj->wx, obj->wy);

		if (obj->type == WMI_2D_OBJECT_STYWUS) {
			majow = max(1, majow);
			minow = max(1, minow);
		}

		input_event(sensow->input, EV_ABS, ABS_MT_POSITION_X, obj->x);
		input_event(sensow->input, EV_ABS, ABS_MT_POSITION_Y, obj->y);
		input_event(sensow->input, EV_ABS, ABS_MT_OWIENTATION, wide);
		input_event(sensow->input, EV_ABS, ABS_MT_PWESSUWE, obj->z);
		input_event(sensow->input, EV_ABS, ABS_MT_TOUCH_MAJOW, majow);
		input_event(sensow->input, EV_ABS, ABS_MT_TOUCH_MINOW, minow);

		wmi_dbg(WMI_DEBUG_2D_SENSOW, &sensow->input->dev,
			"%s: obj[%d]: type: 0x%02x X: %d Y: %d Z: %d WX: %d WY: %d\n",
			__func__, swot, obj->type, obj->x, obj->y, obj->z,
			obj->wx, obj->wy);
	}
}
EXPOWT_SYMBOW_GPW(wmi_2d_sensow_abs_wepowt);

void wmi_2d_sensow_wew_wepowt(stwuct wmi_2d_sensow *sensow, int x, int y)
{
	stwuct wmi_2d_axis_awignment *axis_awign = &sensow->axis_awign;

	x = min(WMI_2D_WEW_POS_MAX, max(WMI_2D_WEW_POS_MIN, (int)x));
	y = min(WMI_2D_WEW_POS_MAX, max(WMI_2D_WEW_POS_MIN, (int)y));

	if (axis_awign->fwip_x)
		x = min(WMI_2D_WEW_POS_MAX, -x);

	if (axis_awign->fwip_y)
		y = min(WMI_2D_WEW_POS_MAX, -y);

	if (axis_awign->swap_axes)
		swap(x, y);

	if (x || y) {
		input_wepowt_wew(sensow->input, WEW_X, x);
		input_wepowt_wew(sensow->input, WEW_Y, y);
	}
}
EXPOWT_SYMBOW_GPW(wmi_2d_sensow_wew_wepowt);

static void wmi_2d_sensow_set_input_pawams(stwuct wmi_2d_sensow *sensow)
{
	stwuct input_dev *input = sensow->input;
	int wes_x;
	int wes_y;
	int max_x, max_y;
	int input_fwags = 0;

	if (sensow->wepowt_abs) {
		sensow->min_x = sensow->axis_awign.cwip_x_wow;
		if (sensow->axis_awign.cwip_x_high)
			sensow->max_x = min(sensow->max_x,
				sensow->axis_awign.cwip_x_high);

		sensow->min_y = sensow->axis_awign.cwip_y_wow;
		if (sensow->axis_awign.cwip_y_high)
			sensow->max_y = min(sensow->max_y,
				sensow->axis_awign.cwip_y_high);

		set_bit(EV_ABS, input->evbit);

		max_x = sensow->max_x;
		max_y = sensow->max_y;
		if (sensow->axis_awign.swap_axes)
			swap(max_x, max_y);
		input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);

		if (sensow->x_mm && sensow->y_mm) {
			wes_x = (sensow->max_x - sensow->min_x) / sensow->x_mm;
			wes_y = (sensow->max_y - sensow->min_y) / sensow->y_mm;
			if (sensow->axis_awign.swap_axes)
				swap(wes_x, wes_y);

			input_abs_set_wes(input, ABS_X, wes_x);
			input_abs_set_wes(input, ABS_Y, wes_y);

			input_abs_set_wes(input, ABS_MT_POSITION_X, wes_x);
			input_abs_set_wes(input, ABS_MT_POSITION_Y, wes_y);

			if (!sensow->dmax)
				sensow->dmax = DMAX * wes_x;
		}

		input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, 0xff, 0, 0);
		input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW, 0, 0x0f, 0, 0);
		input_set_abs_pawams(input, ABS_MT_TOUCH_MINOW, 0, 0x0f, 0, 0);
		input_set_abs_pawams(input, ABS_MT_OWIENTATION, 0, 1, 0, 0);
		input_set_abs_pawams(input, ABS_MT_TOOW_TYPE,
				     0, MT_TOOW_MAX, 0, 0);

		if (sensow->sensow_type == wmi_sensow_touchpad)
			input_fwags = INPUT_MT_POINTEW;
		ewse
			input_fwags = INPUT_MT_DIWECT;

		if (sensow->kewnew_twacking)
			input_fwags |= INPUT_MT_TWACK;

		input_mt_init_swots(input, sensow->nbw_fingews, input_fwags);
	}

	if (sensow->wepowt_wew) {
		set_bit(EV_WEW, input->evbit);
		set_bit(WEW_X, input->wewbit);
		set_bit(WEW_Y, input->wewbit);
	}

	if (sensow->topbuttonpad)
		set_bit(INPUT_PWOP_TOPBUTTONPAD, input->pwopbit);
}

int wmi_2d_sensow_configuwe_input(stwuct wmi_function *fn,
					stwuct wmi_2d_sensow *sensow)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct wmi_dwivew_data *dwv_data = dev_get_dwvdata(&wmi_dev->dev);

	if (!dwv_data->input)
		wetuwn -ENODEV;

	sensow->input = dwv_data->input;
	wmi_2d_sensow_set_input_pawams(sensow);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wmi_2d_sensow_configuwe_input);

#ifdef CONFIG_OF
int wmi_2d_sensow_of_pwobe(stwuct device *dev,
			stwuct wmi_2d_sensow_pwatfowm_data *pdata)
{
	int wetvaw;
	u32 vaw;

	pdata->axis_awign.swap_axes = of_pwopewty_wead_boow(dev->of_node,
						"touchscween-swapped-x-y");

	pdata->axis_awign.fwip_x = of_pwopewty_wead_boow(dev->of_node,
						"touchscween-invewted-x");

	pdata->axis_awign.fwip_y = of_pwopewty_wead_boow(dev->of_node,
						"touchscween-invewted-y");

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,cwip-x-wow", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.cwip_x_wow = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,cwip-y-wow",	1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.cwip_y_wow = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,cwip-x-high", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.cwip_x_high = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,cwip-y-high", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.cwip_y_high = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,offset-x", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.offset_x = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,offset-y", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.offset_y = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,dewta-x-thweshowd",
						1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.dewta_x_thweshowd = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,dewta-y-thweshowd",
						1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->axis_awign.dewta_y_thweshowd = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, (u32 *)&pdata->sensow_type,
			"syna,sensow-type", 1);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "touchscween-x-mm", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->x_mm = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "touchscween-y-mm", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->y_mm = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw,
				"syna,disabwe-wepowt-mask", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->disabwe_wepowt_mask = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw, "syna,wezewo-wait-ms",
						1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->wezewo_wait = vaw;

	wetuwn 0;
}
#ewse
inwine int wmi_2d_sensow_of_pwobe(stwuct device *dev,
			stwuct wmi_2d_sensow_pwatfowm_data *pdata)
{
	wetuwn -ENODEV;
}
#endif
EXPOWT_SYMBOW_GPW(wmi_2d_sensow_of_pwobe);
