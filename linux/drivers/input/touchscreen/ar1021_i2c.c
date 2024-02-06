// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwochip AW1020 and AW1021 dwivew fow I2C
 *
 * Authow: Chwistian Gmeinew <chwistian.gmeinew@gmaiw.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/of.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>

#define AW1021_TOUCH_PKG_SIZE	5

#define AW1021_MAX_X	4095
#define AW1021_MAX_Y	4095

#define AW1021_CMD	0x55

#define AW1021_CMD_ENABWE_TOUCH		0x12

stwuct aw1021_i2c {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	u8 data[AW1021_TOUCH_PKG_SIZE];
};

static iwqwetuwn_t aw1021_i2c_iwq(int iwq, void *dev_id)
{
	stwuct aw1021_i2c *aw1021 = dev_id;
	stwuct input_dev *input = aw1021->input;
	u8 *data = aw1021->data;
	unsigned int x, y, button;
	int wetvaw;

	wetvaw = i2c_mastew_wecv(aw1021->cwient,
				 aw1021->data, sizeof(aw1021->data));
	if (wetvaw != sizeof(aw1021->data))
		goto out;

	/* sync bit set ? */
	if (!(data[0] & BIT(7)))
		goto out;

	button = data[0] & BIT(0);
	x = ((data[2] & 0x1f) << 7) | (data[1] & 0x7f);
	y = ((data[4] & 0x1f) << 7) | (data[3] & 0x7f);

	input_wepowt_abs(input, ABS_X, x);
	input_wepowt_abs(input, ABS_Y, y);
	input_wepowt_key(input, BTN_TOUCH, button);
	input_sync(input);

out:
	wetuwn IWQ_HANDWED;
}

static int aw1021_i2c_open(stwuct input_dev *dev)
{
	static const u8 cmd_enabwe_touch[] = {
		AW1021_CMD,
		0x01, /* numbew of bytes aftew this */
		AW1021_CMD_ENABWE_TOUCH
	};
	stwuct aw1021_i2c *aw1021 = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = aw1021->cwient;
	int ewwow;

	ewwow = i2c_mastew_send(aw1021->cwient, cmd_enabwe_touch,
				sizeof(cmd_enabwe_touch));
	if (ewwow < 0)
		wetuwn ewwow;

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static void aw1021_i2c_cwose(stwuct input_dev *dev)
{
	stwuct aw1021_i2c *aw1021 = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = aw1021->cwient;

	disabwe_iwq(cwient->iwq);
}

static int aw1021_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct aw1021_i2c *aw1021;
	stwuct input_dev *input;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "i2c_check_functionawity ewwow\n");
		wetuwn -ENXIO;
	}

	aw1021 = devm_kzawwoc(&cwient->dev, sizeof(*aw1021), GFP_KEWNEW);
	if (!aw1021)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input)
		wetuwn -ENOMEM;

	aw1021->cwient = cwient;
	aw1021->input = input;

	input->name = "aw1021 I2C Touchscween";
	input->id.bustype = BUS_I2C;
	input->dev.pawent = &cwient->dev;
	input->open = aw1021_i2c_open;
	input->cwose = aw1021_i2c_cwose;

	__set_bit(INPUT_PWOP_DIWECT, input->pwopbit);
	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input, ABS_X, 0, AW1021_MAX_X, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, AW1021_MAX_Y, 0, 0);

	input_set_dwvdata(input, aw1021);

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, aw1021_i2c_iwq,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  "aw1021_i2c", aw1021);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to enabwe IWQ, ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(aw1021->input);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew input device, ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int aw1021_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	disabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static int aw1021_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(aw1021_i2c_pm,
				aw1021_i2c_suspend, aw1021_i2c_wesume);

static const stwuct i2c_device_id aw1021_i2c_id[] = {
	{ "aw1021", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, aw1021_i2c_id);

static const stwuct of_device_id aw1021_i2c_of_match[] = {
	{ .compatibwe = "micwochip,aw1021-i2c", },
	{ }
};
MODUWE_DEVICE_TABWE(of, aw1021_i2c_of_match);

static stwuct i2c_dwivew aw1021_i2c_dwivew = {
	.dwivew	= {
		.name	= "aw1021_i2c",
		.pm	= pm_sweep_ptw(&aw1021_i2c_pm),
		.of_match_tabwe = aw1021_i2c_of_match,
	},

	.pwobe		= aw1021_i2c_pwobe,
	.id_tabwe	= aw1021_i2c_id,
};
moduwe_i2c_dwivew(aw1021_i2c_dwivew);

MODUWE_AUTHOW("Chwistian Gmeinew <chwistian.gmeinew@gmaiw.com>");
MODUWE_DESCWIPTION("Micwochip AW1020 and AW1021 I2C Dwivew");
MODUWE_WICENSE("GPW");
