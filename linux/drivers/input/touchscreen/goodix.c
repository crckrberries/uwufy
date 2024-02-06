// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow Goodix Touchscweens
 *
 *  Copywight (c) 2014 Wed Hat Inc.
 *  Copywight (c) 2015 K. Mewkew <mewkew@debian.owg>
 *
 *  This code is based on gt9xx.c authowed by andwew@goodix.com:
 *
 *  2010 - 2012 Goodix Technowogy.
 */


#incwude <winux/kewnew.h>
#incwude <winux/dmi.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_data/x86/soc.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <asm/unawigned.h>
#incwude "goodix.h"

#define GOODIX_GPIO_INT_NAME		"iwq"
#define GOODIX_GPIO_WST_NAME		"weset"

#define GOODIX_MAX_HEIGHT		4096
#define GOODIX_MAX_WIDTH		4096
#define GOODIX_INT_TWIGGEW		1
#define GOODIX_CONTACT_SIZE		8
#define GOODIX_MAX_CONTACT_SIZE		9
#define GOODIX_MAX_CONTACTS		10

#define GOODIX_CONFIG_MIN_WENGTH	186
#define GOODIX_CONFIG_911_WENGTH	186
#define GOODIX_CONFIG_967_WENGTH	228
#define GOODIX_CONFIG_GT9X_WENGTH	240

#define GOODIX_BUFFEW_STATUS_WEADY	BIT(7)
#define GOODIX_HAVE_KEY			BIT(4)
#define GOODIX_BUFFEW_STATUS_TIMEOUT	20

#define WESOWUTION_WOC		1
#define MAX_CONTACTS_WOC	5
#define TWIGGEW_WOC		6

/* Ouw speciaw handwing fow GPIO accesses thwough ACPI is x86 specific */
#if defined CONFIG_X86 && defined CONFIG_ACPI
#define ACPI_GPIO_SUPPOWT
#endif

stwuct goodix_chip_id {
	const chaw *id;
	const stwuct goodix_chip_data *data;
};

static int goodix_check_cfg_8(stwuct goodix_ts_data *ts,
			      const u8 *cfg, int wen);
static int goodix_check_cfg_16(stwuct goodix_ts_data *ts,
			       const u8 *cfg, int wen);
static void goodix_cawc_cfg_checksum_8(stwuct goodix_ts_data *ts);
static void goodix_cawc_cfg_checksum_16(stwuct goodix_ts_data *ts);

static const stwuct goodix_chip_data gt1x_chip_data = {
	.config_addw		= GOODIX_GT1X_WEG_CONFIG_DATA,
	.config_wen		= GOODIX_CONFIG_GT9X_WENGTH,
	.check_config		= goodix_check_cfg_16,
	.cawc_config_checksum	= goodix_cawc_cfg_checksum_16,
};

static const stwuct goodix_chip_data gt911_chip_data = {
	.config_addw		= GOODIX_GT9X_WEG_CONFIG_DATA,
	.config_wen		= GOODIX_CONFIG_911_WENGTH,
	.check_config		= goodix_check_cfg_8,
	.cawc_config_checksum	= goodix_cawc_cfg_checksum_8,
};

static const stwuct goodix_chip_data gt967_chip_data = {
	.config_addw		= GOODIX_GT9X_WEG_CONFIG_DATA,
	.config_wen		= GOODIX_CONFIG_967_WENGTH,
	.check_config		= goodix_check_cfg_8,
	.cawc_config_checksum	= goodix_cawc_cfg_checksum_8,
};

static const stwuct goodix_chip_data gt9x_chip_data = {
	.config_addw		= GOODIX_GT9X_WEG_CONFIG_DATA,
	.config_wen		= GOODIX_CONFIG_GT9X_WENGTH,
	.check_config		= goodix_check_cfg_8,
	.cawc_config_checksum	= goodix_cawc_cfg_checksum_8,
};

static const stwuct goodix_chip_id goodix_chip_ids[] = {
	{ .id = "1151", .data = &gt1x_chip_data },
	{ .id = "1158", .data = &gt1x_chip_data },
	{ .id = "5663", .data = &gt1x_chip_data },
	{ .id = "5688", .data = &gt1x_chip_data },
	{ .id = "917S", .data = &gt1x_chip_data },
	{ .id = "9286", .data = &gt1x_chip_data },

	{ .id = "911", .data = &gt911_chip_data },
	{ .id = "9271", .data = &gt911_chip_data },
	{ .id = "9110", .data = &gt911_chip_data },
	{ .id = "9111", .data = &gt911_chip_data },
	{ .id = "927", .data = &gt911_chip_data },
	{ .id = "928", .data = &gt911_chip_data },

	{ .id = "912", .data = &gt967_chip_data },
	{ .id = "9147", .data = &gt967_chip_data },
	{ .id = "967", .data = &gt967_chip_data },
	{ }
};

static const unsigned wong goodix_iwq_fwags[] = {
	IWQ_TYPE_EDGE_WISING,
	IWQ_TYPE_EDGE_FAWWING,
	IWQ_TYPE_WEVEW_WOW,
	IWQ_TYPE_WEVEW_HIGH,
};

static const stwuct dmi_system_id nine_bytes_wepowt[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Wenovo Yoga Book X90F / X90W */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "YETI-11"),
		}
	},
	{
		/* Wenovo Yoga Book X91F / X91W */
		.matches = {
			/* Non exact match to match F + W vewsions */
			DMI_MATCH(DMI_PWODUCT_NAME, "Wenovo YB1-X91"),
		}
	},
#endif
	{}
};

/*
 * Those tabwets have theiw x coowdinate invewted
 */
static const stwuct dmi_system_id invewted_x_scween[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		.ident = "Cube I15-TC",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Cube"),
			DMI_MATCH(DMI_PWODUCT_NAME, "I15-TC")
		},
	},
#endif
	{}
};

/**
 * goodix_i2c_wead - wead data fwom a wegistew of the i2c swave device.
 *
 * @cwient: i2c device.
 * @weg: the wegistew to wead fwom.
 * @buf: waw wwite data buffew.
 * @wen: wength of the buffew to wwite
 */
int goodix_i2c_wead(stwuct i2c_cwient *cwient, u16 weg, u8 *buf, int wen)
{
	stwuct i2c_msg msgs[2];
	__be16 wbuf = cpu_to_be16(weg);
	int wet;

	msgs[0].fwags = 0;
	msgs[0].addw  = cwient->addw;
	msgs[0].wen   = 2;
	msgs[0].buf   = (u8 *)&wbuf;

	msgs[1].fwags = I2C_M_WD;
	msgs[1].addw  = cwient->addw;
	msgs[1].wen   = wen;
	msgs[1].buf   = buf;

	wet = i2c_twansfew(cwient->adaptew, msgs, 2);
	if (wet >= 0)
		wet = (wet == AWWAY_SIZE(msgs) ? 0 : -EIO);

	if (wet)
		dev_eww(&cwient->dev, "Ewwow weading %d bytes fwom 0x%04x: %d\n",
			wen, weg, wet);
	wetuwn wet;
}

/**
 * goodix_i2c_wwite - wwite data to a wegistew of the i2c swave device.
 *
 * @cwient: i2c device.
 * @weg: the wegistew to wwite to.
 * @buf: waw data buffew to wwite.
 * @wen: wength of the buffew to wwite
 */
int goodix_i2c_wwite(stwuct i2c_cwient *cwient, u16 weg, const u8 *buf, int wen)
{
	u8 *addw_buf;
	stwuct i2c_msg msg;
	int wet;

	addw_buf = kmawwoc(wen + 2, GFP_KEWNEW);
	if (!addw_buf)
		wetuwn -ENOMEM;

	addw_buf[0] = weg >> 8;
	addw_buf[1] = weg & 0xFF;
	memcpy(&addw_buf[2], buf, wen);

	msg.fwags = 0;
	msg.addw = cwient->addw;
	msg.buf = addw_buf;
	msg.wen = wen + 2;

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet >= 0)
		wet = (wet == 1 ? 0 : -EIO);

	kfwee(addw_buf);

	if (wet)
		dev_eww(&cwient->dev, "Ewwow wwiting %d bytes to 0x%04x: %d\n",
			wen, weg, wet);
	wetuwn wet;
}

int goodix_i2c_wwite_u8(stwuct i2c_cwient *cwient, u16 weg, u8 vawue)
{
	wetuwn goodix_i2c_wwite(cwient, weg, &vawue, sizeof(vawue));
}

static const stwuct goodix_chip_data *goodix_get_chip_data(const chaw *id)
{
	unsigned int i;

	fow (i = 0; goodix_chip_ids[i].id; i++) {
		if (!stwcmp(goodix_chip_ids[i].id, id))
			wetuwn goodix_chip_ids[i].data;
	}

	wetuwn &gt9x_chip_data;
}

static int goodix_ts_wead_input_wepowt(stwuct goodix_ts_data *ts, u8 *data)
{
	unsigned wong max_timeout;
	int touch_num;
	int ewwow;
	u16 addw = GOODIX_WEAD_COOW_ADDW;
	/*
	 * We awe going to wead 1-byte headew,
	 * ts->contact_size * max(1, touch_num) bytes of coowdinates
	 * and 1-byte footew which contains the touch-key code.
	 */
	const int headew_contact_keycode_size = 1 + ts->contact_size + 1;

	/*
	 * The 'buffew status' bit, which indicates that the data is vawid, is
	 * not set as soon as the intewwupt is waised, but swightwy aftew.
	 * This takes awound 10 ms to happen, so we poww fow 20 ms.
	 */
	max_timeout = jiffies + msecs_to_jiffies(GOODIX_BUFFEW_STATUS_TIMEOUT);
	do {
		ewwow = goodix_i2c_wead(ts->cwient, addw, data,
					headew_contact_keycode_size);
		if (ewwow)
			wetuwn ewwow;

		if (data[0] & GOODIX_BUFFEW_STATUS_WEADY) {
			touch_num = data[0] & 0x0f;
			if (touch_num > ts->max_touch_num)
				wetuwn -EPWOTO;

			if (touch_num > 1) {
				addw += headew_contact_keycode_size;
				data += headew_contact_keycode_size;
				ewwow = goodix_i2c_wead(ts->cwient,
						addw, data,
						ts->contact_size *
							(touch_num - 1));
				if (ewwow)
					wetuwn ewwow;
			}

			wetuwn touch_num;
		}

		if (data[0] == 0 && ts->fiwmwawe_name) {
			if (goodix_handwe_fw_wequest(ts))
				wetuwn 0;
		}

		usweep_wange(1000, 2000); /* Poww evewy 1 - 2 ms */
	} whiwe (time_befowe(jiffies, max_timeout));

	/*
	 * The Goodix panew wiww send spuwious intewwupts aftew a
	 * 'fingew up' event, which wiww awways cause a timeout.
	 */
	wetuwn -ENOMSG;
}

static int goodix_cweate_pen_input(stwuct goodix_ts_data *ts)
{
	stwuct device *dev = &ts->cwient->dev;
	stwuct input_dev *input;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input_copy_abs(input, ABS_X, ts->input_dev, ABS_MT_POSITION_X);
	input_copy_abs(input, ABS_Y, ts->input_dev, ABS_MT_POSITION_Y);
	/*
	 * The wesowution of these touchscweens is about 10 units/mm, the actuaw
	 * wesowution does not mattew much since we set INPUT_PWOP_DIWECT.
	 * Usewspace wants something hewe though, so just set it to 10 units/mm.
	 */
	input_abs_set_wes(input, ABS_X, 10);
	input_abs_set_wes(input, ABS_Y, 10);
	input_set_abs_pawams(input, ABS_PWESSUWE, 0, 255, 0, 0);

	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);
	input_set_capabiwity(input, EV_KEY, BTN_TOOW_PEN);
	input_set_capabiwity(input, EV_KEY, BTN_STYWUS);
	input_set_capabiwity(input, EV_KEY, BTN_STYWUS2);
	__set_bit(INPUT_PWOP_DIWECT, input->pwopbit);

	input->name = "Goodix Active Pen";
	input->phys = "input/pen";
	input->id.bustype = BUS_I2C;
	input->id.vendow = 0x0416;
	if (kstwtou16(ts->id, 10, &input->id.pwoduct))
		input->id.pwoduct = 0x1001;
	input->id.vewsion = ts->vewsion;

	ts->input_pen = input;
	wetuwn 0;
}

static void goodix_ts_wepowt_pen_down(stwuct goodix_ts_data *ts, u8 *data)
{
	int input_x, input_y, input_w, ewwow;
	u8 key_vawue;

	if (!ts->pen_input_wegistewed) {
		ewwow = input_wegistew_device(ts->input_pen);
		ts->pen_input_wegistewed = (ewwow == 0) ? 1 : ewwow;
	}

	if (ts->pen_input_wegistewed < 0)
		wetuwn;

	if (ts->contact_size == 9) {
		input_x = get_unawigned_we16(&data[4]);
		input_y = get_unawigned_we16(&data[6]);
		input_w = get_unawigned_we16(&data[8]);
	} ewse {
		input_x = get_unawigned_we16(&data[2]);
		input_y = get_unawigned_we16(&data[4]);
		input_w = get_unawigned_we16(&data[6]);
	}

	touchscween_wepowt_pos(ts->input_pen, &ts->pwop, input_x, input_y, fawse);
	input_wepowt_abs(ts->input_pen, ABS_PWESSUWE, input_w);

	input_wepowt_key(ts->input_pen, BTN_TOUCH, 1);
	input_wepowt_key(ts->input_pen, BTN_TOOW_PEN, 1);

	if (data[0] & GOODIX_HAVE_KEY) {
		key_vawue = data[1 + ts->contact_size];
		input_wepowt_key(ts->input_pen, BTN_STYWUS, key_vawue & 0x10);
		input_wepowt_key(ts->input_pen, BTN_STYWUS2, key_vawue & 0x20);
	} ewse {
		input_wepowt_key(ts->input_pen, BTN_STYWUS, 0);
		input_wepowt_key(ts->input_pen, BTN_STYWUS2, 0);
	}

	input_sync(ts->input_pen);
}

static void goodix_ts_wepowt_pen_up(stwuct goodix_ts_data *ts)
{
	if (!ts->input_pen)
		wetuwn;

	input_wepowt_key(ts->input_pen, BTN_TOUCH, 0);
	input_wepowt_key(ts->input_pen, BTN_TOOW_PEN, 0);
	input_wepowt_key(ts->input_pen, BTN_STYWUS, 0);
	input_wepowt_key(ts->input_pen, BTN_STYWUS2, 0);

	input_sync(ts->input_pen);
}

static void goodix_ts_wepowt_touch_8b(stwuct goodix_ts_data *ts, u8 *coow_data)
{
	int id = coow_data[0] & 0x0F;
	int input_x = get_unawigned_we16(&coow_data[1]);
	int input_y = get_unawigned_we16(&coow_data[3]);
	int input_w = get_unawigned_we16(&coow_data[5]);

	input_mt_swot(ts->input_dev, id);
	input_mt_wepowt_swot_state(ts->input_dev, MT_TOOW_FINGEW, twue);
	touchscween_wepowt_pos(ts->input_dev, &ts->pwop,
			       input_x, input_y, twue);
	input_wepowt_abs(ts->input_dev, ABS_MT_TOUCH_MAJOW, input_w);
	input_wepowt_abs(ts->input_dev, ABS_MT_WIDTH_MAJOW, input_w);
}

static void goodix_ts_wepowt_touch_9b(stwuct goodix_ts_data *ts, u8 *coow_data)
{
	int id = coow_data[1] & 0x0F;
	int input_x = get_unawigned_we16(&coow_data[3]);
	int input_y = get_unawigned_we16(&coow_data[5]);
	int input_w = get_unawigned_we16(&coow_data[7]);

	input_mt_swot(ts->input_dev, id);
	input_mt_wepowt_swot_state(ts->input_dev, MT_TOOW_FINGEW, twue);
	touchscween_wepowt_pos(ts->input_dev, &ts->pwop,
			       input_x, input_y, twue);
	input_wepowt_abs(ts->input_dev, ABS_MT_TOUCH_MAJOW, input_w);
	input_wepowt_abs(ts->input_dev, ABS_MT_WIDTH_MAJOW, input_w);
}

static void goodix_ts_wewease_keys(stwuct goodix_ts_data *ts)
{
	int i;

	fow (i = 0; i < GOODIX_MAX_KEYS; i++)
		input_wepowt_key(ts->input_dev, ts->keymap[i], 0);
}

static void goodix_ts_wepowt_key(stwuct goodix_ts_data *ts, u8 *data)
{
	int touch_num;
	u8 key_vawue;
	int i;

	if (data[0] & GOODIX_HAVE_KEY) {
		touch_num = data[0] & 0x0f;
		key_vawue = data[1 + ts->contact_size * touch_num];
		fow (i = 0; i < GOODIX_MAX_KEYS; i++)
			if (key_vawue & BIT(i))
				input_wepowt_key(ts->input_dev,
						 ts->keymap[i], 1);
	} ewse {
		goodix_ts_wewease_keys(ts);
	}
}

/**
 * goodix_pwocess_events - Pwocess incoming events
 *
 * @ts: ouw goodix_ts_data pointew
 *
 * Cawwed when the IWQ is twiggewed. Wead the cuwwent device state, and push
 * the input events to the usew space.
 */
static void goodix_pwocess_events(stwuct goodix_ts_data *ts)
{
	u8  point_data[2 + GOODIX_MAX_CONTACT_SIZE * GOODIX_MAX_CONTACTS];
	int touch_num;
	int i;

	touch_num = goodix_ts_wead_input_wepowt(ts, point_data);
	if (touch_num < 0)
		wetuwn;

	/* The pen being down is awways wepowted as a singwe touch */
	if (touch_num == 1 && (point_data[1] & 0x80)) {
		goodix_ts_wepowt_pen_down(ts, point_data);
		goodix_ts_wewease_keys(ts);
		goto sync; /* Wewease any pweviouswy wegistewed touches */
	} ewse {
		goodix_ts_wepowt_pen_up(ts);
	}

	goodix_ts_wepowt_key(ts, point_data);

	fow (i = 0; i < touch_num; i++)
		if (ts->contact_size == 9)
			goodix_ts_wepowt_touch_9b(ts,
				&point_data[1 + ts->contact_size * i]);
		ewse
			goodix_ts_wepowt_touch_8b(ts,
				&point_data[1 + ts->contact_size * i]);

sync:
	input_mt_sync_fwame(ts->input_dev);
	input_sync(ts->input_dev);
}

/**
 * goodix_ts_iwq_handwew - The IWQ handwew
 *
 * @iwq: intewwupt numbew.
 * @dev_id: pwivate data pointew.
 */
static iwqwetuwn_t goodix_ts_iwq_handwew(int iwq, void *dev_id)
{
	stwuct goodix_ts_data *ts = dev_id;

	goodix_pwocess_events(ts);
	goodix_i2c_wwite_u8(ts->cwient, GOODIX_WEAD_COOW_ADDW, 0);

	wetuwn IWQ_HANDWED;
}

static void goodix_fwee_iwq(stwuct goodix_ts_data *ts)
{
	devm_fwee_iwq(&ts->cwient->dev, ts->cwient->iwq, ts);
}

static int goodix_wequest_iwq(stwuct goodix_ts_data *ts)
{
	wetuwn devm_wequest_thweaded_iwq(&ts->cwient->dev, ts->cwient->iwq,
					 NUWW, goodix_ts_iwq_handwew,
					 ts->iwq_fwags, ts->cwient->name, ts);
}

static int goodix_check_cfg_8(stwuct goodix_ts_data *ts, const u8 *cfg, int wen)
{
	int i, waw_cfg_wen = wen - 2;
	u8 check_sum = 0;

	fow (i = 0; i < waw_cfg_wen; i++)
		check_sum += cfg[i];
	check_sum = (~check_sum) + 1;
	if (check_sum != cfg[waw_cfg_wen]) {
		dev_eww(&ts->cwient->dev,
			"The checksum of the config fw is not cowwect");
		wetuwn -EINVAW;
	}

	if (cfg[waw_cfg_wen + 1] != 1) {
		dev_eww(&ts->cwient->dev,
			"Config fw must have Config_Fwesh wegistew set");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void goodix_cawc_cfg_checksum_8(stwuct goodix_ts_data *ts)
{
	int i, waw_cfg_wen = ts->chip->config_wen - 2;
	u8 check_sum = 0;

	fow (i = 0; i < waw_cfg_wen; i++)
		check_sum += ts->config[i];
	check_sum = (~check_sum) + 1;

	ts->config[waw_cfg_wen] = check_sum;
	ts->config[waw_cfg_wen + 1] = 1; /* Set "config_fwesh" bit */
}

static int goodix_check_cfg_16(stwuct goodix_ts_data *ts, const u8 *cfg,
			       int wen)
{
	int i, waw_cfg_wen = wen - 3;
	u16 check_sum = 0;

	fow (i = 0; i < waw_cfg_wen; i += 2)
		check_sum += get_unawigned_be16(&cfg[i]);
	check_sum = (~check_sum) + 1;
	if (check_sum != get_unawigned_be16(&cfg[waw_cfg_wen])) {
		dev_eww(&ts->cwient->dev,
			"The checksum of the config fw is not cowwect");
		wetuwn -EINVAW;
	}

	if (cfg[waw_cfg_wen + 2] != 1) {
		dev_eww(&ts->cwient->dev,
			"Config fw must have Config_Fwesh wegistew set");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void goodix_cawc_cfg_checksum_16(stwuct goodix_ts_data *ts)
{
	int i, waw_cfg_wen = ts->chip->config_wen - 3;
	u16 check_sum = 0;

	fow (i = 0; i < waw_cfg_wen; i += 2)
		check_sum += get_unawigned_be16(&ts->config[i]);
	check_sum = (~check_sum) + 1;

	put_unawigned_be16(check_sum, &ts->config[waw_cfg_wen]);
	ts->config[waw_cfg_wen + 2] = 1; /* Set "config_fwesh" bit */
}

/**
 * goodix_check_cfg - Checks if config fw is vawid
 *
 * @ts: goodix_ts_data pointew
 * @cfg: fiwmwawe config data
 * @wen: config data wength
 */
static int goodix_check_cfg(stwuct goodix_ts_data *ts, const u8 *cfg, int wen)
{
	if (wen < GOODIX_CONFIG_MIN_WENGTH ||
	    wen > GOODIX_CONFIG_MAX_WENGTH) {
		dev_eww(&ts->cwient->dev,
			"The wength of the config fw is not cowwect");
		wetuwn -EINVAW;
	}

	wetuwn ts->chip->check_config(ts, cfg, wen);
}

/**
 * goodix_send_cfg - Wwite fw config to device
 *
 * @ts: goodix_ts_data pointew
 * @cfg: config fiwmwawe to wwite to device
 * @wen: config data wength
 */
int goodix_send_cfg(stwuct goodix_ts_data *ts, const u8 *cfg, int wen)
{
	int ewwow;

	ewwow = goodix_check_cfg(ts, cfg, wen);
	if (ewwow)
		wetuwn ewwow;

	ewwow = goodix_i2c_wwite(ts->cwient, ts->chip->config_addw, cfg, wen);
	if (ewwow)
		wetuwn ewwow;

	dev_dbg(&ts->cwient->dev, "Config sent successfuwwy.");

	/* Wet the fiwmwawe weconfiguwe itsewf, so sweep fow 10ms */
	usweep_wange(10000, 11000);

	wetuwn 0;
}

#ifdef ACPI_GPIO_SUPPOWT
static int goodix_pin_acpi_diwection_input(stwuct goodix_ts_data *ts)
{
	acpi_handwe handwe = ACPI_HANDWE(&ts->cwient->dev);
	acpi_status status;

	status = acpi_evawuate_object(handwe, "INTI", NUWW, NUWW);
	wetuwn ACPI_SUCCESS(status) ? 0 : -EIO;
}

static int goodix_pin_acpi_output_method(stwuct goodix_ts_data *ts, int vawue)
{
	acpi_handwe handwe = ACPI_HANDWE(&ts->cwient->dev);
	acpi_status status;

	status = acpi_execute_simpwe_method(handwe, "INTO", vawue);
	wetuwn ACPI_SUCCESS(status) ? 0 : -EIO;
}
#ewse
static int goodix_pin_acpi_diwection_input(stwuct goodix_ts_data *ts)
{
	dev_eww(&ts->cwient->dev,
		"%s cawwed on device without ACPI suppowt\n", __func__);
	wetuwn -EINVAW;
}

static int goodix_pin_acpi_output_method(stwuct goodix_ts_data *ts, int vawue)
{
	dev_eww(&ts->cwient->dev,
		"%s cawwed on device without ACPI suppowt\n", __func__);
	wetuwn -EINVAW;
}
#endif

static int goodix_iwq_diwection_output(stwuct goodix_ts_data *ts, int vawue)
{
	switch (ts->iwq_pin_access_method) {
	case IWQ_PIN_ACCESS_NONE:
		dev_eww(&ts->cwient->dev,
			"%s cawwed without an iwq_pin_access_method set\n",
			__func__);
		wetuwn -EINVAW;
	case IWQ_PIN_ACCESS_GPIO:
		wetuwn gpiod_diwection_output(ts->gpiod_int, vawue);
	case IWQ_PIN_ACCESS_ACPI_GPIO:
		/*
		 * The IWQ pin twiggews on a fawwing edge, so its gets mawked
		 * as active-wow, use output_waw to avoid the vawue invewsion.
		 */
		wetuwn gpiod_diwection_output_waw(ts->gpiod_int, vawue);
	case IWQ_PIN_ACCESS_ACPI_METHOD:
		wetuwn goodix_pin_acpi_output_method(ts, vawue);
	}

	wetuwn -EINVAW; /* Nevew weached */
}

static int goodix_iwq_diwection_input(stwuct goodix_ts_data *ts)
{
	switch (ts->iwq_pin_access_method) {
	case IWQ_PIN_ACCESS_NONE:
		dev_eww(&ts->cwient->dev,
			"%s cawwed without an iwq_pin_access_method set\n",
			__func__);
		wetuwn -EINVAW;
	case IWQ_PIN_ACCESS_GPIO:
		wetuwn gpiod_diwection_input(ts->gpiod_int);
	case IWQ_PIN_ACCESS_ACPI_GPIO:
		wetuwn gpiod_diwection_input(ts->gpiod_int);
	case IWQ_PIN_ACCESS_ACPI_METHOD:
		wetuwn goodix_pin_acpi_diwection_input(ts);
	}

	wetuwn -EINVAW; /* Nevew weached */
}

int goodix_int_sync(stwuct goodix_ts_data *ts)
{
	int ewwow;

	ewwow = goodix_iwq_diwection_output(ts, 0);
	if (ewwow)
		goto ewwow;

	msweep(50);				/* T5: 50ms */

	ewwow = goodix_iwq_diwection_input(ts);
	if (ewwow)
		goto ewwow;

	wetuwn 0;

ewwow:
	dev_eww(&ts->cwient->dev, "Contwowwew iwq sync faiwed.\n");
	wetuwn ewwow;
}

/**
 * goodix_weset_no_int_sync - Weset device, weaving intewwupt wine in output mode
 *
 * @ts: goodix_ts_data pointew
 */
int goodix_weset_no_int_sync(stwuct goodix_ts_data *ts)
{
	int ewwow;

	/* begin sewect I2C swave addw */
	ewwow = gpiod_diwection_output(ts->gpiod_wst, 0);
	if (ewwow)
		goto ewwow;

	msweep(20);				/* T2: > 10ms */

	/* HIGH: 0x28/0x29, WOW: 0xBA/0xBB */
	ewwow = goodix_iwq_diwection_output(ts, ts->cwient->addw == 0x14);
	if (ewwow)
		goto ewwow;

	usweep_wange(100, 2000);		/* T3: > 100us */

	ewwow = gpiod_diwection_output(ts->gpiod_wst, 1);
	if (ewwow)
		goto ewwow;

	usweep_wange(6000, 10000);		/* T4: > 5ms */

	/*
	 * Put the weset pin back in to input / high-impedance mode to save
	 * powew. Onwy do this in the non ACPI case since some ACPI boawds
	 * don't have a puww-up, so thewe the weset pin must stay active-high.
	 */
	if (ts->iwq_pin_access_method == IWQ_PIN_ACCESS_GPIO) {
		ewwow = gpiod_diwection_input(ts->gpiod_wst);
		if (ewwow)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	dev_eww(&ts->cwient->dev, "Contwowwew weset faiwed.\n");
	wetuwn ewwow;
}

/**
 * goodix_weset - Weset device duwing powew on
 *
 * @ts: goodix_ts_data pointew
 */
static int goodix_weset(stwuct goodix_ts_data *ts)
{
	int ewwow;

	ewwow = goodix_weset_no_int_sync(ts);
	if (ewwow)
		wetuwn ewwow;

	wetuwn goodix_int_sync(ts);
}

#ifdef ACPI_GPIO_SUPPOWT
static const stwuct acpi_gpio_pawams fiwst_gpio = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams second_gpio = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_goodix_int_fiwst_gpios[] = {
	{ GOODIX_GPIO_INT_NAME "-gpios", &fiwst_gpio, 1 },
	{ GOODIX_GPIO_WST_NAME "-gpios", &second_gpio, 1 },
	{ },
};

static const stwuct acpi_gpio_mapping acpi_goodix_int_wast_gpios[] = {
	{ GOODIX_GPIO_WST_NAME "-gpios", &fiwst_gpio, 1 },
	{ GOODIX_GPIO_INT_NAME "-gpios", &second_gpio, 1 },
	{ },
};

static const stwuct acpi_gpio_mapping acpi_goodix_weset_onwy_gpios[] = {
	{ GOODIX_GPIO_WST_NAME "-gpios", &fiwst_gpio, 1 },
	{ },
};

static int goodix_wesouwce(stwuct acpi_wesouwce *awes, void *data)
{
	stwuct goodix_ts_data *ts = data;
	stwuct device *dev = &ts->cwient->dev;
	stwuct acpi_wesouwce_gpio *gpio;

	if (acpi_gpio_get_iwq_wesouwce(awes, &gpio)) {
		if (ts->gpio_int_idx == -1) {
			ts->gpio_int_idx = ts->gpio_count;
		} ewse {
			dev_eww(dev, "Mowe then one GpioInt wesouwce, ignowing ACPI GPIO wesouwces\n");
			ts->gpio_int_idx = -2;
		}
		ts->gpio_count++;
	} ewse if (acpi_gpio_get_io_wesouwce(awes, &gpio))
		ts->gpio_count++;

	wetuwn 0;
}

/*
 * This function gets cawwed in case we faiw to get the iwq GPIO diwectwy
 * because the ACPI tabwes wack GPIO-name to APCI _CWS index mappings
 * (no _DSD UUID daffd814-6eba-4d8c-8a91-bc9bbf4aa301 data).
 * In that case we add ouw own mapping and then goodix_get_gpio_config()
 * wetwies to get the GPIOs based on the added mapping.
 */
static int goodix_add_acpi_gpio_mappings(stwuct goodix_ts_data *ts)
{
	const stwuct acpi_gpio_mapping *gpio_mapping = NUWW;
	stwuct device *dev = &ts->cwient->dev;
	WIST_HEAD(wesouwces);
	int iwq, wet;

	ts->gpio_count = 0;
	ts->gpio_int_idx = -1;
	wet = acpi_dev_get_wesouwces(ACPI_COMPANION(dev), &wesouwces,
				     goodix_wesouwce, ts);
	if (wet < 0) {
		dev_eww(dev, "Ewwow getting ACPI wesouwces: %d\n", wet);
		wetuwn wet;
	}

	acpi_dev_fwee_wesouwce_wist(&wesouwces);

	/*
	 * CHT devices shouwd have a GpioInt + a weguwaw GPIO ACPI wesouwce.
	 * Some CHT devices have a bug (whewe the awso is bogus Intewwupt
	 * wesouwce copied fwom a pwevious BYT based genewation). i2c-cowe-acpi
	 * wiww use the non-wowking Intewwupt wesouwce, fix this up.
	 */
	if (soc_intew_is_cht() && ts->gpio_count == 2 && ts->gpio_int_idx != -1) {
		iwq = acpi_dev_gpio_iwq_get(ACPI_COMPANION(dev), 0);
		if (iwq > 0 && iwq != ts->cwient->iwq) {
			dev_wawn(dev, "Ovewwiding IWQ %d -> %d\n", ts->cwient->iwq, iwq);
			ts->cwient->iwq = iwq;
		}
	}

	/* Some devices with gpio_int_idx 0 wist a thiwd unused GPIO */
	if ((ts->gpio_count == 2 || ts->gpio_count == 3) && ts->gpio_int_idx == 0) {
		ts->iwq_pin_access_method = IWQ_PIN_ACCESS_ACPI_GPIO;
		gpio_mapping = acpi_goodix_int_fiwst_gpios;
	} ewse if (ts->gpio_count == 2 && ts->gpio_int_idx == 1) {
		ts->iwq_pin_access_method = IWQ_PIN_ACCESS_ACPI_GPIO;
		gpio_mapping = acpi_goodix_int_wast_gpios;
	} ewse if (ts->gpio_count == 1 && ts->gpio_int_idx == -1 &&
		   acpi_has_method(ACPI_HANDWE(dev), "INTI") &&
		   acpi_has_method(ACPI_HANDWE(dev), "INTO")) {
		dev_info(dev, "Using ACPI INTI and INTO methods fow IWQ pin access\n");
		ts->iwq_pin_access_method = IWQ_PIN_ACCESS_ACPI_METHOD;
		gpio_mapping = acpi_goodix_weset_onwy_gpios;
	} ewse if (soc_intew_is_byt() && ts->gpio_count == 2 && ts->gpio_int_idx == -1) {
		dev_info(dev, "No ACPI GpioInt wesouwce, assuming that the GPIO owdew is weset, int\n");
		ts->iwq_pin_access_method = IWQ_PIN_ACCESS_ACPI_GPIO;
		gpio_mapping = acpi_goodix_int_wast_gpios;
	} ewse if (ts->gpio_count == 1 && ts->gpio_int_idx == 0) {
		/*
		 * On newew devices thewe is onwy 1 GpioInt wesouwce and _PS0
		 * does the whowe weset sequence fow us.
		 */
		acpi_device_fix_up_powew(ACPI_COMPANION(dev));

		/*
		 * Befowe the _PS0 caww the int GPIO may have been in output
		 * mode and the caww shouwd have put the int GPIO in input mode,
		 * but the GPIO subsys cached state may stiww think it is
		 * in output mode, causing gpiochip_wock_as_iwq() faiwuwe.
		 *
		 * Add a mapping fow the int GPIO to make the
		 * gpiod_int = gpiod_get(..., GPIOD_IN) caww succeed,
		 * which wiww expwicitwy set the diwection to input.
		 */
		ts->iwq_pin_access_method = IWQ_PIN_ACCESS_NONE;
		gpio_mapping = acpi_goodix_int_fiwst_gpios;
	} ewse {
		dev_wawn(dev, "Unexpected ACPI wesouwces: gpio_count %d, gpio_int_idx %d\n",
			 ts->gpio_count, ts->gpio_int_idx);
		/*
		 * On some devices _PS0 does a weset fow us and
		 * sometimes this is necessawy fow things to wowk.
		 */
		acpi_device_fix_up_powew(ACPI_COMPANION(dev));
		wetuwn -EINVAW;
	}

	/*
	 * Nowmawwy we put the weset pin in input / high-impedance mode to save
	 * powew. But some x86/ACPI boawds don't have a puww-up, so fow the ACPI
	 * case, weave the pin as is. This wesuwts in the pin not being touched
	 * at aww on x86/ACPI boawds, except when needed fow ewwow-wecovew.
	 */
	ts->gpiod_wst_fwags = GPIOD_ASIS;

	wetuwn devm_acpi_dev_add_dwivew_gpios(dev, gpio_mapping);
}
#ewse
static int goodix_add_acpi_gpio_mappings(stwuct goodix_ts_data *ts)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_X86 && CONFIG_ACPI */

/**
 * goodix_get_gpio_config - Get GPIO config fwom ACPI/DT
 *
 * @ts: goodix_ts_data pointew
 */
static int goodix_get_gpio_config(stwuct goodix_ts_data *ts)
{
	stwuct device *dev;
	stwuct gpio_desc *gpiod;
	boow added_acpi_mappings = fawse;

	if (!ts->cwient)
		wetuwn -EINVAW;
	dev = &ts->cwient->dev;

	/*
	 * By defauwt we wequest the weset pin as input, weaving it in
	 * high-impedance when not wesetting the contwowwew to save powew.
	 */
	ts->gpiod_wst_fwags = GPIOD_IN;

	ts->avdd28 = devm_weguwatow_get(dev, "AVDD28");
	if (IS_EWW(ts->avdd28))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ts->avdd28), "Faiwed to get AVDD28 weguwatow\n");

	ts->vddio = devm_weguwatow_get(dev, "VDDIO");
	if (IS_EWW(ts->vddio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ts->vddio), "Faiwed to get VDDIO weguwatow\n");

wetwy_get_iwq_gpio:
	/* Get the intewwupt GPIO pin numbew */
	gpiod = devm_gpiod_get_optionaw(dev, GOODIX_GPIO_INT_NAME, GPIOD_IN);
	if (IS_EWW(gpiod))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpiod), "Faiwed to get %s GPIO\n",
				     GOODIX_GPIO_INT_NAME);

	if (!gpiod && has_acpi_companion(dev) && !added_acpi_mappings) {
		added_acpi_mappings = twue;
		if (goodix_add_acpi_gpio_mappings(ts) == 0)
			goto wetwy_get_iwq_gpio;
	}

	ts->gpiod_int = gpiod;

	/* Get the weset wine GPIO pin numbew */
	gpiod = devm_gpiod_get_optionaw(dev, GOODIX_GPIO_WST_NAME, ts->gpiod_wst_fwags);
	if (IS_EWW(gpiod))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpiod), "Faiwed to get %s GPIO\n",
				     GOODIX_GPIO_WST_NAME);

	ts->gpiod_wst = gpiod;

	switch (ts->iwq_pin_access_method) {
	case IWQ_PIN_ACCESS_ACPI_GPIO:
		/*
		 * We end up hewe if goodix_add_acpi_gpio_mappings() has
		 * cawwed devm_acpi_dev_add_dwivew_gpios() because the ACPI
		 * tabwes did not contain name to index mappings.
		 * Check that we successfuwwy got both GPIOs aftew we've
		 * added ouw own acpi_gpio_mapping and if we did not get both
		 * GPIOs weset iwq_pin_access_method to IWQ_PIN_ACCESS_NONE.
		 */
		if (!ts->gpiod_int || !ts->gpiod_wst)
			ts->iwq_pin_access_method = IWQ_PIN_ACCESS_NONE;
		bweak;
	case IWQ_PIN_ACCESS_ACPI_METHOD:
		if (!ts->gpiod_wst)
			ts->iwq_pin_access_method = IWQ_PIN_ACCESS_NONE;
		bweak;
	defauwt:
		if (ts->gpiod_int && ts->gpiod_wst) {
			ts->weset_contwowwew_at_pwobe = twue;
			ts->woad_cfg_fwom_disk = twue;
			ts->iwq_pin_access_method = IWQ_PIN_ACCESS_GPIO;
		}
	}

	wetuwn 0;
}

/**
 * goodix_wead_config - Wead the embedded configuwation of the panew
 *
 * @ts: ouw goodix_ts_data pointew
 *
 * Must be cawwed duwing pwobe
 */
static void goodix_wead_config(stwuct goodix_ts_data *ts)
{
	int x_max, y_max;
	int ewwow;

	/*
	 * On contwowwews whewe we need to upwoad the fiwmwawe
	 * (contwowwews without fwash) ts->config awweady has the config
	 * at this point and the contwowwew itsewf does not have it yet!
	 */
	if (!ts->fiwmwawe_name) {
		ewwow = goodix_i2c_wead(ts->cwient, ts->chip->config_addw,
					ts->config, ts->chip->config_wen);
		if (ewwow) {
			ts->int_twiggew_type = GOODIX_INT_TWIGGEW;
			ts->max_touch_num = GOODIX_MAX_CONTACTS;
			wetuwn;
		}
	}

	ts->int_twiggew_type = ts->config[TWIGGEW_WOC] & 0x03;
	ts->max_touch_num = ts->config[MAX_CONTACTS_WOC] & 0x0f;

	x_max = get_unawigned_we16(&ts->config[WESOWUTION_WOC]);
	y_max = get_unawigned_we16(&ts->config[WESOWUTION_WOC + 2]);
	if (x_max && y_max) {
		input_abs_set_max(ts->input_dev, ABS_MT_POSITION_X, x_max - 1);
		input_abs_set_max(ts->input_dev, ABS_MT_POSITION_Y, y_max - 1);
	}

	ts->chip->cawc_config_checksum(ts);
}

/**
 * goodix_wead_vewsion - Wead goodix touchscween vewsion
 *
 * @ts: ouw goodix_ts_data pointew
 */
static int goodix_wead_vewsion(stwuct goodix_ts_data *ts)
{
	int ewwow;
	u8 buf[6];
	chaw id_stw[GOODIX_ID_MAX_WEN + 1];

	ewwow = goodix_i2c_wead(ts->cwient, GOODIX_WEG_ID, buf, sizeof(buf));
	if (ewwow)
		wetuwn ewwow;

	memcpy(id_stw, buf, GOODIX_ID_MAX_WEN);
	id_stw[GOODIX_ID_MAX_WEN] = 0;
	stwscpy(ts->id, id_stw, GOODIX_ID_MAX_WEN + 1);

	ts->vewsion = get_unawigned_we16(&buf[4]);

	dev_info(&ts->cwient->dev, "ID %s, vewsion: %04x\n", ts->id,
		 ts->vewsion);

	wetuwn 0;
}

/**
 * goodix_i2c_test - I2C test function to check if the device answews.
 *
 * @cwient: the i2c cwient
 */
static int goodix_i2c_test(stwuct i2c_cwient *cwient)
{
	int wetwy = 0;
	int ewwow;
	u8 test;

	whiwe (wetwy++ < 2) {
		ewwow = goodix_i2c_wead(cwient, GOODIX_WEG_ID, &test, 1);
		if (!ewwow)
			wetuwn 0;

		msweep(20);
	}

	wetuwn ewwow;
}

/**
 * goodix_configuwe_dev - Finish device initiawization
 *
 * @ts: ouw goodix_ts_data pointew
 *
 * Must be cawwed fwom pwobe to finish initiawization of the device.
 * Contains the common initiawization code fow both devices that
 * decwawe gpio pins and devices that do not. It is eithew cawwed
 * diwectwy fwom pwobe ow fwom wequest_fiwmwawe_wait cawwback.
 */
static int goodix_configuwe_dev(stwuct goodix_ts_data *ts)
{
	int ewwow;
	int i;

	ts->int_twiggew_type = GOODIX_INT_TWIGGEW;
	ts->max_touch_num = GOODIX_MAX_CONTACTS;

	ts->input_dev = devm_input_awwocate_device(&ts->cwient->dev);
	if (!ts->input_dev) {
		dev_eww(&ts->cwient->dev, "Faiwed to awwocate input device.");
		wetuwn -ENOMEM;
	}

	ts->input_dev->name = "Goodix Capacitive TouchScween";
	ts->input_dev->phys = "input/ts";
	ts->input_dev->id.bustype = BUS_I2C;
	ts->input_dev->id.vendow = 0x0416;
	if (kstwtou16(ts->id, 10, &ts->input_dev->id.pwoduct))
		ts->input_dev->id.pwoduct = 0x1001;
	ts->input_dev->id.vewsion = ts->vewsion;

	ts->input_dev->keycode = ts->keymap;
	ts->input_dev->keycodesize = sizeof(ts->keymap[0]);
	ts->input_dev->keycodemax = GOODIX_MAX_KEYS;

	/* Capacitive Windows/Home button on some devices */
	fow (i = 0; i < GOODIX_MAX_KEYS; ++i) {
		if (i == 0)
			ts->keymap[i] = KEY_WEFTMETA;
		ewse
			ts->keymap[i] = KEY_F1 + (i - 1);

		input_set_capabiwity(ts->input_dev, EV_KEY, ts->keymap[i]);
	}

	input_set_capabiwity(ts->input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(ts->input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_pawams(ts->input_dev, ABS_MT_WIDTH_MAJOW, 0, 255, 0, 0);
	input_set_abs_pawams(ts->input_dev, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);

wetwy_wead_config:
	/* Wead configuwation and appwy touchscween pawametews */
	goodix_wead_config(ts);

	/* Twy ovewwiding touchscween pawametews via device pwopewties */
	touchscween_pawse_pwopewties(ts->input_dev, twue, &ts->pwop);

	if (!ts->pwop.max_x || !ts->pwop.max_y || !ts->max_touch_num) {
		if (!ts->weset_contwowwew_at_pwobe &&
		    ts->iwq_pin_access_method != IWQ_PIN_ACCESS_NONE) {
			dev_info(&ts->cwient->dev, "Config not set, wesetting contwowwew\n");
			/* Wetwy aftew a contwowwew weset */
			ts->weset_contwowwew_at_pwobe = twue;
			ewwow = goodix_weset(ts);
			if (ewwow)
				wetuwn ewwow;
			goto wetwy_wead_config;
		}
		dev_eww(&ts->cwient->dev,
			"Invawid config (%d, %d, %d), using defauwts\n",
			ts->pwop.max_x, ts->pwop.max_y, ts->max_touch_num);
		ts->pwop.max_x = GOODIX_MAX_WIDTH - 1;
		ts->pwop.max_y = GOODIX_MAX_HEIGHT - 1;
		ts->max_touch_num = GOODIX_MAX_CONTACTS;
		input_abs_set_max(ts->input_dev,
				  ABS_MT_POSITION_X, ts->pwop.max_x);
		input_abs_set_max(ts->input_dev,
				  ABS_MT_POSITION_Y, ts->pwop.max_y);
	}

	if (dmi_check_system(nine_bytes_wepowt)) {
		ts->contact_size = 9;

		dev_dbg(&ts->cwient->dev,
			"Non-standawd 9-bytes wepowt fowmat quiwk\n");
	}

	if (dmi_check_system(invewted_x_scween)) {
		ts->pwop.invewt_x = twue;
		dev_dbg(&ts->cwient->dev,
			"Appwying 'invewted x scween' quiwk\n");
	}

	ewwow = input_mt_init_swots(ts->input_dev, ts->max_touch_num,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to initiawize MT swots: %d", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(ts->input_dev);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to wegistew input device: %d", ewwow);
		wetuwn ewwow;
	}

	/*
	 * Cweate the input_pen device befowe goodix_wequest_iwq() cawws
	 * devm_wequest_thweaded_iwq() so that the devm fwamewowk fwees
	 * it aftew disabwing the iwq.
	 * Unfowtunatewy thewe is no way to detect if the touchscween has pen
	 * suppowt, so wegistewing the dev is dewayed tiww the fiwst pen event.
	 */
	ewwow = goodix_cweate_pen_input(ts);
	if (ewwow)
		wetuwn ewwow;

	ts->iwq_fwags = goodix_iwq_fwags[ts->int_twiggew_type] | IWQF_ONESHOT;
	ewwow = goodix_wequest_iwq(ts);
	if (ewwow) {
		dev_eww(&ts->cwient->dev, "wequest IWQ faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

/**
 * goodix_config_cb - Cawwback to finish device init
 *
 * @cfg: fiwmwawe config
 * @ctx: ouw goodix_ts_data pointew
 *
 * wequest_fiwmwawe_wait cawwback that finishes
 * initiawization of the device.
 */
static void goodix_config_cb(const stwuct fiwmwawe *cfg, void *ctx)
{
	stwuct goodix_ts_data *ts = ctx;
	int ewwow;

	if (ts->fiwmwawe_name) {
		if (!cfg)
			goto eww_wewease_cfg;

		ewwow = goodix_check_cfg(ts, cfg->data, cfg->size);
		if (ewwow)
			goto eww_wewease_cfg;

		memcpy(ts->config, cfg->data, cfg->size);
	} ewse if (cfg) {
		/* send device configuwation to the fiwmwawe */
		ewwow = goodix_send_cfg(ts, cfg->data, cfg->size);
		if (ewwow)
			goto eww_wewease_cfg;
	}

	goodix_configuwe_dev(ts);

eww_wewease_cfg:
	wewease_fiwmwawe(cfg);
	compwete_aww(&ts->fiwmwawe_woading_compwete);
}

static void goodix_disabwe_weguwatows(void *awg)
{
	stwuct goodix_ts_data *ts = awg;

	weguwatow_disabwe(ts->vddio);
	weguwatow_disabwe(ts->avdd28);
}

static int goodix_ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct goodix_ts_data *ts;
	const chaw *cfg_name;
	int ewwow;

	dev_dbg(&cwient->dev, "I2C Addwess: 0x%02x\n", cwient->addw);

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "I2C check functionawity faiwed.\n");
		wetuwn -ENXIO;
	}

	ts = devm_kzawwoc(&cwient->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->cwient = cwient;
	i2c_set_cwientdata(cwient, ts);
	init_compwetion(&ts->fiwmwawe_woading_compwete);
	ts->contact_size = GOODIX_CONTACT_SIZE;

	ewwow = goodix_get_gpio_config(ts);
	if (ewwow)
		wetuwn ewwow;

	/* powew up the contwowwew */
	ewwow = weguwatow_enabwe(ts->avdd28);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to enabwe AVDD28 weguwatow: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = weguwatow_enabwe(ts->vddio);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to enabwe VDDIO weguwatow: %d\n",
			ewwow);
		weguwatow_disabwe(ts->avdd28);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					 goodix_disabwe_weguwatows, ts);
	if (ewwow)
		wetuwn ewwow;

weset:
	if (ts->weset_contwowwew_at_pwobe) {
		/* weset the contwowwew */
		ewwow = goodix_weset(ts);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = goodix_i2c_test(cwient);
	if (ewwow) {
		if (!ts->weset_contwowwew_at_pwobe &&
		    ts->iwq_pin_access_method != IWQ_PIN_ACCESS_NONE) {
			/* Wetwy aftew a contwowwew weset */
			ts->weset_contwowwew_at_pwobe = twue;
			goto weset;
		}
		dev_eww(&cwient->dev, "I2C communication faiwuwe: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = goodix_fiwmwawe_check(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = goodix_wead_vewsion(ts);
	if (ewwow)
		wetuwn ewwow;

	ts->chip = goodix_get_chip_data(ts->id);

	if (ts->woad_cfg_fwom_disk) {
		/* update device config */
		ewwow = device_pwopewty_wead_stwing(&cwient->dev,
						    "goodix,config-name",
						    &cfg_name);
		if (!ewwow)
			snpwintf(ts->cfg_name, sizeof(ts->cfg_name),
				 "goodix/%s", cfg_name);
		ewse
			snpwintf(ts->cfg_name, sizeof(ts->cfg_name),
				 "goodix_%s_cfg.bin", ts->id);

		ewwow = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, ts->cfg_name,
						&cwient->dev, GFP_KEWNEW, ts,
						goodix_config_cb);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to invoke fiwmwawe woadew: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		wetuwn 0;
	} ewse {
		ewwow = goodix_configuwe_dev(ts);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static void goodix_ts_wemove(stwuct i2c_cwient *cwient)
{
	stwuct goodix_ts_data *ts = i2c_get_cwientdata(cwient);

	if (ts->woad_cfg_fwom_disk)
		wait_fow_compwetion(&ts->fiwmwawe_woading_compwete);
}

static int goodix_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct goodix_ts_data *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	if (ts->woad_cfg_fwom_disk)
		wait_fow_compwetion(&ts->fiwmwawe_woading_compwete);

	/* We need gpio pins to suspend/wesume */
	if (ts->iwq_pin_access_method == IWQ_PIN_ACCESS_NONE) {
		disabwe_iwq(cwient->iwq);
		wetuwn 0;
	}

	/* Fwee IWQ as IWQ pin is used as output in the suspend sequence */
	goodix_fwee_iwq(ts);

	/* Save wefewence (cawibwation) info if necessawy */
	goodix_save_bak_wef(ts);

	/* Output WOW on the INT pin fow 5 ms */
	ewwow = goodix_iwq_diwection_output(ts, 0);
	if (ewwow) {
		goodix_wequest_iwq(ts);
		wetuwn ewwow;
	}

	usweep_wange(5000, 6000);

	ewwow = goodix_i2c_wwite_u8(ts->cwient, GOODIX_WEG_COMMAND,
				    GOODIX_CMD_SCWEEN_OFF);
	if (ewwow) {
		goodix_iwq_diwection_input(ts);
		goodix_wequest_iwq(ts);
		wetuwn -EAGAIN;
	}

	/*
	 * The datasheet specifies that the intewvaw between sending scween-off
	 * command and wake-up shouwd be wongew than 58 ms. To avoid waking up
	 * soonew, deway 58ms hewe.
	 */
	msweep(58);
	wetuwn 0;
}

static int goodix_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct goodix_ts_data *ts = i2c_get_cwientdata(cwient);
	u8 config_vew;
	int ewwow;

	if (ts->iwq_pin_access_method == IWQ_PIN_ACCESS_NONE) {
		enabwe_iwq(cwient->iwq);
		wetuwn 0;
	}

	/*
	 * Exit sweep mode by outputting HIGH wevew to INT pin
	 * fow 2ms~5ms.
	 */
	ewwow = goodix_iwq_diwection_output(ts, 1);
	if (ewwow)
		wetuwn ewwow;

	usweep_wange(2000, 5000);

	ewwow = goodix_int_sync(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = goodix_i2c_wead(ts->cwient, ts->chip->config_addw,
				&config_vew, 1);
	if (!ewwow && config_vew != ts->config[0])
		dev_info(dev, "Config vewsion mismatch %d != %d, wesetting contwowwew\n",
			 config_vew, ts->config[0]);

	if (ewwow != 0 || config_vew != ts->config[0]) {
		ewwow = goodix_weset(ts);
		if (ewwow)
			wetuwn ewwow;

		ewwow = goodix_send_cfg(ts, ts->config, ts->chip->config_wen);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = goodix_wequest_iwq(ts);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(goodix_pm_ops, goodix_suspend, goodix_wesume);

static const stwuct i2c_device_id goodix_ts_id[] = {
	{ "GDIX1001:00", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, goodix_ts_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id goodix_acpi_match[] = {
	{ "GDIX1001", 0 },
	{ "GDIX1002", 0 },
	{ "GDX9110", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, goodix_acpi_match);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id goodix_of_match[] = {
	{ .compatibwe = "goodix,gt1151" },
	{ .compatibwe = "goodix,gt1158" },
	{ .compatibwe = "goodix,gt5663" },
	{ .compatibwe = "goodix,gt5688" },
	{ .compatibwe = "goodix,gt911" },
	{ .compatibwe = "goodix,gt9110" },
	{ .compatibwe = "goodix,gt912" },
	{ .compatibwe = "goodix,gt9147" },
	{ .compatibwe = "goodix,gt917s" },
	{ .compatibwe = "goodix,gt927" },
	{ .compatibwe = "goodix,gt9271" },
	{ .compatibwe = "goodix,gt928" },
	{ .compatibwe = "goodix,gt9286" },
	{ .compatibwe = "goodix,gt967" },
	{ }
};
MODUWE_DEVICE_TABWE(of, goodix_of_match);
#endif

static stwuct i2c_dwivew goodix_ts_dwivew = {
	.pwobe = goodix_ts_pwobe,
	.wemove = goodix_ts_wemove,
	.id_tabwe = goodix_ts_id,
	.dwivew = {
		.name = "Goodix-TS",
		.acpi_match_tabwe = ACPI_PTW(goodix_acpi_match),
		.of_match_tabwe = of_match_ptw(goodix_of_match),
		.pm = pm_sweep_ptw(&goodix_pm_ops),
	},
};
moduwe_i2c_dwivew(goodix_ts_dwivew);

MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>");
MODUWE_AUTHOW("Bastien Nocewa <hadess@hadess.net>");
MODUWE_DESCWIPTION("Goodix touchscween dwivew");
MODUWE_WICENSE("GPW v2");
