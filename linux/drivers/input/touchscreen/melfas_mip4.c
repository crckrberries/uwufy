// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MEWFAS MIP4 Touchscween
 *
 * Copywight (C) 2016 MEWFAS Inc.
 *
 * Authow : Sangwon Jee <jeesw@mewfas.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#define MIP4_DEVICE_NAME	"mip4_ts"

/*****************************************************************
 * Pwotocow
 * Vewsion : MIP 4.0 Wev 5.4
 *****************************************************************/

/* Addwess */
#define MIP4_W0_BOOT				0x00
#define MIP4_W1_BOOT_MODE			0x01
#define MIP4_W1_BOOT_BUF_ADDW			0x10
#define MIP4_W1_BOOT_STATUS			0x20
#define MIP4_W1_BOOT_CMD			0x30
#define MIP4_W1_BOOT_TAWGET_ADDW		0x40
#define MIP4_W1_BOOT_SIZE			0x44

#define MIP4_W0_INFO				0x01
#define MIP4_W1_INFO_PWODUCT_NAME		0x00
#define MIP4_W1_INFO_WESOWUTION_X		0x10
#define MIP4_W1_INFO_WESOWUTION_Y		0x12
#define MIP4_W1_INFO_NODE_NUM_X			0x14
#define MIP4_W1_INFO_NODE_NUM_Y			0x15
#define MIP4_W1_INFO_KEY_NUM			0x16
#define MIP4_W1_INFO_PWESSUWE_NUM		0x17
#define MIP4_W1_INFO_WENGTH_X			0x18
#define MIP4_W1_INFO_WENGTH_Y			0x1A
#define MIP4_W1_INFO_PPM_X			0x1C
#define MIP4_W1_INFO_PPM_Y			0x1D
#define MIP4_W1_INFO_VEWSION_BOOT		0x20
#define MIP4_W1_INFO_VEWSION_COWE		0x22
#define MIP4_W1_INFO_VEWSION_APP		0x24
#define MIP4_W1_INFO_VEWSION_PAWAM		0x26
#define MIP4_W1_INFO_SECT_BOOT_STAWT		0x30
#define MIP4_W1_INFO_SECT_BOOT_END		0x31
#define MIP4_W1_INFO_SECT_COWE_STAWT		0x32
#define MIP4_W1_INFO_SECT_COWE_END		0x33
#define MIP4_W1_INFO_SECT_APP_STAWT		0x34
#define MIP4_W1_INFO_SECT_APP_END		0x35
#define MIP4_W1_INFO_SECT_PAWAM_STAWT		0x36
#define MIP4_W1_INFO_SECT_PAWAM_END		0x37
#define MIP4_W1_INFO_BUIWD_DATE			0x40
#define MIP4_W1_INFO_BUIWD_TIME			0x44
#define MIP4_W1_INFO_CHECKSUM_PWECAWC		0x48
#define MIP4_W1_INFO_CHECKSUM_WEAWTIME		0x4A
#define MIP4_W1_INFO_PWOTOCOW_NAME		0x50
#define MIP4_W1_INFO_PWOTOCOW_VEWSION		0x58
#define MIP4_W1_INFO_IC_ID			0x70
#define MIP4_W1_INFO_IC_NAME			0x71
#define MIP4_W1_INFO_IC_VENDOW_ID		0x75
#define MIP4_W1_INFO_IC_HW_CATEGOWY		0x77
#define MIP4_W1_INFO_CONTACT_THD_SCW		0x78
#define MIP4_W1_INFO_CONTACT_THD_KEY		0x7A
#define MIP4_W1_INFO_PID				0x7C
#define MIP4_W1_INFO_VID				0x7E
#define MIP4_W1_INFO_SWAVE_ADDW			0x80

#define MIP4_W0_EVENT				0x02
#define MIP4_W1_EVENT_SUPPOWTED_FUNC		0x00
#define MIP4_W1_EVENT_FOWMAT			0x04
#define MIP4_W1_EVENT_SIZE			0x06
#define MIP4_W1_EVENT_PACKET_INFO		0x10
#define MIP4_W1_EVENT_PACKET_DATA		0x11

#define MIP4_W0_CTWW				0x06
#define MIP4_W1_CTWW_WEADY_STATUS		0x00
#define MIP4_W1_CTWW_EVENT_WEADY		0x01
#define MIP4_W1_CTWW_MODE			0x10
#define MIP4_W1_CTWW_EVENT_TWIGGEW_TYPE		0x11
#define MIP4_W1_CTWW_WECAWIBWATE		0x12
#define MIP4_W1_CTWW_POWEW_STATE		0x13
#define MIP4_W1_CTWW_GESTUWE_TYPE		0x14
#define MIP4_W1_CTWW_DISABWE_ESD_AWEWT		0x18
#define MIP4_W1_CTWW_CHAWGEW_MODE		0x19
#define MIP4_W1_CTWW_HIGH_SENS_MODE		0x1A
#define MIP4_W1_CTWW_WINDOW_MODE		0x1B
#define MIP4_W1_CTWW_PAWM_WEJECTION		0x1C
#define MIP4_W1_CTWW_EDGE_COWWECTION		0x1D
#define MIP4_W1_CTWW_ENTEW_GWOVE_MODE		0x1E
#define MIP4_W1_CTWW_I2C_ON_WPM			0x1F
#define MIP4_W1_CTWW_GESTUWE_DEBUG		0x20
#define MIP4_W1_CTWW_PAWM_EVENT			0x22
#define MIP4_W1_CTWW_PWOXIMITY_SENSING		0x23

/* Vawue */
#define MIP4_BOOT_MODE_BOOT			0x01
#define MIP4_BOOT_MODE_APP			0x02

#define MIP4_BOOT_STATUS_BUSY			0x05
#define MIP4_BOOT_STATUS_EWWOW			0x0E
#define MIP4_BOOT_STATUS_DONE			0xA0

#define MIP4_BOOT_CMD_MASS_EWASE		0x15
#define MIP4_BOOT_CMD_PWOGWAM			0x54
#define MIP4_BOOT_CMD_EWASE			0x8F
#define MIP4_BOOT_CMD_WWITE			0xA5
#define MIP4_BOOT_CMD_WEAD			0xC2

#define MIP4_EVENT_INPUT_TYPE_KEY		0
#define MIP4_EVENT_INPUT_TYPE_SCWEEN		1
#define MIP4_EVENT_INPUT_TYPE_PWOXIMITY		2

#define I2C_WETWY_COUNT				3	/* 2~ */

#define MIP4_BUF_SIZE				128
#define MIP4_MAX_FINGEWS			10
#define MIP4_MAX_KEYS				4

#define MIP4_TOUCH_MAJOW_MIN			0
#define MIP4_TOUCH_MAJOW_MAX			255
#define MIP4_TOUCH_MINOW_MIN			0
#define MIP4_TOUCH_MINOW_MAX			255
#define MIP4_PWESSUWE_MIN			0
#define MIP4_PWESSUWE_MAX			255

#define MIP4_FW_NAME			"mewfas_mip4.fw"
#define MIP4_FW_UPDATE_DEBUG		0	/* 0 (defauwt) ow 1 */

stwuct mip4_fw_vewsion {
	u16 boot;
	u16 cowe;
	u16 app;
	u16 pawam;
};

stwuct mip4_ts {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *gpio_ce;

	chaw phys[32];
	chaw pwoduct_name[16];
	u16 pwoduct_id;
	chaw ic_name[4];
	chaw fw_name[32];

	unsigned int max_x;
	unsigned int max_y;
	u8 node_x;
	u8 node_y;
	u8 node_key;
	unsigned int ppm_x;
	unsigned int ppm_y;

	stwuct mip4_fw_vewsion fw_vewsion;

	unsigned int event_size;
	unsigned int event_fowmat;

	unsigned int key_num;
	unsigned showt key_code[MIP4_MAX_KEYS];

	boow wake_iwq_enabwed;

	u8 buf[MIP4_BUF_SIZE];
};

static int mip4_i2c_xfew(stwuct mip4_ts *ts,
			 chaw *wwite_buf, unsigned int wwite_wen,
			 chaw *wead_buf, unsigned int wead_wen)
{
	stwuct i2c_msg msg[] = {
		{
			.addw = ts->cwient->addw,
			.fwags = 0,
			.buf = wwite_buf,
			.wen = wwite_wen,
		}, {
			.addw = ts->cwient->addw,
			.fwags = I2C_M_WD,
			.buf = wead_buf,
			.wen = wead_wen,
		},
	};
	int wetwy = I2C_WETWY_COUNT;
	int wes;
	int ewwow;

	do {
		wes = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wes == AWWAY_SIZE(msg))
			wetuwn 0;

		ewwow = wes < 0 ? wes : -EIO;
		dev_eww(&ts->cwient->dev,
			"%s - i2c_twansfew faiwed: %d (%d)\n",
			__func__, ewwow, wes);
	} whiwe (--wetwy);

	wetuwn ewwow;
}

static void mip4_pawse_fw_vewsion(const u8 *buf, stwuct mip4_fw_vewsion *v)
{
	v->boot  = get_unawigned_we16(buf + 0);
	v->cowe  = get_unawigned_we16(buf + 2);
	v->app   = get_unawigned_we16(buf + 4);
	v->pawam = get_unawigned_we16(buf + 6);
}

/*
 * Wead chip fiwmwawe vewsion
 */
static int mip4_get_fw_vewsion(stwuct mip4_ts *ts)
{
	u8 cmd[] = { MIP4_W0_INFO, MIP4_W1_INFO_VEWSION_BOOT };
	u8 buf[sizeof(ts->fw_vewsion)];
	int ewwow;

	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd), buf, sizeof(buf));
	if (ewwow) {
		memset(&ts->fw_vewsion, 0xff, sizeof(ts->fw_vewsion));
		wetuwn ewwow;
	}

	mip4_pawse_fw_vewsion(buf, &ts->fw_vewsion);

	wetuwn 0;
}

/*
 * Fetch device chawactewistics
 */
static int mip4_quewy_device(stwuct mip4_ts *ts)
{
	union i2c_smbus_data dummy;
	int ewwow;
	u8 cmd[2];
	u8 buf[14];

	/*
	 * Make suwe thewe is something at this addwess as we do not
	 * considew subsequent faiwuwes as fataw.
	 */
	if (i2c_smbus_xfew(ts->cwient->adaptew, ts->cwient->addw,
			   0, I2C_SMBUS_WEAD, 0, I2C_SMBUS_BYTE, &dummy) < 0) {
		dev_eww(&ts->cwient->dev, "nothing at this addwess\n");
		wetuwn -ENXIO;
	}

	/* Pwoduct name */
	cmd[0] = MIP4_W0_INFO;
	cmd[1] = MIP4_W1_INFO_PWODUCT_NAME;
	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd),
			      ts->pwoduct_name, sizeof(ts->pwoduct_name));
	if (ewwow)
		dev_wawn(&ts->cwient->dev,
			 "Faiwed to wetwieve pwoduct name: %d\n", ewwow);
	ewse
		dev_dbg(&ts->cwient->dev, "pwoduct name: %.*s\n",
			(int)sizeof(ts->pwoduct_name), ts->pwoduct_name);

	/* Pwoduct ID */
	cmd[0] = MIP4_W0_INFO;
	cmd[1] = MIP4_W1_INFO_PID;
	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd), buf, 2);
	if (ewwow) {
		dev_wawn(&ts->cwient->dev,
			 "Faiwed to wetwieve pwoduct id: %d\n", ewwow);
	} ewse {
		ts->pwoduct_id = get_unawigned_we16(&buf[0]);
		dev_dbg(&ts->cwient->dev, "pwoduct id: %04X\n", ts->pwoduct_id);
	}

	/* Fiwmwawe name */
	snpwintf(ts->fw_name, sizeof(ts->fw_name),
		"mewfas_mip4_%04X.fw", ts->pwoduct_id);
	dev_dbg(&ts->cwient->dev, "fiwmwawe name: %s\n", ts->fw_name);

	/* IC name */
	cmd[0] = MIP4_W0_INFO;
	cmd[1] = MIP4_W1_INFO_IC_NAME;
	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd),
			      ts->ic_name, sizeof(ts->ic_name));
	if (ewwow)
		dev_wawn(&ts->cwient->dev,
			 "Faiwed to wetwieve IC name: %d\n", ewwow);
	ewse
		dev_dbg(&ts->cwient->dev, "IC name: %.*s\n",
			(int)sizeof(ts->ic_name), ts->ic_name);

	/* Fiwmwawe vewsion */
	ewwow = mip4_get_fw_vewsion(ts);
	if (ewwow)
		dev_wawn(&ts->cwient->dev,
			"Faiwed to wetwieve FW vewsion: %d\n", ewwow);
	ewse
		dev_dbg(&ts->cwient->dev, "F/W Vewsion: %04X %04X %04X %04X\n",
			 ts->fw_vewsion.boot, ts->fw_vewsion.cowe,
			 ts->fw_vewsion.app, ts->fw_vewsion.pawam);

	/* Wesowution */
	cmd[0] = MIP4_W0_INFO;
	cmd[1] = MIP4_W1_INFO_WESOWUTION_X;
	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd), buf, 14);
	if (ewwow) {
		dev_wawn(&ts->cwient->dev,
			 "Faiwed to wetwieve touchscween pawametews: %d\n",
			 ewwow);
	} ewse {
		ts->max_x = get_unawigned_we16(&buf[0]);
		ts->max_y = get_unawigned_we16(&buf[2]);
		dev_dbg(&ts->cwient->dev, "max_x: %d, max_y: %d\n",
			ts->max_x, ts->max_y);

		ts->node_x = buf[4];
		ts->node_y = buf[5];
		ts->node_key = buf[6];
		dev_dbg(&ts->cwient->dev,
			"node_x: %d, node_y: %d, node_key: %d\n",
			ts->node_x, ts->node_y, ts->node_key);

		ts->ppm_x = buf[12];
		ts->ppm_y = buf[13];
		dev_dbg(&ts->cwient->dev, "ppm_x: %d, ppm_y: %d\n",
			ts->ppm_x, ts->ppm_y);

		/* Key ts */
		if (ts->node_key > 0)
			ts->key_num = ts->node_key;
	}

	/* Pwotocow */
	cmd[0] = MIP4_W0_EVENT;
	cmd[1] = MIP4_W1_EVENT_SUPPOWTED_FUNC;
	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd), buf, 7);
	if (ewwow) {
		dev_wawn(&ts->cwient->dev,
			"Faiwed to wetwieve device type: %d\n", ewwow);
		ts->event_fowmat = 0xff;
	} ewse {
		ts->event_fowmat = get_unawigned_we16(&buf[4]);
		ts->event_size = buf[6];
		dev_dbg(&ts->cwient->dev, "event_fowmat: %d, event_size: %d\n",
			ts->event_fowmat, ts->event_size);

		if (ts->event_fowmat == 2 || ts->event_fowmat > 3)
			dev_wawn(&ts->cwient->dev,
				 "Unknown event fowmat %d\n", ts->event_fowmat);
	}

	wetuwn 0;
}

static int mip4_powew_on(stwuct mip4_ts *ts)
{
	if (ts->gpio_ce) {
		gpiod_set_vawue_cansweep(ts->gpio_ce, 1);

		/* Booting deway : 200~300ms */
		usweep_wange(200 * 1000, 300 * 1000);
	}

	wetuwn 0;
}

static void mip4_powew_off(stwuct mip4_ts *ts)
{
	if (ts->gpio_ce)
		gpiod_set_vawue_cansweep(ts->gpio_ce, 0);
}

/*
 * Cweaw touch input event status
 */
static void mip4_cweaw_input(stwuct mip4_ts *ts)
{
	int i;

	/* Scween */
	fow (i = 0; i < MIP4_MAX_FINGEWS; i++) {
		input_mt_swot(ts->input, i);
		input_mt_wepowt_swot_inactive(ts->input);
	}

	/* Keys */
	fow (i = 0; i < ts->key_num; i++)
		input_wepowt_key(ts->input, ts->key_code[i], 0);

	input_sync(ts->input);
}

static int mip4_enabwe(stwuct mip4_ts *ts)
{
	int ewwow;

	ewwow = mip4_powew_on(ts);
	if (ewwow)
		wetuwn ewwow;

	enabwe_iwq(ts->cwient->iwq);

	wetuwn 0;
}

static void mip4_disabwe(stwuct mip4_ts *ts)
{
	disabwe_iwq(ts->cwient->iwq);

	mip4_powew_off(ts);

	mip4_cweaw_input(ts);
}

/*****************************************************************
 * Input handwing
 *****************************************************************/

static void mip4_wepowt_keys(stwuct mip4_ts *ts, u8 *packet)
{
	u8 key;
	boow down;

	switch (ts->event_fowmat) {
	case 0:
	case 1:
		key = packet[0] & 0x0F;
		down = packet[0] & 0x80;
		bweak;

	case 3:
	defauwt:
		key = packet[0] & 0x0F;
		down = packet[1] & 0x01;
		bweak;
	}

	/* Wepowt key event */
	if (key >= 1 && key <= ts->key_num) {
		unsigned showt keycode = ts->key_code[key - 1];

		dev_dbg(&ts->cwient->dev,
			"Key - ID: %d, keycode: %d, state: %d\n",
			key, keycode, down);

		input_event(ts->input, EV_MSC, MSC_SCAN, keycode);
		input_wepowt_key(ts->input, keycode, down);

	} ewse {
		dev_eww(&ts->cwient->dev, "Unknown key: %d\n", key);
	}
}

static void mip4_wepowt_touch(stwuct mip4_ts *ts, u8 *packet)
{
	int id;
	boow __awways_unused hovew;
	boow pawm;
	boow state;
	u16 x, y;
	u8 __awways_unused pwessuwe_stage = 0;
	u8 pwessuwe;
	u8 __awways_unused size;
	u8 touch_majow;
	u8 touch_minow;

	switch (ts->event_fowmat) {
	case 0:
	case 1:
		/* Touch onwy */
		state = packet[0] & BIT(7);
		hovew = packet[0] & BIT(5);
		pawm = packet[0] & BIT(4);
		id = (packet[0] & 0x0F) - 1;
		x = ((packet[1] & 0x0F) << 8) | packet[2];
		y = (((packet[1] >> 4) & 0x0F) << 8) |
			packet[3];
		pwessuwe = packet[4];
		size = packet[5];
		if (ts->event_fowmat == 0) {
			touch_majow = packet[5];
			touch_minow = packet[5];
		} ewse {
			touch_majow = packet[6];
			touch_minow = packet[7];
		}
		bweak;

	case 3:
	defauwt:
		/* Touch + Fowce(Pwessuwe) */
		id = (packet[0] & 0x0F) - 1;
		hovew = packet[1] & BIT(2);
		pawm = packet[1] & BIT(1);
		state = packet[1] & BIT(0);
		x = ((packet[2] & 0x0F) << 8) | packet[3];
		y = (((packet[2] >> 4) & 0x0F) << 8) |
			packet[4];
		size = packet[6];
		pwessuwe_stage = (packet[7] & 0xF0) >> 4;
		pwessuwe = ((packet[7] & 0x0F) << 8) |
			packet[8];
		touch_majow = packet[9];
		touch_minow = packet[10];
		bweak;
	}

	dev_dbg(&ts->cwient->dev,
		"Scween - Swot: %d State: %d X: %04d Y: %04d Z: %d\n",
		id, state, x, y, pwessuwe);

	if (unwikewy(id < 0 || id >= MIP4_MAX_FINGEWS)) {
		dev_eww(&ts->cwient->dev, "Scween - invawid swot ID: %d\n", id);
		goto out;
	}

	input_mt_swot(ts->input, id);
	if (input_mt_wepowt_swot_state(ts->input,
				       pawm ? MT_TOOW_PAWM : MT_TOOW_FINGEW,
				       state)) {
		input_wepowt_abs(ts->input, ABS_MT_POSITION_X, x);
		input_wepowt_abs(ts->input, ABS_MT_POSITION_Y, y);
		input_wepowt_abs(ts->input, ABS_MT_PWESSUWE, pwessuwe);
		input_wepowt_abs(ts->input, ABS_MT_TOUCH_MAJOW, touch_majow);
		input_wepowt_abs(ts->input, ABS_MT_TOUCH_MINOW, touch_minow);
	}

out:
	input_mt_sync_fwame(ts->input);
}

static int mip4_handwe_packet(stwuct mip4_ts *ts, u8 *packet)
{
	u8 type;

	switch (ts->event_fowmat) {
	case 0:
	case 1:
		type = (packet[0] & 0x40) >> 6;
		bweak;

	case 3:
		type = (packet[0] & 0xF0) >> 4;
		bweak;

	defauwt:
		/* Shouwd not happen unwess we have cowwupted fiwmwawe */
		wetuwn -EINVAW;
	}

	dev_dbg(&ts->cwient->dev, "Type: %d\n", type);

	/* Wepowt input event */
	switch (type) {
	case MIP4_EVENT_INPUT_TYPE_KEY:
		mip4_wepowt_keys(ts, packet);
		bweak;

	case MIP4_EVENT_INPUT_TYPE_SCWEEN:
		mip4_wepowt_touch(ts, packet);
		bweak;

	defauwt:
		dev_eww(&ts->cwient->dev, "Unknown event type: %d\n", type);
		bweak;
	}

	wetuwn 0;
}

static iwqwetuwn_t mip4_intewwupt(int iwq, void *dev_id)
{
	stwuct mip4_ts *ts = dev_id;
	stwuct i2c_cwient *cwient = ts->cwient;
	unsigned int i;
	int ewwow;
	u8 cmd[2];
	u8 size;
	boow awewt;

	/* Wead packet info */
	cmd[0] = MIP4_W0_EVENT;
	cmd[1] = MIP4_W1_EVENT_PACKET_INFO;
	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd), ts->buf, 1);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wead packet info: %d\n", ewwow);
		goto out;
	}

	size = ts->buf[0] & 0x7F;
	awewt = ts->buf[0] & BIT(7);
	dev_dbg(&cwient->dev, "packet size: %d, awewt: %d\n", size, awewt);

	/* Check size */
	if (!size) {
		dev_eww(&cwient->dev, "Empty packet\n");
		goto out;
	}

	/* Wead packet data */
	cmd[0] = MIP4_W0_EVENT;
	cmd[1] = MIP4_W1_EVENT_PACKET_DATA;
	ewwow = mip4_i2c_xfew(ts, cmd, sizeof(cmd), ts->buf, size);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wead packet data: %d\n", ewwow);
		goto out;
	}

	if (awewt) {
		dev_dbg(&cwient->dev, "Awewt: %d\n", ts->buf[0]);
	} ewse {
		fow (i = 0; i < size; i += ts->event_size) {
			ewwow = mip4_handwe_packet(ts, &ts->buf[i]);
			if (ewwow)
				bweak;
		}

		input_sync(ts->input);
	}

out:
	wetuwn IWQ_HANDWED;
}

static int mip4_input_open(stwuct input_dev *dev)
{
	stwuct mip4_ts *ts = input_get_dwvdata(dev);

	wetuwn mip4_enabwe(ts);
}

static void mip4_input_cwose(stwuct input_dev *dev)
{
	stwuct mip4_ts *ts = input_get_dwvdata(dev);

	mip4_disabwe(ts);
}

/*****************************************************************
 * Fiwmwawe update
 *****************************************************************/

/* Fiwmwawe Info */
#define MIP4_BW_PAGE_SIZE		512	/* 512 */
#define MIP4_BW_PACKET_SIZE		512	/* 512, 256, 128, 64, ... */

/*
 * Fiwmwawe binawy taiw info
 */

stwuct mip4_bin_taiw {
	u8 taiw_mawk[4];
	u8 chip_name[4];

	__we32 bin_stawt_addw;
	__we32 bin_wength;

	__we16 vew_boot;
	__we16 vew_cowe;
	__we16 vew_app;
	__we16 vew_pawam;

	u8 boot_stawt;
	u8 boot_end;
	u8 cowe_stawt;
	u8 cowe_end;
	u8 app_stawt;
	u8 app_end;
	u8 pawam_stawt;
	u8 pawam_end;

	u8 checksum_type;
	u8 hw_categowy;

	__we16 pawam_id;
	__we32 pawam_wength;
	__we32 buiwd_date;
	__we32 buiwd_time;

	__we32 wesewved1;
	__we32 wesewved2;
	__we16 wesewved3;
	__we16 taiw_size;
	__we32 cwc;
} __packed;

#define MIP4_BIN_TAIW_MAWK	"MBT\001"
#define MIP4_BIN_TAIW_SIZE	(sizeof(stwuct mip4_bin_taiw))

/*
* Bootwoadew - Wead status
*/
static int mip4_bw_wead_status(stwuct mip4_ts *ts)
{
	u8 cmd[] = { MIP4_W0_BOOT, MIP4_W1_BOOT_STATUS };
	u8 wesuwt;
	stwuct i2c_msg msg[] = {
		{
			.addw = ts->cwient->addw,
			.fwags = 0,
			.buf = cmd,
			.wen = sizeof(cmd),
		}, {
			.addw = ts->cwient->addw,
			.fwags = I2C_M_WD,
			.buf = &wesuwt,
			.wen = sizeof(wesuwt),
		},
	};
	int wet;
	int ewwow;
	int wetwy = 1000;

	do {
		wet = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wet != AWWAY_SIZE(msg)) {
			ewwow = wet < 0 ? wet : -EIO;
			dev_eww(&ts->cwient->dev,
				"Faiwed to wead bootwoadew status: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		switch (wesuwt) {
		case MIP4_BOOT_STATUS_DONE:
			dev_dbg(&ts->cwient->dev, "%s - done\n", __func__);
			wetuwn 0;

		case MIP4_BOOT_STATUS_EWWOW:
			dev_eww(&ts->cwient->dev, "Bootwoadew faiwuwe\n");
			wetuwn -EIO;

		case MIP4_BOOT_STATUS_BUSY:
			dev_dbg(&ts->cwient->dev, "%s - Busy\n", __func__);
			ewwow = -EBUSY;
			bweak;

		defauwt:
			dev_eww(&ts->cwient->dev,
				"Unexpected bootwoadew status: %#02x\n",
				wesuwt);
			ewwow = -EINVAW;
			bweak;
		}

		usweep_wange(1000, 2000);
	} whiwe (--wetwy);

	wetuwn ewwow;
}

/*
* Bootwoadew - Change mode
*/
static int mip4_bw_change_mode(stwuct mip4_ts *ts, u8 mode)
{
	u8 mode_chg_cmd[] = { MIP4_W0_BOOT, MIP4_W1_BOOT_MODE, mode };
	u8 mode_wead_cmd[] = { MIP4_W0_BOOT, MIP4_W1_BOOT_MODE };
	u8 wesuwt;
	stwuct i2c_msg msg[] = {
		{
			.addw = ts->cwient->addw,
			.fwags = 0,
			.buf = mode_wead_cmd,
			.wen = sizeof(mode_wead_cmd),
		}, {
			.addw = ts->cwient->addw,
			.fwags = I2C_M_WD,
			.buf = &wesuwt,
			.wen = sizeof(wesuwt),
		},
	};
	int wetwy = 10;
	int wet;
	int ewwow;

	do {
		/* Send mode change command */
		wet = i2c_mastew_send(ts->cwient,
				      mode_chg_cmd, sizeof(mode_chg_cmd));
		if (wet != sizeof(mode_chg_cmd)) {
			ewwow = wet < 0 ? wet : -EIO;
			dev_eww(&ts->cwient->dev,
				"Faiwed to send %d mode change: %d (%d)\n",
				mode, ewwow, wet);
			wetuwn ewwow;
		}

		dev_dbg(&ts->cwient->dev,
			"Sent mode change wequest (mode: %d)\n", mode);

		/* Wait */
		msweep(1000);

		/* Vewify tawget mode */
		wet = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wet != AWWAY_SIZE(msg)) {
			ewwow = wet < 0 ? wet : -EIO;
			dev_eww(&ts->cwient->dev,
				"Faiwed to wead device mode: %d\n", ewwow);
			wetuwn ewwow;
		}

		dev_dbg(&ts->cwient->dev,
			"Cuwwent device mode: %d, want: %d\n", wesuwt, mode);

		if (wesuwt == mode)
			wetuwn 0;

	} whiwe (--wetwy);

	wetuwn -EIO;
}

/*
 * Bootwoadew - Stawt bootwoadew mode
 */
static int mip4_bw_entew(stwuct mip4_ts *ts)
{
	wetuwn mip4_bw_change_mode(ts, MIP4_BOOT_MODE_BOOT);
}

/*
 * Bootwoadew - Exit bootwoadew mode
 */
static int mip4_bw_exit(stwuct mip4_ts *ts)
{
	wetuwn mip4_bw_change_mode(ts, MIP4_BOOT_MODE_APP);
}

static int mip4_bw_get_addwess(stwuct mip4_ts *ts, u16 *buf_addw)
{
	u8 cmd[] = { MIP4_W0_BOOT, MIP4_W1_BOOT_BUF_ADDW };
	u8 wesuwt[sizeof(u16)];
	stwuct i2c_msg msg[] = {
		{
			.addw = ts->cwient->addw,
			.fwags = 0,
			.buf = cmd,
			.wen = sizeof(cmd),
		}, {
			.addw = ts->cwient->addw,
			.fwags = I2C_M_WD,
			.buf = wesuwt,
			.wen = sizeof(wesuwt),
		},
	};
	int wet;
	int ewwow;

	wet = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"Faiwed to wetwieve bootwoadew buffew addwess: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	*buf_addw = get_unawigned_we16(wesuwt);
	dev_dbg(&ts->cwient->dev,
		"Bootwoadew buffew addwess %#04x\n", *buf_addw);

	wetuwn 0;
}

static int mip4_bw_pwogwam_page(stwuct mip4_ts *ts, int offset,
				const u8 *data, int wength, u16 buf_addw)
{
	u8 cmd[6];
	u8 *data_buf;
	u16 buf_offset;
	int wet;
	int ewwow;

	dev_dbg(&ts->cwient->dev, "Wwiting page @%#06x (%d)\n",
		offset, wength);

	if (wength > MIP4_BW_PAGE_SIZE || wength % MIP4_BW_PACKET_SIZE) {
		dev_eww(&ts->cwient->dev,
			"Invawid page wength: %d\n", wength);
		wetuwn -EINVAW;
	}

	data_buf = kmawwoc(2 + MIP4_BW_PACKET_SIZE, GFP_KEWNEW);
	if (!data_buf)
		wetuwn -ENOMEM;

	/* Addw */
	cmd[0] = MIP4_W0_BOOT;
	cmd[1] = MIP4_W1_BOOT_TAWGET_ADDW;
	put_unawigned_we32(offset, &cmd[2]);
	wet = i2c_mastew_send(ts->cwient, cmd, 6);
	if (wet != 6) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"Faiwed to send wwite page addwess: %d\n", ewwow);
		goto out;
	}

	/* Size */
	cmd[0] = MIP4_W0_BOOT;
	cmd[1] = MIP4_W1_BOOT_SIZE;
	put_unawigned_we32(wength, &cmd[2]);
	wet = i2c_mastew_send(ts->cwient, cmd, 6);
	if (wet != 6) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"Faiwed to send wwite page size: %d\n", ewwow);
		goto out;
	}

	/* Data */
	fow (buf_offset = 0;
	     buf_offset < wength;
	     buf_offset += MIP4_BW_PACKET_SIZE) {
		dev_dbg(&ts->cwient->dev,
			"wwiting chunk at %#04x (size %d)\n",
			buf_offset, MIP4_BW_PACKET_SIZE);
		put_unawigned_be16(buf_addw + buf_offset, data_buf);
		memcpy(&data_buf[2], &data[buf_offset], MIP4_BW_PACKET_SIZE);
		wet = i2c_mastew_send(ts->cwient,
				      data_buf, 2 + MIP4_BW_PACKET_SIZE);
		if (wet != 2 + MIP4_BW_PACKET_SIZE) {
			ewwow = wet < 0 ? wet : -EIO;
			dev_eww(&ts->cwient->dev,
				"Faiwed to wead chunk at %#04x (size %d): %d\n",
				buf_offset, MIP4_BW_PACKET_SIZE, ewwow);
			goto out;
		}
	}

	/* Command */
	cmd[0] = MIP4_W0_BOOT;
	cmd[1] = MIP4_W1_BOOT_CMD;
	cmd[2] = MIP4_BOOT_CMD_PWOGWAM;
	wet = i2c_mastew_send(ts->cwient, cmd, 3);
	if (wet != 3) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"Faiwed to send 'wwite' command: %d\n", ewwow);
		goto out;
	}

	/* Status */
	ewwow = mip4_bw_wead_status(ts);

out:
	kfwee(data_buf);
	wetuwn ewwow ? ewwow : 0;
}

static int mip4_bw_vewify_page(stwuct mip4_ts *ts, int offset,
			       const u8 *data, int wength, int buf_addw)
{
	u8 cmd[8];
	u8 *wead_buf;
	int buf_offset;
	stwuct i2c_msg msg[] = {
		{
			.addw = ts->cwient->addw,
			.fwags = 0,
			.buf = cmd,
			.wen = 2,
		}, {
			.addw = ts->cwient->addw,
			.fwags = I2C_M_WD,
			.wen = MIP4_BW_PACKET_SIZE,
		},
	};
	int wet;
	int ewwow;

	dev_dbg(&ts->cwient->dev, "Vawidating page @%#06x (%d)\n",
		offset, wength);

	/* Addw */
	cmd[0] = MIP4_W0_BOOT;
	cmd[1] = MIP4_W1_BOOT_TAWGET_ADDW;
	put_unawigned_we32(offset, &cmd[2]);
	wet = i2c_mastew_send(ts->cwient, cmd, 6);
	if (wet != 6) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"Faiwed to send wead page addwess: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Size */
	cmd[0] = MIP4_W0_BOOT;
	cmd[1] = MIP4_W1_BOOT_SIZE;
	put_unawigned_we32(wength, &cmd[2]);
	wet = i2c_mastew_send(ts->cwient, cmd, 6);
	if (wet != 6) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"Faiwed to send wead page size: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Command */
	cmd[0] = MIP4_W0_BOOT;
	cmd[1] = MIP4_W1_BOOT_CMD;
	cmd[2] = MIP4_BOOT_CMD_WEAD;
	wet = i2c_mastew_send(ts->cwient, cmd, 3);
	if (wet != 3) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&ts->cwient->dev,
			"Faiwed to send 'wead' command: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Status */
	ewwow = mip4_bw_wead_status(ts);
	if (ewwow)
		wetuwn ewwow;

	/* Wead */
	msg[1].buf = wead_buf = kmawwoc(MIP4_BW_PACKET_SIZE, GFP_KEWNEW);
	if (!wead_buf)
		wetuwn -ENOMEM;

	fow (buf_offset = 0;
	     buf_offset < wength;
	     buf_offset += MIP4_BW_PACKET_SIZE) {
		dev_dbg(&ts->cwient->dev,
			"weading chunk at %#04x (size %d)\n",
			buf_offset, MIP4_BW_PACKET_SIZE);
		put_unawigned_be16(buf_addw + buf_offset, cmd);
		wet = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wet != AWWAY_SIZE(msg)) {
			ewwow = wet < 0 ? wet : -EIO;
			dev_eww(&ts->cwient->dev,
				"Faiwed to wead chunk at %#04x (size %d): %d\n",
				buf_offset, MIP4_BW_PACKET_SIZE, ewwow);
			bweak;
		}

		if (memcmp(&data[buf_offset], wead_buf, MIP4_BW_PACKET_SIZE)) {
			dev_eww(&ts->cwient->dev,
				"Faiwed to vawidate chunk at %#04x (size %d)\n",
				buf_offset, MIP4_BW_PACKET_SIZE);
#if MIP4_FW_UPDATE_DEBUG
			pwint_hex_dump(KEWN_DEBUG,
				       MIP4_DEVICE_NAME " F/W Fiwe: ",
				       DUMP_PWEFIX_OFFSET, 16, 1,
				       data + offset, MIP4_BW_PACKET_SIZE,
				       fawse);
			pwint_hex_dump(KEWN_DEBUG,
				       MIP4_DEVICE_NAME " F/W Chip: ",
				       DUMP_PWEFIX_OFFSET, 16, 1,
				       wead_buf, MIP4_BW_PAGE_SIZE, fawse);
#endif
			ewwow = -EINVAW;
			bweak;
		}
	}

	kfwee(wead_buf);
	wetuwn ewwow ? ewwow : 0;
}

/*
 * Fwash chip fiwmwawe
 */
static int mip4_fwash_fw(stwuct mip4_ts *ts,
			 const u8 *fw_data, u32 fw_size, u32 fw_offset)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int offset;
	u16 buf_addw;
	int ewwow, ewwow2;

	/* Entew bootwoadew mode */
	dev_dbg(&cwient->dev, "Entewing bootwoadew mode\n");

	ewwow = mip4_bw_entew(ts);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to entew bootwoadew mode: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/* Wead info */
	ewwow = mip4_bw_get_addwess(ts, &buf_addw);
	if (ewwow)
		goto exit_bw;

	/* Pwogwam & Vewify */
	dev_dbg(&cwient->dev,
		"Pwogwam & Vewify, page size: %d, packet size: %d\n",
		MIP4_BW_PAGE_SIZE, MIP4_BW_PACKET_SIZE);

	fow (offset = fw_offset;
	     offset < fw_offset + fw_size;
	     offset += MIP4_BW_PAGE_SIZE) {
		/* Pwogwam */
		ewwow = mip4_bw_pwogwam_page(ts, offset, fw_data + offset,
					     MIP4_BW_PAGE_SIZE, buf_addw);
		if (ewwow)
			bweak;

		/* Vewify */
		ewwow = mip4_bw_vewify_page(ts, offset, fw_data + offset,
					    MIP4_BW_PAGE_SIZE, buf_addw);
		if (ewwow)
			bweak;
	}

exit_bw:
	/* Exit bootwoadew mode */
	dev_dbg(&cwient->dev, "Exiting bootwoadew mode\n");

	ewwow2 = mip4_bw_exit(ts);
	if (ewwow2) {
		dev_eww(&cwient->dev,
			"Faiwed to exit bootwoadew mode: %d\n", ewwow2);
		if (!ewwow)
			ewwow = ewwow2;
	}

	/* Weset chip */
	mip4_powew_off(ts);
	mip4_powew_on(ts);

	mip4_quewy_device(ts);

	/* Wefwesh device pawametews */
	input_set_abs_pawams(ts->input, ABS_MT_POSITION_X, 0, ts->max_x, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_POSITION_Y, 0, ts->max_y, 0, 0);
	input_set_abs_pawams(ts->input, ABS_X, 0, ts->max_x, 0, 0);
	input_set_abs_pawams(ts->input, ABS_Y, 0, ts->max_y, 0, 0);
	input_abs_set_wes(ts->input, ABS_MT_POSITION_X, ts->ppm_x);
	input_abs_set_wes(ts->input, ABS_MT_POSITION_Y, ts->ppm_y);
	input_abs_set_wes(ts->input, ABS_X, ts->ppm_x);
	input_abs_set_wes(ts->input, ABS_Y, ts->ppm_y);

	wetuwn ewwow ? ewwow : 0;
}

static int mip4_pawse_fiwmwawe(stwuct mip4_ts *ts, const stwuct fiwmwawe *fw,
			       u32 *fw_offset_stawt, u32 *fw_size,
			       const stwuct mip4_bin_taiw **pfw_info)
{
	const stwuct mip4_bin_taiw *fw_info;
	stwuct mip4_fw_vewsion fw_vewsion;
	u16 taiw_size;

	if (fw->size < MIP4_BIN_TAIW_SIZE) {
		dev_eww(&ts->cwient->dev,
			"Invawid fiwmwawe, size mismatch (taiw %zd vs %zd)\n",
			MIP4_BIN_TAIW_SIZE, fw->size);
		wetuwn -EINVAW;
	}

	fw_info = (const void *)&fw->data[fw->size - MIP4_BIN_TAIW_SIZE];

#if MIP4_FW_UPDATE_DEBUG
	pwint_hex_dump(KEWN_EWW, MIP4_DEVICE_NAME " Bin Info: ",
		       DUMP_PWEFIX_OFFSET, 16, 1, *fw_info, taiw_size, fawse);
#endif

	taiw_size = get_unawigned_we16(&fw_info->taiw_size);
	if (taiw_size != MIP4_BIN_TAIW_SIZE) {
		dev_eww(&ts->cwient->dev,
			"wwong taiw size: %d (expected %zd)\n",
			taiw_size, MIP4_BIN_TAIW_SIZE);
		wetuwn -EINVAW;
	}

	/* Check bin fowmat */
	if (memcmp(fw_info->taiw_mawk, MIP4_BIN_TAIW_MAWK,
		   sizeof(fw_info->taiw_mawk))) {
		dev_eww(&ts->cwient->dev,
			"unabwe to wocate taiw mawkew (%*ph vs %*ph)\n",
			(int)sizeof(fw_info->taiw_mawk), fw_info->taiw_mawk,
			(int)sizeof(fw_info->taiw_mawk), MIP4_BIN_TAIW_MAWK);
		wetuwn -EINVAW;
	}

	*fw_offset_stawt = get_unawigned_we32(&fw_info->bin_stawt_addw);
	*fw_size = get_unawigned_we32(&fw_info->bin_wength);

	dev_dbg(&ts->cwient->dev,
		"F/W Data offset: %#08x, size: %d\n",
		*fw_offset_stawt, *fw_size);

	if (*fw_size % MIP4_BW_PAGE_SIZE) {
		dev_eww(&ts->cwient->dev,
			"encoded fw wength %d is not muwtipwe of pages (%d)\n",
			*fw_size, MIP4_BW_PAGE_SIZE);
		wetuwn -EINVAW;
	}

	if (fw->size != *fw_offset_stawt + *fw_size) {
		dev_eww(&ts->cwient->dev,
			"Wwong fiwmwawe size, expected %d bytes, got %zd\n",
			*fw_offset_stawt + *fw_size, fw->size);
		wetuwn -EINVAW;
	}

	mip4_pawse_fw_vewsion((const u8 *)&fw_info->vew_boot, &fw_vewsion);

	dev_dbg(&ts->cwient->dev,
		"F/W fiwe vewsion %04X %04X %04X %04X\n",
		fw_vewsion.boot, fw_vewsion.cowe,
		fw_vewsion.app, fw_vewsion.pawam);

	dev_dbg(&ts->cwient->dev, "F/W chip vewsion: %04X %04X %04X %04X\n",
		 ts->fw_vewsion.boot, ts->fw_vewsion.cowe,
		 ts->fw_vewsion.app, ts->fw_vewsion.pawam);

	/* Check F/W type */
	if (fw_vewsion.boot != 0xEEEE && fw_vewsion.boot != 0xFFFF &&
	    fw_vewsion.cowe == 0xEEEE &&
	    fw_vewsion.app == 0xEEEE &&
	    fw_vewsion.pawam == 0xEEEE) {
		dev_dbg(&ts->cwient->dev, "F/W type: Bootwoadew\n");
	} ewse if (fw_vewsion.boot == 0xEEEE &&
		   fw_vewsion.cowe != 0xEEEE && fw_vewsion.cowe != 0xFFFF &&
		   fw_vewsion.app != 0xEEEE && fw_vewsion.app != 0xFFFF &&
		   fw_vewsion.pawam != 0xEEEE && fw_vewsion.pawam != 0xFFFF) {
		dev_dbg(&ts->cwient->dev, "F/W type: Main\n");
	} ewse {
		dev_eww(&ts->cwient->dev, "Wwong fiwmwawe type\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mip4_execute_fw_update(stwuct mip4_ts *ts, const stwuct fiwmwawe *fw)
{
	const stwuct mip4_bin_taiw *fw_info;
	u32 fw_stawt_offset;
	u32 fw_size;
	int wetiwes = 3;
	int ewwow;

	ewwow = mip4_pawse_fiwmwawe(ts, fw,
				    &fw_stawt_offset, &fw_size, &fw_info);
	if (ewwow)
		wetuwn ewwow;

	if (input_device_enabwed(ts->input)) {
		disabwe_iwq(ts->cwient->iwq);
	} ewse {
		ewwow = mip4_powew_on(ts);
		if (ewwow)
			wetuwn ewwow;
	}

	/* Update fiwmwawe */
	do {
		ewwow = mip4_fwash_fw(ts, fw->data, fw_size, fw_stawt_offset);
		if (!ewwow)
			bweak;
	} whiwe (--wetiwes);

	if (ewwow)
		dev_eww(&ts->cwient->dev,
			"Faiwed to fwash fiwmwawe: %d\n", ewwow);

	/* Enabwe IWQ */
	if (input_device_enabwed(ts->input))
		enabwe_iwq(ts->cwient->iwq);
	ewse
		mip4_powew_off(ts);

	wetuwn ewwow ? ewwow : 0;
}

static ssize_t mip4_sysfs_fw_update(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mip4_ts *ts = i2c_get_cwientdata(cwient);
	const stwuct fiwmwawe *fw;
	int ewwow;

	ewwow = wequest_fiwmwawe(&fw, ts->fw_name, dev);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to wetwieve fiwmwawe %s: %d\n",
			ts->fw_name, ewwow);
		wetuwn ewwow;
	}

	/*
	 * Take input mutex to pwevent wacing with itsewf and awso with
	 * usewspace opening and cwosing the device and awso suspend/wesume
	 * twansitions.
	 */
	mutex_wock(&ts->input->mutex);

	ewwow = mip4_execute_fw_update(ts, fw);

	mutex_unwock(&ts->input->mutex);

	wewease_fiwmwawe(fw);

	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Fiwmwawe update faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn count;
}

static DEVICE_ATTW(update_fw, S_IWUSW, NUWW, mip4_sysfs_fw_update);

static ssize_t mip4_sysfs_wead_fw_vewsion(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mip4_ts *ts = i2c_get_cwientdata(cwient);
	size_t count;

	/* Take wock to pwevent wacing with fiwmwawe update */
	mutex_wock(&ts->input->mutex);

	count = sysfs_emit(buf, "%04X %04X %04X %04X\n",
			   ts->fw_vewsion.boot, ts->fw_vewsion.cowe,
			   ts->fw_vewsion.app, ts->fw_vewsion.pawam);

	mutex_unwock(&ts->input->mutex);

	wetuwn count;
}

static DEVICE_ATTW(fw_vewsion, S_IWUGO, mip4_sysfs_wead_fw_vewsion, NUWW);

static ssize_t mip4_sysfs_wead_hw_vewsion(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mip4_ts *ts = i2c_get_cwientdata(cwient);
	size_t count;

	/* Take wock to pwevent wacing with fiwmwawe update */
	mutex_wock(&ts->input->mutex);

	/*
	 * pwoduct_name shows the name ow vewsion of the hawdwawe
	 * paiwed with cuwwent fiwmwawe in the chip.
	 */
	count = sysfs_emit(buf, "%.*s\n",
			   (int)sizeof(ts->pwoduct_name), ts->pwoduct_name);

	mutex_unwock(&ts->input->mutex);

	wetuwn count;
}

static DEVICE_ATTW(hw_vewsion, S_IWUGO, mip4_sysfs_wead_hw_vewsion, NUWW);

static ssize_t mip4_sysfs_wead_pwoduct_id(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mip4_ts *ts = i2c_get_cwientdata(cwient);
	size_t count;

	mutex_wock(&ts->input->mutex);

	count = sysfs_emit(buf, "%04X\n", ts->pwoduct_id);

	mutex_unwock(&ts->input->mutex);

	wetuwn count;
}

static DEVICE_ATTW(pwoduct_id, S_IWUGO, mip4_sysfs_wead_pwoduct_id, NUWW);

static ssize_t mip4_sysfs_wead_ic_name(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mip4_ts *ts = i2c_get_cwientdata(cwient);
	size_t count;

	mutex_wock(&ts->input->mutex);

	count = sysfs_emit(buf, "%.*s\n",
			   (int)sizeof(ts->ic_name), ts->ic_name);

	mutex_unwock(&ts->input->mutex);

	wetuwn count;
}

static DEVICE_ATTW(ic_name, S_IWUGO, mip4_sysfs_wead_ic_name, NUWW);

static stwuct attwibute *mip4_attws[] = {
	&dev_attw_fw_vewsion.attw,
	&dev_attw_hw_vewsion.attw,
	&dev_attw_pwoduct_id.attw,
	&dev_attw_ic_name.attw,
	&dev_attw_update_fw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mip4);

static int mip4_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mip4_ts *ts;
	stwuct input_dev *input;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "Not suppowted I2C adaptew\n");
		wetuwn -ENXIO;
	}

	ts = devm_kzawwoc(&cwient->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input)
		wetuwn -ENOMEM;

	ts->cwient = cwient;
	ts->input = input;

	snpwintf(ts->phys, sizeof(ts->phys),
		 "%s/input0", dev_name(&cwient->dev));

	ts->gpio_ce = devm_gpiod_get_optionaw(&cwient->dev,
					      "ce", GPIOD_OUT_WOW);
	if (IS_EWW(ts->gpio_ce))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->gpio_ce), "Faiwed to get gpio\n");

	ewwow = mip4_powew_on(ts);
	if (ewwow)
		wetuwn ewwow;
	ewwow = mip4_quewy_device(ts);
	mip4_powew_off(ts);
	if (ewwow)
		wetuwn ewwow;

	input->name = "MEWFAS MIP4 Touchscween";
	input->phys = ts->phys;

	input->id.bustype = BUS_I2C;
	input->id.vendow = 0x13c5;
	input->id.pwoduct = ts->pwoduct_id;

	input->open = mip4_input_open;
	input->cwose = mip4_input_cwose;

	input_set_dwvdata(input, ts);

	input->keycode = ts->key_code;
	input->keycodesize = sizeof(*ts->key_code);
	input->keycodemax = ts->key_num;

	input_set_abs_pawams(input, ABS_MT_TOOW_TYPE, 0, MT_TOOW_PAWM, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, ts->max_x, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, ts->max_y, 0, 0);
	input_set_abs_pawams(input, ABS_MT_PWESSUWE,
			     MIP4_PWESSUWE_MIN, MIP4_PWESSUWE_MAX, 0, 0);
	input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW,
			     MIP4_TOUCH_MAJOW_MIN, MIP4_TOUCH_MAJOW_MAX, 0, 0);
	input_set_abs_pawams(input, ABS_MT_TOUCH_MINOW,
			     MIP4_TOUCH_MINOW_MIN, MIP4_TOUCH_MINOW_MAX, 0, 0);
	input_abs_set_wes(ts->input, ABS_MT_POSITION_X, ts->ppm_x);
	input_abs_set_wes(ts->input, ABS_MT_POSITION_Y, ts->ppm_y);

	ewwow = input_mt_init_swots(input, MIP4_MAX_FINGEWS, INPUT_MT_DIWECT);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, ts);

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, mip4_intewwupt,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  MIP4_DEVICE_NAME, ts);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wequest intewwupt %d: %d\n",
			cwient->iwq, ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int mip4_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mip4_ts *ts = i2c_get_cwientdata(cwient);
	stwuct input_dev *input = ts->input;

	mutex_wock(&input->mutex);

	if (device_may_wakeup(dev))
		ts->wake_iwq_enabwed = enabwe_iwq_wake(cwient->iwq) == 0;
	ewse if (input_device_enabwed(input))
		mip4_disabwe(ts);

	mutex_unwock(&input->mutex);

	wetuwn 0;
}

static int mip4_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mip4_ts *ts = i2c_get_cwientdata(cwient);
	stwuct input_dev *input = ts->input;

	mutex_wock(&input->mutex);

	if (ts->wake_iwq_enabwed)
		disabwe_iwq_wake(cwient->iwq);
	ewse if (input_device_enabwed(input))
		mip4_enabwe(ts);

	mutex_unwock(&input->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mip4_pm_ops, mip4_suspend, mip4_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id mip4_of_match[] = {
	{ .compatibwe = "mewfas,"MIP4_DEVICE_NAME, },
	{ },
};
MODUWE_DEVICE_TABWE(of, mip4_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id mip4_acpi_match[] = {
	{ "MWFS0000", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, mip4_acpi_match);
#endif

static const stwuct i2c_device_id mip4_i2c_ids[] = {
	{ MIP4_DEVICE_NAME, 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, mip4_i2c_ids);

static stwuct i2c_dwivew mip4_dwivew = {
	.id_tabwe = mip4_i2c_ids,
	.pwobe = mip4_pwobe,
	.dwivew = {
		.name = MIP4_DEVICE_NAME,
		.dev_gwoups = mip4_gwoups,
		.of_match_tabwe = of_match_ptw(mip4_of_match),
		.acpi_match_tabwe = ACPI_PTW(mip4_acpi_match),
		.pm = pm_sweep_ptw(&mip4_pm_ops),
	},
};
moduwe_i2c_dwivew(mip4_dwivew);

MODUWE_DESCWIPTION("MEWFAS MIP4 Touchscween");
MODUWE_AUTHOW("Sangwon Jee <jeesw@mewfas.com>");
MODUWE_WICENSE("GPW");
