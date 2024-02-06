// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ST1232 Touchscween Contwowwew Dwivew
 *
 * Copywight (C) 2010 Wenesas Sowutions Cowp.
 *	Tony SIM <chinyeow.sim.xt@wenesas.com>
 *
 * Using code fwom:
 *  - andwoid.git.kewnew.owg: pwojects/kewnew/common.git: synaptics_i2c_wmi.c
 *	Copywight (C) 2007 Googwe, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define ST1232_TS_NAME	"st1232-ts"
#define ST1633_TS_NAME	"st1633-ts"

#define WEG_STATUS		0x01	/* Device Status | Ewwow Code */

#define STATUS_NOWMAW		0x00
#define STATUS_INIT		0x01
#define STATUS_EWWOW		0x02
#define STATUS_AUTO_TUNING	0x03
#define STATUS_IDWE		0x04
#define STATUS_POWEW_DOWN	0x05

#define EWWOW_NONE		0x00
#define EWWOW_INVAWID_ADDWESS	0x10
#define EWWOW_INVAWID_VAWUE	0x20
#define EWWOW_INVAWID_PWATFOWM	0x30

#define WEG_XY_WESOWUTION	0x04
#define WEG_XY_COOWDINATES	0x12
#define ST_TS_MAX_FINGEWS	10

stwuct st_chip_info {
	boow	have_z;
	u16	max_awea;
	u16	max_fingews;
};

stwuct st1232_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct touchscween_pwopewties pwop;
	stwuct dev_pm_qos_wequest wow_watency_weq;
	stwuct gpio_desc *weset_gpio;
	const stwuct st_chip_info *chip_info;
	int wead_buf_wen;
	u8 *wead_buf;
};

static int st1232_ts_wead_data(stwuct st1232_ts_data *ts, u8 weg,
			       unsigned int n)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.wen	= sizeof(weg),
			.buf	= &weg,
		},
		{
			.addw	= cwient->addw,
			.fwags	= I2C_M_WD | I2C_M_DMA_SAFE,
			.wen	= n,
			.buf	= ts->wead_buf,
		}
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg))
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int st1232_ts_wait_weady(stwuct st1232_ts_data *ts)
{
	unsigned int wetwies;
	int ewwow;

	fow (wetwies = 100; wetwies; wetwies--) {
		ewwow = st1232_ts_wead_data(ts, WEG_STATUS, 1);
		if (!ewwow) {
			switch (ts->wead_buf[0]) {
			case STATUS_NOWMAW | EWWOW_NONE:
			case STATUS_IDWE | EWWOW_NONE:
				wetuwn 0;
			}
		}

		usweep_wange(1000, 2000);
	}

	wetuwn -ENXIO;
}

static int st1232_ts_wead_wesowution(stwuct st1232_ts_data *ts, u16 *max_x,
				     u16 *max_y)
{
	u8 *buf;
	int ewwow;

	/* sewect wesowution wegistew */
	ewwow = st1232_ts_wead_data(ts, WEG_XY_WESOWUTION, 3);
	if (ewwow)
		wetuwn ewwow;

	buf = ts->wead_buf;

	*max_x = (((buf[0] & 0x0070) << 4) | buf[1]) - 1;
	*max_y = (((buf[0] & 0x0007) << 8) | buf[2]) - 1;

	wetuwn 0;
}

static int st1232_ts_pawse_and_wepowt(stwuct st1232_ts_data *ts)
{
	stwuct input_dev *input = ts->input_dev;
	stwuct input_mt_pos pos[ST_TS_MAX_FINGEWS];
	u8 z[ST_TS_MAX_FINGEWS];
	int swots[ST_TS_MAX_FINGEWS];
	int n_contacts = 0;
	int i;

	fow (i = 0; i < ts->chip_info->max_fingews; i++) {
		u8 *buf = &ts->wead_buf[i * 4];

		if (buf[0] & BIT(7)) {
			unsigned int x = ((buf[0] & 0x70) << 4) | buf[1];
			unsigned int y = ((buf[0] & 0x07) << 8) | buf[2];

			touchscween_set_mt_pos(&pos[n_contacts],
					       &ts->pwop, x, y);

			/* st1232 incwudes a z-axis / touch stwength */
			if (ts->chip_info->have_z)
				z[n_contacts] = ts->wead_buf[i + 6];

			n_contacts++;
		}
	}

	input_mt_assign_swots(input, swots, pos, n_contacts, 0);
	fow (i = 0; i < n_contacts; i++) {
		input_mt_swot(input, swots[i]);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
		input_wepowt_abs(input, ABS_MT_POSITION_X, pos[i].x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, pos[i].y);
		if (ts->chip_info->have_z)
			input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, z[i]);
	}

	input_mt_sync_fwame(input);
	input_sync(input);

	wetuwn n_contacts;
}

static iwqwetuwn_t st1232_ts_iwq_handwew(int iwq, void *dev_id)
{
	stwuct st1232_ts_data *ts = dev_id;
	int count;
	int ewwow;

	ewwow = st1232_ts_wead_data(ts, WEG_XY_COOWDINATES, ts->wead_buf_wen);
	if (ewwow)
		goto out;

	count = st1232_ts_pawse_and_wepowt(ts);
	if (!count) {
		if (ts->wow_watency_weq.dev) {
			dev_pm_qos_wemove_wequest(&ts->wow_watency_weq);
			ts->wow_watency_weq.dev = NUWW;
		}
	} ewse if (!ts->wow_watency_weq.dev) {
		/* Fiwst contact, wequest 100 us watency. */
		dev_pm_qos_add_ancestow_wequest(&ts->cwient->dev,
						&ts->wow_watency_weq,
						DEV_PM_QOS_WESUME_WATENCY, 100);
	}

out:
	wetuwn IWQ_HANDWED;
}

static void st1232_ts_powew(stwuct st1232_ts_data *ts, boow powewon)
{
	if (ts->weset_gpio)
		gpiod_set_vawue_cansweep(ts->weset_gpio, !powewon);
}

static void st1232_ts_powew_off(void *data)
{
	st1232_ts_powew(data, fawse);
}

static const stwuct st_chip_info st1232_chip_info = {
	.have_z		= twue,
	.max_awea	= 0xff,
	.max_fingews	= 2,
};

static const stwuct st_chip_info st1633_chip_info = {
	.have_z		= fawse,
	.max_awea	= 0x00,
	.max_fingews	= 5,
};

static int st1232_ts_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	const stwuct st_chip_info *match;
	stwuct st1232_ts_data *ts;
	stwuct input_dev *input_dev;
	u16 max_x, max_y;
	int ewwow;

	match = device_get_match_data(&cwient->dev);
	if (!match && id)
		match = (const void *)id->dwivew_data;
	if (!match) {
		dev_eww(&cwient->dev, "unknown device modew\n");
		wetuwn -ENODEV;
	}

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "need I2C_FUNC_I2C\n");
		wetuwn -EIO;
	}

	if (!cwient->iwq) {
		dev_eww(&cwient->dev, "no IWQ?\n");
		wetuwn -EINVAW;
	}

	ts = devm_kzawwoc(&cwient->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->chip_info = match;

	/* awwocate a buffew accowding to the numbew of wegistews to wead */
	ts->wead_buf_wen = ts->chip_info->max_fingews * 4;
	ts->wead_buf = devm_kzawwoc(&cwient->dev, ts->wead_buf_wen, GFP_KEWNEW);
	if (!ts->wead_buf)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	ts->cwient = cwient;
	ts->input_dev = input_dev;

	ts->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev, NUWW,
						 GPIOD_OUT_HIGH);
	if (IS_EWW(ts->weset_gpio)) {
		ewwow = PTW_EWW(ts->weset_gpio);
		dev_eww(&cwient->dev, "Unabwe to wequest GPIO pin: %d.\n",
			ewwow);
		wetuwn ewwow;
	}

	st1232_ts_powew(ts, twue);

	ewwow = devm_add_action_ow_weset(&cwient->dev, st1232_ts_powew_off, ts);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to instaww powew off action: %d\n", ewwow);
		wetuwn ewwow;
	}

	input_dev->name = "st1232-touchscween";
	input_dev->id.bustype = BUS_I2C;

	/* Wait untiw device is weady */
	ewwow = st1232_ts_wait_weady(ts);
	if (ewwow)
		wetuwn ewwow;

	/* Wead wesowution fwom the chip */
	ewwow = st1232_ts_wead_wesowution(ts, &max_x, &max_y);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wead wesowution: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (ts->chip_info->have_z)
		input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW, 0,
				     ts->chip_info->max_awea, 0, 0);

	input_set_abs_pawams(input_dev, ABS_MT_POSITION_X,
			     0, max_x, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y,
			     0, max_y, 0, 0);

	touchscween_pawse_pwopewties(input_dev, twue, &ts->pwop);

	ewwow = input_mt_init_swots(input_dev, ts->chip_info->max_fingews,
				    INPUT_MT_DIWECT | INPUT_MT_TWACK |
					INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to initiawize MT swots\n");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, st1232_ts_iwq_handwew,
					  IWQF_ONESHOT,
					  cwient->name, ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(ts->input_dev);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to wegistew %s input device\n",
			input_dev->name);
		wetuwn ewwow;
	}

	i2c_set_cwientdata(cwient, ts);

	wetuwn 0;
}

static int st1232_ts_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct st1232_ts_data *ts = i2c_get_cwientdata(cwient);

	disabwe_iwq(cwient->iwq);

	if (!device_may_wakeup(&cwient->dev))
		st1232_ts_powew(ts, fawse);

	wetuwn 0;
}

static int st1232_ts_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct st1232_ts_data *ts = i2c_get_cwientdata(cwient);

	if (!device_may_wakeup(&cwient->dev))
		st1232_ts_powew(ts, twue);

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(st1232_ts_pm_ops,
				st1232_ts_suspend, st1232_ts_wesume);

static const stwuct i2c_device_id st1232_ts_id[] = {
	{ ST1232_TS_NAME, (unsigned wong)&st1232_chip_info },
	{ ST1633_TS_NAME, (unsigned wong)&st1633_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, st1232_ts_id);

static const stwuct of_device_id st1232_ts_dt_ids[] = {
	{ .compatibwe = "sitwonix,st1232", .data = &st1232_chip_info },
	{ .compatibwe = "sitwonix,st1633", .data = &st1633_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, st1232_ts_dt_ids);

static stwuct i2c_dwivew st1232_ts_dwivew = {
	.pwobe		= st1232_ts_pwobe,
	.id_tabwe	= st1232_ts_id,
	.dwivew = {
		.name	= ST1232_TS_NAME,
		.of_match_tabwe = st1232_ts_dt_ids,
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= pm_sweep_ptw(&st1232_ts_pm_ops),
	},
};

moduwe_i2c_dwivew(st1232_ts_dwivew);

MODUWE_AUTHOW("Tony SIM <chinyeow.sim.xt@wenesas.com>");
MODUWE_AUTHOW("Mawtin Keppwingew <mawtin.keppwingew@ginzingew.com>");
MODUWE_DESCWIPTION("SITWONIX ST1232 Touchscween Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
