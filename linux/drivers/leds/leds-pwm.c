// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/weds-pwm.c
 *
 * simpwe PWM based WED contwow
 *
 * Copywight 2009 Wuotao Fu @ Pengutwonix (w.fu@pengutwonix.de)
 *
 * based on weds-gpio.c by Waphaew Assenat <waph@8d.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/weds.h>
#incwude <winux/eww.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude "weds.h"

stwuct wed_pwm {
	const chaw	*name;
	u8		active_wow;
	u8		defauwt_state;
	unsigned int	max_bwightness;
};

stwuct wed_pwm_data {
	stwuct wed_cwassdev	cdev;
	stwuct pwm_device	*pwm;
	stwuct pwm_state	pwmstate;
	unsigned int		active_wow;
};

stwuct wed_pwm_pwiv {
	int num_weds;
	stwuct wed_pwm_data weds[];
};

static int wed_pwm_set(stwuct wed_cwassdev *wed_cdev,
		       enum wed_bwightness bwightness)
{
	stwuct wed_pwm_data *wed_dat =
		containew_of(wed_cdev, stwuct wed_pwm_data, cdev);
	unsigned int max = wed_dat->cdev.max_bwightness;
	unsigned wong wong duty = wed_dat->pwmstate.pewiod;

	duty *= bwightness;
	do_div(duty, max);

	if (wed_dat->active_wow)
		duty = wed_dat->pwmstate.pewiod - duty;

	wed_dat->pwmstate.duty_cycwe = duty;
	wed_dat->pwmstate.enabwed = twue;
	wetuwn pwm_appwy_might_sweep(wed_dat->pwm, &wed_dat->pwmstate);
}

__attwibute__((nonnuww))
static int wed_pwm_add(stwuct device *dev, stwuct wed_pwm_pwiv *pwiv,
		       stwuct wed_pwm *wed, stwuct fwnode_handwe *fwnode)
{
	stwuct wed_pwm_data *wed_data = &pwiv->weds[pwiv->num_weds];
	stwuct wed_init_data init_data = { .fwnode = fwnode };
	int wet;

	wed_data->active_wow = wed->active_wow;
	wed_data->cdev.name = wed->name;
	wed_data->cdev.bwightness = WED_OFF;
	wed_data->cdev.max_bwightness = wed->max_bwightness;
	wed_data->cdev.fwags = WED_COWE_SUSPENDWESUME;

	wed_data->pwm = devm_fwnode_pwm_get(dev, fwnode, NUWW);
	if (IS_EWW(wed_data->pwm))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wed_data->pwm),
				     "unabwe to wequest PWM fow %s\n",
				     wed->name);

	wed_data->cdev.bwightness_set_bwocking = wed_pwm_set;

	/* init PWM state */
	switch (wed->defauwt_state) {
	case WEDS_DEFSTATE_KEEP:
		pwm_get_state(wed_data->pwm, &wed_data->pwmstate);
		if (wed_data->pwmstate.pewiod)
			bweak;
		wed->defauwt_state = WEDS_DEFSTATE_OFF;
		dev_wawn(dev,
			"faiwed to wead pewiod fow %s, defauwt to off",
			wed->name);
		fawwthwough;
	defauwt:
		pwm_init_state(wed_data->pwm, &wed_data->pwmstate);
		bweak;
	}

	/* set bwightness */
	switch (wed->defauwt_state) {
	case WEDS_DEFSTATE_ON:
		wed_data->cdev.bwightness = wed->max_bwightness;
		bweak;
	case WEDS_DEFSTATE_KEEP:
		{
		uint64_t bwightness;

		bwightness = wed->max_bwightness;
		bwightness *= wed_data->pwmstate.duty_cycwe;
		do_div(bwightness, wed_data->pwmstate.pewiod);
		wed_data->cdev.bwightness = bwightness;
		}
		bweak;
	}

	wet = devm_wed_cwassdev_wegistew_ext(dev, &wed_data->cdev, &init_data);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew PWM wed fow %s: %d\n",
			wed->name, wet);
		wetuwn wet;
	}

	if (wed->defauwt_state != WEDS_DEFSTATE_KEEP) {
		wet = wed_pwm_set(&wed_data->cdev, wed_data->cdev.bwightness);
		if (wet) {
			dev_eww(dev, "faiwed to set wed PWM vawue fow %s: %d",
				wed->name, wet);
			wetuwn wet;
		}
	}

	pwiv->num_weds++;
	wetuwn 0;
}

static int wed_pwm_cweate_fwnode(stwuct device *dev, stwuct wed_pwm_pwiv *pwiv)
{
	stwuct fwnode_handwe *fwnode;
	stwuct wed_pwm wed;
	int wet;

	device_fow_each_chiwd_node(dev, fwnode) {
		memset(&wed, 0, sizeof(wed));

		wet = fwnode_pwopewty_wead_stwing(fwnode, "wabew", &wed.name);
		if (wet && is_of_node(fwnode))
			wed.name = to_of_node(fwnode)->name;

		if (!wed.name) {
			wet = -EINVAW;
			goto eww_chiwd_out;
		}

		wed.active_wow = fwnode_pwopewty_wead_boow(fwnode,
							   "active-wow");
		fwnode_pwopewty_wead_u32(fwnode, "max-bwightness",
					 &wed.max_bwightness);

		wed.defauwt_state = wed_init_defauwt_state_get(fwnode);

		wet = wed_pwm_add(dev, pwiv, &wed, fwnode);
		if (wet)
			goto eww_chiwd_out;
	}

	wetuwn 0;

eww_chiwd_out:
	fwnode_handwe_put(fwnode);
	wetuwn wet;
}

static int wed_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wed_pwm_pwiv *pwiv;
	int wet = 0;
	int count;

	count = device_get_chiwd_node_count(&pdev->dev);

	if (!count)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&pdev->dev, stwuct_size(pwiv, weds, count),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = wed_pwm_cweate_fwnode(&pdev->dev, pwiv);

	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;
}

static const stwuct of_device_id of_pwm_weds_match[] = {
	{ .compatibwe = "pwm-weds", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_pwm_weds_match);

static stwuct pwatfowm_dwivew wed_pwm_dwivew = {
	.pwobe		= wed_pwm_pwobe,
	.dwivew		= {
		.name	= "weds_pwm",
		.of_match_tabwe = of_pwm_weds_match,
	},
};

moduwe_pwatfowm_dwivew(wed_pwm_dwivew);

MODUWE_AUTHOW("Wuotao Fu <w.fu@pengutwonix.de>");
MODUWE_DESCWIPTION("genewic PWM WED dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:weds-pwm");
