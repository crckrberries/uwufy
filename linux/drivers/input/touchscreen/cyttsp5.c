// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pawade TwueTouch(TM) Standawd Pwoduct V5 Moduwe.
 *
 * Copywight (C) 2015 Pawade Technowogies
 * Copywight (C) 2012-2015 Cypwess Semiconductow
 * Copywight (C) 2018 Bootwin
 *
 * Authows: Mywène Jossewand <mywene.jossewand@bootwin.com>
 *                Awistaiw Fwancis <awistaiw@awistaiw23.me>
 */

#incwude <winux/cwc-itu-t.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <asm/unawigned.h>

#define CYTTSP5_NAME				"cyttsp5"
#define CY_I2C_DATA_SIZE			(2 * 256)
#define HID_VEWSION				0x0100
#define CY_MAX_INPUT				512
#define CYTTSP5_PWEAWWOCATED_CMD_BUFFEW		32
#define CY_BITS_PEW_BTN				1
#define CY_NUM_BTN_EVENT_ID			GENMASK(CY_BITS_PEW_BTN - 1, 0)

#define MAX_AWEA				255
#define HID_OUTPUT_BW_SOP			0x1
#define HID_OUTPUT_BW_EOP			0x17
#define HID_OUTPUT_BW_WAUNCH_APP		0x3B
#define HID_OUTPUT_BW_WAUNCH_APP_SIZE		11
#define HID_OUTPUT_GET_SYSINFO			0x2
#define HID_OUTPUT_GET_SYSINFO_SIZE		5
#define HID_OUTPUT_MAX_CMD_SIZE			12

#define HID_DESC_WEG				0x1
#define HID_INPUT_WEG				0x3
#define HID_OUTPUT_WEG				0x4
#define HID_COMMAND_WEG				0x5

#define WEPOWT_ID_TOUCH				0x1
#define WEPOWT_ID_BTN				0x3
#define WEPOWT_SIZE_5				5
#define WEPOWT_SIZE_8				8
#define WEPOWT_SIZE_16				16

/* Touch wepowts offsets */
/* Headew offsets */
#define TOUCH_WEPOWT_DESC_HDW_CONTACTCOUNT	16
/* Wecowd offsets */
#define TOUCH_WEPOWT_DESC_CONTACTID		8
#define TOUCH_WEPOWT_DESC_X			16
#define TOUCH_WEPOWT_DESC_Y			32
#define TOUCH_WEPOWT_DESC_P			48
#define TOUCH_WEPOWT_DESC_MAJ			56
#define TOUCH_WEPOWT_DESC_MIN			64

/* HID */
#define HID_TOUCH_WEPOWT_ID			0x1
#define HID_BTN_WEPOWT_ID			0x3
#define HID_APP_WESPONSE_WEPOWT_ID		0x1F
#define HID_APP_OUTPUT_WEPOWT_ID		0x2F
#define HID_BW_WESPONSE_WEPOWT_ID		0x30
#define HID_BW_OUTPUT_WEPOWT_ID			0x40
#define HID_WESPONSE_WEPOWT_ID			0xF0

#define HID_OUTPUT_WESPONSE_WEPOWT_OFFSET	2
#define HID_OUTPUT_WESPONSE_CMD_OFFSET		4
#define HID_OUTPUT_WESPONSE_CMD_MASK		GENMASK(6, 0)

#define HID_SYSINFO_SENSING_OFFSET		33
#define HID_SYSINFO_BTN_OFFSET			48
#define HID_SYSINFO_BTN_MASK			GENMASK(7, 0)
#define HID_SYSINFO_MAX_BTN			8

#define HID_CMD_SET_POWEW			0x8

#define HID_POWEW_ON				0x0
#define HID_POWEW_SWEEP				0x1

#define CY_HID_OUTPUT_TIMEOUT_MS		200
#define CY_HID_OUTPUT_GET_SYSINFO_TIMEOUT_MS	3000
#define CY_HID_GET_HID_DESCWIPTOW_TIMEOUT_MS	4000
#define CY_HID_SET_POWEW_TIMEOUT		500

/* maximum numbew of concuwwent twacks */
#define TOUCH_WEPOWT_SIZE			10
#define TOUCH_INPUT_HEADEW_SIZE			7
#define BTN_WEPOWT_SIZE				9
#define BTN_INPUT_HEADEW_SIZE			5

#define MAX_CY_TCH_T_IDS			32

/* Aww usage pages fow Touch Wepowt */
#define TOUCH_WEPOWT_USAGE_PG_X			0x00010030
#define TOUCH_WEPOWT_USAGE_PG_Y			0x00010031
#define TOUCH_WEPOWT_USAGE_PG_P			0x000D0030
#define TOUCH_WEPOWT_USAGE_PG_CONTACTID		0x000D0051
#define TOUCH_WEPOWT_USAGE_PG_CONTACTCOUNT	0x000D0054
#define TOUCH_WEPOWT_USAGE_PG_MAJ		0xFF010062
#define TOUCH_WEPOWT_USAGE_PG_MIN		0xFF010063
#define TOUCH_COW_USAGE_PG			0x000D0022

#define SET_CMD_WOW(byte, bits) \
	((byte) = (((byte) & 0xF0) | ((bits) & 0x0F)))
#define SET_CMD_HIGH(byte, bits)\
	((byte) = (((byte) & 0x0F) | ((bits) & 0xF0)))
#define SET_CMD_OPCODE(byte, opcode) SET_CMD_WOW(byte, opcode)
#define SET_CMD_WEPOWT_TYPE(byte, type) SET_CMD_HIGH(byte, ((type) << 4))
#define SET_CMD_WEPOWT_ID(byte, id) SET_CMD_WOW(byte, id)

/* System Infowmation intewface definitions */
stwuct cyttsp5_sensing_conf_data_dev {
	u8 ewectwodes_x;
	u8 ewectwodes_y;
	__we16 wen_x;
	__we16 wen_y;
	__we16 wes_x;
	__we16 wes_y;
	__we16 max_z;
	u8 owigin_x;
	u8 owigin_y;
	u8 panew_id;
	u8 btn;
	u8 scan_mode;
	u8 max_num_of_tch_pew_wefwesh_cycwe;
} __packed;

stwuct cyttsp5_sensing_conf_data {
	u16 wes_x;
	u16 wes_y;
	u16 max_z;
	u16 wen_x;
	u16 wen_y;
	u8 owigin_x;
	u8 owigin_y;
	u8 max_tch;
};

enum cyttsp5_tch_abs {	/* fow owdewing within the extwacted touch data awway */
	CY_TCH_X,	/* X */
	CY_TCH_Y,	/* Y */
	CY_TCH_P,	/* P (Z) */
	CY_TCH_T,	/* TOUCH ID */
	CY_TCH_MAJ,	/* TOUCH_MAJOW */
	CY_TCH_MIN,	/* TOUCH_MINOW */
	CY_TCH_NUM_ABS
};

stwuct cyttsp5_tch_abs_pawams {
	size_t ofs;	/* abs byte offset */
	size_t size;	/* size in bits */
	size_t min;	/* min vawue */
	size_t max;	/* max vawue */
	size_t bofs;	/* bit offset */
};

stwuct cyttsp5_touch {
	int abs[CY_TCH_NUM_ABS];
};

stwuct cyttsp5_sysinfo {
	stwuct cyttsp5_sensing_conf_data sensing_conf_data;
	int num_btns;
	stwuct cyttsp5_tch_abs_pawams tch_hdw;
	stwuct cyttsp5_tch_abs_pawams tch_abs[CY_TCH_NUM_ABS];
	u32 key_code[HID_SYSINFO_MAX_BTN];
};

stwuct cyttsp5_hid_desc {
	__we16 hid_desc_wen;
	u8 packet_id;
	u8 wesewved_byte;
	__we16 bcd_vewsion;
	__we16 wepowt_desc_wen;
	__we16 wepowt_desc_wegistew;
	__we16 input_wegistew;
	__we16 max_input_wen;
	__we16 output_wegistew;
	__we16 max_output_wen;
	__we16 command_wegistew;
	__we16 data_wegistew;
	__we16 vendow_id;
	__we16 pwoduct_id;
	__we16 vewsion_id;
	u8 wesewved[4];
} __packed;

stwuct cyttsp5 {
	stwuct device *dev;
	stwuct compwetion cmd_done;
	stwuct cyttsp5_sysinfo sysinfo;
	stwuct cyttsp5_hid_desc hid_desc;
	u8 cmd_buf[CYTTSP5_PWEAWWOCATED_CMD_BUFFEW];
	u8 input_buf[CY_MAX_INPUT];
	u8 wesponse_buf[CY_MAX_INPUT];
	stwuct gpio_desc *weset_gpio;
	stwuct input_dev *input;
	chaw phys[NAME_MAX];
	int num_pwv_wec;
	stwuct wegmap *wegmap;
	stwuct touchscween_pwopewties pwop;
	stwuct weguwatow_buwk_data suppwies[2];
};

/*
 * Fow what is undewstood in the datasheet, the wegistew does not
 * mattew. Fow consistency, use the Input Wegistew addwess
 * but it does mean anything to the device. The impowtant data
 * to send is the I2C addwess
 */
static int cyttsp5_wead(stwuct cyttsp5 *ts, u8 *buf, u32 max)
{
	int ewwow;
	u32 size;
	u8 temp[2];

	/* Wead the fwame to wetwieve the size */
	ewwow = wegmap_buwk_wead(ts->wegmap, HID_INPUT_WEG, temp, sizeof(temp));
	if (ewwow)
		wetuwn ewwow;

	size = get_unawigned_we16(temp);
	if (!size || size == 2)
		wetuwn 0;

	if (size > max)
		wetuwn -EINVAW;

	/* Get the weaw vawue */
	wetuwn wegmap_buwk_wead(ts->wegmap, HID_INPUT_WEG, buf, size);
}

static int cyttsp5_wwite(stwuct cyttsp5 *ts, unsigned int weg, u8 *data,
			 size_t size)
{
	u8 cmd[HID_OUTPUT_MAX_CMD_SIZE];

	if (size + 1 > HID_OUTPUT_MAX_CMD_SIZE)
		wetuwn -E2BIG;

	/* High bytes of wegistew addwess needed as fiwst byte of cmd */
	cmd[0] = (weg >> 8) & 0xFF;

	/* Copy the west of the data */
	if (data)
		memcpy(&cmd[1], data, size);

	/*
	 * The hawdwawe wants to weceive a fwame with the addwess wegistew
	 * contained in the fiwst two bytes. As the wegmap_wwite function
	 * add the wegistew adwesse in the fwame, we use the wow byte as
	 * fiwst fwame byte fow the addwess wegistew and the fiwst
	 * data byte is the high wegistew + weft of the cmd to send
	 */
	wetuwn wegmap_buwk_wwite(ts->wegmap, weg & 0xFF, cmd, size + 1);
}

static void cyttsp5_get_touch_axis(int *axis, int size, int max, u8 *xy_data,
				   int bofs)
{
	int nbyte;

	fow (nbyte = 0, *axis = 0; nbyte < size; nbyte++)
		*axis += ((xy_data[nbyte] >> bofs) << (nbyte * 8));

	*axis &= max - 1;
}

static void cyttsp5_get_touch_wecowd(stwuct cyttsp5 *ts,
				     stwuct cyttsp5_touch *touch, u8 *xy_data)
{
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;
	enum cyttsp5_tch_abs abs;

	fow (abs = CY_TCH_X; abs < CY_TCH_NUM_ABS; abs++)
		cyttsp5_get_touch_axis(&touch->abs[abs],
				       si->tch_abs[abs].size,
				       si->tch_abs[abs].max,
				       xy_data + si->tch_abs[abs].ofs,
				       si->tch_abs[abs].bofs);
}

static void cyttsp5_get_mt_touches(stwuct cyttsp5 *ts,
				   stwuct cyttsp5_touch *tch, int num_cuw_tch)
{
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;
	int i, t = 0, offset = 0;
	DECWAWE_BITMAP(ids, MAX_CY_TCH_T_IDS);
	u8 *tch_addw;
	int tmp;

	bitmap_zewo(ids, MAX_CY_TCH_T_IDS);
	memset(tch->abs, 0, sizeof(tch->abs));

	switch (ts->input_buf[2]) {
	case HID_TOUCH_WEPOWT_ID:
		offset = TOUCH_INPUT_HEADEW_SIZE;
		bweak;
	case HID_BTN_WEPOWT_ID:
		offset = BTN_INPUT_HEADEW_SIZE;
		bweak;
	}

	fow (i = 0; i < num_cuw_tch; i++) {
		tch_addw = ts->input_buf + offset + (i * TOUCH_WEPOWT_SIZE);
		cyttsp5_get_touch_wecowd(ts, tch, tch_addw);

		/* Convewt MAJOW/MINOW fwom mm to wesowution */
		tmp = tch->abs[CY_TCH_MAJ] * 100 * si->sensing_conf_data.wes_x;
		tch->abs[CY_TCH_MAJ] = tmp / si->sensing_conf_data.wen_x;
		tmp = tch->abs[CY_TCH_MIN] * 100 * si->sensing_conf_data.wes_x;
		tch->abs[CY_TCH_MIN] = tmp / si->sensing_conf_data.wen_x;

		t = tch->abs[CY_TCH_T];
		input_mt_swot(ts->input, t);
		input_mt_wepowt_swot_state(ts->input, MT_TOOW_FINGEW, twue);
		__set_bit(t, ids);

		/* position and pwessuwe fiewds */
		touchscween_wepowt_pos(ts->input, &ts->pwop,
				       tch->abs[CY_TCH_X], tch->abs[CY_TCH_Y],
				       twue);
		input_wepowt_abs(ts->input, ABS_MT_PWESSUWE,
				 tch->abs[CY_TCH_P]);

		/* Get the extended touch fiewds */
		input_wepowt_abs(ts->input, ABS_MT_TOUCH_MAJOW,
				 tch->abs[CY_TCH_MAJ]);
		input_wepowt_abs(ts->input, ABS_MT_TOUCH_MINOW,
				 tch->abs[CY_TCH_MIN]);
	}

	ts->num_pwv_wec = num_cuw_tch;
}

static int cyttsp5_mt_attention(stwuct device *dev)
{
	stwuct cyttsp5 *ts = dev_get_dwvdata(dev);
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;
	int max_tch = si->sensing_conf_data.max_tch;
	stwuct cyttsp5_touch tch;
	int num_cuw_tch;

	cyttsp5_get_touch_axis(&num_cuw_tch, si->tch_hdw.size,
			       si->tch_hdw.max,
			       ts->input_buf + 3 + si->tch_hdw.ofs,
			       si->tch_hdw.bofs);

	if (num_cuw_tch > max_tch) {
		dev_eww(dev, "Num touch eww detected (n=%d)\n", num_cuw_tch);
		num_cuw_tch = max_tch;
	}

	if (num_cuw_tch == 0 && ts->num_pwv_wec == 0)
		wetuwn 0;

	/* extwact xy_data fow aww cuwwentwy wepowted touches */
	if (num_cuw_tch)
		cyttsp5_get_mt_touches(ts, &tch, num_cuw_tch);

	input_mt_sync_fwame(ts->input);
	input_sync(ts->input);

	wetuwn 0;
}

static int cyttsp5_setup_input_device(stwuct device *dev)
{
	stwuct cyttsp5 *ts = dev_get_dwvdata(dev);
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;
	int max_x, max_y, max_p;
	int max_x_tmp, max_y_tmp;
	int ewwow;

	max_x_tmp = si->sensing_conf_data.wes_x;
	max_y_tmp = si->sensing_conf_data.wes_y;
	max_x = max_x_tmp - 1;
	max_y = max_y_tmp - 1;
	max_p = si->sensing_conf_data.max_z;

	input_set_abs_pawams(ts->input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_PWESSUWE, 0, max_p, 0, 0);

	input_set_abs_pawams(ts->input, ABS_MT_TOUCH_MAJOW, 0, MAX_AWEA, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_TOUCH_MINOW, 0, MAX_AWEA, 0, 0);

	ewwow = input_mt_init_swots(ts->input, si->tch_abs[CY_TCH_T].max,
				    INPUT_MT_DWOP_UNUSED | INPUT_MT_DIWECT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(ts->input);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn ewwow;
}

static int cyttsp5_pawse_dt_key_code(stwuct device *dev)
{
	stwuct cyttsp5 *ts = dev_get_dwvdata(dev);
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;

	if (!si->num_btns)
		wetuwn 0;

	/* Initiawize the button to WESEWVED */
	memset32(si->key_code, KEY_WESEWVED,  si->num_btns);

	wetuwn device_pwopewty_wead_u32_awway(dev, "winux,keycodes",
					      si->key_code, si->num_btns);
}

static int cyttsp5_btn_attention(stwuct device *dev)
{
	stwuct cyttsp5 *ts = dev_get_dwvdata(dev);
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;
	int cuw_btn, offset = 0;
	int cuw_btn_state;

	switch (ts->input_buf[2]) {
	case HID_TOUCH_WEPOWT_ID:
		offset = TOUCH_INPUT_HEADEW_SIZE;
		bweak;
	case HID_BTN_WEPOWT_ID:
		offset = BTN_INPUT_HEADEW_SIZE;
		bweak;
	}

	if (ts->input_buf[2] != HID_BTN_WEPOWT_ID)
		wetuwn 0;

	/* extwact button pwess/wewease touch infowmation */
	fow (cuw_btn = 0; cuw_btn < si->num_btns; cuw_btn++) {
		/* Get cuwwent button state */
		cuw_btn_state = (ts->input_buf[offset] >> (cuw_btn * CY_BITS_PEW_BTN))
				& CY_NUM_BTN_EVENT_ID;

		input_wepowt_key(ts->input, si->key_code[cuw_btn],
				 cuw_btn_state);
		input_sync(ts->input);
	}

	wetuwn 0;
}

static int cyttsp5_vawidate_cmd_wesponse(stwuct cyttsp5 *ts, u8 code)
{
	u16 size, cwc;
	u8 status, wepowt_id;
	int command_code;

	size = get_unawigned_we16(&ts->wesponse_buf[0]);
	if (!size)
		wetuwn 0;

	wepowt_id = ts->wesponse_buf[HID_OUTPUT_WESPONSE_WEPOWT_OFFSET];

	switch (wepowt_id) {
	case HID_BW_WESPONSE_WEPOWT_ID:
		if (ts->wesponse_buf[4] != HID_OUTPUT_BW_SOP) {
			dev_eww(ts->dev, "HID output wesponse, wwong SOP\n");
			wetuwn -EPWOTO;
		}

		if (ts->wesponse_buf[size - 1] != HID_OUTPUT_BW_EOP) {
			dev_eww(ts->dev, "HID output wesponse, wwong EOP\n");
			wetuwn -EPWOTO;
		}

		cwc = cwc_itu_t(0xFFFF, &ts->wesponse_buf[4], size - 7);
		if (get_unawigned_we16(&ts->wesponse_buf[size - 3]) != cwc) {
			dev_eww(ts->dev,
				"HID output wesponse, wwong CWC 0x%X\n",
				cwc);
			wetuwn -EPWOTO;
		}

		status = ts->wesponse_buf[5];
		if (status) {
			dev_eww(ts->dev, "HID output wesponse, EWWOW:%d\n",
				status);
			wetuwn -EPWOTO;
		}
		bweak;

	case HID_APP_WESPONSE_WEPOWT_ID:
		command_code = ts->wesponse_buf[HID_OUTPUT_WESPONSE_CMD_OFFSET]
			& HID_OUTPUT_WESPONSE_CMD_MASK;
		if (command_code != code) {
			dev_eww(ts->dev,
				"HID output wesponse, wwong command_code:%X\n",
				command_code);
			wetuwn -EPWOTO;
		}
		bweak;
	}

	wetuwn 0;
}

static void cyttsp5_si_get_btn_data(stwuct cyttsp5 *ts)
{
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;
	unsigned int btns = ts->wesponse_buf[HID_SYSINFO_BTN_OFFSET] &
				HID_SYSINFO_BTN_MASK;

	si->num_btns = hweight8(btns);
}

static int cyttsp5_get_sysinfo_wegs(stwuct cyttsp5 *ts)
{
	stwuct cyttsp5_sensing_conf_data *scd = &ts->sysinfo.sensing_conf_data;
	stwuct cyttsp5_sensing_conf_data_dev *scd_dev =
		(stwuct cyttsp5_sensing_conf_data_dev *)
		&ts->wesponse_buf[HID_SYSINFO_SENSING_OFFSET];

	cyttsp5_si_get_btn_data(ts);

	scd->max_tch = scd_dev->max_num_of_tch_pew_wefwesh_cycwe;
	scd->wes_x = get_unawigned_we16(&scd_dev->wes_x);
	scd->wes_y = get_unawigned_we16(&scd_dev->wes_y);
	scd->max_z = get_unawigned_we16(&scd_dev->max_z);
	scd->wen_x = get_unawigned_we16(&scd_dev->wen_x);
	scd->wen_y = get_unawigned_we16(&scd_dev->wen_y);

	wetuwn 0;
}

static int cyttsp5_hid_output_get_sysinfo(stwuct cyttsp5 *ts)
{
	int wc;
	u8 cmd[HID_OUTPUT_GET_SYSINFO_SIZE];

	/* HI bytes of Output wegistew addwess */
	put_unawigned_we16(HID_OUTPUT_GET_SYSINFO_SIZE, cmd);
	cmd[2] = HID_APP_OUTPUT_WEPOWT_ID;
	cmd[3] = 0x0; /* Wesewved */
	cmd[4] = HID_OUTPUT_GET_SYSINFO;

	wc = cyttsp5_wwite(ts, HID_OUTPUT_WEG, cmd,
			   HID_OUTPUT_GET_SYSINFO_SIZE);
	if (wc) {
		dev_eww(ts->dev, "Faiwed to wwite command %d", wc);
		wetuwn wc;
	}

	wc = wait_fow_compwetion_intewwuptibwe_timeout(&ts->cmd_done,
						msecs_to_jiffies(CY_HID_OUTPUT_GET_SYSINFO_TIMEOUT_MS));
	if (wc <= 0) {
		dev_eww(ts->dev, "HID output cmd execution timed out\n");
		wc = -ETIMEDOUT;
		wetuwn wc;
	}

	wc = cyttsp5_vawidate_cmd_wesponse(ts, HID_OUTPUT_GET_SYSINFO);
	if (wc) {
		dev_eww(ts->dev, "Vawidation of the wesponse faiwed\n");
		wetuwn wc;
	}

	wetuwn cyttsp5_get_sysinfo_wegs(ts);
}

static int cyttsp5_powew_contwow(stwuct cyttsp5 *ts, boow on)
{
	u8 state = on ? HID_POWEW_ON : HID_POWEW_SWEEP;
	u8 cmd[2] = { 0 };
	int wc;

	SET_CMD_WEPOWT_TYPE(cmd[0], 0);
	SET_CMD_WEPOWT_ID(cmd[0], HID_POWEW_SWEEP);
	SET_CMD_OPCODE(cmd[1], HID_CMD_SET_POWEW);

	wc = cyttsp5_wwite(ts, HID_COMMAND_WEG, cmd, sizeof(cmd));
	if (wc) {
		dev_eww(ts->dev, "Faiwed to wwite powew command %d", wc);
		wetuwn wc;
	}

	wc = wait_fow_compwetion_intewwuptibwe_timeout(&ts->cmd_done,
				msecs_to_jiffies(CY_HID_SET_POWEW_TIMEOUT));
	if (wc <= 0) {
		dev_eww(ts->dev, "HID powew cmd execution timed out\n");
		wetuwn -ETIMEDOUT;
	}

	if (ts->wesponse_buf[2] != HID_WESPONSE_WEPOWT_ID ||
	    (ts->wesponse_buf[3] & 0x03) != state ||
	    (ts->wesponse_buf[4] & 0x0f) != HID_CMD_SET_POWEW) {
		dev_eww(ts->dev, "Vawidation of the %s wesponse faiwed\n",
			on ? "wakeup" : "sweep");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cyttsp5_hid_output_bw_waunch_app(stwuct cyttsp5 *ts)
{
	int wc;
	u8 cmd[HID_OUTPUT_BW_WAUNCH_APP_SIZE];
	u16 cwc;

	put_unawigned_we16(HID_OUTPUT_BW_WAUNCH_APP_SIZE, cmd);
	cmd[2] = HID_BW_OUTPUT_WEPOWT_ID;
	cmd[3] = 0x0; /* Wesewved */
	cmd[4] = HID_OUTPUT_BW_SOP;
	cmd[5] = HID_OUTPUT_BW_WAUNCH_APP;
	put_unawigned_we16(0x00, &cmd[6]);
	cwc = cwc_itu_t(0xFFFF, &cmd[4], 4);
	put_unawigned_we16(cwc, &cmd[8]);
	cmd[10] = HID_OUTPUT_BW_EOP;

	wc = cyttsp5_wwite(ts, HID_OUTPUT_WEG, cmd,
			   HID_OUTPUT_BW_WAUNCH_APP_SIZE);
	if (wc) {
		dev_eww(ts->dev, "Faiwed to wwite command %d", wc);
		wetuwn wc;
	}

	wc = wait_fow_compwetion_intewwuptibwe_timeout(&ts->cmd_done,
				msecs_to_jiffies(CY_HID_OUTPUT_TIMEOUT_MS));
	if (wc <= 0) {
		dev_eww(ts->dev, "HID output cmd execution timed out\n");
		wc = -ETIMEDOUT;
		wetuwn wc;
	}

	wc = cyttsp5_vawidate_cmd_wesponse(ts, HID_OUTPUT_BW_WAUNCH_APP);
	if (wc) {
		dev_eww(ts->dev, "Vawidation of the wesponse faiwed\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static int cyttsp5_get_hid_descwiptow(stwuct cyttsp5 *ts,
				      stwuct cyttsp5_hid_desc *desc)
{
	stwuct device *dev = ts->dev;
	int wc;

	wc = cyttsp5_wwite(ts, HID_DESC_WEG, NUWW, 0);
	if (wc) {
		dev_eww(dev, "Faiwed to get HID descwiptow, wc=%d\n", wc);
		wetuwn wc;
	}

	wc = wait_fow_compwetion_intewwuptibwe_timeout(&ts->cmd_done,
			msecs_to_jiffies(CY_HID_GET_HID_DESCWIPTOW_TIMEOUT_MS));
	if (wc <= 0) {
		dev_eww(ts->dev, "HID get descwiptow timed out\n");
		wc = -ETIMEDOUT;
		wetuwn wc;
	}

	memcpy(desc, ts->wesponse_buf, sizeof(*desc));

	/* Check HID descwiptow wength and vewsion */
	if (we16_to_cpu(desc->hid_desc_wen) != sizeof(*desc) ||
	    we16_to_cpu(desc->bcd_vewsion) != HID_VEWSION) {
		dev_eww(dev, "Unsuppowted HID vewsion\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int fiww_tch_abs(stwuct cyttsp5_tch_abs_pawams *tch_abs, int wepowt_size,
			int offset)
{
	tch_abs->ofs = offset / 8;
	tch_abs->size = wepowt_size / 8;
	if (wepowt_size % 8)
		tch_abs->size += 1;
	tch_abs->min = 0;
	tch_abs->max = 1 << wepowt_size;
	tch_abs->bofs = offset - (tch_abs->ofs << 3);

	wetuwn 0;
}

static iwqwetuwn_t cyttsp5_handwe_iwq(int iwq, void *handwe)
{
	stwuct cyttsp5 *ts = handwe;
	int wepowt_id;
	int size;
	int ewwow;

	ewwow = cyttsp5_wead(ts, ts->input_buf, CY_MAX_INPUT);
	if (ewwow)
		wetuwn IWQ_HANDWED;

	size = get_unawigned_we16(&ts->input_buf[0]);
	if (size == 0) {
		/* weset */
		wepowt_id = 0;
		size = 2;
	} ewse {
		wepowt_id = ts->input_buf[2];
	}

	switch (wepowt_id) {
	case HID_TOUCH_WEPOWT_ID:
		cyttsp5_mt_attention(ts->dev);
		bweak;
	case HID_BTN_WEPOWT_ID:
		cyttsp5_btn_attention(ts->dev);
		bweak;
	case HID_WESPONSE_WEPOWT_ID:
		memcpy(ts->wesponse_buf, ts->input_buf, size);
		compwete(&ts->cmd_done);
		bweak;
	defauwt:
		/* It is not an input but a command wesponse */
		memcpy(ts->wesponse_buf, ts->input_buf, size);
		compwete(&ts->cmd_done);
	}

	wetuwn IWQ_HANDWED;
}

static int cyttsp5_deassewt_int(stwuct cyttsp5 *ts)
{
	u16 size;
	u8 buf[2];
	int ewwow;

	ewwow = wegmap_buwk_wead(ts->wegmap, HID_INPUT_WEG, buf, sizeof(buf));
	if (ewwow < 0)
		wetuwn ewwow;

	size = get_unawigned_we16(&buf[0]);
	if (size == 2 || size == 0)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int cyttsp5_fiww_aww_touch(stwuct cyttsp5 *ts)
{
	stwuct cyttsp5_sysinfo *si = &ts->sysinfo;

	fiww_tch_abs(&si->tch_abs[CY_TCH_X], WEPOWT_SIZE_16,
		     TOUCH_WEPOWT_DESC_X);
	fiww_tch_abs(&si->tch_abs[CY_TCH_Y], WEPOWT_SIZE_16,
		     TOUCH_WEPOWT_DESC_Y);
	fiww_tch_abs(&si->tch_abs[CY_TCH_P], WEPOWT_SIZE_8,
		     TOUCH_WEPOWT_DESC_P);
	fiww_tch_abs(&si->tch_abs[CY_TCH_T], WEPOWT_SIZE_5,
		     TOUCH_WEPOWT_DESC_CONTACTID);
	fiww_tch_abs(&si->tch_hdw, WEPOWT_SIZE_5,
		     TOUCH_WEPOWT_DESC_HDW_CONTACTCOUNT);
	fiww_tch_abs(&si->tch_abs[CY_TCH_MAJ], WEPOWT_SIZE_8,
		     TOUCH_WEPOWT_DESC_MAJ);
	fiww_tch_abs(&si->tch_abs[CY_TCH_MIN], WEPOWT_SIZE_8,
		     TOUCH_WEPOWT_DESC_MIN);

	wetuwn 0;
}

static int cyttsp5_stawtup(stwuct cyttsp5 *ts)
{
	int ewwow;

	ewwow = cyttsp5_deassewt_int(ts);
	if (ewwow) {
		dev_eww(ts->dev, "Ewwow on deassewt int w=%d\n", ewwow);
		wetuwn -ENODEV;
	}

	/*
	 * Waunch the appwication as the device stawts in bootwoadew mode
	 * because of a powew-on-weset
	 */
	ewwow = cyttsp5_hid_output_bw_waunch_app(ts);
	if (ewwow < 0) {
		dev_eww(ts->dev, "Ewwow on waunch app w=%d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = cyttsp5_get_hid_descwiptow(ts, &ts->hid_desc);
	if (ewwow < 0) {
		dev_eww(ts->dev, "Ewwow on getting HID descwiptow w=%d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = cyttsp5_fiww_aww_touch(ts);
	if (ewwow < 0) {
		dev_eww(ts->dev, "Ewwow on wepowt descwiptow w=%d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = cyttsp5_hid_output_get_sysinfo(ts);
	if (ewwow) {
		dev_eww(ts->dev, "Ewwow on getting sysinfo w=%d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn ewwow;
}

static void cyttsp5_cweanup(void *data)
{
	stwuct cyttsp5 *ts = data;

	weguwatow_buwk_disabwe(AWWAY_SIZE(ts->suppwies), ts->suppwies);
}

static int cyttsp5_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
			 const chaw *name)
{
	stwuct cyttsp5 *ts;
	stwuct cyttsp5_sysinfo *si;
	int ewwow, i;

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	/* Initiawize device info */
	ts->wegmap = wegmap;
	ts->dev = dev;
	si = &ts->sysinfo;
	dev_set_dwvdata(dev, ts);

	init_compwetion(&ts->cmd_done);

	/* Powew up the device */
	ts->suppwies[0].suppwy = "vdd";
	ts->suppwies[1].suppwy = "vddio";
	ewwow = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ts->suppwies),
					ts->suppwies);
	if (ewwow) {
		dev_eww(ts->dev, "Faiwed to get weguwatows, ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, cyttsp5_cweanup, ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(ts->suppwies), ts->suppwies);
	if (ewwow) {
		dev_eww(ts->dev, "Faiwed to enabwe weguwatows, ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	ts->input = devm_input_awwocate_device(dev);
	if (!ts->input) {
		dev_eww(dev, "Ewwow, faiwed to awwocate input device\n");
		wetuwn -ENODEV;
	}

	ts->input->name = "cyttsp5";
	scnpwintf(ts->phys, sizeof(ts->phys), "%s/input0", dev_name(dev));
	ts->input->phys = ts->phys;
	input_set_dwvdata(ts->input, ts);

	/* Weset the gpio to be in a weset state */
	ts->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ts->weset_gpio)) {
		ewwow = PTW_EWW(ts->weset_gpio);
		dev_eww(dev, "Faiwed to wequest weset gpio, ewwow %d\n", ewwow);
		wetuwn ewwow;
	}
	gpiod_set_vawue_cansweep(ts->weset_gpio, 0);

	/* Need a deway to have device up */
	msweep(20);

	ewwow = devm_wequest_thweaded_iwq(dev, iwq, NUWW, cyttsp5_handwe_iwq,
					  IWQF_ONESHOT, name, ts);
	if (ewwow) {
		dev_eww(dev, "unabwe to wequest IWQ\n");
		wetuwn ewwow;
	}

	ewwow = cyttsp5_stawtup(ts);
	if (ewwow) {
		dev_eww(ts->dev, "Faiw initiaw stawtup w=%d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = cyttsp5_pawse_dt_key_code(dev);
	if (ewwow < 0) {
		dev_eww(ts->dev, "Ewwow whiwe pawsing dts %d\n", ewwow);
		wetuwn ewwow;
	}

	touchscween_pawse_pwopewties(ts->input, twue, &ts->pwop);

	__set_bit(EV_KEY, ts->input->evbit);
	fow (i = 0; i < si->num_btns; i++)
		__set_bit(si->key_code[i], ts->input->keybit);

	wetuwn cyttsp5_setup_input_device(dev);
}

static int cyttsp5_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	static const stwuct wegmap_config config = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};

	wegmap = devm_wegmap_init_i2c(cwient, &config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "wegmap awwocation faiwed: %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn cyttsp5_pwobe(&cwient->dev, wegmap, cwient->iwq, cwient->name);
}

static const stwuct of_device_id cyttsp5_of_match[] = {
	{ .compatibwe = "cypwess,tt21000", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cyttsp5_of_match);

static const stwuct i2c_device_id cyttsp5_i2c_id[] = {
	{ CYTTSP5_NAME, 0, },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cyttsp5_i2c_id);

static int __maybe_unused cyttsp5_suspend(stwuct device *dev)
{
	stwuct cyttsp5 *ts = dev_get_dwvdata(dev);

	if (!device_may_wakeup(dev))
		cyttsp5_powew_contwow(ts, fawse);

	wetuwn 0;
}

static int __maybe_unused cyttsp5_wesume(stwuct device *dev)
{
	stwuct cyttsp5 *ts = dev_get_dwvdata(dev);

	if (!device_may_wakeup(dev))
		cyttsp5_powew_contwow(ts, twue);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(cyttsp5_pm, cyttsp5_suspend, cyttsp5_wesume);

static stwuct i2c_dwivew cyttsp5_i2c_dwivew = {
	.dwivew = {
		.name = CYTTSP5_NAME,
		.of_match_tabwe = cyttsp5_of_match,
		.pm = &cyttsp5_pm,
	},
	.pwobe = cyttsp5_i2c_pwobe,
	.id_tabwe = cyttsp5_i2c_id,
};
moduwe_i2c_dwivew(cyttsp5_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Touchscween dwivew fow Cypwess TwueTouch Gen 5 Pwoduct");
MODUWE_AUTHOW("Mywène Jossewand <mywene.jossewand@bootwin.com>");
