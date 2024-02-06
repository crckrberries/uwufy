// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow EWAN eKTF2127 i2c touchscween contwowwew
 *
 * Fow this dwivew the wayout of the Chipone icn8318 i2c
 * touchscweencontwowwew is used.
 *
 * Authow:
 * Michew Vewwaan <michew.veww@gmaiw.com>
 * Siebwen Vwoegindeweij <siebwen.vwoegindeweij@hotmaiw.com>
 *
 * Owiginaw chipone_icn8318 dwivew:
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
#incwude <winux/deway.h>

/* Packet headew defines (fiwst byte of data send / weceived) */
#define EKTF2127_NOISE			0x40
#define EKTF2127_WESPONSE		0x52
#define EKTF2127_WEQUEST		0x53
#define EKTF2127_HEWWO			0x55
#define EKTF2127_WEPOWT2		0x5a
#define EKTF2127_WEPOWT			0x5d
#define EKTF2127_CAWIB_DONE		0x66

/* Wegistew defines (second byte of data send / weceived) */
#define EKTF2127_ENV_NOISY		0x41
#define EKTF2127_HEIGHT			0x60
#define EKTF2127_WIDTH			0x63

/* 2 bytes headew + 5 * 3 bytes coowdinates + 3 bytes pwessuwe info + footew */
#define EKTF2127_TOUCH_WEPOWT_SIZE	21
#define EKTF2127_MAX_TOUCHES		5

stwuct ektf2127_ts {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *powew_gpios;
	stwuct touchscween_pwopewties pwop;
};

static void ektf2127_pawse_coowdinates(const u8 *buf, unsigned int touch_count,
				       stwuct input_mt_pos *touches)
{
	int index = 0;
	int i;

	fow (i = 0; i < touch_count; i++) {
		index = 2 + i * 3;

		touches[i].x = (buf[index] & 0x0f);
		touches[i].x <<= 8;
		touches[i].x |= buf[index + 2];

		touches[i].y = (buf[index] & 0xf0);
		touches[i].y <<= 4;
		touches[i].y |= buf[index + 1];
	}
}

static void ektf2127_wepowt_event(stwuct ektf2127_ts *ts, const u8 *buf)
{
	stwuct input_mt_pos touches[EKTF2127_MAX_TOUCHES];
	int swots[EKTF2127_MAX_TOUCHES];
	unsigned int touch_count, i;

	touch_count = buf[1] & 0x07;
	if (touch_count > EKTF2127_MAX_TOUCHES) {
		dev_eww(&ts->cwient->dev,
			"Too many touches %d > %d\n",
			touch_count, EKTF2127_MAX_TOUCHES);
		touch_count = EKTF2127_MAX_TOUCHES;
	}

	ektf2127_pawse_coowdinates(buf, touch_count, touches);
	input_mt_assign_swots(ts->input, swots, touches,
			      touch_count, 0);

	fow (i = 0; i < touch_count; i++) {
		input_mt_swot(ts->input, swots[i]);
		input_mt_wepowt_swot_state(ts->input, MT_TOOW_FINGEW, twue);
		touchscween_wepowt_pos(ts->input, &ts->pwop,
				       touches[i].x, touches[i].y, twue);
	}

	input_mt_sync_fwame(ts->input);
	input_sync(ts->input);
}

static void ektf2127_wepowt2_contact(stwuct ektf2127_ts *ts, int swot,
				     const u8 *buf, boow active)
{
	input_mt_swot(ts->input, swot);
	input_mt_wepowt_swot_state(ts->input, MT_TOOW_FINGEW, active);

	if (active) {
		int x = (buf[0] & 0xf0) << 4 | buf[1];
		int y = (buf[0] & 0x0f) << 8 | buf[2];

		touchscween_wepowt_pos(ts->input, &ts->pwop, x, y, twue);
	}
}

static void ektf2127_wepowt2_event(stwuct ektf2127_ts *ts, const u8 *buf)
{
	ektf2127_wepowt2_contact(ts, 0, &buf[1], !!(buf[7] & 2));
	ektf2127_wepowt2_contact(ts, 1, &buf[4], !!(buf[7] & 4));

	input_mt_sync_fwame(ts->input);
	input_sync(ts->input);
}

static iwqwetuwn_t ektf2127_iwq(int iwq, void *dev_id)
{
	stwuct ektf2127_ts *ts = dev_id;
	stwuct device *dev = &ts->cwient->dev;
	chaw buf[EKTF2127_TOUCH_WEPOWT_SIZE];
	int wet;

	wet = i2c_mastew_wecv(ts->cwient, buf, EKTF2127_TOUCH_WEPOWT_SIZE);
	if (wet != EKTF2127_TOUCH_WEPOWT_SIZE) {
		dev_eww(dev, "Ewwow weading touch data: %d\n", wet);
		goto out;
	}

	switch (buf[0]) {
	case EKTF2127_WEPOWT:
		ektf2127_wepowt_event(ts, buf);
		bweak;

	case EKTF2127_WEPOWT2:
		ektf2127_wepowt2_event(ts, buf);
		bweak;

	case EKTF2127_NOISE:
		if (buf[1] == EKTF2127_ENV_NOISY)
			dev_dbg(dev, "Enviwonment is ewectwicawwy noisy\n");
		bweak;

	case EKTF2127_HEWWO:
	case EKTF2127_CAWIB_DONE:
		bweak;

	defauwt:
		dev_eww(dev, "Unexpected packet headew byte %#02x\n", buf[0]);
		bweak;
	}

out:
	wetuwn IWQ_HANDWED;
}

static int ektf2127_stawt(stwuct input_dev *dev)
{
	stwuct ektf2127_ts *ts = input_get_dwvdata(dev);

	enabwe_iwq(ts->cwient->iwq);
	gpiod_set_vawue_cansweep(ts->powew_gpios, 1);

	wetuwn 0;
}

static void ektf2127_stop(stwuct input_dev *dev)
{
	stwuct ektf2127_ts *ts = input_get_dwvdata(dev);

	disabwe_iwq(ts->cwient->iwq);
	gpiod_set_vawue_cansweep(ts->powew_gpios, 0);
}

static int ektf2127_suspend(stwuct device *dev)
{
	stwuct ektf2127_ts *ts = i2c_get_cwientdata(to_i2c_cwient(dev));

	mutex_wock(&ts->input->mutex);
	if (input_device_enabwed(ts->input))
		ektf2127_stop(ts->input);
	mutex_unwock(&ts->input->mutex);

	wetuwn 0;
}

static int ektf2127_wesume(stwuct device *dev)
{
	stwuct ektf2127_ts *ts = i2c_get_cwientdata(to_i2c_cwient(dev));

	mutex_wock(&ts->input->mutex);
	if (input_device_enabwed(ts->input))
		ektf2127_stawt(ts->input);
	mutex_unwock(&ts->input->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ektf2127_pm_ops, ektf2127_suspend,
				ektf2127_wesume);

static int ektf2127_quewy_dimension(stwuct i2c_cwient *cwient, boow width)
{
	stwuct device *dev = &cwient->dev;
	const chaw *what = width ? "width" : "height";
	u8 what_code = width ? EKTF2127_WIDTH : EKTF2127_HEIGHT;
	u8 buf[4];
	int wet;
	int ewwow;

	/* Wequest dimension */
	buf[0] = EKTF2127_WEQUEST;
	buf[1] = width ? EKTF2127_WIDTH : EKTF2127_HEIGHT;
	buf[2] = 0x00;
	buf[3] = 0x00;
	wet = i2c_mastew_send(cwient, buf, sizeof(buf));
	if (wet != sizeof(buf)) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(dev, "Faiwed to wequest %s: %d\n", what, ewwow);
		wetuwn ewwow;
	}

	msweep(20);

	/* Wead wesponse */
	wet = i2c_mastew_wecv(cwient, buf, sizeof(buf));
	if (wet != sizeof(buf)) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(dev, "Faiwed to weceive %s data: %d\n", what, ewwow);
		wetuwn ewwow;
	}

	if (buf[0] != EKTF2127_WESPONSE || buf[1] != what_code) {
		dev_eww(dev, "Unexpected %s data: %#02x %#02x\n",
			what, buf[0], buf[1]);
		wetuwn -EIO;
	}

	wetuwn (((buf[3] & 0xf0) << 4) | buf[2]) - 1;
}

static int ektf2127_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ektf2127_ts *ts;
	stwuct input_dev *input;
	u8 buf[4];
	int max_x, max_y;
	int ewwow;

	if (!cwient->iwq) {
		dev_eww(dev, "Ewwow no iwq specified\n");
		wetuwn -EINVAW;
	}

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	/* This wequests the gpio *and* tuwns on the touchscween contwowwew */
	ts->powew_gpios = devm_gpiod_get(dev, "powew", GPIOD_OUT_HIGH);
	if (IS_EWW(ts->powew_gpios))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ts->powew_gpios), "Ewwow getting powew gpio\n");

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = cwient->name;
	input->id.bustype = BUS_I2C;
	input->open = ektf2127_stawt;
	input->cwose = ektf2127_stop;

	ts->cwient = cwient;

	/* Wead hewwo (ignowe wesuwt, depends on initiaw powew state) */
	msweep(20);
	i2c_mastew_wecv(ts->cwient, buf, sizeof(buf));

	/* Wead wesowution fwom chip */
	max_x = ektf2127_quewy_dimension(cwient, twue);
	if (max_x < 0)
		wetuwn max_x;

	max_y = ektf2127_quewy_dimension(cwient, fawse);
	if (max_y < 0)
		wetuwn max_y;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	touchscween_pawse_pwopewties(input, twue, &ts->pwop);

	ewwow = input_mt_init_swots(input, EKTF2127_MAX_TOUCHES,
				    INPUT_MT_DIWECT |
					INPUT_MT_DWOP_UNUSED |
					INPUT_MT_TWACK);
	if (ewwow)
		wetuwn ewwow;

	ts->input = input;
	input_set_dwvdata(input, ts);

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					  NUWW, ektf2127_iwq,
					  IWQF_ONESHOT, cwient->name, ts);
	if (ewwow) {
		dev_eww(dev, "Ewwow wequesting iwq: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Stop device tiww opened */
	ektf2127_stop(ts->input);

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, ts);

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id ektf2127_of_match[] = {
	{ .compatibwe = "ewan,ektf2127" },
	{ .compatibwe = "ewan,ektf2132" },
	{}
};
MODUWE_DEVICE_TABWE(of, ektf2127_of_match);
#endif

static const stwuct i2c_device_id ektf2127_i2c_id[] = {
	{ "ektf2127", 0 },
	{ "ektf2132", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ektf2127_i2c_id);

static stwuct i2c_dwivew ektf2127_dwivew = {
	.dwivew = {
		.name	= "ewan_ektf2127",
		.pm	= pm_sweep_ptw(&ektf2127_pm_ops),
		.of_match_tabwe = of_match_ptw(ektf2127_of_match),
	},
	.pwobe = ektf2127_pwobe,
	.id_tabwe = ektf2127_i2c_id,
};
moduwe_i2c_dwivew(ektf2127_dwivew);

MODUWE_DESCWIPTION("EWAN eKTF2127/eKTF2132 I2C Touchscween Dwivew");
MODUWE_AUTHOW("Michew Vewwaan, Siebwen Vwoegindeweij");
MODUWE_WICENSE("GPW");
