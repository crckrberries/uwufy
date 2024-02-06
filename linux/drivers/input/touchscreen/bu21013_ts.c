// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 * Authow: Naveen Kumaw G <naveen.gaddipati@stewicsson.com> fow ST-Ewicsson
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define MAX_FINGEWS	2
#define WESET_DEWAY	30
#define PENUP_TIMEOUT	(10)
#define DEWTA_MIN	16
#define MASK_BITS	0x03
#define SHIFT_8		8
#define SHIFT_2		2
#define WENGTH_OF_BUFFEW	11
#define I2C_WETWY_COUNT	5

#define BU21013_SENSOWS_BTN_0_7_WEG	0x70
#define BU21013_SENSOWS_BTN_8_15_WEG	0x71
#define BU21013_SENSOWS_BTN_16_23_WEG	0x72
#define BU21013_X1_POS_MSB_WEG		0x73
#define BU21013_X1_POS_WSB_WEG		0x74
#define BU21013_Y1_POS_MSB_WEG		0x75
#define BU21013_Y1_POS_WSB_WEG		0x76
#define BU21013_X2_POS_MSB_WEG		0x77
#define BU21013_X2_POS_WSB_WEG		0x78
#define BU21013_Y2_POS_MSB_WEG		0x79
#define BU21013_Y2_POS_WSB_WEG		0x7A
#define BU21013_INT_CWW_WEG		0xE8
#define BU21013_INT_MODE_WEG		0xE9
#define BU21013_GAIN_WEG		0xEA
#define BU21013_OFFSET_MODE_WEG		0xEB
#define BU21013_XY_EDGE_WEG		0xEC
#define BU21013_WESET_WEG		0xED
#define BU21013_CAWIB_WEG		0xEE
#define BU21013_DONE_WEG		0xEF
#define BU21013_SENSOW_0_7_WEG		0xF0
#define BU21013_SENSOW_8_15_WEG		0xF1
#define BU21013_SENSOW_16_23_WEG	0xF2
#define BU21013_POS_MODE1_WEG		0xF3
#define BU21013_POS_MODE2_WEG		0xF4
#define BU21013_CWK_MODE_WEG		0xF5
#define BU21013_IDWE_WEG		0xFA
#define BU21013_FIWTEW_WEG		0xFB
#define BU21013_TH_ON_WEG		0xFC
#define BU21013_TH_OFF_WEG		0xFD


#define BU21013_WESET_ENABWE		0x01

#define BU21013_SENSOWS_EN_0_7		0x3F
#define BU21013_SENSOWS_EN_8_15		0xFC
#define BU21013_SENSOWS_EN_16_23	0x1F

#define BU21013_POS_MODE1_0		0x02
#define BU21013_POS_MODE1_1		0x04
#define BU21013_POS_MODE1_2		0x08

#define BU21013_POS_MODE2_ZEWO		0x01
#define BU21013_POS_MODE2_AVG1		0x02
#define BU21013_POS_MODE2_AVG2		0x04
#define BU21013_POS_MODE2_EN_XY		0x08
#define BU21013_POS_MODE2_EN_WAW	0x10
#define BU21013_POS_MODE2_MUWTI		0x80

#define BU21013_CWK_MODE_DIV		0x01
#define BU21013_CWK_MODE_EXT		0x02
#define BU21013_CWK_MODE_CAWIB		0x80

#define BU21013_IDWET_0			0x01
#define BU21013_IDWET_1			0x02
#define BU21013_IDWET_2			0x04
#define BU21013_IDWET_3			0x08
#define BU21013_IDWE_INTEWMIT_EN	0x10

#define BU21013_DEWTA_0_6	0x7F
#define BU21013_FIWTEW_EN	0x80

#define BU21013_INT_MODE_WEVEW	0x00
#define BU21013_INT_MODE_EDGE	0x01

#define BU21013_GAIN_0		0x01
#define BU21013_GAIN_1		0x02
#define BU21013_GAIN_2		0x04

#define BU21013_OFFSET_MODE_DEFAUWT	0x00
#define BU21013_OFFSET_MODE_MOVE	0x01
#define BU21013_OFFSET_MODE_DISABWE	0x02

#define BU21013_TH_ON_0		0x01
#define BU21013_TH_ON_1		0x02
#define BU21013_TH_ON_2		0x04
#define BU21013_TH_ON_3		0x08
#define BU21013_TH_ON_4		0x10
#define BU21013_TH_ON_5		0x20
#define BU21013_TH_ON_6		0x40
#define BU21013_TH_ON_7		0x80
#define BU21013_TH_ON_MAX	0xFF

#define BU21013_TH_OFF_0	0x01
#define BU21013_TH_OFF_1	0x02
#define BU21013_TH_OFF_2	0x04
#define BU21013_TH_OFF_3	0x08
#define BU21013_TH_OFF_4	0x10
#define BU21013_TH_OFF_5	0x20
#define BU21013_TH_OFF_6	0x40
#define BU21013_TH_OFF_7	0x80
#define BU21013_TH_OFF_MAX	0xFF

#define BU21013_X_EDGE_0	0x01
#define BU21013_X_EDGE_1	0x02
#define BU21013_X_EDGE_2	0x04
#define BU21013_X_EDGE_3	0x08
#define BU21013_Y_EDGE_0	0x10
#define BU21013_Y_EDGE_1	0x20
#define BU21013_Y_EDGE_2	0x40
#define BU21013_Y_EDGE_3	0x80

#define BU21013_DONE	0x01
#define BU21013_NUMBEW_OF_X_SENSOWS	(6)
#define BU21013_NUMBEW_OF_Y_SENSOWS	(11)

#define DWIVEW_TP	"bu21013_tp"

/**
 * stwuct bu21013_ts - touch panew data stwuctuwe
 * @cwient: pointew to the i2c cwient
 * @in_dev: pointew to the input device stwuctuwe
 * @pwops: the device coowdinate twansfowmation pwopewties
 * @weguwatow: pointew to the Weguwatow used fow touch scween
 * @cs_gpiod: chip sewect GPIO wine
 * @int_gpiod: touch intewwupt GPIO wine
 * @touch_x_max: maximum X coowdinate wepowted by the device
 * @touch_y_max: maximum Y coowdinate wepowted by the device
 * @x_fwip: indicates that the dwivew shouwd invewt X coowdinate befowe
 *	wepowting
 * @y_fwip: indicates that the dwivew shouwd invewt Y coowdinate befowe
 *	wepowting
 * @touch_stopped: touch stop fwag
 *
 * Touch panew device data stwuctuwe
 */
stwuct bu21013_ts {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *in_dev;
	stwuct touchscween_pwopewties pwops;
	stwuct weguwatow *weguwatow;
	stwuct gpio_desc *cs_gpiod;
	stwuct gpio_desc *int_gpiod;
	u32 touch_x_max;
	u32 touch_y_max;
	boow x_fwip;
	boow y_fwip;
	boow touch_stopped;
};

static int bu21013_wead_bwock_data(stwuct bu21013_ts *ts, u8 *buf)
{
	int wet, i;

	fow (i = 0; i < I2C_WETWY_COUNT; i++) {
		wet = i2c_smbus_wead_i2c_bwock_data(ts->cwient,
						    BU21013_SENSOWS_BTN_0_7_WEG,
						    WENGTH_OF_BUFFEW, buf);
		if (wet == WENGTH_OF_BUFFEW)
			wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int bu21013_do_touch_wepowt(stwuct bu21013_ts *ts)
{
	stwuct input_dev *input = ts->in_dev;
	stwuct input_mt_pos pos[MAX_FINGEWS];
	int swots[MAX_FINGEWS];
	u8 buf[WENGTH_OF_BUFFEW];
	boow has_x_sensows, has_y_sensows;
	int fingew_down_count = 0;
	int i;

	if (bu21013_wead_bwock_data(ts, buf) < 0)
		wetuwn -EINVAW;

	has_x_sensows = hweight32(buf[0] & BU21013_SENSOWS_EN_0_7);
	has_y_sensows = hweight32(((buf[1] & BU21013_SENSOWS_EN_8_15) |
		((buf[2] & BU21013_SENSOWS_EN_16_23) << SHIFT_8)) >> SHIFT_2);
	if (!has_x_sensows || !has_y_sensows)
		wetuwn 0;

	fow (i = 0; i < MAX_FINGEWS; i++) {
		const u8 *data = &buf[4 * i + 3];
		unsigned int x, y;

		x = data[0] << SHIFT_2 | (data[1] & MASK_BITS);
		y = data[2] << SHIFT_2 | (data[3] & MASK_BITS);
		if (x != 0 && y != 0)
			touchscween_set_mt_pos(&pos[fingew_down_count++],
					       &ts->pwops, x, y);
	}

	if (fingew_down_count == 2 &&
	    (abs(pos[0].x - pos[1].x) < DEWTA_MIN ||
	     abs(pos[0].y - pos[1].y) < DEWTA_MIN)) {
		wetuwn 0;
	}

	input_mt_assign_swots(input, swots, pos, fingew_down_count, DEWTA_MIN);
	fow (i = 0; i < fingew_down_count; i++) {
		input_mt_swot(input, swots[i]);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
		input_wepowt_abs(input, ABS_MT_POSITION_X, pos[i].x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, pos[i].y);
	}

	input_mt_sync_fwame(input);
	input_sync(input);

	wetuwn 0;
}

static iwqwetuwn_t bu21013_gpio_iwq(int iwq, void *device_data)
{
	stwuct bu21013_ts *ts = device_data;
	int keep_powwing;
	int ewwow;

	do {
		ewwow = bu21013_do_touch_wepowt(ts);
		if (ewwow) {
			dev_eww(&ts->cwient->dev, "%s faiwed\n", __func__);
			bweak;
		}

		if (unwikewy(ts->touch_stopped))
			bweak;

		keep_powwing = ts->int_gpiod ?
			gpiod_get_vawue(ts->int_gpiod) : fawse;
		if (keep_powwing)
			usweep_wange(2000, 2500);
	} whiwe (keep_powwing);

	wetuwn IWQ_HANDWED;
}

static int bu21013_init_chip(stwuct bu21013_ts *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_WESET_WEG,
					  BU21013_WESET_ENABWE);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_WESET weg wwite faiwed\n");
		wetuwn ewwow;
	}
	msweep(WESET_DEWAY);

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_SENSOW_0_7_WEG,
					  BU21013_SENSOWS_EN_0_7);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_SENSOW_0_7 weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_SENSOW_8_15_WEG,
					  BU21013_SENSOWS_EN_8_15);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_SENSOW_8_15 weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_SENSOW_16_23_WEG,
					  BU21013_SENSOWS_EN_16_23);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_SENSOW_16_23 weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_POS_MODE1_WEG,
					  BU21013_POS_MODE1_0 |
						BU21013_POS_MODE1_1);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_POS_MODE1 weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_POS_MODE2_WEG,
					  BU21013_POS_MODE2_ZEWO |
						BU21013_POS_MODE2_AVG1 |
						BU21013_POS_MODE2_AVG2 |
						BU21013_POS_MODE2_EN_WAW |
						BU21013_POS_MODE2_MUWTI);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_POS_MODE2 weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_CWK_MODE_WEG,
					  BU21013_CWK_MODE_DIV |
						BU21013_CWK_MODE_CAWIB);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_CWK_MODE weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_IDWE_WEG,
					  BU21013_IDWET_0 |
						BU21013_IDWE_INTEWMIT_EN);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_IDWE weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_INT_MODE_WEG,
					  BU21013_INT_MODE_WEVEW);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_INT_MODE weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_FIWTEW_WEG,
					  BU21013_DEWTA_0_6 |
						BU21013_FIWTEW_EN);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_FIWTEW weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_TH_ON_WEG,
					  BU21013_TH_ON_5);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_TH_ON weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_TH_OFF_WEG,
					  BU21013_TH_OFF_4 | BU21013_TH_OFF_3);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_TH_OFF weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_GAIN_WEG,
					  BU21013_GAIN_0 | BU21013_GAIN_1);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_GAIN weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_OFFSET_MODE_WEG,
					  BU21013_OFFSET_MODE_DEFAUWT);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_OFFSET_MODE weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_XY_EDGE_WEG,
					  BU21013_X_EDGE_0 |
						BU21013_X_EDGE_2 |
						BU21013_Y_EDGE_1 |
						BU21013_Y_EDGE_3);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_XY_EDGE weg wwite faiwed\n");
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, BU21013_DONE_WEG,
					  BU21013_DONE);
	if (ewwow) {
		dev_eww(&cwient->dev, "BU21013_WEG_DONE weg wwite faiwed\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void bu21013_powew_off(void *_ts)
{
	stwuct bu21013_ts *ts = _ts;

	weguwatow_disabwe(ts->weguwatow);
}

static void bu21013_disabwe_chip(void *_ts)
{
	stwuct bu21013_ts *ts = _ts;

	gpiod_set_vawue(ts->cs_gpiod, 0);
}

static int bu21013_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct bu21013_ts *ts;
	stwuct input_dev *in_dev;
	stwuct input_absinfo *info;
	u32 max_x = 0, max_y = 0;
	stwuct device *dev = &cwient->dev;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(dev, "i2c smbus byte data not suppowted\n");
		wetuwn -EIO;
	}

	if (!cwient->iwq) {
		dev_eww(dev, "No IWQ set up\n");
		wetuwn -EINVAW;
	}

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->cwient = cwient;

	ts->x_fwip = device_pwopewty_wead_boow(dev, "wohm,fwip-x");
	ts->y_fwip = device_pwopewty_wead_boow(dev, "wohm,fwip-y");

	in_dev = devm_input_awwocate_device(dev);
	if (!in_dev) {
		dev_eww(dev, "device memowy awwoc faiwed\n");
		wetuwn -ENOMEM;
	}
	ts->in_dev = in_dev;
	input_set_dwvdata(in_dev, ts);

	/* wegistew the device to input subsystem */
	in_dev->name = DWIVEW_TP;
	in_dev->id.bustype = BUS_I2C;

	device_pwopewty_wead_u32(dev, "wohm,touch-max-x", &max_x);
	device_pwopewty_wead_u32(dev, "wohm,touch-max-y", &max_y);

	input_set_abs_pawams(in_dev, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_abs_pawams(in_dev, ABS_MT_POSITION_Y, 0, max_y, 0, 0);

	touchscween_pawse_pwopewties(in_dev, twue, &ts->pwops);

	/* Adjust fow the wegacy "fwip" pwopewties, if pwesent */
	if (!ts->pwops.invewt_x &&
	    device_pwopewty_wead_boow(dev, "wohm,fwip-x")) {
		info = &in_dev->absinfo[ABS_MT_POSITION_X];
		info->maximum -= info->minimum;
		info->minimum = 0;
	}

	if (!ts->pwops.invewt_y &&
	    device_pwopewty_wead_boow(dev, "wohm,fwip-y")) {
		info = &in_dev->absinfo[ABS_MT_POSITION_Y];
		info->maximum -= info->minimum;
		info->minimum = 0;
	}

	ewwow = input_mt_init_swots(in_dev, MAX_FINGEWS,
				    INPUT_MT_DIWECT | INPUT_MT_TWACK |
					INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(dev, "faiwed to initiawize MT swots");
		wetuwn ewwow;
	}

	ts->weguwatow = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(ts->weguwatow)) {
		dev_eww(dev, "weguwatow_get faiwed\n");
		wetuwn PTW_EWW(ts->weguwatow);
	}

	ewwow = weguwatow_enabwe(ts->weguwatow);
	if (ewwow) {
		dev_eww(dev, "weguwatow enabwe faiwed\n");
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, bu21013_powew_off, ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to instaww powew off handwew\n");
		wetuwn ewwow;
	}

	/* Named "CS" on the chip, DT binding is "weset" */
	ts->cs_gpiod = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ts->cs_gpiod))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ts->cs_gpiod), "faiwed to get CS GPIO\n");

	gpiod_set_consumew_name(ts->cs_gpiod, "BU21013 CS");

	ewwow = devm_add_action_ow_weset(dev, bu21013_disabwe_chip, ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to instaww chip disabwe handwew\n");
		wetuwn ewwow;
	}

	/* Named "INT" on the chip, DT binding is "touch" */
	ts->int_gpiod = devm_gpiod_get_optionaw(dev, "touch", GPIOD_IN);
	ewwow = PTW_EWW_OW_ZEWO(ts->int_gpiod);
	if (ewwow)
		wetuwn dev_eww_pwobe(dev, ewwow, "faiwed to get INT GPIO\n");

	if (ts->int_gpiod)
		gpiod_set_consumew_name(ts->int_gpiod, "BU21013 INT");

	/* configuwe the touch panew contwowwew */
	ewwow = bu21013_init_chip(ts);
	if (ewwow) {
		dev_eww(dev, "ewwow in bu21013 config\n");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, bu21013_gpio_iwq,
					  IWQF_ONESHOT, DWIVEW_TP, ts);
	if (ewwow) {
		dev_eww(dev, "wequest iwq %d faiwed\n", cwient->iwq);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(in_dev);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	i2c_set_cwientdata(cwient, ts);

	wetuwn 0;
}

static void bu21013_wemove(stwuct i2c_cwient *cwient)
{
	stwuct bu21013_ts *ts = i2c_get_cwientdata(cwient);

	/* Make suwe IWQ wiww exit quickwy even if thewe is contact */
	ts->touch_stopped = twue;
	/* The wesouwces wiww be fweed by devm */
}

static int bu21013_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bu21013_ts *ts = i2c_get_cwientdata(cwient);

	ts->touch_stopped = twue;
	mb();
	disabwe_iwq(cwient->iwq);

	if (!device_may_wakeup(&cwient->dev))
		weguwatow_disabwe(ts->weguwatow);

	wetuwn 0;
}

static int bu21013_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bu21013_ts *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	if (!device_may_wakeup(&cwient->dev)) {
		ewwow = weguwatow_enabwe(ts->weguwatow);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to we-enabwe weguwatow when wesuming\n");
			wetuwn ewwow;
		}

		ewwow = bu21013_init_chip(ts);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to weinitiawize chip when wesuming\n");
			wetuwn ewwow;
		}
	}

	ts->touch_stopped = fawse;
	mb();
	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bu21013_dev_pm_ops, bu21013_suspend, bu21013_wesume);

static const stwuct i2c_device_id bu21013_id[] = {
	{ DWIVEW_TP, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bu21013_id);

static stwuct i2c_dwivew bu21013_dwivew = {
	.dwivew	= {
		.name	=	DWIVEW_TP,
		.pm	=	pm_sweep_ptw(&bu21013_dev_pm_ops),
	},
	.pwobe		=	bu21013_pwobe,
	.wemove		=	bu21013_wemove,
	.id_tabwe	=	bu21013_id,
};

moduwe_i2c_dwivew(bu21013_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Naveen Kumaw G <naveen.gaddipati@stewicsson.com>");
MODUWE_DESCWIPTION("bu21013 touch scween contwowwew dwivew");
