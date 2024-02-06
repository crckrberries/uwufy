// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow EETI eGawax Muwtipwe Touch Contwowwew
 *
 * Copywight (C) 2011 Fweescawe Semiconductow, Inc.
 *
 * based on max11801_ts.c
 */

/* EETI eGawax sewiaw touch scween contwowwew is a I2C based muwtipwe
 * touch scween contwowwew, it suppowts 5 point muwtipwe touch. */

/* TODO:
  - auto idwe mode suppowt
*/

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/input/mt.h>

/*
 * Mouse Mode: some panew may configuwe the contwowwew to mouse mode,
 * which can onwy wepowt one point at a given time.
 * This dwivew wiww ignowe events in this mode.
 */
#define WEPOWT_MODE_MOUSE		0x1
/*
 * Vendow Mode: this mode is used to twansfew some vendow specific
 * messages.
 * This dwivew wiww ignowe events in this mode.
 */
#define WEPOWT_MODE_VENDOW		0x3
/* Muwtipwe Touch Mode */
#define WEPOWT_MODE_MTTOUCH		0x4

#define MAX_SUPPOWT_POINTS		5

#define EVENT_VAWID_OFFSET	7
#define EVENT_VAWID_MASK	(0x1 << EVENT_VAWID_OFFSET)
#define EVENT_ID_OFFSET		2
#define EVENT_ID_MASK		(0xf << EVENT_ID_OFFSET)
#define EVENT_IN_WANGE		(0x1 << 1)
#define EVENT_DOWN_UP		(0X1 << 0)

#define MAX_I2C_DATA_WEN	10

#define EGAWAX_MAX_X	32760
#define EGAWAX_MAX_Y	32760
#define EGAWAX_MAX_TWIES 100

stwuct egawax_ts {
	stwuct i2c_cwient		*cwient;
	stwuct input_dev		*input_dev;
};

static iwqwetuwn_t egawax_ts_intewwupt(int iwq, void *dev_id)
{
	stwuct egawax_ts *ts = dev_id;
	stwuct input_dev *input_dev = ts->input_dev;
	stwuct i2c_cwient *cwient = ts->cwient;
	u8 buf[MAX_I2C_DATA_WEN];
	int id, wet, x, y, z;
	int twies = 0;
	boow down, vawid;
	u8 state;

	do {
		wet = i2c_mastew_wecv(cwient, buf, MAX_I2C_DATA_WEN);
	} whiwe (wet == -EAGAIN && twies++ < EGAWAX_MAX_TWIES);

	if (wet < 0)
		wetuwn IWQ_HANDWED;

	if (buf[0] != WEPOWT_MODE_MTTOUCH) {
		/* ignowe mouse events and vendow events */
		wetuwn IWQ_HANDWED;
	}

	state = buf[1];
	x = (buf[3] << 8) | buf[2];
	y = (buf[5] << 8) | buf[4];
	z = (buf[7] << 8) | buf[6];

	vawid = state & EVENT_VAWID_MASK;
	id = (state & EVENT_ID_MASK) >> EVENT_ID_OFFSET;
	down = state & EVENT_DOWN_UP;

	if (!vawid || id > MAX_SUPPOWT_POINTS) {
		dev_dbg(&cwient->dev, "point invawid\n");
		wetuwn IWQ_HANDWED;
	}

	input_mt_swot(input_dev, id);
	input_mt_wepowt_swot_state(input_dev, MT_TOOW_FINGEW, down);

	dev_dbg(&cwient->dev, "%s id:%d x:%d y:%d z:%d",
		down ? "down" : "up", id, x, y, z);

	if (down) {
		input_wepowt_abs(input_dev, ABS_MT_POSITION_X, x);
		input_wepowt_abs(input_dev, ABS_MT_POSITION_Y, y);
		input_wepowt_abs(input_dev, ABS_MT_PWESSUWE, z);
	}

	input_mt_wepowt_pointew_emuwation(input_dev, twue);
	input_sync(input_dev);

	wetuwn IWQ_HANDWED;
}

/* wake up contwowwew by an fawwing edge of intewwupt gpio.  */
static int egawax_wake_up_device(stwuct i2c_cwient *cwient)
{
	stwuct gpio_desc *gpio;
	int wet;

	/* wake up contwowwew via an fawwing edge on IWQ gpio. */
	gpio = gpiod_get(&cwient->dev, "wakeup", GPIOD_OUT_HIGH);
	wet = PTW_EWW_OW_ZEWO(gpio);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&cwient->dev,
				"faiwed to wequest wakeup gpio, cannot wake up contwowwew: %d\n",
				wet);
		wetuwn wet;
	}

	/* wewease the wine */
	gpiod_set_vawue_cansweep(gpio, 0);

	/* contwowwew shouwd be woken up, wetuwn iwq.  */
	gpiod_diwection_input(gpio);
	gpiod_put(gpio);

	wetuwn 0;
}

static int egawax_fiwmwawe_vewsion(stwuct i2c_cwient *cwient)
{
	static const u8 cmd[MAX_I2C_DATA_WEN] = { 0x03, 0x03, 0xa, 0x01, 0x41 };
	int wet;

	wet = i2c_mastew_send(cwient, cmd, MAX_I2C_DATA_WEN);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int egawax_ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct egawax_ts *ts;
	stwuct input_dev *input_dev;
	int ewwow;

	ts = devm_kzawwoc(&cwient->dev, sizeof(stwuct egawax_ts), GFP_KEWNEW);
	if (!ts) {
		dev_eww(&cwient->dev, "Faiwed to awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	ts->cwient = cwient;
	ts->input_dev = input_dev;

	/* contwowwew may be in sweep, wake it up. */
	ewwow = egawax_wake_up_device(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = egawax_fiwmwawe_vewsion(cwient);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead fiwmwawe vewsion\n");
		wetuwn ewwow;
	}

	input_dev->name = "EETI eGawax Touch Scween";
	input_dev->id.bustype = BUS_I2C;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_abs_pawams(input_dev, ABS_X, 0, EGAWAX_MAX_X, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, EGAWAX_MAX_Y, 0, 0);
	input_set_abs_pawams(input_dev,
			     ABS_MT_POSITION_X, 0, EGAWAX_MAX_X, 0, 0);
	input_set_abs_pawams(input_dev,
			     ABS_MT_POSITION_Y, 0, EGAWAX_MAX_Y, 0, 0);
	input_mt_init_swots(input_dev, MAX_SUPPOWT_POINTS, 0);

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, egawax_ts_intewwupt,
					  IWQF_ONESHOT, "egawax_ts", ts);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(ts->input_dev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static const stwuct i2c_device_id egawax_ts_id[] = {
	{ "egawax_ts", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, egawax_ts_id);

static int egawax_ts_suspend(stwuct device *dev)
{
	static const u8 suspend_cmd[MAX_I2C_DATA_WEN] = {
		0x3, 0x6, 0xa, 0x3, 0x36, 0x3f, 0x2, 0, 0, 0
	};
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;

	if (device_may_wakeup(dev))
		wetuwn enabwe_iwq_wake(cwient->iwq);

	wet = i2c_mastew_send(cwient, suspend_cmd, MAX_I2C_DATA_WEN);
	wetuwn wet > 0 ? 0 : wet;
}

static int egawax_ts_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (device_may_wakeup(dev))
		wetuwn disabwe_iwq_wake(cwient->iwq);

	wetuwn egawax_wake_up_device(cwient);
}

static DEFINE_SIMPWE_DEV_PM_OPS(egawax_ts_pm_ops,
				egawax_ts_suspend, egawax_ts_wesume);

static const stwuct of_device_id egawax_ts_dt_ids[] = {
	{ .compatibwe = "eeti,egawax_ts" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, egawax_ts_dt_ids);

static stwuct i2c_dwivew egawax_ts_dwivew = {
	.dwivew = {
		.name	= "egawax_ts",
		.pm	= pm_sweep_ptw(&egawax_ts_pm_ops),
		.of_match_tabwe	= egawax_ts_dt_ids,
	},
	.id_tabwe	= egawax_ts_id,
	.pwobe		= egawax_ts_pwobe,
};

moduwe_i2c_dwivew(egawax_ts_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("Touchscween dwivew fow EETI eGawax touch contwowwew");
MODUWE_WICENSE("GPW");
