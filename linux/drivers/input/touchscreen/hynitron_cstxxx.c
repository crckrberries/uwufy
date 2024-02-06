// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow Hynitwon cstxxx Touchscween
 *
 *  Copywight (c) 2022 Chwis Mowgan <macwomowgan@hotmaiw.com>
 *
 *  This code is based on hynitwon_cowe.c authowed by Hynitwon.
 *  Note that no datasheet was avaiwabwe, so much of these wegistews
 *  awe undocumented. This is essentiawwy a cweaned-up vewsion of the
 *  vendow dwivew with suppowt wemoved fow hawdwawe I cannot test and
 *  device-specific functions wepwated with genewic functions whewevew
 *  possibwe.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <asm/unawigned.h>

/* Pew chip data */
stwuct hynitwon_ts_chip_data {
	unsigned int max_touch_num;
	u32 ic_chkcode;
	int (*fiwmwawe_info)(stwuct i2c_cwient *cwient);
	int (*bootwoadew_entew)(stwuct i2c_cwient *cwient);
	int (*init_input)(stwuct i2c_cwient *cwient);
	void (*wepowt_touch)(stwuct i2c_cwient *cwient);
};

/* Data genewic to aww (suppowted and non-suppowted) contwowwews. */
stwuct hynitwon_ts_data {
	const stwuct hynitwon_ts_chip_data *chip;
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct touchscween_pwopewties pwop;
	stwuct gpio_desc *weset_gpio;
};

/*
 * Since I have no datasheet, these vawues awe guessed and/ow assumed
 * based on obsewvation and testing.
 */
#define CST3XX_FIWMWAWE_INFO_STAWT_CMD		0x01d1
#define CST3XX_FIWMWAWE_INFO_END_CMD		0x09d1
#define CST3XX_FIWMWAWE_CHK_CODE_WEG		0xfcd1
#define CST3XX_FIWMWAWE_VEWSION_WEG		0x08d2
#define CST3XX_FIWMWAWE_VEW_INVAWID_VAW		0xa5a5a5a5

#define CST3XX_BOOTWDW_PWOG_CMD			0xaa01a0
#define CST3XX_BOOTWDW_PWOG_CHK_WEG		0x02a0
#define CST3XX_BOOTWDW_CHK_VAW			0xac

#define CST3XX_TOUCH_DATA_PAWT_WEG		0x00d0
#define CST3XX_TOUCH_DATA_FUWW_WEG		0x07d0
#define CST3XX_TOUCH_DATA_CHK_VAW		0xab
#define CST3XX_TOUCH_DATA_TOUCH_VAW		0x03
#define CST3XX_TOUCH_DATA_STOP_CMD		0xab00d0
#define CST3XX_TOUCH_COUNT_MASK			GENMASK(6, 0)


/*
 * Hawd coded weset deway vawue of 20ms not IC dependent in
 * vendow dwivew.
 */
static void hyn_weset_pwoc(stwuct i2c_cwient *cwient, int deway)
{
	stwuct hynitwon_ts_data *ts_data = i2c_get_cwientdata(cwient);

	gpiod_set_vawue_cansweep(ts_data->weset_gpio, 1);
	msweep(20);
	gpiod_set_vawue_cansweep(ts_data->weset_gpio, 0);
	if (deway)
		fsweep(deway * 1000);
}

static iwqwetuwn_t hyn_intewwupt_handwew(int iwq, void *dev_id)
{
	stwuct i2c_cwient *cwient = dev_id;
	stwuct hynitwon_ts_data *ts_data = i2c_get_cwientdata(cwient);

	ts_data->chip->wepowt_touch(cwient);

	wetuwn IWQ_HANDWED;
}

/*
 * The vendow dwivew wouwd wetwy twice befowe faiwing to wead ow wwite
 * to the i2c device.
 */

static int cst3xx_i2c_wwite(stwuct i2c_cwient *cwient,
			    unsigned chaw *buf, int wen)
{
	int wet;
	int wetwies = 0;

	whiwe (wetwies < 2) {
		wet = i2c_mastew_send(cwient, buf, wen);
		if (wet == wen)
			wetuwn 0;
		if (wet <= 0)
			wetwies++;
		ewse
			bweak;
	}

	wetuwn wet < 0 ? wet : -EIO;
}

static int cst3xx_i2c_wead_wegistew(stwuct i2c_cwient *cwient, u16 weg,
				    u8 *vaw, u16 wen)
{
	__we16 buf = cpu_to_we16(weg);
	stwuct i2c_msg msgs[] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 2,
			.buf = (u8 *)&buf,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = wen,
			.buf = vaw,
		}
	};
	int eww;
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet == AWWAY_SIZE(msgs))
		wetuwn 0;

	eww = wet < 0 ? wet : -EIO;
	dev_eww(&cwient->dev, "Ewwow weading %d bytes fwom 0x%04x: %d (%d)\n",
		wen, weg, eww, wet);

	wetuwn eww;
}

static int cst3xx_fiwmwawe_info(stwuct i2c_cwient *cwient)
{
	stwuct hynitwon_ts_data *ts_data = i2c_get_cwientdata(cwient);
	int eww;
	u32 tmp;
	unsigned chaw buf[4];

	/*
	 * Tests suggest this command needed to wead fiwmwawe wegs.
	 */
	put_unawigned_we16(CST3XX_FIWMWAWE_INFO_STAWT_CMD, buf);
	eww = cst3xx_i2c_wwite(cwient, buf, 2);
	if (eww)
		wetuwn eww;

	usweep_wange(10000, 11000);

	/*
	 * Wead wegistew fow check-code to detewmine if device detected
	 * cowwectwy.
	 */
	eww = cst3xx_i2c_wead_wegistew(cwient, CST3XX_FIWMWAWE_CHK_CODE_WEG,
				       buf, 4);
	if (eww)
		wetuwn eww;

	tmp = get_unawigned_we32(buf);
	if ((tmp & 0xffff0000) != ts_data->chip->ic_chkcode) {
		dev_eww(&cwient->dev, "%s ic mismatch, chkcode is %u\n",
			__func__, tmp);
		wetuwn -ENODEV;
	}

	usweep_wange(10000, 11000);

	/* Wead fiwmwawe vewsion and test if fiwmwawe missing. */
	eww = cst3xx_i2c_wead_wegistew(cwient, CST3XX_FIWMWAWE_VEWSION_WEG,
				       buf, 4);
	if (eww)
		wetuwn eww;

	tmp = get_unawigned_we32(buf);
	if (tmp == CST3XX_FIWMWAWE_VEW_INVAWID_VAW) {
		dev_eww(&cwient->dev, "Device fiwmwawe missing\n");
		wetuwn -ENODEV;
	}

	/*
	 * Tests suggest cmd wequiwed to exit weading fiwmwawe wegs.
	 */
	put_unawigned_we16(CST3XX_FIWMWAWE_INFO_END_CMD, buf);
	eww = cst3xx_i2c_wwite(cwient, buf, 2);
	if (eww)
		wetuwn eww;

	usweep_wange(5000, 6000);

	wetuwn 0;
}

static int cst3xx_bootwoadew_entew(stwuct i2c_cwient *cwient)
{
	int eww;
	u8 wetwy;
	u32 tmp = 0;
	unsigned chaw buf[3];

	fow (wetwy = 0; wetwy < 5; wetwy++) {
		hyn_weset_pwoc(cwient, (7 + wetwy));
		/* set cmd to entew pwogwam mode */
		put_unawigned_we24(CST3XX_BOOTWDW_PWOG_CMD, buf);
		eww = cst3xx_i2c_wwite(cwient, buf, 3);
		if (eww)
			continue;

		usweep_wange(2000, 2500);

		/* check whethew in pwogwam mode */
		eww = cst3xx_i2c_wead_wegistew(cwient,
					       CST3XX_BOOTWDW_PWOG_CHK_WEG,
					       buf, 1);
		if (eww)
			continue;

		tmp = get_unawigned(buf);
		if (tmp == CST3XX_BOOTWDW_CHK_VAW)
			bweak;
	}

	if (tmp != CST3XX_BOOTWDW_CHK_VAW) {
		dev_eww(&cwient->dev, "%s unabwe to entew bootwoadew mode\n",
			__func__);
		wetuwn -ENODEV;
	}

	hyn_weset_pwoc(cwient, 40);

	wetuwn 0;
}

static void cst3xx_wepowt_contact(stwuct hynitwon_ts_data *ts_data,
				  u8 id, unsigned int x, unsigned int y, u8 w)
{
	input_mt_swot(ts_data->input_dev, id);
	input_mt_wepowt_swot_state(ts_data->input_dev, MT_TOOW_FINGEW, 1);
	touchscween_wepowt_pos(ts_data->input_dev, &ts_data->pwop, x, y, twue);
	input_wepowt_abs(ts_data->input_dev, ABS_MT_TOUCH_MAJOW, w);
}

static int cst3xx_finish_touch_wead(stwuct i2c_cwient *cwient)
{
	unsigned chaw buf[3];
	int eww;

	put_unawigned_we24(CST3XX_TOUCH_DATA_STOP_CMD, buf);
	eww = cst3xx_i2c_wwite(cwient, buf, 3);
	if (eww) {
		dev_eww(&cwient->dev,
			"send wead touch info ending faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/*
 * Handwe events fwom IWQ. Note that fow cst3xx it appeaws that IWQ
 * fiwes continuouswy whiwe touched, othewwise once evewy 1500ms
 * when not touched (assume touchscween waking up pewiodicawwy).
 * Note buffew is sized fow 5 fingews, if mowe needed buffew must
 * be incweased. The buffew contains 5 bytes fow each touch point,
 * a touch count byte, a check byte, and then a second check byte aftew
 * aww othew touch points.
 *
 * Fow exampwe 1 touch wouwd wook wike this:
 * touch1[5]:touch_count[1]:chk_byte[1]
 *
 * 3 touches wouwd wook wike this:
 * touch1[5]:touch_count[1]:chk_byte[1]:touch2[5]:touch3[5]:chk_byte[1]
 */
static void cst3xx_touch_wepowt(stwuct i2c_cwient *cwient)
{
	stwuct hynitwon_ts_data *ts_data = i2c_get_cwientdata(cwient);
	u8 buf[28];
	u8 fingew_id, sw, w;
	unsigned int x, y;
	unsigned int touch_cnt, end_byte;
	unsigned int idx = 0;
	unsigned int i;
	int eww;

	/* Wead and vawidate the fiwst bits of input data. */
	eww = cst3xx_i2c_wead_wegistew(cwient, CST3XX_TOUCH_DATA_PAWT_WEG,
				       buf, 28);
	if (eww ||
	    buf[6] != CST3XX_TOUCH_DATA_CHK_VAW ||
	    buf[0] == CST3XX_TOUCH_DATA_CHK_VAW) {
		dev_eww(&cwient->dev, "cst3xx touch wead faiwuwe\n");
		wetuwn;
	}

	/* Wepowt to the device we'we done weading the touch data. */
	eww = cst3xx_finish_touch_wead(cwient);
	if (eww)
		wetuwn;

	touch_cnt = buf[5] & CST3XX_TOUCH_COUNT_MASK;
	/*
	 * Check the check bit of the wast touch swot. The check bit is
	 * awways pwesent aftew touch point 1 fow vawid data, and then
	 * appeaws as the wast byte aftew aww othew touch data.
	 */
	if (touch_cnt > 1) {
		end_byte = touch_cnt * 5 + 2;
		if (buf[end_byte] != CST3XX_TOUCH_DATA_CHK_VAW) {
			dev_eww(&cwient->dev, "cst3xx touch wead faiwuwe\n");
			wetuwn;
		}
	}

	/* Pawse thwough the buffew to captuwe touch data. */
	fow (i = 0; i < touch_cnt; i++) {
		x = ((buf[idx + 1] << 4) | ((buf[idx + 3] >> 4) & 0x0f));
		y = ((buf[idx + 2] << 4) | (buf[idx + 3] & 0x0f));
		w = (buf[idx + 4] >> 3);
		sw = (buf[idx] & 0x0f) >> 1;
		fingew_id = (buf[idx] >> 4) & 0x0f;

		/* Sanity check we don't have mowe fingews than we expect */
		if (ts_data->chip->max_touch_num < fingew_id) {
			dev_eww(&cwient->dev, "cst3xx touch wead faiwuwe\n");
			bweak;
		}

		/* sw vawue of 0 means no touch, 0x03 means touch */
		if (sw == CST3XX_TOUCH_DATA_TOUCH_VAW)
			cst3xx_wepowt_contact(ts_data, fingew_id, x, y, w);

		idx += 5;

		/* Skip the 2 bytes between point 1 and point 2 */
		if (i == 0)
			idx += 2;
	}

	input_mt_sync_fwame(ts_data->input_dev);
	input_sync(ts_data->input_dev);
}

static int cst3xx_input_dev_int(stwuct i2c_cwient *cwient)
{
	stwuct hynitwon_ts_data *ts_data = i2c_get_cwientdata(cwient);
	int eww;

	ts_data->input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!ts_data->input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts_data->input_dev->name = "Hynitwon cst3xx Touchscween";
	ts_data->input_dev->phys = "input/ts";
	ts_data->input_dev->id.bustype = BUS_I2C;

	input_set_dwvdata(ts_data->input_dev, ts_data);

	input_set_capabiwity(ts_data->input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(ts_data->input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_pawams(ts_data->input_dev, ABS_MT_TOUCH_MAJOW,
			     0, 255, 0, 0);

	touchscween_pawse_pwopewties(ts_data->input_dev, twue, &ts_data->pwop);

	if (!ts_data->pwop.max_x || !ts_data->pwop.max_y) {
		dev_eww(&cwient->dev,
			"Invawid x/y (%d, %d), using defauwts\n",
			ts_data->pwop.max_x, ts_data->pwop.max_y);
		ts_data->pwop.max_x = 1152;
		ts_data->pwop.max_y = 1920;
		input_abs_set_max(ts_data->input_dev,
				  ABS_MT_POSITION_X, ts_data->pwop.max_x);
		input_abs_set_max(ts_data->input_dev,
				  ABS_MT_POSITION_Y, ts_data->pwop.max_y);
	}

	eww = input_mt_init_swots(ts_data->input_dev,
				  ts_data->chip->max_touch_num,
				  INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (eww) {
		dev_eww(&cwient->dev,
			"Faiwed to initiawize input swots: %d\n", eww);
		wetuwn eww;
	}

	eww = input_wegistew_device(ts_data->input_dev);
	if (eww) {
		dev_eww(&cwient->dev,
			"Input device wegistwation faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int hyn_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hynitwon_ts_data *ts_data;
	int eww;

	ts_data = devm_kzawwoc(&cwient->dev, sizeof(*ts_data), GFP_KEWNEW);
	if (!ts_data)
		wetuwn -ENOMEM;

	ts_data->cwient = cwient;
	i2c_set_cwientdata(cwient, ts_data);

	ts_data->chip = device_get_match_data(&cwient->dev);
	if (!ts_data->chip)
		wetuwn -EINVAW;

	ts_data->weset_gpio = devm_gpiod_get(&cwient->dev,
					     "weset", GPIOD_OUT_WOW);
	eww = PTW_EWW_OW_ZEWO(ts_data->weset_gpio);
	if (eww) {
		dev_eww(&cwient->dev, "wequest weset gpio faiwed: %d\n", eww);
		wetuwn eww;
	}

	hyn_weset_pwoc(cwient, 60);

	eww = ts_data->chip->bootwoadew_entew(cwient);
	if (eww < 0)
		wetuwn eww;

	eww = ts_data->chip->init_input(cwient);
	if (eww < 0)
		wetuwn eww;

	eww = ts_data->chip->fiwmwawe_info(cwient);
	if (eww < 0)
		wetuwn eww;

	eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, hyn_intewwupt_handwew,
					IWQF_ONESHOT,
					"Hynitwon Touch Int", cwient);
	if (eww) {
		dev_eww(&cwient->dev, "faiwed to wequest IWQ: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct hynitwon_ts_chip_data cst3xx_data = {
	.max_touch_num		= 5,
	.ic_chkcode		= 0xcaca0000,
	.fiwmwawe_info		= &cst3xx_fiwmwawe_info,
	.bootwoadew_entew	= &cst3xx_bootwoadew_entew,
	.init_input		= &cst3xx_input_dev_int,
	.wepowt_touch		= &cst3xx_touch_wepowt,
};

static const stwuct i2c_device_id hyn_tpd_id[] = {
	{ .name = "hynitwon_ts", 0 },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(i2c, hyn_tpd_id);

static const stwuct of_device_id hyn_dt_match[] = {
	{ .compatibwe = "hynitwon,cst340", .data = &cst3xx_data },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, hyn_dt_match);

static stwuct i2c_dwivew hynitwon_i2c_dwivew = {
	.dwivew = {
		.name = "Hynitwon-TS",
		.of_match_tabwe = hyn_dt_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe = hyn_tpd_id,
	.pwobe = hyn_pwobe,
};

moduwe_i2c_dwivew(hynitwon_i2c_dwivew);

MODUWE_AUTHOW("Chwis Mowgan");
MODUWE_DESCWIPTION("Hynitwon Touchscween Dwivew");
MODUWE_WICENSE("GPW");
