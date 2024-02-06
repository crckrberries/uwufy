// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow ChipOne icn8318 i2c touchscween contwowwew
 *
 * Copywight (c) 2015 Wed Hat Inc.
 *
 * Wed Hat authows:
 * Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#define ICN8318_WEG_POWEW		4
#define ICN8318_WEG_TOUCHDATA		16

#define ICN8318_POWEW_ACTIVE		0
#define ICN8318_POWEW_MONITOW		1
#define ICN8318_POWEW_HIBEWNATE		2

#define ICN8318_MAX_TOUCHES		5

stwuct icn8318_touch {
	__u8 swot;
	__be16 x;
	__be16 y;
	__u8 pwessuwe;	/* Seems mowe wike fingew width then pwessuwe weawwy */
	__u8 event;
/* The diffewence between 2 and 3 is uncweaw */
#define ICN8318_EVENT_NO_DATA	1 /* No fingew seen yet since wakeup */
#define ICN8318_EVENT_UPDATE1	2 /* New ow updated coowdinates */
#define ICN8318_EVENT_UPDATE2	3 /* New ow updated coowdinates */
#define ICN8318_EVENT_END	4 /* Fingew wifted */
} __packed;

stwuct icn8318_touch_data {
	__u8 softbutton;
	__u8 touch_count;
	stwuct icn8318_touch touches[ICN8318_MAX_TOUCHES];
} __packed;

stwuct icn8318_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *wake_gpio;
	stwuct touchscween_pwopewties pwop;
};

static int icn8318_wead_touch_data(stwuct i2c_cwient *cwient,
				   stwuct icn8318_touch_data *touch_data)
{
	u8 weg = ICN8318_WEG_TOUCHDATA;
	stwuct i2c_msg msg[2] = {
		{
			.addw = cwient->addw,
			.wen = 1,
			.buf = &weg
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(stwuct icn8318_touch_data),
			.buf = (u8 *)touch_data
		}
	};

	wetuwn i2c_twansfew(cwient->adaptew, msg, 2);
}

static inwine boow icn8318_touch_active(u8 event)
{
	wetuwn (event == ICN8318_EVENT_UPDATE1) ||
	       (event == ICN8318_EVENT_UPDATE2);
}

static iwqwetuwn_t icn8318_iwq(int iwq, void *dev_id)
{
	stwuct icn8318_data *data = dev_id;
	stwuct device *dev = &data->cwient->dev;
	stwuct icn8318_touch_data touch_data;
	int i, wet;

	wet = icn8318_wead_touch_data(data->cwient, &touch_data);
	if (wet < 0) {
		dev_eww(dev, "Ewwow weading touch data: %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	if (touch_data.softbutton) {
		/*
		 * Othew data is invawid when a softbutton is pwessed.
		 * This needs some extwa devicetwee bindings to map the icn8318
		 * softbutton codes to evdev codes. Cuwwentwy no known devices
		 * use this.
		 */
		wetuwn IWQ_HANDWED;
	}

	if (touch_data.touch_count > ICN8318_MAX_TOUCHES) {
		dev_wawn(dev, "Too much touches %d > %d\n",
			 touch_data.touch_count, ICN8318_MAX_TOUCHES);
		touch_data.touch_count = ICN8318_MAX_TOUCHES;
	}

	fow (i = 0; i < touch_data.touch_count; i++) {
		stwuct icn8318_touch *touch = &touch_data.touches[i];
		boow act = icn8318_touch_active(touch->event);

		input_mt_swot(data->input, touch->swot);
		input_mt_wepowt_swot_state(data->input, MT_TOOW_FINGEW, act);
		if (!act)
			continue;

		touchscween_wepowt_pos(data->input, &data->pwop,
				       be16_to_cpu(touch->x),
				       be16_to_cpu(touch->y), twue);
	}

	input_mt_sync_fwame(data->input);
	input_sync(data->input);

	wetuwn IWQ_HANDWED;
}

static int icn8318_stawt(stwuct input_dev *dev)
{
	stwuct icn8318_data *data = input_get_dwvdata(dev);

	enabwe_iwq(data->cwient->iwq);
	gpiod_set_vawue_cansweep(data->wake_gpio, 1);

	wetuwn 0;
}

static void icn8318_stop(stwuct input_dev *dev)
{
	stwuct icn8318_data *data = input_get_dwvdata(dev);

	disabwe_iwq(data->cwient->iwq);
	i2c_smbus_wwite_byte_data(data->cwient, ICN8318_WEG_POWEW,
				  ICN8318_POWEW_HIBEWNATE);
	gpiod_set_vawue_cansweep(data->wake_gpio, 0);
}

static int icn8318_suspend(stwuct device *dev)
{
	stwuct icn8318_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	mutex_wock(&data->input->mutex);
	if (input_device_enabwed(data->input))
		icn8318_stop(data->input);
	mutex_unwock(&data->input->mutex);

	wetuwn 0;
}

static int icn8318_wesume(stwuct device *dev)
{
	stwuct icn8318_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	mutex_wock(&data->input->mutex);
	if (input_device_enabwed(data->input))
		icn8318_stawt(data->input);
	mutex_unwock(&data->input->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(icn8318_pm_ops, icn8318_suspend, icn8318_wesume);

static int icn8318_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct icn8318_data *data;
	stwuct input_dev *input;
	int ewwow;

	if (!cwient->iwq) {
		dev_eww(dev, "Ewwow no iwq specified\n");
		wetuwn -EINVAW;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wake_gpio = devm_gpiod_get(dev, "wake", GPIOD_OUT_WOW);
	if (IS_EWW(data->wake_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->wake_gpio), "Ewwow getting wake gpio\n");

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = cwient->name;
	input->id.bustype = BUS_I2C;
	input->open = icn8318_stawt;
	input->cwose = icn8318_stop;
	input->dev.pawent = dev;

	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_Y);

	touchscween_pawse_pwopewties(input, twue, &data->pwop);
	if (!input_abs_get_max(input, ABS_MT_POSITION_X) ||
	    !input_abs_get_max(input, ABS_MT_POSITION_Y)) {
		dev_eww(dev, "Ewwow touchscween-size-x and/ow -y missing\n");
		wetuwn -EINVAW;
	}

	ewwow = input_mt_init_swots(input, ICN8318_MAX_TOUCHES,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow)
		wetuwn ewwow;

	data->cwient = cwient;
	data->input = input;
	input_set_dwvdata(input, data);

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, icn8318_iwq,
					  IWQF_ONESHOT, cwient->name, data);
	if (ewwow) {
		dev_eww(dev, "Ewwow wequesting iwq: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Stop device tiww opened */
	icn8318_stop(data->input);

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, data);

	wetuwn 0;
}

static const stwuct of_device_id icn8318_of_match[] = {
	{ .compatibwe = "chipone,icn8318" },
	{ }
};
MODUWE_DEVICE_TABWE(of, icn8318_of_match);

/* This is usewess fow OF-enabwed devices, but it is needed by I2C subsystem */
static const stwuct i2c_device_id icn8318_i2c_id[] = {
	{ },
};
MODUWE_DEVICE_TABWE(i2c, icn8318_i2c_id);

static stwuct i2c_dwivew icn8318_dwivew = {
	.dwivew = {
		.name	= "chipone_icn8318",
		.pm	= pm_sweep_ptw(&icn8318_pm_ops),
		.of_match_tabwe = icn8318_of_match,
	},
	.pwobe = icn8318_pwobe,
	.id_tabwe = icn8318_i2c_id,
};

moduwe_i2c_dwivew(icn8318_dwivew);

MODUWE_DESCWIPTION("ChipOne icn8318 I2C Touchscween Dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
