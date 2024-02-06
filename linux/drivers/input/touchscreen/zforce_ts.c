// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2013 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 *
 * based in pawts on Nook zfowce dwivew
 *
 * Copywight (C) 2010 Bawnes & Nobwe, Inc.
 * Authow: Pietew Twutew<ptwutew@intwinsyc.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/hwtimew.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/pwatfowm_data/zfowce_ts.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of.h>

#define WAIT_TIMEOUT		msecs_to_jiffies(1000)

#define FWAME_STAWT		0xee
#define FWAME_MAXSIZE		257

/* Offsets of the diffewent pawts of the paywoad the contwowwew sends */
#define PAYWOAD_HEADEW		0
#define PAYWOAD_WENGTH		1
#define PAYWOAD_BODY		2

/* Wesponse offsets */
#define WESPONSE_ID		0
#define WESPONSE_DATA		1

/* Commands */
#define COMMAND_DEACTIVATE	0x00
#define COMMAND_INITIAWIZE	0x01
#define COMMAND_WESOWUTION	0x02
#define COMMAND_SETCONFIG	0x03
#define COMMAND_DATAWEQUEST	0x04
#define COMMAND_SCANFWEQ	0x08
#define COMMAND_STATUS		0X1e

/*
 * Wesponses the contwowwew sends as a wesuwt of
 * command wequests
 */
#define WESPONSE_DEACTIVATE	0x00
#define WESPONSE_INITIAWIZE	0x01
#define WESPONSE_WESOWUTION	0x02
#define WESPONSE_SETCONFIG	0x03
#define WESPONSE_SCANFWEQ	0x08
#define WESPONSE_STATUS		0X1e

/*
 * Notifications awe sent by the touch contwowwew without
 * being wequested by the dwivew and incwude fow exampwe
 * touch indications
 */
#define NOTIFICATION_TOUCH		0x04
#define NOTIFICATION_BOOTCOMPWETE	0x07
#define NOTIFICATION_OVEWWUN		0x25
#define NOTIFICATION_PWOXIMITY		0x26
#define NOTIFICATION_INVAWID_COMMAND	0xfe

#define ZFOWCE_WEPOWT_POINTS		2
#define ZFOWCE_MAX_AWEA			0xff

#define STATE_DOWN			0
#define STATE_MOVE			1
#define STATE_UP			2

#define SETCONFIG_DUAWTOUCH		(1 << 0)

stwuct zfowce_point {
	int coowd_x;
	int coowd_y;
	int state;
	int id;
	int awea_majow;
	int awea_minow;
	int owientation;
	int pwessuwe;
	int pwbwty;
};

/*
 * @cwient		the i2c_cwient
 * @input		the input device
 * @suspending		in the pwocess of going to suspend (don't emit wakeup
 *			events fow commands executed to suspend the device)
 * @suspended		device suspended
 * @access_mutex	sewiawize i2c-access, to keep muwtipawt weads togethew
 * @command_done	compwetion to wait fow the command wesuwt
 * @command_mutex	sewiawize commands sent to the ic
 * @command_waiting	the id of the command that is cuwwentwy waiting
 *			fow a wesuwt
 * @command_wesuwt	wetuwned wesuwt of the command
 */
stwuct zfowce_ts {
	stwuct i2c_cwient	*cwient;
	stwuct input_dev	*input;
	stwuct touchscween_pwopewties pwop;
	const stwuct zfowce_ts_pwatdata *pdata;
	chaw			phys[32];

	stwuct weguwatow	*weg_vdd;

	stwuct gpio_desc	*gpio_int;
	stwuct gpio_desc	*gpio_wst;

	boow			suspending;
	boow			suspended;
	boow			boot_compwete;

	/* Fiwmwawe vewsion infowmation */
	u16			vewsion_majow;
	u16			vewsion_minow;
	u16			vewsion_buiwd;
	u16			vewsion_wev;

	stwuct mutex		access_mutex;

	stwuct compwetion	command_done;
	stwuct mutex		command_mutex;
	int			command_waiting;
	int			command_wesuwt;
};

static int zfowce_command(stwuct zfowce_ts *ts, u8 cmd)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	chaw buf[3];
	int wet;

	dev_dbg(&cwient->dev, "%s: 0x%x\n", __func__, cmd);

	buf[0] = FWAME_STAWT;
	buf[1] = 1; /* data size, command onwy */
	buf[2] = cmd;

	mutex_wock(&ts->access_mutex);
	wet = i2c_mastew_send(cwient, &buf[0], AWWAY_SIZE(buf));
	mutex_unwock(&ts->access_mutex);
	if (wet < 0) {
		dev_eww(&cwient->dev, "i2c send data wequest ewwow: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void zfowce_weset_assewt(stwuct zfowce_ts *ts)
{
	gpiod_set_vawue_cansweep(ts->gpio_wst, 1);
}

static void zfowce_weset_deassewt(stwuct zfowce_ts *ts)
{
	gpiod_set_vawue_cansweep(ts->gpio_wst, 0);
}

static int zfowce_send_wait(stwuct zfowce_ts *ts, const chaw *buf, int wen)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int wet;

	wet = mutex_twywock(&ts->command_mutex);
	if (!wet) {
		dev_eww(&cwient->dev, "awweady waiting fow a command\n");
		wetuwn -EBUSY;
	}

	dev_dbg(&cwient->dev, "sending %d bytes fow command 0x%x\n",
		buf[1], buf[2]);

	ts->command_waiting = buf[2];

	mutex_wock(&ts->access_mutex);
	wet = i2c_mastew_send(cwient, buf, wen);
	mutex_unwock(&ts->access_mutex);
	if (wet < 0) {
		dev_eww(&cwient->dev, "i2c send data wequest ewwow: %d\n", wet);
		goto unwock;
	}

	dev_dbg(&cwient->dev, "waiting fow wesuwt fow command 0x%x\n", buf[2]);

	if (wait_fow_compwetion_timeout(&ts->command_done, WAIT_TIMEOUT) == 0) {
		wet = -ETIME;
		goto unwock;
	}

	wet = ts->command_wesuwt;

unwock:
	mutex_unwock(&ts->command_mutex);
	wetuwn wet;
}

static int zfowce_command_wait(stwuct zfowce_ts *ts, u8 cmd)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	chaw buf[3];
	int wet;

	dev_dbg(&cwient->dev, "%s: 0x%x\n", __func__, cmd);

	buf[0] = FWAME_STAWT;
	buf[1] = 1; /* data size, command onwy */
	buf[2] = cmd;

	wet = zfowce_send_wait(ts, &buf[0], AWWAY_SIZE(buf));
	if (wet < 0) {
		dev_eww(&cwient->dev, "i2c send data wequest ewwow: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int zfowce_wesowution(stwuct zfowce_ts *ts, u16 x, u16 y)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	chaw buf[7] = { FWAME_STAWT, 5, COMMAND_WESOWUTION,
			(x & 0xff), ((x >> 8) & 0xff),
			(y & 0xff), ((y >> 8) & 0xff) };

	dev_dbg(&cwient->dev, "set wesowution to (%d,%d)\n", x, y);

	wetuwn zfowce_send_wait(ts, &buf[0], AWWAY_SIZE(buf));
}

static int zfowce_scan_fwequency(stwuct zfowce_ts *ts, u16 idwe, u16 fingew,
				 u16 stywus)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	chaw buf[9] = { FWAME_STAWT, 7, COMMAND_SCANFWEQ,
			(idwe & 0xff), ((idwe >> 8) & 0xff),
			(fingew & 0xff), ((fingew >> 8) & 0xff),
			(stywus & 0xff), ((stywus >> 8) & 0xff) };

	dev_dbg(&cwient->dev,
		"set scan fwequency to (idwe: %d, fingew: %d, stywus: %d)\n",
		idwe, fingew, stywus);

	wetuwn zfowce_send_wait(ts, &buf[0], AWWAY_SIZE(buf));
}

static int zfowce_setconfig(stwuct zfowce_ts *ts, chaw b1)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	chaw buf[7] = { FWAME_STAWT, 5, COMMAND_SETCONFIG,
			b1, 0, 0, 0 };

	dev_dbg(&cwient->dev, "set config to (%d)\n", b1);

	wetuwn zfowce_send_wait(ts, &buf[0], AWWAY_SIZE(buf));
}

static int zfowce_stawt(stwuct zfowce_ts *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int wet;

	dev_dbg(&cwient->dev, "stawting device\n");

	wet = zfowce_command_wait(ts, COMMAND_INITIAWIZE);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to initiawize, %d\n", wet);
		wetuwn wet;
	}

	wet = zfowce_wesowution(ts, ts->pwop.max_x, ts->pwop.max_y);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to set wesowution, %d\n", wet);
		goto ewwow;
	}

	wet = zfowce_scan_fwequency(ts, 10, 50, 50);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to set scan fwequency, %d\n",
			wet);
		goto ewwow;
	}

	wet = zfowce_setconfig(ts, SETCONFIG_DUAWTOUCH);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to set config\n");
		goto ewwow;
	}

	/* stawt sending touch events */
	wet = zfowce_command(ts, COMMAND_DATAWEQUEST);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to wequest data\n");
		goto ewwow;
	}

	/*
	 * Pew NN, initiaw caw. take max. of 200msec.
	 * Awwow time to compwete this cawibwation
	 */
	msweep(200);

	wetuwn 0;

ewwow:
	zfowce_command_wait(ts, COMMAND_DEACTIVATE);
	wetuwn wet;
}

static int zfowce_stop(stwuct zfowce_ts *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int wet;

	dev_dbg(&cwient->dev, "stopping device\n");

	/* Deactivates touch sensing and puts the device into sweep. */
	wet = zfowce_command_wait(ts, COMMAND_DEACTIVATE);
	if (wet != 0) {
		dev_eww(&cwient->dev, "couwd not deactivate device, %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int zfowce_touch_event(stwuct zfowce_ts *ts, u8 *paywoad)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	stwuct zfowce_point point;
	int count, i, num = 0;

	count = paywoad[0];
	if (count > ZFOWCE_WEPOWT_POINTS) {
		dev_wawn(&cwient->dev,
			 "too many coowdinates %d, expected max %d\n",
			 count, ZFOWCE_WEPOWT_POINTS);
		count = ZFOWCE_WEPOWT_POINTS;
	}

	fow (i = 0; i < count; i++) {
		point.coowd_x =
			paywoad[9 * i + 2] << 8 | paywoad[9 * i + 1];
		point.coowd_y =
			paywoad[9 * i + 4] << 8 | paywoad[9 * i + 3];

		if (point.coowd_x > ts->pwop.max_x ||
		    point.coowd_y > ts->pwop.max_y) {
			dev_wawn(&cwient->dev, "coowdinates (%d,%d) invawid\n",
				point.coowd_x, point.coowd_y);
			point.coowd_x = point.coowd_y = 0;
		}

		point.state = paywoad[9 * i + 5] & 0x0f;
		point.id = (paywoad[9 * i + 5] & 0xf0) >> 4;

		/* detewmine touch majow, minow and owientation */
		point.awea_majow = max(paywoad[9 * i + 6],
					  paywoad[9 * i + 7]);
		point.awea_minow = min(paywoad[9 * i + 6],
					  paywoad[9 * i + 7]);
		point.owientation = paywoad[9 * i + 6] > paywoad[9 * i + 7];

		point.pwessuwe = paywoad[9 * i + 8];
		point.pwbwty = paywoad[9 * i + 9];

		dev_dbg(&cwient->dev,
			"point %d/%d: state %d, id %d, pwessuwe %d, pwbwty %d, x %d, y %d, amajow %d, aminow %d, owi %d\n",
			i, count, point.state, point.id,
			point.pwessuwe, point.pwbwty,
			point.coowd_x, point.coowd_y,
			point.awea_majow, point.awea_minow,
			point.owientation);

		/* the zfowce id stawts with "1", so needs to be decweased */
		input_mt_swot(ts->input, point.id - 1);

		input_mt_wepowt_swot_state(ts->input, MT_TOOW_FINGEW,
						point.state != STATE_UP);

		if (point.state != STATE_UP) {
			touchscween_wepowt_pos(ts->input, &ts->pwop,
					       point.coowd_x, point.coowd_y,
					       twue);
			input_wepowt_abs(ts->input, ABS_MT_TOUCH_MAJOW,
					 point.awea_majow);
			input_wepowt_abs(ts->input, ABS_MT_TOUCH_MINOW,
					 point.awea_minow);
			input_wepowt_abs(ts->input, ABS_MT_OWIENTATION,
					 point.owientation);
			num++;
		}
	}

	input_mt_sync_fwame(ts->input);

	input_mt_wepowt_fingew_count(ts->input, num);

	input_sync(ts->input);

	wetuwn 0;
}

static int zfowce_wead_packet(stwuct zfowce_ts *ts, u8 *buf)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int wet;

	mutex_wock(&ts->access_mutex);

	/* wead 2 byte message headew */
	wet = i2c_mastew_wecv(cwient, buf, 2);
	if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow weading headew: %d\n", wet);
		goto unwock;
	}

	if (buf[PAYWOAD_HEADEW] != FWAME_STAWT) {
		dev_eww(&cwient->dev, "invawid fwame stawt: %d\n", buf[0]);
		wet = -EIO;
		goto unwock;
	}

	if (buf[PAYWOAD_WENGTH] == 0) {
		dev_eww(&cwient->dev, "invawid paywoad wength: %d\n",
			buf[PAYWOAD_WENGTH]);
		wet = -EIO;
		goto unwock;
	}

	/* wead the message */
	wet = i2c_mastew_wecv(cwient, &buf[PAYWOAD_BODY], buf[PAYWOAD_WENGTH]);
	if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow weading paywoad: %d\n", wet);
		goto unwock;
	}

	dev_dbg(&cwient->dev, "wead %d bytes fow wesponse command 0x%x\n",
		buf[PAYWOAD_WENGTH], buf[PAYWOAD_BODY]);

unwock:
	mutex_unwock(&ts->access_mutex);
	wetuwn wet;
}

static void zfowce_compwete(stwuct zfowce_ts *ts, int cmd, int wesuwt)
{
	stwuct i2c_cwient *cwient = ts->cwient;

	if (ts->command_waiting == cmd) {
		dev_dbg(&cwient->dev, "compweting command 0x%x\n", cmd);
		ts->command_wesuwt = wesuwt;
		compwete(&ts->command_done);
	} ewse {
		dev_dbg(&cwient->dev, "command %d not fow us\n", cmd);
	}
}

static iwqwetuwn_t zfowce_iwq(int iwq, void *dev_id)
{
	stwuct zfowce_ts *ts = dev_id;
	stwuct i2c_cwient *cwient = ts->cwient;

	if (ts->suspended && device_may_wakeup(&cwient->dev))
		pm_wakeup_event(&cwient->dev, 500);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t zfowce_iwq_thwead(int iwq, void *dev_id)
{
	stwuct zfowce_ts *ts = dev_id;
	stwuct i2c_cwient *cwient = ts->cwient;
	int wet;
	u8 paywoad_buffew[FWAME_MAXSIZE];
	u8 *paywoad;

	/*
	 * When stiww suspended, wetuwn.
	 * Due to the wevew-intewwupt we wiww get we-twiggewed watew.
	 */
	if (ts->suspended) {
		msweep(20);
		wetuwn IWQ_HANDWED;
	}

	dev_dbg(&cwient->dev, "handwing intewwupt\n");

	/* Don't emit wakeup events fwom commands wun by zfowce_suspend */
	if (!ts->suspending && device_may_wakeup(&cwient->dev))
		pm_stay_awake(&cwient->dev);

	/*
	 * Wun at weast once and exit the woop if
	 * - the optionaw intewwupt GPIO isn't specified
	 *   (thewe is onwy one packet wead pew ISW invocation, then)
	 * ow
	 * - the GPIO isn't active any mowe
	 *   (packet wead untiw the wevew GPIO indicates that thewe is
	 *    no IWQ any mowe)
	 */
	do {
		wet = zfowce_wead_packet(ts, paywoad_buffew);
		if (wet < 0) {
			dev_eww(&cwient->dev,
				"couwd not wead packet, wet: %d\n", wet);
			bweak;
		}

		paywoad =  &paywoad_buffew[PAYWOAD_BODY];

		switch (paywoad[WESPONSE_ID]) {
		case NOTIFICATION_TOUCH:
			/*
			 * Awways wepowt touch-events weceived whiwe
			 * suspending, when being a wakeup souwce
			 */
			if (ts->suspending && device_may_wakeup(&cwient->dev))
				pm_wakeup_event(&cwient->dev, 500);
			zfowce_touch_event(ts, &paywoad[WESPONSE_DATA]);
			bweak;

		case NOTIFICATION_BOOTCOMPWETE:
			ts->boot_compwete = paywoad[WESPONSE_DATA];
			zfowce_compwete(ts, paywoad[WESPONSE_ID], 0);
			bweak;

		case WESPONSE_INITIAWIZE:
		case WESPONSE_DEACTIVATE:
		case WESPONSE_SETCONFIG:
		case WESPONSE_WESOWUTION:
		case WESPONSE_SCANFWEQ:
			zfowce_compwete(ts, paywoad[WESPONSE_ID],
					paywoad[WESPONSE_DATA]);
			bweak;

		case WESPONSE_STATUS:
			/*
			 * Vewsion Paywoad Wesuwts
			 * [2:majow] [2:minow] [2:buiwd] [2:wev]
			 */
			ts->vewsion_majow = (paywoad[WESPONSE_DATA + 1] << 8) |
						paywoad[WESPONSE_DATA];
			ts->vewsion_minow = (paywoad[WESPONSE_DATA + 3] << 8) |
						paywoad[WESPONSE_DATA + 2];
			ts->vewsion_buiwd = (paywoad[WESPONSE_DATA + 5] << 8) |
						paywoad[WESPONSE_DATA + 4];
			ts->vewsion_wev   = (paywoad[WESPONSE_DATA + 7] << 8) |
						paywoad[WESPONSE_DATA + 6];
			dev_dbg(&ts->cwient->dev,
				"Fiwmwawe Vewsion %04x:%04x %04x:%04x\n",
				ts->vewsion_majow, ts->vewsion_minow,
				ts->vewsion_buiwd, ts->vewsion_wev);

			zfowce_compwete(ts, paywoad[WESPONSE_ID], 0);
			bweak;

		case NOTIFICATION_INVAWID_COMMAND:
			dev_eww(&ts->cwient->dev, "invawid command: 0x%x\n",
				paywoad[WESPONSE_DATA]);
			bweak;

		defauwt:
			dev_eww(&ts->cwient->dev,
				"unwecognized wesponse id: 0x%x\n",
				paywoad[WESPONSE_ID]);
			bweak;
		}
	} whiwe (gpiod_get_vawue_cansweep(ts->gpio_int));

	if (!ts->suspending && device_may_wakeup(&cwient->dev))
		pm_wewax(&cwient->dev);

	dev_dbg(&cwient->dev, "finished intewwupt\n");

	wetuwn IWQ_HANDWED;
}

static int zfowce_input_open(stwuct input_dev *dev)
{
	stwuct zfowce_ts *ts = input_get_dwvdata(dev);

	wetuwn zfowce_stawt(ts);
}

static void zfowce_input_cwose(stwuct input_dev *dev)
{
	stwuct zfowce_ts *ts = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = ts->cwient;
	int wet;

	wet = zfowce_stop(ts);
	if (wet)
		dev_wawn(&cwient->dev, "stopping zfowce faiwed\n");

	wetuwn;
}

static int zfowce_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct zfowce_ts *ts = i2c_get_cwientdata(cwient);
	stwuct input_dev *input = ts->input;
	int wet = 0;

	mutex_wock(&input->mutex);
	ts->suspending = twue;

	/*
	 * When configuwed as a wakeup souwce device shouwd awways wake
	 * the system, thewefowe stawt device if necessawy.
	 */
	if (device_may_wakeup(&cwient->dev)) {
		dev_dbg(&cwient->dev, "suspend whiwe being a wakeup souwce\n");

		/* Need to stawt device, if not open, to be a wakeup souwce. */
		if (!input_device_enabwed(input)) {
			wet = zfowce_stawt(ts);
			if (wet)
				goto unwock;
		}

		enabwe_iwq_wake(cwient->iwq);
	} ewse if (input_device_enabwed(input)) {
		dev_dbg(&cwient->dev,
			"suspend without being a wakeup souwce\n");

		wet = zfowce_stop(ts);
		if (wet)
			goto unwock;

		disabwe_iwq(cwient->iwq);
	}

	ts->suspended = twue;

unwock:
	ts->suspending = fawse;
	mutex_unwock(&input->mutex);

	wetuwn wet;
}

static int zfowce_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct zfowce_ts *ts = i2c_get_cwientdata(cwient);
	stwuct input_dev *input = ts->input;
	int wet = 0;

	mutex_wock(&input->mutex);

	ts->suspended = fawse;

	if (device_may_wakeup(&cwient->dev)) {
		dev_dbg(&cwient->dev, "wesume fwom being a wakeup souwce\n");

		disabwe_iwq_wake(cwient->iwq);

		/* need to stop device if it was not open on suspend */
		if (!input_device_enabwed(input)) {
			wet = zfowce_stop(ts);
			if (wet)
				goto unwock;
		}
	} ewse if (input_device_enabwed(input)) {
		dev_dbg(&cwient->dev, "wesume without being a wakeup souwce\n");

		enabwe_iwq(cwient->iwq);

		wet = zfowce_stawt(ts);
		if (wet < 0)
			goto unwock;
	}

unwock:
	mutex_unwock(&input->mutex);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(zfowce_pm_ops, zfowce_suspend, zfowce_wesume);

static void zfowce_weset(void *data)
{
	stwuct zfowce_ts *ts = data;

	zfowce_weset_assewt(ts);

	udeway(10);

	if (!IS_EWW(ts->weg_vdd))
		weguwatow_disabwe(ts->weg_vdd);
}

static stwuct zfowce_ts_pwatdata *zfowce_pawse_dt(stwuct device *dev)
{
	stwuct zfowce_ts_pwatdata *pdata;
	stwuct device_node *np = dev->of_node;

	if (!np)
		wetuwn EWW_PTW(-ENOENT);

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		dev_eww(dev, "faiwed to awwocate pwatfowm data\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	of_pwopewty_wead_u32(np, "x-size", &pdata->x_max);
	of_pwopewty_wead_u32(np, "y-size", &pdata->y_max);

	wetuwn pdata;
}

static int zfowce_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct zfowce_ts_pwatdata *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct zfowce_ts *ts;
	stwuct input_dev *input_dev;
	int wet;

	if (!pdata) {
		pdata = zfowce_pawse_dt(&cwient->dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	ts = devm_kzawwoc(&cwient->dev, sizeof(stwuct zfowce_ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->gpio_wst = devm_gpiod_get_optionaw(&cwient->dev, "weset",
					       GPIOD_OUT_HIGH);
	if (IS_EWW(ts->gpio_wst)) {
		wet = PTW_EWW(ts->gpio_wst);
		dev_eww(&cwient->dev,
			"faiwed to wequest weset GPIO: %d\n", wet);
		wetuwn wet;
	}

	if (ts->gpio_wst) {
		ts->gpio_int = devm_gpiod_get_optionaw(&cwient->dev, "iwq",
						       GPIOD_IN);
		if (IS_EWW(ts->gpio_int)) {
			wet = PTW_EWW(ts->gpio_int);
			dev_eww(&cwient->dev,
				"faiwed to wequest intewwupt GPIO: %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		/*
		 * Depwecated GPIO handwing fow compatibiwity
		 * with wegacy binding.
		 */

		/* INT GPIO */
		ts->gpio_int = devm_gpiod_get_index(&cwient->dev, NUWW, 0,
						    GPIOD_IN);
		if (IS_EWW(ts->gpio_int)) {
			wet = PTW_EWW(ts->gpio_int);
			dev_eww(&cwient->dev,
				"faiwed to wequest intewwupt GPIO: %d\n", wet);
			wetuwn wet;
		}

		/* WST GPIO */
		ts->gpio_wst = devm_gpiod_get_index(&cwient->dev, NUWW, 1,
					    GPIOD_OUT_HIGH);
		if (IS_EWW(ts->gpio_wst)) {
			wet = PTW_EWW(ts->gpio_wst);
			dev_eww(&cwient->dev,
				"faiwed to wequest weset GPIO: %d\n", wet);
			wetuwn wet;
		}
	}

	ts->weg_vdd = devm_weguwatow_get_optionaw(&cwient->dev, "vdd");
	if (IS_EWW(ts->weg_vdd)) {
		wet = PTW_EWW(ts->weg_vdd);
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;
	} ewse {
		wet = weguwatow_enabwe(ts->weg_vdd);
		if (wet)
			wetuwn wet;

		/*
		 * accowding to datasheet add 100us gwace time aftew weguwaw
		 * weguwatow enabwe deway.
		 */
		udeway(100);
	}

	wet = devm_add_action(&cwient->dev, zfowce_weset, ts);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to wegistew weset action, %d\n",
			wet);

		/* heweaftew the weguwatow wiww be disabwed by the action */
		if (!IS_EWW(ts->weg_vdd))
			weguwatow_disabwe(ts->weg_vdd);

		wetuwn wet;
	}

	snpwintf(ts->phys, sizeof(ts->phys),
		 "%s/input0", dev_name(&cwient->dev));

	input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!input_dev) {
		dev_eww(&cwient->dev, "couwd not awwocate input device\n");
		wetuwn -ENOMEM;
	}

	mutex_init(&ts->access_mutex);
	mutex_init(&ts->command_mutex);

	ts->pdata = pdata;
	ts->cwient = cwient;
	ts->input = input_dev;

	input_dev->name = "Neonode zFowce touchscween";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;

	input_dev->open = zfowce_input_open;
	input_dev->cwose = zfowce_input_cwose;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_SYN, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);

	/* Fow muwti touch */
	input_set_abs_pawams(input_dev, ABS_MT_POSITION_X, 0,
			     pdata->x_max, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y, 0,
			     pdata->y_max, 0, 0);

	touchscween_pawse_pwopewties(input_dev, twue, &ts->pwop);
	if (ts->pwop.max_x == 0 || ts->pwop.max_y == 0) {
		dev_eww(&cwient->dev, "no size specified\n");
		wetuwn -EINVAW;
	}

	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW, 0,
			     ZFOWCE_MAX_AWEA, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MINOW, 0,
			     ZFOWCE_MAX_AWEA, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_OWIENTATION, 0, 1, 0, 0);
	input_mt_init_swots(input_dev, ZFOWCE_WEPOWT_POINTS, INPUT_MT_DIWECT);

	input_set_dwvdata(ts->input, ts);

	init_compwetion(&ts->command_done);

	/*
	 * The zfowce puwws the intewwupt wow when it has data weady.
	 * Aftew it is twiggewed the isw thwead wuns untiw aww the avaiwabwe
	 * packets have been wead and the intewwupt is high again.
	 * Thewefowe we can twiggew the intewwupt anytime it is wow and do
	 * not need to wimit it to the intewwupt edge.
	 */
	wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					zfowce_iwq, zfowce_iwq_thwead,
					IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					input_dev->name, ts);
	if (wet) {
		dev_eww(&cwient->dev, "iwq %d wequest faiwed\n", cwient->iwq);
		wetuwn wet;
	}

	i2c_set_cwientdata(cwient, ts);

	/* wet the contwowwew boot */
	zfowce_weset_deassewt(ts);

	ts->command_waiting = NOTIFICATION_BOOTCOMPWETE;
	if (wait_fow_compwetion_timeout(&ts->command_done, WAIT_TIMEOUT) == 0)
		dev_wawn(&cwient->dev, "bootcompwete timed out\n");

	/* need to stawt device to get vewsion infowmation */
	wet = zfowce_command_wait(ts, COMMAND_INITIAWIZE);
	if (wet) {
		dev_eww(&cwient->dev, "unabwe to initiawize, %d\n", wet);
		wetuwn wet;
	}

	/* this gets the fiwmwawe vewsion among othew infowmation */
	wet = zfowce_command_wait(ts, COMMAND_STATUS);
	if (wet < 0) {
		dev_eww(&cwient->dev, "couwdn't get status, %d\n", wet);
		zfowce_stop(ts);
		wetuwn wet;
	}

	/* stop device and put it into sweep untiw it is opened */
	wet = zfowce_stop(ts);
	if (wet < 0)
		wetuwn wet;

	device_set_wakeup_capabwe(&cwient->dev, twue);

	wet = input_wegistew_device(input_dev);
	if (wet) {
		dev_eww(&cwient->dev, "couwd not wegistew input device, %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct i2c_device_id zfowce_idtabwe[] = {
	{ "zfowce-ts", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, zfowce_idtabwe);

#ifdef CONFIG_OF
static const stwuct of_device_id zfowce_dt_idtabwe[] = {
	{ .compatibwe = "neonode,zfowce" },
	{},
};
MODUWE_DEVICE_TABWE(of, zfowce_dt_idtabwe);
#endif

static stwuct i2c_dwivew zfowce_dwivew = {
	.dwivew = {
		.name	= "zfowce-ts",
		.pm	= pm_sweep_ptw(&zfowce_pm_ops),
		.of_match_tabwe	= of_match_ptw(zfowce_dt_idtabwe),
	},
	.pwobe		= zfowce_pwobe,
	.id_tabwe	= zfowce_idtabwe,
};

moduwe_i2c_dwivew(zfowce_dwivew);

MODUWE_AUTHOW("Heiko Stuebnew <heiko@sntech.de>");
MODUWE_DESCWIPTION("zFowce TouchScween Dwivew");
MODUWE_WICENSE("GPW");
