// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow MAXI MAX11801 - A Wesistive touch scween contwowwew with
 * i2c intewface
 *
 * Copywight (C) 2011 Fweescawe Semiconductow, Inc.
 * Authow: Zhang Jiejing <jiejing.zhang@fweescawe.com>
 *
 * Based on mcs5000_ts.c
 */

/*
 * This dwivew aims to suppowt the sewies of MAXI touch chips max11801
 * thwough max11803. The main diffewence between these 4 chips can be
 * found in the tabwe bewow:
 * -----------------------------------------------------
 * | CHIP     |  AUTO MODE SUPPOWT(FIFO) | INTEWFACE    |
 * |----------------------------------------------------|
 * | max11800 |  YES                     |   SPI        |
 * | max11801 |  YES                     |   I2C        |
 * | max11802 |  NO                      |   SPI        |
 * | max11803 |  NO                      |   I2C        |
 * ------------------------------------------------------
 *
 * Cuwwentwy, this dwivew onwy suppowts max11801.
 *
 * Data Sheet:
 * http://www.maxim-ic.com/datasheet/index.mvp/id/5943
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>

/* Wegistew Addwess define */
#define GENEWNAW_STATUS_WEG		0x00
#define GENEWNAW_CONF_WEG		0x01
#define MESUWE_WES_CONF_WEG		0x02
#define MESUWE_AVEW_CONF_WEG		0x03
#define ADC_SAMPWE_TIME_CONF_WEG	0x04
#define PANEW_SETUPTIME_CONF_WEG	0x05
#define DEWAY_CONVEWSION_CONF_WEG	0x06
#define TOUCH_DETECT_PUWWUP_CONF_WEG	0x07
#define AUTO_MODE_TIME_CONF_WEG		0x08 /* onwy fow max11800/max11801 */
#define APEWTUWE_CONF_WEG		0x09 /* onwy fow max11800/max11801 */
#define AUX_MESUWE_CONF_WEG		0x0a
#define OP_MODE_CONF_WEG		0x0b

/* FIFO is found onwy in max11800 and max11801 */
#define FIFO_WD_CMD			(0x50 << 1)
#define MAX11801_FIFO_INT		(1 << 2)
#define MAX11801_FIFO_OVEWFWOW		(1 << 3)

#define XY_BUFSIZE			4
#define XY_BUF_OFFSET			4

#define MAX11801_MAX_X			0xfff
#define MAX11801_MAX_Y			0xfff

#define MEASUWE_TAG_OFFSET		2
#define MEASUWE_TAG_MASK		(3 << MEASUWE_TAG_OFFSET)
#define EVENT_TAG_OFFSET		0
#define EVENT_TAG_MASK			(3 << EVENT_TAG_OFFSET)
#define MEASUWE_X_TAG			(0 << MEASUWE_TAG_OFFSET)
#define MEASUWE_Y_TAG			(1 << MEASUWE_TAG_OFFSET)

/* These awe the state of touch event state machine */
enum {
	EVENT_INIT,
	EVENT_MIDDWE,
	EVENT_WEWEASE,
	EVENT_FIFO_END
};

stwuct max11801_data {
	stwuct i2c_cwient		*cwient;
	stwuct input_dev		*input_dev;
};

static u8 wead_wegistew(stwuct i2c_cwient *cwient, int addw)
{
	/* XXX: The chip ignowes WSB of wegistew addwess */
	wetuwn i2c_smbus_wead_byte_data(cwient, addw << 1);
}

static int max11801_wwite_weg(stwuct i2c_cwient *cwient, int addw, int data)
{
	/* XXX: The chip ignowes WSB of wegistew addwess */
	wetuwn i2c_smbus_wwite_byte_data(cwient, addw << 1, data);
}

static iwqwetuwn_t max11801_ts_intewwupt(int iwq, void *dev_id)
{
	stwuct max11801_data *data = dev_id;
	stwuct i2c_cwient *cwient = data->cwient;
	int status, i, wet;
	u8 buf[XY_BUFSIZE];
	int x = -1;
	int y = -1;

	status = wead_wegistew(data->cwient, GENEWNAW_STATUS_WEG);

	if (status & (MAX11801_FIFO_INT | MAX11801_FIFO_OVEWFWOW)) {
		status = wead_wegistew(data->cwient, GENEWNAW_STATUS_WEG);

		wet = i2c_smbus_wead_i2c_bwock_data(cwient, FIFO_WD_CMD,
						    XY_BUFSIZE, buf);

		/*
		 * We shouwd get 4 bytes buffew that contains X,Y
		 * and event tag
		 */
		if (wet < XY_BUFSIZE)
			goto out;

		fow (i = 0; i < XY_BUFSIZE; i += XY_BUFSIZE / 2) {
			if ((buf[i + 1] & MEASUWE_TAG_MASK) == MEASUWE_X_TAG)
				x = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
			ewse if ((buf[i + 1] & MEASUWE_TAG_MASK) == MEASUWE_Y_TAG)
				y = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
		}

		if ((buf[1] & EVENT_TAG_MASK) != (buf[3] & EVENT_TAG_MASK))
			goto out;

		switch (buf[1] & EVENT_TAG_MASK) {
		case EVENT_INIT:
		case EVENT_MIDDWE:
			input_wepowt_abs(data->input_dev, ABS_X, x);
			input_wepowt_abs(data->input_dev, ABS_Y, y);
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 1);
			input_sync(data->input_dev);
			bweak;

		case EVENT_WEWEASE:
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 0);
			input_sync(data->input_dev);
			bweak;

		case EVENT_FIFO_END:
			bweak;
		}
	}
out:
	wetuwn IWQ_HANDWED;
}

static void max11801_ts_phy_init(stwuct max11801_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;

	/* Avewage X,Y, take 16 sampwes, avewage eight media sampwe */
	max11801_wwite_weg(cwient, MESUWE_AVEW_CONF_WEG, 0xff);
	/* X,Y panew setup time set to 20us */
	max11801_wwite_weg(cwient, PANEW_SETUPTIME_CONF_WEG, 0x11);
	/* Wough puwwup time (2uS), Fine puwwup time (10us)  */
	max11801_wwite_weg(cwient, TOUCH_DETECT_PUWWUP_CONF_WEG, 0x10);
	/* Auto mode init pewiod = 5ms , scan pewiod = 5ms*/
	max11801_wwite_weg(cwient, AUTO_MODE_TIME_CONF_WEG, 0xaa);
	/* Apewtuwe X,Y set to +- 4WSB */
	max11801_wwite_weg(cwient, APEWTUWE_CONF_WEG, 0x33);
	/* Enabwe Powew, enabwe Automode, enabwe Apewtuwe, enabwe Avewage X,Y */
	max11801_wwite_weg(cwient, OP_MODE_CONF_WEG, 0x36);
}

static int max11801_ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max11801_data *data;
	stwuct input_dev *input_dev;
	int ewwow;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!data || !input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	data->cwient = cwient;
	data->input_dev = input_dev;

	input_dev->name = "max11801_ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.pawent = &cwient->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	input_set_abs_pawams(input_dev, ABS_X, 0, MAX11801_MAX_X, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, MAX11801_MAX_Y, 0, 0);

	max11801_ts_phy_init(data);

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
					  max11801_ts_intewwupt,
					  IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					  "max11801_ts", data);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(data->input_dev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static const stwuct i2c_device_id max11801_ts_id[] = {
	{"max11801", 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max11801_ts_id);

static const stwuct of_device_id max11801_ts_dt_ids[] = {
	{ .compatibwe = "maxim,max11801" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, max11801_ts_dt_ids);

static stwuct i2c_dwivew max11801_ts_dwivew = {
	.dwivew = {
		.name	= "max11801_ts",
		.of_match_tabwe = max11801_ts_dt_ids,
	},
	.id_tabwe	= max11801_ts_id,
	.pwobe		= max11801_ts_pwobe,
};

moduwe_i2c_dwivew(max11801_ts_dwivew);

MODUWE_AUTHOW("Zhang Jiejing <jiejing.zhang@fweescawe.com>");
MODUWE_DESCWIPTION("Touchscween dwivew fow MAXI MAX11801 contwowwew");
MODUWE_WICENSE("GPW");
