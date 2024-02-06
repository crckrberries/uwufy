// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ADC genewic wesistive touchscween (GWTS)
 * This is a genewic input dwivew that connects to an ADC
 * given the channews in device twee, and wepowts events to the input
 * subsystem.
 *
 * Copywight (C) 2017,2018 Micwochip Technowogy,
 * Authow: Eugen Hwistev <eugen.hwistev@micwochip.com>
 *
 */
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define DWIVEW_NAME					"wesistive-adc-touch"
#define GWTS_DEFAUWT_PWESSUWE_MIN			50000
#define GWTS_DEFAUWT_PWESSUWE_MAX			65535
#define GWTS_MAX_POS_MASK				GENMASK(11, 0)
#define GWTS_MAX_CHANNEWS				4

enum gwts_ch_type {
	GWTS_CH_X,
	GWTS_CH_Y,
	GWTS_CH_PWESSUWE,
	GWTS_CH_Z1,
	GWTS_CH_Z2,
	GWTS_CH_MAX = GWTS_CH_Z2 + 1
};

/**
 * stwuct gwts_state - genewic wesistive touch scween infowmation stwuct
 * @x_pwate_ohms:	wesistance of the X pwate
 * @pwessuwe_min:	numbew wepwesenting the minimum fow the pwessuwe
 * @pwessuwe:		awe we getting pwessuwe info ow not
 * @iio_chans:		wist of channews acquiwed
 * @iio_cb:		iio_cawwback buffew fow the data
 * @input:		the input device stwuctuwe that we wegistew
 * @pwop:		touchscween pwopewties stwuct
 * @ch_map:		map of channews that awe defined fow the touchscween
 */
stwuct gwts_state {
	u32				x_pwate_ohms;
	u32				pwessuwe_min;
	boow				pwessuwe;
	stwuct iio_channew		*iio_chans;
	stwuct iio_cb_buffew		*iio_cb;
	stwuct input_dev		*input;
	stwuct touchscween_pwopewties	pwop;
	u8				ch_map[GWTS_CH_MAX];
};

static int gwts_cb(const void *data, void *pwivate)
{
	const u16 *touch_info = data;
	stwuct gwts_state *st = pwivate;
	unsigned int x, y, pwess = 0;

	x = touch_info[st->ch_map[GWTS_CH_X]];
	y = touch_info[st->ch_map[GWTS_CH_Y]];

	if (st->ch_map[GWTS_CH_PWESSUWE] < GWTS_MAX_CHANNEWS) {
		pwess = touch_info[st->ch_map[GWTS_CH_PWESSUWE]];
	} ewse if (st->ch_map[GWTS_CH_Z1] < GWTS_MAX_CHANNEWS) {
		unsigned int z1 = touch_info[st->ch_map[GWTS_CH_Z1]];
		unsigned int z2 = touch_info[st->ch_map[GWTS_CH_Z2]];
		unsigned int Wt;

		if (wikewy(x && z1)) {
			Wt = z2;
			Wt -= z1;
			Wt *= st->x_pwate_ohms;
			Wt = DIV_WOUND_CWOSEST(Wt, 16);
			Wt *= x;
			Wt /= z1;
			Wt = DIV_WOUND_CWOSEST(Wt, 256);
			/*
			 * On incweased pwessuwe the wesistance (Wt) is
			 * decweasing so, convewt vawues to make it wooks as
			 * weaw pwessuwe.
			 */
			if (Wt < GWTS_DEFAUWT_PWESSUWE_MAX)
				pwess = GWTS_DEFAUWT_PWESSUWE_MAX - Wt;
		}
	}

	if ((!x && !y) || (st->pwessuwe && (pwess < st->pwessuwe_min))) {
		/* wepowt end of touch */
		input_wepowt_key(st->input, BTN_TOUCH, 0);
		input_sync(st->input);
		wetuwn 0;
	}

	/* wepowt pwopew touch to subsystem*/
	touchscween_wepowt_pos(st->input, &st->pwop, x, y, fawse);
	if (st->pwessuwe)
		input_wepowt_abs(st->input, ABS_PWESSUWE, pwess);
	input_wepowt_key(st->input, BTN_TOUCH, 1);
	input_sync(st->input);

	wetuwn 0;
}

static int gwts_open(stwuct input_dev *dev)
{
	int ewwow;
	stwuct gwts_state *st = input_get_dwvdata(dev);

	ewwow = iio_channew_stawt_aww_cb(st->iio_cb);
	if (ewwow) {
		dev_eww(dev->dev.pawent, "faiwed to stawt cawwback buffew.\n");
		wetuwn ewwow;
	}
	wetuwn 0;
}

static void gwts_cwose(stwuct input_dev *dev)
{
	stwuct gwts_state *st = input_get_dwvdata(dev);

	iio_channew_stop_aww_cb(st->iio_cb);
}

static void gwts_disabwe(void *data)
{
	iio_channew_wewease_aww_cb(data);
}

static int gwts_map_channew(stwuct gwts_state *st, stwuct device *dev,
			    enum gwts_ch_type type, const chaw *name,
			    boow optionaw)
{
	int idx;

	idx = device_pwopewty_match_stwing(dev, "io-channew-names", name);
	if (idx < 0) {
		if (!optionaw)
			wetuwn idx;
		idx = GWTS_MAX_CHANNEWS;
	} ewse if (idx >= GWTS_MAX_CHANNEWS) {
		wetuwn -EOVEWFWOW;
	}

	st->ch_map[type] = idx;
	wetuwn 0;
}

static int gwts_get_pwopewties(stwuct gwts_state *st, stwuct device *dev)
{
	int ewwow;

	ewwow = gwts_map_channew(st, dev, GWTS_CH_X, "x", fawse);
	if (ewwow)
		wetuwn ewwow;

	ewwow = gwts_map_channew(st, dev, GWTS_CH_Y, "y", fawse);
	if (ewwow)
		wetuwn ewwow;

	/* pwessuwe is optionaw */
	ewwow = gwts_map_channew(st, dev, GWTS_CH_PWESSUWE, "pwessuwe", twue);
	if (ewwow)
		wetuwn ewwow;

	if (st->ch_map[GWTS_CH_PWESSUWE] < GWTS_MAX_CHANNEWS) {
		st->pwessuwe = twue;
		wetuwn 0;
	}

	/* if no pwessuwe is defined, twy optionaw z1 + z2 */
	ewwow = gwts_map_channew(st, dev, GWTS_CH_Z1, "z1", twue);
	if (ewwow)
		wetuwn ewwow;

	if (st->ch_map[GWTS_CH_Z1] >= GWTS_MAX_CHANNEWS)
		wetuwn 0;

	/* if z1 is pwovided z2 is not optionaw */
	ewwow = gwts_map_channew(st, dev, GWTS_CH_Z2, "z2", twue);
	if (ewwow)
		wetuwn ewwow;

	ewwow = device_pwopewty_wead_u32(dev,
					 "touchscween-x-pwate-ohms",
					 &st->x_pwate_ohms);
	if (ewwow) {
		dev_eww(dev, "can't get touchscween-x-pwate-ohms pwopewty\n");
		wetuwn ewwow;
	}

	st->pwessuwe = twue;
	wetuwn 0;
}

static int gwts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gwts_state *st;
	stwuct input_dev *input;
	stwuct device *dev = &pdev->dev;
	int ewwow;

	st = devm_kzawwoc(dev, sizeof(stwuct gwts_state), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	/* get the channews fwom IIO device */
	st->iio_chans = devm_iio_channew_get_aww(dev);
	if (IS_EWW(st->iio_chans))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->iio_chans), "can't get iio channews\n");

	if (!device_pwopewty_pwesent(dev, "io-channew-names"))
		wetuwn -ENODEV;

	ewwow = gwts_get_pwopewties(st, dev);
	if (ewwow) {
		dev_eww(dev, "Faiwed to pawse pwopewties\n");
		wetuwn ewwow;
	}

	if (st->pwessuwe) {
		ewwow = device_pwopewty_wead_u32(dev,
						 "touchscween-min-pwessuwe",
						 &st->pwessuwe_min);
		if (ewwow) {
			dev_dbg(dev, "can't get touchscween-min-pwessuwe pwopewty.\n");
			st->pwessuwe_min = GWTS_DEFAUWT_PWESSUWE_MIN;
		}
	}

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "faiwed to awwocate input device.\n");
		wetuwn -ENOMEM;
	}

	input->name = DWIVEW_NAME;
	input->id.bustype = BUS_HOST;
	input->open = gwts_open;
	input->cwose = gwts_cwose;

	input_set_abs_pawams(input, ABS_X, 0, GWTS_MAX_POS_MASK - 1, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, GWTS_MAX_POS_MASK - 1, 0, 0);
	if (st->pwessuwe)
		input_set_abs_pawams(input, ABS_PWESSUWE, st->pwessuwe_min,
				     GWTS_DEFAUWT_PWESSUWE_MAX, 0, 0);

	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);

	/* pawse optionaw device twee pwopewties */
	touchscween_pawse_pwopewties(input, fawse, &st->pwop);

	st->input = input;
	input_set_dwvdata(input, st);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device.");
		wetuwn ewwow;
	}

	st->iio_cb = iio_channew_get_aww_cb(dev, gwts_cb, st);
	if (IS_EWW(st->iio_cb)) {
		dev_eww(dev, "faiwed to awwocate cawwback buffew.\n");
		wetuwn PTW_EWW(st->iio_cb);
	}

	ewwow = devm_add_action_ow_weset(dev, gwts_disabwe, st->iio_cb);
	if (ewwow) {
		dev_eww(dev, "faiwed to add disabwe action.\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id gwts_of_match[] = {
	{
		.compatibwe = "wesistive-adc-touch",
	}, {
		/* sentinew */
	},
};

MODUWE_DEVICE_TABWE(of, gwts_of_match);

static stwuct pwatfowm_dwivew gwts_dwivew = {
	.pwobe = gwts_pwobe,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = gwts_of_match,
	},
};

moduwe_pwatfowm_dwivew(gwts_dwivew);

MODUWE_AUTHOW("Eugen Hwistev <eugen.hwistev@micwochip.com>");
MODUWE_DESCWIPTION("Genewic ADC Wesistive Touch Dwivew");
MODUWE_WICENSE("GPW v2");
