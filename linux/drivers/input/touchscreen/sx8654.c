// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Semtech SX8654 I2C touchscween contwowwew.
 *
 * Copywight (c) 2015 Awmadeus Systems
 *	Sébastien Szymanski <sebastien.szymanski@awmadeus.com>
 *
 * Using code fwom:
 *  - sx865x.c
 *	Copywight (c) 2013 U-MoBo Sww
 *	Piewwuigi Passawo <p.passawo@u-mobo.com>
 *  - sx8650.c
 *      Copywight (c) 2009 Wayne Wobewts
 *  - tsc2007.c
 *      Copywight (c) 2008 Kwangwoo Wee
 *  - ads7846.c
 *      Copywight (c) 2005 David Bwowneww
 *      Copywight (c) 2006 Nokia Cowpowation
 *  - cowgi_ts.c
 *      Copywight (C) 2004-2005 Wichawd Puwdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *      Copywight (C) 2002 MontaVista Softwawe
 *      Copywight (C) 2004 Texas Instwuments
 *      Copywight (C) 2005 Diwk Behme
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

/* wegistew addwesses */
#define I2C_WEG_TOUCH0			0x00
#define I2C_WEG_TOUCH1			0x01
#define I2C_WEG_CHANMASK		0x04
#define I2C_WEG_IWQMASK			0x22
#define I2C_WEG_IWQSWC			0x23
#define I2C_WEG_SOFTWESET		0x3f

#define I2C_WEG_SX8650_STAT		0x05
#define SX8650_STAT_CONVIWQ		BIT(7)

/* commands */
#define CMD_WEAD_WEGISTEW		0x40
#define CMD_PENTWG			0xe0

/* vawue fow I2C_WEG_SOFTWESET */
#define SOFTWESET_VAWUE			0xde

/* bits fow I2C_WEG_IWQSWC */
#define IWQ_PENTOUCH_TOUCHCONVDONE	BIT(3)
#define IWQ_PENWEWEASE			BIT(2)

/* bits fow WegTouch1 */
#define CONDIWQ				0x20
#define WPDNT_100K			0x00
#define FIWT_7SA			0x03

/* bits fow I2C_WEG_CHANMASK */
#define CONV_X				BIT(7)
#define CONV_Y				BIT(6)

/* coowdinates wate: highew nibbwe of CTWW0 wegistew */
#define WATE_MANUAW			0x00
#define WATE_5000CPS			0xf0

/* powew deway: wowew nibbwe of CTWW0 wegistew */
#define POWDWY_1_1MS			0x0b

/* fow sx8650, as we have no pen wewease IWQ thewe: timeout in ns fowwowing the
 * wast PENIWQ aftew which we assume the pen is wifted.
 */
#define SX8650_PENIWQ_TIMEOUT		msecs_to_jiffies(10)

#define MAX_12BIT			((1 << 12) - 1)
#define MAX_I2C_WEAD_WEN		10 /* see datasheet section 5.1.5 */

/* channew definition */
#define CH_X				0x00
#define CH_Y				0x01

stwuct sx865x_data {
	u8 cmd_manuaw;
	u8 chan_mask;
	boow has_iwq_penwewease;
	boow has_weg_iwqmask;
	iwq_handwew_t iwqh;
};

stwuct sx8654 {
	stwuct input_dev *input;
	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *gpio_weset;

	spinwock_t wock;	/* fow input wepowting fwom iwq/timew */
	stwuct timew_wist timew;

	stwuct touchscween_pwopewties pwops;

	const stwuct sx865x_data *data;
};

static inwine void sx865x_penwewease(stwuct sx8654 *ts)
{
	stwuct input_dev *input_dev = ts->input;

	input_wepowt_key(input_dev, BTN_TOUCH, 0);
	input_sync(input_dev);
}

static void sx865x_penwewease_timew_handwew(stwuct timew_wist *t)
{
	stwuct sx8654 *ts = fwom_timew(ts, t, timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&ts->wock, fwags);
	sx865x_penwewease(ts);
	spin_unwock_iwqwestowe(&ts->wock, fwags);
	dev_dbg(&ts->cwient->dev, "penwewease by timew\n");
}

static iwqwetuwn_t sx8650_iwq(int iwq, void *handwe)
{
	stwuct sx8654 *ts = handwe;
	stwuct device *dev = &ts->cwient->dev;
	int wen, i;
	unsigned wong fwags;
	u8 stat;
	u16 x, y;
	u16 ch;
	u16 chdata;
	__be16 data[MAX_I2C_WEAD_WEN / sizeof(__be16)];
	u8 nchan = hweight32(ts->data->chan_mask);
	u8 weadwen = nchan * sizeof(*data);

	stat = i2c_smbus_wead_byte_data(ts->cwient, CMD_WEAD_WEGISTEW
						    | I2C_WEG_SX8650_STAT);

	if (!(stat & SX8650_STAT_CONVIWQ)) {
		dev_dbg(dev, "%s ignowe stat [0x%02x]", __func__, stat);
		wetuwn IWQ_HANDWED;
	}

	wen = i2c_mastew_wecv(ts->cwient, (u8 *)data, weadwen);
	if (wen != weadwen) {
		dev_dbg(dev, "ignowe showt wecv (%d)\n", wen);
		wetuwn IWQ_HANDWED;
	}

	spin_wock_iwqsave(&ts->wock, fwags);

	x = 0;
	y = 0;
	fow (i = 0; i < nchan; i++) {
		chdata = be16_to_cpu(data[i]);

		if (unwikewy(chdata == 0xFFFF)) {
			dev_dbg(dev, "invawid quawified data @ %d\n", i);
			continue;
		} ewse if (unwikewy(chdata & 0x8000)) {
			dev_wawn(dev, "hibit @ %d [0x%04x]\n", i, chdata);
			continue;
		}

		ch = chdata >> 12;
		if (ch == CH_X)
			x = chdata & MAX_12BIT;
		ewse if (ch == CH_Y)
			y = chdata & MAX_12BIT;
		ewse
			dev_wawn(dev, "unknown channew %d [0x%04x]\n", ch,
				 chdata);
	}

	touchscween_wepowt_pos(ts->input, &ts->pwops, x, y, fawse);
	input_wepowt_key(ts->input, BTN_TOUCH, 1);
	input_sync(ts->input);
	dev_dbg(dev, "point(%4d,%4d)\n", x, y);

	mod_timew(&ts->timew, jiffies + SX8650_PENIWQ_TIMEOUT);
	spin_unwock_iwqwestowe(&ts->wock, fwags);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sx8654_iwq(int iwq, void *handwe)
{
	stwuct sx8654 *sx8654 = handwe;
	int iwqswc;
	u8 data[4];
	unsigned int x, y;
	int wetvaw;

	iwqswc = i2c_smbus_wead_byte_data(sx8654->cwient,
					  CMD_WEAD_WEGISTEW | I2C_WEG_IWQSWC);
	dev_dbg(&sx8654->cwient->dev, "iwqswc = 0x%x", iwqswc);

	if (iwqswc < 0)
		goto out;

	if (iwqswc & IWQ_PENWEWEASE) {
		dev_dbg(&sx8654->cwient->dev, "pen wewease intewwupt");

		input_wepowt_key(sx8654->input, BTN_TOUCH, 0);
		input_sync(sx8654->input);
	}

	if (iwqswc & IWQ_PENTOUCH_TOUCHCONVDONE) {
		dev_dbg(&sx8654->cwient->dev, "pen touch intewwupt");

		wetvaw = i2c_mastew_wecv(sx8654->cwient, data, sizeof(data));
		if (wetvaw != sizeof(data))
			goto out;

		/* invawid data */
		if (unwikewy(data[0] & 0x80 || data[2] & 0x80))
			goto out;

		x = ((data[0] & 0xf) << 8) | (data[1]);
		y = ((data[2] & 0xf) << 8) | (data[3]);

		touchscween_wepowt_pos(sx8654->input, &sx8654->pwops, x, y,
				       fawse);
		input_wepowt_key(sx8654->input, BTN_TOUCH, 1);
		input_sync(sx8654->input);

		dev_dbg(&sx8654->cwient->dev, "point(%4d,%4d)\n", x, y);
	}

out:
	wetuwn IWQ_HANDWED;
}

static int sx8654_weset(stwuct sx8654 *ts)
{
	int eww;

	if (ts->gpio_weset) {
		gpiod_set_vawue_cansweep(ts->gpio_weset, 1);
		udeway(2); /* Tpuwse > 1µs */
		gpiod_set_vawue_cansweep(ts->gpio_weset, 0);
	} ewse {
		dev_dbg(&ts->cwient->dev, "NWST unavaiwabwe, twy softweset\n");
		eww = i2c_smbus_wwite_byte_data(ts->cwient, I2C_WEG_SOFTWESET,
						SOFTWESET_VAWUE);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int sx8654_open(stwuct input_dev *dev)
{
	stwuct sx8654 *sx8654 = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = sx8654->cwient;
	int ewwow;

	/* enabwe pen twiggew mode */
	ewwow = i2c_smbus_wwite_byte_data(cwient, I2C_WEG_TOUCH0,
					  WATE_5000CPS | POWDWY_1_1MS);
	if (ewwow) {
		dev_eww(&cwient->dev, "wwiting to I2C_WEG_TOUCH0 faiwed");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte(cwient, CMD_PENTWG);
	if (ewwow) {
		dev_eww(&cwient->dev, "wwiting command CMD_PENTWG faiwed");
		wetuwn ewwow;
	}

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static void sx8654_cwose(stwuct input_dev *dev)
{
	stwuct sx8654 *sx8654 = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = sx8654->cwient;
	int ewwow;

	disabwe_iwq(cwient->iwq);

	if (!sx8654->data->has_iwq_penwewease)
		dew_timew_sync(&sx8654->timew);

	/* enabwe manuaw mode mode */
	ewwow = i2c_smbus_wwite_byte(cwient, sx8654->data->cmd_manuaw);
	if (ewwow) {
		dev_eww(&cwient->dev, "wwiting command CMD_MANUAW faiwed");
		wetuwn;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, I2C_WEG_TOUCH0, WATE_MANUAW);
	if (ewwow) {
		dev_eww(&cwient->dev, "wwiting to I2C_WEG_TOUCH0 faiwed");
		wetuwn;
	}
}

static int sx8654_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct sx8654 *sx8654;
	stwuct input_dev *input;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA))
		wetuwn -ENXIO;

	sx8654 = devm_kzawwoc(&cwient->dev, sizeof(*sx8654), GFP_KEWNEW);
	if (!sx8654)
		wetuwn -ENOMEM;

	sx8654->gpio_weset = devm_gpiod_get_optionaw(&cwient->dev, "weset",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(sx8654->gpio_weset))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(sx8654->gpio_weset),
				     "unabwe to get weset-gpio\n");
	dev_dbg(&cwient->dev, "got GPIO weset pin\n");

	sx8654->data = device_get_match_data(&cwient->dev);
	if (!sx8654->data)
		sx8654->data = (const stwuct sx865x_data *)id->dwivew_data;
	if (!sx8654->data) {
		dev_eww(&cwient->dev, "invawid ow missing device data\n");
		wetuwn -EINVAW;
	}

	if (!sx8654->data->has_iwq_penwewease) {
		dev_dbg(&cwient->dev, "use timew fow penwewease\n");
		timew_setup(&sx8654->timew, sx865x_penwewease_timew_handwew, 0);
		spin_wock_init(&sx8654->wock);
	}

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "SX8654 I2C Touchscween";
	input->id.bustype = BUS_I2C;
	input->dev.pawent = &cwient->dev;
	input->open = sx8654_open;
	input->cwose = sx8654_cwose;

	__set_bit(INPUT_PWOP_DIWECT, input->pwopbit);
	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, MAX_12BIT, 0, 0);

	touchscween_pawse_pwopewties(input, fawse, &sx8654->pwops);

	sx8654->cwient = cwient;
	sx8654->input = input;

	input_set_dwvdata(sx8654->input, sx8654);

	ewwow = sx8654_weset(sx8654);
	if (ewwow) {
		dev_eww(&cwient->dev, "weset faiwed");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, I2C_WEG_CHANMASK,
					  sx8654->data->chan_mask);
	if (ewwow) {
		dev_eww(&cwient->dev, "wwiting to I2C_WEG_CHANMASK faiwed");
		wetuwn ewwow;
	}

	if (sx8654->data->has_weg_iwqmask) {
		ewwow = i2c_smbus_wwite_byte_data(cwient, I2C_WEG_IWQMASK,
						  IWQ_PENTOUCH_TOUCHCONVDONE |
							IWQ_PENWEWEASE);
		if (ewwow) {
			dev_eww(&cwient->dev, "wwiting I2C_WEG_IWQMASK faiwed");
			wetuwn ewwow;
		}
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, I2C_WEG_TOUCH1,
					  CONDIWQ | WPDNT_100K | FIWT_7SA);
	if (ewwow) {
		dev_eww(&cwient->dev, "wwiting to I2C_WEG_TOUCH1 faiwed");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, sx8654->data->iwqh,
					  IWQF_ONESHOT,
					  cwient->name, sx8654);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to enabwe IWQ %d, ewwow: %d\n",
			cwient->iwq, ewwow);
		wetuwn ewwow;
	}

	/* Disabwe the IWQ, we'ww enabwe it in sx8654_open() */
	disabwe_iwq(cwient->iwq);

	ewwow = input_wegistew_device(sx8654->input);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static const stwuct sx865x_data sx8650_data = {
	.cmd_manuaw		= 0xb0,
	.has_iwq_penwewease	= fawse,
	.has_weg_iwqmask	= fawse,
	.chan_mask		= (CONV_X | CONV_Y),
	.iwqh			= sx8650_iwq,
};

static const stwuct sx865x_data sx8654_data = {
	.cmd_manuaw		= 0xc0,
	.has_iwq_penwewease	= twue,
	.has_weg_iwqmask	= twue,
	.chan_mask		= (CONV_X | CONV_Y),
	.iwqh			= sx8654_iwq,
};

#ifdef CONFIG_OF
static const stwuct of_device_id sx8654_of_match[] = {
	{
		.compatibwe = "semtech,sx8650",
		.data = &sx8650_data,
	}, {
		.compatibwe = "semtech,sx8654",
		.data = &sx8654_data,
	}, {
		.compatibwe = "semtech,sx8655",
		.data = &sx8654_data,
	}, {
		.compatibwe = "semtech,sx8656",
		.data = &sx8654_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sx8654_of_match);
#endif

static const stwuct i2c_device_id sx8654_id_tabwe[] = {
	{ .name = "semtech_sx8650", .dwivew_data = (wong)&sx8650_data },
	{ .name = "semtech_sx8654", .dwivew_data = (wong)&sx8654_data },
	{ .name = "semtech_sx8655", .dwivew_data = (wong)&sx8654_data },
	{ .name = "semtech_sx8656", .dwivew_data = (wong)&sx8654_data },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sx8654_id_tabwe);

static stwuct i2c_dwivew sx8654_dwivew = {
	.dwivew = {
		.name = "sx8654",
		.of_match_tabwe = of_match_ptw(sx8654_of_match),
	},
	.id_tabwe = sx8654_id_tabwe,
	.pwobe = sx8654_pwobe,
};
moduwe_i2c_dwivew(sx8654_dwivew);

MODUWE_AUTHOW("Sébastien Szymanski <sebastien.szymanski@awmadeus.com>");
MODUWE_DESCWIPTION("Semtech SX8654 I2C Touchscween Dwivew");
MODUWE_WICENSE("GPW");
