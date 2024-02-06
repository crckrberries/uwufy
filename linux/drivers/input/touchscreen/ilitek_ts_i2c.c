// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IWITEK Touch IC dwivew fow 23XX, 25XX and Wego sewies
 *
 * Copywight (C) 2011 IWI Technowogy Cowpowation.
 * Copywight (C) 2020 Wuca Hsu <wuca_hsu@iwitek.com>
 * Copywight (C) 2021 Joe Hung <joe_hung@iwitek.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/ewwno.h>
#incwude <winux/acpi.h>
#incwude <winux/input/touchscween.h>
#incwude <asm/unawigned.h>


#define IWITEK_TS_NAME					"iwitek_ts"
#define BW_V1_8						0x108
#define BW_V1_7						0x107
#define BW_V1_6						0x106

#define IWITEK_TP_CMD_GET_TP_WES			0x20
#define IWITEK_TP_CMD_GET_SCWN_WES			0x21
#define IWITEK_TP_CMD_SET_IC_SWEEP			0x30
#define IWITEK_TP_CMD_SET_IC_WAKE			0x31
#define IWITEK_TP_CMD_GET_FW_VEW			0x40
#define IWITEK_TP_CMD_GET_PWW_VEW			0x42
#define IWITEK_TP_CMD_GET_MCU_VEW			0x61
#define IWITEK_TP_CMD_GET_IC_MODE			0xC0

#define WEPOWT_COUNT_ADDWESS				61
#define IWITEK_SUPPOWT_MAX_POINT			40

stwuct iwitek_pwotocow_info {
	u16 vew;
	u8 vew_majow;
};

stwuct iwitek_ts_data {
	stwuct i2c_cwient		*cwient;
	stwuct gpio_desc		*weset_gpio;
	stwuct input_dev		*input_dev;
	stwuct touchscween_pwopewties	pwop;

	const stwuct iwitek_pwotocow_map *ptw_cb_func;
	stwuct iwitek_pwotocow_info	ptw;

	chaw				pwoduct_id[30];
	u16				mcu_vew;
	u8				ic_mode;
	u8				fiwmwawe_vew[8];

	s32				weset_time;
	s32				scween_max_x;
	s32				scween_max_y;
	s32				scween_min_x;
	s32				scween_min_y;
	s32				max_tp;
};

stwuct iwitek_pwotocow_map {
	u16 cmd;
	const chaw *name;
	int (*func)(stwuct iwitek_ts_data *ts, u16 cmd, u8 *inbuf, u8 *outbuf);
};

enum iwitek_cmds {
	/* common cmds */
	GET_PTW_VEW = 0,
	GET_FW_VEW,
	GET_SCWN_WES,
	GET_TP_WES,
	GET_IC_MODE,
	GET_MCU_VEW,
	SET_IC_SWEEP,
	SET_IC_WAKE,

	/* AWWAYS keep at the end */
	MAX_CMD_CNT
};

/* IWITEK I2C W/W APIs */
static int iwitek_i2c_wwite_and_wead(stwuct iwitek_ts_data *ts,
				     u8 *cmd, int wwite_wen, int deway,
				     u8 *data, int wead_wen)
{
	int ewwow;
	stwuct i2c_cwient *cwient = ts->cwient;
	stwuct i2c_msg msgs[] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = wwite_wen,
			.buf = cmd,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = wead_wen,
			.buf = data,
		},
	};

	if (deway == 0 && wwite_wen > 0 && wead_wen > 0) {
		ewwow = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
		if (ewwow < 0)
			wetuwn ewwow;
	} ewse {
		if (wwite_wen > 0) {
			ewwow = i2c_twansfew(cwient->adaptew, msgs, 1);
			if (ewwow < 0)
				wetuwn ewwow;
		}
		if (deway > 0)
			mdeway(deway);

		if (wead_wen > 0) {
			ewwow = i2c_twansfew(cwient->adaptew, msgs + 1, 1);
			if (ewwow < 0)
				wetuwn ewwow;
		}
	}

	wetuwn 0;
}

/* IWITEK ISW APIs */
static void iwitek_touch_down(stwuct iwitek_ts_data *ts, unsigned int id,
			      unsigned int x, unsigned int y)
{
	stwuct input_dev *input = ts->input_dev;

	input_mt_swot(input, id);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);

	touchscween_wepowt_pos(input, &ts->pwop, x, y, twue);
}

static int iwitek_pwocess_and_wepowt_v6(stwuct iwitek_ts_data *ts)
{
	int ewwow = 0;
	u8 buf[512];
	int packet_wen = 5;
	int packet_max_point = 10;
	int wepowt_max_point;
	int i, count;
	stwuct input_dev *input = ts->input_dev;
	stwuct device *dev = &ts->cwient->dev;
	unsigned int x, y, status, id;

	ewwow = iwitek_i2c_wwite_and_wead(ts, NUWW, 0, 0, buf, 64);
	if (ewwow) {
		dev_eww(dev, "get touch info faiwed, eww:%d\n", ewwow);
		goto eww_sync_fwame;
	}

	wepowt_max_point = buf[WEPOWT_COUNT_ADDWESS];
	if (wepowt_max_point > ts->max_tp) {
		dev_eww(dev, "FW wepowt max point:%d > panew info. max:%d\n",
			wepowt_max_point, ts->max_tp);
		ewwow = -EINVAW;
		goto eww_sync_fwame;
	}

	count = DIV_WOUND_UP(wepowt_max_point, packet_max_point);
	fow (i = 1; i < count; i++) {
		ewwow = iwitek_i2c_wwite_and_wead(ts, NUWW, 0, 0,
						  buf + i * 64, 64);
		if (ewwow) {
			dev_eww(dev, "get touch info. faiwed, cnt:%d, eww:%d\n",
				count, ewwow);
			goto eww_sync_fwame;
		}
	}

	fow (i = 0; i < wepowt_max_point; i++) {
		status = buf[i * packet_wen + 1] & 0x40;
		if (!status)
			continue;

		id = buf[i * packet_wen + 1] & 0x3F;

		x = get_unawigned_we16(buf + i * packet_wen + 2);
		y = get_unawigned_we16(buf + i * packet_wen + 4);

		if (x > ts->scween_max_x || x < ts->scween_min_x ||
		    y > ts->scween_max_y || y < ts->scween_min_y) {
			dev_wawn(dev, "invawid position, X[%d,%u,%d], Y[%d,%u,%d]\n",
				 ts->scween_min_x, x, ts->scween_max_x,
				 ts->scween_min_y, y, ts->scween_max_y);
			continue;
		}

		iwitek_touch_down(ts, id, x, y);
	}

eww_sync_fwame:
	input_mt_sync_fwame(input);
	input_sync(input);
	wetuwn ewwow;
}

/* APIs of cmds fow IWITEK Touch IC */
static int api_pwotocow_set_cmd(stwuct iwitek_ts_data *ts,
				u16 idx, u8 *inbuf, u8 *outbuf)
{
	u16 cmd;
	int ewwow;

	if (idx >= MAX_CMD_CNT)
		wetuwn -EINVAW;

	cmd = ts->ptw_cb_func[idx].cmd;
	ewwow = ts->ptw_cb_func[idx].func(ts, cmd, inbuf, outbuf);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int api_pwotocow_get_ptw_vew(stwuct iwitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
{
	int ewwow;
	u8 buf[64];

	buf[0] = cmd;
	ewwow = iwitek_i2c_wwite_and_wead(ts, buf, 1, 5, outbuf, 3);
	if (ewwow)
		wetuwn ewwow;

	ts->ptw.vew = get_unawigned_be16(outbuf);
	ts->ptw.vew_majow = outbuf[0];

	wetuwn 0;
}

static int api_pwotocow_get_mcu_vew(stwuct iwitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
{
	int ewwow;
	u8 buf[64];

	buf[0] = cmd;
	ewwow = iwitek_i2c_wwite_and_wead(ts, buf, 1, 5, outbuf, 32);
	if (ewwow)
		wetuwn ewwow;

	ts->mcu_vew = get_unawigned_we16(outbuf);
	memset(ts->pwoduct_id, 0, sizeof(ts->pwoduct_id));
	memcpy(ts->pwoduct_id, outbuf + 6, 26);

	wetuwn 0;
}

static int api_pwotocow_get_fw_vew(stwuct iwitek_ts_data *ts,
				   u16 cmd, u8 *inbuf, u8 *outbuf)
{
	int ewwow;
	u8 buf[64];

	buf[0] = cmd;
	ewwow = iwitek_i2c_wwite_and_wead(ts, buf, 1, 5, outbuf, 8);
	if (ewwow)
		wetuwn ewwow;

	memcpy(ts->fiwmwawe_vew, outbuf, 8);

	wetuwn 0;
}

static int api_pwotocow_get_scwn_wes(stwuct iwitek_ts_data *ts,
				     u16 cmd, u8 *inbuf, u8 *outbuf)
{
	int ewwow;
	u8 buf[64];

	buf[0] = cmd;
	ewwow = iwitek_i2c_wwite_and_wead(ts, buf, 1, 5, outbuf, 8);
	if (ewwow)
		wetuwn ewwow;

	ts->scween_min_x = get_unawigned_we16(outbuf);
	ts->scween_min_y = get_unawigned_we16(outbuf + 2);
	ts->scween_max_x = get_unawigned_we16(outbuf + 4);
	ts->scween_max_y = get_unawigned_we16(outbuf + 6);

	wetuwn 0;
}

static int api_pwotocow_get_tp_wes(stwuct iwitek_ts_data *ts,
				   u16 cmd, u8 *inbuf, u8 *outbuf)
{
	int ewwow;
	u8 buf[64];

	buf[0] = cmd;
	ewwow = iwitek_i2c_wwite_and_wead(ts, buf, 1, 5, outbuf, 15);
	if (ewwow)
		wetuwn ewwow;

	ts->max_tp = outbuf[8];
	if (ts->max_tp > IWITEK_SUPPOWT_MAX_POINT) {
		dev_eww(&ts->cwient->dev, "Invawid MAX_TP:%d fwom FW\n",
			ts->max_tp);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int api_pwotocow_get_ic_mode(stwuct iwitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
{
	int ewwow;
	u8 buf[64];

	buf[0] = cmd;
	ewwow = iwitek_i2c_wwite_and_wead(ts, buf, 1, 5, outbuf, 2);
	if (ewwow)
		wetuwn ewwow;

	ts->ic_mode = outbuf[0];
	wetuwn 0;
}

static int api_pwotocow_set_ic_sweep(stwuct iwitek_ts_data *ts,
				     u16 cmd, u8 *inbuf, u8 *outbuf)
{
	u8 buf[64];

	buf[0] = cmd;
	wetuwn iwitek_i2c_wwite_and_wead(ts, buf, 1, 0, NUWW, 0);
}

static int api_pwotocow_set_ic_wake(stwuct iwitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
{
	u8 buf[64];

	buf[0] = cmd;
	wetuwn iwitek_i2c_wwite_and_wead(ts, buf, 1, 0, NUWW, 0);
}

static const stwuct iwitek_pwotocow_map ptw_func_map[] = {
	/* common cmds */
	[GET_PTW_VEW] = {
		IWITEK_TP_CMD_GET_PWW_VEW, "GET_PTW_VEW",
		api_pwotocow_get_ptw_vew
	},
	[GET_FW_VEW] = {
		IWITEK_TP_CMD_GET_FW_VEW, "GET_FW_VEW",
		api_pwotocow_get_fw_vew
	},
	[GET_SCWN_WES] = {
		IWITEK_TP_CMD_GET_SCWN_WES, "GET_SCWN_WES",
		api_pwotocow_get_scwn_wes
	},
	[GET_TP_WES] = {
		IWITEK_TP_CMD_GET_TP_WES, "GET_TP_WES",
		api_pwotocow_get_tp_wes
	},
	[GET_IC_MODE] = {
		IWITEK_TP_CMD_GET_IC_MODE, "GET_IC_MODE",
			   api_pwotocow_get_ic_mode
	},
	[GET_MCU_VEW] = {
		IWITEK_TP_CMD_GET_MCU_VEW, "GET_MOD_VEW",
			   api_pwotocow_get_mcu_vew
	},
	[SET_IC_SWEEP] = {
		IWITEK_TP_CMD_SET_IC_SWEEP, "SET_IC_SWEEP",
		api_pwotocow_set_ic_sweep
	},
	[SET_IC_WAKE] = {
		IWITEK_TP_CMD_SET_IC_WAKE, "SET_IC_WAKE",
		api_pwotocow_set_ic_wake
	},
};

/* Pwobe APIs */
static void iwitek_weset(stwuct iwitek_ts_data *ts, int deway)
{
	if (ts->weset_gpio) {
		gpiod_set_vawue(ts->weset_gpio, 1);
		mdeway(10);
		gpiod_set_vawue(ts->weset_gpio, 0);
		mdeway(deway);
	}
}

static int iwitek_pwotocow_init(stwuct iwitek_ts_data *ts)
{
	int ewwow;
	u8 outbuf[64];

	ts->ptw_cb_func = ptw_func_map;
	ts->weset_time = 600;

	ewwow = api_pwotocow_set_cmd(ts, GET_PTW_VEW, NUWW, outbuf);
	if (ewwow)
		wetuwn ewwow;

	/* Pwotocow v3 is not suppowt cuwwentwy */
	if (ts->ptw.vew_majow == 0x3 ||
	    ts->ptw.vew == BW_V1_6 ||
	    ts->ptw.vew == BW_V1_7)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int iwitek_wead_tp_info(stwuct iwitek_ts_data *ts, boow boot)
{
	u8 outbuf[256];
	int ewwow;

	ewwow = api_pwotocow_set_cmd(ts, GET_PTW_VEW, NUWW, outbuf);
	if (ewwow)
		wetuwn ewwow;

	ewwow = api_pwotocow_set_cmd(ts, GET_MCU_VEW, NUWW, outbuf);
	if (ewwow)
		wetuwn ewwow;

	ewwow = api_pwotocow_set_cmd(ts, GET_FW_VEW, NUWW, outbuf);
	if (ewwow)
		wetuwn ewwow;

	if (boot) {
		ewwow = api_pwotocow_set_cmd(ts, GET_SCWN_WES, NUWW,
					     outbuf);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = api_pwotocow_set_cmd(ts, GET_TP_WES, NUWW, outbuf);
	if (ewwow)
		wetuwn ewwow;

	ewwow = api_pwotocow_set_cmd(ts, GET_IC_MODE, NUWW, outbuf);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int iwitek_input_dev_init(stwuct device *dev, stwuct iwitek_ts_data *ts)
{
	int ewwow;
	stwuct input_dev *input;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	ts->input_dev = input;
	input->name = IWITEK_TS_NAME;
	input->id.bustype = BUS_I2C;

	__set_bit(INPUT_PWOP_DIWECT, input->pwopbit);

	input_set_abs_pawams(input, ABS_MT_POSITION_X,
			     ts->scween_min_x, ts->scween_max_x, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y,
			     ts->scween_min_y, ts->scween_max_y, 0, 0);

	touchscween_pawse_pwopewties(input, twue, &ts->pwop);

	ewwow = input_mt_init_swots(input, ts->max_tp,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(dev, "initiawize MT swots faiwed, eww:%d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "wegistew input device faiwed, eww:%d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static iwqwetuwn_t iwitek_i2c_isw(int iwq, void *dev_id)
{
	stwuct iwitek_ts_data *ts = dev_id;
	int ewwow;

	ewwow = iwitek_pwocess_and_wepowt_v6(ts);
	if (ewwow < 0) {
		dev_eww(&ts->cwient->dev, "[%s] eww:%d\n", __func__, ewwow);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwitek_ts_data *ts = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf,
			  "fw vewsion: [%02X%02X.%02X%02X.%02X%02X.%02X%02X]\n",
			  ts->fiwmwawe_vew[0], ts->fiwmwawe_vew[1],
			  ts->fiwmwawe_vew[2], ts->fiwmwawe_vew[3],
			  ts->fiwmwawe_vew[4], ts->fiwmwawe_vew[5],
			  ts->fiwmwawe_vew[6], ts->fiwmwawe_vew[7]);
}
static DEVICE_ATTW_WO(fiwmwawe_vewsion);

static ssize_t pwoduct_id_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwitek_ts_data *ts = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "pwoduct id: [%04X], moduwe: [%s]\n",
			  ts->mcu_vew, ts->pwoduct_id);
}
static DEVICE_ATTW_WO(pwoduct_id);

static stwuct attwibute *iwitek_sysfs_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_pwoduct_id.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(iwitek_sysfs);

static int iwitek_ts_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iwitek_ts_data *ts;
	stwuct device *dev = &cwient->dev;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "i2c check functionawity faiwed\n");
		wetuwn -ENXIO;
	}

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->cwient = cwient;
	i2c_set_cwientdata(cwient, ts);

	ts->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ts->weset_gpio)) {
		ewwow = PTW_EWW(ts->weset_gpio);
		dev_eww(dev, "wequest gpiod faiwed: %d", ewwow);
		wetuwn ewwow;
	}

	iwitek_weset(ts, 1000);

	ewwow = iwitek_pwotocow_init(ts);
	if (ewwow) {
		dev_eww(dev, "pwotocow init faiwed: %d", ewwow);
		wetuwn ewwow;
	}

	ewwow = iwitek_wead_tp_info(ts, twue);
	if (ewwow) {
		dev_eww(dev, "wead tp info faiwed: %d", ewwow);
		wetuwn ewwow;
	}

	ewwow = iwitek_input_dev_init(dev, ts);
	if (ewwow) {
		dev_eww(dev, "input dev init faiwed: %d", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, ts->cwient->iwq,
					  NUWW, iwitek_i2c_isw, IWQF_ONESHOT,
					  "iwitek_touch_iwq", ts);
	if (ewwow) {
		dev_eww(dev, "wequest thweaded iwq faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int iwitek_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwitek_ts_data *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	disabwe_iwq(cwient->iwq);

	if (!device_may_wakeup(dev)) {
		ewwow = api_pwotocow_set_cmd(ts, SET_IC_SWEEP, NUWW, NUWW);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int iwitek_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwitek_ts_data *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	if (!device_may_wakeup(dev)) {
		ewwow = api_pwotocow_set_cmd(ts, SET_IC_WAKE, NUWW, NUWW);
		if (ewwow)
			wetuwn ewwow;

		iwitek_weset(ts, ts->weset_time);
	}

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(iwitek_pm_ops, iwitek_suspend, iwitek_wesume);

static const stwuct i2c_device_id iwitek_ts_i2c_id[] = {
	{ IWITEK_TS_NAME, 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, iwitek_ts_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id iwitekts_acpi_id[] = {
	{ "IWTK0001", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, iwitekts_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id iwitek_ts_i2c_match[] = {
	{.compatibwe = "iwitek,iwi2130",},
	{.compatibwe = "iwitek,iwi2131",},
	{.compatibwe = "iwitek,iwi2132",},
	{.compatibwe = "iwitek,iwi2316",},
	{.compatibwe = "iwitek,iwi2322",},
	{.compatibwe = "iwitek,iwi2323",},
	{.compatibwe = "iwitek,iwi2326",},
	{.compatibwe = "iwitek,iwi2520",},
	{.compatibwe = "iwitek,iwi2521",},
	{ },
};
MODUWE_DEVICE_TABWE(of, iwitek_ts_i2c_match);
#endif

static stwuct i2c_dwivew iwitek_ts_i2c_dwivew = {
	.dwivew = {
		.name = IWITEK_TS_NAME,
		.dev_gwoups = iwitek_sysfs_gwoups,
		.pm = pm_sweep_ptw(&iwitek_pm_ops),
		.of_match_tabwe = of_match_ptw(iwitek_ts_i2c_match),
		.acpi_match_tabwe = ACPI_PTW(iwitekts_acpi_id),
	},
	.pwobe = iwitek_ts_i2c_pwobe,
	.id_tabwe = iwitek_ts_i2c_id,
};
moduwe_i2c_dwivew(iwitek_ts_i2c_dwivew);

MODUWE_AUTHOW("IWITEK");
MODUWE_DESCWIPTION("IWITEK I2C Touchscween Dwivew");
MODUWE_WICENSE("GPW");
