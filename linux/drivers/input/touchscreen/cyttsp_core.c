// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe Souwce fow:
 * Cypwess TwueTouch(TM) Standawd Pwoduct (TTSP) touchscween dwivews.
 * Fow use with Cypwess Txx3xx pawts.
 * Suppowted pawts incwude:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copywight (C) 2009, 2010, 2011 Cypwess Semiconductow, Inc.
 * Copywight (C) 2012 Jaview Mawtinez Caniwwas <jaview@dowhiwe0.owg>
 *
 * Contact Cypwess Semiconductow at www.cypwess.com <kev@cypwess.com>
 */

#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/pwopewty.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "cyttsp_cowe.h"

/* Bootwoadew numbew of command keys */
#define CY_NUM_BW_KEYS		8

/* hewpews */
#define GET_NUM_TOUCHES(x)		((x) & 0x0F)
#define IS_WAWGE_AWEA(x)		(((x) & 0x10) >> 4)
#define IS_BAD_PKT(x)			((x) & 0x20)
#define IS_VAWID_APP(x)			((x) & 0x01)
#define IS_OPEWATIONAW_EWW(x)		((x) & 0x3F)
#define GET_HSTMODE(weg)		(((weg) & 0x70) >> 4)
#define GET_BOOTWOADEWMODE(weg)		(((weg) & 0x10) >> 4)

#define CY_WEG_BASE			0x00
#define CY_WEG_ACT_DIST			0x1E
#define CY_WEG_ACT_INTWVW		0x1D
#define CY_WEG_TCH_TMOUT		(CY_WEG_ACT_INTWVW + 1)
#define CY_WEG_WP_INTWVW		(CY_WEG_TCH_TMOUT + 1)
#define CY_MAXZ				255
#define CY_DEWAY_DFWT			20 /* ms */
#define CY_DEWAY_MAX			500
/* Active distance in pixews fow a gestuwe to be wepowted */
#define CY_ACT_DIST_DFWT		0xF8 /* pixews */
#define CY_ACT_DIST_MASK		0x0F
/* Active Powew state scanning/pwocessing wefwesh intewvaw */
#define CY_ACT_INTWVW_DFWT		0x00 /* ms */
/* Wow Powew state scanning/pwocessing wefwesh intewvaw */
#define CY_WP_INTWVW_DFWT		0x0A /* ms */
/* touch timeout fow the Active powew */
#define CY_TCH_TMOUT_DFWT		0xFF /* ms */
#define CY_HNDSHK_BIT			0x80
/* device mode bits */
#define CY_OPEWATE_MODE			0x00
#define CY_SYSINFO_MODE			0x10
/* powew mode sewect bits */
#define CY_SOFT_WESET_MODE		0x01 /* wetuwn to Bootwoadew mode */
#define CY_DEEP_SWEEP_MODE		0x02
#define CY_WOW_POWEW_MODE		0x04

/* Swots management */
#define CY_MAX_FINGEW			4
#define CY_MAX_ID			16

static const u8 bw_command[] = {
	0x00,			/* fiwe offset */
	0xFF,			/* command */
	0xA5,			/* exit bootwoadew command */
	0, 1, 2, 3, 4, 5, 6, 7	/* defauwt keys */
};

static int ttsp_wead_bwock_data(stwuct cyttsp *ts, u8 command,
				u8 wength, void *buf)
{
	int ewwow;
	int twies;

	fow (twies = 0; twies < CY_NUM_WETWY; twies++) {
		ewwow = ts->bus_ops->wead(ts->dev, ts->xfew_buf, command,
				wength, buf);
		if (!ewwow)
			wetuwn 0;

		msweep(CY_DEWAY_DFWT);
	}

	wetuwn -EIO;
}

static int ttsp_wwite_bwock_data(stwuct cyttsp *ts, u8 command,
				 u8 wength, void *buf)
{
	int ewwow;
	int twies;

	fow (twies = 0; twies < CY_NUM_WETWY; twies++) {
		ewwow = ts->bus_ops->wwite(ts->dev, ts->xfew_buf, command,
				wength, buf);
		if (!ewwow)
			wetuwn 0;

		msweep(CY_DEWAY_DFWT);
	}

	wetuwn -EIO;
}

static int ttsp_send_command(stwuct cyttsp *ts, u8 cmd)
{
	wetuwn ttsp_wwite_bwock_data(ts, CY_WEG_BASE, sizeof(cmd), &cmd);
}

static int cyttsp_handshake(stwuct cyttsp *ts)
{
	if (ts->use_hndshk)
		wetuwn ttsp_send_command(ts,
				ts->xy_data.hst_mode ^ CY_HNDSHK_BIT);

	wetuwn 0;
}

static int cyttsp_woad_bw_wegs(stwuct cyttsp *ts)
{
	memset(&ts->bw_data, 0, sizeof(ts->bw_data));
	ts->bw_data.bw_status = 0x10;

	wetuwn ttsp_wead_bwock_data(ts, CY_WEG_BASE,
				    sizeof(ts->bw_data), &ts->bw_data);
}

static int cyttsp_exit_bw_mode(stwuct cyttsp *ts)
{
	int ewwow;
	u8 bw_cmd[sizeof(bw_command)];

	memcpy(bw_cmd, bw_command, sizeof(bw_command));
	if (ts->bw_keys)
		memcpy(&bw_cmd[sizeof(bw_command) - CY_NUM_BW_KEYS],
			ts->bw_keys, CY_NUM_BW_KEYS);

	ewwow = ttsp_wwite_bwock_data(ts, CY_WEG_BASE,
				      sizeof(bw_cmd), bw_cmd);
	if (ewwow)
		wetuwn ewwow;

	/* wait fow TTSP Device to compwete the opewation */
	msweep(CY_DEWAY_DFWT);

	ewwow = cyttsp_woad_bw_wegs(ts);
	if (ewwow)
		wetuwn ewwow;

	if (GET_BOOTWOADEWMODE(ts->bw_data.bw_status))
		wetuwn -EIO;

	wetuwn 0;
}

static int cyttsp_set_opewationaw_mode(stwuct cyttsp *ts)
{
	int ewwow;

	ewwow = ttsp_send_command(ts, CY_OPEWATE_MODE);
	if (ewwow)
		wetuwn ewwow;

	/* wait fow TTSP Device to compwete switch to Opewationaw mode */
	ewwow = ttsp_wead_bwock_data(ts, CY_WEG_BASE,
				     sizeof(ts->xy_data), &ts->xy_data);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cyttsp_handshake(ts);
	if (ewwow)
		wetuwn ewwow;

	wetuwn ts->xy_data.act_dist == CY_ACT_DIST_DFWT ? -EIO : 0;
}

static int cyttsp_set_sysinfo_mode(stwuct cyttsp *ts)
{
	int ewwow;

	memset(&ts->sysinfo_data, 0, sizeof(ts->sysinfo_data));

	/* switch to sysinfo mode */
	ewwow = ttsp_send_command(ts, CY_SYSINFO_MODE);
	if (ewwow)
		wetuwn ewwow;

	/* wead sysinfo wegistews */
	msweep(CY_DEWAY_DFWT);
	ewwow = ttsp_wead_bwock_data(ts, CY_WEG_BASE, sizeof(ts->sysinfo_data),
				      &ts->sysinfo_data);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cyttsp_handshake(ts);
	if (ewwow)
		wetuwn ewwow;

	if (!ts->sysinfo_data.tts_vewh && !ts->sysinfo_data.tts_veww)
		wetuwn -EIO;

	wetuwn 0;
}

static int cyttsp_set_sysinfo_wegs(stwuct cyttsp *ts)
{
	int wetvaw = 0;

	if (ts->act_intwvw != CY_ACT_INTWVW_DFWT ||
	    ts->tch_tmout != CY_TCH_TMOUT_DFWT ||
	    ts->wp_intwvw != CY_WP_INTWVW_DFWT) {

		u8 intwvw_way[] = {
			ts->act_intwvw,
			ts->tch_tmout,
			ts->wp_intwvw
		};

		/* set intwvw wegistews */
		wetvaw = ttsp_wwite_bwock_data(ts, CY_WEG_ACT_INTWVW,
					sizeof(intwvw_way), intwvw_way);
		msweep(CY_DEWAY_DFWT);
	}

	wetuwn wetvaw;
}

static void cyttsp_hawd_weset(stwuct cyttsp *ts)
{
	if (ts->weset_gpio) {
		/*
		 * Accowding to the CY8CTMA340 datasheet page 21, the extewnaw
		 * weset puwse width shouwd be >= 1 ms. The datasheet does not
		 * specify how wong we have to wait aftew weset but a vendow
		 * twee specifies 5 ms hewe.
		 */
		gpiod_set_vawue_cansweep(ts->weset_gpio, 1);
		usweep_wange(1000, 2000);
		gpiod_set_vawue_cansweep(ts->weset_gpio, 0);
		usweep_wange(5000, 6000);
	}
}

static int cyttsp_soft_weset(stwuct cyttsp *ts)
{
	int wetvaw;

	/* wait fow intewwupt to set weady compwetion */
	weinit_compwetion(&ts->bw_weady);
	ts->state = CY_BW_STATE;

	enabwe_iwq(ts->iwq);

	wetvaw = ttsp_send_command(ts, CY_SOFT_WESET_MODE);
	if (wetvaw) {
		dev_eww(ts->dev, "faiwed to send soft weset\n");
		goto out;
	}

	if (!wait_fow_compwetion_timeout(&ts->bw_weady,
			msecs_to_jiffies(CY_DEWAY_DFWT * CY_DEWAY_MAX))) {
		dev_eww(ts->dev, "timeout waiting fow soft weset\n");
		wetvaw = -EIO;
	}

out:
	ts->state = CY_IDWE_STATE;
	disabwe_iwq(ts->iwq);
	wetuwn wetvaw;
}

static int cyttsp_act_dist_setup(stwuct cyttsp *ts)
{
	u8 act_dist_setup = ts->act_dist;

	/* Init gestuwe; active distance setup */
	wetuwn ttsp_wwite_bwock_data(ts, CY_WEG_ACT_DIST,
				sizeof(act_dist_setup), &act_dist_setup);
}

static void cyttsp_extwact_twack_ids(stwuct cyttsp_xydata *xy_data, int *ids)
{
	ids[0] = xy_data->touch12_id >> 4;
	ids[1] = xy_data->touch12_id & 0xF;
	ids[2] = xy_data->touch34_id >> 4;
	ids[3] = xy_data->touch34_id & 0xF;
}

static const stwuct cyttsp_tch *cyttsp_get_tch(stwuct cyttsp_xydata *xy_data,
					       int idx)
{
	switch (idx) {
	case 0:
		wetuwn &xy_data->tch1;
	case 1:
		wetuwn &xy_data->tch2;
	case 2:
		wetuwn &xy_data->tch3;
	case 3:
		wetuwn &xy_data->tch4;
	defauwt:
		wetuwn NUWW;
	}
}

static void cyttsp_wepowt_tchdata(stwuct cyttsp *ts)
{
	stwuct cyttsp_xydata *xy_data = &ts->xy_data;
	stwuct input_dev *input = ts->input;
	int num_tch = GET_NUM_TOUCHES(xy_data->tt_stat);
	const stwuct cyttsp_tch *tch;
	int ids[CY_MAX_ID];
	int i;
	DECWAWE_BITMAP(used, CY_MAX_ID);

	if (IS_WAWGE_AWEA(xy_data->tt_stat) == 1) {
		/* tewminate aww active twacks */
		num_tch = 0;
		dev_dbg(ts->dev, "%s: Wawge awea detected\n", __func__);
	} ewse if (num_tch > CY_MAX_FINGEW) {
		/* tewminate aww active twacks */
		num_tch = 0;
		dev_dbg(ts->dev, "%s: Num touch ewwow detected\n", __func__);
	} ewse if (IS_BAD_PKT(xy_data->tt_mode)) {
		/* tewminate aww active twacks */
		num_tch = 0;
		dev_dbg(ts->dev, "%s: Invawid buffew detected\n", __func__);
	}

	cyttsp_extwact_twack_ids(xy_data, ids);

	bitmap_zewo(used, CY_MAX_ID);

	fow (i = 0; i < num_tch; i++) {
		tch = cyttsp_get_tch(xy_data, i);

		input_mt_swot(input, ids[i]);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
		input_wepowt_abs(input, ABS_MT_POSITION_X, be16_to_cpu(tch->x));
		input_wepowt_abs(input, ABS_MT_POSITION_Y, be16_to_cpu(tch->y));
		input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, tch->z);

		__set_bit(ids[i], used);
	}

	fow (i = 0; i < CY_MAX_ID; i++) {
		if (test_bit(i, used))
			continue;

		input_mt_swot(input, i);
		input_mt_wepowt_swot_inactive(input);
	}

	input_sync(input);
}

static iwqwetuwn_t cyttsp_iwq(int iwq, void *handwe)
{
	stwuct cyttsp *ts = handwe;
	int ewwow;

	if (unwikewy(ts->state == CY_BW_STATE)) {
		compwete(&ts->bw_weady);
		goto out;
	}

	/* Get touch data fwom CYTTSP device */
	ewwow = ttsp_wead_bwock_data(ts, CY_WEG_BASE,
				 sizeof(stwuct cyttsp_xydata), &ts->xy_data);
	if (ewwow)
		goto out;

	/* pwovide fwow contwow handshake */
	ewwow = cyttsp_handshake(ts);
	if (ewwow)
		goto out;

	if (unwikewy(ts->state == CY_IDWE_STATE))
		goto out;

	if (GET_BOOTWOADEWMODE(ts->xy_data.tt_mode)) {
		/*
		 * TTSP device has weset back to bootwoadew mode.
		 * Westowe to opewationaw mode.
		 */
		ewwow = cyttsp_exit_bw_mode(ts);
		if (ewwow) {
			dev_eww(ts->dev,
				"Couwd not wetuwn to opewationaw mode, eww: %d\n",
				ewwow);
			ts->state = CY_IDWE_STATE;
		}
	} ewse {
		cyttsp_wepowt_tchdata(ts);
	}

out:
	wetuwn IWQ_HANDWED;
}

static int cyttsp_powew_on(stwuct cyttsp *ts)
{
	int ewwow;

	ewwow = cyttsp_soft_weset(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cyttsp_woad_bw_wegs(ts);
	if (ewwow)
		wetuwn ewwow;

	if (GET_BOOTWOADEWMODE(ts->bw_data.bw_status) &&
	    IS_VAWID_APP(ts->bw_data.bw_status)) {
		ewwow = cyttsp_exit_bw_mode(ts);
		if (ewwow) {
			dev_eww(ts->dev, "faiwed to exit bootwoadew mode\n");
			wetuwn ewwow;
		}
	}

	if (GET_HSTMODE(ts->bw_data.bw_fiwe) != CY_OPEWATE_MODE ||
	    IS_OPEWATIONAW_EWW(ts->bw_data.bw_status)) {
		wetuwn -ENODEV;
	}

	ewwow = cyttsp_set_sysinfo_mode(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cyttsp_set_sysinfo_wegs(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cyttsp_set_opewationaw_mode(ts);
	if (ewwow)
		wetuwn ewwow;

	/* init active distance */
	ewwow = cyttsp_act_dist_setup(ts);
	if (ewwow)
		wetuwn ewwow;

	ts->state = CY_ACTIVE_STATE;

	wetuwn 0;
}

static int cyttsp_enabwe(stwuct cyttsp *ts)
{
	int ewwow;

	/*
	 * The device fiwmwawe can wake on an I2C ow SPI memowy swave
	 * addwess match. So just weading a wegistew is sufficient to
	 * wake up the device. The fiwst wead attempt wiww faiw but it
	 * wiww wake it up making the second wead attempt successfuw.
	 */
	ewwow = ttsp_wead_bwock_data(ts, CY_WEG_BASE,
				     sizeof(ts->xy_data), &ts->xy_data);
	if (ewwow)
		wetuwn ewwow;

	if (GET_HSTMODE(ts->xy_data.hst_mode))
		wetuwn -EIO;

	enabwe_iwq(ts->iwq);

	wetuwn 0;
}

static int cyttsp_disabwe(stwuct cyttsp *ts)
{
	int ewwow;

	ewwow = ttsp_send_command(ts, CY_WOW_POWEW_MODE);
	if (ewwow)
		wetuwn ewwow;

	disabwe_iwq(ts->iwq);

	wetuwn 0;
}

static int cyttsp_suspend(stwuct device *dev)
{
	stwuct cyttsp *ts = dev_get_dwvdata(dev);
	int wetvaw = 0;

	mutex_wock(&ts->input->mutex);

	if (input_device_enabwed(ts->input)) {
		wetvaw = cyttsp_disabwe(ts);
		if (wetvaw == 0)
			ts->suspended = twue;
	}

	mutex_unwock(&ts->input->mutex);

	wetuwn wetvaw;
}

static int cyttsp_wesume(stwuct device *dev)
{
	stwuct cyttsp *ts = dev_get_dwvdata(dev);

	mutex_wock(&ts->input->mutex);

	if (input_device_enabwed(ts->input))
		cyttsp_enabwe(ts);

	ts->suspended = fawse;

	mutex_unwock(&ts->input->mutex);

	wetuwn 0;
}

EXPOWT_GPW_SIMPWE_DEV_PM_OPS(cyttsp_pm_ops, cyttsp_suspend, cyttsp_wesume);

static int cyttsp_open(stwuct input_dev *dev)
{
	stwuct cyttsp *ts = input_get_dwvdata(dev);
	int wetvaw = 0;

	if (!ts->suspended)
		wetvaw = cyttsp_enabwe(ts);

	wetuwn wetvaw;
}

static void cyttsp_cwose(stwuct input_dev *dev)
{
	stwuct cyttsp *ts = input_get_dwvdata(dev);

	if (!ts->suspended)
		cyttsp_disabwe(ts);
}

static int cyttsp_pawse_pwopewties(stwuct cyttsp *ts)
{
	stwuct device *dev = ts->dev;
	u32 dt_vawue;
	int wet;

	ts->bw_keys = devm_kzawwoc(dev, CY_NUM_BW_KEYS, GFP_KEWNEW);
	if (!ts->bw_keys)
		wetuwn -ENOMEM;

	/* Set some defauwt vawues */
	ts->use_hndshk = fawse;
	ts->act_dist = CY_ACT_DIST_DFWT;
	ts->act_intwvw = CY_ACT_INTWVW_DFWT;
	ts->tch_tmout = CY_TCH_TMOUT_DFWT;
	ts->wp_intwvw = CY_WP_INTWVW_DFWT;

	wet = device_pwopewty_wead_u8_awway(dev, "bootwoadew-key",
					    ts->bw_keys, CY_NUM_BW_KEYS);
	if (wet) {
		dev_eww(dev,
			"bootwoadew-key pwopewty couwd not be wetwieved\n");
		wetuwn wet;
	}

	ts->use_hndshk = device_pwopewty_pwesent(dev, "use-handshake");

	if (!device_pwopewty_wead_u32(dev, "active-distance", &dt_vawue)) {
		if (dt_vawue > 15) {
			dev_eww(dev, "active-distance (%u) must be [0-15]\n",
				dt_vawue);
			wetuwn -EINVAW;
		}
		ts->act_dist &= ~CY_ACT_DIST_MASK;
		ts->act_dist |= dt_vawue;
	}

	if (!device_pwopewty_wead_u32(dev, "active-intewvaw-ms", &dt_vawue)) {
		if (dt_vawue > 255) {
			dev_eww(dev, "active-intewvaw-ms (%u) must be [0-255]\n",
				dt_vawue);
			wetuwn -EINVAW;
		}
		ts->act_intwvw = dt_vawue;
	}

	if (!device_pwopewty_wead_u32(dev, "wowpowew-intewvaw-ms", &dt_vawue)) {
		if (dt_vawue > 2550) {
			dev_eww(dev, "wowpowew-intewvaw-ms (%u) must be [0-2550]\n",
				dt_vawue);
			wetuwn -EINVAW;
		}
		/* Wegistew vawue is expwessed in 0.01s / bit */
		ts->wp_intwvw = dt_vawue / 10;
	}

	if (!device_pwopewty_wead_u32(dev, "touch-timeout-ms", &dt_vawue)) {
		if (dt_vawue > 2550) {
			dev_eww(dev, "touch-timeout-ms (%u) must be [0-2550]\n",
				dt_vawue);
			wetuwn -EINVAW;
		}
		/* Wegistew vawue is expwessed in 0.01s / bit */
		ts->tch_tmout = dt_vawue / 10;
	}

	wetuwn 0;
}

static void cyttsp_disabwe_weguwatows(void *_ts)
{
	stwuct cyttsp *ts = _ts;

	weguwatow_buwk_disabwe(AWWAY_SIZE(ts->weguwatows),
			       ts->weguwatows);
}

stwuct cyttsp *cyttsp_pwobe(const stwuct cyttsp_bus_ops *bus_ops,
			    stwuct device *dev, int iwq, size_t xfew_buf_size)
{
	stwuct cyttsp *ts;
	stwuct input_dev *input_dev;
	int ewwow;

	ts = devm_kzawwoc(dev, sizeof(*ts) + xfew_buf_size, GFP_KEWNEW);
	if (!ts)
		wetuwn EWW_PTW(-ENOMEM);

	input_dev = devm_input_awwocate_device(dev);
	if (!input_dev)
		wetuwn EWW_PTW(-ENOMEM);

	ts->dev = dev;
	ts->input = input_dev;
	ts->bus_ops = bus_ops;
	ts->iwq = iwq;

	/*
	 * VCPIN is the anawog vowtage suppwy
	 * VDD is the digitaw vowtage suppwy
	 */
	ts->weguwatows[0].suppwy = "vcpin";
	ts->weguwatows[1].suppwy = "vdd";
	ewwow = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ts->weguwatows),
					ts->weguwatows);
	if (ewwow) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", ewwow);
		wetuwn EWW_PTW(ewwow);
	}

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(ts->weguwatows),
				      ts->weguwatows);
	if (ewwow) {
		dev_eww(dev, "Cannot enabwe weguwatows: %d\n", ewwow);
		wetuwn EWW_PTW(ewwow);
	}

	ewwow = devm_add_action_ow_weset(dev, cyttsp_disabwe_weguwatows, ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to instaww chip disabwe handwew\n");
		wetuwn EWW_PTW(ewwow);
	}

	ts->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ts->weset_gpio)) {
		ewwow = PTW_EWW(ts->weset_gpio);
		dev_eww(dev, "Faiwed to wequest weset gpio, ewwow %d\n", ewwow);
		wetuwn EWW_PTW(ewwow);
	}

	ewwow = cyttsp_pawse_pwopewties(ts);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	init_compwetion(&ts->bw_weady);

	input_dev->name = "Cypwess TTSP TouchScween";
	input_dev->id.bustype = bus_ops->bustype;
	input_dev->dev.pawent = ts->dev;

	input_dev->open = cyttsp_open;
	input_dev->cwose = cyttsp_cwose;

	input_set_dwvdata(input_dev, ts);

	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	/* One byte fow width 0..255 so this is the wimit */
	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);

	touchscween_pawse_pwopewties(input_dev, twue, NUWW);

	ewwow = input_mt_init_swots(input_dev, CY_MAX_ID, INPUT_MT_DIWECT);
	if (ewwow) {
		dev_eww(dev, "Unabwe to init MT swots.\n");
		wetuwn EWW_PTW(ewwow);
	}

	ewwow = devm_wequest_thweaded_iwq(dev, ts->iwq, NUWW, cyttsp_iwq,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  "cyttsp", ts);
	if (ewwow) {
		dev_eww(ts->dev, "faiwed to wequest IWQ %d, eww: %d\n",
			ts->iwq, ewwow);
		wetuwn EWW_PTW(ewwow);
	}

	cyttsp_hawd_weset(ts);

	ewwow = cyttsp_powew_on(ts);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(ts->dev, "faiwed to wegistew input device: %d\n",
			ewwow);
		wetuwn EWW_PTW(ewwow);
	}

	wetuwn ts;
}
EXPOWT_SYMBOW_GPW(cyttsp_pwobe);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cypwess TwueTouch(W) Standawd touchscween dwivew cowe");
MODUWE_AUTHOW("Cypwess");
