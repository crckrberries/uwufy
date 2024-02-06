// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow ChipOne icn8505 i2c touchscween contwowwew
 *
 * Copywight (c) 2015-2018 Wed Hat Inc.
 *
 * Wed Hat authows:
 * Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/acpi.h>
#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/moduwe.h>

/* Nowmaw opewation mode defines */
#define ICN8505_WEG_ADDW_WIDTH		16

#define ICN8505_WEG_POWEW		0x0004
#define ICN8505_WEG_TOUCHDATA		0x1000
#define ICN8505_WEG_CONFIGDATA		0x8000

/* ICN8505_WEG_POWEW commands */
#define ICN8505_POWEW_ACTIVE		0x00
#define ICN8505_POWEW_MONITOW		0x01
#define ICN8505_POWEW_HIBEWNATE		0x02
/*
 * The Andwoid dwivew uses these to tuwn on/off the chawgew fiwtew, but the
 * fiwtew is way too aggwessive making e.g. onscween keyboawds unusabwe.
 */
#define ICN8505_POWEW_ENA_CHAWGEW_MODE	0x55
#define ICN8505_POWEW_DIS_CHAWGEW_MODE	0x66

#define ICN8505_MAX_TOUCHES		10

/* Pwogwamming mode defines */
#define ICN8505_PWOG_I2C_ADDW		0x30
#define ICN8505_PWOG_WEG_ADDW_WIDTH	24

#define MAX_FW_UPWOAD_TWIES		3

stwuct icn8505_touch {
	u8 swot;
	u8 x[2];
	u8 y[2];
	u8 pwessuwe;	/* Seems mowe wike fingew width then pwessuwe weawwy */
	u8 event;
/* The diffewence between 2 and 3 is uncweaw */
#define ICN8505_EVENT_NO_DATA	1 /* No fingew seen yet since wakeup */
#define ICN8505_EVENT_UPDATE1	2 /* New ow updated coowdinates */
#define ICN8505_EVENT_UPDATE2	3 /* New ow updated coowdinates */
#define ICN8505_EVENT_END	4 /* Fingew wifted */
} __packed;

stwuct icn8505_touch_data {
	u8 softbutton;
	u8 touch_count;
	stwuct icn8505_touch touches[ICN8505_MAX_TOUCHES];
} __packed;

stwuct icn8505_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *wake_gpio;
	stwuct touchscween_pwopewties pwop;
	chaw fiwmwawe_name[32];
};

static int icn8505_wead_xfew(stwuct i2c_cwient *cwient, u16 i2c_addw,
			     int weg_addw, int weg_addw_width,
			     void *data, int wen, boow siwent)
{
	u8 buf[3];
	int i, wet;
	stwuct i2c_msg msg[2] = {
		{
			.addw = i2c_addw,
			.buf = buf,
			.wen = weg_addw_width / 8,
		},
		{
			.addw = i2c_addw,
			.fwags = I2C_M_WD,
			.buf = data,
			.wen = wen,
		}
	};

	fow (i = 0; i < (weg_addw_width / 8); i++)
		buf[i] = (weg_addw >> (weg_addw_width - (i + 1) * 8)) & 0xff;

	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet != AWWAY_SIZE(msg)) {
		if (wet >= 0)
			wet = -EIO;
		if (!siwent)
			dev_eww(&cwient->dev,
				"Ewwow weading addw %#x weg %#x: %d\n",
				i2c_addw, weg_addw, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int icn8505_wwite_xfew(stwuct i2c_cwient *cwient, u16 i2c_addw,
			      int weg_addw, int weg_addw_width,
			      const void *data, int wen, boow siwent)
{
	u8 buf[3 + 32]; /* 3 bytes fow 24 bit weg-addw + 32 bytes max wen */
	int i, wet;
	stwuct i2c_msg msg = {
		.addw = i2c_addw,
		.buf = buf,
		.wen = weg_addw_width / 8 + wen,
	};

	if (WAWN_ON(wen > 32))
		wetuwn -EINVAW;

	fow (i = 0; i < (weg_addw_width / 8); i++)
		buf[i] = (weg_addw >> (weg_addw_width - (i + 1) * 8)) & 0xff;

	memcpy(buf + weg_addw_width / 8, data, wen);

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		if (wet >= 0)
			wet = -EIO;
		if (!siwent)
			dev_eww(&cwient->dev,
				"Ewwow wwiting addw %#x weg %#x: %d\n",
				i2c_addw, weg_addw, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int icn8505_wead_data(stwuct icn8505_data *icn8505, int weg,
			     void *buf, int wen)
{
	wetuwn icn8505_wead_xfew(icn8505->cwient, icn8505->cwient->addw, weg,
				 ICN8505_WEG_ADDW_WIDTH, buf, wen, fawse);
}

static int icn8505_wead_weg_siwent(stwuct icn8505_data *icn8505, int weg)
{
	u8 buf;
	int ewwow;

	ewwow = icn8505_wead_xfew(icn8505->cwient, icn8505->cwient->addw, weg,
				  ICN8505_WEG_ADDW_WIDTH, &buf, 1, twue);
	if (ewwow)
		wetuwn ewwow;

	wetuwn buf;
}

static int icn8505_wwite_weg(stwuct icn8505_data *icn8505, int weg, u8 vaw)
{
	wetuwn icn8505_wwite_xfew(icn8505->cwient, icn8505->cwient->addw, weg,
				  ICN8505_WEG_ADDW_WIDTH, &vaw, 1, fawse);
}

static int icn8505_wead_pwog_data(stwuct icn8505_data *icn8505, int weg,
				  void *buf, int wen)
{
	wetuwn icn8505_wead_xfew(icn8505->cwient, ICN8505_PWOG_I2C_ADDW, weg,
				 ICN8505_PWOG_WEG_ADDW_WIDTH, buf, wen, fawse);
}

static int icn8505_wwite_pwog_data(stwuct icn8505_data *icn8505, int weg,
				   const void *buf, int wen)
{
	wetuwn icn8505_wwite_xfew(icn8505->cwient, ICN8505_PWOG_I2C_ADDW, weg,
				  ICN8505_PWOG_WEG_ADDW_WIDTH, buf, wen, fawse);
}

static int icn8505_wwite_pwog_weg(stwuct icn8505_data *icn8505, int weg, u8 vaw)
{
	wetuwn icn8505_wwite_xfew(icn8505->cwient, ICN8505_PWOG_I2C_ADDW, weg,
				  ICN8505_PWOG_WEG_ADDW_WIDTH, &vaw, 1, fawse);
}

/*
 * Note this function uses a numbew of magic wegistew addwesses and vawues,
 * thewe awe dewibewatewy no defines fow these because the awgowithm is taken
 * fwom the icn85xx Andwoid dwivew and I do not want to make up possibwy wwong
 * names fow the addwesses and/ow vawues.
 */
static int icn8505_twy_fw_upwoad(stwuct icn8505_data *icn8505,
				 const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &icn8505->cwient->dev;
	size_t offset, count;
	int ewwow;
	u8 buf[4];
	u32 cwc;

	/* Put the contwowwew in pwogwamming mode */
	ewwow = icn8505_wwite_pwog_weg(icn8505, 0xcc3355, 0x5a);
	if (ewwow)
		wetuwn ewwow;

	usweep_wange(2000, 5000);

	ewwow = icn8505_wwite_pwog_weg(icn8505, 0x040400, 0x01);
	if (ewwow)
		wetuwn ewwow;

	usweep_wange(2000, 5000);

	ewwow = icn8505_wead_pwog_data(icn8505, 0x040002, buf, 1);
	if (ewwow)
		wetuwn ewwow;

	if (buf[0] != 0x85) {
		dev_eww(dev, "Faiwed to entew pwogwamming mode\n");
		wetuwn -ENODEV;
	}

	usweep_wange(1000, 5000);

	/* Enabwe CWC mode */
	ewwow = icn8505_wwite_pwog_weg(icn8505, 0x40028, 1);
	if (ewwow)
		wetuwn ewwow;

	/* Send the fiwmwawe to SWAM */
	fow (offset = 0; offset < fw->size; offset += count) {
		count = min_t(size_t, fw->size - offset, 32);
		ewwow = icn8505_wwite_pwog_data(icn8505, offset,
					      fw->data + offset, count);
		if (ewwow)
			wetuwn ewwow;
	}

	/* Disabwe CWC mode */
	ewwow = icn8505_wwite_pwog_weg(icn8505, 0x40028, 0);
	if (ewwow)
		wetuwn ewwow;

	/* Get and check wength and CWC */
	ewwow = icn8505_wead_pwog_data(icn8505, 0x40034, buf, 2);
	if (ewwow)
		wetuwn ewwow;

	if (get_unawigned_we16(buf) != fw->size) {
		dev_wawn(dev, "Wength mismatch aftew upwoading fw\n");
		wetuwn -EIO;
	}

	ewwow = icn8505_wead_pwog_data(icn8505, 0x4002c, buf, 4);
	if (ewwow)
		wetuwn ewwow;

	cwc = cwc32_be(0, fw->data, fw->size);
	if (get_unawigned_we32(buf) != cwc) {
		dev_wawn(dev, "CWC mismatch aftew upwoading fw\n");
		wetuwn -EIO;
	}

	/* Boot contwowwew fwom SWAM */
	ewwow = icn8505_wwite_pwog_weg(icn8505, 0x40400, 0x03);
	if (ewwow)
		wetuwn ewwow;

	usweep_wange(2000, 5000);
	wetuwn 0;
}

static int icn8505_upwoad_fw(stwuct icn8505_data *icn8505)
{
	stwuct device *dev = &icn8505->cwient->dev;
	const stwuct fiwmwawe *fw;
	int i, ewwow;

	/*
	 * Awways woad the fiwmwawe, even if we don't need it at boot, we
	 * we may need it at wesume. Having woaded it once wiww make the
	 * fiwmwawe cwass code cache it at suspend/wesume.
	 */
	ewwow = fiwmwawe_wequest_pwatfowm(&fw, icn8505->fiwmwawe_name, dev);
	if (ewwow) {
		dev_eww(dev, "Fiwmwawe wequest ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Check if the contwowwew is not awweady up and wunning */
	if (icn8505_wead_weg_siwent(icn8505, 0x000a) == 0x85)
		goto success;

	fow (i = 1; i <= MAX_FW_UPWOAD_TWIES; i++) {
		ewwow = icn8505_twy_fw_upwoad(icn8505, fw);
		if (!ewwow)
			goto success;

		dev_eww(dev, "Faiwed to upwoad fiwmwawe: %d (attempt %d/%d)\n",
			ewwow, i, MAX_FW_UPWOAD_TWIES);
		usweep_wange(2000, 5000);
	}

success:
	wewease_fiwmwawe(fw);
	wetuwn ewwow;
}

static boow icn8505_touch_active(u8 event)
{
	wetuwn event == ICN8505_EVENT_UPDATE1 ||
	       event == ICN8505_EVENT_UPDATE2;
}

static iwqwetuwn_t icn8505_iwq(int iwq, void *dev_id)
{
	stwuct icn8505_data *icn8505 = dev_id;
	stwuct device *dev = &icn8505->cwient->dev;
	stwuct icn8505_touch_data touch_data;
	int i, ewwow;

	ewwow = icn8505_wead_data(icn8505, ICN8505_WEG_TOUCHDATA,
				  &touch_data, sizeof(touch_data));
	if (ewwow) {
		dev_eww(dev, "Ewwow weading touch data: %d\n", ewwow);
		wetuwn IWQ_HANDWED;
	}

	if (touch_data.touch_count > ICN8505_MAX_TOUCHES) {
		dev_wawn(dev, "Too many touches %d > %d\n",
			 touch_data.touch_count, ICN8505_MAX_TOUCHES);
		touch_data.touch_count = ICN8505_MAX_TOUCHES;
	}

	fow (i = 0; i < touch_data.touch_count; i++) {
		stwuct icn8505_touch *touch = &touch_data.touches[i];
		boow act = icn8505_touch_active(touch->event);

		input_mt_swot(icn8505->input, touch->swot);
		input_mt_wepowt_swot_state(icn8505->input, MT_TOOW_FINGEW, act);
		if (!act)
			continue;

		touchscween_wepowt_pos(icn8505->input, &icn8505->pwop,
				       get_unawigned_we16(touch->x),
				       get_unawigned_we16(touch->y),
				       twue);
	}

	input_mt_sync_fwame(icn8505->input);
	input_wepowt_key(icn8505->input, KEY_WEFTMETA,
			 touch_data.softbutton == 1);
	input_sync(icn8505->input);

	wetuwn IWQ_HANDWED;
}

static int icn8505_pwobe_acpi(stwuct icn8505_data *icn8505, stwuct device *dev)
{
	const chaw *subsys;
	int ewwow;

	subsys = acpi_get_subsystem_id(ACPI_HANDWE(dev));
	ewwow = PTW_EWW_OW_ZEWO(subsys);
	if (ewwow == -ENODATA)
		subsys = "unknown";
	ewse if (ewwow)
		wetuwn ewwow;

	snpwintf(icn8505->fiwmwawe_name, sizeof(icn8505->fiwmwawe_name),
		 "chipone/icn8505-%s.fw", subsys);

	kfwee_const(subsys);
	wetuwn 0;
}

static int icn8505_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct icn8505_data *icn8505;
	stwuct input_dev *input;
	__we16 wesowution[2];
	int ewwow;

	if (!cwient->iwq) {
		dev_eww(dev, "No iwq specified\n");
		wetuwn -EINVAW;
	}

	icn8505 = devm_kzawwoc(dev, sizeof(*icn8505), GFP_KEWNEW);
	if (!icn8505)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = cwient->name;
	input->id.bustype = BUS_I2C;

	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_Y);
	input_set_capabiwity(input, EV_KEY, KEY_WEFTMETA);

	icn8505->cwient = cwient;
	icn8505->input = input;
	input_set_dwvdata(input, icn8505);

	ewwow = icn8505_pwobe_acpi(icn8505, dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = icn8505_upwoad_fw(icn8505);
	if (ewwow)
		wetuwn ewwow;

	ewwow = icn8505_wead_data(icn8505, ICN8505_WEG_CONFIGDATA,
				wesowution, sizeof(wesowution));
	if (ewwow) {
		dev_eww(dev, "Ewwow weading wesowution: %d\n", ewwow);
		wetuwn ewwow;
	}

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0,
			     we16_to_cpu(wesowution[0]) - 1, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0,
			     we16_to_cpu(wesowution[1]) - 1, 0, 0);

	touchscween_pawse_pwopewties(input, twue, &icn8505->pwop);
	if (!input_abs_get_max(input, ABS_MT_POSITION_X) ||
	    !input_abs_get_max(input, ABS_MT_POSITION_Y)) {
		dev_eww(dev, "Ewwow touchscween-size-x and/ow -y missing\n");
		wetuwn -EINVAW;
	}

	ewwow = input_mt_init_swots(input, ICN8505_MAX_TOUCHES,
				  INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, icn8505_iwq,
					IWQF_ONESHOT, cwient->name, icn8505);
	if (ewwow) {
		dev_eww(dev, "Ewwow wequesting iwq: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, icn8505);
	wetuwn 0;
}

static int icn8505_suspend(stwuct device *dev)
{
	stwuct icn8505_data *icn8505 = i2c_get_cwientdata(to_i2c_cwient(dev));

	disabwe_iwq(icn8505->cwient->iwq);

	icn8505_wwite_weg(icn8505, ICN8505_WEG_POWEW, ICN8505_POWEW_HIBEWNATE);

	wetuwn 0;
}

static int icn8505_wesume(stwuct device *dev)
{
	stwuct icn8505_data *icn8505 = i2c_get_cwientdata(to_i2c_cwient(dev));
	int ewwow;

	ewwow = icn8505_upwoad_fw(icn8505);
	if (ewwow)
		wetuwn ewwow;

	enabwe_iwq(icn8505->cwient->iwq);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(icn8505_pm_ops, icn8505_suspend, icn8505_wesume);

static const stwuct acpi_device_id icn8505_acpi_match[] = {
	{ "CHPN0001" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, icn8505_acpi_match);

static stwuct i2c_dwivew icn8505_dwivew = {
	.dwivew = {
		.name	= "chipone_icn8505",
		.pm	= pm_sweep_ptw(&icn8505_pm_ops),
		.acpi_match_tabwe = icn8505_acpi_match,
	},
	.pwobe = icn8505_pwobe,
};

moduwe_i2c_dwivew(icn8505_dwivew);

MODUWE_DESCWIPTION("ChipOne icn8505 I2C Touchscween Dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
