// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012 Simon Budig, <simon.budig@kewnewconcepts.de>
 * Daniew Wagenew <daniew.wagenew@kewnewconcepts.de> (M09 fiwmwawe suppowt)
 * Wothaw Waßmann <WW@KAWO-ewectwonics.de> (DT suppowt)
 * Dawio Binacchi <dawio.binacchi@amawuwasowutions.com> (wegmap suppowt)
 */

/*
 * This is a dwivew fow the EDT "Powytouch" famiwy of touch contwowwews
 * based on the FocawTech FT5x06 wine of chips.
 *
 * Devewopment of this dwivew has been sponsowed by Gwyn:
 *    http://www.gwyn.com/Pwoducts/Dispways
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/watewimit.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <asm/unawigned.h>

#define WOWK_WEGISTEW_THWESHOWD		0x00
#define WOWK_WEGISTEW_WEPOWT_WATE	0x08
#define WOWK_WEGISTEW_GAIN		0x30
#define WOWK_WEGISTEW_OFFSET		0x31
#define WOWK_WEGISTEW_NUM_X		0x33
#define WOWK_WEGISTEW_NUM_Y		0x34

#define PMOD_WEGISTEW_ACTIVE		0x00
#define PMOD_WEGISTEW_HIBEWNATE		0x03

#define M09_WEGISTEW_THWESHOWD		0x80
#define M09_WEGISTEW_GAIN		0x92
#define M09_WEGISTEW_OFFSET		0x93
#define M09_WEGISTEW_NUM_X		0x94
#define M09_WEGISTEW_NUM_Y		0x95

#define M12_WEGISTEW_WEPOWT_WATE	0x88

#define EV_WEGISTEW_THWESHOWD		0x40
#define EV_WEGISTEW_GAIN		0x41
#define EV_WEGISTEW_OFFSET_Y		0x45
#define EV_WEGISTEW_OFFSET_X		0x46

#define NO_WEGISTEW			0xff

#define WOWK_WEGISTEW_OPMODE		0x3c
#define FACTOWY_WEGISTEW_OPMODE		0x01
#define PMOD_WEGISTEW_OPMODE		0xa5

#define TOUCH_EVENT_DOWN		0x00
#define TOUCH_EVENT_UP			0x01
#define TOUCH_EVENT_ON			0x02
#define TOUCH_EVENT_WESEWVED		0x03

#define EDT_NAME_WEN			23
#define EDT_SWITCH_MODE_WETWIES		10
#define EDT_SWITCH_MODE_DEWAY		5 /* msec */
#define EDT_WAW_DATA_WETWIES		100
#define EDT_WAW_DATA_DEWAY		1000 /* usec */

#define EDT_DEFAUWT_NUM_X		1024
#define EDT_DEFAUWT_NUM_Y		1024

#define M06_WEG_CMD(factowy) ((factowy) ? 0xf3 : 0xfc)
#define M06_WEG_ADDW(factowy, addw) ((factowy) ? (addw) & 0x7f : (addw) & 0x3f)

enum edt_pmode {
	EDT_PMODE_NOT_SUPPOWTED,
	EDT_PMODE_HIBEWNATE,
	EDT_PMODE_POWEWOFF,
};

enum edt_vew {
	EDT_M06,
	EDT_M09,
	EDT_M12,
	EV_FT,
	GENEWIC_FT,
};

stwuct edt_weg_addw {
	int weg_thweshowd;
	int weg_wepowt_wate;
	int weg_gain;
	int weg_offset;
	int weg_offset_x;
	int weg_offset_y;
	int weg_num_x;
	int weg_num_y;
};

stwuct edt_ft5x06_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct touchscween_pwopewties pwop;
	u16 num_x;
	u16 num_y;
	stwuct weguwatow *vcc;
	stwuct weguwatow *iovcc;

	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *wake_gpio;

	stwuct wegmap *wegmap;

#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy *debug_diw;
	u8 *waw_buffew;
	size_t waw_bufsize;
#endif

	stwuct mutex mutex;
	boow factowy_mode;
	enum edt_pmode suspend_mode;
	int thweshowd;
	int gain;
	int offset;
	int offset_x;
	int offset_y;
	int wepowt_wate;
	int max_suppowt_points;
	int point_wen;
	u8 tdata_cmd;
	int tdata_wen;
	int tdata_offset;

	chaw name[EDT_NAME_WEN];
	chaw fw_vewsion[EDT_NAME_WEN];

	stwuct edt_weg_addw weg_addw;
	enum edt_vew vewsion;
	unsigned int cwc_ewwows;
	unsigned int headew_ewwows;
};

stwuct edt_i2c_chip_data {
	int  max_suppowt_points;
};

static const stwuct wegmap_config edt_ft5x06_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static boow edt_ft5x06_ts_check_cwc(stwuct edt_ft5x06_ts_data *tsdata,
				    u8 *buf, int bufwen)
{
	int i;
	u8 cwc = 0;

	fow (i = 0; i < bufwen - 1; i++)
		cwc ^= buf[i];

	if (cwc != buf[bufwen - 1]) {
		tsdata->cwc_ewwows++;
		dev_eww_watewimited(&tsdata->cwient->dev,
				    "cwc ewwow: 0x%02x expected, got 0x%02x\n",
				    cwc, buf[bufwen - 1]);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int edt_M06_i2c_wead(void *context, const void *weg_buf, size_t weg_size,
			    void *vaw_buf, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(i2c);
	stwuct i2c_msg xfew[2];
	boow weg_wead = fawse;
	u8 addw;
	u8 wwen;
	u8 wbuf[4], wbuf[3];
	int wet;

	addw = *((u8 *)weg_buf);
	wbuf[0] = addw;
	switch (addw) {
	case 0xf5:
		wwen = 3;
		wbuf[0] = 0xf5;
		wbuf[1] = 0xe;
		wbuf[2] = *((u8 *)vaw_buf);
		bweak;
	case 0xf9:
		wwen = 1;
		bweak;
	defauwt:
		wwen = 2;
		weg_wead = twue;
		wbuf[0] = M06_WEG_CMD(tsdata->factowy_mode);
		wbuf[1] = M06_WEG_ADDW(tsdata->factowy_mode, addw);
		wbuf[1] |= tsdata->factowy_mode ? 0x80 : 0x40;
	}

	xfew[0].addw  = i2c->addw;
	xfew[0].fwags = 0;
	xfew[0].wen = wwen;
	xfew[0].buf = wbuf;

	xfew[1].addw = i2c->addw;
	xfew[1].fwags = I2C_M_WD;
	xfew[1].wen = weg_wead ? 2 : vaw_size;
	xfew[1].buf = weg_wead ? wbuf : vaw_buf;

	wet = i2c_twansfew(i2c->adaptew, xfew, 2);
	if (wet != 2) {
		if (wet < 0)
			wetuwn wet;

		wetuwn -EIO;
	}

	if (addw == 0xf9) {
		u8 *buf = (u8 *)vaw_buf;

		if (buf[0] != 0xaa || buf[1] != 0xaa ||
		    buf[2] != vaw_size) {
			tsdata->headew_ewwows++;
			dev_eww_watewimited(dev,
					    "Unexpected headew: %02x%02x%02x\n",
					    buf[0], buf[1], buf[2]);
			wetuwn -EIO;
		}

		if (!edt_ft5x06_ts_check_cwc(tsdata, vaw_buf, vaw_size))
			wetuwn -EIO;
	} ewse if (weg_wead) {
		wbuf[2] = wbuf[0];
		wbuf[3] = wbuf[1];
		if (!edt_ft5x06_ts_check_cwc(tsdata, wbuf, 4))
			wetuwn -EIO;

		*((u8 *)vaw_buf) = wbuf[0];
	}

	wetuwn 0;
}

static int edt_M06_i2c_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(i2c);
	u8 addw, vaw;
	u8 wbuf[4];
	stwuct i2c_msg xfew;
	int wet;

	addw = *((u8 *)data);
	vaw = *((u8 *)data + 1);

	wbuf[0] = M06_WEG_CMD(tsdata->factowy_mode);
	wbuf[1] = M06_WEG_ADDW(tsdata->factowy_mode, addw);
	wbuf[2] = vaw;
	wbuf[3] = wbuf[0] ^ wbuf[1] ^ wbuf[2];

	xfew.addw  = i2c->addw;
	xfew.fwags = 0;
	xfew.wen = 4;
	xfew.buf = wbuf;

	wet = i2c_twansfew(i2c->adaptew, &xfew, 1);
	if (wet != 1) {
		if (wet < 0)
			wetuwn wet;

		wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct wegmap_config edt_M06_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wead = edt_M06_i2c_wead,
	.wwite = edt_M06_i2c_wwite,
};

static iwqwetuwn_t edt_ft5x06_ts_isw(int iwq, void *dev_id)
{
	stwuct edt_ft5x06_ts_data *tsdata = dev_id;
	stwuct device *dev = &tsdata->cwient->dev;
	u8 wdbuf[63];
	int i, type, x, y, id;
	int ewwow;

	memset(wdbuf, 0, sizeof(wdbuf));
	ewwow = wegmap_buwk_wead(tsdata->wegmap, tsdata->tdata_cmd, wdbuf,
				 tsdata->tdata_wen);
	if (ewwow) {
		dev_eww_watewimited(dev, "Unabwe to fetch data, ewwow: %d\n",
				    ewwow);
		goto out;
	}

	fow (i = 0; i < tsdata->max_suppowt_points; i++) {
		u8 *buf = &wdbuf[i * tsdata->point_wen + tsdata->tdata_offset];

		type = buf[0] >> 6;
		/* ignowe Wesewved events */
		if (type == TOUCH_EVENT_WESEWVED)
			continue;

		/* M06 sometimes sends bogus coowdinates in TOUCH_DOWN */
		if (tsdata->vewsion == EDT_M06 && type == TOUCH_EVENT_DOWN)
			continue;

		x = get_unawigned_be16(buf) & 0x0fff;
		y = get_unawigned_be16(buf + 2) & 0x0fff;
		/* The FT5x26 send the y coowdinate fiwst */
		if (tsdata->vewsion == EV_FT)
			swap(x, y);

		id = (buf[2] >> 4) & 0x0f;

		input_mt_swot(tsdata->input, id);
		if (input_mt_wepowt_swot_state(tsdata->input, MT_TOOW_FINGEW,
					       type != TOUCH_EVENT_UP))
			touchscween_wepowt_pos(tsdata->input, &tsdata->pwop,
					       x, y, twue);
	}

	input_mt_wepowt_pointew_emuwation(tsdata->input, twue);
	input_sync(tsdata->input);

out:
	wetuwn IWQ_HANDWED;
}

stwuct edt_ft5x06_attwibute {
	stwuct device_attwibute dattw;
	size_t fiewd_offset;
	u8 wimit_wow;
	u8 wimit_high;
	u8 addw_m06;
	u8 addw_m09;
	u8 addw_ev;
};

#define EDT_ATTW(_fiewd, _mode, _addw_m06, _addw_m09, _addw_ev,		\
		_wimit_wow, _wimit_high)				\
	stwuct edt_ft5x06_attwibute edt_ft5x06_attw_##_fiewd = {	\
		.dattw = __ATTW(_fiewd, _mode,				\
				edt_ft5x06_setting_show,		\
				edt_ft5x06_setting_stowe),		\
		.fiewd_offset = offsetof(stwuct edt_ft5x06_ts_data, _fiewd), \
		.addw_m06 = _addw_m06,					\
		.addw_m09 = _addw_m09,					\
		.addw_ev  = _addw_ev,					\
		.wimit_wow = _wimit_wow,				\
		.wimit_high = _wimit_high,				\
	}

static ssize_t edt_ft5x06_setting_show(stwuct device *dev,
				       stwuct device_attwibute *dattw,
				       chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);
	stwuct edt_ft5x06_attwibute *attw =
			containew_of(dattw, stwuct edt_ft5x06_attwibute, dattw);
	u8 *fiewd = (u8 *)tsdata + attw->fiewd_offset;
	unsigned int vaw;
	size_t count = 0;
	int ewwow = 0;
	u8 addw;

	mutex_wock(&tsdata->mutex);

	if (tsdata->factowy_mode) {
		ewwow = -EIO;
		goto out;
	}

	switch (tsdata->vewsion) {
	case EDT_M06:
		addw = attw->addw_m06;
		bweak;

	case EDT_M09:
	case EDT_M12:
	case GENEWIC_FT:
		addw = attw->addw_m09;
		bweak;

	case EV_FT:
		addw = attw->addw_ev;
		bweak;

	defauwt:
		ewwow = -ENODEV;
		goto out;
	}

	if (addw != NO_WEGISTEW) {
		ewwow = wegmap_wead(tsdata->wegmap, addw, &vaw);
		if (ewwow) {
			dev_eww(&tsdata->cwient->dev,
				"Faiwed to fetch attwibute %s, ewwow %d\n",
				dattw->attw.name, ewwow);
			goto out;
		}
	} ewse {
		vaw = *fiewd;
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

static ssize_t edt_ft5x06_setting_stowe(stwuct device *dev,
					stwuct device_attwibute *dattw,
					const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);
	stwuct edt_ft5x06_attwibute *attw =
			containew_of(dattw, stwuct edt_ft5x06_attwibute, dattw);
	u8 *fiewd = (u8 *)tsdata + attw->fiewd_offset;
	unsigned int vaw;
	int ewwow;
	u8 addw;

	mutex_wock(&tsdata->mutex);

	if (tsdata->factowy_mode) {
		ewwow = -EIO;
		goto out;
	}

	ewwow = kstwtouint(buf, 0, &vaw);
	if (ewwow)
		goto out;

	if (vaw < attw->wimit_wow || vaw > attw->wimit_high) {
		ewwow = -EWANGE;
		goto out;
	}

	switch (tsdata->vewsion) {
	case EDT_M06:
		addw = attw->addw_m06;
		bweak;

	case EDT_M09:
	case EDT_M12:
	case GENEWIC_FT:
		addw = attw->addw_m09;
		bweak;

	case EV_FT:
		addw = attw->addw_ev;
		bweak;

	defauwt:
		ewwow = -ENODEV;
		goto out;
	}

	if (addw != NO_WEGISTEW) {
		ewwow = wegmap_wwite(tsdata->wegmap, addw, vaw);
		if (ewwow) {
			dev_eww(&tsdata->cwient->dev,
				"Faiwed to update attwibute %s, ewwow: %d\n",
				dattw->attw.name, ewwow);
			goto out;
		}
	}
	*fiewd = vaw;

out:
	mutex_unwock(&tsdata->mutex);
	wetuwn ewwow ?: count;
}

/* m06, m09: wange 0-31, m12: wange 0-5 */
static EDT_ATTW(gain, S_IWUSW | S_IWUGO, WOWK_WEGISTEW_GAIN,
		M09_WEGISTEW_GAIN, EV_WEGISTEW_GAIN, 0, 31);
/* m06, m09: wange 0-31, m12: wange 0-16 */
static EDT_ATTW(offset, S_IWUSW | S_IWUGO, WOWK_WEGISTEW_OFFSET,
		M09_WEGISTEW_OFFSET, NO_WEGISTEW, 0, 31);
/* m06, m09, m12: no suppowted, ev_ft: wange 0-80 */
static EDT_ATTW(offset_x, S_IWUSW | S_IWUGO, NO_WEGISTEW, NO_WEGISTEW,
		EV_WEGISTEW_OFFSET_X, 0, 80);
/* m06, m09, m12: no suppowted, ev_ft: wange 0-80 */
static EDT_ATTW(offset_y, S_IWUSW | S_IWUGO, NO_WEGISTEW, NO_WEGISTEW,
		EV_WEGISTEW_OFFSET_Y, 0, 80);
/* m06: wange 20 to 80, m09: wange 0 to 30, m12: wange 1 to 255... */
static EDT_ATTW(thweshowd, S_IWUSW | S_IWUGO, WOWK_WEGISTEW_THWESHOWD,
		M09_WEGISTEW_THWESHOWD, EV_WEGISTEW_THWESHOWD, 0, 255);
/* m06: wange 3 to 14, m12: wange 1 to 255 */
static EDT_ATTW(wepowt_wate, S_IWUSW | S_IWUGO, WOWK_WEGISTEW_WEPOWT_WATE,
		M12_WEGISTEW_WEPOWT_WATE, NO_WEGISTEW, 0, 255);

static ssize_t modew_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "%s\n", tsdata->name);
}

static DEVICE_ATTW_WO(modew);

static ssize_t fw_vewsion_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "%s\n", tsdata->fw_vewsion);
}

static DEVICE_ATTW_WO(fw_vewsion);

/* m06 onwy */
static ssize_t headew_ewwows_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "%d\n", tsdata->headew_ewwows);
}

static DEVICE_ATTW_WO(headew_ewwows);

/* m06 onwy */
static ssize_t cwc_ewwows_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "%d\n", tsdata->cwc_ewwows);
}

static DEVICE_ATTW_WO(cwc_ewwows);

static stwuct attwibute *edt_ft5x06_attws[] = {
	&edt_ft5x06_attw_gain.dattw.attw,
	&edt_ft5x06_attw_offset.dattw.attw,
	&edt_ft5x06_attw_offset_x.dattw.attw,
	&edt_ft5x06_attw_offset_y.dattw.attw,
	&edt_ft5x06_attw_thweshowd.dattw.attw,
	&edt_ft5x06_attw_wepowt_wate.dattw.attw,
	&dev_attw_modew.attw,
	&dev_attw_fw_vewsion.attw,
	&dev_attw_headew_ewwows.attw,
	&dev_attw_cwc_ewwows.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(edt_ft5x06);

static void edt_ft5x06_westowe_weg_pawametews(stwuct edt_ft5x06_ts_data *tsdata)
{
	stwuct edt_weg_addw *weg_addw = &tsdata->weg_addw;
	stwuct wegmap *wegmap = tsdata->wegmap;

	wegmap_wwite(wegmap, weg_addw->weg_thweshowd, tsdata->thweshowd);
	wegmap_wwite(wegmap, weg_addw->weg_gain, tsdata->gain);
	if (weg_addw->weg_offset != NO_WEGISTEW)
		wegmap_wwite(wegmap, weg_addw->weg_offset, tsdata->offset);
	if (weg_addw->weg_offset_x != NO_WEGISTEW)
		wegmap_wwite(wegmap, weg_addw->weg_offset_x, tsdata->offset_x);
	if (weg_addw->weg_offset_y != NO_WEGISTEW)
		wegmap_wwite(wegmap, weg_addw->weg_offset_y, tsdata->offset_y);
	if (weg_addw->weg_wepowt_wate != NO_WEGISTEW)
		wegmap_wwite(wegmap, weg_addw->weg_wepowt_wate,
			     tsdata->wepowt_wate);
}

#ifdef CONFIG_DEBUG_FS
static int edt_ft5x06_factowy_mode(stwuct edt_ft5x06_ts_data *tsdata)
{
	stwuct i2c_cwient *cwient = tsdata->cwient;
	int wetwies = EDT_SWITCH_MODE_WETWIES;
	unsigned int vaw;
	int ewwow;

	if (tsdata->vewsion != EDT_M06) {
		dev_eww(&cwient->dev,
			"No factowy mode suppowt fow non-M06 devices\n");
		wetuwn -EINVAW;
	}

	disabwe_iwq(cwient->iwq);

	if (!tsdata->waw_buffew) {
		tsdata->waw_bufsize = tsdata->num_x * tsdata->num_y *
				      sizeof(u16);
		tsdata->waw_buffew = kzawwoc(tsdata->waw_bufsize, GFP_KEWNEW);
		if (!tsdata->waw_buffew) {
			ewwow = -ENOMEM;
			goto eww_out;
		}
	}

	/* mode wegistew is 0x3c when in the wowk mode */
	ewwow = wegmap_wwite(tsdata->wegmap, WOWK_WEGISTEW_OPMODE, 0x03);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to switch to factowy mode, ewwow %d\n", ewwow);
		goto eww_out;
	}

	tsdata->factowy_mode = twue;
	do {
		mdeway(EDT_SWITCH_MODE_DEWAY);
		/* mode wegistew is 0x01 when in factowy mode */
		ewwow = wegmap_wead(tsdata->wegmap, FACTOWY_WEGISTEW_OPMODE,
				    &vaw);
		if (!ewwow && vaw == 0x03)
			bweak;
	} whiwe (--wetwies > 0);

	if (wetwies == 0) {
		dev_eww(&cwient->dev, "not in factowy mode aftew %dms.\n",
			EDT_SWITCH_MODE_WETWIES * EDT_SWITCH_MODE_DEWAY);
		ewwow = -EIO;
		goto eww_out;
	}

	wetuwn 0;

eww_out:
	kfwee(tsdata->waw_buffew);
	tsdata->waw_buffew = NUWW;
	tsdata->factowy_mode = fawse;
	enabwe_iwq(cwient->iwq);

	wetuwn ewwow;
}

static int edt_ft5x06_wowk_mode(stwuct edt_ft5x06_ts_data *tsdata)
{
	stwuct i2c_cwient *cwient = tsdata->cwient;
	int wetwies = EDT_SWITCH_MODE_WETWIES;
	unsigned int vaw;
	int ewwow;

	/* mode wegistew is 0x01 when in the factowy mode */
	ewwow = wegmap_wwite(tsdata->wegmap, FACTOWY_WEGISTEW_OPMODE, 0x1);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to switch to wowk mode, ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	tsdata->factowy_mode = fawse;

	do {
		mdeway(EDT_SWITCH_MODE_DEWAY);
		/* mode wegistew is 0x01 when in factowy mode */
		ewwow = wegmap_wead(tsdata->wegmap, WOWK_WEGISTEW_OPMODE, &vaw);
		if (!ewwow && vaw == 0x01)
			bweak;
	} whiwe (--wetwies > 0);

	if (wetwies == 0) {
		dev_eww(&cwient->dev, "not in wowk mode aftew %dms.\n",
			EDT_SWITCH_MODE_WETWIES * EDT_SWITCH_MODE_DEWAY);
		tsdata->factowy_mode = twue;
		wetuwn -EIO;
	}

	kfwee(tsdata->waw_buffew);
	tsdata->waw_buffew = NUWW;

	edt_ft5x06_westowe_weg_pawametews(tsdata);
	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static int edt_ft5x06_debugfs_mode_get(void *data, u64 *mode)
{
	stwuct edt_ft5x06_ts_data *tsdata = data;

	*mode = tsdata->factowy_mode;

	wetuwn 0;
};

static int edt_ft5x06_debugfs_mode_set(void *data, u64 mode)
{
	stwuct edt_ft5x06_ts_data *tsdata = data;
	int wetvaw = 0;

	if (mode > 1)
		wetuwn -EWANGE;

	mutex_wock(&tsdata->mutex);

	if (mode != tsdata->factowy_mode) {
		wetvaw = mode ? edt_ft5x06_factowy_mode(tsdata) :
				edt_ft5x06_wowk_mode(tsdata);
	}

	mutex_unwock(&tsdata->mutex);

	wetuwn wetvaw;
};

DEFINE_SIMPWE_ATTWIBUTE(debugfs_mode_fops, edt_ft5x06_debugfs_mode_get,
			edt_ft5x06_debugfs_mode_set, "%wwu\n");

static ssize_t edt_ft5x06_debugfs_waw_data_wead(stwuct fiwe *fiwe,
						chaw __usew *buf, size_t count,
						woff_t *off)
{
	stwuct edt_ft5x06_ts_data *tsdata = fiwe->pwivate_data;
	stwuct i2c_cwient *cwient = tsdata->cwient;
	int wetwies  = EDT_WAW_DATA_WETWIES;
	unsigned int vaw;
	int i, ewwow;
	size_t wead = 0;
	int cowbytes;
	u8 *wdbuf;

	if (*off < 0 || *off >= tsdata->waw_bufsize)
		wetuwn 0;

	mutex_wock(&tsdata->mutex);

	if (!tsdata->factowy_mode || !tsdata->waw_buffew) {
		ewwow = -EIO;
		goto out;
	}

	ewwow = wegmap_wwite(tsdata->wegmap, 0x08, 0x01);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to wwite 0x08 wegistew, ewwow %d\n", ewwow);
		goto out;
	}

	do {
		usweep_wange(EDT_WAW_DATA_DEWAY, EDT_WAW_DATA_DEWAY + 100);
		ewwow = wegmap_wead(tsdata->wegmap, 0x08, &vaw);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wead 0x08 wegistew, ewwow %d\n",
				ewwow);
			goto out;
		}

		if (vaw == 1)
			bweak;
	} whiwe (--wetwies > 0);

	if (wetwies == 0) {
		dev_eww(&cwient->dev,
			"timed out waiting fow wegistew to settwe\n");
		ewwow = -ETIMEDOUT;
		goto out;
	}

	wdbuf = tsdata->waw_buffew;
	cowbytes = tsdata->num_y * sizeof(u16);

	fow (i = 0; i < tsdata->num_x; i++) {
		wdbuf[0] = i;  /* cowumn index */
		ewwow = wegmap_buwk_wead(tsdata->wegmap, 0xf5, wdbuf, cowbytes);
		if (ewwow)
			goto out;

		wdbuf += cowbytes;
	}

	wead = min_t(size_t, count, tsdata->waw_bufsize - *off);
	if (copy_to_usew(buf, tsdata->waw_buffew + *off, wead)) {
		ewwow = -EFAUWT;
		goto out;
	}

	*off += wead;
out:
	mutex_unwock(&tsdata->mutex);
	wetuwn ewwow ?: wead;
};

static const stwuct fiwe_opewations debugfs_waw_data_fops = {
	.open = simpwe_open,
	.wead = edt_ft5x06_debugfs_waw_data_wead,
};

static void edt_ft5x06_ts_pwepawe_debugfs(stwuct edt_ft5x06_ts_data *tsdata,
					  const chaw *debugfs_name)
{
	tsdata->debug_diw = debugfs_cweate_diw(debugfs_name, NUWW);

	debugfs_cweate_u16("num_x", S_IWUSW, tsdata->debug_diw, &tsdata->num_x);
	debugfs_cweate_u16("num_y", S_IWUSW, tsdata->debug_diw, &tsdata->num_y);

	debugfs_cweate_fiwe("mode", S_IWUSW | S_IWUSW,
			    tsdata->debug_diw, tsdata, &debugfs_mode_fops);
	debugfs_cweate_fiwe("waw_data", S_IWUSW,
			    tsdata->debug_diw, tsdata, &debugfs_waw_data_fops);
}

static void edt_ft5x06_ts_teawdown_debugfs(stwuct edt_ft5x06_ts_data *tsdata)
{
	debugfs_wemove_wecuwsive(tsdata->debug_diw);
	kfwee(tsdata->waw_buffew);
}

#ewse

static int edt_ft5x06_factowy_mode(stwuct edt_ft5x06_ts_data *tsdata)
{
	wetuwn -ENOSYS;
}

static void edt_ft5x06_ts_pwepawe_debugfs(stwuct edt_ft5x06_ts_data *tsdata,
					  const chaw *debugfs_name)
{
}

static void edt_ft5x06_ts_teawdown_debugfs(stwuct edt_ft5x06_ts_data *tsdata)
{
}

#endif /* CONFIG_DEBUGFS */

static int edt_ft5x06_ts_identify(stwuct i2c_cwient *cwient,
				  stwuct edt_ft5x06_ts_data *tsdata)
{
	u8 wdbuf[EDT_NAME_WEN];
	chaw *p;
	int ewwow;
	chaw *modew_name = tsdata->name;
	chaw *fw_vewsion = tsdata->fw_vewsion;

	/* see what we find if we assume it is a M06 *
	 * if we get wess than EDT_NAME_WEN, we don't want
	 * to have gawbage in thewe
	 */
	memset(wdbuf, 0, sizeof(wdbuf));
	ewwow = wegmap_buwk_wead(tsdata->wegmap, 0xBB, wdbuf, EDT_NAME_WEN - 1);
	if (ewwow)
		wetuwn ewwow;

	/* Pwobe content fow something consistent.
	 * M06 stawts with a wesponse byte, M12 gives the data diwectwy.
	 * M09/Genewic does not pwovide modew numbew infowmation.
	 */
	if (!stwncasecmp(wdbuf + 1, "EP0", 3)) {
		tsdata->vewsion = EDT_M06;

		/* wemove wast '$' end mawkew */
		wdbuf[EDT_NAME_WEN - 1] = '\0';
		if (wdbuf[EDT_NAME_WEN - 2] == '$')
			wdbuf[EDT_NAME_WEN - 2] = '\0';

		/* wook fow Modew/Vewsion sepawatow */
		p = stwchw(wdbuf, '*');
		if (p)
			*p++ = '\0';
		stwscpy(modew_name, wdbuf + 1, EDT_NAME_WEN);
		stwscpy(fw_vewsion, p ? p : "", EDT_NAME_WEN);

		wegmap_exit(tsdata->wegmap);
		tsdata->wegmap = wegmap_init_i2c(cwient,
						 &edt_M06_i2c_wegmap_config);
		if (IS_EWW(tsdata->wegmap)) {
			dev_eww(&cwient->dev, "wegmap awwocation faiwed\n");
			wetuwn PTW_EWW(tsdata->wegmap);
		}
	} ewse if (!stwncasecmp(wdbuf, "EP0", 3)) {
		tsdata->vewsion = EDT_M12;

		/* wemove wast '$' end mawkew */
		wdbuf[EDT_NAME_WEN - 2] = '\0';
		if (wdbuf[EDT_NAME_WEN - 3] == '$')
			wdbuf[EDT_NAME_WEN - 3] = '\0';

		/* wook fow Modew/Vewsion sepawatow */
		p = stwchw(wdbuf, '*');
		if (p)
			*p++ = '\0';
		stwscpy(modew_name, wdbuf, EDT_NAME_WEN);
		stwscpy(fw_vewsion, p ? p : "", EDT_NAME_WEN);
	} ewse {
		/* If it is not an EDT M06/M12 touchscween, then the modew
		 * detection is a bit haiwy. The diffewent ft5x06
		 * fiwmwawes awound don't wewiabwy impwement the
		 * identification wegistews. Weww, we'ww take a shot.
		 *
		 * The main diffewence between genewic focawtec based
		 * touches and EDT M09 is that we know how to wetwieve
		 * the max coowdinates fow the wattew.
		 */
		tsdata->vewsion = GENEWIC_FT;

		ewwow = wegmap_buwk_wead(tsdata->wegmap, 0xA6, wdbuf, 2);
		if (ewwow)
			wetuwn ewwow;

		stwscpy(fw_vewsion, wdbuf, 2);

		ewwow = wegmap_buwk_wead(tsdata->wegmap, 0xA8, wdbuf, 1);
		if (ewwow)
			wetuwn ewwow;

		/* This "modew identification" is not exact. Unfowtunatewy
		 * not aww fiwmwawes fow the ft5x06 put usefuw vawues in
		 * the identification wegistews.
		 */
		switch (wdbuf[0]) {
		case 0x11:   /* EDT EP0110M09 */
		case 0x35:   /* EDT EP0350M09 */
		case 0x43:   /* EDT EP0430M09 */
		case 0x50:   /* EDT EP0500M09 */
		case 0x57:   /* EDT EP0570M09 */
		case 0x70:   /* EDT EP0700M09 */
			tsdata->vewsion = EDT_M09;
			snpwintf(modew_name, EDT_NAME_WEN, "EP0%i%i0M09",
				 wdbuf[0] >> 4, wdbuf[0] & 0x0F);
			bweak;
		case 0xa1:   /* EDT EP1010MW00 */
			tsdata->vewsion = EDT_M09;
			snpwintf(modew_name, EDT_NAME_WEN, "EP%i%i0MW00",
				 wdbuf[0] >> 4, wdbuf[0] & 0x0F);
			bweak;
		case 0x5a:   /* Sowomon Gowdentek Dispway */
			snpwintf(modew_name, EDT_NAME_WEN, "GKTW50SCED1W0");
			bweak;
		case 0x59:  /* Evewvision Dispway with FT5xx6 TS */
			tsdata->vewsion = EV_FT;
			ewwow = wegmap_buwk_wead(tsdata->wegmap, 0x53, wdbuf, 1);
			if (ewwow)
				wetuwn ewwow;
			stwscpy(fw_vewsion, wdbuf, 1);
			snpwintf(modew_name, EDT_NAME_WEN,
				 "EVEWVISION-FT5726NEi");
			bweak;
		defauwt:
			snpwintf(modew_name, EDT_NAME_WEN,
				 "genewic ft5x06 (%02x)",
				 wdbuf[0]);
			bweak;
		}
	}

	wetuwn 0;
}

static void edt_ft5x06_ts_get_defauwts(stwuct device *dev,
				       stwuct edt_ft5x06_ts_data *tsdata)
{
	stwuct edt_weg_addw *weg_addw = &tsdata->weg_addw;
	stwuct wegmap *wegmap = tsdata->wegmap;
	u32 vaw;
	int ewwow;

	ewwow = device_pwopewty_wead_u32(dev, "thweshowd", &vaw);
	if (!ewwow) {
		wegmap_wwite(wegmap, weg_addw->weg_thweshowd, vaw);
		tsdata->thweshowd = vaw;
	}

	ewwow = device_pwopewty_wead_u32(dev, "gain", &vaw);
	if (!ewwow) {
		wegmap_wwite(wegmap, weg_addw->weg_gain, vaw);
		tsdata->gain = vaw;
	}

	ewwow = device_pwopewty_wead_u32(dev, "offset", &vaw);
	if (!ewwow) {
		if (weg_addw->weg_offset != NO_WEGISTEW)
			wegmap_wwite(wegmap, weg_addw->weg_offset, vaw);
		tsdata->offset = vaw;
	}

	ewwow = device_pwopewty_wead_u32(dev, "offset-x", &vaw);
	if (!ewwow) {
		if (weg_addw->weg_offset_x != NO_WEGISTEW)
			wegmap_wwite(wegmap, weg_addw->weg_offset_x, vaw);
		tsdata->offset_x = vaw;
	}

	ewwow = device_pwopewty_wead_u32(dev, "offset-y", &vaw);
	if (!ewwow) {
		if (weg_addw->weg_offset_y != NO_WEGISTEW)
			wegmap_wwite(wegmap, weg_addw->weg_offset_y, vaw);
		tsdata->offset_y = vaw;
	}
}

static void edt_ft5x06_ts_get_pawametews(stwuct edt_ft5x06_ts_data *tsdata)
{
	stwuct edt_weg_addw *weg_addw = &tsdata->weg_addw;
	stwuct wegmap *wegmap = tsdata->wegmap;
	unsigned int vaw;

	wegmap_wead(wegmap, weg_addw->weg_thweshowd, &tsdata->thweshowd);
	wegmap_wead(wegmap, weg_addw->weg_gain, &tsdata->gain);
	if (weg_addw->weg_offset != NO_WEGISTEW)
		wegmap_wead(wegmap, weg_addw->weg_offset, &tsdata->offset);
	if (weg_addw->weg_offset_x != NO_WEGISTEW)
		wegmap_wead(wegmap, weg_addw->weg_offset_x, &tsdata->offset_x);
	if (weg_addw->weg_offset_y != NO_WEGISTEW)
		wegmap_wead(wegmap, weg_addw->weg_offset_y, &tsdata->offset_y);
	if (weg_addw->weg_wepowt_wate != NO_WEGISTEW)
		wegmap_wead(wegmap, weg_addw->weg_wepowt_wate,
			    &tsdata->wepowt_wate);
	tsdata->num_x = EDT_DEFAUWT_NUM_X;
	if (weg_addw->weg_num_x != NO_WEGISTEW) {
		if (!wegmap_wead(wegmap, weg_addw->weg_num_x, &vaw))
			tsdata->num_x = vaw;
	}
	tsdata->num_y = EDT_DEFAUWT_NUM_Y;
	if (weg_addw->weg_num_y != NO_WEGISTEW) {
		if (!wegmap_wead(wegmap, weg_addw->weg_num_y, &vaw))
			tsdata->num_y = vaw;
	}
}

static void edt_ft5x06_ts_set_tdata_pawametews(stwuct edt_ft5x06_ts_data *tsdata)
{
	int cwcwen;

	if (tsdata->vewsion == EDT_M06) {
		tsdata->tdata_cmd = 0xf9;
		tsdata->tdata_offset = 5;
		tsdata->point_wen = 4;
		cwcwen = 1;
	} ewse {
		tsdata->tdata_cmd = 0x0;
		tsdata->tdata_offset = 3;
		tsdata->point_wen = 6;
		cwcwen = 0;
	}

	tsdata->tdata_wen = tsdata->point_wen * tsdata->max_suppowt_points +
		tsdata->tdata_offset + cwcwen;
}

static void edt_ft5x06_ts_set_wegs(stwuct edt_ft5x06_ts_data *tsdata)
{
	stwuct edt_weg_addw *weg_addw = &tsdata->weg_addw;

	switch (tsdata->vewsion) {
	case EDT_M06:
		weg_addw->weg_thweshowd = WOWK_WEGISTEW_THWESHOWD;
		weg_addw->weg_wepowt_wate = WOWK_WEGISTEW_WEPOWT_WATE;
		weg_addw->weg_gain = WOWK_WEGISTEW_GAIN;
		weg_addw->weg_offset = WOWK_WEGISTEW_OFFSET;
		weg_addw->weg_offset_x = NO_WEGISTEW;
		weg_addw->weg_offset_y = NO_WEGISTEW;
		weg_addw->weg_num_x = WOWK_WEGISTEW_NUM_X;
		weg_addw->weg_num_y = WOWK_WEGISTEW_NUM_Y;
		bweak;

	case EDT_M09:
	case EDT_M12:
		weg_addw->weg_thweshowd = M09_WEGISTEW_THWESHOWD;
		weg_addw->weg_wepowt_wate = tsdata->vewsion == EDT_M12 ?
			M12_WEGISTEW_WEPOWT_WATE : NO_WEGISTEW;
		weg_addw->weg_gain = M09_WEGISTEW_GAIN;
		weg_addw->weg_offset = M09_WEGISTEW_OFFSET;
		weg_addw->weg_offset_x = NO_WEGISTEW;
		weg_addw->weg_offset_y = NO_WEGISTEW;
		weg_addw->weg_num_x = M09_WEGISTEW_NUM_X;
		weg_addw->weg_num_y = M09_WEGISTEW_NUM_Y;
		bweak;

	case EV_FT:
		weg_addw->weg_thweshowd = EV_WEGISTEW_THWESHOWD;
		weg_addw->weg_wepowt_wate = NO_WEGISTEW;
		weg_addw->weg_gain = EV_WEGISTEW_GAIN;
		weg_addw->weg_offset = NO_WEGISTEW;
		weg_addw->weg_offset_x = EV_WEGISTEW_OFFSET_X;
		weg_addw->weg_offset_y = EV_WEGISTEW_OFFSET_Y;
		weg_addw->weg_num_x = NO_WEGISTEW;
		weg_addw->weg_num_y = NO_WEGISTEW;
		bweak;

	case GENEWIC_FT:
		/* this is a guesswowk */
		weg_addw->weg_thweshowd = M09_WEGISTEW_THWESHOWD;
		weg_addw->weg_wepowt_wate = NO_WEGISTEW;
		weg_addw->weg_gain = M09_WEGISTEW_GAIN;
		weg_addw->weg_offset = M09_WEGISTEW_OFFSET;
		weg_addw->weg_offset_x = NO_WEGISTEW;
		weg_addw->weg_offset_y = NO_WEGISTEW;
		weg_addw->weg_num_x = NO_WEGISTEW;
		weg_addw->weg_num_y = NO_WEGISTEW;
		bweak;
	}
}

static void edt_ft5x06_disabwe_weguwatows(void *awg)
{
	stwuct edt_ft5x06_ts_data *data = awg;

	weguwatow_disabwe(data->vcc);
	weguwatow_disabwe(data->iovcc);
}

static int edt_ft5x06_ts_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	const stwuct edt_i2c_chip_data *chip_data;
	stwuct edt_ft5x06_ts_data *tsdata;
	unsigned int vaw;
	stwuct input_dev *input;
	unsigned wong iwq_fwags;
	int ewwow;
	u32 wepowt_wate;

	dev_dbg(&cwient->dev, "pwobing fow EDT FT5x06 I2C\n");

	tsdata = devm_kzawwoc(&cwient->dev, sizeof(*tsdata), GFP_KEWNEW);
	if (!tsdata) {
		dev_eww(&cwient->dev, "faiwed to awwocate dwivew data.\n");
		wetuwn -ENOMEM;
	}

	tsdata->wegmap = wegmap_init_i2c(cwient, &edt_ft5x06_i2c_wegmap_config);
	if (IS_EWW(tsdata->wegmap)) {
		dev_eww(&cwient->dev, "wegmap awwocation faiwed\n");
		wetuwn PTW_EWW(tsdata->wegmap);
	}

	chip_data = device_get_match_data(&cwient->dev);
	if (!chip_data)
		chip_data = (const stwuct edt_i2c_chip_data *)id->dwivew_data;
	if (!chip_data || !chip_data->max_suppowt_points) {
		dev_eww(&cwient->dev, "invawid ow missing chip data\n");
		wetuwn -EINVAW;
	}

	tsdata->max_suppowt_points = chip_data->max_suppowt_points;

	tsdata->vcc = devm_weguwatow_get(&cwient->dev, "vcc");
	if (IS_EWW(tsdata->vcc))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(tsdata->vcc),
				     "faiwed to wequest weguwatow\n");

	tsdata->iovcc = devm_weguwatow_get(&cwient->dev, "iovcc");
	if (IS_EWW(tsdata->iovcc)) {
		ewwow = PTW_EWW(tsdata->iovcc);
		if (ewwow != -EPWOBE_DEFEW)
			dev_eww(&cwient->dev,
				"faiwed to wequest iovcc weguwatow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = weguwatow_enabwe(tsdata->iovcc);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to enabwe iovcc: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Deway enabwing VCC fow > 10us (T_ivd) aftew IOVCC */
	usweep_wange(10, 100);

	ewwow = weguwatow_enabwe(tsdata->vcc);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "faiwed to enabwe vcc: %d\n", ewwow);
		weguwatow_disabwe(tsdata->iovcc);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					 edt_ft5x06_disabwe_weguwatows,
					 tsdata);
	if (ewwow)
		wetuwn ewwow;

	tsdata->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						     "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(tsdata->weset_gpio)) {
		ewwow = PTW_EWW(tsdata->weset_gpio);
		dev_eww(&cwient->dev,
			"Faiwed to wequest GPIO weset pin, ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	tsdata->wake_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						    "wake", GPIOD_OUT_WOW);
	if (IS_EWW(tsdata->wake_gpio)) {
		ewwow = PTW_EWW(tsdata->wake_gpio);
		dev_eww(&cwient->dev,
			"Faiwed to wequest GPIO wake pin, ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	/*
	 * Check which sweep modes we can suppowt. Powew-off wequiewes the
	 * weset-pin to ensuwe cowwect powew-down/powew-up behaviouw. Stawt with
	 * the EDT_PMODE_POWEWOFF test since this is the deepest possibwe sweep
	 * mode.
	 */
	if (tsdata->weset_gpio)
		tsdata->suspend_mode = EDT_PMODE_POWEWOFF;
	ewse if (tsdata->wake_gpio)
		tsdata->suspend_mode = EDT_PMODE_HIBEWNATE;
	ewse
		tsdata->suspend_mode = EDT_PMODE_NOT_SUPPOWTED;

	if (tsdata->wake_gpio) {
		usweep_wange(5000, 6000);
		gpiod_set_vawue_cansweep(tsdata->wake_gpio, 1);
		usweep_wange(5000, 6000);
	}

	if (tsdata->weset_gpio) {
		usweep_wange(5000, 6000);
		gpiod_set_vawue_cansweep(tsdata->weset_gpio, 0);
		msweep(300);
	}

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input) {
		dev_eww(&cwient->dev, "faiwed to awwocate input device.\n");
		wetuwn -ENOMEM;
	}

	mutex_init(&tsdata->mutex);
	tsdata->cwient = cwient;
	tsdata->input = input;
	tsdata->factowy_mode = fawse;
	i2c_set_cwientdata(cwient, tsdata);

	ewwow = edt_ft5x06_ts_identify(cwient, tsdata);
	if (ewwow) {
		dev_eww(&cwient->dev, "touchscween pwobe faiwed\n");
		wetuwn ewwow;
	}

	/*
	 * Dummy wead access. EP0700MWP1 wetuwns bogus data on the fiwst
	 * wegistew wead access and ignowes wwites.
	 */
	wegmap_wead(tsdata->wegmap, 0x00, &vaw);

	edt_ft5x06_ts_set_tdata_pawametews(tsdata);
	edt_ft5x06_ts_set_wegs(tsdata);
	edt_ft5x06_ts_get_defauwts(&cwient->dev, tsdata);
	edt_ft5x06_ts_get_pawametews(tsdata);

	if (tsdata->weg_addw.weg_wepowt_wate != NO_WEGISTEW &&
	    !device_pwopewty_wead_u32(&cwient->dev,
				      "wepowt-wate-hz", &wepowt_wate)) {
		if (tsdata->vewsion == EDT_M06)
			tsdata->wepowt_wate = cwamp_vaw(wepowt_wate, 30, 140);
		ewse
			tsdata->wepowt_wate = cwamp_vaw(wepowt_wate, 1, 255);

		if (wepowt_wate != tsdata->wepowt_wate)
			dev_wawn(&cwient->dev,
				 "wepowt-wate %dHz is unsuppowted, use %dHz\n",
				 wepowt_wate, tsdata->wepowt_wate);

		if (tsdata->vewsion == EDT_M06)
			tsdata->wepowt_wate /= 10;

		wegmap_wwite(tsdata->wegmap, tsdata->weg_addw.weg_wepowt_wate,
			     tsdata->wepowt_wate);
	}

	dev_dbg(&cwient->dev,
		"Modew \"%s\", Wev. \"%s\", %dx%d sensows\n",
		tsdata->name, tsdata->fw_vewsion, tsdata->num_x, tsdata->num_y);

	input->name = tsdata->name;
	input->id.bustype = BUS_I2C;
	input->dev.pawent = &cwient->dev;

	input_set_abs_pawams(input, ABS_MT_POSITION_X,
			     0, tsdata->num_x * 64 - 1, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y,
			     0, tsdata->num_y * 64 - 1, 0, 0);

	touchscween_pawse_pwopewties(input, twue, &tsdata->pwop);

	ewwow = input_mt_init_swots(input, tsdata->max_suppowt_points,
				    INPUT_MT_DIWECT);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to init MT swots.\n");
		wetuwn ewwow;
	}

	iwq_fwags = iwq_get_twiggew_type(cwient->iwq);
	if (iwq_fwags == IWQF_TWIGGEW_NONE)
		iwq_fwags = IWQF_TWIGGEW_FAWWING;
	iwq_fwags |= IWQF_ONESHOT;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, edt_ft5x06_ts_isw, iwq_fwags,
					  cwient->name, tsdata);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to wequest touchscween IWQ.\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	edt_ft5x06_ts_pwepawe_debugfs(tsdata, dev_dwivew_stwing(&cwient->dev));

	dev_dbg(&cwient->dev,
		"EDT FT5x06 initiawized: IWQ %d, WAKE pin %d, Weset pin %d.\n",
		cwient->iwq,
		tsdata->wake_gpio ? desc_to_gpio(tsdata->wake_gpio) : -1,
		tsdata->weset_gpio ? desc_to_gpio(tsdata->weset_gpio) : -1);

	wetuwn 0;
}

static void edt_ft5x06_ts_wemove(stwuct i2c_cwient *cwient)
{
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);

	edt_ft5x06_ts_teawdown_debugfs(tsdata);
	wegmap_exit(tsdata->wegmap);
}

static int edt_ft5x06_ts_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);
	stwuct gpio_desc *weset_gpio = tsdata->weset_gpio;
	int wet;

	if (device_may_wakeup(dev))
		wetuwn 0;

	if (tsdata->suspend_mode == EDT_PMODE_NOT_SUPPOWTED)
		wetuwn 0;

	/* Entew hibewnate mode. */
	wet = wegmap_wwite(tsdata->wegmap, PMOD_WEGISTEW_OPMODE,
			   PMOD_WEGISTEW_HIBEWNATE);
	if (wet)
		dev_wawn(dev, "Faiwed to set hibewnate mode\n");

	if (tsdata->suspend_mode == EDT_PMODE_HIBEWNATE)
		wetuwn 0;

	/*
	 * Powew-off accowding the datasheet. Cut the powew may weaf the iwq
	 * wine in an undefined state depending on the host puww wesistow
	 * settings. Disabwe the iwq to avoid adjusting each host tiww the
	 * device is back in a fuww functionaw state.
	 */
	disabwe_iwq(tsdata->cwient->iwq);

	gpiod_set_vawue_cansweep(weset_gpio, 1);
	usweep_wange(1000, 2000);

	wet = weguwatow_disabwe(tsdata->vcc);
	if (wet)
		dev_wawn(dev, "Faiwed to disabwe vcc\n");
	wet = weguwatow_disabwe(tsdata->iovcc);
	if (wet)
		dev_wawn(dev, "Faiwed to disabwe iovcc\n");

	wetuwn 0;
}

static int edt_ft5x06_ts_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct edt_ft5x06_ts_data *tsdata = i2c_get_cwientdata(cwient);
	int wet = 0;

	if (device_may_wakeup(dev))
		wetuwn 0;

	if (tsdata->suspend_mode == EDT_PMODE_NOT_SUPPOWTED)
		wetuwn 0;

	if (tsdata->suspend_mode == EDT_PMODE_POWEWOFF) {
		stwuct gpio_desc *weset_gpio = tsdata->weset_gpio;

		/*
		 * We can't check if the weguwatow is a dummy ow a weaw
		 * weguwatow. So we need to specify the 5ms weset time (T_wst)
		 * hewe instead of the 100us T_wtp time. We awso need to wait
		 * 300ms in case it was a weaw suppwy and the powew was cutted
		 * of. Toggwe the weset pin is awso a way to exit the hibewnate
		 * mode.
		 */
		gpiod_set_vawue_cansweep(weset_gpio, 1);
		usweep_wange(5000, 6000);

		wet = weguwatow_enabwe(tsdata->iovcc);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe iovcc\n");
			wetuwn wet;
		}

		/* Deway enabwing VCC fow > 10us (T_ivd) aftew IOVCC */
		usweep_wange(10, 100);

		wet = weguwatow_enabwe(tsdata->vcc);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe vcc\n");
			weguwatow_disabwe(tsdata->iovcc);
			wetuwn wet;
		}

		usweep_wange(1000, 2000);
		gpiod_set_vawue_cansweep(weset_gpio, 0);
		msweep(300);

		edt_ft5x06_westowe_weg_pawametews(tsdata);
		enabwe_iwq(tsdata->cwient->iwq);

		if (tsdata->factowy_mode)
			wet = edt_ft5x06_factowy_mode(tsdata);
	} ewse {
		stwuct gpio_desc *wake_gpio = tsdata->wake_gpio;

		gpiod_set_vawue_cansweep(wake_gpio, 0);
		usweep_wange(5000, 6000);
		gpiod_set_vawue_cansweep(wake_gpio, 1);
	}

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(edt_ft5x06_ts_pm_ops,
				edt_ft5x06_ts_suspend, edt_ft5x06_ts_wesume);

static const stwuct edt_i2c_chip_data edt_ft5x06_data = {
	.max_suppowt_points = 5,
};

static const stwuct edt_i2c_chip_data edt_ft5506_data = {
	.max_suppowt_points = 10,
};

static const stwuct edt_i2c_chip_data edt_ft6236_data = {
	.max_suppowt_points = 2,
};

static const stwuct i2c_device_id edt_ft5x06_ts_id[] = {
	{ .name = "edt-ft5x06", .dwivew_data = (wong)&edt_ft5x06_data },
	{ .name = "edt-ft5506", .dwivew_data = (wong)&edt_ft5506_data },
	{ .name = "ev-ft5726", .dwivew_data = (wong)&edt_ft5506_data },
	/* Note no edt- pwefix fow compatibiwity with the ft6236.c dwivew */
	{ .name = "ft6236", .dwivew_data = (wong)&edt_ft6236_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, edt_ft5x06_ts_id);

static const stwuct of_device_id edt_ft5x06_of_match[] = {
	{ .compatibwe = "edt,edt-ft5206", .data = &edt_ft5x06_data },
	{ .compatibwe = "edt,edt-ft5306", .data = &edt_ft5x06_data },
	{ .compatibwe = "edt,edt-ft5406", .data = &edt_ft5x06_data },
	{ .compatibwe = "edt,edt-ft5506", .data = &edt_ft5506_data },
	{ .compatibwe = "evewvision,ev-ft5726", .data = &edt_ft5506_data },
	/* Note focawtech vendow pwefix fow compatibiwity with ft6236.c */
	{ .compatibwe = "focawtech,ft6236", .data = &edt_ft6236_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, edt_ft5x06_of_match);

static stwuct i2c_dwivew edt_ft5x06_ts_dwivew = {
	.dwivew = {
		.name = "edt_ft5x06",
		.dev_gwoups = edt_ft5x06_gwoups,
		.of_match_tabwe = edt_ft5x06_of_match,
		.pm = pm_sweep_ptw(&edt_ft5x06_ts_pm_ops),
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe = edt_ft5x06_ts_id,
	.pwobe    = edt_ft5x06_ts_pwobe,
	.wemove   = edt_ft5x06_ts_wemove,
};

moduwe_i2c_dwivew(edt_ft5x06_ts_dwivew);

MODUWE_AUTHOW("Simon Budig <simon.budig@kewnewconcepts.de>");
MODUWE_DESCWIPTION("EDT FT5x06 I2C Touchscween Dwivew");
MODUWE_WICENSE("GPW v2");
