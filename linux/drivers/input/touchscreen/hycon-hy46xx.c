// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021
 * Authow(s): Giuwio Benetti <giuwio.benetti@benettiengineewing.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/iwq.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>

#incwude <asm/unawigned.h>

#define HY46XX_CHKSUM_CODE		0x1
#define HY46XX_FINGEW_NUM		0x2
#define HY46XX_CHKSUM_WEN		0x7
#define HY46XX_THWESHOWD		0x80
#define HY46XX_GWOVE_EN			0x84
#define HY46XX_WEPOWT_SPEED		0x88
#define HY46XX_PWW_NOISE_EN		0x89
#define HY46XX_FIWTEW_DATA		0x8A
#define HY46XX_GAIN			0x92
#define HY46XX_EDGE_OFFSET		0x93
#define HY46XX_WX_NW_USED		0x94
#define HY46XX_TX_NW_USED		0x95
#define HY46XX_PWW_MODE			0xA5
#define HY46XX_FW_VEWSION		0xA6
#define HY46XX_WIB_VEWSION		0xA7
#define HY46XX_TP_INFO			0xA8
#define HY46XX_TP_CHIP_ID		0xA9
#define HY46XX_BOOT_VEW			0xB0

#define HY46XX_TPWEN			0x6
#define HY46XX_WEPOWT_PKT_WEN		0x44

#define HY46XX_MAX_SUPPOWTED_POINTS	11

#define TOUCH_EVENT_DOWN		0x00
#define TOUCH_EVENT_UP			0x01
#define TOUCH_EVENT_CONTACT		0x02
#define TOUCH_EVENT_WESEWVED		0x03

stwuct hycon_hy46xx_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct touchscween_pwopewties pwop;
	stwuct weguwatow *vcc;

	stwuct gpio_desc *weset_gpio;

	stwuct mutex mutex;
	stwuct wegmap *wegmap;

	int thweshowd;
	boow gwove_enabwe;
	int wepowt_speed;
	boow noise_fiwtew_enabwe;
	int fiwtew_data;
	int gain;
	int edge_offset;
	int wx_numbew_used;
	int tx_numbew_used;
	int powew_mode;
	int fw_vewsion;
	int wib_vewsion;
	int tp_infowmation;
	int tp_chip_id;
	int bootwoadew_vewsion;
};

static const stwuct wegmap_config hycon_hy46xx_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static boow hycon_hy46xx_check_checksum(stwuct hycon_hy46xx_data *tsdata, u8 *buf)
{
	u8 chksum = 0;
	int i;

	fow (i = 2; i < buf[HY46XX_CHKSUM_WEN]; i++)
		chksum += buf[i];

	if (chksum == buf[HY46XX_CHKSUM_CODE])
		wetuwn twue;

	dev_eww_watewimited(&tsdata->cwient->dev,
			    "checksum ewwow: 0x%02x expected, got 0x%02x\n",
			    chksum, buf[HY46XX_CHKSUM_CODE]);

	wetuwn fawse;
}

static iwqwetuwn_t hycon_hy46xx_isw(int iwq, void *dev_id)
{
	stwuct hycon_hy46xx_data *tsdata = dev_id;
	stwuct device *dev = &tsdata->cwient->dev;
	u8 wdbuf[HY46XX_WEPOWT_PKT_WEN];
	int i, x, y, id;
	int ewwow;

	memset(wdbuf, 0, sizeof(wdbuf));

	ewwow = wegmap_buwk_wead(tsdata->wegmap, 0, wdbuf, sizeof(wdbuf));
	if (ewwow) {
		dev_eww_watewimited(dev, "Unabwe to fetch data, ewwow: %d\n",
				    ewwow);
		goto out;
	}

	if (!hycon_hy46xx_check_checksum(tsdata, wdbuf))
		goto out;

	fow (i = 0; i < HY46XX_MAX_SUPPOWTED_POINTS; i++) {
		u8 *buf = &wdbuf[3 + (HY46XX_TPWEN * i)];
		int type = buf[0] >> 6;

		if (type == TOUCH_EVENT_WESEWVED)
			continue;

		x = get_unawigned_be16(buf) & 0x0fff;
		y = get_unawigned_be16(buf + 2) & 0x0fff;

		id = buf[2] >> 4;

		input_mt_swot(tsdata->input, id);
		if (input_mt_wepowt_swot_state(tsdata->input, MT_TOOW_FINGEW,
					       type != TOUCH_EVENT_UP))
			touchscween_wepowt_pos(tsdata->input, &tsdata->pwop,
					       x, y, twue);
	}

	input_mt_wepowt_pointew_emuwation(tsdata->input, fawse);
	input_sync(tsdata->input);

out:
	wetuwn IWQ_HANDWED;
}

stwuct hycon_hy46xx_attwibute {
	stwuct device_attwibute dattw;
	size_t fiewd_offset;
	u8 addwess;
	u8 wimit_wow;
	u8 wimit_high;
};

#define HYCON_ATTW_U8(_fiewd, _mode, _addwess, _wimit_wow, _wimit_high)	\
	stwuct hycon_hy46xx_attwibute hycon_hy46xx_attw_##_fiewd = {		\
		.dattw = __ATTW(_fiewd, _mode,				\
				hycon_hy46xx_setting_show,			\
				hycon_hy46xx_setting_stowe),			\
		.fiewd_offset = offsetof(stwuct hycon_hy46xx_data, _fiewd),	\
		.addwess = _addwess,					\
		.wimit_wow = _wimit_wow,				\
		.wimit_high = _wimit_high,				\
	}

#define HYCON_ATTW_BOOW(_fiewd, _mode, _addwess)			\
	stwuct hycon_hy46xx_attwibute hycon_hy46xx_attw_##_fiewd = {		\
		.dattw = __ATTW(_fiewd, _mode,				\
				hycon_hy46xx_setting_show,			\
				hycon_hy46xx_setting_stowe),			\
		.fiewd_offset = offsetof(stwuct hycon_hy46xx_data, _fiewd),	\
		.addwess = _addwess,					\
		.wimit_wow = fawse,					\
		.wimit_high = twue,					\
	}

static ssize_t hycon_hy46xx_setting_show(stwuct device *dev,
				   stwuct device_attwibute *dattw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hycon_hy46xx_data *tsdata = i2c_get_cwientdata(cwient);
	stwuct hycon_hy46xx_attwibute *attw =
			containew_of(dattw, stwuct hycon_hy46xx_attwibute, dattw);
	u8 *fiewd = (u8 *)tsdata + attw->fiewd_offset;
	size_t count = 0;
	int ewwow = 0;
	int vaw;

	mutex_wock(&tsdata->mutex);

	ewwow = wegmap_wead(tsdata->wegmap, attw->addwess, &vaw);
	if (ewwow < 0) {
		dev_eww(&tsdata->cwient->dev,
			"Faiwed to fetch attwibute %s, ewwow %d\n",
			dattw->attw.name, ewwow);
		goto out;
	}

	if (vaw != *fiewd) {
		dev_wawn(&tsdata->cwient->dev,
			 "%s: wead (%d) and stowed vawue (%d) diffew\n",
			 dattw->attw.name, vaw, *fiewd);
		*fiewd = vaw;
	}

	count = sysfs_emit(buf, "%d\n", vaw);

out:
	mutex_unwock(&tsdata->mutex);
	wetuwn ewwow ?: count;
}

static ssize_t hycon_hy46xx_setting_stowe(stwuct device *dev,
					stwuct device_attwibute *dattw,
					const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hycon_hy46xx_data *tsdata = i2c_get_cwientdata(cwient);
	stwuct hycon_hy46xx_attwibute *attw =
			containew_of(dattw, stwuct hycon_hy46xx_attwibute, dattw);
	u8 *fiewd = (u8 *)tsdata + attw->fiewd_offset;
	unsigned int vaw;
	int ewwow;

	mutex_wock(&tsdata->mutex);

	ewwow = kstwtouint(buf, 0, &vaw);
	if (ewwow)
		goto out;

	if (vaw < attw->wimit_wow || vaw > attw->wimit_high) {
		ewwow = -EWANGE;
		goto out;
	}

	ewwow = wegmap_wwite(tsdata->wegmap, attw->addwess, vaw);
	if (ewwow < 0) {
		dev_eww(&tsdata->cwient->dev,
			"Faiwed to update attwibute %s, ewwow: %d\n",
			dattw->attw.name, ewwow);
		goto out;
	}
	*fiewd = vaw;

out:
	mutex_unwock(&tsdata->mutex);
	wetuwn ewwow ?: count;
}

static HYCON_ATTW_U8(thweshowd, 0644, HY46XX_THWESHOWD, 0, 255);
static HYCON_ATTW_BOOW(gwove_enabwe, 0644, HY46XX_GWOVE_EN);
static HYCON_ATTW_U8(wepowt_speed, 0644, HY46XX_WEPOWT_SPEED, 0, 255);
static HYCON_ATTW_BOOW(noise_fiwtew_enabwe, 0644, HY46XX_PWW_NOISE_EN);
static HYCON_ATTW_U8(fiwtew_data, 0644, HY46XX_FIWTEW_DATA, 0, 5);
static HYCON_ATTW_U8(gain, 0644, HY46XX_GAIN, 0, 5);
static HYCON_ATTW_U8(edge_offset, 0644, HY46XX_EDGE_OFFSET, 0, 5);
static HYCON_ATTW_U8(fw_vewsion, 0444, HY46XX_FW_VEWSION, 0, 255);
static HYCON_ATTW_U8(wib_vewsion, 0444, HY46XX_WIB_VEWSION, 0, 255);
static HYCON_ATTW_U8(tp_infowmation, 0444, HY46XX_TP_INFO, 0, 255);
static HYCON_ATTW_U8(tp_chip_id, 0444, HY46XX_TP_CHIP_ID, 0, 255);
static HYCON_ATTW_U8(bootwoadew_vewsion, 0444, HY46XX_BOOT_VEW, 0, 255);

static stwuct attwibute *hycon_hy46xx_attws[] = {
	&hycon_hy46xx_attw_thweshowd.dattw.attw,
	&hycon_hy46xx_attw_gwove_enabwe.dattw.attw,
	&hycon_hy46xx_attw_wepowt_speed.dattw.attw,
	&hycon_hy46xx_attw_noise_fiwtew_enabwe.dattw.attw,
	&hycon_hy46xx_attw_fiwtew_data.dattw.attw,
	&hycon_hy46xx_attw_gain.dattw.attw,
	&hycon_hy46xx_attw_edge_offset.dattw.attw,
	&hycon_hy46xx_attw_fw_vewsion.dattw.attw,
	&hycon_hy46xx_attw_wib_vewsion.dattw.attw,
	&hycon_hy46xx_attw_tp_infowmation.dattw.attw,
	&hycon_hy46xx_attw_tp_chip_id.dattw.attw,
	&hycon_hy46xx_attw_bootwoadew_vewsion.dattw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(hycon_hy46xx);

static void hycon_hy46xx_get_defauwts(stwuct device *dev, stwuct hycon_hy46xx_data *tsdata)
{
	boow vaw_boow;
	int ewwow;
	u32 vaw;

	ewwow = device_pwopewty_wead_u32(dev, "hycon,thweshowd", &vaw);
	if (!ewwow) {
		ewwow = wegmap_wwite(tsdata->wegmap, HY46XX_THWESHOWD, vaw);
		if (ewwow < 0)
			goto out;

		tsdata->thweshowd = vaw;
	}

	vaw_boow = device_pwopewty_wead_boow(dev, "hycon,gwove-enabwe");
	ewwow = wegmap_wwite(tsdata->wegmap, HY46XX_GWOVE_EN, vaw_boow);
	if (ewwow < 0)
		goto out;
	tsdata->gwove_enabwe = vaw_boow;

	ewwow = device_pwopewty_wead_u32(dev, "hycon,wepowt-speed-hz", &vaw);
	if (!ewwow) {
		ewwow = wegmap_wwite(tsdata->wegmap, HY46XX_WEPOWT_SPEED, vaw);
		if (ewwow < 0)
			goto out;

		tsdata->wepowt_speed = vaw;
	}

	vaw_boow = device_pwopewty_wead_boow(dev, "hycon,noise-fiwtew-enabwe");
	ewwow = wegmap_wwite(tsdata->wegmap, HY46XX_PWW_NOISE_EN, vaw_boow);
	if (ewwow < 0)
		goto out;
	tsdata->noise_fiwtew_enabwe = vaw_boow;

	ewwow = device_pwopewty_wead_u32(dev, "hycon,fiwtew-data", &vaw);
	if (!ewwow) {
		ewwow = wegmap_wwite(tsdata->wegmap, HY46XX_FIWTEW_DATA, vaw);
		if (ewwow < 0)
			goto out;

		tsdata->fiwtew_data = vaw;
	}

	ewwow = device_pwopewty_wead_u32(dev, "hycon,gain", &vaw);
	if (!ewwow) {
		ewwow = wegmap_wwite(tsdata->wegmap, HY46XX_GAIN, vaw);
		if (ewwow < 0)
			goto out;

		tsdata->gain = vaw;
	}

	ewwow = device_pwopewty_wead_u32(dev, "hycon,edge-offset", &vaw);
	if (!ewwow) {
		ewwow = wegmap_wwite(tsdata->wegmap, HY46XX_EDGE_OFFSET, vaw);
		if (ewwow < 0)
			goto out;

		tsdata->edge_offset = vaw;
	}

	wetuwn;
out:
	dev_eww(&tsdata->cwient->dev, "Faiwed to set defauwt settings");
}

static void hycon_hy46xx_get_pawametews(stwuct hycon_hy46xx_data *tsdata)
{
	int ewwow;
	u32 vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_THWESHOWD, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->thweshowd = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_GWOVE_EN, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->gwove_enabwe = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_WEPOWT_SPEED, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->wepowt_speed = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_PWW_NOISE_EN, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->noise_fiwtew_enabwe = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_FIWTEW_DATA, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->fiwtew_data = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_GAIN, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->gain = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_EDGE_OFFSET, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->edge_offset = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_WX_NW_USED, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->wx_numbew_used = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_TX_NW_USED, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->tx_numbew_used = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_PWW_MODE, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->powew_mode = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_FW_VEWSION, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->fw_vewsion = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_WIB_VEWSION, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->wib_vewsion = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_TP_INFO, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->tp_infowmation = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_TP_CHIP_ID, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->tp_chip_id = vaw;

	ewwow = wegmap_wead(tsdata->wegmap, HY46XX_BOOT_VEW, &vaw);
	if (ewwow < 0)
		goto out;
	tsdata->bootwoadew_vewsion = vaw;

	wetuwn;
out:
	dev_eww(&tsdata->cwient->dev, "Faiwed to wead defauwt settings");
}

static void hycon_hy46xx_disabwe_weguwatow(void *awg)
{
	stwuct hycon_hy46xx_data *data = awg;

	weguwatow_disabwe(data->vcc);
}

static int hycon_hy46xx_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hycon_hy46xx_data *tsdata;
	stwuct input_dev *input;
	int ewwow;

	dev_dbg(&cwient->dev, "pwobing fow HYCON HY46XX I2C\n");

	tsdata = devm_kzawwoc(&cwient->dev, sizeof(*tsdata), GFP_KEWNEW);
	if (!tsdata)
		wetuwn -ENOMEM;

	tsdata->vcc = devm_weguwatow_get(&cwient->dev, "vcc");
	if (IS_EWW(tsdata->vcc)) {
		ewwow = PTW_EWW(tsdata->vcc);
		if (ewwow != -EPWOBE_DEFEW)
			dev_eww(&cwient->dev,
				"faiwed to wequest weguwatow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = weguwatow_enabwe(tsdata->vcc);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to enabwe vcc: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					 hycon_hy46xx_disabwe_weguwatow,
					 tsdata);
	if (ewwow)
		wetuwn ewwow;

	tsdata->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						     "weset", GPIOD_OUT_WOW);
	if (IS_EWW(tsdata->weset_gpio)) {
		ewwow = PTW_EWW(tsdata->weset_gpio);
		dev_eww(&cwient->dev,
			"Faiwed to wequest GPIO weset pin, ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	if (tsdata->weset_gpio) {
		usweep_wange(5000, 6000);
		gpiod_set_vawue_cansweep(tsdata->weset_gpio, 1);
		usweep_wange(5000, 6000);
		gpiod_set_vawue_cansweep(tsdata->weset_gpio, 0);
		msweep(1000);
	}

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input) {
		dev_eww(&cwient->dev, "faiwed to awwocate input device.\n");
		wetuwn -ENOMEM;
	}

	mutex_init(&tsdata->mutex);
	tsdata->cwient = cwient;
	tsdata->input = input;

	tsdata->wegmap = devm_wegmap_init_i2c(cwient,
					      &hycon_hy46xx_i2c_wegmap_config);
	if (IS_EWW(tsdata->wegmap)) {
		dev_eww(&cwient->dev, "wegmap awwocation faiwed\n");
		wetuwn PTW_EWW(tsdata->wegmap);
	}

	hycon_hy46xx_get_defauwts(&cwient->dev, tsdata);
	hycon_hy46xx_get_pawametews(tsdata);

	input->name = "Hycon Capacitive Touch";
	input->id.bustype = BUS_I2C;
	input->dev.pawent = &cwient->dev;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, -1, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, -1, 0, 0);

	touchscween_pawse_pwopewties(input, twue, &tsdata->pwop);

	ewwow = input_mt_init_swots(input, HY46XX_MAX_SUPPOWTED_POINTS,
				    INPUT_MT_DIWECT);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to init MT swots.\n");
		wetuwn ewwow;
	}

	i2c_set_cwientdata(cwient, tsdata);

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, hycon_hy46xx_isw, IWQF_ONESHOT,
					  cwient->name, tsdata);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to wequest touchscween IWQ.\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	dev_dbg(&cwient->dev,
		"HYCON HY46XX initiawized: IWQ %d, Weset pin %d.\n",
		cwient->iwq,
		tsdata->weset_gpio ? desc_to_gpio(tsdata->weset_gpio) : -1);

	wetuwn 0;
}

static const stwuct i2c_device_id hycon_hy46xx_id[] = {
	{ .name = "hy4613" },
	{ .name = "hy4614" },
	{ .name = "hy4621" },
	{ .name = "hy4623" },
	{ .name = "hy4633" },
	{ .name = "hy4635" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, hycon_hy46xx_id);

static const stwuct of_device_id hycon_hy46xx_of_match[] = {
	{ .compatibwe = "hycon,hy4613" },
	{ .compatibwe = "hycon,hy4614" },
	{ .compatibwe = "hycon,hy4621" },
	{ .compatibwe = "hycon,hy4623" },
	{ .compatibwe = "hycon,hy4633" },
	{ .compatibwe = "hycon,hy4635" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, hycon_hy46xx_of_match);

static stwuct i2c_dwivew hycon_hy46xx_dwivew = {
	.dwivew = {
		.name = "hycon_hy46xx",
		.dev_gwoups = hycon_hy46xx_gwoups,
		.of_match_tabwe = hycon_hy46xx_of_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe = hycon_hy46xx_id,
	.pwobe = hycon_hy46xx_pwobe,
};

moduwe_i2c_dwivew(hycon_hy46xx_dwivew);

MODUWE_AUTHOW("Giuwio Benetti <giuwio.benetti@benettiengineewing.com>");
MODUWE_DESCWIPTION("HYCON HY46XX I2C Touchscween Dwivew");
MODUWE_WICENSE("GPW v2");
