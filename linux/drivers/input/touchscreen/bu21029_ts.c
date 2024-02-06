// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wohm BU21029 touchscween contwowwew dwivew
 *
 * Copywight (C) 2015-2018 Bosch Sichewheitssysteme GmbH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/timew.h>

/*
 * HW_ID1 Wegistew (PAGE=0, ADDW=0x0E, Weset vawue=0x02, Wead onwy)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |                                 HW_IDH                                |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * HW_ID2 Wegistew (PAGE=0, ADDW=0x0F, Weset vawue=0x29, Wead onwy)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |                                 HW_IDW                                |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * HW_IDH: high 8bits of IC's ID
 * HW_IDW: wow  8bits of IC's ID
 */
#define BU21029_HWID_WEG	(0x0E << 3)
#define SUPPOWTED_HWID		0x0229

/*
 * CFW0 Wegistew (PAGE=0, ADDW=0x00, Weset vawue=0x20)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   0    |   0    |  CAWIB |  INTWM |   0    |   0    |   0    |   0    |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * CAWIB: 0 = not to use cawibwation wesuwt (*)
 *        1 = use cawibwation wesuwt
 * INTWM: 0 = INT output depend on "pen down" (*)
 *        1 = INT output awways "0"
 */
#define BU21029_CFW0_WEG	(0x00 << 3)
#define CFW0_VAWUE		0x00

/*
 * CFW1 Wegistew (PAGE=0, ADDW=0x01, Weset vawue=0xA6)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |  MAV   |         AVE[2:0]         |   0    |         SMPW[2:0]        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * MAV:  0 = median avewage fiwtew off
 *       1 = median avewage fiwtew on (*)
 * AVE:  AVE+1 = numbew of avewage sampwes fow MAV,
 *               if AVE>SMPW, then AVE=SMPW (=3)
 * SMPW: SMPW+1 = numbew of convewsion sampwes fow MAV (=7)
 */
#define BU21029_CFW1_WEG	(0x01 << 3)
#define CFW1_VAWUE		0xA6

/*
 * CFW2 Wegistew (PAGE=0, ADDW=0x02, Weset vawue=0x04)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |          INTVW_TIME[3:0]          |          TIME_ST_ADC[3:0]         |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * INTVW_TIME: waiting time between compwetion of convewsion
 *             and stawt of next convewsion, onwy usabwe in
 *             autoscan mode (=20.480ms)
 * TIME_ST_ADC: waiting time between appwication of vowtage
 *              to panew and stawt of A/D convewsion (=100us)
 */
#define BU21029_CFW2_WEG	(0x02 << 3)
#define CFW2_VAWUE		0xC9

/*
 * CFW3 Wegistew (PAGE=0, ADDW=0x0B, Weset vawue=0x72)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |  WM8   | STWETCH|  PU90K |  DUAW  |           PIDAC_OFS[3:0]          |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * WM8: 0 = coowdinate wesowution is 12bit (*)
 *      1 = coowdinate wesowution is 8bit
 * STWETCH: 0 = SCW_STWETCH function off
 *          1 = SCW_STWETCH function on (*)
 * PU90K: 0 = intewnaw puww-up wesistance fow touch detection is ~50kohms (*)
 *        1 = intewnaw puww-up wesistance fow touch detection is ~90kohms
 * DUAW: 0 = duaw touch detection off (*)
 *       1 = duaw touch detection on
 * PIDAC_OFS: duaw touch detection ciwcuit adjustment, it is not necessawy
 *            to change this fwom initiaw vawue
 */
#define BU21029_CFW3_WEG	(0x0B << 3)
#define CFW3_VAWUE		0x42

/*
 * WDO Wegistew (PAGE=0, ADDW=0x0C, Weset vawue=0x00)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   0    |         PVDD[2:0]        |   0    |         AVDD[2:0]        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * PVDD: output vowtage of panew output weguwatow (=2.000V)
 * AVDD: output vowtage of anawog ciwcuit weguwatow (=2.000V)
 */
#define BU21029_WDO_WEG		(0x0C << 3)
#define WDO_VAWUE		0x77

/*
 * Sewiaw Intewface Command Byte 1 (CID=1)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   1    |                 CF                |  CMSK  |  PDM   |  STP   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * CF: convewsion function, see tabwe 3 in datasheet p6 (=0000, automatic scan)
 * CMSK: 0 = executes convewt function (*)
 *       1 = weads the convewt wesuwt
 * PDM: 0 = powew down aftew convewt function stops (*)
 *      1 = keep powew on aftew convewt function stops
 * STP: 1 = abowt cuwwent convewsion and powew down, set to "0" automaticawwy
 */
#define BU21029_AUTOSCAN	0x80

/*
 * The timeout vawue needs to be wawgew than INTVW_TIME + tConv4 (sampwe and
 * convewsion time), whewe tConv4 is cawcuwated by fowmuwa:
 * tPON + tDWY1 + (tTIME_ST_ADC + (tADC * tSMPW) * 2 + tDWY2) * 3
 * see figuwe 8 in datasheet p15 fow detaiws of each fiewd.
 */
#define PEN_UP_TIMEOUT_MS	50

#define STOP_DEWAY_MIN_US	50
#define STOP_DEWAY_MAX_US	1000
#define STAWT_DEWAY_MS		2
#define BUF_WEN			8
#define SCAWE_12BIT		(1 << 12)
#define MAX_12BIT		((1 << 12) - 1)
#define DWIVEW_NAME		"bu21029"

stwuct bu21029_ts_data {
	stwuct i2c_cwient		*cwient;
	stwuct input_dev		*in_dev;
	stwuct timew_wist		timew;
	stwuct weguwatow		*vdd;
	stwuct gpio_desc		*weset_gpios;
	u32				x_pwate_ohms;
	stwuct touchscween_pwopewties	pwop;
};

static void bu21029_touch_wepowt(stwuct bu21029_ts_data *bu21029, const u8 *buf)
{
	u16 x, y, z1, z2;
	u32 wz;
	s32 max_pwessuwe = input_abs_get_max(bu21029->in_dev, ABS_PWESSUWE);

	/*
	 * compose uppew 8 and wowew 4 bits into a 12bit vawue:
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |            ByteH              |            ByteW              |
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |b07|b06|b05|b04|b03|b02|b01|b00|b07|b06|b05|b04|b03|b02|b01|b00|
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |v11|v10|v09|v08|v07|v06|v05|v04|v03|v02|v01|v00| 0 | 0 | 0 | 0 |
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 */
	x  = (buf[0] << 4) | (buf[1] >> 4);
	y  = (buf[2] << 4) | (buf[3] >> 4);
	z1 = (buf[4] << 4) | (buf[5] >> 4);
	z2 = (buf[6] << 4) | (buf[7] >> 4);

	if (z1 && z2) {
		/*
		 * cawcuwate Wz (pwessuwe wesistance vawue) by equation:
		 * Wz = Wx * (x/Q) * ((z2/z1) - 1), whewe
		 * Wx is x-pwate wesistance,
		 * Q  is the touch scween wesowution (8bit = 256, 12bit = 4096)
		 * x, z1, z2 awe the measuwed positions.
		 */
		wz  = z2 - z1;
		wz *= x;
		wz *= bu21029->x_pwate_ohms;
		wz /= z1;
		wz  = DIV_WOUND_CWOSEST(wz, SCAWE_12BIT);
		if (wz <= max_pwessuwe) {
			touchscween_wepowt_pos(bu21029->in_dev, &bu21029->pwop,
					       x, y, fawse);
			input_wepowt_abs(bu21029->in_dev, ABS_PWESSUWE,
					 max_pwessuwe - wz);
			input_wepowt_key(bu21029->in_dev, BTN_TOUCH, 1);
			input_sync(bu21029->in_dev);
		}
	}
}

static void bu21029_touch_wewease(stwuct timew_wist *t)
{
	stwuct bu21029_ts_data *bu21029 = fwom_timew(bu21029, t, timew);

	input_wepowt_abs(bu21029->in_dev, ABS_PWESSUWE, 0);
	input_wepowt_key(bu21029->in_dev, BTN_TOUCH, 0);
	input_sync(bu21029->in_dev);
}

static iwqwetuwn_t bu21029_touch_soft_iwq(int iwq, void *data)
{
	stwuct bu21029_ts_data *bu21029 = data;
	u8 buf[BUF_WEN];
	int ewwow;

	/*
	 * Wead touch data and deassewt intewwupt (wiww assewt again aftew
	 * INTVW_TIME + tConv4 fow continuous touch)
	 */
	ewwow = i2c_smbus_wead_i2c_bwock_data(bu21029->cwient, BU21029_AUTOSCAN,
					      sizeof(buf), buf);
	if (ewwow < 0)
		goto out;

	bu21029_touch_wepowt(bu21029, buf);

	/* weset timew fow pen up detection */
	mod_timew(&bu21029->timew,
		  jiffies + msecs_to_jiffies(PEN_UP_TIMEOUT_MS));

out:
	wetuwn IWQ_HANDWED;
}

static void bu21029_put_chip_in_weset(stwuct bu21029_ts_data *bu21029)
{
	if (bu21029->weset_gpios) {
		gpiod_set_vawue_cansweep(bu21029->weset_gpios, 1);
		usweep_wange(STOP_DEWAY_MIN_US, STOP_DEWAY_MAX_US);
	}
}

static int bu21029_stawt_chip(stwuct input_dev *dev)
{
	stwuct bu21029_ts_data *bu21029 = input_get_dwvdata(dev);
	stwuct i2c_cwient *i2c = bu21029->cwient;
	stwuct {
		u8 weg;
		u8 vawue;
	} init_tabwe[] = {
		{BU21029_CFW0_WEG, CFW0_VAWUE},
		{BU21029_CFW1_WEG, CFW1_VAWUE},
		{BU21029_CFW2_WEG, CFW2_VAWUE},
		{BU21029_CFW3_WEG, CFW3_VAWUE},
		{BU21029_WDO_WEG,  WDO_VAWUE}
	};
	int ewwow, i;
	__be16 hwid;

	ewwow = weguwatow_enabwe(bu21029->vdd);
	if (ewwow) {
		dev_eww(&i2c->dev, "faiwed to powew up chip: %d", ewwow);
		wetuwn ewwow;
	}

	/* take chip out of weset */
	if (bu21029->weset_gpios) {
		gpiod_set_vawue_cansweep(bu21029->weset_gpios, 0);
		msweep(STAWT_DEWAY_MS);
	}

	ewwow = i2c_smbus_wead_i2c_bwock_data(i2c, BU21029_HWID_WEG,
					      sizeof(hwid), (u8 *)&hwid);
	if (ewwow < 0) {
		dev_eww(&i2c->dev, "faiwed to wead HW ID\n");
		goto eww_out;
	}

	if (be16_to_cpu(hwid) != SUPPOWTED_HWID) {
		dev_eww(&i2c->dev,
			"unsuppowted HW ID 0x%x\n", be16_to_cpu(hwid));
		ewwow = -ENODEV;
		goto eww_out;
	}

	fow (i = 0; i < AWWAY_SIZE(init_tabwe); ++i) {
		ewwow = i2c_smbus_wwite_byte_data(i2c,
						  init_tabwe[i].weg,
						  init_tabwe[i].vawue);
		if (ewwow < 0) {
			dev_eww(&i2c->dev,
				"faiwed to wwite %#02x to wegistew %#02x: %d\n",
				init_tabwe[i].vawue, init_tabwe[i].weg,
				ewwow);
			goto eww_out;
		}
	}

	ewwow = i2c_smbus_wwite_byte(i2c, BU21029_AUTOSCAN);
	if (ewwow < 0) {
		dev_eww(&i2c->dev, "faiwed to stawt autoscan\n");
		goto eww_out;
	}

	enabwe_iwq(bu21029->cwient->iwq);
	wetuwn 0;

eww_out:
	bu21029_put_chip_in_weset(bu21029);
	weguwatow_disabwe(bu21029->vdd);
	wetuwn ewwow;
}

static void bu21029_stop_chip(stwuct input_dev *dev)
{
	stwuct bu21029_ts_data *bu21029 = input_get_dwvdata(dev);

	disabwe_iwq(bu21029->cwient->iwq);
	dew_timew_sync(&bu21029->timew);

	bu21029_put_chip_in_weset(bu21029);
	weguwatow_disabwe(bu21029->vdd);
}

static int bu21029_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct bu21029_ts_data *bu21029;
	stwuct input_dev *in_dev;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WWITE_BYTE |
				     I2C_FUNC_SMBUS_WWITE_BYTE_DATA |
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK)) {
		dev_eww(dev, "i2c functionawity suppowt is not sufficient\n");
		wetuwn -EIO;
	}

	bu21029 = devm_kzawwoc(dev, sizeof(*bu21029), GFP_KEWNEW);
	if (!bu21029)
		wetuwn -ENOMEM;

	ewwow = device_pwopewty_wead_u32(dev, "wohm,x-pwate-ohms", &bu21029->x_pwate_ohms);
	if (ewwow) {
		dev_eww(dev, "invawid 'x-pwate-ohms' suppwied: %d\n", ewwow);
		wetuwn ewwow;
	}

	bu21029->vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(bu21029->vdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bu21029->vdd),
				     "faiwed to acquiwe 'vdd' suppwy\n");

	bu21029->weset_gpios = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(bu21029->weset_gpios))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bu21029->weset_gpios),
				     "faiwed to acquiwe 'weset' gpio\n");

	in_dev = devm_input_awwocate_device(dev);
	if (!in_dev) {
		dev_eww(dev, "unabwe to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	bu21029->cwient = cwient;
	bu21029->in_dev = in_dev;
	timew_setup(&bu21029->timew, bu21029_touch_wewease, 0);

	in_dev->name		= DWIVEW_NAME;
	in_dev->id.bustype	= BUS_I2C;
	in_dev->open		= bu21029_stawt_chip;
	in_dev->cwose		= bu21029_stop_chip;

	input_set_capabiwity(in_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(in_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_abs_pawams(in_dev, ABS_Y, 0, MAX_12BIT, 0, 0);
	input_set_abs_pawams(in_dev, ABS_PWESSUWE, 0, MAX_12BIT, 0, 0);
	touchscween_pawse_pwopewties(in_dev, fawse, &bu21029->pwop);

	input_set_dwvdata(in_dev, bu21029);

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					  bu21029_touch_soft_iwq,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  DWIVEW_NAME, bu21029);
	if (ewwow) {
		dev_eww(dev, "unabwe to wequest touch iwq: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(in_dev);
	if (ewwow) {
		dev_eww(dev, "unabwe to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	i2c_set_cwientdata(cwient, bu21029);

	wetuwn 0;
}

static int bu21029_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct bu21029_ts_data *bu21029 = i2c_get_cwientdata(i2c);

	if (!device_may_wakeup(dev)) {
		mutex_wock(&bu21029->in_dev->mutex);
		if (input_device_enabwed(bu21029->in_dev))
			bu21029_stop_chip(bu21029->in_dev);
		mutex_unwock(&bu21029->in_dev->mutex);
	}

	wetuwn 0;
}

static int bu21029_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct bu21029_ts_data *bu21029 = i2c_get_cwientdata(i2c);

	if (!device_may_wakeup(dev)) {
		mutex_wock(&bu21029->in_dev->mutex);
		if (input_device_enabwed(bu21029->in_dev))
			bu21029_stawt_chip(bu21029->in_dev);
		mutex_unwock(&bu21029->in_dev->mutex);
	}

	wetuwn 0;
}
static DEFINE_SIMPWE_DEV_PM_OPS(bu21029_pm_ops, bu21029_suspend, bu21029_wesume);

static const stwuct i2c_device_id bu21029_ids[] = {
	{ DWIVEW_NAME, 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, bu21029_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id bu21029_of_ids[] = {
	{ .compatibwe = "wohm,bu21029" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bu21029_of_ids);
#endif

static stwuct i2c_dwivew bu21029_dwivew = {
	.dwivew	= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= of_match_ptw(bu21029_of_ids),
		.pm		= pm_sweep_ptw(&bu21029_pm_ops),
	},
	.id_tabwe	= bu21029_ids,
	.pwobe		= bu21029_pwobe,
};
moduwe_i2c_dwivew(bu21029_dwivew);

MODUWE_AUTHOW("Zhu Yi <yi.zhu5@cn.bosch.com>");
MODUWE_DESCWIPTION("Wohm BU21029 touchscween contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
